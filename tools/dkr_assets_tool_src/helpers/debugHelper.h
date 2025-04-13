#pragma once

#include <cstdarg>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

// Terminal colors
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define BLUE_TEXT "\033[1;34m"
#define MAGENTA_TEXT "\033[1;35m"
#define CYAN_TEXT "\033[1;36m"

#define RESET_TEXT "\033[0m"

namespace DkrAssetsTool {

/**
 * Singleton class that deals with info / logging / errors
 */
class DebugHelper {
public:
    // From https://gist.github.com/tzutalin/fd0340a93bb8d998abb9
    class DebugTimer {
    public:
        DebugTimer();
        void reset();
        std::string elapsed();
    private:
        typedef std::chrono::high_resolution_clock clock_;
        typedef std::chrono::duration<double, std::ratio<1>> second_;
        std::chrono::time_point<clock_> m_beg;
    };

    static DebugHelper& get() {
        static DebugHelper instance;
        return instance;
    }
    
    template<class... Args>
    static void info(Args... args) {
        std::stringstream ss;
        ss << CYAN_TEXT << "INFO: " << RESET_TEXT;
        (ss << ... << args);
        ss << std::endl;
        std::cout << ss.str();
    }
    
    template<class... Args>
    static void info_custom(const char *type, const char *color, Args... args) {
        std::stringstream ss;
        ss << color << type << ": " << RESET_TEXT;
        (ss << ... << args);
        ss << std::endl;
        std::cout << ss.str();
    }
    
    template<class... Args>
    static void info_verbose(Args... args) {
        if(!DebugHelper::get().is_verbose()) {
            return;
        }
        info(args...);
    }
    
    template<class... Args>
    static void warn(Args... args) {
        std::stringstream ss;
        ss << YELLOW_TEXT << "WARNING: ";
        (ss << ... << args);
        ss  << RESET_TEXT << std::endl;
        std::cout << ss.str();
    }
    
    template<class... Args>
    static void error(Args... args) {
        std::stringstream ss;
        ss << RED_TEXT << "ERROR: ";
        (ss << ... << args);
        ss  << RESET_TEXT << std::endl;
        std::cout << ss.str();
        throw 1;
    }
    
    template<class... Args>
    static void error_no_throw(Args... args) {
        std::stringstream ss;
        ss << RED_TEXT << "ERROR: ";
        (ss << ... << args);
        ss  << RESET_TEXT << std::endl;
        std::cout << ss.str();
    }
    
    template<class... Args>
    static void assert(bool condition, Args... args) {
        if(!DebugHelper::get().using_asserts()) return;
        if(!condition) {
            DebugHelper::error(args...);
        }
    }
    
    // For use in files that have <cassert> included.
    template<class... Args>
    static void assert_(bool condition, Args... args) {
        assert(condition, args...);
    }
    
    template<typename T>
    static std::string vector_to_string(std::vector<T> vec, int maxLength=-1) {
        std::stringstream ss;
        size_t len = (maxLength < 1) ? vec.size() : maxLength;
        
        ss << "[";
        for(size_t i = 0; i < len; i++) {
            ss << vec[i];
            if(i < len - 1) {
                ss << ", ";
            }
        }
        ss << "]";
        
        return ss.str();
    }
    
    static std::string bytes_to_hex_string(uint8_t *data, uint32_t dataLength) {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for(uint32_t i = 0; i < dataLength; ++i)
            ss << std::setw(2) << static_cast<int>(data[i]) << " ";
        return ss.str();
    }
    
    static std::string to_hex(uint32_t val) {
        std::stringstream ss;
        ss << "0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0') << val << std::nouppercase << std::dec;
        return ss.str();
    }
    
    void set_verbose(bool isVerbose = true);
    bool is_verbose();
    void set_asserts(bool useAsserts = true);
    bool using_asserts();
private:
    bool _verbose = false;
    bool _assertsEnabled = false;
    int timerChannel = 0;
};
}
