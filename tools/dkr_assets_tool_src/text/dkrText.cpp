#include "dkrText.h"

#include <algorithm>

#include "helpers/stringHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/debugHelper.h"

using namespace DkrAssetsTool;

const std::vector<std::string> DKRJP_FONT_CHARACTERS = {
    "", "、", "$", "(", ")", "・", "%", "「", "」", "’", "”", "<", ">", "&", "〜", " ",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F",
    "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
    "W", "X", "Y", "Z", "!", "\"", "#", "'", "*", "+", ",", "-", ".", "/", ":", "=",
    "?", "@", "。", "゛", "゜", "ァ", "ィ", "ゥ", "ェ", "ォ", "ッ", "ャ", "ュ", "ョ", "ヲ", "ン",
    "ア", "イ", "ウ", "エ", "オ", "カ", "キ", "ク", "ケ", "コ", "サ", "シ", "ス", "セ", "ソ", "タ",
    "チ", "ツ", "テ", "ト", "ナ", "ニ", "ヌ", "ネ", "ノ", "ハ", "ヒ", "フ", "ヘ", "ホ", "マ", "ミ",
    "ム", "メ", "モ", "ヤ", "ユ", "ヨ", "ラ", "リ", "ル", "レ", "ロ", "ワ", "ガ", "ギ", "グ", "ゲ",
    "ゴ", "ザ", "ジ", "ズ", "ゼ", "ゾ", "ダ", "ヂ", "ヅ", "デ", "ド", "バ", "ビ", "ブ", "ベ", "ボ",
    "パ", "ピ", "プ", "ペ", "ポ", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "ぁ",
    "ぃ", "ぅ", "ぇ", "ぉ", "っ", "ゃ", "ゅ", "ょ", "を", "ん", "あ", "い", "う", "え", "お", "か",
    "き", "く", "け", "こ", "さ", "し", "す", "せ", "そ", "た", "ち", "つ", "て", "と", "な", "に",
    "ぬ", "ね", "の", "は", "ひ", "ふ", "へ", "ほ", "ま", "み", "む", "め", "も", "や", "ゆ", "よ",
    "ら", "り", "る", "れ", "ろ", "わ", "が", "ぎ", "ぐ", "げ", "ご", "ざ", "じ", "ず", "ぜ", "ぞ",
    "だ", "ぢ", "づ", "で", "ど", "ば", "び", "ぶ", "べ", "ぼ", "ぱ", "ぴ", "ぷ", "ぺ", "ぽ", "ヴ"
    // Note: In v77, there is actually a ton of kanji after the hiragana characters,
    // but they were removed in later versions most likely to save on ROM space.
};

static bool string_has_non_ascii(const std::string& str) {
    return std::any_of(str.begin(), str.end(), [](unsigned char c) {
        return c > 127;
    });
}

DKRText::DKRText(std::string text) : _text(text) {
}

DKRText::DKRText(std::vector<uint8_t> &textBytes, size_t startOffset) : DKRText(BytesView(textBytes, startOffset)) {
}

DKRText::DKRText(BytesView view) {
    size_t numBytes = 0;
    bool hasNonAscii = false;

    // Must first determine if there are any non-ascii characters. 
    // If so, then this text is assumed to be in the DKRJP text format.
    while (numBytes < view.size() && view[numBytes] != '\0') {
        uint8_t curChar = view[numBytes++];
        if (curChar & 0x80) {
            hasNonAscii = true;
            numBytes++; // Increment by 1 since DKRJP text characters use 2 bytes.
        }
    }
    
    _dkrjpSize = numBytes;

    if (!hasNonAscii) { 
        // The text is ascii, so this is easy.
        _text = std::string(view.data(), view.data() + numBytes);
        return;
    }

    // Gotta convert from DKRJP text bytes to UTF-8 characters.
    for (size_t i = 0; i < numBytes; i++) {
        uint8_t curChar = view[i];
        if (curChar & 0x80) {
            size_t tableOffset = (((size_t)curChar & 0x7F) << 8) | view[++i];
            DebugHelper::assert_(tableOffset < DKRJP_FONT_CHARACTERS.size(), "(DKRText::DKRText) jp font index 0x", std::hex, tableOffset, 
                " is out of range. It should be smaller than 0x", DKRJP_FONT_CHARACTERS.size(), ".", std::dec, " At byte index ", i - 1);
            _text += DKRJP_FONT_CHARACTERS[tableOffset];
        } else {
            _text += (char)curChar;
        }
    }
}

DKRText::~DKRText() {
}

std::string DKRText::get_text() {
    return _text;
}

// TODO: Is there a better way to handle this?
void DKRText::_get_next_utf8_char(std::string& outChar, size_t& textOffset) {
    uint8_t curByte = _text[textOffset];

    // Determine number of bytes for the character..
    size_t charLength = 1;
    if ((curByte & 0xE0) == 0xC0) {
        charLength = 2;
    } else if ((curByte & 0xF0) == 0xE0) {
        charLength = 3;
    } else if ((curByte & 0xF8) == 0xF0) {
        charLength = 4;
    }

    outChar = _text.substr(textOffset, charLength);

    textOffset += charLength;
}

std::vector<uint8_t> DKRText::get_bytes(bool forceDKRJP) {
    
    if(!forceDKRJP && !string_has_non_ascii(_text)) {
        // The text is ascii, so this is easy.
        return std::vector<uint8_t>(_text.begin(), _text.end());
    }

    // Gotta convert from UTF-8 to DKRJP text bytes
    std::vector<uint8_t> bytes;
    
    if(_text.empty()) {
        // Only occurs if forceDKRJP is true.
        bytes.push_back(0x80);
        bytes.push_back(0x00);
        return bytes;
    }

    std::string curChar;
    size_t offset = 0;
    while (offset < _text.length()) {
        // Gets the next utf-8 character from the string and puts it into curChar.
        // Offset will be updated to the next character.
        _get_next_utf8_char(curChar, offset);

        int indexOfJpChar = DataHelper::vector_index_of(DKRJP_FONT_CHARACTERS, curChar);

        if (indexOfJpChar == -1) {
            // Not found in the table.
            if (curChar.length() > 1 || curChar[0] > 127) {
                // Not a valid DKRJP/ASCII character. Skip it!
                continue;
            }
            
            // This is an ASCII character. DKRJP uses the control characters of ASCII, but ignores regular characters.
            bytes.push_back(curChar[0]);
            continue;
        }

        bytes.push_back(0x80 | ((indexOfJpChar >> 8) & 0xFF));
        bytes.push_back(indexOfJpChar & 0xFF);
    }

    return bytes;
}

size_t DKRText::bytes_size(bool forceDKRJP) {
    if(!_dkrjpSize.has_value()) {
        // Not the most efficient way to do this, but it should work.
        _dkrjpSize = get_bytes(forceDKRJP).size();
    }
    return _dkrjpSize.value();
}

size_t DKRText::length() {
    return _text.length();
}
        
const std::vector<std::string> &DKRText::get_dkrjp_characters() {
    return DKRJP_FONT_CHARACTERS;
}

