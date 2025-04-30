#include "waves.h"
#include "types.h"
#include "macros.h"
#include <ultra64.h>
#include "memory.h"
#include "textures_sprites.h"
#include "objects.h"
#include "tracks.h"
#include "math_util.h"
#include "PRinternal/viint.h"

/************ .data ************/

f32 *D_800E3040 = NULL;   // indexed by values of D_800E3044
Vec2s *D_800E3044 = NULL; // holds some sort of index?
TexCoords *D_800E3048 = NULL;
f32 *D_800E304C[9] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

Vertex *gWaveVertices[4][1] = { { NULL }, { NULL } };
Triangle *gWaveTriangles[4][1] = { { NULL }, { NULL }, { NULL }, { NULL } };
Triangle D_800E3090[4] = {
    { { { BACKFACE_DRAW, 0, 2, 1 } }, { { { 0, 0 } } }, { { { 0, 0 } } }, { { { 0, 0 } } } },
    { { { BACKFACE_DRAW, 1, 2, 3 } }, { { { 0, 0 } } }, { { { 0, 0 } } }, { { { 0, 0 } } } },
    { { { BACKFACE_DRAW, 0, 2, 1 } }, { { { 0, 0 } } }, { { { 0, 0 } } }, { { { 0, 0 } } } },
    { { { BACKFACE_DRAW, 1, 2, 3 } }, { { { 0, 0 } } }, { { { 0, 0 } } }, { { { 0, 0 } } } },
};

TextureHeader *gWaveTextureHeader = NULL;
s32 *D_800E30D4 = NULL; // indexed by D_800E30D8.unkC
LevelModel_Alternate *D_800E30D8 = NULL;
s32 D_800E30DC = 0;     // Tracks an index into D_8012A1E8
s16 *D_800E30E0 = NULL; // Points to either D_800E30E8 or D_800E3110 and is used for D_800E30D4
s16 *D_800E30E4 = NULL; // Points to either D_800E30FC or D_800E3144 and is used to index D_800E304C

s16 D_800E30E8[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

s16 D_800E30FC[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 0 };

s16 D_800E3110[26] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0 };

s16 D_800E3144[26] = { 0, 1, 1, 1, 2, 3, 4, 4, 4, 5, 3, 4, 4, 4, 5, 3, 4, 4, 4, 5, 6, 7, 7, 7, 8, 0 };

u8 *D_800E3178 = NULL;
s32 D_800E317C = 0; // some sort of count? Relative to D_80129FC8.unk0
LevelHeader_70 *D_800E3180 = NULL;
unk800E3184 *D_800E3184 = NULL; // tracks an index into D_800E3190
s32 D_800E3188 = 0;             // counter for something, incremented in func_800BF634, decremented in func_800BF3E4
s32 D_800E318C = 0;             // used in mempool_alloc_safe size calculation, multiplied with 8
unk800E3190 *D_800E3190 = NULL;
Object **D_800E3194 = NULL; // might be a length of 32
Object *gWaveGeneratorObj = NULL;

/*******************************/

/************ .rodata ************/

const char D_800E9160[] = "\nCouldn't find a block to pick wave details from.\nUsing block 0 as default.";
const char D_800E91AC[] = "\n\nBlock may be specified using 'P' on water group node.";
const char D_800E91E4[] = "\nError :: can not remove a wave swell object which doesn't exist !";
const char D_800E9228[] = "\nError :: more than eight swells overlap on column %d.";
const char D_800E9260[] = "\nError :: can not add another wave swell, reached limit of %d.";

/*********************************/

/************ .bss ************/

Gfx *gWaveDL;
MatrixS *D_80129FC4;
unk80129FC8 D_80129FC8; // holds lots of control information used in this file
s32 D_8012A018;         // either 1 or 0, toggled in func_800B9C18, used to index vertices and triangles
f32 D_8012A01C;         // is set to lowest value of D_800E3040
f32 D_8012A020;         // is set to highest value of D_800E3040
UNUSED s32 D_8012A024;
Vertex D_8012A028[2][4]; // stores values of gWaveVertices to be used in func_800BA8E4
s32 D_8012A078;          // controls whether 2 or 4 items are used in gWaveVertices / gWaveTriangles
TriangleBatchInfo *gWaveBatch;
TextureHeader *gWaveTexture;
s32 D_8012A084; // u value for D_800E3048
s32 D_8012A088; // v value for D_800E3048
s32 D_8012A08C; // is added onto u of D_8012A084, is multiplied with texture width
s32 D_8012A090; // is added onto v of D_8012A084, is multiplied with texture height
s32 D_8012A094; // bitmask / something width (related to texture)
s32 D_8012A098; // bitmask / something height (related to texture)
s32 D_8012A09C; // stores / relates to frameAdvanceDelay, used in func_800BA8E4
f32 D_8012A0A0; // copy of gWaveBoundingBoxDiffX
f32 D_8012A0A4; // copy of gWaveBoundingBoxDiffZ
s32 gWaveBoundingBoxDiffX;
s32 gWaveBoundingBoxDiffZ;
s32 gWaveBoundingBoxX1;
s32 gWaveBoundingBoxZ1;
f32 D_8012A0B8; // some sort of ratio for x
f32 D_8012A0BC; // some sort of ratio for z
s32 D_8012A0C0; // level bounding box x1
s32 D_8012A0C4; // level bounding box x2
s32 D_8012A0C8; // level bounding box z1
s32 D_8012A0CC; // level bounding box x2
s32 D_8012A0D0; // copy of gWaveBoundingBoxX1
s32 D_8012A0D4; // copy of gWaveBoundingBoxZ1
s32 D_8012A0D8; // used in mempool_alloc_safe size calculation
s32 D_8012A0DC; // used in mempool_alloc_safe size calculation
s32 gNumberOfLevelSegments;
s32 D_8012A0E8[64];
s16 D_8012A1E8[512]; // used to index D_800E30D8 and as arg0 for func_800B92F4 and func_800B97A8
unk8012A5E8 D_8012A5E8[2];
unk8012A5E8 D_8012A600[24];
f32 gWavePowerBase;
f32 gWaveMagnitude;
s32 gWavePowerDivisor;

/*****************************/

#define FREE_MEM(mem)          \
    tempMem = (s32 *) mem;     \
    if (tempMem != NULL) {     \
        mempool_free(tempMem); \
        mem = NULL;            \
    }
#define FREE_TEX(tex)      \
    tempTex = tex;         \
    if (tempTex != NULL) { \
        tex_free(tempTex); \
        tex = NULL;        \
    }

void free_waves(void) {
    TextureHeader *tempTex;
    s32 *tempMem;
    FREE_MEM(D_800E3040);
    FREE_MEM(D_800E3044);
    FREE_MEM(D_800E3048);
    FREE_MEM(D_800E304C[0]);
    FREE_MEM(gWaveVertices[0][0]);
    FREE_MEM(gWaveTriangles[0][0]);
    FREE_TEX(gWaveTextureHeader);
    FREE_MEM(D_800E30D4);
    FREE_MEM(D_800E30D8);
    FREE_MEM(D_800E3178);
    D_800E3190 = NULL;
    D_800E3194 = NULL;
    D_800E3184 = NULL;
    D_800E3188 = 0;
}

void wave_init(void) {
    s32 temp;
    s32 allocSize;
    s32 i;

    free_waves();
    D_800E3040 = (f32 *) mempool_alloc_safe(D_80129FC8.unk20 * sizeof(f32 *), COLOUR_TAG_CYAN);
    D_800E3044 = (Vec2s *) mempool_alloc_safe((D_80129FC8.unk4 * sizeof(Vec2s *)) * D_80129FC8.unk4, COLOUR_TAG_CYAN);
    D_800E3048 = (TexCoords *) mempool_alloc_safe(((D_80129FC8.unk0 + 1) * sizeof(TexCoords *)) * (D_80129FC8.unk0 + 1),
                                                  COLOUR_TAG_CYAN);
    allocSize = ((D_80129FC8.unk0 + 1) << 2) * (D_80129FC8.unk0 + 1);
    D_800E304C[0] = mempool_alloc_safe(allocSize * ARRAY_COUNT(D_800E304C), COLOUR_TAG_CYAN);
    for (i = 1; i < ARRAY_COUNT(D_800E304C); i++) {
        D_800E304C[i] = (f32 *) (((u32) D_800E304C[0]) + (allocSize * i));
    }
    temp = (D_80129FC8.unk0 + 1);
    allocSize = (temp * 250 * (D_80129FC8.unk0 + 1));
    if (D_8012A078 != 2) {
        gWaveVertices[0][0] = (Vertex *) mempool_alloc_safe(allocSize << 1, COLOUR_TAG_CYAN);
        gWaveVertices[1][0] = (Vertex *) (((u32) gWaveVertices[0][0]) + allocSize);
    } else {
        gWaveVertices[0][0] = (Vertex *) mempool_alloc_safe(allocSize << 2, COLOUR_TAG_CYAN);
        gWaveVertices[1][0] = (Vertex *) (((u32) gWaveVertices[0][0]) + allocSize);
        gWaveVertices[2][0] = (Vertex *) (((u32) gWaveVertices[1][0]) + allocSize);
        gWaveVertices[3][0] = (Vertex *) (((u32) gWaveVertices[2][0]) + allocSize);
    }
    allocSize = (D_80129FC8.unk0 * 32) * D_80129FC8.unk0;
    if (D_8012A078 != 2) {
        gWaveTriangles[0][0] = mempool_alloc_safe(allocSize << 1, COLOUR_TAG_CYAN);
        gWaveTriangles[1][0] = (Triangle *) (((u32) gWaveTriangles[0][0]) + allocSize);
    } else {
        gWaveTriangles[0][0] = (Triangle *) mempool_alloc_safe(allocSize << 2, COLOUR_TAG_CYAN);
        gWaveTriangles[1][0] = (Triangle *) (((u32) gWaveTriangles[0][0]) + allocSize);
        gWaveTriangles[2][0] = (Triangle *) (((u32) gWaveTriangles[1][0]) + allocSize);
        gWaveTriangles[3][0] = (Triangle *) (((u32) gWaveTriangles[2][0]) + allocSize);
    }
    gWaveTextureHeader = load_texture(D_80129FC8.textureId);
}

void func_800B8134(LevelHeader *header) {
    if (D_8012A078 != 2) {
        D_80129FC8.unk0 = header->unk56;
    } else {
        D_80129FC8.unk0 = 4;
    }
    D_80129FC8.unk4 = header->unk57;
    D_80129FC8.unk8 = header->unk58;
    D_80129FC8.unkC = header->unk5A / 256.0f;
    D_80129FC8.unk10 = header->unk59 << 8;
    D_80129FC8.unk14 = header->unk5C;
    D_80129FC8.unk18 = header->unk5E / 256.0f;
    D_80129FC8.unk1C = header->unk5D << 8;
    D_80129FC8.unk20 = header->unk60 & ~1;
    if (D_8012A078 != 2) {
        D_80129FC8.unk24 = header->unk6E;
    } else {
        D_80129FC8.unk24 = 3;
    }
    D_80129FC8.unk28 = header->unk71;
    D_80129FC8.textureId = header->textureId & 0xFFFF;
    D_80129FC8.unk30 = header->unk6A;
    D_80129FC8.unk34 = header->unk6B;
    D_80129FC8.unk38 = header->unk6C;
    D_80129FC8.unk3C = header->unk6D;
    D_80129FC8.magnitude = header->wavePower / 256.0f;
    D_80129FC8.unk44 = header->unk64 / 256.0f;
    D_80129FC8.unk48 = header->unk66 / 256.0f;
    D_80129FC8.darkVertexColours = header->darkVertexColours;
}

