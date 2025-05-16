#include "match.h"

using namespace DkrAssetsTool;

RegexMatchGroup::RegexMatchGroup(std::string &text, int offset) : _text(text), _offset(offset) {
}

RegexMatchGroup::~RegexMatchGroup() {
}

std::string RegexMatchGroup::get_text() {
    return _text;
}

size_t RegexMatchGroup::get_text_length() {
    return _text.length();
}

int RegexMatchGroup::get_offset() {
    return _offset;
}

RegexMatch::RegexMatch() {
}

RegexMatch::~RegexMatch() {
}

size_t RegexMatch::group_count() {
    return _groups.size();
}

std::string EMPTY_STRING = "";
RegexMatchGroup EMPTY_GROUP(EMPTY_STRING, -1);

RegexMatchGroup &RegexMatch::get_group(size_t index) {
    if(index >= _groups.size()) {
        return EMPTY_GROUP;
    }
    return _groups[index];
}

void RegexMatch::_add_to_group(std::string text, size_t textOffset) {
    _groups.push_back(RegexMatchGroup(text, textOffset));
}
