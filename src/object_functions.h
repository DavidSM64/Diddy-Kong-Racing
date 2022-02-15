#ifndef _OBJECT_FUNCTIONS_H_
#define _OBJECT_FUNCTIONS_H_

#include "types.h"
#include "structs.h"
#include "level_object_entries.h"

#define WORLD_KEY_GRAB_CHECK_RADIUS 50
#define SOUND_WORLD_KEY_GRAB 54

typedef struct Object78_80033DD0 {
	s32 *unk0;
	s16 unk4;
	s16 unk6;
} Object78_80033DD0;

typedef struct unk80034B4C {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0x5E];
    s32 unk78;
} unk80034B4C;

typedef struct Object_3C_80034B74 {
    u8 pad0[0x8];
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
} Object_3C_80034B74;

typedef struct Object_64_80034B74 {
    u8 pad0[0x1FE];
    u8 unk1FE;
    u8 unk1FF;
} Object_64_80034B74;

typedef struct unk8003564C {
    s8 unk0;
    s8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} unk8003564C;

typedef struct Object_64_8003564C {
    u8 pad0[4];
    Object *unk4;
} Object_64_8003564C;

typedef struct unk80035E20 {
    u8 pad0[0x40];
    s32 unk40;
    u8 pad44[0x34];
    s32 unk78;
    s32 unk7C;
} unk80035E20;

typedef struct Object_64_80035E34 {
    u8 pad0[0x1D6];
    s8 unk1D6;
} Object_64_80035E34;

typedef struct Object_64_80035F6C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s16 *unk20;
    u8  *unk24;
} Object_64_80035F6C;

typedef struct Object_64_80035F6C_2 {
    u8 pad0[3];
    s8 unk3;
} Object_64_80035F6C_2;

typedef struct unk80037578 {
    u8 pad0[0x78];
    s32 unk78;
    s32 unk7C;
} unk80037578;

typedef struct unk80037624 {
    u8 pad0[6];
    s16 unk6;
} unk80037624;

/* Size: 12 bytes */
typedef struct LevelObjectEntry800376E0 {
    LevelObjectEntryCommon common;
    s8 unk8;
    s8 unk9;
    s8 unkA;
} LevelObjectEntry800376E0;

typedef struct Object_64_800376E0 {
    s16 segmentId;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Object_64_800376E0;

typedef struct unk80037D08_arg0_64 {
    u8 pad0[0x2A];
    s16 unk2A;
} unk80037D08_arg0_64;

typedef struct unk80037D08_arg0 {
    u8 pad0[0x64];
    unk80037D08_arg0_64 *unk64;
} unk80037D08_arg0;

// Not sure if Object_60 differs between objects yet.
typedef struct Object_60_800380F8 {
    s32 unk0;
    Object *unk4;
    s32 pad8;
    Object *unkC;
} Object_60_800380F8;

typedef struct Object_64_8003827C {
    u8 pad0[0x20];
    s32 unk20;
    s16 unk24;
    u8 pad28[0x12];
    s8 unk38;
} Object_64_8003827C;

typedef struct Object_64_80038710 {
    u8 pad0[0x30];
    s8 unk30;
    u8 pad31[0x13];
    s8 unk44;
} Object_64_80038710;

typedef struct Object_64_800387CC {
    u8 pad0[0x148];
    Object *unk148;
} Object_64_800387CC;

typedef struct Object_64_800388D4 {
    s16 unk0;
} Object_64_800388D4;

typedef struct unk80038B74 {
    u8 pad0[8];
    s8 unk8;
} unk80038B74;

typedef struct Object_3C_80038DC4 {
    u8 pad0[8];
    s8 unk8;
} Object_3C_80038DC4;

typedef struct Object_64_80038E3C {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s8 unk14;
} Object_64_80038E3C;

typedef struct unk80039160 {
    u8 pad0[0x78];
    s32 unk78;
} unk80039160;

typedef struct unk80039190 {
    u16 unk0;
    u8 pad2[0x76];
    s32 unk78;
    s32 unk7C;
} unk80039190;

typedef struct Object_64_8003AD34 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s8 unk14;
} Object_64_8003AD34;

typedef struct Object_64_8003C1E0 {
    f32 unk0;
    u8 pad4[4];
    s32 unk8;
    u8 padC[3];
    s8 unkF;
    u8 pad10[2];
    u8 unk12;
    u8 unk13;
} Object_64_8003C1E0;

