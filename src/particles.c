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

/************ .rodata ************/

// Need to move this to the correct file when we figure out where the lens flare code is.
const char D_800E87F0[] = "\nMaximum limit of %d lens flare switches, per level, has been exceeded.";

// This is most likely a file boundary. Not sure where the split occurs though.
const int D_800E8838[2] = { 0, 0 };

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
s32 *D_800E2CA8 = NULL;
s32 D_800E2CAC = 0;
s32 D_800E2CB0 = 0;
s32 *D_800E2CB4 = NULL;
s32 D_800E2CB8 = 0;
s32 D_800E2CBC = 0;
s32 *D_800E2CC0 = NULL;
s32 D_800E2CC4 = 0;
s32 D_800E2CC8 = 0;
s32 *D_800E2CCC = NULL;
s32 D_800E2CD0 = 0;
s32 D_800E2CD4 = 0;
s32 *D_800E2CD8 = NULL;
s32 D_800E2CDC = 0;
s32 *D_800E2CE0 = NULL;
s32 *D_800E2CE4 = NULL;
s32 gParticlesAssetTableCount = 0;
s32 *gParticlesAssets = NULL;

unk800E2CF0 **gParticlesAssetTable = NULL;
s32 gParticleBehavioursAssetTableCount = 0;
s32 *gParticleBehavioursAssets = NULL;
ParticleBehavior **gParticleBehavioursAssetTable = NULL;
s32 D_800E2D00[2] = { 0, 0 };

// Are these just Triangles?
unk800E2D08 D_800E2D08[5] = {
    { 0x4000, 0x0102, 0x0100, 0x0000, 0x0000, 0x01E0, 0x0100, 0x01E0 },
    { 0x4000, 0x0203, 0x0100, 0x0000, 0x0100, 0x01E0, 0x01E0, 0x01E0 },
    { 0x4001, 0x0204, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000, 0x01E0 },
    { 0x4002, 0x0305, 0x0100, 0x0000, 0x01E0, 0x0000, 0x01E0, 0x01E0 },
    { 0x4000, 0x0103, 0x0100, 0x0000, 0x0000, 0x01E0, 0x01E0, 0x01E0 },
};

