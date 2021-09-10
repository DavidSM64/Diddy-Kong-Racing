/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80002660 */

#include "unknown_003260.h"

// This file is needed, since there is a bss reordering issue with D_80119BD0 and gAlSndPlayer

s32 D_80115F90;
ALHeap *D_80115F94;
s32 D_80115F98[2];
s32 D_80115FA0[3];
OSThread audioThread;
OSMesgQueue OSMesgQueue_80116160;
OSMesg D_80116178[8];
OSMesgQueue D_80116198;
OSMesg D_801161B0[8];
ALGlobals ALGlobals_801161D0;
s32 D_80116220[3076];
s32 D_80119230[3];
unk80119240 D_80119240[50];
s32 D_80119628;
s32 D_8011962C;
s32 D_80119630;
s32 D_80119634;
s32 D_80119638[2];
s32 D_80119640[300];
OSMesgQueue D_80119AF0;
OSMesg D_80119B08[50];
unk800DC6BC D_80119BD0;
u16 *D_80119C28;
