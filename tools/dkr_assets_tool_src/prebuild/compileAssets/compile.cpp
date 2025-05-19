#include "compile.h"

#include "helpers/dataHelper.h"
#include "helpers/jsonHelper.h"
#include "libs/zip_file.hpp"

#include "misc/globalSettings.h"

using namespace DkrAssetsTool;

void check_mod_path(fs::path &modPath) {
    if(!FileHelper::path_exists(modPath)) {
        // This might just be a zip file. See if adding .zip as the extension will find it.
        fs::path tryZipPath = modPath;
        tryZipPath.replace_extension(".zip");
        if(FileHelper::path_exists(tryZipPath)) {
            modPath = tryZipPath;
        } else {
            DebugHelper::error("(check_mod_path) Path ", modPath, " does not exist!");
        }
    }
}

// Check if the number of mods has changed.
bool compile_check_order_size(size_t modOrderCount, StatJsonFile &statFile) {
    size_t lastOrderCount = statFile.get_value<int>("/last-order-size", 0);
    return modOrderCount != lastOrderCount;
}

// Check if the order of the mods was changed.
bool compile_check_order_of_mods(size_t modOrderCount, const JsonFile &modOrderFile, StatJsonFile &statFile) {
    if(modOrderCount < 2) {
        return false;
    }
    for(size_t i = 0; i < modOrderCount; i++) {
        std::string modName = modOrderFile.get_string("/order/" + std::to_string(i));
        std::string lastModName = statFile.get_value<std::string>("/last-mod-order/" + std::to_string(i) , "");
        if(modName != lastModName) {
            return true;
        }
    }
    
    return false;
}

void update_last_mod_order(size_t modOrderCount, const JsonFile &modOrderFile, StatJsonFile &statFile) {
    for(size_t i = 0; i < modOrderCount; i++) {
        std::string modName = modOrderFile.get_string("/order/" + std::to_string(i));
        statFile.set_value<std::string>("/last-mod-order/" + std::to_string(i), modName);
    }
}

// Check if any of the mod files have been updated.
bool compile_check_order_files_updated(size_t modOrderCount, const JsonFile &modOrderFile, StatJsonFile &statFile, std::vector<fs::path> &modFilesModified) {
    std::unordered_map<fs::path, std::string, PathHash> lastModifiedDates;
    
    for(size_t i = 0; i < modOrderCount; i++) {
        std::string modFolderName = modOrderFile.get_string("/order/" + std::to_string(i));
        
        if(modFolderName.empty()) {
            continue;
        }
        
        fs::path modPath = GlobalSettings::get_decomp_path("mods-subpath", "mods/") / "assets";
        
        // Make sure the path is valid.
        check_mod_path(modPath);
        
        // is_zip_file() checks the first 4 bytes to see if the file contains the standard .zip signature.
        if(FileHelper::is_zip_file(modPath)) {
            // If it is a zip file, then we only care about the archive file itself. Not it's contents
            lastModifiedDates[modPath] = FileHelper::get_last_modified_timestamp(modPath);
        } else {
            // Insert the timestamps from all the files in modPath into lastModifiedDates
            FileHelper::insert_timestamps_from_directory(modPath, lastModifiedDates);
        }
    }
    
    modFilesModified.clear();
    
    for(auto &pair : lastModifiedDates) {
        std::string statModifiedDate = statFile.get_entry(pair.first);
        
        // If the file isn't on record, or if the modified date has changed, then we should compile!
        if(statModifiedDate.empty() || (statModifiedDate != pair.second)) {
            statFile.set_entry(pair.first, pair.second);
            modFilesModified.push_back(pair.first);
        }
    }
    
    return modFilesModified.size() > 0;
}

void merge_or_copy_file(fs::path &modDir, fs::path &path) {
    fs::path modPath = modDir / path;
    fs::path outPath = GlobalSettings::get_decomp_path_to_output_assets() / path;
    
    bool copyFile = (path.extension() != ".json") || !FileHelper::path_exists(outPath);
    
    if(copyFile) {
        FileHelper::copy(modPath, outPath);
    } else { // Merge file
        JsonHelper::patch_json(outPath, modPath);
    }
}


