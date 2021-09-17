#ifndef _UNKNOWN_060450_H_
#define _UNKNOWN_060450_H_

#include "types.h"
#include "PR/gbi.h"
#include "structs.h"

/* 8 Bytes */
typedef struct unk8011D624 {
    s32 unk0;
    ObjectModel *model;
} unk8011D624;

extern s32 D_800DCEA0;
extern s32 D_800DCEA4;

void func_8005F850(void);
void func_800619F4(s32 arg0);

void free_object_model(ObjectModel *model); //Non Matching
void func_8005FF40(ObjectModel **modelPtr); //Non Matching

#endif
