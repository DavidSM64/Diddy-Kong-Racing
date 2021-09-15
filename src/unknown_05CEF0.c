/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005C2F0 */

#include "unknown_05CEF0.h"

#include "structs.h"
#include "types.h"
#include "macros.h"
#include "audio.h"
#include "unknown_00BC20.h"
#include "unknown_005740.h"
#include "unknown_008C40.h"

/************ .data ************/

s16 D_800DCDE0[16] = {
    0x022B, 0x00A3, 0x00A4, 0x00B3,
    0x00B4, 0x00F0, 0x00F1, 0x00F6, 
    0x00F7, 0x0225, 0x0226, 0x002E, 
    0x002F, 0x0030, 0x0000, 0x0000,
};

/*******************************/

/************ .bss ************/

f32 D_8011D5C0;
s8 D_8011D5C4;
u16 *D_8011D5C8;
s32 D_8011D5CC;

/******************************/

void func_8005C2F0(Object *object, unk8005C2F0 *arg1) {
    object->unk4C->unk14 = 5;
    object->unk4C->unk11 = 0;
    object->unk4C->unk10 = 0x1E;
    object->unk4C->unk12 = 0;
    arg1->unkC = 0.0f;
    D_8011D5C0 = object->y_position;
    if (arg1->unk118 != 0) {
        func_80006AC8();
    }
    D_8011D5C4 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005C364.s")

void func_8005CA78(s32 arg0) {
    D_8011D5C8 = arg0;
}

void func_8005CA84(f32 x, f32 y, f32 z, s32 arg3) {
    s8 phi_v1 = get_random_number_from_range(0, 1);
    if (arg3 == 0) {
        phi_v1 = 0;
    }
    arg3 += phi_v1;
    func_80009558(D_8011D5C8[arg3], x, y, z, 4, 0);
}

void func_8005CB04(s32 arg0) {
    s8 phi_v1 = get_random_number_from_range(0, 1);
    if (arg0 == 0) {
        phi_v1 = 0;
    }
    arg0 += phi_v1;
    func_80001D04(D_8011D5C8[arg0], 0);
}

GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005CB68.s")

void func_8005D048(Object *object, unk8005D048 *arg1, s32 arg2) {
    Object *sp1C = get_object_struct(0);
    arg1->unk1F7 = 0xFF;
    if (!func_8001139C()) {
        if ((object->unk30 + arg2) < sp1C->unk30) {
            arg1->unk1F7 = 0x40;
        }
    }
}
