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

#define TEXTBOX_CMD_ARGS BuildInfo &info_, const std::string &cmdPtr
#define TEXTBOX_CMD_LAMDA(func) [](TEXTBOX_CMD_ARGS) { func(info_, cmdPtr); }


void build_dialog(BuildInfo &info) {
    std::string rawPath = info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildGameText::BuildGameText) \"raw\" not specified!");
    
    if(info.build_to_file()) {
        // Copy file from rawPath to destination path.
        FileHelper::copy(info.localDirectory / rawPath, info.dstPath);
    } else {
        // Read raw file into out
        info.out = FileHelper::read_binary_file(info.localDirectory / rawPath);
    }
}

void textbox_set_font(BuildInfo &info, const std::string &cmdPtr) {
    std::string fontId = info.srcFile->get_string(cmdPtr + "/value");
    JsonFile &fontsFile = AssetsHelper::get_asset_json("ASSET_FONTS");
    uint8_t font = fontsFile.get_index_of_elem_in_array<std::string>("/fonts-order", fontId);
    
    // Write font id
    info.out.push_back(font);
}

void textbox_set_border(BuildInfo &info, const std::string &cmdPtr) {
    size_t offset = info.out.size();
    info.out.resize(offset + sizeof(SetBorderCommand));
    
    SetBorderCommand *borderCmd = reinterpret_cast<SetBorderCommand *>(&info.out[offset]);
    
    borderCmd->left = info.srcFile->get_int(cmdPtr + "/value/left");
    borderCmd->top = info.srcFile->get_int(cmdPtr + "/value/top");
    borderCmd->right = info.srcFile->get_int(cmdPtr + "/value/right");
    borderCmd->bottom = info.srcFile->get_int(cmdPtr + "/value/bottom");
}

void textbox_set_colour(BuildInfo &info, const std::string &cmdPtr) {
    size_t offset = info.out.size();
    info.out.resize(offset + sizeof(SetColourCommand));
    
    SetColourCommand *colourCmd = reinterpret_cast<SetColourCommand *>(&info.out[offset]);
    
    colourCmd->red = info.srcFile->get_int(cmdPtr + "/value/red");
    colourCmd->green = info.srcFile->get_int(cmdPtr + "/value/green");
    colourCmd->blue = info.srcFile->get_int(cmdPtr + "/value/blue");
    colourCmd->alpha = info.srcFile->get_int(cmdPtr + "/value/alpha");
}

void textbox_set_alignment(BuildInfo &info, const std::string &cmdPtr) {
    std::string alignment = info.srcFile->get_string_lowercase(cmdPtr + "/value");
    
    if(alignment == "center") {
        info.out.push_back(0);
    } else { // alignment == "left"
        info.out.push_back(1);
    }
}

void textbox_unknown7(BuildInfo &info, const std::string &cmdPtr) {
    info.out.push_back(info.srcFile->get_int(cmdPtr + "/value"));
}

void textbox_add_vertical_spacing(BuildInfo &info, const std::string &cmdPtr) {
    info.out.push_back(info.srcFile->get_int(cmdPtr + "/value"));
}

void textbox_set_line_height(BuildInfo &info, const std::string &cmdPtr) {
    info.out.push_back(info.srcFile->get_int(cmdPtr + "/value"));
}

void textbox_set_timer(BuildInfo &info, const std::string &cmdPtr) {
    info.out.push_back(info.srcFile->get_int(cmdPtr + "/value"));
}

void textbox_allow_user_input(BuildInfo &info, const std::string &cmdPtr) {
    info.out.push_back(info.srcFile->get_int(cmdPtr + "/value"));
}

void textbox_text(BuildInfo &info, const std::string &cmdPtr) {
    std::string valueStr = info.srcFile->get_string(cmdPtr + "/value");
    size_t valueStrLen = valueStr.size();
    int offset = info.out.size();
    
    // Expand `out` to include the string.
    info.out.resize(info.out.size() + valueStrLen + 1); // +1 for the NULL terminator.
    
    char *outText = reinterpret_cast<char *>(&info.out[offset]);
    std::strncpy(outText, valueStr.c_str(), valueStrLen); // Copy text to info.out.
    outText[valueStrLen] = '\0'; // Add Null terminator to the end of the string.
}

void build_textbox(BuildInfo &info) {
    if(!info.srcFile->has("/pages")) {
        // No pages means it is an empty file!
        FileHelper::write_empty_file(info.dstPath, true);
        return;
    }
    
    size_t numberOfPages = info.srcFile->length_of_array("/pages");
    
    for(size_t page = 0; page < numberOfPages; page++) {
        std::string pagePtr = "/pages/" + std::to_string(page);
        size_t numberOfCmds = info.srcFile->length_of_array(pagePtr);
        for(size_t cmd = 0; cmd < numberOfCmds; cmd++) {
            std::string cmdPtr = pagePtr + "/" + std::to_string(cmd);
            std::string command = info.srcFile->get_string(cmdPtr + "/command");
            
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
            
            cmdFunctions.at(command)(info, cmdPtr);
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
        FileHelper::write_binary_file(info.out, info.dstPath, true);
    }
}


void BuildGameText::build(BuildInfo &info) {
    // Get text-type as lowercase to make sure it is case-insensitive
    std::string textType = info.srcFile->get_string_lowercase("/text-type", "not_set");
    
    if(textType == "dialog") {
        build_dialog(info);
    } else if(textType == "textbox") {
        build_textbox(info);
    } else {
        DebugHelper::error("Invalid text type: ", textType);
    }
}
