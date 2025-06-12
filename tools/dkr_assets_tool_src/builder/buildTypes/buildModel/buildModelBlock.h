#pragma once

#include <optional>
#include <vector>
#include <map>
#include <functional>

#include "buildModelVertex.h"
#include "buildModelMaterial.h"
#include "buildModelBatch.h"

#include "fileTypes/vertex.hpp"
#include "fileTypes/triangle.hpp"
#include "fileTypes/batch.hpp"

namespace DkrAssetsTool {
class BuildModelBlock {
public:
    BuildModelBlock(std::optional<std::string> materialId = std::nullopt);
    
    void add_new_triangle(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC,
        Vec2f uv0, Vec2f uv1, Vec2f uv2);
    void set_material(std::optional<std::string> materialId);
    
    size_t total_number_of_triangles();
    size_t total_number_of_vertices();
    size_t number_of_batches();
    size_t number_of_batches_to_allocate();
    
    void write_batches(const std::map<std::string, int> &materialIds, std::vector<BuildModelMaterial> &materials, 
        DkrBatch*& outBatches, DkrVertex*& outVertices, DkrTriangle*& outTriangles, float modelScale);
        
    void process_vertices(std::function<void(BuildModelVertex &vertex)> callbackFunction);
    
private:
    std::vector<BuildModelBatch> _batches;
    std::optional<std::string> _materialId = std::nullopt;
};
}
