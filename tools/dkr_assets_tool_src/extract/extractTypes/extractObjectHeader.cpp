#include "extractObjectHeader.h"

using namespace DkrAssetsTool;

#include "helpers/stringHelper.h"
#include "helpers/assetsHelper.h"
#include "helpers/dataHelper.h"

#include "fileTypes/objectHeader.hpp"

#include <sstream>

ExtractObjectHeader::ExtractObjectHeader(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    
    DebugHelper::info_custom("Extracting Object", YELLOW_TEXT, _outFilepath);
    
    std::vector<uint8_t> rawBytes;
    _info.get_data_from_rom(rawBytes);
    
    ObjectHeader *objectHeader = reinterpret_cast<ObjectHeader *>(&rawBytes[0]);
    
    //DebugHelper::info(objectHeader->internalName);
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_string("/type", "ObjectHeader");
    
    CEnum *objBehaviors = _info.c_context->get_enum("ObjectBehaviours");
    
    int behaviorId = objectHeader->behaviorId;
    
    // Behavior
    if(behaviorId >= 0) {
        std::string objBehaviorStr;
        DebugHelper::assert(objBehaviors->get_symbol_of_value(behaviorId, objBehaviorStr), 
            "(ExtractObjectHeader::ExtractObjectHeader) Could not find a symbol for the behavior id: ", behaviorId);
        jsonFile.set_string("/behavior", objBehaviorStr);
    } else {
        jsonFile.set_null("/behavior");
    }
    
    // Model Type
    std::string modelTypeName = "ObjectModelType";
    std::string modelType = _info.c_context->get_symbol_of_enum_int(modelTypeName, objectHeader->modelType);
    jsonFile.set_string("/model-type", modelType);
    
    // Flags
    _flags_to_string(jsonFile, objectHeader->flags);
    
    // Internal Name
    jsonFile.set_string("/internal-name", objectHeader->internalName);
    
    // Floats
    jsonFile.set_float("/shadow-scale", objectHeader->shadowScale);
    jsonFile.set_float("/scale", objectHeader->scale);
    jsonFile.set_float("/shade-brightness", objectHeader->shadeBrightness);
    jsonFile.set_float("/shade-ambient", objectHeader->shadeAmbient);
    
    // Unknowns
    jsonFile.set_int("/unknown/unk0", objectHeader->unk0);
    jsonFile.set_float("/unknown/unk8", objectHeader->unk8);
    jsonFile.set_int("/unknown/unk34", objectHeader->unk34);
    jsonFile.set_int("/unknown/unk38", objectHeader->unk38);
    jsonFile.set_int("/unknown/unk3A", objectHeader->unk3A);
    jsonFile.set_int("/unknown/unk3B", objectHeader->unk3B);
    jsonFile.set_int("/unknown/unk3C", objectHeader->unk3C);
    jsonFile.set_int("/unknown/unk3D", objectHeader->unk3D);
    jsonFile.set_int("/unknown/unk42", objectHeader->unk42);
    jsonFile.set_int("/unknown/unk44", objectHeader->unk44);
    jsonFile.set_int("/unknown/unk46", objectHeader->unk46);
    jsonFile.set_int("/unknown/unk48", objectHeader->unk48);
    jsonFile.set_int("/unknown/unk4A", objectHeader->unk4A);
    jsonFile.set_int("/unknown/unk4C", objectHeader->unk4C);
    jsonFile.set_int("/unknown/unk50", objectHeader->unk50);
    jsonFile.set_int("/unknown/unk52", objectHeader->unk52);
    //jsonFile.set_int("/unknown/unk56", objectHeader->unk56); // vehiclePartIds count.
    //jsonFile.set_int("/unknown/unk57", objectHeader->unk57); // particle count.
    jsonFile.set_int("/unknown/unk58", objectHeader->unk58);
    jsonFile.set_int("/unknown/unk59", objectHeader->unk59);
    jsonFile.set_int("/unknown/unk5B", objectHeader->unk5B);
    jsonFile.set_int("/unknown/unk5C", objectHeader->unk5C);
    jsonFile.set_int("/unknown/unk5D", objectHeader->unk5D);
    jsonFile.set_int("/unknown/unk5E", objectHeader->unk5E);
    jsonFile.set_int("/unknown/unk5F", objectHeader->unk5F);
    jsonFile.set_int("/unknown/unk70", objectHeader->unk70);
    jsonFile.set_int("/unknown/unk71", objectHeader->unk71);
    jsonFile.set_int("/unknown/unk72", objectHeader->unk72);
    jsonFile.set_int("/unknown/unk73", objectHeader->unk73);
    jsonFile.set_int("/unknown/unk74", objectHeader->unk74);
    jsonFile.set_int("/unknown/unk75", objectHeader->unk75);
    jsonFile.set_int("/unknown/unk76", objectHeader->unk76);
    jsonFile.set_int("/unknown/unk77", objectHeader->unk77);
    
    // Other
    jsonFile.set_int("/shadow-group", objectHeader->shadowGroup);
    jsonFile.set_int("/water-effect-group", objectHeader->waterEffectGroup);
    jsonFile.set_int("/shade-angle-y", objectHeader->shadeAngleY);
    jsonFile.set_int("/shade-angle-z", objectHeader->shadeAngleZ);
    jsonFile.set_int("/draw-distance", objectHeader->drawDistance);
    
    // Always zero?
    //jsonFile.set_int("/num-light-sources", objectHeader->numLightSources);
    
    be_int32_t *modelIds = reinterpret_cast<be_int32_t *>(&rawBytes[objectHeader->modelIds]);
    be_int32_t *vehiclePartIds = reinterpret_cast<be_int32_t *>(&rawBytes[objectHeader->vehiclePartIds]);
    uint8_t *vehiclePartIndices = reinterpret_cast<uint8_t *>(&rawBytes[objectHeader->vehiclePartIndices]);
    ObjectHeaderParticleData *particles = reinterpret_cast<ObjectHeaderParticleData *>(&rawBytes[objectHeader->objectParticles]);
                        
    for(int i = 0; i < objectHeader->numberOfModelIds; i++) {
        std::string modelBuildId;
        switch(objectHeader->modelType) {
            case OBJECT_MODEL_TYPE_3D_MODEL:
                modelBuildId = AssetsHelper::get_build_id_of_index(_settings, "ASSET_OBJECT_MODELS", modelIds[i]);
                break;
            case OBJECT_MODEL_TYPE_MISC:
                modelBuildId = AssetsHelper::get_build_id_of_index(_settings, "ASSET_TEXTURES_2D", modelIds[i]);
                break;
            default:
                modelBuildId = AssetsHelper::get_build_id_of_index(_settings, "ASSET_SPRITES", modelIds[i]);
                break;
        }
        jsonFile.set_string("/models/" + std::to_string(i), modelBuildId);
    }
    
    for(int i = 0; i < objectHeader->numberOfVehicleParts; i++) {
        jsonFile.set_int("/vehicle-parts/" + std::to_string(i), vehiclePartIds[i]);
        jsonFile.set_int("/vehicle-part-indices/" + std::to_string(i), vehiclePartIndices[i]);
    }
    
    // There are some junk bytes at the end of the vehicle part indices.
    size_t numberOfJunkVehiclePartsIndexBytes = DataHelper::align8(objectHeader->numberOfVehicleParts) - objectHeader->numberOfVehicleParts;
    for(int i = 0; i < numberOfJunkVehiclePartsIndexBytes; i++) {
        jsonFile.set_int("/vehicle-part-indices-junk-bytes/" + std::to_string(i), vehiclePartIndices[objectHeader->numberOfVehicleParts + i]);
    }
    
    for(int i = 0; i < objectHeader->numberOfParticles; i++) {
        std::string ptr = "/particles/" + std::to_string(i);
        if(particles[i].upper_w.s0_s == -1) { // This seems to be a special case?
            jsonFile.set_bool(ptr + "/special-case", true);
            jsonFile.set_int(ptr + "/junk-data", particles[i].lower);
            jsonFile.set_int(ptr + "/arg1", particles[i].upper_w.s1_b.b0);
            jsonFile.set_int(ptr + "/arg2", particles[i].upper_w.s1_b.b1);
        } else {
            //jsonFile.set_bool(ptr + "/special-case", false);
            jsonFile.set_int(ptr + "/arg1", particles[i].upper_w.s0_b.b0);
            jsonFile.set_int(ptr + "/arg2", particles[i].upper_w.s0_b.b1);
            jsonFile.set_int(ptr + "/arg3", particles[i].upper_w.s1_s);
            jsonFile.set_int(ptr + "/arg4", particles[i].lower_w.s0_s);
            jsonFile.set_int(ptr + "/arg5", particles[i].lower_w.s1_s);
        }
    }
    
    size_t offsetToJunkBytes = objectHeader->objectParticles + (objectHeader->numberOfParticles * sizeof(ObjectHeaderParticleData));
    size_t numberOfJunkBytes = rawBytes.size() - offsetToJunkBytes;
    
    for(size_t i = 0; i < numberOfJunkBytes; i++) {
        jsonFile.set_int("/junk-data/"+std::to_string(i), rawBytes[offsetToJunkBytes + i]);
    }
    
    jsonFile.save();
}

ExtractObjectHeader::~ExtractObjectHeader() {
    
}

void ExtractObjectHeader::_flags_to_string(WritableJsonFile &jsonFile, be_uint16_t flags) {
    if(flags == 0) {
        return;
    }
    
    size_t numberOfBits = sizeof(be_uint16_t) * 8;
    
    int count = 0;
    
    for(size_t i = 0; i < numberOfBits; i++) {
        int flag = 1 << i;
        
        if(!(flag & flags)) {
            continue;
        }
        
        std::string ptr = "/flags/" + std::to_string(count);
        
        if(OBJECT_HEADER_FLAGS.has_value(flag)) {
            jsonFile.set_string(ptr, OBJECT_HEADER_FLAGS.get_key(flag));
        } else {
            jsonFile.set_string(ptr, "FLAG_" + StringHelper::to_hex(flag, 4));
        }
        
        count++;
    }
}