/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B6E50 */

#include "thread0_epc.h"
#include "types.h"
#include "macros.h"
#include "menu.h"
#include "save_data.h"
#include "printf.h"
#include "objects.h"
#include "controller.h"
#include "game.h"
#include "stacks.h"

/************ .rodata ************/

const char D_800E8E70[] = "\nAssertion failed: '%s' in file %s, line %d\n";
const char D_800E8EA0[] = "\nAssertion failed: '%s' in file %s, line %d\n";
const char D_800E8ED0[] = ">fault< ";
const char D_800E8EDC[] = "CORE";
const char D_800E8EE4[4] = { 0, 0, 0, 0 };
const char sCoreFileName1[] = "CORE";
const char sCoreFileExt1[] = { 0, 0, 0, 0 };
const char sCoreFileName2[] = "CORE";
const char sCoreFileExt2[] = { 0, 0, 0, 0 };

/*********************************/

/************ .data ************/

s32 sLockupStatus = -1;
s32 sLockupPage = 0;
s32 sLockupDelay = 0;

char *D_800E302C[3] = {
    "setup", "control", "print"
};

/*******************************/

/************ .bss ************/

epcInfo gEpcInfo; //Very similar to __OSThreadContext
s32 D_801299B0[64];

/******************************/

extern OSThread D_801295E0;
extern OSMesgQueue D_80129790;
extern OSMesg D_801297A8;
extern OSMesgQueue D_801297E8;
extern OSMesg D_801297C8;

extern s32 D_80129FB0[3];

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

