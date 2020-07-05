/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8009EC70 */

#include "types.h"
#include "macros.h"

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
extern u8 D_80126464;
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

extern s32 D_800DF458;
extern s32 D_800DF494;
extern s32 gActiveMagicCodes;
extern s32 D_800DF4B8;
extern s32 D_800DF4BC;
extern s32 D_800DF4C0;
extern s32 D_800DF4CC;
extern s16 D_800DF7C4[11];
extern s32 D_800DFA2C;
extern s32 D_800DFDC8;
extern s32 D_800DFFD0;
extern s32 D_800E0398;
extern s32 D_800E0984;
extern s32 D_800E0A24;
extern s32 D_800E0FB4;
extern s32 D_800E0FE8;
extern s32 D_800E1024;
extern s32 D_800E1708;
extern s32 D_800E1768;
extern s32 D_800E17D8;
extern s32 D_801263D8;
extern s32 D_80126804;
extern s32 D_801269FC;
extern s32 D_80126AA0;

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8007F900.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8007FF88.s")
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
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800829F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLogosScreenInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLogoScreenLoop.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80082FAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80083098.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTitleScreenInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008377C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuTitleScreenLoop.s")

void func_80084118(void) {
    func_8009C4A8(&D_800DF7C4);
    func_80000BE0(0x10);
    func_800660D0();
    func_800C422C(2);
    func_80000890(1);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuOptionsInit.s")
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
    func_8009C4A8(&D_800DFA2C);
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuSaveOptionsInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800853D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80085B9C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800860A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800861C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800862C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800867D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80086A48.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80086AFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800871D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800874D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800875E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800876CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80087734.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuSaveOptionsLoop.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80087EB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80087F14.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008832C.s")


/*
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
*/
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuBootInit.s")

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuBootLoop.s")

void func_800887C4(void) {
    func_8009C4A8(&D_800DF7C4);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800887E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80088938.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800890AC.s")

void func_800895A4(void) {
    func_8009C508(0x3F);
    func_80071140(D_80126AA0);
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuMagicCodesInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800896A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuMagicCodesLoop.s")

void func_8008A4C8(void) {
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuMagicCodesListInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008A56C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008A8F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuMagicCodesListLoop.s")

void func_8008AD1C(void) {
    func_8009C508(0x3F);
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008AD44.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008AEB4.s")
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
    func_8009C4A8(&D_800DFDC8);
    func_800710B0(0);
    func_800C422C(2);
    func_800710B0(2);
    D_800DFFD0 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008C168.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuCautionInit.s")
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
    func_8009C4A8(&D_800E0398);
    func_8007FF88();
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8008E45C.s")
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
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80090ED8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80090F30.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80092188.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80092BE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLoadNewAreaInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80092E94.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuLoadNewAreaLoop.s")

void func_80093A0C(void) {
    func_8009C4A8(&D_800E0FB4);
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094604.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094688.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094A5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094C14.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80094D28.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80095624.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80095728.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80096790.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/Menu11Init.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80096978.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/Menu11Loop.s")

void func_800976CC(void) {
    func_8009C4A8(&D_800E0A24);
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800976F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80097744.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800977D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80097874.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80097918.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80097D10.s")

void func_800981E8(void) {
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80098208.s")
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
    func_8009C4A8(&D_800E1024);
    func_800C422C(2);
}

s32 func_8009962C(void) {
    return D_800E0FE8;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009963C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_800998E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuGhostDataInit.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_80099E8C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/MenuGhostDataLoop.s")

void func_8009ABAC(void) {
    func_8009C4A8(&D_800E1708);
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009ABD8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/Menu17Init.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/Menu17Loop.s")

void func_8009AF18(void) {
    if (D_80126804 != 0) {
        func_8009C4A8(&D_800E1768);
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
    func_8009C4A8(&D_800E17D8);
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
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C154.s")

s32 func_8009C1A0(void) {
    return D_800DF4CC;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C1B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C228.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C250.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C274.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C280.s")

s32 func_8009C2D0(void) {
    return D_800DF4B8;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C2E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C30C.s")

s32 func_8009C3C8(void) {
    return D_800DF4BC;
}

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C3D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C440.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C490.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C4A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C508.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C674.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C6D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C8A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009C904.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009CA60.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009CD7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009CF68.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009CFB0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009CFEC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009D118.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009D1B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009D26C.s")
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

GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009E9B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EA6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EA78.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EABC.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EB08.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EB20.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EB94.s")
GLOBAL_ASM("asm/non_matchings/unknown_080500/func_8009EC60.s")

s32 func_8009EC70(void) {
    return D_800DF494;
}

s32 func_8009EC80(void) {
    if (func_8009C2D0() != 0) {
        return 0;
    }
    return D_800DF4C0;
}

s32 is_tt_unlocked(void) {
    return gActiveMagicCodes & 1;
}

s32 is_drumstick_unlocked(void) {
    return gActiveMagicCodes & 2;
}
