/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065EA0 */

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "fast3d.h"

extern u32 osTvType;

/* Size: 0x34 bytes. Might be an array? */
typedef struct unk800DD094 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
} unk800DD094;
extern unk800DD094 D_800DD064[2]; // Unknown number of entries
extern unk800DD094 D_800DD094[2]; // Unknown number of entries

extern s32 D_800DD288;
extern s32 D_800DD2A0;
extern f32 D_800DD2CC;
extern u8 D_800DD2F8[8]; // Unknown number of entries
extern s16 D_800DD304;
extern s8  D_800DD318;
extern s32 D_800DD31C;
extern s16 D_800DD328;
extern s16 D_800DD32C;
extern s8  D_800DD330;
extern s32 D_800DD37C;
extern s32 D_800DD384;
extern s8 D_800DD38C;
extern u8  D_800DD390;
extern s16 D_800DD394;
extern u8  D_800DD398;
extern s8  D_800DD3F0;
extern s32 D_800DD3F4;
extern s32 D_800DD408;
extern s32 D_800DD41C;
extern s32 D_800DD424;
extern s32 D_800DFD94;
extern f32 D_800E70A0;
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
    f32 pad18;
    f32 unk1C;
    f32 pad20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
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
extern s32 D_80120CE8;
extern s32 D_80120D08;
extern s32 D_80120D0C;
extern f32 D_80120D10;
extern s8  D_80120D14;
extern u8  D_80120D15;
extern s32 D_80120D18;
extern s32 D_80120D1C;
extern s32 D_80120D6C;
extern s32 D_80120D70[6];
extern s32 D_80120D88[6]; // Unknown number of entries.
extern s32 D_80120EE0;
extern s32 D_80120F20;
extern s32 D_80120F60;
extern s32 D_80120FE0;
extern s32 D_80120FA0;
extern s32 D_80121060;
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

extern LevelHeader* D_80121168;

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
extern Gfx *D_801211F0[3]; // Unknown number of entries.
extern Gfx *D_801211F8;
extern s32 D_80121208;
extern s32 D_80121218;
extern s32 D_80121228;
extern s8  D_80121250[16]; // Unknown number of entries
extern s32 D_801234E8;
extern s32 D_801234EC;
extern s32 D_801234F0;
extern s32 D_801234F4;
extern s32 D_801234F8;
extern s32 D_801234FC;
extern s32 D_80123500;
extern s32 D_80123504;
extern s32 D_80123508;
extern Settings *gSettingsPtr;
extern s8  D_80123514;
extern s8  D_80123515;
extern s8  D_80123516;
extern s32 D_80123518;
extern s32 D_8012351C;
extern s32 D_80123520;
extern u8  D_80123524;
extern u8  D_80123525;
extern u8  D_80123526;
extern s32* D_80123548; // This is actually an OSMesgQueue pointer.
extern s32 D_80123560;

extern s32 D_A4000000;
extern s32 SP_IMEM;

void func_800014BC(f32 arg0);
s8* func_8001E29C(s32 arg0);
s32 func_8006A624(s8 arg0);
void func_8006F64C(s32*, f32, f32, f32, f32*, f32*, f32*);
void guPerspectiveF(s32*, s32*, f32, f32, f32, f32, f32);
void func_8006F870(s32*, s32*);
s16 func_80029F18(f32, f32, f32);    
void func_8006A50C(void);
void func_8006CB58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8006C164(void);
void func_8000E194(void);
f32 sqrtf(f32);
void osSetTime(u64);
unk80120AC0 *func_80069D20(void);
void func_800665E8(s32 arg0);
void func_8001D5E0(f32 arg0, f32 arg1, f32 arg2);
void func_800705F8(s32, f32, f32, f32);
void func_8006ECFC(s32 arg0);

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

void func_800660EC(f32 arg0) {
    if (0.0f < arg0 && arg0 < 90.0f && arg0 != D_80120D10) {
        D_80120D10 = arg0;
        guPerspectiveF(&D_80120EE0, &D_80120D6C, arg0, 1.33333333f, 10.0f, D_800E70A0, 1.0f);
        func_8006F870(&D_80120EE0, &D_80120FE0);
    }
}

void func_80066194(void) {
    guPerspectiveF(&D_80120EE0, &D_80120D6C, 60.0f, 1.33333333f, 10.0f, D_800E70A4, 1.0f);
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

void func_80066230(s32 arg0, s32 arg1) {
    unk80120AC0 *someStruct;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    s16 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    func_8006652C(0);
    func_800665E8(0);
    someStruct = func_80069D20();
    sp2A = someStruct->unk0;
    sp28 = someStruct->unk2;
    sp26 = someStruct->unk4;
    sp20 = someStruct->unkC;
    sp1C = someStruct->unk10;
    sp18 = someStruct->unk14;
    sp24 = someStruct->unk38;
    someStruct->unk4 = 0;
    someStruct->unk2 = 0;
    someStruct->unk0 = -0x8000;
    someStruct->unk38 = 0;
    someStruct->unkC = 0.0f;
    someStruct->unk10 = 0.0f;
    someStruct->unk14 = 0.0f;
    func_8001D5E0(0.0f, 0.0f, -1.0f);
    func_80066CDC(arg0, arg1);
    someStruct->unk38 = sp24;
    someStruct->unk0 = sp2A;
    someStruct->unk2 = sp28;
    someStruct->unk4 = sp26;
    someStruct->unkC = sp20;
    someStruct->unk10 = sp1C;
    someStruct->unk14 = sp18;
}

f32 func_80066348(f32 arg0, f32 arg1, f32 arg2) {
    s32 phi_v1;
    f32 temp_f2, temp_f0, temp_f14;

    phi_v1 = D_80120CE4;
    
    if (D_80120D14 != 0) {
        phi_v1 += 4;
    }
    
    temp_f0 = arg2 - D_80120AC0[phi_v1].unk14;
    temp_f2 = arg0 - D_80120AC0[phi_v1].unkC;
    temp_f14 = arg1 - D_80120AC0[phi_v1].unk10;
    return sqrtf((temp_f0 * temp_f0) + ((temp_f2 * temp_f2) + (temp_f14 * temp_f14)));
}

void func_800663DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    D_80120AC0[D_80120CE4].unk4 = (s16) (arg3 * 0xB6);
    D_80120AC0[D_80120CE4].unkC = (f32) arg0;
    D_80120AC0[D_80120CE4].unk10 = (f32) arg1;
    D_80120AC0[D_80120CE4].unk14 = (f32) arg2;
    D_80120AC0[D_80120CE4].unk2 = (s16) (arg4 * 0xB6);
    D_80120AC0[D_80120CE4].unk38 = (u16)0;
    D_80120AC0[D_80120CE4].unk24 = 0.0f;
    D_80120AC0[D_80120CE4].unk28 = 0.0f;
    D_80120AC0[D_80120CE4].unk2C = 0.0f;
    D_80120AC0[D_80120CE4].unk30 = 0.0f;
    D_80120AC0[D_80120CE4].unk1C = 160.0f;
    D_80120AC0[D_80120CE4].unk0 = (s16) (arg5 * 0xB6);
    D_80120AC0[D_80120CE4].unk3B = D_800DD2F8[D_80120CE4];
}

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

