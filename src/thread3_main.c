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
#include "rcp.h"
#include "audiosfx.h"
#include "audiomgr.h"
#include "lights.h"
#include "textures_sprites.h"
#include "PR/os_internal.h"
#include "printf.h"
#include "fade_transition.h"
#include "borders.h"
#include "audio_spatial.h"
#include "tracks.h"
#include "game_text.h"
#include "game_ui.h"
#include "main.h"
#include "object_models.h"
#include "racer.h"
#include "particles.h"
#include "math_util.h"
#include "controller.h"

/************ .rodata ************/

UNUSED char *sDebugRomBuildInfo[] = { "1.1605", "02/10/97 16:03", "pmountain" };

const char D_800E7134[] = "BBB\n"; // Functionally unused.

/*********************************/

/************ .data ************/

UNUSED char gBuildString[40] = "Version 7.7 29/09/97 15.00 L.Schuneman";

s8 sAntiPiracyTriggered = 0;
UNUSED s32 D_800DD378 = 1;
s32 gSaveDataFlags = 0; // Official Name: load_save_flags
s32 gScreenStatus = OSMESG_SWAP_BUFFER;
s32 sControllerStatus = 0;
UNUSED s32 D_800DD388 = 0;
s8 gSkipGfxTask = FALSE;
s8 gDrumstickSceneLoadTimer = 0;
s16 gLevelLoadTimer = 0;
s8 gPauseLockTimer = 0; // If this is above zero, the player cannot pause the game.
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
FadeTransition D_800DD3F4 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_OUT, FADE_COLOR_BLACK, 20, 0);
UNUSED FadeTransition D_800DD3FC = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 20, -1);
s32 sLogicUpdateRate = LOGIC_5FPS;
FadeTransition gDrumstickSceneTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 30, -1);
UNUSED char *D_800DD410[3] = { "CAR", "HOV", "PLN" };
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
s8 gLevelSettings[16];
OSSched gMainSched; // 0x288 / 648 bytes
u64 gSchedStack[0x400];
s32 gSPTaskNum;
s32 gGameMode;
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
Vehicle gMenuVehicleID; // Looks to be the current level's vehicle ID.
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
s32 gNMIMesgBuf;          // Official Name: resetPressed
UNUSED s32 D_80123568[3]; // BSS Padding

/******************************/

/**
 * Main looping function for the main thread.
 * Official Name: mainThread
 */
