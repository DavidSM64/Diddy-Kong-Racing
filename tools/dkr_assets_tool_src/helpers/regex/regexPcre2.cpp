/**
 * PCRE2 version of the regex helper
 */

#include "regexPcre2.h"

#include "helpers/debugHelper.h"

class PCRE2Cache {
public:
    static PCRE2Cache& get() {
        static PCRE2Cache instance;
        return instance;
    }
    
    pcre2_code *compile_regex(const std::string &regex) {
        if(_cache.find(regex) == _cache.end()) {
            pcre2_code *re;
            int errorcode;
            PCRE2_SIZE erroroffset;
            re = pcre2_compile(
                (PCRE2_SPTR)regex.c_str(),
                (PCRE2_SIZE)regex.size(),
                PCRE2_MULTILINE,
                &errorcode,
                &erroroffset,
                NULL
            );
            _cache[regex] = re;
        }
        return _cache[regex];
    }
    
private:
    std::unordered_map<std::string, pcre2_code*> _cache;
    
};

void RegexHelperPcre2::get_matches(const std::string &input, const std::string &regexInput, std::vector<RegexMatch> &out, int startOffset) {
    pcre2_code *re = PCRE2Cache::get().compile_regex(regexInput);
    
    pcre2_match_context *mcontext = pcre2_match_context_create(NULL);
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
    PCRE2_SPTR subjectSPTR = (PCRE2_SPTR)input.c_str();
    PCRE2_SIZE subjectLength = (PCRE2_SIZE)input.size();
    PCRE2_SIZE startPos = startOffset;
    
    while(startPos < subjectLength) {
        int numberOfGroups = pcre2_match(
            re,
            subjectSPTR,
            subjectLength,
            startPos,
            0,
            match_data,
            mcontext
        );
        
        if(numberOfGroups < 2) {
            break;
        }
        
        RegexMatch newMatch;
        
        for(int i = 0; i < numberOfGroups; i++) {
            int start = (int)pcre2_get_ovector_pointer(match_data)[2 * i];
            int end = (int)pcre2_get_ovector_pointer(match_data)[2 * i + 1];
            if(start < 0) {
                newMatch._add_to_group("", -1);
                continue;
            }
            std::string groupMatch;
            size_t groupLen = end - start;
            if((size_t)start < input.length() && groupLen > 0) {
                groupMatch = input.substr(start, groupLen);
            }
            int position = start - startPos;
            newMatch._add_to_group(groupMatch, position);
        }
        
        out.push_back(newMatch);
        
        // Set the next start position to the end of the matched string.
        startPos = pcre2_get_ovector_pointer(match_data)[1]; 
    }
    
    pcre2_match_data_free(match_data);
    pcre2_match_context_free(mcontext);
}

RegexMatch *RegexHelperPcre2::get_first_match(const std::string &input, const std::string &regexInput, int startOffset) {
    pcre2_code *re = PCRE2Cache::get().compile_regex(regexInput);
    
    pcre2_match_context *mcontext = pcre2_match_context_create(NULL);
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
    PCRE2_SPTR subjectSPTR = (PCRE2_SPTR)input.c_str();
    PCRE2_SIZE subjectLength = (PCRE2_SIZE)input.size();
    
    int numberOfGroups = pcre2_match(
        re,
        subjectSPTR,
        subjectLength,
        startOffset,
        0,
        match_data,
        mcontext
    );
    
    if(numberOfGroups < 2) {
        return nullptr;
    }
    
    RegexMatch *newMatch = new RegexMatch();
    
    for(int i = 0; i < numberOfGroups; i++) {
        int start = (int)pcre2_get_ovector_pointer(match_data)[2 * i];
        int end = (int)pcre2_get_ovector_pointer(match_data)[2 * i + 1];
        if(start < 0) {
            newMatch->_add_to_group("", -1);
            continue;
        }
        std::string groupMatch;
        size_t groupLen = end - start;
        if((size_t)start < input.length() && groupLen > 0) {
            groupMatch = input.substr(start, groupLen);
        }
        int position = start - startOffset;
        newMatch->_add_to_group(groupMatch, position);
    }
    
    pcre2_match_data_free(match_data);
    pcre2_match_context_free(mcontext);
    
    return newMatch;
}

