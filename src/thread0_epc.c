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
#include "stdarg.h"

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

const char *const gCauseDesc[18] = {
    "Interrupt",
    "TLB modification",
    "TLB exception on load",
    "TLB exception on store",
    "Address error on load",
    "Address error on store",
    "Bus error on inst.",
    "Bus error on data",
    "System call exception",
    "Breakpoint exception",
    "Reserved instruction",
    "Coprocessor unusable",
    "Arithmetic overflow",
    "Trap exception",
    "Virtual coherency on inst.",
    "Floating point exception",
    "Watchpoint exception",
    "Virtual coherency on data",
};

const char *const gFpcsrDesc[6] = {
    "Unimplemented operation", "Invalid operation", "Division by zero", "Overflow", "Underflow",
    "Inexact operation",
};

const u8 gCrashScreenCharToGlyph[128] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 41, -1, -1, -1, 43, -1, -1, 37, 38, -1, 42,
    -1, 39, 44, -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  36, -1, -1, -1, -1, 40, -1, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1,
};

// Bit-compressed font. '#' = 1, '.' = 0
const u32 gCrashScreenFont[7 * 9] = {
    0x70871c30, // .###.. ..#... .###.. .###.. ..##.. ..
    0x8988a250, // #...#. .##... #...#. #...#. .#.#.. ..
    0x88808290, // #...#. ..#... ....#. ....#. #..#.. ..
    0x88831c90, // #...#. ..#... ..##.. .###.. #..#.. ..
    0x888402f8, // #...#. ..#... .#.... ....#. #####. ..
    0x88882210, // #...#. ..#... #..... #...#. ...#.. ..
    0x71cf9c10, // .###.. .###.. #####. .###.. ...#.. ..

    0xf9cf9c70, // #####. .###.. #####. .###.. .###.. ..
    0x8228a288, // #..... #...#. #...#. #...#. #...#. ..
    0xf200a288, // ####.. #..... ....#. #...#. #...#. ..
    0x0bc11c78, // ....#. ####.. ...#.. .###.. .####. ..
    0x0a222208, // ....#. #...#. ..#... #...#. ....#. ..
    0x8a222288, // #...#. #...#. ..#... #...#. #...#. ..
    0x71c21c70, // .###.. .###.. ..#... .###.. .###.. ..

    0x23c738f8, // ..#... ####.. .###.. ###... #####. ..
    0x5228a480, // .#.#.. #...#. #...#. #..#.. #..... ..
    0x8a282280, // #...#. #...#. #..... #...#. #..... ..
    0x8bc822f0, // #...#. ####.. #..... #...#. ####.. ..
    0xfa282280, // #####. #...#. #..... #...#. #..... ..
    0x8a28a480, // #...#. #...#. #...#. #..#.. #..... ..
    0x8bc738f8, // #...#. ####.. .###.. ###... #####. ..

    0xf9c89c08, // #####. .###.. #...#. .###.. ....#. ..
    0x82288808, // #..... #...#. #...#. ..#... ....#. ..
    0x82088808, // #..... #..... #...#. ..#... ....#. ..
    0xf2ef8808, // ####.. #.###. #####. ..#... ....#. ..
    0x82288888, // #..... #...#. #...#. ..#... #...#. ..
    0x82288888, // #..... #...#. #...#. ..#... #...#. ..
    0x81c89c70, // #..... .###.. #...#. .###.. .###.. ..

    0x8a08a270, // #...#. #..... #...#. #...#. .###.. ..
    0x920da288, // #..#.. #..... ##.##. #...#. #...#. ..
    0xa20ab288, // #.#... #..... #.#.#. ##..#. #...#. ..
    0xc20aaa88, // ##.... #..... #.#.#. #.#.#. #...#. ..
    0xa208a688, // #.#... #..... #...#. #..##. #...#. ..
    0x9208a288, // #..#.. #..... #...#. #...#. #...#. ..
    0x8be8a270, // #...#. #####. #...#. #...#. .###.. ..

    0xf1cf1cf8, // ####.. .###.. ####.. .###.. #####. ..
    0x8a28a220, // #...#. #...#. #...#. #...#. ..#... ..
    0x8a28a020, // #...#. #...#. #...#. #..... ..#... ..
    0xf22f1c20, // ####.. #...#. ####.. .###.. ..#... ..
    0x82aa0220, // #..... #.#.#. #.#... ....#. ..#... ..
    0x82492220, // #..... #..#.. #..#.. #...#. ..#... ..
    0x81a89c20, // #..... .##.#. #...#. .###.. ..#... ..

    0x8a28a288, // #...#. #...#. #...#. #...#. #...#. ..
    0x8a28a288, // #...#. #...#. #...#. #...#. #...#. ..
    0x8a289488, // #...#. #...#. #...#. .#.#.. #...#. ..
    0x8a2a8850, // #...#. #...#. #.#.#. ..#... .#.#.. ..
    0x894a9420, // #...#. .#.#.. #.#.#. .#.#.. ..#... ..
    0x894aa220, // #...#. .#.#.. #.#.#. #...#. ..#... ..
    0x70852220, // .###.. ..#... .#.#.. #...#. ..#... ..

    0xf8011000, // #####. ...... ...#.. .#.... ...... ..
    0x08020800, // ....#. ...... ..#... ..#... ...... ..
    0x10840400, // ...#.. ..#... .#.... ...#.. ...... ..
    0x20040470, // ..#... ...... .#.... ...#.. .###.. ..
    0x40840400, // .#.... ..#... .#.... ...#.. ...... ..
    0x80020800, // #..... ...... ..#... ..#... ...... ..
    0xf8011000, // #####. ...... ...#.. .#.... ...... ..

    0x70800000, // .###.. ..#... ...... ...... ...... ..
    0x88822200, // #...#. ..#... ..#... #...#. ...... ..
    0x08820400, // ....#. ..#... ..#... ...#.. ...... ..
    0x108f8800, // ...#.. ..#... #####. ..#... ...... ..
    0x20821000, // ..#... ..#... ..#... .#.... ...... ..
    0x00022200, // ...... ...... ..#... #...#. ...... ..
    0x20800020, // ..#... ..#... ...... ...... ..#... ..
};

