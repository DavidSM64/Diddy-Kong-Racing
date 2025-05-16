#include "cEnumsHelper.h"

#include <stdexcept>
#include <sstream>

#include "helpers/fileHelper.h"
#include "helpers/regexHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/dataHelper.h"

#include "libs/calculator.hpp"

#include "cContext.h"

using namespace DkrAssetsTool;

const std::string C_ENUM_DEFINITION = R"((typedef)?\s*(enum)\s*([A-Za-z_][A-Za-z_0-9]*)?\s*\{([^}]*)\}\s*([A-Za-z_][A-Za-z_0-9]*)?\s*;)";
const std::string C_ENUM_MEMBER = R"(\s*([A-Za-z_][A-Za-z0-9_]*)\s*((?:(?:=)\s*([^,]*))|(?:\,)|(?:$)))";
const std::string C_ENUM_SYMBOL = R"(\b([A-Za-z_][A-Za-z0-9_]*)\b)";

// Modifies `enumValue` so that all symbols get converted to integers. For example: "VEHICLE_PLANE" should get replaced with "2".
void CEnum::_evaluate_enum_symbols(std::string &enumValue) {
    while(true) {
        RegexMatch *match = RegexHelper::get_first_match(enumValue, C_ENUM_SYMBOL);
        if(match == nullptr) {
            return; // Done!
        }
        std::string symbol = match->get_group(1).get_text();
        int offset = match->get_group(1).get_offset();
        int value;
        if(!get_value_of_member(symbol, value)) {
            // If the value is not a part of this enum, then go check to see if the context has it.
            value = _context.get_int_value_of_symbol(symbol);
        }
        std::string valueAsString = std::to_string(value);
        enumValue = enumValue.replace(offset, symbol.length(), valueAsString);
        delete match; // Done with the match.
    }
}

int CEnum::_evaluate_enum(std::string enumValue) {
    StringHelper::trim(enumValue);
    _evaluate_enum_symbols(enumValue);
    try {
        return calculator::eval(enumValue);
    } catch (calculator::error& e) {
        std::cerr << e.what() << std::endl;
        throw 1;
    }
}

int CEnum::_parse_enum_value(std::string &enumValue) {
    try {
        // Should work for most basic cases.
        return std::stoi(enumValue, 0, 0);
    } catch (const std::invalid_argument& ia) {
        // Not a simple conversion, continue.
    }
    return _evaluate_enum(enumValue);
}

CEnum::CEnum(CContext &context) : _context(context) {
}

CEnum::CEnum(CContext &context, const std::string &rawCode) : _context(context) {
    RegexMatch *enumDefMatch = RegexHelper::get_first_match(rawCode, C_ENUM_DEFINITION);
    DebugHelper::assert(enumDefMatch != nullptr, "rawCode \"", rawCode, "\" is not valid.");
    
    _name = enumDefMatch->get_group(3).get_text();
    
    std::string typedefGroup = enumDefMatch->get_group(1).get_text();
    if(typedefGroup == "typedef") {
        _typedefName = enumDefMatch->get_group(5).get_text();
    }
    
    const std::string enumCode = enumDefMatch->get_group(4).get_text();
    
    std::vector<RegexMatch> enumMemberMatches;
    
    RegexHelper::get_matches(enumCode, C_ENUM_MEMBER, enumMemberMatches);
    
    int nextValue = 0;
    for(RegexMatch &match : enumMemberMatches) {
        std::string enumLabel = match.get_group(1).get_text();
        std::string rest = match.get_group(2).get_text();
        
        if(StringHelper::starts_with(rest, "=")) {
            std::string enumValue = match.get_group(3).get_text();
            int parsedEnumValue = _parse_enum_value(enumValue);
            if(_values.find(parsedEnumValue) == _values.end()) {
                // New vector in values map.
                _values[parsedEnumValue] = {};
            }
            _members[enumLabel] = parsedEnumValue;
            // _values map is ordered by which the values were added.
            _values[parsedEnumValue].push_back(enumLabel); 
            nextValue = parsedEnumValue + 1;
            continue;
        }
        if(_values.find(nextValue) == _values.end()) {
            // New vector in values map.
            _values[nextValue] = {};
        }
        // _values map is ordered by which the values were added.
        _values[nextValue].push_back(enumLabel); 
        _members[enumLabel] = nextValue;
        nextValue++;
    }
    
    _context.register_enum(this);
}

CEnum::~CEnum() {
    _context.deregister_enum(_name);
}

// The namespace is needed here for g++ to resolve the function correctly.
namespace DkrAssetsTool {
    std::ostream& operator<<(std::ostream& os, const CEnum& cEnum) {
        os << cEnum.to_string();
        return os;
    }
}

std::string CEnum::get_name() const {
    return _name;
}

