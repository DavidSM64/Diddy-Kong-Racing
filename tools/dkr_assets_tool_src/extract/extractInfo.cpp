#include "extractInfo.h"

#include <sstream>

#include "misc/globalSettings.h"

#include "stats.h"

using namespace DkrAssetsTool;

/*****************************************************/

std::unordered_map<std::string, std::vector<ExtractInfo>> _extractions;

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

ExtractInfo::ExtractInfo(std::string &type, std::string buildId, fs::path filename, fs::path folder, BytesView view, AssetExtractConfig &config, std::string sectionPtr, CContext &ctx, size_t fileIndex, ExtractStats &stats) 
:  _type(type), _buildId(buildId), _filename(filename), _folder(folder), _view(view), _sectionPtr(sectionPtr), _config(config), _cContext(ctx), _stats(stats), _fileIndex(fileIndex)
{
    DebugHelper::assert_(!_filename.empty(),
        "(ExtractInfo::ExtractInfo) No filename was set for the type \"", _type, "\" in the folder \"", folder, "\"");
    DebugHelper::assert_(!_buildId.empty(),
        "(ExtractInfo::ExtractInfo) No build id was set for the filename \"", _filename, "\"");
    
    //DebugHelper::info(_filename, " was created!");
}

ExtractInfo::~ExtractInfo(){
    //DebugHelper::warn(_filename, " is being deleted!");
}

void ExtractInfo::set_tag(const std::string &key, const std::any value) {
    _tags[key] = value;
}

std::string ExtractInfo::get_type() const {
    return _type;
}

std::string ExtractInfo::get_build_id() const {
    return _buildId;
}

fs::path ExtractInfo::get_folder() const {
    return _folder;
}

fs::path ExtractInfo::get_filename(std::string extension) const {
    fs::path out = _filename;
    if(!extension.empty()) {
        out.replace_extension(extension);
    }
    return out;
}

const CContext &ExtractInfo::get_c_context() const {
    return _cContext.value();
}

const AssetExtractConfig &ExtractInfo::get_config() const {
    return _config.value();
}

ExtractStats &ExtractInfo::get_stats() const {
    return _stats.value();
}

size_t ExtractInfo::get_file_index()  const{
    return _fileIndex;
}

fs::path ExtractInfo::get_out_filepath(std::string extension) const {
    fs::path out = get_out_folder() / _filename;
    if(!extension.empty()) {
        out.replace_extension(extension);
    }
    return out;
}

fs::path ExtractInfo::get_out_folder() const {
    return _folder;
}

const BytesView &ExtractInfo::get_view() const {
    return _view;
}

size_t ExtractInfo::get_data_size() const {
    return _view.size();
}

// TODO: Remove this in favor of just getting the byte-view
void ExtractInfo::get_data_from_rom(std::vector<uint8_t> &out, size_t offset, size_t length) {
    if(length == (size_t)-1) {
        length = _view.size();
    }
    out = std::vector<uint8_t>(_view.data() + offset, _view.data() + offset + length);
}
    
WritableJsonFile &ExtractInfo::get_json_file() {
    _make_sure_json_file_is_defined();
    return _jsonFile.value();
}

void ExtractInfo::write_json_file() {
    _make_sure_json_file_is_defined();
    _jsonFile.value().save();
}

void ExtractInfo::write_raw_data_file() {
    fs::path outPath = GlobalSettings::get_decomp_path_to_vanilla_assets() / get_out_filepath(".bin");
    FileHelper::write_binary_file(_view, outPath, true);
}

void ExtractInfo::_make_sure_json_file_is_defined() {
    if(_jsonFile.has_value()) {
        return;
    }
    
    fs::path outPath = GlobalSettings::get_decomp_path_to_vanilla_assets() / get_out_filepath(".json");
    _jsonFile = WritableJsonFile(outPath);
}
