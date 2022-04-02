#include "compiler.h"

// Needs to be defined here.
#include "../libs/zip_file.hpp"


const std::string JSON_WRITE_MODE_REPLACE = "replace";
const std::string JSON_WRITE_MODE_MERGE = "merge";
const std::string DEFAULT_JSON_WRITE_MODE = JSON_WRITE_MODE_REPLACE;

const std::string BASE_DIR_NAME = "vanilla";
const std::string EXT_DIR_NAME = "packages";

void print_text(std::string text) {
    std::cout << text << std::endl;
}

void print_coloured_text(std::string color, std::string text) {
    std::cout << color << text << RESET_TEXT << std::endl;
}

AssetCompiler::AssetCompiler() {
    print_text("Compiling assets...");

    std::string assetsDirectory = get_asset_folder_path();
    std::string version = get_version();

    std::string vanillaDirPath = assetsDirectory + "/" + BASE_DIR_NAME;
    std::string outDirPath = assetsDirectory + "/" + version;
    std::string packagesDirPath = assetsDirectory + "/" + EXT_DIR_NAME + "/" + version;
    std::string tempDirPath = assetsDirectory + "/_temp";

    try {
        // 1.) Create temporary directory for working files.
        create_directory(tempDirPath);

        // 2.) Create "compiled" directory for output files
        std::string compiledDir = tempDirPath + "/__compiled__";

        // Copy vanilla folder to the compiled directory as the baseline.
        print_text("Copying vanilla files...");
        recursively_copy_directory(vanillaDirPath + "/" + version, compiledDir);

        print_text("Reading package order...");
        std::string packageOrderFilepath = packagesDirPath + "/order.json";

        bool isVanilla = true;

        if(path_exists(packageOrderFilepath)) {
            std::vector<std::string> packageOrder = get_array_from_json(packageOrderFilepath);
            for(std::string &packageName : packageOrder) {
                print_text("Applying package \"" + packageName + "\"...");
                if(packageName.length() == 0) {
                    display_error_and_abort("The package \"\" does not exist!");
                }
                apply_package(packagesDirPath, packageName, tempDirPath, compiledDir);
                isVanilla = false;
            }
        }

        if(isVanilla) {
            print_coloured_text(CYAN_TEXT, "Assets are vanilla.");
        } else {
            print_coloured_text(CYAN_TEXT, "Assets are modified.");
        }

        print_text("Merging modified files...");
        merge_output(compiledDir, outDirPath);
        
        // Remove the temp directory
        print_text("Cleaning up...");
        delete_directory(tempDirPath);
    } catch (int e) {
        //delete_directory(tempDirPath);
        throw e;
    }

    print_text("Done!");
}

AssetCompiler::~AssetCompiler() {

}

void ensure_meta_json_has_key(std::string &packageName, std::string &metaJsonFilepath, std::string key) {
    if(!json_has_key(metaJsonFilepath, key)) {
        display_error_and_abort("\"", key, "\" not defined in ", packageName, "'s meta.json file!");
    }
}

void AssetCompiler::check_meta_json(std::string &packageName, std::string metaJsonFilepath) {
    if(!path_exists(metaJsonFilepath)) {
        display_error_and_abort("The package \"", packageName, "\" is missing a meta.json file!");
    }

    ensure_meta_json_has_key(packageName, metaJsonFilepath, "name");
    ensure_meta_json_has_key(packageName, metaJsonFilepath, "pkg-version");
    ensure_meta_json_has_key(packageName, metaJsonFilepath, "authors");
    ensure_meta_json_has_key(packageName, metaJsonFilepath, "revision");
    ensure_meta_json_has_key(packageName, metaJsonFilepath, "revision-minor");

    int revision = get_int_from_json(metaJsonFilepath, "revision");
    int revisionMinor = get_int_from_json(metaJsonFilepath, "revision-minor");

    if(revision != REVISION_NUMBER || revisionMinor != REVISION_MINOR_NUMBER) {
        display_error_and_abort("The package \"", packageName, "\" is not supported. It's revision number is ", revision, ".", revisionMinor, ", when it should be ", REVISION_NUMBER, ".", REVISION_MINOR_NUMBER, "!");
    }
}

