#include "regexHelper.h"
#include "helpers/debugHelper.h"

#define HAS_PCRE2 __has_include (<pcre2.h>)

#if HAS_PCRE2
#include "regex/regexPcre2.h"
#endif

// default
#include "regex/regexStd.h"

RegexHelper::RegexHelper() {
#if HAS_PCRE2
    // Set the default engine to PCRE2 if avaliable.
    _currentEngine = RegexEngine::PCRE2;
#else
    _currentEngine = RegexEngine::STL;
#endif
}

void RegexHelper::get_matches(const std::string &input, const std::string &regexInput, std::vector<RegexMatch> &out, int startOffset) {
    RegexEngine engine = RegexHelper::get()._currentEngine;
    switch(engine){
        case RegexEngine::STL:
            RegexHelperStl::get_matches(input, regexInput, out, startOffset);
            break;
#if HAS_PCRE2
        case RegexEngine::PCRE2:
            RegexHelperPcre2::get_matches(input, regexInput, out, startOffset);
            break;
#endif
    }
}

RegexMatch *RegexHelper::get_first_match(const std::string &input, const std::string &regexInput, int startOffset) {
    RegexEngine engine = RegexHelper::get()._currentEngine;
    switch(engine){
        case RegexEngine::STL:
            return RegexHelperStl::get_first_match(input, regexInput, startOffset);
#if HAS_PCRE2
        case RegexEngine::PCRE2:
            return RegexHelperPcre2::get_first_match(input, regexInput, startOffset);
#endif
    }
    return nullptr;
}

bool RegexHelper::set_engine(RegexEngine engine) {
    #if !HAS_PCRE2
        if(engine == RegexEngine::PCRE2) {
            DebugHelper::warn("(RegexHelper::set_engine) Your computer does not have PCRE2 installed!");
            return false;
        }
    #endif
    RegexHelper::get()._currentEngine = engine;
    return true;
}

std::string RegexHelper::get_current_engine_name() {
    RegexEngine engine = RegexHelper::get()._currentEngine;
    switch(engine){
        case RegexEngine::STL:
            return RegexHelperStl::get_name();
#if HAS_PCRE2
        case RegexEngine::PCRE2:
            return RegexHelperPcre2::get_name();
#endif
    }
    return "";
}
