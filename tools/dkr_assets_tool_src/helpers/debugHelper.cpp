#include "debugHelper.h"

using namespace DkrAssetsTool;

void DebugHelper::set_verbose(bool isVerbose) {
    _verbose = isVerbose;
}

bool DebugHelper::is_verbose() {
    return _verbose;
}

void DebugHelper::set_asserts(bool useAsserts) {
    _assertsEnabled = useAsserts;
}
bool DebugHelper::using_asserts() {
    return _assertsEnabled;
}

DebugHelper::DebugTimer::DebugTimer() :
    m_beg(clock_::now()) {
}

void DebugHelper::DebugTimer::reset() {
    m_beg = clock_::now();
}

std::string DebugHelper::DebugTimer::elapsed() {
    std::chrono::time_point<clock_> m_end = clock_::now();
    
    const char *label = GREEN_TEXT "us" RESET_TEXT;
    
    double time = std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_beg).count();
    if(time > 1000.0) {
        time /= 1000.0;
        label = CYAN_TEXT "ms" RESET_TEXT;
        if(time > 1000.0) {
            time /= 1000.0;
            label = MAGENTA_TEXT "seconds" RESET_TEXT;
        }
    }
    return std::to_string(time).substr(0, std::to_string(time).find(".") + 3) + " " + label;
}
