#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <mutex>

#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cContext.h"

#include "builder/textureCache.h"

namespace DkrAssetsTool {

class BuildInfoCollection;

class BuildInfoContext {
public:
    BuildInfoContext(CContext &cContext, BuildTextureCache &textureCache, BuildInfoCollection &collection);
    
    CContext &get_c_context() const;
    BuildTextureCache &get_texture_cache() const;
    BuildInfoCollection &get_collection() const;
    
    // Used in BuildObjectMap
    void init_obj_beh_to_entry_map(); 
    std::string get_object_entry_from_behavior(std::string objBehavior) const;
    
private:
    std::reference_wrapper<CContext> _cContext;
    std::reference_wrapper<BuildTextureCache> _textureCache;
    std::reference_wrapper<BuildInfoCollection> _collection;
    
    std::unordered_map<std::string, std::string> _objBehaviorToEntry;
};

}