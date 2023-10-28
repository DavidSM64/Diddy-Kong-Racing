/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80072250 */

#include "save_data.h"
#include "memory.h"
#include "PR/pfs.h"
#include "PR/os_cont.h"
#include "macros.h"
#include "structs.h"
#include "camera.h"
#include "objects.h"
#include "game.h"
#include "thread3_main.h"
#include "controller.h"

/************ .data ************/

s8 *D_800DE440 = 0;

u8 gN64FontCodes[] = "\0               0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#'*+,-./:=?@";

u8 sControllerPaksPresent = 0; // Bits 0, 1, 2, and 3 of the bit pattern correspond to Controllers 1, 2, 3, and 4. 1 if a controller pak is present
s32 D_800DE48C = 0;

/*******************************/

/************ .rodata ************/

UNUSED const char D_800E7590[] = "Region = %d	 loc = %x	 size = %x\t";
UNUSED const char D_800E75B4[] = "FREE";
UNUSED const char D_800E75BC[] = "ALLOCATED";
UNUSED const char D_800E75C8[] = "ALLOCATED,FIXED";
UNUSED const char D_800E75D8[] = "\n";
UNUSED const char D_800E75DC[] = "\n";
UNUSED const char D_800E75E0[] = "Region number = %d\t";
UNUSED const char D_800E75F4[] = "maxSlots = %d\t";
UNUSED const char D_800E7604[] = "slotsUsed = %d\t";
UNUSED const char D_800E7614[] = "loc = %x\t";
UNUSED const char D_800E7620[] = "size = %x\n";
UNUSED const char D_800E762C[] = "\n";

// File Names
const char sDKRacingAdv1[] = "DKRACING-ADV";
const char sDKRacingAdv2[] = "DKRACING-ADV";
const char sDKRacingTimes1[] = "DKRACING-TIMES";
const char sDKRacingTimes2[] = "DKRACING-TIMES";
const char sDKRacingAdv3[] = "DKRACING-ADV";
const char sDKRacingAdv4[] = "DKRACING-ADV";
const char sDKRacingTimes3[] = "DKRACING-TIMES";
const char sDKRacingTimes4[] = "DKRACING-TIMES";

UNUSED const char D_800E76B0[] = "WARNING : No Eprom\n";
UNUSED const char D_800E76C4[] = "WARNING : No Eprom\n";
UNUSED const char D_800E76D8[] = "WARNING : No Eprom\n";
UNUSED const char D_800E76EC[] = "WARNING : No Eprom\n";
UNUSED const char D_800E7700[] = "WARNING : No Eprom\n";
UNUSED const char D_800E7714[] = "WARNING : No Eprom\n";
UNUSED const char D_800E7728[] = "WARNING : No Eprom\n";

const char sDKRacingGhosts[] = "DKRACING-GHOSTS";
const char sDKRacingGhostFileExt[] = "";

UNUSED const char D_800E7750[] = "warning: corrupt ghost\n";

/*********************************/

/************ .bss ************/

OSMesgQueue *sControllerMesgQueue;
s32 D_80124014;

OSPfs pfs[MAXCONTROLLERS];

/* Size: 0xA bytes */
typedef struct unk_801241B8 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
} unk_801241B8;
unk_801241B8 D_801241B8[MAXCONTROLLERS];

s16 *sUnkMiscAsset19; //Misc Asset 19
/**
 * Values for Misc Asset 19
 * 00 2D 00 12 
 * 00 46 00 0A
 * 00 3C 00 3C 
 * 00 64 00 0F 
 * 00 3C 00 36 
 * 00 32 00 0F 
 * 00 32 00 34 
 * 00 46 00 3C 
 * 00 55 00 3C 
 * 00 46 00 16 
 * 00 50 00 4B 
 * 00 64 00 0C 
 * 00 3C 00 18
 * 00 50 00 1E 
 * 00 64 00 2A 
 * 00 32 00 3C 
 * 00 28 00 0A 
 * 00 28 00 0A 
 * 00 64 00 0F
**/
u8 D_801241E4;
u8 sRumblePaksPresent; // Bits 0, 1, 2, and 3 of the bit pattern correspond to Controllers 1, 2, 3, and 4. 1 if a rumble pak is present
u8 D_801241E6;
u8 D_801241E7;
s32 gRumbleDetectionTimer;
u8 *D_801241EC;
u32 D_801241F0;
u32 D_801241F4;

/*******************************/

// Guessing, but maybe this gets player id from controller index,
// but it might check for something like jointventure and will return
// the same value for controllers one and two?
u8 func_80072250(s32 arg0) {
    if ((arg0 == 0 || arg0 == 1) && func_8000E158()) {
        arg0 = 1 - arg0;
    }
    return get_player_id(arg0);
}

void func_80072298(u8 arg0) {
    D_801241E4 = arg0;
    if (arg0) {
        gRumbleDetectionTimer = 0x79;
        D_801241E6 = 0xF;
        return;
    }
    func_80072708();
}

UNUSED s32 func_800722E8(s16 controllerIndex) {
    s32 temp;
    if (controllerIndex < 0 || controllerIndex >= 4) {
        return 0;
    }
    temp = ((1 << func_80072250(controllerIndex)) & 0xFF);
    return sRumblePaksPresent & temp;
}

void func_80072348(s16 controllerIndex, u8 arg1) {
    s32 index;

    if (arg1 < 19 && controllerIndex >= 0 && controllerIndex < 4) {
        index = (func_80072250(controllerIndex)) & 0xFFFF;
        if (D_801241B8[index].unk0 == arg1) {
            if (D_801241B8[index].unk8 < 0) {
                D_801241B8[index].unk8 = -300;
            }
            D_801241B8[index].unk4 = sUnkMiscAsset19[(arg1 * 2) + 1];
        } else {
            D_801241B8[index].unk0 = arg1;
            if (sUnkMiscAsset19[arg1 * 2] != 0) {
                func_80072578(controllerIndex, sUnkMiscAsset19[arg1 * 2], sUnkMiscAsset19[(arg1 * 2) + 1]);
            }
        }
    }
}

void func_80072424(s16 controllerIndex, u8 arg1, f32 arg2) {
    s32 index;

    if (arg1 < 19 && controllerIndex >= 0 && controllerIndex < 4) {
        index = func_80072250(controllerIndex) & 0xFFFF;
        if (arg1 == D_801241B8[index].unk0) {
            if (D_801241B8[index].unk8 < 0) {
                D_801241B8[index].unk8 = -300;
            }
            D_801241B8[index].unk4 = sUnkMiscAsset19[(arg1 * 2) + 1];
        } else {
            if (arg2 < 0.0f) {
                arg2 = 0.0f;
            }
            if (arg2 > 1.0f) {
                arg2 = 1.0f;
            }
            D_801241B8[index].unk0 = arg1;
            if (sUnkMiscAsset19[arg1 * 2] != 0) {
                func_80072578(controllerIndex, (sUnkMiscAsset19[arg1 * 2] * arg2), sUnkMiscAsset19[(arg1 * 2) + 1]);
            }
        }
    }
}

void func_80072578(s16 controllerIndex, s16 arg1, s16 arg2) {
    s16 index;
    u8 new_var;

    if (D_801241E4 && controllerIndex >= 0 && controllerIndex < 4) {
        new_var = func_80072250(controllerIndex);
        index = 0xFFFF;
        index &= new_var;
        new_var = 1 << index;
        D_801241E6 |= new_var;
        D_801241E7 &= ~new_var;
        D_801241B8[index].unk6 = ((arg1 * arg1) * 0.1);
        D_801241B8[index].unk2 = ((arg1 * arg1) * 0.1);
        D_801241B8[index].unk4 = arg2;
    }
}

UNUSED void func_8007267C(s16 controllerIndex) {
    s16 index;

    if (controllerIndex >= 0 && controllerIndex < 4) {
        index = func_80072250(controllerIndex);
        D_801241E7 |= 1 << index;
        D_801241B8[index].unk4 = -1;
        D_801241B8[index].unk0 = -1;
        D_801241B8[index].unk8 = 0;
    }
}

/* Official Name: RumbleKill? */
void func_80072708(void) {
    D_800DE48C = 3;
}

/* Official Name: rumbleTick */
void rumble_controllers(s32 updateRate) {
    unk_801241B8 *temp;
    s32 pfsStatus;
    u8 i;
    u8 controllerToCheck;
    u8 pfsBitPattern;

    if ((D_801241E6 != 0) || ((D_800DE48C != 0))) {
        gRumbleDetectionTimer += updateRate;
        if (gRumbleDetectionTimer >= 121) {
            gRumbleDetectionTimer = 0;
            osPfsIsPlug(sControllerMesgQueue, &pfsBitPattern);
            for (i = 0, controllerToCheck = 1; i < MAXCONTROLLERS; i++, controllerToCheck <<= 1) {
                if ((pfsBitPattern & controllerToCheck) && !(~D_801241E6 & sRumblePaksPresent & controllerToCheck)) {
                    if (osMotorInit(sControllerMesgQueue, &pfs[i], i) != 0) {
                        D_801241E6 &= ~controllerToCheck;
                        D_801241E7 &= ~controllerToCheck;
                        sRumblePaksPresent &= ~controllerToCheck;
                    } else {
                        sRumblePaksPresent |= controllerToCheck;
                    }
                }
            }
        }
        if ((sRumblePaksPresent != 0) || (D_800DE48C != 0)) {
            pfsStatus = 0;
            if (D_800DE48C != 0) {
                osPfsIsPlug(sControllerMesgQueue, &pfsBitPattern);
            }
            for (i = 0, controllerToCheck = 1, temp = D_801241B8; i < MAXCONTROLLERS; i++, controllerToCheck <<= 1, temp++) {
                if (D_800DE48C != 0) {
                    temp->unk0 = temp->unk6 = temp->unk4 = -1;
                    if (!(pfsBitPattern & controllerToCheck)) {
                        continue;
                    } else if (osMotorInit(sControllerMesgQueue, &pfs[i], i) == 0) {
                        osMotorStop(&pfs[i]);
                    }
                } else if (D_801241E6 & sRumblePaksPresent & controllerToCheck) {
                    if (temp->unk4 <= 0) {
                        D_801241E6 &= ~controllerToCheck;
                        temp->unk0 = -1;
                        temp->unk8 = 0;
                        osMotorStop(&pfs[i]);
                    } else {
                        temp->unk4 -= updateRate;
                        temp->unk8 += updateRate;
                        if (temp->unk8 < 0) {
                            continue;
                        } else if (temp->unk8 >= 601) {
                            D_801241E6 &= ~controllerToCheck;
                            temp->unk0 = -1;
                            temp->unk8 = -300;
                            osMotorStop(&pfs[i]);
                        } else {
                            if (temp->unk2 > 490.0) {
                                if (!(D_801241E7 & controllerToCheck)) {
                                    pfsStatus |= osMotorStart(&pfs[i]);
                                    D_801241E7 |= controllerToCheck;
                                }
                            } else if (temp->unk2 < 3.6) {
                                if (D_801241E7 & controllerToCheck) {
                                    pfsStatus |= osMotorStop(&pfs[i]);
                                    D_801241E7 &= ~controllerToCheck;
                                }
                            } else if (temp->unk6 >= 256) {
                                if (!(D_801241E7 & controllerToCheck)) {
                                    pfsStatus |= osMotorStart(&pfs[i]);
                                    D_801241E7 |= controllerToCheck;
                                }
                                temp->unk6 -= 256;
                            } else {
                                if (D_801241E7 & controllerToCheck) {
                                    pfsStatus |= osMotorStop(&pfs[i]);
                                    D_801241E7 &= ~controllerToCheck;
                                }
                                temp->unk6 += temp->unk2 + 4;
                            }
                            if (1) { } // fakematch
                        }
                    }
                }
            }
            if (pfsStatus != 0) {
                sRumblePaksPresent = 0;
            }
            if (D_800DE48C != 0) {
                D_800DE48C--;
            }
        }
    }
}

