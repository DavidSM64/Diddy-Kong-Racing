/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D20 */

#include "waves.h"
#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "memory.h"
#include "textures_sprites.h"
#include "objects.h"

/************ .data ************/

s32 *D_800E3040 = NULL;
s32 *D_800E3044 = NULL;
s32 *D_800E3048 = NULL;
s32 *D_800E304C = NULL;

// Could be an array of pointers?
s32 D_800E3050[8] = {
    0, 0, 0, 0, 0, 0, 0, 0,
};

s32 *D_800E3070[2] = { NULL, NULL };
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
s32 D_800E30DC = 0;
s32 D_800E30E0 = 0;
s32 D_800E30E4 = 0;

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
s32 D_800E3180 = 0;
unk800E3184 *D_800E3184 = NULL;
s32 D_800E3188 = NULL;
s32 D_800E318C = 0;
unk800E3190 *D_800E3190 = NULL;
s32 *D_800E3194 = NULL;
Object *D_800E3198 = 0;
s32 D_800E319C = 0;

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
s32 D_8012A01C;
s32 D_8012A020[2];
s32 D_8012A028[20];
s32 D_8012A078;
TriangleBatchInfo *D_8012A07C;
TextureHeader *D_8012A080;
s32 D_8012A084;
s32 D_8012A088;
s32 D_8012A08C;
s32 D_8012A090;
s32 D_8012A094;
s32 D_8012A098;
s32 D_8012A09C;
s32 D_8012A0A0;
s32 D_8012A0A4;
s32 D_8012A0A8;
s32 D_8012A0AC;
s32 D_8012A0B0;
s32 D_8012A0B4;
s32 D_8012A0B8;
s32 D_8012A0BC;
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
s32 D_8012A5F8;
s32 D_8012A5FC;
s32 D_8012A600[72];
f32 D_8012A720;
f32 D_8012A724;
s32 D_8012A728;
s32 D_8012A72C;

/*****************************/

void func_800B7D20(void) {
    if (D_800E3040 != NULL) {
        free_from_memory_pool(D_800E3040);
        D_800E3040 = NULL;
    }
    if (D_800E3044 != NULL) {
        free_from_memory_pool(D_800E3044);
        D_800E3044 = NULL;
    }
    if (D_800E3048 != NULL) {
        free_from_memory_pool(D_800E3048);
        D_800E3048 = NULL;
    }
    if (D_800E304C != NULL) {
        free_from_memory_pool(D_800E304C);
        D_800E304C = NULL;
    }
    if (D_800E3070[0] != NULL) {
        free_from_memory_pool(D_800E3070[0]);
        D_800E3070[0] = NULL;
    }
    if (D_800E3080[0] != NULL) {
        free_from_memory_pool(D_800E3080[0]);
        D_800E3080[0] = NULL;
    }
    if (D_800E30D0 != NULL) {
        free_texture(D_800E30D0);
        D_800E30D0 = NULL;
    }
    if (D_800E30D4 != NULL) {
        free_from_memory_pool(D_800E30D4);
        D_800E30D4 = NULL;
    }
    if (D_800E30D8 != NULL) {
        free_from_memory_pool(D_800E30D8);
        D_800E30D8 = NULL;
    }
    if (D_800E3178 != NULL) {
        free_from_memory_pool(D_800E3178);
        D_800E3178 = NULL;
    }
    D_800E3190 = NULL;
    D_800E3194 = NULL;
    D_800E3184 = NULL;
    D_800E3188 = NULL;
}

GLOBAL_ASM("asm/non_matchings/waves/func_800B7EB4.s")

void func_800B8134(unk800B8134 *arg0) {
    if (D_8012A078 != 2) {
        D_80129FC8->unk0 = arg0->unk56;
    } else {
        D_80129FC8->unk0 = 4;
    }
    D_80129FC8->unk4 = arg0->unk57;
    D_80129FC8->unk8 = arg0->unk58;
    D_80129FC8->unkC = arg0->unk5A * 0.00390625f;
    D_80129FC8->unk10 = arg0->unk59 << 8;
    D_80129FC8->unk14 = arg0->unk5C;
    D_80129FC8->unk18 = arg0->unk5E * 0.00390625f;
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
    D_80129FC8->unk40 = arg0->unk62 * 0.00390625f;
    D_80129FC8->unk44 = arg0->unk64 * 0.00390625f;
    D_80129FC8->unk48 = arg0->unk66 * 0.00390625f;
    D_80129FC8->unk4C = arg0->unk70;
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
    if (D_800E30D4[D_800E30D8[v0].unk0C]) {
        result = TRUE;
        D_8012A1E8[D_800E30DC++] = v0;
    }
    return result;
}

GLOBAL_ASM("asm/non_matchings/waves/func_800B92F4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800B97A8.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800B9C18.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BA288.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BA4B8.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BA8E4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BB2F4.s")

