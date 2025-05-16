#include "extractObjectMap.h"

#include "fileTypes/levelObjectMap.hpp"

#include "helpers/gzipHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/stringHelper.h"

#include "misc/globalSettings.h"

#include "helpers/c/cStructGltfHelper.h"

#include "extract/stats.h"

using namespace DkrAssetsTool;

void get_obj_position(WriteableGltfFile &gltfFile, uint8_t *bytes, CStruct *entryCommon, int nodeIndex, const std::string &entryStructName) {
    CStructEntry *memberX = entryCommon->get_entry(2);
    CStructEntry *memberY = entryCommon->get_entry(3);
    CStructEntry *memberZ = entryCommon->get_entry(4);
    
    DebugHelper::assert_(memberX != nullptr, "(ExtractObjectMap::get_obj_position) Could not find \"x\" in struct: ", entryStructName);
    DebugHelper::assert_(memberY != nullptr, "(ExtractObjectMap::get_obj_position) Could not find \"y\" in struct: ", entryStructName);
    DebugHelper::assert_(memberZ != nullptr, "(ExtractObjectMap::get_obj_position) Could not find \"z\" in struct: ", entryStructName);
    
    int16_t xPos = memberX->get_integer_from_data(bytes);
    int16_t yPos = memberY->get_integer_from_data(bytes);
    int16_t zPos = memberZ->get_integer_from_data(bytes);
    
    // Scale position based on user input.
    double scaledX = xPos;//_settings.adjust_to_model_scale(xPos);
    double scaledY = yPos;//_settings.adjust_to_model_scale(yPos);
    double scaledZ = zPos;//_settings.adjust_to_model_scale(zPos);
        
    gltfFile.set_node_position(nodeIndex, scaledX, scaledY, scaledZ);
}


void ExtractObjectMap::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Level Object Map", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    const ExtractStats &stats = info.get_stats();
    const AssetExtractConfig &config = info.get_config();
    
    const JsonFile &transTable = stats.get_json("ASSET_LEVEL_OBJECT_TRANSLATION_TABLE");
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_string("/type", "LevelObjectMap");
    
    // Get the compressed data from the ROM.
    std::vector<uint8_t> compressedData;
    info.get_data_from_rom(compressedData);
    
    if(compressedData.empty()) {
        jsonFile.set_null("/objects");
        jsonFile.save();
        return;
    }
    
    fs::path localGltfPath = info.get_filename(".gltf");
    fs::path gltfFilepath = GlobalSettings::get_decomp_path_to_vanilla_assets() / info.get_out_filepath(".gltf");
    
    WriteableGltfFile gltfFile("objects");
    
    jsonFile.set_string("/objects", localGltfPath);
    
    // Decompress it
    std::vector<uint8_t> rawBytes = GzipHelper::decompress_gzip(compressedData);
    
    /*
    if(_settings.debugExtractKeepUncompressed) {
        // Have the uncompressed binary in a seperate directory in the assets folder.
        fs::path outUncompressedPath = GlobalSettings::get_decomp_path_to_vanilla_assets() / "debug/objectMaps" / info.get_filename(".bin");
        FileHelper::write_binary_file(rawBytes, outUncompressedPath, true);
    }
    */
    //DebugHelper::info(rawBytes.size());
    
    // Now we can read it.
    LevelObjectMap *mapData = reinterpret_cast<LevelObjectMap *>(&rawBytes[0]);
    
    size_t offset = sizeof(LevelObjectMapHeader); // Should start at offset 0x10
    size_t end = mapData->header.fileSize + sizeof(LevelObjectMapHeader);
    uint8_t *bytes = &mapData->entriesData[0];
    
    DebugHelper::assert_(offset == 16, "(ExtractObjectMap::extract) Invalid size for LevelObjectMapHeader: ", offset);
    
    int currentObjectIndex = 0;
    while(offset < end) {
        int id = bytes[0] | ((bytes[1] >> 7) << 8);
        size_t numBytes = (bytes[1] & 0x7F);
        
        DebugHelper::assert_(numBytes >= 8, "(ExtractObjectMap::extract) Invalid number of bytes for object! offset = ", DebugHelper::to_hex(offset));
        
        std::string objectBuildId = transTable.get_string("/table/" + std::to_string(id));
        
        std::string objectIndex = "/objects/" + std::to_string(currentObjectIndex);
        
        //jsonFile.set_string(objectIndex + "/id", objectBuildId);
        
        // Get the object behavior for this object.
        const JsonFile &objJson = stats.get_json("ASSET_OBJECTS", objectBuildId);
        
        std::string objInternalName = objJson.get_string("/internal-name", "NoName");
        std::string objBehavior = objJson.get_string("/behavior");
        
        DebugHelper::assert_(
            !objBehavior.empty(),
            "(ExtractObjectMap::extract) Object \"", objectBuildId, "\" does not specify a behavior!"
        );
        
        std::string entryStructName = config.get_object_entry_from_behavior(objBehavior);
        
        CStruct *entryStruct = info.get_c_context().get_struct(entryStructName);
        size_t entryStructByteSize = entryStruct->get_byte_size();
        
        DebugHelper::assert_(
            entryStructByteSize == numBytes,
            "(ExtractObjectMap::extract) The struct \"", entryStructName, "\" is the incorrect byte size! Is ",
                DebugHelper::to_hex(entryStructByteSize), " bytes, when it should be ", 
                DebugHelper::to_hex(numBytes), " bytes."
        );
        
        // Assumption: entryStruct is LevelObjectEntryCommon
        CStruct *entryCommon = entryStruct;
        
        // Check assumption by seeing if the first entry is a LevelObjectEntryCommon
        if(entryStruct->get_entry(0)->type == "LevelObjectEntryCommon") {
            // Assumption was wrong, so fix it!
            entryCommon = info.get_c_context().get_struct("LevelObjectEntryCommon");
        }
        
        int gltfObjNode = gltfFile.new_node(objInternalName);
        
        gltfFile.set_node_extra<std::string>(gltfObjNode, "id", objectBuildId);
        
        get_obj_position(gltfFile, bytes, entryCommon, gltfObjNode, entryStructName);
        
        if(entryCommon != entryStruct) {
            for(size_t i = 0; i < entryStruct->entry_count(); i++) {
                CStructEntry *structMember = entryStruct->get_entry(i);
                CStructGltfHelper::put_struct_entry_into_gltf_node_extra(structMember, gltfFile, gltfObjNode, bytes);
            }
        }
        
        currentObjectIndex++;
        bytes += numBytes;
        offset += numBytes;
    }
    
    gltfFile.save(gltfFilepath);
    DebugHelper::assert_(FileHelper::path_exists(gltfFilepath), "(ExtractObjectMap::extract) gltfPath ", gltfFilepath, " did not save!");
    jsonFile.save();
}
