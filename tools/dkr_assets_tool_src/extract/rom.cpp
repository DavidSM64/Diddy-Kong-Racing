#include <iostream>
#include <vector>
#include "libs/md5.hpp"
#include "rom.h"

DkrExtractROM::DkrExtractROM(fs::path filepath) {
    _filepath = filepath;
    _bytes = FileHelper::read_binary_file(filepath);
    _romSize = _bytes.size(); // ROM shouldn't change size.
    if(_bytes.size() < 4) {
        return;
    }
    _detect_and_fix_rom_endianness();
    if(!_isValid) {
        return;
    }
    _calculate_md5_checksum();
}

DkrExtractROM::~DkrExtractROM() {
    
}

std::string DkrExtractROM::get_calculated_md5() {
    return _md5;
}

bool DkrExtractROM::is_valid() {
    return _isValid;
}

void DkrExtractROM::_detect_and_fix_rom_endianness() {
    bool convertedToBigEndian = false;
    
    if(_bytes[0] == 0x80 && _bytes[1] == 0x37) { // Detect big endian
        // Do nothing
    } else if(_bytes[0] == 0x37 && _bytes[1] == 0x80) { // Detect mixed endian (byteswapped)
        FileHelper::byteswap(_bytes); // Convert to big endian
        convertedToBigEndian = true;
    } else if(_bytes[0] == 0x40 && _bytes[1] == 0x12) { // Detect little endian
        FileHelper::endianswap(_bytes); // Convert to big endian
        convertedToBigEndian = true;
    } else {
        _isValid = false; // Not a valid N64 ROM
        return;
    }
    
    _isValid = true;
    
    if(convertedToBigEndian) {
        // First overwrite baserom bytes, so that it stays big-endian.
        FileHelper::write_binary_file(_bytes, _filepath);
        
        // Then rename the ROM to .z64 to indicate that it is big-endian.
        fs::path filename = FileHelper::get_filename_from_path(_filepath, true);
        filename.replace_extension(".z64");
        
        fs::path dir = FileHelper::get_directory(_filepath).string();
        fs::path newPath = dir / filename;
        FileHelper::rename(_filepath, newPath);
    }
    
    return;
}

void DkrExtractROM::_calculate_md5_checksum() {
    md5::Digest digest = md5::compute(_bytes);
    std::stringstream ss;

    // set up stringstream format
    ss << std::hex << std::setfill('0');

    for(uint8_t uc: digest) {
        ss << std::setw(2) << (int)uc;
    }

    _md5 = ss.str();
}

uint32_t DkrExtractROM::get_u32(uint32_t offset) {
    DebugHelper::assert((offset + 3) < _romSize, "(DkrExtractROM::get_u32) Data access out of bounds; offset was ", DebugHelper::to_hex(offset), " when ROM size is ", DebugHelper::to_hex(_romSize));
    return (_bytes[offset] << 24) | (_bytes[offset + 1] << 16) | (_bytes[offset + 2] << 8) | _bytes[offset + 3];
}

int32_t DkrExtractROM::get_s32(uint32_t offset) {
    DebugHelper::assert((offset + 3) < _romSize, "(DkrExtractROM::get_s32) Data access out of bounds; offset was ", DebugHelper::to_hex(offset), " when ROM size is ", DebugHelper::to_hex(_romSize));
    return (_bytes[offset] << 24) | (_bytes[offset + 1] << 16) | (_bytes[offset + 2] << 8) | _bytes[offset + 3];
}

uint16_t DkrExtractROM::get_u16(uint32_t offset) {
    DebugHelper::assert((offset + 1) < _romSize, "(DkrExtractROM::get_u16) Data access out of bounds; offset was ", DebugHelper::to_hex(offset), " when ROM size is ", DebugHelper::to_hex(_romSize));
    return (_bytes[offset] << 8) | _bytes[offset + 1];
}

