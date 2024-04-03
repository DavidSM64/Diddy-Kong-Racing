/**
 * C++11 std version of the regex helper
*/

#include <regex>
#include <string>

#include "match.h"

class RegexHelperStl {
public:
    static void get_matches(const std::string &input, const std::string &regexInput, std::vector<RegexMatch> &out, int startOffset);
    static RegexMatch *get_first_match(const std::string &input, const std::string &regexInput, int startOffset);
    static std::string get_name();
};
