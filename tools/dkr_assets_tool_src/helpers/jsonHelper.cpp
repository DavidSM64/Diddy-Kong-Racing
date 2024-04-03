#include "jsonHelper.h"

#include <fstream>
#include <iostream>
#include <cmath>

#include "helpers/fileHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/stringHelper.h"

// TODO: Support RapidJSON
#include "libs/json.hpp" // nlohmann JSON library. (https://github.com/nlohmann/json)

#include "libs/ThreadPool.h"

using json = nlohmann::json;

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

/*******************************************************************************************************/

JsonFile::JsonFile(std::string filepath) : _filepath(filepath) {
    _data = new JSON_HELPER_DETAILS::JsonFileData(filepath);
}

JsonFile::~JsonFile() {
    delete _data;
}

std::string JsonFile::get_string(const std::string &ptr, const std::string &defaultValue) {
    const json::json_pointer jsonPtr(ptr); // Working with JSON pointers is a LOT faster than normal basic_json
    return _data->data.value(jsonPtr, defaultValue);
}

// Returns the string as lowercase, used when case shouldn't matter.
std::string JsonFile::get_string_lowercase(const std::string &ptr, const std::string &defaultValue) {
    std::string out = get_string(ptr, defaultValue);
    StringHelper::make_lowercase(out);
    return out;
}

// Returns the string as uppercase, mainly used for texture formats (RGBA16, IA8, etc.)
std::string JsonFile::get_string_uppercase(const std::string &ptr, const std::string &defaultValue) {
    std::string out = get_string(ptr, defaultValue);
    StringHelper::make_uppercase(out);
    return out;
}

fs::path JsonFile::get_path(const std::string &ptr, const std::string &defaultValue) {
    fs::path out = get_string(ptr, defaultValue);
    FileHelper::format_folder_string(out); // Make sure the returning string is in valid form.
    return out;
}

