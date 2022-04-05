#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread>

#include "../common/util.h"

class AssetEnumsHeader {
public:
    AssetEnumsHeader(std::string dstPath);
    ~AssetEnumsHeader();
private:
    void write_comment(std::stringstream &out, std::string text);
    void write_header_comment(std::stringstream &out, std::string text);
    void write_order_section(std::stringstream &out, std::string name, std::vector<std::string> &order);
};
