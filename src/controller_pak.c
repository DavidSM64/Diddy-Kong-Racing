/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80072250 */

#include "controller_pak.h"
#include "memory.h"
#include "PR/pfs.h"
#include "PR/os_cont.h"
#include "macros.h"
#include "structs.h"
#include "camera.h"
#include "unknown_00BC20.h"
#include "unknown_06B2B0.h"
#include "unknown_0CEC50.h"

/************ .data ************/

s8 *D_800DE440 = 0;

u8 gN64FontCodes[] = "\0               0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#'*+,-./:=?@";

u8 sControllerPaksPresent = 0; // Bits 0, 1, 2, and 3 of the bit pattern correspond to Controllers 1, 2, 3, and 4. 1 if a controller pak is present
s32 D_800DE48C = 0;

/*******************************/

/************ .rodata ************/

const char D_800E7590[] = "Region = %d	 loc = %x	 size = %x\t";
const char D_800E75B4[] = "FREE";
const char D_800E75BC[] = "ALLOCATED";
const char D_800E75C8[] = "ALLOCATED,FIXED";
const char D_800E75D8[] = "\n";
const char D_800E75DC[] = "\n";
const char D_800E75E0[] = "Region number = %d\t";
const char D_800E75F4[] = "maxSlots = %d\t";
const char D_800E7604[] = "slotsUsed = %d\t";
const char D_800E7614[] = "loc = %x\t";
const char D_800E7620[] = "size = %x\n";
const char D_800E762C[] = "\n";

const char D_800E7630[] = "DKRACING-ADV";
const char D_800E7640[] = "DKRACING-ADV";
const char D_800E7650[] = "DKRACING-TIMES";
const char D_800E7660[] = "DKRACING-TIMES";
const char D_800E7670[] = "DKRACING-ADV";
const char D_800E7680[] = "DKRACING-ADV";
const char D_800E7690[] = "DKRACING-TIMES";
const char D_800E76A0[] = "DKRACING-TIMES";

const char D_800E76B0[] = "WARNING : No Eprom\n";
const char D_800E76C4[] = "WARNING : No Eprom\n";
const char D_800E76D8[] = "WARNING : No Eprom\n";
const char D_800E76EC[] = "WARNING : No Eprom\n";
const char D_800E7700[] = "WARNING : No Eprom\n";
const char D_800E7714[] = "WARNING : No Eprom\n";
const char D_800E7728[] = "WARNING : No Eprom\n";

const char D_800E773C[] = "DKRACING-GHOSTS"; // Used in func_80074B34
const u8 D_800E774C[4] = { 0, 0, 0, 0 };     // Used in func_80074B34, but I'm confused to what this is for.
const char D_800E7750[] = "warning: corrupt ghost\n";

/*********************************/

/************ .bss ************/

OSMesgQueue *sControllerMesgQueue;
s32 D_80124014;

OSPfs pfs[MAXCONTROLLERS];

typedef struct unk_801241B8 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
} unk_801241B8;
unk_801241B8 D_801241B8[MAXCONTROLLERS];

s32 *sUnkMiscAsset19; //Misc Asset 19
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
volatile u8 D_801241E7;
s32 D_801241E8;
s8 *D_801241EC;
s32 D_801241F0;
s32 D_801241F4;

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
    if (arg0 != 0) {
        D_801241E8 = 0x79;
        D_801241E6 = 0xF;
        return;
    }
    func_80072708();
}

UNUSED s32 func_800722E8(s16 arg0) {
    s32 temp;
    if (arg0 < 0 || arg0 >= 4) {
        return 0;
    }
    temp = ((1 << func_80072250(arg0)) & 0xFF);
    return sRumblePaksPresent & temp;
}

