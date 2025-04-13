#pragma once

#include <vector>
#include <string>

namespace DkrAssetsTool {
class RegexMatchGroup {
public:
    RegexMatchGroup(std::string &text, int offset);
    ~RegexMatchGroup();
    
    std::string get_text();
    size_t get_text_length();
    
    int get_offset();
    
private:
    std::string _text;
    int _offset;
};

class RegexMatch {
public:
    RegexMatch();
    ~RegexMatch();
    size_t group_count();
    
    RegexMatchGroup &get_group(size_t index);
    
    // This shouldn't be used outside of RegexHelper.
    void _add_to_group(std::string text, size_t textOffset);
private:
    std::vector<RegexMatchGroup> _groups;
};
}
