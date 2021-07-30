/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800249E0 */

#include "unknown_0255E0.h"

#include "types.h"
#include "macros.h"
#include "structs.h"

/* Size: 0x44 bytes */
typedef struct unk80120AC0 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8  pad6[6];
    f32 x_position;
    f32 y_position;
    f32 z_position;
    f32 pad18;
    f32 unk1C;
    f32 pad20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    s16 unk34;
    s16 pad36;
    s16 unk38;
    s8  pad3A;
    s8  unk3B;
    u8  pad3C[8];
} unk80120AC0;

/************ .data ************/

s32 D_800DC870 = 0; // Currently unknown, might be a different type.
unknown800DC874 D_800DC874 = { -128, 40, -1 };
unknown800DC874 D_800DC87C = { -125, 70, -1 };

f32 D_800DC884[10] = { 
    0.0f, 0.125f, 0.25f, 0.375f,
    0.5f, 0.625f, 0.75f, 0.875f
};

f32 D_800DC8AC[27] = {
    50.0f, 0.0f, 32.0f, -50.0f, 
    0.0f, 32.0f, -50.0f, 100.0f, 
    32.0f, 0.0f, 0.0f, 32.0f, 
    130.0f, 60.0f, -68.0f, 130.0f, 
    -60.0f, -68.0f, 0.0f, 0.0f, 
    32.0f, -130.0f, -60.0f, -68.0f, 
    -130.0f, 60.0f, -68.0f
};

LevelModel* D_800DC918 = NULL;
LevelHeader *D_800DC91C = NULL;

s32 D_800DC920 = -1;
s32 D_800DC924 = 0;
s32 D_800DC928 = 0; // Currently unknown, might be a different type.

s8 D_800DC92C[24] = { 
    0, 1, 4, 1, 2, 4, 2, 3, 
    4, 3, 0, 4, 5, 6, 1, 1, 
    0, 5, 3, 2, 7, 7, 8, 3
    // There may or may not be extra zeroes here.
};

/*******************************/

/************ .rodata ************/

const char D_800E5DF0[] = "TT CAM";
const char D_800E5DF8[] = "Solid Clipping x0=x1 Error!!!\n";
const char D_800E5E10[] = "TrackGetHeight() - Overflow!!!\n";

/*********************************/

/************ .bss ************/

s32 D_8011B0A0;
s32 D_8011B0A4;
s32 D_8011B0A8;
s32 D_8011B0AC;

typedef struct{
    s16 unk00;
    s16 unk02;
    s16 unk04;
}unk8011B0B0;
unk8011B0B0 *D_8011B0B0;

s32 D_8011B0B4;
Object *D_8011B0B8;
s32 D_8011B0BC;
s32 D_8011B0C0;
s32 D_8011B0C4;
s32 D_8011B0C8;
s32 D_8011B0CC;
s32 D_8011B0D0;
s32 D_8011B0D4;
s32 D_8011B0D8;
s32 D_8011B0DC;
s8 D_8011B0E0;
s8 D_8011B0E1;
s8 D_8011B0E2;
s8 D_8011B0E3;
f32 D_8011B0E4;
f32 D_8011B0E8;
f32 D_8011B0EC;
s32 D_8011B0F0;
s32 D_8011B0F4;
s32 D_8011B0F8;
s32 D_8011B0FC;
s32 D_8011B100;
s32 D_8011B104;
s32 D_8011B108;
s32 D_8011B10C;
s32 D_8011B110;
s32 D_8011B114;
s32 D_8011B118;
s32 D_8011B11C;
s32 D_8011B120[128];
s32 D_8011B320[4];
s32 D_8011B330[960];
s32 D_8011C230[2];
s32 D_8011C238[96];
s32 D_8011C3B8[320];
s32 D_8011C8B8[512];
s32 D_8011D0B8;
s32 D_8011D0BC;
s32 D_8011D0C0;
s32 D_8011D0C4;
s32 D_8011D0C8;
s16 D_8011D0CC;
s16 D_8011D0CE;
s32 D_8011D0D0;
s32 D_8011D0D4;
s32 D_8011D0D8;
s32 D_8011D0DC;
s32 D_8011D0E0;
s32 D_8011D0E4;
s32 D_8011D0E8;
s32 D_8011D0EC;
s32 D_8011D0F0;
s32 D_8011D0F4;
s32 D_8011D0F8[12];
s32 D_8011D128[15];
s32 D_8011D164;
s32 D_8011D168[84];
s32 D_8011D2B8[20];
s32 D_8011D308;
s32 D_8011D30C;
s32 D_8011D310;
s32 D_8011D314;
s32 D_8011D318;
s32 D_8011D31C;
s32 D_8011D320[4];
s32 D_8011D330[2];
s32 D_8011D338[4];
s32 D_8011D348[2];
s32 D_8011D350[4];
s32 D_8011D360;
s32 D_8011D364;
s32 D_8011D368;
s32 D_8011D36C;
s32 D_8011D370;
s32 D_8011D374;
s32 D_8011D378;
s32 D_8011D37C;
s32 D_8011D380;
s32 D_8011D384;
s32 D_8011D388[56];

