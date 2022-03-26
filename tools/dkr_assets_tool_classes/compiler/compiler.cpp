#include "compiler.h"

// Needs to be defined here.
#include "../libs/zip_file.hpp"

const std::string BASE_DIR_NAME = "vanilla";
const std::string EXT_DIR_NAME = "packages";

AssetCompiler::AssetCompiler() {
    std::cout << "Compiling assets..." << std::endl;

    std::string assetsDirectory = get_asset_folder_path();
    std::string version = get_version();

    std::string vanillaDirPath = assetsDirectory + "/" + BASE_DIR_NAME;
    std::string outDirPath = assetsDirectory + "/" + version;
    std::string packagesDirPath = assetsDirectory + "/" + EXT_DIR_NAME + "/" + version;
    
    // Deletes the output directory if it currently exists.
    std::cout << "Deleting \"" << outDirPath << "\"..." << std::endl;
    delete_directory(outDirPath); 

    // Copy vanilla folder to the output directory as the baseline.
    std::cout << "Copying vanilla files..." << std::endl;
    recursively_copy_directory(vanillaDirPath + "/" + version, outDirPath);

    std::cout << "Reading package order..." << std::endl;
    std::string packageOrderFilepath = packagesDirPath + "/order.json";
    if(path_exists(packageOrderFilepath)) {
        std::vector<std::string> packageOrder = get_array_from_json(packageOrderFilepath);
        for(std::string &packageName : packageOrder) {
            std::cout << "Applying package: " << packageName << std::endl;
            apply_package(packagesDirPath, packageName, outDirPath);
        }
    }
    
    // Remove the temp directory if it exists.
    if(path_exists(packagesDirPath + "/_temp")) {
        delete_directory(packagesDirPath + "/_temp");
    }

    std::cout << "Done!" << std::endl;
}

AssetCompiler::~AssetCompiler() {

}

void AssetCompiler::apply_package(std::string &packagesDirPath, std::string &packageName, std::string &outDirPath) {
    std::string packageDir = packagesDirPath + "/" + packageName;

    bool isZip = false;

    if(ends_with(packageName, ".zip")) {
        packageName = packageName.substr(0, packageName.length() - 4);
        isZip = true;
    } else if(!path_exists(packageDir) && path_exists(packageDir + ".zip")) {
        packageDir += ".zip";
        isZip = true;
    }

    // Extract zip to a temp directory and use that directory.
    if(isZip) {
        std::string tempDirPath = packagesDirPath + "/_temp";
        create_directory(tempDirPath);
        miniz_cpp::zip_file file(packageDir);
        packageDir = tempDirPath + "/" + packageName;
        // Make sure a subdirectory with the name of the package exists in the temp directory.
        if(!file.has_file(packageName + "/")) {
            create_directory(packageDir);
            file.extractall(packageDir);
        } else {
            file.extractall(tempDirPath);
        }
    }

    copy_stuff_from_folders(packageDir, outDirPath);
    append_manifest_files(packageDir, outDirPath);
}

void AssetCompiler::copy_stuff_from_folders(std::string &packageDir, std::string &outDirPath) {
    std::vector<fs::path> packageFolders = get_folders_from_directory_only(packageDir);
    for(int i = 0; i < packageFolders.size(); i++) {
        std::string folderPath = packageFolders[i].string();
        verify_json_files(folderPath);
        recursively_copy_directory(folderPath, outDirPath + "/" + packageFolders[i].filename().string());
    }
}

void AssetCompiler::append_manifest_files(std::string &packageDir, std::string &outDirPath) {
    std::vector<fs::path> packageFiles = get_filenames_from_directory_only_with_extension(packageDir, ".json");
    std::string curDataPath, newDataPath;
    for(int i = 0; i < packageFiles.size(); i++) {
        std::string filename = packageFiles[i].filename().string();
        // meta.json is a special file, so ignore it!
        if(filename == "meta.json") { 
            continue;
        }
        newDataPath = packageFiles[i].string();
        curDataPath = outDirPath + "/" + filename;
        combine_json_files(curDataPath, newDataPath, curDataPath);
    }
}

// TODO: Implement more checks. Maybe add option to skip verification?
void AssetCompiler::verify_json_files(std::string &folderPath) {
    std::vector<std::string> jsonFiles = get_filenames_from_directory_with_extension(folderPath, ".json");
    for(std::string &jsonFilePath : jsonFiles) {
        // Need to make sure that all the json files within directories have a type in them.
        std::string jsonFileType = get_string_from_json(jsonFilePath, "type");
        if(jsonFileType == "") {
            display_error_and_abort("\"", jsonFilePath, "\" does not have a type.");
        }
    }
}


