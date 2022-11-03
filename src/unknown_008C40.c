/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80008040 */

#include "unknown_008C40.h"
#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "unknown_005740.h"
#include "memory.h"
#include "audio.h"

/************ .data ************/

s32 D_800DC6E0 = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .rodata ************/

const char D_800E4D00[] = "OUT OF AUDIO POINTS\n";
const char D_800E4D18[] = "amAudioLineAddVertex: Exceeded maximum number of lines (%d)\n";
const char D_800E4D58[] = "amAudioLineAddVertex: Exceeded maximum number of line vertices (%d)\n";
const char D_800E4DA0[] = "amReverbLineAddVertex: Exceeded maximum number of lines (%d)\n";
const char D_800E4DE0[] = "amReverbLineAddVertex: Exceeded maximum number of line vertices (%d)\n";

const char D_800E4E28[] = "Audio line definition error (less than 2 vertices on line %d)\n";
const char D_800E4E68[] = "Audio line definition error (line=%d, vertex=%d)\n";
const char D_800E4E9C[] = "Reverb line definition error (less than 2 vertices on line %d)\n";
const char D_800E4EDC[] = "Reverb line definition error (line=%d, vertex=%d)\n";

/*********************************/

/************ .bss ************/

extern s8 D_8011AC18;

/*******************************/

