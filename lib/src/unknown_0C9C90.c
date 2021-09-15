/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9090 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "libultra_internal.h"

void alEvtqFlushType(ALEventQueue *evtq, s16 type)
{
    ALLink      	*thisNode;
    ALLink      	*nextNode;
    ALEventListItem     *thisItem, *nextItem;
    OSIntMask   	mask;

    mask = osSetIntMask(OS_IM_NONE);

    thisNode = evtq->allocList.next;
    while( thisNode != 0 )
    {
	nextNode = thisNode->next;
	thisItem = (ALEventListItem *)thisNode;
	nextItem = (ALEventListItem *)nextNode;
	if (thisItem->evt.type == type)
	{
	    if (nextItem)
		nextItem->delta += thisItem->delta;
	    alUnlink(thisNode);
	    alLink(thisNode, &evtq->freeList);
	}
	thisNode = nextNode;
    }

    osSetIntMask(mask);
}

void alEvtqFlush(ALEventQueue *evtq)
{
    ALLink      *thisNode;
    ALLink      *nextNode;
    OSIntMask   mask;

    mask = osSetIntMask(OS_IM_NONE);

    thisNode = evtq->allocList.next;
    while( thisNode != 0 ) {
	nextNode = thisNode->next;
	alUnlink(thisNode);
	alLink(thisNode, &evtq->freeList);
	thisNode = nextNode;
    }
    
    osSetIntMask(mask);
}

#if 1
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alEvtqPostEvent.s")
#else
void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta)
{
    ALEventListItem     *item;
    ALEventListItem     *nextItem;
    ALLink              *node;
    s32                 postAtEnd=0;
    OSIntMask           mask;

    mask = osSetIntMask(OS_IM_NONE);

    item = (ALEventListItem *)evtq->freeList.next;
    if (!item) {
        osSetIntMask(mask);
#ifdef _DEBUG
        __osError(ERR_ALEVENTNOFREE, 0);
#endif        
        return;
    }
    
    alUnlink((ALLink *)item);
    alCopy(evt, &item->evt, sizeof(*evt));

    if (delta == AL_EVTQ_END)
        postAtEnd = -1;
    
    for (node = &evtq->allocList; node != 0; node = node->next) {
        if (!node->next) { /* end of the list */
            if (postAtEnd)
                item->delta = 0;
            else
                item->delta = delta;
            alLink((ALLink *)item, node);
            break;
        } else {
            nextItem = (ALEventListItem *)node->next;

            if (delta < nextItem->delta) {
                item->delta = delta;
                nextItem->delta -= delta;
                    
                alLink((ALLink *)item, node);
                break;
            }
                
            delta -= nextItem->delta;

        }
    }

    osSetIntMask(mask);
    
}
#endif

ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt) {
    ALEventListItem *item;
    ALMicroTime delta;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);
    
    item = (ALEventListItem *)evtq->allocList.next;

    if (item)
    {
        alUnlink((ALLink *)item);
        alCopy(&item->evt, evt, sizeof(*evt));
        alLink((ALLink *)item, &evtq->freeList);
	delta = item->delta;
    }
    else
    {
        /* sct 11/28/95 - If we get here, most like we overflowed the event queue */
	/* with non-self-perpetuating events.  Eg. if we filled the evtq with volume */
	/* events, then when the seqp is told to play it will handle all the events */
	/* at once completely emptying out the queue.  At this point this problem */
	/* must be treated as an out of resource error and the evtq should be increased. */
	evt->type = -1;
	delta = 0;	    
    }

    osSetIntMask(mask);
    
    return delta;
}


void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount) {
    s32 i;
    
    evtq->eventCount     = 0;
    evtq->allocList.next = 0;
    evtq->allocList.prev = 0;
    evtq->freeList.next  = 0;
    evtq->freeList.prev  = 0;

    for (i = 0; i < itemCount; i++) {
        alLink((ALLink *)&items[i], &evtq->freeList);
    }
}

void alSynAddPlayer(ALSynth *drvr, ALPlayer *client)
{
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    client->samplesLeft = drvr->curSamples;
    client->next = drvr->head;
    drvr->head   = client;

    osSetIntMask(mask);
}

#if 1
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/_allocatePVoice.s")
#else
s32 _allocatePVoice(ALSynth *drvr, PVoice **pvoice, s16 priority)
{
    ALLink      *dl;
    PVoice      *pv;
    s32         stolen = 0;
    
    if ((dl = drvr->pLameList.next) != 0) { /* check the lame list first */
        *pvoice = (PVoice *) dl;
        alUnlink(dl);
        alLink(dl, &drvr->pAllocList);        
    } else if ((dl = drvr->pFreeList.next) != 0) { /* from the free list */
        *pvoice = (PVoice *) dl;
        alUnlink(dl);
        alLink(dl, &drvr->pAllocList);        
    } else { /* steal one */
        for (dl = drvr->pAllocList.next; dl != 0; dl = dl->next) {
            pv = (PVoice *)dl;

            /*
             * if it is lower priority and not already stolen, keep it
             * as a candidate for stealing
             */
            if ((pv->vvoice->priority <= priority) && (pv->offset == 0)) {
                *pvoice = pv;
                priority = pv->vvoice->priority;
                stolen = 1;
            }
        }
    }
    
    return stolen;
}
#endif

s32 alSynAllocVoice(ALSynth *drvr, ALVoice *voice, ALVoiceConfig *vc)
{
    PVoice  *pvoice = 0;
    ALFilter *f;
    ALParam *update;
    s32 stolen;
    
#ifdef _DEBUG
    /* need two updates if voice is stolen */
    if (drvr->paramList == 0) {
        __osError(ERR_ALSYN_NO_UPDATE, 0);
        return 0;
    } else if (drvr->paramList->next == 0) {
        __osError(ERR_ALSYN_NO_UPDATE, 0);
        return 0;
    }
#endif    

    voice->priority     = vc->priority;
    voice->unityPitch   = vc->unityPitch;
    voice->table        = 0;
    voice->fxBus        = vc->fxBus;
    voice->state        = AL_STOPPED;        
    voice->pvoice       = 0;

    stolen = _allocatePVoice(drvr, &pvoice, vc->priority);
        
    if (pvoice) {    /* if we were able to allocate a voice */

        f = pvoice->channelKnob;            
            
        if (stolen) {
                
            pvoice->offset = 512;
            pvoice->vvoice->pvoice = 0; /* zero stolen voice */
                
            /*
             * ramp down stolen voice
             */
            update = __allocParam();
            update->delta      = drvr->paramSamples;
            update->type       = AL_FILTER_SET_VOLUME;
            update->data.i     = 0;
            update->moredata.i = pvoice->offset - 64;
            (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);

            /*
             * stop stolen voice
             */
            update = __allocParam();
            if (update) {
                update->delta  = drvr->paramSamples + pvoice->offset;
                update->type   = AL_FILTER_STOP_VOICE;
                update->next   = 0;
                (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
            } else {
#ifdef _DEBUG                
                __osError(ERR_ALSYN_NO_UPDATE, 0);
#endif
            }

        } else {
            pvoice->offset = 0;
        }
            
        pvoice->vvoice = voice;     /* assign new voice  */
        voice->pvoice  = pvoice;

    }

    return (pvoice != 0);    
}