#include "buildObjectAnimation.h"

using namespace DkrAssetsTool;

void BuildObjectAnimation::build(BuildInfo &info) {
    const JsonFile &jsonFile = info.get_src_json_file();
    std::string rawPath = jsonFile.get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildObjectAnimation::build) \"raw\" not specified!");
    
    fs::path dir = info.get_path_to_directory();
    
    if(info.build_to_file()) {
        // Copy file from rawPath to destination path.
        info.copy_to_dstPath(dir / rawPath);
    } else {
        // Load raw binary into info's out
        info.out = FileHelper::read_binary_file(dir / rawPath);
    }
}
