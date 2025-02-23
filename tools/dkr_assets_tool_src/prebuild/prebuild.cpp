#include "prebuild.h"

#include "libs/ThreadPool.h"

#include "helpers/debugHelper.h"
#include "helpers/regexHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/stringHelper.h"

#include "prebuild/makeIncludes/assetsAsm.h"
#include "prebuild/makeIncludes/assetEnums.h"
#include "prebuild/compileAssets/compile.h"

const std::string SECTION_TEXT = "text";
const std::string SECTION_DATA = "data";
const std::string SECTION_RODATA = "rodata";
const std::string SECTION_BSS = "bss";

PreBuild::PreBuild(DkrAssetsSettings &settings) : _settings(settings) {
    _buildFolder = _settings.pathToBuild / _settings.dkrVersion;
    
    // Gets rid of the starting "./" from the path.
    _buildFolder = fs::relative(_buildFolder);
    
    _buildAsm = _buildFolder / "asm";
    _buildSrc = _buildFolder / "src";
    _buildLibAsm = _buildFolder / "lib/asm";
    _buildLibSrc = _buildFolder / "lib/src";
    
    CompileAssets compileAssets(_settings);
    
    _settings.pathToAssets /= _settings.dkrVersion;
    
    AssetsAsm assetsAsm(_settings);   // Generate asm/assets/assets.s
    AssetEnums assetEnums(_settings); // Generate include/asset_enums.h
    
    _generate_ld();
    _generate_ucode_files();
}

PreBuild::~PreBuild() {
}

void PreBuild::_append_files(const std::string inPath, const std::string extension, const std::string outPath) {
    std::vector<fs::path> files = FileHelper::get_files_from_directory_with_extension(fs::path(inPath), extension);
    for(auto &p : files) {
        DebugHelper::info(p);
    }
}

const std::string _RAM_POS_REGEX = R"([\/][*]+[ \t]*RAM_POS:[ \t]*((?:0x)[0-9a-fA-F]+|(?:[Aa][Uu][Tt][Oo]))[ \t]*(?:if[ \t]*([^*]*))?[*][\/])";

void PreBuild::_check_file_for_ram_pos(fs::path &filepath) {
    // Only load the first 256 bytes of the file for speed reasons.
    
    std::string file = FileHelper::read_text_file(filepath, 256);
    RegexMatch *match = RegexHelper::get_first_match(file, _RAM_POS_REGEX);
    if(match == nullptr) {
        return;
    }
    
    std::string ramPos = match->get_group(1).get_text();
    std::string condition = match->get_group(2).get_text();
    
    StringHelper::make_lowercase(ramPos);
    
    if(ramPos == "auto") {
        ramPos = "0x800FFFF0";
    }
    
    if(!StringHelper::starts_with(ramPos, "0x")) {
        ramPos.insert(0, "0x");
    }
    
    uint32_t address = static_cast<uint32_t>(std::stoul(ramPos, nullptr, 0));
    
    fs::path outFilepath = filepath.lexically_relative(_settings.pathToRepo);
    outFilepath.replace_extension(".o");
    
    outFilepath = _buildFolder / outFilepath;
    
    _codeFilesMutex.lock();
    while(_codeFiles.find(address) != _codeFiles.end()) {
        address++; // Make sure each address is unique.
    }
    _codeFiles[address] = {
        outFilepath,
        condition
    };
    _codeFilesMutex.unlock();
}

void PreBuild::_get_code_files() {
    std::vector<fs::path> allFiles;
    
    FileHelper::append_files_from_directory_with_extension(_settings.pathToAsm, ".s", allFiles);
    FileHelper::append_files_from_directory_with_extension(_settings.pathToSrc, ".c", allFiles);
    FileHelper::append_files_from_directory_with_extension(_settings.pathToLibAsm, ".s", allFiles);
    FileHelper::append_files_from_directory_with_extension(_settings.pathToLibSrc, ".c", allFiles);
    
    {
        ThreadPool pool(_settings.threadCount);
        for(fs::path &filepath : allFiles) {
            pool.enqueue([this, &filepath = filepath] {
                _check_file_for_ram_pos(filepath);
            });
        }
    }
}

void PreBuild::_populate_filepaths() {
    _lateDataFiles = {
    };
    _bssLibOrderFiles = {
    };
}

