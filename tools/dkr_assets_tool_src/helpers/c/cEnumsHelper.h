#pragma once

#include "helpers/fileHelper.h"

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>

namespace DkrAssetsTool {

class CContext;

class CEnum {
public:
    CEnum(CContext &context); // Empty enum
    CEnum(CContext &context, const std::string &rawCode); // Parse from a enum string.
    ~CEnum();
    
    friend std::ostream& operator<<(std::ostream& os, const CEnum& cEnum);
    
    std::string get_name() const;
    
    // Used in CContext.
    void copy_members_to_map(std::unordered_map<std::string, int> &inputMap);
    
    // Returns true if key was found in the _members map.
    bool get_value_of_member(const std::string &memberKey, int &out);
    
    bool get_symbol_of_value(int value, std::string &outSymbol);
    
    size_t get_member_count() const;
    
    // "simple" here just means an enum that starts at 0 and increases by 1 for each value.
    bool is_simple() const;
    std::string to_string() const;
    
    std::unordered_map<std::string, int>::iterator get_start_iterator();
    std::unordered_map<std::string, int>::iterator get_end_iterator();
    
private:
    CContext &_context;
    std::unordered_map<std::string, int> _members;
    
     // Multiple keys may have the same value, that is the reason for the vector here.
    std::map<int, std::vector<std::string>> _values;
    
    std::string _name;
    std::string _typedefName;
    
    // Modifies `enumValue` so that all symbols get converted to integers. For example: "VEHICLE_PLANE" should get replaced with "2".
    void _evaluate_enum_symbols(std::string &enumValue);
    int _evaluate_enum(std::string enumValue);
    int _parse_enum_value(std::string &enumValue);
};

// Write-Only Enum class. Used in cHeader.h to create enums with.
class WriteableCEnum {
public:
    WriteableCEnum(std::string name);
    ~WriteableCEnum();
    
    friend std::ostream& operator<<(std::ostream& os, const WriteableCEnum& cEnum);
    
    void add_symbol(std::string symbol);
    void add_symbol(std::string symbol, int newValue);
    
    std::string to_string() const;
private:
    std::string _name;
    int _currentValue;
    std::map<int, std::string> _members; // Note: Inverted from CEnum version.
};

namespace CEnumsHelper {
    void get_enums_from_code(CContext &context, const std::string &code, std::vector<CEnum*> &out);
    void load_enums_from_file(CContext &context, fs::path filepath);
}
}
