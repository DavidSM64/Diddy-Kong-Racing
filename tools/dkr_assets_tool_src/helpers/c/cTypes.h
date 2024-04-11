#pragma once

#include <cstddef>
#include <string>

// Class that represents standard c types.
class CTypes {
public:
    static bool is_standard_type(const std::string &typeName);
    
    static size_t get_size_of_type(const std::string &typeName);
    
    static bool is_integer_type(const std::string &typeName);
    static bool is_float_type(const std::string &typeName);
    
    static bool is_signed_type(const std::string &typeName);
    
    static int64_t get_min_int(const std::string &typeName);
    static int64_t get_max_int(const std::string &typeName);
    
    static size_t size_of_pointer();
    
    static bool does_type_have_an_entry(const std::string &typeName);
    
    static int64_t clamp_int(const std::string &typeName, int64_t value);
    
};