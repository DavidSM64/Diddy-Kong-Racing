#include "buildMenuText.h"

using namespace DkrAssetsTool;

#include <cstring> // for strncpy

#include "helpers/assetsHelper.h"
#include "helpers/dataHelper.h"

#include "fileTypes/types.hpp"

size_t get_total_string_lengths(BuildInfo &info, std::vector<std::string> &menuTextOrder) {
    size_t totalLength = 0;
    
    for(std::string &entryId : menuTextOrder) {
        const std::string ptr = "/sections/" + entryId;
        if(!info.srcFile->has(ptr)) {
            continue;
        }
        // +1 for null terminator
        totalLength += info.srcFile->length_of_string(ptr) + 1;
    }
    
    return totalLength;
}


void BuildMenuText::build(BuildInfo &info) {
    JsonFile &menuTextSection = AssetsHelper::get_asset_section_json("ASSET_MENU_TEXT");
    
    std::vector<std::string> menuTextOrder;
    menuTextSection.get_array<std::string>("/menu-text-build-ids", menuTextOrder);
    
    size_t numberOfEntries = menuTextOrder.size();
    
    size_t outSize = (numberOfEntries * 4) + get_total_string_lengths(info, menuTextOrder);
    outSize = DataHelper::align8(outSize); // Make sure the output is 8-byte aligned.
    
    info.out.resize(outSize);
    
    be_uint32_t *offsets = reinterpret_cast<be_uint32_t *>(&info.out[0]);
    
    size_t currentTextOffset = numberOfEntries * 4;
    
    for(size_t i = 0; i < numberOfEntries; i++) {
        const std::string &entryId = menuTextOrder[i];
        const std::string ptr = "/sections/" + entryId;
        if(!info.srcFile->has(ptr)) {
            offsets[i] = 0xFFFFFFFF; // Null entry.
            continue;
        }
        
        offsets[i] = currentTextOffset;
        
        std::string entryStr = info.srcFile->get_string(ptr);
        char *text = reinterpret_cast<char *>(&info.out[currentTextOffset]);
        std::strncpy(text, entryStr.c_str(), entryStr.size());
        currentTextOffset += entryStr.size() + 1;
        
        // Shouldn't need to write the null terminator?
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