void func_800B6F30(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {}

// Only called from two libultra funcs for some reason. 
// This is likely an assert gone wrong.
// Called from alEnvMixerPull, and _pullSubFrame
// thread0_Assert("samples >= 0", "env.c", 104);
// thread0_Assert("samples <= AL_MAX_RSP_SAMPLES", "env.c", 105);
// thread0_Assert("source", "env.c", 373);
void thread0_Assert(UNUSED char *message, UNUSED char *fileName, UNUSED s32 lineNumber) {}

#ifdef NON_EQUIVALENT
void thread0_create(void) {
    s32 i;

    // Almost matching, just have an issue with argument 4.
    // The -O2 compiler is too smart. :(
    // It's possible D_801295E0 is a struct containing both the thread and stack pointer
    osCreateThread(&D_801295E0, 0, thread0_Main, NULL, &D_801295E0, OS_PRIORITY_MAX);

    osStartThread(&D_801295E0);

    for (i = 0; i < 3; i++) {
        D_80129FB0[i] = -1;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/thread0_epc/thread0_create.s")
#endif

#ifdef NON_EQUIVALENT
void thread0_Main(UNUSED void *unused) { // Has regalloc issues
    s32 sp34;
    s32 s0 = 0;

    osCreateMesgQueue(&D_80129790, &D_801297A8, 8);
    osSetEventMesg(12, &D_80129790, 8);
    osSetEventMesg(10, &D_80129790, 2);
    osCreatePiManager(150, &D_801297E8, &D_801297C8, 8);

    while (1) {
        while (1) {
            osRecvMesg(&D_80129790, &sp34, OS_MESG_BLOCK);
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
GLOBAL_ASM("asm/non_matchings/thread0_epc/thread0_Main.s")
#endif

void func_800B70D0(void) {
    OSThread *node = __osGetActiveQueue();
    while (node->priority != -1) {
        if (node->priority == 0) {
            node->context.sr &= 0xFFFF00FE;
            node->context.sr |= 0x6C01;
            break;
        }
        node = node->tlnext;
    }
}

void func_800B7144(void) {
    OSThread *node = __osGetActiveQueue();
    while (node->priority != -1) {
        if ((node->priority > 0) && (node->priority < 128)) {
            osStopThread((OSThread *)&node->next);
        }
        node = node->tlnext;
    }
}

GLOBAL_ASM("asm/non_matchings/thread0_epc/func_800B71B0.s")

#ifdef NON_EQUIVALENT
//Rename mask to colorTag?
void func_800B7460(s32 *epc, s32 size, s32 mask) {
    epcInfo sp840;
    s16 sp440[0x200];
    u8 sp240[0x200];
    epcInfo sp40;
    s32 sp38;
    s16 *v0;
    s32 i;

    if ((get_filtered_cheats() << 4) < 0) { // This is checking if the EPC cheat is active
        bzero(&sp840, 0x1B0);
        sp840.a0 = size;
        sp840.a1 = mask;
        sp840.epc = epc;
        sp840.cause = -1;
        sp840.unk130 = D_80129FB0[0];
        sp840.unk134 = D_80129FB0[1];
        sp840.unk138 = D_80129FB0[2];
        bcopy(&sp840, &sp40, 0x1B0);
        bzero(&sp240, 0x200);
        v0 = func_80024594(&sp38, &size);
        for (i = 0; i < size; i++) {
            sp440[i] = v0[sp38];
            sp38--;
            if (sp38 < 0) {
                sp38 += size;
            }
        }
        write_controller_pak_file(0, -1, sCoreFileName1, sCoreFileExt1, &sp40, 0x800);
        while (1); // Infinite loop; waiting for the player to reset the console?
    }
}
#else
GLOBAL_ASM("asm/non_matchings/thread0_epc/func_800B7460.s")
#endif

void func_800B76B8(s32 arg0, s32 arg1) {
    if ((arg0 >= 0) && (arg0 < 3)) {
        D_80129FB0[arg0] = arg1;
    }
}

//Called as a check to see if render_epc_lock_up_display should be called.
s32 get_lockup_status(void) {
    s32 fileNum;
    s32 controllerIndex = 0;
    s64 sp420[128]; // Overwrite epcStack?
    s64 sp220[64];
    u8 dataFromControllerPak[512]; //Looks to be sizeof(epcInfo), aligned to 64

    if (sLockupStatus != -1) {
        return sLockupStatus;
    } else {
        sLockupStatus = 0;
        // Looks like it reads EpcInfo data from the controller pak, which is interesting
        if ((get_si_device_status(controllerIndex) == CONTROLLER_PAK_GOOD) &&
            (get_file_number(controllerIndex, (char *)sCoreFileName2, (char *)sCoreFileExt2, &fileNum) == CONTROLLER_PAK_GOOD) &&
            (read_data_from_controller_pak(controllerIndex, fileNum, dataFromControllerPak, 2048) == CONTROLLER_PAK_GOOD))
        {
            bcopy(&dataFromControllerPak, &gEpcInfo, sizeof(epcInfo));
            bcopy(&sp220, &D_801299B0, sizeof(sp220));
            bcopy(&sp420, &D_80129BB0, sizeof(sp420));
            sLockupStatus = 1;
        }
        start_reading_controller_data(controllerIndex);
        if (sLockupStatus) {
            delete_file(controllerIndex, fileNum);
        }
    }

    return sLockupStatus;
}

void lockup_screen_loop(s32 updateRate) {
    sLockupDelay += updateRate;
    if (sLockupDelay >= 61) {
        sLockupDelay = 0;
        sLockupPage++;
    }
}

#ifdef NON_EQUIVALENT
void render_epc_lock_up_display(void) {
    char *sp50[3];
    s32 s3;
    s32 i, j;

    sp50[0] = D_800E302C[0]; // "setup"
    sp50[1] = D_800E302C[1]; // "control"
    sp50[2] = D_800E302C[2]; // "print"

    s3 = 0;

    set_render_printf_position(0x10, 0x20);

    switch (sLockupPage) {
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
                for (i = 0; i < 3; i++) {
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
                for (i = 0; i < 3; i++) {
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
                              D_801299B0[i - 1],
                              D_801299B0[i - 1 + 16],
                              D_801299B0[i - 1 + 32]);
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
            sLockupPage = 0;
            break;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/thread0_epc/render_epc_lock_up_display.s")
#endif
