#pragma once

#include "types.hpp"

struct TitleScreenDemos {
    int8_t levelId;
    int8_t numberOfPlayers;
    int8_t cutsceneId;
};

struct CheatsTableEntry {
    be_int16_t codeOffset;
    be_int16_t descOffset;
};
