/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80077050 */

#include "unknown_077C50.h"

#include "camera.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"

#ifdef NON_MATCHING

// Draws the borders/negative space for multiplayer. Has regalloc issues
void render_borders_for_multiplayer(Gfx **dlist) {
    u32 widthAndHeight, width, height;
    u32 temp0, temp1, temp2, temp3;
    LevelHeader *levelHeader;
    widthAndHeight = get_video_width_and_height_as_s32();
    width = widthAndHeight & 0xFFFF;
    temp0 = width >> 8;
    height = widthAndHeight >> 16;
    temp1 = height >> 7;
    gDPSetCycleType((*dlist)++, G_CYC_FILL);
    gDPSetFillColor((*dlist)++, 0x00010001); // Black fill color
    switch(get_viewport_count()){
        case VIEWPORTS_COUNT_2_PLAYERS:
            // Draws a solid horizontal black line in the middle of the screen.
            gDPFillRectangle((*dlist)++, 0, (height >> 1) - temp1, width, ((height >> 1) - temp1) + temp1);
            break;
        case VIEWPORTS_COUNT_3_PLAYERS:
            levelHeader = get_current_level_header();
            // Draw black square in the bottom-right corner.
            if (func_800A8458() || (levelHeader->race_type & 0x40)) {
                gDPFillRectangle((*dlist)++, width >> 1, height >> 1, width, height);
            }
            // There is no break statement here. This is intentional.
        case VIEWPORTS_COUNT_4_PLAYERS:
            temp2 = (width >> 1) - temp0;
            // Draws 2 black lines in the middle of the screen. One vertical, another horizontal.
            gDPFillRectangle((*dlist)++, 0, (height >> 1) - temp1, width, ((height >> 1) - temp1) + temp1);
            gDPFillRectangle((*dlist)++, temp2, 0, temp2 + temp0, height);
            break;
    }
    return;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_077C50/render_borders_for_multiplayer.s")
#endif

#if 0
void func_80077268(Gfx **dlist) {
    u32 temp_a2_2;
    u32 temp_v0_3;
    u32 temp_v0_4;
    u32 height;
    u32 width;
    u32 temp_t2;
    u32 widthAndHeight;
    u32 ra;

    widthAndHeight = get_video_width_and_height_as_s32();
    height = widthAndHeight >> 16;
    width = widthAndHeight & 0xFFFF;
    gDPSetCycleType((*dlist)++, G_CYC_1CYCLE);
    gDPSetCombineMode((*dlist)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode((*dlist)++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor((*dlist)++, 0, 0, 0, 0, 0, 0);
    // Issues with this block.
    switch(get_viewport_count()){
        case VIEWPORTS_COUNT_2_PLAYERS:
            temp_v0_4 = (height >> 1) - (temp_t2 >> 1);
            gDPFillRectangle((*dlist)++, 0, temp_v0_4, width, temp_v0_4 + temp_t2);
            break;
        case VIEWPORTS_COUNT_3_PLAYERS:
        case VIEWPORTS_COUNT_4_PLAYERS:
            temp_v0_3 = (height >> 1) - (temp_t2 >> 1);
            temp_a2_2 = (width >> 1) - (ra >> 1);
            gDPFillRectangle((*dlist)++, 0, temp_v0_3, width, temp_v0_3 + temp_t2);
            gDPFillRectangle((*dlist)++, temp_a2_2, 0, temp_a2_2 + ra, height);
            break;
    }
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_077C50/func_80077268.s")
#endif
