#include "cStructHelper.h"

#include <string>
#include <sstream>

#include "helpers/debugHelper.h"
#include "helpers/regexHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/fileHelper.h"

#include "cContext.h"
#include "cTypes.h"

CStructEntry::CStructEntry(CContext *context, CStruct *parent, std::string &type, std::string &pointer, std::string &name, 
    std::string &arrayBrackets, std::string hint) : type(type), pointer(pointer), name(name), arrayBrackets(arrayBrackets), 
    _context(context), _parent(parent) {
        // Make sure the strings have no whitespace. Makes processing easier.
        StringHelper::remove_all_whitespace(this->type);
        StringHelper::remove_all_whitespace(this->pointer);
        StringHelper::remove_all_whitespace(this->name);
        StringHelper::remove_all_whitespace(this->arrayBrackets);
        _calc_array_multiplier();
        
        if(!hint.empty()) {
            _generate_hint_map(hint);
        }
        
        _isSignedType = CTypes::is_signed_type(type);
}

bool CStructEntry::is_pointer_to_type() {
    return !pointer.empty();
}

bool CStructEntry::is_array() {
    return !arrayBrackets.empty();
}

bool CStructEntry::has_hint() {
    return !_hintMap.empty();
}

std::string CStructEntry::get_hint_type() {
    DebugHelper::assert(has_hint(), "(CStructEntry::get_hint_type) ", name, " does not have a hint!");
    DebugHelper::assert(_hintMap.find("_hintType") != _hintMap.end(), "(CStructEntry::get_hint_type) ", name
        , " does not have a hint type! (Should not be possible?)");
    return _hintMap["_hintType"];
}

std::string CStructEntry::get_hint_value(const std::string hintKey) {
    DebugHelper::assert(has_hint(), "(CStructEntry::get_hint_type) ", name, " does not have a hint!");
    DebugHelper::assert(_hintMap.find(hintKey) != _hintMap.end(), "(CStructEntry::get_hint_type) ", name
        , " does not have the hint key: \"", hintKey, "\"");
    return _hintMap[hintKey];
}

std::string CStructEntry::get_hint_value(const std::string hintKey, std::string defaultValue) {
    DebugHelper::assert(has_hint(), "(CStructEntry::get_hint_type) ", name, " does not have a hint!");
    if(_hintMap.find(hintKey) == _hintMap.end()) {
        return defaultValue;
    }
    return _hintMap[hintKey];
}

void CStructEntry::_generate_hint_map(std::string &hint) {
    std::vector<std::string> hintArgs;
    StringHelper::split(hint, ',', hintArgs);
    size_t numArgs = hintArgs.size();
    
    std::string &firstArg = hintArgs[0];
    
    // Arg 0 is always the hint type. Might have a colon to indicate the sub-type.
    if(StringHelper::has(firstArg, ":")) {
        size_t colonIndex = firstArg.find_first_of(':');
        std::string hintType = firstArg.substr(0, colonIndex);
        _hintMap["_hintType"] = hintType;
        _hintMap[hintType] = firstArg.substr(colonIndex + 1);
    } else {
        _hintMap["_hintType"] = firstArg;
    }
    
    // Rest of the args
    for(size_t i = 1; i < numArgs; i++) {
        std::string &arg = hintArgs[i];
        
        size_t colonIndex = arg.find_first_of(':');
        
        if(colonIndex == std::string::npos) {
            // TODO: Support other hint types besides just a std::string?
            DebugHelper::error("(CStructEntry::_generate_hint_map) Invalid hint argument: \"", arg, "\"");
        }
        
        std::string hintKey = arg.substr(0, colonIndex);
        DebugHelper::assert(!hintKey.empty(), "(CStructEntry::_generate_hint_map) Hint arg ", i, 
            " for \"", name, "\" does not have a key!");
        _hintMap[hintKey] = arg.substr(colonIndex + 1);
    }
}

std::string CStructEntry::to_string() {
    std::stringstream ss;
    ss << type << " " << pointer << name << arrayBrackets << ";"; 
    return ss.str();
}

