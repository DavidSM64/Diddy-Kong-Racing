/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005F850 */

#include "object_models.h"
#include "macros.h"
#include "memory.h"
#include "asset_enums.h"
#include "tracks.h"
#include "asset_loading.h"
#include "textures_sprites.h"
#include "racer.h"

/************ .data ************/

s32 gTractionTableChecksum = 116315;
s32 gFunc80024D54Length = 1980;

/*******************************/

/************ .rodata ************/

UNUSED const char D_800E6B20[] = "Error: Model no. out of range on load. !!\n";
UNUSED const char D_800E6B4C[] = "TEXTURE ERROR!!\n%d,%d\n";
UNUSED const char D_800E6B64[] = "Error: Model table overflow!!\n";
UNUSED const char D_800E6B84[] = "WARNING :: createModelInstance called with NULL pointer\n";
UNUSED const char D_800E6BC0[] = "ModFreeModel : NULL mod_inst!!\n";
UNUSED const char D_800E6BE0[] = "MOD Error: Tryed to deallocate non-existent model!!\n";

/*********************************/

/************ .bss ************/

s32 *gObjectModelTable;
unk8011D624 *D_8011D624; // Array of unk8011D624
s32 *D_8011D628;
s32 D_8011D62C;
s32 D_8011D630;
s32 D_8011D634;
s16 *gAnimationTable;
s32 *gObjectAnimationTable;
s32 D_8011D640;
s32 D_8011D644;

/******************************/

/**
 * Allocate memory for object model ID's and animation tables.
*/
void allocate_object_model_pools(void) {
    s32 i;
    s32 checksum;

    D_8011D624 = (unk8011D624 *) allocate_from_main_pool_safe(0x230, COLOUR_TAG_GREEN);
    D_8011D628 = allocate_from_main_pool_safe(0x190, COLOUR_TAG_GREEN);
    D_8011D62C = 0;
    D_8011D634 = 0;
    gObjectModelTable = (s32 *) load_asset_section_from_rom(ASSET_OBJECT_MODELS_TABLE);
    D_8011D630 = 0;
    while (gObjectModelTable[D_8011D630] != -1) {
        D_8011D630++;
    }
    D_8011D630--;
    gAnimationTable = (s16 *) load_asset_section_from_rom(ASSET_ANIMATION_IDS);
    gObjectAnimationTable = (s32 *) load_asset_section_from_rom(ASSET_OBJECT_ANIMATIONS_TABLE);
    D_8011D644 = (s32) allocate_from_main_pool_safe(0xC00, COLOUR_TAG_GREEN);
    D_8011D640 = 0;

    // Antipiracy measure
    checksum = 0;
    for (i = 0; i < gFunc80024D54Length; i++) {
        checksum += *(u8 *)(((s32) &render_scene) + i);
    }
    if (checksum != gTractionTableChecksum) {
        antipiracy_modify_surface_traction_table();
    }
}

GLOBAL_ASM("asm/non_matchings/object_models/func_8005F99C.s")
GLOBAL_ASM("asm/non_matchings/object_models/func_8005FCD0.s")

#ifdef NON_MATCHING
void func_8005FF40(ObjectModel **modelPtr) {
    s32 i;
    s32 modelIndex;
    ObjectModel *model;
    
    if (modelPtr != NULL) {
        model = *modelPtr;
        model->unk30--;
        if (model->unk30 > 0) {
            free_from_memory_pool(modelPtr);
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
            D_8011D624[modelIndex].model = (ObjectModel *) -1;
            free_from_memory_pool(modelPtr);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/object_models/func_8005FF40.s")
#endif

void free_object_model(ObjectModel *mdl) {
    // free the textures
    s16 numTextures = mdl->numberOfTextures;
    if (numTextures > 0) {
        s32 texturesFreed = 0;
        s32 textureIndex = 0;
        do {
            TextureHeader *header = mdl->textures[textureIndex].texture;
            if (header != NULL) {
                free_texture(header);
                numTextures = mdl->numberOfTextures;
            }
            texturesFreed++;
            textureIndex++;
        } while (texturesFreed < numTextures);
    }
    // ???
    if (mdl->unkC != NULL) {
        free_from_memory_pool(mdl->unkC);
    }
    // ???
    if (mdl->unk10 != NULL) {
        free_from_memory_pool(mdl->unk10);
    }
    // ???
    if (mdl->unk40 != NULL) {
        free_from_memory_pool(mdl->unk40);
    }
    // free the animations
    if (mdl->animations != NULL) {
        s32 animsFreed = 0;
        s32 animIndex = 0;
        if (mdl->numberOfAnimations != 0) {
            do {
                free_from_memory_pool(mdl->animations[animIndex].anim - 1);
                animsFreed++;
                animIndex++;
            } while (animsFreed < mdl->numberOfAnimations);
            free_from_memory_pool(mdl->animations);
        }
    }
    // free the model itself
    free_from_memory_pool(mdl);
}

GLOBAL_ASM("asm/non_matchings/object_models/func_8006017C.s")
GLOBAL_ASM("asm/non_matchings/object_models/func_80060910.s")
GLOBAL_ASM("asm/non_matchings/object_models/func_80060AC8.s")
GLOBAL_ASM("asm/non_matchings/object_models/func_80060C58.s")
GLOBAL_ASM("asm/non_matchings/object_models/func_80060EA8.s")

void func_800619F4(s32 arg0) {
    D_8011D640 = arg0;
}

// s32 func_80061A00(ObjectModel *model, s32 animTableIndex)
// Returns 0 if successful, or 1 if an error occured.
GLOBAL_ASM("asm/non_matchings/object_models/func_80061A00.s")

void func_80061C0C(Object *obj) {
    ObjectModel *mdl;
    Object_68 *temp_a1;
    s32 var_v1;

    if (obj->segment.object.numModelIDs < 0) {
        obj->segment.object.numModelIDs = 0;
    }
    var_v1 = obj->segment.header->numberOfModelIds - 1;
    if (var_v1 < obj->segment.object.numModelIDs) {
        obj->segment.object.numModelIDs = var_v1;
    }
    temp_a1 = obj->unk68[obj->segment.object.numModelIDs];
    mdl = temp_a1->objModel;
    if (temp_a1->objModel->animations != NULL) {
        if (obj->segment.object.animationID < 0) {
            obj->segment.object.animationID = 0;
        }
        if (obj->segment.object.animationID >= mdl->numberOfAnimations) {
            obj->segment.object.animationID = mdl->numberOfAnimations - 1;
        }
        if (mdl->numberOfAnimations > 0) {
            var_v1 = mdl->animations[obj->segment.object.animationID].unk4 - 2;
        } else {
            var_v1 = 0;
        }
        if (obj->segment.animFrame >> 4 < 0) {
            obj->segment.animFrame = var_v1;
        }
        if (var_v1 < obj->segment.animFrame >> 4) {
            obj->segment.animFrame = 0;
            temp_a1->unk10 = -1;
        }
    }
}
