#ifndef _MAIN_H_
#define _MAIN_H_

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "config.h"

extern u8 gAssert;
extern char gAssertString[64];

void main(void);
void thread1_main(void *);
void thread3_verify_stack(void);


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
    PP_SHADOW,

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

enum PPProfilerEvent {
    idk,
    idk2,
    THREAD5_START,
    THREAD5_END,
    THREAD3_START,
    THREAD3_END,
    THREAD4_START,
    THREAD4_END,
    THREAD30_START,
    THREAD30_END,

    NUM_THREAD_TIMERS
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



#define NUM_OBJECT_PRINTS 250
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
    PPTimer cpuTotal;
    u32 threadTimes[16][NUM_THREAD_TIMERS];
    u8 threadIteration[NUM_THREAD_TIMERS / 2];
    u16 objTimers[NUM_OBJECT_PRINTS][NUM_PERF_ITERATIONS + 2];
};
extern struct PuppyPrintTimers gPuppyTimers;
extern void profiler_update(u32 *time, u32 time2);
extern void puppyprint_update_rsp(u8 flags);
extern void profiler_add(u32 *time, u32 offset);
void profiler_offset(u32 *time, u32 offset);
void profiler_reset_values(void);
void render_profiler(void);
void count_triangles(u8 *dlist, u8 *dlistEnd);
void calculate_and_update_fps(void);
void puppyprint_calculate_average_times(void);
void profiler_add_obj(u32 objID, u32 time);
void update_rdp_profiling(void);
void profiler_snapshot(s32 eventID);

extern u8 perfIteration;
extern u32 sPrevLoadTimeTotal;
extern u32 gPrevLoadTimeDecompress;
extern u32 gPrevLoadTimeDMA;
extern u32 gPrevLoadTimeTexture;
extern u32 gPrevLoadTimeModel;
extern u32 gPrevLoadTimeObjects;
extern u8 sPrevLoadTimer;
extern u8 gProfilerOn;
extern u8 gShowHiddenGeometry;
extern u8 gShowHiddenObjects;
extern u32 gFreeMem[12];
#else

#define update_rdp_profiling()
#define profiler_snapshot(eventID)
#endif
int puppyprintf(char *dst, const char *fmt, ...);
void crash_screen_init(void);

#endif
