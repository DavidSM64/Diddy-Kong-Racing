/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A310 */

#include "types.h"
#include "macros.h"

/************ .data ************/

s32 D_800DE770 = 0;
s32 D_800DE774 = 0; // Currently unknown, might be a different type.
s8  D_800DE778 = 2;

/* Size: 0x08 bytes */
typedef struct unk800DE77C {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
} unk800DE77C;

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
s32 D_801262E4;
s32 D_801262E8[8];
s8  D_80126308;
s8  D_80126309;
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

GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007A550.s")
GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007A7E8.s")

void func_8007A974(void) {
    D_80126308 = 0;
    D_80126309 = 2;
}

GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007A98C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007AB24.s")
GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007AB9C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07AF10/func_8007ABFC.s")
