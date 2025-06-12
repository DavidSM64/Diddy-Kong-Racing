#include "buildJpFonts.h"

#include "fileTypes/jpFonts.hpp"
#include "fileTypes/texture.hpp"

#include "helpers/dataHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/imageHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/assetsHelper.h"

#include "misc/globalSettings.h"

#include "libs/bytes_view.hpp"

#include "text/dkrText.h"

#include "builder/buildInfoCollection.h"

using namespace DkrAssetsTool;

void build_v77_beta_font(BuildInfo &info, const JsonFile &jsonFile) {
    DeferredAssetInfo deferInfo = AssetsHelper::get_deferred_asset_info("ASSET_JAPANESE_FONTS_TABLE");
    BuildInfoCollection &collection = info.get_collection();
    
    size_t numberOfFonts = jsonFile.length_of_array("/fonts-order");
    
    std::vector<uint8_t> outJpFontTable(numberOfFonts * sizeof(BetaJpFontHeader));
    
    BytesView outJpFontTableView(outJpFontTable);
    BetaJpFontHeader *headers = outJpFontTableView.data_cast<BetaJpFontHeader>();
    
    std::vector<N64Image> images;
    images.reserve(numberOfFonts);
    
    size_t totalDataSize = 0;
    
    for(size_t fontIndex = 0; fontIndex < numberOfFonts; fontIndex++) {
        std::string fontBuildId = jsonFile.get_string("/fonts-order/" + std::to_string(fontIndex));
        
        std::string fontLocalFilepath = jsonFile.get_string("/fonts/" + fontBuildId);
        
        DebugHelper::assert_(!fontLocalFilepath.empty(), 
            "(BuildJpFonts::build_v77_beta_font) Could not find a filepath for jp font \"", fontBuildId, "\"");
        
        fs::path fontFilepath = info.get_path_to_directory() / fontLocalFilepath;
        
        auto tryGetFontJsonFile = JsonHelper::get_file(fontFilepath);
        
        DebugHelper::assert_(tryGetFontJsonFile.has_value(), 
            "(BuildJpFonts::build_v77_beta_font) Could not find the file ", fontFilepath);
            
        JsonFile &fontJsonFile = tryGetFontJsonFile.value();
        
        fs::path imgPath = fontJsonFile.get_filepath().parent_path() / fontJsonFile.get_string("/image/filename");
        std::string imgFormat = fontJsonFile.get_string("/image/format", "I4");
        
        DebugHelper::assert_(imgFormat == "I4", 
            "(BuildJpFonts::build_v77_beta_font) The image format \"", imgFormat, 
            "\" is currently not supported for beta JP fonts. Only I4 images are supported at the moment. Sorry!");
            
        //DebugHelper::info(fontJsonFile.get_filepath());
        
        images.emplace_back(imgPath, imgFormat);
        
        size_t imgWidth = images[fontIndex].get_width();
        size_t imgHeight = images[fontIndex].get_height();
        
        //DebugHelper::info(fontJsonFile.get_int("/header/unk0"));
        
        headers[fontIndex].unk0 = fontJsonFile.get_int("/header/unk0");
        headers[fontIndex].x = fontJsonFile.get_int("/header/x");
        headers[fontIndex].y = fontJsonFile.get_int("/header/y");
        headers[fontIndex].charWidth = fontJsonFile.get_int("/header/charWidth");
        headers[fontIndex].height = fontJsonFile.get_int("/header/height");
        headers[fontIndex].unk5 = fontJsonFile.get_int("/header/unk5");
        headers[fontIndex].imgWidth = imgWidth;
        headers[fontIndex].unk8 = fontJsonFile.get_int("/header/unk8");
        headers[fontIndex].unkA = fontJsonFile.get_int("/header/unkA");
        headers[fontIndex].unkC = totalDataSize; // Not sure about this! Not like it is getting used anyway.
        
        totalDataSize += (imgWidth * imgHeight) / 2;
    }
       
    info.out.resize(totalDataSize);
    
    size_t curOutOffset = 0;
    for(size_t i = 0; i < numberOfFonts; i++) {
        BytesView outImgData(info.out, curOutOffset);
        N64Image &curImg = images[i];
        
        curImg.flip_vertically(); // Was flipped vertically during extraction, now I need to flip it back.
        
        uint8_t *imgData = curImg.get_img_as_ia16(); // Must be freed!
        
        size_t imgWidth = images[i].get_width();
        size_t imgHeight = images[i].get_height();
        
        size_t numberOfBytes = (imgWidth * imgHeight) / 2;
        
        for(size_t j = 0; j < numberOfBytes; j++) {
            uint8_t a = imgData[j * 4];     // Should be either 0xFF or 0x00
            uint8_t b = imgData[j * 4 + 2]; // Should be either 0xFF or 0x00
            
            if(a == 0xFF) {
                a = 0x10;
            }
            if(b == 0xFF) {
                b = 0x1;
            }
            outImgData[j] = a | b;
        }
        
        curOutOffset += numberOfBytes;
        
        free(imgData);
    }
    
    //outJpFontTableView.print(0, outJpFontTable.size());
    
    // Add jp font table to build collection.
    collection.add_deferred_build_info("ASSET_JAPANESE_FONTS_TABLE", "ASSET_JAPANESE_FONTS_TABLE", info.get_build_id(), 
        info.get_section_build_id(), outJpFontTable,info.get_dst_folder() / deferInfo.outputPath, info.get_info_context());
    
}