extern u64 osClockRate;

struct {
    OSThread thread;
    u64 stack[0x800 / sizeof(u64)];
    OSMesgQueue mesgQueue;
    OSMesg mesg;
    u16 *framebuffer;
    u16 width;
    u16 height;
} gCrashScreen;

void crash_screen_draw_rect(s32 x, s32 y, s32 w, s32 h) {
    u16 *ptr;
    s32 i, j;

    ptr = gCrashScreen.framebuffer + gCrashScreen.width * y + x;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            // 0xe738 = 0b1110011100111000
            *ptr = ((*ptr & 0xe738) >> 2) | 1;
            ptr++;
        }
        ptr += gCrashScreen.width - w;
    }
}

void crash_screen_draw_glyph(s32 x, s32 y, s32 glyph) {
    const u32 *data;
    u16 *ptr;
    u32 bit;
    u32 rowMask;
    s32 i, j;

    data = &gCrashScreenFont[glyph / 5 * 7];
    ptr = gCrashScreen.framebuffer + gCrashScreen.width * y + x;

    for (i = 0; i < 7; i++) {
        bit = 0x80000000U >> ((glyph % 5) * 6);
        rowMask = *data++;

        for (j = 0; j < 6; j++) {
            *ptr++ = (bit & rowMask) ? 0xffff : 1;
            bit >>= 1;
        }
        ptr += gCrashScreen.width - 6;
    }
}

static char *write_to_buf(char *buffer, const char *data, size_t size) {
    return (char *) memcpy(buffer, data, size) + size;
}

