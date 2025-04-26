#include "config.h"

#include "misc/globalSettings.h"
#include "helpers/c/cContext.h"

using namespace DkrAssetsTool;

AssetExtractConfig::AssetExtractConfig() {
    fs::path configPath = GlobalSettings::get_decomp_path("extract_config", "tools/dkr_assets_tool_extract.json");
    
    _configJson = JsonHelper::get_file(configPath);
    
    DebugHelper::assert_(_configJson.has_value(),
        "(AssetExtractConfig::AssetExtractConfig) Could not find dkr_assets_tool_extract.json");
        
    const JsonFile &jsonFile = get_config_json();
    
    // Doing this for performance reasons. Turns the array of files into a hashmap with the sha1 property being the key.
    // Multiple files will have the same sha1 hash (duplicate textures mostly), so that is why I'm using std::vector<size_t> as the map's value.
    _sha1HashToFileIndex = jsonFile.create_map_of_indices_from_property_value<std::string>("/files", "sha1");
}

AssetExtractConfig::~AssetExtractConfig() {
}

const JsonFile &AssetExtractConfig::get_config_json() const {
    return _configJson.value();
}

const BytesView &AssetExtractConfig::get_rom_assets_view() const {
    DebugHelper::assert_(_romAssetsView.has_value(),
        "(AssetExtractConfig::get_rom_assets_view) ROM file has not been loaded yet!");
    return _romAssetsView.value();
}

bool AssetExtractConfig::is_input_file_valid(fs::path baseromPath) const {
    const JsonFile &configJson = get_config_json();
    
    std::string fileSha1 = FileHelper::get_sha1_of_file(baseromPath);
    
    std::optional<size_t> tryFindEntryFromSha1 = configJson.get_index_of_object_that_has_property<std::string>("/inputs-supported", "sha1", fileSha1);
    
    if(!tryFindEntryFromSha1.has_value()) {
        return false; // File was not in the "inputs-supported" array.
    }
    
    size_t entryIndex = tryFindEntryFromSha1.value();
    
    std::string dkrVersion = GlobalSettings::get_dkr_version();
    std::string fileDkrVersion = configJson.get_string_lowercase("/inputs-supported/" + std::to_string(entryIndex) + "/dkr_version");
    
    if(dkrVersion != fileDkrVersion) {
        return false; // DKR version of file was not correct.
    }
    
    return true;
}

void AssetExtractConfig::load_input_file(fs::path baseromPath) {
    const JsonFile &configJson = get_config_json();
    
    std::string fileSha1 = FileHelper::get_sha1_of_file(baseromPath);
    std::optional<size_t> tryFindEntryFromSha1 = configJson.get_index_of_object_that_has_property<std::string>("/inputs-supported", "sha1", fileSha1);
    DebugHelper::assert_(tryFindEntryFromSha1.has_value(),
        "(AssetExtractConfig::load_input_file) Trying to load an invalid ROM file!");
    size_t entryIndex = tryFindEntryFromSha1.value();
    std::string entryPtr = "/inputs-supported/" + std::to_string(entryIndex);
    
    _rom = FileHelper::read_binary_file(baseromPath);
    
    size_t assetsStart = configJson.get_int(entryPtr + "/assets");
    size_t assetsEnd = configJson.get_int(entryPtr + "/assets_end");
    
    _romAssetsView = BytesView(_rom, assetsStart, assetsEnd - assetsStart);
}
    
size_t AssetExtractConfig::number_of_sections() const {
    return get_config_json().length_of_array("/sections");
}

std::optional<size_t> AssetExtractConfig::get_section_table_index(std::string buildId) const {
    const JsonFile &configJson = get_config_json();
    return configJson.get_index_of_object_that_has_property<std::string>("/sections", "for", buildId);
}

std::optional<size_t> AssetExtractConfig::get_file_index_from_sha1(std::string sha1Hash, size_t foundSoFar) const {
    if(_sha1HashToFileIndex.find(sha1Hash) == _sha1HashToFileIndex.end()) {
        return std::nullopt; // File not found in "files" array.
    }
    size_t numberOfFilesForHash = _sha1HashToFileIndex.at(sha1Hash).size();
    DebugHelper::assert_(foundSoFar < numberOfFilesForHash, 
        "(AssetExtractConfig::get_file_index_from_sha1) foundSoFar out of bounds! ",
        "foundSoFar = ", foundSoFar, ", numberOfFilesForHash = ", numberOfFilesForHash);
    return _sha1HashToFileIndex.at(sha1Hash).at(foundSoFar);
}

std::string AssetExtractConfig::get_object_entry_from_behavior(std::string objBehavior) const {
    DebugHelper::assert_(_objBehaviorToEntry.find(objBehavior) != _objBehaviorToEntry.end(),
        "(AssetExtractConfig::get_object_entry_from_behavior) ", objBehavior, 
        " was not in the _objBehaviorToEntry map!");
    
    return _objBehaviorToEntry.at(objBehavior);
}

void AssetExtractConfig::init_obj_beh_to_entry_map(const CContext &cContext) {
    const JsonFile &configJson = get_config_json();
    CEnum *objBehaviors = cContext.get_enum("ObjectBehaviours");
    
    std::vector<std::string> defaultObjEntriesOrder;
    configJson.get_array<std::string>("/misc/default-object-entries-order", defaultObjEntriesOrder);
    
    for(int i = 0; i < 128; i++) {
        std::string symbol;
        DebugHelper::assert_(objBehaviors->get_symbol_of_value(i, symbol),
            "(generate_obj_behavior_to_entry_json_file) Could not get a symbol for the value ", i, " in the ObjectBehaviors enum.");
        
        CStruct *entryStruct = cContext.get_struct(defaultObjEntriesOrder[i]);
        DebugHelper::assert_(entryStruct != nullptr, 
            "(generate_obj_behavior_to_entry_json_file) Could not find struct \"", defaultObjEntriesOrder[i], "\"");
        
        _objBehaviorToEntry[symbol] = defaultObjEntriesOrder[i];
    }
}
