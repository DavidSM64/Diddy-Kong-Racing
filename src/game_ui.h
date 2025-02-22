#ifndef _GAME_UI_H_
#define _GAME_UI_H_

#include "types.h"
#include "structs.h"
#include <ultra64.h>

#define HUD_ELEMENT_MODEL       0x0000
#define HUD_ELEMENT_OBJECT      0x4000
#define HUD_ELEMENT_SPRITE      0x8000
#define HUD_ELEMENT_TEXTURE     0xC000

#define HUD_ELEMENT_COUNT (sizeof(struct HudData) / sizeof(struct HudElement))

#define HUD_EGG_TOTAL 3

enum CourseIndicatorArrows {
    INDICATOR_NONE,
    INDICATOR_LEFT,
    INDICATOR_LEFT_SHARP,
    INDICATOR_LEFT_UTURN,
    INDICATOR_RIGHT,
    INDICATOR_RIGHT_SHARP,
    INDICATOR_RIGHT_UTURN,
    INDICATOR_UP,
    INDICATOR_DOWN,
    INDICATOR_EXCLAMATION
};

enum HudElementNames {
    HUD_ELEMENT_UNK_00,
    HUD_ELEMENT_UNK_01,
    HUD_ELEMENT_UNK_02,
    HUD_ELEMENT_UNK_03,
    HUD_ELEMENT_UNK_04,
    HUD_ELEMENT_UNK_05,
    HUD_ELEMENT_UNK_06,
    HUD_ELEMENT_UNK_07,
    HUD_ELEMENT_UNK_08,
    HUD_ELEMENT_UNK_09,
    HUD_ELEMENT_UNK_0A,
    HUD_ELEMENT_UNK_0B,
    HUD_ELEMENT_UNK_0C,
    HUD_ELEMENT_UNK_0D,
    HUD_ELEMENT_UNK_0E,
    HUD_ELEMENT_UNK_0F,
    HUD_ELEMENT_UNK_10,
    HUD_ELEMENT_UNK_11,
    HUD_ELEMENT_UNK_12,
    HUD_ELEMENT_UNK_13,
    HUD_ELEMENT_UNK_14,
    HUD_ELEMENT_UNK_15,
    HUD_ELEMENT_UNK_16,
    HUD_ELEMENT_UNK_17,
    HUD_ELEMENT_UNK_18,
    HUD_ELEMENT_UNK_19,
    HUD_ELEMENT_UNK_1A,
    HUD_ELEMENT_UNK_1B,
    HUD_ELEMENT_UNK_1C,
    HUD_ELEMENT_UNK_1D,
    HUD_ELEMENT_UNK_1E,
    HUD_ELEMENT_UNK_1F,
    HUD_ELEMENT_UNK_20,
    HUD_ELEMENT_UNK_21,
    HUD_ELEMENT_UNK_22,
    HUD_ELEMENT_UNK_23,
    HUD_ELEMENT_UNK_24,
    HUD_ELEMENT_UNK_25,
    HUD_ELEMENT_UNK_26,
    HUD_ELEMENT_UNK_27
};

enum HudAssets {
    HUD_ASSET_0,
    HUD_SPRITE_WEAPONS,
    HUD_ASSET_2,
    HUD_ASSET_3,
    HUD_ASSET_4,
    HUD_SPRITE_FINISH,
    HUD_ASSET_6,
    HUD_SPRITE_GO_BIG,
    HUD_SPRITE_BANANA_ANIM,
    HUD_ASSET_9,
    HUD_ASSET_10,
    HUD_ASSET_11,
    HUD_ASSET_12,
    HUD_ASSET_13,
    HUD_SPRITE_MAP_DOT,
    HUD_ASSET_15,
    HUD_SPRITE_CHEQUER_FLAG,
    HUD_SPRITE_RETICLE,
    HUD_ASSET_18,
    HUD_SPRITE_GOLD_BALLOON,
    HUD_ASSET_20,
    HUD_SPRITE_BANANA_STATIC,
    HUD_SPRITE_GET_READY,
    HUD_ASSET_23,
    HUD_SPRITE_LAP_FINAL,
    HUD_SPRITE_LAP_LAP,
    HUD_SPRITE_LAP_2,
    HUD_SPRITE_MAP_ARROW,
    HUD_ASSET_28,
    HUD_SPRITE_INDICATOR_EXCLAMATION,
    HUD_SPRITE_INDICATOR_DOWN,
    HUD_SPRITE_INDICATOR_U,
    HUD_SPRITE_INDICATOR_TURN_90,
    HUD_SPRITE_INDICATOR_TURN_45,
    HUD_ASSET_34,
    HUD_SPRITE_WRONG,
    HUD_SPRITE_WAY,
    HUD_SPRITE_GO_SMALL,
    HUD_SPRITE_LAP_LAP_SMALL,
    HUD_SPRITE_GET_READY_SMALL,
    HUD_SPRITE_PRO_AM,
    HUD_SPRITE_LAP_FINAL_SMALL,
    HUD_SPRITE_FINISH_SMALL,
    HUD_SPRITE_LAP_2_SMALL,
    HUD_SPRITE_WAY_SMALL,
    HUD_SPRITE_WRONG_SMALL,
    HUD_SPRITE_SPEEDOMETRE_ARROW,
    HUD_ASSET_47,
    HUD_ASSET_48,
    HUD_ASSET_49,
    HUD_ASSET_50,
    HUD_ASSET_51,
    HUD_ASSET_52,
    HUD_ASSET_53,
    HUD_ASSET_54,
    HUD_SPRITE_WEAPON_NUMBER,
    HUD_SPRITE_PORTRAIT,
    HUD_ASSET_57,
    HUD_ASSET_58,
    HUD_ASSET_59,
    HUD_ASSET_60,
    HUD_ASSET_61,
    HUD_ASSET_62,
    HUD_ASSET_63,
    HUD_ASSET_64,
    HUD_ASSET_65,
    HUD_ASSET_66,
    HUD_SPRITE_PLACE_1,
    HUD_SPRITE_PLACE_ST,
    HUD_SPRITE_BALLOON_DIAMOND
};

