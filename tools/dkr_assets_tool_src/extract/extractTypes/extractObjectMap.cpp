#include "extractObjectMap.h"

#include "fileTypes/levelObjectMap.hpp"

#include "helpers/gzipHelper.h"
#include "helpers/assetsHelper.h"
#include "helpers/stringHelper.h"

#include "helpers/c/cStructGltfHelper.h"

ExtractObjectMap::ExtractObjectMap(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Level Object Map", YELLOW_TEXT, _outFilepath);
    
    JsonFile *transTable = AssetsHelper::get_asset_json(_settings, "ASSET_LEVEL_OBJECT_TRANSLATION_TABLE");
    JsonFile *objBehaviorToEntryTable = AssetsHelper::get_meta_file(_settings, "objects/obj_beh_to_entry.meta.json");
    
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_string("/type", "LevelObjectMap");
    
    // Get the compressed data from the ROM.
    std::vector<uint8_t> compressedData;
    _info.get_data_from_rom(compressedData);
    
    if(compressedData.empty()) {
        jsonFile.set_null("/objects");
        jsonFile.save();
        return;
    }
    
    fs::path localGltfPath = _info.get_filename(".gltf");
    fs::path gltfFilepath = _settings.pathToAssets / _info.get_out_filepath(".gltf");
    
    WriteableGltfFile gltfFile("objects");
    
    jsonFile.set_string("/objects", localGltfPath);
    
    // Decompress it
    std::vector<uint8_t> rawBytes = GzipHelper::decompress_gzip(compressedData);
    
    if(_settings.debugExtractKeepUncompressed) {
        // Have the uncompressed binary in a seperate directory in the assets folder.
        fs::path outUncompressedPath = _settings.pathToAssets / "debug/objectMaps" / _info.get_filename(".bin");
        FileHelper::write_binary_file(rawBytes, outUncompressedPath, true);
    }
    
    //DebugHelper::info(rawBytes.size());
    
    // Now we can read it.
    LevelObjectMap *mapData = reinterpret_cast<LevelObjectMap *>(&rawBytes[0]);
    
    size_t offset = sizeof(LevelObjectMapHeader); // Should start at offset 0x10
    size_t end = mapData->header.fileSize + sizeof(LevelObjectMapHeader);
    uint8_t *bytes = &mapData->entriesData[0];
    
    DebugHelper::assert_(offset == 16, "(ExtractObjectMap::ExtractObjectMap) Invalid size for LevelObjectMapHeader: ", offset);
    
    int currentObjectIndex = 0;
    while(offset < end) {
        int id = bytes[0] | ((bytes[1] >> 7) << 8);
        size_t numBytes = (bytes[1] & 0x7F);
        
        DebugHelper::assert_(numBytes >= 8, "(ExtractObjectMap::ExtractObjectMap) Invalid number of bytes for object! offset = ", DebugHelper::to_hex(offset));
        
        std::string objectBuildId = transTable->get_string("/table/" + std::to_string(id));
        
        std::string objectIndex = "/objects/" + std::to_string(currentObjectIndex);
        
        //jsonFile.set_string(objectIndex + "/id", objectBuildId);
        
        // Get the object behavior for this object.
        JsonFile *objJson = AssetsHelper::get_asset_json(_settings, "ASSET_OBJECTS", objectBuildId);
        
        std::string objInternalName = objJson->get_string("/internal-name", "NoName");
        std::string objBehavior = objJson->get_string("/behavior");
        
        DebugHelper::assert_(
            !objBehavior.empty(),
            "(ExtractObjectMap::ExtractObjectMap) Object \"", objectBuildId, "\" does not specify a behavior!"
        );
        
        std::string entryStructName = objBehaviorToEntryTable->get_string("/" + objBehavior);
        DebugHelper::assert_(
            !entryStructName.empty(),
            "(ExtractObjectMap::ExtractObjectMap) The behavior \"", objBehavior, "\" does not specify an entry struct!"
        );
        
        //DebugHelper::info(objectBuildId, "/", objBehavior, "/", entryStructName);
        
        CStruct *entryStruct = _info.c_context->get_struct(entryStructName);
        size_t entryStructByteSize = entryStruct->get_byte_size();
        
        DebugHelper::assert_(
            entryStructByteSize == numBytes,
            "(ExtractObjectMap::ExtractObjectMap) The struct \"", entryStructName, "\" is the incorrect byte size! Is ",
                DebugHelper::to_hex(entryStructByteSize), " bytes, when it should be ", 
                DebugHelper::to_hex(numBytes), " bytes."
        );
        
        // Assumption: entryStruct is LevelObjectEntryCommon
        CStruct *entryCommon = entryStruct;
        
        // Check assumption by seeing if the first entry is a LevelObjectEntryCommon
        if(entryStruct->get_entry(0)->type == "LevelObjectEntryCommon") {
            // Assumption was wrong, so fix it!
            entryCommon = _info.c_context->get_struct("LevelObjectEntryCommon");
        }
        
        int gltfObjNode = gltfFile.new_node(objInternalName);
        
        gltfFile.set_node_extra<std::string>(gltfObjNode, "id", objectBuildId);
        
        _get_obj_position(gltfFile, bytes, entryCommon, gltfObjNode, entryStructName);
        
        if(entryCommon != entryStruct) {
            for(size_t i = 0; i < entryStruct->entry_count(); i++) {
                CStructEntry *structMember = entryStruct->get_entry(i);
                CStructGltfHelper::put_struct_entry_into_gltf_node_extra(_settings, structMember, gltfFile, gltfObjNode, bytes);
            }
        }
        
        currentObjectIndex++;
        bytes += numBytes;
        offset += numBytes;
    }
    
    
    gltfFile.save(gltfFilepath);
    DebugHelper::assert_(FileHelper::path_exists(gltfFilepath), "(ExtractObjectMap::ExtractObjectMap) gltfPath ", gltfFilepath, " did not save!");
    jsonFile.save();
}

ExtractObjectMap::~ExtractObjectMap() {
}

void ExtractObjectMap::_get_obj_position(WriteableGltfFile &gltfFile, uint8_t *bytes, CStruct *entryCommon, int nodeIndex, const std::string &entryStructName) {
    CStructEntry *memberX = entryCommon->get_entry(2);
    CStructEntry *memberY = entryCommon->get_entry(3);
    CStructEntry *memberZ = entryCommon->get_entry(4);
    
    DebugHelper::assert_(memberX != nullptr, "(ExtractObjectMap::_get_obj_position) Could not find \"x\" in struct: ", entryStructName);
    DebugHelper::assert_(memberY != nullptr, "(ExtractObjectMap::_get_obj_position) Could not find \"y\" in struct: ", entryStructName);
    DebugHelper::assert_(memberZ != nullptr, "(ExtractObjectMap::_get_obj_position) Could not find \"z\" in struct: ", entryStructName);
    
    int16_t xPos = memberX->get_integer_from_data(bytes);
    int16_t yPos = memberY->get_integer_from_data(bytes);
    int16_t zPos = memberZ->get_integer_from_data(bytes);
    
    // Scale position based on user input.
    double scaledX = _settings.adjust_to_model_scale(xPos);
    double scaledY = _settings.adjust_to_model_scale(yPos);
    double scaledZ = _settings.adjust_to_model_scale(zPos);
        
    gltfFile.set_node_position(nodeIndex, scaledX, scaledY, scaledZ);
}
