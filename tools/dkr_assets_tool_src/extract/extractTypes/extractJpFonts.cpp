#include "extractJpFonts.h"

#include "helpers/assetsHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/imageHelper.h"

#include "misc/globalSettings.h"

#include "libs/bytes_view.hpp"

#include "text/dkrText.h"

#include "fileTypes/jpFonts.hpp"
#include "fileTypes/texture.hpp"

#include "extract/stats.h"

using namespace DkrAssetsTool;

void extract_v77_beta_font(ExtractInfo &info, WritableJsonFile &jsonFile, BytesView &jpFontsTableView) {
    // Only one beta font. Includes a lot of kanji in it. Image is 4-bit 192x732. No palette as far as I know if it is CI4.
    
    BytesView jpFontsDataView = info.get_view();
    
    fs::path outFontFilepath = GlobalSettings::get_decomp_path_to_vanilla_assets() / info.get_out_folder() / "jp_fonts/beta_jp_font.meta.json";
    jsonFile.set_path("/fonts/ASSET_JPFONTS_BETAFONT", "jp_fonts/beta_jp_font.meta.json");
    jsonFile.set_string("/fonts-order/0", "ASSET_JPFONTS_BETAFONT");
    
    WritableJsonFile fontJsonFont(outFontFilepath);
    
    const BetaJpFontHeader *header = jpFontsTableView.data_cast<BetaJpFontHeader>();
    
    fontJsonFont.set_int("/header/unk0", header->unk0);
    fontJsonFont.set_int("/header/x", header->x);
    fontJsonFont.set_int("/header/y", header->y);
    fontJsonFont.set_int("/header/charWidth", header->charWidth);
    fontJsonFont.set_int("/header/height", header->height);
    fontJsonFont.set_int("/header/unk5", header->unk5);
    fontJsonFont.set_int("/header/unk8", header->unk8);
    fontJsonFont.set_int("/header/unkA", header->unkA);
    
    size_t numberOfBytes = jpFontsDataView.size();
    
    size_t imgWidth = header->imgWidth;
    size_t imgHeight = (numberOfBytes * 2) / imgWidth; // Should be 732
    
    // The beta jp font image data only uses 0 or 1, so I'm interpreting 0 as black and 1 as white.
    // With that in mind, I'm using this loop to convert the input data an I4 image.
    for(size_t i = 0; i < numberOfBytes; i++) {
        switch(jpFontsDataView[i]) {
            case 0x01:
                jpFontsDataView[i] = 0x0F;
                break;
            case 0x10:
                jpFontsDataView[i] = 0xF0;
                break;
            case 0x11:
                jpFontsDataView[i] = 0xFF;
                break;
            default:
                // Do nothing
                break;
        }
    }
    
    N64Image betaJPFontImg(imgWidth, imgHeight, "I4");
    
    // Copy input data to the image.
    betaJPFontImg.write_from(jpFontsDataView.data(), numberOfBytes);
    
    fs::path outImgPath = outFontFilepath.replace_extension(".png");
    
    // Image is stored upside-down, so gotta flip it vertically.
    betaJPFontImg.flip_vertically();
    
    // Save beta font image.
    betaJPFontImg.save(outImgPath);
    
    std::string filename = outImgPath.filename().generic_string();
    
    fontJsonFont.set_string("/name", "BetaJpFont");
    fontJsonFont.set_string("/image/filename", filename);
    fontJsonFont.set_string("/image/format", "I4");
    
    fontJsonFont.save();
}

