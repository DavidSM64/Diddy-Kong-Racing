/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80008040 */

#include "unknown_008C40.h"
#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "unknown_005740.h"
#include "memory.h"
#include "audio.h"

/************ .data ************/

s32 D_800DC6E0 = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .rodata ************/

const char D_800E4D00[] = "OUT OF AUDIO POINTS\n";
const char D_800E4D18[] = "amAudioLineAddVertex: Exceeded maximum number of lines (%d)\n";
const char D_800E4D58[] = "amAudioLineAddVertex: Exceeded maximum number of line vertices (%d)\n";
const char D_800E4DA0[] = "amReverbLineAddVertex: Exceeded maximum number of lines (%d)\n";
const char D_800E4DE0[] = "amReverbLineAddVertex: Exceeded maximum number of line vertices (%d)\n";

const char D_800E4E28[] = "Audio line definition error (less than 2 vertices on line %d)\n";
const char D_800E4E68[] = "Audio line definition error (line=%d, vertex=%d)\n";
const char D_800E4E9C[] = "Reverb line definition error (less than 2 vertices on line %d)\n";
const char D_800E4EDC[] = "Reverb line definition error (line=%d, vertex=%d)\n";

/*********************************/

/************ .bss ************/

extern s8 D_8011AC18;

/*******************************/

#ifdef NON_EQUIVALENT
void func_80008040(void) {
    u32 temp_v1;
    //? *phi_v1;
    s32 i;

    func_80002128(&D_80119C40, NULL, NULL);
    D_80119C48 = allocate_from_main_pool_safe(1440, COLOR_TAG_CYAN);
    D_80119C50 = allocate_from_main_pool_safe(160, COLOR_TAG_CYAN);
    D_80119C44 = allocate_from_main_pool_safe(160, COLOR_TAG_CYAN);
    D_800DC6E0 = 0;
    // phi_v1 = &D_80119C58;
    // do {
    //     temp_v1 = phi_v1 + 0x180;
    //     temp_v1->unk-8 = 0;
    //     phi_v1 = (? *) temp_v1;
    // } while (temp_v1 < (u32) &D_8011A6D8);
    for (i = 0; i < 384; i++) {
        D_80119C48[i]->unk18 = 0;
        D_80119C48[i]->unk3C = 0;
        D_80119C48[i]->unk60 = 0;
        D_80119C48[i]->unk84 = 0;
    }
    func_80008174();
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008040.s")
#endif

void func_80008140(void) {
    func_800018E0();
    D_8011AC18 = 1;
}

void func_80008168(void) {
    D_8011AC18 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008174.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008438.s")

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800090C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800092A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009558.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800095E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800096D8.s")
void func_800096F8(s32 arg0) {
    s32 i;
    s32 *v0 = D_80119C44;
    for (i = 0; i < 40; i++) {
        if (arg0 == *v0) {
            func_8000A2E8(i);
            break;
        }
        v0++;
    }
}
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000974C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800098A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009968.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800099EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009AB4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009B7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009D6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A2E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A414.s")
