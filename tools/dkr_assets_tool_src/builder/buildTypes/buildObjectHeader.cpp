#include "buildObjectHeader.h"

#include <cstring>

#include "helpers/assetsHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/dataHelper.h"
#include "fileTypes/objectHeader.hpp"

BuildObjectHeader::BuildObjectHeader(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    _preload_c_context();
    
    // Get the counts for each section.
    size_t numberOfModels = _info.srcFile->length_of_array("/models");
    size_t numberOfVehicleParts = _info.srcFile->length_of_array("/vehicle-parts");
    size_t numberOfParticles = _info.srcFile->length_of_array("/particles");
    size_t numberOfJunkBytes = _info.srcFile->length_of_array("/junk-data");
    
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
    
    std::vector<uint8_t> out(outSize);
    
    // Make pointers to the different sections based on the offsets.
    ObjectHeader *objectHeader = reinterpret_cast<ObjectHeader *>(&out[0]);
    be_int32_t *modelIds = reinterpret_cast<be_int32_t *>(&out[offsetToModels]);
    be_int32_t *vehiclePartIds = reinterpret_cast<be_int32_t *>(&out[offsetToVehiclePartIds]);
    uint8_t *vehiclePartIndices = &out[offsetToVehiclePartIndices];
    ObjectHeaderParticleData *particles = reinterpret_cast<ObjectHeaderParticleData *>(&out[offsetToParticles]);
    uint8_t *junkData = &out[offsetToJunkData];
    
    std::string modelType = _info.srcFile->get_string("/model-type");
    
    /** Object Header **/
    
    // Offsets to data
    objectHeader->modelIds           = offsetToModels;
    objectHeader->vehiclePartIds     = offsetToVehiclePartIds;
    objectHeader->vehiclePartIndices = offsetToVehiclePartIndices;
    objectHeader->objectParticles    = offsetToParticles;
    objectHeader->unk20              = offsetToJunkData;
    objectHeader->unk24              = offsetToJunkData;
    
    // Behavior
    if(_info.srcFile->has("/behavior")) {
        std::string behavior = _info.srcFile->get_string("/behavior");
        objectHeader->behaviorId = _c_context.get_int_value_of_symbol(behavior);
    } else {
        objectHeader->behaviorId = -1;
    }
    
    // Model Type
    objectHeader->modelType = _c_context.get_int_value_of_symbol(modelType);
    
    // Flags
    objectHeader->flags = _string_to_flags();
    
    // Internal Name
    std::string internalName = _info.srcFile->get_string("/internal-name");
    std::strncpy(objectHeader->internalName, internalName.c_str(), internalName.size());
    
    // Floats
    objectHeader->shadowScale = _info.srcFile->get_float("/shadow-scale");
    objectHeader->scale = _info.srcFile->get_float("/scale");
    objectHeader->shadeBrightness = _info.srcFile->get_float("/shade-brightness");
    objectHeader->shadeAmbient = _info.srcFile->get_float("/shade-ambient");
    
    // Unknowns
    objectHeader->unk0 = _info.srcFile->get_int("/unknown/unk0");
    objectHeader->unk8 = _info.srcFile->get_float("/unknown/unk8");
    objectHeader->unk34 = _info.srcFile->get_int("/unknown/unk34");
    objectHeader->unk38 = _info.srcFile->get_int("/unknown/unk38");
    objectHeader->unk3A = _info.srcFile->get_int("/unknown/unk3A");
    objectHeader->unk3B = _info.srcFile->get_int("/unknown/unk3B");
    objectHeader->unk3C = _info.srcFile->get_int("/unknown/unk3C");
    objectHeader->unk3D = _info.srcFile->get_int("/unknown/unk3D");
    objectHeader->unk42 = _info.srcFile->get_int("/unknown/unk42");
    objectHeader->unk44 = _info.srcFile->get_int("/unknown/unk44");
    objectHeader->unk46 = _info.srcFile->get_int("/unknown/unk46");
    objectHeader->unk48 = _info.srcFile->get_int("/unknown/unk48");
    objectHeader->unk4A = _info.srcFile->get_int("/unknown/unk4A");
    objectHeader->unk4C = _info.srcFile->get_int("/unknown/unk4C");
    objectHeader->unk50 = _info.srcFile->get_int("/unknown/unk50");
    objectHeader->unk52 = _info.srcFile->get_int("/unknown/unk52");
    objectHeader->unk58 = _info.srcFile->get_int("/unknown/unk58");
    objectHeader->unk59 = _info.srcFile->get_int("/unknown/unk59");
    objectHeader->unk5B = _info.srcFile->get_int("/unknown/unk5B");
    objectHeader->unk5C = _info.srcFile->get_int("/unknown/unk5C");
    objectHeader->unk5D = _info.srcFile->get_int("/unknown/unk5D");
    objectHeader->unk5E = _info.srcFile->get_int("/unknown/unk5E");
    objectHeader->unk5F = _info.srcFile->get_int("/unknown/unk5F");
    objectHeader->unk70 = _info.srcFile->get_int("/unknown/unk70");
    objectHeader->unk71 = _info.srcFile->get_int("/unknown/unk71");
    objectHeader->unk72 = _info.srcFile->get_int("/unknown/unk72");
    objectHeader->unk73 = _info.srcFile->get_int("/unknown/unk73");
    objectHeader->unk74 = _info.srcFile->get_int("/unknown/unk74");
    objectHeader->unk75 = _info.srcFile->get_int("/unknown/unk75");
    objectHeader->unk76 = _info.srcFile->get_int("/unknown/unk76");
    objectHeader->unk77 = _info.srcFile->get_int("/unknown/unk77");
    
    // Other
    objectHeader->shadowGroup = _info.srcFile->get_int("/shadow-group");
    objectHeader->waterEffectGroup = _info.srcFile->get_int("/water-effect-group");
    objectHeader->shadeAngleY = _info.srcFile->get_int("/shade-angle-y");
    objectHeader->shadeAngleZ = _info.srcFile->get_int("/shade-angle-z");
    objectHeader->drawDistance = _info.srcFile->get_int("/draw-distance");
    
    
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
        std::string modelBuildId = _info.srcFile->get_string("/models/" + std::to_string(i));
        modelIds[i] = AssetsHelper::get_asset_index(_settings, assetSection, modelBuildId);
    }
    
    /** Vehicle Parts **/
    for(size_t i = 0; i < numberOfVehicleParts; i++) {
        vehiclePartIds[i] = _info.srcFile->get_int("/vehicle-parts/" + std::to_string(i));
        vehiclePartIndices[i] = _info.srcFile->get_int("/vehicle-part-indices/" + std::to_string(i));
    }
    
    if(_info.srcFile->has("/vehicle-part-indices-junk-bytes")) {
        size_t numberOfJunkVehiclePartsIndexBytes = _info.srcFile->length_of_array("/vehicle-part-indices-junk-bytes");
        for(size_t i = 0; i < numberOfJunkVehiclePartsIndexBytes; i++) {
            vehiclePartIndices[i + numberOfVehicleParts] = _info.srcFile->get_int("/vehicle-part-indices-junk-bytes/" + std::to_string(i));
        }
    }
    
    /** Particles **/
    for(size_t i = 0; i < numberOfParticles; i++) {
        std::string ptr = "/particles/" + std::to_string(i);
        
        // Not sure what this special case actually is. Just that the args are different.
        bool isSpecialCase = _info.srcFile->get_bool(ptr + "/special-case");
        if(isSpecialCase) {
            particles[i].lower = _info.srcFile->get_int(ptr + "/junk-data"); // Not actually used I think.
            particles[i].upper_w.s0_s = -1; // Marks this as the special case
            particles[i].upper_w.s1_b.b0 = _info.srcFile->get_int(ptr + "/arg1");
            particles[i].upper_w.s1_b.b1 = _info.srcFile->get_int(ptr + "/arg2");
        } else {
             particles[i].upper_w.s0_b.b0 = _info.srcFile->get_int(ptr + "/arg1");
             particles[i].upper_w.s0_b.b1 = _info.srcFile->get_int(ptr + "/arg2");
             particles[i].upper_w.s1_s    = _info.srcFile->get_int(ptr + "/arg3");
             particles[i].lower_w.s0_s    = _info.srcFile->get_int(ptr + "/arg4");
             particles[i].lower_w.s1_s    = _info.srcFile->get_int(ptr + "/arg5");
        }
    }
    
    /** Junk Data **/
    for(size_t i = 0; i < numberOfJunkBytes; i++) {
        junkData[i] = _info.srcFile->get_int("/junk-data/" + std::to_string(i));
    }
    
    // Write Object Header.
    FileHelper::write_binary_file(out, _info.dstPath, true);
}

