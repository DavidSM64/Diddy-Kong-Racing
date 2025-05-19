#include "buildAudio.h"

using namespace DkrAssetsTool;

void BuildAudio::build(BuildInfo &info)  {
    const JsonFile &jsonFile = info.get_src_json_file();
    
    if(jsonFile.is_value_null("/raw")) {
        if(info.build_to_file()) {
            info.write_empty_file_to_dstPath();
        }
        // Don't need to do anything for the BUILD_TO_BINARY case.
        return;
    }
    
    std::string rawPath = jsonFile.get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildAudio::BuildAudio) \"raw\" not specified!");
    
    fs::path dir = info.get_path_to_directory();
    
    if(info.build_to_file()) {
        // Copy file from rawPath to destination path.
        info.copy_to_dstPath(dir / rawPath);
    } else {
        // Load raw binary into info's out
        info.out = FileHelper::read_binary_file(dir / rawPath);
    }
}