void AssetCompiler::apply_package(std::string &packagesDirPath, std::string &packageName, std::string &tempDirPath, std::string &outDirPath) {
    std::string packageDir = packagesDirPath + "/" + packageName;

    bool isZip = false;

    if(ends_with(packageName, ".zip")) {
        packageName = packageName.substr(0, packageName.length() - 4);
        isZip = true;
    } else if(!path_exists(packageDir) && path_exists(packageDir + ".zip")) {
        packageDir += ".zip";
        isZip = true;
    } else if(!path_exists(packageDir)) {
        display_error_and_abort("The package \"", packageName, "\" does not exist!");
    }

    if(isZip) {
        miniz_cpp::zip_file file(packageDir);
        packageDir = tempDirPath + "/" + packageName;
        // Make sure a subdirectory with the name of the package exists in the temp directory.
        if(file.has_file("meta.json")) {
            create_directory(packageDir);
            file.extractall(packageDir);
        } else {
            file.extractall(tempDirPath);
        }
    }
    
    check_meta_json(packageName, packageDir + "/meta.json");

    std::vector<std::string> jsonFiles = get_filenames_from_directory_with_extension(packageDir, ".json");
    std::vector<std::string> otherFiles = get_filenames_from_directory_without_extension(packageDir, ".json");
    for(int i = 0; i < jsonFiles.size(); i++) {
        std::string localPath = jsonFiles[i].substr(packageDir.length() + 1);

        if(localPath == "meta.json") {
            continue; // Skip meta.json file.
        }

        std::string outPath = outDirPath + "/" + localPath;

        std::string write_mode = get_string_from_json(jsonFiles[i], "pkg-write");
        make_lowercase(write_mode);
        if(write_mode == "") {
            write_mode = DEFAULT_JSON_WRITE_MODE;
        }

        if(write_mode == JSON_WRITE_MODE_REPLACE) {
            copy_file(jsonFiles[i], outPath);
        } else if(write_mode == JSON_WRITE_MODE_MERGE) {
            combine_json_files(outPath, jsonFiles[i], outPath);
        } else {
            display_error_and_abort("Unknown json write mode: \"", write_mode, "\"");
        }
    }

    for(int i = 0; i < otherFiles.size(); i++) {
        if(path_is_directory(otherFiles[i])) {
            std::string localPath = otherFiles[i].substr(packageDir.length() + 1);
            if(localPath == "meta") {
                continue; // Skip meta folder if it exists.
            }
            std::string outPath = outDirPath + "/" + localPath;
            create_directory(outPath);
        } else {
            std::string localPath = otherFiles[i].substr(packageDir.length() + 1);
            if(starts_with(localPath, "meta/")) {
                continue; // Skip files within the meta folder.
            }
            std::string outPath = outDirPath + "/" + localPath;
            copy_file(otherFiles[i], outPath);
        }
    }
}

void AssetCompiler::merge_output(std::string &tempDir, std::string &outDir) {
    std::vector<std::string> tempFiles = get_filenames_from_directory(tempDir);
    std::vector<std::string> curFiles = get_filenames_from_directory(outDir);
    std::vector<std::string> sameFiles;

    for(int i = 0; i < tempFiles.size(); i++) {
        std::string tempFilepath = tempFiles[i];
        std::string localPath = tempFilepath.substr(tempDir.length() + 1);
        if(path_exists(outDir + "/" + localPath)) {
            sameFiles.push_back(localPath);
            tempFiles.erase(tempFiles.begin() + i);
            i--;
        }
    }

    for(int i = 0; i < curFiles.size(); i++) {
        std::string curOutFilepath = curFiles[i];
        std::string localPath = curOutFilepath.substr(outDir.length() + 1);
        if(path_exists(tempDir + "/" + localPath)) {
            curFiles.erase(curFiles.begin() + i);
            i--;
        }
    }

    // tempFiles now only has files that only exist in the temp directory. (Need to get added)
    // curFiles now only has files that only exist in the current output directory. (Need to get deleted)
    // sameFiles only has files that exist in both directories. (Need to compare their hashes)

    for(std::string &pathToRemove : curFiles) {
        delete_path(pathToRemove);
    }
    
    for(std::string &pathToAdd : tempFiles) {
        std::string localPath = pathToAdd.substr(tempDir.length() + 1);
        std::string outAddPath = outDir + "/" + localPath;
        if(path_is_directory(pathToAdd)) {
            create_directory(outAddPath);
        } else {
            copy_file(pathToAdd, outAddPath);
        }
    }
    
    for(std::string &sameFileLocalPath : sameFiles) {
        std::string tempFilePath = tempDir + "/" + sameFileLocalPath;
        std::string curFilePath = outDir + "/" + sameFileLocalPath;
        if(!path_is_directory(tempFilePath)) {
            bool doHashCheck = true;
            if(ends_with(tempFilePath, ".json")) {
                std::string pkgRebuild = "onchange";
                if(json_has_key(tempFilePath, "pkg-rebuild")) {
                    pkgRebuild = get_string_from_json(tempFilePath, "pkg-rebuild");
                    make_lowercase(pkgRebuild);
                }
                if(pkgRebuild == "always") {
                    doHashCheck = false;
                } else if(pkgRebuild == "onchange") {
                    doHashCheck = true;
                } else {
                    display_error_and_abort("Unknown pkg-rebuild value \"", pkgRebuild, "\".");
                }
            }
            if(doHashCheck) {
                std::string tempFileHash = calculate_file_md5(tempFilePath);
                std::string curFileHash = calculate_file_md5(curFilePath);
                if(tempFileHash == curFileHash) {
                    continue;
                }
            }
            copy_file(tempFilePath, curFilePath);
        }
    }
}


