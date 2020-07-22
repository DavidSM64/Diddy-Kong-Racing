/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065EA0 */

#include "types.h"
#include "macros.h"
#include "structs.h"
extern u32 osTvType;

/* Size: 0x34 bytes */
typedef struct unk800DD094 {
    s32 unk0;
    u8 pad4[0x1C];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
} unk800DD094;
extern unk800DD094 D_800DD064[2]; // Unknown number of entries
extern unk800DD094 D_800DD094[2]; // Unknown number of entries

extern f32 D_800DD2CC;
extern s8 D_800DD2F8[8]; // Unknown number of entries
extern s16 D_800DD304;
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
extern f32 D_800E70A4;

/* Size: 0x44 bytes */
typedef struct unk80120AC0 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8  pad6[6];
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8  pad18[0x1C];
    s16 unk34;
    s16 pad36;
    s16 unk38;
    s8  pad3A;
    s8  unk3B;
    u8  pad3C[8];
} unk80120AC0;

extern unk80120AC0 D_80120AC0[4]; // Unknown number of entries.
extern unk80120AC0 D_80120AFB[4]; // Unknown number of entries.
extern unk80120AC0 D_80120BD0[4]; // Unknown number of entries.
extern s32 D_80120CE0;
extern s32 D_80120CE4;
extern s32 D_80120D0C;
extern f32 D_80120D10;
extern s8  D_80120D14;
extern u8  D_80120D15;
extern s32 D_80120D18;
extern s32 D_80120D6C;
extern s32 D_80120EE0;
extern s32 D_80120F60;
extern s32 D_80120FE0;
extern s32 D_80120FA0;
extern s32 D_801210A0;
extern s32 D_801210E0;

/* Size: 5 bytes */
typedef struct unk80121110 {
    u16 unk0;
    s8 unk2;
    s8 unk3;
    s8 unk4;
} unk80121110;
extern unk80121110 D_80121110[2]; // Unknown number of entries
extern u16 D_80121140[2]; // Unknown number of entries.
extern u16 D_80121148[2]; // Unknown number of entries.
extern u8 D_80121150[8]; // Unknown number of entries.
extern s32 D_80121164;

/* Unknown size */
typedef struct unk80121168 {
    s32 unk0;
    u8  pad4[0x48];
    u8  unk4C;
    u8  pad4D[3];
    u16 pad50;
    u8  unk52;
    u8  pad53;
    u16 unk54;
} unk80121168;
extern unk80121168* D_80121168;

extern s32 D_80121170;
extern s32 D_80121174;

// Size: 6 bytes
typedef struct unk8012117C {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 pad3[3];
} unk8012117C;
extern unk8012117C *D_8012117C[2]; // Unknown number of entries

extern s32 D_801211C0;
extern s16 D_801211C8[8]; // Unknown number of entries
extern s32 D_801211F8;
extern s32 D_80121208;
extern s32 D_80121218;
extern s32 D_80121228;
extern s8  D_80121250[16]; // Unknown number of entries
extern s32 D_801234EC;
extern s32 D_801234F4;
extern s32 D_801234F8;
extern s32 D_80123500;
extern s32 D_80123504;
extern s32 D_80123508;
extern Settings *gSettingsPtr;
extern s8  D_80123514;
extern s8  D_80123515;
extern s8  D_80123516;
extern s32 D_80123518;
extern s32 D_8012351C;
extern u8  D_80123524;
extern u8  D_80123525;
extern s32* D_80123548; // This is actually an OSMesgQueue pointer.
extern s32 D_80123560;

extern s32 D_A4000000;
extern s32 SP_IMEM;


void func_800014BC(f32 arg0);
s8* func_8001E29C(s32 arg0);
s32 func_8006A624(s8 arg0);
void func_8006F64C(s32*, f32, f32, f32, f32*, f32*, f32*);
void func_800CC920(s32*, s32*, f32, f32, f32, f32, f32);
void func_8006F870(s32*, s32*);
s16 func_80029F18(f32, f32, f32);    
void func_8006A50C(void);
void func_8000E194(void);

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80065EA0.s")

void func_80066060(s32 arg0, s32 arg1) {
    if (arg0 >= 0 && arg0 < 4) {
        D_800DD2F8[arg0] = arg1;
        D_80120AC0[arg0].unk3B = arg1;
    }
}

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

