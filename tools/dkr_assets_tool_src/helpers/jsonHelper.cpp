#include "jsonHelper.h"

using namespace DkrAssetsTool;

#include <fstream>
#include <iostream>
#include <cmath>

#include "helpers/fileHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/stringHelper.h"

#include "misc/globalSettings.h"

// TODO: Support RapidJSON
#include "libs/json.hpp" // nlohmann JSON library. (https://github.com/nlohmann/json)

#include "libs/ThreadPool.h"

using json = nlohmann::json;

namespace DkrAssetsTool {
namespace JSON_HELPER_DETAILS {
    class JsonFileData {
    public:
        JsonFileData(std::string filepath) {
            std::ifstream f(filepath);
            data = json::parse(f);
        }
        JsonFileData() {
        }
        json data;
    };
}
}

/*******************************************************************************************************/

JsonFile::JsonFile(std::string filepath) : _filepath(filepath) {
    _data = std::make_unique<JSON_HELPER_DETAILS::JsonFileData>(filepath);
}

JsonFile::~JsonFile() {
}

std::string JsonFile::get_string(const std::string &ptr, const std::string &defaultValue) const {
    const json::json_pointer jsonPtr(ptr); // Working with JSON pointers is a LOT faster than normal basic_json
    return _data->data.value(jsonPtr, defaultValue);
}

// Returns the string as lowercase, used when case shouldn't matter.
std::string JsonFile::get_string_lowercase(const std::string &ptr, const std::string &defaultValue) const {
    std::string out = get_string(ptr, defaultValue);
    StringHelper::make_lowercase(out);
    return out;
}

// Returns the string as uppercase, mainly used for texture formats (RGBA16, IA8, etc.)
std::string JsonFile::get_string_uppercase(const std::string &ptr, const std::string &defaultValue) const {
    std::string out = get_string(ptr, defaultValue);
    StringHelper::make_uppercase(out);
    return out;
}

fs::path JsonFile::get_path(const std::string &ptr, const std::string &defaultValue) const {
    fs::path out = get_string(ptr, defaultValue);
    FileHelper::format_folder_string(out); // Make sure the returning string is in valid form.
    return out;
}

void JsonFile::copy_string_to(const std::string &ptr, char *output, size_t maxLengthForOutput, const std::string &defaultValue) const {
    if(maxLengthForOutput < 1) {
        return;
    }
    std::string outStr;
    if(!has(ptr)) {
        // JSON file does not have ptr, so just use the defaultValue instead.
        outStr = defaultValue;
    } else {
        // JSON file does have the ptr, but make sure that value is a string.
        DebugHelper::assert_(is_value_a_string(ptr), "(JsonFile::copy_string_to) Value at [", ptr, "] is not a string!");
        outStr = get_string(ptr, "");
    }
    size_t length = outStr.length();
    if(length > maxLengthForOutput) {
        DebugHelper::warn("(JsonFile::copy_string_to) String at [", ptr, "] is too long! Length was ", length, ", but the limit is ", maxLengthForOutput);
        length = maxLengthForOutput;
    }
    outStr.copy(output, length);
}

int JsonFile::get_int(const std::string &ptr, const int &defaultValue) const {
    const json::json_pointer jsonPtr(ptr);
    return _data->data.value(jsonPtr, defaultValue);
}

bool JsonFile::get_bool(const std::string &ptr, const bool &defaultValue) const {
    const json::json_pointer jsonPtr(ptr);
    return _data->data.value(jsonPtr, defaultValue);
}

double JsonFile::get_float(const std::string &ptr, const double &defaultValue) const {
    const json::json_pointer jsonPtr(ptr);
    return _data->data.value(jsonPtr, defaultValue);
}

std::any JsonFile::get_any(const std::string& ptr) const {
    const json::json_pointer jsonPtr(ptr);

    switch (_data->data[jsonPtr].type()) {
        case json::value_t::boolean:
            return std::any(_data->data.value(jsonPtr, false));
        case json::value_t::number_float:
            return std::any(_data->data.value(jsonPtr, 0.0));
        case json::value_t::number_integer:
        case json::value_t::number_unsigned:
            return std::any(_data->data.value(jsonPtr, 0));
        case json::value_t::string:
            return std::any(_data->data.value(jsonPtr, ""));
        default:
            return std::any();
    }
}

