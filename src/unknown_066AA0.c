/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065EA0 */

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "fast3d.h"

extern u32 osTvType;

/************ .rodata ************/

const char D_800E6F00[] = "Camera Error: Illegal mode!\n";
const char D_800E6F20[] = "Camera Error: Illegal player no!\n";
const char D_800E6F34[] = "cameraPushSprMtx: model stack overflow!!\n";
const char D_800E6F70[] = "\nCam do 2D sprite called with NULL pointer!";
const char D_800E6F9C[] = "CamDo2DSprite FrameNo Overflow !!!\n";
const char D_800E6FC0[] = "cameraPushModelMtx: model stack overflow!!\n";
const char D_800E6FEC[] = "camPushModelMtx: bsp stack overflow!!\n";
const char D_800E7010[] = "camPopModelMtx: model stack negative overflow!!\n";
const char D_800E7048[] = "camPopModelMtx: bsp stack negative overflow!!\n";

/*********************************/

/************ .data ************/

s32 D_800DD060 = 0; // Currently unknown, might be a different type.

/* Size: 0x34 bytes. */
typedef struct unk800DD064 {
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
} unk800DD064;

unk800DD064 D_800DD064[4] = {
    { 
        0x00, 0x00, 0x140, 0xF0,
        0xA0, 0x78, 0x140, 0xF0,
        0x00, 0x00, 0x13F, 0xEF, 0x00
    },
    { 
        0x00, 0x00, 0x140, 0xF0,
        0xA0, 0x78, 0x140, 0xF0,
        0x00, 0x00, 0x13F, 0xEF, 0x00
    },
    { 
        0x00, 0x00, 0x140, 0xF0,
        0xA0, 0x78, 0x140, 0xF0,
        0x00, 0x00, 0x13F, 0xEF, 0x00
    },
    { 
        0x00, 0x00, 0x140, 0xF0,
        0xA0, 0x78, 0x140, 0xF0,
        0x00, 0x00, 0x13F, 0xEF, 0x00
    }
};

// Not sure about the typing here
s16 D_800DD134[10] = { 
    0, 0, 0, 0, 
    0, -1, -1, 0,
    0, 0
};

// Not sure about the typing here
u16 D_800DD148[160] = {
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0,
    0, 0, 0x01FF, 0
};

f32 D_800DD288[6] = {  
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -281.0f
};

f32 D_800DD2A0[6] = {  
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f
};

f32 D_800DD2B8[5] = {  
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f
};

f32 D_800DD2CC[11] = {
    1.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 160.0f
};

u8 D_800DD2F8[8] = {
    0, 0, 0, 0, 0, 0, 0, 0
};

s32 D_800DD300 = 0; // Currently unknown, might be a different type.

s16 D_800DD304 = -1;

/*******************************/

/************ .bss ************/

/* Size: 0x44 bytes, might just be Object? */
typedef struct unk80120AC0 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8  pad6[6];
    f32 x_position;
    f32 y_position;
    f32 z_position;
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

unk80120AC0 D_80120AC0[8];
s32 D_80120CE0;
s32 D_80120CE4;
s32 D_80120CE8;
s32 D_80120CEC;
s32 D_80120CF0[6];
s32 D_80120D08;
s32 D_80120D0C;
f32 D_80120D10;
s8  D_80120D14;
u8  D_80120D15;
s32 D_80120D18;
s32 D_80120D1C;
s32 D_80120D20[2];
s32 D_80120D28[6];
s32 D_80120D40[6];
s32 D_80120D58[6];
s32 D_80120D70[6];
s32 D_80120D88[6];
s32 D_80120DA0[80];
s32 D_80120EE0[16];
s32 D_80120F20[16];
s32 D_80120F60[16];
s32 D_80120FA0[16];
s32 D_80120FE0[16];
s32 D_80121020[16];
s32 D_80121060[16];
s32 D_801210A0[16];
s32 D_801210E0[6];
s32 D_801210F8;
s32 D_801210FC;
u8 D_80121100[16];

/* Size: 6 bytes */
typedef struct unk80121110 {
    u16 unk0;
    s8 unk2;
    s8 unk3;
    s8 unk4;
    s8 unk6;
} unk80121110;
unk80121110 D_80121110[8];
u16 D_80121140[4];
u16 D_80121148[4];
u8 D_80121150[16];

/******************************/

extern s32 D_A4000000;
extern s32 SP_IMEM;

