#include "compiler.h"

const std::string BASE_DIR_NAME = "vanilla";
const std::string EXT_DIR_NAME = "packages";

AssetCompiler::AssetCompiler(std::string assetsDirectory, std::string version) {
    std::string vanillaDirPath = assetsDirectory + "/" + BASE_DIR_NAME;
    std::string outDirPath = assetsDirectory + "/" + version;
    std::string packagesDirPath = assetsDirectory + "/" + EXT_DIR_NAME + "/" + version;
    
    // Deletes the output directory if it currently exists.
    delete_directory(outDirPath); 

    // Copy vanilla folder to the output directory as the baseline.
    recursively_copy_directory(vanillaDirPath + "/" + version, outDirPath);

    std::string packageOrderFilepath = packagesDirPath + "/order.json";
    if(path_exists(packageOrderFilepath)) {
        std::vector<std::string> packageOrder = get_array_from_json(packageOrderFilepath);
        for(std::string &packageName : packageOrder) {
            std::string packageDir = packagesDirPath + "/" + packageName;
            copy_stuff_from_folders(packageDir, outDirPath, packageName);
            append_manifest_files(packageDir, outDirPath, packageName);
        }
    }
}

AssetCompiler::~AssetCompiler() {

}

void AssetCompiler::copy_stuff_from_folders(std::string &packageDir, std::string &outDirPath, std::string &packageName) {
    std::vector<fs::path> packageFolders = get_folders_from_directory_only(packageDir);
    for(int i = 0; i < packageFolders.size(); i++) {
        recursively_copy_directory(packageFolders[i].string(), outDirPath + "/" + packageFolders[i].filename().string());
    }
}

void AssetCompiler::append_manifest_files(std::string &packageDir, std::string &outDirPath, std::string &packageName) {
    std::vector<fs::path> packageFiles = get_filenames_from_directory_only_with_extension(packageDir, ".json");
    std::string curDataPath, newDataPath;
    for(int i = 0; i < packageFiles.size(); i++) {
        std::string filename = packageFiles[i].filename().string();
        if(filename == "meta.json") { 
            continue;
        }
        newDataPath = packageFiles[i].string();
        curDataPath = outDirPath + "/" + filename;
        combine_json_files(curDataPath, newDataPath, curDataPath);
    }
}


