#pragma once

#include <cstddef>
#include <string>

#include <unordered_map>

#include "helpers/c/cStructHelper.h"
#include "helpers/c/cEnumsHelper.h"

namespace DkrAssetsTool {

class CContext {
public:
    CContext();
    ~CContext();
    
    // Structures / Unions
    void register_struct(CStruct *structRef);
    void deregister_struct(std::string &structName);
    CStruct *get_struct(const std::string &structName) const;
    size_t get_size_of_element(const std::string &elementName);
    void clear_structs();
    
    // Enums
    void register_enum(CEnum *enumRef);
    void deregister_enum(std::string &enumName);
    CEnum *get_enum(const std::string &enumName) const;
    void clear_enums();
    
    // General
    int get_int_value_of_symbol(const std::string &symbolName) const;
    
    std::string get_symbol_of_enum_int(std::string enumName, int index) const;
    
private:
    std::unordered_map<std::string, CStruct*> _structsByName; 
    std::unordered_map<std::string, CEnum*> _enumsByName; 
    std::unordered_map<std::string, int> _enumValues;
    
    void _add_enum_values(CEnum *enumRef);
};

}
