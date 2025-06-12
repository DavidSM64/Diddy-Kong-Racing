#include "buildObjectMap.h"

#include "fileTypes/levelObjectMap.hpp"

#include "helpers/assetsHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/gzipHelper.h"

#include "helpers/c/cStructGltfHelper.h"

#include "builder/buildInfoCollection.h"

using namespace DkrAssetsTool;

// Both are populated in calculate_size()
std::unordered_map<std::string, size_t> _objectIdStructSizeCache;
std::unordered_map<std::string, CStruct*> _objectIdToStructCache;

void search_for_objects_node() {
    
}

void set_obj_position(tinygltf::Node &objNode, uint8_t *bytes, CStruct *entryCommon) {
    CStructEntry *memberX = entryCommon->get_entry(2);
    CStructEntry *memberY = entryCommon->get_entry(3);
    CStructEntry *memberZ = entryCommon->get_entry(4);
    
    //double scaledX, scaledY, scaledZ;
    //objNode->get_position(scaledX, scaledY, scaledZ);
    Vec3f position = GltfHelper::get_node_position(objNode);
    
    int xPos = position.x; //_settings.adjust_from_model_scale(scaledX);
    int yPos = position.y; //_settings.adjust_from_model_scale(scaledY);
    int zPos = position.z; //_settings.adjust_from_model_scale(scaledZ);
    
    memberX->set_integer_to_data(bytes, xPos);
    memberY->set_integer_to_data(bytes, yPos);
    memberZ->set_integer_to_data(bytes, zPos);
}

size_t calculate_size(GltfFile &gltf, tinygltf::Node &objectsNode, BuildInfo &info, CContext &cContext, std::mutex &globalMutex) {
    const BuildInfoContext &infoContext = info.get_info_context();
    
    size_t out = 0;
    
    size_t numberOfChildNodes = objectsNode.children.size();
    
    globalMutex.lock();
    
    for(size_t i = 0; i < numberOfChildNodes; i++) {
        tinygltf::Node &objNode = gltf.get_node(objectsNode.children[i]);
        std::string objectBuildId = GltfHelper::get_extra<std::string>(objNode.extras, "/id", "");
        
        DebugHelper::assert_(!objectBuildId.empty(), 
            "(calculate_size) id was not defined in node: ", objNode.name);
        
        // First check if we have already calcuated the size of this object build id.
        if(_objectIdStructSizeCache.find(objectBuildId) != _objectIdStructSizeCache.end()) {
            out += _objectIdStructSizeCache[objectBuildId];
            continue;
        }
        
        // Get behavior from object id.
        JsonFile &objJson = AssetsHelper::get_asset_json("ASSET_OBJECTS", objectBuildId);
        std::string objBehavior = objJson.get_string("/behavior");
        
        DebugHelper::assert_(
            !objBehavior.empty(),
            "(calculate_size) Object \"", objectBuildId, "\" does not specify a behavior!"
        );
        
        std::string entryStructName = infoContext.get_object_entry_from_behavior(objBehavior);
        DebugHelper::assert_(
            !entryStructName.empty(),
            "(calculate_size) The behavior \"", objBehavior, "\" does not specify an entry struct!"
        );
        
        CStruct *entryStruct = cContext.get_struct(entryStructName);
        
        // Save struct pointer to cache.
        _objectIdToStructCache[objectBuildId] = entryStruct;
        
        size_t byteSize = entryStruct->get_byte_size();
        
        // Save size to cache.
        _objectIdStructSizeCache[objectBuildId] = byteSize;
        
        out += byteSize;
    }
    
    globalMutex.unlock();
    return out;
}

