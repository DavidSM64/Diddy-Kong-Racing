#include "buildObjectHeader.h"

#include <cstring>

#include "helpers/assetsHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/dataHelper.h"
#include "fileTypes/objectHeader.hpp"

using namespace DkrAssetsTool;

be_uint16_t string_to_flags(BuildInfo &info) {
    size_t flagCount = info.srcFile->length_of_array("/flags");
    
    if(flagCount < 1) {
        return 0;
    }
    
    uint16_t result = 0;
    
    for(size_t i = 0; i < flagCount; i++) {
        std::string curFlag = info.srcFile->get_string_uppercase("/flags/" + std::to_string(i));
        uint16_t flagVal;
        if(StringHelper::starts_with(curFlag, "FLAG_")) {
            std::string flagHexVal = curFlag.substr(5);
            flagVal = std::stoi(flagHexVal, 0, 16);
        } else {
            DebugHelper::assert(OBJECT_HEADER_FLAGS.has_key(curFlag), 
                "(BuildObjectHeader::string_to_flags) Invalid object header flag: \"", curFlag, "\"");
            flagVal = OBJECT_HEADER_FLAGS.get_value(curFlag);
        }
        
        result |= flagVal;
    }
    
    return result;
}

void BuildObjectHeader::build(BuildInfo &info) {
    info.load_enums_into_c_context({ "enums.h", "object_behaviors.h" });
    
    // Get the counts for each section.
    size_t numberOfModels = info.srcFile->length_of_array("/models");
    size_t numberOfVehicleParts = info.srcFile->length_of_array("/vehicle-parts");
    size_t numberOfParticles = info.srcFile->length_of_array("/particles");
    size_t numberOfJunkBytes = info.srcFile->length_of_array("/junk-data");
    
    // Calculate size & offsets to the different sections.
    size_t outSize = sizeof(ObjectHeader);
    size_t offsetToModels = outSize;
    outSize += numberOfModels * sizeof(be_int32_t); // model ids
    size_t offsetToVehiclePartIds = outSize;
    outSize += numberOfVehicleParts * sizeof(be_int32_t); // Vehicle part ids
    size_t offsetToVehiclePartIndices = outSize;
    outSize += DataHelper::align8(numberOfVehicleParts * sizeof(uint8_t)); // Vehicle part indices
    size_t offsetToParticles = outSize;
    outSize += numberOfParticles * sizeof(ObjectHeaderParticleData); // Particles
    size_t offsetToJunkData = outSize;
    outSize += numberOfJunkBytes; // random bytes
    
    info.out.resize(outSize);
    
    // Make pointers to the different sections based on the offsets.
    ObjectHeader *objectHeader = reinterpret_cast<ObjectHeader *>(&info.out[0]);
    be_int32_t *modelIds = reinterpret_cast<be_int32_t *>(&info.out[offsetToModels]);
    be_int32_t *vehiclePartIds = reinterpret_cast<be_int32_t *>(&info.out[offsetToVehiclePartIds]);
    uint8_t *vehiclePartIndices = &info.out[offsetToVehiclePartIndices];
    ObjectHeaderParticleData *particles = reinterpret_cast<ObjectHeaderParticleData *>(&info.out[offsetToParticles]);
    uint8_t *junkData = &info.out[offsetToJunkData];
    
    std::string modelType = info.srcFile->get_string("/model-type");
    
    const CContext &cContext = info.get_c_context();
    
    /** Object Header **/
    
    // Offsets to data
    objectHeader->modelIds           = offsetToModels;
    objectHeader->vehiclePartIds     = offsetToVehiclePartIds;
    objectHeader->vehiclePartIndices = offsetToVehiclePartIndices;
    objectHeader->objectParticles    = offsetToParticles;
    objectHeader->unk20              = offsetToJunkData;
    objectHeader->unk24              = offsetToJunkData;
    
    // Behavior
    if(info.srcFile->has("/behavior")) {
        std::string behavior = info.srcFile->get_string("/behavior");
        objectHeader->behaviorId = cContext.get_int_value_of_symbol(behavior);
    } else {
        objectHeader->behaviorId = -1;
    }
    
    // Model Type
    objectHeader->modelType = cContext.get_int_value_of_symbol(modelType);
    
    // Flags
    objectHeader->flags = string_to_flags(info);
    
    // Internal Name
    std::string internalName = info.srcFile->get_string("/internal-name");
    std::strncpy(objectHeader->internalName, internalName.c_str(), internalName.size());
    
    // Floats
    objectHeader->shadowScale = info.srcFile->get_float("/shadow-scale");
    objectHeader->scale = info.srcFile->get_float("/scale");
    objectHeader->shadeBrightness = info.srcFile->get_float("/shade-brightness");
    objectHeader->shadeAmbient = info.srcFile->get_float("/shade-ambient");
    
    // Unknowns
    objectHeader->unk0 = info.srcFile->get_int("/unknown/unk0");
    objectHeader->unk8 = info.srcFile->get_float("/unknown/unk8");
    objectHeader->unk34 = info.srcFile->get_int("/unknown/unk34");
    objectHeader->unk38 = info.srcFile->get_int("/unknown/unk38");
    objectHeader->unk3A = info.srcFile->get_int("/unknown/unk3A");
    objectHeader->unk3B = info.srcFile->get_int("/unknown/unk3B");
    objectHeader->unk3C = info.srcFile->get_int("/unknown/unk3C");
    objectHeader->unk3D = info.srcFile->get_int("/unknown/unk3D");
    objectHeader->unk42 = info.srcFile->get_int("/unknown/unk42");
    objectHeader->unk44 = info.srcFile->get_int("/unknown/unk44");
    objectHeader->unk46 = info.srcFile->get_int("/unknown/unk46");
    objectHeader->unk48 = info.srcFile->get_int("/unknown/unk48");
    objectHeader->unk4A = info.srcFile->get_int("/unknown/unk4A");
    objectHeader->unk4C = info.srcFile->get_int("/unknown/unk4C");
    objectHeader->unk50 = info.srcFile->get_int("/unknown/unk50");
    objectHeader->unk52 = info.srcFile->get_int("/unknown/unk52");
    objectHeader->unk58 = info.srcFile->get_int("/unknown/unk58");
    objectHeader->unk59 = info.srcFile->get_int("/unknown/unk59");
    objectHeader->unk5B = info.srcFile->get_int("/unknown/unk5B");
    objectHeader->unk5C = info.srcFile->get_int("/unknown/unk5C");
    objectHeader->unk5D = info.srcFile->get_int("/unknown/unk5D");
    objectHeader->unk5E = info.srcFile->get_int("/unknown/unk5E");
    objectHeader->unk5F = info.srcFile->get_int("/unknown/unk5F");
    objectHeader->unk70 = info.srcFile->get_int("/unknown/unk70");
    objectHeader->unk71 = info.srcFile->get_int("/unknown/unk71");
    objectHeader->unk72 = info.srcFile->get_int("/unknown/unk72");
    objectHeader->unk73 = info.srcFile->get_int("/unknown/unk73");
    objectHeader->unk74 = info.srcFile->get_int("/unknown/unk74");
    objectHeader->unk75 = info.srcFile->get_int("/unknown/unk75");
    objectHeader->unk76 = info.srcFile->get_int("/unknown/unk76");
    objectHeader->unk77 = info.srcFile->get_int("/unknown/unk77");
    
    // Other
    objectHeader->shadowGroup = info.srcFile->get_int("/shadow-group");
    objectHeader->waterEffectGroup = info.srcFile->get_int("/water-effect-group");
    objectHeader->shadeAngleY = info.srcFile->get_int("/shade-angle-y");
    objectHeader->shadeAngleZ = info.srcFile->get_int("/shade-angle-z");
    objectHeader->drawDistance = info.srcFile->get_int("/draw-distance");
    
    
    objectHeader->numberOfModelIds = numberOfModels;
    objectHeader->numberOfVehicleParts = numberOfVehicleParts;
    objectHeader->numberOfParticles = numberOfParticles;
    
    
    /** Model IDs **/
    std::string assetSection;
    
    switch(objectHeader->modelType) {
        case OBJECT_MODEL_TYPE_3D_MODEL:
            assetSection = "ASSET_OBJECT_MODELS";
            break;
        case OBJECT_MODEL_TYPE_MISC:
            assetSection = "ASSET_TEXTURES_2D";
            break;
        default:
            assetSection = "ASSET_SPRITES";
            break;
    }
    
    for(size_t i = 0; i < numberOfModels; i++) {
        std::string modelBuildId = info.srcFile->get_string("/models/" + std::to_string(i));
        modelIds[i] = AssetsHelper::get_asset_index(assetSection, modelBuildId);
    }
    
    /** Vehicle Parts **/
    for(size_t i = 0; i < numberOfVehicleParts; i++) {
        vehiclePartIds[i] = info.srcFile->get_int("/vehicle-parts/" + std::to_string(i));
        vehiclePartIndices[i] = info.srcFile->get_int("/vehicle-part-indices/" + std::to_string(i));
    }
    
    if(info.srcFile->has("/vehicle-part-indices-junk-bytes")) {
        size_t numberOfJunkVehiclePartsIndexBytes = info.srcFile->length_of_array("/vehicle-part-indices-junk-bytes");
        for(size_t i = 0; i < numberOfJunkVehiclePartsIndexBytes; i++) {
            vehiclePartIndices[i + numberOfVehicleParts] = info.srcFile->get_int("/vehicle-part-indices-junk-bytes/" + std::to_string(i));
        }
    }
    
    /** Particles **/
    for(size_t i = 0; i < numberOfParticles; i++) {
        std::string ptr = "/particles/" + std::to_string(i);
        
        // Not sure what this special case actually is. Just that the args are different.
        bool isSpecialCase = info.srcFile->get_bool(ptr + "/special-case");
        if(isSpecialCase) {
            particles[i].lower = info.srcFile->get_int(ptr + "/junk-data"); // Not actually used I think.
            particles[i].upper_w.s0_s = -1; // Marks this as the special case
            particles[i].upper_w.s1_b.b0 = info.srcFile->get_int(ptr + "/arg1");
            particles[i].upper_w.s1_b.b1 = info.srcFile->get_int(ptr + "/arg2");
        } else {
             particles[i].upper_w.s0_b.b0 = info.srcFile->get_int(ptr + "/arg1");
             particles[i].upper_w.s0_b.b1 = info.srcFile->get_int(ptr + "/arg2");
             particles[i].upper_w.s1_s    = info.srcFile->get_int(ptr + "/arg3");
             particles[i].lower_w.s0_s    = info.srcFile->get_int(ptr + "/arg4");
             particles[i].lower_w.s1_s    = info.srcFile->get_int(ptr + "/arg5");
        }
    }
    
    /** Junk Data **/
    for(size_t i = 0; i < numberOfJunkBytes; i++) {
        junkData[i] = info.srcFile->get_int("/junk-data/" + std::to_string(i));
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
