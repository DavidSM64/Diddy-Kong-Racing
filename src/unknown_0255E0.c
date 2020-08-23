/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800249E0 */

#include "types.h"
#include "macros.h"
#include "structs.h"

typedef struct{
u8 pad00[0x49];
s8 unk49;
} unk800DC91C;

/* Size: 0x44 bytes */
typedef struct unk80120AC0 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8  pad6[6];
    f32 x_position;
    f32 y_position;
    f32 z_position;
    f32 pad18;
    f32 unk1C;
    f32 pad20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    s16 unk34;
    s16 pad36;
    s16 unk38;
    s8  pad3A;
    s8  unk3B;
    u8  pad3C[8];
} unk80120AC0;

extern unk800DC91C* D_800DC91C;
extern s32 D_800DC924;
extern s32 D_8011D37C;
extern s32 D_8011D474;

extern s32 D_8011B0A0;
extern s32 D_8011B0A4;
extern s32 D_8011B0A8;

typedef struct{
    Player * unk00;
} unk8011B0B8;

extern unk8011B0B8 D_8011B0B8;

extern s32 D_8011B0DC;
extern s32 D_8011B0F0;
extern s32 D_8011B0F4;
extern s32 D_8011B0FC;

extern f32 D_8011B0E4;
extern f32 D_8011B0E8;
extern f32 D_8011B0EC;

typedef struct{
    u8 pad00[0x12];
    u16 unk12;
    u16 unk14;
} unk800DC918_00_00;

typedef struct{
    unk800DC918_00_00 *unk00;
    u8 pad00[0x04];
} unk800DC918_00;

typedef struct{
    u8 unk00;
    u8 pad01[0x05];
    u8  unk06;
    u8  unk07;
    u32 unk08;  
} unk800DC918_04_0C;

typedef struct{
    u8 pad00[0x0C];
    unk800DC918_04_0C* unk0C;
    u8 pad0C[0x10];
    s16 unk20;
    u8 pad24[0x20];
} unk800DC918_04;

typedef struct{
    s16 unk00;
    u8 pad02[0x02];
    s16 unk04;  
    s16 unk06;
    u8 pad08[0x02];
    s16 unk0A;
} unk800DC918_08;

typedef struct{
    unk800DC918_00 *unk00;
    unk800DC918_04 *unk04;
    unk800DC918_08 *unk08;
    u8 pad0C[0x0E];
    s16 unk08_count;
} unk800DC918;

extern unk800DC918* D_800DC918;

s32 func_800249E0(s32 arg0) {
    D_8011D37C = arg0;
    return 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800249F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/D_80024D54.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80025510.s")

void func_800257D0(void) {
    if (D_800DC924 != 0) {
        func_80071140(D_8011D474);
        func_80071140(D_800DC924);
        D_800DC924 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002581C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026070.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026430.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026C14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026E54.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027184.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027568.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800278E8.s")
#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027E24.s")
#else
typedef struct{
    u32 unk00;
    u8 pad04[0x10];
    u32 unk14;

}unk80027E24_sp58;

void func_80027E24(u32 arg0){
    unk80027E24_sp58 sp58;
    unk800DC918_04 *s6;
    unk800DC918_04_0C * s0;
    unk800DC918_04_0C * s5;
    unk800DC918_00_00 * tmp_a0;
    s32 i;//sp_6c
    s32 j;
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027FC4.s")

void func_80028044(s32 arg0) {
    D_8011B0DC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028050.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800289B8.s")

void func_80028C10(void){
    unk80120AC0 * v0_some_struct;
    if(D_8011B0B8.unk00 == NULL)
        return;

    v0_some_struct = func_80069D20();
    if(D_800DC91C->unk49 == 0){
        D_8011B0B8.unk00->x_position = v0_some_struct->x_position;
        D_8011B0B8.unk00->y_position = v0_some_struct->y_position;
        D_8011B0B8.unk00->z_position = v0_some_struct->z_position;
    }

    func_80068408(&D_8011B0A0, &D_8011B0A4);
    if(D_8011B0DC){
        func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, D_8011B0B8.unk00);
    }
}
#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028CD0.s")
#else

#endif


void func_80028FA0(s32 arg0) {
    D_8011B0FC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028FAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029658.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029AF8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029D14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029F18.s")

s32 func_8002A05C(s32 arg0, s32 arg1, s32* arg2){
    s32 i;
    s32 cnt = 0;
    unk800DC918_08 * a0;
    for(i = 0; i < D_800DC918->unk08_count; i++){
        a0 = D_800DC918->unk08 + i;
        if(arg0 < a0->unk06 + 4 && a0->unk00 - 4 < arg0
        && arg1 < a0->unk0A + 4 && a0->unk04 - 4 < arg1
        ){
            *arg2 = i;
            cnt++;
            arg2++;
        }

    }
    return cnt;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A134.s")

unk800DC918_08 *func_8002A2DC(s32 arg0){
    if(arg0 < 0 || D_800DC918->unk08_count < arg0)
        return NULL;

    return D_800DC918->unk08 + arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A31C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A5F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A900.s")

void func_8002ACC8(s32 arg0) {
    D_8011B0F4 = arg0;
}

s32 func_8002ACD4(f32* arg0, f32* arg1, f32* arg2) {
    *arg0 = D_8011B0E4;
    *arg1 = D_8011B0E8;
    *arg2 = D_8011B0EC;
    return D_8011B0F0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002AD08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002B0F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002B9BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002BAB0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C0C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C71C.s")

unk800DC918* func_8002C7C4(void) {
    return D_800DC918;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C7D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C954.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002CC30.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D30C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D384.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D670.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D8DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002DE30.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E234.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E904.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002EEEC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F2AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F440.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FA64.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FD74.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FF6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800304C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030664.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030750.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800307BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030838.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8003093C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030A74.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030DE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80031018.s")
