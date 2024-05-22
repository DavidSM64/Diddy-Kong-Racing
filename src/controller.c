/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8006A100 */

#include "controller.h"
#include "game.h"

s32 sNoControllerPluggedIn =
    FALSE; // Looks to be a boolean for whether a controller is plugged in. FALSE if plugged in, and TRUE if not.
u16 gButtonMask = 0xFFFF; // Used when anti-cheat/anti-tamper has failed in init_level_globals()

OSMesgQueue sSIMesgQueue;
OSMesg sSIMesgBuf;
OSMesg gSIMesg;
OSContStatus gControllerStatus[MAXCONTROLLERS];
OSContPad gControllerCurrData[MAXCONTROLLERS];
OSContPad gControllerPrevData[MAXCONTROLLERS];
u16 gControllerButtonsPressed[MAXCONTROLLERS];
u16 gControllerButtonsReleased[MAXCONTROLLERS];
u8 sPlayerID[16];

/**
 * Return the serial interface message queue.
 * Official name: joyMessageQ
 */
OSMesgQueue *get_si_mesg_queue(void) {
    return &sSIMesgQueue;
}

/**
 * Initialise the player controllers, and return the status when finished.
 * Official name: joyInit
 */
s32 init_controllers(void) {
    UNUSED s32 *temp1;
    u8 bitpattern;
    UNUSED s32 *temp2;

    osCreateMesgQueue(&sSIMesgQueue, &sSIMesgBuf, 1);
    osSetEventMesg(OS_EVENT_SI, &sSIMesgQueue, gSIMesg);
    osContInit(&sSIMesgQueue, &bitpattern, gControllerStatus);
    osContStartReadData(&sSIMesgQueue);
    initialise_player_ids();

    sNoControllerPluggedIn = FALSE;

    if ((bitpattern & CONT_ABSOLUTE) && (!(gControllerStatus[0].errno & CONT_NO_RESPONSE_ERROR))) {
        return CONTROLLER_EXISTS;
    }

    if (!bitpattern) {} // Fakematch

    sNoControllerPluggedIn = TRUE;

    return CONTROLLER_MISSING;
}

/**
 * Reads arg0 for a set of flags on whether to read, write, or erase any save data.
 * Also reads the latest inputs from the controllers, and sets their values.
 * Official name: joyRead
 */
s32 handle_save_data_and_read_controller(s32 saveDataFlags, s32 updateRate) {
    Settings **allSaves;
    OSMesg unusedMsg;
    Settings *settings;
    s32 i;

    if (osRecvMesg(&sSIMesgQueue, &unusedMsg, OS_MESG_NOBLOCK) == 0) {
        // Back up old controller data
        for (i = 0; i < MAXCONTROLLERS; i++) {
            gControllerPrevData[i] = gControllerCurrData[i];
        }
        osContGetReadData(gControllerCurrData);
        if (saveDataFlags != 0) {
            settings = get_settings();
            if (SAVE_DATA_FLAG_READ_EEPROM_INDEX(saveDataFlags)) {
                read_eeprom_data(settings, SAVE_DATA_FLAG_READ_EEPROM_INDEX(saveDataFlags));
            }
            if (saveDataFlags & SAVE_DATA_FLAG_READ_ALL_SAVE_DATA) {
                allSaves = get_all_save_files_ptr();
                for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
                    read_save_file(i, allSaves[i]);
                }
            }
            if (saveDataFlags & SAVE_DATA_FLAG_READ_SAVE_DATA) {
                read_save_file(SAVE_DATA_FLAG_READ_SAVE_FILE_NUMBER(saveDataFlags), settings);
            }
            if (SAVE_DATA_FLAG_WRITE_EEPROM_INDEX(saveDataFlags)) {
                write_eeprom_data(settings, SAVE_DATA_FLAG_WRITE_EEPROM_INDEX(saveDataFlags));
            }
            if (saveDataFlags & SAVE_DATA_FLAG_WRITE_SAVE_DATA) {
                write_save_data(SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER(saveDataFlags), settings);
            }
            if (saveDataFlags & SAVE_DATA_FLAG_ERASE_SAVE_DATA) {
                erase_save_file(SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER(saveDataFlags), settings);
            }
            // @bug These next two if statements check the same bits
            // as the ones used to set the save file number to read from.
            if (saveDataFlags & SAVE_DATA_FLAG_READ_EEPROM_SETTINGS) {
                read_eeprom_settings(get_eeprom_settings_pointer());
            }
            if (saveDataFlags & SAVE_DATA_FLAG_WRITE_EEPROM_SETTINGS) {
                write_eeprom_settings(get_eeprom_settings_pointer());
            }
            // Reset all flags
            saveDataFlags = 0;
        }
        rumble_update(updateRate);
        osContStartReadData(&sSIMesgQueue);
    }
    for (i = 0; i < MAXCONTROLLERS; i++) {
        if (sNoControllerPluggedIn) {
            gControllerCurrData[i].button = 0;
        }
        // XOR the diff between the last read of the controller data with the current read to see what buttons have been
        // pushed and released.
        gControllerButtonsPressed[i] =
            ((gControllerCurrData[i].button ^ gControllerPrevData[i].button) & gControllerCurrData[i].button) &
            gButtonMask;
        gControllerButtonsReleased[i] =
            ((gControllerCurrData[i].button ^ gControllerPrevData[i].button) & gControllerPrevData[i].button) &
            gButtonMask;
    }
    return saveDataFlags;
}

