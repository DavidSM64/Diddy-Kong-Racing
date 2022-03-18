#include "build_levelname.h"

BuildLevelName::BuildLevelName(std::string srcPath, std::string dstPath) {
    std::vector<uint8_t> out;
    
    std::vector<std::string> languages = get_enum_keys("Language");

    int numLangWritten = 0;
    
    // Search through and add all the avaliable languages.
    // Note: If a language is not defined in the enum, then it won't be added to the output!
    for(auto &langName : languages) {
        if(json_has_key(srcPath, "languages", langName)) { // Check if the level name json has the language.
            write_ascii(out, get_string_from_json(srcPath, "languages", langName));
            numLangWritten++;
        } else { 
            // Language not found. For now, this means the text will be empty.
            // TODO: Maybe have an option to default to english?
            out.push_back('\0'); // Push back a null terminator
        }
    }

    if(numLangWritten == 0) {
        std::cout << "Warning: No languages were found." << std::endl;
    }
    
    write_binary_file(out, dstPath);
}

BuildLevelName::~BuildLevelName() {
    
}