typedef struct HudElementBase {
    s16 y_rotation;
    s16 x_rotation;
    s16 z_rotation;
    s16 spriteID;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    s16 spriteOffset;
} HudElementBase;

typedef struct HudElement {
    s16 y_rotation;
    s16 x_rotation;
    s16 z_rotation;
    s16 spriteID;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    s16 spriteOffset;
    s8 unk1A;
    s8 unk1B;
    s8 unk1C;
    s8 unk1D;
    s8 unk1E;
    s8 unk1F;
} HudElement;

typedef struct HudElementArray {
    s16 y_rotation;
    s16 x_rotation;
    s16 z_rotation;
    s16 spriteID;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    s16 spriteOffset;
    s8 unk1A[6];
} HudElementArray;

// Size: 0x760
typedef struct HudData {
  /* 0x0000 */ HudElement racePostion;
  /* 0x0020 */ HudElement racePositionEnd;
  /* 0x0040 */ HudElement weaponDisplay;
  /* 0x0060 */ HudElement lapCountLabel;
  /* 0x0080 */ HudElement lapCountCurrent;
  /* 0x00A0 */ HudElement lapCountSeperator;
  /* 0x00C0 */ HudElement lapCountTotal;
  /* 0x00E0 */ HudElement bananaCountIconSpin;
  /* 0x0100 */ HudElement bananaCountNumber1;
  /* 0x0120 */ HudElement bananaCountNumber2;
  /* 0x0140 */ HudElement raceTimeLabel;
  /* 0x0160 */ HudElement raceTimeNumber;
  /* 0x0180 */ HudElementArray raceStartGo;
  /* 0x01A0 */ HudElement raceStartReady;
  /* 0x01C0 */ HudElement raceEndFinish;
  /* 0x01E0 */ HudElement minimapMarker;
  /* 0x0200 */ HudElement lapCountFlag;
  /* 0x0200 */ HudElement magnetReticle;
  /* 0x0240 */ HudElement bananaCountX;
  /* 0x0260 */ HudElement balloonCountIcon;
  /* 0x0280 */ HudElement balloonCountX;
  /* 0x02A0 */ HudElement balloonCountNumber1;
  /* 0x02C0 */ HudElement balloonCountNumber2;
  /* 0x02E0 */ HudElement lapTimeText;
  /* 0x0300 */ HudElement timeTrialLapText;
  /* 0x0320 */ HudElement timeTrialLapNumber;
  /* 0x0340 */ HudElement stopwatchHands;
  /* 0x0360 */ HudElement bananaCountIconStatic;
  /* 0x0380 */ HudElement bananaCountSparkle;
  /* 0x03A0 */ HudElement lapTextFinal;
  /* 0x03C0 */ HudElement lapTextLap;
  /* 0x03E0 */ HudElement lapTextTwo;
  /* 0x03E0 */ HudElement treasureMetre;
  /* 0x0440 */ HudElement courseArrows;
  /* 0x0440 */ HudElement stopwatch;
  /* 0x0460 */ HudElement wrongWay1;
  /* 0x0480 */ HudElement wrongWay2;
  /* 0x04A0 */ HudElement unk4A0;
  /* 0x04C0 */ HudElement speedometreArrow;
  /* 0x04E0 */ HudElement speedometreNumber0;
  /* 0x0500 */ HudElement speedometreNumber30;
  /* 0x0520 */ HudElement speedometreNumber60;
  /* 0x0540 */ HudElement speedometreNumber90;
  /* 0x0560 */ HudElement speedometreNumber120;
  /* 0x0580 */ HudElement speedometreNumber150;
  /* 0x05A0 */ HudElement speedometreBG;
  /* 0x05C0 */ HudElement silverCoinTally;
  /* 0x05E0 */ HudElement challengeFinishPosition1;
  /* 0x0600 */ HudElement challengeFinishPosition2;
  /* 0x0620 */ HudElement weaponQuantity;
  /* 0x0640 */ HudElement challengePortrait;
  /* 0x0660 */ HudElement eggChallengeIcon;
  /* 0x0680 */ HudElement battleBananaIcon;
  /* 0x06A0 */ HudElement battleBananaX;
  /* 0x06C0 */ HudElement battleBananaCount1;
  /* 0x06E0 */ HudElement battleBananaCount2;
  /* 0x0700 */ HudElement raceFinishPosition1;
  /* 0x0720 */ HudElement twoPlayerAdvPortrait;
  /* 0x0740 */ HudElement raceFinishPosition2;
} HudData;

