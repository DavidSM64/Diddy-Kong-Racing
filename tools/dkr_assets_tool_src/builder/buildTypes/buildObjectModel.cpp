#include "buildObjectModel.h"

#include "helpers/debugHelper.h"
#include "helpers/stringHelper.h"

#include "buildModel/objModel.h"
#include "buildModel/gltfModel.h"

using namespace DkrAssetsTool;

void BuildObjectModel::build(BuildInfo &info) {
    // Vanilla models will just use the original raw binary.
    if(info.srcFile->has("/raw")) {
        std::string rawPath = info.srcFile->get_string("/raw");
        
        // Copy file from rawPath to destination path.
        if(info.build_to_file()) {
            // Copy file from rawPath to destination path.
            FileHelper::copy(info.localDirectory / rawPath, info.dstPath);
        } else {
            // Load raw binary into info's out
            info.out = FileHelper::read_binary_file(info.localDirectory / rawPath);
        }
        return;
    }
    
    // Custom models should support .obj (simple static models) and .gltf (for animated models)
    
    std::string localPathToModel = info.srcFile->get_string("/model");
    
    DebugHelper::assert_(!localPathToModel.empty(), "(BuildObjectModel::build) \"model\" property not specified!");
    
    fs::path modelPath = info.localDirectory / localPathToModel;
    
    std::string modelExtension = modelPath.extension().generic_string();
    
    // Make the extension case-insensitive.
    StringHelper::make_lowercase(modelExtension);
    
    if(modelExtension == ".obj") {
        ObjBuildModel objModel(modelPath);
        objModel.generate_object_model(info.dstPath);
    } else if(modelExtension == ".gltf") {
        DebugHelper::error("(BuildObjectModel::build) TODO: GLTF support");
    } else {
        DebugHelper::error("(BuildObjectModel::build) Unsupported model type: \"", modelExtension, "\"");
    }
}
