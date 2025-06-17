#include "buildModel.h"

#include "helpers/dataHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/gzipHelper.h"

#include "fileTypes/objectModel.hpp"
#include "fileTypes/batch.hpp"
#include "fileTypes/triangle.hpp"
#include "fileTypes/vertex.hpp"
#include "fileTypes/textureInfo.hpp"

#include "libs/bytes_view.hpp"

#include "misc/globalSettings.h"

#include "builder/buildInfoCollection.h"

using namespace DkrAssetsTool;

void BuildModel::generate_object_model(BuildInfo &info) {
    const JsonFile &modelJson = info.get_src_json_file();
    float modelScale = modelJson.get_float("/scale", 1000.0f);
    
    size_t numberOfTriangles = _total_number_of_triangles();
    size_t numberOfVertices  = _total_number_of_vertices();
    size_t numberOfAnimatedVertices = _total_number_of_animated_vertices();
    size_t numberOfBatches  = _total_number_of_batches();
    size_t numberOfBatchesToAllocate  = _total_number_of_batches_to_allocate();
    size_t numberOfTextures = _total_number_of_textures();
    size_t numberOfAttachPoints = _attachPoints.size();
    
    size_t sizeOfHeader = DataHelper::align16(sizeof(ObjectModel));
    size_t sizeOfTextures = DataHelper::align16(sizeof(DkrTextureInfo) * numberOfTextures);
    size_t sizeOfVertices = DataHelper::align16(sizeof(DkrVertex) * (numberOfVertices + numberOfAttachPoints));
    size_t sizeOfTriangles = DataHelper::align16(sizeof(DkrTriangle) * numberOfTriangles);
    size_t sizeOfBatches  = DataHelper::align16(sizeof(DkrBatch) * numberOfBatchesToAllocate);
    size_t sizeOfAnimatedVertexIndices = _animations.empty() ? 0 : DataHelper::align16(sizeof(int16_t) * numberOfVertices);
    size_t sizeOfAttachPoints = DataHelper::align16(sizeof(be_int16_t) * numberOfAttachPoints);
    
    // Calculated the file size for the binary model file.
    size_t calculatedFileSize = sizeOfHeader +
                                sizeOfTextures +
                                sizeOfVertices +
                                sizeOfTriangles +
                                sizeOfBatches +
                                sizeOfAnimatedVertexIndices +
                                sizeOfAttachPoints;
    
    info.out.resize(calculatedFileSize);
    
    ObjectModel *objectModelHeader = reinterpret_cast<ObjectModel *>(&info.out[0]);
    
    objectModelHeader->textures = sizeOfHeader;
    objectModelHeader->vertices = objectModelHeader->textures + sizeOfTextures;
    objectModelHeader->triangles = objectModelHeader->vertices + sizeOfVertices;
    objectModelHeader->batches = objectModelHeader->triangles + sizeOfTriangles;
    objectModelHeader->animatedVertexIndices = objectModelHeader->batches + sizeOfBatches;
    objectModelHeader->attachPoints = objectModelHeader->animatedVertexIndices + sizeOfAnimatedVertexIndices;
    objectModelHeader->numberOfTextures = (int16_t)numberOfTextures;
    objectModelHeader->numberOfTriangles = (int16_t)numberOfTriangles;
    objectModelHeader->numberOfVertices = (int16_t)numberOfVertices;
    objectModelHeader->numberOfBatches = (int16_t)numberOfBatches;
    objectModelHeader->numberOfAttachPoints = (int16_t)numberOfAttachPoints;
    objectModelHeader->fileSize = (int16_t)calculatedFileSize;
    objectModelHeader->numberOfAnimatedVertices = (int16_t)numberOfAnimatedVertices;
    
    DkrTextureInfo *textures = reinterpret_cast<DkrTextureInfo *>(&info.out[objectModelHeader->textures]);
    DkrVertex *vertices = reinterpret_cast<DkrVertex *>(&info.out[objectModelHeader->vertices]);
    DkrTriangle *triangles = reinterpret_cast<DkrTriangle *>(&info.out[objectModelHeader->triangles]);
    DkrBatch *batches = reinterpret_cast<DkrBatch *>(&info.out[objectModelHeader->batches]);
    be_int16_t *animatedVertexIndices = reinterpret_cast<be_int16_t *>(&info.out[objectModelHeader->animatedVertexIndices]);
    be_int16_t *attachPoints = reinterpret_cast<be_int16_t *>(&info.out[objectModelHeader->attachPoints]);
    
    bool hasAnimatedTexture = false;
    for(size_t materialIndex = 0; materialIndex < numberOfTextures; materialIndex++) {
        BuildModelMaterial &material = _materials[materialIndex];
        
        material.write_to(&textures[materialIndex], info);
        hasAnimatedTexture = hasAnimatedTexture || material.is_texture_animated();
    }
    objectModelHeader->hasAnimatedTexture = (int)hasAnimatedTexture;
    
    for(auto &block : _blocks) {
        block.write_batches(_materialIds, _materials, batches, vertices, triangles, modelScale);
    }
    
    // Does nothing with static models.
    _generate_animations(info, objectModelHeader, animatedVertexIndices);
    
    vertices = reinterpret_cast<DkrVertex *>(&info.out[objectModelHeader->vertices]);
    for(size_t i = 0; i < numberOfAttachPoints; i++) {
        attachPoints[i] = numberOfVertices + i;
        
        DkrVertex *vertex = &vertices[numberOfVertices + i];
        vertex->x = static_cast<int16_t>(_attachPoints[i].x * modelScale);
        vertex->y = static_cast<int16_t>(_attachPoints[i].y * modelScale);
        vertex->z = static_cast<int16_t>(_attachPoints[i].z * modelScale);
    }
    
    bool debugKeepUncompressed = GlobalSettings::get_value<bool>("/debug/keep-uncompressed", false);
    
    if(debugKeepUncompressed) {
        fs::path outUncompressedPath = GlobalSettings::get_decomp_path("build_subpath", "build/");
        outUncompressedPath /= "debug/models";
        outUncompressedPath /= info.get_src_json_file().get_filepath().filename().replace_extension(".bin");
        FileHelper::write_binary_file(info.out, outUncompressedPath, true);
    }
    
    info.out = GzipHelper::compress_gzip(info.out);
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}

