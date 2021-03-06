/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80042D20 */

#include "unknown_043920.h"
#include "memory.h"

#include "types.h"
#include "macros.h"
#include "structs.h"


/************ .data ************/

s32 D_800DCB50 = 0x310;
s16 D_800DCB54 = 0;
s32 D_800DCB58 = 0; // Currently unknown, might be a different type.
s32 D_800DCB5C = 0; // Currently unknown, might be a different type.

// Not sure if D_800DCB58 & D_800DCB5C are actually a part of this array.
f32 D_800DCB60[14] = {
    -10.0f, 5.0f, 0.0f, 0.0f,
    10.0f, 5.0f, 0.0f, 0.0f,
    -10.0f, 10.0f, 0.0f, 0.0f, 
    10.0f, 10.0f
};

s32 D_800DCB98 = 0; // Currently unknown, might be a different type.
f32 D_800DCB9C[19] = { 
    0.004f, 0.007f, 0.0099999999f, 0.004f, 
    0.0099999999f, 0.0099999999f, 0.0099999999f, 0.0099999999f, 
    0.0099999999f, 0.0099999999f, 0.004f, 0.004f, 
    0.004f, 0.004f, 0.004f, 0.004f, 
    0.004f, 0.004f, 0.004f
};

f32 D_800DCBE8[19] = {
    0.8f, 0.85f, 0.85f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.8f,
    0.8f, 0.84f, 0.8f, 0.8f,
    0.8f, 0.8f, 0.8f
};

// Unused? Not sure if this is actually an array or just some random data.
s32 D_800DCC34[19] = {
    0, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0
};

s32 D_800DCC80[13] = {
    0, 26, 27, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
};

// Unused?
s16 D_800DCCB4[12] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
};

u16 D_800DCCCC[20] = {
    0x010C, 0x010B, 0x0009, 0x010C,
    0x010C, 0x010C, 0x010C, 0x010C, 
    0x010C, 0x010C, 0x010C, 0x0005, 
    0x010C, 0x010C, 0x010C, 0x010C, 
    0x010C, 0x010C, 0x010C, 0x0000
};

s32 D_800DCCF4[19] = {
    1, 4, 16, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0x100, 1, 1, 1, 1, 1, 
};

s32 D_800DCD40[20] = {
    0, 4, 16, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0x100, 0, 0, 0, 0,
    0, 0
};

s8 D_800DCD90[15] = {
    1, 1, 2, 2, 4, 3, 0, 6,
    4, 3, 2, 2, 5, 5, 5
};

// Unused?
s8 D_800DCDA0[8] = {
    0, 0, 0, 1, 1, 2, 2, 2,
};

s8 D_800DCDA8[8] = {
    1, 1, 1, 2, 3, 2, 3, 2 
};

// Unused?
s16 D_800DCDB0[16] = {
    0x02FE, 0x03FE, 0x02FC, 0x02FB,
    0x02FB, 0x02FE, 0x02FD, 0x02FE,
    0x03FD, 0x05FC, 0x04FE, 0x02FE,
    0x02FA, 0x02FE, 0x08F8, 0x03FD
};

// Checksum count for func_8003B4BC
s32 D_800DCDD0 = 42391;

s16 D_800DCDD4[4] = {
    0, 0, 0x32, -1
    // There might be one or two extra zeroes here.
};

/*******************************/

/************ .rodata ************/

const char D_800E6280[] = "%.1f,%.1f,%.1f\n";
const char D_800E6290[] = "Chk ovflow!!\n";
const char D_800E62A0[] = "Back\n";

/*********************************/

/************ .bss ************/

s32 D_8011D4F0[2];
s32 D_8011D4F8[3];
s32 D_8011D504;
s32 D_8011D508[2];

/* Size: 0x18 bytes */
typedef struct unk8011D510 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} unk8011D510;
unk8011D510 D_8011D510;

