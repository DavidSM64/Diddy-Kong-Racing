/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B6E50 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "menu.h"

/************ .rodata ************/

const char D_800E8E70[] = "\nAssertion failed: '%s' in file %s, line %d\n";
const char D_800E8EA0[] = "\nAssertion failed: '%s' in file %s, line %d\n";
const char D_800E8ED0[] = ">fault< ";
const char D_800E8EDC[] = "CORE";
const u8 D_800E8EE4[4] = { 0, 0, 0, 0 };
const char D_800E8EE8[] = "CORE";
const u8 D_800E8EF0[4] = { 0, 0, 0, 0 };
const char D_800E8EF4[] = "CORE";
const u8 D_800E8EFC[4] = { 0, 0, 0, 0 };

/*********************************/

/************ .data ************/

s32 D_800E3020 = -1;
s32 D_800E3024 = 0;
s32 D_800E3028 = 0;

char *D_800E302C[3] = {
    "setup", "control", "print"
};

/*******************************/

/************ .bss ************/

/* Size: 0x1B0 bytes */
typedef struct epcInfo {
/*  0x00 */ s32 unk0;
/*  0x04 */ s32 unk4;
/*  0x08 */ s32 unk8;
/*  0x0C */ s32 unkC;
/*  0x10 */ s32 unk10;
/*  0x14 */ s32 thread;
/*  0x18 */ s32 unk18;
/*  0x1C */ s32 unk1C;
/*  0x20 */ s64 at;
/*  0x28 */ s64 v0;
/*  0x30 */ s64 v1;
/*  0x38 */ s64 a0;
/*  0x40 */ s64 a1;
/*  0x48 */ s64 a2;
/*  0x50 */ s64 a3;
/*  0x58 */ s64 t0;
/*  0x60 */ s64 t1;
/*  0x68 */ s64 t2;
/*  0x70 */ s64 t3;
/*  0x78 */ s64 t4;
/*  0x80 */ s64 t5;
/*  0x88 */ s64 t6;
/*  0x90 */ s64 t7;
/*  0x98 */ s64 s0;
/*  0xA0 */ s64 s1;
/*  0xA8 */ s64 s2;
/*  0xB0 */ s64 s3;
/*  0xB8 */ s64 s4;
/*  0xC0 */ s64 s5;
/*  0xC8 */ s64 s6;
/*  0xD0 */ s64 s7;
/*  0xD8 */ s64 t8;
/*  0xE0 */ s64 t9;
/*  0xE8 */ s64 gp;
/*  0xF0 */ s64 sp;
/*  0xF8 */ s64 s8;
/* 0x100 */ s64 ra;
/* 0x108 */ s32 unk108;
/* 0x10C */ s32 unk10C;
/* 0x110 */ s32 unk110;
/* 0x114 */ s32 unk114;
/* 0x118 */ s32 sr;
/* 0x11C */ s32 epc;
/* 0x120 */ s32 cause;
/* 0x124 */ s32 badvaddr;
/* 0x128 */ s32 unk128;
/* 0x12C */ s32 unk12C;
/* 0x130 */ f32 unk130;
/* 0x134 */ f32 unk134;
/* 0x138 */ f32 unk138;
/* 0x13C */ u8 pad13C[0x74];
} epcInfo;

epcInfo gEpcInfo;
s32 D_801299B0[64];

extern s32 D_80129BB0[256];

/******************************/

s16 *func_80024594(s32 *arg0, s32 *arg1);

void thread0(s32 arg0);
void func_800B70D0(void);
void func_800B7144(void);
void func_800B71B0(void);

extern OSThread D_801295E0;
extern OSMesgQueue D_80129790;
extern OSMesg D_801297A8;
extern OSMesgQueue D_801297E8;
extern OSMesg D_801297C8;

extern s32 D_80129FB0[3];

extern u16 D_80127CAC;
extern u16 D_80127CAE;
extern s32 D_80127CBC;
extern s32 D_80127CC0;
extern s32 D_80127CC4;
extern s32 D_80127CC8;
extern u16 D_80127CD0;
extern u16 D_80127CD2;

void func_800B6E50(void) {
    if (D_80127CD0 < 0x141) {
        D_80127CBC = 0x10;
        D_80127CC0 = D_80127CD0 - 0x10;
    } else {
        D_80127CBC = 0x20;
        D_80127CC0 = D_80127CD0 - 0x20;
    }
    if (D_80127CD2 < 0xF1) {
        D_80127CC4 = 0x10;
        D_80127CC8 = D_80127CD2 - 0x10;
    } else {
        D_80127CC4 = 0x20;
        D_80127CC8 = D_80127CD2 - 0x20;
    }
}



void func_800B6EE0(void) {
    D_80127CAC = D_80127CBC;
    D_80127CAE = D_80127CC4;
}

