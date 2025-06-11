#include "object_models.h"
#include "common.h"
#include "macros.h"
#include "memory.h"
#include "asset_enums.h"
#include "tracks.h"
#include "asset_loading.h"
#include "textures_sprites.h"
#include "racer.h"
#include "objects.h"

#define MODEL_LOADED_MAX 70

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
s32 *gModelCache; // A table of two entries. The first half is the model ID, while the second half is the model data.
s32 *D_8011D628;
s32 gModelCacheCount;
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

    gModelCache = mempool_alloc_safe(MODEL_LOADED_MAX * ((sizeof(uintptr_t)) * 2), COLOUR_TAG_GREEN);
    D_8011D628 = mempool_alloc_safe(100 * sizeof(uintptr_t), COLOUR_TAG_GREEN);
    gModelCacheCount = 0;
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
 * v79 and newer have a bugfix that revert the cache count if allocation fails.
 */
Object_68 *object_model_init(s32 modelID, s32 flags) {
    s32 i;
    s32 cacheIndex;
    ObjectModel *objMdl;
    s32 sp48;
    s32 temp_s0;
    Object_68 *ret;
    s8 sp3F;
#if VERSION >= VERSION_79
    s8 var_a2;
    s8 cacheChanged;
#endif
    u32 compressedData;
    s32 modelSize;

    if (modelID >= gNumModelIDs) {
        stubbed_printf(D_800E6B20);
        modelID = 0;
    }

    // Check if the model already exists in the cache.
    for (i = 0; i < gModelCacheCount; i++) {
        if (modelID == gModelCache[ASSETCACHE_ID(i)]) {
            objMdl = (ObjectModel *) gModelCache[ASSETCACHE_PTR(i)];
            ret = model_init_type(objMdl, flags);
            if (ret != NULL) {
                objMdl->references++;
            }
            return ret;
        }
    }

#if VERSION >= VERSION_79
    var_a2 = FALSE;
    cacheChanged = FALSE;
#endif
    if (D_8011D634 > 0) {
        D_8011D634--;
#if VERSION >= VERSION_79
        var_a2 = TRUE;
#endif
        cacheIndex = D_8011D628[D_8011D634];
    } else {
        cacheIndex = gModelCacheCount;
#if VERSION >= VERSION_79
        cacheChanged = TRUE;
#endif
        gModelCacheCount++;
    }

    temp_s0 = gObjectModelTable[modelID];
    sp48 = gObjectModelTable[modelID + 1] - temp_s0;
    modelSize = get_asset_uncompressed_size(ASSET_OBJECT_MODELS, temp_s0) + sizeof(ObjectModel);
    objMdl = (ObjectModel *) mempool_alloc(modelSize, COLOUR_TAG_RED);
    if (objMdl == NULL) {
#if VERSION >= VERSION_79
        if (var_a2) {
            D_8011D634++;
        }
        if (cacheChanged) {
            gModelCacheCount--;
        }
#endif
        return NULL;
    }
    compressedData = (u32) ((u8 *) objMdl + modelSize) - sp48;
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
    objMdl->texOffsetUpdateRate = 0;
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
            ret = model_init_type(objMdl, flags);
            if (ret != NULL) {
                gModelCache[ASSETCACHE_ID(cacheIndex)] = modelID;
                gModelCache[ASSETCACHE_PTR(cacheIndex)] = (s32) objMdl;
                if (gModelCacheCount < MODEL_LOADED_MAX) {
                    ret->animUpdateTimer = 0;
                    return ret;
                } else {
                    stubbed_printf(D_800E6B64);
                }
            }
        }
    }
block_30:
#if VERSION >= VERSION_79
    if (cacheChanged) {
        gModelCacheCount--;
    }
    if (var_a2) {
        D_8011D634++;
    }
#endif
    free_model_data((ObjectModel *) objMdl);
    return NULL;
}

