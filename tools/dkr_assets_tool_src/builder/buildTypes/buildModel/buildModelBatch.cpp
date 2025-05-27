#include "buildModelBatch.h"

#include "helpers/debugHelper.h"
#include "helpers/dataHelper.h"

using namespace DkrAssetsTool;

BuildModelBatch::BuildModelBatch(std::optional<std::string> materialId) : _materialId(materialId) {
}

bool BuildModelBatch::add_new_triangle(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC, Vec2f uv0, Vec2f uv1, Vec2f uv2) {
    if(_triangles.size() >= 16) {
        return false;
    }
    
    auto tryGetIndexA = _index_of_vertex(vertA);
    auto tryGetIndexB = _index_of_vertex(vertB);
    auto tryGetIndexC = _index_of_vertex(vertC);
    
    size_t numberOfNewVertices = tryGetIndexA.has_value() + tryGetIndexB.has_value() + tryGetIndexC.has_value();
    
    if(_vertices.size() + numberOfNewVertices >= 24) {
        return false;
    }
    
    // Cannot use .value_or() here, since we only want to run _add_vertex() if it is needed.
    uint16_t indexA = tryGetIndexA.has_value() ? tryGetIndexA.value() : _add_vertex(vertA);
    uint16_t indexB = tryGetIndexB.has_value() ? tryGetIndexB.value() : _add_vertex(vertB);
    uint16_t indexC = tryGetIndexC.has_value() ? tryGetIndexC.value() : _add_vertex(vertC);
    
    _triangles.emplace_back(indexA, indexB, indexC, uv0, uv1, uv2);
    
    return true;
}


void BuildModelBatch::set_material(std::optional<std::string> materialId) {
    _materialId = materialId;
}

size_t BuildModelBatch::number_of_triangles() {
    return _triangles.size();
}

size_t BuildModelBatch::number_of_vertices() {
    return _vertices.size();
}

void BuildModelBatch::write_batch(const std::map<std::string, int> &materialIds, std::vector<BuildModelMaterial> &materials, 
  DkrBatch* outBatch, DkrVertex*& outVertices, DkrTriangle*& outTriangles) {
    uint32_t flags = 0x00000003;
    bool materialDoubleSided = false;
    
    if(_materialId.has_value()) {
        outBatch->textureIndex = materialIds.at(_materialId.value());
        BuildModelMaterial &material = materials[outBatch->textureIndex];
        if(material.is_texture_animated()) {
            flags |= 0x10000; // RENDER_TEX_ANIM
        }
        materialDoubleSided = material.is_texture_double_sided();
    } else {
        outBatch->textureIndex = 0xFF; // No texture
    }
    
    outBatch->flags = flags;
    
    bool useVertexColors = false;
    for(auto &vertex : _vertices) {
        vertex.write_to(outVertices);
        outVertices++; // Next out vertex.
        if(!vertex.is_color_white()) {
            useVertexColors = true;
        }
    }
    
    outBatch->lightSource = useVertexColors ? 0xFF : 0x00;
    
    uint8_t triFlags = materialDoubleSided ? 0x40 : 0x00;
    
    for(auto &tri : _triangles) {
        outTriangles->flags = triFlags; 
        outTriangles->vi0 = tri.a;
        outTriangles->vi1 = tri.b;
        outTriangles->vi2 = tri.c;
        outTriangles->uv0.u = tri.uv0.u;
        outTriangles->uv0.v = tri.uv0.v;
        outTriangles->uv1.u = tri.uv1.u;
        outTriangles->uv1.v = tri.uv1.v;
        outTriangles->uv2.u = tri.uv2.u;
        outTriangles->uv2.v = tri.uv2.v;
        outTriangles++; // next out triangle.
    }
}

std::optional<uint16_t> BuildModelBatch::_index_of_vertex(const BuildModelVertex& vertex) {
    int index = DataHelper::vector_index_of(_vertices, vertex);
    if(index == -1) {
        return std::nullopt;
    }
    return static_cast<uint16_t>(index);
}

uint16_t BuildModelBatch::_add_vertex(const BuildModelVertex& vertex) {
    _vertices.emplace_back(vertex);
    return static_cast<uint16_t>(_vertices.size()) - 1;
}