bool CStructEntry::is_type_trivial() {
    if(is_pointer_to_type()) {
        return true; // Pointers have fixed sizes, so yes.
    }
    if(innerStruct != nullptr) {
        return innerStruct->is_trivial();
    }
    return CTypes::is_standard_type(type);
}

CStructEntry::InternalType CStructEntry::get_internal_type() {
    if(_internalType == InternalType::NOT_SET) {
        update_internal_type();
    }
    return _internalType;
}

void CStructEntry::update_internal_type() {
    if(is_pointer_to_type()) {
        _internalType = InternalType::POINTER;
    } else if(innerStruct != nullptr) {
        _internalType = InternalType::STRUCT_UNION;
    } else if(CTypes::is_integer_type(type)) {
        _internalType = InternalType::INTEGER;
    } else if(CTypes::is_float_type(type)) {
        _internalType = InternalType::FLOAT;
    } else {
        _internalType = InternalType::UNKNOWN;
        return;
    }

    if(is_array()) {
        _internalType = (InternalType)((int)_internalType + (int)NUMBER_OF_VALUE_TYPES);
    }
}

bool CStructEntry::is_internal_type(const InternalType internalType) {
    if(_internalType == InternalType::NOT_SET) {
        update_internal_type();
    }
    return _internalType == internalType;
}
    
bool CStructEntry::is_integer_type() {
    return is_internal_type(InternalType::INTEGER);
}

bool CStructEntry::is_float_type() {
    return is_internal_type(InternalType::FLOAT);
}

bool CStructEntry::is_pointer_type() {
    return is_internal_type(InternalType::POINTER);
}

bool CStructEntry::is_array_of_integers() {
    return is_internal_type(InternalType::ARRAY_INTEGER);
}

bool CStructEntry::is_array_of_floats() {
    return is_internal_type(InternalType::ARRAY_FLOAT);
}

bool CStructEntry::is_array_of_pointers() {
    return is_internal_type(InternalType::ARRAY_POINTER);
}

bool CStructEntry::is_array_of_structs_or_unions() {
    return is_internal_type(InternalType::ARRAY_STRUCT_UNION);
}

size_t CStructEntry::get_array_multiplier() {
    return _arrayMultiplier;
}

size_t CStructEntry::get_byte_size() {
    size_t outSize;
    
    if(is_pointer_to_type()) {
        outSize = CTypes::size_of_pointer();
    } else if(innerStruct != nullptr) {
        outSize = innerStruct->get_byte_size();
    } else {
        outSize = CTypes::get_size_of_type(type);
        if(outSize == 0) { 
            // Not a trivial type, try to get it from global context.
            outSize = _context->get_size_of_element(type);
        }
    }
    
    DebugHelper::assert(outSize > 0, 
        "(CStructEntry::get_byte_size) Failed to calculate size for \"", name, "\" (type is \"", type, "\"). Is that type defined?");
    
    return outSize * _arrayMultiplier;
}

std::string CStructEntry::get_display_name() {
    if(name.empty() && innerStruct != nullptr) {
        std::stringstream ss;
        ss << "(Anonymous " << (innerStruct->is_a_union() ? "Union" : "Struct") << ")";
        return ss.str();
    }
    return name;
}

int64_t CStructEntry::get_integer_from_data(uint8_t *data, bool isBigEndian) {
    size_t numBytes = get_byte_size();
        
    int64_t value = 0;
    
    for(size_t i = 0; i < numBytes; i++) {
        size_t index = get_offset() + ((isBigEndian) ? numBytes - i - 1 : i);
        value |= ((int64_t)data[index]) << (int64_t)(i * 8);
    }
    
    if(_isSignedType) {
        // Convert unsigned value to signed value.
        int shiftBy = (sizeof(int64_t) - numBytes) * 8;
        value <<= shiftBy;
        value >>= shiftBy;
    }
    
    return value;
}

void CStructEntry::set_integer_to_data(uint8_t *data, int64_t value, bool isBigEndian) {
    size_t numBytes = get_byte_size();

    for(size_t i = 0; i < numBytes; i++) {
        size_t index = get_offset() + ((isBigEndian) ? numBytes - i - 1 : i);
        data[index] = value >> (int64_t)(i * 8);
    }
}

