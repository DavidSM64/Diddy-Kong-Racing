#pragma once

#include <string>
#include <vector>

// These are functions that I would've expected to be a part of std::string. (Except for a few)
class StringHelper {
public:
    static bool has(const std::string &input, const char *substring);

    static void make_lowercase(std::string &input);
    static void make_uppercase(std::string &input);
    
    static bool starts_with(const std::string &input, const std::string &sub);
    static bool ends_with(const std::string &input, const std::string &sub);
    
    // Trim functions from: https://stackoverflow.com/a/25385766
    static void rtrim(std::string &input); // Trim whitespace from the end of the string
    static void ltrim(std::string &input); // Trim whitespace from the start of the string
    static void trim(std::string &input); // Trim whitespace from both sides
    
    static void remove_all_whitespace(std::string &input);
    
    static void replace(std::string &input, std::string oldPattern, std::string newPattern);
    
    // Splits the input string by a single character into out, so "A,B,C" would be put into [A,B,C]. input is NOT modified!
    static void split(std::string &input, const char delim, std::vector<std::string> &out);
    static void split_and_trim(std::string &input, const char delim, std::vector<std::string> &out);
    
    // Returns the index of the closing brace of the first opening brace encountered. Or -1 if none was encountered.
    static int find_closing_brace(const std::string &input, int inputOffset=0);
    
    // Converts `FOO_BAR` to `FooBar`.
    static std::string upper_snake_case_to_pascal_case(const std::string &input);
    
    static std::string to_hex(uint64_t value, int numDigits=0);
    
    // Returns offset + length of string + 1 (for null-terminator)
    static size_t get_ascii_from_data(std::vector<uint8_t> &data, size_t offset, std::string &out);
};
