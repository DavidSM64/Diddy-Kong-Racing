/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800AB1F0 */

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"

typedef struct {
    s16 unk0;
    s16 unk2;
} unk80127BF8;

extern u32 osTvType;

/************ .data ************/

/* Size: 0x2C Bytes */
typedef struct unk800E2850 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
} unk800E2850;

unk800E2850 D_800E2850[3] = {
    { 0,  0x40, 0, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
    { 0, 0x100, 1, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
    { 0,  0x08, 2, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 }
};

s32 D_800E28D4 = 0;

unk800E2850 D_800E28D8 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Not sure about typing for the following.
s32 D_800E2904 = 0;
s32 D_800E2908 = 0;
s32 D_800E290C = 0;
s32 D_800E2910 = 0;
s32 D_800E2914[2] = { 0, 0 };
s32 D_800E291C = 0;
s32 D_800E2920[2] = { 0, 0 };

Gfx D_800E2928[] = {
    gsDPPipeSync(), 
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP), 
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT), 
    gsDPSetAlphaCompare(G_AC_NONE), 
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsSPEndDisplayList(),
};

/* Size: 0x10 Bytes */
typedef struct unk800E2980 {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    f32 unk8;
    f32 unkC;
} unk800E2980;

unk800E2980 D_800E2980[2] = {
    { 1, 0xFFFF, 0xC090, 3.0f, 0.0f },
    { 0,      0,      0, 0.0f, 0.0f }
};

unk800E2980 D_800E29A0[4] = {
    { 3, 0xFFFF, 0x0090, 0.75f,  -32.0f },
    { 2, 0x0050, 0xFF60,  0.8f,  -96.0f },
    { 2, 0x00FF, 0x0090, 0.75f, -192.0f },
    { 0,      0,      0,  0.0f,    0.0f }
};

unk800E2980 D_800E29E0[5] = {
    { 3, 0xFF80, 0x1490, 0.65f,  -64.0f },
    { 2, 0xFFFF, 0xFF90,  1.0f, -128.0f },
    { 3, 0xFFFF, 0x8090,  0.5f, -176.0f },
    { 3, 0xFF28, 0x2890, 0.75f, -224.0f },
    { 0,      0,      0,  0.0f,    0.0f }
};

unk800E2980 D_800E2A30[5] = {
    { 3, 0xFF80, 0xFF80,  0.5f,  -64.0f },
    { 1, 0xFFFF, 0xC090, 0.75f, -128.0f },
    { 2, 0xFF28, 0x0080,  0.6f, -176.0f },
    { 1, 0xFFC0, 0xFF90, 0.75f, -224.0f },
    { 0,      0,      0,  0.0f,    0.0f }
};

s32 D_800E2A80 = 0;
s32 D_800E2A84 = 1;
s32 D_800E2A88 = 0;
f32 D_800E2A8C = -200.0f;
f32 D_800E2A90 = 200.0f;
f32 D_800E2A94 = 200.0f;
f32 D_800E2A98 = 200.0f;
f32 D_800E2A9C = 200.0f;
f32 D_800E2AA0 = -200.0f;
f32 D_800E2AA4 = -200.0f;
f32 D_800E2AA8 = -200.0f;

s16 D_800E2AAC[80] = {
    0, 0, 0, -1, -1, 0, 0, 0, 
    -1, -1, 0, 0, 0, -1, -1, 0, 
    0, 0, -1, -1, 0, 0, 0, -1, 
    -1, 0, 0, 0, -1, -1, 0, 0, 
    0, -1, -1, 0, 0, 0, -1, -1, 
    0, 0, 0, -1, -1, 0, 0, 0, 
    -1, -1, 0, 0, 0, -1, -1, 0, 
    0, 0, -1, -1, 0, 0, 0, -1, 
    -1, 0, 0, 0, -1, -1, 0, 0, 
    0, -1, -1, 0, 0, 0, -1, -1
};

/* Size: 0x1C Bytes */
typedef struct unk800E2B4C {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
} unk800E2B4C;

unk800E2B4C D_800E2B4C[8] = {
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 }
};

/* Size: 0x18 Bytes */
typedef struct unk800E2C2C {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} unk800E2C2C;

unk800E2C2C D_800E2C2C[2] = {
    { 0, 0x400, 0x400, 0x000AFFC4, 0, 0x80FF, 0xFF80, 0x80FF, 0x8000 },
    { 0, 0x600, 0x600, 0x0020FF40, 0, 0xFFFF, 0xFF00, 0x80FF, 0xFF00 }
};

s32 D_800E2C5C = 0;
s32 D_800E2C60 = 0x00010000;
s32 D_800E2C64 = 0;
s32 D_800E2C68 = 0x00010000;
s32 D_800E2C6C = 0x00010000;
s32 D_800E2C70 = 0;
s32 D_800E2C74 = 0x00010000;
s32 D_800E2C78 = 0;
s32 D_800E2C7C = 0;
s32 D_800E2C80 = 0;
s32 D_800E2C84 = 0;
s32 D_800E2C88 = 0;
s32 D_800E2C8C = 0;
s32 D_800E2C90 = 0;
s32 D_800E2C94 = 0;

s16 D_800E2C98[4] = {
    0x40FF, 0xFFFF, 0x0005, 0x0002
};

/*******************************/

/************ .bss ************/

s32 D_80127BB0;
s32 D_80127BB4;
s32 D_80127BB8[16];
unk80127BF8 D_80127BF8;
s32 D_80127BFC;
s32 D_80127C00;
s32 D_80127C04;
s32 D_80127C08;
s32 D_80127C0C;
s32 D_80127C10;
s32 D_80127C14;
s32 D_80127C18;
s16 *D_80127C1C;
s32 D_80127C20;
s32 D_80127C24;
s32 D_80127C28;
s32 D_80127C2C;
s32 D_80127C30[4];
s32 D_80127C40[16];

/******************************/

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

void func_800ACF60(s32 arg0) {
    if (D_800E2A88 < 0x10) {
        D_80127C40[D_800E2A88] = arg0;
        D_800E2A88++;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ACF98.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD030.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD144.s")

void func_800AD220(void) {
    if (D_800E2C2C[0].unkC != 0) {
        free_texture(D_800E2C2C[0].unkC);
        D_800E2C88 = 0;
    }

    if (D_800E2C2C[1].unkC != 0) {
        free_texture(D_800E2C2C[1].unkC);
        D_800E2C88 = 0;
    }

    if (D_800E2C8C != 0) {
        free_sprite(D_800E2C8C);
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

#ifdef NON_MATCHING
void func_800AD40C(void) {
    s16 a, b;
    if (D_800E2C5C && !get_viewport_count()) {
        a = ((-D_800E2C60 * 38) >> 16) + 1018;
        b = ((-D_800E2C60 * 20) >> 16) + 1023;
        func_80030664(0, a, b, 28, 15, 36);
    }
}

// Unused.
void func_800AD4AC(s32 arg0) {
    D_800E2C6C = arg0;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD40C.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD4B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD658.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADAB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADBC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADCBC.s")