template<typename T>
void JsonFile::get_array(const std::string &ptr, std::vector<T> &arr) const {
    const json::json_pointer jsonPtr(ptr);
    json arrayJson = _data->data[jsonPtr];
    if(!arrayJson.is_array()) {
        // Not an array, so don't do anything to the array.
        return;
    }
    size_t arrLen = arrayJson.size();
    for(size_t i = 0; i < arrLen; i++) {
        arr.push_back(arrayJson[i]);
    }
}

template void JsonFile::get_array<std::string>(const std::string &ptr, std::vector<std::string> &arr) const;
template void JsonFile::get_array<int>(const std::string &ptr, std::vector<int> &arr) const;
template void JsonFile::get_array<bool>(const std::string &ptr, std::vector<bool> &arr) const;


// Returns the index of the element, or -1 if it doesn't exist.
template <typename T>
int JsonFile::get_index_of_elem_in_array(const std::string &ptr, T elem) const {
    const json::json_pointer jsonPtr(ptr);
    json arrayJson = _data->data[jsonPtr];
    if(!arrayJson.is_array()) {
        DebugHelper::error(_filepath, " [", ptr, "] is not an array!");
    }
    
    auto it = std::find(arrayJson.cbegin(), arrayJson.cend(), elem);
    
    if (it == arrayJson.end()) {
        // Element not found in array
        return -1;
    }
    
    return std::distance(arrayJson.cbegin(), it);
}

template int JsonFile::get_index_of_elem_in_array<std::string>(const std::string &ptr, std::string elem) const;
template int JsonFile::get_index_of_elem_in_array<int>(const std::string &ptr, int elem) const;
template int JsonFile::get_index_of_elem_in_array<bool>(const std::string &ptr, bool elem) const;

template <typename T>
T JsonFile::get_elem_from_array(const std::string &ptr, size_t index) const {
    const json::json_pointer jsonPtr(ptr);
    json arrayJson = _data->data[jsonPtr];
    if(!arrayJson.is_array()) {
        DebugHelper::error(_filepath, " [", ptr, "] is not an array!");
    }
    DebugHelper::assert_(index < arrayJson.size(), _filepath, ": Index ", index," into array [", ptr, "] is out of bounds!");
    return arrayJson[index].get<T>();
}

template std::string JsonFile::get_elem_from_array(const std::string &ptr, size_t index) const;
template int JsonFile::get_elem_from_array(const std::string &ptr, size_t index) const;
template bool JsonFile::get_elem_from_array(const std::string &ptr, size_t index) const;
template float JsonFile::get_elem_from_array(const std::string &ptr, size_t index) const;


template<typename T, typename T2>
std::optional<T> JsonFile::get_elem_from_object_array_that_has_property(const std::string& ptr, const std::string& valueName, const std::string& propertyName, T2 propertyValue) const {
    const json::json_pointer jsonPtr(ptr);
    json &arrayJson = _data->data[jsonPtr];
    DebugHelper::assert_(arrayJson.is_array(), "(JsonFile::get_elem_from_object_array_that_has_property) ", 
        _filepath, " [", ptr, "] is not an array!");

    for (auto it = arrayJson.begin(); it != arrayJson.end(); it++) {
        json &arrayJsonObj = it.value();
        DebugHelper::assert_(arrayJsonObj.is_object(), "(JsonFile::get_elem_from_object_array_that_has_property) ", 
            _filepath, " [", ptr, "] has an element that is not an object!");
        if (arrayJsonObj.contains(propertyName) && arrayJsonObj[propertyName] == propertyValue) {
            return arrayJsonObj[valueName];
        }
    }
    
    // Value does not exist in the array.
    return std::nullopt;
}
template std::optional<std::string> JsonFile::get_elem_from_object_array_that_has_property(const std::string& ptr, const std::string& valueName,
    const std::string& propertyName, std::string propertyValue) const;
