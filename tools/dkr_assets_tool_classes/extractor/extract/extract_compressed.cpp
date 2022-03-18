#include "extract_compressed.h"

ExtractCompressed::ExtractCompressed(std::string key, std::vector<uint8_t> data, std::string outFilepath) 
: Extract(key, data, outFilepath) {
    
    if(data.size() == 0) {
        std::cout << "Warning: \"" << outFilepath << "\" is empty." << std::endl;
        write_binary_file(data, outFilepath);
        print_extracted();
        return;
    }
    
    data = decompress_dkr_gzip(data);
    write_binary_file(data, outFilepath);
    print_extracted();
}

ExtractCompressed::~ExtractCompressed(){
}
