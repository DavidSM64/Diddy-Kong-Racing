#ifndef _OBJECT_MODELS_H_
#define _OBJECT_MODELS_H_

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

extern s32 gRenderSceneChecksum;
extern s32 gRenderSceneFuncLength;

void allocate_object_model_pools(void);
void model_anim_offset(s32 offset);
void func_80061C0C(Object* obj);
void free_3d_model(ModelInstance *modInst);
s32 model_anim_init(ObjectModel *model, s32 modelID);
s32 check_nearby_vertices(Vertex *vertices, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
ModelInstance *model_instance_init(ObjectModel *model, s32 flags);
ModelInstance *object_model_init(s32 modelID, s32 flags);
s32 func_80060C58(Vertex *vertices, s32 i1, s32 i2, s32 i3, s32 i4);

void free_model_data(ObjectModel *mdl); // Non Matching
void func_80060910(ObjectModel *);
s32 func_80060AC8(ObjectModel *mdl, s32 arg1, s32 arg2, s32 arg3, s32 *outBatchIndex, s32 *outVertexIndex);
s32 model_init_normals(ObjectModel *);

#endif
