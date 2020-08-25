/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8009EC70 */

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "fast3d.h"

typedef enum MENU_ID {
    TITLE_SCREEN,
    LOGOS_SCREEN,
    UNUSED_2,
    CHARACTER_SELECT,
    UNUSED_4,
    UNKNOWN_5,
    FILE_SELECT,
    UNUSED_7,
    UNUSED_8,
    UNUSED_9,
    MAGIC_CODES,
    MAGIC_CODES_LIST,
    OPTIONS,
    AUDIO_OPTIONS,
    SAVE_OPTIONS,
    TRACK_SELECT,
    UNUSED_16,
    RESULTS,
    UNUSED_18,
    GAME_SELECT,
    TROPHY_RACE_ROUND,
    TROPHY_RACE_RANKINGS,
    UNUSED_22,
    UNKNOWN_23,
    GHOST_DATA,
    CREDITS,
    BOOT_SCREEN,
    UNUSED_27,
    CAUTION_MESSAGE
} MENU_ID;

extern s32 osTvType;

extern s8 D_800DF450;
extern s32 D_800DF458;
extern s32 D_800DF460;
extern s32 D_800DF46C;
extern s32 gIsInAdventureTwo;
extern s32 gActiveMagicCodes;
extern s32 gUnlockedMagicCodes;

typedef struct unk800DF4A0 {
    u8  pad0[0x5C];
    s32 unk5C;
    s32 unk60;
    u8  unk64[0xC];
    s32 unk70;
    u8  pad74[0x1C];
    s32 unk90;
    u8  pad94[0x30];
    s32 unkC4;
    s32 unkC8;
    s32 unkCC;
    u8  padD0[0x48];
    s32 unk118;
    u8  pad11C[0x100];
    s32 unk21C;
    u8  pad220[0x8];
    s32 unk228[4];
    u8  pad238[0x24];
    s32 unk25C;
    u8  pad260[0x78];
    s32 unk2D8;
    s32 unk2DC;
} unk800DF4A0;
extern unk800DF4A0* D_800DF4A0;

extern s32 D_800DF478;
extern s32 D_800DF47C;
extern s32 D_800DF480;
extern s32 D_800DF488;
extern s32 D_800DF498;
extern s32 D_800DF4B8;
extern s32 D_800DF4BC; // Number of active players?
extern s32 D_800DF4C8;
extern s32 D_800DF4D4;
extern s8 D_800DF4D8;
extern s8 D_800DF4DC;
extern s8 D_800DF4E0;
extern s8 D_800DF4E4[4];
extern s8 D_800DF4EC;
extern s32 gIsInTwoPlayerAdventure;
extern s32 gSaveFileIndex;

extern u8 D_800DF4A4;
extern u8 D_800DF4A8;
extern u8 D_800DF4AC;

/* Size: 0x20 bytes */
typedef struct unk800DF510 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s8  unk1A;
    s8  unk1B;
    s8  unk1C;
    s8  unk1D;
    u8  pad1E[2];
} unk800DF510;

extern unk800DF510 D_800DF510[18];
extern unk800DF510 *D_800DF75C;
extern s32 D_800DF764;

extern s16 *D_800DF750[32]; // unknown number of entries
extern s16 D_800DF754;
extern s16 D_800DF758;
extern s32 D_800DF760;
extern s16 D_800DF7C4[11];
extern s32 D_800DF774;
extern s32 D_800DF77C;
extern s32 D_800DF794;
extern s32 D_800DF798;
extern s32 D_800DF79C;
extern s32 D_800DF7A0;
extern char *D_800DFA10[7];
extern s32 D_800DFA2C;

typedef struct unk800DFA3C {
    u8 pad0[0x32];
    u16 unk32;
    u8 pad34[0x38];
    u32* unk6C;
} unk800DFA3C;

extern unk800DFA3C D_800DFA3C;

extern s32 D_800DFAC0;
extern s32 D_800DFAC4;
extern s16 D_800DFA38;
extern u32* D_800DFC10;
extern u32* D_800DFC20;
extern u32* D_800DFC30;
extern u32* D_800DFC40;
extern u32* D_800DFC50;
extern u32* D_800DFC60;
extern s16 D_800DFC78[24];
extern u32* D_800DFCAC;
extern s32 D_800DFD94;
extern u8 D_800DFDB4[10][2];
extern s32 D_800DFDC8;
extern s32 D_800DFFD0;
extern s32 D_800DFFD4;
extern s32 D_800E0398;
extern s32 D_800E03A4;
extern s32 D_800E0410;
extern s32 D_800E0414;
extern u32* D_800E041C;
extern u32* D_800E042C;
extern u32* D_800E043C;
extern u32* D_800E044C;

/* Size: 0x18 Bytes */
typedef struct unk800E045C {
    u32* unk0;
    s32 pad4;
    u32* unk8;
    s32 padC;
    s32 pad10;
    s32 pad14;
} unk800E045C;

extern unk800E045C D_800E045C;

extern unk800E045C D_800E0474;
extern unk800E045C D_800E048C;
extern s16 D_800E0710[30];
extern s16 D_800E07C4[30];
extern s32 D_800E0970;
extern s32 D_800E0984;
extern s32 D_800E0988;
extern s32 D_800E0A24;
extern s32 D_800E0A40;
extern u32* D_800E0A50;
extern u32* D_800E0A60;
extern u32* D_800E0A70;
extern u32* D_800E0A90;
extern u32* D_800E0A80;
extern u32* D_800E0AA0;
extern u32* D_800E0AB0;
extern u32* D_800E0AC0;
extern u32* D_800E0AD0;
extern u32* D_800E0AE0;
extern u8 D_800E0F6C[0x20]; // "ABCDEFGHIJKLMNOPQRSTYVWXYZ.?    " = Valid chars for name input.
extern s32 D_800E0F90;
extern s32 D_800E0F94;
extern s32 D_800E0F98;
extern s32 D_800E0F9C;
extern s32 D_800E0FA0;
extern s32 D_800E0FB4;
extern s32 D_800E0FE4; // Number of racers in trophy race? (1 to 8)
extern s32 D_800E0FEC; // Trophy race round? (0 to 3)
extern s32 gTrophyRaceWorldId;
extern s32 D_800E1024;
extern MenuElement D_800E1048;
extern MenuElement D_800E1088[8][3]; // 8 Racers with 3 MenuElement structs.
extern s32 D_800E1708;
extern s16 D_800E1768[10];
extern s32 D_800E17D8;
extern s16 D_800E17F0[8]; // Unknown number of entries
extern u16 D_800E18F8;
extern char *D_800E1938[107]; // Credits text look-up table
extern char *D_800E1AE4[5]; // Credits text look-up table
extern s32 D_800E1AF8[28];
extern s32 D_800E1B4C; // boolean, set to 1 if viewing credits from "WHODIDTHIS" cheat
extern s32 *D_800E1DA4[2];
extern s32 *D_800E1DAC[2];
extern s32 D_800E1DB4;
extern s32 D_800E1DB8;
extern s32 D_800E1DBC;
extern s8 D_800E1E28;
extern s32 D_800E8230;
extern f32 D_800E8414;

extern Gfx *D_801263A0;
extern s32 D_801263A8;
extern s32 D_801263AC;
extern s8 D_801263B4;
extern s32 D_801263BC;
extern s32 D_801263C4;
extern s8 D_801263D4[4]; // Array of bools
extern s8 D_801263DC[4];
extern s32 D_801263D8;
extern s32 D_801263E0;
extern s8 players_character_array[8];
extern s8 D_801263F0[8];
extern u8 D_80126418[8];
extern u8 D_80126420[8];
extern s64 D_80126448;
extern f32 D_80126450;
extern u8 D_80126454[4];
extern u8 D_80126458[4];
extern s8 D_8012645C[4];
extern s8 D_80126464[4];
extern u8 D_80126468[4];
extern u8 D_8012646C[4];
extern s32 D_80126470;
extern s32 D_80126484;
extern s32 D_80126488;
extern s8 D_801264D8;
extern s8 D_801264E2;
extern s8 D_80126504;
extern s8 D_8012650E;
extern s8 D_80126516;
extern Settings *D_80126530[3];
extern s32 D_80126548;
extern u32* D_80126550[1]; // lookup table? Unknown number of entries.
extern u8 D_80126750[1]; // unknown number of entries
extern s32 D_801267D0;
extern s8* D_801267EC;
extern s32 D_80126804;
extern s32 D_80126824;
extern s32 D_8012683C;
extern s32 D_80126840;
extern s32 D_80126844;
extern s32 D_8012684C;
extern s32 D_80126854;
extern s32 D_80126858;
extern s32 D_8012685C;
extern s32 D_80126860;
extern s8 p1_vehicle[4]; // Unknown number of entries.
extern s32 D_801269C8;
extern s32 D_801269CC;
extern u32* D_801269E0;
extern s32 D_801269FC;
extern s32 D_80126A00;
extern s32 D_80126A04;
extern s32 D_80126A08;
extern s32 D_80126A0C;
extern s32 D_80126A10;
extern s32 D_80126A14;
extern s32 D_80126A18;
extern s32 D_80126A1C;
extern s32 D_80126A20[8]; // Unknown number of entries.
extern s8 D_80126A60[2]; 
extern s32 D_80126A64;
extern s32 D_80126A68;
extern s32 D_80126A6C;
extern s32 D_80126A94;
extern s32* D_80126AA0[16];
extern s32 D_80126BB4;
extern s32 D_80126BB8;
extern s32 D_80126BBC;
extern s32 D_80126BC4;
extern s32 D_80126BC8;
extern s32 D_80126BCC;
extern s32 D_80126BD0;
extern s32 D_80126BD4;
extern s32 D_80126BD8;
extern f32 D_80126BDC;
extern s32 D_80126BE0;
extern f32 D_80126BEC;
extern s32 D_80126BE4;
extern s32 D_80126BF0[3];
extern s32 D_80126C10; 
extern s32 D_80126C14;
extern s32 *D_80126C2C;
extern u16 *D_80126C30[30]; // Cheat table.
extern s32 D_80126C34;
extern s32 D_80126C3C;
extern u16 D_80126C40;
extern u16 D_80126C42;
extern s16 D_80126C46;
extern u16 D_80126C44;
extern s32 D_80126C48;
extern s16 D_80126C4C;
extern u8  D_80126C58;
extern f32 D_80126C50;
extern s32 *D_80126C6C;
extern s32 D_80126C70;
extern s32 D_80126C74;
extern s32 D_80126C78;
extern s32 D_80126CC0;

Settings *get_settings(void);
void func_8009C4A8(s16 *arg0);
void func_8009C674(s16 *arg0);
void func_8008E4B0(void);
s8* func_8001E29C(s32 arg0);
void func_80001D04(s32, s32*);
void func_800660EC(f32 arg0);
void func_8009C508(s32 arg0);
void *func_80070C9C(s32, u32);
void func_800C4170(s32 arg0);
void func_80000B34(s32 arg0);

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8007F900.s")

