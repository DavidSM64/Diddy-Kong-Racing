#include "buildMenuText.h"

#include <cstring>

#include "helpers/assetsHelper.h"
#include "helpers/dataHelper.h"

#include "fileTypes/types.hpp"

#include "misc/globalSettings.h"
#include "text/dkrText.h"

using namespace DkrAssetsTool;

size_t get_total_string_lengths(BuildInfo &info, const JsonFile &jsonFile, std::vector<std::string> &menuTextOrder, bool forceDKRJP) {
    size_t totalLength = 0;
    
    for(std::string &entryId : menuTextOrder) {
        const std::string ptr = "/sections/" + entryId;
        if(!jsonFile.has(ptr)) {
            continue;
        }
        
        std::string strValue = jsonFile.get_string(ptr);
        DKRText text(strValue);
        totalLength += text.bytes_size(forceDKRJP) + 1; // +1 for null terminator
    }
    
    return totalLength;
}

void BuildMenuText::build(BuildInfo &info) {
    JsonFile &menuTextSection = AssetsHelper::get_asset_section_json("ASSET_MENU_TEXT");
    
    std::vector<std::string> menuTextOrder;
    menuTextSection.get_array<std::string>("/menu-text-build-ids", menuTextOrder);
    
    size_t numberOfEntries = menuTextOrder.size();
    
    const JsonFile &jsonFile = info.get_src_json_file();
    
    std::string buildId = info.get_build_id();
    std::string dkrVersion = GlobalSettings::get_dkr_version();
    
    // If the version is not v77 and the language is japanese, then we need to force the DKRJP text format.
    bool forceDKRJP = !StringHelper::ends_with(dkrVersion, "v77") && StringHelper::has(buildId, "JAPANESE");
    
    size_t outSize = (numberOfEntries * 4) + get_total_string_lengths(info, jsonFile, menuTextOrder, forceDKRJP);
    outSize = DataHelper::align8(outSize); // Make sure the output is 8-byte aligned.
    
    info.out.resize(outSize);
    
    be_uint32_t *offsets = reinterpret_cast<be_uint32_t *>(&info.out[0]);
    
    size_t currentTextOffset = numberOfEntries * 4;
    
    for(size_t i = 0; i < numberOfEntries; i++) {
        const std::string &entryId = menuTextOrder[i];
        const std::string ptr = "/sections/" + entryId;
        if(!jsonFile.has(ptr)) {
            offsets[i] = 0xFFFFFFFF; // Null entry.
            continue;
        }
        
        offsets[i] = currentTextOffset;
        
        std::string entryStr = jsonFile.get_string(ptr);
        DKRText text(entryStr);
        std::vector<uint8_t> textBytes = text.get_bytes(forceDKRJP);
        char *outText = reinterpret_cast<char *>(&info.out[currentTextOffset]);
        
        memcpy(outText, (char*)&textBytes[0], textBytes.size());
        currentTextOffset += textBytes.size() + 1;
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
