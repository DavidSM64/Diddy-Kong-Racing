/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005F850 */

#include "object_models.h"
#include "common.h"
#include "macros.h"
#include "memory.h"
#include "asset_enums.h"
#include "tracks.h"
#include "asset_loading.h"
#include "textures_sprites.h"
#include "racer.h"
#include "save_data.h"

/************ .data ************/

s32 gTractionTableChecksum = TractionTableChecksum;
s32 gTrackRenderFuncLength = 1980;

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
s32 gNumModelIDs;
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

    D_8011D624 = mempool_alloc_safe(0x230, COLOUR_TAG_GREEN);
    D_8011D628 = mempool_alloc_safe(0x190, COLOUR_TAG_GREEN);
    D_8011D62C = 0;
    D_8011D634 = 0;
    gObjectModelTable = (s32 *) load_asset_section_from_rom(ASSET_OBJECT_MODELS_TABLE);
    gNumModelIDs = 0;
    while (gObjectModelTable[gNumModelIDs] != -1) {
        gNumModelIDs++;
    }
    gNumModelIDs--;
    gAnimationTable = (s16 *) load_asset_section_from_rom(ASSET_ANIMATION_IDS);
    gObjectAnimationTable = (s32 *) load_asset_section_from_rom(ASSET_OBJECT_ANIMATIONS_TABLE);
    D_8011D644 = (s32) mempool_alloc_safe(0xC00, COLOUR_TAG_GREEN);
    D_8011D640 = 0;

#ifdef ANTI_TAMPER
    // Antipiracy measure
    checksum = 0;
    for (i = 0; i < gTrackRenderFuncLength; i++) {
        checksum += *(u8 *) (((s32) &render_scene) + i);
    }
    if (checksum != gTractionTableChecksum) {
        drm_vehicle_traction();
    }
#endif
}

/**
 * Load the associated model ID and assign it to the objects gfx data.
 * Also loads textures and animations.
 */
