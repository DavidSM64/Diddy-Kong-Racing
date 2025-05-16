#pragma once

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <type_traits> // for is_integral_v
#include <any>
#include <optional>
#include <memory>

#include "helpers/fileHelper.h"

namespace DkrAssetsTool {

namespace JSON_HELPER_DETAILS {
    // Only forward declared here, cause I don't want to expose the JSON library in the header.
    // This will allow me to change the implementation if I want to in the future.
    class JsonFileData;
}

// Read-Only JSON class
class JsonFile {
    public:
        JsonFile(std::string filepath);
        ~JsonFile();
        
        std::string get_string(const std::string &ptr, const std::string &defaultValue = "") const;
        std::string get_string_lowercase(const std::string &ptr, const std::string &defaultValue = "") const;
        std::string get_string_uppercase(const std::string &ptr, const std::string &defaultValue = "") const;
        fs::path get_path(const std::string &ptr, const std::string &defaultValue = "") const;
        void copy_string_to(const std::string &ptr, char *output, size_t maxLengthForOutput, const std::string &defaultValue = "") const;
        int get_int(const std::string &ptr, const int &defaultValue = -1) const;
        bool get_bool(const std::string &ptr, const bool &defaultValue = false) const;
        double get_float(const std::string &ptr, const double &defaultValue = 0.0) const;
        std::any get_any(const std::string& ptr) const;
        
        template<typename T>
        void get_array(const std::string &ptr, std::vector<T> &arr) const;
        
        template <typename T>
        int get_index_of_elem_in_array(const std::string &ptr, T elem) const;
        
        template <typename T>
        T get_elem_from_array(const std::string &ptr, size_t index) const;
        
        template<typename T, typename T2>
        std::optional<T> get_elem_from_object_array_that_has_property(const std::string& ptr, const std::string& valueName, const std::string& propertyName, T2 propertyValue) const;

        template<typename T>
        std::optional<size_t> get_index_of_object_that_has_property(const std::string& ptr, const std::string& propertyName, T propertyValue) const;

        // I made this as a faster version of `get_index_of_object_that_has_property`, for when that gets called a lot.
        // With this map, you use the property value (sha1 hash for example) to get the index in the array.
        template<typename T>
        std::unordered_map<T, std::vector<size_t>> create_map_of_indices_from_property_value(const std::string& ptr, const std::string& propertyName) const;

        std::vector<std::string> get_keys_of_object(const std::string& ptr) const;

        std::vector<std::string> get_all_pointers() const;

        size_t length_of_array(const std::string &ptr) const;
        size_t length_of_string(const std::string &ptr) const;
        bool has(const std::string &ptrStr) const;
        
        bool is_value_a_number(const std::string &ptr) const;
        bool is_value_a_bool(const std::string &ptr) const;
        bool is_value_a_string(const std::string &ptr) const;
        bool is_value_an_array(const std::string &ptr) const;
        bool is_value_an_object(const std::string &ptr) const;
        bool is_value_null(const std::string &ptr) const;
        
        fs::path get_filepath() const;
        JSON_HELPER_DETAILS::JsonFileData *get_data() const;
    private:
        std::string _filepath;
        std::unique_ptr<JSON_HELPER_DETAILS::JsonFileData> _data;
};

// Write-Only JSON class
class WritableJsonFile {
    public:
        WritableJsonFile(std::string outFilepath);
        ~WritableJsonFile();
        
        void new_object(const std::string &ptr);
        void new_array(const std::string &ptr);
        void set_string(const std::string &ptr, const std::string &value);
        void set_string_if_not_empty(const std::string& ptr, const std::string& value);
        void set_path(const std::string &ptr, fs::path value);
        void set_int(const std::string &ptr, const int value);
        void set_int_if_not_value(const std::string &ptr, const int value, const int checkValue);
        void set_int_if_not_zero(const std::string &ptr, const int value);
        void set_float(const std::string &ptr, double value, const int precision = 0);
        void set_float_if_not_zero(const std::string& ptr, double value, const int precision = 0);
        void set_bool(const std::string &ptr, const bool value);
        void set_bool_if_true(const std::string &ptr, const bool value);
        void set_null(const std::string &ptr);
        
        template<typename T>
        void set_array(const std::string &ptr, const std::vector<T> &arr);
        
        void save();
        
    private:
        std::string _outFilepath = "";
        std::shared_ptr<JSON_HELPER_DETAILS::JsonFileData> _data;
};

// Represents a json file with limited read/write capability.
class StatJsonFile {
    public:
        StatJsonFile(fs::path filepath);
        ~StatJsonFile();
        
        std::string get_entry(const fs::path &path);
        void set_entry(const fs::path &path, const std::string &value);
        
        template<typename T>
        T get_value(const std::string ptr, T defaultValue);

        template<typename T>
        void set_value(const std::string ptr, T value);
        
        void save();
    private:
        fs::path _filepath;
        JSON_HELPER_DETAILS::JsonFileData *_data;
};

namespace JsonHelper {
    std::optional<std::reference_wrapper<JsonFile>> get_file(fs::path filepath);
    void patch_json(const fs::path &dst, const fs::path &patch);
}

}
