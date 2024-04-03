#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <any>

#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"
#include "rom.h"
#include "config.h"

#include "helpers/c/cContext.h"

class ExtractInfo;

class DeferredExtractions {
public:
    static DeferredExtractions& get() {
        static DeferredExtractions instance;
        return instance;
    }

    void add_extraction(std::string key, ExtractInfo newExtract);
    ExtractInfo &get_extraction(std::string key, size_t index);
private:
    std::unordered_map<std::string, std::vector<ExtractInfo>> _extractions;
};

class ExtractInfo {
public:
    // Code file info
    ExtractInfo(std::string &type, fs::path filename, fs::path folder, DkrExtractROM *rom, DkrExtractConfig *config, CContext *ctx,
        uint32_t dataOffset, size_t dataLength, size_t fileIndex);
    // Asset file info
    ExtractInfo(std::string &type, fs::path filename, fs::path folder, DkrExtractROM *rom, DkrExtractConfig *config, CContext *ctx,
        uint32_t dataOffset, size_t dataLength, size_t fileIndex, DkrExtractAssetSection *assetSection);
    ~ExtractInfo();
    
    void set_tag(const std::string &key, const std::any elem);
    //void set_tag_as_array(const std::string &key, size_t numElements=1);
    //void add_elem_to_tag_array(const std::string &key, const ExtractInfoTagValue elem, int32_t index=-1);
    
    template <typename T>
    T get_tag(const std::string &key, T defaultValue) {
        if(_tags.find(key) == _tags.end()) {
            return defaultValue;
        }
        
        return std::any_cast<T>(_tags[key]);
    }
    
    // There may or may not be a pointer to a DkrExtractAssetSection. Code sections will not have it for obvious reasons.
    // TODO: I think I'm just being lazy here. Probably needs to be refactored.
    DkrExtractAssetSection *assetSection = nullptr;
    
    DkrExtractROM *rom;
    DkrExtractConfig *config;
    
    CContext *c_context; // C Code context. (For loading enums & structs)
    
    bool is_asset();
    
    std::string get_type();
    fs::path get_folder();
    fs::path get_filename(const char *extension = "\0");
    fs::path get_out_filepath(const char *extension = "\0");
    fs::path get_out_folder();
    
    uint32_t get_data_offset();
    size_t get_data_size();
    
    size_t get_file_index();
    
    void get_data_from_rom(std::vector<uint8_t> &out);
    
    void write_rom_data_to_file(fs::path finalFilepath, uint32_t offset=0, int32_t length=-1);
    
private:
    
    std::string _type;
    fs::path _filename;
    fs::path _folder;
    uint32_t _dataOffset;
    size_t _dataLength;
    
    size_t _fileIndex;
    
    bool _isAsset;
    
    std::unordered_map<std::string, std::any> _tags;
    
    void _check_params();
};
