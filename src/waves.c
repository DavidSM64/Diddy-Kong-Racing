/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D20 */

#include "waves.h"
#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "memory.h"
#include "textures_sprites.h"
#include "objects.h"
#include "tracks.h"
#include "math_util.h"

/************ .data ************/

f32 *D_800E3040 = NULL;
s32 *D_800E3044 = NULL;
s32 *D_800E3048 = NULL;
s32 *D_800E304C = NULL;

// Could be an array of pointers?
s32 D_800E3050[8] = {
    0, 0, 0, 0, 0, 0, 0, 0,
};

Vertex *D_800E3070[2] = { NULL, NULL };
s32 *D_800E3078[2] = { NULL, NULL };

// This could also be D_800E3080[2] + D_800E3088[2]
s32 *D_800E3080[4] = { NULL, NULL, NULL, NULL };

/* Size: 0x10, might just be an array? */
typedef struct unk800E3090 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
} unk800E3090;

unk800E3090 D_800E3090[4] = {
    { 0x4000, 0x0201, 0, 0, 0, 0, 0, 0, },
    { 0x4001, 0x0203, 0, 0, 0, 0, 0, 0, },
    { 0x4000, 0x0201, 0, 0, 0, 0, 0, 0, },
    { 0x4001, 0x0203, 0, 0, 0, 0, 0, 0, },
};

TextureHeader *D_800E30D0 = NULL;
s32 *D_800E30D4 = NULL;
LevelModel_Alternate *D_800E30D8 = NULL;
s32 D_800E30DC = 0; //Tracks an index into D_8012A1E8
s16 *D_800E30E0 = NULL; //Points to either D_800E30E8 or D_800E3110
s16 *D_800E30E4 = NULL; //Points to either D_800E30FC or D_800E3144

s16 D_800E30E8[10] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 0
};

s16 D_800E30FC[10] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 0
};

s16 D_800E3110[26] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0
};

s16 D_800E3144[26] = {
    0, 1, 1, 1, 2, 3, 4, 4, 4, 5, 3, 4, 4, 4, 5, 3, 4, 4, 4, 5, 6, 7, 7, 7, 8, 0
};

s32 *D_800E3178 = NULL;
s32 D_800E317C = 0;
LevelHeader_70 *D_800E3180 = NULL;
unk800E3184 *D_800E3184 = NULL;
s32 D_800E3188 = 0;
s32 D_800E318C = 0;
unk800E3190 *D_800E3190 = NULL;
Object **D_800E3194 = NULL;
Object *gWaveGeneratorObj = NULL;

/*******************************/

/************ .rodata ************/

const char D_800E9160[] = "\nCouldn't find a block to pick wave details from.\nUsing block 0 as default.";
const char D_800E91AC[] = "\n\nBlock may be specified using 'P' on water group node.";
const char D_800E91E4[] = "\nError :: can not remove a wave swell object which doesn't exist !";
const char D_800E9228[] = "\nError :: more than eight swells overlap on column %d.";
const char D_800E9260[] = "\nError :: can not add another wave swell, reached limit of %d.";

/*********************************/

/************ .bss ************/

s32 D_80129FC0;
s32 D_80129FC4;
unk80129FC8 D_80129FC8[1];
s32 D_8012A018;
f32 D_8012A01C;
f32 D_8012A020[2];
unk8012A028 *D_8012A028[20];
s32 D_8012A078;
TriangleBatchInfo *gWaveBatch;
TextureHeader *gWaveTexture;
s32 D_8012A084;
s32 D_8012A088;
s32 D_8012A08C;
s32 D_8012A090;
s32 D_8012A094;
s32 D_8012A098;
s32 D_8012A09C;
f32 D_8012A0A0;
f32 D_8012A0A4;
s32 gWaveBoundingBoxDiffX;
s32 gWaveBoundingBoxDiffZ;
s32 gWaveBoundingBoxX1;
s32 gWaveBoundingBoxZ1;
f32 D_8012A0B8;
f32 D_8012A0BC;
s32 D_8012A0C0;
s32 D_8012A0C4;
s32 D_8012A0C8;
s32 D_8012A0CC;
s32 D_8012A0D0;
s32 D_8012A0D4;
s32 D_8012A0D8;
s32 D_8012A0DC;
s32 D_8012A0E0;
s32 D_8012A0E8[64];
s16 D_8012A1E8[512];
s32 D_8012A5E8[3];
s32 D_8012A5F4;
UNUSED s32 D_8012A5F8;
UNUSED s32 D_8012A5FC;
s32 D_8012A600[72];
f32 D_8012A720;
f32 D_8012A724;
s32 D_8012A728;

