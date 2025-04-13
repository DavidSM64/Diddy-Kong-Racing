#pragma once

#include <unordered_map>

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/gltf/gltfHelper.h"
#include "helpers/c/cContext.h"
#include "helpers/c/cStructHelper.h"

namespace DkrAssetsTool {
class BuildObjectMap {
public:
    BuildObjectMap(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildObjectMap();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
    CContext _c_context; // C Code context. (For loading enums & structs)
    
    // Both are populated in _calculate_size()
    std::unordered_map<std::string, size_t> _objectIdStructSizeCache;
    std::unordered_map<std::string, CStruct*> _objectIdToStructCache;
    
    JsonFile *_transTable;
    JsonFile *_objBehaviorToEntryTable;
    
    void _set_obj_position(GltfFileNode *objNode, uint8_t *bytes, CStruct *entryCommon, int nodeIndex);
    
    size_t _calculate_size(GltfFileNode *objectsNode);
    void _preload_c_context();
};
}
