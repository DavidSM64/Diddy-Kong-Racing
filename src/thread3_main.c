/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8006C330 */

#include "thread3_main.h"

#include <PR/os_cont.h>
#include <PR/gu.h>
#include <PR/os_time.h>
#include "memory.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "asset_enums.h"
#include "asset_loading.h"
#include "menu.h"
#include "video.h"
#include "set_rsp_segment.h"
#include "gzip.h"
#include "printf.h"
#include "thread0_epc.h"
#include "thread30_track_loading.h"
#include "weather.h"
#include "audio.h"
#include "objects.h"
#include "camera.h"
#include "save_data.h"
#include "unknown_078050.h"
#include "audiosfx.h"
#include "audiomgr.h"
#include "unknown_032760.h"
#include "textures_sprites.h"
#include "PR/os_internal.h"
#include "printf.h"
#include "fade_transition.h"
#include "borders.h"
#include "unknown_008C40.h"
#include "unknown_0255E0.h"
#include "game_text.h"
#include "game_ui.h"
#include "main.h"
#include "object_models.h"
#include "racer.h"
#include "particles.h"
#include "math_util.h"
#include "controller.h"
#include "game.h"

#include "config.h"
#ifdef ENABLE_USB
#include "usb/dkr_usb.h"
#endif

/************ .data ************/

s8 sAntiPiracyTriggered = 0;
s32 gSaveDataFlags = 0; //Official Name: load_save_flags
s32 gScreenStatus = OSMESG_SWAP_BUFFER;
s32 sControllerStatus = 0;
s8 gSkipGfxTask = FALSE;
s8 D_800DD390 = 0;
s16 gLevelLoadTimer = 0;
s8 D_800DD398 = 0;
s8 gFutureFunLandLevelTarget = FALSE;
s8 gDmemInvalid = FALSE;
s32 gNumF3dCmdsPerPlayer[4] = NUM_GFX_COMMANDS;
s32 gNumHudVertsPerPlayer[4] = NUM_VERTICES;
s32 gNumHudMatPerPlayer[4] = NUM_MATRICES;
s32 gNumHudTrisPerPlayer[4] = NUM_HUD_VERTS;
s8 gDrawFrameTimer = 0;
FadeTransition D_800DD3F4 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_UNK2, FADE_COLOR_BLACK, 20, 0);
s32 sLogicUpdateRate = LOGIC_5FPS;
FadeTransition D_800DD408 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 30, -1);
FadeTransition gLevelFadeOutTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 30, -1);
FadeTransition D_800DD424 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 260, -1);
s32 gNumGfxTasksAtScheduler = 0;

/*******************************/

/************ .bss ************/

Gfx *gDisplayLists[2];
Gfx *gCurrDisplayList;
MatrixS *gMatrixHeap[2];
MatrixS *gGameCurrMatrix;
Vertex *gVertexHeap[2];
Vertex *gGameCurrVertexList;
TriangleList *gTriangleHeap[2];
TriangleList *gGameCurrTriList;
s8 D_80121250[16]; //Settings4C
OSSched gMainSched; // 0x288 / 648 bytes
u64 gSchedStack[THREAD5_STACK / sizeof(u64)];
s32 gSPTaskNum;
s32 sRenderContext;
s32 gRenderMenu; // I don't think this is ever not 1
// Similar to gMapId, but is 0 if not currently playing a level (e.g. start menu).
s32 gPlayableMapId;
s32 D_801234F8;
s32 D_801234FC;
s32 gGameNumPlayers;
s32 gGameCurrentEntrance;
s32 gGameCurrentCutscene;
s32 gPrevPlayerCount;
Settings *gSettingsPtr;
s8 gIsLoading;
s8 gIsPaused;
s8 gPostRaceViewPort;
Vehicle gLevelDefaultVehicleID;
Vehicle D_8012351C; // Looks to be the current level's vehicle ID.
s32 sBootDelayTimer;
s8 gLevelLoadType;
s8 gNextMap;
s32 gCurrNumF3dCmdsPerPlayer;
s32 gCurrNumHudMatPerPlayer;
s32 gCurrNumHudTrisPerPlayer;
s32 gCurrNumHudVertsPerPlayer;
OSScClient *gNMISched[3];
OSMesg gGameMesgBuf[3];
OSMesgQueue gGameMesgQueue;
s32 gNMIMesgBuf; //Official Name: resetPressed

/******************************/


/**
 * Main looping function for the main thread.
 * Official Name: mainThread
 */
void thread3_main(UNUSED void *unused) {
    OSMesg mesg;

    init_game();
    gSaveDataFlags = handle_save_data_and_read_controller(gSaveDataFlags, 0);
    sBootDelayTimer = 0;
    sRenderContext = DRAW_INTRO;

    while (1) {
        while (gNumGfxTasksAtScheduler < 2) {
            main_game_loop();
        }

        osRecvMesg(&gGameMesgQueue, &mesg, OS_MESG_BLOCK);

        switch ((s32) mesg) {
        case OS_SC_DONE_MSG:
            gNumGfxTasksAtScheduler--;
            break;

        case OS_SC_PRE_NMI_MSG:
            gNMIMesgBuf = TRUE;
            func_80072708();
            audioStopThread();
            stop_thread30();
            __osSpSetStatus(SP_SET_HALT | SP_CLR_INTR_BREAK | SP_CLR_YIELD | SP_CLR_YIELDED | SP_CLR_TASKDONE | SP_CLR_RSPSIGNAL
                    | SP_CLR_CPUSIGNAL | SP_CLR_SIG5 | SP_CLR_SIG6 | SP_CLR_SIG7);
            osDpSetStatus(DPC_SET_XBUS_DMEM_DMA | DPC_CLR_FREEZE | DPC_CLR_FLUSH | DPC_CLR_TMEM_CTR | DPC_CLR_PIPE_CTR
                    | DPC_CLR_CMD_CTR | DPC_CLR_CMD_CTR);
            while (1);
            break;
        }
    }
}


struct ConfigOptions gConfig;
u8 gHideHUD = FALSE;
u8 gSkipCutbacks = FALSE;

void init_config(void) {
    bzero(&gConfig, sizeof(gConfig));
    if (gPlatform & EMULATOR) {
        gConfig.noCutbacks = TRUE;
        gConfig.antiAliasing = 1;
        gConfig.dedither = TRUE;
    }
    gSkipCutbacks = gConfig.noCutbacks;
}

/**
 * Setup all of the necessary pieces required for the game to function.
 * This includes the memory pool. controllers, video, audio, core assets and more.
 * Official Name: mainInitGame
 */
void init_game(void) {
    s32 i;

    init_main_memory_pool();
    rzipInit(); // Initialise gzip decompression related things
#ifndef NO_ANTIPIRACY
    sAntiPiracyTriggered = TRUE;
    if (check_imem_validity()) {
        sAntiPiracyTriggered = FALSE;
    }
#endif
    gIsLoading = FALSE;
    gLevelDefaultVehicleID = VEHICLE_CAR;

    osCreateScheduler(&gMainSched, &gSchedStack[0x40], OS_SC_PRIORITY, (u8) 0, 1);
    init_video(VIDEO_MODE_LOWRES_LPN, &gMainSched);
    init_PI_mesg_queue();
    setup_gfx_mesg_queues(&gMainSched);
    audio_init(&gMainSched);
    func_80008040(); // Should be very similar to allocate_object_model_pools
    sControllerStatus = init_controllers();
    tex_init_textures();
    allocate_object_model_pools();
    allocate_object_pools();
    diPrintfInit();
    allocate_ghost_data();
    init_particle_assets();
    init_weather();
    calc_and_alloc_heap_for_settings();
    default_alloc_displaylist_heap();
    load_fonts();
    init_controller_paks();
    func_80081218(); // init_save_data
    create_and_start_thread30();
#ifdef ENABLE_USB
    init_usb_thread();
#endif
    osCreateMesgQueue(&gGameMesgQueue, gGameMesgBuf, 3);
    osScAddClient(&gMainSched, (OSScClient*) gNMISched, &gGameMesgQueue, OS_SC_ID_VIDEO);
    gNMIMesgBuf = 0;
    gGameCurrentEntrance = 0;
    gGameCurrentCutscene = 0;
    gSPTaskNum = 0;

    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);
    get_platform();
    init_config();

    osSetTime(0);
}

