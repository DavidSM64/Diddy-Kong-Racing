/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D3820 */

#include "types.h"
#include "macros.h"

s32 D_800E48A0[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D43F0/alCopy.s")


char D_800E48C0[36] = "                                ";
char D_800E48E4[32] = "00000000000000000000000000000000";

/************ .rodata ************/

const char D_800E96C0[] = "hlL";
const char D_800E96C4[] = " +-#0";
const int D_800E96CC[] = { 1, 2, 4, 8, 16, 0 };

// Jump table in _Putfld
const u32 D_800E96E4[] = {
    0x800D3C08, 0x800D3EE8, 0x800D3C08, 0x800D3EE8, 
    0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 
    0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 
    0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 
    0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 0x800D3AB8, 
    0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 
    0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 
    0x800D3EE8, 0x800D3EE8, 0x800D3910, 0x800D3948, 
    0x800D3C08, 0x800D3C08, 0x800D3C08, 0x800D3EE8, 
    0x800D3948, 0x800D3EE8, 0x800D3EE8, 0x800D3EE8, 
    0x800D3EE8, 0x800D3D6C, 0x800D3AB8, 0x800D3E3C, 
    0x800D3EE8, 0x800D3EE8, 0x800D3E84, 0x800D3EE8, 
    0x800D3AB8, 0x800D3EE8, 0x800D3EE8, 0x800D3AB8
};

/*********************************/

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D43F0/_Putfld.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D43F0/_Printf.s")