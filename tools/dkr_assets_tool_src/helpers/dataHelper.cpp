#include "dataHelper.h"
#include "libs/sha1.hpp"
#include <streambuf>

using namespace DkrAssetsTool;

#define ALIGN_N(val, N) ((val + (N - 1)) & (~(N - 1)))

// ALigns length to 16-bytes.
size_t DataHelper::align16(size_t length) {
    return ALIGN_N(length, 16);
}

// ALigns length to 8-bytes.
size_t DataHelper::align8(size_t length) {
    return ALIGN_N(length, 8);
}

// ALigns length to 4-bytes.
size_t DataHelper::align4(size_t length) {
    return ALIGN_N(length, 4);
}

bool DataHelper::is_power_of_two(uint32_t value) {
    if(value == 0) {
        return false;
    }
    return (value & (value - 1)) == 0; 
}

// As far as I know, this is needed to convert a std::vector<uint8_t> into a std::istream
class VectorStreamBuf : public std::streambuf {
public:
    VectorStreamBuf(const std::vector<uint8_t>& vec) {
        char* begin = reinterpret_cast<char*>(const_cast<uint8_t*>(vec.data()));
        this->setg(begin, begin, begin + vec.size());
    }
};

std::string make_sha1_hash_of_bytes(const std::vector<uint8_t>& bytes) {
    VectorStreamBuf buf(bytes);
    std::istream stream(&buf); // Need an std::istream for the sha1 library.
    SHA1 sha1;
    sha1.update(stream);
    return sha1.final();
}

std::string DataHelper::make_sha1_hash_of_bytes(BytesView bytes) {
    BytesViewStreamBuf buf(bytes);
    std::istream stream(&buf); // Need an std::istream for the sha1 library.
    SHA1 sha1;
    sha1.update(stream);
    return sha1.final();
}

