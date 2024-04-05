#include "cStructGltfHelper.h"

#include "helpers/c/cContext.h"
#include "helpers/c/cTypes.h"

enum StructHintType {
    NO_HINT,
    ENUM, // An enum from include/enums.h
    ASSET_ID,
    ANGLE, // Converts angle byte into degrees.
    SCALE  // Divide by some number to get a float representation of scale.
};

std::unordered_map<std::string, StructHintType> hintTypes = {
    { "Enum", StructHintType::ENUM },
    { "Angle", StructHintType::ANGLE }
};

// Gets an enum symbol from a struct member and an integer value.
// Assumption: structMember has the "Enum" hint.
std::string get_hint_enum_value(CStructEntry *structMember, int value) {
    std::string enumName = structMember->get_hint_value("Enum");
    CContext *context = structMember->get_context();
    CEnum *hintEnum = context->get_enum(enumName);
    std::string enumValue;
    
    DebugHelper::assert_(hintEnum->get_symbol_of_value(value, enumValue), 
        "(get_hint_enum_value) Enum ", enumName, 
        " does not have a symbol for the value ", value);
        
    return enumValue;
}

// Get the integer value from an enum value string.
// Assumption: structMember has the "Enum" hint.
int get_value_from_hint_enum(CStructEntry *structMember, std::string &enumValue) {
    std::string enumName = structMember->get_hint_value("Enum");
    CContext *context = structMember->get_context();
    CEnum *hintEnum = context->get_enum(enumName);
    int value;
    
    DebugHelper::assert_(hintEnum->get_value_of_member(enumValue, value), 
        "(get_value_from_hint_enum) Enum ", enumName, 
        " does not have a value for the symbol ", enumValue);
        
    return value;
}

double get_hint_angle(CStructEntry *structMember, int value) {
    std::string divideByStr = structMember->get_hint_value("DivideBy", "64");
    double divideBy = std::stod(divideByStr);
    
    double angle = (value / divideBy) * 360.0; // Convert value to degrees
    
    // *Probably* meant to be negative; convert the unsigned value to a signed value.
    if((angle > 360.0) && (!CTypes::is_signed_type(structMember->type))) { 
        int64_t maxValuePlusOne = CTypes::get_max_int(structMember->type) + 1;
        double maxAngle = (maxValuePlusOne / divideBy) * 360.0;
        angle -= maxAngle; // convert angle to a signed value.
    }
    
    return angle;
}

int get_value_from_hint_angle(CStructEntry *structMember, double angle) {
    std::string divideByStr = structMember->get_hint_value("DivideBy", "64");
    double divideBy = std::stod(divideByStr);
    
    if((angle < 0.0) && (!CTypes::is_signed_type(structMember->type))) {
        // convert angle back to a unsigned type.
        int64_t maxValuePlusOne = CTypes::get_max_int(structMember->type) + 1;
        double maxAngle = (maxValuePlusOne / divideBy) * 360.0;
        angle += maxAngle; // convert angle back to unsigned.
    }
    
    int out = (int)((angle / 360.0) * divideBy); // Convert from degrees
    return CTypes::clamp_int(structMember->type, out);
}