#ifdef FIFO_UCODE
s8 suCodeSwitch = 0;
#endif

u32 sPrevTime = 0;
u32 sDeltaTime = 0;
s32 sTotalTime = 0;
u8 gOverrideAA = 0;
s32 gOverrideTimer = 0;

extern s32 gVideoSkipNextRate;

s32 calculate_updaterate(void) {
    static u32 prevtime = 0;
    static s32 remainder = 0;
    s32 total;
    s32 rate;

    u32 now = osGetCount();

    if (gVideoSkipNextRate) {
        rate = LOGIC_60FPS;
        remainder = 0;
        gVideoSkipNextRate = FALSE;
    } else {
        if (now > prevtime) {
            total = (u32) (now - prevtime) + remainder;
        } else {
            // Counter has reset since last time
            total = (0xffffffff - prevtime) + 1 + now + remainder;
        }

        if (total < (OS_CPU_COUNTER / 30)) { // 30-60 fps
            rate = LOGIC_60FPS;
        } else if (total < (OS_CPU_COUNTER / 20)) { // 20-30 fps
            rate = LOGIC_30FPS;
        } else if (total < (OS_CPU_COUNTER / 15)) {
            rate = LOGIC_20FPS;
        } else if (total < (OS_CPU_COUNTER / 12)) {
            rate = LOGIC_15FPS;
        } else if (total < (OS_CPU_COUNTER / 10)) {
            rate = LOGIC_12FPS;
        } else {
            rate = LOGIC_10FPS;
        }

        remainder = total - rate * (OS_CPU_COUNTER / 60);
    }

    prevtime = now;

    return rate;
}


/**
 * The main gameplay loop.
 * Contains all game logic, audio and graphics processing.
 */
void main_game_loop(void) {
    s32 framebufferSize;
    s32 tempLogicUpdateRate, tempLogicUpdateRateMax;
#ifdef PUPPYPRINT_DEBUG
    profiler_reset_values();
    profiler_snapshot(THREAD4_START);
#endif

#ifdef ENABLE_USB
    tick_usb_thread();
#endif

    /*if (gVideoSkipNextRate) {
        sLogicUpdateRate = LOGIC_60FPS;
        sTotalTime = 0;
        sPrevTime = 0;
        gVideoSkipNextRate = FALSE;
    } else {
        sDeltaTime = osGetCount() - sPrevTime;
        sPrevTime = osGetCount();
        sTotalTime += OS_CYCLES_TO_USEC(sDeltaTime);
        sTotalTime -= 16666;
        sLogicUpdateRate = LOGIC_60FPS;
        while (sTotalTime > 16666) {
            sTotalTime -= 16666;
            sLogicUpdateRate++;
            if (sLogicUpdateRate == 4) {
                sTotalTime = 0;
            }
            if (sLogicUpdateRate > D_801262E4) {
                sLogicUpdateRate = D_801262E4;
            }

        }
    }*/

    sLogicUpdateRate = calculate_updaterate();

    if (gConfig.antiAliasing == 1) {
        gOverrideTimer -= 40000;
        gOverrideTimer += MIN(OS_CYCLES_TO_USEC(sDeltaTime), 66666);
        if (gOverrideTimer <= -125000) {
            gOverrideTimer = -125000;
            if (gOverrideAA == TRUE) {
                gOverrideAA = FALSE;
                //set_dither_filter();
            }
        }
        if (gOverrideTimer >= 125000) {
            gOverrideTimer = 125000;
            if (gOverrideAA == FALSE) {
                gOverrideAA = TRUE;
                //set_dither_filter();
            }
        }
    }

    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gGameCurrMatrix = gMatrixHeap[gSPTaskNum];
    gGameCurrVertexList = gVertexHeap[gSPTaskNum];
    gGameCurrTriList = gTriangleHeap[gSPTaskNum];

    set_rsp_segment(&gCurrDisplayList, 0, 0);
    set_rsp_segment(&gCurrDisplayList, 1, (s32) gVideoLastFramebuffer);
    set_rsp_segment(&gCurrDisplayList, 2, (s32) gVideoLastDepthBuffer);
    set_rsp_segment(&gCurrDisplayList, 4, (s32) gVideoLastFramebuffer - 0x500);
    init_rsp(&gCurrDisplayList);
    init_rdp_and_framebuffer(&gCurrDisplayList);
    render_background(&gCurrDisplayList, (Matrix *) &gGameCurrMatrix, TRUE); 
    gSaveDataFlags = handle_save_data_and_read_controller(gSaveDataFlags, sLogicUpdateRate);
    switch (sRenderContext) {
        case DRAW_INTRO: // Pre-boot screen
            pre_intro_loop();
            break;
        case DRAW_MENU: // In a menu
            func_8006DCF8(sLogicUpdateRate);
            break;
        case DRAW_GAME: // In game (Controlling a character)
            ingame_logic_loop(sLogicUpdateRate);
            break;
    }

    // This is a good spot to place custom text if you want it to overlay it over ALL the
    // menus & gameplay.
    
#ifdef ENABLE_USB
#ifdef SHOW_USB_INFO
    render_usb_info();
#endif
#endif

    handle_music_fade(sLogicUpdateRate);
    print_debug_strings(&gCurrDisplayList);
    render_dialogue_boxes(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList);
    close_dialogue_box(4);
    assign_dialogue_box_id(4);
    // handle_transitions will perform the logic of transitions and return the transition ID.
    if (handle_transitions(sLogicUpdateRate)) {
        render_fade_transition(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList);
    }
    if ((sBootDelayTimer >= 8) && (is_controller_missing())) {
        print_missing_controller_text(&gCurrDisplayList, sLogicUpdateRate);
    }

#ifdef PUPPYPRINT_DEBUG
    gPuppyPrint.mainTimerPoints[0][PP_PROFILER_DRAW] = osGetCount();
    if (gPuppyPrint.enabled) {
        render_profiler();
        count_triangles((u8*) gDisplayLists[gSPTaskNum], (u8*) gCurrDisplayList);
    }
    gPuppyPrint.mainTimerPoints[1][PP_PROFILER_DRAW] = osGetCount();
#endif
    profiler_snapshot(THREAD4_END);

    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);

    copy_viewports_to_stack();
    if (gDrawFrameTimer != 1) {
        if (gSkipGfxTask == FALSE) {
            wait_for_gfx_task();
        }
    } else {
        gDrawFrameTimer = 0;
    }
    gSkipGfxTask = FALSE;
    clear_free_queue();
    if (!gIsPaused) {
        disable_cutscene_camera();
    }
#ifdef PUPPYPRINT_DEBUG
    gPuppyPrint.mainTimerPoints[0][PP_PROFILER_CALC] = osGetCount();
    calculate_and_update_fps();
    puppyprint_calculate_average_times();
    perfIteration++;
    if (perfIteration == NUM_PERF_ITERATIONS - 1) {
        perfIteration = 0;
    }
    gPuppyPrint.mainTimerPoints[1][PP_PROFILER_CALC] = osGetCount();
