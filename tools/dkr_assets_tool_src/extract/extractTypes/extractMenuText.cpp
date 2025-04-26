#include "extractMenuText.h"

#include "fileTypes/types.hpp"

#include "helpers/jsonHelper.h"

using namespace DkrAssetsTool;

void ExtractMenuText::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Menu Text", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    /*
    DkrExtractMenuTextSection &menuTextConfig = info.assetSection->specific.menuText; 
    std::string language = info.get_tag<std::string>("language", "");
    
    DebugHelper::assert(!language.empty(), 
        "(ExtractMenuText::extract) Language not set for ", info.get_out_filepath(".json"));
    
    WritableJsonFile &jsonFile = info.get_json_file();
    
    jsonFile.set_string("/language", language);
    jsonFile.set_string("/type", "MenuText");
    
    std::string sectionsPtr = "/sections";
    //std::string orderPtr = "/order";
    
    be_uint32_t *offsets = reinterpret_cast<be_uint32_t *>(&rawBytes[0]);
    
    for(size_t i = 0; i < menuTextConfig.numberOfTextEntries; i++) {
        be_uint32_t offsetToText = offsets[i];
        
        if(offsetToText == 0xFFFFFFFF) {
            //jsonFile.set_null(orderPtr + "/" + std::to_string(i));
            continue;
        }
        
        char *text = reinterpret_cast<char *>(&rawBytes[offsetToText]);
        
        std::string textBuildId = menuTextConfig.menuTextBuildIds[i];
        
        //jsonFile.set_string(orderPtr + "/" + std::to_string(i), textBuildId);
        jsonFile.set_string(sectionsPtr + "/" + textBuildId, text);
    }
    */
    info.write_json_file();
}
