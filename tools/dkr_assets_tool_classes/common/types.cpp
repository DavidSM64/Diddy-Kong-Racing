#include "types.h"

bool is_binary_type(std::string type) {
    return type == "Binary" || type == "Miscellaneous"
        || type == "ObjectHeaders" || type == "Audio" 
        || type == "Particles" || type == "ParticleBehaviors";
}

bool is_compressed_type(std::string type) {
    return type == "Compressed" || type == "LevelObjectMap" || type == "LevelModels" 
        || type == "ObjectModels" || type == "ObjectAnimations";
}

bool is_json_type(std::string type){
    return type == "MenuText" || type == "GameText"  || type == "TTGhosts" || type == "LevelNames" || 
        type == "LevelHeaders" || type == "Textures" || type == "Sprites" || type == "Fonts";
}
