#pragma once

#include <string>

#include "helpers/jsonHelper.h"

class BuildInfo {
public:
    BuildInfo(JsonFile *src, const fs::path &dst, const fs::path &dir);
    ~BuildInfo();
    
    JsonFile *srcFile;
    const fs::path &dstPath;
    const fs::path &localDirectory;
private:
};