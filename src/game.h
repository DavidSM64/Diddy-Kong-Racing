#ifndef _UNKNOWN_06B2B0_H_
#define _UNKNOWN_06B2B0_H_

#include "types.h"
#include "video.h"
#include "structs.h"
#include "fade_transition.h"
#include "libc/math.h"
#include "racer.h"

extern Gfx *gDisplayLists[2];

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

#ifdef PUPPYPRINT_DEBUG

enum rspFlags {
    RSP_NONE,
    RSP_AUDIO_START,
    RSP_GFX_START,
    RSP_AUDIO_FINISHED,
    RSP_GFX_FINISHED,
    RSP_GFX_PAUSED,
    RSP_GFX_RESUME,
};

enum TrackTimers {
    PP_LOGIC,
    PP_COLLISION,
    PP_OBJECTS,
    PP_RACER,
    PP_LIGHT,
    PP_ENVMAP,
    PP_HUD,
    PP_SCENE,
    PP_DMA,
    PP_PAD,
    PP_TEXT,
    PP_MENU,
    PP_TEXTURES,
    PP_PARTICLES,
    PP_AI,
    PP_WEATHER,
    PP_WAVES,
    PP_DIALOGUE,
    PP_PROFILER,
    PP_TRANSITION,
    PP_CAMERA,
    PP_MATRIX,
    PP_BACKGROUND,
    PP_DECAL,
    PP_BILLBOARD,
    PP_LEVEL,
    PP_OBJGFX,
    PP_VOID,
    PP_SEGMENTS,

    PP_THREAD0,
    PP_THREAD30,
    PP_AUDIO,
    PP_SCHED,

    PP_RSP_GFX,
    PP_RSP_AUD,

    PP_RDP_BUS,
    PP_RDP_BUF,
    PP_RDP_TMM,

    PP_TIMES_TOTAL
};

#define PP_STRINGS \
    {"Unknown"}, \
    {"Collision"}, \
    {"Objects"}, \
    {"Racers"}, \
    {"Lighting"}, \
    {"Envmaps"}, \
    {"HUD\t"}, \
    {"Render"}, \
    {"DMA"}, \
    {"Pad\t"}, \
    {"Text"}, \
    {"Menu"}, \
    {"Textures"}, \
    {"Particles"}, \
    {"AI\t"}, \
    {"Weather"}, \
    {"Water"}, \
    {"Dialogue"}, \
    {"Profiler"}, \
    {"Transition"}, \
    {"Camera"}, \
    {"Matrix"}, \
    {"BG\t"}, \
    {"Decals"}, \
    {"Billboards"}, \
    {"Level Gfx"}, \
    {"Obj Gfx"}, \
    {"Void"}, \
    {"Segments"}, \
    {"Thread0"}, \
    {"Thread30"}, \
    {"Audio"}, \
    {"Sched"},



#define NUM_PERF_ITERATIONS 32
#define PERF_AGGREGATE NUM_PERF_ITERATIONS
#define PERF_TOTAL NUM_PERF_ITERATIONS + 1
typedef u32 PPTimer[NUM_PERF_ITERATIONS + 2];
struct PuppyPrintTimers {
    u32 cpuTime; // Sum of multiple CPU timings, and what will be displayed.
    u32 rspTime; // Sum of multiple RSP timings, and publicly shamed on the street.
    u32 rdpTime; // Sum of multiple RDP timings, and hung by its entrails for all to see.
    u32 rspPauseTime; // Buffer that keeps track of the halt time of the Gfx task.
    u32 rspGfxBufTime; // Buffer that keeps track of the current Gfx task;
    u32 rspAudioBufTime; // Buffer that keeps track of the current Audio task;
    PPTimer timers[PP_TIMES_TOTAL];
};
extern struct PuppyPrintTimers gPuppyTimers;
extern void profiler_update(u32 *time, u32 time2);
extern void puppyprint_update_rsp(u8 flags);
extern void profiler_add(u32 *time, u32 offset);
extern u8 perfIteration;
#endif
extern s32 gAntiAliasing;

extern s8 *D_800DD310;
extern s8  D_800DD314;
extern u8  D_800DD318;
extern s32 D_800DD31C;
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
extern s32 gVideoLastFramebuffer;
extern s32 gVideoLastDepthBuffer;

void func_8006F870(Matrix *, Matrix *); //unknown_070110
void func_800705F8(Matrix *, f32, f32, f32); //From unknown_070110
void func_80070B04(s32 videoLastFrameBuffer, s32 VideoCurrFrameBuffer, s32 size);

s16 func_8006ABB4(s32 arg0);
s32 func_8006B018(s8 arg0);
s32 func_8006B054(s8 arg0);
Vehicle get_map_default_vehicle(MapId mapId);
// Returns bitfield with (1 << Vehicle) set for every available vehicle.
s32 get_map_available_vehicles(MapId mapId);
s8 func_8006B14C(MapId mapId);
s8 func_8006B190(MapId mapId);
MapId get_hub_area_id(s32 worldId);
void get_number_of_levels_and_worlds(s32 *outLevelCount, s32 *outWorldCount);
s32 func_8006B240(void);
void func_8006BD10(f32 arg0);
MapId func_8006BD88(void);
u8 get_current_level_race_type(void);
LevelHeader *get_current_level_header(void);
u8 get_total_level_header_count(void);
u8 *get_level_name(MapId levelId);
void func_8006BEFC(void);
void func_8006BFC8(s8 *arg0);
void func_8006C164(void);
TempStruct5 *func_8006C18C(void);
s8 func_8006C19C(void);
void func_8006C1AC(MapId levelId, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void func_8006C22C(s32 *levelId, s32 *entranceId, s32 *vehicleId, s32 *cutsceneId);
void func_8006C2E4(void);
s16 func_8006C2F0(void);
s32 func_8006C300(void);
void thread3_main(UNUSED void *unused);
void init_game(void);
void main_game_loop(void);
void func_8006CAE4(s32 arg0, s32 arg1, Vehicle vehicle);
void load_level_2(MapId levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId);
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
void load_level_3(MapId levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void func_8006DBE4(void);
void func_8006DC58(s32 arg0);
void load_level_for_menu(MapId levelId, s32 numberOfPlayers, s32 cutsceneId);
void calc_and_alloc_heap_for_settings(void);
void func_8006E5BC(void);
void func_8006E770(Settings *settings, s32 arg1);
void func_8006E994(Settings *settings);
void func_8006EA58(void);
Settings *get_settings(void);
s8 is_game_paused(void);
s8 func_8006EAB0(void);
s32 is_reset_pressed(void);
MapId func_8006EB14(void);
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

//Non Matching
void func_8006ECFC(s32 numberOfPlayers);
void func_8006DCF8(s32 arg0);
void func_8006EFDC(void);
void load_level(MapId levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void func_8006A6B0(void);
void func_80010994(s32 updateRate);

#endif
