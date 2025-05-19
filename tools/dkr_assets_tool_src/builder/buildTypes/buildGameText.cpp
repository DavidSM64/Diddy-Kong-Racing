#include "buildGameText.h"

using namespace DkrAssetsTool;

#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <functional>

#include "helpers/assetsHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

#include "fileTypes/gameText.hpp"

#include "text/dkrText.h"

#define TEXTBOX_CMD_ARGS BuildInfo &info_, const std::string &cmdPtr, const JsonFile &jsonFile
#define TEXTBOX_CMD_LAMDA(func) [](TEXTBOX_CMD_ARGS) { func(info_, cmdPtr, jsonFile); }

void build_dialog(BuildInfo &info, const JsonFile &jsonFile) {
    std::string rawPath = jsonFile.get_string("/raw");
    
    DebugHelper::assert_(!rawPath.empty(), 
        "(BuildGameText::BuildGameText) \"raw\" not specified!");
    
    fs::path dir = info.get_path_to_directory();
    
    if(info.build_to_file()) {
        // Copy file from rawPath to destination path.
        info.copy_to_dstPath(dir / rawPath);
    } else {
        // Load raw binary into info's out
        info.out = FileHelper::read_binary_file(dir / rawPath);
    }
}

void textbox_set_font(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    std::string fontId = jsonFile.get_string(cmdPtr + "/value");
    JsonFile &fontsFile = AssetsHelper::get_asset_json("ASSET_FONTS");
    DebugHelper::assert_(fontsFile.has("/fonts-order"), 
        "(textbox_set_font) fonts.json is missing the `/fonts-order` property!");
    uint8_t font = fontsFile.get_index_of_elem_in_array<std::string>("/fonts-order", fontId);
    
    DebugHelper::assert_(font != 0xFF, "(textbox_set_font) Could not find the font: ", fontId);
    
    // Write font id
    info.out.push_back(font);
}

void textbox_set_border(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    size_t offset = info.out.size();
    info.out.resize(offset + sizeof(SetBorderCommand));
    
    SetBorderCommand *borderCmd = reinterpret_cast<SetBorderCommand *>(&info.out[offset]);
    
    borderCmd->left = jsonFile.get_int(cmdPtr + "/value/left");
    borderCmd->top = jsonFile.get_int(cmdPtr + "/value/top");
    borderCmd->right = jsonFile.get_int(cmdPtr + "/value/right");
    borderCmd->bottom = jsonFile.get_int(cmdPtr + "/value/bottom");
}

void textbox_set_colour(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    size_t offset = info.out.size();
    info.out.resize(offset + sizeof(SetColourCommand));
    
    SetColourCommand *colourCmd = reinterpret_cast<SetColourCommand *>(&info.out[offset]);
    
    colourCmd->red = jsonFile.get_int(cmdPtr + "/value/red");
    colourCmd->green = jsonFile.get_int(cmdPtr + "/value/green");
    colourCmd->blue = jsonFile.get_int(cmdPtr + "/value/blue");
    colourCmd->alpha = jsonFile.get_int(cmdPtr + "/value/alpha");
}

void textbox_set_alignment(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    std::string alignment = jsonFile.get_string_lowercase(cmdPtr + "/value");
    
    if(alignment == "center") {
        info.out.push_back(0);
    } else { // alignment == "left"
        info.out.push_back(1);
    }
}

void textbox_unknown7(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    info.out.push_back(jsonFile.get_int(cmdPtr + "/value"));
}

void textbox_add_vertical_spacing(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    info.out.push_back(jsonFile.get_int(cmdPtr + "/value"));
}

void textbox_set_line_height(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    info.out.push_back(jsonFile.get_int(cmdPtr + "/value"));
}

void textbox_set_timer(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    info.out.push_back(jsonFile.get_int(cmdPtr + "/value"));
}

void textbox_allow_user_input(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    info.out.push_back(jsonFile.get_int(cmdPtr + "/value"));
}

