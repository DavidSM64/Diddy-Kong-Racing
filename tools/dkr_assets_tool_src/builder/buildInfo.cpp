#include "buildInfo.h"

BuildInfo::BuildInfo(JsonFile *src, const fs::path &dst, const fs::path &dir) 
    : srcFile(src), dstPath(dst), localDirectory(dir) {
}

BuildInfo::~BuildInfo() {
}
