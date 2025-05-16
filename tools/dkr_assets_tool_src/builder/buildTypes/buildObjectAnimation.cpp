#include "buildObjectAnimation.h"

using namespace DkrAssetsTool;

BuildObjectAnimation::BuildObjectAnimation(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    std::string rawPath = info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildObjectAnimation::BuildObjectAnimation) \"raw\" not specified!");
    
    // Copy file from rawPath to destination path.
    FileHelper::copy(_info.localDirectory / rawPath, info.dstPath);
}

BuildObjectAnimation::~BuildObjectAnimation() {
    
}

