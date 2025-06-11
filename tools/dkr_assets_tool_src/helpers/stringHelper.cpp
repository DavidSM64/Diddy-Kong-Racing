#include "stringHelper.h"

#include "helpers/debugHelper.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <cstring> // for std::strchr

using namespace DkrAssetsTool;

bool StringHelper::has(const std::string &input, const char* substring) {
    return input.find(substring) != std::string::npos;
}

bool StringHelper::has(const std::string &input, const std::string substring) {
    return input.find(substring) != std::string::npos;
}

void StringHelper::make_lowercase(std::string& input) {
    for(char& character : input) {
        character = std::tolower(character);
    }
}

void StringHelper::make_uppercase(std::string& input) {
    for(char& character : input) {
        character = std::toupper(character);
    }
}
    
std::string StringHelper::lowercase(std::string input) {
    make_lowercase(input);
    return input;
}

std::string StringHelper::uppercase(std::string input) {
    make_uppercase(input);
    return input;
}

bool StringHelper::starts_with(const std::string &input, const std::string &sub) {
    return input.rfind(sub, 0) == 0;
}

bool StringHelper::ends_with(const std::string &input, const std::string &sub) {
    if (sub.size() > input.size()) return false;
    return std::equal(input.begin() + input.size() - sub.size(), input.end(), sub.begin());
}

bool StringHelper::is_a_number(const std::string& input) {
    return (!input.empty()) && (std::all_of(input.begin(), input.end(), ::isdigit));
}

const char* WHITESPACE = " \t\n\r\f\v";

void StringHelper::rtrim(std::string& input) {
    input.erase(input.find_last_not_of(WHITESPACE) + 1);
}

void StringHelper::ltrim(std::string& input) {
    input.erase(0, input.find_first_not_of(WHITESPACE));
}

void StringHelper::trim(std::string& input) {
    ltrim(input);
    rtrim(input);
}

void StringHelper::remove_all_whitespace(std::string &input) {
    input.erase(std::remove_if(input.begin(), input.end(), [](char c) {
        return std::strchr(WHITESPACE, c) != nullptr;
    }), input.end());
}

std::string StringHelper::simplify(const std::string& input) {
    std::string output(input); // Create a copy of the input

    make_lowercase(output);
    remove_all_whitespace(output);
    replace(output, "-", ""); // Remove all dashes
    replace(output, "_", ""); // Remove all underscores

    return output;
}

void StringHelper::replace(std::string &input, std::string oldPattern, std::string newPattern) {
    size_t pos = 0;
    while((pos = input.find(oldPattern, pos)) != std::string::npos) {
         input.replace(pos, oldPattern.length(), newPattern);
         pos += newPattern.length();
    }
}

