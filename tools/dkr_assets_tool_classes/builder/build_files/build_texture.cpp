#include "build_texture.h"

#define SET_BOOL_FLAG(flagName, flagVal) \
    flags |= get_bool_from_json(srcPath, "flags", flagName) ? flagVal : 0
#define SET_STRING_FLAG(flagName, strVal, flagVal) \
    flags |= get_string_from_json(srcPath, "flags", flagName) == strVal ? flagVal : 0

int get_png_data_size(int width, int height, int format) {
    switch(format) {
        case TEX_FORMAT_I8:
        case TEX_FORMAT_I4:
        case TEX_FORMAT_IA16:
        case TEX_FORMAT_IA8:
        case TEX_FORMAT_IA4:
            return (width * height * 2);
        default:
            return (width * height * 4);
    }
}
    
int get_png_offset(int i, int width, int height, int format) {
    return get_png_data_size(width, height, format) * i;
}

BuildTexture::BuildTexture(std::string srcPath, std::string dstPath) {
    std::string directory = get_directory_from_full_path(srcPath);
    std::string imgPath = directory + "/" + get_string_from_json(srcPath, "img");
    
    bool isCompressed = get_bool_from_json(srcPath, "compressed");
    bool flipTexture = get_bool_from_json(srcPath, "flipped-image");
    bool interlaced = get_bool_from_json(srcPath, "flags", "interlaced");
    
    int width = get_int_from_json(srcPath, "width");
    int height = get_int_from_json(srcPath, "height");
    std::string formatString = get_string_from_json(srcPath, "format");
    int format = get_texture_format_from_string(formatString);
    int texType = get_int_from_json(srcPath, "tex-type");

    int spriteX = json_has_key(srcPath, "sprite-x") ? get_int_from_json(srcPath, "sprite-x") : 0; 
    int spriteY = json_has_key(srcPath, "sprite-y") ? get_int_from_json(srcPath, "sprite-y") : 0; 

    bool writeSize = get_bool_from_json(srcPath, "write-size");
    
    // TODO: Figure out all the flags
    int flags = 0;
    SET_BOOL_FLAG("flag-01", 0x0001);
    SET_BOOL_FLAG("flag-04", 0x0004);
    SET_BOOL_FLAG("flag-10", 0x0010);
    SET_STRING_FLAG("wrap-s", "Clamp", 0x0040);
    SET_STRING_FLAG("wrap-t", "Clamp", 0x0080);
    SET_BOOL_FLAG("interlaced", 0x0400);
    
    int textureSize = get_texture_size(width, height, format);
    
    int numberOfTextures = get_int_from_json(srcPath, "frame-count");

    int frameAdvance = json_has_key(srcPath, "frame-advance-delay") ? get_int_from_json(srcPath, "frame-advance-delay") : 0; 
    
    std::vector<uint8_t> uncompressed(textureSize * numberOfTextures);
    
    int pngWidth, pngHeight;
    std::vector<uint8_t> pngData = load_texture_from_png(imgPath, format, &pngWidth, &pngHeight);
    
    for(int i = 0; i < numberOfTextures; i++) {
        int off = i * textureSize;
        int pngOff = get_png_offset(i, width, height, format);
        
        // Texture Header
        uncompressed[off] = width;
        uncompressed[off + 0x01] = height;
        uncompressed[off + 0x02] = (texType << 4) | format;
        uncompressed[off + 0x03] = spriteX;
        uncompressed[off + 0x04] = spriteY;
        uncompressed[off + 0x05] = 1; // Number of instances. Always 1 in the ROM.
        write_big_endian_halfword(uncompressed, off + 0x06, flags);
        uncompressed[off + 0x12] = numberOfTextures;
        write_big_endian_halfword(uncompressed, off + 0x14, frameAdvance);
        if(writeSize) {
            write_big_endian_halfword(uncompressed, off + 0x16, align16(textureSize));
        } else {
            uncompressed[off + 0x1D] = 0x01;
        }
        
        // Subsection of pngData
        std::vector<uint8_t> rgbaData(pngData.begin() + pngOff, pngData.begin() + pngOff + get_png_data_size(width, height, format));
        
        write_texture_data(uncompressed, off + TEX_HEADER_SIZE, rgbaData, width, height, format, interlaced, flipTexture);
    }
    
    if(!writeSize) {
        while(uncompressed.size() % 16 != 0) {
            uncompressed.push_back(0);
        }
    }

    // isCompressed = false; // Uncomment to help with debugging.

    if(isCompressed) {
        std::vector<uint8_t> compressedHeader;
        compressedHeader.insert(compressedHeader.end(), uncompressed.begin(), uncompressed.begin() + TEX_HEADER_SIZE);
        
        compressedHeader[0x1D] = 0x01;
    
        DKRCompression compression;
        std::vector<uint8_t> compressed = compression.compressBuffer(uncompressed);
        
        // Note: uncompressed is garbled at this point.
        
        compressed.insert(compressed.begin(), compressedHeader.begin(), compressedHeader.end());
        
        write_binary_file(compressed, dstPath);
    } else {
        write_binary_file(uncompressed, dstPath);
    }
    
    //write_binary_file(out, dstPath);
}