void thread3_main(UNUSED void *unused) {
    init_game();
    gSaveDataFlags = handle_save_data_and_read_controller(gSaveDataFlags, 0);
    sBootDelayTimer = 0;
    gGameMode = GAMEMODE_INTRO;
    while (1) {
        if (is_reset_pressed()) {
            rumble_kill();
            audioStopThread();
            stop_thread30();
            __osSpSetStatus(SP_SET_HALT | SP_CLR_INTR_BREAK | SP_CLR_YIELD | SP_CLR_YIELDED | SP_CLR_TASKDONE |
                            SP_CLR_RSPSIGNAL | SP_CLR_CPUSIGNAL | SP_CLR_SIG5 | SP_CLR_SIG6 | SP_CLR_SIG7);
            osDpSetStatus(DPC_SET_XBUS_DMEM_DMA | DPC_CLR_FREEZE | DPC_CLR_FLUSH | DPC_CLR_TMEM_CTR | DPC_CLR_PIPE_CTR |
                          DPC_CLR_CMD_CTR | DPC_CLR_CMD_CTR);
            while (1) {
                ; // Infinite loop
            }
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

    stubbed_printf(sDebugRomBuildInfo);
    init_main_memory_pool();
    init_rzip(); // Initialise gzip decompression related things
#ifdef ANTI_TAMPER
    sAntiPiracyTriggered = TRUE;
    if (check_imem_validity()) {
        sAntiPiracyTriggered = FALSE;
    }
#endif
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
#ifdef ANTI_TAMPER
    // Antipiracy measure.
    gDmemInvalid = FALSE;
    if (check_dmem_validity() == FALSE) {
        gDmemInvalid = TRUE;
    }
#endif
    init_video(VIDEO_MODE_LOWRES_LPN, &gMainSched);
    init_PI_mesg_queue();
    setup_gfx_mesg_queues(&gMainSched);
    audio_init(&gMainSched);
    func_80008040(); // Should be very similar to allocate_object_model_pools
    sControllerStatus = init_controllers();
    tex_init_textures();
    allocate_object_model_pools();
    allocate_object_pools();
    debug_text_init();
    allocate_ghost_data();
    init_particle_assets();
    weather_init();
    calc_and_alloc_heap_for_settings();
    default_alloc_displaylist_heap();
    load_fonts();
    init_controller_paks();
    init_save_data();
    create_and_start_thread30();
    osCreateMesgQueue(&gNMIMesgQueue, &gNMIOSMesg, 1);
    osScAddClient(&gMainSched, (OSScClient *) gNMISched, &gNMIMesgQueue, OS_SC_ID_PRENMI);
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
        gGameMode = GAMEMODE_LOCKUP;
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

    switch (gGameMode) {
        case GAMEMODE_INTRO: // Pre-boot screen
            pre_intro_loop();
            break;
        case GAMEMODE_MENU: // In a menu
            menu_logic_loop(sLogicUpdateRate);
            break;
        case GAMEMODE_INGAME: // In game (Controlling a character)
            ingame_logic_loop(sLogicUpdateRate);
            break;
        case GAMEMODE_LOCKUP: // EPC (lockup display)
            lockup_screen_loop(sLogicUpdateRate);
            break;
    }

    // This is a good spot to place custom text if you want it to overlay it over ALL the
    // menus & gameplay.

    sound_update_queue(sLogicUpdateRate);
    debug_text_print(&gCurrDisplayList);
    render_dialogue_boxes(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList);
    dialogue_close(4);
    dialogue_clear(4);
    // handle_transitions will perform the logic of transitions and return the transition ID.
    if (handle_transitions(sLogicUpdateRate)) {
        render_fade_transition(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList);
    }
    if (sBootDelayTimer >= 8 && is_controller_missing()) {
        menu_missing_controller(&gCurrDisplayList, sLogicUpdateRate);
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
            framebufferSize = (s32) ((SCREEN_WIDTH * SCREEN_HEIGHT * 2) * 1.1f);
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

/**
 * Loads a level for gameplay based on what the next track ID is, with the option to override.
 */
void load_next_ingame_level(s32 numPlayers, s32 trackID, Vehicle vehicle) {
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
    camera_init();
    load_game_text_table();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, gGameCurrentCutscene);
    init_hud(get_viewport_count());
    func_800AE728(8, 0x10, 0x96, 0x64, 0x32, 0);
    ainode_update();
    osSetTime(0);
    set_free_queue_state(2);
    rumble_init(TRUE);
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
    free_hud();
    free_game_text_table();
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
    s32 buttonPressedInputs, buttonHeldInputs, i, loadContext, sp3C;

    loadContext = LEVEL_CONTEXT_NONE;
    buttonHeldInputs = 0;
    buttonPressedInputs = 0;

    // Get input data for all 4 players.
    for (i = 0; i < get_active_player_count(); i++) {
        buttonHeldInputs |= get_buttons_held_from_player(i);
        buttonPressedInputs |= get_buttons_pressed_from_player(i);
    }
#ifdef ANTI_TAMPER
    // Spam the start button, making the game unplayable because it's constantly paused.
    if (sAntiPiracyTriggered) {
        buttonPressedInputs |= START_BUTTON;
    }
#endif
    // Update all objects
    if (!gIsPaused) {
        func_80010994(updateRate);
        if (check_if_showing_cutscene_camera() == 0 || get_race_countdown()) {
            if (buttonPressedInputs & START_BUTTON && get_level_property_stack_pos() == 0 &&
                gDrumstickSceneLoadTimer == 0 && gGameMode == GAMEMODE_INGAME && gPostRaceViewPort == FALSE &&
                gLevelLoadTimer == 0 && gPauseLockTimer == 0) {
                buttonPressedInputs = 0;
                gIsPaused = TRUE;
                menu_pause_init();
            }
        }
    } else {
        set_anti_aliasing(TRUE);
    }
    gPauseLockTimer -= updateRate;
    if (gPauseLockTimer < 0) {
        gPauseLockTimer = 0;
    }
    if (gPostRaceViewPort) {
        gIsPaused = FALSE;
    }
    gParticlePtrList_flush();
    ainode_update();
    render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
    if (gGameMode == GAMEMODE_INGAME) {
        // Ignore the user's L/R/Z buttons.
        buttonHeldInputs &= ~(L_TRIG | R_TRIG | Z_TRIG);
    }
    if (gPostRaceViewPort) {
        i = menu_postrace(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, updateRate);
        switch (i) {
            case POSTRACE_OPT_2:
                buttonHeldInputs |= (L_TRIG | Z_TRIG);
                break;
            case POSTRACE_OPT_1:
                gPostRaceViewPort = FALSE;
                func_8006D8F0(-1);
                break;
            case POSTRACE_OPT_4:
                clear_level_property_stack();
                gDrumstickSceneLoadTimer = 0;
                buttonHeldInputs |= (L_TRIG | R_TRIG);
                break;
            case POSTRACE_OPT_5:
                buttonHeldInputs |= L_TRIG, loadContext = LEVEL_CONTEXT_TRACK_SELECT;
                break;
            case POSTRACE_OPT_8:
                buttonHeldInputs |= L_TRIG, loadContext = LEVEL_CONTEXT_RESULTS;
                break;
            case POSTRACE_OPT_9:
                buttonHeldInputs |= L_TRIG, loadContext = LEVEL_CONTEXT_TROPHY_ROUND;
                break;
            case POSTRACE_OPT_10:
                buttonHeldInputs |= L_TRIG, loadContext = LEVEL_CONTEXT_TROPHY_RESULTS;
                break;
            case POSTRACE_OPT_11:
                buttonHeldInputs |= L_TRIG, loadContext = LEVEL_CONTEXT_UNUSED;
                break;
            case POSTRACE_OPT_12:
                buttonHeldInputs |= L_TRIG, loadContext = LEVEL_CONTEXT_CHARACTER_SELECT;
                break;
            case POSTRACE_OPT_13:
                buttonHeldInputs |= L_TRIG, loadContext = LEVEL_CONTEXT_UNK7;
                break;
        }
    }
    process_onscreen_textbox(updateRate);
    i = textbox_visible();
    if (i != 0) {
        if (i == 2) {
            gIsPaused = TRUE;
        }
        if (textbox_visible() != 2) {
            gIsPaused = FALSE;
            menu_close_dialogue();
        }
    }
    if (gIsPaused) {
        i = menu_pause_loop(&gCurrDisplayList, updateRate);
        switch (i) {
            case PAUSE_CONTINUE:
                gIsPaused = FALSE;
                break;
            case PAUSE_RESET:
                sound_clear_delayed();
                reset_delayed_text();
                if (func_80023568() != 0 && is_in_two_player_adventure()) {
                    swap_lead_player();
                }
                buttonHeldInputs |= (L_TRIG | Z_TRIG);
                break;
            case PAUSE_QUIT_LOBBY:
                sound_clear_delayed();
                reset_delayed_text();
                if (func_80023568() != 0 && is_in_two_player_adventure()) {
                    swap_lead_player();
                }
                buttonHeldInputs |= L_TRIG;
                break;
            case PAUSE_QUIT_TRACKS:
                loadContext = LEVEL_CONTEXT_TRACK_SELECT;
                reset_delayed_text();
                buttonHeldInputs |= L_TRIG;
                break;
            case PAUSE_QUIT_CHARSELECT:
                loadContext = LEVEL_CONTEXT_CHARACTER_SELECT;
                reset_delayed_text();
                buttonHeldInputs |= L_TRIG;
                break;
            case PAUSE_OPT_6:
                gIsPaused = FALSE;
                break;
            case PAUSE_QUIT_CHALLENGE:
                mode_end_taj_race(CHALLENGE_END_QUIT);
                gIsPaused = FALSE;
                break;
            case PAUSE_OPT_4:
                gDrumstickSceneLoadTimer = 0;
                sound_clear_delayed();
                reset_delayed_text();
                clear_level_property_stack();
                buttonHeldInputs |= (L_TRIG | R_TRIG);
                break;
        }
    }
    init_rdp_and_framebuffer(&gCurrDisplayList);
    divider_draw(&gCurrDisplayList);
    render_minimap_and_misc_hud(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, updateRate);
    divider_clear_coverage(&gCurrDisplayList);
    if (gFutureFunLandLevelTarget) {
        if (func_800214C4() != 0) {
            gPlayableMapId = ASSET_LEVEL_FUTUREFUNLANDHUB;
            D_801234F8 = TRUE;
            gGameCurrentEntrance = 0;
            gFutureFunLandLevelTarget = FALSE;
        }
    }
    sp3C = FALSE;
    if (gDrumstickSceneLoadTimer) {
        gDrumstickSceneLoadTimer -= updateRate;
        if (gDrumstickSceneLoadTimer <= 0) {
            gDrumstickSceneLoadTimer = 0;
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
                    loadContext = LEVEL_CONTEXT_TROPHY_ROUND;
                    trophyround_adventure();
                    D_801234FC = 2;
                    break;
                case LEVEL_LOAD_LIGHTHOUSE_CUTSCENE:
                    gFutureFunLandLevelTarget = TRUE;
                    // fall-through
                case LEVEL_LOAD_FUTURE_FUN_LAND:
                    D_801234F8 = TRUE;
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
                if (gPlayableMapId == SPECIAL_MAP_ID_NO_LEVEL || gPlayableMapId == SPECIAL_MAP_ID_UNK_NEG10) {
                    if (gPlayableMapId == SPECIAL_MAP_ID_UNK_NEG10 && is_in_two_player_adventure()) {
                        swap_lead_player();
                    }
                    buttonHeldInputs |= L_TRIG;
                    D_801234FC = 2;
                } else {
                    buttonHeldInputs = 0;
                    D_801234FC = 1;
                    loadContext = LEVEL_CONTEXT_CREDITS;
                }
            } else {
                D_801234FC = 0;
                D_801234F8 = TRUE;
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
                        music_change_on();
                    }
                    set_frame_blackout_timer();
                    pop_level_property_stack(&gPlayableMapId, &gGameCurrentEntrance, &i, &gGameCurrentCutscene);
                    if (gPlayableMapId < 0) {
                        if (gPlayableMapId == -1 || gPlayableMapId == -10) {
                            if (gPlayableMapId == -10 && is_in_two_player_adventure()) {
                                swap_lead_player();
                            }
                            buttonHeldInputs |= L_TRIG;
                            D_801234FC = 2;
                        } else {
                            buttonHeldInputs = 0;
                            D_801234FC = 1;
                            loadContext = LEVEL_CONTEXT_CREDITS;
                        }
                    } else {
                        D_801234F8 = TRUE;
                    }
                }
            }
        }
    }
    if ((buttonHeldInputs & L_TRIG && gGameMode == GAMEMODE_INGAME) || D_801234FC != 0) {
        gIsPaused = FALSE;
        gLevelLoadTimer = 0;
        gPostRaceViewPort = FALSE;
        unload_level_game();
        safe_mark_write_save_file(get_save_file_index());
        if (loadContext) {
            gIsLoading = FALSE;
            switch (loadContext) {
                case LEVEL_CONTEXT_TRACK_SELECT:
                    // Go to track select menu from "Select Track" option in tracks menu.
                    load_menu_with_level_background(MENU_TRACK_SELECT, SPECIAL_MAP_ID_NO_LEVEL, 1);
                    break;
                case LEVEL_CONTEXT_RESULTS:
                    load_menu_with_level_background(MENU_RESULTS, ASSET_LEVEL_TROPHYRACE, 0);
                    break;
                case LEVEL_CONTEXT_TROPHY_ROUND:
                    load_menu_with_level_background(MENU_TROPHY_RACE_ROUND, ASSET_LEVEL_TROPHYRACE, 0);
                    break;
                case LEVEL_CONTEXT_TROPHY_RESULTS:
                    load_menu_with_level_background(MENU_TROPHY_RACE_RANKINGS, ASSET_LEVEL_TROPHYRACE, 0);
                    break;
                case LEVEL_CONTEXT_UNUSED:
                    // Trophy race related?
                    load_menu_with_level_background(MENU_UNUSED_22, ASSET_LEVEL_TROPHYRACE, 0);
                    break;
                case LEVEL_CONTEXT_CHARACTER_SELECT:
                    // Go to character select menu from "Select Character" option in tracks menu.
                    i = 0;
                    if (is_drumstick_unlocked()) {
                        i ^= 1;
                    }
                    if (is_tt_unlocked()) {
                        i ^= 3;
                    }
                    charselect_prev(1, 0);
                    load_menu_with_level_background(MENU_CHARACTER_SELECT, ASSET_LEVEL_CHARACTERSELECT, i);
                    break;
                case LEVEL_CONTEXT_UNK7:
                    gIsLoading = TRUE;
                    load_menu_with_level_background(MENU_NEWGAME_CINEMATIC, SPECIAL_MAP_ID_NO_LEVEL, 0);
                    gIsLoading = FALSE;
                    break;
                case LEVEL_CONTEXT_CREDITS:
                    load_menu_with_level_background(MENU_CREDITS, SPECIAL_MAP_ID_NO_LEVEL, 0);
                    break;
            }
        } else if (D_801234FC == 1) {
            if (gLevelSettings[2] == -1) {
                load_menu_with_level_background(MENU_UNUSED_8, SPECIAL_MAP_ID_NO_LEVEL, 0);
            } else {
                gIsLoading = TRUE;
                load_menu_with_level_background(MENU_TRACK_SELECT_ADVENTURE, SPECIAL_MAP_ID_NO_LEVEL, -1);
            }
        } else if (!(buttonHeldInputs & R_TRIG)) {
            if (!(buttonHeldInputs & Z_TRIG)) {
                gPlayableMapId = gLevelSettings[0];
                gGameCurrentEntrance = gLevelSettings[15];
                gGameCurrentCutscene = gLevelSettings[gLevelSettings[1] + 8];
                gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
                if (gGameCurrentCutscene < 0) {
                    gGameCurrentCutscene = CUTSCENE_ID_UNK_64;
                }
            }
            load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
        } else {
            safe_mark_write_save_file(get_save_file_index());
            load_menu_with_level_background(MENU_TITLE, SPECIAL_MAP_ID_NO_LEVEL, 0);
        }
        D_801234FC = 0;
    }
    if (D_801234F8) {
        gPostRaceViewPort = FALSE;
        unload_level_game();
        load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
        safe_mark_write_save_file(get_save_file_index());
        D_801234F8 = FALSE;
    }
}

