#include "extract_fonts.h"

#define SECTION_TEXTURE_2D_INDEX 4
#define SECTION_FONTS_INDEX 44

#define GAME_FONTS_FOLDERNAME "game_fonts"

ExtractFonts::ExtractFonts(std::string key, std::vector<uint8_t> data, std::string outFilepath, std::string folder, json::JSON &configJSON) 
: Extract(key, data, outFilepath) {    
    json::JSON out = json::Object();
    
    //out["fonts-folder"] = GAME_FONTS_FOLDERNAME;
    create_directory(folder + "/" + GAME_FONTS_FOLDERNAME); 
    out["fonts"] = json::Object();

    int numberOfFonts = get_big_endian_word(data, 0);
    for(int i = 0; i < numberOfFonts; i++) {
        int offset = (i * 0x400) + 4; // Offset in file for this font.

        std::string fontName = get_ascii(data, offset);
        std::string fontId = "ASSET_FONTS_" + fontName;
        make_uppercase(fontId);
        
        json::JSON font = json::Object();
        
        font["name"] = fontName;
        font["unknown-text"] = get_ascii(data, offset + 0x28);
        font["fixed-width"] = get_big_endian_halfword(data, offset + 0x20);
        font["y-offset"] = get_big_endian_halfword(data, offset + 0x22);
        font["special-character-width"] = get_big_endian_halfword(data, offset + 0x24);
        font["tab-width"] = get_big_endian_halfword(data, offset + 0x26);
        
        font["textures"] = json::Array();
        
        int texOffset = offset + 0x40;
        int16_t texIndex = get_big_endian_halfword(data, texOffset);
        while(texIndex != -1) {
            json::JSON textureId = configJSON["assets"]["sections"][SECTION_TEXTURE_2D_INDEX]["child-build-ids"][texIndex];
            font["textures"].append(textureId);
            texOffset += 2;
            texIndex = get_big_endian_halfword(data, texOffset);
        }
        
        font["characters"] = json::Object();
        
        for(int j = 32; j < 128; j++) {
            int nodeOffset = offset + 0x100 + ((j - 32) * 8);
            json::JSON node = json::Object();
            
            node["tex-index"] = (int8_t)data[nodeOffset];
            node["char-width"] = data[nodeOffset + 1];
            node["offset"] = json::Array();
            node["offset"].append(data[nodeOffset + 2]); // X offset
            node["offset"].append(data[nodeOffset + 3]); // Y offset
            node["uv"] = json::Array();
            node["uv"].append(data[nodeOffset + 4]); // U coordinate
            node["uv"].append(data[nodeOffset + 5]); // V coordinate
            node["tex-size"] = json::Array();
            node["tex-size"].append(data[nodeOffset + 6]); // Width
            node["tex-size"].append(data[nodeOffset + 7]); // Height
            
            if(j == '\"') {
                font["characters"]["\\\""] = node;
            } else if(j == '\\') {
                font["characters"]["\\\\"] = node;
            } else if(j == 127) {
                font["characters"]["DEL"] = node;
            } else {
                font["characters"][std::string(1, (char)j)] = node;
            }
        }
        
        font["encoding"] = json::Object();
        font["encoding"]["type"] = "ASCII";

        std::string fontJsonFilename = GAME_FONTS_FOLDERNAME;
        fontJsonFilename += "/" + fontName + ".json";

        out["fonts"][fontId] = fontJsonFilename;
        
        write_json(font, folder + "/" + fontJsonFilename);
    }
    out["type"] = "Fonts";
    write_json(out, outFilepath);
    print_extracted();
}

ExtractFonts::~ExtractFonts(){
}
