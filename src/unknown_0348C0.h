#ifndef _UNKNOWN_0348C0_H_
#define _UNKNOWN_0348C0_H_

#include "types.h"
#include "structs.h"

#define WORLD_KEY_GRAB_CHECK_RADIUS 50
#define SOUND_WORLD_KEY_GRAB 54

typedef struct unk80034530 {
    u8 pad0[0x8];
    u8 unk8;
    u8 unk9;
    s8 unkA;
    s8 unkB;
    u8 unkC;
    u8 unkD;
} unk80034530;

typedef struct unk80034B4C {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0x5E];
    s32 unk78;
} unk80034B4C;

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

/* Size: 12 bytes */
typedef struct LevelObjectEntry8003572C {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8003572C;

/* Size: 12 bytes */
typedef struct LevelObjectEntry8003588C {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8003588C;

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

typedef struct unk80035EF8 {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
} unk80035EF8;

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

typedef struct LevelObjectEntry80038E3C {
    LevelObjectEntryCommon common;
    u8 pad8[8];
    u8 unk10;
    u8 unk11;
    u8 pad12[6];
    s8 unk18;
} LevelObjectEntry80038E3C;

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

typedef struct LevelObjectEntry8003AD34 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8003AD34;

typedef struct Object_64_8003AD34 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s8 unk14;
} Object_64_8003AD34;

typedef struct LevelObjectEntry8003C1E0 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 padD;
    s8 unkE;
} LevelObjectEntry8003C1E0;

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

typedef struct unk8003DE74 {
    u8 pad0[8];
    u8 unk8;
} unk8003DE74;

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

/* Size: 12 bytes */
typedef struct LevelObjectEntry800400A4 {
    LevelObjectEntryCommon common;
    s16 unk8;
    s8 unkA;
    s8 unkB;
} LevelObjectEntry800400A4;

