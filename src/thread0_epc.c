/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B6F50 */

#include "thread0_epc.h"
#include "common.h"
#include "types.h"
#include "macros.h"
#include "menu.h"
#include "save_data.h"
#include "printf.h"
#include "objects.h"
#include "joypad.h"
#include "game.h"
#include "stacks.h"
#include "PR/os_internal_thread.h"

/************ .rodata ************/

UNUSED const char D_800E8E70[] = "\nAssertion failed: '%s' in file %s, line %d\n";
UNUSED const char D_800E8EA0[] = "\nAssertion failed: '%s' in file %s, line %d\n";

/*********************************/

/************ .data ************/

s32 sLockupStatus = -1;
s32 sLockupPage = EPC_PAGE_REGISTER;
s32 sLockupDelay = 0;

/*******************************/

u64 gEPCStack[0x200];
OSThread gEPCThread;
OSMesgQueue D_80129790;
OSMesg D_801297A8[8];
OSMesg D_801297C8[8];
OSMesgQueue D_801297E8;

/**
 * Start the exception program counter thread.
 * Official Name: diCpuTraceInit
 */
void thread0_create(void) {
    s32 i;

    osCreateThread(&gEPCThread, 0, thread0_Main, 0, &gEPCStack[0x200], OS_PRIORITY_MAX);
    osStartThread(&gEPCThread);
    for (i = 0; i < 3; i++) {
        gObjectStackTrace[i] = -1;
    }
}

/**
 * Main thread for the epc lockup screen. Thread 0.
 */
void thread0_Main(UNUSED void *unused) {
    s32 sp34;
    s32 s0 = 0;

    osCreateMesgQueue(&D_80129790, D_801297A8, ARRAY_COUNT(D_801297A8));
    osSetEventMesg(OS_EVENT_FAULT, &D_80129790, (OSMesg) 8);
    osSetEventMesg(OS_EVENT_CPU_BREAK, &D_80129790, (OSMesg) 2);
    osCreatePiManager(150, &D_801297E8, D_801297C8, ARRAY_COUNT(D_801297C8));

    while (1) {
        osRecvMesg(&D_80129790, (OSMesg) &sp34, OS_MESG_BLOCK);
#if VERSION < VERSION_80
        if (!(get_filtered_cheats() & CHEAT_EPC_LOCK_UP_DISPLAY)) {
            continue;
        }
        s0 |= sp34;
        if ((s0 & 8) == 0 && (s0 & 2) == 0) {
            continue;
        }
#endif
        s0 &= ~8;
        stubbed_printf(">fault< ");
        enable_interupts_on_main();
        stop_all_threads_except_main();
        write_epc_data_to_cpak();
    }
}

/**
 * Enable interrupts on all idle priority threads, which should just be the main thread 1.
 */
void enable_interupts_on_main(void) {
    OSThread *node = __osGetActiveQueue();
    while (node->priority != -1) {
        if (node->priority == OS_PRIORITY_IDLE) {
            // Clear all existing interrupts and disable them.
            node->context.sr &= ~(SR_IMASK | SR_IE);

            // Enable interrupts
            // IP3 Int1 pin (N64: Cartridge)
            // IP4 Int2 pin (N64: Pre-NMI (Reset button))
            // IP6 Int4 pin (N64: RDB Write)
            // IP7 Timer interrupt
            node->context.sr |= (SR_IBIT7 | SR_IBIT6 | SR_IBIT4 | SR_IBIT3 | SR_IE);
            break;
        }
        node = node->tlnext;
    }
}

/**
 * Stop all threads except for the main thread 1
 */
void stop_all_threads_except_main(void) {
    OSThread *node = __osGetActiveQueue();
    while (node->priority != -1) {
        if (node->priority > OS_PRIORITY_IDLE && node->priority <= OS_PRIORITY_APPMAX) {
            osStopThread((OSThread *) &node->next);
        }
        node = node->tlnext;
    }
}

/**
 * Writes epc data to the controller pak so that it can be read back later.
 */
