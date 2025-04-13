#include "buildInfo.h"

using namespace DkrAssetsTool;

BuildInfo::BuildInfo(JsonFile *src, const fs::path &dst, const fs::path &dir) 
    : srcFile(src), dstPath(dst), localDirectory(dir) {
    _buildType = BUILD_TO_FILE;
}

BuildInfo::BuildInfo(JsonFile *src, const uint8_t *dstBinaryPtr, const fs::path &dir) 
    : srcFile(src), dstPath(""), localDirectory(dir), dstBinaryPtr(dstBinaryPtr) {
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