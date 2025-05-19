#pragma once

#include <string>

namespace DkrAssetsTool {

const std::string DKRAT_NAME = "DKR Assets Tool";
const int DKRAT_VERSION_RELEASE = 0;
const int DKRAT_VERSION_MAJOR = 5;
const int DKRAT_VERSION_MINOR = 0;
const std::string DKRAT_VERSION = "Version " + std::to_string(DKRAT_VERSION_RELEASE) + "."
                                             + std::to_string(DKRAT_VERSION_MAJOR) + "."
                                             + std::to_string(DKRAT_VERSION_MINOR);

const std::string DKRAT_SETTINGS_FILE = "dkr_assets_tool_settings.json";

const std::string DEFAULT_BASEROMS_SUBPATH = "baseroms/";
const std::string DEFAULT_ASSETS_SUBPATH = "assets/";
const std::string DEFAULT_CONFIGS_SUBPATH = "extract-ver/";
const std::string DEFAULT_INCLUDE_SUBPATH = "include/";
const std::string DEFAULT_ASM_SUBPATH = "asm/";
const std::string DEFAULT_DATA_SUBPATH = "data/";
const std::string DEFAULT_BUILD_SUBPATH = "build/";
const std::string DEFAULT_CACHE_SUBPATH = ".cache/";
const std::string DEFAULT_MODS_SUBPATH = "mods/";
const std::string DEFAULT_MOD_ASSETS_SUBPATH = "assets/";

// Debugging stuff
const bool DEFAULT_VERBOSE_VALUE = true; 
const bool USING_ASSERTS = true;

const double DEFAULT_MODEL_SCALE_GLTF = 1.0 / 1000.0;

const double DKR_FPS = 60.0; // For time conversions

}
