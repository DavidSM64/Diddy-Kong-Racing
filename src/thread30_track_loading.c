/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C7350 */

#include "thread30_track_loading.h"
#include "macros.h"
#include "libultra_internal.h"
#include "game.h"
#include "stacks.h"

/************ .data ************/

s32 gThread30NeedToLoadLevel = FALSE;
s32 gThread30LevelIdToLoad = -1;
s32 gThread30CutsceneIdToLoad = -1;
s32 gThread30LoadDelay = 0;

/*******************************/

/************ .bss ************/

// Used for __osException, but .bss file order is weird. Need to fix later.
u8 leoDiskStack[16]; // technically should have a OS_LEO_STACKSIZE or something.
                     // This is something like 4096 in libreultra...
OSThread gThread30;
OSMesgQueue gThread30MesgQueue;
OSMesg gThread30Message[2];

// Currently defined in osViMgr.c
// There are a few stacks defined next to each other. Maybe they are in their own separate file?
extern u64 gThread30Stack[0x400];

/*****************************/

/**
 * Initalizes and starts thread30()
 */
void create_and_start_thread30(void) {
    osCreateMesgQueue(&gThread30MesgQueue, &gThread30Message[0], ARRAY_COUNT(gThread30Message));
    osCreateThread(&gThread30, 30, &thread30_track_loading, NULL, &gThread30Stack[0x400], 8);
    osStartThread(&gThread30);
}

/**
 * Stop thread30()
 * Official Name: amStop
 */
void stop_thread30(void) {
    osStopThread(&gThread30);
}

/**
 * Returns the value in gThread30NeedToLoadLevel.
 */
s32 get_thread30_level_id_to_load(void) {
    return gThread30NeedToLoadLevel;
}

/**
 * If gThread30NeedToLoadLevel is set, then decrement gThread30LoadDelay. If gThread30LoadDelay is 0,
 * then signal thread30 to load a level.
 */
void tick_thread30(void) {
    if (gThread30NeedToLoadLevel && gThread30LoadDelay > 0) {
        gThread30LoadDelay--;
        if (gThread30LoadDelay == 0) {
            // Signal thread30 that the level needs to load.
            osSendMesg(&gThread30MesgQueue, (OSMesg *) OS_MESG_TYPE_LOOPBACK, OS_MESG_NOBLOCK);
        }
    }
}

/**
 * Returns the value in gThread30LoadDelay.
 */
UNUSED s32 get_thread30_load_delay(void) {
    return gThread30LoadDelay;
}

/**
 * Sets a level id and cutscene id to be loaded. Used in the tracks menu & credits menu.
 * Returns 1 if successful, or 0 if gThread30NeedToLoadLevel was already set.
 */
s32 set_level_to_load_in_background(s32 levelId, s32 cutsceneId) {
    if (!gThread30NeedToLoadLevel) {
        gThread30LoadDelay = 4;
        gThread30LevelIdToLoad = levelId;
        gThread30CutsceneIdToLoad = cutsceneId;
        gThread30NeedToLoadLevel = TRUE;
        return TRUE;
    }
    return FALSE;
}

/**
 * Waits for a signal from the main thread to load a level asynchronously.
 */
void thread30_track_loading(UNUSED void *arg) {
    OSMesg mesg = 0;
    while (TRUE) {
        // Wait for a signal from the main thread
        osRecvMesg(&gThread30MesgQueue, &mesg, OS_MESG_BLOCK);
        if (mesg != (OSMesg) OS_MESG_TYPE_LOOPBACK) {
            continue;
        }
        // -1 means there won't be any racers loaded.
        load_level_for_menu(gThread30LevelIdToLoad, -1, gThread30CutsceneIdToLoad);
        gThread30NeedToLoadLevel = FALSE;
    }
}
