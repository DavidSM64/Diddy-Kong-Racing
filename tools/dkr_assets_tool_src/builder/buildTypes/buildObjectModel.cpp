#include "buildObjectModel.h"

#include "helpers/debugHelper.h"
#include "helpers/stringHelper.h"

#include "buildModel/objModel.h"
#include "buildModel/gltfModel.h"

using namespace DkrAssetsTool;

BuildObjectModel::BuildObjectModel(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    // Vanilla models will just use the original raw binary.
    if(info.srcFile->has("/raw")) {
        std::string rawPath = info.srcFile->get_string("/raw");
        
        // Copy file from rawPath to destination path.
        FileHelper::copy(_info.localDirectory / rawPath, info.dstPath);
        return;
    }
    
    // Custom models should support .obj (simple static models) and .gltf
    
    std::string localPathToModel = info.srcFile->get_string("/model");
    
    DebugHelper::assert_(!localPathToModel.empty(), "(BuildObjectModel::BuildObjectModel) \"model\" property not specified!");
    
    fs::path modelPath = _info.localDirectory / localPathToModel;
    
    std::string modelExtension = modelPath.extension().generic_string();
    
    // Make the extension case-insensitive.
    StringHelper::make_lowercase(modelExtension);
    
    if(modelExtension == ".obj") {
        ObjBuildModel objModel(modelPath, settings);
        objModel.generate_object_model(info.dstPath);
    } else if(modelExtension == ".gltf") {
        DebugHelper::error("TODO: GLTF support");
    } else {
        DebugHelper::error("Unsupported model type: \"", modelExtension, "\"");
    }
}

BuildObjectModel::~BuildObjectModel() {
    
}