void func_800B82B4(LevelModel *model, LevelHeader *header, s32 arg2) {
    s32 k;
    s32 var_fp;
    s32 j_2;
    s32 var_s3;
    s32 var_s5;
    s32 var_s6;
    s32 sp54;
    s32 i;
    s32 sp4C;
    s32 j;
    s32 i_2;
    s32 var_t0;
    s32 var_v1;
    s32 var_t7;
    s32 var_a1;
    s32 var_t2;

    D_8012A078 = arg2;
    func_800B8134(header);
    wave_init();
    func_800BBDDC(model, header);
    D_8012A0A0 = gWaveBoundingBoxDiffX;
    D_8012A0A4 = gWaveBoundingBoxDiffZ;
    D_8012A0B8 = D_8012A0A0 / D_80129FC8.unk0;
    D_8012A0BC = D_8012A0A4 / D_80129FC8.unk0;
    D_8012A084 = 0;
    D_8012A088 = 0;
    D_8012A08C = ((gWaveTexture->width * D_80129FC8.unk30) * 32) / D_80129FC8.unk0;
    D_8012A090 = ((gWaveTexture->height * D_80129FC8.unk34) * 32) / D_80129FC8.unk0;
    D_8012A094 = (gWaveTexture->width * 32) - 1;
    D_8012A098 = (gWaveTexture->height * 32) - 1;
    D_8012A09C = 0;
    var_s6 = D_80129FC8.unk10;
    sp54 = (D_80129FC8.unk8 << 16) / D_80129FC8.unk20;
    var_fp = D_80129FC8.unk1C;
    sp4C = (D_80129FC8.unk14 << 16) / D_80129FC8.unk20;
    D_8012A01C = 10000.0f;
    D_8012A020 = -10000.0f;
    for (i_2 = 0; i_2 < D_80129FC8.unk20; i_2++) {
        D_800E3040[i_2] = (sins_f(var_s6) * D_80129FC8.unkC) + (sins_f(var_fp) * D_80129FC8.unk18);
        if (D_80129FC8.unk28 != FALSE) {
            D_800E3040[i_2] *= 2.0f;
        }
        if (D_800E3040[i_2] < D_8012A01C) {
            D_8012A01C = D_800E3040[i_2];
        }
        if (D_8012A020 < D_800E3040[i_2]) {
            D_8012A020 = D_800E3040[i_2];
        }
        var_s6 += sp54;
        var_fp += sp4C;
    };
    save_rng_seed();
    set_rng_seed(0x57415646);

    var_s5 = 0;
    for (i_2 = 0; i_2 < D_80129FC8.unk4; i_2++) {
        for (j_2 = 0; j_2 < D_80129FC8.unk4; j_2++) {
            D_800E3044[var_s5].s[0] = get_random_number_from_range(0, D_80129FC8.unk20 - 1);
            D_800E3044[var_s5].s[1] = get_random_number_from_range(0, D_80129FC8.unk20 - 1);
            var_s5++;
        }
    }
    var_s5 = 0;
    i_2 = 0;
    load_rng_seed();
    if (arg2 != 2) {
        arg2 = 2;
    } else {
        arg2 = 4;
    }
    for (var_s3 = 0; var_s3 < 25; var_s3++) {
        if (0 <= D_80129FC8.unk0) {
            do {
                for (j_2 = 0; D_80129FC8.unk0 >= j_2; j_2++) {
                    for (k = 0; k < arg2; k++) {
                        gWaveVertices[0][k][var_s5].x = (j_2 * D_8012A0B8) + 0.5;
                        gWaveVertices[0][k][var_s5].z = (i_2 * D_8012A0BC) + 0.5;
                        // this is only 0 for hot top volcano
                        if (D_80129FC8.darkVertexColours == 0) {
                            gWaveVertices[0][k][var_s5].r = 255;
                            gWaveVertices[0][k][var_s5].g = 255;
                            gWaveVertices[0][k][var_s5].b = 255;
                        } else {
                            gWaveVertices[0][k][var_s5].r = 0;
                            gWaveVertices[0][k][var_s5].g = 0;
                            gWaveVertices[0][k][var_s5].b = 0;
                        }
                        gWaveVertices[0][k][var_s5].a = 255;
                    }
                    var_s5++;
                }
                i_2++;
            } while (D_80129FC8.unk0 >= i_2);
            i_2 = 0;
        }
    }

    var_s5 = 0;
    for (i_2 = 0; i_2 < D_80129FC8.unk0; i_2++) {
        for (j_2 = 0; j_2 < D_80129FC8.unk0; j_2++) {
            for (k = 0; k < arg2; k++) {
                gWaveTriangles[0][k][var_s5].flags = BACKFACE_DRAW;
                gWaveTriangles[0][k][var_s5].vi0 = j_2;
                gWaveTriangles[0][k][var_s5].vi1 = (j_2 + D_80129FC8.unk0) + 1;
                gWaveTriangles[0][k][var_s5].vi2 = j_2 + 1;
                var_s5++;
                gWaveTriangles[0][k][var_s5].flags = BACKFACE_DRAW;
                gWaveTriangles[0][k][var_s5].vi0 = j_2 + 1;
                gWaveTriangles[0][k][var_s5].vi1 = (j_2 + D_80129FC8.unk0) + 1;
                gWaveTriangles[0][k][var_s5].vi2 = (j_2 + D_80129FC8.unk0) + 2;
                var_s5--;
            }
            var_s5 += 2;
        }
    }
    func_800BC6C8();

    var_s5 = (D_80129FC8.unk0 + 1) * D_80129FC8.unk0;
    for (i = 0; i < ARRAY_COUNT(D_8012A028); i++) {
        D_8012A028[i][0].x = gWaveVertices[i][0][0].x;
        D_8012A028[i][0].y = 0;
        D_8012A028[i][0].z = gWaveVertices[i][0][0].z;
        D_8012A028[i][0].r = gWaveVertices[i][0][0].r;
        D_8012A028[i][0].g = gWaveVertices[i][0][0].g;
        D_8012A028[i][0].b = gWaveVertices[i][0][0].b;
        D_8012A028[i][0].a = gWaveVertices[i][0][0].a;

        D_8012A028[i][1].x = gWaveVertices[i][0][D_80129FC8.unk0].x;
        D_8012A028[i][1].y = 0;
        D_8012A028[i][1].z = gWaveVertices[i][0][D_80129FC8.unk0].z;
        D_8012A028[i][1].r = gWaveVertices[i][0][D_80129FC8.unk0].r;
        D_8012A028[i][1].g = gWaveVertices[i][0][D_80129FC8.unk0].g;
        D_8012A028[i][1].b = gWaveVertices[i][0][D_80129FC8.unk0].b;
        D_8012A028[i][1].a = gWaveVertices[i][0][D_80129FC8.unk0].a;

        D_8012A028[i][2].x = gWaveVertices[i][0][var_s5].x;
        D_8012A028[i][2].y = 0;
        D_8012A028[i][2].z = gWaveVertices[i][0][var_s5].z;
        D_8012A028[i][2].r = gWaveVertices[i][0][var_s5].r;
        D_8012A028[i][2].g = gWaveVertices[i][0][var_s5].g;
        D_8012A028[i][2].b = gWaveVertices[i][0][var_s5].b;
        D_8012A028[i][2].a = gWaveVertices[i][0][var_s5].a;

        D_8012A028[i][3].x = gWaveVertices[i][0][var_s5 + D_80129FC8.unk0].x;
        D_8012A028[i][3].y = 0;
        D_8012A028[i][3].z = gWaveVertices[i][0][var_s5 + D_80129FC8.unk0].z;
        D_8012A028[i][3].r = gWaveVertices[i][0][var_s5 + D_80129FC8.unk0].r;
        D_8012A028[i][3].g = gWaveVertices[i][0][var_s5 + D_80129FC8.unk0].g;
        D_8012A028[i][3].b = gWaveVertices[i][0][var_s5 + D_80129FC8.unk0].b;
        D_8012A028[i][3].a = gWaveVertices[i][0][var_s5 + D_80129FC8.unk0].a;
    }

    func_800BCC70(model);
    if (D_80129FC8.unk24 == 3) {
        D_800E30E0 = D_800E30E8;
        D_800E30E4 = D_800E30FC;
    } else {
        D_80129FC8.unk24 = 5;
        D_800E30E0 = D_800E3110;
        D_800E30E4 = D_800E3144;
    }
    D_800E3188 = 0;
    gWavePowerDivisor = 0;
    gWaveGeneratorObj = NULL;
    D_8012A018 = 0;
}

void func_800B8B8C(void) {
    s32 i;

    D_800E30DC = 0;
    for (i = 0; i < D_8012A0D8 * D_8012A0DC; i++) {
        D_800E30D4[i] = 0;
    }
}

void func_800B8C04(s32 xPosition, s32 yPosition, s32 zPosition, s32 currentViewport, s32 updateRate) {
    s32 xPosRatio;
    s32 zPosRatio;
    s32 tempXPosRatio;
    s32 var_v1;
    s32 var_s5;
    u32 var_t2;
    s32 var_t5;
    s32 var_v0;
    s32 var_s4;
    s32 var_a3;
    s32 var_s6;

    xPosRatio = (xPosition - D_8012A0D0) / gWaveBoundingBoxDiffX;
    zPosRatio = (zPosition - D_8012A0D4) / gWaveBoundingBoxDiffZ;

    if (0) {}

    for (var_v1 = 0; var_v1 != ARRAY_COUNT(D_8012A600); var_v1 += 4) {
        D_8012A5E8[0].unk0 = -1;
        D_8012A5E8[1].unk0 = -1;
        D_8012A600[var_v1].unk0 = -1;
        D_8012A600[var_v1 + 1].unk0 = -1;
        D_8012A600[var_v1 + 2].unk0 = -1;
        D_8012A600[var_v1 + 3].unk0 = -1;
    }

    if (D_80129FC8.unk28 != 0) {
        xPosition -= (xPosRatio * gWaveBoundingBoxDiffX) + D_8012A0D0;
        zPosition -= (zPosRatio * gWaveBoundingBoxDiffZ) + D_8012A0D4;
        if ((gWaveBoundingBoxDiffX >> 1) < xPosition) {
            var_v1 = 8;
        } else {
            var_v1 = 0;
        }

        if ((gWaveBoundingBoxDiffZ >> 1) < zPosition) {
            var_s4 = 16;
        } else {
            var_s4 = 0;
        }

        for (var_v1 -= (D_80129FC8.unk24 >> 1) * 8; var_v1 < 0; var_v1 += 16) {
            xPosRatio -= 1;
        }

        for (var_s4 -= (D_80129FC8.unk24 >> 1) * 16; var_s4 < 0; var_s4 += 32) {
            zPosRatio -= 1;
        }

        for (var_s6 = 0, var_a3 = 0; var_s6 < D_80129FC8.unk24; var_s6++) {
            if ((zPosRatio >= 0) && (zPosRatio < D_8012A0DC)) {
                tempXPosRatio = xPosRatio;
                var_t5 = var_v1;
                var_t2 = (zPosRatio * D_8012A0D8) + xPosRatio;
                for (var_s5 = 0; var_s5 < D_80129FC8.unk24; var_s5++) {
                    // clang-format off
                    if (
                        (tempXPosRatio >= 0) &&
                        (tempXPosRatio < D_8012A0D8) &&
                        (D_8012A0E8[zPosRatio] & (1 << tempXPosRatio))
                    ) {
                        // clang-format on
                        D_800E30D4[var_t2] |= D_800E30E0[var_s6 * D_80129FC8.unk24 + var_s5] << (var_t5 + var_s4);
                        for (var_v0 = 0; var_v0 < gNumberOfLevelSegments; var_v0++) {
                            if (var_t2 == D_800E30D8[var_v0].unkC) {
                                D_8012A5E8[var_a3].unk0 = var_v0;
                                D_8012A5E8[var_a3].unk2 = (var_t5 + var_s4) >> 3;
                                D_8012A5E8[var_a3].unk8 = var_v0 * D_800E317C;
                                D_8012A5E8[var_a3].unk4 = D_800E30D8[var_v0].unk12;
                                if (var_t5 != 0) {
                                    D_8012A5E8[var_a3].unk8 += D_80129FC8.unk0;
                                    D_8012A5E8[var_a3].unk4 += D_80129FC8.unk0;
                                    while (D_8012A5E8[var_a3].unk4 >= D_80129FC8.unk4) {
                                        D_8012A5E8[var_a3].unk4 -= D_80129FC8.unk4;
                                    }
                                }
                                D_8012A5E8[var_a3].unk6 = D_800E30D8[var_v0].unk10;
                                if (var_s4 != 0) {
                                    D_8012A5E8[var_a3].unk8 += ((D_80129FC8.unk0 * 2) + 1) * D_80129FC8.unk0;
                                    D_8012A5E8[var_a3].unk6 += D_80129FC8.unk0;
                                    while (D_8012A5E8[var_a3].unk6 >= D_80129FC8.unk4) {
                                        D_8012A5E8[var_a3].unk6 -= D_80129FC8.unk4;
                                    }
                                }
                                var_a3++;
                                var_v0 = 0x7FFF;
                            }
                        }
                    }
                    var_t5 += 8;
                    if (var_t5 > 8) {
                        var_t5 -= 16;
                        tempXPosRatio++;
                        var_t2++;
                    }
                }
            }
            var_s4 += 16;
            if (var_s4 > 16) {
                var_s4 -= 32;
                zPosRatio++;
            }
        }
    } else {
        xPosRatio -= D_80129FC8.unk24 >> 1;
        zPosRatio -= D_80129FC8.unk24 >> 1;
        for (var_s6 = 0, var_a3 = 0; var_s6 < D_80129FC8.unk24; var_s6++, zPosRatio++) {
            if ((zPosRatio >= 0) && (zPosRatio < D_8012A0DC)) {
                tempXPosRatio = xPosRatio;
                var_t2 = (zPosRatio * D_8012A0D8) + xPosRatio;
                for (var_s5 = 0; var_s5 < D_80129FC8.unk24; var_s5++, tempXPosRatio++, var_t2++) {
                    // clang-format off
                    if (
                        (tempXPosRatio >= 0) &&
                        (tempXPosRatio < D_8012A0D8) &&
                        (D_8012A0E8[zPosRatio] & (1 << tempXPosRatio))
                    ) {
                        // clang-format on
                        D_800E30D4[var_t2] = D_800E30E0[var_s6 * D_80129FC8.unk24 + var_s5];
                        for (var_v0 = 0; var_v0 < gNumberOfLevelSegments; var_v0++) {
                            if (var_t2 == D_800E30D8[var_v0].unkC) {
                                D_8012A5E8[var_a3].unk0 = var_v0;
                                D_8012A5E8[var_a3].unk2 = 0;
                                D_8012A5E8[var_a3].unk4 = D_800E30D8[var_v0].unk12;
                                D_8012A5E8[var_a3].unk6 = D_800E30D8[var_v0].unk10;
                                D_8012A5E8[var_a3].unk8 = var_v0 * D_800E317C;
                                var_a3++;
                                var_v0 = 0x7FFF;
                            }
                        }
                    }
                }
            }
        }
    }

    func_800BA288(currentViewport, updateRate);
}

