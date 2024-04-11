#include "cContext.h"

#include "helpers/debugHelper.h"
#include "helpers/c/cStructHelper.h"

#include "cTypes.h"

CContext::CContext() {
}

CContext::~CContext() {
}

void CContext::register_struct(CStruct *structRef) {
    DebugHelper::assert(structRef != nullptr, "(CContext::register_struct) Trying to register a null pointer!");
    std::string structName = structRef->get_name();
    if(structName.empty()) {
        return;
    }
    //DebugHelper::info("Registering struct \"", structName, "\"");
    DebugHelper::assert(_structsByName.find(structName) == _structsByName.end(), 
        "(CContext::register_struct) struct \"", structName, "\" has already been defined!");
    _structsByName[structName] = structRef;
}

void CContext::deregister_struct(std::string &structName) {
    if(structName.empty()) {
        return;
    }
    // Make sure the key actually exists in the map.
    if(_structsByName.find(structName) == _structsByName.end()) {
        return;
    }
    _structsByName.erase(structName);
}

CStruct *CContext::get_struct(const std::string &structName) {
    DebugHelper::assert(_structsByName.find(structName) != _structsByName.end(), 
        "(CContext::get_struct) struct \"", structName, "\" is not defined!");
    return _structsByName[structName];
}

// Returns 0 if element was not found.
size_t CContext::get_size_of_element(const std::string &elementName) {
    // First search to see if the element is a struct
    if(_structsByName.find(elementName) != _structsByName.end()) {
        CStruct *structElem = get_struct(elementName);
        return structElem->get_byte_size();
    }
    // Then search to see if the element is an enum.
    if(_enumsByName.find(elementName) != _enumsByName.end()) {
        return 4; // Enums should be integers, which are 4 bytes.
    }
    // Lastly, check to see if the element is just a basic type.
    if(CTypes::is_standard_type(elementName)) {
        return CTypes::get_size_of_type(elementName);
    }
    return 0; // Could not find element.
}

void CContext::clear_structs() {
    _structsByName.clear();
}

void CContext::register_enum(CEnum *enumRef) {
    DebugHelper::assert(enumRef != nullptr, "(CContext::register_enum) Trying to register a null pointer!");
    std::string enumName = enumRef->get_name();
    if(enumName.empty()) {
        return;
    }
    //DebugHelper::info("Registering enum \"", enumName, "\"");
    DebugHelper::assert(_enumsByName.find(enumName) == _enumsByName.end(), 
        "(CContext::register_enum) struct \"", enumName, "\" has already been defined!");
    _enumsByName[enumName] = enumRef;
    _add_enum_values(enumRef);
}

void CContext::deregister_enum(std::string &enumName) {
    if(enumName.empty()) {
        return;
    }
    // Make sure the key actually exists in the map.
    if(_enumsByName.find(enumName) == _enumsByName.end()) {
        return;
    }
    _enumsByName.erase(enumName);
}

CEnum *CContext::get_enum(const std::string &enumName) {
    DebugHelper::assert(_enumsByName.find(enumName) != _enumsByName.end(), 
        "(CContext::get_enum) enum \"", enumName, "\" is not defined!");
    return _enumsByName[enumName];
}

void CContext::clear_enums() {
    _enumsByName.clear();
    _enumValues.clear();
}

// Currently just gets loaded enum values.
int CContext::get_int_value_of_symbol(const std::string &symbolName) {
    if(_enumValues.find(symbolName) != _enumValues.end()) {
        return _enumValues[symbolName];
    }
    DebugHelper::error("(CContext::get_int_value_of_symbol) Could not evaluate the symbol \"", symbolName, "\"");
    return 0;
}


std::string CContext::get_symbol_of_enum_int(std::string enumName, int index) {
    CEnum *e = get_enum(enumName);
    DebugHelper::assert(e != nullptr, "(CContext::get_symbol_of_enum_int) Enum \"", enumName, "\" does not exist!");
    std::string out;
    DebugHelper::assert(
        e->get_symbol_of_value(index, out), 
        "(CContext::get_symbol_of_enum_int) Enum \"", enumName, "\" does not have the index value of ", index
    );
    return out;
}

void CContext::_add_enum_values(CEnum *enumRef) {
    enumRef->copy_members_to_map(_enumValues);
}
