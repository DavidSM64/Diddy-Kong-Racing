#pragma once

#include "builder/buildInfo.h"

namespace DkrAssetsTool {
namespace BuildTexture {
    void build(BuildInfo &info);
    
    // Called from object/level model builders to add new textures.
    // Returns the fileIndex of the new texture asset.
    size_t build_deferred(BuildInfo &baseInfo, fs::path pathToImage);
}
}