/**
 * Reset dialogue and set the transition effect for the cutscene showing an unlocked Drumstick.
 */
void set_drumstick_unlock_transition(void) {
    gDrumstickSceneLoadTimer = 44;
    gIsPaused = 0;
    menu_close_dialogue();
    transition_begin(&gDrumstickSceneTransition);
}

/**
 * Set the postrace viewport var to match the finish state.
 * The game never actually uses this beyond checking it's nonzero.
 */
void race_postrace_type(s32 finishState) {
    gPostRaceViewPort = finishState + 1;
}

void func_8006D8F0(UNUSED s32 arg0) {
    s32 temp;
    if (gGameMode != GAMEMODE_UNUSED_4) {
        gPlayableMapId = gLevelSettings[0];
        gGameCurrentEntrance = 0;
        gGameCurrentCutscene = CUTSCENE_ID_UNK_64;
        temp = gLevelSettings[1];
        if (gLevelSettings[15] >= 0) {
            gGameCurrentEntrance = gLevelSettings[15];
        }
        if (gLevelSettings[temp + 8] >= 0) {
            gGameCurrentCutscene = gLevelSettings[temp + 8];
        }
        D_801234F8 = TRUE;
    }
}

void func_8006D968(s8 *arg0) {
    // Is arg0 LevelObjectEntry_Exit?
    s32 i;
    if (gGameMode != GAMEMODE_UNUSED_4) {
        gLevelSettings[0] = gPlayableMapId;
        for (i = 0; i < 2; i++) {
            gLevelSettings[i + 2] = arg0[i + 8];   // 0x8-0x9 - destinationMapId
            gLevelSettings[i + 4] = arg0[i + 10];  // 0xA-0xB - overworldSpawnIndex
            gLevelSettings[i + 6] = arg0[i + 12];  // 0xC-0xD - ?
            gLevelSettings[i + 8] = arg0[i + 14];  // 0xE-0xF - ?
            gLevelSettings[i + 10] = arg0[i + 18]; // 0x12-0x13 - ?
            gLevelSettings[i + 12] = arg0[i + 20]; // 0x14-0x15 - ?
        }
        gLevelSettings[14] = arg0[22]; // 0x16 - ?
        gLevelSettings[15] = arg0[23]; // 0x17 returnSpawnIndex
        D_801234FC = 1;
    }
}

