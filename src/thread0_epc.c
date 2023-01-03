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
#include "particles.h"
#include "stdarg.h"

/************ .rodata ************/

const char D_800E8EDC[] = "CORE";
const char D_800E8EE4[4] = { 0, 0, 0, 0 };

/*********************************/

/************ .data ************/

s32 sLockupStatus = -1;
s32 sLockupPage = EPC_PAGE_REGISTER;
s32 sLockupDelay = 0;

/*******************************/

/************ .bss ************/

/******************************/

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

void thread0_create(void) {
}

void thread0_Main(UNUSED void *unused) {
}

void func_800B70D0(void) {
}

void func_800B7144(void) {
}

GLOBAL_ASM("asm/non_matchings/thread0_epc/func_800B71B0.s")

void func_800B7460(s32 *epc, s32 size, s32 mask) {
}

void func_800B76B8(s32 arg0, s32 arg1) {
}

//Called as a check to see if render_epc_lock_up_display should be called.
s32 get_lockup_status(void) {
}

void lockup_screen_loop(s32 updateRate) {
}

#define GET_REG(reg) (s32)gEpcInfo.reg

/**
 * Draw onscreen the four pages of the crash screen.
 * Page 0 shows the address of the instruction that crashed as well as fixed point registers
 * Page 1-3 show the stack dump of the crashed thread.
 * Page 4 appears to show the data of the EPC stack itself?
*/
void render_epc_lock_up_display(void) {
}

#include "crash_screen.h"
