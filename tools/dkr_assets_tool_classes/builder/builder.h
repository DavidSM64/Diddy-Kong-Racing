#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread>

#include "../common/util.h"
#include "../common/types.h"

#include "build/build_fonts.h"
#include "build/build_gametext.h"
#include "build/build_levelname.h"
#include "build/build_levelheader.h"
#include "build/build_menutext.h"
#include "build/build_sprite.h"
#include "build/build_texture.h"
#include "build/build_ttghost.h"

class Builder {
public:
    Builder(std::string srcPath, std::string dstPath);
    ~Builder();
private:
};
