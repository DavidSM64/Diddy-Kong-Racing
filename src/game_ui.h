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
    struct unk80126CDC *unk0;
    u8 unk4[0x2];
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
    struct unk80126CDC *unk60;
    s8 unk64[4];
    u8 unk68[0x30];
    s16 unk98;
    s16 unk9A;
    u8 unk9C[0x3C];
    s16 unkD8;
    s8 unkDA[0x6];
    struct unk80126CDC *unkE0;
    u8 unkE4[0x8];
    f32 unkEC;
    f32 unkF0;
    u8 unkF4[0x4];
    s16 unkF8;
    s8 unkFA;
    s8 unkFB;
    u8 unkFC[0x4];
    struct unk80126CDC *unk100;
    u8 unk104[0x8];
    f32 unk10C;
    f32 unk110;
    u8 unk114[0x4];
    s16 unk118;
    u8 unk11A[0x6];
    struct unk80126CDC *unk120;
    u8 unk124[0x8];
    f32 unk12C;
    f32 unk130;
    u8 unk134[0x4];
    s16 unk138;
    u8 unk13A[0x6];
    u8 unk140;
    u8 unk141;
    u8 unk142[0x18];
    s8 unk15A;
    s8 unk15B;
    u8 pad[0x10];
    f32 unk16C;
    f32 unk170;
    u8 unk174[0x18];
    f32 unk18C;
    u8 pad190[0xA];
    s8 unk19A[1];
    u8 pad19C[0x44];
    struct unk80126CDC *unk1E0;
    s16 unk1E4;
    s16 unk1E6;
    f32 unk1E8;
    f32 unk1EC;
    f32 unk1F0;
    u8 pad1F4[0xC];
    struct unk80126CDC *unk200;
    u8 unk204[0x14];
    s16 unk218; 
    s8 unk21A;
    s8 unk21B;
    u8 unk21C[0x24];
    struct unk80126CDC *unk240;
    u8 unk244[0x8];
    f32 unk24C;
    f32 unk250;
    u8 unk254[0x98];
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
    s32 unk354;
    s32 unk358;
    s32 unk35C;
    s32 unk360;
    u8 pad364[0x8];
    f32 unk36C;
    f32 unk370;
    u8 pad374[0xC];
    struct unk80126CDC *unk380;
    f32 unk384;
    f32 unk388;
    f32 unk38C;
    f32 unk390;
    u8 pad394[0x4];
    s16 unk398;
    s8 unk39A;
    s8 unk39B;
    u8 unk39C[0x10];
    f32 unk3AC;
    u8 unk3B0[0xC];
    s8 unk3BC;
    s8 unk3BD[0xF];
    f32 unk3CC;
    u8 unk3D0[0xA];
    s8 unk3DA;
    s8 unk3DB;
    s8 unk3DC;
    s8 unk3DD;
    s8 unk3DE;
    s8 unk3DF;
    u8 unk3E0[0xC];
    f32 unk3EC;
    u8 unk3F0[0xC];
    s8 unk3FC;
    u8 unk3FD;
    u8 unk3FE;
    u8 unk3FF;
    struct unk80126CDC *unk400;
    u8 unk404[0x8];
    f32 unk40C;
    f32 unk410;
    u8 unk414[0xC];
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
    s16 unk4C4;
    u8 unk4C6[0x15A];
    struct unk80126CDC *unk620;
    u8 unk624[0x14];
    s16 unk638;
    s8 unk63A;
    s8 unk63B;
    u8 unk63C[0x4];
    struct unk80126CDC *unk640;
    s16 unk644;
    s16 unk646;
    u8 unk648[0x4];
    f32 unk64C;
    f32 unk650;
    u8 unk654[0x18];
    f32 unk66C;
    f32 unk670;
    u8 unk674[0x6];
    s8 unk67A;
    s8 unk67B[0x85];
    struct unk80126CDC *unk700;
    s8 unk704[0x1C];
} unk80126CDC;

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
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s32 unk4;
    s32 unk8;
    s8 unkC;
    s8 unkD;
    s8 unkE;
    s8 unkF;
} unk800E2770;

typedef struct unk800A497C {
    u8 pad0[0xC];
    f32 unkC;
    u8 pad10[0xA];
    s8 unk1A;
    s8 unk1B;
    s8 unk1C;
    s8 unk1D;
} unk800A497C;

typedef struct ObjectTransform_800A8474 {
    ObjectTransform trans;
    s16 unk18;
} ObjectTransform_800A8474;

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
void render_weapon_hud(Object *obj, s32 updateRate);
void render_race_start(s32 arg0, s32 updateRate);
void render_racer_bananas(Object_64 *obj, s32 updateRate);
void render_race_finish_position(Object_64 *obj, s32 updateRate);
void render_speedometer(Object *obj, s32 updateRate);
void render_lap_count(Object_64 *obj, s32 updateRate);

// Non Matching
void func_800A14F0(Object *, s32);
void func_800A4C44(Object_64 *obj, s32 updateRate);
void func_800A47A0(Object_64 *obj, s32 updateRate);
void func_800A718C(Object_64 *obj);
void func_800AA600(Gfx **dList, Matrix **mtx, TriangleList **triList, unk80126CDC *arg3);
void func_8009ECF0(s32 viewPortCount);
void func_800A003C(void);
void func_800A8474(Gfx **dList, Matrix **mtx, VertexList **triList, s32 updateRate);
void func_800A7FBC(s32, s32, s32 minutes, s32 seconds, s32 hundredths, s32); 
void func_800A1248(s32, Object*, s32);
void func_800A1C04(s32, Object*, s32);
void func_800A277C(s32, Object*, s32);
void func_800A6254(Object_64* obj, s32 updateRate);
void func_800A6E30(Object_64* obj, s32 updateRate);
void func_800A7A60(Object*, Gfx**);
void func_800095E8(s32, f32, f32, f32, s32, s32, f32, s32*);
void func_800A0BD4(s32);
void func_800A19A4(Object_Racer*, s32 updateRate);
void func_800A1E48(s32, s32);
void func_800A45F0(Object_Racer*);
void func_800AA3EC(f32, f32, f32, f32, f32);

#endif
