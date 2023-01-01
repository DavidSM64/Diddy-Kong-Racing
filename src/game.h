#ifndef _UNKNOWN_06B2B0_H_
#define _UNKNOWN_06B2B0_H_

#include "types.h"
#include "video.h"
#include "structs.h"
#include "fade_transition.h"
#include "libc/math.h"
#include "racer.h"

extern Gfx *gDisplayLists[2];
extern s32 sLogicUpdateRate;

enum RenderContext {
    DRAW_INTRO = -1,
    DRAW_GAME,
    DRAW_MENU,
    DRAW_UNK_02,
    DRAW_UNK_03,
    DRAW_UNK_04,
    DRAW_CRASH_SCREEN
};

/* Size: 6 bytes */
typedef struct unk8012117C {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s16 unk4;
} unk8012117C;

enum NumberOfPlayers {
    ZERO_PLAYERS  = -1, // A.I. Only
    ONE_PLAYER    = 0,
    TWO_PLAYERS   = 1,
    THREE_PLAYERS = 2,
    FOUR_PLAYERS  = 3
};

extern s8  gCurrentDefaultVehicle;
extern u8  D_800DD318;
extern s32 gIsInRace;
extern s32 gFunc80068158Checksum;
extern s32 gFunc80068158Length;
extern s16 D_800DD328;
extern s16 D_800DD32C;

extern s8 D_800DD330;

extern s8  sAntiPiracyTriggered;
extern s32 D_800DD378;
extern s32 D_800DD37C;
extern s32 gScreenStatus;
extern s32 sControllerStatus;
extern s32 D_800DD388;
extern s8  gSkipGfxTask;
extern s8  D_800DD390;
extern s16 gLevelLoadTimer;
extern s8  D_800DD398;
extern s8  D_800DD39C;
extern s8  D_800DD3A0;
extern s32 D_800DD3A4;
extern s32 D_800DD3A8;
extern s32 D_800DD3AC;


extern s8  gDrawFrameTimer;
extern FadeTransition D_800DD3F4;
extern FadeTransition D_800DD408;
// Unused?
extern FadeTransition D_800DD3FC;

// Unused?
extern char *D_800DD410[3];
extern FadeTransition D_800DD41C;
extern FadeTransition D_800DD424;
extern u16 *gVideoCurrFramebuffer;
extern u16 *gVideoLastFramebuffer;
extern u16 *gVideoLastDepthBuffer;

extern s8 gScreenMode;
extern s8 gScreenPos[2];

void dmacopy_doubleword(s32 videoLastFrameBuffer, s32 VideoCurrFrameBuffer, s32 size);

s16 func_8006ABB4(s32 arg0);
s32 func_8006B018(s8 arg0);
s32 func_8006B054(s8 arg0);
Vehicle get_map_default_vehicle(s32 mapId);
// Returns bitfield with (1 << Vehicle) set for every available vehicle.
s32 get_map_available_vehicles(s32 mapId);
s8 func_8006B14C(s32 mapId);
s8 func_8006B190(s32 mapId);
s32 get_hub_area_id(s32 worldId);
void get_number_of_levels_and_worlds(s32 *outLevelCount, s32 *outWorldCount);
s32 check_if_in_race(void);
void func_8006BD10(f32 arg0);
s32 func_8006BD88(void);
u8 get_current_level_race_type(void);
LevelHeader *get_current_level_header(void);
u8 get_total_level_header_count(void);
char *get_level_name(s32 levelId);
void func_8006BEFC(void);
void func_8006BFC8(s8 *arg0);
void func_8006C164(void);
TempStruct5 *func_8006C18C(void);
s8 func_8006C19C(void);
void func_8006C1AC(s32 levelId, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void func_8006C22C(s32 *levelId, s32 *entranceId, s32 *vehicleId, s32 *cutsceneId);
void func_8006C2E4(void);
s16 func_8006C2F0(void);
s32 func_8006C300(void);
void thread3_main(UNUSED void *unused);
void init_game(void);
void main_game_loop(void);
void func_8006CAE4(s32 arg0, s32 arg1, Vehicle vehicle);
void load_level_2(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId);
void func_8006CC14(void);
void func_8006D8A4(void);
void func_8006D8E0(s32 arg0);
void func_8006D8F0(s32 arg0);
void func_8006D968(s8 *arg0);
s32 get_render_context(void);
UNUSED void func_8006DA1C(s32 arg0);
void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId);
void set_level_default_vehicle(Vehicle arg0);
void func_8006DB20(Vehicle vehicleId);
Vehicle get_level_default_vehicle(void);
void load_level_3(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void func_8006DBE4(void);
void func_8006DC58(s32 arg0);
void load_level_for_menu(s32 levelId, s32 numberOfPlayers, s32 cutsceneId);
void calc_and_alloc_heap_for_settings(void);
void func_8006E5BC(void);
void func_8006E770(Settings *settings, s32 arg1);
void func_8006E994(Settings *settings);
void func_8006EA58(void);
Settings *get_settings(void);
s8 is_game_paused(void);
s8 is_postrace_viewport_active(void);
s32 is_reset_pressed(void);
s32 func_8006EB14(void);
void func_8006EB24(void);
void func_8006EB40(void);
void func_8006EB5C(void);
void func_8006EB78(s32 saveFileIndex);
void func_8006EBA8(void);
void func_8006EBC4(void);
void func_8006EBE0(void);
void func_8006EBFC(void);
void func_8006EC18(s32 arg0);
void func_8006EC48(s32 saveFileIndex);
void func_8006ECAC(s32 arg0);
void func_8006ECC4(void);
void func_8006ECE0(void);
s32 func_8006EFB8(void);
void func_8006F140(s32 arg0);
void func_8006F20C(void);
void func_8006F254(void);
void func_8006F29C(void);
void func_8006F338(s32 arg0);
void func_8006F388(u8 arg0);
void func_8006F398(void);
void func_8006F42C(void);
void pre_intro_loop(void);
s32 is_controller_missing(void);
s32 check_imem_validity(void);
void ingame_logic_loop(s32 updateRate);
void load_level(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void func_8006A6B0(void);

//Non Matching
void func_8006ECFC(s32 numberOfPlayers);
void func_8006DCF8(s32 arg0);
void func_8006EFDC(void);
void func_8006A6B0(void);
void func_80010994(s32 updateRate);

#endif
