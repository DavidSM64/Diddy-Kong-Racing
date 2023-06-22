/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80008040 */

#include "unknown_008C40.h"
#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "unknown_005740.h"
#include "memory.h"
#include "audio.h"
#include "textures_sprites.h"
#include "objects.h"
#include "audiosfx.h"
#include "tracks.h"
#include "math_util.h"

/************ .data ************/

u16 D_800DC6E0 = 0;

/*******************************/

/************ .rodata ************/

UNUSED const char D_800E4D00[] = "OUT OF AUDIO POINTS\n";
UNUSED const char D_800E4D18[] = "amAudioLineAddVertex: Exceeded maximum number of lines (%d)\n";
UNUSED const char D_800E4D58[] = "amAudioLineAddVertex: Exceeded maximum number of line vertices (%d)\n";
UNUSED const char D_800E4DA0[] = "amReverbLineAddVertex: Exceeded maximum number of lines (%d)\n";
UNUSED const char D_800E4DE0[] = "amReverbLineAddVertex: Exceeded maximum number of line vertices (%d)\n";

UNUSED const char D_800E4E28[] = "Audio line definition error (less than 2 vertices on line %d)\n";
UNUSED const char D_800E4E68[] = "Audio line definition error (line=%d, vertex=%d)\n";
UNUSED const char D_800E4E9C[] = "Reverb line definition error (less than 2 vertices on line %d)\n";
UNUSED const char D_800E4EDC[] = "Reverb line definition error (line=%d, vertex=%d)\n";

/*********************************/

/************ .bss ************/

extern s8 D_8011AC18;
extern unk80115D18 *D_80119C40;
extern unk80119C58 D_80119C58[];
extern unk8011A6D8 D_8011A6D8[];

/*******************************/

