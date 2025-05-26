#include "buildModel.h"

#include "helpers/dataHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/gzipHelper.h"

#include "fileTypes/objectModel.hpp"
#include "fileTypes/batch.hpp"
#include "fileTypes/triangle.hpp"
#include "fileTypes/vertex.hpp"
#include "fileTypes/textureInfo.hpp"

#include "misc/globalSettings.h"

using namespace DkrAssetsTool;

void BuildModel::generate_object_model(BuildInfo &info) {
    size_t numberOfTriangles = _total_number_of_triangles();
    size_t numberOfVertices  = _total_number_of_vertices();
    size_t numberOfBatches  = _total_number_of_batches();
    size_t numberOfBatchesToAllocate  = _total_number_of_batches_to_allocate();
    size_t numberOfTextures = _total_number_of_textures();
    
    size_t sizeOfHeader = DataHelper::align16(sizeof(ObjectModel));
    size_t sizeOfTextures = DataHelper::align16(sizeof(DkrTextureInfo) * numberOfTextures);
    size_t sizeOfVertices = DataHelper::align16(sizeof(DkrVertex) * numberOfVertices);
    size_t sizeOfTriangles = DataHelper::align16(sizeof(DkrTriangle) * numberOfTriangles);
    size_t sizeOfBatches  = DataHelper::align16(sizeof(DkrBatch) * numberOfBatchesToAllocate);
    
    // Calculated the file size for the binary model file.
    size_t calculatedFileSize = sizeOfHeader +
                                sizeOfTextures +
                                sizeOfVertices +
                                sizeOfTriangles +
                                sizeOfBatches;
    
    info.out.resize(calculatedFileSize);
    
    ObjectModel *objectModelHeader = reinterpret_cast<ObjectModel *>(&info.out[0]);
    
    objectModelHeader->textures = sizeOfHeader;
    objectModelHeader->vertices = objectModelHeader->textures + sizeOfTextures;
    objectModelHeader->triangles = objectModelHeader->vertices + sizeOfVertices;
    objectModelHeader->batches = objectModelHeader->triangles + sizeOfTriangles;
    objectModelHeader->numberOfTextures= (int16_t)numberOfTextures;
    objectModelHeader->numberOfTriangles = (int16_t)numberOfTriangles;
    objectModelHeader->numberOfVertices = (int16_t)numberOfVertices;
    objectModelHeader->numberOfBatches = (int16_t)numberOfBatches;
    objectModelHeader->fileSize = (int16_t)calculatedFileSize;
    
    DkrTextureInfo *textures = reinterpret_cast<DkrTextureInfo *>(&info.out[objectModelHeader->textures]);
    DkrVertex *vertices = reinterpret_cast<DkrVertex *>(&info.out[objectModelHeader->vertices]);
    DkrTriangle *triangles = reinterpret_cast<DkrTriangle *>(&info.out[objectModelHeader->triangles]);
    DkrBatch *batches = reinterpret_cast<DkrBatch *>(&info.out[objectModelHeader->batches]);
    
    bool hasAnimatedTexture = false;
    for(size_t materialIndex = 0; materialIndex < numberOfTextures; materialIndex++) {
        BuildModelMaterial &material = _materials[materialIndex];
        material.write_to(&textures[materialIndex], info);
        hasAnimatedTexture = hasAnimatedTexture || material.is_texture_animated();
    }
    objectModelHeader->hasAnimatedTexture = (int)hasAnimatedTexture;
    
    for(auto &block : _blocks) {
        block.write_batches(_materialIds, _materials, batches, vertices, triangles);
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
    _materials.emplace_back(texturePath);
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
