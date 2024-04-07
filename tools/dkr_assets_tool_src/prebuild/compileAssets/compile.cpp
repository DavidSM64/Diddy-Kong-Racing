#include "compile.h"

#include "helpers/dataHelper.h"
#include "libs/zip_file.hpp"

CompileAssets::CompileAssets(DkrAssetsSettings &settings) : _settings(settings) {
    _vanillaAssetsPath = _settings.pathToAssets / ".vanilla" / settings.dkrVersion;
    _outAssetsPath = _settings.pathToAssets / settings.dkrVersion;
    
    _statFile = new StatJsonFile(_settings.pathToCache / "compileAssetsCache.json");
    
    // Load order.json
    DebugHelper::assert_(JsonHelper::get().get_file(_settings.pathToModAssets / "order.json", &_modOrderFile),
        "Failed to get order.json for compiling!");

    _modOrderCount = _modOrderFile->length_of_array("/order");
    
    bool doCompile = 
        _compile_check_assets_exist() ||
        _compile_check_order_size();
    
    if(!doCompile && (_modOrderCount > 0)) {
        // Only do these checks if there are any entries in the order.json file.
        doCompile = _compile_check_order_of_mods() ||
                    _compile_check_order_files_updated();
    }
    
    if(doCompile) {
        _compile_assets();
        _update_last_mod_order();
        _statFile->save();
    }
}

CompileAssets::~CompileAssets() {
    delete _statFile;
}

void CompileAssets::_check_mod_path(fs::path &modPath) {
    if(!FileHelper::path_exists(modPath)) {
        // This might just be a zip file. See if adding .zip as the extension will find it.
        fs::path tryZipPath = modPath;
        tryZipPath.replace_extension(".zip");
        if(FileHelper::path_exists(tryZipPath)) {
            modPath = tryZipPath;
        } else {
            DebugHelper::error("(CompileAssets::_check_mod_path) Path ", modPath, " does not exist!");
        }
    }
}

// Check if the main assets folder exists.
bool CompileAssets::_compile_check_assets_exist() {
    return !FileHelper::path_exists(_outAssetsPath);
}

// Check if the number of mods has changed.
bool CompileAssets::_compile_check_order_size() {
    size_t lastOrderCount = _statFile->get_value<int>("/last-order-size", 0);
    return _modOrderCount != lastOrderCount;
}

// Check if the order of the mods was changed.
bool CompileAssets::_compile_check_order_of_mods() {
    if(_modOrderCount < 2) {
        return false;
    }
    for(size_t i = 0; i < _modOrderCount; i++) {
        std::string modName = _modOrderFile->get_string("/order/" + std::to_string(i));
        std::string lastModName = _statFile->get_value<std::string>("/last-mod-order/" + std::to_string(i) , "");
        if(modName != lastModName) {
            return true;
        }
    }
    
    return false;
}

void CompileAssets::_update_last_mod_order() {
    for(size_t i = 0; i < _modOrderCount; i++) {
        std::string modName = _modOrderFile->get_string("/order/" + std::to_string(i));
        _statFile->set_value<std::string>("/last-mod-order/" + std::to_string(i), modName);
    }
}

// Check if any of the mod files have been updated.
bool CompileAssets::_compile_check_order_files_updated() {
    for(size_t i = 0; i < _modOrderCount; i++) {
        std::string modFolderName = _modOrderFile->get_string("/order/" + std::to_string(i));
        
        if(modFolderName.empty()) {
            continue;
        }
        
        fs::path modPath = _settings.pathToModAssets / modFolderName;
        
        // Make sure the path is valid.
        _check_mod_path(modPath);
        
        // is_zip_file() checks the first 4 bytes to see if the file contains the standard .zip signature.
        if(FileHelper::is_zip_file(modPath)) {
            // If it is a zip file, then we only care about the archive file itself. Not it's contents
            _lastModifiedDates[modPath] = FileHelper::get_last_modified_timestamp(modPath);
        } else {
            // Insert the timestamps from all the files in modPath into _lastModifiedDates
            FileHelper::insert_timestamps_from_directory(modPath, _lastModifiedDates);
        }
    }
    
    _modFilesModified.clear();
    
    for(auto &pair : _lastModifiedDates) {
        std::string statModifiedDate = _statFile->get_entry(pair.first);
        
        // If the file isn't on record, or if the modified date has changed, then we should compile!
        if(statModifiedDate.empty() || (statModifiedDate != pair.second)) {
            _statFile->set_entry(pair.first, pair.second);
            _modFilesModified.push_back(pair.first);
        }
    }
    
    return _modFilesModified.size() > 0;
}