// arg0 is the number of bits we care about.
s32 func_80072C54(s32 arg0) {
    s32 ret;
    u32 var_v0;

    if (arg0 <= 0) {
        return 0;
    }

    ret = 0;
    var_v0 = 1 << (arg0 - 1);

    // Loop backwards through arg0
    while (arg0 != 0) {
        // After shifting D_801241F4 right 8 times
        if (D_801241F4 == 0) {
            D_801241F0 = *D_801241EC++;
            D_801241F4 = 128; //1000 0000 in binary.
        }
        if (D_801241F0 & D_801241F4) {
            ret |= var_v0;
        }
        var_v0 >>= 1;
        D_801241F4 >>= 1;
        arg0--;
    }

    return ret;
}

// arg0 is the number of bits we care about
// arg1 is the bit being looked for.
void func_80072E28(s32 arg0, u32 arg1) {
    u32 var_v0;

    if (arg0 > 0) {
        var_v0 = 1 << (arg0 - 1);
        while (arg0 != 0 ) {
            if (D_801241F4 == 0) {
                *D_801241EC++ = D_801241F0;
                D_801241F0 = 0;
                D_801241F4 = 128; //Reset the byte counter, so we can shift 8 times before coming back here.
            }
            if (arg1 & var_v0) {
                D_801241F0 |= D_801241F4;
            }
            var_v0 >>= 1;
            D_801241F4 >>= 1;
            arg0--;
        }
        *D_801241EC = D_801241F0;
    }
}

void populate_settings_from_save_data(Settings *settings, u8 *saveData) {
    s32 i;
    s32 levelCount;
    s32 worldCount;
    s32 temp_v0;
    s32 var_s1;
    s16 var_a0;
    u8 temp_v1;

    clear_game_progress(settings);
    get_number_of_levels_and_worlds(&levelCount, &worldCount);
    D_801241EC = saveData;
    D_801241F0 = D_801241F4 = 0;
    var_a0 = func_80072C54(0x10) - 5;
    for (i = 2; i < 40; i++) { var_a0 -= saveData[i]; } // Must be one line
    if (var_a0 == 0) {
        for (i = 0, var_s1 = 0; i < levelCount; i++) {
            temp_v0 = get_map_race_type(i);
            if ((temp_v0 == 0) || (temp_v0 & 0x40) || (temp_v0 == 8)) {
                temp_v1 = func_80072C54(2);
                if (temp_v1 > 0) {
                    // Set Map Visited
                    settings->courseFlagsPtr[i] |= RACE_VISITED;
                }
                if (temp_v1 >= 2) {
                    // Set Map Completed
                    settings->courseFlagsPtr[i] |= RACE_CLEARED;
                }
                if (temp_v1 >= 3) {
                    // Set Map Silver Coin Challenge Completed
                    settings->courseFlagsPtr[i] |= RACE_CLEARED_SILVER_COINS;
                }
                var_s1 += 2;
            }
        }
        func_80072C54(0x44 - var_s1);
        settings->tajFlags = func_80072C54(6);
        settings->trophies = func_80072C54(0xA);
        settings->bosses = func_80072C54(0xC);
        for (i = 0; i < worldCount; i++) {
            settings->balloonsPtr[i] = func_80072C54(7);
        }
        settings->ttAmulet = func_80072C54(3);
        settings->wizpigAmulet = func_80072C54(3);
        for (i = 0; i < worldCount; i++) {
            settings->courseFlagsPtr[get_hub_area_id(i)] |= func_80072C54(16) << 16;
        }
        settings->keys = func_80072C54(8);
        settings->cutsceneFlags = func_80072C54(0x20);
        settings->filename = func_80072C54(0x10);
        func_80072C54(8);
        settings->newGame = FALSE;
    }
}

void func_800732E8(Settings *settings, u8 *saveData) {
    s16 var_v0;
    s8 temp_v0;
    u8 courseStatus;
    s32 levelCount;
    s32 worldCount;
    s32 i;
    s32 var_s0;

    get_number_of_levels_and_worlds(&levelCount, &worldCount);
    D_801241EC = saveData;
    D_801241F0 = 0;
    D_801241F4 = 128;
    func_80072E28(16, 0);
    for (i = 0, var_s0 = 0; i < levelCount; i++) {
        temp_v0 = get_map_race_type(i);
         if ((temp_v0 == 0) || (temp_v0 & 0x40) || (temp_v0 == 8)) {
            courseStatus = 0;
            // Map visited
            if (settings->courseFlagsPtr[i] & RACE_VISITED) {
                courseStatus = 1;
            }
            // Map completed
            if (settings->courseFlagsPtr[i] & RACE_CLEARED) {
                courseStatus++;
            }
            // Map Silver coin challenge completed
            if (settings->courseFlagsPtr[i] & RACE_CLEARED_SILVER_COINS) {
                courseStatus++;
            }
            func_80072E28(2, courseStatus);
            var_s0 += 2;
        }
    }
    func_80072E28(68 - var_s0, 0);
    func_80072E28(6, settings->tajFlags);
    func_80072E28(10, settings->trophies);
    func_80072E28(12, settings->bosses);
    for (i = 0; i < worldCount; i++) {
        func_80072E28(7, settings->balloonsPtr[i]);
    }
    func_80072E28(3, settings->ttAmulet);
    func_80072E28(3, settings->wizpigAmulet);
    for (i = 0; i < worldCount; i++) {
        func_80072E28(16, (settings->courseFlagsPtr[get_hub_area_id(i)] >> 16) & 0xFFFF);
    }
    func_80072E28(8, settings->keys);
    func_80072E28(32, settings->cutsceneFlags);
    func_80072E28(16, settings->filename);
    func_80072E28(8, 0);
    for (i = 2, var_v0 = 5; i < 40; i++) {
        var_v0 += saveData[i];
    }
    D_801241EC = saveData;
    D_801241F0 = 0;
    D_801241F4 = 128;
    func_80072E28(16, var_v0);
}

//arg1 is eepromData, from read_eeprom_data
//arg2 seems to be a flag for either lap times or course initials?
void func_80073588(Settings *settings, u8 *saveData, u8 arg2) {
    s16 availableVehicles;
    s32 levelCount;
    s32 worldCount;
    s32 i;
    s16 sum;

    clear_lap_records(settings, arg2);
    get_number_of_levels_and_worlds(&levelCount, &worldCount);

    if (arg2 & 1) {
        D_801241EC = saveData;
        D_801241F0 = 0;
        D_801241F4 = 0;
        for (i = 2, sum = 5; i < 192; i++) {
            sum += D_801241EC[i];
        }
        sum -= func_80072C54(16);
        if (sum == 0) {
            for (i = 0; i < levelCount; i++) {
                if (get_map_race_type(i) == 0) {
                    availableVehicles = get_map_available_vehicles(i);
                    // Car Available
                    if (availableVehicles & 1) {
                        settings->flapTimesPtr[0][i] = func_80072C54(16);
                        settings->flapInitialsPtr[0][i] = func_80072C54(16);
                    }
                    // Hovercraft Available
                    if (availableVehicles & 2) {
                        settings->flapTimesPtr[1][i] = func_80072C54(16);
                        settings->flapInitialsPtr[1][i] = func_80072C54(16);
                    }
                    // Plane Available
                    if (availableVehicles & 4) {
                        settings->flapTimesPtr[2][i] = func_80072C54(16);
                        settings->flapInitialsPtr[2][i] = func_80072C54(16);
                    }
                }
            }
        }
    }
    if (arg2 & 2) {
        D_801241EC = saveData + 192;
        D_801241F0 = 0;
        D_801241F4 = 0;
        for (i = 2, sum = 5; i < 192; i++) {
            sum += D_801241EC[i];
        }
        sum -= func_80072C54(16);
        if (sum == 0) {
            for (i = 0; i < levelCount; i++) {
                if (get_map_race_type(i) == 0) {
                    availableVehicles = get_map_available_vehicles(i);
                    // Car Available
                    if (availableVehicles & 1) {
                        settings->courseTimesPtr[0][i] = func_80072C54(16);
                        settings->courseInitialsPtr[0][i] = func_80072C54(16);
                    }
                    // Hovercraft Available
                    if (availableVehicles & 2) {
                        settings->courseTimesPtr[1][i] = func_80072C54(16);
                        settings->courseInitialsPtr[1][i] = func_80072C54(16);
                    }
                    // Plane Available
                    if (availableVehicles & 4) {
                        settings->courseTimesPtr[2][i] = func_80072C54(16);
                        settings->courseInitialsPtr[2][i] = func_80072C54(16);
                    }
                }
            }
        }
    }
}

