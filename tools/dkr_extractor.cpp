#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include "dkr_extractor_classes/extract_config.h"
#include "dkr_extractor_classes/rom.h"
#include "dkr_extractor_classes/extract_binary.h"
#include "dkr_extractor_classes/extract_compressed.h"
#include "dkr_extractor_classes/extract_cheats.h"
#include "dkr_extractor_classes/extract_textures.h"
#include "dkr_decompressor_src/DKRCompression.h"
#include "n64graphics/n64graphics.h"

// C++17
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;

const std::string CONFIG_EXTENSION = ".extract-config";

const std::string ROM_EXTENSIONS[3] = { ".z64", ".v64", ".n64" };

std::string outDirectory;
std::string currentCategory;

/*********************************************/

void show_help() {
    std::cout << "Usage: ./dkr_extractor <configs_directory> <baseroms_directory> <out_directory>" << std::endl;
}

bool ends_with_extension(std::string filename, std::string extension) {
    return std::equal(extension.rbegin(), extension.rend(), filename.rbegin());
}

bool ends_with_config_extension(std::string filename) {
    return ends_with_extension(filename, CONFIG_EXTENSION);
}

bool ends_with_rom_extension(std::string filename) {
    for (const std::string romExtension : ROM_EXTENSIONS) {
        if(ends_with_extension(filename, romExtension)) {
            return true;
        }
    }
    return false;
}

/*********************************************/

void add_to_JSON(json::JSON& assetsJson, std::string filename) {
    if(currentCategory != "none") {
        json::JSON obj = json::Object();
        obj["filename"] = filename;
        obj["category"] = currentCategory;
        assetsJson["assets"].append(obj);
    }
}

void extract_range(std::string subfolder, ConfigRange& range, ROM& rom, json::JSON& assetsJson) {

    switch(range.get_type()) {
        case ConfigRangeType::BINARY:
        {
            ExtractBinary(range, rom, assetsJson, outDirectory);
            break;
        }
        case ConfigRangeType::COMPRESSED:
        {
            ExtractCompressed(range, rom, assetsJson, outDirectory);
            break;
        }
        case ConfigRangeType::CHEATS:
        {
            ExtractCheats(range, rom, assetsJson, outDirectory);
            break;
        }
        case ConfigRangeType::TEXTURE:
        {
            ExtractTextures(range, rom, assetsJson, outDirectory);
            break;
        }
    }
}

void write_json(json::JSON& assetsJson) {
    std::string filename = "./assets/us_1.0/assets.json";
    std::ofstream myfile;
    myfile.open(filename);
    myfile << assetsJson;
    myfile.close();
}

void extract_assets_from_rom(Config& config, ROM& rom) {
    if(config.get_size() != rom.get_size()) {
        std::cout << "Error: Config does not add up to the ROM size." << std::endl 
            << std::hex << "ROM size is " << rom.get_size() 
            << "; Config ends at " << config.get_size() << std::dec << std::endl;
    }
    
    currentCategory = "none";
    
    json::JSON assetsJson;
    
    assetsJson["@version"] = config.get_subfolder();
    assetsJson["@revision"] = 0;
    assetsJson["assets"] = json::Array();
    
    int numRanges = config.get_number_of_ranges();
    for (int i = 0; i < numRanges; i++) {
        ConfigRange range = config.get_range(i);
        currentCategory = range.get_category();
        extract_range(config.get_subfolder(), range, rom, assetsJson);
    }
    
    write_json(assetsJson);
}

/*********************************************/

int main(int argc, char* argv[]) {
    
    if(argc != 4) {
        show_help();
        return 1;
    }
    
    std::string configsDirectory = argv[1];
    std::string baseromsDirectory = argv[2];
    outDirectory = argv[3];
    
    std::vector<Config> configs;
    std::vector<ROM> roms;
    
    for (const auto & entry : fs::directory_iterator(configsDirectory)){
        std::string filename = entry.path().filename();
        if(ends_with_config_extension(filename)) {
            configs.push_back(Config(configsDirectory, filename));
        }
    }
    
    for (const auto & entry : fs::directory_iterator(baseromsDirectory)){
        std::string filename = entry.path().string();
        if(ends_with_rom_extension(filename)) {
            roms.push_back(ROM(filename));
        }
    }
    
    bool completedAnExtraction = false;
    
    for(auto& config : configs) {
        if(config.is_supported()) {
            for(auto& rom : roms) {
                if(rom.get_md5() == config.get_md5()) {
                    extract_assets_from_rom(config, rom);
                    completedAnExtraction = true;
                    break;
                }
            }
        } else {
            std::cout << "The config for \"" << config.get_name() << "\" is currently not supported." << std::endl;
        }
    }
    
    if(!completedAnExtraction) {
        std::cout << "No compatible ROMs were found within the /baseroms/ directory" << std::endl;
        return 1;
    }
    
    return 0;
}
