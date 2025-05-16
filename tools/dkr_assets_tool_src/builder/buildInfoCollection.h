#pragma once

#include <functional>
#include <vector>
#include <unordered_map>
#include <mutex>

#include "helpers/fileHelper.h"

#include "builder/buildInfo.h"

namespace DkrAssetsTool {

class BuildInfoCollection {
public:
    BuildInfoCollection();
    ~BuildInfoCollection();

    void add_build_info(std::string sectionBuildId, std::string buildId, const JsonFile &src, const fs::path &dir, const BuildInfoContext &infoContext);
    
    // Adds deferred info to the end of the list. Returns the fileIndex of the added asset.
    size_t add_deferred_build_info(std::string sectionBuildId, std::string buildId, const std::vector<uint8_t> &out, 
        const fs::path &dir, const BuildInfoContext &infoContext);
        
    // Adds deferred info to a specific file index.
    void add_deferred_build_info(std::string sectionBuildId, std::string buildId, size_t fileIndex, const std::vector<uint8_t> &out, 
        const fs::path &dir, const BuildInfoContext &infoContext);
    
    void run_builds(std::function<void(BuildInfo &info)> callbackFunction);
    
    void get_infos_for_section(std::string sectionBuildId, std::function<void(BuildInfo &info)> callbackFunction);
    
    void create_assets_file();
    
    void print_section_counts();
    
    std::mutex &get_global_mutex();
    
    size_t get_section_count() const;
    
    // Returns number of files for section.
    size_t get_file_count_for_section(std::string sectionBuildId) const;
    
    // Returns total bytes size for section.
    size_t get_size_of_section(std::string sectionBuildId) const;
    
private:
    // Place for all of the build infos to exist.
    // Note: Should only ever be added to! Do NOT erase any entries during the building process!
    std::vector<BuildInfo> _buildInfos; 
    
    std::vector<std::string> _sectionOrder;
    
    // <key: Section build id, value: Array of indices into _buildInfos for files associated with the section>
    std::unordered_map<std::string, std::vector<int>> _buildInfoSections;
    
    std::mutex _buildInfoMutex;
    std::mutex _globalMutex;
};

}
