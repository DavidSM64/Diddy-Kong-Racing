#pragma once

#include <string>
#include "extract/extractInfo.h"
#include "misc/settings.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/gltf/gltfHelper.h"
#include "helpers/c/cStructHelper.h"

class ExtractObjectMap {
public:
    ExtractObjectMap(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractObjectMap();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
    
    void _get_obj_position(WriteableGltfFile &gltfFile, uint8_t *bytes, CStruct *entryCommon, int nodeIndex, const std::string &entryStructName);
};
