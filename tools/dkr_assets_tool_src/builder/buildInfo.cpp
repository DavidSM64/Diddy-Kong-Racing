#include "buildInfo.h"

#include "misc/globalSettings.h"
#include "helpers/c/cContext.h"
#include "helpers/jsonHelper.h"

using namespace DkrAssetsTool;

/**************************************************************************/

BuildInfoContext::BuildInfoContext(CContext &cContext, BuildStats &stats, BuildInfoCollection &collection) 
    : _cContext(cContext), _stats(stats), _collection(collection) {}

CContext &BuildInfoContext::get_c_context() const {
    return _cContext;
}

BuildStats &BuildInfoContext::get_stats() const {
    return _stats;
}

BuildInfoCollection &BuildInfoContext::get_collection() const {
    return _collection;
}

void BuildInfoContext::init_obj_beh_to_entry_map() {
    if(!_objBehaviorToEntry.empty()) {
        return; // Don't redo this if the map is already filled!
    }
    
    // TODO: This was copy-pasted from extract/config.cpp; need to refactor to not require the config file.
    
    fs::path pathToConfig = GlobalSettings::get_decomp_path("tools", "tools/") / "dkr_assets_tool_extract.json";
    auto tryGetConfigFile = JsonHelper::get_file(pathToConfig);
    DebugHelper::assert_(tryGetConfigFile.has_value(), 
        "(BuildInfoContext::init_obj_beh_to_entry_map) Could not find the config file at: ", pathToConfig);
    JsonFile &configJson = tryGetConfigFile.value();
    
    CContext &cContext = get_c_context();
    
    CEnum *objBehaviors = cContext.get_enum("ObjectBehaviours");
    
    DebugHelper::assert_(objBehaviors != nullptr, 
        "(BuildInfoContext::init_obj_beh_to_entry_map) The enum ObjectBehaviours could not be loaded!");
    
    std::vector<std::string> defaultObjEntriesOrder;
    configJson.get_array<std::string>("/misc/default-object-entries-order", defaultObjEntriesOrder);
    
    for(int i = 0; i < 128; i++) {
        std::string symbol;
        DebugHelper::assert_(objBehaviors->get_symbol_of_value(i, symbol),
            "(BuildInfoContext::init_obj_beh_to_entry_map) Could not get a symbol for the value ", i, " in the ObjectBehaviors enum.");
        
        CStruct *entryStruct = cContext.get_struct(defaultObjEntriesOrder[i]);
        DebugHelper::assert_(entryStruct != nullptr, 
            "(BuildInfoContext::init_obj_beh_to_entry_map) Could not find struct \"", defaultObjEntriesOrder[i], "\"");
        
        _objBehaviorToEntry[symbol] = defaultObjEntriesOrder[i];
    }
}

std::string BuildInfoContext::get_object_entry_from_behavior(std::string objBehavior) const {
    DebugHelper::assert_(_objBehaviorToEntry.find(objBehavior) != _objBehaviorToEntry.end(),
        "(AssetExtractConfig::get_object_entry_from_behavior) ", objBehavior, 
        " was not in the _objBehaviorToEntry map!");
    
    return _objBehaviorToEntry.at(objBehavior);
}

/**************************************************************************/

BuildInfo::BuildInfo() {
    DebugHelper::error("Must not initalize empty build info.");
}
/*
BuildInfo::BuildInfo(JsonFile *src, const fs::path &dst, const fs::path &dir) 
    : srcFile(src), dstPath(dst), localDirectory(dir) {
    _buildType = BUILD_TO_FILE;
}*/

/*
BuildInfo::BuildInfo(JsonFile *src, const fs::path &dir) 
    : srcFile(src), dstPath(""), localDirectory(dir) {
    _buildType = BUILD_TO_BINARY;
}
*/

BuildInfo::BuildInfo(std::string buildId, const JsonFile &src, size_t fileIndex, const fs::path &dir, const BuildInfoContext &infoContext) 
    : _dstPath(""), _localDirectory(dir), _jsonFile(src), _infoContext(infoContext), _buildId(buildId), _fileIndex(fileIndex) {
    _buildType = BUILD_TO_BINARY;
    const JsonFile &jsonFile = get_src_json_file();
    _type = jsonFile.get_string("/type", "NoType");
}