void write_epc_data_to_cpak(void) {
    OSThread *thread;
    UNUSED s16 sp444[0x200];
    u8 sp244[0x200];
    u8 sp44[0x200];
    s16 *v0;
    s32 i;
    s32 currentCount;
    s32 maxCount;
    u8 zero;

    for (thread = __osGetActiveQueue(); thread->priority != -1; thread = thread->tlnext) {
        if (thread->priority > OS_PRIORITY_IDLE && thread->priority <= OS_PRIORITY_APPMAX) {
            if (thread->flags & 2 || thread->flags & 1) {
                break;
            }
        }
    }

    if (thread->priority != -1) {
        thread->context.fp0.f.f_odd = gObjectStackTrace[0];
        thread->context.fp0.f.f_even = gObjectStackTrace[1];
        thread->context.fp2.f.f_odd = gObjectStackTrace[2];
        bcopy(thread, sp44, sizeof(epcInfo));
        bcopy((void *) thread->context.sp, sp244, sizeof(sp244));
        zero = 0; // Why is this needed to match?
        v0 = func_80024594(&currentCount, &maxCount);
        for (i = zero; i < maxCount; i++) {
            sp444[i] = v0[currentCount];
            currentCount--;
            if (currentCount < zero) {
                currentCount += maxCount;
            }
        }
        write_controller_pak_file(0, -1, "CORE", "", sp44, sizeof(sp44) + sizeof(sp244) + sizeof(sp444));
    }
    while (1) {} // Infinite loop
}

/**
 * Writes epc data to the controller pak when a memory allocation has failed,
 * but only if CHEAT_EPC_LOCK_UP_DISPLAY is active.
 */
void dump_memory_to_cpak(s32 epc, s32 size, u32 colourTag) {
    epcInfo epcinfo;
    s16 sp440[0x200];
    u8 sp240[0x200];
    u8 sp40[0x200];
    s16 *v0;
    s32 currentCount;
    s32 i;
    UNUSED s32 pad;

    // This is checking if the EPC cheat is active
    if (get_filtered_cheats() & CHEAT_EPC_LOCK_UP_DISPLAY) {
        bzero(&epcinfo, sizeof(epcInfo));
        epcinfo.epc = epc & 0xFFFFFFFFFFFFFFFF; // fakematch
        epcinfo.a0 = size;
        epcinfo.a1 = colourTag;
        epcinfo.cause = -1;
        epcinfo.objectStackTrace[0] = gObjectStackTrace[0];
        epcinfo.objectStackTrace[1] = gObjectStackTrace[1];
        epcinfo.objectStackTrace[2] = gObjectStackTrace[2];
        bcopy(&epcinfo, &sp40, sizeof(epcInfo));
        bzero(&sp240, sizeof(sp240));
        v0 = func_80024594(&currentCount, &size);
        for (i = 0; i < size; i++) {
            sp440[i] = v0[currentCount];
            currentCount--;
            if (currentCount < 0) {
                currentCount += size;
            }
        }
        i = sizeof(sp40) + sizeof(sp240) + sizeof(sp440); // fakematch?
        write_controller_pak_file(0, -1, "CORE", "", sp40, i);
        while (1) {} // Infinite loop; waiting for the player to reset the console?
    }
}

/**
 * Mark the object type given, so if the game crashes while processing it, the debug screen will tell you which object
 * ID is to blame. Split into three sections, for spawning an object, updating an object and for rendering an object.
 */
void update_object_stack_trace(s32 index, s32 value) {
    if (index >= OBJECT_SPAWN && index <= OBJECT_DRAW) {
        gObjectStackTrace[index] = value;
    }
}

/**
 * Called as a check to see if render_epc_lock_up_display should be called.
 */