void func_80066194(void) {
    func_800CC920(&D_80120EE0, &D_80120D6C, 60.0f, 1.33333333f, 10.0f, D_800E70A4, 1.0f);
    func_8006F870(&D_80120EE0, &D_80120FE0);
}

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

void func_80066488(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6) {
    arg0 += 4;
    D_80120AC0[arg0].unk38 = 0;
    D_80120AC0[arg0].unkC = arg1;
    D_80120AC0[arg0].unk10 = arg2;
    D_80120AC0[arg0].unk14 = arg3;
    D_80120AC0[arg0].unk0 = arg4;
    D_80120AC0[arg0].unk2 = arg5;
    D_80120AC0[arg0].unk4 = arg6;
    D_80120AC0[arg0].unk34 = func_80029F18(arg1, arg2, arg3);
    D_80120D14 = 1;
}

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

void func_80066818(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        D_800DD064[arg0].unk30 |= 1;
    } else {
        D_800DD064[arg0].unk30 |= 2;
    }
    D_800DD064[arg0].unk30 &= -5;
}

void func_80066894(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        D_800DD064[arg0].unk30 &= -2;
    } else {
        D_800DD064[arg0].unk30 |= 4;
    }
    D_800DD064[arg0].unk30 &= -3;
}

s32 func_80066910(s32 arg0) {
    return D_800DD094[arg0].unk0 & 0x1;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066940.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066AA8.s")

s32 func_80066BA8(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    *arg1 = D_800DD064[arg0].unk20;
    *arg3 = D_800DD064[arg0].unk28;
    *arg2 = D_800DD064[arg0].unk24;
    *arg4 = D_800DD064[arg0].unk2C;
    if ((*arg1 | *arg3 | *arg2 | *arg4) == 0) {
        return 0;
    }
    return 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066C2C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066CDC.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80067A3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80067D3C.s")

void func_80067F20(f32 arg0) {
    D_800DD2CC = arg0;
}

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

s16 *func_80069CFC(void) {
    return &D_80120AC0[D_80120CE4].unk0;
}

s16 *func_80069D20(void) {
    if (D_80120D14 != 0) {
        return &D_80120AC0[D_80120CE4 + 4].unk0;
    }
    return &D_80120AC0[D_80120CE4].unk0;
}

unk80120AC0 *func_80069D7C(void) {
    if (D_80120D14 != 0) {
        return D_80120BD0;
    }
    return D_80120AC0;
}

s32* func_80069DA4(void) {
    return &D_80120FA0;
}

s32* func_80069DB0(void) {
    return &D_80120FE0;
}

s32* func_80069DBC(void) {
    return &D_80120F60;
}

f32 func_80069DC8(f32 arg0, f32 arg1, f32 arg2) {
    f32 sp34;
    f32 sp30;
    f32 returnVal;
    func_8006F64C(&D_80120F60, arg0, arg1, arg2, &sp34, &sp30, &returnVal);
    return returnVal;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069E14.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069F28.s")

s32* func_8006A100(void) {
    return &D_801210E0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A10C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A1C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A434.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A458.s")

u8 func_8006A4F8(s32 arg0) {
    return D_80121150[arg0];
}

void func_8006A50C(void) {
    u8 temp = D_80121150[0];
    D_80121150[0] = D_80121150[1];
    D_80121150[1] = temp;
}

u16 func_8006A528(s32 arg0) {
    return D_80121110[D_80121150[arg0]].unk0;
}

u16 func_8006A554(s32 arg0) {
    return D_80121140[D_80121150[arg0]];
}

u16 func_8006A578(s32 arg0) {
    return D_80121148[D_80121150[arg0]];
}

s32 func_8006A59C(s32 arg0) {
    func_8006A624(D_80121110[D_80121150[arg0]].unk2);
}

s32 func_8006A5E0(s32 arg0) {
    func_8006A624(D_80121110[D_80121150[arg0]].unk3);
}

s32 func_8006A624(s8 arg0) {
    if (arg0 < 8 && arg0 >= -7) {
        return 0;
    }
    if (arg0 > 0) {
        arg0 -= 8;
        if (arg0 >= 0x47) {
            arg0 = 0x46;
        }
    } else {
        arg0 += 8;
        if (arg0 < -0x46) {
            arg0 = -0x46;
        }
    }
    return arg0;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A6A0.s")
#else
void func_8006A6A0(void) {
    D_800DD304 = 0;
}
#endif

/*!!! FILE BOUNDARY !!!*/

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A6B0.s")

s32 func_8006B0AC(s32 arg0) {
    if (arg0 > 0 && arg0 < D_80121170) {
        return (*D_8012117C)[arg0].unk2 & 0xF;
    }
    return 0;
}

s32 func_8006B0F8(s32 arg0) {
    if (arg0 > 0 && arg0 < D_80121170) {
        s32 temp = (*D_8012117C)[arg0].unk2;
        if(temp != 0) {
            return (temp >> 4) & 0xF;
        }
    }
    return 1;
}

s8 func_8006B14C(s32 arg0) {
    if (arg0 >= 0 && arg0 < D_80121170) {
        return (*D_8012117C)[arg0].unk1;
    }
    return -1;
}

s8 func_8006B190(s32 arg0) {
    if (arg0 >= 0 && arg0 < D_80121170) {
        return (*D_8012117C)[arg0].unk0;
    }
    return 0;
}

s32 func_8006B1D4(s32 arg0) {
    s8* temp;
    
    if (arg0 < 0 || arg0 >= D_80121174) {
        arg0 = 0;
    }
    temp = func_8001E29C(0x1B);
    
    return temp[arg0];
}

void func_8006B224(s32* arg0, s32* arg1) {
    *arg0 = D_80121170;
    *arg1 = D_80121174;
}

s32 func_8006B240(void) {
    return D_800DD31C;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006B250.s")

void func_8006BD10(f32 arg0) {
    if (D_80121168->unk52 != 0) {
        func_800012E8();
        func_80000B34(D_80121168->unk52);
        func_800014BC(arg0);
        func_80001074(D_80121168->unk54);
    }
}

s32 func_8006BD88(void) {
    return D_80121164;
}

u8 func_8006BD98(void) {
    return D_80121168->unk4C;
}

unk80121168* func_8006BDB0(void) {
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

void func_8006C1AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_801211C8[D_800DD328++] = arg0;
    D_801211C8[D_800DD328++] = arg1;
    D_801211C8[D_800DD328++] = arg2;
    D_801211C8[D_800DD328++] = arg3;
}

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

void func_8006D8F0(s32 arg0) {
    s32 temp;
    if (D_801234EC != 4) {
        D_801234F4 = D_80121250[0];
        D_80123504 = 0;
        D_80123508 = 0x64;
        temp = D_80121250[1];
        if (D_80121250[15] >= 0) {
            D_80123504 = D_80121250[15];
        }
        if (D_80121250[temp + 8] >= 0) {
            D_80123508 = D_80121250[temp + 8];
        }
        D_801234F8 = 1;
    }
}

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

s32 func_8006EAC0(void) {
    if (D_80123560 == 0) {
        D_80123560 = (s32) ((osRecvMesg(&D_80123548, NULL, 0) + 1) != 0);
    }
    return D_80123560;
}

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

void func_8006EB78(s32 arg0) {
    D_800DD37C &= -0x301;
    D_800DD37C |= (0x04 | ((arg0 & 3) << 8));
}

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

void func_8006EC18(s32 arg0) {
    D_800DD37C &= -0xC01;
    D_800DD37C |= (0x40 | ((arg0 & 3) << 0xA));
}

void func_8006EC48(s32 arg0) {
    if (D_801234EC == 0 && !is_in_tracks_mode()) {
        D_800DD37C &= -0xC01;
        D_800DD37C |= (0x40 | ((arg0 & 3) << 0xA));
    }
}

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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006EFB8.s")
#else
s32 func_8006EFB8(void) {
    if (D_A4000000 != -1) { // regalloc issue with D_A4000000
        return 0;
    }
    return 1;
}
#endif

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

void func_8006F398(void) {
    s32 i;
    u8 temp;
    u8 *first_racer_data;
    u8 *second_racer_data;

    func_8006A50C();
    func_8000E194();
    
    first_racer_data = (u8*)(gSettingsPtr->racers);
    second_racer_data = (u8*)(gSettingsPtr->racers + 1);
    
    for(i = 0; i < sizeof(Racer); i++) {
        temp = first_racer_data[i];
        first_racer_data[i] = second_racer_data[i];
        second_racer_data[i] = temp;
    }
}


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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006F4EC.s")
#else
s32 func_8006F4EC(void) {
    if (SP_IMEM != 0x17D7) { // Same regalloc issue as func_8006EFB8
        return 0;
    }
    return 1;
}
#endif
