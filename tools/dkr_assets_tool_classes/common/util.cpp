#include "util.h"

uint32_t get_big_endian_word(std::vector<uint8_t> &data, int offset) {
    return (data[offset] << 24) | (data[offset + 1] << 16) | (data[offset + 2] << 8) | data[offset + 3];
}

void write_big_endian_word(std::vector<uint8_t> &data, int offset, uint32_t value) {
    data[offset] = (value >> 24) & 0xFF;
    data[offset + 1] = (value >> 16) & 0xFF;
    data[offset + 2] = (value >> 8) & 0xFF;
    data[offset + 3] = value & 0xFF;
}

uint16_t get_big_endian_halfword(std::vector<uint8_t> &data, int offset) {
    return (data[offset] << 8) | data[offset + 1];
}

void write_big_endian_halfword(std::vector<uint8_t> &data, int offset, uint16_t value) {
    data[offset] = (value >> 8) & 0xFF;
    data[offset + 1] = value & 0xFF;
}

float get_big_endian_float(std::vector<uint8_t> &data, int offset) {
    uint32_t word = get_big_endian_word(data, offset);
    return *((float*)&word);
}

void write_big_endian_float(std::vector<uint8_t> &data, int offset, float value){
    write_big_endian_word(data, offset, *((uint32_t*)&value));
}

std::string get_ascii(std::vector<uint8_t> &data, int offset) {
    std::stringstream ss;
    
    while(data[offset] != '\0'){
        ss << (char)data[offset++];
    }
    
    return ss.str();
}

void write_ascii(std::vector<uint8_t> &data, std::string value) {
    for(size_t i = 0; i < value.length(); i++) {
        if(value[i] == '\\') {
            char nextChar = value[i+1];
            if(nextChar == 't') {
                data.push_back((uint8_t)'\t');
            } else if(nextChar == 'n') {
                data.push_back((uint8_t)'\n');
            } else if(nextChar == 'r') {
                data.push_back((uint8_t)'\r');
            } else if(nextChar == 'v') {
                data.push_back((uint8_t)'\v');
            } else if(nextChar == '0') {
                data.push_back((uint8_t)'\0');
            }
            i++;
        } else {
            data.push_back(value[i]);
        }
    }
    data.push_back('\0'); // Write null terminator.
}

int insert_ascii(std::vector<uint8_t> &data, int offset, std::string value) {
    for(size_t i = 0; i < value.length(); i++) {
        if(value[i] == '\\') {
            char nextChar = value[i+1];
            if(nextChar == 't') {
                data[offset++] = (uint8_t)'\t';
            } else if(nextChar == 'n') {
                data[offset++] = (uint8_t)'\n';
            } else if(nextChar == 'r') {
                data[offset++] = (uint8_t)'\r';
            } else if(nextChar == 'v') {
                data[offset++] = (uint8_t)'\v';
            } else if(nextChar == '0') {
                data[offset++] = (uint8_t)'\0';
            }
            i++;
        } else {
            data[offset++] = value[i];
        }
    }
    data[offset++] = '\0'; // Write null terminator.
    return offset;
}

std::vector<std::string> get_multiple_ascii(std::vector<uint8_t> &data, int offset, int count) {
    std::vector<std::string> out(count);
    for(int i = 0; i < count; i++) {
        std::stringstream ss;
        while(data[offset] != '\0') {
            ss << (char)data[offset++];
        }
        out[i] = ss.str();
        offset++; // Move past the null terminator
    }
    return out;
}

std::vector<uint8_t> decompress_dkr_gzip(std::vector<uint8_t> &compressedData) {
    // Needed padding to prevent errors with decompressing.
    if(compressedData[compressedData.size() - 1] != 0) {
        compressedData.push_back(0);
        compressedData.push_back(0);
        compressedData.push_back(0);
        compressedData.push_back(0);
    }
    DKRCompression compression;
    return compression.decompressBuffer(compressedData);
}

std::vector<uint8_t> compress_dkr_gzip(std::vector<uint8_t> &uncompressedData) {
    DKRCompression compression;
    return compression.compressBuffer(uncompressedData);
}

int align16(int val) {
    return (val + 15) & 0xFFFFFFF0;
}

std::string to_hex(uint32_t value) {
    std::stringstream sstream;
    sstream << std::hex << value;
    std::string out = sstream.str();
    make_uppercase(out);
    return "0x" + out;
}

// Converts `FOO_BAR` to `FooBar`.
std::string upper_snake_case_to_pascal_case(std::string input) {
    std::stringstream out;
    bool isFirst = true;
    for(int i = 0; i < input.length(); i++) {
        if(input[i] == '_') {
            isFirst = true;
        } else {
            if(isFirst) {
                out << input[i];
                isFirst = false;
            } else {
                out << (char)tolower(input[i]);
            }
        }
    }
    
    return out.str();
}

void print_data(std::vector<uint8_t> &data, int offset, int length) {
    int start = offset;
    int end = start + length;
    
    std::cout << std::hex;
    for(int i = start; i < end; i++) {
        std::cout << (int)data[i] << ' ';
    }
    std::cout << std::dec << std::endl;
}