s32 func_8006652C(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4)) {
        D_80120CE0 = arg0;
    } else {
        D_80120CE0 = 0;
    }
    switch(D_80120CE0) {
        case 0:
            D_80120CE8 = 1;
            break;
        case 1:
            D_80120CE8 = 2;
            break;
        case 2:
            D_80120CE8 = 3;
            break;
        case 3:
            D_80120CE8 = 4;
            break;
    }
    if (D_80120CE4 >= D_80120CE8) {
        D_80120CE4 = 0;
    }
    return D_80120CE8;
}

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

void func_80066AA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg1 != 0x8000) {
        D_800DD064[arg0].unk10 = arg1;
        D_800DD064[arg0].unk30 |= 8;
    } else {
        D_800DD064[arg0].unk30 &= 0xFFFFFFF7;
    }
    if (arg2 != 0x8000) {
        D_800DD064[arg0].unk10 = arg2;
        D_800DD064[arg0].unk30 |= 0x10;
    } else {
        D_800DD064[arg0].unk30 &= 0xFFFFFFEF;
    }
    if (arg3 != 0x8000) {
        D_800DD064[arg0].unk18 = arg3;
        D_800DD064[arg0].unk30 |= 0x20;
    } else {
        D_800DD064[arg0].unk30 &= 0xFFFFFFDF;
    }
    if (arg4 != 0x8000) {
        D_800DD064[arg0].unk1C = arg4;
        D_800DD064[arg0].unk30 |= 0x40;
        return;
    }
    D_800DD064[arg0].unk30 &= 0xFFFFFFBF;
}

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

void func_80066C2C(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    *arg1 = D_800DD064[arg0].unk0;
    *arg2 = D_800DD064[arg0].unk4;
    *arg3 = D_800DD064[arg0].unk8;
    *arg4 = D_800DD064[arg0].unkC;
}

// Unused?
void func_80066C80(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    u32 temp_v0 = func_8007A520();
    *arg0 = 0;
    *arg1 = 0;
    *arg2 = temp_v0 & 0xFFFF;
    *arg3 = (u32) (temp_v0 >> 0x10);
}


#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80066CDC.s")
#else
// Work in progress!

