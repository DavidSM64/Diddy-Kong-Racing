#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include "dkr_extractor_classes/config.h"
#include "dkr_extractor_classes/rom.h"
#include "dkr_decompressor_src/DKRCompression.h"
#include "n64graphics/n64graphics.h"

// C++17
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;

#define REVISION_NUMBER 1

const std::string CONFIG_EXTENSION = ".config.json";

const std::string ROM_EXTENSIONS[] = { ".z64", ".v64", ".n64", ".rom" };

std::string outDirectory;
std::string currentCategory;

/*********************************************/

void show_help() {
    std::cout << "Usage: ./dkr_extractor <version> <configs_directory> <baseroms_directory> <out_directory>" << std::endl;
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

void write_json(json::JSON& assetsJson) {
    std::string filename = outDirectory + "/assets/" + assetsJson["@version"].ToString() + "/assets.json";
    std::ofstream myfile;
    myfile.open(filename);
    myfile << assetsJson;
    myfile.close();
}

void extract_assets_from_rom(ExtractConfig& config, ROM& rom) {
    json::JSON assetsJson;
    
    assetsJson["@version"] = config.get_subfolder();
    assetsJson["@revision"] = REVISION_NUMBER;
    
    config.extract(rom, assetsJson);
    
    write_json(assetsJson);
}

/*********************************************/

int main(int argc, char* argv[]) {
    
    if(argc != 5) {
        show_help();
        return 1;
    }
    
    std::string version = argv[1];
    std::string configsDirectory = argv[2];
    std::string baseromsDirectory = argv[3];
    outDirectory = argv[4];
    
    std::vector<ExtractConfig> configs;
    std::vector<ROM> roms;
    
    for (const auto & entry : fs::directory_iterator(configsDirectory)){
        std::string filename = entry.path().filename();
        if(ends_with_config_extension(filename)) {
            configs.push_back(ExtractConfig(configsDirectory, filename, outDirectory));
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
        if(config.is_supported() && config.get_subfolder() == version) {
            for(auto& rom : roms) {
                if(rom.get_md5() == config.get_md5()) {
                    extract_assets_from_rom(config, rom);
                    completedAnExtraction = true;
                    break;
                }
            }
        }
    }
    
    if(!completedAnExtraction) {
        std::cout << "No compatible ROMs were found within the /baseroms/ directory" << std::endl;
        return 1;
    }
    
    return 0;
}