void CEnum::copy_members_to_map(std::unordered_map<std::string, int> &inputMap) {
    for (const auto & [ key, value ] : _members) {
        inputMap[key] = value;
    }
}

bool CEnum::get_value_of_member(const std::string &memberKey, int &out) {
    if(_members.find(memberKey) == _members.end()) {
        return false;
    }
    out = _members[memberKey];
    return true;
}

bool CEnum::get_symbol_of_value(int value, std::string &outSymbol) {
    if(_values.find(value) == _values.end()) {
        DebugHelper::warn("(CEnum::get_symbol_of_value) Could not find the value ", value, " for the enum \"", _name, "\"");
        return false;
    }
    outSymbol = _values[value][0]; // Return the first symbol of the value.
    return true;
}

size_t CEnum::get_member_count() const {
    return _members.size();
}

bool CEnum::is_simple() const {
    size_t index = 0;
    for(auto &val : _values) {
        if(val.first != index || val.second.size() != 1) {
            return false;
        }
        index++;
    }
    return true;
}

std::string CEnum::to_string() const {
    std::stringstream ss;
    
    const char *indent = "    ";
    
    int checkVal = 0;
    
    ss << "typedef enum " << _name << " { " << std::endl;
    
    // Iterate over the map
    for(auto &pair : _values) {
        bool lastEntry = pair == *std::prev(_values.end());
        int value = pair.first;
        const std::vector<std::string> &symbols = pair.second;
        // Iterate over the keys for that value
        for(size_t i = 0; i < symbols.size(); i++) {
            if(i > 0) {
                ss << "," << std::endl;
            }
            ss << indent << symbols[i];
            if(value != checkVal) {
                checkVal = value;
                ss << " = " << checkVal;
            }
            checkVal++;
        }
        
        if(!lastEntry) {
            ss << ",";
        }
        
        ss << std::endl;
    }
    
    ss << "} " << _name << ";" << std::endl;
    
    return ss.str();
}

std::unordered_map<std::string, int>::iterator CEnum::get_start_iterator() {
    return _members.begin();
}

std::unordered_map<std::string, int>::iterator CEnum::get_end_iterator() {
    return _members.end();
}

/*******************************************************************************************/

WriteableCEnum::WriteableCEnum(std::string name) : _name(name), _currentValue(0) {
}

WriteableCEnum::~WriteableCEnum() {
}

namespace DkrAssetsTool {
    std::ostream& operator<<(std::ostream& os, const WriteableCEnum& cEnum) {
        os << cEnum.to_string();
        return os;
    }
}

void WriteableCEnum::add_symbol(std::string symbol) {
    _members[_currentValue] = symbol;
    _currentValue++;
}

void WriteableCEnum::add_symbol(std::string symbol, int newValue) {
    _currentValue = newValue;
    add_symbol(symbol);
}

std::string WriteableCEnum::to_string() const {
    std::stringstream ss;
    
    const char *indent = "    ";
    
    int checkVal = 0;
    
    ss << "typedef enum " << _name << " { " << std::endl;
    
    // Iterate over the map
    for (const auto& member : _members) {
        ss << indent << member.second;
        if(member.first != checkVal) {
            checkVal = member.first;
            ss << " = " << checkVal;
        }
        if (member != *std::prev(_members.end())) {
            ss << ",";
        }
        ss << std::endl;
        checkVal++;
    }
    
    ss << "} " << _name << ";" << std::endl;
    
    return ss.str();
}

/*******************************************************************************************/

const std::string LOOKFOR_C_ENUM_REGEX = R"(\s*(typedef)?\s*(enum)\s*([A-Za-z_][A-Za-z0-9_]*)\s*\{[^}]*\}\s*([A-Za-z_][A-Za-z0-9_]*)?\s*;)";

void CEnumsHelper::get_enums_from_code(CContext &context, const std::string &code, std::vector<CEnum*> &out) {
    std::vector<RegexMatch> matches;
    RegexHelper::get_matches(code, LOOKFOR_C_ENUM_REGEX, matches);
    
    for(RegexMatch &match : matches) {
        // Get the C code for this enum.
        std::string enumCode = match.get_group(0).get_text();
        // Output new CEnum
        out.push_back(new CEnum(context, enumCode));
    }
}

std::vector<fs::path> _loadedFiles;

void CEnumsHelper::load_enums_from_file(CContext &context, fs::path filepath) {
    if(DataHelper::vector_has(_loadedFiles, filepath)) {
        return; // Already loaded. Don't do it again!
    }
    _loadedFiles.emplace_back(filepath);
    std::vector<CEnum*> dummy; // Not actually used.
    std::string cFileCode = FileHelper::read_text_file(filepath);
    get_enums_from_code(context, cFileCode, dummy);
}
    
    