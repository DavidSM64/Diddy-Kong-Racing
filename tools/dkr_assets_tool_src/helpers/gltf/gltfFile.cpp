#include "gltfHelper.h"

#include "helpers/stringHelper.h"

#include <functional>

// Defines for the tinygltf library.
#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_USE_CPP14
#include "libs/tiny_gltf.h"

using namespace DkrAssetsTool;
    
GltfFile::GltfFile(const fs::path &filepath) : _filepath(filepath) {
    std::string err;
    std::string warn;
    
    bool loadResult;
    
    if(filepath.extension() == ".gltf") {
        loadResult = _tinygltf.LoadASCIIFromFile(&_model, &err, &warn, filepath);
    } else {
        // .glb
        loadResult = _tinygltf.LoadBinaryFromFile(&_model, &err, &warn, filepath);
    }
    
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
    
fs::path GltfFile::get_filepath() {
    return _filepath;
}
    
bool GltfFile::empty() {
    return (_model.scenes.size() == 0) || (_model.nodes.size() == 0);
}
    
std::vector<int> GltfFile::get_root_node_indices(std::optional<std::vector<std::string>> blacklist) {
    std::vector<int> indices;
    
    for(auto &scene : _model.scenes) {
        indices.insert(indices.end(), scene.nodes.begin(), scene.nodes.end());
    }
    
    if(blacklist.has_value()) {
        std::vector<std::string> &blist = blacklist.value();
        
        for(size_t i = 0; i < indices.size(); i++) {
            std::string nodeName = StringHelper::simplify(_model.nodes[indices[i]].name);
            bool removeThis = false;
            for(const std::string &blistEntry : blist) {
                if(StringHelper::starts_with(nodeName, blistEntry)) {
                    removeThis = true;
                    break;
                }
            }
            if(removeThis) {
                indices.erase(indices.begin() + i);
                i--;
            }
        }
    }
    
    return indices;
}
    
std::optional<int> GltfFile::get_root_node_from_name(std::string lookForName) {
    lookForName = StringHelper::simplify(lookForName);
    
    std::vector<int> childrenToSearch;
    
    for(auto &scene : _model.scenes) {
        for(auto nodeIndex : scene.nodes) {
            std::string nodeName = StringHelper::simplify(_model.nodes[nodeIndex].name);
            if(StringHelper::starts_with(nodeName, lookForName)) {
                return nodeIndex;
            }
            if(_model.nodes[nodeIndex].mesh == -1) {
                for(int childIndex : _model.nodes[nodeIndex].children) {
                    childrenToSearch.emplace_back(childIndex);
                }
            }
        }
    }
    
    for(int childIndex : childrenToSearch) {
        std::string nodeName = StringHelper::simplify(_model.nodes[childIndex].name);
        if(StringHelper::starts_with(nodeName, lookForName)) {
            return childIndex;
        }
    }
    
    return std::nullopt; // No node found.
}

size_t GltfFile::get_node_count() {
    return _model.nodes.size();
}

template<typename T>
inline std::optional<std::reference_wrapper<T>> try_get_element(int index, std::vector<T> &elementArray) {
    if((index < 0) || (index >= (int)elementArray.size())) {
        return std::nullopt;
    }
    
    return elementArray[index];
}

std::optional<std::reference_wrapper<tinygltf::Node>> GltfFile::try_get_node(int index) {
    return try_get_element<tinygltf::Node>(index, _model.nodes);
}

std::optional<std::reference_wrapper<tinygltf::Mesh>> GltfFile::try_get_mesh(int index) {
    return try_get_element<tinygltf::Mesh>(index, _model.meshes);
}

std::optional<std::reference_wrapper<tinygltf::Buffer>> GltfFile::try_get_buffer(int index) {
    return try_get_element<tinygltf::Buffer>(index, _model.buffers);
}

std::optional<std::reference_wrapper<tinygltf::BufferView>> GltfFile::try_get_bufferview(int index) {
    return try_get_element<tinygltf::BufferView>(index, _model.bufferViews);
}

std::optional<std::reference_wrapper<tinygltf::Accessor>> GltfFile::try_get_accessor(int index) {
    return try_get_element<tinygltf::Accessor>(index, _model.accessors);
}

std::optional<std::reference_wrapper<tinygltf::Material>> GltfFile::try_get_material(int index) {
    return try_get_element<tinygltf::Material>(index, _model.materials);
}

std::optional<std::reference_wrapper<tinygltf::Image>> GltfFile::try_get_image(int index) {
    return try_get_element<tinygltf::Image>(index, _model.images);
}

std::optional<std::reference_wrapper<tinygltf::Sampler>> GltfFile::try_get_sampler(int index) {
    return try_get_element<tinygltf::Sampler>(index, _model.samplers);
}

std::optional<std::reference_wrapper<tinygltf::Texture>> GltfFile::try_get_texture(int index) {
    return try_get_element<tinygltf::Texture>(index, _model.textures);
}

std::optional<std::reference_wrapper<tinygltf::Animation>> GltfFile::try_get_animation(int index) {
    return try_get_element<tinygltf::Animation>(index, _model.animations);
}

template<typename T>
inline T &get_element(int index, const std::function<std::optional<std::reference_wrapper<T>>(int)> &try_get_func, const char* name) {
    auto tryGetElement = try_get_func(index);
    DebugHelper::assert_(tryGetElement.has_value(), 
        "(GltfFile::get_element) Failed to get ", name, " at index ", index);
    return tryGetElement.value();
}

#define GET_ELEMENT_LAMBDA(funcName) [this](int i) { return this->funcName(i); }

tinygltf::Node &GltfFile::get_node(int index) {
    return get_element<tinygltf::Node>(index, GET_ELEMENT_LAMBDA(try_get_node), "node");
}

tinygltf::Mesh &GltfFile::get_mesh(int index) {
    return get_element<tinygltf::Mesh>(index, GET_ELEMENT_LAMBDA(try_get_mesh), "mesh");
}

tinygltf::Buffer &GltfFile::get_buffer(int index) {
    return get_element<tinygltf::Buffer>(index, GET_ELEMENT_LAMBDA(try_get_buffer), "buffer");
}

tinygltf::BufferView &GltfFile::get_bufferview(int index) {
    return get_element<tinygltf::BufferView>(index, GET_ELEMENT_LAMBDA(try_get_bufferview), "buffer view");
}

tinygltf::Accessor &GltfFile::get_accessor(int index) {
    return get_element<tinygltf::Accessor>(index, GET_ELEMENT_LAMBDA(try_get_accessor), "accessor");
}

tinygltf::Material &GltfFile::get_material(int index) {
    return get_element<tinygltf::Material>(index, GET_ELEMENT_LAMBDA(try_get_material), "material");
}

tinygltf::Image &GltfFile::get_image(int index) {
    return get_element<tinygltf::Image>(index, GET_ELEMENT_LAMBDA(try_get_image), "image");
}

tinygltf::Sampler &GltfFile::get_sampler(int index) {
    return get_element<tinygltf::Sampler>(index, GET_ELEMENT_LAMBDA(try_get_sampler), "sampler");
}

tinygltf::Texture &GltfFile::get_texture(int index) {
    return get_element<tinygltf::Texture>(index, GET_ELEMENT_LAMBDA(try_get_texture), "texture");
}

tinygltf::Animation &GltfFile::get_animation(int index) {
    return get_element<tinygltf::Animation>(index, GET_ELEMENT_LAMBDA(try_get_animation), "animation");
}
    
size_t GltfFile::number_of_nodes() const {
    return _model.nodes.size();
}

size_t GltfFile::number_of_mesh() const {
    return _model.meshes.size();
}

size_t GltfFile::number_of_buffer() const {
    return _model.buffers.size();
}

size_t GltfFile::number_of_bufferview() const {
    return _model.bufferViews.size();
}

size_t GltfFile::number_of_accessors() const {
    return _model.accessors.size();
}

size_t GltfFile::number_of_materials() const {
    return _model.materials.size();
}

size_t GltfFile::number_of_images() const {
    return _model.images.size();
}

size_t GltfFile::number_of_samplers() const {
    return _model.samplers.size();
}

size_t GltfFile::number_of_textures() const {
    return _model.textures.size();
}

size_t GltfFile::number_of_animations() const {
    return _model.animations.size();
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

/***************************************************************************/

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