/**
 * Returns the current game mode.
 */
GameMode get_game_mode(void) {
    return gGameMode;
}

/**
 *  Sets the current game mode.
 *  Official Name: mainSetMode?
 */
UNUSED void set_game_mode(s32 changeTo) {
    gGameMode = changeTo;
}

/**
 * Sets up and loads a level to be used in the background of the menu that's about to be set up.
 * Used for every kind of menu that's not ingame.
 */
void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId) {
    alloc_displaylist_heap(PLAYER_ONE);
    gGameMode = GAMEMODE_MENU;
    gRenderMenu = TRUE;
    set_sound_channel_volume(0, 32767);
    set_sound_channel_volume(1, 32767);
    set_sound_channel_volume(2, 32767);
    camera_init();

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

/**
 * Sets the vehicle option that the next level loaded for a menu may use.
 */
void set_vehicle_id_for_menu(Vehicle vehicleId) {
    stubbed_printf("Swapping\n");
    gMenuVehicleID = vehicleId;
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
    camera_init();
    load_game_text_table();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, cutsceneId);
    init_hud(get_viewport_count());
    func_800AE728(4, 4, 0x6E, 0x30, 0x20, 0);
    ainode_update();
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
        free_hud();
        free_game_text_table();
        set_free_queue_state(2);
    }
    gIsLoading = FALSE;
}

