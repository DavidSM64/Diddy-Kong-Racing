#include "prebuild.h"

#include "prebuild/makeIncludes/assetsAsm.h"
#include "prebuild/makeIncludes/assetEnums.h"
#include "prebuild/compileAssets/compile.h"

using namespace DkrAssetsTool;

void PreBuild::prebuild() {
    CompileAssets::compile();
    AssetsAsm assetsAsm;   // Generate asm/assets/assets.s
    AssetEnums assetEnums; // Generate include/asset_enums.h
}

