  #pragma once

#include <cstdint>
#include <cstdlib>
#include <vector>

class MiscHelper {
public:
    static void process_cheats_encryption(uint8_t *data, size_t dataSize);
    static void process_cheats_encryption(std::vector<uint8_t> &data);
};