void PreBuild::_write_files_to_section(WritableLD &ld, const std::string &sectionName) {
    bool isDataSection = (sectionName == "data") || (sectionName == "rodata");
    bool isBssSection = (sectionName == "bss");
    
    for (auto &file : _codeFiles) {
        std::string &path = file.second.path;
        
        if(isDataSection && DataHelper::vector_has<fs::path>(_lateDataFiles, path)) {
            continue;
        } else if(isBssSection && DataHelper::vector_has<fs::path>(_bssLibOrderFiles, path)) {
            continue;
        }
        
        std::string &condition = file.second.condition;
        if(!condition.empty()) {
            ld.write_raw_line("#if " + condition);
        }
        ld.write_raw_line(path + "(." + sectionName + ");");
        if(!condition.empty()) {
            ld.write_raw_line("#endif");
        }
    }
    if(isDataSection) {
        for(fs::path &path : _lateDataFiles) {
            ld.write_raw_line(std::string(path) + "(." + sectionName + ");");
        }
    } else if(isBssSection) {
        for(fs::path &path : _bssLibOrderFiles) {
            ld.write_raw_line(std::string(path) + "(." + sectionName + ");");
        }
    }
}

void PreBuild::_write_ld_boot_section(WritableLD &ld) {
    ld.write_section_header("boot", "0", "romPos", LD_SUBALIGN::NONE);
    ld.write_open_brace(); // Open .boot
    
    // TODO: Refactor to remove hardcoding.
    ld.write_raw_line(_buildFolder / "asm/boot/rom_header.o(.text);");
    ld.write_raw_line(_buildFolder / "asm/boot/rom_boot.o(.text);");
    
    ld.write_close_brace(); // Close .boot
    ld.write_add_to_rom_pos("SIZEOF(.boot)");
    ld.write_newline();
}

void PreBuild::_write_main_section(WritableLD &ld) {
    ld.write_section_header("main", "__FUNC_RAM_START", "romPos", LD_SUBALIGN::ALIGN16);
    ld.write_open_brace(); // Open .main
    
    _write_files_to_section(ld, SECTION_TEXT);
    
    ld.write_close_brace(); // Close .main
    ld.write_add_to_rom_pos("SIZEOF(.main)");
    ld.write_newline();
}

void PreBuild::_write_ucode_text_section(WritableLD &ld) {
    ld.write_section_header("ucodeText", ".", "romPos", LD_SUBALIGN::NONE);
    ld.write_open_brace(); // Open .ucodeText
    
    // TODO: Refactor to remove hardcoding.
    ld.write_raw_line(_buildFolder / "asm/assets/ucode_text.o(.text);");
    
    ld.write_close_brace(); // Close .ucodeText
    ld.write_add_to_rom_pos("SIZEOF(.ucodeText)");
    ld.write_newline();
}

void PreBuild::_write_data_section(WritableLD &ld) {
    ld.write_section_header("data", ".", "romPos", LD_SUBALIGN::ALIGN16);
    ld.write_open_brace(); // Open .data
    
    _write_files_to_section(ld, SECTION_DATA);
    
    ld.write_close_brace(); // Close .data
    ld.write_add_to_rom_pos("SIZEOF(.data)");
    ld.write_newline();
}

void PreBuild::_write_rodata_section(WritableLD &ld) {
    ld.write_section_header("rodata", ".", "romPos", LD_SUBALIGN::ALIGN16);
    ld.write_open_brace(); // Open .rodata
    
    _write_files_to_section(ld, SECTION_RODATA);
    
    ld.write_close_brace(); // Close .rodata
    ld.write_add_to_rom_pos("SIZEOF(.rodata)");
    ld.write_newline();
}

void PreBuild::_write_ucode_data_section(WritableLD &ld) {
    ld.write_section_header("ucodeData", ".", "romPos", LD_SUBALIGN::NONE);
    ld.write_open_brace(); // Open .ucodeData
    
    // TODO: Refactor to remove hardcoding.
    ld.write_raw_line(_buildFolder / "asm/assets/ucode_data.o(.text);");
    
    ld.write_close_brace(); // Close .ucodeData
    ld.write_add_to_rom_pos("SIZEOF(.ucodeData)");
    ld.write_newline();
}

void PreBuild::_write_bss_section(WritableLD &ld) {
    // TODO: add this to ld file
    ld.write_raw_line(".bss.noload . (NOLOAD): SUBALIGN(4)");
    ld.write_open_brace(); // Open .bss
    
    _write_files_to_section(ld, SECTION_BSS);
    
    ld.write_close_brace(); // Close .bss
    ld.write_newline();
}

void PreBuild::_write_assets_section(WritableLD &ld) {
    ld.write_section_header("assets", "0", "romPos", LD_SUBALIGN::NONE);
    ld.write_open_brace(); // Open .assets
    
    // TODO: Refactor to remove hardcoding.
    ld.write_raw_line(_buildFolder / "asm/assets/assets.o(.text);");
    
    
    ld.write_close_brace(); // Close .assets
    ld.write_add_to_rom_pos("SIZEOF(.assets)");
    ld.write_newline();
}

void PreBuild::_write_discard_section(WritableLD &ld) {
    ld.write_comment("Discard everything not specifically mentioned above.");
    
    // TODO: add this to ld file
    ld.write_raw_line("/DISCARD/ :");
    ld.write_open_brace(); // Open discard
    ld.write_raw_line("*(*);");
    ld.write_close_brace(); // Close discard
    ld.write_newline();
}

