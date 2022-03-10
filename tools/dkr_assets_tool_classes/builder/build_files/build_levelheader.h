#pragma once

#include "../../common/util.h"

#define SIZEOF_LEVEL_HEADER 0xC8

class BuildLevelHeader {
public:
    BuildLevelHeader(std::string srcPath, std::string dstPath);
    ~BuildLevelHeader();
};
