#include "buildFonts.h"

#include <cstring> // for memset

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/assetsHelper.h"

using namespace DkrAssetsTool;

static std::reference_wrapper<JsonFile> get_font_file(BuildInfo &info, fs::path &localFontFilepath) {
    fs::path fontPath = info.get_path_to_directory() / localFontFilepath;
    
    auto tryGetJsonFile = JsonHelper::get_file(fontPath);
    
    // Get the font file, and throw an error if it doesn't exist.
    DebugHelper::assert_(tryGetJsonFile.has_value(), 
        "(BuildFonts::get_font_file) Could not font file ", fontPath);
    
    return tryGetJsonFile.value();
}

 static void parse_ascii_encoding(const JsonFile &fontJson, FontFile *fontFile) {
     for(int i = 0; i < FONTS_NUMBER_OF_CHARACTERS; i++) {
         FontCharacter *outFontCharacter = &fontFile->characters[i];
         char character = (char)(FONTS_START_CHAR + i);
         std::string charPtr = "/characters/";
         
         if(character == '~') {
            charPtr += "~0"; // Tilde
        } else if(character == '/') {
            charPtr += "~1"; // Frontslash
        } else if(character == 127) {
            charPtr += "DEL"; // Delete
        } else {
            charPtr += character;
        }
        
        outFontCharacter->texIndex = fontJson.get_int(charPtr + "/tex-index");
        outFontCharacter->charWidth = fontJson.get_int(charPtr + "/char-width", 0);
        outFontCharacter->offsetX = fontJson.get_int(charPtr + "/offset/x", 0);
        outFontCharacter->offsetY = fontJson.get_int(charPtr + "/offset/y", 0);
        outFontCharacter->texU = fontJson.get_int(charPtr + "/uv/u", 0);
        outFontCharacter->texV = fontJson.get_int(charPtr + "/uv/v", 0);
        outFontCharacter->texWidth = fontJson.get_int(charPtr + "/tex-size/width", 0);
        outFontCharacter->texHeight = fontJson.get_int(charPtr + "/tex-size/height", 0);
     }
 }


void BuildFonts::build(BuildInfo &info) {
    const JsonFile &jsonFile = info.get_src_json_file();
    
    size_t numberOfFonts = jsonFile.length_of_array("/fonts-order");
    
    size_t outSize = DataHelper::align16(sizeof(be_uint32_t) + (numberOfFonts * sizeof(FontFile)));
    info.out.resize(outSize);
    
    // Convert the raw bytes into the FontData structure.
    FontData *fontData = reinterpret_cast<FontData *>(&info.out[0]);
    
    fontData->numberOfFonts = numberOfFonts;
    
    for(size_t fontIndex = 0; fontIndex < numberOfFonts; fontIndex++) {
        std::string fontBuildId = jsonFile.get_string("/fonts-order/" + std::to_string(fontIndex));
        fs::path localFontFilepath = jsonFile.get_string("/fonts/" + fontBuildId);
        
        JsonFile &fontJson = get_font_file(info, localFontFilepath);
        FontFile *outFontFile = &fontData->fonts[fontIndex];
        
        fontJson.copy_string_to("/name", outFontFile->name, FONTS_NAME_LENGTH, "unnamedFont");
        fontJson.copy_string_to("/junk-text", outFontFile->junkText, FONTS_JUNKTEXT_LENGTH);
        
        outFontFile->tabWidth = fontJson.get_int("/tab-width");
        outFontFile->fixedWidth = fontJson.get_int("/fixed-width");
        outFontFile->yOffset = fontJson.get_int("/y-offset");
        outFontFile->specialCharacterWidth = fontJson.get_int("/special-character-width");
        
        size_t numTextures = fontJson.length_of_array("/textures");
        
        if(numTextures > FONTS_NUMBER_OF_TEXTURE_INDICES) {
            std::string fontName = fontJson.get_string("/name");
            DebugHelper::warn("(BuildFonts::build) Too many textures in font \"", fontName, "\". Have ", 
                numTextures, " texture ids, but the limit is ", FONTS_NUMBER_OF_TEXTURE_INDICES);
            numTextures = FONTS_NUMBER_OF_TEXTURE_INDICES;
        }
        
        for(size_t texIndex = 0; texIndex < numTextures; texIndex++) {
            std::string texIndexPtr = "/textures/" + std::to_string(texIndex);
            
            if(fontJson.is_value_null(texIndexPtr)) {
                outFontFile->textureIndices[texIndex] = -1; // -1 = No Texture
                continue;
            }
            
            DebugHelper::assert(fontJson.is_value_a_string(texIndexPtr), "(BuildFonts::build) [", texIndexPtr, "] is not a string!");
            
            std::string texBuildId = fontJson.get_string(texIndexPtr);
            
            int fontTextureIndex = AssetsHelper::get_asset_index("ASSET_TEXTURES_2D", texBuildId);
            
            outFontFile->textureIndices[texIndex] = fontTextureIndex;
        }
        
        // Fills in the rest with nulls
        for(size_t texIndex = numTextures; texIndex < FONTS_NUMBER_OF_TEXTURE_INDICES; texIndex++) {
            outFontFile->textureIndices[texIndex] = -1;
        }
        
        // Assume ASCII by default.
        std::string encodingType = fontJson.get_string("/encoding/type", "ASCII");
        
        StringHelper::make_uppercase(encodingType); // Make sure string is uppercase.
        
        if(encodingType == "ASCII") {
            parse_ascii_encoding(fontJson, outFontFile);
        } else {
            // TODO: Support other encodings?
            DebugHelper::error("(BuildFonts::build) Unsupported font encoding type: \"", encodingType, "\"");
        }
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
