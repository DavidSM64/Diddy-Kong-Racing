#include "extract_levelname.h"

ExtractLevelName::ExtractLevelName(std::string key, std::vector<uint8_t> data, std::string outFilepath) 
: Extract(key, data, outFilepath) {    
    json::JSON out = json::Object();
    
    out["type"] = "LevelNames";
    out["languages"] = json::Object();
    
    // Assumption: All of the values in the "Language" enum are continuous and start at 0.
    std::vector<std::string> languages = get_enum_keys("Language");
    
    int numLanguages = languages.size();
    std::vector<std::string> names = get_multiple_ascii(data, 0, numLanguages);
    
    for(int i = 0; i < numLanguages; i++) {
        out["languages"][languages[i]] = names[i];
    }
    
    write_json(out, outFilepath);
    print_extracted();
}

ExtractLevelName::~ExtractLevelName(){
}
