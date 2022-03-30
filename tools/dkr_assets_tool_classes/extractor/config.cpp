#include "config.h"

#define REVISION_NUMBER 2
#define REVISION_MINOR_NUMBER 0

const std::string BASE_DIR_NAME = "vanilla";
const std::string EXT_DIR_NAME = "packages";

#define VANILLA_WARNING_FILENAME "PLEASE_DONT_MODIFY_ANYTHING.txt"

ExtractConfig::ExtractConfig(std::string configFilepath, std::string outDirectory) {
    std::cout << "Reading config \"" << configFilepath << "\"" << std::endl;
    configJSON = json::JSON::Load(read_text_file(configFilepath));
    
    this->outBaseDirectory = outDirectory + "/assets/" + BASE_DIR_NAME + "/" + configJSON["subfolder"].ToString();
    this->outDirectory = outDirectory + "/assets/" + configJSON["subfolder"].ToString();
    this->name = configJSON["config-name"].ToString();
    this->subfolder = configJSON["subfolder"].ToString();
    this->md5 = configJSON["checksum-md5"].ToString();
    this->notSupported = configJSON["not-supported"].ToString() == "true";
    
    assetsJson["@version"] = this->subfolder;
    assetsJson["@revision"] = REVISION_NUMBER;
    assetsJson["@revision-minor"] = REVISION_MINOR_NUMBER;

    // Create package extensions folder if it doesn't exist.
    if(this->subfolder == "us_1.0"){
        std::string packagesDir = outDirectory + "/assets/" + EXT_DIR_NAME + "/" + configJSON["subfolder"].ToString();
        create_directory(packagesDir);
        json::JSON orderJson = json::Array();
        write_json(orderJson, packagesDir + "/order.json");
    }
}

ExtractConfig::~ExtractConfig() {
}

void ExtractConfig::find_rom_for_this_config_and_extract(std::vector<ROM*> &roms) {
    if(this->subfolder != "us_1.0"){
        std::cout << "Sorry, extracting only works for us_1.0 at the moment." << std::endl;
        return;
    }
    for (ROM* rom : roms) {
        if(rom->get_md5() == this->md5) {
            this->rom = rom;
            std::cout << "Extracting using config: \"" << this->name << "\"" << std::endl; 
            extract();
            return;
        }
    }
    std::cout << "No valid ROMs were found for the config \"" << this->name << "\"" << std::endl;
}

bool ExtractConfig::is_correct_version(std::string version) {
    return this->subfolder == version;
}

void ExtractConfig::extract_code_sections(int &romOffset) {
    json::JSON codeSections = configJSON["code"]["sections"];
    int numCodeSections = codeSections.length();
    for(int i = 0; i < numCodeSections; i++) {
        json::JSON section = codeSections[i];
        std::string type = section["type"].ToString();
        
        json::JSON files = section["files"];
        std::string folder = this->outBaseDirectory + "/" + section["folder"].ToString();

        if(type != "NoExtract") {
            create_directory(folder);
        }
        
        std::string key = "CODE_" + std::to_string(i);
        
        int numFiles = files.length();
        for(int j = 0; j < numFiles; j++) {
            json::JSON file = files[j];
            int length = std::stoul(file["length"].ToString(), nullptr, 16);
            extractions.push_back(ExtractInfo(key, type, folder, file["filename"].ToString(), 
                rom->get_bytes_from_range(romOffset, length)));
            romOffset += length;
        }
        
    }
}

std::string get_extension_from_type(std::string type) {
    if(is_json_type(type)) {
        return ".json";
    } else if(is_compressed_type(type)) {
        return ".cbin";
    } else {
        return ".bin";
    }
}

