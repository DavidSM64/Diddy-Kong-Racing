#include "objModel.h"

#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"

using namespace DkrAssetsTool;

ObjBuildModel::ObjBuildModel(fs::path filepath) {
    std::string objText = FileHelper::read_text_file(filepath);
    
    std::vector<std::string> lines;
    StringHelper::split_and_trim(objText, '\n', lines);
    
    std::vector<BuildModelVertex> vertices;
    std::vector<Vec2f> uvs;
    
    std::string currentMaterial = "";
    
    size_t faceIndex = 0;
    
    for(std::string &line : lines) {
        if(line[0] == '#' || line.empty()) {
            // Skip this line if it is empty or a comment.
            continue;
        }
        std::vector<std::string> components;
        StringHelper::split(line, ' ', components);
        if(components[0] == "v") {
            // Parse position coordinates.
            double x = std::stod(components[1]);
            double y = std::stod(components[2]);
            double z = std::stod(components[3]);
            
            // Scale the model according that is specified in settings.
            //settings.adjust_from_model_scale(x);
            //settings.adjust_from_model_scale(y);
           // settings.adjust_from_model_scale(z);
            
            // Add the new vertex
            vertices.emplace_back(Vec3f(x, y, z));
            continue;
        }
        if(components[0] == "vn") {
            // User-generated normals are not used in DKR.
            continue;
        }
        if(components[0] == "vt") {
            double u = std::stod(components[1]);
            double v = std::stod(components[2]);
            
            uvs.emplace_back(Vec2f(u, v));
            continue;
        }
        if(components[0] == "f") {
            std::vector<std::string> faceComponentsA;
            std::vector<std::string> faceComponentsB;
            std::vector<std::string> faceComponentsC;
            
            // split the different indicies for a face.
            StringHelper::split(components[1], '/', faceComponentsA);
            StringHelper::split(components[2], '/', faceComponentsB);
            StringHelper::split(components[3], '/', faceComponentsC);
            
            // parse index for vertex.
            int positionAIndex = std::stoi(faceComponentsA[0]) - 1;
            int positionBIndex = std::stoi(faceComponentsB[0]) - 1;
            int positionCIndex = std::stoi(faceComponentsC[0]) - 1;
            
            // Make sure the indicies are in the correct range.
            DebugHelper::assert_((positionAIndex >= 0) && (positionAIndex < vertices.size()), 
                "(ObjBuildModel::ObjBuildModel) Face ", faceIndex, " first index is out of range!");
            DebugHelper::assert_((positionBIndex >= 0) && (positionBIndex < vertices.size()), 
                "(ObjBuildModel::ObjBuildModel) Face ", faceIndex, " second index is out of range!");
            DebugHelper::assert_((positionCIndex >= 0) && (positionCIndex < vertices.size()), 
                "(ObjBuildModel::ObjBuildModel) Face ", faceIndex, " third index is out of range!");
            
            if(faceComponentsA.size() == 1 || faceComponentsA[1].empty()) {
                DebugHelper::info("No UVs!");
                // Add the new triangle with no UV coordinates.
                _add_new_triangle_to_current_block(vertices[positionAIndex], vertices[positionBIndex], vertices[positionCIndex]);
            } else {
                int uvAIndex = std::stoi(faceComponentsA[1]) - 1;
                int uvBIndex = std::stoi(faceComponentsB[1]) - 1;
                int uvCIndex = std::stoi(faceComponentsC[1]) - 1;
                
                // Adjust the uv coordinates to the N64 format.
                Vec2f uv0 = _get_adjusted_uv(uvs[uvAIndex], currentMaterial);
                Vec2f uv1 = _get_adjusted_uv(uvs[uvBIndex], currentMaterial);
                Vec2f uv2 = _get_adjusted_uv(uvs[uvCIndex], currentMaterial);
                
                DebugHelper::info(uv0, " ", uv1, " ", uv2);
                
                // Add the new triangle with UV coordinates.
                _add_new_triangle_to_current_block(vertices[positionAIndex], vertices[positionBIndex], vertices[positionCIndex], uv0, uv1, uv2);
            }
            
            faceIndex++;
            continue;
        }
        if(components[0] == "usemtl") {
            currentMaterial = components[1];
            _set_material(currentMaterial);
            continue;
        }
        if(components[0] == "o") {
            continue;
        }
        if(components[0] == "mtllib") {
            _parse_mtllib(filepath.parent_path() / components[1]);
            continue;
        }
    }
    
    DebugHelper::info("Done!");
}

Vec2f ObjBuildModel::_get_adjusted_uv(Vec2f uv, std::string materialId) {
    auto tryGetMaterial = _try_get_material(materialId);
    DebugHelper::assert_(tryGetMaterial.has_value(),
        "(ObjBuildModel::_get_adjusted_uv) Failed parsing UV coordinates. Could not get the material \"", materialId, "\"");
    
    BuildModelMaterial &material = tryGetMaterial.value();
    
    int texWidth, texHeight;
    material.get_texture_width_and_height(texWidth, texHeight);
    
    if(texWidth == 0 || texHeight == 0) {
        DebugHelper::warn("Could not process UV! width = ", texWidth, ", height = ", texHeight);
        return uv;
    }
    
    uv.u *= (texWidth * 32.0);
    uv.v *= (texHeight * 32.0);
            
    return uv;
}

void ObjBuildModel::_parse_mtllib(fs::path pathToLib) {
    std::string mtlText = FileHelper::read_text_file(pathToLib);
    
    std::vector<std::string> lines;
    StringHelper::split_and_trim(mtlText, '\n', lines);
    
    std::string currentMaterial = "";
    fs::path currentTexture = "";
    
    for(std::string &line : lines) {
        if(line[0] == '#' || line.empty()) {
            // Skip this line if it is empty or a comment.
            continue;
        }
        std::vector<std::string> components;
        StringHelper::split(line, ' ', components);
        
        if(components[0] == "newmtl") {
            if(!currentMaterial.empty()) {
                _add_material(currentMaterial, currentTexture);
            }
            currentMaterial = components[1];
            continue;
        }
        if(components[0] == "map_Kd") {
            currentTexture = pathToLib.parent_path() / components[1];
            continue;
        }
    }
    
    if(!currentMaterial.empty()) {
        _add_material(currentMaterial, currentTexture);
    }
}
