#pragma once

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/mathHelper.h"
#include <string>
#include <optional>
#include <vector>
#include "libs/tiny_gltf.h"

namespace DkrAssetsTool {

// Read-Only .gltf file
class GltfFile {
public:
    GltfFile(const fs::path &filepath); 
    ~GltfFile();
    
    fs::path get_filepath();
    
    // Returns true if there are no root nodes.
    bool empty();
    
    // Returns a list of indices to root nodes from each scene in the model.
    // A blacklist is useful for ignore certain sections (Meta data like collision spheres, attach points, etc.)
    std::vector<int> get_root_node_indices(std::optional<std::vector<std::string>> blacklist = std::nullopt);
    
    std::optional<int> get_root_node_from_name(std::string lookForName);
    
    size_t get_node_count();
    
    // Returns std::nullopt if element does not exist.
    std::optional<std::reference_wrapper<tinygltf::Node>> try_get_node(int index);
    std::optional<std::reference_wrapper<tinygltf::Mesh>> try_get_mesh(int index);
    std::optional<std::reference_wrapper<tinygltf::Buffer>> try_get_buffer(int index);
    std::optional<std::reference_wrapper<tinygltf::BufferView>> try_get_bufferview(int index);
    std::optional<std::reference_wrapper<tinygltf::Accessor>> try_get_accessor(int index);
    std::optional<std::reference_wrapper<tinygltf::Material>> try_get_material(int index);
    std::optional<std::reference_wrapper<tinygltf::Image>> try_get_image(int index);
    std::optional<std::reference_wrapper<tinygltf::Sampler>> try_get_sampler(int index);
    std::optional<std::reference_wrapper<tinygltf::Texture>> try_get_texture(int index);
    std::optional<std::reference_wrapper<tinygltf::Animation>> try_get_animation(int index);
    
    tinygltf::Node &get_node(int index); 
    tinygltf::Mesh &get_mesh(int index);
    tinygltf::Buffer &get_buffer(int index);
    tinygltf::BufferView &get_bufferview(int index);
    tinygltf::Accessor &get_accessor(int index);
    tinygltf::Material &get_material(int index);
    tinygltf::Image &get_image(int index);
    tinygltf::Sampler &get_sampler(int index);
    tinygltf::Texture &get_texture(int index);
    tinygltf::Animation &get_animation(int index);
    
    size_t number_of_nodes() const;
    size_t number_of_mesh() const;
    size_t number_of_buffer() const;
    size_t number_of_bufferview() const;
    size_t number_of_accessors() const;
    size_t number_of_materials() const;
    size_t number_of_images() const;
    size_t number_of_samplers() const;
    size_t number_of_textures() const;
    size_t number_of_animations() const;
    
    bool search_for_node_by_name(const std::string nodeName, int &outIndex);
    
private:
    tinygltf::Model _model;
    tinygltf::TinyGLTF _tinygltf;
    fs::path _filepath;
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
}