void CompileAssets::_compile_assets() {
    DebugHelper::info("Compiling assets...");
    
    _statFile->set_value<int>("/last-order-size", _modOrderCount);
    
    // First clear the output directory (if it exists)
    FileHelper::delete_directory(_outAssetsPath);
    
    // Copy all the vanilla files over to the output directory
    FileHelper::copy(_vanillaAssetsPath, _outAssetsPath, true);
    
    if(_modOrderCount == 0) {
        DebugHelper::info("Done! (Vanilla)");
        return;
    }
    
    _merge_and_copy_files();
    
    DebugHelper::info("Done! (", _modOrderCount, (_modOrderCount == 1) ? " mod)" : " mods)");
}

void CompileAssets::_merge_and_copy_files() {
    std::vector<fs::path> modDirectories(_modOrderCount);
    
    for(size_t i = 0; i < _modOrderCount; i++) {
        std::string modFolderName = _modOrderFile->get_string("/order/" + std::to_string(i));
        
        if(modFolderName.empty()) {
            continue;
        }
        
        modDirectories[i] = _settings.pathToModAssets / modFolderName;
        
        // Make sure the path exists.
        _check_mod_path(modDirectories[i]); 
    }
    
    for(fs::path &modDir : modDirectories) {
        if(FileHelper::is_zip_file(modDir)) {
            DebugHelper::info_verbose("Applying Asset Mod: ", modDir, " (zip archive)");
        
            fs::path modName = modDir.stem();
            
            fs::path extractedDir = _settings.pathToModAssets / ".extracted";
            
            const bool zipFileHasChanged = DataHelper::vector_has<fs::path>(_modFilesModified, modDir);
            
            // Only extract if the zip file changed or if the mod's extracted folder does not exist.
            if(zipFileHasChanged || !FileHelper::path_exists(extractedDir / modName)) {
                DebugHelper::info_verbose("Extracting: ", modDir);
                
                miniz_cpp::zip_file file(modDir);
                // Make sure a subdirectory with the name of the mod exists in the .extracted directory.
                if(file.has_file("meta.json")) {
                    extractedDir /= modName;
                }
                FileHelper::write_folder_if_it_does_not_exist(extractedDir);
                file.extractall(extractedDir);
            }
            
            modDir = _settings.pathToModAssets / ".extracted" / modName;
            
            DebugHelper::assert_(FileHelper::path_exists(modDir), 
                "(CompileAssets::_merge_and_copy_files) Path ", modDir, " does not exist!");
        } else {
            DebugHelper::info_verbose("Applying Asset Mod: ", modDir);
        }
        
        FileHelper::append_files_from_directory_relative(modDir, _modFiles[modDir]);
        for(fs::path &path : _modFiles[modDir]) {
            if(FileHelper::does_filename_equal(path, "meta.json")) { 
                // Don't copy meta.json over.
                continue;
            }
            _merge_or_copy_file(modDir, path);
        }
    }
}

void CompileAssets::_merge_or_copy_file(fs::path &modDir, fs::path &path) {
    fs::path modPath = modDir / path;
    fs::path outPath = _outAssetsPath / path;
    
    bool copyFile = (path.extension() != ".json") || !FileHelper::path_exists(outPath);
    
    if(copyFile) {
        FileHelper::copy(modPath, outPath);
    } else { // Merge file
        JsonHelper::get().patch_json(outPath, modPath);
    }
    
}