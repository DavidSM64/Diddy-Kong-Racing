/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800AE270 */

#include "particles.h"
#include "types.h"
#include "macros.h"
#include "asset_enums.h"
#include "memory.h"
#include "textures_sprites.h"
#include "thread0_epc.h"
#include "objects.h"
#include "asset_loading.h"
#include "math_util.h"
#include "tracks.h"

/************ .rodata ************/

const char D_800E8840[] = "\n\nUnknown trigger type in initParticleTrigger %d, Max %d.\n\n";
const char D_800E887C[] = "\n\nUnknown particle type in initParticleTrigger %d, Max %d.\n\n";
const char D_800E88BC[] = "\n\nUnknown trigger type in initParticleTrigger %d, Max %d.\n\n";
const char D_800E88F8[] = "Sprite Particle buffer is full.\n";
const char D_800E891C[] = "Triangle Particle buffer is full.\n";
const char D_800E8940[] = "Rectangle Particle buffer is full.\n";
const char D_800E8964[] = "Line Particle buffer is full.\n";
const char D_800E8980[] = "Point Particle buffer is full.\n";
const char D_800E89A4[] = "\n\nCan't allocate space for unknown particle type.";
const char D_800E89D8[] = "\n\nParticle has been freed twice, this is Super Safe, Honest!\n";
const char D_800E8A18[] = "\n\nSprite Particle Buffer is empty.\n\n";
const char D_800E8A40[] = "\n\nTriangle Particle Buffer is empty.\n\n";
const char D_800E8A68[] = "\n\nRectangle Particle Buffer is empty.\n\n";
const char D_800E8A90[] = "\n\nLine Particle buffer is empty.\n\n";
const char D_800E8AB4[] = "\n\nPoint Particle buffer is empty.\n\n";
const char D_800E8AD8[] = "\n\nCan't deallocate space for unknown particle type.\n\n";
const char D_800E8B10[] = "\nError :: trigger %x has no reference to point %x";
const char D_800E8B44[] = "\nError :: particle %x is not indexed correctly in trigger list %x (%d >> %p)";

/*********************************/

/************ .data ************/

// I woundn't be suprised if most of these zeroes are really just null pointers.
s32 D_800E2CA0 = 0;
s32 D_800E2CA4 = 0;
ParticleType *D_800E2CA8 = NULL;
s32 D_800E2CAC = 0;
s32 D_800E2CB0 = 0;
ParticleType *D_800E2CB4 = NULL;
s32 D_800E2CB8 = 0;
s32 D_800E2CBC = 0;
ParticleType *D_800E2CC0 = NULL;
s32 D_800E2CC4 = 0;
s32 D_800E2CC8 = 0;
ParticleType *D_800E2CCC = NULL;
s32 D_800E2CD0 = 0;
s32 D_800E2CD4 = 0;
Particle *D_800E2CD8 = NULL;
UNUSED s32 D_800E2CDC = 0; // Only ever and checked for being less than 512.
s32 *D_800E2CE0 = NULL;
s32 *D_800E2CE4 = NULL;
s32 gParticlesAssetTableCount = 0;
s32 *gParticlesAssets = NULL;

ParticleProperties **gParticlesAssetTable = NULL;
s32 gParticleBehavioursAssetTableCount = 0;
s32 *gParticleBehavioursAssets = NULL;
ParticleBehavior **gParticleBehavioursAssetTable = NULL;
ColourRGBA D_800E2D00[2] = {{{{ 0 }}}, {{{ 0 }}}};

// Are these just Triangles?
unk800E2D08 D_800E2D08[5] = {
    { 0x4000, 0x0102, 0x0100, 0x0000, 0x0000, 0x01E0, 0x0100, 0x01E0 },
    { 0x4000, 0x0203, 0x0100, 0x0000, 0x0100, 0x01E0, 0x01E0, 0x01E0 },
    { 0x4001, 0x0204, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000, 0x01E0 },
    { 0x4002, 0x0305, 0x0100, 0x0000, 0x01E0, 0x0000, 0x01E0, 0x01E0 },
    { 0x4000, 0x0103, 0x0100, 0x0000, 0x0000, 0x01E0, 0x01E0, 0x01E0 },
};

Vec3s D_800E2D58[5] = {
    {{{ 0x0000, 0x01FF, 0x01FF }}},
    {{{ 0x0000, 0x01FF, 0x01FF }}},
    {{{ 0x0000, 0x0000, 0x01FF }}},
    {{{ 0x0000, 0x0000, 0x01FF }}},
    {{{ 0x0000, 0x01FF, 0x01FF }}},
};

// Are these just Triangles?
unk800E2D08 D_800E2D78[8] = {
    { 0x0000, 0x0105, 0x0000, 0x0000, 0x0080, 0x0000, 0x0080, 0x01FF },
    { 0x0000, 0x0504, 0x0000, 0x0000, 0x0080, 0x01FF, 0x0000, 0x01FF },
    { 0x0001, 0x0206, 0x0080, 0x0000, 0x0100, 0x0000, 0x0100, 0x01FF },
    { 0x0001, 0x0605, 0x0080, 0x0000, 0x0100, 0x01FF, 0x0080, 0x01FF },
    { 0x0002, 0x0307, 0x0100, 0x0000, 0x0180, 0x0000, 0x0180, 0x01FF },
    { 0x0002, 0x0706, 0x0100, 0x0000, 0x0180, 0x01FF, 0x0100, 0x01FF },
    { 0x0003, 0x0004, 0x0180, 0x0000, 0x0200, 0x0000, 0x0200, 0x01FF },
    { 0x0003, 0x0407, 0x0180, 0x0000, 0x0200, 0x01FF, 0x0180, 0x01FF },
};

Vec3s D_800E2DF8[8] = {
    {{{ 0x0000, 0x0000, 0x01FF }}},
    {{{ 0x0000, 0x01FF, 0x01FF }}},
    {{{ 0x0000, 0x0000, 0x01FF }}},
    {{{ 0x0000, 0x01FF, 0x01FF }}},
    {{{ 0x0000, 0x0000, 0x01FF }}},
    {{{ 0x0000, 0x01FF, 0x01FF }}},
    {{{ 0x0000, 0x0000, 0x01FF }}},
    {{{ 0x0000, 0x01FF, 0x01FF }}},
};

s16 D_800E2E28 = 0;

f32 gParticleGravityTable[8] = {
    0.0f, 0.1, 0.2f, 0.3f, 0.45f, 0.525f, 0.6f, 0.8f
};

s32 D_800E2E4C = 0;
s32 D_800E2E50 = 0;
s32 D_800E2E54 = 0;
s32 D_800E2E58 = 0;
s32 D_800E2E5C = 0;
Sprite **D_800E2E60 = NULL;
s32 D_800E2E64 = 0;

XYStruct gParticleCoordListTri[3] = {
    { 0,  8 },
    { 7, -4 },
    { -7, -4 },
};

XYStruct gParticleCoordListQuad[4] = {
    { -6,  6 },
    { 6,  6 },
    { 6, -6 },
    { -6, -6 },
};

s32 D_800E2E84[16] = {
    0x00000000, 0xC00840FF, 0xFF6008FF, 0x404040FF, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x1070FFFF, 0x00000000, 0x00000000
};

s32 D_800E2EC4[10] = {
    0x404040FF, 0x404040FF, 0x002D00FF, 0x002D00FF, 
    0x403C0AFF, 0x403C0AFF, 0x4040FFFF, 0x4040FFFF, 
    0x404040FF, 0x404040FF
};

s32 gParticleOpacity = 256;

/*******************************/

/************ .bss ************/

s32 gParticleUpdateRate;
s32 D_80127C84;
s32 D_80127C88[6];
//printf.c
//thread0_epc
/******************************/

void func_800AE270(void) {
    func_800AE374();
    func_800AE438();
    func_800AE2D8();
}

void func_800AE2A0(void) {
    func_800AE374();
    func_800AE438();
    func_800AE490();
    func_800AE2D8();
}

void func_800AE2D8(void) {
    s32 i;

    if (D_800E2E60 != NULL) {
        for (i = 0; i < D_800E2E64; i++) {
            free_sprite(D_800E2E60[i]);
        }
        free_from_memory_pool(D_800E2E60);
        D_800E2E60 = 0;
    }
}

void func_800AE374(void) {
    if (D_800E2CA8 != NULL) {
        free_from_memory_pool(D_800E2CA8);
        D_800E2CA8 = NULL;
    }
    if (D_800E2CB4 != NULL) {
        free_from_memory_pool(D_800E2CB4);
        D_800E2CB4 = NULL;
    }
    if (D_800E2CC0 != NULL) {
        free_from_memory_pool(D_800E2CC0);
        D_800E2CC0 = NULL;
    }
    if (D_800E2CCC != NULL) {
        free_from_memory_pool(D_800E2CCC);
        D_800E2CCC = NULL;
    }
    if (D_800E2CD8 != NULL) {
        free_from_memory_pool(D_800E2CD8);
        D_800E2CD8 = NULL;
    }
}