/*****************************/

#define FREE_MEM(mem)                   \
    tempMem = (s32 *) mem;              \
    if (tempMem != NULL) {              \
        free_from_memory_pool(tempMem); \
        mem = NULL;                     \
    }
#define FREE_TEX(tex)                   \
    tempTex = tex;                      \
    if (tempTex != NULL) {              \
        free_texture(tempTex);          \
        tex = NULL;                     \
    }

void free_waves(void) {
    TextureHeader *tempTex;
    s32 *tempMem;
    FREE_MEM(D_800E3040);
    FREE_MEM(D_800E3044);
    FREE_MEM(D_800E3048);
    FREE_MEM(D_800E304C);
    FREE_MEM(D_800E3070[0]);
    FREE_MEM(D_800E3080[0]);
    FREE_TEX(D_800E30D0);
    FREE_MEM(D_800E30D4);
    FREE_MEM(D_800E30D8);
    FREE_MEM(D_800E3178);
    D_800E3190 = NULL;
    D_800E3194 = NULL;
    D_800E3184 = NULL;
    D_800E3188 = NULL;
}

#ifdef NON_EQUIVALENT
void func_800B7EB4(void) {
    s32 *var_v1;
    s32 temp_lo;
    s32 temp_t7;
    s32 temp_t9;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;

    free_waves();
    D_800E3040 = (s32 *) allocate_from_main_pool_safe(D_80129FC8->unk20 << 2, COLOUR_TAG_CYAN);
    D_800E3044 = (s32 *) allocate_from_main_pool_safe((D_80129FC8->unk4 << 2) * D_80129FC8->unk4, COLOUR_TAG_CYAN);
    D_800E3048 = (s32 *) allocate_from_main_pool_safe(((D_80129FC8->unk0 + 1) << 2) * (D_80129FC8->unk0 + 1), COLOUR_TAG_CYAN);
    temp_lo = ((D_80129FC8->unk0 + 1) << 2) * (D_80129FC8->unk0 + 1);
    D_800E304C = allocate_from_main_pool_safe(temp_lo * 9, COLOUR_TAG_CYAN);
    
    // for (var_a1 = 1; var_a1 < 4; var_a1++) {
    //     D_800E3050[var_a1] = (s32 *) ((u32) D_800E304C + (temp_lo * var_a1));
    // }

    var_v1 = D_800E3050;
    var_a1 = 1;
    do {
        var_v1[0] = (s32 *) (D_800E304C + temp_lo);
        var_v1[1] = (s32 *) (D_800E304C + (temp_lo * 2));
        var_v1[2] = (s32 *) (D_800E304C + (temp_lo * 3));
        var_v1[3] = (s32 *) (D_800E304C + (temp_lo * 4));
        var_v1 += 4;
        var_a1 += 4;
    } while (var_a1 < 9);

    //temp_lo = (D_80129FC8->unk0 + 1) * 250 * (D_80129FC8->unk0 + 1);
    temp_lo = ((((D_80129FC8->unk0 + 1) << 5)  - D_80129FC8->unk0) * 10) * (D_80129FC8->unk0 + 1);
    if (D_8012A078 != 2) {
        D_800E3070[0] = (s32 *) allocate_from_main_pool_safe(temp_lo << 1, COLOUR_TAG_CYAN);
        D_800E3070[1] = (s32 *) ((u32) D_800E3070[0] + temp_lo);
    } else {        
        D_800E3070[0] = (s32 *) allocate_from_main_pool_safe(temp_lo << 2, COLOUR_TAG_CYAN);
        D_800E3070[1] = (s32 *) ((u32) D_800E3070[0] + temp_lo);
        D_800E3070[2] = (s32 *) ((u32) D_800E3070[1] + temp_lo);
        D_800E3070[3] = (s32 *) ((u32) D_800E3070[2] + temp_lo);
    }
    temp_lo = (D_80129FC8->unk0 << 5) * D_80129FC8->unk0;
    if (D_8012A078 != 2) {
        D_800E3080[0] = allocate_from_main_pool_safe(temp_lo << 1, COLOUR_TAG_CYAN);
        D_800E3080[1] = (s32 *) ((u32) D_800E3080[0] + temp_lo);
    } else {
        D_800E3080[0] = (s32 *) allocate_from_main_pool_safe(temp_lo << 2, COLOUR_TAG_CYAN);
        D_800E3080[1] = (s32 *) ((u32) D_800E3080[0] + temp_lo);
        D_800E3080[2] = (s32 *) ((u32) D_800E3080[1] + temp_lo);
        D_800E3080[3] = (s32 *) ((u32) D_800E3080[2] + temp_lo);
    }
    D_800E30D0 = load_texture(D_80129FC8->unk2C);
}
#else
GLOBAL_ASM("asm/non_matchings/waves/func_800B7EB4.s")
#endif

