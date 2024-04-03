#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>

/**
 * Singleton class that has useful functions for helping with data.
 */
class DataHelper {
public:
    // Probably not needed?
    static DataHelper& get() {
        static DataHelper instance;
        return instance;
    }
    
    // ALigns length to 16-bytes.
    static size_t align16(size_t length);
    
    // ALigns length to 8-bytes.
    static size_t align8(size_t length);
    
    // ALigns length to 4-bytes.
    static size_t align4(size_t length);
    
    static bool is_power_of_two(uint32_t value);
    
    // Returns -1 if element was not found.
    template <typename T>
    static int vector_index_of(const std::vector<T> &vec, T element) {
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
    static bool vector_has(const std::vector<T> &vec, T element) {
        auto it = std::find(vec.begin(), vec.end(), element); // Iterator for the element.
        
        if(it == vec.end()) {
            // Not found.
            return false;
        }
        
        // Element was found, get index into the array.
        return true;
    }
};