typedef struct Object_64_800400A4 {
    s16 unk0;
    s16 pad2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Object_64_800400A4;

/* Size: 12 bytes */
typedef struct LevelObjectEntry8004049C {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8004049C;

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

typedef struct unk8004203C_arg1 {
    u8 pad0[0x8];
    u8 unk8;
    u8 unk9;
    u16 unkA;
} unk8004203C_arg1;

/* Size: 12 bytes */
typedef struct LevelObjectEntry80042210 {
    LevelObjectEntryCommon common;
    s16 unk8;
    u8 unkA;
} LevelObjectEntry80042210;

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

void func_80033F44(Object *arg0, s32 arg1);
void func_80034530(Object *arg0, unk80034530 *arg1);
void func_80034844(Object *arg0, s32 arg1);
void func_80034AF0(Object *arg0, u8 *arg1);
void func_80034B4C(unk80034B4C *arg0, s32 arg1);
void func_80034B68(s32 arg0, s32 arg1);
void func_80034E70(Object *arg0, u8 *arg1);
void func_8003522C(Object *arg0, s32 arg1);
void func_80035640(s32 arg0, s32 arg1);
void func_8003564C(Object *arg0, s32 arg1);
void func_8003572C(Object *arg0, LevelObjectEntry8003572C *arg1);
void func_800357D4(Object *obj, s32 arg1);
void func_8003588C(Object *arg0, LevelObjectEntry8003588C *arg1);
void func_80035E20(unk80035E20 *arg0, s32 arg1);
void func_80035E34(Object *obj, s32 arg1);
void func_80035EF8(Object *arg0, unk80035EF8 *arg1);
void func_80035F6C(Object *obj, s32 arg1);
void func_80036194(Object *arg0, s32 arg1);
void func_80036BCC(u16 arg0, s32 arg1);
void func_80037578(unk80037578 *arg0, u8 *arg1);
void func_80037624(unk80037624 *arg0, s32 arg1);
void func_800376E0(Object *arg0, LevelObjectEntry800376E0 *arg1, s32 arg2);
void func_80037CE8(s32 arg0, s32 arg1);
void func_80037D08(unk80037D08_arg0 *arg0, s32 arg1);
void func_80037D54(s32 arg0, s32 arg1);
void func_80037D60(s32 arg0, s32 arg1);
void func_80037D6C(s32 arg0, s32 arg1);
void func_8003818C(Object *arg0, s32 arg1);
void func_800381C0(s32 arg0, s32 arg1);
void func_800381E0(Object *arg0, s32 arg1);
void func_80038214(Object *arg0, s32 arg1);
void func_80038248(Object *arg0, s32 arg1);
void func_80038330(Object *obj, s32 arg1);
void func_80038710(Object *obj, s32 arg1);
void func_800387C0(Object *obj, s32 arg1);
void func_800387CC(Object *obj, s32 arg1);
void func_80038854(Object *arg0, u8 *arg1);
void func_800388D4(Object *arg0, s32 arg1);
void func_800389AC(s32 arg0, s32 arg1);
void func_800389B8(Object *obj, s32 arg1);
void func_80038A6C(s32 arg0, s32 arg1);
void func_80038A78(Object *arg0, s32 arg1);
void func_80038AC8(s32 arg0, s32 arg1);
void func_80038AD4(Object *arg0, s32 arg1);
void func_80038D58(Object *arg0, s32 arg1);
void func_80038DC4(Object *arg0, s32 arg1);
void func_80038E3C(Object *obj, LevelObjectEntry80038E3C *arg1);
void func_80039160(unk80039160 *arg0, s8 *arg1);
void func_80039184(s32 arg0, s32 arg1);
void func_80039190(unk80039190 *arg0, u8 *arg1);
void func_800391BC(s32 arg0, s32 arg1);
void func_800391C8(Object *arg0, s32 arg1);
void func_800391FC(Object *obj, s32 arg1);
void func_800392B8(Object *arg0, s32 arg1);
void func_80039320(s16 arg0);
void func_8003AC3C(u16 arg0, s32 arg1);
void func_8003ACA0(s32 arg0, s32 arg1);
f32 func_8003ACAC(void);
void func_8003ACBC(Object *arg0, u8 *arg1, s32 arg2);
void func_8003AD28(s32 arg0, s32 arg1);
void func_8003AD34(Object *obj, LevelObjectEntry8003AD34 *arg1);
void func_8003B058(Object *obj, LevelObjectEntry8003AD34 *arg1);
void func_8003C1E0(Object *obj, LevelObjectEntry8003C1E0 *arg1);
void func_8003C9EC(Object *arg0, u8 *arg1);
void func_8003CE64(Object *arg0, u8 *arg1);
void func_8003CEA0(Object *arg0, s32 arg1);
void func_8003CF00(s32 arg0, s32 arg1);
void func_8003CF0C(s32 arg0, s32 arg1);
void func_8003CF18(unk8003CF18 *arg0, u8 *arg1);
void func_8003CF58(Object *arg0, u8 *arg1);
void func_8003CF98(Object *arg0, s32 arg1);
void func_8003CFE0(s32 arg0, u8 *arg1);
void func_8003D02C(s32 arg0, s32 arg1);
void func_8003D038(unk8003D038 *arg0, s8 *arg1);
void func_8003D2AC(s32 arg0, s32 arg1);
void func_8003D3EC(unk8003D3EC *arg0, s32 arg1);
void func_8003D534(Object *arg0, s32 arg1);
void func_8003DBA0(Object *obj, s32 arg1);
void func_8003DC5C(Object *obj, s32 arg1);
void func_8003DE74(Object *obj, unk8003DE74 *arg1);
void obj_loop_world_key(Object *worldKeyObj, s32 speed);
void func_8003E5B0(s32 arg0, s32 arg1);
void func_8003E5BC(s32 arg0, s32 arg1);
void func_8003E5C8(Object *arg0, s32 arg1);
void func_8003E630(Object *arg0);
void func_8003F0D0(void);
void func_8003F0DC(void);
void func_8003FEF4(Object *arg0, LevelObjectEntry8003FEF4 *arg1);
void func_8004001C(Object *arg0, LevelObjectEntry8004001C *entry);
void func_800400A4(Object *obj, LevelObjectEntry800400A4 *arg1, s32 arg2);
void func_800403A8(Object *arg0, s32 arg1, s32 arg2);
void func_800403D8(Object *arg0, s32 arg1, s32 arg2);
void func_80040448(Object *arg0, s32 arg1);
void func_8004049C(Object *arg0, LevelObjectEntry8004049C *arg1, s32 arg2);
void func_800409A4(s32 arg0, s32 arg1, s32 arg2);
void func_80042014(unk80042014_arg0 *arg0, unk80042014_arg1 *arg1);
void func_8004203C(Object *arg0, unk8004203C_arg1 *arg1);
void func_80042090(Object *arg0, s32 arg1);
void func_8004210C(unk8004210C *arg0, s8 *arg1);
void func_80042150(s32 arg0, s32 arg1, s32 arg2);
void func_80042160(s32 arg0, s32 arg1);
void func_8004216C(s32 arg0, s32 arg1);
void func_80042178(Object *obj, s32 arg1);
void func_80042210(Object *obj, LevelObjectEntry80042210 *arg1);
void func_80042998(s32 arg0, s32 arg1);
void func_80042A1C(unk80042A1C *arg0, s8 *arg1);
void func_80042CD0(unk80042CD0 *arg0, s32 arg1);

//Non Matching
void func_80037594(Object *obj, s32 arg1);
void func_800377E4(Object *obj, s32 arg1);
void func_800380F8(Object *obj, s32 arg1);
void func_8003827C(Object *obj, s32 arg1);
void func_8003B4BC(s32 arg0);

#endif
