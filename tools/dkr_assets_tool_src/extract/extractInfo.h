#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <any>
#include <optional>

#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"
#include "rom.h"
#include "config.h"

#include "helpers/c/cContext.h"

namespace DkrAssetsTool {

class ExtractInfo;
class ExtractStats;

namespace DeferredExtractions {
    void add_extraction(std::string key, ExtractInfo newExtract);
    ExtractInfo &get_extraction(std::string key, size_t index);
    ExtractInfo &get_extraction(std::string key, std::string buildId);
}

class ExtractInfo {
public:
    ExtractInfo(std::string &type, std::string buildId, fs::path filename, fs::path folder, BytesView view, 
        AssetExtractConfig &config, std::string sectionPtr, CContext &ctx, size_t fileIndex, ExtractStats &stats);
    ~ExtractInfo();
    
    void replace_info(std::string &type, fs::path filename, fs::path folder, BytesView view, std::string sectionPtr, size_t fileIndex);
    
    void set_tag(const std::string &key, const std::any elem);
    
    template <typename T>
    T get_tag(const std::string &key, T defaultValue) {
        if(_tags.find(key) == _tags.end()) {
            return defaultValue;
        }
        try {
            return std::any_cast<T>(_tags[key]);
        } catch(std::bad_any_cast &err) {
            return defaultValue;
        }
    }
    
    std::string get_type() const;
    std::string get_build_id() const;
    fs::path get_folder() const;
    fs::path get_filename(std::string extension="") const;
    fs::path get_out_filepath(std::string extension="") const;
    fs::path get_out_folder() const;
    
    const BytesView &get_view() const;
    size_t get_data_size() const;
    
    CContext &get_c_context() const;
    const AssetExtractConfig &get_config() const;
    ExtractStats &get_stats() const;
    
    size_t get_file_index() const;
    
    void get_data_from_rom(std::vector<uint8_t> &out, size_t offset=0, size_t length=-1);
    
    WritableJsonFile &get_json_file();
    void write_json_file();
    void write_raw_data_file();
    
    template <typename T>
    T get_from_config_section(std::string property, T defaultValue) const {
        if(!_config.has_value()) {
            return defaultValue;
        }
        AssetExtractConfig &config = _config.value();
        return config.get<T>(_sectionPtr + property, defaultValue);
    }
    
private:
    std::string _type;
    std::string _buildId;
    fs::path _filename;
    fs::path _folder;
    BytesView _view;
    std::string _sectionPtr;
    std::optional<WritableJsonFile> _jsonFile = std::nullopt;
    std::optional<std::reference_wrapper<AssetExtractConfig>> _config = std::nullopt;
    std::optional<std::reference_wrapper<CContext>> _cContext = std::nullopt;
    std::optional<std::reference_wrapper<ExtractStats>> _stats = std::nullopt;
    
    size_t _fileIndex;
    
    std::unordered_map<std::string, std::any> _tags;
    
    void _make_sure_json_file_is_defined();
};

}
