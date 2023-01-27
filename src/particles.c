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
#include "unknown_0255E0.h"

/************ .rodata ************/

// This is most likely a file boundary. Not sure where the split occurs though.
const int D_800E8838[2] = { 0, 0 };

/*********************************/

/************ .data ************/

// I woundn't be suprised if most of these zeroes are really just null pointers.
s32 D_800E2CA0 = 0;
s32 D_800E2CA4 = 0;
unk800B1CB8 *D_800E2CA8 = NULL;
s32 D_800E2CAC = 0;
s32 D_800E2CB0 = 0;
unk800B1CB8 *D_800E2CB4 = NULL;
s32 D_800E2CB8 = 0;
s32 D_800E2CBC = 0;
unk800B1CB8 *D_800E2CC0 = NULL;
s32 D_800E2CC4 = 0;
s32 D_800E2CC8 = 0;
unk800B1CB8 *D_800E2CCC = NULL;
s32 D_800E2CD0 = 0;
s32 D_800E2CD4 = 0;
unk800E2CD8 *D_800E2CD8 = NULL;
s32 D_800E2CDC = 0;
s32 *D_800E2CE0 = NULL;
s32 *D_800E2CE4 = NULL;
s32 gParticlesAssetTableCount = 0;
s32 *gParticlesAssets = NULL;

unk800E2CF0 **gParticlesAssetTable = NULL;
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

f32 D_800E2E2C[8] = {
    0.0f, 0.1f, 0.2f, 0.3f, 0.45f, 0.525f, 0.6f, 0.8f
};

s32 D_800E2E4C = 0;
s32 D_800E2E50 = 0;
s32 D_800E2E54 = 0;
s32 D_800E2E58 = 0;
s32 D_800E2E5C = 0;
Sprite **D_800E2E60 = NULL;
s32 D_800E2E64 = 0;

XYStruct D_800E2E68[3] = {
    { 0,  8 },
    { 7, -4 },
    { -7, -4 },
};

