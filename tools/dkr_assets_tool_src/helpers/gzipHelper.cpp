#include "gzipHelper.h"

using namespace DkrAssetsTool;

#include "libs/gzip/DKRCompression.h"

// Compression shouldn't be thread safe, but testing suggests that the mutex isn't necessary?
//#include <mutex>
//std::mutex gzipMutex;

std::vector<uint8_t> GzipHelper::decompress_gzip(std::vector<uint8_t> &compressedData) {
    //gzipMutex.lock();
    
    // Needed padding to prevent errors with decompressing.
    if(compressedData[compressedData.size() - 1] != 0) {
        compressedData.push_back(0);
        compressedData.push_back(0);
        compressedData.push_back(0);
        compressedData.push_back(0);
    }
    DKRCompression compression;
    std::vector<uint8_t> out = compression.decompressBuffer(compressedData);
    //gzipMutex.unlock();
    
    return out;
}

std::vector<uint8_t> GzipHelper::compress_gzip(std::vector<uint8_t> &uncompressedData) {
    //gzipMutex.lock();
    DKRCompression compression;
    std::vector<uint8_t> out = compression.compressBuffer(uncompressedData);
    //gzipMutex.unlock();
    return out;
}