void BuildModel::_add_new_triangle_to_current_block(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC, Vec2f uv0, Vec2f uv1, Vec2f uv2) {
    if(_blocks.size() == 0) {
        _new_block();
    }
    _blocks.back().add_new_triangle(vertA, vertB, vertC, uv0, uv1, uv2);
}

void BuildModel::_add_new_triangle_to_current_block(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC) {
    if(_blocks.size() == 0) {
        _new_block();
    }
    _blocks.back().add_new_triangle(vertA, vertB, vertC, Vec2f(), Vec2f(), Vec2f());
}
    
void BuildModel::_new_block() {
    _blocks.emplace_back(_currentMaterialId);
}
    
void BuildModel::_add_material(std::string id, fs::path texturePath) {
    if(texturePath.empty()) {
        _materialIds[id] = -1;
        return;
    }
    _materialIds[id] = _materials.size();
    _materials.emplace_back(texturePath, id);
}
    
void BuildModel::_add_material(std::string id, uint8_t *imgData, size_t imgDataLength, std::string mimeType) {
    if(imgData == nullptr || imgDataLength == 0) {
        _materialIds[id] = -1;
        return;
    }
    _materialIds[id] = _materials.size();
    _materials.emplace_back(imgData, imgDataLength, mimeType, id);
}

void BuildModel::_set_material(std::string id) {
    _currentMaterialId = id;
    if(_blocks.size() == 0) {
        _new_block();
    } else {
        _blocks.back().set_material(_currentMaterialId);
    }
}

std::optional<std::reference_wrapper<BuildModelMaterial>> BuildModel::_try_get_material(std::string id) {
    if(_materialIds.find(id) == _materialIds.end() || _materialIds.at(id) == -1) {
        return std::nullopt;
    }
    
    return _materials.at(_materialIds.at(id));
}
    
size_t BuildModel::_total_number_of_triangles() {
    size_t count = 0;
    
    for(auto &block : _blocks) {
        count += block.total_number_of_triangles();
    }
    
    return count;
}