void func_800738A4(Settings *settings, u8 *saveData) {
    s16 availableVehicles;
    s32 levelCount;
    s32 worldCount;
    s32 i;
    s32 vehicleCount;
    s16 sum;

    get_number_of_levels_and_worlds(&levelCount, &worldCount);
    D_801241EC = saveData;
    D_801241F0 = 0;
    D_801241F4 = 128;
    func_80072E28(16, 0);
    for (vehicleCount = 0, i = 0; i < levelCount; i++) {
        if (get_map_race_type(i) == 0) {
            availableVehicles = get_map_available_vehicles(i);
            // Car Available
            if (availableVehicles & 1) {
                func_80072E28(16, settings->flapTimesPtr[0][i]);
                func_80072E28(16, settings->flapInitialsPtr[0][i]);
                vehicleCount++;
            }
            // Hovercraft Available
            if (availableVehicles & 2) {
                func_80072E28(16, settings->flapTimesPtr[1][i]);
                func_80072E28(16, settings->flapInitialsPtr[1][i]);
                vehicleCount++;
            }
            // Plane Available
            if (availableVehicles & 4) {
                func_80072E28(16, settings->flapTimesPtr[2][i]);
                func_80072E28(16, settings->flapInitialsPtr[2][i]);
                vehicleCount++;
            }
            if (vehicleCount >= 48) {
                vehicleCount = 0; // Fakematch
                break;
            }
        }
    }

    if (vehicleCount) { } // Fakematch

    D_801241EC = saveData;
    D_801241F0 = 0;
    D_801241F4 = 128;
    for (i = 2, sum = 5; i < 192; i++) {
        sum += D_801241EC[i];
    }
    func_80072E28(16, sum);
    D_801241EC = saveData + 192;
    D_801241F0 = 0;
    D_801241F4 = 128;
    func_80072E28(16, 0);
    for (i = 0; i < levelCount; i++) {
        if (get_map_race_type(i) == 0) {
            availableVehicles = get_map_available_vehicles(i);
            // Car Available
            if (availableVehicles & 1) {
                func_80072E28(16, settings->courseTimesPtr[0][i]);
                func_80072E28(16, settings->courseInitialsPtr[0][i]);
            }
            // Hovercraft Available
            if (availableVehicles & 2) {
                func_80072E28(16, settings->courseTimesPtr[1][i]);
                func_80072E28(16, settings->courseInitialsPtr[1][i]);
            }
            // Plane Available
            if (availableVehicles & 4) {
                func_80072E28(16, settings->courseTimesPtr[2][i]);
                func_80072E28(16, settings->courseInitialsPtr[2][i]);
            }
        }
    }
    D_801241EC = saveData + 192;
    D_801241F0 = 0;
    D_801241F4 = 128;
    for (i = 2, sum = 5; i < 192; i++) {
        sum += D_801241EC[i];
    }
    func_80072E28(16, sum);
}

s32 get_game_data_file_size(void) {
    return 256;
}

s32 get_time_data_file_size(void) {
    return 512;
}

SIDeviceStatus get_file_extension(s32 controllerIndex, s32 fileType, char *fileExt) {
    #define BLANK_EXT_CHAR ' '
    char *fileNames[16];
    char *fileExtensions[16];
    u8 fileTypes[16];
    u32 fileSizes[16];
    s32 var_s1;
    s32 fileNum;
    char fileExtChar;
    SIDeviceStatus ret;

    fileExtChar = BLANK_EXT_CHAR;
    var_s1 = 0;
    ret = get_controller_pak_file_list(controllerIndex, 16, fileNames, fileExtensions, fileSizes, fileTypes);
    if (ret == CONTROLLER_PAK_GOOD) {
        for (fileNum = 0; fileNum < 16; fileNum++) {
            if (fileNames[fileNum] == NULL) {
                continue;
            }
            if (fileType == SAVE_FILE_TYPE_GAME_DATA) {
                if((bcmp((u8 *) fileNames[fileNum], (char *) sDKRacingAdv1, strlen((char *) sDKRacingAdv2)) != 0)) {
                    continue;
                }
            } else if((bcmp((u8 *) fileNames[fileNum], (char *) sDKRacingTimes1, strlen((char *) sDKRacingTimes2)) != 0))  {
                continue;
            }

            if (fileExtChar < fileExtensions[fileNum][0]) {
                fileExtChar = fileExtensions[fileNum][0];
            }
            var_s1 |= (1 << (fileExtensions[fileNum][0] + (BLANK_EXT_CHAR - 1)));
        }
        if (fileExtChar == BLANK_EXT_CHAR) {
            fileExtChar = 'A';
        } else if (fileExtChar == 'Z') {
            for (fileExtChar = 'A'; fileExtChar <= 'Z'; var_s1 >>= 1, fileExtChar++) {
                if (!(var_s1 & 1)) {
                    break;
                }
            }
        } else {
            fileExtChar++;
        }
        // Even though file extensions are technically 4 characters, only the first is used.
        // So this will set the extension to that character and then a null terminator.
        fileExt[0] = fileExtChar;
        fileExt[1] = '\0';
    }
    return ret;
}

//Read DKRACING-ADV data into settings?
s32 read_game_data_from_controller_pak(s32 controllerIndex, char *fileExt, Settings *settings) {
    s32 *alloc;
    s32 ret;
    s32 fileNumber;
    s32 fileSize;

    //Initialize controller pak
    ret = get_si_device_status(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | ret;
    }
    ret = get_file_number(controllerIndex, (char *) sDKRacingAdv3, fileExt, &fileNumber);
    if (ret == CONTROLLER_PAK_GOOD) {
        ret = get_file_size(controllerIndex, fileNumber, &fileSize);
        if (fileSize == 0) {
            ret = CONTROLLER_PAK_BAD_DATA;
        }
        if (ret == CONTROLLER_PAK_GOOD) {
            alloc = allocate_from_main_pool_safe(fileSize, COLOUR_TAG_BLACK);
            ret = read_data_from_controller_pak(controllerIndex, fileNumber, (u8 *)alloc, fileSize);

            if (ret == CONTROLLER_PAK_GOOD) {
                if (*alloc == GAMD) {
                    populate_settings_from_save_data(settings, (u8 *) (alloc + 1));
                    if (settings->newGame) {
                        ret = CONTROLLER_PAK_CHANGED;
                    }
                }
                else {
                    ret = CONTROLLER_PAK_BAD_DATA;
                }
            }

            free_from_memory_pool(alloc);
        }
    }

    start_reading_controller_data(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        ret |= (controllerIndex << 30);
    }
    return ret;
}

s32 write_game_data_to_controller_pak(s32 controllerIndex, Settings *arg1) {
    UNUSED s32 pad;
    char *fileExt;
    u8 *gameData; //Probably a struct where the first s32 is GAMD
    s32 ret;
    s32 fileSize;

    fileSize = get_game_data_file_size(); // 256 bytes
    gameData = allocate_from_main_pool_safe(fileSize, COLOUR_TAG_WHITE);
    *((s32 *)gameData) = GAMD;
    func_800732E8(arg1, gameData + 4);
    ret = get_file_extension(controllerIndex, 3, (char *)&fileExt);
    if (ret == CONTROLLER_PAK_GOOD) {
        ret = write_controller_pak_file(controllerIndex, -1, (char *) sDKRacingAdv4, (char *) &fileExt, gameData, fileSize);
    }
    free_from_memory_pool(gameData);
    if (ret != CONTROLLER_PAK_GOOD) {
        ret |= (controllerIndex << 30);
    }
    return ret;
}

//Read time data from controller pak into settings
s32 read_time_data_from_controller_pak(s32 controllerIndex, char *fileExt, Settings *settings) {
    s32 *cpakData;
    s32 status;
    s32 fileNumber;
    s32 fileSize;

    status = get_si_device_status(controllerIndex);
    if (status != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | status;
    }

    status = get_file_number(controllerIndex, (char *) sDKRacingTimes3, fileExt, &fileNumber);
    if (status == CONTROLLER_PAK_GOOD) {
        status = get_file_size(controllerIndex, fileNumber, &fileSize);
        if (fileSize == 0) {
            status = CONTROLLER_PAK_BAD_DATA;
        }

        if (status == CONTROLLER_PAK_GOOD) {
            cpakData = allocate_from_main_pool_safe(fileSize, COLOUR_TAG_BLACK);

            status = read_data_from_controller_pak(controllerIndex, fileNumber, (u8 *)cpakData, fileSize);
            if (status == CONTROLLER_PAK_GOOD) {
                if (*cpakData == TIMD) {
                    func_80073588(settings, (u8 *) (cpakData + 1), SAVE_DATA_FLAG_READ_FLAP_TIMES | SAVE_DATA_FLAG_READ_COURSE_TIMES);
                } else {
                    status = CONTROLLER_PAK_BAD_DATA;
                }
            }

            free_from_memory_pool(cpakData);
        }
    }

    start_reading_controller_data(controllerIndex);
    if (status != CONTROLLER_PAK_GOOD) {
        status |= (controllerIndex << 30);
    }

    return status;
}

s32 write_time_data_to_controller_pak(s32 controllerIndex, Settings *arg1) {
    u8 *timeData; //Should probably be a struct or maybe an array?
    s32 ret;
    s32 fileSize;
    UNUSED s32 pad;
    char *fileExt;

    fileSize = get_time_data_file_size(); // 512 bytes
    timeData = allocate_from_main_pool_safe(fileSize, COLOUR_TAG_WHITE);
    *((s32 *)timeData) = TIMD;
    func_800738A4(arg1, timeData + 4);
    ret = get_file_extension(controllerIndex, 4, (char *)&fileExt);
    if (ret == CONTROLLER_PAK_GOOD) {
        ret = write_controller_pak_file(controllerIndex, -1, (char *) sDKRacingTimes4, (char *) &fileExt, timeData, fileSize);
    }
    free_from_memory_pool(timeData);
    if (ret != CONTROLLER_PAK_GOOD) {
        ret |= (controllerIndex << 30);
    }
    return ret;
}

