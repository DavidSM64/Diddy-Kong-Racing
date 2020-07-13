/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065EA0 */

#include "types.h"
#include "macros.h"
#include "structs.h"

extern u32 osTvType;
extern s8  D_800DD318;
extern s32 D_800DD31C;
extern s16 D_800DD328;
extern s8  D_800DD330;
extern s32 D_800DD37C;
extern s32 D_800DD384;
extern u8  D_800DD390;
extern s16 D_800DD394;
extern u8  D_800DD398;
extern u8  D_800DD3F0;
extern s32 D_800DD3F4;
extern s32 D_800DD408;
extern s32 D_800DD41C;
extern s32 D_80120CE0;
extern s32 D_80120CE4;
extern s32 D_80120D0C;
extern f32 D_80120D10;
extern u8  D_80120D14;
extern u8  D_80120D15;
extern s32 D_80120D18;
extern s32 D_80120F60;
extern s32 D_80120FE0;
extern s32 D_80120FA0;
extern s32 D_801210A0;
extern s32 D_801210E0;
extern s32 D_80121164;
extern s32 D_80121168;
extern s32 D_80121170;
extern s32 D_80121174;
extern s32 D_801211C0;
extern s32 D_801211F8;
extern s32 D_80121208;
extern s32 D_80121218;
extern s32 D_80121228;
extern s32 D_801234EC;
extern s32 D_801234F4;
extern s32 D_80123500;
extern s32 D_80123504;
extern Settings *gSettingsPtr;
extern s8  D_80123514;
extern s8  D_80123515;
extern s8  D_80123516;
extern s32 D_80123518;
extern s32 D_8012351C;
extern u8  D_80123524;
extern u8  D_80123525;

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80065EA0.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066060.s")

