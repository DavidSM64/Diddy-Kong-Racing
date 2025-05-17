#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include <any>

#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {
    
typedef struct ExtractStatInfo {
    std::string buildId;
    fs::path outFilepath;
    fs::path localPath;
} ExtractStatInfo;

// TODO: This needs a better name.
class ExtractStats {
public:
    void add_info(std::string sectionBuildId, ExtractStatInfo newInfo);
    
    void replace_info(std::string sectionBuildId, std::string buildId, fs::path newOutFilepath);
    
    // Returns std::nullopt if not in the map
    std::optional<size_t> try_get_file_index_of_build_id(std::string sectionBuildId, std::string fileBuildId) const;
    std::optional<std::string> try_get_build_id_from_file_index(std::string sectionBuildId, size_t fileIndex) const;
    std::optional<fs::path> try_get_output_filepath_from_file_index(std::string sectionBuildId, size_t fileIndex) const;
    
    // Returns std::nullopt if sectionBuildId is not in the map
    std::optional<std::reference_wrapper<const std::vector<ExtractStatInfo>>> get_section_info(std::string sectionBuildId) const;
    
    // These will throw an error if not in the map
    size_t get_file_index_of_build_id(std::string sectionBuildId, std::string fileBuildId) const;
    std::string get_build_id_from_file_index(std::string sectionBuildId, size_t fileIndex=0) const;
    fs::path get_output_filepath_from_file_index(std::string sectionBuildId, size_t fileIndex=0) const;
    const JsonFile &get_json(std::string sectionBuildId, size_t fileIndex=0) const;
    const JsonFile &get_json(std::string sectionBuildId, std::string fileBuildId) const;
    
    void print_section_counts() const;
    
    // Tags are for setting/getting generic info between different types.
    void set_tag(const std::string &key, const std::any elem);
    
    template <typename T>
    T get_tag(const std::string &key, T defaultValue) const {
        if(_tags.find(key) == _tags.end()) {
            return defaultValue;
        }
        try {
            return std::any_cast<T>(_tags.at(key));
        } catch(std::bad_any_cast &err) {
            return defaultValue;
        }
    }
    
private:
    std::unordered_map<std::string, std::vector<ExtractStatInfo>> _sectionInfos;
    std::unordered_map<std::string, std::any> _tags;
};

}