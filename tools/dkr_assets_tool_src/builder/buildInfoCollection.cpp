#include "buildInfoCollection.h"

#include "libs/ThreadPool.h"

#include "helpers/debugHelper.h"
#include "helpers/dataHelper.h"
#include "misc/globalSettings.h"

using namespace DkrAssetsTool;

const size_t MAX_NUMBER_OF_BUILD_INFOS = 10000; 

BuildInfoCollection::BuildInfoCollection() {
    fs::path assetsPath = GlobalSettings::get_decomp_path_to_output_assets();
    _buildInfos.reserve(MAX_NUMBER_OF_BUILD_INFOS); // More than likely overkill, but I REALLY don't want pointers changing mid-build.
}

BuildInfoCollection::~BuildInfoCollection() {
}

void BuildInfoCollection::add_build_info(std::string sectionBuildId, std::string buildId, const JsonFile &src, const fs::path &dir, const BuildInfoContext &infoContext) {
    _buildInfoMutex.lock();
    
    if(_buildInfoSections.find(sectionBuildId) == _buildInfoSections.end()) {
        _buildInfoSections[sectionBuildId] = {};
        
        // Textures have a lot of files.
        if(sectionBuildId == "ASSET_TEXTURES_2D") {
            _buildInfoSections[sectionBuildId].reserve(1000);
        } else if(sectionBuildId == "ASSET_TEXTURES_3D") {
            _buildInfoSections[sectionBuildId].reserve(1500);
        }
    }
    
    size_t index = _buildInfos.size();
    
    DebugHelper::assert_(index < MAX_NUMBER_OF_BUILD_INFOS,
        "(BuildInfoCollection::add_build_info) Max number of assets reached! Limit was ", MAX_NUMBER_OF_BUILD_INFOS);
    
    size_t fileIndex = _buildInfoSections[sectionBuildId].size();
    _buildInfos.emplace_back(buildId, sectionBuildId, src, fileIndex, dir, infoContext);
    
    // Add the index to the section.
    _buildInfoSections[sectionBuildId].emplace_back(index);
    
    _buildInfoMutex.unlock();
}

size_t BuildInfoCollection::add_deferred_build_info(std::string sectionBuildId, std::string buildId, std::string deferredFromBuildId, std::string deferredFromSectionId, 
    const std::vector<uint8_t> &out, const fs::path &dir, const BuildInfoContext &infoContext) {
    _buildInfoMutex.lock();
    
    if(_buildInfoSections.find(sectionBuildId) == _buildInfoSections.end()) {
        _buildInfoSections[sectionBuildId] = {};
    }
    
    int index = _buildInfos.size();
    
    DebugHelper::assert_(index < MAX_NUMBER_OF_BUILD_INFOS,
        "(BuildInfoCollection::add_build_info) Max number of assets reached! Limit was ", MAX_NUMBER_OF_BUILD_INFOS);
        
    size_t fileIndex = _buildInfoSections[sectionBuildId].size();
    _buildInfos.emplace_back(buildId, sectionBuildId, deferredFromBuildId, deferredFromSectionId, out, fileIndex, dir, infoContext);
    
    // Do not process deferred assets.
    _buildInfos.back().done();
    
    // Add the index to the section.
    _buildInfoSections[sectionBuildId].emplace_back(index);
    
    _buildInfoMutex.unlock();
    
    return fileIndex;
}

