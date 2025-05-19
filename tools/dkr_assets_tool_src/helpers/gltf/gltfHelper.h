#pragma once

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include <string>
#include "libs/tiny_gltf.h"

namespace DkrAssetsTool {

class GltfFile;

// Represents a node in the gltf file.
class GltfFileNode {
public:
    GltfFileNode(GltfFile *file, tinygltf::Node *node);
    ~GltfFileNode();
    
    size_t get_child_count();
    GltfFileNode *get_child_node_by_index(int nodeIndex);
    
    void get_position(double &outX, double &outY, double &outZ);
    std::string get_name();
    
    template <typename T>
    T get_extra(std::string key, T defaultValue) {
        if(!_node->extras.IsObject()) {
            // This node does not have any extras, just return the default value.
            return defaultValue;
        }
        
        if(!_node->extras.Has(key)) {
            // Return default value if the key is not in the map.
            return defaultValue;
        }
        
        tinygltf::Value val = _node->extras.Get(key);
        
        return val.Get<T>();
    }
private:
    GltfFile *_file;
    tinygltf::Node *_node;
};

// Read-Only .gltf file
class GltfFile {
public:
    GltfFile(const fs::path &filepath); 
    ~GltfFile();
    
    size_t get_node_count();
    GltfFileNode *get_node(int nodeIndex);
    bool search_for_node_by_name(const std::string nodeName, int &outIndex);
    
private:
    tinygltf::Model _model;
    tinygltf::TinyGLTF _tinygltf;
    std::unordered_map<tinygltf::Node *, GltfFileNode *> _nodeCache;
    
};

// Write-Only .gltf file
class WriteableGltfFile {
public:
    WriteableGltfFile(std::string rootNode);
    ~WriteableGltfFile();
    
    // Node stuff
    static const int ROOT_NODE = 0;
    
    // returns index of the new node.
    int new_node(const std::string nodeName, int parentNode = ROOT_NODE);
    
    void set_node_position(int node, double x, double y, double z);
    void set_node_scale(int node, double x, double y, double z);
    void set_node_rotation(int node, double x, double y, double z, double w);
    void set_node_rotation_y(int node, double y);
    
    template <typename T>
    void set_node_extra(int node, std::string key, T value) {
        if((int)_model.nodes[node].extras.Type() == 0) {
            tinygltf::Value::Object initObj;
            _model.nodes[node].extras = tinygltf::Value(initObj);
        }
        
        tinygltf::Value::Object &obj = _model.nodes[node].extras.Get<tinygltf::Value::Object>();

        obj[key] = tinygltf::Value(value);
    };
    
    void save(const std::string filepath);
    
private:
    tinygltf::Model _model;
    tinygltf::TinyGLTF _tinygltf;
};

class GltfHelper {
public:
    
};

}