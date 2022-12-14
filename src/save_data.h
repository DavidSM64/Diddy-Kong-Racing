#ifndef _SAVE_DATA_H_
#define _SAVE_DATA_H_

#include "types.h"
#include "structs.h"
#include "PR/pfs.h"
#include "PR/os_cont.h"

#define GAMD 0x47414D44 // 'GAMD' ASCII - Game Data?
#define TIMD 0x54494D44 // 'TIMD' ASCII - Time Data?
#define GHSS 0x47485353 // 'GHSS' ASCII - Ghosts?

// These are the unique game codes assigned to DKR
#define NDYJ 0x4E44594A // 'NDYJ' ASCII
#define NDYP 0x4E445950 // 'NDYP' ASCII
#define NDYE 0x4E445945 // 'NDYE' ASCII
#define JPN_GAME_CODE NDYJ
#define PAL_GAME_CODE NDYP
#define NTSC_GAME_CODE NDYE

// This is RARE's unique code
#define COMPANY_CODE 0x3459

typedef enum {
    CONTROLLER_PAK_GOOD,
    NO_CONTROLLER_PAK,
    CONTROLLER_PAK_INCONSISTENT,
    CONTROLLER_PAK_WITH_BAD_ID,
    CONTROLLER_PAK_FULL,
    CONTROLLER_PAK_CHANGED,
    CONTROLLER_PAK_UNK6, //Could be another way to mark as full according to tt_menu_loop
    RUMBLE_PAK,
    CONTROLLER_PAK_UNK8, // func_80074B34 Sets this, possibly set in func_800860A8
    CONTROLLER_PAK_BAD_DATA
} SIDeviceStatus;

extern s8 *D_800DE440;
extern u8 gN64FontCodes[68];
extern s32 D_800DE48C;
extern OSPfs pfs[MAXCONTROLLERS];
size_t strlen(const char *str);

u8 func_80072250(s32 arg0);
void func_80072298(u8 arg0);
s32 func_800722E8(s16 arg0);
void func_80072708(void);
s32 get_game_data_file_size(void);
s32 get_time_data_file_size(void);
s32 read_game_data_from_controller_pak(s32 controllerIndex, char *fileExt, Settings *settings);
s32 write_game_data_to_controller_pak(s32 controllerIndex, Settings *arg1);
s32 read_time_data_from_controller_pak(s32 controllerIndex, char *fileExt, Settings *settings);
s32 write_time_data_to_controller_pak(s32 controllerIndex, Settings *arg1);
s32 write_save_data(s32 saveFileNum, Settings *settings);
s32 read_eeprom_data(Settings *arg0, u8 arg1);
s32 write_eeprom_data(Settings *arg0, u8 arg1);
s32 calculate_eeprom_settings_checksum(u64 eepromSettings);
s32 read_eeprom_settings(u64 *eepromSettings);
s32 write_eeprom_settings(u64 *eepromSettings);
s16 calculate_ghost_header_checksum(GhostHeader *ghostHeader);
void func_80074AA8(GhostHeader *ghostHeader, s16 characterID, s16 time, s16 nodeCount, u8 *dest);
s32 func_80074B1C(void);
SIDeviceStatus get_si_device_status(s32 controllerIndex);
s32 start_reading_controller_data(s32 controllerIndex);
SIDeviceStatus check_for_rumble_pak(s32 controllerIndex);
SIDeviceStatus repair_controller_pak(s32 controllerIndex);
SIDeviceStatus reformat_controller_pak(s32 controllerIndex);
s32 get_controller_pak_file_list(s32 controllerIndex, s32 maxNumOfFilesToGet, char **fileNames, char **fileExtensions, u32 *fileSizes, u8 *fileTypes);
void func_80076164(void);
s32 get_free_space(s32 controllerIndex, u32 *bytesFree, s32 *notesFree);
s32 delete_file(s32 controllerIndex, s32 fileNum);
s32 copy_controller_pak_data(s32 controllerIndex, s32 fileNumber, s32 secondControllerIndex);
SIDeviceStatus get_file_number(s32 controllerIndex, char *fileName, char *fileExt, s32 *fileNumber);
SIDeviceStatus read_data_from_controller_pak(s32 controllerIndex, s32 fileNum, u8 *data, s32 dataLength);
SIDeviceStatus write_controller_pak_file(s32 controllerIndex, s32 fileNumber, char *fileName, char *fileExt, u8 *dataToWrite, s32 fileSize);
SIDeviceStatus get_file_size(s32 controllerIndex, s32 fileNum, s32 *fileSize);
char *font_codes_to_string(char *inString, char *outString, s32 stringLength);
s32 get_file_type(s32 controllerIndex, s32 fileNum);
void func_80072578(s16 controllerIndex, s16 arg1, s16 arg2);
void func_80072348(s16 controllerIndex, u8 arg1);
void func_80072424(s16 controllerIndex, u8 arg1, f32 arg2);
void rumble_controllers(s32 arg0);
void init_controller_paks(void);
void func_80072E28(s32 arg0, u32 arg1);
s32 func_80072C54(s32 arg0);
void populate_settings_from_save_data(Settings *settings, u8 *saveData);
s32 func_80074204(s32 saveFileNum, Settings *settings);
void erase_save_file(s32 saveFileNum, Settings *settings);
SIDeviceStatus func_800756D4(s32 controllerIndex, u8 *arg1, u8 *arg2, u8 *arg3, s16 *arg4);
SIDeviceStatus get_file_extension(s32 controllerIndex, s32 fileType, char *fileExt); //Non matching
void func_80073588(Settings *settings, u8 *saveData, u8 arg2);

void func_800738A4(Settings *settings, u8 *saveData);
void func_800732E8(Settings *arg0, u8 *arg1); //Non matching
//Using some context, and best guesses, these could be the names of the variables
s32 func_80074B34(s32 controllerIndex, s16 levelId, s16 vehicleId, u16 *ghostCharacterId, s16 *ghostTime, s16 *ghostNodeCount, GhostHeader *ghostData); //Non matching
char *string_to_font_codes(char *inString, char *outString, s32 stringLength);

//Reasonably certain about these names for now.
s32 func_80074EB8(s32 controllerIndex, s16 arg1, s16 arg2, s16 ghostCharacterId, s16 ghostTime, s16 ghostNodeCount, u8 *dest);
s32 func_80075000(s32 controllerIndex, s16 arg1, s16 arg2, s16 ghostCharacterId, s16 ghostTime, s16 ghostNodeCount, GhostHeader *arg6);
s32 func_800753D8(s32 controllerIndex, s32 arg1);

#endif
