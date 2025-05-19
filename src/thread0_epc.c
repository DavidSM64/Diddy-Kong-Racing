#include "thread0_epc.h"
#include "common.h"
#include "types.h"
#include "macros.h"
#include "menu.h"
#include "save_data.h"
#include "printf.h"
#include "objects.h"
#include "joypad.h"
#include "stacks.h"
#include "PR/os_internal_thread.h"
#include "PRinternal/rmonint.h"

/************ .data ************/

s32 sLockupStatus = -1;
s32 sLockupPage = EPC_PAGE_REGISTER;
s32 sLockupDelay = 0;

/*******************************/

u64 gEPCStack[STACKSIZE(STACK_EPC)];
OSThread gEPCThread;
OSMesgQueue gEPCMesgQueue;
OSMesg gEPCMesgBuf[8];
OSMesg gEPCPIBuf[8];
OSMesgQueue gEPCPIQueue;
epcInfo gEpcInfo;
u64 gEpcInfoStack1[STACKSIZE(STACK_EPCINFO1)];
u64 gEpcInfoStack2[STACKSIZE(STACK_EPCINFO2)];
s32 gObjectStackTrace[3];

/**
 * Start the exception program counter thread.
 * Official Name: diCpuTraceInit
 */
void thread0_create(void) {
    s32 i;

    osCreateThread(&gEPCThread, 0, thread0_Main, 0, &gEPCStack[STACKSIZE(STACK_EPC)], OS_PRIORITY_MAX);
    osStartThread(&gEPCThread);
    for (i = 0; i < ARRAY_COUNT(gObjectStackTrace); i++) {
        gObjectStackTrace[i] = -1;
    }
}

/**
 * Main thread for the epc lockup screen. Thread 0.
 * Official Name: diCpuThread
 */
