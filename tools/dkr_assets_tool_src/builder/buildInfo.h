#pragma once

#include <string>
#include <vector>
#include <optional>

#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cContext.h"

namespace DkrAssetsTool {

typedef enum BuildInfoType {
    BUILD_TO_FILE, // When building a single asset.
    BUILD_TO_BINARY // When building all assets
} BuildInfoType;

class BuildInfo {
public:
    BuildInfo(JsonFile *src, const fs::path &dst, const fs::path &dir); // BUILD_TO_FILE
    BuildInfo(JsonFile *src, const fs::path &dir); // BUILD_TO_BINARY
    ~BuildInfo();
    
    JsonFile *srcFile;
    const fs::path &dstPath; // Only used for BUILD_TO_FILE
    const fs::path &localDirectory;
    std::vector<uint8_t> out;
    
    BuildInfoType get_build_type() const;
    bool build_to_file() const;
    bool build_to_binary() const;
    
    void write_out_to_dstPath();
    
    CContext &get_c_context() const;
    void load_structs_into_c_context(std::vector<fs::path> structFilesToLoad);
    void load_enums_into_c_context(std::vector<fs::path> enumsFilesToLoad);
    
private:
    BuildInfoType _buildType;
    
    std::optional<std::reference_wrapper<CContext>> _cContext;
};

}