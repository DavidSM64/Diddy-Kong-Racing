/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800AB1F0 */

#include "unknown_0ABDF0.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "PR/libultra.h"
#include "camera.h"
#include "unknown_0255E0.h"
#include "unknown_008C40.h"

/************ .data ************/

unk800E2850 D_800E2850[3] = {
    { 0,  0x40, 0, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
    { 0, 0x100, 1, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
    { 0,  0x08, 2, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
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

unk800E2980 D_800E2980[2] = {
    { 1, 0xFFFF, 0xC090, 3.0f, 0.0f },
    { 0,      0,      0, 0.0f, 0.0f },
};

unk800E2980 D_800E29A0[4] = {
    { 3, 0xFFFF, 0x0090, 0.75f,  -32.0f },
    { 2, 0x0050, 0xFF60,  0.8f,  -96.0f },
    { 2, 0x00FF, 0x0090, 0.75f, -192.0f },
    { 0,      0,      0,  0.0f,    0.0f },
};

unk800E2980 D_800E29E0[5] = {
    { 3, 0xFF80, 0x1490, 0.65f,  -64.0f },
    { 2, 0xFFFF, 0xFF90,  1.0f, -128.0f },
    { 3, 0xFFFF, 0x8090,  0.5f, -176.0f },
    { 3, 0xFF28, 0x2890, 0.75f, -224.0f },
    { 0,      0,      0,  0.0f,    0.0f },
};

unk800E2980 D_800E2A30[5] = {
    { 3, 0xFF80, 0xFF80,  0.5f,  -64.0f },
    { 1, 0xFFFF, 0xC090, 0.75f, -128.0f },
    { 2, 0xFF28, 0x0080,  0.6f, -176.0f },
    { 1, 0xFFC0, 0xFF90, 0.75f, -224.0f },
    { 0,      0,      0,  0.0f,    0.0f },
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

Vertex D_800E2AAC[16] = {
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
};

unk800E2B4C D_800E2B4C[8] = {
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};

unk800E2C2C D_800E2C2C[2] = {
    { 0, 0, 0x400, 0x400, 0x000A, 0xFFC4, NULL, 0x80, 0xFF, 0xFF, 0x80, 0x80, 0xFF, 0x80, 0x00 },
    { 0, 0, 0x600, 0x600, 0x0020, 0xFF40, NULL, 0xFF, 0xFF, 0xFF, 0x00, 0x80, 0xFF, 0xFF, 0x00 }
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
Sprite *D_800E2C8C = 0;
s32 D_800E2C90 = 0;
s32 D_800E2C94 = 0;


FadeTransition D_800E2C98 = FADE_TRANSITION(0x40, FADE_COLOR_WHITE, 5, 2);

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
Gfx *D_80127C0C;
s32 D_80127C10;
s32 D_80127C14;
Triangle *D_80127C18;
Object *D_80127C1C;
s32 D_80127C20;
s32 D_80127C24;
s32 D_80127C28;
s32 D_80127C2C;
s32 D_80127C30[4];
Object *D_80127C40[16];

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

void func_800ACF60(Object *arg0) {
    if (D_800E2A88 < 0x10) {
        D_80127C40[D_800E2A88] = arg0;
        D_800E2A88++;
    }
}

void func_800ACF98(Object* arg0) {
    s32 i;
    s32 isFound = FALSE;

    for (i = 0; i < D_800E2A88 && !isFound; i++) {
        if (D_80127C40[i] == arg0) {
            isFound = TRUE;
        }
    }

    if (isFound) {
        D_800E2A88--;
        i--;
        for (; i < D_800E2A88; i++) {
            D_80127C40[i] = D_80127C40[i + 1];
        }
    }

}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD030.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD144.s")

void func_800AD220(void) {
    if (D_800E2C2C[0].tex != NULL) {
        free_texture(D_800E2C2C[0].tex);
        D_800E2C88 = 0;
    }

    if (D_800E2C2C[1].tex != NULL) {
        free_texture(D_800E2C2C[1].tex);
        D_800E2C88 = 0;
    }

    if (D_800E2C8C != NULL) {
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
    D_800E2C78 = osTvType == TV_TYPE_PAL ? 50.0 * arg2 : 60.0 * arg2;
    D_800E2C68 = arg0;
    D_800E2C64 = (D_800E2C68 - D_800E2C60) / D_800E2C78;
    D_800E2C74 = arg1;
    D_800E2C70 = (D_800E2C74 - D_800E2C6C) / D_800E2C78;
}

void func_800AD40C(void) {
    s32 a, b;
    if (D_800E2C5C && !get_viewport_count()) {
        a = ((D_800E2C60 * -38) >> 16) + 0x3FA;
        b = ((D_800E2C60 * -20) >> 16) + 0x3FF;
        func_80030664(0, a, b, 0x1CU, 0xFU, 0x24U);
    }
}

// Unused.
void func_800AD4AC(s32 arg0) {
    D_800E2C6C = arg0;
}

void func_800AD4B8(s32 arg0) {
    s32 i;

    if ((get_viewport_count() == 0) && (D_800E2C5C != 0)) {
        if (D_800E2C78 > 0) {
            if (arg0 < D_800E2C78) {
                D_800E2C78 -= arg0;
                D_800E2C60 += D_800E2C64 * arg0;
                D_800E2C6C += D_800E2C70 * arg0;
            } else {
                D_800E2C78 = 0;
                D_800E2C60 = D_800E2C68;
                D_800E2C6C = D_800E2C74;
            }
        }
        func_800ADBC8(arg0);
        func_800AD658(arg0);
        func_800ADAB8(arg0);
        if (D_800E2C60 >= 256) {
            func_80067F2C(&D_80127C0C, &D_80127C10);
            for(i = 0; i < 2; i++) {
                func_800ADCBC(&D_800E2C2C[i], arg0);
            }
            gDPSetPrimColor(D_80127C0C++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(D_80127C0C++, 255, 255, 255, 0);
            func_8007B3D0(&D_80127C0C);
            func_800682AC(&D_80127C0C);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD658.s")

void func_800ADAB8(s32 arg0) {
    if (D_800E2C80 > 0) {
        D_800E2C80 -= arg0;
        if (D_800E2C80 <= 0) {
            if (D_800E2C6C >= 32769 && func_800C018C() == 0) {
                func_800C01D8(&D_800E2C98);
            }
            func_80001D04(39, 0);
            D_800E2C80 = 0;
        }
    } else if (D_800E2C60 >= 48000) {
        if (D_800E2C7C > 0) {
            D_800E2C7C -= arg0;
            return;
        }
        func_80001D04(575, 0);
        D_800E2C80 = 600 - ((s32) (D_800E2C60 + -48000) >> 5);
        D_800E2C7C = get_random_number_from_range(900, 1140) - ((s32) (D_800E2C60 + -48000) >> 5);
    }
}

void func_800ADBC8(UNUSED s32 arg0) {
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 sp28;
    f32 sp24;
    f32 temp_f2;

    sp28 = 1152.0f - (f32) (D_800E2C60 >> 6);
    sp24 = func_800707C4(D_80127C1C->y_rotation) * sp28;
    temp_f2 = func_800707F8(D_80127C1C->y_rotation) * sp28;
    temp_f14 = D_80127C1C->x_position + (temp_f2 - sp24);
    temp_f16 = D_80127C1C->y_position;
    temp_f18 = D_80127C1C->z_position + (-temp_f2 - sp24);
    if (D_800E2C94 != 0) {
        func_800096D8(D_800E2C94, temp_f14, temp_f16, temp_f18);
    } else {
        func_80009558(574, temp_f14, temp_f16, temp_f18, 1, &D_800E2C94);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADCBC.s")
