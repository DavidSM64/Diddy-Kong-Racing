#include "audio_spatial.h"
#include "types.h"
#include "macros.h"
#include "audio_vehicle.h"
#include "memory.h"
#include "audio.h"
#include "textures_sprites.h"
#include "objects.h"
#include "audiosfx.h"
#include "tracks.h"
#include "math_util.h"

/************ .data ************/

u16 gUsedMasks = 0;

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

SoundData *D_80119C40;
SoundMask **gSoundMaskHeapUsed;
SoundMask *gSoundMaskHeap; // 0x24 struct size - 0x5A0 total size - should be 40 elements
u8 gFreeMasks;
SoundMask **gSoundMaskHeapFree;
unk80119C58 D_80119C58[7];
unk8011A6D8 D_8011A6D8[7]; // Reverb stuff
s8 gAudioLinesOff;
s32 D_8011AC1C;

#define SOUND_MASK_HEAP_COUNT 40

/*******************************/

void audioline_init(void) {
    s32 i;

    sound_table_properties(&D_80119C40, NULL, NULL);
    gSoundMaskHeap = mempool_alloc_safe(sizeof(SoundMask) * SOUND_MASK_HEAP_COUNT, COLOUR_TAG_CYAN);
    gSoundMaskHeapFree = mempool_alloc_safe(sizeof(uintptr_t) * SOUND_MASK_HEAP_COUNT, COLOUR_TAG_CYAN);
    gSoundMaskHeapUsed = mempool_alloc_safe(sizeof(uintptr_t) * SOUND_MASK_HEAP_COUNT, COLOUR_TAG_CYAN);
    gUsedMasks = 0;
    for (i = 0; i < ARRAY_COUNT(D_80119C58); i++) {
        D_80119C58[i].soundPtr = NULL;
    }
    for (i = 0; i < SOUND_MASK_HEAP_COUNT; i++) {
        gSoundMaskHeap[i].soundPtr = NULL;
    }
    audioline_reset();
}

/**
 * Stop any playing jingles, then block audio lines from playing anymore.
 * Official Name: amAmbientPause
 */
void audioline_off(void) {
    music_jingle_stop();
    gAudioLinesOff = TRUE;
}

/**
 * Allow audio lines to play jingles.
 * Official Name: amAmbientRestart
 */
void audioline_on(void) {
    gAudioLinesOff = FALSE;
}

void audioline_reset(void) {
    s32 i;
    s32 j;
    SoundHandle sound;
    SoundMask *heap;
    f32 *ptr;

    heap = gSoundMaskHeap;
    gFreeMasks = 0;
    while (gFreeMasks < SOUND_MASK_HEAP_COUNT) {
        gSoundMaskHeapFree[gFreeMasks] = heap;
        heap++;
        gFreeMasks++;
    }

    gFreeMasks--;

    for (i = 0; i < gUsedMasks; i++) {
        sound = gSoundMaskHeapUsed[i]->soundPtr;
        gSoundMaskHeapUsed[i]->unk12 = 0;
        if (sound != NULL) {
            sndp_stop(sound);
        }
    }
    gUsedMasks = 0;

    for (i = 0; i < 7; i++) {
        D_80119C58[i].soundID = 0;
        if (D_80119C58[i].soundPtr != 0) {
            if (D_80119C58[i].unk0_02 == 0) {
                sndp_stop(D_80119C58[i].soundPtr);
            } else if (D_80119C58[i].unk0_02 == 1) {
                music_jingle_stop();
            }
            D_80119C58[i].soundPtr = NULL;
        }
        D_80119C58[i].unk17C = -1;

        ptr = D_80119C58[i].unk4_floats;
        for (j = 0; j < 30; j++) {
            *ptr++ = -100000.0f;
            *ptr++ = -100000.0f;
            *ptr++ = -100000.0f;
        }
    }

    for (i = 0; i < 7; i++) {
        D_8011A6D8[i].unkB8 = -1;
        D_8011A6D8[i].unk0_02 = 0;
        D_8011A6D8[i].unkBC = 0.0f;

        ptr = D_8011A6D8[i].unk4_floats;
        for (j = 0; j < 15; j++) {
            *ptr++ = -100000.0f;
            *ptr++ = -100000.0f;
            *ptr++ = -100000.0f;
        }
    }

    gAudioLinesOff = 0;
}