template<typename T>
void CStructEntry::get_values_from_data_array(std::vector<T> &out, uint8_t *data, bool isBigEndian) {
    DebugHelper::assert(is_array(), "(CStructEntry::get_values_from_data_array) Entry ", name, " is not an array!");
    DebugHelper::assert(is_type_trivial(), "(CStructEntry::get_values_from_data_array) Entry ", name, " is not trivial, cannot get data!");
    
    size_t totalSize = get_byte_size();
    size_t numEntries = _arrayMultiplier;
    size_t numBytesPerEntry = totalSize / numEntries;

    out.resize(numEntries);
    
    for(size_t arrayEntry = 0; arrayEntry < numEntries; arrayEntry++) {
        int64_t valueAsInteger = 0;
        
        // Get each byte of the value from the data array.
        // Note: This must be done byte-by-byte, since N64 data is *usually* big endian.
        for(size_t byteIndex = 0; byteIndex < numBytesPerEntry; byteIndex++) {
            size_t index = get_offset() + (arrayEntry * numBytesPerEntry) + ((isBigEndian) ? numBytesPerEntry - byteIndex - 1 : byteIndex);
            valueAsInteger |= ((int64_t)data[index]) << (int64_t)(byteIndex * 8);
        }
        
        out[arrayEntry] = *(reinterpret_cast<T*>(&valueAsInteger)); // Convert value to proper type.
    }
}

template void CStructEntry::get_values_from_data_array(std::vector<int64_t> &out, uint8_t *data, bool isBigEndian);

template<typename T>
void CStructEntry::set_values_to_data_array(std::vector<T> &in, uint8_t *data, bool isBigEndian) {
    DebugHelper::assert(is_array(), "(CStructEntry::set_values_to_data_array) Entry ", name, " is not an array!");
    DebugHelper::assert(is_type_trivial(), "(CStructEntry::set_values_to_data_array) Entry ", name, " is not trivial, cannot get data!");
    
    size_t totalSize = get_byte_size();
    size_t numEntries = _arrayMultiplier;
    size_t numBytesPerEntry = totalSize / numEntries;
    
    for(size_t arrayEntry = 0; arrayEntry < numEntries; arrayEntry++) {
        // Convert entry to int64_t
        int64_t valueAsInteger = *(reinterpret_cast<int64_t*>(&in[arrayEntry]));
        
        // Note: This must be done byte-by-byte, since N64 data is *usually* big endian.
        for(size_t byteIndex = 0; byteIndex < numBytesPerEntry; byteIndex++) {
            size_t index = get_offset() + (arrayEntry * numBytesPerEntry) + ((isBigEndian) ? numBytesPerEntry - byteIndex - 1 : byteIndex);
            data[index] = valueAsInteger >> (int64_t)(byteIndex * 8);
        }
    }
}

template void CStructEntry::set_values_to_data_array(std::vector<int64_t> &in, uint8_t *data, bool isBigEndian);

int CStructEntry::get_offset() {
    if(_offset == -1) {
        _parent->calculate_offsets();
    }
    DebugHelper::assert(_offset >= 0, "(CStructEntry::get_offset) Could not calculate offset for ", name);
    return _offset;
}

void CStructEntry::set_offset(int newOffset) {
    _offset = newOffset;
}

const std::string C_STRUCT_ENTRY_REGEX_ARRAY_BRACKET_NUMBERS = R"(\[\s*([^\]\s]+)\s*\])";

void CStructEntry::_calc_array_multiplier() {
    _arrayMultiplier = 1;
    if(!is_array()) {
        return;
    }
    std::vector<RegexMatch> matches;
    RegexHelper::get_matches(arrayBrackets, C_STRUCT_ENTRY_REGEX_ARRAY_BRACKET_NUMBERS, matches);
    
    DebugHelper::assert(matches.size() > 0, "(CStructEntry::_calc_array_multiplier) Brackets are invalid: \"", arrayBrackets, "\"");
    
    for(RegexMatch &match : matches) {
        std::string numberStr = match.get_group(1).get_text();
        
        int numberValue = std::stoi(numberStr, nullptr, 0);
        
        DebugHelper::assert(numberValue > 0, "(CStructEntry::_calc_array_multiplier) Value cannot be less than 1. \"", numberStr, "\"");
        
        _arrayMultiplier *= numberValue;
    }
}

