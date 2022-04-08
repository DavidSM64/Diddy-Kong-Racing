#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread>

#include "../common/util.h"

class AssetAsmIncludes {
public:
    AssetAsmIncludes(std::string assetsDirectory, std::string buildDirectory, std::string dstPath);
    ~AssetAsmIncludes();
private:
    void write_comment(std::stringstream &out, std::string text);
    void write_header_comment(std::stringstream &out, std::string text);
    void write_word(std::stringstream &out, std::string value);
    void write_two_words(std::stringstream &out, std::string value, std::string value2);
    void write_word_with_comment(std::stringstream &out, std::string value, std::string comment);
    void write_binary_include(std::stringstream &out, std::string path);
    void write_global_label(std::stringstream &out, std::string label, bool align = false);
    void write_main_table(std::stringstream &out, std::vector<std::string> &sectionNames);
    void write_section(std::stringstream &out, std::string assetsDirectory, std::string buildDirectory, std::string sectionName);
    void write_ttghost_table_entry(std::stringstream &out, std::string entryWord, std::string ttGhostJsonPath);
};
