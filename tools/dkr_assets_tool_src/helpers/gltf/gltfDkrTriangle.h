#pragma once

#include "fileTypes/triangle.hpp"

class GltfDkrTriangle {
public:
    uint16_t vi0, vi1, vi2;

    GltfDkrTriangle(DkrTriangle &tri);
    GltfDkrTriangle(uint16_t a, uint16_t b, uint16_t c);

    // Determine if another triangle is the backface of this one.
    bool is_backface(const GltfDkrTriangle &other);

    // Returns number of bytes written.
    int write_indices(uint16_t *indices);

    uint16_t get_minimum_index();
    uint16_t get_maximum_index();

    static size_t get_size();
};