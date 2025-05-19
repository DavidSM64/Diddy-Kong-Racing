#include "extractLevelName.h"

#include <vector>
#include <string>

#include "helpers/debugHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/c/cContext.h"

using namespace DkrAssetsTool;

void ExtractLevelName::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Level Name", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_string("/type", "LevelName");
    
    CEnum *languages = info.get_c_context().get_enum("Language");
    
    size_t numLanguages = languages->get_member_count();
    
    size_t curOffset = 0;
    
    for(size_t i = 0; i < numLanguages; i++) {
        std::string lang, levelNameInLang;
        DebugHelper::assert(languages->get_symbol_of_value(i, lang), 
            "(ExtractLevelName::extract) Index ", i, " is out of range.");
        
        // Get the current language name.
        curOffset = StringHelper::get_ascii_from_data(rawBytes, curOffset, levelNameInLang);
        
        jsonFile.set_string("/languages/" + lang, levelNameInLang);
    }
    
    info.write_json_file();
}
