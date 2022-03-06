#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread>

#include "config.h"
#include "rom.h"
#include "../common/util.h"

class Extractor {
public:
    Extractor(std::string version, std::string configsDirectory, 
        std::string baseromsDirectory, std::string outDirectory);
    ~Extractor();
private:
    std::vector<ExtractConfig> configs;
};
