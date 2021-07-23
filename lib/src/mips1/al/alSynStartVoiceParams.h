#ifndef AL_SYN_START_VOICE_PARAMS
#define AL_SYN_START_VOICE_PARAMS

#include "types.h"
#include "audio_internal.h"

// Can be changed in the "Audio Options" menu.
enum StereoPanMode {
    STEREO,
    MONO,
    HEADPHONES
};

void set_stereo_pan_mode(s32 panMode);
s32 modify_panning(s32 pan);

#endif