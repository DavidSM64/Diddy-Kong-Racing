#pragma once

#include <optional>

#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "libs/bytes_view.hpp"
#include "helpers/c/cContext.h"

namespace DkrAssetsTool {

class AssetExtractConfig {
public:
    AssetExtractConfig();
    ~AssetExtractConfig();
    
    const JsonFile &get_config_json() const;
    const BytesView &get_rom_assets_view() const;
    
    bool is_input_file_valid(fs::path baseromPath) const;
    void load_input_file(fs::path baseromPath);
    
    size_t number_of_sections() const;
    
    template <typename T>
    T get(std::string ptr, T defaultValue) const {
        const JsonFile& configJson = get_config_json();
        try {
            return std::any_cast<T>(configJson.get_any(ptr));
        } catch (std::bad_any_cast &err) {
        }
        return defaultValue;
    }
    
    // Returns the index into `/sections` array of the table associated with this build id. 
    // Returns std::nullopt if no table was found.
    std::optional<size_t> get_section_table_index(std::string buildId) const;
    
    // Returns the indices to the files given a sha1 hash. Multiple files may contain the same hash.
    std::vector<size_t> get_file_indices_from_sha1(std::string sha1Hash) const;
    
    std::string get_object_entry_from_behavior(std::string objBehavior) const;
    
    // initalizes _objBehaviorToEntry
    void init_obj_beh_to_entry_map(CContext &cContext);
    
private:
    std::optional<std::reference_wrapper<JsonFile>> _configJson;
    
    std::vector<uint8_t> _rom;
    std::optional<BytesView> _romAssetsView;
    
    std::unordered_map<std::string, std::vector<size_t>> _sha1HashToFileIndex;
    std::unordered_map<std::string, std::string> _objBehaviorToEntry;
    
};

}
