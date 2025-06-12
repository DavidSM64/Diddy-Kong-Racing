#include "gltfModel.h"

#include "helpers/fileHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/mathHelper.h"

#include <string>
#include <vector>
#include <cmath>
#include <mutex>

using namespace DkrAssetsTool;

GltfBuildModel::GltfBuildModel(GltfFile &gltf, CContext &cContext, bool isObjectModel) : _isObjectModel(isObjectModel) {
    if(gltf.empty()) {
        return;
    }
    
    // Ignore these nodes, since they are used for meta-data.
    std::vector<std::string> rootNodeBlacklist;
    if(_isObjectModel) {
        rootNodeBlacklist = { "collisionspheres", "attachpoints" };
    } else {
        rootNodeBlacklist = { "bsp" };
    }
    
    std::vector<int> rootNodeIndices = gltf.get_root_node_indices(rootNodeBlacklist);
    
    if(rootNodeIndices.empty()) {
        return;
    }
    
    // Process animation inputs
    for(int i = 0; i < gltf.number_of_animations(); i++) {
        tinygltf::Animation &animation = gltf.get_animation(i);
        _animations.emplace_back(gltf, animation);
    }
    
    // Process materials
    for(int i = 0; i < gltf.number_of_materials(); i++) {
        tinygltf::Material &material = gltf.get_material(i);
        
        bool hasExtras = material.extras.Type() != tinygltf::NULL_TYPE;
        
        if(material.name.empty()) {
            material.name = "material_" + std::to_string(i);
        }
        
        std::string materialId = material.name;
        
        int materialImageIndex = _get_image_index_for_material(gltf, i);
        if(materialImageIndex == -1) {
            // No image associated.
            _add_material(materialId);
        } else {
            tinygltf::Image &image = gltf.get_image(materialImageIndex);
            if(image.uri.empty()) {
                if(image.bufferView == -1) {
                    // No image data found.
                    _add_material(materialId);
                } else {
                    // Embedded image.
                    tinygltf::BufferView &embeddedImgBufferView = gltf.get_bufferview(image.bufferView);
                    tinygltf::Buffer &embeddedImgBuffer = gltf.get_buffer(embeddedImgBufferView.buffer);
                    uint8_t *imgData = GltfHelper::get_buffer_pointer<uint8_t>(embeddedImgBufferView, embeddedImgBuffer, 0);
                    
                    _add_material(materialId, imgData, embeddedImgBufferView.byteLength, image.mimeType);
                }
            } else {
                // image from a filepath.
                auto tryGetFilepath = FileHelper::determine_full_filepath(image.uri, gltf.get_filepath().parent_path());
                if(!tryGetFilepath.has_value()) {
                    DebugHelper::error("Could not find the texture image: ", image.uri);
                }
                std::string pathToImage = tryGetFilepath.value();
                _add_material(materialId, pathToImage);
            }
        }
        // Get the material we just added, to add some extras
        BuildModelMaterial &buildMaterial = _materials.back();
        
        if(hasExtras) {
            if(GltfHelper::has_extra(material.extras, "/format")) {
                buildMaterial.set_format(GltfHelper::get_extra<std::string>(material.extras, "/format", ""));
            }
            if(GltfHelper::has_extra(material.extras, "/render-mode")) {
                buildMaterial.set_rendermode(GltfHelper::get_extra<std::string>(material.extras, "/render-mode", ""));
            }
            if(GltfHelper::has_extra(material.extras, "/flip-texture")) {
                buildMaterial.set_flip_vertically(GltfHelper::get_extra<bool>(material.extras, "/flip-texture", false));
            }
            if(GltfHelper::has_extra(material.extras, "/flags")) {
                buildMaterial.set_flag(_get_render_flags_from_extras(material.extras, "/flags", cContext));
            }
        }
        
        // Get the sampler for the material so we can get wrapS/wrapT for the texture.
        int materialSamplerIndex = _get_image_sampler_index_for_material(gltf, i);
        if(materialSamplerIndex >= 0) {
            tinygltf::Sampler &sampler = gltf.get_sampler(materialSamplerIndex);
            std::string wrapS = (sampler.wrapS == TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE) ? "clamp" : "wrap";
            std::string wrapT = (sampler.wrapT == TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE) ? "clamp" : "wrap";
            buildMaterial.set_wrap_mode(wrapS, wrapT);
        }
        
        buildMaterial.set_double_sided(material.doubleSided);
        
    }
    
    Mat4x4f rootMatrix;
    
    // Process the base model 
    for(int rootNodeIndex : rootNodeIndices) {
        _process_node_base(gltf, rootNodeIndex, rootMatrix);
    }
    
    std::optional<int> attachPointsIndex = gltf.get_root_node_from_name("attachpoints");
    
    if(attachPointsIndex.has_value()) {
        tinygltf::Node &attachPointsNode = gltf.get_node(attachPointsIndex.value());
        for(int childIndex : attachPointsNode.children) {
            tinygltf::Node &attachPointNode = gltf.get_node(childIndex);
            if(attachPointNode.translation.empty()) {
                continue;
            }
            Vec3f position(attachPointNode.translation, 0);
            _attachPoints.emplace_back(position);
        }
    }
}

