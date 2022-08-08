/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9810 */

/*====================================================================
 * synsetfxmix.c
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

ALParam *__allocParam();

void alSynSetFXMix(ALSynth *synth, ALVoice *v, u8 fxmix)
{
    ALParam  *update;
    ALFilter *f;

    if (v->pvoice) {
        /*
         * get new update struct from the free list
         */
        update = __allocParam();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        /*
         * set offset and fxmix data
         */
        update->delta  = synth->paramSamples + v->pvoice->offset;
        update->type   = AL_FILTER_SET_FXAMT;

//Ignore GCC warnings for this line, as there's no other way to match this.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
        //Differs from ultralib
        if (fxmix < 0)
            update->data.i = -fxmix;
        else
            update->data.i = fxmix;
#pragma GCC diagnostic pop

        update->next   = 0;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
    }
}


