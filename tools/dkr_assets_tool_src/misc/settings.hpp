#pragma once

#include <thread>
#include <string>
#include <vector>
#include <cmath>
#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/jsonHelper.h"
#include "misc/constants.hpp"

// Some paths to find if a directory is considered to be the "root" of the decomp.
const std::vector<fs::path> REPO_ROOT_FIND_PATHS = {
    "src",
    "libultra",
    "include",
    "baseroms",
    "README.md"
};

struct DkrAssetsSettings {
    std::string dkrVersion;
    
    // TODO: Maybe redo this? Feels like it could be better.
    fs::path pathToRepo;
    fs::path pathToBaseroms;
    fs::path pathToAssets;
    fs::path pathToConfigs;
    fs::path pathToInclude;
    fs::path pathToAsm;
    fs::path pathToData;
    fs::path pathToBuild;
    fs::path pathToCache;
    fs::path pathToMods;
    fs::path pathToModAssets;
    
    double modelScale;
    size_t threadCount;
    
    // Keep binary copies of uncompressed data. (For comparison).
    bool debugExtractKeepUncompressed;
    bool debugBuildKeepUncompressed;
    
    void print() {
        DebugHelper::info(
            "\n--------------- Settings ---------------",
            "\n DKR Version: ", dkrVersion,
            "\n Repo Path: ", pathToRepo,
            "\n Baseroms Path: ", pathToBaseroms,
            "\n Assets Path: ", pathToAssets,
            "\n Configs Path: ", pathToConfigs,
            "\n Include Path: ", pathToInclude,
            "\n ASM Path: ", pathToAsm,
            "\n Data Path: ", pathToData,
            "\n Build Path: ", pathToBuild,
            "\n Model Scale: ", modelScale,
            "\n Mods Path: ", pathToMods,
            "\n Mod Assets Path: ", pathToModAssets,
            "\n Threads: ", threadCount,
            "\n----------------------------------------"
        );
    }
    
    template <typename T>
    double adjust_to_model_scale(T val) {
        return ((double)val) * modelScale;
    }
    
    template <typename T>
    double adjust_from_model_scale(T val) {
        return std::round(((double)val) * (1.0 / modelScale));
    }
    
    fs::path find_repo_root() {
        fs::path start = fs::absolute(".");
        fs::path cur = start;
        
        while(cur.has_parent_path()) {
            bool foundIt = true;
            for(const fs::path &findFile : REPO_ROOT_FIND_PATHS) {
                if(!FileHelper::path_exists(cur / findFile)) {
                    foundIt = false;
                    break;
                }
            }
            if(foundIt) {
                return fs::relative(cur, start);
            }
            cur = cur.parent_path(); // Go up one level.
        }
        
        DebugHelper::error("Could not find the DKR repo path from: ", start);
        return "";
    }
    
    void load_from_json(const std::string &jsonPath) {
        _settingsFileExists = JsonHelper::get().get_file(jsonPath, &_settingsJson);
        
        _load_string_from_ptr(dkrVersion, "/default_dkr_version", DEFAULT_DKR_VERSION);
        
        _load_bool_from_ptr(debugExtractKeepUncompressed, "/debug/keep-uncompressed", false);
        _load_bool_from_ptr(debugBuildKeepUncompressed, "/debug/keep-uncompressed", false);
        
        _load_path_from_ptr(pathToRepo, "/repo_path", find_repo_root());
        
        // Internal cache directory to be used for this tool only.
        _load_path_from_ptr(pathToCache, "/cache", DEFAULT_CACHE_SUBPATH);
        
        // Load subpaths
        _load_subpath_from_ptr(pathToBaseroms, "/baseroms_subpath", DEFAULT_BASEROMS_SUBPATH);
        _load_subpath_from_ptr(pathToAssets,   "/assets_subpath"  , DEFAULT_ASSETS_SUBPATH);
        _load_subpath_from_ptr(pathToConfigs,  "/configs_subpath" , DEFAULT_CONFIGS_SUBPATH);
        _load_subpath_from_ptr(pathToInclude,  "/include_subpath" , DEFAULT_INCLUDE_SUBPATH);
        _load_subpath_from_ptr(pathToMods, "/mods_subpath", DEFAULT_MODS_SUBPATH);
        
        std::string localAsmPath;
        std::string localSrcPath;
        std::string localLibAsmPath;
        std::string localLibSrcPath;
        std::string localModAssetsPath;
        
        _load_string_from_ptr(localAsmPath, "/asm_subpath", DEFAULT_ASM_SUBPATH);
        _load_string_from_ptr(localModAssetsPath, "/mod_assets_subpath", DEFAULT_MOD_ASSETS_SUBPATH);
        
        _format_subpath(pathToAsm, pathToRepo, localAsmPath);
        _format_subpath(pathToModAssets, pathToMods, localModAssetsPath);
        
        // Build subdirectories
        _load_subpath_from_ptr(pathToBuild, "/build_subpath", DEFAULT_BUILD_SUBPATH);
        
        _load_subpath_from_ptr(pathToData, "/data_subpath", DEFAULT_DATA_SUBPATH);
        
        _load_float_ptr(modelScale, "/model_scale", DEFAULT_MODEL_SCALE_GLTF);
        
        _load_size_ptr(threadCount, "/threads", (size_t)std::thread::hardware_concurrency());
    }
    
    DkrAssetsSettings() {
        pathToRepo = find_repo_root();
        load_from_json(pathToRepo / "tools" / DKRAT_SETTINGS_FILE);
    }
    
private:
    bool _settingsFileExists;
    JsonFile *_settingsJson;
    
    void _format_subpath(fs::path &pathVar, fs::path &parent, std::string &child) {
        pathVar = parent / fs::path(child);
        FileHelper::format_folder_string(pathVar);
    }
    
    void _load_subpath_from_ptr(fs::path &pathVar, const char *ptr, const std::string defaultValue) {
        pathVar = pathToRepo;
        pathVar /= (_settingsFileExists) ? _settingsJson->get_string(ptr, defaultValue) : defaultValue;
        FileHelper::format_folder_string(pathVar);
    }
    
    void _load_path_from_ptr(fs::path &pathVar, const char *ptr, const std::string defaultValue) {
        pathVar = (_settingsFileExists) ? _settingsJson->get_string(ptr, defaultValue) : defaultValue;
        FileHelper::format_folder_string(pathVar);
    }
    
    void _load_string_from_ptr(std::string &strVar, const char *ptr, const std::string defaultValue) {
        strVar = (_settingsFileExists) ? _settingsJson->get_string(ptr, defaultValue) : defaultValue;
    }
    
    void _load_bool_from_ptr(bool &strVar, const char *ptr, const bool defaultValue) {
        strVar = (_settingsFileExists) ? _settingsJson->get_bool(ptr, defaultValue) : defaultValue;
    }
    
    void _load_float_ptr(double &doubleVar, const char *ptr, const double defaultValue) {
        doubleVar = (_settingsFileExists) ? _settingsJson->get_float(ptr, defaultValue) : defaultValue;
    }
    
    void _load_size_ptr(size_t &sizeVar, const char *ptr, const size_t defaultValue) {
        sizeVar = (_settingsFileExists) ? _settingsJson->get_int(ptr, defaultValue) : defaultValue;
    }
};