// Returns TRUE / FALSE for whether a given save file is a new game. Also populates the settings object.
s32 read_save_file(s32 saveFileNum, Settings *settings) {
    s32 startingAddress;
    u64 *saveData;
    s32 address;
    s32 blocks;
    s32 block;
    s32 ret;

    if (osEepromProbe(get_si_mesg_queue()) == 0) {
        return -1;
    }
    switch(saveFileNum) {
        case 0:
            startingAddress = 0;
            break;
        case 1:
            startingAddress = 5;
            break;
        case 2:
            startingAddress = 10;
            break;
        default:
            startingAddress = 10;
            break;
    }
    blocks = 5;
    saveData = allocate_from_main_pool_safe(blocks * sizeof(u64), COLOUR_TAG_WHITE);
    for (block = 0, address = startingAddress; block < blocks; block++, address++) {
        osEepromRead(get_si_mesg_queue(), address, (u8 *)&saveData[block]);
    }
    populate_settings_from_save_data(settings, (u8 *) saveData);
    free_from_memory_pool(saveData);
    ret = settings->newGame;
    if (settings->newGame) {
        erase_save_file(saveFileNum, settings);
        ret = settings->newGame;
    }
    return ret;
}

void erase_save_file(s32 saveFileNum, Settings *settings) {
    s32 startingAddress;
    u8 *saveData;
    u64 *alloc;
    s32 blockSize;
    s32 levelCount;
    s32 worldCount;
    s32 address;
    s32 i;

    if (osEepromProbe(get_si_mesg_queue()) != 0) {
        get_number_of_levels_and_worlds(&levelCount, &worldCount);
        for (i = 0; i < levelCount; i++) {
            settings->courseFlagsPtr[i] = 0;
        }
        for (i = 0; i < worldCount; i++) {
            settings->balloonsPtr[i] = 0;
        }
        settings->trophies = 0;
        settings->bosses = 0;
        settings->tajFlags = 0;
        settings->cutsceneFlags = 0;
        settings->newGame = TRUE;
        switch(saveFileNum) {
            case 0:
                startingAddress = 0;
                break;
            case 1:
                startingAddress = 5;
                break;
            case 2:
                startingAddress = 10;
                break;
            default:
                startingAddress = 10;
                break;
        }
        blockSize = 5;
        alloc = allocate_from_main_pool_safe(blockSize * sizeof(u64), COLOUR_TAG_WHITE);
        saveData = (u8 *)alloc;
        // Blank out the data before writing it.
        for (i = 0; i < blockSize * (s32)sizeof(u64); i++) { saveData[i] = 0xFF; } // Must be one line
        if (!is_reset_pressed()) {
            for (i = 0, address = startingAddress; i < blockSize; i++, address++) {
                osEepromWrite(get_si_mesg_queue(), address, (u8 *)&alloc[i]);
            }
        }
        free_from_memory_pool(alloc);
    }
}

/**
 * Writes Eeprom in 5 block chunks of data starting at either 0x0, 0x5, or 0xA
 * In Save File:
 * 0x00 - 0x27 Save 1
 * 0x28 - 0x4F Save 2
 * 0x50 - 0x77 Save 3
 */
s32 write_save_data(s32 saveFileNum, Settings *settings) {
    s32 startingAddress;
    u64 *alloc;
    s32 address;
    s32 blocks;
    s32 i;

    if (osEepromProbe(get_si_mesg_queue()) == 0) {
        return -1;
    }

    switch(saveFileNum) {
        case 0:
            startingAddress = 0;
            break;
        case 1:
            startingAddress = 5;
            break;
        case 2:
            startingAddress = 10;
            break;
        default:
            startingAddress = 10;
            break;
    }

    blocks = 5;
    alloc = allocate_from_main_pool_safe(blocks * sizeof(u64), COLOUR_TAG_WHITE);
    func_800732E8(settings, (u8 *)alloc);

    if (!is_reset_pressed()) {
        for (i = 0, address = startingAddress; i < blocks; i++, address++) {
            osEepromWrite(get_si_mesg_queue(), address, (u8 *)&alloc[i]);
        }
    }

    free_from_memory_pool(alloc);

    return 0;
}

/**
 * Read Eeprom Data for addresses 0x10 - 0x39
 * arg1 is a flag
 * arg1 is descended from (gSaveDataFlags & 3) so the first 2 bits of that value.
 * bit 1 is for 0x10 - 0x27 - SAVE_DATA_FLAG_READ_FLAP_TIMES
 * bit 2 is for 0x28 - 0x39 - SAVE_DATA_FLAG_READ_COURSE_TIMES
 */
s32 read_eeprom_data(Settings *settings, u8 flags) {
    u64 *alloc;
    s32 i;

    if (osEepromProbe(get_si_mesg_queue()) == 0) {
        return -1;
    }

    alloc = allocate_from_main_pool_safe(0x200, COLOUR_TAG_WHITE);

    if (flags & SAVE_DATA_FLAG_READ_FLAP_TIMES) {
        s32 blocks = 24;
        for (i = 0; i < blocks; i++) {
            osEepromRead(get_si_mesg_queue(), i + 0x10, (u8 *)&alloc[i]);
        }
        func_80073588(settings, (u8 *) alloc, SAVE_DATA_FLAG_READ_FLAP_TIMES);
    }

    if (flags & SAVE_DATA_FLAG_READ_COURSE_TIMES) {
        s32 blocks = 24;
        for (i = 0; i < blocks; i++) {
            osEepromRead(get_si_mesg_queue(), i + 0x28, (u8 *)(&alloc[24] + i));
        }
        func_80073588(settings, (u8 *) alloc, SAVE_DATA_FLAG_READ_COURSE_TIMES);
    }

    free_from_memory_pool(alloc);
    return 0;
}

/**
 * Write Eeprom Data for addresses 0x10 - 0x39
 * 0x80 - 0x1C8 in file
 * arg1 is a flag
 * arg1 is descended from gSaveDataFlags bits 4 and 5.
 * bit 1 is for 0x10 - 0x27 - SAVE_DATA_FLAG_READ_FLAP_TIMES
 * bit 2 is for 0x28 - 0x39 - SAVE_DATA_FLAG_READ_COURSE_TIMES
 */
s32 write_eeprom_data(Settings *settings, u8 flags) {
    u64 *alloc;
    s32 i;

    if (osEepromProbe(get_si_mesg_queue()) == 0) {
        return -1;
    }

    alloc = allocate_from_main_pool_safe(0x200, COLOUR_TAG_WHITE);

    func_800738A4(settings, (u8 *)alloc);

    if (flags & SAVE_DATA_FLAG_READ_FLAP_TIMES) {
        s32 size = 24;
        if (1){} //Fake Match
        if (!is_reset_pressed()) {
            for (i = 0; i != size; i++) {
                osEepromWrite(get_si_mesg_queue(), i + 16, (u8 *)&alloc[i]);
            }
        }
    }

    if (flags & SAVE_DATA_FLAG_READ_COURSE_TIMES) {
        s32 size = 24;
        if (!is_reset_pressed()) {
            for (i = 0; i != size; i++) {
                osEepromWrite(get_si_mesg_queue(), i + 40, (u8 *)(&alloc[24] + i));
            }
        }
    }

    free_from_memory_pool(alloc);
    return 0;
}

/**
 * Calculates a checksum for the game settings, and compares
 * against this to validate the data on load.
 */
s32 calculate_eeprom_settings_checksum(u64 eepromSettings) {
    s32 ret;
    s32 i;

    ret = 5;
    for (i = 0; i <= 13; i++) {
        ret += (u16)(eepromSettings >> (i << 2)) & 0xF;
    }
    return ret;
}

/**
 * Reads eeprom address 0xF (15)
 * This contains the settings data, and global unlocks like characters
 * Address (0xF * sizeof(u64)) = 0x78 - 0x80 of the actual save data file
 */
s32 read_eeprom_settings(u64 *eepromSettings) {
    s32 temp;
    s32 sp20;

    if (osEepromProbe(get_si_mesg_queue()) == 0) {
        return -1;
    }

    osEepromRead(get_si_mesg_queue(), 0xF, (u8 *) eepromSettings);
    sp20 = calculate_eeprom_settings_checksum(*eepromSettings);
    temp =  *eepromSettings >> 56;
    if (sp20 != temp) {
        //bit 24 = Unknown
        //bit 25 = Seems to be a flag for whether subtitles are enabled or not.
        *eepromSettings = 0x3000000; //Sets bits 24 and 25 high
        *eepromSettings <<= 8;
        *eepromSettings >>= 8;
        *eepromSettings |= (u64)calculate_eeprom_settings_checksum(*eepromSettings) << 56;
    }

    return 1;
}

/**
 * Writes eeprom address 0xF (15)
 * This contains the settings data, and global unlocks like characters
 * Address (0xF * sizeof(u64)) = 0x78 - 0x80 of the actual save data file
 */
s32 write_eeprom_settings(u64 *eepromSettings) {
    if (osEepromProbe(get_si_mesg_queue()) == 0) {
        return -1;
    }
    *eepromSettings <<= 8;
    *eepromSettings >>= 8;
    *eepromSettings |= (s64)(calculate_eeprom_settings_checksum(*eepromSettings)) << 56;
    if (is_reset_pressed() == 0) {
        osEepromWrite(get_si_mesg_queue(), 0xF, (u8 *) eepromSettings);
    }
    return 1;
}

s16 calculate_ghost_header_checksum(GhostHeader *ghostHeader) {
    s16 i;
    s16 len;
    s16 sum;

    sum = 0;
    len = (s16)(ghostHeader->nodeCount * sizeof(GhostDataFrame)) + sizeof(GhostHeader);
    for (i = 2; i < len; i++) {
        sum += ((u8 *)ghostHeader)[i];
    }
    return sum;
}

