/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065D40 */

#include "main.h"
#include "thread0_epc.h"
#include "game.h"
#include "lib/src/libc/rmonPrintf.h"
#include "lib/src/libc/xprintf.h"
#include "string.h"
#include "stdarg.h"
#include "controller.h"
#include "printf.h"

/************ .bss ************/

u64 *gThread1StackPointer; // stack pointer for thread 1
u64 gThread3Stack[0x400];
u64 *gThread3StackPointer; // stack pointer for thread 3
OSThread gThread1; // OSThread for thread 1
OSThread gThread3; // OSThread for thread 3
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
    gUseExpansionMemory = FALSE;
    return;
#endif
    if (osGetMemSize() == 0x800000) {
        gExpansionPak = TRUE;
#ifndef EXPANSION_PAK_SUPPORT
        gUseExpansionMemory = FALSE;
#else
        gUseExpansionMemory = TRUE;
#endif
    } else {
        gExpansionPak = FALSE;
        gUseExpansionMemory = FALSE;
    }
}

/******************************/

/**
 * Where it all begins.
 * Once the boot procedure is finished in IPL3, this function is run.
 * It kicks things off by initialising thread1, which serves as the top level
 * Official name: boot
*/
void main(void) {
    osInitialize();
    osCreateThread(&gThread1, 1, &thread1_main, 0, &gThread1StackPointer, OS_PRIORITY_IDLE);
    osStartThread(&gThread1);
}

extern OSSched gMainSched;

#ifdef EXPANSION_PAK_REQUIRED
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
    set_rsp_segment(&dlist, 1, (s32) gVideoFrontFramebuffer);
    set_rsp_segment(&dlist, 2, gVideoLastDepthBuffer);
    set_rsp_segment(&dlist, 4, (s32) gVideoFrontFramebuffer - 0x500);
    init_rsp(&dlist);
    init_rdp_and_framebuffer(&dlist);
    setup_ostask_xbus(gDisplayLists[0], dlist, 0);
    gDPFullSync(dlist++);
    gSPEndDisplayList(dlist++);
    wait_for_gfx_task();
    osViBlack(FALSE);
    osViSwapBuffer(gVideoFrontFramebuffer);
}
#endif

/**
 * Initialise the crash handler thread, then initialise the main game thread.
 * Reset the start and endpoint of the game thread stack, then set thread priority to zero, effectively
 * stopping this thread, as it's no longer needed.
*/
void thread1_main(UNUSED void *unused) {
    //thread0_create();
    crash_screen_init();
    find_expansion_pak();
#ifdef EXPANSION_PAK_REQUIRED
    if (!gExpansionPak) {
        draw_memory_error_screen();
    } else {
#endif
        osCreateThread(&gThread3, 3, &thread3_main, 0, &gThread3StackPointer, 10);
        gThread3Stack[0x400] = 0;
        gThread3Stack[0] = 0;
        osStartThread(&gThread3);
        osSetThreadPri(NULL, OS_PRIORITY_IDLE);
#ifdef EXPANSION_PAK_REQUIRED
    }
#endif
    while (1) {}
}

/**
 * Increments the start and endpoint of the stack.
 * They should have an equal value, so if they don't, that triggers a printout saying a stack wraparound has occured.
*/
void thread3_verify_stack(void) {
    gThread3Stack[0x400]++;
    gThread3Stack[0]++;
    if ((gThread3Stack[0x400] != gThread3Stack[0])) {
        rmonPrintf("WARNING: Stack overflow/underflow!!!\n");
    }
}

s32 _Printf(outfun prout, char *dst, const char *fmt, va_list args);

static char *proutSprintf(char *dst, const char *src, size_t count)
{
    return (char *)memcpy((u8 *)dst, (u8 *)src, count) + count;
}

int puppyprintf(char *dst, const char *fmt, ...)
{
    s32 ans;
    va_list ap;
    va_start(ap, fmt);
    ans = _Printf(proutSprintf, dst, fmt, ap);
    if (ans >= 0)
    {
        dst[ans] = 0;
    }
    return ans; 
}

