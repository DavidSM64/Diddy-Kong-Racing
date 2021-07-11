/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005F850 */

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "memory.h"
#include "asset_sections.h"

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

/* 8 Bytes */
typedef struct unk8011D624 {
    s32 unk0;
    ObjectModel *model;
} unk8011D624;

s32 *D_8011D620;
unk8011D624 *D_8011D624; // Array of unk8011D624
s32 *D_8011D628;
s32 D_8011D62C;
s32 D_8011D630;
s32 D_8011D634;
s16 *D_8011D638;
s32 *D_8011D63C;
s32 D_8011D640;
s32 D_8011D644;
s32 D_8011D648[66];

/******************************/

void func_80024D54(void);

void func_8005F850(void) {
    s32 i;
    s32 checksum;

    D_8011D624 = allocate_from_main_pool_safe(0x230, COLOR_TAG_GREEN);
    D_8011D628 = allocate_from_main_pool_safe(0x190, COLOR_TAG_GREEN);
    D_8011D62C = 0;
    D_8011D634 = 0;
    D_8011D620 = load_asset_section_from_rom(ASSET_OBJECT_MODELS_TABLE);
    D_8011D630 = 0;
    while (D_8011D620[D_8011D630] != -1) {
        D_8011D630++;
    }
    D_8011D630--;
    D_8011D638 = load_asset_section_from_rom(ASSET_ANIMATION_IDS);
    D_8011D63C = load_asset_section_from_rom(ASSET_OBJECT_ANIMATIONS_TABLE);
    D_8011D644 = allocate_from_main_pool_safe(0xC00, COLOR_TAG_GREEN);
    D_8011D640 = 0;
    checksum = 0;
    for (i = 0; i < D_800DCEA4; i++) {
        checksum += *(u8*)(((s32)&func_80024D54) + i);
    }
    if (checksum != D_800DCEA0) {
        func_8005C25C();
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005F99C.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005FCD0.s")

#if 0
void free_object_model(ObjectModel *model);
void free_from_memory_pool(void*);

// Causes crashes after playing a little, and I don't know why.
void func_8005FF40(ObjectModel **modelPtr) {
    s32 i;
    s32 modelIndex;
    ObjectModel *model;
    
    if (modelPtr != NULL) {
        model = *modelPtr;
        model->unk30--;
        if (model->unk30 > 0) {
            free_from_memory_pool(model);
            return;
        }
        modelIndex = -1;
        for (i = 0; i < D_8011D62C; i++) {
            if (model == D_8011D624[i].model) {
                modelIndex = i;
            }
        }
        if (modelIndex != -1) {
            free_object_model(model);
            D_8011D628[D_8011D634] = modelIndex;
            D_8011D634++;
            D_8011D624[modelIndex].unk0 = -1;
            D_8011D624[modelIndex].model = (ObjectModel *)-1;
            free_from_memory_pool(modelPtr);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005FF40.s")
#endif

#ifdef NON_MATCHING
// Regalloc issues.
void free_object_model(ObjectModel *model) {
    s32 i;
    for (i = 0; i < model->numberOfTextures; i++) {
        if (model->textures[i].texture != NULL) {
            func_8007B2BC(model->textures[i].texture);
        }
    }
    if (model->unkC != NULL) {
        free_from_memory_pool(model->unkC);
    }
    if (model->unk10 != NULL) {
        free_from_memory_pool(model->unk10);
    }
    if (model->unk40 != NULL) {
        free_from_memory_pool(model->unk40);
    }
    if (model->animations != NULL) {
        // Small issue with this loop too.
        for (i = 0; i < model->numberOfAnimations; i++) {
            free_from_memory_pool(model->animations[i].anim - 1);
        }
        free_from_memory_pool(model->animations);
    }
    free_from_memory_pool(model);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_05F690/free_object_model.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8006017C.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060910.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060AC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060C58.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060EA8.s")

void func_800619F4(s32 arg0) {
    D_8011D640 = arg0;
}

// s32 func_80061A00(ObjectModel *model, s32 animTableIndex)
// Returns 0 if successful, or 1 if an error occured.
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80061A00.s")

GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80061C0C.s")
