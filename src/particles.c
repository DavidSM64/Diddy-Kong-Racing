#include "particles.h"
#include "objects.h"
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

s32 gNumTriangleParticles = 0;
s32 gTriangleParticleBufferFull = FALSE;
Particle *gTriangleParticleBuffer = NULL;
s32 gNumRectangleParticles = 0;
s32 gRectangleParticleBufferFull = FALSE;
Particle *gRectangleParticleBuffer = NULL;
s32 gNumSpriteParticles = 0;
s32 gSpriteParticleBufferFull = FALSE;
Particle *gSpriteParticleBuffer = NULL;
s32 gNumLineParticles = 0;
s32 gLineParticleBufferFull = FALSE;
Particle *gLineParticleBuffer = NULL;
s32 gNumPointParticles = 0;
s32 gPointParticleBufferFull = FALSE;
PointParticle *gPointParticleBuffer = NULL;

UNUSED s32 D_800E2CDC = 0; // Only ever and checked for being less than 512.
Vertex *gParticleVertexBuffer = NULL;
Triangle *gParticleTriangleBuffer = NULL;
s32 gParticlesAssetTableCount = 0;
s32 *gParticlesAssets = NULL;

ParticleDescriptor **gParticlesAssetTable = NULL;
s32 gParticleBehavioursAssetTableCount = 0;
s32 *gParticleBehavioursAssets = NULL;
ParticleBehaviour **gParticleBehavioursAssetTable = NULL;
ColourRGBA gParticleOverrideColor[2] = { { { { 0 } } }, { { { 0 } } } };

Triangle gLineParticleTriangles[5] = {
    // Use these 4 triangles if the particle is fully rendered
    { { { BACKFACE_DRAW, 0, 1, 2 } }, { { { 256, 0 } } }, { { { 0, 480 } } }, { { { 256, 480 } } } },
    { { { BACKFACE_DRAW, 0, 2, 3 } }, { { { 256, 0 } } }, { { { 256, 480 } } }, { { { 480, 480 } } } },
    { { { BACKFACE_DRAW, 1, 2, 4 } }, { { { 0, 0 } } }, { { { 256, 0 } } }, { { { 0, 480 } } } },
    { { { BACKFACE_DRAW, 2, 3, 5 } }, { { { 256, 0 } } }, { { { 480, 0 } } }, { { { 480, 480 } } } },
    // Use this one triangle if the particle is partially rendered
    { { { BACKFACE_DRAW, 0, 1, 3 } }, { { { 256, 0 } } }, { { { 0, 480 } } }, { { { 480, 480 } } } }
};

Vec3s gLineParticleVCoords[5] = {
    { { { 0, 511, 511 } } }, { { { 0, 511, 511 } } }, { { { 0, 0, 511 } } },
    { { { 0, 0, 511 } } },   { { { 0, 511, 511 } } },
};

Triangle gPointParticleTriangles[8] = {
    { { { BACKFACE_CULL, 0, 1, 5 } }, { { { 0, 0 } } }, { { { 128, 0 } } }, { { { 128, 511 } } } },
    { { { BACKFACE_CULL, 0, 5, 4 } }, { { { 0, 0 } } }, { { { 128, 511 } } }, { { { 0, 511 } } } },
    { { { BACKFACE_CULL, 1, 2, 6 } }, { { { 128, 0 } } }, { { { 256, 0 } } }, { { { 256, 511 } } } },
    { { { BACKFACE_CULL, 1, 6, 5 } }, { { { 128, 0 } } }, { { { 256, 511 } } }, { { { 128, 511 } } } },
    { { { BACKFACE_CULL, 2, 3, 7 } }, { { { 256, 0 } } }, { { { 384, 0 } } }, { { { 384, 511 } } } },
    { { { BACKFACE_CULL, 2, 7, 6 } }, { { { 256, 0 } } }, { { { 384, 511 } } }, { { { 256, 511 } } } },
    { { { BACKFACE_CULL, 3, 0, 4 } }, { { { 384, 0 } } }, { { { 512, 0 } } }, { { { 512, 511 } } } },
    { { { BACKFACE_CULL, 3, 4, 7 } }, { { { 384, 0 } } }, { { { 512, 511 } } }, { { { 384, 511 } } } },
};

Vec3s gPointParticleVCoords[8] = {
    { { { 0, 0, 511 } } }, { { { 0, 511, 511 } } }, { { { 0, 0, 511 } } }, { { { 0, 511, 511 } } },
    { { { 0, 0, 511 } } }, { { { 0, 511, 511 } } }, { { { 0, 0, 511 } } }, { { { 0, 511, 511 } } },
};

s16 gParticleTextureScrollOffset = 0;

f32 gParticleGravityTable[8] = { 0.0f, 0.1, 0.2f, 0.3f, 0.45f, 0.525f, 0.6f, 0.8f };

s32 gMaxTriangleParticles = 0;
s32 gMaxRectangleParticles = 0;
s32 gMaxSpriteParticles = 0;
s32 gMaxLineParticles = 0;
s32 gMaxPointParticles = 0;
Sprite **D_800E2E60 = NULL; // Sprites loaded from asset 47; appears to be unused
s32 D_800E2E64 = 0;         // Number of sprites in D_800E2E60

Vec2s gParticleCoordListTri[3] = {
    { { { 0, 8 } } },
    { { { 7, -4 } } },
    { { { -7, -4 } } },
};

Vec2s gParticleCoordListQuad[4] = {
    { { { -6, 6 } } },
    { { { 6, 6 } } },
    { { { 6, -6 } } },
    { { { -6, -6 } } },
};

ColourRGBA gVehicleTrackMarkColors[16] = {
    { { { 0, 0, 0, 0 } } },        // SURFACE_DEFAULT
    { { { 192, 8, 64, 255 } } },   // SURFACE_GRASS
    { { { 255, 96, 8, 255 } } },   // SURFACE_SAND
    { { { 64, 64, 64, 255 } } },   // SURFACE_ZIP_PAD
    { { { 0, 0, 0, 0 } } },        // SURFACE_STONE
    { { { 0, 0, 0, 0 } } },        // SURFACE_EGG_SPAWN
    { { { 0, 0, 0, 0 } } },        // SURFACE_EGG_01
    { { { 0, 0, 0, 0 } } },        // SURFACE_EGG_02
    { { { 0, 0, 0, 0 } } },        // SURFACE_EGG_03
    { { { 0, 0, 0, 0 } } },        // SURFACE_EGG_04
    { { { 0, 0, 0, 0 } } },        // SURFACE_FROZEN_WATER
    { { { 0, 0, 0, 0 } } },        // SURFACE_UNK0B
    { { { 0, 0, 0, 0 } } },        // SURFACE_TAJ_PAD
    { { { 16, 112, 255, 255 } } }, // SURFACE_SNOW
    { { { 0, 0, 0, 0 } } },        // SURFACE_UNK0E
    { { { 0, 0, 0, 0 } } },        // SURFACE_UNK0F
};

ColourRGBA D_800E2EC4[10] = {
    { { { 64, 64, 64, 255 } } },  { { { 64, 64, 64, 255 } } },  { { { 0, 45, 0, 255 } } },
    { { { 0, 45, 0, 255 } } },    { { { 64, 60, 10, 255 } } },  { { { 64, 60, 10, 255 } } },
    { { { 64, 64, 255, 255 } } }, { { { 64, 64, 255, 255 } } }, { { { 64, 64, 64, 255 } } },
    { { { 64, 64, 64, 255 } } },
};

s32 gCurrentHovercraftParticleOpacity = 256;

/*******************************/

/************ .bss ************/

s32 gParticleUpdateRate;
UNUSED s32 D_80127C84;
s16 gHovercraftParticleOpacities[8];
// printf.c
// thread0_epc
/******************************/

/**
 * Deallocate all memory buffers used by particles.
 */
void reset_particles(void) {
    free_particle_buffers();
    free_particle_vertices_triangles();
    free_unknown_particle_sprites();
}

/**
 * Deallocate all memory buffers used by particles and unload all related assets
 */
void reset_particles_with_assets(void) {
    free_particle_buffers();
    free_particle_vertices_triangles();
    free_particle_assets();
    free_unknown_particle_sprites();
}

/**
 * Deallocate buffers used for sprites from asset 47.
 */
void free_unknown_particle_sprites(void) {
    s32 i;

    if (D_800E2E60 != NULL) {
        for (i = 0; i < D_800E2E64; i++) {
            sprite_free(D_800E2E60[i]);
        }
        mempool_free(D_800E2E60);
        D_800E2E60 = 0;
    }
}

/**
 * Free buffers allocated for particle objects.
 */
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

/**
 * Free buffers allocated for triangles and vertices used in particle models.
 */
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

/**
 * Unload all assets related to particles.
 */
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

/**
 * Load all assets related to particles.
 */
void init_particle_assets(void) {
    s32 i;

    free_particle_assets();
    gParticlesAssetTable = (ParticleDescriptor **) load_asset_section_from_rom(ASSET_PARTICLES_TABLE);
    gParticlesAssetTableCount = -1;
    while (((s32) gParticlesAssetTable[gParticlesAssetTableCount + 1]) != -1) {
        gParticlesAssetTableCount++;
    }

    gParticlesAssets = (s32 *) load_asset_section_from_rom(ASSET_PARTICLES);
    for (i = 0; i < gParticlesAssetTableCount; i++) {
        gParticlesAssetTable[i] = (ParticleDescriptor *) (((u8 *) gParticlesAssets) + ((s32) gParticlesAssetTable[i]));
    }

    gParticleBehavioursAssetTable = (ParticleBehaviour **) load_asset_section_from_rom(ASSET_PARTICLE_BEHAVIORS_TABLE);
    gParticleBehavioursAssetTableCount = -1;
    while (((s32) gParticleBehavioursAssetTable[gParticleBehavioursAssetTableCount + 1]) != -1) {
        gParticleBehavioursAssetTableCount++;
    }

    gParticleBehavioursAssets = (s32 *) load_asset_section_from_rom(ASSET_PARTICLE_BEHAVIORS);
    for (i = 0; i < gParticleBehavioursAssetTableCount; i++) {
        gParticleBehavioursAssetTable[i] =
            (ParticleBehaviour *) (((u8 *) gParticleBehavioursAssets) + ((s32) gParticleBehavioursAssetTable[i]));
        if (((u32) gParticleBehavioursAssetTable[i]->colourLoop) != 0xFFFFFFFF) {
            gParticleBehavioursAssetTable[i]->colourLoop =
                (ColorLoopEntry *) get_misc_asset((s32) gParticleBehavioursAssetTable[i]->colourLoop);
        }
    }
}

