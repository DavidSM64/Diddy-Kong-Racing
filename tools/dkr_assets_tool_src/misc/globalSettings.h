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
    fs::path get_decomp_path_to_output_assets(); // Gets the path to "<root>/assets/<dkrVersion>". Throws an error if a path could not be found.
    fs::path get_decomp_path_to_vanilla_assets(); // Gets the path to "<root>/assets/.vanilla/<dkrVersion>". Throws an error if a path could not be found.
    
    size_t get_max_thread_count();
};
};
