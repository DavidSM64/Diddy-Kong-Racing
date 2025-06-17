#include "buildModelBlock.h"

#include "helpers/debugHelper.h"

using namespace DkrAssetsTool;

BuildModelBlock::BuildModelBlock(std::optional<std::string> materialId) : _materialId(materialId) {
}

void BuildModelBlock::add_new_triangle(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC, Vec2f uv0, Vec2f uv1, Vec2f uv2) {
    if(_batches.size() == 0) {
        _batches.emplace_back(_materialId); // Create a new batch if none exist yet.
    }
    
    bool addedTriangle = false;
    
    addedTriangle = _batches.back().add_new_triangle(vertA, vertB, vertC, uv0, uv1, uv2);
    if(addedTriangle) {
        return;
    }
    
    _batches.emplace_back(_materialId); // Create a new batch, then add the triangle to it.
    addedTriangle = _batches.back().add_new_triangle(vertA, vertB, vertC, uv0, uv1, uv2);
    DebugHelper::assert_(addedTriangle, 
        "(BuildModelBlock::add_new_triangle) Failed to add a new triangle to a new batch. Something is terribly wrong!");
}

void BuildModelBlock::set_material(std::optional<std::string> materialId) {
    if(materialId == _materialId) {
        return;
    }
    _materialId = materialId;
    _batches.emplace_back(_materialId); // Create a new batch with the new material.
}

size_t BuildModelBlock::total_number_of_triangles() {
    size_t count = 0;
    
    for(auto &batch : _batches) {
        count += batch.number_of_triangles();
    }
    
    return count;
}

size_t BuildModelBlock::total_number_of_vertices() {
    size_t count = 0;
    
    for(auto &batch : _batches) {
        count += batch.number_of_vertices();
    }
    
    return count;
}

size_t BuildModelBlock::number_of_batches() {
    return _batches.size();
}

size_t BuildModelBlock::number_of_batches_to_allocate() {
    return _batches.size() + 1; // Must have an extra entry to calculate the sizes for the last batch.
}

void BuildModelBlock::write_batches(const std::map<std::string, int> &materialIds, std::vector<BuildModelMaterial> &materials, 
  DkrBatch*& outBatches, DkrVertex*& outVertices, DkrTriangle*& outTriangles, float modelScale) {
    size_t vertexCount = 0;
    size_t triCount = 0;
    for(BuildModelBatch &batch : _batches) {
        batch.write_batch(materialIds, materials, outBatches, outVertices, outTriangles, modelScale);
        outBatches->verticesOffset = vertexCount;
        outBatches->trianglesOffset = triCount;
        outBatches->unk1 = (int8_t)batch.number_of_vertices();
        vertexCount += batch.number_of_vertices();
        triCount += batch.number_of_triangles();
        outBatches++; // next out batch.
    }
    // One extra batch for that extra entry.
    outBatches->verticesOffset = vertexCount;
    outBatches->trianglesOffset = triCount;
}

void BuildModelBlock::process_vertices(std::function<void(BuildModelVertex &vertex)> callbackFunction) {
    for(BuildModelBatch &batch : _batches) {
        batch.process_vertices(callbackFunction);
    }
}
