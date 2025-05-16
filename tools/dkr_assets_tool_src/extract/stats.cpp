#include "stats.h"

#include <algorithm>

#include "helpers/debugHelper.h"
#include "helpers/dataHelper.h"

using namespace DkrAssetsTool;

void ExtractStats::add_info(std::string sectionBuildId, ExtractStatInfo newInfo) {
    if(_sectionInfos.find(sectionBuildId) == _sectionInfos.end()) {
        _sectionInfos[sectionBuildId] = {}; // new empty vector.
        if(sectionBuildId == "ASSET_TEXTURES_2D") {
            _sectionInfos[sectionBuildId].reserve(1000);
        }
        else if(sectionBuildId == "ASSET_TEXTURES_3D") {
            _sectionInfos[sectionBuildId].reserve(1500);
        }
    }
    
    _sectionInfos[sectionBuildId].emplace_back(newInfo);
}

void ExtractStats::replace_info(std::string sectionBuildId, std::string buildId, fs::path newOutFilepath) {
    DebugHelper::assert_(_sectionInfos.find(sectionBuildId) != _sectionInfos.end(),
        "(ExtractStats::replace_info) Could not find section id ", sectionBuildId);
        
     auto it = std::find_if(_sectionInfos[sectionBuildId].begin(), _sectionInfos[sectionBuildId].end(), 
        [&buildId](const ExtractStatInfo& statInfo) {
            return statInfo.buildId == buildId;
        }
    );
    
    DebugHelper::assert_(it != _sectionInfos[sectionBuildId].end(),
        "(ExtractStats::replace_info) Could not find build id ", buildId, " in section ", sectionBuildId);
    
    // New info to replace
    it->outFilepath = newOutFilepath; 
}

std::optional<size_t> ExtractStats::try_get_file_index_of_build_id(std::string sectionBuildId, std::string fileBuildId) const {
    if(_sectionInfos.find(sectionBuildId) == _sectionInfos.end()) {
        return std::nullopt;
    }
    
    for(size_t i = 0; i < _sectionInfos.at(sectionBuildId).size(); i++) {
        if(_sectionInfos.at(sectionBuildId).at(i).buildId == fileBuildId) {
            return i;
        }
    }
    
    return std::nullopt;
}

std::optional<std::string> ExtractStats::try_get_build_id_from_file_index(std::string sectionBuildId, size_t fileIndex) const {
    if(_sectionInfos.find(sectionBuildId) == _sectionInfos.end()) {
        return std::nullopt;
    }
    if(fileIndex >= _sectionInfos.at(sectionBuildId).size()) {
        return std::nullopt;
    }
    return _sectionInfos.at(sectionBuildId).at(fileIndex).buildId;
}

std::optional<fs::path> ExtractStats::try_get_output_filepath_from_file_index(std::string sectionBuildId, size_t fileIndex) const {
    if(_sectionInfos.find(sectionBuildId) == _sectionInfos.end()) {
        return std::nullopt;
    }
    if(fileIndex >= _sectionInfos.at(sectionBuildId).size()) {
        return std::nullopt;
    }
    return _sectionInfos.at(sectionBuildId).at(fileIndex).outFilepath;
}

std::optional<std::reference_wrapper<const std::vector<ExtractStatInfo>>> ExtractStats::get_section_info(std::string sectionBuildId) const {
    if(_sectionInfos.find(sectionBuildId) == _sectionInfos.end()) {
        return std::nullopt;
    }
    return _sectionInfos.at(sectionBuildId);
}

size_t ExtractStats::get_file_index_of_build_id(std::string section, std::string fileBuildId) const {
    std::optional<size_t> tryGetFileIndex = try_get_file_index_of_build_id(section, fileBuildId);
    
    DebugHelper::assert_(tryGetFileIndex.has_value(),
        "(ExtractStats::get_file_index_of_build_id) Could not get the index from section \"", section, "\" with build-id ", fileBuildId);
    
    return tryGetFileIndex.value();
}

std::string ExtractStats::get_build_id_from_file_index(std::string section, size_t fileIndex) const {
    std::optional<std::string> tryGetBuildId = try_get_build_id_from_file_index(section, fileIndex);
    
    DebugHelper::assert_(tryGetBuildId.has_value(),
        "(ExtractStats::get_build_id_from_file_index) Could not get a build id from section \"", section, "\" at index ", fileIndex);
    
    return tryGetBuildId.value();
}

fs::path ExtractStats::get_output_filepath_from_file_index(std::string section, size_t fileIndex) const {
    std::optional<fs::path> tryGetOutPath = try_get_output_filepath_from_file_index(section, fileIndex);
    
    DebugHelper::assert_(tryGetOutPath.has_value(),
        "(ExtractStats::get_build_id_from_file_index) Could not get a output path from section \"", section, "\" at index ", fileIndex);
    
    return tryGetOutPath.value();
}

const JsonFile &ExtractStats::get_json(std::string section, size_t fileIndex) const {
    fs::path jsonPath = get_output_filepath_from_file_index(section, fileIndex);
    auto tryGetJson = JsonHelper::get_file(jsonPath);
    
    DebugHelper::assert_(tryGetJson.has_value(),
        "(ExtractStats::get_json) Could not get json file ", jsonPath);
    
    return tryGetJson.value();
}

const JsonFile &ExtractStats::get_json(std::string section, std::string fileBuildId) const {
    return get_json(section, get_file_index_of_build_id(section, fileBuildId));
}

void ExtractStats::print_section_counts() const {
    for (auto section : _sectionInfos) {
        DebugHelper::info(section.first, ": ", section.second.size());
    }
}

void ExtractStats::set_tag(const std::string &key, const std::any value) {
    _tags[key] = value;
}
