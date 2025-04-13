#pragma once

#include <string>
#include "misc/settings.hpp"

namespace DkrAssetsTool {

// Converts a JSON file into raw asset data the game can read.
class DkrAssetBuilder {
public:
    DkrAssetBuilder(DkrAssetsSettings &settings, const fs::path &dstPath); // build ALL assets
    DkrAssetBuilder(DkrAssetsSettings &settings, const fs::path &srcPath, const fs::path &dstPath); // build single asset
    ~DkrAssetBuilder();
private:
    
    
};
}