#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

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

std::string read_text_file(std::string& filename) {
    std::ifstream t(filename);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 
    return buffer;
}

void write_binary_file(std::vector<uint8_t>& data, std::string& filename) {
    std::ofstream wf(filename.c_str(), std::ios::out | std::ios::binary);
    for(int i = 0; i < data.size(); i++)
        wf.write((char *)&data[i], 1);
    wf.close();
}

std::string trim(std::string input) {
   size_t b = input.find_first_not_of(' ');
   if (b == std::string::npos) b = 0;
   return input.substr(b, input.find_last_not_of(' ') + 1 - b);
}

std::vector<std::string> split_string(std::string s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        if(item.length() > 0) {
            elems.push_back(trim(item));
        }
    }
    return elems;
}

#define push_back_u16(data, offset, value) \
    data.push_back((value >> 8) & 0xFF); \
    data.push_back(value & 0xFF)

int main(int argc, char* argv[]) {
    
    if(argc != 3) {
        show_help();
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    
    std::vector<std::string> lines = split_string(read_text_file(inputFile), '\n');
    
    int numCheats = lines.size();
    
    std::vector<uint8_t> data;
    
    push_back_u16(data, 0, numCheats);
    
    std::regex regex_cheat("^[\"]([^\"]+)[\"]\\s*[,]\\s*[\"]([^\"]+)[\"]$");
    std::smatch match;
    
    // Create look-up table
    uint16_t offset = 2 + (numCheats * 4);
    for(auto& line : lines) {
        if (std::regex_search(line, match, regex_cheat)) {
            push_back_u16(data, 0, offset);
            offset += match[1].length() + 1; // +1 for the null terminator
            push_back_u16(data, 0, offset);
            offset += match[2].length() + 1;
        } else {
            std::cout << "Invalid line: " << line << std::endl;
            throw 1;
        }
    }
    
    // Now insert the strings
    for(auto& line : lines) {
        if (std::regex_search(line, match, regex_cheat)) {
            std::string codeWord = match[1];
            std::string codeDescription = match[2];
            for(int ch = 0; ch < codeWord.length(); ch++) {
                data.push_back(codeWord[ch]);
            }
            data.push_back(0);
            for(int ch = 0; ch < codeDescription.length(); ch++) {
                data.push_back(codeDescription[ch]);
            }
            data.push_back(0);
        } else {
            std::cout << "Invalid line: " << line << std::endl;
            throw 1;
        }
    }
    
    // Make sure the data is 16-byte aligned.
    while(data.size() % 16 != 0) {
        data.push_back(0);
    }
    
    encrypt_data(data);
    write_binary_file(data, outputFile);
    
    return 0;
}