/* Size: 0x10 bytes */
typedef struct HudAudio {
    u16 soundID;
    u8 volume;
    s8 volumeRamp;
    SoundMask *soundMask;
    s32 unk8;
    s8 playerIndex;
    s8 unkD;
    s8 unkE;
    s8 unkF;
} HudAudio;

typedef struct HudElements {
    void *entry[HUD_ELEMENT_COUNT];
} HudElements;

extern u8 gGfxTaskYieldData[OS_YIELD_DATA_SIZE];

u8 race_starting(void);
void hud_audio_init(void);
void render_hud_race(s32 countdown, Object *obj, s32 updateRate);
void render_hud_challenge_eggs(s32 countdown, Object *obj, s32 updateRate);
void render_hud_race_boss(s32 countdown, Object *obj, s32 updateRate);
void render_hud_taj_race(s32 countdown, Object *obj, s32 updateRate);
void hud_speedometre_reset(void);
void play_time_trial_end_message(s16 *playerID);
void hud_sound_play_delayed(u16 soundID, f32 delay, s32 playerIndex);
void hud_sound_stop(u16 soundID, s32 playerIndex);
void minimap_init(LevelModel *model);
s8 get_hud_setting(void);
void minimap_fade(s32 setting);
void minimap_opacity_set(s32 setting);
void func_800AB1C8(void);
void hud_visibility(u8 setting);
void render_race_time(Object_Racer *racer, s32 updateRate);
void render_wrong_way_text(Object_Racer *obj, s32 updateRate);
void render_course_indicator_arrows(Object_Racer *racer, s32 updateRate);
void render_hud_hubworld(Object *obj, s32 updateRate);
void render_hud(Gfx **dList, MatrixS **mtx, Vertex **vertexList, Object *obj, s32 updateRate);
void render_weapon_hud(Object *obj, s32 updateRate);
void render_race_start(s32 countdown, s32 updateRate);
void render_racer_bananas(Object_Racer *racer, s32 updateRate);
void render_race_finish_position(Object_Racer *racer, s32 updateRate);
void render_speedometer(Object *obj, s32 updateRate);
void render_lap_count(Object_Racer *racer, s32 updateRate);
void render_minimap_and_misc_hud(Gfx **dList, MatrixS **mtx, Vertex **vtx, s32 updateRate);
void init_hud(s32 viewportCount);
void render_hud_battle(s32 countdown, Object *obj, s32 updateRate);
void hud_draw_lives(Object_Racer *racer, s32 updateRate);
void free_hud(void);
void set_stopwatch_face(u8, u8, u8, u8, u8);
void hud_audio_update(s32 updateRate);
void render_silver_coin_counter(Object_Racer *racer, s32 updateRate);
void render_magnet_reticle(Object *racerObj);
void render_time_trial_finish(Object_Racer *racer, s32 updateRate);
void hud_eggs_portrait(Object_Racer *racer, s32 updateRate);
void hud_draw_eggs(Object *racerObj, s32 updateRate);
void render_race_position(Object_Racer *racer, s32 updateRate);
void render_hud_banana_challenge(s32 countdown, Object *obj, s32 updateRate);
void render_balloon_count(Object_Racer *racer);
void render_treasure_hud(Object_Racer *racer);
void minimap_marker_pos(f32 x, f32 z, f32 angleSin, f32 angleCos, f32 modelAspectRatio);
void render_timer(s32 x, s32 y, s32 minutes, s32 seconds, s32 hundredths, s32 smallFont);
void hud_draw_model(ObjectModel *objModel);

// Non Matching
void func_800AA600(Gfx **dList, MatrixS **mtx, Vertex **vtxList, HudElement *arg3);
void func_800A277C(s32, Object*, s32);
void func_800A6254(Object_Racer *racer, s32 updateRate);
void func_800A1E48(Object*, s32 updateRate);
void func_8009F034(void);

#endif
