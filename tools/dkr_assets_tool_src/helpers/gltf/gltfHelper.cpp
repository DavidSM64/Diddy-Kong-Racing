#include "gltfHelper.h"

#include "helpers/debugHelper.h"
#include "helpers/stringHelper.h"
#include <cmath>
#include <optional>

using namespace DkrAssetsTool;

// The "normalized" functions are taken directly from the glTF 2.0 spec:
/*
+------------------------+----------------------------+------------------------+
| accessor.componentType |        int-to-float        |      float-to-int      |
+------------------------+----------------------------+------------------------+
| signed byte            | f = max(c / 127.0, -1.0)   | c = round(f * 127.0)   |
| unsigned byte          | f = c / 255.0              | c = round(f * 255.0)   |
| signed short           | f = max(c / 32767.0, -1.0) | c = round(f * 32767.0) |
| unsigned short         | f = c / 65535.0            | c = round(f * 65535.0) |
+------------------------+----------------------------+------------------------+
*/

inline float GltfHelper::normalized_byte_to_float(int8_t value) {
    return std::fmax(((float)value) / 127.0f, -1.0);
}

inline float GltfHelper::normalized_ubyte_to_float(uint8_t value) {
    return ((float)value) / 255.0f;
}

inline float GltfHelper::normalized_short_to_float(int16_t value) {
    return std::fmax(((float)value) / 32767.0f, -1.0);
}

inline float GltfHelper::normalized_ushort_to_float(uint16_t value) {
    return ((float)value) / 65535.0f;
}

inline int8_t GltfHelper::float_to_normalized_byte(float value) {
    return std::roundf(value * 127.0f);
}

inline uint8_t GltfHelper::float_to_normalized_ubyte(float value) {
    return std::roundf(value * 255.0f);
}

inline int16_t GltfHelper::float_to_normalized_short(float value) {
    return std::roundf(value * 32767.0f);
}

inline uint16_t GltfHelper::float_to_normalized_ushort(float value) {
    return std::roundf(value * 65535.0f);
}

inline uint8_t GltfHelper::normalized_byte_to_normalized_ubyte(int8_t value) {
    // byte -> float -> ubyte
    return float_to_normalized_ubyte(normalized_byte_to_float(value));
}

inline uint8_t GltfHelper::normalized_short_to_normalized_ubyte(int16_t value) {
    // short -> float -> ubyte
    return float_to_normalized_ubyte(normalized_short_to_float(value));
}

inline uint8_t GltfHelper::normalized_ushort_to_normalized_ubyte(uint16_t value) {
    // ushort -> float -> ubyte
    return float_to_normalized_ubyte(normalized_ushort_to_float(value));
}

/***************************************************************************************************************/

Vec3f GltfHelper::get_node_position(tinygltf::Node &node) {
    if(!node.matrix.empty()) {
        return Vec3f(node.matrix[3], node.matrix[7], node.matrix[11]);
    }
    
    if(node.translation.empty()) {
        return Vec3f();
    }
    
    return Vec3f(node.translation[0], node.translation[1], node.translation[2]);
}

/***************************************************************************************************************/

size_t GltfHelper::get_accessor_count(GltfFile& gltf, int accessorIndex) {
    if (accessorIndex < 0 || accessorIndex >= gltf.number_of_accessors()) {
        return 0;
    }
    
    tinygltf::Accessor &accessor = gltf.get_accessor(accessorIndex);
    return accessor.count;
}

