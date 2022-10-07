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

extern OSSched gMainSched;


#ifdef EXPANSION_PAK
void draw_memory_error_screen(void) {
    Gfx *dlist;
    init_main_memory_pool();
    func_800C6170();
    func_80076BA0();
    func_80008040(); // Should be very similar to func_8005F850
    func_8007AC70(); // Should be very similar to func_8005F850
    func_800B5E88();
    osCreateScheduler(&gMainSched, 0, /*priority*/ 13, (u8) 0, 1);
    init_video(VIDEO_MODE_LOWRES_LPN, &gMainSched);

    dlist = gDisplayLists[0];
	change_vi(&gGlobalVI, SCREEN_WIDTH, SCREEN_HEIGHT);
	osViSetMode(&gGlobalVI);
    load_font(FONT_SMALL);
    set_text_font(FONT_SMALL);
    draw_text(dlist++, SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, "Expansion Pak Required", ALIGN_MIDDLE_CENTER);
    set_rsp_segment(&dlist, 0, 0);
    set_rsp_segment(&dlist, 1, (s32) gVideoLastFramebuffer);
    set_rsp_segment(&dlist, 2, gVideoLastDepthBuffer);
    set_rsp_segment(&dlist, 4, (s32) gVideoLastFramebuffer - 0x500);
    init_rsp(&dlist);
    init_rdp_and_framebuffer(&dlist);
    setup_ostask_xbus(gDisplayLists[0], dlist, 0);
    gDPFullSync(dlist++);
    gSPEndDisplayList(dlist++);
    wait_for_gfx_task();
    osViBlack(FALSE);
    osViSwapBuffer(gVideoLastFramebuffer);
}
#endif

void thread1_main(UNUSED void *unused) {
    //thread0_create();
    crash_screen_init();
    find_expansion_pak();
#ifdef EXPANSION_PAK
    if (!gExpansionPak) {
        draw_memory_error_screen();
    } else {
#endif
        osCreateThread(&gThread3, 3, &thread3_main, 0, &gThread3StackPointer, 10);
        gThread3Stack[1024] = 0;
        gThread3Stack[0] = 0;
        osStartThread(&gThread3);
        osSetThreadPri(NULL, 0);
#ifdef EXPANSION_PAK
    }
#endif
    while (1) {}
}

void thread3_verify_stack(void) {
    gThread3Stack[1024]++;
    gThread3Stack[0]++;
    if ((gThread3Stack[1024] != gThread3Stack[0])) {
        rmonPrintf("WARNING: Stack overflow/underflow!!!\n");
    }
}