// audioline_ambient
// Official Name: amPlayAudioMap
#ifdef NON_EQUVALENT
void func_80008438(Object **objRacers, s32 numRacers, s32 updateRate) {
    s32 sp260;
    s32 sp254;
    s32 sp250;
    s32 sp24C;
    s32 sp248;
    s32 sp244;
    f32 sp22C;
    f32 sp228;
    f32 sp224;
    s32 sp1A8;
    s32 sp12C;
    s32 spB0;
    ObjectSegment *spAC;
    f32 spA8;
    f32 sp98;
    f32 sp90;
    unk80119C58 *sp88;
    f32 *sp70;
    ALSoundState *temp_a0_3;
    ALSoundState *temp_a0_4;
    ALSoundState *var_a0_3;
    ObjectSegment *temp_s3;
    ObjectSegment *var_s3;
    ObjectSegment *var_s3_2;
    f32 *var_s4_2;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f12;
    f32 temp_f16_3;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f22_3;
    f32 temp_f2;
    f32 temp_f4;
    f32 var_f10;
    f32 var_f10_2;
    f32 var_f18;
    f32 var_f24;
    f32 var_f4;
    f32 var_f6;
    s32 *temp_v1_3;
    s32 *var_s0;
    s32 *var_s0_2;
    s32 *var_s1;
    s32 *var_s1_2;
    s32 *var_v0_5;
    s32 *var_v0_6;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_f16;
    s32 temp_f16_2;
    s32 temp_f8;
    s32 temp_t1;
    s32 temp_t4;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_at;
    s32 var_fp;
    s32 var_fp_2;
    s32 var_fp_3;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v1;
    s8 var_v1_2;
    u8 temp_t1_2;
    u8 temp_t6;
    u8 temp_t8;
    u8 temp_t9;
    u8 temp_t9_2;
    u8 temp_v0;
    u8 temp_v0_2;
    unk80119C58 *var_v0_3;
    SoundMask *temp_s1;
    s32 *spB8;

    sp24C = 0;
    spB0 = set_active_viewports_and_max(get_viewport_count());
    spAC = get_cutscene_camera_segment();
    sp260 = 0;
    if ((s32) gUsedMasks > 0) {
        var_s4 = 0;
        do {
            temp_s1 = *(gSoundMaskHeapUsed + var_s4);
            sp254 = 0;
            if (temp_s1->unk11 & 2) {
                if (spB0 == 1) {
                    temp_f20 = temp_s1->pos.x - spAC->trans.x_position;
                    temp_f0 = temp_s1->pos.y - spAC->trans.y_position;
                    temp_f22 = temp_s1->pos.z - spAC->trans.z_position;
                    temp_a0 = temp_s1->distance;
                    temp_f16 = (s32) sqrtf((temp_f20 * temp_f20) + (temp_f0 * temp_f0) + (temp_f22 * temp_f22));
                    var_at = temp_a0 < temp_f16;
                    if ((temp_f16 < temp_a0) && (var_at = temp_a0 < temp_f16, (temp_s1->unk12 == 0))) {
                        if ((temp_s1->soundPtr == NULL) && ((temp_s1->unk22 == 0) || !(temp_s1->unk11 & 4))) {
                            func_80001F14(temp_s1->soundId, temp_s1 + 24);
                            temp_s1->unk22 = 1U;
                        }
                        if (temp_s1->soundPtr != NULL) {
                            temp_t8 = temp_s1->pitch;
                            var_f4 = (f32) temp_t8;
                            if ((s32) temp_t8 < 0) {
                                var_f4 += 4294967296.0f;
                            }
                            spA8 = var_f4 / 100.0f;
                            sndp_set_param(temp_s1->soundPtr, 8, temp_s1->volume << 8);
                            sndp_set_param(temp_s1->soundPtr, 0x10, *((u32 *) &spA8));
                            var_a2 = func_800090C0(temp_f20, temp_f22, (s32) spAC->trans.rotation.x);
                            if (spB0 != 1) {
                                var_a2 = 0x40;
                            }
                            sndp_set_param(temp_s1->soundPtr, 4, (u32) var_a2);
                            audioline_reverb(temp_s1->soundPtr, temp_s1->pos.x, temp_s1->pos.y, temp_s1->pos.z);
                            sndp_set_priority(temp_s1->soundPtr, temp_s1->unk21);
                        }
                        temp_s1->unk12 = 1U;
                    } else if ((var_at != 0) && (temp_s1->unk12 != 0)) {
                        temp_s1->unk12 = 0U;
                    }
                }
            } else {
                var_fp = 0;
                if (spB0 > 0) {
                    var_s3 = spAC;
                    do {
                        temp_f20_2 = temp_s1->pos.x - var_s3->trans.x_position;
                        temp_f0_2 = temp_s1->pos.y - var_s3->trans.y_position;
                        temp_f22_2 = temp_s1->pos.z - var_s3->trans.z_position;
                        temp_a0_2 = temp_s1->distance;
                        temp_f8 = (s32) sqrtf((temp_f20_2 * temp_f20_2) + (temp_f0_2 * temp_f0_2) + (temp_f22_2 * temp_f22_2));
                        if (temp_f8 < temp_a0_2) {
                            if (temp_s1->unk20 == 0) {
                                temp_t6 = temp_s1->volume;
                                var_f18 = (f32) temp_t6;
                                if ((s32) temp_t6 < 0) {
                                    var_f18 += 4294967296.0f;
                                }
                                var_v0 = (s32) ((1.0f - ((f32) temp_f8 / (f32) temp_a0_2)) * var_f18);
                            } else {
                                temp_t9 = temp_s1->volume;
                                temp_f0_3 = (f32) (temp_a0_2 - temp_f8) / (f32) temp_a0_2;
                                var_f10 = (f32) temp_t9;
                                if ((s32) temp_t9 < 0) {
                                    var_f10 += 4294967296.0f;
                                }
                                var_v0 = (s32) (temp_f0_3 * temp_f0_3 * var_f10);
                            }
                            if (sp254 < var_v0) {
                                sp254 = var_v0;
                                sp250 = func_800090C0(temp_f20_2, temp_f22_2, (s32) var_s3->trans.rotation.x);
                            }
                        }
                        var_fp += 1;
                        var_s3 += 0x44;
                    } while (var_fp != spB0);
                }
                if (sp254 < (s32) temp_s1->unk10) {
                    var_f24 = 999999.0f;
                    var_fp_2 = 0;
                    if (spB0 > 0) {
                        var_s3_2 = spAC;
                        do {
                            temp_f20_3 = temp_s1->pos.x - var_s3_2->trans.x_position;
                            temp_f0_4 = temp_s1->pos.y - var_s3_2->trans.y_position;
                            temp_f22_3 = temp_s1->pos.z - var_s3_2->trans.z_position;
                            temp_f16_2 = (s32) sqrtf((temp_f20_3 * temp_f20_3) + (temp_f0_4 * temp_f0_4) + (temp_f22_3 * temp_f22_3));
                            if ((f32) temp_f16_2 < var_f24) {
                                sp250 = func_800090C0(temp_f20_3, temp_f22_3, (s32) var_s3_2->trans.rotation.x);
                                var_f24 = (f32) temp_f16_2;
                            }
                            var_fp_2 += 1;
                            var_s3_2 += 0x44;
                        } while (var_fp_2 != spB0);
                    }
                    sp254 = (s32) temp_s1->unk10;
                }
                if (sp254 >= 0xB) {
                    if ((temp_s1->soundPtr == NULL) && ((temp_s1->unk22 == 0) || !(temp_s1->unk11 & 4))) {
                        func_80001F14(temp_s1->soundId, temp_s1 + 0x18);
                        temp_s1->unk22 = 1U;
                    }
                    if (temp_s1->soundPtr != NULL) {
                        temp_t1_2 = temp_s1->pitch;
                        var_f10_2 = (f32) temp_t1_2;
                        if ((s32) temp_t1_2 < 0) {
                            var_f10_2 += 4294967296.0f;
                        }
                        sp98 = var_f10_2 / 100.0f;
                        sndp_set_param(temp_s1->soundPtr, 8, sp254 << 8);
                        sndp_set_param(temp_s1->soundPtr, 0x10, *((u32 *) &sp98));
                        if (spB0 != 1) {
                            sp250 = 0x40;
                        }
                        sndp_set_param(temp_s1->soundPtr, 4, (u32) sp250);
                        sndp_set_priority(temp_s1->soundPtr, temp_s1->unk21);
                        audioline_reverb(temp_s1->soundPtr, temp_s1->pos.x, temp_s1->pos.y, temp_s1->pos.z);
                    }
                    var_v0_2 = temp_s1->unk11 & 4;
                } else {
                    temp_a0_3 = temp_s1->soundPtr;
                    if (temp_a0_3 != NULL) {
                        sndp_stop(temp_a0_3);
                        var_v0_2 = temp_s1->unk11 & 4;
                    } else {
                        temp_s1->unk22 = 1U;
                        var_v0_2 = temp_s1->unk11 & 4;
                    }
                }
                if ((var_v0_2 != 0) && (temp_s1->unk22 != 0) && (temp_s1->soundPtr == NULL)) {
                    func_8000A2E8(sp260);
                }
            }
            temp_t1 = sp260 + 1;
            sp260 = temp_t1;
            var_s4 += 4;
        } while (temp_t1 < (s32) gUsedMasks);
        sp260 = 0;
    }
    var_v0_3 = D_80119C58;
    do {
        sp88 = var_v0_3;
        if (var_v0_3->soundID != 0) {
            sp88 = var_v0_3;
            if (func_800099EC(var_v0_3->unk0_02/*unksp263*/) != 0) {
                sp254 = 0;
                var_fp_3 = 0;
                if (spB0 > 0) {
                    sp70 = sp88->unk4_floats;
                    do {
                        var_s4_2 = sp70;
                        var_v1 = sp88->unk170;
                        var_s5 = 0;
                        var_s2 = 0;
                        var_s6 = var_v1;
                        if (sp88->unk17C > 0) {
                            var_s0 = &sp1A8;
                            var_s1 = &sp12C;
                            temp_s3 = &spAC[var_fp_3];
                            do {
                                *var_s0 = audioline_distance(temp_s3->trans.x_position, temp_s3->trans.y_position, temp_s3->trans.z_position, var_s4_2, &sp22C, &sp228, &sp224);
                                temp_v1 = *var_s0;
                                *var_s1 = func_800090C0(sp22C - temp_s3->trans.x_position, sp224 - temp_s3->trans.z_position, (s32) temp_s3->trans.rotation.x);
                                var_s4_2 += 0xC;
                                if (temp_v1 < var_s6) {
                                    var_s6 = temp_v1;
                                }
                                var_s2 += 1;
                                var_s0 += 4;
                                var_s1 += 4;
                                var_s5 += temp_v1;
                            } while (var_s2 < var_v0_3->unk17C);
                            var_v1 = sp88->unk170;
                        }
                        temp_f2 = (f32) var_v1;
                        temp_f12 = (f32) sp88->unk174;
                        if (sp88->unk17D == 0) {
                            var_v0_4 = (s32) ((1.0f - ((f32) var_s6 / temp_f2)) * temp_f12);
                        } else {
                            temp_f0_5 = (f32) (var_v1 - var_s6) / temp_f2;
                            var_v0_4 = (s32) (temp_f0_5 * temp_f0_5 * temp_f12);
                        }
                        if (var_v0_4 >= sp254) {
                            sp254 = var_v0_4;
                            var_v1_2 = sp88->unk17C;
                            var_a0 = 0;
                            if (var_v1_2 == 1) {
                                sp250 = sp12C;
                            } else {
                                var_s2_2 = 0;
                                sp250 = 0;
                                if (var_v1_2 > 0) {
                                    var_s0_2 = &sp1A8;
                                    var_v0_5 = &spB8[0];
                                    do {
                                        var_s2_2 += 1;
                                        temp_v1_2 = var_s5 - *var_s0_2;
                                        *var_v0_5 = temp_v1_2;
                                        var_s0_2 += 4;
                                        var_v0_5 += 4;
                                        var_a0 += temp_v1_2;
                                    } while (var_s2_2 < var_v0_3->unk17C);
                                    var_v1_2 = sp88->unk17C;
                                }
                                var_s1_2 = &sp12C;
                                if (var_v1_2 > 0) {
                                    var_v0_6 = &spB8[0];
                                    var_a0_2 = sp250;
                                    temp_v1_3 = &var_v0_6[var_v0_3->unk17C];
                                    do {
                                        temp_f16_3 = (f32) *var_v0_6;
                                        var_v0_6 += 4;
                                        temp_f4 = (f32) *var_s1_2;
                                        var_s1_2 += 4;
                                        var_a0_2 = (s32) ((f32) var_a0_2 + ((temp_f16_3 / (f32) var_a0) * temp_f4));
                                    } while ((u32) var_v0_6 < (u32) temp_v1_3);
                                    sp250 = var_a0_2;
                                }
                            }
                            if (var_s6 < 0x190) {
                                sp250 = (s32) (((f32) (sp250 - 0x40) * ((f32) var_s6 / 400.0f)) + 64.0f);
                            }
                        }
                        var_fp_3 += 1;
                    } while (var_fp_3 != spB0);
                }
                temp_v0 = sp88->unk0_02;
                if (temp_v0 == 0) {
                    temp_v0_2 = sp88->unk175;
                    if (sp254 < (s32) temp_v0_2) {
                        sp254 = (s32) temp_v0_2;
                    }
                    if (sp254 >= 0xB) {
                        temp_t9_2 = sp88->unk176;
                        var_f6 = (f32) temp_t9_2;
                        if ((s32) temp_t9_2 < 0) {
                            var_f6 += 4294967296.0f;
                        }
                        sp90 = var_f6 / 100.0f;
                        var_a0_3 = sp88->soundPtr;
                        if (var_a0_3 == NULL) {
                            func_80001F14(sp88->soundID, (s32 *) &sp88->soundPtr);
                            var_a0_3 = sp88->soundPtr;
                        }
                        if (var_a0_3 != NULL) {
                            sndp_set_param(var_a0_3, 8, sp254 << 8);
                            sndp_set_param(sp88->soundPtr, 0x10, *((u32 *) &sp90));
                            if (spB0 != 1) {
                                sp250 = 0x40;
                            }
                            sndp_set_param(sp88->soundPtr, 4, (u32) sp250);
                            sndp_set_priority(sp88->soundPtr, sp88->unk17E);
                        }
                    } else {
                        temp_a0_4 = sp88->soundPtr;
                        if (temp_a0_4 != NULL) {
                            sndp_stop(temp_a0_4);
                        }
                    }
                } else if ((temp_v0 == 1) && (sp24C < sp254)) {
                    sp24C = sp254;
                    sp248 = sp250;
                    sp244 = sp88->soundID;
                }
            }
        }
        temp_t4 = sp260 + 1;
        sp260 = temp_t4;
        var_v0_3 = &sp88[1];
    } while (temp_t4 != 7);
    if ((sp24C >= 0xB) && ((u8) gAudioLinesOff == 0)) {
        if (sp244 != music_jingle_current()) {
            music_jingle_play_safe(var_v0_3->unk0_02/*unksp247*/);
        }
        music_jingle_volume_set(var_v0_3->unk0_05/*unksp24F*/);
        music_jingle_pan_set(var_v0_3->unk0_03/*unksp24B*/);
    } else {
        music_jingle_stop();
    }
    if (numRacers != 0) {
        func_80006FC8(objRacers, numRacers, spAC, spB8[0]/*unkspB3*/, updateRate);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio_spatial/func_80008438.s")
#endif

/**
 * Official Name: amCalcSfxStereo
 */
s32 func_800090C0(f32 x, f32 z, s32 yRot) {
    s32 temp_v1;
    s32 ret;
    f32 sp1C;

    sp1C = sqrtf((x * x) + (z * z));
    temp_v1 = 0xFFFF - arctan2_f(x, z);

    if (temp_v1 < yRot) {
        if (sp1C <= 1.0f) {
            ret = 64 - ((sins_s16(yRot - temp_v1) / 1024) * (sp1C * 1));
        } else {
            ret = 64 - (sins_2(yRot - temp_v1) / 1024);
        }
    } else if (sp1C <= 1.0f) {
        ret = (sins_s16(temp_v1 - yRot) / 1024) * (sp1C * 1) + 64;
    } else {
        ret = (sins_2(temp_v1 - yRot) / 1024) + 64;
    }

    if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
        ret = 128 - ret;
    }

    return ret;
}

/**
 * Calculates the position between two points, then the distance from the nearest point.
 * Write the adjusted positions to the arguments.
 * Returns the distance between the input and the nearest endpoint.
 */
s32 audioline_distance(f32 inX, f32 inY, f32 inZ, f32 coords[6], f32 *outX, f32 *outY, f32 *outZ) {
    f32 dx, dy, dz;
    f32 x1, y1, z1;
    f32 x2, y2, z2;

    f32 mag;
    f32 ret;

    x1 = coords[0];
    y1 = coords[1];
    z1 = coords[2];
    x2 = coords[3];
    y2 = coords[4];
    z2 = coords[5];
    mag = 0.0f;

    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;

    if (dx == 0.0 && dy == 0.0 && dz == 0.0) {
        mag = 0.0f;
    } else {
        mag = ((inX - x1) * dx + (inY - y1) * dy + (inZ - z1) * dz) / (dx * dx + dy * dy + dz * dz);
    }

    if (mag < 0.0f) {
        *outX = x1;
        *outY = y1;
        *outZ = z1;
        dx = x1 - inX;
        dy = y1 - inY;
        dz = z1 - inZ;
        ret = sqrtf(dx * dx + dy * dy + dz * dz);
    } else if (mag > 1.0f) {
        *outX = x2;
        *outY = y2;
        *outZ = z2;
        dx = x2 - inX;
        dy = y2 - inY;
        dz = z2 - inZ;
        ret = sqrtf(dx * dx + dy * dy + dz * dz);
    } else {
        *outX = mag * dx + x1, // Comma required here as this was likely all one line.
            *outY = mag * dy + y1, *outZ = mag * dz + z1;

        ret = sqrtf((*outX - inX) * (*outX - inX) + (*outY - inY) * (*outY - inY) + (*outZ - inZ) * (*outZ - inZ));
    }

    return ret;
}

/**
 * Play Sound at position
 * Official Name: amSndPlayXYZ
 */
void play_sound_at_position(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, SoundMask **soundMask) {
    func_8000974C(D_80119C40[soundId].soundBite, x, y, z, arg4, D_80119C40[soundId].unk3, D_80119C40[soundId].volume,
                  D_80119C40[soundId].distance, 0, D_80119C40[soundId].pitch, D_80119C40[soundId].unk8, soundMask);
}

/**
 * Official Name: amSndPlayDirectXYZ
 */
void func_800095E8(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, f32 pitch, SoundMask **soundMask) {
    func_8000974C(soundId, x, y, z, arg4, 100, arg5, 15000, 0, pitch, 0x3F, soundMask);
}

/**
 * I think this function is used to update the world position of any sound associated with the given soundmask.
 * Official Name: amSndSetXYZ
 */
void update_spatial_audio_position(SoundMask *soundMask, f32 x, f32 y, f32 z) {
    soundMask->pos.x = x;
    soundMask->pos.y = y;
    soundMask->pos.z = z;
}

/**
 * Official Name: amSndStopXYZ
 */
void func_800096F8(SoundMask *soundMask) {
    s32 i;
    for (i = 0; i < SOUND_MASK_HEAP_COUNT; i++) {
        if (soundMask == gSoundMaskHeapUsed[i]) {
            func_8000A2E8(i);
            break;
        }
    }
}

/**
 * Official Name: amCreateAudioPoint
 */
void func_8000974C(u16 soundBite, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, u8 volume, u16 distance, u8 arg8, u8 pitch,
                   u8 argA, SoundMask **soundMask) {
    SoundMask *newMask;

    if (soundMask != NULL) {
        func_800245B4(soundBite | 0xE000);
    }
    if (gUsedMasks == SOUND_MASK_HEAP_COUNT) {
        if (soundMask != NULL) {
            *soundMask = NULL;
        }
        func_800245B4(0xAA55);
        return;
    }
    newMask = gSoundMaskHeapFree[gFreeMasks--];
    newMask->pos.x = x;
    newMask->pos.y = y;
    newMask->pos.z = z;
    newMask->soundId = soundBite;
    newMask->unk11 = arg4;
    newMask->unk10 = arg5;
    newMask->volume = volume;
    newMask->pitch = pitch;
    newMask->distance = distance;
    newMask->unk20 = arg8;
    newMask->unk21 = argA;
    newMask->unk22 = 0;
    newMask->soundMask = soundMask;
    gSoundMaskHeapUsed[gUsedMasks++] = newMask;
    if (soundMask != NULL) {
        *soundMask = newMask;
    }
}

void audioline_ambient_create(u8 arg0, u16 soundId, f32 x, f32 y, f32 z, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u16 arg9,
                              u8 argA, u8 lineID, u8 argC) {
    unk80119C58 *temp_v1;
    f32 *temp_a0;

    if (lineID < 7 && argC < 30) {
        temp_v1 = &D_80119C58[lineID];
        temp_a0 = &temp_v1->unk4_floats[argC * 3];
        temp_a0[0] = x;
        temp_a0[1] = y;
        temp_a0[2] = z;
        if (argC == 0) {
            temp_v1->soundID = soundId;
            temp_v1->unk0_02 = arg0;
            temp_v1->unk170 = arg9;
            temp_v1->unk17D = argA;
            temp_v1->unk174 = arg6;
            temp_v1->unk175 = arg5;
            temp_v1->unk176 = arg7;
            temp_v1->unk17E = arg8;
        }
        if (temp_v1->unk17C < argC) {
            temp_v1->unk17C = argC;
        }
    }
}

void audioline_reverb_create(f32 x, f32 y, f32 z, u8 arg3, u8 arg4, u8 arg5) {
    unk8011A6D8 *temp;
    if (arg4 < ARRAY_COUNT(D_8011A6D8) && arg5 < 15) {
        temp = &D_8011A6D8[arg4];
        temp->unk4_floats[3 * arg5 + 0] = x;
        temp->unk4_floats[3 * arg5 + 1] = y;
        temp->unk4_floats[3 * arg5 + 2] = z;
        if (arg5 == 0) {
            temp->unk0_02 = arg3;
        }
        if (temp->unkB8 < arg5) {
            temp->unkB8 = arg5;
        }
    }
}

s32 func_800099EC(u8 arg0) {
    s32 ret;
    s32 i;
    unk80119C58 *temp_v0;
    f32 *var_a2;

    ret = 1;
    temp_v0 = &D_80119C58[arg0];
    var_a2 = temp_v0->unk4_floats;

    if (temp_v0->unk17C <= 0) {
        return 0;
    }

    for (i = 0; i < temp_v0->unk17C; i++) {
        //@bug should be *(var_a2 + 0), *(var_a2 + 1), *(var_a2 + 2)
        if (*var_a2 + 0 == -100000.0 || *var_a2 + 1 == -100000.0 || *var_a2 + 2 == -100000.0) {
            ret = 0;
        }
        var_a2 += 3;
    }

    return ret;
}

s32 func_80009AB4(u8 arg0) {
    s32 ret;
    s32 i;
    unk8011A6D8 *temp_v0;
    f32 *var_a2;

    ret = 1;
    temp_v0 = &D_8011A6D8[arg0];
    var_a2 = temp_v0->unk4_floats;

    if (temp_v0->unkB8 <= 0) {
        return 0;
    }

    for (i = 0; i < temp_v0->unkB8; i++) {
        //@bug should be *(var_a2 + 0), *(var_a2 + 1), *(var_a2 + 2)
        if (*var_a2 == -100000.0 || *var_a2 + 1 == -100000.0 || *var_a2 + 2 == -100000.0) {
            ret = 0;
        }
        var_a2 += 3;
    }

    return ret;
}

void audioline_reverb(SoundHandle soundHandle, f32 x, f32 y, f32 z) {
    s32 i;
    s32 j;
    unk8011A6D8 *temp;
    s32 k;
    f32 outX;
    f32 outY;
    f32 outZ;
    s32 distBetween;
    s32 maxDist;
    s32 levelSegmentIndex;
    s32 numOfYVals;
    u8 volume;
    u8 temp_v0_4;
    f32 *coords;
    f32 yVals[10];

    levelSegmentIndex = get_level_segment_index_from_position(x, y, z);
    volume = 0;
    maxDist = 400;
    for (i = 0; i < ARRAY_COUNT(D_8011A6D8); i++) {
        temp = &D_8011A6D8[i];
        if (temp->unk0_02 != 0) {
            if (func_80009AB4(i) != 0) {
                coords = temp->unk4_floats;
                for (j = 0; j < temp->unkB8; j++) {
                    distBetween = audioline_distance(x, y, z, coords, &outX, &outY, &outZ);
                    if (distBetween < maxDist) {
                        numOfYVals = func_8002BAB0(levelSegmentIndex, x, z, yVals);
                        for (k = 0; k < numOfYVals; k++) {
                            if (y < yVals[k]) {
                                maxDist = distBetween;
                                temp_v0_4 = func_80009D6C(&D_8011A6D8[i], outX, outY, outZ);
                                if (volume < temp_v0_4) {
                                    volume = temp_v0_4;
                                }
                            }
                        }
                    }
                    coords += 3;
                }
            }
        }
    }
    if (soundHandle != NULL) {
        sndp_set_param((SoundHandle) (s32) soundHandle, AL_SNDP_FX_EVT, (u32) volume);
    }
}

u8 func_80009D6C(unk8011A6D8 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    f32 *coords;
    f32 x1, y1, z1;
    f32 x2, y2, z2;
    f32 dx, dy, dz;
    f32 f20;
    f32 sp5C;
    f32 length;
    u8 sp57;
    f32 f12;

    if (arg0->unkBC == 0.0f) {
        coords = arg0->unk4_floats;
        for (f20 = 0.0f; f20 < arg0->unkB8; f20 += 1.0f) {
            deltaX = coords[3] - coords[0];
            deltaY = coords[4] - coords[1];
            deltaZ = coords[5] - coords[2];
            arg0->unkBC += sqrtf((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));
            coords += 3;
        }
    }

    coords = arg0->unk4_floats;
    sp5C = 0.0f;
    sp57 = FALSE;

    for (; !sp57; coords += 3) {
        x1 = coords[0];
        y1 = coords[1];
        z1 = coords[2];
        x2 = coords[3];
        y2 = coords[4];
        z2 = coords[5];
        dx = x2 - x1;
        dy = y2 - y1;
        dz = z2 - z1;
        length = sqrtf((dx * dx) + (dy * dy) + (dz * dz));

        if ((arg1 >= x1 && arg1 <= x2) || (arg1 >= x2 && arg1 <= x1)) {
            if (dx != 0.0f) {
                f12 = (arg1 - x1) / dx;
            } else if (dy != 0.0f) {
                f12 = (arg2 - y1) / dy;
            } else if (dz != 0.0f) {
                f12 = (arg3 - z1) / dz;
            } else {
                f12 = 0.0f;
            }

            if (ABS(dy * f12 + y1 - arg2) < 2.0f && ABS(dz * f12 + z1 - arg3) < 2.0f) {
                sp57 = TRUE;
                sp5C += f12 * length;
            } else {
                sp5C += length;
            }
        } else {
            sp5C += length;
        }
    }

    if (sp5C > arg0->unkBC / 2) {
        sp5C = arg0->unkBC - sp5C;
    }

    if (sp5C < 300.0f) {
        return arg0->unk0_02 * sp5C / 300.0f;
    } else {
        return arg0->unk0_02;
    }
}

void debug_render_audio_effects(Gfx **dList, Vertex **verts, Triangle **tris) {
    s32 i, j;
    f32 *coords;
    unk80119C58 *var_s2;
    unk8011A6D8 *var_s2_2;

    for (i = 0; i < ARRAY_COUNT(D_80119C58); i++) {
        var_s2 = &D_80119C58[i];
        coords = var_s2->unk4_floats;
        if (D_80119C58[i].soundID != 0) {
            for (j = 0; j < var_s2->unk17C; j++) {
                debug_render_line(dList, verts, tris, coords, 255, 255, 0);
                coords += 3;
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_8011A6D8); i++) {
        var_s2_2 = &D_8011A6D8[i];
        coords = var_s2_2->unk4_floats;
        if (D_8011A6D8[i].unk0_02 != 0) {
            for (j = 0; j < var_s2_2->unkB8; j++) {
                debug_render_line(dList, verts, tris, coords, 255, 0, 255);
                coords += 3;
            }
        }
    }
}

void func_8000A2E8(s32 arg0) {
    if (gUsedMasks != 0) {
        if (gSoundMaskHeapUsed[arg0]->soundPtr != 0) {
            sndp_stop(gSoundMaskHeapUsed[arg0]->soundPtr);
        }
        if (gSoundMaskHeapUsed[arg0]->soundMask != NULL) {
            *gSoundMaskHeapUsed[arg0]->soundMask = NULL;
            func_800245B4(gSoundMaskHeapUsed[arg0]->soundId | 0x5000);
        }
        gFreeMasks++;
        gSoundMaskHeapFree[gFreeMasks] = gSoundMaskHeapUsed[arg0];
        gSoundMaskHeapUsed[arg0] = gSoundMaskHeapUsed[gUsedMasks - 1];
        gUsedMasks--;
    }
}

/**
 * Generates and renders a coloured line visible from anywhere.
 * Allows use of a colour, that interpolates from bright to dark from the beginning to the end of the line.
 */
void debug_render_line(Gfx **dList, Vertex **verts, Triangle **tris, f32 coords[6], u8 red, u8 green, u8 blue) {
    Gfx *temp_dlist;
    Vertex *temp_verts;
    Triangle *temp_tris;
    s16 x1;
    s16 y1;
    s16 z1;
    s16 x2;
    s16 y2;
    s16 z2;

    x1 = coords[0];
    y1 = coords[1];
    z1 = coords[2];
    x2 = coords[3];
    y2 = coords[4];
    z2 = coords[5];
    temp_dlist = *dList;

    temp_verts = *verts;
    temp_tris = *tris;
    material_set_no_tex_offset(&temp_dlist, NULL, RENDER_NONE);
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

    temp_tris[0].flags = BACKFACE_DRAW;
    temp_tris[0].vi0 = 2;
    temp_tris[0].vi1 = 1;
    temp_tris[0].vi2 = 0;
    temp_tris[0].uv0.u = 1024 - 32;
    temp_tris[0].uv0.v = 1024 - 32;
    temp_tris[0].uv1.u = 1024 - 32;
    temp_tris[0].uv1.v = 0;
    temp_tris[0].uv2.u = 1;
    temp_tris[0].uv2.v = 0;
    temp_tris[1].flags = BACKFACE_DRAW;
    temp_tris[1].vi0 = 3;
    temp_tris[1].vi1 = 2;
    temp_tris[1].vi2 = 1;
    temp_tris[1].uv0.u = 1;
    temp_tris[1].uv0.v = 1024 - 32;
    temp_tris[1].uv1.u = 1024 - 32;
    temp_tris[1].uv1.v = 1024 - 32;
    temp_tris[1].uv2.u = 1;
    temp_tris[1].uv2.v = 0;
    temp_tris += 2;

    *dList = temp_dlist;
    *verts = temp_verts;
    *tris = temp_tris;
}