std::optional<std::vector<uint8_t>> GltfHelper::get_indices_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive) {
    int accessorIndex = gltfPrimitive.indices;
    if (accessorIndex < 0) {
        return std::nullopt;
    }

    tinygltf::Accessor &gltfAccessor = gltf.get_accessor(accessorIndex);

    size_t numberOfIndices = gltfAccessor.count;

    switch (gltfAccessor.componentType) {
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
            {
                return get_data_from_accessor<uint8_t>(gltf, accessorIndex);
            }
            break;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
            {
                std::vector<uint16_t> gltfData = get_data_from_accessor<uint16_t>(gltf, accessorIndex);
                std::vector<uint8_t> out(numberOfIndices);
                for (size_t i = 0; i < numberOfIndices; i++) {
                    DebugHelper::assert_(gltfData[i] <= 255,
                        "(GltfHelper::get_indices_from_primitive) uint32_t index is greater than 255: ", gltfData[i]);
                    out[i] = static_cast<uint8_t>(gltfData[i]);
                }
                return out;
            }
            break;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
            {
                std::vector<uint32_t> gltfData = get_data_from_accessor<uint32_t>(gltf, accessorIndex);
                std::vector<uint8_t> out(numberOfIndices);
                for (size_t i = 0; i < numberOfIndices; i++) {
                    DebugHelper::assert_(gltfData[i] <= 255, 
                        "(GltfHelper::get_indices_from_primitive) uint32_t index is greater than 255: ", gltfData[i]);
                    out[i] = static_cast<uint8_t>(gltfData[i]);
                }
                return out;
            }
            break;
        default:
            DebugHelper::error("(GltfHelper::get_indices_from_primitive) Invalid component type for indices: ", gltfAccessor.componentType);
            break;
    }

    return std::nullopt;
}

std::optional<std::vector<float>> GltfHelper::get_positions_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive) {
    int accessorIndex = gltfPrimitive.attributes["POSITION"];
    if (accessorIndex < 0) {
        return std::nullopt;
    }
    return get_data_from_accessor<float>(gltf, accessorIndex);
}

// Returns RGBA unsigned byte array of colors.
std::optional<std::vector<uint8_t>> GltfHelper::get_colors_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive) {
    int accessorIndex = -1;
    
    // First check if the primitive has a color attribute
    if (gltfPrimitive.attributes.find("COLOR_0") != gltfPrimitive.attributes.end()) {
        accessorIndex = gltfPrimitive.attributes["COLOR_0"];
    }
    
    if (accessorIndex < 0) { 
        // No color accessor found? return null.
        return std::nullopt;
    }
    
    tinygltf::Accessor &gltfAccessor = gltf.get_accessor(accessorIndex);

    size_t numberOfColors = gltfAccessor.count;

    // SPEC: Colors can be VEC3(RGB) or VEC4(RGBA) with floats, normalized ubytes, or normalized ushorts.
    //       Alpha is always 1.0 (255) for the VEC3 type
    int type = gltfAccessor.type;

    bool isVec3 = (type == TINYGLTF_TYPE_VEC3), isVec4 = (type == TINYGLTF_TYPE_VEC4);
    DebugHelper::assert_(isVec3 || isVec4,
        "(GltfHelper::get_colors_from_primitive) Invalid accessor type for colors: ", type);

    int dataStride = (isVec4) ? 4 : 3;

    switch (gltfAccessor.componentType) {
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        {
            if (isVec4) {
                // Can be gotten directly.
                return get_data_from_accessor<uint8_t>(gltf, accessorIndex);
            } else {
                std::vector<uint8_t> gltfData = get_data_from_accessor<uint8_t>(gltf, accessorIndex);
                std::vector<uint8_t> out(numberOfColors * 4);
                for (size_t i = 0; i < numberOfColors; i++) {
                    out[i * 4 + 0] = gltfData[i * dataStride + 0];
                    out[i * 4 + 1] = gltfData[i * dataStride + 1];
                    out[i * 4 + 2] = gltfData[i * dataStride + 2];
                    out[i * 4 + 3] = 255;
                }
                return out;
            }
        }
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        {
            // Downconverting from 16-bit color to 8-bit color.
            std::vector<uint16_t> gltfData = get_data_from_accessor<uint16_t>(gltf, accessorIndex);
            std::vector<uint8_t> out(numberOfColors * 4);
            for (size_t i = 0; i < numberOfColors; i++) {
                out[i * 4 + 0] = gltfData[i * dataStride + 0] >> 8;
                out[i * 4 + 1] = gltfData[i * dataStride + 1] >> 8;
                out[i * 4 + 2] = gltfData[i * dataStride + 2] >> 8;
                out[i * 4 + 3] = (isVec4) ? gltfData[i * dataStride + 3] >> 8 : 255;
            }
            return out;
        }
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
        {
            std::vector<float> gltfData = get_data_from_accessor<float>(gltf, accessorIndex);
            std::vector<uint8_t> out(numberOfColors * 4);
            for (size_t i = 0; i < numberOfColors; i++) {
                out[i * 4 + 0] = float_to_normalized_ubyte(gltfData[i * dataStride + 0]);
                out[i * 4 + 1] = float_to_normalized_ubyte(gltfData[i * dataStride + 1]);
                out[i * 4 + 2] = float_to_normalized_ubyte(gltfData[i * dataStride + 2]);
                out[i * 4 + 3] = (isVec4) ? float_to_normalized_ubyte(gltfData[i * dataStride + 3]) : 255;
            }
            return out;
        }
        default:
            DebugHelper::error("(GltfHelper::get_colors_from_primitive) Invalid accessor component type for colors: ", gltfAccessor.componentType);
            break;
    }

    return std::nullopt;
}

