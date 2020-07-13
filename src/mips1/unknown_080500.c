/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8009EC70 */

#include "types.h"
#include "macros.h"
#include "structs.h"

extern s32 osTvType;

extern s8 D_800DF450;
extern s32 D_800DF458;
extern s32 D_800DF46C;
extern s32 gIsInAdventureTwo;
extern s32 gActiveMagicCodes;
extern s32 gUnlockedMagicCodes;

typedef struct unk800DF4A0 {
    u8 pad0[0x25C];
    s32 unk25C;
} unk800DF4A0;
extern unk800DF4A0* D_800DF4A0;

extern s32 D_800DF478;
extern s32 D_800DF47C;
extern s32 D_800DF498;
extern s32 D_800DF4B8;
extern s32 D_800DF4BC;
extern s32 D_800DF4C8;
extern s32 D_800DF4D4;
extern s8 D_800DF4D8;
extern s8 D_800DF4E0;
extern s8 D_800DF4E4[4];
extern s8 D_800DF4EC;
extern s32 gIsInTwoPlayerAdventure;
extern s32 gSaveFileIndex;
extern s16 D_800DF7C4[11];
extern s32 D_800DF77C;
extern s32 D_800DFA2C;
extern s16 D_800DFC78[24];
extern s32 D_800DFDC8;
extern s32 D_800DFFD0;
extern s32 D_800DFFD4;
extern s32 D_800E0398;
extern s32 D_800E0410;
extern s32 D_800E0414;

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

extern s32 D_800E0984;
extern s32 D_800E0A24;
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
extern s32 D_800E0FEC;
extern s32 gTrophyRaceWorldId;
extern s32 D_800E1024;
extern s32 D_800E1708;
extern s16 D_800E1768[10];
extern s32 D_800E17D8;
extern s32 *D_800E1DA4[2];
extern s32 *D_800E1DAC[2];
extern s32 D_800E1DB8;
extern s32 D_800E1DBC;
extern s8 D_800E1E28;

extern s32 D_801263A0;
extern s32 D_801263A8;
extern s32 D_801263AC;
extern s32 D_801263BC;
extern s32 D_801263C4;
extern s8 D_801263D4[4];
extern s32 D_801263D8;
extern s32 D_801263E0;
extern s8 D_801263E8[8];
extern s8 D_801263F0[8];
extern f32 D_80126450;
extern u8 D_80126454;
extern u8 D_80126455;
extern u8 D_80126456;
extern u8 D_80126457;
extern u8 D_80126458;
extern u8 D_80126459;
extern u8 D_8012645A;
extern u8 D_8012645B;
extern u8 D_8012645C;
extern u8 D_8012645D;
extern u8 D_8012645E;
extern u8 D_8012645F;
extern s8 D_80126464;
extern u8 D_80126465;
extern u8 D_80126466;
extern u8 D_80126467;
extern u8 D_80126468;
extern u8 D_80126469;
extern u8 D_8012646A;
extern u8 D_8012646B;
extern u8 D_8012646C;
extern u8 D_8012646D;
extern u8 D_8012646E;
extern u8 D_8012646F;
extern s32 D_80126470;
extern s8 D_801264D8;
extern s8 D_801264E2;
extern s8 D_80126504;
extern s8 D_8012650E;
extern s8 D_80126516;
extern u32* D_80126550[1]; // lookup table? Unknown number of entries.
extern s8* D_801267EC;
extern s32 D_80126804;
extern s32 D_80126824;
extern s32 D_8012683C;
extern s32 D_80126840;
extern s32 D_80126844;
extern s32 D_8012684C;
extern s32 D_801269FC;
extern s32 D_80126A0C;
extern s32 D_80126A64;
extern s32 D_80126AA0;
extern s32 *D_80126C2C;
extern s32 D_80126C34;
extern s32 D_80126C3C;
extern u16 D_80126C40;
extern u16 D_80126C42;
extern u16 D_80126C46;
extern u16 D_80126C44;
extern s32 D_80126C48;
extern s16 D_80126C4C;
extern u8  D_80126C58;
extern f32 D_80126C50;
extern s32 *D_80126C6C;
extern s32 D_80126C70;
extern s32 D_80126C74;
extern s32 D_80126C78;

Settings *get_settings();
void func_8009C4A8(s16 *arg0);

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
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80080E6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80080E90.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80081218.s")