std::string RegexHelperPcre2::get_name() {
    return "PCRE2";
};

/*
void RegexHelper::get_matches(const std::string &input, const std::string &regexInput, std::vector<RegexMatch> &out, int startOffset) {
    pcre2_code *re = PCRE2Cache::get().compile_regex(regexInput);
    
    pcre2_match_context *mcontext = pcre2_match_context_create(NULL);
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
    PCRE2_SPTR subjectSPTR = (PCRE2_SPTR)input.c_str();
    PCRE2_SIZE subjectLength = (PCRE2_SIZE)input.size();
    PCRE2_SIZE startPos = startOffset;
    
    while(startPos < subjectLength) {
        size_t numberOfGroups = pcre2_match(
            re,
            subjectSPTR,
            subjectLength,
            startPos,
            0,
            match_data,
            mcontext
        );
        
        if(numberOfGroups < 2) {
            break;
        }
        
        RegexMatch newMatch;
        
        for(size_t i = 0; i < numberOfGroups; i++) {
            int start = (int)pcre2_get_ovector_pointer(match_data)[2 * i];
            int end = (int)pcre2_get_ovector_pointer(match_data)[2 * i + 1];
            if(start < 0) {
                newMatch._add_to_group("", 0);
                continue;
            }
            //DebugHelper::info("start = ", start, ", end = ", end);
            std::string groupMatch;
            if((size_t)start < input.length() && end - start > 0) {
                groupMatch = input.substr(start, end - start);
            }
            int position = std::max(0, start);
            newMatch._add_to_group(groupMatch, position);
            //DebugHelper::info(groupMatch);
        }
        
        out.push_back(newMatch);
        
        // Set the next start position to the end of the matched string.
        startPos = pcre2_get_ovector_pointer(match_data)[1] + 1; 
    }
    
    pcre2_match_data_free(match_data);
    pcre2_match_context_free(mcontext);
    
    //DebugHelper::info("matchResult: ", matchResult);
}

RegexMatch *RegexHelper::get_first_match(const std::string &input, const std::string &regexInput, int startOffset) {
    pcre2_code *re = PCRE2Cache::get().compile_regex(regexInput);
    
    pcre2_match_context *mcontext = pcre2_match_context_create(NULL);
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
    PCRE2_SPTR subjectSPTR = (PCRE2_SPTR)input.c_str();
    PCRE2_SIZE subjectLength = (PCRE2_SIZE)input.size();
    
    size_t numberOfGroups = pcre2_match(
        re,
        subjectSPTR,
        subjectLength,
        startOffset,
        0,
        match_data,
        mcontext
    );
    
    if(numberOfGroups < 2) {
        return nullptr;
    }
    
    RegexMatch *newMatch = new RegexMatch();
    
    for(size_t i = 0; i < numberOfGroups; i++) {
        int start = (int)pcre2_get_ovector_pointer(match_data)[2 * i];
        int end = (int)pcre2_get_ovector_pointer(match_data)[2 * i + 1];
        if(start < 0) {
            newMatch->_add_to_group("", 0);
            continue;
        }
        //DebugHelper::info("start = ", start, ", end = ", end);
        
        std::string groupMatch;
        if((size_t)start < input.length() && end - start > 0) {
            groupMatch = input.substr(start, end - start);
        }
        int position = std::max(0, start - startOffset);
        newMatch->_add_to_group(groupMatch, position);
        //DebugHelper::info(groupMatch);
    }
    
    pcre2_match_data_free(match_data);
    pcre2_match_context_free(mcontext);
    
    //DebugHelper::error("(RegexHelper::get_first_match) PCRE2 version not implemeted!");
    return newMatch;
}
*/