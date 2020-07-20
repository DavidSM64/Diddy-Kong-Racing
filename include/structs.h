#ifndef _STRUCTS_H_
#define _STRUCTS_H_

/* Note: Structs are not complete, take them with a grain of salt. */

#include "types.h"

/* Size: 0x20 bytes */
typedef struct MenuElement {
  /* 0x00 */ s16 unk0; // This is something related to position, not sure what though.
  /* 0x02 */ s16 unk2; // This is something related to position, not sure what though.
  /* 0x04 */ s16 screenX;
  /* 0x06 */ s16 screenY;
  /* 0x08 */ s16 unk6;
  /* 0x0A */ s16 unk8;
  /* 0x0C */ u8 filterRed;
  /* 0x0D */ u8 filterGreen;
  /* 0x0E */ u8 filterBlue;
  /* 0x0F */ u8 filterAlpha; // 0 = no filter color, 0xFF = full color.
  /* 0x10 */ u8 opacity;
  /* 0x11 */ u8 textType; 
  /* 0x12 */ u8 textAlignFlags;
  /* 0x13 */ u8 unk13; // Source type? 0 = ascii text, 7 = texture?
  union {
  /* 0x14 */ char* asciiText; // Pointer to ascii text to be displayed on the screen.
  /* 0x14 */ u32* texture;    // Pointer to texture to be displayed on the screen.
  } source;
  /* 0x18 */ u16 backgroundRed;
  /* 0x1A */ u16 backgroundGreen; 
  /* 0x1C */ u16 backgroundBlue;  
  /* 0x1E */ u16 backgroundAlpha; // 0x0000 = No background, 0x00FF = full background color.
} MenuElement;

/* Size: 0x18 bytes */
typedef struct dkr_racer_t {
  /* 0x00 */ u32 trophy_points;
  /* 0x04 */ u8 best_times;
  /* 0x05 */ u8 character;
  /* 0x06 */ u8 starting_position;
  /* 0x07 */ char unk7;
  /* 0x08 */ u16 placements[4];
  /* 0x10 */ u16 course_time;
  /* 0x12 */ u16 lap_times[3];
} dkr_racer_t;

/* Unknown Size */
typedef struct Settings4C {
    u8 unk0;
    u8 unk1;
    u8 pad2[0xD];
    u8 unkF;
} Settings4C;

/* Size: 0x840 bytes */
typedef struct Settings {
  /* 0x0000 */ void *balloonsPtr;
  /* 0x0004 */ s32 *courseFlagsPtr;
  /* 0x0008 */ u16 keys;
  /* 0x000A */ char unkA[2];
  /* 0x000C */ u16 bosses;
  /* 0x000E */ u16 trophies;
  /* 0x0010 */ u32 cutsceneFlags;
  /* 0x0014 */ u16 tajFlags;
  /* 0x0016 */ u8 ttAmulet;
  /* 0x0017 */ u8 wizpigAmulet;
  /* 0x0018 */ void *flapInitialsPtr[3];
  /* 0x0024 */ void *flapTimesPtr[3];
  /* 0x0030 */ void *courseInitialsPtr[3];
  /* 0x003C */ void *courseTimesPtr[3];
  /* 0x0048 */ u8 worldId;
  /* 0x0049 */ u8 courseId;
  /* 0x004A */ u8 playerCount;
  /* 0x004B */ u8 newGame;
  /* 0x004C */ Settings4C *unk4C;
  /* 0x0050 */ u32 filename;
  /* 0x0054 */ dkr_racer_t racers[8];
  /* 0x0114 */ u8 timeTrialRacer;
  /* 0x0115 */ char unk0115[2];
  /* 0x0117 */ u8 display_times;
  /* 0x0118 */ u32 courseFlags[65];
  /* 0x021C */ u16 balloons;
  /* 0x021E */ u16 worldBalloons[5];
  /* 0x0228 */ u16 flapInitials[3][65];
  /* 0x03AE */ u16 flapTimes[3][65];
  /* 0x0534 */ u16 courseInitials[3][65];
  /* 0x06BA */ u16 courseTimes[3][65];
} Settings;