std::vector<std::vector<uint8_t>> get_section_files(std::vector<uint8_t>& section, std::vector<uint8_t>& table, std::string tableType, json::JSON& outputAsset) {
    std::vector<std::vector<uint8_t>> out;
    
    int currentTableIndex = 0;
    int scale = 1; // Each table entry is 4-bytes long.
    int offset = 0;
    
    if(tableType == "MenuText") {
        outputAsset["_text-entry-count"] = std::to_string(get_big_endian_word(table, currentTableIndex*4));
        currentTableIndex = 1; // The first entry is the number of text entries for each language.
    } else if(tableType == "TTGhosts") {
        scale = 2; // Each table entry is 8-bytes long.
        offset = 1; // offset by 4 bytes.
        //outputAsset["meta"] = json::Array();
    } else if (tableType == "GameText") {
        // Temporary
        outputAsset["_textTypes"] = json::Array();
    }
    
    uint32_t currentTableValue = get_big_endian_word(table, (currentTableIndex * scale + offset)*4);
    uint32_t nextTableValue = get_big_endian_word(table, ((currentTableIndex + 1) * scale + offset)*4);
    
    if (tableType == "Audio") {
        // The audio table doesn't start at offset 0, so this check will extract
        // the first actual part of the audio section.
        std::vector<uint8_t> file(section.begin(), section.begin() + currentTableValue);
        out.push_back(file);
    }
    
    while(nextTableValue != 0xFFFFFFFF) {
        
        if(tableType == "GameText") {
            bool isDialog = (currentTableValue & 0x80000000) == 0x80000000;
            outputAsset["_textTypes"].append(isDialog ? 1 : 0);
            currentTableValue &= 0x7FFFFFFF;
            nextTableValue &= 0x7FFFFFFF;
        } else if(tableType == "Miscellaneous") {
            currentTableValue *= 4;
            nextTableValue *= 4;
        }
        
        int length = nextTableValue - currentTableValue;
        if(length < 0) {
            display_error_and_abort("Invalid table length: ", length, "\ncurrentTableValue: ", currentTableValue, "\nnextTableValue: ", nextTableValue);
        }
        
        std::vector<uint8_t> file(section.begin() + currentTableValue, section.begin() + nextTableValue);
        out.push_back(file);
        
        currentTableIndex++;
        currentTableValue = get_big_endian_word(table, (currentTableIndex * scale + offset)*4);
        nextTableValue = get_big_endian_word(table, ((currentTableIndex + 1) * scale + offset)*4);
    }
    
    return out;
}

