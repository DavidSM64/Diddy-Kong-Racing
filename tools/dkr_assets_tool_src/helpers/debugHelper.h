#pragma once

#if defined(__GNUG__) && defined(DEBUG)
// If you want to turn off the stack trace, then set this to 0.
#define INCLUDE_STACK_TRACE 1
#else
#define INCLUDE_STACK_TRACE 0
#endif

#include <cstdarg>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <mutex>

#if INCLUDE_STACK_TRACE
// Need to have libdwarf-dev installed if you want filenames & line numbers.
#if __has_include (<dwarf.h>)
#define BACKWARD_HAS_DWARF 1
#endif
#include "libs/backward.hpp"
#endif

// Terminal colors
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define FOREST_GREEN_TEXT "\033[38;5;35m"
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
        get().set_error_occured();
        std::stringstream ss;
        ss << RED_TEXT << "ERROR: ";
        (ss << ... << args);
        ss  << RESET_TEXT << std::endl;
#if INCLUDE_STACK_TRACE
        _print_error_with_stack_trace(ss.str());
#else
        std::cout << ss.str();
#endif
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
    static std::string vector_to_string(std::vector<T> vec, int startOffset = 0, int maxLength=-1) {
        std::stringstream ss;
        size_t len = (maxLength < 1) ? vec.size() : maxLength;
        
        ss << "[";
        for(size_t i = startOffset; i < len; i++) {
            ss << vec[i];
            if(i < len - 1) {
                ss << ", ";
            }
        }
        ss << "]";
        
        return ss.str();
    }
    
    template<typename T>
    static void print_vector(std::vector<T> vec, int startOffset = 0, int maxLength=-1) {
        info(vector_to_string<T>(vec, startOffset, maxLength));
    }
    
    static void sleep(float ms) {
        std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(ms));
    }
    
    static std::string bytes_to_hex_string(const uint8_t *data, uint32_t dataLength) {
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
    
    static std::thread::id get_current_thread_id() {
        return std::this_thread::get_id();
    }
    
    void set_verbose(bool isVerbose = true);
    bool is_verbose();
    void set_asserts(bool useAsserts = true);
    bool using_asserts();
    void set_error_occured();
    bool has_error_occured();
    
private:
    bool _verbose = false;
    bool _assertsEnabled = false;
    bool _errorOccured = false;
    std::mutex _mutex;
    int timerChannel = 0;
    
    
#if INCLUDE_STACK_TRACE
    static bool _str_starts_with(const std::string &str, std::string substr) {
        if(substr.length() > str.length()) {
            return false;
        }
        for(size_t i = 0; i < substr.length(); i++) {
            if(str[i] != substr[i]) {
                return false;
            }
        }
        return true;
    }
    
    static void _print_stack_func(std::stringstream &ss, std::string functionSignature) {
        // Don't need the "DkrAssetsTool::" part, since that applies to pretty much all of my code.
        if(_str_starts_with(functionSignature, "DkrAssetsTool::")) {
            functionSignature = functionSignature.substr(15);
        }
        
        if(functionSignature.length() > 100) {
            functionSignature = functionSignature.substr(0, 97) + "...";
        }
        
        ss << " ";
        
        size_t findOpen = functionSignature.find('(');
        if(findOpen != std::string::npos) {
            size_t start = findOpen;
            while((functionSignature[start] != ':') && (start > 0)) start--;
            char curChar = functionSignature[start];
            while(!((curChar >= 'A' && curChar <= 'Z') || (curChar >= 'a' && curChar <= 'z') || (curChar == '_'))) {
                curChar = functionSignature[++start];
            }
            
            ss << functionSignature.substr(0, start);
            ss << YELLOW_TEXT << functionSignature.substr(start, findOpen - start) << RESET_TEXT;
            ss << functionSignature.substr(findOpen);
        } else {
            ss << functionSignature;
        }
    }

    static void _print_error_with_stack_trace(std::string error) {
        using namespace backward;
        StackTrace st;
        st.load_here(20);
        TraceResolver tr; 
        tr.load_stacktrace(st);
        std::stringstream ss;
        
        ss << error;
        ss << YELLOW_TEXT << "Thread: " << std::hex << DebugHelper::get_current_thread_id() << std::dec << RESET_TEXT << std::endl;
        
        int startOffset = 0;
        for (size_t i = 0; i < st.size(); ++i) {
            ResolvedTrace trace = tr.resolve(st[i]);
            
            if((trace.object_function.find("backward::") != std::string::npos) || 
               (trace.object_function.find("DkrAssetsTool::DebugHelper::") != std::string::npos)) {
                // Skip the first few lines, since they include stack-trace calls.
                startOffset++;
                continue;
            }
            
            bool hasSourceInfo = trace.source.line > 0;
            
            // Don't bother printing functions that come from system libraries.
            bool isThirdParty = (hasSourceInfo) ? _str_starts_with(trace.source.filename, "/usr/include/") : false;
            
            if(isThirdParty) {
                continue;
            }
            
            bool printFuncSignature = (!trace.object_function.empty()) && (!isThirdParty); 
            
            if(!printFuncSignature && !hasSourceInfo) {
                continue; // Not useful, so skip.
            }
            
            ss << BLUE_TEXT << "#" << std::setw(2) << std::setfill('0') << (i - startOffset) << RESET_TEXT << ":";
            if(printFuncSignature) {
                _print_stack_func(ss, trace.object_function);
            } else if (!trace.inliners.empty()) {
                for(auto &inl : trace.inliners) {
                    ss << inl.function << std::endl;
                }
            }
            if(hasSourceInfo) {
                if(printFuncSignature) {
                    ss << std::endl;
                } else if (!isThirdParty) {
                    _print_stack_func(ss, trace.source.function);
                    ss << std::endl;
                }
                
                std::string sourceFilename = trace.source.filename;
                size_t startFolderIndex = sourceFilename.find("dkr_assets_tool_src");
                if(startFolderIndex != std::string::npos) {
                    // Don't need the entire directory, just local to the src folder.
                    sourceFilename = sourceFilename.substr(startFolderIndex + 19);
                }
                if(sourceFilename.length() > 100) {
                    // Unlike the function name, the end of the filename string is more important than the beginning.
                    sourceFilename = "..." + sourceFilename.substr(sourceFilename.length() - 97);
                }
                
                ss << " at " << FOREST_GREEN_TEXT << sourceFilename << RESET_TEXT << ":" << CYAN_TEXT << trace.source.line << RESET_TEXT;
            }
            ss << std::endl;
            
        }
        std::cout << ss.str() << std::endl;
    }
#endif
};
}