std::optional<std::vector<float>> GltfHelper::get_uvs_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive) {
    int accessorIndex = -1;
    if (gltfPrimitive.attributes.find("TEXCOORD_0") != gltfPrimitive.attributes.end()) {
        accessorIndex = gltfPrimitive.attributes["TEXCOORD_0"];
    }

    if (accessorIndex < 0) {
        return std::nullopt;
    }

    tinygltf::Accessor &gltfAccessor = gltf.get_accessor(accessorIndex);

    size_t numberOfUVs = gltfAccessor.count;

    // SPEC: texture coordinates use VEC2 floats, normalized bytes/ubytes, or normalized shorts/ushorts

    switch (gltfAccessor.componentType) {
    case TINYGLTF_COMPONENT_TYPE_BYTE:
    {
        std::vector<int8_t> gltfData = get_data_from_accessor<int8_t>(gltf, accessorIndex);
        std::vector<float> out(numberOfUVs * 2);
        for (size_t i = 0; i < numberOfUVs; i++) {
            out[i * 2 + 0] = normalized_byte_to_float(gltfData[i * 2 + 0]);
            out[i * 2 + 1] = normalized_byte_to_float(gltfData[i * 2 + 1]);
        }
        return out;
    }
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
    {
        std::vector<uint8_t> gltfData = get_data_from_accessor<uint8_t>(gltf, accessorIndex);
        std::vector<float> out(numberOfUVs * 2);
        for (size_t i = 0; i < numberOfUVs; i++) {
            out[i * 2 + 0] = normalized_ubyte_to_float(gltfData[i * 2 + 0]);
            out[i * 2 + 1] = normalized_ubyte_to_float(gltfData[i * 2 + 1]);
        }
        return out;
    }
    case TINYGLTF_COMPONENT_TYPE_SHORT:
    {
        std::vector<int16_t> gltfData = get_data_from_accessor<int16_t>(gltf, accessorIndex);
        std::vector<float> out(numberOfUVs * 2);
        for (size_t i = 0; i < numberOfUVs; i++) {
            out[i * 2 + 0] = normalized_short_to_float(gltfData[i * 2 + 0]);
            out[i * 2 + 1] = normalized_short_to_float(gltfData[i * 2 + 1]);
        }
        return out;
    }
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
    {
        std::vector<uint16_t> gltfData = get_data_from_accessor<uint16_t>(gltf, accessorIndex);
        std::vector<float> out(numberOfUVs * 2);
        for (size_t i = 0; i < numberOfUVs; i++) {
            out[i * 2 + 0] = normalized_ushort_to_float(gltfData[i * 2 + 0]);
            out[i * 2 + 1] = normalized_ushort_to_float(gltfData[i * 2 + 1]);
        }
        return out;
    }
    case TINYGLTF_COMPONENT_TYPE_FLOAT:
    {
        // Can be gotten directly.
        return get_data_from_accessor<float>(gltf, accessorIndex);
    }
    default:
        DebugHelper::error("(GltfHelper::get_colors_from_primitive) Invalid accessor component type for uvs: ", gltfAccessor.componentType);
        break;
    }

    return std::nullopt;
}

