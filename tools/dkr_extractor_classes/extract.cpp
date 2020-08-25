#include "extract.h"

Extract::Extract(std::vector<uint8_t> data, ROM& rom, std::string outFilepath){
}

Extract::~Extract(){
}
    
void Extract::write_binary_file(std::vector<uint8_t> data, std::string filepath){
    std::ofstream wf(filepath.c_str(), std::ios::out | std::ios::binary);
    for(int i = 0; i < data.size(); i++)
        wf.write((char *)&data[i], 1);
    wf.close();
}

void Extract::write_text_file(std::string text, std::string filepath){
    std::ofstream myfile;
    myfile.open(filepath);
    myfile << text;
    myfile.close();
}

void Extract::print_extracted(std::string outFilepath) {
    std::stringstream out;
    out << "Extracted " << outFilepath << std::endl;
    std::cout << out.str();
}

void Extract::to_lowercase(std::string& input) {
    for(char& character : input) {
        character = std::tolower(character);
    }
}