unk800E2D58 D_800E2D58[5] = {
    { 0x0000, 0x01FF, 0x01FF },
    { 0x0000, 0x01FF, 0x01FF },
    { 0x0000, 0x0000, 0x01FF },
    { 0x0000, 0x0000, 0x01FF },
    { 0x0000, 0x01FF, 0x01FF },
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

unk800E2D58 D_800E2DF8[8] = {
    { 0x0000, 0x0000, 0x01FF },
    { 0x0000, 0x01FF, 0x01FF },
    { 0x0000, 0x0000, 0x01FF },
    { 0x0000, 0x01FF, 0x01FF },
    { 0x0000, 0x0000, 0x01FF },
    { 0x0000, 0x01FF, 0x01FF },
    { 0x0000, 0x0000, 0x01FF },
    { 0x0000, 0x01FF, 0x01FF },
};

s16 D_800E2E28 = 0;

f32 D_800E2E2C[8] = {
    0.0f, 0.1, 0.2f, 0.3f, 0.45f, 0.525f, 0.6f, 0.8f
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
s32 D_80127CCC;
u16 D_80127CD0;
u16 D_80127CD2;
s32 D_80127CD4;
s8 gDebugPrintBufferStart[2300];
s32 gDebugPrintBufferEnd[1026];
OSThread D_801295E0;
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
    while (((s32) gParticlesAssetTable[gParticlesAssetTableCount + 1]) != -1){
        gParticlesAssetTableCount++;
    }

    gParticlesAssets = (s32 *) load_asset_section_from_rom(ASSET_PARTICLES);
    for (i = 0; i < gParticlesAssetTableCount; i++) {
    gParticlesAssetTable[i] = (unk800E2CF0 *) (((u8 *) gParticlesAssets) + ((s32) gParticlesAssetTable[i]));
    }

  gParticleBehavioursAssetTable = (ParticleBehavior **) load_asset_section_from_rom(ASSET_PARTICLE_BEHAVIORS_TABLE);
  gParticleBehavioursAssetTableCount = -1; 
  while (((s32) gParticleBehavioursAssetTable[gParticleBehavioursAssetTableCount + 1]) != (-1)) {
      gParticleBehavioursAssetTableCount++;
  }

    gParticleBehavioursAssets = (s32 *) load_asset_section_from_rom(ASSET_PARTICLE_BEHAVIORS);
    for (i = 0; i < gParticleBehavioursAssetTableCount; i++) {
        new_var = -1;
        gParticleBehavioursAssetTable[i] = (ParticleBehavior *) (((u8 *) gParticleBehavioursAssets) + ((s32) gParticleBehavioursAssetTable[i]));
        if (((u32) gParticleBehavioursAssetTable[i]->unk9C) != new_var)
        {
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

void func_800AF134(unk800AF29C *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    ParticleBehavior *temp;
    if (arg2 >= gParticlesAssetTableCount) {
        arg2 = 0;
    }
    if (arg1 >= gParticleBehavioursAssetTableCount) {
        arg1 = 0;
    }
    temp = gParticleBehavioursAssetTable[arg1];
    if ((arg0->unk8 != arg2) || (temp != arg0->unk0)) {
        func_800B2260(arg0);
        func_800AF29C(arg0, arg1, arg2, arg3, arg4, arg5);
    }
}

void func_800AF1E0(unk800AF29C *arg0, s32 arg1, s32 arg2) {
    ParticleBehavior *temp_v0;

    if (arg1 < gParticleBehavioursAssetTableCount) {
        temp_v0 = (ParticleBehavior *)gParticleBehavioursAssetTable[arg1];
        func_800AF29C(arg0, arg1, arg2, temp_v0->unk4, temp_v0->unk8, temp_v0->unkC);
    }
}

void func_800AF29C(unk800AF29C *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    ParticleBehavior *temp_v1;
    s32 temp_v0_2;
    s32 flags;

    temp_v1 = gParticleBehavioursAssetTable[arg1];
    arg0->unk8 = arg2;
    arg0->unk18 = arg3;
    arg0->unk0 = temp_v1;
    arg0->unk1A = arg4;
    arg0->unk1C = arg5;
    arg0->unk1E = 0;

    flags = temp_v1->flags;

    if (flags & 0x4000) {
        arg0->unk4 = 0x4000;
        arg0->unk6 = 0;
        arg0->unkB.unkC_4000.unkC = 0.0f;
        arg0->unkB.unkC_4000.unk10 = 0.0f;
        arg0->unkB.unkC_4000.unk14 = 0.0f;
    } else if (flags & 0x400) {
        arg0->unk6 = 0;
        arg0->unk4 = 0x400;
        temp_v0_2 = gParticlesAssetTable[arg2]->unk8;
        if (temp_v0_2 < 0x100) {
            arg0->unk7 = temp_v0_2;
        } else {
            arg0->unk7 = 0xFF;
        }
        arg0->unkB.unkC_400.unkC = (s32 *)allocate_from_main_pool_safe(arg0->unk7 * 4, COLOUR_TAG_SEMITRANS_GREY);
        arg0->unkB.unkC_400.unk10 = temp_v1->unk14;
        arg0->unkB.unkC_400.unk12 = temp_v1->unk16;
        arg0->unkB.unkC_400.unk14 = temp_v1->unk22;
        arg0->unkB.unkC_400.unk16 = temp_v1->unk24;
    } else {
        arg0->unk4 = 0;
        arg0->unkB.unkC.unkC = temp_v1->unk14;
        arg0->unkB.unkC.unkE = temp_v1->unk16;
        arg0->unkB.unkC.unk10 = temp_v1->unk18;
        arg0->unkB.unkC.unk12 = temp_v1->unk22;
        arg0->unkB.unkC.unk14 = temp_v1->unk24;
        arg0->unkB.unkC.unk16 = temp_v1->unk26;
    }
}

#ifdef NON_EQUIVALENT

// Should be functionally equivalent.
void func_800AF404(s32 arg0) {
    s32 i;

    D_800E2E28 = (D_800E2E28 + (arg0 * 64)) & 0x1FF;
    for (i = 0; i < 5; i++) {
        D_800E2D08[i].unk6 = D_800E2D58[i].unk0 + D_800E2E28;
        D_800E2D08[i].unkA = D_800E2D58[i].unk2 + D_800E2E28;
        D_800E2D08[i].unkE = D_800E2D58[i].unk4 + D_800E2E28;
    }
    for (i = 0; i < 8; i++) {
        D_800E2D78[i].unk6 = D_800E2DF8[i].unk0 + D_800E2E28;
        D_800E2D78[i].unkA = D_800E2DF8[i].unk2 + D_800E2E28;
        D_800E2D78[i].unkE = D_800E2DF8[i].unk4 + D_800E2E28;
    }
}

#else
GLOBAL_ASM("asm/non_matchings/particles/func_800AF404.s")
#endif

void func_800AF52C(Object *obj, s32 arg1) {
    s32 i;
    Object_6C_800AF52C *temp_v0;
    Object_6C_800AF52C_0* temp_v1;
    Object_6C_800AF52C_C * temp;

    temp_v0 = &((Object_6C_800AF52C*)obj->unk6C)[arg1];
    temp_v1 = temp_v0->unk0;
    temp_v0->unkA = 0;
    if (temp_v0->unk4 & 0x4000) {
        ((ObjectSegment*)temp_v0)->trans.x_position = obj->segment.trans.x_position;
        ((ObjectSegment*)temp_v0)->trans.y_position = obj->segment.trans.y_position;
        ((ObjectSegment*)temp_v0)->trans.z_position = obj->segment.trans.z_position;
    } else if (temp_v0->unk4 & 0x400) {
        temp_v0->unkA = (s16) (gParticlesAssetTable[temp_v0->unk8]->unk17 << 8);

        if (temp_v0->unk6 > 0) { // Useless if statement, since the loop already does this.
            for (i = 0; i < temp_v0->unk6; i++){
                temp = temp_v0->unkC_arr[i];
                temp->unk3A = 0;
            }
        }
        if (temp_v1->unk0 & 1) {
            temp_v0->unk10 = (s16) temp_v1->unk14;
            temp_v0->unk12 = (s16) temp_v1->unk16;
        }
        if (temp_v1->unk0 & 4) {
            temp_v0->unk14 = (s16) temp_v1->unk22;
            temp_v0->unk16 = (s16) temp_v1->unk24;
        }
    } else {
        if (temp_v1->unk0 & 1) {
            temp_v0->unk6 = 0U;
            temp_v0->unkC = (s16) temp_v1->unk14;
            temp_v0->unkE = (s16) temp_v1->unk16;
            temp_v0->unk10 = (s16) temp_v1->unk18;
        }
        if (temp_v1->unk0 & 4) {
            temp_v0->unk7 = 0;
            temp_v0->unk12 = (s16) temp_v1->unk22;
            temp_v0->unk14 = (s16) temp_v1->unk24;
            temp_v0->unk16 = (s16) temp_v1->unk26;
        }
    }
    temp_v0->unk4 &= 0xFDFF;
    temp_v0->unk4 |= 0xA000;
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

void func_800AFE5C(s32 arg0, Object_6C_800AF52C *arg1) {
    unk800B0698 *temp_s0;
    Object *tempObj;
    Object *tempObj2;
    s32 i;
    Object_6C_800AF52C_0 *temp_s4;

    temp_s4 = arg1->unk0;
    if (arg1->unk4 & 0x4000) {
        tempObj = func_800B0BAC();
        if (tempObj != NULL) {
            func_8000E9D0(tempObj);
        }
        arg1->unk4 &= 0xDFFF;
        if (arg1->unk6 + 64 > 255) {
            arg1->unk6 = 255;
        } else {
            arg1->unk6 += 64;
        }
    } else if (arg1->unk4 & 0x400) {
        if (arg1->unk6 < arg1->unk7) {
            temp_s0 = func_800B0698(arg0, arg1);
            arg1->unk4 &= 0xDFFF;
            if (temp_s0 != NULL) {
                func_8000E9D0((Object*)temp_s0);
                temp_s0->unk74 = (u8) arg1->unk6;
                temp_s0->unk40 |= 0x2000;
                arg1->unkC_arr[arg1->unk6] = temp_s0;
                arg1->unk6++;
            }
        }
    } else {
        while (arg1->unkA >= temp_s4->unk40) {
            arg1->unkA -= temp_s4->unk40;
            for (i = 0; i < temp_s4->unk42; i++) {
                tempObj2 = func_800B1130(arg0, arg1);
                if (tempObj2 != NULL) {
                    func_8000E9D0(tempObj2);
                    func_800B22FC(tempObj2, arg1->unkA);
                }
                arg1->unk4 &= ~0x2000;
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/particles/func_800B0010.s")
GLOBAL_ASM("asm/non_matchings/particles/func_800B03C0.s")
GLOBAL_ASM("asm/non_matchings/particles/func_800B0698.s")
GLOBAL_ASM("asm/non_matchings/particles/func_800B0BAC.s")
GLOBAL_ASM("asm/non_matchings/particles/func_800B1130.s")
GLOBAL_ASM("asm/non_matchings/particles/func_800B1CB8.s")
GLOBAL_ASM("asm/non_matchings/particles/func_800B2040.s")

void func_800B2260(unk800AF29C *arg0) {
    unk800B2260_C *temp_v0;
    s32 i;

    if (arg0->unk4 & 0x400) {
        if (arg0->unkB.unkC_60 != NULL) {
            for (i = 0; i < arg0->unk6; i++) {
                temp_v0 = arg0->unkB.unkC_60[i];
                temp_v0->unk3A = 0;
                temp_v0->unk70 = 0;
            }
            free_from_memory_pool(arg0->unkB.unkC_60);
            arg0->unkB.unkC_60 = NULL;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/particles/func_800B22FC.s")

void func_800B263C(unk800B2260_C *arg0) {
    unk800AF29C *new_var;
    unk800B2260_C *new_var2;
    unk800AF29C *temp_v0;
    s32 i;

    temp_v0 = (unk800AF29C *) arg0->unk70;
    if (temp_v0 != NULL) {
        new_var = temp_v0;
        if (temp_v0->unk6 != 0) {
            if (arg0 == temp_v0->unkB.unkC_60[arg0->unk74]) {
                temp_v0->unk6--;
                for (i = arg0->unk74; i < temp_v0->unk6; i++) {
                    new_var->unkB.unkC_60[i] = new_var->unkB.unkC_60[i + 1];
                    new_var2 = new_var->unkB.unkC_60[i];
                    new_var2->unk74 = i;
                }
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/particles/func_800B26E0.s")
GLOBAL_ASM("asm/non_matchings/particles/func_800B2FBC.s")