void extract_v79_jp_fonts(ExtractInfo &info, WritableJsonFile &jsonFile, BytesView &jpFontsTableView) {
    BytesView jpFontsDataView = info.get_view();
    
    size_t numberOfFonts = jpFontsTableView.size() / sizeof(JpFontHeader);
    
    fs::path outFontsFolder = GlobalSettings::get_decomp_path_to_vanilla_assets() / info.get_out_folder() / "jp_fonts";
    
    const std::vector<std::string> &DKRJP_FONT_CHARACTERS = DKRText::get_dkrjp_characters();
    
    for(size_t i = 0; i < numberOfFonts; i++) {
        const JpFontHeader *header = jpFontsTableView.data_cast<JpFontHeader>(i * sizeof(JpFontHeader));
        
        std::string buildId = "ASSET_JPFONTS_" + std::to_string(i);
        std::string fontName = "jp_font_" + std::to_string(i);
        std::string filename = fontName + ".meta.json";
        fs::path outFontFilepath = outFontsFolder / filename;
        
        jsonFile.set_path("/fonts/" + buildId, "jp_fonts/" + filename);
        jsonFile.set_string("/fonts-order/" + std::to_string(i), buildId);
        
        WritableJsonFile fontJsonFont(outFontFilepath);
        
        fontJsonFont.set_int("/header/unk0", header->unk0);
        fontJsonFont.set_int("/header/cellWidth", header->cellWidth);
        fontJsonFont.set_int("/header/cellHeight", header->cellHeight);
        fontJsonFont.set_int("/header/charWidth", header->charWidth);
        fontJsonFont.set_int("/header/height", header->height);
        fontJsonFont.set_int("/header/unk5", header->unk5);
        fontJsonFont.set_int("/header/unk6", header->unk6);
        fontJsonFont.set_int("/header/unk7", header->unk7);
        
        size_t offsetToData = header->offset;
        size_t numberOfBytesPerCharacter = header->bytesPerCharacter;
        
        size_t imgWidth = header->cellWidth * 16;
        size_t imgHeight = header->cellHeight * 16;
        
        const JpFontChar *firstChar = jpFontsDataView.data_cast<JpFontChar>(offsetToData);
        
        std::string colorImgFormat = TEXTURE_FORMAT_INT_TO_STRING[firstChar->firstImageFormat];
        std::string alphaImgFormat = TEXTURE_FORMAT_INT_TO_STRING[firstChar->secondImageFormat];
        
        N64Image colorImg(imgWidth, imgHeight, colorImgFormat);
        N64Image alphaImg(imgWidth, imgHeight, alphaImgFormat);
        
        bool hasAlphaImage = (firstChar->offsetToSecondImg != -1);
        
        fontJsonFont.set_string("/image/format", colorImgFormat);
        
        if(hasAlphaImage) {
            fontJsonFont.set_string("/image-alpha/format", alphaImgFormat);
        }
        
        for(size_t charIndex = 0; charIndex < 256; charIndex++) {
            std::string charPointer = "/characters/"; 
            
            std::string jpChar = DKRJP_FONT_CHARACTERS[charIndex];
            
            if(jpChar.empty()) {
                jpChar = "<NULL>";
            } else if(jpChar == "/") {
                jpChar = "~1"; // Frontslash
            }
            
            charPointer += jpChar; 
            
            const JpFontChar *charHeader = jpFontsDataView.data_cast<JpFontChar>(offsetToData);
            
            fontJsonFont.set_int(charPointer + "/spacing", charHeader->spacing);
            
            // TODO: Calculate these automatically.
            fontJsonFont.set_int(charPointer + "/left", charHeader->left);
            fontJsonFont.set_int(charPointer + "/top", charHeader->top);
            fontJsonFont.set_int(charPointer + "/right", charHeader->right);
            fontJsonFont.set_int(charPointer + "/bottom", charHeader->bottom);
            
            uint8_t *colorData = jpFontsDataView.data_cast<uint8_t>(offsetToData + charHeader->offsetToFirstImg);
            
            int x = (charIndex % 16) * header->cellWidth;
            int y = (charIndex / 16) * header->cellHeight;
            
            colorImg.write_data_to_region(colorData, header->cellWidth, { x, y, x + header->cellWidth, y + header->cellHeight } );
            
            if(hasAlphaImage) {
                uint8_t *alphaData = jpFontsDataView.data_cast<uint8_t>(offsetToData + charHeader->offsetToSecondImg);
                
                alphaImg.write_data_to_region(alphaData, header->cellWidth, { x, y, x + header->cellWidth, y + header->cellHeight } );
            }
            
            
            
            offsetToData += numberOfBytesPerCharacter;
        }
        
        fontJsonFont.set_string("/name", fontName);
        
        colorImg.interlace();
        colorImg.save(outFontsFolder / (fontName + ".png"));
        fontJsonFont.set_string("/image/filename", fontName + ".png");
        fontJsonFont.set_string("/image/format", colorImgFormat);
        if(hasAlphaImage) {
            alphaImg.interlace();
            alphaImg.save(outFontsFolder / (fontName + "_alpha.png"));
            fontJsonFont.set_string("/image-alpha/filename", fontName + "_alpha.png");
            fontJsonFont.set_string("/image-alpha/format", alphaImgFormat);
        }
        
        fontJsonFont.save();
    }
}

void ExtractJPFonts::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Japanese Fonts", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    ExtractInfo &jpFontsTableInfo = DeferredExtractions::get_extraction("ASSET_JAPANESE_FONTS_TABLE", 0);
    BytesView jpFontsTableView = jpFontsTableInfo.get_view();
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_string("/type", "JPFonts");
    
    // Note: The format is different in v79/v80. So gotta check if this is the beta version of the JP font.
    bool isBetaJpFont = StringHelper::ends_with(GlobalSettings::get_dkr_version(), "v77");
    
    if(isBetaJpFont) {
        extract_v77_beta_font(info, jsonFile, jpFontsTableView);
    } else {
        // v79/v80, TODO
        extract_v79_jp_fonts(info, jsonFile, jpFontsTableView);
    }
    
    info.write_json_file();
}
