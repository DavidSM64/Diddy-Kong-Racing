/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005C2F0 */

#include "unknown_05CEF0.h"

#include "structs.h"
#include "types.h"
#include "macros.h"
#include "audio.h"
#include "objects.h"
#include "unknown_005740.h"
#include "unknown_008C40.h"

/************ .data ************/

s16 D_800DCDE0[16] = {
    SOUND_VOICE_BOSS_LAUGH,
    SOUND_VOICE_TRICKY_WOAH,
    SOUND_VOICE_TRICKY_WOAH2,
    SOUND_VOICE_WIZPIG_LAUGH_SHORT2,
    SOUND_VOICE_WIZPIG_LAUGH_SHORT3,
    SOUND_VOICE_TRICKY_WOAH3,
    SOUND_VOICE_TRICKY_WOAH4,
    SOUND_VOICE_TRICKY_LAUGH,
    SOUND_VOICE_TRICKY_LAUGH2,
    SOUND_VOICE_TRICKY_OW,
    SOUND_VOICE_TRICKY_OW2,
    SOUND_VOICE_CONKER_YEHAHA,
    SOUND_VOICE_TIMBER_WOW,
    SOUND_WHOOSH2,
    SOUND_UNK00,
    SOUND_UNK00
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
    D_8011D5C0 = object->segment.trans.y_position;
    if (arg1->unk118 != 0) {
        func_80006AC8(object);
    }
    D_8011D5C4 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005C364.s")

void func_8005CA78(u16 *arg0) {
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
    play_sound_global(D_8011D5C8[arg0], 0);
}

GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005CB68.s")

void func_8005D048(Object *object, Object_Racer *arg1, s32 arg2) {
    Object *sp1C = get_object_struct(0);
    arg1->transparency = 0xFF;
    if (!func_8001139C()) {
        if ((object->segment.unk30 + arg2) < sp1C->segment.unk30) {
            arg1->transparency = 0x40;
        }
    }
}
