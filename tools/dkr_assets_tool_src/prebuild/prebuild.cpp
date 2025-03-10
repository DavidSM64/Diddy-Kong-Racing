#include "prebuild.h"

#include "libs/ThreadPool.h"

#include "helpers/debugHelper.h"
#include "helpers/regexHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/stringHelper.h"

#include "prebuild/makeIncludes/assetsAsm.h"
#include "prebuild/makeIncludes/assetEnums.h"
#include "prebuild/compileAssets/compile.h"

const std::string SECTION_TEXT = "text";
const std::string SECTION_DATA = "data";
const std::string SECTION_RODATA = "rodata";
const std::string SECTION_BSS = "bss";

PreBuild::PreBuild(DkrAssetsSettings &settings) : _settings(settings) {
    _buildFolder = _settings.pathToBuild;
    
    // Gets rid of the starting "./" from the path.
    _buildFolder = fs::relative(_buildFolder);
    
    CompileAssets compileAssets(_settings);
    
    _settings.pathToAssets /= _settings.dkrVersion;
    
    AssetsAsm assetsAsm(_settings);   // Generate asm/assets/assets.s
    AssetEnums assetEnums(_settings); // Generate include/asset_enums.h
}

PreBuild::~PreBuild() {
}
