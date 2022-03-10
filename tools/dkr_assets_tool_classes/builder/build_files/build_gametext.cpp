#include "build_gametext.h"

// Dialog
#define END_OF_LINES 0x00
#define ACTIVE_LINE  0x01
#define CONTINUE     0x0C

// Textbox
#define NEXT_PAGE 0x01

BuildGameText::BuildGameText(std::string srcPath, std::string dstPath) {
    std::vector<uint8_t> out;
    
    
    // TODO: Figure this out!
    /*
    std::string textType = get_string_from_json(srcPath, "text-type");
    if(textType == "Dialog") {
        build_dialog(out, inputJSON);
    } else {
        build_textbox(out, inputJSON);
    }
    */

    // This is temporary until the game text format is figured out
    int numRawBytes = get_array_length_from_json(srcPath, "raw");

    for(int i = 0; i < numRawBytes; i++) {
        out.push_back(get_int_from_json(srcPath, "raw", i));
    }
    
    while(out.size() % 8 != 0) {
        out.push_back(0); // Make sure the data is 8-byte aligned.
    }
    
    write_binary_file(out, dstPath);
}

BuildGameText::~BuildGameText() {
    
}

/*
void BuildGameText::build_dialog(std::vector<uint8_t> &out, json::JSON inputJSON) {
    int numberOfLines = GET_ARRAY_LENGTH("lines");
    for(int i = 0; i < numberOfLines; i++) {
        if(inputJSON["lines"][i].JSONType() == json::JSON::Class::String) {
            out.push_back(CONTINUE);
            continue;
        }
        if(HAS_KEY("unknown-data", "lines", i)) { // Check if the key "unknown-data" exists.
            for(int j = 0; j < GET_ARRAY_LENGTH("lines", i, "unknown-data"); j++) {
                out.push_back(get_int_from_json(srcPath, "lines", i, "unknown-data", j));
            }
            break;
        }
        out.push_back(ACTIVE_LINE);
        out.push_back(get_int_from_json(srcPath, "lines", i, "color", "red"));
        out.push_back(get_int_from_json(srcPath, "lines", i, "color", "green"));
        out.push_back(get_int_from_json(srcPath, "lines", i, "color", "blue"));
        out.push_back(get_int_from_json(srcPath, "lines", i, "color", "alpha"));
        out.push_back(get_int_from_json(srcPath, "lines", i, "font"));
        out.push_back(get_int_from_json(srcPath, "lines", i, "alignment"));
        out.push_back((uint8_t)(GET_FLOAT("lines", i, "time") * 5));
        write_ascii(out, get_string_from_json(srcPath, "lines", i, "text"));
        //if(i < numberOfLines - 1 && !HAS_KEY("unknown-data", "lines", i + 1)) {
        //    out.push_back(CONTINUE);
        //}
    }
}

void write_basic_command(std::vector<uint8_t> &out, uint8_t cmdId, uint8_t value) {
    out.push_back(cmdId);
    out.push_back(value);
}

void write_basic_command_4_args(std::vector<uint8_t> &out, uint8_t cmdId, uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
    out.push_back(cmdId);
    out.push_back(a);
    out.push_back(b);
    out.push_back(c);
    out.push_back(d);
}

void BuildGameText::build_textbox(std::vector<uint8_t> &out, json::JSON inputJSON) {
    int numberOfPages = GET_ARRAY_LENGTH("pages");
    for(int page = 0; page < numberOfPages; page++) {
        int numberOfCommandsInPage = GET_ARRAY_LENGTH("pages", page);
        for(int cmd = 0; cmd < numberOfCommandsInPage; cmd++) {
            std::string cmdType = get_string_from_json(srcPath, "pages", page, cmd, "command");
            if(cmdType == "Text") {
                write_ascii(out, get_string_from_json(srcPath, "pages", page, cmd, "value"));
            } else if(cmdType == "SetFont") {
                write_basic_command(out, 3, get_int_from_json(srcPath, "pages", page, cmd, "value"));
            } else if(cmdType == "SetBorder") {
                write_basic_command_4_args(out, 4, 
                    get_int_from_json(srcPath, "pages", page, cmd, "value", "Left"),
                    get_int_from_json(srcPath, "pages", page, cmd, "value", "Top"),
                    get_int_from_json(srcPath, "pages", page, cmd, "value", "Right"),
                    get_int_from_json(srcPath, "pages", page, cmd, "value", "Bottom")
                );
            } else if(cmdType == "SetColor") {
                write_basic_command_4_args(out, 5, 
                    get_int_from_json(srcPath, "pages", page, cmd, "value", "red"),
                    get_int_from_json(srcPath, "pages", page, cmd, "value", "green"),
                    get_int_from_json(srcPath, "pages", page, cmd, "value", "blue"),
                    get_int_from_json(srcPath, "pages", page, cmd, "value", "alpha")
                );
            } else if(cmdType == "SetAlignment") {
                write_basic_command(out, 6, get_string_from_json(srcPath, "pages", page, cmd, "value") == "ALIGN_CENTER" ? 0 : 4);
            } else if(cmdType == "Unknown") {
                write_basic_command(out, 7, get_int_from_json(srcPath, "pages", page, cmd, "value"));
            } else if(cmdType == "AddVerticalSpacing") {
                write_basic_command(out, 8, get_int_from_json(srcPath, "pages", page, cmd, "value"));
            } else if(cmdType == "SetLineHeight") {
                write_basic_command(out, 9, get_int_from_json(srcPath, "pages", page, cmd, "value"));
            } else if(cmdType == "SetTimer") {
                write_basic_command(out, 10, get_int_from_json(srcPath, "pages", page, cmd, "value"));
            } else if(cmdType == "AllowUserInput") {
                write_basic_command(out, 10, GET_BOOL("pages", page, cmd, "value") ? 1 : 0);
            }
        }
        if(page < numberOfPages - 1) {
            out.push_back(NEXT_PAGE);
        }
    }
}
*/
