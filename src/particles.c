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
s32 gNumTriangleParticles = 0;
s32 D_800E2CA4 = 0;
Particle *gTriangleParticleBuffer = NULL;
s32 gNumRectangleParticles = 0;
s32 D_800E2CB0 = 0;
Particle *gRectangleParticleBuffer = NULL;
s32 gNumSpriteParticles = 0;
s32 D_800E2CBC = 0;
Particle *gSpriteParticleBuffer = NULL;
s32 gNumLineParticles = 0;
s32 D_800E2CC8 = 0;
Particle *gLineParticleBuffer = NULL;
s32 gNumPointParticles = 0;
s32 D_800E2CD4 = 0;
PointParticle *gPointParticleBuffer = NULL;
UNUSED s32 D_800E2CDC = 0; // Only ever and checked for being less than 512.
Vertex *gParticleVertexBuffer = NULL;
Triangle *gParticleTriangleBuffer = NULL;
s32 gParticlesAssetTableCount = 0;
s32 *gParticlesAssets = NULL;

ParticleProperties **gParticlesAssetTable = NULL;
s32 gParticleBehavioursAssetTableCount = 0;
s32 *gParticleBehavioursAssets = NULL;
ParticleBehavior **gParticleBehavioursAssetTable = NULL;
ColourRGBA D_800E2D00[2] = { { { { 0 } } }, { { { 0 } } } };

Triangle D_800E2D08[5] = {
    { { { BACKFACE_DRAW, 0, 1, 2 } }, { { { 256, 0 } } }, { { { 0, 480 } } }, { { { 256, 480 } } } },
    { { { BACKFACE_DRAW, 0, 2, 3 } }, { { { 256, 0 } } }, { { { 256, 480 } } }, { { { 480, 480 } } } },
    { { { BACKFACE_DRAW, 1, 2, 4 } }, { { { 0, 0 } } }, { { { 256, 0 } } }, { { { 0, 480 } } } },
    { { { BACKFACE_DRAW, 2, 3, 5 } }, { { { 256, 0 } } }, { { { 480, 0 } } }, { { { 480, 480 } } } },
    { { { BACKFACE_DRAW, 0, 1, 3 } }, { { { 256, 0 } } }, { { { 0, 480 } } }, { { { 480, 480 } } } }
};

Vec3s D_800E2D58[5] = {
    { { { 0x0000, 0x01FF, 0x01FF } } }, { { { 0x0000, 0x01FF, 0x01FF } } }, { { { 0x0000, 0x0000, 0x01FF } } },
    { { { 0x0000, 0x0000, 0x01FF } } }, { { { 0x0000, 0x01FF, 0x01FF } } },
};

Triangle D_800E2D78[8] = {
    { { { BACKFACE_CULL, 0, 1, 5 } }, { { { 0, 0 } } }, { { { 128, 0 } } }, { { { 128, 511 } } } },
    { { { BACKFACE_CULL, 0, 5, 4 } }, { { { 0, 0 } } }, { { { 128, 511 } } }, { { { 0, 511 } } } },
    { { { BACKFACE_CULL, 1, 2, 6 } }, { { { 128, 0 } } }, { { { 256, 0 } } }, { { { 256, 511 } } } },
    { { { BACKFACE_CULL, 1, 6, 5 } }, { { { 128, 0 } } }, { { { 256, 511 } } }, { { { 128, 511 } } } },
    { { { BACKFACE_CULL, 2, 3, 7 } }, { { { 256, 0 } } }, { { { 384, 0 } } }, { { { 384, 511 } } } },
    { { { BACKFACE_CULL, 2, 7, 6 } }, { { { 256, 0 } } }, { { { 384, 511 } } }, { { { 256, 511 } } } },
    { { { BACKFACE_CULL, 3, 0, 4 } }, { { { 384, 0 } } }, { { { 512, 0 } } }, { { { 512, 511 } } } },
    { { { BACKFACE_CULL, 3, 4, 7 } }, { { { 384, 0 } } }, { { { 512, 511 } } }, { { { 384, 511 } } } },
};

Vec3s D_800E2DF8[8] = {
    { { { 0x0000, 0x0000, 0x01FF } } }, { { { 0x0000, 0x01FF, 0x01FF } } }, { { { 0x0000, 0x0000, 0x01FF } } },
    { { { 0x0000, 0x01FF, 0x01FF } } }, { { { 0x0000, 0x0000, 0x01FF } } }, { { { 0x0000, 0x01FF, 0x01FF } } },
    { { { 0x0000, 0x0000, 0x01FF } } }, { { { 0x0000, 0x01FF, 0x01FF } } },
};

s16 D_800E2E28 = 0;

f32 gParticleGravityTable[8] = { 0.0f, 0.1, 0.2f, 0.3f, 0.45f, 0.525f, 0.6f, 0.8f };

s32 gMaxTriangleParticles = 0;
s32 gMaxRectangleParticles = 0;
s32 gMaxSpriteParticles = 0;
s32 gMaxLineParticles = 0;
s32 gMaxPointParticles = 0;
Sprite **D_800E2E60 = NULL;
s32 D_800E2E64 = 0;

XYStruct gParticleCoordListTri[3] = {
    { 0, 8 },
    { 7, -4 },
    { -7, -4 },
};

XYStruct gParticleCoordListQuad[4] = {
    { -6, 6 },
    { 6, 6 },
    { 6, -6 },
    { -6, -6 },
};

ColourRGBA D_800E2E84[16] = {
    { { { 0, 0, 0, 0 } } }, { { { 192, 8, 64, 255 } } },   { { { 255, 96, 8, 255 } } }, { { { 64, 64, 64, 255 } } },
    { { { 0, 0, 0, 0 } } }, { { { 0, 0, 0, 0 } } },        { { { 0, 0, 0, 0 } } },      { { { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 } } }, { { { 0, 0, 0, 0 } } },        { { { 0, 0, 0, 0 } } },      { { { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 } } }, { { { 16, 112, 255, 255 } } }, { { { 0, 0, 0, 0 } } },      { { { 0, 0, 0, 0 } } },
};

ColourRGBA D_800E2EC4[10] = {
    { { { 64, 64, 64, 255 } } },  { { { 64, 64, 64, 255 } } },  { { { 0, 45, 0, 255 } } },
    { { { 0, 45, 0, 255 } } },    { { { 64, 60, 10, 255 } } },  { { { 64, 60, 10, 255 } } },
    { { { 64, 64, 255, 255 } } }, { { { 64, 64, 255, 255 } } }, { { { 64, 64, 64, 255 } } },
    { { { 64, 64, 64, 255 } } },
};

s32 gParticleOpacity = 256;

/*******************************/

/************ .bss ************/

s32 gParticleUpdateRate;
s32 D_80127C84;
s16 D_80127C88[12];
// printf.c
// thread0_epc
/******************************/

void func_800AE270(void) {
    free_particle_buffers();
    free_particle_vertices_triangles();
    func_800AE2D8();
}

void func_800AE2A0(void) {
    free_particle_buffers();
    free_particle_vertices_triangles();
    free_particle_assets();
    func_800AE2D8();
}

void func_800AE2D8(void) {
    s32 i;

    if (D_800E2E60 != NULL) {
        for (i = 0; i < D_800E2E64; i++) {
            free_sprite(D_800E2E60[i]);
        }
        mempool_free(D_800E2E60);
        D_800E2E60 = 0;
    }
}

void free_particle_buffers(void) {
    if (gTriangleParticleBuffer != NULL) {
        mempool_free(gTriangleParticleBuffer);
        gTriangleParticleBuffer = NULL;
    }
    if (gRectangleParticleBuffer != NULL) {
        mempool_free(gRectangleParticleBuffer);
        gRectangleParticleBuffer = NULL;
    }
    if (gSpriteParticleBuffer != NULL) {
        mempool_free(gSpriteParticleBuffer);
        gSpriteParticleBuffer = NULL;
    }
    if (gLineParticleBuffer != NULL) {
        mempool_free(gLineParticleBuffer);
        gLineParticleBuffer = NULL;
    }
    if (gPointParticleBuffer != NULL) {
        mempool_free(gPointParticleBuffer);
        gPointParticleBuffer = NULL;
    }
}

void free_particle_vertices_triangles(void) {
    if (gParticleVertexBuffer != NULL) {
        mempool_free(gParticleVertexBuffer);
        gParticleVertexBuffer = NULL;
    }
    if (gParticleTriangleBuffer != NULL) {
        mempool_free(gParticleTriangleBuffer);
        gParticleTriangleBuffer = NULL;
    }
}

void free_particle_assets(void) {
    if (gParticlesAssets != NULL) {
        mempool_free(gParticlesAssets);
        gParticlesAssets = NULL;
    }
    if (gParticlesAssetTable != NULL) {
        mempool_free(gParticlesAssetTable);
        gParticlesAssetTable = NULL;
    }
    if (gParticleBehavioursAssets != NULL) {
        mempool_free(gParticleBehavioursAssets);
        gParticleBehavioursAssets = NULL;
    }
    if (gParticleBehavioursAssetTable != NULL) {
        mempool_free(gParticleBehavioursAssetTable);
        gParticleBehavioursAssetTable = NULL;
    }
}

void init_particle_assets(void) {
    s32 i;

    free_particle_assets();
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
        gParticleBehavioursAssetTable[i] =
            (ParticleBehavior *) (((u8 *) gParticleBehavioursAssets) + ((s32) gParticleBehavioursAssetTable[i]));
        if (((u32) gParticleBehavioursAssetTable[i]->unk9C) != 0xFFFFFFFF) {
            gParticleBehavioursAssetTable[i]->unk9C =
                (s32 *) get_misc_asset((s32) gParticleBehavioursAssetTable[i]->unk9C);
        }
    }
}

