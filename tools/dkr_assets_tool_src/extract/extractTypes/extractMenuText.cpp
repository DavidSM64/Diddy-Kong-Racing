#include "extractMenuText.h"

#include "fileTypes/types.hpp"

#include "helpers/jsonHelper.h"

ExtractMenuText::ExtractMenuText(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Menu Text", YELLOW_TEXT, _outFilepath);
    
    std::vector<uint8_t> rawBytes;
    _info.get_data_from_rom(rawBytes);
    
    DkrExtractMenuTextSection &menuTextConfig = _info.assetSection->specific.menuText; 
    std::string language = _info.get_tag<std::string>("language", "");
    
    DebugHelper::assert(!language.empty(), "(ExtractMenuText::ExtractMenuText) Language not set for ", _outFilepath);
    
    WritableJsonFile jsonFile(_outFilepath);
    
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
    
    jsonFile.save();
}

ExtractMenuText::~ExtractMenuText() {
}

