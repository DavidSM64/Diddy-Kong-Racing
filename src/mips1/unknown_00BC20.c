/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8000B020 */

#include "types.h"
#include "macros.h"

extern s32 D_800DC700;
extern s16 D_800DC708;
extern s32 D_800DC718;
extern s8 D_800DC71C;
extern u8 D_800DC730;
extern u8 D_800DC738;
extern s8 D_800DC73C;
extern s8 D_800DC740;
extern s8 D_800DC748;
extern s32 D_800DC760;
extern s8 D_800DC848;

extern s16 D_8011AC20[12];
extern s16 D_8011AD4E;
extern s8 D_8011AD20;
extern s8 D_8011AD21;
extern s8 D_8011AD22;
extern s8 D_8011AD23;
extern s32 D_8011AD34;
extern s8 D_8011AD3D;
extern s8 D_8011AD50;
extern s8 D_8011AD51;
extern s8 D_8011AD52;
extern s8 D_8011AD53;
extern s16 D_8011ADA4;
extern s32 D_8011ADAC;
extern s32 D_8011ADB0;
extern s32 D_8011ADB8;
extern s32 D_8011ADBC;
extern s32 D_8011ADC8;
extern u8* D_8011ADCC[8];
extern s8 D_8011ADD4;
extern s8 D_8011ADD5;
extern s8 D_8011AE02;
extern s8 D_8011AE03;
u32* D_8011AE08[16];
extern u32* D_8011AE58[64]; // Not sure about the number of elements
extern s32 D_8011AE5C;
extern s16 D_8011AE78;
extern s16 D_8011AE7A;

/* Size: 0x3C bytes */
typedef struct unknown8011AECC {
    u8 unk00[0x3A];
    s8 unk3A;
    s8 unk3B;
} unknown8011AECC;
extern unknown8011AECC* D_8011AECC; // Array of structs, unknown number of members

extern s32 D_8011AED0;
extern s16 D_8011AED8;
extern u32* D_8011AEDC[64]; // Not sure about the number of elements
extern s32 D_8011AEE0;
extern s32 D_8011AEE4;
extern s32 D_8011AEE8;
extern s32 D_8011AEEC;
extern s32 D_8011AEF0;
extern u8 D_8011AEF4;
extern u8 D_8011AEF6;
extern u32* D_8011AF04[64]; // Not sure about the number of elements
extern s32 D_8011AF10;

/* Size: 0x40 bytes */
typedef struct unk800179D0 {
    s32 unk00;
    u32* unk04;
    u32* unk08;
    f32 unk0C[12];
    u32 unk3C;
} unk800179D0;

/* Unknown Size */
typedef struct unk800179D0_2 {
    unk800179D0* unk00; 
    s32 unk04; 
} unk800179D0_2;

extern unk800179D0_2 D_8011AFF4;
extern u32* D_8011B020[10];

extern s16 D_8011D5AC;

extern s32 osTvType;


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

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000BF8C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C2D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C460.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C604.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C718.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C844.s")

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

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000CBF0.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000CC20.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000CC7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E0B0.s")

void func_8000E128(void) {
    D_800DC708 = 0x8000;
}

s8 func_8000E138() {
    return D_8011AD20;
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

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E1EC.s")
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
    return D_8011AE58[0][arg0];
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E988.s")
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
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012C98.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012CE8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012D5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012E28.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012F30.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012F94.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001348C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80013548.s")
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


//GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800179D0.s")
u32 func_800179D0(void) {
    s16 i = 0;
    while(i < 16) {
        unk800179D0* temp = &D_8011AFF4.unk00[i]; 
        if (temp->unk00 != 0) {
            temp->unk00--;
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
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B288.s")

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
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B738.s")

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

s32 func_8001BA74(s32 *arg0) {
    *arg0 = D_8011AEF0;
    return D_8011AEE4;
}

s32 func_8001BA90(s32 *arg0) {
    *arg0 = D_8011AEF0;
    return D_8011AEEC;
}

s32 func_8001BAAC(s32 *arg0) {
    *arg0 = D_8011AEF0;
    return D_8011AEE8;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BAC8.s")
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

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D1BC.s")

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
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E29C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E2EC.s")

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

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E45C.s")
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
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800214C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800214E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80021600.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022540.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002263C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002277C.s")

f32 func_80022888(f32 *arg0, u32 arg1, f32 arg2) {
    f32 result = arg0[arg1 + 1] + ((arg0[arg1 + 2] - arg0[arg1 + 1]) * arg2);
    return result;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800228B0.s")

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800228EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022948.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022CFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022E18.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800230D0.s")

s8 func_8002341C(void) {
    return D_8011AEF6;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002342C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80023568.s")

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

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800245F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80024744.s")


