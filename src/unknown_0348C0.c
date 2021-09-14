/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80033CC0 */

#include "unknown_0348C0.h"

#include "PR/os_cont.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "video.h"
#include "camera.h"
#include "menu.h" // For cheats
#include "unknown_0ABDF0.h"
#include "unknown_043920.h"

/************ .data ************/

// Unsure about the signed/unsigned with these arrays.
u16 D_800DC970[4] = { 
    0x40FF, 0xFFFF, 0x0007, 0x0003 
}; 
u16 D_800DC978[4] = { 
    0x0000, 0x0000, 0x001E, 0xFFFF 
};
u16 D_800DC980[20] = {
    0xFF00, 0x0100, 0x0000, 0xFFFF,
    0xFFFF, 0x0100, 0x0100, 0x0000,
    0xFFFF, 0xFFFF, 0x0100, 0xFF00,
    0x0000, 0xFFFF, 0xFFFF, 0xFF00,
    0xFF00, 0x0000, 0xFFFF, 0xFFFF
};
u16 D_800DC9A8[20] = {
    0x0000, 0x0040, 0xFFC0, 0x0000,
    0xFFC0, 0xFFC0, 0x0000, 0x0040,
    0x0020, 0x0000, 0xFFC0, 0x0020,
    0x0000, 0x0040, 0x0040, 0x0000,
    0xFFC0, 0x0040, 0x0000, 0x0000
};
u16 D_800DC9D0[64] = {
    0x0000, 0x0301, 0x0004, 0x0000,
    0x0001, 0x0004, 0x0004, 0x0004,
    0x0000, 0x0203, 0x0004, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0004,
    0x0002, 0x0503, 0x0001, 0x0000,
    0x0000, 0x0004, 0x0001, 0x0004,
    0x0002, 0x0405, 0x0001, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0004,
    0x0000, 0x0103, 0x0004, 0x0000,
    0x0004, 0x0004, 0x0001, 0x0004,
    0x0000, 0x0302, 0x0004, 0x0000,
    0x0001, 0x0004, 0x0001, 0x0000,
    0x0002, 0x0305, 0x0001, 0x0000,
    0x0001, 0x0004, 0x0000, 0x0004,
    0x0002, 0x0504, 0x0001, 0x0000,
    0x0000, 0x0004, 0x0000, 0x0000
};
s8 D_800DCA50[8] = {
    2, 5, 6, 3, 10, 8, 7, 9
};
u8 D_800DCA58[9] = {
    2, 5, 6, 3, 10, 8, 7, 9, 11
};
s8 D_800DCA64[9] = {
    2, 5, 6, 3, 10, 8, 7, 9, 12
};
s8 D_800DCA70[10] = {
    2, 5, 6, 3, 10, 8, 7, 9, 11, 12
};
s32 D_800DCA7C[3] = { // Not sure about typing
    0, 0, 0
};
s32 D_800DCA88[3] = { // Not sure about typing
    0, 0, 0
};

s8 D_800DCA94[8] = {
    0x00, 0x00, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00
};

s8 D_800DCA9C[12] = {
    0x00, 0x01, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

u16 D_800DCAA8[64] = {
    0x0000, 0x0301, 0x0000, 0x0000,
    0xFFFF, 0xFFFF, 0x0000, 0xFFFF,
    0x0000, 0x0203, 0x0000, 0x0000,
    0xFFFF, 0x0000, 0xFFFF, 0xFFFF,
    0x0002, 0x0503, 0xFFFF, 0x0000,
    0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
    0x0002, 0x0405, 0xFFFF, 0x0000,
    0x0000, 0x0000, 0x0000, 0xFFFF,
    0x0000, 0x0103, 0x0000, 0x0000,
    0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
    0x0000, 0x0302, 0x0000, 0x0000,
    0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
    0x0002, 0x0305, 0xFFFF, 0x0000,
    0xFFFF, 0xFFFF, 0x0000, 0xFFFF,
    0x0002, 0x0504, 0xFFFF, 0x0000,
    0x0000, 0xFFFF, 0x0000, 0x0000
};
u16 D_800DCB28[20] = {
    0xFFC0, 0x0000, 0x0020, 0xFFC0,
    0x0000, 0xFFE0, 0x0000, 0x0000,
    0x0020, 0x0000, 0x0000, 0xFFE0,
    0x0040, 0x0000, 0x0020, 0x0040,
    0x0000, 0xFFE0, 0x0000, 0x0000
};

/*******************************/

/************ .bss ************/

f32 D_8011D4D0;
s32 D_8011D4D4;
s32 D_8011D4D8;
s32 D_8011D4DC;
s16 D_8011D4E0;
s16 D_8011D4E2;

/******************************/

extern u32 osTvType;

Settings *get_settings();
Object_64 *func_800BE654(s16, f32, f32);
void func_80000FDC(s32, s32, f32);
void func_80009558(s32, f32, f32, f32, s32, s32*);
void func_80009968(f32, f32, f32, u8, u8, s32);
s32 func_8001F460(Object*, s32, Object*);
f32 func_800707C4(s16);
f32 func_800707F8(s16);

#ifdef NON_MATCHING

typedef struct LevelObjectEntry80033CC0 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} LevelObjectEntry80033CC0;

typedef struct Object_50_80033CC0 {
    f32 unk0;
} Object_50_80033CC0;

