#include "cContext.h"

using namespace DkrAssetsTool;

#include "helpers/debugHelper.h"
#include "helpers/c/cStructHelper.h"

#include "cTypes.h"

CContext::CContext() {
}

CContext::~CContext() {
}

void CContext::register_struct(CStruct *structRef) {
    if(structRef == nullptr) {
        return;
    }
    std::string structName = structRef->get_name();
    if(structName.empty()) {
        return;
    }
    
    DebugHelper::assert_(_structsByName.find(structName) == _structsByName.end(), 
        "(CContext::register_struct) struct \"", structName, "\" has already been defined!");
    _mutex.lock();
    _structsByName[structName] = structRef;
    _mutex.unlock();
}

void CContext::deregister_struct(std::string &structName) {
    if(structName.empty()) {
        return;
    }
    _mutex.lock();
    // Make sure the key actually exists in the map.
    if(_structsByName.find(structName) == _structsByName.end()) {
        _mutex.unlock();
        return;
    }
    _structsByName.erase(structName);
    _mutex.unlock();
}

CStruct *CContext::get_struct(const std::string &structName) {
    _mutex.lock();
    if(_structsByName.find(structName) == _structsByName.end()) {
        _mutex.unlock();
        return nullptr;
    }
    CStruct *out = _structsByName.at(structName);
    _mutex.unlock();
    return out;
}

// Returns 0 if element was not found.
size_t CContext::get_size_of_element(const std::string &elementName) {
    _mutex.lock();
    // First search to see if the element is a struct
    if(_structsByName.find(elementName) != _structsByName.end()) {
        _mutex.unlock();
        CStruct *structElem = get_struct(elementName);
        return structElem->get_byte_size();
    }
    // Then search to see if the element is an enum.
    if(_enumsByName.find(elementName) != _enumsByName.end()) {
        _mutex.unlock();
        return 4; // Enums should be integers, which are 4 bytes.
    }
    // Lastly, check to see if the element is just a basic type.
    if(CTypes::is_standard_type(elementName)) {
        _mutex.unlock();
        return CTypes::get_size_of_type(elementName);
    }
    _mutex.unlock();
    return 0; // Could not find element.
}

void CContext::clear_structs() {
    _mutex.lock();
    _structsByName.clear();
    _mutex.unlock();
}

void CContext::register_enum(CEnum *enumRef) {
    if(enumRef == nullptr) {
        return;
    }
    std::string enumName = enumRef->get_name();
    if(enumName.empty()) {
        return;
    }
    //DebugHelper::info("Registering enum \"", enumName, "\"");
    DebugHelper::assert_(_enumsByName.find(enumName) == _enumsByName.end(), 
        "(CContext::register_enum) struct \"", enumName, "\" has already been defined!");
    
    _mutex.lock();
    _enumsByName[enumName] = enumRef;
    _add_enum_values(enumRef);
    _mutex.unlock();
    
}

void CContext::deregister_enum(std::string &enumName) {
    if(enumName.empty()) {
        return;
    }
    
    _mutex.lock();
    // Make sure the key actually exists in the map.
    if(_enumsByName.find(enumName) == _enumsByName.end()) {
        _mutex.unlock();
        return;
    }
    _enumsByName.erase(enumName);
    _mutex.unlock();
    
}

CEnum *CContext::get_enum(const std::string &enumName) {
    _mutex.lock();
    if(_enumsByName.find(enumName) == _enumsByName.end()) {
        _mutex.unlock();
        return nullptr;
    }
    CEnum *out = _enumsByName.at(enumName);
    _mutex.unlock();
    return out;
}

void CContext::clear_enums() {
    _mutex.lock();
    _enumsByName.clear();
    _enumValues.clear();
    _mutex.unlock();
}

// Currently just gets loaded enum values.
int CContext::get_int_value_of_symbol(const std::string &symbolName) {
    _mutex.lock();
    if(_enumValues.find(symbolName) != _enumValues.end()) {
        int out = _enumValues.at(symbolName);
        _mutex.unlock();
        return out;
    }
    _mutex.unlock();
    
    DebugHelper::error("(CContext::get_int_value_of_symbol) Could not evaluate the symbol \"", symbolName, "\"");
    return 0;
}


std::string CContext::get_symbol_of_enum_int(std::string enumName, int index) {
    
    CEnum *e = get_enum(enumName);
    DebugHelper::assert_(e != nullptr, 
        "(CContext::get_symbol_of_enum_int) Enum \"", enumName, "\" does not exist!");
    std::string out;
    _mutex.lock();
    bool success = e->get_symbol_of_value(index, out);
    _mutex.unlock();
    DebugHelper::assert_(success, 
        "(CContext::get_symbol_of_enum_int) Enum \"", enumName, "\" does not have the index value of ", index
    );
    return out;
}

void CContext::_add_enum_values(CEnum *enumRef) {
    enumRef->copy_members_to_map(_enumValues);
}
