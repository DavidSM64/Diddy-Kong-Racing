/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065D40 */

#include "main.h"
#include "thread0_epc.h"
#include "game.h"
#include "lib/src/libc/rmonPrintf.h"

/************ .bss ************/

u64 *gThread1StackPointer; // stack pointer for thread 1
u64 gThread3Stack[1024];
u64 *gThread3StackPointer; // stack pointer for thread 3
OSThread gThread1; // OSThread for thread 1
OSThread gThread3; // OSThread for thread 3
u64 D_8011FAC0[512]; //Thread1 stack?
u8 gPlatformSet = FALSE;
u8 gPlatform;

/******************************/

u32 get_clockspeed(void);
void skGetId(u32 *arg);

void get_platform(void)
{
    /*u32 notiQue;
    if (get_clockspeed() == 0 || (u32)IO_READ(DPC_PIPEBUSY_REG) + (u32)IO_READ(DPC_TMEM_REG) + (u32)IO_READ(DPC_BUFBUSY_REG))
    {
        gPlatform &= ~EMULATOR;
        gPlatform |= CONSOLE;
    }
    else
    {
        gPlatform &= ~CONSOLE;
        gPlatform |= EMULATOR;
    }*/

    /*if (IS_VC())
    {
        gPlatform &= ~CONSOLE;
        gPlatform |= EMULATOR;
        gPlatform |= VC;
    }
    else
    {*/
        //gPlatform &= ~VC;
    //}

    /*skGetId(&notiQue);
    if (!notiQue)
    {
        gPlatform |= IQUE;
        gPlatform &= EMULATOR;
    }*/
}

#define STEP 0x100000
#define SIZE_4MB 0x400000
#define SIZE_8MB 0x800000

u32 osGetMemSize(void) {
    vu32* ptr;
    u32 size = SIZE_4MB;
    u32 data0;
    u32 data1;

    while (size < SIZE_8MB) {
        ptr = (vu32*)(K1BASE + size);

        data0 = *ptr;
        data1 = ptr[STEP / 4 - 1];

        *ptr ^= ~0;
        ptr[STEP / 4 - 1] ^= ~0;

        if ((*ptr != (data0 ^ ~0)) || (ptr[STEP / 4 - 1] != (data1 ^ ~0))) {
            return size;
        }

        *ptr = data0;
        ptr[STEP / 4 - 1] = data1;

        size += STEP;
    }

    return size;
}

void find_expansion_pak(void) {
#ifdef FORCE_4MB_MEMORY
    gExpansionPak = FALSE;
    return;
#endif
    if (osGetMemSize() == 0x800000) {
        gExpansionPak = TRUE;
    } else {
        gExpansionPak = FALSE;
    }
}

void main(void) {
    osInitialize();
    osCreateThread(&gThread1, 1, &thread1_main, 0, &gThread1StackPointer, OS_PRIORITY_IDLE);
    osStartThread(&gThread1);
}

void thread1_main(UNUSED void *unused) {
    //thread0_create();
    crash_screen_init();
    find_expansion_pak();
    osCreateThread(&gThread3, 3, &thread3_main, 0, &gThread3StackPointer, 10);
    gThread3Stack[1024] = 0;
    gThread3Stack[0] = 0;
    osStartThread(&gThread3);
    osSetThreadPri(NULL, 0);
    while (1) {}
}

void thread3_verify_stack(void) {
    gThread3Stack[1024]++;
    gThread3Stack[0]++;
    if ((gThread3Stack[1024] != gThread3Stack[0])) {
        rmonPrintf("WARNING: Stack overflow/underflow!!!\n");
    }
}
