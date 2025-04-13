  #pragma once

#include <cstdint>
#include <cstdlib>
#include <vector>

namespace DkrAssetsTool {
namespace MiscHelper {
    void process_cheats_encryption(uint8_t *data, size_t dataSize);
    void process_cheats_encryption(std::vector<uint8_t> &data);
}
}