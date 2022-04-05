#pragma once

#include "../../common/util.h"

#define SIZEOF_TTGHOST_HEADER 8
#define SIZEOF_TTGHOST_NODE 12

class BuildTTGhost {
public:
    BuildTTGhost(std::string srcPath, std::string dstPath);
    ~BuildTTGhost();
};
