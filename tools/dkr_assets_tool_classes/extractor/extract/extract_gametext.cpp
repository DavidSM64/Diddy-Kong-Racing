#include "extract_gametext.h"

ExtractGameText::ExtractGameText(std::string key, std::vector<uint8_t> data, std::string outFilepath, 
  std::unordered_map<std::string, std::string> *tags) : Extract(key, data, outFilepath) {    
    json::JSON out = json::Object();
    bool isDialog = false;
    
    out["type"] = "GameText";
    
    if(tags != nullptr) {
        out["text-type"] = (*tags)["text-type"];
        isDialog = (out["text-type"].ToString() == "Dialog");
    }
    
    if(isDialog) {
        // Uncomment this when the formats have been fully figured out.
        //extract_dialog(out, data);
        // Remove this raw part when dialog has been figured out.
        out["raw"] = json::Array();
        size_t dataLength = data.size();
        for(int i = 0; i < dataLength; i++) {
            out["raw"].append(data[i]);
        }
    } else { // Textbox
        extract_textbox(out, data);
    }

    write_json(out, outFilepath);
    print_extracted();
}

ExtractGameText::~ExtractGameText() {
}

void ExtractGameText::extract_dialog(json::JSON &out, std::vector<uint8_t> &data) {
    out["lines"] = json::Array();
    
    size_t offset = 0;
    size_t dataLength = data.size();
    
    while(offset < dataLength) {
        if(data[offset++] == 1) {
            json::JSON line = json::Object();
            line["color"] = json::Object();
            line["color"]["red"] = data[offset++];
            line["color"]["green"] = data[offset++];
            line["color"]["blue"] = data[offset++];
            line["color"]["alpha"] = data[offset++];
            line["font"] = data[offset++];
            line["alignment"] = data[offset++];
            line["time"] = (data[offset++] * 6.0f) / 30.0f;
            uint8_t c = data[offset++];
            std::stringstream rawTextStream;
            while(c != 0) {
                rawTextStream << (char)c;
                c = data[offset++];
            }
            line["text"] = rawTextStream.str();
            out["lines"].append(line);
        }
        if(data[offset++] != 0xC) {
            break;
        } else {
            out["lines"].append("CONTINUE");
        }
    }
    if(offset < dataLength) {
        offset--;
        json::JSON junk = json::Object();
        json::JSON junkData = json::Array();
        while(offset < dataLength) {
            junkData.append(data[offset++]);
        }
        junk["unknown-data"] = junkData;
        out["lines"].append(junk);
    }
}

void ExtractGameText::extract_textbox(json::JSON &out, std::vector<uint8_t> &data) {
    size_t offset = 0;
    size_t dataLength = data.size();
    
    out["pages"] = json::Array();
    int currentPage = 0;
    out["pages"].append(json::Array()); // Each page is an array of commands/text.
    
    bool end = false;
    while((offset < dataLength) && !end) {
        json::JSON cmd = json::Object();
        switch(data[offset++]){
            case 0: // End of textbox commands.
                end = true;
                break;
            case 1: // Go to next page.
                currentPage++;
                out["pages"].append(json::Array());
                continue; // Move onto the next command, since there is nothing to add anyway.
            case 2:
                // Not used?
                break;
            case 3:
                cmd["command"] = "SetFont";
                cmd["value"] = data[offset++];
                break;
            case 4:
                cmd["command"] = "SetBorder";
                cmd["value"] = json::Object(); // 0 = Farthest left/top, 0xFF = Farthest right/bottom
                cmd["value"]["Left"] = data[offset++];
                cmd["value"]["Top"] = data[offset++];
                cmd["value"]["Right"] = data[offset++];
                cmd["value"]["Bottom"] = data[offset++];
                break;
            case 5:
                cmd["command"] = "SetColor";
                cmd["value"] = json::Object();
                cmd["value"]["red"]   = data[offset++];
                cmd["value"]["green"] = data[offset++];
                cmd["value"]["blue"]  = data[offset++];
                cmd["value"]["alpha"] = data[offset++];
                break;
            case 6:
                cmd["command"] = "SetAlignment";
                cmd["value"] = (data[offset++] == 0) ? "Center" : "Left";
                break;
            case 7:
                cmd["command"] = "Unknown"; // Doesn't seem to do anything as far as I can tell.
                cmd["value"] = data[offset++];
                break;
            case 8:
                cmd["command"] = "AddVerticalSpacing";
                cmd["value"] = data[offset++];
                break;
            case 9:
                cmd["command"] = "SetLineHeight";
                cmd["value"] = data[offset++];
                break;
            case 10:
                cmd["command"] = "SetTimer";
                cmd["value"] = data[offset++]; // time in seconds.
                break;
            case 11:
                cmd["command"] = "AllowUserInput";
                cmd["value"] = data[offset++] ? true : false;
                break;
            default: // Just regular text.
                uint8_t c = data[--offset];
                std::stringstream rawTextStream;
                while(c != 0) {
                    rawTextStream << (char)c;
                    c = data[++offset];
                }
                offset++;
                cmd["command"] = "Text";
                cmd["value"] = rawTextStream.str();
                break;
        }
        if(!end) {
            out["pages"][currentPage].append(cmd);
        }
    }
}



