#pragma once

#include <string>
#include <vector>

#include "regex/match.h"

// Supported regex engine libraries
enum RegexEngine {
    STL, // standard C++11 library
    PCRE2
};

class RegexHelper {
public:
    static RegexHelper& get() {
        static RegexHelper instance;
        return instance;
    }
    
    RegexHelper();

    static void get_matches(const std::string &input, const std::string &regexInput, std::vector<RegexMatch> &out, int startOffset = 0);
    
    static RegexMatch *get_first_match(const std::string &input, const std::string &regexInput, int startOffset = 0);
    
    static bool set_engine(RegexEngine engine);
    
    static std::string get_current_engine_name();
private:
    RegexEngine _currentEngine;
};
