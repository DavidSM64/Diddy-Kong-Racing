#ifndef _GAME_UI_H_
#define _GAME_UI_H_

#include "types.h"
#include "structs.h"
#include <ultra64.h>

#define ASSET_MASK_MODEL       0x0000
#define ASSET_MASK_OBJECT      0x4000
#define ASSET_MASK_SPRITE      0x8000
#define ASSET_MASK_TEXTURE     0xC000

#define ASSET_MASK_TEX2D       0x0000
#define ASSET_MASK_TEX3D       0x8000

#define HUD_EGG_TOTAL 3

typedef enum RaceFinishStages {
    HUD_RACEFINISH_MUTE,
    HUD_RACEFINISH_TEXT_IN,
    HUD_RACEFINISH_TEXT_OUT,
    HUD_RACEFINISH_IDLE
} RaceFinishStages;

typedef enum TimeTrialFinishStages {
    TIMETRIAL_FINISH_INIT,  // Init necessary vars, then advance.
    TIMETRIAL_FINISH_IN,    // Slide in the text.
    TIMETRIAL_FINISH_SHOW,  // Keep the text onscreen for a few seconds.
    TIMETRIAL_FINISH_OUT,   // Slide out the text.
    TIMETRIAL_FINISH_IDLE,  // Text is offscreen, reset a few vars then advance.
    TIMETRIAL_FINISH_IDLE_2 // Do nothing.
} TimeTrialFinishStages;

typedef enum WrongWayStages {
    WRONGWAY_HIDE,
    WRONGWAY_SHOW
} WrongWayStages;

typedef enum LapTextStages {
    LAPTEXT_IDLE,
    LAPTEXT_UNK1,
    LAPTEXT_UNK2,
    LAPTEXT_UNK3
} LapTextStages;

typedef enum LapTextDirection {
    LAPTEXT_IN = -1,
    LAPTEXT_OUT = 1
} LapTextDirection;

// Consistently inconsistent, courtesy of Rare.
typedef enum WrongWayDirection {
    WRONGWAY_OUT = -1,
    WRONGWAY_IN = 1
} WrongWayDirection;



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

enum HudTypes {
    HUD_RACE_POSITION,
    HUD_RACE_POSITION_END,
    HUD_WEAPON_DISPLAY,
    HUD_LAP_COUNT_LABEL,
    HUD_LAP_COUNT_CURRENT,
    HUD_LAP_COUNT_SEPERATOR,
    HUD_LAP_COUNT_TOTAL,
    HUD_BANANA_COUNT_ICON_SPIN,
    HUD_BANANA_COUNT_NUMBER_1,
    HUD_BANANA_COUNT_NUMBER_2,
    HUD_RACE_TIME_LABEL,
    HUD_RACE_TIME_NUMBER,
    HUD_RACE_START_GO,
    HUD_RACE_START_READY,
    HUD_RACE_END_FINISH,
    HUD_MINIMAP_MARKER,
    HUD_LAP_COUNT_FLAG,
    HUD_MAGNET_RETICLE,
    HUD_BANANA_COUNT_X,
    HUD_BALLOON_COUNT_ICON,
    HUD_BALLOON_COUNT_X,
    HUD_BALLOON_COUNT_NUMBER_1,
    HUD_BALLOON_COUNT_NUMBER_2,
    HUD_LAP_TIME_TEXT,
    HUD_TIME_TRIAL_LAP_TEXT,
    HUD_TIME_TRIAL_LAP_NUMBER,
    HUD_STOPWATCH_HANDS,
    HUD_BANANA_COUNT_ICON_STATIC,
    HUD_BANANA_COUNT_SPARKLE,
    HUD_LAP_TEXT_FINAL,
    HUD_LAP_TEXT_LAP,
    HUD_LAP_TEXT_TWO,
    HUD_TREASURE_METRE,
    HUD_COURSE_ARROWS,
    HUD_STOPWATCH,
    HUD_WRONGWAY_1,
    HUD_WRONGWAY_2,
    HUD_PRO_AM_LOGO,
    HUD_SPEEDOMETRE_ARROW,
    HUD_SPEEDOMETRE_0,
    HUD_SPEEDOMETRE_30,
    HUD_SPEEDOMETRE_60,
    HUD_SPEEDOMETRE_90,
    HUD_SPEEDOMETRE_120,
    HUD_SPEEDOMETRE_150,
    HUD_SPEEDOMETRE_BG,
    HUD_SILVER_COIN_TALLY,
    HUD_CHALLENGE_FINISH_POS_1,
    HUD_CHALLENGE_FINISH_POS_2,
    HUD_WEAPON_QUANTITY,
    HUD_CHALLENGE_PORTRAIT,
    HUD_EGG_CHALLENGE_ICON,
    HUD_BATTLE_BANANA_ICON,
    HUD_BATTLE_BANANA_X,
    HUD_BATTLE_BANANA_COUNT_1,
    HUD_BATTLE_BANANA_COUNT_2,
    HUD_RACE_FINISH_POS_1,
    HUD_TWO_PLAYER_ADV_PORTRAIT,
    HUD_RACE_FINISH_POS_2,