Object_68 *object_model_init(s32 modelID, s32 flags) {
    s32 i;
    s32 sp50;
    ObjectModel *objMdl;
    s32 sp48;
    s32 temp_s0;
    Object_68 *ret;
    s8 sp3F;
#if VERSION >= VERSION_79
    s8 var_a2;
    s8 var_a3;
#endif
    u32 compressedData;
    s32 sp34;

    if (modelID >= gNumModelIDs) {
        stubbed_printf(D_800E6B20);
        modelID = 0;
    }

    // Check if the model already exists in the cache.
    for (i = 0; i < D_8011D62C; i++) {
        if (modelID == D_8011D624[(i << 1)]) {
            objMdl = (ObjectModel *) D_8011D624[(i << 1) + 1];
            ret = func_8005FCD0(objMdl, flags);
            if (ret != NULL) {
                objMdl->references++;
            }
            return ret;
        }
    }

#if VERSION >= VERSION_79
    var_a2 = FALSE;
    var_a3 = FALSE;
#endif
    if (D_8011D634 > 0) {
        D_8011D634--;
#if VERSION >= VERSION_79
        var_a2 = TRUE;
#endif
        sp50 = D_8011D628[D_8011D634];
    } else {
        sp50 = D_8011D62C;
#if VERSION >= VERSION_79
        var_a3 = TRUE;
#endif
        D_8011D62C++;
    }

    temp_s0 = gObjectModelTable[modelID];
    sp48 = gObjectModelTable[modelID + 1] - temp_s0;
    sp34 = get_asset_uncompressed_size(ASSET_OBJECT_MODELS, temp_s0) + 0x80;
    objMdl = (ObjectModel *) mempool_alloc(sp34, COLOUR_TAG_RED);
    if (objMdl == NULL) {
#if VERSION >= VERSION_79
        if (var_a2) {
            D_8011D634++;
        }
        if (var_a3) {
            D_8011D62C--;
        }
#endif
        return NULL;
    }
    compressedData = (u32) ((u8 *) objMdl + sp34) - sp48;
    load_asset_to_address(ASSET_OBJECT_MODELS, compressedData, temp_s0, sp48);
    gzip_inflate((u8 *) compressedData, (u8 *) objMdl);
    objMdl->textures = (TextureInfo *) ((s32) objMdl->textures + (u8 *) objMdl);
    objMdl->vertices = (Vertex *) ((s32) objMdl->vertices + (u8 *) objMdl);
    objMdl->triangles = (Triangle *) ((s32) objMdl->triangles + (u8 *) objMdl);
    objMdl->batches = (TriangleBatchInfo *) ((s32) objMdl->batches + (u8 *) objMdl);
    objMdl->unk14 = (s16 *) ((s32) objMdl->unk14 + (u8 *) objMdl);
    objMdl->unk1C = (s16 *) ((s32) objMdl->unk1C + (u8 *) objMdl);
    objMdl->unk4C = (s32 *) ((s32) objMdl->unk4C + (u8 *) objMdl);
    objMdl->references = 1;
    objMdl->unkC = 0;
    objMdl->unk10 = 0;
    objMdl->unk32 = 0;
    objMdl->unk52 = 0;
    objMdl->unk40 = 0;
    objMdl->numberOfAnimations = 0;
    objMdl->animations = NULL;
    sp3F = 0;
    for (i = 0; i < objMdl->numberOfTextures; i++) {
        objMdl->textures[i].texture = load_texture(((s32) objMdl->textures[i].texture) | 0x8000);
        if (objMdl->textures[i].texture == NULL) {
            sp3F = 1;
        }
    }
    if (!sp3F) {
        for (i = 0; i < objMdl->numberOfBatches; i++) {
            if ((objMdl->batches[i].textureIndex != 0xFF) &&
                (objMdl->batches[i].textureIndex >= objMdl->numberOfTextures)) {
                stubbed_printf(D_800E6B4C);
                goto block_30;
            }
        }
        if ((func_80060EA8(objMdl) == 0) && (func_80061A00(objMdl, modelID) == 0)) {
            ret = func_8005FCD0(objMdl, flags);
            if (ret != NULL) {
                D_8011D624[(sp50 << 1)] = modelID;
                D_8011D624[(sp50 << 1) + 1] = (s32) objMdl;
                if (D_8011D62C < 70) {
                    ret->unk20 = 0;
                    return ret;
                }
            }
        }
    }
block_30:
#if VERSION >= VERSION_79
    if (var_a3) {
        D_8011D62C--;
    }
    if (var_a2) {
        D_8011D634++;
    }
#endif
    free_model_data((ObjectModel *) objMdl);
    return NULL;
}

Object_68 *func_8005FCD0(ObjectModel *model, s32 arg1) {
    s32 temp;
    Object_68 *result;
    Vertex *var_v1;
    Vertex *vertex;
    Vertex *mdlVertex;

    if ((model->numberOfAnimations != 0) && (arg1 & 8)) {
        temp = ((model->numberOfVertices << 1) * 10) + 36;
        result = (Object_68 *) mempool_alloc((model->unk4A * 6) + temp, COLOUR_TAG_BLUE);
        if (result == NULL) {
            return NULL;
        }
        result->unk4[0] = (Vertex *) ((u8 *) result + 36);
        result->unk4[1] = (Vertex *) ((u8 *) result + (model->numberOfVertices * 10) + 36);
        result->unk4[2] = (Vertex *) ((u8 *) result + temp);
        result->unk1E = 2;
    } else if ((model->unk40 != NULL) && (arg1 & 1)) {
        temp = (model->numberOfVertices * 10);
        result = (Object_68 *) mempool_alloc(temp + 36, COLOUR_TAG_BLUE);
        if (result == NULL) {
            return NULL;
        }
        var_v1 = (Vertex *) ((u8 *) result + 36);
        result->unk4[0] = var_v1;
        result->unk4[1] = var_v1;
        result->unk4[2] = NULL;
        result->unk1E = 1;
    } else {
        result = (Object_68 *) mempool_alloc(36, COLOUR_TAG_BLUE);
        if (result == NULL) {
            return NULL;
        }
        result->unk4[0] = model->vertices;
        result->unk4[1] = model->vertices;
        result->unk4[2] = NULL;
        result->unk1E = 0;
    }
    result->offsetX = 0;
    result->offsetY = 0;
    result->offsetZ = 0;
    result->objModel = model;
    result->animationID = -1;
    result->animationFrame = -1;
    result->animationTaskNum = 0;
    if (result->unk1E != 0) {
        temp = 0;
        vertex = result->unk4[0];
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
        } while (temp < model->numberOfVertices);

        temp = 0;
        vertex = result->unk4[1];
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
        } while (temp < model->numberOfVertices);
    }
    return result;
}