void func_80066CDC(Gfx **dlist, s32 *arg1) {
    u32 sp58;
    u32 sp54;
    u32 sp50;
    u32 sp4C;
    s32 sp34;
    s32 sp2C;
    u32 temp_a0;
    u32 temp_a0_3;
    u32 temp_a0_4;
    u32 temp_a2;
    u32 temp_a3;
    u32 temp_a3_2;
    u32 temp_t0;
    u32 temp_t1_2;
    u32 temp_v0;
    u32 temp_v0_3;
    u32 temp_v0_4;
    u32 temp_v1_10;
    u32 temp_v1_3;
    u32 temp_v1_4;
    s32 phi_t1;
    s32 phi_v1;
    f32 phi_f6;
    f32 phi_f18;
    f32 phi_f16;
    f32 phi_f8;
    f32 phi_f6_2;
    f32 phi_f18_2;
    f32 phi_f8_2;
    f32 phi_f16_2;
    u32 phi_a1;
    f32 phi_f8_3;
    f32 phi_f16_3;
    f32 phi_f16_4;
    u32 phi_t3;
    u32 phi_a3_2;
    u32 phi_t5;
    u32 phi_t4;
    
    sp34 = D_80120CE4;
    phi_t1 = D_80120CE4;
    if (func_8000E184() && D_80120CE0 == 0) {
        D_80120CE4 = 1;
        phi_t1 = 0;
    }
    temp_v0 = func_8007A520();
    temp_t0 = temp_v0 >> 0x10;
    temp_a3 = temp_t0 >> 1;
    
    if (D_800DD064[phi_t1].unk30 & 1) {
        sp2C = D_80120CE4;
        D_80120CE4 = phi_t1;
        fast3d_cmd(
            (*dlist)++,
            ((((s32)(D_800DD064[D_80120CE4].unk24 * 4.0f)) & 0xFFF) | 0xED000000) | (((s32)(D_800DD064[D_80120CE4].unk20 * 4.0f)) & 0xFFF) << 0xC,
            (((s32)(D_800DD064[D_80120CE4].unk2C * 4.0f)) & 0xFFF) | (((s32)(D_800DD064[D_80120CE4].unk28 * 4.0f)) & 0xFFF) << 0xC
        )
        func_80068158(dlist, 0, 0, 0, 0);
        D_80120CE4 = sp2C;
        if (arg1 != 0) {
            func_80067D3C(dlist, arg1);
        }
        D_80120CE4 = sp34;
        return;
    }
    temp_t1_2 = temp_v0 & 0xFFFF;
    phi_v1 = D_80120CE0;
    if (D_80120CE0 == 2) {
        phi_v1 = 3;
    }
    temp_a2 = temp_t1_2 >> 1;
    sp54 = temp_a2;
    sp58 = temp_a3;
    if (osTvType == 0) {
        sp58 = 0x91;
    }
    
    switch(phi_v1) {
        case 0:
            phi_t3 = sp58;
            if (osTvType == 0) {
                phi_t3 = sp58 - 0x12;
            }
            phi_f16_4 = temp_t0;
            if (temp_t0 < 0) {
                phi_f16_4 = temp_t0 + 4294967296.0f;
            }
            fast3d_cmd(
                (*dlist)++,
                0xED000000,
                ((((s32)(temp_t1_2 * 4.0f)) & 0xFFF) << 0xC) | (((s32)(phi_f16_4 * 4.0f)) & 0xFFF)
            )
            sp4C = temp_a2;
            phi_a3_2 = temp_a2;
            break;
        case 1:
            if (D_80120CE4 == 0) {
                temp_v0_4 = temp_t0 >> 2;
                phi_t3 = temp_v0_4;
                if (osTvType == 0) {
                    phi_t3 = temp_v0_4 - 0xC;
                }
                phi_f8_3 = temp_a3 - (temp_t0 >> 7);
                if (phi_f8_3 < 0) {
                    phi_f8_3 += 4294967296.0f;
                }
                fast3d_cmd(
                    (*dlist)++,
                    0xED000000,
                    ((((s32)(temp_t1_2 * 4.0f)) & 0xFFF) << 0xC) | (((s32)(phi_f8_3 * 4.0f)) & 0xFFF)
                )
            } else {
                temp_v1_10 = temp_t0 >> 7;
                phi_f16_3 = temp_t0 - temp_v1_10;
                if (phi_f16_3 < 0) {
                    phi_f16_3 += 4294967296.0f;
                }
                fast3d_cmd(
                    (*dlist)++,
                    (((s32)((temp_a3 + temp_v1_10) * 4.0f)) & 0xFFF) | 0xED000000,
                    ((((s32)(temp_t1_2 * 4.0f)) & 0xFFF) << 0xC) | (((s32)(phi_f16_3 * 4.0f)) & 0xFFF)
                )
                phi_t3 = temp_a3 + (temp_t0 >> 2);
            }
            sp4C = temp_a2;
            phi_a3_2 = temp_a2;
            break;
        case 2:
            if (D_80120CE4 == 0) {
                phi_f8_2 = temp_t0;
                if (temp_t0 < 0) {
                    phi_f8_2 = temp_t0 + 4294967296.0f;
                }
                fast3d_cmd(
                    (*dlist)++,
                    0xED000000,
                    ((((s32)((temp_a2 - (temp_t1_2 >> 8)) * 4.0f)) & 0xFFF) << 0xC) | (((s32)(phi_f8_2 * 4.0f)) & 0xFFF)
                )
                phi_a1 = temp_t1_2 >> 2;
            } else {
                temp_a0_4 = temp_t1_2 >> 8;
                phi_f16_2 = temp_t0;
                if (temp_t0 < 0) {
                    phi_f16_2 = temp_t0 + 4294967296.0f;
                }
                fast3d_cmd(
                    (*dlist)++,
                    (((s32)((temp_a2 + temp_a0_4) * 4.0f) & 0xFFF) << 0xC) | 0xED000000,
                    (((s32)((temp_t1_2 - temp_a0_4) * 4.0f) & 0xFFF) << 0xC) | (((s32)(phi_f16_2 * 4.0f)) & 0xFFF)
                )
                phi_a1 = temp_a2 + (temp_t1_2 >> 2);
            }
            sp4C = phi_a1;
            phi_t3 = sp58;
            phi_a3_2 = phi_a1;
            break;
        case 3:
            switch(D_80120CE4) {
                case 0:
                    phi_f6_2 = temp_a2 - (temp_t1_2 >> 8);
                    if (phi_f6_2 < 0) {
                        phi_f6_2 += 4294967296.0f;
                    }
                    phi_f18_2 = temp_a3 - (temp_t0 >> 7);
                    if (phi_f18_2 < 0) {
                        phi_f18_2 += 4294967296.0f;
                    }
                    fast3d_cmd(
                        (*dlist)++,
                        ((((s32)(0U * 4.0f) & 0xFFF) << 0xC) | 0xED000000) | (((s32)(0U * 4.0f)) & 0xFFF),
                        (((s32)(phi_f6_2 * 4.0f) & 0xFFF) << 0xC) | (((s32)(phi_f18_2 * 4.0f)) & 0xFFF)
                    )
                    phi_t5 = 0U;
                    phi_t4 = 0U;
                    break;
                case 1:
                    temp_a0_3 = temp_t1_2 >> 8;
                    phi_f8 = temp_a3 - (temp_t0 >> 7);
                    if (phi_f8 < 0) {
                        phi_f8 += 4294967296.0f;
                    }
                    fast3d_cmd(
                        (*dlist)++,
                        ((((s32)((temp_a2 + temp_a0_3) * 4.0f)) & 0xFFF) << 0xC) | 0xED000000,
                        ((((s32)(((temp_a2 * 2) - temp_a0_3) * 4.0f)) & 0xFFF) << 0xC) | (((s32)(phi_f8 * 4.0f)) & 0xFFF)
                    )
                    phi_t5 = 0U;
                    phi_t4 = temp_a2;
                    break;
                case 2:
                    temp_v1_4 = temp_t0 >> 7;
                    phi_f16 = (temp_a3 * 2) - temp_v1_4;
                    if (phi_f16 < 0) {
                        phi_f16 += 4294967296.0f;
                    }
                    fast3d_cmd(
                        (*dlist)++,
                        (((s32)((temp_a3 + temp_v1_4) * 4.0f)) & 0xFFF) | 0xED000000,
                        ((((s32)((temp_a2 - (temp_t1_2 >> 8)) * 4.0f)) & 0xFFF) << 0xC) | (((s32)(phi_f16 * 4.0f)) & 0xFFF)
                    )
                    phi_t5 = temp_a3;
                    phi_t4 = 0U;
                    break;
                case 3:
                    temp_a0 = temp_t1_2 >> 8;
                    temp_v1_3 = temp_t0 >> 7;
                    phi_f6 = (temp_a2 * 2) - temp_a0;
                    if (phi_f6 < 0) {
                        phi_f6 += 4294967296.0f;
                    } 
                    phi_f18 = (temp_a3 * 2) - temp_v1_3;
                    if (phi_f18 < 0) {
                        phi_f18 += 4294967296.0f;
                    }
                    fast3d_cmd(
                        (*dlist)++,
                        (((((s32)((temp_a2 + temp_a0) * 4.0f)) & 0xFFF) << 0xC) | 0xED000000) | (((s32)((temp_a3 + temp_v1_3) * 4.0f)) & 0xFFF),
                        ((((s32)(phi_f6 * 4.0f) & 0xFFF)) << 0xC) | (((s32)(phi_f18 * 4.0f)) & 0xFFF)
                    )
                    phi_t5 = temp_a3;
                    phi_t4 = temp_a2;
                    break;
                default:
                    phi_t5 = 0;
                    phi_t4 = 0;
                    break;
            }
            temp_v0_3 = phi_t5 + sp58;
            temp_a3_2 = phi_t4 + sp54;
            phi_t3 = temp_v0_3;
            phi_a3_2 = temp_a3_2;
            if (osTvType == 0) {
                phi_t3 = temp_v0_3 - 6;
                phi_a3_2 = temp_a3_2;
                if (D_80120CE4 < 2) {
                    phi_t3 = temp_v0_3 - 0x14;
                    phi_a3_2 = temp_a3_2;
                }
            }
            break;
        default:
            phi_t3 = sp50;
            phi_a3_2 = sp4C;
            break;
    }
    
    if (osTvType == 0) {
        phi_a3_2 -= 4;
    }
    func_80068158(dlist, sp54, sp58, phi_a3_2, phi_t3);
    if (arg1 != 0) {
        func_80067D3C(dlist, arg1);
    }
    D_80120CE4 = sp34;
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80067A3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80067D3C.s")

void func_80067F20(f32 arg0) {
    D_800DD2CC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80067F2C.s")

void func_8006807C(Gfx **dlist, s32 *arg1) {
    func_8006FE74(&D_80121060, &D_800DD288);
    func_8006F768(&D_80121060, &D_80120EE0, &D_80120F20);
    func_8006FE74(D_80120D70[0], &D_800DD2A0);
    func_8006F768(D_80120D70[0], &D_80120F20, &D_80121060);
    func_8006F870(&D_80121060, (s32*)*arg1); // This doesn't look right. Need to check this!
    fast3d_cmd((*dlist)++, 0x1000040, (u32)(*arg1 + 0x80000000))
    *arg1 += 0x40;
    D_80120D1C = 0;
    D_80120D08 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80068158.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_800682AC.s")

void func_80068408(Gfx **dlist, s32 *arg1) {
    func_800705F8(D_80120D70[D_80120D1C], 0.0f, 0.0f, 0.0f);
    func_8006F768(D_80120D70[D_80120D1C], &D_80120F20, &D_80121060);
    func_8006F870(&D_80121060, (s32*)*arg1); // This doesn't look right. Need to check this!
    D_80120D88[D_80120D1C] = *arg1;
    
    fast3d_cmd((*dlist)++, ((((D_80120D08 << 6) & 0xFF) << 0x10) | 0x1000000) | 0x40, (u32)(*arg1 + 0x80000000))
    
    *arg1 += 0x40;
}

void func_80068508(s32 arg0) {
    D_80120D0C = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80068514.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80068BF4.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80068FA8.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069484.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069790.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069A40.s")

unk80120AC0 *func_80069CFC(void) {
    return &D_80120AC0[D_80120CE4];
}

unk80120AC0 *func_80069D20(void) {
    if (D_80120D14 != 0) {
        return &D_80120AC0[D_80120CE4 + 4];
    }
    return &D_80120AC0[D_80120CE4];
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

void func_80069E14(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f14;
    f32 temp_f2;
    s32 i;
    
    for (i = 0; i <= D_80120CE0; i++) {
        temp_f0 = arg0 - D_80120AC0[i].unkC;
        temp_f2 = arg1 - D_80120AC0[i].unk10;
        temp_f14 = arg2 - D_80120AC0[i].unk14;
        temp_f0_2 = sqrtf(((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) + (temp_f14 * temp_f14));
        if (temp_f0_2 < arg3) {
            D_80120AC0[i].unk30 = ((arg3 - temp_f0_2) * arg4) / arg3;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_80069F28.s")

s32* func_8006A100(void) {
    return &D_801210E0;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A10C.s")
#else

extern s32 D_800DD300; 
extern s32 D_801210F8;  
extern s32 D_801210FC;
extern s8 D_80121100;   
extern u8 D_80121103;   

// Has regalloc & stack issues.
s32 func_8006A10C(void) {
    u8 sp23;
    osCreateMesgQueue(&D_801210E0, &D_801210F8, 1);
    osSetEventMesg(5, &D_801210E0, D_801210FC);
    func_800CCC20(&D_801210E0, &sp23, &D_80121100);
    func_800CCFE0(&D_801210E0);
    func_8006A434();
    D_800DD300 = 0;
    if ((sp23 & 1) && !(D_80121103 & 8)) {
        return 0;
    }
    D_800DD300 = 1;
    return -1;
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A1C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006A434.s")

void func_8006A458(s8 *activePlayers) {
    s32 i;
    s32 temp = 0;
    for(i = 0; i < 4; i++) {
        if (activePlayers[i]) {
            D_80121150[temp++] = i;
        }
    }
    for(i = 0; i < 4; i++) {
        if (!activePlayers[i]) {
            D_80121150[temp++] = i;
        }
    }
}

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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006B250.s")
#else

extern s32 *D_80121160;
extern s32 D_800DD314;

Settings *get_settings(void);
s32 *func_80076C58(s32);
LevelHeader *func_80070C9C(s32, s32);
void func_8006C1AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8006C2E4(void);
s16 func_8006C2F0(void);
void func_8006DB20(s32 arg0);
void func_80072708(void);

// load_level(levelID, numOfPlayers, entrance, vehicle, ???);
void func_8006B250(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp48;
    s32 sp44;
    Settings *settings;
    s32 temp_s0_2;
    s32 temp_s0_5;
    s32 temp_t8_3;
    s32 temp_v0_5;
    s8 *temp_v0_4;
    s32 phi_v1;
    s32 phi_v1_2;
    s32 phi_v0_2;
    s32 phi_s0;
    s32 phi_v1_5;
    s8 phi_s0_2;
    s32 phi_at;
    s32 phi_s0_3;
    s32 phi_s0_5;
    s32 phi_v1_9;
    s32 temp, temp2;

    func_80072708();
    if (arg4 == -1) {
        arg4 = 0;
    }
    if (arg1 == -1) {
        sp48 = 1;
        arg1 = 0;
    } else {
        sp48 = 0;
    }
    if (arg1 == 0) {
        func_8000318C(0x8);
    } else if (arg1 == 1) {
        func_8000318C(0xC);
    } else {
        func_8000318C(0x10);
    }
    
    settings = get_settings();
    D_80121160 = func_80076C58(0x16);
    phi_v1 = 0;
    while (-1 != D_80121160[phi_v1]) {
        phi_v1++;
    }
    phi_v1--;
    if (arg0 >= phi_v1) {
        arg0 = 0;
    }
    temp2 = D_80121160[arg0];
    temp = D_80121160[arg0 + 1] - temp2;
    D_80121168 = func_80070C9C(temp, 0xFFFF00FF);
    func_80076E68(0x17, D_80121168, temp2, temp);
    D_800DD330 = 0;
    sp44 = arg0;
    if (D_80121168->race_type == 0) {
        func_8006C2E4();
    }
    if (func_8006C2F0() == 0) {
        if (D_800DD32C == 0) {
            if (D_80121168->race_type == 8) {
                phi_v1_2 = settings->courseFlagsPtr[temp2] & 1;
                phi_v0_2 = 0;
                if (D_80121168->world == 0 || D_80121168->world == 5) {
                    phi_v0_2 = 1;
                }
                if (phi_v1_2 == 0 || phi_v0_2 != 0) {
                    func_8006C1AC(arg0, arg2, arg3, arg4);
                    if ((settings->bosses & (1 << settings->worldId)) != 0) {
                        arg4 = 7;
                    } else {
                        arg4 = 3;
                    }
                    if (phi_v0_2 != 0) {
                        arg4 = 0;
                        if (phi_v1_2 != 0) {
                            D_800DD330 = (u8)2;
                        }
                    }
                    temp_v0_4 = func_8001E29C(0x43);
                    phi_s0 = 0;
                    while(arg0 != temp_v0_4[phi_s0 + 1]) {
                        phi_s0++;
                    }
                    arg0 = temp_v0_4[phi_s0 + 1];
                    arg2 = arg4;
                }
                
            }
            if (D_80121168->race_type == 5) {
                if (D_80121168->world > 0 && D_80121168->world < 5) {
                    if ((settings->keys & (1 << D_80121168->world)) != 0) {
                        temp_v0_5 = 0x4000 << (D_80121168->world + 0x1F);
                        if ((settings->cutsceneFlags & temp_v0_5) == 0) {
                            func_8006C1AC(arg0, arg2, arg3, arg4);
                            settings->cutsceneFlags |= temp_v0_5;
                            arg2 = 0;
                            arg4 = 5;
                            arg0 = func_8001E29C(0x44)[D_80121168->world - 1];
                        }
                    }
                }
            }
            if (D_80121168->race_type == 5 && D_80121168->world == 0 && (settings->cutsceneFlags & 0x2000) == 0 && settings->wizpigAmulet >= 4) {
                s32 temp_a1 = arg2;
                s32 temp_a3 = arg4;
                arg4 = 0;
                arg2 = 0;
                func_8006C1AC(arg0, temp_a1, arg3, temp_a3);
                settings->cutsceneFlags |= 0x2000;
                arg0 = (s32) func_8001E29C(0x44)[1];
            }
        }
    }
    D_800DD32C = 0;
    if (sp44 != arg0) {
        func_80071140(D_80121168);
        temp2 = D_80121160[arg0];
        temp = D_80121160[arg0 + 1] - temp2;
        D_80121168 = func_80070C9C(temp, 0xFFFF00FF);
        func_80076E68(0x17, D_80121168, temp2, temp);
    }
    func_80071140(D_80121160);
    func_8006BFC8(&D_80121168->unk20);
    func_8000CBC0();
    D_80121164 = arg0;
    for (phi_v1_5 = 0; phi_v1_5 < 7; phi_v1_5++) {
        if ((s32)D_80121168->unk74[phi_v1_5] != -1) {
            D_80121168->unk74[phi_v1_5] = func_8001E29C((s32)D_80121168->unk74[phi_v1_5]);
            func_8007F1E8(D_80121168->unk74[phi_v1_5]);
        }
    }
    if (arg4 == 0x64) {
        if(get_trophy_race_world_id() != 0 && D_80121168->race_type == 0) {
            arg4 = 0;
        } else if(is_in_tracks_mode() == 1 && D_80121168->race_type == 0) {
            arg4 = 0;
        }
    }
    if (D_80121168->race_type == 0 || D_80121168->race_type == 8) {
        D_800DD31C = 1;
    } else {
        D_800DD31C = 0;
    }
    if (sp48 != 0 && D_80121168->race_type != 7) {
        D_80121168->race_type = 6;
    }
    func_80000BE0(D_80121168->unkB3);
    func_80000CBC();
    func_80031BB8(0x20);
    phi_s0_2 = (u8)0;
    if (arg3 >= 0 && arg3 < 3) {
        phi_s0_2 = D_80121168->unk4F[arg3];
    }
    func_80017E74(phi_s0_2);
    settings->courseId = arg0;
    if (D_80121168->world != -1) {
        settings->worldId = D_80121168->world;
    }
    if (settings->worldId == 0 && settings->worldId > 0) {
        D_800DD314 = func_8006DB2C();
    }
    if (settings->worldId == 0 && settings->worldId > 0 && D_800DD314 != -1) {
        arg3 = D_800DD314;
    }
    func_8006DB20(arg3);
    if (D_80121168->race_type == 5) {
        if (settings->worldId > 0) {
            temp_s0_5 = 8 << (settings->worldId + 31);
            if (settings->worldId == 5) {
                if (settings->balloonsPtr[0] >= 47) {
                    if (settings->ttAmulet >= 4) {
                        if ((settings->cutsceneFlags & temp_s0_5) == 0) {
                            settings->cutsceneFlags |= temp_s0_5;
                            arg4 = 5;
                        }
                    }
                }
            } else {
                if (settings->balloonsPtr[settings->worldId] >= 4) {
                    if ((settings->cutsceneFlags & temp_s0_5) == 0) {
                        settings->cutsceneFlags |= temp_s0_5;
                        arg4 = 5;
                    }
                }
                temp_t8_3 = temp_s0_5 << 5;
                if (settings->balloonsPtr[settings->worldId] >= 8) {
                    if ((settings->cutsceneFlags & temp_t8_3) == 0) {
                        settings->cutsceneFlags |= temp_t8_3;
                        arg4 = 5;
                    }
                }
            }
        }
    }
    if (arg1 != 0 && D_80121168->race_type == 0) {
        arg4 = 0x64;
    }
    if (D_80121168->race_type == 0 || ((D_80121168->race_type & 0x40) != 0 && is_in_two_player_adventure(D_80121168->race_type) != 0)) {
        D_800DD318 = (u8)1;
        arg4 = 0x64;
    } else {
        D_800DD318 = (u8)0;
    }
    if (D_80121168->race_type == 0 && sp48 == 0 && func_8000E4C8(arg4) != 0) {
        arg4 = 0x64;
    }
    func_8001E450(arg4);
    func_800249F0(D_80121168->geometry, D_80121168->skybox, arg1, arg3, arg2, D_80121168->collectables, D_80121168->unkBA);
    if (D_80121168->unk3A == 0 && D_80121168->unk3C == 0 && D_80121168->fogR == 0 && D_80121168->fogG == 0 && D_80121168->fogB == 0) {
        phi_s0_3 = 0;
        while(phi_s0_3 < 4) {
            func_800307BC(phi_s0_3);
            phi_s0_3++;
        }
    } else {
        phi_s0_3 = 0;
        while(phi_s0_3 < 4) {
            func_80030664(phi_s0_3, D_80121168->unk3A, D_80121168->unk3C, (u8)D_80121168->fogR, D_80121168->fogG, D_80121168->fogB);
            phi_s0_3++;
        }
    }
    settings = get_settings();
    if (D_80121168->world != -1) {
        settings->worldId = D_80121168->world;
    }
    settings->courseId = arg0;
    if (D_80121168->weather_enable > 0) {
        func_800AB4A8(
            D_80121168->unk92, 
            D_80121168->weather_enable, 
            D_80121168->unk96 << 8, 
            D_80121168->unk98 << 8, 
            D_80121168->unk9A << 8, 
            D_80121168->unk94 * 0x101, 
            D_80121168->unk95 * 0x101
        );
        func_800AB308(-1, -0x200);
    }
    if (D_80121168->unk49 == -1) {
        D_80121168->unkA4 = func_8007AE74(D_80121168->unkA4);
        D_80121168->unkA8 = (u16)0;
        D_80121168->unkAA = (u16)0;
    }
    if ((s32)D_80121168->unkAC != -1) {
        D_80121168->unkAC = func_8001E29C((s32)D_80121168->unkAC);
        func_8007F414(D_80121168->unkAC);
    }
    func_800660EC((f32)D_80121168->unk9C);
    func_80077B34(D_80121168->unk9D, D_80121168->unk9E, D_80121168->unk9F);
    func_8007A974();
    func_8007AB24(D_80121168->unk4[arg1]);
}
#endif

void func_8006BD10(f32 arg0) {
    if (D_80121168->music != 0) {
        func_800012E8();
        func_80000B34(D_80121168->music);
        func_800014BC(arg0);
        func_80001074(D_80121168->instruments);
    }
}

s32 func_8006BD88(void) {
    return D_80121164;
}

u8 func_8006BD98(void) {
    return D_80121168->race_type;
}

LevelHeader* func_8006BDB0(void) {
    return D_80121168;
}

/* Unused? */
u8 func_8006BDC0(void) {
    return D_80121170 - 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006BDDC.s")

void func_8006BEFC(void) {
    func_8006C164();
    func_80077B34(0, 0, 0);
    func_80071140(D_80121168);
    func_800049D8();
    func_80001844();
    func_800018E0();
    func_800012E8();
    func_80031B60();
    func_8002C7D4();
    func_80008174();
    func_80000968(0);
    if (D_80121168->weather_enable > 0) {
        func_800AB35C();
    }
    if (D_80121168->unk49 == 0xFF) {
       func_8007B2BC(D_80121168->unkA4);
    }
}

extern s32 *D_80121160;
Settings *get_settings(void);
s32 *func_80076C58(s32);

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006BFC8.s")
#else
void func_8006BFC8(s8 *arg0) {
    s32 temp, temp2;
    s16 phi_v1;
    s8 phi_s0 = 0;
    
    if (!is_in_tracks_mode()) {
        Settings *settings = get_settings();
        // Regalloc issue: temp3 should be a3, not v1.
        s32 temp3 = settings->courseFlagsPtr[settings->courseId];
        if (temp3 & 2) {
            phi_s0 = 1;
        }
        if (temp3 & 4) {
            phi_s0 = 2;
        }
    } else {
        phi_s0 = 3;
    }
    
    if (get_trophy_race_world_id() != 0) {
        phi_s0 = 4;
    }
    
    if(is_in_adventure_two()){
        phi_s0 += 5;
    }
    
    phi_s0 = arg0[phi_s0];
    
    if ((func_8009C30C() << 6) < 0) {
        phi_s0 = 9;
    }
    if (func_8006DA0C() == 1) {
        phi_s0 = 5;
    }
    D_80121160 = func_80076C58(1);
    phi_v1 = 0;
    while (-1 != (s32)D_80121160[phi_v1]) {
        phi_v1++;
    }
    phi_v1--;
    if (phi_s0 >= phi_v1) {
        phi_s0 = 0;
    }
    temp2 = D_80121160[phi_s0];
    temp = D_80121160[phi_s0 + 1] - temp2;
    D_801211C0 = func_80070C9C(temp, 0xFFFF00FF, D_80121160);
    func_80076E68(0, D_801211C0, temp2, temp);
    func_80071140(D_80121160);
}
#endif

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

void func_8006C22C(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s16 temp_v1;
    
    D_800DD328--;
    *arg3 = D_801211C8[D_800DD328];
    D_800DD328--;
    temp_v1 = D_801211C8[D_800DD328];
    D_800DD328--;
    *arg1 = D_801211C8[D_800DD328];
    D_800DD328--;
    *arg0 = D_801211C8[D_800DD328];
    
    if (temp_v1 != -1) {
        *arg2 = temp_v1;
    }
    
    D_800DD32C = 1;
}


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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/D_8006C330.s")
#else
void func_8006C330(s32 arg0) {
    func_8006C3E0();
    D_800DD37C = func_8006A1C4(D_800DD37C, 0);
    D_80123520 = 0;
    D_801234EC = -1;
    while(1) {
        if (func_8006EAC0() != 0) {
            func_80072708();
            func_80002A74();
            func_800C73BC();
            __osSpSetStatus(0xAAAA82);
            func_800CD250(0x1D6);
            while(1); // Infinite loop
        }
        func_8006C60C();
        func_80065E30();
    }
    // This infinite loop creates too many nops! Needs to be 0x10 aligned, not 0x20 aligned.
}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006C3E0.s")
#else
extern Gfx *D_801211F0;
extern u8 D_800DD374;
extern u8 D_800DD3A0;
extern u16 D_80121260;
extern u8 D_80123538;

extern s32 D_80123544;
extern s32 D_801234E8;

void func_80079350(u16*, s32*, s32, u8, s32);
void func_80079480(u16*, u8*, s32**, s32);

void func_8006C3E0(void) {
    s32 sp24;

    func_80070B30();
    func_800C6170();
    D_800DD374 = 1;
    if (func_8006F4EC() != 0) {
        D_800DD374 = 0;
    }
    D_80123514 = 0;
    D_80123518 = 0;
    
    if (osTvType == 0) {
        sp24 = 0xE;
    } else if (osTvType == 1) {
        sp24 = 0;
    } else if (osTvType == 2) {
        sp24 = 0x1C;
    }
    
    func_80079350(&D_80121260, &D_801234E8, 0xD, sp24, 1);
    D_800DD3A0 = 0;
    if (func_8006EFB8() == 0) {
        D_800DD3A0 = 1;
    }
    func_8007A310(1, &D_80121260);
    func_80076BA0();
    func_80078100(&D_80121260);
    audio_init(&D_80121260);
    func_80008040();
    D_800DD384 = func_8006A10C();
    func_8007AC70();
    func_8005F850();
    func_8000BF8C();
    func_800B5E88();
    func_800598D0();
    func_800AE530();
    func_800AB1F0();
    func_8006E3BC();
    func_8006EFDC();
    func_800C3C00();
    func_80075B18();
    func_80081218();
    func_800C7350();
    osCreateMesgQueue(&D_80123548, &D_80123544, 1);
    func_80079480(&D_80121260, &D_80123538, &D_80123548, 3);
    D_80123560 = 0;
    D_80123504 = 0;
    D_80123508 = 0;
    D_801234E8 = 0;
    
    // ???
    D_801211F8 = D_801211F0;
    fast3d_cmd(D_801211F8++, 0xE9000000, 0x00000000)
    fast3d_cmd(D_801211F8++, 0xB8000000, 0x00000000)
    
    osSetTime(0);
}
#endif

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

void func_8006CB58(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8006ECFC(arg1);
    func_800710B0(0);
    func_80065EA0();
    func_800C3048();
    func_8006B250(arg0, arg1, arg2, arg3, D_80123508);
    func_8009ECF0(func_80066210());
    func_800AE728(8, 0x10, 0x96, 0x64, 0x32, 0);
    func_8001BF20();
    osSetTime(0);
    func_800710B0(2);
    func_80072298(1);
}

void func_8006CC14(void) {
    func_800710B0(0);
    if (D_800DD38C == 0) {
        if (D_800DD3F0 != 1) {
            func_80077A54();
        }
        D_800DD38C = 1;
    }
    func_8006BEFC();
    func_800C01D8(&D_800DD3F4);
    func_800AE270();
    func_800A003C();
    func_800C30CC();
    D_801211F8 = D_801211F0[D_801234E8];
    fast3d_cmd(D_801211F8++, 0xE9000000, 0x00000000)
    fast3d_cmd(D_801211F8++, 0xB8000000, 0x00000000)
    func_800710B0(2);
}

// Has a jump table
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

void func_8006D968(s8 *arg0) {
    s32 i;
    if (D_801234EC != 4) {
        D_80121250[0] = D_801234F4;
        for(i = 0; i < 2; i++) {
            D_80121250[i + 2] = arg0[i + 8];
            D_80121250[i + 4] = arg0[i + 10];
            D_80121250[i + 6] = arg0[i + 12];
            D_80121250[i + 8] = arg0[i + 14];
            D_80121250[i + 10] = arg0[i + 18];
            D_80121250[i + 12] = arg0[i + 20];
        }
        D_80121250[14] = arg0[22];
        D_80121250[15] = arg0[23];
        D_801234FC = 1;
    }
}

s32 func_8006DA0C(void) {
    return D_801234EC;
}

/* Unused? */
void func_8006DA1C(s32 arg0) {
    D_801234EC = arg0;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006DA28.s")
#else

// For some reason this function is storing arg0 in s0.

void func_8006DB3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800813C0(s32);
void func_80004A60(s32, s32);
void MenuInit(s32);

void func_8006DA28(s32 arg0, s32 arg1, s32 arg2) {
    func_8006ECFC(0);
    D_801234EC = 1;
    D_801234F0 = 1;
    func_80004A60(0, 0x7FFF);
    func_80004A60(1, 0x7FFF);
    func_80004A60(2, 0x7FFF);
    func_80065EA0();
    
    if (D_80123514 == 0) {
        D_80123514 = 0; // Someone at rare: "I know I just checked if this was zero, but I need to be sure!"
        if (arg1 < 0) {
            D_80123514 = 1;
        } else {
            func_8006DB3C(arg1, -1, 0, 2, arg2);
        }
    }
    if (arg0 == 0 || arg0 == 1 || arg0 == 2) {
        func_800813C0(arg0);
    }
    MenuInit(arg0);
    D_80123504 = 0;
}
#endif

void func_8006DB14(s32 arg0) {
    D_80123518 = arg0;
}

void func_8006DB20(s32 arg0) {
    D_8012351C = arg0;
}

s32 func_8006DB2C(void) {
    return D_80123518;
}

void func_8006DB3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_800710B0(0);
    func_80065EA0();
    func_800C3048();
    func_8006B250(arg0, arg1, arg2, arg3, arg4);
    func_8009ECF0(func_80066210());
    func_800AE728(4, 4, 0x6E, 0x30, 0x20, 0);
    func_8001BF20();
    osSetTime(0);
    func_800710B0(2);
}

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

// Has a jump table
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006DCF8.s")

void func_8006E2E8(s32 arg0, s32 arg1, s32 arg2) {
    if (D_80123514 == 0) {
        func_8006DBE4();
        if (func_800C73E0() == 0) {
            D_801211F8 = D_801211F0[D_801234E8];
            fast3d_cmd(D_801211F8++, 0xE9000000, 0x00000000)
            fast3d_cmd(D_801211F8++, 0xB8000000, 0x00000000)
        }
    }
    if (arg0 != -1) {
        func_8006DB3C(arg0, arg1, 0, 2, arg2);
        D_80123514 = (u8)0;
        return;
    }
    D_80123514 = (u8)1;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006E3BC.s")

void func_8006E5BC(void) {
    s32 i, j;
    gSettingsPtr->playerCount = func_8009C3C8();
    for (i = 0; i < 8; i++) {
        gSettingsPtr->racers[i].best_times = 0;
        gSettingsPtr->racers[i].character = func_8009C228(i);
        if (gSettingsPtr->playerCount >= 2) {
            gSettingsPtr->racers[i].starting_position = i;
        } else if (is_in_two_player_adventure()) {
            gSettingsPtr->racers[i].starting_position = 5 - i;
        } else {
            gSettingsPtr->racers[i].starting_position = 7 - i;
        }
        gSettingsPtr->racers[i].unk7 = 0;
        for(j = 0; j < 4; j++) {
            gSettingsPtr->racers[i].placements[j] = 0;
        }
        gSettingsPtr->racers[i].course_time = 0;
        for(j = 0; j < 3; j++) {
            gSettingsPtr->racers[i].lap_times[j] = 0;
        }
    }
    gSettingsPtr->timeTrialRacer = 0;
    gSettingsPtr->unk115[0] = 0;
    gSettingsPtr->unk115[1] = 0;
    gSettingsPtr->display_times = 0;
    gSettingsPtr->worldId = 0;
    gSettingsPtr->courseId = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006E770.s")

void func_8006E994(Settings* settings) {
    s32 i;
    s32 sp20;
    s32 sp1C;

    func_8006B224(&sp1C, &sp20);
    settings->newGame = 1;
    
    for (i = 0; i < sp20; i++) {
        settings->balloonsPtr[i] = 0;
    }
    for(i = 0; i < sp1C; i++) {
        settings->courseFlagsPtr[i] = 0;
    }
    
    settings->keys = 0;
    settings->unkA = 0;
    settings->bosses = 0;
    settings->trophies = 0;
    settings->cutsceneFlags = 0;
    settings->tajFlags = 0;
    settings->ttAmulet = 0;
    settings->wizpigAmulet = 0;
}

// Unused?
void func_8006EA58(void) {
    func_8006E770(gSettingsPtr, 3);
    func_8006E994(gSettingsPtr);
}

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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_066AA0/func_8006EFDC.s")
#else
    
/* Size: 0x40 bytes, I think this might be a 4x4 matrix. */
typedef struct unk80121200 {
    u8 pad0[0x40];
} unk80121200;

/* Size: 10 bytes */
typedef struct unk80121210 {
    u8 pad0[10];
} unk80121210;

/* Size: 16 bytes */
typedef struct unk80121220 {
    u8 pad0[16];
} unk80121220;

extern s32 D_8012350C;

extern s32 D_800DD3BC;
extern s32 D_800DD3CC;
extern s32 D_800DD3DC;
extern s32 D_800DD3EC;

extern s32 D_80123528;
extern s32 D_8012352C;
extern s32 D_80123530;
extern s32 D_80123534;

extern unk80121200 *D_80121200[3];
extern unk80121210 *D_80121210[3];
extern unk80121220 *D_80121220[3];

void *func_80070C9C(s32, s32); // Allocates memory?

void func_8006EFDC(void) {
    s32 size;
    s8* current;

    D_8012350C = 3;
    
    size = (D_800DD3EC * sizeof(unk80121220)) + 
           (D_800DD3BC * sizeof(Gfx)) + 
           (D_800DD3DC * sizeof(unk80121200)) + 
           (D_800DD3CC * sizeof(unk80121210));
    
    current = (s8*)func_80070C9C(size, 0xFF0000FF);
    D_801211F0[0] = (Gfx*)current;
    current += (D_800DD3BC * sizeof(Gfx));
    D_80121200[0] = (unk80121200*)current;
    current += (D_800DD3DC * sizeof(unk80121200));
    D_80121210[0] = (unk80121210*)current;
    current += (D_800DD3CC * sizeof(unk80121210));
    D_80121220[0] = (unk80121220*)current;
    
    current = (s8*)func_80070C9C(size, 0xFFFF00FF);
    D_801211F0[1] = (Gfx*)current;
    current += (D_800DD3BC * sizeof(Gfx));
    D_80121200[1] = (unk80121200*)current;
    current += (D_800DD3DC * sizeof(unk80121200));
    D_80121210[1] = (unk80121210*)current;
    current += (D_800DD3CC * sizeof(unk80121210));
    D_80121220[1] = (unk80121220*)current;
    
    D_80123528 = D_800DD3BC;
    D_8012352C = D_800DD3DC;
    D_80123530 = D_800DD3EC;
    D_80123534 = D_800DD3CC;
}
#endif

void func_8006F140(s32 arg0) {
    if (D_800DD394 == 0) {
        D_800DD394 = 0x28;
        D_80123524 = 0;
        D_80123526 = 0;
        if (arg0 == 1) {
            func_800C01D8(&D_800DD41C);
        }
        if (arg0 == 3) {
            D_800DD394 = 0x11A;
            func_800C01D8(&D_800DD424);
        }
        if (arg0 == 4) {
            D_800DD394 = 0x168;
            func_800C01D8(&D_800DD424);
        }
        if (arg0 == 0) {
            D_800DD394 = 2;
        }
    }
}

// Unused?
void func_8006F20C(void) {
    if (D_800DD394 == 0) {
        func_800C01D8(&D_800DD41C);
        D_800DD394 = 0x28;
        D_80123524 = 1;
    }
}

void func_8006F254(void) {
    if (D_800DD394 == 0) {
        func_800C01D8(&D_800DD41C);
        D_800DD394 = 0x28;
        D_80123524 = 2;
    }
}

void func_8006F29C(void) {
    if (D_800DD394 == 0) {
        if ((gSettingsPtr->trophies & 0xFF) == 0xFF && !(gSettingsPtr->cutsceneFlags & 1) && gSettingsPtr->bosses & 1) {
            gSettingsPtr->cutsceneFlags |= 1;
            func_800C01D8(&D_800DD41C);
            D_800DD394 = 0x28;
            D_80123525 = 0x2D;
            D_80123524 = 3;
        }
    }
}

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

void func_8006F43C(void) {
    s32 phi_s1 = 0;
    s32 phi_s0 = 0;
    while(phi_s0 != 4) {
        phi_s1 |= func_8006A528(phi_s0);
        phi_s0++;
    }
    if (phi_s1 & 0x1000) {
        D_800DFD94 = 1;
    }
    D_80123520++;
    if (D_80123520 >= 8) {
        func_8006DA28(0x1A, 0x27, 2);
    }
}

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
