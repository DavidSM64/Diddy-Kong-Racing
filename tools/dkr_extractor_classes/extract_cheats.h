#pragma once

#include "extract.h"

class ExtractCheats : Extract {
public:
    ExtractCheats(ConfigRange& range, ROM& rom, json::JSON& assetsJson, std::string outDirectory);
    ~ExtractCheats();
private:
    void decrypt_data(std::vector<uint8_t>& data);
};
