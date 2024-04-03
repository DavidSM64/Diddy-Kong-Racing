#pragma once

#include "types.hpp"
#include "texCoords.hpp"

/* Size: 0x10 bytes */
typedef struct DkrTriangle {
/* 0x00 */ uint8_t flags; // 0x40 = Draw backface, 0x00 = Cull backface
/* 0x01 */ uint8_t vi0;   // First vertex index
/* 0x02 */ uint8_t vi1;   // Second vertex index
/* 0x03 */ uint8_t vi2;   // Third vertex index
/* 0x04 */ DkrTexCoords uv0; // Texture coordinates for the first vertex
/* 0x08 */ DkrTexCoords uv1; // Texture coordinates for the second vertex
/* 0x0C */ DkrTexCoords uv2; // Texture coordinates for the third vertex
} DkrTriangle;
