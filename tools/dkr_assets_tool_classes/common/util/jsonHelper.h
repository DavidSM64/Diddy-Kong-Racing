#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../../libs/json.hpp"

#include "fileHelper.h"

void write_json(json::JSON &assetsJSON, std::string filename);
json::JSON load_assets_json(std::string assetsFolder, std::string jsonName);
void setAssetsFolderPath(std::string path);
std::string get_build_id_from_section(std::string sectionName, int index);
int get_index_of_string_from_json_array(json::JSON &jsonArray, std::string value);
int get_index_from_build_id(std::string sectionName, std::string buildId);
int get_tex_2d_index_from_build_id(std::string texBuildId);
std::vector<std::string> get_section_order(std::string sectionName);
std::vector<std::string> get_assets_order();
std::string get_filename_from_section_entry(std::string sectionName, std::string entryName);
std::string get_source_section_for_table(std::string tableSectionName);
int get_asset_count();
void combine_json_files(std::string src1Path, std::string src2Path, std::string outputPath);

// The variadic templates require C++17. They also need to be defined in the header, not in the cpp file.

// Do not use these outside of this file! They are exposed in the header only for the variadic template functions.
std::vector<std::string> get_order(json::JSON orderJson);
json::JSON *get_section_json(std::string sectionName);
json::JSON *load_json_file(std::string filename);

template<typename FirstKey, typename ...RestKeys>
inline json::JSON json_get(json::JSON &json, FirstKey const& key, RestKeys const&... rest_keys) {
    if constexpr(sizeof...(RestKeys) == 0) {
        return json[key];
     } else {
        return json_get(json[key], rest_keys...);
    }
}

template<typename FirstKey, typename ...RestKeys>
inline bool _json_has_key(json::JSON &json, FirstKey const& key, RestKeys const&... rest_keys) {
    if constexpr(sizeof...(RestKeys) == 0)
        return json.hasKey(key);
    else
        return _json_has_key(json[key], rest_keys...);
}

template<typename FirstKey, typename ...RestKeys>
inline int get_int_from_json(std::string filename, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = load_json_file(filename);
    return json_get(*json, key, rest_keys...).ToInt();
}

template<typename FirstKey, typename ...RestKeys>
inline bool get_bool_from_json(std::string filename, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = load_json_file(filename);
    return json_get(*json, key, rest_keys...).ToBool();
}

template<typename FirstKey, typename ...RestKeys>
inline float get_float_from_json(std::string filename, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = load_json_file(filename);
    return json_get(*json, key, rest_keys...).ToFloat();
}

template<typename FirstKey, typename ...RestKeys>
inline std::string get_string_from_json(std::string filename, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = load_json_file(filename);
    return json_get(*json, key, rest_keys...).ToString();
}

template<typename FirstKey, typename ...RestKeys>
inline std::vector<std::string> get_array_from_json(std::string filename, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = load_json_file(filename);
    json::JSON arrayJson = json_get(*json, key, rest_keys...);
    return get_order(arrayJson);
}

inline std::vector<std::string> get_array_from_json(std::string filename) {
    return get_order(*load_json_file(filename));
}

template<typename FirstKey, typename ...RestKeys>
inline int get_array_length_from_json(std::string filename, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = load_json_file(filename);
    return json_get(*json, key, rest_keys...).length();
}

template<typename FirstKey, typename ...RestKeys>
inline bool json_has_key(std::string filename, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = load_json_file(filename);
    if constexpr(sizeof...(RestKeys) == 0) {
        return json->hasKey(key);
    } else {
        return _json_has_key(*json, key, rest_keys...);
    }
}

template<typename FirstKey, typename ...RestKeys>
inline int get_int_from_section(std::string sectionName, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = get_section_json(sectionName);
    return json_get(*json, key, rest_keys...).ToInt();
}

template<typename FirstKey, typename ...RestKeys>
inline std::string get_string_from_section(std::string sectionName, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = get_section_json(sectionName);
    return json_get(*json, key, rest_keys...).ToString();
}

template<typename FirstKey, typename ...RestKeys>
inline std::vector<std::string> get_array_from_section(std::string sectionName, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = get_section_json(sectionName);
    json::JSON arrayJson = json_get(*json, key, rest_keys...);
    return get_order(arrayJson);
}

template<typename FirstKey, typename ...RestKeys>
inline int get_array_length_from_section(std::string sectionName, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = get_section_json(sectionName);
    return json_get(*json, key, rest_keys...).length();
}

template<typename FirstKey, typename ...RestKeys>
inline bool section_has_key(std::string sectionName, FirstKey const& key, RestKeys const&... rest_keys) {
    json::JSON *json = get_section_json(sectionName);
    if constexpr(sizeof...(RestKeys) == 0)
        return json->hasKey(key);
    else
        return _json_has_key(*json, key, rest_keys...);
}



