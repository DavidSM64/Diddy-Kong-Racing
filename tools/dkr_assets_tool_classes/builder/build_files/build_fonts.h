#pragma once

#include "../../common/util.h"
//#include "macros.h"

class BuildFonts {
public:
    BuildFonts(std::string srcPath, std::string dstPath);
    ~BuildFonts();
private:
    void write_ascii_char_nodes(std::vector<uint8_t> &out, std::string srcPath, int offset, bool uppercaseOnly);
    void write_custom_char_nodes(std::vector<uint8_t> &out, std::string srcPath, int offset, bool uppercaseOnly);
};
