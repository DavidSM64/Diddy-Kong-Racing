#include "assetsHelper.h"
#include <sstream>
#include <unordered_map>
#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "misc/globalSettings.h"

using namespace DkrAssetsTool;

DeferredAssetInfo::DeferredAssetInfo(DeferredAssetMode mode, std::string type, std::string fromSection, std::string idPostfix, std::string outputPath) :
    mode(mode), type(type), fromSection(fromSection), idPostfix(idPostfix), outputPath(outputPath) {
    DebugHelper::assert_(!type.empty(), "(DeferredAssetInfo::DeferredAssetInfo) Type not specified!");
}

std::reference_wrapper<JsonFile> _get_section_json(fs::path pathToAssets, const std::string& assetSectionId);
fs::path _get_path_to_assets_folder();

// Note: filepath is local to assets.
std::reference_wrapper<JsonFile> AssetsHelper::get_meta_file(fs::path filepath) {
    fs::path pathToAssets = _get_path_to_assets_folder();

    auto tryGetAssetFile = JsonHelper::get_file(pathToAssets / filepath);
    DebugHelper::assert_(tryGetAssetFile.has_value(),
        "(AssetsHelper::get_meta_file) Could not find json file in assets folder: ", filepath);

    return tryGetAssetFile.value();
}

std::reference_wrapper<JsonFile> AssetsHelper::get_main_json() {
    fs::path pathToAssets = _get_path_to_assets_folder();
    return get_main_json(pathToAssets);
}

std::reference_wrapper<JsonFile> AssetsHelper::get_main_json(fs::path pathToAssets) {
    fs::path mainAssetsFilepath = pathToAssets / "assets.meta.json";

    auto tryGetMainAssetsJson = JsonHelper::get_file(mainAssetsFilepath);
    // Load assets.meta.json, and throw error if it couldn't be found.
    DebugHelper::assert_(tryGetMainAssetsJson.has_value(),
        "(AssetsHelper::_get_section_json) Could not find assets.meta.json. Path was ", mainAssetsFilepath);

    return tryGetMainAssetsJson.value();
}

std::reference_wrapper<JsonFile> AssetsHelper::get_asset_section_json(const std::string assetSectionId) {
    fs::path pathToAssets = _get_path_to_assets_folder();
    return _get_section_json(pathToAssets, assetSectionId);
}

size_t AssetsHelper::get_asset_section_count(const std::string assetSectionId) {
    JsonFile& assetSection = get_asset_section_json(assetSectionId);
    return assetSection.length_of_array("/files/order");
}

// Returns the asset JSON file from a section ID & build ID.
std::reference_wrapper<JsonFile> AssetsHelper::get_asset_json(const std::string assetSectionId, std::string buildId) {
    fs::path filepath = get_path_to_asset(assetSectionId, buildId);

    // Load the file JSON, and throw error if it couldn't be found.
    auto tryGetAssetFile = JsonHelper::get_file(filepath);
    DebugHelper::assert_(tryGetAssetFile.has_value(),
        "(AssetsHelper::get_asset_json) Could not find file json. Path was ", filepath);

    return tryGetAssetFile.value();
}

// Returns the index to an asset from a section.
int AssetsHelper::get_asset_index(const std::string assetSectionId, std::string& buildId) {
    fs::path pathToAssets = _get_path_to_assets_folder();

    JsonFile& sectionJson = _get_section_json(pathToAssets, assetSectionId);
    int index = sectionJson.get_index_of_elem_in_array("/files/order", buildId);

    // Throws an error if the element was not found.
    DebugHelper::assert_(index >= 0,
        "(AssetsHelper::get_asset_index) Could not find \"", buildId, "\" in the order defined in the section \"", assetSectionId, "\"");

    return index;
}

bool AssetsHelper::section_contains_build_id(const std::string assetSectionId, std::string& buildId) {
    fs::path pathToAssets = _get_path_to_assets_folder();
    JsonFile& sectionJson = _get_section_json(pathToAssets, assetSectionId);
    int index = sectionJson.get_index_of_elem_in_array("/files/order", buildId);
    return index >= 0;
}

