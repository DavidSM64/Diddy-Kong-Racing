#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

class ExtractGameText {
public:
    ExtractGameText(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractGameText();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
    fs::path _outFilepath;
    
    void _extract_dialog(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes);
    void _extract_textbox(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes);
};
