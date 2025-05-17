#pragma once

#include <string>
#include <sstream>
#include "types.hpp"

struct DkrTextureInfo {
    /* 0x00 */ be_int32_t id;
    /* 0x04 */ uint8_t width;
    /* 0x05 */ uint8_t height;
    /* 0x06 */ uint8_t format; // upper 4 bits = render mode/textype, lower 4 bits = texture format.
    /* 0x07 */ uint8_t surfaceType; // enum SurfaceType for levels, not sure what this does for object models.

    std::string to_string() {
        std::stringstream ss;

        ss << std::hex;
        ss << "{ tex:" << (int)id;
        ss << ", width: " << (int)width;
        ss << ", height: " << (int)height;
        ss << ", format: " << (int)format;
        ss << ", byte7: " << (int)surfaceType;
        ss << " }";

        return ss.str();
    }

    bool operator==(const DkrTextureInfo& other) {
        return (id == other.id) && (width == other.width) && (height == other.height) && 
            (format == other.format) && (surfaceType == other.surfaceType);
    }

};
