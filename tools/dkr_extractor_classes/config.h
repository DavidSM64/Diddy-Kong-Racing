#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

// C++17
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;

#include "../json/json.hpp"

#include "rom.h"
#include "extract_binary.h"
#include "extract_compressed.h"
#include "extract_textures.h"

class ExtractConfig {
public:
    ExtractConfig(std::string configsDirectory, std::string filename, std::string outDirectory);
    ~ExtractConfig();
    
    void extract(ROM& rom, json::JSON& assetsJson);
    void extract_file(ROM& rom, std::string type, std::string folder, std::string filename, std::vector<uint8_t> data);
    
    bool is_supported();
    std::string get_name();
    std::string get_md5();
    std::string get_subfolder();
    
    
private:
    json::JSON configJSON; // Loaded from a config file.
    
    int currentROMOffset;
    
    bool notSupported;
    std::string outDirectory;
    std::string name;
    std::string md5;
    std::string subfolder;
    
    std::string read_file(std::string filename);
};
