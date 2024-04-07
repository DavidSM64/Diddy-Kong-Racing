#include "assetsHelper.h"

#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"

DeferredAssetInfo::DeferredAssetInfo(std::string type, std::string fromSection, std::string idPostfix, std::string outputPath) : 
    type(type), fromSection(fromSection), idPostfix(idPostfix), outputPath(outputPath) {
        DebugHelper::assert(!type.empty(), "(DeferredAssetInfo::DeferredAssetInfo) Type not specified!");
}

// Note: filepath is local to assets.
JsonFile *AssetsHelper::get_meta_file(DkrAssetsSettings &settings, fs::path filepath) {
    JsonFile *out;
    
    DebugHelper::assert(JsonHelper::get().get_file(settings.pathToAssets / filepath, &out), 
        "(AssetsHelper::get_meta_file) Could not find json file in assets folder: ", filepath);
    
    return out;
}

JsonFile *AssetsHelper::get_main_json(DkrAssetsSettings &settings) {
    return get_main_json(settings.pathToAssets);
}

JsonFile *AssetsHelper::get_main_json(fs::path pathToAssets) {
    fs::path mainAssetsFilepath = pathToAssets / "assets.meta.json";
    
    JsonFile *mainJson;
    // Load assets.meta.json, and throw error if it couldn't be found.
    DebugHelper::assert(JsonHelper::get().get_file(mainAssetsFilepath, &mainJson), 
        "(AssetsHelper::_get_section_json) Could not find assets.meta.json. Path was ", mainAssetsFilepath);
        
    return mainJson;
}

JsonFile *AssetsHelper::get_asset_section_json(DkrAssetsSettings &settings, const std::string assetSectionId) {
    return _get_section_json(settings.pathToAssets, assetSectionId);
}

size_t AssetsHelper::get_asset_section_count(DkrAssetsSettings &settings, const std::string assetSectionId) {
    JsonFile *assetSection = get_asset_section_json(settings, assetSectionId);
    
    if(assetSection == nullptr) {
        return 0;
    }
    
    return assetSection->length_of_array("/files/order");
}

// Returns the asset JSON file from a section ID & build ID.
JsonFile *AssetsHelper::get_asset_json(DkrAssetsSettings &settings, const std::string assetSectionId, std::string buildId) {
    JsonFile *out = nullptr;
    
    JsonFile *sectionJson = _get_section_json(settings.pathToAssets, assetSectionId);
    
    DebugHelper::assert(sectionJson != nullptr, 
        "(AssetsHelper::get_build_id_of_index) _get_section_json returned null for ", assetSectionId);
    
    fs::path filename;
    
    if(buildId.empty()) {
        DebugHelper::assert(sectionJson->has("/filename"), 
            "(AssetsHelper::get_asset_json) [/filename] was not found in the section \"", assetSectionId, "\"");
        filename = sectionJson->get_string("/filename");
    } else {
        std::string fileSectionPtr = "/files/sections/" + buildId;
        
        // Make sure the section build id exists in the section json file.
        DebugHelper::assert(sectionJson->has(fileSectionPtr), 
            "(AssetsHelper::get_asset_json) Section \"", buildId, "\" was not found in the section \"", assetSectionId, "\"");

        filename = sectionJson->get_string(fileSectionPtr + "/filename");
    }
    
    
    fs::path localFolder = sectionJson->get_path("/folder");
    FileHelper::format_folder_string(localFolder); // Make sure localFolder string is valid.
    fs::path filepath = settings.pathToAssets / localFolder / filename;
    
    // Load the file JSON, and throw error if it couldn't be found.
    DebugHelper::assert(JsonHelper::get().get_file(filepath, &out), 
        "(AssetsHelper::get_asset_json) Could not find file json. Path was ", filepath);
            
    return out;
}

// Returns the index to an asset from a section.
int AssetsHelper::get_asset_index(DkrAssetsSettings &settings, const std::string assetSectionId, std::string &buildId) {
    JsonFile *sectionJson = _get_section_json(settings.pathToAssets, assetSectionId);
    int index = sectionJson->get_index_of_elem_in_array("/files/order", buildId);
    
    // Throws an error if the element was not found.
    DebugHelper::assert(index >= 0, 
        "(AssetsHelper::get_asset_index) Could not find \"", buildId, "\" in the order defined in the section \"", assetSectionId, "\"");
    
    return index;
}

std::string AssetsHelper::get_section_path(DkrAssetsSettings &settings, const std::string &assetSectionId) {
    JsonFile *sectionJson = _get_section_json(settings.pathToAssets, assetSectionId);
    
    DebugHelper::assert(sectionJson != nullptr, 
        "(AssetsHelper::get_section_path) _get_section_json returned null for ", assetSectionId);
    
    return sectionJson->get_path("/folder");
}

std::string AssetsHelper::get_build_id_of_index(DkrAssetsSettings &settings, const std::string &assetSectionId, int index) {
    JsonFile *sectionJson = _get_section_json(settings.pathToAssets, assetSectionId);
    
    DebugHelper::assert(sectionJson != nullptr, 
        "(AssetsHelper::get_build_id_of_index) _get_section_json returned null for ", assetSectionId);
    
    return sectionJson->get_elem_from_array<std::string>("/files/order", index);
}

DeferredAssetInfo AssetsHelper::get_deferred_asset_info(DkrAssetsSettings &settings, const std::string assetSectionId) {
    JsonFile *mainJson = get_main_json(settings);
    
    std::string sectionJsonPtr = "/assets/sections/" + assetSectionId;
    
    DebugHelper::assert(mainJson->get_bool(sectionJsonPtr + "/deferred"), 
        "(AssetsHelper::get_deferred_asset_info) ", assetSectionId, " is not deferred!");
        
    std::string deferInfoPtr = sectionJsonPtr + "/defer-info";
    
    return DeferredAssetInfo(
        mainJson->get_string(sectionJsonPtr + "/type"),
        mainJson->get_string(deferInfoPtr + "/from-section"),
        mainJson->get_string(deferInfoPtr + "/id-postfix"),
        mainJson->get_string(deferInfoPtr + "/output-path")
    );
}

JsonFile *AssetsHelper::_get_section_json(fs::path pathToAssets, const std::string &assetSectionId) {
    JsonFile *out = nullptr;
    
    JsonFile *mainJson = get_main_json(pathToAssets);
    
    std::string sectionJsonPtr = "/assets/sections/" + assetSectionId;
    
    // Make sure the section build id exists in assets.meta.json
    DebugHelper::assert(mainJson->has(sectionJsonPtr), 
        "(AssetsHelper::_get_section_json) Section \"", assetSectionId, "\" was not found in assets.meta.json");
    
    bool isDeferred = mainJson->get_bool(sectionJsonPtr + "/deferred", false);
    
    if(isDeferred) {
        //DebugHelper::warn("Section \"", assetSectionId, "\" is deferred. Returning null pointer!");
        return nullptr;
    }
    
    fs::path filename = mainJson->get_string(sectionJsonPtr + "/filename");
    
    if(filename.empty()) {
        //DebugHelper::warn("Section \"", assetSectionId, "\" has no filename. Returning null pointer!");
        return nullptr;
    }
    
    fs::path sectionFilepath = pathToAssets / filename;
    
    // Load the section JSON, and throw error if it couldn't be found.
    DebugHelper::assert(JsonHelper::get().get_file(sectionFilepath, &out), 
        "(AssetsHelper::_get_section_json) Could not find section json. Path was ", sectionFilepath);
    
    return out;
}