BuildInfo::BuildInfo(std::string buildId, const std::vector<uint8_t> &outData, size_t fileIndex, const fs::path &dir, const BuildInfoContext &infoContext) 
    : out(outData), _dstPath(""), _localDirectory(dir), _jsonFile(std::nullopt), _infoContext(infoContext), _buildId(buildId), _type("Binary"), _fileIndex(fileIndex) {
    _buildType = BUILD_TO_BINARY;
}

BuildInfo::~BuildInfo() {
}

BuildInfoType BuildInfo::get_build_type() const {
    return _buildType;
}

bool BuildInfo::build_to_file() const {
    return _buildType == BUILD_TO_FILE;
}

bool BuildInfo::build_to_binary() const {
    return _buildType == BUILD_TO_BINARY;
}
    
void BuildInfo::write_out_to_dstPath() {
    FileHelper::write_binary_file(out, _dstPath, true);
}
    
void BuildInfo::copy_to_dstPath(fs::path srcPath) {
    FileHelper::copy(srcPath, _dstPath);
}

void BuildInfo::write_empty_file_to_dstPath() {
    FileHelper::write_empty_file(_dstPath, true);
}

fs::path BuildInfo::get_dstPath() const {
    return _dstPath;
}

fs::path BuildInfo::get_dst_folder() const {
    return _dstPath.parent_path();
}

fs::path BuildInfo::get_dst_filename() const {
    return _dstPath.filename();
}

fs::path BuildInfo::get_path_to_directory() const {
    return GlobalSettings::get_decomp_path_to_output_assets() / _localDirectory;
}
    
CContext &BuildInfo::get_c_context() const {
    const BuildInfoContext &infoContext = _infoContext.value();
    return infoContext.get_c_context();
}
    
BuildStats &BuildInfo::get_stats() const {
    const BuildInfoContext &infoContext = _infoContext.value();
    return infoContext.get_stats();
}
    
BuildInfoCollection &BuildInfo::get_collection() const {
    const BuildInfoContext &infoContext = _infoContext.value();
    return infoContext.get_collection();
}

const JsonFile &BuildInfo::get_src_json_file() const {
    DebugHelper::assert_(_jsonFile.has_value(), 
        "(BuildInfo::get_src_json_file) _jsonFile is null! build id was \"", _buildId, "\"");
    return _jsonFile.value();
}

const BuildInfoContext &BuildInfo::get_info_context() const {
    DebugHelper::assert_(_infoContext.has_value(), 
        "(BuildInfo::get_info_context) _infoContext is null! build id was \"", _buildId, "\"");
    return _infoContext.value();
}

std::string BuildInfo::get_type() const {
    return _type;
}

std::string BuildInfo::get_build_id() const {
    return _buildId;
}

size_t BuildInfo::get_file_index() const {
    return _fileIndex;
}

bool BuildInfo::is_complete() const {
    return _complete;
}

void BuildInfo::done() {
    _complete = true;
    //pad_output_data();
}
    
void BuildInfo::pad_output_data() {
    while((out.size() % 8) != 0) {
        out.push_back(0);
    }
}
    
void BuildInfo::load_structs_into_c_context(std::vector<fs::path> structFilesToLoad) {
    fs::path includeFolder = GlobalSettings::get_decomp_path("include_subpath", "include/");
    
    DebugHelper::assert_(!includeFolder.empty(),
        "(BuildInfo::load_structs_into_c_context) Could not find the include folder!");
    
    CContext &cContext = get_c_context();
    
    for(fs::path &structPath : structFilesToLoad) {
        CStructHelper::load_structs_from_file(cContext, includeFolder / structPath);
    }
}

void BuildInfo::load_enums_into_c_context(std::vector<fs::path> enumFilesToLoad) {
    fs::path includeFolder = GlobalSettings::get_decomp_path("include_subpath", "include/");
    
    DebugHelper::assert_(!includeFolder.empty(),
        "(BuildInfo::load_enums_into_c_context) Could not find the include folder!");
    
    CContext &cContext = get_c_context();
    
    for(fs::path &enumPath : enumFilesToLoad) {
        CEnumsHelper::load_enums_from_file(cContext, includeFolder / enumPath);
    }
}
