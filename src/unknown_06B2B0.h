#ifndef _UNKNOWN_06B2B0_H_
#define _UNKNOWN_06B2B0_H_

#include "types.h"

typedef struct unknown800DD408 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u16 unk4;
    u16 unk6;
} unknown800DD408;

enum NumberOfPlayers {
    ZERO_PLAYERS  = -1, // A.I. Only
    ONE_PLAYER    = 0,
    TWO_PLAYERS   = 1,
    THREE_PLAYERS = 2,
    FOUR_PLAYERS  = 3
};

#define NUMBER_OF_VEHICLE_TYPES 3
enum Vehicle {
    VEHICLE_CAR,
    VEHICLE_HOVERCRAFT,
    VEHICLE_PLANE
};

enum RaceType {
    RACE_TYPE_DEFAULT = 0,
    RACE_TYPE_HUB_AREA = 5,
    RACE_TYPE_CUTSCENE_1 = 6,
    RACE_TYPE_CUTSCENE_2 = 7,
    RACE_TYPE_BOSS = 8,
    RACE_TYPE_CHALLENGE = 0x40, // For masking
    RACE_TYPE_CHALLENGE_BATTLE = 0x40,
    RACE_TYPE_CHALLENGE_BANANAS = 0x41,
    RACE_TYPE_CHALLENGE_EGGS = 0x42,
};

extern s8 *D_800DD310;
extern s8  D_800DD314;
extern u8  D_800DD318;
extern s32 D_800DD31C;
extern s32 gFunc80068158Checksum;
extern s32 gFunc80068158Length;
extern s16 D_800DD328;
extern s16 D_800DD32C;

extern s8 D_800DD330;

// Unused?
extern char *D_800DD334[6];

// Unused?
extern char gBuildString[40];

extern s8  D_800DD374;
extern s32 D_800DD378;
extern s32 D_800DD37C;
extern s32 D_800DD380;
extern s32 D_800DD384;
extern s32 D_800DD388;
extern s8  D_800DD38C;
extern s8  D_800DD390;
extern s16 D_800DD394;
extern s8  D_800DD398;
extern s8  D_800DD39C;
extern s8  D_800DD3A0;
extern s32 D_800DD3A4;
extern s32 D_800DD3A8;
extern s32 D_800DD3AC;


extern s8  D_800DD3F0;
extern s16 D_800DD3F4[8];
extern unknown800DD408 D_800DD408;
extern s32 D_800DD40C;

// Unused?
extern char *D_800DD410[3];

// Not sure if this is an array or a struct.
extern s32 D_800DD41C[2];

extern s32 D_800DD424[2];

#endif