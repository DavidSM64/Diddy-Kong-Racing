#pragma once

#include "../common/util.h"
#include <iomanip>

class ROM {
public:
    ROM(std::string filename);
    ~ROM();
    
    std::vector<uint8_t> get_bytes_from_range(int start, int numBytes);
    uint8_t get_byte(int romOffset);
    uint32_t get_uint(int romOffset);
    
    int get_size();


    std::string get_md5();
    
    bool is_valid();
    
private:
    void test_endianness();
    bool readROMFile(std::string filename);
    bool writeROMFile(std::string filename);
    
    std::vector<uint8_t> bytes;
    std::string md5;
    std::string romFilename;
    
    bool isValid = false;
};
