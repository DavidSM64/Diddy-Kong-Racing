#include "builder.h"

Builder::Builder(std::string srcPath, std::string dstPath) {
    if(!path_exists(srcPath)) {
        std::cout << "Error: Invalid path \"" << srcPath << "\"" << std::endl;
        throw 1;
    }
    
    if(ends_with(srcPath, ".json")) {
        std::string type = get_string_from_json(srcPath, "type");
        if(type == "Textures") {
            BuildTexture(srcPath, dstPath);
        } else if (type == "TTGhosts") {
            BuildTTGhost(srcPath, dstPath);
        } else if (type == "Sprites") {
            BuildSprite(srcPath, dstPath);
        } else if (type == "LevelNames") {
            BuildLevelName(srcPath, dstPath);
        } else if (type == "LevelHeaders") {
            BuildLevelHeader(srcPath, dstPath);
        } else if (type == "GameText") {
            BuildGameText(srcPath, dstPath);
        } else if (type == "MenuText") {
            BuildMenuText(srcPath, dstPath);
        } else if (type == "Fonts") {
            BuildFonts(srcPath, dstPath);
        }  
    }
}

Builder::~Builder() {
    
}