BuildTexture::~BuildTexture() {
    
}

void BuildTexture::write_texture_data(std::vector<uint8_t> &out, int outOffset, std::vector<uint8_t> &rgbaData, 
    int width, int height, int format, bool interlace, bool flipTexture) {
    if(flipTexture) {
        switch(format) {
            case TEX_FORMAT_I8:
            case TEX_FORMAT_I4:
            case TEX_FORMAT_IA16:
            case TEX_FORMAT_IA8:
            case TEX_FORMAT_IA4:
                flip_texture_vertically(rgbaData, 0, width, height, TEX_FORMAT_IA16);
                break;
            default:
                flip_texture_vertically(rgbaData, 0, width, height, TEX_FORMAT_RGBA32);
                break;
        }
    }
    switch(format) {
        case TEX_FORMAT_RGBA32:
        {
            if (interlace) {
                deinterlace(rgbaData, 0, width, height, 32, 8);
            }
            std::copy(rgbaData.begin(), rgbaData.end(), out.begin() + outOffset);
            break;
        }
        case TEX_FORMAT_RGBA16:
        {
            uint8_t* rgba16Data = (uint8_t*)malloc(width * height * 2);
            rgba2raw(rgba16Data, (const rgba*)&rgbaData[0], width, height, 16);
            std::vector<uint8_t> rgba16(rgba16Data, rgba16Data + (width * height * 2));
            if (interlace) {
                deinterlace(rgba16, 0, width, height, 16, 4);
            }
            std::copy(rgba16.begin(), rgba16.end(), out.begin() + outOffset);
            break;
        }
        case TEX_FORMAT_I8:
        {
            uint8_t* i8Data = (uint8_t*)malloc(width * height);
            i2raw(i8Data, (const ia*)&rgbaData[0], width, height, 8);
            std::vector<uint8_t> i8(i8Data, i8Data + (width * height));
            if (interlace) {
                deinterlace(i8, 0, width, height, 8, 4);
            }
            std::copy(i8.begin(), i8.end(), out.begin() + outOffset);
            break;
        }
        case TEX_FORMAT_I4:
        {
            uint8_t* i4Data = (uint8_t*)malloc(width * height / 2);
            i2raw(i4Data, (const ia*)&rgbaData[0], width, height, 4);
            std::vector<uint8_t> i4(i4Data, i4Data + (width * height / 2));
            if (interlace) {
                deinterlace(i4, 0, width, height, 4, 4);
            }
            std::copy(i4.begin(), i4.end(), out.begin() + outOffset);
            break;
        }
        case TEX_FORMAT_IA16:
        {
            uint8_t* ia16Data = (uint8_t*)malloc(width * height * 2);
            ia2raw(ia16Data, (const ia*)&rgbaData[0], width, height, 16);
            std::vector<uint8_t> ia16(ia16Data, ia16Data + (width * height * 2));
            if (interlace) {
                deinterlace(ia16, 0, width, height, 16, 4);
            }
            std::copy(ia16.begin(), ia16.end(), out.begin() + outOffset);
            break;
        }
        case TEX_FORMAT_IA8:
        {
            uint8_t* ia8Data = (uint8_t*)malloc(width * height);
            ia2raw(ia8Data, (const ia*)&rgbaData[0], width, height, 8);
            std::vector<uint8_t> ia8(ia8Data, ia8Data + (width * height));
            if (interlace) {
                deinterlace(ia8, 0, width, height, 8, 4);
            }
            std::copy(ia8.begin(), ia8.end(), out.begin() + outOffset);
            break;
        }
        case TEX_FORMAT_IA4:
        {
            uint8_t* ia4Data = (uint8_t*)malloc(width * height / 2);
            ia2raw(ia4Data, (const ia*)&rgbaData[0], width, height, 4);
            std::vector<uint8_t> ia4(ia4Data, ia4Data + (width * height / 2));
            if (interlace) {
                deinterlace(ia4, 0, width, height, 4, 4);
            }
            std::copy(ia4.begin(), ia4.end(), out.begin() + outOffset);
            break;
        }
        case TEX_FORMAT_CI4:
        case TEX_FORMAT_CI8:
        {
            display_error_and_abort("CI4/CI8 texture formats are not currently supported.");
        }
    }
}