#ifdef NON_EQUIVALENT
//In the right ballpark, but not right yet.
void func_80072348(s16 arg0, u8 arg1) {
    s32 arg1AsS32 = arg1;
    s16 *temp_v0;
    unk_801241B8 *temp_v1;
    u16 playerId;

    if (arg1AsS32 < 19 && arg0 >= 0) {
        if (arg0 < 4) {
            playerId = (func_80072250(arg0));
            temp_v1 = &D_801241B8[playerId];
            if (arg1AsS32 == temp_v1->unk0) {
                if (temp_v1->unk8 < 0) {
                    temp_v1->unk8 = -300;
                }
                temp_v1->unk4 = sUnkMiscAsset19[arg1AsS32 + 1];
            } else {
                temp_v1->unk0 = arg1AsS32;
                temp_v0 = &sUnkMiscAsset19[arg1AsS32];
                if (*temp_v0 != 0) {
                    func_80072578(arg0,  temp_v0[0], temp_v0[1]);
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072348.s")
#endif

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072424.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072578.s")

void func_80072708(void) {
    D_800DE48C = 3;
}

//Rumbles controller?
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072718.s")

#ifdef NON_EQUIVALENT
u16 func_80072C54(s32 arg0) {
    // v0 v1 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 t8
    u32 v0;
    u32 v1;
    s32 a1;
    u32 a2;
    u8 *a3;
    s32 t0;
    u32 *t1;
    u32 *t2;
    u8 **t3;
    u32 t4;
    u32 t5;
    u32 t6;
    u32 t7;
    u32 t8;
    u32 t9;

    v1 = 0;
    if (arg0 <= 0) {
        return v1;
    }
    // L80072C64
    v0 = 1 << (arg0 + 0x1F);
    if (arg0 != 0) {
        a1 = -(arg0 & 3);
        t0 = a1 + arg0;
        if (a1 != 0) {
            // L80072CA0
            do {
                a2 = D_801241F4;
                a1 = arg0 - 1;
                t6 = v0 >> 1;
                if (a2 == 0) {
                    a3 = D_801241EC;
                    a2 = 0x80;
                    t8 = *a3;
                    D_801241EC = a3 + 1;
                    D_801241F4 = 0x80;
                    D_801241F0 = t8;
                }
                // L80072CCC
                arg0 = a1;
                if (D_801241F0 & a2 != 0) {
                    v1 |= v0;
                }
                // L80072CE4
                v0 = t6;
                D_801241F4 = a2 >> 1;
            } while (t0 != a1);
            if (a1 == 0) {
                return v1;  // should jump to end
            }
        }
        // L80072CF4
        t1 = &D_801241F4;
        t2 = &D_801241F0;
        t3 = &D_801241EC;
        t4 = 128;
        // L80072D10
        do {
            a2 = *t1;
            t6 = v0 >> 1;
            arg0 -= 4;
            if (a2 == 0) {
                a3 = *t3;
                a2 = t4;
                t9 = *a3;
                *t3 = a3 + 1;
                *t1 = t4;
                *t2 = t9;
            }
            // L80072D3C
            a1 = *t2;
            t8 = a2 << 1;
            t7 = a1 & a2;
            a2 = t8;
            if (t7 != 0) {
                v1 |= v0;
            }
            // L80072D54
            v0 = t6;
            *t1 = t8;
            if (t8 == 0) {
                a3 = *t3;
                a2 = t4;
                a1 = *a3;
                *t3 = a3 + 1;
                *t1 = t4;
                *t2 = a1;
            }
            // L80072D7C
            t7 = a1 & a2;
            t6 = v0 >> 1;
            if (t7 != 0) {
                v1 |= v0;
            }
            // L80072D8C
            t8 = a2 >> 1;
            *t1 = t8;
            a2 = t8;
            v0 = t6;
            if (t8 == 0) {
                a3 = *t3;
                a2 = t4;
                a1 = *a3;
                *t3 = a3 + 1;
                *t1 = t4;
                *t2 = a1;
            }
            // L80072DBC
            t7 = a1 & a2;
            t6 = v0 >> 1;
            if (t7 != 0) {
                v1 |= v0;
            }
            // L80072DCC
            t8 = a2 >> 1;
            *t1 = t8;
            a2 = t8;
            v0 = t6;
            if (t8 == 0) {
                a3 = *t3;
                a2 = t4;
                a1 = *a3;
                *t3 = a3 + 1;
                *t1 = t4;
                *t2 = a1;
            }
            // L80072DFC
            t7 = a1 & a2;
            t6 = v0 >> 1;
            if (t7 != 0) {
                v1 |= v0;
            }
            // L80072E0C
            t8 = a2 >> 1;
            *t1 = t8;
            v0 = t6;
        } while (arg0 != 0);
    }
    // L80072E1C
    return v1;
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072C54.s")
#endif

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072E28.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_8007306C.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800732E8.s")

//arg1 is eepromData, from read_eeprom_data
//arg2 seems to be a flag for either lap times or course initials?
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80073588.s")

GLOBAL_ASM("asm/non_matchings/controller_pak/func_800738A4.s")

s32 get_game_data_file_size(void) {
    return 256;
}

s32 get_time_data_file_size(void) {
    return 512;
}

//Probably get_file_extension
//func_80073C5C(s32 controllerIndex, s32 fileType, u8 **fileExt);
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80073C5C.s")

//Read DKRACING-ADV data into settings?
s32 read_game_data_from_controller_pak(s32 controllerIndex, u8 *fileExt, Settings *settings) {
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
    //D_800E7670 = "DKRACING-ADV"
    ret = get_file_number(controllerIndex, (u8 *)D_800E7670, fileExt, &fileNumber);
    if (ret == CONTROLLER_PAK_GOOD) {
        ret = get_file_size(controllerIndex, fileNumber, &fileSize);
        if (fileSize == 0) {
            ret = CONTROLLER_PAK_BAD_DATA;
        }
        if (ret == CONTROLLER_PAK_GOOD) {
            alloc = allocate_from_main_pool_safe(fileSize, COLOR_TAG_BLACK);
            ret = read_data_from_controller_pak(controllerIndex, fileNumber, (u8 *)alloc, fileSize);

            if (ret == CONTROLLER_PAK_GOOD) {
                if (*alloc == GAMD) {
                    func_8007306C(settings, (s32) (alloc + 1));
                    if (settings->newGame != 0) {
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
    u8 *fileExt;
    u8 *gameData; //Probably a struct where the first s32 is GAMD
    s32 ret;
    s32 fileSize;

    fileSize = get_game_data_file_size(); // 256 bytes
    gameData = allocate_from_main_pool_safe(fileSize, COLOR_TAG_WHITE);
    *((s32 *)gameData) = GAMD;
    func_800732E8(arg1, gameData + 4);
    ret = func_80073C5C(controllerIndex, 3, &fileExt);
    if (ret == 0) {
        // D_800E7680 = DKRACING-ADV
        ret = write_controller_pak_file(controllerIndex, -1, (u8 *) D_800E7680, (u8 *) &fileExt, gameData, fileSize);
    }
    free_from_memory_pool(gameData);
    if (ret != 0) {
        ret |= (controllerIndex << 30);
    }
    return ret;
}

//Read time data from controller pak into settings
s32 read_time_data_from_controller_pak(s32 controllerIndex, u8 *fileExt, Settings *settings) {
    s32 *cpakData;
    s32 status;
    s32 fileNumber;
    s32 fileSize;

    status = get_si_device_status(controllerIndex);
    if (status != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | status;
    }

    //D_800E7690 = DKRACING-TIMES
    status = get_file_number(controllerIndex, (u8 *)D_800E7690, fileExt, &fileNumber);
    if (status == CONTROLLER_PAK_GOOD) {
        status = get_file_size(controllerIndex, fileNumber, &fileSize);
        if (fileSize == 0) {
            status = CONTROLLER_PAK_BAD_DATA;
        }

        if (status == CONTROLLER_PAK_GOOD) {
            cpakData = allocate_from_main_pool_safe(fileSize, COLOR_TAG_BLACK);

            status = read_data_from_controller_pak(controllerIndex, fileNumber, (u8 *)cpakData, fileSize);
            if (status == CONTROLLER_PAK_GOOD) {
                if (*cpakData == TIMD) {
                    func_80073588(settings, (u64 *) (cpakData + 1), 3);
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
    UNUSED s32 temp_v0;
    u8 *fileExt;

    fileSize = get_time_data_file_size(); // 512 bytes
    timeData = allocate_from_main_pool_safe(fileSize, COLOR_TAG_WHITE);
    *((s32 *)timeData) = TIMD;
    func_800738A4(arg1, timeData + 4);
    ret = func_80073C5C(controllerIndex, 4, &fileExt);
    if (ret == CONTROLLER_PAK_GOOD) {
        //D_800E76A0 = DKRACING-TIMES
        ret = write_controller_pak_file(controllerIndex, -1, (u8 *) &D_800E76A0, (u8 *) &fileExt, timeData, fileSize);
    }
    free_from_memory_pool(timeData);
    if (ret != CONTROLLER_PAK_GOOD) {
        ret |= (controllerIndex << 30);
    }
    return ret;
}

#ifdef MIPS_TO_C
u8 func_80074204(s32 arg0, Settings *arg1) {
    s32 sp2C;
    s32 temp_s0;
    u8 temp_v1;
    void *temp_s2;
    s32 phi_v1;
    s32 phi_s1;
    s32 phi_s0;
    u8 phi_v0;

    if (osEepromProbe(get_si_mesg_queue()) == 0) {
        return -1U;
    }
    if (arg0 != 0) {
        if (arg0 != 1) {
            phi_v1 = 0xA;
            if (arg0 != 2) {

            }
        } else {
            phi_v1 = 5;
        }
    } else {
        phi_v1 = 0;
    }
    sp2C = phi_v1;
    temp_s2 = allocate_from_main_pool_safe(0x28, -1U);
    phi_s1 = sp2C;
    phi_s0 = 0;
    do {
        osEepromRead(get_si_mesg_queue(), phi_s1 & 0xFF, (phi_s0 * 8) + temp_s2);
        temp_s0 = phi_s0 + 1;
        phi_s1 += 1;
        phi_s0 = temp_s0;
    } while (temp_s0 != 5);
    func_8007306C(arg1, (s32) temp_s2);
    free_from_memory_pool(temp_s2);
    temp_v1 = arg1->newGame;
    phi_v0 = temp_v1;
    if (temp_v1 != 0) {
        func_8007431C(arg0, arg1);
        phi_v0 = arg1->newGame;
    }
    return phi_v0;
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074204.s")
#endif

#ifdef MIPS_TO_C
void func_8007431C(s32 arg0, Settings *arg1) {
    s32 sp54;
    s32 sp44;
    s32 sp40;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    void *temp_s3;
    void *temp_v0;
    s32 phi_v0;
    s32 phi_s0;
    s32 phi_v0_2;
    s32 phi_s0_2;
    s32 phi_a2;
    void *phi_v1;
    s32 phi_s0_3;
    s32 phi_s1;
    s32 phi_s0_4;
    s32 phi_s0_5;

    if (osEepromProbe(get_si_mesg_queue()) != 0) {
        get_number_of_levels_and_worlds(&sp44, &sp40);
        phi_s0 = 0;
        phi_s0_4 = 0;
        phi_s0_5 = 0;
        if (sp44 > 0) {
            phi_v0 = 0;
            do {
                temp_s0 = phi_s0 + 1;
                *(arg1->courseFlagsPtr + phi_v0) = 0;
                phi_v0 += 4;
                phi_s0 = temp_s0;
            } while (temp_s0 < sp44);
        }
        phi_s0_2 = 0;
        phi_s0_5 = 0;
        if (sp40 > 0) {
            phi_v0_2 = 0;
            do {
                temp_s0_2 = phi_s0_2 + 1;
                *(arg1->balloonsPtr + phi_v0_2) = 0;
                phi_v0_2 += 2;
                phi_s0_2 = temp_s0_2;
            } while (temp_s0_2 < sp40);
        }
        arg1->trophies = 0;
        arg1->bosses = 0;
        arg1->tajFlags = 0;
        arg1->cutsceneFlags = 0;
        arg1->newGame = 1;
        phi_s0_3 = phi_s0_5;
        if (arg0 != 0) {
            if (arg0 != 1) {
                phi_a2 = 0xA;
                if (arg0 != 2) {

                }
            } else {
                phi_a2 = 5;
            }
        } else {
            phi_a2 = 0;
        }
        sp54 = phi_a2;
        temp_v0 = allocate_from_main_pool_safe(0x28, -1U);
        temp_s3 = temp_v0;
        phi_v1 = temp_v0 + phi_s0_5;
        do {
            temp_s0_3 = phi_s0_3 + 4;
            phi_v1->unk0 = 0xFF;
            phi_v1->unk1 = 0xFF;
            phi_v1->unk2 = 0xFF;
            phi_v1->unk3 = 0xFF;
            phi_v1 += 4;
            phi_s0_3 = temp_s0_3;
        } while (temp_s0_3 != (5 * 8));
        sp54 = phi_a2;
        if (is_reset_pressed() == 0) {
            phi_s1 = phi_a2;
            do {
                osEepromWrite(get_si_mesg_queue(), phi_s1 & 0xFF, (phi_s0_4 * 8) + temp_s3);
                temp_s0_4 = phi_s0_4 + 1;
                phi_s1 += 1;
                phi_s0_4 = temp_s0_4;
            } while (temp_s0_4 != 5);
        }
        free_from_memory_pool(temp_s3);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_8007431C.s")
#endif

// Writes Eeprom in 5 block chunks of data starting at either 0x0, 0x5, or 0xA
// Educated guess says this might be for one of three save files
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
    alloc = allocate_from_main_pool_safe(blocks * sizeof(u64), COLOR_TAG_WHITE);
    func_800732E8(settings, (u8 *)alloc);

    if (!is_reset_pressed()) {
        for (i = 0, address = startingAddress; i < blocks; i++, address++) {
            osEepromWrite(get_si_mesg_queue(), address, (u8 *)&alloc[i]);
        }
    }

    free_from_memory_pool(alloc);

    return 0;
}

// Read Eeprom Data for addresses 0x10 - 0x39
// arg1 is a flag
// arg1 is descended from (D_800DD37C & 3) so the first 2 bits of that value.
// bit 1 is for 0x10 - 0x27
// bit 2 is for 0x28 - 0x39
s32 read_eeprom_data(Settings *arg0, u8 arg1) {
    u64 *alloc;
    s32 i;

    if (osEepromProbe(get_si_mesg_queue()) == 0) {
        return -1;
    }

    alloc = allocate_from_main_pool_safe(0x200, COLOR_TAG_WHITE);

    if (arg1 & 1) {
        s32 blocks = 24;
        for (i = 0; i < blocks; i++) {
            osEepromRead(get_si_mesg_queue(), i + 0x10, (u8 *)&alloc[i]);
        }
        func_80073588(arg0, alloc, 1);
    }

    if (arg1 & 2) {
        s32 blocks = 24;
        for (i = 0; i < blocks; i++) {
            osEepromRead(get_si_mesg_queue(), i + 0x28, (u8 *)(&alloc[24] + i));
        }
        func_80073588(arg0, alloc, 2);
    }

    free_from_memory_pool(alloc);
    return 0;
}

// Write Eeprom Data for addresses 0x10 - 0x39
// arg1 is a flag
// bit 1 is for 0x10 - 0x27
// bit 2 is for 0x28 - 0x39
s32 write_eeprom_data(Settings *arg0, u8 arg1) {
    u64 *alloc;
    s32 i;

    if (osEepromProbe(get_si_mesg_queue()) == 0) {
        return -1;
    }

    alloc = allocate_from_main_pool_safe(0x200, COLOR_TAG_WHITE);

    func_800738A4(arg0, (u8 *)alloc);

    if (arg1 & 1) {
        s32 size = 24;
        if (1){} //Fake Match
        if (!is_reset_pressed()) {
            for (i = 0; i != size; i++) {
                osEepromWrite(get_si_mesg_queue(), i + 16, (u8 *)&alloc[i]);
            }
        }
    }

    if (arg1 & 2) {
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

s32 calculate_eeprom_settings_checksum(u64 eepromSettings) {
    s32 ret;
    s32 i;

    ret = 5;
    for (i = 0; i <= 13; i++) {
        ret += (u16)(eepromSettings >> (i << 2)) & 0xF;
    }
    return ret;
}

// Reads eeprom address 0xF (15)
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

//Writes eeprom address 0xF (15)
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
    ghostHeader->FirstPair.checksum = 0;
    ghostHeader->SecondPair.character.ID = characterID;
    ghostHeader->SecondPair.character.unk3 = 0;
    ghostHeader->time = time;
    ghostHeader->nodeCount = nodeCount;
    bcopy(dest, (u8 *)ghostHeader + 8, nodeCount * sizeof(GhostDataFrame));
    ghostHeader->FirstPair.checksum = calculate_ghost_header_checksum(ghostHeader);
}

//Seems to only be called when used as an argument for func_800860A8. Effectively just returns 0x6700
s32 func_80074B1C(void) {
    //func_80074EB8 Makes extensive use out of 0x1100, and even does a * 6 to it.
    //func_80075000 Uses 0x1100 once as well.
    //Another possibility for 0x1100, seems to be from func_8007BA5C which seems to do (0xF5101100 & 0xFFFF);
    int x = 0x1100;
    return (&x)[0] * 6 + 0x100;
}

#ifdef MIPS_TO_C
//The GhostHeader might have an alternate version where the checksum is u8 levelId, u8 vehicleId, and the chararcter ID is an s16 or something?
s32 func_80074B34(s32 controllerIndex, s16 levelID, s16 vehicleID, s16 *ghostCharacterID, s16 *ghostTime, s16 *ghostNodeCount, GhostHeader *arg6) {
    GhostHeader *sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp40;
    s32 sp3C;
    u32 sp38;
    s32 sp34;
    OSPfs *sp30;
    OSPfs *temp_t4;
    s16 temp_t3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    GhostHeader *temp_a1;
    u8 *temp_v0_5;
    void *temp_v0_4;
    GhostHeader *phi_v0;
    s32 phi_v1;
    s32 phi_a3;
    s32 phi_a3_2;
    s32 phi_a3_3;
    s32 phi_v0_2;

    sp40 = 0;
    temp_v0 = get_si_device_status(controllerIndex);
    if (temp_v0 != CONTROLLER_PAK_GOOD) {
        sp4C = temp_v0;
        start_reading_controller_data(controllerIndex);
        return temp_v0;
    }
    if (ghostCharacterID != 0) {
        *ghostTime = -1;
        *ghostCharacterID = -1;
    }
    temp_v0_2 = get_file_number(controllerIndex, (u8 *) D_800E773C, D_800E774C, &sp48);
    phi_a3_3 = temp_v0_2;
    if (temp_v0_2 == 0) {
        temp_t4 = &pfs[controllerIndex];
        sp50 = allocate_from_main_pool_safe(0x100, 0xFFU);
        sp30 = temp_t4;
        if ((temp_t4->status & 1) == 0) {
            osPfsInit(sControllerMesgQueue, temp_t4, controllerIndex);
        }
        temp_v0_3 = read_data_from_controller_pak(controllerIndex, sp48, sp50, 0x100);
        phi_a3 = temp_v0_3;
        if (temp_v0_3 == 0) {
            temp_a1 = sp50 + 4;
            if (sp50->checksum == GHSS) {
                phi_v0 = temp_a1;
                phi_v1 = 0;
loop_10:
                temp_v1 = phi_v1 + 4;
                phi_v1 = temp_v1;
                //This could mean the GhostHeader can be seperated by levelId, and vehicleID u8s?
                if ((levelID == phi_v0->levelID) && (vehicleID == phi_v0->vehicleID)) {
                    temp_t3 = phi_v0->unk2;
                    sp40 = (s32) temp_t3;
                    sp3C = phi_v0->nodeCount - temp_t3;
                } else {
                    phi_v0 += 4;
                    if (temp_v1 < 0x18) {
                        goto loop_10;
                    }
                }
                if (sp40 == 0) {
                    phi_a3 = 6;
                    if (sp50[4] == 0xFF) {
                        phi_a3 = 8;
                    }
                    temp_v0_4 = temp_a1 + (2 * 4);
                    if (sp50[4].unk4 == 0xFF) {
                        phi_a3 = 8;
                    }
                    if (temp_v0_4->unk0 == 0xFF) {
                        phi_a3 = 8;
                    }
                    if (temp_v0_4->unk4 == 0xFF) {
                        phi_a3 = 8;
                    }
                    if (temp_v0_4->unk8 == 0xFF) {
                        phi_a3 = 8;
                    }
                    if (temp_v0_4->unkC == 0xFF) {
                        phi_a3 = 8;
                    }
                }
            } else {
                phi_a3 = 9;
            }
        }
        sp4C = phi_a3;
        free_from_memory_pool(sp50);
        phi_a3_3 = phi_a3;
        phi_a3_3 = phi_a3;
        if (sp40 != 0) {
            if (ghostCharacterId != 0) {
                temp_v0_5 = allocate_from_main_pool_safe(sp3C + 0x100, 0xFFU);
                sp50 = temp_v0_5;
                phi_a3_2 = 9;
                if (osPfsReadWriteFile(sp30, sp48, 0U, sp40, sp3C, temp_v0_5) == 0) {
                    if (calculate_ghost_header_checksum((GhostHeader *) sp50) == (s16) sp50->checksum) {
                        *ghostCharacterId = (s16) sp50->characterID;
                        *ghostTime = sp50->time;
                        *ghostNodeCount = sp50->nodeCount;
                        bcopy(sp50 + 8, arg6, *ghostNodeCount * 0xC);
                        phi_a3_2 = 0;
                    }
                }
                sp4C = phi_a3_2;
                free_from_memory_pool(sp50);
                phi_a3_3 = phi_a3_2;
            }
        }
        if ((sp40 != 0) && (ghostCharacterID == 0)) {
            phi_a3_3 = 0;
        }
    }
    sp4C = phi_a3_3;
    start_reading_controller_data(controllerIndex);
    if (phi_a3_3 == 5) {
        sp4C = phi_a3_3;
        if (get_free_space(controllerIndex, &sp38, &sp34) == 0) {
            sp4C = sp4C;
            if (((s32) sp38 < func_80074B1C()) || (phi_v0_2 = sp4C, (sp34 == 0))) {
                return 4;
            }
            /* Duplicate return node #48. Try simplifying control flow for better match */
            return phi_v0_2;
        }
        return 9;
    }
    phi_v0_2 = phi_a3_3;
    return phi_v0_2;
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074B34.s")
#endif

#ifdef MIPS_TO_C
static u8 D_800E7778 = 0;                           /* const */

s32 func_80074EB8(s32 controllerIndex, s16 arg1, s16 arg2, s16 ghostCharacterId, s16 ghostTime, s16 ghostNodeCount, u8 *dest) {
    u8 *sp38;
    s32 sp30;
    s32 sp28;
    s32 sp24;
    s32 temp_v0;
    s32 temp_v0_2;
    u8 *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v1;

    temp_v0_2 = 0x1100 * 6;
    sp24 = temp_v0_2;
    sp30 = 0x1100;
    temp_v0_3 = allocate_from_main_pool_safe(temp_v0_2 + 0x200, 0xFFU);
    temp_v0_3->unk0 = 0x47485353;
    temp_v0_3->unk4 = (s8) arg1;
    temp_v0_3->unk6 = 0x100;
    temp_v1 = temp_v0_3 + 4;
    temp_v0_3->unkA = (s16) (temp_v0_3->unk6 + 0x1100);
    temp_v0_3->unk5 = (s8) arg2;
    temp_v0_4 = temp_v1 + 4;
    temp_v0_4->unk0 = 0xFF;
    temp_v0_4->unk4 = 0xFF;
    temp_v0_4->unk2 = (s16) temp_v1->unk6;
    temp_v0_4->unk6 = (s16) temp_v1->unk6;
    temp_v0_5 = temp_v1 + (3 * 4);
    temp_v0_5->unk0 = 0xFF;
    temp_v0_5->unk4 = 0xFF;
    temp_v0_5->unk2 = (s16) temp_v1->unk6;
    temp_v0_5->unk8 = 0xFF;
    temp_v0_5->unk6 = (s16) temp_v1->unk6;
    temp_v0_5->unkC = 0xFF;
    temp_v0_5->unkA = (s16) temp_v1->unk6;
    temp_v0_5->unkE = (s16) temp_v1->unk6;
    sp38 = temp_v0_3;
    func_80074AA8((GhostHeader *) &temp_v0_3[temp_v1->unk2], ghostCharacterId, ghostTime, ghostNodeCount, dest);
    temp_v0 = write_controller_pak_file(controllerIndex, -1, "DKRACING-GHOSTS", &D_800E7778, sp38, sp24 + 0x100);
    sp28 = temp_v0;
    free_from_memory_pool(sp38);
    return temp_v0;
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074EB8.s")
#endif

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80075000.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800753D8.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800756D4.s")

s32 get_si_device_status(s32 controllerIndex) {
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
    while (sControllerMesgQueue->validCount != 0 && i != 10) {
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

s32 start_reading_controller_data(UNUSED s32 controllerIndex) {
    osContStartReadData(sControllerMesgQueue);
    return 0;
}

#ifdef NON_MATCHING
void init_controller_paks(void) {
    s32 controllerIndex;
    s32 ret;
    u8 controllerBit;
    u8 pakPattern;
    s8 maxControllers;

    sControllerMesgQueue = get_si_mesg_queue();
    sUnkMiscAsset19 = get_misc_asset(19), //Comma is here on purpose
    D_801241E7 = 0xF;
    D_801241E6 = 0xF;
    D_801241E4 = 1;
    D_801241E8 = 0;
    D_800DE48C = 1;
    sRumblePaksPresent = 0; //sRumblePaksPresent
    sControllerPaksPresent = 0; //sControllerPaksPresent

    //pakPattern will set the first 4 bits representing each controller
    //and it will be 1 if there's something attached.
    osPfsIsPlug(sControllerMesgQueue, &pakPattern);

    for (controllerIndex = 0, controllerBit = 1, maxControllers = MAXCONTROLLERS; controllerIndex != maxControllers; controllerIndex++, controllerBit <<= 1) {
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
                if (osMotorInit(sControllerMesgQueue, &pfs[controllerIndex], controllerIndex) == 0) {
                    //If we found a rumble pak, set the bit that has one
                    sRumblePaksPresent |= controllerBit;
                }
            }
        }
    }

    osContStartReadData(sControllerMesgQueue);
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/init_controller_paks.s")
#endif

UNUSED s32 check_for_rumble_pak(s32 controllerIndex) {
    s32 ret;

    ret = get_si_device_status(controllerIndex);
    start_reading_controller_data(controllerIndex);

    if (ret == RUMBLE_PAK) {
        sRumblePaksPresent |= 1 << controllerIndex;
    }

    return ret;
}

//Inspects and repairs the Controller Pak's file system
s32 repair_controller_pak(s32 controllerIndex) {
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
s32 reformat_controller_pak(s32 controllerIndex) {
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

s32 get_controller_pak_file_list(s32 controllerIndex, s32 arg1, u8 **fileNames, u8 **fileExtensions, u32 *fileSizes, u8 *fileTypes) {
    OSPfsState state;
    s32 ret;
    s32 max_files;
    s32 files_used;
    s8 *temp_D_800DE440;
    s32 i;
    u32 gameCode;

    ret = get_si_device_status(controllerIndex);
    if (ret != CONTROLLER_PAK_GOOD) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | ret;
    }

    if (osPfsNumFiles(&pfs[controllerIndex], &max_files, &files_used) != 0) {
        start_reading_controller_data(controllerIndex);
        return (controllerIndex << 30) | CONTROLLER_PAK_BAD_DATA;
    }
    
    if (get_language() == JAPANESE) {
        gameCode = JPN_GAME_CODE;
    } else if (osTvType == TV_TYPE_PAL) {
        gameCode = PAL_GAME_CODE;
    } else {
        gameCode = NTSC_GAME_CODE;
    }
    
    if (arg1 < max_files) {
        max_files = arg1;
    }
    
    if (D_800DE440 != NULL) {
        free_from_memory_pool(D_800DE440);
    }
    
    files_used = max_files * 24;
    D_800DE440 = allocate_from_main_pool_safe(files_used, COLOR_TAG_BLACK);
    bzero(D_800DE440, files_used);
    temp_D_800DE440 = D_800DE440;
    
    //TODO: There's probably an unidentified struct here
    for (i = 0; i < max_files; i++) {
        fileNames[i] = (u8 *) temp_D_800DE440;
        temp_D_800DE440 += 0x12;
        fileExtensions[i] = (u8 *) temp_D_800DE440;
        fileSizes[i] = 0;
        fileTypes[i] = -1;
        temp_D_800DE440 += 6;
    }
    
    while (i < arg1) {
        fileExtensions[i] = 0;
        fileNames[i] = 0;
        fileSizes[i] = 0;
        fileTypes[i] = -1;
        i++;
    }
    
    for (i = 0; i < max_files; i++) {
        ret = osPfsFileState(&pfs[controllerIndex], i, &state);
        if (ret == PFS_ERR_INVALID) {
            fileNames[i] = 0;
            continue;
        }
        
        if (ret != 0) {
            start_reading_controller_data(controllerIndex);
            return CONTROLLER_PAK_BAD_DATA;
        }
        
        string_to_font_codes((u8 *)&state.game_name, (u8 *)fileNames[i], PFS_FILE_NAME_LEN);
        string_to_font_codes((u8 *)&state.ext_name, (u8 *)fileExtensions[i], PFS_FILE_EXT_LEN);
        fileSizes[i] = state.file_size;
        fileTypes[i] = 6; // Unknown file type? Possibly from another game?
        
        if ((state.game_code == gameCode) && (state.company_code == COMPANY_CODE)) {
            fileTypes[i] = get_file_type(controllerIndex, i);
        }
    }
    
    start_reading_controller_data(controllerIndex);
    return CONTROLLER_PAK_GOOD;
}

//Free D_800DE440
void func_80076164(void) {
    if (D_800DE440 != 0) {
        free_from_memory_pool(D_800DE440);
    }
    D_800DE440 = 0;
}

//Get Available Space in Controller Pak
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
s32 copy_controller_pak_data(s32 controllerIndex, s32 fileNumber, s32 secondControllerIndex) {
    UNUSED s32 pad;
    u8 fileName[PFS_FILE_NAME_LEN];
    UNUSED s32 pad2;
    u8 fileExt[PFS_FILE_EXT_LEN];
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

    alloc = allocate_from_main_pool_safe(state.file_size, COLOR_TAG_BLACK);

    status = read_data_from_controller_pak(controllerIndex, fileNumber, alloc, state.file_size);
    start_reading_controller_data(controllerIndex);
    if (status != CONTROLLER_PAK_GOOD) {
        free_from_memory_pool(alloc);
        return (controllerIndex << 30) | status;
    }

    string_to_font_codes((u8 *)&state.game_name, fileName, PFS_FILE_NAME_LEN);
    string_to_font_codes((u8 *)&state.ext_name, fileExt, PFS_FILE_EXT_LEN);

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
s32 get_file_number(s32 controllerIndex, u8 *fileName, u8 *fileExt, s32 *fileNumber) {
    u32 gameCode;
    u8 fileNameAsFontCodes[PFS_FILE_NAME_LEN];
    UNUSED s32 pad;
    u8 fileExtAsFontCodes[PFS_FILE_EXT_LEN];
    UNUSED s32 pad2;
    s32 ret;

    func_80076A38(fileName, fileNameAsFontCodes, PFS_FILE_NAME_LEN);
    func_80076A38(fileExt, fileExtAsFontCodes, PFS_FILE_EXT_LEN);

    if (get_language() == JAPANESE) {
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

s32 read_data_from_controller_pak(s32 controllerIndex, s32 fileNum, u8 *data, s32 dataLength) {
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
s32 write_controller_pak_file(s32 controllerIndex, s32 fileNumber, u8 *fileName, u8 *fileExt, u8 *dataToWrite, s32 fileSize) {
    s32 temp;
    u8 fileNameAsFontCodes[PFS_FILE_NAME_LEN];
    UNUSED s32 temp2;
    u8 fileExtAsFontCodes[PFS_FILE_EXT_LEN];
    s32 ret;
    s32 file_number;
    s32 bytesToSave;
    u32 game_code;

    ret = get_si_device_status(controllerIndex);
    if (ret != 0) {
        start_reading_controller_data(controllerIndex);
        return ret;
    }

    bytesToSave = fileSize;
    temp = fileSize & 0xFF;
    if (temp != 0) {
        bytesToSave = (fileSize - temp) + 0x100;
    }

    func_80076A38(fileName, fileNameAsFontCodes, PFS_FILE_NAME_LEN);
    func_80076A38(fileExt, fileExtAsFontCodes, PFS_FILE_EXT_LEN);

    if (get_language() == JAPANESE) {
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
            }
            else {
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
s32 get_file_size(s32 controllerIndex, s32 fileNum, s32 *fileSize) {
    OSPfsState state;

    *fileSize = 0;
    if (osPfsFileState(&pfs[controllerIndex], fileNum, &state) == 0) {
        *fileSize = state.file_size;
        return CONTROLLER_PAK_GOOD;
    }
    return CONTROLLER_PAK_BAD_DATA;
}

//Converts strings into N64 Font codes for controller pak file names
u8 *string_to_font_codes(u8 *inString, u8 *outString, s32 stringLength) {
    s32 index = *inString;
    u8 *ret = outString;

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

//Seems to be the same as above, with maybe minor changes
//I think it gets the index value of the fontCode rather that the value?
u8 *func_80076A38(u8 *inString, u8 *outString, s32 stringLength) {
    s32 i;
    u8 currentChar;
    u8 *ret = outString;

    while (*inString != 0 && stringLength != 0) {
        *outString = 0;
        for (i = 0; i != 0x41; i++) {
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
 * 3 = GAMD / Game Data
 * 4 = TIMD / Time Data
 * 5 = GHSS / Ghost Data
 * 6 = Unknown? Possibly from another game?
 */
s32 get_file_type(s32 controllerIndex, s32 fileNum) {
    s32 *data;
    UNUSED s32 pad;
    s32 ret;

    ret = 6;
    data = allocate_from_main_pool_safe(0x100, COLOR_TAG_BLACK);
    if (read_data_from_controller_pak(controllerIndex, fileNum, (u8 *)data, 0x100) == CONTROLLER_PAK_GOOD) {
        switch (*data) {
            case GAMD:
                ret = 3;
                break;
            case TIMD:
                ret = 4;
                break;
            case GHSS:
                ret = 5;
                break;
            default:
                ret = 6;
                break;
        }
    }
    free_from_memory_pool(data);
    return ret;
}