#ifdef PUPPYPRINT_DEBUG
extern Gfx *gCurrDisplayList;
extern s32 gSPTaskNum;
extern s32 gCurrNumF3dCmdsPerPlayer;
extern s32 sLogicUpdateRate;

u8 perfIteration = 0;
f32 gFPS = 0;
u8 gProfilerOn = 1;
u8 gWidescreen = 0;
s32 sTriCount = 0;
s32 sVtxCount = 0;
s32 prevTime = 0;
u32 sTimerTemp = 0;
u8 sProfilerPage = 0;
u32 sPrevLoadTimeTotal = 0;
u32 gPrevLoadTimeDecompress = 0;
u32 gPrevLoadTimeDMA = 0;
u32 gPrevLoadTimeTexture = 0;
u32 gPrevLoadTimeModel = 0;
u32 gPrevLoadTimeObjects = 0;
u8 sPrevLoadTimer = 0;
u8 gShowHiddenGeometry = FALSE;
u8 gShowHiddenObjects = FALSE;
u32 gFreeMem[12];
u8 sPrintOrder[PP_RSP_GFX];
u16 sObjPrintOrder[NUM_OBJECT_PRINTS];
struct PuppyPrintTimers gPuppyTimers;
char sPuppyPrintStrings[][16] = {
    PP_STRINGS
};
char sPuppyprintMemColours[][16] = {
    "Red\t",
    "Green",
    "Blue\t",
    "Yellow",
    "Magenta",
    "Cyan",
    "White",
    "Grey",
    "GreyXLU",
    "Orange",
    "Black"
};

#define FRAMETIME_COUNT 10

OSTime frameTimes[FRAMETIME_COUNT];
u8 curFrameTimeIndex = 0;

// Call once per frame
void calculate_and_update_fps(void) {
    OSTime newTime = osGetCount();
    OSTime oldTime = frameTimes[curFrameTimeIndex];
    frameTimes[curFrameTimeIndex] = newTime;

    curFrameTimeIndex++;
    if (curFrameTimeIndex >= FRAMETIME_COUNT) {
        curFrameTimeIndex = 0;
    }
    gFPS = (FRAMETIME_COUNT * 1000000.0f) / (s32)OS_CYCLES_TO_USEC(newTime - oldTime);
}

void rdp_profiler_update(u32 *time, u32 time2) {
    time[PERF_AGGREGATE] -= time[perfIteration];
    time[perfIteration] = time2;
    time[PERF_AGGREGATE] += time[perfIteration];
}

void profiler_update(u32 *time, u32 time2) {
    u32 tmm = (osGetCount() - time2);
    if (tmm > OS_USEC_TO_CYCLES(99999)) {
        tmm =  OS_USEC_TO_CYCLES(99999);
    }
    time[PERF_AGGREGATE] -= time[perfIteration];
    time[perfIteration] = tmm;
    time[PERF_AGGREGATE] += time[perfIteration];
}

void profiler_offset(u32 *time, u32 offset) {
    time[PERF_AGGREGATE] -= offset;
    time[perfIteration] -= offset;
}

void profiler_add(u32 *time, u32 offset) {
    if (offset > OS_USEC_TO_CYCLES(99999)) {
        offset =  OS_USEC_TO_CYCLES(99999);
    }
    time[PERF_AGGREGATE] += offset;
    time[perfIteration] += offset;
}

void profiler_reset_values(void) {
    s32 i;
    for (i = 0; i < PP_RDP_BUS; i++) {
        gPuppyTimers.timers[i][PERF_AGGREGATE] -= gPuppyTimers.timers[i][perfIteration];
        gPuppyTimers.timers[i][perfIteration] = 0;
    }
    for (i = 0; i < NUM_OBJECT_PRINTS; i++) {
        gPuppyTimers.objTimers[i][PERF_AGGREGATE] -= gPuppyTimers.objTimers[i][perfIteration];
        gPuppyTimers.objTimers[i][perfIteration] = 0;
    }
}

