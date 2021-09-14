#ifndef _UNKNOWN_00BC20_H_
#define _UNKNOWN_00BC20_H_

#include "types.h"
#include "structs.h"
#include "f3ddkr.h"

/* Size: 0x8 bytes */
typedef struct unknown800DC6F0 {
    union {
        s8 unk00;
        s32 dummy_force_alignment; // Not sure of a better way to do this.
    } unk00_a;
    u16 unk04;
    u16 unk06;
} unknown800DC6F0;

/* Size: 0x3C bytes */
typedef struct unknown8011AECC {
    u8 unk00[0x3A];
    s8 unk3A;
    s8 unk3B;
} unknown8011AECC;

/* Size: 0x40 bytes */
typedef struct unk800179D0 {
    s32 unk0;
    u32 *unk04;
    u32 *unk08;
    f32 unk0C[12];
    u32 unk3C;
} unk800179D0;

/* Unknown Size */
typedef struct unk800179D0_2 {
    s32 unk04; 
} unk800179D0_2;

typedef struct unk8001D6E4_arg1_40 {
           u8 pad0[0x71];
/* 0x71 */ u8 unk71;
} unk8001D6E4_arg1_40;

typedef struct unk8001D6E4_arg1 {
/* 0x00 */ s16 unk0;
/* 0x02 */ s16 unk2;
/* 0x04 */ s16 unk4;
           u8  pad6[0x3A];
/* 0x40 */ unk8001D6E4_arg1_40 *unk40;
} unk8001D6E4_arg1;

/* Unknown Size */
typedef struct unk8000FD20_2 {
    u8 unk00[0x13];
    u8 unk13;
} unk8000FD20_2;

/* Unknown Size */
typedef struct unk8000FD20 {
    u8 unk00[0x4C];
    unk8000FD20_2 *unk4C;
} unk8000FD20;

/* Unknown Size. This might just be unk8000FD20. */
typedef struct unk8000FD34 {
    u8 unk00[0x5C];
    s32 unk5C;
} unk8000FD34;

extern unknown800DC6F0 D_800DC6F0;
extern unknown800DC6F0 D_800DC6F8;

extern s32 D_800DC700;
extern s32 D_800DC704;
extern s16 D_800DC708;
extern s32 D_800DC70C;
extern s16 D_800DC710;
extern s32 D_800DC714;
extern s32 D_800DC718;
extern s8 D_800DC71C;
extern s32 D_800DC720;
extern s16 D_800DC724;
extern s16 D_800DC728;
extern s16 D_800DC72C;
extern u8 D_800DC730;
extern s32 D_800DC734;
extern u8 D_800DC738;
extern s8 D_800DC73C;
extern s8 D_800DC740;
extern s8 D_800DC744;
extern s8 D_800DC748;
extern s32 D_800DC74C;
extern s32 D_800DC750;
extern s32 D_800DC754;
extern s32 D_800DC758;
extern s32 D_800DC75C;
extern s32 D_800DC760;
extern s32 D_800DC764;
extern s32 D_800DC768;

extern f32 D_800DC76C[15];

extern u16 D_800DC7A8[8];

extern s16 D_800DC7B8[52];

extern s16 D_800DC820[16];

extern s8 D_800DC840[8];

extern s8 D_800DC848;
extern s32 D_800DC84C[3];
extern s32 D_800DC858;
extern s32 D_800DC85C;

extern u8 D_800DC860;
extern u16 D_800DC864;

void free_tt_ghost_data(void); //unknown_043920.c
f32 func_800707F8(s16); //?
void func_8006C164(void); //unknown_06B2B0