void func_800AE438(void) {
    if (D_800E2CE0 != NULL) {
        free_from_memory_pool(D_800E2CE0);
        D_800E2CE0 = NULL;
    }
    if (D_800E2CE4 != NULL) {
        free_from_memory_pool(D_800E2CE4);
        D_800E2CE4 = NULL;
    }
}

void func_800AE490(void) {
    if (gParticlesAssets != NULL) {
        free_from_memory_pool(gParticlesAssets);
        gParticlesAssets = NULL;
    }
    if (gParticlesAssetTable != NULL) {
        free_from_memory_pool(gParticlesAssetTable);
        gParticlesAssetTable = NULL;
    }
    if (gParticleBehavioursAssets != NULL) {
        free_from_memory_pool(gParticleBehavioursAssets);
        gParticleBehavioursAssets = NULL;
    }
    if (gParticleBehavioursAssetTable != NULL) {
        free_from_memory_pool(gParticleBehavioursAssetTable);
        gParticleBehavioursAssetTable = NULL;
    }
}

void init_particle_assets(void) {
    s32 i;

    func_800AE490();
    gParticlesAssetTable = (ParticleProperties **) load_asset_section_from_rom(ASSET_PARTICLES_TABLE);
    gParticlesAssetTableCount = -1; 
    while (((s32) gParticlesAssetTable[gParticlesAssetTableCount + 1]) != -1) {
        gParticlesAssetTableCount++;
    }

    gParticlesAssets = (s32 *) load_asset_section_from_rom(ASSET_PARTICLES);
    for (i = 0; i < gParticlesAssetTableCount; i++) {
    gParticlesAssetTable[i] = (ParticleProperties *) (((u8 *) gParticlesAssets) + ((s32) gParticlesAssetTable[i]));
    }

    gParticleBehavioursAssetTable = (ParticleBehavior **) load_asset_section_from_rom(ASSET_PARTICLE_BEHAVIORS_TABLE);
    gParticleBehavioursAssetTableCount = -1; 
    while (((s32) gParticleBehavioursAssetTable[gParticleBehavioursAssetTableCount + 1]) != -1) {
        gParticleBehavioursAssetTableCount++;
    }

    gParticleBehavioursAssets = (s32 *) load_asset_section_from_rom(ASSET_PARTICLE_BEHAVIORS);
    for (i = 0; i < gParticleBehavioursAssetTableCount; i++) {
        gParticleBehavioursAssetTable[i] = (ParticleBehavior *) (((u8 *) gParticleBehavioursAssets) + ((s32) gParticleBehavioursAssetTable[i]));
        if (((u32) gParticleBehavioursAssetTable[i]->unk9C) != 0xFFFFFFFF) {
            gParticleBehavioursAssetTable[i]->unk9C = (s32 *) get_misc_asset((s32) gParticleBehavioursAssetTable[i]->unk9C);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/particles/func_800AE728.s")

/**
 * Generate a triangle shaped particle mesh.
 * Use a lookup table to generate the vertices.
*/
void generate_particle_shape_triangle(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
    s16 i;
    Vertex *tempVtx;
    Triangle *tempTri;
    XYStruct *coordList;

    model->vertexCount = 3;
    model->vertices = *vtx;
    tempVtx = *vtx;
    coordList = &gParticleCoordListTri[0];
    for (i = 0; i < 3; i++) {
        tempVtx->x = coordList->x;
        tempVtx->y = coordList->y;
        coordList++;
        tempVtx->z = 0;
        tempVtx->r = 255;
        tempVtx->g = 255;
        tempVtx->b = 255;
        tempVtx->a = 255;
        tempVtx++;
    }
    *vtx = tempVtx;
    model->triangleCount = 1;
    model->triangles = *triangles;
    tempTri = *triangles;
    tempTri->flags = RENDER_UNK_0000040;
    tempTri->vi0 = 2;
    tempTri->vi1 = 1;
    tempTri->vi2 = 0;
    tempTri++;
    *triangles = tempTri;
}

/**
 * Generate a square shaped particle mesh.
 * Use a lookup table to generate the vertices.
*/
void generate_particle_shape_quad(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
    s16 i;
    Vertex *tempVtx;
    Triangle *tempTri;
    XYStruct *coordList;

    model->vertexCount = 4;
    model->vertices = *vtx;
    tempVtx = *vtx;
    coordList = &gParticleCoordListQuad[0];
    for (i = 0; i < 4; i++) {
        tempVtx->x = coordList->x;
        tempVtx->y = coordList->y;
        coordList++;
        tempVtx->z = 0;
        tempVtx->r = 255;
        tempVtx->g = 255;
        tempVtx->b = 255;
        tempVtx->a = 255;
        tempVtx++;
    }
    *vtx = tempVtx;
    model->triangleCount = 2;
    model->triangles = *triangles;
    tempTri = *triangles;
    tempTri[0].flags = RENDER_UNK_0000040;
    tempTri[0].vi0 = 3;
    tempTri[0].uv0.u = 0;
    tempTri[0].vi1 = 1;
    tempTri[0].uv1.v = 0;
    tempTri[0].vi2 = 0;
    tempTri[0].uv2.u = 0;
    tempTri[0].uv2.v = 0;
    tempTri[1].flags = RENDER_UNK_0000040;
    tempTri[1].vi0 = 3;
    tempTri[1].uv0.u = 0;
    tempTri[1].vi1 = 2;
    tempTri[1].vi2 = 1;
    tempTri[1].uv2.v = 0;
    tempTri += 2;
    *triangles = tempTri;
}

void func_800AEF88(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
    s32 i;
    Vertex *tempVtx;

    model->vertexCount = 6;
    model->triangleCount = 4;
    model->vertices = *vtx;
    model->triangles = *triangles;
    tempVtx = *vtx;
    for (i = 0; i < 6; i++) {
        tempVtx->r = 255;
        tempVtx->g = 255;
        tempVtx->b = 255;
        tempVtx->a = 255;
        tempVtx++;
    }
    *vtx = tempVtx;
}

void func_800AF024(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
    s32 i;
    Vertex *tempVtx;

    model->vertexCount = 8;
    model->triangleCount = 8;
    model->vertices = *vtx;
    model->triangles = *triangles;
    tempVtx = *vtx;
    for (i = 0; i < 16; i++) {
        tempVtx->r = 255;
        tempVtx->g = 255;
        tempVtx->b = 255;
        tempVtx->a = 255;
        tempVtx++;
    }
    *vtx = tempVtx;
}

void func_800AF0A4(Particle *particle) {
    Object_44 *temp_v0;
    Object_44_C *temp_v1;
    s16 temp_t1, temp_t8_0;
    s32 temp_t8;

    temp_v0 = (Object_44 *) particle->modelData;
    temp_v1 = temp_v0->unkC;
    temp_t8_0 = (temp_v0->unk0->unk0 - 1) << 5;
    temp_t8 = (s32)temp_t8_0;
    temp_t1 = (temp_v0->unk0->unk1 - 1) << 5;
    temp_v1->unk4 = temp_t8 >> 1;
    temp_v1->unk6 = 0;
    temp_v1->unk8 = 0;
    temp_v1->unkA = temp_t1;
    temp_v1->unkC = temp_t8;
    temp_v1->unkE = temp_t1;
}

void func_800AF0F0(Particle *particle) {
    Object_44 *temp_v0;
    Object_44_C *temp_v1;
    s16 temp_t8, temp_t1;

    temp_v0 = (Object_44 *) particle->modelData;
    temp_v1 = temp_v0->unkC;
    temp_t8 = (temp_v0->unk0->unk0 - 1) << 5;
    temp_t1 = (temp_v0->unk0->unk1 - 1) << 5;
    temp_v1->unk6 = temp_t1;
    temp_v1->unk8 = temp_t8;
    temp_v1->unk16 = temp_t8;
    temp_v1->unk18 = temp_t8;
    temp_v1->unk1A = temp_t1;
    temp_v1->unk1C = temp_t8;
}

void func_800AF134(Particle *particle, s32 behaviourID, s32 propertyID, s16 velX, s16 velY, s16 velZ) {
    ParticleBehavior *behaviour;
    if (propertyID >= gParticlesAssetTableCount) {
        propertyID = 0;
    }
    if (behaviourID >= gParticleBehavioursAssetTableCount) {
        behaviourID = 0;
    }
    behaviour = gParticleBehavioursAssetTable[behaviourID];
    if (particle->data.propertyID != propertyID || behaviour != particle->data.behaviour) {
        func_800B2260(particle);
        func_800AF29C(particle, behaviourID, propertyID, velX, velY, velZ);
    }
}

void partInitTrigger(Particle *particle, s32 behaviourID, s32 propertyID) {
    ParticleBehavior *behaviour;

    if (behaviourID < gParticleBehavioursAssetTableCount) {
        behaviour = gParticleBehavioursAssetTable[behaviourID];
        func_800AF29C(particle, behaviourID, propertyID, behaviour->velX, behaviour->velY, behaviour->velZ);
    }
}

void func_800AF29C(Particle *arg0, s32 behaviourID, s32 propertyID, s16 velX, s16 velY, s16 velZ) {
    ParticleBehavior *behaviour;
    s32 flags;

    behaviour = gParticleBehavioursAssetTable[behaviourID];
    arg0->data.propertyID = propertyID;
    arg0->data.behaviour = behaviour;
    arg0->data.baseVelX = velX;
    arg0->data.baseVelY = velY;
    arg0->data.baseVelZ = velZ;
    arg0->data.unk1E = 0;

    flags = behaviour->flags;

    if (flags & 0x4000) {
        arg0->data.flags = 0x4000;
        arg0->data.unk6 = 0;
        arg0->data.pos.x = 0.0f;
        arg0->data.pos.y = 0.0f;
        arg0->data.pos.z = 0.0f;
    } else if (flags & 0x400) {
        arg0->data.unk6 = 0;
        arg0->data.flags = 0x400;
        if (gParticlesAssetTable[propertyID]->lifeTime <= 255) {
            arg0->data.lifeTime = gParticlesAssetTable[propertyID]->lifeTime;
        } else {
            arg0->data.lifeTime = 255;
        }
        arg0->data.unkC_400.unkC = (s32 *) allocate_from_main_pool_safe(arg0->data.lifeTime * sizeof(uintptr_t), COLOUR_TAG_SEMITRANS_GREY);
        arg0->data.unkC_400.unk10 = behaviour->unk14;
        arg0->data.unkC_400.unk12 = behaviour->unk16;
        arg0->data.unkC_400.unk14 = behaviour->unk22;
        arg0->data.unkC_400.unk16 = behaviour->unk24;
    } else {
        arg0->data.flags = 0;
        arg0->data.angle.y_rotation = behaviour->unk14;
        arg0->data.angle.x_rotation = behaviour->unk16;
        arg0->data.angle.z_rotation = behaviour->unk18;
        arg0->data.angle.y_direction = behaviour->unk22;
        arg0->data.angle.x_direction = behaviour->unk24;
        arg0->data.angle.z_direction = behaviour->unk26;
    }
}

#ifdef NON_EQUIVALENT

// Should be functionally equivalent.
void func_800AF404(s32 arg0) {
    s32 i;

    D_800E2E28 = (D_800E2E28 + (arg0 * 64)) & 0x1FF;
    for (i = 0; i < 5; i++) {
        D_800E2D08[i].unk6 = D_800E2D58[i].y_rotation + D_800E2E28;
        D_800E2D08[i].unkA = D_800E2D58[i].x_rotation + D_800E2E28;
        D_800E2D08[i].unkE = D_800E2D58[i].z_rotation + D_800E2E28;
    }
    for (i = 0; i < 8; i++) {
        D_800E2D78[i].unk6 = D_800E2DF8[i].y_rotation + D_800E2E28;
        D_800E2D78[i].unkA = D_800E2DF8[i].x_rotation + D_800E2E28;
        D_800E2D78[i].unkE = D_800E2DF8[i].z_rotation + D_800E2E28;
    }
}

#else
GLOBAL_ASM("asm/non_matchings/particles/func_800AF404.s")
#endif

void func_800AF52C(Object *obj, s32 arg1) {
    s32 i;
    Particle *temp_v0;
    ParticleBehavior *behaviour;
    Particle *temp;

    temp_v0 = (Particle *) &obj->unk6C[arg1];
    behaviour = temp_v0->data.behaviour;
    temp_v0->data.opacity = 0;
    if (temp_v0->data.flags & 0x4000) {
        temp_v0->segment.trans.x_position = obj->segment.trans.x_position;
        temp_v0->segment.trans.y_position = obj->segment.trans.y_position;
        temp_v0->segment.trans.z_position = obj->segment.trans.z_position;
    } else if (temp_v0->data.flags & 0x400) {
        temp_v0->data.opacity = gParticlesAssetTable[temp_v0->data.propertyID]->colour.a << 8;

        if (temp_v0->data.unk6 > 0) { // Useless if statement, since the loop already does this.
            for (i = 0; i < temp_v0->data.unk6; i++){
                temp = temp_v0->data.unkC_60[i];
                temp->segment.particle.destroyTimer = 0;
            }
        }
        if (behaviour->flags & 1) {
            temp_v0->data.angle.z_rotation = behaviour->unk14;
            temp_v0->data.angle.y_direction = behaviour->unk16;
        }
        if (behaviour->flags & 4) {
            temp_v0->data.angle.x_direction = behaviour->unk22;
            temp_v0->data.angle.z_direction = behaviour->unk24;
        }
    } else {
        if (behaviour->flags & 1) {
            temp_v0->data.unk6 = 0;
            temp_v0->data.angle.y_rotation = behaviour->unk14;
            temp_v0->data.angle.x_rotation = behaviour->unk16;
            temp_v0->data.angle.z_rotation = behaviour->unk18;
        }
        if (behaviour->flags & 4) {
            temp_v0->data.lifeTime = 0;
            temp_v0->data.angle.y_direction = behaviour->unk22;
            temp_v0->data.angle.x_direction = behaviour->unk24;
            temp_v0->data.angle.z_direction = behaviour->unk26;
        }
    }
    temp_v0->data.flags &= 0xFDFF;
    temp_v0->data.flags |= 0xA000;
    obj->segment.unk1A++;
}

void func_800AF6E4(Object *obj, s32 arg1) {
    Object_6C *obj6C;

    obj6C = &obj->unk6C[arg1];

    obj6C->unk4 &= 0x7FFF;
    obj->segment.unk1A--;
}

GLOBAL_ASM("asm/non_matchings/particles/func_800AF714.s")
GLOBAL_ASM("asm/non_matchings/particles/func_800AFC3C.s")

void func_800AFE5C(Particle *arg0, Particle *arg1) {
    Particle *temp_s0;
    Particle *tempObj;
    Particle *tempObj2;
    s32 i;
    ParticleBehavior *temp_s4;

    temp_s4 = arg1->data.behaviour;
    if (arg1->data.flags & 0x4000) {
        tempObj = func_800B0BAC();
        if (tempObj != NULL) {
            func_8000E9D0((Object *) tempObj);
        }
        arg1->data.flags &= 0xDFFF;
        if (arg1->data.unk6 + 64 > 255) {
            arg1->data.unk6 = 255;
        } else {
            arg1->data.unk6 += 64;
        }
    } else if (arg1->data.flags & 0x400) {
        if (arg1->data.unk6 < arg1->data.lifeTime) {
            temp_s0 = func_800B0698(arg0, arg1);
            arg1->data.flags &= 0xDFFF;
            if (temp_s0 != NULL) {
                func_8000E9D0((Object *) temp_s0);
                temp_s0->unk74 = arg1->data.unk6;
                temp_s0->segment.unk40 |= 0x2000;
                arg1->data.unkC_60[arg1->data.unk6] = temp_s0;
                arg1->data.unk6++;
            }
        }
    } else {
        while (arg1->data.opacity >= temp_s4->unk40) {
            arg1->data.opacity -= temp_s4->unk40;
            for (i = 0; i < temp_s4->unk42; i++) {
                tempObj2 = func_800B1130(arg0, arg1);
                if (tempObj2 != NULL) {
                    func_8000E9D0((Object *) tempObj2);
                    handle_particle_movement(tempObj2, arg1->data.opacity);
                }
                arg1->data.flags &= ~0x2000;
            }
        }
    }
}

void func_800B0010(Particle *arg0, Particle *arg1, Particle *arg2, ParticleBehavior *arg3) {
    s32 flags;
    Vec3f velocityPos;
    Vec3s angle;

    if (arg3->flags & 0x70) {
        arg0->segment.x_velocity = arg3->unk30;
        arg0->segment.y_velocity = arg3->unk34;
        arg0->segment.z_velocity = arg3->unk38;
    } else {
        arg0->segment.x_velocity = 0.0f;
        arg0->segment.y_velocity = 0.0f;
        arg0->segment.z_velocity = 0.0f;
    }
    flags = arg3->behaviourFlags & (PARTICLE_VEL_Z | PARTICLE_VEL_Y | PARTICLE_VEL_X);
    if (flags) {
        if (flags & PARTICLE_VEL_X) {
            arg0->segment.x_velocity += (f32) get_random_number_from_range(-arg3->velocityRangeX1, arg3->velocityRangeX1) * 0.00001525878906;
        }
        if (flags & PARTICLE_VEL_Y) {
            arg0->segment.y_velocity += (f32) get_random_number_from_range(-arg3->velocityRangeY1, arg3->velocityRangeY1) * 0.00001525878906;
        }
        if (flags & PARTICLE_VEL_Z) {
            arg0->segment.z_velocity += (f32) get_random_number_from_range(-arg3->velocityRangeZ1, arg3->velocityRangeZ1) * 0.00001525878906;
        }
    }
    switch (arg3->flags & (0x40 | 0x20 | 0x10)) {
        case 0x10:
            arg0->segment.x_velocity += arg1->segment.x_velocity;
            arg0->segment.y_velocity += arg1->segment.y_velocity;
            arg0->segment.z_velocity += arg1->segment.z_velocity;
            break;
        case 0x40:
            arg0->segment.x_velocity *= arg1->segment.x_velocity;
            arg0->segment.y_velocity *= arg1->segment.y_velocity;
            arg0->segment.z_velocity *= arg1->segment.z_velocity;
            break;
    }
    if (arg3->flags & 4) {
        velocityPos.x = 0.0f;
        velocityPos.y = 0.0f;
        velocityPos.z = -arg3->unk3C;
        flags = arg3->behaviourFlags;
        if (flags & PARTICLE_UNK00000010) {
            velocityPos.z += (f32) get_random_number_from_range(-arg3->gravityRange2, arg3->gravityRange2) * 0.00001525878906;
        }
        if (flags & (PARTICLE_UNK00000040 | PARTICLE_UNK00000020)) {
            angle.y_rotation = arg2->data.angle.y_direction;
            if (flags & PARTICLE_UNK00000020) {
                angle.y_rotation += get_random_number_from_range(-arg3->angleRangeY2, arg3->angleRangeY2);
            }
            angle.x_rotation = arg2->data.angle.x_direction;
            if (flags & PARTICLE_UNK00000040) {
                angle.x_rotation += get_random_number_from_range(-arg3->angleRangeX2, arg3->angleRangeX2);
            }
            f32_vec3_apply_object_rotation3((ObjectTransform* ) &angle, (f32*) &velocityPos);
        } else {
            f32_vec3_apply_object_rotation3((ObjectTransform* ) &arg2->data.angle.y_direction, (f32*) &velocityPos);
        }
        f32_vec3_apply_object_rotation((ObjectTransform* ) arg0->segment.unk3C, (f32*) &velocityPos);
        arg0->segment.x_velocity += velocityPos.x;
        arg0->segment.y_velocity += velocityPos.y;
        arg0->segment.z_velocity += velocityPos.z;
    }
}

void func_800B03C0(Particle *particle, Particle *arg1, Particle *arg2, ParticleBehavior *behaviour) {
    s32 flags;
    Vec3f posVel;
    Vec3s angle;

    particle->baseVelX = arg2->data.baseVelX;
    particle->baseVelY = arg2->data.baseVelY;
    particle->baseVelZ = arg2->data.baseVelZ;
    particle->forwardVel = behaviour->forwardVel;
    if (behaviour->behaviourFlags & PARTICLE_FORWARDVEL) {
        particle->forwardVel += (f32) get_random_number_from_range(-behaviour->velocityRange, behaviour->velocityRange) * 0.00001525878906; // 0.00001525878906 ~= 1.0/65536.0
    }
    if (behaviour->flags & 1) {
        posVel.x = 0.0f;
        posVel.y = 0.0f;
        posVel.z = -behaviour->unk10;
        flags = behaviour->behaviourFlags;
        if (flags & PARTICLE_GRAVITY) {
            posVel.z += (f32) get_random_number_from_range(-behaviour->gravityRange1, behaviour->gravityRange1) * 0.00001525878906;
        }
        if (flags & (PARTICLE_UNK00000004 | PARTICLE_UNK00000002)) {
            angle.y_rotation = arg2->data.angle.y_rotation;
            if (flags & PARTICLE_UNK00000002) {
                angle.y_rotation += get_random_number_from_range(-behaviour->angleRangeY1, behaviour->angleRangeY1);
            }
            angle.x_rotation = arg2->data.angle.x_rotation;
            if (flags & PARTICLE_UNK00000004) {
                angle.x_rotation += get_random_number_from_range(-behaviour->angleRangeX1, behaviour->angleRangeX1);
            }
            f32_vec3_apply_object_rotation3((ObjectTransform* ) &angle, (f32 *) &posVel);
        } else {
            f32_vec3_apply_object_rotation((ObjectTransform* ) &arg2->data.angle.y_rotation, (f32 *) &posVel);
        }
        particle->baseVelX += posVel.x;
        particle->baseVelY += posVel.y;
        particle->baseVelZ += posVel.z;
    }
    if (particle->segment.particle.movementType != PARTICLE_MOVEMENT_BASIC_PARENT) {
        f32_vec3_apply_object_rotation((ObjectTransform *) arg1, &particle->baseVelX);
    }
    particle->segment.trans.x_position = particle->baseVelX;
    particle->segment.trans.y_position = particle->baseVelY;
    particle->segment.trans.z_position = particle->baseVelZ;
    if (particle->segment.particle.movementType == PARTICLE_MOVEMENT_BASIC_PARENT) {
        f32_vec3_apply_object_rotation((ObjectTransform *) arg1, &particle->segment.trans.x_position);
    }
    particle->segment.trans.x_position += arg1->segment.trans.x_position;
    particle->segment.trans.y_position += arg1->segment.trans.y_position;
    particle->segment.trans.z_position += arg1->segment.trans.z_position;
}

Particle *func_800B0698(Particle *arg0, Particle *arg1) {
    ParticleProperties *properties;
    Particle *var_v0;
    TextureHeader **texture;
    ParticleBehavior *sp20;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f2;

    properties = gParticlesAssetTable[arg1->data.propertyID];
    if (properties->unk0 != 4) {
        return NULL;
    }
    sp20 = arg1->data.behaviour;
    var_v0 = func_800B1CB8(4);
    if (var_v0 == NULL) {
        return var_v0;
    }
    var_v0->segment.particle.blockID = arg0->segment.particle.blockID;
    var_v0->segment.trans.flags = -OBJ_FLAGS_DEACTIVATED;
    var_v0->segment.particle.movementType = properties->movementType;
    var_v0->segment.unk40 = properties->unk2;
    var_v0->segment.unk3C = arg0;
    var_v0->unk70 = arg1;
    var_v0->segment.trans.scale = properties->scale * sp20->unk50;
    var_v0->segment.scaleVel = properties->scale * sp20->unk54;
    var_v0->segment.particle.destroyTimer = properties->lifeTime;
    var_v0->segment.particle.unk34 = 0.0f;
    var_v0->segment.particle.unk38 = 0.0f;
    var_v0->colour.r = properties->colour.r;
    var_v0->colour.g = properties->colour.g;
    var_v0->colour.b = properties->colour.b;
    var_v0->colour.a = properties->colour.a;
    if (var_v0->segment.unk40 & 0x800 && arg0->unk54_ptr != NULL) {
        var_v0->brightness = *arg0->unk54_ptr * 255.0f;
    } else {
        var_v0->brightness = 255;
    }
    var_v0->opacityTimer = properties->opacityTimer;
    if (arg1->data.flags & 0x100) {
        var_v0->opacity = arg1->data.opacity;
    } else {
        var_v0->opacity = properties->opacity << 8;
    }
    if (properties->opacity < 255) {
        if (var_v0->segment.unk40 & 0x1000) {
            var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
        } else {
            var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
        }
    }
    if (var_v0->opacityTimer < var_v0->segment.particle.destroyTimer) {
        var_v0->opacityVel = ((properties->opacityVel << 8) - (var_v0->opacity & 0xFFFF)) / (var_v0->segment.particle.destroyTimer - var_v0->opacityTimer);
    } else {
        var_v0->opacityVel = 0;
    }
    func_800B03C0(var_v0, arg0, arg1, sp20);
    if (sp20->flags & 0x80) {
        var_v0->segment.trans.y_rotation = sp20->angleOffsetY;
        var_v0->segment.trans.x_rotation = sp20->angleOffsetX;
        var_v0->segment.trans.z_rotation = sp20->angleOffsetZ;
    } else {
        var_v0->segment.trans.y_rotation = arg0->segment.trans.y_rotation + sp20->angleOffsetY;
        var_v0->segment.trans.x_rotation = arg0->segment.trans.x_rotation + sp20->angleOffsetX;
        var_v0->segment.trans.z_rotation = arg0->segment.trans.z_rotation + sp20->angleOffsetZ;
    }
    var_v0->angleVelY = sp20->angleVelY;
    var_v0->angleVelX = sp20->angleVelX;
    var_v0->angleVelZ = sp20->angleVelZ;
    func_800B0010(var_v0, arg0, arg1, sp20);
    var_v0->gravity = gParticleGravityTable[(var_v0->segment.unk40 >> 4) & 7];
    if (var_v0->segment.particle.movementType == PARTICLE_MOVEMENT_VELOCITY) {
        temp_f0 = var_v0->segment.x_velocity;
        temp_f2 = var_v0->segment.y_velocity;
        temp_f14 = var_v0->segment.z_velocity;
        var_v0->forwardVel = sqrtf((temp_f0 * temp_f0) + (temp_f2 * temp_f2) + (temp_f14 * temp_f14));
    }
    if (sp20->flags & 2) {
        arg1->data.angle.z_rotation += sp20->unk1C;
        arg1->data.angle.y_direction += sp20->unk1E;
    }
    if (sp20->flags & 8) {
        arg1->data.angle.x_direction += sp20->unk2A;
        arg1->data.angle.z_direction += sp20->unk2C;
    }
    var_v0->segment.unk1A = properties->unk6;
    var_v0->segment.textureFrame = 0;
    texture = &var_v0->modelData->texture;
    if (properties->textureID == -1) {
        *texture = NULL;
    } else {
        *texture = load_texture(properties->textureID);
        if ((*texture) != NULL) {
            if ((*texture)->flags & 4) {
                if (var_v0->segment.unk40 & 0x1000) {
                    var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
                }
            }
            if ((var_v0->segment.unk40 & 3) == 2) {
                var_v0->segment.textureFrame = (*texture)->numOfTextures - 1;
            }
        }
    }
    var_v0->modelFrame = 0;
    var_v0->unk76 = ((u32) (u16) properties->lifeTimeRange) >> 10;
    var_v0->unk77 = 0;
    if (*texture == NULL) {
        func_800B2040(var_v0);
        return NULL;
    }
    return var_v0;
}

GLOBAL_ASM("asm/non_matchings/particles/func_800B0BAC.s")

Particle *func_800B1130(Particle *arg0, Particle *arg1) {
    s32 flags;
    ParticleProperties *properties;
    Particle* var_v0;
    TextureHeader **texture;
    ParticleBehavior *behaviour;
    unk800B1130_SP28 *sp28;
    f32 sp24;
    s8 sp23;
    
    properties = gParticlesAssetTable[arg1->data.propertyID];
    if (properties->unk0 == 3 || properties->unk0 == 4) {
        return NULL;
    }
    behaviour = arg1->data.behaviour;
    sp28 = (unk800B1130_SP28 *) behaviour->unk9C;
    
    var_v0 = func_800B1CB8(properties->unk0);
    if (var_v0 == NULL) {
        return var_v0;
    }
    var_v0->segment.particle.blockID = arg0->segment.particle.blockID;
    var_v0->segment.trans.flags = -OBJ_FLAGS_DEACTIVATED;
    var_v0->segment.particle.movementType = properties->movementType;
    var_v0->segment.unk40 = properties->unk2;
    var_v0->segment.unk3C = arg0;
    if (var_v0->segment.unk40 & 0x800 && arg0->unk54_ptr != NULL) {
        var_v0->brightness = *arg0->unk54_ptr * 255.0f;
    } else {
        var_v0->brightness = 255;
    }
    sp24 = behaviour->unk50;
    if (behaviour->behaviourFlags & PARTICLE_UNK00020000) {
        sp24 += (f32) get_random_number_from_range(-behaviour->unk8C, behaviour->unk8C) * 0.00001525878906;
    }
    var_v0->segment.trans.scale = properties->scale * sp24;
    sp24 = behaviour->unk54;
    if (behaviour->behaviourFlags & PARTICLE_UNK00040000) {
        sp24 += (f32) get_random_number_from_range(-behaviour->unk90, behaviour->unk90) * 0.00001525878906;
    }
    if (behaviour->flags & 0x1000) {
        var_v0->segment.scaleVel = sqrtf((arg0->segment.x_velocity * arg0->segment.x_velocity) + (arg0->segment.y_velocity * arg0->segment.y_velocity) + (arg0->segment.z_velocity * arg0->segment.z_velocity)) * sp24 * 0.1f;
    } else {
        var_v0->segment.scaleVel = properties->scale * sp24;
    }
    var_v0->segment.particle.destroyTimer = get_random_number_from_range(-properties->lifeTimeRange, properties->lifeTimeRange) + properties->lifeTime;
    var_v0->segment.particle.unk38 = 0.0f;
    var_v0->segment.particle.unk34 = 0.0f;
    if (D_800E2D00[0].word != 0) {
        var_v0->colour.word = D_800E2D00[0].word;
    } else if ((s32) sp28 != -1) {
        arg1->data.unk1E++;
        if (arg1->data.unk1E >= sp28->unk0) {
            arg1->data.unk1E = 0;
        }
        var_v0->colour.r = sp28[arg1->data.unk1E + 2].r;
        var_v0->colour.g = sp28[arg1->data.unk1E + 2].g;
        var_v0->colour.b = sp28[arg1->data.unk1E + 2].b;
        var_v0->colour.a = sp28[arg1->data.unk1E + 2].a;
    } else {
        var_v0->colour.r = properties->colour.r;
        var_v0->colour.g = properties->colour.g;
        var_v0->colour.b = properties->colour.b;
        var_v0->colour.a = properties->colour.a;
    }
    flags = behaviour->behaviourFlags & (PARTICLE_COLOURVEL_ALPHA | PARTICLE_COLOURVEL_BLUE | PARTICLE_COLOURVEL_GREEN | PARTICLE_COLOURVEL_RED);
    if (flags) {
        if (flags & PARTICLE_COLOURVEL_RED) {
            var_v0->colour.r += get_random_number_from_range(-behaviour->colourRangeR, behaviour->colourRangeR);
        }
        if (flags & PARTICLE_COLOURVEL_GREEN) {
            var_v0->colour.g += get_random_number_from_range(-behaviour->colourRangeG, behaviour->colourRangeG);
        }
        if (flags & PARTICLE_COLOURVEL_BLUE) {
            var_v0->colour.b += get_random_number_from_range(-behaviour->colourRangeB, behaviour->colourRangeB);
        }
        if (flags & PARTICLE_COLOURVEL_ALPHA) {
            var_v0->colour.a += get_random_number_from_range(-behaviour->colourRangeA, behaviour->colourRangeA);
        }
    }
    var_v0->opacityTimer = properties->opacityTimer;
    var_v0->opacity = properties->opacity * gParticleOpacity;
    if (properties->opacity < 255) {
        if (var_v0->segment.unk40 & 0x1000) {
            var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
        } else {
            var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
        }
    }
    if (var_v0->opacityTimer < var_v0->segment.particle.destroyTimer) {
        var_v0->opacityVel = (s16) (((properties->opacityVel - properties->opacity) * gParticleOpacity) / (var_v0->segment.particle.destroyTimer - var_v0->opacityTimer));
    } else {
        var_v0->opacityVel = 0;
    }
    sp23 = 0;
    var_v0->segment.unk1A = properties->unk6;
    if (var_v0->segment.particle.unk2C == 0x80) {
        var_v0->modelData = (ParticleModel *) func_8007C12C(properties->textureID, 0);
        if (var_v0->modelData) {
            if ((*var_v0->unk44_1->unk8)->unk6 & 4) {
                if (var_v0->segment.unk40 & 0x1000) {
                    var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
                }
            }
            if (behaviour->flags & PARTICLE_ANGLE_Y) {
                var_v0->segment.textureFrame = get_random_number_from_range(0, var_v0->unk44_1->textureCount - 1) << 8;
                if ((var_v0->segment.unk40 & 3) == 2) {
                    var_v0->segment.textureFrame |= 0xFF;
                }
            } else if ((var_v0->segment.unk40 & 3) == 2) {
                var_v0->segment.textureFrame = (var_v0->unk44_1->textureCount << 8) - 1;
            } else {
                var_v0->segment.textureFrame = 0;
            }
        } else {
            sp23 = 1;
        }
    } else if ((var_v0->segment.particle.unk2C == 2) || (var_v0->segment.particle.unk2C == 1)) {
        texture = &var_v0->modelData->texture;
        if (texture) {
            *texture = load_texture(properties->textureID);
            if (*texture != NULL) {
                if ((*texture)->flags & 4) {
                    if (var_v0->segment.unk40 & 0x1000) {
                        var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                    } else {
                        var_v0->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
                    }
                }
                if (behaviour->flags & 0x800) {
                    var_v0->segment.textureFrame = get_random_number_from_range(0, ((*texture)->numOfTextures >> 8) - 1) << 8;
                    if ((var_v0->segment.unk40 & 3) == 2) {
                        var_v0->segment.textureFrame |= 0xFF;
                    }
                } else if ((var_v0->segment.unk40 & 3) == 2) {
                    var_v0->segment.textureFrame = (*texture)->numOfTextures - 1;
                } else {
                    var_v0->segment.textureFrame = 0;
                }
            } else {
                sp23 = 1;
            }
        }
    }
    if (sp23 == 0) {
        if (var_v0->segment.particle.unk2C == 1) {
            func_800AF0A4(var_v0);
        }
        if (var_v0->segment.particle.unk2C == 2) {
            func_800AF0F0(var_v0);
        }
    }
    func_800B03C0(var_v0, arg0, arg1, behaviour);
    if (behaviour->flags & 0x80) {
        var_v0->segment.trans.y_rotation = behaviour->angleOffsetY;
        var_v0->segment.trans.x_rotation = behaviour->angleOffsetX;
        var_v0->segment.trans.z_rotation = behaviour->angleOffsetZ;
    } else {
        var_v0->segment.trans.y_rotation = arg0->segment.trans.y_rotation + behaviour->angleOffsetY;
        var_v0->segment.trans.x_rotation = arg0->segment.trans.x_rotation + behaviour->angleOffsetX;
        var_v0->segment.trans.z_rotation = arg0->segment.trans.z_rotation + behaviour->angleOffsetZ;
    }
    flags = behaviour->behaviourFlags & (PARTICLE_ANGLE_Z | PARTICLE_ANGLE_X | PARTICLE_ANGLE_Y);
    if (flags != 0) {
        if (flags & PARTICLE_ANGLE_Y) {
            var_v0->segment.trans.y_rotation += get_random_number_from_range(-behaviour->angleRangeY3, behaviour->angleRangeY3);
        }
        if (flags & PARTICLE_ANGLE_X) {
            var_v0->segment.trans.x_rotation += get_random_number_from_range(-behaviour->angleRangeX3, behaviour->angleRangeX3);
        }
        if (flags & PARTICLE_ANGLE_Z) {
            var_v0->segment.trans.z_rotation += get_random_number_from_range(-behaviour->angleRangeZ3, behaviour->angleRangeZ3);
        }
    }
    var_v0->angleVelY = behaviour->angleVelY;
    var_v0->angleVelX = behaviour->angleVelX;
    var_v0->angleVelZ = behaviour->angleVelZ;
    flags = behaviour->behaviourFlags & (PARTICLE_ANGLEVEL_Z | PARTICLE_ANGLEVEL_X | PARTICLE_ANGLEVEL_Y);
    if (flags) {
        if (flags & PARTICLE_ANGLEVEL_Y) {
            var_v0->angleVelY += get_random_number_from_range(-behaviour->unk86, behaviour->unk86);
        }
        if (flags & PARTICLE_ANGLEVEL_X) {
            var_v0->angleVelX += get_random_number_from_range(-behaviour->unk88, behaviour->unk88);
        }
        if (flags & PARTICLE_ANGLEVEL_Z) {
            var_v0->angleVelZ += get_random_number_from_range(-behaviour->unk8A, behaviour->unk8A);
        }
    }
    func_800B0010(var_v0, arg0, arg1, behaviour);
    var_v0->gravity = gParticleGravityTable[(var_v0->segment.unk40 >> 4) & 7];
    if (var_v0->segment.particle.movementType == PARTICLE_MOVEMENT_VELOCITY) {
        var_v0->forwardVel = sqrtf((var_v0->segment.x_velocity * var_v0->segment.x_velocity) + (var_v0->segment.y_velocity * var_v0->segment.y_velocity) + (var_v0->segment.z_velocity * var_v0->segment.z_velocity));
    }
    if (behaviour->flags & 2) {
        arg1->data.unk6++;
        if (arg1->data.unk6 >= behaviour->unk1A) {
            arg1->data.angle.y_rotation += behaviour->unk1C;
            arg1->data.angle.x_rotation += behaviour->unk1E;
            arg1->data.angle.z_rotation += behaviour->unk18;
            arg1->data.unk6 -= behaviour->unk1A;
        }
    }
    if (behaviour->flags & 8) {
        arg1->data.lifeTime++;
        if (arg1->data.lifeTime >= behaviour->unk28) {
            arg1->data.angle.y_direction += behaviour->unk2A;
            arg1->data.angle.x_direction += behaviour->unk2C;
            arg1->data.angle.z_direction += behaviour->unk2E;
            arg1->data.lifeTime -= behaviour->unk28;
        }
    }
    if (var_v0->modelData == NULL) {
        func_800B2040(var_v0);
        return NULL;
    } else {   
        return var_v0;
    }
}


Particle *func_800B1CB8(s32 arg0) {
    s32 i;
    Particle *var_v1;

    var_v1 = NULL;
    i = 0;

    switch(arg0) {
        case 0x80:
            if ((D_800E2CC0 != NULL)) {
                if (D_800E2CB8 >= D_800E2E54 - 1) {
                    if (D_800E2CBC == 0) {
                        D_800E2CBC = 1;
                    }
                } else {
                    while(D_800E2CC0[i].unk2C != 0) {
                        i++;
                    }
                    D_800E2CC0[i].unk2C = 0x80;
                    D_800E2CB8++;
                    var_v1 = (Particle *) &D_800E2CC0[i];
                }
            }
            break;
        case 1:
            if (D_800E2CA8 != NULL) {
                if (D_800E2CA0 >= D_800E2E4C - 1) {
                    if (D_800E2CA4 == 0) {
                        D_800E2CA4 = 1;
                    }
                } else {
                    while (D_800E2CA8[i].unk2C != 0) {
                        i++;
                    }
                    D_800E2CA8[i].unk2C = 1;
                    D_800E2CA0++;
                    var_v1 = (Particle *) &D_800E2CA8[i];
                }
            }
            break;
        case 2:
            if (D_800E2CB4 != NULL) {
                if (D_800E2CAC >= D_800E2E50 - 1) {
                    if (D_800E2CB0 == 0) {
                        D_800E2CB0 = 1;
                    }
                } else {
                    while (D_800E2CB4[i].unk2C != 0) {
                        i++;
                    }
                    D_800E2CB4[i].unk2C = 2;
                    D_800E2CAC++;
                    var_v1 = (Particle *) &D_800E2CB4[i];
                }
            }
            break;
        case 3:
            if (D_800E2CCC != NULL) {
                if (D_800E2CC4 >= D_800E2E58 - 1) {
                    if (D_800E2CC8 == 0) {
                        D_800E2CC8 = 1;
                    }
                } else {
                    while (D_800E2CCC[i].unk2C != 0) {
                        i++;
                    }
                    D_800E2CCC[i].unk2C = 3;
                    D_800E2CC4++;
                    var_v1 = (Particle *) &D_800E2CCC[i];
                }
            }
            break;
        case 4:
            if (D_800E2CD8 != NULL) {
                if (D_800E2CD0 >= D_800E2E5C - 1) {
                    if (D_800E2CD4 == 0) {
                        D_800E2CD4 = 1;
                    }
                } else {
                    while (D_800E2CD8[i].segment.particle.unk2C != 0) {
                        i++;
                    }
                    D_800E2CD8[i].segment.particle.unk2C = 4;
                    D_800E2CD0++;
                    var_v1 = (Particle *) &D_800E2CD8[i];
                }
            }
            break;
    }
    if (var_v1 != NULL) {
        var_v1->behaviorId = -1;
    }
    return var_v1;
}

void func_800B2040(Particle *arg0) {
    TextureHeader *tex;

    switch (arg0->segment.particle.unk2C) {
    case 0x80:
        if (D_800E2CB8 > 0) {
            if (arg0->modelData) {
                free_sprite((Sprite *) &arg0->modelData->texture);
            }
            D_800E2CB8--;
            arg0->segment.particle.unk2C = 0;
        }
        break;
    case 0:
        return;
    case 1:
        if (D_800E2CA0 > 0) {
            tex = arg0->modelData->texture;
            if (tex != NULL) {
                free_texture(tex);
            }
            D_800E2CA0--;
            arg0->segment.particle.unk2C = 0;
        }
        break;
    case 2:
        if (D_800E2CAC > 0) {
            tex = arg0->modelData->texture;
            if (tex != NULL) {
                free_texture(tex);
            }
            D_800E2CAC--;
            arg0->segment.particle.unk2C = 0;
        }
        break;
    case 3:
        if (D_800E2CC4 > 0) {
            tex = arg0->modelData->texture;
            if (tex != NULL) {
                free_texture(tex);
            }
            D_800E2CC4--;
            arg0->segment.particle.unk2C = 0;
        }
        break;
    case 4:
        if (D_800E2CD0 > 0) {
            func_800B263C(arg0);
            tex = arg0->modelData->texture;
            if (tex != NULL) {
                free_texture(tex);
            }
            D_800E2CD0--;
            arg0->segment.particle.unk2C = 0;
        }
        break;
    }
}


void func_800B2260(Particle *arg0) {
    Particle *temp_v0;
    s32 i;

    if (arg0->data.flags & 0x400) {
        if (arg0->data.unkC_60 != NULL) {
            for (i = 0; i < arg0->data.unk6; i++) {
                temp_v0 = arg0->data.unkC_60[i];
                temp_v0->segment.particle.destroyTimer = 0;
                temp_v0->unk70 = 0;
            }
            free_from_memory_pool(arg0->data.unkC_60);
            arg0->data.unkC_60 = NULL;
        }
    }
}

/**
 * Call a function to update the current particle texture frame if applicable.
 * Applies movement, gets block ID and then shifts the opacity.
*/
void handle_particle_movement(Particle *particle, s32 updateRate) {
    LevelModelSegmentBoundingBox *boundingBox;
    Particle *tempParticle;

    gParticleUpdateRate = updateRate;
    tempParticle = NULL;
    if (particle->segment.particle.unk2C == 3) {
        func_800B26E0();
    } else {
        if (particle->segment.unk40 & 3) {
            if (gParticleUpdateRate > 0) {
                set_particle_texture_frame(particle);
            }
        }
        if (particle->segment.particle.unk2C == 4) {
            tempParticle = particle;
            particle->modelFrame = 1 - particle->modelFrame;
            particle->unk77 = 0;
        }
        if (tempParticle == NULL || (tempParticle && tempParticle->unk70)) {
            if (particle->segment.particle.movementType == PARTICLE_MOVEMENT_VELOCITIES) {
                move_particle_with_velocities(particle);
            } else if (particle->segment.particle.movementType == PARTICLE_MOVEMENT_VELOCITY_PARENT) {
                move_particle_velocity_parent(particle);
            } else if (particle->segment.particle.movementType == PARTICLE_MOVEMENT_BASIC_PARENT) {
                move_particle_basic_parent(particle);
            } else if (particle->segment.particle.movementType == PARTICLE_MOVEMENT_VELOCITY) {
                move_particle_with_velocity(particle);
            } else {
                move_particle_basic(particle);
            }
        }
        boundingBox = get_segment_bounding_box(particle->segment.particle.blockID);
        if (boundingBox != NULL) {
            if (particle->segment.trans.x_position < boundingBox->x1 || boundingBox->x2 < particle->segment.trans.x_position || 
                particle->segment.trans.y_position < boundingBox->y1 || boundingBox->y2 < particle->segment.trans.y_position || 
                particle->segment.trans.z_position < boundingBox->z1 || boundingBox->z2 < particle->segment.trans.z_position) {
                particle->segment.particle.blockID = get_level_segment_index_from_position(particle->segment.trans.x_position, particle->segment.trans.y_position, particle->segment.trans.z_position);
            }
        } else {
            particle->segment.particle.blockID = get_level_segment_index_from_position(particle->segment.trans.x_position, particle->segment.trans.y_position, particle->segment.trans.z_position);
        }
        particle->segment.particle.destroyTimer -= gParticleUpdateRate;
        if (particle->segment.particle.destroyTimer <= 0) {
            free_object((Object*) particle);
        } else {
            if (particle->opacityTimer == 0) {
                particle->opacity += gParticleUpdateRate * particle->opacityVel;
                if (particle->opacity < 0xFF) {
                    if (particle->segment.unk40 & 0x1000) {
                        particle->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                    } else {
                        particle->segment.trans.flags |=  OBJ_FLAGS_UNK_0080;
                    }
                }
            } else {
                particle->opacityTimer -= gParticleUpdateRate;
                if (particle->opacityTimer < 0) {
                    particle->opacity -= (particle->opacityTimer * particle->opacityVel);
                    particle->opacityTimer = 0;
                }
            }
        }
    }
}


void func_800B263C(Particle *arg0) {
    Particle *new_var;
    Particle *new_var2;
    Particle *temp_v0;
    s32 i;

    temp_v0 = arg0->unk70;
    if (temp_v0 != NULL) {
        new_var = temp_v0;
        if (temp_v0->data.unk6 != 0) {
            if (arg0 == temp_v0->data.unkC_60[arg0->unk74]) {
                temp_v0->data.unk6--;
                for (i = arg0->unk74; i < temp_v0->data.unk6; i++) {
                    new_var->data.unkC_60[i] = new_var->data.unkC_60[i + 1];
                    new_var2 = new_var->data.unkC_60[i];
                    new_var2->unk74 = i;
                }
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/particles/func_800B26E0.s")

void set_particle_texture_frame(Particle *particle) {
    s32 someFlag;
    s32 keepGoing;
    s32 i;
    s32 textureCount;
    s32 someFlag2;
    s32 someFlag3;
    s32 someFlag4;
    
    keepGoing = -1;

    i = 128; // This is needed to match.
    if (particle->segment.particle.unk2C == i) {
        textureCount = particle->unk44_1->textureCount * 256;
    } else {
        textureCount = particle->modelData->texture->numOfTextures;
    }

    someFlag4 = particle->segment.unk40 & 1;
    someFlag2 = particle->segment.unk40 & 2;
    someFlag3 = particle->segment.unk40 & 4;
    someFlag = particle->segment.unk40 & 8;
    for (i = 0; (i++ < gParticleUpdateRate) && keepGoing;) {
        if (!someFlag) {
            particle->segment.textureFrame += particle->segment.unk1A;
            if (particle->segment.textureFrame >= textureCount) {
                if (someFlag2) {
                    particle->segment.textureFrame = ((textureCount * 2) - particle->segment.textureFrame) - 1;
                    someFlag = TRUE;
                    particle->segment.unk40 |= 8;
                } else if (someFlag3) {
                    particle->segment.textureFrame -= textureCount;
                } else {
                    particle->segment.textureFrame = textureCount - 1;
                    keepGoing = FALSE;
                    particle->segment.unk40 &= ~3;
                }
            }
        } else {
            particle->segment.textureFrame -= particle->segment.unk1A;
            if (particle->segment.textureFrame < 0) {
                if (someFlag3) {
                    if (someFlag4) {
                        particle->segment.textureFrame = -particle->segment.textureFrame;
                        someFlag = FALSE;
                        particle->segment.unk40 &= ~8;
                    } else {
                        particle->segment.textureFrame += textureCount;
                    }
                } else {
                    particle->segment.textureFrame = 0;
                    keepGoing = FALSE;
                    particle->segment.unk40 &= ~3;
                }
            }
        }
    }
}

/**
 * Apply translation, rotation and scale based off the velocities of the particle.
 * Applies further translation based on the position of the parent.
*/
void move_particle_basic_parent(Particle *particle) {
    s32 i;
    ObjectSegment *parent;

    i = gParticleUpdateRate;
    while (i-- > 0) {
        particle->baseVelX += particle->segment.x_velocity;
        particle->baseVelY += particle->segment.y_velocity;
        particle->segment.y_velocity -= particle->gravity;
        particle->baseVelZ += particle->segment.z_velocity;
        particle->segment.trans.y_rotation += particle->angleVelY;
        particle->segment.trans.x_rotation += particle->angleVelX;
        particle->segment.trans.z_rotation += particle->angleVelZ;
        particle->segment.trans.scale += particle->segment.scaleVel;
    }
    particle->segment.trans.x_position = particle->baseVelX;
    particle->segment.trans.y_position = particle->baseVelY;
    particle->segment.trans.z_position = particle->baseVelZ;
    parent = particle->segment.unk3C;
    if (parent) {
        particle->segment.trans.x_position += parent->trans.x_position;
        particle->segment.trans.y_position += parent->trans.y_position;
        particle->segment.trans.z_position += parent->trans.z_position;
    }
}


/**
 * Apply translation, rotation and scale based off the velocities of the particle.
 * Velocity is set from forward velocity.
 * Applies further translation based on the position of the parent.
*/
void move_particle_velocity_parent(Particle *particle) {
    s32 i;
    ObjectSegment *parent;

    i = gParticleUpdateRate;
    while (i-- > 0) {
        particle->segment.trans.y_rotation += particle->angleVelY;
        particle->segment.trans.x_rotation += particle->angleVelX;
        particle->segment.trans.z_rotation += particle->angleVelZ;
        particle->segment.trans.scale += particle->segment.scaleVel;
    }
    particle->segment.trans.x_position = 0.0f;
    particle->segment.trans.y_position = -particle->forwardVel;
    particle->segment.trans.z_position = 0.0f;
    f32_vec3_apply_object_rotation(&particle->segment.trans, &particle->segment.trans.x_position);
    particle->segment.trans.x_position += particle->baseVelX;
    particle->segment.trans.y_position += particle->baseVelY;
    particle->segment.trans.z_position += particle->baseVelZ;
    parent = particle->segment.unk3C;
    if (parent) {
        particle->segment.trans.x_position += parent->trans.x_position;
        particle->segment.trans.y_position += parent->trans.y_position;
        particle->segment.trans.z_position += parent->trans.z_position;
    }
}

/**
 * Apply translation, rotation and scale based off the velocities of the particle.
 * Uses base velocity, then applies additional velocity based off the forward moving direction.
*/
void move_particle_with_velocities(Particle *particle) {
    s32 i;
    Vec3f vel;

    for (i = 0; gParticleUpdateRate > i++;) {
        particle->segment.trans.x_position += particle->segment.x_velocity;
        particle->segment.trans.y_position += particle->segment.y_velocity;
        particle->segment.trans.z_position += particle->segment.z_velocity;
        particle->segment.trans.scale += particle->segment.scaleVel;
        particle->segment.trans.y_rotation += particle->angleVelY;
        particle->segment.trans.x_rotation += particle->angleVelX;
        particle->segment.trans.z_rotation += particle->angleVelZ;
        vel.x = 0.0f;
        vel.y = -particle->forwardVel;
        vel.z = 0.0f;
        f32_vec3_apply_object_rotation(&particle->segment.trans, vel.f);
        particle->segment.x_velocity += vel.x;
        particle->segment.y_velocity += vel.y;
        particle->segment.y_velocity -= particle->gravity;
        particle->segment.z_velocity += vel.z;
    }
}

/**
 * Apply translation, rotation and scale based off the velocities of the particle.
*/
void move_particle_basic(Particle *particle) {
    s32 i;

    for (i = 0; gParticleUpdateRate > i++;) {
        particle->segment.trans.x_position += particle->segment.x_velocity;
        particle->segment.trans.y_position += particle->segment.y_velocity;
        particle->segment.y_velocity = particle->segment.y_velocity - particle->gravity;
        particle->segment.trans.z_position += particle->segment.z_velocity;
        particle->segment.trans.scale += particle->segment.scaleVel;
        particle->segment.trans.y_rotation += particle->angleVelY;
        particle->segment.trans.x_rotation += particle->angleVelX;
        particle->segment.trans.z_rotation += particle->angleVelZ;
    }
}

/**
 * Apply translation, rotation and scale based off the velocities of the particle.
 * Velocity is set from forward velocity.
*/
void move_particle_with_velocity(Particle *particle) {
    s32 i;

    for (i = 0; gParticleUpdateRate > i++;) {
        particle->segment.x_velocity = 0.0f;
        particle->segment.y_velocity = 0.0f;
        particle->segment.z_velocity = -particle->forwardVel;
        f32_vec3_apply_object_rotation3(&particle->segment.trans, &particle->segment.x_velocity);
        particle->segment.trans.x_position += particle->segment.x_velocity;
        particle->segment.trans.y_position += particle->segment.y_velocity - particle->gravity;
        particle->segment.trans.z_position += particle->segment.z_velocity;
        particle->segment.trans.scale += particle->segment.scaleVel;
        particle->segment.trans.y_rotation += particle->angleVelY;
        particle->segment.trans.x_rotation += particle->angleVelX;
        particle->segment.trans.z_rotation += particle->angleVelZ;
    }
}

/**
 * Iterate through every object and render it as particle if applicable.
*/
UNUSED void render_active_particles(Gfx **dList, MatrixS **arg1, Vertex **arg2) {
    UNUSED s32 pad;
    UNUSED s32 pad2;
    Object **objects;
    s32 iObj;
    s32 nObjs;

    objects = objGetObjList(&iObj, &nObjs);
    for (; iObj < nObjs; iObj++) {
        if (objects[iObj]->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) {
            if ((s32) objects[iObj]->segment.header & 0x8000) {
                render_particle((Particle *) objects[iObj], dList, arg1, arg2, 0);
            }
        }
    }
}

/**
 * Load a texture then render a sprite or a billboard.
*/
void render_particle(Particle *particle, Gfx **dList, MatrixS **mtx, Vertex **vtx, s32 flags) {
    s32 renderFlags;
    s32 alpha;
    s32 temp;
    ParticleModel *modelData;
    Vertex *tempvtx;

    renderFlags = (RENDER_FOG_ACTIVE | RENDER_Z_COMPARE);
    
    // Never true
    if (particle->segment.unk40 & flags && D_800E2CDC < 512) {
        return;
    }
    alpha = (particle->opacity >> 8) & 0xFF;
    if (alpha <= 0) {
        return;
    }
    if (particle->segment.object.unk2C != 4 && particle->segment.object.unk2C != 3) {
        gDPSetEnvColor((*dList)++, particle->colour.r, particle->colour.g, particle->colour.b, particle->colour.a);
        if (alpha != 255) {
            renderFlags = (RENDER_Z_UPDATE | RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE);
            gDPSetPrimColor((*dList)++, 0, 0, particle->brightness, particle->brightness, particle->brightness, alpha);
        } else {
            gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
        }
        if (particle->segment.object.unk2C == 0x80) {
            temp = particle->segment.textureFrame;
            particle->segment.textureFrame >>= 8;
            particle->segment.textureFrame = (particle->segment.textureFrame * 255) / (particle->unk44_1->textureCount);
            render_sprite_billboard(dList, mtx, vtx, (Object *) particle, (unk80068514_arg4 *) particle->modelData, renderFlags);
            particle->segment.textureFrame = temp;
        } else {
            modelData = particle->modelData;
            if (modelData->texture) {
                camera_push_model_mtx(dList, mtx, &particle->segment.trans, 1.0f, 0.0f);
                load_and_set_texture(dList, (TextureHeader *) modelData->texture, renderFlags, particle->segment.textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(modelData->vertices), modelData->vertexCount, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(modelData->triangles), modelData->triangleCount, TRIN_ENABLE_TEXTURE);
                func_80069A40(dList);
            }
        }
        if (alpha != 255 || particle->brightness != 255) {
            gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
        }
        if (particle->colour.a) {
            gDPSetEnvColor((*dList)++, 255, 255, 255, 0);
        }
    } else {
        renderFlags = (RENDER_VTX_ALPHA | RENDER_Z_UPDATE | RENDER_FOG_ACTIVE | RENDER_Z_COMPARE | RENDER_ANTI_ALIASING);
        gDPSetEnvColor((*dList)++, 255, 255, 255, 0);
        if (particle->segment.object.unk2C == 4) {
            if (particle->segment.camera.unk3A > 0) {
                gDPSetPrimColor((*dList)++, 0, 0, particle->brightness, particle->brightness, particle->brightness, 255);
                if (particle->unk77 == 0) {
                    func_800B3E64((Object *) particle);
                }
                modelData = particle->modelData;
                temp = particle->modelFrame;
                temp <<= 3;
                tempvtx = &modelData->vertices[temp];
                load_and_set_texture(dList, modelData->texture, renderFlags, particle->segment.textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(tempvtx), modelData->vertexCount, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(modelData->triangles), modelData->triangleCount, TRIN_ENABLE_TEXTURE);
                if (particle->brightness != 255) {
                    gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
                }
            }
        } else if (particle->segment.object.unk2C == 3) {
            gDPSetPrimColor((*dList)++, 0, 0, particle->brightness, particle->brightness, particle->brightness, alpha);
            if (particle->unk68b >= 2) {
                modelData = particle->modelData;
                load_and_set_texture(dList, modelData->texture, renderFlags, particle->segment.textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(modelData->vertices), modelData->vertexCount, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(modelData->triangles),  modelData->triangleCount, 1);
            } else if (particle->unk68b > 0) {
                modelData = particle->modelData;
                load_and_set_texture(dList, modelData->texture, renderFlags, particle->segment.textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(modelData->vertices), 4, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(&modelData->triangles[modelData->triangleCount]), 1, TRIN_ENABLE_TEXTURE);
            }
            if (alpha != 255 || particle->brightness != 255) {
                gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/particles/func_800B3E64.s")

/**
 * Return a specific particle asset table from the main table.
*/
UNUSED ParticleProperties *get_particle_asset_table(s32 idx) {
    if (idx < gParticlesAssetTableCount) {
        return gParticlesAssetTable[idx];
    }
    return gParticlesAssetTable[gParticlesAssetTableCount - 1];
}

/**
 * Return the next particle table after the index.
 * Make sure the index is in range by wrapping it.
*/
UNUSED ParticleProperties *get_next_particle_table(s32 *idx) {
    *idx = *idx + 1;
    while (*idx >= gParticlesAssetTableCount) {
        *idx = *idx - gParticlesAssetTableCount;
    }
    return gParticlesAssetTable[*idx];
}

/**
 * Return the previous particle table before the index.
 * Make sure the index is in range by wrapping it.
*/
UNUSED ParticleProperties *get_previous_particle_table(s32 *idx) {
    *idx = *idx - 1;
    while (*idx < 0) {
        *idx += gParticlesAssetTableCount;
    }
    return gParticlesAssetTable[*idx];
}

/**
 * Return the particle behaviour ID from the behaviour table.
*/
UNUSED ParticleBehavior *get_particle_behaviour(s32 idx) {
    if (idx < gParticleBehavioursAssetTableCount) {
        return gParticleBehavioursAssetTable[idx];
    }
    return gParticleBehavioursAssetTable[gParticleBehavioursAssetTableCount - 1];
}

UNUSED ParticleBehavior *func_800B45C4(s32 *idx) {
    *idx += 1;
    while (*idx >= gParticleBehavioursAssetTableCount) {
        *idx -= gParticleBehavioursAssetTableCount;
    }
    return gParticleBehavioursAssetTable[*idx];
}

UNUSED ParticleBehavior *func_800B461C(s32 *idx) {
    *idx -= 1;
    while (*idx < 0) {
        *idx += gParticleBehavioursAssetTableCount;
    }
    return gParticleBehavioursAssetTable[*idx];
}

void func_800B4668(Object *obj, s32 idx, s32 arg2, s32 arg3) {
    s32 temp_v0;

    arg3 <<= 8; 
    temp_v0 = (obj->unk6C[idx].unkA & 0xFFFF) + arg2;
    if (arg3 < temp_v0) {
        obj->unk6C[idx].unkA = arg3;
    } else {
        obj->unk6C[idx].unkA = temp_v0;
    }
    obj->unk6C[idx].unk4 |= 0x100;
}

void func_800B46BC(Object *obj, s32 idx, s32 arg2, s32 arg3) {
    s32 temp_v0;

    arg3 <<= 8; 
    temp_v0 = (obj->unk6C[idx].unkA & 0xFFFF) - arg2;
    if (temp_v0 < arg3) {
        obj->unk6C[idx].unkA = arg3;
    } else {
        obj->unk6C[idx].unkA = temp_v0;
    }
    obj->unk6C[idx].unk4 |= 0x100;
}
