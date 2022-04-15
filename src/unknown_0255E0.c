/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800249E0 */

#include "unknown_0255E0.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "PR/gu.h"
#include "textures_sprites.h"
#include "objects.h"
#include "game.h"
#include "memory.h"
#include "racer.h"
#include "camera.h"
#include "waves.h"

/************ .data ************/

s32 D_800DC870 = 0; // Currently unknown, might be a different type.
unknown800DC874 D_800DC874 = { { -128 }, 40, -1 };
unknown800DC874 D_800DC87C = { { -125 }, 70, -1 };

f32 D_800DC884[10] = {
    0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f
};

f32 D_800DC8AC[27] = {
    50.0f, 0.0f, 32.0f, -50.0f,
    0.0f, 32.0f, -50.0f, 100.0f,
    32.0f, 0.0f, 0.0f, 32.0f,
    130.0f, 60.0f, -68.0f, 130.0f,
    -60.0f, -68.0f, 0.0f, 0.0f,
    32.0f, -130.0f, -60.0f, -68.0f,
    -130.0f, 60.0f, -68.0f,
};

LevelModel *gCurrentLevelModel = NULL;
LevelHeader *gCurrentLevelHeader2 = NULL;

s32 D_800DC920 = -1;
s32 *D_800DC924 = NULL;
s32 D_800DC928 = 0; // Currently unknown, might be a different type.

s8 D_800DC92C[24] = {
    0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4, 5, 6, 1, 1, 0, 5, 3, 2, 7, 7, 8, 3
    // There may or may not be extra zeroes here.
};

/*******************************/

/************ .rodata ************/

const char D_800E5DF0[] = "TT CAM";
const char D_800E5DF8[] = "Solid Clipping x0=x1 Error!!!\n";
const char D_800E5E10[] = "TrackGetHeight() - Overflow!!!\n";

/*********************************/

/************ .bss ************/

Gfx *D_8011B0A0;
Mtx *D_8011B0A4;
VertexList *D_8011B0A8;
TriangleList *D_8011B0AC;

Object *D_8011B0B0; // Camera Object?

s32 D_8011B0B4;
Object *D_8011B0B8;
s32 D_8011B0BC;
s32 D_8011B0C0;
s32 D_8011B0C4;
s32 D_8011B0C8;
s32 D_8011B0CC;
s32 D_8011B0D0;
s32 D_8011B0D4;
s32 D_8011B0D8;
s32 D_8011B0DC;
s8 D_8011B0E0;
u8 D_8011B0E1;
u8 D_8011B0E2;
u8 D_8011B0E3;
f32 D_8011B0E4;
f32 D_8011B0E8;
f32 D_8011B0EC;
s32 D_8011B0F0;
s32 D_8011B0F4;
s32 D_8011B0F8;
s32 D_8011B0FC;
s32 D_8011B100;
s32 D_8011B104;
s32 D_8011B108;
s32 D_8011B10C;
s32 D_8011B110;
s32 D_8011B114;
s32 D_8011B118;
s32 D_8011B11C;
s32 D_8011B120[128];
s32 D_8011B320[4];
s32 D_8011B330[960];
s32 D_8011C230[2];
s32 D_8011C238[96];
s32 D_8011C3B8[320];
s32 D_8011C8B8[512];
s32 D_8011D0B8;
s32 D_8011D0BC;
s32 D_8011D0C0;
s32 D_8011D0C4;
s32 D_8011D0C8;
s16 D_8011D0CC;
s16 D_8011D0CE;
s32 D_8011D0D0;
s32 D_8011D0D4;
s32 D_8011D0D8;
s32 D_8011D0DC;
s32 D_8011D0E0;
s32 D_8011D0E4;
s32 D_8011D0E8;
s32 D_8011D0EC;
s32 D_8011D0F0;
s32 D_8011D0F4;
unk8011D0F8 D_8011D0F8[3];
unk8011D0F8 D_8011D128[3];
s32 D_8011D158[3]; // Unused? Or part of something bigger above?
s32 D_8011D164;
s32 D_8011D168[84];
s32 D_8011D2B8[20];
s32 D_8011D308;
LevelModel *D_8011D30C;
s32 *D_8011D310;
s32 D_8011D314;
s32 D_8011D318;
s32 D_8011D31C;
s32 D_8011D320[4];
unk8011D330 *D_8011D330;
s32 D_8011D334;
s32 D_8011D338[4];
unk8011D348 *D_8011D348;
s32 D_8011D34C;
s32 D_8011D350[4];
unk8011D360 *D_8011D360;
s32 D_8011D364;
s32 D_8011D368;
s32 D_8011D36C;
s32 *D_8011D370;
s32 *D_8011D374;
s32 D_8011D378;
s32 D_8011D37C;
f32 D_8011D380;
u32 D_8011D384;
unk8011D388 D_8011D388[4];
unk8011D468 D_8011D468;
s32 *D_8011D474;
s32 D_8011D478;
s32 D_8011D47C;
s32 D_8011D480[2];
Vertex **D_8011D488;
s32 D_8011D48C;
s32 D_8011D490[2];
Vertex **D_8011D498;
s16 D_8011D49C;
s16 D_8011D49E;
f32 D_8011D4A0;
f32 D_8011D4A4;
f32 D_8011D4A8;
f32 D_8011D4AC;
f32 D_8011D4B0;
s8 D_8011D4B4;
s16 D_8011D4B6;
s16 D_8011D4B8;
s16 D_8011D4BA;
s32 D_8011D4BC;

/******************************/

s32 func_800249E0(s32 arg0) {
    D_8011D37C = arg0;
    return 0;
}

