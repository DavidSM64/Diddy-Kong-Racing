#include "buildInfo.h"

#include "misc/globalSettings.h"
#include "helpers/c/cContext.h"

using namespace DkrAssetsTool;

BuildInfo::BuildInfo(JsonFile *src, const fs::path &dst, const fs::path &dir) 
    : srcFile(src), dstPath(dst), localDirectory(dir) {
    _buildType = BUILD_TO_FILE;
}

BuildInfo::BuildInfo(JsonFile *src, const fs::path &dir) 
    : srcFile(src), dstPath(""), localDirectory(dir) {
    _buildType = BUILD_TO_BINARY;
}

BuildInfo::~BuildInfo() {
}

BuildInfoType BuildInfo::get_build_type() const {
    return _buildType;
}

bool BuildInfo::build_to_file() const {
    return _buildType == BUILD_TO_FILE;
}

bool BuildInfo::build_to_binary() const {
    return _buildType == BUILD_TO_BINARY;
}
    
void BuildInfo::write_out_to_dstPath() {
    FileHelper::write_binary_file(out, dstPath, true);
}
    
CContext &BuildInfo::get_c_context() const {
    DebugHelper::assert_(_cContext.has_value(), "(BuildInfo::get_c_context) No C context found.");
    return _cContext.value();
}

void BuildInfo::load_structs_into_c_context(std::vector<fs::path> structFilesToLoad) {
    fs::path includeFolder = GlobalSettings::get_decomp_path("include_subpath", "include/");
    
    DebugHelper::assert_(!includeFolder.empty(),
        "(BuildInfo::load_structs_into_c_context) Could not find the include folder!");
    
    CContext &cContext = get_c_context();
    
    for(fs::path &structPath : structFilesToLoad) {
        CStructHelper::load_structs_from_file(cContext, includeFolder / structPath);
    }
}

void BuildInfo::load_enums_into_c_context(std::vector<fs::path> enumFilesToLoad) {
    fs::path includeFolder = GlobalSettings::get_decomp_path("include_subpath", "include/");
    
    DebugHelper::assert_(!includeFolder.empty(),
        "(BuildInfo::load_enums_into_c_context) Could not find the include folder!");
    
    CContext &cContext = get_c_context();
    
    for(fs::path &enumPath : enumFilesToLoad) {
        CEnumsHelper::load_enums_from_file(cContext, includeFolder / enumPath);
    }
}
