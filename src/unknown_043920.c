/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80042D20 */

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

s32 D_800DCC80[19] = {
    0, 26, 27, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0
};

// Unused?
s16 D_800DCCB4[6] = {
    0x010C, 0x010B, 0x0009, 0x010C,
    0x010C, 0x010C
};

u16 D_800DCCCC[14] = {
    0x010C, 0x010C, 0x010C, 0x010C,
    0x010C, 0x0005, 0x010C, 0x010C,
    0x010C, 0x010C, 0x010C, 0x010C,
    0x010C, 0x0000
};

// Unused? Not sure if this is actually an array or just some random data.
s32 D_800DCCDC[2] = {
    1, 4
};

// Used for some sort of bit mask
s32 D_800DCCF4[19] = {
    16, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0x100, 1, 1, 1, 1,
    1, 0, 4
};

// Used for some sort of bit mask
s32 D_800DCD40[18] = {
    16, 0, 0, 0, 0, 0, 0, 0,
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

const DoubleLiteral D_800E62A8 = { -2500.0 };
const DoubleLiteral D_800E62B0 = { 0.025 };
const DoubleLiteral D_800E62B8 = { 0.561 };
const DoubleLiteral D_800E62C0 = { 0.004 };
const DoubleLiteral D_800E62C8 = { 0.025 };
const DoubleLiteral D_800E62D0 = { 0.561 };
const DoubleLiteral D_800E62D8 = { 0.004 };
const DoubleLiteral D_800E62E0 = { 0.2 };
const DoubleLiteral D_800E62E8 = { 0.004 };
const DoubleLiteral D_800E62F0 = { 0.595 };
const DoubleLiteral D_800E62F8 = { 0.025 };
const DoubleLiteral D_800E6300 = { 500.0 };
const DoubleLiteral D_800E6308 = { 650.0 };
const DoubleLiteral D_800E6310 = { -0.3 };

// Jump table in func_8004447C
const u32 D_800E6318[] = {
    0x800446AC, 0x80044A04, 0x80044A04, 0x80044A04, 
    0x80044A04, 0x80044F54, 0x80044A04
};

// Jump table in func_8004447C
const u32 D_800E6334[] = {
    0x80044A2C, 0x80044A44, 0x80044A60, 0x80044A94, 
    0x80044ADC, 0x80044AC8
};

const DoubleLiteral D_800E6350 = { 300.0 };

// Jump table in func_800452A0
const u32 D_800E6358[] = {
    0x800456A0, 0x800456A8, 0x800456B0, 0x800456BC, 
    0x800456CC, 0x800456D4, 0x800456B0, 0x800456DC
};

const FloatLiteral D_800E6378 = { 1000000.0f };

// Jump table in 
const u32 D_800E637C[] = {
    0x80045ADC, 0x80045AF8, 0x80045B30, 0x80045B30, 
    0x80045B58, 0x80045B70, 0x80045BB8, 0x80045ADC
};

const DoubleLiteral D_800E63A0 = { 500.0 };
const DoubleLiteral D_800E63A8 = { 1.15 };
const DoubleLiteral D_800E63B0 = { 0.016 };
const DoubleLiteral D_800E63B8 = { 0.016 };
const DoubleLiteral D_800E63C0 = { 1.2 };
const DoubleLiteral D_800E63C8 = { 0.046 };
const DoubleLiteral D_800E63D0 = { 1.2 };
const FloatLiteral D_800E63D8 = { 1.2f };
const DoubleLiteral D_800E63E0 = { 0.046 };
const DoubleLiteral D_800E63E8 = { 0.3 };
const FloatLiteral D_800E63F0 = { 0.004f };
const DoubleLiteral D_800E63F8 = { 0.025 };
const DoubleLiteral D_800E6400 = { 300.0 };
const DoubleLiteral D_800E6408 = { 0.02 };
const DoubleLiteral D_800E6410 = { 1.7 };
const DoubleLiteral D_800E6418 = { 0.35 };
const DoubleLiteral D_800E6420 = { 0.2 };
const DoubleLiteral D_800E6428 = { 0.07 };
const DoubleLiteral D_800E6430 = { 0.8 };
const DoubleLiteral D_800E6438 = { 0.65 };
const DoubleLiteral D_800E6440 = { 0.65 };
const DoubleLiteral D_800E6448 = { 35.0 };
const FloatLiteral D_800E6450 = { -10000.0f };
const DoubleLiteral D_800E6458 = { 0.8 };
const DoubleLiteral D_800E6460 = { 0.05 };
const FloatLiteral D_800E6468 = { 0.11f };

// Jump table in func_80048C7C
const u32 D_800E646C[] = {
    0x80048D40, 0x80048D40, 0x80048E50, 0x80048DAC, 
    0x80048E18, 0x80048DB8
};

const DoubleLiteral D_800E6488 = { 0.7 };
const DoubleLiteral D_800E6490 = { 20.5 };
const DoubleLiteral D_800E6498 = { 65.0 };
const DoubleLiteral D_800E64A0 = { 0.16666666666666666 };
const DoubleLiteral D_800E64A8 = { 1.09 };
const DoubleLiteral D_800E64B0 = { 0.4 };
const DoubleLiteral D_800E64B8 = { 0.01 };
const DoubleLiteral D_800E64C0 = { 0.01 };
const DoubleLiteral D_800E64C8 = { 0.016 };
const DoubleLiteral D_800E64D0 = { 1.2 };
const FloatLiteral D_800E64D8 = { 1.2f };
const DoubleLiteral D_800E64E0 = { 0.016 };
const FloatLiteral D_800E64E8 = { 1.4f };
const FloatLiteral D_800E64EC = { 0.01f };
const FloatLiteral D_800E64F0 = { 0.02f };
const FloatLiteral D_800E64F4 = { 0.004f };
const DoubleLiteral D_800E64F8 = { 0.6 };
const DoubleLiteral D_800E6500 = { 0.3 };
const FloatLiteral D_800E6508 = { 1.2f };
const DoubleLiteral D_800E6510 = { 0.00015 };
const DoubleLiteral D_800E6518 = { 1.8 };
const DoubleLiteral D_800E6520 = { 0.4 };
const FloatLiteral D_800E6528 = { 0.4f };
const DoubleLiteral D_800E6530 = { 0.058823529411764705 };
const DoubleLiteral D_800E6538 = { 0.05 };
const DoubleLiteral D_800E6540 = { 0.65 };
const DoubleLiteral D_800E6548 = { 0.65 };
const DoubleLiteral D_800E6550 = { 0.7 };
const DoubleLiteral D_800E6558 = { 0.4 };
const DoubleLiteral D_800E6560 = { 0.005555555555555556 };
const FloatLiteral D_800E6568 = { 0.4f };
const DoubleLiteral D_800E6570 = { 65.0 };
const DoubleLiteral D_800E6578 = { 0.2 };
const FloatLiteral D_800E6580 = { 1.3f };
const FloatLiteral D_800E6584 = { 0.1f };
const FloatLiteral D_800E6588 = { 0.002f };
const FloatLiteral D_800E658C = { 0.01f };
const DoubleLiteral D_800E6590 = { 1.2 };
const DoubleLiteral D_800E6598 = { 0.45 };
const FloatLiteral D_800E65A0 = { -0.02f };
const FloatLiteral D_800E65A4 = { 0.87f };
const FloatLiteral D_800E65A8 = { 0.9f };
const FloatLiteral D_800E65AC = { -10000.0f };

// Jump table in func_8004DE38
const u32 D_800E65B0[] = {
    0x8004EB84, 0x8004EBBC, 0x8004EBD8, 0x8004EBF4, 
    0x8004EBA0, 0x8004EC10, 0x8004EC50, 0x8004EC90, 
    0x8004EC90, 0x8004ED88, 0x8004EBF4, 0x8004ECD0, 
    0x8004ED10, 0x8004ED50
};

const FloatLiteral D_800E65E8 = { 1.12f };
const FloatLiteral D_800E65EC = { 0.02f };
const FloatLiteral D_800E65F0 = { -0.02f };
const FloatLiteral D_800E65F4 = { 265.0f };
const DoubleLiteral D_800E65F8 = { 1500.0 };
const DoubleLiteral D_800E6600 = { 0.065 };
const DoubleLiteral D_800E6608 = { 0.3 };
const DoubleLiteral D_800E6610 = { 0.1 };
const DoubleLiteral D_800E6618 = { 0.3 };
const DoubleLiteral D_800E6620 = { 0.1 };
const DoubleLiteral D_800E6628 = { 0.004 };
const DoubleLiteral D_800E6630 = { 0.65 };
const DoubleLiteral D_800E6638 = { 0.024999999999999998 };
const DoubleLiteral D_800E6640 = { 0.4 };
const DoubleLiteral D_800E6648 = { 1.1 };
const DoubleLiteral D_800E6650 = { -0.3 };
const DoubleLiteral D_800E6658 = { 0.3 };
const FloatLiteral D_800E6660 = { 0.02f };
const DoubleLiteral D_800E6668 = { 0.9 };
const DoubleLiteral D_800E6670 = { 0.7 };
const DoubleLiteral D_800E6678 = { 1.7 };
const DoubleLiteral D_800E6680 = { 0.15 };
const DoubleLiteral D_800E6688 = { 0.3 };
const DoubleLiteral D_800E6690 = { 0.32 };
const DoubleLiteral D_800E6698 = { -0.04 };
const DoubleLiteral D_800E66A0 = { 0.04 };
const DoubleLiteral D_800E66A8 = { 0.9 };
const DoubleLiteral D_800E66B0 = { 0.3 };
const DoubleLiteral D_800E66B8 = { 0.1 };
const FloatLiteral D_800E66C0 = { 0.1f };
const DoubleLiteral D_800E66C8 = { 0.05 };

// Jump table in func_8005250C
const u32 D_800E66D0[] = {
    0x80052678, 0x80052978, 0x80052978, 0x800527AC, 
    0x8005280C, 0x80052858, 0x800528A4, 0x80052910
};

const DoubleLiteral D_800E66F0 = { 0.97 };
const DoubleLiteral D_800E66F8 = { 0.87 };
const DoubleLiteral D_800E6700 = { 0.9 };
const DoubleLiteral D_800E6708 = { 0.3 };
const DoubleLiteral D_800E6710 = { 1.6 };
const DoubleLiteral D_800E6718 = { 0.025 };
const FloatLiteral D_800E6720 = { 0.45f };
const DoubleLiteral D_800E6728 = { 0.97 };
const DoubleLiteral D_800E6730 = { 0.2 };
const DoubleLiteral D_800E6738 = { 0.2 };
const DoubleLiteral D_800E6740 = { 1.33 };
const DoubleLiteral D_800E6748 = { 0.53 };
const DoubleLiteral D_800E6750 = { 1.8 };
const FloatLiteral D_800E6758 = { 1.8f };
const DoubleLiteral D_800E6760 = { 0.2 };
const DoubleLiteral D_800E6768 = { 0.1 };
const DoubleLiteral D_800E6770 = { 0.2 };
const DoubleLiteral D_800E6778 = { 0.05 };
const DoubleLiteral D_800E6780 = { 0.1 };
const DoubleLiteral D_800E6788 = { 0.4 };
const DoubleLiteral D_800E6790 = { 0.1 };
const DoubleLiteral D_800E6798 = { 1.4 };
const FloatLiteral D_800E67A0 = { 0.1f };

// Jump table in func_80053E9C
const u32 D_800E67A4[] = {
    0x80053FF0, 0x8005406C, 0x800540FC, 0x8005408C, 
    0x800540C4, 0x80054098
};

const DoubleLiteral D_800E67C0 = { 20.5 };
const DoubleLiteral D_800E67C8 = { 0.3 };
const DoubleLiteral D_800E67D0 = { 0.1 };
const DoubleLiteral D_800E67D8 = { 0.3 };
const DoubleLiteral D_800E67E0 = { 0.1 };
const DoubleLiteral D_800E67E8 = { -0.3 };
const DoubleLiteral D_800E67F0 = { 0.3 };
const DoubleLiteral D_800E67F8 = { 0.9 };
const FloatLiteral D_800E6800 = { 0.02f };
const DoubleLiteral D_800E6808 = { 1.7 };
const DoubleLiteral D_800E6810 = { 0.15 };
const DoubleLiteral D_800E6818 = { 0.32 };
const DoubleLiteral D_800E6820 = { -0.04 };
const DoubleLiteral D_800E6828 = { 0.04 };
const DoubleLiteral D_800E6830 = { 0.9 };
const DoubleLiteral D_800E6838 = { 1.075 };
const DoubleLiteral D_800E6840 = { 0.15 };
const DoubleLiteral D_800E6848 = { 0.7 };
const FloatLiteral D_800E6850 = { 1500.0f };

// Jump table in func_80055EC0
const u32 D_800E6854[] = {
    0x8005635C, 0x80056370, 0x80056380, 0x8005639C, 
    0x800563EC, 0x80056508, 0x8005655C, 0x80056508, 
    0x800563EC, 0x80056620, 0x800563CC, 0x80056380, 
    0x800565C0, 0x800565E0, 0x80056600, 0x800563EC, 
    0x80056828
};

// Jump table in func_80055EC0
const u32 D_800E6894[] = {
    0x80056834, 0x80056840, 0x8005684C, 0x80056884, 
    0x80056884, 0x80056884, 0x80056884, 0x80056884, 
    0x80056884, 0x80056874, 0x80056880
};

const FloatLiteral D_800E68C4 = { 10000.0f };
const FloatLiteral D_800E68C8 = { 10000.0f };
const FloatLiteral D_800E68CC = { 0.025f };

// Jump table in func_80057A40
const u32 D_800E68D0[] = {
    0x80057BBC, 0x80057BE4, 0x80057CD0, 0x80057C0C, 
    0x80057C34, 0x80057C5C, 0x80057C84, 0x80057CAC
};

const DoubleLiteral D_800E68F0 = { 91.75 };
const DoubleLiteral D_800E68F8 = { 90.0 };
const DoubleLiteral D_800E6900 = { 48.5 };
const DoubleLiteral D_800E6908 = { 0.95 };
const DoubleLiteral D_800E6910 = { 65.0 };
const DoubleLiteral D_800E6918 = { 1.3 };
const DoubleLiteral D_800E6920 = { -0.2 };
const DoubleLiteral D_800E6928 = { 1.2 };
const DoubleLiteral D_800E6930 = { 1.2 };
const DoubleLiteral D_800E6938 = { 0.8 };
const DoubleLiteral D_800E6940 = { 0.45 };
const FloatLiteral D_800E6948 = { -0.02f };
const FloatLiteral D_800E694C = { 1000000.0f };
const DoubleLiteral D_800E6950 = { 160000.0 };
const FloatLiteral D_800E6958 = { 0.8f };
const DoubleLiteral D_800E6960 = { 160000.0 };

// Jump table in func_8005A6F0
const u32 D_800E6968[] = {
    0x8005AF80, 0x8005AFD8, 0x8005B004, 0x8005B030, 
    0x8005AFAC, 0x8005B05C, 0x8005B094, 0x8005B0CC, 
    0x8005B0CC, 0x8005B1B0, 0x8005B030, 0x8005B10C, 
    0x8005B144, 0x8005B17C
};

const DoubleLiteral D_800E69A0 = { 0.9 };
const FloatLiteral D_800E69A8 = { 0.02f };
const FloatLiteral D_800E69AC = { -0.02f };
const FloatLiteral D_800E69B0 = { 265.0f };
const DoubleLiteral D_800E69B8 = { 1500.0 };
const DoubleLiteral D_800E69C0 = { 0.025 };
const DoubleLiteral D_800E69C8 = { 0.595 };
const DoubleLiteral D_800E69D0 = { 0.004 };
const DoubleLiteral D_800E69D8 = { 1.3 };
const DoubleLiteral D_800E69E0 = { 150.0 };
const FloatLiteral D_800E69E8 = { 0.01f };
const DoubleLiteral D_800E69F0 = { 0.01 };
const DoubleLiteral D_800E69F8 = { 35.0 };
const FloatLiteral D_800E6A00 = { 0.05f };

/*********************************/

/************ .bss ************/

extern s32 D_8011D528;
extern s32 D_8011D55C;
extern s8 D_8011D582;
extern s8 D_8011D583;
extern s8 D_8011D584;
extern s32 D_8011D598;
extern s8 D_8011D59C;
extern s8 D_8011D59D;
extern s16 D_8011D59E;
extern u32 D_8011D590[];
extern s16 D_8011D5A0[];
extern s16 D_8011D5A8[];
extern s16 D_8011D5AC;

GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80042D20.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80043ECC.s")
GLOBAL_ASM("asm/non_matchings/unknown_043920/func_80044170.s")

s32 func_80044450(s32 arg0) {
    return func_8006F94C(0, 99) < arg0;
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

void func_80052988(Player* arg0, Player_64* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
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

/* Unknown Size */
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

void func_8006F64C(unk800535C4_3*, f32, f32, f32, s32*, s32*, s32*);

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

    func_8006F64C(&sp30, 0, -1, 0, &arg1->unkA0, &arg1->unkA4, &arg1->unk9C);
}

void func_80053664(Player_64 *arg0) {
    if (arg0->throttle > 0.0) {
        arg0->throttle -= D_800E6768.doubleLiteral;
    }

    if (D_8011D528 & 0x8000) {
        arg0->throttle = 1.0f;
    }

    if (D_8011D528 & 0x4000) {
        if (arg0->brake < 1.0) {
            arg0->brake += D_800E6770.doubleLiteral;
        }
    } else {
        //! @bug Will cause a negative brake value resulting in higher velocity
        if (arg0->brake > D_800E6778.doubleLiteral) {
            arg0->brake -= D_800E6780.doubleLiteral;
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
    if ((func_8009C30C() & 0x100) != 0) {
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
    D_8011D590[0] = func_80070C9C(0x21C0, 0xFF0000FF);
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
        func_80071140(D_8011D598);
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

void func_8005C25C(void) {
    D_800DCB9C[0] = D_800E6A00.floatLiteral;
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