void func_80066098(s8 arg0) {
    s8 temp = (arg0 << 24) >> 24;
    if (!osTvType) {
        D_80120D15 = temp;
    }
}
void func_800660C0(void) {
    D_80120D18 = 1;
}
void func_800660D0(void) {
    D_80120D18 = 0;
}
/* Unused? */
f32 func_800660DC(void) {
    return D_80120D10;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_800660EC.s")

/* Unused? */
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066194.s")

/* Unused? */
s32* func_80066204(void) {
    return &D_801210A0;
}

s32 func_80066210(void) {
    return D_80120CE0;
}

s32 func_80066220(void) {
    return D_80120CE4;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066230.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066348.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_800663DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066488.s")

s8 func_80066510(void) {
    return D_80120D14;
}

void func_80066520(void) {
    D_80120D14 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006652C.s")

void func_800665E8(s32 arg0) {
    if (arg0 >= 0 && arg0 < 4) {
        D_80120CE4 = arg0;
    } else {
        D_80120CE4 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066610.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066818.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066894.s")


/*
// Close to matching
extern s32 D_800DD094[48];
s32 func_80066910(s32 arg0) {
    s32 index = arg0 * 13;
    return D_800DD094[index] & 0x1;
}
*/
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066910.s")

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066940.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066AA8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066BA8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066C2C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066CDC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80067A3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80067D3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80067F20.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80067F2C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006807C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80068158.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_800682AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80068408.s")

void func_80068508(s32 arg0) {
    D_80120D0C = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80068514.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80068BF4.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80068FA8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069484.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069790.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069A40.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069CFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069D20.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069D7C.s")

s32* func_80069DA4(void) {
    return &D_80120FA0;
}

s32* func_80069DB0(void) {
    return &D_80120FE0;
}

s32* func_80069DBC(void) {
    return &D_80120F60;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069DC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069E14.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069F28.s")

s32* func_8006A100(void) {
    return &D_801210E0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A10C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A1C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A434.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A458.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A4F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A50C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A528.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A554.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A578.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A59C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A5E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A624.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A6A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A6B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006B0AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006B0F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006B14C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006B190.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006B1D4.s")

void func_8006B224(s32* arg0, s32* arg1) {
    *arg0 = D_80121170;
    *arg1 = D_80121174;
}

s32 func_8006B240(void) {
    return D_800DD31C;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006B250.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006BD10.s")

s32 func_8006BD88(void) {
    return D_80121164;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006BD98.s")

s32 func_8006BDB0(void) {
    return D_80121168;
}

/* Unused? */
u8 func_8006BDC0(void) {
    return D_80121170 - 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006BDDC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006BEFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006BFC8.s")

void func_8006C164(void) {
    func_80071140(D_801211C0);
}

s32 func_8006C18C(void) {
    return D_801211C0;
}

s8 func_8006C19C(void) {
    return D_800DD318;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006C1AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006C22C.s")

void func_8006C2E4(void) {
    D_800DD328 = 0;
}

s16 func_8006C2F0(void) {
    return D_800DD328;
}

s32 func_8006C300(void) {
    if (D_800DD330 >= 2) {
        D_800DD330 = 1;
        return 0;
    } else {
        return D_800DD330;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/D_8006C330.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006C3E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006C60C.s")

void func_8006CAE4(s32 arg0, s32 arg1, s32 arg2) {
    D_80123500 = arg0 - 1;
    if (arg1 == -1) {
        D_801234F4 = func_8009C1B0();
    } else {
        D_801234F4 = arg1;
    }
    func_8006CB58(D_801234F4, D_80123500, D_80123504, arg2);
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006CB58.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006CC14.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006CCF0.s")

void func_8006D8A4(void) {
    D_800DD390 = 0x2C;
    D_80123515 = 0;
    func_800945E4();
    func_800C01D8(&D_800DD408);
}

void func_8006D8E0(s32 arg0) {
    D_80123516 = arg0 + 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006D8F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006D968.s")

s32 func_8006DA0C(void) {
    return D_801234EC;
}

/* Unused? */
void func_8006DA1C(s32 arg0) {
    D_801234EC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006DA28.s")

void func_8006DB14(s32 arg0) {
    D_80123518 = arg0;
}

void func_8006DB20(s32 arg0) {
    D_8012351C = arg0;
}

s32 func_8006DB2C(void) {
    return D_80123518;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006DB3C.s")

void func_8006DBE4(void) {
    if (D_80123514 == 0) {
        D_80123514 = 1;
        func_800710B0(0);
        func_8006BEFC();
        func_800C01D8(&D_800DD3F4);
        func_800AE270();
        func_800A003C();
        func_800C30CC();
        func_800710B0(2);
    }
    D_80123514 = 0;
}

void func_8006DC58(s32 arg0) {
    if (func_800C73E0() == 0) {
        func_80010994(arg0);
        func_8001004C();
        func_8001BF20();
        D_80024D54(&D_801211F8, &D_80121208, &D_80121218, &D_80121228, arg0);
        func_800C3440(arg0);
        func_80078054(&D_801211F8);
        func_80077050(&D_801211F8);
        func_80077268(&D_801211F8);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006DCF8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006E2E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006E3BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006E5BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006E770.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006E994.s")

Settings* get_settings(void) {
    return gSettingsPtr;
}

s8 func_8006EAA0(void) {
    return D_80123515;
}

s8 func_8006EAB0(void) {
    return D_80123516;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006EAC0.s")

s32 func_8006EB14(void) {
    return D_801234F4;
}

/* Unused? */
void func_8006EB24(void) {
    D_800DD37C |= 0x01;
}

/* Unused? */
void func_8006EB40(void) {
    D_800DD37C |= 0x02;
}

void func_8006EB5C(void) {
    D_800DD37C |= 0x03;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006EB78.s")

void func_8006EBA8(void) {
    D_800DD37C |= 0x08;
}

void func_8006EBC4(void) {
    D_800DD37C |= 0x10;
}

void func_8006EBE0(void) {
    D_800DD37C |= 0x20;
}

void func_8006EBFC(void) {
    D_800DD37C |= 0x30;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006EC18.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006EC48.s")

void func_8006ECAC(s32 arg0) {
    D_800DD37C = ((arg0 & 0x03) << 10) | 0x80;
}

/* Unused? */
void func_8006ECC4(void) {
    D_800DD37C |= 0x100;
}

void func_8006ECE0(void) {
    D_800DD37C |= 0x200;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006ECFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006EFB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006EFDC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006F140.s")

void func_8006F254(void) {
    if (D_800DD394 == 0) {
        func_800C01D8(&D_800DD41C);
        D_800DD394 = 0x28;
        D_80123524 = 2;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006F29C.s")

void func_8006F338(s32 arg0) {
    if (D_800DD394 == 0) {
        D_80123525 = arg0;
        func_800C01D8(&D_800DD41C);
        D_800DD394 = 0x28;
        D_80123524 = 4;
    }
}

void func_8006F388(u8 arg0) {
    D_800DD398 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006F398.s")

void func_8006F42C(void) {
    D_800DD3F0 = 2;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006F43C.s")

s32 func_8006F4C8(void) {
    if (D_800DD384 == -1) {
        return 1;
    } else {
        return 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006F4EC.s")
