#include "cEnumsHelper.h"

#include <stdexcept>
#include <sstream>

#include "helpers/fileHelper.h"
#include "helpers/regexHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/stringHelper.h"

#include "libs/calculator.hpp"

#include "cContext.h"

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
            value = _context->get_int_value_of_symbol(symbol);
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

CEnum::CEnum(CContext *context) : _context(context) {
}

CEnum::CEnum(CContext *context, const std::string &rawCode) : _context(context) {
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
            _members[enumLabel] = parsedEnumValue;
            nextValue = parsedEnumValue + 1;
            continue;
        }
        _members[enumLabel] = nextValue;
        nextValue++;
    }
    
    _context->register_enum(this);
}

CEnum::~CEnum() {
    _context->deregister_enum(_name);
}

std::string CEnum::get_name() {
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
    for (auto& it : _members) {
        if (it.second == value) {
            outSymbol = it.first; // Return the first symbol that matches the value.
            return true;
        }
    }
    // value was not found in the map.
    return false;
}

size_t CEnum::get_member_count() {
    return _members.size();
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

void WriteableCEnum::add_symbol(std::string symbol) {
    _members[_currentValue] = symbol;
    _currentValue++;
}

void WriteableCEnum::add_symbol(std::string symbol, int newValue) {
    _currentValue = newValue;
    add_symbol(symbol);
}

std::string WriteableCEnum::to_string() {
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

// TODO: Implement these!
void CEnumsHelper::get_enums_from_code(CContext *context, const std::string &code, std::vector<CEnum*> &out) {
    std::vector<RegexMatch> matches;
    RegexHelper::get_matches(code, LOOKFOR_C_ENUM_REGEX, matches);
    
    for(RegexMatch &match : matches) {
        // Get the C code for this enum.
        std::string enumCode = match.get_group(0).get_text();
        // Output new CEnum
        out.push_back(new CEnum(context, enumCode));
    }
}

void CEnumsHelper::load_enums_from_file(CContext *context, fs::path filepath) {
    std::vector<CEnum*> dummy; // Not actually used.
    std::string cFileCode = FileHelper::read_text_file(filepath);
    get_enums_from_code(context, cFileCode, dummy);
}
    
    