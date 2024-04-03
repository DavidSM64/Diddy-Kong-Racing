#include "buildObjectMap.h"

#include "fileTypes/levelObjectMap.hpp"

#include "helpers/assetsHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/gzipHelper.h"

#include "helpers/c/cStructGltfHelper.h"

BuildObjectMap::BuildObjectMap(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    _preload_c_context();
    
    _transTable = AssetsHelper::get_asset_json(_settings, "ASSET_LEVEL_OBJECT_TRANSLATION_TABLE");
    _objBehaviorToEntryTable = AssetsHelper::get_meta_file(_settings, "objects/obj_beh_to_entry.meta.json");
    
    if(info.srcFile->is_value_null("/objects")) {
        FileHelper::write_empty_file(_info.dstPath, true);
        return;
    }
    
    fs::path gltfPath = info.localDirectory / info.srcFile->get_string("/objects");
    
    GltfFile gltf(gltfPath);
    
    // _calculate_size() also fills the `_objectIdToStructCache` map.
    size_t dataSize = _calculate_size(gltf);
    
    size_t outSize = DataHelper::align8(dataSize + sizeof(LevelObjectMapHeader));
    
    std::vector<uint8_t> out(outSize);
    
    LevelObjectMap *objectMap = reinterpret_cast<LevelObjectMap *>(&out[0]);
    
    // Set number of bytes.
    objectMap->header.fileSize = dataSize;
    uint8_t *bytes = &objectMap->entriesData[0];
    
    int numberOfNodes = gltf.get_node_count();
    
    // Node 0 is the root node, so we want to start at node 1.
    for(int i = 1; i < numberOfNodes; i++) {
        std::string objectBuildId = gltf.get_node_extra<std::string>(i, "id", "");
        
        int id = _transTable->get_index_of_elem_in_array<std::string>("/table", objectBuildId);
        
        DebugHelper::assert_(id >= 0, "(BuildObjectMap::BuildObjectMap) ", objectBuildId, " is not in the level-object translation table!");
        
        CStruct *entryStruct = _objectIdToStructCache[objectBuildId];
        size_t entrySize = _objectIdStructSizeCache[objectBuildId];
        
        // TODO: Increase this limit?
        DebugHelper::assert_(entrySize < 128, "(BuildObjectMap::BuildObjectMap) Entry for ", objectBuildId, " is too big! 127 bytes is the maximum.");
        
        bytes[0] = (id & 0xFF); // First byte is the lower 8 bits of the id.
        bytes[1] = ((id >> 8) << 7) | entrySize; // Upper-most bit is the 9th bit of the id, lower 7 bits is the length.
        
        // Assumption: entryStruct is LevelObjectEntryCommon
        CStruct *entryCommon = entryStruct;
        
        // Check assumption by seeing if the first entry is a LevelObjectEntryCommon
        if(entryStruct->get_entry(0)->type == "LevelObjectEntryCommon") {
            // Assumption was wrong, so fix it!
            entryCommon = _c_context.get_struct("LevelObjectEntryCommon");
        }
        
        _set_obj_position(gltf, bytes, entryCommon, i);
        
        if(entryCommon != entryStruct) {
            for(size_t entry = 0; entry < entryStruct->entry_count(); entry++) {
                CStructEntry *structMember = entryStruct->get_entry(entry);
                CStructGltfHelper::put_gltf_node_extra_into_struct_entry(structMember, gltf, i, bytes);
            }
        }
        
        bytes += entrySize;
    }
    
    if(_settings.debugBuildKeepUncompressed) {
        // Have the uncompressed binary in a seperate directory in the build folder.
        fs::path outUncompressedPath = _settings.pathToBuild / _settings.dkrVersion / "debug/objectMaps" /  (_info.dstPath.stem().string() + ".bin");
        FileHelper::write_binary_file(out, outUncompressedPath, true);
    }
    
    // Note: `out` becomes garbled after this.
    std::vector<uint8_t> compressedOut = GzipHelper::compress_gzip(out);
    
    FileHelper::write_binary_file(compressedOut, _info.dstPath, true);
}

BuildObjectMap::~BuildObjectMap() {
    
}

void BuildObjectMap::_set_obj_position(GltfFile &gltf, uint8_t *bytes, CStruct *entryCommon, int nodeIndex) {
    CStructEntry *memberX = entryCommon->get_entry(2);
    CStructEntry *memberY = entryCommon->get_entry(3);
    CStructEntry *memberZ = entryCommon->get_entry(4);
    
    double scaledX, scaledY, scaledZ;
    gltf.get_node_position(nodeIndex, scaledX, scaledY, scaledZ);
    
    int xPos = _settings.adjust_from_model_scale(scaledX);
    int yPos = _settings.adjust_from_model_scale(scaledY);
    int zPos = _settings.adjust_from_model_scale(scaledZ);
    
    memberX->set_integer_to_data(bytes, xPos);
    memberY->set_integer_to_data(bytes, yPos);
    memberZ->set_integer_to_data(bytes, zPos);
}

size_t BuildObjectMap::_calculate_size(GltfFile &gltf) {
    size_t out = 0;
    
    int numberOfNodes = gltf.get_node_count();
    
    
    
    // Node 0 is the root node, so we want to start at node 1.
    for(int i = 1; i < numberOfNodes; i++) {
        std::string objectBuildId = gltf.get_node_extra<std::string>(i, "id", "");
        
        DebugHelper::assert_(!objectBuildId.empty(), "(BuildObjectMap::_calculate_size) id was not defined in node ", i);
        
        // First check if we have already calcuated the size of this object build id.
        if(_objectIdStructSizeCache.find(objectBuildId) != _objectIdStructSizeCache.end()) {
            out += _objectIdStructSizeCache[objectBuildId];
            continue;
        }
        
        // Get behavior from object id.
        JsonFile *objJson = AssetsHelper::get_asset_json(_settings, "ASSET_OBJECTS", objectBuildId);
        std::string objBehavior = objJson->get_string("/behavior");
        
        DebugHelper::assert_(
            !objBehavior.empty(),
            "(BuildObjectMap::_calculate_size) Object \"", objectBuildId, "\" does not specify a behavior!"
        );
        
        std::string entryStructName = _objBehaviorToEntryTable->get_string("/" + objBehavior);
        DebugHelper::assert_(
            !entryStructName.empty(),
            "(ExtractObjectMap::ExtractObjectMap) The behavior \"", objBehavior, "\" does not specify an entry struct!"
        );
        
        CStruct *entryStruct = _c_context.get_struct(entryStructName);
        
        // Save struct pointer to cache.
        _objectIdToStructCache[objectBuildId] = entryStruct;
        
        size_t byteSize = entryStruct->get_byte_size();
        
        // Save size to cache.
        _objectIdStructSizeCache[objectBuildId] = byteSize;
        
        out += byteSize;
    }
    
    return out;
}

void BuildObjectMap::_preload_c_context() {
    fs::path includeFolder = _settings.pathToRepo / "include/";
    
    // Load all structs from these files.
    fs::path structPaths[] = {
        includeFolder / "level_object_entries.h",
    };
    
    for(fs::path &structPath : structPaths) {
        CStructHelper::load_structs_from_file(&_c_context, structPath);
    }
    
    // Load all enums from these files.
    fs::path enumPaths[] = {
        includeFolder / "enums.h",
        includeFolder / "object_behaviors.h",
    };
    
    for(fs::path &enumPath : enumPaths) {
        CEnumsHelper::load_enums_from_file(&_c_context, enumPath);
    }
}