#endif
    if (gDrawFrameTimer == 2) {
        framebufferSize = SCREEN_WIDTH * SCREEN_HEIGHT * 2;
        dmacopy_doubleword(gVideoLastFramebuffer, gVideoCurrFramebuffer, (s32) gVideoCurrFramebuffer + framebufferSize);
    }

    swap_framebuffer_when_ready();

    if (gDrawFrameTimer == 0) {
#ifndef FIFO_UCODE
        setup_ostask_xbus(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
#else
    #ifdef FIFO_4MB
        if (suCodeSwitch == FALSE && IO_READ(DPC_BUFBUSY_REG) + IO_READ(DPC_CLOCK_REG) + IO_READ(DPC_TMEM_REG)) {
    #else
        if (suCodeSwitch == FALSE && IO_READ(DPC_BUFBUSY_REG) + IO_READ(DPC_CLOCK_REG) + IO_READ(DPC_TMEM_REG) && gExpansionPak) {
    #endif
            setup_ostask_fifo(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
        } else {
            setup_ostask_xbus(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
        }
#endif
        gNumGfxTasksAtScheduler++;
        gSPTaskNum ^= 1;
    }
    if (gDrawFrameTimer) {
        gDrawFrameTimer--;
    }
}

void func_8006CAE4(s32 numPlayers, s32 trackID, Vehicle vehicle) {
    gGameNumPlayers = numPlayers - 1;
    if (trackID == -1) {
        gPlayableMapId = get_track_id_to_load();
    } else {
        gPlayableMapId = trackID; // Unused, because arg1 is always -1.
    }
    load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, vehicle);
}

/**
 * Calls load_level() with the same arguments except for the cutsceneId,
 * which is the value at gGameCurrentCutscene. Also does some other stuff.
 * Used when ingame.
 */
void load_level_game(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId) {
    profiler_begin_timer();
    alloc_displaylist_heap(numberOfPlayers);
    set_free_queue_state(0);
    func_80065EA0();
    func_800C3048();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, gGameCurrentCutscene);
    func_8009ECF0(get_viewport_count());
    func_800AE728(8, 0x10, 0x96, 0x64, 0x32, 0);
    func_8001BF20();
    osSetTime(0);
    sPrevTime = 0;
    set_free_queue_state(2);
    func_80072298(1);
    puppyprint_log("Level [%s] loaded in %2.3fs.", get_level_name(levelId), OS_CYCLES_TO_USEC(osGetCount() - profiler_get_timer()) / 1000000.0f);
}

/**
 * Call numerous functions to clear data in RAM.
 * Then call to free particles, HUD and text.
 * Waits for a GFX task before unloading.
*/
void unload_level_game(void) {
    set_free_queue_state(0);
    if (gSkipGfxTask == FALSE) {
        if (gDrawFrameTimer != 1) {
            wait_for_gfx_task();
        }
        gSkipGfxTask = TRUE;
    }
    clear_audio_and_track();
    transition_begin(&D_800DD3F4);
    func_800AE270();
    func_800A003C();
    func_800C30CC();
    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);
    set_free_queue_state(2);
}

