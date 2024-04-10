#pragma once

#include <unordered_map>
#include <vector>

#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"

#include "misc/settings.hpp"

class CompileAssets {
public:
    CompileAssets(DkrAssetsSettings &settings);
    ~CompileAssets();
private:
    DkrAssetsSettings &_settings;
    fs::path _outAssetsPath;
    fs::path _vanillaAssetsPath;
    StatJsonFile *_statFile;
    JsonFile *_modOrderFile;
    size_t _modOrderCount;
    
    std::unordered_map<fs::path, std::string, PathHash> _lastModifiedDates;
    std::unordered_map<fs::path, std::vector<fs::path>, PathHash> _modFiles;
    std::vector<fs::path> _modFilesModified;
    
    void _check_mod_path(fs::path &modPath);
    
    bool _compile_check_assets_exist();
    bool _compile_check_order_size();
    bool _compile_check_order_of_mods();
    bool _compile_check_order_files_updated();
    
    void _update_last_mod_order();
    
    void _compile_assets();
    void _merge_and_copy_files();
    void _merge_or_copy_file(fs::path &modDir, fs::path &path);
};
