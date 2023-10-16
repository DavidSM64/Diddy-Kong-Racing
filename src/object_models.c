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
s32 *D_8011D624;
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

    D_8011D624 = allocate_from_main_pool_safe(0x230, COLOUR_TAG_GREEN);
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

unk8005FCD0 *func_8005FCD0(ObjectModel* model, s32 arg1) {
    s32 temp;
    unk8005FCD0 *result;
    s32 var_v1;
    Vertex *vertex;
    Vertex *mdlVertex;

    if ((model->numberOfAnimations != 0) && (arg1 & 8)) {
        temp = ((model->numberOfVertices << 1) * 10) + 36;
        result = (unk8005FCD0 *) allocate_from_main_pool((model->unk4A * 6) + temp, COLOUR_TAG_BLUE);
        if (result == NULL) {
            return NULL;
        }
        result->unk4 = (Vertex *) ((u8 *) result + 36);
        result->unk8 = (Vertex *) ((u8 *) result + (model->numberOfVertices * 10) + 36);
        result->unkC = ((u8*)result + temp);
        result->unk1E = 2;
    } else if ((model->unk40 != NULL) && (arg1 & 1)) {
        temp = (model->numberOfVertices * 10);
        result = (unk8005FCD0 *) allocate_from_main_pool(temp + 36, COLOUR_TAG_BLUE);
        if (result == NULL) {
            return NULL;
        }
        var_v1 = (u8 *) result + 36;
        result->unk4 = (Vertex *) var_v1;
        result->unk8 = (Vertex *) var_v1;
        result->unkC = 0;
        result->unk1E = 1;
    } else {
        result = (unk8005FCD0 *) allocate_from_main_pool(36, COLOUR_TAG_BLUE);
        if (result == NULL) {
            return NULL;
        }
        result->unk4 = (Vertex *) model->vertices;
        result->unk8 = (Vertex *) model->vertices;
        result->unkC = 0;
        result->unk1E = 0;
    }
    result->unk16 = 0;
    result->unk18 = 0;
    result->unk1A = 0;
    result->unk0 = model;
    result->unk10 = -1;
    result->unk12 = -1;
    result->unk1F = 0;
    if (result->unk1E != 0) {
        temp = 0;
        vertex = &result->unk4[0];
        mdlVertex = &model->vertices[0];
        do {
            vertex->x = mdlVertex->x;
            vertex->y = mdlVertex->y;
            vertex->z = mdlVertex->z;
            vertex->r = mdlVertex->r;
            vertex->g = mdlVertex->g;
            vertex->b = mdlVertex->b;
            vertex->a = mdlVertex->a;
            vertex++;
            mdlVertex++;
            temp++;
        } while(temp < model->numberOfVertices);
        
        temp = 0;
        vertex = &result->unk8[0];
        mdlVertex = &model->vertices[0];
        do {
            vertex->x = mdlVertex->x;
            vertex->y = mdlVertex->y;
            vertex->z = mdlVertex->z;
            vertex->r = mdlVertex->r;
            vertex->g = mdlVertex->g;
            vertex->b = mdlVertex->b;
            vertex->a = mdlVertex->a;
            vertex++;
            mdlVertex++;
            temp++;
        } while(temp < model->numberOfVertices);
    }
    return result;
}

void func_8005FF40(ObjectModel **modelPtr) {
    UNUSED s32 pad;
    s32 modelIndex;
    ObjectModel *model;
    s32 i;
    
    if (modelPtr != 0) {
        model = *modelPtr;
        model->unk30--;
        if (model->unk30 > 0) {
            free_from_memory_pool(modelPtr);
            return;
        }
        
        modelIndex = -1;
        for (i = 0; i < D_8011D62C; i++) {
            if ((s32) model == D_8011D624[(i << 1) + 1]) {
                modelIndex = i;
            }
        }
        
        if (modelIndex != -1) {
            free_object_model(model);
            D_8011D628[D_8011D634] = modelIndex;
            D_8011D634++;
            D_8011D624[modelIndex << 1] = -1;
            D_8011D624[(modelIndex << 1) + 1] = -1;
            free_from_memory_pool(modelPtr);
        }
    }
}

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