typedef struct{
    s32 unk00;
    s32 unk04;
    s32 unk08;
}unk8011D468;
unk8011D468 D_8011D468;

s32 D_8011D474;
s32 D_8011D478;
s32 D_8011D47C;
s32 D_8011D480[2];
s32 D_8011D488[2];
s32 D_8011D490[2];
s32 D_8011D498;
s16 D_8011D49C;
s16 D_8011D49E;
s32 D_8011D4A0;
s32 D_8011D4A4;
s32 D_8011D4A8;
s32 D_8011D4AC;
s32 D_8011D4B0;
s16 D_8011D4B4;
s16 D_8011D4B6;
s16 D_8011D4B8;
s16 D_8011D4BA;
s32 D_8011D4BC;


/******************************/

extern void guMtxXFMF(void*, f32, f32, f32, f32*, f32*, f32*);



s32 func_800249E0(s32 arg0) {
    D_8011D37C = arg0;
    return 0;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800249F0.s")
#else 
extern u32 D_800DC874;
extern u32 D_800DC87C;
extern u32 D_8011B0C8;
extern u8  D_8011B0E1;
extern u8  D_8011B0E2;
extern u8  D_8011B0E3;
extern u32 D_8011B0F8;
extern u32 D_8011B100;
extern u32 D_8011B104;
extern u32 D_8011B108;
extern u32 D_8011B10C;
extern u32 D_8011B110;
extern u32 D_8011B114;
extern u32 D_8011D320[4];
extern u32 D_8011D338[4];
extern u32 D_8011D348;
extern u32 D_8011D350[4];

extern u32 D_8011D384;


void func_800249F0(u32 arg0, u32 arg1, s32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6){
    s32 i;
    s32 tmp_a2;

    D_800DC91C = get_current_level_header();
    D_8011B0F8 = 0;
    D_8011B100 = 0;
    D_8011B104 = 0;
    D_8011B108 = 0;
    D_8011B10C = 0;
    if(D_800DC91C->race_type == 6 || D_800DC91C->race_type == 7){
        D_8011B0F8 = 1;
    }
    func_8002C0C4(arg0);

    if(arg2 < 2){
        D_8011D384 = 0;
        for(i = 0; i < D_800DC918->numberOfSegments; i++){
            if(D_800DC918->segments[i].unk2B != 0){
                D_8011D384++;
                D_800DC918->segments[i].unk2B = 1;
            }
        }
    }
    if(is_in_two_player_adventure() && (D_800DC91C->race_type == 0 || D_800DC91C->race_type & 0x40)){
        tmp_a2 = 2;
    }else{
        tmp_a2 = arg2;
        tmp_a2++;
    }
    if(D_8011D384){
        func_800B82B4(D_800DC918, D_800DC91C, tmp_a2);
    }
    func_8006652C(arg2);
    func_80027FC4(arg1);
    D_8011B110 = 0;
    D_8011B114 = 0x10000;
    func_80011390();
    func_8000C8F8(arg6,0);
    func_8000C8F8(arg5,1);
    D_8011D37C = arg2;
    func_8000CC7C(arg3, arg4, arg2);
    func_8000B020(72, 64);
    if(arg0 == 0 && arg4 == 0){
        func_800C01D8(&D_800DC87C);
    }
    else{
        func_800C01D8(&D_800DC874);
    }
    func_8006652C(D_8011D37C);
    D_8011B0FC = 0;
    i = 0;
    do{
        D_8011D350[i] = allocate_from_main_pool_safe(3200, COLOR_TAG_YELLOW);
        D_8011D320[i] = allocate_from_main_pool_safe(12800, COLOR_TAG_YELLOW);
        D_8011D338[i] = allocate_from_main_pool_safe(20000, COLOR_TAG_YELLOW);
    }while(&D_8011D338[++i] != &D_8011D348);
    
    D_8011B0C8 = 0;
    func_8002D8DC(1,1,0);
    func_8002D8DC(2,2,0);
    D_8011B0C8 = 1;
    func_8002D8DC(1,1,0);
    func_8002D8DC(2,2,0);
    D_8011B0C8 = 0;
    if(D_800DC91C->unkB7){
        D_8011B0E1 = D_800DC91C->unkB4;
        D_8011B0E2 = D_800DC91C->unkB5;
        D_8011B0E3 = D_800DC91C->unkB6;
        func_80025510(arg2 + 1);
    }
}
#endif


GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80024D54.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80025510.s")

void func_800257D0(void) {
    if (D_800DC924 != 0) {
        free_from_memory_pool(D_8011D474);
        free_from_memory_pool(D_800DC924);
        D_800DC924 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002581C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026070.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026430.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026C14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026E54.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027184.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027568.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800278E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027E24.s")

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027FC4.s")

void func_80028044(s32 arg0) {
    D_8011B0DC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028050.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800289B8.s")
#else
void func_800289B8(void){
    u8 sp_2f = D_800DC91C->unkC1;
    u8 sp_2e = D_800DC91C->unkC2;
    u8 sp_2d = D_800DC91C->unkC3;
    u8 sp_2c = D_800DC91C->unkBE;
    u8 sp_2b = D_800DC91C->unkBF;
    u8 sp_2a = D_800DC91C->unkC0;
    u32 sp_24 = D_8011B0A8;
    func_8007B3D0(&D_8011B0A0);
    func_8007B4C8(&D_8011B0A0, 0, 8);
    D_8011B0A0 += 8;
}
#endif

void render_skydome(void){
    unk80120AC0 * v0_some_struct;
    if(D_8011B0B8 == NULL)
        return;

    v0_some_struct = func_80069D20();
    if(D_800DC91C->unk49 == 0){
        D_8011B0B8->x_position = v0_some_struct->x_position;
        D_8011B0B8->y_position = v0_some_struct->y_position;
        D_8011B0B8->z_position = v0_some_struct->z_position;
    }

    func_80068408(&D_8011B0A0, &D_8011B0A4);
    if(D_8011B0DC){
        func_80012D5C(&D_8011B0A0, &D_8011B0A4, &D_8011B0A8, D_8011B0B8);
    }
}
#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028CD0.s")
#else

#endif


void func_80028FA0(s32 arg0) {
    D_8011B0FC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/render_level_geometry_and_objects.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/render_level_segment.s")

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029AF8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029D14.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029F18.s")
#else
func_80029F18(){
    
}
#endif


s32 func_8002A05C(s32 arg0, s32 arg1, s32* arg2){
    s32 i;
    s32 cnt = 0;
    LevelModelSegmentBoundingBox * a0;
    for(i = 0; i < D_800DC918->numberOfSegments; i++){
        a0 = D_800DC918->segmentsBoundingBoxes + i;
        if(arg0 < a0->unk06 + 4 && a0->unk00 - 4 < arg0
        && arg1 < a0->unk0A + 4 && a0->unk04 - 4 < arg1
        ){
            *arg2 = i;
            cnt++;
            arg2++;
        }
    }
    return cnt;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A134.s")
#else
s32 func_8002A134(s32* arg0, LevelModelSegmentBoundingBox arg1){
    s32 i;
    LevelModelSegmentBoundingBox * a0;
    s32 cnt = 0;
    LevelModelSegmentBoundingBox bnd;

    //BAD variable assignments;
    bnd.unk00 = arg1.unk00 - 4;
    bnd.unk02 = arg1.unk02 - 4;
    bnd.unk04 = arg1.unk04 - 4;
    bnd.unk06 = arg1.unk06 + 4;
    bnd.unk08 = arg1.unk08 + 4;
    bnd.unk0A = arg1.unk0A + 4;


    for(i = 0; i < D_800DC918->numberOfSegments; i++){
        a0 = D_800DC918->segmentsBoundingBoxes + i;
        if( a0->unk06 >= bnd.unk00 && bnd.unk06 >= a0->unk00
        &&  a0->unk0A >= bnd.unk04 && bnd.unk0A >= a0->unk04
        &&  a0->unk08 >= bnd.unk02 && bnd.unk08 >= a0->unk02
        ){
            *arg0 = i;
            cnt++;
            arg0++;
        }
    }
    return cnt;
}
#endif

LevelModelSegment *func_8002A2C8(s32 arg0){
    if(arg0 < 0 || D_800DC918->numberOfSegments < arg0)
        return NULL;
    
    return D_800DC918->segments + arg0;
}

LevelModelSegmentBoundingBox *func_8002A2DC(s32 arg0){
    if(arg0 < 0 || D_800DC918->numberOfSegments < arg0)
        return NULL;

    return D_800DC918->segmentsBoundingBoxes + arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A31C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A5F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A900.s")

void func_8002ACC8(s32 arg0) {
    D_8011B0F4 = arg0;
}

s32 func_8002ACD4(f32* arg0, f32* arg1, f32* arg2) {
    *arg0 = D_8011B0E4;
    *arg1 = D_8011B0E8;
    *arg2 = D_8011B0EC;
    return D_8011B0F0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002AD08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002B0F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002B9BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002BAB0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C0C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C71C.s")

LevelModel* func_8002C7C4(void) {
    return D_800DC918;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C7D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C954.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002CC30.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D30C.s")
#else

typedef struct{
    u8 pad00[0x04];
    u32 unk04;
    u32 unk08;
}unk8002D30C_a0;

void func_8002D30C(unk8002D30C_a0* arg0, u32 arg1){
    unk8002D30C_a0* s0 = arg0;
    while(s0 != NULL){
        if(s0->unk04){
            s0->unk04 += arg1;
        }

        if(s0->unk08){
            s0->unk08 += arg1;
        }

        func_8002D30C(s0->unk04, arg1);
        s0 = s0->unk08;
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/render_floor_decal.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D670.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D8DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002DE30.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E234.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E904.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002EEEC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F2AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F440.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FA64.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FD74.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FF6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800304C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030664.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030750.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800307BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030838.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8003093C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030A74.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030DE0.s")


void func_80031018(void){
    struct {
        u8 pad00[0x40];
    } sp_50; //same as unk80535C4_3

    struct {
        s16 unk00; //sp_38
        s16 unk02; //sp_3A
        s16 unk04; //sp_3C
        u8 pad06[0x02];
        f32 unk08; //sp40;
        f32 unk0C; //sp44;
        f32 unk10; //sp48;
        f32 unk14; //sp4C;
    } sp_38;

    f32 sp_34 = 0.0f;
    f32 sp_30 = 0.0f;
    f32 sp_2C = -65536.0f;    
    
    sp_38.unk04 = D_8011B0B0->unk04;
    sp_38.unk02 = D_8011B0B0->unk02;
    sp_38.unk00 = D_8011B0B0->unk00;
    sp_38.unk0C = 0.0f;
    sp_38.unk10 = 0.0f;
    sp_38.unk14 = 0.0f;
    sp_38.unk08 = 1.0f;
    
    func_8006FC30(&sp_50, &sp_38);
    guMtxXFMF(&sp_50, sp_34, sp_30, sp_2C, &sp_34, &sp_30, &sp_2C);
    D_8011D468.unk00 = sp_34;
    D_8011D468.unk04 = sp_30;
    D_8011D468.unk08 = sp_2C;
}