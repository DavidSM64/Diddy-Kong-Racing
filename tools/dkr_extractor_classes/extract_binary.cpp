#include "extract_binary.h"

ExtractBinary::ExtractBinary(ConfigRange& range, ROM& rom, json::JSON& assetsJson, std::string outDirectory) : Extract(range, rom, assetsJson, outDirectory) {
    std::string name = range.get_property(1);
    std::string outFolder = range.get_property(2);
    std::string subfolder = range.get_subfolder();
    int startOffset = range.get_start();
    int endOffset = startOffset + range.get_size();
    std::vector<uint8_t> data = rom.get_bytes_from_range(startOffset, range.get_size());
    
    std::string outputDirectory = outDirectory + "/assets/" + subfolder + "/" + outFolder;
    if(!fs::is_directory(outputDirectory)) {
        fs::create_directories(outputDirectory);
    }
    
    std::stringstream filename;
    filename << name << "." << std::setfill('0') << std::setw(6) << std::hex << std::uppercase << startOffset << std::dec << ".bin";
    
    std::stringstream filepath;
    filepath << outputDirectory << "/" << filename.str();
    
    write_binary_file(data, filepath.str());
    
    print_extracted(startOffset, endOffset, outFolder, filename.str());
    
    std::string category = range.get_category();
    if(category != "none") {
        json::JSON obj = json::Object();
        obj["filename"] = outFolder + "/" + filename.str();
        obj["category"] = category;
        assetsJson["assets"].append(obj);
    }
}

ExtractBinary::~ExtractBinary(){
}
