#pragma once

#include <optional>
#include <string>

#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {

enum DeferredAssetMode {
    ONE_TO_ONE, // Strict one deferred asset to a regular one. (Level names)
    MANY_TO_ONE, // Many deferred assets to a regular one. (Object animations)
    BUILD_ONLY // Run on build, but ignore source file. (Object animation ids)
};

struct DeferredAssetInfo {
    DeferredAssetMode mode;
    std::string type;
    std::string fromSection;
    std::string idPostfix;
    std::string outputPath;
    
    DeferredAssetInfo(DeferredAssetMode mode, std::string type,
        std::string fromSection, std::string idPostfix, std::string outputPath);
};

namespace AssetsHelper {
    std::reference_wrapper<JsonFile> get_meta_file(fs::path filepath);
    std::reference_wrapper<JsonFile> get_main_json();
    std::reference_wrapper<JsonFile> get_main_json(fs::path pathToAssets);
    std::reference_wrapper<JsonFile> get_asset_section_json(const std::string assetSectionId);
    size_t get_asset_section_count(const std::string assetSectionId);
    std::reference_wrapper<JsonFile> get_asset_json(const std::string assetSectionId, std::string buildId = "");
    int get_asset_index(const std::string assetSectionId, std::string& buildId);
    bool section_contains_build_id(const std::string assetSectionId, std::string& buildId);
    fs::path get_path_to_asset(const std::string assetSectionId, std::string& buildId);
    std::string get_section_path(const std::string& assetSectionId);
    std::string get_build_id_of_index(const std::string& assetSectionId, int index);

    DeferredAssetInfo get_deferred_asset_info(const std::string assetSectionId);
}
}
