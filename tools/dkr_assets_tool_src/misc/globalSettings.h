#pragma once

#include <optional>
#include "helpers/fileHelper.h"

namespace DkrAssetsTool {
namespace GlobalSettings {

    template <typename T>
    T get_value(std::string key, T defaultValue);

    template <typename T>
    void set_value(std::string key, T value);

    void parse_values_from_json_file(fs::path pathToJsonFile);

    void print_all_values();
    
    std::string get_dkr_version(); // Alias of Args::get_dkr_version()
    std::optional<fs::path> find_decomp_root();
    fs::path get_decomp_path(std::string key, fs::path defaultSubpath);
    
    // Gets the path to "<root>/assets/<dkrVersion>". 
    // Will use get_decomp_path_to_vanilla_assets() if output dir could not be found and fallbackToVanillaPath is true.
    fs::path get_decomp_path_to_output_assets(bool fallbackToVanillaPath=true); 
    
    // Gets the path to "<root>/assets/.vanilla/<dkrVersion>".
    fs::path get_decomp_path_to_vanilla_assets(); 
    
    size_t get_max_thread_count();
};
};
