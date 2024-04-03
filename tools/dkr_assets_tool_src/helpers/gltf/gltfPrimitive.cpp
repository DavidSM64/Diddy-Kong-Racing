#include "gltfPrimitive.h"

GltfPrimitive::GltfPrimitive(DkrVertex *vertices, DkrTriangle *triangles, size_t numTris, TextureHeader *texture, int materialIndex) {
    int texW = 0;
    int texH = 0;
    if(texture != nullptr) {
        texW = texture->width;
        texH = texture->height;
    }
    
    _materialIndex = materialIndex;
    
    for(size_t i = 0; i < numTris; i++) {
        DkrTriangle *tri = &triangles[i];
        
        int index0 = _get_or_set_index(&vertices[tri->vi0], &tri->uv0, texW, texH);
        int index1 = _get_or_set_index(&vertices[tri->vi1], &tri->uv1, texW, texH);
        int index2 = _get_or_set_index(&vertices[tri->vi2], &tri->uv2, texW, texH);
        
        _triangles.push_back(new GltfDkrTriangle(index0, index1, index2));
        
        if(tri->flags & 0x40) { // Draw backface
            _triangles.push_back(new GltfDkrTriangle(index0, index2, index1));
        }
    }
}

GltfPrimitive::~GltfPrimitive() {
    // _triangles and _vertices should be deleted automatically from std::vector's deconstructor.
}

int GltfPrimitive::_get_or_set_index(DkrVertex *vertex, DkrTexCoords *uv, int texWidth, int texHeight) {
    GltfDkrVertex *newVertex = new GltfDkrVertex(vertex, uv, texWidth, texHeight);
    int i = 0;
    while(i < (int)_vertices.size()) {
        if(newVertex == _vertices[i]) {
            // Found vertex.
            delete newVertex; // Was not needed.
            return i;
        }
        i++;
    }
    _vertices.push_back(newVertex);
    return i;
}

