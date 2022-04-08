#include "extract_binary.h"

ExtractBinary::ExtractBinary(std::string key, std::vector<uint8_t> data, std::string outFilepath) 
: Extract(key, data, outFilepath) {
    write_binary_file(data, outFilepath);
    print_extracted();
}

ExtractBinary::~ExtractBinary(){
}
