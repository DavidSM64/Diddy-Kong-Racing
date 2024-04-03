#pragma once

#include <sstream>

#include "helpers/fileHelper.h"

// Write-Only C Header generator class
class WritableAsmInclude {
public:
    WritableAsmInclude();
    ~WritableAsmInclude();
    
    void write_comment(const char *comment);
    void write_header_comment(const char *comment);
    
    void write_newline();
    
    void write_word(const std::string &value);
    void write_two_words(const std::string &value, const std::string &value2);
    void write_word_with_comment(const std::string &value, const char *comment);

    void write_include(std::string filepath);
    void write_binary_include(std::string filepath);
    
    void write_global_label(const std::string &label, bool align=false);
    
    void save(fs::path filepath);
    
private:
    std::stringstream _out;
};
