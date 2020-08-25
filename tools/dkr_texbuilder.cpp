#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <tuple>
#include "dkr_decompressor_src/DKRCompression.h"
#include "n64graphics/n64graphics.h"

#define TEX_FORMAT_RGBA32 0
#define TEX_FORMAT_RGBA16 1
#define TEX_FORMAT_I8     2
#define TEX_FORMAT_I4     3
#define TEX_FORMAT_IA16   4
#define TEX_FORMAT_IA8    5
#define TEX_FORMAT_IA4    6
#define TEX_FORMAT_CI4    7

#define TEX_HEADER_SIZE 0x20

const std::string PNG_EXTENSION = ".png";

/*********************************************/

void show_help() {
    std::cout << "Usage: ./dkr_texbuilder <input_png_file> <output_compressed_file>" << std::endl;
}

bool starts_with(std::string filename, std::string pattern) {
    return std::equal(pattern.begin(), pattern.end(), filename.begin());
}

void write_binary_file(std::vector<uint8_t>& data, std::string& filename) {
    std::ofstream wf(filename.c_str(), std::ios::out | std::ios::binary);
    for(int i = 0; i < data.size(); i++)
        wf.write((char *)&data[i], 1);
    wf.close();
}

void to_lowercase(std::string& input) {
    for(char& character : input) {
        character = std::tolower(character);
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(std::move(item));
    }
    return elems;
}

std::vector<uint8_t> read_binary(std::string filename) {
    std::vector<uint8_t> bytes;
    std::ifstream is;
    is.open(filename.c_str(), std::ios::binary);
    is.seekg(0, std::ios::end);
    size_t filesize = is.tellg();
    is.seekg(0, std::ios::beg);
    bytes.resize(filesize);
    is.read((char *)bytes.data(), filesize);
    is.close();
    return bytes;
}

/*********************************************/


