/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80033CC0 */

#include "unknown_0348C0.h"

#include "PR/os_cont.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "video.h"
#include "camera.h"
#include "menu.h" // For cheats
#include "unknown_0ABDF0.h"
#include "unknown_043920.h"
#include "unknown_06B2B0.h"
#include "audio.h"
#include "unknown_008C40.h"
#include "unknown_00BC20.h"
#include "particles.h"
#include "unknown_0255E0.h"
#include "font.h"
#include "unknown_032760.h"
#include "unknown_09F8F0.h"
#include "waves.h"
#include "unknown_003260.h"

/************ .data ************/

// Unsure about the signed/unsigned with these arrays.
u16 D_800DC970[4] = {
    0x40FF, 0xFFFF, 0x0007, 0x0003
};
u16 D_800DC978[4] = {
    0x0000, 0x0000, 0x001E, 0xFFFF
};
u16 D_800DC980[20] = {
    0xFF00, 0x0100, 0x0000, 0xFFFF,
    0xFFFF, 0x0100, 0x0100, 0x0000,
    0xFFFF, 0xFFFF, 0x0100, 0xFF00,
    0x0000, 0xFFFF, 0xFFFF, 0xFF00,
    0xFF00, 0x0000, 0xFFFF, 0xFFFF,
};
u16 D_800DC9A8[20] = {
    0x0000, 0x0040, 0xFFC0, 0x0000,
    0xFFC0, 0xFFC0, 0x0000, 0x0040,
    0x0020, 0x0000, 0xFFC0, 0x0020,
    0x0000, 0x0040, 0x0040, 0x0000,
    0xFFC0, 0x0040, 0x0000, 0x0000,
};
u16 D_800DC9D0[64] = {
    0x0000, 0x0301, 0x0004, 0x0000,
    0x0001, 0x0004, 0x0004, 0x0004,
    0x0000, 0x0203, 0x0004, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0004,
    0x0002, 0x0503, 0x0001, 0x0000,
    0x0000, 0x0004, 0x0001, 0x0004,
    0x0002, 0x0405, 0x0001, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0004,
    0x0000, 0x0103, 0x0004, 0x0000,
    0x0004, 0x0004, 0x0001, 0x0004,
    0x0000, 0x0302, 0x0004, 0x0000,
    0x0001, 0x0004, 0x0001, 0x0000,
    0x0002, 0x0305, 0x0001, 0x0000,
    0x0001, 0x0004, 0x0000, 0x0004,
    0x0002, 0x0504, 0x0001, 0x0000,
    0x0000, 0x0004, 0x0000, 0x0000,
};
s8 D_800DCA50[8] = {
    2, 5, 6, 3, 10, 8, 7, 9
};
u8 D_800DCA58[9] = {
    2, 5, 6, 3, 10, 8, 7, 9, 11
};
s8 D_800DCA64[9] = {
    2, 5, 6, 3, 10, 8, 7, 9, 12
};
s8 D_800DCA70[10] = {
    2, 5, 6, 3, 10, 8, 7, 9, 11, 12
};
s32 D_800DCA7C[3] = { // Not sure about typing
    0, 0, 0
};
s32 D_800DCA88[3] = { // Not sure about typing
    0, 0, 0
};

s8 D_800DCA94[8] = {
    0x00, 0x00, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00
};

s8 D_800DCA9C[12] = {
    0x00, 0x01, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
u16 D_800DCAA8[64] = {
    0x0000, 0x0301, 0x0000, 0x0000,
    0xFFFF, 0xFFFF, 0x0000, 0xFFFF,
    0x0000, 0x0203, 0x0000, 0x0000,
    0xFFFF, 0x0000, 0xFFFF, 0xFFFF,
    0x0002, 0x0503, 0xFFFF, 0x0000,
    0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
    0x0002, 0x0405, 0xFFFF, 0x0000,
    0x0000, 0x0000, 0x0000, 0xFFFF,
    0x0000, 0x0103, 0x0000, 0x0000,
    0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
    0x0000, 0x0302, 0x0000, 0x0000,
    0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
    0x0002, 0x0305, 0xFFFF, 0x0000,
    0xFFFF, 0xFFFF, 0x0000, 0xFFFF,
    0x0002, 0x0504, 0xFFFF, 0x0000,
    0x0000, 0xFFFF, 0x0000, 0x0000,
};
u16 D_800DCB28[20] = {
    0xFFC0, 0x0000, 0x0020, 0xFFC0,
    0x0000, 0xFFE0, 0x0000, 0x0000,
    0x0020, 0x0000, 0x0000, 0xFFE0,
    0x0040, 0x0000, 0x0020, 0x0040,
    0x0000, 0xFFE0, 0x0000, 0x0000,
};

/*******************************/

/************ .bss ************/

f32 D_8011D4D0;
s32 D_8011D4D4;
s32 D_8011D4D8;
s32 D_8011D4DC;
s16 D_8011D4E0;
s16 D_8011D4E2;

/******************************/

#ifdef NON_EQUIVALENT
typedef struct LevelObjectEntry80033CC0 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} LevelObjectEntry80033CC0;

typedef struct Object_50_80033CC0 {
    f32 unk0;
} Object_50_80033CC0;