void merge_and_copy_files(size_t modOrderCount, const JsonFile &modOrderFile, std::vector<fs::path> &modFilesModified) {
    std::vector<fs::path> modDirectories(modOrderCount);
    
    for(size_t i = 0; i < modOrderCount; i++) {
        std::string modFolderName = modOrderFile.get_string("/order/" + std::to_string(i));
        
        if(modFolderName.empty()) {
            continue;
        }
        
        modDirectories[i] = GlobalSettings::get_decomp_path("mods-subdir", "mods/") / "assets" / modFolderName;
        
        // Make sure the path exists.
        check_mod_path(modDirectories[i]); 
    }
    
    for(fs::path &modDir : modDirectories) {
        if(FileHelper::is_zip_file(modDir)) {
            DebugHelper::info_verbose("Applying Asset Mod: ", modDir, " (zip archive)");
        
            fs::path modName = modDir.stem();
            
            fs::path extractedDir = GlobalSettings::get_decomp_path("mods-subdir", "mods/") / "assets" / ".extracted";
            
            const bool zipFileHasChanged = DataHelper::vector_has<fs::path>(modFilesModified, modDir);
            
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
            
            modDir = GlobalSettings::get_decomp_path("mods-subdir", "mods/") / "assets" / ".extracted" / modName;
            
            DebugHelper::assert_(FileHelper::path_exists(modDir), 
                "(merge_and_copy_files) Path ", modDir, " does not exist!");
        } else {
            DebugHelper::info_verbose("Applying Asset Mod: ", modDir);
        }
        
        std::unordered_map<fs::path, std::vector<fs::path>, PathHash> modFiles;
        FileHelper::append_files_from_directory_relative(modDir, modFiles[modDir]);
        for(fs::path &path : modFiles[modDir]) {
            if(FileHelper::does_filename_equal(path, "meta.json")) { 
                // Don't copy meta.json over.
                continue;
            }
            merge_or_copy_file(modDir, path);
        }
    }
}
void compile_assets(size_t modOrderCount, const JsonFile &modOrderFile, StatJsonFile &statFile, std::vector<fs::path> &modFilesModified) {
    statFile.set_value<int>("/last-order-size", modOrderCount);
    
    fs::path vanillaDir = GlobalSettings::get_decomp_path_to_vanilla_assets();
    fs::path outDir = GlobalSettings::get_decomp_path_to_output_assets(false);
    
    // Clear the output directory (if it exists)
    FileHelper::delete_directory(outDir);
    
    if(modOrderCount == 0) {
        DebugHelper::info("Done! (Vanilla)");
        return;
    }
    
    // Copy all the vanilla files over to the output directory
    FileHelper::copy(vanillaDir, outDir, true);
    
    merge_and_copy_files(modOrderCount, modOrderFile, modFilesModified);
    
    DebugHelper::info("Done! (", modOrderCount, (modOrderCount == 1) ? " mod)" : " mods)");
}

void CompileAssets::compile() {
    DebugHelper::info("Compiling modded assets...");
    
    std::vector<fs::path> modFilesModified;
    
    StatJsonFile statFile(GlobalSettings::get_decomp_path("cache_subdir", ".cache/") / "compileAssetsCache.json");
    
    // Load order.json
    auto tryGetModOrderFile = JsonHelper::get_file(GlobalSettings::get_decomp_path("mods-subdir", "mods/") / "assets/order.json");
    
    if(!tryGetModOrderFile.has_value()) {
        DebugHelper::warn("Could not find mods/assets/order.json");
        return;
    }
    
    const JsonFile &modOrderFile = tryGetModOrderFile.value();

    size_t modOrderCount = modOrderFile.length_of_array("/order");
    
    bool doCompile = 
        compile_check_order_size(modOrderCount, statFile);
    
    if(!doCompile && (modOrderCount > 0)) {
        // Only do these checks if there are any entries in the order.json file.
        doCompile = compile_check_order_of_mods(modOrderCount, modOrderFile, statFile) || 
                    compile_check_order_files_updated(modOrderCount, modOrderFile, statFile, modFilesModified);
    }
    
    if(doCompile) {
        compile_assets(modOrderCount, modOrderFile, statFile, modFilesModified);
        update_last_mod_order(modOrderCount, modOrderFile, statFile);
        statFile.save();
    }
}