CContext *CStructEntry::get_context() {
    return _context;
}

CStruct::CStruct(CContext *context) : _context(context) {
}

CStruct::~CStruct() {
    // Should be fine to call even if the struct is already not registered.
    _context->deregister_struct(_name);
    
    for(CStructEntry *entry : _entries) {
        delete entry;
    }
}

//std::string C_STRUCT_NAME_REGEX = R"(struct\s+([A-Za-z_][A-Za-z0-9_]*)\s+\{)";

const std::string C_STRUCT_MEMBERS_REGEX = R"(([A-Za-z_][A-Za-z0-9_]*)[ \t]+([0-9A-Za-z_*\[\], \t]+);)";
const std::string C_STRUCT_MEMBERS_ENTRY_REGEX = R"(^([*][* ]*)?([a-zA-Z_][a-zA-Z_0-9]*)?(?:\s*(\[.*\]))?)";
const std::string C_STRUCT_DEFINITION = R"((typedef)?\s*(struct|union)\s*([A-Za-z_][A-Za-z0-9_]*)?\s*\{((?:.|\n)*)}\s*([A-Za-z_][A-Za-z0-9_]*)?\s*;?)";
const std::string C_STRUCT_RANGE_CHECK = R"(((?:.|\n)*?)(((struct|union)\s*([A-Za-z_][A-Za-z0-9_]*)?\s*))?(;|\{))";

struct CStructMemberParse {
    int start; // Offset to the start of the text.
    int end;   // Offset to the end of the text.
    bool isStruct; // type is a struct/union
    int structStart;
    int structEnd;
    bool hasHint;
    int hintStart;
    int hintEnd;
    
    void reset() {
        start = -1;
        end = -1;
        isStruct = false;
        structStart = -1;
        structEnd = -1;
        hasHint = false;
        hintStart = -1;
        hintEnd = -1;
    }
    
    std::string to_string() {
        std::stringstream ss;
        
        ss << "[CStructMemberParse] " 
           << start << "," << end;
        
        if(isStruct) {
            ss << "(" << structStart << "," << structEnd << ")";
        }
        
        return ss.str();
    }
    
    std::string get_substring(const std::string &structCode) {
        size_t length = end - start;
        return structCode.substr(start, length);
    }
    
    std::string get_struct_substring(const std::string &structCode) {
        size_t length = structEnd - structStart;
        return structCode.substr(structStart, length);
    }
    
    std::string get_hint_substring(const std::string &structCode) {
        if(!hasHint) {
            return "";
        }
        size_t length = hintEnd - hintStart;
        std::string out = structCode.substr(hintStart, length);
        StringHelper::remove_all_whitespace(out); // Should be no spaces in a hint.
        return out;
    }
};

const std::string C_STRUCT_END_CHAR = R"(^((?:.|\n)*?([;{]))(?:\s*Hint[(]\s*[(]?([^)\n]*)[)](?:\s*[)])?)?)";

