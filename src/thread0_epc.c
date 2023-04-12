/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B6F50 */

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

/*********************************/

/************ .data ************/

/*******************************/

u64 gEPCStack[0x200];
OSThread gEPCThread;
s32 D_80129790[6]; // Osmesg stuff
s32 D_801297A8[8];
s32 D_801297C8[8];
s32 D_801297E8[6];

/**
 * Start the exception program counter thread.
 * Official Name: diCpuTraceInit
*/
void thread0_create(void) {
}

void thread0_Main(UNUSED void *unused) {
}

void func_800B70D0(void) {
}

void func_800B7144(void) {
}

void func_800B7460(s32 *epc, s32 size, s32 mask) {
}

void func_800B76B8(s32 arg0, s32 arg1) {
}

//Called as a check to see if render_epc_lock_up_display should be called.
s32 get_lockup_status(void) {
}

/* Official name: diCpuTraceTick */
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
