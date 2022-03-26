#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../common/util.h"
#include "../common/types.h"

class AssetCompiler {
public:
    AssetCompiler();
    ~AssetCompiler();
private:
    void apply_package(std::string &packagesDirPath, std::string &packageName, std::string &outDirPath);
    void copy_stuff_from_folders(std::string &packagesDirPath, std::string &outDirPath);
    void append_manifest_files(std::string &packagesDirPath, std::string &outDirPath);
    void verify_json_files(std::string &folderPath);
};