XYStruct D_800E2E74[4] = {
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

s32 D_800E2EEC = 0x100;

/*******************************/

/************ .bss ************/

s32 D_80127C80;
s32 D_80127C84;
s32 D_80127C88[6];
TextureHeader *gTexture0;
TextureHeader *gTexture1;
TextureHeader *gTexture2;
u16 D_80127CAC;
u16 D_80127CAE;
s16 D_80127CB0;
s16 D_80127CB2;
s32 D_80127CB4;
s32 D_80127CB8;
s32 D_80127CBC;
s32 D_80127CC0;
s32 D_80127CC4;
s32 D_80127CC8;
s32 gDebugFontTexture;
u16 D_80127CD0;
u16 D_80127CD2;
s32 D_80127CD4;
s8 gDebugPrintBufferStart[2300];
u8 *gDebugPrintBufferEnd;
u64 gEPCStack[0x200];
OSThread gEPCThread;
s32 D_80129790[6]; // Osmesg stuff
s32 D_801297A8[8];
s32 D_801297C8[8];
s32 D_801297E8[6];

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
    s32 *new_var2;
    s32 i;
    u32 new_var;

    func_800AE490();
    gParticlesAssetTable = (unk800E2CF0 **) load_asset_section_from_rom(ASSET_PARTICLES_TABLE);
    gParticlesAssetTableCount = -1; 
    while (((s32) gParticlesAssetTable[gParticlesAssetTableCount + 1]) != -1) {
        gParticlesAssetTableCount++;
    }

    gParticlesAssets = (s32 *) load_asset_section_from_rom(ASSET_PARTICLES);
    for (i = 0; i < gParticlesAssetTableCount; i++) {
    gParticlesAssetTable[i] = (unk800E2CF0 *) (((u8 *) gParticlesAssets) + ((s32) gParticlesAssetTable[i]));
    }

  gParticleBehavioursAssetTable = (ParticleBehavior **) load_asset_section_from_rom(ASSET_PARTICLE_BEHAVIORS_TABLE);
  gParticleBehavioursAssetTableCount = -1; 
  while (((s32) gParticleBehavioursAssetTable[gParticleBehavioursAssetTableCount + 1]) != -1) {
      gParticleBehavioursAssetTableCount++;
  }

    gParticleBehavioursAssets = (s32 *) load_asset_section_from_rom(ASSET_PARTICLE_BEHAVIORS);
    for (i = 0; i < gParticleBehavioursAssetTableCount; i++) {
        new_var = -1;
        gParticleBehavioursAssetTable[i] = (ParticleBehavior *) (((u8 *) gParticleBehavioursAssets) + ((s32) gParticleBehavioursAssetTable[i]));
        if (((u32) gParticleBehavioursAssetTable[i]->unk9C) != new_var) {
            new_var2 = gParticleBehavioursAssetTable[i]->unk9C;
            gParticleBehavioursAssetTable[i]->unk9C = (s32 *) get_misc_asset((s32) new_var2);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/particles/func_800AE728.s")

void func_800AEE14(unk800AF024 *arg0, Vertex **arg1, Triangle **arg2) {
    s16 i;
    Vertex *temp;
    Triangle *tri;
    XYStruct *temp2;

    arg0->unk4 = 3;
    arg0->unk8 = *arg1;
    temp = *arg1;
    temp2 = &D_800E2E68[0];
    for (i = 0; i < 3; i++) {
        temp->x = temp2->x;
        temp->y = temp2->y;
        temp2 += 1;
        temp->z = 0;
        temp->r = 255;
        temp->g = 255;
        temp->b = 255;
        temp->a = 255;
        temp++;
    }
    *arg1 = temp;
    arg0->unk6 = 1;
    arg0->unkC = *arg2;
    tri = *arg2;
    tri->flags = 0x40;
    tri->vi0 = 2;
    tri->vi1 = 1;
    tri->vi2 = 0;
    tri++;
    *arg2 = tri;
}

void func_800AEEB8(unk800AF024 *arg0, Vertex **arg1, Triangle **arg2) {
    s16 i;
    Vertex *temp;
    Triangle *tri;
    XYStruct *temp2;

    arg0->unk4 = 4;
    arg0->unk8 = *arg1;
    temp = *arg1;
    temp2 = &D_800E2E74[0];
    for (i = 0; i < 4; i++) {
        temp->x = temp2->x;
        temp->y = temp2->y;
        temp2 += 1;
        temp->z = 0;
        temp->r = 255;
        temp->g = 255;
        temp->b = 255;
        temp->a = 255;
        temp++;
    }
    *arg1 = temp;
    arg0->unk6 = 2;
    arg0->unkC = *arg2;
    tri = *arg2;
    tri[0].flags = 0x40;
    tri[0].vi0 = 3;
    tri[0].uv0.u = 0;
    tri[0].vi1 = 1;
    tri[0].uv1.v = 0;
    tri[0].vi2 = 0;
    tri[0].uv2.u = 0;
    tri[0].uv2.v = 0;
    tri[1].flags = 0x40;
    tri[1].vi0 = 3;
    tri[1].uv0.u = 0;
    tri[1].vi1 = 2;
    tri[1].vi2 = 1;
    tri[1].uv2.v = 0;
    tri += 2;
    *arg2 = tri;
}

void func_800AEF88(unk800AF024 *arg0, Vertex **arg1, Triangle **arg2) {
    s32 i;
    Vertex *temp;

    arg0->unk4 = 6;
    arg0->unk6 = 4;
    arg0->unk8 = *arg1;
    arg0->unkC = *arg2;
    temp = *arg1;
    for (i = 0; i < 6; i++) {
        temp->r = 255;
        temp->g = 255;
        temp->b = 255;
        temp->a = 255;
        temp++;
    }
    *arg1 = temp;
}

void func_800AF024(unk800AF024 *arg0, Vertex **arg1, Triangle **arg2) {
    s32 i;
    Vertex *temp;

    arg0->unk4 = 8;
    arg0->unk6 = 8;
    arg0->unk8 = *arg1;
    arg0->unkC = *arg2;
    temp = *arg1;
    for (i = 0; i < 16; i++) {
        temp->r = 255;
        temp->g = 255;
        temp->b = 255;
        temp->a = 255;
        temp++;
    }
    *arg1 = temp;
}

void func_800AF0A4(Object *obj) {
    Object_44 *temp_v0;
    Object_44_C *temp_v1;
    s16 temp_t1, temp_t8_0;
    s32 temp_t8;

    temp_v0 = (Object_44 *) obj->unk44;
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

void func_800AF0F0(Object *obj) {
    Object_44 *temp_v0;
    Object_44_C *temp_v1;
    s16 temp_t8, temp_t1;

    temp_v0 = (Object_44 *) obj->unk44;
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

void func_800AF134(Particle *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    ParticleBehavior *temp;
    if (arg2 >= gParticlesAssetTableCount) {
        arg2 = 0;
    }
    if (arg1 >= gParticleBehavioursAssetTableCount) {
        arg1 = 0;
    }
    temp = gParticleBehavioursAssetTable[arg1];
    if (arg0->unk8 != arg2 || temp != arg0->behaviour) {
        func_800B2260(arg0);
        func_800AF29C(arg0, arg1, arg2, arg3, arg4, arg5);
    }
}

void func_800AF1E0(Particle *arg0, s32 arg1, s32 arg2) {
    ParticleBehavior *temp_v0;

    if (arg1 < gParticleBehavioursAssetTableCount) {
        temp_v0 = gParticleBehavioursAssetTable[arg1];
        func_800AF29C(arg0, arg1, arg2, temp_v0->unk4, temp_v0->unk8, temp_v0->unkC);
    }
}

void func_800AF29C(Particle *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    ParticleBehavior *temp_v1;
    s32 temp_v0_2;
    s32 flags;

    temp_v1 = gParticleBehavioursAssetTable[arg1];
    arg0->unk8 = arg2;
    arg0->unk18 = arg3;
    arg0->behaviour = temp_v1;
    arg0->unk1A = arg4;
    arg0->unk1C = arg5;
    arg0->unk1E = 0;

    flags = temp_v1->flags;

    if (flags & 0x4000) {
        arg0->flags = 0x4000;
        arg0->unk6 = 0;
        arg0->pos.x = 0.0f;
        arg0->pos.y = 0.0f;
        arg0->pos.z = 0.0f;
    } else if (flags & 0x400) {
        arg0->unk6 = 0;
        arg0->flags = 0x400;
        temp_v0_2 = gParticlesAssetTable[arg2]->unk8;
        if (temp_v0_2 < 0x100) {
            arg0->unk7 = temp_v0_2;
        } else {
            arg0->unk7 = 0xFF;
        }
        arg0->unkC_400.unkC = (s32 *) allocate_from_main_pool_safe(arg0->unk7 * 4, COLOUR_TAG_SEMITRANS_GREY);
        arg0->unkC_400.unk10 = temp_v1->unk14;
        arg0->unkC_400.unk12 = temp_v1->unk16;
        arg0->unkC_400.unk14 = temp_v1->unk22;
        arg0->unkC_400.unk16 = temp_v1->unk24;
    } else {
        arg0->flags = 0;
        arg0->unkC.unkC = temp_v1->unk14;
        arg0->unkC.unkE = temp_v1->unk16;
        arg0->unkC.unk10 = temp_v1->unk18;
        arg0->unkC.unk12 = temp_v1->unk22;
        arg0->unkC.unk14 = temp_v1->unk24;
        arg0->unkC.unk16 = temp_v1->unk26;
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
    ParticleBehavior *temp_v1;
    Particle2 *temp;

    temp_v0 = (Particle *) &obj->unk6C[arg1];
    temp_v1 = temp_v0->behaviour;
    temp_v0->unkA = 0;
    if (temp_v0->flags & 0x4000) {
        ((ObjectSegment *) temp_v0)->trans.x_position = obj->segment.trans.x_position;
        ((ObjectSegment *) temp_v0)->trans.y_position = obj->segment.trans.y_position;
        ((ObjectSegment *) temp_v0)->trans.z_position = obj->segment.trans.z_position;
    } else if (temp_v0->flags & 0x400) {
        temp_v0->unkA = gParticlesAssetTable[temp_v0->unk8]->unk17 << 8;

        if (temp_v0->unk6 > 0) { // Useless if statement, since the loop already does this.
            for (i = 0; i < temp_v0->unk6; i++){
                temp = temp_v0->unkC_60[i];
                temp->unk38.half.unk3A = 0;
            }
        }
        if (temp_v1->flags & 1) {
            temp_v0->unkC.unk10 = temp_v1->unk14;
            temp_v0->unkC.unk12 = temp_v1->unk16;
        }
        if (temp_v1->flags & 4) {
            temp_v0->unkC.unk14 = temp_v1->unk22;
            temp_v0->unkC.unk16 = temp_v1->unk24;
        }
    } else {
        if (temp_v1->flags & 1) {
            temp_v0->unk6 = 0;
            temp_v0->unkC.unkC = temp_v1->unk14;
            temp_v0->unkC.unkE = temp_v1->unk16;
            temp_v0->unkC.unk10 = temp_v1->unk18;
        }
        if (temp_v1->flags & 4) {
            temp_v0->unk7 = 0;
            temp_v0->unkC.unk12 = temp_v1->unk22;
            temp_v0->unkC.unk14 = temp_v1->unk24;
            temp_v0->unkC.unk16 = temp_v1->unk26;
        }
    }
    temp_v0->flags &= 0xFDFF;
    temp_v0->flags |= 0xA000;
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

void func_800AFE5C(unk800B1CB8 *arg0, Particle *arg1) {
    Particle2 *temp_s0;
    Object *tempObj;
    Particle2 *tempObj2;
    s32 i;
    ParticleBehavior *temp_s4;

    temp_s4 = arg1->behaviour;
    if (arg1->flags & 0x4000) {
        tempObj = func_800B0BAC();
        if (tempObj != NULL) {
            func_8000E9D0(tempObj);
        }
        arg1->flags &= 0xDFFF;
        if (arg1->unk6 + 64 > 255) {
            arg1->unk6 = 255;
        } else {
            arg1->unk6 += 64;
        }
    } else if (arg1->flags & 0x400) {
        if (arg1->unk6 < arg1->unk7) {
            temp_s0 = func_800B0698(arg0, arg1);
            arg1->flags &= 0xDFFF;
            if (temp_s0 != NULL) {
                func_8000E9D0((Object *) temp_s0);
                temp_s0->unk74 = arg1->unk6;
                temp_s0->unk40 |= 0x2000;
                arg1->unkC_60[arg1->unk6] = temp_s0;
                arg1->unk6++;
            }
        }
    } else {
        while (arg1->unkA >= temp_s4->unk40) {
            arg1->unkA -= temp_s4->unk40;
            for (i = 0; i < temp_s4->unk42; i++) {
                tempObj2 = func_800B1130(arg0, arg1);
                if (tempObj2 != NULL) {
                    func_8000E9D0((Object *) tempObj2);
                    func_800B22FC(tempObj2, arg1->unkA);
                }
                arg1->flags &= ~0x2000;
            }
        }
    }
}

void func_800B0010(Object *arg0, Object *arg1, unk800B03C0_arg2 *arg2, Object *arg3) {
    s32 sp3C;
    Vec3f sp30;
    Vec3s sp28;

    if (arg3->segment.trans_unk.unk0 & 0x70) {
        arg0->segment.x_velocity = arg3->segment.unk30;
        arg0->segment.y_velocity = arg3->segment.unk34_a.unk34;
        arg0->segment.z_velocity = arg3->segment.unk38.unk38_f32;
    } else {
        arg0->segment.x_velocity = 0.0f;
        arg0->segment.y_velocity = 0.0f;
        arg0->segment.z_velocity = 0.0f;
    }
    sp3C = arg3->unk5C_s32 & 0x700;
    if (sp3C) {
        if (sp3C & 0x100) {
            arg0->segment.x_velocity += (f32) get_random_number_from_range(-arg3->unk74_signed, arg3->unk74_signed) * 0.00001525878906f;
        }
        if (sp3C & 0x200) {
            arg0->segment.y_velocity += (f32) get_random_number_from_range(-arg3->unk78,  arg3->unk78) * 0.00001525878906f;
        }
        if (sp3C & 0x400) {
            arg0->segment.z_velocity += (f32) get_random_number_from_range(-arg3->unk7C.word, arg3->unk7C.word) * 0.00001525878906f;
        }
    }
    switch (arg3->segment.trans_unk.unk0 & 0x70) {
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
    if (arg3->segment.trans_unk.unk0 & 4) {
        sp30.x = 0.0f;
        sp30.y = 0.0f;
        sp30.z = -arg3->segment.unk3C_a.unk3C_f;
        sp3C = arg3->unk5C_s32;
        if (sp3C & 0x10) {
            sp30.z += (f32) get_random_number_from_range(-arg3->unk70_s32, arg3->unk70_s32) * 0.00001525878906f;
        }
        if (sp3C & 0x60) {
            sp28.y_rotation = arg2->unk12;
            if (sp3C & 0x20) {
                sp28.y_rotation += get_random_number_from_range((s32) -arg3->unk68_halfs.unk6A, (s32) arg3->unk68_halfs.unk6A);
            }
            sp28.x_rotation = arg2->unk14;
            if (sp3C & 0x40) {
                sp28.x_rotation += get_random_number_from_range((s32) -arg3->unk6C_halfs.unk6C, (s32) arg3->unk6C_halfs.unk6C);
            }
            f32_vec3_apply_object_rotation3((ObjectTransform* ) &sp28, (f32*) &sp30);
        } else {
            f32_vec3_apply_object_rotation3((ObjectTransform* ) &arg2->unk12, (f32*) &sp30);
        }
        f32_vec3_apply_object_rotation((ObjectTransform* ) arg0->segment.unk3C_a.unk3C_ptr, (f32*) &sp30);
        arg0->segment.x_velocity += sp30.x;
        arg0->segment.y_velocity += sp30.y;
        arg0->segment.z_velocity += sp30.z;
    }
}

void func_800B03C0(Object *arg0, ObjectTransform *arg1, unk800B03C0_arg2 *arg2, Object *arg3) {
    s32 sp3C;
    Vec3f sp30;
    Vec3s sp28;

    arg0->unk4C_f32 = arg2->unk18;
    arg0->unk50_f32 = arg2->unk1A;
    arg0->unk54_f32 = arg2->unk1C;
    arg0->unk58_f32 = arg3->unk58_f32;
    if (arg3->unk5C_s32 & 0x80000) {
        arg0->unk58_f32 += (f32) get_random_number_from_range(-arg3->unk94_signed, arg3->unk94_signed) * 0.00001525878906f; // 0.00001525878906 ~= 1.0/65536.0
    }
    if (arg3->segment.trans_unk.unk0 & 1) {
        sp30.x = 0.0f;
        sp30.y = 0.0f;
        sp30.z = -arg3->segment.trans_unk.y_position;
        sp3C = arg3->unk5C_s32;
        if (sp3C & 1) {
            sp30.z += (f32) get_random_number_from_range(-arg3->unk60_s32, arg3->unk60_s32) * 0.00001525878906f;
        }
        if (sp3C & 6) {
            sp28.y_rotation = arg2->y_rotation;
            if (sp3C & 2) {
                sp28.y_rotation += get_random_number_from_range(-arg3->unk64_halfs.unk64, arg3->unk64_halfs.unk64);
            }
            sp28.x_rotation = arg2->x_rotation;
            if (sp3C & 4) {
                sp28.x_rotation += get_random_number_from_range(-arg3->unk64_halfs.unk66, arg3->unk64_halfs.unk66);
            }
            f32_vec3_apply_object_rotation3((ObjectTransform* ) &sp28, (f32 *) &sp30);
        } else {
            f32_vec3_apply_object_rotation((ObjectTransform* ) &arg2->y_rotation, (f32 *) &sp30);
        }
        arg0->unk4C_f32 += sp30.x;
        arg0->unk50_f32 += sp30.y;
        arg0->unk54_f32 += sp30.z;
    }
    if (arg0->segment.unk38.byte.unk39 != 4) {
        f32_vec3_apply_object_rotation(arg1, &arg0->unk4C_f32);
    }
    arg0->segment.trans.x_position = arg0->unk4C_f32;
    arg0->segment.trans.y_position = arg0->unk50_f32;
    arg0->segment.trans.z_position = arg0->unk54_f32;
    if (arg0->segment.unk38.byte.unk39 == 4) {
        f32_vec3_apply_object_rotation(arg1, &arg0->segment.trans.x_position);
    }
    arg0->segment.trans.x_position += arg1->x_position;
    arg0->segment.trans.y_position += arg1->y_position;
    arg0->segment.trans.z_position += arg1->z_position;
}

Particle2 *func_800B0698(unk800B1CB8 *arg0, Particle *arg1) {
    unk800E2CF0 *sp2C;
    unk800E2CD8 *var_v0;
    TextureHeader **sp24;
    ParticleBehavior *sp20;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f2;

    sp2C = gParticlesAssetTable[arg1->unk8];
    if (sp2C->unk0 != 4) {
        return NULL;
    }
    sp20 = arg1->behaviour;
    var_v0 = (unk800E2CD8 *) func_800B1CB8(4);
    if (var_v0 == NULL) {
        return (Particle2 *) var_v0;
    }
    var_v0->unk0.unk2E = arg0->unk2E;
    var_v0->unk0.unk6 = -0x8000;
    var_v0->unk0.unk39 = sp2C->unk1;
    var_v0->unk0.unk40 = sp2C->unk2;
    var_v0->unk0.unk3C = arg0;
    var_v0->unk70 = arg1;
    var_v0->unk0.unk8 = sp2C->unk10 * sp20->unk50;
    var_v0->unk0.unk28 = sp2C->unk10 * sp20->unk54;
    var_v0->unk0.unk3A = sp2C->unk8;
    var_v0->unk0.unk34 = 0.0f;
    var_v0->unk0.unk38 = 0;
    var_v0->unk0.unk6C.r = sp2C->unk14;
    var_v0->unk0.unk6C.g = sp2C->unk15;
    var_v0->unk0.unk6C.b = sp2C->unk16;
    var_v0->unk0.unk6C.a = sp2C->unk17;
    if (var_v0->unk0.unk40 & 0x800 && arg0->unk54 != NULL) {
        var_v0->unk0.unk4A = *arg0->unk54 * 255.0f;
    } else {
        var_v0->unk0.unk4A = 0xFF;
    }
    var_v0->unk0.unk60 = sp2C->unkE;
    if (arg1->flags & 0x100) {
        var_v0->unk0.unk5C = arg1->unkA;
    } else {
        var_v0->unk0.unk5C = sp2C->unkC << 8;
    }
    if (sp2C->unkC < 255) {
        if (var_v0->unk0.unk40 & 0x1000) {
            var_v0->unk0.unk6 |= 0x100;
        } else {
            var_v0->unk0.unk6 |= 0x80;
        }
    }
    if (var_v0->unk0.unk60 < var_v0->unk0.unk3A) {
        var_v0->unk0.unk5E = ((sp2C->unkD << 8) - (var_v0->unk0.unk5C & 0xFFFF)) / (var_v0->unk0.unk3A - var_v0->unk0.unk60);
    } else {
        var_v0->unk0.unk5E = 0;
    }
    func_800B03C0((Object *) var_v0, (ObjectTransform *) arg0, (unk800B03C0_arg2 *) arg1, (Object *)sp20);
    if (sp20->flags & 0x80) {
        var_v0->unk0.unk0 = sp20->unk44;
        var_v0->unk0.unk2 = sp20->unk46;
        var_v0->unk0.unk4 = sp20->unk48;
    } else {
        var_v0->unk0.unk0 = arg0->unk0 + sp20->unk44;
        var_v0->unk0.unk2 = arg0->unk2 + sp20->unk46;
        var_v0->unk0.unk4 = arg0->unk4 + sp20->unk48;
    }
    var_v0->unk0.unk62 = sp20->unk4A;
    var_v0->unk0.unk64 = sp20->unk4C;
    var_v0->unk0.unk66 = sp20->unk4E;
    func_800B0010((Object *) var_v0, (Object *) arg0, (unk800B03C0_arg2 *) arg1, (Object *)sp20);
    var_v0->unk0.unk68 = D_800E2E2C[(var_v0->unk0.unk40 >> 4) & 7];
    if (var_v0->unk0.unk39 == 5) {
        temp_f0 = var_v0->unk0.unk1C;
        temp_f2 = var_v0->unk0.unk20;
        temp_f14 = var_v0->unk0.unk24;
        var_v0->unk0.unk58 = sqrtf((temp_f0 * temp_f0) + (temp_f2 * temp_f2) + (temp_f14 * temp_f14));
    }
    if (sp20->flags & 2) {
        arg1->unkC.unk10 += sp20->unk1C;
        arg1->unkC.unk12 += sp20->unk1E;
    }
    if (sp20->flags & 8) {
        arg1->unkC.unk14 += sp20->unk2A;
        arg1->unkC.unk16 += sp20->unk2C;
    }
    var_v0->unk0.unk1A = sp2C->unk6;
    var_v0->unk0.unk18 = 0;
    sp24 = (TextureHeader **) var_v0->unk0.unk44;
    if (sp2C->unk4 == -1) {
        *sp24 = NULL;
    } else {
        *sp24 = load_texture(sp2C->unk4);
        if ((*sp24) != NULL) {
            if ((*sp24)->flags & 4) {
                if (var_v0->unk0.unk40 & 0x1000) {
                    var_v0->unk0.unk6 |= 0x100;
                } else {
                    var_v0->unk0.unk6 |= 0x80;
                }
            }
            if ((var_v0->unk0.unk40 & 3) == 2) {
                var_v0->unk0.unk18 = (*sp24)->numOfTextures - 1;
            }
        }
    }
    var_v0->unk75 = 0;
    var_v0->unk76 = ((u32) (u16) sp2C->unkA) >> 10;
    var_v0->unk77 = 0;
    if (*sp24 == NULL) {
        func_800B2040((Particle2 *) var_v0);
        return NULL;
    }
    return (Particle2 *) var_v0;
}

GLOBAL_ASM("asm/non_matchings/particles/func_800B0BAC.s")

Particle2 *func_800B1130(unk800B1CB8 *arg0, Particle *arg1) {
    s32 sp3C;
    unk800E2CF0 *sp38;
    unk800B1CB8* var_v0;
    TextureHeader **sp30;
    ParticleBehavior *partBeh;
    unk800B1130_SP28 *sp28;
    f32 sp24;
    s8 sp23;
    
    sp38 = gParticlesAssetTable[arg1->unk8];
    if (sp38->unk0 == 3 || sp38->unk0 == 4) {
        return NULL;
    }
    partBeh = arg1->behaviour;
    sp28 = (unk800B1130_SP28 *) partBeh->unk9C;
    
    var_v0 = func_800B1CB8(sp38->unk0);
    if (var_v0 == NULL) {
        return (Particle2 *) var_v0;
    }
    var_v0->unk2E = arg0->unk2E;
    var_v0->unk6 = -0x8000;
    var_v0->unk39 = sp38->unk1;
    var_v0->unk40 = sp38->unk2;
    var_v0->unk3C = arg0;
    if (var_v0->unk40 & 0x800 && arg0->unk54 != NULL) {
        var_v0->unk4A = *arg0->unk54 * 255.0f;
    } else {
        var_v0->unk4A = 255;
    }
    sp24 = partBeh->unk50;
    if (partBeh->unk5C & 0x20000) {
        sp24 += (f32) get_random_number_from_range(-partBeh->unk8C, partBeh->unk8C) * 0.00001525878906;
    }
    var_v0->unk8 = sp38->unk10 * sp24;
    sp24 = partBeh->unk54;
    if (partBeh->unk5C & 0x40000) {
        sp24 += (f32) get_random_number_from_range(-partBeh->unk90, partBeh->unk90) * 0.00001525878906;
    }
    if (partBeh->flags & 0x1000) {
        var_v0->unk28 = sqrtf((arg0->unk1C * arg0->unk1C) + (arg0->unk20 * arg0->unk20) + (arg0->unk24 * arg0->unk24)) * sp24 * 0.1f;
    } else {
        var_v0->unk28 = sp38->unk10 * sp24;
    }
    var_v0->unk3A = get_random_number_from_range(-sp38->unkA, sp38->unkA) + sp38->unk8;
    var_v0->unk38 = 0;
    var_v0->unk34 = 0.0f;
    if (D_800E2D00[0].word != 0) {
        var_v0->unk6C.word = D_800E2D00[0].word;
    } else if ((s32) sp28 != -1) {
        arg1->unk1E++;
        if (arg1->unk1E >= sp28->unk0) {
            arg1->unk1E = 0;
        }
        var_v0->unk6C.r = sp28[arg1->unk1E + 2].r;
        var_v0->unk6C.g = sp28[arg1->unk1E + 2].g;
        var_v0->unk6C.b = sp28[arg1->unk1E + 2].b;
        var_v0->unk6C.a = sp28[arg1->unk1E + 2].a;
    } else {
        var_v0->unk6C.r = sp38->unk14;
        var_v0->unk6C.g = sp38->unk15;
        var_v0->unk6C.b = sp38->unk16;
        var_v0->unk6C.a = sp38->unk17;
    }
    sp3C = partBeh->unk5C & 0xF00000;
    if (sp3C != 0) {
        if (sp3C & 0x100000) {
            var_v0->unk6C.r += get_random_number_from_range(-partBeh->unk98, partBeh->unk98);
        }
        if ((sp3C << 10) < 0) {
            var_v0->unk6C.g += get_random_number_from_range(-partBeh->unk99, partBeh->unk99);
        }
        if ((sp3C << 9) < 0) {
            var_v0->unk6C.b += get_random_number_from_range(-partBeh->unk9A, partBeh->unk9A);
        }
        if ((sp3C << 8) < 0) {
            var_v0->unk6C.a += get_random_number_from_range(-partBeh->unk9B, partBeh->unk9B);
        }
    }
    var_v0->unk60 = sp38->unkE;
    var_v0->unk5C = sp38->unkC * D_800E2EEC;
    if (sp38->unkC < 0xFF) {
        if (var_v0->unk40 & 0x1000) {
            var_v0->unk6 |= 0x100;
        } else {
            var_v0->unk6 |= 0x80;
        }
    }
    if (var_v0->unk60 < var_v0->unk3A) {
        var_v0->unk5E = (s16) (((sp38->unkD - sp38->unkC) * D_800E2EEC) / (var_v0->unk3A - var_v0->unk60));
    } else {
        var_v0->unk5E = 0;
    }
    sp23 = 0;
    var_v0->unk1A = sp38->unk6;
    if (var_v0->unk2C == 0x80) {
        var_v0->unk44 = (unk800B1CB8_44 *) func_8007C12C(sp38->unk4, 0);
        if (var_v0->unk44 != 0) {
            if ((*var_v0->unk44->unk8)->unk6 & 4) {
                if (var_v0->unk40 & 0x1000) {
                    var_v0->unk6 |= 0x100;
                } else {
                    var_v0->unk6 |= 0x80;
                }
            }
            if (partBeh->flags & 0x800) {
                var_v0->unk18 = get_random_number_from_range(0, var_v0->unk44->unk0 - 1) << 8;
                if ((var_v0->unk40 & 3) == 2) {
                    var_v0->unk18 |= 0xFF;
                }
            } else if ((var_v0->unk40 & 3) == 2) {
                var_v0->unk18 = (var_v0->unk44->unk0 << 8) - 1;
            } else {
                var_v0->unk18 = 0;
            }
        } else {
            sp23 = 1;
        }
    } else if ((var_v0->unk2C == 2) || (var_v0->unk2C == 1)) {
        sp30 = (TextureHeader **) var_v0->unk44;
        if (sp30 != 0) {
            (*sp30) = load_texture(sp38->unk4);
            if ((*sp30) != NULL) {
                if ((*sp30)->flags & 4) {
                    if (var_v0->unk40 & 0x1000) {
                        var_v0->unk6 |= 0x100;
                    } else {
                        var_v0->unk6 |= 0x80;
                    }
                }
                if (partBeh->flags & 0x800) {
                    var_v0->unk18 = get_random_number_from_range(0, ((*sp30)->numOfTextures >> 8) - 1) << 8;
                    if ((var_v0->unk40 & 3) == 2) {
                        var_v0->unk18 |= 0xFF;
                    }
                } else if ((var_v0->unk40 & 3) == 2) {
                    var_v0->unk18 = (*sp30)->numOfTextures - 1;
                } else {
                    var_v0->unk18 = 0;
                }
            } else {
                sp23 = 1;
            }
        }
    }
    if (sp23 == 0) {
        if (var_v0->unk2C == 1) {
            func_800AF0A4((Object* ) var_v0);
        }
        if (var_v0->unk2C == 2) {
            func_800AF0F0((Object* ) var_v0);
        }
    }
    func_800B03C0((Object *) var_v0, (ObjectTransform *) arg0, (unk800B03C0_arg2 *) arg1, (Object *) partBeh);
    if (partBeh->flags & 0x80) {
        var_v0->unk0 = partBeh->unk44;
        var_v0->unk2 = partBeh->unk46;
        var_v0->unk4 = partBeh->unk48;
    } else {
        var_v0->unk0 = arg0->unk0 + partBeh->unk44;
        var_v0->unk2 = arg0->unk2 + partBeh->unk46;
        var_v0->unk4 = arg0->unk4 + partBeh->unk48;
    }
    sp3C = partBeh->unk5C & 0x3800;
    if (sp3C != 0) {
        if (sp3C & 0x800) {
            var_v0->unk0 += get_random_number_from_range(-partBeh->unk80, partBeh->unk80);
        }
        if (sp3C & 0x1000) {
            var_v0->unk2 += get_random_number_from_range(-partBeh->unk82, partBeh->unk82);
        }
        if (sp3C & 0x2000) {
            var_v0->unk4 += get_random_number_from_range(-partBeh->unk84, partBeh->unk84);
        }
    }
    var_v0->unk62 = partBeh->unk4A;
    var_v0->unk64 = partBeh->unk4C;
    var_v0->unk66 = partBeh->unk4E;
    sp3C = partBeh->unk5C & 0x1C000;
    if (sp3C != 0) {
        if (sp3C & 0x4000) {
            var_v0->unk62 += get_random_number_from_range(-partBeh->unk86, partBeh->unk86);
        }
        if (sp3C & 0x8000) {
            var_v0->unk64 += get_random_number_from_range(-partBeh->unk88, partBeh->unk88);
        }
        if ((sp3C << 0xF) < 0) {
            var_v0->unk66 += get_random_number_from_range(-partBeh->unk8A, partBeh->unk8A);
        }
    }
    func_800B0010((Object *) var_v0, (Object *) arg0, (unk800B03C0_arg2 *) arg1, (Object *) partBeh);
    var_v0->unk68 = D_800E2E2C[(var_v0->unk40 >> 4) & 7];
    if (var_v0->unk39 == 5) {
        var_v0->unk58 = sqrtf((var_v0->unk1C * var_v0->unk1C) + (var_v0->unk20 * var_v0->unk20) + (var_v0->unk24 * var_v0->unk24));
    }
    if (partBeh->flags & 2) {
        arg1->unk6++;
        if (arg1->unk6 >= partBeh->unk1A) {
            arg1->unkC.unkC += partBeh->unk1C;
            arg1->unkC.unkE += partBeh->unk1E;
            arg1->unkC.unk10 += partBeh->unk18;
            arg1->unk6 -= partBeh->unk1A;
        }
    }
    if (partBeh->flags & 8) {
        arg1->unk7++;
        if (arg1->unk7 >= partBeh->unk28) {
            arg1->unkC.unk12 += partBeh->unk2A;
            arg1->unkC.unk14 += partBeh->unk2C;
            arg1->unkC.unk16 += partBeh->unk2E;
            arg1->unk7 -= partBeh->unk28;
        }
    }
    if (var_v0->unk44 == 0) {
        func_800B2040((Particle2 *) var_v0);
        return NULL;
    } else {   
        return (Particle2 *) var_v0;
    }
}


unk800B1CB8 *func_800B1CB8(s32 arg0) {
    s32 i;
    unk800B1CB8 *var_v1;

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
                    var_v1 = &D_800E2CC0[i];
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
                    var_v1 = &D_800E2CA8[i];
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
                    var_v1 = &D_800E2CB4[i];
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
                    var_v1 = &D_800E2CCC[i];
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
                    while (D_800E2CD8[i].unk0.unk2C != 0) {
                        i++;
                    }
                    D_800E2CD8[i].unk0.unk2C = 4;
                    D_800E2CD0++;
                    var_v1 = &D_800E2CD8[i].unk0;
                }
            }
            break;
    }
    if (var_v1 != NULL) {
        var_v1->unk48 = -1;
    }
    return var_v1;
}

void func_800B2040(Particle2 *arg0) {
    TextureHeader *tex;

    switch (arg0->unk2C) {
    case 0x80:
        if (D_800E2CB8 > 0) {
            if (arg0->unk44 != NULL) {
                free_sprite((Sprite *) arg0->unk44);
            }
            D_800E2CB8--;
            arg0->unk2C = 0;
        }
        break;
    case 0:
        return;
    case 1:
        if (D_800E2CA0 > 0) {\
            if (((unk800B2260_C_44 *) arg0->unk44)->texture != NULL) {
                free_texture(arg0->unk44_1->texture);
            }
            D_800E2CA0--;
            arg0->unk2C = 0;
        }
        break;
    case 2:
        if (D_800E2CAC > 0) {
            tex = arg0->unk44_1->texture;
            if (tex != NULL) {
                free_texture(tex);
            }
            D_800E2CAC--;
            arg0->unk2C = 0;
        }
        break;
    case 3:
        if (D_800E2CC4 > 0) {
            tex = arg0->unk44_1->texture;
            if (tex != NULL) {
                free_texture(tex);
            }
            D_800E2CC4--;
            arg0->unk2C = 0;
        }
        break;
    case 4:
        if (D_800E2CD0 > 0) {
            func_800B263C(arg0);
            tex = arg0->unk44_1->texture;
            if (tex != NULL) {
                free_texture(tex);
            }
            D_800E2CD0--;
            arg0->unk2C = 0;
        }
        break;
    }
}


void func_800B2260(Particle *arg0) {
    Particle2 *temp_v0;
    s32 i;

    if (arg0->flags & 0x400) {
        if (arg0->unkC_60 != NULL) {
            for (i = 0; i < arg0->unk6; i++) {
                temp_v0 = arg0->unkC_60[i];
                temp_v0->unk38.half.unk3A = 0;
                temp_v0->unk70 = 0;
            }
            free_from_memory_pool(arg0->unkC_60);
            arg0->unkC_60 = NULL;
        }
    }
}

void func_800B22FC(Particle2 *arg0, s32 arg1) {
    LevelModelSegmentBoundingBox *temp_v0_2;
    Particle2 *sp20;

    D_80127C80 = arg1;
    sp20 = NULL;
    if (arg0->unk2C == 3) {
        func_800B26E0();
    } else {
        if (arg0->unk40 & 3) {
            if (D_80127C80 > 0) {
                sp20 = NULL;
                func_800B2FBC(arg0);
                sp20 = NULL;
            }
        }
        if (arg0->unk2C == 4) {
            sp20 = arg0;
            arg0->unk75 = 1 - arg0->unk75;
            arg0->unk77 = 0;
        }
        if (sp20 == NULL || (sp20 != NULL && sp20->unk70 != 0)) {
            if (arg0->unk38.byte.unk39 == 2) {
                func_800B3358(arg0);
            } else if (arg0->unk38.byte.unk39 == 3) {
                func_800B3240(arg0);
            } else if (arg0->unk38.byte.unk39 == 4) {
                func_800B3140(arg0);
            } else if (arg0->unk38.byte.unk39 == 5) {
                func_800B3564(arg0);
            } else {
                func_800B34B0(arg0);
            }
        }
        temp_v0_2 = get_segment_bounding_box(arg0->unk2E);
        if (temp_v0_2 != NULL) {
            if (arg0->trans.x_position < temp_v0_2->x1 || temp_v0_2->x2 < arg0->trans.x_position || arg0->trans.y_position < temp_v0_2->y1 || temp_v0_2->y2 < arg0->trans.y_position || arg0->trans.z_position < temp_v0_2->z1 || temp_v0_2->z2 < arg0->trans.z_position) {
                arg0->unk2E = get_level_segment_index_from_position(arg0->trans.x_position, arg0->trans.y_position, arg0->trans.z_position);
            }
        } else {
            arg0->unk2E = get_level_segment_index_from_position(arg0->trans.x_position, arg0->trans.y_position, arg0->trans.z_position);
        }
        arg0->unk38.half.unk3A -= D_80127C80;
        if (arg0->unk38.half.unk3A <= 0) {
            gParticlePtrList_addObject((Object*) arg0);
        } else {
            if (arg0->unk60_halfs.unk60 == 0) {
                arg0->unk5C_halfs.unk5C += D_80127C80 * arg0->unk5C_halfs.unk5E;
                if (arg0->unk5C_halfs.unk5C < 0xFF) {
                    if (arg0->unk40 & 0x1000) {
                        arg0->trans.unk6 |= 0x100;
                    } else {
                        arg0->trans.unk6 |=  0x80;
                    }
                }
            } else {
                arg0->unk60_halfs.unk60 -= D_80127C80;
                if (arg0->unk60_halfs.unk60 < 0) {
                    arg0->unk5C_halfs.unk5C -= (arg0->unk60_halfs.unk60 * arg0->unk5C_halfs.unk5E);
                    arg0->unk60_halfs.unk60 = 0;
                }
            }
        }
    }
}


void func_800B263C(Particle2 *arg0) {
    Particle *new_var;
    Particle2 *new_var2;
    Particle *temp_v0;
    s32 i;

    temp_v0 = (Particle *) arg0->unk70;
    if (temp_v0 != NULL) {
        new_var = temp_v0;
        if (temp_v0->unk6 != 0) {
            if (arg0 == temp_v0->unkC_60[arg0->unk74]) {
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

GLOBAL_ASM("asm/non_matchings/particles/func_800B26E0.s")

void func_800B2FBC(Particle2 *arg0) {
    s32 someFlag;
    s32 keepGoing;
    s32 i;
    s32 var_a1;
    s32 someFlag2;
    s32 someFlag3;
    s32 someFlag4;
    
    keepGoing = -1;

    i = 128; // This is needed to match.
    if (arg0->unk2C == i) {
        var_a1 = arg0->unk44->unk0 * 256;
    } else {
        var_a1 = arg0->unk44->unk0Ptr->unk12;
    }

    someFlag4 = arg0->unk40 & 1;
    someFlag2 = arg0->unk40 & 2;
    someFlag3 = arg0->unk40 & 4;
    someFlag = arg0->unk40 & 8;
    for (i = 0; (i++ < D_80127C80) && keepGoing;) {
        if (!someFlag) {
            arg0->unk18 += arg0->unk1A;
            if (arg0->unk18 >= var_a1) {
                if (someFlag2) {
                    arg0->unk18 = ((var_a1 * 2) - arg0->unk18) - 1;
                    someFlag = TRUE;
                    arg0->unk40 |= 8;
                } else if (someFlag3) {
                    arg0->unk18 -= var_a1;
                } else {
                    arg0->unk18 = var_a1 - 1;
                    keepGoing = FALSE;
                    arg0->unk40 &= ~3;
                }
            }
        } else {
            arg0->unk18 -= arg0->unk1A;
            if (arg0->unk18 < 0) {
                if (someFlag3) {
                    if (someFlag4) {
                        arg0->unk18 = -arg0->unk18;
                        someFlag = FALSE;
                        arg0->unk40 &= ~8;
                    } else {
                        arg0->unk18 += var_a1;
                    }
                } else {
                    arg0->unk18 = 0;
                    keepGoing = FALSE;
                    arg0->unk40 &= ~3;
                }
            }
        }
    }
}

