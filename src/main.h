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

#define CONSOLE 1
#define EMULATOR 2
#define VC 4
#define IQUE 8

enum DebugPages {
    PAGE_MINIMAL,
    PAGE_OVERVIEW,
    PAGE_BREAKDOWN,
    PAGE_OBJECTS,
    PAGE_MEMORY,
    PAGE_AUDIO,
    PAGE_LOG,
    PAGE_COVERAGE,

    PAGE_COUNT
};

#define PP_PAGES \
    {"Minimal"}, \
    {"Overview"}, \
    {"Breakdown"}, \
    {"Objects"}, \
    {"Memory"}, \
    {"Audio"}, \
    {"Logging\t"}, \
    {"Coverage"}

enum rspFlags {
    RSP_NONE,
    RSP_AUDIO_START,
    RSP_GFX_START,
    RSP_AUDIO_FINISHED,
    RSP_GFX_FINISHED,
    RSP_GFX_PAUSED,
    RSP_GFX_RESUME,
};

enum MainTimers {
    PP_LEVELGFX,
    PP_OBJGFX,
    PP_OBJECTS,
    PP_RACER,
    PP_PARTICLEGFX,
    PP_PROFILER_CALC,
    PP_PROFILER_DRAW,

    PP_MAIN_TIMES_TOTAL,
    PP_MAIN_TIME_OFFSET = 3 // This exists to skip the profiler times.
};

#define PP_MAINDRAW \
    {"Lvl Gfx"}, \
    {"Obj Gfx"}, \
    {"Objects"}, \
    {"Racers"}, \
    {"Audio"},

enum TrackTimers {
    PP_COLLISION,
    PP_LIGHT,
    PP_ENVMAP,
    PP_HUD,
    PP_DMA,
    PP_PAD,
    PP_TEXT,
    PP_TEXTURES,
    PP_SHADOW,
    PP_PARTICLES,
    PP_AI,
    PP_WEATHER,
    PP_WAVES,
    PP_DIALOGUE,
    PP_TRANSITION,
    PP_CAMERA,
    PP_MATRIX,
    PP_BACKGROUND,
    PP_DECAL,
    PP_BILLBOARD,
    PP_VOID,
    PP_SEGMENTS,

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
    {"Lighting"}, \
    {"Envmaps"}, \
    {"HUD\t"}, \
    {"Render"}, \
    {"DMA"}, \
    {"Pad\t"}, \
    {"Text"}, \
    {"Textures"}, \
    {"Particles"}, \
    {"AI\t"}, \
    {"Weather"}, \
    {"Water"}, \
    {"Dialogue"}, \
    {"Transition"}, \
    {"Camera"}, \
    {"Matrix"}, \
    {"BG\t"}, \
    {"Decals"}, \
    {"Billboards"}, \
    {"Void"},


#ifdef PUPPYPRINT_DEBUG

#define NUM_OBJECT_PRINTS 250
#define NUM_PERF_ITERATIONS 32
#define PERF_AGGREGATE NUM_PERF_ITERATIONS
#define PERF_TOTAL NUM_PERF_ITERATIONS + 1
#define NUM_THREAD_ITERATIONS 8
#define NUM_LOG_LINES 32
typedef u32 PPTimer[NUM_PERF_ITERATIONS + 2];

struct PuppyPrint {
    PPTimer cpuTime; // Sum of multiple CPU timings, and what will be displayed.
    u32 rspTime; // Sum of multiple RSP timings, and publicly shamed on the street.
    u32 rdpTime; // Sum of multiple RDP timings, and hung by its entrails for all to see.
    u32 rspPauseTime; // Buffer that keeps track of the halt time of the Gfx task.
    u32 rspGfxBufTime; // Buffer that keeps track of the current Gfx task.
    u32 rspAudioBufTime; // Buffer that keeps track of the current Audio task.
    PPTimer timers[PP_TIMES_TOTAL]; // Large collection of timers for various things.
    PPTimer coreTimers[PP_MAIN_TIMES_TOTAL]; // Large collection of timers for various things.
    PPTimer audTime; // Normalised total for audio processing time.
    PPTimer gameTime; // Normalised total for game processing time.
    u32 threadTimes[NUM_THREAD_ITERATIONS][NUM_THREAD_TIMERS]; // Timers for individual threads.
    u16 objTimers[NUM_OBJECT_PRINTS][NUM_PERF_ITERATIONS + 2]; // Timers for individual object IDs
    u32 mainTimerPoints[2][PP_MAIN_TIMES_TOTAL]; // Timers for individual threads.
    u16 menuScroll; // Page menu scroll value to offset the text.
    s16 pageScroll; // Generic scroller var for a page. Reset when swapped.
    u8 threadIteration[NUM_THREAD_TIMERS / 2]; // Number of times the respective thread has looped.
    u8 enabled; // Show the profiler
    u8 menuOpen; // Whether the page menu's open
    u8 page; // Current viewed page.
    s8 menuOption; // Current option in the page menu.
    char logText[NUM_LOG_LINES][127];
};

extern struct PuppyPrint gPuppyPrint;
extern void profiler_update(u32 *time, u32 time2);
extern void puppyprint_update_rsp(u8 flags);
extern void profiler_add(u32 time, u32 offset);
void profiler_offset(u32 *time, u32 offset);
void profiler_reset_values(void);
void render_profiler(void);
void count_triangles(u8 *dlist, u8 *dlistEnd);
void calculate_and_update_fps(void);
void puppyprint_calculate_average_times(void);
void profiler_add_obj(u32 objID, u32 time);
void update_rdp_profiling(void);
void profiler_snapshot(s32 eventID);
void puppyprint_log(const char *str, ...);
#define profiler_begin_timer() u32 first = osGetCount();
#define profiler_begin_timer2() u32 first2 = osGetCount();
#define profiler_begin_timer3() u32 first3 = osGetCount();
#define profiler_reset_timer() first = osGetCount();
#define profiler_reset_timer2() first2 = osGetCount();
#define profiler_reset_timer3() first3 = osGetCount();
#define profiler_get_timer() first
#define profiler_get_timer2() first2
#define profiler_get_timer3() first3

extern u8 perfIteration;
extern u32 sPrevLoadTimeTotal;
extern u32 gPrevLoadTimeDecompress;
extern u32 gPrevLoadTimeDMA;
extern u32 gPrevLoadTimeTexture;
extern u32 gPrevLoadTimeModel;
extern u32 gPrevLoadTimeObjects;
extern u8 sPrevLoadTimer;
extern u8 gShowHiddenGeometry;
extern u8 gShowHiddenObjects;
extern u32 gFreeMem[12];
#else

#define update_rdp_profiling()
#define profiler_snapshot(eventID)
#define puppyprint_update_rsp(eventID)
#define profiler_begin_timer()
#define profiler_begin_timer2()
#define profiler_begin_timer3()
#define profiler_reset_timer()
#define profiler_reset_timer2()
#define profiler_reset_timer3()
#define profiler_get_timer() 0
#define profiler_get_timer2() 0
#define profiler_get_timer3() 0
#define profiler_add(x, y)
#define profiler_add_obj(x, y)
#define profiler_update(x, y)
#define profiler_offset(x, y)
#ifdef __sgi
#define puppyprint_log
#else
#define puppyprint_log(...)
#endif
#endif
int puppyprintf(char *dst, const char *fmt, ...);
void crash_screen_init(void);
void get_platform(void);

#endif
