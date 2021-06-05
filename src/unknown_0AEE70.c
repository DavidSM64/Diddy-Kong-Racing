/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800AE270 */

#include "types.h"
#include "macros.h"

/************ .rodata ************/

const char D_800E87F0[] = "\nMaximum limit of %d lens flare switches, per level, has been exceeded.";

// File Boundary! Not sure where the split occurs. Need to split when that gets figured out.
const DoubleLiteral D_800E8838 = { 0.0 };

const char D_800E8840[] = "\n\nUnknown trigger type in initParticleTrigger %d, Max %d.\n\n";
const char D_800E887C[] = "\n\nUnknown particle type in initParticleTrigger %d, Max %d.\n\n";
const char D_800E88BC[] = "\n\nUnknown trigger type in initParticleTrigger %d, Max %d.\n\n";
const char D_800E88F8[] = "Sprite Particle buffer is full.\n";
const char D_800E891C[] = "Triangle Particle buffer is full.\n";
const char D_800E8940[] = "Rectangle Particle buffer is full.\n";
const char D_800E8964[] = "Line Particle buffer is full.\n";
const char D_800E8980[] = "Point Particle buffer is full.\n";
const char D_800E89A4[] = "\n\nCan't allocate space for unknown particle type.";
const char D_800E89D8[] = "\n\nParticle has been freed twice, this is Super Safe, Honest!\n";
const char D_800E8A18[] = "\n\nSprite Particle Buffer is empty.\n\n";
const char D_800E8A40[] = "\n\nTriangle Particle Buffer is empty.\n\n";
const char D_800E8A68[] = "\n\nRectangle Particle Buffer is empty.\n\n";
const char D_800E8A90[] = "\n\nLine Particle buffer is empty.\n\n";
const char D_800E8AB4[] = "\n\nPoint Particle buffer is empty.\n\n";
const char D_800E8AD8[] = "\n\nCan't deallocate space for unknown particle type.\n\n";
const char D_800E8B10[] = "\nError :: trigger %x has no reference to point %x";
const char D_800E8B44[] = "\nError :: particle %x is not indexed correctly in trigger list %x (%d >> %p)";

/*********************************/

/************ .data ************/

// I woundn't be suprised if most of these zeroes are really just null pointers.
s32 D_800E2CA0 = 0;
s32 D_800E2CA4 = 0;
s32 *D_800E2CA8 = NULL;
s32 D_800E2CAC = 0;
s32 D_800E2CB0 = 0;
s32 *D_800E2CB4 = NULL;
s32 D_800E2CB8 = 0;
s32 D_800E2CBC = 0;
s32 *D_800E2CC0 = NULL;
s32 D_800E2CC4 = 0;
s32 D_800E2CC8 = 0;
s32 *D_800E2CCC = NULL;
s32 D_800E2CD0 = 0;
s32 D_800E2CD4 = 0;
s32 *D_800E2CD8 = NULL;
s32 D_800E2CDC = 0;
s32 *D_800E2CE0 = NULL;
s32 *D_800E2CE4 = NULL;
s32 D_800E2CE8 = 0;
s32 *D_800E2CEC = NULL;
s32 *D_800E2CF0 = NULL;
s32 D_800E2CF4 = 0;
s32 *D_800E2CF8 = NULL;
s32 *D_800E2CFC = NULL;
s32 D_800E2D00[2] = { 0, 0 };

/* Size: 0x10 bytes, might just be an array? */
typedef struct unk800E2D08 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
} unk800E2D08;

unk800E2D08 D_800E2D08[5] = {
    { 0x4000, 0x0102, 0x0100, 0x0000, 0x0000, 0x01E0, 0x0100, 0x01E0 },
    { 0x4000, 0x0203, 0x0100, 0x0000, 0x0100, 0x01E0, 0x01E0, 0x01E0 },
    { 0x4001, 0x0204, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000, 0x01E0 },
    { 0x4002, 0x0305, 0x0100, 0x0000, 0x01E0, 0x0000, 0x01E0, 0x01E0 },
    { 0x4000, 0x0103, 0x0100, 0x0000, 0x0000, 0x01E0, 0x01E0, 0x01E0 }
};

// This might be a different struct/type
unk800E2D08 D_800E2D58[2] = {
    { 0x0000, 0x01FF, 0x01FF, 0x0000, 0x01FF, 0x01FF, 0x0000, 0x0000 },
    { 0x01FF, 0x0000, 0x0000, 0x01FF, 0x0000, 0x01FF, 0x01FF, 0x0000 }
};

/* Size: 0x40 bytes, might just be an array? */
typedef struct unk800E2D78 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
    s16 unk10, unk12, unk14, unk16, unk18, unk1A, unk1C, unk1E;
    s16 unk20, unk22, unk24, unk26, unk28, unk2A, unk2C, unk2E;
    s16 unk30, unk32, unk34, unk36, unk38, unk3A, unk3C, unk3E;
} unk800E2D78;

