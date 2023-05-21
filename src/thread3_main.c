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

/************ .rodata ************/

UNUSED const char sLevelErrorString[] = "LOADLEVEL Error: Level out of range\n";
UNUSED const char sBossErrorString[] = "BossLev problem\n";
UNUSED const char sAITableErrorString[] = "AITABLE Error: Table out of range\n";
UNUSED const char sDebugVersionInfoString[] = "1.1605";
UNUSED const char sDebugBuildDateString[] = "02/10/97 16:03";
UNUSED const char sDebugUsernameString[] = "pmountain";

const char D_800E7134[] = "BBB\n"; // Functionally unused.
UNUSED const char sDebugCarString[] = "CAR";
UNUSED const char sDebugHovercraftString[] = "HOV";
UNUSED const char sDebugPlaneString[] = "PLN";
UNUSED const char sDebugVehicleSwapString[] = "Swapping\n";

/*********************************/

/************ .data ************/

UNUSED char *sDebugRomBuildInfo[3] = {
    (char *)sDebugVersionInfoString,
    (char *)sDebugBuildDateString,
    (char *)sDebugUsernameString
};

UNUSED char gBuildString[40] = "Version 7.7 29/09/97 15.00 L.Schuneman";

s8 sAntiPiracyTriggered = 0;
UNUSED s32 D_800DD378 = 1;
s32 gSaveDataFlags = 0; //Official Name: load_save_flags
s32 gScreenStatus = OSMESG_SWAP_BUFFER;
s32 sControllerStatus = 0;
UNUSED s32 D_800DD388 = 0;
s8 gSkipGfxTask = FALSE;
s8 D_800DD390 = 0;
s16 gLevelLoadTimer = 0;
s8 D_800DD398 = 0;
s8 gFutureFunLandLevelTarget = FALSE;
s8 gDmemInvalid = FALSE;
UNUSED s32 D_800DD3A4 = 0;
UNUSED s32 D_800DD3A8 = 0;
UNUSED s32 D_800DD3AC = 0;
s32 gNumF3dCmdsPerPlayer[4] = { 4500, 7000, 11000, 11000 };
s32 gNumHudVertsPerPlayer[4] = { 300, 600, 850, 900 };
s32 gNumHudMatPerPlayer[4] = { 300, 400, 550, 600 };
s32 gNumHudTrisPerPlayer[4] = { 20, 30, 40, 50 };
s8 gDrawFrameTimer = 0;
FadeTransition D_800DD3F4 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_UNK2, FADE_COLOR_BLACK, 20, 0);
UNUSED FadeTransition D_800DD3FC = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 20, -1);
s32 sLogicUpdateRate = LOGIC_5FPS;
FadeTransition D_800DD408 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 30, -1);
UNUSED char *D_800DD410[3] = {
    (char *)sDebugCarString, (char *)sDebugHovercraftString, (char *)sDebugPlaneString
};
FadeTransition gLevelFadeOutTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 30, -1);
FadeTransition D_800DD424 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 260, -1);

/*******************************/

/************ .bss ************/

Gfx *gDisplayLists[2];
Gfx *gCurrDisplayList;
UNUSED s32 D_801211FC;
MatrixS *gMatrixHeap[2];
MatrixS *gGameCurrMatrix;
Vertex *gVertexHeap[2];
Vertex *gGameCurrVertexList;
TriangleList *gTriangleHeap[2];
TriangleList *gGameCurrTriList;
UNUSED s32 D_80121230[8];
s8 D_80121250[16]; //Settings4C
OSSched gMainSched; // 0x288 / 648 bytes
u64 gSchedStack[0x400];
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
UNUSED s8 D_80123526; // Set to 0 then never used.
s32 gCurrNumF3dCmdsPerPlayer;
s32 gCurrNumHudMatPerPlayer;
s32 gCurrNumHudTrisPerPlayer;
s32 gCurrNumHudVertsPerPlayer;
OSScClient *gNMISched[3];
OSMesg gNMIOSMesg;
OSMesgQueue gNMIMesgQueue;
s32 gNMIMesgBuf; //Official Name: resetPressed
s32 D_80123568[6]; // BSS Padding

/******************************/


/**
 * Main looping function for the main thread.
 * Official Name: mainThread
 */
void thread3_main(UNUSED void *unused) {
    init_game();
    gSaveDataFlags = handle_save_data_and_read_controller(gSaveDataFlags, 0);
    sBootDelayTimer = 0;
    sRenderContext = DRAW_INTRO;
    while (1) {
        if (is_reset_pressed()) {
            func_80072708();
            audioStopThread();
            stop_thread30();
            __osSpSetStatus(SP_SET_HALT | SP_CLR_INTR_BREAK | SP_CLR_YIELD | SP_CLR_YIELDED | SP_CLR_TASKDONE | SP_CLR_RSPSIGNAL
                            | SP_CLR_CPUSIGNAL | SP_CLR_SIG5 | SP_CLR_SIG6 | SP_CLR_SIG7);
            osDpSetStatus(DPC_SET_XBUS_DMEM_DMA | DPC_CLR_FREEZE | DPC_CLR_FLUSH | DPC_CLR_TMEM_CTR | DPC_CLR_PIPE_CTR
                            | DPC_CLR_CMD_CTR | DPC_CLR_CMD_CTR);
            while (1); // Infinite loop
        }
        main_game_loop();
        thread3_verify_stack();
    }
}