s32 func_80060C58(Vertex *vertices, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Vertex *a;
    Vertex *b;
    Vertex *c;
    Vertex *d;
    if (((arg1 == arg3) && (arg2 == arg4)) || ((arg1 == arg4) && (arg2 == arg3))) {
        return 1;
    }
    a = &vertices[arg1];
    b = &vertices[arg2];
    c = &vertices[arg3];
    d = &vertices[arg4];
    if (((c->x - 4) < a->x) && (a->x < (c->x + 4))) {
        if (((c->y - 4) < a->y) && (a->y < (c->y + 4))) {
            if (((c->z - 4) < a->z) && (a->z < (c->z + 4))) {
                if (((d->x - 4) < b->x) && (b->x < (d->x + 4))) {
                    if (((d->y - 4) < b->y) && (b->y < (d->y + 4))) {
                        if (((d->z - 4) < b->z) && (b->z < (d->z + 4))) {
                            return 2;
                        }
                    }
                }
                goto end;
            }
        }
    }
    if (((d->x - 4) < a->x) && (a->x < (d->x + 4))) {
        if (((d->y - 4) < a->y) && (a->y < (d->y + 4))) {
            if (((d->z - 4) < a->z) && (a->z < (d->z + 4))) {
                if (((c->x - 4) < b->x) && (b->x < (c->x + 4))) {
                    if (((c->y - 4) < b->y) && (b->y < (c->y + 4))) {
                        if (((c->z - 4) < b->z) && (b->z < (c->z + 4))) {
                            return 2;
                        }
                    }
                }
            }
        }
    }
    end:
    return 0;
    
}

GLOBAL_ASM("asm/non_matchings/object_models/func_80060EA8.s")

void func_800619F4(s32 arg0) {
    D_8011D640 = arg0;
}

// Returns 0 if successful, or 1 if an error occured.
s32 func_80061A00(ObjectModel *model, s32 animTableIndex) {
    s32 j;
    s32 end;
    ObjectModel_44 *allocAnimData;
    s32 start;
    s32 size;
    s32 assetOffset;
    s32 assetSize;
    s32 i;
    s32 i2;
    u32 animAddress;
    s32 *temp;

    start = gAnimationTable[animTableIndex];
    end = gAnimationTable[animTableIndex+1];
    if (start == end) {
        model->numberOfAnimations = 0;
        return 0;
    }
    if (D_8011D640 != 0) {
        if (start + D_8011D640 < end) {
            end = start + D_8011D640;
        }
    }
    model->numberOfAnimations = end - start;
    allocAnimData = (ObjectModel_44 *) allocate_from_main_pool(model->numberOfAnimations * 8, COLOUR_TAG_RED);
    model->animations = allocAnimData;
    if (allocAnimData == NULL) {
        return 1;
    }
    i = 0;
    i2 = 0;
    do {
        assetOffset = gObjectAnimationTable[start];
        animAddress = gObjectAnimationTable[start+1] - assetOffset;
        assetSize = animAddress;
        size = get_asset_uncompressed_size(ASSET_OBJECT_ANIMATIONS, assetOffset) + 0x80;
        model->animations[i].animData = (u8 *) allocate_from_main_pool(size, COLOUR_TAG_RED);
        if (model->animations[i].animData == NULL) {
            for(j = 0; j < i2; j++) {
                free_from_memory_pool(model->animations[j].animData);
            }
            free_from_memory_pool(model->animations);
            model->animations = NULL;
            return 1;
        }
        animAddress = (u32) (model->animations[i].animData + size) - assetSize;
        load_asset_to_address(ASSET_OBJECT_ANIMATIONS, animAddress, assetOffset, assetSize);
        gzip_inflate((u8* ) animAddress, (u8 *) model->animations[i].anim);
        temp = model->animations[i].anim;
        model->animations[i].unk4 = *temp;
        model->animations[i].anim++;
        i++;
        start++;
        i2++;
    } while (start < end);

    return 0;
}

void func_80061C0C(Object *obj) {
    ObjectModel *mdl;
    Object_68 *gfxData;
    s32 var_v1;

    if (obj->segment.object.modelIndex < 0) {
        obj->segment.object.modelIndex = 0;
    }
    var_v1 = obj->segment.header->numberOfModelIds - 1;
    if (var_v1 < obj->segment.object.modelIndex) {
        obj->segment.object.modelIndex = var_v1;
    }
    gfxData = obj->unk68[obj->segment.object.modelIndex];
    mdl = gfxData->objModel;
    if (gfxData->objModel->animations != NULL) {
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
            gfxData->unk10 = -1;
        }
    }
}