#ifdef NON_EQUIVALENT
void init_particle_buffers(s32 maxTriangleParticles, s32 maxRectangleParticles, s32 maxSpriteParticles,
                           s32 maxLineParticles, s32 maxPointParticles, s32 unused_arg) {
    unsigned int new_var2;
    Vertex *sp54;
    Triangle *sp50;
    s32 i;
    s16 *asset2F;
    ParticleModel *modelPtr;
    s32 zero = 0;

    D_800E2D00->word = 0;

    if (maxTriangleParticles < 0) {
        maxTriangleParticles = 0x10;
    }
    if (maxRectangleParticles < 0) {
        maxRectangleParticles = 0x10;
    }
    if (maxSpriteParticles < 0) {
        maxSpriteParticles = 0xD0;
    }
    if (maxLineParticles < 0) {
        maxLineParticles = 0xA0;
    }
    if (maxPointParticles < 0) {
        maxPointParticles = 0x40;
    }
    gMaxTriangleParticles = maxTriangleParticles;
    D_800E2CA4 = 0;
    gMaxRectangleParticles = maxRectangleParticles;
    D_800E2CB0 = 0;
    gMaxSpriteParticles = maxSpriteParticles;
    D_800E2CBC = 0;
    gMaxLineParticles = maxLineParticles;
    D_800E2CC8 = 0;
    gMaxPointParticles = maxPointParticles;
    D_800E2CD4 = 0;

    free_particle_vertices_triangles();
    gParticleVertexBuffer = mempool_alloc_safe(
        (3 * maxTriangleParticles + 4 * maxRectangleParticles + 6 * maxLineParticles + 16 * maxPointParticles) *
            sizeof(Vertex),
        COLOUR_TAG_SEMITRANS_GREY);
    gParticleTriangleBuffer = mempool_alloc_safe((maxTriangleParticles + 2 * maxRectangleParticles) * sizeof(Triangle),
                                                 COLOUR_TAG_SEMITRANS_GREY);
    D_800E2CDC = 0;

    free_particle_buffers();
    if (gMaxTriangleParticles > 0) {
        gNumTriangleParticles = 0;
        gTriangleParticleBuffer = mempool_alloc_safe(maxTriangleParticles * (sizeof(Particle) + sizeof(ParticleModel)),
                                                     COLOUR_TAG_SEMITRANS_GREY);
    }
    if (gMaxRectangleParticles > 0) {
        gNumRectangleParticles = 0;
        gRectangleParticleBuffer = mempool_alloc_safe(
            maxRectangleParticles * (sizeof(Particle) + sizeof(ParticleModel)), COLOUR_TAG_SEMITRANS_GREY);
    }
    if (gMaxSpriteParticles > 0) {
        gNumSpriteParticles = 0;
        gSpriteParticleBuffer = mempool_alloc_safe(maxSpriteParticles * sizeof(Particle), COLOUR_TAG_SEMITRANS_GREY);
    }
    if (gMaxLineParticles > 0) {
        gNumLineParticles = 0;
        gLineParticleBuffer = mempool_alloc_safe(maxLineParticles * (sizeof(Particle) + sizeof(ParticleModel)),
                                                 COLOUR_TAG_SEMITRANS_GREY);
    }
    if (gMaxPointParticles > 0) {
        gNumPointParticles = 0;
        gPointParticleBuffer = mempool_alloc_safe(maxPointParticles * (sizeof(PointParticle) + sizeof(ParticleModel)),
                                                  COLOUR_TAG_SEMITRANS_GREY);
    }

    sp54 = &gParticleVertexBuffer[zero];
    sp50 = &gParticleTriangleBuffer[zero];

    modelPtr = (ParticleModel*)&gTriangleParticleBuffer[gMaxTriangleParticles];
    for (i = 0; i < gMaxTriangleParticles; i++) {
        gTriangleParticleBuffer[i].modelData = &modelPtr[i];
        generate_particle_shape_triangle(gTriangleParticleBuffer[i].modelData, &sp54, &sp50);
    }

    modelPtr = (ParticleModel*)&gRectangleParticleBuffer[gMaxRectangleParticles];
    for (i = 0; i < gMaxRectangleParticles; i++) {
        gRectangleParticleBuffer[i].modelData = &modelPtr[i];
        generate_particle_shape_quad(gRectangleParticleBuffer[i].modelData, &sp54, &sp50);
    }

    modelPtr = (ParticleModel*)&gLineParticleBuffer[gMaxLineParticles];
    for (i = 0; i < gMaxLineParticles; i++) {
        gLineParticleBuffer[i].modelData = &modelPtr[i];
        sp50 = D_800E2D08;
        generate_particle_shape_line(gLineParticleBuffer[i].modelData, &sp54, &sp50);
    }

    modelPtr = (ParticleModel*)&gPointParticleBuffer[gMaxPointParticles];
    for (i = 0; i < gMaxPointParticles; i++) {
        gPointParticleBuffer[i].base.modelData = &modelPtr[i];
        sp50 = D_800E2D78;
        generate_particle_shape_point(gPointParticleBuffer[i].base.modelData, &sp54, &sp50);
    }

    for (i = 0; i < gMaxTriangleParticles; i++) {
        gTriangleParticleBuffer[i].segment.particle.kind = PARTICLE_KIND_NONE;
    }

    for (i = 0; i < gMaxRectangleParticles; i++) {
        gRectangleParticleBuffer[i].segment.particle.kind = PARTICLE_KIND_NONE;
    }

    for (i = 0; i < gMaxSpriteParticles; i++) {
        gSpriteParticleBuffer[i].segment.particle.kind = PARTICLE_KIND_NONE;
    }

    for (i = 0; i < gMaxLineParticles; i++) {
        gLineParticleBuffer[i].segment.particle.kind = PARTICLE_KIND_NONE;
    }

    for (i = 0; i < gMaxPointParticles; i++) {
        gPointParticleBuffer[i].base.segment.particle.kind = PARTICLE_KIND_NONE;
    }

    if (D_800E2E60 == NULL) {
        asset2F = (s16*)load_asset_section_from_rom(ASSET_BINARY_47);
        D_800E2E64 = 0;
        while (asset2F[D_800E2E64] != -1) {
            D_800E2E64++;
        }

        D_800E2E60 = mempool_alloc_safe(D_800E2E64 * 4, COLOUR_TAG_BLUE);
        for (i = 0; i < D_800E2E64; i++) {
            D_800E2E60[i] = (Sprite *) func_8007C12C(asset2F[i] & 0x3FFF, 1);
        }

        mempool_free(asset2F);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/particles/init_particle_buffers.s")
#endif

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
    tempTri->flags = RENDER_CLAMP_X;
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
    tempTri[0].flags = RENDER_CLAMP_X;
    tempTri[0].vi0 = 3;
    tempTri[0].uv0.u = 0;
    tempTri[0].vi1 = 1;
    tempTri[0].uv1.v = 0;
    tempTri[0].vi2 = 0;
    tempTri[0].uv2.u = 0;
    tempTri[0].uv2.v = 0;
    tempTri[1].flags = RENDER_CLAMP_X;
    tempTri[1].vi0 = 3;
    tempTri[1].uv0.u = 0;
    tempTri[1].vi1 = 2;
    tempTri[1].vi2 = 1;
    tempTri[1].uv2.v = 0;
    tempTri += 2;
    *triangles = tempTri;
}

void generate_particle_shape_line(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
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

void generate_particle_shape_point(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
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
    ParticleModel *model;
    Triangle *tri;
    s16 texV, texU;

    model = particle->modelData;
    tri = model->triangles;
    texU = (model->texture->width - 1) << 5;
    texV = (model->texture->height - 1) << 5;

    tri->uv0.u = texU >> 1;
    tri->uv0.v = 0;
    tri->uv1.u = 0;
    tri->uv1.v = texV;
    tri->uv2.u = texU;
    tri->uv2.v = texV;
}

void func_800AF0F0(Particle *particle) {
    ParticleModel *model;
    Triangle *tri;
    s16 texV, texU;

    model = particle->modelData;
    tri = model->triangles;
    texU = (model->texture->width - 1) << 5;
    texV = (model->texture->height - 1) << 5;

    tri[0].uv0.v = texV;
    tri[0].uv1.u = texU;
    tri[1].uv0.v = texU;
    tri[1].uv1.u = texU;
    tri[1].uv1.v = texV;
    tri[1].uv2.u = texU;
}

void func_800AF134(ParticleEmitter *emitter, s32 behaviourID, s32 propertyID, s16 velX, s16 velY, s16 velZ) {
    ParticleBehavior *behaviour;
    if (propertyID >= gParticlesAssetTableCount) {
        propertyID = 0;
    }
    if (behaviourID >= gParticleBehavioursAssetTableCount) {
        behaviourID = 0;
    }
    behaviour = gParticleBehavioursAssetTable[behaviourID];
    if (emitter->propertyID != propertyID || behaviour != emitter->behaviour) {
        func_800B2260(emitter);
        func_800AF29C(emitter, behaviourID, propertyID, velX, velY, velZ);
    }
}

void partInitTrigger(ParticleEmitter *emitter, s32 behaviourID, s32 propertyID) {
    ParticleBehavior *behaviour;

    if (behaviourID < gParticleBehavioursAssetTableCount) {
        behaviour = gParticleBehavioursAssetTable[behaviourID];
        func_800AF29C(emitter, behaviourID, propertyID, behaviour->velX, behaviour->velY, behaviour->velZ);
    }
}

void func_800AF29C(ParticleEmitter *emitter, s32 behaviourID, s32 propertyID, s16 velX, s16 velY, s16 velZ) {
    ParticleBehavior *behaviour;
    s32 flags;

    behaviour = gParticleBehavioursAssetTable[behaviourID];
    emitter->propertyID = propertyID;
    emitter->behaviour = behaviour;
    emitter->baseVelX = velX;
    emitter->baseVelY = velY;
    emitter->baseVelZ = velZ;
    emitter->unk1E = 0;

    flags = behaviour->emitterFlags;

    if (flags & PARTICLE_BEHAVIOR_FLAG_4000) {
        emitter->emmmflags = PARTICLE_BEHAVIOR_FLAG_4000;
        emitter->unk6 = 0;
        emitter->pos.x = 0.0f;
        emitter->pos.y = 0.0f;
        emitter->pos.z = 0.0f;
    } else if (flags & PARTICLE_BEHAVIOR_FLAG_400) {
        emitter->unk6 = 0;
        emitter->emmmflags = PARTICLE_BEHAVIOR_FLAG_400;
        if (gParticlesAssetTable[propertyID]->lifeTime <= 255) {
            emitter->lifeTime = gParticlesAssetTable[propertyID]->lifeTime;
        } else {
            emitter->lifeTime = 255;
        }
        emitter->unkC_400.unkC =
            (s32 *) mempool_alloc_safe(emitter->lifeTime * sizeof(uintptr_t), COLOUR_TAG_SEMITRANS_GREY);
        emitter->unkC_400.unk10 = behaviour->unk14;
        emitter->unkC_400.unk12 = behaviour->unk16;
        emitter->unkC_400.unk14 = behaviour->unk22;
        emitter->unkC_400.unk16 = behaviour->unk24;
    } else {
        emitter->emmmflags = PARTICLE_BEHAVIOR_FLAGS_NONE;
        emitter->angle.rotation.y_rotation = behaviour->unk14;
        emitter->angle.rotation.x_rotation = behaviour->unk16;
        emitter->angle.rotation.z_rotation = behaviour->unk18;
        emitter->angle.direction.y_rotation = behaviour->unk22;
        emitter->angle.direction.x_rotation = behaviour->unk24;
        emitter->angle.direction.z_rotation = behaviour->unk26;
    }
}

#ifdef NON_EQUIVALENT
void func_800AF404(s32 updateRate) {
    s32 i;

    D_800E2E28 = (D_800E2E28 + (updateRate << 6)) & 0x1FF;

    for (i = 0; i < ARRAY_COUNT(D_800E2D08); i++) {
        D_800E2D08[i].uv2.v = D_800E2D58[i].s[0] + D_800E2E28;
        D_800E2D08[i].uv1.v = D_800E2D58[i].s[1] + D_800E2E28;
        D_800E2D08[i].uv0.v = D_800E2D58[i].s[2] + D_800E2E28;
    }

    for (i = 0; i < ARRAY_COUNT(D_800E2D78); i++) {
        D_800E2D78[i].uv0.v = D_800E2DF8[i].s[0] + D_800E2E28;
        D_800E2D78[i].uv1.v = D_800E2DF8[i].s[1] + D_800E2E28;
        D_800E2D78[i].uv2.v = D_800E2DF8[i].s[2] + D_800E2E28;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/particles/func_800AF404.s")
#endif

void func_800AF52C(Object *obj, s32 emitterIndex) {
    s32 i;
    ParticleEmitter *emitter;
    ParticleBehavior *behaviour;
    Particle *temp;

    emitter = &obj->particleEmitter[emitterIndex];
    behaviour = emitter->behaviour;
    emitter->opacity = 0;

    if (emitter->emmmflags & PARTICLE_BEHAVIOR_FLAG_4000) {
        emitter->pos.x = obj->segment.trans.x_position;
        emitter->pos.y = obj->segment.trans.y_position;
        emitter->pos.z = obj->segment.trans.z_position;
    } else if (emitter->emmmflags & PARTICLE_BEHAVIOR_FLAG_400) {
        emitter->opacity = gParticlesAssetTable[emitter->propertyID]->colour.a << 8;

        if (emitter->unk6 > 0) { // Useless if statement, since the loop already does this.
            for (i = 0; i < emitter->unk6; i++) {
                temp = emitter->unkC_60[i];
                temp->segment.particle.destroyTimer = 0;
            }
        }
        if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_1) {
            emitter->angle.rotation.z_rotation = behaviour->unk14;
            emitter->angle.direction.y_rotation = behaviour->unk16;
        }
        if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_4) {
            emitter->angle.direction.x_rotation = behaviour->unk22;
            emitter->angle.direction.z_rotation = behaviour->unk24;
        }
    } else {
        if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_1) {
            emitter->unk6 = 0;
            emitter->angle.rotation.y_rotation = behaviour->unk14;
            emitter->angle.rotation.x_rotation = behaviour->unk16;
            emitter->angle.rotation.z_rotation = behaviour->unk18;
        }
        if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_4) {
            emitter->lifeTime = 0;
            emitter->angle.direction.y_rotation = behaviour->unk22;
            emitter->angle.direction.x_rotation = behaviour->unk24;
            emitter->angle.direction.z_rotation = behaviour->unk26;
        }
    }
    emitter->emmmflags &= ~PARTICLE_BEHAVIOR_FLAG_200;
    emitter->emmmflags |= PARTICLE_BEHAVIOR_FLAG_8000 | PARTICLE_BEHAVIOR_FLAG_2000;
    obj->segment.unk1A++;
}