unk80120AC0 *func_80069D20(void);
void func_800014BC(f32 arg0);
s8* get_misc_asset(s32 arg0);
s32 func_8006A624(s8 arg0);
void func_8006F64C(s32*, f32, f32, f32, f32*, f32*, f32*);
void guPerspectiveF(s32*, s32*, f32, f32, f32, f32, f32);
void func_8006F870(s32*, s32*);
s16 func_80029F18(f32, f32, f32);    
void func_8006A50C(void);
void func_800665E8(s32 arg0);
void load_level_2(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8006C164(void);
void func_8000E194(void);
f32 sqrtf(f32);
void osSetTime(u64);
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
        guPerspectiveF(&D_80120EE0, &D_80120D58[5], arg0, 1.33333333f, 10.0f, 15000.0f, 1.0f);
        func_8006F870(&D_80120EE0, &D_80120FE0);
    }
}

void func_80066194(void) {
    guPerspectiveF(&D_80120EE0, &D_80120D58[5], 60.0f, 1.33333333f, 10.0f, 15000.0f, 1.0f);
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
    sp20 = someStruct->x_position;
    sp1C = someStruct->y_position;
    sp18 = someStruct->z_position;
    sp24 = someStruct->unk38;
    someStruct->unk4 = 0;
    someStruct->unk2 = 0;
    someStruct->unk0 = -0x8000;
    someStruct->unk38 = 0;
    someStruct->x_position = 0.0f;
    someStruct->y_position = 0.0f;
    someStruct->z_position = 0.0f;
    func_8001D5E0(0.0f, 0.0f, -1.0f);
    func_80066CDC(arg0, arg1);
    someStruct->unk38 = sp24;
    someStruct->unk0 = sp2A;
    someStruct->unk2 = sp28;
    someStruct->unk4 = sp26;
    someStruct->x_position = sp20;
    someStruct->y_position = sp1C;
    someStruct->z_position = sp18;
}

f32 func_80066348(f32 arg0, f32 arg1, f32 arg2) {
    s32 phi_v1;
    f32 temp_f2, temp_f0, temp_f14;

    phi_v1 = D_80120CE4;
    
    if (D_80120D14 != 0) {
        phi_v1 += 4;
    }
    
    temp_f0 = arg2 - D_80120AC0[phi_v1].z_position;
    temp_f2 = arg0 - D_80120AC0[phi_v1].x_position;
    temp_f14 = arg1 - D_80120AC0[phi_v1].y_position;
    return sqrtf((temp_f0 * temp_f0) + ((temp_f2 * temp_f2) + (temp_f14 * temp_f14)));
}

void func_800663DC(s32 x_pos, s32 y_pos, s32 z_pos, s32 arg3, s32 arg4, s32 arg5) {
    D_80120AC0[D_80120CE4].unk4 = (s16) (arg3 * 0xB6);
    D_80120AC0[D_80120CE4].x_position = (f32) x_pos;
    D_80120AC0[D_80120CE4].y_position = (f32) y_pos;
    D_80120AC0[D_80120CE4].z_position = (f32) z_pos;
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
    D_80120AC0[arg0].x_position = arg1;
    D_80120AC0[arg0].y_position = arg2;
    D_80120AC0[arg0].z_position = arg3;
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
    return D_800DD064[arg0].unk30 & 0x1;
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
    D_800DD2CC[0] = arg0;
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
        return &D_80120AC0[4];
    }
    return &D_80120AC0[0];
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
        temp_f0 = arg0 - D_80120AC0[i].x_position;
        temp_f2 = arg1 - D_80120AC0[i].y_position;
        temp_f14 = arg2 - D_80120AC0[i].z_position;
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
extern u8 D_80121100+3;   

// Has regalloc & stack issues.
s32 func_8006A10C(void) {
    u8 sp23;
    osCreateMesgQueue(&D_801210E0, &D_801210F8, 1);
    osSetEventMesg(5, &D_801210E0, D_801210FC);
    func_800CCC20(&D_801210E0, &sp23, &D_80121100);
    func_800CCFE0(&D_801210E0);
    func_8006A434();
    D_800DD300 = 0;
    if ((sp23 & 1) && !(D_80121100+3 & 8)) {
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

u16 get_button_inputs_from_player(s32 arg0) {
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

void func_8006A6A0(void) {
    D_800DD304 = 0;
}