void BuildObjectMap::build(BuildInfo &info) {
    std::mutex &globalMutex = info.get_collection().get_global_mutex();
    
    if(info.build_to_file()) {
        info.load_enums_into_c_context({ "enums.h", "object_behaviors.h" });
        info.load_structs_into_c_context({ "level_object_entries.h" });
    }
    
    CContext &cContext = info.get_c_context();
    
    JsonFile &transTable = AssetsHelper::get_asset_json("ASSET_LEVEL_OBJECT_TRANSLATION_TABLE");
    
    const JsonFile &jsonFile = info.get_src_json_file();
    
    if(jsonFile.is_value_null("/objects")) {
        if(info.build_to_file()) {
            info.write_empty_file_to_dstPath();
        }
        return;
    }
    
    fs::path gltfPath = info.get_path_to_directory() / jsonFile.get_string("/objects");
    
    GltfFile gltf(gltfPath);
    
    int objectsNodeIndex;
    DebugHelper::assert_(gltf.search_for_node_by_name("objects", objectsNodeIndex),
        "(BuildObjectMap::build) .glTF file does not contain a node named \"objects\"!");
        
    tinygltf::Node &objectsNode = gltf.get_node(objectsNodeIndex);
    
    // calculate_size() also fills the `_objectIdToStructCache` map.
    size_t dataSize = calculate_size(gltf, objectsNode, info, cContext, globalMutex);
    
    size_t outSize = DataHelper::align8(dataSize + sizeof(LevelObjectMapHeader));
    
    info.out.resize(outSize);
    
    LevelObjectMap *objectMap = reinterpret_cast<LevelObjectMap *>(&info.out[0]);
    
    // Set number of bytes.
    objectMap->header.fileSize = dataSize;
    uint8_t *bytes = &objectMap->entriesData[0];
    
    int numberOfChildNodes = objectsNode.children.size();
    
    for(int i = 0; i < numberOfChildNodes; i++) {
        tinygltf::Node &objNode = gltf.get_node(objectsNode.children[i]);
        
        std::string objectBuildId = GltfHelper::get_extra<std::string>(objNode.extras, "/id", "");
        
        DebugHelper::assert_(!objectBuildId.empty(), "(BuildObjectMap::build) Child node ", i,
            " does not have id defined!");
        
        int id = transTable.get_index_of_elem_in_array<std::string>("/table", objectBuildId);
        
        DebugHelper::assert_(id >= 0, "(BuildObjectMap::build) ", objectBuildId, " is not in the level-object translation table!");
        
        CStruct *entryStruct = _objectIdToStructCache[objectBuildId];
        size_t entrySize = _objectIdStructSizeCache[objectBuildId];
        
        // TODO: Increase this limit?
        DebugHelper::assert_(entrySize < 128, "(BuildObjectMap::build) Entry for ", objectBuildId, " is too big! 127 bytes is the maximum.");
        
        bytes[0] = (id & 0xFF); // First byte is the lower 8 bits of the id.
        bytes[1] = ((id >> 8) << 7) | entrySize; // Upper-most bit is the 9th bit of the id, lower 7 bits is the length.
        
        // Assumption: entryStruct is LevelObjectEntryCommon
        CStruct *entryCommon = entryStruct;
        
        // Check assumption by seeing if the first entry is a LevelObjectEntryCommon
        if(entryStruct->get_entry(0)->type == "LevelObjectEntryCommon") {
            // Assumption was wrong, so fix it!
            entryCommon = cContext.get_struct("LevelObjectEntryCommon");
        }
        
        set_obj_position(objNode, bytes, entryCommon);
        
        if(entryCommon != entryStruct) {
            for(size_t entry = 0; entry < entryStruct->entry_count(); entry++) {
                globalMutex.lock();
                CStructEntry *structMember = entryStruct->get_entry(entry);
                CStructGltfHelper::put_gltf_node_extra_into_struct_entry(structMember, objNode, bytes);
                globalMutex.unlock();
            }
        }
        
        bytes += entrySize;
    }
    /*
    // TODO: Use new GlobalSettings
    if(_settings.debugBuildKeepUncompressed) {
        // Have the uncompressed binary in a seperate directory in the build folder.
        fs::path outUncompressedPath = _settings.pathToBuild / "debug/objectMaps" /  (_info.dstPath.stem().string() + ".bin");
        FileHelper::write_binary_file(out, outUncompressedPath, true);
    }
    */
    
    info.out = GzipHelper::compress_gzip(info.out);
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
    
}
