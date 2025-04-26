#pragma once

#include "helpers/fileHelper.h"

namespace DkrAssetsTool {
namespace AssetBuilder {
    void build_all(const fs::path &dstPath); // build ALL assets
    void build(const fs::path &srcPath, const fs::path &dstPath); // build single asset
}
}
