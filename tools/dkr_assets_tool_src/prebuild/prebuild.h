#pragma once

#include <mutex>
#include <map>
#include <vector>

#include "misc/settings.hpp"
#include "prebuild/linker/ld.h"

#include "helpers/fileHelper.h"
#include "helpers/asmHeader.h"

struct LDCodeFile {
    std::string path;
    std::string condition;
};

class PreBuild {
public:
    PreBuild(DkrAssetsSettings &settings);
    ~PreBuild();
private:
    DkrAssetsSettings &_settings;
    
    std::vector<fs::path> _lateDataFiles;
    std::vector<fs::path> _bssLibOrderFiles;
    std::map<uint32_t, LDCodeFile> _codeFiles; // Sorted by ram address
    std::mutex _codeFilesMutex;
    
    fs::path _buildFolder, _buildAsm, _buildSrc, _buildLibAsm, _buildLibSrc;
    
    void _write_files_to_section(WritableLD &ld, const std::string &sectionName);
    
    void _write_ld_boot_section(WritableLD &ld);
    void _write_main_section(WritableLD &ld);
    void _write_ucode_text_section(WritableLD &ld);
    void _write_data_section(WritableLD &ld);
    void _write_rodata_section(WritableLD &ld);
    void _write_ucode_data_section(WritableLD &ld);
    void _write_bss_section(WritableLD &ld);
    void _write_assets_section(WritableLD &ld);
    void _write_discard_section(WritableLD &ld);
    
    void _append_files(const std::string inPath, const std::string extension, const std::string outPath);
    void _check_file_for_ram_pos(fs::path &filepath);
    void _get_code_files();
    void _populate_filepaths();
    
    void _generate_ld();
    void _write_ucode_file_glabel(WritableAsmInclude &asmInc, std::string label, std::string path);
    void _generate_ucode_text_file();
    void _generate_ucode_data_file();
    void _generate_ucode_files();
};