void func_80074AA8(GhostHeader *ghostHeader, s16 characterID, s16 time, s16 nodeCount, u8 *dest) {
    ghostHeader->checksum = 0;
    ghostHeader->characterID = characterID;
    ghostHeader->unk3 = 0;
    ghostHeader->time = time;
    ghostHeader->nodeCount = nodeCount;
    bcopy(dest, (u8 *)ghostHeader + 8, nodeCount * sizeof(GhostDataFrame));
    ghostHeader->checksum = calculate_ghost_header_checksum(ghostHeader);
}

//Seems to only be called when used as an argument for func_800860A8. Effectively just returns 0x6700
s32 get_ghost_data_file_size(void) {
    int x = 0x1100;
    return (&x)[0] * 6 + 0x100;
}

#ifdef NON_EQUIVALENT
s32 func_80074B34(s32 controllerIndex, s16 levelId, s16 vehicleId, s16 *ghostCharacterId, s16 *ghostTime, s16 *ghostNodeCount, GhostHeader *ghostData) {
    #define GHSS_FILE_SIZE 0x100
    u8 *fileData;
    s32 fileNumber;
    s32 fileOffset;
    s32 fileSize;
    s32 bytesFree;
    s32 notesFree;
    s32 ret;
    s32 retTemp;
    s32 var_v1;
    u8 *temp_a1;
    GhostHeader *ghostHeader;
    u8 *var_v0_2;
    u8 *temp_v0_4;

    fileOffset = 0;
    ret = get_si_device_status(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return ret;
    }
    if (ghostCharacterId != NULL) {
        *ghostTime = -1;
        *ghostCharacterId = -1;
    }
    ret = get_file_number(controllerIndex, (char *) sDKRacingGhosts, (char *) sDKRacingGhostFileExt, &fileNumber);
    if (ret == CONTROLLER_PAK_GOOD) {
        fileData = allocate_from_main_pool_safe(GHSS_FILE_SIZE, COLOUR_TAG_BLACK);
        if (!(pfs[controllerIndex].status & PFS_INITIALIZED)) {
            osPfsInit(sControllerMesgQueue, &pfs[controllerIndex], controllerIndex);
        }
        ret = read_data_from_controller_pak(controllerIndex, fileNumber, fileData, GHSS_FILE_SIZE);
        if (ret == CONTROLLER_PAK_GOOD) {
            temp_a1 = fileData + 4;
            if (fileData[0] == GHSS) {
                var_v1 = 0;
                var_v0_2 = temp_a1;
loop_10:
                var_v1 += 4;
                if ((levelId == var_v0_2[0]) && (vehicleId == var_v0_2[1])) {
                    fileOffset = var_v0_2[2];
                    fileSize = var_v0_2[6] - var_v0_2[2];
                } else {
                    var_v0_2 += 4;
                    if (var_v1 < 24) {
                        goto loop_10;
                    }
                }
                if (fileOffset == 0) {
                    ret = CONTROLLER_PAK_UNK6;
                    if (fileData[4] == 0xFF) {
                        ret = CONTROLLER_PAK_UNK8;
                    }
                    temp_v0_4 = temp_a1 + (2 * 4);
                    if (fileData[4] == 0xFF) {
                        ret = CONTROLLER_PAK_UNK8;
                    }
                    if (temp_v0_4[0] == 0xFF) {
                        ret = CONTROLLER_PAK_UNK8;
                    }
                    if (temp_v0_4[4] == 0xFF) {
                        ret = CONTROLLER_PAK_UNK8;
                    }
                    if (temp_v0_4[8] == 0xFF) {
                        ret = CONTROLLER_PAK_UNK8;
                    }
                    if (temp_v0_4[12] == 0xFF) {
                        ret = CONTROLLER_PAK_UNK8;
                    }
                }
            } else {
                ret = CONTROLLER_PAK_BAD_DATA;
            }
        }
        free_from_memory_pool(fileData);
        if (fileOffset != 0) {
            if (ghostCharacterId != NULL) {
                ghostHeader = allocate_from_main_pool_safe(fileSize + GHSS_FILE_SIZE, COLOUR_TAG_BLACK);
                retTemp = CONTROLLER_PAK_BAD_DATA;
                if (osPfsReadWriteFile(&pfs[controllerIndex], fileNumber, PFS_READ, fileOffset, fileSize, (u8 *) ghostHeader) == 0) {
                    if (calculate_ghost_header_checksum(ghostHeader) == ghostHeader->checksum) {
                        *ghostCharacterId = ghostHeader->characterID;
                        *ghostTime = ghostHeader->time;
                        *ghostNodeCount = ghostHeader->nodeCount;
                        bcopy(ghostHeader + 8, ghostData, *ghostNodeCount * sizeof(GhostNode));
                        retTemp = CONTROLLER_PAK_GOOD;
                    } else {
                        retTemp = CONTROLLER_PAK_BAD_DATA;
                    }
                }
                free_from_memory_pool(ghostHeader);
                ret = retTemp;
            }
        }
        if ((fileOffset != 0) && (ghostCharacterId == NULL)) {
            ret = CONTROLLER_PAK_GOOD;
        }
    }
    start_reading_controller_data(controllerIndex);
    if (ret == CONTROLLER_PAK_CHANGED) {
        if (get_free_space(controllerIndex, &bytesFree, &notesFree) == CONTROLLER_PAK_GOOD) {
            if ((bytesFree < get_ghost_data_file_size()) || ((notesFree == 0))) {
                return CONTROLLER_PAK_FULL;
            }
            /* Duplicate return node #48. Try simplifying control flow for better match */
            return ret;
        }
        return CONTROLLER_PAK_BAD_DATA;
    }
    return ret;
}
#else
GLOBAL_ASM("asm/non_matchings/save_data/func_80074B34.s")
#endif

typedef struct GhostHeaderAltUnk0 {
  u8 levelID;
  u8 vehicleID; // 0 = Car, 1 = Hovercraft, 2 = Plane
} GhostHeaderAltUnk0;

/* Size: 4 bytes */
typedef struct GhostHeaderAlt {
    union {
      GhostHeaderAltUnk0 unk0;
      s16 checksum;
    };
    union {
      struct {
        u8 characterID; // 9 = T.T.
        u8 unk3;
      };
      s16 unk2;
    };
} GhostHeaderAlt;

typedef struct GhostDataData {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    u8 padB[10];
    s16 unk16;
    s16 unk18;
    s16 unk1A;
} GhostDataData;

typedef struct GhostData {
    /* 0x00 */ s32 headerId;
    union {
    /* 0x04 */ GhostHeader *ghostHeader;
    /* 0x04 */ GhostDataData *ghostData;
    };
    /* 0x08 */ u8 unk8_pad[0x14];
    /* 0x1C */ u8 unk1C;
    /* 0x1E */ s16 unk1E;
} GhostData;

GLOBAL_ASM("asm/non_matchings/save_data/func_80074EB8.s")

#ifdef NON_EQUIVALENT
s32 func_80075000(s32 controllerIndex, s16 levelId, s16 vehicleId, s16 ghostCharacterId, s16 ghostTime, s16 ghostNodeCount, GhostHeader *ghostData) {
    GhostHeaderAlt *sp70;
    s32 sp58;
    s32 fileSize;
    s32 fileNumber;
    s32 ret;
    s32 ghostIndex;
    s32 i;
    GhostHeader *ghostFileData;
    GhostHeaderAlt *ghostFileDataAlt;
    GhostData *fileData;
    GhostData *fileDataToWrite;

    ret = get_si_device_status(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return ret;
    }
    ret = get_file_number(controllerIndex, "DKRACING-GHOSTS", "", &fileNumber);
    if (ret == CONTROLLER_PAK_CHANGED) {
        start_reading_controller_data(controllerIndex);
        return func_80074EB8(controllerIndex, levelId, vehicleId, ghostCharacterId, ghostTime, ghostNodeCount, &ghostData->unk0.levelID);
    }
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return ret;
    } else {
        ret = get_file_size(controllerIndex, fileNumber, &fileSize);
        if (ret != CONTROLLER_PAK_GOOD) {
            start_reading_controller_data(controllerIndex);
            return ret;
        } else {
            fileData = allocate_from_main_pool_safe(fileSize + 0x100, COLOUR_TAG_BLACK);
            ret = read_data_from_controller_pak(controllerIndex, fileNumber, fileData, fileSize);
            start_reading_controller_data(controllerIndex);
            if (ret != CONTROLLER_PAK_GOOD) {
                free_from_memory_pool(fileData);
            } else {
                ret = CONTROLLER_PAK_BAD_DATA;
                if (fileData->headerId == GHSS) {
                    ghostFileData = &fileData->ghostHeader;
                    ghostFileDataAlt = (GhostHeaderAlt *) &fileData->ghostHeader;

                    for (i = 0, ghostIndex = -1; i < 6; i++) {
                        if (levelId == ghostFileDataAlt[i].unk0.levelID && vehicleId == ghostFileDataAlt[i].unk0.vehicleID) {
                            ghostIndex = i;
                            break;
                        }
                    }

                    if ((ghostIndex != -1) && (fileData[ghostFileDataAlt[ghostIndex].unk2].ghostHeader->time < ghostTime)) {
                        ghostIndex = -2;
                    }

                    if (ghostIndex == -1) {
                        ghostFileDataAlt = (GhostHeaderAlt *) &fileData->ghostHeader;
                        for (i = 0; i < 6; i++) {
                            if (ghostFileDataAlt[i].unk0.levelID == 0xFF) {
                                ghostIndex = i;
                                break;
                            }
                        }
                    }
                    if (ghostIndex == -2) {
                        ret = CONTROLLER_PAK_GOOD;
                    } else if (ghostIndex == -1) {
                        ret = CONTROLLER_PAK_UNK6;
                    } else {
                        sp58 = (0x1100 - ghostFileData[ghostIndex].nodeCount) + ghostFileData[ghostIndex].unk2;
                        fileDataToWrite = allocate_from_main_pool_safe(fileSize + 0x100, COLOUR_TAG_BLACK);
                        fileDataToWrite->headerId = GHSS;
                        sp70 = &fileDataToWrite->ghostHeader;
                        fileDataToWrite->unk1C = 0xFF;
                        fileDataToWrite->unk1E = (s16) (ghostFileData[3].unk2 + sp58);
                        for (i = 0; i < 6; i++) {
                            sp70[i].unk0.levelID = ghostFileData[i].unk0.levelID;
                            sp70[i].unk0.vehicleID = ghostFileData[i].unk0.vehicleID;
                            if (ghostIndex >= i) {
                                sp70[i].unk2 = ghostFileData[i].unk2;
                            } else {
                                sp70[i].unk2 = (ghostFileData[i].unk2 + sp58);
                            }
                            bcopy(&fileData[ghostFileData[i].unk2], &fileDataToWrite[sp70[i].unk2], ghostFileData[i].nodeCount - ghostFileData[i].unk2);
                        }
                        func_80074AA8((GhostHeader *) &fileDataToWrite[sp70[ghostIndex].unk2], ghostCharacterId, ghostTime, ghostNodeCount, &ghostData->unk0.levelID);
                        sp70[ghostIndex].unk0.levelID = levelId;
                        sp70[ghostIndex].unk0.vehicleID = vehicleId;
                        ret = write_controller_pak_file(controllerIndex, fileNumber, "DKRACING-GHOSTS", "", fileDataToWrite, fileSize);
                        free_from_memory_pool(fileDataToWrite);
                    }
                }
                free_from_memory_pool(fileData);
            }
        }
    }
    return ret;
}
#else
GLOBAL_ASM("asm/non_matchings/save_data/func_80075000.s")
#endif



