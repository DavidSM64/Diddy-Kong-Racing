/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031B60 */

#include "types.h"
#include "macros.h"
#include "structs.h"

/************ .data ************/

s32 D_800DC950 = 0;
s32 D_800DC954 = 0;
s32 D_800DC958 = 0;
s32 D_800DC95C = 0;
s32 D_800DC960 = 0;
s32 D_800DC964 = 0;
s32 D_800DC968 = 0; // Currently unknown, might be a different type.
s32 D_800DC96C = 0; // Currently unknown, might be a different type.

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
s8 D_800DCA94[16] = {
    0x00, 0x00, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00
};
s8 D_800DCA9C[4] = {
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

extern f32 D_8011D4D0;
extern s32 D_8011D4D4;
extern s32 D_8011D4D8;
extern s32 D_8011D4DC;
extern s16 D_8011D4E2;

/******************************/

Settings* get_settings();
Player_64 *func_800BE654(s16, f32, f32);
void func_80000FDC(s32, s32, f32);

void func_80031B60(void) {
    if (D_800DC950 != 0) {
        func_80071140(D_800DC950);
        D_800DC950 = 0;
        D_800DC954 = 0;
        D_800DC960 = 0;
        D_800DC964 = 0;
    }
    D_800DC95C = 0;
    D_800DC958 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031BB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031CAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031F88.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032398.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032424.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032BAC.s")

s32 func_80032C6C(void) {
    return D_800DC95C;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032C7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800337E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033A14.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033C08.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033CC0.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033DD0.s")

void func_80033F44(Player *arg0, s32 arg1) {
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

void func_80034530(Player *arg0, unk80034530 *arg1) {
    Player_64* temp;
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
void func_80034844(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80034860.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80034AF0.s")
#else
// regalloc issues
void func_80034AF0(Player *arg0, u8 *arg1) {
    f32 phi_f0 = (s32)arg1[9];
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    arg0->scale = arg0->descriptor_ptr->unkC * phi_f0;
    arg0->unk78 = arg1[8];
}
#endif

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

void func_80034E70(Player *arg0, u8 *arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->y_rotation = arg1[8] << 6 << 4; // Not sure about the values here.
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80034E9C.s")

void func_8003522C(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80035260.s")

void func_80035640(s32 arg0, s32 arg1) {

}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003564C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003572C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800357D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003588C.s")
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

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80035E34.s")

typedef struct unk80035EF8 {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
} unk80035EF8;

void func_80035EF8(Player *arg0, unk80035EF8 *arg1) {
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

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80035F6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80036040.s")

void func_80036194(Player *arg0, s32 arg1) {
    Player_64* temp;
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x1E;
    arg0->unk4C->unk12 = 0;
    temp = arg0->unk64;
    temp->unkCD.bytes.byteD = 0xFF;
    temp->unk0 = 0.0f;
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

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80037594.s")

typedef struct unk80037624 {
    u8 pad0[6];
    s16 unk6;
} unk80037624;

void func_80037624(unk80037624 *arg0, s32 arg1) {
    arg0->unk6 |= 0x4000;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003763C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800376E0.s")
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
    unk80037D08_arg0_64* unk64;
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
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800380F8.s")

void func_8003818C(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 0x81;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

// Literally the same as func_80037CE8()
void func_800381C0(s32 arg0, s32 arg1) {
    func_8001F460(arg0, arg1, arg0);
}

void func_800381E0(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

// Literally the same as func_8003818C()
void func_80038214(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 0x81;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

// Literally the same as func_800381E0()
void func_80038248(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003827C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003833C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80038710.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800387CC.s")

void func_80038854(Player *arg0, u8 *arg1) {
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

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800388D4.s")

void func_800389AC(s32 arg0, s32 arg1) {

}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800389B8.s")

void func_80038A6C(s32 arg0, s32 arg1) {

}

typedef struct unk80038A78 {
    u8 pad0[0x18];
    s16 unk18;
} unk80038A78;

void func_80038A78(unk80038A78 *arg0, s32 arg1) {
    arg0->unk18 += arg1 * 8;
    if (arg0->unk18 >= 0x100) {
        particlePtrList_addObject();
        arg0->unk18 = 0xFF;
    }
}

void func_80038AC8(s32 arg0, s32 arg1) {

}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80038AD4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80038B74.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80038BF4.s")

void func_80038D58(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0xF;
    arg0->unk4C->unk12 = 0;
    if (get_settings()->cutsceneFlags & 1) {
        arg0->unk78 = 1;
    }
}

void func_80038DC4(Player *arg0, s32 arg1) {
    if (arg0->unk78 != 0) {
        Player_3C* temp = arg0->unk3C;
        if(arg0->unk4C->unk13 < 0x78) {
            func_8006F338(temp->unk8);
            arg0->unk78 = 0;
            func_80001D04(0x30, 0, arg0);
            func_80000FDC(0x12A, 0, 1.0f);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80038E3C.s")
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

void func_800391C8(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 3;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800391FC.s")

void func_800392B8(Player *arg0, s32 arg1) {
    Player_64* temp;
    arg0->unk4C->unk14 = (u16)1;
    arg0->unk4C->unk11 = (u8)0;
    arg0->unk4C->unk10 = (u8)0x1E;
    arg0->unk4C->unk12 = (u8)0;
    temp = arg0->unk64;
    temp->unkCD.bytes.byteD = 0xFF;
    temp->unk0 = 0.0f;
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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003ACBC.s")
#else

void func_8003ACBC(Player *arg0, u8 *arg1, s32 arg2) {
    f32 phi_f0 = (s32)arg1[8]; // Regalloc issue here
    if (phi_f0 < 5.0f) {
        phi_f0 = 5.0f;
    }
    phi_f0 /= 64;
    arg0->scale = phi_f0;
    arg0->y_rotation = arg1[10] << 6 << 4; // Not sure about the values here.
    func_80011390();
}
#endif

void func_8003AD28(s32 arg0, s32 arg1) {

}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003AD34.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003AE50.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B058.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B174.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B368.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B4BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B7CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003B988.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003C1E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003C2E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003C644.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003C7A4.s")

void func_8003C9EC(Player *arg0, u8 *arg1) {
    Player_64 *temp = arg0->unk64;
    arg0->unk3A = arg1[8];
    arg0->y_rotation = arg1[9] << 6 << 4;
    temp->unk0 = arg0->y_position;
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

void func_8003CE64(Player *arg0, u8 *arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
    arg0->unk78 = arg1[8];
}

void func_8003CEA0(Player *arg0, s32 arg1) {
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

void func_8003CF58(Player *arg0, u8 *arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = arg1[9];
    arg0->unk78 = arg1[8];
    arg0->unk7C.word = arg1[9];
}

void func_8003CF98(Player *arg0, s32 arg1) {
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

void func_8003D534(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x1E;
    arg0->unk7C.half.upper = 0x14;
    arg0->unk7C.half.lower = 0x10;
    if (func_8009C30C() & 0x1000) {
        particlePtrList_addObject(arg0);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003D5A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003DBA0.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003DC5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003DD14.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003DE74.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003DF08.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003DFCC.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003E140.s")

void func_8003E5B0(s32 arg0, s32 arg1) {

}

void func_8003E5BC(s32 arg0, s32 arg1) {

}

void func_8003E5C8(Player *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x18;
    arg0->unk4C->unk12 = 0;
    arg0->unk78 = func_8000C8B4(0x1E0, arg0);
    arg0->unk7C.word = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003E630.s")
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
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003FC44.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003FD68.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003FEF4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8004001C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800400A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80040148.s")

typedef struct unk800403A8 {
    u8 pad0[0x64];
    s32 unk64;
} unk800403A8;

void func_800403A8(unk800403A8 *arg0, s32 arg1, s32 arg2) {
    arg0->unk64 = func_80031CAC(arg0, arg1);
}

void func_800403D8(Player *arg0, s32 arg1, s32 arg2) {
    arg0->unk64 = func_800BE654(arg0->unk2E, arg0->x_position, arg0->z_position);
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x1E;
    arg0->unk4C->unk12 = 0;
}

f32 func_800BEEB4(Player_64*);

void func_80040448(Player *arg0, s32 arg1) {
    if (arg0->unk64 != NULL) {
        arg0->y_position = func_800BEEB4(arg0->unk64);
    }
    arg0->unk18 += arg1 * 8;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8004049C.s")
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

void func_8004094C(Player *arg0, s16 *arg1, s32 arg2) {
    func_800ACF60();
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
    unk80042014_arg0_64* unk64;
} unk80042014_arg0;

typedef struct unk80042014_arg1 {
    u8 pad0[8];
    u16 unk8;
    u8 unkA;
    u8 unkB;
} unk80042014_arg1;

void func_80042014(unk80042014_arg0 *arg0, unk80042014_arg1 *arg1) {
    unk80042014_arg0_64* temp = arg0->unk64;
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

void func_8004203C(Player *arg0, unk8004203C_arg1 *arg1) {
    func_800AF134(arg0->unk6C, arg1->unk9, arg1->unk8, 0, 0, 0);
    arg0->unk78 = arg1->unkA;
}

void func_80042090(Player *arg0, s32 arg1) {
    if (arg0->unk78 >= func_8006F94C(0, 0x400)) {
        arg0->unk74 = 1;
    } else {
        arg0->unk74 = 0;
    }
    if (func_8009C3C8() < 2) {
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
    arg0->unk64 = func_8001E29C(0x14) + (arg1[8] << 7);
    arg0->unk3C = 0;
}

void func_80042150(s32 arg0, s32 arg1, s32 arg2) {

}

void func_80042160(s32 arg0, s32 arg1) {

}

void func_8004216C(s32 arg0, s32 arg1) {

}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80042178.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80042210.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800422F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80042998.s")

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
        particlePtrList_addObject(arg0);
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


