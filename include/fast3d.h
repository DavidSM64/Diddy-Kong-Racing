/* TODO: Replace this with a real gbi.h later */

#ifndef _FAST3D_H_
#define _FAST3D_H_

#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

#define fast3d_cmd(pkt, word0, word1) \
{                                     \
    Gfx *_g = (Gfx*)(pkt);            \
    _g->w0 = word0;                   \
    _g->w1 = word1;                   \
}

#endif
