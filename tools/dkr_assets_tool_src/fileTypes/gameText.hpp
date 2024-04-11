#pragma once

#include "types.hpp"
#include <vector>

const std::vector<const char*> TEXTBOX_COMMANDS = {
    "End",
    "NextPage",
    "Unused2",
    "SetFont",
    "SetBorder",
    "SetColour",
    "SetAlignment",
    "Unknown7",
    "AddVerticalSpacing",
    "SetLineHeight",
    "SetTimer",
    "AllowUserInput"
};

struct SetFontCommand {
    uint8_t fontId;
};

// 0 = Farthest left/top, 0xFF = Farthest right/bottom
struct SetBorderCommand {
    uint8_t left;
    uint8_t top;
    uint8_t right;
    uint8_t bottom;
};

struct SetColourCommand {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

struct SetAlignmentCommand {
    uint8_t value;
};

struct Unknown7Command {
    uint8_t value;
};

struct AddVerticalSpacingCommand {
    uint8_t value;
};

struct SetLineHeightCommand {
    uint8_t value;
};

struct SetTimerCommand {
    uint8_t value;
};

struct AllowUserInputCommand {
    uint8_t value;
};
