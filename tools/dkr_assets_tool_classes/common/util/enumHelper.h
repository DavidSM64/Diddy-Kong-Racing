#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#define DKR_ASSETS_TOOL
#include "../../../../include/enums.h"

std::string get_enum_string_from_value(std::string enumName, int value);
int get_enum_value_from_string(std::string enumName, std::string value);
std::vector<std::string> get_enum_keys(std::string enumName);


