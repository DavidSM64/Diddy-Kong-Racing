#ifndef _OBJECT_FUNCTIONS_H_
#define _OBJECT_FUNCTIONS_H_

#include "macros.h"
#include "types.h"
#include "structs.h"
#include "level_object_entries.h"
#include "libc/math.h"

#define WORLD_KEY_GRAB_CHECK_RADIUS 50

#define TIME_JIFFIES_PER_SECOND 60
#define TIME_SECONDS(sec) sec * TIME_JIFFIES_PER_SECOND
#define U8_ANGLE_TO_U16(x) (x << 6 << 4)
#define TEX_INDEX_NO_TEXTURE 0xFF

enum BananaBehaviour {
    BANANA_COLLECTED = -1,
    BANANA_IDLE,
    BANANA_DROPPED
};

enum WeaponBehaviour {
    WEAPON_DROPPED,
    WEAPON_ARMED,
    WEAPON_TRIGGERED,
    WEAPON_DESTROY,
    WEAPON_STATUS_4,
    WEAPON_STATUS_5
};

enum DoorStatus {
    DOOR_CLOSING = -1,
    DOOR_CLOSED,
    DOOR_OPENING
};

enum BossRaceWarps {
    WARP_STANDARD = -1,
    WARP_BOSS_FIRST,
    WARP_BOSS_REMATCH,
};

enum TajBehaviours {
    TAJ_MODE_ROAM,
    TAJ_MODE_APPROACH_PLAYER,
    TAJ_MODE_TURN_TOWARDS_PLAYER,
    TAJ_MODE_GREET_PLAYER,
    TAJ_MODE_DIALOGUE,
    TAJ_MODE_TRANSFORM_BEGIN,
    TAJ_MODE_TRANSFORM_END,
    TAJ_MODE_END_DIALOGUE,
    TAJ_MODE_END_DIALOGUE_CHALLENGE,
    TAJ_MODE_TELEPORT_TO_PLAYER_BEGIN = 10,
    TAJ_MODE_TELEPORT_TO_PLAYER_END,
    TAJ_MODE_SET_CHALLENGE = 15,
    TAJ_MODE_TELEPORT_AWAY_BEGIN = 20,
    TAJ_MODE_TELEPORT_AWAY_END,
    TAJ_MODE_RACE = 30,
    TAJ_MODE_UNK1F
};

enum TTBehaviours {
    TT_MODE_ROAM,
    TT_MODE_APPROACH_PLAYER,
    TT_MODE_TURN_TOWARDS_PLAYER,
    TT_MODE_DIALOGUE,
    TT_MODE_DIALOGUE_END
};

enum SilvereCoinBehaviours {
    SILVER_COIN_ACTIVE,
    SILVER_COIN_COLLECTED,
    SILVER_COIN_COLLECTED_PLAYER_2,
    SILVER_COIN_INACTIVE
};

enum EggPickupStatus {
    EGG_SPAWNED,
    EGG_COLLECTED,
    EGG_MOVING,
    EGG_IN_BASE,
    EGG_HATCHED
};

enum FrogActions {
    FROG_IDLE,
    FROG_HOP,
    FROG_SQUISH,
    FROG_FLAT,
    FROG_UNSQUISH
};

typedef struct unk80034B4C {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0x5E];
    s32 unk78;
} unk80034B4C;

typedef struct unk80035E20 {
    u8 pad0[0x40];
    s32 unk40;
    u8 pad44[0x34];
    s32 unk78;
    s32 unk7C;
} unk80035E20;

typedef struct unk80037578 {
    u8 pad0[0x78];
    s32 unk78;
    s32 unk7C;
} unk80037578;

typedef struct unk80037624 {
    u8 pad0[6];
    s16 unk6;
} unk80037624;

/* Size: 12 bytes */
typedef struct LevelObjectEntry800376E0 {
    LevelObjectEntryCommon common;
    s8 unk8;
    s8 unk9;
    s8 unkA;
} LevelObjectEntry800376E0;

typedef struct unk80037D08_arg0_64 {
    u8 pad0[0x2A];
    s16 unk2A;
} unk80037D08_arg0_64;

typedef struct unk80037D08_arg0 {
    u8 pad0[0x64];
    unk80037D08_arg0_64 *unk64;
} unk80037D08_arg0;

// Not sure if Object_60 differs between objects yet.
typedef struct Object_60_800380F8 {
    s32 unk0;
    Object *unk4;
    s32 pad8;
    Object *unkC;
} Object_60_800380F8;

