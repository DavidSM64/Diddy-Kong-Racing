/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80077450 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

extern u8 D_800DE4B0;
extern u8 D_800DE4B4;
extern u8 D_800DE4B8;

extern u32 D_800DE4C0;
extern u32 D_800DE4C4;
extern u32 D_800DE4C8;

extern u32 D_800DE4D0;

extern u32 D_800DE4E0;

extern OSMesgQueue  D_80125EA0;
extern OSMesg       D_80125EB8;
extern OSMesgQueue  D_80125EC0;
extern OSMesgQueue  D_80125ED8;
extern OSMesg       D_80125EF0;
extern OSMesg       D_80125F10;

extern u32 D_80126100;

GLOBAL_ASM("asm/non_matchings/unknown_078050/setupOSTasks.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077A54.s")

void func_80077B34(u8 arg0, u8 arg1, u8 arg2){
    D_800DE4B0 = arg0;
    D_800DE4B4 = arg1;
    D_800DE4B8 = arg2;
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077B5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077B9C.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078054.s")



#if 1
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_800780DC.s")
#else
typedef struct{
    u32 unk00;
    u32* unk04;
} struct_800780DC_a0;

void func_800780DC(struct_800780DC_a0** arg0){
    u32* tmp2= &D_800DE4E0;
    struct_800780DC_a0* tmp = *arg0;
    

    *arg0 = *arg0 + 1;
    tmp->unk00 = 0x6000000;
    tmp->unk04 = tmp2;
}
#endif


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
