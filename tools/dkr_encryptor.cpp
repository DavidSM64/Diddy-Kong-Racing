#include <iostream>
#include <fstream>
#include <vector>

void show_help() {
    std::cout << "Usage: ./dkr_encryptor <input_file> <output_file>" << std::endl;
}

void encrypt_data(std::vector<uint8_t>& data) {
    int numWords = data.size() / 4;
    int a, b, c, d, sp0, sp1, sp2, sp3;
    for(int i = 0; i < numWords; i++) {
        a = (data[(i * 4) + 3] & 0xC0) >> 6;
        b = (data[(i * 4) + 0] & 0xC0);
        c = (data[(i * 4) + 1] & 0xC0) >> 2;
        d = (data[(i * 4) + 2] & 0xC0) >> 4;
        sp0 = a | b | c | d;
        a = (data[(i * 4) + 3] & 0x30) >> 4;
        b = (data[(i * 4) + 0] & 0x30) << 2;
        c = (data[(i * 4) + 1] & 0x30);
        d = (data[(i * 4) + 2] & 0x30) >> 2;
        sp1 = a | b | c | d;
        a = (data[(i * 4) + 3] & 0x0C) >> 2;
        b = (data[(i * 4) + 0] & 0x0C) << 4;
        c = (data[(i * 4) + 1] & 0x0C) << 2;
        d = (data[(i * 4) + 2] & 0x0C);
        sp2 = a | b | c | d;
        a = (data[(i * 4) + 3] & 0x03);
        b = (data[(i * 4) + 0]       ) << 6;
        c = (data[(i * 4) + 1] & 0x03) << 4;
        d = (data[(i * 4) + 2] & 0x03) << 2;
        sp3 = a | b | c | d;
        a = (sp0 & 0xAA) >> 1;
        b = (sp0 & 0x55) << 1;
        data[(i * 4) + 0] = a | b;
        a = (sp1 & 0xAA) >> 1;
        b = (sp1 & 0x55) << 1;
        data[(i * 4) + 1] = a | b;
        a = (sp2 & 0xAA) >> 1;
        b = (sp2 & 0x55) << 1;
        data[(i * 4) + 2] = a | b;
        a = (sp3 & 0xAA) >> 1;
        b = (sp3 & 0x55) << 1;
        data[(i * 4) + 3] = a | b;
    }
}

void read_binary_file(std::vector<uint8_t>& data, std::string filename) {
    std::ifstream is;
    is.open(filename.c_str(), std::ios::binary);
    is.seekg(0, std::ios::end);
    size_t filesize = is.tellg();
    is.seekg(0, std::ios::beg);
    data.resize(filesize);
    is.read((char *)data.data(), filesize);
    is.close();
}

void write_binary_file(std::vector<uint8_t>& data, std::string& filename) {
    std::ofstream wf(filename.c_str(), std::ios::out | std::ios::binary);
    for(int i = 0; i < data.size(); i++)
        wf.write((char *)&data[i], 1);
    wf.close();
}

int main(int argc, char* argv[]) {
    
    if(argc != 3) {
        show_help();
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::vector<uint8_t> data;
    
    read_binary_file(data, inputFile);
    encrypt_data(data);
    write_binary_file(data, outputFile);
    
    return 0;
}


