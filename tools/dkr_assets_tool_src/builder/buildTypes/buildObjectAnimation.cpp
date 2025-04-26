#include "buildObjectAnimation.h"

using namespace DkrAssetsTool;

void BuildObjectAnimation::build(BuildInfo &info) {
    std::string rawPath = info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildObjectAnimation::build) \"raw\" not specified!");
    
    if(info.build_to_file()) {
        // Copy file from rawPath to destination path.
        FileHelper::copy(info.localDirectory / rawPath, info.dstPath);
    } else {
        // Load raw binary into info's out
        info.out = FileHelper::read_binary_file(info.localDirectory / rawPath);
    }
}
