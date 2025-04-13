#include "extractInfo.h"

using namespace DkrAssetsTool;

#include <sstream>

void DeferredExtractions::add_extraction(std::string key, ExtractInfo newExtract) {
    if(_extractions.find(key) == _extractions.end()) {
        _extractions[key] = std::vector<ExtractInfo>();
    }
    _extractions[key].push_back(newExtract);
}

ExtractInfo &DeferredExtractions::get_extraction(std::string key, size_t index) {
    DebugHelper::assert(_extractions.find(key) != _extractions.end(), 
        "(DeferredExtractions::get_extraction) \"", key, "\" not in map.");
    DebugHelper::assert(index < _extractions[key].size(), 
        "(DeferredExtractions::get_extraction) index ", index, " for key \"", key, "\" is out of range.");
    return _extractions[key][index];
}

/*****************************************************/

ExtractInfo::ExtractInfo(std::string &type, fs::path filename, fs::path folder, DkrExtractROM *rom, DkrExtractConfig *config, CContext *ctx, uint32_t dataOffset, size_t dataLength, size_t fileIndex) 
: rom(rom), config(config), c_context(ctx), _type(type), _filename(filename), _folder(folder), _dataOffset(dataOffset), _dataLength(dataLength), _fileIndex(fileIndex), _isAsset(false)
{
    _check_params();
}

ExtractInfo::ExtractInfo(std::string &type, fs::path filename, fs::path folder, DkrExtractROM *rom, DkrExtractConfig *config, CContext *ctx, uint32_t dataOffset, size_t dataLength, size_t fileIndex, DkrExtractAssetSection *assetSection) 
: assetSection(assetSection), rom(rom), config(config), c_context(ctx), _type(type), _filename(filename), _folder(folder), _dataOffset(dataOffset), _dataLength(dataLength), _fileIndex(fileIndex), _isAsset(true)
{
    if(_filename.empty()) {
        DebugHelper::error("No filename was set for the type \"", _type, "\" in the folder \"", folder, "\"");
    }
    _check_params();
}

ExtractInfo::~ExtractInfo(){
    
}

void ExtractInfo::set_tag(const std::string &key, const std::any value) {
    _tags[key] = value;
}

/*
void ExtractInfo::set_tag_as_array(const std::string &key, size_t numElements) {
    _tags[key] = std::vector<ExtractInfoTagValue>(numElements);
}

void ExtractInfo::add_elem_to_tag_array(const std::string &key, ExtractInfoTagValue elem, int32_t index) {
    std::vector<ExtractInfoTagValue> &arr = std::get<std::vector<ExtractInfoTagValue>>(_tags[key]);
    if(index < 0) {
        arr.push_back(elem);
        return;
    }
    arr[index] = elem;
}
*/

bool ExtractInfo::is_asset() {
    return _isAsset;
}

std::string ExtractInfo::get_type() {
    return _type;
}

fs::path ExtractInfo::get_folder() {
    return _folder;
}

fs::path ExtractInfo::get_filename(const char *extension) {
    fs::path out = _filename;
    if(extension[0] != '\0') {
        out.replace_extension(extension);
    }
    return out;
}

uint32_t ExtractInfo::get_data_offset() {
    return _dataOffset;
}

size_t ExtractInfo::get_data_size() {
    return _dataLength;
}

size_t ExtractInfo::get_file_index() {
    return _fileIndex;
}

fs::path ExtractInfo::get_out_filepath(const char *extension) {
    fs::path out = _folder / _filename;
    if(assetSection != nullptr) {
        out = assetSection->folder / out;
    }
    if(extension[0] != '\0') {
        out.replace_extension(extension);
    }
    return out;
}

fs::path ExtractInfo::get_out_folder() {
    fs::path out = _folder;
    if(assetSection != nullptr) {
        out = assetSection->folder / out;
    }
    return out;
}

void ExtractInfo::get_data_from_rom(std::vector<uint8_t> &out) {
    rom->get_data(_dataOffset, _dataLength, out);
}

void ExtractInfo::write_rom_data_to_file(fs::path finalFilepath, uint32_t offset, int32_t length) {
    if(length < 0) {
        length = (int32_t)_dataLength;
        if(length < 1) {
            DebugHelper::info_verbose("Auto-set length to ", _dataLength);
        }
    }
    if(length < 1) {
        DebugHelper::error("(ExtractInfo::write_rom_data_to_file) Invalid length of ", length, " for path ", finalFilepath);
    }
    
    if((size_t)(offset + length) > _dataLength) {
        DebugHelper::error("(ExtractInfo::write_rom_data_to_file) Out of bounds! (offset + length) was larger than dataLength for path ", finalFilepath);
    }
    
    rom->write_rom_section_to_binary_file(finalFilepath, _dataOffset + offset, length);
}

void ExtractInfo::_check_params() {
    if(_type == "GameText") {
        _tags["dialog"] = (_dataOffset & 0x80000000) != 0;
        _dataOffset &= 0x7FFFFFFF;
    }
}
