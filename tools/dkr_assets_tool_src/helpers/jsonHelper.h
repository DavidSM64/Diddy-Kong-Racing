#pragma once

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <type_traits> // for is_integral_v

#include "helpers/fileHelper.h"

namespace JSON_HELPER_DETAILS {
    // Only forward declared here, cause I don't want to expose the JSON library in the header.
    // This will allow me to change the implementation if I want to in the future.
    class JsonFileData;
}

typedef std::variant<std::string, int> JsonKey;
typedef std::variant<std::string, double, int, bool> JsonValue;

// Read-Only JSON class
class JsonFile {
    public:
        JsonFile(std::string filepath);
        ~JsonFile();
        
        std::string get_string(const std::string &ptr, const std::string &defaultValue = "");
        std::string get_string_lowercase(const std::string &ptr, const std::string &defaultValue = "");
        std::string get_string_uppercase(const std::string &ptr, const std::string &defaultValue = "");
        fs::path get_path(const std::string &ptr, const std::string &defaultValue = "");
        void copy_string_to(const std::string &ptr, char *output, size_t maxLengthForOutput, const std::string &defaultValue = "");
        int get_int(const std::string &ptr, const int &defaultValue = -1);
        bool get_bool(const std::string &ptr, const bool &defaultValue = false);
        double get_float(const std::string &ptr, const double &defaultValue = 0.0);
        
        template<typename T>
        void get_array(const std::string &ptr, std::vector<T> &arr);
        
        template <typename T>
        int get_index_of_elem_in_array(const std::string &ptr, T elem);
        
        template <typename T>
        T get_elem_from_array(const std::string &ptr, size_t index);

        size_t length_of_array(const std::string &ptr);
        size_t length_of_string(const std::string &ptr);
        bool has(const std::string &ptrStr);
        
        bool is_value_a_number(const std::string &ptr);
        bool is_value_a_bool(const std::string &ptr);
        bool is_value_a_string(const std::string &ptr);
        bool is_value_an_array(const std::string &ptr);
        bool is_value_an_object(const std::string &ptr);
        bool is_value_null(const std::string &ptr);
        
        fs::path get_filepath();
        JSON_HELPER_DETAILS::JsonFileData *get_data();
    private:
        std::string _filepath;
        JSON_HELPER_DETAILS::JsonFileData *_data;
};

// Write-Only JSON class
class WritableJsonFile {
    public:
        WritableJsonFile(std::string outFilepath);
        ~WritableJsonFile();
        
        void new_object(const std::string &ptr);
        void new_array(const std::string &ptr);
        void set_string(const std::string &ptr, const std::string &value);
        void set_path(const std::string &ptr, fs::path value);
        void set_int(const std::string &ptr, const int value);
        void set_int_if_not_value(const std::string &ptr, const int value, const int checkValue);
        void set_int_if_not_zero(const std::string &ptr, const int value);
        void set_float(const std::string &ptr, double value, const int precision = 0);
        void set_bool(const std::string &ptr, const bool value);
        void set_bool_if_true(const std::string &ptr, const bool value);
        void set_null(const std::string &ptr);
        
        void save();
        
    private:
        std::string _outFilepath;
        JSON_HELPER_DETAILS::JsonFileData *_data;
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

/**
 * Singleton class that deals with saving & loading json files.
 */
class JsonHelper {
public:
    static JsonHelper& get() {
        static JsonHelper instance;
        return instance;
    }
    
    bool get_file(fs::path filepath, JsonFile **out);
    void patch_json(const fs::path &dst, const fs::path &patch);
    
private:
    std::unordered_map<std::string, JsonFile*> _fileCache;
    std::mutex _jsonHelperMutex;
    
    // Returns nullptr if unsuccessful
    JsonFile *_load_json_from_cache(const fs::path &filepath);
    
};
