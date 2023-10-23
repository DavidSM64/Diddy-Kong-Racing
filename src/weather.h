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
    s16 unk0; //tri - u?
    s16 unk2; //tri - v?
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    TextureHeader *tex;
    u8 primitiveRed;
    u8 primitiveGreen;
    u8 primitiveBlue;
    u8 environmentRed;
    u8 environmentGreen;
    u8 environmentBlue;
    u8 unk16;
    u8 unk17;
} unk800E2C2C;

typedef struct {
    s16 unk0;
    s16 unk2;
    //s16 unk4;
    s32 unk4;
} unk80127BF8;

typedef struct unk800E28D4 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8  padC[3];
    u8  unkF;
} unk800E28D4;

extern u32 osTvType;

void set_weather_limits(s16 arg0, s16 arg1);
void func_800AC880(Object *obj);
void cameraAddOverrideObject(Object *arg0);
void free_rain_memory(void);
void func_800AD2C4(s32 arg0, s32 arg1, f32 arg2);
void func_800AD40C(void);
void handle_weather_rain(s32 updateRate);
void handle_rain_sound(s32 updateRate);
void render_rain_splashes(s32 updateRate);
void handle_rain_lightning(s32 updateRate);
void render_rain_overlay(unk800E2C2C*, s32);
void process_weather(Gfx **currDisplayList, MatrixS **currHudMat, Vertex **currHudVerts, TriangleList **currHudTris, s32 updateRate);
void render_falling_snow(void);
void free_weather_memory(void);
void changeWeather(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_800AD030(ObjectSegment *cameraSegment);
void func_800AC0C8(s32 updateRate);

s32 coss(s16);
s32 sins(s16);
void init_weather(void);
void f32_matrix_dot(Matrix *arg0, Matrix *arg1, Matrix *arg2);
void func_800AC21C(void);
void func_800AC8A8(Object *);
void func_800ACA20(Gfx**, MatrixS**, Vertex**, ObjectSegment*);
void func_800AB4A8(s32 weatherType, s32 weatherEnable, s32 velX, s32 velY, s32 velZ, s32 intensity, s32 opacity);

#endif