/**
 * Used in menus, update objects and draw the game.
 * In the tracks menu, this only runs if there's a track actively loaded.
 */
void update_menu_scene(s32 updateRate) {
    if (get_thread30_level_id_to_load() == NULL) {
        func_80010994(updateRate);
        gParticlePtrList_flush();
        ainode_update();
        render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
        process_onscreen_textbox(updateRate);
        init_rdp_and_framebuffer(&gCurrDisplayList);
        divider_draw(&gCurrDisplayList);
        divider_clear_coverage(&gCurrDisplayList);
    }
}

/**
 * Main function for handling behaviour in menus.
 * Runs the menu code, with a simplified object update and scene rendering system.
 */
void menu_logic_loop(s32 updateRate) {
    s32 menuLoopResult;
    s32 temp;
    s32 playerVehicle;
    s32 temp5;

    gIsPaused = FALSE;
    gPostRaceViewPort = NULL;
    if (!gIsLoading && gRenderMenu) {
        update_menu_scene(updateRate);
    }
    menuLoopResult =
        menu_loop(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
    gRenderMenu = TRUE;
    if (menuLoopResult == -2) {
        gRenderMenu = FALSE;
        return;
    }
    if (menuLoopResult != -1 && menuLoopResult & MENU_RESULT_FLAGS_200) {
        unload_level_menu();
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        gDPFullSync(gCurrDisplayList++);
        gSPEndDisplayList(gCurrDisplayList++);
        gPlayableMapId = menuLoopResult & 0x7F;
        gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
        gGameCurrentEntrance = 0;
        gGameCurrentCutscene = CUTSCENE_ID_UNK_64;
        gGameMode = GAMEMODE_INGAME;
        gIsPaused = FALSE;
        gPostRaceViewPort = NULL;
        load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
        safe_mark_write_save_file(get_save_file_index());
        return;
    }
    if (menuLoopResult != -1 && menuLoopResult & MENU_RESULT_FLAGS_100) {
        unload_level_game();
        gIsPaused = FALSE;
        gPostRaceViewPort = NULL;
        switch (menuLoopResult & 0x7F) {
            case MENU_RESULT_TRACKS_MODE:
                load_menu_with_level_background(MENU_TRACK_SELECT, SPECIAL_MAP_ID_NO_LEVEL, 1);
                break;
            case MENU_RESULT_UNK14:
                gPlayableMapId = ASSET_LEVEL_CENTRALAREAHUB;
                gGameCurrentEntrance = 0;
                gGameCurrentCutscene = CUTSCENE_ID_UNK_64;
                gGameMode = GAMEMODE_INGAME;
                load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
                safe_mark_write_save_file(get_save_file_index());
                break;
            case MENU_RESULT_RETURN_TO_GAME:
                gGameCurrentEntrance = 0;
                gPlayableMapId = gLevelSettings[0];
                gGameCurrentCutscene = CUTSCENE_ID_UNK_64;
                gGameMode = GAMEMODE_INGAME;
                temp5 = gLevelSettings[1];
                if (gLevelSettings[15] >= 0) {
                    gGameCurrentEntrance = gLevelSettings[15];
                }
                temp = gLevelSettings[temp5 + 8];
                if (temp >= 0) {
                    gGameCurrentCutscene = temp;
                }
                load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
                safe_mark_write_save_file(get_save_file_index());
                break;
            case MENU_RESULT_UNK2:
                gGameMode = GAMEMODE_INGAME;
                load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
                break;
            case MENU_RESULT_UNK3:
                gGameMode = GAMEMODE_INGAME;
                gPlayableMapId = gLevelSettings[0];
                gGameCurrentEntrance = gLevelSettings[15];
                gGameCurrentCutscene = gLevelSettings[gLevelSettings[1] + 8];
                gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
                load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, gLevelDefaultVehicleID);
                break;
            default:
                load_menu_with_level_background(MENU_TITLE, SPECIAL_MAP_ID_NO_LEVEL, 0);
                break;
        }
        return;
    }
    if (menuLoopResult & MENU_RESULT_FLAGS_80 && menuLoopResult != -1) {
        unload_level_menu();
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        gDPFullSync(gCurrDisplayList++);
        gSPEndDisplayList(gCurrDisplayList++);

        menuLoopResult &= 0x7f;
        gLevelSettings[1] = menuLoopResult;
        gLevelSettings[0] = gPlayableMapId;

        gPlayableMapId = gLevelSettings[menuLoopResult + 2];
        gGameCurrentEntrance = gLevelSettings[menuLoopResult + 4];
        gGameMode = GAMEMODE_INGAME;
        gGameCurrentCutscene = gLevelSettings[menuLoopResult + 12];
        playerVehicle = get_player_selected_vehicle(PLAYER_ONE);
        gGameNumPlayers = gSettingsPtr->gNumRacers - 1;
        load_level_game(gPlayableMapId, gGameNumPlayers, gGameCurrentEntrance, playerVehicle);
        D_801234FC = 0;
        gLevelDefaultVehicleID = gMenuVehicleID;
        return;
    }
    if (menuLoopResult > 0) {
        unload_level_menu();
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        gDPFullSync(gCurrDisplayList++);
        gSPEndDisplayList(gCurrDisplayList++);
        gGameMode = GAMEMODE_INGAME;
        load_next_ingame_level(menuLoopResult, -1, gLevelDefaultVehicleID);
        if (gSettingsPtr->newGame && !is_in_tracks_mode()) {
            music_change_on();
            gSettingsPtr->newGame = FALSE;
        }
    }
}