void func_800B8134(LevelHeader *arg0) {
    if (D_8012A078 != 2) {
        D_80129FC8->unk0 = arg0->unk56;
    } else {
        D_80129FC8->unk0 = 4;
    }
    D_80129FC8->unk4 = arg0->unk57;
    D_80129FC8->unk8 = arg0->unk58;
    D_80129FC8->unkC = arg0->unk5A / 256.0f;
    D_80129FC8->unk10 = arg0->unk59 << 8;
    D_80129FC8->unk14 = arg0->unk5C;
    D_80129FC8->unk18 = arg0->unk5E / 256.0f;
    D_80129FC8->unk1C = arg0->unk5D << 8;
    D_80129FC8->unk20 = arg0->unk60 & ~1;
    if (D_8012A078 != 2) {
        D_80129FC8->unk24 = arg0->unk6E;
    } else {
        D_80129FC8->unk24 = 3;
    }
    D_80129FC8->unk28 = arg0->unk71;
    D_80129FC8->unk2C = arg0->unk68 & 0xFFFF;
    D_80129FC8->unk30 = arg0->unk6A;
    D_80129FC8->unk34 = arg0->unk6B;
    D_80129FC8->unk38 = arg0->unk6C;
    D_80129FC8->unk3C = arg0->unk6D;
    D_80129FC8->unk40 = arg0->unk62 / 256.0f;
    D_80129FC8->unk44 = arg0->unk64 / 256.0f;
    D_80129FC8->unk48 = arg0->unk66 / 256.0f;
    D_80129FC8->unk4C = arg0->unk70_u8;
}

GLOBAL_ASM("asm/non_matchings/waves/func_800B82B4.s")

void func_800B8B8C(void) {
    s32 temp_v0;
    s32 phi_v0;
    s32 i;

    D_800E30DC = 0;
    phi_v0 = 0;

    for (i = 0; i < D_8012A0D8 * D_8012A0DC; i++) {
        temp_v0 = phi_v0 + 1;
        D_800E30D4[i] = 0;
        phi_v0 = temp_v0;
    }
}

GLOBAL_ASM("asm/non_matchings/waves/func_800B8C04.s")

s32 func_800B9228(LevelModelSegment *arg0) {
    s32 v0 = 0;
    s32 result = FALSE;
    while (v0 < D_8012A0E0 && arg0 != D_800E30D8[v0].unk00) {
        v0++;
    };
    if (D_800E30D4[D_800E30D8[v0].unkC]) {
        result = TRUE;
        D_8012A1E8[D_800E30DC++] = v0;
    }
    return result;
}

GLOBAL_ASM("asm/non_matchings/waves/func_800B92F4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800B97A8.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800B9C18.s")