#ifdef NON_EQUIVALENT
void func_8002C0C4(s32 modelId);
void func_800249F0(u32 arg0, u32 arg1, s32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6) {
    s32 i;
    s32 tmp_a2;

    gCurrentLevelHeader2 = get_current_level_header();
    D_8011B0F8 = 0;
    D_8011B100 = 0;
    D_8011B104 = 0;
    D_8011B108 = 0;
    D_8011B10C = 0;
    if (gCurrentLevelHeader2->race_type == RACE_TYPE_CUTSCENE_1 || gCurrentLevelHeader2->race_type == RACE_TYPE_CUTSCENE_2) {
        D_8011B0F8 = 1;
    }
    func_8002C0C4(arg0);

    if (arg2 < 2) {
        D_8011D384 = 0;
        for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
            if (gCurrentLevelModel->segments[i].unk2B != 0) {
                D_8011D384++;
                gCurrentLevelModel->segments[i].unk2B = 1;
            }
        }
    }
    if (is_in_two_player_adventure() && (gCurrentLevelHeader2->race_type == RACE_TYPE_DEFAULT || gCurrentLevelHeader2->race_type & RACE_TYPE_CHALLENGE)) {
        tmp_a2 = 2;
    } else {
        tmp_a2 = arg2;
        tmp_a2++;
    }
    if (D_8011D384) {
        func_800B82B4(gCurrentLevelModel, gCurrentLevelHeader2, tmp_a2);
    }
    func_8006652C(arg2);
    func_80027FC4(arg1);
    D_8011B110 = 0;
    D_8011B114 = 0x10000;
    func_80011390();
    func_8000C8F8(arg6, 0);
    func_8000C8F8(arg5, 1);
    D_8011D37C = arg2;
    func_8000CC7C(arg3, arg4, arg2);
    func_8000B020(72, 64);
    if (arg0 == 0 && arg4 == 0) {
        func_800C01D8(&D_800DC87C);
    } else {
        func_800C01D8(&D_800DC874);
    }
    func_8006652C(D_8011D37C);
    D_8011B0FC = 0;
    i = 0;
    do {
        D_8011D350[i] = allocate_from_main_pool_safe(3200, COLOUR_TAG_YELLOW);
        D_8011D320[i] = allocate_from_main_pool_safe(12800, COLOUR_TAG_YELLOW);
        D_8011D338[i] = allocate_from_main_pool_safe(20000, COLOUR_TAG_YELLOW);
    } while ((s32)&D_8011D338[++i] != (s32)&D_8011D348);

    D_8011B0C8 = 0;
    func_8002D8DC(1, 1, 0);
    func_8002D8DC(2, 2, 0);
    D_8011B0C8 = 1;
    func_8002D8DC(1, 1, 0);
    func_8002D8DC(2, 2, 0);
    D_8011B0C8 = 0;
    if (gCurrentLevelHeader2->unkB7) {
        D_8011B0E1 = gCurrentLevelHeader2->unkB4;
        D_8011B0E2 = gCurrentLevelHeader2->unkB5;
        D_8011B0E3 = gCurrentLevelHeader2->unkB6;
        func_80025510(arg2 + 1);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800249F0.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80024D54.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80025510.s")

void func_800257D0(void) {
    if (D_800DC924 != 0) {
        free_from_memory_pool(D_8011D474);
        free_from_memory_pool(D_800DC924);
        D_800DC924 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002581C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026070.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026430.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026C14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026E54.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027184.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027568.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800278E8.s")

void func_80027E24(s32 arg0) {
    s32 segmentNumber, batchNumber;
    LevelModelSegment *segment;
    TextureHeader *texture;
    TriangleBatchInfo *batch;
    s32 temp;

    segment = gCurrentLevelModel->segments;
    for (segmentNumber = 0; segmentNumber < gCurrentLevelModel->numberOfSegments; segmentNumber++) {
        batch = segment[segmentNumber].batches;
        for (batchNumber = 0; batchNumber < segment[segmentNumber].numberOfBatches; batchNumber++) {
            if (batch[batchNumber].flags & 0x10000) {
                if (batch[batchNumber].textureIndex != 0xFF) {
                    texture = gCurrentLevelModel->textures[batch[batchNumber].textureIndex].texture;
                    if ((texture->numOfTextures != 0x100) && (texture->frameAdvanceDelay != 0)) {
                        temp = batch[batchNumber].unk7 << 6;
                        if (batch[batchNumber].flags & 0x80000000) {
                            temp |= batch[batchNumber].unk6;
                            func_8007EF80(texture, &batch[batchNumber].flags, &temp, arg0);
                            batch[batchNumber].unk6 = temp & 0x3F;
                        } else {
                            func_8007EF80(texture, &batch[batchNumber].flags, &temp, arg0);
                        }
                        batch[batchNumber].unk7 = (temp >> 6) & 0xFF;
                    }
                }
            }
        }
    }
}

void func_80027FC4(s32 arg0) {
    unk80027FC4 sp20;

    func_8005A3D0();
    if (arg0 == -1) {
        D_8011B0B8 = NULL;
        return;
    }
    sp20.unk2 = 0;
    sp20.unk4 = 0;
    sp20.unk6 = 0;
    sp20.unk1 = 8;
    sp20.unk0 = arg0;
    D_8011B0B8 = spawn_object(&sp20, 2);
    if (D_8011B0B8 != 0) {
        D_8011B0B8->segment.unk3C_a.unk3C = 0;
        D_8011B0B8->unk4A = -1;
    }
}

void func_80028044(s32 arg0) {
    D_8011B0DC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028050.s")

#ifdef NON_EQUIVALENT
void func_800289B8(void) {
    u8 sp_2f = gCurrentLevelHeader2->unkC1;
    u8 sp_2e = gCurrentLevelHeader2->unkC2;
    u8 sp_2d = gCurrentLevelHeader2->unkC3;
    u8 sp_2c = gCurrentLevelHeader2->unkBE;
    u8 sp_2b = gCurrentLevelHeader2->unkBF;
    u8 sp_2a = gCurrentLevelHeader2->unkC0;
    u32 sp_24 = D_8011B0A8;
    func_8007B3D0(&D_8011B0A0);
    func_8007B4C8(&D_8011B0A0, 0, 8);
    D_8011B0A0 += 8;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800289B8.s")
#endif

void render_skydome(void) {
    ObjectSegment *v0_some_struct;
    if (D_8011B0B8 == NULL)
        return;

    v0_some_struct = func_80069D20();
    if (gCurrentLevelHeader2->unk49 == 0) {
        D_8011B0B8->segment.trans.x_position = v0_some_struct->trans.x_position;
        D_8011B0B8->segment.trans.y_position = v0_some_struct->trans.y_position;
        D_8011B0B8->segment.trans.z_position = v0_some_struct->trans.z_position;
    }

    func_80068408(&D_8011B0A0, &D_8011B0A4);
    if (D_8011B0DC) {
        func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, D_8011B0B8);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028CD0.s")

void func_80028FA0(s32 arg0) {
    D_8011B0FC = arg0;
}

void render_level_geometry_and_objects(void) {
    s32 sp16C;
    s32 numberOfSegments;
    s32 objFlags;
    s32 sp160;
    s32 i;
    s32 sp158;
    u8 segmentIds[128];
    u8 sp58[128];
    s32 s0;
    Object *obj;

    func_80012C30();

    if (get_settings()->courseId == 0x24) { // 0x24 = Opening sequence area
        D_8011B0FC = 1;
    }

    sp160 = func_80014814(&sp16C);

    if (gCurrentLevelModel->numberOfSegments > 1) {
        numberOfSegments = 0;
        traverse_segments_bsp_tree(0, 0, gCurrentLevelModel->numberOfSegments - 1, segmentIds, &numberOfSegments);
    } else {
        numberOfSegments = 1;
        segmentIds[0] = 0;
    }

    for (i = 1; i <= gCurrentLevelModel->numberOfSegments; i++) {
        sp58[i] = FALSE;
    }

    sp58[0] = TRUE;

    if (D_8011B0E0 != 0) {
        for (i = 0; i < numberOfSegments; i++) {
            render_level_segment(segmentIds[i], 0); // Render opaque segments
            sp58[segmentIds[i] + 1] = TRUE;
        }
    }

    if (gCurrentLevelModel->numberOfSegments < 2) {
        sp58[1] = TRUE;
    }

    func_8007B3D0(&D_8011B0A0);
    func_80015348(sp160, sp16C - 1);
    sp158 = 0x200 << (func_80066220() & 1);

    for (i = sp160; i < sp16C; i++) {
        obj = get_object(i);
        s0 = 0xFF;
        objFlags = obj->segment.trans.unk6;
        if (objFlags & 0x80) {
            s0 = 0;
        } else if (!(objFlags & 0x8000)) {
            s0 = obj->segment.unk38.half.lower;
        }
        if (objFlags & sp158) {
            s0 = 0;
        }
        if ((obj != NULL) && (s0 == 0xFF) && (func_8002A900(obj)) && ((sp58[obj->segment.unk2C.half.lower + 1]) || (1000.0 < obj->segment.unk34_a.unk34))) {
            if (obj->segment.trans.unk6 & 0x8000) {
                func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                continue;
            } else if (obj->unk50 != NULL) {
                render_floor_decal(obj, obj->unk50);
            }
            func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
            if ((obj->unk58 != NULL) && (obj->segment.header->unk30 & 0x10)) {
                func_8002D670(obj, obj->unk58);
            }
        }
    }

    for (i = sp16C - 1; i >= sp160; i--) {
        obj = get_object(i);
        objFlags = obj->segment.trans.unk6;
        if (objFlags & sp158) {
            s0 = FALSE;
        } else {
            s0 = TRUE;
        }
        if (obj != NULL && s0 && (objFlags & 0x100) && (sp58[obj->segment.unk2C.half.lower + 1]) && (func_8002A900(obj) != 0)) {
            if (obj->segment.trans.unk6 & 0x8000) {
                func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                continue;
            } else if (obj->unk50 != NULL) {
                render_floor_decal(obj, obj->unk50);
            }
            func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
            if ((obj->unk58 != NULL) && (obj->segment.header->unk30 & 0x10)) {
                func_8002D670(obj, obj->unk58);
            }
        }
    }

    if (D_8011B0E0 != 0) {
        for (i = numberOfSegments - 1; i >= 0; i--) {
            render_level_segment(segmentIds[i], 1); // Render transparent segments
        }
    }

    if (D_8011D384 != 0) {
        func_800BA8E4(&D_8011B0A0, &D_8011B0A4, func_80066220());
    }

    func_8007B3D0(&D_8011B0A0);
    func_8007B4C8(&D_8011B0A0, 0, 0xA);
    func_80012C3C(&D_8011B0A0);

    for (i = sp16C - 1; i >= sp160; i--) {
        obj = get_object(i);
        s0 = 0xFF;
        objFlags = obj->segment.trans.unk6;
        if (objFlags & 0x80) {
            s0 = 1;
        } else if (!(objFlags & 0x8000)) {
            s0 = obj->segment.unk38.half.lower;
        }
        if (objFlags & sp158) {
            s0 = 0;
        }
        if ((obj->behaviorId == 1) && (s0 >= 0xFF)) {
            s0 = 0;
        }
        if (obj != NULL && s0 < 0xFF && sp58[obj->segment.unk2C.half.lower + 1] && func_8002A900(obj)) {
            if (s0 > 0) {
                if (obj->segment.trans.unk6 & 0x8000) {
                    func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                    goto skip;
                } else if (obj->unk50 != NULL) {
                    render_floor_decal(obj, obj->unk50);
                }
                func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                if ((obj->unk58 != 0) && (obj->segment.header->unk30 & 0x10)) {
                    func_8002D670(obj, obj->unk58);
                }
            }
skip:
            if (obj->behaviorId == 1) {
                func_80013A0C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                func_80013DCC(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
            }
        }
    }

    if (D_800DC924 && func_80027568()) {
        func_8002581C(segmentIds, numberOfSegments, func_80066220());
    }
    D_8011B0FC = 0;
}

#ifdef NON_EQUIVALENT
// nonOpaque: 0 for solid geometry, 1 for transparent geometry.
void render_level_segment(s32 segmentId, s32 nonOpaque) {
    LevelModelSegment *segment;
    LevelHeader_70 *lvlHeader70;
    TriangleBatchInfo *batchInfo;
    TextureHeader *texture;
    s32 renderBatch;
    s16 numberVertices;
    s16 numberTriangles;
    s32 vertices;
    s32 triangles;
    s32 color;
    s32 hasTexture;
    s32 levelHeaderIndex;
    s32 sp78;
    s32 i;
    s32 sp70;
    s16 textureFlags;
    u8 textureIndex;
    s32 temp;

    segment = &gCurrentLevelModel->segments[segmentId];
    sp78 = (nonOpaque && D_8011D384) ? func_800B9228(segment) : FALSE;

    if (nonOpaque) {
        sp70 = segment->numberOfBatches;
        i = segment->unk40;
    } else {
        sp70 = segment->unk40;
        i = 0;
    }

    for (; i < sp70; i++) {
        batchInfo = &segment->batches[i];
        textureFlags = 0;
        if (!(batchInfo->flags & 0x100)) { // 0x100 = Is this invisible geometry?
            textureIndex = batchInfo->textureIndex;
            renderBatch = FALSE;
            if (textureIndex == 0xFF) {
                texture = NULL; // Solid color only
            } else {
                texture = gCurrentLevelModel->textures[textureIndex].texture;
                textureFlags = texture->flags;
            }
            batchInfo->flags |= (0x8 | 0x2);
            if (!(batchInfo->flags & 0x10) && !(batchInfo->flags & 0x800)) { // 0x10 = Depth write
                batchInfo->flags |= D_8011B0FC;
            }
            // textureFlags & 0x04 = Is interlaced texture
            if ((!(textureFlags & 4) && !(batchInfo->flags & 0x2000)) || (batchInfo->flags & 0x800)) {
                renderBatch = TRUE;
            }
            if (nonOpaque) {
                renderBatch = (renderBatch + 1) & 1; // Why not just do `renderBatch ^= 1;` or `renderBatch = !renderBatch`?
            }
            if (sp78 && (batchInfo->flags & 0x2000)) {
                renderBatch = FALSE;
            }
            if (renderBatch) {
                numberVertices = (batchInfo + 1)->verticesOffset - batchInfo->verticesOffset;
                numberTriangles = (batchInfo + 1)->facesOffset - batchInfo->facesOffset;
                vertices = &segment->vertices[batchInfo->verticesOffset];
                triangles = &segment->triangles[batchInfo->facesOffset];
                levelHeaderIndex = (batchInfo->flags >> 28) & 7;
                temp = batchInfo->unk7 << 14;
                if (levelHeaderIndex != 0) {                   // This is unused, so this should always be false.
                    lvlHeader70 = gCurrentLevelHeader2[levelHeaderIndex << 2].unk70;
                    gDPSetEnvColor(D_8011B0A0++, lvlHeader70->red, lvlHeader70->green, lvlHeader70->blue, lvlHeader70->alpha);
                } else {
                    gDPSetEnvColor(D_8011B0A0++, 255, 255, 255, 0);
                }
                if (batchInfo->flags & 0x40000) { // Only gets used in Spaceport alpha for the pulsating lights in the outside section.
                    color = gCurrentLevelHeader2->pulseLightData->outColorValue & 0xFF;
                    gDPSetPrimColor(D_8011B0A0++, 0, 0, color, color, color, color);
                    func_8007BA5C(&D_8011B0A0, texture, batchInfo->flags, temp);
                    gDkrVertices(D_8011B0A0++, OS_PHYSICAL_TO_K0(vertices), (((numberVertices - 1) << 3) | ((s32)OS_PHYSICAL_TO_K0(vertices) & 6)), numberVertices);
                    gDkrTriangles(D_8011B0A0++, OS_PHYSICAL_TO_K0(triangles), numberTriangles, TRIN_ENABLE_TEXTURE);
                    gDPSetPrimColor(D_8011B0A0++, 0, 0, 255, 255, 255, 255); // Reset the primitive color
                } else {
                    func_8007B4E8(&D_8011B0A0, texture, batchInfo->flags, temp);
                    hasTexture = (texture == NULL) ? TRIN_DISABLE_TEXTURE : TRIN_ENABLE_TEXTURE;
                    gDkrVertices(D_8011B0A0++, OS_PHYSICAL_TO_K0(vertices), ((numberVertices - 1) << 3) | ((s32)OS_PHYSICAL_TO_K0(vertices) & 6), numberVertices);
                    gDkrTriangles(D_8011B0A0++, OS_PHYSICAL_TO_K0(triangles), numberTriangles, hasTexture);
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/render_level_segment.s")
#endif

void traverse_segments_bsp_tree(s32 nodeIndex, s32 segmentIndex, s32 segmentIndex2, u8 *segmentsOrder, s32 *segmentsOrderIndex) {
    BspTreeNode *curNode;
    s32 camValue;

    curNode = &gCurrentLevelModel->segmentsBspTree[nodeIndex];
    if (curNode->splitType == 0) {
        camValue = D_8011B0B0->segment.trans.x_position; // Camera X
    } else if (curNode->splitType == 1) {
        camValue = D_8011B0B0->segment.trans.y_position; // Camera Y
    } else {
        camValue = D_8011B0B0->segment.trans.z_position; // Camera Z
    }

    if (camValue < curNode->splitValue) {
        if (curNode->leftNode != -1) {
            traverse_segments_bsp_tree(curNode->leftNode, segmentIndex, curNode->segmentIndex - 1, segmentsOrder, segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex, segmentsOrderIndex, segmentsOrder);
        }

        if (curNode->rightNode != -1) {
            traverse_segments_bsp_tree(curNode->rightNode, curNode->segmentIndex, segmentIndex2, segmentsOrder, segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex2, segmentsOrderIndex, segmentsOrder);
        }
    } else {
        if (curNode->rightNode != -1) {
            traverse_segments_bsp_tree(curNode->rightNode, curNode->segmentIndex, segmentIndex2, segmentsOrder, segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex2, segmentsOrderIndex, segmentsOrder);
        }

        if (curNode->leftNode != -1) {
            traverse_segments_bsp_tree(curNode->leftNode, segmentIndex, curNode->segmentIndex - 1, segmentsOrder, segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex, segmentsOrderIndex, segmentsOrder);
        }
    }
}

void add_segment_to_order(s32 segmentIndex, s32 *segmentsOrderIndex, u8 *segmentsOrder) {
    u32 temp;
    if (segmentIndex < gCurrentLevelModel->numberOfSegments) {
        if (D_8011B0D4 != -1) {
            temp = gCurrentLevelModel->segmentsBitfields[D_8011B0D4 + (segmentIndex >> 3)];
            temp >>= segmentIndex & 7;
            temp &= 0xFF;
        } else {
            temp = 1;
        }
        if ((temp & 1) && func_8002A5F8(&gCurrentLevelModel->segmentsBoundingBoxes[segmentIndex])) {
            segmentsOrder[(*segmentsOrderIndex)++] = segmentIndex;
        }
    }
}

UNUSED s32 func_80029DE0(Object *obj, s32 segmentIndex) {
    LevelModelSegmentBoundingBox *bb;
    s32 x, y, z;
    if (segmentIndex >= gCurrentLevelModel->numberOfSegments) {
        return FALSE;
    }
    bb = &gCurrentLevelModel->segmentsBoundingBoxes[segmentIndex];
    x = obj->segment.trans.x_position;
    y = obj->segment.trans.y_position;
    z = obj->segment.trans.z_position;
    if ((x < (bb->x2 + 25)) && ((bb->x1 - 25) < x) &&
        (z < (bb->z2 + 25)) && ((bb->z1 - 25) < z) &&
        (y < (bb->y2 + 25)) && ((bb->y1 - 25) < y)) {
        return TRUE;
    }

    return FALSE;
}

s32 get_level_segment_index_from_position(f32 xPos, f32 yPos, f32 zPos) {
    LevelModelSegmentBoundingBox *bb;
    s32 i;
    s32 z = zPos;
    s32 x = xPos;
    s32 y = yPos;
    s32 minVal;
    s32 result;
    s32 heightDiff;

    if (gCurrentLevelModel == NULL) {
        return -1;
    }

    minVal = 1000000;
    result = -1;

    for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        bb = &gCurrentLevelModel->segmentsBoundingBoxes[i];
        if ((x < bb->x2) && (bb->x1 < x) && (z < bb->z2) && (bb->z1 < z)) {
            heightDiff = (bb->y2 + bb->y1) >> 1; // Couldn't get / 2 to match, but >> 1 does.
            heightDiff = y - heightDiff;
            if (heightDiff < 0) {
                heightDiff = -heightDiff;
            }
            if (heightDiff < minVal) {
                minVal = heightDiff;
                result = i;
            }
        }
    }

    return result;
}

s32 func_8002A05C(s32 x, s32 z, s32 *arg2) {
    s32 i;
    s32 cnt = 0;
    LevelModelSegmentBoundingBox *bb;
    for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        bb = gCurrentLevelModel->segmentsBoundingBoxes + i;
        if (x < bb->x2 + 4 && bb->x1 - 4 < x
         && z < bb->z2 + 4 && bb->z1 - 4 < z) {
            *arg2 = i;
            cnt++;
            arg2++;
        }
    }
    return cnt;
}

s32 func_8002A134(s32 *arg0, s16 xPos1, s16 yPos1, s16 zPos1, s16 xPos2, s16 yPos2, s16 zPos2) {
    s32 ret;
    s32 i;
    LevelModelSegmentBoundingBox *bb;

    xPos1 -= 4;
    yPos1 -= 4;
    zPos1 -= 4;
    xPos2 += 4;
    yPos2 += 4;
    zPos2 += 4;

    i = 0;
    ret = 0;

    while (i < gCurrentLevelModel->numberOfSegments) {
        bb = &gCurrentLevelModel->segmentsBoundingBoxes[i];
        if ((bb->x2 >= xPos1) && (xPos2 >= bb->x1) &&
            (bb->z2 >= zPos1) && (zPos2 >= bb->z1) &&
            (bb->y2 >= yPos1) && (yPos2 >= bb->y1)) {
            ret++;
            *arg0++ = i;
        }
        i++;
    }

    return ret;
}

LevelModelSegment *func_8002A2C8(s32 arg0) {
    if (arg0 < 0 || gCurrentLevelModel->numberOfSegments < arg0)
        return NULL;

    return gCurrentLevelModel->segments + arg0;
}

LevelModelSegmentBoundingBox *func_8002A2DC(s32 arg0) {
    if (arg0 < 0 || gCurrentLevelModel->numberOfSegments < arg0)
        return NULL;

    return gCurrentLevelModel->segmentsBoundingBoxes + arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A31C.s")

#ifdef NON_EQUIVALENT
// Has some minor issues, but should be functionally equivalent.
s32 func_8002A5F8(LevelModelSegmentBoundingBox *bb) {
    s64 sp48;
    s32 i, j;
    s32 s2;
    f32 temp0, temp1, temp2, temp3;

    j = 0;
    while (TRUE) {
        temp0 = D_8011D0F8[j].unk0;
        temp1 = D_8011D0F8[j].unk4;
        temp2 = D_8011D0F8[j].unk8;
        temp3 = D_8011D0F8[j].unkC;
        i = 0;
        s2 = FALSE;
        while (i < 8 && !s2) {
            if (i & 1) {
                sp48 = bb->x1 * temp0;
            } else {
                sp48 = bb->x2 * temp0;
            }
            if (i & 2) {
                sp48 += bb->y1 * temp1;
            } else {
                sp48 += bb->y2 * temp1;
            }
            if (i & 4) {
                sp48 += bb->z1 * temp2;
            } else {
                sp48 += bb->z2 * temp2;
            }
            sp48 += temp3;
            if (sp48 > 0) {
                s2 = TRUE;
            }
            i++;
        }
        j++;
        if (i == 8 && !s2) {
            return FALSE;
        }
        if (j == 3) {
            D_8011D380 = func_80066348((bb->x2 + bb->x1) >> 1, (bb->y2 + bb->y1) >> 1, (bb->z2 + bb->z1) >> 1);
            if (D_8011D380 < 1000.0) {
                D_8011B0BC = 1;
                return TRUE;
            }
            D_8011B0BC = 0;
            return TRUE;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A5F8.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A900.s")

void func_8002ACC8(s32 arg0) {
    D_8011B0F4 = arg0;
}

s32 func_8002ACD4(f32 *arg0, f32 *arg1, f32 *arg2) {
    *arg0 = D_8011B0E4;
    *arg1 = D_8011B0E8;
    *arg2 = D_8011B0EC;
    return D_8011B0F0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002AD08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002B0F4.s")

s32 func_8002B9BC(Object *obj, f32 *arg1, f32 *arg2, s32 arg3) {
    LevelModelSegment *seg;

    if (arg2 != NULL) {
        arg2[0] = 0.0f;
        arg2[2] = 0.0f;
        arg2[1] = 1.0f;
    }
    if ((obj->segment.unk2C.half.lower < 0) || (obj->segment.unk2C.half.lower >= gCurrentLevelModel->numberOfSegments)) {
        return FALSE;
    }
    seg = &gCurrentLevelModel->segments[obj->segment.unk2C.half.lower];
    if ((seg->unk2B != 0) && (D_8011D384 != 0) && (arg3 == 1)) {
        *arg1 = func_800BB2F4(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, arg2);
        return TRUE;
    } else {
        *arg1 = seg->unk38;
        return TRUE;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002BAB0.s")

#ifdef NON_EQUIVALENT

// Maximum size for a level model is 522.5 KiB
#define LEVEL_MODEL_MAX_SIZE 0x82A00

#define LOCAL_OFFSET_TO_RAM_ADDRESS(ptr) \
    ptr = (s32)((u8*)ptr) + (s32)((u8*)gCurrentLevelModel)

// Loads a level track from the index in the models table.
// Has regalloc issues.
void func_8002C0C4(s32 modelId) {
    s32 i, j, k;
    s32 numLevelModels;
    s32 temp_s4;
    s32 offset, size;
    u8 *compressedRamAddr;
    LevelModelSegment *segment;
    TriangleBatchInfo *batch;
    Vertex *vertex;
    
    func_8007B374(0xFF00FF);
    D_8011D30C = allocate_from_main_pool_safe(LEVEL_MODEL_MAX_SIZE, 0xFFFF00FFU);
    gCurrentLevelModel = D_8011D30C;
    D_8011D370 = allocate_from_main_pool_safe(0x7D0, 0xFFFF00FFU);
    D_8011D374 = allocate_from_main_pool_safe(0x1F4, 0xFFFF00FFU);
    D_8011D378 = 0;
    D_8011D310 = load_asset_section_from_rom(ASSET_LEVEL_MODELS_TABLE);
    for(numLevelModels = 0; D_8011D310[numLevelModels] != -1; numLevelModels++) {}
    numLevelModels--;
    if (modelId >= numLevelModels) {
        modelId = 0;
    }
    offset = D_8011D310[modelId];
    size = D_8011D310[modelId + 1] - offset;
    compressedRamAddr = (u8*)gCurrentLevelModel + LEVEL_MODEL_MAX_SIZE - size;
    compressedRamAddr = compressedRamAddr - (u8*)((s32)compressedRamAddr % 16);
    load_asset_to_address(ASSET_LEVEL_MODELS, compressedRamAddr, offset, size);
    gzip_inflate((u8*) compressedRamAddr, (u8*) gCurrentLevelModel);
    free_from_memory_pool(D_8011D310); // Done with the level models table, so free it.

    LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->textures);
    LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->segments);
    LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->segmentsBoundingBoxes);
    LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->unkC);
    LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->segmentsBitfields);
    LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->segmentsBspTree);
    for(i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->segments[i].vertices);
        LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->segments[i].triangles);
        LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->segments[i].batches);
        LOCAL_OFFSET_TO_RAM_ADDRESS(gCurrentLevelModel->segments[i].unk14);
    }
    for(i = 0; i < gCurrentLevelModel->numberOfTextures; i++) {
        gCurrentLevelModel->textures[i].texture = load_texture(((s32)gCurrentLevelModel->textures[i].texture) | 0x8000);
    }
    temp_s4 = (s32)gCurrentLevelModel + gCurrentLevelModel->modelSize;
    for(i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        gCurrentLevelModel->segments[i].unk10 = temp_s4;
        temp_s4 = align16((gCurrentLevelModel->segments[i].numberOfTriangles * 2) + temp_s4);
        gCurrentLevelModel->segments[i].unk18 = temp_s4;
        temp_s4 = &((u8*)temp_s4)[func_8002CC30(&gCurrentLevelModel->segments[i])];
        func_8002C954(&gCurrentLevelModel->segments[i], &gCurrentLevelModel->segmentsBoundingBoxes[i], i);
        gCurrentLevelModel->segments[i].unk30 = 0;
        gCurrentLevelModel->segments[i].unk34 = temp_s4;
        func_8002C71C(&gCurrentLevelModel->segments[i]);
        temp_s4 = align16((gCurrentLevelModel->segments[i].unk32 * 2) + temp_s4);
    }
    temp_s4 -= (s32)gCurrentLevelModel;
    if (temp_s4 > LEVEL_MODEL_MAX_SIZE) {
        rmonPrintf("ERROR!! TrackMem overflow .. %d\n", temp_s4);
    }
    set_free_queue_state(0);
    free_from_memory_pool(D_8011D30C);
    allocate_at_address_in_main_pool(temp_s4, (u8 *) D_8011D30C, 0xFFFF00FFU);
    set_free_queue_state(2);
    func_800A83B4(gCurrentLevelModel);

    for(i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        for(j = 0; j < gCurrentLevelModel->segments[i].numberOfBatches; j++) {
            for(k = gCurrentLevelModel->segments[i].batches[j].verticesOffset; 
                k < gCurrentLevelModel->segments[i].batches[j+1].verticesOffset; 
                k++) {
                // Why do this? Why not just set the vertex colors in the model itself?
                if(gCurrentLevelModel->segments[i].vertices[k].r == 1 && gCurrentLevelModel->segments[i].vertices[k].g == 1) { 
                    gCurrentLevelModel->segments[i].vertices[k].a = gCurrentLevelModel->segments[i].vertices[k].b;
                    gCurrentLevelModel->segments[i].vertices[k].r = 0x80;
                    gCurrentLevelModel->segments[i].vertices[k].g = 0x80;
                    gCurrentLevelModel->segments[i].vertices[k].b = 0x80;
                    gCurrentLevelModel->segments[i].batches[j].flags |= 0x08000000;
                }
            }
        }
    }
    func_8007B374(0xFF00FFFF);
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C0C4.s")
#endif

void func_8002C71C(LevelModelSegment *segment) {
    s32 curVertY;
    s32 numVerts;
    s32 i;

    segment->unk38 = -10000;
    numVerts = 0;
    for (i = 0; i < segment->numberOfBatches; i++) {
        if (segment->batches[i].flags & 0x2000) {
            segment->unk34[numVerts++] = i;
            curVertY = segment->vertices[segment->batches[i].verticesOffset].y;
            if (segment->unk38 == -10000 || segment->unk38 < curVertY) {
                segment->unk38 = curVertY;
            }
        }
    }
    segment->unk32 = numVerts;
}

LevelModel *func_8002C7C4(void) {
    return gCurrentLevelModel;
}

void func_8002C7D4(void) {
    s32 i;

    func_8000B290();
    if (D_8011D384 != 0) {
        func_800B7D20();
    }
    for(i = 0; i < gCurrentLevelModel->numberOfTextures; i++) {
        free_texture(gCurrentLevelModel->textures[i].texture);
    }
    free_from_memory_pool(D_8011D30C);
    free_from_memory_pool(D_8011D370);
    free_from_memory_pool(D_8011D374);
    free_sprite((Sprite *) gCurrentLevelModel->unk20);
    for(i = 0; i < MAXCONTROLLERS; i++) {
        free_from_memory_pool(D_8011D350[i]);
        free_from_memory_pool(D_8011D320[i]);
        free_from_memory_pool(D_8011D338[i]);
    }
    func_800257D0();
    if (D_8011B0B8 != NULL) {
        gParticlePtrList_addObject(D_8011B0B8);
        gParticlePtrList_flush();
    }
    func_8000C604();
    gCurrentLevelModel = NULL;
}


GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C954.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002CC30.s")

typedef struct unk8002D30C_a0 {
    u8 pad00[0x04];
    struct unk8002D30C_a0 *unk04;
    struct unk8002D30C_a0 *unk08;
} unk8002D30C_a0;

void func_8002D30C(unk8002D30C_a0 *arg0, s32 arg1) {
    while(1) {
        if(!arg0) {
            return;
        }
        if (arg0->unk04) {
            arg0->unk04 = (unk8002D30C_a0 *)((s32)arg0->unk04 + arg1);
        }
        if (arg0->unk08) {
            arg0->unk08 = (unk8002D30C_a0 *)((s32)arg0->unk08 + arg1);
        }

        func_8002D30C(arg0->unk04, arg1);
        arg0 = arg0->unk08;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/render_floor_decal.s")

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D670.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D8DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002DE30.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E234.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E904.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002EEEC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F2AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F440.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FA64.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FD74.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FF6C.s")

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800304C8.s")

#ifdef NON_EQUIVALENT

// Should be functionally equivalent.
void func_80030664(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    s32 max, min;

    max = arg2;
    min = arg1;
    if (arg2 < arg1) {
        max = arg1;
        min = arg2;
    }
    if (max >= 0x400) {
        max = 0x3FF;
    }
    if (min >= max - 5) {
        min = max - 5;
    }
    D_8011D388[arg0].unk20 = 0;
    D_8011D388[arg0].unk24 = 0;
    D_8011D388[arg0].unk14 = 0;
    D_8011D388[arg0].unk18 = 0;
    D_8011D388[arg0].unk1C = 0;
    D_8011D388[arg0].unk0 = arg3 << 0x10;
    D_8011D388[arg0].unk4 = arg4 << 0x10;
    D_8011D388[arg0].unk8 = arg5 << 0x10;
    D_8011D388[arg0].unkC = min << 0x10;
    D_8011D388[arg0].unk10 = max << 0x10;
    D_8011D388[arg0].unk28 = arg3;
    D_8011D388[arg0].unk2C = min;
    D_8011D388[arg0].unk2E = max;
    D_8011D388[arg0].unk30 = 0;
    D_8011D388[arg0].unk34 = 0;
    D_8011D388[arg0].unk29 = arg4;
    D_8011D388[arg0].unk2A = arg5;
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030664.s")
#endif

void func_80030750(s32 arg0, s16 *arg1, s16 *arg2, s8 *arg3, s8 *arg4, s8 *arg5) {
    *arg1 = D_8011D388[arg0].unkC >> 0x10;
    *arg2 = D_8011D388[arg0].unk10 >> 0x10;
    *arg3 = D_8011D388[arg0].unk0 >> 0x10;
    *arg4 = D_8011D388[arg0].unk4 >> 0x10;
    *arg5 = D_8011D388[arg0].unk8 >> 0x10;
}

void func_800307BC(s32 arg0) {
    D_8011D388[arg0].unk20 = 0;
    D_8011D388[arg0].unk24 = 0;
    D_8011D388[arg0].unk14 = 0;
    D_8011D388[arg0].unk18 = 0;
    D_8011D388[arg0].unk1C = 0;
    D_8011D388[arg0].unkC = 0x03FA0000;
    D_8011D388[arg0].unk10 = 0x03FF0000;
    D_8011D388[arg0].unk28 = D_8011D388[arg0].unk0 >> 0x10;
    D_8011D388[arg0].unk29 = D_8011D388[arg0].unk4 >> 0x10;
    D_8011D388[arg0].unk2A = D_8011D388[arg0].unk8 >> 0x10;
    D_8011D388[arg0].unk2C = 0x03FA;
    D_8011D388[arg0].unk2E = 0x03FF;
    D_8011D388[arg0].unk30 = 0;
    D_8011D388[arg0].unk34 = 0;
}

void func_80030838(s32 arg0, s32 arg1) {
    s32 i;
    for (i = 0; i < arg0; i++) {
        if (D_8011D388[i].unk30 > 0) {
            if (arg1 < D_8011D388[i].unk30) {
                D_8011D388[i].unk0 += D_8011D388[i].unk14 * arg1;
                D_8011D388[i].unk4 += D_8011D388[i].unk18 * arg1;
                D_8011D388[i].unk8 += D_8011D388[i].unk1C * arg1;
                D_8011D388[i].unkC += D_8011D388[i].unk20 * arg1;
                D_8011D388[i].unk10 += D_8011D388[i].unk24 * arg1;
                D_8011D388[i].unk30 -= arg1;
            } else {
                D_8011D388[i].unk0 = D_8011D388[i].unk28 << 0x10;
                D_8011D388[i].unk4 = D_8011D388[i].unk29 << 0x10;
                D_8011D388[i].unk8 = D_8011D388[i].unk2A << 0x10;
                D_8011D388[i].unkC = D_8011D388[i].unk2C << 0x10;
                D_8011D388[i].unk10 = D_8011D388[i].unk2E << 0x10;
                D_8011D388[i].unk30 = 0;
            }
        }
    }
}

void func_8003093C(s32 arg0) {
    gDPSetFogColor(D_8011B0A0++, D_8011D388[arg0].unk0 >> 0x10, D_8011D388[arg0].unk4 >> 0x10, D_8011D388[arg0].unk8 >> 0x10, 0xFF);
    gSPFogPosition(D_8011B0A0++, D_8011D388[arg0].unkC >> 0x10, D_8011D388[arg0].unk10 >> 0x10);
}

#ifdef NON_EQUIVALENT
//unk8011D388 D_8011D388[4];

typedef struct Object_3C_FogChanger {
    u8 pad0[0x2];
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} Object_3C_FogChanger;

void obj_loop_fogchanger(Object* obj) {
    s32 temp_v0;
    s32 index;
    s32 sp74;
    s32 i;
    s32 phi_a0, phi_v1;
    f32 x, z;
    s32 temp_a3, temp_t0, temp_t1, temp_a1;
    s32 temp;
    Object **sp40;
    Object_3C_FogChanger *sp44;
    Object *tempObj;
    unk8011D388 *temp_v0_3;
    ObjectSegment *phi_s3;
    
    sp40 = NULL;
    sp44 = obj->segment.unk3C_a.unk3C;
    phi_s3 = NULL;
    
    // func_80066510() returns the bool D_80120D14. 1 if camera is controlled by cutscene, 0 if controlled by racer.
    if (func_80066510()) {
        phi_s3 = func_80069D7C();
        sp74 = get_viewport_count() + 1;
    } else {
        sp40 = get_object_struct_array(&sp74);
    }
    
    for(i = 0; i < sp74; i++) {
        index = -1;
        if (sp40 != NULL) {
            tempObj = sp40[i]; // Might be a player object?
            temp_v0 = tempObj->unk64->fog_changer.unk0;
            if ((temp_v0 >= 0) && (temp_v0 < MAXCONTROLLERS) && (obj != D_8011D388[i].unk34)) {
                index = temp_v0;
                x = tempObj->segment.trans.x_position;
                z = tempObj->segment.trans.z_position;
            }
        } else if ((i < 4) && (obj != D_8011D388[i].unk34)) {
            index = i;
            x = phi_s3[i].trans.x_position;
            z = phi_s3[i].trans.z_position;
        }
        if (index != -1) {
            x -= obj->segment.trans.x_position;
            z -= obj->segment.trans.z_position;
            if (((x * x) + (z * z)) < obj->unk78f) {
                phi_a0 = sp44->unkC;
                phi_v1 = sp44->unkE;
                temp_a3 = sp44->unk9;
                temp_t0 = sp44->unkA;
                temp_t1 = sp44->unkB;
                temp_a1 = sp44->unk10;
                if (phi_v1 < phi_a0) {
                    phi_v1 = sp44->unkC;
                    phi_a0 = sp44->unkE;
                }
                if (phi_v1 >= 0x400) {
                    phi_v1 = 0x3FF;
                }
                if (phi_a0 >= phi_v1 - 5) {
                    phi_a0 = phi_v1 - 5;
                }
                temp_v0_3 = &D_8011D388[index];
                temp_v0_3->unk28 = temp_a3;
                temp_v0_3->unk29 = temp_t0;
                temp_v0_3->unk2A = temp_t1;
                temp_v0_3->unk2C = phi_a0;
                temp_v0_3->unk2E = phi_v1;
                temp_v0_3->unk14 = ((temp_a3 << 16) - temp_v0_3->unk0) / temp_a1;
                temp_v0_3->unk18 = ((temp_t0 << 16) - temp_v0_3->unk4) / temp_a1;
                temp_v0_3->unk1C = ((temp_t1 << 16) - temp_v0_3->unk8) / temp_a1;
                temp_v0_3->unk20 = ((phi_a0 << 16) - temp_v0_3->unkC) / temp_a1;
                temp_v0_3->unk24 = ((phi_v1 << 16) - temp_v0_3->unk10) / temp_a1;
                temp_v0_3->unk30 = temp_a1;
                temp_v0_3->unk34 = obj;
            }
        }
    }
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/obj_loop_fogchanger.s")
#endif

#ifdef NON_EQUIVALENT
void func_80030DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 max, min;
    unk8011D388 *entry;

    entry = &D_8011D388[arg0];
    max = arg5;
    min = arg4;
    if (arg5 < arg4) {
        max = arg4;
        min = arg5;
    }
    if (max > 0x3FF) {
        max = 0x3FF;
    }
    if (min >= max - 5) {
        min = max - 5;
    }
    entry->unk28 = arg1;
    entry->unk29 = arg2;
    entry->unk2A = arg3;
    entry->unk2C = min;
    entry->unk2E = max;
    entry->unk14 = ((arg1 << 16) - entry->unk0) / arg6;
    entry->unk18 = ((arg2 << 16) - entry->unk4) / arg6;
    entry->unk1C = ((arg3 << 16) - entry->unk8) / arg6;
    entry->unk20 = ((min << 16) - entry->unkC) / arg6;
    entry->unk24 = ((max << 16) - entry->unk10) / arg6;
    entry->unk30 = arg6;
    entry->unk34 = 0;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030DE0.s")
#endif

UNUSED void func_80030FA0(void) {
    D_8011B0B0 = func_80069D20();
    func_80031018();
    func_8001D5E0((f32) D_8011D468.x / 65536.0f, (f32) D_8011D468.y / 65536.0f, (f32) D_8011D468.z / 65536.0f);
}

void func_80031018(void) {
    Matrix mf;
    ObjectTransform trans;

    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = -65536.0f;

    trans.z_rotation = D_8011B0B0->segment.trans.z_rotation;
    trans.x_rotation = D_8011B0B0->segment.trans.x_rotation;
    trans.y_rotation = D_8011B0B0->segment.trans.y_rotation;
    trans.x_position = 0.0f;
    trans.y_position = 0.0f;
    trans.z_position = 0.0f;
    trans.scale = 1.0f;

    func_8006FC30(mf, &trans);
    guMtxXFMF(mf, x, y, z, &x, &y, &z);

    //Store x/y/z as integers
    D_8011D468.x = (s32)x;
    D_8011D468.y = (s32)y;
    D_8011D468.z = (s32)z;
}
