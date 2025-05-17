/**
 * C++11 std version of the regex helper
*/

#include <regex>
#include <string>

#include "match.h"

namespace DkrAssetsTool {
namespace RegexHelperStl {
    void get_matches(const std::string &input, const std::string &regexInput, std::vector<RegexMatch> &out, int startOffset);
    RegexMatch *get_first_match(const std::string &input, const std::string &regexInput, int startOffset);
    std::string get_name();
}
}
