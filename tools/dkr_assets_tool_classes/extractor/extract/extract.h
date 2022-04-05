#pragma once

#include "../../common/util.h"
#include <unordered_map>

class Extract {
public:
    Extract(std::string key, std::vector<uint8_t> data, std::string outFilepath);
    ~Extract();
protected:
    std::string key;
    std::vector<uint8_t> data;
    std::string outFilepath;
    
    void print_extracted();
};
