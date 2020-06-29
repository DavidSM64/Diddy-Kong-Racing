/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800249E0 */

#include "types.h"

extern s32 D_8011D37C;

s32 func_800249E0(s32 arg0) {
    D_8011D37C = arg0;
    return 0;
}