void PreBuild::_generate_ld() {
    _get_code_files();
    _populate_filepaths();
    
    fs::path outputPath = _settings.pathToRepo / "dkr.ld";
    WritableLD ld(_settings);
    
    ld.write_comment("This file is automatically generated. Any changes you make to this file will get overwritten.");
    ld.write_newline();
    
    ld.write_include("config.h");
    ld.write_newline();
    
    ld.write_arch("mips");
    ld.write_newline();
    
    ld.write_raw_line("SECTIONS");
    ld.write_open_brace(); // Open SECTIONS
    
    ld.write_rom_pos_at("0");
    
    // .boot section
    _write_ld_boot_section(ld);
    
    ld.write_assignment("__FUNC_RAM_START", "0x80000400");
    ld.write_assignment("__FUNC_ROM_START", "0x00001000");
    ld.write_assignment("__RAM_TO_ROM", "__FUNC_RAM_START - __FUNC_ROM_START");
    ld.write_newline();
    
    // .main section
    _write_main_section(ld);
    
    // .ucodeText section
    _write_ucode_text_section(ld);
    
    // .data section
    _write_data_section(ld);
    
    // .rodata section
    _write_rodata_section(ld);
    
    // .ucodeData section
    _write_ucode_data_section(ld);
    
    ld.write_assignment("__BSS_SECTION_SIZE", "SIZEOF(.bss.noload) - 32");
    ld.write_newline();
    
    // .bss.noload section
    _write_bss_section(ld);
    
    ld.write_assignment("__ASSETS_LUT_START", "romPos");
    // TODO: Turn `0xD0` into sizeof main asset table.
    ld.write_assignment("__ASSETS_LUT_END", "__ASSETS_LUT_START + 0xD0"); 
    ld.write_newline();
    
    // .assets section
    _write_assets_section(ld);
    
    ld.write_assignment("__ROM_END", "romPos");
    ld.write_newline();
    
    _write_discard_section(ld);
    
    ld.write_close_brace(); // Close SECTIONS
    
    ld.save(outputPath);
}

void PreBuild::_write_ucode_file_glabel(WritableAsmInclude &asmInc, std::string label, std::string path) {
    asmInc.write_global_label(label);
    asmInc.write_binary_include(_buildFolder / path);
}

void PreBuild::_generate_ucode_text_file() {
    fs::path ucodeTextPath = _settings.pathToAsm / "assets/ucode_text.s";
    WritableAsmInclude text;
    
    text.write_comment("This file is automatically generated. Any changes you make to this file will get overwritten.");
    text.write_newline();
    
    text.write_include("macros.inc");
    text.write_newline();
    
    // TODO: Refactor this!
    _write_ucode_file_glabel(text, "aspMainTextStart", "ucode/ucode_audio.bin");
    _write_ucode_file_glabel(text, "rspF3DDKRBootStart", "ucode/ucode_boot.bin");
    _write_ucode_file_glabel(text, "rspF3DDKRDramStart", "ucode/ucode_f3ddkr_dram.bin");
    _write_ucode_file_glabel(text, "rspF3DDKRFifoStart", "ucode/ucode_f3ddkr_fifo.bin");
    _write_ucode_file_glabel(text, "rspF3DDKRXbusStart", "ucode/ucode_f3ddkr_xbus.bin");
    _write_ucode_file_glabel(text, "rspUnknown2Start", "ucode/ucode_unknown_2.bin");
    
    text.save(ucodeTextPath);
}

void PreBuild::_generate_ucode_data_file() {
    fs::path ucodeDataPath = _settings.pathToAsm / "assets/ucode_data.s";
    WritableAsmInclude data;
    
    data.write_comment("This file is automatically generated. Any changes you make to this file will get overwritten.");
    data.write_newline();
    
    data.write_include("macros.inc");
    data.write_newline();
    
    // TODO: Refactor this!
    _write_ucode_file_glabel(data, "aspMainDataStart", "ucode/data_audio.bin");
    _write_ucode_file_glabel(data, "rspF3DDKRDataDramStart", "ucode/data_f3ddkr_dram.bin");
    _write_ucode_file_glabel(data, "rspF3DDKRDataFifoStart", "ucode/data_f3ddkr_fifo.bin");
    _write_ucode_file_glabel(data, "rspF3DDKRDataXbusStart", "ucode/data_f3ddkr_xbus.bin");
    _write_ucode_file_glabel(data, "rspUnknown2DataStart", "ucode/data_unknown_2.bin");
    
    data.save(ucodeDataPath);
}

void PreBuild::_generate_ucode_files() {
    _generate_ucode_text_file();
    _generate_ucode_data_file();
}

