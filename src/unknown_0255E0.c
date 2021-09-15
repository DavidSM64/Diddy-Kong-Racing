/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800249E0 */

#include "unknown_0255E0.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "PR/gu.h"
#include "textures_sprites.h"
#include "unknown_00BC20.h"
#include "unknown_06B2B0.h"
#include "memory.h"
#include "unknown_043920.h"
#include "camera.h"

/************ .data ************/

s32 D_800DC870 = 0; // Currently unknown, might be a different type.
unknown800DC874 D_800DC874 = { -128, 40, -1 };
unknown800DC874 D_800DC87C = { -125, 70, -1 };

f32 D_800DC884[10] = { 
    0.0f, 0.125f, 0.25f, 0.375f,
    0.5f, 0.625f, 0.75f, 0.875f
};

f32 D_800DC8AC[27] = {
    50.0f, 0.0f, 32.0f, -50.0f, 
    0.0f, 32.0f, -50.0f, 100.0f, 
    32.0f, 0.0f, 0.0f, 32.0f, 
    130.0f, 60.0f, -68.0f, 130.0f, 
    -60.0f, -68.0f, 0.0f, 0.0f, 
    32.0f, -130.0f, -60.0f, -68.0f, 
    -130.0f, 60.0f, -68.0f
};

LevelModel *gCurrentLevelModel = NULL;
LevelHeader *gCurrentLevelHeader2 = NULL;

s32 D_800DC920 = -1;
s32 D_800DC924 = 0;
s32 D_800DC928 = 0; // Currently unknown, might be a different type.