void GltfBuildModel::_process_node_base(GltfFile &gltf, int nodeIndex, const Mat4x4f &parentMatrix) {
    tinygltf::Node &node = gltf.get_node(nodeIndex);
    
    Mat4x4f nodeMatrix = GltfHelper::calculate_node_matrix(node, parentMatrix);
    
    if(node.mesh >= 0) {
        _process_mesh_base(gltf, node.mesh, nodeMatrix);
    }
    
    for(int childIndex : node.children) {
        _process_node_base(gltf, childIndex, nodeMatrix);
    }
}

void GltfBuildModel::_process_mesh_base(GltfFile &gltf, int meshIndex, const Mat4x4f &nodeMatrix) {
    tinygltf::Mesh &mesh = gltf.get_mesh(meshIndex);
    
    for(auto &primitive : mesh.primitives) {
        if(primitive.material == -1) {
            _set_material("");
        } else {
            tinygltf::Material &material = gltf.get_material(primitive.material);
            _set_material(material.name);
        }
        
        std::optional<std::vector<float>> positions = GltfHelper::get_positions_from_primitive(gltf, primitive);
        std::optional<std::vector<uint8_t>> colors = GltfHelper::get_colors_from_primitive(gltf, primitive);
        
        std::optional<std::vector<float>> morphTargets = std::nullopt;
        
        if(_isObjectModel) {
            // Only parse morph targets data for object models.
            morphTargets = GltfHelper::get_morph_targets_from_primitive(gltf, primitive);
        }
        
        std::vector<BuildModelVertex> vertices = _make_vertices_from_primitive_data(positions, colors, morphTargets, nodeMatrix);
        
        std::optional<std::vector<float>> gltfUVs = GltfHelper::get_uvs_from_primitive(gltf, primitive);
        std::vector<Vec2f> uvs = _adjust_uvs(gltf, primitive.material, gltfUVs);
        
        bool hasUVs = (uvs.size() > 0) && (primitive.material >= 0);
        
        std::optional<std::vector<uint8_t>> indices = GltfHelper::get_indices_from_primitive(gltf, primitive);
        if(indices.has_value()) {
            std::vector<uint8_t> &triIndices = indices.value();
            size_t numberOfTriangles = triIndices.size() / 3;
            
            for(size_t i = 0; i < numberOfTriangles; i++) {
                BuildModelVertex &vertexA = vertices[triIndices[i * 3 + 0]];
                BuildModelVertex &vertexB = vertices[triIndices[i * 3 + 1]];
                BuildModelVertex &vertexC = vertices[triIndices[i * 3 + 2]];
                
                if(!hasUVs) {
                    _add_new_triangle_to_current_block(vertexA, vertexB, vertexC);
                } else {
                    _add_new_triangle_to_current_block(vertexA, vertexB, vertexC, 
                        uvs[triIndices[i * 3 + 0]], uvs[triIndices[i * 3 + 1]], uvs[triIndices[i * 3 + 2]]);
                }
            }
        } else {
            // Each 3 positions makes a triangle.
            size_t numberOfTriangles = vertices.size() / 3;
            
            for(size_t i = 0; i < numberOfTriangles; i++) {
                BuildModelVertex &vertexA = vertices[i * 3 + 0];
                BuildModelVertex &vertexB = vertices[i * 3 + 1];
                BuildModelVertex &vertexC = vertices[i * 3 + 2];
                
                if(!hasUVs) {
                    _add_new_triangle_to_current_block(vertexA, vertexB, vertexC);
                } else {
                    _add_new_triangle_to_current_block(vertexA, vertexB, vertexC, 
                        uvs[i * 3 + 0], uvs[i * 3 + 1], uvs[i * 3 + 2]);
                }
            }
        }
    }
}

