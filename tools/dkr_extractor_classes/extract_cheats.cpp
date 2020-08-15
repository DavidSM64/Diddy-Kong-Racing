#include "extract_cheats.h"

#define get_u16(data, offset) (uint16_t)((data[offset] << 8) | data[offset + 1])

ExtractCheats::ExtractCheats(ConfigRange& range, ROM& rom, json::JSON& assetsJson, std::string outDirectory) : Extract(range, rom, assetsJson, outDirectory) {
    std::string name = range.get_property(1);
    std::string outFolder = range.get_property(2);
    std::string subfolder = range.get_subfolder();
    int startOffset = range.get_start();
    int endOffset = startOffset + range.get_size();
    
    std::string outputDirectory = outDirectory + "/assets/" + subfolder + "/" + outFolder;
    if(!fs::is_directory(outputDirectory)) {
        fs::create_directories(outputDirectory);
    }
    
    std::stringstream filename;
    filename << name << "." << std::setfill('0') << std::setw(6) << std::hex << std::uppercase << startOffset << std::dec << ".cheats";
    std::stringstream filepath;
    filepath << outputDirectory << "/" << filename.str();
    
    std::vector<uint8_t> data = rom.get_bytes_from_range(startOffset, range.get_size());
    
    decrypt_data(data);
    
    std::stringstream outFile;
    
    uint16_t numOfCheats = get_u16(data, 0);
    
    for(int i = 0; i < numOfCheats; i++) {
        uint16_t codeWordOffset = get_u16(data, 2 + (i * 4));
        uint16_t codeDescriptionOffset = get_u16(data, 2 + (i * 4) + 2);
        char* codeWord = (char*)&data[codeWordOffset];
        char* codeDescription = (char*)&data[codeDescriptionOffset];
        outFile << "\"" << codeWord << "\", \"" << codeDescription << "\"" << std::endl;
    }
    
    write_text_file(outFile.str(), filepath.str());
    
    print_extracted(startOffset, endOffset, outFolder, filename.str());
    
    std::string category = range.get_category();
    if(category != "none") {
        json::JSON obj = json::Object();
        obj["filename"] = outFolder + "/" + filename.str();
        obj["category"] = category;
        assetsJson["assets"].append(obj);
    }
}

ExtractCheats::~ExtractCheats(){
}

// Only used for the magic codes.
void ExtractCheats::decrypt_data(std::vector<uint8_t>& data) {
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