size_t BuildModel::_total_number_of_vertices() {
    size_t count = 0;
    
    for(auto &block : _blocks) {
        count += block.total_number_of_vertices();
    }
    
    return count;
}

size_t BuildModel::_total_number_of_animated_vertices() {
    if(_animations.empty()) {
        return 0;
    }
    
    size_t count = 0;
    
    for(auto &block : _blocks) {
        block.process_vertices([&count](BuildModelVertex &vertex) {
            if(vertex.is_animated()) {
                count++;
            }
        });
    }
    
    return count;
}

size_t BuildModel::_total_number_of_textures() {
    size_t count = 0;
    
    for(auto &material : _materials) {
        if(material.has_texture()) {
            count++;
        }
    }
    
    return count;
}

size_t BuildModel::_total_number_of_batches() {
    size_t count = 0;
    
    for(auto &block : _blocks) {
        count += block.number_of_batches();
    }
    
    return count;
}

size_t BuildModel::_total_number_of_batches_to_allocate() {
    size_t count = 0;
    
    for(auto &block : _blocks) {
        count += block.number_of_batches_to_allocate();
    }
    
    return count;
}

template<typename T, typename T2>
inline void process_keyframe(T *keyframe, size_t &animDataOffset, const std::vector<std::reference_wrapper<BuildModelVertex>> &animatedVertices, AnimWeights &weights, 
  std::optional<AnimWeights> previousWeights, float modelScale) {
    size_t numberOfAnimatedVertices = animatedVertices.size();
    Vec3f vertexDelta;
    
    for(size_t i = 0; i < numberOfAnimatedVertices; i++) {
        const BuildModelVertex &vertex = animatedVertices.at(i);
        if(previousWeights.has_value()) {
            vertexDelta = vertex.animated_position(weights) - vertex.animated_position(previousWeights.value());
        } else {
            vertexDelta = vertex.animated_position(weights) - vertex.position();
        }
            
        keyframe[i].offsetX = static_cast<T2>(vertexDelta.x * modelScale);
        keyframe[i].offsetY = static_cast<T2>(vertexDelta.y * modelScale);
        keyframe[i].offsetZ = static_cast<T2>(vertexDelta.z * modelScale);
    }
    
    animDataOffset += sizeof(T) * numberOfAnimatedVertices;
}

