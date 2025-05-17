#include "gltfHelper.h"

using namespace DkrAssetsTool;

// Defines for the tinygltf library.
#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_USE_CPP14
#include "libs/tiny_gltf.h"

GltfFileNode::GltfFileNode(GltfFile *file, tinygltf::Node *node) : _file(file), _node(node) {
}

GltfFileNode::~GltfFileNode(){
}

size_t GltfFileNode::get_child_count() {
    return _node->children.size();
}

GltfFileNode *GltfFileNode::get_child_node_by_index(int nodeIndex) {
    return _file->get_node(_node->children[nodeIndex]);
}

void GltfFileNode::get_position(double &outX, double &outY, double &outZ) {
    outX = _node->translation[0];
    outY = _node->translation[1];
    outZ = _node->translation[2];
}

std::string GltfFileNode::get_name() {
    return _node->name;
}
    
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
    // Free node cache memory.
    for (auto &pair : _nodeCache) {
        if(pair.second == nullptr) {
            continue;
        }
        delete pair.second;
    }
}

size_t GltfFile::get_node_count() {
    return _model.nodes.size();
}

GltfFileNode *GltfFile::get_node(int nodeIndex) {
    DebugHelper::assert_(nodeIndex < (int)_model.nodes.size(), 
        "(GltfFile::get_node) Node index ", nodeIndex, " is out of range!");
        
    tinygltf::Node *tinygltfNode = &_model.nodes[nodeIndex];
    
    if(_nodeCache.find(tinygltfNode) == _nodeCache.end()) {
        _nodeCache[tinygltfNode] = new GltfFileNode(this, tinygltfNode);
    }
        
    return _nodeCache[tinygltfNode];
}


bool GltfFile::search_for_node_by_name(const std::string nodeName, int &outIndex) {
    size_t numNodes = get_node_count();
    for(size_t i = 0; i < numNodes; i++) {
        if(_model.nodes[i].name == nodeName) {
            outIndex = i;
            return true;
        }
    }
    // No node with the name was found.
    outIndex = -1;
    return false;
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