/**
 * Setup all of the necessary pieces required for the game to function.
 * This includes the memory pool. controllers, video, audio, core assets and more.
 * Official Name: mainInitGame
 */
void init_game(void) {
    s32 viMode;

    init_main_memory_pool();
    rzipInit(); // Initialise gzip decompression related things
    sAntiPiracyTriggered = TRUE;
    if (check_imem_validity()) {
        sAntiPiracyTriggered = FALSE;
    }
    gIsLoading = FALSE;
    gLevelDefaultVehicleID = VEHICLE_CAR;

    if (osTvType == TV_TYPE_PAL) {
        viMode = OS_VI_PAL_LPN1;
    } else if (osTvType == TV_TYPE_NTSC) {
        viMode = OS_VI_NTSC_LPN1;
    } else if (osTvType == TV_TYPE_MPAL) {
        viMode = OS_VI_MPAL_LPN1;
    }

    osCreateScheduler(&gMainSched, &gSchedStack[0x400], /*priority*/ 13, viMode, 1);
    // Antipiracy measure.
    gDmemInvalid = FALSE;
    if (check_dmem_validity() == FALSE) {
        gDmemInvalid = TRUE;
    }
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
    osCreateMesgQueue(&gNMIMesgQueue, &gNMIOSMesg, 1);
    osScAddClient(&gMainSched, (OSScClient*) gNMISched, &gNMIMesgQueue, OS_SC_ID_PRENMI);
    gNMIMesgBuf = 0;
    gGameCurrentEntrance = 0;
    gGameCurrentCutscene = 0;
    gSPTaskNum = 0;

    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);

    osSetTime(0);
}

/**
 * The main gameplay loop.
 * Contains all game logic, audio and graphics processing.
 */
