#ifndef _OBJECT_MODELS_H_
#define _OBJECT_MODELS_H_

#include "types.h"
#include "PR/gbi.h"
#include "structs.h"

/* 8 Bytes */
typedef struct unk8011D624 {
    s32 unk0;
    ObjectModel *model;
} unk8011D624;

//Object_68?
typedef struct unk8005FCD0 {
    ObjectModel *unk0;
    Vertex *unk4;
    Vertex *unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s8 unk1E;
    s8 unk1F;
    s8 unk20;
} unk8005FCD0;

extern s32 gTractionTableChecksum;
extern s32 gFunc80024D54Length;

void allocate_object_model_pools(void);
void func_800619F4(s32 arg0);
void func_80061C0C(Object* obj);
void func_8005FF40(ObjectModel **modelPtr);
s32 func_80061A00(ObjectModel *model, s32 animTableIndex);
s32 func_80060C58(Vertex *vertices, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
unk8005FCD0 *func_8005FCD0(ObjectModel* model, s32 arg1);
unk8005FCD0 *func_8005F99C(s32 arg0, s32 arg1);

void free_object_model(ObjectModel *model); //Non Matching
void func_80060910(ObjectModel *);
s32 func_80060AC8(ObjectModel *mdl, s32 arg1, s32 arg2, s32 arg3, s32 *outBatchIndex, s32 *outVertexIndex);
s32 func_80060EA8(ObjectModel *);

#endif
