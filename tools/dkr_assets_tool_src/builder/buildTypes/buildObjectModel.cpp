#include "buildObjectModel.h"

#include "helpers/debugHelper.h"
#include "helpers/stringHelper.h"

#include "buildModel/objModel.h"
#include "buildModel/gltfModel.h"

using namespace DkrAssetsTool;

void BuildObjectModel::build(BuildInfo &info) {
    const JsonFile &jsonFile = info.get_src_json_file();
    
    // Vanilla models will just use the original raw binary.
    if(jsonFile.has("/raw")) {
        std::string rawPath = jsonFile.get_string("/raw");
        
        fs::path dir = info.get_path_to_directory();
        
        if(info.build_to_file()) {
            // Copy file from rawPath to destination path.
            info.copy_to_dstPath(dir / rawPath);
        } else {
            // Load raw binary into info's out
            info.out = FileHelper::read_binary_file(dir / rawPath);
        }
        return;
    }
    
    // Custom models should support .obj (simple static models) and .gltf (for animated models)
    
    std::string localPathToModel = jsonFile.get_string("/model");
    
    DebugHelper::assert_(!localPathToModel.empty(), "(BuildObjectModel::build) \"model\" property not specified!");
    
    fs::path modelPath = info.get_path_to_directory() / localPathToModel;
    
    std::string modelExtension = modelPath.extension().generic_string();
    
    // Make the extension case-insensitive.
    StringHelper::make_lowercase(modelExtension);
    
    if(modelExtension == ".obj") {
        ObjBuildModel objModel(modelPath);
        objModel.generate_object_model(info);
    } else if(modelExtension == ".gltf") {
        DebugHelper::error("(BuildObjectModel::build) TODO: GLTF support");
    } else {
        DebugHelper::error("(BuildObjectModel::build) Unsupported model type: \"", modelExtension, "\"");
    }
}