typedef struct unk80038B74 {
    u8 pad0[8];
    s8 unk8;
} unk80038B74;

typedef struct unk80039160 {
    u8 pad0[0x78];
    s32 unk78;
} unk80039160;

typedef struct unk80039190 {
    u16 unk0;
    u8 pad2[0x76];
    s32 unk78;
    s32 unk7C;
} unk80039190;

typedef struct unk8003CF18 {
    u8 pad1A[0x78];
    f32 unk78;
} unk8003CF18;

typedef struct unk8003D038 {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0x5E];
    s32 unk78;
} unk8003D038;

typedef struct unk8003D3EC {
    u8 pad0[0x18];
    u16 unk18;
} unk8003D3EC;

typedef struct unk8003FC44 {
    s8 unk0;
    s8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s8 unk7;
} unk8003FC44;

typedef struct LevelObjectEntry8003FEF4 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u16 unkA;
    u8 unkC;
    u8 unkD;
    u16 unkE;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} LevelObjectEntry8003FEF4;

typedef struct LevelObjectEntry8004001C {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} LevelObjectEntry8004001C;

typedef struct unk80040800 {
    u8 pad0[0x78];
    f32 unk78;
} unk80040800;

typedef struct unk80042014_arg0_64 {
    u16 unk0;
    u8 unk2;
    u8 unk3;
} unk80042014_arg0_64;

typedef struct unk80042014_arg0 {
    u8 pad0[0x64];
    unk80042014_arg0_64 *unk64;
} unk80042014_arg0;

typedef struct unk80042014_arg1 {
    u8 pad0[8];
    u16 unk8;
    u8 unkA;
    u8 unkB;
} unk80042014_arg1;

typedef struct unk8004210C {
    u8 pad0[0x3C];
    s32 unk3C;
    u8 pad40[0x24];
    s32 unk64;
} unk8004210C;

typedef struct unk80042A1C {
    u8 pad0[0x78];
    f32 unk78;
    s16 unk7C;
    s16 unk7E;
} unk80042A1C;

typedef struct unk80042CD0 {
    u8 pad0[0x18];
    s16 unk18;
} unk80042CD0;

//void rumble_set(s16 obj, u8 arg1);

typedef struct unk80041A90_MidiFade {
    s16 unk0; // Y rotation
    s16 unk2; // X rotation
    s16 unk4; // Z rotation
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} unk80041A90_MidiFade;

typedef struct VertexPosition {
/* 0x00 */ s16 x;
/* 0x02 */ s16 y;
/* 0x04 */ s16 z;
} VertexPosition;

extern Triangle D_800DCAA8[8];
extern VertexPosition D_800DCB28[6];

