#include "objModel.h"

#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"

using namespace DkrAssetsTool;

ObjBuildModel::ObjBuildModel(fs::path filepath, DkrAssetsSettings &settings) {
    DebugHelper::warn("Obj file: ", filepath);
    
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
            settings.adjust_from_model_scale(x);
            settings.adjust_from_model_scale(y);
            settings.adjust_from_model_scale(z);
            
            // Add the new vertex
            vertices.emplace_back(Vec3f(x, y, z));
            continue;
        }
        if(components[0] == "vn") {
            // User-generated normals are not used in DKR.
            continue;
        }
        if(components[0] == "vt") {
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
            
            // Add the new triangle.
            _add_new_triangle_to_current_block(vertices[positionAIndex], vertices[positionBIndex], vertices[positionCIndex]);
            
            faceIndex++;
            continue;
        }
        if(components[0] == "usemtl") {
            currentMaterial = components[1];
            continue;
        }
        if(components[0] == "o") {
            continue;
        }
        if(components[0] == "mtllib") {
            continue;
        }
    }
    
    DebugHelper::info("Done!");
}
