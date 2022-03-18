#include "textures.h"

std::string get_texture_format_string(int format) {
    switch(format) {
        case TEX_FORMAT_RGBA32: return "RGBA32";
        case TEX_FORMAT_RGBA16: return "RGBA16";
        case TEX_FORMAT_I8:     return "I8";
        case TEX_FORMAT_I4:     return "I4";
        case TEX_FORMAT_IA16:   return "IA16";
        case TEX_FORMAT_IA8:    return "IA8";
        case TEX_FORMAT_IA4:    return "IA4";
        case TEX_FORMAT_CI4:    return "CI4";
        case TEX_FORMAT_CI8:    return "CI8";
    }
    throw 1;
}

int get_texture_format_from_string(std::string format) {
    if(format == "RGBA32") return TEX_FORMAT_RGBA32;
    if(format == "RGBA16") return TEX_FORMAT_RGBA16;
    if(format == "I8")     return TEX_FORMAT_I8;
    if(format == "I4")     return TEX_FORMAT_I4;
    if(format == "IA16")   return TEX_FORMAT_IA16;
    if(format == "IA8")    return TEX_FORMAT_IA8;
    if(format == "IA4")    return TEX_FORMAT_IA4;
    if(format == "CI4")    return TEX_FORMAT_CI4;
    if(format == "CI8")    return TEX_FORMAT_CI8;
    throw 1;
}

void deinterlace(std::vector<uint8_t>& texData, int texDataOffset, int width, int height, int bitDepth, int bufferSize) {
    uint8_t* temp = new uint8_t[bufferSize];
    
    int numPixels;
    if(bitDepth == 4) {
        numPixels = ((width * height) / 2);
    } else {
        numPixels = (width * height * (bitDepth / 8));
    }
    
    int stride = bufferSize * 2;
    
    int size = numPixels / stride;
    
    for(int i = 0; i < size; i++) {
        int row;
        if(bitDepth == 4) {
            row = (i * stride) / width * 2;
        } else {
            row = (i * stride) / width / (bitDepth / 8);
        }
        if(row % 2 == 0) continue;
        for(int j = 0; j < bufferSize; j++) {
            temp[j] = texData[texDataOffset + (i * stride + j)];
            texData[texDataOffset + (i * stride + j)] = texData[texDataOffset + (i * stride + j + bufferSize)];
            texData[texDataOffset + (i * stride + j + bufferSize)] = temp[j];
        }
    }
    
    delete[] temp;
}

void flip_texture_vertically(std::vector<uint8_t> &data, int dataOffset, int width, int height, int format) {
    // Convert width into number of bytes per line.
    switch(format) {
        case TEX_FORMAT_I4:
        case TEX_FORMAT_IA4:
        case TEX_FORMAT_CI4:
            width /= 2; // 2 pixels per byte
            break;
        case TEX_FORMAT_RGBA16:
        case TEX_FORMAT_IA16:
            width *= 2; // 2 bytes per pixel
            break;
        case TEX_FORMAT_RGBA32:
            width *= 4; // 4 bytes per pixel
            break;
        // Don't need to do anything for the 8-bit formats.
    }
    
    for(int y = 0; y < height / 2; y++) {
        for(int x = 0; x < width; x++) {
            uint8_t temp = data[dataOffset + (y * width + x)];
            data[dataOffset + (y * width + x)] = data[dataOffset + ((height - y - 1) * width + x)];
            data[dataOffset + ((height - y - 1) * width + x)] = temp;
        }
    }
}

int get_texture_size(int width, int height, int format) {
    switch(format) {
        case TEX_FORMAT_RGBA32:
            return (width * height * 4) + TEX_HEADER_SIZE;
        case TEX_FORMAT_RGBA16:
        case TEX_FORMAT_IA16:
            return (width * height * 2) + TEX_HEADER_SIZE;
        case TEX_FORMAT_I8:
        case TEX_FORMAT_IA8:
            return (width * height) + TEX_HEADER_SIZE;
        case TEX_FORMAT_I4:
        case TEX_FORMAT_IA4:
            return (width * height / 2) + TEX_HEADER_SIZE;
        case TEX_FORMAT_CI4:
        case TEX_FORMAT_CI8:
            std::cout << "Error: CI texture formats are not currently supported." << std::endl;
            throw 1;
    }
    
    std::cout << "Error: Invalid texture format " << format << std::endl;
    throw 1;
}

std::vector<uint8_t> load_texture_from_png(std::string filepath, int textureFormat, int *width, int *height) {
    switch(textureFormat) {
        case TEX_FORMAT_RGBA32:
        case TEX_FORMAT_RGBA16:
        {
            uint8_t* data = (uint8_t*)png2rgba(filepath.c_str(), width, height);
            std::vector<uint8_t> vec(data, data + ((*width) * (*height) * 4));
            free(data);
            return vec;
        }
        case TEX_FORMAT_I8:
        case TEX_FORMAT_I4:
        case TEX_FORMAT_IA16:
        case TEX_FORMAT_IA8:
        case TEX_FORMAT_IA4:
        {
            uint8_t* data = (uint8_t*)png2ia(filepath.c_str(), width, height);
            std::vector<uint8_t> vec(data, data + ((*width) * (*height) * 2));
            free(data);
            return vec;
        }
        case TEX_FORMAT_CI4:
            std::cout << "Error: CI4 is currently not supported." << std::endl;
            throw 1;
        default:
            std::cout << "Error: Invalid texture type: " << textureFormat << std::endl;
            throw 1;
    }
}