std::optional<std::vector<float>> GltfHelper::get_morph_targets_from_primitive(GltfFile& gltf, tinygltf::Primitive& gltfPrimitive) {
    if(gltfPrimitive.targets.empty()) {
        return std::nullopt;
    }
    
    // POSITION is required to exist according to the gltf spec.
    int positionsAccessorIndex = gltfPrimitive.attributes["POSITION"];
    size_t numberOfPositions = get_accessor_count(gltf, positionsAccessorIndex) * 3;
    
    size_t numberOfTargetsWithPositions = 0;
    
    for(auto &targetMap : gltfPrimitive.targets) {
        if(targetMap.find("POSITION") == targetMap.end()) {
            continue;
        }
        numberOfTargetsWithPositions++;
    }
    
    if(numberOfTargetsWithPositions == 0) {
        return std::nullopt;
    }
    
    std::vector<float> out(numberOfPositions * numberOfTargetsWithPositions);
    
    size_t currentTargetWithPositions = 0;
    for(auto &targetMap : gltfPrimitive.targets) {
        if(targetMap.find("POSITION") == targetMap.end()) {
            continue;
        }
        
        int targetAccessor = targetMap.at("POSITION");
        
        if((targetAccessor < 0)) {
            continue;
        }
        
        tinygltf::Accessor &gltfAccessor = gltf.get_accessor(targetAccessor);
    
        DebugHelper::assert_(gltfAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT, 
            "(GltfHelper::get_morph_targets_from_primitive) Morph target positions can only use floats!");
        DebugHelper::assert_(gltfAccessor.type == TINYGLTF_TYPE_VEC3, 
            "(GltfHelper::get_morph_targets_from_primitive) Morph target positions can only be VEC3!");
            
        std::vector<float> targetValues = get_data_from_accessor<float>(gltf, targetAccessor);
        
        std::copy(targetValues.begin(), targetValues.end(), out.begin() + (currentTargetWithPositions * numberOfPositions));
        
        currentTargetWithPositions++;
    }
    
    return out;
}

// Weights can be in multiple formats, not just floats, so this is necessary.
std::optional<std::vector<float>> GltfHelper::get_weights_from_accessor(GltfFile& gltf, int accessorIndex) {
    tinygltf::Accessor &gltfAccessor = gltf.get_accessor(accessorIndex);

    size_t numberOfWeights = gltfAccessor.count;
    
    int compType = gltfAccessor.componentType;

    switch (compType) {
    case TINYGLTF_COMPONENT_TYPE_BYTE:
    {
        std::vector<int8_t> gltfData = get_data_from_accessor<int8_t>(gltf, accessorIndex);
        std::vector<float> out(numberOfWeights);
        for (size_t i = 0; i < numberOfWeights; i++) {
            out[i] = normalized_byte_to_float(gltfData[i]);
        }
        return out;
    }
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
    {
        std::vector<uint8_t> gltfData = get_data_from_accessor<uint8_t>(gltf, accessorIndex);
        std::vector<float> out(numberOfWeights);
        for (size_t i = 0; i < numberOfWeights; i++) {
            out[i] = normalized_ubyte_to_float(gltfData[i]);
        }
        return out;
    }
    case TINYGLTF_COMPONENT_TYPE_SHORT:
    {
        std::vector<int16_t> gltfData = get_data_from_accessor<int16_t>(gltf, accessorIndex);
        std::vector<float> out(numberOfWeights);
        for (size_t i = 0; i < numberOfWeights; i++) {
            out[i] = normalized_short_to_float(gltfData[i]);
        }
        return out;
    }
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
    {
        std::vector<uint16_t> gltfData = get_data_from_accessor<uint16_t>(gltf, accessorIndex);
        std::vector<float> out(numberOfWeights);
        for (size_t i = 0; i < numberOfWeights; i++) {
            out[i] = normalized_ushort_to_float(gltfData[i]);
        }
        return out;
    }
    case TINYGLTF_COMPONENT_TYPE_FLOAT:
    {
        // Can be gotten directly.
        return get_data_from_accessor<float>(gltf, accessorIndex);
    }
    default:
        DebugHelper::error("(GltfHelper::get_weights_from_accessor) Invalid accessor component type for weights: ", gltfAccessor.componentType);
        break;
    }
    
    return std::nullopt;
}