s32 D_8011D528;
s32 D_8011D52C;
s32 D_8011D530;
s32 D_8011D534;
s32 D_8011D538;
s32 D_8011D53C;
s32 D_8011D540;
s32 D_8011D544;
s32 D_8011D548;
s32 D_8011D54C;
s16 D_8011D550;
s8 D_8011D552;
s8 D_8011D553;
s32 D_8011D554;
s32 D_8011D558;
s32 D_8011D55C;
s32 D_8011D560;
s32 D_8011D564;
s32 D_8011D568;
s32 D_8011D56C;
s32 D_8011D570;
s32 D_8011D574;
s32 D_8011D578;
s32 D_8011D57C;
s8 D_8011D580;
s8 D_8011D581;
s8 D_8011D582;
s8 D_8011D583;
s8 D_8011D584;
s8 D_8011D585;
s8 D_8011D586;
s8 D_8011D587;
s8 D_8011D588;
s8 D_8011D589;
s8 D_8011D58A;
s8 D_8011D58B;
s8 D_8011D58C;
s8 D_8011D58D;
s8 D_8011D58E;
s8 D_8011D58F;
u32 D_8011D590[2];
s32 D_8011D598;
s8 D_8011D59C;
s8 D_8011D59D;
s16 D_8011D59E;
s16 D_8011D5A0[2];
s32 D_8011D5A4;
s16 D_8011D5A8[2];
s16 D_8011D5AC;
s16 D_8011D5AE;
s32 D_8011D5B0;
s32 D_8011D5B4;
s16 D_8011D5B8;
s8 D_8011D5BA;
s8 D_8011D5BB;
s8 D_8011D5BC;

/******************************/

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80042D20.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80043ECC.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80044170.s")