/**
 * Loads a level, intended to be used in a menu.
 * Skips loading many things, otherwise used in gameplay.
 */
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
        //!@bug: Forcing the plane here makes all AI use plane paths.
        //! This can be seen most evidently in the Ancient Lake demo.
        load_level_menu(levelId, numberOfPlayers, 0, VEHICLE_PLANE, cutsceneId);
        gIsLoading = FALSE;
        return;
    }
    gIsLoading = TRUE;
}

/**
 * Initialise global game settings data.
 * Allocate space to accomodate it then set the start points for each data point.
 */
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
    gSettingsPtr->courseFlagsPtr = (s32 *) ((u8 *) gSettingsPtr + sizes[0]);
    gSettingsPtr->balloonsPtr = (s16 *) ((u8 *) gSettingsPtr + sizes[1]);
    gSettingsPtr->tajFlags = 0;
    gSettingsPtr->flapInitialsPtr[0] = (u16 *) ((u8 *) gSettingsPtr + sizes[2]);
    gSettingsPtr->flapInitialsPtr[1] = (u16 *) ((u8 *) gSettingsPtr + sizes[3]);
    gSettingsPtr->flapInitialsPtr[2] = (u16 *) ((u8 *) gSettingsPtr + sizes[4]);
    gSettingsPtr->flapTimesPtr[0] = (u16 *) ((u8 *) gSettingsPtr + sizes[5]);
    gSettingsPtr->flapTimesPtr[1] = (u16 *) ((u8 *) gSettingsPtr + sizes[6]);
    gSettingsPtr->flapTimesPtr[2] = (u16 *) ((u8 *) gSettingsPtr + sizes[7]);
    gSettingsPtr->courseInitialsPtr[0] = (u16 *) ((u8 *) gSettingsPtr + sizes[8]);
    gSettingsPtr->courseInitialsPtr[1] = (u16 *) ((u8 *) gSettingsPtr + sizes[9]);
    gSettingsPtr->courseInitialsPtr[2] = (u16 *) ((u8 *) gSettingsPtr + sizes[10]);
    gSettingsPtr->courseTimesPtr[0] = (u16 *) ((u8 *) gSettingsPtr + sizes[11]);
    gSettingsPtr->courseTimesPtr[1] = (u16 *) ((u8 *) gSettingsPtr + sizes[12]);
    gSettingsPtr->courseTimesPtr[2] = (u16 *) ((u8 *) gSettingsPtr + sizes[13]);
    gSettingsPtr->unk4C = (Settings4C *) &gLevelSettings;
    gSaveDataFlags = // Set bits 0/1/2/8 and wipe out all others
        SAVE_DATA_FLAG_READ_FLAP_TIMES | SAVE_DATA_FLAG_READ_COURSE_TIMES | SAVE_DATA_FLAG_READ_SAVE_DATA |
        SAVE_DATA_FLAG_READ_EEPROM_SETTINGS;
}