    HUD_ELEMENT_COUNT
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
    HUD_ASSET_NUMBERS,
    HUD_ASSET_NUMBERS_SMALL,
    HUD_ASSET_SEPERATOR,
    HUD_ASSET_SEPERATOR_SMALL,
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

typedef struct HudElement_ChallengeEggs {
    s8 alphaTimer;      // Counts up, wrapping between s8 bounds, used for setting the alpha.
} HudElement_ChallengeEggs;

typedef struct HudElement_RaceStartGo {
    s8 musicStartTimer[4];  // Counts up to 60 frames (1 second) before starting the music
} HudElement_RaceStartGo;

typedef struct HudElement_BananaCountIconSpin {
    s8 spinCounter;     // Number of remaining times the icon will spin
    s8 visualCounter;   // Previously known banana value.
} HudElement_BananaCountIconSpin;

typedef struct HudElement_BananaCountSparkle {
    s8 sparkleTimer;    // Delay timer before starting a new sparkle
    s8 sparkleCounter;  // Number of remaining times the icon will sparkle
} HudElement_BananaCountSparkle;

typedef struct HudElement_SilverCoinTally {
    s8 soundPlayed;     // Whether the sound has been played
    s8 soundTimer;      // Delay timer before playing the sound
    s8 offsetY;         // Offset for the hud, utilised for two players.
} HudElement_SilverCoinTally;

typedef struct HudElement_RaceFinishPos {
    s8 status;          // Which behaviour to do
    s8 textOutTimer;    // Delay timer in frames, increases ticks at 120 before getting set to -120
    s8 textOutTicks;    // Number of times delay timer has reached 120. This is because the timer is only 8 bits.
    s8 targetPos;       // Target X offset for the element;
} HudElement_RaceFinishPos;

typedef struct HudElement_RacePosition {
    s8 active;          // Whether the scale effect is active.
    s8 scaleCounter;    // Ranges from -128 to 127, plus 129 then multiplied to 127 to get a 16 bit range for the trig func.
    s8 baseScale;       // The initial scale value used. Lets you have smaller baseline scales.
} HudElement_RacePosition;

typedef struct HudElement_LapCountFlag {
    s8 visualCounter;   // Counter that sets the sprite offset when above 6.
} HudElement_LapCountFlag;

typedef struct HudElement_LapText {
    s8 status;          // Which behaviour to do
    s8 direction;       // Direction to slide the text
    s8 targetPos;       // Target X offset for the element
    s8 soundPlayed;     // Whether the sound has been played
} HudElement_LapText;

typedef struct HudElement_Timer {
    s8 minutes;         // Minutes elapsed
    s8 seconds;         // Seconds elapsed
    s8 hundredths;      // Hundredths of a second elapsed
    s8 unk1D;
} HudElement_Timer;

typedef struct HudElement_FinishText {
    s8 status;          // Which behaviour to do
    s8 fadeTimer;       // Timer that signals sliding the text offscreen when it hits 120
    s8 unk1C;           // Unused
    s8 targetPos;       // Target X offset for the element
} HudElement_FinishText;

typedef struct HudElement_WeaponDisplay {
    s8 hideTimer;       // Value that counts down when having fewer than 3 quantity.
    s8 rotation;        // s8 rotation representation. Wraps from 0-16, then multiplied by 0x1000
    s8 scale;           // s8 scale representation. A new weapon grows larger until reaching full size. Ranges from 0 - 120
    s8 prevLevel;       // Previous known weapon level, for starting the visual effects upon collecting another.
} HudElement_WeaponDisplay;

typedef struct HudElement_RaceTimeLabel {
    s8 hideTimer;       // Counter that's used for having the text flicker.
    s8 hundredths;      // Rounds hundredths to the next tenth, but functionally unused.
} HudElement_RaceTimeLabel;

typedef struct HudElement {
    Vec3s rotation;
    s16 spriteID;
    f32 scale;
    Vec3f pos;
    s16 spriteOffset;
    union {
        u8 filler[4];   // Ensures this union is 6 bytes, since Rare never actually use more than four.
        HudElement_ChallengeEggs challengeEggs;
        HudElement_RaceStartGo raceStartGo;
        HudElement_BananaCountIconSpin bananaCountIconSpin;
        HudElement_BananaCountSparkle bananaCountSparkle;
        HudElement_SilverCoinTally silverCoinTally;
        HudElement_RaceFinishPos raceFinishPos;
        HudElement_RacePosition racePosition;
        HudElement_LapCountFlag lapCountFlag;
        HudElement_LapText lapText;
        HudElement_Timer timer;
        HudElement_FinishText finishText;
        HudElement_WeaponDisplay weaponDisplay;
        HudElement_RaceTimeLabel raceTimeLabel;
    };
    
} HudElement;

// Size: 0x760
typedef struct HudData {
  /* 0x0000 */ HudElement entry[HUD_ELEMENT_COUNT];
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
void hud_main_race(s32 countdown, Object *obj, s32 updateRate);
void hud_main_eggs(s32 countdown, Object *obj, s32 updateRate);
void hud_main_boss(s32 countdown, Object *obj, s32 updateRate);
void hud_main_taj(s32 countdown, Object *obj, s32 updateRate);
void hud_speedometre_reset(void);
void hud_time_trial_message(s16 *playerID);
void hud_sound_play_delayed(u16 soundID, f32 delay, s32 playerIndex);
void hud_sound_stop(u16 soundID, s32 playerIndex);
void minimap_init(LevelModel *model);
s8 hud_setting(void);
void minimap_fade(s32 setting);
void minimap_opacity_set(s32 setting);
void func_800AB1C8(void);
void hud_visibility(u8 setting);
void hud_race_time(Object_Racer *racer, s32 updateRate);
void hud_wrong_way(Object_Racer *obj, s32 updateRate);
void hud_course_arrows(Object_Racer *racer, s32 updateRate);
void hud_main_hub(Object *obj, s32 updateRate);
void hud_render_player(Gfx **dList, MatrixS **mtx, Vertex **vertexList, Object *obj, s32 updateRate);
void hud_weapon(Object *obj, s32 updateRate);
void hud_race_start(s32 countdown, s32 updateRate);
void hud_bananas(Object_Racer *racer, s32 updateRate);
void hud_race_finish_1player(Object_Racer *racer, s32 updateRate);
void hud_speedometre(Object *obj, s32 updateRate);
void hud_lap_count(Object_Racer *racer, s32 updateRate);
void hud_render_general(Gfx **dList, MatrixS **mtx, Vertex **vtx, s32 updateRate);
void hud_init(s32 viewportCount);
void hud_main_battle(s32 countdown, Object *obj, s32 updateRate);
void hud_lives_render(Object_Racer *racer, s32 updateRate);
void hud_free(void);
void hud_stopwatch_face(u8, u8, u8, u8, u8);
void hud_audio_update(s32 updateRate);
void hud_silver_coins(Object_Racer *racer, s32 updateRate);
void hud_magnet_reticle(Object *racerObj);
void hud_time_trial_finish(Object_Racer *racer, s32 updateRate);
void hud_eggs_portrait(Object_Racer *racer, s32 updateRate);
void hud_draw_eggs(Object *racerObj, s32 updateRate);
void hud_race_position(Object_Racer *racer, s32 updateRate);
void hud_main_treasure(s32 countdown, Object *obj, s32 updateRate);
void hud_balloons(Object_Racer *racer);
void hud_treasure(Object_Racer *racer);
void minimap_marker_pos(f32 x, f32 z, f32 angleSin, f32 angleCos, f32 modelAspectRatio);
void hud_timer_render(s32 x, s32 y, s32 minutes, s32 seconds, s32 hundredths, s32 smallFont);
void hud_draw_model(ObjectModel *objModel);

// Non Matching
void hud_element_render(Gfx **dList, MatrixS **mtx, Vertex **vtxList, HudElement *arg3);
void hud_main_time_trial(s32, Object*, s32);
void hud_race_finish_multiplayer(Object_Racer *racer, s32 updateRate);
void func_800A1E48(Object*, s32 updateRate);
void func_8009F034(void);

#endif