s32 func_80044450(s32 arg0) {
    return get_random_number_from_range(0, 99) < arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004447C.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80045128.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_800452A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80045C48.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80046524.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80048C7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80048E64.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_800494E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80049794.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004C0A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004C140.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004C2B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004CC20.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004D590.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004D95C.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004DAB0.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004DE38.s")

typedef struct unk8004F77C {
    u8 unk0[0x20A];
    u8 unk20A;
} unk8004F77C;

void func_8004F77C(unk8004F77C *arg0) {
    s32 temp;

    arg0->unk20A &= ~0x80;
    if ((D_8011D528 & 0x4000) != 0) {
        arg0->unk20A |= 0x80;
    }

    temp = arg0->unk20A & 0xF;
    if ((arg0->unk20A & 0xC0) != 0) {
        temp++;
        if (temp >= 3) {
            temp = 2;
        }
    } else {
        temp--;
        if (temp < 0) {
            temp = 0;
        }
    }

    arg0->unk20A = (arg0->unk20A & 0xFFF0) | temp;
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8004F7F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80050754.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80050850.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80050A28.s")

s32 func_80052188(void) {
    if (D_8011D582 == 2) {
        D_8011D582 = 1;
        return 1;
    }
    return 0;
}

void func_800521B8(s32 arg0) {
    D_8011D582 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_800521C4.s")

/* Unknown Size */
typedef struct unk8005234C {
    u8 unk0[0x16C];
    s16 unk16C;
} unk8005234C;

void func_8005234C(unk8005234C *arg0) {
    arg0->unk16C -= arg0->unk16C >> 3;
    if (arg0->unk16C >= -9 && arg0->unk16C < 10) { // Deadzone?
        arg0->unk16C = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80052388.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8005250C.s")

void func_80052988(Object* arg0, Object_64* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    arg5 *= arg7;

    if ((D_8011D55C == -1) && (arg2 >= 3)) {
        arg0->unk3B = 0;
        arg1->unk1F2 = 0;
    } else if (arg0->unk3B == 0) {
        if (arg6 & 1) {
            if (arg0->unk18 >= 0x29) {
                arg0->unk18 -= arg7 * 4;
                if (arg0->unk18 < 0x29) {
                    arg0->unk3B = arg2;
                    arg0->unk18 = arg3;
                }
            } else {
                arg0->unk18 += arg7 * 4;
                if (arg0->unk18 >= 0x28) {
                    arg0->unk3B = arg2;
                    arg0->unk18 = arg3;
                }
            }
        } else {
            arg0->unk3B = arg2;
            arg0->unk18 = arg3;
            arg1->unk1F3 &= ~0x80;
        }
    } else if (arg0->unk3B == arg2) {
        if (arg6 & 2) {
            if (arg1->unk1F3 & 0x80) {
                arg0->unk18 -= arg5;
                if (arg0->unk18 <= 0) {
                    arg0->unk3B = 0;
                    arg1->unk1F2 = 0;
                    arg0->unk18 = 0x28;
                    arg1->unk1F3 = 0;
                }
            } else {
                arg0->unk18 += arg5;
                if (arg0->unk18 >= arg4) {
                    arg0->unk18 = arg4 - 1;
                    if ((arg6 & 4) == 0) {
                        arg1->unk1F3 |= 0x80;
                    }
                }
            }
        } else {
            arg0->unk18 += arg5;
            if (arg0->unk18 >= arg4) {
                arg0->unk3B = 0;
                arg1->unk1F2 = 0;
                arg0->unk18 = 0x28;
                arg1->unk1F3 = 0;
            }
        }
    } else {
        arg0->unk18 = arg3;
        arg0->unk3B = arg2;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80052B64.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80052D7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80053478.s")


extern unk8011D510 D_8011D510;

/* Unknown Size */
typedef struct unk800535C4 {
    s16 unk0;
    s16 unk2;
} unk800535C4;

/* Unknown Size */
typedef struct unk800535C4_2 {
    u8 unk0[0x9C];
    s32 unk9C;
    s32 unkA0;
    s32 unkA4;
    u8 unkA8[0xF8];
    s16 unk1A0;
    s16 unk1A2;
    s16 unk1A4;
} unk800535C4_2;

/* Size: 0x40 Bytes */
typedef struct unk800535C4_3 {
    u8 unk0[0x40];
} unk800535C4_3;

void guMtxXFMF(unk800535C4_3*, f32, f32, f32, s32*, s32*, s32*);

void func_800535C4(unk800535C4 *arg0, unk800535C4_2 *arg1) {
    unk800535C4_3 sp30;

    D_8011D510.unk0 = -arg1->unk1A0;
    D_8011D510.unk2 = -arg0->unk2;
    D_8011D510.unk4 = -arg1->unk1A4;
    D_8011D510.unkC = 0;
    D_8011D510.unk10 = 0;
    D_8011D510.unk14 = 0;
    D_8011D510.unk8 = 1;
    func_8006FE74(&sp30, &D_8011D510);

    guMtxXFMF(&sp30, 0, -1, 0, &arg1->unkA0, &arg1->unkA4, &arg1->unk9C);
}

void func_80053664(Object_64 *arg0) {
    if (arg0->throttle > 0.0) {
        arg0->throttle -= 0.1;
    }

    if (D_8011D528 & 0x8000) {
        arg0->throttle = 1.0f;
    }

    if (D_8011D528 & 0x4000) {
        if (arg0->brake < 1.0) {
            arg0->brake += 0.2;
        }
    } else {
        //! @bug Will cause a negative brake value resulting in higher velocity
        if (arg0->brake > 0.05) {
            arg0->brake -= 0.1;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80053750.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80053E9C.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80054110.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8005492C.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80054FD0.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80055A84.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80055EC0.s")

/* Unknown Size */
typedef struct unk800570A4 {
    u8 unk0[0x108];
    s32 unk108;
    u8 unk10C[0x102];
    s16 unk20E;
    s8 unk210;
} unk800570A4;

/* Unknown Size */
typedef struct unk800570A4_2 {
    u8 unk0[0xC];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 unk18[0x4C];
    unk800570A4* unk64;
} unk800570A4_2;

/* Unknown Size */
typedef struct unk80056930 {
    u8 unk0[0x3];
    s8 unk3;
} unk80056930;

void func_80057048(unk800570A4_2 *arg0, s32 arg1);

void func_80056930(unk800570A4_2 *arg0, unk80056930 *arg1) {
    if ((get_filtered_cheats() & 0x100) != 0) {
        func_800570B8(arg0, 0x162, 8, 0x82);
    } else {
        func_80057048(arg0, arg1->unk3 + 0x156);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8005698C.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80056E2C.s")


void func_80057048(unk800570A4_2 *arg0, s32 arg1) {
    unk800570A4 *temp = arg0->unk64;
    u16 temp2 = arg1;
    if (D_8011D55C != -1 && temp->unk108 == 0) {
        func_80001EA8(temp2, arg0->unkC, arg0->unk10, arg0->unk14, 0);
    }
}

void func_800570A4(unk800570A4_2 *arg0, s32 arg1, s32 arg2) {
    unk800570A4 *temp = arg0->unk64;
    temp->unk20E = arg1;
    temp->unk210 = arg2;
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_800570B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80057220.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_800575EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_800576E0.s")

extern s32 D_8011D534;

/* Unknown Size */
typedef struct unk800579B0 {
    u8 unk0[0x1E1];
    s8 unk1E1;
} unk800579B0;

void func_800579B0(unk800579B0 *arg0, s32 arg1, f32 arg2) {
    s32 temp, temp2;

    temp = D_8011D534 - arg0->unk1E1;
    temp2 = (s32)((f64)((f32)temp * arg2) * 0.125);

    if (temp != 0 && temp2 == 0) {
        if (temp > 0) {
            temp2 = 1;
        }
        if (temp < 0) {
            temp2 = -1;
        }
    }

    arg0->unk1E1 = arg0->unk1E1 + temp2;
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80057A40.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_800580B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_800581E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80058B84.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80058D5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80058F44.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80059080.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80059208.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80059790.s")

void func_800598D0(void) {
    D_8011D590[0] = allocate_from_main_pool_safe(0x21C0, COLOR_TAG_RED);
    D_8011D590[1] = D_8011D590[0] + 0x10E0;
    D_8011D590[2] = 0;
    D_8011D5A0[0] = 0;
    D_8011D5A0[1] = 0;
    D_8011D5A0[2] = 0;
    D_8011D5A8[0] = 0;
    D_8011D5A8[1] = 0;
    D_8011D59D = 0;
    D_8011D5AC = -1;
}

void func_80059944(void) {
    D_8011D59C = D_8011D59D;
    D_8011D5A0[D_8011D59C] = 0;
    D_8011D5A8[D_8011D59C] = 0;
    D_8011D59E = 0;
}

void func_80059984(s32 arg0) {
    D_8011D59D = (s8) ((D_8011D59C + 1) & 1);
    D_8011D5AC = arg0;
}

s16 func_800599A8(void) {
    return D_8011D5AC;
}

s32 func_800599B8(s32 arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4) {
    s32 temp_v0;
    s32 temp_t8;
    s16 sp2E;

    temp_t8 = (D_8011D59C + 1) & 1;
    temp_v0 = func_80074B34(arg0, (s16)arg1, arg2, arg3, arg4, &sp2E, D_8011D590[temp_t8]);
    if (arg3 != 0) {
        if (temp_v0 == 0) {
            D_8011D5A0[temp_t8] = sp2E;
            D_8011D5AC = arg1;
        } else {
            D_8011D5AC = -1;
        }
    }

    return temp_v0;
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80059A68.s")

void func_80059B4C(void) {
    if (D_8011D598 != 0) {
        free_from_memory_pool(D_8011D598);
    }
    D_8011D598 = 0;
}

void func_80059B7C(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    func_80075000(arg0, (s16)arg1, arg2, arg3, arg4, D_8011D5A0[D_8011D59C], D_8011D590[D_8011D59C]);
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80059BF0.s")

s16 func_80059E20(void) {
    return D_8011D5A8[D_8011D59C];
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80059E40.s")

void func_8005A3B0(void) {
    D_8011D584 = 1;
}

void func_8005A3C0(void) {
    D_8011D583 = 1;
}

void func_8003B4BC(s32 arg0);

void func_8005A3D0(void) {
    s32 i;
    s32 count = 0;
    u8* temp = (u8*)&func_8003B4BC;

    for(i = 0; i < D_800DCB50; i++) {
        count += temp[i];
    }

    if (count != D_800DCDD0) {
        D_800DCB54 = 0x800;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8005A424.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8005A6F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_8005B818.s")

// This gets called if an anti-piracy checksum fails in func_8005F850.
void func_8005C25C(void) {
    D_800DCB9C[0] = 0.05f;
}

/* Unknown Size */
typedef struct unk8005C270 {
    u8 unk0[0x190];
    s16 unk190;
    s8 unk192;
    s8 unk193;
} unk8005C270;

void func_8005C270(unk8005C270 *arg0) {
    s32 temp = func_8001BA64();

    arg0->unk192--;
    if (arg0->unk192 < 0) {
        arg0->unk192 += temp;
        if(arg0->unk193 > 0){
            arg0->unk193--;
        }
    }

    if (arg0->unk190 >= -31999) {
        arg0->unk190--;
    }
}
