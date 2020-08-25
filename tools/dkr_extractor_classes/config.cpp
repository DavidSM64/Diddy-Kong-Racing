#include "config.h"

ExtractConfig::ExtractConfig(std::string configsDirectory, std::string filename, std::string outDirectory){
    std::cout << "Reading config \"" << filename << "\"" << std::endl;
    configJSON = json::JSON::Load(read_file(configsDirectory + '/' + filename));
    
    this->outDirectory = outDirectory + "/assets/" + configJSON["subfolder"].ToString();
    
    this->name = configJSON["config-name"].ToString();
    this->subfolder = configJSON["subfolder"].ToString();
    this->md5 = configJSON["checksum-md5"].ToString();
    this->notSupported = configJSON["not-supported"].ToString() == "true";
}

ExtractConfig::~ExtractConfig(){
}

bool is_binary_type(std::string type) {
    return type == "Binary" || type == "GameText" || type == "MenuText" || type == "Sprites" || type == "Miscellaneous"
        || type == "LevelHeaders" || type == "LevelNames" || type == "ObjectHeaders" 
        || type == "Audio" || type == "Particles" || type == "ParticleBehaviors" || type == "TTGhosts";
}

bool is_compressed_type(std::string type) {
    return type == "Compressed" || type == "LevelObjectMap" || type == "LevelModels" 
        || type == "ObjectModels" || type == "ObjectAnimations";
}

std::string get_extension_from_type(std::string type) {
    if(is_compressed_type(type)) {
        return ".cbin";
    } else if(type == "Textures") {
        return ".png";
    } else {
        return ".bin";
    }
}

void ExtractConfig::extract_file(ROM& rom, std::string type, std::string folder, std::string filename, std::vector<uint8_t> data) {
    if(!fs::is_directory(folder)) {
        fs::create_directories(folder);
    }
    
    std::string outFilepath = folder + "/" + filename;
    
    if(is_binary_type(type)) {
        ExtractBinary(data, rom, outFilepath + ".bin");
    } else if(is_compressed_type(type)) {
        ExtractCompressed(data, rom, outFilepath + ".cbin");
    } else if(type == "Textures") {
        ExtractTextures(data, rom, outFilepath + ".png");
    } else if(type == "Empty") {
    } else if(type != "NoExtract") {
        std::cout << "Unknown extraction type: " << type << std::endl;
        throw 1;
    }
}

uint32_t get_uint_from_table(std::vector<uint8_t>& table, int index) {
    return (table[index * 4] << 24) | (table[index * 4 + 1] << 16) | (table[index * 4 + 2] << 8) | table[index * 4 + 3];
}

std::vector<std::vector<uint8_t>> get_section_files(std::vector<uint8_t>& section, std::vector<uint8_t>& table, std::string tableType, json::JSON& outputAsset) {
    std::vector<std::vector<uint8_t>> out;
    
    int currentTableIndex = 0;
    int scale = 1; // Each table entry is 4-bytes long.
    int offset = 0;
    
    if(tableType == "MenuText") {
        outputAsset["text-entry-count"] = get_uint_from_table(table, currentTableIndex);
        currentTableIndex = 1; // The first entry is the number of text entries for each language.
    } else if(tableType == "TTGhosts") {
        scale = 2; // Each table entry is 8-bytes long.
        offset = 1; // offset by 4 bytes.
        outputAsset["meta"] = json::Array();
    } else if (tableType == "GameText") {
        outputAsset["textTypes"] = json::Array();
    }
    
    uint32_t currentTableValue = get_uint_from_table(table, currentTableIndex * scale + offset);
    uint32_t nextTableValue = get_uint_from_table(table, (currentTableIndex + 1) * scale + offset);
    
    if (tableType == "Audio") {
        // The audio table doesn't start at offset 0, so this check will extract
        // the first actual part of the audio section.
        std::vector<uint8_t> file(section.begin(), section.begin() + currentTableValue);
        out.push_back(file);
    }
    
    while(nextTableValue != 0xFFFFFFFF) {
        
        if(tableType == "GameText") {
            bool isDialog = (currentTableValue & 0x80000000) == 0x80000000;
            outputAsset["textTypes"].append(isDialog ? 1 : 0);
            currentTableValue &= 0x7FFFFFFF;
            nextTableValue &= 0x7FFFFFFF;
        } else if(tableType == "Miscellaneous") {
            currentTableValue *= 4;
            nextTableValue *= 4;
        } else if (tableType == "TTGhosts") {
            json::JSON metaObj = json::Object();
            metaObj["levelID"] = table[currentTableIndex * 8 + 0];
            metaObj["vehicleID"] = table[currentTableIndex * 8 + 1];
            outputAsset["meta"].append(metaObj);
        }
        
        int length = nextTableValue - currentTableValue;
        if(length < 0) {
            std::cout << "Error: Invalid table length: " << length << std::endl;
            std::cout << std::hex << "currentTableValue: " << currentTableValue << std::dec << std::endl;
            std::cout << std::hex << "nextTableValue: " << nextTableValue << std::dec << std::endl;
            throw 1;
        }
        
        std::vector<uint8_t> file(section.begin() + currentTableValue, section.begin() + nextTableValue);
        out.push_back(file);
        
        currentTableIndex++;
        currentTableValue = get_uint_from_table(table, currentTableIndex * scale + offset);
        nextTableValue = get_uint_from_table(table, (currentTableIndex + 1) * scale + offset);
    }
    
    return out;
}

