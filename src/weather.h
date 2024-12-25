#ifndef _UNKNOWN_0ABDF0_H_
#define _UNKNOWN_0ABDF0_H_

#include "types.h"
#include "textures_sprites.h"
#include "audio.h"

typedef enum WeatherType {
    WEATHER_SNOW,
    WEATHER_RAIN,
    WEATHER_UNK
} WeatherType;

/* Size: 0x2C Bytes */
typedef struct SnowGfxData {
    Vec3i *pos;
    s32 size;
    union {
        WeatherType type;
        TextureHeader *texture;
    };
    s32 offsetX;
    s32 offsetY;
    s32 offsetZ;
    s32 radiusX;
    s32 radiusY;
    s32 radiusZ;
    s16 vertOffsetW;
    s16 vertOffsetH;
    s16 vertWidth;
    s16 vertHeight;
} SnowGfxData;

/* Size: 0x10 Bytes */
typedef struct LensFlareData {
    s32 count; // Amount of pieces to draw
    ColourRGBA colour;
    f32 scale;
    f32 offset;
} LensFlareData;

/* Size: 0x1C Bytes */
typedef struct RainPosData {
  ObjectTransform trans;
  s16 animFrame;
  s16 opacity;
} RainPosData;

/* Size: 0x18 Bytes */
typedef struct RainGfxData {
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
    u8 opacity;
    // pad
} RainGfxData;

typedef struct {
    s16 near;
    s16 far;
    s32 current;
} SnowLimits;

typedef struct SnowPosData {
    s32 x_position;
    s32 y_position;
    s32 z_position;
    u8  unused_C;
    u8  unused_D;
    u8  unused_E;
    u8  index;
} SnowPosData;

typedef struct WeatherData {
    s32 intensity;
    s32 intensityStep;
    s32 intensityTarget;
    s32 velX;
    s32 velXStep;
    s32 velXTarget;
    s32 velY;
    s32 velYStep;
    s32 velYTarget;
    s32 velZ;
    s32 velZStep;
    s32 velZTarget;
    s32 opacity;
    s32 opacityStep;
    s32 opacityTarget;
    s32 shiftTime;
} WeatherData;

void weather_clip_planes(s16 arg0, s16 arg1);
void lensflare_remove(Object *obj);
void lensflare_override_add(Object *obj);
void free_rain_memory(void);
void rain_set(s32 arg0, s32 arg1, f32 arg2);
void rain_fog(void);
void rain_update(s32 updateRate);
void rain_sound(s32 updateRate);
void rain_render_splashes(s32 updateRate);
void rain_lightning(s32 updateRate);
void render_rain_overlay(RainGfxData*, s32);
void weather_update(Gfx **currDisplayList, MatrixS **currHudMat, Vertex **currHudVerts, TriangleList **currHudTris, s32 updateRate);
void snow_render(void);
void weather_free(void);
void weather_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void lensflare_override(ObjectSegment *cameraSegment);
void snow_update(s32 updateRate);
void snow_init(void);
void rain_init(s32 arg0, s32 arg1);
void weather_init(void);
void snow_vertices(void);
void lensflare_init(Object *);
void lensflare_render(Gfx**, MatrixS**, Vertex**, ObjectSegment*);
void weather_reset(s32 weatherType, s32 weatherEnable, s32 velX, s32 velY, s32 velZ, s32 intensity, s32 opacity);

#endif
