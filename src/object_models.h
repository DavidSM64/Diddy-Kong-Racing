#ifndef _OBJECT_MODELS_H_
#define _OBJECT_MODELS_H_

#include "types.h"
#include "PR/gbi.h"
#include "structs.h"

typedef enum AnimType {
    MODELTYPE_BASIC,    // No shading nor animation
    MODELTYPE_SHADE,    // Model is intended to be shaded.
    MODELTYPE_ANIMATED  // Model has animation and shading.
} AnimType ;

/* 8 Bytes */
typedef struct unk8011D624 {
    s32 unk0;
    ObjectModel *model;
} unk8011D624;

extern s32 gTractionTableChecksum;
extern s32 gTrackRenderFuncLength;

void allocate_object_model_pools(void);
void func_800619F4(s32 arg0);
void func_80061C0C(Object* obj);
void free_3d_model(ObjectModel **modelPtr);
s32 func_80061A00(ObjectModel *model, s32 animTableIndex);
s32 check_nearby_vertices(Vertex *vertices, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
Object_68 *model_init_type(ObjectModel *model, s32 flags);
Object_68 *object_model_init(s32 modelID, s32 flags);

void free_model_data(ObjectModel *mdl); // Non Matching
void func_80060910(ObjectModel *);
s32 func_80060AC8(ObjectModel *mdl, s32 arg1, s32 arg2, s32 arg3, s32 *outBatchIndex, s32 *outVertexIndex);
s32 func_80060EA8(ObjectModel *);

#endif
