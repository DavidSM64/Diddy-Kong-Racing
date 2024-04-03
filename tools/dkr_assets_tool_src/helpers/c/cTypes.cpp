#include "cTypes.h"

#include <unordered_map>
#include "helpers/debugHelper.h"

enum CTypeCategory {
    CTYPE_INTEGER,
    CTYPE_FLOAT
};

struct CTypeInfo {
    size_t size;
    CTypeCategory category;
};

// TODO: Is there a better way to do this?
// Note: sizes according to N64 hardware.
std::unordered_map<std::string, CTypeInfo> typeInfos = {
    // 1 byte types
    { "char", {1, CTYPE_INTEGER}},
    { "signed char", {1, CTYPE_INTEGER}},
    { "unsigned char", {1, CTYPE_INTEGER}},
    { "s8", {1, CTYPE_INTEGER}},
    { "u8", {1, CTYPE_INTEGER}},
    // 2 byte types
    { "short", {2, CTYPE_INTEGER}},
    { "signed short", {2, CTYPE_INTEGER}},
    { "unsigned short", {2, CTYPE_INTEGER}},
    { "short int", {2, CTYPE_INTEGER}},
    { "signed short int", {2, CTYPE_INTEGER}},
    { "unsigned short int", {2, CTYPE_INTEGER}},
    { "s16", {2, CTYPE_INTEGER}},
    { "u16", {2, CTYPE_INTEGER}},
    // 4 byte types
    { "int", {4, CTYPE_INTEGER}},
    { "signed int", {4, CTYPE_INTEGER}},
    { "unsigned int", {4, CTYPE_INTEGER}},
    { "long", {4, CTYPE_INTEGER}}, // long is 32-bits on N64
    { "signed long", {4, CTYPE_INTEGER}},  
    { "unsigned long", {4, CTYPE_INTEGER}},
    { "s32", {4, CTYPE_INTEGER}},
    { "u32", {4, CTYPE_INTEGER}},
    { "float", {4, CTYPE_FLOAT}},
    { "f32", {4, CTYPE_FLOAT}},
    // 8 byte types
    { "long long int", {8, CTYPE_INTEGER}},
    { "signed long long int", {8, CTYPE_INTEGER}},
    { "unsigned long long int", {8, CTYPE_INTEGER}},
    { "s64", {8, CTYPE_INTEGER}},
    { "u64", {8, CTYPE_INTEGER}},
    { "double", {8, CTYPE_FLOAT}},
    { "f64", {8, CTYPE_FLOAT}},
};

bool CTypes::is_standard_type(const std::string &typeName) {
    if(typeName.empty()) {
        return false; // Empty string is no type at all.
    }
    auto found = typeInfos.find(typeName);
    if(found == typeInfos.end()) {
        return false; // Invalid type
    }
    return true;
}

size_t CTypes::get_size_of_type(const std::string &typeName) {
    if(!CTypes::is_standard_type(typeName)) {
        return 0;
    }
    return typeInfos[typeName].size;
}

bool CTypes::is_integer_type(const std::string &typeName) {
    if(!CTypes::is_standard_type(typeName)) {
        return false;
    }
    return typeInfos[typeName].category == CTypeCategory::CTYPE_INTEGER;
}

bool CTypes::is_float_type(const std::string &typeName) {
    if(!CTypes::is_standard_type(typeName)) {
        return false;
    }
    return typeInfos[typeName].category == CTypeCategory::CTYPE_FLOAT;
}

size_t CTypes::size_of_pointer() {
    return 4; // Note: Assuming N64 platform.
}

