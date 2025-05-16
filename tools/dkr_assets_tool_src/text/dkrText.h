#pragma once

#include <string>
#include <vector>
#include <optional>
#include "libs/bytes_view.hpp"

namespace DkrAssetsTool {
class DKRText {
    public:
        DKRText(std::string text);
        
        // Can't use `const std::vector<uint8_t> &` here, since BytesView requires it be non-const.
        DKRText(std::vector<uint8_t>& textBytes, size_t startOffset=0); 
        DKRText(BytesView textView);
        ~DKRText();

        std::string get_text();
        std::vector<uint8_t> get_bytes(bool forceDKRJP=false); // Will convert to the native DKRJP text format if needed.
        
        size_t size(); // Number of bytes in the utf-8 string. (same as length() for ascii text)
        size_t bytes_size(bool forceDKRJP=false); // Number of bytes (ASCII or DKRJP) needed for this text.
        size_t length(); // Number of characters
        
        static const std::vector<std::string> &get_dkrjp_characters();
        
    private:
        std::string _text;
        void _get_next_utf8_char(std::string &outChar, size_t &textOffset);
        std::optional<size_t> _dkrjpSize = std::nullopt;
};
}
