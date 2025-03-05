#ifndef _SEQCHANNEL_H_
#define _SEQCHANNEL_H_


#include "types.h"
#include "audio_internal.h"

void alSeqChOff(ALSeqPlayer *seqp, u8 chan);
void alSeqChOn(ALSeqPlayer *seqp, u8 chan);

#endif
