/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A310 */

#include "unknown_07AF10.h"

#include "types.h"
#include "macros.h"

/************ .data ************/

s32 D_800DE770 = 0;
s32 D_800DE774 = 0; // Currently unknown, might be a different type.
s8  D_800DE778 = 2;

// Video mode resolutions
unk800DE77C D_800DE77C[8] = {
    { 320, 240 },
    { 320, 240 },
    { 640, 240 },
    { 640, 240 },
    { 640, 480 },
    { 640, 480 },
    { 640, 480 },
    { 640, 480 }
};

s32 D_800DE7BC = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .rodata ************/

const char D_800E7990[] = "320 by 240 Point sampled, Non interlaced.\n";
const char D_800E79BC[] = "320 by 240 Anti-aliased, Non interlaced.\n";
const char D_800E79EC[] = "640 by 240 Point sampled, Non interlaced.\n";
const char D_800E7A10[] = "640 by 240 Anti-aliased, Non interlaced.\n";
const char D_800E7A40[] = "640 by 480 Point sampled, Interlaced.\n";
const char D_800E7A68[] = "640 by 480 Anti-aliased, Interlaced.\n";
const char D_800E7A90[] = "640 by 480 Point sampled, Interlaced, De-flickered.\n";
const char D_800E7AC8[] = "640 by 480 Anti-aliased, Interlaced, De-flickered.\n";

/*********************************/

/************ .bss ************/

s32 D_80126170;
s32 D_80126174;
s32 D_80126178[2];
s32 D_80126180[8];
s32 D_801261A0[48];
s32 D_80126260[20];
s32 D_801262B0[2];
s32 D_801262B8[2];
s32 D_801262C0[2];
s32 D_801262C8;
s32 D_801262CC;
s32 D_801262D0;
s32 D_801262D4;
s32 D_801262D8;
s32 D_801262DC;
s32 D_801262E0;
s8 D_801262E4;
s32 D_801262E8[8];
s8  D_80126308;
u8  D_80126309;
s32 D_8012630C;
s32 D_80126310;

/******************************/

GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007A310.s")

void func_8007A4C0(s32 arg0) {
    D_801262CC = arg0;
}

/* Unused? */
s32 func_8007A4CC(void) {
    return D_801262CC;
}

/* Unused? */
void func_8007A4DC(s32 arg0) {
    D_801262B0[arg0] = D_800DE77C[D_801262CC & 0x07].width;
    D_801262B8[arg0] = D_800DE77C[D_801262CC & 0x07].height;
}

s32 func_8007A520(void) {
    return (D_801262B8[D_801262C8] << 16) | D_801262B0[D_801262C8];
}

#if 0
void func_8007A550(void) {
    s32 temp_t2;
    s32 temp_t4;
    s32 phi_v1;
    ? *phi_a0;
    ? *phi_a0_2;
    ? *phi_a0_3;

    if (osTvType == 0) {
        phi_v1 = 0xE;
    } else {
        phi_v1 = 0;
        if (osTvType == 2) {
            phi_v1 = 0x1C;
        }
    }
    switch(D_801262CC & 7) {
        case 0:
            osViSetMode((phi_v1 * 0x50) + &D_800E3900, 2);
            break;
        case 1:
            if (osTvType == 0) {
                phi_a0 = &D_800E4670;
            } else {
                phi_a0 = &D_800E4620;
                if (2 == osTvType) {
                    phi_a0 = &D_800E46C0;
                }
            }
            memory_copy(phi_a0, &D_80126260, 0x50);
            if (osTvType == 0) {
                temp_t2 = D_80126260.unk30 - 0x180000;
                temp_t4 = D_80126260.unk44 - 0x180000;
                D_80126260.unk30 = temp_t2;
                D_80126260.unk44 = temp_t4;
                D_80126260.unk30 = temp_t2 + 0x18;
                D_80126260.unk44 = temp_t4 + 0x18;
            }
            osViSetMode(&D_80126260, &D_80126260);
            break;
        case 2:
            if (osTvType == 0) {
                phi_a0_2 = &D_800E4670;
            } else {
                phi_a0_2 = &D_800E4620;
                if (2 == osTvType) {
                    phi_a0_2 = &D_800E46C0;
                }
            }
            memory_copy(phi_a0_2, &D_80126260, 0x50);
            D_80126260.unk8 = 0x280;
            D_80126260.unk20 = 0x400;
            D_80126260.unk28 = 0x500;
            D_80126260.unk3C = 0x500;
            osViSetMode(&D_80126260, &D_80126260);
            break;
        case 3:
            if (osTvType == 0) {
                phi_a0_3 = &D_800E4760;
            } else {
                phi_a0_3 = &D_800E4710;
                if (2 == osTvType) {
                    phi_a0_3 = &D_800E47B0;
                }
            }
            memory_copy(phi_a0_3, &D_80126260, 0x50);
            D_80126260.unk8 = 0x280;
            D_80126260.unk20 = 0x400;
            D_80126260.unk28 = 0x500;
            D_80126260.unk3C = 0x500;
            osViSetMode(&D_80126260, &D_80126260);
            break;
        case 4:
            osViSetMode((phi_v1 * 0x50) + 0x280 + &D_800E3900, 2);
            break;
        case 5:
            osViSetMode((phi_v1 * 0x50) + 0x320 + &D_800E3900, 2);
            break;
        case 6:
            osViSetMode((phi_v1 * 0x50) + 0x2D0 + &D_800E3900, 2);
            break;
        case 7:
            osViSetMode((phi_v1 * 0x50) + 0x370 + &D_800E3900, 2);
            break;
    }
    osViSetSpecialFeatures(0x10);
    osViSetSpecialFeatures(0x40);
    osViSetSpecialFeatures(2);
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007A550.s")
#endif



GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007A7E8.s")

void func_8007A974(void) {
    D_80126308 = 0;
    D_80126309 = 2;
}

GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007A98C.s")

void func_8007AB24(s8 arg0) {
    D_801262E4 = arg0;
}

// Unused?
s32 func_8007AB34(void) {
    return (s32)((f32)D_80126170 / (f32)D_80126309);
}

GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007AB9C.s")

#ifdef NON_MATCHING
// regalloc issues
// They made their own worse version of memcpy, despite the fact that they already had bcopy?
void memory_copy(u8 *src, u8 *dst, s32 numBytes) {
    s32 i;
    for(i = 0; i < numBytes; i++){
        dst[i] = src[i];
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_07AF10/memory_copy.s")
#endif


