#include "gltfDkrTriangle.h"

using namespace DkrAssetsTool;

#include <algorithm>

GltfDkrTriangle::GltfDkrTriangle(DkrTriangle &tri) {
    vi0 = tri.vi0;
    vi1 = tri.vi1;
    vi2 = tri.vi2;
}

GltfDkrTriangle::GltfDkrTriangle(uint16_t a, uint16_t b, uint16_t c) {
    vi0 = a;
    vi1 = b;
    vi2 = c;
}

// Determine if another triangle is the backface of this one.
bool GltfDkrTriangle::is_backface(const GltfDkrTriangle &other) {
    return this->vi0 == other.vi0 && this->vi1 == other.vi2 && this->vi2 == other.vi1;
}

// Returns number of bytes written.
int GltfDkrTriangle::write_indices(uint16_t *indices) {
    indices[0] = vi0;
    indices[1] = vi1;
    indices[2] = vi2;
    return get_size();
}

uint16_t GltfDkrTriangle::get_minimum_index() {
    return std::min<int>(vi0, std::min<int>(vi1, vi2));
}

uint16_t GltfDkrTriangle::get_maximum_index() {
    return std::max<int>(vi0, std::max<int>(vi1, vi2));
}

size_t GltfDkrTriangle::get_size() {
    return sizeof(uint16_t) * 3;
}