void func_8007FF88(void) {
    if (D_800E1DAC[0] != NULL) {
        func_80071140(D_800E1DAC[0]);
        D_800E1DAC[0] = NULL;
    }
    D_800E1DAC[1] = NULL;
    D_80126C2C = NULL;
    D_800E1DA4[0] = NULL;
    D_800E1DA4[1] = NULL;
    D_800E1DB8 = 0;
    D_800E1DBC = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8007FFEC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80080580.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80080BC8.s")

void func_80080E6C(void) {
    D_800E1DB8 = 0;
    D_800E1DB4 = (s32) (1 - D_800E1DB4);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80080E90.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80081218.s")

void func_800813C0(void) {
    D_800DF458 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLoop.s")

void func_80081800(s32 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 phi_s6;
    s32 phi_s5;
    s32 phi_s3;
    s32 sp44;
    s32 sp40;

    D_800DF4A4 = arg3;
    D_800DF4A8 = arg4;
    D_800DF4AC = arg5;
    if (arg6 == 0) {
        D_800DF75C[0].unk10 = arg2;
        D_800DF75C[1].unk10 = arg2 - 2;
        phi_s3 = 0;
        phi_s5 = 1;
        arg1 -= 0x27;
        phi_s6 = 0xC;
        sp44 = 0xB;
        sp40 = 0xA;
    } else {
        D_800DF75C[2].unk10 = arg2;
        D_800DF75C[3].unk10 = arg2 - 1;
        phi_s3 = 2;
        phi_s5 = 3;
        arg1 -= 0x1C;
        phi_s6 = 9;
        sp44 = 9;
        sp40 = 5;
    }
    func_80059790(arg0, &sp5C, &sp58, &sp54);
    func_80068508(1);
    func_8007BF1C(0);
    D_800DF75C[phi_s3].unk18 = sp5C / 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += phi_s6;
    D_800DF75C[phi_s3].unk18 = sp5C % 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += sp44;
    D_800DF75C[phi_s5].unkC = arg1;
    func_8009CA60(phi_s5);
    arg1 += sp40;
    D_800DF75C[phi_s3].unk18 = sp58 / 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += phi_s6;
    D_800DF75C[phi_s3].unk18 = sp58 % 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += sp44;
    D_800DF75C[phi_s5].unkC = arg1;
    func_8009CA60(phi_s5);
    arg1 += sp40;
    D_800DF75C[phi_s3].unk18 = sp54 / 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += phi_s6;
    D_800DF75C[phi_s3].unk18 = sp54 % 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    func_80068508(0);
    func_8007BF1C(1);
    D_800DF4A4 = (u8)0xFF;
    D_800DF4A8 = (u8)0xFF;
    D_800DF4AC = (u8)0xFF;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80081C04.s")

void func_80081E54(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    D_800DF798 = arg0;
    D_800DF794 = 0;
    D_80126858 = arg1 * 60.0f;
    D_8012685C = arg2 * 60.0f;
    D_80126860 = arg3 * 60.0f;
    D_80126854 = 0;
    D_800DF79C = arg4;
    D_800DF7A0 = arg5;
    if (D_80126858 > 0) {
        func_80001D04(0x16, NULL);
    }
}


GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80081F4C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/DrawMenuText.s")

void func_800828B8(void) {
    s32 i;
    s32 j;
    s32 num;
    Settings *settings;

    settings = get_settings();
    func_8006B224(&num, &j);
    
    for(i = 0; i < num; i++) {
        settings->courseFlagsPtr[i] = 0;
        for(j = 0; j < 3; j++) {
            settings->courseFlagsPtr[i] |= D_80126530[j]->courseFlagsPtr[i];
        }
    }
    
    settings->trophies = 0;
    settings->keys = 0;
    settings->bosses = 0;
    settings->cutsceneFlags = 0;
    for(i = 0; i < 3; i++) {
        settings->trophies |= D_80126530[i]->trophies;
        settings->keys |= D_80126530[i]->keys;
        settings->bosses |= D_80126530[i]->bosses;
        settings->cutsceneFlags |= D_80126530[i]->cutsceneFlags;
    }
}

void func_800829F8(s32 arg0, s32 arg1) {
    s32 temp;

    D_800DF46C += arg1;
    
    if (D_800DF46C & 0x10) {
        func_8007F900(func_8009EB20());
        func_800C42EC(0);
        func_800C4384(0xFF, 0xFF, 0xFF, 0, 0xFF);
        func_800C43CC(0, 0, 0, 0);
        temp = 0xD0;
        if (osTvType == 0) {
            temp = 0xEA;
        }
        func_800C4440(arg0, -0x8000, temp, D_800DF4A0->unk25C, 0xC);
    }
}

void menu_logos_screen_init(void) {
    D_800DF47C = 0;
    D_80126450 = 16.0f;
    func_80077B5C(0, 0, 0);
    if (osTvType == 0) {
        func_80066940(0, 0, 0x26, 0x140, 0xE0);
        func_80066AA8(0, 0x8000, 0x8000, 0x140, 0x11C);
    } else {
        func_80066940(0, 0, 0x28, 0x140, 0xC4);
        func_80066AA8(0, 0x8000, 0x8000, 0x140, 0xF0);
    }
    func_80066610();
    func_80066818(0, 1);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLogoScreenLoop.s")

void set_magic_code_flags(s32 flags);

void func_80082FAC(void) {
    if (D_80126448 & 2) {
        set_magic_code_flags(2);
    }
    if ((D_80126448 & 0xFFFFF0) == 0xFFFFF0) {
        set_magic_code_flags(1);
    }
    if (D_80126448 & 1) {
        gIsInAdventureTwo = 1;
    } else {
        gIsInAdventureTwo = 0;
    }
    if ((D_80126448 & 0x2000000) == 0) {
        func_800C2AF4(0);
    }
    func_8007F900(func_8009EB20());
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80083098.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTitleScreenInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008377C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTitleScreenLoop.s")

void func_80084118(void) {
    func_8009C4A8((s16*)D_800DF7C4);
    func_80000BE0(0x10);
    func_800660D0();
    func_800C422C(2);
    func_80000890(1);
}

void menu_options_init(void) {
    D_801263BC = 0;
    D_800DF47C = 0;
    func_800C01D8(&D_800DF77C);
    func_800C4170(2);
    func_800C42EC(2);
    func_80000BE0(0x18);
    func_80000B34(0x18);
    func_80000B18();
}

void func_800841B8(s32 arg0) {
    s32 phi_s1;
    s32 phi_a3;
    s32 phi_s2;

    func_800C42EC(2);
    func_800C43CC(0, 0, 0, 0);
    func_800C4384(0, 0, 0, 0xFF, 0x80);
    func_800C4440(&D_801263A0, 0xA1, 0x23, D_800DF4A0->unk90, 0xC);
    func_800C4384(0xFF, 0xFF, 0xFF, 0, 0xFF);
    func_800C4440(&D_801263A0, 0xA0, 0x20, D_800DF4A0->unk90, 0xC);
    
    phi_s1 = 0;
    phi_s2 = 0x4C;
    
    func_800C42EC(0);
    
    while(D_800DFA10[phi_s1] != NULL) {
        if (phi_s1 == D_800DF460) {
            phi_a3 = D_801263BC * 8;
            if (D_801263BC >= 0x20) {
                phi_a3 = 0x1FF - phi_a3;
            }
        } else {
            phi_a3 = 0;
        }
        func_800C4384(0xFF, 0xFF, 0xFF, phi_a3, 0xFF);
        func_800C4440(&D_801263A0, -0x8000, phi_s2, D_800DFA10[phi_s1], 0xC);
        
        phi_s1++;
        phi_s2 += 0x1C;
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuOptionsLoop.s")
#else
    
extern s32 D_800DFA14;
extern s32 D_8012644C;

void func_80084734(void);
void set_language(s32 language);

s32 MenuOptionsLoop(s32 arg0) {
    s32 buttonsPressed;
    s32 analogX;
    s32 analogY;
    
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    
    if (D_800DF47C != 0) {
        if (D_800DF47C > 0) {
           D_800DF47C += arg0;
        } else {
            D_800DF47C -= arg0;
        }
    }
    
    if (D_800DF47C >= -0x13 && D_800DF47C < 0x23) {
        func_800841B8(arg0);
    }
    
    buttonsPressed = 0;
    analogX = 0;
    analogY = 0;
    if (D_801263C4 == 0 && D_800DF47C == 0) {
        // Get input from all 4 controllers.
        s32 i;
        for (i = 0; i < 4; i++) {
            analogY += D_80126464[i]; // Y axis (-1 = down, 1 = up) for controller
            analogX += D_8012645C[i]; // X axis (-1 = left, 1 = right) for controller
            buttonsPressed |= func_8006A554(i); // Button presses for controller
        }
    }
    
    if ((buttonsPressed & 0x4000) || ((buttonsPressed & 0x9000) && D_800DF460 == 5)) {
        // Leave the option menu
        func_80000C98(-0x80, D_800DF460, analogX);
        D_800DF47C = -1;
        func_800C01D8(&D_800DF774);
        func_80001D04(0x241, 0);
    } else if ((buttonsPressed & 0x9000) && D_800DF460 >= 2) {
        // Go to a sub-menu
        D_800DF47C = 0x1F;
        func_80001D04(0xEF, 0);
    } else if (D_800DF460 == 0 && analogX != 0) {
        // Change language
        s32 temp_v0 = func_8009EB20();
        if ((temp_v0 >> 0x1F) == 0 && temp_v0 == 0) {
            set_language(2); // Sets language to french
        } else {
            set_language(0); // Sets language to english
        }
        func_80001D04(0xEB, 0);
    } else if (D_800DF460 == 1 && analogX != 0) {
        // Enable/Disable subtitles.
        if (D_8012644C & 0x2000000) {
            func_80001D04(0xEB, 0);
            func_8009EABC(0, 0x2000000);
            func_800C2AF4(0);
            D_800DFA14 = D_800DF4A0->unk2DC;
        } else {
            func_80001D04(0xEB, 0);
            func_8009EA78(0, 0x2000000);
            func_800C2AF4(1);
            D_800DFA14 = D_800DF4A0->unk2D8;
        }
    } else {
        // Move up & down the list
        if (analogY < 0) {
            // Scroll down the list.
            D_800DF460++;
            if (D_800DF460 >= 6) {
                D_800DF460 = 5;
            }
            func_80001D04(0xEB, 0);
        }
        if (analogY > 0) {
            // Scroll up the list.
            D_800DF460--;
            if (D_800DF460 < 0) {
                D_800DF460 = 0;
            }
            func_80001D04(0xEB, 0);
        }
    }
    
    if (D_800DF47C >= 0x1F) {
        // Change screen to a sub-menu
        switch(D_800DF460) {
            case 2:
                func_80084734();
                MenuInit(AUDIO_OPTIONS);
                return 0;
            case 3:
                func_80084734();
                MenuInit(SAVE_OPTIONS);
                return 0;
            default:
                func_80084734();
                MenuInit(MAGIC_CODES);
                return 0;
        }
    }
    if (D_800DF47C < -0x1E) {
        // Change screen back to the title screen.
        func_80000B28();
        func_80084734();
        MenuInit(TITLE_SCREEN);
        return 0;
    }
    D_801263C4 = 0;
    return 0;
}
#endif


void func_80084734(void) {
    func_800C422C(2);
}

void func_8009C8A4(s16 *arg0);

void MenuAudioOptionsInit(void) {
    D_80126C46 = 0;
    D_801263BC = 0;
    D_800DF47C = 0;
    D_801269FC = 0;
    D_801263D8 = -1;
    func_8009C674((s16*)&D_800DFA2C);
    func_8009C8A4(&D_800DFA38);
    func_8008E4B0();
    func_800C01D8(&D_800DF77C);
    func_8007FFEC(2);
    D_800DFAC4 = musicGetVolSliderPercentage();
    D_800DFAC0 = sfxGetVolumeSlider();
    if (gActiveMagicCodes & 0x40) { // Check if "JUKEBOX" cheat is active
        D_800DFA3C.unk6C = D_801269E0;
        D_800DFA3C.unk32 = 0xD4;
        func_80000BE0(0x20);
        D_801263E0 = 5;
    } else {
        D_800DFA3C.unk6C = NULL;
        D_800DFA3C.unk32 = 0xC0;
        D_801263E0 = 4;
    }
    func_800C4170(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80084854.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuAudioOptionsLoop.s")
#else

extern s32 D_800DFABC;
extern s32 D_800DFAC8;

void func_800851FC(void);

s32 MenuAudioOptionsLoop(s32 arg0) {
    s32 sp40;
    s32 sp30;
    s32 phi_a2;
    s32 phi_a3;
    s32 phi_t0;
    s32 phi_s0;

    sp30 = 0;
    D_801263BC = (s32) ((D_801263BC + arg0) & 0x3F);
    if (D_800DF47C != 0) {
        if (D_800DF47C > 0) {
            D_800DF47C += arg0;
        } else {
            D_800DF47C -= arg0;
        }
    }
    if (D_800DF47C >= -0x13 && D_800DF47C < 0x14) {
        func_80084854();
    }
    if (D_801263C4 == 0 && D_800DF47C == 0) {
        sp40 = 0;
        phi_a2 = 0;
        phi_a3 = 0;
        phi_t0 = 0;
        phi_s0 = 0;
        
        while(phi_s0 != 4) {
            sp40 |= func_8006A554(phi_s0);
            phi_a2 += func_8006A59C(phi_s0);
            phi_a3 += D_80126464[phi_s0];
            phi_t0 += D_8012645C[phi_s0];
            phi_s0++;
        }
        
        if (phi_a2 < 0) {
            phi_a2 += 0x18;
            if (phi_a2 > 0) {
                phi_a2 = 0;
            }
        } else {
            phi_a2 -= 0x18;
            if (phi_a2 < 0) {
                phi_a2 = 0;
            }
        }
        
        if (((sp40 & 0x9000) && (D_801263E0 == D_80126C46 + 1)) || (sp40 & 0x4000)) {
            D_800DF47C = -1;
            func_800C01D8(&D_800DF774);
            if (D_801263D8 >= 0) {
                func_80000C98(-0x80);
            }
            sp30 = 3;
        } else if (phi_a3 < 0 && D_80126C46 < D_801263E0 - 1) {
            D_80126C46++;
            sp30 = 1;
        } else if (phi_a3 > 0 && D_80126C46 > 0) {
            D_80126C46--;
            sp30 = 1;
        } else if (D_80126C46 == 0 && phi_t0 != 0) {
            if (phi_t0 < 0) {
                D_800DFAC8--;
            } else {
                D_800DFAC8++;
            }
            if (D_800DFAC8 < 0) {
                D_800DFAC8 = 2;
            }
            if (D_800DFAC8 > 2) {
                D_800DFAC8 = 0;
            }
            func_80065BD0(D_800DFAC8);
            sp30 = 1;
        } else if ((phi_a2 >> 2) != 0) {
            if(D_80126C46 == 2) {
                D_800DFAC0 += (phi_a2 >> 2);
                if (D_800DFAC0 < 0) {
                    D_800DFAC0 = 0;
                } else if (D_800DFAC0 >= 0x101) {
                    D_800DFAC0 = 0x100;
                }
                sfxSetVolumeSlider(D_800DFAC0);
            } else if(D_80126C46 == 1) {
                D_800DFAC4 += (phi_a2 >> 2);
                if (D_800DFAC4 < 0) {
                    D_800DFAC4 = 0;
                } else {
                    if (D_800DFAC4 >= 0x101) {
                        D_800DFAC4 = 0x100;
                    }
                }
                func_80001A3C(D_800DFAC4);
                if (!musicIsPlaying()) {
                    if (D_801263D8 >= 0) {
                        func_80000B28();
                        func_80000B34((u8)D_800DFABC);
                    } else {
                        func_80000B28();
                        func_80000BE0(0x18);
                        func_80000B34(0x18);
                        func_80000B18();
                    }
                }
            }
        } else if (D_801263E0 >= 5 && D_80126C46 == 1) {
            if (phi_t0 < 0 && D_800DFABC > 0) {
                D_800DFABC--;
                sp30 = 1;
            } else if (phi_t0 > 0 && D_800DFABC < (ALSeqFile_80115CF8_GetSeqCount() - 1)) {
                D_800DFABC++;
                sp30 = 1;
            }
            if (sp40 & 0x9000) {
                func_80000B28();
                func_80000BE0(0x18);
                func_80000B34((u8)D_800DFABC);
                D_801263D8 = D_800DFABC;
            }
        }
        
        if (D_80126C46 == 1 && D_801269FC == 0) {
            func_80001D04(0x19B, &D_801269FC);
        } else if (D_801269FC != 0) {
            func_8000488C(D_801269FC);
        }
        
        if (sp30 == 3) {
            func_80001D04(0x241, 0);
        } else if (sp30 == 2) {
            func_80001D04(0xEF, 0);
        } else if (sp30 == 1) {
            func_80001D04(0xEB, 0);
        }
    }
    if (D_800DF47C < -0x1E) {
        func_800851FC();
        MenuInit(0xC);
        return 0;
    }
    D_801263C4 = 0;
    return 0;
}

#endif

void func_800851FC(void) {
    if (D_801269FC != 0) {
        func_8000488C(D_801269FC);
    }
    if (D_801263D8 >= 0) {
        func_80000BE0(0x18);
        func_80000B34(0x18);
        func_80000C98(0x100);
        func_80000B18();
    }
    func_8009C4A8((s16*)&D_800DFA2C);
    func_800C422C(2);
}

void menu_save_options_init(void) {
    D_80126A6C = 1;
    D_80126A10 = 0;
    D_80126A18 = 1;
    D_80126A1C = 1;
    D_80126C46 = 0;
    D_801263BC = 0;
    D_800DF47C = 0;
    D_801263E0 = 1;
    D_801263D8 = 0;
    D_80126A64 = (s32)func_80070C9C(0x800, 0xFFFFFFFF);
    D_80126A0C = (s32)func_80070C9C(0xA00, 0xFFFFFFFF);
    D_80126A04 = (s32)(D_80126A0C + 0x500);
    D_80126A08 = 0;
    D_80126BD4 = 0;
    D_80126BDC = 0.0f;
    D_80126A00 = 0;
    D_80126BE4 = 0;
    D_80126BEC = 0.0f;
    func_8009C674((s16*)&D_800DFC78);
    func_8009C8A4((s16*)&D_800DFCAC);
    func_8007FFEC(0xA);
    func_800C4170(2);
    D_800DFC10 = D_80126550[71];
    D_800DFC20 = D_80126550[72];
    D_800DFC30 = D_80126550[75];
    D_800DFC40 = D_80126550[74];
    D_800DFC50 = D_80126550[73];
    D_800DFC60 = D_80126550[70];
    func_8008E4B0();
    func_8006EBA8();
    func_800C01D8(&D_800DF77C);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800853D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80085B9C.s")

/* Size: 0x10 Bytes */
typedef struct unk800860A8 {
    s8 unk0;
    u8 pad1[0x5];
    s8 unk6;
    u8 pad7[0x5];
    s32 unkC;
} unk800860A8;

s32 func_800860A8(s32 arg0, s32 *arg1, unk800860A8 *arg2, s32 *arg3, s32 arg4) {
    s32 temp_v1;
    s32 phi_t0;

    phi_t0 = 0;
    if (*arg1 != 0) {
        phi_t0 = func_80076194(arg0, &arg2[*arg3].unkC, &D_80126A20[arg0]);
        if (phi_t0 == 0) {
            if ((arg2[*arg3].unkC >= arg4) && (D_80126A20[arg0] > 0)) {
                arg2[*arg3].unk0 = 8;
                arg2[*arg3].unk6 = arg0;
                (*arg3)++;
            }
        } else {
            if((*arg1 < 0) && ((phi_t0 & 0xFF) == 7)) {
                *arg1 = 0;
                phi_t0 = 0;
            } else {
                temp_v1 = phi_t0 & 0xFF;
                if (temp_v1 != 3 && temp_v1 != 2 && temp_v1 != 9) {
                    phi_t0 = 0;
                }
            }
        }
    }
    
    return phi_t0;
}

/* Size: 0x10 bytes */
typedef struct unk800861C8 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3;
    u16 pad4;
    s8  unk6;
    s8  pad7;
    u32 pad8;
    u32 unkC;
} unk800861C8;

void func_800861C8(unk800861C8* arg0, s32 *arg1) {
    s32 i;
    for(i = 0; i < 3; i++) {
        if (D_80126530[i]->newGame != 0) {
            arg0[*arg1].unk0 = 1;
            arg0[*arg1].unk1 = 0;
            arg0[*arg1].unk2 = 0;
            arg0[*arg1].unk6 = i;
            arg0[*arg1].unkC = func_80073C4C();
            (*arg1)++;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800862C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800867D4.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80086A48.s")
#else
void func_80086A48(s32 arg0) {
    f32 temp, temp2, temp3;
    temp = D_80126BD4;
    temp2 = D_80126BE4;
    while (arg0 > 0) {
        temp3 = D_800E8414;
        if (D_80126A08 > 0) {
            D_80126BDC = D_80126BDC + temp3 * (temp - D_80126BDC);
        }
        if (D_801263E0 > 0 && D_80126A00 > 0) {
            D_80126BEC = D_80126BEC + temp3 * (temp2 - D_80126BEC);
        }
        arg0--;
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80086AFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800871D8.s")


s32 func_800874D0(s32 arg0, s32 arg1) {
    s32 sp1C;

    sp1C = 0;
    if (arg0 & 0x4000) {
        D_801263E0 = 0;
        if (D_80126A10 != D_80126A14) {
            func_800871D8(8);
        } else {
            func_80001D04(0x241, NULL);
            sp1C = -1;
        }
    } else {
        if (arg0 & 0x9000) {
            func_80001D04(0xEF, NULL);
            D_801263E0 = 4;
        } else {
            if ((arg1 < 0) && (D_80126BD4 > 0)) {
                func_80001D04(0xEB, NULL);
                D_80126BD4 = (s32) (D_80126BD4 - 1);
            } else if ((arg1 > 0) && (D_80126BD4 < (D_80126A08 - 1))) {
                func_80001D04(0xEB, NULL);
                D_80126BD4 = (s32) (D_80126BD4 + 1);
            }
        }
    }
    return sp1C;
}

s32 func_800875E4(s32 arg0, s32 arg1) {
    if (arg0 & 0x4000) {
        func_80001D04(0x241, NULL);
        D_801263E0 = 3;
    } else {
        if (arg0 & 0x9000) {
            func_80001D04(0xEF, NULL);
            D_801263E0 = 6;
        } else {
            if ((arg1 < 0) && (D_80126BE4 > 0)) {
                func_80001D04(0xEB, NULL);
                D_80126BE4 = (s32) (D_80126BE4 - 1);
            } else if ((arg1 > 0) && (D_80126BE4 < D_80126A00 - 1)) {
                func_80001D04(0xEB, NULL);
                D_80126BE4 = (s32) (D_80126BE4 + 1);
            }
        }
    }
    return 0;
}


s32 func_800876CC(s32 arg0, s32 arg1) {
    if (arg0 & 0x4000) {
        func_80001D04(0x241, NULL);
        D_801263E0 = 5;
    } else if (arg0 & 0x9000) {
        func_80001D04(0xEF, NULL);
        D_801263E0 = 7;
        D_801263D8 = 0;
    }
    
    return 0;
}


GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80087734.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuSaveOptionsLoop.s")

void func_80087EB8(void) {
    func_800C422C(2);
    func_8007FF88();
    func_8009C4A8(D_800DFC78);
    func_800C5494(7);
    func_80071140(D_80126A0C);
    func_80071140(D_80126A64);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80087F14.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008832C.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuBootInit.s")
#else
// Probably not unqiue to the boot menu.
typedef struct MenuBootDrawTexture {
u32* texture; // Pointer to texture to draw. TODO: Make structure for texture header.
s16 xOffset; // Offset from the center of the screen.
s16 yOffset; // Offset from the center of the screen.
} MenuBootDrawTexture;

extern s32 D_800DF77C;
extern s16 D_800DF7C4[11];
static MenuBootDrawTexture D_800DF7DC[11];
extern u32* D_80126550[]; // texture lookup table?
extern s32 D_80126C18;
extern s32 D_80126C20;

// Almost matches, except for an extra `lui` instruction when the loop unrolls.
void menu_boot_init(void) {
    s32 i;

    func_800C01D8(&D_800DF77C);
    func_80077B34(0, 0, 0);
    func_8009C674(&D_800DF7C4);
    
    // Sets up the 11 texture pointers for the "Diddy Kong Racing" logo.
    for(i = 0; i < 11; i++) {
        D_800DF7DC[i].texture = D_80126550[D_800DF7C4[i]];
    }
    
    // Reset variables for menu_boot_loop()
    D_80126C20 = 0; // D_80126C20 is the current state of the boot screen. Either 0, 1, or 2.
    D_80126C18 = 0; // D_80126C18 is a timer for the boot screen, counts up to 0x8C frames.
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuBootLoop.s")

void func_800887C4(void) {
    func_8009C4A8((s16*)D_800DF7C4);
}

void func_800887E8(void) {
    s32 i;

    // Starting point
    D_80126AA0[0] = func_80070C9C(0x200, 0xFFFFFFFF);
    
    // Fills in the table.
    for(i = 1; i < 16; i++) {
        D_80126AA0[i] = (s32*)(((u32)D_80126AA0[0]) + (i * 0x20));
    }
    
    for(i = 0; i < 1; i++) {
        D_80126A60[i] = 0;
    }
    
    D_80126C10 = 0;
    D_801263E0 = 0;
    D_801263BC = 0;
    D_80126A68 = -1;
    func_8007F900(func_8009EB20());
    if (func_80087F14(&D_80126A68, 0) == 0) {
        D_800DF47C = 0;
    } else if (func_8008832C() == 0) {
        D_800DF47C = 0x14;
    }
    if (D_80126BC8 == 0 && D_800DFD94 == 0) {
        D_800DF47C = 0x14;
    }
    D_800DF460 = 0;
    D_801263D8 = 0;
    func_8009C6D4(0x3F);
    func_8008E4B0();
    if (osTvType == 0) {
        D_80126BB4 = 8;
    } else {
        D_80126BB4 = 7;
    }
    func_800C4170(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80088938.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800890AC.s")

void func_800895A4(void) {
    func_8009C508(0x3F);
    func_80071140(D_80126AA0[0]);
    func_800C422C(2);
}

void menu_magic_codes_init(void) {
    D_80126C40 = 0;
    D_80126C42 = 0;
    D_80126C46 = 0;
    D_80126C44 = 0;
    D_80126470 = 0;
    D_80126C4C = -1;
    D_80126C58 = 0;
    D_801263BC = 0;
    D_800DF47C = 0;
    D_801263D8 = 0;
    D_801263E0 = 0;
    func_800C01D8(&D_800DF77C);
    func_800C4EDC(7, 0x32, 0x32, 0x10E, 0x84);
    func_800C4FBC(7, 0, 0, 0, 0x80);
    func_800C5494(7);
    func_800C4170(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800896A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuMagicCodesLoop.s")

void func_8008A4C8(void) {
    func_800C422C(2);
}

void menu_magic_codes_list_init(void) {
    D_801263BC = 0;
    D_800DF47C = 0;
    D_801263E0 = 0;
    D_80126C46 = (u16)0;
    func_800C4170(2);
    func_8009C6D4(0x3F);
    func_8008E4B0();
    func_800C01D8(&D_800DF77C);
    if (osTvType == 0) {
        D_80126C70 = 0xB;
    } else {
        D_80126C70 = 0xA;
    }
}


GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008A56C.s")

void func_8008A8F8(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 & arg1) {
        if (arg0 & gActiveMagicCodes) {
            gActiveMagicCodes &= ~arg2;
        }
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuMagicCodesListLoop.s")
#else

extern s16 D_80126C80[0x1E]; // Array of shorts of the unlocked cheat's bit ids.
void func_8008AD1C(void);
void func_8008A56C(void);
s32 func_8006A554(s32 arg0);

s32 MenuMagicCodesListLoop(s32 arg0) {
    s32 temp_t0;
    s32 phi_a2;
    s32 phi_s0;
    s32 sp48;
    s32 phi_s1;
    s32 phi_s2;
    s32 phi_a3_2;
    s32 phi_v0_2;
    s32 phi_s3;
    s8 *temp, *temp2;

    sp48 = 0;
    if (D_800DF47C != 0) {
        if (D_800DF47C > 0) {
            D_800DF47C += arg0;
        } else {
            D_800DF47C -= arg0;
        }
    }
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    if (D_800DF47C >= -0x13 && D_800DF47C < 0x14) {
        func_8008A56C();
    }
    
    phi_s3 = 0;
    phi_a2 = 0;
    phi_s2 = 0;
    if (D_801263C4 == 0 && D_800DF47C == 0) {
        phi_s0 = 0; 
        temp = (s8*)&D_80126464;
        temp2 = (s8*)&D_8012645C;
        while(phi_s0 < 4) {
            phi_s3 |= func_8006A554(phi_s0);
            phi_a2 += *temp;
            phi_s2 += *temp2;
            temp++;
            temp2++;
            phi_s0++;
        }
    }
    
    phi_s0 = 0;
    phi_s1 = 1;
    phi_a3_2 = 0;
    while(phi_s0 < 32) { // 32 is the max number of cheats.
        if (phi_s1 & gUnlockedMagicCodes) {
            D_80126C80[phi_a3_2] = phi_s0;
            phi_a3_2++;
        }
        phi_s1 <<= 1;
        phi_s0++;
    }
    
    if (((phi_a2 < 0) || (phi_a2 > 0)) && (phi_a3_2 != D_80126C46)) {
        func_80001D04(0xEF, NULL);
        phi_s1 = 1 << D_80126C80[D_80126C46];
        gActiveMagicCodes ^= phi_s1; // Toggle active cheats?
        func_8008A8F8(phi_s1, 0x10, 0x20);  // func_8008A8F8() = Clear flags?
        func_8008A8F8(phi_s1, 0x20, 0x10);
        func_8008A8F8(phi_s1, 0x1000, 0x6080);
        func_8008A8F8(phi_s1, 0x6080, 0x1000);
        func_8008A8F8(phi_s1, 0x800, 0x1F8000);
        func_8008A8F8(phi_s1, 0x1F8000, 0x800);
        func_8008A8F8(phi_s1, 0x8000, 0xF0000);
        func_8008A8F8(phi_s1, 0x10000, 0xE8000);
        func_8008A8F8(phi_s1, 0x20000, 0xD8000);
        func_8008A8F8(phi_s1, 0x40000, 0xB8000);
        func_8008A8F8(phi_s1, 0x80000, 0x78000);
    }
    
    phi_a2 = D_80126C46;
    
    if (phi_s2 < 0) {
        D_80126C46++;
        if (phi_a3_2 < D_80126C46) {
            D_80126C46 = phi_a3_2;
        }
    }
    if (phi_s2 > 0) {
        D_80126C46--;
        if ((s32) D_80126C46 < 0) {
            D_80126C46 = 0;
        }
    }
    
    if (D_80126C46 < D_801263E0) {
        D_801263E0 = D_80126C46;
    } else if (D_80126C46 >= (D_801263E0 + D_80126C70)) {
        D_801263E0 = (D_80126C46 - D_80126C70) + 1;
    }
    
    if (D_80126C46 != phi_a2) {
        func_80001D04(0xEB, NULL);
    }
    
    if ((phi_s3 & 0x9000) && (phi_a3_2 == D_80126C46)) {
        sp48 = -1;
    }
    if (phi_s3 & 0x4000) {
        sp48 = -1;
    }
    if (sp48 != 0) {
        D_800DF47C = sp48;
        func_800C01D8(&D_800DF774);
        func_80001D04(0x241, NULL);
    }
    if (D_800DF47C < -0x1E) {
        func_8008AD1C();
        MenuInit(0xA);
        return 0;
    }
    D_801263C4 = 0;
    return 0;
}
#endif

void func_8008AD1C(void) {
    func_8009C508(0x3F);
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008AD44.s")

void func_8008AEB4(s32 arg0, s32 *arg1) {
    switch(arg0) {
        default:
            D_800DFFD0 = 0;
            return;
        case 1:
        case 3:
            D_800DFFD0 = 1;
            return;
        case 2:
            D_800DFFD0 = 2;
            D_800DFFD4 = *arg1;
            return;
    }
}

void func_8008AF00(s32 arg0) {
    s32 i;
    
    D_800DF4BC = 1;
    
    for (i = 0; i < 8; i++) {
        players_character_array[i] = (i == arg0) ? 1 : -1;
    }
    
    for(i = 0; i < 4; i++) {
        D_801263D4[i] = (i == arg0) ? 1 : 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuCharacterSelectInit.s")

void func_8008B20C(s32 arg0) {
    s32 temp;
    if (D_800DF47C >= -0x16 && D_800DF47C < 0x17) {
        func_800C42EC(2);
        func_800C43CC(0, 0, 0, 0);
        func_800C4384(0, 0, 0, 0xFF, 0x80);
        func_800C4440(&D_801263A0, 0xA1, 0x23, D_800DF4A0->unk21C, 0xC);
        func_800C4384(0xFF, 0xFF, 0xFF, 0, 0xFF);
        func_800C4440(&D_801263A0, 0xA0, 0x20, D_800DF4A0->unk21C, 0xC);
        if (D_800DF480 == D_800DF4BC && D_800DF4BC > 0) {
            temp = 0xD0;
            if (osTvType == 0) {
                temp = 0xEA;
            }
            func_800C4440(&D_801263A0, 0xA0, temp, &D_800E8230, 0xC);
        }
        func_8007B3D0(&D_801263A0);
        func_800660EC(40.0f);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008B358.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008B4C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008B758.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008BB3C.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuCharacterSelectLoop.s")
#else
    
/* Size: 0xE bytes. */
typedef struct unk801263CC {
    u8 pad0[0xC];
    s16 unkC;
} unk801263CC;

extern unk801263CC *D_801263CC[8]; // unknown number of entries

void func_8008C128(void);

s32 MenuCharacterSelectLoop(s32 arg0) {
    s32 i;
    s32 phi_a0;
    s32 phi_t3;
    s8 temp[4];

    func_8008B20C(arg0);
    func_8008C168(arg0);
    func_8008E4EC();
    
    for(i = 0; i < 4; i++){
        if (1 == D_801263DC[i]) {
            D_801263DC[i] = 2;
        }
    }
    D_801263C4 = 0;
    if (D_800DF47C == 0) {
        // Issue: this loop unrolls weirdly.
        for (i = 0; i < 4; i++) {
            temp[i] = D_801263D4[i];
        }
        func_8008B358();
        if (D_800DF480 == D_800DF4BC) {
            func_8008B4C8();
        } else {
            func_8008B758(temp);
        }
        return 0; // This return needs to be here.
    } else if (D_800DF47C > 0) {
        D_800DF47C += arg0;
        if (D_800DF47C >= 0x1F) {
            phi_t3 = 0;
            if (D_800DFFD0 == 0) {
                phi_t3++;
                if ((gActiveMagicCodes << 7) < 0) {
                    phi_t3++;
                }
            }
            func_8008C128();
            
            // Regalloc issue: D_801263D4 and phi_a0 need to switch registers.
            phi_a0 = 0;
            for(i = 0; i < 4; i++) {
                if (D_801263D4[i]) {
                    D_801263F0[phi_a0] = (*D_801263CC)[players_character_array[i]].unkC;
                    phi_a0++;
                }
            }
            func_8008BB3C(phi_a0);
            func_8006A458(D_801263D4);
            
            D_800DF4B8 = 1;
            if (phi_t3 >= D_800DF4BC) {
                func_80000B18();
                func_8006E2E8(0x27, -1, 0);
                if (D_800DF4BC == 1 && D_800DF498 == 0) {
                    MenuInit(CAUTION_MESSAGE);
                } else {
                    MenuInit(GAME_SELECT);
                }
            } else {
                func_80000B28();
                func_800828B8();
                func_8006E5BC();
                MenuInit(TRACK_SELECT);
            }
        }
    } else if (D_800DF47C < 0) {
        D_800DF47C -= arg0;
        if (D_800DF47C < -0x1E) {
            func_80000B28();
            func_8008C128();
            D_800DF4BC = 1;
            MenuInit(TITLE_SCREEN);
        }
    }
    return 0;
}

#endif

void func_8008BFE8(s32 arg0, s8 *arg1, s32 arg2, u16 arg3, u16 arg4) {
    s32 someBool;
    s32 j;
    s32 i;

    j = 0;
    someBool = 1;
    while (someBool && j < arg2 && arg1[j] != -1) {
        someBool = 0;
        if ((func_8009C30C() & 0x400000) == 0) {
            i = 0;
            while(i < 4 && !someBool){
                if (i != arg0 && players_character_array[i] == arg1[j]) {
                    someBool = 1;
                }
                i++;
            }
            if (someBool) {
                j++;
            }
        }
    }
    if (!someBool) {
        players_character_array[arg0] = arg1[j];
        func_80001D04(arg3, NULL);
        return;
    }
    func_80001D04(arg4, NULL);
}

void func_8008C128(void) {
    func_8009C4A8((s16*)&D_800DFDC8);
    func_800710B0(0);
    func_800C422C(2);
    func_800710B0(2);
    D_800DFFD0 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008C168.s")

void menu_caution_init(void) {
    D_801263C4 = 0x3C;
    D_800DF47C = 0;
    func_800C4170(2);
    func_800C01D8(&D_800DF77C);
    D_800DF498 = 1;
}

extern MenuElement D_800DFFD8[13];

void func_8008C4E8(void);

void DrawMenuText(s32, MenuElement*, f32);

s32 menu_caution_loop(s32 arg0) {
    if (D_800DF47C != 0) {
        D_800DF47C += arg0;
    } else {
        if (D_801263C4 <= 0) {
            if (func_8006A554(0) & 0xD000) {
                func_80001D04(0xEF, NULL);
                D_800DF47C = 1;
                func_800C01D8(&D_800DF774);
            }
        }
    }
    if (D_800DF47C < 0x14) {
        DrawMenuText(1, D_800DFFD8, 1.0f);
    }
    if (D_800DF47C >= 0x1F) {
        func_8008C4E8();
        MenuInit(GAME_SELECT);
    }
    if (D_801263C4 > 0) {
        D_801263C4 = (s32) (D_801263C4 - arg0);
    }
    
    return 0;
}

void func_8008C4E8(void) {
    func_800C422C(2);
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuGameSelectInit.s")
#else

typedef struct MenuElementTest {
    MenuElement unk0;
    MenuElement unk20;
} MenuElementTest;

extern MenuElementTest *D_80126460;
extern MenuElementTest D_800E0198[4];
extern MenuElementTest D_800E0278[4];

void MenuGameSelectInit(void) {
    s32 i, j;

    D_800DF47C = 0;
    D_801263BC = 0;
    D_800DF460 = 0;
    D_801263E0 = 2;
    func_800C01D8(&D_800DF77C);
    func_8006EBA8();
    func_8001B790();
    D_801263D8 = 1;
    func_8009C6D4(0x43);
    func_8007FFEC(3);
    func_800C4170(2);
    func_80000B34(0x1A);
    
    for(i = 0; i < 10; i++) {
        if (i != D_801263B4) {
            func_80001114(D_800DFDB4[i][0]);
            func_80001114(D_800DFDB4[i][1]);
        }
    }
    
    func_80001114(6);
    func_80000B18();
    if (func_8009EC60()) {
        D_80126460 = (MenuElementTest *)D_800E0278;
        D_801263E0 = 2;
    } else {
        D_80126460 = (MenuElementTest *)D_800E0198;
        D_801263E0 = 1;
    }
    
    for(i = 0; D_801263E0 >= i; i++) {
        ((MenuElementTest*)(D_80126460 + i + 1))->unk0.source.texture = D_80126550[67];
    }
}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008C698.s")
#else
typedef struct unk80126460 {
    MenuElement textShadow;
    MenuElement text;
} unk80126460;

extern unk80126460 *D_80126460[4];

void func_8008C698(s32 arg0) {
    s32 fade;
    s32 i;
    s32 filterAlpha;

    if (D_800DF47C >= -21 && D_800DF47C < 22) {
        fade = D_801263BC * 8;
        fade = fade;
        if (fade >= 0x100) {
            fade = 0x1FF - fade;
        }
        func_80067F2C(&D_801263A0, &D_801263A8);
        
        for(i = 0; i <= D_801263E0; i++) {
            filterAlpha = 0;
            if (i == D_800DF460) {
                filterAlpha = fade;
            }
            ((unk80126460*)(*D_80126460 + i + 1))->text.filterAlpha = filterAlpha;
        }
        
        if (osTvType == 0) {
            D_800DF79C = 0xC;
            D_800DF7A0 = 0;
        } else {
            D_800DF79C = 0;
            D_800DF7A0 = 0;
        }
        
        DrawMenuText(1, (MenuElement*)*D_80126460, 1.0f);
        func_80080BC8(&D_801263A0);
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuFileSelectLoop.s")

void func_8008CACC(void) {
    func_800C422C(2);
    func_8007FF88();
    func_8009C508(0x43);
}

void menu_file_select_init(void) {
    s32 i;
    s32 sp38;
    s32 sp34;

    func_8006B224(&sp38, &sp34);
    func_8009C674((s16*)&D_800E0398);
    func_8009C8A4((s16*)&D_800E03A4);
    func_8007FFEC(6);
    func_8006EBA8();
    D_801263D8 = 1;
    gSaveFileIndex = 0;
    D_800DF47C = 0;
    D_801263E0 = 0;
    D_801263BC = 0;
    D_80126484 = 0;
    D_80126488 = 0;
    D_80126CC0 = 0;
    func_800C01D8(&D_800DF77C);
    func_800C4170(2);
    func_80000B34(0x1A);
    for(i = 0; i < 10; i++) {
        if (i != D_801263B4) {
            func_80001114(D_800DFDB4[i][0]);
            func_80001114(D_800DFDB4[i][1]);
        }
    }
    func_80001114(6);
    func_80000B18();
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008CC28.s")

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008CD74.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008D5F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008D8BC.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008DC7C.s")
#else
/* Size: 0x0C Bytes */
typedef struct unk801264A0 {
    u8 unk0;
    u8 unk1;
    u16 unk2;
    char name[4];
    u32 pad8;
} unk801264A0;

extern unk801264A0 D_801264A0[3]; // Filename structs?
extern s32 D_80126494;
extern s32 D_8012648C;

void func_8008DC7C(s32 arg0) {
    s32 temp_t6;
    s32 temp_a1;
    s32 phi_v1;
    s32 phi_v1_2;

    phi_v1 = func_8006A554(0);
    temp_a1 = D_8012645C;
    if (D_800DF4BC == 2) {
        phi_v1 = phi_v1 | func_8006A554(1);
        temp_a1 += D_8012645D;
    }
    
    if (D_80126494 == 0) {
        if (phi_v1 & 0x4000) {
            func_80001D04(0x241, NULL);
            D_80126488 = 0;
        } else if (phi_v1 & 0x9000) {
            if (D_801264A0[D_8012648C].unk0 == 0) {
                func_80001D04(0x241, NULL);
            }
            func_80001D04(0xEF, NULL);
            D_80126494 = 1;
        }
        
        phi_v1_2 = D_8012648C;
        if (temp_a1 < 0) {
            phi_v1_2 = D_8012648C;
            if (D_8012648C > 0) {
                D_8012648C--;
                phi_v1_2 = D_8012648C;
            }
        }
        
        if (temp_a1 > 0) {
            temp_t6 = phi_v1_2 + 1;
            if (phi_v1_2 < 2) {
                D_8012648C = temp_t6;
                phi_v1_2 = temp_t6;
            }
        }
        
        //if (D_8012648C != phi_v1_2) {
            func_80001D04(0xEB, NULL);
        //}
    } else {
        if (phi_v1 & 0x9000) {
            func_80001D04(0xEF, NULL);
            func_8006ECAC(D_8012648C);
            D_801264A0[D_8012648C].unk0 = 0;
            D_801264A0[D_8012648C].unk1 = 0;
            D_801264A0[D_8012648C].unk2 = 0;
            D_801264A0[D_8012648C].name[0] = 'D';
            D_801264A0[D_8012648C].name[1] = 'K';
            D_801264A0[D_8012648C].name[2] = 'R';
            D_801264A0[D_8012648C].name[3] = '\0';
            gSaveFileIndex = (s32) D_8012648C;
            D_801263E0 = 0;
            D_80126488 = 0;
        } else if (phi_v1 & 0x4000) {
            func_80001D04(0x241, NULL);
            D_80126494 = 0;
        }
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuGameSelectLoop.s")

void func_8008E428(void) {
    func_8009C4A8((s16*)&D_800E0398);
    func_8007FF88();
    func_800C422C(2);
}

void func_8008E45C(void) {
    D_800E045C.unk0 = D_80126550[24];
    D_800E045C.unk8 = D_80126550[25];
    D_800E0474.unk0 = D_80126550[26];
    D_800E0474.unk8 = D_80126550[27];
    D_800E048C.unk0 = D_80126550[28];
    D_800E048C.unk8 = D_80126550[29];
}

void func_8008E4B0(void) {
    D_800E041C = D_80126550[61];
    D_800E042C = D_80126550[60];
    D_800E043C = D_80126550[63];
    D_800E044C = D_80126550[62];
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008E4EC.s")



#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrackSelectInit.s")
#else
extern u32 D_800E0418;
void MenuTrackSelectInit(void){
    u32 sp_7c;
    u32 sp_78;
    Settings *settings;

    func_800C4170(2);
    get_settings();
    func_8006B224(&sp_7c, &sp_78);
    func_8001E29C(26);
    if(D_800DF488){
        D_801269C8 = 0;
        D_801269CC = 0;
        D_800E0414 = 0;
        D_800E0418 = 0;
        D_800DF488 = 0;
    }
    func_8007A520();
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008F00C.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrackSelectLoop.s")
#else
    
// Close to done with this function. Just a regalloc issue remains. :/

void func_8008F534(void);
void func_8008FF1C(s32 arg0);
void func_800904E8(s32 arg0);
void func_80090918(s32 arg0);
void func_80090ED8(s32 arg0);
void func_80090F30(s32 arg0);
void func_80092188(s32 arg0);
void func_8008E4EC(void);
s32 func_800C73E0(void);
void musicSetRelativeVolume(u8 arg0);

s32 MenuTrackSelectLoop(s32 arg0) {
    s32 phi_a2;
    Settings *settings;
    s32 i = 0;

    settings = get_settings();
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    if (func_800C73E0() == 0) {
        if (D_800DF47C != 0) {
            if (D_800DF47C < 0) {
                D_800DF47C -= arg0;
            } else {
                D_800DF47C += arg0;
            }
        }
    }
    func_8008E4EC();
    
    fast3d_cmd(D_801263A0++, 0xB6000000, 0x00001000) // gSPClearGeometryMode(D_801263A0++, G_CULL_FRONT)
    
    switch(D_801267D0) {
        case 0:
            func_8008FF1C(arg0);
            func_800904E8(arg0);
            func_80090918(arg0);
            break;
        case 1:
            func_80090ED8(arg0);
            func_80090F30(arg0);
            func_80092188(arg0);
            break;
    }
    
    if (D_800DF760 < 0) {
        musicSetRelativeVolume(0);
    } else {
        D_800DF760 += arg0 * 2;
        if (D_800DF760 >= 0x51) {
            D_800DF760 = 0x50;
        }
        musicSetRelativeVolume((u8)D_800DF760);
    }
    if (D_801267D0 < 0) {
        func_8008F534();
        D_800DF478 = 0;
        if (D_800DF4BC >= 3 || D_800DF4BC == 2 && (gActiveMagicCodes << 7) >= 0) {
            phi_a2 = 0;
            if (is_drumstick_unlocked()) {
                phi_a2 = 1;
            }
            if (is_tt_unlocked()) {
                phi_a2 ^= 3;
            }
            func_8006E2E8(0x16, -1, phi_a2);
            func_8008AEB4(0, NULL);
            MenuInit(CHARACTER_SELECT);
            return 0;
        }
        func_8006E2E8(0x27, -1, 0);
        MenuInit(GAME_SELECT);
        return 0;
    }
    if (D_801267D0 >= 2) {
        func_8008F534();
        if (D_80126548 != D_800E0410) {
            // regalloc issue with the for loop.
            for(i = 0; i < 8; i++) {
                settings->racers[i].starting_position = i;
            }
        }
        if (D_801269C8 != 4) {
            D_800DF478 = 1;
            return D_800DF4BC;
        }
        gTrophyRaceWorldId = D_801269CC + 1;
        D_800DF450 = 0;
        D_800E0FEC = 0;
        MenuInit(TROPHY_RACE_ROUND);
        return 0;
    }
    D_801263C4 = 0;
    return 0;
}
#endif

void func_8008F534(void) {
    s32 i;

    func_80066894(0, 0);
    func_8009C4A8(D_800E07C4);
    func_800710B0(0);
    func_80071140(D_800E0970);
    func_800710B0(2);
    for(i = 0; i < 15; i += 3){
        if (D_800E0710[i] != -1) {
            func_8009C508(D_800E0710[i]);
        }
        if (D_800E0710[i + 1] != -1) {
            func_8009C508(D_800E0710[i + 1]);
        }
    }
    func_800C422C(2);
    func_8007FF88();
    func_80000B28();
    func_80000C2C();
    func_80001844();
    func_8006F564(0);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/D_8008F618.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008FA54.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008FF1C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800904E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80090918.s")

void func_80090ED8(s32 arg0) {
    if (D_801263E0 == 1 && D_800E0414 == 0 && D_80126840 == 0) {
        func_80001D04(0x132, &D_80126840);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80090F30.s")

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80092188.s")

s32 func_80092BE0(s32 arg0) {
    s8 *trackIdArray; 
    s32 index;
    s32 temp;
    
    trackIdArray = (s8*)func_8001E29C(0x1C);
    
    index = 0;
    temp = -1;
    if (trackIdArray[0] != -1) {
        while(temp < 0) {
            if (arg0 == trackIdArray[index]) {
                temp = index;
            }
            index++;
            if (trackIdArray[index] == -1) {
                break;
            }
        }
    }
    
    if (temp >= 0) {
        s64 temp2 = 0x10 << temp;
        if ((temp2 & D_80126448) == 0) {
            temp = -1;
        }
    }
    
    return temp;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLoadNewAreaInit.s")
#else

extern s16 D_800E0758[8]; // Unknown number of entries.

void MenuLoadNewAreaInit(void) {
    s32 temp_v0_2;
    s8 temp_s0;
    Settings *settings;

    settings = get_settings();
    D_800DF4C4 = 0;
    D_801263BC = 0;
    D_800DF47C = 0;
    temp_s0 = settings->unk4C->unk2;
    p1_vehicle = func_8006B0AC(temp_s0);
    temp_v0_2 = func_8006B14C(temp_s0);
    if (temp_v0_2 != 5) {
        if (temp_v0_2 != 8) {
            if ((temp_v0_2 & 0x40) == 0) {
                if ((*(settings->courseFlagsPtr + (temp_s0 * 4)) & 2) == 0) {
block_4:
                    if (D_800E0758[temp_s0] != -1) {
                        func_80000FDC(D_800E0758[temp_s0] & 0xFFFF, 0, 0x3F800000);
                    }
                    D_801263E0 = -1;
                } else {
block_7:
                    if (D_800E0758[temp_s0] != -1) {
                        func_80000FDC(D_800E0758[temp_s0] & 0xFFFF, 0, 0x3F000000);
                    }
                    func_80000BE0(0x18);
                    func_80000B34(0x18);
                    func_80000B18();
                    D_801263E0 = 0;
                    func_8009C674(&D_800E0FB4);
                    func_8009C8A4(&D_800E0FD8);
                    func_8008E45C();
                    D_800E04D4 = (s32) D_80126550.unk7C;
                    D_800E04E4 = (s32) D_80126550.unk78;
                    D_800E04F4 = (s32) D_80126550.unk84;
                    D_800E0504 = (s32) D_80126550.unk80;
                    D_800E0514 = (s32) D_80126550.unk8C;
                    D_800E0524 = (s32) D_80126550.unk88;
                    D_800E05B4 = (s32) D_80126550.unkC0;
                    D_800E0614 = (s32) D_80126550.unk178;
                    func_800C01D8(&D_800DF77C);
                    D_801263BC = 0;
                    D_800DF47C = 0;
                    D_800E0980 = 0x1E;
                    func_800C4170(2);
                    func_8006E2E8(temp_s0, -1, 1);
                }
            } else {
                goto block_7;
            }
        } else {
            goto block_4;
        }
    } else {
        goto block_4;
    }
    func_800C5494(7);
    if (func_8006B14C(temp_s0) & 0x40) {
        func_800C31EC(func_8006B190(temp_s0) + 0x3B);
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80092E94.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLoadNewAreaLoop.s")

void func_80093A0C(void) {
    func_8009C4A8((s16*)&D_800E0FB4);
    func_800C422C(2);
    func_80000B28();
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80093A40.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80093D40.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094170.s")

void func_800945B0(void) {
    func_80072298(1);
    func_800C5620(7);
    func_800C5494(7);
    D_800E0984 = 0;
}

void func_800945E4(void) {
    func_800945B0();
}

void func_80094604(void) {
    D_800E0A50 = D_80126550[50];
    D_800E0A60 = D_80126550[51];
    D_800E0A70 = D_80126550[52];
    D_800E0A90 = D_80126550[54];
    D_800E0A80 = D_80126550[53];
    D_800E0AA0 = D_80126550[55];
    D_800E0AB0 = D_80126550[56];
    D_800E0AC0 = D_80126550[57];
    D_800E0AD0 = D_80126550[58];
    D_800E0AE0 = D_80126550[59];
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094688.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094A5C.s")

void func_80094C14(s32 arg0) {
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    D_80126A94 += arg0;
    if (D_801263D8 >= 0) {
        D_801263D8 += arg0;
        switch(D_800DF460) {
            case 0:
                if (func_8000C8B4(0xF0, &D_80126A94) < D_801263D8) {
                    func_80000C98(-0x100);
                    D_800DF460 = 1;
                }
                break;
            case 1:
                if (func_8000C8B4(0x12C, &D_80126A94) < D_801263D8) {
                    func_80000BE0(0x18);
                    func_80000B34(0x18);
                    func_80000C98(0x100);
                }
                break;
        }
        if (func_8000C8B4(0x12C) < D_801263D8) {
            D_801263D8 = -1;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094D28.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80095624.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80095728.s")

void func_800981E8(void);

void func_80096790(void) {
    s32 temp;
    s8 *temp2;
    
    temp2 = (s8*)func_8006BDB0();
    func_8009C4A8((s16*)&D_800E0A24);
    temp = *temp2 - 1; // temp is $v1, when it should be $v0!
    
    if (D_80126BB8) {
        func_8009C508(D_800E0710[temp * 3]);
    }
    D_80126BB8 = 0;
    
    if (D_80126BBC) {
        func_8009C508(D_800E0710[(temp * 3) + 1]);
    }
    D_80126BBC = 0;
    
    func_800981E8();
    func_80000968(0);
}

void menu_11_init(void) {
    Settings *settings;
    u16 *placements;
    s32 i;
    s8 temp_a2;

    settings = get_settings();
    D_80126BF0[0] = (s32) D_800DF4A0->unk60;
    D_80126BF0[1] = (s32) D_800DF4A0->unk5C;
    D_80126BF0[2] = (s32) D_800DF4A0->unk70;
    D_80126C14 = 3;
    
     
    for (i = 0; i < D_800DF4BC; i++) {
        temp_a2 = settings->racers[i].starting_position;
        if (temp_a2 < 4) {
            placements = settings->racers[i].placements;
            placements[temp_a2]++;
        }
    }
    
    D_801263E0 = -1;
    D_801263BC = 0;
    D_801263D8 = 0;
    D_800DF47C = 0;
    D_80126A68 = 0;
    D_801263C4 = 1;
    D_800E0988 = 0;
    func_8009C674((s16*)&D_800E0A24);
    func_8009C8A4((s16*)&D_800E0A40);
    func_80094604();
    func_800C4170(2);
    func_800C01D8(&D_800DF77C);
    func_80000BE0(0x18);
    func_80000B34(0x18);
    func_80000C98(0x80);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80096978.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/Menu11Loop.s")

void func_800976CC(void) {
    func_8009C4A8((s16*)&D_800E0A24);
    func_800C422C(2);
}

void func_800976F8(u32 arg0, char *output, s32 length) {
    s32 index;
    output[length] = 0; // Set null terminator
    index = length - 1;
    while(index >= 0){
        index--;
        // D_800E0F6C[0x20] = "ABCDEFGHIJKLMNOPQRSTYVWXYZ.?    " = valid ascii chars for name input.
        output[index + 1] = D_800E0F6C[arg0 & 0x1F];
        arg0 = arg0 >> 5;
    }
}

s32 func_80097744(unsigned char *arg0, s32 arg1) {
    s32 i;
    u32 output;
    u8 processingChars;
    u8 currentChar;
    s32 charIndex;

    output = 0;
    processingChars = 1;
    
    for (i = 0; i < arg1; i++) {
        if (arg0[i] == '\0') {
            processingChars = 0;
        }
        
        if (!processingChars) {
            currentChar = ' ';
            charIndex = 0;
        } else {
            currentChar = arg0[i];
            charIndex = 0;
        }
        
        while (currentChar != D_800E0F6C[charIndex]) {
            charIndex++;
            if (charIndex >= 0x1F) {
                break;
            }
        }
        
        output <<= 5;
        output |= charIndex & 0x1F;
    }
    
    return output;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800977D0.s")
#else
s32 func_800977D0(unsigned char *arg0, unsigned char *arg1) {
    s32 phi_v0 = 0;
    s32 phi_v1 = 0;
    while (*arg0 != '\0') {
        if (*arg0 == ' ') {
            arg0++;
            phi_v0++;
            while (*arg0 == ' ') {
                arg0++;
                phi_v0++;
            }
            if (*arg0 != '\0') {
                while(phi_v1 < phi_v0){
                    *arg1 = *arg0;
                    arg0++;
                    arg1++;
                    phi_v1++;
                }
            }
            
        } else {
            *(arg1++) = *(arg0++);
        }
    }
    *arg1 = '\0';
}
#endif 

void func_80097874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 arg5, s32 arg6) {
    D_800E0F90 = arg0;
    D_800E0F94 = arg1;
    D_800E0F98 = arg2;
    D_800E0F9C = arg3;
    D_80126C6C = arg4;
    D_80126C74 = arg5;
    D_80126C78 = arg6;
    D_800E0FA0 = 0;
    D_80126C50 = (f32) *D_80126C6C;
    D_80126C48 = 0;
    D_80126C3C = 0;
    D_80126C34 = 0;
    func_800C4170(2);
}


GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80097918.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80097D10.s")

void func_800981E8(void) {
    func_800C422C(2);
}

// Gets triggered when entering trophy race in adventure mode.
void func_80098208(void) {
    Settings *settings = get_settings();
    gTrophyRaceWorldId = settings->worldId;
    D_800E0FEC = 0;
    settings->unk4C->unk0 = settings->courseId;
    settings->unk4C->unkF = 0;
    settings->unk4C->unk1 = 0;
    D_800DF450 = 1;
    func_8000E4BC(0);
}

extern s32 D_800E0980;
s8* func_8001E29C(s32 arg0);

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrophyRaceRoundInit.s")
#else
void MenuTrophyRaceRoundInit(void) {
    s32 temp;
    s32 i;
    Settings *settings;
    s8 *temp_t9;

    settings = get_settings();
    temp_t9 = func_8001E29C(0x1A); // Returns level ids array.
    
    if (D_800E0FEC == 0) {
        for(i = 0; i < 8; i++) {
            settings->racers[i].trophy_points = 0;
        }
    }
    
    temp = temp_t9[((gTrophyRaceWorldId - 1) * 6) + D_800E0FEC];
    while(temp == -1) {
        temp = (temp + 1) & 3;
    }
    
    for(i = 0; i < D_800DF4BC; i++){
        p1_vehicle[i] = func_8006B0AC(temp);
    }
    
    func_8006DB14(func_8006B0AC(temp));
    func_8006E2E8(temp, -1, 1);
    
    D_800DF47C = 0;
    D_800E0980 = 10;
    func_800C4170(2);
    func_80000BE0(0x18);
    func_80000B34(0x18);
    func_80000C98(0x100);
}
#endif

void func_800983C0(s32 arg0) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s8* sp20;

    sp20 = func_8001E29C(0x1A);
    if (osTvType == 0) {
        sp2C = 0x12;
    } else {
        sp2C = 0;
    }
    
    sp28 = func_8006BDDC(func_8006B1D4(gTrophyRaceWorldId));
    sp24 = func_8006BDDC(sp20[((gTrophyRaceWorldId - 1) * 6) + D_800E0FEC]);
    func_800C43CC(0, 0, 0, 0);
    func_800C42EC(2);
    func_800C4384(0, 0, 0, 0xFF, 0x80);
    func_800C4440(&D_801263A0, 0xA1, 0x23, sp28, 0xC);
    func_800C4440(&D_801263A0, 0xA1, 0x43, D_800DF4A0->unk118, 0xC);
    func_800C4384(0xFF, 0xFF, 0xFF, 0, 0xFF);
    func_800C4440(&D_801263A0, 0xA0, 0x20, sp28, 0xC);
    func_800C4440(&D_801263A0, 0xA0, 0x40, D_800DF4A0->unk118, 0xC);
    func_800C4440(&D_801263A0, 0xA0, sp2C + 0xB0, D_800DF4A0->unk228[D_800E0FEC], 0xC);
    func_800C4440(&D_801263A0, 0xA0, sp2C + 0xD0, sp24, 0xC);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrophyRaceRoundLoop.s")

void func_80098754(void) {
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80098774.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrophyRaceRankingsInit.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80098EBC.s")
#else
void func_80098EBC(s32 arg0) {
    s32 test;
    s32 fade;
    s32 i;

    D_801263BC = (D_801263BC + arg0) & 0x3F;
    
    test = D_801263BC * 8;
    if (test >= 0x100) {
        test = 0x1FF - test;
    }
    
    // Has regalloc issues starting here.
    for (i = 0; i < D_800E0FE4; i++) {
        fade = 0xFF;
        
        if (D_800DF4BC < 3 && ((D_801263E0 == 0 && D_80126418[i]) || (D_801263E0 != 0 && D_80126420[i]))) {
            fade = (test >> 1) + 0x80;
        }
        
        D_800E1088[i][0].filterRed = fade;
        D_800E1088[i][0].filterGreen = fade;
        D_800E1088[i][0].filterBlue = fade;
    }
    
    if (D_801263E0 == 2 || D_801263E0 == 3) {
        DrawMenuText(1, &D_800E1048, 1.0f);
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrophyRaceRankingsLoop.s")

void func_80099600(void) {
    func_8009C4A8((s16*)&D_800E1024);
    func_800C422C(2);
}

s32 get_trophy_race_world_id(void) {
    return gTrophyRaceWorldId;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009963C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800998E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuGhostDataInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80099E8C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuGhostDataLoop.s")

void func_8009ABAC(void) {
    func_8009C4A8((s16*)&D_800E1708);
    func_800C422C(2);
}

void func_8009ABD8(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 phi_v1;
    
    phi_v1 = 0;
    while(phi_v1 < arg1) {
        phi_v1++;
        while (-1 != *arg0) {
            arg0 += 3;
        }
        arg0++;
    }
    
    if ((phi_v1 == 0) && (func_8001E29C(0x19) == arg0)) {
        D_8012684C = 1;
    } else {
        D_8012684C = 0;
    }
    
    D_801267EC = arg0;
    D_80126824 = arg2;
    D_8012683C = arg3;
    D_80126844 = arg4;
    D_80126804 = arg5;
}

void menu_17_init(void) {
    if (D_80126804 != 0) {
        func_8009C674(D_800E1768);
        func_80094604();
    }
    func_8006E2E8(D_801267EC[0], D_801267EC[1], D_801267EC[2]);
    D_800DF47C = 0;
    D_801263E0 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/Menu17Loop.s")

void func_8009AF18(void) {
    if (D_80126804 != 0) {
        func_8009C4A8(D_800E1768);
    }
}

void menu_credits_init(void) {
    s32 phi_v1;
    s32 phi_a0;
    u16 *temp;
    Settings *settings;

    settings = get_settings();
    D_800DF47C = 0;
    D_80126BC4 = 0;
    D_80126BCC = 0;
    D_801263E0 = 0;
    D_801263D8 = 0x28;
    D_800DF460 = 0;
    D_80126BD0 = 0;
    D_80126BD8 = 0;
    D_80126BE0 = 0;
    func_80077B5C(0, 0, 0);
    if (osTvType == 0) {
        func_80066940(0, 0, 0x26, 0x140, 0xE0);
        func_80066AA8(0, 0x8000, 0x8000, 0x140, 0x11C);
    } else {
        func_80066940(0, 0, 0x28, 0x140, 0xC4);
        func_80066AA8(0, 0x8000, 0x8000, 0x140, 0xF0);
    }
    func_80066610();
    func_80066818(0, 1);
    func_8009C674((s16*)&D_800E17D8);
    func_8009C8A4((s16*)&D_800E17F0);
    func_80094604();
    func_800C4170(2);
    func_80000BE0(0x18);
    D_800E18F8 = (u16)0x1000;
    if (D_800E1B4C) {
        func_80000B34(8);
        D_800E1938[84] = D_800E1AE4[2];
        D_800E1938[85] = D_800E1AE4[3];
        D_800E1938[86] = D_800E1AE4[4];
        D_800E1B4C = 0;
    } else {
        if (settings->bosses & 0x20) {
            func_80000B34(0x25);
            D_800E1938[84] = D_800E1AE4[1];
            D_800E18F8 = (u16)0x61F4;
            D_80126BCC = 9;
        } else {
            func_80000B34(8);
            D_800E1938[84] = D_800E1AE4[0];
        }
        phi_v1 = D_800E1AF8[func_8006F94C(0, 0x14, &D_800E1938)];
        phi_a0 = -1;
        while(phi_v1 != 0) {
            phi_v1 >>= 1;
            phi_a0++;
        }
        
        // I don't know why this works. Please clean it up if you can!
        temp = *D_80126C30 + 1;
        D_800E1938[85] = (char*)(*D_80126C30) + (temp)[(phi_a0 << 1) + 1];
        D_800E1938[86] = (char*)(*D_80126C30) + (temp)[(phi_a0 << 1)];
    }
    func_80000B18();
    func_800C0170();
    func_8006F564(1);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009B1E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuCreditsLoop.s")

void func_8009BCF0(void) {
    func_80000BE0(0x12);
    func_800C0180();
    func_80066894(0, 0);
    func_80066AA8(0, 0x8000, 0x8000, 0x8000, 0x8000);
    func_8009C4A8((s16*)&D_800E17D8);
    func_800C422C(2);
    func_8006F564(0);
}

/* Unknown size */
typedef struct unk80069D20 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[6];
    f32 unkC;
    f32 unk10;
    f32 unk14;
} unk80069D20;

void func_8001D5E0(f32 arg0, f32 arg1, f32 arg2);

void func_8009BD5C(void) {
    unk80069D20 *temp_v0;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    func_8006652C(0);
    func_800665E8(0);
    
    temp_v0 = (unk80069D20*)func_80069D20();
    
    sp2A = temp_v0->unk0;
    sp28 = temp_v0->unk2;
    sp26 = temp_v0->unk4;
    sp20 = temp_v0->unkC;
    sp1C = temp_v0->unk10;
    sp18 = temp_v0->unk14;
    temp_v0->unk4 = 0;
    temp_v0->unk2 = 0;
    temp_v0->unk0 = 0x8000;
    temp_v0->unkC = -32.0f;
    temp_v0->unk10 = -32.0f;
    temp_v0->unk14 = -32.0f;
    
    func_8001D5E0(0, 0, -1);
    func_80066CDC(&D_801263A0, &D_801263A8);
    
    temp_v0->unk0 = sp2A;
    temp_v0->unk2 = sp28;
    temp_v0->unk4 = sp26;
    temp_v0->unkC = sp20;
    temp_v0->unk10 = sp1C;
    temp_v0->unk14 = sp18;
}

void func_8009BE54() {
    
}

void func_8009BE5C(void) {
    s32 i;
    for(i = 0; i < 4; i++) {
        D_8012645C[i] = 0;
        D_80126464[i] = 0;
        D_80126454[i] = 0;
        D_80126458[i] = 0;
        D_80126468[i] = 0;
        D_8012646C[i] = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009BF20.s")

void func_8009C154(void) {
    s32 i;
    D_800DF4C8 = 1;
    for(i = 0; i < 8; i++) {
        D_801263F0[i] = i;
    }
}

s32 get_save_file_index(void) {
    return gSaveFileIndex;
}

s32 func_8009C1B0(void) {
    Settings *settings = get_settings();
    if (D_800DF4B8 == 0 && D_800DF478 == 0) {
        if (settings->newGame) {
            return 0;
        } else {
            return settings->courseId;
        }
    }
    D_800DF478 = 0;
    return D_800DF4D4;
}

s8 func_8009C228(s32 arg0) {
    return D_801263F0[arg0];
}

// Unused duplicate of func_8009C228()?
s8 func_8009C23C(s32 arg0) {
    return D_801263F0[arg0];
}

s8 func_8009C250(s32 arg0) {
    return p1_vehicle[arg0];
}

void func_8009C264(s32 arg0, s32 arg1) {
    p1_vehicle[arg0] = arg1;
}

s8* func_8009C274(void) {
    return D_801263DC;
}

s8 func_8009C280(s32 arg0) {
    if (arg0 < 0 || arg0 >= 4) {
        return -1;
    }
    if (D_801263D4[arg0] == 0) {
        return -1;
    }
    return players_character_array[arg0];
}

void func_8009C2C4(s32 arg0) {
    D_800DF4B8 = arg0;
}

s32 is_in_tracks_mode(void) {
    return D_800DF4B8;
}

void set_magic_code_flags(s32 flags) {
    gActiveMagicCodes |= flags;
    gUnlockedMagicCodes |= flags;
}

s32 func_8009C30C(void) {
    s32 cheats = gActiveMagicCodes;
    if (D_800DF4B8 == 0 || func_8000E4C8() != 0) {
        cheats &= 0x1B400133;
    }
    if (!func_8006B240()) {
        cheats &= ~4; // Clears MIRRORED_TRACKS cheat
    }
    if ((func_8006B14C(get_settings()->courseId) & 0x40) != 0) {
        // Clears START_WITH_10_BANANAS, DISABLE_WEAPONS, DISABLE_BANANAS, and BALLOON cheats.
        cheats &= ~0xF9880; 
    }
    if (gIsInAdventureTwo && func_8006B240()) {
        cheats |= 4; // Sets MIRRORED_TRACKS cheat
    }
    return cheats;
}

s32 func_8009C3C8(void) {
    return D_800DF4BC;
}

typedef struct unk8006BDB0 {
    u8 pad[0x4C];
    s8 unk4C;
} unk8006BDB0;

s32 func_8009C3D8(void) {
    unk8006BDB0 *temp = (unk8006BDB0*)func_8006BDB0(); 
    if (gIsInTwoPlayerAdventure && D_800DF4B8 == 0) {
        if (temp->unk4C == 0 || (temp->unk4C & 0x40) != 0) {
            return 2;
        }
    }
    return D_800DF4BC;
}

s32 func_8009C440(void) {
    if (D_800DF4B8 == 0) {
        return 6;
    }
    if (gTrophyRaceWorldId) {
        return 6;
    }
    return (D_800E0410 + 1) << 1; // Doesn't match with multiply.
}

Settings** func_8009C490(void) {
    return (Settings**)D_80126530;
}

void func_8009C49C(void) {
    D_800DF488 = 0;
}

void func_8009C4A8(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C508(arg0[index++]);
    }
}

void func_8007B2BC(u32 arg0);
void func_8007CCB0(u32 arg0);
void particlePtrList_addObject(u32 arg0);
void func_8005FF40(u32 arg0);

void func_8009C508(s32 arg0) {
    if (D_80126750[arg0] != 0) {
        if (D_80126550[arg0] != 0) {
            if ((((*D_800DF750)[arg0] & 0xC000) == 0xC000) && (D_80126550[arg0] != 0)) {
                func_800710B0(0);
                func_8007B2BC((u32)D_80126550[arg0]);
                func_800710B0(2);
            } else {
                if ((*D_800DF750)[arg0] & 0x8000) {
                    func_8007CCB0((u32)D_80126550[arg0]);
                } else {
                    if ((*D_800DF750)[arg0] & 0x4000) {
                        particlePtrList_addObject((u32)D_80126550[arg0]);
                    } else {
                        func_8005FF40((u32)D_80126550[arg0]);
                    }
                }
            }
        }
        D_80126550[arg0] = 0;
        D_80126750[arg0] = 0;
        D_800DF758--;
        particlePtrList_flush();
    }
    if (D_800DF758 == 0) {
        if (D_800DF75C != NULL) {
            func_80071140(D_800DF75C);
            D_800DF75C = NULL;
        }
        if (*D_800DF750 != NULL) {
            func_80071140(*D_800DF750);
            *D_800DF750 = NULL;
            D_800DF754 = (u16)0;
        }
    }
}

void func_8009C674(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C6D4(arg0[index++]);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C6D4.s")

void func_8009C904(s32 arg0);

void func_8009C8A4(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C904(arg0[index++]);
    }
}

s32 func_8006F94C(s32, s32);
void func_8009C904(s32 arg0) {
    if (D_800DF75C == NULL) {
        D_800DF75C = func_80070C9C(sizeof(unk800DF510) * 18, 0xFF0000FF);
    }
    
    D_800DF75C[arg0].unk0 = D_800DF510[arg0].unk0;
    D_800DF75C[arg0].unk2 = D_800DF510[arg0].unk2;
    D_800DF75C[arg0].unk4 = D_800DF510[arg0].unk4;
    D_800DF75C[arg0].unk6 = D_800DF510[arg0].unk6;
    D_800DF75C[arg0].unkC = D_800DF510[arg0].unkC;
    D_800DF75C[arg0].unk10 = D_800DF510[arg0].unk10;
    D_800DF75C[arg0].unk14 = D_800DF510[arg0].unk14;
    D_800DF75C[arg0].unk8 = D_800DF510[arg0].unk8;
    D_800DF75C[arg0].unk18 = D_800DF510[arg0].unk18;
    D_800DF75C[arg0].unk1A = func_8006F94C(0, 0xFFFF);
    D_800DF75C[arg0].unk1B = func_8006F94C(0, 0xFFFF);
    D_800DF75C[arg0].unk1C = func_8006F94C(0, 0xFFFF);
    D_800DF75C[arg0].unk1D = D_800DF510[arg0].unk1D;
}

void func_8009CA58(void) {
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009CA60.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009CD7C.s")

void func_8009CF68(s32 arg0) {
    if (D_800DF4E4[arg0] == 0) {
        if (arg0 != 3) {
            D_801264E2 = 0;
            D_801264D8 = 0;
        }
        D_800DF4E0 = 1;
        D_800DF4E4[arg0] = 1;
    }
}

void func_8009CFB0(void) {
    if (D_800DF4E0 != 0) {
        D_800DF4E0 = 0;
        func_800C5620(1);
        func_8009BE5C();
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009CFEC.s")

void func_8009D118(s32 arg0) {
    if (arg0 == 0) {
        func_800C5000(1, 0, 0, 0x7F, 0x5A, 0xFF);
        if (D_800DF4EC != 0) {
            func_800C5000(1, 0, 0, 0x7F, 0x5A, 0x78);
        }
    } else {
        func_800C5000(1, 0xCF, 0xCF, 0xCF, 0x5A, 0xFF);
    }
    D_800DF4EC = (u8)0;
}

void func_8009D1B8(s32 arg0, s32 arg1, s32 arg2) {
    func_8009D118(D_801264D8 == D_80126504);
    if (D_801264D8 == D_80126504) {
        D_80126516 = arg2;
    }
    func_800C5168(1, -0x8000, D_8012650E, arg0, 1, 4);
    D_8012650E = (s8) (D_8012650E + arg1);
    D_80126504 = (s8) (D_80126504 + 1);
}

void func_8009D26C(void) {
    if (D_80126464[0] < 0) {
        D_801264D8 = D_801264D8 + 1;
        func_80001D04(0xB2, NULL);
    } else if (D_80126464[0] > 0) {
        D_801264D8 = D_801264D8 - 1;
        func_80001D04(0xB2, NULL);
    }
    
    if (D_801264D8 < 0) {
        D_801264D8 = D_80126504 - 1;
    }
    
    if (D_801264D8 >= D_80126504) {
        D_801264D8 = 0;
    }
}

void func_8009D324(void) {
    D_800DF4D8 = 0;
}

void func_8009D330(s32 arg0) {
    D_800DF4DC = arg0;
}

void func_8009D33C(s32 arg0, s32 arg1) {
    if (D_801264E2 == arg0) {
        D_801264E2 = arg1;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009D360.s")

s32 func_8009D9F4(void) {
    s32 state;
    s32 temp_v0;

    func_800C4EDC(1, 0x18, 0x10, 0xB8, 0x87);
    func_800C4F7C(1, 0);
    state = 0;
    temp_v0 = func_8006A554(0);
    D_80126504 = 0;
    D_800DF4DC = 0;
    func_800C5168(1, -0x8000, 6, D_800DF4A0->unkC4, 1, 4);
    func_800C5168(1, -0x8000, 0x14, D_800DF4A0->unkC8, 1, 4);
    D_8012650E = 0x32;
    func_8009D1B8(D_800DF4A0->unk5C, 0x14, 0);
    func_8009D1B8(D_800DF4A0->unkCC, 0x14, 1);
    func_8009D26C();
    if (temp_v0 & 0x8000) {
        func_80001D04(0xEF, NULL);
        switch(D_80126516) {
            case 0:
                state = 1;
                break;
            case 1:
                state = 2;
                break;
        }
    }
    return state;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009DB3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009E3D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009E7E8.s")

void func_8009E9A0(void) {

}

void func_8009E9A8(void) {

}

f32 func_8009E9B0(s32 arg0, Gfx **arg1, s32 *arg2, s32 *arg3) {
    D_801263A0 = *arg1;
    D_801263A8 = *arg2;
    D_801263AC = *arg3;
    func_80067F2C(&D_801263A0, &D_801263A8);
    if (D_800E1E28 != 0 && D_801264E2 == 4) {
        func_8009E3D0();
    }
    *arg1 = D_801263A0;
    *arg2 = D_801263A8;
    *arg3 = D_801263AC;
    return 1.0f;
}

s64* func_8009EA6C(void) {
    return &D_80126448;
}

s32 func_8009EA78(s64 arg0) {
    D_80126448 |= arg0;
    func_8006ECE0();
    return 1;
}

s32 func_8009EABC(s64 arg0) {
    D_80126448 &= ~arg0;
    func_8006ECE0();
    return 1;
}

s64 func_8009EB08(void) {
    return D_80126448;
}

s32 func_8009EB20(void) {
    s32 val = 0;
    switch(D_80126448 & 0xC) {
        case 4: 
            val = 1;
            break;
        case 8: 
            val = 2;
            break;
        case 12: 
            val = 3;
            break;
    }
    return val;
}

void set_language(s32 language) {
    s64 sp18 = 0; // English
    
    switch(language) {
        case 1: // German
            sp18 = 4;
            break;
        case 2: // French
            sp18 = 8;
            break;
        case 3: // Japanese
            sp18 = 12;
            break;
    }
    
    D_80126448 &= 0xFFFFFFFFFFFFFFF3;
    D_80126448 |= sp18;
    
    func_8007F900();
    func_8006ECE0();
}

s32 func_8009EC60(void) {
    return D_80126448 & 1;
}

s32 is_in_adventure_two(void) {
    return gIsInAdventureTwo;
}

s32 is_in_two_player_adventure(void) {
    if (is_in_tracks_mode()) {
        return 0;
    }
    return gIsInTwoPlayerAdventure;
}

s32 is_tt_unlocked(void) {
    return gActiveMagicCodes & 1;
}

s32 is_drumstick_unlocked(void) {
    return gActiveMagicCodes & 2;
}
