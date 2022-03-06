#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread>
#include <unordered_map>
#include <algorithm>

// C++17
#include <variant>
#include <filesystem> 
namespace fs = std::filesystem;

#include "../common/util.h"
#include "../common/types.h"
#include "../libs/json.hpp"
#include "../libs/ThreadPool.h"

#include "rom.h"

#include "extract/extract_binary.h"
#include "extract/extract_compressed.h"
#include "extract/extract_gametext.h"
#include "extract/extract_fonts.h"
#include "extract/extract_menutext.h"
#include "extract/extract_levelname.h"
#include "extract/extract_levelheader.h"
#include "extract/extract_sprite.h"
#include "extract/extract_textures.h"
#include "extract/extract_ttghost.h"

struct ExtractInfo {
    std::string key;
    std::string type;
    std::string folder;
    std::string filename;
    std::vector<uint8_t> data;
    std::unordered_map<std::string, std::string> *tags;
    
    ExtractInfo(std::string key, std::string type, std::string folder, std::string filename, 
    std::vector<uint8_t> data, std::unordered_map<std::string, std::string> *tags = nullptr) 
        : key(key), type(type), folder(folder), filename(filename), data(data), tags(tags) 
        {}
};

class ExtractConfig {
public:
    ExtractConfig(std::string configFilepath, std::string outDirectory);
    ~ExtractConfig();
    void find_rom_for_this_config_and_extract(std::vector<ROM*> &roms);
    bool is_correct_version(std::string version);
private:
    
    void extract_code_sections(int &romOffset);
    void extract_asset_sections(int &romOffset);
    void execute_extraction();
    void extract();

    json::JSON configJSON; // Loaded from a config file.
    json::JSON assetsJson; // Output assets.json
    
    bool notSupported;
    std::string outBaseDirectory;
    std::string outDirectory;
    std::string name;
    std::string md5;
    std::string subfolder;
    
    ROM *rom;
    std::vector<ExtractInfo> extractions;
};
