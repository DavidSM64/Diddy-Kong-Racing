#pragma once

#include <vector>

#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/imageHelper.h"

namespace DkrAssetsTool {

class DkrExtractROM {
public:

    DkrExtractROM(fs::path filepath);
    ~DkrExtractROM();
    
    std::string get_calculated_md5();
    bool is_valid();
    
    uint32_t get_u32(uint32_t offset);
    int32_t get_s32(uint32_t offset);
    uint16_t get_u16(uint32_t offset);
    int16_t get_s16(uint32_t offset);
    uint8_t get_u8(uint32_t offset);
    int8_t get_s8(uint32_t offset);
    float get_f32(uint32_t offset);
    std::string get_ascii(uint32_t offset, int length=-1);
    void get_multiple_ascii(uint32_t offset, std::vector<std::string> &out, int count);
    void get_data(uint32_t offset, size_t numBytes, std::vector<uint8_t> &out);
    
    void write_rom_section_to_binary_file(fs::path finalFilepath, uint32_t offset, int32_t length);
    
private:
    void _detect_and_fix_rom_endianness();
    void _calculate_md5_checksum();

    fs::path _filepath;
    bool _isValid = false;
    std::vector<uint8_t> _bytes;
    uint32_t _romSize;
    std::string _md5;
    void _get_fixed_table(uint32_t offset, std::vector<int32_t> &outTable);
    void _get_variable_table(uint32_t offset, std::vector<int32_t> &outTable);
};
}
