/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C0170 */

#include "fade_transition.h"

#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "asset_sections.h"
#include "memory.h"

/************ .data ************/

s32 D_800E31A0 = 0;
s32 D_800E31A4 = 0;
s32 D_800E31A8 = 0;
s32 D_800E31AC = 0;
u16 D_800E31B0 = 0;
u16 D_800E31B4 = 0;
u16 D_800E31B8 = 0;
s8 D_800E31BC = 0;
s32 *D_800E31C0[2] = { NULL, NULL };
s32 *D_800E31C8[2] = { NULL, NULL };
s32 D_800E31D0[2] = { 0, 0 };

Gfx D_800E31D8[] = {
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

s16 D_800E3230[28] = {
    0xFE20, 0x0078, 0xFEC0, 0x0078, 0xFF60, 0x0078, 0x0000, 0x0078, 
    0x00A0, 0x0078, 0x0140, 0x0078, 0x01E0, 0x0078, 0xFE20, 0xFF88, 
    0xFEC0, 0xFF88, 0xFF60, 0xFF88, 0x0000, 0xFF88, 0x00A0, 0xFF88, 
    0x0140, 0xFF88, 0x01E0, 0xFF88
};

s16 D_800E3268[28] = {
    0xFF60, 0x0168, 0xFF60, 0x00F0, 0xFF60, 0x0078, 0xFF60, 0x0000, 
    0xFF60, 0xFF88, 0xFF60, 0xFF10, 0xFF60, 0xFF10, 0x00A0, 0x0168, 
    0x00A0, 0x00F0, 0x00A0, 0x0078, 0x00A0, 0x0000, 0x00A0, 0xFF88,
    0x00A0, 0xFF10, 0x00A0, 0xFF10
};

s8 D_800E32A0[12] = {
    0x00, 0x02, 0x04, 0x0E, 0x10, 0x12, 0x08, 0x0A,
    0x0C, 0x16, 0x18, 0x1A
};

s8 D_800E32AC[12] = {
    0x04, 0x06, 0x08, 0x12, 0x14, 0x16, 0x04, 0x06,
    0x08, 0x12, 0x14, 0x16
};

s8 D_800E32B8[24] = {
    0, 3, 1, 1, 3, 4, 1, 4, 
    2, 2, 4, 5, 6, 9, 7, 7, 
    9, 10, 7, 10, 8, 8, 10, 11
};

s8 D_800E32D0[12] = {
    -1, -1, 0, -1, -1, 0, 0, -1, -1, 0, -1, -1
};

s16 D_800E32DC[24] = {
    0xFCE0, 0x0078, 0xFE20, 0x0078, 0xFF60, 0x0078, 0x00A0, 0x0078, 
    0x01E0, 0x0078, 0x0320, 0x0078, 0xFCE0, 0xFF88, 0xFE20, 0xFF88, 
    0xFF60, 0xFF88, 0x00A0, 0xFF88, 0x01E0, 0xFF88, 0x0320, 0xFF88
};

s8 D_800E330C[12] = {
    0, 2, 4, 12, 14, 8, 10, 18, 20, 22, 0, 0
};

s8 D_800E3318[12] = {
    4, 6, 8, 16, 18, 4, 6, 14, 16, 18, 0, 0
};

s8 D_800E3324[20] = {
    0, 1, 3, 1, 3, 4, 1, 4, 2, 5, 7, 8, 5, 8, 6, 6, 8, 9, 0, 0
};

s8 D_800E3338[12] = {
    -1, -1, 0, -1, 0, 0, -1, 0, -1, -1, 0, 0
};

s16 D_800E3344[126] = {
    0xFF60, 0x00A0, 0xFF70, 0x00A0, 0xFF80, 0x00A0, 0xFF90, 0x00A0, 
    0xFFA0, 0x00A0, 0xFFB0, 0x00A0, 0xFFC0, 0x00A0, 0xFFD0, 0x00A0, 
    0xFFE0, 0x00A0, 0xFFF0, 0x00A0, 0x0000, 0x00A0, 0x0010, 0x00A0, 
    0x0020, 0x00A0, 0x0030, 0x00A0, 0x0040, 0x00A0, 0x0050, 0x00A0, 
    0x0060, 0x00A0, 0x0070, 0x00A0, 0x0080, 0x00A0, 0x0090, 0x00A0, 
    0x00A0, 0x00A0, 0xFF60, 0xFF38, 0xFF70, 0xFF60, 0xFF80, 0xFF74, 
    0xFF90, 0xFF7E, 0xFFA0, 0xFF74, 0xFFB0, 0xFF38, 0xFFC0, 0xFF10, 
    0xFFD0, 0xFEFC, 0xFFE0, 0xFEF2, 0xFFF0, 0xFEFC, 0x0000, 0xFF24, 
    0x0010, 0xFF2E, 0x0020, 0xFF38, 0x0030, 0xFF2E, 0x0040, 0xFF24, 
    0x0050, 0xFEFC, 0x0060, 0xFEF2, 0x0070, 0xFEFC, 0x0080, 0xFF24, 
    0x0090, 0xFF60, 0x00A0, 0xFF74, 0xFF60, 0xFEE8, 0xFF70, 0xFEE8, 
    0xFF80, 0xFEE8, 0xFF90, 0xFEE8, 0xFFA0, 0xFEE8, 0xFFB0, 0xFEE8, 
    0xFFC0, 0xFEE8, 0xFFD0, 0xFEE8, 0xFFE0, 0xFEE8, 0xFFF0, 0xFEE8, 
    0x0000, 0xFEE8, 0x0010, 0xFEE8, 0x0020, 0xFEE8, 0x0030, 0xFEE8, 
    0x0040, 0xFEE8, 0x0050, 0xFEE8, 0x0060, 0xFEE8, 0x0070, 0xFEE8, 
    0x0080, 0xFEE8, 0x0090, 0xFEE8, 0x00A0, 0xFEE8
};

s8 D_800E3440[92] = {
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 
    0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x0E, 
    0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1A, 0x1C, 
    0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x1A, 0x1C, 
    0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x00, 0x02, 
    0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x54, 0x56, 
    0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x0E, 0x10, 
    0x12, 0x14, 0x16, 0x18, 0x1A, 0x62, 0x64, 0x66, 
    0x68, 0x6A, 0x6C, 0x6E, 0x1A, 0x1C, 0x1E, 0x20, 
    0x22, 0x24, 0x26, 0x28, 0x6E, 0x70, 0x72, 0x74, 
    0x76, 0x78, 0x7A, 0x7C
};

s8 D_800E349C[92] = {
    0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 
    0x54, 0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 
    0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x42, 0x44, 0x62, 
    0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x44, 0x46, 
    0x48, 0x4A, 0x4C, 0x4E, 0x50, 0x52, 0x6E, 0x70, 
    0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x54, 0x56, 
    0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x54, 0x56, 
    0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x62, 0x64, 
    0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x62, 0x64, 0x66, 
    0x68, 0x6A, 0x6C, 0x6E, 0x6E, 0x70, 0x72, 0x74, 
    0x76, 0x78, 0x7A, 0x7C, 0x6E, 0x70, 0x72, 0x74, 
    0x76, 0x78, 0x7A, 0x7C
};

s8 D_800E34F8[92] = {
    0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, 
    0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, 0, 0, 
    0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

s8 D_800E3554[244] = {
    0, 8, 9, 0, 9, 1, 1, 9, 10, 1, 10, 2, 2, 10, 11, 2, 
    11, 3, 3, 11, 12, 3, 12, 4, 4, 12, 13, 4, 13, 5, 5, 13, 
    14, 5, 14, 6, 6, 14, 15, 6, 15, 7, 0, 7, 8, 0, 8, 1, 
    1, 8, 9, 1, 9, 2, 2, 9, 10, 2, 10, 3, 3, 10, 11, 3, 
    11, 4, 4, 11, 12, 4, 12, 5, 5, 12, 13, 5, 13, 6, 0, 8, 
    9, 0, 9, 1, 1, 9, 10, 1, 10, 2, 2, 10, 11, 2, 11, 3, 
    3, 11, 12, 3, 12, 4, 4, 12, 13, 4, 13, 5, 5, 13, 14, 5, 
    14, 6, 6, 14, 15, 6, 15, 7, 0, 8, 9, 0, 9, 1, 1, 9, 
    10, 1, 10, 2, 2, 10, 11, 2, 11, 3, 3, 11, 12, 3, 12, 4, 
    4, 12, 13, 4, 13, 5, 5, 13, 14, 5, 14, 6, 6, 14, 15, 6, 
    15, 7, 0, 7, 8, 0, 8, 1, 1, 8, 9, 1, 9, 2, 2, 9, 
    10, 2, 10, 3, 3, 10, 11, 3, 11, 4, 4, 11, 12, 4, 12, 5, 
    5, 12, 13, 5, 13, 6, 0, 8, 9, 0, 9, 1, 1, 9, 10, 1, 
    10, 2, 2, 10, 11, 2, 11, 3, 3, 11, 12, 3, 12, 4, 4, 12, 
    13, 4, 13, 5, 5, 13, 14, 5, 14, 6, 6, 14, 15, 6, 15, 7, 
    0, 0, 0, 0
};

Gfx D_800E3648[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsSPEndDisplayList(),
};

/*******************************/

/************ .bss ************/

s32 gCurFaceTransition;
u8 gCurFadeRed;
u8 gCurFadeGreen;
u8 gCurFadeBlue;
u8 gCurFadeAlpha;
s32 gLastFadeRed;
s32 gLastFadeGreen;
s32 gLastFadeBlue;
s32 D_8012A744;
s32 D_8012A748;
s32 D_8012A74C;
f32 D_8012A750;
f32 D_8012A754;
s32 D_8012A758;
s32 D_8012A75C;
s32 D_8012A760;
s32 D_8012A764;
s32 D_8012A768;
s32 D_8012A76C;
s32 D_8012A770;
s32 D_8012A774;
s32 D_8012A778;
s32 D_8012A77C;

/*****************************/

extern u32 osTvType;

void func_80067F20(f32 arg0);
void func_800C0724(void);
void func_800C0834(s32);
void render_fade_fullscreen(Gfx **dlist, s32 arg1, s32 arg2);
void func_800C1130(s32);
void render_fade_barndoor_horizontal(Gfx **dlist, s32 arg1, s32 arg2);
void render_fade_barndoor_vertical(Gfx **dlist, s32 arg1, s32 arg2);
void func_800C1EE8(s32);
void render_fade_circle(Gfx **dlist, s32 arg1, s32 arg2);
void render_fade_waves(Gfx **dlist, s32 arg1, s32 arg2);
void render_fade_barndoor_diagonal(Gfx **dlist, s32 arg1, s32 arg2);
void func_800C27A0(s32);
void render_fade_disabled(Gfx **dlist, s32 arg1, s32 arg2);
void func_800C0780(FadeTransition *transition);
void func_800C0B00(FadeTransition *transition, s32, s32, s16*, s8*, s8*, s8*, s8*, s8*);
void func_800C15D4(FadeTransition *transition);
void func_800C2640(FadeTransition *transition);
void func_800C0724(void);

void func_800C0170(void) {
    D_800E31A0 = 1;
}

void func_800C0180(void) {
    D_800E31A0 = 0;
}

#ifdef NON_MATCHING
// Regalloc issues. Uses v1 instead of v0.
s32 func_800C018C(void) {
    s32 phi_v0 = (D_800E31B0 != 0);
    if (phi_v0 == 0) {
        phi_v0 = (D_800E31B4 != 0);
        if (phi_v0 != 0) {
            phi_v0 = (D_800E31BC != 0);
        }
    }
    return phi_v0;
}
#else
GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C018C.s")
#endif

#ifdef NON_MATCHING

// Regalloc issue.
s32 func_800C01D8(FadeTransition *transition) {
    if (D_800E31A0) {
        return 0;
    }
    func_800C0724();
    if (transition == NULL) {
        return 0;
    }
    D_800E31B0 = transition->duration;
    D_800E31B8 = transition->duration;
    D_800E31B4 = transition->unk6;
    D_800E31BC = !(transition->type & 0x80);
    gCurFaceTransition = transition->type & 0x3F;
    D_800E31A8 = transition->type & 0x40;
    D_800E31A4 = 0;
    if (!D_800E31BC) {
        D_800E31A4 = 2;
    }
    if (D_800E31B0 > 0) {
        gLastFadeRed = gCurFadeRed;
        gLastFadeGreen = gCurFadeGreen;
        gLastFadeBlue = gCurFadeBlue;
        gCurFadeRed = transition->red;
        gCurFadeGreen = transition->green;
        gCurFadeBlue = transition->blue;
        switch (gCurFaceTransition) {
            case FADE_FULLSCREEN:
                func_800C0780(transition);
                break;
            case FADE_BARNDOOR_HORIZONTAL:
                func_800C0B00(transition, 0xC, 8, &D_800E3230, &D_800E32A0, &D_800E32AC, &D_800E32D0, &D_800E32D0, &D_800E32B8);
                break;
            case FADE_BARNDOOR_VERTICAL:
                func_800C0B00(transition, 0xC, 8, &D_800E3268, &D_800E32A0, &D_800E32AC, &D_800E32D0, &D_800E32D0, &D_800E32B8);
                break;
            case FADE_CIRCLE:
                func_800C15D4(transition);
                break;
            case FADE_WAVES:
                func_800C0B00(transition, 0x5C, 0x50, &D_800E3344, &D_800E349C, &D_800E3440, &D_800E34F8, &D_800E34F8, &D_800E3554);
                break;
            case FADE_BARNDOOR_DIAGONAL:
                func_800C0B00(transition, 0xA, 6, &D_800E32DC, &D_800E330C, &D_800E3318, &D_800E3338, &D_800E3338, &D_800E3324);
                break;
            case FADE_DISABLED:
                func_800C2640(transition);
                break;
        }
    }
    return D_800E31AC;
}
#else
GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C01D8.s")
#endif

s32 func_800C0494(s32 arg0) {
    if (D_800E31A4 != 0) {
        D_800E31A4 = D_800E31A4 - 1;
        arg0 = 0;
    } else if (arg0 >= 6) {
        arg0 = 5;
    }
    
    if (D_800E31AC != 0) {
        if (D_800E31B0 == 0) {
            D_800E31AC = -1;
        }
        if ((D_800E31B0 == 0) && (D_800E31B4 == 0)) {
            func_800C0724();
        } else {
            if (D_800E31B0 > 0) {
                D_800E31D0[0] = 1 - D_800E31D0[0];
            }
            switch (gCurFaceTransition) {
                case FADE_FULLSCREEN:
                    func_800C0834(arg0);
                    break;
                case FADE_BARNDOOR_HORIZONTAL:
                case FADE_BARNDOOR_VERTICAL:
                case FADE_WAVES:
                case FADE_BARNDOOR_DIAGONAL:
                    func_800C1130(arg0);
                    break;
                case FADE_CIRCLE:
                    func_800C1EE8(arg0);
                    break;
                case FADE_DISABLED:
                    func_800C27A0(arg0);
                    break;
            }
        }
    }
    return D_800E31AC;
}

void render_fade_transition(s32 dlist, s32 arg1, s32 arg2) {
    if (D_800E31AC != 0) {
        if (osTvType == 0) {
            func_80067F20(1.4f);
        } else {
            func_80067F20(1.2f);
        }
        func_80067F2C(dlist, arg1, arg2);
        func_80067F20(1.0f);
        switch (gCurFaceTransition) {
            case FADE_FULLSCREEN:
                render_fade_fullscreen(dlist, arg1, arg2);
                break;
            case FADE_BARNDOOR_HORIZONTAL:
                render_fade_barndoor_horizontal(dlist, arg1, arg2);
                break;
            case FADE_BARNDOOR_VERTICAL:
                render_fade_barndoor_vertical(dlist, arg1, arg2);
                break;
            case FADE_CIRCLE:
                render_fade_circle(dlist, arg1, arg2);
                break;
            case FADE_WAVES:
                render_fade_waves(dlist, arg1, arg2);
                break;
            case FADE_BARNDOOR_DIAGONAL:
                render_fade_barndoor_diagonal(dlist, arg1, arg2);
                break;
            case FADE_DISABLED:
                render_fade_disabled(dlist, arg1, arg2);
                break;
        }
        
        func_80066CDC(dlist, arg1);
    }
}

void func_800C0724(void) {
    if (D_800E31C0[0] != NULL) {
        free_from_memory_pool(D_800E31C0[0]);
        D_800E31C0[0] = NULL;
        D_800E31C0[1] = NULL;
        D_800E31C8[0] = NULL;
        D_800E31C8[1] = NULL;
    }
    D_800E31AC = 0;
    D_800E31D0[0] = 0;
}

void func_800C0780(FadeTransition *transition) {
    if (transition->type & 0x80) {
        D_8012A750 = 255.0f;
        D_8012A754 = -255.0f / (f32) D_800E31B0;
    } else {
        D_8012A750 = 0.0f;
        D_8012A754 = 255.0f / (f32) D_800E31B0;
    }
    D_800E31AC = 1;
}

GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C0834.s")

void render_fade_fullscreen(Gfx **dlist, s32 arg1, s32 arg2) {
    s32 screenSize = get_video_width_and_height_as_s32();
    gSPDisplayList((*dlist)++, D_800E31D8)
    gDPSetPrimColor((*dlist)++, 0, 0, gCurFadeRed, gCurFadeGreen, gCurFadeBlue, gCurFadeAlpha)
    gDPSetCombineMode((*dlist)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE)
    gDPFillRectangle((*dlist)++, 0, 0, screenSize & 0x3FF, (screenSize >> 16) & 0x3FF)
    func_8007B3D0(dlist);
}

GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C0B00.s")
GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C1130.s")

void render_fade_barndoor_horizontal(Gfx **dlist, s32 arg1, s32 arg2) {
    func_8007B3D0();
    gSPDisplayList((*dlist)++, D_800E3648)
    // TODO: Need to clean this up.
    gDkrVertices((*dlist)++, (s32)D_800E31C0[D_800E31D0[0]] + 0x80000000, (((s32)D_800E31C0[D_800E31D0[0]] + 0x80000000) & 6) | 0x58, 0x70)
    gDkrTriangles((*dlist)++, (s32)D_800E31C8[D_800E31D0[0]] + 0x80000000, 8, TRIN_DISABLE_TEXTURE)
    func_8007B3D0(dlist);
}

// This is exactly the same as render_fade_barndoor_horizontal; I wonder what gets changed then?
void render_fade_barndoor_vertical(Gfx **dlist, s32 arg1, s32 arg2) {
    func_8007B3D0();
    gSPDisplayList((*dlist)++, D_800E3648)
    // TODO: Need to clean this up.
    gDkrVertices((*dlist)++, (s32)D_800E31C0[D_800E31D0[0]] + 0x80000000, (((s32)D_800E31C0[D_800E31D0[0]] + 0x80000000) & 6) | 0x58, 0x70)
    gDkrTriangles((*dlist)++, (s32)D_800E31C8[D_800E31D0[0]] + 0x80000000, 8, TRIN_DISABLE_TEXTURE)
    func_8007B3D0(dlist);
}

GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C15D4.s")
GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C1EE8.s")

#ifdef NON_MATCHING
void render_fade_circle(Gfx **dlist, s32 arg1, s32 arg2) {
    u8 *addr, *addr2;
    func_8007B3D0();
    gSPDisplayList((*dlist)++, D_800E3648)
    addr  = (D_800E31C0[D_800E31D0[0]] + 0x80000000);
    addr2 = (D_800E31C8[D_800E31D0[0]] + 0x80000000);
    gDkrVertices((*dlist)++, (s32)addr, ((s32)addr & 6) | 0x88, 0xA6)
    gDkrTriangles((*dlist)++, (s32)addr2, 16, TRIN_DISABLE_TEXTURE)
    addr += 0xB4;
    addr2 += 0x100;
    gDkrVertices((*dlist)++, (s32)addr, ((s32)addr & 6) | 0x88, 0xA6)
    gDkrTriangles((*dlist)++, (s32)addr2, 16, TRIN_DISABLE_TEXTURE)
    addr += 0xB4;
    addr2 += 0x100;
    gDkrVertices((*dlist)++, (s32)addr, ((s32)addr & 6) | 0x88, 0xA6)
    gDkrTriangles((*dlist)++, (s32)addr2, 16, TRIN_DISABLE_TEXTURE)
    addr += 0xB4;
    addr2 += 0x100;
    gDkrVertices((*dlist)++, (s32)addr, ((s32)addr & 6) | 0x88, 0xA6)
    gDkrTriangles((*dlist)++, (s32)addr2, 16, TRIN_DISABLE_TEXTURE)
    func_8007B3D0(dlist);
}
#else
GLOBAL_ASM("asm/non_matchings/fade_transition/render_fade_circle.s")
#endif

#if 0 // This doesn't work properly.
void render_fade_waves(Gfx **dlist, s32 arg1, s32 arg2) {
    s32 i;
    func_8007B3D0();
    gSPDisplayList((*dlist)++, D_800E3648)
    for(i = 0; i < 6; i++) {
        s32 index = D_800E31D0[0] + i;
        if(i != 1 && i != 4) {
            gDkrVertices((*dlist)++, (s32)D_800E31C0[index] + 0x80000000, (((s32)D_800E31C0[index] + 0x80000000) & 6) | 0x78, 0x94)
            gDkrTriangles((*dlist)++, (s32)D_800E31C8[index] + 0x80000000, 14, TRIN_DISABLE_TEXTURE)
        } else {
            gDkrVertices((*dlist)++, (s32)D_800E31C0[index] + 0x80000000, (((s32)D_800E31C0[index] + 0x80000000) & 6) | 0x68, 0x82)
            gDkrTriangles((*dlist)++, (s32)D_800E31C8[index] + 0x80000000, 12, TRIN_DISABLE_TEXTURE)
        }
    }
    func_8007B3D0(dlist);
}
#else
GLOBAL_ASM("asm/non_matchings/fade_transition/render_fade_waves.s")
#endif

void render_fade_barndoor_diagonal(Gfx **dlist, s32 arg1, s32 arg2) {
    func_8007B3D0();
    gSPDisplayList((*dlist)++, D_800E3648)
    // TODO: Need to clean this up.
    gDkrVertices((*dlist)++, (s32)D_800E31C0[D_800E31D0[0]] + 0x80000000, (((s32)D_800E31C0[D_800E31D0[0]] + 0x80000000) & 6) | 0x48, 0x5E)
    gDkrTriangles((*dlist)++, (s32)D_800E31C8[D_800E31D0[0]] + 0x80000000, 6, TRIN_DISABLE_TEXTURE)
    func_8007B3D0(dlist);
}

GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C2640.s")

#ifdef NON_MATCHING
void func_800C27A0(s32 arg0) {
    //do {
        if (D_800E31B0 > 0) {
            gLastFadeRed += D_8012A744 * arg0;
            gLastFadeGreen += D_8012A748 * arg0;
            gLastFadeBlue += D_8012A74C * arg0;
            if (arg0 >= D_800E31B0) {
                gLastFadeRed = gCurFadeRed << 16;
                gLastFadeGreen = gCurFadeGreen << 16;
                gLastFadeBlue = gCurFadeBlue << 16;
                D_800E31B0 = 0;
                arg0 -= D_800E31B0;
            } else {
                D_800E31B0 -= arg0;
            }
        } else {
            D_800E31B4 -= arg0;
            if (D_800E31B4 != 0xFFFF) {
                if ((D_800E31B4 & 0xFFFF) <= 0) {
                    D_800E31B4 = 0;
                }
            }
        }
    //} while(1 == 0);
}
#else
GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C27A0.s")
#endif

void render_fade_disabled(Gfx **dlist, s32 arg1, s32 arg2) {
    s32 screenSize = get_video_width_and_height_as_s32();
    gSPDisplayList((*dlist)++, D_800E31D8)
    gDPSetPrimColor((*dlist)++, 0, 0, (gLastFadeRed >> 16), (gLastFadeGreen >> 16), (gLastFadeBlue >> 16), 255)
    gDPSetCombineMode((*dlist)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE)
    gDPFillRectangle((*dlist)++, 0, 0, screenSize & 0x3FF, (screenSize >> 16) & 0x3FF)
    func_8007B3D0(dlist);
}