void func_80033CC0(Object *arg0, LevelObjectEntry80033CC0 *arg1) {
    f32 phi_f0;
    arg0->unk6 |= 2;
    phi_f0 = arg1->unk9 & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    arg0->scale = arg0->descriptor_ptr->unkC * phi_f0;
    ((Object_50_80033CC0*)arg0->unk50)->unk0 = arg0->descriptor_ptr->unk4 * phi_f0;
    arg0->unk3A = arg1->unk8;
    arg0->y_rotation = arg1->unkA << 6 << 4;
    if (arg1->unkB) {
        // Regalloc issue here
        arg0->unk4C->unk14 = 1;
        arg0->unk4C->unk11 = 1;
        arg0->unk4C->unk10 = 0x14;
        arg0->unk4C->unk12 = 0;
        arg0->unk4C->unk16 = -5;
        arg0->unk4C->unk17 = arg1->unkB;
    }
    if (arg0->unk3A >= arg0->descriptor_ptr->unk55) {
        arg0->unk3A = 0;
    }
    arg0->unk78 = 0;
    arg0->unk7C.word = 0;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033CC0.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033DD0.s")

void func_80033F44(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033F60.s")

typedef struct unk80034530 {
    u8 pad0[0x8];
    u8 unk8;
    u8 unk9;
    s8 unkA;
    s8 unkB;
    u8 unkC;
    u8 unkD;
} unk80034530;

void func_80034530(Object *arg0, unk80034530 *arg1) {
    Object_64 *temp;
    arg0->unk4C->unk14 = 0x22;
    arg0->unk4C->unk11 = 0;
    temp = arg0->unk64;
    temp->unkE = arg1->unkA;
    temp->unkF = arg1->unkB;
    temp->unk10 = arg1->unkC;
    temp->unk11 = arg1->unkD;
    temp->unkCD.half = temp->unkF;
    arg0->y_rotation = arg1->unk8 << 4 << 4; // Not sure about the shift amounts here, but it
    arg0->x_rotation = arg1->unk9 << 4 << 4; // just needs to be 2 left shifts that add up to 8.
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800345A0.s")

// Literally the same function as func_80033F44()
void func_80034844(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80034860.s")

void func_80034AF0(Object *arg0, u8 *arg1) {
    f32 phi_f0 = (s32)(arg1[9] & 0xFF);
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    arg0->scale = arg0->descriptor_ptr->unkC * phi_f0;
    arg0->unk78 = arg1[8];
}

typedef struct unk80034B4C {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0x5E];
    s32 unk78;
} unk80034B4C;

void func_80034B4C(unk80034B4C *arg0, s32 arg1) {
    arg0->unk18 += arg0->unk78 * arg1;
}

void func_80034B68(s32 arg0, s32 arg1) {

}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80034B74.s")

void func_80034E70(Object *arg0, u8 *arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->y_rotation = arg1[8] << 6 << 4; // Not sure about the values here.
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80034E9C.s")

void func_8003522C(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80035260.s")

void func_80035640(s32 arg0, s32 arg1) {

}

typedef struct unk8003564C {
    s8 unk0;
    s8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} unk8003564C;

typedef struct Object_64_8003564C {
    u8 pad0[4];
    Object *unk4;
} Object_64_8003564C;

void func_8003564C(Object *arg0, s32 arg1) {
    unk8003564C sp20;
    Object *someObj;

    if (arg0->unk78 == 0) {
        sp20.unk2 = arg0->x_position;
        sp20.unk4 = arg0->y_position;
        sp20.unk6 = arg0->z_position;
        sp20.unk1 = 8;
        sp20.unk0 = 0x34;
        someObj = func_8000EA54(&sp20, 1);
        if (someObj != NULL) {
            Object_64_8003564C *someObj64 = someObj->unk64;
            someObj64->unk4 = arg0;
            arg0->unk78 = someObj;
            someObj->unk3C_a.unk3C = 0;
        }
    }
}

/* Size: 12 bytes */
typedef struct LevelObjectEntry8003572C {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8003572C;

void func_8003572C(Object *arg0, LevelObjectEntry8003572C *arg1) {
    f32 phi_f0 = arg1->unk9 & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    arg0->scale = arg0->descriptor_ptr->unkC * phi_f0;
    arg0->y_rotation = arg1->unkA << 6 << 4;
    if (arg0->unk3A >= arg0->descriptor_ptr->unk55) {
        arg0->unk3A = 0;
    }
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

void func_800357D4(Object *obj, s32 arg1) {
    Object *someObj;
    Object_4C *temp_v1;

    someObj = get_object_struct(0);
    if (someObj != NULL) {
        temp_v1 = obj->unk4C;
        if (temp_v1->unk13 < 0xC8) {
            if (someObj == temp_v1->unk0) {
                if ((get_buttons_pressed_from_player(0) & Z_TRIG) || someObj == obj->unk5C->unk100) {
                    func_8006F29C();
                }
            }
        }
    }
    obj->unk4C->unk13 = 0xFF;
}

/* Size: 12 bytes */
typedef struct LevelObjectEntry8003588C {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8003588C;

void func_8003588C(Object *arg0, LevelObjectEntry8003588C *arg1) {
    Object_40 *obj40;
    f32 phi_f0;

    phi_f0 = arg1->unk9 & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    obj40 = arg0->descriptor_ptr;
    phi_f0 /= 64;
    arg0->scale = obj40->unkC * phi_f0;
    arg0->y_rotation = arg1->unkA << 6 << 4;
    if (arg0->unk3A >= obj40->unk55) {
        arg0->unk3A = 0;
    }
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        gParticlePtrList_addObject(arg0);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003596C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80035AE8.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80035C50.s")

typedef struct unk80035E20 {
    u8 pad0[0x40];
    s32 unk40;
    u8 pad44[0x34];
    s32 unk78;
    s32 unk7C;
} unk80035E20;

void func_80035E20(unk80035E20 *arg0, s32 arg1) {
    arg0->unk78 = 0;
    arg0->unk7C = arg0->unk40;
}

typedef struct Object_64_80035E34 {
    u8 pad0[0x1D6];
    s8 unk1D6;
} Object_64_80035E34;

void func_80035E34(Object *obj, s32 arg1) {
    Object *someObj;
    Object *someOtherObj;
    Object_64_80035E34 *someOtherObj64;
    Object_60 *obj60;

    obj->unk3B = 0;
    obj->unk18 = 0x28;
    if (func_8001139C() == 0) {
        obj->unk78 += arg1;
    }
    set_ghost_position_and_rotation(obj);
    func_800AFC3C(obj, arg1);
    someOtherObj = get_object_struct(0);
    someOtherObj64 = someOtherObj->unk64;
    obj60 = obj->unk60;
    if (obj60->unk0 == 1) {
        s8 temp = someOtherObj64->unk1D6;
        if ((temp == 1) || (temp == 2)) {
            someObj = (Object*)obj60->unk4;
            someObj->y_rotation = 0x4000;
            someObj->unk3A++;
            someObj->unk3A &= 1;
        }
    }
}

typedef struct unk80035EF8 {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
} unk80035EF8;

void func_80035EF8(Object *arg0, unk80035EF8 *arg1) {
    f32 phi_f0;
    arg0->unk78 = (s32) arg1->unkE;
    arg0->unk7C.word = -1;
    arg0->y_rotation = arg1->unkC << 6 << 4; // Not sure about the values here.
    phi_f0 = (f32) (arg1->unkA & 0xFF);
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    arg0->scale = (f32) (arg0->descriptor_ptr->unkC * phi_f0);
}

typedef struct Object_64_80035F6C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s16 *unk20;
    u8  *unk24;
} Object_64_80035F6C;

typedef struct Object_64_80035F6C_2 {
    u8 pad0[3];
    s8 unk3;
} Object_64_80035F6C_2;

void func_80035F6C(Object *obj, s32 arg1) {
    s32 temp_t4;
    s32 temp_t5;
    Object *someObj;
    Object_64_80035F6C *obj64;
    Object_64_80035F6C_2 *someObj64;

    if (obj->unk7C.word < 0) {
        someObj = get_object_struct(obj->unk78);
        if (someObj != NULL) {
            obj64 = obj->unk64;
            someObj64 = someObj->unk64;
            obj->unk7C.word = someObj64->unk3;
            if (obj->unk7C.word < 0 || obj->unk7C.word >= 0xA) {
                obj->unk7C.word = 0;
            }
            obj64->unk20 = D_800DC980;
            obj64->unk24 = obj->unk68[obj->unk7C.word];
            temp_t4 = (obj64->unk24[0] - 1) << 0x15;
            temp_t5 = (obj64->unk24[1] - 1) << 5;
            obj64->unk0 = 0x40000103;
            obj64->unk4 = 0;
            obj64->unk8 = temp_t4;
            obj64->unkC = temp_t5;
            obj64->unk10 = 0x40010203;
            obj64->unk14 = temp_t4;
            obj64->unk18 = (s32) (temp_t4 | temp_t5);
            obj64->unk1C = temp_t5;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80036040.s")

void func_80036194(Object *arg0, s32 arg1) {
    Object_64 *temp;
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x1E;
    arg0->unk4C->unk12 = 0;
    temp = arg0->unk64;
    temp->unkCD.bytes.byteD = 0xFF;
    temp->unk0_a.unk0 = 0.0f;
    D_8011D4D8 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800361E0.s")

void func_80036BCC(u16 arg0, s32 arg1) {
    if ((D_8011D4D8 != 0) && (arg1 & 1)) {
        func_8000488C(D_8011D4D8);
        D_8011D4D8 = 0;
    }
    if (D_8011D4D8 == 0) {
        func_80001D04(arg0, &D_8011D4D8);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80036C30.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800370D4.s")

typedef struct unk80037578 {
    u8 pad0[0x78];
    s32 unk78;
    s32 unk7C;
} unk80037578;

void func_80037578(unk80037578 *arg0, u8 *arg1) {
    arg0->unk78 = arg1[9] * 2;
    arg0->unk7C = arg1[8];
}

#ifdef NON_MATCHING
// Regalloc issues
void func_80037594(Object *obj, s32 arg1) {
    if (obj->unk78 > 0) {
        obj->unk78 -= arg1;
        obj->unk6 |= 0x4000;
    } else {
        obj->unk18 += arg1 * 4;
        obj->unk6 &= 0xBFFF;
        if (obj->unk18 >= 256) {
            obj->unk18 = 0;
            obj->unk78 = get_random_number_from_range(0, 30) + obj->unk7C.word;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80037594.s")
#endif

typedef struct unk80037624 {
    u8 pad0[6];
    s16 unk6;
} unk80037624;

void func_80037624(unk80037624 *arg0, s32 arg1) {
    arg0->unk6 |= 0x4000;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003763C.s")

void func_800377E4(Object*, s32);

/* Size: 12 bytes */
typedef struct LevelObjectEntry800376E0 {
    LevelObjectEntryCommon common;
    s8 unk8;
    s8 unk9;
    s8 unkA;
} LevelObjectEntry800376E0;

typedef struct Object_64_800376E0 {
    s16 segmentId;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Object_64_800376E0;

s16 get_level_segment_index_from_position(f32, f32, f32);

void func_800376E0(Object *arg0, LevelObjectEntry800376E0 *arg1, s32 arg2) {
    Object_64_800376E0 *obj64;
    LevelModel *levelModel;
    s16 segmentBatchCount;

    obj64 = arg0->unk64;
    levelModel = func_8002C7C4();
    obj64->unk2 = arg1->unk8;
    obj64->unk4 = arg1->unk9;
    obj64->unk6 = arg1->unkA;
    obj64->segmentId = get_level_segment_index_from_position(arg0->x_position, arg0->y_position, arg0->z_position);
    if (arg2 == 0) {
        obj64->unk8 = 0;
        obj64->unkA = 0;
    }
    if (obj64->segmentId != -1) {
        if (obj64->unk2 < 0) {
            obj64->unk2 = 0;
        }
        segmentBatchCount = levelModel->segments[obj64->segmentId].numberOfBatches;
        if (obj64->unk2 >= segmentBatchCount) {
            obj64->unk2 = segmentBatchCount - 1;
        }
    }
    func_800377E4(arg0, 0x20000);
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800377E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80037A18.s")

void func_80037CE8(s32 arg0, s32 arg1) {
    func_8001F460(arg0, arg1, arg0);
}

typedef struct unk80037D08_arg0_64 {
    u8 pad0[0x2A];
    s16 unk2A;
} unk80037D08_arg0_64;

typedef struct unk80037D08_arg0 {
    u8 pad0[0x64];
    unk80037D08_arg0_64 *unk64;
} unk80037D08_arg0;

void func_80037D08(unk80037D08_arg0 *arg0, s32 arg1) {
    s32 phi_a0;
    unk80037D08_arg0_64 *sp18;

    sp18 = arg0->unk64;
    phi_a0 = 1 - func_8001F460(arg0, arg1, arg0);
    if (sp18->unk2A > 0) {
        phi_a0 = 0;
    }
    func_800235D0(phi_a0);
}

void func_80037D54(s32 arg0, s32 arg1) {

}

/* Unused? */
void func_80037D60(s32 arg0, s32 arg1) {

}

void func_80037D6C(s32 arg0, s32 arg1) {

}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80037D78.s")

#ifdef NON_MATCHING

// Not sure if Object_60 differs between objects yet.
typedef struct Object_60_800380F8 {
    s32 unk0;
    Object *unk4;
    s32 pad8;
    Object *unkC;
} Object_60_800380F8;

// Regalloc issues
void func_800380F8(Object *obj, s32 arg1) {
    Object_60_800380F8 *obj60;
    Object *someObj;

    func_8001F460(obj, arg1, obj);
    obj60 = obj->unk60;
    if (obj60 != NULL) {
        if (obj60->unk0 > 0) {
            if (obj60->unk0 == 3) {
                someObj = obj60->unkC;
            } else {
                someObj = obj60->unk4;
            }
            someObj->unk3A++;
            someObj->y_rotation = 0x4000;
            if (someObj->descriptor_ptr->unk55 == someObj->unk3A) {
                someObj->unk3A = 0;
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800380F8.s")
#endif

void func_8003818C(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 0x81;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

// Literally the same as func_80037CE8()
void func_800381C0(s32 arg0, s32 arg1) {
    func_8001F460(arg0, arg1, arg0);
}

void func_800381E0(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

// Literally the same as func_8003818C()
void func_80038214(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 0x81;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

// Literally the same as func_800381E0()
void func_80038248(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

#ifdef NON_MATCHING

void func_800096D8(s32, f32, f32, f32);

typedef struct Object_64_8003827C {
    u8 pad0[0x20];
    s32 unk20;
    s16 unk24;
    u8 pad28[0x12];
    s8 unk38;
} Object_64_8003827C;

// Regalloc issues
void func_8003827C(Object *obj, s32 arg1) {
    Object_64_8003827C *obj64 = obj->unk64;
    if (obj64->unk24 == 0) {
        if (obj64->unk38 != 0) {
            obj64->unk24 = (s16) (obj64->unk38 & 0xFF);
        }
    }
    if (obj64->unk24 != 0) {
        if (obj64->unk20 == 0) {
            func_80009558(obj64->unk24 & 0xFFFF, obj->x_position, obj->y_position, obj->z_position, 1, &obj64->unk20);
        } else {
            func_800096D8(obj64->unk20, obj->x_position, obj->y_position, obj->z_position);
        }
    }
    func_8001F460(obj, arg1, obj);
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003827C.s")
#endif

// Unused
void func_80038330(Object *obj, s32 arg1) {
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003833C.s")

typedef struct Object_64_80038710 {
    u8 pad0[0x30];
    s8 unk30;
    u8 pad31[0x13];
    s8 unk44;
} Object_64_80038710;

void func_80066488(s32, f32, f32, f32, s16, s16, s16);

void func_80038710(Object *obj, s32 arg1) {
    s32 temp_v0;
    s32 phi_v1;
    Object_64_80038710 *obj64;

    temp_v0 = func_8001F460(obj, arg1, obj);
    obj->unk6 |= 0x4000;
    obj64 = obj->unk64;
    if (temp_v0 == 0) {
        if (get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER) {
            phi_v1 = func_800210CC(obj64->unk44);
        } else {
            phi_v1 = 1;
        }
        if (phi_v1) {
            func_80066488(obj64->unk30, obj->x_position, obj->y_position, obj->z_position, 0x8000 - obj->y_rotation, -obj->x_rotation, obj->z_rotation);
        }
    }
}

// Unused
void func_800387C0(Object *obj, s32 arg1) {
}

typedef struct Object_64_800387CC {
    u8 pad0[0x148];
    Object *unk148;
} Object_64_800387CC;

void func_800387CC(Object *obj, s32 arg1) {
    Object *someObj;
    s32 temp_v0;
    temp_v0 = obj->unk78;
    someObj = NULL;
    if (temp_v0 != 0) {
        someObj = get_object_struct(temp_v0 - 1);
    }
    obj->unk7C.word = func_8001F460(obj, arg1, obj);
    obj->unk6 |= 0x4000;
    if (obj->unk7C.word == 0 && someObj != NULL) {
        Object_64_800387CC *someObj64 = someObj->unk64;
        someObj64->unk148 = obj;
    }
}

void func_80038854(Object *arg0, u8 *arg1) {
    if (arg1[9] != 0) {
        arg0->unk4C->unk14 = 0x21;
    } else {
        arg0->unk4C->unk14 = 0x22;
    }
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0xF;
    arg0->unk4C->unk12 = 0;
    arg0->unk78 = (arg1[10] << 16) | arg1[8]; // Not sure about the values here.
    arg0->unk7C.word = arg1[9];
    arg0->y_rotation = arg1[11] << 10; // Not sure about the values here.
}

typedef struct Object_64_800388D4 {
    s16 unk0;
} Object_64_800388D4;

void func_800388D4(Object *arg0, s32 arg1) {
    s16 temp_a0;
    Object_4C *obj4C;
    Object *playerObj;

    if (arg0->unk7C.word == 0) {
        arg0->unk6 |= 0x4000;
    } else {
        arg0->unk6 &= ~0x4000;
    }
    
    obj4C = arg0->unk4C;
    if (obj4C->unk13 < ((arg0->unk78 >> 16) & 0xFF)) {
        playerObj = obj4C->unk0;
        if (playerObj->descriptor_ptr->unk54 == 1) {
            Object_64_800388D4 *playerObj64 = playerObj->unk64;
            temp_a0 = playerObj64->unk0;
            if ((temp_a0 != -1) && (get_buttons_pressed_from_player(temp_a0) & Z_TRIG)) {
                func_800C31EC(arg0->unk78 & 0xFF, arg0);
            }
        }
    }
}

void func_800389AC(s32 arg0, s32 arg1) {

}

void func_800389B8(Object *obj, s32 arg1) {
    f32 temp_f2 = arg1;
    if (osTvType == TV_TYPE_PAL) {
        temp_f2 *= 1.2;
    }
    obj->x_position += obj->x_velocity * temp_f2;
    obj->unk18 += arg1 * 16;
    obj->y_position += obj->y_velocity * temp_f2;
    obj->z_position += obj->z_velocity * temp_f2;
    if (obj->unk18 >= 256) {
        gParticlePtrList_addObject(obj);
        obj->unk18 = 255;
    }
}

void func_80038A6C(s32 arg0, s32 arg1) {

}

void func_80038A78(Object *arg0, s32 arg1) {
    arg0->unk18 += arg1 * 8;
    if (arg0->unk18 >= 256) {
        gParticlePtrList_addObject(arg0);
        arg0->unk18 = 255;
    }
}

void func_80038AC8(s32 arg0, s32 arg1) {

}

void func_80038AD4(Object *arg0, s32 arg1) {
    f32 temp_f2;

    temp_f2 = (f32) arg1;
    if (osTvType == TV_TYPE_PAL) {
        temp_f2 *= 1.2;
    }
    arg0->unk18 += arg1 * 4;
    arg0->y_position += temp_f2 * 0.25;
    if (arg0->unk18 >= 256) {
        gParticlePtrList_addObject(arg0);
        arg0->unk18 = 255;
    }
}

#ifdef NON_MATCHING

typedef struct unk80038B74 {
    u8 pad0[8];
    s8 unk8;
} unk80038B74;

// regalloc issues
void func_80038B74(Object *obj, unk80038B74 *arg1) {
    s32 temp;
    obj->unk18 = 0;
    obj->scale = 0.5f;
    obj->unk3A = get_random_number_from_range(0, obj->descriptor_ptr->unk55 - 1);
    obj->unk78 = 0;
    obj->unk7C.word = 0xFF;
    temp = (s32)arg1->unk8;
    if (temp != 0) {
        obj->unk7C.word |= (temp << 8) & 0xFF00;
    }
    obj->unk74 = 1;
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80038B74.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80038BF4.s")

void func_80038D58(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0xF;
    arg0->unk4C->unk12 = 0;
    if (get_settings()->cutsceneFlags & 1) {
        arg0->unk78 = 1;
    }
}

typedef struct Object_3C_80038DC4 {
    u8 pad0[8];
    s8 unk8;
} Object_3C_80038DC4;

void func_80038DC4(Object *arg0, s32 arg1) {
    if (arg0->unk78 != 0) {
        Object_3C_80038DC4 *temp = arg0->unk3C_a.unk3C;
        if(arg0->unk4C->unk13 < 0x78) {
            func_8006F338(temp->unk8);
            arg0->unk78 = 0;
            func_80001D04(0x30, 0, arg0);
            func_80000FDC(0x12A, 0, 1.0f);
        }
    }
}

typedef struct LevelObjectEntry80038E3C {
    LevelObjectEntryCommon common;
    u8 pad8[8];
    u8 unk10;
    u8 unk11;
    u8 pad12[6];
    s8 unk18;
} LevelObjectEntry80038E3C;

typedef struct Object_64_80038E3C {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s8 unk14;
} Object_64_80038E3C;

void func_80038E3C(Object *obj, LevelObjectEntry80038E3C *arg1) {
    f32 phi_f0;
    Object_64_80038E3C *obj64;
    phi_f0 = arg1->unk10 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = obj->unk64;
    phi_f0 /= 128;
    obj->scale = phi_f0;
    obj->y_rotation = arg1->unk11 << 6 << 4;
    obj64->unk0 = func_800707C4(obj->y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->x_position) + (obj64->unk8 * obj->z_position));
    obj64->unk10 = arg1->unk10;
    obj64->unk14 = arg1->unk18;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = arg1->unk10;
    obj->unk4C->unk12 = 0;
}

//GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80038E3C.s")

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80038F58.s")

typedef struct unk80039160 {
    u8 pad0[0x78];
    s32 unk78;
} unk80039160;

void func_80039160(unk80039160 *arg0, s8 *arg1) {
    arg0->unk78 = arg1[8];
    func_80011390();
}

void func_80039184(s32 arg0, s32 arg1) {

}

typedef struct unk80039190 {
    u16 unk0;
    u8 pad2[0x76];
    s32 unk78;
    s32 unk7C;
} unk80039190;

void func_80039190(unk80039190 *arg0, u8 *arg1) {
    s32 temp;
    arg0->unk78 = arg1[8];
    arg0->unk7C = arg1[9];
    arg0->unk0 = arg1[10] << 6 << 4; // Not sure about the values here.
}

void func_800391BC(s32 arg0, s32 arg1) {

}

void func_800391C8(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 3;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

void func_800391FC(Object *obj, s32 arg1) {
    s32 sp2C;
    
    if (obj->unk78 > 0) {
        obj->unk78 -= arg1;
        arg1 *= 2;
    } else {
        obj->unk78 = 0;
    }
    sp2C = obj->unk18;
    func_8001F460(obj, arg1, obj);
    func_800113CC(obj, 0, sp2C, 0xAC, 0xAD);
    if (obj->unk4C->unk13 < 0xFF) {
        if (obj->unk78 == 0) {
            obj->unk78 = 0x3C;
            func_80009558(0x23B, obj->x_position, obj->y_position, obj->z_position, 4, NULL);
        }
    }
}

void func_800392B8(Object *arg0, s32 arg1) {
    Object_64 *temp;
    arg0->unk4C->unk14 = (u16)1;
    arg0->unk4C->unk11 = (u8)0;
    arg0->unk4C->unk10 = (u8)0x1E;
    arg0->unk4C->unk12 = (u8)0;
    temp = arg0->unk64;
    temp->unkCD.bytes.byteD = 0xFF;
    temp->unk0_a.unk0 = 0.0f;
    temp->unk28 = 0;
    temp->unk2C = 0;
    temp->unk34 = 0;
    temp->unk36 = 0;
    D_8011D4D4 = 0;
    D_8011D4E2 = 0x10F;
}

void func_80039320(s16 arg0) {
    D_8011D4E2 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80039330.s")

void func_8003AC3C(u16 arg0, s32 arg1) {
    if ((D_8011D4D4 != 0) && (arg1 & 1)) {
        func_8000488C(D_8011D4D4);
        D_8011D4D4 = 0;
    }
    if (D_8011D4D4 == 0) {
        func_80001D04(arg0, &D_8011D4D4);
    }
}

void func_8003ACA0(s32 arg0, s32 arg1) {

}

f32 func_8003ACAC(void) {
    return D_8011D4D0;
}

void func_8003ACBC(Object *arg0, u8 *arg1, s32 arg2) {
    f32 phi_f0 = (s32)(arg1[8] & 0xFF);
    if (phi_f0 < 5.0f) {
        phi_f0 = 5.0f;
    }
    phi_f0 /= 64;
    arg0->scale = phi_f0;
    arg0->y_rotation = arg1[10] << 6 << 4; // Not sure about the values here.
    func_80011390();
}

void func_8003AD28(s32 arg0, s32 arg1) {

}

typedef struct LevelObjectEntry8003AD34 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8003AD34;

typedef struct Object_64_8003AD34 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s8 unk14;
} Object_64_8003AD34;

void func_8003AD34(Object *obj, LevelObjectEntry8003AD34 *arg1) {
    f32 phi_f0;
    Object_64_8003AD34 *obj64;
    phi_f0 = arg1->unk8 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = obj->unk64;
    phi_f0 /= 128;
    obj->scale = phi_f0;
    obj->y_rotation = arg1->unk9 << 6 << 4;
    obj64->unk0 = func_800707C4(obj->y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->x_position) + (obj64->unk8 * obj->z_position));
    obj64->unk10 = arg1->unk8;
    obj64->unk14 = arg1->unkA;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = arg1->unk8;
    obj->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003AE50.s")

// Exactly the same as func_8003AD34
void func_8003B058(Object *obj, LevelObjectEntry8003AD34 *arg1) {
    f32 phi_f0;
    Object_64_8003AD34 *obj64;
    phi_f0 = arg1->unk8 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = obj->unk64;
    phi_f0 /= 128;
    obj->scale = phi_f0;
    obj->y_rotation = arg1->unk9 << 6 << 4;
    obj64->unk0 = func_800707C4(obj->y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->x_position) + (obj64->unk8 * obj->z_position));
    obj64->unk10 = arg1->unk8;
    obj64->unk14 = arg1->unkA;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = arg1->unk8;
    obj->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B174.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B368.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B4BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B7CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B988.s")

typedef struct LevelObjectEntry8003C1E0 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 padD;
    s8 unkE;
} LevelObjectEntry8003C1E0;

typedef struct Object_64_8003C1E0 {
    f32 unk0;
    u8 pad4[4];
    s32 unk8;
    u8 padC[3];
    s8 unkF;
    u8 pad10[2];
    u8 unk12;
    u8 unk13;
} Object_64_8003C1E0;

void func_8003C1E0(Object *obj, LevelObjectEntry8003C1E0 *arg1) {
    f32 temp_f0;
    Object_64_8003C1E0 *obj64;
    f32 phi_f0;

    obj->unk3A = 0;
    obj64 = obj->unk64;
    obj->y_rotation = arg1->unk8 << 6 << 4;
    obj64->unkF = arg1->unkE;
    obj64->unk13 = arg1->unkB;
    obj64->unk0 = obj->y_position;
    obj64->unk8 = 0;
    obj64->unk12 = arg1->unkA;
    obj->unk78 = obj->y_rotation;
    obj->unk7C.word = (arg1->unk9 & 0x3F) << 0xA;
    phi_f0 = arg1->unkC & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    obj->scale = obj->descriptor_ptr->unkC * phi_f0;
    obj->unk4C->unk14 = 0x21;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    if (obj->unk3A >= obj->descriptor_ptr->unk55) {
        obj->unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003C2E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003C644.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003C7A4.s")

void func_8003C9EC(Object *arg0, u8 *arg1) {
    Object_64 *temp = arg0->unk64;
    arg0->unk3A = arg1[8];
    arg0->y_rotation = arg1[9] << 6 << 4;
    temp->unk0_a.unk0 = arg0->y_position;
    arg0->unk4C->unk14 = 0x21;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
    temp->unk4 = 0;
    if (arg0->unk3A >= arg0->descriptor_ptr->unk55) {
        arg0->unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003CA68.s")

void func_8003CE64(Object *arg0, u8 *arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
    arg0->unk78 = arg1[8];
}

void func_8003CEA0(Object *arg0, s32 arg1) {
    if (arg0->unk4C->unk13 < 0x2D) {
        func_8001E344(arg0->unk78, arg0);
    }
    arg0->unk4C->unk13 = (u8)0xFF;
}

void func_8003CF00(s32 arg0, s32 arg1) {

}

void func_8003CF0C(s32 arg0, s32 arg1) {

}

typedef struct unk8003CF18 {
    u8 pad1A[0x78];
    f32 unk78;
} unk8003CF18;

void func_8003CF18(unk8003CF18 *arg0, u8 *arg1) {
    f32 temp_f0;
    temp_f0 = arg1[8] * 8.0f;
    temp_f0 = temp_f0 * temp_f0;
    arg0->unk78 = temp_f0;
}

void func_8003CF58(Object *arg0, u8 *arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = arg1[9];
    arg0->unk78 = arg1[8];
    arg0->unk7C.word = arg1[9];
}

void func_8003CF98(Object *arg0, s32 arg1) {
    if (arg0->unk4C->unk13 < arg0->unk7C.word) {
        func_80028044(arg0->unk78);
    }
}

void func_8003CFE0(s32 arg0, u8 *arg1) {
    if (arg1[9] == 0xFF) {
        arg1[9] = func_8001C48C(arg0) & 0xFF;
    }
    func_8001D1BC(arg1[9], arg1);
    func_8001D1AC();
}

void func_8003D02C(s32 arg0, s32 arg1) {

}

typedef struct unk8003D038 {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0x5E];
    s32 unk78;
} unk8003D038;

void func_8003D038(unk8003D038 *arg0, s8 *arg1) {
    arg0->unk18 = 0x78;
    arg0->unk78 = (arg1[8] - 1) & 3;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003D058.s")

void func_8003D2AC(s32 arg0, s32 arg1) {

}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003D2B8.s")

typedef struct unk8003D3EC {
    u8 pad0[0x18];
    u16 unk18;
} unk8003D3EC;

void func_8003D3EC(unk8003D3EC *arg0, s32 arg1) {
    arg0->unk18 = 0x64;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003D3FC.s")

void func_8003D534(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x1E;
    arg0->unk7C.half.upper = 0x14;
    arg0->unk7C.half.lower = 0x10;
    if (get_filtered_cheats() & CHEAT_DISABLE_BANANAS) {
        gParticlePtrList_addObject(arg0);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003D5A0.s")

void func_8003DBA0(Object *obj, s32 arg1) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk78 = 3;
    obj->unk7C.word = 16;
    if(!is_in_tracks_mode()) {
        if (func_8000E1DC() && is_in_adventure_two()) {
            obj->unk78 = 0;
        } else {
            obj->unk78 = 3;
        }
    }
    if (obj->unk78 == 3) {
        obj->unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

void func_8003DC5C(Object *obj, s32 arg1) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk78 = 3;
    obj->unk7C.word = 0;
    if(!is_in_tracks_mode()) {
        if (func_8000E1DC() && !is_in_adventure_two()) {
            obj->unk78 = 0;
        } else {
            obj->unk78 = 3;
        }
    }
    if (obj->unk78 == 3) {
        obj->unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003DD14.s")

typedef struct unk8003DE74 {
    u8 pad0[8];
    u8 unk8;
} unk8003DE74;

void func_8003DE74(Object *obj, unk8003DE74 *arg1) {
    Settings *settings;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    arg1->unk8 &= 0xF;
    obj->unk78 = arg1->unk8;
    settings = get_settings();
    if (!is_in_tracks_mode() && !(settings->keys & (1 << obj->unk78))) {
        return;
    }
    gParticlePtrList_addObject(obj);
}

#define WORLD_KEY_GRAB_CHECK_RADIUS 50
#define SOUND_WORLD_KEY_GRAB 54

typedef struct Object_64_8003DF08 {
    s16 unk0;
} Object_64_8003DF08;

/**
 * Rotates the key and checks to see if the player grabbed it.
 */
void obj_loop_world_key(Object *worldKeyObj, s32 speed) {
    Settings *settings;
    Object *playerObj;
    
    // Check if the player is near the key
    // "worldKeyObj->unk4C->unk13" is the player's distance from the key (Up to 255).
    if (worldKeyObj->unk4C->unk13 < WORLD_KEY_GRAB_CHECK_RADIUS) {
        // "worldKeyObj->unk4C->unk0" is only set when the player is within 255 units of 
        // the key object, otherwise it is NULL.
        playerObj = worldKeyObj->unk4C->unk0;
        if (playerObj != NULL) {
            if (playerObj->descriptor_ptr->unk54 == 1) {
                Object_64_8003DF08 *obj64 = playerObj->unk64;
                if (obj64->unk0 != -1) {
                    // Player has grabbed the key!
                    play_sound(SOUND_WORLD_KEY_GRAB);
                    settings = get_settings();
                    settings->keys |= 1 << worldKeyObj->unk78; // Set key flag
                    gParticlePtrList_addObject(worldKeyObj); // Makes the key unload.
                }
            }
        }
    }
    
    // Rotate world key 
    worldKeyObj->y_rotation += speed * 256;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003DFCC.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003E140.s")

void func_8003E5B0(s32 arg0, s32 arg1) {

}

void func_8003E5BC(s32 arg0, s32 arg1) {

}

void func_8003E5C8(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x18;
    arg0->unk4C->unk12 = 0;
    arg0->unk78 = func_8000C8B4(0x1E0, arg0);
    arg0->unk7C.word = 0;
}

void func_8003E630(Object *arg0) {
    Object_64 *temp = arg0->unk64;
    switch (temp->unk18) {
        case 0:
        case 1:
            func_8003E694();
            break;
        case 2:
        case 3:
        case 10:
        case 11:
            func_8003F2E8();
            break;
    }
    return;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003E694.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003EC14.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003EDD8.s")

void func_8003F0D0(void) {
    D_8011D4DC = 0;
}

void func_8003F0DC(void) {
    D_8011D4DC--;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003F0F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003F2E8.s")

#ifdef NON_MATCHING

typedef struct unk8003FC44 {
    s8 unk0;
    s8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s8 unk7;
} unk8003FC44;

// Regalloc issues
void func_8003FC44(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, f32 arg5, s32 arg6) {
    Object *someObj;
    unk8003FC44 sp24;

    sp24.unk4 = (s32)arg1 + 0x24;
    sp24.unk1 = 0xA;
    sp24.unk2 = arg0;
    sp24.unk0 = arg3;
    sp24.unk7 = arg6;
    sp24.unk6 = arg2;
    someObj = func_8000EA54(&sp24, 1);
    if (someObj != NULL) {
        someObj->scale *= 3.5 * arg5;
        someObj->unk3C_a.unk3C = NULL;
        someObj->x_velocity = 0.0f;
        someObj->y_velocity = 0.0f;
        someObj->z_velocity = 0.0f;
    }
    if (arg4 != 0) {
        func_80009558(arg4, arg0, arg1, arg2, 4, 0);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003FC44.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003FD68.s")

void func_800098A4(s32, s32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Object_64_8003FEF4 {
    u8 unk0;
    u8 pad1;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    union {
        struct {
            u8 unk8;
            u8 unk9;
            u8 unkA;
            u8 padB;
        };
        s32 unk8_word;
    };
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
} Object_64_8003FEF4;

typedef struct LevelObjectEntry8003FEF4 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u16 unkA;
    u8 unkC;
    u8 unkD;
    u16 unkE;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} LevelObjectEntry8003FEF4;

void func_8003FEF4(Object *arg0, LevelObjectEntry8003FEF4 *arg1) {
    Object_64_8003FEF4 *obj64;

    obj64 = arg0->unk64;
    obj64->unk0 = arg1->unk8;
    obj64->unk2 = arg1->unkA;
    obj64->unkC = arg1->unkC;
    obj64->unkD = arg1->unkD;
    obj64->unk8_word = 0;
    obj64->unk4 = arg1->unkE;
    obj64->unk11 = arg1->unk12;
    obj64->unk10 = arg1->unk11;
    obj64->unkE = arg1->unk9;
    obj64->unkF = arg1->unk10;
    obj64->unk12 = arg1->unk13;
    func_800098A4(obj64->unk0, obj64->unk2, arg1->common.x, arg1->common.y, arg1->common.z,
                  obj64->unkF, obj64->unkE, obj64->unk10, obj64->unk12, obj64->unk4, obj64->unk11, 
                  obj64->unkC, obj64->unkD);
    gParticlePtrList_addObject(arg0);
}

typedef struct LevelObjectEntry8004001C {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8004001C;

typedef struct Object_64_8004001C {
    u16 pad0;
    s16 unk2;
    u8 unk4;
    u8 unk5;
} Object_64_8004001C;

void func_8004001C(Object *arg0, LevelObjectEntry8004001C *entry) {
    s32 temp;
    Object_64_8004001C *obj64 = (Object_64_8004001C*)arg0->unk64;
    obj64->unk2 = entry->unk8;
    temp = entry->unk9;
    obj64->unk4 = temp & 0xFF;
    obj64->unk5 = entry->unkA;
    func_80009968(entry->common.x, entry->common.y, entry->common.z, obj64->unk2, obj64->unk4, obj64->unk5);
    gParticlePtrList_addObject(arg0);
}

/* Size: 12 bytes */
typedef struct LevelObjectEntry800400A4 {
    LevelObjectEntryCommon common;
    s16 unk8;
    s8 unkA;
    s8 unkB;
} LevelObjectEntry800400A4;

typedef struct Object_64_800400A4 {
    s16 unk0;
    s16 pad2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Object_64_800400A4;

void func_800400A4(Object *obj, LevelObjectEntry800400A4 *arg1, s32 arg2) {
    Object_64_800400A4 *obj64;
    LevelModel *levelModel;
    s16 numberOfTexturesInLevel;

    obj64 = obj->unk64;
    levelModel = func_8002C7C4();
    obj64->unk0 = arg1->unk8;
    if (obj64->unk0 < 0) {
        obj64->unk0 = 0;
    }
    numberOfTexturesInLevel = levelModel->numberOfTextures;
    if (obj64->unk0 >= numberOfTexturesInLevel) {
        obj64->unk0 = numberOfTexturesInLevel - 1;
    }
    obj64->unk4 = (s16) arg1->unkA;
    obj64->unk6 = (s16) arg1->unkB;
    if (arg2 == 0) {
        obj64->unk8 = 0;
        obj64->unkA = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80040148.s")

typedef struct unk800403A8 {
    u8 pad0[0x64];
    s32 unk64;
} unk800403A8;

void func_800403A8(unk800403A8 *arg0, s32 arg1, s32 arg2) {
    arg0->unk64 = func_80031CAC(arg0, arg1);
}

void func_800403D8(Object *arg0, s32 arg1, s32 arg2) {
    arg0->unk64 = func_800BE654(arg0->unk2E, arg0->x_position, arg0->z_position);
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x1E;
    arg0->unk4C->unk12 = 0;
}

f32 func_800BEEB4(Object_64*);

void func_80040448(Object *arg0, s32 arg1) {
    if (arg0->unk64 != NULL) {
        arg0->y_position = func_800BEEB4(arg0->unk64);
    }
    arg0->unk18 += arg1 * 8;
}

/* Size: 12 bytes */
typedef struct LevelObjectEntry8004049C {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8004049C;

void func_8004049C(Object *arg0, LevelObjectEntry8004049C *arg1, s32 arg2) {
    f32 phi_f0;
    arg0->unk64 = func_800BE654(arg0->unk2E, arg0->x_position, arg0->z_position);
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x1E;
    phi_f0 = arg1->unk9 & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    arg0->scale = arg0->descriptor_ptr->unkC * phi_f0;
    arg0->unk3A = arg1->unk8;
    arg0->y_rotation = arg1->unkA << 6 << 4;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80040570.s")

typedef struct unk80040800 {
    u8 pad0[0x78];
    f32 unk78;
} unk80040800;

void func_80040800(unk80040800 *arg0, s16 *arg1) {
    f32 temp = arg1[4];
    temp *= temp;
    arg0->unk78 = temp;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80040820.s")

void func_8004092C(s32 arg0, s32 arg1) {
    func_800AC8A8(arg0);
}

void func_8004094C(Object *arg0, s16 *arg1, s32 arg2) {
    func_800ACF60(arg0);
    arg0->scale = arg1[4];
    arg0->scale /= 40.0f;
}

void func_800409A4(s32 arg0, s32 arg1, s32 arg2) {
    func_800BF524(arg0);
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800409C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80040C54.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80041A90.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80041E80.s")

typedef struct unk80042014_arg0_64 {
    u16 unk0;
    u8 unk2;
    u8 unk3;
} unk80042014_arg0_64;

typedef struct unk80042014_arg0 {
    u8 pad0[0x64];
    unk80042014_arg0_64 *unk64;
} unk80042014_arg0;

typedef struct unk80042014_arg1 {
    u8 pad0[8];
    u16 unk8;
    u8 unkA;
    u8 unkB;
} unk80042014_arg1;

void func_80042014(unk80042014_arg0 *arg0, unk80042014_arg1 *arg1) {
    unk80042014_arg0_64 *temp = arg0->unk64;
    temp->unk0 = arg1->unk8;
    temp->unk2 = arg1->unkA;
    temp->unk3 = arg1->unkB;
}

typedef struct unk8004203C_arg1 {
    u8 pad0[0x8];
    u8 unk8;
    u8 unk9;
    u16 unkA;
} unk8004203C_arg1;

void func_8004203C(Object *arg0, unk8004203C_arg1 *arg1) {
    func_800AF134(arg0->unk6C, arg1->unk9, arg1->unk8, 0, 0, 0);
    arg0->unk78 = arg1->unkA;
}

void func_80042090(Object *arg0, s32 arg1) {
    if (arg0->unk78 >= get_random_number_from_range(0, 0x400)) {
        arg0->unk74 = 1;
    } else {
        arg0->unk74 = 0;
    }
    if (get_number_of_active_players() < 2) {
        func_800AFC3C(arg0, arg1);
    }
}

typedef struct unk8004210C {
    u8 pad0[0x3C];
    s32 unk3C;
    u8 pad40[0x24];
    s32 unk64;
} unk8004210C;

void func_8004210C(unk8004210C *arg0, s8 *arg1) {
    arg0->unk64 = get_misc_asset(0x14) + (arg1[8] << 7);
    arg0->unk3C = 0;
}

void func_80042150(s32 arg0, s32 arg1, s32 arg2) {

}

void func_80042160(s32 arg0, s32 arg1) {

}

void func_8004216C(s32 arg0, s32 arg1) {

}

typedef struct unk80042178 {
    u8 pad0[0x20];
} unk80042178;

s32 func_80016DE8(f32, f32, f32, f32, s32, unk80042178*);

typedef struct Object_3C_80042178 {
    u8 pad0[8];
    u16 unk8;
    u16 unkA;
} Object_3C_80042178;

void func_80042178(Object *obj, s32 arg1) {
    s32 temp;
    Object_3C_80042178 *obj3C;
    unk80042178 sp20;

    obj3C = obj->unk3C_a.unk3C;
    if (func_80016DE8(obj->x_position, 0, obj->z_position, (f32) obj3C->unk8, 1, &sp20) > 0) {
        obj->unk74 = obj3C->unkA;
    } else {
        obj->unk74 = 0;
    }
    func_800AFC3C(obj, arg1);
}

/* Size: 12 bytes */
typedef struct LevelObjectEntry80042210 {
    LevelObjectEntryCommon common;
    s16 unk8;
    u8 unkA;
} LevelObjectEntry80042210;

typedef struct Object_64_80042210 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[3];
    u8 unk19;
    u8 pad1A[6];
    f32 unk20;
    f32 unk24;
    u8 pad28[8];
    f32 unk30;
} Object_64_80042210;

void func_80042210(Object *obj, LevelObjectEntry80042210 *arg1) {
    Object_64_80042210 *obj64;
    
    obj64 = (Object_64_80042210*)obj->unk64;
    obj64->unk15 = arg1->unkA;
    obj64->unk0 = obj->x_position;
    obj64->unk4 = obj->y_position;
    obj64->unk8 = obj->z_position;
    obj64->unkC = arg1->unk8;
    obj64->unk10 = obj64->unkC * obj64->unkC;
    obj64->unk14 = 0;
    obj64->unk20 = obj->x_position;
    obj64->unk24 = obj->z_position;
    obj64->unk19 = 0;
    obj64->unk30 = 1.0f;
    
    if (obj64->unk15) {
        obj->unk3A = 1;
        if (is_drumstick_unlocked() || (get_settings()->trophies & 0xFF) != 0xFF) {
            gParticlePtrList_addObject(obj);
        }
    } else {
        obj->unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800422F0.s")

typedef struct Object_64_80042998 {
    u8 pad0[0x70];
    u8 unk70;
    u8 pad71;
    u8 unk72;
    u8 pad73;
    f32 unk74;
} Object_64_80042998;

void func_80042998(s32 arg0, s32 arg1) {
    Object *obj;
    Object_64_80042998 *obj64;

    func_8001F460(arg0, arg1, arg0);
    obj = func_8000BF44(-1);
    
    if (obj != NULL) {
        obj64 = obj->unk64;
        obj->unk78 = 0;
        if (obj64 != 0) {
            obj64->unk72 += arg1;
            obj64->unk70 = 2;
            obj64->unk74 = 1.0f;
            func_8000B750(arg0, -1, 2, 1, 1);
        }
    }
}

typedef struct unk80042A1C {
    u8 pad0[0x78];
    f32 unk78;
    s16 unk7C;
    s16 unk7E;
} unk80042A1C;

void func_80042A1C(unk80042A1C *arg0, s8 *arg1) {
    arg0->unk78 = arg1[9] * 8.0f;
    arg0->unk78 *= arg0->unk78;
    arg0->unk7C = arg1[8];
    arg0->unk7E = 0;
    if (is_in_tracks_mode()) {
        gParticlePtrList_addObject(arg0);
    }
    func_800C56D0(4);
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80042A90.s")

typedef struct unk80042CD0 {
    u8 pad0[0x18];
    s16 unk18;
} unk80042CD0;

void func_80042CD0(unk80042CD0 *arg0, s32 arg1) {
    func_8001F460(arg0, arg1, arg0);
    arg0->unk18 = (arg0->unk18 + (arg1 * 8)) & 0xFF;
}
