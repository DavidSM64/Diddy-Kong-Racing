#ifndef _UNKNOWN_0ABDF0_H_
#define _UNKNOWN_0ABDF0_H_

#include "types.h"
#include "textures_sprites.h"
#include "audio.h"

typedef enum WeatherType {
    WEATHER_SNOW,
    WEATHER_RAIN
} WeatherType;

typedef struct unk800E2850_unk0 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} unk800E2850_unk0;

/* Size: 0x2C Bytes */
typedef struct unk800E2850 {
    unk800E2850_unk0 *unk0;
    s32 unk4;
    TextureHeader *unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
} unk800E2850;

/* Size: 0x10 Bytes */
typedef struct unk800E2980 {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    f32 unk8;
    f32 unkC;
} unk800E2980;

/* Size: 0x1C Bytes */
typedef struct unk800E2B4C {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
} unk800E2B4C;

/* Size: 0x18 Bytes */
typedef struct unk800E2C2C {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    TextureHeader *tex;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
} unk800E2C2C;

typedef struct {
    s16 unk0;
    s16 unk2;
    //s16 unk4;
    s32 unk4;
} unk80127BF8;

extern u32 osTvType;

void func_800AB308(s16 arg0, s16 arg1);
void func_800AC880(s32 arg0);
void func_800ACF60(Object *arg0);
void free_rain_memory(void);
void func_800AD2C4(s32 arg0, s32 arg1, f32 arg2);
void func_800AD40C(void);
void handle_weather_rain(s32 updateRate);
void handle_rain_sound(s32 updateRate);
void render_rain_splashes(s32 updateRate);
void handle_rain_lightning(s32 updateRate);
void render_rain_overlay(unk800E2C2C*, s32);
void process_weather(Gfx **currDisplayList, Mtx **currHudMat, VertexList **currHudVerts, TriangleList **currHudTris, s32 updateRate);

f32 cosine_s(s16);
f32 sine_s(s16);
s32 func_8007082C(s16);
s32 func_80070830(s16);
void free_weather_memory(void);
void func_800AB1F0(void);
s32 func_800AC0C8(s32, unk80127BF8 *);
void func_8006F6EC(Matrix *arg0, Matrix *arg1, Matrix *arg2);
void func_800AC21C(void);
void func_800AC5A4(void);

#endif
