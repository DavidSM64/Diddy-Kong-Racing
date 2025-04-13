#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {
class BuildGameText {
public:
    BuildGameText(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildGameText();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
    
    void _build_dialog();
    
    void _textbox_set_font(std::vector<uint8_t> &out, const std::string &cmdPtr);
    void _textbox_set_border(std::vector<uint8_t> &out, const std::string &cmdPtr);
    void _textbox_set_colour(std::vector<uint8_t> &out, const std::string &cmdPtr);
    void _textbox_set_alignment(std::vector<uint8_t> &out, const std::string &cmdPtr);
    void _textbox_unknown7(std::vector<uint8_t> &out, const std::string &cmdPtr);
    void _textbox_add_vertical_spacing(std::vector<uint8_t> &out, const std::string &cmdPtr);
    void _textbox_set_line_height(std::vector<uint8_t> &out, const std::string &cmdPtr);
    void _textbox_set_timer(std::vector<uint8_t> &out, const std::string &cmdPtr);
    void _textbox_allow_user_input(std::vector<uint8_t> &out, const std::string &cmdPtr);
    void _textbox_text(std::vector<uint8_t> &out, const std::string &cmdPtr);
    
    void _build_textbox();
};
}
