/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005F850 */

#include "types.h"
#include "macros.h"

/************ .data ************/

s32 D_800DCEA0 = 116315;
s32 D_800DCEA4 = 1980;

/*******************************/

/************ .rodata ************/

const char D_800E6B20[] = "Error: Model no. out of range on load. !!\n";
const char D_800E6B4C[] = "TEXTURE ERROR!!\n%d,%d\n";
const char D_800E6B64[] = "Error: Model table overflow!!\n";
const char D_800E6B84[] = "WARNING :: createModelInstance called with NULL pointer\n";
const char D_800E6BC0[] = "ModFreeModel : NULL mod_inst!!\n";
const char D_800E6BE0[] = "MOD Error: Tryed to deallocate non-existent model!!\n";

/*********************************/

/************ .bss ************/

s32 D_8011D620;
s32 D_8011D624;
s32 D_8011D628;
s32 D_8011D62C;
s32 D_8011D630;
s32 D_8011D634;
s32 D_8011D638;
s32 D_8011D63C;
s32 D_8011D640;
s32 D_8011D644;
s32 D_8011D648[66];

/******************************/

GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005F850.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005F99C.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005FCD0.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005FF40.s")

#if 1
void func_80060058(void *arg0) {
    s32 i;
    for (i = 0; i < arg0->unk22; i++) {
        if (arg0->unk0[i].unk0 != NULL) {
            func_8007B2BC(arg0->unk0[i].unk0);
        }
    }
    if (arg0->unkC != NULL) {
        free_from_memory_pool(arg0->unkC);
    }
    if (arg0->unk10 != NULL) {
        free_from_memory_pool(arg0->unk10);
    }
    if (arg0->unk40 != NULL) {
        free_from_memory_pool(arg0->unk40);
    }
    if (arg0->unk44 != NULL) {
        for (i = 0; i < arg0->unk48; i++) {
            free_from_memory_pool((u8*)arg0->unk44[i] - 4);
        }
        free_from_memory_pool(arg0->unk44);
    }
    free_from_memory_pool(arg0);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060058.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8006017C.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060910.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060AC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060C58.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060EA8.s")

void func_800619F4(s32 arg0) {
    D_8011D640 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80061A00.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80061C0C.s")