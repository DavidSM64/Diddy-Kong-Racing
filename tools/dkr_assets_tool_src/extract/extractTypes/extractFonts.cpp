#include "extractFonts.h"

using namespace DkrAssetsTool;

#include "helpers/assetsHelper.h"
#include "helpers/stringHelper.h"

#include "fileTypes/fonts.hpp"

ExtractFonts::ExtractFonts(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Font", YELLOW_TEXT, _outFilepath);
    
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_string("/type", "Fonts");
    
    std::vector<uint8_t> rawBytes;
    _info.get_data_from_rom(rawBytes);
    
    FontData *fontsData = reinterpret_cast<FontData *>(&rawBytes[0]);
    
    for(int i = 0; i < (int)fontsData->numberOfFonts; i++) {
        FontFile &font = fontsData->fonts[i];
        
        std::string fontName(font.name);
        std::string fontBuildId = info.assetSection->buildId + "_" + fontName;
        StringHelper::make_uppercase(fontBuildId);
        fs::path fontLocalPath = FONTS_SUBDIRECTORY / (fontName + ".meta.json");
        fs::path _outFontFilepath = _settings.pathToAssets / _info.get_out_folder() / fontLocalPath;
        
        jsonFile.set_string("/fonts-order/" + std::to_string(i), fontBuildId);
        jsonFile.set_string("/fonts/" + fontBuildId, fontLocalPath);
        
        WritableJsonFile fontJsonFont(_outFontFilepath);
        
        fontJsonFont.set_string("/name", fontName);
        fontJsonFont.set_int("/fixed-width", font.fixedWidth);
        fontJsonFont.set_int("/y-offset", font.yOffset);
        fontJsonFont.set_int("/special-character-width", font.specialCharacterWidth);
        fontJsonFont.set_int("/tab-width", font.tabWidth);
        
        fontJsonFont.set_string("/encoding/type", "ASCII");
        
        fontJsonFont.set_string("/junk-text", font.junkText);
        
        for(int j = 0; j < FONTS_NUMBER_OF_TEXTURE_INDICES; j++) {
            if(font.textureIndices[j] == -1) {
                fontJsonFont.set_null("/textures/" + std::to_string(j) + "");
                continue;
            }
            std::string texBuildId = AssetsHelper::get_build_id_of_index(_settings, "ASSET_TEXTURES_2D", font.textureIndices[j]);
            fontJsonFont.set_string("/textures/" + std::to_string(j) + "", texBuildId);
        }
        
        for(int j = FONTS_START_CHAR; j < FONTS_START_CHAR + FONTS_NUMBER_OF_CHARACTERS; j++) {
            FontCharacter &charInfo = font.characters[j - FONTS_START_CHAR];
            
            std::string charPtr = "/characters/";
            
            if(j == '~') {
                charPtr += "~0"; // Tilde
            } else if(j == '/') {
                charPtr += "~1"; // Frontslash
            } else if(j == 127) {
                charPtr += "DEL"; // Delete
            } else {
                charPtr += (char)j;
            }
            
            fontJsonFont.set_int(charPtr + "/tex-index", charInfo.texIndex);
            fontJsonFont.set_int_if_not_zero(charPtr + "/char-width", charInfo.charWidth);
            fontJsonFont.set_int_if_not_zero(charPtr + "/offset/x", charInfo.offsetX);
            fontJsonFont.set_int_if_not_zero(charPtr + "/offset/y", charInfo.offsetY);
            fontJsonFont.set_int(charPtr + "/uv/u", charInfo.texU);
            fontJsonFont.set_int(charPtr + "/uv/v", charInfo.texV);
            fontJsonFont.set_int_if_not_zero(charPtr + "/tex-size/width", charInfo.texWidth);
            fontJsonFont.set_int_if_not_zero(charPtr + "/tex-size/height", charInfo.texHeight);
            
        }
        
        fontJsonFont.save();
    }
    
    jsonFile.save();
}

ExtractFonts::~ExtractFonts() {
}
