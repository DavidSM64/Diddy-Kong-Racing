/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80000450 */

#include "types.h"
#include "macros.h"

/* Size: 0x08 bytes */
typedef struct unk80115D48 {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
} unk80115D48;

/* Unknown size */
typedef struct unk800DC630 {
    u8 pad0[0x2C];
    s32 unk2C;
    u16 unk30;
} unk800DC630;

extern unk800DC630* D_800DC630;
extern unk800DC630* D_800DC634;

extern u8  D_800DC638;
extern u8  D_800DC63C;
extern u8  D_800DC640;
extern s32 D_800DC648;
extern s32 D_800DC64C;
extern f32 D_800DC650;
extern s32 D_800DC654;
extern s32 D_800DC658;
extern u8  D_800DC660;
extern u8  D_800DC670;

/* Unknown size */
typedef struct unk80115CF8 {
    u8 pad0[2];
    s16 unk2; 
} unk80115CF8;

extern unk80115CF8 *D_80115CF8;

extern u8  D_80115D04;
extern u8  D_80115D05;
extern s32 D_80115D08;

typedef struct unk80115D14_4_C {
    u8 pad0[0xE];
    u16 unkE;
} unk80115D14_4_C;

typedef struct unk80115D14_4 {
    u8 pad0[0xC];
    unk80115D14_4_C* unkC;
} unk80115D14_4;

typedef struct unk80115D14 {
    u8 pad0[4];
    unk80115D14_4* unk4;
} unk80115D14;

extern unk80115D14 *D_80115D14;

/* Size: 0x0A bytes */
typedef struct unk80115D18 {
    u8 pad0[6];
    u16 unk6;
    u8 pad8[2];
} unk80115D18;

extern unk80115D18* D_80115D18;

/* Size: 3 bytes */
typedef struct unk80115D1C {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} unk80115D1C;

extern unk80115D1C* D_80115D1C;
extern s32 D_80115D20;
extern s32 D_80115D24;
extern s32 D_80115D28;
extern s32 D_80115D2C;
extern s16 D_80115D30;
extern s32 D_80115D38;
extern s32 D_80115D3C;
extern u8  D_80115D40;
extern u8  D_80115D41;
extern unk80115D48 D_80115D48[8];
extern s8  D_80115F79;
extern s32 D_80115F7C;

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000450.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000890.s")

void func_80000968(s32 arg0) {
    switch(arg0) {
        case 1:
            func_80004A60(0, 0);
            func_80004A60(1, 0x7FFF);
            func_80004A60(2, 0);
            func_80004A60(4, 0);
            func_800C7850(D_800DC630, (s16) (D_800DC638 * D_800DC654 >> 2));
            func_800C7850(D_800DC634, 0);
            break;
        case 2:
            func_80004A60(0, 0);
            func_80004A60(1, 0x7FFF);
            func_80004A60(2, 0x7FFF);
            func_80004A60(4, 0x7FFF);
            break;
        case 3:
            func_80004A60(0, 0);
            func_80004A60(1, 0x7FFF);
            func_80004A60(2, 0);
            func_80004A60(4, 0);
            break;
        default:
            func_80004A60(0, 0x7FFF);
            func_80004A60(1, 0x7FFF);
            func_80004A60(2, 0x7FFF);
            func_80004A60(4, 0x7FFF);
            func_800C7850(D_800DC630, (s16) (D_800DC638 * D_800DC654));
            func_800C7850(D_800DC634, (s16) (sfxVolumeSliderPercentage() * D_800DC63C));
            break;
    }
    D_80115F79 = arg0;
}

void func_80000B18(void) {
    D_800DC648 = 1;
}

void func_80000B28(void) {
    D_800DC648 = 0;
}

void func_800022BC(u8, unk800DC630*);

void func_80000B34(u8 arg0) {
    if (D_800DC648 == 0 && D_800DC654 != 0) {
        D_80115D04 = arg0;
        D_800DC638 = 0x7F;
        if (D_800DC640 != 0) {
            func_800022BC(D_80115D04, D_800DC630);
        }
        D_80115D08 = func_800C7890(D_800DC630);
        D_800DC64C = func_800C78D0();
        D_80115D40 = 1;
        D_80115F7C = -1;
    }
}

void func_8000B010(unk800DC630* arg0, u8 arg1);

void func_80000BE0(u8 arg0) {
    if (D_800DC670 == 0) {
        func_8000B010(D_800DC630, arg0);
    }
}

void func_80000C1C(void) {
    D_800DC670 = 1;
}

void func_80000C2C(void) {
    D_800DC670 = 0;
}

void func_80000C38(u8 arg0) {
    func_8000B010(D_800DC634, arg0);
}

/* Unused? */
void func_80000C68(u8 arg0) {
    func_80063A90(D_800DC630, arg0);
}

void func_80000C98(s32 arg0) {
    D_80115D38 = 0;
    D_80115D3C = (arg0 * 0x3C) >> 8;
}