void CStructGltfHelper::put_struct_entry_into_gltf_node_extra(CStructEntry *structMember, WriteableGltfFile &gltfFile, int gltfNode, uint8_t *bytes) {
    CStructEntry::InternalType internalType = structMember->get_internal_type();
    StructHintType hintType = StructHintType::NO_HINT;
    if(structMember->has_hint()) {
        hintType = hintTypes[structMember->get_hint_type()];
    }
    switch(internalType) {
        case CStructEntry::InternalType::INTEGER:
        {
            int value = structMember->get_integer_from_data(bytes);
            switch(hintType) {
                case StructHintType::NO_HINT:
                    gltfFile.set_node_extra<int>(gltfNode, structMember->name, value);
                    break;
                case StructHintType::ENUM:
                {
                    std::string enumValue = get_hint_enum_value(structMember, value);
                    gltfFile.set_node_extra<std::string>(gltfNode, structMember->name, enumValue);
                    break;
                }
                case StructHintType::ANGLE:
                {
                    double angle = get_hint_angle(structMember, value);
                    gltfFile.set_node_extra<double>(gltfNode, structMember->name, angle);
                    break;
                }
                default:
                    DebugHelper::error("Unimplemented hint type: ", structMember->get_hint_type());
                    break;
            }
            break;
        }
        case CStructEntry::InternalType::ARRAY_INTEGER:
        {
            std::vector<int64_t> values;
            structMember->get_values_from_data_array<int64_t>(values, bytes);
            tinygltf::Value::Array arrayOfValues;
            for(int64_t value : values) {
                // TODO: This looks pretty similar to the InternalType::INTEGER case. Can I make this a common function?
                switch(hintType) {
                    case StructHintType::NO_HINT:
                        arrayOfValues.push_back(tinygltf::Value((int)value));
                        break;
                    case StructHintType::ENUM:
                    {
                        std::string enumValue = get_hint_enum_value(structMember, value);
                        arrayOfValues.push_back(tinygltf::Value(enumValue));
                        break;
                    }
                    case StructHintType::ANGLE:
                    {
                        double angle = get_hint_angle(structMember, value);
                        arrayOfValues.push_back(tinygltf::Value(angle));
                        break;
                    }
                    default:
                        DebugHelper::error("Unimplemented hint type: ", structMember->get_hint_type());
                        break;
                }
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
    StructHintType hintType = StructHintType::NO_HINT;
    if(structMember->has_hint()) {
        hintType = hintTypes[structMember->get_hint_type()];
    }
    
    switch(internalType) {
        case CStructEntry::InternalType::INTEGER:
        {
            int value = 0;
            switch(hintType) {
                case StructHintType::NO_HINT:
                    value = gltfFile.get_node_extra<int>(gltfNode, structMember->name, 0);
                    break;
                case StructHintType::ENUM:
                {
                    std::string enumValue = gltfFile.get_node_extra<std::string>(gltfNode, structMember->name, "");
                    value = get_value_from_hint_enum(structMember, enumValue);
                    break;
                }
                case StructHintType::ANGLE:
                {
                    double angle = gltfFile.get_node_extra<double>(gltfNode, structMember->name, 0.0);
                    value = get_value_from_hint_angle(structMember, angle);
                    break;
                }
                default:
                    DebugHelper::error("Unimplemented hint type: ", structMember->get_hint_type());
                    break;
            }
            structMember->set_integer_to_data(bytes, value);
            break;
        }
        case CStructEntry::InternalType::ARRAY_INTEGER:
        {
            tinygltf::Value::Array arrayOfValues = gltfFile.get_node_extra<tinygltf::Value::Array>(gltfNode, structMember->name, {});
            std::vector<int64_t> values;
            for(tinygltf::Value &val : arrayOfValues) {
                switch(hintType) {
                    case StructHintType::NO_HINT:
                        values.push_back(val.GetNumberAsInt());
                        break;
                    case StructHintType::ENUM:
                        values.push_back(get_value_from_hint_enum(structMember, val.Get<std::string>()));
                        break;
                    case StructHintType::ANGLE:
                        values.push_back(get_value_from_hint_angle(structMember, val.Get<double>()));
                        break;
                    default:
                        DebugHelper::error("Unimplemented hint type: ", structMember->get_hint_type());
                        break;
                }
                
            }
            structMember->set_values_to_data_array<int64_t>(values, bytes);
            break;
        }
        case CStructEntry::InternalType::UNKNOWN:
            break; // Do nothing (for now)
        default:
            DebugHelper::error("(CStructGltfHelper::put_struct_entry_into_gltf_node_extra) Type not implemented: ", internalType);
            break;
    }
}
