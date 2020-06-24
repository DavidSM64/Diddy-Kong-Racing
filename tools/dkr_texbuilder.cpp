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

void flip_vertically(std::vector<uint8_t>& data, int width, int height, int bitDepth) {
    int rowSize;
    if(bitDepth == 4) {
        rowSize = width / 2;
    } else {
        rowSize = width * (bitDepth / 8);
    }
    
    uint8_t temp = 0;
    
    for(int y = 0; y < height/2; y++) {
        for(int x = 0; x < rowSize; x++) {
            temp = data[y * rowSize + x];
            data[y * rowSize + x] = data[(height - y - 1) * rowSize + x];
            data[(height - y - 1) * rowSize + x] = temp;
        }
    }
}

int get_texture_type(std::string textureFormatString) {
    to_lowercase(textureFormatString);
    
    if(textureFormatString == "rgba32")      return TEX_FORMAT_RGBA32;
    else if(textureFormatString == "rgba16") return TEX_FORMAT_RGBA16;
    else if(textureFormatString == "i8")     return TEX_FORMAT_I8;
    else if(textureFormatString == "i4")     return TEX_FORMAT_I4;
    else if(textureFormatString == "ia16")   return TEX_FORMAT_IA16;
    else if(textureFormatString == "ia8")    return TEX_FORMAT_IA8;
    else if(textureFormatString == "ia4")    return TEX_FORMAT_IA4;
    else if(textureFormatString == "ci4")    return TEX_FORMAT_CI4;
    
    std::cout << "Error: Invalid texture type: " << textureFormatString << std::endl;
    throw 1;
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

void generate_texture_header(std::vector<uint8_t>& outData, int width, int height, int textureFormat, 
    int numTextures, std::string flags, std::string headerBytes, bool& forceAlignment) {
    // I currently do not know what these are for.
    int A = std::stoi(headerBytes.substr(0, 1), 0, 16);
    int B = std::stoi(headerBytes.substr(1, 2), 0, 16);
    int C = std::stoi(headerBytes.substr(3, 2), 0, 16);
    int D = std::stoi(headerBytes.substr(5, 4), 0, 16);
    int E = std::stoi(headerBytes.substr(9, 2), 0, 16);
    
    bool dontComputeSize = (flags.at(2) == 'Z');
    
    int textureSize = get_texture_size(width, height, textureFormat);
    
    /* Texture header is 0x20 bytes long */
    /* 0x00 */ outData.push_back(width);
    /* 0x01 */ outData.push_back(height);
    /* 0x02 */ outData.push_back((A << 4) | textureFormat);
    /* 0x03 */ outData.push_back(B);
    /* 0x04 */ outData.push_back(C);
    /* 0x05 */ outData.push_back(0x01); // Always 0x01?
    /* 0x06 */ outData.push_back((D >> 8) & 0xFF); 
               outData.push_back(D & 0xFF);
    /* 0x08 */ outData.push_back(0); // Offset to CI4 palette
               outData.push_back(0);
    /* 0x0A */ outData.push_back(0);
    /* 0x0B */ outData.push_back(0); // Initalized in RAM; Number of commands in display list.
    /* 0x0C */ outData.push_back(0); // Initalized in RAM; Pointer to texture display list
               outData.push_back(0);
               outData.push_back(0);
               outData.push_back(0);
    /* 0x10 */ outData.push_back(0);
    /* 0x11 */ outData.push_back(0);
    /* 0x12 */ outData.push_back(numTextures);
    /* 0x13 */ outData.push_back(0);
    /* 0x14 */ outData.push_back(0);
    /* 0x15 */ outData.push_back(E);
    if(dontComputeSize) {
    /* 0x16 */ outData.push_back(0); // Keep it zero, Not sure why this is neccessary though.
               outData.push_back(0);
               forceAlignment = true;
    } else {
    /* 0x16 */ outData.push_back((textureSize >> 8) & 0xFF); // Texture size
               outData.push_back(textureSize & 0xFF);
               forceAlignment = false;
    }   
    /* 0x18 */ outData.push_back(0);
    /* 0x19 */ outData.push_back(0);
    /* 0x1A */ outData.push_back(0);
    /* 0x1B */ outData.push_back(0);
    /* 0x1C */ outData.push_back(0);
    /* 0x1D */ outData.push_back(dontComputeSize ? 1 : 0);
    /* 0x1E */ outData.push_back(0);
    /* 0x1F */ outData.push_back(0);
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

std::vector<uint8_t> get_texture_data(std::vector<uint8_t> pngData, int width, int height, int textureFormat, int numTextures, 
std::string flags, std::string headerBytes) {
    std::vector<uint8_t> outData;
    
    bool forceAlignment;
    generate_texture_header(outData, width, height, textureFormat, numTextures, flags, headerBytes, forceAlignment);
    
    bool flipVertically = (flags.at(1) == 'F');
    bool interlace = ((outData[0x06] & 0x4) == 0x04);
    
    switch(textureFormat) {
        case TEX_FORMAT_RGBA32:
        {
            if(flipVertically) {
                flip_vertically(pngData, width, height, 32); 
            }
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
            if(flipVertically) {
                flip_vertically(rgba16, width, height, 16); 
            }
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
            if(flipVertically) {
                flip_vertically(i8, width, height, 8); 
            }
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
            if(flipVertically) {
                flip_vertically(i4, width, height, 4); 
            }
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
            if(flipVertically) {
                flip_vertically(ia16, width, height, 16); 
            }
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
            if(flipVertically) {
                flip_vertically(ia8, width, height, 8); 
            }
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
            if(flipVertically) {
                flip_vertically(ia4, width, height, 4); 
            }
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

std::vector<uint8_t> get_texture_binary(std::string inputFilename, std::string inputFilepath, std::string& flags) {
    std::vector<uint8_t> out;
    std::vector<std::string> elems = split(inputFilename, '.');
    
    int numElements = elems.size();
    
    int numTextures, textureFormat;
    std::string headerBytes;
    
    if(numElements == 6) {
        numTextures = 1;
        flags = elems[2];
        headerBytes = elems[3];
        textureFormat = get_texture_type(elems[4]);
    } else if(numElements == 7) {
        numTextures = stoi(elems[2], 0, 10);
        flags = elems[3];
        headerBytes = elems[4];
        textureFormat = get_texture_type(elems[5]);
    } else {
        std::cout << "Invalid texture name" << std::endl;
        throw 1;
    }
    
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
        std::vector<uint8_t> textureData = get_texture_data(pngData, width, height, textureFormat, numTextures, flags, headerBytes);
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
    std::string outputFilename = argv[2];
    std::string inputFilename;
    
    std::size_t lastSlash = inputFilepath.rfind('/');
    if(lastSlash == std::string::npos) {
        inputFilename = inputFilepath;
    } else {
        inputFilename = inputFilepath.substr(lastSlash + 1, inputFilepath.length() - lastSlash - 1);
    }
    
    std::string flags;
    std::vector<uint8_t> uncompressed = get_texture_binary(inputFilename, inputFilepath, flags);
    
    // DEBUG
    // std::string outFilename = outputFilename + ".uncmp.bin";
    // write_binary_file(uncompressed, outFilename);
    
    if(flags.at(0) == 'C') {
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






