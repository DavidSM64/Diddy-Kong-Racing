#pragma once

#include <optional>
#include "builder/buildInfo.h"

namespace DkrAssetsTool {
namespace BuildTexture {
    
    void build(BuildInfo &info);

    struct DeferredTextureInfo {
        std::string buildId = "";
        std::string format = "";
        std::string renderMode = "";
        size_t totalSize = 0;
        int frameAdvanceDelay = 0;
        std::string wrapS = "";
        std::string wrapT = "";
        bool shouldFlip = false;
    };
    
    // Called from object/level model builders to add new textures.
    // Returns the fileIndex of the new texture asset.
    size_t build_deferred(BuildInfo &baseInfo, fs::path pathToImage, DeferredTextureInfo textureInfo = {});
    size_t build_deferred(BuildInfo &baseInfo, uint8_t *imgData, size_t imgDataLength, std::string mimeType, 
        std::string imgName, DeferredTextureInfo textureInfo = {});
        
}
}