void main_game_loop(void) {
    s32 debugLoopCounter;
    s32 framebufferSize;
    s32 tempLogicUpdateRate, tempLogicUpdateRateMax;

    osSetTime(0);

    if (gScreenStatus == MESG_SKIP_BUFFER_SWAP) {
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        set_rsp_segment(&gCurrDisplayList, 0, 0);
        set_rsp_segment(&gCurrDisplayList, 1, (s32) gVideoCurrFramebuffer);
        set_rsp_segment(&gCurrDisplayList, 2, (s32) gVideoLastDepthBuffer);
        set_rsp_segment(&gCurrDisplayList, 4, (s32) gVideoCurrFramebuffer - 0x500);
    }
    if (gDrawFrameTimer == 0) {
        setup_ostask_xbus(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
        gSPTaskNum += 1;
        gSPTaskNum &= 1;
    }
    if (gDrawFrameTimer) {
        gDrawFrameTimer--;
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
    if (get_lockup_status()) {
        render_epc_lock_up_display();
        sRenderContext = DRAW_CRASH_SCREEN;
    }
    if (gDmemInvalid) {
        debugLoopCounter = 0;
        while (debugLoopCounter != 10000000) {
            debugLoopCounter++;
        }
        if (debugLoopCounter > 20000000) { // This shouldn't ever be true?
            render_printf(D_800E7134 /* "BBB\n" */);
        }
    }

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
        case DRAW_CRASH_SCREEN: // EPC (lockup display)
            lockup_screen_loop(sLogicUpdateRate);
            break;
    }

    // This is a good spot to place custom text if you want it to overlay it over ALL the
    // menus & gameplay.

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

    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);

    copy_viewports_to_stack();
    if (gDrawFrameTimer != 1) {
        if (gSkipGfxTask == FALSE) {
            gScreenStatus = wait_for_gfx_task();
        }
    } else {
        gDrawFrameTimer = 0;
    }
    gSkipGfxTask = FALSE;
    clear_free_queue();
    if (!gIsPaused) {
        disable_cutscene_camera();
    }
    if (gDrawFrameTimer == 2) {
        framebufferSize = SCREEN_WIDTH * SCREEN_HEIGHT * 2;
        if (osTvType == TV_TYPE_PAL) {
            framebufferSize = (s32)((SCREEN_WIDTH * SCREEN_HEIGHT * 2) * 1.1f);
        }
        dmacopy_doubleword(gVideoLastFramebuffer, gVideoCurrFramebuffer, (s32) gVideoCurrFramebuffer + framebufferSize);
    }
    // tempLogicUpdateRate will be set to a value 2 or higher, based on the framerate.
    // the mul factor is hardcapped at 6, which happens at 10FPS. The mul factor
    // affects frameskipping, to maintain consistent game speed, through the (many)
    // dropped frames in DKR.
    tempLogicUpdateRate = swap_framebuffer_when_ready(gScreenStatus);
    sLogicUpdateRate = tempLogicUpdateRate;
    tempLogicUpdateRateMax = LOGIC_10FPS;
    if (tempLogicUpdateRate > tempLogicUpdateRateMax) {
        sLogicUpdateRate = tempLogicUpdateRateMax;
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
    alloc_displaylist_heap(numberOfPlayers);
    set_free_queue_state(0);
    func_80065EA0();
    func_800C3048();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, gGameCurrentCutscene);
    func_8009ECF0(get_viewport_count());
    func_800AE728(8, 0x10, 0x96, 0x64, 0x32, 0);
    func_8001BF20();
    osSetTime(0);
    set_free_queue_state(2);
    func_80072298(1);
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
    // Spam the start button, making the game unplayable because it's constantly paused.
    if (sAntiPiracyTriggered) {
        buttonPressedInputs |= START_BUTTON;
    }
    // Update all objects
    if (!gIsPaused) {
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
    render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
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
    render_second_multiplayer_borders(&gCurrDisplayList);
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
 *  Unused function used to set the render context from outside this file
 *  Official Name: mainSetMode?
 */
UNUSED void set_render_context(s32 changeTo) {
    sRenderContext = changeTo;
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
    set_free_queue_state(0);
    func_80065EA0();
    func_800C3048();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, cutsceneId);
    func_8009ECF0(get_viewport_count());
    func_800AE728(4, 4, 0x6E, 0x30, 0x20, 0);
    func_8001BF20();
    osSetTime(0);
    set_free_queue_state(2);
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
        func_80010994(updateRate);
        gParticlePtrList_flush();
        func_8001BF20();
        render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
        func_800C3440(updateRate);
        init_rdp_and_framebuffer(&gCurrDisplayList);
        render_borders_for_multiplayer(&gCurrDisplayList);
        render_second_multiplayer_borders(&gCurrDisplayList);
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
    if (!gIsLoading) {
        unload_level_menu();
        if (get_thread30_level_id_to_load() == 0) {
            gCurrDisplayList = gDisplayLists[gSPTaskNum];
            gDPFullSync(gCurrDisplayList++);
            gSPEndDisplayList(gCurrDisplayList++);
        }
    }
    if (levelId != (s32) SPECIAL_MAP_ID_NO_LEVEL) {
        //!@bug: Forcing the plane here makes all AI use plane paths. This can be seen most evidently in the Ancient Lake demo.
        load_level_menu(levelId, numberOfPlayers, 0, VEHICLE_PLANE, cutsceneId);
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
    for (i = 0; i < 8; i++) {
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

UNUSED void func_8006EA58(void) {
    func_8006E770(gSettingsPtr, 3);
    func_8006E994(gSettingsPtr);
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
    if (gNMIMesgBuf == 0) {
        gNMIMesgBuf = (s32)((osRecvMesg(&gNMIMesgQueue, NULL, OS_MESG_NOBLOCK) + 1) != 0);
    }
    return gNMIMesgBuf;
}

/**
 * Returns the current map ID if ingame, since this var is only set ingame.
*/
s32 get_ingame_map_id(void) {
    return gPlayableMapId;
}

/**
 * Marks a flag to read flap times from the eeprom
 */
UNUSED void mark_to_read_flap_times(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_READ_FLAP_TIMES;
}

/**
 * Marks a flag to read course times from the eeprom
 */
UNUSED void mark_to_read_course_times(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_READ_COURSE_TIMES;
}

/**
 * Marks a flag to read both flap times and course times from the eeprom
 */
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

/**
 * Marks a flag to read eeprom settings from flash later
 * @bug: Because this is the same bit used for reading save files,
 *       it will change the save file number to read from
 */
UNUSED void mark_read_eeprom_settings(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_READ_EEPROM_SETTINGS; // Set bit 8
}

/**
 * Marks a flag to write eeprom settings to flash later
 * @bug: Because this is the same bit used for reading save files,
 *       it will change the save file number to read from
 */
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
        gLevelLoadType = LEVEL_LOAD_NORMAL;
        D_80123526 = 0;
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

UNUSED void func_8006F20C(void) {
    if (gLevelLoadTimer == 0) {
        transition_begin(&gLevelFadeOutTransition);
        gLevelLoadTimer = 40;
        gLevelLoadType = LEVEL_LOAD_UNK1;
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
    sBootDelayTimer++;
    if (sBootDelayTimer >= 8) {
        load_menu_with_level_background(MENU_BOOT, 0x27, 2);
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
