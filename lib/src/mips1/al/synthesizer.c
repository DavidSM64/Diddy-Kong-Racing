/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065130 */

#include "types.h"
#include "audio_internal.h"
#include "macros.h"

s32 __nextSampleTime(ALSynth *drvr, ALPlayer **client);
s32 _timeToSamplesNoRound(ALSynth *ALSynth, s32 micros);

void alSynNew(ALSynth *drvr, ALSynConfig *c)
{
    s32         i;
    PVoice      *pv;
    PVoice      *pvoices;
    ALHeap      *hp = c->heap;
    ALSave      *save;
    ALFilter    *sources;
    ALParam     *params;
    ALParam     *paramPtr;
    
    drvr->head            = NULL;
    drvr->numPVoices      = c->maxPVoices;
    drvr->curSamples      = 0;
    drvr->paramSamples    = 0;
    drvr->outputRate      = c->outputRate;
    drvr->maxOutSamples   = AL_MAX_RSP_SAMPLES;
    drvr->dma             = (ALDMANew) c->dmaproc;

    save = alHeapAlloc(hp, 1, sizeof(ALSave));
    alSaveNew(save);
    drvr->outputFilter = (ALFilter *)save;

    drvr->auxBus = alHeapAlloc(hp, 2, sizeof(ALAuxBus));
    drvr->maxAuxBusses = 2;
    sources = alHeapAlloc(hp, c->maxPVoices, sizeof(ALFilter *));
    alAuxBusNew(drvr->auxBus, sources, c->maxPVoices);
    
    sources = alHeapAlloc(hp, c->maxPVoices, sizeof(ALFilter *));
    alAuxBusNew(drvr->auxBus + 1, sources, c->maxPVoices);
    
    drvr->mainBus = alHeapAlloc(hp, 1, sizeof(ALMainBus));
    sources = alHeapAlloc(hp, c->maxPVoices, sizeof(ALFilter *));
    alMainBusNew(drvr->mainBus, sources, c->maxPVoices);
    
    for(i = 0; i < 2; i++) {
        if (c->fxType[i] != 0) {
            alSynAllocFX(drvr, (s16)i, c, hp);
        } else {
            alMainBusParam(drvr->mainBus, 2, drvr->auxBus + i);
        }
    }
    
    drvr->pFreeList.next = 0;
    drvr->pFreeList.prev = 0;
    drvr->pLameList.next = 0;
    drvr->pLameList.prev = 0;
    drvr->pAllocList.next = 0;
    drvr->pAllocList.prev = 0;

    pvoices = alHeapAlloc(hp, c->maxPVoices, sizeof(PVoice));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        alLink((ALLink *)pv, &drvr->pFreeList);
        pv->vvoice = 0;

        alLoadNew(&pv->decoder, drvr->dma, hp);
        alLoadParam(&pv->decoder, AL_FILTER_SET_SOURCE, 0);
    
        alResampleNew(&pv->resampler, hp);
        alResampleParam(&pv->resampler, AL_FILTER_SET_SOURCE, &pv->decoder);

        alEnvmixerNew(&pv->envmixer, hp);
        alEnvmixerParam(&pv->envmixer, AL_FILTER_SET_SOURCE, &pv->resampler);

        alAuxBusParam(drvr->auxBus, AL_FILTER_ADD_SOURCE, &pv->envmixer);
        
        pv->channelKnob   = (ALFilter *)&pv->envmixer;
    }
    
    alSaveParam(save, AL_FILTER_SET_SOURCE, drvr->mainBus);

    params = alHeapAlloc(hp, c->maxUpdates, sizeof(ALParam));
    drvr->paramList = 0;
    for (i = 0; i < c->maxUpdates; i++) {
        paramPtr= &params[i];
        paramPtr->next = drvr->paramList;
        drvr->paramList = paramPtr;
    }
    
    drvr->heap = hp;
}

void __collectPVoices(ALSynth *drvr);
s32 __timeToSamplesNoRound(ALSynth *synth, s32 micros);

Acmd *alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen)
{
    ALPlayer    *client;
    ALFilter    *output;
    ALSynth     *drvr = &alGlobals->drvr;
    s16         tmp = 0;        /* Starting buffer in DMEM */
    Acmd        *cmdlEnd = cmdList;
    Acmd        *cmdPtr;
    s32         nOut;
    s16         *lOutBuf = outBuf;

    if (drvr->head == 0) {
        *cmdLen = 0;
        return cmdList;         /* nothing to do */
    }    

    for (drvr->paramSamples = __nextSampleTime(drvr, &client);
	 drvr->paramSamples - drvr->curSamples < outLen;
	 drvr->paramSamples = __nextSampleTime(drvr, &client))
    {
        drvr->paramSamples &= ~0xf;
        client->samplesLeft += __timeToSamplesNoRound(drvr, (*client->handler)(client));
    }

    drvr->paramSamples &= ~0xf;

    while (outLen > 0){
        nOut = MIN(drvr->maxOutSamples, outLen);

        cmdPtr = cmdlEnd;
        aSegment(cmdPtr++, 0, 0);
        output = drvr->outputFilter;
        (*output->setParam)(output, AL_FILTER_SET_DRAM, lOutBuf);
        cmdlEnd = (*output->handler)(output, &tmp, nOut, drvr->curSamples,
                                     cmdPtr);
        
        outLen -= nOut;
        lOutBuf += nOut<<1;
        drvr->curSamples += nOut;
                
    }
    *cmdLen = (s32) (cmdlEnd - cmdList);

    __collectPVoices(drvr);
    
    return cmdlEnd;
}

ALParam *__allocParam() 
{
    ALParam *update = 0;
    ALSynth *drvr = &alGlobals->drvr;

    if (drvr->paramList) {        
        update = drvr->paramList;
        drvr->paramList = drvr->paramList->next;
        update->next = 0;
    }
    return update;
}

void __freeParam(ALParam *param) 
{
    ALSynth *drvr = &alGlobals->drvr;
    param->next = drvr->paramList;
    drvr->paramList = param;
}

void __collectPVoices(ALSynth *drvr) 
{
    ALLink *dl;

    while ((dl = drvr->pLameList.next) != 0) {
        alUnlink(dl);
        alLink(dl, &drvr->pFreeList);        
    }
}

void __freePVoices(ALSynth *drvr, PVoice *pvoice) 
{
    alUnlink((ALLink *)pvoice);
    alLink((ALLink *)pvoice, &drvr->pLameList);
}

s32 __timeToSamplesNoRound(ALSynth *synth, s32 micros)
{
    f32 tmp = ((f32)micros) * synth->outputRate / 1000000.0 + 0.5;

    return (s32)tmp;
}

s32 __timeToSamples(ALSynth *synth, s32 micros)
{
    return __timeToSamplesNoRound(synth, micros) & ~0xF;
}

s32 __nextSampleTime(ALSynth *drvr, ALPlayer **client) 
{
    ALMicroTime delta = 0x7fffffff;
    ALPlayer *cl;

    *client = 0;
    
    for (cl = drvr->head; cl != 0; cl = cl->next) {
        if ((cl->samplesLeft - drvr->curSamples) < delta) {
            *client = cl;
            delta = cl->samplesLeft - drvr->curSamples;
        }
    }

    return (*client)->samplesLeft;
}
