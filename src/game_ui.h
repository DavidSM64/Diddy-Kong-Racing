#ifndef _GAME_UI_H_
#define _GAME_UI_H_

#include "types.h"
#include "structs.h"
#include "libultra_internal.h"

enum CourseIndicatorArrows {
    INDICATOR_NONE,
    INDICATOR_LEFT,
    INDICATOR_LEFT_SHARP,
    INDICATOR_LEFT_UTURN,
    INDICATOR_RIGHT,
    INDICATOR_RIGHT_SHARP,
    INDICATOR_RIGHT_UTURN,
    INDICATOR_UP,
    INDICATOR_DOWN,
    INDICATOR_EXCLAMATION
};

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 textureID;
    s16 unk8;
    s16 unkA;
    f32 unkC;
} IndicatorArrow;

typedef struct unk80126CDC {
    u8 unk0[0x6];
    s16 unk6;
    u8 unk8[0x38];
    struct unk80126CDC *unk40;
    s16 unk44;
    s16 unk46;
    f32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s16 unk58;
    s8 unk5A;
    s8 unk5B;
    s8 unk5C;
    s8 unk5D;
    s8 unk5E;
    s8 unk5F;
    struct unk80126CDC *unk60; // Not sure if this is correct.
    s8 unk64[4];
    u8 unk68[0xD8];
    u8 unk140;
    u8 unk141;
    u8 unk142[0x18];
    s8 unk15A;
    s8 unk15B;
    u8 pad[0x10];
    f32 unk16C;
    f32 unk170;
    u8 unk174[0x8C];    
    struct unk80126CDC *unk200; // Not sure if this is correct.
    u8 unk204[0x14];
    s16 unk218; 
    s16 unk21A;
    u8 unk21C[0xD0];
    f32 unk2EC;
    f32 unk2F0;
    u8 unk2F4[0x1C];
    f32 unk310;
    u8 unk314[0x1C];
    f32 unk330;
    s32 unk334;
    s16 unk338;
    s16 unk33A;
    s32 unk33C;
    s16 unk340;
    s16 unk342;
    u8 unk344[0xC];
    f32 unk350;
    u8 unk354[0xCC];
    struct IndicatorArrow *courseIndicator;
    u8 unk424[0x1C];
    s16 unk440;
    s16 unk442;
    s16 unk444;
    u8 unk446[0xA];
    f32 unk450;
    s8 unk454[4];
    u8 unk458;
    u8 unk459;
    u8 unk45A[0x6];
    u8 unk460;
    s8 unk461;
    u8 unk462[0xA];
    f32 unk46C;
    u8 unk470[0xA];
    s8 unk47A[4];
    u8 unk47E;
    u8 unk47F;
    u8 unk480;
    s8 unk481;
    u8 unk482[0x8];
    f32 unk48C;
    u8 unk490[0xC];
    s8 unk49C;
    s8 unk49D;
    s8 unk49E[0x25];
    u16 unk4C4;
    u8 unk4C6[0x15A];
    struct unk80126CDC *unk620;
    u8 unk624[0x14];
    s16 unk638;
    s8 unk63A;
    s8 unk63B;
    u8 unk63C[0x3E];
    s8 unk67A;
    s8 unk67B[0xA4];
    s8 unk720;
} unk80126CDC;

typedef struct {
    u8 unk0[0x4B];
    s8 numLaps;
    s8 unk4C;
} unk80126D60;

typedef struct unk800E1E64 {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} unk800E1E64;

/* Size: 0x10 bytes */
typedef struct unk800E2770 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} unk800E2770;

extern unk80126CDC *D_80126CDC;
extern Gfx *gHUDCurrDisplayList;
extern Matrix *gHUDCurrMatrix;
extern TriangleList *gHUDCurrTriList;
extern u8 D_80126D37;

extern u8 gGfxTaskYieldData[0xA00];

u8 func_800A0190(void);
void func_800A0B74(void);
void func_800A0DC0(s32 arg0, Object *arg1, s32 updateRate);
void render_hud_challenge_eggs(s32 arg0, Object *arg1, s32 updateRate);
void render_hud_race_boss(s32 arg0, Object *arg1, s32 updateRate);
void func_800A263C(s32 arg0, Object *arg1, s32 updateRate);
void func_800A3870(void);
void play_time_trial_end_message(s16 *playerID);
void func_800A7484(u16 arg0, f32 arg1, s32 arg2);
void func_800A74EC(u16 arg0, s32 arg1);
void func_800A83B4(LevelModel *model);
s8 func_800A8458(void);
void func_800AB194(s32 arg0);
void func_800AB1AC(s32 arg0);
void func_800AB1C8(void);
void func_800AB1D4(u8 arg0);
void render_race_time(Object_64 *obj, s32 updateRate);
void render_wrong_way_text(Object_64 *obj, s32 updateRate);
void render_course_indicator_arrows(Object_64 *obj, s32 updateRate);
void render_hud_hubworld(Object *obj, s32 updateRate);
void render_hud(Gfx **dList, Matrix **mtx, TriangleList **tris, Object *arg3, s32 updateRate);

// Non Matching
void func_800A14F0(Object *, s32);
void func_800A3CE4(s32, s32);
void render_weapon_hud(Object *, s32);
void func_800A4F50(Object_64 *arg0, s32 arg1);
void func_800A4154(Object_64 *arg0, s32 arg1);
void func_800A4C44(Object_64 *arg0, s32 arg1);
void func_800A3884(Object *arg0, s32 arg1);
void func_800A47A0(Object_64 *arg0, s32 arg1);
void func_800A718C(Object_64 *);
void func_800AA600(Gfx **arg0, u32 *arg1, u32 *arg2, unk80126CDC *arg3);
void func_8009ECF0(s32 viewPortCount);
void func_800A003C(void);
void func_800A8474(Gfx **gfx, Mtx **mtx, VertexList **vtx, s32 updateRate);
void func_800A7FBC(s32, s32, s32 minutes, s32 seconds, s32 hundredths, s32); 
void func_800A1248(s32, Object*, s32);
void func_800A1C04(s32, Object*, s32);
void func_800A277C(s32, Object*, s32);
void func_800A497C(Object_64*, s32);
void func_800A6254(Object_64*, s32);
void func_800A6E30(Object_64*, s32);
void func_800A7A60(Object*, Gfx**);

#endif