template std::optional<int> JsonFile::get_elem_from_object_array_that_has_property(const std::string& ptr, const std::string& valueName,
    const std::string& propertyName, std::string propertyValue) const;


template<typename T>
std::optional<size_t> JsonFile::get_index_of_object_that_has_property(const std::string& ptr, const std::string& propertyName, T propertyValue) const {
    const json::json_pointer jsonPtr(ptr);
    json &arrayJson = _data->data[jsonPtr];
    DebugHelper::assert_(arrayJson.is_array(), "(JsonFile::get_index_of_object_that_has_property) ",
        _filepath, " [", ptr, "] is not an array!");

    for (size_t i = 0; i < arrayJson.size(); i++) {
        json &arrayJsonObj = arrayJson[i];
        DebugHelper::assert_(arrayJsonObj.is_object(), "(JsonFile::get_index_of_object_that_has_property) ", 
            _filepath, " [", ptr, "] has an element that is not an object!");
        if (arrayJsonObj.contains(propertyName) && arrayJsonObj[propertyName] == propertyValue) {
            return i;
        }
    }

    // Value does not exist in the array.
    return std::nullopt;
}

template std::optional<size_t> JsonFile::get_index_of_object_that_has_property(const std::string& ptr,
    const std::string& propertyName, std::string propertyValue) const;

template<typename T>
std::unordered_map<T, std::vector<size_t>> JsonFile::create_map_of_indices_from_property_value(const std::string& ptr, const std::string& propertyName) const {
    std::unordered_map<T, std::vector<size_t>> out;

    const json::json_pointer jsonPtr(ptr);
    json& arrayJson = _data->data[jsonPtr];
    DebugHelper::assert_(arrayJson.is_array(), "(JsonFile::get_index_of_object_that_has_property) ",
        _filepath, " [", ptr, "] is not an array!");

    for (size_t i = 0; i < arrayJson.size(); i++) {
        json& arrayJsonObj = arrayJson[i];
        DebugHelper::assert_(arrayJsonObj.is_object(), "(JsonFile::get_index_of_object_that_has_property) ",
            _filepath, " [", ptr, "] has an element that is not an object!");
        if (arrayJsonObj.contains(propertyName)) {
            T outIndex = arrayJsonObj[propertyName].get<T>();
            if (out.find(outIndex) == out.end()) {
                out[outIndex] = std::vector<size_t>();
            }
            out[outIndex].emplace_back(i); // Add the index into the out vector.
        }
    }

    return out;
}

template std::unordered_map<std::string, std::vector<size_t>> JsonFile::create_map_of_indices_from_property_value(const std::string& ptr, const std::string& propertyName) const;


std::vector<std::string> JsonFile::get_keys_of_object(const std::string& ptr) const {
    std::vector<std::string> keys;

    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];

    if (!data.is_object()) {
        return keys; // Return empty vector.
    }

    for (auto it = data.begin(); it != data.end(); it++) {
        keys.push_back(it.key());
    }

    return keys;
}

static void add_json_pointers(std::vector<std::string> &pointers, json &data, std::string currentPointer = "") {
    if (!currentPointer.empty()) {
        pointers.push_back(currentPointer);
    }
    if (!data.is_object() && !data.is_array()) {
        return;
    }
    currentPointer += "/";
    for (auto it = data.begin(); it != data.end(); it++) {
        add_json_pointers(pointers, it.value(), currentPointer + it.key());
    }
}

std::vector<std::string> JsonFile::get_all_pointers() const {
    std::vector<std::string> pointers;
    add_json_pointers(pointers, _data->data);
    return pointers;
}

size_t JsonFile::length_of_array(const std::string &ptr) const {
    const json::json_pointer jsonPtr(ptr);
    json arrayJson = _data->data[jsonPtr];
    if(arrayJson.is_null()) {
        return 0;
    }
    if(!arrayJson.is_array()) {
        DebugHelper::error(_filepath, " [", ptr, "] is not an array!");
    }
    return arrayJson.size();
}

