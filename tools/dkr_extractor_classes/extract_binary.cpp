#include "extract_binary.h"

ExtractBinary::ExtractBinary(std::vector<uint8_t>& data, ROM& rom, std::string outFilepath) 
: Extract(data, rom, outFilepath) {
    write_binary_file(data, outFilepath);
    print_extracted(outFilepath);
}

ExtractBinary::~ExtractBinary(){
}
