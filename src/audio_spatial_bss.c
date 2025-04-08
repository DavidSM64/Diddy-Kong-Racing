#include "audio_vehicle.h"

#include "types.h"
#include "macros.h"
#include "audio_spatial.h"
#include "audiosfx.h"
#include "objects.h"
#include "joypad.h"
#include "racer.h"
#include "PR/libaudio.h"
#include "game_ui.h"
#include "math_util.h"
#include "printf.h"

// This should be moved to audio_spatial.c, but for some reason we can't get it to match in there yet.

SoundData *D_80119C40; // This should be in audio_spatial?
SoundMask **gSoundMaskHeapUsed;
SoundMask **gSoundMaskHeap; // 0x24 struct size - 0x5A0 total size - should be 40 elements
u8 gFreeMasks;
SoundMask **gSoundMaskHeapFree;
s32 D_80119C54;           // Padding?
unk80119C58 **D_80119C58; // Struct of size in func_8000A184 = 0x180 = 384 bytes | Ambient Sounds
unk80119C58 **D_80119C5C; // Struct of size in func_8000A184 = 0x180 = 384 bytes Likely the same as above
f32 D_80119C60[670];      // array size of 672 looks to be required for func_80008174
unk8011A6D8 *D_8011A6D8;  // unk8011A6D8[] | Reverb stuff
unk8011A6D8 **D_8011A6DC; // Struct of size 0xC0
f32 D_8011A6E0[334];
s32 gAudioLinesOff;
s32 D_8011AC1C;
