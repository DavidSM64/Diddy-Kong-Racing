/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80072250 */

#include "unknown_072E50.h"

#include "types.h"
#include "macros.h"

/************ .data ************/

s32 D_800DE440 = 0;
char D_800DE444[68] = "\0               0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#'*+,-./:=?@";
s32 D_800DE488 = 0; // Currently unknown, might be a different type. 
s32 D_800DE48C = 0;

/*******************************/

/************ .rodata ************/

const char D_800E7590[] = "Region = %d	 loc = %x	 size = %x\t";
const char D_800E75B4[] = "FREE";
const char D_800E75BC[] = "ALLOCATED";
const char D_800E75C8[] = "ALLOCATED,FIXED";
const char D_800E75D8[] = "\n";
const char D_800E75DC[] = "\n";
const char D_800E75E0[] = "Region number = %d\t";
const char D_800E75F4[] = "maxSlots = %d\t";
const char D_800E7604[] = "slotsUsed = %d\t";
const char D_800E7614[] = "loc = %x\t";
const char D_800E7620[] = "size = %x\n";
const char D_800E762C[] = "\n";

const char D_800E7630[] = "DKRACING-ADV";
const char D_800E7640[] = "DKRACING-ADV";
const char D_800E7650[] = "DKRACING-TIMES";
const char D_800E7660[] = "DKRACING-TIMES";
const char D_800E7670[] = "DKRACING-ADV";
const char D_800E7680[] = "DKRACING-ADV";
const char D_800E7690[] = "DKRACING-TIMES";
const char D_800E76A0[] = "DKRACING-TIMES";

const char D_800E76B0[] = "WARNING : No Eprom\n";
const char D_800E76C4[] = "WARNING : No Eprom\n";
const char D_800E76D8[] = "WARNING : No Eprom\n";
const char D_800E76EC[] = "WARNING : No Eprom\n";
const char D_800E7700[] = "WARNING : No Eprom\n";
const char D_800E7714[] = "WARNING : No Eprom\n";
const char D_800E7728[] = "WARNING : No Eprom\n";

const char D_800E773C[] = "DKRACING-GHOSTS\0";
const char D_800E7750[] = "warning: corrupt ghost\n";

/*********************************/

/************ .bss ************/

extern s32 D_80124010;

/*******************************/

GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80072250.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80072298.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80072348.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80072424.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80072578.s")

void func_80072708(void) {
    D_800DE48C = 3;
}

GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80072718.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80072C54.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80072E28.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_8007306C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800732E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80073588.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800738A4.s")

s32 func_80073C4C(void) {
    return 0x100;
}

s32 func_80073C54(void) {
    return 0x200;
}

GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80073C5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80073E1C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80073F5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80074018.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80074148.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80074204.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_8007431C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800744DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800745D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800746F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_8007480C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80074874.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_8007497C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80074A4C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80074AA8.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80074B1C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80074B34.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80074EB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80075000.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800753D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800756D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800758DC.s")

s32 func_80075AEC(s32 arg0) {
    func_800CCFE0(D_80124010);
    return 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80075B18.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80075D38.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80075DC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80075E60.s")

void func_80076164(void) {
    if (D_800DE440 != 0) {
        func_80071140(D_800DE440);
    }
    D_800DE440 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80076194.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800762C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80076388.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800764E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80076610.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_800766D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80076924.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_8007698C.s")
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80076A38.s")

s32 func_80076AF4(s32 arg0, s32 arg1) {
    s32* temp;
    s32 pad;
    s32 ret;

    ret = 6;
    temp = func_80070C9C(0x100, 0xFF);
    if (func_80076610(arg0, arg1, temp, 0x100) == 0) {
        switch(*temp) {
            case 0x47414D44: // GAMD
                ret = 3;
                break;
            case 0x54494D44: // TIMD
                ret = 4;
                break;
            case 0x47485353: // GHSS
                ret = 5;
                break;
            default:
                ret = 6;
                break;
        }
    }
    func_80071140(temp);
    return ret;
}