s32 func_800B9228(LevelModelSegment *arg0) {
    s32 v0 = 0;
    s32 result = FALSE;
    while (v0 < gNumberOfLevelSegments && arg0 != D_800E30D8[v0].unk00) {
        v0++;
    };
    if (D_800E30D4[D_800E30D8[v0].unkC]) {
        result = TRUE;
        D_8012A1E8[D_800E30DC++] = v0;
    }
    return result;
}

void func_800B92F4(s32 arg0, s32 arg1) {
    s32 i;
    s32 var_s2;
    s32 j;
    f32 temp_f22;
    f32 vertexY;
    s32 sp98;
    s32 var_v0;
    s32 sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s32 var_v1;
    s32 vertexIdx;
    s32 var_s1;
    s32 k;
    Vertex *vertices;
    LevelModel_Alternate *sp6C;

    temp_f22 = (1.0f - D_80129FC8.unk44) / 255.0f;
    sp6C = &D_800E30D8[arg0];
    sp90 = (D_80129FC8.unk0 + 1) * (D_80129FC8.unk0 + 1);
    for (k = 0; D_8012A5E8[k].unk0 != -1; k++) {
        if (arg0 != D_8012A5E8[k].unk0) {
            continue;
        }

        if (D_80129FC8.unk28 != FALSE) {
            sp98 = (((u32) D_800E30D4[sp6C->unkC] >> (D_8012A5E8[k].unk2 * 8)) & 0xFF) - 1;
            sp8C = (D_8012A5E8[k].unk2 & 1) * D_80129FC8.unk0;
            sp88 = ((D_8012A5E8[k].unk2 & 2) >> 1) * D_80129FC8.unk0;
        } else {
            sp98 = (D_800E30D4[sp6C->unkC] & 0xFF) - 1;
            sp8C = 0;
            sp88 = 0;
        }

        sp84 = D_8012A5E8[k].unk6;
        vertices = &gWaveVertices[D_8012A018 + arg1][0][sp90 * sp98];
        sp98 = D_800E30E4[sp98];
        vertexIdx = 0;
        for (i = 0; i <= D_80129FC8.unk0; i++) {
            var_s1 = D_8012A5E8[k].unk4;
            var_s2 = (sp84 * D_80129FC8.unk4) + var_s1;
            for (j = 0; j <= D_80129FC8.unk0; j++) {
                vertexY =
                    (D_800E3040[D_800E3044[var_s2].s[0]] + D_800E3040[D_800E3044[var_s2].s[1]]) * D_80129FC8.magnitude;
                if (D_800E3188 > 0) {
                    vertexY += func_800BEFC4(arg0, j + sp8C, i + sp88);
                }
                vertexY *= D_800E304C[sp98][vertexIdx];
                var_v0 = D_800E3178[D_8012A5E8[k].unk8];

                // clang-format off
                var_v0 <<= 1; \
                D_8012A5E8[k].unk8++;
                // clang-format on
                if (var_v0 < 0xFF) {
                    vertexY *= D_80129FC8.unk44 + ((f32) var_v0 * temp_f22);
                }
                var_v0 += (s32) (vertexY * D_80129FC8.unk48);
                if (var_v0 > 0xFF) {
                    var_v0 = 0xFF;
                } else if (var_v0 < 0) {
                    var_v0 = 0;
                }
                var_v0 += ((0xFF - var_v0) * sp6C->unk14[arg1 >> 1].unk0[D_8012A5E8[k].unk2]) >> 7;
                vertices[vertexIdx].y = vertexY;

                var_v1 = var_v0 < 0xC0 ? 0xFF : ((0xFF - var_v0) * 4) & 0xFF;
                vertices[vertexIdx].r = var_v1;
                vertices[vertexIdx].g = var_v1;
                vertices[vertexIdx].b = var_v1;

                var_v1 = var_v0 < 0x40 ? (var_v0 * 4) & 0xFF : 0xFF;
                vertices[vertexIdx].a = var_v1;
                vertexIdx++;
                var_s1++;
                var_s2++;
                if (var_s1 >= D_80129FC8.unk4) {
                    var_s1 -= D_80129FC8.unk4;
                    var_s2 -= D_80129FC8.unk4;
                }
            }
            sp84++;
            if (sp84 >= D_80129FC8.unk4) {
                sp84 -= D_80129FC8.unk4;
            }
            if (D_80129FC8.unk28 != FALSE) {
                D_8012A5E8[k].unk8 += D_80129FC8.unk0;
            }
        }
    }
}

void func_800B97A8(s32 arg0, s32 arg1) {
    s32 var_v0;
    f32 temp_f26;
    s32 vertexIdx;
    s32 spA8;
    f32 var_f20;
    s32 spA0;
    s32 sp9C;
    s32 sp98;
    s32 var_a0;
    f32 var_f28;
    s32 var_s1;
    s32 i;
    s32 var_s2;
    s32 j;
    Vertex *vertices;
    LevelModel_Alternate *sp78;
    s32 k;

    k = 0;
    temp_f26 = (D_8012A020 * 2.0f) - (D_8012A01C * 2.0f);
    spA0 = (D_80129FC8.unk0 + 1) * (D_80129FC8.unk0 + 1);
    sp78 = &D_800E30D8[arg0];
    var_f28 = temp_f26 <= 0 ? 0 : 1.0f / temp_f26;

    temp_f26 = D_8012A01C * 2.0f;
    for (; D_8012A5E8[k].unk0 != -1; k++) {
        if (arg0 != D_8012A5E8[k].unk0) {
            continue;
        }

        if (D_80129FC8.unk28 != FALSE) {
            spA8 = (((u32) D_800E30D4[sp78->unkC] >> (D_8012A5E8[k].unk2 * 8)) & 0xFF) - 1;
            sp9C = (D_8012A5E8[k].unk2 & 1) * D_80129FC8.unk0;
            sp98 = ((s32) (D_8012A5E8[k].unk2 & 2) >> 1) * D_80129FC8.unk0;
        } else {
            spA8 = (D_800E30D4[sp78->unkC] & 0xFF) - 1;
            sp9C = 0;
            sp98 = 0;
        }

        var_a0 = D_8012A5E8[k].unk6;
        vertices = &gWaveVertices[D_8012A018 + arg1][0][spA0 * spA8];
        spA8 = D_800E30E4[spA8];
        for (i = 0, vertexIdx = 0; i <= D_80129FC8.unk0; i++) {
            var_s1 = D_8012A5E8[k].unk4;
            var_s2 = (var_a0 * D_80129FC8.unk4) + var_s1;
            for (j = 0; j <= D_80129FC8.unk0; j++) {
                var_f20 =
                    (D_800E3040[D_800E3044[var_s2].s[0]] + D_800E3040[D_800E3044[var_s2].s[1]]) * D_80129FC8.magnitude;
                if (D_800E3188 > 0) {
                    var_f20 += func_800BEFC4(arg0, j + sp9C, i + sp98);
                }
                var_f20 *= D_800E304C[spA8][vertexIdx];
                vertices[vertexIdx].y = var_f20;
                var_f20 = (var_f20 - temp_f26) * var_f28;
                if (var_f20 > 1.0f) {
                    var_f20 = 1.0f;
                } else if (var_f20 < 0) {
                    var_f20 = 0;
                }
                var_v0 = (0 * var_f20);
                var_v0 += 0xFF;
                vertices[vertexIdx].r = var_v0;
                vertices[vertexIdx].g = var_v0;
                vertices[vertexIdx].b = var_v0;
                vertices[vertexIdx].a = 0xFF;
                vertexIdx++;
                var_s1++;
                var_s2++;
                if (var_s1 >= D_80129FC8.unk4) {
                    var_s1 -= D_80129FC8.unk4;
                    var_s2 -= D_80129FC8.unk4;
                }
            }
            var_a0++;
            if (var_a0 >= D_80129FC8.unk4) {
                var_a0 -= D_80129FC8.unk4;
            }
            if (D_80129FC8.unk28 != FALSE) {
                D_8012A5E8[k].unk8 += D_80129FC8.unk0;
            }
        }
    }
}

void func_800B9C18(s32 arg0) {
    s32 i;
    s32 j;
    s32 k;
    s32 var_a2;
    s32 var_ra;
    s32 var_v1;
    s32 var_t5;
    s32 var_t2;
    s32 var_s0;
    s32 k_2;
    s32 j_2;
    s32 i_2;

    D_8012A018 = 1 - D_8012A018;
    for (i_2 = 0, j_2 = 0; i_2 < D_80129FC8.unk4; i_2++) {
        for (k_2 = 0; k_2 < D_80129FC8.unk4; k_2++) {
            D_800E3044[j_2].s[0] += arg0;
            while (D_800E3044[j_2].s[0] >= D_80129FC8.unk20) {
                D_800E3044[j_2].s[0] -= D_80129FC8.unk20;
            }
            D_800E3044[j_2].s[1] += arg0;
            while (D_800E3044[j_2].s[1] >= D_80129FC8.unk20) {
                D_800E3044[j_2].s[1] -= D_80129FC8.unk20;
            }
            j_2++;
        }
    }

    D_8012A09C += gWaveTextureHeader->frameAdvanceDelay * arg0;
    if (D_8012A09C < 0) {
        D_8012A09C = 0;
    } else {
        while (D_8012A09C >= gWaveTextureHeader->numOfTextures) {
            D_8012A09C -= gWaveTextureHeader->numOfTextures;
        }
    }

    D_8012A084 = ((D_80129FC8.unk38 * arg0) + D_8012A084) & D_8012A094;
    D_8012A088 = ((D_80129FC8.unk3C * arg0) + D_8012A088) & D_8012A098;
    var_a2 = D_8012A088;
    for (i = 0, var_s0 = 0; i <= D_80129FC8.unk0; i++) {
        var_v1 = D_8012A084;
        for (j = 0; j <= D_80129FC8.unk0; j++) {
            D_800E3048[var_s0].u = var_v1;
            D_800E3048[var_s0].v = var_a2;
            var_v1 += D_8012A08C;
            var_s0++;
        }
        var_a2 += D_8012A090;
    }

    if (D_8012A078 != 2) {
        var_t2 = 1;
    } else {
        var_t2 = 2;
    }

    var_s0 = 0;
    var_t5 = 0;
    var_ra = D_80129FC8.unk0 + 1;
    for (i = 0; i < D_80129FC8.unk0; i++) {
        for (j = 0; j < D_80129FC8.unk0; j++) {
            for (k = 0; k < var_t2; k++) {
                gWaveTriangles[D_8012A018][k << 1][var_s0].uv0.u = D_800E3048[var_t5].u;
                gWaveTriangles[D_8012A018][k << 1][var_s0].uv0.v = D_800E3048[var_t5 + 1].v;
                gWaveTriangles[D_8012A018][k << 1][var_s0].uv1.u = D_800E3048[var_ra].u;
                gWaveTriangles[D_8012A018][k << 1][var_s0].uv1.v = D_800E3048[var_ra].v;
                gWaveTriangles[D_8012A018][k << 1][var_s0].uv2.u = D_800E3048[var_t5 + 1].u;
                gWaveTriangles[D_8012A018][k << 1][var_s0].uv2.v = D_800E3048[var_t5 + 1].v;
                gWaveTriangles[D_8012A018][k << 1][var_s0 + 1].uv0.u = D_800E3048[var_t5 + 1].u;
                gWaveTriangles[D_8012A018][k << 1][var_s0 + 1].uv0.v = D_800E3048[var_t5 + 1].v;
                gWaveTriangles[D_8012A018][k << 1][var_s0 + 1].uv1.u = D_800E3048[var_ra].u;
                gWaveTriangles[D_8012A018][k << 1][var_s0 + 1].uv1.v = D_800E3048[var_ra + 1].v;
                gWaveTriangles[D_8012A018][k << 1][var_s0 + 1].uv2.u = D_800E3048[var_ra + 1].u;
                gWaveTriangles[D_8012A018][k << 1][var_s0 + 1].uv2.v = D_800E3048[var_ra + 1].v;
            }
            var_t5++;
            var_ra++;
            var_s0 += 2;
        }
        var_t5++;
        var_ra++;
    }

    D_800E3090[2 * D_8012A018].uv0.u = D_800E3048[0].u;
    D_800E3090[2 * D_8012A018].uv0.v = D_800E3048[0].v;
    D_800E3090[2 * D_8012A018].uv1.u = D_800E3048[D_80129FC8.unk0 * (D_80129FC8.unk0 + 1)].u;
    D_800E3090[2 * D_8012A018].uv1.v = D_800E3048[D_80129FC8.unk0 * (D_80129FC8.unk0 + 1)].v;
    D_800E3090[2 * D_8012A018].uv2.u = D_800E3048[D_80129FC8.unk0].u;
    D_800E3090[2 * D_8012A018].uv2.v = D_800E3048[D_80129FC8.unk0].v;
    D_800E3090[2 * D_8012A018 + 1].uv0.u = D_800E3048[D_80129FC8.unk0].u;
    D_800E3090[2 * D_8012A018 + 1].uv0.v = D_800E3048[D_80129FC8.unk0].v;
    D_800E3090[2 * D_8012A018 + 1].uv1.u = D_800E3048[D_80129FC8.unk0 * (D_80129FC8.unk0 + 1)].u;
    D_800E3090[2 * D_8012A018 + 1].uv1.v = D_800E3048[D_80129FC8.unk0 * (D_80129FC8.unk0 + 1)].v;
    D_800E3090[2 * D_8012A018 + 1].uv2.u = D_800E3048[D_80129FC8.unk0 * (D_80129FC8.unk0 + 1) + D_80129FC8.unk0].u;
    D_800E3090[2 * D_8012A018 + 1].uv2.v = D_800E3048[D_80129FC8.unk0 * (D_80129FC8.unk0 + 1) + D_80129FC8.unk0].v;

    if (D_800E3188 > 0) {
        func_800BFE98(arg0);
    }

    if (gWavePowerDivisor <= 0) {
        return;
    }

    if (arg0 < gWavePowerDivisor) {
        D_80129FC8.magnitude += (f32) arg0 * gWaveMagnitude;
        gWavePowerDivisor -= arg0;
    } else {
        D_80129FC8.magnitude = gWavePowerBase;
        gWavePowerDivisor = 0;
    }
}