void obj_init_scenery(Object *arg0, LevelObjectEntry80033CC0 *arg1) {
    f32 phi_f0;
    arg0->unk6 |= 2;
    phi_f0 = arg1->unk9 & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    arg0->scale = arg0->header->scale * phi_f0;
    ((Object_50_80033CC0 *)arg0->unk50)->unk0 = arg0->header->unk4 * phi_f0;
    arg0->unk3A = arg1->unk8;
    arg0->y_rotation = arg1->unkA << 6 << 4;
    if (arg1->unkB) {
        // Regalloc issue here
        arg0->unk4C->unk14 = 1;
        arg0->unk4C->unk11 = 1;
        arg0->unk4C->unk10 = 0x14;
        arg0->unk4C->unk12 = 0;
        arg0->unk4C->unk16 = -5;
        arg0->unk4C->unk17 = arg1->unkB;
    }
    if (arg0->unk3A >= arg0->header->numberOfModelIds) {
        arg0->unk3A = 0;
    }
    arg0->unk78 = 0;
    arg0->unk7C.word = 0;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_scenery.s")
#endif

void obj_loop_scenery(Object *obj, s32 arg1) {
	Object78_80033DD0 *obj78;
	s32 temp_v0;
	
    if (obj->unk4C != NULL) {
        obj78 = &obj->unk78;
        if (obj->unk7C.half.upper > 0) {
            obj78->unk4 -= arg1;
        }
        if ((obj->unk4C->unk14 & 0x40) && ((s32) obj78->unk4 <= 0)) {
            func_80009558(316, obj->x_position, obj->y_position, obj->z_position, 4, NULL);
            obj78->unk0 = (s32*) obj->unk4C->unk0;
            obj78->unk6 = 1820;
            obj78->unk4 = 10;
            if (get_number_of_active_players() < 2) {
                if (obj->header->unk57 > 0) {
                    if (obj->header->unk57 == 1) {
                        temp_v0 = 0;
                    } else {
                        temp_v0 = get_random_number_from_range(0, obj->header->unk57 - 1);
                    }
                    obj->unk74 = 1 << temp_v0;
                    func_800AFC3C(obj, 2);
                }
            }
        } else if (obj78->unk4 <= 0) {
            obj78->unk0 = 0;
        }
        obj->z_rotation = (s16) obj78->unk6;
        obj78->unk6 = (obj78->unk6 * -200) >> 8;
    }
}

void obj_init_fireball_octoweapon(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
}

#ifdef NON_MATCHING
// Has a minor regalloc issue with obj4C_obj.

typedef struct Object80033F60_64 {
	u8 pad0[0x1C];
	s32 *unk1C;
	u8 pad20[0x8];
	s32 unk28;
} Object80033F60_64;

typedef struct Object80033F60_4C_64 {
	s16 unk0;
	u8 pad2[0x185];
	s8 unk187;
	u8 pad188[0x7C];
	s16 unk204;
} Object80033F60_4C_64;

s32 func_80011560(void);
void func_80011570(Object*, f32, f32, f32);
void func_8003FC44(f32, f32, f32, s32, s32, f32, s32);
s16 func_80070750(f32, f32);
s32 func_8002AD08(f32, f32**, s32);
void func_80001D04(u16, s32 *);               
void func_8000488C(s32);                                                     
void func_800AFC3C(Object *, s32);                 
void gParticlePtrList_addObject(Object *);      
f32 sqrtf(f32);                                

void obj_loop_fireball_octoweapon(Object *obj, s32 arg1) {
	Object *obj78;
	Object_4C *obj4C;
	f32 sp7C;
	Object80033F60_4C_64 *obj4C_obj64;
	Object80033F60_64 *obj64;
	Object *obj4C_obj;
	f32 phi_f2;
    s32* temp;
	f32 sp4C[7];

    obj78 = (Object*)obj->unk78;
	
    sp7C = arg1;
    if (osTvType == TV_TYPE_PAL) {
        sp7C *= 1.2;
    }
	
    if ((obj->behaviorId == 116) && (obj->unk7C.word < 0)) {
        obj->x_position = 0.0f;
        obj->y_position = 0.0f;
        obj->z_position = 0.0f;
        func_80011560();
        func_80011570(obj, obj78->x_position, obj78->y_position, obj78->z_position);
    } else {
        phi_f2 = (obj78->x_position - obj->x_position) * 0.1;
        if (phi_f2 > 10.0) {
            phi_f2 = 10.0f;
        }
        if (phi_f2 < -10.0) {
            phi_f2 = -10.0f;
        }
        obj->x_velocity += (phi_f2 - obj->x_velocity) * 0.125 * sp7C;
        phi_f2 = (obj78->y_position - obj->y_position) * 0.1;
        if (phi_f2 > 10.0) {
            phi_f2 = 10.0f;
        }
        if (phi_f2 < -10.0) {
            phi_f2 = -10.0f;
        }
        obj->y_velocity += (phi_f2 - obj->y_velocity) * 0.125 * sp7C;
        phi_f2 = (obj78->z_position - obj->z_position) * 0.1;
        if (phi_f2 > 10.0) {
            phi_f2 = 10.0f;
        }
        if (phi_f2 < -10.0) {
            phi_f2 = -10.0f;
        }
        obj->z_velocity += (phi_f2 - obj->z_velocity) * 0.125 * sp7C;
        if (sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity)) > 0.5) {
            obj->y_rotation = func_80070750(obj->x_velocity, obj->z_velocity);
            obj->x_rotation -= arg1 << 9;
        }
        func_80011570(obj, obj->x_velocity * sp7C, obj->y_velocity * sp7C, obj->z_velocity * sp7C);
        if (obj->unk4A == 298 && func_8002AD08(obj->y_position, &sp4C, 0)) {
			obj->y_position = sp4C[0];
        }
    }
    obj->unk18 += arg1 * 10;
    obj64 = obj->unk64;
    obj4C = obj->unk4C;
    obj4C_obj = (Object*)obj4C->unk0; // This should be a0, not v1!
    if ((obj4C_obj != NULL) && (obj4C->unk13 < 60) && (obj4C_obj->header->behaviorId == 1)) {
        obj4C_obj64 = obj4C_obj->unk64;
        if (obj4C_obj64->unk0 != -1) {
            if (obj->behaviorId == 108) {
                obj4C_obj64->unk187 = 1;
                obj->unk7C.word = 20;
                func_8003FC44(obj->x_position, obj->y_position, obj->z_position, 44, 17, 1.0f, 1);
                gParticlePtrList_addObject(obj);
            } else if (obj->unk7C.word > 0) {
                obj4C_obj64->unk204 = 60;
                obj->unk7C.word = -60;
                obj->unk78 = obj4C_obj;
                func_80001D04(586, &obj64->unk1C);
            }
        }
    }
    if (obj->behaviorId == 108) {
        obj->unk74 = 1;
        func_800AFC3C(obj, arg1);
        obj->unk7C.word -= arg1;
        if (obj->unk7C.word < 0) {
            if (obj->unk4A == 298) {
                gParticlePtrList_addObject(obj);
                func_8003FC44(obj->x_position, obj->y_position, obj->z_position, 44, 17, 1.0f, 1);
            }
            obj->scale *= 0.9;
            if (obj->scale < 0.5) {
                gParticlePtrList_addObject(obj);
            }
        }
    } else {
        if (obj->unk7C.word < 0) {
            obj->unk7C.word += arg1;
            if (obj->unk7C.word >= 0) {
                obj->unk7C.word = 0;
            }
        } else {
            obj->unk7C.word -= arg1;
            if (obj->unk7C.word <= 0) {
                obj->unk7C.word = 0;
            }
        }
        if (obj->unk7C.word == 0) {
            temp = obj64->unk1C;
            if (temp != 0) {
                func_8000488C(temp);
            }
            func_80009558(341, obj->x_position, obj->y_position, obj->z_position, 4, 0);
            gParticlePtrList_addObject(obj);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_fireball_octoweapon.s")
#endif

void obj_init_lasergun(Object *arg0, unk80034530 *arg1) {
    Object_64 *temp;
    arg0->unk4C->unk14 = 0x22;
    arg0->unk4C->unk11 = 0;
    temp = arg0->unk64;
    temp->unkE = arg1->unkA;
    temp->unkF = arg1->unkB;
    temp->unk10 = arg1->unkC;
    temp->unk11 = arg1->unkD;
    temp->unkCD.half = temp->unkF;
    arg0->y_rotation = arg1->unk8 << 4 << 4; // Not sure about the shift amounts here, but it
    arg0->x_rotation = arg1->unk9 << 4 << 4; // just needs to be 2 left shifts that add up to 8.
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_lasergun.s")

// Literally the same function as obj_init_fireball_octoweapon()
void obj_init_laserbolt(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
}

void func_80031130(s32, f32*, f32*, s32);
void func_80031600(f32*, f32*, f32*, s8*, s32, s8*);
void func_8003FC44(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, f32 arg5, s32 arg6);

typedef struct Object_7C_80034860 {
	u8 pad0[0xC];
	s16 unkC;
} Object_7C_80034860;

typedef struct Object_64_80034860 {
	s16 unk0;
	u8  unk4[0x185];
	s8  unk187;
} Object_64_80034860;

void obj_loop_laserbolt(Object *obj, s32 arg1) {
	f32 sp5C;

	Object *obj4C_obj;

	Object_7C_80034860 *obj7C;
	Object_64_80034860 *obj4C_obj64;

	s8 sp4F; // Boolean
	s8 sp4E;
	f32 sp48;
	f32 sp44;
	f32 sp40;
	f32 sp3C;
	s32 sp38; // Boolean

	
    sp4F = FALSE;
    sp5C = arg1;
    if (osTvType == TV_TYPE_PAL) {
        sp5C *= 1.2;
    }
    sp40 = obj->x_position + (obj->x_velocity * sp5C);
    sp44 = obj->y_position + (obj->y_velocity * sp5C);
    sp48 = obj->z_position + (obj->z_velocity * sp5C);
    sp3C = 9.0f;

    func_80031130(1, &obj->x_position, &sp40, -1);
    sp38 = FALSE;
    func_80031600(&obj->x_position, &sp40, &sp3C, &sp4E, 1, &sp38);
    if (sp38) {
        obj->x_velocity = (sp40 - obj->x_position) / sp5C;
        obj->y_velocity = (sp44 - obj->y_position) / sp5C;
        obj->z_velocity = (sp48 - obj->z_position) / sp5C;
    }
    func_80011570(obj, obj->x_velocity * sp5C, obj->y_velocity * sp5C, obj->z_velocity * sp5C);
    if (sp38) {
        func_8003FC44(obj->x_position, obj->y_position - 36.0f, obj->z_position, 44, 0, 0.2, 0);
        sp4F = TRUE;
    }
	
    if (obj->unk78 > 0) {
        obj->unk78 -= arg1;
    } else {
        sp4F = TRUE;
    }
	
    if (obj->unk4C->unk13 < 80) {
        obj4C_obj = (Object*)obj->unk4C->unk0;
        if (obj4C_obj && (obj4C_obj->behaviorId == 1)) {
            obj4C_obj64 = obj4C_obj->unk64;
            sp4F = TRUE;
            if (obj4C_obj64->unk0 != -1) {
                obj4C_obj64->unk187 = 1;
            }
            obj7C = (Object_7C_80034860 *)obj->unk7C.word;
            if (obj7C) {
                obj7C->unkC = 180;
            }
            sp4F = TRUE;
            func_8003FC44(obj->x_position, obj->y_position - 36.0f, obj->z_position, 44, 17, 0.5, 0);
        }
    }
    if (sp4F) {
        gParticlePtrList_addObject(obj);
    }
}

void obj_init_torch_mist(Object *arg0, u8 *arg1) {
    f32 phi_f0 = (s32)(arg1[9] & 0xFF);
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    arg0->scale = arg0->header->scale * phi_f0;
    arg0->unk78 = arg1[8];
}

void obj_loop_torch_mist(unk80034B4C *arg0, s32 arg1) {
    arg0->unk18 += arg0->unk78 * arg1;
}

void obj_init_effectbox(s32 arg0, s32 arg1) {
}

#ifdef NON_EQUIVALENT

// Has regalloc & stack issues.

f32 func_800707C4(s16);
f32 func_800707F8(s16);
Object **get_object_struct_array(s32 *count);

void obj_loop_effectbox(Object *obj, s32 arg1) {
    Object **objList;
    Object_3C_80034B74 *obj3C;
    Object_64_80034B74 *curObj64;
    s32 i;
    s32 numberOfObjects;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 temp0;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;
    f32 temp5;
    f32 tempf0;
    u8 new_var2;

    obj3C = obj->unk3C_a.unk3C;
    objList = get_object_struct_array(&numberOfObjects);
    temp0 = func_800707F8((((0, obj3C->unkB)) << 8) * (-1));
    temp1 = func_800707C4((obj3C->unkB << 8) * (-1));
    temp2 = obj3C->unk8 * 3;
    temp3 = obj3C->unk9 * 3;
    temp4 = obj3C->unkA * 3;
    for (i = 0; i < numberOfObjects; i++)
    {
        xDiff = objList[i]->x_position - obj->x_position;
        yDiff = objList[i]->y_position - obj->y_position;
        zDiff = objList[i]->z_position - obj->z_position;
        if (((-temp3) < yDiff) && (yDiff < temp3))
        {
            temp5 = (xDiff * temp0) + (zDiff * temp1);
            if (((-temp2) < temp5) && (temp5 < temp2))
            {
                temp5 = ((-xDiff) * temp1) + (zDiff * temp0);
                if (((-temp4) < (((-xDiff) * temp1) + (zDiff * temp0))) && (temp5 < temp4))
                {
                    temp5 = temp3 / 2;
                    curObj64 = objList[i]->unk64;
                    curObj64->unk1FE = obj3C->unkC;
                    curObj64->unk1FF = obj3C->unkD;
                    if ((temp5 < yDiff) && (curObj64->unk1FE == 1))
                    {
                        new_var2 = curObj64->unk1FF;
                        tempf0 = (new_var2 & 0xFF) * ((f32) (1.0 - ((yDiff - temp5) / temp5)));
                        curObj64->unk1FF = new_var2 * ((f32) (1.0 - ((yDiff - temp5) / temp5)));
                        if (tempf0 < 0.0f)
                        {
                        }
                    }
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_effectbox.s")
#endif

void obj_init_trophycab(Object *arg0, u8 *arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->y_rotation = arg1[8] << 6 << 4; // Not sure about the values here.
}

#ifdef NON_EQUIVALENT

void func_80001D04(u16, s32 *);
f32 sqrtf(f32);
void func_80001D04(u16, s32 *);
f32 sqrtf(f32);
u32 func_80001C08(void);
void func_80001D04(u16, s32 *);
Object *func_8000EA54(unk80027FC4 *, s32);
void func_8005A3B0(void);
void func_8006F254(void);
void func_8009CF68(s32 arg0);
s32 func_8009CFEC(u32 arg0);
void func_800A3870(void);
void func_800AB1AC(s32 arg0);
void func_800AB1D4(u8 arg0);
void func_800C31EC(s32);
s32 func_800C3400(void);
LevelHeader *get_current_level_header(void);
Settings *get_settings(void);
void play_sound(u8 arg0);
void set_music_fade_timer(s32 time);
void set_sndfx_player_voice_limit(u8 voiceLimit);
f32 sqrtf(f32);

typedef struct Object_64_80034E9C {
    s32 unk0;
    s16 unk4;
} Object_64_80034E9C;

typedef struct Object_54_80034E9C {
    u8 pad0[0x28];
    f32 unk28;
    f32 unk2C;
} Object_54_80034E9C;

// Has regalloc & stack issues.

void obj_loop_trophycab(Object *obj, s32 arg1) {
    s32 sp34;
    s32 isTrophyRaceAvaliable;
    s32 raceType;
    unk80027FC4 sp44;
    Settings *settings;
    LevelHeader *curLevelHeader;
    Object_64_80034E9C *obj64;
    Object *trophyObj;
    Object *playerObj;
    f32 xDiff;
    f32 zDiff;
    s32 new_var2;
    
    settings = get_settings();
    curLevelHeader = get_current_level_header();
    obj64 = obj->unk64;
    
    // Show trophy inside the cabinet
    if (obj->unk7C.word == 0) {
        raceType = curLevelHeader->race_type;
        if ((raceType != 7) && (raceType != 6)) { // Make sure the current level is not a cutscene.
            obj->unk7C.word = 1;
            if ((settings->trophies >> (((settings->worldId - 1) ^ 0) * 2)) & 3) {
                sp44.unk0 = 128;
                sp44.unk2 = obj->unk3C_a.unk3C->unk2;
                sp44.unk4 = obj->unk3C_a.unk3C->unk4;
                sp44.unk6 = obj->unk3C_a.unk3C->unk6;
                sp44.unk1 = 8;
                trophyObj = func_8000EA54(&sp44, 1);
                if (trophyObj) {
                    trophyObj->unk3C_a.unk3C = (void *) 0;
                    trophyObj->y_rotation = obj->y_rotation;
                }
            }
        }
    }
    
    ((Object_54_80034E9C *) obj->unk54)->unk2C = 0.612f;
    ((Object_54_80034E9C *) obj->unk54)->unk28 = 0.0f;
    
    playerObj = get_object_struct(0);
    if (playerObj) {
        xDiff = obj->x_position - playerObj->x_position;
        zDiff = playerObj->z_position - obj->z_position;
        sqrtf((xDiff * xDiff) + (zDiff * zDiff)); // Distance on X & Z axes. Not used?
    
        new_var2 = settings->bosses;
        new_var2 |= 0x800; // Why OR with 0x800?
    
        // Check if all the balloons have been collected.
        isTrophyRaceAvaliable = (settings->balloonsPtr[settings->worldId] < 8) ^ 1;
        if (isTrophyRaceAvaliable) {
            isTrophyRaceAvaliable = ((1 << (settings->worldId + 6)) & new_var2) != 0;
        }
    
        // Hit detection between cabinet & player?
        if ((((obj->unk78 == 0) && (!func_800C3400())) && obj->unk5C->unk100) && (obj64->unk4 == 0)) {
            // A hit has been detected at this point.
            if (isTrophyRaceAvaliable) {
                obj->unk78 = 1;
                func_80001D04(303, 0);
                func_800A3870();
            }
            else
            {
                func_800C31EC(4);
                obj64->unk4 = 180;
                obj64->unk0 = 140;
                set_sndfx_player_voice_limit(16);
                set_music_fade_timer(-8);
                play_sound(17);
            }
        }
        if ((obj64->unk0 != 0) && (func_80001C08() == 0)) {
            if (arg1 < obj64->unk0) {
                obj64->unk0 -= arg1;
            }
            else
            {
                obj64->unk0 = 0;
                set_music_fade_timer(8);
                set_sndfx_player_voice_limit(6);
            }
        }
        if (obj->unk5C->unk100 || func_800C3400()) {
            obj64->unk4 = 180;
        }
        if (obj64->unk4 > 0) {
            obj64->unk4 -= arg1;
        }
        else
        {
            obj64->unk4 = 0;
        }
        if (obj->unk78 == 1) {
            func_800AB1AC(3);
            func_800AB1D4(0);
            sp34 = func_8009CFEC(4);
            if (sp34 != 0) {
                obj->unk78 = 0;
                func_8009CF68(4);
                if (sp34 == 1) {
                    func_8006F254();
                    obj->unk78 = 2;
                }
                else
                {
                    func_800AB1D4(1);
                }
            }
            func_8005A3B0();
        }
        obj->unk5C->unk100 = NULL;
        if (isTrophyRaceAvaliable) {
            // Changes lighting/color of the cabinet?
            ((Object_54_80034E9C *) obj->unk54)->unk28 = 0.552f;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_trophycab.s")
#endif

void obj_init_collectegg(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_collectegg.s")

void obj_init_eggcreator(s32 arg0, s32 arg1) {
}

void obj_loop_eggcreator(Object *arg0, s32 arg1) {
    unk8003564C sp20;
    Object *someObj;

    if (arg0->unk78 == 0) {
        sp20.unk2 = arg0->x_position;
        sp20.unk4 = arg0->y_position;
        sp20.unk6 = arg0->z_position;
        sp20.unk1 = 8;
        sp20.unk0 = 0x34;
        someObj = func_8000EA54(&sp20, 1);
        if (someObj != NULL) {
            Object_64_8003564C *someObj64 = someObj->unk64;
            someObj64->unk4 = arg0;
            arg0->unk78 = someObj;
            someObj->unk3C_a.unk3C = 0;
        }
    }
}

void obj_init_lighthouse_rocketsignpost(Object *arg0, LevelObjectEntry8003572C *arg1) {
    f32 phi_f0 = arg1->unk9 & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    arg0->scale = arg0->header->scale * phi_f0;
    arg0->y_rotation = arg1->unkA << 6 << 4;
    if (arg0->unk3A >= arg0->header->numberOfModelIds) {
        arg0->unk3A = 0;
    }
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

void obj_loop_rocketsignpost(Object *obj, s32 arg1) {
    Object *someObj;
    Object_4C *temp_v1;

    someObj = get_object_struct(0);
    if (someObj != NULL) {
        temp_v1 = obj->unk4C;
        if (temp_v1->unk13 < 0xC8) {
            if (someObj == temp_v1->unk0) {
                if ((get_buttons_pressed_from_player(0) & Z_TRIG) || someObj == obj->unk5C->unk100) {
                    func_8006F29C();
                }
            }
        }
    }
    obj->unk4C->unk13 = 0xFF;
}

void obj_init_airzippers_waterzippers(Object *arg0, LevelObjectEntry8003588C *arg1) {
    ObjectHeader *objHeader;
    f32 phi_f0;

    phi_f0 = arg1->unk9 & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    objHeader = arg0->header;
    phi_f0 /= 64;
    arg0->scale = objHeader->scale * phi_f0;
    arg0->y_rotation = arg1->unkA << 6 << 4;
    if (arg0->unk3A >= objHeader->numberOfModelIds) {
        arg0->unk3A = 0;
    }
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        gParticlePtrList_addObject(arg0);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_airzippers_waterzippers.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_groundzipper.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_groundzipper.s")

void obj_init_unknown58(unk80035E20 *arg0, s32 arg1) {
    arg0->unk78 = 0;
    arg0->unk7C = arg0->unk40;
}

void obj_loop_unknown58(Object *obj, s32 arg1) {
    Object *someObj;
    Object *someOtherObj;
    Object_64_80035E34 *someOtherObj64;
    Object_60 *obj60;

    obj->unk3B = 0;
    obj->unk18 = 0x28;
    if (func_8001139C() == 0) {
        obj->unk78 += arg1;
    }
    set_ghost_position_and_rotation(obj);
    func_800AFC3C(obj, arg1);
    someOtherObj = get_object_struct(0);
    someOtherObj64 = someOtherObj->unk64;
    obj60 = obj->unk60;
    if (obj60->unk0 == 1) {
        s8 temp = someOtherObj64->unk1D6;
        if ((temp == 1) || (temp == 2)) {
            someObj = (Object *)obj60->unk4;
            someObj->y_rotation = 0x4000;
            someObj->unk3A++;
            someObj->unk3A &= 1;
        }
    }
}

void obj_init_characterflag(Object *arg0, unk80035EF8 *arg1) {
    f32 phi_f0;
    arg0->unk78 = (s32)arg1->unkE;
    arg0->unk7C.word = -1;
    arg0->y_rotation = arg1->unkC << 6 << 4; // Not sure about the values here.
    phi_f0 = (f32)(arg1->unkA & 0xFF);
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    arg0->scale = (f32)(arg0->header->scale * phi_f0);
}

void obj_loop_characterflag(Object *obj, s32 arg1) {
    s32 temp_t4;
    s32 temp_t5;
    Object *someObj;
    Object_64_80035F6C *obj64;
    Object_64_80035F6C_2 *someObj64;

    if (obj->unk7C.word < 0) {
        someObj = get_object_struct(obj->unk78);
        if (someObj != NULL) {
            obj64 = obj->unk64;
            someObj64 = someObj->unk64;
            obj->unk7C.word = someObj64->unk3;
            if (obj->unk7C.word < 0 || obj->unk7C.word >= 0xA) {
                obj->unk7C.word = 0;
            }
            obj64->unk20 = D_800DC980;
            obj64->unk24 = obj->unk68[obj->unk7C.word];
            temp_t4 = (obj64->unk24[0] - 1) << 0x15;
            temp_t5 = (obj64->unk24[1] - 1) << 5;
            obj64->unk0 = 0x40000103;
            obj64->unk4 = 0;
            obj64->unk8 = temp_t4;
            obj64->unkC = temp_t5;
            obj64->unk10 = 0x40010203;
            obj64->unk14 = temp_t4;
            obj64->unk18 = (s32)(temp_t4 | temp_t5);
            obj64->unk1C = temp_t5;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80036040.s")

void obj_init_stopwatchman(Object *arg0, s32 arg1) {
    Object_64 *temp;
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x1E;
    arg0->unk4C->unk12 = 0;
    temp = arg0->unk64;
    temp->unkCD.bytes.byteD = 0xFF;
    temp->unk0_a.unk0 = 0.0f;
    D_8011D4D8 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_stopwatchman.s")

void func_80036BCC(u16 arg0, s32 arg1) {
    if ((D_8011D4D8 != 0) && (arg1 & 1)) {
        func_8000488C(D_8011D4D8); //This is likely wrong and will need to be fixed
        D_8011D4D8 = 0;
    }
    if (D_8011D4D8 == 0) {
        func_80001D04(arg0, &D_8011D4D8);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_fish.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_fish.s")

void obj_init_lavaspurt(unk80037578 *arg0, u8 *arg1) {
    arg0->unk78 = arg1[9] * 2;
    arg0->unk7C = arg1[8];
}

void obj_loop_lavaspurt(Object *obj, s32 arg1) {
    if (obj->unk78 > 0) {
        obj->unk78 -= arg1;
        obj->unk6 |= 0x4000;
    } else {
        obj->unk6 &= ~0x4000;
        obj->unk18 += arg1 * 4;
        if (obj->unk18 >= 256) {
            obj->unk18 = 0;
            obj->unk78 = get_random_number_from_range(0, 30) + obj->unk7C.word;
        }
    }
}

void obj_init_posarrow(unk80037624 *arg0, s32 arg1) {
    arg0->unk6 |= 0x4000;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_posarrow.s")

void obj_init_animator(Object *arg0, LevelObjectEntry800376E0 *arg1, s32 arg2) {
    Object_64_800376E0 *obj64;
    LevelModel *levelModel;
    s16 segmentBatchCount;

    obj64 = arg0->unk64;
    levelModel = func_8002C7C4();
    obj64->unk2 = arg1->unk8;
    obj64->unk4 = arg1->unk9;
    obj64->unk6 = arg1->unkA;
    obj64->segmentId = get_level_segment_index_from_position(arg0->x_position, arg0->y_position, arg0->z_position);
    if (arg2 == 0) {
        obj64->unk8 = 0;
        obj64->unkA = 0;
    }
    if (obj64->segmentId != -1) {
        if (obj64->unk2 < 0) {
            obj64->unk2 = 0;
        }
        segmentBatchCount = levelModel->segments[obj64->segmentId].numberOfBatches;
        if (obj64->unk2 >= segmentBatchCount) {
            obj64->unk2 = segmentBatchCount - 1;
        }
    }
    obj_loop_animator(arg0, 0x20000);
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_animator.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_animation.s")

void obj_loop_animobject(s32 arg0, s32 arg1) {
    func_8001F460(arg0, arg1, arg0);
}

void obj_loop_dooropener(unk80037D08_arg0 *arg0, s32 arg1) {
    s32 phi_a0;
    unk80037D08_arg0_64 *sp18;

    sp18 = arg0->unk64;
    phi_a0 = 1 - func_8001F460(arg0, arg1, arg0);
    if (sp18->unk2A > 0) {
        phi_a0 = 0;
    }
    func_800235D0(phi_a0);
}

void obj_init_overridepos(s32 arg0, s32 arg1) {
}

/* Unused? */
void func_80037D60(s32 arg0, s32 arg1) {
}

void obj_init_wizpigship(s32 arg0, s32 arg1) {
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_wizpigship.s")

void obj_loop_vehicleanim(Object *obj, s32 arg1) {
    Object_60_800380F8 *obj60;
    Object *someObj;

    func_8001F460(obj, arg1, obj);
    obj60 = obj->unk60;
    if (obj60 != NULL) {
        if (obj60->unk0 > 0) {
            someObj = obj60->unk0 == 3 ? obj60->unkC : obj60->unk4;
            someObj->y_rotation = 0x4000;
            someObj->unk3A++;
            if (someObj->unk3A == someObj->header->numberOfModelIds) {
                someObj->unk3A = 0;
            }
        }
    }
}

void obj_init_hittester(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 0x81;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

// Literally the same as obj_loop_animobject()
void obj_loop_hittester(s32 arg0, s32 arg1) {
    func_8001F460(arg0, arg1, arg0);
}

void obj_init_dynamic_lighting_object(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

// Literally the same as obj_init_hittester()
void obj_init_unknown96(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 0x81;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

// Literally the same as obj_init_dynamic_lighting_object()
void obj_init_snowball(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

#ifdef NON_EQUIVALENT
// Regalloc issues
void obj_loop_snowball(Object *obj, s32 arg1) {
    Object_64_8003827C *obj64 = obj->unk64;
    if (obj64->unk24 == 0) {
        if (obj64->unk38 != 0) {
            obj64->unk24 = (s16)(obj64->unk38 & 0xFF);
        }
    }
    if (obj64->unk24 != 0) {
        if (obj64->unk20 == 0) {
            func_80009558(obj64->unk24 & 0xFFFF, obj->x_position, obj->y_position, obj->z_position, 1, &obj64->unk20);
        } else {
            func_800096D8(obj64->unk20, obj->x_position, obj->y_position, obj->z_position);
        }
    }
    func_8001F460(obj, arg1, obj);
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_snowball.s")
#endif

// Unused
void func_80038330(Object *obj, s32 arg1) {
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_char_select.s")

void obj_loop_animcamera(Object *obj, s32 arg1) {
    s32 temp_v0;
    s32 phi_v1;
    Object_64_80038710 *obj64;

    temp_v0 = func_8001F460(obj, arg1, obj);
    obj->unk6 |= 0x4000;
    obj64 = obj->unk64;
    if (temp_v0 == 0) {
        if (get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER) {
            phi_v1 = func_800210CC(obj64->unk44);
        } else {
            phi_v1 = 1;
        }
        if (phi_v1) {
            func_80066488(obj64->unk30, obj->x_position, obj->y_position, obj->z_position, 0x8000 - obj->y_rotation, -obj->x_rotation, obj->z_rotation);
        }
    }
}

// Unused
void func_800387C0(Object *obj, s32 arg1) {
}

void obj_loop_animcar(Object *obj, s32 arg1) {
    Object *someObj;
    s32 temp_v0;
    temp_v0 = obj->unk78;
    someObj = NULL;
    if (temp_v0 != 0) {
        someObj = get_object_struct(temp_v0 - 1);
    }
    obj->unk7C.word = func_8001F460(obj, arg1, obj);
    obj->unk6 |= 0x4000;
    if (obj->unk7C.word == 0 && someObj != NULL) {
        Object_64_800387CC *someObj64 = someObj->unk64;
        someObj64->unk148 = obj;
    }
}

void obj_init_infopoint(Object *arg0, u8 *arg1) {
    if (arg1[9] != 0) {
        arg0->unk4C->unk14 = 0x21;
    } else {
        arg0->unk4C->unk14 = 0x22;
    }
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0xF;
    arg0->unk4C->unk12 = 0;
    arg0->unk78 = (arg1[10] << 16) | arg1[8]; // Not sure about the values here.
    arg0->unk7C.word = arg1[9];
    arg0->y_rotation = arg1[11] << 10; // Not sure about the values here.
}

void obj_loop_infopoint(Object *arg0, s32 arg1) {
    s16 temp_a0;
    Object_4C *obj4C;
    Object *playerObj;

    if (arg0->unk7C.word == 0) {
        arg0->unk6 |= 0x4000;
    } else {
        arg0->unk6 &= ~0x4000;
    }

    obj4C = arg0->unk4C;
    if (obj4C->unk13 < ((arg0->unk78 >> 16) & 0xFF)) {
        playerObj = obj4C->unk0;
        if (playerObj->header->behaviorId == 1) {
            Object_64_800388D4 *playerObj64 = playerObj->unk64;
            temp_a0 = playerObj64->unk0;
            if ((temp_a0 != -1) && (get_buttons_pressed_from_player(temp_a0) & Z_TRIG)) {
                func_800C31EC(arg0->unk78 & 0xFF);
            }
        }
    }
}

void obj_init_smoke(s32 arg0, s32 arg1) {
}

void obj_loop_smoke(Object *obj, s32 arg1) {
    f32 temp_f2 = arg1;
    if (osTvType == TV_TYPE_PAL) {
        temp_f2 *= 1.2;
    }
    obj->x_position += obj->x_velocity * temp_f2;
    obj->unk18 += arg1 * 16;
    obj->y_position += obj->y_velocity * temp_f2;
    obj->z_position += obj->z_velocity * temp_f2;
    if (obj->unk18 >= 256) {
        gParticlePtrList_addObject(obj);
        obj->unk18 = 255;
    }
}

void obj_init_unknown25(s32 arg0, s32 arg1) {
}

void obj_loop_unknown25(Object *arg0, s32 arg1) {
    arg0->unk18 += arg1 * 8;
    if (arg0->unk18 >= 256) {
        gParticlePtrList_addObject(arg0);
        arg0->unk18 = 255;
    }
}

void obj_init_wardensmoke(s32 arg0, s32 arg1) {
}

void obj_loop_wardensmoke(Object *arg0, s32 arg1) {
    f32 temp_f2;

    temp_f2 = (f32)arg1;
    if (osTvType == TV_TYPE_PAL) {
        temp_f2 *= 1.2;
    }
    arg0->unk18 += arg1 * 4;
    arg0->y_position += temp_f2 * 0.25;
    if (arg0->unk18 >= 256) {
        gParticlePtrList_addObject(arg0);
        arg0->unk18 = 255;
    }
}

#ifdef NON_EQUIVALENT
// regalloc issues
void obj_init_bombexplosion(Object *obj, unk80038B74 *arg1) {
    s32 temp;
    obj->unk18 = 0;
    obj->scale = 0.5f;
    obj->unk3A = get_random_number_from_range(0, obj->header->numberOfModelIds - 1);
    obj->unk78 = 0;
    obj->unk7C.word = 0xFF;
    temp = (s32)arg1->unk8;
    if (temp != 0) {
        obj->unk7C.word |= (temp << 8) & 0xFF00;
    }
    obj->unk74 = 1;
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_bombexplosion.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_bombexplosion.s")

void obj_init_teleport(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0xF;
    arg0->unk4C->unk12 = 0;
    if (get_settings()->cutsceneFlags & 1) {
        arg0->unk78 = 1;
    }
}

void obj_loop_teleport(Object *arg0, s32 arg1) {
    if (arg0->unk78 != 0) {
        Object_3C_80038DC4 *temp = arg0->unk3C_a.unk3C;
        if (arg0->unk4C->unk13 < 0x78) {
            func_8006F338(temp->unk8);
            arg0->unk78 = 0;
            func_80001D04(0x30, 0);
            func_80000FDC(0x12A, 0, 1.0f);
        }
    }
}

void obj_init_exit(Object *obj, LevelObjectEntry80038E3C *arg1) {
    f32 phi_f0;
    Object_64_80038E3C *obj64;
    phi_f0 = arg1->unk10 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = obj->unk64;
    phi_f0 /= 128;
    obj->scale = phi_f0;
    obj->y_rotation = arg1->unk11 << 6 << 4;
    obj64->unk0 = func_800707C4(obj->y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->x_position) + (obj64->unk8 * obj->z_position));
    obj64->unk10 = arg1->unk10;
    obj64->unk14 = arg1->unk18;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = arg1->unk10;
    obj->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_exit.s")

void obj_init_cameracontrol(unk80039160 *arg0, s8 *arg1) {
    arg0->unk78 = arg1[8];
    func_80011390();
}

void obj_loop_cameracontrol(s32 arg0, s32 arg1) {
}

void obj_init_setuppoint(unk80039190 *arg0, u8 *arg1) {
    s32 temp;
    arg0->unk78 = arg1[8];
    arg0->unk7C = arg1[9];
    arg0->unk0 = arg1[10] << 6 << 4; // Not sure about the values here.
}

void obj_loop_setuppoint(s32 arg0, s32 arg1) {
}

void obj_init_dino_whale(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 3;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
}

void obj_loop_dino_whale(Object *obj, s32 arg1) {
    s32 sp2C;

    if (obj->unk78 > 0) {
        obj->unk78 -= arg1;
        arg1 *= 2;
    } else {
        obj->unk78 = 0;
    }
    sp2C = obj->unk18;
    func_8001F460(obj, arg1, obj);
    func_800113CC(obj, 0, sp2C, 0xAC, 0xAD);
    if (obj->unk4C->unk13 < 0xFF) {
        if (obj->unk78 == 0) {
            obj->unk78 = 0x3C;
            func_80009558(0x23B, obj->x_position, obj->y_position, obj->z_position, 4, NULL);
        }
    }
}

void obj_init_parkwarden(Object *arg0, s32 arg1) {
    Object_64 *temp;
    arg0->unk4C->unk14 = (u16)1;
    arg0->unk4C->unk11 = (u8)0;
    arg0->unk4C->unk10 = (u8)0x1E;
    arg0->unk4C->unk12 = (u8)0;
    temp = arg0->unk64;
    temp->unkCD.bytes.byteD = 0xFF;
    temp->unk0_a.unk0 = 0.0f;
    temp->unk28 = 0;
    temp->unk2C = 0;
    temp->unk34 = 0;
    temp->unk36 = 0;
    D_8011D4D4 = 0;
    D_8011D4E2 = 0x10F;
}

void func_80039320(s16 arg0) {
    D_8011D4E2 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_parkwarden.s")

void func_8003AC3C(u16 arg0, s32 arg1) {
    if ((D_8011D4D4 != 0) && (arg1 & 1)) {
        func_8000488C(D_8011D4D4);
        D_8011D4D4 = 0;
    }
    if (D_8011D4D4 == 0) {
        func_80001D04(arg0, &D_8011D4D4);
    }
}

void obj_loop_gbparkwarden(s32 arg0, s32 arg1) {
}

f32 func_8003ACAC(void) {
    return D_8011D4D0;
}

void obj_init_checkpoint(Object *arg0, u8 *arg1, s32 arg2) {
    f32 phi_f0 = (s32)(arg1[8] & 0xFF);
    if (phi_f0 < 5.0f) {
        phi_f0 = 5.0f;
    }
    phi_f0 /= 64;
    arg0->scale = phi_f0;
    arg0->y_rotation = arg1[10] << 6 << 4; // Not sure about the values here.
    func_80011390();
}

void obj_loop_checkpoint(s32 arg0, s32 arg1) {
}

void obj_init_modechange(Object *obj, LevelObjectEntry8003AD34 *arg1) {
    f32 phi_f0;
    Object_64_8003AD34 *obj64;
    phi_f0 = arg1->unk8 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = obj->unk64;
    phi_f0 /= 128;
    obj->scale = phi_f0;
    obj->y_rotation = arg1->unk9 << 6 << 4;
    obj64->unk0 = func_800707C4(obj->y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->x_position) + (obj64->unk8 * obj->z_position));
    obj64->unk10 = arg1->unk8;
    obj64->unk14 = arg1->unkA;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = arg1->unk8;
    obj->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_modechange.s")

// Exactly the same as obj_init_modechange
void obj_init_bonus(Object *obj, LevelObjectEntry8003AD34 *arg1) {
    f32 phi_f0;
    Object_64_8003AD34 *obj64;
    phi_f0 = arg1->unk8 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = obj->unk64;
    phi_f0 /= 128;
    obj->scale = phi_f0;
    obj->y_rotation = arg1->unk9 << 6 << 4;
    obj64->unk0 = func_800707C4(obj->y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->x_position) + (obj64->unk8 * obj->z_position));
    obj64->unk10 = arg1->unk8;
    obj64->unk14 = arg1->unkA;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = arg1->unk8;
    obj->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_bonus.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_goldenballoon.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_goldenballoon.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_door.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_door.s")

void obj_init_ttdoor(Object *obj, LevelObjectEntry8003C1E0 *arg1) {
    f32 temp_f0;
    Object_64_8003C1E0 *obj64;
    f32 phi_f0;

    obj->unk3A = 0;
    obj64 = obj->unk64;
    obj->y_rotation = arg1->unk8 << 6 << 4;
    obj64->unkF = arg1->unkE;
    obj64->unk13 = arg1->unkB;
    obj64->unk0 = obj->y_position;
    obj64->unk8 = 0;
    obj64->unk12 = arg1->unkA;
    obj->unk78 = obj->y_rotation;
    obj->unk7C.word = (arg1->unk9 & 0x3F) << 0xA;
    phi_f0 = arg1->unkC & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    obj->scale = obj->header->scale * phi_f0;
    obj->unk4C->unk14 = 0x21;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    if (obj->unk3A >= obj->header->numberOfModelIds) {
        obj->unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_ttdoor.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_trigger.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_trigger.s")

void obj_init_bridge_whaleramp(Object *arg0, u8 *arg1) {
    Object_64 *temp = arg0->unk64;
    arg0->unk3A = arg1[8];
    arg0->y_rotation = arg1[9] << 6 << 4;
    temp->unk0_a.unk0 = arg0->y_position;
    arg0->unk4C->unk14 = 0x21;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
    temp->unk4 = 0;
    if (arg0->unk3A >= arg0->header->numberOfModelIds) {
        arg0->unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_bridge_whaleramp.s")

void obj_init_rampswitch(Object *arg0, u8 *arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
    arg0->unk78 = arg1[8];
}

void obj_loop_rampswitch(Object *arg0, s32 arg1) {
    if (arg0->unk4C->unk13 < 0x2D) {
        func_8001E344(arg0->unk78);
    }
    arg0->unk4C->unk13 = (u8)0xFF;
}

void obj_init_seamonster(s32 arg0, s32 arg1) {
}

void obj_loop_seamonster(s32 arg0, s32 arg1) {
}

void obj_init_fogchanger(unk8003CF18 *arg0, u8 *arg1) {
    f32 temp_f0;
    temp_f0 = arg1[8] * 8.0f;
    temp_f0 = temp_f0 * temp_f0;
    arg0->unk78 = temp_f0;
}

void obj_init_skycontrol(Object *arg0, u8 *arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = arg1[9];
    arg0->unk78 = arg1[8];
    arg0->unk7C.word = arg1[9];
}

void obj_loop_skycontrol(Object *arg0, s32 arg1) {
    if (arg0->unk4C->unk13 < arg0->unk7C.word) {
        func_80028044(arg0->unk78);
    }
}

void obj_init_ainode(s32 arg0, u8 *arg1) {
    if (arg1[9] == 0xFF) {
        arg1[9] = func_8001C48C(arg0) & 0xFF;
    }
    func_8001D1BC(arg1[9]);
    func_8001D1AC();
}

void obj_loop_ainode(s32 arg0, s32 arg1) {
}

void obj_init_treasuresucker(unk8003D038 *arg0, s8 *arg1) {
    arg0->unk18 = 0x78;
    arg0->unk78 = (arg1[8] - 1) & 3;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_treasuresucker.s")

void obj_init_flycoin(s32 arg0, s32 arg1) {
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_flycoin.s")

void obj_init_coincreator(unk8003D3EC *arg0, s32 arg1) {
    arg0->unk18 = 0x64;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_coincreator.s")

void obj_init_coin(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x1E;
    arg0->unk7C.half.upper = 0x14;
    arg0->unk7C.half.lower = 0x10;
    if (get_filtered_cheats() & CHEAT_DISABLE_BANANAS) {
        gParticlePtrList_addObject(arg0);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_coin.s")

void obj_init_silvercoin_adv2(Object *obj, s32 arg1) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk78 = 3;
    obj->unk7C.word = 16;
    if (!is_in_tracks_mode()) {
        if (func_8000E1DC() && is_in_adventure_two()) {
            obj->unk78 = 0;
        } else {
            obj->unk78 = 3;
        }
    }
    if (obj->unk78 == 3) {
        obj->unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

void obj_init_silvercoin(Object *obj, s32 arg1) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk78 = 3;
    obj->unk7C.word = 0;
    if (!is_in_tracks_mode()) {
        if (func_8000E1DC() && !is_in_adventure_two()) {
            obj->unk78 = 0;
        } else {
            obj->unk78 = 3;
        }
    }
    if (obj->unk78 == 3) {
        obj->unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_silvercoin.s")

void obj_init_worldkey(Object *obj, unk8003DE74 *arg1) {
    Settings *settings;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    arg1->unk8 &= 0xF;
    obj->unk78 = arg1->unk8;
    settings = get_settings();
    if (!is_in_tracks_mode() && !(settings->keys & (1 << obj->unk78))) {
        return;
    }
    gParticlePtrList_addObject(obj);
}

/**
 * Rotates the key and checks to see if the player grabbed it.
 */
void obj_loop_worldkey(Object *worldKeyObj, s32 speed) {
    Settings *settings;
    Object *playerObj;

    // Check if the player is near the key
    // "worldKeyObj->unk4C->unk13" is the player's distance from the key (Up to 255).
    if (worldKeyObj->unk4C->unk13 < WORLD_KEY_GRAB_CHECK_RADIUS) {
        // "worldKeyObj->unk4C->unk0" is only set when the player is within 255 units of
        // the key object, otherwise it is NULL.
        playerObj = worldKeyObj->unk4C->unk0;
        if (playerObj != NULL) {
            if (playerObj->header->behaviorId == 1) {
                Object_64_8003DF08 *obj64 = playerObj->unk64;
                if (obj64->unk0 != -1) {
                    // Player has grabbed the key!
                    play_sound(SOUND_WORLD_KEY_GRAB);
                    settings = get_settings();
                    settings->keys |= 1 << worldKeyObj->unk78; // Set key flag
                    gParticlePtrList_addObject(worldKeyObj);   // Makes the key unload.
                }
            }
        }
    }

    // Rotate world key
    worldKeyObj->y_rotation += speed * 256;
}

typedef struct Object_64_8003DFCC {
    f32 unk0;
    s16 unk4;
    char unk6[0x2];
    u8 unk8;
    u8 unk9;
    u8 unkA;
} Object_64_8003DFCC;

void obj_init_weaponballoon(Object *arg0, Object_64_8003DFCC *arg1) {
    s32 cheats;
    Object_64_8003DFCC *obj;
    f32 temp;

    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 4;
    arg0->unk4C->unk10 = 0x14;

    cheats = get_filtered_cheats();

    if (cheats & CHEAT_ALL_BALLOONS_ARE_BLUE) {
        arg1->unk9 = 0;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_RED) {
        arg1->unk9 = 1;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_GREEN) {
        arg1->unk9 = 2;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_YELLOW) {
        arg1->unk9 = 3;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_RAINBOW) {
        arg1->unk9 = 4;
    }

    if (arg1->unk8 >= 6) {
        arg1->unk8 = 0;
    }

    if (arg0->unk3A >= arg0->header->numberOfModelIds) {
        arg0->unk3A = 0;
    }

    arg0->unk3A = arg1->unk9;
    arg0->unk78 = arg0->unk3A;

    temp = arg1->unkA & 0xFF;
    if (temp < 10) {
        temp = 10;
    }
    temp /= 64;

    obj = (Object_64_8003DFCC*)arg0->unk64;

    arg0->scale = arg0->header->scale * temp;
    obj->unk0 = arg0->scale;
    obj->unk4 = 0;
    arg0->unk7C.word = 0;

    if (get_filtered_cheats() & CHEAT_DISABLE_WEAPONS) {
        gParticlePtrList_addObject(arg0);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_weaponballoon.s")

void obj_init_wballoonpop(s32 arg0, s32 arg1) {
}

void obj_loop_wballoonpop(s32 arg0, s32 arg1) {
}

void obj_init_weapon(Object *arg0, s32 arg1) {
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x18;
    arg0->unk4C->unk12 = 0;
    arg0->unk78 = func_8000C8B4(0x1E0);
    arg0->unk7C.word = 0;
}

void obj_loop_weapon(Object *arg0) {
    Object_64 *obj64 = arg0->unk64;
    switch (obj64->unk18) {
        case 0:
        case 1:
            func_8003E694();
            break;
        case 2:
        case 3:
        case 10:
        case 11:
            func_8003F2E8();
            break;
    }
    return;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003E694.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003EC14.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003EDD8.s")

void func_8003F0D0(void) {
    D_8011D4DC = 0;
}

void func_8003F0DC(void) {
    D_8011D4DC--;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003F0F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003F2E8.s")

#ifdef NON_EQUIVALENT
// Regalloc issues
void func_8003FC44(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, f32 arg5, s32 arg6) {
    Object *someObj;
    unk8003FC44 sp24;

    sp24.unk4 = (s32)arg1 + 0x24;
    sp24.unk1 = 0xA;
    sp24.unk2 = arg0;
    sp24.unk0 = arg3;
    sp24.unk7 = arg6;
    sp24.unk6 = arg2;
    someObj = func_8000EA54(&sp24, 1);
    if (someObj != NULL) {
        someObj->scale *= 3.5 * arg5;
        someObj->unk3C_a.unk3C = NULL;
        someObj->x_velocity = 0.0f;
        someObj->y_velocity = 0.0f;
        someObj->z_velocity = 0.0f;
    }
    if (arg4 != 0) {
        func_80009558(arg4, arg0, arg1, arg2, 4, 0);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003FC44.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_audio.s")

void obj_init_audioline(Object *arg0, LevelObjectEntry8003FEF4 *arg1) {
    Object_64_8003FEF4 *obj64;

    obj64 = arg0->unk64;
    obj64->unk0 = arg1->unk8;
    obj64->unk2 = arg1->unkA;
    obj64->unkC = arg1->unkC;
    obj64->unkD = arg1->unkD;
    obj64->unk_union.unk8_word = 0;
    obj64->unk4 = arg1->unkE;
    obj64->unk11 = arg1->unk12;
    obj64->unk10 = arg1->unk11;
    obj64->unkE = arg1->unk9;
    obj64->unkF = arg1->unk10;
    obj64->unk12 = arg1->unk13;
    func_800098A4(obj64->unk0, obj64->unk2, arg1->common.x, arg1->common.y, arg1->common.z,
                  obj64->unkF, obj64->unkE, obj64->unk10, obj64->unk12, obj64->unk4, obj64->unk11,
                  obj64->unkC, obj64->unkD);
    gParticlePtrList_addObject(arg0);
}

void obj_init_audioreverb(Object *arg0, LevelObjectEntry8004001C *entry) {
    s32 temp;
    Object_64_8004001C *obj64 = (Object_64_8004001C *)arg0->unk64;
    obj64->unk2 = entry->unk8;
    temp = entry->unk9;
    obj64->unk4 = temp & 0xFF;
    obj64->unk5 = entry->unkA;
    func_80009968(entry->common.x, entry->common.y, entry->common.z, obj64->unk2, obj64->unk4, obj64->unk5);
    gParticlePtrList_addObject(arg0);
}

void obj_init_texscroll(Object *obj, LevelObjectEntry800400A4 *arg1, s32 arg2) {
    Object_64_800400A4 *obj64;
    LevelModel *levelModel;
    s16 numberOfTexturesInLevel;

    obj64 = obj->unk64;
    levelModel = func_8002C7C4();
    obj64->unk0 = arg1->unk8;
    if (obj64->unk0 < 0) {
        obj64->unk0 = 0;
    }
    numberOfTexturesInLevel = levelModel->numberOfTextures;
    if (obj64->unk0 >= numberOfTexturesInLevel) {
        obj64->unk0 = numberOfTexturesInLevel - 1;
    }
    obj64->unk4 = (s16)arg1->unkA;
    obj64->unk6 = (s16)arg1->unkB;
    if (arg2 == 0) {
        obj64->unk8 = 0;
        obj64->unkA = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_texscroll.s")

void obj_init_rgbalight(Object *arg0, s32 arg1, s32 arg2) {
    arg0->unk64 = func_80031CAC(arg0, arg1);
}

void obj_init_buoy_pirateship(Object *arg0, s32 arg1, s32 arg2) {
    arg0->unk64 = func_800BE654(arg0->unk2E, arg0->x_position, arg0->z_position);
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x1E;
    arg0->unk4C->unk12 = 0;
}

void obj_loop_buoy_pirateship(Object *arg0, s32 arg1) {
    if (arg0->unk64 != NULL) {
        arg0->y_position = func_800BEEB4(arg0->unk64);
    }
    arg0->unk18 += arg1 * 8;
}

void obj_init_log(Object *arg0, LevelObjectEntry8004049C *arg1, s32 arg2) {
    f32 phi_f0;
    arg0->unk64 = func_800BE654(arg0->unk2E, arg0->x_position, arg0->z_position);
    arg0->unk4C->unk14 = 1;
    arg0->unk4C->unk11 = 2;
    arg0->unk4C->unk10 = 0x1E;
    phi_f0 = arg1->unk9 & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    arg0->scale = arg0->header->scale * phi_f0;
    arg0->unk3A = arg1->unk8;
    arg0->y_rotation = arg1->unkA << 6 << 4;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_log.s")

void obj_init_weather(unk80040800 *arg0, s16 *arg1) {
    f32 temp = arg1[4];
    temp *= temp;
    arg0->unk78 = temp;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_weather.s")

void obj_init_lensflare(s32 arg0, s32 arg1) {
    func_800AC8A8(arg0);
}

void obj_init_lensflareswitch(Object *arg0, s16 *arg1, s32 arg2) {
    func_800ACF60(arg0);
    arg0->scale = arg1[4];
    arg0->scale /= 40.0f;
}

void obj_init_wavegenerator(s32 arg0, s32 arg1, s32 arg2) {
    func_800BF524(arg0); //waves.c
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_butterfly.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_butterfly.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_midifade.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_midifadepoint.s")

void obj_init_midichset(unk80042014_arg0 *arg0, unk80042014_arg1 *arg1) {
    unk80042014_arg0_64 *temp = arg0->unk64;
    temp->unk0 = arg1->unk8;
    temp->unk2 = arg1->unkA;
    temp->unk3 = arg1->unkB;
}

void obj_init_bubbler(Object *arg0, unk8004203C_arg1 *arg1) {
    func_800AF134(arg0->unk6C, arg1->unk9, arg1->unk8, 0, 0, 0);
    arg0->unk78 = arg1->unkA;
}

void obj_loop_bubbler(Object *arg0, s32 arg1) {
    if (arg0->unk78 >= get_random_number_from_range(0, 0x400)) {
        arg0->unk74 = 1;
    } else {
        arg0->unk74 = 0;
    }
    if (get_number_of_active_players() < 2) {
        func_800AFC3C(arg0, arg1);
    }
}

void obj_init_boost(unk8004210C *arg0, s8 *arg1) {
    arg0->unk64 = (s32)get_misc_asset(0x14) + (arg1[8] << 7);
    arg0->unk3C = 0;
}

void obj_init_unknown94(s32 arg0, s32 arg1, s32 arg2) {
}

void obj_loop_unknown94(s32 arg0, s32 arg1) {
}

void obj_init_rangetrigger(s32 arg0, s32 arg1) {
}

void obj_loop_rangetrigger(Object *obj, s32 arg1) {
    s32 temp;
    Object_3C_80042178 *obj3C;
    unk80042178 sp20;

    obj3C = obj->unk3C_a.unk3C;
    if (func_80016DE8(obj->x_position, 0, obj->z_position, (f32)obj3C->unk8, 1, &sp20) > 0) {
        obj->unk74 = obj3C->unkA;
    } else {
        obj->unk74 = 0;
    }
    func_800AFC3C(obj, arg1);
}

void obj_init_frog(Object *obj, LevelObjectEntry80042210 *arg1) {
    Object_64_80042210 *obj64;

    obj64 = (Object_64_80042210 *)obj->unk64;
    obj64->unk15 = arg1->unkA;
    obj64->unk0 = obj->x_position;
    obj64->unk4 = obj->y_position;
    obj64->unk8 = obj->z_position;
    obj64->unkC = arg1->unk8;
    obj64->unk10 = obj64->unkC * obj64->unkC;
    obj64->unk14 = 0;
    obj64->unk20 = obj->x_position;
    obj64->unk24 = obj->z_position;
    obj64->unk19 = 0;
    obj64->unk30 = 1.0f;

    if (obj64->unk15) {
        obj->unk3A = 1;
        if (is_drumstick_unlocked() || (get_settings()->trophies & 0xFF) != 0xFF) {
            gParticlePtrList_addObject(obj);
        }
    } else {
        obj->unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_frog.s")

void obj_loop_pigrocketeer(s32 arg0, s32 arg1) {
    Object *obj;
    Object_64_80042998 *obj64;

    func_8001F460(arg0, arg1, arg0);
    obj = func_8000BF44(-1);

    if (obj != NULL) {
        obj64 = obj->unk64;
        obj->unk78 = 0;
        if (obj64 != 0) {
            obj64->unk72 += arg1;
            obj64->unk70 = 2;
            obj64->unk74 = 1.0f;
            func_8000B750(arg0, -1, 2, 1, 1);
        }
    }
}

void obj_init_levelname(unk80042A1C *arg0, s8 *arg1) {
    arg0->unk78 = arg1[9] * 8.0f;
    arg0->unk78 *= arg0->unk78;
    arg0->unk7C = arg1[8];
    arg0->unk7E = 0;
    if (is_in_tracks_mode()) {
        gParticlePtrList_addObject(arg0);
    }
    func_800C56D0(4);
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_levelname.s")

void obj_init_wizghosts(unk80042CD0 *arg0, s32 arg1) {
    func_8001F460(arg0, arg1, arg0);
    arg0->unk18 = (arg0->unk18 + (arg1 * 8)) & 0xFF;
}

