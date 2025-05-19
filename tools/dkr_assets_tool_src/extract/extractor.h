#pragma once

#include "helpers/fileHelper.h"

namespace DkrAssetsTool {
namespace AssetExtractor {
    void extract_all(); // extract ALL assets
    void extract(const fs::path &srcPath, const fs::path &dstPath); // extract single asset
}
}