void func_800BA288(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;

    arg1 <<= 3;
    for (i = 0; i < gNumberOfLevelSegments; i++) {
        if (D_8012A0E8[D_800E30D8[i].unkB] & (1 << D_800E30D8[i].unkA)) {
            if (D_80129FC8.unk28 != FALSE) {
                for (j = 0; j < 4; j++) {
                    if (D_800E30D4[D_800E30D8[i].unkC] & (0xFF << (j << 3))) {
                        if (arg1 < D_800E30D8[i].unk14[arg0].unk0[j]) {
                            D_800E30D8[i].unk14[arg0].unk0[j] -= arg1;
                        } else {
                            D_800E30D8[i].unk14[arg0].unk0[j] = 0;
                        }
                    } else {
                        if ((D_800E30D8[i].unk14[arg0].unk0[j] + arg1) < 0x80) {
                            D_800E30D8[i].unk14[arg0].unk0[j] += arg1;
                        } else {
                            D_800E30D8[i].unk14[arg0].unk0[j] = 0x80;
                        }
                    }
                }
            } else {
                if (D_800E30D4[D_800E30D8[i].unkC]) {
                    if (arg1 < D_800E30D8[i].unk14[arg0].unk0[0]) {
                        D_800E30D8[i].unk14[arg0].unk0[0] -= arg1;
                    } else {
                        D_800E30D8[i].unk14[arg0].unk0[0] = 0;
                    }
                } else {
                    if (D_800E30D8[i].unk14[arg0].unk0[0] + arg1 < 0x80) {
                        D_800E30D8[i].unk14[arg0].unk0[0] += arg1;
                    } else {
                        D_800E30D8[i].unk14[arg0].unk0[0] = 0x80;
                    }
                }
            }
        }
    }
}

void func_800BA4B8(TextureHeader *tex, s32 rtile) {
    s32 txmask;
    s32 tmem;
    u32 texWidth;

    texWidth = tex->width;
    tmem = 0;
    if (texWidth == 16) {
        txmask = 4;
        if (rtile != G_TX_RENDERTILE) {
            tmem = 384;
        }
    } else if (texWidth == 32) {
        txmask = 5;
        if (rtile != G_TX_RENDERTILE) {
            tmem = 256;
        }
    } else {
        //!@bug: txmask is not set, so it's value will be UB. I wonder if they accidentally set the width to 3 instead
        //! of the mask?
        texWidth = 3;
        if (rtile != G_TX_RENDERTILE) {
            tmem = 384;
        }
    }

    // difference is G_IM_SIZ_32b vs G_IM_SIZ_16b
    if ((tex->format & 0xF) == TEX_FORMAT_RGBA32) {
        gDPLoadMultiBlock(gWaveDL++, OS_PHYSICAL_TO_K0(tex + 1), tmem, rtile, G_IM_FMT_RGBA, G_IM_SIZ_32b, texWidth,
                          texWidth, 0, 0, 0, txmask, txmask, 0, 0);
    } else {
        gDPLoadMultiBlock(gWaveDL++, OS_PHYSICAL_TO_K0(tex + 1), tmem, rtile, G_IM_FMT_RGBA, G_IM_SIZ_16b, texWidth,
                          texWidth, 0, 0, 0, txmask, txmask, 0, 0);
    }
}

void func_800BA8E4(Gfx **dList, MatrixS **mtx, s32 arg2) {
    s32 sp11C;
    Vertex *vtx;
    Triangle *tri;
    s32 numTris;
    s32 numVerts;
    s32 j;
    s32 sp104;
    s32 var_fp;
    s32 var_t0;
    ObjectTransform spE4;
    LevelModel_Alternate *spE0;
    s32 i;
    TextureHeader *tex1;
    TextureHeader *tex2;

    if ((arg2 != 1) || (D_8012A078 != 2)) {
        arg2 = 0;
    } else {
        arg2 = 2;
    }

    if (D_800E30DC > 0) {
        gWaveDL = *dList;
        D_80129FC4 = *mtx;
        i = 0;
        rendermode_reset(&gWaveDL);
        gSPSetGeometryMode(gWaveDL++, G_ZBUFFER);
        if (D_80129FC8.darkVertexColours) {
            gSPClearGeometryMode(gWaveDL++, G_FOG);
            tex1 = set_animated_texture_header(gWaveTextureHeader, D_8012A09C << 8);
            tex2 = set_animated_texture_header(gWaveTexture, gWaveBatch->unk7 << 14);
            func_800BA4B8(tex1, 1);
            func_800BA4B8(tex2, 0);
            gDPSetCombineMode(gWaveDL++, DKR_CC_UNK14, DKR_CC_UNK15);
            if ((tex1->format & 0xF) == TEX_FORMAT_RGBA32 && get_viewport_count() <= 0) {
                gDPSetOtherMode(gWaveDL++, DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_INTER2);
            } else {
                gDPSetOtherMode(gWaveDL++, DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_OPA_SURF2);
            }
            gDPSetPrimColor(gWaveDL++, 0, 0, 255, 255, 255, 0);
            if (D_800E3180 != NULL) {
                gDPSetEnvColor(gWaveDL++, D_800E3180->red, D_800E3180->green, D_800E3180->blue, D_800E3180->alpha);
            } else {
                gDPSetEnvColor(gWaveDL++, 255, 255, 255, 0);
            }
        } else {
            gSPSetGeometryMode(gWaveDL++, G_FOG);
            tex1 = set_animated_texture_header(gWaveTexture, gWaveBatch->unk7 << 14);
            gDkrDmaDisplayList(gWaveDL++, OS_K0_TO_PHYSICAL(tex1->cmd), tex1->numberOfCommands);
            gDPSetCombineMode(gWaveDL++, DKR_CC_UNK16, DKR_CC_UNK8);
            gDPSetOtherMode(gWaveDL++, DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2);
            gDPSetPrimColor(gWaveDL++, 0, 0, 255, 255, 255, 255);
            if (D_800E3180 != NULL) {
                gDPSetEnvColor(gWaveDL++, D_800E3180->red, D_800E3180->green, D_800E3180->blue, D_800E3180->alpha);
            } else {
                gDPSetEnvColor(gWaveDL++, 255, 255, 255, 0);
            }
        }
        if (D_80129FC8.unk28) {
            spE4.scale = 0.5f;
        } else {
            spE4.scale = 1.0f;
        }

        spE4.rotation.x = spE4.rotation.y = spE4.rotation.z = 0;
        for (; i < D_800E30DC; i++) {
            if (D_80129FC8.darkVertexColours) {
                func_800B92F4(D_8012A1E8[i], arg2);
            } else {
                func_800B97A8(D_8012A1E8[i], arg2);
            }
            spE0 = &D_800E30D8[D_8012A1E8[i]];
            spE4.x_position = spE0->unk4;
            spE4.y_position = spE0->unk6;
            spE4.z_position = spE0->unk8;
            sp104 = D_800E30D4[spE0->unkC];
            if (D_80129FC8.unk28) {
                for (sp11C = 0; sp11C < 2; sp11C++) {
                    spE4.x_position = spE0->unk4;
                    for (var_fp = 0; var_fp < 2; var_fp++) {
                        camera_push_model_mtx(&gWaveDL, &D_80129FC4, &spE4, 1.0f, 0.0f);
                        if (sp104 & 0xFF) {
                            numTris = D_80129FC8.unk0 << 1;
                            numVerts = D_80129FC8.unk0 + 1;
                            var_t0 = ((sp104 & 0xFF) - 1) * numVerts * numVerts;
                            for (j = 0; j < D_80129FC8.unk0; j++) {
                                vtx = &gWaveVertices[D_8012A018 + arg2][0][var_t0];
                                tri = &gWaveTriangles[D_8012A018 + arg2][0][j * (D_80129FC8.unk0 << 1)];

                                gSPVertexDKR(gWaveDL++, OS_K0_TO_PHYSICAL(vtx), numVerts << 1, 0);
                                gSPPolygon(gWaveDL++, OS_K0_TO_PHYSICAL(tri), numTris, TRIN_ENABLE_TEXTURE);

                                var_t0 += D_80129FC8.unk0 + 1;
                            }
                        } else {
                            gSPVertexDKR(gWaveDL++, OS_K0_TO_PHYSICAL(&D_8012A028[D_8012A018]), 4, 0);
                            gSPPolygon(gWaveDL++, OS_K0_TO_PHYSICAL(&D_800E3090[D_8012A018 << 1]), 2,
                                       TRIN_ENABLE_TEXTURE);
                        }
                        apply_matrix_from_stack(&gWaveDL);
                        sp104 >>= 8;
                        spE4.x_position += D_8012A0A0 * 0.5f;
                    }
                    spE4.z_position += D_8012A0A4 * 0.5f;
                }
            } else {
                camera_push_model_mtx(&gWaveDL, &D_80129FC4, &spE4, 1.0f, 0.0f);
                numTris = D_80129FC8.unk0 << 1;
                numVerts = D_80129FC8.unk0 + 1;
                var_t0 = ((sp104 & 0xFF) - 1) * numVerts * numVerts;
                for (j = 0; j < D_80129FC8.unk0; j++) {
                    vtx = &gWaveVertices[D_8012A018 + arg2][0][var_t0];
                    tri = &gWaveTriangles[D_8012A018 + arg2][0][j * (D_80129FC8.unk0 << 1)];

                    gSPVertexDKR(gWaveDL++, OS_K0_TO_PHYSICAL(vtx), numVerts << 1, 0);
                    gSPPolygon(gWaveDL++, OS_K0_TO_PHYSICAL(tri), numTris, TRIN_ENABLE_TEXTURE);

                    var_t0 += D_80129FC8.unk0 + 1;
                }
                apply_matrix_from_stack(&gWaveDL);
            }
        }
        if (D_80129FC8.darkVertexColours) {
            gSPSetGeometryMode(gWaveDL++, G_FOG);
            gDPSetPrimColor(gWaveDL++, 0, 0, 255, 255, 255, 255);
        }
        *dList = gWaveDL;
        *mtx = D_80129FC4;
    }
    D_800E30DC = 0;
}