/**
 * Set the init values for each racer based on which character they are and which player they are.
 * Then reset race status.
 */
void init_racer_headers(void) {
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

/**
 * Depending on flags, clear fastest lap times and/or overall course times.
 */
void clear_lap_records(Settings *settings, s32 flags) {
    s32 i, j;
    s32 numWorlds, numLevels;
    s32 index;
    u16 *temp_v0;

    get_number_of_levels_and_worlds(&numLevels, &numWorlds);
    temp_v0 = (u16 *) get_misc_asset(ASSET_MISC_23);
    for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
        for (j = 0; j < numLevels; j++) {
            index = (j * 12) + (i * 4);
            if (flags & 1) {
                settings->flapInitialsPtr[i][j] = temp_v0[index + 3];
                settings->flapTimesPtr[i][j] = temp_v0[index + 2];
            }
            if (flags & 2) {
                settings->courseInitialsPtr[i][j] = temp_v0[index + 1];
                settings->courseTimesPtr[i][j] = temp_v0[index];
            }
        }
    }
}

/**
 * Set all game progression values to their default, as if it were a new game.
 */
void clear_game_progress(Settings *settings) {
    s32 i;
    s32 worldCount;
    s32 levelCount;

    get_number_of_levels_and_worlds(&levelCount, &worldCount);
    settings->newGame = TRUE;

    for (i = 0; i < worldCount; i++) {
        settings->balloonsPtr[i] = 0;
    }
    for (i = 0; i < levelCount; i++) {
        settings->courseFlagsPtr[i] = RACE_UNATTEMPTED;
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
 * Call functions to set all game save data to the default.
 */
UNUSED void reset_save_data(void) {
    clear_lap_records(gSettingsPtr, 3);
    clear_game_progress(gSettingsPtr);
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
        gNMIMesgBuf = (s32) ((osRecvMesg(&gNMIMesgQueue, NULL, OS_MESG_NOBLOCK) + 1) != 0);
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
    // Wipe out bits 8 and 9
    gSaveDataFlags &= ~(SAVE_DATA_FLAG_READ_EEPROM_SETTINGS | SAVE_DATA_FLAG_WRITE_EEPROM_SETTINGS);
    // Place saveFileIndex at bits 8 and 9 and set bit 2
    gSaveDataFlags |= (SAVE_DATA_FLAG_READ_SAVE_DATA | ((saveFileIndex & SAVE_DATA_FLAG_INDEX_VALUE) << 8));
}

/**
 * Marks a flag to read all save file data from flash.
 */
void mark_read_all_save_files(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_READ_ALL_SAVE_DATA; // Set bit 3
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
    gSaveDataFlags &= ~SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER_BITS; // Wipe out bits 10 and 11
    gSaveDataFlags |= (SAVE_DATA_FLAG_WRITE_SAVE_DATA |
                       ((saveFileIndex & 3) << 10)); // Set bit 6 and place saveFileIndex into bits 10 and 11
}

/**
 * Marks a flag to write a save file to flash as long as we're not in tracks mode, and we're in the draw game render
 * context. This should prevent save data from being overwritten outside of Adventure Mode. Official Name: mainSaveGame2
 */
void safe_mark_write_save_file(s32 saveFileIndex) {
    if (gGameMode == GAMEMODE_INGAME && !is_in_tracks_mode()) {
        gSaveDataFlags &= ~SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER_BITS; // Wipe out bits 10 and 11
        gSaveDataFlags |= (SAVE_DATA_FLAG_WRITE_SAVE_DATA | ((saveFileIndex & 3) << 10));
        ; // Set bit 6 and place saveFileIndex into bits 10 and 11
    }
}

/**
 * Marks a flag to erase a save file from flash later
 */
void mark_save_file_to_erase(s32 saveFileIndex) {
    // Set bit 7 and and place saveFileIndex into bits 10 and 11 while wiping everything else
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
        totalSize = ((gNumF3dCmdsPerPlayer[num] * sizeof(Gwords))) + ((gNumHudMatPerPlayer[num] * sizeof(Matrix))) +
                    ((gNumHudVertsPerPlayer[num] * sizeof(Vertex))) + ((gNumHudTrisPerPlayer[num] * sizeof(Triangle)));
        gDisplayLists[0] = (Gfx *) allocate_at_address_in_main_pool(totalSize, (u8 *) gDisplayLists[0], COLOUR_TAG_RED);
        gDisplayLists[1] =
            (Gfx *) allocate_at_address_in_main_pool(totalSize, (u8 *) gDisplayLists[1], COLOUR_TAG_YELLOW);
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
        gMatrixHeap[0] = (MatrixS *) ((u8 *) gDisplayLists[0] + ((gNumF3dCmdsPerPlayer[num] * sizeof(Gwords))));
        gTriangleHeap[0] = (TriangleList *) ((u8 *) gMatrixHeap[0] + ((gNumHudMatPerPlayer[num] * sizeof(Matrix))));
        gVertexHeap[0] = (Vertex *) ((u8 *) gTriangleHeap[0] + ((gNumHudTrisPerPlayer[num] * sizeof(Triangle))));
        gMatrixHeap[1] = (MatrixS *) ((u8 *) gDisplayLists[1] + ((gNumF3dCmdsPerPlayer[num] * sizeof(Gwords))));
        gTriangleHeap[1] = (TriangleList *) ((u8 *) gMatrixHeap[1] + ((gNumHudMatPerPlayer[num] * sizeof(Matrix))));
        gVertexHeap[1] = (Vertex *) ((u8 *) gTriangleHeap[1] + ((gNumHudTrisPerPlayer[num] * sizeof(Triangle))));
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
    totalSize = (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords)) +
                (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix)) +
                (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex)) +
                (gNumHudTrisPerPlayer[numberOfPlayers] * sizeof(Triangle));

    gDisplayLists[0] = (Gfx *) allocate_from_main_pool_safe(totalSize, COLOUR_TAG_RED);
    gMatrixHeap[0] = (MatrixS *) ((u8 *) gDisplayLists[0] + (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords)));
    gVertexHeap[0] = (Vertex *) ((u8 *) gMatrixHeap[0] + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix)));
    gTriangleHeap[0] =
        (TriangleList *) ((u8 *) gVertexHeap[0] + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex)));

    gDisplayLists[1] = (Gfx *) allocate_from_main_pool_safe(totalSize, COLOUR_TAG_YELLOW);
    gMatrixHeap[1] = (MatrixS *) ((u8 *) gDisplayLists[1] + (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords)));
    gVertexHeap[1] = (Vertex *) ((u8 *) gMatrixHeap[1] + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix)));
    gTriangleHeap[1] =
        (TriangleList *) ((u8 *) gVertexHeap[1] + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex)));

    gCurrNumF3dCmdsPerPlayer = gNumF3dCmdsPerPlayer[numberOfPlayers];
    gCurrNumHudMatPerPlayer = gNumHudMatPerPlayer[numberOfPlayers];
    gCurrNumHudTrisPerPlayer = gNumHudTrisPerPlayer[numberOfPlayers];
    gCurrNumHudVertsPerPlayer = gNumHudVertsPerPlayer[numberOfPlayers];
}