void StringHelper::split(const std::string &input, const char delim, std::vector<std::string> &out) {
    std::stringstream ss(input);
    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

void StringHelper::split_and_trim(const std::string &input, const char delim, std::vector<std::string> &out) {
    std::stringstream ss(input);
    std::string s;
    while (std::getline(ss, s, delim)) {
        trim(s);
        out.push_back(s);
    }
}

void StringHelper::split(const std::string &input, const std::vector<char> delims, std::vector<std::string> &out) {
    if(delims.empty()) {
        return;
    }
    
    size_t startIndex = 0;
    for(size_t i = 0; i < input.size(); i++) {
        for(char delim : delims) {
            if(input[i] == delim) {
                // Output string.
                out.emplace_back(input.substr(startIndex, i - startIndex));
                startIndex = i + 1;
                break;
            }
        }
    }
}

void StringHelper::split_and_trim(const std::string &input, const std::vector<char> delims, std::vector<std::string> &out) {
    if(delims.empty()) {
        return;
    }
    
    size_t startIndex = 0;
    for(size_t i = 0; i < input.size(); i++) {
        for(char delim : delims) {
            if(input[i] == delim) {
                // Output string.
                std::string outEntry = input.substr(startIndex, i - startIndex);
                trim(outEntry);
                out.emplace_back(outEntry);
                startIndex = i + 1;
                break;
            }
        }
    }
}

std::string StringHelper::join(const std::vector<std::string> &input, std::string delim, size_t startIndex) {
    std::stringstream ss;
    for(size_t i = startIndex; i < input.size(); i++) {
        ss << input[i];
        if(i < input.size() - 1) {
            ss << delim;
        }
    }
    return ss.str();
}

int StringHelper::find_closing_brace(const std::string &input, int inputOffset) {
    int curOffset = inputOffset;
    int limit = input.length();
    
    bool encounteredOpeningBrace = false;
    int depth = 0;
    while(curOffset < limit) {
        char inputChar = input[curOffset];
        switch(inputChar) {
            case '{':
                encounteredOpeningBrace = true;
                depth++;
                break;
            case '}':
                DebugHelper::assert(encounteredOpeningBrace, "(StringHelper::find_closing_brace) Got closing brace before an open one!");
                depth--;
                if(depth < 1) {
                    return curOffset;
                }
                break;
        }
        curOffset++;
    }
    
    // Could not find a closing brace!
    return -1;
}

std::string StringHelper::remove_comments_from_c_code(std::string code) {
    std::stringstream ss; // Use stringstream to build the result
    bool inMultilineComment = false;
    bool inSinglelineComment = false;
    bool inString = false; // To handle comments inside string literals

    for (size_t i = 0; i < code.length(); ++i) {
        // Check for beginning of string literal
        if (!inMultilineComment && !inSinglelineComment && code[i] == '"') {
            inString = !inString;
            ss << code[i]; // Append to stringstream
            continue;
        }

        // If we are inside a string, just append the character
        if (inString) {
            ss << code[i]; // Append to stringstream
            // Handle escaped quotes inside string
            if (code[i] == '\\' && i + 1 < code.length() && code[i + 1] == '"') {
                ss << code[i + 1];
                i++;
            }
            continue;
        }

        // Check for start of multi-line comment /*
        if (!inSinglelineComment && i + 1 < code.length() &&
            code[i] == '/' && code[i + 1] == '*') {
            inMultilineComment = true;
            i++; // Skip the '*'
            continue;
        }

        // Check for end of multi-line comment */
        if (inMultilineComment && i + 1 < code.length() &&
            code[i] == '*' && code[i + 1] == '/') {
            inMultilineComment = false;
            i++; // Skip the '/'
            continue;
        }

        // Check for start of single-line comment //
        if (!inMultilineComment && i + 1 < code.length() &&
            code[i] == '/' && code[i + 1] == '/') {
            inSinglelineComment = true;
            i++; // Skip the second '/'
            continue;
        }

        // Check for end of single-line comment (newline)
        if (inSinglelineComment && code[i] == '\n') {
            inSinglelineComment = false;
            ss << code[i]; // Keep the newline character, append to stringstream
            continue;
        }

        // If not in any comment, append the character to the result
        if (!inMultilineComment && !inSinglelineComment) {
            ss << code[i];
        }
    }
    
    return ss.str();
}

std::string StringHelper::upper_snake_case_to_pascal_case(const std::string &input) {
    std::stringstream out;
    bool isFirst = true;
    for(size_t i = 0; i < input.length(); i++) {
        if(input[i] == '_') {
            isFirst = true;
        } else {
            if(isFirst) {
                out << input[i];
                isFirst = false;
            } else {
                out << static_cast<char>(std::tolower(input[i]));
            }
        }
    }
    
    return out.str();
}

std::string StringHelper::pascal_case_to_upper_snake_case(const std::string &input) {
    std::stringstream out;

    for (size_t i = 0; i < input.size(); i++) {
        char ch = input[i];
        if (std::isupper(ch) && i != 0) {
            out << '_';
        }
        out << static_cast<char>(std::toupper(ch));
    }

    return out.str();
}

std::string StringHelper::to_hex(uint64_t value, int numDigits) {
    std::stringstream ss;
    ss << std::hex;
    if(numDigits > 0) {
        ss << std::setw(numDigits) << std::setfill('0');
    }
    ss << value;
    return ss.str();
}

std::string StringHelper::to_uppercase_hex(uint64_t value, int numDigits) {
    std::string out = to_hex(value, numDigits);
    make_uppercase(out);
    return out;
}

// Returns offset + length of string + 1 (for null-terminator)
size_t StringHelper::get_ascii_from_data(std::vector<uint8_t> &data, size_t offset, std::string &out) {
    char *dataAsStr = reinterpret_cast<char*>(&data[offset]);
    out = std::string(dataAsStr);
    return offset + out.length() + 1;
}