u32 *func_8000BF44(s32 arg0);
void func_8000BF8C(void);
void func_8000C460(void);
void func_8000C604(void);
s32 func_8000C8B4(s32 arg0);
void func_8000CBC0(void);
s32 func_8000CC20(u32 *arg0);
u32 func_8000E0B0(void);
void func_8000E128(void);
s8 func_8000E138();
s8 func_8000E148();
s8 func_8000E158(void);
s8 func_8000E184();
void func_8000E194(void);
void func_8000E1B8(void);
s8 func_8000E1CC(void);
s8 func_8000E1DC();
void func_8000E1EC(Object *object, s32 arg1);
void set_time_trial_enabled(s32 arg0);
u8 is_time_trial_enabled();
u8 func_8000E4D8(void);
Object *get_object(s32 index);
Object **func_8000E988(s32 *arg0, s32 *cnt);
s32 getObjectCount(void);
s32 func_8000E9C0(void);
void func_8000E9D0(Object *arg0);
void gParticlePtrList_addObject(Object *object);
s32 func_80010018(void);
s32 func_80010028(s32 arg0);
void func_80011390(void);
s32 func_8001139C();
s32 func_800113AC();
s32 func_800113BC();
void func_80011560(void);
void func_80012C30(void);
void func_80012C3C(Gfx** dlist);
void func_80012C98(Gfx **dlist);
void func_80012CE8(Gfx **dlist);
void func_80012D5C(u32 *arg0, u32 *arg1, u32 *arg2, Object *object);
void func_80012F30(Object *arg0);
void render_object(Object *this);
void func_80013548(Object *arg0);
void func_800142B8(void);
u32 func_800179D0(void);
void func_80017E74(s32 arg0);
s16 func_80017E88(void);
Object *func_80018C6C(void);
void func_8001A8D4(s32 arg0);
s16 func_8001AE44();
s32 func_8001AE54();
s32 func_8001B288(void);
s32 func_8001B2E0();
s32 func_8001B3AC(s32 arg0);
s32 func_8001B640();
s32 func_8001B650(void);
s32 func_8001B738(s32 arg0);
u8 func_8001B780();
void func_8001B790(void);
unknown8011AECC *func_8001BA00(s32 arg0);
unknown8011AECC *func_8001BA1C(s32 arg0, s32 arg1);
s32 func_8001BA64();
Object **get_object_struct_array(s32 *cnt);
s32 *func_8001BA90(s32 *arg0);
s32 *func_8001BAAC(s32 *arg0);
Object *get_object_struct(s32 indx);
void func_8001BC40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
u32 func_8001BD94(s32 arg0);
void func_8001D1AC(void);
void func_8001D1BC(s32 arg0);
u32 func_8001D1E4(s32 *arg0);
u32 func_8001D214(s32 arg0);
void func_8001D23C(s32 arg0, s32 arg1, s32 arg2);
void calc_dyn_light_and_env_map_for_object(ObjectModel *model, Object *object, s32 arg2, f32 arg3);
s32 *get_misc_asset(s32 index);
s32 func_8001E2EC(s32 arg0);
void func_8001E344(s32 arg0);
void func_8001E36C(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3);
s16 func_8001E440();
void func_8001E450(s32 arg0);
void func_8001E45C(s32 arg0);
s32 func_8001E4B4(void);
s8 func_8001F3B8(void);
void func_8001F3C8(s32 arg0);
void func_8001F450(void);
s32 func_800210CC(s8 arg0);
s8 func_800214C4(void);
f32 lerp(f32 *arg0, u32 arg1, f32 arg2);
void func_800228DC(s32 arg0, s32 arg1, s32 arg2);
void func_800228EC(s32 arg0);
s8 func_8002341C(void);
s32 func_80023568(void);
s8 func_800235C0(void);
void func_800238BC(Object *arg0);
void run_object_loop_func(Object *obj, s32 arg1);
void func_8002458C(s32 arg0);
s16 *func_80024594(s32 *arg0, s32 *arg1);
void func_800245B4(s16 arg0);

//Non Matching
void calc_dynamic_lighting_for_object_1(unk8001D6E4_arg1 *, ObjectModel *, s16, unk8001D6E4_arg1 *, f32, f32);
void calc_dynamic_lighting_for_object_2(unk8001D6E4_arg1 *, ObjectModel *, s16, f32);
void gParticlePtrList_flush(void);
void func_8001D258(f32, f32, s32, s32, s32);
void decrypt_magic_codes(u8 *arg0, s32 length);
void func_80011960(Object*, s32, u32, Object_64*, u32, u32, u32, u32, f32);
void func_80011AD0(Object *this);
void func_80012E28(Object *this);
void func_8001D5E0(f32 arg0, f32 arg1, f32 arg2);

#endif