/**
 * Set a delayed level trigger and a transition.
 * Once the timer hits zero, the level will change.
 */
void level_transition_begin(s32 type) {
    if (gLevelLoadTimer == 0) {
        gLevelLoadTimer = 40;
        gLevelLoadType = LEVEL_LOAD_NORMAL;
        D_80123526 = 0;
        if (type == 1) { // FADE_BARNDOOR_HORIZONTAL?
            transition_begin(&gLevelFadeOutTransition);
        }
        if (type == 3) { // FADE_CIRCLE?
            gLevelLoadTimer = 282;
            transition_begin(&D_800DD424);
        }
        if (type == 4) { // FADE_WAVES?
            gLevelLoadTimer = 360;
            transition_begin(&D_800DD424);
        }
        if (type == 0) { // FADE_FULLSCREEN?
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
        if ((gSettingsPtr->trophies & 0xFF) == 0xFF && !(gSettingsPtr->cutsceneFlags & CUTSCENE_LIGHTHOUSE_ROCKET) &&
            gSettingsPtr->bosses & 1) {
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

/**
 * Set the number of frames to disallow pausing for.
 */
void set_pause_lockout_timer(u8 time) {
    gPauseLockTimer = time;
}

/**
 * Switch the data around for player 1 and 2 for two player adventure,
 * effectively passing the lead over to the other player.
 */
void swap_lead_player(void) {
    s32 i;
    u8 temp;
    u8 *first_racer_data;
    u8 *second_racer_data;

    swap_player_1_and_2_ids();
    func_8000E194();

    first_racer_data = (u8 *) (gSettingsPtr->racers);
    second_racer_data = (u8 *) (gSettingsPtr->racers + 1);

    for (i = 0; i < (s32) sizeof(Racer); i++) {
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
        load_menu_with_level_background(MENU_BOOT, ASSET_LEVEL_OPTIONSBACKGROUND, 2);
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

#ifdef ANTI_TAMPER
/**
 * Ran on boot, will make sure the CIC chip (CIC6103) is to spec. Will return true if it's all good, otherwise it
 * returns false. The intention of this function, is an attempt to check that the cartridge is a legitimate copy. A
 * false read, meaning you're caught running an illegitimate copy, will force the game to pause when you enter the
 * world.
 */
s32 check_imem_validity(void) {
    if (IO_READ(SP_IMEM_START) != CIC_ID) {
        return FALSE;
    }
    return TRUE;
}
#endif