void func_800AF6E4(Object *obj, s32 emitterIndex) {
    ParticleEmitter *emitter;

    emitter = &obj->particleEmitter[emitterIndex];

    emitter->emmmflags &= ~PARTICLE_BEHAVIOR_FLAG_8000;
    obj->segment.unk1A--;
}

void func_800AF714(Object *racerObj, s32 updateRate) {
    Object_Racer *racer;
    ParticleProperties *temp_a3;
    s32 var_v0;
    s32 temp_v1;
    s32 i;
    ParticleEmitter *new_var;
    ParticleEmitter *new_var2;
    s32 var_t1;
    s32 someBool;
    s8 vehicleId;
    u32 var_s7;
    u8 *alphaPtr;

    racer = &racerObj->unk64->racer;
    var_s7 = racerObj->particleEmittersEnabled;
    vehicleId = racer->vehicleID;
    i = 0;
    object_do_player_tumble(racerObj);
    for (; i < racerObj->segment.header->particleCount; i++) {
        if (var_s7 & OBJ_EMIT_1) {
            someBool = TRUE;
            switch (vehicleId) {
                case VEHICLE_CAR:
                    if (i >= 0 && i < 10) {
                        var_v0 = racer->unk16E;
                        if (var_v0 < 0) {
                            var_v0 = -var_v0;
                        }
                        var_v0 -= 24;
                        if (var_v0 > 0) {
                            temp_a3 = gParticlesAssetTable[racerObj->particleEmitter[i].propertyID];
                            alphaPtr = &D_800E2EC4[i].a;
                            var_t1 = 4;
                            if (var_v0 > 32) {
                                var_v0 = 32;
                            }
                            var_t1 = var_v0 << var_t1;
                            temp_v1 = var_t1 - ((var_v0 * var_v0) >> 2);
                            D_800E2D00[0].word =
                                ((((D_800E2EC4[i].r - temp_a3->colour.r) * temp_v1) >> 8) + temp_a3->colour.r) << 24;
                            D_800E2D00[0].word |=
                                (temp_a3->colour.g + ((((D_800E2EC4[i].g - temp_a3->colour.g) * temp_v1)) >> 8)) << 16;
                            D_800E2D00[0].word |=
                                (temp_a3->colour.b + ((((D_800E2EC4[i].b - temp_a3->colour.b) * temp_v1)) >> 8)) << 8;
                            if (var_v0 > 16) {
                                var_t1 = 256;
                            }
                            var_v0 = temp_a3->colour.a;
                            D_800E2D00[0].word |= var_v0 + (((*alphaPtr - var_v0) * var_t1) >> 8);
                        }
                    } else {
                        switch (i) {
                            case 10:
                                if (racer->wheel_surfaces[2] == 0xFF) {
                                    someBool = FALSE;
                                }
                                D_800E2D00[0].word = D_800E2E84[racer->wheel_surfaces[2] & 0xF].word;
                                break;

                            case 11:
                                if (racer->wheel_surfaces[3] == 0xFF) {
                                    someBool = FALSE;
                                }
                                D_800E2D00[0].word = D_800E2E84[racer->wheel_surfaces[3] & 0xF].word;
                                break;

                            case 12:
                                if (racer->wheel_surfaces[0] == 0xFF) {
                                    someBool = FALSE;
                                }
                                D_800E2D00[0].word = D_800E2E84[racer->wheel_surfaces[0] & 0xF].word;
                                break;

                            case 13:
                                if (racer->wheel_surfaces[1] == 0xFF) {
                                    someBool = FALSE;
                                }
                                D_800E2D00[0].word = D_800E2E84[racer->wheel_surfaces[1] & 0xF].word;
                                break;
                        }
                    }
                    break;
                case VEHICLE_PLANE:
                    if (i == 0) {
                        D_800E2D00[0].word = D_800E2E84[racer->wheel_surfaces[0] & 0xF].word;
                    } else if (i == 1) {
                        D_800E2D00[0].word = D_800E2E84[racer->wheel_surfaces[1] & 0xF].word;
                    }
                    break;
                case VEHICLE_HOVERCRAFT:
                    if (i == 2 || i == 3) {
                        var_v0 = D_80127C88[racer->racerIndex & 7];
                        var_v0 += (updateRate * 4);
                        if (var_v0 > 256) {
                            var_v0 = 256;
                        }
                        D_80127C88[racer->racerIndex & 7] = var_v0;
                        gParticleOpacity = var_v0;
                    }
                    break;
            }

            if (someBool) {
                if (!(racerObj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_8000)) {
                    func_800AF52C(racerObj, i);
                }
                if (racerObj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_4000) {
                    func_800AFE5C(racerObj, &racerObj->particleEmitter[i]);
                } else if (racerObj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_400) {
                    func_800AFE5C(racerObj, &racerObj->particleEmitter[i]);
                } else {
                    racerObj->particleEmitter[i].opacity += updateRate;
                    if (racerObj->particleEmitter[i].opacity >= racerObj->particleEmitter[i].behaviour->unk40) {
                        func_800AFE5C(racerObj, &racerObj->particleEmitter[i]);
                    }
                }
            }
        } else if (racerObj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_8000) {
            if (racerObj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_4000) {
                new_var2 = &racerObj->particleEmitter[i];
                new_var2->unk6 = 0;
                func_800AF6E4(racerObj, i);
            } else {
                if (racerObj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_400) {
                    new_var = &racerObj->particleEmitter[i];
                    racerObj->particleEmitter[i].emmmflags |= PARTICLE_BEHAVIOR_FLAG_200;
                    if (new_var->unk6 == 0) {
                        func_800AF6E4(racerObj, i);
                    }
                } else {
                    func_800AF6E4(racerObj, i);
                }
            }
            if (i == 2 || i == 3) {
                D_80127C88[racer->racerIndex & 7] = 0;
            }
        }
        D_800E2D00[0].word = 0;
        var_s7 >>= 1;
        gParticleOpacity = 256;
    }

    object_undo_player_tumble(racerObj);
}

void obj_spawn_particle(Object *obj, s32 updateRate) {
    s32 var_s0;
    s32 i;
    u32 bits;

    bits = obj->particleEmittersEnabled;
    for (i = 0; i < obj->segment.header->particleCount; i++) {
        if (bits & 1) {
            if (!(obj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_8000)) {
                func_800AF52C(obj, i);
            }
            if (obj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_4000) {
                func_800AFE5C(obj, &obj->particleEmitter[i]);
            } else if ((obj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_400)) {
                func_800AFE5C(obj, &obj->particleEmitter[i]);
            } else {
                obj->particleEmitter[i].opacity += updateRate;
                if (obj->particleEmitter[i].opacity >= obj->particleEmitter[i].behaviour->unk40) {
                    func_800AFE5C(obj, &obj->particleEmitter[i]);
                }
            }
        } else {
            if (obj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_8000) {
                if (obj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_4000) {
                    ParticleEmitter *temp_s1 = &obj->particleEmitter[i];
                    var_s0 = temp_s1->unk6 - 0x40;
                    if (var_s0 < 0) {
                        var_s0 = 0;
                    }
                    temp_s1->unk6 = var_s0;
                    func_800AFE5C(obj, temp_s1);
                    temp_s1->unk6 = var_s0;
                    if (var_s0 == 0) {
                        func_800AF6E4(obj, i);
                    }
                } else if ((obj->particleEmitter[i].emmmflags & PARTICLE_BEHAVIOR_FLAG_400)) {
                    ParticleEmitter *temp_s1_2 = &obj->particleEmitter[i];
                    obj->particleEmitter[i].emmmflags |= PARTICLE_BEHAVIOR_FLAG_200;
                    if (temp_s1_2->unk6 == 0) {
                        func_800AF6E4(obj, i);
                    }
                } else {
                    func_800AF6E4(obj, i);
                }
            }
        }
        bits >>= 1;
    }
}

void func_800AFE5C(Object *obj, ParticleEmitter *emitter) {
    PointParticle *temp_s0;
    Particle *tempObj;
    Particle *tempObj2;
    s32 i;
    ParticleBehavior *behavior;

    behavior = emitter->behaviour;
    if (emitter->emmmflags & PARTICLE_BEHAVIOR_FLAG_4000) {
        tempObj = init_line_particle(obj, emitter);
        if (tempObj != NULL) {
            add_particle_to_entity_list((Object *) tempObj);
        }
        emitter->emmmflags &= ~PARTICLE_BEHAVIOR_FLAG_2000;
        if (emitter->unk6 + 64 > 255) {
            emitter->unk6 = 255;
        } else {
            emitter->unk6 += 64;
        }
    } else if (emitter->emmmflags & PARTICLE_BEHAVIOR_FLAG_400) {
        if (emitter->unk6 < emitter->lifeTime) {
            temp_s0 = init_point_particle(obj, emitter);
            emitter->emmmflags &= ~PARTICLE_BEHAVIOR_FLAG_2000;
            if (temp_s0 != NULL) {
                add_particle_to_entity_list((Object *) temp_s0);
                temp_s0->unk74 = emitter->unk6;
                temp_s0->base.segment.unk40 |= PARTICLE_F40_2000;
                emitter->unkC_60[emitter->unk6] = temp_s0;
                emitter->unk6++;
            }
        }
    } else {
        while (emitter->opacity >= behavior->unk40) {
            emitter->opacity -= behavior->unk40;
            for (i = 0; i < behavior->unk42; i++) {
                tempObj2 = init_general_particle(obj, emitter);
                if (tempObj2 != NULL) {
                    add_particle_to_entity_list((Object *) tempObj2);
                    handle_particle_movement(tempObj2, emitter->opacity);
                }
                emitter->emmmflags &= ~PARTICLE_BEHAVIOR_FLAG_2000;
            }
        }
    }
}

void setup_particle_velocity(Particle *particle, Object *obj, ParticleEmitter *emitter, ParticleBehavior *behavior) {
    s32 randomizationFlags;
    Vec3f velocityPos;
    Vec3s angle;

    if (behavior->emitterFlags & (PARTICLE_BEHAVIOR_FLAG_10 | PARTICLE_BEHAVIOR_FLAG_20 | PARTICLE_BEHAVIOR_FLAG_40)) {
        particle->segment.x_velocity = behavior->unk30;
        particle->segment.y_velocity = behavior->unk34;
        particle->segment.z_velocity = behavior->unk38;
    } else {
        particle->segment.x_velocity = 0.0f;
        particle->segment.y_velocity = 0.0f;
        particle->segment.z_velocity = 0.0f;
    }

    randomizationFlags = behavior->randomizationFlags & (PARTICLE_RANDOM_VEL_Z | PARTICLE_RANDOM_VEL_Y | PARTICLE_RANDOM_VEL_X);
    if (randomizationFlags) {
        if (randomizationFlags & PARTICLE_RANDOM_VEL_X) {
            particle->segment.x_velocity +=
                (f32) get_random_number_from_range(-behavior->velocityRangeX1, behavior->velocityRangeX1) *
                0.00001525878906;
        }
        if (randomizationFlags & PARTICLE_RANDOM_VEL_Y) {
            particle->segment.y_velocity +=
                (f32) get_random_number_from_range(-behavior->velocityRangeY1, behavior->velocityRangeY1) *
                0.00001525878906;
        }
        if (randomizationFlags & PARTICLE_RANDOM_VEL_Z) {
            particle->segment.z_velocity +=
                (f32) get_random_number_from_range(-behavior->velocityRangeZ1, behavior->velocityRangeZ1) *
                0.00001525878906;
        }
    }

    switch (behavior->emitterFlags &
            (PARTICLE_BEHAVIOR_FLAG_10 | PARTICLE_BEHAVIOR_FLAG_20 | PARTICLE_BEHAVIOR_FLAG_40)) {
        case PARTICLE_BEHAVIOR_FLAG_10:
            particle->segment.x_velocity += obj->segment.x_velocity;
            particle->segment.y_velocity += obj->segment.y_velocity;
            particle->segment.z_velocity += obj->segment.z_velocity;
            break;
        case PARTICLE_BEHAVIOR_FLAG_40:
            particle->segment.x_velocity *= obj->segment.x_velocity;
            particle->segment.y_velocity *= obj->segment.y_velocity;
            particle->segment.z_velocity *= obj->segment.z_velocity;
            break;
    }

    if (behavior->emitterFlags & PARTICLE_BEHAVIOR_FLAG_4) {
        velocityPos.x = 0.0f;
        velocityPos.y = 0.0f;
        velocityPos.z = -behavior->unk3C;

        randomizationFlags = behavior->randomizationFlags;
        if (randomizationFlags & PARTICLE_UNK00000010) {
            velocityPos.z += (f32) get_random_number_from_range(-behavior->gravityRange2, behavior->gravityRange2) *
                             0.00001525878906;
        }

        if (randomizationFlags & (PARTICLE_UNK00000040 | PARTICLE_UNK00000020)) {
            angle.y_rotation = emitter->angle.direction.y_rotation;
            if (randomizationFlags & PARTICLE_UNK00000020) {
                angle.y_rotation += get_random_number_from_range(-behavior->angleRangeY2, behavior->angleRangeY2);
            }
            angle.x_rotation = emitter->angle.direction.x_rotation;
            if (randomizationFlags & PARTICLE_UNK00000040) {
                angle.x_rotation += get_random_number_from_range(-behavior->angleRangeX2, behavior->angleRangeX2);
            }
            f32_vec3_apply_object_rotation3(&angle, &velocityPos.x);
        } else {
            f32_vec3_apply_object_rotation3(&emitter->angle.direction, &velocityPos.x);
        }
        f32_vec3_apply_object_rotation((ObjectTransform *) particle->segment.parentObj, &velocityPos.x);

        particle->segment.x_velocity += velocityPos.x;
        particle->segment.y_velocity += velocityPos.y;
        particle->segment.z_velocity += velocityPos.z;
    }
}

