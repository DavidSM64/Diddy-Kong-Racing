/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8009ECF0 */

#include "types.h"
#include "macros.h"
#include "structs.h"

typedef struct {
    u8 unk0[0x4C4];
    u16 unk4C4;
} unk80126CDC;

typedef struct {
    u8 unk0[0x4C];
    s8 unk4C;
} unk80126D60;

typedef struct {
    s16 unk0;
    s16 unk2;
} unk80127BF8;

extern u32 osTvType;
extern s32 D_800E2A80;
extern s32 D_800E2A84;
extern s32 D_800E2C38;
extern s32 D_800E2C50;
extern s32 D_800E2C5C;
extern s32 D_800E2C60;
extern s32 D_800E2C64;
extern s32 D_800E2C68;
extern s32 D_800E2C6C;
extern s32 D_800E2C70;
extern s32 D_800E2C74;
extern s32 D_800E2C78;
extern s32 D_800E2C88;
extern s32 D_800E2C8C;
extern s32 D_800E2C94;
extern u8 D_80126CD0;
extern u8 D_80126CD1;
extern u8 D_80126CD2;
extern u8 D_80126CD3;
extern u8 D_80126CD4;
extern unk80126CDC* D_80126CDC;
extern u8 D_80126D34;
extern s32 D_80126D40;
extern unk80126D60* D_80126D60;
extern s32 D_80126D74;
extern s32 D_80126D78;
extern u16 D_80126D7C;
extern u8 D_80127188;
extern u8 D_8012718B;
extern unk80127BF8 D_80127BF8;

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_8009ECF0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_8009F034.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A003C.s")

u8 func_800A0190(void) {
    return D_80126D34;
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A01A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A0B74.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A0BD4.s")

typedef struct {
    u8 unk0[0x64];
    s32* unk64;
} unk800A0DC0;

typedef struct {
    u8 unk0[0x1D8];
    s8 unk1D8;
} unk800A0DC0_2;

void func_800A0DC0(s32 arg0, unk800A0DC0* arg1, s32 arg2) {
    unk800A0DC0_2* temp = arg1->unk64;

    func_80068508(1);
    func_800A0EB4(temp, arg2);
    func_800A5A64(temp, arg2);
    func_800A3CE4(arg0, arg2);

    if (D_80126D60->unk4C == 0) {
        func_800A4F50(temp, arg2);
    }

    func_800A4154(temp, arg2);
    func_800A7B68(temp, arg2);
    func_800A4C44(temp, arg2);
    func_800A3884(arg1, arg2);

    if (D_80127188 != 0 && temp->unk1D8 == 0) {
        func_800A47A0(temp, arg2);
    }

    func_800A7520(arg1, arg2);
    func_80068508(0);
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A0EB4.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A1248.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A1428.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A14F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A19A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A1C04.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A1E48.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A22F4.s")

void func_800A258C(s32 arg0, unk800A0DC0* arg1, s32 arg2) {
    LevelHeader* level;
    unk800A0DC0_2* temp = arg1->unk64;

    func_80068508(1);
    func_800A5A64(temp, arg2);
    func_800A3CE4(arg0, arg2);
    func_800A7B68(temp, arg2);
    func_800A7520(arg1, arg2);

    level = func_8006BDB0();
    if (level->laps > 1) {
        func_800A4F50(temp, arg2);
    }

    func_800A3884(arg1, arg2);
    func_800A4C44(temp, arg2);
    func_80068508(0);
}

void func_800A263C(s32 arg0, unk800A0DC0* arg1, s32 arg2) {
    unk800A0DC0_2* temp = arg1->unk64;

    func_80068508(1);
    func_800A5A64(temp, arg2);
    func_800A4F50(temp, arg2);
    func_800A4C44(temp, arg2);
    func_800A7B68(temp, arg2);
    func_800A3CE4(arg0, arg2);
    func_800A3884(arg1, arg2);
    func_80068508(0);
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A26C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A277C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A36CC.s")

void func_800A3870(void) {
    D_80126CDC->unk4C4 = 0x6490;
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A3884.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A3CE4.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A4154.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A45F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A47A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A497C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A4C44.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A4F50.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A5A64.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A5F18.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A6254.s")

void func_800A6DB4(s16* arg0) {
    Settings* settings = get_settings();

    if (arg0 != NULL) {
        if (settings->racers[*arg0].best_times & 0x80) {
            func_80001D04(0x145, &D_80126D40);
        } else {
            func_80001D04(0x102, &D_80126D40);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A6E30.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A718C.s")

void func_800A7484(u16 arg0, f32 arg1, s32 arg2) {
    if (D_80126D74 == 0) {
        D_80126D7C = arg0;
        D_80126D74 = arg1 * 60.0f;
        D_80126D78 = arg2;
    }
}

void func_800A74EC(u16 arg0, s32 arg1) {
    if (arg0 == D_80126D7C && D_80126D78 == arg1) {
        D_80126D74 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A7520.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A7A60.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A7B68.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A7FBC.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A83B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A8458.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A8474.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AA3EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AA600.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AAFD0.s")

void func_800AB194(s32 arg0) {
    D_80126CD1 = 1;
    D_80126CD3 = arg0;
}

void func_800AB1AC(s32 arg0) {
    D_80126CD0 = D_8012718B;
    D_80126CD3 = arg0;
}

/* Unused? */
void func_800AB1C8(void) {
    D_80126CD4 = 0;
}

/* Last function of file */
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AB1D4.s")
//void func_800AB1D4(s32 arg0) {
//    D_80126CD2 = arg0 - 1;
//}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AB1F0.s")

void func_800AB308(s16 arg0, s16 arg1) {
    if (D_80127BF8.unk2 < D_80127BF8.unk0) {
        D_80127BF8.unk0 = arg0;
        D_80127BF8.unk2 = arg1;
    } else {
        D_80127BF8.unk0 = arg1;
        D_80127BF8.unk2 = arg0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AB35C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AB4A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ABB34.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ABC5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ABE68.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AC0C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AC21C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AC5A4.s")

void func_800AC880(s32 arg0) {
    if (arg0 == D_800E2A80) {
        D_800E2A80 = 0;
        D_800E2A84 = 1;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AC8A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ACA20.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ACF60.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ACF98.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD030.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD144.s")

void func_800AD220(void) {
    if (D_800E2C38 != 0) {
        func_8007B2BC(D_800E2C38);
        D_800E2C88 = 0;
    }

    if (D_800E2C50 != 0) {
        func_8007B2BC(D_800E2C50);
        D_800E2C88 = 0;
    }

    if (D_800E2C8C != 0) {
        func_8007CCB0(D_800E2C8C);
        D_800E2C8C = 0;
    }

    if (D_800E2C94 != 0) {
        func_800096F8(D_800E2C94);
        D_800E2C94 = 0;
    }

    D_800E2C5C = 0;
}

void func_800AD2C4(s32 arg0, s32 arg1, f32 arg2) {
    D_800E2C78 = osTvType == 0 ? 50.0 * arg2 : 60.0 * arg2;
    D_800E2C68 = arg0;
    D_800E2C64 = (D_800E2C68 - D_800E2C60) / D_800E2C78;
    D_800E2C74 = arg1;
    D_800E2C70 = (D_800E2C74 - D_800E2C6C) / D_800E2C78;
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD40C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD4B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD658.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADAB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADBC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADCBC.s")