f32 func_800BB2F4(s32 arg0, f32 arg1, f32 arg2, Vec3f *arg3) {
    f32 spA4;
    f32 spA0;
    f32 var_f12;
    f32 var_f2;
    f32 sp94;
    f32 sp90;
    f32 var_f16;
    f32 arg3X;
    f32 arg3Y;
    f32 arg3Z;
    s32 var_a0;
    f32 sp78;
    s32 var_v0;
    s32 sp70;
    s32 sp6C;
    s32 var_t0;
    s32 var_a3;
    s32 sp60;
    u8 *tempD_800E3178;
    s32 sp58;
    s32 pad;

    if (arg0 < 0 || arg0 >= gNumberOfLevelSegments) {
        arg0 = 0;
    }

    sp78 = D_800E30D8[arg0].unk6;

    sp90 = D_8012A0BC;
    sp94 = D_8012A0B8;
    var_f16 = (1.0f - D_80129FC8.unk44) / 127.0f;
    sp58 = arg0 * D_800E317C;

    if (D_80129FC8.unk28 != FALSE) {
        sp90 *= 0.5f;
        sp94 *= 0.5f;
        sp60 = (D_80129FC8.unk0 * 2) + 1;
    } else {
        sp60 = D_80129FC8.unk0 + 1;
    }

    arg1 -= D_800E30D8[arg0].unk4;
    if (arg1 < 0.0f) {
        arg1 = 0.0f;
    } else if (D_8012A0A0 <= arg1) {
        arg1 = D_8012A0A0 - 1; // needs to be 1 instead of 1.0f
    }

    arg2 -= D_800E30D8[arg0].unk8;
    if (arg2 < 0.0f) {
        arg2 = 0.0f;
    } else if (D_8012A0A4 <= arg2) {
        arg2 = D_8012A0A4 - 1; // needs to be 1 instead of 1.0f
    }

    sp70 = arg1 / sp94;
    sp6C = arg2 / sp90;
    arg1 -= sp70 * sp94;
    arg2 -= sp6C * sp90;

    var_t0 = D_800E30D8[arg0].unk12 + sp70;
    while (var_t0 >= D_80129FC8.unk4) {
        var_t0 -= D_80129FC8.unk4;
    }

    var_a3 = D_800E30D8[arg0].unk10 + sp6C;
    while (var_a3 >= D_80129FC8.unk4) {
        var_a3 -= D_80129FC8.unk4;
    }

    var_v0 = 0;
    if (arg2 != sp90 && arg1 < (((sp90 - arg2) / sp90) * sp94)) {
        var_v0 = 1;
    }

    if (var_v0) {
        var_a0 = (var_a3 * D_80129FC8.unk4) + var_t0;
        spA0 = (D_800E3040[D_800E3044[var_a0].s[0]] + D_800E3040[D_800E3044[var_a0].s[1]]) * D_80129FC8.magnitude;
        var_a0 = sp58 + sp70 + (sp6C * sp60);
        if (D_800E3188 > 0) {
            spA0 += func_800BEFC4(arg0, sp70, sp6C);
        }

        var_v0 = D_800E3178[var_a0];
        if (D_800E3178[var_a0] < 0x7F) {
            spA0 *= D_80129FC8.unk44 + (var_v0 * var_f16);
        }

        var_a0 = (var_a3 + 1) >= D_80129FC8.unk4 ? var_t0 : ((var_a3 + 1) * D_80129FC8.unk4) + var_t0;
        var_f12 = (D_800E3040[D_800E3044[var_a0].s[0]] + D_800E3040[D_800E3044[var_a0].s[1]]) * D_80129FC8.magnitude;
        if (D_800E3188 > 0) {
            var_f12 += func_800BEFC4(arg0, sp70, sp6C + 1);
        }
        var_a0 = sp58 + sp70 + ((sp6C + 1) * sp60);
        var_v0 = D_800E3178[var_a0];
        if (D_800E3178[var_a0] < 0x7F) {
            var_f12 *= D_80129FC8.unk44 + (var_v0 * var_f16);
        }

        if ((var_t0 + 1) >= D_80129FC8.unk4) {
            var_a0 = var_a3 * D_80129FC8.unk4;
        } else {
            var_a0 = (var_t0 + 0) + (var_a3 * D_80129FC8.unk4) + 1;
        }
        var_f2 = (D_800E3040[D_800E3044[var_a0].s[0]] + D_800E3040[D_800E3044[var_a0].s[1]]) * D_80129FC8.magnitude;
        if (D_800E3188 > 0) {
            var_f2 += func_800BEFC4(arg0, sp70 + 1, sp6C);
        }
        var_a0 = sp58 + sp70 + (sp6C * sp60);
        var_a0++;
        var_v0 = D_800E3178[var_a0];
        if (D_800E3178[var_a0] < 0x7F) {
            var_f2 *= D_80129FC8.unk44 + (var_v0 * var_f16);
        }

        if (D_80129FC8.unk28 != FALSE) {
            spA0 *= 0.5f;
            var_f12 *= 0.5f;
            var_f2 *= 0.5f;
        }

        spA4 = 0.0f;
        arg3X = (spA0 - var_f2) * sp90;
        arg3Y = sp90 * sp94;
        arg3Z = (spA0 - var_f12) * sp94;
    } else {
        if ((var_t0 + 1) >= D_80129FC8.unk4) {
            var_a0 = var_a3 * D_80129FC8.unk4;
        } else {
            var_a0 = (var_t0 + 0) + (var_a3 * D_80129FC8.unk4) + 1;
        }
        spA0 = (D_800E3040[D_800E3044[var_a0].s[0]] + D_800E3040[D_800E3044[var_a0].s[1]]) * D_80129FC8.magnitude;
        if (D_800E3188 > 0) {
            spA0 += func_800BEFC4(arg0, sp70 + 1, sp6C);
        }
        var_a0 = sp58 + sp70 + (sp6C * sp60);
        var_a0++;
        var_v0 = D_800E3178[var_a0];
        if (D_800E3178[var_a0] < 0x7F) {
            spA0 *= D_80129FC8.unk44 + (var_v0 * var_f16);
        }

        var_a0 = (var_a3 + 1) >= D_80129FC8.unk4 ? var_t0 : ((var_a3 + 1) * D_80129FC8.unk4) + var_t0;
        var_f12 = (D_800E3040[D_800E3044[var_a0].s[0]] + D_800E3040[D_800E3044[var_a0].s[1]]) * D_80129FC8.magnitude;
        if (D_800E3188 > 0) {
            var_f12 += func_800BEFC4(arg0, sp70, sp6C + 1);
        }
        var_a0 = sp58 + sp70 + ((sp6C + 1) * sp60);
        var_v0 = (tempD_800E3178 = D_800E3178)[var_a0];
        if (var_v0 < 0x7F) {
            var_f12 *= D_80129FC8.unk44 + (var_v0 * var_f16);
        }

        var_a0 = (var_t0 + 1) >= D_80129FC8.unk4 ? 0 : (var_t0 + 1);
        if ((var_a3 + 1) < D_80129FC8.unk4) {
            var_a0 += (var_a3 + 1) * D_80129FC8.unk4;
        }

        var_f2 = (D_800E3040[D_800E3044[var_a0].s[0]] + D_800E3040[D_800E3044[var_a0].s[1]]) * D_80129FC8.magnitude;
        if (D_800E3188 > 0) {
            var_f2 += func_800BEFC4(arg0, sp70 + 1, sp6C + 1);
        }
        var_a0 = sp58 + sp70 + ((sp6C + 1) * sp60);
        var_a0++;
        var_v0 = D_800E3178[var_a0];
        if (var_v0 < 0x7F) {
            var_f2 *= D_80129FC8.unk44 + (var_v0 * var_f16);
        }

        if (D_80129FC8.unk28 != FALSE) {
            spA0 *= 0.5f;
            var_f12 *= 0.5f;
            var_f2 *= 0.5f;
        }

        spA4 = sp94;
        arg3X = sp90 * (var_f12 - var_f2);
        arg3Y = sp90 * sp94;
        arg3Z = sp94 * (spA0 - var_f2);
    }

    var_f16 = sqrtf((arg3X * arg3X) + (arg3Y * arg3Y) + (arg3Z * arg3Z));
    if (var_f16 != 0.0 && arg3Y != 0.0) {
        arg3X /= var_f16;
        arg3Y /= var_f16;
        arg3Z /= var_f16;
        sp78 -= (((arg3X * arg1) + (arg3Z * arg2)) - ((spA4 * arg3X) + (spA0 * arg3Y))) / arg3Y;
    }

    if (arg3 != NULL) {
        arg3->x = arg3X;
        arg3->y = arg3Y;
        arg3->z = arg3Z;
    }

    return sp78;
}

void func_800BBDDC(LevelModel *level, LevelHeader *header) {
    func_800BBE08(level, header);
    func_800BBF78(level);
}

// determines current bounding box, batch and texture
void func_800BBE08(LevelModel *level, LevelHeader *header) {
    s16 numSegments;
    s32 j;
    TriangleBatchInfo *curBatch;
    s32 i;
    s32 temp_t6;
    LevelModelSegmentBoundingBox *bb;
    LevelModelSegment *segment;

    numSegments = level->numberOfSegments;
    curBatch = 0;

    for (i = 0; curBatch == 0 && i < numSegments; i++) {
        segment = &level->segments[i];
        for (j = 0; curBatch == 0 && j < segment->numberOfBatches; j++) {
            if ((segment->batches[j].flags & (BATCH_FLAGS_UNK01000000 | BATCH_FLAGS_WATER | BATCH_FLAGS_HIDDEN)) ==
                (BATCH_FLAGS_UNK01000000 | BATCH_FLAGS_WATER)) {
                curBatch = &segment->batches[j];
            }
        }
    }

    if (curBatch == 0) {
        i = 0;
    } else {
        i--;
    }
    bb = &level->segmentsBoundingBoxes[i];
    gWaveBoundingBoxDiffX = bb->x2 - bb->x1;
    gWaveBoundingBoxDiffZ = bb->z2 - bb->z1;
    gWaveBoundingBoxX1 = bb->x1;
    gWaveBoundingBoxZ1 = bb->z1;
    gWaveBatch = curBatch;
    gWaveTexture = level->textures[curBatch->textureIndex].texture;
    temp_t6 = (curBatch->flags & (BATCH_FLAGS_UNK40000000 | BATCH_FLAGS_UNK20000000 | BATCH_FLAGS_UNK10000000)) >> 28;
    if (temp_t6 > 0) {
        D_800E3180 = header->unk70[temp_t6];
    } else {
        D_800E3180 = 0;
    }
}

