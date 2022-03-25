#include "build_fonts.h"

#define SIZEOF_FONTS_HEADER 4

// Note that these are just for DKR afaik. Other rare games have different sizes.
#define SIZEOF_FONT              0x400 // Larger in later Rare games
#define MAX_NUMBER_OF_TEXTURES   32    // Extended to 64 in later Rare games
#define CHAR_NODE_START_OFFSET   32
#define NUMBER_OF_CHAR_NODES     96    // Extended to 224 in later Rare games
#define CHAR_NODE_END_OFFSET     CHAR_NODE_START_OFFSET + NUMBER_OF_CHAR_NODES
#define SIZEOF_CHAR_NODE         8

BuildFonts::BuildFonts(std::string srcPath, std::string dstPath) {
    int numberOfFonts = get_array_length_from_json(srcPath, "fonts");
    std::vector<uint8_t> out(align16(SIZEOF_FONT * numberOfFonts + SIZEOF_FONTS_HEADER));
    
    // Write header.
    write_big_endian_word(out, 0, numberOfFonts);
    
    // Write fonts.
    for(int font = 0; font < numberOfFonts; font++) {
        int fontOffset = font * SIZEOF_FONT + SIZEOF_FONTS_HEADER;
        
        insert_ascii(out, fontOffset, get_string_from_json(srcPath, "fonts", font, "name"));
        write_big_endian_halfword(out, fontOffset + 0x20, get_int_from_json(srcPath, "fonts", font, "fixed-width"));
        write_big_endian_halfword(out, fontOffset + 0x22, get_int_from_json(srcPath, "fonts", font, "y-offset"));
        write_big_endian_halfword(out, fontOffset + 0x24, get_int_from_json(srcPath, "fonts", font, "special-character-width"));
        write_big_endian_halfword(out, fontOffset + 0x26, get_int_from_json(srcPath, "fonts", font, "tab-width"));
        insert_ascii(out, fontOffset + 0x28, get_string_from_json(srcPath, "fonts", font, "unknown-text"));
        
        int numberOfTextures = get_array_length_from_json(srcPath, "fonts", font, "textures");
        int texOffset = fontOffset + 0x40;
        int texIndex = 0;
        // Write texture ids.
        for(; texIndex < numberOfTextures; texIndex++) {
            write_big_endian_halfword(out, texOffset, get_tex_2d_index_from_build_id(get_string_from_json(srcPath, "fonts", font, "textures", texIndex)));
            texOffset += 2;
        }
        // Fill rest of the space with -1.
        for(; texIndex < MAX_NUMBER_OF_TEXTURES; texIndex++) {
            write_big_endian_halfword(out, texOffset, -1);
            texOffset += 2;
        }
        
        std::string encoding = get_string_from_json(srcPath, "fonts", font, "encoding", "type");
        make_uppercase(encoding);
        
        // Write character nodes
        if(encoding == "ASCII") {
            write_ascii_char_nodes(out, srcPath, fontOffset + 0x100, font);
        } else if(encoding == "CUSTOM") {
            write_custom_char_nodes(out, srcPath, fontOffset + 0x100, font);
        } else {
            display_error_and_abort("Unsupported font encoding type: \"", encoding, "\"");
        }
        
    }
    
    write_binary_file(out, dstPath);
}

BuildFonts::~BuildFonts() {
    
}

void write_char_node(std::vector<uint8_t> &out, std::string srcPath, int nodeOffset, int font, std::string &chr) {
    out[nodeOffset]     = get_int_from_json(srcPath, "fonts", font, "characters", chr, "tex-index");
    out[nodeOffset + 1] = get_int_from_json(srcPath, "fonts", font, "characters", chr, "char-width");
    out[nodeOffset + 2] = get_int_from_json(srcPath, "fonts", font, "characters", chr, "offset", 0);   // X offset
    out[nodeOffset + 3] = get_int_from_json(srcPath, "fonts", font, "characters", chr, "offset", 1);   // Y offset
    out[nodeOffset + 4] = get_int_from_json(srcPath, "fonts", font, "characters", chr, "uv", 0);       // U coordinate
    out[nodeOffset + 5] = get_int_from_json(srcPath, "fonts", font, "characters", chr, "uv", 1);       // V coordinate
    out[nodeOffset + 6] = get_int_from_json(srcPath, "fonts", font, "characters", chr, "tex-size", 0); // Width
    out[nodeOffset + 7] = get_int_from_json(srcPath, "fonts", font, "characters", chr, "tex-size", 1); // Height
}

void BuildFonts::write_ascii_char_nodes(std::vector<uint8_t> &out, std::string srcPath, int offset, int font) {
    for(int node = CHAR_NODE_START_OFFSET; node < CHAR_NODE_END_OFFSET; node++) {
        std::string chr;
        if(node == 127) {
            chr = "DEL"; // Special case because the delete character itself is sometimes weird.
        } else if (node == 92) {
            chr = "\\\\";
        } else if (node == 34) {
            chr = "\\\"";
        } else {
            chr = (char)node;
        }
        int nodeOffset = offset + (node - CHAR_NODE_START_OFFSET) * SIZEOF_CHAR_NODE;
        write_char_node(out, srcPath, nodeOffset, font, chr);
    }
}

void BuildFonts::write_custom_char_nodes(std::vector<uint8_t> &out, std::string srcPath, int offset, int font) {
    int index = 0;
    std::vector<std::string> order = get_array_from_json(srcPath, "fonts", font, "encoding", "order");
    for(std::string &chr : order) {
        if(index >= NUMBER_OF_CHAR_NODES) {
            std::string fontName = get_string_from_json(srcPath, "fonts", font, "name");
            display_error_and_abort("Too many character nodes in ", fontName, ". The limit is ", NUMBER_OF_CHAR_NODES);
        }
        int nodeOffset = offset + (index++ * SIZEOF_CHAR_NODE);
        write_char_node(out, srcPath, nodeOffset, font, chr);
    }
    // Set the rest of the nodes to show nothing.
    while(index < NUMBER_OF_CHAR_NODES) {
        int nodeOffset = offset + (index++ * SIZEOF_CHAR_NODE);
        out[nodeOffset] = -1;
    }
}
