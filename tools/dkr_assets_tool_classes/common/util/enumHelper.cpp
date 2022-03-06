#include "enumHelper.h"

bool hasLoadedEnums = false;
std::map<std::string, std::map<std::string, int>> enums;
void make_sure_enums_are_loaded() {
    if(hasLoadedEnums) {
        return;
    }
    enums = get_enums();
    hasLoadedEnums = true;
}

std::string get_enum_string_from_value(std::string enumName, int value) {
    make_sure_enums_are_loaded();
    for (auto const& x : enums[enumName]) {
        if(x.second == value) {
            return x.first;
        }
    }
    return "null";
}

int get_enum_value_from_string(std::string enumName, std::string value) {
    make_sure_enums_are_loaded();
    return enums[enumName][value];
}

std::vector<std::string> get_enum_keys(std::string enumName) {
    make_sure_enums_are_loaded();
    std::vector<std::string> keys;
    for (auto const& x : enums[enumName]) {
        keys.push_back(x.first);
    }
    return keys;
}
