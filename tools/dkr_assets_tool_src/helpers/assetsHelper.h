#pragma once

#include <string>

#include "helpers/jsonHelper.h"
#include "misc/settings.hpp"

struct DeferredAssetInfo {
    std::string type;
    std::string fromSection;
    std::string idPostfix;
    std::string outputPath;
    
    DeferredAssetInfo(std::string type, std::string fromSection, 
        std::string idPostfix, std::string outputPath);
};

/**
 * Singleton class that deals with getting asset JSON files for building.
 */
class AssetsHelper {
public:
    static AssetsHelper& get() {
        static AssetsHelper instance;
        return instance;
    }
    
    static JsonFile *get_meta_file(DkrAssetsSettings &settings, fs::path filepath);
    static JsonFile *get_main_json(DkrAssetsSettings &settings);
    static JsonFile *get_main_json(fs::path pathToAssets);
    static JsonFile *get_asset_section_json(DkrAssetsSettings &settings, const std::string assetSectionId);
    static JsonFile *get_asset_json(DkrAssetsSettings &settings, const std::string assetSectionId, std::string buildId="");
    static int get_asset_index(DkrAssetsSettings &settings, const std::string assetSectionId, std::string &buildId);
    static std::string get_section_path(DkrAssetsSettings &settings, const std::string &assetSectionId);
    static std::string get_build_id_of_index(DkrAssetsSettings &settings, const std::string &assetSectionId, int index);
    
    static DeferredAssetInfo get_deferred_asset_info(DkrAssetsSettings &settings, const std::string assetSectionId);
private:
    static JsonFile *_get_section_json(fs::path pathToAssets, const std::string &assetSectionId);
};
