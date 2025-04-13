#include "buildParticleBehavior.h"

using namespace DkrAssetsTool;

BuildParticleBehavior::BuildParticleBehavior(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    std::string rawPath = info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildParticleBehavior::BuildParticleBehavior) \"raw\" not specified!");
    
    // Copy file from rawPath to destination path.
    FileHelper::copy(_info.localDirectory / rawPath, _info.dstPath);
}

BuildParticleBehavior::~BuildParticleBehavior() {
    
}