s8 D_800DC92C[24] = { 
    0, 1, 4, 1, 2, 4, 2, 3, 
    4, 3, 0, 4, 5, 6, 1, 1, 
    0, 5, 3, 2, 7, 7, 8, 3
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
s32 D_8011B0A4;
s32 D_8011B0A8;
s32 D_8011B0AC;

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
s8 D_8011B0E1;
s8 D_8011B0E2;
s8 D_8011B0E3;
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
s32 D_8011D128[15];
s32 D_8011D164;
s32 D_8011D168[84];
s32 D_8011D2B8[20];
s32 D_8011D308;
s32 D_8011D30C;
s32 D_8011D310;
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
s32 D_8011D370;
s32 D_8011D374;
s32 D_8011D378;
s32 D_8011D37C;
f32 D_8011D380;
u32 D_8011D384;
unk8011D388 D_8011D388[4];
unk8011D468 D_8011D468;
s32 D_8011D474;
s32 D_8011D478;
s32 D_8011D47C;
s32 D_8011D480[2];
s32 D_8011D488[2];
s32 D_8011D490[2];
s32 D_8011D498;
s16 D_8011D49C;
s16 D_8011D49E;
s32 D_8011D4A0;
s32 D_8011D4A4;
s32 D_8011D4A8;
s32 D_8011D4AC;
s32 D_8011D4B0;
s16 D_8011D4B4;
s16 D_8011D4B6;
s16 D_8011D4B8;
s16 D_8011D4BA;
s32 D_8011D4BC;


/******************************/

s32 func_800249E0(s32 arg0) {
    D_8011D37C = arg0;
    return 0;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800249F0.s")
#else
void func_800249F0(u32 arg0, u32 arg1, s32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6) {
    s32 i;
    s32 tmp_a2;

    gCurrentLevelHeader2 = get_current_level_header();
    D_8011B0F8 = 0;
    D_8011B100 = 0;
    D_8011B104 = 0;
    D_8011B108 = 0;
    D_8011B10C = 0;
    if(gCurrentLevelHeader2->race_type == 6 || gCurrentLevelHeader2->race_type == 7){
        D_8011B0F8 = 1;
    }
    func_8002C0C4(arg0);

    if(arg2 < 2){
        D_8011D384 = 0;
        for(i = 0; i < gCurrentLevelModel->numberOfSegments; i++){
            if(gCurrentLevelModel->segments[i].unk2B != 0){
                D_8011D384++;
                gCurrentLevelModel->segments[i].unk2B = 1;
            }
        }
    }
    if(is_in_two_player_adventure() && (gCurrentLevelHeader2->race_type == 0 || gCurrentLevelHeader2->race_type & 0x40)){
        tmp_a2 = 2;
    }else{
        tmp_a2 = arg2;
        tmp_a2++;
    }
    if(D_8011D384){
        func_800B82B4(gCurrentLevelModel, gCurrentLevelHeader2, tmp_a2);
    }
    func_8006652C(arg2);
    func_80027FC4(arg1);
    D_8011B110 = 0;
    D_8011B114 = 0x10000;
    func_80011390();
    func_8000C8F8(arg6,0);
    func_8000C8F8(arg5,1);
    D_8011D37C = arg2;
    func_8000CC7C(arg3, arg4, arg2);
    func_8000B020(72, 64);
    if(arg0 == 0 && arg4 == 0){
        func_800C01D8(&D_800DC87C);
    }
    else{
        func_800C01D8(&D_800DC874);
    }
    func_8006652C(D_8011D37C);
    D_8011B0FC = 0;
    i = 0;
    do{
        D_8011D350[i] = allocate_from_main_pool_safe(3200, COLOR_TAG_YELLOW);
        D_8011D320[i] = allocate_from_main_pool_safe(12800, COLOR_TAG_YELLOW);
        D_8011D338[i] = allocate_from_main_pool_safe(20000, COLOR_TAG_YELLOW);
    }while(&D_8011D338[++i] != &D_8011D348);
    
    D_8011B0C8 = 0;
    func_8002D8DC(1,1,0);
    func_8002D8DC(2,2,0);
    D_8011B0C8 = 1;
    func_8002D8DC(1,1,0);
    func_8002D8DC(2,2,0);
    D_8011B0C8 = 0;
    if(gCurrentLevelHeader2->unkB7){
        D_8011B0E1 = gCurrentLevelHeader2->unkB4;
        D_8011B0E2 = gCurrentLevelHeader2->unkB5;
        D_8011B0E3 = gCurrentLevelHeader2->unkB6;
        func_80025510(arg2 + 1);
    }
}
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
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027E24.s")

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
    D_8011B0B8 = func_8000EA54(&sp20, 2);
    if (D_8011B0B8 != 0) {
        D_8011B0B8->unk3C_a.unk3C = 0;
        D_8011B0B8->unk4A = -1;
    }
}

void func_80028044(s32 arg0) {
    D_8011B0DC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028050.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800289B8.s")
#else
void func_800289B8(void){
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
#endif

void render_skydome(void) {
    unk80120AC0 * v0_some_struct;
    if(D_8011B0B8 == NULL)
        return;

    v0_some_struct = func_80069D20();
    if(gCurrentLevelHeader2->unk49 == 0){
        D_8011B0B8->x_position = v0_some_struct->x_position;
        D_8011B0B8->y_position = v0_some_struct->y_position;
        D_8011B0B8->z_position = v0_some_struct->z_position;
    }

    func_80068408(&D_8011B0A0, &D_8011B0A4);
    if(D_8011B0DC){
        func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, D_8011B0B8);
    }
}
#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028CD0.s")
#else

#endif


void func_80028FA0(s32 arg0) {
    D_8011B0FC = arg0;
}

#ifdef NON_MATCHING

// Regalloc & stack issues.
void render_level_geometry_and_objects(void) {
    s32 sp16C;
    s32 sp168;
    s32 objFlags;
    s32 sp160;
    s32 i;
    s32 sp158;
    u8 spD8[128];
    u8 sp58[128];
    s32 s0;
    Object *obj;
    s32 sp44;
    
    func_80012C30();
    if (get_settings()->courseId == 0x24) { // 0x24 = Opening sequence area
        D_8011B0FC = 1;
    }
    sp160 = func_80014814(&sp16C);
    if (gCurrentLevelModel->numberOfSegments >= 2) {
        sp168 = 0;
        traverse_segments_bsp_tree(0, 0, gCurrentLevelModel->numberOfSegments - 1, &spD8, &sp168);
    } else {
        sp168 = 1;
        spD8[0] = 0;
    }
    
    for (i = 1; i <= gCurrentLevelModel->numberOfSegments; i++) {
        sp58[i] = FALSE;
    }
    sp58[0] = TRUE;
    
    if (D_8011B0E0 != 0) {
        for (i = 0; i < sp168; i++) {
            render_level_segment(spD8[i], 0);  // Render opaque segments
            sp58[spD8[i]+1] = TRUE;
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
        objFlags = obj->unk6;
        if (objFlags & 0x80) {
            s0 = 0;
        }
        else if (!(objFlags & 0x8000)) {
            s0 = obj->unk39;
        }
        if (objFlags & sp158) {
            s0 = 0;
        }
        if ((obj != NULL) && (s0 == 0xFF) && (func_8002A900(obj)) && ((sp58[obj->unk2E + 1]) || (1000.0 < obj->unk34_a.unk34))) {
            if (obj->unk6 & 0x8000) {
                func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
            } else if (obj->unk50 != NULL) {
                render_floor_decal(obj, obj->unk50);
            }
            func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
            if ((obj->unk58 != NULL) && (obj->descriptor_ptr->unk30 & 0x10)) {
                func_8002D670(obj, obj->unk58);
            }
        }
    }
    
    i = sp16C - 1;
    if (i >= sp160) {
        sp44 = sp160 - 1;
        do {
            obj = get_object(i);
            objFlags = obj->unk6;
            if (objFlags & sp158) {
                s0 = FALSE;
            } else {
                s0 = TRUE;
            }
            if (obj != NULL && s0 && (objFlags & 0x100) && (sp58[obj->unk2E + 1]) && (func_8002A900(obj) != 0)) {
                if (obj->unk6 & 0x8000) {
                    func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                } else if (obj->unk50 != NULL) {
                    render_floor_decal(obj, obj->unk50);
                }
                func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                if ((obj->unk58 != NULL) && (obj->descriptor_ptr->unk30 & 0x10)) {
                    func_8002D670(obj, obj->unk58);
                }
            }
            i--;
        } while(i != sp44);
    }
    i = sp168 - 1;
    if (D_8011B0E0 != 0) {
        while (i >= 0) {
            render_level_segment(spD8[i], 1); // Render transparent segments
            i--;
        }
    }
    if (D_8011D384 != 0) {
        func_800BA8E4(&D_8011B0A0, &D_8011B0A4, func_80066220());
    }
    func_8007B3D0(&D_8011B0A0);
    func_8007B4C8(&D_8011B0A0, 0, 0xA);
    func_80012C3C(&D_8011B0A0);
    
    i = sp16C - 1;
    if (i >= sp160) {
        sp44 = sp160 - 1;
        do {
            obj = get_object(i);
            s0 = 0xFF;
            objFlags = obj->unk6;
            if (objFlags & 0x80) {
                s0 = 1;
            } else if (!(objFlags & 0x8000)) {
                s0 = obj->unk39;
            }
            if (objFlags & sp158) {
                s0 = 0;
            }
            if ((obj->unk48 == 1) && (s0 >= 0xFF)) {
                s0 = 0;
            }
            if (obj != NULL && s0 < 0xFF && sp58[obj->unk2E + 1] && func_8002A900(obj)) {
                if (s0 > 0) {
                    if (obj->unk6 & 0x8000) {
                        func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                    } else {
                        if (obj->unk50 != NULL) {
                            render_floor_decal(obj, obj->unk50);
                        }
                        // This is being called when it shouldn't.
                        func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                        if ((obj->unk58 != 0) && (obj->descriptor_ptr->unk30 & 0x10)) {
                            func_8002D670(obj, obj->unk58);
                        }
                    }
                }
                if (obj->unk48 == 1) {
                    func_80013A0C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                    func_80013DCC(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, obj);
                }
            }
            i--;
        } while(i != sp44);
    }
    if (D_800DC924 && func_80027568()) {
        func_8002581C(&spD8, sp168, func_80066220());
    }
    D_8011B0FC = 0;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/render_level_geometry_and_objects.s")
#endif

// *Should *be functionally equivalent.
#ifdef NON_MATCHING
// nonOpaque: 0 for solid geometry, 1 for transparent geometry.
void render_level_segment(s32 segmentId, s32 nonOpaque) {
    LevelModelSegment *segment = &gCurrentLevelModel->segments[segmentId]; // spAC
    LevelHeader_70 *lvlHeader70;
    TriangleBatchInfo *batchInfo;
    TextureHeader *texture;
    s32 temp_v0;
    s32 temp_v1;
    s32 flags;
    s32 renderBatch;
    s32 numberVertices;
    s32 numberTriangles;
    s32 vertices;
    s32 triangles;
    s32 color;
    s32 hasTexture;
    s32 levelHeaderIndex;
    s32 sp78;
    s32 i;
    s32 sp70;
    s32 textureIndex;
    s32 textureFlags;
    s32 temp;
    
    if (nonOpaque && (D_8011D384 != 0)) {
        sp78 = func_800B9228(segment);
    } else {
        sp78 = 0;
    }
    if (nonOpaque) {
        sp70 = segment->numberOfBatches;
        i = segment->unk40;
    } else {
        sp70 = segment->unk40;
        i = 0;
    }
    
    for(; i < sp70; i++) {
        batchInfo = &segment->batches[i];
        flags = batchInfo->flags;
        textureFlags = 0;
        if (!(flags & 0x100)) { // 0x100 = Is this invisible geometry?
            textureIndex = batchInfo->textureIndex;
            renderBatch = FALSE;
            if (textureIndex == 0xFF) {
                texture = NULL; // Solid color only
            } else {
                texture = gCurrentLevelModel->textures[textureIndex].texture;
                textureFlags = texture->flags;
            }
            flags |= (0x8 | 0x2);
            if (!(flags & 0x10) && !(flags & 0x800)) { // 0x10 = Depth write
                flags |= D_8011B0FC;
            }
            // textureFlags & 0x04 = Is interlaced texture
            if ((!(textureFlags & 4) && !(flags & 0x2000)) || (flags & 0x800)) {
                renderBatch = TRUE;
            }
            if (nonOpaque) {
                renderBatch = (renderBatch + 1) & 1; // Why not just do `renderBatch ^= 1;` or `renderBatch = !renderBatch`?
            }
            if (sp78 && (flags & 0x2000)) {
                renderBatch = FALSE;
            }
            if (renderBatch) {
                temp_v0 = batchInfo->verticesOffset;
                temp_v1 = batchInfo->facesOffset;
                numberVertices = (batchInfo + 1)->verticesOffset - temp_v0;
                numberTriangles = (batchInfo + 1)->facesOffset - temp_v1;
                vertices = &segment->vertices[temp_v0];
                triangles = &segment->triangles[temp_v1];
                levelHeaderIndex = (flags >> 28) & 7;
                if (levelHeaderIndex != 0) { // This is unused, so this should always be false.
                    lvlHeader70 = gCurrentLevelHeader2->unk70;//gCurrentLevelHeader2[levelHeaderIndex].unk70;
                    gDPSetEnvColor(D_8011B0A0++, lvlHeader70->red, lvlHeader70->green, lvlHeader70->blue, lvlHeader70->alpha)
                } else {
                    gDPSetEnvColor(D_8011B0A0++, 255, 255, 255, 0)
                }
                temp = batchInfo->unk7 << 14;
                if (flags & 0x40000) { // Only gets used in Spaceport alpha for the pulsating lights in the outside section.
                    color = gCurrentLevelHeader2->pulseLightData->outColorValue & 0xFF;
                    gDPSetPrimColor(D_8011B0A0++, 0, 0, color, color, color, color)
                    func_8007BA5C(&D_8011B0A0, texture, flags, temp);
                    vertices += 0x80000000;
                    gDkrVertices(D_8011B0A0++, vertices, (((numberVertices - 1) << 3) | (vertices & 6)), numberVertices)
                    gDkrTriangles(D_8011B0A0++, triangles + 0x80000000, numberTriangles, TRIN_ENABLE_TEXTURE)
                    gDPSetPrimColor(D_8011B0A0++, 0, 0, 255, 255, 255, 255) // Reset the primitive color
                } else {
                    func_8007B4E8(&D_8011B0A0, texture, flags, temp);
                    hasTexture = (texture == NULL) ? TRIN_DISABLE_TEXTURE : TRIN_ENABLE_TEXTURE;
                    vertices += 0x80000000;
                    gDkrVertices(D_8011B0A0++, vertices, (((numberVertices - 1) << 3) | (vertices & 6)), numberVertices)
                    gDkrTriangles(D_8011B0A0++, triangles + 0x80000000, numberTriangles, hasTexture)
                    
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/render_level_segment.s")
#endif

#ifdef NON_MATCHING
// Regalloc issues.
void traverse_segments_bsp_tree(s32 nodeIndex, s32 segmentIndex, s32 segmentIndex2, u8 *segmentsOrder, u32 *segmentsOrderIndex) {
    BspTreeNode *curNode;
    s32 camValue;
    
    while(TRUE) {
        curNode = &gCurrentLevelModel->segmentsBspTree[nodeIndex];
        if (curNode->splitType == 0) {
            camValue = D_8011B0B0->x_position; // Camera X
        } else if (curNode->splitType == 1) {
            camValue = D_8011B0B0->y_position; // Camera Y
        } else {
            camValue = D_8011B0B0->z_position; // Camera Z
        }
        if (camValue < curNode->splitValue) {
            if (curNode->leftNode != -1) {
                traverse_segments_bsp_tree(curNode->leftNode, segmentIndex, curNode->segmentIndex - 1, segmentsOrder, segmentsOrderIndex);
            } else {
                add_segment_to_order(segmentIndex, segmentsOrderIndex, segmentsOrder);
            }
            if (curNode->rightNode != -1) {
                segmentIndex = curNode->segmentIndex;
                nodeIndex = curNode->rightNode;
                continue;
            }
            add_segment_to_order(segmentIndex2, segmentsOrderIndex, segmentsOrder);
            return;
        }
        if (curNode->rightNode != -1) {
            traverse_segments_bsp_tree(curNode->rightNode, curNode->segmentIndex, segmentIndex2, segmentsOrder, segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex2, segmentsOrderIndex, segmentsOrder);
        }
        nodeIndex = curNode->leftNode;
        if (nodeIndex == -1) {
            break;
        }
        segmentIndex2 = curNode->segmentIndex;
        segmentIndex2--;
    }
    add_segment_to_order(segmentIndex, segmentsOrderIndex, segmentsOrder);
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/traverse_segments_bsp_tree.s")
#endif

void add_segment_to_order(s32 segmentIndex, u32 *segmentsOrderIndex, u8 *segmentsOrder) {
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

#ifdef NON_MATCHING
// Unused. Has regalloc issues.
s32 func_80029DE0(Object *obj, s32 segmentIndex) {
    LevelModelSegmentBoundingBox *bb;
    s32 x, y, z;
    if (segmentIndex >= gCurrentLevelModel->numberOfSegments) {
        return FALSE;
    }
    x = obj->x_position;
    y = obj->y_position;
    z = obj->z_position;
    bb = &gCurrentLevelModel->segmentsBoundingBoxes[segmentIndex];
    if ((x < (bb->unk6 + 25)) && ((bb->unk0 - 25) < x) && 
        (z < (bb->unkA + 25)) && ((bb->unk4 - 25) < z) && 
        (y < (bb->unk8 + 25)) && ((bb->unk2 - 25) < y)) {
        return TRUE;
    }
    
    return FALSE;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029DE0.s")
#endif

#ifdef NON_MATCHING
// Has regalloc issues.
s32 get_level_segment_index_from_position(f32 xPos, f32 yPos, f32 zPos) {
    LevelModelSegmentBoundingBox *bb;
    s32 i;
    s32 minVal;
    s32 result;
    s32 heightDiff;

    if (gCurrentLevelModel == NULL) {
        return -1;
    }
    
    minVal = 1000000;
    result = -1;
    
    for(i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        bb = &gCurrentLevelModel->segmentsBoundingBoxes[i];
        if (((s32)xPos < bb->unk6) && (bb->unk0 < (s32)xPos) && ((s32)zPos < bb->unkA) && (bb->unk4 < (s32)zPos)) {
            heightDiff = (s32)yPos - ((bb->unk8 + bb->unk2) >> 1);
            if (heightDiff < 0) {
                heightDiff = -heightDiff;
            }
            if (heightDiff < minVal) {
                result = i;
                minVal = heightDiff;
            }
        }
    }
    
    return result;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/get_level_segment_index_from_position.s")
#endif


s32 func_8002A05C(s32 arg0, s32 arg1, s32 *arg2) {
    s32 i;
    s32 cnt = 0;
    LevelModelSegmentBoundingBox * a0;
    for(i = 0; i < gCurrentLevelModel->numberOfSegments; i++){
        a0 = gCurrentLevelModel->segmentsBoundingBoxes + i;
        if(arg0 < a0->unk6 + 4 && a0->unk0 - 4 < arg0
        && arg1 < a0->unkA + 4 && a0->unk4 - 4 < arg1
        ){
            *arg2 = i;
            cnt++;
            arg2++;
        }
    }
    return cnt;
}

s32 func_8002A134(s32 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    s32 phi_v1;
    s32 i;
    LevelModelSegmentBoundingBox *bb;
    
    arg1 -= 4;
    arg2 -= 4;
    arg3 -= 4;
    arg4 += 4;
    arg5 += 4;
    arg6 += 4;
    
    i = 0;
    phi_v1 = 0;
    
    while(i < gCurrentLevelModel->numberOfSegments) {
        bb = &gCurrentLevelModel->segmentsBoundingBoxes[i];
        if ((bb->unk6 >= arg1) && (arg4 >= bb->unk0) && 
            (bb->unkA >= arg3) && (arg6 >= bb->unk4) && 
            (bb->unk8 >= arg2) && (arg5 >= bb->unk2)) {
            phi_v1++;
            *arg0++ = i;
        }
        i++;
    }
    
    return phi_v1;
}

LevelModelSegment *func_8002A2C8(s32 arg0) {
    if(arg0 < 0 || gCurrentLevelModel->numberOfSegments < arg0)
        return NULL;
    
    return gCurrentLevelModel->segments + arg0;
}

LevelModelSegmentBoundingBox *func_8002A2DC(s32 arg0) {
    if(arg0 < 0 || gCurrentLevelModel->numberOfSegments < arg0)
        return NULL;

    return gCurrentLevelModel->segmentsBoundingBoxes + arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A31C.s")

#ifdef NON_MATCHING
// Has some minor issues, but should be functionally equivalent.
s32 func_8002A5F8(LevelModelSegmentBoundingBox *bb) {
    s64 sp48;
    s32 i, j;
    s32 s2;
    f32 temp0, temp1, temp2, temp3;
    
    j = 0;
    while(TRUE) {
        temp0 = D_8011D0F8[j].unk0;
        temp1 = D_8011D0F8[j].unk4;
        temp2 = D_8011D0F8[j].unk8;
        temp3 = D_8011D0F8[j].unkC;
        i = 0;
        s2 = FALSE;
        while(i < 8 && !s2) {
            if (i & 1) {
                sp48 = bb->unk0 * temp0;
            } else {
                sp48 = bb->unk6 * temp0;
            }
            if (i & 2) {
                sp48 += bb->unk2 * temp1;
            } else {
                sp48 += bb->unk8 * temp1;
            }
            if (i & 4) {
                sp48 += bb->unk4 * temp2;
            } else {
                sp48 += bb->unkA * temp2;
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
            D_8011D380 = func_80066348((bb->unk6 + bb->unk0) >> 1, (bb->unk8 + bb->unk2) >> 1, (bb->unkA + bb->unk4) >> 1);
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
    if ((obj->unk2E < 0) || (obj->unk2E >= gCurrentLevelModel->numberOfSegments)) {
        return FALSE;
    }
    seg = &gCurrentLevelModel->segments[obj->unk2E];
    if ((seg->unk2B != 0) && (D_8011D384 != 0) && (arg3 == 1)) {
        *arg1 = func_800BB2F4(obj->unk2E, obj->x_position, obj->z_position, arg2);
        return TRUE;
    } else {
        *arg1 = seg->unk38;
        return TRUE;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002BAB0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C0C4.s")

void func_8002C71C(LevelModelSegment *segment) {
    s32 curVertY;
    s32 numVerts;
    s32 i;
    
    segment->unk38 = -10000;
    numVerts = 0;
    for(i = 0; i < segment->numberOfBatches; i++) {
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

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C7D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C954.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002CC30.s")

#ifdef NON_MATCHING

typedef struct unk8002D30C_a0{
    u8 pad00[0x04];
    struct unk8002D30C_a0 *unk04;
    struct unk8002D30C_a0 *unk08;
}unk8002D30C_a0;

void func_8002D30C(unk8002D30C_a0 *arg0, s32 arg1) {
    // Weird issue here with the ra register.
    while(arg0 != NULL) {
        if(arg0->unk04) {
            arg0->unk04 = (unk8002D30C_a0*)((s32)arg0->unk04 + arg1);
        }

        if(arg0->unk08){
            arg0->unk08 = (unk8002D30C_a0*)((s32)arg0->unk08 + arg1);
        }

        func_8002D30C(arg0->unk04, arg1);
        arg0 = arg0->unk08;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D30C.s")
#endif

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

#ifdef NON_MATCHING

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
    *arg1 = D_8011D388[arg0].unkC  >> 0x10;
    *arg2 = D_8011D388[arg0].unk10 >> 0x10;
    *arg3 = D_8011D388[arg0].unk0  >> 0x10;
    *arg4 = D_8011D388[arg0].unk4  >> 0x10;
    *arg5 = D_8011D388[arg0].unk8  >> 0x10;
}

void func_800307BC(s32 arg0) {
    D_8011D388[arg0].unk20 = 0;
    D_8011D388[arg0].unk24 = 0;
    D_8011D388[arg0].unk14 = 0;
    D_8011D388[arg0].unk18 = 0;
    D_8011D388[arg0].unk1C = 0;
    D_8011D388[arg0].unkC  = 0x03FA0000;
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
    for(i = 0; i < arg0; i++) {
        if (D_8011D388[i].unk30 > 0) {
            if (arg1 < D_8011D388[i].unk30) {
                D_8011D388[i].unk0 += D_8011D388[i].unk14 * arg1;
                D_8011D388[i].unk4 += D_8011D388[i].unk18 * arg1;
                D_8011D388[i].unk8 += D_8011D388[i].unk1C * arg1;
                D_8011D388[i].unkC += D_8011D388[i].unk20 * arg1;
                D_8011D388[i].unk10 += D_8011D388[i].unk24 * arg1;
                D_8011D388[i].unk30 -= arg1;
            } else {
                D_8011D388[i].unk0  = D_8011D388[i].unk28 << 0x10;
                D_8011D388[i].unk4  = D_8011D388[i].unk29 << 0x10;
                D_8011D388[i].unk8  = D_8011D388[i].unk2A << 0x10;
                D_8011D388[i].unkC  = D_8011D388[i].unk2C << 0x10;
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
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030A74.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030DE0.s")


void func_80031018(void) {
    Matrix mf;

    struct {
        s16 unk00; //sp_38
        s16 unk02; //sp_3A
        s16 unk04; //sp_3C
        u8 pad06[0x02];
        f32 unk08; //sp40;
        f32 unk0C; //sp44;
        f32 unk10; //sp48;
        f32 unk14; //sp4C;
    } sp_38;

    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = -65536.0f;
    
    sp_38.unk04 = D_8011B0B0->z_rotation;
    sp_38.unk02 = D_8011B0B0->x_rotation;
    sp_38.unk00 = D_8011B0B0->y_rotation;
    sp_38.unk0C = 0.0f;
    sp_38.unk10 = 0.0f;
    sp_38.unk14 = 0.0f;
    sp_38.unk08 = 1.0f;
    
    func_8006FC30(&mf, &sp_38);
    guMtxXFMF(&mf, x, y, z, &x, &y, &z);

    //Store x/y/z as integers
    D_8011D468.x = (s32) x;
    D_8011D468.y = (s32) y;
    D_8011D468.z = (s32) z;
}