void func_800BBF78(LevelModel *model) {
    LevelModelSegmentBoundingBox *levelSegmentBoundingBoxes;
    s32 j;
    s32 temp_t1;
    s32 segmentVertexY;
    s32 temp_t2;
    s32 pad;
    s32 sp44;
    LevelModelSegment *levelSegments;
    s32 i;
    s32 var_v0;
    LevelModel_Alternate *otherModel;

    levelSegments = model->segments;
    levelSegmentBoundingBoxes = model->segmentsBoundingBoxes;
    sp44 = D_80129FC8.unk0;
    if (D_80129FC8.unk28 != FALSE) {
        sp44 = sp44 * 2;
    }
    D_8012A0C0 = levelSegmentBoundingBoxes->x1;
    D_8012A0C8 = levelSegmentBoundingBoxes->x2;
    D_8012A0C4 = levelSegmentBoundingBoxes->z1;
    D_8012A0CC = levelSegmentBoundingBoxes->z2;
    for (i = 1; i < model->numberOfSegments; i++) {
        if (levelSegmentBoundingBoxes[i].x1 < D_8012A0C0) {
            D_8012A0C0 = levelSegmentBoundingBoxes[i].x1;
        }
        if (D_8012A0C8 < levelSegmentBoundingBoxes[i].x2) {
            D_8012A0C8 = levelSegmentBoundingBoxes[i].x2;
        }
        if (levelSegmentBoundingBoxes[i].z1 < D_8012A0C4) {
            D_8012A0C4 = levelSegmentBoundingBoxes[i].z1;
        }
        if (D_8012A0CC < levelSegmentBoundingBoxes[i].z2) {
            D_8012A0CC = levelSegmentBoundingBoxes[i].z2;
        }
    }

    D_8012A0D0 = gWaveBoundingBoxX1;
    while (D_8012A0C0 < D_8012A0D0) {
        D_8012A0D0 -= gWaveBoundingBoxDiffX;
    }

    D_8012A0D4 = gWaveBoundingBoxZ1;
    while (D_8012A0C4 < D_8012A0D4) {
        D_8012A0D4 -= gWaveBoundingBoxDiffZ;
    }

    D_8012A0D8 = ((D_8012A0C8 - D_8012A0D0) / gWaveBoundingBoxDiffX) + 1;
    D_8012A0DC = ((D_8012A0CC - D_8012A0D4) / gWaveBoundingBoxDiffZ) + 1;
    D_800E318C = (sp44 * D_8012A0D8) + 1;

    if (D_800E30D4 != NULL) {
        mempool_free(D_800E30D4);
    }
    D_800E30D4 = mempool_alloc_safe(D_8012A0D8 * D_8012A0DC * 4, 0xFFFFFF);

    if (D_800E30D8 != NULL) {
        mempool_free(D_800E30D8);
    }

    // clang-format off
    D_800E30D8 = mempool_alloc_safe(
        (model->numberOfSegments * sizeof(LevelModel_Alternate)) + (D_800E318C * 8) + 0x880,
        0xFFFFFF
    );
    // clang-format on

    D_800E3190 = (unk800E3190 *) ((u32) D_800E30D8 + model->numberOfSegments * sizeof(LevelModel_Alternate));
    D_800E3194 = (Object **) (D_800E3190 + sizeof(unk800E3190 *) * 8);
    D_800E3184 = (unk800E3184 *) (D_800E3194 + sizeof(Object *) * 8);

    for (i = 0; i < (D_800E318C * 8); i++) {
        D_800E3184->unk0[i] = 0xFF;
    }

    // 0x20 / 32 sizeof what?
    for (i = 0; i < 32; i++) {
        D_800E3194[i] = 0;
    }

    D_800E3188 = 0;

    for (i = 0; i < (D_8012A0D8 * D_8012A0DC); i++) {
        D_800E30D4[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_8012A0E8); i++) {
        D_8012A0E8[i] = 0;
    }

    gNumberOfLevelSegments = model->numberOfSegments;
    for (i = 0; i < gNumberOfLevelSegments; i++) {
        temp_t1 = levelSegmentBoundingBoxes[i].x1 - D_8012A0D0 + 8;
        temp_t2 = levelSegmentBoundingBoxes[i].z1 - D_8012A0D4 + 8;
        temp_t1 = ((temp_t1 / gWaveBoundingBoxDiffX) * gWaveBoundingBoxDiffX) + D_8012A0D0;
        temp_t2 = ((temp_t2 / gWaveBoundingBoxDiffZ) * gWaveBoundingBoxDiffZ) + D_8012A0D4;
        segmentVertexY = 0;
        for (j = 0; j < levelSegments[i].numberOfBatches; j++) {
            if ((levelSegments[i].batches[j].flags & 0x2000) && (levelSegments[i].batches[j].flags & 0x400000)) {
                segmentVertexY = levelSegments[i].vertices[levelSegments[i].batches[j].verticesOffset].y;
            }
        }

        otherModel = &D_800E30D8[i];
        otherModel->unk00 = &levelSegments[i];
        otherModel->unk4 = temp_t1;
        otherModel->unk6 = segmentVertexY;
        otherModel->unk8 = temp_t2;
        otherModel->unkA = (temp_t1 - D_8012A0D0) / gWaveBoundingBoxDiffX;
        otherModel->unkB = (temp_t2 - D_8012A0D4) / gWaveBoundingBoxDiffZ;
        otherModel->unkC = otherModel->unkA + (otherModel->unkB * D_8012A0D8);
        otherModel->unk12 = 0;
        otherModel->unk10 = 0;
        if (levelSegments[i].hasWaves != 0) {
            var_v0 = otherModel->unkA * sp44;
            while (var_v0 >= D_80129FC8.unk4) {
                var_v0 -= D_80129FC8.unk4;
            }
            otherModel->unk12 = var_v0;
            var_v0 = otherModel->unkB * sp44;
            while (var_v0 >= D_80129FC8.unk4) {
                var_v0 -= D_80129FC8.unk4;
            }
            otherModel->unk10 = var_v0;
            D_8012A0E8[otherModel->unkB] |= (1 << otherModel->unkA);
        }

        for (j = 0; j < 4; j++) {
            otherModel->unk14[0].unk0[j] = 0x80;
            otherModel->unk14[1].unk0[j] = 0x80;
        }
    }
}

