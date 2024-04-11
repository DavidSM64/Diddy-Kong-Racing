#include "buildLevelModel.h"

BuildLevelModel::BuildLevelModel(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    std::string rawPath = info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildLevelModel::BuildLevelModel) \"raw\" not specified!");
    
    // Copy file from rawPath to destination path.
    FileHelper::copy(_info.localDirectory / rawPath, info.dstPath);
}

BuildLevelModel::~BuildLevelModel() {
    
}

