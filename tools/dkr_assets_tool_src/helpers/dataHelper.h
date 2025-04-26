#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>

#include "libs/bytes_view.hpp"

namespace DkrAssetsTool {

namespace DataHelper {
    
    // ALigns length to 16-bytes.
    size_t align16(size_t length);
    
    // ALigns length to 8-bytes.
    size_t align8(size_t length);
    
    // ALigns length to 4-bytes.
    size_t align4(size_t length);
    
    bool is_power_of_two(uint32_t value);
    
    std::string make_sha1_hash_of_bytes(const std::vector<uint8_t>& bytes);
    std::string make_sha1_hash_of_bytes(BytesView bytes);
    
    // Returns -1 if element was not found.
    template <typename T>
    int vector_index_of(const std::vector<T> &vec, T element) {
        auto it = std::find(vec.begin(), vec.end(), element); // Iterator for the element.
        
        if(it == vec.end()) {
            // Not found.
            return -1;
        }
        
        // Element was found, get index into the array.
        return it - vec.begin();
    }
    
    // Returns -1 if element was not found.
    template <typename T>
    bool vector_has(const std::vector<T> &vec, T element) {
        auto it = std::find(vec.begin(), vec.end(), element); // Iterator for the element.
        
        if(it == vec.end()) {
            // Not found.
            return false;
        }
        
        // Element was found, get index into the array.
        return true;
    }
}

}