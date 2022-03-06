#pragma once

#include "../common/util.h"
#include <iomanip>
#include <openssl/md5.h>

class ROM {
public:
    ROM(std::string filename);
    ~ROM();
    
    std::vector<uint8_t> get_bytes_from_range(int start, int numBytes);
    uint8_t get_byte(int romOffset);
    uint32_t get_uint(int romOffset);
    
    std::string get_md5();
    int get_size();
    
    bool is_valid();
    
private:
    void test_endianness();
    void calculate_md5();
    bool readROMFile(std::string filename);
    bool writeROMFile(std::string filename);
    
    std::vector<uint8_t> bytes;
    std::string md5;
    std::string romFilename;
    
    bool isValid = false;
};