/* Size: 0xC8 bytes */
typedef struct {
  /* 0x00 */ u8 world;
  
  /* 0x01 */ u8 unk1;
  /* 0x02 */ u8 unk2;
  /* 0x03 */ u8 unk3;
  /* 0x04 */ u8 unk4;
  /* 0x05 */ u8 unk5;
  /* 0x06 */ u8 unk6;
  /* 0x07 */ u8 unk7;
             
  /* 0x08 */ f32 course_height;
  
  u32 unkC[10]; // Not an array. Unknown values.

  /* 0x34 */ u16 geometry;
  /* 0x36 */ u16 collectables; // Objects such as bananas, balloons, etc.
  /* 0x38 */ u16 skybox;
  
  /* 0x3A */ u16 unk3A;
  /* 0x3C */ u16 unk3C;

  /* 0x3E */ u16 r; // Fog related
  /* 0x40 */ u16 g;
  /* 0x42 */ u16 b;

  /* 0x4B */ u8 laps;
  /* 0x4C */ u8 race_type;
  /* 0x4D */ u8 vehicle;
  /* 0x4E */ u8 available_vehicles;

  /* 0x4F */ u8 unk4F;
  /* 0x50 */ u8 unk50;
  /* 0x51 */ u8 unk51;
  
  /* 0x52 */ u8 music;
  /* 0x53 */ u8 unk53;
  /* 0x54 */ u16 instruments;
  
  u32 unk58[14]; // Not an array. Unknown values.

  // Weather related?
  /* 0x90 */ u16 weather_enable;
  /* 0x92 */ u16 unk92;
  /* 0x94 */ u8 unk94;
  /* 0x95 */ u8 unk95;
  /* 0x96 */ u16 unk96;
  /* 0x98 */ u16 unk98;
  
  u32 unk9C[11]; // Not an array. Unknown values.

} dkr_level_header_t;

