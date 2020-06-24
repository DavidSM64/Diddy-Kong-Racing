#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <openssl/md5.h>

// C++17
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;

class ROM {
public:
    ROM(std::string filename);
    ~ROM();
    
    std::vector<uint8_t> get_bytes_from_range(int start, int numBytes);
    uint8_t get_byte(int romOffset);
    
    std::string get_md5();
    int get_size();
    
private:
    void test_endianness();
    void calculate_md5();
    bool readROMFile(std::string filename);
    bool writeROMFile(std::string filename);
    
    std::vector<uint8_t> bytes;
    std::string md5;
    std::string romFilename;
};