void func_800BBDDC(s32 arg0) {
    func_800BBE08();
    func_800BBF78(arg0);
}

void func_800BBE08(LevelModel *arg0, unk800BBE08_arg1 *arg1) {
    s16 numSegments;
    s32 j;
    TriangleBatchInfo *curBatch;
    s32 i;
    s32 temp_t6;
    LevelModelSegmentBoundingBox* bb;
    LevelModelSegment *segment;

    numSegments = arg0->numberOfSegments;
    curBatch = 0;
    
    for (i = 0; (curBatch == 0) && (i < numSegments); i++) {
        segment = &arg0->segments[i];
        for (j = 0; (curBatch == 0) && (j < segment->numberOfBatches); j++) {
            if ((segment->batches[j].flags & 0x01002100) == 0x01002000) {
                curBatch = &segment->batches[j];
            }
        }
    }
    
    if (curBatch == 0) {
        i = 0;
    } else {
        i--;
    }
    bb = &arg0->segmentsBoundingBoxes[i];
    D_8012A0A8 = bb->x2 - bb->x1;
    D_8012A0AC = bb->z2 - bb->z1;
    D_8012A0B0 = bb->x1;
    D_8012A0B4 = bb->z1;
    D_8012A07C = curBatch;
    D_8012A080 = arg0->textures[curBatch->textureIndex].texture;
    temp_t6 = (curBatch->flags & 0x70000000) >> 0x1C;
    if (temp_t6 > 0) {
        D_800E3180 = arg1->unk70[temp_t6];
    } else {
        D_800E3180 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/waves/func_800BBF78.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BC6C8.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BCC70.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BDC80.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BE654.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BEEB4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BEFC4.s")

void func_800BF3E4(s32 arg0) {
    s32 i;
    s32 k;
    s32 j;
    s32 m;
    unk800E3184 *temp_a1;

    if (D_800E3190 != NULL) {
        
        for (i = 0, m = 0; i < D_800E3188 && m == 0; i++) {
            if (arg0 == D_800E3194[i]) {
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
            D_800E3194[j] = 0;
            D_800E3188 -= 1;
        }
    }
}

void func_800BF524(Object *obj) {
    LevelObjectEntry800BF524 *temp_v0;
    s32 var_v1;

    temp_v0 = (LevelObjectEntry800BF524 *) obj->segment.unk3C_a.level_entry;
    var_v1 = 0;
    if (temp_v0->unk10 != 0) {
        var_v1 = 1;
    }
    if (temp_v0->unk11 != 0) {
        var_v1 |= 2;
    }
    func_800BF634(obj, obj->segment.trans.x_position, obj->segment.trans.z_position, (f32)temp_v0->unkA, temp_v0->unk9 << 8,  
        (f32)temp_v0->unk8 * 0.0625, (f32)temp_v0->unkE, (f32)temp_v0->unkC * 0.0625, var_v1);
}


GLOBAL_ASM("asm/non_matchings/waves/func_800BF634.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BF9F8.s")

void func_800BFC54(unk800BFC54_arg0 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    if (arg0 != NULL) {
        arg0->unk10 = (arg0->unk10 + arg1);
        if (arg0->unk10 < 1.0) {
            arg0->unk10 = 1.0f;
        }
        arg0->unk0 = (arg0->unkC - arg0->unk10);
        arg0->unk4 = (arg0->unkC + arg0->unk10);
        arg0->unk28 += arg2;
        if (osTvType == 0) {
            arg0->unk1C = arg0->unk28 * 20971.52;
        } else {
            arg0->unk1C = arg0->unk28 * 17476.27;
        }
        arg0->unk2C = (arg0->unk2C + arg3);
        if (arg0->unk2C < 1.0) {
            arg0->unk2C = 1.0f;
        }
        arg0->unk20 = (65536.0f / arg0->unk2C);
        arg0->unk24 = (arg0->unk24 + arg4);
    }
}

void func_800BFE98(s32 arg0) {
    s32 i;

    for(i = 0; i < 32; i++) {
        if (D_800E3194[i] != 0) {
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

    if (obj != D_800E3198) {
        racers = get_racer_objects(&numRacers);
        if (numRacers > 0) {
            racerObj = NULL;
            for (i = 0; i < numRacers && racerObj == NULL; i++) {
                racer = (Object_Racer *) racers[i]->unk64;
                if (racer->playerIndex == 0) {
                    racerObj = racers[i];
                }
            }
            if (racerObj != NULL) {
                entry = (LevelObjectEntry_WavePower *) obj->segment.unk3C_a.level_entry;
                distance = entry->radius;
                distance *= distance;
                diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if (((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) < distance) {
                    D_8012A720 = ((f32) entry->unkA * (1.0f / 256.0f));
                    D_8012A724 = ((D_8012A720 -  D_80129FC8->unk40) / (f32) entry->unkC);
                    D_8012A728 = (s32) entry->unkC;
                    D_800E3198 = obj;
                }
            }
        }
    }
}
