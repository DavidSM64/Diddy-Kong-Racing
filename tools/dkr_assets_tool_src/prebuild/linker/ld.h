#pragma once

#include <string>
#include <sstream>

#include "misc/settings.hpp"

enum LD_SUBALIGN {
    NONE = 0,
    ALIGN4 = 4,
    ALIGN8 = 8,
    ALIGN16 = 16
};

// Creates a read-only linker
class WritableLD {
public:
    WritableLD(DkrAssetsSettings &settings);
    ~WritableLD();
    
    void write_comment(const char *text);
    void write_include(const char *text);
    void write_arch(const char *archName);
    void write_raw(const char *text);
    void write_raw_line(const char *text);
    void write_raw_line(const std::string text);
    
    void write_assignment(const char *var, const char *value);
    
    void write_rom_pos_at(const char *value);
    void write_add_to_rom_pos(const char *value);
    
    void write_section_header(const char *name, const char *ramPos, const char *romPos, const LD_SUBALIGN subalign);
    
    void write_open_brace();
    void write_close_brace();
    void write_newline();
    
    
    void save(const std::string &filepath);
private:
    DkrAssetsSettings &_settings;
    
    std::string _indent;
    std::stringstream _out;
};