size_t JsonFile::length_of_string(const std::string &ptr) const {
    const json::json_pointer jsonPtr(ptr);
    json strJson = _data->data[jsonPtr];
    if(!strJson.is_string()) {
        DebugHelper::error(_filepath, " [", ptr, "] is not a string!");
    }
    // Apparently strJson.json() doesn't work for string types. :/
    return strJson.get<std::string>().size();
}

bool JsonFile::has(const std::string &ptr) const {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return !data.is_null();
}

bool JsonFile::is_value_a_number(const std::string &ptr) const {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_number();
}

bool JsonFile::is_value_a_bool(const std::string &ptr) const {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_boolean();
}

bool JsonFile::is_value_a_string(const std::string &ptr) const {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_string();
}

bool JsonFile::is_value_an_array(const std::string &ptr) const {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_array();
}

bool JsonFile::is_value_an_object(const std::string &ptr) const {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_object();
}

bool JsonFile::is_value_null(const std::string &ptr) const {
    return !has(ptr);
}

fs::path JsonFile::get_filepath() const {
    return _filepath;
}

JSON_HELPER_DETAILS::JsonFileData *JsonFile::get_data() const {
    return _data.get();
}

/*******************************************************************************************************/

WritableJsonFile::WritableJsonFile(std::string outFilepath) : _outFilepath(outFilepath) {
    _data = std::make_shared<JSON_HELPER_DETAILS::JsonFileData>();
}

WritableJsonFile::~WritableJsonFile() {
}

void WritableJsonFile::new_object(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    _data->data[jsonPtr] = json::object();
}

void WritableJsonFile::new_array(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    _data->data[jsonPtr] = json::array();
}

void WritableJsonFile::set_string(const std::string &ptr, const std::string &value) {
    const json::json_pointer jsonPtr(ptr);
    _data->data[jsonPtr] = value;
}

void WritableJsonFile::set_path(const std::string &ptr, fs::path value) {
    //FileHelper::format_folder_string(value); // Make sure the stored string is in valid form.
    set_string(ptr, value);
}

void WritableJsonFile::set_int(const std::string &ptr, const int value) {
    const json::json_pointer jsonPtr(ptr);
    _data->data[jsonPtr] = value;
}

void WritableJsonFile::set_int_if_not_value(const std::string &ptr, const int value, const int checkValue) {
    if(value == checkValue) return;
    set_int(ptr, value);
}

void WritableJsonFile::set_int_if_not_zero(const std::string &ptr, const int value) {
    WritableJsonFile::set_int_if_not_value(ptr, value, 0);
}

void WritableJsonFile::set_float(const std::string &ptr, double value, const int precision) {
    if(precision > 0) {
        double mult = std::pow(10.0, precision);
        value = std::round(value * mult) / mult;
    }
    const json::json_pointer jsonPtr(ptr);
    _data->data[jsonPtr] = value;
}

void WritableJsonFile::set_float_if_not_zero(const std::string& ptr, double value, const int precision) {
    if (value == 0.0) return;
    set_float(ptr, value, precision);
}

void WritableJsonFile::set_bool(const std::string &ptr, const bool value) {
    const json::json_pointer jsonPtr(ptr);
    _data->data[jsonPtr] = value;
}

void WritableJsonFile::set_bool_if_true(const std::string &ptr, const bool value) {
    if(!value) return;
    set_bool(ptr, value);
}

void WritableJsonFile::set_null(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    _data->data[jsonPtr] = nullptr;
}

void WritableJsonFile::save() {
    // Make sure the directory exists first
    FileHelper::write_folder_if_it_does_not_exist(_outFilepath);
    std::ofstream o(_outFilepath);
    o << std::setw(4) << _data->data << std::endl;
}

/*******************************************************************************************************/

