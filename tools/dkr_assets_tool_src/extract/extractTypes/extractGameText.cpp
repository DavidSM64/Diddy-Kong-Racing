#include "extractGameText.h"

#include "fileTypes/gameText.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/assetsHelper.h"

#include "extract/stats.h"
#include "text/dkrText.h"

using namespace DkrAssetsTool;

// TODO: Actually extract the dialog into the json instead of it being raw binary.
void extract_dialog(ExtractInfo &info, WritableJsonFile &jsonFile) {
    jsonFile.set_path("/raw", info.get_filename(".bin"));
    jsonFile.set_string("/type", "GameText");
    jsonFile.set_string("/text-type", "Dialog");
    
    info.write_raw_data_file();
}

void extract_textbox(ExtractInfo &info, WritableJsonFile &jsonFile) {
    const ExtractStats &stats = info.get_stats();
    
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
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
                // Fonts should be extracted before GameText, so FONT_N should be a valid tag and return the build id for that font.
                std::string fontBuildId = stats.get_tag<std::string>("FONT_" + std::to_string(fontCmd->fontId), "");
                DebugHelper::assert(!fontBuildId.empty(), "(ExtractGameText::extract_textbox) Invalid font index: ", fontCmd->fontId);
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
                DKRText text(rawBytes, --offset);
                jsonFile.set_string(ptr + "/command", "Text");
                jsonFile.set_string(ptr + "/value", text.get_text());
                offset += text.bytes_size() + 1;
                break;
            }
        }
    }
}

void ExtractGameText::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Game Text", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    bool isDialog = info.get_tag<bool>("isDialog", false);
    
    WritableJsonFile &jsonFile = info.get_json_file();
    
    jsonFile.set_string("/text-type", isDialog ? "Dialog" : "Textbox");
    jsonFile.set_string("/type", "GameText");
    
    if(isDialog) {
        extract_dialog(info, jsonFile);
    } else {
        extract_textbox(info, jsonFile);
    }
    
    info.write_json_file();
}
