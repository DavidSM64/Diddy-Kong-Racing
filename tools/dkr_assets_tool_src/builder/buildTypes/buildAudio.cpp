#include "buildAudio.h"

using namespace DkrAssetsTool;

void BuildAudio::build(BuildInfo &info)  {
    if(info.srcFile->is_value_null("/raw")) {
        if(info.build_to_file()) {
            FileHelper::write_empty_file(info.dstPath, true);
        }
        // Don't need to do anything for the BUILD_TO_BINARY case.
        return;
    }
    
    std::string rawPath = info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildAudio::BuildAudio) \"raw\" not specified!");
    
    if(info.build_to_file()) {
        // Copy file from rawPath to destination path.
        FileHelper::copy(info.localDirectory / rawPath, info.dstPath);
    } else {
        // Load raw binary into info's out
        info.out = FileHelper::read_binary_file(info.localDirectory / rawPath);
    }
}