StatJsonFile::StatJsonFile(fs::path filepath) : _filepath(filepath) {
    if(FileHelper::path_exists(filepath)) {
        _data = new JSON_HELPER_DETAILS::JsonFileData(filepath);
    } else {
        _data = new JSON_HELPER_DETAILS::JsonFileData();
    }
}

StatJsonFile::~StatJsonFile() {
    delete _data;
}

// Returns empty if entry was not found.
std::string StatJsonFile::get_entry(const fs::path &path) {
    std::string pathEntry = std::string(path);
    StringHelper::replace(pathEntry, "/", "~1");
    const json::json_pointer jsonPtr("/files/" + pathEntry);
    return _data->data.value(jsonPtr, "");
}

void StatJsonFile::set_entry(const fs::path &path, const std::string &value) {
    std::string pathEntry = std::string(path);
    StringHelper::replace(pathEntry, "/", "~1");
    const json::json_pointer jsonPtr("/files/" + pathEntry);
    _data->data[jsonPtr] = value;
}

template<typename T>
T StatJsonFile::get_value(const std::string ptr, T defaultValue) {
    const json::json_pointer jsonPtr(ptr);
    json jsonData = _data->data[jsonPtr];
    if(jsonData.is_null()) {
        return defaultValue;
    }
    return _data->data.value(jsonPtr, defaultValue);
}

template std::string StatJsonFile::get_value(const std::string ptr, std::string defaultValue);
template int StatJsonFile::get_value(const std::string ptr, int defaultValue);
template bool StatJsonFile::get_value(const std::string ptr, bool defaultValue);

template<typename T>
void StatJsonFile::set_value(const std::string ptr, T value) {
    const json::json_pointer jsonPtr(ptr);
    _data->data[jsonPtr] = value;
}

template void StatJsonFile::set_value(const std::string ptr, std::string value);
template void StatJsonFile::set_value(const std::string ptr, int value);
template void StatJsonFile::set_value(const std::string ptr, bool value);

void StatJsonFile::save() {
    FileHelper::write_folder_if_it_does_not_exist(_filepath);
    std::ofstream o(_filepath);
    o << std::setw(4) << _data->data << std::endl;
}

/******************************************************************/

// Prototype here, because of recursion. (Can't have the `json` type be in the header file either)
void json_merge_append(json &dst, json &patch);

void json_merge_append_step(json &dst, json &patch, const std::string &key) {
    if(key == "merge-type") { // ignore merge-type
        return;
    }
    if(dst[key].is_object()) {
        // Recursion!
        json_merge_append(dst[key], patch[key]);
    } else if(dst[key].is_array()) {
        // Append patch array to the end of the dst array!
        dst[key].insert(dst[key].end(), patch[key].begin(), patch[key].end());
    } else {
        dst[key] = patch[key];
    }
}

void json_merge_append(json &dst, json &patch) {
    if(dst.is_object() && patch.is_object()) {
        for (json::iterator it = patch.begin(); it != patch.end(); ++it) {
           json_merge_append_step(dst, patch, it.key());
        }
    }
}

/******************************************************************/

void json_delete_file(json &dst, std::string filename) {
    fs::path pathToAssets = GlobalSettings::get_decomp_path_to_output_assets();
    std::string folder = dst[json::json_pointer("/folder")];
    fs::path fileToDelete = pathToAssets / folder / filename;
    
    DebugHelper::info_verbose("Deleting file: ", fileToDelete);
    
    FileHelper::delete_file(fileToDelete);
}

#define _JSON_HAS_KEY(json, key) (json.find(key) != json.end())