void crash_screen_print(s32 x, s32 y, const char *fmt, ...) {
    char *ptr;
    char buf[0x108];
    u32 glyph;
    va_list args;

    va_start(args, fmt);
    if (_Printf(write_to_buf, buf, fmt, args) > 0) {
        ptr = buf;
        while (*ptr) {
            glyph = gCrashScreenCharToGlyph[*ptr & 0x7f];
            if (glyph != 0xff) {
                crash_screen_draw_glyph(x, y, glyph);
            }
            ptr++;
            x += 6;
        }
    }
    va_end(args);
}

void crash_screen_sleep(s32 ms) {
    u64 cycles = ms * 1000LL * osClockRate / 1000000ULL;
    osSetTime(0);
    while (osGetTime() < cycles) {
    }
}

void crash_screen_print_float_reg(s32 x, s32 y, s32 regNum, void *addr) {
    u32 bits;
    s32 exponent;

    bits = *(u32 *) addr;
    exponent = ((bits & 0x7f800000U) >> 0x17) - 0x7f;
    if ((exponent >= -0x7e && exponent <= 0x7f) || bits == 0) {
        crash_screen_print(x, y, "F%02d:%.3e", regNum, *(f32 *) addr);
    } else {
        crash_screen_print(x, y, "F%02d:---------", regNum);
    }
}

void crash_screen_print_fpcsr(u32 fpcsr) {
    s32 i;
    u32 bit;

    bit = 1 << 17;
    crash_screen_print(30, 155, "FPCSR:%08XH", fpcsr);
    for (i = 0; i < 6; i++) {
        if (fpcsr & bit) {
            crash_screen_print(132, 155, "(%s)", gFpcsrDesc[i]);
            return;
        }
        bit >>= 1;
    }
}

void draw_crash_screen(OSThread *thread) {
    s16 cause;
    __OSThreadContext *tc = &thread->context;

    cause = (tc->cause >> 2) & 0x1f;
    if (cause == 23) // EXC_WATCH
    {
        cause = 16;
    }
    if (cause == 31) // EXC_VCED
    {
        cause = 17;
    }

    crash_screen_draw_rect(25, 20, 270, 25);
    crash_screen_print(30, 25, "THREAD:%d  (%s)", thread->id, gCauseDesc[cause]);
    crash_screen_print(30, 35, "PC:%08XH   SR:%08XH   VA:%08XH", tc->pc, tc->sr, tc->badvaddr);
    osWritebackDCacheAll();
    crash_screen_sleep(2000);
    crash_screen_draw_rect(25, 45, 270, 185);
    crash_screen_print(30, 50, "AT:%08XH   V0:%08XH   V1:%08XH", (u32) tc->at, (u32) tc->v0, (u32) tc->v1);
    crash_screen_print(30, 60, "A0:%08XH   A1:%08XH   A2:%08XH", (u32) tc->a0, (u32) tc->a1, (u32) tc->a2);
    crash_screen_print(30, 70, "A3:%08XH   T0:%08XH   T1:%08XH", (u32) tc->a3, (u32) tc->t0, (u32) tc->t1);
    crash_screen_print(30, 80, "T2:%08XH   T3:%08XH   T4:%08XH", (u32) tc->t2, (u32) tc->t3, (u32) tc->t4);
    crash_screen_print(30, 90, "T5:%08XH   T6:%08XH   T7:%08XH", (u32) tc->t5, (u32) tc->t6, (u32) tc->t7);
    crash_screen_print(30, 100, "S0:%08XH   S1:%08XH   S2:%08XH", (u32) tc->s0, (u32) tc->s1, (u32) tc->s2);
    crash_screen_print(30, 110, "S3:%08XH   S4:%08XH   S5:%08XH", (u32) tc->s3, (u32) tc->s4, (u32) tc->s5);
    crash_screen_print(30, 120, "S6:%08XH   S7:%08XH   T8:%08XH", (u32) tc->s6, (u32) tc->s7, (u32) tc->t8);
    crash_screen_print(30, 130, "T9:%08XH   GP:%08XH   SP:%08XH", (u32) tc->t9, (u32) tc->gp, (u32) tc->sp);
    crash_screen_print(30, 140, "S8:%08XH   RA:%08XH", (u32) tc->s8, (u32) tc->ra);
    crash_screen_print_fpcsr(tc->fpcsr);
    osWritebackDCacheAll();
    crash_screen_print_float_reg(30, 170, 0, &tc->fp0.f.f_even);
    crash_screen_print_float_reg(120, 170, 2, &tc->fp2.f.f_even);
    crash_screen_print_float_reg(210, 170, 4, &tc->fp4.f.f_even);
    crash_screen_print_float_reg(30, 180, 6, &tc->fp6.f.f_even);
    crash_screen_print_float_reg(120, 180, 8, &tc->fp8.f.f_even);
    crash_screen_print_float_reg(210, 180, 10, &tc->fp10.f.f_even);
    crash_screen_print_float_reg(30, 190, 12, &tc->fp12.f.f_even);
    crash_screen_print_float_reg(120, 190, 14, &tc->fp14.f.f_even);
    crash_screen_print_float_reg(210, 190, 16, &tc->fp16.f.f_even);
    crash_screen_print_float_reg(30, 200, 18, &tc->fp18.f.f_even);
    crash_screen_print_float_reg(120, 200, 20, &tc->fp20.f.f_even);
    crash_screen_print_float_reg(210, 200, 22, &tc->fp22.f.f_even);
    crash_screen_print_float_reg(30, 210, 24, &tc->fp24.f.f_even);
    crash_screen_print_float_reg(120, 210, 26, &tc->fp26.f.f_even);
    crash_screen_print_float_reg(210, 210, 28, &tc->fp28.f.f_even);
    crash_screen_print_float_reg(30, 220, 30, &tc->fp30.f.f_even);
    osWritebackDCacheAll();
    osViBlack(FALSE);
    osViSwapBuffer(gCrashScreen.framebuffer);
}