/**
 * The main behaviour function involving all of the ingame stuff.
 * Involves the updating of all objects and setting up the render scene.
*/
void ingame_logic_loop(s32 updateRate) {
    s32 buttonPressedInputs, buttonHeldInputs, i, sp40, sp3C;

    sp40 = 0;
    buttonHeldInputs = 0;
    buttonPressedInputs = 0;

    // Get input data for all 4 players.
    for (i = 0; i < get_active_player_count(); i++) {
        buttonHeldInputs |= get_buttons_held_from_player(i);
        buttonPressedInputs |= get_buttons_pressed_from_player(i);
    }
    
    /*if (get_buttons_pressed_from_player(0) & L_TRIG && !(get_buttons_held_from_player(0) & U_JPAD)) {
        s32 soundID;
        gHideHUD ^= 1;
        if (gHideHUD == 0) {
            soundID = SOUND_TING_HIGH;
        } else {
            soundID = SOUND_TING_LOW;
        }
        play_sound_global(soundID, NULL);
    }*/
#ifndef NO_ANTIPIRACY
    // Spam the start button, making the game unplayable because it's constantly paused.
    if (sAntiPiracyTriggered) {
        buttonPressedInputs |= START_BUTTON;
    }
#endif
    // Update all objects
    if (!gIsPaused) {
        update_time_dialation(updateRate);
        func_80010994(updateRate);
        if (check_if_showing_cutscene_camera() == 0 || func_8001139C()) {
            if ((buttonPressedInputs & START_BUTTON) && (get_level_property_stack_pos() == 0) && (D_800DD390 == 0)
                && (sRenderContext == DRAW_GAME) && (gPostRaceViewPort == NULL) && (gLevelLoadTimer == 0) && (D_800DD398 == 0)) {
                buttonPressedInputs = 0;
                gIsPaused = TRUE;
                func_80093A40();
            }
        }
    } else {
        set_anti_aliasing(TRUE);
    }
    D_800DD398 -= updateRate;
    if (D_800DD398 < 0) {
        D_800DD398 = 0;
    }
    if (gPostRaceViewPort) {
        gIsPaused = FALSE;
    }
    gParticlePtrList_flush();
    func_8001BF20();
#ifdef PUPPYPRINT_DEBUG
    gPuppyPrint.mainTimerPoints[0][PP_LEVELGFX] = osGetCount();
#endif
    render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
#ifdef PUPPYPRINT_DEBUG
    gPuppyPrint.mainTimerPoints[1][PP_LEVELGFX] = osGetCount();
#endif
    if (sRenderContext == DRAW_GAME) {
        // Ignore the user's L/R/Z buttons.
        buttonHeldInputs &= ~(L_TRIG | R_TRIG | Z_TRIG);
    }
    if (gPostRaceViewPort) {
        i = func_80095728(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, updateRate); 
        switch (i) {
            case 2:
                buttonHeldInputs |= (L_TRIG | Z_TRIG);
                break;
            case 1:
                gPostRaceViewPort = NULL;
                func_8006D8F0(-1);
                break;
            case 4:
                clear_level_property_stack(); 
                D_800DD390 = 0;
                buttonHeldInputs |= (L_TRIG | R_TRIG);
                break;
            case 5:
                buttonHeldInputs |= L_TRIG,
                sp40 = 1;
                break;
            case 8:
                buttonHeldInputs |= L_TRIG,
                sp40 = 2;
                break;
            case 9:
                buttonHeldInputs |= L_TRIG,
                sp40 = 3;
                break;
            case 10:
                buttonHeldInputs |= L_TRIG,
                sp40 = 4;
                break;
            case 11:
                buttonHeldInputs |= L_TRIG,
                sp40 = 5;
                break;
            case 12:
                buttonHeldInputs |= L_TRIG,
                sp40 = 6;
                break;
            case 13:
                buttonHeldInputs |= L_TRIG,
                sp40 = 7;
                break;
        }
    }
    func_800C3440(updateRate);
    i = func_800C3400();
    if (i != 0) {
        if (i == 2) {
            gIsPaused = TRUE;
        }
        if (func_800C3400() != 2) {
            gIsPaused = FALSE;
            n_alSeqpDelete();
        }
    }
    if (gIsPaused) {
        i = render_pause_menu(&gCurrDisplayList, updateRate);
        switch (i - 1) {
            case 0:
                gIsPaused = FALSE;
                break;
            case 1:
                func_80001050();
                func_800C314C();
                if (func_80023568() != 0 && is_in_two_player_adventure()) {
                    func_8006F398();
                }
                buttonHeldInputs |= (L_TRIG | Z_TRIG);
                break;
            case 2:
                func_80001050();
                func_800C314C();
                if (func_80023568() != 0 && is_in_two_player_adventure()) {
                    func_8006F398();
                }
                buttonHeldInputs |= L_TRIG;
                break;
            case 4:
                sp40 = 1;
                func_800C314C();
                buttonHeldInputs |= L_TRIG;
                break;
            case 11:
                sp40 = 6;
                func_800C314C();
                buttonHeldInputs |= L_TRIG;
                break;
            case 5:
                gIsPaused = FALSE;
                break;
            case 6:
                func_80022E18(1);
                gIsPaused = FALSE;
                break;
            case 3:
                D_800DD390 = 0;
                func_80001050();
                func_800C314C();
                clear_level_property_stack();
                buttonHeldInputs |= (L_TRIG | R_TRIG);
                break;
        }
    }
    init_rdp_and_framebuffer(&gCurrDisplayList);
    render_borders_for_multiplayer(&gCurrDisplayList);
    render_minimap_and_misc_hud(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, updateRate);
    //render_second_multiplayer_borders(&gCurrDisplayList);
    if (gFutureFunLandLevelTarget) {
        if (func_800214C4() != 0) {
            gPlayableMapId = ASSET_LEVEL_FUTUREFUNLANDHUB;
            D_801234F8 = 1;
            gGameCurrentEntrance = 0;
            gFutureFunLandLevelTarget = FALSE;
        }
    }
    sp3C = FALSE;
    if (D_800DD390 != 0) {
        D_800DD390 -= updateRate;
        if (D_800DD390 <= 0) {
            D_800DD390 = 0;
            push_level_property_stack(ASSET_LEVEL_CENTRALAREAHUB, 0, VEHICLE_CAR, CUTSCENE_ID_NONE);
            push_level_property_stack(ASSET_LEVEL_WIZPIGAMULETSEQUENCE, 0, -1, CUTSCENE_ID_UNK_A);
            sp3C = TRUE;
        }
    }
    if (gLevelLoadTimer > 0) {
        gLevelLoadTimer -= updateRate;
        if (gLevelLoadTimer <= 0) {
            buttonHeldInputs = L_TRIG;
            sp3C = TRUE;
            switch (gLevelLoadType) {
                case LEVEL_LOAD_UNK1:
                    buttonHeldInputs = (L_TRIG | Z_TRIG);
                    break;
                case LEVEL_LOAD_TROPHY_RACE:
                    sp40 = 3;
                    func_80098208();
                    D_801234FC = 2;
                    break;
                case LEVEL_LOAD_LIGHTHOUSE_CUTSCENE:
                    gFutureFunLandLevelTarget = TRUE;
                    // fall-through
                case LEVEL_LOAD_FUTURE_FUN_LAND:
                    D_801234F8 = 1;
                    gPlayableMapId = gNextMap;
                    gGameCurrentEntrance = 0;
                    gGameCurrentCutscene = 0;
                    buttonHeldInputs = 0;
                    break;
            }
            gLevelLoadType = LEVEL_LOAD_NORMAL;
            gLevelLoadTimer = 0;
        }
    }
    if (sp3C) {
        if (get_level_property_stack_pos() != 0) {
            pop_level_property_stack(&gPlayableMapId, &gGameCurrentEntrance, &i, &gGameCurrentCutscene);
            set_frame_blackout_timer();
            if (gPlayableMapId < 0) {
                if (gPlayableMapId == (s32)SPECIAL_MAP_ID_NO_LEVEL || gPlayableMapId == (s32)SPECIAL_MAP_ID_UNK_NEG10) {
                    if (gPlayableMapId == (s32)SPECIAL_MAP_ID_UNK_NEG10 && is_in_two_player_adventure()) {
                        func_8006F398();
                    }
                    buttonHeldInputs |= L_TRIG;
                    D_801234FC = 2;
                } else {
                    buttonHeldInputs = 0;
                    D_801234FC = 1;
                    sp40 = 8;
                }
            } else {
                D_801234FC = 0;
                D_801234F8 = 1;
                buttonHeldInputs = 0;
            }
        }
    } else {
        sp3C = func_8006C300();
        if (get_level_property_stack_pos()) {
            if (gLevelLoadTimer == 0) {
                i = func_800214C4();
                if ((i != 0) || ((buttonPressedInputs & A_BUTTON) && (sp3C != 0))) {
                    if (sp3C != 0) {
                        func_80000B28();
                    }
                    set_frame_blackout_timer();
                    pop_level_property_stack(&gPlayableMapId, &gGameCurrentEntrance, &i, &gGameCurrentCutscene);
                    if (gPlayableMapId < 0) {
                        if (gPlayableMapId == -1 || gPlayableMapId == -10) {
                            if (gPlayableMapId == -10 && is_in_two_player_adventure()) {
                                func_8006F398();
                            }
                            buttonHeldInputs |= L_TRIG;
                            D_801234FC = 2;
                        } else {
                            buttonHeldInputs = 0;
                            D_801234FC = 1;
                            sp40 = 8;
                        }
                    } else {
                        D_801234F8 = 1;
                    }
                }
            }
        }
    }
    if (((buttonHeldInputs & L_TRIG) && (sRenderContext == DRAW_GAME)) || (D_801234FC != 0)) {
        gIsPaused = FALSE;
        gLevelLoadTimer = 0;
        gPostRaceViewPort = NULL;
        unload_level_game();
        safe_mark_write_save_file(get_save_file_index());
        if (sp40 != 0) {
            gIsLoading = FALSE;
            switch (sp40) {
                case 1:
                    // Go to track select menu from "Select Track" option in tracks menu.
                    load_menu_with_level_background(MENU_TRACK_SELECT, -1, 1);
                    break;
                case 2:
                    load_menu_with_level_background(MENU_RESULTS, 0x22, 0);
                    break;
                case 3:
                    load_menu_with_level_background(MENU_TROPHY_RACE_ROUND, 0x22, 0);
                    break;
                case 4:
                    load_menu_with_level_background(MENU_TROPHY_RACE_RANKINGS, 0x22, 0);
                    break;
                case 5:
                    // Trophy race related?
                    load_menu_with_level_background(MENU_UNUSED_22, 0x22, 0);
                    break;
                case 6:
                    // Go to character select menu from "Select Character" option in tracks menu.
                    i = 0;
                    if (is_drumstick_unlocked()) {
                        i ^= 1;
                    }
                    if (is_tt_unlocked()) {
                        i ^= 3;
                    }
                    func_8008AEB4(1, 0);
                    load_menu_with_level_background(MENU_CHARACTER_SELECT, 0x16, i);
                    break;
                case 7:
                    gIsLoading = TRUE;
                    load_menu_with_level_background(MENU_UNKNOWN_23, -1, 0);
                    gIsLoading = FALSE;
                    break;
                case 8:
                    load_menu_with_level_background(MENU_CREDITS, -1, 0);
                    break;
            }
        } else if (D_801234FC == 1) {
            if (D_80121250[2] == -1) {
                load_menu_with_level_background(MENU_UNUSED_8, -1, 0);
            } else {
                gIsLoading = TRUE;
                load_menu_with_level_background(MENU_TRACK_SELECT_ADVENTURE, -1, -1);
            }
        } else if (!(buttonHeldInputs & R_TRIG)) {
            if (!(buttonHeldInputs & Z_TRIG)) {
                gPlayableMapId = D_80121250[0];
                gGameCurrentEntrance = D_80121250[15];
                gGameCurrentCutscene = D_80121250[D_80121250[1] + 8];
                gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
                if (gGameCurrentCutscene < 0) {
                    gGameCurrentCutscene = 0x64;
                }
            }
            load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
        } else {
            safe_mark_write_save_file(get_save_file_index());
            load_menu_with_level_background(MENU_TITLE, -1, 0);
        }
        D_801234FC = 0;
    }
    if (D_801234F8 != 0) {
        gPostRaceViewPort = NULL;
        unload_level_game();
        load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
        safe_mark_write_save_file(get_save_file_index());
        D_801234F8 = 0;
    }
}

void func_8006D8A4(void) {
    D_800DD390 = 0x2C;
    gIsPaused = 0;
    n_alSeqpDelete();
    transition_begin(&D_800DD408);
}

void func_8006D8E0(s32 arg0) {
    gPostRaceViewPort = arg0 + 1;
}

void func_8006D8F0(UNUSED s32 arg0) {
    s32 temp;
    if (sRenderContext != DRAW_UNK_04) {
        gPlayableMapId = D_80121250[0];
        gGameCurrentEntrance = 0;
        gGameCurrentCutscene = 0x64;
        temp = D_80121250[1];
        if (D_80121250[15] >= 0) {
            gGameCurrentEntrance = D_80121250[15];
        }
        if (D_80121250[temp + 8] >= 0) {
            gGameCurrentCutscene = D_80121250[temp + 8];
        }
        D_801234F8 = 1;
    }
}

