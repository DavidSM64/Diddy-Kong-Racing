#include "extract_compressed.h"

ExtractCompressed::ExtractCompressed(std::vector<uint8_t> data, ROM& rom, std::string outFilepath) 
: Extract(data, rom, outFilepath) {
    
    if(data.size() == 0) {
        std::cout << "Warning: \"" << outFilepath << "\" is empty." << std::endl;
        write_binary_file(data, outFilepath);
        print_extracted(outFilepath);
        return;
    }
    
    // Needed padding to prevent errors with decompressing.
    if(data[data.size() - 1] != 0) {
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);
    }
    
    DKRCompression compression;
    data = compression.decompressBuffer(data);
    
    write_binary_file(data, outFilepath);
    print_extracted(outFilepath);
}

ExtractCompressed::~ExtractCompressed(){
}
