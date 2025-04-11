#pragma once

#include <optional>
#include <vector>

#include "helpers/mathHelper.h"

#include "buildModelVertex.h"

#include "fileTypes/vertex.hpp"
#include "fileTypes/triangle.hpp"
#include "fileTypes/batch.hpp"

namespace DkrAssetsTool {
    
struct BuildModelTriangle {
    uint16_t a, b, c;
    Vec2f uv0, uv1, uv2;
    
    BuildModelTriangle(uint16_t a, uint16_t b, uint16_t c, Vec2f uv0, Vec2f uv1, Vec2f uv2) :
        a(a), b(b), c(c), uv0(uv0), uv1(uv1), uv2(uv2){}
};
    
    
class BuildModelBatch {
public:
    BuildModelBatch(std::optional<std::string> materialId = std::nullopt);

    // Returns true if successful, or false if a new batch needs to be created.
    bool add_new_triangle(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC,
        Vec2f uv0, Vec2f uv1, Vec2f uv2);
    void set_material(std::optional<std::string> materialId);
    
    size_t number_of_triangles();
    size_t number_of_vertices();
    
    void write_batch(DkrBatch* outBatch, DkrVertex*& outVertices, DkrTriangle*& outTriangles);
    
private:
    std::vector<BuildModelTriangle> _triangles;
    std::vector<BuildModelVertex> _vertices;
    std::optional<std::string> _materialId = std::nullopt;
    
    std::optional<uint16_t> _index_of_vertex(const BuildModelVertex& vertex);
    uint16_t _add_vertex(const BuildModelVertex& vertex);
};
}