void func_8006D968(s8 *arg0) {
    s32 i;
    if (sRenderContext != DRAW_UNK_04) {
        D_80121250[0] = gPlayableMapId;
        for (i = 0; i < 2; i++) {
            D_80121250[i + 2] = arg0[i + 8];
            D_80121250[i + 4] = arg0[i + 10];
            D_80121250[i + 6] = arg0[i + 12];
            D_80121250[i + 8] = arg0[i + 14];
            D_80121250[i + 10] = arg0[i + 18];
            D_80121250[i + 12] = arg0[i + 20];
        }
        D_80121250[14] = arg0[22];
        D_80121250[15] = arg0[23];
        D_801234FC = 1;
    }
}

/**
 * Gets the render context from outside this file
 */
RenderContext get_render_context(void) {
    return sRenderContext;
}

/**
 * Sets up and loads a level to be used in the background of the menu that's about to be set up.
 * Used for every kind of menu that's not ingame.
*/
void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId) {
    alloc_displaylist_heap(PLAYER_ONE);
    sRenderContext = DRAW_MENU;
    gRenderMenu = TRUE;
    set_sound_channel_volume(0, 32767);
    set_sound_channel_volume(1, 32767);
    set_sound_channel_volume(2, 32767);
    func_80065EA0();

    if (!gIsLoading) {
        gIsLoading = FALSE;
        if (levelId < 0) {
            gIsLoading = TRUE;
        } else {
            load_level_menu(levelId, -1, 0, VEHICLE_PLANE, cutsceneId);
        }
    }
    if (menuId == MENU_UNUSED_2 || menuId == MENU_LOGOS || menuId == MENU_TITLE) {
        reset_title_logo_scale();
    }
    menu_init(menuId);
    gGameCurrentEntrance = 0;
}

/**
 * Set the default vehicle option from the current loaded level.
 */
void set_level_default_vehicle(Vehicle vehicleID) {
    gLevelDefaultVehicleID = vehicleID;
}

void func_8006DB20(Vehicle vehicleId) {
    D_8012351C = vehicleId;
}

/**
 * Get the default vehicle option, set by a loaded level.
 */
Vehicle get_level_default_vehicle(void) {
    return gLevelDefaultVehicleID;
}

/**
 * Calls load_level() with the same arguments, but also does some other stuff.
 * Used for menus.
 */
void load_level_menu(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId) {
    profiler_begin_timer();
    set_free_queue_state(0);
    func_80065EA0();
    func_800C3048();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, cutsceneId);
    func_8009ECF0(get_viewport_count());
    func_800AE728(4, 4, 0x6E, 0x30, 0x20, 0);
    func_8001BF20();
    osSetTime(0);
    sPrevTime = 0;
    set_free_queue_state(2);
    if (gBootTimer == 0) {
        puppyprint_log("Level (%s) (Menu) loaded in %2.3fs.", get_level_name(levelId), OS_CYCLES_TO_USEC(osGetCount() - profiler_get_timer()) / 1000000.0f);
    }
}

/**
 * Call numerous functions to clear data in RAM.
 * Then call to free particles, HUD and text.
*/
void unload_level_menu(void) {
    if (!gIsLoading) {
        gIsLoading = TRUE;
        set_free_queue_state(0);
        clear_audio_and_track();
        transition_begin(&D_800DD3F4);
        func_800AE270();
        func_800A003C();
        func_800C30CC();
        set_free_queue_state(2);
    }
    gIsLoading = FALSE;
}

/**
 * Used in menus, update objects and draw the game.
 * In the tracks menu, this only runs if there's a track actively loaded.
*/
void update_menu_scene(s32 updateRate) {
    if (get_thread30_level_id_to_load() == 0) {
        update_time_dialation(updateRate);
        func_80010994(updateRate);
        gParticlePtrList_flush();
        func_8001BF20();
#ifdef PUPPYPRINT_DEBUG
        gPuppyPrint.mainTimerPoints[0][PP_LEVELGFX] = osGetCount();
#endif
        render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
#ifdef PUPPYPRINT_DEBUG
        gPuppyPrint.mainTimerPoints[1][PP_LEVELGFX] = osGetCount();
#endif
        func_800C3440(updateRate);
        init_rdp_and_framebuffer(&gCurrDisplayList);
        //render_borders_for_multiplayer(&gCurrDisplayList);
        //render_second_multiplayer_borders(&gCurrDisplayList);
    }
}

#ifdef NON_EQUIVALENT
// Minor & regalloc issues.
void func_8006DCF8(s32 updateRate) {
    s32 menuLoopResult, temp, temp2, tempResult;

    gIsPaused = FALSE;
    gPostRaceViewPort = NULL;
    if (!gIsLoading && gRenderMenu) {
        update_menu_scene(updateRate);
    }
    menuLoopResult = menu_loop(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
    gRenderMenu = TRUE;
    if (menuLoopResult == -2) {
        gRenderMenu = FALSE;
        return;
    }
    if ((menuLoopResult != -1) && (menuLoopResult & 0x200)) {
        unload_level_menu();
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        gDPFullSync(gCurrDisplayList++);
        gSPEndDisplayList(gCurrDisplayList++);
        gPlayableMapId = menuLoopResult & 0x7F;
        gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
        gGameCurrentEntrance = 0;
        gGameCurrentCutscene = 0x64;
        sRenderContext = DRAW_GAME;
        gIsPaused = FALSE;
        gPostRaceViewPort = NULL;
        load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
        safe_mark_write_save_file(get_save_file_index());
        return;
    }
    if ((menuLoopResult != -1) && (menuLoopResult & 0x100)) {
        unload_level_game();
        gIsPaused = FALSE;
        gPostRaceViewPort = NULL;
        switch (menuLoopResult & 0x7F) {
            case 5:
                load_menu_with_level_background(MENU_TRACK_SELECT, -1, 1);
                break;
            case 14:
                gPlayableMapId = ASSET_LEVEL_CENTRALAREAHUB;
                gGameCurrentEntrance = 0;
                gGameCurrentCutscene = 0x64;
                sRenderContext = DRAW_GAME;
                load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
                safe_mark_write_save_file(get_save_file_index());
                break;
            case 1:
                gGameCurrentEntrance = 0;
                gGameCurrentCutscene = 0x64;
                gPlayableMapId = D_80121250[0];
                sRenderContext = DRAW_GAME;
                // Minor issue with these 2 if statements
                temp2 = D_80121250[D_80121250[1] + 8];
                temp = D_80121250[15];
                if (temp >= 0) {
                    gGameCurrentEntrance = temp;
                }
                if (temp2 >= 0) {
                    gGameCurrentCutscene = temp2;
                }
                load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
                safe_mark_write_save_file(get_save_file_index());
                break;
            case 2:
                sRenderContext = DRAW_GAME;
                load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
                break;
            case 3:
                sRenderContext = DRAW_GAME;
                gPlayableMapId = D_80121250[0];
                gGameCurrentEntrance = D_80121250[15];
                gGameCurrentCutscene = D_80121250[D_80121250[1] + 8];
                gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
                load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
                break;
            default:
                load_menu_with_level_background(MENU_TITLE, -1, 0);
                break;
        }
        return;
    }
    if ((menuLoopResult & 0x80) && (menuLoopResult != -1)) {
        unload_level_menu();
        // Minor issue here.
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        gDPFullSync(gCurrDisplayList++);
        gSPEndDisplayList(gCurrDisplayList++);
        temp = menuLoopResult & 0x7F;
        D_80121250[1] = temp;
        D_80121250[0] = gPlayableMapId;
        gPlayableMapId = D_80121250[temp + 2];
        gGameCurrentEntrance = D_80121250[temp + 4];
        sRenderContext = DRAW_GAME;
        gGameCurrentCutscene = D_80121250[temp + 12];
        temp = get_player_selected_vehicle(0);
        gGameNumPlayers = gSettingsPtr->gNumRacers - 1;
        load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, temp);
        D_801234FC = 0;
        gLevelDefaultVehicleID = D_8012351C;
        return;
    }
    if (menuLoopResult > 0) {
        unload_level_menu();
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        gDPFullSync(gCurrDisplayList++);
        gSPEndDisplayList(gCurrDisplayList++);
        sRenderContext = DRAW_GAME;
        func_8006CAE4(menuLoopResult, -1, gLevelDefaultVehicleID);
        if (gSettingsPtr->newGame && !is_in_tracks_mode()) {
            func_80000B28();
            gSettingsPtr->newGame = FALSE;
        }
    }
}

