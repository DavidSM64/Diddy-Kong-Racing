#include "buildMenuText.h"

using namespace DkrAssetsTool;

#include <cstring> // for strncpy

#include "helpers/assetsHelper.h"
#include "helpers/dataHelper.h"

BuildMenuText::BuildMenuText(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    JsonFile *menuTextSection = AssetsHelper::get_asset_section_json(_settings, "ASSET_MENU_TEXT");
    
    std::vector<std::string> menuTextOrder;
    menuTextSection->get_array<std::string>("/menu-text-build-ids", menuTextOrder);
    
    size_t numberOfEntries = menuTextOrder.size();
    
    size_t outSize = (numberOfEntries * 4) + _get_total_string_lengths(menuTextOrder);
    outSize = DataHelper::align8(outSize); // Make sure the output is 8-byte aligned.
    
    std::vector<uint8_t> out(outSize);
    
    be_uint32_t *offsets = reinterpret_cast<be_uint32_t *>(&out[0]);
    
    size_t currentTextOffset = numberOfEntries * 4;
    
    for(size_t i = 0; i < numberOfEntries; i++) {
        const std::string &entryId = menuTextOrder[i];
        const std::string ptr = "/sections/" + entryId;
        if(!_info.srcFile->has(ptr)) {
            offsets[i] = 0xFFFFFFFF; // Null entry.
            continue;
        }
        
        offsets[i] = currentTextOffset;
        
        std::string entryStr = _info.srcFile->get_string(ptr);
        char *text = reinterpret_cast<char *>(&out[currentTextOffset]);
        std::strncpy(text, entryStr.c_str(), entryStr.size());
        currentTextOffset += entryStr.size() + 1;
        
        // Shouldn't need to write the null terminator?
    }
    
    FileHelper::write_binary_file(out, _info.dstPath, true);
}

BuildMenuText::~BuildMenuText() {
    
}

size_t BuildMenuText::_get_total_string_lengths(std::vector<std::string> &menuTextOrder) {
    size_t totalLength = 0;
    
    for(std::string &entryId : menuTextOrder) {
        const std::string ptr = "/sections/" + entryId;
        if(!_info.srcFile->has(ptr)) {
            continue;
        }
        // +1 for null terminator
        totalLength += _info.srcFile->length_of_string(ptr) + 1;
    }
    
    return totalLength;
}