s32 get_lockup_status(void) {
    s32 fileNum;
    s32 controllerIndex = 0;
    s64 sp420[128]; // Overwrite epcStack?
    s64 sp220[64];
    u8 dataFromControllerPak[512]; // Looks to be sizeof(epcInfo), aligned to 64
    extern epcInfo gEpcInfo;
    extern s32 D_801299B0[64];

    if (sLockupStatus != -1) {
        return sLockupStatus;
    } else {
        sLockupStatus = 0;
        // Looks like it reads EpcInfo data from the controller pak, which is interesting
        if ((get_si_device_status(controllerIndex) == CONTROLLER_PAK_GOOD) &&
            (get_file_number(controllerIndex, "CORE", "", &fileNum) == CONTROLLER_PAK_GOOD) &&
            (read_data_from_controller_pak(controllerIndex, fileNum, dataFromControllerPak, 0x800) ==
             CONTROLLER_PAK_GOOD)) {
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

/**
 * Counts up. Automatically switches page every second.
 * Official name: diCpuTraceTick
 */
void mode_lockup(s32 updateRate) {
    sLockupDelay += updateRate;
    if (sLockupDelay > 60) {
        sLockupDelay = 0;
        sLockupPage++;
    }
}

#define GET_REG(reg) (s32) gEpcInfo.reg

/**
 * Draw onscreen the four pages of the crash screen.
 * Page 0 shows the address of the instruction that crashed as well as fixed point registers
 * Page 1-3 show the stack dump of the crashed thread.
 * Page 4 appears to show the data of the EPC stack itself?
 */
void render_epc_lock_up_display(void) {
    u16 *temp;
    char *objStatusString[3] = { "setup", "control", "print" };
    s32 offset;
    s32 s3;
    s32 j;
    s32 i;
    static epcInfo gEpcInfo;
    static s32 D_801299B0[64];

    s3 = 0;

    set_render_printf_position(16, 32);

    switch (sLockupPage) {
        case EPC_PAGE_REGISTER:
            gObjectStackTrace[OBJECT_SPAWN] = gEpcInfo.objectStackTrace[OBJECT_SPAWN];
            gObjectStackTrace[OBJECT_UPDATE] = gEpcInfo.objectStackTrace[OBJECT_UPDATE];
            gObjectStackTrace[OBJECT_DRAW] = gEpcInfo.objectStackTrace[OBJECT_DRAW];
            if (((u32 *) gEpcInfo.objectStackTrace)[-4] == -1U) { // TODO: find better solution
                render_printf(" epc\t\t0x%08x\n", gEpcInfo.epc);
                render_printf(" cause\t\tmmAlloc(%d,0x%8x)\n", GET_REG(a0), GET_REG(a1));
                for (i = 0; i < 3; i++) {
                    if (gObjectStackTrace[i] != OBJECT_CLEAR) {
                        if (!s3) {
                            s3 = TRUE;
                            render_printf(" object\t\t");
                        }
                        render_printf("%s %d ", objStatusString[i], gObjectStackTrace[i]);
                    }
                }
                render_printf("\n");
                render_printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                break;
            }
            render_printf(" Fault in thread %d\n", gEpcInfo.thread[0]);
            render_printf(" epc\t\t0x%08x\n", gEpcInfo.epc);
            render_printf(" cause\t\t0x%08x\n", gEpcInfo.cause);
            render_printf(" sr\t\t0x%08x\n", gEpcInfo.sr);
            render_printf(" badvaddr\t0x%08x\n", gEpcInfo.badvaddr);
            for (i = 0; i < 3; i++) {
                if (gObjectStackTrace[i] != OBJECT_CLEAR) {
                    if (!s3) {
                        s3 = TRUE;
                        render_printf(" object\t\t");
                    }
                    render_printf("%s %d ", objStatusString[i], gObjectStackTrace[i]);
                }
            }
            render_printf("\n");
            render_printf(" at 0x%08x v0 0x%08x v1 0x%08x\n", GET_REG(at), GET_REG(v0), GET_REG(v1));
            render_printf(" a0 0x%08x a1 0x%08x a2 0x%08x\n", GET_REG(a0), GET_REG(a1), GET_REG(a2));
            render_printf(" a3 0x%08x t0 0x%08x t1 0x%08x\n", GET_REG(a3), GET_REG(t0), GET_REG(t1));
            render_printf(" t2 0x%08x t3 0x%08x t4 0x%08x\n", GET_REG(t2), GET_REG(t3), GET_REG(t4));
            render_printf(" t5 0x%08x t6 0x%08x t7 0x%08x\n", GET_REG(t5), GET_REG(t6), GET_REG(t7));
            render_printf(" s0 0x%08x s1 0x%08x s2 0x%08x\n", GET_REG(s0), GET_REG(s1), GET_REG(s2));
            render_printf(" s3 0x%08x s4 0x%08x s5 0x%08x\n", GET_REG(s3), GET_REG(s4), GET_REG(s5));
            render_printf(" s6 0x%08x s7 0x%08x t8 0x%08x\n", GET_REG(s6), GET_REG(s7), GET_REG(t8));
            render_printf(" t9 0x%08x gp 0x%08x sp 0x%08x\n", GET_REG(t9), GET_REG(gp), GET_REG(sp));
            render_printf(" s8 0x%08x ra 0x%08x\n\n", GET_REG(s8), GET_REG(ra));
            break;
        case EPC_PAGE_STACK_TOP:
        case EPC_PAGE_STACK_MIDDLE:
        case EPC_PAGE_STACK_BOTTOM:
            offset = (sLockupPage - 1) * 48;
            for (j = (s32) &D_801299B0[offset], i = 0; i < 16; i++) {
                render_printf("   %08x %08x %08x\n", ((u8 **) j)[0], ((u8 **) j)[16], ((u8 **) j)[32]);
                j = (s32) ((s32 *) j + 1);
            }
            break;
        case EPC_PAGE_UNK04:
            offset = (sLockupPage - 4) * 128;
            for (temp = (u16 *) &D_80129BB0[offset], i = 0; i < 16; i++) {
                render_printf("  ");
                for (j = 0; j < 8; j++) {
                    render_printf("%04x ", temp[0]);
                    temp++;
                }
                render_printf("\n");
            }
            break;
        case EPC_PAGE_EXIT:
            sLockupPage = 0;
            return;
        default:
            return;
    }
}