void BuildInfoCollection::add_deferred_build_info(std::string sectionBuildId, std::string buildId, std::string deferredFromBuildId, std::string deferredFromSectionId, 
    size_t fileIndex, const std::vector<uint8_t> &out, const fs::path &dir, const BuildInfoContext &infoContext) {
    _buildInfoMutex.lock();
    
    if(_buildInfoSections.find(sectionBuildId) == _buildInfoSections.end()) {
        _buildInfoSections[sectionBuildId] = {};
    }
    
    if(_buildInfoSections[sectionBuildId].size() <= fileIndex) {
        _buildInfoSections[sectionBuildId].resize(fileIndex + 1);
    }
    
    size_t index = _buildInfos.size();
    
    DebugHelper::assert_(index < MAX_NUMBER_OF_BUILD_INFOS,
        "(BuildInfoCollection::add_build_info) Max number of assets reached! Limit was ", MAX_NUMBER_OF_BUILD_INFOS);
        
    _buildInfos.emplace_back(buildId, sectionBuildId, deferredFromBuildId, deferredFromSectionId, out, fileIndex, dir, infoContext);
    
    // Do not process deferred assets.
    _buildInfos.back().done();
    
    // Add the index to the section.
    _buildInfoSections[sectionBuildId][fileIndex] = index;
    
    _buildInfoMutex.unlock();
}

void BuildInfoCollection::run_builds(std::function<void(BuildInfo &)> callbackFunction, const std::vector<std::string> &sectionsOrder) {
    size_t threadCount = GlobalSettings::get_max_thread_count();
    bool multithreaded = threadCount != 1;
    DebugHelper::info_verbose("Using ", threadCount, " thread", (multithreaded ? "s" : ""));
    
    if(multithreaded) {
        // Multi-threaded (Better for performance)
        ThreadPool pool(threadCount);
        for(const std::string &sectionBuildId : sectionsOrder) {
            if(_buildInfoSections.find(sectionBuildId) == _buildInfoSections.end()) {
                // Skip empty sections.
                continue;
            }
            for(int buildInfoIndex : _buildInfoSections[sectionBuildId]) {
                BuildInfo &info = _buildInfos[buildInfoIndex];
                pool.enqueue([&info, &callbackFunction] {
                    if(!info.is_complete()) {
                        callbackFunction(info);
                        info.done();
                    }
                });
            }
        }
    } else {
        // Single-threaded (Better for debugging)
        for(const std::string &sectionBuildId : sectionsOrder) {
            if(_buildInfoSections.find(sectionBuildId) == _buildInfoSections.end()) {
                // Skip empty sections.
                continue;
            }
            for(int buildInfoIndex : _buildInfoSections[sectionBuildId]) {
                BuildInfo &info = _buildInfos[buildInfoIndex];
                if(!info.is_complete()) {
                    callbackFunction(info);
                    info.done();
                }
            }
        }
    }
    
}
    
void BuildInfoCollection::get_infos_for_section(std::string sectionBuildId, std::function<void(BuildInfo &info)> callbackFunction) {
    std::vector<int> &sectionIndices = _buildInfoSections[sectionBuildId];
    for(int buildInfoIndex : sectionIndices) {
        callbackFunction(_buildInfos[buildInfoIndex]);
    }
}

void BuildInfoCollection::create_assets_file() {
    
}

void BuildInfoCollection::print_section_counts() {
    for(auto &pair : _buildInfoSections) {
        DebugHelper::info(pair.first, ": ", pair.second.size());
    }
}

std::mutex &BuildInfoCollection::get_global_mutex() {
    return _globalMutex;
}

size_t BuildInfoCollection::get_section_count() const {
    return _buildInfoSections.size();
}

size_t BuildInfoCollection::get_file_count_for_section(std::string sectionBuildId) const {
    if(_buildInfoSections.find(sectionBuildId) == _buildInfoSections.end()) {
        return 0;
    }
    return _buildInfoSections.at(sectionBuildId).size();
}
    
size_t BuildInfoCollection::get_size_of_section(std::string sectionBuildId) const {
    if(_buildInfoSections.find(sectionBuildId) == _buildInfoSections.end()) {
        return 0;
    }
    
    const std::vector<int> &sectionIndices = _buildInfoSections.at(sectionBuildId);
    
    size_t totalSize = 0;
    
    for(int buildInfoIndex : sectionIndices) {
        totalSize += _buildInfos.at(buildInfoIndex).out.size();
    }
    
    // Make sure the size is 16-byte aligned
    totalSize = DataHelper::align16(totalSize);
    
    return totalSize;
}