typedef struct unk8003CF18 {
    u8 pad1A[0x78];
    f32 unk78;
} unk8003CF18;

typedef struct unk8003D038 {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0x5E];
    s32 unk78;
} unk8003D038;

typedef struct unk8003D3EC {
    u8 pad0[0x18];
    u16 unk18;
} unk8003D3EC;

typedef struct Object_64_8003DF08 {
    s16 unk0;
} Object_64_8003DF08;

typedef struct unk8003FC44 {
    s8 unk0;
    s8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s8 unk7;
} unk8003FC44;


typedef struct Object_64_8003FEF4 {
    u8 unk0;
    u8 pad1;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    union {
        struct {
            u8 unk8;
            u8 unk9;
            u8 unkA;
            u8 padB;
        } unk_struct;
        s32 unk8_word;
    } unk_union;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
} Object_64_8003FEF4;

typedef struct LevelObjectEntry8003FEF4 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u16 unkA;
    u8 unkC;
    u8 unkD;
    u16 unkE;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} LevelObjectEntry8003FEF4;

typedef struct LevelObjectEntry8004001C {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8004001C;

typedef struct Object_64_8004001C {
    u16 pad0;
    s16 unk2;
    u8 unk4;
    u8 unk5;
} Object_64_8004001C;

typedef struct Object_64_800400A4 {
    s16 unk0;
    s16 pad2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Object_64_800400A4;

typedef struct unk80040800 {
    u8 pad0[0x78];
    f32 unk78;
} unk80040800;

typedef struct unk80042014_arg0_64 {
    u16 unk0;
    u8 unk2;
    u8 unk3;
} unk80042014_arg0_64;

typedef struct unk80042014_arg0 {
    u8 pad0[0x64];
    unk80042014_arg0_64 *unk64;
} unk80042014_arg0;

typedef struct unk80042014_arg1 {
    u8 pad0[8];
    u16 unk8;
    u8 unkA;
    u8 unkB;
} unk80042014_arg1;

typedef struct unk8004210C {
    u8 pad0[0x3C];
    s32 unk3C;
    u8 pad40[0x24];
    s32 unk64;
} unk8004210C;

typedef struct Object_3C_80042178 {
    u8 pad0[8];
    u16 unk8;
    u16 unkA;
} Object_3C_80042178;

typedef struct Object_64_80042210 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[3];
    u8 unk19;
    u8 pad1A[6];
    f32 unk20;
    f32 unk24;
    u8 pad28[8];
    f32 unk30;
} Object_64_80042210;

typedef struct Object_64_80042998 {
    u8 pad0[0x70];
    u8 unk70;
    u8 pad71;
    u8 unk72;
    u8 pad73;
    f32 unk74;
} Object_64_80042998;

typedef struct unk80042A1C {
    u8 pad0[0x78];
    f32 unk78;
    s16 unk7C;
    s16 unk7E;
} unk80042A1C;

typedef struct unk80042CD0 {
    u8 pad0[0x18];
    s16 unk18;
} unk80042CD0;

// Unsure about the signed/unsigned with these arrays.
extern u16 D_800DC970[4];
extern u16 D_800DC978[4];
extern u16 D_800DC980[20];
extern u16 D_800DC9A8[20];
extern u16 D_800DC9D0[64];
extern s8 D_800DCA50[8];
extern u8 D_800DCA58[9];
extern s8 D_800DCA64[9];
extern s8 D_800DCA70[10];
extern s32 D_800DCA7C[3];
extern s32 D_800DCA88[3];
extern s8 D_800DCA94[8];
extern s8 D_800DCA9C[12];
extern u16 D_800DCAA8[64];
extern u16 D_800DCB28[20];
extern u32 osTvType;

f32 func_800707C4(s16); // No idea where it's located
f32 func_800707F8(s16); // No idea where it's located
s32 get_random_number_from_range(s32, s32); // Non Matching src/unknown_070110.c
s32 func_8007066C(s32, s32); // Non Matching src/unknown_070110.c

void obj_init_fireball_octoweapon(Object *obj, LevelObjectEntry_Fireball_Octoweapon *entry);
void obj_init_lasergun(Object *obj, LevelObjectEntry_Lasergun *entry);
void obj_init_laserbolt(Object *obj, LevelObjectEntry_Laserbolt *entry);
void obj_init_torch_mist(Object *obj, LevelObjectEntry_Torch_Mist *entry);
void obj_loop_torch_mist(Object *obj, s32 speed);
void obj_init_effectbox(Object *obj, LevelObjectEntry_EffectBox *entry);
void obj_init_trophycab(Object *obj, LevelObjectEntry_TrophyCab *entry);
void obj_init_collectegg(Object *obj, LevelObjectEntry_CollectEgg *entry);
void obj_init_eggcreator(Object *obj, LevelObjectEntry_EggCreator *entry);
void obj_loop_eggcreator(Object *obj, s32 speed);
void obj_init_lighthouse_rocketsignpost(Object *obj, LevelObjectEntry_Lighthouse_RocketSignpost *entry);
void obj_loop_rocketsignpost(Object *obj, s32 speed);
void obj_init_airzippers_waterzippers(Object *obj, LevelObjectEntry_AirZippers_WaterZippers *entry);
void obj_init_unknown58(Object *obj, LevelObjectEntry_Unknown58 *entry);
void obj_loop_unknown58(Object *obj, s32 speed);
void obj_init_characterflag(Object *obj, LevelObjectEntry_CharacterFlag *entry);
void obj_loop_characterflag(Object *obj, s32 speed);
void obj_init_stopwatchman(Object *obj, LevelObjectEntry_StopWatchMan *entry);
void func_80036BCC(u16 arg0, s32 arg1);
void obj_init_lavaspurt(Object *obj, LevelObjectEntry_LavaSpurt *entry);
void obj_init_posarrow(Object *obj, LevelObjectEntry_PosArrow *entry);
void obj_init_animator(Object *obj, LevelObjectEntry_Animator *entry, s32 arg2);
void obj_loop_animobject(Object *obj, s32 speed);
void obj_loop_dooropener(Object *obj, s32 speed);
void obj_init_overridepos(Object *obj, LevelObjectEntry_OverridePos *entry);
void func_80037D60(s32 arg0, s32 arg1);
void obj_init_wizpigship(Object *obj, LevelObjectEntry_WizpigShip *entry);
void obj_init_hittester(Object *obj, LevelObjectEntry_HitTester *entry);
void obj_loop_hittester(Object *obj, s32 speed);
void obj_init_dynamic_lighting_object(Object *obj, LevelObjectEntry_DynamicLightingObject *entry);
void obj_init_unknown96(Object *obj, LevelObjectEntry_Unknown96 *entry);
void obj_init_snowball(Object *obj, LevelObjectEntry_Snowball *entry);
void func_80038330(s32 arg0, s32 arg1);
void obj_loop_animcamera(Object *obj, s32 speed);
void func_800387C0(s32 arg0, s32 arg1);
void obj_loop_animcar(Object *obj, s32 speed);
void obj_init_infopoint(Object *obj, LevelObjectEntry_InfoPoint *entry);
void obj_loop_infopoint(Object *obj, s32 speed);
void obj_init_smoke(Object *obj, LevelObjectEntry_Smoke *entry);
void obj_loop_smoke(Object *obj, s32 speed);
void obj_init_unknown25(Object *obj, LevelObjectEntry_Unknown25 *entry);
void obj_loop_unknown25(Object *obj, s32 speed);
void obj_init_wardensmoke(Object *obj, LevelObjectEntry_WardenSmoke *entry);
void obj_loop_wardensmoke(Object *obj, s32 speed);
void obj_init_teleport(Object *obj, LevelObjectEntry_Teleport *entry);
void obj_loop_teleport(Object *obj, s32 speed);
void obj_init_exit(Object *obj, LevelObjectEntry_Exit *entry);
void obj_init_cameracontrol(Object *obj, LevelObjectEntry_CameraControl *entry);
void obj_loop_cameracontrol(Object *obj, s32 speed);
void obj_init_setuppoint(Object *obj, LevelObjectEntry_SetupPoint *entry);
void obj_loop_setuppoint(Object *obj, s32 speed);
void obj_init_dino_whale(Object *obj, LevelObjectEntry_Dino_Whale *entry);
void obj_loop_dino_whale(Object *obj, s32 speed);
void obj_init_parkwarden(Object *obj, LevelObjectEntry_Parkwarden *entry);
void func_80039320(s16 arg0);
void func_8003AC3C(u16 arg0, s32 arg1);
void obj_loop_gbparkwarden(Object *obj, s32 speed);
f32 func_8003ACAC(void);
void obj_init_checkpoint(Object *obj, LevelObjectEntry_Checkpoint *entry, s32 arg2);
void obj_loop_checkpoint(Object *obj, s32 speed);
void obj_init_modechange(Object *obj, LevelObjectEntry_ModeChange *entry);
void obj_init_bonus(Object *obj, LevelObjectEntry_Bonus *entry);
void obj_init_ttdoor(Object *obj, LevelObjectEntry_TTDoor *entry);
void obj_init_bridge_whaleramp(Object *obj, LevelObjectEntry_Bridge_WhaleRamp *entry);
void obj_init_rampswitch(Object *obj, LevelObjectEntry_RampSwitch *entry);
void obj_loop_rampswitch(Object *obj, s32 speed);
void obj_init_seamonster(Object *obj, LevelObjectEntry_SeaMonster *entry);
void obj_loop_seamonster(Object *obj, s32 speed);
void obj_init_fogchanger(Object *obj, LevelObjectEntry_FogChanger *entry);
void obj_init_skycontrol(Object *obj, LevelObjectEntry_SkyControl *entry);
void obj_loop_skycontrol(Object *obj, s32 speed);
void obj_init_ainode(Object *obj, LevelObjectEntry_AiNode *entry);
void obj_loop_ainode(Object *obj, s32 speed);
void obj_init_treasuresucker(Object *obj, LevelObjectEntry_TreasureSucker *entry);
void obj_init_flycoin(Object *obj, LevelObjectEntry_FlyCoin *entry);
void obj_init_coincreator(Object *obj, LevelObjectEntry_BananaCreator *entry);
void obj_init_coin(Object *obj, LevelObjectEntry_Banana *entry);
void obj_init_silvercoin_adv2(Object *obj, LevelObjectEntry_SilverCoinAdv2 *entry);
void obj_init_silvercoin(Object *obj, LevelObjectEntry_SilverCoin *entry);
void obj_init_worldkey(Object *obj, LevelObjectEntry_WorldKey *entry);
void obj_loop_worldkey(Object *worldKeyObj, s32 speed);
void obj_init_wballoonpop(Object *obj, LevelObjectEntry_WBalloonPop *entry);
void obj_loop_wballoonpop(Object *obj, s32 speed);
void obj_init_weapon(Object *obj, LevelObjectEntry_Weapon *entry);
void obj_loop_weapon(Object *obj, s32 speed);
void func_8003F0D0(void);
void func_8003F0DC(void);
void obj_init_audioline(Object *obj, LevelObjectEntry_AudioLine *entry);
void obj_init_audioreverb(Object *obj, LevelObjectEntry_AudioReverb *entry);
void obj_init_texscroll(Object *obj, LevelObjectEntry_TexScroll *entry, s32 arg2);
void obj_init_rgbalight(Object *obj, LevelObjectEntry_RgbaLight *entry, s32 arg2);
void obj_init_buoy_pirateship(Object *obj, LevelObjectEntry_Buoy_PirateShip *entry, s32 arg2);
void obj_loop_buoy_pirateship(Object *obj, s32 speed);
void obj_init_log(Object *obj, LevelObjectEntry_Log *entry, s32 arg2);
void obj_init_wavegenerator(Object *obj, LevelObjectEntry_WaveGenerator *entry, s32 arg2);
void obj_init_midichset(Object *obj, LevelObjectEntry_Midichset *entry);
void obj_init_bubbler(Object *obj, LevelObjectEntry_Bubbler *entry);
void obj_loop_bubbler(Object *obj, s32 speed);
void obj_init_boost(Object *obj, LevelObjectEntry_Boost *entry);
void obj_init_unknown94(Object *obj, LevelObjectEntry_Unknown94 *entry, s32 arg2);
void obj_loop_unknown94(Object *obj, s32 speed);
void obj_init_rangetrigger(Object *obj, LevelObjectEntry_RangeTrigger *entry);
void obj_loop_rangetrigger(Object *obj, s32 speed);
void obj_init_frog(Object *obj, LevelObjectEntry_Frog *entry);
void obj_loop_pigrocketeer(Object *obj, s32 speed);
void obj_init_levelname(Object *obj, LevelObjectEntry_LevelName *entry);
void obj_loop_wizghosts(Object *obj, s32 speed);

//Non Matching
void obj_loop_lavaspurt(Object *obj, s32 speed);
void obj_loop_animator(Object *obj, s32 speed);
void obj_loop_vehicleanim(Object *obj, s32 speed);
void obj_loop_snowball(Object *obj, s32 speed);
void obj_loop_goldenballoon(Object *obj, s32 speed);

#endif
