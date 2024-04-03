#include "gltfHelper.h"

// Defines for the tinygltf library.
#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_USE_CPP14
#include "libs/tiny_gltf.h"

GltfFile::GltfFile(const fs::path &filepath) {
    std::string err;
    std::string warn;
    bool loadResult = _tinygltf.LoadASCIIFromFile(&_model, &err, &warn, filepath);
    
    if(!warn.empty()) {
        DebugHelper::warn(warn);
    }
    
    if(!err.empty()) {
        DebugHelper::error_no_throw(err);
    }
    
    DebugHelper::assert_(loadResult, "(GltfFile::GltfFile) Failed to load GLTF file ", filepath);
    
    // Model has successfully loaded.
}

GltfFile::~GltfFile() {
}

int GltfFile::get_node_count() {
    return _model.nodes.size();
}

std::string GltfFile::get_node_name(int node) {
    return _model.nodes[node].name;
}

void GltfFile::get_node_position(int node, double &x, double &y, double &z) {
    x = _model.nodes[node].translation[0];
    y = _model.nodes[node].translation[1];
    z = _model.nodes[node].translation[2];
}

WriteableGltfFile::WriteableGltfFile(std::string rootName) {
    tinygltf::Node rootNode;
    tinygltf::Scene scene;
    tinygltf::Asset asset;
    
    rootNode.name = rootName;
    
    // Root node is node 0.
    _model.nodes.push_back(rootNode);
    
    // Scene should just have the root node.
    scene.nodes.push_back(0);
    
    _model.scenes.push_back(scene);
}

WriteableGltfFile::~WriteableGltfFile() {
    
}

int WriteableGltfFile::new_node(const std::string nodeName, int parentNode) {
    tinygltf::Node newNode;
    
    int thisIndex = (int)_model.nodes.size();
    
    newNode.name = nodeName;
    
    _model.nodes[parentNode].children.push_back(thisIndex);
    
    _model.nodes.push_back(newNode);
    
    return thisIndex;
}

void WriteableGltfFile::set_node_position(int node, double x, double y, double z) {
    if(_model.nodes[node].translation.size() == 0) {
        _model.nodes[node].translation.resize(3);
    }
    _model.nodes[node].translation[0] = x;
    _model.nodes[node].translation[1] = y;
    _model.nodes[node].translation[2] = z;
}

void WriteableGltfFile::set_node_scale(int node, double x, double y, double z) {
    if(_model.nodes[node].scale.size() == 0) {
        _model.nodes[node].scale.resize(3);
    }
    _model.nodes[node].scale[0] = x;
    _model.nodes[node].scale[1] = y;
    _model.nodes[node].scale[2] = z;
}

void WriteableGltfFile::set_node_rotation(int node, double x, double y, double z, double w) {
    if(_model.nodes[node].rotation.size() == 0) {
        _model.nodes[node].rotation.resize(4);
    }
    _model.nodes[node].rotation[0] = x;
    _model.nodes[node].rotation[1] = y;
    _model.nodes[node].rotation[2] = z;
    _model.nodes[node].rotation[3] = w;
}

void WriteableGltfFile::set_node_rotation_y(int node, double y) {
    if(_model.nodes[node].rotation.size() == 0) {
        _model.nodes[node].rotation.resize(4);
        _model.nodes[node].rotation[3] = 1.0;
    }
    _model.nodes[node].rotation[1] = y;
}

void WriteableGltfFile::save(const std::string filepath) {
    FileHelper::write_folder_if_it_does_not_exist(filepath);
    _tinygltf.WriteGltfSceneToFile(&_model, filepath,
                                        true, // embedImages
                                        true, // embedBuffers
                                        true, // pretty print
                                        false); // write binary
}
