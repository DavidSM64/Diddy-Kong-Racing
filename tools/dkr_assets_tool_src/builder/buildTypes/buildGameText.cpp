#include "buildGameText.h"

#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <functional>

#include "helpers/assetsHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/dataHelper.h"

#include "fileTypes/gameText.hpp"


#define TEXTBOX_CMD_ARGS std::vector<uint8_t> &out, const std::string &cmdPtr
#define TEXTBOX_CMD_LAMDA(func) [this](TEXTBOX_CMD_ARGS) { func(out, cmdPtr); }

//typedef void (*MiscFuncPtr)(MISC_ARGS);

BuildGameText::BuildGameText(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    // Get text-type as lowercase to make sure it is case-insensitive
    std::string textType = _info.srcFile->get_string_lowercase("/text-type", "not_set");
    
    if(textType == "dialog") {
        _build_dialog();
    } else if(textType == "textbox") {
        _build_textbox();
    } else {
        DebugHelper::error("Invalid text type: ", textType);
    }
}

BuildGameText::~BuildGameText() {
    
}

void BuildGameText::_build_dialog() {
    std::string rawPath = _info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildGameText::BuildGameText) \"raw\" not specified!");
    
    // Copy file from rawPath to destination path.
    FileHelper::copy(_info.localDirectory / rawPath, _info.dstPath);
}

void BuildGameText::_textbox_set_font(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    std::string fontId = _info.srcFile->get_string(cmdPtr + "/value");
    JsonFile *fontsFile = AssetsHelper::get_asset_json(_settings, "ASSET_FONTS");
    uint8_t font = fontsFile->get_index_of_elem_in_array<std::string>("/fonts-order", fontId);
    
    // Write font id
    out.push_back(font);
}

void BuildGameText::_textbox_set_border(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    size_t offset = out.size();
    out.resize(offset + sizeof(SetBorderCommand));
    
    SetBorderCommand *borderCmd = reinterpret_cast<SetBorderCommand *>(&out[offset]);
    
    borderCmd->left = _info.srcFile->get_int(cmdPtr + "/value/left");
    borderCmd->top = _info.srcFile->get_int(cmdPtr + "/value/top");
    borderCmd->right = _info.srcFile->get_int(cmdPtr + "/value/right");
    borderCmd->bottom = _info.srcFile->get_int(cmdPtr + "/value/bottom");
}

void BuildGameText::_textbox_set_colour(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    size_t offset = out.size();
    out.resize(offset + sizeof(SetColourCommand));
    
    SetColourCommand *colourCmd = reinterpret_cast<SetColourCommand *>(&out[offset]);
    
    colourCmd->red = _info.srcFile->get_int(cmdPtr + "/value/red");
    colourCmd->green = _info.srcFile->get_int(cmdPtr + "/value/green");
    colourCmd->blue = _info.srcFile->get_int(cmdPtr + "/value/blue");
    colourCmd->alpha = _info.srcFile->get_int(cmdPtr + "/value/alpha");
}

void BuildGameText::_textbox_set_alignment(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    std::string alignment = _info.srcFile->get_string_lowercase(cmdPtr + "/value");
    
    if(alignment == "center") {
        out.push_back(0);
    } else { // alignment == "left"
        out.push_back(1);
    }
}

void BuildGameText::_textbox_unknown7(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    out.push_back(_info.srcFile->get_int(cmdPtr + "/value"));
}

void BuildGameText::_textbox_add_vertical_spacing(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    out.push_back(_info.srcFile->get_int(cmdPtr + "/value"));
}

void BuildGameText::_textbox_set_line_height(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    out.push_back(_info.srcFile->get_int(cmdPtr + "/value"));
}

void BuildGameText::_textbox_set_timer(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    out.push_back(_info.srcFile->get_int(cmdPtr + "/value"));
}

void BuildGameText::_textbox_allow_user_input(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    out.push_back(_info.srcFile->get_int(cmdPtr + "/value"));
}

void BuildGameText::_textbox_text(std::vector<uint8_t> &out, const std::string &cmdPtr) {
    std::string valueStr = _info.srcFile->get_string(cmdPtr + "/value");
    size_t valueStrLen = valueStr.size();
    int offset = out.size();
    
    // Expand `out` to include the string.
    out.resize(out.size() + valueStrLen + 1); // +1 for the NULL terminator.
    
    char *outText = reinterpret_cast<char *>(&out[offset]);
    std::strncpy(outText, valueStr.c_str(), valueStrLen); // Copy text to out.
    outText[valueStrLen] = '\0'; // Add Null terminator to the end of the string.
}

void BuildGameText::_build_textbox() {
    if(!_info.srcFile->has("/pages")) {
        // No pages means it is an empty file!
        FileHelper::write_empty_file(_info.dstPath, true);
        return;
    }
    
    std::vector<uint8_t> out;
    
    size_t numberOfPages = _info.srcFile->length_of_array("/pages");
    
    for(size_t page = 0; page < numberOfPages; page++) {
        std::string pagePtr = "/pages/" + std::to_string(page);
        size_t numberOfCmds = _info.srcFile->length_of_array(pagePtr);
        for(size_t cmd = 0; cmd < numberOfCmds; cmd++) {
            std::string cmdPtr = pagePtr + "/" + std::to_string(cmd);
            std::string command = _info.srcFile->get_string(cmdPtr + "/command");
            
            const std::unordered_map<std::string, std::function<void(TEXTBOX_CMD_ARGS)>> cmdFunctions = {
                {            "SetFont", TEXTBOX_CMD_LAMDA(_textbox_set_font)             },
                {          "SetBorder", TEXTBOX_CMD_LAMDA(_textbox_set_border)           },
                {          "SetColour", TEXTBOX_CMD_LAMDA(_textbox_set_colour)           },
                {       "SetAlignment", TEXTBOX_CMD_LAMDA(_textbox_set_alignment)        },
                {           "Unknown7", TEXTBOX_CMD_LAMDA(_textbox_unknown7)             },
                { "AddVerticalSpacing", TEXTBOX_CMD_LAMDA(_textbox_add_vertical_spacing) },
                {      "SetLineHeight", TEXTBOX_CMD_LAMDA(_textbox_set_line_height)      },
                {           "SetTimer", TEXTBOX_CMD_LAMDA(_textbox_set_timer)            },
                {     "AllowUserInput", TEXTBOX_CMD_LAMDA(_textbox_allow_user_input)     },
                {               "Text", TEXTBOX_CMD_LAMDA(_textbox_text)                 },
            };
            
            // Make sure the misc type has a function to extract it.
            DebugHelper::assert(cmdFunctions.find(command) != cmdFunctions.end(), 
                "(BuildGameText::_build_textbox) Invalid textbox command: ", command);
            
            if(command != "Text") {
                int commandIndex = std::find(TEXTBOX_COMMANDS.begin(), TEXTBOX_COMMANDS.end(), command) - TEXTBOX_COMMANDS.begin();
                out.push_back(commandIndex); // Add command byte to out
            }
            
            cmdFunctions.at(command)(out, cmdPtr);
        }
        if(page < numberOfPages - 1) {
            out.push_back(1); // cmd 0x01 means next-page.
        }
    }
    
    // TODO: Probably should pre-allocate the correct size.
    if((out.size() & 0x7)) {
        out.resize(DataHelper::align8(out.size()), 0);
    }
    
    FileHelper::write_binary_file(out, _info.dstPath, true);
}
