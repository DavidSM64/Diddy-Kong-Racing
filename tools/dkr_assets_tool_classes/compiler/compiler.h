#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../common/util.h"
#include "../common/types.h"
#include "../common/revision_number.h"

class AssetCompiler {
public:
    AssetCompiler();
    ~AssetCompiler();
private:
    void apply_package(std::string &packagesDirPath, std::string &packageName, std::string &tempDirPath, std::string &outDirPath);
    void check_meta_json(std::string &packageName, std::string metaJsonFilepath);
    void merge_output(std::string &tempDir, std::string &outDir);
};
