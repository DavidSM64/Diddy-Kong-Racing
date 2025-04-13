#pragma once

#include <vector>
#include <cstdint>

namespace DkrAssetsTool {
namespace GzipHelper {
    
    std::vector<uint8_t> decompress_gzip(std::vector<uint8_t> &compressedData);
    
    // Note: uncompressedData will become garbled (Don't use it after this function!).
    std::vector<uint8_t> compress_gzip(std::vector<uint8_t> &uncompressedData);
};
}