int get_next_member(const std::string &structCode, int offsetInCode, CStructMemberParse &out) {
    
    // Make sure previous information doesn't get reused.
    out.reset();
    
    // We need to first check if we are dealing with a struct/union or not.
    // To do that, I look to see if a ';' or a '{' appears first.
    int endCharOffset; 
    char endChar;
    RegexMatch *match = RegexHelper::get_first_match(structCode, C_STRUCT_END_CHAR, offsetInCode);
    
    if(match == nullptr) {
        //DebugHelper::info("(get_next_member) match was null!");
        return -1;
    }
    
    endCharOffset = match->get_group(2).get_offset();
    
    if(endCharOffset == -1) {
        //DebugHelper::info("(get_next_member) endChar was not found!");
        delete match;
        return -1;
    }
    
    endCharOffset += offsetInCode;
    
    endChar = match->get_group(2).get_text()[0];
    
    if(endChar == ';') { 
        // Not a struct type, so just return the start/end points.
        out.start = offsetInCode;
        out.end = endCharOffset + 1;
        
        // Check for hint.
        out.hintStart = match->get_group(3).get_offset();
        
        if(out.hintStart != -1) {
            // Hint data was found!
            out.hintStart += offsetInCode;
            out.hintEnd = out.hintStart + match->get_group(3).get_text_length();
            out.hasHint = true;
        }
        
        delete match;
        return out.end;
    }
    
    DebugHelper::assert(endChar == '{', "(get_next_member) endChar not a opening brace!");
    
    // endChar is a '{'
    out.isStruct = true;
    out.structStart = offsetInCode;
    
    int closeBraceOffset = StringHelper::find_closing_brace(structCode, endCharOffset);
    
    DebugHelper::assert(structCode[closeBraceOffset] == '}', "(get_next_member) Invalid closing brace!");
    
    out.structEnd = closeBraceOffset + 1;
    
    offsetInCode = out.structEnd;
    
    delete match;
    
    // Now that the struct was found, get the rest of the member.
    endCharOffset = structCode.find_first_of(';', offsetInCode);
    
    out.start = offsetInCode;
    out.end = endCharOffset + 1;
    
    // Don't bother checking hints for the struct. (Maybe at a later date?)
    
    return out.end;
}

CStruct::CStruct(CContext *context, const std::string &rawCode) : _context(context) {
    RegexMatch *structDefMatch = RegexHelper::get_first_match(rawCode, C_STRUCT_DEFINITION);
    DebugHelper::assert(structDefMatch != nullptr, "rawCode \"", rawCode, "\" is not valid.");
    
    std::string structOrUnion = structDefMatch->get_group(2).get_text();
    _isUnion = (structOrUnion == "union");
    _name = structDefMatch->get_group(3).get_text();
    
    std::string typedefGroup = structDefMatch->get_group(1).get_text();
    if(typedefGroup == "typedef") {
        _typedefName = structDefMatch->get_group(5).get_text();
    }
    
    const std::string structCode = structDefMatch->get_group(4).get_text();
    
    int textOffset = 0;
    int structCodeEnd = (int)structCode.length();
    
    CStructMemberParse parseInfo;
    while (textOffset < structCodeEnd) {
        int newOffset = get_next_member(structCode, textOffset, parseInfo);
        //DebugHelper::info("newOffset = ", newOffset, ", parsed = ", parseInfo.to_string());
        
        if(newOffset <= textOffset) {
            break;
        }
        
        CStruct *innerStruct = nullptr;
        
        std::string memberCode = parseInfo.get_substring(structCode);
        //DebugHelper::info("memberCode = ", memberCode);
        
        std::string type;
        std::string rest;
        
        // Should be empty if there is no hint.
        std::string hint = parseInfo.get_hint_substring(structCode);
        
        if(parseInfo.isStruct) {
            std::string innerStructCode = parseInfo.get_struct_substring(structCode);
            innerStruct = new CStruct(_context, innerStructCode);
            
            type = innerStruct->is_a_union() ? "union" : "struct";
            rest = memberCode;
        } else {
            // Regular non-struct member.
            RegexMatch *match = RegexHelper::get_first_match(memberCode, C_STRUCT_MEMBERS_REGEX);
            
            DebugHelper::assert(match != nullptr, "memberCode \"", memberCode, "\" is not valid.");
            
            type = match->get_group(1).get_text();
            rest = match->get_group(2).get_text();
            
            delete match; // done with match.
        }
        
        std::vector<std::string> entries;
        StringHelper::split_and_trim(rest, ',', entries);
        
        for(std::string &entry : entries) {
            
            std::string pointers;
            std::string name;
            std::string arrayBrackets;
            
            if(entry != ";") {
                RegexMatch *match = RegexHelper::get_first_match(entry, C_STRUCT_MEMBERS_ENTRY_REGEX);
                DebugHelper::assert(match != nullptr, "entry \"", entry, "\" is not valid.");
                pointers = match->get_group(1).get_text(); // The asterisks
                name = match->get_group(2).get_text(); // Name of the variable.
                arrayBrackets = match->get_group(3).get_text(); // If this entry is an array, then get the brackets.
                delete match; // done with match.
            }
            
            _entries.push_back(new CStructEntry(_context, this, type, pointers, name, arrayBrackets, hint));
            
            if(parseInfo.isStruct) {
                _entries.back()->innerStruct = innerStruct;
            }
            
        }
        
        textOffset = newOffset;
    }
    
    _calc_trivialness();
    _context->register_struct(this);
}

