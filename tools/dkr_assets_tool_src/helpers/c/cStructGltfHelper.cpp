#include "cStructGltfHelper.h"

void CStructGltfHelper::put_struct_entry_into_gltf_node_extra(CStructEntry *structMember, WriteableGltfFile &gltfFile, int gltfNode, uint8_t *bytes) {
    CStructEntry::InternalType internalType = structMember->get_internal_type();
    
    switch(internalType) {
        case CStructEntry::InternalType::INTEGER:
        {
            int value = structMember->get_integer_from_data(bytes);
            gltfFile.set_node_extra<int>(gltfNode, structMember->name, value);
        }
            break;
        case CStructEntry::InternalType::ARRAY_INTEGER:
        {
            std::vector<int64_t> values;
            structMember->get_values_from_data_array<int64_t>(values, bytes);
            tinygltf::Value::Array arrayOfValues;
            for(int64_t val : values) {
                arrayOfValues.push_back(tinygltf::Value((int)val));
            }
            gltfFile.set_node_extra<tinygltf::Value::Array>(gltfNode, structMember->name, arrayOfValues);
        }
            break;
        case CStructEntry::InternalType::UNKNOWN:
            break; // Do nothing (for now)
        default:
            DebugHelper::error("(CStructGltfHelper::put_struct_entry_into_gltf_node_extra) Type not implemented: ", internalType);
            break;
    }
}

void CStructGltfHelper::put_gltf_node_extra_into_struct_entry(CStructEntry *structMember, GltfFile &gltfFile, int gltfNode, uint8_t *bytes) {
    CStructEntry::InternalType internalType = structMember->get_internal_type();
    
    switch(internalType) {
        case CStructEntry::InternalType::INTEGER:
        {
            int value = gltfFile.get_node_extra<int>(gltfNode, structMember->name, 0);
            structMember->set_integer_to_data(bytes, value);
        }
            break;
        case CStructEntry::InternalType::ARRAY_INTEGER:
        {
            tinygltf::Value::Array arrayOfValues = gltfFile.get_node_extra<tinygltf::Value::Array>(gltfNode, structMember->name, {});
            std::vector<int64_t> values;
            for(tinygltf::Value &val : arrayOfValues) {
                values.push_back(val.GetNumberAsInt());
            }
            structMember->set_values_to_data_array<int64_t>(values, bytes);
            /*
            std::vector<int64_t> values;
            structMember->get_values_from_data_array<int64_t>(values, bytes);
            tinygltf::Value::Array arrayOfValues;
            for(int64_t val : values) {
                arrayOfValues.push_back(tinygltf::Value((int)val));
            }
            gltfFile.set_node_extra<tinygltf::Value::Array>(gltfNode, structMember->name, arrayOfValues);
            */
        }
            break;
        case CStructEntry::InternalType::UNKNOWN:
            break; // Do nothing (for now)
        default:
            DebugHelper::error("(CStructGltfHelper::put_struct_entry_into_gltf_node_extra) Type not implemented: ", internalType);
            break;
    }
}