BuildObjectHeader::~BuildObjectHeader() {
    
}

be_uint16_t BuildObjectHeader::_string_to_flags() {
    size_t flagCount = _info.srcFile->length_of_array("/flags");
    
    if(flagCount < 1) {
        return 0;
    }
    
    uint16_t result = 0;
    
    for(size_t i = 0; i < flagCount; i++) {
        std::string curFlag = _info.srcFile->get_string_uppercase("/flags/" + std::to_string(i));
        uint16_t flagVal;
        if(StringHelper::starts_with(curFlag, "FLAG_")) {
            std::string flagHexVal = curFlag.substr(5);
            flagVal = std::stoi(flagHexVal, 0, 16);
        } else {
            DebugHelper::assert(OBJECT_HEADER_FLAGS.has_key(curFlag), 
                "(BuildObjectHeader::_string_to_flags) Invalid object header flag: \"", curFlag, "\"");
            flagVal = OBJECT_HEADER_FLAGS.get_value(curFlag);
        }
        
        result |= flagVal;
    }
    
    return result;
}

void BuildObjectHeader::_preload_c_context() {
    fs::path includeFolder = _settings.pathToRepo / "include/";
    
    // Load all enums from these files.
    fs::path enumPaths[] = {
        includeFolder / "object_behaviors.h",
        includeFolder / "enums.h"
    };
    
    for(fs::path &enumPath : enumPaths) {
        CEnumsHelper::load_enums_from_file(&_c_context, enumPath);
    }
}