void setup_particle_position(Particle *particle, Object *obj, ParticleEmitter *emitter, ParticleBehavior *behaviour) {
    s32 randomizationFlags;
    Vec3f posVel;
    Vec3s angle;

    particle->localPosX = emitter->baseVelX;
    particle->localPosY = emitter->baseVelY;
    particle->localPosZ = emitter->baseVelZ;
    particle->forwardVel = behaviour->forwardVel;
    if (behaviour->randomizationFlags & PARTICLE_FORWARDVEL) {
        particle->forwardVel +=
            (f32) get_random_number_from_range(-behaviour->velocityRange, behaviour->velocityRange) *
            0.00001525878906; // 0.00001525878906 ~= 1.0/65536.0
    }
    if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_1) {
        posVel.x = 0.0f;
        posVel.y = 0.0f;
        posVel.z = -behaviour->unk10;
        randomizationFlags = behaviour->randomizationFlags;
        if (randomizationFlags & PARTICLE_GRAVITY) {
            posVel.z += (f32) get_random_number_from_range(-behaviour->gravityRange1, behaviour->gravityRange1) *
                        0.00001525878906;
        }
        if (randomizationFlags & (PARTICLE_UNK00000004 | PARTICLE_UNK00000002)) {
            angle.y_rotation = emitter->angle.rotation.y_rotation;
            if (randomizationFlags & PARTICLE_UNK00000002) {
                angle.y_rotation += get_random_number_from_range(-behaviour->angleRangeY1, behaviour->angleRangeY1);
            }
            angle.x_rotation = emitter->angle.rotation.x_rotation;
            if (randomizationFlags & PARTICLE_UNK00000004) {
                angle.x_rotation += get_random_number_from_range(-behaviour->angleRangeX1, behaviour->angleRangeX1);
            }
            f32_vec3_apply_object_rotation3(&angle, (f32 *) &posVel);
        } else {
            f32_vec3_apply_object_rotation((ObjectTransform *) &emitter->angle.rotation, (f32 *) &posVel);
        }
        particle->localPosX += posVel.x;
        particle->localPosY += posVel.y;
        particle->localPosZ += posVel.z;
    }
    if (particle->segment.particle.movementType != PARTICLE_MOVEMENT_BASIC_PARENT) {
        f32_vec3_apply_object_rotation((ObjectTransform *) obj, &particle->localPosX);
    }
    particle->segment.trans.x_position = particle->localPosX;
    particle->segment.trans.y_position = particle->localPosY;
    particle->segment.trans.z_position = particle->localPosZ;
    if (particle->segment.particle.movementType == PARTICLE_MOVEMENT_BASIC_PARENT) {
        f32_vec3_apply_object_rotation((ObjectTransform *) obj, &particle->segment.trans.x_position);
    }
    particle->segment.trans.x_position += obj->segment.trans.x_position;
    particle->segment.trans.y_position += obj->segment.trans.y_position;
    particle->segment.trans.z_position += obj->segment.trans.z_position;
}

PointParticle *init_point_particle(Object *obj, ParticleEmitter *emitter) {
    ParticleProperties *properties;
    PointParticle *particle;
    ParticleModel *model;
    ParticleBehavior *behavior;

    properties = gParticlesAssetTable[emitter->propertyID];
    if (properties->kind != PARTICLE_KIND_POINT) {
        return NULL;
    }
    behavior = emitter->behaviour;
    particle = particle_allocate(PARTICLE_KIND_POINT);
    if (particle == NULL) {
        return particle;
    }
    
    particle->base.segment.particle.segmentID = obj->segment.object.segmentID;
    particle->base.segment.trans.flags = OBJ_FLAGS_DEACTIVATED;
    particle->base.segment.particle.movementType = properties->movementType;
    particle->base.segment.unk40 = properties->unk2;
    particle->base.segment.parentObj = obj;
    particle->pointEmitter = emitter;
    particle->base.segment.trans.scale = properties->scale * behavior->unk50;
    particle->base.segment.scaleVel = properties->scale * behavior->unk54;
    particle->base.segment.particle.destroyTimer = properties->lifeTime;
    particle->base.segment.particle.unk34 = 0.0f;
    particle->base.segment.particle.unk38 = 0;
    particle->base.colour.r = properties->colour.r;
    particle->base.colour.g = properties->colour.g;
    particle->base.colour.b = properties->colour.b;
    particle->base.colour.a = properties->colour.a;

    if (particle->base.segment.unk40 & PARTICLE_F40_800 && obj->shading != NULL) {
        particle->base.brightness = obj->shading->unk0 * 255.0f;
    } else {
        particle->base.brightness = 255;
    }
    particle->base.opacityTimer = properties->opacityTimer;
    if (emitter->emmmflags & PARTICLE_BEHAVIOR_FLAG_100) {
        particle->base.opacity = emitter->opacity;
    } else {
        particle->base.opacity = properties->opacity << 8;
    }
    if (properties->opacity < 255) {
        if (particle->base.segment.unk40 & PARTICLE_F40_1000) {
            particle->base.segment.trans.flags |= OBJ_FLAGS_UNK_0100;
        } else {
            particle->base.segment.trans.flags |= OBJ_FLAGS_UNK_0080;
        }
    }
    if (particle->base.opacityTimer < particle->base.segment.particle.destroyTimer) {
        particle->base.opacityVel = ((properties->opacityVel << 8) - (particle->base.opacity & 0xFFFF)) /
                                    (particle->base.segment.particle.destroyTimer - particle->base.opacityTimer);
    } else {
        particle->base.opacityVel = 0;
    }

    setup_particle_position(particle, obj, emitter, behavior);

    // Setup particle rotation
    if (behavior->emitterFlags & PARTICLE_BEHAVIOR_FLAG_80) {
        particle->base.segment.trans.rotation.y_rotation = behavior->angleOffsetY;
        particle->base.segment.trans.rotation.x_rotation = behavior->angleOffsetX;
        particle->base.segment.trans.rotation.z_rotation = behavior->angleOffsetZ;
    } else {
        particle->base.segment.trans.rotation.y_rotation =
            obj->segment.trans.rotation.y_rotation + behavior->angleOffsetY;
        particle->base.segment.trans.rotation.x_rotation =
            obj->segment.trans.rotation.x_rotation + behavior->angleOffsetX;
        particle->base.segment.trans.rotation.z_rotation =
            obj->segment.trans.rotation.z_rotation + behavior->angleOffsetZ;
    }
    particle->base.angleVelY = behavior->angleVelY;
    particle->base.angleVelX = behavior->angleVelX;
    particle->base.angleVelZ = behavior->angleVelZ;

    setup_particle_velocity(particle, obj, emitter, behavior);

    particle->base.gravity = gParticleGravityTable[(particle->base.segment.unk40 >> 4) & 7];
    if (particle->base.segment.particle.movementType == PARTICLE_MOVEMENT_VELOCITY) {
        particle->base.forwardVel = sqrtf((particle->base.segment.x_velocity * particle->base.segment.x_velocity) + (particle->base.segment.y_velocity * particle->base.segment.y_velocity) + (particle->base.segment.z_velocity * particle->base.segment.z_velocity));
    }
    if (behavior->emitterFlags & PARTICLE_BEHAVIOR_FLAG_2) {
        emitter->angle.rotation.z_rotation += behavior->unk1C;
        emitter->angle.direction.y_rotation += behavior->unk1E;
    }
    if (behavior->emitterFlags & PARTICLE_BEHAVIOR_FLAG_8) {
        emitter->angle.direction.x_rotation += behavior->unk2A;
        emitter->angle.direction.z_rotation += behavior->unk2C;
    }
    particle->base.segment.unk1A = properties->unk6;
    particle->base.segment.textureFrame = 0;
    model = particle->base.modelData;
    if (properties->textureID == -1) {
        model->texture = NULL;
    } else {
        model->texture = load_texture(properties->textureID);
        if (model->texture != NULL) {
            if (model->texture->flags & 4) {
                if (particle->base.segment.unk40 & PARTICLE_F40_1000) {
                    particle->base.segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    particle->base.segment.trans.flags |= OBJ_FLAGS_UNK_0080;
                }
            }
            if ((particle->base.segment.unk40 & (PARTICLE_F40_1 | PARTICLE_F40_2)) == PARTICLE_F40_2) {
                particle->base.segment.textureFrame = model->texture->numOfTextures - 1;
            }
        }
    }
    particle->modelFrame = 0;
    particle->unk76 = ((u32) (u16) properties->lifeTimeRange) >> 10;
    particle->unk77 = 0;
    if (model->texture == NULL) {
        particle_deallocate(particle);
        return NULL;
    }
    return particle;
}