/**
 * Set the first 4 player ID's to the controller numbers, so players can input in the menus after boot.
 * Official name: joyResetMap
 */
void initialise_player_ids(void) {
    s32 i;
    for (i = 0; i < MAXCONTROLLERS; i++) {
        sPlayerID[i] = i;
    }
}

/**
 * Assign the first four player ID's to the index of the connected players.
 * Assign the next four player ID's to the index of the players who are not connected.
 * Official name: joyCreateMap
 */
void charselect_assign_players(s8 *activePlayers) {
    s32 i;
    s32 temp = 0;
    for (i = 0; i < MAXCONTROLLERS; i++) {
        if (activePlayers[i]) {
            sPlayerID[temp++] = i;
        }
    }
    for (i = 0; i < MAXCONTROLLERS; i++) {
        if (!activePlayers[i]) {
            sPlayerID[temp++] = i;
        }
    }
}

/**
 * Returns the id of the selected index.
 * Official name: joyGetController
 */
u8 get_player_id(s32 player) {
    return sPlayerID[player];
}

/**
 * Swaps the ID's of the first two indexes.
 * This applies in 2 player adventure, so that player 2 can control the car in the overworld.
 */
void swap_player_1_and_2_ids(void) {
    u8 tempID = sPlayerID[0];
    sPlayerID[0] = sPlayerID[1];
    sPlayerID[1] = tempID;
}

/**
 * Returns the buttons that are currently pressed down on the controller.
 * Official name: joyGetButtons
 */
u16 get_buttons_held_from_player(s32 player) {
    return gControllerCurrData[sPlayerID[player]].button;
}

/**
 * Returns the buttons that are newly pressed during that frame.
 * NOTE: This was a u16, but we only got a match in menu_ghost_data_loop when it was a u32 for some reason
 * Official name: joyGetPressed
 */
u32 get_buttons_pressed_from_player(s32 player) {
    return gControllerButtonsPressed[sPlayerID[player]];
}

/**
 * Returns the buttons that are no longer pressed in that frame.
 * Official name: joyGetReleased
 */
u16 get_buttons_released_from_player(s32 player) {
    return gControllerButtonsReleased[sPlayerID[player]];
}

/**
 * Clamps the X joystick axis of the selected player to 70 and returns it.
 * Official name: joyGetStickX
 */
s32 clamp_joystick_x_axis(s32 player) {
    return clamp_joystick(gControllerCurrData[sPlayerID[player]].stick_x);
}

/**
 * Clamps the Y joystick axis of the selected player to 70 and returns it.
 * Official name: joyGetStickY
 */
s32 clamp_joystick_y_axis(s32 player) {
    return clamp_joystick(gControllerCurrData[sPlayerID[player]].stick_y);
}

/**
 * Keeps the joysticks axis reads no higher than 70 (of a possible 127 or -128)
 * Will also pull the reading towards the centre.
 */
s8 clamp_joystick(s8 stickMag) {
    if (stickMag < JOYSTICK_DEADZONE && stickMag > -JOYSTICK_DEADZONE) {
        return 0;
    }
    if (stickMag > 0) {
        stickMag -= JOYSTICK_DEADZONE;
        if (stickMag > JOYSTICK_MAX_RANGE) {
            stickMag = JOYSTICK_MAX_RANGE;
        }
    } else {
        stickMag += JOYSTICK_DEADZONE;
        if (stickMag < -JOYSTICK_MAX_RANGE) {
            stickMag = -JOYSTICK_MAX_RANGE;
        }
    }
    return stickMag;
}

/**
 * Used when anti-cheat/anti-tamper has failed in init_level_globals()
 * Official Name: joySetSecurity
 */
void disable_button_mask(void) {
    gButtonMask = 0;
}