#ifdef NON_EQUIVALENT
//I give up. Ghost data structs have be beat for now.

s32 func_800753D8(s32 controllerIndex, s32 arg1) {
    GhostData *dataToWrite;
    s32 fileNumber;
    s32 fileLength;
    u8 *sp28;
    u8 *sp20;
    s16 temp_t9_2;
    s16 temp_t9_3;
    s32 temp_a3;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 var_at;
    s32 ret;
    s32 var_v1_4;
    GhostDataData *temp_t1;
    GhostData *fileData;
    GhostData *temp_v0_6;
    u8 *temp_v1;
    u8 temp_t2_2;
    u8 temp_t3;
    u8 temp_t7;
    u8 temp_t7_2;
    u8 temp_t8_3;
    u8 temp_t8_4;
    GhostDataData *temp_v0_5;
    u8 *temp_v0_8;
    GhostDataData *var_v0;
    u8 *var_v0_2;

    ret = get_si_device_status(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return ret;
    }
    ret = get_file_number(controllerIndex, "DKRACING-GHOSTS", "", &fileNumber);
    if (ret == CONTROLLER_PAK_GOOD) {
        ret = get_file_size(controllerIndex, fileNumber, &fileLength);
        if (ret != CONTROLLER_PAK_GOOD) {
            start_reading_controller_data(controllerIndex);
            return ret;
        }
        fileData = (GhostData *)allocate_from_main_pool_safe(fileLength + 0x100, COLOUR_TAG_BLACK);
        ret = read_data_from_controller_pak(controllerIndex, fileNumber, (u8 *)fileData, fileLength);
        start_reading_controller_data(controllerIndex);
        if (ret == CONTROLLER_PAK_GOOD) {
            ret = CONTROLLER_PAK_BAD_DATA;
            if (fileData->headerId == GHSS) {
                temp_t8 = arg1 * 4;
                temp_v0_5 = (GhostDataData *)&fileData[temp_t8];
                temp_a3 = temp_v0_5->unk6 - temp_v0_5->unkA;
                temp_v0_6 = (GhostData *)allocate_from_main_pool_safe(fileLength + 0x100, COLOUR_TAG_BLACK);
                temp_v1 = fileData->ghostHeader;
                dataToWrite = temp_v0_6;
                temp_t1 = &temp_v1[temp_t8];
                sp20 = temp_t1;
                sp28 = temp_v1;
                bcopy(fileData, temp_v0_6, temp_t1->unk2);
                if (arg1 != 5) {
                    bcopy(&fileData[temp_t1->unk6], &(&dataToWrite[temp_t1->unk6])[temp_a3], fileData->ghostData->unk1A - temp_t1->unk6);
                }
                var_v0 = &dataToWrite[arg1].ghostData;
                for (var_v1_4 = arg1; var_v1_4 < 6; var_v1_4++) {
                    var_v0[var_v1_4].unk2 = (var_v0[var_v1_4].unk6 + temp_a3);
                    var_v0[var_v1_4].unk18 = var_v0[var_v1_4].unk4;
                    var_v0[var_v1_4].unk1A = var_v0[var_v1_4].unk5;
                }
                dataToWrite->ghostData->unk1A = dataToWrite->ghostData->unk16;
                ret = write_controller_pak_file(controllerIndex, fileNumber, "DKRACING-GHOSTS", "", (u8 *) dataToWrite, fileLength);
            }
            free_from_memory_pool(dataToWrite);
        }
        free_from_memory_pool(fileData);
    } else {
        start_reading_controller_data(controllerIndex);
    }

    return ret;
}
#else
GLOBAL_ASM("asm/non_matchings/save_data/func_800753D8.s")
#endif

SIDeviceStatus func_800756D4(s32 controllerIndex, u8 *arg1, u8 *arg2, u8 *arg3, s16 *arg4) {
    s32 i;
    u8 *fileData;
    s32 ret; // sp64
    GhostHeaderAlt *var_s1;
    s32 fileNumber;
    s32 fileSize;
    u8 temp_v0_2;

    ret = get_si_device_status(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return ret;
    }
    for (i = 0; i < 6; i++) {
        arg1[i] = 0xFF;
        arg4[i] = 0;
        temp_v0_2 = arg4[i];
        arg3[i] = temp_v0_2;
        arg2[i] = temp_v0_2;
    }
    ret = get_file_number(controllerIndex, "DKRACING-GHOSTS", "", &fileNumber);
    if (ret == CONTROLLER_PAK_GOOD) {
        ret = get_file_size(controllerIndex, fileNumber, &fileSize);
        if (ret == CONTROLLER_PAK_GOOD) {
            fileData = allocate_from_main_pool_safe(fileSize + 0x100, COLOUR_TAG_BLACK);
            ret = read_data_from_controller_pak(controllerIndex, fileNumber, (u8 *)fileData, fileSize);
            if (ret == CONTROLLER_PAK_GOOD) {
                for (i = 0, var_s1 = (GhostHeaderAlt *) (&fileData[4]); i < 6; i++) {
                    if (var_s1[i].unk0.levelID != 0xFF) {
                        if (calculate_ghost_header_checksum((GhostHeader *) &fileData[var_s1[i].unk2]) != ((GhostHeaderAlt*)&fileData[var_s1[i].unk2])->checksum) {
                            ret = CONTROLLER_PAK_BAD_DATA;
                            break;
                        } else {
                            arg1[i] = var_s1[i].unk0.levelID;
                            arg2[i] = var_s1[i].unk0.vehicleID;
                            arg3[i] = fileData[var_s1[i].unk2+2];
                            arg4[i] = ((GhostHeaderAlt *) &fileData[var_s1[i].unk2] + 1)->checksum;
                        }
                    }
                }
            }
            free_from_memory_pool(fileData);
        }
    }
    start_reading_controller_data(controllerIndex);
    return ret;
}

/* Official name: packOpen */
SIDeviceStatus get_si_device_status(s32 controllerIndex) {
    OSMesg unusedMsg;
    s32 ret;
    s32 bytes_not_used;
    s32 i;

    if (sControllerMesgQueue->validCount == 0) {
        if (osMotorInit(sControllerMesgQueue,  &pfs[controllerIndex], controllerIndex) == 0) {
            return RUMBLE_PAK;
        }
    }

    //Couldn't get a for loop to match this
    i = 0;
    while (sControllerMesgQueue->validCount != 0 && i < 10) {
        osRecvMesg(sControllerMesgQueue, &unusedMsg, OS_MESG_NOBLOCK);
        i++;
    }

    for (i = 0; i <= 4; i++) {
        ret = osPfsFreeBlocks( &pfs[controllerIndex], &bytes_not_used);
        if (ret == PFS_ERR_INVALID) {
            ret = osPfsInit(sControllerMesgQueue,  &pfs[controllerIndex], controllerIndex);
        }
        if (ret == PFS_ERR_ID_FATAL) {
            if (osMotorInit(sControllerMesgQueue,  &pfs[controllerIndex], controllerIndex) == 0) {
                return RUMBLE_PAK;
            }
        }
        if (ret == PFS_ERR_NEW_PACK) {
            if ((osPfsInit(sControllerMesgQueue,  &pfs[controllerIndex], controllerIndex) == PFS_ERR_ID_FATAL)
                && (osMotorInit(sControllerMesgQueue,  &pfs[controllerIndex], controllerIndex) == 0)) {
                return RUMBLE_PAK;
            }
            return CONTROLLER_PAK_CHANGED;
        }
        if (ret == PFS_ERR_NOPACK || ret == PFS_ERR_DEVICE) {
            return NO_CONTROLLER_PAK;
        }
        if (ret == PFS_ERR_BAD_DATA) {
            return CONTROLLER_PAK_BAD_DATA;
        }
        if (ret == PFS_ERR_ID_FATAL) {
            return CONTROLLER_PAK_WITH_BAD_ID;
        }
        if (ret == PFS_ERR_INCONSISTENT) {
            return CONTROLLER_PAK_INCONSISTENT;
        }
        if (ret == 0) {
            return CONTROLLER_PAK_GOOD;
        }
    }

    return NO_CONTROLLER_PAK;
}

/* Official name: packClose */
s32 start_reading_controller_data(UNUSED s32 controllerIndex) {
    osContStartReadData(sControllerMesgQueue);
    return 0;
}