void func_800BA288(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;
    
    arg1 <<= 3;
    for (i = 0; i < D_8012A0E0; i++) {
        if (D_8012A0E8[D_800E30D8[i].unkB] & (1 << D_800E30D8[i].unkA)) {
            if (D_80129FC8->unk28 != 0) {
                for(j = 0; j < 4; j++) {
                    s32 ti = j << 3;
                    if (D_800E30D4[D_800E30D8[i].unkC] & (0xFF << ti)) {
                        if (arg1 < D_800E30D8[i].unk14[arg0].unk0[j]) {
                            D_800E30D8[i].unk14[arg0].unk0[j] -= arg1;
                        } else {
                            D_800E30D8[i].unk14[arg0].unk0[j] = 0;
                        }
                    } else {
                        if (D_800E30D8[i].unk14[arg0].unk0[j] + arg1 < 128) {
                            D_800E30D8[i].unk14[arg0].unk0[j] += arg1;
                        } else {
                           D_800E30D8[i].unk14[arg0].unk0[j] = 128;
                        }
                    }
                }
            } else {
                if (D_800E30D4[D_800E30D8[i].unkC]) {
                    if (arg1 < D_800E30D8[i].unk14[arg0].unk0[0]) {
                        D_800E30D8[i].unk14[arg0].unk0[0] -= arg1;
                    } else {
                        D_800E30D8[i].unk14[arg0].unk0[0] = 0;
                    }
                } else {
                    if (D_800E30D8[i].unk14[arg0].unk0[0] + arg1 < 128) {
                        D_800E30D8[i].unk14[arg0].unk0[0] += arg1;
                    } else {
                        D_800E30D8[i].unk14[arg0].unk0[0] = 128;
                    }
                }
            }
        }
    }
}

//https://decomp.me/scratch/h4uac
GLOBAL_ASM("asm/non_matchings/waves/func_800BA4B8.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BA8E4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BB2F4.s")

void func_800BBDDC(LevelModel *level, LevelHeader *header) {
    func_800BBE08(level, (unk800BBE08_arg1 *) header);
    func_800BBF78(level);
}

