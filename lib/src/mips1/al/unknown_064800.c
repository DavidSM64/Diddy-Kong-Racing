/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80063C00 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
/* Size: 0x14 bytes */
typedef struct unk80063C00 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u8  unk10;
    u8  unk11;
    u8  unk12;
    u8  unk13;
} unk80063C00;

/* Unknown size */
typedef struct unk80063C00_2 {
    u8  unk00[0x60];
    unk80063C00* unk60; // Array of unk80063C00, unknown number of elements (At most 256).
} unk80063C00_2;

u8 func_80063C00(unk80063C00_2 *arg0, u8 arg1) {
    return arg0->unk60[arg1].unk10;
    //return seqp->chanState[chan].unk10???
}