/**
 * https://decomp.me/scratch/z60XZ
 *
 * Allocate buffers for particle objects.
 * Generate particle shapes.
 * Load sprites from asset 47.
 */
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

    gParticleOverrideColor->word = 0;

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
    gTriangleParticleBufferFull = FALSE;
    gMaxRectangleParticles = maxRectangleParticles;
    gRectangleParticleBufferFull = FALSE;
    gMaxSpriteParticles = maxSpriteParticles;
    gSpriteParticleBufferFull = FALSE;
    gMaxLineParticles = maxLineParticles;
    gLineParticleBufferFull = FALSE;
    gMaxPointParticles = maxPointParticles;
    gPointParticleBufferFull = FALSE;

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

    modelPtr = (ParticleModel *) &gTriangleParticleBuffer[gMaxTriangleParticles];
    for (i = 0; i < gMaxTriangleParticles; i++) {
        gTriangleParticleBuffer[i].model = &modelPtr[i];
        init_triangle_particle_model(gTriangleParticleBuffer[i].model, &sp54, &sp50);
    }

    modelPtr = (ParticleModel *) &gRectangleParticleBuffer[gMaxRectangleParticles];
    for (i = 0; i < gMaxRectangleParticles; i++) {
        gRectangleParticleBuffer[i].model = &modelPtr[i];
        init_rectangle_particle_model(gRectangleParticleBuffer[i].model, &sp54, &sp50);
    }

    modelPtr = (ParticleModel *) &gLineParticleBuffer[gMaxLineParticles];
    for (i = 0; i < gMaxLineParticles; i++) {
        gLineParticleBuffer[i].model = &modelPtr[i];
        sp50 = gLineParticleTriangles;
        init_line_particle_model(gLineParticleBuffer[i].model, &sp54, &sp50);
    }

    modelPtr = (ParticleModel *) &gPointParticleBuffer[gMaxPointParticles];
    for (i = 0; i < gMaxPointParticles; i++) {
        gPointParticleBuffer[i].base.model = &modelPtr[i];
        sp50 = gPointParticleTriangles;
        init_point_particle_model(gPointParticleBuffer[i].base.model, &sp54, &sp50);
    }

    for (i = 0; i < gMaxTriangleParticles; i++) {
        gTriangleParticleBuffer[i].kind = PARTICLE_KIND_NONE;
    }

    for (i = 0; i < gMaxRectangleParticles; i++) {
        gRectangleParticleBuffer[i].kind = PARTICLE_KIND_NONE;
    }

    for (i = 0; i < gMaxSpriteParticles; i++) {
        gSpriteParticleBuffer[i].kind = PARTICLE_KIND_NONE;
    }

    for (i = 0; i < gMaxLineParticles; i++) {
        gLineParticleBuffer[i].kind = PARTICLE_KIND_NONE;
    }

    for (i = 0; i < gMaxPointParticles; i++) {
        gPointParticleBuffer[i].base.kind = PARTICLE_KIND_NONE;
    }

    if (D_800E2E60 == NULL) {
        asset2F = (s16 *) load_asset_section_from_rom(ASSET_BINARY_47);
        D_800E2E64 = 0;
        while (asset2F[D_800E2E64] != -1) {
            D_800E2E64++;
        }

        D_800E2E60 = mempool_alloc_safe(D_800E2E64 * 4, COLOUR_TAG_BLUE);
        for (i = 0; i < D_800E2E64; i++) {
            D_800E2E60[i] = (Sprite *) tex_load_sprite(asset2F[i] & 0x3FFF, 1);
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
void init_triangle_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
    s16 i;
    Vertex *tempVtx;
    Triangle *tempTri;
    Vec2s *coordList;

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
    tempTri->flags = BACKFACE_DRAW;
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
void init_rectangle_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
    s16 i;
    Vertex *tempVtx;
    Triangle *tempTri;
    Vec2s *coordList;

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
    tempTri[0].flags = BACKFACE_DRAW;
    tempTri[0].vi0 = 3;
    tempTri[0].uv0.u = 0;
    tempTri[0].vi1 = 1;
    tempTri[0].uv1.v = 0;
    tempTri[0].vi2 = 0;
    tempTri[0].uv2.u = 0;
    tempTri[0].uv2.v = 0;
    tempTri[1].flags = BACKFACE_DRAW;
    tempTri[1].vi0 = 3;
    tempTri[1].uv0.u = 0;
    tempTri[1].vi1 = 2;
    tempTri[1].vi2 = 1;
    tempTri[1].uv2.v = 0;
    tempTri += 2;
    *triangles = tempTri;
}

/**
 * Initializes the model for a line particle without setting coordinates.
 */
void init_line_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
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

/**
 * Initializes the model for a point particle without setting coordinates.
 */
void init_point_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles) {
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

/**
 * Sets texture coordinates for the triangle of a triangle particle.
 */
void set_triangle_texture_coords(Particle *particle) {
    ParticleModel *model;
    Triangle *tri;
    s16 texV, texU;

    model = particle->model;
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

/**
 * Sets texture coordinates for the triangle of a rectangle particle.
 */
void set_rectangle_texture_coords(Particle *particle) {
    ParticleModel *model;
    Triangle *tris;
    s16 texV, texU;

    model = particle->model;
    tris = model->triangles;
    texU = (model->texture->width - 1) << 5;
    texV = (model->texture->height - 1) << 5;

    tris[0].uv0.v = texV;
    tris[0].uv1.u = texU;
    tris[1].uv0.v = texU;
    tris[1].uv1.u = texU;
    tris[1].uv1.v = texV;
    tris[1].uv2.u = texU;
}

/**
 * Sets the particle type, behaviour, and position for the emitter.
 * Ignores the emitter position specified for the current behaviour.
 * Does nothing if the particle type and behaviour are the same as previously set.
 */
void emitter_change_settings(ParticleEmitter *emitter, s32 behaviourID, s32 particleID, s16 posX, s16 posY, s16 posZ) {
    ParticleBehaviour *behaviour;
    if (particleID >= gParticlesAssetTableCount) {
        particleID = 0;
    }
    if (behaviourID >= gParticleBehavioursAssetTableCount) {
        behaviourID = 0;
    }
    behaviour = gParticleBehavioursAssetTable[behaviourID];
    if (emitter->descriptorID != particleID || behaviour != emitter->behaviour) {
        emitter_cleanup(emitter);
        emitter_init_with_pos(emitter, behaviourID, particleID, posX, posY, posZ);
    }
}

/**
 * Initializes the emitter with the specified particle type and behaviour.
 */
void emitter_init(ParticleEmitter *emitter, s32 behaviourID, s32 particleID) {
    ParticleBehaviour *behaviour;

    if (behaviourID < gParticleBehavioursAssetTableCount) {
        behaviour = gParticleBehavioursAssetTable[behaviourID];
        emitter_init_with_pos(emitter, behaviourID, particleID, behaviour->emitterPos.x, behaviour->emitterPos.y,
                              behaviour->emitterPos.z);
    }
}

/**
 * Main function to initialize the emitter.
 * Sets the geometry used for generating particles, depending on the particle type.
 */
void emitter_init_with_pos(ParticleEmitter *emitter, s32 behaviourID, s32 particleID, s16 posX, s16 posY, s16 posZ) {
    ParticleBehaviour *behaviour;

    behaviour = gParticleBehavioursAssetTable[behaviourID];
    emitter->descriptorID = particleID;
    emitter->behaviour = behaviour;
    emitter->position.x = posX;
    emitter->position.y = posY;
    emitter->position.z = posZ;
    emitter->colourIndex = 0;

    if (behaviour->flags & PARTICLE_LINE) {
        emitter->flags = PARTICLE_LINE;
        emitter->lineOpacity = 0;
        emitter->lineRefPoint.x = 0.0f;
        emitter->lineRefPoint.y = 0.0f;
        emitter->lineRefPoint.z = 0.0f;
    } else if (behaviour->flags & PARTICLE_POINT) {
        emitter->pointCount = 0;
        emitter->flags = PARTICLE_POINT;
        // Maximum number of points equals the particle's lifetime
        if (gParticlesAssetTable[particleID]->lifeTime <= 255) {
            emitter->maxPointCount = gParticlesAssetTable[particleID]->lifeTime;
        } else {
            emitter->maxPointCount = 255;
        }
        emitter->refPoints = (PointParticle **) mempool_alloc_safe(emitter->maxPointCount * sizeof(PointParticle *),
                                                                   COLOUR_TAG_SEMITRANS_GREY);
        emitter->pointSourceRotation.y_rotation = behaviour->sourceRotation.y_rotation;
        emitter->pointSourceRotation.x_rotation = behaviour->sourceRotation.x_rotation;
        emitter->pointEmissionDirection.y_rotation = behaviour->emissionDirection.y_rotation;
        emitter->pointEmissionDirection.x_rotation = behaviour->emissionDirection.x_rotation;
    } else {
        emitter->flags = PARTICLE_FLAGS_NONE;
        emitter->sourceRotation.y_rotation = behaviour->sourceRotation.y_rotation;
        emitter->sourceRotation.x_rotation = behaviour->sourceRotation.x_rotation;
        emitter->sourceRotation.z_rotation = behaviour->sourceRotation.z_rotation;
        emitter->emissionDirection.y_rotation = behaviour->emissionDirection.y_rotation;
        emitter->emissionDirection.x_rotation = behaviour->emissionDirection.x_rotation;
        emitter->emissionDirection.z_rotation = behaviour->emissionDirection.z_rotation;
    }
}

/**
 * Scrolls textures downward for point and line particles.
 * Texture state repeats in an 8-frame loop.
 */
void scroll_particle_textures(s32 updateRate) {
    s32 i;
    s32 j;

    gParticleTextureScrollOffset = (gParticleTextureScrollOffset + (updateRate << 6)) & 0x1FF;

    for (i = 0, j = 0; i < ARRAY_COUNT(gLineParticleTriangles); i++) {
        gLineParticleTriangles[i].uv0.v = gLineParticleVCoords[j].s[0] + gParticleTextureScrollOffset;
        gLineParticleTriangles[i].uv1.v = gLineParticleVCoords[j].s[1] + gParticleTextureScrollOffset;
        gLineParticleTriangles[i].uv2.v = gLineParticleVCoords[j].s[2] + gParticleTextureScrollOffset;
        j++;
    }

    for (i = 0, j = 0; i < ARRAY_COUNT(gPointParticleTriangles); i++) {
        gPointParticleTriangles[i].uv0.v = gPointParticleVCoords[j].s[0] + gParticleTextureScrollOffset;
        gPointParticleTriangles[i].uv1.v = gPointParticleVCoords[j].s[1] + gParticleTextureScrollOffset;
        gPointParticleTriangles[i].uv2.v = gPointParticleVCoords[j].s[2] + gParticleTextureScrollOffset;
        j++;
    }
}

/**
 * Initializes the emitter if it has been activated for an object.
 * Sets the geometry used for generating particles, depending on the particle type.
 */
void obj_enable_emitter(Object *obj, s32 emitterIndex) {
    s32 i;
    ParticleEmitter *emitter;
    ParticleBehaviour *behaviour;

    emitter = &obj->particleEmitter[emitterIndex];
    behaviour = emitter->behaviour;
    emitter->timeFromLastSpawn = 0;

    if (emitter->flags & PARTICLE_LINE) {
        emitter->lineRefPoint.x = obj->segment.trans.x_position;
        emitter->lineRefPoint.y = obj->segment.trans.y_position;
        emitter->lineRefPoint.z = obj->segment.trans.z_position;
    } else if (emitter->flags & PARTICLE_POINT) {
        emitter->point_opacity = gParticlesAssetTable[emitter->descriptorID]->colour.a << 8;

        if (emitter->pointCount > 0) { // Useless if statement, since the loop already does this.
            for (i = 0; i < emitter->pointCount; i++) {
                PointParticle *temp = emitter->refPoints[i];
                temp->base.destroyTimer = 0;
            }
        }
        if (behaviour->flags & PARTICLE_SOURCE_OFFSET_ENABLED) {
            emitter->pointSourceRotation.y_rotation = behaviour->sourceRotation.y_rotation;
            emitter->pointSourceRotation.x_rotation = behaviour->sourceRotation.x_rotation;
        }
        if (behaviour->flags & PARTICLE_SOURCE_EMITS_WITH_VELOCITY) {
            emitter->pointEmissionDirection.y_rotation = behaviour->emissionDirection.y_rotation;
            emitter->pointEmissionDirection.x_rotation = behaviour->emissionDirection.x_rotation;
        }
    } else {
        if (behaviour->flags & PARTICLE_SOURCE_OFFSET_ENABLED) {
            emitter->sourceRotationCounter = 0;
            emitter->sourceRotation.y_rotation = behaviour->sourceRotation.y_rotation;
            emitter->sourceRotation.x_rotation = behaviour->sourceRotation.x_rotation;
            emitter->sourceRotation.z_rotation = behaviour->sourceRotation.z_rotation;
        }
        if (behaviour->flags & PARTICLE_SOURCE_EMITS_WITH_VELOCITY) {
            emitter->emissionDirRotationCounter = 0;
            emitter->emissionDirection.y_rotation = behaviour->emissionDirection.y_rotation;
            emitter->emissionDirection.x_rotation = behaviour->emissionDirection.x_rotation;
            emitter->emissionDirection.z_rotation = behaviour->emissionDirection.z_rotation;
        }
    }
    emitter->flags &= ~PARTICLE_POINT_EMITTER_DISABLED;
    emitter->flags |= PARTICLE_EMITTER_ENABLED | PARTICLE_EMITTER_AWAITING_SPAWN;
    obj->segment.numActiveEmitters++;
}

/**
 * Deinitializes the emitter if it was deactivated for a given object.
 */
void obj_disable_emitter(Object *obj, s32 emitterIndex) {
    ParticleEmitter *emitter;

    emitter = &obj->particleEmitter[emitterIndex];

    emitter->flags &= ~PARTICLE_EMITTER_ENABLED;
    obj->segment.numActiveEmitters--;
}

/**
 * Creates particles for vehicle-related effects like dust, tyre marks, and wing trails.
 * The colour of the particles is determined by the surface type the vehicle is moving on, which is why this logic is
 * separated.
 */
void update_vehicle_particles(Object *racerObj, s32 updateRate) {
    Object_Racer *racer;
    ParticleDescriptor *descriptor;
    s32 opacity;
    s32 temp_v1;
    s32 i;
    ParticleEmitter *new_var;

    s32 var_t1;
    s32 someBool;
    s8 vehicleId;
    u32 emittersEnabled;
    u8 *alphaPtr;

    racer = &racerObj->unk64->racer;
    emittersEnabled = racerObj->particleEmittersEnabled;
    vehicleId = racer->vehicleID;
    i = 0;
    object_do_player_tumble(racerObj);
    for (; i < racerObj->segment.header->particleCount; i++) {
        if (emittersEnabled & OBJ_EMIT_1) {
            someBool = TRUE;
            switch (vehicleId) {
                case VEHICLE_CAR:
                    if (i >= 0 && i < 10) {
                        // Dust effects for vehicle ?
                        opacity = racer->unk16E;
                        if (opacity < 0) {
                            opacity = -opacity;
                        }
                        opacity -= 24;
                        if (opacity > 0) {
                            descriptor = gParticlesAssetTable[racerObj->particleEmitter[i].descriptorID];
                            alphaPtr = &D_800E2EC4[i].a;
                            var_t1 = 4;
                            if (opacity > 32) {
                                opacity = 32;
                            }
                            var_t1 = opacity << var_t1;
                            temp_v1 = var_t1 - ((opacity * opacity) >> 2);
                            gParticleOverrideColor[0].word =
                                ((((D_800E2EC4[i].r - descriptor->colour.r) * temp_v1) >> 8) + descriptor->colour.r)
                                << 24;
                            gParticleOverrideColor[0].word |=
                                (descriptor->colour.g + ((((D_800E2EC4[i].g - descriptor->colour.g) * temp_v1)) >> 8))
                                << 16;
                            gParticleOverrideColor[0].word |=
                                (descriptor->colour.b + ((((D_800E2EC4[i].b - descriptor->colour.b) * temp_v1)) >> 8))
                                << 8;
                            if (opacity > 16) {
                                var_t1 = 256;
                            }
                            opacity = descriptor->colour.a;
                            gParticleOverrideColor[0].word |= opacity + (((*alphaPtr - opacity) * var_t1) >> 8);
                        }
                    } else {
                        // Tire marks
                        switch (i) {
                            case 10:
                                if (racer->wheel_surfaces[2] == SURFACE_NONE) {
                                    someBool = FALSE;
                                }
                                gParticleOverrideColor[0].word =
                                    gVehicleTrackMarkColors[racer->wheel_surfaces[2] & 0xF].word;
                                break;
                            case 11:
                                if (racer->wheel_surfaces[3] == SURFACE_NONE) {
                                    someBool = FALSE;
                                }
                                gParticleOverrideColor[0].word =
                                    gVehicleTrackMarkColors[racer->wheel_surfaces[3] & 0xF].word;
                                break;
                            case 12:
                                if (racer->wheel_surfaces[0] == SURFACE_NONE) {
                                    someBool = FALSE;
                                }
                                gParticleOverrideColor[0].word =
                                    gVehicleTrackMarkColors[racer->wheel_surfaces[0] & 0xF].word;
                                break;
                            case 13:
                                if (racer->wheel_surfaces[1] == SURFACE_NONE) {
                                    someBool = FALSE;
                                }
                                gParticleOverrideColor[0].word =
                                    gVehicleTrackMarkColors[racer->wheel_surfaces[1] & 0xF].word;
                                break;
                        }
                    }
                    break;
                case VEHICLE_PLANE:
                    if (i == 0) {
                        gParticleOverrideColor[0].word = gVehicleTrackMarkColors[racer->wheel_surfaces[0] & 0xF].word;
                    } else if (i == 1) {
                        gParticleOverrideColor[0].word = gVehicleTrackMarkColors[racer->wheel_surfaces[1] & 0xF].word;
                    }
                    break;
                case VEHICLE_HOVERCRAFT:
                    if (i == 2 || i == 3) {
                        opacity = gHovercraftParticleOpacities[racer->racerIndex & 7];
                        opacity += updateRate * 4;
                        if (opacity > 256) {
                            opacity = 256;
                        }
                        gHovercraftParticleOpacities[racer->racerIndex & 7] = opacity;
                        gCurrentHovercraftParticleOpacity = opacity;
                    }
                    break;
            }

            if (someBool) {
                if (!(racerObj->particleEmitter[i].flags & PARTICLE_EMITTER_ENABLED)) {
                    obj_enable_emitter(racerObj, i);
                }
                if (racerObj->particleEmitter[i].flags & PARTICLE_LINE) {
                    obj_trigger_emitter(racerObj, &racerObj->particleEmitter[i]);
                } else if (racerObj->particleEmitter[i].flags & PARTICLE_POINT) {
                    obj_trigger_emitter(racerObj, &racerObj->particleEmitter[i]);
                } else {
                    racerObj->particleEmitter[i].timeFromLastSpawn += updateRate;
                    if (racerObj->particleEmitter[i].timeFromLastSpawn >=
                        racerObj->particleEmitter[i].behaviour->spawnInterval) {
                        obj_trigger_emitter(racerObj, &racerObj->particleEmitter[i]);
                    }
                }
            }
        } else if (racerObj->particleEmitter[i].flags & PARTICLE_EMITTER_ENABLED) {
            if (racerObj->particleEmitter[i].flags & PARTICLE_LINE) {
                ParticleEmitter *new_var2 = &racerObj->particleEmitter[i];
                new_var2->lineOpacity = 0;
                obj_disable_emitter(racerObj, i);
            } else {
                if (racerObj->particleEmitter[i].flags & PARTICLE_POINT) {
                    new_var = &racerObj->particleEmitter[i];
                    racerObj->particleEmitter[i].flags |= PARTICLE_POINT_EMITTER_DISABLED;
                    if (new_var->pointCount == 0) {
                        obj_disable_emitter(racerObj, i);
                    }
                } else {
                    obj_disable_emitter(racerObj, i);
                }
            }
            if (i == 2 || i == 3) {
                gHovercraftParticleOpacities[racer->racerIndex & 7] = 0;
            }
        }
        gParticleOverrideColor[0].word = 0;
        emittersEnabled >>= 1;
        gCurrentHovercraftParticleOpacity = 256;
    }

    object_undo_player_tumble(racerObj);
}

/**
 * Update all particle emitters attached to the object and spawn new particles
 */
void obj_spawn_particle(Object *obj, s32 updateRate) {
    s32 new_opacity;
    s32 i;
    u32 bits;

    bits = obj->particleEmittersEnabled;
    for (i = 0; i < obj->segment.header->particleCount; i++) {
        if (bits & 1) {
            if (!(obj->particleEmitter[i].flags & PARTICLE_EMITTER_ENABLED)) {
                obj_enable_emitter(obj, i);
            }
            if (obj->particleEmitter[i].flags & PARTICLE_LINE) {
                obj_trigger_emitter(obj, &obj->particleEmitter[i]);
            } else if ((obj->particleEmitter[i].flags & PARTICLE_POINT)) {
                obj_trigger_emitter(obj, &obj->particleEmitter[i]);
            } else {
                obj->particleEmitter[i].timeFromLastSpawn += updateRate;
                if (obj->particleEmitter[i].timeFromLastSpawn >= obj->particleEmitter[i].behaviour->spawnInterval) {
                    obj_trigger_emitter(obj, &obj->particleEmitter[i]);
                }
            }
        } else {
            if (obj->particleEmitter[i].flags & PARTICLE_EMITTER_ENABLED) {
                if (obj->particleEmitter[i].flags & PARTICLE_LINE) {
                    // Line particles are not immediately disabled, but instead, they gradually fade away over a few
                    // frames.
                    ParticleEmitter *emitter = &obj->particleEmitter[i];
                    new_opacity = emitter->lineOpacity - 64;
                    if (new_opacity < 0) {
                        new_opacity = 0;
                    }
                    emitter->lineOpacity = new_opacity;
                    obj_trigger_emitter(obj, emitter);
                    emitter->lineOpacity = new_opacity;
                    if (new_opacity == 0) {
                        obj_disable_emitter(obj, i);
                    }
                } else if ((obj->particleEmitter[i].flags & PARTICLE_POINT)) {
                    ParticleEmitter *emitter = &obj->particleEmitter[i];
                    obj->particleEmitter[i].flags |= PARTICLE_POINT_EMITTER_DISABLED;
                    if (emitter->pointCount == 0) {
                        obj_disable_emitter(obj, i);
                    }
                } else {
                    obj_disable_emitter(obj, i);
                }
            }
        }
        bits >>= 1;
    }
}

/**
 * Generates particles from a specific emitter attached to the object.
 * The particles are created according to the emitter's settings and behaviour.
 */
void obj_trigger_emitter(Object *obj, ParticleEmitter *emitter) {
    s32 i;
    ParticleBehaviour *behaviour;

    behaviour = emitter->behaviour;
    if (emitter->flags & PARTICLE_LINE) {
        Particle *particle = create_line_particle(obj, emitter);
        if (particle != NULL) {
            add_particle_to_entity_list((Object *) particle);
        }
        emitter->flags &= ~PARTICLE_EMITTER_AWAITING_SPAWN;
        if (emitter->lineOpacity + 64 > 255) {
            emitter->lineOpacity = 255;
        } else {
            emitter->lineOpacity += 64;
        }
    } else if (emitter->flags & PARTICLE_POINT) {
        if (emitter->pointCount < emitter->maxPointCount) {
            PointParticle *particle = create_point_particle(obj, emitter);
            emitter->flags &= ~PARTICLE_EMITTER_AWAITING_SPAWN;
            if (particle != NULL) {
                add_particle_to_entity_list((Object *) particle);
                particle->pointIndex = emitter->pointCount;
                particle->base.descFlags |= PARTICLE_DESC_FLAG_2000;
                emitter->refPoints[emitter->pointCount] = particle;
                emitter->pointCount++;
            }
        }
    } else {
        while (emitter->timeFromLastSpawn >= behaviour->spawnInterval) {
            emitter->timeFromLastSpawn -= behaviour->spawnInterval;
            for (i = 0; i < behaviour->burstCount; i++) {
                Particle *particle = create_general_particle(obj, emitter);
                if (particle != NULL) {
                    add_particle_to_entity_list((Object *) particle);
                    particle_update(particle, emitter->timeFromLastSpawn);
                }
                emitter->flags &= ~PARTICLE_EMITTER_AWAITING_SPAWN;
            }
        }
    }
}

/**
 * Initializes the particle velocity.
 */
void setup_particle_velocity(Particle *particle, Object *obj, ParticleEmitter *emitter, ParticleBehaviour *behaviour) {
    s32 randomizationFlags;
    Vec3f sourceVel;
    Vec3s angle;

    if (behaviour->flags &
        (PARTICLE_VELOCITY_RELATIVE_TO_PARENT | PARTICLE_VELOCITY_ABSOLUTE | PARTICLE_VELOCITY_SCALED_FROM_PARENT)) {
        particle->velocity.x = behaviour->velocityModifier.x;
        particle->velocity.y = behaviour->velocityModifier.y;
        particle->velocity.z = behaviour->velocityModifier.z;
    } else {
        particle->velocity.x = 0.0f;
        particle->velocity.y = 0.0f;
        particle->velocity.z = 0.0f;
    }

    randomizationFlags = behaviour->randomizationFlags &
                         (PARTICLE_RANDOM_VELOCITY_Z | PARTICLE_RANDOM_VELOCITY_Y | PARTICLE_RANDOM_VELOCITY_X);
    if (randomizationFlags) {
        if (randomizationFlags & PARTICLE_RANDOM_VELOCITY_X) {
            particle->velocity.x +=
                (f32) rand_range(-behaviour->velocityModifierRange.x, behaviour->velocityModifierRange.x) *
                0.00001525878906;
        }
        if (randomizationFlags & PARTICLE_RANDOM_VELOCITY_Y) {
            particle->velocity.y +=
                (f32) rand_range(-behaviour->velocityModifierRange.y, behaviour->velocityModifierRange.y) *
                0.00001525878906;
        }
        if (randomizationFlags & PARTICLE_RANDOM_VELOCITY_Z) {
            particle->velocity.z +=
                (f32) rand_range(-behaviour->velocityModifierRange.z, behaviour->velocityModifierRange.z) *
                0.00001525878906;
        }
    }

    switch (behaviour->flags & (PARTICLE_VELOCITY_RELATIVE_TO_PARENT | PARTICLE_VELOCITY_ABSOLUTE |
                                PARTICLE_VELOCITY_SCALED_FROM_PARENT)) {
        case PARTICLE_VELOCITY_RELATIVE_TO_PARENT:
            particle->velocity.x += obj->segment.x_velocity;
            particle->velocity.y += obj->segment.y_velocity;
            particle->velocity.z += obj->segment.z_velocity;
            break;
        case PARTICLE_VELOCITY_SCALED_FROM_PARENT:
            particle->velocity.x *= obj->segment.x_velocity;
            particle->velocity.y *= obj->segment.y_velocity;
            particle->velocity.z *= obj->segment.z_velocity;
            break;
    }

    if (behaviour->flags & PARTICLE_SOURCE_EMITS_WITH_VELOCITY) {
        sourceVel.x = 0.0f;
        sourceVel.y = 0.0f;
        sourceVel.z = -behaviour->emissionSpeed;

        randomizationFlags = behaviour->randomizationFlags;
        if (randomizationFlags & PARTICLE_RANDOM_EMISSION_SPEED) {
            sourceVel.z +=
                (f32) rand_range(-behaviour->emissionSpeedRange, behaviour->emissionSpeedRange) * 0.00001525878906;
        }

        if (randomizationFlags & (PARTICLE_RANDOM_EMISSION_DIR_PITCH | PARTICLE_RANDOM_EMISSION_DIR_YAW)) {
            angle.y_rotation = emitter->emissionDirection.y_rotation;
            if (randomizationFlags & PARTICLE_RANDOM_EMISSION_DIR_YAW) {
                angle.y_rotation +=
                    rand_range(-behaviour->emissionDirRange.y_rotation, behaviour->emissionDirRange.y_rotation);
            }
            angle.x_rotation = emitter->emissionDirection.x_rotation;
            if (randomizationFlags & PARTICLE_RANDOM_EMISSION_DIR_PITCH) {
                angle.x_rotation +=
                    rand_range(-behaviour->emissionDirRange.x_rotation, behaviour->emissionDirRange.x_rotation);
            }
            vec3f_rotate_py(&angle, &sourceVel);
        } else {
            vec3f_rotate_py(&emitter->emissionDirection, &sourceVel);
        }
        vec3f_rotate(&particle->parentObj->segment.trans.rotation, &sourceVel);

        particle->velocity.x += sourceVel.x;
        particle->velocity.y += sourceVel.y;
        particle->velocity.z += sourceVel.z;
    }
}

/**
 * Initializes the particle position.
 */
void setup_particle_position(Particle *particle, Object *obj, ParticleEmitter *emitter, ParticleBehaviour *behaviour) {
    s32 randomizationFlags;
    Vec3f sourcePos;
    Vec3s sourceDir;

    particle->localPos.x = emitter->position.x;
    particle->localPos.y = emitter->position.y;
    particle->localPos.z = emitter->position.z;

    // particle->movementParam shares memory with other fields; use the appropriate one based on movement type
    particle->movementParam = behaviour->movementParam;
    if (behaviour->randomizationFlags & PARTICLE_RANDOM_MOVEMENT_PARAM) {
        particle->movementParam += (f32) rand_range(-behaviour->movementParamRange, behaviour->movementParamRange) *
                                   0.00001525878906; // 0.00001525878906 ~= 1.0/65536.0
    }

    if (behaviour->flags & PARTICLE_SOURCE_OFFSET_ENABLED) {
        sourcePos.x = 0.0f;
        sourcePos.y = 0.0f;
        sourcePos.z = -behaviour->sourceDistance;
        randomizationFlags = behaviour->randomizationFlags;
        if (randomizationFlags & PARTICLE_RANDOM_SOURCE_DISTANCE) {
            sourcePos.z +=
                (f32) rand_range(-behaviour->sourceDistanceRange, behaviour->sourceDistanceRange) * 0.00001525878906;
        }
        if (randomizationFlags & (PARTICLE_RANDOM_SOURCE_PITCH | PARTICLE_RANDOM_SOURCE_YAW)) {
            sourceDir.y_rotation = emitter->sourceRotation.y_rotation;
            if (randomizationFlags & PARTICLE_RANDOM_SOURCE_YAW) {
                sourceDir.y_rotation +=
                    rand_range(-behaviour->sourceDirRange.y_rotation, behaviour->sourceDirRange.y_rotation);
            }
            sourceDir.x_rotation = emitter->sourceRotation.x_rotation;
            if (randomizationFlags & PARTICLE_RANDOM_SOURCE_PITCH) {
                sourceDir.x_rotation +=
                    rand_range(-behaviour->sourceDirRange.x_rotation, behaviour->sourceDirRange.x_rotation);
            }
            vec3f_rotate_py(&sourceDir, &sourcePos);
        } else {
            vec3f_rotate(&emitter->sourceRotation, &sourcePos);
        }
        particle->localPos.x += sourcePos.x;
        particle->localPos.y += sourcePos.y;
        particle->localPos.z += sourcePos.z;
    }
    if (particle->movementType != PARTICLE_MOVEMENT_BASIC_PARENT) {
        vec3f_rotate(&obj->segment.trans.rotation, &particle->localPos);
    }
    particle->trans.x_position = particle->localPos.x;
    particle->trans.y_position = particle->localPos.y;
    particle->trans.z_position = particle->localPos.z;
    if (particle->movementType == PARTICLE_MOVEMENT_BASIC_PARENT) {
        vec3f_rotate(&obj->segment.trans.rotation, (Vec3f *) &particle->trans.x_position);
    }

    particle->trans.x_position += obj->segment.trans.x_position;
    particle->trans.y_position += obj->segment.trans.y_position;
    particle->trans.z_position += obj->segment.trans.z_position;
}

/**
 * Create point particle and initialize it's fields.
 */
PointParticle *create_point_particle(Object *obj, ParticleEmitter *emitter) {
    ParticleDescriptor *descriptor;
    PointParticle *particle;
    ParticleModel *model;
    ParticleBehaviour *behaviour;

    descriptor = gParticlesAssetTable[emitter->descriptorID];
    if (descriptor->kind != PARTICLE_KIND_POINT) {
        return NULL;
    }
    behaviour = emitter->behaviour;
    particle = (PointParticle *) particle_allocate(PARTICLE_KIND_POINT);
    if (particle == NULL) {
        return particle;
    }

    particle->base.segmentID = obj->segment.object.segmentID;
    particle->base.trans.flags = OBJ_FLAGS_PARTICLE;
    particle->base.movementType = descriptor->movementType;
    particle->base.descFlags = descriptor->flags;
    particle->base.parentObj = obj;
    particle->pointEmitter = emitter;
    particle->base.trans.scale = descriptor->scale * behaviour->scale;
    particle->base.scaleVelocity = descriptor->scale * behaviour->scaleVelocity;
    particle->base.destroyTimer = descriptor->lifeTime;
    particle->base.unk34 = 0.0f;
    particle->base.unk38 = 0;
    particle->base.colour.r = descriptor->colour.r;
    particle->base.colour.g = descriptor->colour.g;
    particle->base.colour.b = descriptor->colour.b;
    particle->base.colour.a = descriptor->colour.a;

    if (particle->base.descFlags & PARTICLE_SHADED && obj->shading != NULL) {
        particle->base.brightness = obj->shading->unk0 * 255.0f;
    } else {
        particle->base.brightness = 255;
    }

    particle->base.opacityTimer = descriptor->opacityTimer;
    if (emitter->flags & PARTICLE_OVERRIDE_OPACITY_FROM_DESCRIPTOR) {
        particle->base.opacity = emitter->point_opacity;
    } else {
        particle->base.opacity = descriptor->opacity << 8;
    }
    if (descriptor->opacity < 255) {
        if (particle->base.descFlags & PARTICLE_DESC_FLAG_1000) {
            particle->base.trans.flags |= OBJ_FLAGS_UNK_0100;
        } else {
            particle->base.trans.flags |= OBJ_FLAGS_UNK_0080;
        }
    }
    if (particle->base.opacityTimer < particle->base.destroyTimer) {
        particle->base.opacityVel = ((descriptor->opacityVel << 8) - (particle->base.opacity & 0xFFFF)) /
                                    (particle->base.destroyTimer - particle->base.opacityTimer);
    } else {
        particle->base.opacityVel = 0;
    }

    setup_particle_position(&particle->base, obj, emitter, behaviour);

    // Setup particle rotation
    if (behaviour->flags & PARTICLE_ROTATION_ABSOLUTE) {
        particle->base.trans.rotation.y_rotation = behaviour->rotation.y_rotation;
        particle->base.trans.rotation.x_rotation = behaviour->rotation.x_rotation;
        particle->base.trans.rotation.z_rotation = behaviour->rotation.z_rotation;
    } else {
        particle->base.trans.rotation.y_rotation =
            obj->segment.trans.rotation.y_rotation + behaviour->rotation.y_rotation;
        particle->base.trans.rotation.x_rotation =
            obj->segment.trans.rotation.x_rotation + behaviour->rotation.x_rotation;
        particle->base.trans.rotation.z_rotation =
            obj->segment.trans.rotation.z_rotation + behaviour->rotation.z_rotation;
    }
    particle->base.angularVelocity.y_rotation = behaviour->angularVelocity.y_rotation;
    particle->base.angularVelocity.x_rotation = behaviour->angularVelocity.x_rotation;
    particle->base.angularVelocity.z_rotation = behaviour->angularVelocity.z_rotation;

    setup_particle_velocity(&particle->base, obj, emitter, behaviour);

    particle->base.gravity = gParticleGravityTable[(particle->base.descFlags >> 4) & 7];

    if (particle->base.movementType == PARTICLE_MOVEMENT_FORWARD) {
        particle->base.forwardVel = sqrtf((particle->base.velocity.x * particle->base.velocity.x) +
                                          (particle->base.velocity.y * particle->base.velocity.y) +
                                          (particle->base.velocity.z * particle->base.velocity.z));
    }

    if (behaviour->flags & PARTICLE_SOURCE_ROTATION_ENABLED) {
        emitter->pointSourceRotation.y_rotation += behaviour->sourceAngularVelocity.y_rotation;
        emitter->pointSourceRotation.x_rotation += behaviour->sourceAngularVelocity.x_rotation;
    }
    if (behaviour->flags & PARTICLE_ROTATING_DIRECTION) {
        emitter->pointEmissionDirection.y_rotation += behaviour->emissionDirAngularVelocity.y_rotation;
        emitter->pointEmissionDirection.x_rotation += behaviour->emissionDirAngularVelocity.x_rotation;
    }

    particle->base.textureFrameStep = descriptor->textureFrameStep;
    particle->base.textureFrame = 0;

    model = particle->base.model;
    if (descriptor->textureID == -1) {
        model->texture = NULL;
    } else {
        model->texture = load_texture(descriptor->textureID);
        if (model->texture != NULL) {
            if (model->texture->flags & 4) {
                if (particle->base.descFlags & PARTICLE_DESC_FLAG_1000) {
                    particle->base.trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    particle->base.trans.flags |= OBJ_FLAGS_UNK_0080;
                }
            }
            if ((particle->base.descFlags &
                 (PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED)) ==
                PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED) {
                particle->base.textureFrame = model->texture->numOfTextures - 1;
            }
        }
    }
    particle->modelFrame = 0;
    particle->unused_76 = descriptor->unused_point_field;
    particle->meshRegenerated = FALSE;
    if (model->texture == NULL) {
        // Only point particles with textures are supported
        particle_deallocate(&particle->base);
        return NULL;
    }
    return particle;
}

/**
 * Create line particle and initialize its fields.
 */
Particle *create_line_particle(Object *obj, ParticleEmitter *emitter) {
    ParticleDescriptor *descriptor;
    Particle *particle;
    ParticleModel *model;
    ParticleBehaviour *behaviour;
    ColorLoopEntry *colourLoop;

    descriptor = gParticlesAssetTable[emitter->descriptorID];
    if (descriptor->kind != PARTICLE_KIND_LINE) {
        return NULL;
    }
    behaviour = emitter->behaviour;
    colourLoop = behaviour->colourLoop;
    particle = particle_allocate(PARTICLE_KIND_LINE);
    if (particle == NULL) {
        return NULL;
    }
    particle->segmentID = obj->segment.object.segmentID;
    particle->trans.flags = OBJ_FLAGS_PARTICLE;
    particle->movementType = descriptor->movementType;
    particle->descFlags = descriptor->flags;
    particle->parentObj = obj;
    particle->lineEmitter = emitter;
    particle->trans.scale = descriptor->scale * behaviour->scale;
    particle->scaleVelocity = descriptor->scale * behaviour->scaleVelocity;
    particle->destroyTimer = descriptor->lifeTime;

    particle->unk34 = 0.0f;
    particle->unk38 = 0;

    if (gParticleOverrideColor->word != 0) {
        particle->colour.word = gParticleOverrideColor->word;
    } else {
        particle->colour.r = descriptor->colour.r;
        particle->colour.g = descriptor->colour.g;
        particle->colour.b = descriptor->colour.b;
    }
    particle->colour.a = descriptor->colour.a;

    if (particle->descFlags & PARTICLE_SHADED && obj->shading != NULL) {
        particle->brightness = obj->shading->unk0 * 255.0f;
    } else {
        particle->brightness = 255;
    }

    particle->opacityTimer = descriptor->opacityTimer;
    particle->opacity = descriptor->opacity << 8;
    if (descriptor->opacity < 255) {
        if (particle->descFlags & PARTICLE_DESC_FLAG_1000) {
            particle->trans.flags |= OBJ_FLAGS_UNK_0100;
        } else {
            particle->trans.flags |= OBJ_FLAGS_UNK_0080;
        }
    }
    if (particle->opacityTimer < particle->destroyTimer) {
        particle->opacityVel =
            (((descriptor->opacityVel - descriptor->opacity) << 8) / (particle->destroyTimer - particle->opacityTimer));
    } else {
        particle->opacityVel = 0;
    }

    emitter->lineRefPoint.x = emitter->position.x;
    emitter->lineRefPoint.y = emitter->position.y;
    emitter->lineRefPoint.z = emitter->position.z;
    vec3f_rotate(&obj->segment.trans.rotation, &emitter->lineRefPoint);
    emitter->lineRefPoint.x += obj->segment.trans.x_position;
    emitter->lineRefPoint.y += obj->segment.trans.y_position;
    emitter->lineRefPoint.z += obj->segment.trans.z_position;

    particle->lineCreationPhase = 0;
    particle->lineOrientation = 0;
    particle->line_unused_6B = -1;

    particle->textureFrameStep = descriptor->textureFrameStep;
    particle->textureFrame = 0;

    model = particle->model;
    if (descriptor->textureID == -1) {
        model->texture = NULL;
    } else {
        model->texture = load_texture(descriptor->textureID);
        if (model->texture != NULL) {
            if (model->texture->flags & 4) {
                if (particle->descFlags & PARTICLE_DESC_FLAG_1000) {
                    particle->trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    particle->trans.flags |= OBJ_FLAGS_UNK_0080;
                }
            }
            if ((particle->descFlags &
                 (PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED)) ==
                PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED) {
                particle->textureFrame = model->texture->numOfTextures - 1;
            }
        }
    }
    model->vertices[0].x = emitter->lineRefPoint.x;
    model->vertices[0].y = emitter->lineRefPoint.y;
    model->vertices[0].z = emitter->lineRefPoint.z;

    if ((u32) colourLoop != -1U) {
        emitter->colourIndex++;
        if (emitter->colourIndex >= colourLoop[0].numEntries) {
            emitter->colourIndex = 0;
        }
        model->vertices[0].r = colourLoop[emitter->colourIndex + 2].r;
        model->vertices[0].g = colourLoop[emitter->colourIndex + 2].g;
        model->vertices[0].b = colourLoop[emitter->colourIndex + 2].b;
        model->vertices[0].a = emitter->lineOpacity;
    } else {
        model->vertices[0].r = particle->colour.r;
        model->vertices[0].g = particle->colour.g;
        model->vertices[0].b = particle->colour.b;
        model->vertices[0].a = emitter->lineOpacity;
    }
    particle->lineOrientation = descriptor->lineOrientation;
    particle->line_unused_6B = descriptor->line_unused_B;
    particle->trans.x_position = obj->segment.trans.x_position;
    particle->trans.y_position = obj->segment.trans.y_position;
    particle->trans.z_position = obj->segment.trans.z_position;
    emitter->line_unused = 0;
    return particle;
}

/**
 * Creates a triangle, rectangle, or sprite particle and initializes its fields.
 */
Particle *create_general_particle(Object *obj, ParticleEmitter *emitter) {
    s32 randomizationFlags;
    ParticleDescriptor *descriptor;
    Particle *particle;
    TextureHeader **texture;
    ParticleBehaviour *behaviour;
    ColorLoopEntry *colourLoop;
    f32 scale;
    s8 noTexture;

    descriptor = gParticlesAssetTable[emitter->descriptorID];
    if (descriptor->kind == PARTICLE_KIND_LINE || descriptor->kind == PARTICLE_KIND_POINT) {
        return NULL;
    }

    behaviour = emitter->behaviour;
    colourLoop = behaviour->colourLoop;

    particle = particle_allocate(descriptor->kind);
    if (particle == NULL) {
        return particle;
    }
    particle->segmentID = obj->segment.object.segmentID;
    particle->trans.flags = OBJ_FLAGS_PARTICLE;
    particle->movementType = descriptor->movementType;
    particle->descFlags = descriptor->flags;
    particle->parentObj = obj;
    if ((particle->descFlags & PARTICLE_SHADED) && obj->shading != NULL) {
        particle->brightness = obj->shading->unk0 * 255.0f;
    } else {
        particle->brightness = 255;
    }

    scale = behaviour->scale;
    if (behaviour->randomizationFlags & PARTICLE_RANDOM_SCALE) {
        scale += (f32) rand_range(-behaviour->scaleRange, behaviour->scaleRange) * 0.00001525878906;
    }
    particle->trans.scale = descriptor->scale * scale;

    scale = behaviour->scaleVelocity;
    if (behaviour->randomizationFlags & PARTICLE_RANDOM_SCALE_VELOCITY) {
        scale += (f32) rand_range(-behaviour->scaleVelocityRange, behaviour->scaleVelocityRange) * 0.00001525878906;
    }
    if (behaviour->flags & PARTICLE_SCALE_VELOCITY_INHERITS_PARENT_SPEED) {
        particle->scaleVelocity = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                                        (obj->segment.y_velocity * obj->segment.y_velocity) +
                                        (obj->segment.z_velocity * obj->segment.z_velocity)) *
                                  scale * 0.1f;
    } else {
        particle->scaleVelocity = descriptor->scale * scale;
    }

    particle->destroyTimer = rand_range(-descriptor->lifeTimeRange, descriptor->lifeTimeRange) + descriptor->lifeTime;

    particle->unk38 = 0;
    particle->unk34 = 0.0f;

    if (gParticleOverrideColor[0].word != 0) {
        particle->colour.word = gParticleOverrideColor[0].word;
    } else if ((s32) colourLoop != -1) {
        emitter->colourIndex++;
        if (emitter->colourIndex >= colourLoop->numEntries) {
            emitter->colourIndex = 0;
        }
        particle->colour.r = colourLoop[emitter->colourIndex + 2].r;
        particle->colour.g = colourLoop[emitter->colourIndex + 2].g;
        particle->colour.b = colourLoop[emitter->colourIndex + 2].b;
        particle->colour.a = colourLoop[emitter->colourIndex + 2].a;
    } else {
        particle->colour.r = descriptor->colour.r;
        particle->colour.g = descriptor->colour.g;
        particle->colour.b = descriptor->colour.b;
        particle->colour.a = descriptor->colour.a;
    }
    randomizationFlags = behaviour->randomizationFlags & (PARTICLE_RANDOM_COLOUR_ALPHA | PARTICLE_RANDOM_COLOUR_BLUE |
                                                          PARTICLE_RANDOM_COLOUR_GREEN | PARTICLE_RANDOM_COLOUR_RED);
    if (randomizationFlags) {
        if (randomizationFlags & PARTICLE_RANDOM_COLOUR_RED) {
            particle->colour.r += rand_range(-behaviour->colourRangeR, behaviour->colourRangeR);
        }
        if (randomizationFlags & PARTICLE_RANDOM_COLOUR_GREEN) {
            particle->colour.g += rand_range(-behaviour->colourRangeG, behaviour->colourRangeG);
        }
        if (randomizationFlags & PARTICLE_RANDOM_COLOUR_BLUE) {
            particle->colour.b += rand_range(-behaviour->colourRangeB, behaviour->colourRangeB);
        }
        if (randomizationFlags & PARTICLE_RANDOM_COLOUR_ALPHA) {
            particle->colour.a += rand_range(-behaviour->colourRangeA, behaviour->colourRangeA);
        }
    }

    particle->opacityTimer = descriptor->opacityTimer;
    particle->opacity = descriptor->opacity * gCurrentHovercraftParticleOpacity;
    if (descriptor->opacity < 255) {
        if (particle->descFlags & PARTICLE_DESC_FLAG_1000) {
            particle->trans.flags |= OBJ_FLAGS_UNK_0100;
        } else {
            particle->trans.flags |= OBJ_FLAGS_UNK_0080;
        }
    }
    if (particle->opacityTimer < particle->destroyTimer) {
        particle->opacityVel = (descriptor->opacityVel - descriptor->opacity) * gCurrentHovercraftParticleOpacity /
                               (particle->destroyTimer - particle->opacityTimer);
    } else {
        particle->opacityVel = 0;
    }

    noTexture = FALSE;
    particle->textureFrameStep = descriptor->textureFrameStep;
    if (particle->kind == PARTICLE_KIND_SPRITE) {
        particle->sprite = (Sprite *) tex_load_sprite(descriptor->textureID, 0);
        if (particle->sprite != NULL) {
            if (particle->sprite->frames[0]->flags & 4) {
                if (particle->descFlags & PARTICLE_DESC_FLAG_1000) {
                    particle->trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    particle->trans.flags |= OBJ_FLAGS_UNK_0080;
                }
            }
            if (behaviour->flags & PARTICLE_RANDOM_TEXTURE_FRAME) {
                particle->textureFrame = rand_range(0, particle->sprite->baseTextureId - 1) << 8;
                if ((particle->descFlags &
                     (PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED)) ==
                    PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED) {
                    particle->textureFrame |= 0xFF;
                }
            } else if ((particle->descFlags &
                        (PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED)) ==
                       PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED) {
                particle->textureFrame = (particle->sprite->baseTextureId << 8) - 1;
            } else {
                particle->textureFrame = 0;
            }
        } else {
            noTexture = TRUE;
        }
    } else if (particle->kind == PARTICLE_KIND_RECTANGLE || particle->kind == PARTICLE_KIND_TRIANGLE) {
        texture = &particle->model->texture;
        if (texture) {
            *texture = load_texture(descriptor->textureID);
            if (*texture != NULL) {
                if ((*texture)->flags & 4) {
                    if (particle->descFlags & PARTICLE_DESC_FLAG_1000) {
                        particle->trans.flags |= OBJ_FLAGS_UNK_0100;
                    } else {
                        particle->trans.flags |= OBJ_FLAGS_UNK_0080;
                    }
                }
                if (behaviour->flags & PARTICLE_RANDOM_TEXTURE_FRAME) {
                    particle->textureFrame = rand_range(0, ((*texture)->numOfTextures >> 8) - 1) << 8;
                    if ((particle->descFlags &
                         (PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED)) ==
                        PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED) {
                        particle->textureFrame |= 0xFF;
                    }
                } else if ((particle->descFlags &
                            (PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED)) ==
                           PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED) {
                    particle->textureFrame = (*texture)->numOfTextures - 1;
                } else {
                    particle->textureFrame = 0;
                }
            } else {
                noTexture = TRUE;
            }
        }
    }
    if (!noTexture) {
        if (particle->kind == PARTICLE_KIND_TRIANGLE) {
            set_triangle_texture_coords(particle);
        }
        if (particle->kind == PARTICLE_KIND_RECTANGLE) {
            set_rectangle_texture_coords(particle);
        }
    }

    setup_particle_position(particle, obj, emitter, behaviour);

    // Setup particle rotation
    if (behaviour->flags & PARTICLE_ROTATION_ABSOLUTE) {
        particle->trans.rotation.y_rotation = behaviour->rotation.y_rotation;
        particle->trans.rotation.x_rotation = behaviour->rotation.x_rotation;
        particle->trans.rotation.z_rotation = behaviour->rotation.z_rotation;
    } else {
        particle->trans.rotation.y_rotation = obj->segment.trans.rotation.y_rotation + behaviour->rotation.y_rotation;
        particle->trans.rotation.x_rotation = obj->segment.trans.rotation.x_rotation + behaviour->rotation.x_rotation;
        particle->trans.rotation.z_rotation = obj->segment.trans.rotation.z_rotation + behaviour->rotation.z_rotation;
    }
    randomizationFlags =
        behaviour->randomizationFlags & (PARTICLE_RANDOM_ROLL | PARTICLE_RANDOM_PITCH | PARTICLE_RANDOM_YAW);
    if (randomizationFlags != 0) {
        if (randomizationFlags & PARTICLE_RANDOM_YAW) {
            particle->trans.rotation.y_rotation +=
                rand_range(-behaviour->rotationRange.y_rotation, behaviour->rotationRange.y_rotation);
        }
        if (randomizationFlags & PARTICLE_RANDOM_PITCH) {
            particle->trans.rotation.x_rotation +=
                rand_range(-behaviour->rotationRange.x_rotation, behaviour->rotationRange.x_rotation);
        }
        if (randomizationFlags & PARTICLE_RANDOM_ROLL) {
            particle->trans.rotation.z_rotation +=
                rand_range(-behaviour->rotationRange.z_rotation, behaviour->rotationRange.z_rotation);
        }
    }

    particle->angularVelocity.y_rotation = behaviour->angularVelocity.y_rotation;
    particle->angularVelocity.x_rotation = behaviour->angularVelocity.x_rotation;
    particle->angularVelocity.z_rotation = behaviour->angularVelocity.z_rotation;
    randomizationFlags =
        behaviour->randomizationFlags &
        (PARTCILE_RANDOM_ROLL_VELOCITY | PARTCILE_RANDOM_PITCH_VELOCITY | PARTCILE_RANDOM_YAW_VELOCITY);
    if (randomizationFlags) {
        if (randomizationFlags & PARTCILE_RANDOM_YAW_VELOCITY) {
            particle->angularVelocity.y_rotation +=
                rand_range(-behaviour->angularVelocityRange.y_rotation, behaviour->angularVelocityRange.y_rotation);
        }
        if (randomizationFlags & PARTCILE_RANDOM_PITCH_VELOCITY) {
            particle->angularVelocity.x_rotation +=
                rand_range(-behaviour->angularVelocityRange.x_rotation, behaviour->angularVelocityRange.x_rotation);
        }
        if (randomizationFlags & PARTCILE_RANDOM_ROLL_VELOCITY) {
            particle->angularVelocity.z_rotation +=
                rand_range(-behaviour->angularVelocityRange.z_rotation, behaviour->angularVelocityRange.z_rotation);
        }
    }

    setup_particle_velocity(particle, obj, emitter, behaviour);

    particle->gravity = gParticleGravityTable[(particle->descFlags >> 4) & 7];
    if (particle->movementType == PARTICLE_MOVEMENT_FORWARD) {
        particle->forwardVel =
            sqrtf((particle->velocity.x * particle->velocity.x) + (particle->velocity.y * particle->velocity.y) +
                  (particle->velocity.z * particle->velocity.z));
    }

    if (behaviour->flags & PARTICLE_SOURCE_ROTATION_ENABLED) {
        emitter->sourceRotationCounter++;
        if (emitter->sourceRotationCounter >= behaviour->maxParticlesFromSamePos) {
            emitter->sourceRotation.y_rotation += behaviour->sourceAngularVelocity.y_rotation;
            emitter->sourceRotation.x_rotation += behaviour->sourceAngularVelocity.x_rotation;
            emitter->sourceRotation.z_rotation += behaviour->sourceRotation.z_rotation; //!@bug wrong field used
            emitter->sourceRotationCounter -= behaviour->maxParticlesFromSamePos;
        }
    }
    if (behaviour->flags & PARTICLE_ROTATING_DIRECTION) {
        emitter->emissionDirRotationCounter++;
        if (emitter->emissionDirRotationCounter >= behaviour->maxParticlesInSameDir) {
            emitter->emissionDirection.y_rotation += behaviour->emissionDirAngularVelocity.y_rotation;
            emitter->emissionDirection.x_rotation += behaviour->emissionDirAngularVelocity.x_rotation;
            emitter->emissionDirection.z_rotation += behaviour->emissionDirAngularVelocity.z_rotation;
            emitter->emissionDirRotationCounter -= behaviour->maxParticlesInSameDir;
        }
    }

    if (particle->model == NULL) {
        particle_deallocate(particle);
        return NULL;
    } else {
        return particle;
    }
}

/**
 * Allocates a particle of the given kind from the buffer.
 * Returns NULL if the buffer is full.
 */
Particle *particle_allocate(s32 kind) {
    s32 i;
    Particle *particle;

    particle = NULL;
    i = 0;

    switch (kind) {
        case PARTICLE_KIND_SPRITE:
            if ((gSpriteParticleBuffer != NULL)) {
                if (gNumSpriteParticles >= gMaxSpriteParticles - 1) {
                    if (!gSpriteParticleBufferFull) {
                        gSpriteParticleBufferFull = TRUE;
                    }
                } else {
                    while (gSpriteParticleBuffer[i].kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gSpriteParticleBuffer[i].kind = PARTICLE_KIND_SPRITE;
                    gNumSpriteParticles++;
                    particle = &gSpriteParticleBuffer[i];
                }
            }
            break;
        case PARTICLE_KIND_TRIANGLE:
            if (gTriangleParticleBuffer != NULL) {
                if (gNumTriangleParticles >= gMaxTriangleParticles - 1) {
                    if (!gTriangleParticleBufferFull) {
                        gTriangleParticleBufferFull = TRUE;
                    }
                } else {
                    while (gTriangleParticleBuffer[i].kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gTriangleParticleBuffer[i].kind = PARTICLE_KIND_TRIANGLE;
                    gNumTriangleParticles++;
                    particle = &gTriangleParticleBuffer[i];
                }
            }
            break;
        case PARTICLE_KIND_RECTANGLE:
            if (gRectangleParticleBuffer != NULL) {
                if (gNumRectangleParticles >= gMaxRectangleParticles - 1) {
                    if (!gRectangleParticleBufferFull) {
                        gRectangleParticleBufferFull = TRUE;
                    }
                } else {
                    while (gRectangleParticleBuffer[i].kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gRectangleParticleBuffer[i].kind = PARTICLE_KIND_RECTANGLE;
                    gNumRectangleParticles++;
                    particle = &gRectangleParticleBuffer[i];
                }
            }
            break;
        case PARTICLE_KIND_LINE:
            if (gLineParticleBuffer != NULL) {
                if (gNumLineParticles >= gMaxLineParticles - 1) {
                    if (!gLineParticleBufferFull) {
                        gLineParticleBufferFull = TRUE;
                    }
                } else {
                    while (gLineParticleBuffer[i].kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gLineParticleBuffer[i].kind = PARTICLE_KIND_LINE;
                    gNumLineParticles++;
                    particle = &gLineParticleBuffer[i];
                }
            }
            break;
        case PARTICLE_KIND_POINT:
            if (gPointParticleBuffer != NULL) {
                if (gNumPointParticles >= gMaxPointParticles - 1) {
                    if (!gPointParticleBufferFull) {
                        gPointParticleBufferFull = TRUE;
                    }
                } else {
                    while (gPointParticleBuffer[i].base.kind != PARTICLE_KIND_NONE) {
                        i++;
                    }
                    gPointParticleBuffer[i].base.kind = PARTICLE_KIND_POINT;
                    gNumPointParticles++;
                    particle = &gPointParticleBuffer[i].base;
                }
            }
            break;
    }
    if (particle != NULL) {
        particle->unk_48 = -1;
    }
    return particle;
}

/**
 * Deallocates the specified particle and frees its associated resources.
 */
void particle_deallocate(Particle *particle) {
    TextureHeader *tex;

    switch (particle->kind) {
        case PARTICLE_KIND_NONE:
            break;
        case PARTICLE_KIND_SPRITE:
            if (gNumSpriteParticles > 0) {
                if (particle->model) {
                    sprite_free((Sprite *) particle->sprite);
                }
                gNumSpriteParticles--;
                particle->kind = PARTICLE_KIND_NONE;
            }
            break;
        case PARTICLE_KIND_TRIANGLE:
            if (gNumTriangleParticles > 0) {
                tex = particle->model->texture;
                if (tex != NULL) {
                    tex_free(tex);
                }
                gNumTriangleParticles--;
                particle->kind = PARTICLE_KIND_NONE;
            }
            break;
        case PARTICLE_KIND_RECTANGLE:
            if (gNumRectangleParticles > 0) {
                tex = particle->model->texture;
                if (tex != NULL) {
                    tex_free(tex);
                }
                gNumRectangleParticles--;
                particle->kind = PARTICLE_KIND_NONE;
            }
            break;
        case PARTICLE_KIND_LINE:
            if (gNumLineParticles > 0) {
                tex = particle->model->texture;
                if (tex != NULL) {
                    tex_free(tex);
                }
                gNumLineParticles--;
                particle->kind = PARTICLE_KIND_NONE;
            }
            break;
        case PARTICLE_KIND_POINT:
            if (gNumPointParticles > 0) {
                delete_point_particle_from_sequence((PointParticle *) particle);
                tex = particle->model->texture;
                if (tex != NULL) {
                    tex_free(tex);
                }
                gNumPointParticles--;
                particle->kind = PARTICLE_KIND_NONE;
            }
            break;
    }
}

/**
 * Frees all memory associated with the emitter.
 */
void emitter_cleanup(ParticleEmitter *emitter) {
    PointParticle *pointParticle;
    s32 i;

    if (emitter->flags & PARTICLE_POINT) {
        if (emitter->refPoints != NULL) {
            for (i = 0; i < emitter->pointCount; i++) {
                pointParticle = emitter->refPoints[i];
                pointParticle->base.destroyTimer = 0;
                pointParticle->pointEmitter = NULL;
            }
            mempool_free(emitter->refPoints);
            emitter->refPoints = NULL;
        }
    }
}

/**
 * Call a function to update the current particle texture frame if applicable.
 * Applies movement, gets block ID and then shifts the opacity.
 */
void particle_update(Particle *particle, s32 updateRate) {
    LevelModelSegmentBoundingBox *boundingBox;
    PointParticle *pointParticle;

    gParticleUpdateRate = updateRate;
    pointParticle = NULL;
    if (particle->kind == PARTICLE_KIND_LINE) {
        update_line_particle(particle);
        return;
    }

    if (particle->descFlags & (PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED)) {
        if (gParticleUpdateRate > 0) {
            update_particle_texture_frame(particle);
        }
    }
    if (particle->kind == PARTICLE_KIND_POINT) {
        pointParticle = (PointParticle *) particle;
        pointParticle->modelFrame = 1 - pointParticle->modelFrame;
        pointParticle->meshRegenerated = 0;
    }
    if (pointParticle == NULL || (pointParticle != NULL && pointParticle->pointEmitter != NULL)) {
        if (particle->movementType == PARTICLE_MOVEMENT_ACCELERATION) {
            move_particle_with_acceleration(particle);
        } else if (particle->movementType == PARTICLE_MOVEMENT_ATTACHED_TO_PARENT) {
            move_particle_attached_to_parent(particle);
        } else if (particle->movementType == PARTICLE_MOVEMENT_BASIC_PARENT) {
            move_particle_basic_parent(particle);
        } else if (particle->movementType == PARTICLE_MOVEMENT_FORWARD) {
            move_particle_forward(particle);
        } else {
            // PARTICLE_MOVEMENT_BASIC
            move_particle_basic(particle);
        }
    }

    boundingBox = get_segment_bounding_box(particle->segmentID);
    if (boundingBox != NULL) {
        if (particle->trans.x_position < boundingBox->x1 || boundingBox->x2 < particle->trans.x_position ||
            particle->trans.y_position < boundingBox->y1 || boundingBox->y2 < particle->trans.y_position ||
            particle->trans.z_position < boundingBox->z1 || boundingBox->z2 < particle->trans.z_position) {
            particle->segmentID = get_level_segment_index_from_position(
                particle->trans.x_position, particle->trans.y_position, particle->trans.z_position);
        }
    } else {
        particle->segmentID = get_level_segment_index_from_position(
            particle->trans.x_position, particle->trans.y_position, particle->trans.z_position);
    }

    particle->destroyTimer -= gParticleUpdateRate;
    if (particle->destroyTimer <= 0) {
        free_object((Object *) particle);
        return;
    }
    if (particle->opacityTimer == 0) {
        particle->opacity += gParticleUpdateRate * particle->opacityVel;
        if (particle->opacity < 255) {
            if (particle->descFlags & PARTICLE_DESC_FLAG_1000) {
                particle->trans.flags |= OBJ_FLAGS_UNK_0100;
            } else {
                particle->trans.flags |= OBJ_FLAGS_UNK_0080;
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

/**
 * Removes a point particle from the array managed by its parent emitter.
 */
void delete_point_particle_from_sequence(PointParticle *particle) {
    ParticleEmitter *new_var;
    PointParticle *new_var2;
    ParticleEmitter *emitter;
    s32 i;

    emitter = particle->pointEmitter;
    if (emitter != NULL) {
        new_var = emitter;
        if (emitter->pointCount != 0) {
            if (particle == emitter->refPoints[particle->pointIndex]) {
                emitter->pointCount--;
                for (i = particle->pointIndex; i < emitter->pointCount; i++) {
                    new_var->refPoints[i] = new_var->refPoints[i + 1];
                    new_var2 = new_var->refPoints[i];
                    new_var2->pointIndex = i;
                }
            }
        }
    }
}

/**
 * Line particles have their own update function because they behave differently from other particle types.
 * Instead of moving, they generate their mesh in three steps and remain stationary until their lifetime ends.
 */
void update_line_particle(Particle *particle) {
    Vec3f vtxOffset;
    f32 tempf;
    f32 scale;
    ParticleModel *model;
    Object *obj;
    ParticleEmitter *emitter;
    ColorLoopEntry *colourLoop;
    ColorLoopEntry **colourLoopPtr;

    obj = particle->parentObj;
    model = NULL;
    colourLoopPtr = &colourLoop;

    if (obj != NULL) {
        emitter = particle->lineEmitter;
        colourLoop = emitter->behaviour->colourLoop;
        model = particle->model;
    }

    /*
        This is a description of how it works.

        In the first step, only vertex 0 exists and nothing is rendered.

        In the second step, the vehicle (and therefore the emitter) moves some distance,
        and three more vertices are added: one at the current emitter position, and two others
        to the sides of it (depending on orientation).

        In the third step, the emitter moves further and two more side vertices are added.

        Eventually, all vertices form a chevron shape, so when multiple particles from the same
        emitter are spawned, they merge into one continuous line.
    */

    if (particle->lineCreationPhase < 2 && obj != NULL) {

        if (emitter->behaviour->flags & PARTICLE_SCALE_VELOCITY_INHERITS_PARENT_SPEED) {
            scale = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                          (obj->segment.y_velocity * obj->segment.y_velocity) +
                          (obj->segment.z_velocity * obj->segment.z_velocity));
            scale = scale * particle->trans.scale * 0.1f;
        } else {
            scale = particle->trans.scale;
        }
        if (!(particle->descFlags & PARTICLE_LINE_ALONG_VELOCITY)) {
            vtxOffset.x = 0.0f;
            vtxOffset.y = 0.0f;
            vtxOffset.z = 0.0f;
            switch (particle->lineOrientation) {
                default:
                    vtxOffset.x = scale;
                    break;
                case 2:
                    vtxOffset.z = scale;
                    break;
                case 1:
                    vtxOffset.y = scale;
                    break;
            }
            vec3f_rotate(&obj->segment.trans.rotation, &vtxOffset);
        } else {
            vtxOffset.x = obj->segment.x_velocity;
            vtxOffset.y = obj->segment.y_velocity;
            vtxOffset.z = obj->segment.z_velocity;
            tempf = ((vtxOffset.x * vtxOffset.x) + (vtxOffset.y * vtxOffset.y)) + (vtxOffset.z * vtxOffset.f[2]);
            if (tempf < 0.01f) {
                tempf = 1.0f;
            } else {
                tempf = scale / sqrtf(tempf);
            }
            vtxOffset.x *= tempf;
            vtxOffset.y *= tempf;
            vtxOffset.z *= tempf;
            switch (particle->lineOrientation) {
                case 0:
                    tempf = vtxOffset.x;
                    vtxOffset.x = -vtxOffset.z;
                    vtxOffset.z = tempf;
                    break;
                case 1:
                    tempf = vtxOffset.y;
                    vtxOffset.y = -vtxOffset.z;
                    vtxOffset.z = tempf;
                    break;
            }
        }
        if (model != NULL && particle->lineCreationPhase == 0) {
            // Phase 2: add three more vertices

            model->vertices[1].x = vtxOffset.f[0] + emitter->lineRefPoint.x;
            model->vertices[1].y = vtxOffset.f[1] + emitter->lineRefPoint.y;
            model->vertices[1].z = vtxOffset.f[2] + emitter->lineRefPoint.z;
            model->vertices[1].r = model->vertices->r;
            model->vertices[1].g = model->vertices->g;
            model->vertices[1].b = model->vertices->b;
            model->vertices[1].a = emitter->lineOpacity;

            model->vertices[2].x = emitter->lineRefPoint.x;
            model->vertices[2].y = emitter->lineRefPoint.y;
            model->vertices[2].z = emitter->lineRefPoint.z;
            if ((s32) *colourLoopPtr != -1) {
                model->vertices[2].r = (*colourLoopPtr)[emitter->colourIndex + 2].r;
                model->vertices[2].g = (*colourLoopPtr)[emitter->colourIndex + 2].g;
                model->vertices[2].b = (*colourLoopPtr)[emitter->colourIndex + 2].b;
                model->vertices[2].a = emitter->lineOpacity;
            } else {
                model->vertices[2].r = particle->colour.r;
                model->vertices[2].g = particle->colour.g;
                model->vertices[2].b = particle->colour.b;
                model->vertices[2].a = emitter->lineOpacity;
            }
            model->vertices[3].x = emitter->lineRefPoint.x - vtxOffset.f[0];
            model->vertices[3].y = emitter->lineRefPoint.y - vtxOffset.f[1];
            model->vertices[3].z = emitter->lineRefPoint.z - vtxOffset.f[2];
            model->vertices[3].r = model->vertices->r;
            model->vertices[3].g = model->vertices->g;
            model->vertices[3].b = model->vertices->b;
            model->vertices[3].a = emitter->lineOpacity;
            particle->lineCreationPhase = 1;
        } else if (model != NULL) {
            // Phase 3: add two more vertices

            model->vertices[4].x = vtxOffset.f[0] + emitter->lineRefPoint.x;
            model->vertices[4].y = vtxOffset.f[1] + emitter->lineRefPoint.y;
            model->vertices[4].z = vtxOffset.f[2] + emitter->lineRefPoint.z;
            model->vertices[4].r = model->vertices[2].r;
            model->vertices[4].g = model->vertices[2].g;
            model->vertices[4].b = model->vertices[2].b;
            model->vertices[4].a = emitter->lineOpacity;

            model->vertices[5].x = emitter->lineRefPoint.x - vtxOffset.f[0];
            model->vertices[5].y = emitter->lineRefPoint.y - vtxOffset.f[1];
            model->vertices[5].z = emitter->lineRefPoint.z - vtxOffset.f[2];
            model->vertices[5].r = model->vertices[2].r;
            model->vertices[5].g = model->vertices[2].g;
            model->vertices[5].b = model->vertices[2].b;
            model->vertices[5].a = emitter->lineOpacity;
            particle->lineCreationPhase = 2;
        }
    } else {
        particle->destroyTimer -= gParticleUpdateRate;
        if (particle->destroyTimer <= 0) {
            free_object((Object *) particle);
        } else if (particle->opacityTimer == 0) {
            particle->opacity += gParticleUpdateRate * particle->opacityVel;
            if (particle->opacity < 255) {
                if (particle->descFlags & PARTICLE_DESC_FLAG_1000) {
                    particle->trans.flags |= OBJ_FLAGS_UNK_0100;
                } else {
                    particle->trans.flags |= OBJ_FLAGS_UNK_0080;
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
    if (model != NULL && model->texture != NULL &&
        (particle->descFlags & (PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED)) &&
        gParticleUpdateRate > 0) {
        update_particle_texture_frame(particle);
    }
}

/**
 * Updates the current animation frame based on the animation flags.
 */
void update_particle_texture_frame(Particle *particle) {
    s32 currentlyBackward;
    s32 keepGoing;
    s32 i;
    s32 textureCount;
    s32 backwardEnabled;
    s32 isLooped;
    s32 forwardEnabled;

    keepGoing = -1;
    i = 0; // required to match
    textureCount = particle->kind == PARTICLE_KIND_SPRITE ? particle->sprite->baseTextureId * 256
                                                          : particle->model->texture->numOfTextures;

    forwardEnabled = particle->descFlags & PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED;
    backwardEnabled = particle->descFlags & PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED;
    isLooped = particle->descFlags & PARTICLE_TEXTURE_ANIM_LOOP;
    currentlyBackward = particle->descFlags & PARTICLE_CURRENT_ANIMATION_BACKWARD;

    for (i = 0; (i++ < gParticleUpdateRate) && keepGoing;) {
        if (!currentlyBackward) {
            particle->textureFrame += particle->textureFrameStep;
            if (particle->textureFrame >= textureCount) {
                if (backwardEnabled) {
                    //!@bug the last frame is displayed twice
                    particle->textureFrame = 2 * textureCount - 1 - particle->textureFrame;
                    currentlyBackward = TRUE;
                    particle->descFlags |= PARTICLE_CURRENT_ANIMATION_BACKWARD;
                } else if (isLooped) {
                    particle->textureFrame -= textureCount;
                } else {
                    particle->textureFrame = textureCount - 1;
                    keepGoing = FALSE;
                    particle->descFlags &=
                        ~(PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED);
                }
            }
        } else {
            particle->textureFrame -= particle->textureFrameStep;
            if (particle->textureFrame < 0) {
                if (isLooped) {
                    if (forwardEnabled) {
                        particle->textureFrame = -particle->textureFrame;
                        currentlyBackward = FALSE;
                        particle->descFlags &= ~PARTICLE_CURRENT_ANIMATION_BACKWARD;
                    } else {
                        particle->textureFrame += textureCount;
                    }
                } else {
                    particle->textureFrame = 0;
                    keepGoing = FALSE;
                    particle->descFlags &=
                        ~(PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED | PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED);
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
    Object *parent;

    i = gParticleUpdateRate;
    while (i-- > 0) {
        particle->localPos.x += particle->velocity.x;
        particle->localPos.y += particle->velocity.y;
        particle->velocity.y -= particle->gravity;
        particle->localPos.z += particle->velocity.z;
        particle->trans.rotation.y_rotation += particle->angularVelocity.y_rotation;
        particle->trans.rotation.x_rotation += particle->angularVelocity.x_rotation;
        particle->trans.rotation.z_rotation += particle->angularVelocity.z_rotation;
        particle->trans.scale += particle->scaleVelocity;
    }
    particle->trans.x_position = particle->localPos.x;
    particle->trans.y_position = particle->localPos.y;
    particle->trans.z_position = particle->localPos.z;
    parent = particle->parentObj;
    if (parent) {
        particle->trans.x_position += parent->segment.trans.x_position;
        particle->trans.y_position += parent->segment.trans.y_position;
        particle->trans.z_position += parent->segment.trans.z_position;
    }
}

/**
 * Applies rotation and scale based on the particle's velocities.
 * Translates the particle downward in the object's local coordinate system by downOffset.
 * Applies additional translation based on the parent's position.
 */
void move_particle_attached_to_parent(Particle *particle) {
    s32 i = gParticleUpdateRate;
    Object *parent;

    while (i-- > 0) {
        particle->trans.rotation.y_rotation += particle->angularVelocity.y_rotation;
        particle->trans.rotation.x_rotation += particle->angularVelocity.x_rotation;
        particle->trans.rotation.z_rotation += particle->angularVelocity.z_rotation;
        particle->trans.scale += particle->scaleVelocity;
    }

    particle->trans.x_position = 0.0f;
    particle->trans.y_position = -particle->downOffset;
    particle->trans.z_position = 0.0f;
    vec3f_rotate(&particle->trans.rotation, (Vec3f *) &particle->trans.x_position);
    particle->trans.x_position += particle->localPos.x;
    particle->trans.y_position += particle->localPos.y;
    particle->trans.z_position += particle->localPos.z;

    parent = particle->parentObj;
    if (parent != NULL) {
        particle->trans.x_position += parent->segment.trans.x_position;
        particle->trans.y_position += parent->segment.trans.y_position;
        particle->trans.z_position += parent->segment.trans.z_position;
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
        particle->trans.x_position += particle->velocity.x;
        particle->trans.y_position += particle->velocity.y;
        particle->trans.z_position += particle->velocity.z;
        particle->trans.scale += particle->scaleVelocity;
        particle->trans.rotation.y_rotation += particle->angularVelocity.y_rotation;
        particle->trans.rotation.x_rotation += particle->angularVelocity.x_rotation;
        particle->trans.rotation.z_rotation += particle->angularVelocity.z_rotation;

        acceleration.x = 0.0f;
        acceleration.y = -particle->downAcceleration;
        acceleration.z = 0.0f;
        vec3f_rotate(&particle->trans.rotation, &acceleration);
        particle->velocity.x += acceleration.x;
        particle->velocity.y += acceleration.y;
        particle->velocity.y -= particle->gravity;
        particle->velocity.z += acceleration.z;
    }
}

/**
 * Apply translation, rotation and scale based off the velocities of the particle.
 */
void move_particle_basic(Particle *particle) {
    s32 i = 0;

    while (i++ < gParticleUpdateRate) {
        particle->trans.x_position += particle->velocity.x;
        particle->trans.y_position += particle->velocity.y;
        particle->velocity.y -= particle->gravity;
        particle->trans.z_position += particle->velocity.z;
        particle->trans.scale += particle->scaleVelocity;
        particle->trans.rotation.y_rotation += particle->angularVelocity.y_rotation;
        particle->trans.rotation.x_rotation += particle->angularVelocity.x_rotation;
        particle->trans.rotation.z_rotation += particle->angularVelocity.z_rotation;
    }
}

/**
 * Apply translation, rotation and scale based off the velocities of the particle.
 * Velocity is set from forward velocity.
 * The particle always moves forward in the local coordinate system
 */
void move_particle_forward(Particle *particle) {
    s32 i = 0;

    while (i++ < gParticleUpdateRate) {
        particle->velocity.x = 0.0f;
        particle->velocity.y = 0.0f;
        particle->velocity.z = -particle->forwardVel;
        vec3f_rotate_py(&particle->trans.rotation, &particle->velocity);
        particle->trans.x_position += particle->velocity.x;
        // Gravity is subtracted here, but velocity isn't actually affected by it — possible bug?
        // Might cause the particle to drift downward instead of moving straight forward.
        particle->trans.y_position += particle->velocity.y - particle->gravity;
        particle->trans.z_position += particle->velocity.z;
        particle->trans.scale += particle->scaleVelocity;
        particle->trans.rotation.y_rotation += particle->angularVelocity.y_rotation;
        particle->trans.rotation.x_rotation += particle->angularVelocity.x_rotation;
        particle->trans.rotation.z_rotation += particle->angularVelocity.z_rotation;
    }
}

/**
 * Iterates through every object and renders it as a particle if applicable.
 * Only particles with the PARTICLE_UNK_FLAG_8000 flag set will be rendered.
 */
UNUSED void render_active_particles(Gfx **dList, Mtx **mtx, Vertex **vtx) {
    UNUSED s32 pad;
    UNUSED s32 pad2;
    Particle **objects;
    s32 minObjIndex;
    s32 maxObjIndex;

    objects = (Particle **) objGetObjList(&minObjIndex, &maxObjIndex);
    for (; minObjIndex < maxObjIndex; minObjIndex++) {
        if (objects[minObjIndex]->trans.flags & OBJ_FLAGS_PARTICLE) {
            if (objects[minObjIndex]->descFlags & PARTICLE_UNK_FLAG_8000) {
                render_particle(objects[minObjIndex], dList, mtx, vtx, 0);
            }
        }
    }
}

/**
 * Load a texture then render a sprite or a billboard.
 */
void render_particle(Particle *particle, Gfx **dList, Mtx **mtx, Vertex **vtx, s32 flags) {
    s32 renderFlags;
    s32 alpha;
    s32 temp;
    ParticleModel *model;
    Vertex *tempvtx;

    renderFlags = (RENDER_FOG_ACTIVE | RENDER_Z_COMPARE);

    // Never true
    if ((particle->descFlags & flags) && D_800E2CDC < 512) {
        return;
    }
    alpha = (particle->opacity >> 8) & 0xFF;
    if (alpha <= 0) {
        return;
    }
    if (particle->kind != PARTICLE_KIND_POINT && particle->kind != PARTICLE_KIND_LINE) {
        gDPSetEnvColor((*dList)++, particle->colour.r, particle->colour.g, particle->colour.b, particle->colour.a);
        if (alpha != 255) {
            renderFlags = (RENDER_Z_UPDATE | RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE);
            gDPSetPrimColor((*dList)++, 0, 0, particle->brightness, particle->brightness, particle->brightness, alpha);
        } else {
            gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
        }
        if (particle->kind == PARTICLE_KIND_SPRITE) {
            temp = particle->textureFrame;
            particle->textureFrame >>= 8;
            particle->textureFrame = (particle->textureFrame * 255) / (particle->sprite->baseTextureId);
            render_sprite_billboard(dList, mtx, vtx, (Object *) particle, particle->sprite, renderFlags);
            particle->textureFrame = temp;
        } else {
            model = particle->model;
            if (model->texture) {
                mtx_cam_push(dList, mtx, &particle->trans, 1.0f, 0.0f);
                material_set(dList, model->texture, renderFlags, particle->textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(model->vertices), model->vertexCount, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(model->triangles), model->triangleCount, TRIN_ENABLE_TEXTURE);
                mtx_pop(dList);
            }
        }
        // Restore primitive and environment colour
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
        if (particle->kind == PARTICLE_KIND_POINT) {
            if (particle->destroyTimer > 0) {
                gDPSetPrimColor((*dList)++, 0, 0, particle->brightness, particle->brightness, particle->brightness,
                                255);
                if (((PointParticle *) particle)->meshRegenerated == 0) {
                    regenerate_point_particles_mesh((PointParticle *) particle);
                }
                model = particle->model;
                temp = ((PointParticle *) particle)->modelFrame;
                temp <<= 3;
                tempvtx = &model->vertices[temp];
                material_set(dList, model->texture, renderFlags, particle->textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(tempvtx), model->vertexCount, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(model->triangles), model->triangleCount, TRIN_ENABLE_TEXTURE);
                if (particle->brightness != 255) {
                    gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
                }
            }
        } else if (particle->kind == PARTICLE_KIND_LINE) {
            gDPSetPrimColor((*dList)++, 0, 0, particle->brightness, particle->brightness, particle->brightness, alpha);
            if (particle->lineCreationPhase >= 2) {
                model = particle->model;
                material_set(dList, model->texture, renderFlags, particle->textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(model->vertices), model->vertexCount, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(model->triangles), model->triangleCount, TRIN_ENABLE_TEXTURE);
            } else if (particle->lineCreationPhase > 0) {
                model = particle->model;
                material_set(dList, model->texture, renderFlags, particle->textureFrame << 8);
                gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(model->vertices), 4, 0);
                gSPPolygon((*dList)++, OS_K0_TO_PHYSICAL(&model->triangles[model->triangleCount]), 1,
                           TRIN_ENABLE_TEXTURE);
            }
            if (alpha != 255 || particle->brightness != 255) {
                gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
            }
        }
    }
}

/**
 * Sets the position and colours of all vertices for all particles spawned by a single emitter.
 * Together, they form the shape of a continuous pipe-like structure.
 */
void regenerate_point_particles_mesh(PointParticle *obj) {
    UNUSED s32 pad;
    s32 index;
    Vec3f vec_up;
    Vec3f vec_right;
    PointParticle *particle;
    PointParticle *prev_particle;
    ParticleEmitter *emitter;
    ParticleModel *model;
    Vertex *otherVerts;
    Vertex *verts;
    ParticleModel *prev_model;

    emitter = obj->pointEmitter;
    prev_particle = NULL;
    prev_model = NULL;
    if (emitter != NULL) {
        if (emitter->refPoints != NULL) {
            for (index = emitter->pointCount - 1; index >= 0; index--) {
                particle = emitter->refPoints[index];
                if (particle->base.destroyTimer == 0) {
                    break;
                }

                model = particle->base.model;
                vec_right.x = particle->base.trans.scale;
                vec_right.y = 0.0f;
                vec_right.z = 0.0f;
                vec3f_rotate(&particle->base.trans.rotation, &vec_right);
                vec_up.x = 0.0f;
                vec_up.y = particle->base.trans.scale;
                vec_up.z = 0.0f;
                vec3f_rotate(&particle->base.trans.rotation, &vec_up);

                verts = &model->vertices[(particle->modelFrame << 3)];
                if (1) {}
                if (1) {}
                if (1) {}
                if (1) {} // Fake

                verts += 4;

                verts->x = particle->base.trans.x_position + vec_right.f[0];
                verts->y = particle->base.trans.y_position + vec_right.f[1];
                verts->z = particle->base.trans.z_position + vec_right.f[2];
                verts->r = particle->base.colour.r;
                verts->g = particle->base.colour.g;
                verts->b = particle->base.colour.b;
                verts->a = particle->base.opacity >> 8;
                verts++;

                verts->x = particle->base.trans.x_position + vec_up.f[0];
                verts->y = particle->base.trans.y_position + vec_up.f[1];
                verts->z = particle->base.trans.z_position + vec_up.f[2];
                verts->r = particle->base.colour.r;
                verts->g = particle->base.colour.g;
                verts->b = particle->base.colour.b;
                verts->a = particle->base.opacity >> 8;
                verts++;

                verts->x = particle->base.trans.x_position - vec_right.f[0];
                verts->y = particle->base.trans.y_position - vec_right.f[1];
                verts->z = particle->base.trans.z_position - vec_right.f[2];
                verts->r = particle->base.colour.r;
                verts->g = particle->base.colour.g;
                verts->b = particle->base.colour.b;
                verts->a = particle->base.opacity >> 8;
                verts++;

                verts->x = particle->base.trans.x_position - vec_up.f[0];
                verts->y = particle->base.trans.y_position - vec_up.f[1];
                verts->z = particle->base.trans.z_position - vec_up.f[2];
                verts->r = particle->base.colour.r;
                verts->g = particle->base.colour.g;
                verts->b = particle->base.colour.b;
                verts->a = particle->base.opacity >> 8;
                verts++;

                verts = &model->vertices[particle->modelFrame << 3];
                if (prev_model != NULL) {
                    otherVerts = &prev_model->vertices[prev_particle->modelFrame << 3];
                    otherVerts += 4;
                } else {
                    otherVerts = &model->vertices[particle->modelFrame << 3];
                    otherVerts += 4;
                }

                verts->x = otherVerts->x;
                verts->y = otherVerts->y;
                verts->z = otherVerts->z;
                verts->r = otherVerts->r;
                verts->g = otherVerts->g;
                verts->b = otherVerts->b;
                verts->a = otherVerts->a;
                verts++;
                otherVerts++;

                verts->x = otherVerts->x;
                verts->y = otherVerts->y;
                verts->z = otherVerts->z;
                verts->r = otherVerts->r;
                verts->g = otherVerts->g;
                verts->b = otherVerts->b;
                verts->a = otherVerts->a;
                verts++;
                otherVerts++;

                verts->x = otherVerts->x;
                verts->y = otherVerts->y;
                verts->z = otherVerts->z;
                verts->r = otherVerts->r;
                verts->g = otherVerts->g;
                verts->b = otherVerts->b;
                verts->a = otherVerts->a;
                verts++;
                otherVerts++;

                verts->x = otherVerts->x;
                verts->y = otherVerts->y;
                verts->z = otherVerts->z;
                verts->r = otherVerts->r;
                verts->g = otherVerts->g;
                verts->b = otherVerts->b;
                verts->a = otherVerts->a;
                verts++;
                otherVerts++;

                prev_particle = particle;
                prev_model = model;

                particle->meshRegenerated = -1;
            }
        }
    }
}

/**
 * Return a specific particle asset table from the main table.
 */
UNUSED ParticleDescriptor *get_particle_asset_table(s32 idx) {
    if (idx < gParticlesAssetTableCount) {
        return gParticlesAssetTable[idx];
    }
    return gParticlesAssetTable[gParticlesAssetTableCount - 1];
}

/**
 * Return the next particle table after the index.
 * Make sure the index is in range by wrapping it.
 */
UNUSED ParticleDescriptor *get_next_particle_table(s32 *idx) {
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
UNUSED ParticleDescriptor *get_previous_particle_table(s32 *idx) {
    *idx = *idx - 1;
    while (*idx < 0) {
        *idx += gParticlesAssetTableCount;
    }
    return gParticlesAssetTable[*idx];
}

/**
 * Return the particle behaviour ID from the behaviour table.
 */
UNUSED ParticleBehaviour *get_particle_behaviour(s32 idx) {
    if (idx < gParticleBehavioursAssetTableCount) {
        return gParticleBehavioursAssetTable[idx];
    }
    return gParticleBehavioursAssetTable[gParticleBehavioursAssetTableCount - 1];
}

/**
 * Return the next particle behaviour ID from the behaviour table.
 * Make sure the index is in range by wrapping it.
 */
UNUSED ParticleBehaviour *get_next_particle_behaviour(s32 *idx) {
    *idx += 1;
    while (*idx >= gParticleBehavioursAssetTableCount) {
        *idx -= gParticleBehavioursAssetTableCount;
    }
    return gParticleBehavioursAssetTable[*idx];
}

/**
 * Return the previous particle behaviour ID from the behaviour table.
 * Make sure the index is in range by wrapping it.
 */
UNUSED ParticleBehaviour *get_previous_particle_behaviour(s32 *idx) {
    *idx -= 1;
    while (*idx < 0) {
        *idx += gParticleBehavioursAssetTableCount;
    }
    return gParticleBehavioursAssetTable[*idx];
}

/**
 * Increases the opacity of all point particles spawned by the emitter.
 */
void increase_emitter_opacity(Object *obj, s32 idx, s32 delta, s32 maxOpacity) {
    s32 newOpacity;

    maxOpacity <<= 8;
    newOpacity = (obj->particleEmitter[idx].point_opacity & 0xFFFF) + delta;
    if (maxOpacity < newOpacity) {
        obj->particleEmitter[idx].point_opacity = maxOpacity;
    } else {
        obj->particleEmitter[idx].point_opacity = newOpacity;
    }
    obj->particleEmitter[idx].flags |= PARTICLE_OVERRIDE_OPACITY_FROM_DESCRIPTOR;
}

/**
 * Decreases the opacity of all point particles spawned by the emitter.
 */
void decrease_emitter_opacity(Object *obj, s32 idx, s32 delta, s32 maxOpacity) {
    s32 newOpacity;

    maxOpacity <<= 8;
    newOpacity = (obj->particleEmitter[idx].point_opacity & 0xFFFF) - delta;
    if (newOpacity < maxOpacity) {
        obj->particleEmitter[idx].point_opacity = maxOpacity;
    } else {
        obj->particleEmitter[idx].point_opacity = newOpacity;
    }
    obj->particleEmitter[idx].flags |= PARTICLE_OVERRIDE_OPACITY_FROM_DESCRIPTOR;
}
