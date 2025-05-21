#include "buildInfo.h"

#include "misc/globalSettings.h"
#include "helpers/c/cContext.h"
#include "helpers/jsonHelper.h"

using namespace DkrAssetsTool;

BuildInfoContext::BuildInfoContext(CContext &cContext, BuildTextureCache &textureCache, BuildInfoCollection &collection) 
    : _cContext(cContext), _textureCache(textureCache), _collection(collection) {}

CContext &BuildInfoContext::get_c_context() const {
    return _cContext;
}

BuildTextureCache &BuildInfoContext::get_texture_cache() const {
    return _textureCache;
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
