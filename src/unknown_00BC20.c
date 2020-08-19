/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8000B020 */

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "fast3d.h"

extern s32 D_800DC700;
extern s16 D_800DC708;
extern s32 D_800DC718;
extern s8 D_800DC71C;
extern s16 D_800DC724;
extern s16 D_800DC728;
extern s16 D_800DC72C;
extern u8 D_800DC730;
extern u8 D_800DC738;
extern s8 D_800DC73C;
extern s8 D_800DC740;
extern s8 D_800DC744;
extern s8 D_800DC748;
extern s32 D_800DC760;
extern s8 D_800DC848;
extern f32 D_800E514C;
extern f32 D_800E5150;

extern s16 D_8011AC20[12];
extern s16 D_8011AD4E;
extern s8 D_8011AD20[4];
extern s8 D_8011AD21;
extern s8 D_8011AD22[2];
extern s8 D_8011AD25;
extern s8 D_8011AD26;
extern s32 D_8011AD34;
extern s8 D_8011AD3C;
extern s8 D_8011AD3D;

typedef struct unk8011AD40 {
    s16 unk0;
    s8 pad2[0xA];
    f32 unkC;
    f32 unk10;
    f32 unk14;
} unk8011AD40;

extern unk8011AD40 *D_8011AD40;
extern s8 D_8011AD44;
extern s8 D_8011AD45;
extern s16 D_8011AD46;
extern s16 D_8011AD48;
extern s16 D_8011AD4A;
extern s16 D_8011AD4C;
extern s8 D_8011AD50;
extern s8 D_8011AD51;
extern s8 D_8011AD52;
extern s8 D_8011AD53;
extern s32 *D_8011AD58;
extern s32 D_8011AD5C;
extern s32 D_8011AD60;
extern s32 *D_8011AD64;
extern s32 D_8011AD68;
extern s32 *D_8011AD6C;
extern s32 *D_8011AD70;
extern Gfx *D_8011AD78[9];
extern s32 D_8011ADA0;
extern s16 D_8011ADA4;
extern f32 D_8011ADA8;
extern s32 D_8011ADAC;

extern s32 D_8011ADB0;
extern s32 D_8011ADB8;
extern s32 D_8011ADBC;
extern u8 D_8011ADC4;
extern s32 D_8011ADC8;
extern s8 (*D_8011ADCC)[8];
extern f32 D_8011ADD0;
extern s8 D_8011ADD4;
extern s8 D_8011ADD5;
extern s8 D_8011AE00;
extern s8 D_8011AE01;
extern s8 D_8011AE02;
extern s8 D_8011AE03;
u32 *D_8011AE08[16];
extern s32 (*D_8011AE48)[8]; // Unknown number of entries.
extern u8 (*D_8011AE4C)[8]; // Unknown number of entries.
extern u32 (*D_8011AE58)[64]; // Not sure about the number of elements
extern s32 D_8011AE5C;
extern s32 D_8011AE60;
extern s32 D_8011AE64;
extern s32 *D_8011AE68;
extern s32 *D_8011AE6C;
extern s32 D_8011AE70;
extern s32 *D_8011AE74;
extern s16 D_8011AE78;
extern s16 D_8011AE7A;
extern s16 D_8011AE7C;
extern s8 D_8011AE7E;
extern s16 D_8011AE82;
extern s32 D_8011AE88;
extern s32 D_8011AEB0[2];
extern s16 *D_8011AEB8;
extern s32 D_8011AEBC;
extern s32 *D_8011AEC4;
extern s32 D_8011AEC8;

/* Size: 0x3C bytes */
typedef struct unknown8011AECC {
    u8 unk00[0x3A];
    s8 unk3A;
    s8 unk3B;
} unknown8011AECC;
extern unknown8011AECC* D_8011AECC; // Array of structs, unknown number of members

