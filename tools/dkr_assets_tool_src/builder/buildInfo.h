#pragma once

#include <string>

#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {

typedef enum BuildInfoType {
    BUILD_TO_FILE, // When building a single asset.
    BUILD_TO_BINARY // When building all assets
} BuildInfoType;

class BuildInfo {
public:
    BuildInfo(JsonFile *src, const fs::path &dst, const fs::path &dir);
    BuildInfo(JsonFile *src, const uint8_t *dstBinaryPtr, const fs::path &dir);
    ~BuildInfo();
    
    JsonFile *srcFile;
    const fs::path &dstPath;
    const fs::path &localDirectory;
    const uint8_t *dstBinaryPtr = nullptr;
    
    BuildInfoType get_build_type() const;
    bool build_to_file() const;
    bool build_to_binary() const;
private:
    BuildInfoType _buildType;
};

}