void func_800B6F04(void) {
    D_80127CAC = D_80127CBC;
    D_80127CAE += 11;
}

void func_800B6F30(s32 arg0, s32 arg1, s32 arg2) {
}

void func_800B6F40(s32 arg0, s32 arg1, s32 arg2) {
}

#ifdef NON_MATCHING
void func_800B6F50(void) {
    s32 i;
    
    // Almost matching, just have an issue with argument 4.
    // The -O2 compiler is too smart. :(
    osCreateThread(&D_801295E0, 0, &thread0, 0, &D_801295E0, 255);
    
    osStartThread(&D_801295E0);
    
    for(i = 0; i < 3; i++) {
        D_80129FB0[i] = -1;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F50.s")
#endif

#ifdef NON_MATCHING
void thread0(s32 arg0) { // Has regalloc issues
    s32 sp34;
    s32 s0 = 0;
    
    osCreateMesgQueue(&D_80129790, &D_801297A8, 8);
    osSetEventMesg(12, &D_80129790, 8);
    osSetEventMesg(10, &D_80129790, 2);
    osCreatePiManager(150, &D_801297E8, &D_801297C8, 8);
    
    while(1) {
        while(1) {
            osRecvMesg(&D_80129790, &sp34, 1);
            if (!(get_filtered_cheats() & CHEAT_EPC_LOCK_UP_DISPLAY)) {
                continue;
            }
            s0 |= sp34;
            if ((s0 & 8) || (s0 & 2)) {
                break;
            }
        }
        s0 &= ~8;
        func_800B70D0();
        func_800B7144();
        func_800B71B0();
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/thread0.s")
#endif

/* Unknown Size, might be epcInfo? */
typedef struct unk800D2470 {
/*  0x00 */ OSThread *thread;
/*  0x04 */ s32 unk4;
/*  0x08 */ s32 unk8;
/*  0x0C */ struct unk800D2470 *next;
/*  0x10 */ u8 pad10[0x108];
/* 0x118 */ s32 unk118;
} unk800D2470;

void func_800B70D0(void) {
    unk800D2470 *node = func_800D2470();
    while(node->unk4 != -1) {
        if (node->unk4 == 0) {
            node->unk118 &= 0xFFFF00FE;
            node->unk118 |= 0x6C01;
            return;
        }
        node = node->next;
    }
}

void func_800B7144(void) {
    s32 temp_v0_2;
    s32 phi_v0;
    s32 phi_return;
    unk800D2470 *node = func_800D2470();
    while (node->unk4 != -1) {
        if ((node->unk4 > 0) && (node->unk4 < 0x80)) {
            osStopThread(&node->thread);
        }
        node = node->next;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B71B0.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7460.s")
#else

void func_800B7460(s32 *epc, s32 size, s32 mask) {
    epcInfo sp840;
    s16 sp440[0x200];
    u8 sp240[0x200];
    epcInfo sp40;
    s32 sp38;
    s16 *v0;
    s32 i;

    if ((get_filtered_cheats() << 4) < 0) { // This is checking if the EPC cheat is active
        memzero(&sp840, 0x1B0);
        sp840.a0 = size;
        sp840.a1 = mask;
        sp840.epc = epc;
        sp840.cause = -1;
        sp840.unk130 = D_80129FB0[0];
        sp840.unk134 = D_80129FB0[1];
        sp840.unk138 = D_80129FB0[2];
        bcopy(&sp840, &sp40, 0x1B0);
        memzero(&sp240, 0x200);
        v0 = func_80024594(&sp38, &size);
        for (i = 0; i < size; i++) {
            sp440[i] = v0[sp38];
            sp38--;
            if (sp38 < 0) {
                sp38 += size;
            }
        }
        func_800766D4(0, -1, &D_800E8EE8, &D_800E8EF0, &sp40, 0x800);
        while(1); // Infinite loop; waiting for the player to reset the console?
    }
}
#endif

void func_800B76B8(s32 arg0, s32 arg1) {
    if ((arg0 >= 0) && (arg0 < 3)) {
        D_80129FB0[arg0] = arg1;
    }
}

s32 func_800B76DC(void) {
    s32 sp824;
    u8 sp820[4]; // Unused?
    s16 sp420[0x200];
    u8 sp220[0x200];
    u8 sp1D0[0x50]; // Unused?
    epcInfo sp20;
    
    if (D_800E3020 != -1) {
        return D_800E3020;
    } else {
        D_800E3020 = 0;
        if ((func_800758DC(0) == 0) && (func_800764E8(0, &D_800E8EF4, &D_800E8EFC, &sp824) == 0) 
            && (func_80076610(0, sp824, &sp20, 0x800) == 0)) {
            bcopy(&sp20, &gEpcInfo, 0x1B0);
            bcopy(&sp220, &D_801299B0, 0x200);
            bcopy(&sp420, &D_80129BB0, 0x400);
            D_800E3020 = 1;
        }
        func_80075AEC(0);
        if (D_800E3020 != 0) {
            func_800762C8(0, sp824);
        }
        return D_800E3020;
    }
}

void func_800B77D4(s32 arg0) {
    D_800E3028 += arg0;
    if (D_800E3028 >= 0x3D) {
        D_800E3028 = 0;
        D_800E3024++;
    }
}


#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/render_epc_lock_up_display.s")
#else
void render_epc_lock_up_display(void) {
    char *sp50[3];
    s32 s3;
    s32 i, j;

    sp50[0] = D_800E302C[0]; // "setup"
    sp50[1] = D_800E302C[1]; // "control"
    sp50[2] = D_800E302C[2]; // "print"
    
    s3 = 0;
    
    func_800B635C(0x10, 0x20);
    
    switch (D_800E3024) {
        case 0:
            D_80129FB0[0] = gEpcInfo.unk130;
            D_80129FB0[1] = gEpcInfo.unk134;
            D_80129FB0[2] = gEpcInfo.unk138;
            if (gEpcInfo.cause != -1) {
                render_printf(" Fault in thread %d\n", gEpcInfo.thread);
                render_printf(" epc\t\t0x%08x\n", gEpcInfo.epc);
                render_printf(" cause\t\t0x%08x\n", gEpcInfo.cause);
                render_printf(" sr\t\t0x%08x\n", gEpcInfo.sr);
                render_printf(" badvaddr\t0x%08x\n", gEpcInfo.badvaddr);
                for(i = 0; i < 3; i++) {
                    if (D_80129FB0[i] != -1) {
                        if (s3 == 0) {
                            s3 = 1;
                            render_printf(" object\t\t");
                        }
                        render_printf("%s %d ", sp50[i], D_80129FB0[i]);
                    }
                }
                render_printf("\n");
                render_printf(" at 0x%08x v0 0x%08x v1 0x%08x\n", gEpcInfo.at, gEpcInfo.v0, gEpcInfo.v1);
                render_printf(" a0 0x%08x a1 0x%08x a2 0x%08x\n", gEpcInfo.a0, gEpcInfo.a1, gEpcInfo.a2);
                render_printf(" a3 0x%08x t0 0x%08x t1 0x%08x\n", gEpcInfo.a3, gEpcInfo.t0, gEpcInfo.t1);
                render_printf(" t2 0x%08x t3 0x%08x t4 0x%08x\n", gEpcInfo.t2, gEpcInfo.t3, gEpcInfo.t4);
                render_printf(" t5 0x%08x t6 0x%08x t7 0x%08x\n", gEpcInfo.t5, gEpcInfo.t6, gEpcInfo.t7);
                render_printf(" s0 0x%08x s1 0x%08x s2 0x%08x\n", gEpcInfo.s0, gEpcInfo.s1, gEpcInfo.s2);
                render_printf(" s3 0x%08x s4 0x%08x s5 0x%08x\n", gEpcInfo.s3, gEpcInfo.s4, gEpcInfo.s5);
                render_printf(" s6 0x%08x s7 0x%08x t8 0x%08x\n", gEpcInfo.s6, gEpcInfo.s7, gEpcInfo.t8);
                render_printf(" t9 0x%08x gp 0x%08x sp 0x%08x\n", gEpcInfo.t9, gEpcInfo.gp, gEpcInfo.sp);
                render_printf(" s8 0x%08x ra 0x%08x\n\n", gEpcInfo.s8, gEpcInfo.ra);
            } else { // gEpcInfo.cause == -1
                render_printf(" epc\t\t0x%08x\n", gEpcInfo.epc);
                render_printf(" cause\t\tmmAlloc(%d,0x%8x)\n", gEpcInfo.a0, gEpcInfo.a1);
                for(i = 0; i < 3; i++) {
                    if (D_80129FB0[i] != -1) {
                        if (s3 == 0) {
                            s3 = 1;
                            render_printf(" object\t\t");
                        }
                        render_printf("%s %d ", sp50[i], D_80129FB0[i]);
                    }
                }
                render_printf("\n");
                render_printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                render_printf(" s8 0x%08x ra 0x%08x\n\n", gEpcInfo.s8, gEpcInfo.ra);
                render_printf("\n");
            }
            break;
        default:
            for (i = 0; i < 16; i++) {
                render_printf("   %08x %08x %08x\n", 
                    D_801299B0[i - 1], D_801299B0[i - 1 + 16], D_801299B0[i - 1 + 32]);
            }
            break;
        case 4:
            for (i = 0; i < 16; i++) {
                render_printf("  ");
                for (j = 0; j < 8; j++) {
                    render_printf("%04x ", D_80129BB0[(i * 16) + j - 2]);
                }
                render_printf("\n");
            }
            break;
        case 5:
            D_800E3024 = 0;
            break;
    }
}
#endif