void build_v79_jp_fonts(BuildInfo &info, const JsonFile &jsonFile) {
    DeferredAssetInfo deferInfo = AssetsHelper::get_deferred_asset_info("ASSET_JAPANESE_FONTS_TABLE");
    BuildInfoCollection &collection = info.get_collection();
    
    size_t numberOfFonts = jsonFile.length_of_array("/fonts-order");
    
    std::vector<uint8_t> outJpFontTable(numberOfFonts * sizeof(JpFontHeader));
    
    BytesView outJpFontTableView(outJpFontTable);
    JpFontHeader *headers = outJpFontTableView.data_cast<JpFontHeader>();
    
    size_t totalDataSize = 0;
    
    std::vector<std::pair<be_int32_t, be_int32_t>> fontImageOffsets(numberOfFonts);
    std::vector<fs::path> fontJsonPaths(numberOfFonts);
    
    // First loop to fill in the font headers and get offsets;
    for(size_t fontIndex = 0; fontIndex < numberOfFonts; fontIndex++) {
        std::string fontBuildId = jsonFile.get_string("/fonts-order/" + std::to_string(fontIndex));
        
        std::string fontLocalFilepath = jsonFile.get_string("/fonts/" + fontBuildId);
        
        DebugHelper::assert_(!fontLocalFilepath.empty(), 
            "(BuildJpFonts::build_v79_jp_fonts) Could not find a filepath for jp font \"", fontBuildId, "\"");
        
        fontJsonPaths[fontIndex] = info.get_path_to_directory() / fontLocalFilepath;
        
        auto tryGetFontJsonFile = JsonHelper::get_file(fontJsonPaths[fontIndex]);
        
        DebugHelper::assert_(tryGetFontJsonFile.has_value(), 
            "(BuildJpFonts::build_v79_jp_fonts) Could not find the file ", fontJsonPaths[fontIndex]);
            
        JsonFile &fontJsonFile = tryGetFontJsonFile.value();
        
        headers[fontIndex].unk0 = fontJsonFile.get_int("/header/unk0");
        headers[fontIndex].cellWidth = fontJsonFile.get_int("/header/cellWidth");
        headers[fontIndex].cellHeight = fontJsonFile.get_int("/header/cellHeight");
        headers[fontIndex].charWidth = fontJsonFile.get_int("/header/charWidth");
        headers[fontIndex].height = fontJsonFile.get_int("/header/height");
        headers[fontIndex].unk5 = fontJsonFile.get_int("/header/unk5");
        headers[fontIndex].unk6 = fontJsonFile.get_int("/header/unk6");
        headers[fontIndex].unk7 = fontJsonFile.get_int("/header/unk7");
        
        headers[fontIndex].offset = totalDataSize;
        
        size_t bytesPerCharacter = sizeof(JpFontChar);
        fontImageOffsets[fontIndex].first = bytesPerCharacter;
        
        fs::path colorImgFilename = fontJsonFile.get_string("/image/filename");
        fs::path colorImageFilepath = fontJsonFile.get_filepath().parent_path() / colorImgFilename;
        int imgWidth, imgHeight; 
        ImageHelper::get_width_and_height(colorImageFilepath, imgWidth, imgHeight);
        
        DebugHelper::assert_(imgWidth % 16 == 0, 
            "(BuildJpFonts::build_v79_jp_fonts) ", colorImgFilename, " width of ", imgWidth, " is not divisible by 16!");
        DebugHelper::assert_(imgHeight % 16 == 0, 
            "(BuildJpFonts::build_v79_jp_fonts) ", colorImgFilename, " height of ", imgHeight, " is not divisible by 16!");
            
        int cellWidth = imgWidth / 16;
        int cellHeight = imgHeight / 16;
        
        std::string colorImageFormat = fontJsonFile.get_string("/image/format", "RGBA16");
        
        size_t colorImgSize = ImageHelper::image_size(cellWidth, cellHeight, colorImageFormat);
        bytesPerCharacter += colorImgSize;
        
        bool hasAlphaImage = fontJsonFile.has("/image-alpha/filename");
        
        if(hasAlphaImage) {
            fontImageOffsets[fontIndex].second = bytesPerCharacter;
            std::string alphaImageFormat = fontJsonFile.get_string("/image-alpha/format", "I4");
            bytesPerCharacter += ImageHelper::image_size(cellWidth, cellHeight, alphaImageFormat);
        } else {
            fontImageOffsets[fontIndex].second = -1; // JpFontChar.offsetToSecondImg is -1 if there is no alpha image.
        }
        
        headers[fontIndex].bytesPerCharacter = bytesPerCharacter;
        totalDataSize += bytesPerCharacter * 256;
    }
    
    info.out.resize(totalDataSize);
    BytesView outFontImagesBytesView(info.out);
    
    const std::vector<std::string> &DKRJP_FONT_CHARACTERS = DKRText::get_dkrjp_characters();

    std::string charactersPtr = "/characters/";
            
    // Second loop to build the data for each font.
    for(size_t fontIndex = 0; fontIndex < numberOfFonts; fontIndex++) {
        size_t bytesPerCharacter = headers[fontIndex].bytesPerCharacter;
        size_t sizeOfFont = bytesPerCharacter * 256;
        BytesView outFontImgBytesView = outFontImagesBytesView.get_sub_view(headers[fontIndex].offset, sizeOfFont);
        
        // Already checked the existance of the file in the previous loop, so it *should* be safe to just do value() here.
        JsonFile &fontJsonFile = JsonHelper::get_file(fontJsonPaths[fontIndex]).value();
        bool hasAlphaImage = fontJsonFile.has("/image-alpha/filename");
        
        std::string colorImageFormat = fontJsonFile.get_string("/image/format", "RGBA16");
            
        fs::path colorImageFilepath = fontJsonFile.get_filepath().parent_path() / fontJsonFile.get_string("/image/filename");
        N64Image colorImage = ImageHelper::load_image(colorImageFilepath, colorImageFormat);
        colorImage.interlace();
        
        N64Image alphaImage;
        std::string alphaImageFormat = fontJsonFile.get_string("/image-alpha/format", "I4");
        if(hasAlphaImage) {
            fs::path alphaImageFilepath = fontJsonFile.get_filepath().parent_path() / fontJsonFile.get_string("/image-alpha/filename");
            alphaImage = ImageHelper::load_image(alphaImageFilepath, alphaImageFormat);
            alphaImage.interlace();
        }
        
        uint8_t colorImageFormatInt = DataHelper::vector_index_of<std::string>(TEXTURE_FORMAT_INT_TO_STRING, colorImageFormat);
        uint8_t alphaImageFormatInt = DataHelper::vector_index_of<std::string>(TEXTURE_FORMAT_INT_TO_STRING, alphaImageFormat);
        
        for(size_t charIndex = 0; charIndex < 256; charIndex++) {
            std::string jpChar = DKRJP_FONT_CHARACTERS[charIndex];
            
            if(jpChar.empty()) {
                jpChar = "<NULL>";
            } else if(jpChar == "/") {
                jpChar = "~1"; // Frontslash
            }
            
            std::string charPtr = charactersPtr + jpChar;
            
            BytesView outCharImgBytesView = outFontImgBytesView.get_sub_view(charIndex * bytesPerCharacter, bytesPerCharacter);
            JpFontChar *outChar = outCharImgBytesView.data_cast<JpFontChar>();
            
            outChar->offsetToFirstImg = fontImageOffsets[fontIndex].first;
            outChar->offsetToSecondImg = fontImageOffsets[fontIndex].second;
            outChar->firstImageFormat = colorImageFormatInt;
            outChar->secondImageFormat = alphaImageFormatInt;
            outChar->spacing = fontJsonFile.get_int(charPtr + "/spacing", 0);
            // TODO: Calculate these automatically.
            outChar->left = fontJsonFile.get_int(charPtr + "/left", 0);
            outChar->top = fontJsonFile.get_int(charPtr + "/top", 0);
            outChar->right = fontJsonFile.get_int(charPtr + "/right", 0);
            outChar->bottom = fontJsonFile.get_int(charPtr + "/bottom", 0);
            
            int x = (charIndex % 16) * headers[fontIndex].cellWidth;
            int y = (charIndex / 16) * headers[fontIndex].cellHeight;
            
            N64Image::Region region = { x, y, x + headers[fontIndex].cellWidth, y + headers[fontIndex].cellHeight };
            
            uint8_t *outCharColorData = (uint8_t*)outCharImgBytesView.data() + outChar->offsetToFirstImg;
            colorImage.copy_data_from_region(outCharColorData, headers[fontIndex].cellWidth, region);
            
            if(hasAlphaImage) {
                uint8_t *outCharAlphaData = (uint8_t*)outCharImgBytesView.data() + outChar->offsetToSecondImg;
                alphaImage.copy_data_from_region(outCharAlphaData, headers[fontIndex].cellWidth, region);
            }
        }
        
    }
    
    // Add jp font table to build collection.
    collection.add_deferred_build_info("ASSET_JAPANESE_FONTS_TABLE", "ASSET_JAPANESE_FONTS_TABLE", info.get_build_id(), 
        info.get_section_build_id(), outJpFontTable,info.get_dst_folder() / deferInfo.outputPath, info.get_info_context());
}

void BuildJPFonts::build(BuildInfo &info) {
    const JsonFile &jsonFile = info.get_src_json_file();
    
    //size_t numberOfFonts = jsonFile.length_of_array("/fonts-order");
    
    //size_t outSize = FileHelper::align16(sizeof(be_uint32_t) + (numberOfFonts * sizeof(FontFile)));
    //info.out.resize(outSize);
    
    // Note: The format is different in v79/v80. So gotta check if this is the beta version of the JP font.
    bool isBetaJpFont = StringHelper::ends_with(GlobalSettings::get_dkr_version(), "v77");
    
    if(isBetaJpFont) {
        build_v77_beta_font(info, jsonFile);
    } else {
        // v79/v80
        build_v79_jp_fonts(info, jsonFile);
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
