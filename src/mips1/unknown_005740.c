/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80004B40 */

#include "types.h"
#include "macros.h"

extern s8 D_800DC71C;
extern s8 D_800DC73C;
extern s8 D_800DC740;
extern s8 D_800DC748;
extern s8 D_8011AD20;
extern s8 D_8011AE02;
extern s8 D_8011AE03;
extern u8 D_8011AEF4;

extern s16 D_800DC708;

extern s32 osTvType;

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80004B40.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800050D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005254.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005D08.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800063EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006AC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006BFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006FC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80007FA4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008040.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008140.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008168.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008174.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008438.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800090C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800092A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009558.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800095E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800096D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800096F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000974C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800098A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009968.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800099EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009AB4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009B7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009D6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A2E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A414.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A71C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A7C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A84C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A8D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A9F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000AA88.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000AAAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000AB00.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000AC34.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000ACE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000AD98.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000ADF4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000AE90.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000AEFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000B010.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000B020.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000B290.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000B38C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000B750.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000BADC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000BF44.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000BF8C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000C2D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000C460.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000C604.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000C718.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000C844.s")

s32 func_8000C8B4(s32 arg0) {
    if (osTvType != 0 || arg0 < 0) {
        return arg0;
    }
    else {
        return (arg0 * 5) / 6;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000C8F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000CBC0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000CBF0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000CC20.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000CC7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000E0B0.s")

void func_8000E128(void) {
    D_800DC708 = 0x8000;
}

s8 func_8000E138(void) {
    return D_8011AD20;
}

s8 func_8000E148(void) {
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

s8 func_8000E184(void) {
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

s8 func_8000E1DC(void) {
    return D_8011AE03;
}

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000E1EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000E2B4.s")

void func_8000E4BC(s32 arg0) {
    D_8011AEF4 = arg0;
}

u8 func_8000E4C8(void) {
    return D_8011AEF4;
}

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000E4D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000E948.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000E988.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000E9D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000EA54.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000F648.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000F758.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000F7EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000F99C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000FAC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000FBCC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000FC6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000FD20.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000FD34.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000FD54.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000FFB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001004C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800101AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80010994.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80011134.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80011264.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80011390.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001139C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800113AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800113CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80011560.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80011570.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80011960.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80011AD0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80011C94.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800120C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80012C30.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80012C3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80012C98.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80012CE8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80012D5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80012E28.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80012F30.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80012F94.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001348C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80013548.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800135B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800138A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80013A0C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80013DCC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80014090.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800142B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800143A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80014814.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80014B50.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80015348.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800155B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800159C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80016500.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80016748.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80016BC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80016C68.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80016DE8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001709C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80017248.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001790C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80017978.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800179D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80017A18.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80017E74.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80017E98.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800185E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80018C6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80018CE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001955C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/D_80019808.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001A7D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001A8D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001A8F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001AE44.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001AE54.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001AE64.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B288.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B2E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B2F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B3AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B3C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B4FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B640.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B650.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B668.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B738.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B780.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B790.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B7A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001B834.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BA00.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BA1C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BA64.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BA74.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BA90.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BAAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BAC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BB18.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BC40.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BC54.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BD94.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BDD4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001BF20.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001C418.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001C48C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001C524.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001C6C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001CC48.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001CD28.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001D1AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001D1BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001D214.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001D258.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001D4B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001D5E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001D6E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001D80C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001DD54.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E29C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E2EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E344.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E36C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E440.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E450.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E45C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E4C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E6EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E89C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001E93C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001EE74.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001EFA4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001F23C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001F3B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001F3C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001F3EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001F450.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8001F460.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800210CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80021104.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8002125C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80021400.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800214C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800214E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80021600.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80022540.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8002263C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8002277C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80022888.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800228B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800228EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80022948.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80022CFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80022E18.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800230D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8002341C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8002342C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80023568.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800235C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800235D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800235DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800238BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80023E30.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80023F48.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80024594.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800245B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800245F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80024744.s")