int16_t DkrExtractROM::get_s16(uint32_t offset) {
    DebugHelper::assert((offset + 1) < _romSize, "(DkrExtractROM::get_s16) Data access out of bounds; offset was ", DebugHelper::to_hex(offset), " when ROM size is ", DebugHelper::to_hex(_romSize));
    return (_bytes[offset] << 8) | _bytes[offset + 1];
}

uint8_t DkrExtractROM::get_u8(uint32_t offset) {
    DebugHelper::assert(offset < _romSize, "(DkrExtractROM::get_u8) Data access out of bounds; offset was ", DebugHelper::to_hex(offset), " when ROM size is ", DebugHelper::to_hex(_romSize));
    return _bytes[offset];
}

int8_t DkrExtractROM::get_s8(uint32_t offset) {
    DebugHelper::assert(offset < _romSize, "(DkrExtractROM::get_s8) Data access out of bounds; offset was ", DebugHelper::to_hex(offset), " when ROM size is ", DebugHelper::to_hex(_romSize));
    return _bytes[offset];
}

union _FloatIntUnion {
    uint32_t word;
    float wordAsFloat;
};

float DkrExtractROM::get_f32(uint32_t offset) {
    DebugHelper::assert((offset + 3) < _romSize, "(DkrExtractROM::get_f32) Data access out of bounds; offset was ", DebugHelper::to_hex(offset), " when ROM size is ", DebugHelper::to_hex(_romSize));
    _FloatIntUnion fi; // Doing this to avoid the type-punning warning.
    fi.word = (_bytes[offset] << 24) | (_bytes[offset + 1] << 16) | (_bytes[offset + 2] << 8) | _bytes[offset + 3];
    return fi.wordAsFloat;
}

std::string DkrExtractROM::get_ascii(uint32_t offset, int length) {
    bool asciiWithinBounds = (offset < _romSize) || !((length > 0) && ((offset + length) >= _romSize));
    DebugHelper::assert(asciiWithinBounds, "(DkrExtractROM::get_ascii) Data access out of bounds; offset was ", DebugHelper::to_hex(offset), " when ROM size is ", DebugHelper::to_hex(_romSize));
    
    char *stringData = reinterpret_cast<char*>(_bytes[offset]);
    
    if(length < 0) {
        // string has a null-terminator at the end.
        return std::string(stringData);
    }
    
    return std::string(stringData, length);
}

void DkrExtractROM::get_multiple_ascii(uint32_t offset, std::vector<std::string> &out, int count) {
    // Clear the output vector
    out.clear();
     
    while(count > 0) {
        DebugHelper::assert(offset < _romSize, "(DkrExtractROM::get_multiple_ascii) Data access out of bounds; offset was ", DebugHelper::to_hex(offset), " when ROM size is ", DebugHelper::to_hex(_romSize));
        std::string entry = std::string(reinterpret_cast<char*>(_bytes[offset]));
        offset += entry.length() + 1;
        out.push_back(entry);
        count--;
    }
}

void DkrExtractROM::get_data(uint32_t offset, size_t numBytes, std::vector<uint8_t> &out) {
    // Check if the requested range is within the ROM's size
    DebugHelper::assert(offset + numBytes <= _romSize, "(DkrExtractROM::get_data) Requested range is out of bounds. ROM offset = ", DebugHelper::to_hex(offset), ", numBytes = ", DebugHelper::to_hex(numBytes));

    // Clear the output vector
    out.clear();

    // Get the subsection of the ROM
    out.insert(out.end(), _bytes.begin() + offset, _bytes.begin() + offset + numBytes);
}

void DkrExtractROM::write_rom_section_to_binary_file(fs::path finalFilepath, uint32_t offset, int32_t length) {
    DebugHelper::assert(length > 0, "(DkrExtractROM::write_rom_section_to_binary_file) Invalid length of ", length);
    FileHelper::write_binary_file((char*)&_bytes[offset], length, finalFilepath, true);
}
