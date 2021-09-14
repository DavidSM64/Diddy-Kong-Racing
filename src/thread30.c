/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C7350 */

#include "thread30.h"
#include "macros.h"
#include "libultra_internal.h"

/************ .data ************/

s32 gThread30NeedToLoadLevel = FALSE;
s32 gThread30LevelIdToLoad = -1;
s32 gThread30CutsceneIdToLoad = -1;
s32 gThread30LoadDelay = 0;

/*******************************/

/************ .bss ************/

// Used for __osException, but .bss file order is weird. Need to fix later.
s32 D_8012AAE0[4];

OSThread gThread30;
OSMesgQueue gThread30MesgQueue;
OSMesg gThread30Messages[2];

s32 D_8012ACC0[1305]; // Unused? Might be another stack.

// Currently defined in osViMgr.c
// There are a few stacks defined next to each other. Maybe they are in their own separate file?
extern void *gThread30Stack; 

/*****************************/

/**
 * Initalizes and starts thread30()
 */
void create_and_start_thread30(void) {
    osCreateMesgQueue(&gThread30MesgQueue, &gThread30Messages, 2);
    osCreateThread(&gThread30, 30, &thread30, NULL, &gThread30Stack, 8);
    osStartThread(&gThread30);
}

/**
 * Stop thread30()
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
 * Unused.
 */
void tick_thread30(void) {
    if (gThread30NeedToLoadLevel && gThread30LoadDelay > 0) {
        gThread30LoadDelay--;
        if (gThread30LoadDelay == 0) {
            // Signal thread30 that the level needs to load.
            osSendMesg(&gThread30MesgQueue, OS_MESG_TYPE_LOOPBACK, 0);
        }
    }
}

/**
 * Returns the value in gThread30LoadDelay.
 * Unused.
 */
s32 get_thread30_load_delay(void) {
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
void thread30(void *arg) {
    OSMesg mesg = 0;
    while(TRUE){
        // Wait for a signal from the main thread
        do {
            osRecvMesg(&gThread30MesgQueue, &mesg, 1);
        } while(mesg != (OSMesg)OS_MESG_TYPE_LOOPBACK);
        load_level_for_menu(gThread30LevelIdToLoad, -1, gThread30CutsceneIdToLoad); // -1 means there won't be any racers loaded.
        gThread30NeedToLoadLevel = FALSE;
    }
}