Object_68 *model_init_type(ObjectModel *model, s32 flags) {
    s32 temp;
    Object_68 *result;
    Vertex *var_v1;
    Vertex *vertex;
    Vertex *mdlVertex;

    if ((model->numberOfAnimations != 0) && (flags & OBJECT_SPAWN_ANIMATION)) {
        temp = ((model->numberOfVertices * 2) * sizeof(Vertex)) + 36;
        result = (Object_68 *) mempool_alloc((model->unk4A * 6) + temp, COLOUR_TAG_BLUE);
        if (result == NULL) {
            return NULL;
        }
        result->vertices[0] = (Vertex *) ((u8 *) result + 36);
        result->vertices[1] = (Vertex *) ((u8 *) result + (model->numberOfVertices * sizeof(Vertex)) + 36);
        result->vertices[2] = (Vertex *) ((u8 *) result + temp);
        result->modelType = MODELTYPE_ANIMATED;
    } else if ((model->unk40 != NULL) && (flags & OBJECT_SPAWN_UNK01)) {
        temp = (model->numberOfVertices * sizeof(Vertex)) + 36;
        result = (Object_68 *) mempool_alloc(temp, COLOUR_TAG_BLUE);
        if (result == NULL) {
            return NULL;
        }
        var_v1 = (Vertex *) ((u8 *) result + 36);
        result->vertices[0] = var_v1;
        result->vertices[1] = var_v1;
        result->vertices[2] = NULL;
        result->modelType = MODELTYPE_SHADE;
    } else {
        result = (Object_68 *) mempool_alloc(36, COLOUR_TAG_BLUE);
        if (result == NULL) {
            return NULL;
        }
        result->vertices[0] = model->vertices;
        result->vertices[1] = model->vertices;
        result->vertices[2] = NULL;
        result->modelType = MODELTYPE_BASIC;
    }
    result->offsetX = 0;
    result->offsetY = 0;
    result->offsetZ = 0;
    result->objModel = model;
    result->animationID = -1;
    result->animationFrame = -1;
    result->animationTaskNum = 0;
    // Shaded models need to be double buffered, so duplicate them.
    if (result->modelType != MODELTYPE_BASIC) {
        temp = 0;
        vertex = result->vertices[0];
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
        vertex = result->vertices[1];
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

    if (modelPtr == 0) {
        stubbed_printf(D_800E6BC0);
        return;
    }

    model = *modelPtr;
    model->references--;
    if (model->references > 0) { // Model is still used, so free the reference and return.
        mempool_free(modelPtr);
        return;
    }

    modelIndex = -1;
    for (i = 0; i < gModelCacheCount; i++) {
        if (model == (ObjectModel *) gModelCache[ASSETCACHE_PTR(i)]) {
            modelIndex = i;
        }
    }

    if (modelIndex != -1) {
        free_model_data(model);
        D_8011D628[D_8011D634] = modelIndex;
        D_8011D634++;
        gModelCache[ASSETCACHE_ID(modelIndex)] = -1;
        gModelCache[ASSETCACHE_PTR(modelIndex)] = -1;
        mempool_free(modelPtr);
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
                tex_free(header);
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

// https://decomp.me/scratch/VJ34p
#ifdef NON_EQUIVALENT
void func_8006017C(ObjectModel *arg0) {
    s32 facesOffset;     // v1
    s32 verticesOffset;  // s5
    s32 nextFacesOffset; // spF4
    s32 s4;
    s32 i; // spEC
    s32 j; // s6
    Vertex *v;
    s32 v1, v2;
    f32 x5, y5, z5; // f20, f24, f26
    f32 x1, y1, z1; // spCC, spC8, spC4
    f32 x2, y2, z2; // f14, f16, f18
    f32 x3, y3, z3; // f22, spB0, f0
    f32 nx, ny, nz; // spA8, spA4, spA0
    f32 mag;
    s32 s3;
    s32 k;
    s32 l;
    s32 temp1, temp2, temp3;

    if (arg0->unkC != NULL) {
        return;
    }

    s4 = 0;
    for (i = 0; i < arg0->numberOfBatches; i++) {
        facesOffset = arg0->batches[i].facesOffset;
        nextFacesOffset = arg0->batches[i + 1].facesOffset;
        if (arg0->batches[i].flags & 0x200) {
            continue;
        }
        s4 += nextFacesOffset - facesOffset;
    }

    arg0->unkC = (ObjectModel_C *) mempool_alloc(s4 * sizeof(ObjectModel_C), COLOUR_TAG_RED);
    if (v) {} // FAKE
    if (arg0->unkC == NULL) {
        return;
    }

    arg0->unk10 = (ObjectModel_10 *) mempool_alloc(s4 * 64, COLOUR_TAG_RED);
    if (arg0->unk10 == NULL) {
        mempool_free(arg0->unkC);
        arg0->unkC = NULL;
        return;
    }

    s4 = 0;
    for (i = 0; i < arg0->numberOfBatches; i++) {
        facesOffset = arg0->batches[i].facesOffset;
        verticesOffset = arg0->batches[i].verticesOffset;
        nextFacesOffset = arg0->batches[i + 1].facesOffset;
        if (arg0->batches[i].flags & 0x200) {
            nextFacesOffset = facesOffset - 1;
        }

        for (j = facesOffset; j < nextFacesOffset; j++) {
            v = &arg0->vertices[arg0->triangles[j].vi0 + verticesOffset];
            x1 = v->x;
            y1 = v->y;
            z1 = v->z;

            v = &arg0->vertices[arg0->triangles[j].vi1 + verticesOffset];
            x2 = v->x;
            y2 = v->y;
            z2 = v->z;

            v = &arg0->vertices[arg0->triangles[j].vi2 + verticesOffset];
            x3 = v->x;
            y3 = v->y;
            z3 = v->z;

            nx = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
            ny = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
            nz = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);

            mag = sqrtf(nx * nx + ny * ny + nz * nz);
            if (mag > 0.0) {
                nx /= mag;
                ny /= mag;
                nz /= mag;
            }

            arg0->unk10[s4].A = nx;
            arg0->unk10[s4].B = ny;
            arg0->unk10[s4].C = nz;
            arg0->unk10[s4].D = -(x1 * nx + y1 * ny + z1 * nz);

            arg0->unkC[s4].unk0[0] = s4;
            arg0->unkC[s4].unk0[1] = s4;
            arg0->unkC[s4].unk0[2] = s4;
            arg0->unkC[s4].unk0[3] = s4;

            s4++;
        }
    }

    arg0->unk32 = s4;

    func_80060910(arg0);

    s3 = 0;
    for (i = 0; i < arg0->numberOfBatches; i++) {
        facesOffset = arg0->batches[i].facesOffset;
        verticesOffset = arg0->batches[i].verticesOffset;
        nextFacesOffset = arg0->batches[i + 1].facesOffset;
        if (arg0->batches[i].flags & 0x200) {
            nextFacesOffset = facesOffset - 1;
        }

        for (j = facesOffset; j < nextFacesOffset; j++) {
            nx = arg0->unk10[arg0->unkC[s3].unk0[0]].A;
            ny = arg0->unk10[arg0->unkC[s3].unk0[0]].B;
            nz = arg0->unk10[arg0->unkC[s3].unk0[0]].C;

            for (k = 0; k < 3; k++) {
                l = k + 1;
                if (l >= 3) {
                    l = 0;
                }

                v1 = arg0->triangles[j].verticesArray[1 + k];
                v2 = arg0->triangles[j].verticesArray[1 + l];

                x5 = nx + arg0->unk10[arg0->unkC[s3].unk0[l + 1]].A;
                y5 = ny + arg0->unk10[arg0->unkC[s3].unk0[l + 1]].B;
                z5 = nz + arg0->unk10[arg0->unkC[s3].unk0[l + 1]].C;

                v = &arg0->vertices[v1 + verticesOffset];
                x1 = v->x;
                y1 = v->y;
                z1 = v->z;

                v = &arg0->vertices[v2 + verticesOffset];
                x2 = v->x;
                y2 = v->y;
                z2 = v->z;

                x3 = x5 * 10.0f + x1;
                y3 = y5 * 10.0f + y1;
                z3 = z5 * 10.0f + z1;

                x5 = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
                y5 = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
                z5 = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);

                mag = sqrtf(x5 * x5 + y5 * y5 + z5 * z5);
                if (mag > 0.0) {
                    x5 /= mag;
                    y5 /= mag;
                    z5 /= mag;
                }

                arg0->unkC[s3].unk0[k + 1] = s4;
                arg0->unk10[s4].A = x5;
                arg0->unk10[s4].B = y5;
                arg0->unk10[s4].C = z5;
                arg0->unk10[s4].D = -(x1 * x5 + y1 * y5 + z1 * z5);
                s4++;
            }

            s3++;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/object_models/func_8006017C.s")
#endif

void func_80060910(ObjectModel *mdl) {
    s32 count;
    s32 i;
    s32 vertOffset;
    s32 triIndex;
    s32 startTri;
    s32 endTri;
    s32 nextVertIndex;
    s32 vertIndex;
    s32 vertIndex0;
    s32 vertIndex1;
    s32 result;
    s32 sp60;
    s32 sp5C;

    count = 0;
    for (i = 0; i < mdl->numberOfBatches; i++) {
        startTri = mdl->batches[i].facesOffset;
        vertOffset = mdl->batches[i].verticesOffset;
        endTri = mdl->batches[i + 1].facesOffset;
        if (mdl->batches[i].flags & RENDER_UNK_200) {
            endTri = startTri - 1;
        }

        for (triIndex = startTri; triIndex < endTri; triIndex++, count++) {
            mdl->unkC[count].unk0[0] = count;

            for (vertIndex = 0; vertIndex < 3; vertIndex++) {
                nextVertIndex = vertIndex + 1;
                if (nextVertIndex >= 3) {
                    nextVertIndex = 0;
                }

                vertIndex0 = mdl->triangles[triIndex].verticesArray[vertIndex + 1] + vertOffset;
                vertIndex1 = mdl->triangles[triIndex].verticesArray[nextVertIndex + 1] + vertOffset;

                result = func_80060AC8(mdl, triIndex, vertIndex0, vertIndex1, &sp5C, &sp60);
                if (result != -1) {
                    mdl->unkC[count].unk0[1 + vertIndex] = result;
                } else {
                    mdl->unkC[count].unk0[1 + vertIndex] = count;
                }
            }
        }
    }
}

s32 func_80060AC8(ObjectModel *mdl, s32 arg1, s32 arg2, s32 arg3, s32 *outBatchIndex, s32 *outVertexIndex) {
    s32 i;
    s32 endTri;
    s32 count;
    Triangle *tri;
    s16 vertOffset;
    s16 startTri;
    s32 triIndex;
    s32 nextVertIndex;
    s32 vertIndex;
    s32 vertIndex0;
    s32 vertIndex1;

    count = 0;
    for (i = 0; i < mdl->numberOfBatches; i++) {
        startTri = mdl->batches[i].facesOffset;
        vertOffset = mdl->batches[i].verticesOffset;
        endTri = mdl->batches[i + 1].facesOffset;
        if (mdl->batches[i].flags & RENDER_UNK_200) {
            endTri = startTri - 1;
        }
        for (triIndex = startTri; triIndex < endTri; triIndex++, count++) {
            if (triIndex != arg1) {
                for (vertIndex = 0; vertIndex < 3; vertIndex++) {
                    nextVertIndex = vertIndex + 1;
                    if (nextVertIndex >= 3) {
                        nextVertIndex = 0;
                    }

                    vertIndex0 = mdl->triangles[triIndex].verticesArray[vertIndex + 1] + vertOffset;
                    vertIndex1 = mdl->triangles[triIndex].verticesArray[nextVertIndex + 1] + vertOffset;
                    if (func_80060C58(mdl->vertices, arg2, arg3, vertIndex0, vertIndex1) != 0) {
                        *outVertexIndex = vertIndex;
                        *outBatchIndex = i;
                        return count;
                    }
                }
            }
        }
    }

    return -1;
}

s32 func_80060C58(Vertex *vertices, s32 i1, s32 i2, s32 i3, s32 i4) {
    Vertex *a;
    Vertex *b;
    Vertex *c;
    Vertex *d;

#define NEARBY(a, b, x) (b->x - 4 < a->x && a->x < b->x + 4)

    if ((i1 == i3 && i2 == i4) || (i1 == i4 && i2 == i3)) {
        return 1;
    }

    a = &vertices[i1];
    b = &vertices[i2];
    c = &vertices[i3];
    d = &vertices[i4];

    if (NEARBY(a, c, x) && NEARBY(a, c, y) && NEARBY(a, c, z)) {
        if (NEARBY(b, d, x) && NEARBY(b, d, y) && NEARBY(b, d, z)) {
            return 2;
        }
    } else if (NEARBY(a, d, x) && NEARBY(a, d, y) && NEARBY(a, d, z)) {
        if (NEARBY(b, c, x) && NEARBY(b, c, y) && NEARBY(b, c, z)) {
            return 2;
        }
    }

    return 0;

#undef NEARBY
}

s32 func_80060EA8(ObjectModel *model) {
    Vertex *vertices;           // s3
    Triangle *triangles;        // spB0
    Vec3f *spAC;                // spAC
    s16 i;                      // s1
    TriangleBatchInfo *batches; // spA4
    Vec3s *spA0;                // spA0
    s16 s6;
    s16 l;
    s16 q;
    s16 k; // sp98;
    s16 a2;
    s16 j; // s5
    s16 a0;
    s16 vertOffset;
    f32 length;
    Vec3f *v06;
    s16 *v0;
    s16 vx, vy, vz;

    batches = model->batches;
    model->unk40 = NULL;

    k = 0;
    for (i = 0; i < model->numberOfBatches; i++) {
        if (batches[i].miscData != BATCH_VTX_COL || (batches[i].flags & RENDER_ENVMAP)) {
            k += batches[i + 1].verticesOffset - batches[i].verticesOffset;
        }
    }

    if (k > 0) {
        vertices = model->vertices;
        triangles = model->triangles;

        spAC = (Vec3f *) mempool_alloc(model->numberOfTriangles * sizeof(Vec3f), COLOUR_TAG_ORANGE);
        if (spAC == NULL) {
            return 1;
        }

        spA0 = (Vec3s *) mempool_alloc(k * sizeof(Vec3s), COLOUR_TAG_ORANGE);
        if (spA0 == NULL) {
            mempool_free(spAC);
            return 1;
        }

        for (i = 0; i < model->numberOfBatches; i++) {
            vertOffset = batches[i].verticesOffset;
            for (j = batches[i].facesOffset; j < batches[i + 1].facesOffset; j++) {
                f32 sp70[3];
                f32 sp64[3];
                f32 sp58[3];
                for (k = 0; k < 3; k++) {
                    a2 = triangles[j].verticesArray[k + 1] + vertOffset;
                    sp70[k] = vertices[a2].x;
                    sp64[k] = vertices[a2].y;
                    sp58[k] = vertices[a2].z;
                }

                spAC[j].x = (sp58[0] - sp58[2]) * (sp64[0] - sp64[1]) - (sp64[0] - sp64[2]) * (sp58[0] - sp58[1]);
                spAC[j].y = (sp58[0] - sp58[1]) * (sp70[0] - sp70[2]) - (sp70[0] - sp70[1]) * (sp58[0] - sp58[2]);
                spAC[j].z = (sp70[0] - sp70[1]) * (sp64[0] - sp64[2]) - (sp70[0] - sp70[2]) * (sp64[0] - sp64[1]);
                length = sqrtf(spAC[j].x * spAC[j].x + spAC[j].y * spAC[j].y + spAC[j].z * spAC[j].z);
                if (length != 0.0f) {
                    spAC[j].x /= length;
                    spAC[j].y /= length;
                    spAC[j].z /= length;
                }
            }
        }

        v0 = (s16 *) mempool_alloc(model->numberOfVertices * sizeof(s16), COLOUR_TAG_ORANGE);
        if (v0 == NULL) {
            mempool_free(spAC);
            mempool_free(spA0);
            return 1;
        }

        s6 = 0;

        for (i = 0; i < model->numberOfBatches; i++) {
            for (l = batches[i].verticesOffset; l < batches[i + 1].verticesOffset; l++) {
                if (batches[i].miscData < 0xFE) {
                    a2 = -1;
                    vx = vertices[l].x;
                    vy = vertices[l].y;
                    vz = vertices[l].z;

                    for (q = 0; q <= i && a2 < 0; q++) {
                        if (batches[i].miscData == batches[q].miscData) {
                            a0 = batches[q].verticesOffset;
                            while (((q == i && a0 < l) || (q != i && a0 < batches[q + 1].verticesOffset)) && a2 < 0) {
                                if (vx == vertices[a0].x && vy == vertices[a0].y && vz == vertices[a0].z) {
                                    a2 = v0[a0];
                                }
                                a0++;
                            }
                        }
                    }
                    if (a2 < 0) {
                        v0[l] = s6++;
                    } else {
                        v0[l] = a2;
                    }
                } else if (batches[i].miscData == 0xFE) {
                    v0[l] = s6++;
                } else if (batches[i].flags & RENDER_ENVMAP) {
                    a2 = -1;
                    vx = vertices[l].x;
                    vy = vertices[l].y;
                    vz = vertices[l].z;
                    for (q = 0; q <= i && a2 < 0; q++) {
                        if (batches[q].flags & RENDER_ENVMAP) {
                            a0 = batches[q].verticesOffset;
                            while (((q == i && a0 < l) || (q != i && a0 < batches[q + 1].verticesOffset)) && a2 < 0) {
                                if (vx == vertices[a0].x && vy == vertices[a0].y && vz == vertices[a0].z) {
                                    a2 = v0[a0];
                                }
                                a0++;
                            }
                        }
                    }

                    if (a2 < 0) {
                        v0[l] = s6++;
                    } else {
                        v0[l] = a2;
                    }
                } else {
                    v0[l] = -1;
                }
            }
        }

        v06 = (Vec3f *) mempool_alloc(s6 * sizeof(Vec3f), COLOUR_TAG_ORANGE);
        if (v06 == NULL) {
            mempool_free(spAC);
            mempool_free(spA0);
            mempool_free(v0);
            return 1;
        }

        for (k = 0; k < s6; k++) {
            v06[k].x = 0.0f;
            v06[k].y = 0.0f;
            v06[k].z = 0.0f;
        }

        for (i = 0; i < model->numberOfBatches; i++) {
            if (batches[i].miscData != BATCH_VTX_COL || (batches[i].flags & RENDER_ENVMAP)) {
                vertOffset = batches[i].verticesOffset;
                for (j = batches[i].facesOffset; j < batches[i + 1].facesOffset; j++) {
                    for (k = 0; k < 3; k++) {
                        a2 = triangles[j].verticesArray[k + 1] + vertOffset;
                        a2 = v0[a2];

                        if (a2 >= 0) {
                            v06[a2].x += spAC[j].x;
                            v06[a2].y += spAC[j].y;
                            v06[a2].z += spAC[j].z;
                        }
                    }
                }
            }
        }

        for (k = 0; k < s6; k++) {
            length = sqrtf(v06[k].x * v06[k].x + v06[k].y * v06[k].y + v06[k].z * v06[k].z);
            if (length != 0.0f) {
                v06[k].x /= length * (1.0f / 0x2000);
                v06[k].y /= length * (1.0f / 0x2000);
                v06[k].z /= length * (1.0f / 0x2000);
            }
        }

        a0 = 0;
        for (k = 0; k < model->numberOfVertices; k++) {
            a2 = v0[k];
            if (a2 >= 0) {
                spA0[a0].x = v06[a2].x;
                spA0[a0].y = v06[a2].y;
                spA0[a0].z = v06[a2].z;
                a0++;
            }
        }

        model->unk40 = spA0;
        mempool_free(v0);
        mempool_free(v06);
        mempool_free(spAC);
    }
    return 0;
}

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
        model->animations[i].animLength = *temp;
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
            var_v1 = mdl->animations[obj->segment.object.animationID].animLength - 2;
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
