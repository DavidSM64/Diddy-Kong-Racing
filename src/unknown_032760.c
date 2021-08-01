/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031B60 */

#include "unknown_032760.h"

#include "types.h"
#include "macros.h"

/************ .data ************/

TextureHeader **D_800DC950 = NULL;
s32 D_800DC954 = 0;
s32 D_800DC958 = 0;
s32 D_800DC95C = 0;
s32 D_800DC960 = 0;
s32 D_800DC964 = 0;
s32 D_800DC968 = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

f32 D_8011D4C0;
f32 D_8011D4C4;
f32 D_8011D4C8;
f32 D_8011D4CC;

/*******************************/

void func_80031B60(void) {
    if (D_800DC950 != 0) {
        free_from_memory_pool(D_800DC950);
        D_800DC950 = 0;
        D_800DC954 = 0;
        D_800DC960 = 0;
        D_800DC964 = 0;
    }
    D_800DC95C = 0;
    D_800DC958 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031BB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031CAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031F88.s")

void func_80032398(s32 arg0) {
    s32 i;
    for (i = 0; i < D_800DC95C; i++) {
        func_80032424(D_800DC950[i], arg0);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032424.s")

void func_80032BAC(TextureHeader *texInput) {
    TextureHeader *tex = NULL;
    s32 i;
    for(i = 0; (i < D_800DC95C) && (tex == NULL); i++) {
        if (texInput == D_800DC950[i]) {
            tex = D_800DC950[i];
        }
    }
    if (tex != NULL) {
        D_800DC95C--;
        for (i--; i < D_800DC95C; i++) {
            D_800DC950[i] = D_800DC950[i + 1];
        }
        D_800DC950[D_800DC95C] = tex;
    }
}

s32 func_80032C6C(void) {
    return D_800DC95C;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032C7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800337E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033A14.s")

typedef struct unk80033C08 {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} unk80033C08;

f32 sqrtf(f32);

f32 func_80033C08(unk80033C08 *arg0) {
    f32 temp_f2;
    f32 phi_f12;

    phi_f12 = D_8011D4C0;
    if (phi_f12 > 0.0f) {
        temp_f2 = 1.0f / sqrtf(phi_f12);
        phi_f12 = (D_8011D4C4 * temp_f2 * arg0->unk7C) + (D_8011D4C8 * temp_f2 * arg0->unk80) + (D_8011D4CC * temp_f2 * arg0->unk84);
        if (phi_f12 < 0.0f) {
            phi_f12 = 0.0f;
        }
    } else {
        phi_f12 = 1.0f;
    }
    return phi_f12;
}
