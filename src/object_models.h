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

extern s32 gTractionTableChecksum;
extern s32 gFunc80024D54Length;

void allocate_object_model_pools(void);
void func_800619F4(s32 arg0);
void func_80061C0C(Object* obj);

void free_object_model(ObjectModel *model); //Non Matching
void func_8005FF40(ObjectModel **modelPtr);

#endif
