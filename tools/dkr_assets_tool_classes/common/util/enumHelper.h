#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <regex>
#include <mutex>

#include "../../libs/calculator.hpp"

#include "fileHelper.h"

void generate_enums_cache(std::string enumsHeaderPath);

std::string get_enum_string_from_value(std::string enumName, int value);
int get_enum_value_from_string(std::string enumName, std::string value);
std::vector<std::string> get_enum_keys(std::string enumName);