void func_80000CBC(void) {
    D_80115D38 = 0;
    D_80115D3C = 0;
    D_800DC650 = 1.0f;
    func_80001990(D_800DC638);
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000D00.s")

void func_80000FDC(u16 arg0, s32 arg1, f32 arg2) {
    if (D_800DC658 < 8) {
        D_80115D48[D_800DC658].unk0 = arg0;
        D_80115D48[D_800DC658].unk4 = arg1;
        D_80115D48[D_800DC658].unk2 = arg2 * 60.0f;
        D_800DC658++;
    }
}

void func_80001050(void) {
    D_800DC658 = 0;
}

u16 func_8000105C(void) {
    return D_800DC630->unk30;
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001074.s")

void func_80001114(u8 arg0) {
    if (arg0 < 0x10) {
        func_80063AF0(D_800DC630, arg0);
    }
}

s32 func_8000114C(s32 arg0) {
    return (D_800DC630->unk30 & (1 << arg0)) == 0;
}

void func_80001170(u8 arg0) {
    if (arg0 < 0x10) {
        func_80063B44(D_800DC630, arg0);
    }
}

s32 func_800C78E0(unk800DC630*, u8 arg1, u8 arg2);

void func_800011A8(u8 arg0, u8 arg1) {
    if (arg0 < 0x10) {
        func_800C78E0(D_800DC630, arg0, arg1);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800011E8.s")

s32 func_80063BA0(unk800DC630*, u8 arg1, u8 arg2);

void func_80001268(u8 arg0, u8 arg1) {
    if (arg0 < 0x10) {
        func_80063BA0(D_800DC630, arg0, arg1);
    }
}

s32 func_80063C00(unk800DC630*, u8 arg1);

s32 func_800012A8(u8 arg0) {
    if (arg0 >= 0x10) {
        return 0;
    }
    return func_80063C00(D_800DC630, arg0);
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800012E8.s")

s16 func_800015B8(void);

void func_800014BC(f32 arg0) {
    func_80001534((s32)((f32)(u32)(func_800015B8() & 0xFF) * arg0));
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001534.s")

s16 func_800015B8(void) {
    return D_80115D30;
}

u8 func_800015C8(void) {
    return (func_800C7A50(D_800DC630) == 1);
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800015F8.s")

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001784.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800017D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001844.s")

void func_80002570(unk800DC630* arg0);

void func_800018E0(void) {
    if (func_80001C08() == 0) {
        D_80115D05 = 0;
        func_80002570(D_800DC634);
    }
}

u8 func_80001918(void) {
    if (D_80115D04 != 0 && D_800DC630->unk2C == 1) {
        return D_80115D04;
    }
    return 0;
}

extern u8 D_800DC65C;

// Unused?
u8 func_80001954(void) {
    if (D_800DC65C != 0) {
        return D_800DC65C;
    }
    return D_80115D04;
}

u8 func_80001980(void) {
    return D_80115D05;
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001990.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001A3C.s")

u8 func_80001AEC(void) {
    return D_800DC638;
}

s32 musicVolumeSliderPercentage(void) {
    return D_800DC654;
}

void func_80001B0C(u8 arg0) {
    D_800DC63C = arg0;
    func_800C7850(D_800DC634, (s16) (sfxVolumeSliderPercentage() * D_800DC63C));
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001B58.s")

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001BC0.s")

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001C08.s")

u16 func_80001CB8(u16 arg0) {
    if (D_80115D20 < arg0) {
        return 0;
    }
    return D_80115D18[arg0].unk6;
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001D04.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001EA8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001F14.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001FB8.s")

u16 func_800020E8(void) {
    return D_80115D14->unk4->unkC->unkE;
}

u8 func_80002110(void) {
    return D_80115CF8->unk2;
}

void func_80002128(unk80115D18 **arg0, s32 *arg1, s32 *arg2) {
    if (arg0 != NULL) {
        *arg0 = D_80115D18;
    }
    if (arg1 != NULL) {
        *arg1 = D_80115D28;
    }
    if (arg2 != NULL) {
        *arg2 = D_80115D20;
    }
}

/* Unused? */
void func_8000216C(unk80115D1C **arg0, s32 *arg1, s32 *arg2) {
    if (arg0 != NULL) {
        *arg0 = D_80115D1C;
    }
    if (arg1 != NULL) {
        *arg1 = D_80115D2C;
    }
    if (arg2 != NULL) {
        *arg2 = D_80115D24;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800021B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80002224.s")

void func_800022BC(u8 arg0, unk800DC630* arg1) {
    func_80002570(arg1);
    if (arg0 < D_80115CF8->unk2) {
        if (arg1 == D_800DC630) {
            D_800DC65C = arg0;
            return;
        }
        D_800DC660 = arg0;
    }
}


GLOBAL_ASM("asm/non_matchings/unknown_001050/func_8000232C.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80002570.s")

void func_8006492C(u8 arg0);

void func_80002608(u8 arg0) {
    func_8006492C(arg0);
}

u8 func_80002630(void) {
    return D_80115D1C[D_80115D04].unk2;
}
