#include "extractGameText.h"

using namespace DkrAssetsTool;

#include "fileTypes/gameText.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/assetsHelper.h"

ExtractGameText::ExtractGameText(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Game Text", YELLOW_TEXT, _outFilepath);
    
    std::vector<uint8_t> rawBytes;
    _info.get_data_from_rom(rawBytes);
    
    bool isDialog = _info.get_tag<bool>("dialog", false);
    
    WritableJsonFile jsonFile(_outFilepath);
    
    jsonFile.set_string("/text-type", isDialog ? "Dialog" : "Textbox");
    jsonFile.set_string("/type", "GameText");
    
    if(isDialog) {
        _extract_dialog(jsonFile, rawBytes);
    } else {
        _extract_textbox(jsonFile, rawBytes);
    }
    
    jsonFile.save();
}

ExtractGameText::~ExtractGameText() {
}

void ExtractGameText::_extract_dialog(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes) {
    fs::path _outRawFilepath = _settings.pathToAssets / _info.get_out_filepath(".bin");
    jsonFile.set_path("/raw", _info.get_filename(".bin"));
    FileHelper::write_binary_file(rawBytes, _outRawFilepath, true);
}

void ExtractGameText::_extract_textbox(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes) {
    int currentPage = 0;
    int commandCount = 0;
    std::string topPtr = "/pages";
    std::string middlePtr = topPtr + "/" + std::to_string(currentPage);
    
    bool end = false;
    
    size_t offset = 0;
    size_t dataLength = rawBytes.size();
    
    while((offset < dataLength) && !end) {
        uint8_t command = rawBytes[offset++];
        std::string ptr = middlePtr + "/" + std::to_string(commandCount++);
        
        switch(command) {
            case 0: // End of textbox commands
                end = true;
                break;
            case 1: // Next page
                currentPage++;
                middlePtr = topPtr + "/" + std::to_string(currentPage);
                ptr = middlePtr + "/" + std::to_string(commandCount);
                commandCount = 0;
                break;
            case 2: // Unused
                break;
            case 3: // Set Font
            {
                SetFontCommand *fontCmd = reinterpret_cast<SetFontCommand *>(&rawBytes[offset]);
                JsonFile *fontsFile = AssetsHelper::get_asset_json(_settings, "ASSET_FONTS");
                std::string fontBuildId = fontsFile->get_string("/fonts-order/" + std::to_string(fontCmd->fontId));
                DebugHelper::assert(!fontBuildId.empty(), "(ExtractGameText::_extract_textbox) Invalid font id: ", fontCmd->fontId);
                jsonFile.set_string(ptr + "/command", TEXTBOX_COMMANDS[command]);
                jsonFile.set_string(ptr + "/value", fontBuildId);
                offset += sizeof(SetFontCommand);
                break;
            }
            case 4: // Set Border
            {
                SetBorderCommand *borderCmd = reinterpret_cast<SetBorderCommand *>(&rawBytes[offset]);
                jsonFile.set_string(ptr + "/command", TEXTBOX_COMMANDS[command]);
                jsonFile.set_int(ptr + "/value/left", borderCmd->left);
                jsonFile.set_int(ptr + "/value/top", borderCmd->top);
                jsonFile.set_int(ptr + "/value/right", borderCmd->right);
                jsonFile.set_int(ptr + "/value/bottom", borderCmd->bottom);
                offset += sizeof(SetBorderCommand);
                break;
            }
            case 5: // Set Colour
            {
                SetColourCommand *colourCmd = reinterpret_cast<SetColourCommand *>(&rawBytes[offset]);
                jsonFile.set_string(ptr + "/command", TEXTBOX_COMMANDS[command]);
                jsonFile.set_int(ptr + "/value/red", colourCmd->red);
                jsonFile.set_int(ptr + "/value/green", colourCmd->green);
                jsonFile.set_int(ptr + "/value/blue", colourCmd->blue);
                jsonFile.set_int(ptr + "/value/alpha", colourCmd->alpha);
                offset += sizeof(SetColourCommand);
                break;
            }
            case 6: // Set Alignment
            {
                SetAlignmentCommand *alignCmd = reinterpret_cast<SetAlignmentCommand *>(&rawBytes[offset]);
                jsonFile.set_string(ptr + "/command", TEXTBOX_COMMANDS[command]);
                jsonFile.set_string(ptr + "/value", (alignCmd->value == 0) ? "center" : "left");
                offset += sizeof(SetAlignmentCommand);
                break;
            }
            case 7: // Currently unknown
            {
                Unknown7Command *unk7Cmd = reinterpret_cast<Unknown7Command *>(&rawBytes[offset]);
                jsonFile.set_string(ptr + "/command", TEXTBOX_COMMANDS[command]);
                jsonFile.set_int(ptr + "/value", unk7Cmd->value);
                offset += sizeof(Unknown7Command);
                break;
            }
            case 8: // Add Vertical Spacing
            {
                AddVerticalSpacingCommand *vertSpacingCmd = reinterpret_cast<AddVerticalSpacingCommand *>(&rawBytes[offset]);
                jsonFile.set_string(ptr + "/command", TEXTBOX_COMMANDS[command]);
                jsonFile.set_int(ptr + "/value", vertSpacingCmd->value);
                offset += sizeof(AddVerticalSpacingCommand);
                break;
            }
            case 9: // Set Line Height
            {
                SetLineHeightCommand *lineHeightCmd = reinterpret_cast<SetLineHeightCommand *>(&rawBytes[offset]);
                jsonFile.set_string(ptr + "/command", TEXTBOX_COMMANDS[command]);
                jsonFile.set_int(ptr + "/value", lineHeightCmd->value);
                offset += sizeof(SetLineHeightCommand);
                break;
            }
            case 10: // Set Timer
            {
                SetTimerCommand *timerCmd = reinterpret_cast<SetTimerCommand *>(&rawBytes[offset]);
                jsonFile.set_string(ptr + "/command", TEXTBOX_COMMANDS[command]);
                jsonFile.set_int(ptr + "/value", timerCmd->value);
                offset += sizeof(SetTimerCommand);
                break;
            }
            case 11: // Allow User Input
            {
                AllowUserInputCommand *userInputCmd = reinterpret_cast<AllowUserInputCommand *>(&rawBytes[offset]);
                jsonFile.set_string(ptr + "/command", TEXTBOX_COMMANDS[command]);
                jsonFile.set_int(ptr + "/value", userInputCmd->value);
                offset += sizeof(AllowUserInputCommand);
                break;
            }
            default:
            {
                char *text = reinterpret_cast<char *>(&rawBytes[--offset]);
                jsonFile.set_string(ptr + "/command", "Text");
                jsonFile.set_string(ptr + "/value", text);
                while(rawBytes[offset] != 0) {
                    offset++;
                }
                offset++;
                break;
            }
        }
    }
}