void deinterlace(std::vector<uint8_t>& data, int width, int height, int bitDepth, int bufferSize) {
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

std::vector<uint8_t> load_texture_from_png(std::string filepath, int textureFormat, int* width, int* height) {
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

#define ALIGN16(val) ((val) + 15) & 0xFFFFFFF0  

int get_texture_size(int width, int height, int textureFormat) {
    switch(textureFormat) {
        case TEX_FORMAT_RGBA32:
            return ALIGN16((width * height * 4) + TEX_HEADER_SIZE);
        case TEX_FORMAT_RGBA16:
        case TEX_FORMAT_IA16:
            return ALIGN16((width * height * 2) + TEX_HEADER_SIZE);
        case TEX_FORMAT_I8:
        case TEX_FORMAT_IA8:
            return ALIGN16((width * height) + TEX_HEADER_SIZE);
        case TEX_FORMAT_I4:
        case TEX_FORMAT_IA4:
            return ALIGN16((width * height / 2) + TEX_HEADER_SIZE);
        case TEX_FORMAT_CI4:
            std::cout << "Error: CI4 texture format is not currently supported." << std::endl;
            throw 1;
    }
    
    std::cout << "Error: Invalid texture format " << textureFormat << std::endl;
    throw 1;
}

int get_bitdepth_from_format(int textureFormat){
    switch(textureFormat) {
        case TEX_FORMAT_RGBA32: 
            return 32;
        case TEX_FORMAT_RGBA16: 
        case TEX_FORMAT_IA16: 
            return 16;
        case TEX_FORMAT_I8: 
        case TEX_FORMAT_IA8: 
            return 8;
        case TEX_FORMAT_I4: 
        case TEX_FORMAT_IA4: 
        case TEX_FORMAT_CI4: 
            return 4;
    }
    std::cout << "Error: Invalid texture format " << textureFormat << std::endl;
    throw 1;
}

std::vector<uint8_t> get_texture_data(std::vector<uint8_t> pngData, std::vector<uint8_t> &header, bool forceAlignment) {
    std::vector<uint8_t> outData;
    
    outData.insert(outData.end(), header.begin(), header.begin() + TEX_HEADER_SIZE);
    bool interlace = ((outData[0x06] & 0x4) == 0x04);
    
    int width = outData[0x00];
    int height = outData[0x01];
    int textureFormat = outData[0x02] & 0x0F;
    
    switch(textureFormat) {
        case TEX_FORMAT_RGBA32:
        {
            if (interlace) {
                deinterlace(pngData, width, height, 32, 8);
            }
            outData.insert(outData.end(), pngData.begin(), pngData.end());
            break;
        }
        case TEX_FORMAT_RGBA16:
        {
            uint8_t* rgba16Data = (uint8_t*)malloc(width * height * 2);
            rgba2raw(rgba16Data, (const rgba*)&pngData[0], width, height, 16);
            std::vector<uint8_t> rgba16(rgba16Data, rgba16Data + (width * height * 2));
            free(rgba16Data);
            if (interlace) {
                deinterlace(rgba16, width, height, 16, 4);
            }
            outData.insert(outData.end(), rgba16.begin(), rgba16.end());
            break;
        }
        case TEX_FORMAT_I8:
        {
            uint8_t* i8Data = (uint8_t*)malloc(width * height);
            i2raw(i8Data, (const ia*)&pngData[0], width, height, 8);
            std::vector<uint8_t> i8(i8Data, i8Data + (width * height));
            free(i8Data);
            if (interlace) {
                deinterlace(i8, width, height, 8, 4);
            }
            outData.insert(outData.end(), i8.begin(), i8.end());
            break;
        }
        case TEX_FORMAT_I4:
        {
            uint8_t* i4Data = (uint8_t*)malloc(width * height / 2);
            i2raw(i4Data, (const ia*)&pngData[0], width, height, 4);
            std::vector<uint8_t> i4(i4Data, i4Data + (width * height / 2));
            free(i4Data);
            if (interlace) {
                deinterlace(i4, width, height, 4, 4);
            }
            outData.insert(outData.end(), i4.begin(), i4.end());
            break;
        }
        case TEX_FORMAT_IA16:
        {
            uint8_t* ia16Data = (uint8_t*)malloc(width * height * 2);
            ia2raw(ia16Data, (const ia*)&pngData[0], width, height, 16);
            std::vector<uint8_t> ia16(ia16Data, ia16Data + (width * height * 2));
            free(ia16Data);
            if (interlace) {
                deinterlace(ia16, width, height, 16, 4);
            }
            outData.insert(outData.end(), ia16.begin(), ia16.end());
            break;
        }
        case TEX_FORMAT_IA8:
        {
            uint8_t* ia8Data = (uint8_t*)malloc(width * height);
            ia2raw(ia8Data, (const ia*)&pngData[0], width, height, 8);
            std::vector<uint8_t> ia8(ia8Data, ia8Data + (width * height));
            free(ia8Data);
            if (interlace) {
                deinterlace(ia8, width, height, 8, 4);
            }
            outData.insert(outData.end(), ia8.begin(), ia8.end());
            break;
        }
        case TEX_FORMAT_IA4:
        {
            uint8_t* ia4Data = (uint8_t*)malloc(width * height / 2);
            ia2raw(ia4Data, (const ia*)&pngData[0], width, height, 4);
            std::vector<uint8_t> ia4(ia4Data, ia4Data + (width * height / 2));
            free(ia4Data);
            if (interlace) {
                deinterlace(ia4, width, height, 4, 4);
            }
            outData.insert(outData.end(), ia4.begin(), ia4.end());
            break;
        }
    }
    
    if(forceAlignment) {
        while(outData.size() % 16 != 0) {
            outData.push_back(0);
        }
    }
    
    return outData;
}

std::vector<uint8_t> get_texture_binary(std::string inputFilepath, std::string inputHeaderFilepath, bool& isCompressed) {
    std::vector<uint8_t> out;
    
    std::vector<uint8_t> header = read_binary(inputHeaderFilepath);
    
    isCompressed = (header[0x1D] != 0x00);
    bool dontComputeSizeInHeader = (header[0x16] == 0x00 && header[0x17] == 0x00);
    
    if (!dontComputeSizeInHeader) {
        header[0x1D] = 0x00;
    }
    
    int textureFormat = header[0x02] & 0xF;
    int numTextures = header[0x12];
    
    int width, totalHeight;
    
    std::vector<uint8_t> combinedPngData = load_texture_from_png(inputFilepath, textureFormat, &width, &totalHeight);
    
    int height = totalHeight / numTextures;
    int pngSize;
    
    if(textureFormat == TEX_FORMAT_RGBA32 || textureFormat == TEX_FORMAT_RGBA16) {
        pngSize = width * height * 4;
    } else {
        pngSize = width * height * 2;
    }
    
    for(int i = 0; i < numTextures; i++) {
        int pngSectionStart = i * pngSize;
        int pngSectionEnd = (i + 1) * pngSize;
        std::vector<uint8_t> pngData(combinedPngData.begin() + pngSectionStart, combinedPngData.begin() + pngSectionEnd);
        std::vector<uint8_t> textureData = get_texture_data(pngData, header, dontComputeSizeInHeader);
        out.insert(out.end(), textureData.begin(), textureData.end());
    }
    
    return out;
}

/*********************************************/

int main(int argc, char* argv[]) {
    if(argc != 3) {
        show_help();
        return 1;
    }
    
    std::string inputFilepath = argv[1];
    std::string inputHeaderFilepath = inputFilepath + ".header";
    std::string outputFilename = argv[2];
    
    bool isCompressed;
    std::vector<uint8_t> uncompressed = get_texture_binary(inputFilepath, inputHeaderFilepath, isCompressed);
    
    // DEBUG
    // std::string outFilename = outputFilename + ".uncmp.bin";
    // write_binary_file(uncompressed, outFilename);
    
    if(isCompressed) {
        std::vector<uint8_t> compressedHeader;
        compressedHeader.insert(compressedHeader.end(), uncompressed.begin(), uncompressed.begin() + TEX_HEADER_SIZE);
        
        compressedHeader[0x1D] = 0x01;
    
        DKRCompression compression;
        std::vector<uint8_t> compressed = compression.compressBuffer(uncompressed);
        
        // Note: uncompressed is garbled at this point.
        
        compressed.insert(compressed.begin(), compressedHeader.begin(), compressedHeader.end());
        
        write_binary_file(compressed, outputFilename);
    } else {
        write_binary_file(uncompressed, outputFilename);
    }
    
    return 0;
}