extern s32 D_8011AED0;
extern s32 D_8011AED4;
extern s16 D_8011AED8;
extern u32 (*D_8011AEDC)[64]; // Not sure about the number of elements
extern s32 D_8011AEE0;
extern Player *(*D_8011AEE4)[8];
extern s32 *D_8011AEE8;
extern s32 *D_8011AEEC;
extern s32 D_8011AEF0;
extern u8 D_8011AEF4;
extern u8 D_8011AEF5;
extern u8 D_8011AEF6;
extern u8 D_8011AEF7;
extern u32 (*D_8011AF04)[64]; // Not sure about the number of elements
extern s32 D_8011AF08[2];
extern s32 D_8011AF10;
extern s32 D_8011AF60;

/* Size: 0x40 bytes */
typedef struct unk800179D0 {
    s32 unk0;
    u32* unk04;
    u32* unk08;
    f32 unk0C[12];
    u32 unk3C;
} unk800179D0;

/* Unknown Size */
typedef struct unk800179D0_2 {
    unk800179D0* unk0; 
    s32 unk04; 
} unk800179D0_2;

extern unk800179D0_2 D_8011AFF4;
extern u32* D_8011B020[10];

extern s16 D_8011D5AC;

extern s32 osTvType;

void func_8000C460(void);

void *func_80070B78(s32, u32);
void *func_80070C9C(s32, u32);
s32 *func_80076C58(s32);
void func_8001D258(f32, f32, s32, s32, s32);

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B020.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B290.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B38C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B750.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000BADC.s")

u32* func_8000BF44(s32 arg0) {
    if (arg0 == -1) {
        arg0 = D_800DC760;
    }
    if (arg0 < 0 || arg0 >= 10) {
        return NULL;
    }
    return D_8011B020[arg0];
}

void func_8000C2D8(u8 *arg0, s32 length);

