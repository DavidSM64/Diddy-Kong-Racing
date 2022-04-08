#pragma once
#include <iostream> 
#include <fstream> 
#include <vector>
#include <string>
#include <cstdint>
#include "GECompression.h"
#include "DKRGzip.h"

// C++17
#include <filesystem> 
namespace fs = std::filesystem;

class DKRCompression
{
public:
    DKRCompression();
    ~DKRCompression();
    
    std::vector<uint8_t> compressBuffer(std::vector<uint8_t>& data);
    std::vector<uint8_t> decompressBuffer(std::vector<uint8_t>& data);
    bool readBinaryFile(std::vector<uint8_t>& input, std::string filename);
    bool writeBinaryFile(std::vector<uint8_t>& output, std::string filename);
    
private:
    GECompression compressed;
};
