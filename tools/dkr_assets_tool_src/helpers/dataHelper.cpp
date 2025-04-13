#include "dataHelper.h"

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