std::vector<BuildModelVertex> GltfBuildModel::_make_vertices_from_primitive_data(std::optional<std::vector<float>> &positions, 
  std::optional<std::vector<uint8_t>> &colors, std::optional<std::vector<float>> &morphTargets, 
  const Mat4x4f &nodeMatrix) {
    if(!positions.has_value()) {
        return {};
    }
    
    std::vector<float> &positionValues = positions.value();
    
    size_t numberOfVertices = positionValues.size() / 3;
    
    std::vector<BuildModelVertex> out;
    out.reserve(numberOfVertices);
    
    // TODO: Apply nodeMatrix to position Vec3f
    
    if(colors.has_value()) {
        std::vector<uint8_t> &colorValues = colors.value();
        for(size_t i = 0; i < numberOfVertices; i++) {
            out.emplace_back(Vec3f(positionValues, i * 3), Vec4f(colorValues, i * 4));
        }
    } else {
        for(size_t i = 0; i < numberOfVertices; i++) {
            out.emplace_back(Vec3f(positionValues, i * 3));
        }
    }
    
    if(morphTargets.has_value()){
        std::vector<float> &targets = morphTargets.value();
        size_t numberOfValuesPerKeyframe = positionValues.size();
        size_t numberOfKeyframes = targets.size() / numberOfValuesPerKeyframe;
        for(size_t keyframe = 0; keyframe < numberOfKeyframes; keyframe++) {
            for(size_t i = 0; i < numberOfVertices; i++) {
                out[i].add_morph_target(Vec3f(targets, (keyframe * numberOfValuesPerKeyframe) + (i * 3)));
            }
        }
    }
    
    return out;
}

int GltfBuildModel::_get_image_index_for_material(GltfFile &gltf, int materialIndex) {
    if(materialIndex == -1) {
        return -1;
    }
    
    if(_imageIndexForMaterialCache.find(materialIndex) == _imageIndexForMaterialCache.end()) {
        tinygltf::Material &material = gltf.get_material(materialIndex);
        int textureIndex = material.pbrMetallicRoughness.baseColorTexture.index;
        
        if(textureIndex == -1) {
            _imageIndexForMaterialCache[materialIndex] = -1;
        } else {
            tinygltf::Texture &texture = gltf.get_texture(textureIndex);
            _imageIndexForMaterialCache[materialIndex] = texture.source;
        }
    }
    
    return _imageIndexForMaterialCache.at(materialIndex);
}

int GltfBuildModel::_get_image_sampler_index_for_material(GltfFile &gltf, int materialIndex) {
    if(materialIndex == -1) {
        return -1;
    }
    
    if(_imageSamplerIndexForMaterialCache.find(materialIndex) == _imageSamplerIndexForMaterialCache.end()) {
        tinygltf::Material &material = gltf.get_material(materialIndex);
        int textureIndex = material.pbrMetallicRoughness.baseColorTexture.index;
        
        if(textureIndex == -1) {
            _imageSamplerIndexForMaterialCache[materialIndex] = -1;
        } else {
            tinygltf::Texture &texture = gltf.get_texture(textureIndex);
            _imageSamplerIndexForMaterialCache[materialIndex] = texture.sampler;
        }
    }
    
    return _imageSamplerIndexForMaterialCache.at(materialIndex);
}

std::vector<Vec2f> GltfBuildModel::_adjust_uvs(GltfFile &gltf, int materialIndex, std::optional<std::vector<float>> &uvs) {
    if(!uvs.has_value() || uvs.value().size() == 0) {
        return {};
    }
    
    std::vector<Vec2f> out(uvs.value().size() / 2);
    
    int imageIndex = _get_image_index_for_material(gltf, materialIndex);
    
    if(imageIndex == -1) {
        return out;
    }
    
    std::vector<float> &uvValues = uvs.value();
    tinygltf::Image &image = gltf.get_image(imageIndex); // Need the image info to get width & height of image.
    
    if(image.width == 0 || image.height == 0) {
        DebugHelper::warn("Could not process UVs properly! Tex width = ", image.width, ", Tex height = ", image.height);
        return out;
    }
    
    for(size_t i = 0; i < out.size(); i++) {
        out[i].u = uvValues[i * 2 + 0] * (image.width * 32);
        out[i].v = uvValues[i * 2 + 1] * (image.height * 32);
    }
    
    return out;
}

uint32_t GltfBuildModel::_get_render_flags_from_extras(tinygltf::Value& extras, std::string jsonPointer, CContext &cContext) {
    std::vector<std::string> flags;
    switch(GltfHelper::get_extra_type(extras, "/flags")) {
        case tinygltf::ARRAY_TYPE:
        {
            GltfHelper::get_extra_array<std::string>(extras, "/flags", flags);
            break;
        }
        case tinygltf::STRING_TYPE:
        {
            std::string flagsString = GltfHelper::get_extra<std::string>(extras, "/flags", "");
            StringHelper::split_and_trim(flagsString, {',','|'}, flags); // Flags are separated by either commas or vertical pipes.
            break;
        }
        default:
            // Unsupported.
            return 0;
    }
    uint32_t out = 0;
    for(const std::string &flag : flags) {
        if(flag.empty()) {
            continue;
        }
        out |= cContext.get_int_value_of_symbol(flag);
    }
    return out;
}