#ifdef NON_EQUIVALENT
void func_80008040(void) {
    u32 temp_v1;
    //? *phi_v1;
    s32 i;

    func_80002128(&D_80119C40, NULL, NULL);
    D_80119C48 = allocate_from_main_pool_safe(1440, COLOUR_TAG_CYAN);
    //D_80119C50 = allocate_from_main_pool_safe(160, COLOUR_TAG_CYAN);
    D_80119C44 = allocate_from_main_pool_safe(160, COLOUR_TAG_CYAN);
    D_800DC6E0 = 0;
    // phi_v1 = &D_80119C58;
    // do {
    //     temp_v1 = phi_v1 + 0x180;
    //     temp_v1->unk-8 = 0;
    //     phi_v1 = (? *) temp_v1;
    // } while (temp_v1 < (u32) &D_8011A6D8);
    // for (i = 0; i < 384; i++) {
    //     D_80119C48[i]->unk18 = 0;
    //     D_80119C48[i]->unk3C = 0;
    //     D_80119C48[i]->unk60 = 0;
    //     D_80119C48[i]->unk84 = 0;
    // }
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

#ifdef NON_EQUIVALENT
extern f32 D_80119C60[672];
extern f32 D_8011A6E0[336];//[7][48];
extern unk8011A6D8 **D_8011A6DC;
void func_80008174(void) {
    s32 i;
    s32 j;

    for (D_80119C4C = 0; D_80119C4C < 40; D_80119C4C++) {
        D_80119C50[D_80119C4C] = D_80119C48[D_80119C4C];
    }
    D_80119C4C--;

    for (i = 0; i < D_800DC6E0; i++) {
        D_80119C44[i]->unk12 = 0;
        if (D_80119C44[i]->unk18 != NULL) {
            func_8000488C(D_80119C44[i]->unk18);
        }
    }
    D_800DC6E0 = 0;

    for (i = 0; i < ARRAY_COUNT(D_80119C60); i++) {
        D_80119C58[i].unk16C = 0;
        if (D_80119C58[i].unk178 != 0) {
            if (D_80119C58[i].unk0.unk0_02 == 0) {
                func_8000488C(D_80119C58[i].unk178);
            } else if (D_80119C58[i].unk0.unk0_02 == 1) {
                func_800018E0();
            }
            D_80119C58[i].unk178 = 0;
        }
        D_80119C58[i].unk17C = -1;

        D_80119C60[i] = -100000.0;
    }

    for (i = 0; i < ARRAY_COUNT(D_8011A6E0); i++) {
        D_8011A6D8[i].unkB8 = -1;
        D_8011A6D8[i].unk0.unk0_01 = 0.0f;
        D_8011A6D8[i].unkBC = 0.0f;
        D_8011A6DC[i]->unk0.unk0_01 = -100000.0;
        D_8011A6E0[i] = -100000.0;
        // for (j = 0; j < ARRAY_COUNT(D_8011A6E0[0]); j++) {
        //     D_8011A6E0[i][j] = -100000.0;
        // }
    }
    
    D_8011AC18 = 0;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008174.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008438.s")

s32 func_800090C0(f32 arg0, f32 arg1, s32 arg2) {
    s32 temp_v1;
    s32 ret;
    f32 sp1C;

    sp1C = sqrtf((arg0 * arg0) + (arg1 * arg1));
    temp_v1 = 0xFFFF - arctan2_f(arg0, arg1);

    if (temp_v1 < arg2) {
        if (sp1C <= 1.0f) {
            ret = 64 - ((sins(arg2 - temp_v1) / 1024) * (sp1C * 1));
        } else {
            ret = 64 - (sins_2(arg2 - temp_v1) / 1024);
        }
    } else if (sp1C <= 1.0f) {
        ret = (sins(temp_v1 - arg2) / 1024) * (sp1C * 1) + 64;
    } else {
        ret = (sins_2(temp_v1 - arg2) / 1024) + 64;
    }

    if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
        ret = 128 - ret;
    }

    return ret;
}

//Best I can figure, this measures the distance between XYZ values.
s32 func_800092A8(f32 inX, f32 inY, f32 inZ, floatXYZVals *floatXYZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 dx, dy, dz;
    f32 x1, y1, z1;
    f32 x2, y2, z2;

    f32 temp;
    f32 ret;

    x1 = floatXYZ->x1;
    y1 = floatXYZ->y1;
    z1 = floatXYZ->z1;
    x2 = floatXYZ->x2;
    y2 = floatXYZ->y2;
    z2 = floatXYZ->z2;
    temp = 0.0f;

    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;

    if (dx == 0.0 && dy == 0.0 && dz == 0.0) {
        temp = 0.0f;
    } else {
        temp = ((inX - x1) * dx + (inY - y1) * dy + (inZ - z1) * dz) /
                (dx * dx + dy * dy + dz * dz);
    }

    if (temp < 0.0f) {
        *outX = x1;
        *outY = y1;
        *outZ = z1;
        dx = x1 - inX;
        dy = y1 - inY;
        dz = z1 - inZ;
        ret = sqrtf(dx * dx + dy * dy + dz * dz);
    } else if (temp > 1.0f) {
        *outX = x2;
        *outY = y2;
        *outZ = z2;
        dx = x2 - inX;
        dy = y2 - inY;
        dz = z2 - inZ;
        ret = sqrtf(dx * dx + dy * dy + dz * dz);
    } else {
        *outX = temp * dx + x1, // Comma required here as this was likely all one line.
        *outY = temp * dy + y1,
        *outZ = temp * dz + z1;

        ret = sqrtf((*outX - inX) * (*outX - inX) + (*outY - inY) * (*outY - inY) + (*outZ - inZ) * (*outZ - inZ));
    }

    return ret;
}

/**
 * Play Sound at position 
 */
void play_sound_at_position(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, s32 *soundMask) {
    func_8000974C(D_80119C40[soundId].unk0, x, y, z, arg4, D_80119C40[soundId].unk3,
        D_80119C40[soundId].unk2, D_80119C40[soundId].unk6, 0, D_80119C40[soundId].unk4,
        D_80119C40[soundId].unk8, soundMask);
}

void func_800095E8(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, f32 arg6, s32 *soundMask) {
    func_8000974C(soundId, x, y, z, arg4, 100, arg5, 15000, 0, arg6, 0x3F, soundMask);
}

#if 0
// I think this function is used to update the world position of any sound associated with the given soundmask.
//This matches, but it breaks update_player_racer
void update_spatial_audio_position(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->x = arg1;
    arg0->y = arg2;
    arg0->z = arg3;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/update_spatial_audio_position.s")
#endif

void func_800096F8(s32 arg0) {
    s32 i;
    s32 *v0 = (s32 *) D_80119C44;
    for (i = 0; i < 40; i++) {
        if (arg0 == *v0) {
            func_8000A2E8(i);
            break;
        }
        v0++;
    }
}

void func_8000974C(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, u8 arg6, u16 arg7, u8 arg8, u8 arg9, u8 argA, s32 *soundMask) {
    unk80119C50 *temp_v0;

    if (soundMask != 0) {
        func_800245B4(soundId | 0xE000);
    }
    if (D_800DC6E0 == 40) {
        if (soundMask != 0) {
            *soundMask = 0;
        }
        func_800245B4(-0x55AB);
        return;
    }
    temp_v0 = D_80119C50[D_80119C4C--];
    temp_v0->x = x;
    temp_v0->y = y;
    temp_v0->z = z;
    temp_v0->soundId = soundId;
    temp_v0->unk11 = arg4;
    temp_v0->unk10 = arg5;
    temp_v0->unkE = arg6;
    temp_v0->unkF = arg9;
    temp_v0->unk14 = arg7;
    temp_v0->unk20 = arg8;
    temp_v0->unk21 = argA;
    temp_v0->unk22 = 0;
    temp_v0->soundMask = soundMask;
    D_80119C44[D_800DC6E0++] = temp_v0;
    if (soundMask != 0) {
        *soundMask = (u32) temp_v0;
    }
}

void func_800098A4(u8 arg0, u16 soundId, f32 x, f32 y, f32 z, u8 arg5, u8 arg6,
                   u8 arg7, u8 arg8, u16 arg9, u8 argA, u8 argB, u8 argC) {
    Vec3f *temp_a0;
    unk80119C58 *temp_v1;

    if ((argB < 7) && (argC < 30)) {
        temp_v1 = &D_80119C58[argB];
        temp_a0 = &temp_v1->unk4 + argC * 3; //This can't be right...
        temp_a0->x = x;
        temp_a0->y = y;
        temp_a0->z = z;
        if (argC == 0) {
            (&D_80119C58[argB])->unk16C = soundId;
            (&D_80119C58[argB])->unk0.unk0_02 = arg0;
            (&D_80119C58[argB])->unk170 = arg9;
            (&D_80119C58[argB])->unk17D = argA;
            (&D_80119C58[argB])->unk174 = arg6;
            (&D_80119C58[argB])->unk175 = arg5;
            (&D_80119C58[argB])->unk176 = arg7;
            (&D_80119C58[argB])->unk17E = arg8;
        }
        if ((&D_80119C58[argB])->unk17C < argC) {
            (&D_80119C58[argB])->unk17C = argC;
        }
    }
}

#ifdef NON_MATCHING
// single regalloc diff
void func_80009968(f32 x, f32 y, f32 z, u8 arg3, u8 arg4, u8 arg5) {
    Vec3f *temp_a1;
    unk8011A6D8 *temp_v1;

    if ((arg4 < 7) && (arg5 < 15)) {
        temp_v1 = &D_8011A6D8[arg4];
        temp_a1 = (Vec3f *) &temp_v1->unk4 + arg5 * 1;
        temp_a1->x = x;
        temp_a1->y = y;
        temp_a1->z = z;
        if (arg5 == 0) {
            temp_v1->unk0.unk0_02 = arg3 & 0xFF;
        }
        if (temp_v1->unkB8 < arg5) {
             temp_v1->unkB8 = arg5;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009968.s")
#endif

s32 func_800099EC(u8 arg0) {
    s32 ret;
    f32 *var_a2;
    f32 temp_f0;
    s32 i;
    unk80119C58 *temp_v0;

    ret = 1;
    temp_v0 = &D_80119C58[arg0];
    var_a2 = (f32 *) &temp_v0->unk4;
    if (temp_v0->unk17C <= 0) {
        return 0;
    }

    for (i = 0; i < temp_v0->unk17C; i++) {
        temp_f0 = *var_a2;
        if (temp_f0 == -100000.0 || temp_f0 + 1 == -100000.0 || temp_f0 + 2 == -100000.0) {
            ret = 0;
        }
        var_a2 += 3;
    }

    return ret;
}

s32 func_80009AB4(u8 arg0) {
    s32 ret;
    s32 i;
    unk8011A6D8 *levelHeader;
    unk8011A6D8_04 *var_a2; //Probably a Vec3f
    
    ret = 1;
    levelHeader = &D_8011A6D8[arg0];
    var_a2 = (unk8011A6D8_04 *) &levelHeader->unk4;

    if (levelHeader->unkB8 <= 0) {
        return 0;
    }

    for (i = 0; i < levelHeader->unkB8; i++, var_a2++) {
        if ((var_a2->unk0 == -100000.0) || 
            (var_a2->unk0 + 1 == -100000.0) || 
            (var_a2->unk0 + 2 == -100000.0)) {
            ret = 0;
        }
    }

    return ret;
}

#ifdef NON_EQUIVALENT
u8 func_80009D6C(unk8011A6D8 *, f32, f32, f32);    /* extern */

void func_80009B7C(s32 *soundState, f32 x, f32 y, f32 z) {
    s32 j;
    f32 outX;
    f32 outY;
    f32 outZ;
    s32 levelSegmentIndex;
    f32 *yVals;
    s32 distBetween;
    s32 numOfYVals;
    s32 temp_v0_4;
    s32 volume;
    s32 var_s6;
    s32 i;
    s32 k;

    levelSegmentIndex = get_level_segment_index_from_position(x, y, z);
    volume = 0;
    var_s6 = 0x190;
    for (i = 0; i < 7; i++) {
        if (D_8011A6D8[i].unk0.unk0_02 != 0) {
            if (func_80009AB4(i & 0xFF) != 0) {
                for (j = 0; j < D_8011A6D8[i].unkB8; j++) {
                    distBetween = func_800092A8(x, y, z, &D_8011A6D8[i].unk4.unk4_02[j], &outX, &outY, &outZ);
                    if (distBetween < var_s6) {
                        numOfYVals = func_8002BAB0(levelSegmentIndex, x, z, yVals);
                        for (k = 0; k < numOfYVals; k++) {
                            if (y < yVals[k]) {
                                var_s6 = distBetween;
                                temp_v0_4 = func_80009D6C(&D_8011A6D8[i], outX, outY, outZ);
                                if (volume < temp_v0_4) {
                                    volume = temp_v0_4 & 0xFF;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (soundState != NULL) {
        func_800049F8((s32) soundState, 0x100, (u32) volume);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009B7C.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009D6C.s")

#ifdef NON_EQUIVALENT
extern unk80119C58 **D_80119C5C;
extern unk8011A6D8 **D_8011A6DC;
void func_8000A184(Gfx **arg0, Vertex **arg1, Triangle **arg2) {
    s32 i, j;

    for (i = 0; i < 7; i++) {
        if (D_80119C58[i].unk16C != 0) {
            for (j = 0; j < D_80119C58[i].unk17C; j++) {
                func_8000A414(arg0, arg1, arg2, (floatXYZVals *) &D_80119C5C[i], 0xFF, 0xFF, 0);
            }
        }
    }

    for (i = 0; i < 7; i++) {
        if (D_8011A6D8[i].unk0.unk0_02 != 0) {
            for (j = 0; j < D_8011A6D8[i].unkB8; j++) {
                func_8000A414(arg0, arg1, arg2, (floatXYZVals *) &D_8011A6DC[i], 0xFF, 0xFF, 0);
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A184.s")
#endif

void func_8000A2E8(s32 arg0) {
    if (D_800DC6E0 != 0) {
        if (D_80119C44[arg0]->unk18 != 0) {
            func_8000488C(D_80119C44[arg0]->unk18);
        }
        if (D_80119C44[arg0]->soundMask != 0) {
            *D_80119C44[arg0]->soundMask = 0;
            func_800245B4(D_80119C44[arg0]->soundId | 0x5000);
        }
        D_80119C4C++;
        D_80119C50[D_80119C4C] = D_80119C44[arg0];
        D_80119C44[arg0] = D_80119C44[D_800DC6E0 - 1];
        D_800DC6E0--;
    }
}

void func_8000A414(Gfx **dlist, Vertex **verts, Triangle **tris, floatXYZVals *arg3, u8 red, u8 green, u8 blue) {
    Gfx *temp_dlist;
    Vertex *temp_verts;
    Triangle *temp_tris;
    s16 x1;
    s16 y1;
    s16 z1;
    s16 x2;
    s16 y2;
    s16 z2;

    x1 =  arg3->x1;
    y1 =  arg3->y1;
    z1 =  arg3->z1;
    x2 =  arg3->x2;
    y2 =  arg3->y2;
    z2 =  arg3->z2;
    temp_dlist = *dlist;
    
    temp_verts = *verts;
    temp_tris = *tris;
    load_and_set_texture_no_offset(&temp_dlist, NULL, RENDER_NONE);
    gSPVertexDKR(temp_dlist++, OS_PHYSICAL_TO_K0(temp_verts), 4, 0);
    gSPPolygon(temp_dlist++, OS_PHYSICAL_TO_K0(temp_tris), 2, 0);
    temp_verts[0].x = x1;
    temp_verts[0].y = (y1 + 5);
    temp_verts[0].z = z1;
    temp_verts[0].r = red;
    temp_verts[0].g = green;
    temp_verts[0].b = blue;
    temp_verts[0].a = 255;
    temp_verts[1].x = x1;
    temp_verts[1].y = (y1 - 5);
    temp_verts[1].z = z1;
    temp_verts[1].r = red;
    temp_verts[1].g = green;
    temp_verts[1].b = blue;
    temp_verts[1].a = 255;
    temp_verts[2].x = x2;
    temp_verts[2].y = (y2 + 5);
    temp_verts[2].z = z2;
    temp_verts[2].r = 255;
    temp_verts[2].g = 255;
    temp_verts[2].b = 255;
    temp_verts[2].a = 255;
    temp_verts[3].x = x2;
    temp_verts[3].y = (y2 - 5);
    temp_verts[3].z = z2;
    temp_verts[3].r = 255;
    temp_verts[3].g = 255;
    temp_verts[3].b = 255;
    temp_verts[3].a = 255;
    temp_verts += 4;
    
    temp_tris[0].flags = 0x40; // 0x40 = Draw backface.
    temp_tris[0].vi0 = 2;
    temp_tris[0].vi1 = 1;
    temp_tris[0].vi2 = 0;
    temp_tris[0].uv0.u = 0x3E0;
    temp_tris[0].uv0.v = 0x3E0;
    temp_tris[0].uv1.u = 0x3E0;
    temp_tris[0].uv1.v = 0;
    temp_tris[0].uv2.u = 1;
    temp_tris[0].uv2.v = 0;
    temp_tris[1].flags = 0x40;
    temp_tris[1].vi0 = 3;
    temp_tris[1].vi1 = 2;
    temp_tris[1].vi2 = 1;
    temp_tris[1].uv0.u = 1;
    temp_tris[1].uv0.v = 0x3E0;
    temp_tris[1].uv1.u = 0x3E0;
    temp_tris[1].uv1.v = 0x3E0;
    temp_tris[1].uv2.u = 1;
    temp_tris[1].uv2.v = 0;
    temp_tris += 2;
    
    *dlist = temp_dlist;
    *verts = temp_verts;
    *tris = temp_tris;
}
