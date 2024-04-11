#include "cTypes.h"

#include <climits>
#include <unordered_map>
#include "helpers/debugHelper.h"

enum CTypeCategory {
    CTYPE_INTEGER,
    CTYPE_FLOAT
};

struct MinMaxInfo {
    int64_t minInt;
    uint64_t maxInt;
};

struct CTypeInfo {
    size_t size;
    CTypeCategory category;
    bool isSigned;
    MinMaxInfo minMaxInfo;
};

// Min/Max ranges
const MinMaxInfo mmi_s8 = { INT8_MIN, INT8_MAX };
const MinMaxInfo mmi_u8 = { 0, UINT8_MAX };
const MinMaxInfo mmi_s16 = { SHRT_MIN, SHRT_MAX };
const MinMaxInfo mmi_u16 = { 0, USHRT_MAX };
const MinMaxInfo mmi_s32 = { LONG_MIN, LONG_MAX };
const MinMaxInfo mmi_u32 = { 0, ULONG_MAX };
const MinMaxInfo mmi_s64 = { LLONG_MIN, LLONG_MAX };
const MinMaxInfo mmi_u64 = { 0, ULLONG_MAX };


// TODO: Is there a better way to do this?
// Note: sizes according to N64 hardware.
std::unordered_map<std::string, CTypeInfo> typeInfos = {
    // 1 byte types
    { "char", {1, CTYPE_INTEGER, true, mmi_s8}},
    { "signed char", {1, CTYPE_INTEGER, true, mmi_s8}},
    { "unsigned char", {1, CTYPE_INTEGER, false, mmi_u8}},
    { "s8", {1, CTYPE_INTEGER, true, mmi_s8}},
    { "u8", {1, CTYPE_INTEGER, false, mmi_u8}},
    // 2 byte types
    { "short", {2, CTYPE_INTEGER, true, mmi_s16}},
    { "signed short", {2, CTYPE_INTEGER, true, mmi_s16}},
    { "unsigned short", {2, CTYPE_INTEGER, false, mmi_u16}},
    { "short int", {2, CTYPE_INTEGER, true, mmi_s16}},
    { "signed short int", {2, CTYPE_INTEGER, true, mmi_s16}},
    { "unsigned short int", {2, CTYPE_INTEGER, false, mmi_u16}},
    { "s16", {2, CTYPE_INTEGER, true, mmi_s16}},
    { "u16", {2, CTYPE_INTEGER, false, mmi_u16}},
    // 4 byte types
    { "int", {4, CTYPE_INTEGER, true, mmi_s32}},
    { "signed int", {4, CTYPE_INTEGER, true, mmi_s32}},
    { "unsigned int", {4, CTYPE_INTEGER, false, mmi_u32}},
    { "long", {4, CTYPE_INTEGER, true, mmi_s32}}, // long is 32-bits on N64
    { "signed long", {4, CTYPE_INTEGER, true, mmi_s32}},  
    { "unsigned long", {4, CTYPE_INTEGER, false, mmi_u32}},
    { "s32", {4, CTYPE_INTEGER, true, mmi_s32}},
    { "u32", {4, CTYPE_INTEGER, false, mmi_u32}},
    { "float", {4, CTYPE_FLOAT, false}},
    { "f32", {4, CTYPE_FLOAT, false}},
    // 8 byte types
    { "long long int", {8, CTYPE_INTEGER, true, mmi_s64}},
    { "signed long long int", {8, CTYPE_INTEGER, true, mmi_s64}},
    { "unsigned long long int", {8, CTYPE_INTEGER, false, mmi_u64}},
    { "s64", {8, CTYPE_INTEGER, true, mmi_s64}},
    { "u64", {8, CTYPE_INTEGER, false, mmi_u64}},
    { "double", {8, CTYPE_FLOAT, false}},
    { "f64", {8, CTYPE_FLOAT, false}},
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

bool CTypes::is_signed_type(const std::string &typeName) {
    if(!CTypes::is_standard_type(typeName)) {
        return false;
    }
    return typeInfos[typeName].isSigned;
}

int64_t CTypes::get_min_int(const std::string &typeName) {
    DebugHelper::assert(CTypes::is_standard_type(typeName),
        "(CTypes::get_min_int) Type ", typeName, " is not a standard type!");
    return typeInfos[typeName].minMaxInfo.minInt;
}

int64_t CTypes::get_max_int(const std::string &typeName) {
    DebugHelper::assert(CTypes::is_standard_type(typeName),
        "(CTypes::get_max_int) Type ", typeName, " is not a standard type!");
    return typeInfos[typeName].minMaxInfo.maxInt;
}

size_t CTypes::size_of_pointer() {
    return 4; // Note: Assuming N64 platform.
}

int64_t CTypes::clamp_int(const std::string &typeName, int64_t value) {
    if(!CTypes::is_standard_type(typeName)) {
        return value;
    }
    if(typeInfos[typeName].category != CTypeCategory::CTYPE_INTEGER) {
        return value;
    }
    if(value < typeInfos[typeName].minMaxInfo.minInt) {
        return typeInfos[typeName].minMaxInfo.minInt;
    } 
    if(value > typeInfos[typeName].minMaxInfo.maxInt) {
        return typeInfos[typeName].minMaxInfo.maxInt;
    }
    return value;
}