#else
GLOBAL_ASM("asm/non_matchings/game/func_8006DCF8.s")
#endif

void load_level_for_menu(s32 levelId, s32 numberOfPlayers, s32 cutsceneId) {
    Vehicle vehicleID = VEHICLE_PLANE;
    if (!gIsLoading) {
        unload_level_menu();
        if (get_thread30_level_id_to_load() == 0) {
            gCurrDisplayList = gDisplayLists[gSPTaskNum];
            gDPFullSync(gCurrDisplayList++);
            gSPEndDisplayList(gCurrDisplayList++);
        }
    }
    if (levelId != (s32) SPECIAL_MAP_ID_NO_LEVEL) {
        switch (levelId) {
        case ASSET_LEVEL_TRICKYTOPS1:
            vehicleID = VEHICLE_TRICKY;
            break;
        case ASSET_LEVEL_BLUEY1:
            vehicleID = VEHICLE_BLUEY;
            break;
        case ASSET_LEVEL_BUBBLER1:
            vehicleID = VEHICLE_BUBBLER;
            break;
        case ASSET_LEVEL_SMOKEY1:
            vehicleID = VEHICLE_SMOKEY;
            break;
        case ASSET_LEVEL_WIZPIG1:
            vehicleID = VEHICLE_WIZPIG;
            break;
        case ASSET_LEVEL_CENTRALAREAHUB:
            vehicleID = VEHICLE_PLANE;
            break;
        default: 
            vehicleID = get_map_default_vehicle(levelId);
            if (vehicleID > VEHICLE_PLANE) {
                vehicleID = VEHICLE_PLANE;
            }
            break;
        }
        alloc_displaylist_heap(TWO_PLAYERS);
        load_level_menu(levelId, numberOfPlayers, 0, vehicleID, cutsceneId);
        gIsLoading = FALSE;
        return;
    }
    gIsLoading = TRUE;
}

void calc_and_alloc_heap_for_settings(void) {
    s32 dataSize;
    u32 sizes[15];
    s32 numWorlds, numLevels;

    init_level_globals();
    reset_character_id_slots();
    get_number_of_levels_and_worlds(&numLevels, &numWorlds);
    sizes[0] = sizeof(Settings);
    sizes[1] = sizes[0] + (numLevels * 4); // balloonsPtr
    sizes[2] = sizes[1] + (numWorlds * 2); // flapInitialsPtr[0]
    dataSize = (numLevels * 2);
    sizes[3] = sizes[2] + dataSize;   // flapInitialsPtr[1]
    sizes[4] = sizes[3] + dataSize;   // flapInitialsPtr[2]
    sizes[5] = sizes[4] + dataSize;   // flapTimesPtr[0]
    sizes[6] = sizes[5] + dataSize;   // flapTimesPtr[1]
    sizes[7] = sizes[6] + dataSize;   // flapTimesPtr[2]
    sizes[8] = sizes[7] + dataSize;   // courseInitialsPtr[0]
    sizes[9] = sizes[8] + dataSize;   // courseInitialsPtr[1]
    sizes[10] = sizes[9] + dataSize;  // courseInitialsPtr[2]
    sizes[11] = sizes[10] + dataSize; // courseTimesPtr[0]
    sizes[12] = sizes[11] + dataSize; // courseTimesPtr[1]
    sizes[13] = sizes[12] + dataSize; // courseTimesPtr[2]
    sizes[14] = sizes[13] + dataSize; // total size

    gSettingsPtr = allocate_from_main_pool_safe(sizes[14], COLOUR_TAG_WHITE);
    gSettingsPtr->courseFlagsPtr = (s32 *)((u8 *)gSettingsPtr + sizes[0]);
    gSettingsPtr->balloonsPtr = (s16 *)((u8 *)gSettingsPtr + sizes[1]);
    gSettingsPtr->tajFlags = 0;
    gSettingsPtr->flapInitialsPtr[0] = (u16 *)((u8 *)gSettingsPtr + sizes[2]);
    gSettingsPtr->flapInitialsPtr[1] = (u16 *)((u8 *)gSettingsPtr + sizes[3]);
    gSettingsPtr->flapInitialsPtr[2] = (u16 *)((u8 *)gSettingsPtr + sizes[4]);
    gSettingsPtr->flapTimesPtr[0] = (u16 *)((u8 *)gSettingsPtr + sizes[5]);
    gSettingsPtr->flapTimesPtr[1] = (u16 *)((u8 *)gSettingsPtr + sizes[6]);
    gSettingsPtr->flapTimesPtr[2] = (u16 *)((u8 *)gSettingsPtr + sizes[7]);
    gSettingsPtr->courseInitialsPtr[0] = (u16 *)((u8 *)gSettingsPtr + sizes[8]);
    gSettingsPtr->courseInitialsPtr[1] = (u16 *)((u8 *)gSettingsPtr + sizes[9]);
    gSettingsPtr->courseInitialsPtr[2] = (u16 *)((u8 *)gSettingsPtr + sizes[10]);
    gSettingsPtr->courseTimesPtr[0] = (u16 *)((u8 *)gSettingsPtr + sizes[11]);
    gSettingsPtr->courseTimesPtr[1] = (u16 *)((u8 *)gSettingsPtr + sizes[12]);
    gSettingsPtr->courseTimesPtr[2] = (u16 *)((u8 *)gSettingsPtr + sizes[13]);
    gSettingsPtr->unk4C = (Settings4C *) &D_80121250;
    gSaveDataFlags = // Set bits 0/1/2/8 and wipe out all others
        SAVE_DATA_FLAG_READ_FLAP_TIMES |
        SAVE_DATA_FLAG_READ_COURSE_TIMES |
        SAVE_DATA_FLAG_READ_SAVE_DATA |
        SAVE_DATA_FLAG_READ_EEPROM_SETTINGS;
}

void func_8006E5BC(void) {
    s32 i, j;
    gSettingsPtr->gNumRacers = get_number_of_active_players();
    for (i = 0; i < NUM_RACERS_1P; i++) {
        gSettingsPtr->racers[i].best_times = 0;
        gSettingsPtr->racers[i].character = get_character_id_from_slot(i);
        if (gSettingsPtr->gNumRacers >= 2) {
            gSettingsPtr->racers[i].starting_position = i;
        } else if (is_in_two_player_adventure()) {
            gSettingsPtr->racers[i].starting_position = 5 - i;
        } else {
            gSettingsPtr->racers[i].starting_position = 7 - i;
        }
        gSettingsPtr->racers[i].unk7 = 0;
        for (j = 0; j < 4; j++) {
            gSettingsPtr->racers[i].placements[j] = 0;
        }
        gSettingsPtr->racers[i].course_time = 0;
        for (j = 0; j < 3; j++) {
            gSettingsPtr->racers[i].lap_times[j] = 0;
        }
    }
    gSettingsPtr->timeTrialRacer = 0;
    gSettingsPtr->unk115[0] = 0;
    gSettingsPtr->unk115[1] = 0;
    gSettingsPtr->display_times = 0;
    gSettingsPtr->worldId = 0;
    gSettingsPtr->courseId = 0;
}