void textbox_text(BuildInfo &info, const std::string &cmdPtr, const JsonFile &jsonFile) {
    std::string valueStr = jsonFile.get_string(cmdPtr + "/value");
    
    DKRText text(valueStr);
    
    std::vector<uint8_t> textBytes = text.get_bytes();
    
    size_t numBytesToCopy = textBytes.size();
    
    int offset = info.out.size();
    
    // Expand `out` to include the string.
    info.out.resize(info.out.size() + numBytesToCopy + 1); // +1 for the NULL terminator.
    
    std::copy(textBytes.begin(), textBytes.begin() + numBytesToCopy, info.out.begin() + offset);
}

void build_textbox(BuildInfo &info, const JsonFile &jsonFile) {
    if(!jsonFile.has("/pages")) {
        if(info.build_to_file()) {
            info.write_empty_file_to_dstPath();
        }
        return;
    }
    
    size_t numberOfPages = jsonFile.length_of_array("/pages");
    
    for(size_t page = 0; page < numberOfPages; page++) {
        std::string pagePtr = "/pages/" + std::to_string(page);
        size_t numberOfCmds = jsonFile.length_of_array(pagePtr);
        for(size_t cmd = 0; cmd < numberOfCmds; cmd++) {
            std::string cmdPtr = pagePtr + "/" + std::to_string(cmd);
            std::string command = jsonFile.get_string(cmdPtr + "/command");
            
            const std::unordered_map<std::string, std::function<void(TEXTBOX_CMD_ARGS)>> cmdFunctions = {
                {            "SetFont", TEXTBOX_CMD_LAMDA(textbox_set_font)             },
                {          "SetBorder", TEXTBOX_CMD_LAMDA(textbox_set_border)           },
                {          "SetColour", TEXTBOX_CMD_LAMDA(textbox_set_colour)           },
                {       "SetAlignment", TEXTBOX_CMD_LAMDA(textbox_set_alignment)        },
                {           "Unknown7", TEXTBOX_CMD_LAMDA(textbox_unknown7)             },
                { "AddVerticalSpacing", TEXTBOX_CMD_LAMDA(textbox_add_vertical_spacing) },
                {      "SetLineHeight", TEXTBOX_CMD_LAMDA(textbox_set_line_height)      },
                {           "SetTimer", TEXTBOX_CMD_LAMDA(textbox_set_timer)            },
                {     "AllowUserInput", TEXTBOX_CMD_LAMDA(textbox_allow_user_input)     },
                {               "Text", TEXTBOX_CMD_LAMDA(textbox_text)                 },
            };
            
            // Make sure the misc type has a function to extract it.
            DebugHelper::assert(cmdFunctions.find(command) != cmdFunctions.end(), 
                "(build_textbox) Invalid textbox command: ", command);
            
            if(command != "Text") {
                int commandIndex = std::find(TEXTBOX_COMMANDS.begin(), TEXTBOX_COMMANDS.end(), command) - TEXTBOX_COMMANDS.begin();
                info.out.push_back(commandIndex); // Add command byte to out
            }
            
            cmdFunctions.at(command)(info, cmdPtr, jsonFile);
        }
        if(page < numberOfPages - 1) {
            info.out.push_back(1); // cmd 0x01 means next-page.
        }
    }
    
    // TODO: Probably should pre-allocate the correct size.
    if((info.out.size() & 0x7)) {
        info.out.resize(DataHelper::align8(info.out.size()), 0);
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}

void BuildGameText::build(BuildInfo &info) {
    const JsonFile &jsonFile = info.get_src_json_file();
    
    // Get text-type as lowercase to make sure it is case-insensitive
    std::string textType = jsonFile.get_string_lowercase("/text-type", "not_set");
    
    if(textType == "dialog") {
        build_dialog(info, jsonFile);
    } else if(textType == "textbox") {
        build_textbox(info, jsonFile);
    } else {
        DebugHelper::error("Invalid text type: ", textType);
    }
}