void init_controller_paks(void) {
    s32 controllerIndex;
    s32 ret;
    u8 controllerBit;
    u8 pakPattern;
    s8 maxControllers;

    sControllerMesgQueue = get_si_mesg_queue();
    sUnkMiscAsset19 = (s16 *)get_misc_asset(ASSET_MISC_19);
    D_801241E6 = D_801241E7 = 0xF;
    D_801241E4 = TRUE;
    gRumbleDetectionTimer = 0;
    D_800DE48C = 1;
    sControllerPaksPresent = sRumblePaksPresent = 0;

    //pakPattern will set the first 4 bits representing each controller
    //and it will be 1 if there's something attached.
    osPfsIsPlug(sControllerMesgQueue, &pakPattern);

    for (controllerIndex = 0, controllerBit = 1, maxControllers = MAXCONTROLLERS; (0, controllerIndex) != maxControllers; controllerIndex++, controllerBit <<= 1) {
        D_801241B8[controllerIndex].unk2 = 0;
        D_801241B8[controllerIndex].unk4 = -1;
        D_801241B8[controllerIndex].unk0 = -1;
        D_801241B8[controllerIndex].unk6 = D_801241B8[controllerIndex].unk2;

        //If something is plugged into the controller
        if (pakPattern & controllerBit) {
            ret = osPfsInit(sControllerMesgQueue, &pfs[controllerIndex], controllerIndex);
            if (ret == PFS_ERR_NEW_PACK) {
                ret = osPfsInit(sControllerMesgQueue, &pfs[controllerIndex], controllerIndex);
            }
            if (ret == 0) {
                //If we found a controller pak, set the bit that has one
                sControllerPaksPresent |= controllerBit;
            }
            else if (ret == PFS_ERR_ID_FATAL) {
                if (controllerIndex) { } // Fakematch
                ret = osMotorInit(sControllerMesgQueue, &pfs[controllerIndex], controllerIndex);
                if (ret == 0) {
                    //If we found a rumble pak, set the bit that has one
                    sRumblePaksPresent |= controllerBit;
                }
            }
        }
    }

    osContStartReadData(sControllerMesgQueue);
}

/* Official name: packIsPresent */
UNUSED SIDeviceStatus check_for_rumble_pak(s32 controllerIndex) {
    s32 ret;

    ret = get_si_device_status(controllerIndex);
    start_reading_controller_data(controllerIndex);

    if (ret == RUMBLE_PAK) {
        sRumblePaksPresent |= 1 << controllerIndex;
    }

    return ret;
}

//Inspects and repairs the Controller Pak's file system
/* Official name: packRepair */
SIDeviceStatus repair_controller_pak(s32 controllerIndex) {
    s32 ret;
    s32 status = get_si_device_status(controllerIndex);
    if (status == CONTROLLER_PAK_GOOD || status == CONTROLLER_PAK_INCONSISTENT) {
        status = osPfsChecker(&pfs[controllerIndex]);
        if (status == 0) {
            ret = CONTROLLER_PAK_GOOD;
        } else if (status == PFS_ERR_NEW_PACK) {
            ret = CONTROLLER_PAK_CHANGED;
        } else {
            ret = CONTROLLER_PAK_INCONSISTENT;
        }
    } else {
        ret = CONTROLLER_PAK_GOOD;
    }
    start_reading_controller_data(controllerIndex);
    return ret;
}

//Reformat Controller Pak
/* Official name: packFormat */
SIDeviceStatus reformat_controller_pak(s32 controllerIndex) {
    s32 ret;
    s32 status = get_si_device_status(controllerIndex);
    if (status == CONTROLLER_PAK_GOOD || status == CONTROLLER_PAK_INCONSISTENT || status == CONTROLLER_PAK_WITH_BAD_ID) {
        status = osPfsReFormat(&pfs[controllerIndex], sControllerMesgQueue, controllerIndex);
        if (status == 0) {
            ret = CONTROLLER_PAK_GOOD;
        } else if (status == PFS_ERR_NEW_PACK) {
            ret = CONTROLLER_PAK_CHANGED;
        } else {
            ret = CONTROLLER_PAK_INCONSISTENT;
        }
    } else {
        ret = CONTROLLER_PAK_GOOD;
    }
    start_reading_controller_data(controllerIndex);
    return ret;
}

/* Official Name: packDirectory */
s32 get_controller_pak_file_list(s32 controllerIndex, s32 maxNumOfFilesToGet, char **fileNames, char **fileExtensions, u32 *fileSizes, u8 *fileTypes) {
    OSPfsState state;
    s32 ret;
    s32 maxNumOfFilesOnCpak;
    s32 files_used;
    s8 *temp_D_800DE440;
    s32 i;
    u32 gameCode;

    ret = get_si_device_status(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | ret;
    }

    if (osPfsNumFiles(&pfs[controllerIndex], &maxNumOfFilesOnCpak, &files_used) != 0) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | CONTROLLER_PAK_BAD_DATA;
    }

    if (get_language() == LANGUAGE_JAPANESE) {
        gameCode = JPN_GAME_CODE;
    } else if (osTvType == TV_TYPE_PAL) {
        gameCode = PAL_GAME_CODE;
    } else {
        gameCode = NTSC_GAME_CODE;
    }
    
    if (maxNumOfFilesToGet < maxNumOfFilesOnCpak) {
        maxNumOfFilesOnCpak = maxNumOfFilesToGet;
    }
    
    if (D_800DE440 != NULL) {
        free_from_memory_pool(D_800DE440);
    }
    
    files_used = maxNumOfFilesOnCpak * 24;
    D_800DE440 = allocate_from_main_pool_safe(files_used, COLOUR_TAG_BLACK);
    bzero(D_800DE440, files_used);
    temp_D_800DE440 = D_800DE440;
    
    //TODO: There's probably an unidentified struct here
    for (i = 0; i < maxNumOfFilesOnCpak; i++) {
        fileNames[i] = (char *) temp_D_800DE440;
        temp_D_800DE440 += 0x12;
        fileExtensions[i] = (char *) temp_D_800DE440;
        fileSizes[i] = 0;
        fileTypes[i] = SAVE_FILE_TYPE_UNSET;
        temp_D_800DE440 += 6;
    }
    
    while (i < maxNumOfFilesToGet) {
        fileExtensions[i] = 0;
        fileNames[i] = 0;
        fileSizes[i] = 0;
        fileTypes[i] = SAVE_FILE_TYPE_UNSET;
        i++;
    }
    
    for (i = 0; i < maxNumOfFilesOnCpak; i++) {
        ret = osPfsFileState(&pfs[controllerIndex], i, &state);
        if (ret == PFS_ERR_INVALID) {
            fileNames[i] = 0;
            continue;
        }
        
        if (ret != 0) {
            start_reading_controller_data(controllerIndex);
            return CONTROLLER_PAK_BAD_DATA;
        }
        
        font_codes_to_string((char *)&state.game_name, (char *)fileNames[i], PFS_FILE_NAME_LEN);
        font_codes_to_string((char *)&state.ext_name, (char *)fileExtensions[i], PFS_FILE_EXT_LEN);
        fileSizes[i] = state.file_size;
        fileTypes[i] = SAVE_FILE_TYPE_UNKNOWN;
        
        if ((state.game_code == gameCode) && (state.company_code == COMPANY_CODE)) {
            fileTypes[i] = get_file_type(controllerIndex, i);
        }
    }
    
    start_reading_controller_data(controllerIndex);
    return CONTROLLER_PAK_GOOD;
}

//Free D_800DE440
void packDirectoryFree(void) {
    if (D_800DE440 != 0) {
        free_from_memory_pool(D_800DE440);
    }
    D_800DE440 = 0;
}

//Get Available Space in Controller Pak
//Upper bytes of return value could be controllerIndex
/* Official Name: packFreeSpace */
s32 get_free_space(s32 controllerIndex, u32 *bytesFree, s32 *notesFree) {
    s32 ret;
    s32 bytesNotUsed;
    s32 maxNotes;
    s32 notesUsed;

    ret = get_si_device_status(controllerIndex);
    if (ret == CONTROLLER_PAK_GOOD) {
        if (bytesFree != 0) {
            ret = osPfsFreeBlocks(&pfs[controllerIndex], &bytesNotUsed);
            if (ret != 0) {
                start_reading_controller_data(controllerIndex);
                return (controllerIndex << 30) | CONTROLLER_PAK_BAD_DATA;
            }
            *bytesFree = bytesNotUsed;
        }
        if (notesFree != 0) {
            ret = osPfsNumFiles(&pfs[controllerIndex], &maxNotes, &notesUsed);
            if (ret != 0) {
                start_reading_controller_data(controllerIndex);
                return (controllerIndex << 30) | CONTROLLER_PAK_BAD_DATA;
            }
            if (notesUsed >= 16) {
                *notesFree = 0;
            } else {
                *notesFree = 16 - notesUsed;
            }
        }
    } else {
        ret |= controllerIndex << 30;
    }
    start_reading_controller_data(controllerIndex);
    return ret;
}

/* Official Name: packDeleteFile */
s32 delete_file(s32 controllerIndex, s32 fileNum) {
    OSPfsState state;
    s32 ret;

    ret = get_si_device_status(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | ret;
    }

    ret = (controllerIndex << 30) | CONTROLLER_PAK_BAD_DATA;

    if (osPfsFileState(&pfs[controllerIndex], fileNum, &state) == 0) {
        if (osPfsDeleteFile(&pfs[controllerIndex], state.company_code, state.game_code, (u8 *)&state.game_name, (u8 *)&state.ext_name) == 0) {
            ret = CONTROLLER_PAK_GOOD;
        }
    }

    start_reading_controller_data(controllerIndex);

    return ret;
}

