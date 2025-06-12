#pragma once

#include <cstdint>
#include <optional>

#include "gltfFile.h"

#include "helpers/mathHelper.h"
#include "libs/bytes_view.hpp"

namespace DkrAssetsTool {

namespace GltfHelper {
    // These functions are simple enough that they can be inlined.
    inline float    normalized_byte_to_float(int8_t value);
    inline float    normalized_ubyte_to_float(uint8_t value);
    inline float    normalized_short_to_float(int16_t value);
    inline float    normalized_ushort_to_float(uint16_t value);
    inline int8_t   float_to_normalized_byte(float value);
    inline uint8_t  float_to_normalized_ubyte(float value);
    inline int16_t  float_to_normalized_short(float value);
    inline uint16_t float_to_normalized_ushort(float value);
    inline uint8_t  normalized_byte_to_normalized_ubyte(int8_t value);
    inline uint8_t  normalized_short_to_normalized_ubyte(int16_t value);
    inline uint8_t  normalized_ushort_to_normalized_ubyte(uint16_t value);
    
    Vec3f get_node_position(tinygltf::Node &objNode);

    template<typename T>
    T* get_buffer_pointer(tinygltf::BufferView& bufferView, tinygltf::Buffer& buffer, size_t offset) {
        return reinterpret_cast<T*>(&buffer.data[bufferView.byteOffset + offset]);
    }
    
    template<typename T>
    std::vector<T> get_data_from_bufferview(GltfFile& gltf, int bufferViewIndex) {
        tinygltf::BufferView &bufferView = gltf.get_bufferview(bufferViewIndex);
        tinygltf::Buffer &buffer = gltf.get_buffer(bufferView.buffer);
        
        T *start = reinterpret_cast<T*>(&buffer.data[bufferView.byteOffset]);
        T *end = reinterpret_cast<T*>(&buffer.data[bufferView.byteOffset + bufferView.byteLength]);
        
        return std::vector<T>(start, end);
    }
    
    // Returns 0 if the accessorIndex was invalid.
    size_t get_accessor_count(GltfFile& gltf, int accessorIndex);
    
    template<typename T, typename T2>
    static void _write_modified_sparse_data(std::vector<T> &dst, const std::vector<T> &src, GltfFile& gltf, tinygltf::Accessor &accessor) {
        size_t elementStride = tinygltf::GetNumComponentsInType(accessor.type);
        std::vector<T2> indices = get_data_from_bufferview<T2>(gltf, accessor.sparse.indices.bufferView);
        for(size_t i = 0; i < accessor.sparse.count; i++) {
            auto srcStart = src.begin() + (i * elementStride), srcEnd = srcStart + elementStride;
            auto dstStart = dst.begin() + (indices[i] * elementStride);
            std::copy(srcStart, srcEnd, dstStart);
        }
    }
    
    template<typename T>
    static void modify_data_using_sparse_accessor(std::vector<T> &data, GltfFile& gltf, tinygltf::Accessor &accessor) {
        if(!accessor.sparse.isSparse) {
            return; // If the accessor doesn't have any sparse data, then just exit.
        }
        
        std::vector<T> values = get_data_from_bufferview<T>(gltf, accessor.sparse.values.bufferView);
        
        switch(accessor.sparse.indices.componentType) {
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
            _write_modified_sparse_data<T, uint8_t>(data, values, gltf, accessor);
            break;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
            _write_modified_sparse_data<T, uint16_t>(data, values, gltf, accessor);
            break;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
            _write_modified_sparse_data<T, uint32_t>(data, values, gltf, accessor);
            break;
        default:
            DebugHelper::error("(GltfHelper::modify_data_using_sparse_accessor) Invalid component type for indices: ", 
                accessor.sparse.indices.componentType);
            break;
        }
    }
    
    // Cannot return a reference, because the accessor could have no bufferView or be modified from a sparse accessor.
    template <typename T>
    static std::vector<T> get_data_from_accessor(GltfFile& gltf, int accessorIndex) {
        tinygltf::Accessor &accessor = gltf.get_accessor(accessorIndex);
        
        if(accessor.bufferView == -1) {
            std::vector<T> out(accessor.count * tinygltf::GetNumComponentsInType(accessor.type)); // Empty array filled with zeroes.
            modify_data_using_sparse_accessor(out, gltf, accessor);
            return out;
        }
        
        std::vector<T> out = get_data_from_bufferview<T>(gltf, accessor.bufferView);
        modify_data_using_sparse_accessor(out, gltf, accessor);
        return out;
    }

    std::optional<std::vector<uint8_t>> get_indices_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive);
    std::optional<std::vector<float>> get_positions_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive);
    std::optional<std::vector<uint8_t>> get_colors_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive);
    std::optional<std::vector<float>> get_uvs_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive);
    
    std::optional<std::vector<float>> get_morph_targets_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive);
    
    // Weights can be in multiple formats, not just floats, so this is necessary.
    std::optional<std::vector<float>> get_weights_from_accessor(GltfFile& gltf, int accessorIndex);
    
    // Generic version for non-standard gltf data.
    template <typename T>
    std::vector<T> get_data_from_accessor(GltfFile& gltf, int accessorIndex);
    
    Mat4x4f calculate_node_matrix(tinygltf::Node &node, const Mat4x4f &parentMatrix);

    template <typename T>
    void set_extra(tinygltf::Value& extras, std::string jsonPointer, T value);

    template <typename T>
    void set_extra(tinygltf::Value& extras, std::string jsonPointer, std::vector<T>& values);

    template <typename T>
    T get_extra(tinygltf::Value& extras, std::string jsonPointer, T defaultValue);

    bool has_extra(tinygltf::Value& extras, std::string jsonPointer);

    int get_extra_type(tinygltf::Value& extras, std::string jsonPointer);

    template <typename T>
    void get_extra_array(tinygltf::Value& extras, std::string jsonPointer, std::vector<T>& outValues);

    // Returns nullopt if jsonPointer doesn't exist, is the wrong type, or the object has no keys.
    std::optional<std::vector<std::string>> get_extra_keys(tinygltf::Value& extras, std::string jsonPointer);

    template <typename T>
    void set_extension_value(tinygltf::ExtensionMap &extensions, std::string jsonPointer, T value);
};

}