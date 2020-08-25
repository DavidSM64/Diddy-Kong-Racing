#include "extract_textures.h"

ExtractTextures::ExtractTextures(std::vector<uint8_t> data, ROM& rom, std::string outFilepath) 
: Extract(data, rom, outFilepath) {
    std::vector<uint8_t> header(data.begin(), data.begin() + TEX_HEADER_SIZE);
    std::vector<uint8_t> texData;
    
    bool isCompressed = (header[0x1D] == 0x01);
    
    if(isCompressed) {
        std::vector<uint8_t> compressedData(data.begin() + TEX_HEADER_SIZE, data.end());
        // Needed padding to prevent errors with decompressing.
        if(compressedData[compressedData.size() - 1] != 0) {
            compressedData.push_back(0);
            compressedData.push_back(0);
            compressedData.push_back(0);
            compressedData.push_back(0);
        }
        DKRCompression compression;
        texData = compression.decompressBuffer(compressedData);
    } else {
        texData = data;
    }
    
    int numTextures = header[0x12];
    int dataOffset = 0;
    
    std::vector<uint8_t> combinedTexturesData;
    
    int totalHeight = 0;
    for(int i = 0; i < numTextures; i++){
        int width = texData[dataOffset + 0x00];
        int height = texData[dataOffset + 0x01];
        int textureFormat = texData[dataOffset + 0x02] & 0xF;
        int textureSize = get_texture_size(width, height, textureFormat);
        
        std::vector<uint8_t> texHeader(texData.begin() + dataOffset, texData.begin() + dataOffset + TEX_HEADER_SIZE);
        std::vector<uint8_t> texData(texData.begin() + dataOffset + TEX_HEADER_SIZE, texData.begin() + dataOffset + textureSize);
        
        process_texture(texHeader, texData);
        combinedTexturesData.insert(combinedTexturesData.end(), texData.begin(), texData.end());
        
        dataOffset += textureSize;
        totalHeight += texHeader[1];
    }
    
    int width = header[0];
    int height = totalHeight;
    int textureFormat = header[0x02] & 0xF;
    
    switch(textureFormat) {
        case TEX_FORMAT_RGBA32:
        {
            rgba2png(outFilepath.c_str(), (const rgba*)&combinedTexturesData[0], width, height);
            break;
        }
        case TEX_FORMAT_RGBA16:
        {
            rgba* outTex = raw2rgba(&combinedTexturesData[0], width, height, 16);
            rgba2png(outFilepath.c_str(), outTex, width, height);
            break;
        }
        case TEX_FORMAT_I8:
        {
            ia* outTex = raw2i(&combinedTexturesData[0], width, height, 8);
            ia2png(outFilepath.c_str(), outTex, width, height);
            break;
        }
        case TEX_FORMAT_I4:
        {
            ia* outTex = raw2i(&combinedTexturesData[0], width, height, 4);
            ia2png(outFilepath.c_str(), outTex, width, height);
            break;
        }
        case TEX_FORMAT_IA16:
        {
            ia* outTex = raw2ia(&combinedTexturesData[0], width, height, 16);
            ia2png(outFilepath.c_str(), outTex, width, height);
            break;
        }
        case TEX_FORMAT_IA8:
        {
            ia* outTex = raw2ia(&combinedTexturesData[0], width, height, 8);
            ia2png(outFilepath.c_str(), outTex, width, height);
            break;
        }
        case TEX_FORMAT_IA4:
        {
            ia* outTex = raw2ia(&combinedTexturesData[0], width, height, 4);
            ia2png(outFilepath.c_str(), outTex, width, height);
            break;
        }
        case TEX_FORMAT_CI4:
        {
            std::cout << "Error: CI4 texture format is not currently supported." << std::endl;
            throw 1;
        }
        default: // Invalid texture format
        {
            std::cout << "Error: Unknown texture format " << textureFormat << std::endl;
            throw 1;
        }
    }
    
    write_binary_file(header, outFilepath + ".header");
    
    print_extracted(outFilepath);
}

ExtractTextures::~ExtractTextures(){
}

void ExtractTextures::deinterlace(std::vector<uint8_t>& data, int width, int height, int bitDepth, int bufferSize) {
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
            temp[j] = data[i * stride + j];
            data[i * stride + j] = data[i * stride + j + bufferSize];
            data[i * stride + j + bufferSize] = temp[j];
        }
    }
    
    delete[] temp;
}

void ExtractTextures::process_texture(std::vector<uint8_t>& header, std::vector<uint8_t>& data) {
    int width = header[0];
    int height = header[1];
    int textureFormat = header[0x02] & 0xF;
    bool isInterlaced = ((header[0x06] & 0x04) == 0x04);
    
    switch(textureFormat) {
        case TEX_FORMAT_RGBA32:
        {
            if(isInterlaced) deinterlace(data, width, height, 32, 8);
            break;
        }
        case TEX_FORMAT_RGBA16:
        case TEX_FORMAT_IA16:
        {
            if(isInterlaced) deinterlace(data, width, height, 16, 4);
            break;
        }
        case TEX_FORMAT_I8:
        case TEX_FORMAT_IA8:
        {
            if(isInterlaced) deinterlace(data, width, height, 8, 4);
            break;
        }
        case TEX_FORMAT_I4:
        case TEX_FORMAT_IA4:
        {
            if(isInterlaced) deinterlace(data, width, height, 4, 4);
            break;
        }
    }
}

int ExtractTextures::get_texture_size(int width, int height, int textureFormat) {
    switch(textureFormat) {
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
            std::cout << "Error: CI4 texture format is not currently supported." << std::endl;
            throw 1;
    }
    
    std::cout << "Error: Invalid texture format " << textureFormat << std::endl;
    throw 1;
}
