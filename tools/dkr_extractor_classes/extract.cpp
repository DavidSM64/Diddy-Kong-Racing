#include "extract.h"

Extract::Extract(ConfigRange& range, ROM& rom, json::JSON& assetsJson, std::string outDirectory) : 
    range(range), rom(rom), assetsJson(assetsJson), outDirectory(outDirectory) {
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

void Extract::print_extracted(int start, int end, std::string subfolder, std::string filename) {
    std::cout << "Extracted " << std::setfill('0') << std::setw(6) << std::hex << std::uppercase 
        << start << "-" << std::setfill('0') << std::setw(6) << std::hex << std::uppercase << end 
        << " as /" << subfolder << "/" << filename << std::endl;
}

void Extract::to_lowercase(std::string& input) {
    for(char& character : input) {
        character = std::tolower(character);
    }
}
