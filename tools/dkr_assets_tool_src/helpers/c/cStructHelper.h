#pragma once

#include "helpers/fileHelper.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <any>

namespace DkrAssetsTool {

class CContext;
class CStruct;

// Represents an entry of a C structure.
struct CStructEntry {
    
    enum InternalType {
        // default value
        NOT_SET, 
        // Single value types
        INTEGER,
        POINTER,
        FLOAT,
        STRUCT_UNION,
        // Array types
        ARRAY_INTEGER,
        ARRAY_POINTER,
        ARRAY_FLOAT,
        ARRAY_STRUCT_UNION,
        // Not any recognized value.
        UNKNOWN,
        NUMBER_OF_VALUE_TYPES = 4
    };
    
    std::string type;
    std::string pointer;
    std::string name;
    std::string arrayBrackets;
    
    CStruct *innerStruct = nullptr; // Only used in struct/union type.
    
    CStructEntry(CContext *context, CStruct *parent, std::string &type, std::string &pointer, std::string &name, 
        std::string &arrayBrackets, std::string hint);
    bool is_pointer_to_type();
    bool is_array();
    
    bool has_hint();
    std::string get_hint_type(); // What type of hint does this member have?
    std::string get_hint_value(const std::string hintKey);
    
    // Returns the default value if the key isn't in the hint map.
    std::string get_hint_value(const std::string hintKey, std::string defaultValue);
    
    std::string to_string();
    
    bool is_type_trivial();
    
    InternalType get_internal_type();
    void update_internal_type();
    bool is_internal_type(const InternalType internalType);
    bool is_integer_type();
    bool is_float_type();
    bool is_pointer_type(); // Checks `_internalType` instead of `pointer`
    bool is_array_of_integers();
    bool is_array_of_floats();
    bool is_array_of_pointers();
    bool is_array_of_structs_or_unions();
    
    size_t get_array_multiplier();
    size_t get_byte_size();
    
    std::string get_display_name();
    
    int64_t get_integer_from_data(uint8_t *data, bool isBigEndian=true);
    void set_integer_to_data(uint8_t *data, int64_t value, bool isBigEndian=true);
    
    template<typename T>
    void get_values_from_data_array(std::vector<T> &out, uint8_t *data, bool isBigEndian=true);
    
    template<typename T>
    void set_values_to_data_array(std::vector<T> &in, uint8_t *data, bool isBigEndian=true);
    
    int get_offset();
    void set_offset(int newOffset); // Note: Should only be called by the parent cstruct.
    
    CContext *get_context();
private:
    // The hint map is specifically used for Object Maps.
    std::unordered_map<std::string, std::string> _hintMap;
    void _generate_hint_map(std::string &hint);
    
    CContext *_context;
    CStruct *_parent;
    InternalType _internalType = InternalType::NOT_SET;
    int _offset = -1; // Is only calculated if get_offset is called.
    bool _isSignedType;


    size_t _arrayMultiplier;
    
    void _calc_array_multiplier();
    
};

// Class that represents a structure in a C file.
class CStruct {
public:
    CStruct(CContext *context); // Empty struct
    CStruct(CContext *context, const std::string &rawCode); // Parse from a struct string.
    ~CStruct();
    
    std::string get_name();
    bool is_a_union();
    bool is_anonymous();
    
    std::string to_string();
    
    CStructEntry *get_entry(size_t entryIndex);
    size_t entry_count();
    
    size_t get_byte_size();
    bool is_trivial();
    
    void calculate_offsets(int currentOffset = 0);
    
private:
    CContext *_context;
    
    std::vector<CStructEntry*> _entries;
    std::string _name = "";
    std::string _typedefName = "";
    bool _isUnion = false;
    
    // "Trivial" meaning that the byte size of the struct can be easily calculated.
    bool _isTrivial = false;
    
    void _calc_trivialness();
};

/**
 * Class that deals with reading / creating C structs.
 */
class CStructHelper {
public:
    //static void get_struct_from_c_file(const std::string &filepath, const std::string &structName, CStruct &out);
    static void get_structs_from_code(CContext *context, const std::string &code, std::vector<CStruct*> &out);
    static void load_structs_from_file(CContext *context, fs::path filepath);
};

}
