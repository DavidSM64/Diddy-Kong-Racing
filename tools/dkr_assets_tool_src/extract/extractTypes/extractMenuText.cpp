#include "extractMenuText.h"

#include "fileTypes/types.hpp"

#include "helpers/jsonHelper.h"

#include "text/dkrText.h"

#include "extract/stats.h"

using namespace DkrAssetsTool;

void ExtractMenuText::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Menu Text", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    // TODO: Use BytesView instead of vector!
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    ExtractStats &stats = info.get_stats();
    const AssetExtractConfig &config = info.get_config();
    size_t fileIndex = info.get_file_index();
    
    std::string language = config.get<std::string>("/file-type-attributes/MenuText/language-order/" + std::to_string(fileIndex), "");
    
    DebugHelper::assert(!language.empty(), 
        "(ExtractMenuText::extract) Language not set for ", info.get_out_filepath(".json"));
    
    WritableJsonFile &jsonFile = info.get_json_file();
    
    jsonFile.set_string("/language", language);
    jsonFile.set_string("/type", "MenuText");
    
    std::string sectionsPtr = "/sections";
    
    const JsonFile &configJson = config.get_config_json();
    std::vector<std::string> menuTextBuildIds;
    configJson.get_array<std::string>("/file-type-attributes/MenuText/menu-text-build-ids", menuTextBuildIds);
    
    size_t numberOfTextEntries = stats.get_tag<int>("menuTextCount", 0);
    size_t numberOfRecordedEntries = menuTextBuildIds.size();
    
    be_uint32_t *offsets = reinterpret_cast<be_uint32_t *>(&rawBytes[0]);
    
    for(size_t i = 0; i < numberOfTextEntries; i++) {
        be_uint32_t offsetToText = offsets[i];
        
        if(offsetToText == 0xFFFFFFFF) {
            continue;
        }
        
        DKRText text(rawBytes, offsetToText);
        
        if(i < numberOfRecordedEntries) {
            jsonFile.set_string(sectionsPtr + "/" + menuTextBuildIds[i], text.get_text());
        } else {
            jsonFile.set_string(sectionsPtr + "/ASSET_MENU_TEXT_UNKNOWN_" + std::to_string(i), text.get_text());
        }
    }
    
    info.write_json_file();
}