/***************************************************************************************************************/

// Gotta do the json pointer logic myself, because tinygltf doesn't support it.

static inline std::string get_next_section_from_json_pointer(const std::string& jsonPointer) {
    size_t indexOfNextSlash = jsonPointer.find('/', 1);
    if (indexOfNextSlash == jsonPointer.npos) {
        return "/";
    }
    return jsonPointer.substr(indexOfNextSlash);
}

static inline std::string get_current_section_name(const std::string& jsonPointer) {
    size_t indexOfNextSlash = jsonPointer.find('/', 1);
    if (indexOfNextSlash == jsonPointer.npos) {
        return jsonPointer.substr(1);
    }
    return jsonPointer.substr(1, indexOfNextSlash - 1);
}

static tinygltf::Value& get_value_using_json_pointer(tinygltf::Value& parentSection, bool parentIsArray, std::string jsonPointer, bool createUndefinedSections) {
    DebugHelper::assert_(jsonPointer[0] == '/',
        "(GltfHelper::get_value_using_json_pointer) Invalid json pointer \"", jsonPointer, "\", must start with forward slash.");

    std::string currentSectionName = get_current_section_name(jsonPointer);
    bool isANumber = StringHelper::is_a_number(currentSectionName);
    std::string childJsonPointer = get_next_section_from_json_pointer(jsonPointer);
    std::string childSectionName = get_current_section_name(childJsonPointer);
    bool childIsANumber = StringHelper::is_a_number(childSectionName);
    bool isLastSection = childJsonPointer == "/";

    if (parentIsArray) {
        DebugHelper::assert_(isANumber, "(GltfHelper::set_extension_value) Invalid number: ", currentSectionName);
        tinygltf::Value::Array& parentArray = parentSection.Get<tinygltf::Value::Array>();
        int currentIndex = std::stoi(currentSectionName);
        if (parentArray.size() <= currentIndex) {
            parentArray.resize(currentIndex + 1);
        }
        if (parentArray[currentIndex].Type() == tinygltf::NULL_TYPE) {
            if (!createUndefinedSections) {
                throw 1;
            }
            if (childIsANumber) {
                int childIndex = std::stoi(childSectionName);
                parentArray[currentIndex] = tinygltf::Value(tinygltf::Value::Array(childIndex + 1));
            } else {
                parentArray[currentIndex] = tinygltf::Value(tinygltf::Value::Object());
            }
        }
        if (isLastSection) {
            return parentArray[currentIndex];
        } else {
            return get_value_using_json_pointer(parentArray[currentIndex], childIsANumber, childJsonPointer, createUndefinedSections);
        }
    } else {
        DebugHelper::assert_(parentSection.IsObject(),
            "(GltfHelper::get_value_using_json_pointer) Parent is not an object, it is type: ", (int)parentSection.Type());
        tinygltf::Value::Object& parentObject = parentSection.Get<tinygltf::Value::Object>();
        if (!parentSection.Has(currentSectionName)) {
            if (!createUndefinedSections) {
                throw 1;
            }
            if (childIsANumber) {
                int childIndex = std::stoi(childSectionName);
                parentObject[currentSectionName] = tinygltf::Value(tinygltf::Value::Array(childIndex + 1));
            } else {
                parentObject[currentSectionName] = tinygltf::Value(tinygltf::Value::Object());
            }
        }
        if (isLastSection) {
            return parentObject[currentSectionName];
        } else {
            return get_value_using_json_pointer(parentObject[currentSectionName], childIsANumber, childJsonPointer, createUndefinedSections);
        }
    }
}