Particle *init_line_particle(Object *obj, ParticleEmitter *emitter) {
    ParticleProperties *sp34;
    Particle *particle;
    ParticleModel *model;
    ParticleBehavior *sp28;
    unkParticleBehaviorUnk9C *sp24;

    sp34 = gParticlesAssetTable[emitter->propertyID];
    if (sp34->kind != PARTICLE_KIND_LINE) {
        return NULL;
    }
    sp28 = emitter->behaviour;
    sp24 = (unkParticleBehaviorUnk9C *) sp28->unk9C;
    particle = particle_allocate(PARTICLE_KIND_LINE);
    if (particle == NULL) {
        return NULL;
    }
    particle->segment.particle.segmentID = obj->segment.object.segmentID;
    particle->segment.trans.flags = OBJ_FLAGS_DEACTIVATED;
    particle->segment.particle.movementType = sp34->movementType;
    particle->segment.unk40 = sp34->unk2;
    particle->segment.parentObj = obj;
    particle->lineEmitter = emitter;
    particle->segment.trans.scale = sp34->scale * sp28->unk50;
    particle->segment.scaleVel = sp34->scale * sp28->unk54;
    particle->segment.particle.destroyTimer = sp34->lifeTime;
    particle->segment.particle.unk34 = 0.0f;
    particle->segment.particle.unk38 = 0;
    if (D_800E2D00->word != 0) {
        particle->colour.word = D_800E2D00->word;
    } else {
        particle->colour.r = sp34->colour.r;
        particle->colour.g = sp34->colour.g;
        particle->colour.b = sp34->colour.b;
    }
    particle->colour.a = sp34->colour.a;
    if (particle->segment.unk40 & PARTICLE_F40_800 && obj->shading != NULL) {
        particle->brightness = obj->shading->unk0 * 255.0f;
    } else {
        particle->brightness = 0xFF;
    }
    particle->opacityTimer = sp34->opacityTimer;
    particle->opacity = sp34->opacity << 8;
    if (sp34->opacity < 0xFF) {
        if (particle->segment.unk40 & PARTICLE_F40_1000) {
            particle->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
        } else {
            particle->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
        }
    }
    if (particle->opacityTimer < particle->segment.particle.destroyTimer) {
        particle->opacityVel =
            (((sp34->opacityVel - sp34->opacity) << 8) / (particle->segment.particle.destroyTimer - particle->opacityTimer));
    } else {
        particle->opacityVel = 0;
    }
    // TODO check union member
    emitter->pos.x = emitter->baseVelX;
    emitter->pos.y = emitter->baseVelY;
    emitter->pos.z = emitter->baseVelZ;
    f32_vec3_apply_object_rotation(&obj->segment.trans, &emitter->pos.x);
    emitter->pos.x += obj->segment.trans.x_position;
    emitter->pos.y += obj->segment.trans.y_position;
    emitter->pos.z += obj->segment.trans.z_position;
    particle->unk68b = 0;
    particle->unk6Ab = 0;
    particle->unk6Bb = -1;
    particle->segment.unk1A = sp34->unk6;
    particle->segment.textureFrame = 0;
    model = particle->modelData;
    if (sp34->textureID == -1) {
        model->texture = NULL;
    } else {
        model->texture = load_texture(sp34->textureID);
        if (model->texture != NULL) {
            if (model->texture->flags & 4) {
                if (particle->segment.unk40 & PARTICLE_F40_1000) {
                    particle->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    particle->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
                }
            }
            if ((particle->segment.unk40 & (PARTICLE_F40_1 | PARTICLE_F40_2)) == PARTICLE_F40_2) {
                particle->segment.textureFrame = model->texture->numOfTextures - 1;
            }
        }
    }
    model->vertices->x = emitter->pos.x;
    model->vertices->y = emitter->pos.y;
    model->vertices->z = emitter->pos.z;
    if ((u32) sp24 != -1U) {
        emitter->unk1E += 1;
        if (emitter->unk1E >= sp24[0].unk0) {
            emitter->unk1E = 0;
        }
        model->vertices->r = sp24[emitter->unk1E + 2].r;
        model->vertices->g = sp24[emitter->unk1E + 2].g;
        model->vertices->b = sp24[emitter->unk1E + 2].b;
        model->vertices->a = emitter->unk6;
    } else {
        model->vertices->r = particle->colour.r;
        model->vertices->g = particle->colour.g;
        model->vertices->b = particle->colour.b;
        model->vertices->a = emitter->unk6;
    }
    particle->unk6Ab = ((u32) sp34->lifeTimeRangeUnsigned >> 10);
    particle->unk6Bb = ((u32) (sp34->lifeTimeWord << 22) >> 26);
    particle->segment.trans.x_position = obj->segment.trans.x_position;
    particle->segment.trans.y_position = obj->segment.trans.y_position;
    particle->segment.trans.z_position = obj->segment.trans.z_position;
    emitter->opacity = 0;
    return particle;
}

Particle *init_general_particle(Object *obj, ParticleEmitter *emitter) {
    s32 randomizationFlags;
    ParticleProperties *properties;
    Particle *particle;
    TextureHeader **texture;
    ParticleBehavior *behaviour;
    unk800B1130_SP28 *sp28;
    f32 sp24;
    s8 sp23;

    properties = gParticlesAssetTable[emitter->propertyID];
    if (properties->kind == PARTICLE_KIND_LINE || properties->kind == PARTICLE_KIND_POINT) {
        return NULL;
    }
    behaviour = emitter->behaviour;
    sp28 = (unk800B1130_SP28 *) behaviour->unk9C;

    particle = particle_allocate(properties->kind);
    if (particle == NULL) {
        return particle;
    }
    particle->segment.particle.segmentID = obj->segment.particle.segmentID;
    particle->segment.trans.flags = OBJ_FLAGS_DEACTIVATED;
    particle->segment.particle.movementType = properties->movementType;
    particle->segment.unk40 = properties->unk2;
    particle->segment.parentObj = obj;
    if ((particle->segment.unk40 & PARTICLE_F40_800) && obj->shading != NULL) {
        particle->brightness = obj->shading->unk0 * 255.0f;
    } else {
        particle->brightness = 255;
    }
    sp24 = behaviour->unk50;
    if (behaviour->randomizationFlags & PARTICLE_UNK00020000) {
        sp24 += (f32) get_random_number_from_range(-behaviour->unk8C, behaviour->unk8C) * 0.00001525878906;
    }
    particle->segment.trans.scale = properties->scale * sp24;
    sp24 = behaviour->unk54;
    if (behaviour->randomizationFlags & PARTICLE_UNK00040000) {
        sp24 += (f32) get_random_number_from_range(-behaviour->unk90, behaviour->unk90) * 0.00001525878906;
    }
    if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_1000) {
        particle->segment.scaleVel = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                                         (obj->segment.y_velocity * obj->segment.y_velocity) +
                                         (obj->segment.z_velocity * obj->segment.z_velocity)) *
                                   sp24 * 0.1f;
    } else {
        particle->segment.scaleVel = properties->scale * sp24;
    }
    particle->segment.particle.destroyTimer =
        get_random_number_from_range(-properties->lifeTimeRange, properties->lifeTimeRange) + properties->lifeTime;
    particle->segment.particle.unk38 = 0.0f;
    particle->segment.particle.unk34 = 0.0f;
    if (D_800E2D00[0].word != 0) {
        particle->colour.word = D_800E2D00[0].word;
    } else if ((s32) sp28 != -1) {
        emitter->unk1E++;
        if (emitter->unk1E >= sp28->unk0) {
            emitter->unk1E = 0;
        }
        particle->colour.r = sp28[emitter->unk1E + 2].r;
        particle->colour.g = sp28[emitter->unk1E + 2].g;
        particle->colour.b = sp28[emitter->unk1E + 2].b;
        particle->colour.a = sp28[emitter->unk1E + 2].a;
    } else {
        particle->colour.r = properties->colour.r;
        particle->colour.g = properties->colour.g;
        particle->colour.b = properties->colour.b;
        particle->colour.a = properties->colour.a;
    }
    randomizationFlags = behaviour->randomizationFlags &
            (PARTICLE_COLOURVEL_ALPHA | PARTICLE_COLOURVEL_BLUE | PARTICLE_COLOURVEL_GREEN | PARTICLE_COLOURVEL_RED);
    if (randomizationFlags) {
        if (randomizationFlags & PARTICLE_COLOURVEL_RED) {
            particle->colour.r += get_random_number_from_range(-behaviour->colourRangeR, behaviour->colourRangeR);
        }
        if (randomizationFlags & PARTICLE_COLOURVEL_GREEN) {
            particle->colour.g += get_random_number_from_range(-behaviour->colourRangeG, behaviour->colourRangeG);
        }
        if (randomizationFlags & PARTICLE_COLOURVEL_BLUE) {
            particle->colour.b += get_random_number_from_range(-behaviour->colourRangeB, behaviour->colourRangeB);
        }
        if (randomizationFlags & PARTICLE_COLOURVEL_ALPHA) {
            particle->colour.a += get_random_number_from_range(-behaviour->colourRangeA, behaviour->colourRangeA);
        }
    }
    particle->opacityTimer = properties->opacityTimer;
    particle->opacity = properties->opacity * gParticleOpacity;
    if (properties->opacity < 255) {
        if (particle->segment.unk40 & PARTICLE_F40_1000) {
            particle->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
        } else {
            particle->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
        }
    }
    if (particle->opacityTimer < particle->segment.particle.destroyTimer) {
        particle->opacityVel = (s16) (((properties->opacityVel - properties->opacity) * gParticleOpacity) /
                                    (particle->segment.particle.destroyTimer - particle->opacityTimer));
    } else {
        particle->opacityVel = 0;
    }
    sp23 = 0;
    particle->segment.unk1A = properties->unk6;
    if (particle->segment.particle.kind == PARTICLE_KIND_SPRITE) {
        particle->modelData = (ParticleModel *) func_8007C12C(properties->textureID, 0);
        if (particle->modelData != NULL) {
            if ((*particle->unk44_1->unk8)->unk6 & 4) {
                if (particle->segment.unk40 & PARTICLE_F40_1000) {
                    particle->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    particle->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
                }
            }
            if (behaviour->emitterFlags & PARTICLE_ANGLE_Y) {
                particle->segment.textureFrame = get_random_number_from_range(0, particle->unk44_1->textureCount - 1) << 8;
                if ((particle->segment.unk40 & (PARTICLE_F40_1 | PARTICLE_F40_2)) == PARTICLE_F40_2) {
                    particle->segment.textureFrame |= 0xFF;
                }
            } else if ((particle->segment.unk40 & (PARTICLE_F40_1 | PARTICLE_F40_2)) == PARTICLE_F40_2) {
                particle->segment.textureFrame = (particle->unk44_1->textureCount << 8) - 1;
            } else {
                particle->segment.textureFrame = 0;
            }
        } else {
            sp23 = 1;
        }
    } else if ((particle->segment.particle.kind == PARTICLE_KIND_RECTANGLE) ||
               (particle->segment.particle.kind == PARTICLE_KIND_TRIANGLE)) {
        texture = &particle->modelData->texture;
        if (texture) {
            *texture = load_texture(properties->textureID);
            if (*texture != NULL) {
                if ((*texture)->flags & 4) {
                    if (particle->segment.unk40 & PARTICLE_F40_1000) {
                        particle->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                    } else {
                        particle->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
                    }
                }
                if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_800) {
                    particle->segment.textureFrame = get_random_number_from_range(0, ((*texture)->numOfTextures >> 8) - 1)
                                                   << 8;
                    if ((particle->segment.unk40 & (PARTICLE_F40_1 | PARTICLE_F40_2)) == PARTICLE_F40_2) {
                        particle->segment.textureFrame |= 0xFF;
                    }
                } else if ((particle->segment.unk40 & (PARTICLE_F40_1 | PARTICLE_F40_2)) == PARTICLE_F40_2) {
                    particle->segment.textureFrame = (*texture)->numOfTextures - 1;
                } else {
                    particle->segment.textureFrame = 0;
                }
            } else {
                sp23 = 1;
            }
        }
    }
    if (sp23 == 0) {
        if (particle->segment.particle.kind == PARTICLE_KIND_TRIANGLE) {
            func_800AF0A4(particle);
        }
        if (particle->segment.particle.kind == PARTICLE_KIND_RECTANGLE) {
            func_800AF0F0(particle);
        }
    }
    setup_particle_position(particle, obj, emitter, behaviour);
    if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_80) {
        particle->segment.trans.rotation.y_rotation = behaviour->angleOffsetY;
        particle->segment.trans.rotation.x_rotation = behaviour->angleOffsetX;
        particle->segment.trans.rotation.z_rotation = behaviour->angleOffsetZ;
    } else {
        particle->segment.trans.rotation.y_rotation = obj->segment.trans.rotation.y_rotation + behaviour->angleOffsetY;
        particle->segment.trans.rotation.x_rotation = obj->segment.trans.rotation.x_rotation + behaviour->angleOffsetX;
        particle->segment.trans.rotation.z_rotation = obj->segment.trans.rotation.z_rotation + behaviour->angleOffsetZ;
    }
    randomizationFlags = behaviour->randomizationFlags & (PARTICLE_ANGLE_Z | PARTICLE_ANGLE_X | PARTICLE_ANGLE_Y);
    if (randomizationFlags != 0) {
        if (randomizationFlags & PARTICLE_ANGLE_Y) {
            particle->segment.trans.rotation.y_rotation +=
                get_random_number_from_range(-behaviour->angleRangeY3, behaviour->angleRangeY3);
        }
        if (randomizationFlags & PARTICLE_ANGLE_X) {
            particle->segment.trans.rotation.x_rotation +=
                get_random_number_from_range(-behaviour->angleRangeX3, behaviour->angleRangeX3);
        }
        if (randomizationFlags & PARTICLE_ANGLE_Z) {
            particle->segment.trans.rotation.z_rotation +=
                get_random_number_from_range(-behaviour->angleRangeZ3, behaviour->angleRangeZ3);
        }
    }
    particle->angleVelY = behaviour->angleVelY;
    particle->angleVelX = behaviour->angleVelX;
    particle->angleVelZ = behaviour->angleVelZ;
    randomizationFlags = behaviour->randomizationFlags & (PARTICLE_ANGLEVEL_Z | PARTICLE_ANGLEVEL_X | PARTICLE_ANGLEVEL_Y);
    if (randomizationFlags) {
        if (randomizationFlags & PARTICLE_ANGLEVEL_Y) {
            particle->angleVelY += get_random_number_from_range(-behaviour->unk86, behaviour->unk86);
        }
        if (randomizationFlags & PARTICLE_ANGLEVEL_X) {
            particle->angleVelX += get_random_number_from_range(-behaviour->unk88, behaviour->unk88);
        }
        if (randomizationFlags & PARTICLE_ANGLEVEL_Z) {
            particle->angleVelZ += get_random_number_from_range(-behaviour->unk8A, behaviour->unk8A);
        }
    }
    setup_particle_velocity(particle, obj, emitter, behaviour);
    particle->gravity = gParticleGravityTable[(particle->segment.unk40 >> 4) & 7];
    if (particle->segment.particle.movementType == PARTICLE_MOVEMENT_VELOCITY) {
        particle->forwardVel = sqrtf((particle->segment.x_velocity * particle->segment.x_velocity) +
                                   (particle->segment.y_velocity * particle->segment.y_velocity) +
                                   (particle->segment.z_velocity * particle->segment.z_velocity));
    }
    if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_2) {
        emitter->unk6++;
        if (emitter->unk6 >= behaviour->unk1A) {
            emitter->angle.rotation.y_rotation += behaviour->unk1C;
            emitter->angle.rotation.x_rotation += behaviour->unk1E;
            emitter->angle.rotation.z_rotation += behaviour->unk18;
            emitter->unk6 -= behaviour->unk1A;
        }
    }
    if (behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_8) {
        emitter->lifeTime++;
        if (emitter->lifeTime >= behaviour->unk28) {
            emitter->angle.direction.y_rotation += behaviour->unk2A;
            emitter->angle.direction.x_rotation += behaviour->unk2C;
            emitter->angle.direction.z_rotation += behaviour->unk2E;
            emitter->lifeTime -= behaviour->unk28;
        }
    }
    if (particle->modelData == NULL) {
        particle_deallocate(particle);
        return NULL;
    } else {
        return particle;
    }
}

