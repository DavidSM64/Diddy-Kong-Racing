#pragma once

#include "types.hpp"

struct LevelHeader_AiLevels {
    int8_t baseAiLevel;
    int8_t silverCoinsAiLevel;
    int8_t completedAiLevel;
    int8_t tracksModeAiLevel;
    int8_t trophyRaceAiLevel;
};

struct LevelHeader_Weather {
    be_int16_t enable;
    be_int16_t type;
    uint8_t intensity;
    uint8_t opacity;
    be_int16_t velocity[3]; // X, Y, Z
};

struct LevelHeader_Fog {
    be_int16_t near;
    be_int16_t far;
    be_int16_t colour[3]; // R, G, B
};

struct LevelHeader {
    int8_t world;
    uint8_t unk1;
    int8_t unk2;
    int8_t unk3;
    int8_t unk4[4];
    be_float courseHeight;
    uint8_t unkC[10];
    uint8_t unk16[10];
    LevelHeader_AiLevels adv1AiLevels;
    LevelHeader_AiLevels adv2AiLevels;
    uint8_t unk2A;
    uint8_t unk2B[9];
    be_int16_t geometry;
    be_int16_t collectablesObjMap;
    be_int16_t skybox;
    
    LevelHeader_Fog fog;
    
    uint8_t unk44[5];
    
    // ???
    int8_t specialSky; // For Wizpig 2
    
    int8_t velocityCap;
    
    int8_t laps;
    int8_t raceType;
    int8_t vehicle;
    int8_t avaliableVehicles;
    
    uint8_t unk4F[3];
    
    uint8_t music;
    uint8_t unk53;
    be_uint16_t instruments;
    
    uint8_t waveSubdivisions;
    uint8_t unk57;
    uint8_t waveSineStep0;
    uint8_t waveSineBase0;
    be_int16_t waveSineHeight0;
    uint8_t waveSineStep1;
    uint8_t waveSineBase1;
    be_int16_t waveSineHeight1;
    be_int16_t waveSeedSize;
    be_int16_t wavePower;
    be_int16_t unk64;
    be_int16_t unk66;
    be_int16_t waveTexID;
    uint8_t waveUVScaleX;
    uint8_t waveUVScaleY;
    int8_t waveUVScrollX;
    int8_t waveUVScrollY;
    be_int16_t waveViewDist;
    
    uint8_t unk70;
    uint8_t unk71;
    uint8_t unk72;
    uint8_t unk73;
    be_int32_t miscAssets[7];
    
    // Weather related
    LevelHeader_Weather weather;
    
    int8_t cameraFOV;
    uint8_t bgColour[3]; // R, G, B
    
    be_int16_t unkA0;
    int8_t unkA2;
    int8_t unkA3;
    be_uint32_t specialSkyTexture; // Texture for the animated sky.
    be_int16_t unkA8;
    be_int16_t unkAA;
    be_int32_t pulseLightData;
    
    be_int16_t unkB0;
    uint8_t unkB2;
    uint8_t unkB3;
    uint8_t voidColour[3]; // R, G, B
    uint8_t useVoid;
    int8_t bossRaceID;
    uint8_t unkB9;
    be_int16_t objectMap2;
    uint8_t unkBC;
    int8_t unkBD;
    // Multiplayer gradient background
    uint8_t bgColourBottom[3]; // R, G, B
    uint8_t bgColourTop[3]; // R, G, B
    
    uint32_t unkC4;
};