void json_check_for_removed_file_sections(json &dst, json &patch) {
    json &order = dst[json::json_pointer("/files/order")];
    json &sections = dst[json::json_pointer("/files/sections")];
    json &patchSections = patch[json::json_pointer("/files/sections")];
    
    if(!order.is_array() || !sections.is_object() || !patchSections.is_object()) {
        // Not the correct json type, so don't bother!
        return;
    }
    
    size_t index = 0;
    
    while(index < order.size()) {
        std::string key = order[index];
        if(_JSON_HAS_KEY(patchSections, key)) { // Check if the section id exists in the patch
            json &section = sections.at(key);
            json &patchSection = patchSections.at(key);
            if(_JSON_HAS_KEY(section, "filename") && _JSON_HAS_KEY(patchSection, "filename")) { // Make sure both the patch & dst have a filename.
                if(!section.at("filename").is_null() && patchSection.at("filename").is_null()) { // Check if the filename becomes null
                    json_delete_file(dst, section.at("filename")); // Delete the file if it exists.
                    order.erase(order.begin() + index); // Erase the index from the order.
                    sections.erase(key); // Erase the section.
                    continue;
                }
            }
        }
        index++;
    }
}

#undef _JSON_HAS_KEY

/******************************************************************/

enum JsonMergeType {
    MERGE_PATCH, // RFC 7386 - Arrays get overwritten.
    MERGE_APPEND // Like MERGE_PATCH, but arrays get appended to.
};

const std::vector<std::string> JSON_MERGE_TYPE_VALUES = {
    "patch",       // MERGE_PATCH
    "patch-append" // MERGE_APPEND
};

// Prefer appending arrays instead of overwriting them!
const std::string DEFAULT_PATCH_TYPE = "patch-append";

std::mutex _jsonHelperMutex;

/******************************************************************/

void JsonHelper::patch_json(const fs::path &dstPath, const fs::path &patchPath) {
    auto tryGetDstJsonFile = get_file(dstPath);
    auto tryGetPatchJsonFile = get_file(patchPath);
    
    DebugHelper::assert_(tryGetDstJsonFile.has_value(), "(JsonHelper::patch_json) ", dstPath, " could not be loaded. Make sure it is formatted properly.");
    DebugHelper::assert_(tryGetPatchJsonFile.has_value(), "(JsonHelper::patch_json) ", patchPath, " could not be loaded. Make sure it is formatted properly.");
    
    JsonFile &dstJsonFile = tryGetDstJsonFile.value();
    JsonFile &patchJsonFile = tryGetPatchJsonFile.value();
    
    std::string mergeTypeStr = patchJsonFile.get_string_lowercase("/merge-type", DEFAULT_PATCH_TYPE);
    JsonMergeType mergeType = static_cast<JsonMergeType>(DataHelper::vector_index_of<std::string>(JSON_MERGE_TYPE_VALUES, mergeTypeStr));
    
    JSON_HELPER_DETAILS::JsonFileData *dstJson = dstJsonFile.get_data();
    JSON_HELPER_DETAILS::JsonFileData *patchJson = patchJsonFile.get_data();
    
    json_check_for_removed_file_sections(dstJson->data, patchJson->data);
    
    switch(mergeType) {
        case JsonMergeType::MERGE_PATCH: // RFC 7386
            // Arrays will get overwritten.
            dstJson->data.merge_patch(patchJson->data); 
            break;
        case JsonMergeType::MERGE_APPEND: 
            // Like MERGE_PATCH, but arrays get appended to instead of overwritten.
            json_merge_append(dstJson->data, patchJson->data);
            break;
        default:
            DebugHelper::error("Invalid merge-type value of \"", mergeTypeStr, "\"");
            break;
    }
    
    // Write patched json data to dstPath
    _jsonHelperMutex.lock();
    std::ofstream o(dstPath);
    o << std::setw(4) << dstJson->data << std::endl;
    _jsonHelperMutex.unlock();
}

/*******************************************************************************************************/

std::unordered_map<fs::path, JsonFile*> _fileCache;

std::optional<std::reference_wrapper<JsonFile>> JsonHelper::get_file(fs::path filepath) {
    _jsonHelperMutex.lock();
    if (_fileCache.find(filepath) == _fileCache.end()) {
        try {
            _fileCache[filepath] = new JsonFile(filepath.generic_string());
        } catch (nlohmann::detail::parse_error&) {
            _jsonHelperMutex.unlock();
            return std::nullopt;
        }
    }
    _jsonHelperMutex.unlock();
    return *_fileCache[filepath];
}