void func_8006E770(Settings *settings, s32 arg1) {
    s32 i, j;
    s32 numWorlds, numLevels;
    s32 index;
    u16 *temp_v0;

    get_number_of_levels_and_worlds(&numLevels, &numWorlds);
    temp_v0 = (u16 *)get_misc_asset(MISC_ASSET_UNK17);
    for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
        for (j = 0; j < numLevels; j++) {
            index = (j * 12) + (i * 4);
            if (arg1 & 1) {
                settings->flapInitialsPtr[i][j] = temp_v0[index + 3];
                settings->flapTimesPtr[i][j] = temp_v0[index + 2];
            }
            if (arg1 & 2) {
                settings->courseInitialsPtr[i][j] = temp_v0[index + 1];
                settings->courseTimesPtr[i][j] = temp_v0[index];
            }
        }
    }
}

void func_8006E994(Settings *settings) {
    s32 i;
    s32 sp20;
    s32 sp1C;

    get_number_of_levels_and_worlds(&sp1C, &sp20);
    settings->newGame = TRUE;

    for (i = 0; i < sp20; i++) {
        settings->balloonsPtr[i] = 0;
    }
    for (i = 0; i < sp1C; i++) {
        settings->courseFlagsPtr[i] = 0;
    }

    settings->keys = 0;
    settings->unkA = 0;
    settings->bosses = 0;
    settings->trophies = 0;
    settings->cutsceneFlags = CUTSCENE_NONE;
    settings->tajFlags = 0;
    settings->ttAmulet = 0;
    settings->wizpigAmulet = 0;
}

/**
 * Return the global game settings.
 * This is where global game records and perferences are stored.
*/
Settings *get_settings(void) {
    return gSettingsPtr;
}

/**
 * Returns the value in gIsPaused.
 */
s8 is_game_paused(void) {
    return gIsPaused;
}

/**
 * Returns the status of the post-race shrunken viewport.
*/
s8 is_postrace_viewport_active(void) {
    return gPostRaceViewPort;
}

/**
 * Sets and returns (nonzero) the message set when pressing the reset button.
 * Official name: mainResetPressed
 */
s32 is_reset_pressed(void) {
    return gNMIMesgBuf;
}

/**
 * Returns the current map ID if ingame, since this var is only set ingame.
*/
s32 get_ingame_map_id(void) {
    return gPlayableMapId;
}

void mark_to_read_flap_and_course_times(void) {
    gSaveDataFlags |= (SAVE_DATA_FLAG_READ_FLAP_TIMES | SAVE_DATA_FLAG_READ_COURSE_TIMES);
}

/**
 * Marks a flag to read the save file from the passed index from flash.
 */
void mark_read_save_file(s32 saveFileIndex) {
    //Wipe out bits 8 and 9
    gSaveDataFlags &= ~(SAVE_DATA_FLAG_READ_EEPROM_SETTINGS | SAVE_DATA_FLAG_WRITE_EEPROM_SETTINGS);
    //Place saveFileIndex at bits 8 and 9 and set bit 2
    gSaveDataFlags |= (SAVE_DATA_FLAG_READ_SAVE_DATA | ((saveFileIndex & SAVE_DATA_FLAG_INDEX_VALUE) << 8));
}

/**
 * Marks a flag to read all save file data from flash.
 */
void mark_read_all_save_files(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_READ_ALL_SAVE_DATA; //Set bit 3
}

/**
 * Marks a flag to write flap times to the eeprom
 */
void mark_to_write_flap_times(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_WRITE_FLAP_TIMES;
}

/**
 * Marks a flag to write course times to the eeprom
 */
void mark_to_write_course_times(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_WRITE_COURSE_TIMES;
}

/**
 * Marks a flag to write both flap times and course times to the eeprom
 */
void mark_to_write_flap_and_course_times(void) {
    gSaveDataFlags |= (SAVE_DATA_FLAG_WRITE_FLAP_TIMES | SAVE_DATA_FLAG_WRITE_COURSE_TIMES);
}

/**
 * Forcefully marks a flag to write a save file to flash.
 * Official Name: mainSaveGame
 */
void force_mark_write_save_file(s32 saveFileIndex) {
    gSaveDataFlags &= ~SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER_BITS; //Wipe out bits 10 and 11
    gSaveDataFlags |= (SAVE_DATA_FLAG_WRITE_SAVE_DATA | ((saveFileIndex & 3) << 10)); //Set bit 6 and place saveFileIndex into bits 10 and 11
}

/**
 * Marks a flag to write a save file to flash as long as we're not in tracks mode, and we're in the draw game render context.
 * This should prevent save data from being overwritten outside of Adventure Mode.
 * Official Name: mainSaveGame2
 */
void safe_mark_write_save_file(s32 saveFileIndex) {
    if (sRenderContext == DRAW_GAME && !is_in_tracks_mode()) {
        gSaveDataFlags &= ~SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER_BITS; //Wipe out bits 10 and 11
        gSaveDataFlags |= (SAVE_DATA_FLAG_WRITE_SAVE_DATA | ((saveFileIndex & 3) << 10));; //Set bit 6 and place saveFileIndex into bits 10 and 11
    }
}

/**
 * Marks a flag to erase a save file from flash later
 */
void mark_save_file_to_erase(s32 saveFileIndex) {
    //Set bit 7 and and place saveFileIndex into bits 10 and 11 while wiping everything else
    gSaveDataFlags = SAVE_DATA_FLAG_ERASE_SAVE_DATA | ((saveFileIndex & 3) << 10);
}

//Always called after updating a value in sEepromSettings
void mark_write_eeprom_settings(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_WRITE_EEPROM_SETTINGS; // Set bit 9
}

/**
 * Allocates an amount of memory for the number of players passed in.
 */
void alloc_displaylist_heap(s32 numberOfPlayers) {
    s32 num;
    s32 totalSize;

    if (numberOfPlayers != gPrevPlayerCount) {
        gPrevPlayerCount = numberOfPlayers;
        num = numberOfPlayers;
        set_free_queue_state(0);
        free_from_memory_pool(gDisplayLists[0]);
        free_from_memory_pool(gDisplayLists[1]);
        totalSize =
            ((gNumF3dCmdsPerPlayer[num] * sizeof(Gwords)))
            + ((gNumHudMatPerPlayer[num] * sizeof(Matrix)))
            + ((gNumHudVertsPerPlayer[num] * sizeof(Vertex)))
            + ((gNumHudTrisPerPlayer[num] * sizeof(Triangle)));
        gDisplayLists[0] = (Gfx *) allocate_at_address_in_main_pool(totalSize, (u8 *) gDisplayLists[0], COLOUR_TAG_RED);
        gDisplayLists[1] = (Gfx *) allocate_at_address_in_main_pool(totalSize, (u8 *) gDisplayLists[1], COLOUR_TAG_YELLOW);
        if ((gDisplayLists[0] == NULL) || gDisplayLists[1] == NULL) {
            if (gDisplayLists[0] != NULL) {
                free_from_memory_pool(gDisplayLists[0]);
                gDisplayLists[0] = NULL;
            }
            if (gDisplayLists[1] != NULL) {
                free_from_memory_pool(gDisplayLists[1]);
                gDisplayLists[1] = NULL;
            }
            default_alloc_displaylist_heap();
        }
        gMatrixHeap[0] = (MatrixS *)((u8 *) gDisplayLists[0] + ((gNumF3dCmdsPerPlayer[num] * sizeof(Gwords))));
        gTriangleHeap[0] = (TriangleList *)((u8 *) gMatrixHeap[0] + ((gNumHudMatPerPlayer[num] * sizeof(Matrix))));
        gVertexHeap[0] = (Vertex *)((u8 *) gTriangleHeap[0] + ((gNumHudTrisPerPlayer[num] * sizeof(Triangle))));
        gMatrixHeap[1] = (MatrixS *)((u8 *) gDisplayLists[1] + ((gNumF3dCmdsPerPlayer[num] * sizeof(Gwords))));
        gTriangleHeap[1] = (TriangleList *)((u8 *) gMatrixHeap[1] + ((gNumHudMatPerPlayer[num] * sizeof(Matrix))));
        gVertexHeap[1] = (Vertex *)((u8 *) gTriangleHeap[1] + ((gNumHudTrisPerPlayer[num] * sizeof(Triangle))));
        gCurrNumF3dCmdsPerPlayer = gNumF3dCmdsPerPlayer[num];
        gCurrNumHudMatPerPlayer = gNumHudMatPerPlayer[num];
        gCurrNumHudTrisPerPlayer = gNumHudTrisPerPlayer[num];
        gCurrNumHudVertsPerPlayer = gNumHudVertsPerPlayer[num];
        set_free_queue_state(2);
    }
    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gGameCurrMatrix = gMatrixHeap[gSPTaskNum];
    gGameCurrTriList = gTriangleHeap[gSPTaskNum];
    gGameCurrVertexList = gVertexHeap[gSPTaskNum];

    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);
}

