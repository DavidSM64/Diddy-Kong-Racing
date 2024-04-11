#pragma once

#include <string>
#include "misc/settings.hpp"

// Converts a JSON file into raw asset data the game can read.
class DkrAssetBuilder {
public:
    DkrAssetBuilder(DkrAssetsSettings &settings, const fs::path &srcPath, const fs::path &dstPath);
    ~DkrAssetBuilder();
private:
    
    
};