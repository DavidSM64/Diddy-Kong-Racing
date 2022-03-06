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
    AssetCompiler(std::string assetsDirectory, std::string version);
    ~AssetCompiler();
private:
    void copy_stuff_from_folders(std::string &packagesDirPath, std::string &outDirPath, std::string &packageName);
    void append_manifest_files(std::string &packagesDirPath, std::string &outDirPath, std::string &packageName);
};