void func_800BC6C8(void) {
    s32 i;
    s32 j;
    s32 k;
    s32 var_s0;
    s32 var_v0;
    f32 sp34[0x80];

    var_v0 = 0x4000 / D_80129FC8.unk0;
    var_s0 = 0;
    for (i = 0; i < D_80129FC8.unk0;) {
        sp34[i++] = sins_f(var_s0);
        var_s0 += var_v0;
    }
    sp34[0] = 0.0f;
    sp34[D_80129FC8.unk0] = 1.0f;

    k = 0;
    for (i = 0; i <= D_80129FC8.unk0; i++) {
        for (j = 0; j <= D_80129FC8.unk0; j++) {
            D_800E304C[4][k] = 1.0f;
            k++;
        }
    }

    k = 0;
    for (i = 0; i <= D_80129FC8.unk0; i++) {
        for (j = 0; j <= D_80129FC8.unk0; j++) {
            D_800E304C[1][k] = sp34[i];
            k++;
        }
    }

    k = 0;
    for (i = 0; i <= D_80129FC8.unk0; i++) {
        for (j = 0; j <= D_80129FC8.unk0;) {
            D_800E304C[3][k++] = sp34[j++];
        }
    }

    k = 0;
    for (i = 0; i <= D_80129FC8.unk0; i++) {
        for (j = 0; j <= D_80129FC8.unk0;) {
            D_800E304C[5][k++] = sp34[D_80129FC8.unk0 - j++];
        }
    }

    k = 0;
    for (i = 0; i <= D_80129FC8.unk0; i++) {
        for (j = 0; j <= D_80129FC8.unk0; j++) {
            D_800E304C[7][k] = sp34[D_80129FC8.unk0 - i];
            k++;
        }
    }

    for (i = 0; i <= D_80129FC8.unk0; i++) {
        for (j = i; j <= D_80129FC8.unk0; j++) {
            D_800E304C[0][i * (D_80129FC8.unk0 + 1) + j] = sp34[i];
            D_800E304C[0][j * (D_80129FC8.unk0 + 1) + i] = sp34[i];
        }
    }

    for (i = 0; i <= D_80129FC8.unk0; i++) {
        for (j = i; j <= D_80129FC8.unk0; j++) {
            D_800E304C[2][(i * (D_80129FC8.unk0 + 1)) + D_80129FC8.unk0 - j] = sp34[i];
            D_800E304C[2][(j * (D_80129FC8.unk0 + 1)) + D_80129FC8.unk0 - i] = sp34[i];
        }
    }

    for (i = 0; i <= D_80129FC8.unk0; i++) {
        for (j = i; j <= D_80129FC8.unk0; j++) {
            D_800E304C[6][(D_80129FC8.unk0 * (D_80129FC8.unk0 + 1)) - (i * (D_80129FC8.unk0 + 1)) + j] = sp34[i];
            D_800E304C[6][(D_80129FC8.unk0 * (D_80129FC8.unk0 + 1)) - (j * (D_80129FC8.unk0 + 1)) + i] = sp34[i];
        }
    }

    for (i = 0; i <= D_80129FC8.unk0; i++) {
        for (j = i; j <= D_80129FC8.unk0; j++) {
            // clang-format off
            D_800E304C[8][(D_80129FC8.unk0 * (D_80129FC8.unk0 + 1)) - (i * (D_80129FC8.unk0 + 1)) + D_80129FC8.unk0 - j] = sp34[i];
            D_800E304C[8][(D_80129FC8.unk0 * (D_80129FC8.unk0 + 1)) - (j * (D_80129FC8.unk0 + 1)) + D_80129FC8.unk0 - i] = sp34[i];
            // clang-format on
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/waves/func_800BCC70.s")

#ifdef NON_EQUIVALENT
typedef struct unkArg1 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
} unkArg1;

typedef struct unkArg2 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} unkArg2;

// arg0
// arg1 is s32 D_8011C3B8[320]; according to func_8002EEEC
// arg2 might be s32 D_8011C8B8[512]

s32 func_800BDC80(s32 arg0, unkArg1 *arg1, unkArg2 *arg2, f32 shadowXNegPosition, f32 shadowZNegPosition,
                  f32 shadowXPosition, f32 shadowZPosition) {
    s32 sp36C;
    s32 sp368;
    s32 sp364;
    f32 var_f0;
    f32 var_f12;
    s32 sp358;
    s32 sp354;
    f32 var_f14;
    s32 sp34C;
    f32 var_f16;
    f32 var_f18;
    f32 var_f24;
    f32 var_f26;
    f32 var_f28;
    f32 var_f20;
    s16 var_a1; // sp332
    f32 var_f22;
    s16 var_s8;
    s16 var_s2_s16;
    s16 var_s3_2;
    s32 var_s5;
    s32 var_a2_2;
    s32 var_lo;
    s32 var_lo_2;
    s32 var_s0;
    s32 var_s1;
    s32 var_v1;
    s32 var_s6;
    s32 var_t0;
    s32 temp1_2;
    s32 temp2_2;
    s16 spD8[0x110]; // probably incorrect size
    s32 var_s2;
    s32 var_s4;
    f32 spCC;
    f32 spC8;
    s32 var_v0;
    s32 spA4;
    unkArg2 *var_v0_4;
    s32 sp98;
    unkArg1 *var_s0_2;
    s32 sp90;
    s32 temp3_2;
    s32 temp4_2;
    s32 var_s7; // sp74
    s32 var_t8;

    var_t0 = (arg0 * D_800E317C);
    spCC = D_8012A0B8;
    spC8 = D_8012A0BC;
    var_f24 = (1.0f - D_80129FC8.unk44) / 127.0f;
    if (D_80129FC8.unk28 != FALSE) {
        sp36C = D_80129FC8.unk0 * 2;
        spCC *= 0.5;
        spC8 *= 0.5;
        var_f22 = 0.5f;
    } else {
        var_f22 = 1.0f;
        sp36C = D_80129FC8.unk0;
    }

    var_f12 = shadowXNegPosition - D_800E30D8[arg0].unk4;
    var_f14 = shadowZNegPosition - D_800E30D8[arg0].unk8;
    var_f16 = shadowXPosition - D_800E30D8[arg0].unk4;
    var_f18 = shadowZPosition - D_800E30D8[arg0].unk8;

    if (var_f12 < 0.0f) {
        sp368 = 0;
    } else {
        sp368 = var_f12 / spCC;
    }

    if (var_f14 < 0.0f) {
        sp364 = 0;
    } else {
        sp364 = var_f14 / spC8;
    }

    if (D_8012A0A0 <= var_f16) {
        sp358 = sp36C;
    } else {
        sp358 = (s32) (var_f16 / spCC) + 1;
    }

    if (D_8012A0A4 <= var_f18) {
        sp354 = sp36C;
    } else {
        sp354 = (s32) (var_f18 / spCC) + 1;
    }

    var_v1 = D_800E30D8[arg0].unk12 + sp368;
    while (var_v1 >= D_80129FC8.unk4) {
        var_v1 -= D_80129FC8.unk4;
    }

    var_v0 = D_800E30D8[arg0].unk10 + sp364;
    while (var_v0 >= D_80129FC8.unk4) {
        var_v0 -= D_80129FC8.unk4;
    }

    var_s6 = sp364;
    var_s7 = 0;
    if (sp354 >= sp364) {
        spA4 = var_t0 + sp368 + (sp364 * sp36C);
        sp90 = sp354 + 1;
        sp34C = var_v0;
        do {
            var_s4 = spA4;
            var_s0 = var_v1;
            var_s2 = (sp34C * D_80129FC8.unk4) + var_v1;
            if (sp358 >= sp368) {
                var_s1 = sp368;
                var_s5 = sp358 + 1;
                do {
                    var_f20 = (D_800E3040[D_800E3044[var_s2].s[0]] + D_800E3040[D_800E3044[var_s2].s[1]]) *
                              D_80129FC8.magnitude;
                    if (D_800E3188 > 0) {
                        var_f20 += func_800BEFC4(arg0, var_s1, var_s6);
                    }
                    if (D_800E3178[var_s4] < 0x7F) {
                        // s32 cast below required
                        var_f20 *= D_80129FC8.unk44 + ((s32) D_800E3178[var_s4] * var_f24);
                    }
                    var_s1++;
                    var_s7++;
                    var_s0++;
                    var_s4++;
                    var_s2++;
                    spD8[var_s7 - 1] = D_800E30D8[arg0].unk6 + (s32) (var_f20 * var_f22);
                    if (var_s0 >= D_80129FC8.unk4) {
                        var_s0 -= D_80129FC8.unk4;
                        var_s2 -= D_80129FC8.unk4;
                    }
                } while (var_s5 != var_s1);
            }
            sp34C++;
            if (sp34C >= D_80129FC8.unk4) {
                sp34C -= D_80129FC8.unk4;
            }
            spA4 += sp36C;
            var_s6++;
        } while (sp90 != var_s6);
    }

    var_s7 = 0;
    sp36C = (sp358 - sp368) + 1;
    var_a1 = D_800E30D8[arg0].unk8 + (s32) (sp364 * spC8);
    if (sp364 < sp354) {
        sp98 = sp368 * spCC;
        var_s6 = sp364;
        do {
            var_s8 = D_800E30D8[arg0].unk8 + (s32) ((var_s6 + 1) * spC8);
            var_s3_2 = D_800E30D8[arg0].unk4 + sp98;
            if (sp368 < sp358) {
                var_s0_2 = &arg1[var_s7];
                // a3 / t5 as index
                var_lo = (var_s6 - sp364) * sp36C;
                // t0 / t8 as index
                var_lo_2 = ((var_s6 - sp364) + 1) * sp36C;
                /*
                    t4 = sp368
                    t8 = t4 - t4 ????
                    t6 = t8 * 2
                    t3 = spD8
                    v0 = t6 + t3
                    --
                    a3 = a2 * t7 (var_lo)
                    t5 = a3 * 2
                    s4 = v0 + t5
                */
                // temp1 = &spD8[sp368 - sp368 + var_lo];
                var_t8 = sp368;
                temp1_2 = sp368 + var_lo - sp368;
                /*
                    t4 = sp368
                    t6 = t4 * 2
                    at = neg t4
                    t3 = at * 2
                    t9 = t6 + t3
                    t1 = t9 + t5
                    --
                    a3 = a2 * t7 (var_lo)
                    t5 = a3 * 2
                    a3 = t5
                    --
                    v1 = t1 + a3
                */
                // temp2 = &spD8[sp368 + var_lo];
                temp2_2 = sp368 + var_lo;
                /*
                    t4 = sp368
                    t8 = t4 - t4 ????
                    t6 = t8 * 2
                    t3 = spD8
                    v0 = t6 + t3
                    --
                    t0 = t2 * t7 (var_lo_2)
                    t8 = t0 * 2
                    --
                    s5 = v0 + t8
                */
                // temp3 = &spD8[(sp368 - sp368) + var_lo_2];
                temp3_2 = sp368 + var_lo_2 - sp368;
                /*
                    t4 = sp368
                    t6 = t4 * 2
                    at = neg t4
                    t3 = at * 2
                    t9 = t6 + t3
                    t1 = t9 + t5
                    --
                    t0 = t2 * t7 (var_lo_2)
                    t8 = t0 * 2
                    --
                    a0 = t1 + t8
                */
                // temp4 = &spD8[sp368 + var_lo_2];
                temp4_2 = sp368 + var_lo_2;
                var_s1 = var_s6;
                var_f26 = spCC * spC8;
                var_f28 = var_f26 * var_f26;
                do {
                    var_s0_2->unk0 = var_s3_2;
                    var_s2_s16 = D_800E30D8[arg0].unk4 + (s32) (var_s1 * spCC);
                    var_s0_2->unk6 = var_s3_2;
                    var_s0_2->unkC = var_s2_s16;
                    var_s0_2->unk2 = spD8[temp1_2];
                    var_s0_2->unk8 = spD8[temp3_2];
                    var_s0_2->unkE = spD8[temp2_2 + 1];
                    var_s0_2->unk4 = var_a1;
                    var_s0_2->unkA = var_s8;
                    var_s0_2->unk10 = var_a1;
                    var_f20 = (var_s0_2->unk2 - var_s0_2->unkE) * spC8;
                    var_f22 = (var_s0_2->unk2 - var_s0_2->unk8) * spCC;
                    var_f0 = sqrtf((var_f20 * var_f20) + var_f28 + (var_f22 * var_f22));
                    if (var_f0 > 0.0f) {
                        var_f24 = (1.0f / var_f0);
                        var_v0_4 = &arg2[var_s7];
                        var_v0_4->unk0 = var_f20 * var_f24;
                        var_v0_4->unk4 = var_f26 * var_f24;
                        var_v0_4->unk8 = var_f22 * var_f24;
                        var_v0_4->unkC = -((var_v0_4->unk8 * var_s0_2->unk4) +
                                           ((var_s0_2->unk0 * var_v0_4->unk0) + (var_s0_2->unk2 * var_v0_4->unk4)));
                        var_s7++;
                        var_s0_2++;
                    }
                    var_s0_2->unk0 = var_s2_s16;
                    var_s0_2->unk6 = var_s3_2;
                    var_s0_2->unkC = var_s2_s16;
                    var_s0_2->unk2 = spD8[temp1_2 + 1];
                    var_s0_2->unk8 = spD8[temp3_2];
                    var_s0_2->unkE = spD8[temp4_2 + 1];
                    var_s0_2->unk4 = var_a1;
                    var_s0_2->unkA = var_s8;
                    var_s0_2->unk10 = var_s8;
                    var_f20 = (var_s0_2->unk8 - var_s0_2->unkE) * spC8;
                    var_f22 = (var_s0_2->unk2 - var_s0_2->unkE) * spCC;
                    var_f0 = sqrtf((var_f20 * var_f20) + var_f28 + (var_f22 * var_f22));
                    if (var_f0 > 0.0f) {
                        var_f24 = (1.0f / var_f0);
                        var_v0_4 = &arg2[var_s7];
                        var_v0_4->unk0 = var_f20 * var_f24;
                        var_v0_4->unk4 = var_f26 * var_f24;
                        var_v0_4->unk8 = var_f22 * var_f24;

                        var_v0_4->unkC = -((var_v0_4->unk8 * var_s0_2->unk4) +
                                           ((var_s0_2->unk0 * var_v0_4->unk0) + (var_s0_2->unk2 * var_v0_4->unk4)));
                        var_s7++;
                        var_s0_2++;
                    }
                    var_s1++;
                    temp1_2++;
                    temp3_2++;
                    temp2_2++;
                    temp4_2++;
                    var_s3_2 = var_s2_s16;
                } while (var_s1 != sp358);
            }
            var_a1 = var_s8;
            var_s6++;
        } while (var_s6 != sp354);
    }

    return var_s7;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/waves/func_800BDC80.s")
#endif

Object_64 *func_800BE654(s32 arg0, f32 arg1, f32 arg2) {
    f32 spE4;
    f32 temp_f;
    s32 pad;
    f32 var_f0;
    s32 pad2;
    f32 var_f12;
    s32 var_t4;
    f32 temp_f2;
    s32 spC4;
    s32 spC0;
    f32 var_f18;
    f32 var_f20;
    f32 var_f22;
    s32 spB0;
    s32 var_t1;
    s32 var_a0;
    s16 var_t0;
    s16 var_v1;
    s16 var_a3;
    s16 var_a1;
    f32 var_f2;
    s32 var_v0;
    f32 var_f14;
    s32 var_v0_2;
    s32 var_a2;
    s32 sp80[3];
    s32 sp68[6];
    s32 sp5C[3];
    f32 sp50[3];
    Object_64 *object;

    var_t0 = 0x80;
    object = NULL;
    if ((D_800E3040 != NULL) && (arg0 >= 0) && (arg0 < gNumberOfLevelSegments)) {
        object = mempool_alloc_safe((D_80129FC8.unk20 >> 1) + 0xE, COLOUR_TAG_CYAN);
        object->effect_box.unk0 = D_800E30D8[arg0].unk6;
        object->effect_box.unk2 = 0;
        object->effect_box.unk3 = 1;
        object->effect_box.unk4 = 0;
        object->effect_box.unk6 = D_80129FC8.unk20;
        var_f20 = D_8012A0BC;
        var_f22 = D_8012A0B8;
        temp_f2 = (1.0f - D_80129FC8.unk44) / 127.0f;
        var_f2 = temp_f2;
        spB0 = (arg0 * D_800E317C);
        if (D_80129FC8.unk28 != 0) {
            var_t4 = (D_80129FC8.unk0 * 2) + 1;
            var_f20 *= 0.5f;
            var_f22 *= 0.5f;
        } else {
            var_t4 = D_80129FC8.unk0 + 1;
        }
        arg1 -= D_800E30D8[arg0].unk4;
        if (arg1 < 0.0f) {
            arg1 = 0.0f;
            // clang-format off
        } else if (arg1 >= D_8012A0A0) { \
            arg1 = D_8012A0A0 - 1;
            // clang-format on
        }
        arg2 -= D_800E30D8[arg0].unk8;
        if (arg2 < 0.0f) {
            arg2 = 0.0f;
        } else if (D_8012A0A4 <= arg2) {
            arg2 = D_8012A0A4 - 1;
        }
        spC4 = arg1 / var_f22;
        spC0 = arg2 / var_f20;
        object->effect_box.unk8 = spC4;
        object->effect_box.unkA = spC0;
        object->effect_box.unkC = arg0;
        arg1 -= (spC4 * var_f22);
        arg2 -= (spC0 * var_f20);
        var_a0 = D_800E30D8[arg0].unk12 + spC4;
        while (var_a0 >= D_80129FC8.unk4) {
            var_a0 -= D_80129FC8.unk4;
        }

        var_v0 = D_800E30D8[arg0].unk10 + spC0;
        while (var_v0 >= D_80129FC8.unk4) {
            var_v0 -= D_80129FC8.unk4;
        }

        var_t1 = 0;
        if ((arg2 != var_f20) && (arg1 < (((var_f20 - arg2) / var_f20) * var_f22))) {
            var_t1 = 1;
        }

        if (var_t1 != 0) {
            sp80[0] = (var_v0 * D_80129FC8.unk4) + var_a0;

            if ((var_v0 + 1) >= D_80129FC8.unk4) {
                sp80[1] = var_a0;
            } else {
                sp80[1] = ((var_v0 + 1) * D_80129FC8.unk4) + var_a0;
            }

            if ((var_a0 + 1) >= D_80129FC8.unk4) {
                sp80[2] = (var_v0 * D_80129FC8.unk4);
            } else {
                sp80[2] = (var_v0 * D_80129FC8.unk4) + var_a0 + 1;
            }

            spE4 = 0.0f;
            sp5C[0] = (spB0 + spC4) + (spC0 * var_t4);
            sp5C[1] = (spB0 + spC4) + ((spC0 + 1) * var_t4);
            sp5C[2] = (spB0 + spC4) + (spC0 * var_t4) + 1;
        } else {
            if ((var_a0 + 1) >= D_80129FC8.unk4) {
                sp80[0] = var_v0 * D_80129FC8.unk4;
            } else {
                sp80[0] = var_a0 + 1 + (var_v0 * D_80129FC8.unk4);
            }

            if ((var_v0 + 1) >= D_80129FC8.unk4) {
                sp80[1] = var_a0;
            } else {
                sp80[1] = ((var_v0 + 1) * D_80129FC8.unk4) + var_a0;
            }

            if ((var_a0 + 1) >= D_80129FC8.unk4) {
                sp80[2] = 0;
            } else {
                sp80[2] = var_a0 + 1;
            }

            if ((var_v0 + 1) < D_80129FC8.unk4) {
                sp80[2] += (var_v0 + 1) * D_80129FC8.unk4;
            }

            spE4 = var_f22;
            sp5C[0] = (spC4 + spB0) + (spC0 * var_t4) + 1;
            sp5C[1] = (spC4 + spB0) + (spC0 + 1) * var_t4;
            sp5C[2] = (spC4 + spB0) + (spC0 + 1) * var_t4 + 1;
        }

        for (var_a3 = 0; var_a3 < 3; var_a3++) {
            sp68[var_a3 * 2] = D_800E3044[sp80[var_a3]].s[0];
            sp68[var_a3 * 2 + 1] = D_800E3044[sp80[var_a3]].s[1];
            sp50[var_a3] = 1.0f;

            var_a2 = D_800E3178[sp5C[var_a3]];
            if (var_a2 < 0x7F) {
                sp50[var_a3] *= D_80129FC8.unk44 + (var_a2 * var_f2);
            }
        }

        if (D_80129FC8.unk28 != 0) {
            sp50[0] *= 0.5;
            sp50[1] *= 0.5;
            sp50[2] *= 0.5;
        }

        for (var_a3 = 0; var_a3 < (D_80129FC8.unk20 >> 1); var_a3++) {
            temp_f = (D_800E3040[sp68[0]] + D_800E3040[sp68[1]]) * sp50[0];
            var_f12 = (D_800E3040[sp68[2]] + D_800E3040[sp68[3]]) * sp50[1];
            var_f0 = (D_800E3040[sp68[4]] + D_800E3040[sp68[5]]) * sp50[2];
            if (var_t1 != 0) {
                var_f2 = (temp_f - var_f0) * var_f20;
                var_f14 = (temp_f - var_f12) * var_f22;
            } else {
                var_f2 = (var_f12 - var_f0) * var_f20;
                var_f14 = (temp_f - var_f0) * var_f22;
            }
            var_f18 = var_f20 * var_f22;
            var_f0 = sqrtf((var_f2 * var_f2) + (var_f18 * var_f18) + (var_f14 * var_f14));
            var_f2 /= var_f0;
            var_f14 /= var_f0;
            var_f12 = var_f18 / var_f0;
            var_v0_2 = -(s32) (((var_f2 * arg1) + (var_f14 * arg2) - ((spE4 * var_f2) + (temp_f * var_f12))) * 16.0f /
                               var_f12);
            if ((var_v0_2 >= var_t0) || (var_v0_2 < -var_t0)) {
                var_v1 = 0;
                do {
                    var_t0 += var_t0;
                    var_v1++;
                } while (var_v0_2 >= var_t0 || var_v0_2 < -var_t0);

                for (var_a1 = 0; var_a1 < var_a3; var_a1++) {
                    object->effect_box.unkE[var_a1] >>= var_v1;
                }
                object->effect_box.unk2 += var_v1;
            }
            object->effect_box.unkE[var_a3] = (var_v0_2 >> object->effect_box.unk2);
            for (var_a1 = 0; var_a1 < 6; var_a1++) {
                sp68[var_a1] += 2;
                while (sp68[var_a1] >= D_80129FC8.unk20) {
                    sp68[var_a1] -= D_80129FC8.unk20;
                }
            }
        }
    }

    return object;
}

/**
 * Finds the wave height and returns it for the spinning log object.
 */
f32 log_wave_height(Object_Log *log, s32 updateRate) {
    s32 var_t0;
    f32 y;

    log->unk4 += updateRate;
    while (log->unk4 >= log->unk6) {
        log->unk4 -= log->unk6;
    }
    var_t0 = log->unkE[log->unk4 >> 1];
    if (log->unk4 & 1) {
        if (log->unk4 + 1 >= log->unk6) {
            var_t0 += log->unkE[0];
        } else {
            var_t0 += log->unkE[(log->unk4 >> 1) + 1];
        }
        if (log->unk2 > 0) {
            var_t0 <<= (log->unk2 + 0x1F);
        } else {
            var_t0 >>= 1;
        }
    } else {
        var_t0 <<= log->unk2;
    }
    y = (((f32) var_t0 / 16.0) + (f32) log->unk0);
    y *= D_80129FC8.magnitude;
    y += func_800BEFC4(log->unkC, log->unk8, log->unkA);
    return y;
}

// height related calculation?
f32 func_800BEFC4(s32 arg0, s32 arg1, s32 arg2) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f30;
    f32 var_f0;
    f32 var_f28;
    f32 var_f2;
    u32 var_s0;
    s32 temp_a1;
    s32 var_s3;
    s32 var_v1;
    s32 temp_0;
    unk800E3184 *temp_a3;
    unk800E3190 *temp_s1;

    var_f28 = 0.0f;
    if (D_800E3188 <= 0) {
        return var_f28;
    }

    var_v1 = D_80129FC8.unk0;
    var_f0 = D_8012A0B8;
    var_f2 = D_8012A0BC;
    if (D_80129FC8.unk28 != FALSE) {
        var_v1 *= 2;
        var_f0 *= 0.5f;
        var_f2 *= 0.5f;
    }
    temp_a1 = (D_800E30D8[arg0].unkA * var_v1) + arg1;
    temp_a3 = &D_800E3184[temp_a1];
    if (temp_a3->unk0[0] != 0xFF) {
        temp_0 = arg2 + (var_v1 * D_800E30D8[arg0].unkB);
        temp_f30 = D_8012A0D0 + (temp_a1 * var_f0);
        temp_f24 = D_8012A0D4 + (temp_0 * var_f2);
        temp_f26 = 0;
        var_s3 = 0;
        do {
            temp_s1 = &D_800E3190[temp_a3->unk0[var_s3]];
            if ((temp_s1->unk0 <= temp_f24) && (temp_f24 <= temp_s1->unk4)) {
                temp_f20 = temp_f30 - temp_s1->unk8;
                temp_f22 = temp_f24 - temp_s1->unkC;
                temp_f12 = (temp_f20 * temp_f20) + (temp_f22 * temp_f22);
                if (temp_f12 < temp_s1->unk14) {
                    temp_f0 = sqrtf(temp_f12);
                    var_s0 = temp_s1->unk1A;
                    if (temp_s1->unk31 != 0) {
                        if (temp_f20 < temp_f26) {
                            var_s0 -= (s32) (temp_f20 * temp_s1->unk20);
                        } else {
                            var_s0 += (s32) (temp_f20 * temp_s1->unk20);
                        }
                    } else if (temp_s1->unk32 != 0) {
                        if (temp_f20 < temp_f26) {
                            var_s0 -= (s32) (temp_f22 * temp_s1->unk20);
                        } else {
                            var_s0 += (s32) (temp_f22 * temp_s1->unk20);
                        }
                    } else {
                        var_s0 += (s32) (temp_f0 * temp_s1->unk20);
                    }
                    temp_f20 = coss_f((temp_f0 * 65536.0f) / temp_s1->unk10);
                    var_f28 += temp_s1->unk24 * sins_f(var_s0) * temp_f20;
                }
            }
            var_s3++;
        } while (var_s3 < 8 && temp_a3->unk0[var_s3] != 0xFF);
    }

    return var_f28;
}

void func_800BF3E4(Object *obj) {
    s32 i;
    s32 k;
    s32 j;
    s32 m;
    unk800E3184 *temp_a1;

    if (D_800E3190 == NULL) {
        return;
    }

    for (i = 0, m = 0; i < D_800E3188 && m == 0; i++) {
        if (obj == D_800E3194[i]) {
            m = -1;
        }
    }

    if (m == 0) {
        return;
    }

    i--;
    for (j = 0; j < D_800E318C; j++) {
        for (k = 0, temp_a1 = &D_800E3184[j]; k < 8 && temp_a1->unk0[k] != 0xFF; k++) {
            if (i != temp_a1->unk0[k]) {
                continue;
            }

            while (k < 7) {
                temp_a1->unk0[k] = temp_a1->unk0[k + 1];
                k++;
            }
            temp_a1->unk0[k] = 0xFF;
            k++;
        }
    }

    D_800E3194[j] = NULL;
    D_800E3188--;
}

void func_800BF524(Object *obj) {
    LevelObjectEntry800BF524 *temp_v0;
    s32 var_v1;

    temp_v0 = &obj->segment.level_entry->unk800BF524;
    var_v1 = 0;
    if (temp_v0->unk10 != 0) {
        var_v1 = 1;
    }

    if (temp_v0->unk11 != 0) {
        var_v1 |= 2;
    }

    func_800BF634(obj, obj->segment.trans.x_position, obj->segment.trans.z_position, (f32) temp_v0->unkA,
                  temp_v0->unk9 << 8, (f32) temp_v0->unk8 / 16.0, (f32) temp_v0->unkE, (f32) temp_v0->unkC / 16.0,
                  var_v1);
}

unk800E3190 *func_800BF634(Object *obj, f32 xPos, f32 zPos, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7,
                           s32 arg8) {
    f32 var_f0;
    s32 var_a0;
    s32 var_a0_2;
    s32 j;
    s32 var_a2_2;
    s32 k;
    s32 i;
    unk800E3184 *temp;
    unk800E3190 *result;

    result = NULL;
    if (D_800E3190 != NULL) {
        for (i = 0, var_a0 = 0; i < 32 && var_a0 == 0; i++) {
            if (D_800E3194[i] == NULL) {
                var_a0 = -1;
            }
        }

        i--;
        if (var_a0 != 0) {
            D_800E3194[i] = obj;
            D_800E3188++;
            var_f0 = D_8012A0B8;
            if (D_80129FC8.unk28 != FALSE) {
                var_f0 /= 2.0f;
            }

            var_a0_2 = (((xPos - arg3) - D_8012A0D0) / var_f0);
            if (var_a0_2 >= D_800E318C) {
                return result;
            }

            var_a2_2 = (((xPos + arg3) - D_8012A0D0) / var_f0);
            if (var_a2_2 < 0) {
                return result;
            }

            if (var_a0_2 < 0) {
                var_a0_2 = 0;
            }

            if (var_a2_2 >= D_800E318C) {
                var_a2_2 = D_800E318C - 1;
            }

            for (j = var_a0_2; j <= var_a2_2; j++) {
                temp = &D_800E3184[j];
                if (temp->unk0[7] != 0xFF) {
                    continue;
                }

                k = 0;
                while (temp->unk0[k] != 0xFF) {
                    k++;
                }
                temp->unk0[k] = i;
            }
            result = &D_800E3190[i];
            result->unk0 = zPos - arg3;
            result->unk4 = zPos + arg3;
            result->unk8 = xPos;
            result->unkC = zPos;
            result->unk10 = arg3;
            result->unk18 = i;
            result->unk14 = arg3 * arg3;
            result->unk1A = arg4;
            if (osTvType == OS_TV_TYPE_PAL) {
                result->unk1C = arg5 * 20971.52; //(f64) (0x80000 / 25.0);
            } else {
                result->unk1C = arg5 * 17476.27; //(f64) ((0x80000 / 1.2) / 25.0);
            }
            result->unk20 = 65536.0f / arg6;
            result->unk24 = arg7;
            result->unk28 = arg5;
            result->unk31 = arg8 & 1;
            result->unk32 = arg8 & 2;
            result->unk2C = arg6;
        }
    }

    return result;
}

UNUSED void func_800BF9F8(unk800BF9F8 *arg0, f32 arg1, f32 arg2) {
    UNUSED s32 pad[4];
    s32 sp1C;
    f32 var_f0;
    s32 var_a1;
    s32 i;
    s32 var_a2;
    s32 j;
    s32 iteration;
    s32 temp_v1;
    u8 *var_a2_2;

    if (arg0 == NULL) {
        return;
    }

    var_f0 = D_8012A0B8;
    iteration = 0;
    if (D_80129FC8.unk28 != FALSE) {
        var_f0 *= 0.5f;
    }
    temp_v1 = arg0->unk18;
    while (iteration != 2) {
        var_a1 = TRUE;
        var_a2 = ((arg0->unk8 - arg0->unk10) - D_8012A0D0) / var_f0;
        if (var_a2 >= D_800E318C) {
            var_a1 = FALSE;
        } else if (var_a2 < 0) {
            var_a2 = 0;
        }

        if (var_a1) {
            sp1C = ((arg0->unk8 + arg0->unk10) - D_8012A0D0) / var_f0;
            if (sp1C < 0) {
                var_a1 = FALSE;
            } else if (sp1C >= D_800E318C) {
                sp1C = D_800E318C - 1;
            }
        }

        if (var_a1) {
            for (i = var_a2; i <= sp1C; i++) {
                var_a2_2 = &D_800E3184[i].unk0[0];
                j = 0;
                if (iteration != 0) {
                    if (var_a2_2[7] == 0xFF) {
                        while (var_a2_2[0] != 0xFF) {
                            var_a2_2++;
                        }
                        var_a2_2[0] = temp_v1;
                    }
                } else {
                    while (j < 8) {
                        if (temp_v1 == var_a2_2[j]) {
                            while (j < 7) {
                                var_a2_2[j] = var_a2_2[j + 1];
                                j++;
                            }
                            var_a2_2[j] = 0xFF;
                            j++;
                        }
                        j++;
                    }
                }
            }
        }

        if (iteration == 0) {
            arg0->unk8 += arg1;
            arg0->unkC += arg2;
            arg0->unk0 += arg2;
            arg0->unk4 += arg2;
        }
        iteration++;
    }
}

UNUSED void func_800BFC54(unk800BFC54_arg0 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    if (arg0 == NULL) {
        return;
    }

    arg0->unk10 = (arg0->unk10 + arg1);
    if (arg0->unk10 < 1.0) {
        arg0->unk10 = 1.0f;
    }

    arg0->unk0 = (arg0->unkC - arg0->unk10);
    arg0->unk4 = (arg0->unkC + arg0->unk10);
    arg0->unk28 += arg2;
    if (osTvType == OS_TV_TYPE_PAL) {
        arg0->unk1C = arg0->unk28 * 20971.52; //(f64) (0x80000 / 25.0);
    } else {
        arg0->unk1C = arg0->unk28 * 17476.27; //(f64) ((0x80000 / 1.2) / 25.0);
    }

    arg0->unk2C = arg0->unk2C + arg3;
    if (arg0->unk2C < 1.0) {
        arg0->unk2C = 1.0f;
    }

    arg0->unk20 = 65536.0f / arg0->unk2C; // 0x10000
    arg0->unk24 = arg0->unk24 + arg4;
}

void func_800BFE98(s32 arg0) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (D_800E3194[i] != NULL) {
            D_800E3190[i].unk1A += (0, D_800E3190[i].unk1C * arg0) >> 4;
        }
    }
}

