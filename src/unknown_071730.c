/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80070B30 */

#include "unknown_071730.h"

#include "types.h"
#include "macros.h"

/* Size: 0x8 bytes */
typedef struct unk80070BE4_8_0 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
} unk80070BE4_8_0;
    
/* Size: 0x14 bytes */
typedef struct unk80070BE4_8 {
    unk80070BE4_8_0 *unk0; 
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8  pad10[0x4];
} unk80070BE4_8;

/* Size: 0x10 bytes */
typedef struct unk80070BE4 {
    s32 unk0;
    s32 unk4;
    unk80070BE4_8 *unk8;
    s32 size;
} unk80070BE4;

extern unk80070BE4 D_80123580[12]; // unknown number of entries

#ifndef _ALIGN16
    #define _ALIGN16(val) ((val) & 0xFFFFFFF0) + 0x10
#endif

extern s32 D_801235C0;

/* Size: 0x8 bytes */
typedef struct unk801235C8 {
    u32 unk0;
    s8 unk4;
    u8 pad5[3];
} unk801235C8;

extern unk801235C8 D_801235C8[8];

extern s32 D_80123DC8;
extern s32 D_80123DCC;
extern unk80070BE4_8 D_8012D3F0;

/* Unknown size */
typedef struct unk800B7D10 {
    u8 pad0[0x14];
    s32 unk14;
} unk800B7D10;

unk800B7D10 *func_800B7D10(void);
void *func_80070D3C(s32, s32, s32);

unk80070BE4_8 *func_80070BE4(unk80070BE4_8 *arg0, s32 size, s32 arg2);
void func_800710B0(s32);
void* func_80070C9C(s32, s32);
s32 *func_8006F510(void);
void func_8006F53C(s32*);

void func_80071440(s32 arg0);


void func_80070B30(void) {
    s32 tmp = -1;
    D_801235C0 = tmp;
    if(1){
        func_80070BE4(&D_8012D3F0, 0x80400000 - (s32)(&D_8012D3F0), 1600);
    }
    func_800710B0(2);
    D_80123DC8 = 0;
}

s32 *func_80070B78(s32 arg0, s32 arg1) {
    s32 temp3;
    unk80070BE4_8 * temp4;
    s32 unused_2;
    s32 *temp = func_8006F510();
    s32 *temp2;

    temp3 = arg0 + (arg1 * sizeof(unk80070BE4_8));
    temp4 = (unk80070BE4_8 *)func_80070C9C(temp3, -1);
    temp2 = func_80070BE4(temp4, temp3, arg1);
    func_8006F53C(temp);
    return temp2;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80070BE4.s")
#else
unk80070BE4_8 *func_80070BE4(unk80070BE4_8 *arg0, s32 size, s32 arg2) {
    s32 i;
    unk80070BE4 *temp;
    unk80070BE4_8 *temp2;
    unk80070BE4_8_0 *temp3;
    s32 tmp = ++D_801235C0;
    //s32 tmp2;

    temp = D_80123580 + tmp;
    temp->unk0 = arg2;
    temp->unk4 = 0;
    temp->unk8 = arg0;
    temp->size = size;
    
    
    for(i = 0; i < temp->unk0; i++) {
        arg0[i].unkE = i;
    }
    
    temp2 = temp->unk8;
    temp3 = (unk80070BE4_8_0 *)&arg0[arg2];
    if((s32)temp3 & 0xF) {
        temp2->unk0 = (unk80070BE4_8_0 *)_ALIGN16((s32)temp3);
    } else {
        temp2->unk0 = temp3;
    }

    temp2->unk4 = size - (arg2 * sizeof(unk80070BE4_8));
    temp2->unk8 = 0;
    temp2->unkA = -1;
    temp2->unkC = -1;
    temp->unk4++;
    
    return temp->unk8;
}
#endif

void *func_80070C9C(s32 arg0, s32 arg1) {
    void *temp_v0;
    if (arg0 == 0) {
        func_800B7460(func_800B7D10()->unk14, arg0, arg1);
    }
    temp_v0 = func_80070D3C(0, arg0, arg1);
    if (temp_v0 == (void *)NULL) {
        func_800B7460(func_800B7D10()->unk14, arg0, arg1);
    }
    return temp_v0;
}

void func_80070D10(s32 arg0, s32 arg1) {
    func_80070D3C(0, arg0, arg1);
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80070D3C.s")
#else
    
void *func_80070D3C(s32 arg0, s32 arg1, s32 arg2) {
    unk80070BE4 *temp;
    unk80070BE4_8 *temp2;
    s32 phi_a0;
    s32 phi_a2;
    s32 phi_s0;
    s32 *sp28;

    temp = &D_80123580[arg0];
    if ((temp->unk4 + 1) == temp->unk0) {
        func_8006F53C(sp28);
    } else {
        if (arg1 & 0xF) {
            arg1 = _ALIGN16(arg1); //(arg1 & -0x10) + 0x10;
        }
        phi_a0 = 0;
        phi_a2 = 0x7FFFFFFF;
        phi_s0 = -1;
        while(phi_a0 != -1) {
            temp2 = &temp->unk8[phi_a0];
            if (temp2->unk8 == 0 && temp2->unk4 >= arg1 && temp2->unk4 < phi_a2) {
                phi_s0 = phi_a0;
                phi_a2 = temp2->unk4;
            }
            phi_a0 = temp2->unkC;
        }
        if (phi_s0 != -1) {
            func_8007178C(arg0, phi_s0, arg1, 1, 0, arg2);
            func_8006F53C(sp28);
            return (void *)(&temp->unk8[phi_s0]);
        }
        func_8006F53C(sp28);
    }
    return (void *)NULL;
}
#endif

void *func_80070E90(unk80070BE4_8 *arg0, s32 arg1) {
    s32 i;
    for(i = D_801235C0; i != 0; i--) {
        if (arg0 == D_80123580[i].unk8) {
            return func_80070D3C(i, arg1, 0);
        }
    }
    return (void *)NULL;
}

GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80070EF8.s")

void func_800710B0(s32 arg0) {
    s32 *sp2C = func_8006F510();
    D_80123DCC = arg0;
    if (arg0 == 0) {
        while (D_80123DC8 > 0) {
            func_80071278(D_801235C8[--D_80123DC8].unk0);
        }
    }
    func_8006F53C(sp2C);
}

void func_80071140(s32 arg0) {
    s32 *sp1C = func_8006F510();
    if (D_80123DCC == 0) {
        func_80071278(arg0);
    } else {
        func_80071440(arg0);
    }
    func_8006F53C(sp1C);
}

GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80071198.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80071278.s")

void func_80071440(s32 arg0) {
    D_801235C8[D_80123DC8].unk0 = arg0;
    D_801235C8[D_80123DC8].unk4 = D_80123DCC;
    D_80123DC8++;
}

GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80071478.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80071538.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_800715EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_8007164C.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_8007178C.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80071850.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80071A24.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80071D30.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80071E58.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_80071F80.s")
GLOBAL_ASM("asm/non_matchings/unknown_071730/func_800720DC.s")