/**
 * Returns FALSE if dmem doesn't begin with a -1. This is checked on every main game loop iteration.
 */
s32 check_dmem_validity(void) {
    if (IO_READ(SP_DMEM_START) != -1U) {
        return FALSE;
    }
    return TRUE;
}

/**
 * Defaults allocations for 4 players
 */
void default_alloc_displaylist_heap(void) {
    s32 numberOfPlayers;
    s32 totalSize;

    numberOfPlayers = FOUR_PLAYERS;
    gPrevPlayerCount = numberOfPlayers;
    totalSize = (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords))
        + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix))
        + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex))
        + (gNumHudTrisPerPlayer[numberOfPlayers] * sizeof(Triangle));

    gDisplayLists[0] = (Gfx *) allocate_from_main_pool_safe(totalSize, COLOUR_TAG_RED);
    gMatrixHeap[0] = (MatrixS *) ((u8 *) gDisplayLists[0] + (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords)));
    gVertexHeap[0] = (Vertex *) ((u8 *) gMatrixHeap[0] + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix)));
    gTriangleHeap[0] = (TriangleList *) ((u8 *) gVertexHeap[0] + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex)));

    gDisplayLists[1] = (Gfx *) allocate_from_main_pool_safe(totalSize, COLOUR_TAG_YELLOW);
    gMatrixHeap[1] = (MatrixS *) ((u8 *) gDisplayLists[1] + (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords)));
    gVertexHeap[1] = (Vertex *) ((u8 *) gMatrixHeap[1] + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix)));
    gTriangleHeap[1] = (TriangleList *) ((u8 *) gVertexHeap[1] + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex)));

    gCurrNumF3dCmdsPerPlayer = gNumF3dCmdsPerPlayer[numberOfPlayers];
    gCurrNumHudMatPerPlayer = gNumHudMatPerPlayer[numberOfPlayers];
    gCurrNumHudTrisPerPlayer = gNumHudTrisPerPlayer[numberOfPlayers];
    gCurrNumHudVertsPerPlayer = gNumHudVertsPerPlayer[numberOfPlayers];
}

void func_8006F140(s32 arg0) {
    if (gLevelLoadTimer == 0) {
        gLevelLoadTimer = 40;
        gLevelLoadType = 0;
        if (arg0 == 1) { //FADE_BARNDOOR_HORIZONTAL?
            transition_begin(&gLevelFadeOutTransition);
        }
        if (arg0 == 3) { //FADE_CIRCLE?
            gLevelLoadTimer = 282;
            transition_begin(&D_800DD424);
        }
        if (arg0 == 4) { //FADE_WAVES?
            gLevelLoadTimer = 360;
            transition_begin(&D_800DD424);
        }
        if (arg0 == 0) { //FADE_FULLSCREEN?
            gLevelLoadTimer = 2;
        }
    }
}

/**
 * Begins a fade transition, then signals to the level loading that it wants to be a trophy race.
*/
void begin_trophy_race_teleport(void) {
    if (gLevelLoadTimer == 0) {
        transition_begin(&gLevelFadeOutTransition);
        gLevelLoadTimer = 40;
        gLevelLoadType = LEVEL_LOAD_TROPHY_RACE;
    }
}

/**
 * Check if all available trophy races and Wizpig 1 has been beaten, and if the cutscene has not yet played.
*/
void begin_lighthouse_rocket_cutscene(void) {
    if (gLevelLoadTimer == 0) {
        if ((gSettingsPtr->trophies & 0xFF) == 0xFF && !(gSettingsPtr->cutsceneFlags & CUTSCENE_LIGHTHOUSE_ROCKET) && gSettingsPtr->bosses & 1) {
            gSettingsPtr->cutsceneFlags |= CUTSCENE_LIGHTHOUSE_ROCKET;
            transition_begin(&gLevelFadeOutTransition);
            gLevelLoadTimer = 40;
            gNextMap = ASSET_LEVEL_ROCKETSEQUENCE;
            gLevelLoadType = LEVEL_LOAD_LIGHTHOUSE_CUTSCENE;
        }
    }
}

/**
 * Begin a transition, then set the next level to the passed argument.
 * This is used only to warp to Future Fun Land from the hub area.
*/
void begin_level_teleport(s32 levelID) {
    if (gLevelLoadTimer == 0) {
        gNextMap = levelID;
        transition_begin(&gLevelFadeOutTransition);
        gLevelLoadTimer = 40;
        gLevelLoadType = LEVEL_LOAD_FUTURE_FUN_LAND;
    }
}

void func_8006F388(u8 time) {
    D_800DD398 = time;
}

void func_8006F398(void) {
    s32 i;
    u8 temp;
    u8 *first_racer_data;
    u8 *second_racer_data;

    swap_player_1_and_2_ids();
    func_8000E194();

    first_racer_data = (u8 *)(gSettingsPtr->racers);
    second_racer_data = (u8 *)(gSettingsPtr->racers + 1);

    for (i = 0; i < (s32)sizeof(Racer); i++) {
        temp = first_racer_data[i];
        first_racer_data[i] = second_racer_data[i];
        second_racer_data[i] = temp;
    }
}

/**
 * Sets the timer to delay drawing new frames.
 * When set to 2, the game will copy the previous framebuffer over to the next.
*/
void set_frame_blackout_timer(void) {
    gDrawFrameTimer = 2;
}

#if SKIP_INTRO == SKIP_TITLE
 #define BOOT_LVL MENU_TITLE
#elif SKIP_INTRO == SKIP_CHARACTER
 #define BOOT_LVL MENU_CHARACTER_SELECT
#elif SKIP_INTRO == SKIP_MENU
 #define BOOT_LVL MENU_GAME_SELECT
#else
 #define BOOT_LVL MENU_BOOT
#endif // SKIP_INTRO

/**
 * Give the player 8 frames to enter the CPak menu with start, then load the intro sequence.
 */
void pre_intro_loop(void) {
    s32 i;
    s32 buttonInputs = 0;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        buttonInputs |= get_buttons_held_from_player(i);
    }
    if (buttonInputs & START_BUTTON) {
        gShowControllerPakMenu = TRUE;
    }
#ifndef SKIP_INTRO
    sBootDelayTimer++;
#else
    sBootDelayTimer = 8;
#endif
    if (sBootDelayTimer >= 8) {
        load_menu_with_level_background(BOOT_LVL, 0x27, 2);
    }
}

/**
 * Returns TRUE if the game doesn't detect any controllers.
 * Official name: mainDemoOnly
 */
s32 is_controller_missing(void) {
    if (sControllerStatus == CONTROLLER_MISSING) {
        return TRUE;
    } else {
        return FALSE;
    }
}

#ifndef NO_ANTIPIRACY
/**
 * Ran on boot, will make sure the CIC chip (CIC6103) is to spec. Will return true if it's all good, otherwise it returns false.
 * The intention of this function, is an attempt to check that the cartridge is a legitimate copy.
 * A false read, meaning you're caught running an illegitimate copy, will force the game to pause when you enter the world.
 */
s32 check_imem_validity(void) {
    if (IO_READ(SP_IMEM_START) != CIC_ID) {
        return FALSE;
    }
    return TRUE;
}
#endif