#include "extract.h"

Extract::Extract(std::string key, std::vector<uint8_t> data, std::string outFilepath){    
    this->key = key;
    this->data = data;
    this->outFilepath = outFilepath;
    ensure_that_path_exists(outFilepath);
}

Extract::~Extract(){
}

void Extract::print_extracted() {
    std::stringstream out;
    out << "Extracted " << outFilepath << std::endl;
    std::cout << out.str();
}