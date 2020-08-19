/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80077450 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"


extern u32 D_800DE4C0;
extern u32 D_800DE4C4;
extern u32 D_800DE4C8;

extern u32 D_800DE4D0;

extern OSMesgQueue  D_80125EA0;
extern OSMesg       D_80125EB8;
extern OSMesgQueue  D_80125EC0;
extern OSMesgQueue  D_80125ED8;
extern OSMesg       D_80125EF0;
extern OSMesg       D_80125F10;

extern u32 D_80126100;

GLOBAL_ASM("asm/non_matchings/unknown_078050/setupOSTasks.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077A54.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077B34.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077B5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077B9C.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078054.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_800780DC.s")

void func_80078100(void){
    D_80126100 = func_8007957C();
    osCreateMesgQueue(&D_80125EA0, &D_80125EB8,1);
    osCreateMesgQueue(&D_80125EC0, &D_80125EF0,8);
    osCreateMesgQueue(&D_80125ED8, &D_80125F10,8);
    
}

void func_80078170(u32 arg0, u32 arg1, u32 arg2){
    D_800DE4C4 = arg0;
    D_800DE4C8 = arg1;
    D_800DE4C0 = arg2 << 2;
}


GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078190.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_800787FC.s")

void func_80078AAC(u32 arg0){
    D_800DE4D0 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078AB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078D00.s")
