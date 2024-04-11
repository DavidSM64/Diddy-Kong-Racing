/**
 * C++11 std version of the regex helper
*/

#include "regexStd.h"
#include "helpers/debugHelper.h"

void RegexHelperStl::get_matches(const std::string &input, const std::string &regexInput, std::vector<RegexMatch> &out, int startOffset) {
    std::regex rgx(regexInput, std::regex_constants::ECMAScript);
    std::smatch matches;
    std::string::const_iterator searchStart(input.cbegin() + startOffset);
    while (std::regex_search(searchStart, input.cend(), matches, rgx)) {
        RegexMatch newMatch;
        for (size_t i = 0; i < matches.size(); i++) {
            std::string text = matches[i].str();
            int pos = matches.position(i);
            if(text.empty()) {
                pos = -1;
            }
            newMatch._add_to_group(text, pos);
        }
        out.push_back(newMatch);
        searchStart = matches.suffix().first;
    }
}

RegexMatch *RegexHelperStl::get_first_match(const std::string &input, const std::string &regexInput, int startOffset) {
    std::regex rgx(regexInput, std::regex_constants::ECMAScript);
    std::smatch matches;
    std::string::const_iterator searchStart(input.cbegin() + startOffset);
    std::regex_search(searchStart, input.cend(), matches, rgx);
    
    if(matches.size() < 1) {
        return nullptr; // No matches found.
    }
    RegexMatch *newMatch = new RegexMatch();
    for (size_t i = 0; i < matches.size(); i++) {
        std::string text = matches[i].str();
        int pos = matches.position(i);
        if(text.empty()) {
            pos = -1;
        }
        newMatch->_add_to_group(text, pos);
    }
    return newMatch;
}

std::string RegexHelperStl::get_name() {
    return "C++11 STL";
};