void func_8000BF8C(void) {
    s32 i;

    func_8001D258(D_800E514C, D_800E5150, 0, -0x2000, 0);
    D_8011AE68 = (s32*)func_80070B78(0x15800, 0x200);
    D_8011AEC4 = (s32*)func_80070C9C(0x320, 0xFFFF);
    D_8011AE6C = (s32*)func_80070C9C(0x50, 0xFFFF);
    D_8011AE74 = (s32*)func_80070C9C(0x200, 0xFFFF);
    D_8011AECC = (unknown8011AECC*)func_80070C9C(0xE10, 0xFFFF);
    D_8011AEDC = (s32*)func_80070C9C(0x50, 0xFFFF);
    D_8011AEE4 = (s32*)func_80070C9C(0x28, 0xFFFF);
    D_8011AEEC = (s32*)func_80070C9C(0x28, 0xFFFF);
    D_8011AEE8 = (s32*)func_80070C9C(0x28, 0xFFFF);
    D_8011AF04 = (s32*)func_80070C9C(0x200, 0xFFFF);
    D_8011ADCC = (s32*)func_80070C9C(8, 0xFFFF);
    D_8011AFF4.unk0 = (s32*)func_80070C9C(0x400, 0xFFFF);
    D_8011AEB8 = (s32*)func_80076C58(0x23);
    D_8011AEBC = (func_80076F30(0x23) >> 1) - 1;
    while (D_8011AEB8[D_8011AEBC] == 0) {
        D_8011AEBC--;
    }
    D_8011AD58 = (s32*)func_80070C9C(0x800, 0xFFFF);
    D_8011AD64 = func_80076C58(0x21);
    D_8011AD68 = 0;
    while (-1 != D_8011AD64[D_8011AD68]) {
        D_8011AD68++;
    }
    D_8011AD68--;
    D_8011AE48 = (s32*)func_80070C9C(D_8011AD68 << 2, 0xFFFFFFFF);
    D_8011AE4C = (s32*)func_80070C9C(D_8011AD68, 0xFFFFFFFF);
    
    for (i = 0; i < D_8011AD68; i++) {
        (*D_8011AE4C)[i] = 0;
    }
    
    D_8011AD6C = func_80076C58(0xF);
    D_8011AD70 = func_80076C58(0x10);
    D_8011ADA0 = 0;
    while (-1 != D_8011AD70[D_8011ADA0]) {
        D_8011ADA0++;
    }
    func_8000C2D8(&D_8011AD6C[D_8011AD70[65]], (D_8011AD70[66] - D_8011AD70[65]) * 4);
    D_8011AE58 = (u32**)func_80070C9C(0x800, 0xFFFF);
    D_8011ADC4 = 0;
    D_8011AEF4 = 0;
    D_8011AEF5 = 0;
    D_8011ADA8 = 2.0f;
    func_8000C460();
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C2D8.s")
#else
// Decrypts cheats
void func_8000C2D8(u8 *arg0, s32 length) {
    u8 sp3;
    u8 sp2;
    u8 sp1;
    u8 sp0;
    //s32 numWords;
    s32 i;

    //numWords = length / 4;
    
    for (i = 0; i < length; i++) {
        sp0 = ((arg0[i + 3] & 0xC0) >> 6) | (arg0[i + 0] & 0xC0) | ((arg0[i + 1] & 0xC0) >> 2) | ((arg0[i + 2] & 0xC0) >> 4);
        sp1 = ((arg0[i + 3] & 0x30) >> 4) | ((arg0[i + 0] & 0x30) << 2) | (arg0[i + 1] & 0x30) | ((arg0[i + 2] & 0x30) >> 2);
        sp2 = ((arg0[i + 3] & 0xC) >> 2) | ((arg0[i + 0] & 0xC) << 4) | ((arg0[i + 1] & 0xC) << 2) | (arg0[i + 2] & 0xC);
        sp3 = (arg0[i + 3] & 3) | (arg0[i + 0] << 6) | ((arg0[i + 1] & 3) << 4) | ((arg0[i + 2] & 3) << 2);
        arg0[i + 0] = ((sp0 & 0x55) << 1) | ((sp0 & 0xAA) >> 1);
        arg0[i + 1] = ((sp1 & 0x55) << 1) | ((sp1 & 0xAA) >> 1);
        arg0[i + 2] = ((sp2 & 0x55) << 1) | ((sp2 & 0xAA) >> 1);
        arg0[i + 3] = ((sp3 & 0x55) << 1) | ((sp3 & 0xAA) >> 1);
    }
}
#endif

void func_8000C460(void) {
    s32 i;
    
    D_8011AD26 = 1;
    D_8011AD5C = 0;
    D_8011AD60 = 0;
    D_8011AEC8 = 0;
    D_8011AE70 = 0;
    D_8011AED0 = 0;
    D_8011AED4 = 0;
    D_8011AEF0 = 0;
    D_8011AE78 = 0;
    D_8011AD21 = 0;
    D_8011AD22[0] = 0;
    D_8011AD22[1] = 0;
    
    for (i = 0; i < 0x80; i++) {
        (*D_8011AF04)[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        (*D_8011ADCC)[i] = 0;
    }
    for (i = 0; i < 0x10; i++) {
        D_8011AFF4.unk0[i].unk0 = 0;
    }
    
    D_8011AF08[0] = 0xFF;
    D_8011AF08[1] = 0xFF;
    D_8011AE5C = 0;
    D_8011AE60 = 0;
    D_8011AE64 = 0;
    D_8011AE88 = 0;
    D_8011ADD4 = 0;
    D_8011AE7A = 0;
    D_8011AE7E = 1;
    D_8011AE7C = 0;
    D_8011AD44 = 0;
    D_8011AEF6 = 0;
    D_8011AEF7 = 0;
    D_8011AF60 = 0;
    D_8011AE00 = 0;
    D_8011AE01 = 1;
    D_8011AD53 = 0;
    D_8011ADD5 = 0;
}

void func_8000C604(void) {
    s32 i, len;
    func_80059B4C();
    D_800DC748 = 0;
    if (D_800DC71C != 0) {
        func_80072298(1);
    }
    D_800DC71C = 0;
    if (D_800DC744 && is_in_two_player_adventure()) {
        D_800DC744 = 0;
        func_8006F398();
    }
    func_8001004C();
    len = D_8011AE5C;
    for (i = 0; i < len; i++) {
        func_800101AC((*D_8011AE58)[i], 1);
    }
    D_8011AEC8 = 0;
    D_8011AE5C = 0;
    D_8011AE60 = 0;
    func_8000C460();
    func_80071140(D_8011AEB0[0]);
    func_80071140(D_8011AEB0[1]);
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C718.s")

void func_8000C844(s32 arg0) {
    if ((*D_8011AE4C)[arg0] != 0) {
        (*D_8011AE4C)[arg0]--;
        if ((*D_8011AE4C)[arg0] == 0) {
            func_80071140((*D_8011AE48)[arg0]);
        }
    }
}

s32 func_8000C8B4(s32 arg0) {
    if (osTvType != 0 || arg0 < 0) {
        return arg0;
    }
    else {
        return (arg0 * 5) / 6;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C8F8.s")

void func_8000CBC0(void) {
    s32 i = 0;
    while(i < 16){ // For some odd reason, using a for loop here makes this not match.
        D_8011AE08[i] = NULL;
        i++;
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000CBF0.s")
#else
void func_8000CBF0(u32 *arg0, s32 arg1) {
    u32 **temp = &D_8011AE08[arg1];
    u32 *temp2;
    temp2 = *temp;
    if (temp2 != NULL) {
        return;
    }
    D_8011AE08[arg1] = arg0;
    return; // I can't get this second return to appear.
}
#endif

s32 func_8000CC20(u32 *arg0) {
    s32 i;
    s32 phi_v1;

    phi_v1 = -1;
    for(i = 0; i < 0x10; i++){
        if (D_8011AE08[i] == 0) {
            phi_v1 = i;
            i = 0x10;
        }
    }
    if (phi_v1 != -1) {
        D_8011AE08[phi_v1] = arg0;
    }
    return phi_v1;
}

// Has a jump table
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000CC7C.s")

// Has a jump table
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E0B0.s")

void func_8000E128(void) {
    D_800DC708 = 0x8000;
}

s8 func_8000E138() {
    return D_8011AD20[0];
}

s8 func_8000E148() {
    return D_800DC71C;
}

s8 func_8000E158(void) {
    if (D_800DC740 != 0) {
        return D_800DC73C;
    }
    else {
        return 0;
    }
}

s8 func_8000E184() {
    return D_800DC748;
}

void func_8000E194(void) {
    D_800DC73C = 1 - D_800DC73C;
    D_800DC740 = 0;
}

void func_8000E1B8(void) {
    D_800DC73C = 0;
    D_800DC740 = 0;
}

s8 func_8000E1CC(void) {
    return D_8011AE02;
}

s8 func_8000E1DC() {
    return D_8011AE03;
}

void func_8000E1EC(unk8011AD40 *arg0, s32 arg1) {
    D_8011AD40 = arg0;
    D_8011AD44 = 4;
    D_8011AD45 = arg1;
    D_8011AD46 = arg0->unkC;
    D_8011AD48 = arg0->unk10;
    D_8011AD4A = arg0->unk14;
    D_8011AD4C = arg0->unk0;
    func_8000FFB8();
    D_8011AEF0 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E2B4.s")

void func_8000E4BC(s32 arg0) {
    D_8011AEF4 = arg0;
}

u8 func_8000E4C8() {
    return D_8011AEF4;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E4D8.s")

u32 func_8000E948(s32 arg0) {
    if (arg0 < 0 || arg0 >= D_8011AE5C) {
        return 0;
    }
    return (*D_8011AE58)[arg0];
}

u32 *func_8000E988(s32 *arg0, s32 *arg1) {
    *arg0 = D_8011AE60;
    *arg1 = D_8011AE5C;
    return *D_8011AE58;
}

// Unused?
s32 func_8000E9B0(void) {
    return D_8011AE5C;
}

// Unused?
s32 func_8000E9C0(void) {
    return D_8011AE64;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E9D0.s")

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000EA54.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000F648.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000F758.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000F7EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000F99C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FAC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FBCC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FC6C.s")

/* Unknown Size */
typedef struct unk8000FD20_2 {
    u8 unk00[0x13];
    u8 unk13;
} unk8000FD20_2;

/* Unknown Size */
typedef struct unk8000FD20 {
    u8 unk00[0x4C];
    unk8000FD20_2* unk4C;
} unk8000FD20;

s32 func_8000FD20(unk8000FD20* arg0, unk8000FD20_2* arg1) {
    arg0->unk4C = arg1;
    arg1->unk13 = 0xFF;
    return 0x28;
}

/* Unknown Size. This might just be unk8000FD20. */
typedef struct unk8000FD34 {
    u8 unk00[0x5C];
    s32 unk5C;
} unk8000FD34;

s32 func_8000FD34(unk8000FD34 *arg0, s32 arg1) {
    arg0->unk5C = arg1;
    func_80016BC4();
    return 0x10C;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FD54.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FFB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001004C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800101AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80010994.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011134.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011264.s")

void func_80011390(void) {
    D_8011ADAC = 0;
}

s32 func_8001139C() {
    return D_8011ADB0;
}

s32 func_800113AC() {
    return D_8011ADB8;
}

s32 func_800113BC() {
    return D_8011ADBC;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800113CC.s")

void func_80011560(void) {
    D_800DC848 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011570.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011960.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011AD0.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011C94.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800120C8.s")

void func_80012C30(void) {
    D_8011ADA4 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012C3C.s")

void func_80012C98(Gfx **dlist) {
    if (D_8011ADA4 < 9) {
        fast3d_cmd((*dlist)++, 0x00000000, 0x00000000); // Fast3D NOP
        D_8011AD78[D_8011ADA4] = *dlist;
    }
}

void func_80012CE8(Gfx **dlist) {
    if (D_8011ADA4 < 9) {
        fast3d_cmd((*dlist)++, 0xB8000000, 0x00000000); // End display list
        fast3d_cmd(D_8011AD78[D_8011ADA4] - 1, 0x6010000, (u32)*dlist); // Jump to display list
        D_8011ADA4++;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012D5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012E28.s")

void func_80012F30(Player *arg0) {
    if (arg0->unk48 == 1) {
        Player_64 *player_64 = arg0->unk64;
        arg0->y_rotation -= player_64->unk160;
        arg0->x_rotation -= player_64->unk162;
        arg0->z_rotation -= player_64->unk164;
        arg0->y_position -= D_8011ADD0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012F94.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001348C.s")

void func_80013548(Player *arg0) {
    if ((arg0->unk6 & 0x8000) == 0 && arg0->descriptor_ptr->unk54 == 1) {
        arg0->x_position -= arg0->unk64->unk78;
        arg0->y_position -= arg0->unk64->unk7C;
        arg0->z_position -= arg0->unk64->unk80;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800135B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800138A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80013A0C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80013DCC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80014090.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800142B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800143A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80014814.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80014B50.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80015348.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800155B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800159C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016500.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016748.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016BC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016C68.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016DE8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001709C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80017248.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001790C.s")

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80017978.s")

u32 func_800179D0(void) {
    s16 i = 0;
    while(i < 16) {
        unk800179D0* temp = &D_8011AFF4.unk0[i]; 
        if (temp->unk0 != 0) {
            temp->unk0--;
        }
        i++;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80017A18.s")

void func_80017E74(s32 arg0) {
    D_8011AED8 = arg0;
    D_8011ADAC = 0;
}

s16 func_80017E88(void) {
    return D_8011AED8;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80017E98.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800185E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80018C6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80018CE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001955C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/D_80019808.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001A7D8.s")

void func_8001A8D4(s32 arg0) {
    D_8011AD4E = 0x12C;
    D_8011AD50 = 0;
    D_8011AD52 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001A8F4.s")

s16 func_8001AE44() {
    return D_8011AD4E;
}

s32 func_8001AE54() {
    return D_8011ADC8;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001AE64.s")

s32 func_8001B288(void) {
    if (func_800599A8() != func_8006BD88()) {
        return 0;
    } else {
        if (D_800DC728 != D_8011AE82) {
            return 0;
        } else {
            return 1;
        }
    }
}


s32 func_8001B2E0() {
    return D_8011AD34;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B2F0.s")

s32 func_8001B3AC(s32 arg0) {
    return arg0 == D_800DC718;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B3C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B4FC.s")

s32 func_8001B640() {
    return D_800DC718;
}

s32 func_8001B650(void) {
    return D_800DC738 == 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B668.s")

void func_8001B738(s32 arg0) {
    func_80059B7C(arg0, func_800599A8(), D_800DC728, D_800DC72C, D_800DC724);
}

u8 func_8001B780() {
    return D_800DC730;
}

void func_8001B790(void) {
    D_8011D5AC = -1;
    D_800DC730 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B7A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B834.s")

// Returns a pointer to some struct that is 0x3C bytes long.
unknown8011AECC *func_8001BA00(s32 arg0) {
    return &D_8011AECC[arg0];
}

unknown8011AECC *func_8001BA1C(s32 arg0, s32 arg1) {
    unknown8011AECC *val = &D_8011AECC[arg0];
    if (arg1 != 0 && val->unk3A != -1) {
       val = &D_8011AECC[val->unk3A];
    }
    return val;
}

s32 func_8001BA64() {
    return D_8011AED0;
}

Player **func_8001BA74(s32 *arg0) {
    *arg0 = D_8011AEF0;
    return *D_8011AEE4;
}

s32 *func_8001BA90(s32 *arg0) {
    *arg0 = D_8011AEF0;
    return D_8011AEEC;
}

s32 *func_8001BAAC(s32 *arg0) {
    *arg0 = D_8011AEF0;
    return D_8011AEE8;
}

Player *func_8001BAC8(s32 arg0) {
    if (D_8011AEF0 == 0) {
        return NULL;
    }
    if(arg0 < 0 || arg0 >= D_8011AEF0) {
        return NULL;
    }
    return (*D_8011AEE4)[arg0];
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BB18.s")

void func_8001BC40(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BC54.s")

u32 func_8001BD94(s32 arg0) {
    if (arg0 < 0 || arg0 >= D_8011AEE0) {
        return 0;
    }
    return D_8011AEDC[0][arg0];
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BDD4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BF20.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001C418.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001C48C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001C524.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001C6C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001CC48.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001CD28.s")

void func_8001D1AC(void) {
    D_8011AF10 = 1;
}

void func_8001D1BC(s32 arg0) {
    if (arg0 != D_8011AF08[0]) {
        D_8011AF08[1] = D_8011AF08[0];
        D_8011AF08[0] = arg0;
    }
}

u32 func_8001D1E4(s32 *arg0) {
    *arg0 = D_8011AF08[1];
    return D_8011AF04[0][D_8011AF08[1]];
}

u32 func_8001D214(s32 arg0) {
    if (arg0 >= 0 && arg0 < 0x80) {
        return D_8011AF04[0][arg0];
    }
    return 0;
}

void func_8001D23C(s32 arg0, s32 arg1, s32 arg2) {
    
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D258.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D4B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D5E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D6E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D80C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001DD54.s")

s32 *func_8001E29C(s32 arg0) {
    if (arg0 < 0 || arg0 >= D_8011ADA0) {
        return D_8011AD6C;
    }
    return (s32*)&D_8011AD6C[D_8011AD70[arg0]];
}

s32 func_8001E2EC(s32 arg0) {
    if (arg0 >= 0 && arg0 < 8) {
        if (D_8011ADCC[0][arg0] > 0) {
            D_8011ADCC[0][arg0]--;
        }
        return D_8011ADCC[0][arg0];
    }
    return 0;
}

void func_8001E344(s32 arg0) {
    s32 temp = 8;
    if (arg0 >= 0 && arg0 < 8) {
        D_8011ADCC[0][arg0] = 8;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E36C.s")

s16 func_8001E440() {
    return D_8011AE7A;
}

void func_8001E450(s32 arg0) {
    D_8011AE7A = arg0;
}

void func_8001E45C(s32 arg0) {
    if (arg0 != D_8011AE7A) {
        D_8011AE7A = arg0;
        D_8011ADAC = 0;
        D_8011AE7E = (u8)1;
        if (func_8006DA0C() == 1) {
            func_8006F42C();
        }
    }
}

// Unused?
s32 func_8001E4B4(void) {
    return D_8011AE60;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E4C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E6EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E89C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E93C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001EE74.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001EFA4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001F23C.s")

s8 func_8001F3B8(void) {
    return D_8011ADD4;
}

void func_8001F3C8(s32 arg0) {
    if (arg0 != D_8011ADD4) {
        D_8011AE78 = 0;
    }
    D_8011ADD4 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001F3EC.s")

void func_8001F450(void) {
    D_8011AD53 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001F460.s")

s32 func_800210CC(s8 arg0) {
    if (arg0 >= D_8011AD3D) {
        D_8011AD3D = arg0;
        return 1;
    }
    return 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80021104.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002125C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80021400.s")

s8 func_800214C4(void) {
    return D_8011AD20[3 - D_8011AD21];
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800214E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80021600.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022540.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002263C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002277C.s")

f32 func_80022888(f32 *arg0, u32 arg1, f32 arg2) {
    f32 result = arg0[arg1 + 1] + ((arg0[arg1 + 2] - arg0[arg1 + 1]) * arg2);
    return result;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800228B0.s")
#else
f32 func_800228B0(f32 *arg0, u32 arg1, f32 arg2, f32 *arg3) {
    f32 temp_f12;
    f32 temp_f2;
    // regalloc issues
    temp_f2 = (arg0[arg1 + 2] - arg0[arg1 + 1]) * arg2;
    temp_f12 = arg0[arg1 + 1];
    *arg3 = arg0[arg1 + 2] - arg0[arg1 + 1];
    return temp_f12 + temp_f2;
}
#endif

// Unused?
void func_800228DC(s32 arg0, s32 arg1, s32 arg2) {

}

void func_800228EC(s32 arg0) {
    Player_64 *player_64;

    D_8011AEF7 = 3;
    player_64 = func_8001BAC8(0)->unk64;
    player_64->unk190 = 0;
    player_64->unk192 = 0;
    player_64->unk193 = 0;
    player_64->unk1BA = 0;
    func_80017E74(arg0);
    func_8006F388(10);
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022948.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022CFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022E18.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800230D0.s")

s8 func_8002341C(void) {
    return D_8011AEF6;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002342C.s")

//GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80023568.s")

s32 func_80023568(void) {
    if (D_8011AD3C != 0) {
        return D_8011AD25 + 1;
    } else if (func_8006BD98() == 8) {
        return D_8011AD25 + 1;
    }
    return 0;
}

s8 func_800235C0(void) {
    return D_8011ADD5;
}

void func_800235D0(s32 arg0) {
    D_8011ADD5 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800235DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800238BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80023E30.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80023F48.s")

s16* func_80024594(s32 *arg0, s32 *arg1) {
    *arg0 = D_800DC700;
    *arg1 = 0x80;
    return D_8011AC20;
}

void func_800245B4(s16 arg0) {
    D_8011AC20[D_800DC700++] = arg0;
    if (D_800DC700 >= 0x80) {
        D_800DC700 = 0;
    }
}

