#include "build_menutext.h"

BuildMenuText::BuildMenuText(std::string srcPath, std::string dstPath) {
    //int numberOfEntries = get_array_length_from_json(srcPath, "order");

    std::vector<std::string> ids = get_array_from_section("ASSET_MENU_TEXT", "menu-text-build-ids");
    int numberOfEntries = ids.size();
    
    std::vector<uint8_t> table(numberOfEntries * 4);
    std::vector<uint8_t> text;
    
    int textOffset = numberOfEntries * 4;
    
    for(int i = 0; i < numberOfEntries; i++) {
        // Get the build id for this index.
        std::string buildId = ids[i];

        // If the build ID is not in the sections, then just write -1 to the table.
        if(!json_has_key(srcPath, "sections", buildId)) {
            write_big_endian_word(table, i * 4, -1);
            continue;
        }
        // Get the text string from the inputJSON.
        std::string entryText = get_string_from_json(srcPath, "sections", buildId);
        // Write ascii text to vector
        write_ascii(text, entryText); 
        // Write the offset to the text
        write_big_endian_word(table, i * 4, textOffset); 
        // Increment the current offset by the length of the string (+1 for null terminator)
        textOffset += entryText.length() + 1; 
    }
    
    // Append the text data to the table data.
    table.insert(table.end(), text.begin(), text.end());
    
    while(table.size() % 8 != 0) {
        table.push_back(0); // Make sure the data is 8-byte aligned.
    }
    
    write_binary_file(table, dstPath);
}

BuildMenuText::~BuildMenuText(){
    
}
    
