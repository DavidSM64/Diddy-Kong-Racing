#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

// C++17
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;

enum ConfigRangeType {
    UNDEFINED,
    BINARY,
    NOEXTRACT,
    COMPRESSED,
    CHEATS,
    TEXTURE
};

class ConfigRange {
public:
    ConfigRange(int start, int size, ConfigRangeType type, std::vector<std::string> properties);
    ~ConfigRange();
    
    int get_start();
    int get_size();
    ConfigRangeType get_type();
    std::string get_property(int propertyIndex);

private:
    int rangeStart, rangeSize;
    ConfigRangeType rangeType;
    std::vector<std::string> rangeProperties;
};

class Config {
public:
    Config(std::string directory, std::string filename);
    ~Config();
    
    bool is_supported();
    std::string get_name();
    std::string get_md5();
    std::string get_subfolder();
    int get_size();
    int get_number_of_ranges();
    ConfigRange get_range(int index);

private:
    void parse(std::string text);
    void parse_property(std::string name, std::string value);
    void parse_range(std::string rangeSize, std::string rangeProperties);
    
    ConfigRangeType get_range_type(std::string typeString);
    
    std::string read_file(std::string filename);
    std::string trim(std::string input);
    std::string strip_comments(std::string input);
    std::vector<std::string> split_string(std::string s, char delim);
    std::string get_lowercase(std::string input);
    
    bool notSupported;
    std::string directory;
    std::string name;
    std::string md5;
    std::string subfolder;
    std::vector<ConfigRange> ranges;
    
    int currentRangeOffset = 0;
};