void ExtractConfig::extract(ROM& rom, json::JSON& assetsJson) {
    currentROMOffset = 0;
    
    /* Extract the code sections */
    json::JSON codeSections = configJSON["code"]["sections"];
    int numCodeSections = codeSections.length();
    for(int i = 0; i < numCodeSections; i++) {
        json::JSON section = codeSections[i];
        json::JSON files = section["files"];
        std::string folder = this->outDirectory + "/" + section["folder"].ToString();
        std::string type = section["type"].ToString();
        
        int numFiles = files.length();
        for(int j = 0; j < numFiles; j++) {
            json::JSON file = files[j];
            int length = std::stoul(file["length"].ToString(), nullptr, 16);
            extract_file(rom, type, folder, file["filename"].ToString(), 
                rom.get_bytes_from_range(currentROMOffset, length));
            currentROMOffset += length;
        }
    }
    
    /* Make sure the assets section has the correct number of entries. */
    json::JSON assetSections = configJSON["assets"]["sections"];
    int numAssetSections = assetSections.length();
    int numAssetSectionsFromTable = rom.get_uint(currentROMOffset);
    
    if(numAssetSections != numAssetSectionsFromTable) {
        std::cout << "Error: Number of asset sections in config does not match ROM." << std::endl;
        std::cout << "Number of asset sections in Config: " << numAssetSections << std::endl;
        std::cout << "Number of asset sections in ROM:    " << numAssetSectionsFromTable << std::endl;
        throw 1;
    }
    
    currentROMOffset += 4;
    int tableOffset = currentROMOffset;
    currentROMOffset += (numAssetSections + 1) * 4;
    int assetsStart = currentROMOffset;
    
    std::vector<std::vector<uint8_t>> sectionsData;
    
    /* Read the main assets look-up table for section lengths */
    for(int i = 0; i < numAssetSections; i++) {
        int assetSectionLength = rom.get_uint(tableOffset + ((i + 1) * 4)) - rom.get_uint(tableOffset + (i * 4));
        sectionsData.push_back(rom.get_bytes_from_range(currentROMOffset, assetSectionLength));
        currentROMOffset += assetSectionLength;
    }
    
    currentROMOffset = assetsStart;
    
    assetsJson["assets"] = json::Array();
    
    /* Extract the assets sections */
    for(int i = 0; i < numAssetSections; i++) {
        json::JSON section = assetSections[i];
        std::string folder = this->outDirectory + "/" + section["folder"].ToString();
        std::string type = section["type"].ToString();
        
        json::JSON outputAsset = json::Object();
        outputAsset["type"] = type;
        
        if(type == "Table") {
            assetsJson["assets"].append(outputAsset);
            continue;
        } else if(type == "Textures") {
            outputAsset["flip-textures"] = section["flip-textures"];
        }
        
        outputAsset["folder"] = section["folder"].ToString();
        outputAsset["filenames"] = json::Array();
        
        if(section.hasKey("table")) {
            int tableIndex = section["table"].ToInt();
            std::vector<std::vector<uint8_t>> sectionFiles 
                = get_section_files(sectionsData[i], sectionsData[tableIndex], type, outputAsset);
            int numberOfSectionFiles = sectionFiles.size();
            
            outputAsset["table"] = tableIndex;
            
            for(int j = 0; j < numberOfSectionFiles; j++) {
                std::string filename = "";
                if(section.hasKey("filenames")) {
                    filename = section["filenames"][j].ToString();
                }
                if(filename == "") {
                    std::stringstream filenameStream;
                    filenameStream << "unknown_" << i << "_" << j;
                    filename = filenameStream.str();
                }
                outputAsset["filenames"].append(filename + get_extension_from_type(type));
                extract_file(rom, type, folder, filename, sectionFiles[j]);
            }
        } else {
            // No lookup table associated, so the section is assumed to be 1 file.
            std::string filename = "";
            if(section.hasKey("filenames")) {
                filename = section["filenames"][0].ToString();
            }
            if(filename == "") {
                std::stringstream filenameStream;
                filenameStream << "unknown_" << i;
                filename = filenameStream.str();
            }
            outputAsset["filenames"].append(filename + get_extension_from_type(type));
            extract_file(rom, type, folder, filename, sectionsData[i]);
        }
        currentROMOffset += sectionsData[i].size();
        assetsJson["assets"].append(outputAsset);
    }
}

bool ExtractConfig::is_supported(){
    return !notSupported;
}

std::string ExtractConfig::get_name(){
    return name;
}

std::string ExtractConfig::get_md5(){
    return md5;
}

std::string ExtractConfig::get_subfolder(){
    return subfolder;
}

std::string ExtractConfig::read_file(std::string filename) {
    std::ifstream t(filename);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 
    return buffer;
}

