//TODO: arg1 should be a LevelHeader
void func_800BBE08(LevelModel *level, unk800BBE08_arg1 *arg1) {
    s16 numSegments;
    s32 j;
    TriangleBatchInfo *curBatch;
    s32 i;
    s32 temp_t6;
    LevelModelSegmentBoundingBox *bb;
    LevelModelSegment *segment;

    numSegments = level->numberOfSegments;
    curBatch = 0;
    
    for (i = 0; curBatch == 0 && i < numSegments; i++) {
        segment = &level->segments[i];
        for (j = 0; curBatch == 0 && j < segment->numberOfBatches; j++) {
            if ((segment->batches[j].flags & (BATCH_FLAGS_UNK01000000 | BATCH_FLAGS_WATER | BATCH_FLAGS_HIDDEN)) == (BATCH_FLAGS_UNK01000000 | BATCH_FLAGS_WATER)) {
                curBatch = &segment->batches[j];
            }
        }
    }
    
    if (curBatch == 0) {
        i = 0;
    } else {
        i--;
    }
    bb = &level->segmentsBoundingBoxes[i];
    gWaveBoundingBoxDiffX = bb->x2 - bb->x1;
    gWaveBoundingBoxDiffZ = bb->z2 - bb->z1;
    gWaveBoundingBoxX1 = bb->x1;
    gWaveBoundingBoxZ1 = bb->z1;
    gWaveBatch = curBatch;
    gWaveTexture = level->textures[curBatch->textureIndex].texture;
    temp_t6 = (curBatch->flags & (BATCH_FLAGS_UNK40000000 | BATCH_FLAGS_UNK20000000 | BATCH_FLAGS_UNK10000000)) >> 28;
    if (temp_t6 > 0) {
        D_800E3180 = (LevelHeader_70 *) arg1->unk70[temp_t6];
    } else {
        D_800E3180 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/waves/func_800BBF78.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BC6C8.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BCC70.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BDC80.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BE654.s")

f32 get_wave_height(Object_Log *log, s32 updateRate) {
    s32 var_t0;
    f32 y;

    log->unk4 += updateRate;
    while (log->unk4 >= log->unk6) {
        log->unk4 -= log->unk6;
    }
    var_t0 = log->unkE[log->unk4 >> 1];
    if (log->unk4 & 1) {
        if (log->unk4 + 1 >= log->unk6) {
            var_t0 += log->unkE[0];
        } else {
            var_t0 += log->unkE[(log->unk4 >> 1) + 1];
        }
        if (log->unk2 > 0) {
            var_t0 <<= (log->unk2 + 0x1F);
        } else {
            var_t0 >>= 1;
        }
    } else {
        var_t0 <<= log->unk2;
    }
    y = (((f32) var_t0 / 16.0) + (f32) log->unk0);
    y *= D_80129FC8->unk40;
    y += func_800BEFC4(log->unkC, log->unk8, log->unkA);
    return y;
}

#ifdef NON_EQUIVALENT
f32 func_800BEFC4(s32 arg0, s32 arg1, s32 arg2) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f30;
    f32 var_f0;
    f32 var_f28;
    f32 var_f2;
    s32 temp_a1;
    s32 var_s3;
    s32 var_v1;
    s32 temp_s0;
    u8 temp_t5;
    unk800E3184 *temp_a3;
    unk800E3190 *temp_s1;

    var_f28 = 0.0f;
    if (D_800E3188 <= 0) {
        return 0.0f;
    }
    var_f0 = D_8012A0B8;
    var_v1 = D_80129FC8->unk0;
    var_f2 = D_8012A0BC;
    if (D_80129FC8->unk28 != 0) {
        var_f0 *= 0.5f;
        var_v1 *= 2;
        var_f2 *= 0.5f;
    }
    temp_a1 = (D_800E30D8[arg0].unkA * var_v1) + arg1;
    temp_a3 = &D_800E3184[temp_a1];
    temp_t5 = temp_a3->unk0[0];
    if (temp_t5 != 0xFF) {
        temp_f30 = D_8012A0D0 + (temp_a1 * var_f0);
        temp_f24 = D_8012A0D4 + (((D_800E30D8[arg0].unkB * var_v1) + arg2) * var_f2);
        var_s3 = 0;
        do {
            temp_s1 = &D_800E3190[temp_a3->unk0[var_s3]];
            if ((temp_s1->unk0 <= temp_f24) && (temp_f24 <= temp_s1->unk4)) {
                temp_f20 = temp_f30 - temp_s1->unk8;
                temp_f22 = temp_f24 - temp_s1->unkC;
                temp_f12 = (temp_f20 * temp_f20) + (temp_f22 * temp_f22);
                if (temp_f12 < temp_s1->unk14) {
                    temp_f0 = sqrtf(temp_f12);
                    temp_s0 = temp_s1->unk1A;
                    if (temp_s1->unk31 != 0) {
                        if (temp_f20 < 0.0f) {
                            temp_s0 -= (s32) (temp_f20 * temp_s1->unk20);
                        } else {
                            temp_s0 += (s32) (temp_f20 * temp_s1->unk20);
                        }
                    } else if (temp_s1->unk32 != 0) {
                        if (temp_f20 < 0.0f) {
                            temp_s0 -= (s32) (temp_f22 * temp_s1->unk20);
                        } else {
                            temp_s0 += (s32) (temp_f22 * temp_s1->unk20);
                        }
                    } else {
                        temp_s0 += (s32) (temp_f0 * temp_s1->unk20);
                    }
                    temp_f0 = coss_f((temp_f0 * 65536.0f) / temp_s1->unk10);
                    var_f28 += temp_s1->unk24 * sins_f(temp_s0) * temp_f0;
                }
            }
            var_s3++;
        } while (var_s3 < 8 && temp_a3->unk0[var_s3] != 0xFF);
    }
    return var_f28;
}
#else
GLOBAL_ASM("asm/non_matchings/waves/func_800BEFC4.s")
#endif

void func_800BF3E4(Object *obj) {
    s32 i;
    s32 k;
    s32 j;
    s32 m;
    unk800E3184 *temp_a1;

    if (D_800E3190 != NULL) {
        
        for (i = 0, m = 0; i < D_800E3188 && m == 0; i++) {
            if (obj == D_800E3194[i]) {
                m = -1;
            }
        }
        if (m != 0) {
            i--;
            for (j = 0; j < D_800E318C; j++) {
                for (k = 0, temp_a1 = &D_800E3184[j]; k < 8 && temp_a1->unk0[k] != 0xFF; k++) {
                    if (i == temp_a1->unk0[k]) {
                        while (k < 7) {
                            temp_a1->unk0[k] = temp_a1->unk0[k + 1];
                            k++;
                        }
                        temp_a1->unk0[k] = 0xFF;
                        k++;
                    }
                }
            }
            D_800E3194[j] = NULL;
            D_800E3188--;
        }
    }
}

void func_800BF524(Object *obj) {
    LevelObjectEntry800BF524 *temp_v0;
    s32 var_v1;

    temp_v0 = (LevelObjectEntry800BF524 *) obj->segment.level_entry;
    var_v1 = 0;
    if (temp_v0->unk10 != 0) {
        var_v1 = 1;
    }
    if (temp_v0->unk11 != 0) {
        var_v1 |= 2;
    }
    func_800BF634(obj, obj->segment.trans.x_position, obj->segment.trans.z_position, (f32) temp_v0->unkA, temp_v0->unk9 << 8,  
        (f32) temp_v0->unk8 / 16.0, (f32) temp_v0->unkE, (f32) temp_v0->unkC / 16.0, var_v1);
}

unk800E3190 *func_800BF634(Object *obj, f32 xPos, f32 zPos, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8) {
    f32 var_f0;
    s32 var_a0;
    s32 var_a0_2;
    s32 j;
    s32 var_a2_2;
    s32 k;
    s32 i;
    unk800E3184 *temp;
    unk800E3190 *result;

    result = NULL;
    if (D_800E3190 != NULL) {
        for(i = 0, var_a0 = 0; i < 32 && var_a0 == 0; i++) {
            if (D_800E3194[i] == NULL) {
                var_a0 = -1;
            }
        }
        i--;
        if (var_a0 != 0) {
            D_800E3194[i] = obj;
            D_800E3188++;
            var_f0 = D_8012A0B8;
            if (D_80129FC8->unk28 != 0) {
                var_f0 /= 2.0f;
            }
            var_a0_2 = (((xPos - arg3) - D_8012A0D0) / var_f0);
            if (var_a0_2 >= D_800E318C) {
                return NULL;
            }
            var_a2_2 = (((xPos + arg3) - D_8012A0D0) / var_f0);
            if (var_a2_2 < 0) {
                return NULL;
            }
            if (var_a0_2 < 0) {
                var_a0_2 = 0;
            }
            if (var_a2_2 >= D_800E318C) {
                var_a2_2 = D_800E318C - 1;
            }
            
            for (j = var_a0_2; j <= var_a2_2; j++) {
                temp = &D_800E3184[j];
                if (temp->unk0[7] == 0xFF) {
                    k = 0;
                    while (temp->unk0[k] != 0xFF) {
                        k++;
                    }
                    temp->unk0[k] = i;
                }
            }
            result = &D_800E3190[i];
            result->unk0 = zPos - arg3;
            result->unk4 = zPos + arg3;
            result->unk8 = xPos;
            result->unkC = zPos;
            result->unk10 = arg3;
            result->unk18 = i;
            result->unk14 = arg3 * arg3;
            result->unk1A = arg4;
            if (osTvType == TV_TYPE_PAL) {
                result->unk1C = arg5 * 20971.52;//(f64) (0x80000 / 25.0);
            } else {
                result->unk1C = arg5 * 17476.27;//(f64) ((0x80000 / 1.2) / 25.0);
            }
            result->unk20 = 65536.0f / arg6;
            result->unk24 = arg7; 
            result->unk28 = arg5;
            result->unk31 = arg8 & 1;
            result->unk32 = arg8 & 2;
            result->unk2C = arg6;
        }
    }
    return result;
}

void func_800BF9F8(unk800BF9F8 *arg0, f32 arg1, f32 arg2) {
    UNUSED s32 pad[4];
    s32 sp1C;
    f32 var_f0;
    s32 var_a1;
    s32 i;
    s32 var_a2;
    s32 j;
    s32 iteration;
    s32 temp_v1;
    u8 *var_a2_2;

    if (arg0 != NULL) {
        var_f0 = D_8012A0B8;
        iteration = 0;
        if (D_80129FC8->unk28 != 0) {
            var_f0 *= 0.5f;
        }
        temp_v1 = arg0->unk18;
        while (iteration != 2) {
            var_a1 = TRUE;
            var_a2 = (((arg0->unk8 - arg0->unk10) - D_8012A0D0) / var_f0);
            if (var_a2 >= D_800E318C) {
                var_a1 = FALSE;
            } else if (var_a2 < 0) {
                var_a2 = 0;
            }
            if (var_a1) {
                sp1C = (((arg0->unk8 + arg0->unk10) - D_8012A0D0) / var_f0);
                if (sp1C < 0) {
                    var_a1 = FALSE;
                } else if (sp1C >= D_800E318C) {
                    sp1C = D_800E318C - 1;
                }
            }
            if (var_a1) {
                for (i = var_a2; i <= sp1C; i++) {
                    var_a2_2 = &D_800E3184[i].unk0[0];
                    j = 0;
                    if (iteration != 0) {
                        if (var_a2_2[7] == 0xFF) {
                            while(var_a2_2[0] != 0xFF) {
                                var_a2_2++;
                            }
                            var_a2_2[0] = temp_v1;
                        }
                    } else {
                        while (j < 8) {
                            if (temp_v1 == var_a2_2[j]) {
                                while(j < 7){
                                    var_a2_2[j] = var_a2_2[j+1];
                                    j++;
                                }
                                var_a2_2[j] = 0xFF;
                                j++;
                            }
                            j++;
                        }
                    }
                }
            }
            if (iteration == 0) {
                arg0->unk8 += arg1;
                arg0->unkC += arg2;
                arg0->unk0 += arg2;
                arg0->unk4 += arg2;
            }
            iteration++;
        }
    }
}

UNUSED void func_800BFC54(unk800BFC54_arg0 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    if (arg0 != NULL) {
        arg0->unk10 = (arg0->unk10 + arg1);
        if (arg0->unk10 < 1.0) {
            arg0->unk10 = 1.0f;
        }
        arg0->unk0 = (arg0->unkC - arg0->unk10);
        arg0->unk4 = (arg0->unkC + arg0->unk10);
        arg0->unk28 += arg2;
        if (osTvType == TV_TYPE_PAL) {
            arg0->unk1C = arg0->unk28 * 20971.52;//(f64) (0x80000 / 25.0);
        } else {
            arg0->unk1C = arg0->unk28 * 17476.27;//(f64) ((0x80000 / 1.2) / 25.0);
        }
        arg0->unk2C = (arg0->unk2C + arg3);
        if (arg0->unk2C < 1.0) {
            arg0->unk2C = 1.0f;
        }
        arg0->unk20 = (65536.0f / arg0->unk2C); //0x10000
        arg0->unk24 = (arg0->unk24 + arg4);
    }
}

void func_800BFE98(s32 arg0) {
    s32 i;

    for(i = 0; i < 32; i++) {
        if (D_800E3194[i] != NULL) {
            D_800E3190[i].unk1A += ((0, D_800E3190[i].unk1C * arg0)) >> 4;
        }
    }
}

void obj_loop_wavepower(Object *obj) {
    LevelObjectEntry_WavePower *entry;
    s32 numRacers;
    Object *racerObj;
    Object_Racer *racer;
    Object **racers;
    s32 i;
    f32 diffY;
    f32 diffZ;
    f32 diffX;
    f32 distance;

    if (obj != gWaveGeneratorObj) {
        racers = get_racer_objects(&numRacers);
        if (numRacers > 0) {
            racerObj = NULL;
            for (i = 0; i < numRacers && racerObj == NULL; i++) {
                racer = (Object_Racer *) racers[i]->unk64;
                if (racer->playerIndex == PLAYER_ONE) {
                    racerObj = racers[i];
                }
            }
            if (racerObj != NULL) {
                entry = (LevelObjectEntry_WavePower *) obj->segment.level_entry;
                distance = entry->radius;
                distance *= distance;
                diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ) < distance) {
                    D_8012A720 = entry->unkA / 256.0f;
                    D_8012A724 = (D_8012A720 -  D_80129FC8->unk40) / (f32) entry->unkC;
                    D_8012A728 = entry->unkC;
                    gWaveGeneratorObj = obj;
                }
            }
        }
    }
}
