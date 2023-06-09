/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800d0dd0 */

#include "dkr_usb.h"
#include "autotracker.h"
#include "../memory.h"
#include "../save_data.h"
#include "../menu.h"

void send_save_data_to_computer_using_settings(Settings *settings) {
    s32 saveFileSize = 5 * sizeof(u64);
    u8 *alloc = (u8*)allocate_from_main_pool_safe(saveFileSize + 4, COLOUR_TAG_WHITE);
    func_800732E8(settings, alloc);
    alloc[saveFileSize] = (u8)gSaveFileIndex;
    alloc[saveFileSize + 1] = 0; // Set last 3 bits to zero (unused)
    alloc[saveFileSize + 2] = 0;
    alloc[saveFileSize + 3] = 0;
    usb_send_data("SAVE", alloc, saveFileSize + 4);
    free_from_memory_pool(alloc);
}

void send_gold_balloon_data_to_computer(u16 balloonFlag, u8 worldId, u8 levelId) {
    u8 *alloc = (u8*)allocate_from_main_pool_safe(4, COLOUR_TAG_WHITE);
    ((u16*)alloc)[0] = balloonFlag;
    alloc[2] = worldId;
    alloc[3] = levelId;
    usb_send_data("GOLD", alloc, 4);
    free_from_memory_pool(alloc);
}

extern s32 gMapId; // Defined in game.c

void send_map_warp_data(u8 curMapId, u8 mapIdToWarpTo) {
    u8 *alloc = (u8*)allocate_from_main_pool_safe(4, COLOUR_TAG_WHITE);
    if(curMapId == 0xFF) {
        curMapId = gMapId;
    }
    alloc[0] = curMapId; // Current Map ID
    alloc[1] = mapIdToWarpTo; // Map ID to warp to
    alloc[2] = 0x00; // Always zero (Unused)
    alloc[3] = 0x00; // Always zero (Unused)
    usb_send_data("MAPW", alloc, 4);
    free_from_memory_pool(alloc);
}

extern s8 D_80121250[16]; // Defined in thread3_main.c
void send_map_warp_data_from_warp() {
    send_map_warp_data(D_80121250[0], D_80121250[2]);
}


// Wait half a second before sending another update.
#define SEND_MAP_DELAY_AMOUNT (30) 
s32 sendMapDelay = 0;

// Will be called from a loop (mainly obj_loop_levelname)
void send_map_warp_data_from_loop(u8 mapIdToWarpTo, s32 updateRate) {
    sendMapDelay -= updateRate;
    if (sendMapDelay > 0) {
        return;
    }
    send_map_warp_data(0xFF, mapIdToWarpTo);
    sendMapDelay = SEND_MAP_DELAY_AMOUNT;
}