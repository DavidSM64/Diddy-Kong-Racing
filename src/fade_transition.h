#ifndef _FADE_TRANSITION_H_
#define _FADE_TRANSITION_H_

#include "types.h"
#include "camera.h"

#define FADE_FULLSCREEN          0
#define FADE_BARNDOOR_HORIZONTAL 1
#define FADE_BARNDOOR_VERTICAL   2
#define FADE_CIRCLE              3
#define FADE_WAVES               4
#define FADE_BARNDOOR_DIAGONAL   5
#define FADE_DISABLED            6

//Fade transiton flags live at the top two bits of the fade type.
#define FADE_FLAG_NONE 0
#define FADE_FLAG_INVERT (1 << 6) // Invert the transition timer and opacity when finished.
#define FADE_FLAG_OUT (1 << 7) // Transition fading out
#define FADE_FLAG_BOTH (2 << 6)

#define FADE_COLOR(red, green, blue) red, green, blue
#define FADE_COLOR_BLACK FADE_COLOR(0, 0, 0)
#define FADE_COLOR_WHITE FADE_COLOR(255, 255, 255)

/**
 * type: Transition type
 * flags: Transition flags
 * color: Transition colour
 * duration: Transition length
 * endDelay: Length after transition finishing before it frees.
*/
#define FADE_TRANSITION(type, flags, color, duration, endDelay) { (type & 0x3F) | (flags & 0xC0), color, duration, endDelay }

enum TransitionStatus {
    TRANSITION_LEVELSWAP = -1,
    TRANSITION_NONE,
    TRANSITION_ACTIVE
};

/* Size: 8 bytes */
typedef struct FadeTransition {
  /* 0x00 */ u8 type; // top 2 bits also act as flags
  /* 0x01 */ u8 red;
  /* 0x02 */ u8 green;
  /* 0x03 */ u8 blue;
  /* 0x04 */ u16 duration;
  /* 0x06 */ u16 endTimer;
} FadeTransition;

void enable_new_screen_transitions(void);
void disable_new_screen_transitions(void);
u32 check_fadeout_transition(void);
void transition_end(void);
s32 handle_transitions(s32 updateRate);
void render_fade_transition(Gfx **dList, MatrixS **mats, Vertex **verts);
void render_fade_fullscreen(Gfx **dList, MatrixS **mats, Vertex **verts);
void render_fade_barndoor_horizontal(Gfx **dList, MatrixS **mats, Vertex **verts);
void render_fade_barndoor_vertical(Gfx **dList, MatrixS **mats, Vertex **verts);
void render_fade_barndoor_diagonal(Gfx **dList, MatrixS **mats, Vertex **verts);
void render_fade_disabled(Gfx **dList, MatrixS **mats, Vertex **verts);
void transition_fullscreen_start(FadeTransition *transition);
void init_transition_blank(FadeTransition *transition);
void process_transition_fullscreen(s32 updateRate);
void process_transition_disabled(s32 updateRate);
s32 transition_begin(FadeTransition *transition);
void render_fade_circle(Gfx **dList, MatrixS **mats, Vertex **verts);
void process_transition_shape(s32 updateRate);
void init_transition_shape(FadeTransition *transition, s32 numVerts, s32 numTris, s16 *coords, u8 *nextPos,
                           u8 *targetPos, u8 *nextAlpha, u8 *targetAlpha, u8 *vertIndices);
void func_800C1EE8(s32 updateRate);
void render_fade_waves(Gfx **dlist, UNUSED MatrixS **mats, UNUSED Vertex **verts);

void func_800C15D4(FadeTransition *transition); //Non Matching

#endif
