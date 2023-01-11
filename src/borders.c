/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80077050 */

#include "borders.h"

#include "camera.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "video.h"
#include "game.h"
#include "game_ui.h"

/**
 * Renders the black borders that separate each viewport during multiplayer.
 * 2 player has a single horizontal line, while 3 and 4 player splits the screen into quadrants.
 * 3 player will completely fill in where player 4 would normally be.
 */
void render_borders_for_multiplayer(Gfx **dlist) {
    u32 widthAndHeight, width, height;
    u32 y, x, xOffset, yOffset;
    LevelHeader *levelHeader;

    widthAndHeight = get_video_width_and_height_as_s32();
    width = GET_VIDEO_WIDTH(widthAndHeight);
    height = GET_VIDEO_HEIGHT(widthAndHeight);
    xOffset = width / 256;
    yOffset = height / 128;
    gDPSetCycleType((*dlist)++, G_CYC_FILL);
    gDPSetFillColor((*dlist)++, GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1)); // Black fill color
    switch (get_viewport_count()) {
        case VIEWPORTS_COUNT_2_PLAYERS:
            // Draws a solid horizontal black line in the middle of the screen.
            y = (height >> 1) - yOffset;
            gDPFillRectangle((*dlist)++, height * 0, y, width, y + yOffset);
            break;
        case VIEWPORTS_COUNT_3_PLAYERS:
            levelHeader = get_current_level_header();
            // Draw black square in the bottom-right corner.
            if (get_hud_setting() || (levelHeader->race_type & RACETYPE_CHALLENGE)) {
                gDPFillRectangle((*dlist)++, width >> 1, height >> 1, width, height);
            }
            // There is no break statement here. This is intentional.
        case VIEWPORTS_COUNT_4_PLAYERS:
            x = (width >> 1) - xOffset;
            // Draws 2 black lines in the middle of the screen. One vertical, another horizontal.
            gDPFillRectangle((*dlist)++, height * 0, (height >> 1) - yOffset, width, ((height >> 1) - yOffset) + yOffset);
            gDPFillRectangle((*dlist)++, x, 0, x + xOffset, height);
            break;
    }
}