/* Size: 0x50 bytes */
typedef struct {
  /* 0x00 */ u32 unk00;
  /* 0x04 */ u32 unk04;
  /* 0x08 */ u32 unk08;
  /* 0x0C */ f32 unk0C;
  /* 0x10 */ u32 unk10;
  /* 0x14 */ u32 unk14;
  /* 0x18 */ f32 unk18;
  /* 0x1C */ u32 unk1C;
  /* 0x20 */ u32 unk20;
  /* 0x24 */ u32 unk24;
  /* 0x28 */ u32 unk28;
  /* 0x2C */ u32 unk2C;
  /* 0x30 */ u32 unk30;
  /* 0x34 */ u32 unk34;
  /* 0x38 */ u32 unk38;
  /* 0x3C */ u32 unk3C;
  /* 0x40 */ f32 unk40;
  /* 0x44 */ f32 unk44;
  /* 0x48 */ f32 unk48;
  /* 0x4C */ u32 unk4C;
} dkr_wave_t;

  
/* Size: 0x0630 bytes */
typedef struct {
  /* 0x0000 */ u16 y_rotation;
  /* 0x0002 */ u16 x_rotation;
  /* 0x0004 */ u16 z_rotation;
  /* 0x0006 */ u16 unk6;
  /* 0x0008 */ f32 scale;
  /* 0x000C */ f32 x_position;
  /* 0x0010 */ f32 y_position;
  /* 0x0014 */ f32 z_position;
  /* 0x0018 */ u16 unk18;
  /* 0x001A */ u16 unk1A;
  /* 0x001C */ f32 x_velocity;
  /* 0x0020 */ f32 y_velocity;
  /* 0x0024 */ f32 z_velocity;
  /* 0x0028 */ u32 unk28;

  /* 0x002C */ u16 unk2C;
  
  /* 0x002E */ u16 unk2E;
  /* 0x0030 */ f32 unk30;
  /* 0x0034 */ f32 unk34;
  /* 0x0038 */ u8 unk38;

  /* 0x0039 */ u8 unk39;
  /* 0x003A */ u8 unk3A;
  /* 0x003B */ u8 unk3B;
  /* 0x003C */ u8 unk3C;
  
  /* 0x003D */ u8 unk3D;
  /* 0x003E */ u8 unk3E;
  /* 0x003F */ u8 unk3F;

  /* 0x0040 */ void *descriptor_ptr;
  /* 0x0044 */ void *unk44;
  /* 0x0048 */ u16 unk48;
  /* 0x004A */ u16 unk4A;
  /* 0x004C */ void *unk4C; //player + 0x318
  /* 0x0050 */ void *unk50; //player + 0x2F4
  /* 0x0054 */ void *unk54; //player + 0x2C0
  /* 0x0058 */ void *unk58; //player + 0x304
  /* 0x005C */ u32 unk5C;

  /* 0x0060 */ void *unk60; //player + 0x340
  /* 0x0064 */ void *unk64; //player + 0x98
  /* 0x0068 */ void *unk68; //player + 0x80
  /* 0x006C */ void *unk6C; //player + 0x370
  /* 0x0070 */ u32 unk70;

  /* 0x0074 */ u32 unk74;
  /* 0x0078 */ u32 unk78;
  /* 0x007C */ u32 unk7C;

  /* 0x0080 */ void *unk80;
  /* 0x0084 */ u32 unk84;
  /* 0x0088 */ u32 unk88;
  
  /* 0x008C */ u32 unk8C;
  /* 0x0090 */ u32 unk90;
  /* 0x0094 */ u32 unk94;

  /* 0x0098 */ s16 playerIndex; // -1 = AI Controlled, 0 to 3 = Player controlled
  /* 0x009A */ u8 unk9A;
  /* 0x009B */ u8 characterId; // Affects minimap color, horn, voice, etc.
  
  /* 0x009C */ u32 unk9C;

  /* 0x00A0 */ f32 unkA0;
  
  /* 0x00A4 */ u32 unkA4;
  /* 0x00A8 */ u32 unkA8;
  /* 0x00AC */ u32 unkAC;
  /* 0x00B0 */ u32 unkB0;
  /* 0x00B4 */ u32 unkB4;
  /* 0x00B8 */ u32 unkB8;
  /* 0x00BC */ u32 unkBC;
  /* 0x00C0 */ u32 unkc0;
  
  /* 0x00C4 */ f32 velocity;
  /* 0x00C8 */ f32 lateral_velocity;
  
  u32 unkCC[10]; // Not an array. Unknown values.

  /* 0x00F4 */ f32 prev_x_position;
  /* 0x00F8 */ f32 prev_y_position;
  /* 0x00FC */ f32 prev_z_position;
  
  /* 0x0100 */ u32 unk100;
  /* 0x0104 */ u32 unk104;
  /* 0x0108 */ u32 unk108;
  /* 0x010C */ u32 unk10C;

  /* 0x0110 */ f32 unk110;
  /* 0x0114 */ f32 unk114;
  /* 0x0118 */ f32 unk118;
  /* 0x011C */ f32 unk11C;
  /* 0x0120 */ u32 unk120;
  /* 0x0124 */ f32 stretch_height;
  /* 0x0128 */ f32 stretch_height_cap;
  /* 0x012C */ f32 unk12C;
  /* 0x0130 */ u32 unk130;
  /* 0x0134 */ f32 pitch;
  /* 0x0138 */ u32 unk138;
  /* 0x013C */ u32 unk13C;
  /* 0x0140 */ f32 checkpoint_distance;
  /* 0x0144 */ u32 unk144;
  /* 0x0148 */ f32 unk148;
  /* 0x014C */ f32 throttle;
  /* 0x0150 */ f32 brake;
  /* 0x0154 */ u32 unk154;
  /* 0x0158 */ u32 unk158;
  /* 0x015C */ u32 unk15C;
  /* 0x0160 */ f32 unk160;
  /* 0x0164 */ u32 unk164;
  /* 0x0168 */ u32 unk168;
  /* 0x016C */ u32 unk16C;
  /* 0x0170 */ f32 unk170;
  /* 0x0174 */ f32 unk174;
  /* 0x0178 */ f32 unk178;
  /* 0x017C */ f32 unk17C;
  /* 0x0180 */ f32 unk180;
  /* 0x0184 */ f32 unk184;
  /* 0x0188 */ f32 unk188;
  /* 0x018C */ f32 unk18C;
  /* 0x0190 */ f32 unk190;
  /* 0x0194 */ f32 unk194;
  /* 0x0198 */ f32 unk198;
  /* 0x019C */ f32 unk19C;
  
  u32 unk1A0[8]; // Not an array. Unknown values.
  
  /* 0x01C0 */ u32 lap_times[3];
  
  /* 0x01CC */ u32 unk1CC;
  /* 0x01D0 */ u32 unk1D0;
  /* 0x01D4 */ u32 unk1D4;
  /* 0x01D8 */ u32 unk1D8;

  /* 0x01DC */ void *held_obj_ptr;
  
  u32 unk1E0[10]; // Not an array. Unknown values.

  /* 0x0208 */ u16 unk208;
  /* 0x020A */ u8 balloon_type;
  /* 0x020B */ u8 balloon_quantity;
  /* 0x020C */ u8 balloon_level;
  
  /* 0x020D */ u8 unk20D;
  /* 0x020E */ u8 unk20E;
  /* 0x020F */ u8 unk20F;
  /* 0x0210 */ u32 unk210;
  /* 0x0214 */ u32 unk214;
  /* 0x0218 */ u32 unk218;
  /* 0x021A */ u16 unk21A;
  /* 0x021B */ u8 unk21B;

  /* 0x021D */ s8 bananas;
  /* 0x021E */ u8 unk21E;

  /* 0x0270 */ u8 unk270;
  /* 0x0271 */ u8 unk271;
  /* 0x0272 */ u8 unk272;

  /* 0x0273 */ u8 spinout_timer;
  /* 0x0274 */ u8 wheel_surfaces[4];
  
  /* 0x0278 */ u32 unk278;
  /* 0x027C */ u16 unk27C;

  /* 0x027E */ u8 drift_direction;
  /* 0x027F */ u8 unk27F;
  
  /* 0x0280 */ u32 unk280;
  /* 0x0284 */ u8 unk284;

  /* 0x0285 */ s8 squish_timer;
  /* 0x0286 */ u8 unk286;
  /* 0x0287 */ u8 boost_sound;
  /* 0x0288 */ u32 unk288;
  
  /* 0x028C */ u16 unk28C;
  /* 0x028E */ u8 unk28E;

  /* 0x028F */ u8 transparency;
  /* 0x0290 */ u8 indicator_type;
  /* 0x0291 */ s8 indicator_timer;
  /* 0x0292 */ u16 unk292;
  
  u32 unk294[11]; // Not an array. Unknown values.

  /* 0x02C0 */ f32 unk2C0;
  
  /* 0x02C4 */ u8 red;
  /* 0x02C5 */ u8 blue;
  /* 0x02C6 */ u8 green;
  /* 0x02C7 */ u8 alpha;
  
  /* 0x02C8 */ u32 unk2C8;
  /* 0x02CC */ u32 unk2CC;
  /* 0x02D0 */ u32 unk2D0;
  /* 0x02D4 */ u32 unk2D4;
  /* 0x02D8 */ u32 unk2D8;

  /* 0x02DC */ u16 unk2DC;
  /* 0x02DE */ u16 unk2DE;
  /* 0x02E0 */ u16 unk2E0;
  
  /* 0x02E2 */ u16 unk2E2;
  /* 0x02E4 */ u32 unk2E4;

  /* 0x02E8 */ f32 unk2E8;
  /* 0x02EC */ f32 unk2EC;
  /* 0x02F0 */ u32 unk2F0;

  /* 0x02F4 */ f32 shadow_scale;
  /* 0x02F8 */ void *unk2F8;
  /* 0x02FC */ u16 unk2FC;
  /* 0x02FE */ u16 unk2FE;
  /* 0x0300 */ u32 unk300;

  /* 0x0304 */ f32 unk0304;

  /* 0x0308 */ u32 unk308;
  /* 0x030C */ u32 unk30C;
  /* 0x0310 */ u32 unk310;
  /* 0x0314 */ u32 unk314;

  /* 0x0318 */ void *nearest_obj_ptr;
  /* 0x031C */ f32 unk31C;
  /* 0x0320 */ f32 unk320;
  /* 0x0324 */ f32 unk324;
  
  /* 0x0328 */ u32 unk328;
  /* 0x032C */ u32 unk32C;
  /* 0x0330 */ u32 unk330;
  /* 0x0334 */ u32 unk334;
  /* 0x0338 */ u32 unk338;
  /* 0x033C */ u32 unk33C;

  /* 0x0340 */ u32 unk340;
  /* 0x0344 */ void *unk344;
  /* 0x0348 */ void *unk348;
  /* 0x034C */ void *unk34C;
  /* 0x0350 */ void *unk350;
  
  /* 0x0354 */ u32 unk354;
  /* 0x0358 */ u32 unk358;
  /* 0x035C */ u32 unk35C;
  /* 0x0360 */ u32 unk360;
  /* 0x0364 */ u32 unk364;
  /* 0x0368 */ u32 unk368;
  /* 0x036C */ u32 unk36C;

  /* 0x0370 */ void *unk370;
  /* 0x0374 */ s32 unk374;

  u32 unk378[174]; // Not an array. Unknown values.
} dkr_player_t;

#endif
