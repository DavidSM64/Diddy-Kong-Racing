#include "buildAudio.h"

BuildAudio::BuildAudio(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    if(info.srcFile->is_value_null("/raw")) {
        FileHelper::write_empty_file(_info.dstPath, true);
        return;
    }
    
    std::string rawPath = info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildAudio::BuildAudio) \"raw\" not specified!");
    
    // Copy file from rawPath to destination path.
    FileHelper::copy(_info.localDirectory / rawPath, info.dstPath);
}

BuildAudio::~BuildAudio() {
    
}