void ExtractConfig::extract_asset_sections(int &romOffset) {
    /* Make sure the assets section has the correct number of entries. */
    json::JSON assetSections = configJSON["assets"]["sections"];
    int numAssetSections = assetSections.length();
    int numAssetSectionsFromTable = rom->get_uint(romOffset);
    
    if(numAssetSections != numAssetSectionsFromTable) {
        display_error_and_abort("Number of asset sections in config does not match ROM.\nNumber of asset sections in Config: ", 
            numAssetSections, "\nNumber of asset sections in ROM:    ", numAssetSectionsFromTable);
    }
    
    romOffset += 4;
    int tableOffset = romOffset;
    romOffset += (numAssetSections + 1) * 4;
    int assetsStart = romOffset;
    
    std::vector<std::vector<uint8_t>> sectionsData;
    
    /* Read the main assets look-up table for section lengths */
    for(int i = 0; i < numAssetSections; i++) {
        int assetSectionLength = rom->get_uint(tableOffset + ((i + 1) * 4)) - rom->get_uint(tableOffset + (i * 4));
        sectionsData.push_back(rom->get_bytes_from_range(romOffset, assetSectionLength));
        romOffset += assetSectionLength;
    }
    
    romOffset = assetsStart;
    
    assetsJson["assets"] = json::Object();
    assetsJson["assets"]["order"] = json::Array();
    assetsJson["assets"]["sections"] = json::Object();
    
    /* Extract the assets sections */
    
    // First loop to get the order array in place.
    for(int i = 0; i < numAssetSections; i++) {
        json::JSON section = assetSections[i];
        std::string build_id = section["build-id"].ToString();
        assetsJson["assets"]["order"].append(build_id);
    }
    // Second loop for everything else
    for(int i = 0; i < numAssetSections; i++) {
        json::JSON section = assetSections[i];
        std::string folder = this->outBaseDirectory + "/" + section["folder"].ToString();
        std::string type = section["type"].ToString();
        std::string build_id = section["build-id"].ToString();
        
        if(type != "NoExtract") {
            create_directory(folder);
        }
        
        json::JSON sectionOut = json::Object();
        
        sectionOut["type"] = type;
        
        if(section.hasKey("folder") && !section["folder"].IsNull()) {
            sectionOut["folder"] = section["folder"];
        }
        
        if(section.hasKey("table")) {
            int tableIndex = section["table"].ToInt();
            sectionOut["table"] = assetsJson["assets"]["order"][tableIndex];
            
            std::vector<std::vector<uint8_t>> sectionFiles 
                = get_section_files(sectionsData[i], sectionsData[tableIndex], type, sectionOut);
            int numberOfSectionFiles = sectionFiles.size();
            
            if(numberOfSectionFiles > 0) {
                sectionOut["files"] = json::Object();
                sectionOut["files"]["order"] = json::Array();
                sectionOut["files"]["sections"] = json::Object();
            }
                
            for(int j = 0; j < numberOfSectionFiles; j++) {
                std::unordered_map<std::string, std::string> *tags = nullptr;
                std::string filename = "";
                std::string key = "";
                if(section.hasKey("filenames")) {
                    filename = section["filenames"][j].ToString();
                }
                if(section.hasKey("child-build-ids")) {
                    key = section["child-build-ids"][j].ToString();
                }
                if(filename == "") {
                    std::stringstream filenameStream;
                    filenameStream << "unknown_" << i << "_" << j;
                    filename = filenameStream.str();
                }
                if(key == "") {
                    std::stringstream keyStream;
                    keyStream << build_id << "_" << j;
                    key = keyStream.str();
                }
                make_uppercase(key);
                sectionOut["files"]["order"].append(key);
                sectionOut["files"]["sections"][key] = json::Object();
                sectionOut["files"]["sections"][key]["filename"] = filename + get_extension_from_type(type);
                
                if(type == "GameText") {
                    if(tags == nullptr) {
                        tags = new std::unordered_map<std::string, std::string>();
                    }
                    (*tags)["text-type"] = (sectionOut["_textTypes"][j].ToInt() == 1) ? "Dialog" : "Textbox";
                } else if(type == "MenuText") {
                    if(tags == nullptr) {
                        tags = new std::unordered_map<std::string, std::string>();
                    }
                    (*tags)["text-entry-count"] = sectionOut["_text-entry-count"].ToString();
                    int numberOfEntries = stoi((*tags)["text-entry-count"]);
                    for(int k = 0; k < numberOfEntries; k++) {
                        if(!section["menu-text-build-ids"][k].IsNull()) {
                            (*tags)["text-entry-build-id_" + std::to_string(k)] = section["menu-text-build-ids"][k].ToString();
                        }
                    }
                    if(!sectionOut.hasKey("menu-text-build-ids")) {
                        sectionOut["menu-text-build-ids"] = section["menu-text-build-ids"];
                    }
                    sectionOut["files"]["sections"][key]["language"] = section["language-order"][j];
                } else if (type == "Textures") {
                    if(tags == nullptr) {
                        tags = new std::unordered_map<std::string, std::string>();
                    }
                    (*tags)["flip-texture_" + key] = section["flip-textures"][j].ToInt() == 1 ? "true" : "false";
                }
                
                extractions.push_back(ExtractInfo(key, type, folder, filename, sectionFiles[j], tags));
            }
            
            if(type == "GameText") {
                sectionOut.erase("_textTypes");
            } else if(type == "MenuText") {
                sectionOut.erase("_text-entry-count");
            }
            
        } else {
            if(type != "Table" && type != "NoExtract" && type != "Empty") {
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
                sectionOut["filename"] = filename + get_extension_from_type(type);
                extractions.push_back(ExtractInfo(build_id, type, folder, filename, sectionsData[i]));
            } else if (type == "Table") {
                sectionOut["for"] = section["for"];
            }
        }

        if(type != "Table" && type != "NoExtract" && type != "Empty") {
            std::string sectionFilename = build_id + ".json";
            make_lowercase(sectionFilename);
            write_json(sectionOut, this->outBaseDirectory + "/" + sectionFilename);
            assetsJson["assets"]["sections"][build_id] = sectionFilename;
        } else {
            assetsJson["assets"]["sections"][build_id] = sectionOut;
        }
    }
}

