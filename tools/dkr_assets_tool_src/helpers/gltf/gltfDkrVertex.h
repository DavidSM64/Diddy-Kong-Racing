#pragma once

#include "fileTypes/vertex.hpp"
#include "fileTypes/texCoords.hpp"

namespace DkrAssetsTool {
    
// TODO: Move this into a singleton class.
#define MODEL_SCALE_GLTF (1.0f / 1000.0f)
#define MODEL_SCALE_GLTF_INVERSE (1.0f / MODEL_SCALE_GLTF)

// Class used for converting DKR's vertex information to the glTF format.
class GltfDkrVertex {
public:
    float x, y, z;
    float r, g, b, a;
    float u, v;

    GltfDkrVertex(DkrVertex *vertex, DkrTexCoords *uv=nullptr, int texWidth=0, int texHeight=0);
    GltfDkrVertex(int16_t xPos, int16_t yPos, int16_t zPos, 
        uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255, uint8_t alpha = 255,
        int16_t uOffset = 0, int16_t vOffset = 0, int texWidth = 0, int texHeight = 0);
    GltfDkrVertex(float xPos, float yPos, float zPos, 
        float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f,
        float uOffset = 0, float vOffset = 0);

    bool operator==(const GltfDkrVertex& other);
    bool equals(DkrVertex *vertex, DkrTexCoords *uv=nullptr, int texWidth=0, int texHeight=0);

    int write_position(float *positions); // Returns number of bytes written.
    int write_color(float *colors); // Returns number of bytes written.
    int write_uv(float *uvs); // Returns number of bytes written.

    static size_t get_positions_size();

    static size_t get_colors_size();

    static size_t get_uv_size();

    static size_t get_size();
};

}