/***************************************************************************************************************/

Mat4x4f GltfHelper::calculate_node_matrix(tinygltf::Node &node, const Mat4x4f &parentMatrix) {
    if(node.matrix.size() > 0) {
        return parentMatrix * Mat4x4f(node.matrix);
    }
    
    if(node.translation.empty() && node.rotation.empty() && node.scale.empty()) {
        return parentMatrix;
    }
    
    Vec3f translation = (node.translation.empty()) ? Vec3f() : Vec3f(node.translation);
    Vec4f rotation = (node.rotation.empty()) ? Vec4f() : Vec4f(node.rotation);
    Vec3f scale = (node.scale.empty()) ? Vec3f(1, 1, 1) : Vec3f(node.scale);
    
    return parentMatrix * Mat4x4f(translation, rotation, scale);
}

/***************************************************************************************************************/

template <typename T>
void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, T value) {
    if (!extras.IsObject()) {
        extras = tinygltf::Value(tinygltf::Value::Object());
    }

    tinygltf::Value& extrasValueToSet = get_value_using_json_pointer(extras, false, jsonPointer, true);

    extrasValueToSet = tinygltf::Value(value);
}

template void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, std::string value);
template void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, int value);
template void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, double value);
template void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, bool value);
template void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, tinygltf::Value::Array& value);

template <typename T>
void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, std::vector<T>& values) {
    if (!extras.IsObject()) {
        extras = tinygltf::Value(tinygltf::Value::Object());
    }

    tinygltf::Value& extrasValueToSet = get_value_using_json_pointer(extras, false, jsonPointer, true);

    tinygltf::Value::Array tinygltfValues;

    for (T& value : values) {
        tinygltfValues.push_back(tinygltf::Value(value));
    }

    extrasValueToSet = tinygltf::Value(tinygltfValues);
}

template void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, std::vector<std::string>& values);
template void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, std::vector<int>& values);
template void GltfHelper::set_extra(tinygltf::Value& extras, std::string jsonPointer, std::vector<double>& values);

template <typename T>
T GltfHelper::get_extra(tinygltf::Value& extras, std::string jsonPointer, T defaultValue) {
    if (!extras.IsObject()) {
        // This node does not have any extras, just return the default value.
        return defaultValue;
    }

    try {
        tinygltf::Value& extrasValue = get_value_using_json_pointer(extras, false, jsonPointer, false);
        return extrasValue.Get<T>();
    } catch (int e) {
        return defaultValue;
    }
}

template std::string GltfHelper::get_extra(tinygltf::Value& extras, std::string jsonPointer, std::string defaultValue);
template int GltfHelper::get_extra(tinygltf::Value& extras, std::string jsonPointer, int defaultValue);
template double GltfHelper::get_extra(tinygltf::Value& extras, std::string jsonPointer, double defaultValue);
template bool GltfHelper::get_extra(tinygltf::Value& extras, std::string jsonPointer, bool defaultValue);
template tinygltf::Value::Array GltfHelper::get_extra(tinygltf::Value& extras, std::string jsonPointer, tinygltf::Value::Array defaultValue);
template tinygltf::Value::Object GltfHelper::get_extra(tinygltf::Value& extras, std::string jsonPointer, tinygltf::Value::Object defaultValue);

bool GltfHelper::has_extra(tinygltf::Value& extras, std::string jsonPointer) {
    if (!extras.IsObject()) {
        return false; // Not an object, so it definitely doesn't have the key.
    }
    try {
        tinygltf::Value& extrasValue = get_value_using_json_pointer(extras, false, jsonPointer, false);
        return extrasValue.Type() != tinygltf::NULL_TYPE;
    } catch (int e) {
        return false;
    }
}

