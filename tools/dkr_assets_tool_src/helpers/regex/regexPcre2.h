/**
 * PCRE2 version of the regex helper
 */

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include <unordered_map>
#include <string>

#include "match.h"

namespace DkrAssetsTool {
namespace RegexHelperPcre2 {
    void get_matches(const std::string &input, const std::string &regexInput, std::vector<RegexMatch> &out, int startOffset);
    RegexMatch *get_first_match(const std::string &input, const std::string &regexInput, int startOffset);
    std::string get_name();
}
}
