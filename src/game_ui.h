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

enum HudElementNames {
    HUD_ELEMENT_UNK_00,
    HUD_ELEMENT_UNK_01,
    HUD_ELEMENT_UNK_02,
    HUD_ELEMENT_UNK_03,
    HUD_ELEMENT_UNK_04,
    HUD_ELEMENT_UNK_05,
    HUD_ELEMENT_UNK_06,
    HUD_ELEMENT_UNK_07,
    HUD_ELEMENT_UNK_08,
    HUD_ELEMENT_UNK_09,
    HUD_ELEMENT_UNK_0A,
    HUD_ELEMENT_UNK_0B,
    HUD_ELEMENT_UNK_0C,
    HUD_ELEMENT_UNK_0D,
    HUD_ELEMENT_UNK_0E,
    HUD_ELEMENT_UNK_0F,
    HUD_ELEMENT_UNK_10,
    HUD_ELEMENT_UNK_11,
    HUD_ELEMENT_UNK_12,
    HUD_ELEMENT_UNK_13,
    HUD_ELEMENT_UNK_14,
    HUD_ELEMENT_UNK_15,
    HUD_ELEMENT_UNK_16,
    HUD_ELEMENT_UNK_17,
    HUD_ELEMENT_UNK_18,
    HUD_ELEMENT_UNK_19,
    HUD_ELEMENT_UNK_1A,
    HUD_ELEMENT_UNK_1B,
    HUD_ELEMENT_UNK_1C,
    HUD_ELEMENT_UNK_1D,
    HUD_ELEMENT_UNK_1E,
    HUD_ELEMENT_UNK_1F,
    HUD_ELEMENT_UNK_20,
    HUD_ELEMENT_UNK_21,
    HUD_ELEMENT_UNK_22,
    HUD_ELEMENT_UNK_23,
    HUD_ELEMENT_UNK_24,
    HUD_ELEMENT_UNK_25,
    HUD_ELEMENT_UNK_26,
    HUD_ELEMENT_UNK_27
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

// Used in render_timer
typedef struct unk80126CDC_entry {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
} unk80126CDC_entry;

// Size: 0x760
typedef struct unk80126CDC {
    struct unk80126CDC *unk0;
    u8 unk4[0x2];
    s16 unk6;
    f32 unk8;
    f32 unkC;
    u8 pad10[0x8];
    s16 unk18;
    s8 unk1A;
    s8 unk1B;
    s8 unk1C;
    s8 unk1D;
    u8 pad1E[0x2];
    struct unk80126CDC *unk20;
    u8 pad24[0x14];
    s16 unk38;
    u8 pad3A[0x6];
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
    s8 unk64[0x4];
    u8 unk68[0x18];
    struct unk80126CDC *unk80;
    u8 unk84[0x14];
    s16 unk98;
    s16 unk9A;
    u8 unk9C[0x4];
    struct unk80126CDC *unkA0;
    u8 unkA4[0x1C];
    struct unk80126CDC *unkC0;
    u8 unkC4[0x14];
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
    struct unk80126CDC *unk140;
    u8 unk144[0x16];
    s8 unk15A;
    s8 unk15B;
    u8 pad[0x10];
    f32 unk16C;
    f32 unk170;
    u8 pad174[6];
    s8 unk17A;
    s8 unk17B;
    s8 unk17C;
    s8 unk17D;
    u8 pad17E[2];
    struct unk80126CDC *unk180;
    u8 unk184[0x8];
    f32 unk18C;
    u8 pad190[0xA];
    s8 unk19A[1];
    u8 pad19B;
    u8 pad19C[0x4];
    struct unk80126CDC *unk1A0;
    u8 pad1A4[0x1C];
    struct unk80126CDC *unk1C0;
    u8 pad1C4[0x8];
    f32 unk1CC;
    u8 pad1D0[0xA];
    s8 unk1DA;
    s8 unk1DB;
    s8 unk1DC;
    s8 unk1DD;
    u8 pad1DE[0x2];
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
    u8 pad21C[0x4];
    Object *unk220;
    u8 pad224[0x2];
    s16 unk226;
    u8 pad228[0x2];
    u8 pad22A[0x2];
    f32 unk22C;
    f32 unk230;
    f32 unk234;
    u8 pad238[0x8];
    struct unk80126CDC *unk240;
    u8 unk244[0x8];
    f32 unk24C;
    f32 unk250;
    u8 pad254[0xC];
    struct unk80126CDC *unk260;
    u8 pad264[0x2];
    s16 unk266;
    u8 pad268[0x18];
    struct unk80126CDC *unk280;
    u8 pad284[0x1C];
    struct unk80126CDC *unk2A0;
    u8 pad2A4[0x14];
    s16 unk2B8;
    u8 pad2BA[0x6];
    struct unk80126CDC *unk2C0;
    u8 pad2C4[0x14];
    s16 unk2D8;
    u8 pad2DA[0x12];
    f32 unk2EC;
    f32 unk2F0;
    u8 unk2F4[0x6];
    s8 unk2FA;
    s8 unk2FB;
    s8 unk2FC;
    s8 unk2FD;
    u8 pad2FE[2];
    s16 unk300;
    u8 unk302[0xC];
    u8 pad30E[0x2];
    f32 unk310;
    u8 unk314[0xC];
    s16 unk320;
    u8 pad322[0xE];
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
    struct unk80126CDC *unk360;
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
    s32 unk39C;
    struct unk80126CDC *unk3A0;
    u8 pad304[0x8];
    f32 unk3AC;
    u8 unk3B0[0xC];
    s8 unk3BC;
    s8 unk3BD[0x2];
    u8 pad3BF;
    struct unk80126CDC *unk3C0;
    s8 unk3C4[0x8];
    f32 unk3CC;
    u8 unk3D0[0xA];
    s8 unk3DA;
    s8 unk3DB;
    s8 unk3DC;
    s8 unk3DD;
    s8 unk3DE;
    s8 unk3DF;
    struct unk80126CDC *unk3E0;
    u8 unk3E4[0x8];
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
    s8 unk454[0x4];
    u8 unk458;
    u8 unk459;
    u8 unk45A[0x6];
    struct unk80126CDC *unk460;
    u8 unk464[0x6];
    u8 pad46A[0x2];
    f32 unk46C;
    u8 unk470[0xA];
    s8 unk47A[0x4];
    u8 unk47E;
    u8 unk47F;
    struct unk80126CDC *unk480;
    u8 unk484[0x4];
    u8 pad488[0x4];
    f32 unk48C;
    u8 unk490[0xC];
    s8 unk49C;
    s8 unk49D;
    s8 unk49E[0x21];
    u8 pad4BF;
    struct unk80126CDC *unk4C0;
    s16 unk4C4;
    u8 unk4C6[0x1A];
    struct unk80126CDC *unk4E0;
    u8 unk4E4[0x1C];
    struct unk80126CDC *unk500;
    u8 unk504[0x1C];
    struct unk80126CDC *unk520;
    u8 unk524[0x1C];
    struct unk80126CDC *unk540;
    u8 unk544[0x1C];
    struct unk80126CDC *unk560;
    u8 unk564[0x1C];
    struct unk80126CDC *unk580;
    u8 unk584[0x1C];
    struct unk80126CDC *unk5A0;
    u8 unk5A4[0x1C];
    struct unk80126CDC *unk5C0;
    u8 unk5C4[0xC];
    f32 unk5D0;
    u8 unk5D4[0x6];
    s8 unk5DA;
    s8 unk5DB;
    s8 unk5DC;
    u8 unk5DD[0x3];
    struct unk80126CDC *unk5E0;
    u8 unk5E4[8];
    f32 unk5EC;
    f32 unk5F0;
    u8 unk5F4[4];
    s16 unk5F8;
    u8 unk5FA;
    s8 unk5FB;
    s8 unk5FC;
    s8 unk5FD;
    u8 unk5FE[2];
    struct unk80126CDC *unk600;
    u8 unk604[8];
    f32 unk60C;
    f32 unk610;
    u8 unk614[4];
    s16 unk618;
    u8 unk61A[6];
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
    u8 unk654[0xC];
    struct unk80126CDC *unk660;
    u8 unk664[0x8];
    f32 unk66C;
    f32 unk670;
    u8 unk674[0x6];
    s8 unk67A;
    s8 unk67B[0x5];
    struct unk80126CDC *unk680;
    u8 pad684[8];
    f32 unk68C;
    f32 unk690;
    u8 pad694[0xC];
    struct unk80126CDC *unk6A0;
    u8 pad6A4[8];
    f32 unk6AC;
    f32 unk6B0;
    u8 pad6B4[0xC];
    struct unk80126CDC *unk6C0;
    s8 unk6C4[0x8];
    f32 unk6CC;
    f32 unk6D0;
    u8 unk6D4[4];
    s16 unk6D8;
    s8 unk6DA[0x6];
    struct unk80126CDC *unk6E0;
    s8 unk6E4[8];
    f32 unk6EC;
    f32 unk6F0;
    u8 unk6F4[4];
    s16 unk6F8;
    s8 unk6FA[0x6];
    struct unk80126CDC *unk700;
    s8 unk704[0x1C];
    struct unk80126CDC *unk720;
    s8 unk724[0x1C];
    struct unk800A497C *unk740;
    u8 pad744[0x1C];
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
    u16 soundID;
    u8 volume;
    s8 unk3;
    SoundMask *soundMask;
    s32 unk8;
    s8 playerIndex;
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

typedef struct HudElements {
    void *entry[40];
} HudElements;

extern u8 gGfxTaskYieldData[OS_YIELD_DATA_SIZE];

u8 func_800A0190(void);
void func_800A0B74(void);
void render_hud_race(s32 arg0, Object *obj, s32 updateRate);
void render_hud_challenge_eggs(s32 arg0, Object *obj, s32 updateRate);
void render_hud_race_boss(s32 arg0, Object *obj, s32 updateRate);
void render_hud_taj_race(s32 arg0, Object *obj, s32 updateRate);
void func_800A3870(void);
void play_time_trial_end_message(s16 *playerID);
void set_time_trial_start_voice(u16 soundID, f32 delay, s32 arg2);
void func_800A74EC(u16 soundID, s32 arg1);
void minimap_init(LevelModel *model);
s8 get_hud_setting(void);
void func_800AB194(s32 arg0);
void func_800AB1AC(s32 arg0);
void func_800AB1C8(void);
void set_hud_visibility(u8 setting);
void render_race_time(Object_Racer *racer, s32 updateRate);
void render_wrong_way_text(Object_Racer *obj, s32 updateRate);
void render_course_indicator_arrows(Object_Racer *racer, s32 updateRate);
void render_hud_hubworld(Object *obj, s32 updateRate);
void render_hud(Gfx **dList, MatrixS **mtx, Vertex **vertexList, Object *arg3, s32 updateRate);
void render_weapon_hud(Object *obj, s32 updateRate);
void render_race_start(s32 arg0, s32 updateRate);
void render_racer_bananas(Object_Racer *racer, s32 updateRate);
void render_race_finish_position(Object_Racer *racer, s32 updateRate);
void render_speedometer(Object *obj, s32 updateRate);
void render_lap_count(Object_Racer *racer, s32 updateRate);
void render_minimap_and_misc_hud(Gfx **dList, MatrixS **mtx, Vertex **vtx, s32 updateRate);
void init_hud(s32 viewportCount);
void render_hud_battle(s32 arg0, Object *obj, s32 updateRate);
void func_800A22F4(Object_Racer *racer, s32 updateRate);
void free_hud(void);
void set_stopwatch_face(u8, u8, u8, u8, u8);
void func_800A0BD4(s32 updateRate);
void render_silver_coin_counter(Object_Racer *racer, s32 updateRate);
void render_magnet_reticle(Object *racerObj);
void render_time_trial_finish(Object_Racer *racer, s32 updateRate);
void func_800A19A4(Object_Racer *racer, s32 updateRate);
void func_800A14F0(Object *racerObj, s32 updateRate);
void render_race_position(Object_Racer *racer, s32 updateRate);
void render_hud_banana_challenge(s32 arg0, Object *obj, s32 updateRate);
void render_balloon_count(Object_Racer *racer);
void render_treasure_hud(Object_Racer *racer);
void minimap_marker_pos(f32 x, f32 z, f32 angleSin, f32 angleCos, f32 modelAspectRatio);
void render_timer(s32 arg0, s32 arg1, s32 minutes, s32 seconds, s32 hundredths, s32 someBool);

// Non Matching
void func_800AA600(Gfx **dList, MatrixS **mtx, Vertex **vtxList, unk80126CDC **arg3);
void func_800A277C(s32, Object*, s32);
void func_800A6254(Object_Racer *racer, s32 updateRate);
void func_800A1E48(Object*, s32 updateRate);
void func_8009F034(void);

#endif