int GltfHelper::get_extra_type(tinygltf::Value& extras, std::string jsonPointer) {
    if (!extras.IsObject()) {
        return tinygltf::NULL_TYPE; // Not an object, so it definitely doesn't have the key.
    }
    try {
        tinygltf::Value& extrasValue = get_value_using_json_pointer(extras, false, jsonPointer, false);
        return extrasValue.Type();
    } catch (int e) {
        return tinygltf::NULL_TYPE;
    }
}

std::optional<std::vector<std::string>> GltfHelper::get_extra_keys(tinygltf::Value& extras, std::string jsonPointer) {
    try {
        tinygltf::Value& extrasValue = get_value_using_json_pointer(extras, false, jsonPointer, false);
        if (extrasValue.Type() != tinygltf::OBJECT_TYPE) {
            return std::nullopt; // Return null if the type is not an object.
        }
        if (extrasValue.Size() < 1) {
            return std::nullopt; // Return null if the object is empty.
        }
        return extrasValue.Keys();
    } catch (int e) {
        return std::nullopt; // Return null if the extra value doesn't exist.
    }
}

template <typename T>
void GltfHelper::get_extra_array(tinygltf::Value& extras, std::string jsonPointer, std::vector<T>& outValues) {
    outValues.clear();

    if (!extras.IsObject()) {
        // This node does not have any extras.
        return;
    }

    try {
        tinygltf::Value& extrasValue = get_value_using_json_pointer(extras, false, jsonPointer, false);

        if (!extrasValue.IsArray()) {
            DebugHelper::error("(GltfHelper::get_extra) \"", jsonPointer, "\" should be an array, but it is not!");
            return;
        }


        tinygltf::Value::Array tinygltfValues = extrasValue.Get<tinygltf::Value::Array>();

        for (tinygltf::Value& arrVal : tinygltfValues) {
            outValues.push_back(arrVal.Get<T>());
        }
    } catch (int e) {
    }
}

template void GltfHelper::get_extra_array(tinygltf::Value& extras, std::string jsonPointer, std::vector<std::string>& outValues);
template void GltfHelper::get_extra_array(tinygltf::Value& extras, std::string jsonPointer, std::vector<int>& outValues);
template void GltfHelper::get_extra_array(tinygltf::Value& extras, std::string jsonPointer, std::vector<double>& outValues);
template void GltfHelper::get_extra_array(tinygltf::Value& extras, std::string jsonPointer, std::vector<bool>& outValues);
template void GltfHelper::get_extra_array(tinygltf::Value& extras, std::string jsonPointer, std::vector<tinygltf::Value::Array>& outValues);
template void GltfHelper::get_extra_array(tinygltf::Value& extras, std::string jsonPointer, std::vector<tinygltf::Value::Object>& outValues);

template<typename T>
void GltfHelper::set_extension_value(tinygltf::ExtensionMap& extensions, std::string jsonPointer, T value) {
    DebugHelper::assert_(!jsonPointer.empty(), "(GltfHelper::set_extension_value) jsonPointer was empty!");

    std::string sectionName = get_current_section_name(jsonPointer);

    if (extensions.find(sectionName) == extensions.end()) {
        extensions[sectionName] = tinygltf::Value(tinygltf::Value::Object());
    }

    tinygltf::Value &extensionValue = get_value_using_json_pointer(extensions[sectionName], false, 
        get_next_section_from_json_pointer(jsonPointer), true);

    extensionValue = tinygltf::Value(value);
}

template void GltfHelper::set_extension_value(tinygltf::ExtensionMap& extensions, std::string jsonPointer, std::string value);
template void GltfHelper::set_extension_value(tinygltf::ExtensionMap& extensions, std::string jsonPointer, int value);
template void GltfHelper::set_extension_value(tinygltf::ExtensionMap& extensions, std::string jsonPointer, double value);
template void GltfHelper::set_extension_value(tinygltf::ExtensionMap& extensions, std::string jsonPointer, bool value);
