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

#include "build_files/build_fonts.h"
#include "build_files/build_gametext.h"
#include "build_files/build_levelname.h"
#include "build_files/build_levelheader.h"
#include "build_files/build_menutext.h"
#include "build_files/build_sprite.h"
#include "build_files/build_texture.h"
#include "build_files/build_ttghost.h"

class Builder {
public:
    Builder(std::string srcPath, std::string dstPath);
    ~Builder();
private:
};
