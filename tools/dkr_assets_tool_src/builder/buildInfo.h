#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <mutex>

#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cContext.h"

namespace DkrAssetsTool {

typedef enum BuildInfoType {
    BUILD_TO_FILE, // When building a single asset.
    BUILD_TO_BINARY // When building all assets
} BuildInfoType;

class BuildStats;
class BuildInfoCollection;

class BuildInfoContext {
public:
    BuildInfoContext(CContext &cContext, BuildStats &stats, BuildInfoCollection &collection);
    
    CContext &get_c_context() const;
    BuildStats &get_stats() const;
    BuildInfoCollection &get_collection() const;
    
    // Used in BuildObjectMap
    void init_obj_beh_to_entry_map(); 
    std::string get_object_entry_from_behavior(std::string objBehavior) const;
private:
    std::reference_wrapper<CContext> _cContext;
    std::reference_wrapper<BuildStats> _stats;
    std::reference_wrapper<BuildInfoCollection> _collection;
    
    std::unordered_map<std::string, std::string> _objBehaviorToEntry;
};

class BuildInfo {
public:
    BuildInfo();
    //BuildInfo(std::string buildId, JsonFile *src, const fs::path &dst, const fs::path &dir); // BUILD_TO_FILE, TODO
    //BuildInfo(std::string buildId, JsonFile *src, const fs::path &dir); // BUILD_TO_BINARY
    BuildInfo(std::string buildId, const JsonFile &src, size_t fileIndex, const fs::path &dir, const BuildInfoContext &infoContext); // BUILD_TO_BINARY
    BuildInfo(std::string buildId, const std::vector<uint8_t> &outData, size_t fileIndex, const fs::path &dir, const BuildInfoContext &infoContext); // BUILD_TO_BINARY
    ~BuildInfo();
    
    //JsonFile *srcFile; // Deprecated!
    std::vector<uint8_t> out;
    
    BuildInfoType get_build_type() const;
    bool build_to_file() const;
    bool build_to_binary() const;
    
    void write_out_to_dstPath();
    void copy_to_dstPath(fs::path srcPath);
    void write_empty_file_to_dstPath();
    
    fs::path get_dstPath() const;
    fs::path get_dst_folder() const;
    fs::path get_dst_filename() const;
    
    //void set_c_context(CContext &cContext);
    //void set_stats(BuildStats &stats);
    //void set_collection(BuildInfoCollection &collection);
    
    fs::path get_path_to_directory() const; 
    
    CContext &get_c_context() const;
    BuildStats &get_stats() const;
    BuildInfoCollection &get_collection() const;
    
    const JsonFile &get_src_json_file() const;
    const BuildInfoContext &get_info_context() const;
    
    std::string get_type() const;
    std::string get_build_id() const;
    size_t get_file_index() const;
    
    bool is_complete() const;
    void done();
    
    void pad_output_data();
    
    void load_structs_into_c_context(std::vector<fs::path> structFilesToLoad);
    void load_enums_into_c_context(std::vector<fs::path> enumsFilesToLoad);
    
private:
    fs::path _dstPath; // Only used for BUILD_TO_FILE
    fs::path _localDirectory;
    
    std::optional<std::reference_wrapper<const JsonFile>> _jsonFile;
    std::optional<std::reference_wrapper<const BuildInfoContext>> _infoContext;
    
    std::string _buildId;
    std::string _type;
    size_t _fileIndex;
    BuildInfoType _buildType;
    bool _complete = false;
};

}