unk800E2D78 D_800E2D78[2] = {
    {
        0x0000, 0x0105, 0x0000, 0x0000, 0x0080, 0x0000, 0x0080, 0x01FF, 
        0x0000, 0x0504, 0x0000, 0x0000, 0x0080, 0x01FF, 0x0000, 0x01FF, 
        0x0001, 0x0206, 0x0080, 0x0000, 0x0100, 0x0000, 0x0100, 0x01FF, 
        0x0001, 0x0605, 0x0080, 0x0000, 0x0100, 0x01FF, 0x0080, 0x01FF 
    },
    {
        0x0002, 0x0307, 0x0100, 0x0000, 0x0180, 0x0000, 0x0180, 0x01FF, 
        0x0002, 0x0706, 0x0100, 0x0000, 0x0180, 0x01FF, 0x0100, 0x01FF, 
        0x0003, 0x0004, 0x0180, 0x0000, 0x0200, 0x0000, 0x0200, 0x01FF, 
        0x0003, 0x0407, 0x0180, 0x0000, 0x0200, 0x01FF, 0x0180, 0x01FF
    },
};

/* Size: 0x18 bytes, might just be an array? */
typedef struct unk800E2DF8 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
    s16 unk10, unk12, unk14, unk16;
} unk800E2DF8;

unk800E2DF8 D_800E2DF8[2] = {
    {
        0x0000, 0x0000, 0x01FF, 0x0000, 0x01FF, 0x01FF, 0x0000, 0x0000, 
        0x01FF, 0x0000, 0x01FF, 0x01FF
    },
    {
        0x0000, 0x0000, 0x01FF, 0x0000, 0x01FF, 0x01FF, 0x0000, 0x0000, 
        0x01FF, 0x0000, 0x01FF, 0x01FF
    },
};

f32 D_800E2E28 = 0.0f;

f32 D_800E2E2C[8] = {
    0.0f, 0.1, 0.2f, 0.3f, 0.45f, 0.525f, 0.6f, 0.8f
};

s32 D_800E2E4C = 0;
s32 D_800E2E50 = 0;
s32 D_800E2E54 = 0;
s32 D_800E2E58 = 0;
s32 D_800E2E5C = 0;
s32 *D_800E2E60 = NULL;
s32  D_800E2E64 = 0;

s16 D_800E2E68[6] = {
    0, 8, 7, -4, -7, -4
};

s16 D_800E2E74[8] = {
    -6, 6, 6, 6, 6, -6, -6, -6
};

s32 D_800E2E84[16] = {
    0x00000000, 0xC00840FF, 0xFF6008FF, 0x404040FF, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x1070FFFF, 0x00000000, 0x00000000
};

s32 D_800E2EC4[10] = {
    0x404040FF, 0x404040FF, 0x002D00FF, 0x002D00FF, 
    0x403C0AFF, 0x403C0AFF, 0x4040FFFF, 0x4040FFFF, 
    0x404040FF, 0x404040FF
};

s32 D_800E2EEC = 0x100;

/*******************************/

void func_800AE2D8(void);
void func_800AE374(void);
void func_800AE438(void);
void func_800AE490(void);

void func_800AE270(void) {
    func_800AE374();
    func_800AE438();
    func_800AE2D8();
}

void func_800AE2A0(void) {
    func_800AE374();
    func_800AE438();
    func_800AE490();
    func_800AE2D8();
}

void func_800AE2D8(void) {
    s32 phi_s1;
    s32 phi_s0;

    if (D_800E2E60 != NULL) {
        phi_s1 = 0;
        phi_s0 = 0;
        if (D_800E2E64 > 0) {
            do {
                func_8007CCB0(*(D_800E2E60 + phi_s1));
                phi_s0 += 1;
                phi_s1 += 1;
            } while (phi_s0 < D_800E2E64);
        }
        func_80071140(D_800E2E60);
        D_800E2E60 = 0;
    }
}

void func_800AE374(void) {
    if (D_800E2CA8 != NULL) {
        func_80071140(D_800E2CA8);
        D_800E2CA8 = NULL;
    }
    if (D_800E2CB4 != NULL) {
        func_80071140(D_800E2CB4);
        D_800E2CB4 = NULL;
    }
    if (D_800E2CC0 != NULL) {
        func_80071140(D_800E2CC0);
        D_800E2CC0 = NULL;
    }
    if (D_800E2CCC != NULL) {
        func_80071140(D_800E2CCC);
        D_800E2CCC = NULL;
    }
    if (D_800E2CD8 != NULL) {
        func_80071140(D_800E2CD8);
        D_800E2CD8 = NULL;
    }
}

void func_800AE438(void) {
    if (D_800E2CE0 != NULL) {
        func_80071140(D_800E2CE0);
        D_800E2CE0 = NULL;
    }
    if (D_800E2CE4 != NULL) {
        func_80071140(D_800E2CE4);
        D_800E2CE4 = NULL;
    }
}

void func_800AE490(void) {
    if (D_800E2CEC != NULL) {
        func_80071140(D_800E2CEC);
        D_800E2CEC = NULL;
    }
    if (D_800E2CF0 != NULL) {
        func_80071140(D_800E2CF0);
        D_800E2CF0 = NULL;
    }
    if (D_800E2CF8 != NULL) {
        func_80071140(D_800E2CF8);
        D_800E2CF8 = NULL;
    }
    if (D_800E2CFC != NULL) {
        func_80071140(D_800E2CFC);
        D_800E2CFC = NULL;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AE530.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AE728.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AEE14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AEEB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AEF88.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF024.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF0A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF0F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF134.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF1E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF29C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF404.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF52C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF6E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF714.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AFC3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AFE5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B0010.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B03C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B0698.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B0BAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B1130.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B1CB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B2040.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B2260.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B22FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B263C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B26E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B2FBC.s")