extern OSThread *__osFaultedThread;

OSThread *get_crashed_thread(void) {
    OSThread *thread;

    thread = __osFaultedThread;
    while (thread->priority != -1) {
        if (thread->priority > OS_PRIORITY_IDLE && thread->priority < OS_PRIORITY_APPMAX
            && (thread->flags & 3) != 0) {
            return thread;
        }
        thread = thread->tlnext;
    }
    return NULL;
}

void thread2_crash_screen(UNUSED void *arg) {
    OSMesg mesg;
    OSThread *thread;

    osSetEventMesg(OS_EVENT_CPU_BREAK, &gCrashScreen.mesgQueue, (OSMesg) 1);
    osSetEventMesg(OS_EVENT_FAULT, &gCrashScreen.mesgQueue, (OSMesg) 2);
    do {
        osRecvMesg(&gCrashScreen.mesgQueue, &mesg, 1);
        if (gVideoLastFramebuffer) {
            gCrashScreen.framebuffer = gVideoLastFramebuffer;
        }
        thread = get_crashed_thread();
    } while (thread == NULL);
    draw_crash_screen(thread);
    for (;;) {
    }
}

void crash_screen_set_framebuffer(u16 *framebuffer, s16 width, s16 height) {
    gCrashScreen.framebuffer = framebuffer;
    gCrashScreen.width = width;
    gCrashScreen.height = height;
}

void crash_screen_init(void) {
    gCrashScreen.framebuffer = (u16 *) (0x80300000) - SCREEN_WIDTH * SCREEN_HEIGHT;
    gCrashScreen.width = SCREEN_WIDTH;
    gCrashScreen.height = SCREEN_HEIGHT;
    osCreateMesgQueue(&gCrashScreen.mesgQueue, &gCrashScreen.mesg, 1);
    osCreateThread(&gCrashScreen.thread, 2, thread2_crash_screen, NULL, (u8 *) gCrashScreen.stack + sizeof(gCrashScreen.stack), OS_PRIORITY_APPMAX);
    osStartThread(&gCrashScreen.thread);
}