void thread0_Main(UNUSED void *unused) {
    s32 sp34;
    s32 s0 = 0;

    osCreateMesgQueue(&gEPCMesgQueue, gEPCMesgBuf, ARRAY_COUNT(gEPCMesgBuf));
    osSetEventMesg(OS_EVENT_FAULT, &gEPCMesgQueue, (OSMesg) RMON_MESG_FAULT);
    osSetEventMesg(OS_EVENT_CPU_BREAK, &gEPCMesgQueue, (OSMesg) RMON_MESG_CPU_BREAK);
    osCreatePiManager(150, &gEPCPIQueue, gEPCPIBuf, ARRAY_COUNT(gEPCPIBuf));

    while (1) {
        osRecvMesg(&gEPCMesgQueue, (OSMesg) &sp34, OS_MESG_BLOCK);
#if VERSION < VERSION_80
        if (!(get_filtered_cheats() & CHEAT_EPC_LOCK_UP_DISPLAY)) {
            continue;
        }
        s0 |= sp34;
        if (!(s0 & RMON_MESG_FAULT) && !(s0 & RMON_MESG_CPU_BREAK)) {
            continue;
        }
#endif
        s0 &= ~RMON_MESG_FAULT;
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
    s16 sp444[0x200];
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
        bcopy((void *) (u32) thread->context.sp, sp244, sizeof(sp244));
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
        write_controller_pak_file(0, -1, "CORE", "", sp40, sizeof(sp40) + sizeof(sp240) + sizeof(sp440));
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

#ifndef _ALIGN128
#define _ALIGN128(a) (((u32) (a) + 0x7F) & ~(u32) 0x7F)
#endif

/**
 * Called as a check to see if render_epc_lock_up_display should be called.
 */
s32 get_lockup_status(void) {
    s32 fileNum;
    s32 controllerIndex = 0;
    struct {
        u8 epcInfo[_ALIGN128(sizeof(epcInfo))];
        u64 epcInfoStack1[STACKSIZE(STACK_EPCINFO1)];
        u64 epcInfoStack2[STACKSIZE(STACK_EPCINFO2)];
    } dataFromControllerPak;

    if (sLockupStatus != -1) {
        return sLockupStatus;
    } else {
        sLockupStatus = FALSE;
        // Looks like it reads EpcInfo data from the controller pak, which is interesting
        if ((get_si_device_status(controllerIndex) == CONTROLLER_PAK_GOOD) &&
            (get_file_number(controllerIndex, "CORE", "", &fileNum) == CONTROLLER_PAK_GOOD) &&
            (read_data_from_controller_pak(controllerIndex, fileNum, (u8 *) &dataFromControllerPak,
                                           sizeof(dataFromControllerPak)) == CONTROLLER_PAK_GOOD)) {
            bcopy(&dataFromControllerPak.epcInfo, &gEpcInfo, sizeof(epcInfo));
            bcopy(&dataFromControllerPak.epcInfoStack1, &gEpcInfoStack1, sizeof(dataFromControllerPak.epcInfoStack1));
            bcopy(&dataFromControllerPak.epcInfoStack2, &gEpcInfoStack2, sizeof(dataFromControllerPak.epcInfoStack2));
            sLockupStatus = TRUE;
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

#define GET_REG(reg) (s32) epcinfo->reg

/**
 * Draw onscreen the four pages of the crash screen.
 * Page 0 shows the address of the instruction that crashed as well as fixed point registers
 * Page 1-3 show the stack dump of the crashed thread.
 * Page 4 appears to show the data of the EPC stack itself?
 */
void render_epc_lock_up_display(void) {
    epcInfo *epcinfo;
    char *objStatusString[3] = { "setup", "control", "print" };
    s32 offset;
    s32 s3;
    s32 j;
    s32 i;
    s3 = 0;
    set_render_printf_position(16, 32);
    switch (sLockupPage) {
        case EPC_PAGE_REGISTER:
            epcinfo = &gEpcInfo;
            gObjectStackTrace[OBJECT_SPAWN] = epcinfo->objectStackTrace[OBJECT_SPAWN];
            gObjectStackTrace[OBJECT_UPDATE] = epcinfo->objectStackTrace[OBJECT_UPDATE];
            gObjectStackTrace[OBJECT_DRAW] = epcinfo->objectStackTrace[OBJECT_DRAW];
            if (epcinfo->cause == 0xFFFFFFFF) {
                render_printf(" epc\t\t0x%08x\n", epcinfo->epc);
                render_printf(" cause\t\tmmAlloc(%d,0x%8x)\n", GET_REG(a0), GET_REG(a1));
                for (i = 0; i < ARRAY_COUNT(gObjectStackTrace); i++) {
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
            } else {
                epcinfo = &gEpcInfo;
                render_printf(" Fault in thread %d\n", epcinfo->thread[0]);
                render_printf(" epc\t\t0x%08x\n", epcinfo->epc);
                render_printf(" cause\t\t0x%08x\n", epcinfo->cause);
                render_printf(" sr\t\t0x%08x\n", epcinfo->sr);
                render_printf(" badvaddr\t0x%08x\n", epcinfo->badvaddr);
                for (i = 0; i < ARRAY_COUNT(gObjectStackTrace); i++) {
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
            }
            break;
        case EPC_PAGE_STACK_TOP:    /* fall through */
        case EPC_PAGE_STACK_MIDDLE: /* fall through */
        case EPC_PAGE_STACK_BOTTOM:
            offset = (sLockupPage - 1) * 48;
            for (i = 0; i < 16; i++) {
                render_printf("   %08x %08x %08x\n", ((u16 **) &gEpcInfoStack1)[offset],
                              ((u16 **) &gEpcInfoStack1)[offset + 16], ((u16 **) &gEpcInfoStack1)[offset + 32]);
                offset++;
            }
            break;
        case EPC_PAGE_UNK04:
            offset = (sLockupPage - 4) * 128;
            for (i = 0; i < 16; i++) {
                render_printf("  ");
                for (j = 0; j < 8; j++) {
                    render_printf("%04x ", (((u16 *) &gEpcInfoStack2)[offset]));
                    offset++;
                }
                render_printf("\n");
            }
            break;
        case EPC_PAGE_EXIT:
            sLockupPage = 0;
            break;
        default:
            break;
    }
}