std::string CStruct::get_name() {
    return _name;
}

bool CStruct::is_a_union() {
    return _isUnion;
}

bool CStruct::is_anonymous() {
    return _typedefName.empty();
}

std::string CStruct::to_string() {
    std::stringstream ss;
    if(_name.empty()) {
        ss << "struct {\n";
    } else {
        ss << "typedef struct " << _name << " {\n";
    }
    for(CStructEntry *entry : _entries) {
        ss << "    " << entry->to_string() << "\n";
    }
    if(_name.empty()) {
        ss << "}" << ";";
    } else {
        ss << "} " << _name << ";";
    }
    return ss.str();
}

CStructEntry *CStruct::get_entry(size_t entryIndex) {
    DebugHelper::assert(entryIndex < _entries.size(), "(CStruct::get_entry) Out of bounds index ", entryIndex, ". Struct only has ", _entries.size(), " entries.");
    return _entries[entryIndex];
}

size_t CStruct::entry_count() {
    return _entries.size();
}

size_t CStruct::get_byte_size() {
    size_t outSize = 0;
    
    if(_isUnion) {
        for(CStructEntry *entry : _entries) {
            size_t memberSize = entry->get_byte_size();
            // Get the maximum size.
            outSize = (memberSize > outSize) ? memberSize : outSize;
        }
    } else {
        for(CStructEntry *entry : _entries) {
            outSize += entry->get_byte_size();
        }
    }
    
    return outSize;
}

bool CStruct::is_trivial() {
    return _isTrivial;
}

// This is only run if needed.
void CStruct::calculate_offsets(int currentOffset) {
    for(CStructEntry *entry : _entries) {
        entry->set_offset(currentOffset);
        if(entry->innerStruct != nullptr) {
            entry->innerStruct->calculate_offsets(currentOffset);
        }
        currentOffset += entry->get_byte_size();
    }
}

void CStruct::_calc_trivialness() {
    _isTrivial = true;
    for(CStructEntry *entry : _entries) {
        if(!entry->is_type_trivial()) {
            _isTrivial = false;
            return;
        }
    }
}

const std::string LOOKFOR_C_STRUCT_REGEX = R"(\s*(typedef)?\s*(struct|union)\s*([A-Za-z_][A-Za-z0-9_]*)\s*\{)";

void CStructHelper::get_structs_from_code(CContext *context, const std::string &code, std::vector<CStruct*> &out) {
    size_t codeLength = code.length();
    size_t curPos = 0;
    RegexMatch *currentMatch = RegexHelper::get_first_match(code, LOOKFOR_C_STRUCT_REGEX, curPos);
    
    while((currentMatch != nullptr) && (curPos < codeLength)) {
        // Get start & end points of the struct.
        size_t structStart = curPos + currentMatch->get_group(0).get_offset();
        size_t structEnd = StringHelper::find_closing_brace(code, structStart) + 1;
        
        // Extract the struct from the code file.
        std::string structCode = code.substr(structStart, structEnd - structStart);
        
        // Create struct & add it to the vector.
        out.push_back(new CStruct(context, structCode));
        
        // Find next struct
        curPos = structEnd;
        delete currentMatch;
        currentMatch = RegexHelper::get_first_match(code, LOOKFOR_C_STRUCT_REGEX, curPos);
    }
    
    if(currentMatch != nullptr) {
        delete currentMatch;
    }
    
}

void CStructHelper::load_structs_from_file(CContext *context, fs::path filepath) {
    std::vector<CStruct*> dummy; // Not actually used.
    std::string cFileCode = FileHelper::read_text_file(filepath);
    get_structs_from_code(context, cFileCode, dummy);
}
