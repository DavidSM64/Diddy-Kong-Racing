#include "builder.h"

Builder::Builder(std::string srcPath, std::string dstPath) {
    if(!path_exists(srcPath)) {
        display_error_and_abort("Invalid path \"", srcPath, "\"");
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
        } else if (type == "") {
            display_error_and_abort("No type found for \"", srcPath, "\".\nMake sure the \"type\" property is defined in the json file!");
        } else {
            display_error_and_abort("Unknown type \"", type, "\" in \"", srcPath, "\"");
        }
    }
}

Builder::~Builder() {
    
}
