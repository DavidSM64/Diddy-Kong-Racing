#include "buildBinary.h"

using namespace DkrAssetsTool;

void BuildBinary::build(BuildInfo &info) {
    std::string rawPath = info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildBinary::build) \"raw\" not specified!");
    
    if(info.build_to_file()) {
        // Copy file from rawPath to destination path.
        FileHelper::copy(info.localDirectory / rawPath, info.dstPath);
    } else {
        // Load raw binary into info's out
        info.out = FileHelper::read_binary_file(info.localDirectory / rawPath);
    }
}


