#pragma once

#include <mutex>
#include <map>
#include <vector>

#include "misc/settings.hpp"

#include "helpers/fileHelper.h"
#include "helpers/asmHeader.h"

struct LDCodeFile {
    std::string path;
    std::string condition;
};

class PreBuild {
public:
    PreBuild(DkrAssetsSettings &settings);
    ~PreBuild();
private:
    DkrAssetsSettings &_settings;
    
    fs::path _buildFolder;
};