fs::path AssetsHelper::get_path_to_asset(const std::string assetSectionId, std::string& buildId) {
    fs::path pathToAssets = _get_path_to_assets_folder();

    JsonFile& sectionJson = _get_section_json(pathToAssets, assetSectionId);

    fs::path filename;

    if (buildId.empty()) {
        DebugHelper::assert_(sectionJson.has("/filename"),
            "(AssetsHelper::get_path_to_asset) [/filename] was not found in the section \"", assetSectionId, "\"");
        filename = sectionJson.get_string("/filename");
    } else {
        std::string fileSectionPtr = "/files/sections/" + buildId;

        // Make sure the section build id exists in the section json file.
        DebugHelper::assert_(sectionJson.has(fileSectionPtr),
            "(AssetsHelper::get_path_to_asset) Section \"", buildId, "\" was not found in the section \"", assetSectionId, "\"");

        filename = sectionJson.get_string(fileSectionPtr + "/filename");
    }


    fs::path localFolder = sectionJson.get_path("/folder");
    FileHelper::format_folder_string(localFolder); // Make sure localFolder string is valid.
    return pathToAssets / localFolder / filename;
}

std::string AssetsHelper::get_section_path(const std::string& assetSectionId) {
    fs::path pathToAssets = _get_path_to_assets_folder();
    JsonFile& sectionJson = _get_section_json(pathToAssets, assetSectionId);

    return sectionJson.get_path("/folder").generic_string();
}

std::string AssetsHelper::get_build_id_of_index(const std::string& assetSectionId, int index) {
    fs::path pathToAssets = _get_path_to_assets_folder();
    JsonFile& sectionJson = _get_section_json(pathToAssets, assetSectionId);

    return sectionJson.get_elem_from_array<std::string>("/files/order", index);
}

std::unordered_map<std::string, DeferredAssetMode> stringToDeferredMode = {
    { "1-to-1", DeferredAssetMode::ONE_TO_ONE },
    { "many-to-1", DeferredAssetMode::MANY_TO_ONE },
    { "build-only", DeferredAssetMode::BUILD_ONLY }
};

DeferredAssetInfo AssetsHelper::get_deferred_asset_info(const std::string assetSectionId) {
    JsonFile& mainJson = get_main_json();

    std::string sectionJsonPtr = "/assets/sections/" + assetSectionId;

    DebugHelper::assert_(mainJson.get_bool(sectionJsonPtr + "/deferred"),
        "(AssetsHelper::get_deferred_asset_info) ", assetSectionId, " is not deferred!");

    std::string deferInfoPtr = sectionJsonPtr + "/defer-info";

    return DeferredAssetInfo(
        stringToDeferredMode[mainJson.get_string(deferInfoPtr + "/defer-mode")],
        mainJson.get_string(sectionJsonPtr + "/type"),
        mainJson.get_string(deferInfoPtr + "/from-section"),
        mainJson.get_string(deferInfoPtr + "/id-postfix"),
        mainJson.get_string(deferInfoPtr + "/output-path")
    );
}

std::reference_wrapper<JsonFile> _get_section_json(fs::path pathToAssets, const std::string& assetSectionId) {
    JsonFile& mainJson = AssetsHelper::get_main_json(pathToAssets);

    std::string sectionJsonPtr = "/assets/sections/" + assetSectionId;

    // Make sure the section build id exists in assets.meta.json
    DebugHelper::assert_(mainJson.has(sectionJsonPtr),
        "(AssetsHelper::_get_section_json) Section \"", assetSectionId, "\" was not found in assets.meta.json");

    fs::path filename = mainJson.get_string(sectionJsonPtr + "/filename");

    DebugHelper::assert_(!filename.empty(), "Section \"", assetSectionId, "\" has no filename.");

    fs::path sectionFilepath = pathToAssets / filename;

    auto tryGetSectionJson = JsonHelper::get_file(sectionFilepath);

    // Load the section JSON, and throw error if it couldn't be found.
    DebugHelper::assert_(tryGetSectionJson.has_value(),
        "(AssetsHelper::_get_section_json) Could not find section json. Path was ", sectionFilepath);

    return tryGetSectionJson.value();
}

fs::path _get_path_to_assets_folder() {
    fs::path outputAssets = GlobalSettings::get_decomp_path_to_output_assets();

    if(FileHelper::path_exists(outputAssets)) {
        return outputAssets;
    }

    return GlobalSettings::get_decomp_path_to_vanilla_assets();
}