#include "buildModel.h"

#include "helpers/dataHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/gzipHelper.h"

#include "fileTypes/objectModel.hpp"
#include "fileTypes/batch.hpp"
#include "fileTypes/triangle.hpp"
#include "fileTypes/vertex.hpp"

using namespace DkrAssetsTool;

void BuildModel::generate_object_model(fs::path dstPath) {
    size_t numberOfTriangles = _total_number_of_triangles();
    size_t numberOfVertices  = _total_number_of_vertices();
    size_t numberOfBatches  = _total_number_of_batches();
    size_t numberOfBatchesToAllocate  = _total_number_of_batches_to_allocate();
    
    size_t sizeOfHeader = DataHelper::align16(sizeof(ObjectModel));
    size_t sizeOfTextures = 0;
    size_t sizeOfVertices = DataHelper::align16(sizeof(DkrVertex) * numberOfVertices);
    size_t sizeOfTriangles = DataHelper::align16(sizeof(DkrTriangle) * numberOfTriangles);
    size_t sizeOfBatches  = DataHelper::align16(sizeof(DkrBatch) * numberOfBatchesToAllocate);
    
    // Calculated the file size for the binary model file.
    size_t calculatedFileSize = sizeOfHeader +
                                sizeOfTextures +
                                sizeOfVertices +
                                sizeOfTriangles +
                                sizeOfBatches;
    
    std::vector<uint8_t> outFile(calculatedFileSize);
    
    ObjectModel *objectModelHeader = reinterpret_cast<ObjectModel *>(&outFile[0]);
    
    objectModelHeader->textures = sizeOfHeader;
    objectModelHeader->vertices = objectModelHeader->textures + sizeOfTextures;
    objectModelHeader->triangles = objectModelHeader->vertices + sizeOfVertices;
    objectModelHeader->batches = objectModelHeader->triangles + sizeOfTriangles;
    objectModelHeader->numberOfTriangles = (int16_t)numberOfTriangles;
    objectModelHeader->numberOfVertices = (int16_t)numberOfVertices;
    objectModelHeader->numberOfBatches = (int16_t)numberOfBatches;
    objectModelHeader->fileSize = (int16_t)calculatedFileSize;
    
    DkrVertex *vertices = reinterpret_cast<DkrVertex *>(&outFile[objectModelHeader->vertices]);
    DkrTriangle *triangles = reinterpret_cast<DkrTriangle *>(&outFile[objectModelHeader->triangles]);
    DkrBatch *batches = reinterpret_cast<DkrBatch *>(&outFile[objectModelHeader->batches]);
    
    for(auto &block : _blocks) {
        block.write_batches(batches, vertices, triangles);
    }
    
    fs::path newPath = dstPath;
    newPath.replace_extension(".debug.bin");
    FileHelper::write_binary_file(outFile, newPath, true);
        
    std::vector<uint8_t> compressedOutFile = GzipHelper::compress_gzip(outFile);
    
    FileHelper::write_binary_file(compressedOutFile, dstPath, true);
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