void profiler_add_obj(u32 objID, u32 time) {
    u32 tempTime = OS_CYCLES_TO_USEC(time);
    if (objID >= NUM_OBJECT_PRINTS) {
        return;
    }
    gPuppyTimers.objTimers[objID][PERF_AGGREGATE] += tempTime;
    gPuppyTimers.objTimers[objID][perfIteration] += tempTime;
}

void profiler_snapshot(s32 eventID) {
    u32 snapshot = gPuppyTimers.threadIteration[eventID / 2];
    if (snapshot > NUM_THREAD_ITERATIONS - 1) {
        snapshot = NUM_THREAD_ITERATIONS - 1;
    }
    gPuppyTimers.threadTimes[snapshot][eventID] = osGetCount();
    // Thread endings are even numbers.
    if (eventID % 2) {
        gPuppyTimers.threadIteration[eventID / 2]++;
    }
};

    #define TEXT_OFFSET 10
void render_profiler(void) {
    char textBytes[80];
    s32 printY;
    u32 i;
    s32 y = 8;
    u32 memsize = osGetMemSize();

#ifndef EXPANSION_PAK_SUPPORT
    memsize = 0x400000;
#endif

    if (get_buttons_pressed_from_player(PLAYER_ONE) & R_JPAD) {
        sProfilerPage++;
        if (sProfilerPage == 3) {
            sProfilerPage = 0;
        }
    }
    if (get_buttons_pressed_from_player(PLAYER_ONE) & L_JPAD) {
        sProfilerPage--;
        if (sProfilerPage == 255) {
            sProfilerPage = 2;
        }
    }

    gDPSetScissor(gCurrDisplayList++, G_SC_NON_INTERLACE, 0, 0, gScreenWidth, gScreenHeight);

    set_text_font(ASSET_FONTS_SMALLFONT);
    set_text_colour(255, 255, 255, 255, 255);
    if (IO_READ(DPC_PIPEBUSY_REG) + IO_READ(DPC_CLOCK_REG) + IO_READ(DPC_TMEM_REG)) {
        printY = 50;
    } else {
        printY = 30;
    }
    switch (sProfilerPage) {
        case 0:
            drawCore:
            gDPPipeSync(gCurrDisplayList++);
            gDPSetCycleType(gCurrDisplayList++, G_CYC_1CYCLE);
            gDPSetRenderMode(gCurrDisplayList++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineMode(gCurrDisplayList++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetPrimColor(gCurrDisplayList++, 0, 0, 0, 0, 0, 160);
            gDPFillRectangle(gCurrDisplayList++, TEXT_OFFSET - 2, 8, 112, printY + 2);
            gDPFillRectangle(gCurrDisplayList++, ((gScreenWidth/2) / 3) - 42, gScreenHeight - 30, ((gScreenWidth/2) / 3) + 62, gScreenHeight - 6);
            gDPPipeSync(gCurrDisplayList++);
            set_text_background_colour(0, 0, 0, 0);
            set_kerning(FALSE);
            puppyprintf(textBytes,  "FPS: %2.2f", gFPS);
            draw_text(&gCurrDisplayList, TEXT_OFFSET, 10, textBytes, ALIGN_TOP_LEFT);
            puppyprintf(textBytes,  "CPU: %dus", gPuppyTimers.cpuTime);
            draw_text(&gCurrDisplayList, TEXT_OFFSET, 20, textBytes, ALIGN_TOP_LEFT);
            puppyprintf(textBytes,  "(%d%%)", gPuppyTimers.cpuTime / 333);
            draw_text(&gCurrDisplayList, 112 - 4, 20, textBytes, ALIGN_TOP_RIGHT);
            if (IO_READ(DPC_PIPEBUSY_REG) + IO_READ(DPC_CLOCK_REG) + IO_READ(DPC_TMEM_REG)) {
                puppyprintf(textBytes,  "RSP: %dus", gPuppyTimers.rspTime);
                draw_text(&gCurrDisplayList, TEXT_OFFSET, 30, textBytes, ALIGN_TOP_LEFT);
                puppyprintf(textBytes,  "(%d%%)", gPuppyTimers.rspTime / 333);
                draw_text(&gCurrDisplayList, 112 - 4, 30, textBytes, ALIGN_TOP_RIGHT);
                puppyprintf(textBytes,  "RDP: %dus", gPuppyTimers.rdpTime);
                draw_text(&gCurrDisplayList, TEXT_OFFSET, 40, textBytes, ALIGN_TOP_LEFT);
                puppyprintf(textBytes,  "(%d%%)", gPuppyTimers.rdpTime / 333);
                draw_text(&gCurrDisplayList, 112 - 4, 40, textBytes, ALIGN_TOP_RIGHT);
            }
            //puppyprintf(textBytes,  "RAM: 0x%06X/0x%06X", gFreeMem[11], osGetMemSize());
            //draw_text(&gCurrDisplayList, ((gScreenWidth/2) / 3) + 10, gScreenHeight - 38, textBytes, ALIGN_TOP_CENTER);
            puppyprintf(textBytes,  "Tri: %d Vtx: %d", sTriCount, sVtxCount);
            draw_text(&gCurrDisplayList, ((gScreenWidth/2) / 3) + 10, gScreenHeight - 28, textBytes, ALIGN_TOP_CENTER);
            puppyprintf(textBytes, "Gfx: %d / %d", ((u32)gCurrDisplayList - (u32)gDisplayLists[gSPTaskNum]) / sizeof(Gfx), gCurrNumF3dCmdsPerPlayer);
            draw_text(&gCurrDisplayList, ((gScreenWidth/2) / 3) + 10, gScreenHeight - 18, textBytes, ALIGN_TOP_CENTER);
            break;
        case 1:
            gDPPipeSync(gCurrDisplayList++);
            gDPSetCycleType(gCurrDisplayList++, G_CYC_1CYCLE);
            gDPSetRenderMode(gCurrDisplayList++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineMode(gCurrDisplayList++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetPrimColor(gCurrDisplayList++, 0, 0, 0, 0, 0, 96);
            gDPFillRectangle(gCurrDisplayList++, gScreenWidth - 144, 0, gScreenWidth, SCREEN_HEIGHT);
            gDPPipeSync(gCurrDisplayList++);
            set_text_background_colour(0, 0, 0, 0);
            set_kerning(FALSE);
            for (i = 0; i < PP_RSP_GFX; i++) {
                if (gPuppyTimers.timers[sPrintOrder[i]][PERF_TOTAL] == 0) {
                    continue;
                }
                puppyprintf(textBytes,  "%s \t%dus (%d%%)", sPuppyPrintStrings[sPrintOrder[i]], gPuppyTimers.timers[sPrintOrder[i]][PERF_TOTAL], gPuppyTimers.timers[sPrintOrder[i]][PERF_TOTAL] / 333);
                draw_text(&gCurrDisplayList, gScreenWidth - 136, y, textBytes, ALIGN_TOP_LEFT);
                y += 10;
                if (y > gScreenHeight - 16) {
                    break;
                }
            }
            goto drawCore;
            break;
        case 2:
            gDPPipeSync(gCurrDisplayList++);
            gDPSetCycleType(gCurrDisplayList++, G_CYC_1CYCLE);
            gDPSetRenderMode(gCurrDisplayList++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineMode(gCurrDisplayList++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetPrimColor(gCurrDisplayList++, 0, 0, 0, 0, 0, 96);
            gDPFillRectangle(gCurrDisplayList++, gScreenWidth - 144, 0, gScreenWidth, SCREEN_HEIGHT);
            gDPPipeSync(gCurrDisplayList++);
            set_text_background_colour(0, 0, 0, 0);
            set_kerning(FALSE);
            for (i = 0; i < NUM_OBJECT_PRINTS; i++) {
                if (gPuppyTimers.objTimers[sObjPrintOrder[i]][PERF_TOTAL] == 0) {
                    continue;
                }
                puppyprintf(textBytes,  "%d \t%dus (%d%%)", sObjPrintOrder[i], gPuppyTimers.objTimers[sObjPrintOrder[i]][PERF_TOTAL], gPuppyTimers.objTimers[sObjPrintOrder[i]][PERF_TOTAL] / 333);
                draw_text(&gCurrDisplayList, gScreenWidth - 136, y, textBytes, ALIGN_TOP_LEFT);
                y += 10;
                if (y > gScreenHeight - 16) {
                    break;
                }
            }
            goto drawCore;
            break;
        case 3:
            gDPPipeSync(gCurrDisplayList++);
            gDPSetCycleType(gCurrDisplayList++, G_CYC_1CYCLE);
            gDPSetRenderMode(gCurrDisplayList++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineMode(gCurrDisplayList++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetPrimColor(gCurrDisplayList++, 0, 0, 0, 0, 0, 96);
            gDPFillRectangle(gCurrDisplayList++, gScreenWidth - 144, 0, gScreenWidth, SCREEN_HEIGHT);
            gDPPipeSync(gCurrDisplayList++);
            set_text_background_colour(0, 0, 0, 0);
            set_kerning(FALSE);
            for (i = 0; i < sizeof(sPuppyprintMemColours) / 16; i++) {
                puppyprintf(textBytes,  "%s:\t0x%X\n", sPuppyprintMemColours[i], gFreeMem[i]);
                draw_text(&gCurrDisplayList, gScreenWidth - 136, y, textBytes, ALIGN_TOP_LEFT);
                y += 10;
                if (y > gScreenHeight - 16) {
                    break;
                }
            }
            goto drawCore;
            break;
    }
    
    if (sPrevLoadTimer > 0) {
        gDPPipeSync(gCurrDisplayList++);
        gDPSetCycleType(gCurrDisplayList++, G_CYC_1CYCLE);
        gDPSetRenderMode(gCurrDisplayList++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(gCurrDisplayList++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(gCurrDisplayList++, 0, 0, 0, 0, 0, 160);
        gDPFillRectangle(gCurrDisplayList++, (gScreenWidth/2) - 72, gScreenHeight - 84, (gScreenWidth/2) + 72, gScreenHeight - 12);
        puppyprintf(textBytes, "DMA in %2.3fs", gPrevLoadTimeDMA / 1000000.0f);
        draw_text(&gCurrDisplayList, gScreenWidth/2, gScreenHeight - 74, textBytes, ALIGN_MIDDLE_CENTER);
        puppyprintf(textBytes, "Decompressed in %2.3fs", gPrevLoadTimeDecompress / 1000000.0f);
        draw_text(&gCurrDisplayList, gScreenWidth/2, gScreenHeight - 62, textBytes, ALIGN_MIDDLE_CENTER);
        puppyprintf(textBytes, "Track built in %2.3fs", gPrevLoadTimeModel / 1000000.0f);
        draw_text(&gCurrDisplayList, gScreenWidth/2, gScreenHeight - 50, textBytes, ALIGN_MIDDLE_CENTER);
        puppyprintf(textBytes, "Objects spawned in %2.3fs", gPrevLoadTimeObjects / 1000000.0f);
        draw_text(&gCurrDisplayList, gScreenWidth/2, gScreenHeight - 38, textBytes, ALIGN_MIDDLE_CENTER);
        puppyprintf(textBytes, "Textures built in %2.3fs", gPrevLoadTimeTexture / 1000000.0f);
        draw_text(&gCurrDisplayList, gScreenWidth/2, gScreenHeight - 26, textBytes, ALIGN_MIDDLE_CENTER);
        puppyprintf(textBytes, "Level loaded in %2.3fs", sPrevLoadTimeTotal / 1000000.0f);
        draw_text(&gCurrDisplayList, gScreenWidth/2, gScreenHeight - 14, textBytes, ALIGN_MIDDLE_CENTER);
        if (sPrevLoadTimer - sLogicUpdateRate > 0) {
            sPrevLoadTimer -= sLogicUpdateRate;
        } else {
            sPrevLoadTimer = 0;
        }
    }
    /*if (sProfilerPage == 0) {
#ifdef FIFO_UCODE
        if (!suCodeSwitch) {
            draw_text(&gCurrDisplayList, TEXT_OFFSET, printY, "GFX: FIFO", ALIGN_TOP_LEFT);
        } else {
 #endif
            draw_text(&gCurrDisplayList, TEXT_OFFSET, printY, "GFX: XBUS", ALIGN_TOP_LEFT);
 #ifdef FIFO_UCODE
        }
 #endif
        puppyprintf(textBytes,  "Tri: %d Vtx: %d", sTriCount, sVtxCount);
        draw_text(&gCurrDisplayList, (gScreenWidth/2) / 2, gScreenHeight - 4, textBytes, ALIGN_BOTTOM_CENTER);
        puppyprintf(textBytes, "Gfx: %d / %d", ((u32)gCurrDisplayList - (u32)gDisplayLists[gSPTaskNum]) / sizeof(Gfx), gCurrNumF3dCmdsPerPlayer);
        draw_text(&gCurrDisplayList, (gScreenWidth/2) + ((gScreenWidth/2) / 2), gScreenHeight - 4, textBytes, ALIGN_BOTTOM_CENTER);
        printY = 40;
    }*/
}


void swapu(u8* xp, u8* yp)
{
    u8 temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void swapu16(u16* xp, u16* yp)
{
    u16 temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void calculate_print_order(void) {
    u32 i, j, min_idx;
    for (i = 0; i < PP_RSP_GFX; i++) {
        sPrintOrder[i] = i;
    }

    // One by one move boundary of unsorted subarray
    for (i = 0; i < PP_RSP_AUD; i++) {

        if (gPuppyTimers.timers[sPrintOrder[i]][PERF_TOTAL] == 0)
            continue;
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < PP_RSP_AUD; j++)
            if (gPuppyTimers.timers[sPrintOrder[j]][PERF_TOTAL] > gPuppyTimers.timers[sPrintOrder[min_idx]][PERF_TOTAL])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swapu(&sPrintOrder[min_idx], &sPrintOrder[i]);
    }
}

void calculate_obj_print_order(void) {
    u32 i, j, min_idx;
    for (i = 0; i < NUM_OBJECT_PRINTS; i++) {
        sObjPrintOrder[i] = i;
    }

    // One by one move boundary of unsorted subarray
    for (i = 0; i < NUM_OBJECT_PRINTS; i++) {

        if (gPuppyTimers.objTimers[sObjPrintOrder[i]][PERF_TOTAL] == 0)
            continue;
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < NUM_OBJECT_PRINTS; j++)
            if (gPuppyTimers.objTimers[sObjPrintOrder[j]][PERF_TOTAL] > gPuppyTimers.objTimers[sObjPrintOrder[min_idx]][PERF_TOTAL])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swapu16(&sObjPrintOrder[min_idx], &sObjPrintOrder[i]);
    }
}

void update_rdp_profiling(void) {
    rdp_profiler_update(gPuppyTimers.timers[PP_RDP_BUF], IO_READ(DPC_BUFBUSY_REG));
    rdp_profiler_update(gPuppyTimers.timers[PP_RDP_BUS], IO_READ(DPC_TMEM_REG));
    rdp_profiler_update(gPuppyTimers.timers[PP_RDP_TMM], IO_READ(DPC_PIPEBUSY_REG));
    IO_WRITE(DPC_STATUS_REG, DPC_CLR_CLOCK_CTR | DPC_CLR_CMD_CTR | DPC_CLR_PIPE_CTR | DPC_CLR_TMEM_CTR);
}

/// Add whichever times you wish to create aggregates of.
void puppyprint_calculate_average_times(void) {
    s32 i;
    s32 j;
    u32 highTime = 0;
    u32 lowTime = 0xFFFFFFFF;
    u32 first = osGetCount();
    /*for (i = 1; i < PP_RDP_BUS; i++) {
        gPuppyTimers.timers[i][PERF_TOTAL] = OS_CYCLES_TO_USEC(gPuppyTimers.timers[i][PERF_AGGREGATE]) / NUM_PERF_ITERATIONS;
        if (i < PP_RSP_AUD - 1) {
            gPuppyTimers.cpuTime += gPuppyTimers.timers[i][PERF_TOTAL];
        }
    }*/
    
    for (i = 1; i < NUM_OBJECT_PRINTS; i++) {
        gPuppyTimers.objTimers[i][PERF_TOTAL] = (gPuppyTimers.objTimers[i][PERF_AGGREGATE]) / NUM_PERF_ITERATIONS;
    }
    gPuppyTimers.timers[PP_LOGIC][PERF_TOTAL] = OS_CYCLES_TO_USEC(gPuppyTimers.timers[PP_LOGIC][PERF_AGGREGATE]) / NUM_PERF_ITERATIONS;
    if (gPuppyTimers.timers[PP_LOGIC][PERF_TOTAL] > OS_CYCLES_TO_USEC(99999)) {
        gPuppyTimers.timers[PP_LOGIC][PERF_TOTAL] = 0;
    }
    gPuppyTimers.timers[PP_RSP_AUD][PERF_TOTAL] = OS_CYCLES_TO_USEC(gPuppyTimers.timers[PP_RSP_AUD][PERF_AGGREGATE]) / NUM_PERF_ITERATIONS;
    gPuppyTimers.timers[PP_RSP_GFX][PERF_TOTAL] = OS_CYCLES_TO_USEC(gPuppyTimers.timers[PP_RSP_GFX][PERF_AGGREGATE]) / NUM_PERF_ITERATIONS;
    gPuppyTimers.timers[PP_RDP_BUF][PERF_TOTAL] = (gPuppyTimers.timers[PP_RDP_BUF][PERF_AGGREGATE] * 10) / (625*NUM_PERF_ITERATIONS);
    gPuppyTimers.timers[PP_RDP_BUS][PERF_TOTAL] = (gPuppyTimers.timers[PP_RDP_BUS][PERF_AGGREGATE] * 10) / (625*NUM_PERF_ITERATIONS);
    gPuppyTimers.timers[PP_RDP_TMM][PERF_TOTAL] = (gPuppyTimers.timers[PP_RDP_TMM][PERF_AGGREGATE] * 10) / (625*NUM_PERF_ITERATIONS);
    gPuppyTimers.rspTime = gPuppyTimers.timers[PP_RSP_AUD][PERF_TOTAL] + gPuppyTimers.timers[PP_RSP_GFX][PERF_TOTAL];
    gPuppyTimers.rdpTime = MAX(gPuppyTimers.timers[PP_RDP_BUF][PERF_TOTAL], gPuppyTimers.timers[PP_RDP_BUS][PERF_TOTAL]);
    gPuppyTimers.rdpTime = MAX(gPuppyTimers.timers[PP_RDP_TMM][PERF_TOTAL], gPuppyTimers.rdpTime);
    // Find the earliest snapshot and the latest snapshot.
    for (i = 0; i < NUM_THREAD_TIMERS; i++) {
        for (j = 0; j < gPuppyTimers.threadIteration[i / 2]; j++) {
            // If an iteration crosses over mid read, the low time could be zero, which would ruin this whole gig.
            if (gPuppyTimers.threadTimes[gPuppyTimers.threadIteration[j]][i] < lowTime && gPuppyTimers.threadTimes[gPuppyTimers.threadIteration[j]][i] != 0) {
                lowTime = gPuppyTimers.threadTimes[gPuppyTimers.threadIteration[j]][i];
            }
            if (gPuppyTimers.threadTimes[gPuppyTimers.threadIteration[j]][i] > highTime) {
                highTime = gPuppyTimers.threadTimes[gPuppyTimers.threadIteration[j]][i];
            }
        }
    }
    gPuppyTimers.cpuTotal[PERF_AGGREGATE] -= gPuppyTimers.cpuTotal[perfIteration];
    gPuppyTimers.cpuTotal[perfIteration] = MIN(highTime - lowTime, OS_USEC_TO_CYCLES(99999));
    gPuppyTimers.cpuTotal[PERF_AGGREGATE] += gPuppyTimers.cpuTotal[perfIteration];
    gPuppyTimers.cpuTotal[PERF_TOTAL] = OS_CYCLES_TO_USEC(gPuppyTimers.cpuTotal[PERF_AGGREGATE]) / NUM_PERF_ITERATIONS;
    gPuppyTimers.cpuTime = gPuppyTimers.cpuTotal[PERF_TOTAL];
    bzero(&gPuppyTimers.threadIteration, sizeof(gPuppyTimers.threadIteration));
    bzero(&gPuppyTimers.threadTimes, sizeof(gPuppyTimers.threadTimes));
    if (sProfilerPage == 1) {
        calculate_print_order();
    } else if (sProfilerPage == 2) {
        calculate_obj_print_order();
    }
}

void puppyprint_update_rsp(u8 flags) {
    switch (flags) {
    case RSP_GFX_START:
        gPuppyTimers.rspGfxBufTime = (u32) osGetCount();
        gPuppyTimers.rspPauseTime = 0;
        break;
    case RSP_AUDIO_START:
        gPuppyTimers.rspAudioBufTime = (u32 )osGetCount();
        break;
    case RSP_GFX_PAUSED:
        gPuppyTimers.rspPauseTime = (u32) osGetCount();
        break;
    case RSP_GFX_RESUME:
        gPuppyTimers.rspPauseTime = (u32) osGetCount() - gPuppyTimers.rspPauseTime;
        break;
    case RSP_GFX_FINISHED:
        gPuppyTimers.timers[PP_RSP_GFX][PERF_AGGREGATE] -= gPuppyTimers.timers[PP_RSP_GFX][perfIteration];
        gPuppyTimers.timers[PP_RSP_GFX][perfIteration] = (u32) (osGetCount() - gPuppyTimers.rspGfxBufTime) + gPuppyTimers.rspPauseTime;
        if (gPuppyTimers.timers[PP_RSP_GFX][perfIteration] > OS_USEC_TO_CYCLES(99999)) {
            gPuppyTimers.timers[PP_RSP_GFX][perfIteration] = OS_USEC_TO_CYCLES(99999);
        }
        gPuppyTimers.timers[PP_RSP_GFX][PERF_AGGREGATE] += gPuppyTimers.timers[PP_RSP_GFX][perfIteration];
        break;
    case RSP_AUDIO_FINISHED:
        gPuppyTimers.timers[PP_RSP_AUD][PERF_AGGREGATE] -= gPuppyTimers.timers[PP_RSP_AUD][perfIteration];
        gPuppyTimers.timers[PP_RSP_AUD][perfIteration] = (u32) osGetCount() - gPuppyTimers.rspAudioBufTime;
        if (gPuppyTimers.timers[PP_RSP_AUD][perfIteration] > OS_USEC_TO_CYCLES(99999)) {
            gPuppyTimers.timers[PP_RSP_AUD][perfIteration] = OS_USEC_TO_CYCLES(99999);
        }
        gPuppyTimers.timers[PP_RSP_AUD][PERF_AGGREGATE] += gPuppyTimers.timers[PP_RSP_AUD][perfIteration];
        break;
    }
}

void count_triangles_in_dlist(u8 *dlist, u8 *dlistEnd) {
    s32 triCount = 0;
    s32 vtxCount = 0;
    while(dlist < dlistEnd) {
        switch(dlist[0]) {
            case G_TRIN: // TRIN
                triCount += (dlist[1] >> 4) + 1;
                break;
            case G_VTX:
                vtxCount += (dlist[1] >> 4) + 1;
                break;
        }
        dlist += 8;
    }
    sTriCount = triCount;
    sVtxCount = vtxCount;
}

void count_triangles(u8 *dlist, u8 *dlistEnd) {
    u32 first = osGetCount();
    sTimerTemp++;
    if ((sTimerTemp % 16) == 0) {
        s32 first = osGetCount();
        count_triangles_in_dlist(dlist, dlistEnd);
        sTimerTemp = (s32) OS_CYCLES_TO_USEC(osGetCount() - first);
    }
    profiler_add(gPuppyTimers.timers[PP_PROFILER], osGetCount() - first);
}
#endif
