#include "gltfDkrVertex.h"

using namespace DkrAssetsTool;

GltfDkrVertex::GltfDkrVertex(DkrVertex *vertex, DkrTexCoords *uv, int texWidth, int texHeight){
    x = (float)vertex->x * MODEL_SCALE_GLTF;
    y = (float)vertex->y * MODEL_SCALE_GLTF;
    z = (float)vertex->z * MODEL_SCALE_GLTF;
    r = (float)vertex->r / 255.0f;
    g = (float)vertex->g / 255.0f;
    b = (float)vertex->b / 255.0f;
    a = (float)vertex->a / 255.0f;
    if (uv == nullptr || texWidth == 0 || texHeight == 0) {
        u = 0;
        v = 0;
        return;
    }
    u = ((float)uv->u / 32.0f) / (float)texWidth;
    v = ((float)uv->v / 32.0f) / (float)texHeight;
}

GltfDkrVertex::GltfDkrVertex(int16_t xPos, int16_t yPos, int16_t zPos, 
        uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha,
        int16_t uOffset, int16_t vOffset, int texWidth, int texHeight) {
    x = (float)xPos * MODEL_SCALE_GLTF;
    y = (float)yPos * MODEL_SCALE_GLTF;
    z = (float)zPos * MODEL_SCALE_GLTF;
    r = (float)red / 255.0f;
    g = (float)green / 255.0f;
    b = (float)blue / 255.0f;
    a = (float)alpha / 255.0f;
    if(texWidth == 0 || texHeight == 0) {
        u = 0;
        v = 0;
        return;
    }
    u = ((float)uOffset / 32.0f) / (float)texWidth;
    v = ((float)vOffset / 32.0f) / (float)texHeight;
}

GltfDkrVertex::GltfDkrVertex(float xPos, float yPos, float zPos, 
    float red, float green, float blue, float alpha, float uOffset, float vOffset) {
    x = xPos * MODEL_SCALE_GLTF_INVERSE;
    y = yPos * MODEL_SCALE_GLTF_INVERSE;
    z = zPos * MODEL_SCALE_GLTF_INVERSE;
    r = red;
    g = green;
    b = blue;
    a = alpha;
    u = uOffset;
    v = vOffset;
}

bool GltfDkrVertex::operator==(const GltfDkrVertex& other){
    return x == other.x && y == other.y && z == other.z && 
           r == other.r && g == other.g && b == other.b && a == other.a &&
           u == other.u && v == other.v;
}

// Returns number of bytes written.
int GltfDkrVertex::write_position(float *positions) {
    positions[0] = x;
    positions[1] = y;
    positions[2] = z;
    return get_positions_size();
}

// Returns number of bytes written.
int GltfDkrVertex::write_color(float *colors) {
    colors[0] = r;
    colors[1] = g;
    colors[2] = b;
    colors[3] = a;
    return get_colors_size();
}

// Returns number of bytes written.
int GltfDkrVertex::write_uv(float *uvs) {
    uvs[0] = u;
    uvs[1] = v;
    return get_uv_size();
}

size_t GltfDkrVertex::get_positions_size() {
    return sizeof(float) * 3;
}

size_t GltfDkrVertex::get_colors_size() {
    return sizeof(float) * 4;
}

size_t GltfDkrVertex::get_uv_size() {
    return sizeof(float) * 2;
}

size_t GltfDkrVertex::get_size() {
    return get_positions_size() + get_colors_size() + get_uv_size();
}
