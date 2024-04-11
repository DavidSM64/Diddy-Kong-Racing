#pragma once

#include <vector>
#include <cstdint>

/**
 * Singleton class that deals with compressing / decompressing asset data using gzip.
 */
class GzipHelper {
public:
    static std::vector<uint8_t> decompress_gzip(std::vector<uint8_t> &compressedData);
    
    // Note: uncompressedData will become garbled (Don't use it after this function!).
    static std::vector<uint8_t> compress_gzip(std::vector<uint8_t> &uncompressedData);
};
