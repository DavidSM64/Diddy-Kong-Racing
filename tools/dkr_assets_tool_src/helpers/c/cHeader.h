#pragma once

#include <sstream>

#include "helpers/fileHelper.h"
#include "helpers/c/cEnumsHelper.h"

// Write-Only C Header generator class
namespace DkrAssetsTool {

class WritableCHeader {
public:
    WritableCHeader();
    ~WritableCHeader();
    
    void write_comment(const char *comment);
    void write_header_comment(const char *comment);
    void write_newline();
    
    void write_raw_text(std::string text);
    void write_raw_text_line(std::string text);
    
    void write_enum(const WriteableCEnum &enumValue);
    // TODO: write_struct ?
    
    void save(fs::path filepath);
    
private:
    std::stringstream _out;
};

}