void func_800813C0(void) {
    D_800DF458 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLoop.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80081800.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80081C04.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80081E54.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80081F4C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/DrawMenuText.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800828B8.s")

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
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80082FAC.s")
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800841B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuOptionsLoop.s")

void func_80084734(void) {
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuAudioOptionsInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80084854.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuAudioOptionsLoop.s")

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

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuSaveOptionsInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800853D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80085B9C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800860A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800861C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800862C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800867D4.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80086A48.s")
#else
extern s32 D_80126A08;
extern s32 D_80126A00;
extern s32 D_801263E0;
extern s32 D_80126BD4;
extern f32 D_80126BDC;
extern f32 D_800E8414;
extern f32 D_80126BEC;
extern s32 D_80126BE4;

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
            D_80126BEC = D_80126BEC + temp3 * (temp2 - D_80126BDC);
        }
        arg0--;
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80086AFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800871D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800874D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800875E4.s")

s32 func_800876CC(s32 arg0, s32 arg1) {
    if (arg0 & 0x4000) {
        func_80001D04(0x241, 0);
        D_801263E0 = 5;
    } else if (arg0 & 0x9000) {
        func_80001D04(0xEF, 0);
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800887E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80088938.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800890AC.s")

void func_800895A4(void) {
    func_8009C508(0x3F);
    func_80071140(D_80126AA0);
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
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008A8F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuMagicCodesListLoop.s")

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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008AF00.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuCharacterSelectInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008B20C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008B358.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008B4C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008B758.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008BB3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuCharacterSelectLoop.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008BFE8.s")

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

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuCautionLoop.s")

void func_8008C4E8(void) {
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuGameSelectInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008C698.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuFileSelectLoop.s")

void func_8008CACC(void) {
    func_800C422C(2);
    func_8007FF88();
    func_8009C508(0x43);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuFileSelectInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008CC28.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008CD74.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008D5F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008D8BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008DC7C.s")
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008E4B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008E4EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrackSelectInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008F00C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrackSelectLoop.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008F534.s")
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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80092BE0.s")
#else
extern s32 D_80126448;
extern s32 D_8012644C;
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
    
    // Does not match! This block has regalloc issues.
    if (temp >= 0) {
        s32 temp2 = 0x10 << temp;
        s32 temp3 = (0x10 << temp) & D_8012644C;
        s32 temp4 = ((0x10 << temp) >> 0x1F) & D_80126448;
        if (temp4 == 0 && temp3 == 0) {
            temp = -1;
        }
    }
    
    return temp;
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLoadNewAreaInit.s")
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
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094C14.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094D28.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80095624.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80095728.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80096790.s")
#else
extern s16 D_800E0710[30];
extern s32 D_80126BB8;
extern s32 D_80126BBC;

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
#endif

GLOBAL_ASM("asm/non_matchings/unknown_080500/Menu11Init.s")
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80097744.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800977D0.s")

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


GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrophyRaceRoundInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800983C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrophyRaceRoundLoop.s")

void func_80098754(void) {
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80098774.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTrophyRaceRankingsInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80098EBC.s")
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

s8* func_8001E29C(s32 arg0);

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

void func_8009C674(s16 *arg0);

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

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuCreditsInit.s")
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
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009BD5C.s")

void func_8009BE5C(void) {
    D_8012645C = 0;
    D_80126464 = 0;
    D_80126454 = 0;
    D_80126458 = 0;
    D_80126468 = 0;
    D_8012646C = 0;
    D_8012645D = 0;
    D_80126465 = 0;
    D_80126455 = 0;
    D_80126459 = 0;
    D_80126469 = 0;
    D_8012646D = 0;
    D_8012645E = 0;
    D_80126466 = 0;
    D_80126456 = 0;
    D_8012645A = 0;
    D_8012646A = 0;
    D_8012646E = 0;
    D_8012645F = 0;
    D_80126467 = 0;
    D_80126457 = 0;
    D_8012645B = 0;
    D_8012646B = 0;
    D_8012646F = 0;
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


GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C228.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C250.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C274.s")

s8 func_8009C280(s32 arg0) {
    if (arg0 < 0 || arg0 >= 4) {
        return -1;
    }
    if (D_801263D4[arg0] == 0) {
        return -1;
    }
    return D_801263E8[arg0];
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C490.s")

void func_8009C4A8(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C508(arg0[index++]);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C508.s")

void func_8009C674(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C6D4(arg0[index++]);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C6D4.s")

void func_8009C8A4(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C904(arg0[index++]);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C904.s")
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009CFB0.s")
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
        D_80126516 = (s8) arg2;
    }
    func_800C5168(1, -0x8000, D_8012650E, arg0, 1, 4);
    D_8012650E = (s8) (D_8012650E + arg1);
    D_80126504 = (s8) (D_80126504 + 1);
}

void func_8009D26C(void) {
    if (D_80126464 < 0) {
        D_801264D8 = D_801264D8 + 1;
        func_80001D04(0xB2, 0);
    } else if (D_80126464 > 0) {
        D_801264D8 = D_801264D8 - 1;
        func_80001D04(0xB2, 0);
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009D330.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009D33C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009D360.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009D9F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009DB3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009E3D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009E7E8.s")

void func_8009E9A0(void) {

}

void func_8009E9A8(void) {

}

f32 func_8009E9B0(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EA6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EA78.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EABC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EB08.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EB20.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EB94.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EC60.s")

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