Particle *particle_allocate(s32 kind) {
    s32 i;
    Particle *particle;

    particle = NULL;
    i = 0;

    switch (kind) {
        case PARTICLE_KIND_SPRITE:
            if ((gSpriteParticleBuffer != NULL)) {
                if (gNumSpriteParticles >= gMaxSpriteParticles - 1) {
                    if (D_800E2CBC == 0) {
                        D_800E2CBC = 1;
                    }
                } else {
                    while (gSpriteParticleBuffer[i].segment.particle.kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gSpriteParticleBuffer[i].segment.particle.kind = PARTICLE_KIND_SPRITE;
                    gNumSpriteParticles++;
                    particle = &gSpriteParticleBuffer[i];
                }
            }
            break;
        case PARTICLE_KIND_TRIANGLE:
            if (gTriangleParticleBuffer != NULL) {
                if (gNumTriangleParticles >= gMaxTriangleParticles - 1) {
                    if (D_800E2CA4 == 0) {
                        D_800E2CA4 = 1;
                    }
                } else {
                    while (gTriangleParticleBuffer[i].segment.particle.kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gTriangleParticleBuffer[i].segment.particle.kind = PARTICLE_KIND_TRIANGLE;
                    gNumTriangleParticles++;
                    particle = &gTriangleParticleBuffer[i];
                }
            }
            break;
        case PARTICLE_KIND_RECTANGLE:
            if (gRectangleParticleBuffer != NULL) {
                if (gNumRectangleParticles >= gMaxRectangleParticles - 1) {
                    if (D_800E2CB0 == 0) {
                        D_800E2CB0 = 1;
                    }
                } else {
                    while (gRectangleParticleBuffer[i].segment.particle.kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gRectangleParticleBuffer[i].segment.particle.kind = PARTICLE_KIND_RECTANGLE;
                    gNumRectangleParticles++;
                    particle = &gRectangleParticleBuffer[i];
                }
            }
            break;
        case PARTICLE_KIND_LINE:
            if (gLineParticleBuffer != NULL) {
                if (gNumLineParticles >= gMaxLineParticles - 1) {
                    if (D_800E2CC8 == 0) {
                        D_800E2CC8 = 1;
                    }
                } else {
                    while (gLineParticleBuffer[i].segment.particle.kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gLineParticleBuffer[i].segment.particle.kind = PARTICLE_KIND_LINE;
                    gNumLineParticles++;
                    particle = &gLineParticleBuffer[i];
                }
            }
            break;
        case PARTICLE_KIND_POINT:
            if (gPointParticleBuffer != NULL) {
                if (gNumPointParticles >= gMaxPointParticles - 1) {
                    if (D_800E2CD4 == 0) {
                        D_800E2CD4 = 1;
                    }
                } else {
                    while (gPointParticleBuffer[i].base.segment.particle.kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gPointParticleBuffer[i].base.segment.particle.kind = PARTICLE_KIND_POINT;
                    gNumPointParticles++;
                    particle = &gPointParticleBuffer[i];
                }
            }
            break;
    }
    if (particle != NULL) {
        particle->behaviorId = -1;
    }
    return particle;
}

void particle_deallocate(Particle *particle) {
    TextureHeader *tex;

    switch (particle->segment.particle.kind) {
        case PARTICLE_KIND_SPRITE:
            if (gNumSpriteParticles > 0) {
                if (particle->modelData) {
                    free_sprite((Sprite *) particle->unk44_1);
                }
                gNumSpriteParticles--;
                particle->segment.particle.kind = PARTICLE_KIND_NONE;
            }
            break;
        case PARTICLE_KIND_NONE:
            return;
        case PARTICLE_KIND_TRIANGLE:
            if (gNumTriangleParticles > 0) {
                tex = particle->modelData->texture;
                if (tex != NULL) {
                    free_texture(tex);
                }
                gNumTriangleParticles--;
                particle->segment.particle.kind = PARTICLE_KIND_NONE;
            }
            break;
        case PARTICLE_KIND_RECTANGLE:
            if (gNumRectangleParticles > 0) {
                tex = particle->modelData->texture;
                if (tex != NULL) {
                    free_texture(tex);
                }
                gNumRectangleParticles--;
                particle->segment.particle.kind = PARTICLE_KIND_NONE;
            }
            break;
        case PARTICLE_KIND_LINE:
            if (gNumLineParticles > 0) {
                tex = particle->modelData->texture;
                if (tex != NULL) {
                    free_texture(tex);
                }
                gNumLineParticles--;
                particle->segment.particle.kind = PARTICLE_KIND_NONE;
            }
            break;
        case PARTICLE_KIND_POINT:
            if (gNumPointParticles > 0) {
                func_800B263C(particle);
                tex = particle->modelData->texture;
                if (tex != NULL) {
                    free_texture(tex);
                }
                gNumPointParticles--;
                particle->segment.particle.kind = PARTICLE_KIND_NONE;
            }
            break;
    }
}

void func_800B2260(ParticleEmitter *emitter) {
    PointParticle *temp_v0;
    s32 i;

    if (emitter->emmmflags & PARTICLE_BEHAVIOR_FLAG_400) {
        if (emitter->unkC_60 != NULL) {
            for (i = 0; i < emitter->unk6; i++) {
                temp_v0 = emitter->unkC_60[i];
                temp_v0->base.segment.particle.destroyTimer = 0;
                temp_v0->pointEmitter = 0;
            }
            mempool_free(emitter->unkC_60);
            emitter->unkC_60 = NULL;
        }
    }
}

/**
 * Call a function to update the current particle texture frame if applicable.
 * Applies movement, gets block ID and then shifts the opacity.
 */
void handle_particle_movement(Particle *particle, s32 updateRate) {
    LevelModelSegmentBoundingBox *boundingBox;
    PointParticle *pointParticle;

    gParticleUpdateRate = updateRate;
    pointParticle = NULL;
    if (particle->segment.particle.kind == PARTICLE_KIND_LINE) {
        move_line_particle(particle);
    } else {
        if (particle->segment.unk40 & (PARTICLE_F40_1 | PARTICLE_F40_2)) {
            if (gParticleUpdateRate > 0) {
                set_particle_texture_frame(particle);
            }
        }
        if (particle->segment.particle.kind == PARTICLE_KIND_POINT) {
            pointParticle = particle;
            pointParticle->modelFrame = 1 - pointParticle->modelFrame;
            pointParticle->unk77 = 0;
        }
        if (pointParticle == NULL || (pointParticle != NULL && pointParticle->pointEmitter != NULL)) {
            if (particle->segment.particle.movementType == PARTICLE_MOVEMENT_ACCELERATION) {
                move_particle_with_acceleration(particle);
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
        boundingBox = get_segment_bounding_box(particle->segment.particle.segmentID);
        if (boundingBox != NULL) {
            if (particle->segment.trans.x_position < boundingBox->x1 ||
                boundingBox->x2 < particle->segment.trans.x_position ||
                particle->segment.trans.y_position < boundingBox->y1 ||
                boundingBox->y2 < particle->segment.trans.y_position ||
                particle->segment.trans.z_position < boundingBox->z1 ||
                boundingBox->z2 < particle->segment.trans.z_position) {
                particle->segment.particle.segmentID = get_level_segment_index_from_position(
                    particle->segment.trans.x_position, particle->segment.trans.y_position,
                    particle->segment.trans.z_position);
            }
        } else {
            particle->segment.particle.segmentID = get_level_segment_index_from_position(
                particle->segment.trans.x_position, particle->segment.trans.y_position,
                particle->segment.trans.z_position);
        }
        particle->segment.particle.destroyTimer -= gParticleUpdateRate;
        if (particle->segment.particle.destroyTimer <= 0) {
            free_object((Object *) particle);
        } else {
            if (particle->opacityTimer == 0) {
                particle->opacity += gParticleUpdateRate * particle->opacityVel;
                if (particle->opacity < 0xFF) {
                    if (particle->segment.unk40 & PARTICLE_F40_1000) {
                        particle->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                    } else {
                        particle->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
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

void func_800B263C(PointParticle *arg0) {
    ParticleEmitter *new_var;
    PointParticle *new_var2;
    ParticleEmitter *temp_v0;
    s32 i;

    temp_v0 = arg0->pointEmitter;
    if (temp_v0 != NULL) {
        new_var = temp_v0;
        if (temp_v0->unk6 != 0) {
            if (&arg0->base == temp_v0->unkC_60[arg0->unk74]) {
                temp_v0->unk6--;
                for (i = arg0->unk74; i < temp_v0->unk6; i++) {
                    new_var->unkC_60[i] = new_var->unkC_60[i + 1];
                    new_var2 = new_var->unkC_60[i];
                    new_var2->unk74 = i;
                }
            }
        }
    }
}

void move_line_particle(Particle *particle) {
    Vec3f sp44;
    f32 tempf;
    f32 scale;
    ParticleModel *particleModel;
    Object *sp34;
    ParticleEmitter *sp30;
    unk800B1130_SP28 *sp2C;
    unk800B1130_SP28 **sp2C_ptr;

    sp34 = particle->segment.parentObj;
    particleModel = NULL;
    sp2C_ptr = &sp2C;

    if (sp34 != NULL) {
        sp30 = particle->lineEmitter;
        sp2C = sp30->behaviour->unk9C;
        particleModel = particle->modelData;
    }
    if (particle->unk68b < 2 && sp34 != NULL) {
        if (sp30->behaviour->emitterFlags & PARTICLE_BEHAVIOR_FLAG_1000) {
            scale = sqrtf((sp34->segment.x_velocity * sp34->segment.x_velocity) + (sp34->segment.y_velocity * sp34->segment.y_velocity) + (sp34->segment.z_velocity * sp34->segment.z_velocity));
            scale = scale * particle->segment.trans.scale * 0.1f;
        } else {
            scale = particle->segment.trans.scale;
        }
        if (!(particle->segment.unk40 & PARTICLE_F40_4000)) {
            sp44.x = 0.0f;
            sp44.y = 0.0f;
            sp44.z = 0.0f;
            switch (particle->unk6Ab) {
                default:
                    sp44.x = scale;
                    break;
                case 2:
                    sp44.z = scale;
                    break;
                case 1:
                    sp44.y = scale;
                    break;
            }
            f32_vec3_apply_object_rotation((ObjectTransform *) sp34, &sp44.x);
        } else {
            sp44.x = sp34->segment.x_velocity;
            sp44.y = sp34->segment.y_velocity;
            sp44.z = sp34->segment.z_velocity;
            tempf = ((sp44.x * sp44.x) + (sp44.y * sp44.y)) + (sp44.z * sp44.f[2]);
            if (tempf < 0.01f) {
                tempf = 1.0f;
            } else {
                tempf = scale / sqrtf(tempf);
            }
            sp44.x *= tempf;
            sp44.y *= tempf;
            sp44.z *= tempf;
            switch (particle->unk6Ab) {
                case 0:
                    tempf = sp44.x;
                    sp44.x = -sp44.z;
                    sp44.z = tempf;
                    break;
                case 1:
                    tempf = sp44.y;
                    sp44.y = -sp44.z;
                    sp44.z = tempf;
                    break;
            }
        }
        if (particleModel != NULL && particle->unk68b == 0) {
            particleModel->vertices[1].x = sp44.f[0] + sp30->pos.x;
            particleModel->vertices[1].y = sp44.f[1] + sp30->pos.y;
            particleModel->vertices[1].z = sp44.f[2] + sp30->pos.z;
            particleModel->vertices[1].r = particleModel->vertices->r;
            particleModel->vertices[1].g = particleModel->vertices->g;
            particleModel->vertices[1].b = particleModel->vertices->b;
            particleModel->vertices[1].a = sp30->unk6;

            particleModel->vertices[2].x = sp30->pos.x;
            particleModel->vertices[2].y = sp30->pos.y;
            particleModel->vertices[2].z = sp30->pos.z;
            if ((s32) *sp2C_ptr != -1) {
                particleModel->vertices[2].r = (*sp2C_ptr)[sp30->unk1E + 2].r;
                particleModel->vertices[2].g = (*sp2C_ptr)[sp30->unk1E + 2].g;
                particleModel->vertices[2].b = (*sp2C_ptr)[sp30->unk1E + 2].b;
                particleModel->vertices[2].a = sp30->unk6;
            } else {
                particleModel->vertices[2].r = particle->colour.r;
                particleModel->vertices[2].g = particle->colour.g;
                particleModel->vertices[2].b = particle->colour.b;
                particleModel->vertices[2].a = sp30->unk6;
            }
            particleModel->vertices[3].x = sp30->pos.x - sp44.f[0];
            particleModel->vertices[3].y = sp30->pos.y - sp44.f[1];
            particleModel->vertices[3].z = sp30->pos.z - sp44.f[2];
            particleModel->vertices[3].r = particleModel->vertices->r;
            particleModel->vertices[3].g = particleModel->vertices->g;
            particleModel->vertices[3].b = particleModel->vertices->b;
            particleModel->vertices[3].a = sp30->unk6;
            particle->unk68b = 1;
        } else if (particleModel != NULL) {
            particleModel->vertices[4].x = sp44.f[0] + sp30->pos.x;
            particleModel->vertices[4].y = sp44.f[1] + sp30->pos.y;
            particleModel->vertices[4].z = sp44.f[2] + sp30->pos.z;
            particleModel->vertices[4].r = particleModel->vertices[2].r;
            particleModel->vertices[4].g = particleModel->vertices[2].g;
            particleModel->vertices[4].b = particleModel->vertices[2].b;
            particleModel->vertices[4].a = sp30->unk6;
            particleModel->vertices[5].x = sp30->pos.x - sp44.f[0];
            particleModel->vertices[5].y = sp30->pos.y - sp44.f[1];
            particleModel->vertices[5].z = sp30->pos.z - sp44.f[2];
            particleModel->vertices[5].r = particleModel->vertices[2].r;
            particleModel->vertices[5].g = particleModel->vertices[2].g;
            particleModel->vertices[5].b = particleModel->vertices[2].b;
            particleModel->vertices[5].a = sp30->unk6;
            particle->unk68b = 2;
        }
    } else {
        particle->segment.particle.destroyTimer -= gParticleUpdateRate;
        if (particle->segment.particle.destroyTimer <= 0) {
            free_object((Object *) particle);
        } else if (particle->opacityTimer == 0) {
            particle->opacity += gParticleUpdateRate * particle->opacityVel;
            if (particle->opacity < 255) {
                if (particle->segment.unk40 & PARTICLE_F40_1000) {
                    particle->segment.trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    particle->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
                }
            }
        } else {
            particle->opacityTimer -= gParticleUpdateRate;
            if (particle->opacityTimer < 0) {
                particle->opacity -= particle->opacityTimer * particle->opacityVel;
                particle->opacityTimer = 0;
            }
        }
    }
    if (particleModel != NULL && particleModel->texture != NULL &&
        (particle->segment.unk40 & (PARTICLE_F40_1 | PARTICLE_F40_2)) && gParticleUpdateRate > 0) {
        set_particle_texture_frame(particle);
    }
}

void set_particle_texture_frame(Particle *particle) {
    s32 someFlag;
    s32 keepGoing;
    s32 i;
    s32 textureCount;
    s32 someFlag2;
    s32 someFlag3;
    s32 someFlag4;

    keepGoing = -1;

    i = PARTICLE_KIND_SPRITE; // This is needed to match.
    if (particle->segment.particle.kind == PARTICLE_KIND_SPRITE) {
        textureCount = particle->unk44_1->textureCount * 256;
    } else {
        textureCount = particle->modelData->texture->numOfTextures;
    }

    someFlag4 = particle->segment.unk40 & PARTICLE_F40_1;
    someFlag2 = particle->segment.unk40 & PARTICLE_F40_2;
    someFlag3 = particle->segment.unk40 & PARTICLE_F40_4;
    someFlag = particle->segment.unk40 & PARTICLE_F40_8;
    for (i = 0; (i++ < gParticleUpdateRate) && keepGoing;) {
        if (!someFlag) {
            particle->segment.textureFrame += particle->segment.unk1A;
            if (particle->segment.textureFrame >= textureCount) {
                if (someFlag2) {
                    particle->segment.textureFrame = ((textureCount * 2) - particle->segment.textureFrame) - 1;
                    someFlag = TRUE;
                    particle->segment.unk40 |= PARTICLE_F40_8;
                } else if (someFlag3) {
                    particle->segment.textureFrame -= textureCount;
                } else {
                    particle->segment.textureFrame = textureCount - 1;
                    keepGoing = FALSE;
                    particle->segment.unk40 &= ~(PARTICLE_F40_1 | PARTICLE_F40_2);
                }
            }
        } else {
            particle->segment.textureFrame -= particle->segment.unk1A;
            if (particle->segment.textureFrame < 0) {
                if (someFlag3) {
                    if (someFlag4) {
                        particle->segment.textureFrame = -particle->segment.textureFrame;
                        someFlag = FALSE;
                        particle->segment.unk40 &= ~PARTICLE_F40_8;
                    } else {
                        particle->segment.textureFrame += textureCount;
                    }
                } else {
                    particle->segment.textureFrame = 0;
                    keepGoing = FALSE;
                    particle->segment.unk40 &= ~(PARTICLE_F40_1 | PARTICLE_F40_2);
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
        particle->localPosX += particle->segment.x_velocity;
        particle->localPosY += particle->segment.y_velocity;
        particle->segment.y_velocity -= particle->gravity;
        particle->localPosZ += particle->segment.z_velocity;
        particle->segment.trans.rotation.y_rotation += particle->angleVelY;
        particle->segment.trans.rotation.x_rotation += particle->angleVelX;
        particle->segment.trans.rotation.z_rotation += particle->angleVelZ;
        particle->segment.trans.scale += particle->segment.scaleVel;
    }
    particle->segment.trans.x_position = particle->localPosX;
    particle->segment.trans.y_position = particle->localPosY;
    particle->segment.trans.z_position = particle->localPosZ;
    parent = particle->segment.parentObj;
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
    s32 i = gParticleUpdateRate;
    Object *parent;

    while (i-- > 0) {
        particle->segment.trans.rotation.y_rotation += particle->angleVelY;
        particle->segment.trans.rotation.x_rotation += particle->angleVelX;
        particle->segment.trans.rotation.z_rotation += particle->angleVelZ;
        particle->segment.trans.scale += particle->segment.scaleVel;
    }
    particle->segment.trans.x_position = 0.0f;
    particle->segment.trans.y_position = -particle->downOffset;
    particle->segment.trans.z_position = 0.0f;
    f32_vec3_apply_object_rotation(&particle->segment.trans, &particle->segment.trans.x_position);
    particle->segment.trans.x_position += particle->localPosX;
    particle->segment.trans.y_position += particle->localPosY;
    particle->segment.trans.z_position += particle->localPosZ;

    parent = particle->segment.parentObj;
    if (parent != NULL) {
        particle->segment.trans.x_position += parent->segment.trans.x_position;
        particle->segment.trans.y_position += parent->segment.trans.y_position;
        particle->segment.trans.z_position += parent->segment.trans.z_position;
    }
}

/**
 * Apply translation, rotation and scale based off the velocities of the particle.
 * Apply additional acceleration always directed downward in the local coordinate system
 */
void move_particle_with_acceleration(Particle *particle) {
    s32 i = 0;
    Vec3f acceleration;

    while (i++ < gParticleUpdateRate) {
        particle->segment.trans.x_position += particle->segment.x_velocity;
        particle->segment.trans.y_position += particle->segment.y_velocity;
        particle->segment.trans.z_position += particle->segment.z_velocity;
        particle->segment.trans.scale += particle->segment.scaleVel;
        particle->segment.trans.rotation.y_rotation += particle->angleVelY;
        particle->segment.trans.rotation.x_rotation += particle->angleVelX;
        particle->segment.trans.rotation.z_rotation += particle->angleVelZ;

        acceleration.x = 0.0f;
        acceleration.y = -particle->downAcceleration;
        acceleration.z = 0.0f;
        f32_vec3_apply_object_rotation(&particle->segment.trans, acceleration.f);
        particle->segment.x_velocity += acceleration.x;
        particle->segment.y_velocity += acceleration.y;
        particle->segment.y_velocity -= particle->gravity;
        particle->segment.z_velocity += acceleration.z;
    }
}

/**
 * Apply translation, rotation and scale based off the velocities of the particle.
 */
void move_particle_basic(Particle *particle) {
    s32 i = 0;

    while (i++ < gParticleUpdateRate) {
        particle->segment.trans.x_position += particle->segment.x_velocity;
        particle->segment.trans.y_position += particle->segment.y_velocity;
        particle->segment.y_velocity -= particle->gravity;
        particle->segment.trans.z_position += particle->segment.z_velocity;
        particle->segment.trans.scale += particle->segment.scaleVel;
        particle->segment.trans.rotation.y_rotation += particle->angleVelY;
        particle->segment.trans.rotation.x_rotation += particle->angleVelX;
        particle->segment.trans.rotation.z_rotation += particle->angleVelZ;
    }
}

/**
 * Apply translation, rotation and scale based off the velocities of the particle.
 * Velocity is set from forward velocity.
 * The particle always moves forward in the local coordinate system
 */
void move_particle_with_velocity(Particle *particle) {
    s32 i = 0;

    while (i++ < gParticleUpdateRate) {
        particle->segment.x_velocity = 0.0f;
        particle->segment.y_velocity = 0.0f;
        particle->segment.z_velocity = -particle->forwardVel;
        f32_vec3_apply_object_rotation3(&particle->segment.trans.rotation, &particle->segment.x_velocity);
        particle->segment.trans.x_position += particle->segment.x_velocity;
        particle->segment.trans.y_position += particle->segment.y_velocity - particle->gravity;
        particle->segment.trans.z_position += particle->segment.z_velocity;
        particle->segment.trans.scale += particle->segment.scaleVel;
        particle->segment.trans.rotation.y_rotation += particle->angleVelY;
        particle->segment.trans.rotation.x_rotation += particle->angleVelX;
        particle->segment.trans.rotation.z_rotation += particle->angleVelZ;
    }
}

/**
 * Iterate through every object and render it as particle if applicable.
 */
UNUSED void render_active_particles(Gfx **dList, MatrixS **arg1, Vertex **arg2) {
    UNUSED s32 pad;
    UNUSED s32 pad2;
    Particle **objects;
    s32 iObj;
    s32 nObjs;

    objects = objGetObjList(&iObj, &nObjs);
    for (; iObj < nObjs; iObj++) {
        if (objects[iObj]->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) {
            if (objects[iObj]->segment.unk40 & PARTICLE_F40_8000) {
                render_particle(objects[iObj], dList, arg1, arg2, 0);
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
    if ((particle->segment.unk40 & flags) && D_800E2CDC < 512) {
        return;
    }
    alpha = (particle->opacity >> 8) & 0xFF;
    if (alpha <= 0) {
        return;
    }
    if (particle->segment.particle.kind != PARTICLE_KIND_POINT && particle->segment.particle.kind != PARTICLE_KIND_LINE) {
        gDPSetEnvColor((*dList)++, particle->colour.r, particle->colour.g, particle->colour.b, particle->colour.a);
        if (alpha != 255) {
            renderFlags = (RENDER_Z_UPDATE | RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE);
            gDPSetPrimColor((*dList)++, 0, 0, particle->brightness, particle->brightness, particle->brightness, alpha);
        } else {
            gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
        }
        if (particle->segment.particle.kind == PARTICLE_KIND_SPRITE) {
            temp = particle->segment.textureFrame;
            particle->segment.textureFrame >>= 8;
            particle->segment.textureFrame = (particle->segment.textureFrame * 255) / (particle->unk44_1->textureCount);
            render_sprite_billboard(dList, mtx, vtx, (Object *) particle, (unk80068514_arg4 *) particle->modelData,
                                    renderFlags);
            particle->segment.textureFrame = temp;
        } else {
            modelData = particle->modelData;
            if (modelData->texture) {
                camera_push_model_mtx(dList, mtx, &particle->segment.trans, 1.0f, 0.0f);
                load_and_set_texture(dList, (TextureHeader *) modelData->texture, renderFlags,
                                     particle->segment.textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(modelData->vertices), modelData->vertexCount, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(modelData->triangles), modelData->triangleCount,
                           TRIN_ENABLE_TEXTURE);
                apply_matrix_from_stack(dList);
            }
        }
        if (alpha != 255 || particle->brightness != 255) {
            gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
        }
        if (particle->colour.a) {
            gDPSetEnvColor((*dList)++, 255, 255, 255, 0);
        }
    } else {
        renderFlags =
            (RENDER_VTX_ALPHA | RENDER_Z_UPDATE | RENDER_FOG_ACTIVE | RENDER_Z_COMPARE | RENDER_ANTI_ALIASING);
        gDPSetEnvColor((*dList)++, 255, 255, 255, 0);
        if (particle->segment.particle.kind == PARTICLE_KIND_POINT) {
            if (particle->segment.particle.destroyTimer > 0) {
                gDPSetPrimColor((*dList)++, 0, 0, particle->brightness, particle->brightness, particle->brightness,
                                255);
                if (((PointParticle *) particle)->unk77 == 0) {
                    func_800B3E64((PointParticle*)particle);
                }
                modelData = particle->modelData;
                temp = ((PointParticle *) particle)->modelFrame;
                temp <<= 3;
                tempvtx = &modelData->vertices[temp];
                load_and_set_texture(dList, modelData->texture, renderFlags, particle->segment.textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(tempvtx), modelData->vertexCount, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(modelData->triangles), modelData->triangleCount,
                           TRIN_ENABLE_TEXTURE);
                if (particle->brightness != 255) {
                    gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
                }
            }
        } else if (particle->segment.particle.kind == PARTICLE_KIND_LINE) {
            gDPSetPrimColor((*dList)++, 0, 0, particle->brightness, particle->brightness, particle->brightness, alpha);
            if (particle->unk68b >= 2) {
                modelData = particle->modelData;
                load_and_set_texture(dList, modelData->texture, renderFlags, particle->segment.textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(modelData->vertices), modelData->vertexCount, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(modelData->triangles), modelData->triangleCount, 1);
            } else if (particle->unk68b > 0) {
                modelData = particle->modelData;
                load_and_set_texture(dList, modelData->texture, renderFlags, particle->segment.textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(modelData->vertices), 4, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(&modelData->triangles[modelData->triangleCount]), 1,
                           TRIN_ENABLE_TEXTURE);
            }
            if (alpha != 255 || particle->brightness != 255) {
                gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
            }
        }
    }
}

void func_800B3E64(PointParticle *obj) {
    UNUSED s32 pad;
    s32 index;
    Vec3f vec3_1;
    Vec3f vec3_0;
    Particle *temp_s0;
    Particle *prev_s0;
    ParticleEmitter *emitter;
    ParticleModel *temp_s1;
    Vertex *otherVerts;
    Vertex *verts;
    ParticleModel *prev_s1;

    emitter = obj->pointEmitter;
    prev_s0 = NULL;
    prev_s1 = NULL;
    if (emitter != NULL) {
        if (emitter->unkC_60 != NULL) {
            index = emitter->unk6 - 1;
            while (index >= 0) {
                temp_s0 = emitter->unkC_60[index];
                if (temp_s0->segment.particle.destroyTimer != 0) {
                    temp_s1 = temp_s0->modelData;
                    vec3_0.x = temp_s0->segment.trans.scale;
                    vec3_0.y = 0.0f;
                    vec3_0.z = 0.0f;
                    f32_vec3_apply_object_rotation(&temp_s0->segment.trans, &vec3_0.f[0]);
                    vec3_1.x = 0.0f;
                    vec3_1.y = temp_s0->segment.trans.scale;
                    vec3_1.z = 0.0f;
                    f32_vec3_apply_object_rotation(&temp_s0->segment.trans, &vec3_1.f[0]);

                    // It seems super odd to do negative indices. Why not just increment by 4 and add up from there?
                    verts = &temp_s1->vertices[((PointParticle*) temp_s0)->modelFrame << 3];
                    if (1) {}
                    if (1) {}
                    if (1) {}
                    if (1) {}
                    if (1) {}
                    if (1) {} // Fake
                    verts += 7;
                    verts[-3].x = temp_s0->segment.trans.x_position + vec3_0.f[0];
                    verts[-3].y = temp_s0->segment.trans.y_position + vec3_0.f[1];
                    verts[-3].z = temp_s0->segment.trans.z_position + vec3_0.f[2];
                    verts[-3].r = temp_s0->colour.r;
                    verts[-3].g = temp_s0->colour.g;
                    verts[-3].b = temp_s0->colour.b;
                    verts[-3].a = temp_s0->opacity >> 8;

                    verts[-2].x = temp_s0->segment.trans.x_position + vec3_1.f[0];
                    verts[-2].y = temp_s0->segment.trans.y_position + vec3_1.f[1];
                    verts[-2].z = temp_s0->segment.trans.z_position + vec3_1.f[2];
                    verts[-2].r = temp_s0->colour.r;
                    verts[-2].g = temp_s0->colour.g;
                    verts[-2].b = temp_s0->colour.b;
                    verts[-2].a = temp_s0->opacity >> 8;

                    verts[-1].x = temp_s0->segment.trans.x_position - vec3_0.f[0];
                    verts[-1].y = temp_s0->segment.trans.y_position - vec3_0.f[1];
                    verts[-1].z = temp_s0->segment.trans.z_position - vec3_0.f[2];
                    verts[-1].r = temp_s0->colour.r;
                    verts[-1].g = temp_s0->colour.g;
                    verts[-1].b = temp_s0->colour.b;
                    verts[-1].a = temp_s0->opacity >> 8;
                    
                    verts[0].x = temp_s0->segment.trans.x_position - vec3_1.f[0];
                    verts[0].y = temp_s0->segment.trans.y_position - vec3_1.f[1];
                    verts[0].z = temp_s0->segment.trans.z_position - vec3_1.f[2];
                    verts[0].r = temp_s0->colour.r;
                    verts[0].g = temp_s0->colour.g;
                    verts[0].b = temp_s0->colour.b;
                    verts[0].a = temp_s0->opacity >> 8;

                    verts = &temp_s1->vertices[((PointParticle*) temp_s0)->modelFrame << 3];
                    if (prev_s1 != NULL) {
                        if (1) { // Fake
                            otherVerts = &prev_s1->vertices[((PointParticle*) prev_s0)->modelFrame << 3];
                        }
                        otherVerts += 4;
                    } else {
                        otherVerts = &temp_s1->vertices[((PointParticle*) temp_s0)->modelFrame << 3];
                        otherVerts += 4;
                    }

                    index--;
                    verts += 3;
                    otherVerts += 3;

                    prev_s0 = temp_s0;
                    prev_s1 = temp_s1;

                    verts[-3].x = otherVerts[-3].x;
                    verts[-3].y = otherVerts[-3].y;
                    verts[-3].z = otherVerts[-3].z;
                    verts[-3].r = otherVerts[-3].r;
                    verts[-3].g = otherVerts[-3].g;
                    verts[-3].b = otherVerts[-3].b;
                    verts[-3].a = otherVerts[-3].a;
                    verts[-2].x = otherVerts[-2].x;
                    verts[-2].y = otherVerts[-2].y;
                    verts[-2].z = otherVerts[-2].z;
                    verts[-2].r = otherVerts[-2].r;
                    verts[-2].g = otherVerts[-2].g;
                    verts[-2].b = otherVerts[-2].b;
                    verts[-2].a = otherVerts[-2].a;
                    verts[-1].x = otherVerts[-1].x;
                    verts[-1].y = otherVerts[-1].y;
                    verts[-1].z = otherVerts[-1].z;
                    verts[-1].r = otherVerts[-1].r;
                    verts[-1].g = otherVerts[-1].g;
                    verts[-1].b = otherVerts[-1].b;
                    verts[-1].a = otherVerts[-1].a;
                    verts[0].x = otherVerts[0].x;
                    verts[0].y = otherVerts[0].y;
                    verts[0].z = otherVerts[0].z;
                    verts[0].r = otherVerts[0].r;
                    verts[0].g = otherVerts[0].g;
                    verts[0].b = otherVerts[0].b;
                    verts[0].a = otherVerts[0].a;

                    ((PointParticle*)temp_s0)->unk77 = -1;

                    continue;
                }
                break;
            }
        }
    }
}

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
    temp_v0 = (obj->particleEmitter[idx].opacity & 0xFFFF) + arg2;
    if (arg3 < temp_v0) {
        obj->particleEmitter[idx].opacity = arg3;
    } else {
        obj->particleEmitter[idx].opacity = temp_v0;
    }
    obj->particleEmitter[idx].emmmflags |= PARTICLE_BEHAVIOR_FLAG_100;
}

void func_800B46BC(Object *obj, s32 idx, s32 arg2, s32 arg3) {
    s32 temp_v0;

    arg3 <<= 8;
    temp_v0 = (obj->particleEmitter[idx].opacity & 0xFFFF) - arg2;
    if (temp_v0 < arg3) {
        obj->particleEmitter[idx].opacity = arg3;
    } else {
        obj->particleEmitter[idx].opacity = temp_v0;
    }
    obj->particleEmitter[idx].emmmflags |= PARTICLE_BEHAVIOR_FLAG_100;
}