/**
 * Attempts to free the object model from RAM.
 */
void free_3d_model(ObjectModel **modelPtr) {
    UNUSED s32 pad;
    s32 modelIndex;
    ObjectModel *model;
    s32 i;

    if (modelPtr != 0) {
        model = *modelPtr;
        model->references--;
        if (model->references > 0) { // Model is still used, so free the reference and return.
            mempool_free(modelPtr);
            return;
        }

        modelIndex = -1;
        for (i = 0; i < D_8011D62C; i++) {
            if ((s32) model == D_8011D624[(i << 1) + 1]) {
                modelIndex = i;
            }
        }

        if (modelIndex != -1) {
            free_model_data(model);
            D_8011D628[D_8011D634] = modelIndex;
            D_8011D634++;
            D_8011D624[modelIndex << 1] = -1;
            D_8011D624[(modelIndex << 1) + 1] = -1;
            mempool_free(modelPtr);
        }
    }
}

/**
 * Frees all associated meshes, textures and animations from the model.
 */
void free_model_data(ObjectModel *mdl) {
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
        mempool_free(mdl->unkC);
    }
    // ???
    if (mdl->unk10 != NULL) {
        mempool_free(mdl->unk10);
    }
    // ???
    if (mdl->unk40 != NULL) {
        mempool_free(mdl->unk40);
    }
    // free the animations
    if (mdl->animations != NULL) {
        s32 animsFreed = 0;
        s32 animIndex = 0;
        if (mdl->numberOfAnimations != 0) {
            do {
                mempool_free(mdl->animations[animIndex].anim - 1);
                animsFreed++;
                animIndex++;
            } while (animsFreed < mdl->numberOfAnimations);
            mempool_free(mdl->animations);
        }
    }
    // free the model itself
    mempool_free(mdl);
}

#pragma GLOBAL_ASM("asm/nonmatchings/object_models/func_8006017C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/object_models/func_80060910.s")
#pragma GLOBAL_ASM("asm/nonmatchings/object_models/func_80060AC8.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/object_models/func_80060EA8.s")

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
    end = gAnimationTable[animTableIndex + 1];
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
    allocAnimData = (ObjectModel_44 *) mempool_alloc(model->numberOfAnimations * 8, COLOUR_TAG_RED);
    model->animations = allocAnimData;
    if (allocAnimData == NULL) {
        return 1;
    }
    i = 0;
    i2 = 0;
    do {
        assetOffset = gObjectAnimationTable[start];
        animAddress = gObjectAnimationTable[start + 1] - assetOffset;
        assetSize = animAddress;
        size = get_asset_uncompressed_size(ASSET_OBJECT_ANIMATIONS, assetOffset) + 0x80;
        model->animations[i].animData = (u8 *) mempool_alloc(size, COLOUR_TAG_RED);
        if (model->animations[i].animData == NULL) {
            for (j = 0; j < i2; j++) {
                mempool_free(model->animations[j].animData);
            }
            mempool_free(model->animations);
            model->animations = NULL;
            return 1;
        }
        animAddress = (u32) (model->animations[i].animData + size) - assetSize;
        load_asset_to_address(ASSET_OBJECT_ANIMATIONS, animAddress, assetOffset, assetSize);
        gzip_inflate((u8 *) animAddress, (u8 *) model->animations[i].anim);
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
            gfxData->animationID = -1;
        }
    }
}
