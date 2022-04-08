#include "extractor.h"

Extractor::Extractor(std::string version, std::string configsDirectory, std::string baseromsDirectory, std::string outDirectory) {
    std::vector<std::string> baseroms = get_filenames_from_directory(baseromsDirectory);
    std::vector<ROM*> validROMs;
    for(std::string& baseromPath : baseroms) {
        ROM *checkRom = new ROM(baseromPath);
        if(checkRom->is_valid()) {
            validROMs.push_back(checkRom);
        } else {
            delete checkRom;
        }
    }
    
    if(validROMs.size() == 0) {
        std::cout << "No valid ROMs were found in the baseroms directory" << std::endl;
        return;
    }
    
    std::vector<std::string> configPaths = get_filenames_from_directory_with_extension(configsDirectory, ".config.json");
    for(std::string& configPath : configPaths) {
        ExtractConfig config(configPath, outDirectory);
        if(config.is_correct_version(version)) {
            config.find_rom_for_this_config_and_extract(validROMs);
        }
    }
    
    // Cleanup
    for(size_t i; i < validROMs.size(); i++) {
        delete validROMs[i];
    }
}

Extractor::~Extractor() {
    
}