void BuildModel::_generate_animations(BuildInfo &info, ObjectModel *objectModelHeader, be_int16_t *outAnimatedIndicesPtr) {
    if((_animations.empty()) || (objectModelHeader->numberOfAnimatedVertices < 1)) {
        return;
    }
    
    std::vector<int16_t> animatedVertexIndices;
    std::vector<std::reference_wrapper<BuildModelVertex>> animatedVertices;
    
    animatedVertexIndices.reserve(objectModelHeader->numberOfVertices);
    animatedVertices.reserve(objectModelHeader->numberOfVertices); // Should have no more than the number of vertices.
    
    for(auto &block : _blocks) {
        block.process_vertices([&animatedVertexIndices, &animatedVertices](BuildModelVertex &vertex) {
            if(!vertex.is_animated()) {
                animatedVertexIndices.emplace_back(-1);
                return; // Don't include this vertex.
            }
            animatedVertexIndices.emplace_back(animatedVertices.size());
            animatedVertices.emplace_back(vertex);
        });
    }
    
    for(size_t i = 0; i < objectModelHeader->numberOfVertices; i++) {
        outAnimatedIndicesPtr[i] = animatedVertexIndices[i];
    }
    
    std::optional<AnimWeights> weights = std::nullopt;
    std::optional<AnimTranslations> translations = std::nullopt;
    std::optional<AnimRotations> rotations = std::nullopt;
    std::optional<AnimScales> scales = std::nullopt;
    
    std::optional<AnimWeights> previousWeights = std::nullopt;
    
    size_t numberOfAnimatedVertices = animatedVertices.size();
    
    bool debugKeepUncompressed = GlobalSettings::get_value<bool>("/debug/keep-uncompressed", false);
    
    BuildInfoCollection &collection = info.get_collection();
    
    std::vector<size_t> animationIndices;
    
    const JsonFile &modelJson = info.get_src_json_file();
    float secondsPerKeyframe = modelJson.get_float("/animation/seconds-per-keyframe", 0.267f);
    float modelScale = modelJson.get_float("/scale", 1000.0f);
    
    size_t animIndex = 0;
    for(BuildModelAnimation &anim : _animations) {
        size_t numberOfKeyframes = std::floor(anim.get_max_time() / secondsPerKeyframe) + 1;
        
        size_t animationDataSize = sizeof(ObjectModelAnimationHeader) + 
                                  (sizeof(ObjectModelAnimationKeyframeHeader) * numberOfKeyframes) + // Each keyframe has a header that is 12-bytes long. Mainly used for head tilting?
                                  (sizeof(ObjectModelAnimationKeyframeVertexS16) * numberOfAnimatedVertices) + // First keyframe uses 16-bit values.
                                  (sizeof(ObjectModelAnimationKeyframeVertexS8) * (numberOfAnimatedVertices - 1) * numberOfKeyframes); // Following keyframes use 8-bit values.
        
        std::vector<uint8_t> animationData(animationDataSize);
        BytesView animDataView(animationData);
        size_t animDataOffset = 0;
        
        ObjectModelAnimationHeader *animHeader = animDataView.data_cast<ObjectModelAnimationHeader>(animDataOffset);
        animHeader->keyframeCount = numberOfKeyframes;
        
        animDataOffset += sizeof(ObjectModelAnimationHeader);
        
        bool skipAnimation = false;
        
        for(size_t keyframe = 0; keyframe < numberOfKeyframes; keyframe++) {
            //ObjectModelAnimationKeyframeHeader *keyframeHeader = animDataView.data_cast<ObjectModelAnimationKeyframeHeader>(animDataOffset);
            animDataOffset += sizeof(ObjectModelAnimationKeyframeHeader);
            
            float keyframeTime = keyframe * secondsPerKeyframe;
            anim.get_inputs_for_time(keyframeTime, weights, translations, rotations, scales);
            
            if(keyframe == 0) {
                if(translations.has_value() || rotations.has_value() || scales.has_value()) {
                    DebugHelper::warn("Only morph target/shape key animation is supported at the moment.");
                }
                if(!weights.has_value()) {
                    skipAnimation = true;
                    break; // Only Morph Targets are supported at the moment.
                }
                
                ObjectModelAnimationKeyframeVertexS16 *firstKeyframe = animDataView.data_cast<ObjectModelAnimationKeyframeVertexS16>(animDataOffset);
                process_keyframe<ObjectModelAnimationKeyframeVertexS16, int16_t>(firstKeyframe, animDataOffset, animatedVertices, 
                    weights.value(), std::nullopt, modelScale);
            } else {
                ObjectModelAnimationKeyframeVertexS8 *followingKeyframe = animDataView.data_cast<ObjectModelAnimationKeyframeVertexS8>(animDataOffset);
                process_keyframe<ObjectModelAnimationKeyframeVertexS8, int8_t>(followingKeyframe, animDataOffset, animatedVertices, 
                    weights.value(), previousWeights, modelScale);
            }
            
            previousWeights = weights;
        }
        
        if(skipAnimation) {
            continue;
        }
        
        while((animationData.size() % 16) != 0) {
            animationData.emplace_back(0);
        }
        
        std::string buildId = info.get_build_id() + "_ANIM_" + std::to_string(animIndex);
        
        if(debugKeepUncompressed) {
            fs::path outUncompressedPath = GlobalSettings::get_decomp_path("build_subpath", "build/");
            outUncompressedPath /= "debug/custom-animations";
            outUncompressedPath /= buildId + ".bin";
            FileHelper::write_binary_file(animationData, outUncompressedPath, true);
        }
        
        animationData = GzipHelper::compress_gzip(animationData);
        
        size_t newAnimId = collection.add_deferred_build_info("ASSET_OBJECT_ANIMATIONS", buildId, info.get_build_id(), info.get_section_build_id(), 
            animationData, info.get_path_to_directory(), info.get_info_context());
        
        animationIndices.emplace_back(newAnimId);
        
        animIndex++;
    }
    
    
}