/**
 * Wave Power loop func.
 * Waits for racers to pass through, then sets itself as the current baseline for how strong the waves should be.
 */
void obj_loop_wavepower(Object *obj) {
    LevelObjectEntry_WavePower *entry;
    s32 numRacers;
    Object *racerObj;
    Object_Racer *racer;
    Object **racers;
    s32 i;
    f32 diffY;
    f32 diffZ;
    f32 diffX;
    f32 distance;

    if (obj == gWaveGeneratorObj) {
        return;
    }

    racers = get_racer_objects(&numRacers);
    if (numRacers <= 0) {
        return;
    }

    racerObj = NULL;
    for (i = 0; i < numRacers && racerObj == NULL; i++) {
        racer = &racers[i]->unk64->racer;
        if (racer->playerIndex == PLAYER_ONE) {
            racerObj = racers[i];
        }
    }

    if (racerObj == NULL) {
        return;
    }

    entry = &obj->segment.level_entry->wavePower;
    distance = entry->radius;
    distance *= distance;
    diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
    diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
    diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
    if ((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ) < distance) {
        gWavePowerBase = entry->power / 256.0f;
        gWaveMagnitude = (gWavePowerBase - D_80129FC8.magnitude) / (f32) entry->divisor;
        gWavePowerDivisor = entry->divisor;
        gWaveGeneratorObj = obj;
    }
}