void JsonFile::copy_string_to(const std::string &ptr, char *output, size_t maxLengthForOutput, const std::string &defaultValue) {
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

int JsonFile::get_int(const std::string &ptr, const int &defaultValue) {
    const json::json_pointer jsonPtr(ptr);
    return _data->data.value(jsonPtr, defaultValue);
}

bool JsonFile::get_bool(const std::string &ptr, const bool &defaultValue) {
    const json::json_pointer jsonPtr(ptr);
    return _data->data.value(jsonPtr, defaultValue);
}

double JsonFile::get_float(const std::string &ptr, const double &defaultValue) {
    const json::json_pointer jsonPtr(ptr);
    return _data->data.value(jsonPtr, defaultValue);
}

template<typename T>
void JsonFile::get_array(const std::string &ptr, std::vector<T> &arr) {
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

template void JsonFile::get_array<std::string>(const std::string &ptr, std::vector<std::string> &arr);
template void JsonFile::get_array<int>(const std::string &ptr, std::vector<int> &arr);
template void JsonFile::get_array<bool>(const std::string &ptr, std::vector<bool> &arr);


// Returns the index of the element, or -1 if it doesn't exist.
template <typename T>
int JsonFile::get_index_of_elem_in_array(const std::string &ptr, T elem) {
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

template int JsonFile::get_index_of_elem_in_array<std::string>(const std::string &ptr, std::string elem);
template int JsonFile::get_index_of_elem_in_array<int>(const std::string &ptr, int elem);
template int JsonFile::get_index_of_elem_in_array<bool>(const std::string &ptr, bool elem);

template <typename T>
T JsonFile::get_elem_from_array(const std::string &ptr, size_t index) {
    const json::json_pointer jsonPtr(ptr);
    json arrayJson = _data->data[jsonPtr];
    if(!arrayJson.is_array()) {
        DebugHelper::error(_filepath, " [", ptr, "] is not an array!");
    }
    DebugHelper::assert_(index < arrayJson.size(), _filepath, ": Index ", index," into array [", ptr, "] is out of bounds!");
    return arrayJson[index].get<T>();
}

template std::string JsonFile::get_elem_from_array(const std::string &ptr, size_t index);
template int JsonFile::get_elem_from_array(const std::string &ptr, size_t index);
template bool JsonFile::get_elem_from_array(const std::string &ptr, size_t index);
template float JsonFile::get_elem_from_array(const std::string &ptr, size_t index);

size_t JsonFile::length_of_array(const std::string &ptr) {
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

size_t JsonFile::length_of_string(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    json strJson = _data->data[jsonPtr];
    if(!strJson.is_string()) {
        DebugHelper::error(_filepath, " [", ptr, "] is not a string!");
    }
    // Apparently strJson.json() doesn't work for string types. :/
    return strJson.get<std::string>().size();
}

bool JsonFile::has(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return !data.is_null();
}

bool JsonFile::is_value_a_number(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_number();
}

bool JsonFile::is_value_a_bool(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_boolean();
}

bool JsonFile::is_value_a_string(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_string();
}

bool JsonFile::is_value_an_array(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_array();
}

bool JsonFile::is_value_an_object(const std::string &ptr) {
    const json::json_pointer jsonPtr(ptr);
    json data = _data->data[jsonPtr];
    return data.is_object();
}

bool JsonFile::is_value_null(const std::string &ptr) {
    return !has(ptr);
}

fs::path JsonFile::get_filepath() {
    return _filepath;
}

JSON_HELPER_DETAILS::JsonFileData *JsonFile::get_data() {
    return _data;
}

/*******************************************************************************************************/

/*
class WritableJsonFile {
    public:
        WritableJsonFile(std::string filepath);
        ~WritableJsonFile();
        
        std::string set_string(const std::string &ptr, const std::string &value);
        int set_int(const std::string &ptr, const int &value);
        bool set_bool(const std::string &ptr, const bool &value);
        
        bool save_file();
        
    private:
        std::string _filepath;
        JSON_HELPER_DETAILS::JsonFileData *_data;
};
*/

WritableJsonFile::WritableJsonFile(std::string outFilepath) : _outFilepath(outFilepath) {
    _data = new JSON_HELPER_DETAILS::JsonFileData();
}

WritableJsonFile::~WritableJsonFile() {
    delete _data;
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

/*******************************************************************************************************/

bool JsonHelper::get_file(fs::path filepath, JsonFile **out) {
    *out = _load_json_from_cache(filepath);
    return *out != nullptr;
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

/******************************************************************/

void JsonHelper::patch_json(const fs::path &dstPath, const fs::path &patchPath) {
    JsonFile *dstJsonFile = _load_json_from_cache(dstPath);
    JsonFile *patchJsonFile = _load_json_from_cache(patchPath);
    
    DebugHelper::assert_(dstJsonFile != nullptr, "(JsonHelper::patch_json) ", dstPath, " could not be loaded. Make sure it is formatted properly.");
    DebugHelper::assert_(patchJsonFile != nullptr, "(JsonHelper::patch_json) ", patchPath, " could not be loaded. Make sure it is formatted properly.");
    
    std::string mergeTypeStr = patchJsonFile->get_string_lowercase("/merge-type", DEFAULT_PATCH_TYPE);
    JsonMergeType mergeType = static_cast<JsonMergeType>(DataHelper::vector_index_of<std::string>(JSON_MERGE_TYPE_VALUES, mergeTypeStr));
    
    JSON_HELPER_DETAILS::JsonFileData *dstJson = dstJsonFile->get_data();
    JSON_HELPER_DETAILS::JsonFileData *patchJson = patchJsonFile->get_data();
    
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

// Returns nullptr if unsuccessful
JsonFile *JsonHelper::_load_json_from_cache(const fs::path &filepath) {
     _jsonHelperMutex.lock();
    if(_fileCache.find(filepath) == _fileCache.end()) {
        try {
            _fileCache[filepath] = new JsonFile(filepath);
        } catch (nlohmann::detail::parse_error &err) {
            _jsonHelperMutex.unlock();
            return nullptr;
        }
    }
    _jsonHelperMutex.unlock();
    return _fileCache[filepath];
}