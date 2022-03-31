#include "extract_menutext.h"

ExtractMenuText::ExtractMenuText(std::string key, std::vector<uint8_t> data, std::string outFilepath, 
  std::unordered_map<std::string, std::string> *tags) : Extract(key, data, outFilepath) {    
    json::JSON out = json::Object();
    
    out["type"] = "MenuText";
    
    std::cout << key << std::endl;
    
    uint32_t tableSize = stoi((*tags)["text-entry-count"]);
    
    //out["order"] = json::Array();
    out["sections"] = json::Object();
    
    for(size_t i = 0; i < tableSize; i++) {
        uint32_t offset = get_big_endian_word(data, i*4);
        
        if(offset == 0xFFFFFFFF) {
            //out["order"].append(nullptr);
        } else {
            std::string entry_key = (*tags)["text-entry-build-id_" + std::to_string(i)];
            if(out["sections"].hasKey(entry_key)) {
                std::stringstream err;
                err << "The key \"" << entry_key << "\" is already defined! Aborting!" << std::endl;
                std::cout << err.str();
                throw 1;
            }
            //out["order"].append(entry_key);
            out["sections"][entry_key] = get_ascii(data, offset);
        }
        
    }
    
    write_json(out, outFilepath);
    print_extracted();
}

ExtractMenuText::~ExtractMenuText(){
}