void obj_init_fireball_octoweapon(Object *obj, LevelObjectEntry_Fireball_Octoweapon *entry);
void obj_init_lasergun(Object *obj, LevelObjectEntry_Lasergun *entry);
void obj_init_laserbolt(Object *obj, LevelObjectEntry_Laserbolt *entry);
void obj_init_torch_mist(Object *obj, LevelObjectEntry_Torch_Mist *entry);
void obj_loop_torch_mist(Object *obj, s32 updateRate);
void obj_init_effectbox(Object *obj, LevelObjectEntry_EffectBox *entry);
void obj_init_trophycab(Object *obj, LevelObjectEntry_TrophyCab *entry);
void obj_init_collectegg(Object *obj, LevelObjectEntry_CollectEgg *entry);
void obj_init_eggcreator(Object *obj, LevelObjectEntry_EggCreator *entry);
void obj_loop_eggcreator(Object *obj, s32 updateRate);
void obj_init_lighthouse_rocketsignpost(Object *obj, LevelObjectEntry_Lighthouse_RocketSignpost *entry);
void obj_loop_rocketsignpost(Object *obj, s32 updateRate);
void obj_init_airzippers_waterzippers(Object *obj, LevelObjectEntry_AirZippers_WaterZippers *entry);
void obj_init_timetrialghost(Object *obj, LevelObjectEntry_TimeTrial_Ghost *entry);
void obj_loop_timetrialghost(Object *obj, s32 updateRate);
void obj_init_characterflag(Object *obj, LevelObjectEntry_CharacterFlag *entry);
void obj_loop_characterflag(Object *obj, s32 updateRate);
void obj_init_stopwatchman(Object *obj, LevelObjectEntry_StopWatchMan *entry);
void play_tt_voice_clip(u16 soundID, s32 interrupt);
void obj_init_lavaspurt(Object *obj, LevelObjectEntry_LavaSpurt *entry);
void obj_init_posarrow(Object *obj, LevelObjectEntry_PosArrow *entry);
void obj_init_animator(Object *obj, LevelObjectEntry_Animator *entry, s32 param);
void obj_loop_animobject(Object *obj, s32 updateRate);
void obj_loop_dooropener(Object *obj, s32 updateRate);
void obj_init_overridepos(Object *obj, LevelObjectEntry_OverridePos *entry);
void func_80037D60(s32 arg0, s32 arg1);
void obj_init_wizpigship(Object *obj, LevelObjectEntry_WizpigShip *entry);
void obj_init_hittester(Object *obj, LevelObjectEntry_HitTester *entry);
void obj_loop_hittester(Object *obj, s32 updateRate);
void obj_init_dynamic_lighting_object(Object *obj, LevelObjectEntry_DynamicLightingObject *entry);
void obj_init_unknown96(Object *obj, LevelObjectEntry_Unknown96 *entry);
void obj_init_snowball(Object *obj, LevelObjectEntry_Snowball *entry);
void func_80038330(s32 arg0, s32 arg1);
void obj_loop_animcamera(Object *obj, s32 updateRate);
void func_800387C0(s32 arg0, s32 arg1);
void obj_loop_animcar(Object *obj, s32 updateRate);
void obj_init_infopoint(Object *obj, LevelObjectEntry_InfoPoint *entry);
void obj_loop_infopoint(Object *obj, s32 updateRate);
void obj_init_smoke(Object *obj, LevelObjectEntry_Smoke *entry);
void obj_loop_smoke(Object *obj, s32 updateRate);
void obj_init_unknown25(Object *obj, LevelObjectEntry_Unknown25 *entry);
void obj_loop_unknown25(Object *obj, s32 updateRate);
void obj_init_wardensmoke(Object *obj, LevelObjectEntry_WardenSmoke *entry);
void obj_loop_wardensmoke(Object *obj, s32 updateRate);
void obj_init_teleport(Object *obj, LevelObjectEntry_Teleport *entry);
void obj_loop_teleport(Object *obj, s32 updateRate);
void obj_init_exit(Object *obj, LevelObjectEntry_Exit *entry);
void obj_init_cameracontrol(Object *obj, LevelObjectEntry_CameraControl *entry);
void obj_loop_cameracontrol(Object *obj, s32 updateRate);
void obj_init_setuppoint(Object *obj, LevelObjectEntry_SetupPoint *entry);
void obj_loop_setuppoint(Object *obj, s32 updateRate);
void obj_init_dino_whale(Object *obj, LevelObjectEntry_Dino_Whale *entry);
void obj_loop_dino_whale(Object *obj, s32 updateRate);
void obj_init_parkwarden(Object *obj, LevelObjectEntry_Parkwarden *entry);
void set_taj_voice_line(s16 soundID);
void play_taj_voice_clip(u16 soundID, s32 interrupt);
void obj_loop_gbparkwarden(Object *obj, s32 updateRate);
f32 get_npc_pos_y(void);
void obj_init_checkpoint(Object *obj, LevelObjectEntry_Checkpoint *entry, s32 arg2);
void obj_loop_checkpoint(Object *obj, s32 updateRate);
void obj_init_modechange(Object *obj, LevelObjectEntry_ModeChange *entry);
void obj_init_bonus(Object *obj, LevelObjectEntry_Bonus *entry);
void obj_init_ttdoor(Object *obj, LevelObjectEntry_TTDoor *entry);
void obj_init_bridge_whaleramp(Object *obj, LevelObjectEntry_Bridge_WhaleRamp *entry);
void obj_init_rampswitch(Object *obj, LevelObjectEntry_RampSwitch *entry);
void obj_loop_rampswitch(Object *obj, s32 updateRate);
void obj_init_seamonster(Object *obj, LevelObjectEntry_SeaMonster *entry);
void obj_loop_seamonster(Object *obj, s32 updateRate);
void obj_init_fogchanger(Object *obj, LevelObjectEntry_FogChanger *entry);
void obj_init_skycontrol(Object *obj, LevelObjectEntry_SkyControl *entry);
void obj_loop_skycontrol(Object *obj, s32 updateRate);
void obj_init_ainode(Object *obj, LevelObjectEntry_AiNode *entry);
void obj_loop_ainode(Object *obj, s32 updateRate);
void obj_init_treasuresucker(Object *obj, LevelObjectEntry_TreasureSucker *entry);
void obj_init_flycoin(Object *obj, LevelObjectEntry_FlyCoin *entry);
void obj_init_bananacreator(Object *obj, LevelObjectEntry_BananaCreator *entry);
void obj_init_banana(Object *obj, LevelObjectEntry_Banana *entry);
void obj_init_silvercoin_adv2(Object *obj, LevelObjectEntry_SilverCoinAdv2 *entry);
void obj_init_silvercoin(Object *obj, LevelObjectEntry_SilverCoin *entry);
void obj_init_worldkey(Object *obj, LevelObjectEntry_WorldKey *entry);
void obj_loop_worldkey(Object *worldKeyObj, s32 updateRate);
void obj_init_wballoonpop(Object *obj, LevelObjectEntry_WBalloonPop *entry);
void obj_loop_wballoonpop(Object *obj, s32 updateRate);
void obj_init_weapon(Object *obj, LevelObjectEntry_Weapon *entry);
void obj_loop_weapon(Object *obj, s32 updateRate);
void reset_rocket_sound_timer(void);
void decrease_rocket_sound_timer(void);
void obj_init_audioline(Object *obj, LevelObjectEntry_AudioLine *entry);
void obj_init_audioreverb(Object *obj, LevelObjectEntry_AudioReverb *entry);
void obj_init_texscroll(Object *obj, LevelObjectEntry_TexScroll *entry, s32 arg2);
void obj_init_rgbalight(Object *obj, LevelObjectEntry_RgbaLight *entry, s32 arg2);
void obj_init_buoy_pirateship(Object *obj, LevelObjectEntry_Buoy_PirateShip *entry, s32 arg2);
void obj_loop_buoy_pirateship(Object *obj, s32 updateRate);
void obj_init_log(Object *obj, LevelObjectEntry_Log *entry, s32 arg2);
void obj_init_wavegenerator(Object *obj, LevelObjectEntry_WaveGenerator *entry, s32 arg2);
void obj_init_midichset(Object *obj, LevelObjectEntry_Midichset *entry);
void obj_init_bubbler(Object *obj, LevelObjectEntry_Bubbler *entry);
void obj_loop_bubbler(Object *obj, s32 updateRate);
void obj_init_boost(Object *obj, LevelObjectEntry_Boost2 *entry);
void obj_init_unknown94(Object *obj, LevelObjectEntry_Unknown94 *entry, s32 arg2);
void obj_loop_unknown94(Object *obj, s32 updateRate);
void obj_init_rangetrigger(Object *obj, LevelObjectEntry_RangeTrigger *entry);
void obj_loop_rangetrigger(Object *obj, s32 updateRate);
void obj_init_frog(Object *obj, LevelObjectEntry_Frog *entry);
void obj_loop_pigrocketeer(Object *obj, s32 updateRate);
void obj_init_levelname(Object *obj, LevelObjectEntry_LevelName *entry);
void obj_loop_wizghosts(Object *obj, s32 updateRate);
void obj_loop_ttdoor(Object *obj, s32 updateRate);
void obj_loop_trophycab(Object *obj, s32 updateRate);
void obj_loop_wizpigship(Object* wizShipObj, s32 updateRate);
void obj_loop_silvercoin(Object *obj, s32 updateRate);
void obj_loop_bombexplosion(Object *obj, s32 updateRate);
void obj_loop_flycoin(Object *obj, s32 updateRate);
void obj_spawn_effect(f32 x, f32 y, f32 z, s32 objectID, s32 soundID, f32 scale, s32 arg6);
void obj_loop_stopwatchman(Object *obj, s32 updateRate);
void obj_loop_parkwarden(Object *obj, s32 updateRate);
void obj_loop_bridge_whaleramp(Object *obj, s32 updateRate);
void obj_loop_frog(Object *obj, s32 updateRate);
void obj_loop_levelname(Object *obj, s32 updateRate);
void obj_loop_banana(Object *obj, s32 updateRate);
void obj_loop_collectegg(Object *obj, s32 updateRate);
void obj_loop_weather(Object *obj, s32 updateRate);
void obj_init_groundzipper(Object *obj, LevelObjectEntry_GroundZipper *entry);
void obj_init_goldenballoon(Object *obj, LevelObjectEntry_GoldenBalloon *entry);
void obj_init_midifadepoint(Object *obj, LevelObjectEntry_MidiFadePoint *entry);
void obj_loop_trigger(Object *obj, s32 updateRate);
void obj_init_weather(Object *obj, LevelObjectEntry_Weather *entry);
void obj_loop_treasuresucker(Object *obj, s32 updateRate);
void obj_loop_log(Object *obj, s32 updateRate);
void obj_loop_modechange(Object *obj, s32 updateRate);
void obj_loop_bonus(Object *obj, s32 updateRate);
void obj_loop_fireball_octoweapon(Object *obj, s32 updateRate);
void obj_loop_lasergun(Object *obj, s32 updateRate);
void play_rocket_trailing_sound(Object *obj, struct Object_Weapon *weapon, u16 soundID);
void rocket_prevent_overshoot(Object *obj, s32 updateRate, Object_Weapon *rocket);
void homing_rocket_prevent_overshoot(Object *obj, s32 updateRate, Object_Weapon *rocket);
void func_8001F23C(Object *obj, LevelObjectEntry_Animation *animEntry);
void obj_loop_effectbox(Object *obj, s32 updateRate);
void func_8001EE74(void);
void obj_loop_door(Object *doorObj, s32 updateRate);
void obj_loop_fish(Object *fishObj, s32 updateRate);
void obj_loop_weaponballoon(Object *weaponBalloonObj, s32 updateRate);
void obj_loop_char_select(Object *charSelectObj, s32 updateRate);
void weapon_trap(Object *weaponObj, s32 updateRate);
void obj_init_butterfly(Object *butterflyObj, LevelObjectEntry_Butterfly *butterflyEntry, s32 param);
void obj_init_animation(Object *obj, LevelObjectEntry_Animation *entry, s32 arg2);
void obj_init_lensflareswitch(Object *obj, LevelObjectEntry_LensFlareSwitch *entry, UNUSED s32 arg2);
void obj_loop_lavaspurt(Object *obj, s32 updateRate);
void obj_loop_vehicleanim(Object *obj, s32 updateRate);
void obj_loop_snowball(Object *obj, s32 updateRate);
void obj_loop_goldenballoon(Object *obj, s32 updateRate);
void obj_loop_groundzipper(Object *obj, s32 updateRate);
void obj_loop_laserbolt(Object *obj, s32 updateRate);
void obj_loop_posarrow(Object *obj, s32 updateRate);
void obj_loop_bananacreator(Object *obj, s32 updateRate);
void obj_loop_airzippers_waterzippers(Object *obj, s32 updateRate);
void obj_loop_exit(Object *obj, s32 updateRate);
void obj_loop_scenery(Object *obj, s32 updateRate);
void obj_init_trigger(Object *obj, LevelObjectEntry_Trigger *entry);
void obj_init_lensflare(Object *obj, LevelObjectEntry_LensFlare *entry);
void obj_init_weaponballoon(Object *obj, LevelObjectEntry_WeaponBalloon *entry);
void obj_init_door(Object *obj, LevelObjectEntry_Door *entry);
void obj_init_audio(Object *obj, LevelObjectEntry_Audio *entry);
void obj_init_bombexplosion(Object *obj, LevelObjectEntry_BombExplosion *entry);
void obj_init_scenery(Object *obj, LevelObjectEntry_Scenery *entry);
void weapon_projectile(Object *obj, s32 updateRate);
void obj_loop_texscroll(Object *obj, s32 updateRate);
void obj_loop_animator(Object *obj, s32 updateRate);
void calc_env_mapping_for_object(ObjectModel *, s16, s16, s16);
void obj_init_fish(Object *fishObj, LevelObjectEntry_Fish *fishEntry, s32 param);
void obj_init_midifade(Object *obj, LevelObjectEntry_MidiFade *entry);
void obj_loop_butterfly(Object *butterflyObj, s32 updateRate);
s32 ainode_find_nearest(f32 diffX, f32 diffY, f32 diffZ, s32 useElevation);
s32 func_8001CC48(s32, s32, s32);
f32 func_8001C6C4(Object_64 *, Object *, f32, f32, s32);
void func_8000CBF0(Object*, s32);
void try_to_collect_egg(Object *, Object_CollectEgg*);


s32 func_8001F3EC(s32);
s32 func_80021600(s32);

#endif
