#include "compiler.h"

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
            std::string packageDir = packagesDirPath + "/" + packageName;
            copy_stuff_from_folders(packageDir, outDirPath, packageName);
            append_manifest_files(packageDir, outDirPath, packageName);
        }
    }
    std::cout << "Done!" << std::endl;
}

AssetCompiler::~AssetCompiler() {

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

void AssetCompiler::copy_stuff_from_folders(std::string &packageDir, std::string &outDirPath, std::string &packageName) {
    std::vector<fs::path> packageFolders = get_folders_from_directory_only(packageDir);
    for(int i = 0; i < packageFolders.size(); i++) {
        std::string folderPath = packageFolders[i].string();
        verify_json_files(folderPath);
        recursively_copy_directory(folderPath, outDirPath + "/" + packageFolders[i].filename().string());
    }
}

void AssetCompiler::append_manifest_files(std::string &packageDir, std::string &outDirPath, std::string &packageName) {
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


