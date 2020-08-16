#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

#include "extract_config.h"
#include "rom.h"

#include "../json/json.hpp"

// C++17
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;

class Extract {
public:
    Extract(ConfigRange& range, ROM& rom, json::JSON& assetsJson, std::string outDirectory);
    ~Extract();
    
    void write_binary_file(std::vector<uint8_t> data, std::string filepath);
    void write_text_file(std::string data, std::string filepath);
    void print_extracted(int start, int end, std::string subfolder, std::string name);

protected:
    ConfigRange& range;
    ROM& rom;
    json::JSON& assetsJson;
    std::string outDirectory;
    
    void to_lowercase(std::string& input);
};
