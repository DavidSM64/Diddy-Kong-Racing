#pragma once

#include "types.hpp"

#include <vector>
#include <string>
#include <sstream>

const std::vector<std::string> RENDER_FLAGS = {
    "FLAG_ANTI_ALIASING",
    "FLAG_Z_COMPARE",
    "FLAG_SEMI_TRANSPARENT",
    "FLAG_FOG_ACTIVE",
    "FLAG_CUTOUT",
    "FLAG_COLOUR_INDEX",
    "FLAG_CLAMP_X",
    "FLAG_CLAMP_Y",
    "FLAG_Z_UPDATE",
    "FLAG_PRESERVE_COVERAGE",
    "FLAG_LINE_SWAP",
    "FLAG_DECAL",
    "FLAG_12",
    "FLAG_WATER",
    "FLAG_FORCE_NO_SHADOWS", 
    "FLAG_ENVMAP", 
    "FLAG_TEXTURE_ANIM",
    "FLAG_17",
    "FLAG_PULSATING_LIGHTS",
    "FLAG_19",
    "FLAG_20",
    "FLAG_21",
    "FLAG_22",
    "FLAG_23",
    "FLAG_24",
    "FLAG_25",
    "FLAG_26",
    "FLAG_VTX_ALPHA",
    "FLAG_28",
    "FLAG_29",
    "FLAG_30",
    "FLAG_31"
};


/* Size: 12 bytes */
struct DkrBatch {
    uint8_t textureIndex; // 0xFF = No texture
    int8_t unk1; // Local vertex count. Is zero if flag 0x400000 is set, or flags == 0x100.
    be_int16_t verticesOffset;
    be_int16_t trianglesOffset;
    uint8_t lightSource; // 0xFF = vertex colors, otherwise use dynamic lighting normals (Objects only)
    uint8_t unk7; // Texture offset? Always zero in rom?
    be_uint32_t flags; // render flags
    
    std::string to_string() {
        std::stringstream ss;
        
        ss << std::hex;
        ss << "{ tex:" << (int)textureIndex;
        ss << ", unk1: " << (int)unk1;
        ss << ", verts: " << (int)verticesOffset;
        ss << ", tris: " << (int)trianglesOffset;
        ss << ", light: " << ((lightSource == 0xFF) ? "vertex colors" : "normals");
        ss << ", unk7: " << (int)unk7;
        ss << ", flags: " << flags;
        ss << " }";
        
        return ss.str();
    }
};