void write_vanilla_warning_file(std::string baseDirectory) {
    std::string warningText = "";
    warningText += "This directory contains all the non-modified assets for DKR.\n";
    warningText += "It is VERY important that you do not modify any of the assets in this directory.\n";
    warningText += "If you do, then you might create headaches for yourself later when trying to revert back to a matching build.\n";
    write_text_file(warningText, baseDirectory + "/../" + VANILLA_WARNING_FILENAME);
}

void ExtractConfig::execute_extraction() {
    // These braces are important, because I want the ThreadPool to call its destructor by going out of scope.
    //{
        ThreadPool pool(std::thread::hardware_concurrency()); 
        //ThreadPool pool(1);
        
        for(int i = 0; i < extractions.size(); i++) {
            std::string key = extractions[i].key;
            std::string type = extractions[i].type;
            std::string folder = extractions[i].folder;
            std::string filename = extractions[i].filename;
            std::vector<uint8_t> data = extractions[i].data;
            std::unordered_map<std::string, std::string> *tags = extractions[i].tags;
            pool.enqueue([this, key, type, folder, filename, data, tags] {
                std::string outFilepath = folder + "/" + filename;
                
                if(type == "MenuText") {
                    ExtractMenuText(key, data, outFilepath + ".json", tags);
                } else if(type == "GameText") {
                    ExtractGameText(key, data, outFilepath + ".json", tags);
                } else if(type == "TTGhosts") {
                    ExtractTTGhost(key, data, outFilepath + ".json", configJSON);
                } else if(type == "LevelNames") {
                    ExtractLevelName(key, data, outFilepath + ".json");
                } else if(type == "LevelHeaders") {
                    ExtractLevelHeader(key, data, outFilepath + ".json");
                } else if(type == "Textures") {
                    ExtractTextures(key, data, outFilepath + ".json", tags);
                } else if(type == "Sprites") {
                    ExtractSprite(key, data, outFilepath + ".json", configJSON);
                } else if(type == "Fonts") {
                    ExtractFonts(key, data, outFilepath + ".json", configJSON);
                } else if(is_binary_type(type)) {
                    ExtractBinary(key, data, outFilepath + ".bin");
                } else if(is_compressed_type(type)) {
                    ExtractCompressed(key, data, outFilepath + ".cbin");
                } else if(type == "Empty") {
                } else if(type != "NoExtract") {
                    display_error_and_abort("Unknown extraction type: ", type);
                }
            });
        }
    //}
}

void ExtractConfig::extract() {
    int romOffset = 0;
    extract_code_sections(romOffset);
    extract_asset_sections(romOffset);
    
    std::string jsonFilename = outBaseDirectory + "/assets.json";
    write_json(assetsJson, jsonFilename);

    execute_extraction();
    
    while(!path_exists(jsonFilename)){
        std::cout << "Not created yet!" << std::endl;
    } // Wait for assets.json to be created.
    
    // All extractions are done at this point.
    std::cout << "Finished extracting! Copying from vanilla folder..." << std::endl;
    recursively_copy_directory(this->outBaseDirectory, this->outDirectory);
    write_vanilla_warning_file(this->outBaseDirectory);
}
