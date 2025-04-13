#pragma once


#include <vector>

#include "gltfDkrVertex.h"
#include "gltfDkrTriangle.h"
#include "fileTypes/texture.hpp"

namespace DkrAssetsTool {

class GltfPrimitive {
public:
    GltfPrimitive(DkrVertex *vertices, DkrTriangle *triangles, size_t numTris, TextureHeader *texture, int materialIndex);
    ~GltfPrimitive();
private:
    std::vector<GltfDkrTriangle*> _triangles;
    std::vector<GltfDkrVertex*> _vertices;
    int _materialIndex;
    
    int _get_or_set_index(DkrVertex *vertex, DkrTexCoords *uv, int texWidth, int texHeight);
};

}