#ifdef NON_EQUIVALENT
void func_80008040(void) {
    u32 temp_v1;
    //? *phi_v1;
    s32 i;

    func_80002128(&D_80119C40, NULL, NULL);
    D_80119C48 = allocate_from_main_pool_safe(1440, COLOUR_TAG_CYAN);
    //D_80119C50 = allocate_from_main_pool_safe(160, COLOUR_TAG_CYAN);
    D_80119C44 = allocate_from_main_pool_safe(160, COLOUR_TAG_CYAN);
    D_800DC6E0 = 0;
    // phi_v1 = &D_80119C58;
    // do {
    //     temp_v1 = phi_v1 + 0x180;
    //     temp_v1->unk-8 = 0;
    //     phi_v1 = (? *) temp_v1;
    // } while (temp_v1 < (u32) &D_8011A6D8);
    // for (i = 0; i < 384; i++) {
    //     D_80119C48[i]->unk18 = 0;
    //     D_80119C48[i]->unk3C = 0;
    //     D_80119C48[i]->unk60 = 0;
    //     D_80119C48[i]->unk84 = 0;
    // }
    func_80008174();
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008040.s")
#endif

void func_80008140(void) {
    func_800018E0();
    D_8011AC18 = 1;
}

void func_80008168(void) {
    D_8011AC18 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008174.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008438.s")

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800090C0.s")

//Best I can figure, this measures the distance between XYZ values.
s32 func_800092A8(f32 inX, f32 inY, f32 inZ, floatXYZVals *floatXYZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 dx, dy, dz;
    f32 x1, y1, z1;
    f32 x2, y2, z2;

    f32 temp;
    f32 ret;

    x1 = floatXYZ->x1;
    y1 = floatXYZ->y1;
    z1 = floatXYZ->z1;
    x2 = floatXYZ->x2;
    y2 = floatXYZ->y2;
    z2 = floatXYZ->z2;
    temp = 0.0f;

    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;

    if (dx == 0.0f && dy == 0.0f && dz == 0.0f) {
        temp = 0.0f;
    } else {
        temp = ((inX - x1) * dx + (inY - y1) * dy + (inZ - z1) * dz) /
                (dx * dx + dy * dy + dz * dz);
    }

    if (temp < 0.0f) {
        *outX = x1;
        *outY = y1;
        *outZ = z1;
        dx = x1 - inX;
        dy = y1 - inY;
        dz = z1 - inZ;
        ret = sqrtf(dx * dx + dy * dy + dz * dz);
    } else if (temp > 1.0f) {
        *outX = x2;
        *outY = y2;
        *outZ = z2;
        dx = x2 - inX;
        dy = y2 - inY;
        dz = z2 - inZ;
        ret = sqrtf(dx * dx + dy * dy + dz * dz);
    } else {
        *outX = temp * dx + x1, // Comma required here as this was likely all one line.
        *outY = temp * dy + y1,
        *outZ = temp * dz + z1;

        ret = sqrtf((*outX - inX) * (*outX - inX) + (*outY - inY) * (*outY - inY) + (*outZ - inZ) * (*outZ - inZ));
    }

    return ret;
}

// Another function related to playing sound.
// Play Sound at position?
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009558.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800095E8.s")
#if 0
// I think this function is used to update the world position of any sound associated with the given soundmask.
//This matches, but it breaks update_player_racer
void update_spatial_audio_position(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->x = arg1;
    arg0->y = arg2;
    arg0->z = arg3;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/update_spatial_audio_position.s")
#endif

void func_800096F8(s32 arg0) {
    s32 i;
    s32 *v0 = D_80119C44;
    for (i = 0; i < 40; i++) {
        if (arg0 == *v0) {
            func_8000A2E8(i);
            break;
        }
        v0++;
    }
}
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000974C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800098A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009968.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800099EC.s")

s32 func_80009AB4(u8 arg0) {
    s32 ret;
    s32 i;
    unk8011A6D8 *levelHeader;
    unk8011A6D8_04 *var_a2; //Probably a Vec3f
    
    ret = 1;
    levelHeader = &D_8011A6D8[arg0];
    var_a2 = &levelHeader->unk4;

    if (levelHeader->unkB8 <= 0) {
        return 0;
    }

    for (i = 0; i < levelHeader->unkB8; i++, var_a2++) {
        if ((var_a2->unk0 == -100000.0f)|| 
            (var_a2->unk0 + 1 == -100000.0f)|| 
            (var_a2->unk0 + 2 == -100000.0f)) {
            ret = 0;
        }
    }

    return ret;
}

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009B7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009D6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A184.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A2E8.s")

typedef struct unk800A414_arg3 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} unk800A414_arg3;

void func_8000A414(Gfx **arg0, Vertex **arg1, Triangle **arg2, unk800A414_arg3 *arg3, u8 arg4, u8 arg5, u8 arg6) {
    Gfx *sp34;
    Vertex *sp30;
    Triangle *sp2C;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    s16 sp24;
    s16 sp22;
    s16 sp20;


    sp2A =  arg3->unk0;
    sp28 =  arg3->unk4;
    sp26 =  arg3->unk8;
    sp24 =  arg3->unkC;
    sp22 =  arg3->unk10;
    sp20 =  arg3->unk14;
    sp34 = *arg0;
    
    sp30 = *arg1;
    sp2C = *arg2;
    func_8007B4C8(&sp34, NULL, 0U);
    gDkrVertices(sp34++, OS_PHYSICAL_TO_K0(sp30), (((s32)OS_PHYSICAL_TO_K0(sp30)) & 6) | 0x18, 0x28);
    gDkrTriangles(sp34++, OS_PHYSICAL_TO_K0(sp2C), 2, 0);
    sp30[0].x = sp2A;
    sp30[0].y = (s16) (sp28 + 5);
    sp30[0].z = sp26;
    sp30[0].r = arg4;
    sp30[0].g = arg5;
    sp30[0].b = arg6;
    sp30[0].a = 255;
    sp30[1].x = sp2A;
    sp30[1].y = (s16) (sp28 - 5);
    sp30[1].z = sp26;
    sp30[1].r = arg4;
    sp30[1].g = arg5;
    sp30[1].b = arg6;
    sp30[1].a = 255;
    sp30[2].x = sp24;
    sp30[2].y = (s16) (sp22 + 5);
    sp30[2].z = sp20;
    sp30[2].r = 255;
    sp30[2].g = 255;
    sp30[2].b = 255;
    sp30[2].a = 255;
    sp30[3].x = sp24;
    sp30[3].y = (s16) (sp22 - 5);
    sp30[3].z = sp20;
    sp30[3].r = 255;
    sp30[3].g = 255;
    sp30[3].b = 255;
    sp30[3].a = 255;
    sp30 += 4;
    
    sp2C[0].drawBackface = 0x40; // 0x40 = Draw backface.
    sp2C[0].vi0 = 2;
    sp2C[0].vi1 = 1;
    sp2C[0].vi2 = 0;
    sp2C[0].uv0.u = 0x3E0;
    sp2C[0].uv0.v = 0x3E0;
    sp2C[0].uv1.u = 0x3E0;
    sp2C[0].uv1.v = 0;
    sp2C[0].uv2.u = 1;
    sp2C[0].uv2.v = 0;
    sp2C[1].drawBackface = 0x40;
    sp2C[1].vi0 = 3;
    sp2C[1].vi1 = 2;
    sp2C[1].vi2 = 1;
    sp2C[1].uv0.u = 1;
    sp2C[1].uv0.v = 0x3E0;
    sp2C[1].uv1.u = 0x3E0;
    sp2C[1].uv1.v = 0x3E0;
    sp2C[1].uv2.u = 1;
    sp2C[1].uv2.v = 0;
    sp2C += 2;
    
    *arg0 = sp34;
    *arg1 = sp30;
    *arg2 = sp2C;
}
