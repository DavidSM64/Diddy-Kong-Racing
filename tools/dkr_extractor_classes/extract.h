#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

#include "rom.h"

#include "../json/json.hpp"

// C++17
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;

class Extract {
public:
    Extract(std::vector<uint8_t> data, ROM& rom, std::string outFilepath);
    ~Extract();
    
    void write_binary_file(std::vector<uint8_t> data, std::string filepath);
    void write_text_file(std::string data, std::string filepath);
    void print_extracted(std::string outFilepath);

protected:
    void to_lowercase(std::string& input);
};