// Copies a file from one controller pak to the other
/* Official Name: packCopyFile */
s32 copy_controller_pak_data(s32 controllerIndex, s32 fileNumber, s32 secondControllerIndex) {
    UNUSED s32 pad;
    char fileName[PFS_FILE_NAME_LEN];
    UNUSED s32 pad2;
    char fileExt[PFS_FILE_EXT_LEN];
    OSPfsState state;
    s32 status;
    u8 *alloc;

    status = get_si_device_status(controllerIndex);
    if (status != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | status;
    }

    if (osPfsFileState(&pfs[controllerIndex], fileNumber, &state) != 0) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | CONTROLLER_PAK_BAD_DATA;
    }

    alloc = allocate_from_main_pool_safe(state.file_size, COLOUR_TAG_BLACK);

    status = read_data_from_controller_pak(controllerIndex, fileNumber, alloc, state.file_size);
    start_reading_controller_data(controllerIndex);
    if (status != CONTROLLER_PAK_GOOD) {
        free_from_memory_pool(alloc);
        return (controllerIndex << 30) | status;
    }

    font_codes_to_string(state.game_name, fileName, PFS_FILE_NAME_LEN);
    font_codes_to_string(state.ext_name, fileExt, PFS_FILE_EXT_LEN);

    status = write_controller_pak_file(secondControllerIndex, -1, fileName, fileExt, alloc, state.file_size);
    if (status != CONTROLLER_PAK_GOOD) {
        status |= (secondControllerIndex << 30);
    }

    free_from_memory_pool(alloc);
    return status;
}

// There is likely a struct that looks like this in here.
// typedef struct fileStruct {
//     s32 fileType;
//     u8 game_name[PFS_FILE_NAME_LEN];
// } fileStruct;
/* Official name: packOpenFile */
SIDeviceStatus get_file_number(s32 controllerIndex, char *fileName, char *fileExt, s32 *fileNumber) {
    u32 gameCode;
    char fileNameAsFontCodes[PFS_FILE_NAME_LEN];
    UNUSED s32 pad;
    char fileExtAsFontCodes[PFS_FILE_EXT_LEN];
    UNUSED s32 pad2;
    s32 ret;

    string_to_font_codes(fileName, fileNameAsFontCodes, PFS_FILE_NAME_LEN);
    string_to_font_codes(fileExt, fileExtAsFontCodes, PFS_FILE_EXT_LEN);

    if (get_language() == LANGUAGE_JAPANESE) {
        gameCode = JPN_GAME_CODE;
    } else if (osTvType == TV_TYPE_PAL) {
        gameCode = PAL_GAME_CODE;
    } else {
        gameCode = NTSC_GAME_CODE;
    }


    ret = osPfsFindFile(&pfs[controllerIndex], COMPANY_CODE, gameCode, (u8 *)fileNameAsFontCodes, (u8 *)fileExtAsFontCodes, fileNumber);
    if (ret == 0) {
        return CONTROLLER_PAK_GOOD;
    }
    if ((ret == PFS_ERR_NOPACK) || (ret == PFS_ERR_DEVICE)) {
        return NO_CONTROLLER_PAK;
    }
    if (ret == PFS_ERR_INCONSISTENT) {
        return CONTROLLER_PAK_INCONSISTENT;
    }
    if (ret == PFS_ERR_ID_FATAL) {
        return CONTROLLER_PAK_WITH_BAD_ID;
    }
    if (ret == PFS_ERR_INVALID) {
        return CONTROLLER_PAK_CHANGED;
    }
    
    return CONTROLLER_PAK_BAD_DATA;
}

/* Official name: packReadFile */
SIDeviceStatus read_data_from_controller_pak(s32 controllerIndex, s32 fileNum, u8 *data, s32 dataLength) {
    s32 readResult = osPfsReadWriteFile(&pfs[controllerIndex], fileNum, PFS_READ, 0, dataLength, data);

    if (readResult == 0) {
        return CONTROLLER_PAK_GOOD;
    }
    if ((readResult == PFS_ERR_NOPACK) || (readResult == PFS_ERR_DEVICE)) {
        return NO_CONTROLLER_PAK;
    }
    if (readResult == PFS_ERR_INCONSISTENT) {
        return CONTROLLER_PAK_INCONSISTENT;
    }
    if (readResult == PFS_ERR_ID_FATAL) {
        return CONTROLLER_PAK_WITH_BAD_ID;
    }
    if (readResult == PFS_ERR_INVALID) {
        return CONTROLLER_PAK_CHANGED;
    }

    return CONTROLLER_PAK_BAD_DATA;
}

//If fileNumber -1, it creates a new file?
/* Official name: packWriteFile */
SIDeviceStatus write_controller_pak_file(s32 controllerIndex, s32 fileNumber, char *fileName, char *fileExt, u8 *dataToWrite, s32 fileSize) {
    s32 temp;
    u8 fileNameAsFontCodes[PFS_FILE_NAME_LEN];
    UNUSED s32 temp2;
    u8 fileExtAsFontCodes[PFS_FILE_EXT_LEN];
    s32 ret;
    s32 file_number;
    s32 bytesToSave;
    u32 game_code;

    ret = get_si_device_status(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return ret;
    }

    bytesToSave = fileSize;
    temp = fileSize & 0xFF;
    if (temp != 0) {
        bytesToSave = (fileSize - temp) + 0x100;
    }

    string_to_font_codes(fileName, (char *)fileNameAsFontCodes, PFS_FILE_NAME_LEN);
    string_to_font_codes(fileExt, (char *)fileExtAsFontCodes, PFS_FILE_EXT_LEN);

    if (get_language() == LANGUAGE_JAPANESE) {
        game_code = JPN_GAME_CODE;
    } else if (osTvType == TV_TYPE_PAL) {
        game_code = PAL_GAME_CODE;
    } else {
        game_code = NTSC_GAME_CODE;
    }

    ret = get_file_number(controllerIndex, fileName, fileExt, &file_number);
    if (ret == CONTROLLER_PAK_GOOD) {
        if (fileNumber != -1 && fileNumber != file_number) {
            ret = CONTROLLER_PAK_BAD_DATA;
        }
    } else if (ret == CONTROLLER_PAK_CHANGED) {
        if (fileNumber != -1) {
            ret = CONTROLLER_PAK_BAD_DATA;
        } else {
            temp = osPfsAllocateFile(&pfs[controllerIndex], COMPANY_CODE, game_code, fileNameAsFontCodes, fileExtAsFontCodes, bytesToSave, &file_number);
            if (temp == 0) {
                ret = CONTROLLER_PAK_GOOD;
            } else if (temp == PFS_DATA_FULL || temp == PFS_DIR_FULL) {
                ret = CONTROLLER_PAK_FULL;
            } else {
                ret = CONTROLLER_PAK_BAD_DATA;
            }
        }
    }

    if (ret == CONTROLLER_PAK_GOOD) {
        temp = osPfsReadWriteFile(&pfs[controllerIndex], file_number, PFS_WRITE, 0, bytesToSave, dataToWrite);
        if (temp == 0) {
            ret = CONTROLLER_PAK_GOOD;
        } else if ((temp == PFS_ERR_NOPACK) || (temp == PFS_ERR_DEVICE)) {
            ret = NO_CONTROLLER_PAK;
        } else if (temp == PFS_ERR_INCONSISTENT) {
            ret = CONTROLLER_PAK_INCONSISTENT;
        } else if (temp == PFS_ERR_ID_FATAL) {
            ret = CONTROLLER_PAK_WITH_BAD_ID;
        }
        else {
            ret = CONTROLLER_PAK_BAD_DATA;
        }
    }

    start_reading_controller_data(controllerIndex);
    return ret;
}

//Get File size for given controller's Control Pak
/* Official name: packFileSize */
SIDeviceStatus get_file_size(s32 controllerIndex, s32 fileNum, s32 *fileSize) {
    OSPfsState state;

    *fileSize = 0;
    if (osPfsFileState(&pfs[controllerIndex], fileNum, &state) == 0) {
        *fileSize = state.file_size;
        return CONTROLLER_PAK_GOOD;
    }
    return CONTROLLER_PAK_BAD_DATA;
}

//Converts N64 Font codes used in controller pak file names, into C ASCII a coded string
char *font_codes_to_string(char *inString, char *outString, s32 stringLength) {
    s32 index = *inString;
    char *ret = outString;

    while (index != 0 && stringLength != 0) {
        // Less than sizeof(gN64FontCodes) - 3.
        // So basically make sure it's a valid font code value
        if (index <= 65) {
            *outString = gN64FontCodes[index];
            outString++;
        } else {
            //Replace invalid characters with a hyphen
            *outString = '-';
            outString++;
        }

        inString++;
        stringLength--;
        index = *inString;
    }

    //Pad any extra characters with NULL font code
    while (stringLength != 0) {
        *outString = 0;
        stringLength--;
        outString++;
    }
    
    *outString = 0;
    return ret;
}

//Converts a C ASCII string into N64 Font codes for controller pak file names
char *string_to_font_codes(char *inString, char *outString, s32 stringLength) {
    s32 i;
    char currentChar;
    char *ret = outString;

    while (*inString != 0 && stringLength != 0) {
        *outString = 0;
        for (i = 0; i < 65; i++) {
            currentChar = *inString;
            if (currentChar == gN64FontCodes[i]) {
                *outString = i;
                outString++;
                break;
            }
        }

        inString++;
        stringLength--;
    }

    while (stringLength != 0) {
        *outString = 0;
        stringLength--;
        outString++;
    }
    
    *outString = 0;
    return ret;
}

/**
 * For the given controller, and file, this will return a value for which type of file it is.
 */
SaveFileType get_file_type(s32 controllerIndex, s32 fileNum) {
    s32 *data;
    UNUSED s32 pad;
    s32 ret;

    ret = SAVE_FILE_TYPE_UNKNOWN;
    data = allocate_from_main_pool_safe(0x100, COLOUR_TAG_BLACK);
    if (read_data_from_controller_pak(controllerIndex, fileNum, (u8 *) data, 0x100) == CONTROLLER_PAK_GOOD) {
        switch (*data) {
            case GAMD:
                ret = SAVE_FILE_TYPE_GAME_DATA;
                break;
            case TIMD:
                ret = SAVE_FILE_TYPE_TIME_DATA;
                break;
            case GHSS:
                ret = SAVE_FILE_TYPE_GHOST_DATA;
                break;
            default:
                ret = SAVE_FILE_TYPE_UNKNOWN;
                break;
        }
    }
    free_from_memory_pool(data);
    return ret;
}
