/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80033CC0 */

#include "object_functions.h"

#include "PR/os_cont.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "video.h"
#include "camera.h"
#include "menu.h" // For cheats
#include "unknown_0ABDF0.h"
#include "racer.h"
#include "game.h"
#include "audio.h"
#include "unknown_008C40.h"
#include "objects.h"
#include "particles.h"
#include "unknown_0255E0.h"
#include "font.h"
#include "unknown_032760.h"
#include "game_ui.h"
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

Triangle D_800DCAA8[8] = {
    { {{ 0, 0, 3, 1 }}, {  0, 0 }, { -1, -1 }, {  0, -1 } },
    { {{ 0, 0, 2, 3 }}, {  0, 0 }, { -1,  0 }, { -1, -1 } },
    { {{ 0, 2, 5, 3 }}, { -1, 0 }, {  0, -1 }, { -1, -1 } },
    { {{ 0, 2, 4, 5 }}, { -1, 0 }, {  0,  0 }, {  0, -1 } },
    { {{ 0, 0, 1, 3 }}, {  0, 0 }, {  0, -1 }, { -1, -1 } },
    { {{ 0, 0, 3, 2 }}, {  0, 0 }, { -1, -1 }, { -1,  0 } },
    { {{ 0, 2, 3, 5 }}, { -1, 0 }, { -1, -1 }, {  0, -1 } },
    { {{ 0, 2, 5, 4 }}, { -1, 0 }, {  0, -1 }, {  0,  0 } },
};

VertexPosition D_800DCB28[6] = {
    { -64, 0,  32 },
    { -64, 0, -32 },
    {   0, 0,  32 },
    {   0, 0, -32 },
    {  64, 0,  32 },
    {  64, 0, -32 },
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

void obj_init_scenery(Object *obj, LevelObjectEntry_Scenery *entry) {
    f32 phi_f0;
    obj->segment.trans.unk6 |= 2;
    phi_f0 = entry->unk9 & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    ((Object_50_Scenery *)obj->unk50)->unk0 = obj->segment.header->unk4 * phi_f0;
    obj->segment.unk3A = entry->unk8;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
    if (entry->unkB) {
        obj->unk4C->unk14 = 1;
        obj->unk4C->unk11 = 1;
        obj->unk4C->unk10 = 20;
        obj->unk4C->unk12 = 0;
        obj->unk4C->unk16 = -5;
        obj->unk4C->unk17 = entry->unkB;
    }
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
    obj->unk78 = 0;
    obj->unk7C.word = 0;
}

void obj_loop_scenery(Object *obj, s32 speed) {
	Object78_80033DD0 *obj78;
	s32 temp_v0;
	
    if (obj->unk4C != NULL) {
        obj78 = &obj->unk78;
        if (obj->unk7C.half.upper > 0) {
            obj78->unk4 -= speed;
        }
        if ((obj->unk4C->unk14 & 0x40) && ((s32) obj78->unk4 <= 0)) {
            func_80009558(316, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
            obj78->unk0 = (s32*) obj->unk4C->unk0;
            obj78->unk6 = 1820;
            obj78->unk4 = 10;
            if (get_number_of_active_players() < 2) {
                if (obj->segment.header->unk57 > 0) {
                    if (obj->segment.header->unk57 == 1) {
                        temp_v0 = 0;
                    } else {
                        temp_v0 = get_random_number_from_range(0, obj->segment.header->unk57 - 1);
                    }
                    obj->unk74 = 1 << temp_v0;
                    func_800AFC3C(obj, 2);
                }
            }
        } else if (obj78->unk4 <= 0) {
            obj78->unk0 = 0;
        }
        obj->segment.trans.z_rotation = (s16) obj78->unk6;
        obj78->unk6 = (obj78->unk6 * -200) >> 8;
    }
}

void obj_init_fireball_octoweapon(Object *obj, LevelObjectEntry_Fireball_Octoweapon *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
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

void obj_loop_fireball_octoweapon(Object *obj, s32 speed) {
	Object *obj78;
	Object_4C *obj4C;
	f32 sp7C;
	Object80033F60_4C_64 *obj4C_obj64;
	Object80033F60_64 *obj64;
	Object *obj4C_obj;
	f32 phi_f2;
    s32 *temp;
	f32 sp4C[7];

    obj78 = (Object*)obj->unk78;
	
    sp7C = speed;
    if (osTvType == TV_TYPE_PAL) {
        sp7C *= 1.2;
    }
	
    if ((obj->behaviorId == 116) && (obj->unk7C.word < 0)) {
        obj->segment.trans.x_position = 0.0f;
        obj->segment.trans.y_position = 0.0f;
        obj->segment.trans.z_position = 0.0f;
        func_80011560();
        func_80011570(obj, obj78->segment.trans.x_position, obj78->segment.trans.y_position, obj78->segment.trans.z_position);
    } else {
        phi_f2 = (obj78->segment.trans.x_position - obj->segment.trans.x_position) * 0.1;
        if (phi_f2 > 10.0) {
            phi_f2 = 10.0f;
        }
        if (phi_f2 < -10.0) {
            phi_f2 = -10.0f;
        }
        obj->segment.x_velocity += (phi_f2 - obj->segment.x_velocity) * 0.125 * sp7C;
        phi_f2 = (obj78->segment.trans.y_position - obj->segment.trans.y_position) * 0.1;
        if (phi_f2 > 10.0) {
            phi_f2 = 10.0f;
        }
        if (phi_f2 < -10.0) {
            phi_f2 = -10.0f;
        }
        obj->segment.y_velocity += (phi_f2 - obj->segment.y_velocity) * 0.125 * sp7C;
        phi_f2 = (obj78->segment.trans.z_position - obj->segment.trans.z_position) * 0.1;
        if (phi_f2 > 10.0) {
            phi_f2 = 10.0f;
        }
        if (phi_f2 < -10.0) {
            phi_f2 = -10.0f;
        }
        obj->segment.z_velocity += (phi_f2 - obj->segment.z_velocity) * 0.125 * sp7C;
        if (sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity)) > 0.5) {
            obj->segment.trans.y_rotation = func_80070750(obj->segment.x_velocity, obj->segment.z_velocity);
            obj->segment.trans.x_rotation -= speed << 9;
        }
        func_80011570(obj, obj->segment.x_velocity * sp7C, obj->segment.y_velocity * sp7C, obj->segment.z_velocity * sp7C);
        if (obj->unk4A == 298 && func_8002AD08(obj->segment.trans.y_position, &sp4C, 0)) {
			obj->segment.trans.y_position = sp4C[0];
        }
    }
    obj->segment.unk18 += speed * 10;
    obj64 = obj->unk64;
    obj4C = obj->unk4C;
    obj4C_obj = (Object*)obj4C->unk0; // This should be a0, not v1!
    if ((obj4C_obj != NULL) && (obj4C->unk13 < 60) && (obj4C_obj->segment.header->behaviorId == 1)) {
        obj4C_obj64 = obj4C_obj->unk64;
        if (obj4C_obj64->unk0 != -1) {
            if (obj->behaviorId == 108) {
                obj4C_obj64->unk187 = 1;
                obj->unk7C.word = 20;
                func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 17, 1.0f, 1);
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
        func_800AFC3C(obj, speed);
        obj->unk7C.word -= speed;
        if (obj->unk7C.word < 0) {
            if (obj->unk4A == 298) {
                gParticlePtrList_addObject(obj);
                func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 17, 1.0f, 1);
            }
            obj->segment.trans.scale *= 0.9;
            if (obj->segment.trans.scale < 0.5) {
                gParticlePtrList_addObject(obj);
            }
        }
    } else {
        if (obj->unk7C.word < 0) {
            obj->unk7C.word += speed;
            if (obj->unk7C.word >= 0) {
                obj->unk7C.word = 0;
            }
        } else {
            obj->unk7C.word -= speed;
            if (obj->unk7C.word <= 0) {
                obj->unk7C.word = 0;
            }
        }
        if (obj->unk7C.word == 0) {
            temp = obj64->unk1C;
            if (temp != 0) {
                func_8000488C(temp);
            }
            func_80009558(341, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, 0);
            gParticlePtrList_addObject(obj);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_fireball_octoweapon.s")
#endif

void obj_init_lasergun(Object *obj, LevelObjectEntry_Lasergun *entry) {
    Object_64 *obj64;
    obj->unk4C->unk14 = 0x22;
    obj->unk4C->unk11 = 0;
    obj64 = obj->unk64;
    obj64->unkE = entry->unkA;
    obj64->unkF = entry->unkB;
    obj64->unk10 = entry->unkC;
    obj64->unk11 = entry->unkD;
    obj64->unkCD.half = obj64->unkF;
    obj->segment.trans.y_rotation = entry->unk8 << 4 << 4; // Not sure about the shift amounts here, but it
    obj->segment.trans.x_rotation = entry->unk9 << 4 << 4; // just needs to be 2 left shifts that add up to 8.
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_lasergun.s")

void obj_init_laserbolt(Object *obj, LevelObjectEntry_Laserbolt *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
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

void obj_loop_laserbolt(Object *obj, s32 speed) {
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
    sp5C = speed;
    if (osTvType == TV_TYPE_PAL) {
        sp5C *= 1.2;
    }
    sp40 = obj->segment.trans.x_position + (obj->segment.x_velocity * sp5C);
    sp44 = obj->segment.trans.y_position + (obj->segment.y_velocity * sp5C);
    sp48 = obj->segment.trans.z_position + (obj->segment.z_velocity * sp5C);
    sp3C = 9.0f;

    func_80031130(1, &obj->segment.trans.x_position, &sp40, -1);
    sp38 = FALSE;
    func_80031600(&obj->segment.trans.x_position, &sp40, &sp3C, &sp4E, 1, &sp38);
    if (sp38) {
        obj->segment.x_velocity = (sp40 - obj->segment.trans.x_position) / sp5C;
        obj->segment.y_velocity = (sp44 - obj->segment.trans.y_position) / sp5C;
        obj->segment.z_velocity = (sp48 - obj->segment.trans.z_position) / sp5C;
    }
    func_80011570(obj, obj->segment.x_velocity * sp5C, obj->segment.y_velocity * sp5C, obj->segment.z_velocity * sp5C);
    if (sp38) {
        func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position - 36.0f, obj->segment.trans.z_position, 44, 0, 0.2, 0);
        sp4F = TRUE;
    }
	
    if (obj->unk78 > 0) {
        obj->unk78 -= speed;
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
            func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position - 36.0f, obj->segment.trans.z_position, 44, 17, 0.5, 0);
        }
    }
    if (sp4F) {
        gParticlePtrList_addObject(obj);
    }
}

void obj_init_torch_mist(Object *obj, LevelObjectEntry_Torch_Mist *entry) {
    f32 phi_f0 = (s32)(entry->unk9 & 0xFF);
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->unk78 = entry->unk8;
}

void obj_loop_torch_mist(Object *obj, s32 speed) {
    obj->segment.unk18 += obj->unk78 * speed;
}

void obj_init_effectbox(Object *obj, LevelObjectEntry_EffectBox *entry) {
}

#ifdef NON_EQUIVALENT

// Has regalloc & stack issues.

f32 func_800707C4(s16);
f32 func_800707F8(s16);
Object **get_object_struct_array(s32 *count);

void obj_loop_effectbox(Object *obj, s32 speed) {
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
    temp0 = func_800707F8((obj3C->unkB << 8) * -1);
    temp1 = func_800707C4((obj3C->unkB << 8) * -1);
    temp2 = obj3C->unk8 * 3;
    temp3 = obj3C->unk9 * 3;
    temp4 = obj3C->unkA * 3;
    for (i = 0; i < numberOfObjects; i++)
    {
        xDiff = objList[i]->segment.trans.x_position - obj->segment.trans.x_position;
        yDiff = objList[i]->segment.trans.y_position - obj->segment.trans.y_position;
        zDiff = objList[i]->segment.trans.z_position - obj->segment.trans.z_position;
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

void obj_init_trophycab(Object *obj, LevelObjectEntry_TrophyCab *entry) {
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->segment.trans.y_rotation = entry->rotation << 6 << 4; // Not sure about the values here.
}

#ifdef NON_EQUIVALENT

void func_80001D04(u16, s32 *);
void func_80001D04(u16, s32 *);
u32 func_80001C08(void);
void func_80001D04(u16, s32 *);
Object *spawn_object(void *, s32);
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

void obj_loop_trophycab(Object *obj, s32 speed) {
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
                sp44.unk2 = obj->segment.unk3C_a.unk3C->unk2;
                sp44.unk4 = obj->segment.unk3C_a.unk3C->unk4;
                sp44.unk6 = obj->segment.unk3C_a.unk3C->unk6;
                sp44.unk1 = 8;
                trophyObj = spawn_object(&sp44, 1);
                if (trophyObj) {
                    trophyObj->segment.unk3C_a.unk3C = (void *) 0;
                    trophyObj->segment.trans.y_rotation = obj->segment.trans.y_rotation;
                }
            }
        }
    }
    
    ((Object_54_80034E9C *) obj->unk54)->unk2C = 0.612f;
    ((Object_54_80034E9C *) obj->unk54)->unk28 = 0.0f;
    
    playerObj = get_object_struct(0);
    if (playerObj) {
        xDiff = obj->segment.trans.x_position - playerObj->segment.trans.x_position;
        zDiff = playerObj->segment.trans.z_position - obj->segment.trans.z_position;
        sqrtf((xDiff * xDiff) + (zDiff * zDiff)); // Distance on X & Z axes. Not used?
    
        new_var2 = settings->bosses;

        /**
          * Future Fun Land doesn't have a boss rematch, so this OR is needed so that 
          * trophy race becomes avaliable after all the balloons have been collected.  
          */
        new_var2 |= 0x800; 
    
        // Check if all the balloons have been collected.
        isTrophyRaceAvaliable = (settings->balloonsPtr[settings->worldId] < 8) ^ 1;
        if (isTrophyRaceAvaliable) {
            // Check if the boss rematch has been beaten.
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
            if (speed < obj64->unk0) {
                obj64->unk0 -= speed;
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
            obj64->unk4 -= speed;
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

void obj_init_collectegg(Object *obj, LevelObjectEntry_CollectEgg *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_collectegg.s")

void obj_init_eggcreator(Object *obj, LevelObjectEntry_EggCreator *entry) {
}

void obj_loop_eggcreator(Object *obj, s32 speed) {
    unk8003564C sp20;
    Object *someObj;

    if (obj->unk78 == 0) {
        sp20.unk2 = obj->segment.trans.x_position;
        sp20.unk4 = obj->segment.trans.y_position;
        sp20.unk6 = obj->segment.trans.z_position;
        sp20.unk1 = 8;
        sp20.unk0 = 0x34;
        someObj = spawn_object(&sp20, 1);
        if (someObj != NULL) {
            Object_64_8003564C *someObj64 = someObj->unk64;
            someObj64->unk4 = obj;
            obj->unk78 = someObj;
            someObj->segment.unk3C_a.unk3C = 0;
        }
    }
}

void obj_init_lighthouse_rocketsignpost(Object *obj, LevelObjectEntry_Lighthouse_RocketSignpost *entry) {
    f32 phi_f0 = entry->unk9 & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_loop_rocketsignpost(Object *obj, s32 speed) {
    Object *playerObj;
    Object_4C *obj4C;

    playerObj = get_object_struct(0);
    if (playerObj != NULL) {
        obj4C = obj->unk4C;
        if (obj4C->unk13 < 0xC8) {
            if (playerObj == obj4C->unk0) {
                // Detect if the player honks or slams into the signpost.
                if ((get_buttons_pressed_from_player(0) & Z_TRIG) || playerObj == obj->unk5C->unk100) { 
                    func_8006F29C();
                }
            }
        }
    }
    obj->unk4C->unk13 = 0xFF;
}

void obj_init_airzippers_waterzippers(Object *obj, LevelObjectEntry_AirZippers_WaterZippers *entry) {
    ObjectHeader *objHeader;
    f32 phi_f0;

    phi_f0 = entry->unk9 & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    objHeader = obj->segment.header;
    phi_f0 /= 64;
    obj->segment.trans.scale = objHeader->scale * phi_f0;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
    if (obj->segment.unk3A >= objHeader->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        gParticlePtrList_addObject(obj);
    }
}


void obj_loop_airzippers_waterzippers(Object *obj, s32 speed) {
    Object *curRacerObj;
    Object_64_Racer *racerObj64;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    s32 numObjects;
    Object** racerObjs;
    s32 i;

    if (func_8000E1CC() == 0) {
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= 0xBFFF;
    }
    if ((obj->unk4C->unk13 < 100) && !(obj->segment.trans.unk6 & 0x4000)) {
        racerObjs = get_object_struct_array(&numObjects);
        for (i = 0; i < numObjects; i++) {
            curRacerObj = racerObjs[i];
            racerObj64 = (Object_64_Racer*)curRacerObj->unk64;
            if ((racerObj64->unk1F5 == 0) && (racerObj64->unk1D3 < 15)) {
                xDiff = curRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
                yDiff = curRacerObj->segment.trans.y_position - obj->segment.trans.y_position;
                zDiff = curRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((s32) sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < 100) {
                    racerObj64->unk1F5 = 1;
                    racerObj64->unk14C = obj;
                }
            }
        }
    }
}

void obj_init_groundzipper(Object *arg0, LevelObjectEntry_GroundZipper *entry) {
    ObjectHeader *header;
    f32 objScale;

    objScale = entry->scale & 0xFF;
    if (objScale < 10.0f) {
        objScale = 10.0f;
    }
    objScale /= 64;
    header = arg0->segment.header;
    arg0->segment.trans.scale = header->scale * objScale;
    arg0->unk50->unk0 = header->unk4 * objScale;
    arg0->segment.trans.y_rotation = entry->rotation << 6 << 4;
    if (arg0->segment.unk3A >= arg0->segment.header->numberOfModelIds) {
        arg0->segment.unk3A = 0;
    }
    arg0->unk78 = (s32)(28.0f * objScale) + 15;
    if (arg0->unk78 < 0) {
        arg0->unk78 = 0;
    }
    if (arg0->unk78 >= 0x100) {
        arg0->unk78 = 0xFF;
    }
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
    arg0->unk4C->unk16 = -0x64;
    arg0->unk4C->unk17 = 0x64;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        gParticlePtrList_addObject(arg0);
    }
}

void obj_loop_groundzipper(Object *obj, s32 speed) {
    Object *curRacerObj;
    Object_64_Racer *racerObj64;
    f32 xDiff;
    f32 yDiff;
    s32 numObjects;
    f32 zDiff;
    Object** racerObjs;
    s32 i;

    obj->segment.trans.unk6 &= 0xBFFF;
    obj->segment.trans.unk6 |= 0x1000;
    get_object_struct(0); // Unused. I guess the developers forgot to remove this?
    if ((s32) obj->unk4C->unk13 < obj->unk78) {
        racerObjs = get_object_struct_array(&numObjects);
        for (i = 0; i < numObjects; i++) {
            curRacerObj = racerObjs[i];
            racerObj64 = (Object_64_Racer*)curRacerObj->unk64;
            if ((racerObj64->unk1D3 < 15) && (racerObj64->unk1E2 != 0)) {
                xDiff = curRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
                yDiff = curRacerObj->segment.trans.y_position - obj->segment.trans.y_position;
                zDiff = curRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((s32) sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < obj->unk78) {
                    if (racerObj64->unk0 != -1) {
                        func_80001EA8(263, curRacerObj->segment.trans.x_position, curRacerObj->segment.trans.y_position, curRacerObj->segment.trans.z_position, NULL);
                    }
                    racerObj64->unk1D3 = func_8000C8B4(45);
                    racerObj64->unk203 = 2;
                    if (racerObj64->unk20C) {
                        racerObj64->unk203 |= 4;
                    }
                    if (racerObj64->unk1D8 == 0) {
                        func_80072348(racerObj64->unk0, 8);
                    }
                }
            }
        }
    }
}

void obj_init_unknown58(Object *obj, LevelObjectEntry_Unknown58 *entry) {
    obj->unk78 = 0;
    obj->unk7C.word = obj->segment.header;
}

void obj_loop_unknown58(Object *obj, s32 speed) {
    Object *someObj;
    Object *someOtherObj;
    Object_64_80035E34 *someOtherObj64;
    Object_60 *obj60;

    obj->segment.unk3B = 0;
    obj->segment.unk18 = 0x28;
    if (func_8001139C() == 0) {
        obj->unk78 += speed;
    }
    set_ghost_position_and_rotation(obj);
    func_800AFC3C(obj, speed);
    someOtherObj = get_object_struct(0);
    someOtherObj64 = someOtherObj->unk64;
    obj60 = obj->unk60;
    if (obj60->unk0 == 1) {
        s8 temp = someOtherObj64->unk1D6;
        if ((temp == 1) || (temp == 2)) {
            someObj = (Object *)obj60->unk4;
            someObj->segment.trans.y_rotation = 0x4000;
            someObj->segment.unk3A++;
            someObj->segment.unk3A &= 1;
        }
    }
}

void obj_init_characterflag(Object *obj, LevelObjectEntry_CharacterFlag *entry) {
    f32 phi_f0;
    obj->unk78 = (s32)entry->unkE;
    obj->unk7C.word = -1;
    obj->segment.trans.y_rotation = entry->unkC << 6 << 4; // Not sure about the values here.
    phi_f0 = (f32)(entry->unkA & 0xFF);
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = (f32)(obj->segment.header->scale * phi_f0);
}

void obj_loop_characterflag(Object *obj, s32 speed) {
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

void obj_init_stopwatchman(Object *obj, LevelObjectEntry_StopWatchMan *entry) {
    Object_64 *temp;
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk4C->unk12 = 0;
    temp = obj->unk64;
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

void obj_init_lavaspurt(Object *obj, LevelObjectEntry_LavaSpurt *entry) {
    obj->unk78 = entry->unk9 * 2;
    obj->unk7C.word = entry->unk8;
}

void obj_loop_lavaspurt(Object *obj, s32 speed) {
    if (obj->unk78 > 0) {
        obj->unk78 -= speed;
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= ~0x4000;
        obj->segment.unk18 += speed * 4;
        if (obj->segment.unk18 >= 256) {
            obj->segment.unk18 = 0;
            obj->unk78 = get_random_number_from_range(0, 30) + obj->unk7C.word;
        }
    }
}

void obj_init_posarrow(Object *obj, LevelObjectEntry_PosArrow *entry) {
    obj->segment.trans.unk6 |= 0x4000;
}

void obj_loop_posarrow(Object *obj, s32 speed) {
    Object_64_PosArrow *someObj64;
    Object **someObjList;
    Object *someObj;
    s32 numberOfObjects;

    obj->segment.trans.unk6 |= 0x4000;
    someObjList = func_8001BAAC(&numberOfObjects);
    if (obj->unk78 < numberOfObjects) {
        someObj = someObjList[obj->unk78];
        someObj64 = someObj->unk64;
        if (someObj64->unk0 == -1) {
            obj->segment.trans.unk6 &= ~0x4000;
            someObj64->unk150 = obj;
        }
        obj->segment.unk18 = obj->unk78 * 127;
    }
}

void obj_init_animator(Object *obj, LevelObjectEntry_Animator *entry, s32 arg2) {
    Object_64_800376E0 *obj64;
    LevelModel *levelModel;
    s16 segmentBatchCount;

    obj64 = obj->unk64;
    levelModel = func_8002C7C4();
    obj64->unk2 = entry->unk8;
    obj64->unk4 = entry->unk9;
    obj64->unk6 = entry->unkA;
    obj64->segmentId = get_level_segment_index_from_position(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
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
    obj_loop_animator(obj, 0x20000);
}

#ifdef NON_EQUIVALENT

typedef struct Object_64_Animator {
    /* 0x00 */ s16 segmentId;
    /* 0x02 */ s16 batchId;
    /* 0x04 */ s16 xSpeedFactor;
    /* 0x06 */ s16 ySpeedFactor;
    /* 0x08 */ s16 xSpeed;
    /* 0x0A */ s16 ySpeed;
} Object_64_Animator;

#define TEX_INDEX_NO_TEXTURE 255

// Has minor issues

void obj_loop_animator(Object* obj, s32 speed) {
    Object_64_Animator* obj64; // 3C
    s32 sp20;
    s32 sp1C;
    LevelModel* levelModel;
    s32 temp, temp2, segmentId, batchId;
    s32 i;
    s32 nextFacesOffset;
    s32 curFacesOffset;
    s32 texUVSpeed;
    s32 texIndex;
    TextureInfo *texInfo;
    TriangleBatchInfo *triangleBatchInfo;
    LevelModelSegment *levelModelSegment;
    Triangle* triangle;
    TextureHeader *tex;
    s32 maxSpeed;

    obj64 = (Object_64_Animator*)obj->unk64;
    
    temp = obj64->xSpeedFactor * speed;
    obj64->xSpeed += temp << 4;
    sp20 = obj64->xSpeed >> 4;
    obj64->xSpeed &= 0xF;

    temp2 = obj64->ySpeedFactor * speed;
    obj64->ySpeed += temp2 << 4;
    sp1C = obj64->ySpeed >> 4;
    obj64->ySpeed &= 0xF;

    segmentId = obj64->segmentId;

    if (obj64->segmentId != -1) {
        levelModel = func_8002C7C4();
        levelModelSegment = &levelModel->segments[segmentId];
        batchId = obj64->batchId;
        triangleBatchInfo = &levelModelSegment->batches[batchId];
        texIndex = triangleBatchInfo->textureIndex;
        curFacesOffset = triangleBatchInfo->facesOffset;
        nextFacesOffset = triangleBatchInfo[1].facesOffset;
        if (texIndex != TEX_INDEX_NO_TEXTURE) {
            texUVSpeed = levelModel->textures[texIndex].texture->width << 7;
            maxSpeed = texUVSpeed * 2;
            for (i = curFacesOffset; i < nextFacesOffset; i++) {
                triangle = &levelModelSegment->triangles[i];
                if (!(triangle->drawBackface & 0x80)) {
                    if (maxSpeed < triangle->uv0.v) {
                        triangle->uv0.v -= texUVSpeed;
                        triangle->uv1.v -= texUVSpeed;
                        triangle->uv2.v -= texUVSpeed;
                    }
                    if (triangle->uv0.v < 0) {
                        triangle->uv0.v += texUVSpeed;
                        triangle->uv1.v += texUVSpeed;
                        triangle->uv2.v += texUVSpeed;
                    }
                    if (maxSpeed < triangle->uv0.u) {
                        triangle->uv0.u -= texUVSpeed;
                        triangle->uv1.u -= texUVSpeed;
                        triangle->uv2.u -= texUVSpeed;
                    }
                    if (triangle->uv0.u < 0) {
                        triangle->uv0.u += texUVSpeed;
                        triangle->uv1.u += texUVSpeed;
                        triangle->uv2.u += texUVSpeed;
                    }
                    triangle->uv0.v += sp1C;
                    triangle->uv1.v += sp1C;
                    triangle->uv2.v += sp1C;
                    triangle->uv0.u += sp20;
                    triangle->uv1.u += sp20;
                    triangle->uv2.u += sp20;
                }
            }
        }
    }
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_animator.s")
#endif

void obj_init_animation(Object *obj, LevelObjectEntry_Animation *entry, s32 arg2) {
    Object_64_Animation* obj64;
    Object* sp24;
    s8 tempOrderIndex;
    f32 scalef;

    scalef = entry->scale & 0xFF;
    if (scalef < 1.0f) {
        scalef = 1.0f;
    }
    scalef /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj->segment.trans.y_rotation = entry->y_rotation << 8;
    obj->segment.trans.x_rotation = entry->x_rotation << 8;
    obj->segment.trans.z_rotation = entry->z_rotation << 8;
    if (entry->actorIndex == -2) {
        entry->actorIndex = func_8001F3B8();
    } else {
        if (entry->actorIndex < 0 && entry->actorIndex >= -2) {
            entry->actorIndex = 0;
        }
        func_8001F3C8(entry->actorIndex);
    }
    if (entry->channel == -1) {
        entry->channel = func_8001E440();
    }
    if (entry->channel == 20) {
        entry->actorIndex |= 0x80;
    }
    tempOrderIndex = func_8001F3EC(entry->actorIndex);
    if (entry->order == -2) {
        entry->order = tempOrderIndex;
        if (entry->order < 0) {
            entry->order = 0;
        }
    } else {
        if ((tempOrderIndex >= 0) && (entry->order >= tempOrderIndex)) {
            entry->order = tempOrderIndex;
        }
        if (entry->order < 0) {
            entry->order = 0;
        }
    }
    func_80011390();
    obj->unk7C.word = entry->actorIndex;
    obj->unk78 = arg2;
    if (arg2 != 0 && (get_buttons_pressed_from_player(0) & R_CBUTTONS)) {
        obj->unk78 = 2;
    }
    if (((func_8001E440() == entry->channel) || (entry->channel == 20)) && (obj->unk64 == NULL) && (entry->order == 0) && (entry->objectIdToSpawn != -1)) {
        func_8001F23C(obj, entry);
    }
    obj64 = (Object_64_Animation*)obj->unk64;
    if (obj->unk64 != 0) { 
        func_8001EFA4(obj, obj64);
        if (entry->order != 0 || obj64->unk4A != entry->objectIdToSpawn) {
            gParticlePtrList_addObject(obj64);
            obj->unk64 = NULL;
        }
    }
    if (func_80021600(obj->unk7C.word)) {
        func_8001EE74();
    }
}


void obj_loop_animobject(Object *obj, s32 speed) {
    func_8001F460(obj, speed, obj);
}

void obj_loop_dooropener(Object *obj, s32 speed) {
    s32 phi_a0;
    unk80037D08_arg0_64 *sp18;

    sp18 = obj->unk64;
    phi_a0 = 1 - func_8001F460(obj, speed, obj);
    if (sp18->unk2A > 0) {
        phi_a0 = 0;
    }
    func_800235D0(phi_a0);
}

void obj_init_overridepos(Object *obj, LevelObjectEntry_OverridePos *entry) {
}

/* Unused? */
void func_80037D60(s32 arg0, s32 arg1) {
}

void obj_init_wizpigship(Object *obj, LevelObjectEntry_WizpigShip *entry) {
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_wizpigship.s")

void obj_loop_vehicleanim(Object *obj, s32 speed) {
    Object_60_800380F8 *obj60;
    Object *someObj;

    func_8001F460(obj, speed, obj);
    obj60 = obj->unk60;
    if (obj60 != NULL) {
        if (obj60->unk0 > 0) {
            someObj = obj60->unk0 == 3 ? obj60->unkC : obj60->unk4;
            someObj->segment.trans.y_rotation = 0x4000;
            someObj->segment.unk3A++;
            if (someObj->segment.unk3A == someObj->segment.header->numberOfModelIds) {
                someObj->segment.unk3A = 0;
            }
        }
    }
}

void obj_init_hittester(Object *obj, LevelObjectEntry_HitTester *entry) {
    obj->unk4C->unk14 = 0x81;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_loop_hittester(Object *obj, s32 speed) {
    func_8001F460(obj, speed, obj);
}

void obj_init_dynamic_lighting_object(Object *obj, LevelObjectEntry_DynamicLightingObject *entry) {
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_init_unknown96(Object *obj, LevelObjectEntry_Unknown96 *entry) {
    obj->unk4C->unk14 = 0x81;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_init_snowball(Object *obj, LevelObjectEntry_Snowball *entry) {
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_loop_snowball(Object *obj, s32 speed) {
    Object_64_Snowball *obj64 = obj->unk64;
    if (obj64->unk24 == 0) {
        if (obj64->unk38 != 0) {
            obj64->unk24 = (s16)(obj64->unk38 & 0xFF);
        }
    }
    if (obj64->unk24 != 0) {
        if (obj64->unk20 == 0) {
            func_80009558(obj64->unk24, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, &obj64->unk20);
        } else {
            func_800096D8(obj64->unk20, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
    }
    func_8001F460(obj, speed, obj);
}

// Unused
void func_80038330(s32 arg0, s32 arg1) {
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_char_select.s")

void obj_loop_animcamera(Object *obj, s32 speed) {
    s32 temp_v0;
    s32 phi_v1;
    Object_64_80038710 *obj64;

    temp_v0 = func_8001F460(obj, speed, obj);
    obj->segment.trans.unk6 |= 0x4000;
    obj64 = obj->unk64;
    if (temp_v0 == 0) {
        if (get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER) {
            phi_v1 = func_800210CC(obj64->unk44);
        } else {
            phi_v1 = 1;
        }
        if (phi_v1) {
            func_80066488(obj64->unk30, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0x8000 - obj->segment.trans.y_rotation, -obj->segment.trans.x_rotation, obj->segment.trans.z_rotation);
        }
    }
}

// Unused
void func_800387C0(s32 arg0, s32 arg1) {
}

void obj_loop_animcar(Object *obj, s32 speed) {
    Object *someObj;
    s32 temp_v0;
    temp_v0 = obj->unk78;
    someObj = NULL;
    if (temp_v0 != 0) {
        someObj = get_object_struct(temp_v0 - 1);
    }
    obj->unk7C.word = func_8001F460(obj, speed, obj);
    obj->segment.trans.unk6 |= 0x4000;
    if (obj->unk7C.word == 0 && someObj != NULL) {
        Object_64_800387CC *someObj64 = someObj->unk64;
        someObj64->unk148 = obj;
    }
}

void obj_init_infopoint(Object *obj, LevelObjectEntry_InfoPoint *entry) {
    if (entry->unk8[1] != 0) {
        obj->unk4C->unk14 = 0x21;
    } else {
        obj->unk4C->unk14 = 0x22;
    }
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0xF;
    obj->unk4C->unk12 = 0;
    obj->unk78 = (entry->unk8[2] << 16) | entry->unk8[0]; // Not sure about the values here.
    obj->unk7C.word = entry->unk8[1];
    obj->segment.trans.y_rotation = entry->unkB << 10; // Not sure about the values here.
}

void obj_loop_infopoint(Object *obj, s32 speed) {
    s16 temp_a0;
    Object_4C *obj4C;
    Object *playerObj;

    if (obj->unk7C.word == 0) {
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= ~0x4000;
    }

    obj4C = obj->unk4C;
    if (obj4C->unk13 < ((obj->unk78 >> 16) & 0xFF)) {
        playerObj = obj4C->unk0;
        if (playerObj->segment.header->behaviorId == 1) {
            Object_64_800388D4 *playerObj64 = playerObj->unk64;
            temp_a0 = playerObj64->unk0;
            if ((temp_a0 != -1) && (get_buttons_pressed_from_player(temp_a0) & Z_TRIG)) {
                func_800C31EC(obj->unk78 & 0xFF);
            }
        }
    }
}

void obj_init_smoke(Object *obj, LevelObjectEntry_Smoke *entry) {
}

void obj_loop_smoke(Object *obj, s32 speed) {
    f32 temp_f2 = speed;
    if (osTvType == TV_TYPE_PAL) {
        temp_f2 *= 1.2;
    }
    obj->segment.trans.x_position += obj->segment.x_velocity * temp_f2;
    obj->segment.unk18 += speed * 16;
    obj->segment.trans.y_position += obj->segment.y_velocity * temp_f2;
    obj->segment.trans.z_position += obj->segment.z_velocity * temp_f2;
    if (obj->segment.unk18 >= 256) {
        gParticlePtrList_addObject(obj);
        obj->segment.unk18 = 255;
    }
}

void obj_init_unknown25(Object *obj, LevelObjectEntry_Unknown25 *entry) {
}

void obj_loop_unknown25(Object *obj, s32 speed) {
    obj->segment.unk18 += speed * 8;
    if (obj->segment.unk18 >= 256) {
        gParticlePtrList_addObject(obj);
        obj->segment.unk18 = 255;
    }
}

void obj_init_wardensmoke(Object *obj, LevelObjectEntry_WardenSmoke *entry) {
}

void obj_loop_wardensmoke(Object *obj, s32 speed) {
    f32 temp_f2;

    temp_f2 = (f32)speed;
    if (osTvType == TV_TYPE_PAL) {
        temp_f2 *= 1.2;
    }
    obj->segment.unk18 += speed * 4;
    obj->segment.trans.y_position += temp_f2 * 0.25;
    if (obj->segment.unk18 >= 256) {
        gParticlePtrList_addObject(obj);
        obj->segment.unk18 = 255;
    }
}

void obj_init_bombexplosion(Object *obj, LevelObjectEntry_BombExplosion *entry) {
    LevelObjectEntry_BombExplosion *entry2;
    obj->segment.unk18 = 0;
    obj->segment.trans.scale = 0.5f;
    obj->segment.unk3A = get_random_number_from_range(0, obj->segment.header->numberOfModelIds - 1);
    entry2 = entry; // Needed for a match.
    obj->unk78 = 0;
    obj->unk7C.word = 0xFF;
    if (entry->unk8) {
        obj->unk7C.word |= (entry2->unk8 << 8) & 0xFF00;
    }
    obj->unk74 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_bombexplosion.s")

void obj_init_teleport(Object *obj, LevelObjectEntry_Teleport *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0xF;
    obj->unk4C->unk12 = 0;
    if (get_settings()->cutsceneFlags & 1) {
        obj->unk78 = 1;
    }
}

void obj_loop_teleport(Object *obj, s32 speed) {
    if (obj->unk78 != 0) {
        Object_3C_80038DC4 *temp = obj->segment.unk3C_a.unk3C;
        if (obj->unk4C->unk13 < 0x78) {
            func_8006F338(temp->unk8);
            obj->unk78 = 0;
            func_80001D04(0x30, 0);
            func_80000FDC(0x12A, 0, 1.0f);
        }
    }
}

void obj_init_exit(Object *obj, LevelObjectEntry_Exit *entry) {
    f32 phi_f0;
    Object_64_80038E3C *obj64;
    phi_f0 = entry->unk10 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = obj->unk64;
    phi_f0 /= 128;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->unk11 << 6 << 4;
    obj64->unk0 = func_800707C4(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->segment.trans.y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->segment.trans.x_position) + (obj64->unk8 * obj->segment.trans.z_position));
    obj64->unk10 = entry->unk10;
    obj64->unk14 = entry->unk18;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->unk10;
    obj->unk4C->unk12 = 0;
}

void obj_loop_exit(Object *obj, s32 speed) {
    Object *racerObj;
    Object_64_Racer *racerObj64;
    s32 numberOfRacers;
    Settings *settings;
    f32 xDiff;
    f32 zDiff;
    f32 dist;
    f32 yDiff;
    Object_64_Exit *obj64;
    s32 someBool;
    Object** racerObjects;
    s32 i;
    f32 temp;

    obj64 = (Object_64_Exit*)obj->unk64;
    someBool = TRUE;
    settings = get_settings();
    if ((obj64->unk14 == 0) && (settings->balloonsPtr[settings->worldId] == 8)) {
        someBool = FALSE;
    }
    if ((obj64->unk14 == 1) && (settings->balloonsPtr[settings->worldId] < 8)) {
        someBool = FALSE;
    }
    if (someBool) {
        if (obj->unk4C->unk13 < obj64->unk10) {
            dist = obj64->unk10;
            racerObjects = get_object_struct_array(&numberOfRacers);
            for (i = 0; i < numberOfRacers; i++) {
                racerObj = racerObjects[i];
                racerObj64 = (Object_64_Racer*)racerObj->unk64;
                if ((racerObj64->unk0 != -1) && (racerObj64->unk108 == 0)) {
                    xDiff = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                    yDiff = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                    zDiff = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                    if ((sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < dist)) {
                        temp = (obj64->unk0 * racerObj->segment.trans.x_position) + (obj64->unk8 * racerObj->segment.trans.z_position) + obj64->unkC;
                        if (temp < 0.0f) {
                            racerObj64->unk108 = obj;
                            racerObj64->unk200 = -120;
                        }
                    }
                }
            }
        }
    }
}


void obj_init_cameracontrol(Object *obj, LevelObjectEntry_CameraControl *entry) {
    obj->unk78 = entry->unk8;
    func_80011390();
}

void obj_loop_cameracontrol(Object *obj, s32 speed) {
}

void obj_init_setuppoint(Object *obj, LevelObjectEntry_SetupPoint *entry) {
    s32 temp;
    obj->unk78 = entry->unk8;
    obj->unk7C.word = entry->unk9;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4; // Not sure about the values here.
}

void obj_loop_setuppoint(Object *obj, s32 speed) {
}

void obj_init_dino_whale(Object *obj, LevelObjectEntry_Dino_Whale *entry) {
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 3;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_loop_dino_whale(Object *obj, s32 speed) {
    s32 sp2C;

    if (obj->unk78 > 0) {
        obj->unk78 -= speed;
        speed *= 2;
    } else {
        obj->unk78 = 0;
    }
    sp2C = obj->segment.unk18;
    func_8001F460(obj, speed, obj);
    func_800113CC(obj, 0, sp2C, 0xAC, 0xAD);
    if (obj->unk4C->unk13 < 0xFF) {
        if (obj->unk78 == 0) {
            obj->unk78 = 0x3C;
            func_80009558(0x23B, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
        }
    }
}

void obj_init_parkwarden(Object *obj, LevelObjectEntry_Parkwarden *entry) {
    Object_64 *temp;
    obj->unk4C->unk14 = (u16)1;
    obj->unk4C->unk11 = (u8)0;
    obj->unk4C->unk10 = (u8)0x1E;
    obj->unk4C->unk12 = (u8)0;
    temp = obj->unk64;
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

void obj_loop_gbparkwarden(Object *obj, s32 speed) {
}

f32 func_8003ACAC(void) {
    return D_8011D4D0;
}

void obj_init_checkpoint(Object *obj, LevelObjectEntry_Checkpoint *entry, s32 arg2) {
    f32 phi_f0 = (s32)(entry->unk8 & 0xFF);
    if (phi_f0 < 5.0f) {
        phi_f0 = 5.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4; // Not sure about the values here.
    func_80011390();
}

void obj_loop_checkpoint(Object *obj, s32 speed) {
}

void obj_init_modechange(Object *obj, LevelObjectEntry_ModeChange *entry) {
    f32 phi_f0;
    Object_64_ModeChange *obj64;
    phi_f0 = entry->unk8 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = obj->unk64;
    phi_f0 /= 128;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->unk9 << 6 << 4;
    obj64->unk0 = func_800707C4(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->segment.trans.y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->segment.trans.x_position) + (obj64->unk8 * obj->segment.trans.z_position));
    obj64->unk10 = entry->unk8;
    obj64->unk14 = entry->unkA;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->unk8;
    obj->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_modechange.s")

void obj_init_bonus(Object *obj, LevelObjectEntry_Bonus *entry) {
    f32 phi_f0;
    Object_64_Bonus *obj64;
    phi_f0 = entry->unk8 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = obj->unk64;
    phi_f0 /= 128;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->unk9 << 6 << 4;
    obj64->unk0 = func_800707C4(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->segment.trans.y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->segment.trans.x_position) + (obj64->unk8 * obj->segment.trans.z_position));
    obj64->unk10 = entry->unk8;
    obj64->unk14 = entry->unkA;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->unk8;
    obj->unk4C->unk12 = 0;
}

void obj_loop_bonus(Object *obj, s32 speed) {
    Object *racerObj;
    Object_64_Racer *racerObj64;
    s32 numberOfRacers;
    f32 xDiff;
    f32 yDiff;
    f32 halfDist;
    f32 dist;
    f32 zDiff;
    Object_64_Bonus *obj64;
    Object **racerObjects;
    s32 i;

    obj64 = (Object_64_Bonus *)obj->unk64;
    if (obj->unk4C->unk13 < obj64->unk10) {
        dist = obj64->unk10;
        halfDist = dist * 0.5;
        racerObjects = get_object_struct_array(&numberOfRacers);
        for (i = 0; i < numberOfRacers; i++) {
            racerObj = racerObjects[i];
            racerObj64 = (Object_64_Racer *)racerObj->unk64;
            yDiff = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
            if ((yDiff < halfDist) && (-halfDist < yDiff)) {
                xDiff = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                zDiff = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < dist)) {
                    f32 temp = (obj64->unk0 * racerObj->segment.trans.x_position) + (obj64->unk8 * racerObj->segment.trans.z_position) + obj64->unkC;
                    if (temp < 0.0f) {
                        if ((s32) racerObj64->unk185 < 10) {
                            racerObj64->unk185 = 10;
                            func_80009558(34, racerObj->segment.trans.x_position, racerObj->segment.trans.y_position, racerObj->segment.trans.z_position, 4, NULL);
                            func_80001EA8(racerObj64->unk3 + 123, racerObj->segment.trans.x_position, racerObj->segment.trans.y_position, racerObj->segment.trans.z_position, NULL);
                        }
                    }
                }
            }
        }
    }
}
void obj_init_goldenballoon(Object *obj, LevelObjectEntry_GoldenBalloon *entry) {
    Object_64_GoldenBalloon *obj64;
    f32 scalef;

    if (entry->unk8 == -1) {
        entry->unk8 = func_8000CC20(obj);
    } else {
        func_8000CBF0(obj, entry->unk8);
    }
    if (entry->unk8 == -1) {
        rmonPrintf("Illegal door no!!!\n"); // Did the devs just copy-paste the door init function?
    }
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 4;
    obj->unk4C->unk10 = 20;
    obj->unk4C->unk12 = 0;
    scalef = entry->scale & 0xFF;
    if (scalef < 10.0f) {
        scalef = 10.0f;
    }
    scalef /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj64 = obj->unk64;
    obj64->unkD = 255;
    obj64->unk0 = 0.0f;
    obj->unk78 = 0;
    if (entry->unkA != 0) {
        if ((get_settings()->tajFlags & (1 << (entry->unkA + 2))) != 0) {
            obj->unk78 = 0;
        } else {
            obj->unk78 = 1;
        }
    }
}


#ifdef NON_EQUIVALENT

// Has regalloc issues.

void obj_loop_goldenballoon(Object *obj, s32 speed) {
    s32 padding[1];
    Object_3C *obj3C;
    Object_4C *obj4C;
    Object_64_GoldenBalloon *obj64;
    Settings *settings;
    s32 flag;
    s32 doubleSpeed;
    Object *racerObj;
    f32 sp2C;
    f32 speedf;
    s32 someBool;

    sp2C = speed;
    if (osTvType == TV_TYPE_PAL) {
        sp2C *= 1.2;
    }
    someBool = FALSE;
    if ((*(s32*)0xA0000284) != 0x240B17D7) {
        someBool = TRUE;
    }
    speedf = sp2C;
    settings = get_settings();
    obj3C = obj->unk3C_a.unk3C;
    flag = 0x10000 << obj3C->unk8;
    if (settings->courseFlagsPtr[settings->courseId] & flag) {
        if (obj->unk7C.word > 0) {
            obj->unk74 = 2;
            func_800AFC3C(obj, speed);
            obj->unk7C.word -= speed;
        } else {
            gParticlePtrList_addObject(obj);
        }
    } else {
        obj->segment.trans.unk6 |= 0x4000;
        if (obj->unk78 == 0) {
            obj->segment.trans.unk6 &= 0xBFFF;
            doubleSpeed = speed * 2;
            if (obj->unk38.half.lower < (255 - doubleSpeed)) {
                obj->unk38.half.lower += doubleSpeed;
            } else {
                obj->unk38.half.lower = 255;
            }
            obj4C = obj->unk4C;
            if ((obj4C->unk13 < 45) && (someBool == FALSE)) {
                racerObj = obj4C->unk0;
                if (racerObj && (racerObj->header->behaviorId == 1) && (((Object_64_Racer *)racerObj->unk64)->unk0 == 0)) {
                    settings->balloonsPtr[settings->worldId]++;
                    if (settings->worldId != 0) {
                        settings->balloonsPtr[0]++;
                    }
                    settings->courseFlagsPtr[settings->courseId] |= flag;
                    func_80001EA8(573, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
                    obj->unk7C.word = 16;
                    obj->unk74 = 2;
                    obj->segment.trans.unk6 |= 0x4000;
                    func_800AFC3C(obj, speed);
                }
            }
            obj64 = (Object_64_GoldenBalloon *)obj->unk64;
            obj->unk3B = 0;
            obj64->unk14 = 0.0f;
            if (obj->unk38.half.lower < 255) {
                speedf = 0.0f;
            } else {
                speedf = 1.0f;
            }
            if (obj64->unkD == 255) {
                obj64->unkD = func_8001C524(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0);
                if (obj64->unkD != 255) {
                    obj64->unkE = func_8001CC48(obj64->unkD, -1, 0);
                    obj64->unkF = func_8001CC48(obj64->unkE, obj64->unkD, 0);
                    obj64->unk10 = func_8001CC48(obj64->unkF, obj64->unkE, 0);
                    obj64->unkC = obj64->unkD;
                }
            } else {
                func_8001C6C4(obj64, obj, sp2C, speedf, 0);
            }
        }
    }
}


#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_goldenballoon.s")
#endif

void obj_init_door(Object *obj, LevelObjectEntry_Door *entry) {
    Object_64_Door *obj64;
    f32 phi_f0;

    obj64 = (Object_64_Door *)obj->unk64;
    if (entry->unkC == -1) {
        entry->unkC = func_8000CC20(obj);
    } else {
        func_8000CBF0(obj, entry->unkC);
    }
    obj64->unkE = entry->unkC;
    obj64->unkF = entry->unkE;
    obj64->unk11 = entry->numBalloonsToOpen;
    obj64->unk10 = entry->numBalloonsToOpen;
    obj64->unk12 = entry->distanceToOpen;
    if (obj64->unkE == -1) {
        rmonPrintf("Illegal door no!!!\n");
    }
    obj->segment.unk3A = entry->modelIndex;
    obj->segment.trans.y_rotation = entry->closedRotation << 6 << 4;
    obj64->unk0 = obj->segment.trans.y_position;
    obj64->unk8 = 0;
    obj->unk78 = obj->segment.trans.y_rotation;
    obj->unk7C.word = (s32) ((entry->openRotation & 0x3F) << 10);
    phi_f0 = entry->scale & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj64->unk13 = (u8) entry->unkF;
    obj64->unk14 = (s8) entry->unk11;
    obj->unk4C->unk14 = 0x21;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_door.s")

void obj_init_ttdoor(Object *obj, LevelObjectEntry_TTDoor *entry) {
    f32 temp_f0;
    Object_64_8003C1E0 *obj64;
    f32 phi_f0;

    obj->segment.unk3A = 0;
    obj64 = obj->unk64;
    obj->segment.trans.y_rotation = entry->unk8 << 6 << 4;
    obj64->unkF = entry->unkE;
    obj64->unk13 = entry->unkB;
    obj64->unk0 = obj->segment.trans.y_position;
    obj64->unk8 = 0;
    obj64->unk12 = entry->unkA;
    obj->unk78 = obj->segment.trans.y_rotation;
    obj->unk7C.word = (entry->unk9 & 0x3F) << 0xA;
    phi_f0 = entry->unkC & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->unk4C->unk14 = 0x21;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_ttdoor.s")
void obj_init_trigger(Object *obj, LevelObjectEntry_Trigger *entry) {
    f32 phi_f0;
    Object_64_Trigger *obj64;

    if (entry->unk9 == -1) {
        entry->unk9 = func_8000CC20(obj);
    } else {
        func_8000CBF0(obj, entry->unk9);
    }
    if (entry->unk9 == -1) {
        rmonPrintf("Illegal door no!!!\n");
    }
    phi_f0 = (s32)entry->scale & 0xFF;
    if (phi_f0 < 5.0f) {
        phi_f0 = 5.0f;
    }
    obj64 = (Object_64_Trigger*)obj->unk64;
    phi_f0 /= 128;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->rotation << 6 << 4;
    obj64->unk0 = func_800707C4(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = func_800707F8(obj->segment.trans.y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->segment.trans.x_position) + (obj64->unk8 * obj->segment.trans.z_position));
    obj64->unk10 = entry->scale;
    obj64->unk14 = entry->unkD;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->scale;
    obj->unk4C->unk12 = 0;
}


GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_trigger.s")

void obj_init_bridge_whaleramp(Object *obj, LevelObjectEntry_Bridge_WhaleRamp *entry) {
    Object_64 *temp = obj->unk64;
    obj->segment.unk3A = entry->unk8;
    obj->segment.trans.y_rotation = entry->unk9 << 6 << 4;
    temp->unk0_a.unk0 = obj->segment.trans.y_position;
    obj->unk4C->unk14 = 0x21;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    temp->unk4 = 0;
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_bridge_whaleramp.s")

void obj_init_rampswitch(Object *obj, LevelObjectEntry_RampSwitch *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    obj->unk78 = entry->unk8;
}

void obj_loop_rampswitch(Object *obj, s32 speed) {
    if (obj->unk4C->unk13 < 0x2D) {
        func_8001E344(obj->unk78);
    }
    obj->unk4C->unk13 = (u8)0xFF;
}

void obj_init_seamonster(Object *obj, LevelObjectEntry_SeaMonster *entry) {
}

void obj_loop_seamonster(Object *obj, s32 speed) {
}

void obj_init_fogchanger(Object *obj, LevelObjectEntry_FogChanger *entry) {
    f32 temp_f0;
    temp_f0 = entry->unk8 * 8.0f;
    temp_f0 = temp_f0 * temp_f0;
    obj->unk78f = temp_f0;
}

void obj_init_skycontrol(Object *obj, LevelObjectEntry_SkyControl *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->unk9;
    obj->unk78 = entry->unk8;
    obj->unk7C.word = entry->unk9;
}

void obj_loop_skycontrol(Object *obj, s32 speed) {
    if (obj->unk4C->unk13 < obj->unk7C.word) {
        func_80028044(obj->unk78);
    }
}

void obj_init_ainode(Object *obj, LevelObjectEntry_AiNode *entry) {
    if (entry->unk9 == 0xFF) {
        entry->unk9 = func_8001C48C(obj) & 0xFF;
    }
    func_8001D1BC(entry->unk9);
    func_8001D1AC();
}

void obj_loop_ainode(Object *obj, s32 speed) {
}

void obj_init_treasuresucker(Object *obj, LevelObjectEntry_TreasureSucker *entry) {
    obj->segment.unk18 = 0x78;
    obj->unk78 = (entry->unk8 - 1) & 3;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_treasuresucker.s")

void obj_init_flycoin(Object *obj, LevelObjectEntry_FlyCoin *entry) {
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_flycoin.s")

void obj_init_bananacreator(Object *obj, LevelObjectEntry_BananaCreator *entry) {
    obj->segment.unk18 = 100;
}

void obj_loop_bananacreator(Object *obj, s32 speed) {
  LevelObjectEntryCommon newEntry;
  Object *newBananaObj;
  Object_64_Banana *newBananaObj64;

  if (obj->unk7C.word != 0) {
    obj->unk78 -= speed;
  }

  if (obj->unk78 <= 0) {
    newEntry.x = (s32) obj->segment.trans.x_position;
    newEntry.y = ((s32) ((s16) obj->segment.trans.y_position)) - 3;
    newEntry.z = (s32) obj->segment.trans.z_position;
    newEntry.size = 8;
    newEntry.object_id = 83;
    newBananaObj = spawn_object(&newEntry, 1);
    obj->unk7C.word = 1;
    if (newBananaObj) {
      newBananaObj->segment.unk3C_a.unk3C = 0;
      newBananaObj64 = (Object_64_Banana *) newBananaObj->unk64;
      newBananaObj64->spawner = obj;
      func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position - 14.0f, obj->segment.trans.z_position, 44, 34, 0.25f, 0);
      obj->unk7C.word = 0;
    }
    obj->unk78 = TIME_SECONDS(20); // Set delay to respawn banana to 20 seconds.
  }
}


void obj_init_banana(Object *obj, LevelObjectEntry_Banana *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk7C.half.upper = 0x14;
    obj->unk7C.half.lower = 0x10;
    if (get_filtered_cheats() & CHEAT_DISABLE_BANANAS) {
        gParticlePtrList_addObject(obj);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_banana.s")

void obj_init_silvercoin_adv2(Object *obj, LevelObjectEntry_SilverCoinAdv2 *entry) {
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
        obj->segment.trans.unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

void obj_init_silvercoin(Object *obj, LevelObjectEntry_SilverCoin *entry) {
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
        obj->segment.trans.unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_silvercoin.s")

void obj_init_worldkey(Object *obj, LevelObjectEntry_WorldKey *entry) {
    Settings *settings;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    entry->unk8 &= 0xF;
    obj->unk78 = entry->unk8;
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
            if (playerObj->segment.header->behaviorId == 1) { // Is the player a racer?
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
    worldKeyObj->segment.trans.y_rotation += speed * 256;
}

typedef struct Object_64_8003DFCC {
    f32 unk0;
    s16 unk4;
    s8 unk6[0x2];
} Object_64_8003DFCC;

void obj_init_weaponballoon(Object *obj, LevelObjectEntry_WeaponBalloon *entry) {
    s32 cheats;
    Object_64_8003DFCC *obj64;
    f32 scalef;

    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 4;
    obj->unk4C->unk10 = 0x14;

    cheats = get_filtered_cheats();

    if (cheats & CHEAT_ALL_BALLOONS_ARE_BLUE) {
        entry->balloonType = BALLOON_TYPE_BOOST;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_RED) {
        entry->balloonType = BALLOON_TYPE_MISSILE;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_GREEN) {
        entry->balloonType = BALLOON_TYPE_TRAP;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_YELLOW) {
        entry->balloonType = BALLOON_TYPE_SHIELD;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_RAINBOW) {
        entry->balloonType = BALLOON_TYPE_MAGNET;
    }

    // I guess unk8 is unused?
    if (entry->unk8 >= 6) {
        entry->unk8 = 0;
    }

    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }

    obj->segment.unk3A = entry->balloonType;
    obj->unk78 = obj->segment.unk3A;

    scalef = entry->scale & 0xFF;
    if (scalef < 10) {
        scalef = 10;
    }
    scalef /= 64;

    obj64 = (Object_64_8003DFCC*)obj->unk64;

    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj64->unk0 = obj->segment.trans.scale;
    obj64->unk4 = 0;
    obj->unk7C.word = 0;

    if (get_filtered_cheats() & CHEAT_DISABLE_WEAPONS) {
        gParticlePtrList_addObject(obj);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_weaponballoon.s")

void obj_init_wballoonpop(Object *obj, LevelObjectEntry_WBalloonPop *entry) {
}

void obj_loop_wballoonpop(Object *obj, s32 speed) {
}

void obj_init_weapon(Object *obj, LevelObjectEntry_Weapon *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x18;
    obj->unk4C->unk12 = 0;
    obj->unk78 = func_8000C8B4(0x1E0);
    obj->unk7C.word = 0;
}

void obj_loop_weapon(Object *obj, s32 speed) {
    Object_64 *obj64 = obj->unk64;
    switch (obj64->unk18) {
        case 0:
        case 1:
            func_8003E694(obj, speed);
            break;
        case 2:
        case 3:
        case 10:
        case 11:
            func_8003F2E8(obj, speed);
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
    someObj = spawn_object(&sp24, 1);
    if (someObj != NULL) {
        someObj->segment.trans.scale *= 3.5 * arg5;
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

void obj_init_audio(Object *obj, LevelObjectEntry_Audio *entry) {
    Object_64_Audio *obj64;

    obj64 = (Object_64_Audio*)obj->unk64;
    obj64->unk0 = entry->unk8;
    obj64->unk2 = entry->unkA;
    obj64->unkC = entry->unkF;
    obj64->unk6 = entry->unkE;
    obj64->unk4 = entry->unkC;
    obj64->unk5 = entry->unkD;
    obj64->unkD = entry->unk10;
    obj64->unk8 = 0;
    if (ALBankFile_80115D14_GetSoundDecayTime(obj64->unk0)) {
        func_8000974C(obj64->unk0, entry->common.x, entry->common.y, entry->common.z,
            9, obj64->unk5, obj64->unk4, obj64->unk2, obj64->unkC, 
            obj64->unk6, obj64->unkD, &obj64->unk8);
    } else {
        func_8000974C(obj64->unk0, entry->common.x, entry->common.y, entry->common.z, 
            10, obj64->unk5, obj64->unk4, obj64->unk2, obj64->unkC, 
            obj64->unk6, obj64->unkD, &obj64->unk8);
    }
    gParticlePtrList_addObject(obj);
}

void obj_init_audioline(Object *obj, LevelObjectEntry_AudioLine *entry) {
    Object_64_8003FEF4 *obj64;

    obj64 = obj->unk64;
    obj64->unk0 = entry->unk8;
    obj64->unk2 = entry->unkA;
    obj64->unkC = entry->unkC;
    obj64->unkD = entry->unkD;
    obj64->unk_union.unk8_word = 0;
    obj64->unk4 = entry->unkE;
    obj64->unk11 = entry->unk12;
    obj64->unk10 = entry->unk11;
    obj64->unkE = entry->unk9;
    obj64->unkF = entry->unk10;
    obj64->unk12 = entry->unk13;
    func_800098A4(obj64->unk0, obj64->unk2, entry->common.x, entry->common.y, entry->common.z,
                  obj64->unkF, obj64->unkE, obj64->unk10, obj64->unk12, obj64->unk4, obj64->unk11,
                  obj64->unkC, obj64->unkD);
    gParticlePtrList_addObject(obj);
}

void obj_init_audioreverb(Object *obj, LevelObjectEntry_AudioReverb *entry) {
    s32 temp;
    Object_64_8004001C *obj64 = (Object_64_8004001C *)obj->unk64;
    obj64->unk2 = entry->unk8;
    temp = entry->unk9;
    obj64->unk4 = temp & 0xFF;
    obj64->unk5 = entry->unkA;
    func_80009968(entry->common.x, entry->common.y, entry->common.z, obj64->unk2, obj64->unk4, obj64->unk5);
    gParticlePtrList_addObject(obj);
}

void obj_init_texscroll(Object *obj, LevelObjectEntry_TexScroll *entry, s32 arg2) {
    Object_64_800400A4 *obj64;
    LevelModel *levelModel;
    s16 numberOfTexturesInLevel;

    obj64 = obj->unk64;
    levelModel = func_8002C7C4();
    obj64->unk0 = entry->unk8;
    if (obj64->unk0 < 0) {
        obj64->unk0 = 0;
    }
    numberOfTexturesInLevel = levelModel->numberOfTextures;
    if (obj64->unk0 >= numberOfTexturesInLevel) {
        obj64->unk0 = numberOfTexturesInLevel - 1;
    }
    obj64->unk4 = (s16)entry->unkA;
    obj64->unk6 = (s16)entry->unkB;
    if (arg2 == 0) {
        obj64->unk8 = 0;
        obj64->unkA = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_texscroll.s")

void obj_init_rgbalight(Object *obj, LevelObjectEntry_RgbaLight *entry, s32 arg2) {
    obj->unk64 = func_80031CAC(obj, entry);
}

void obj_init_buoy_pirateship(Object *obj, LevelObjectEntry_Buoy_PirateShip *entry, s32 arg2) {
    obj->unk64 = func_800BE654(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position);
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk4C->unk12 = 0;
}

void obj_loop_buoy_pirateship(Object *obj, s32 speed) {
    if (obj->unk64 != NULL) {
        obj->segment.trans.y_position = func_800BEEB4(obj->unk64);
    }
    obj->segment.unk18 += speed * 8;
}

void obj_init_log(Object *obj, LevelObjectEntry_Log *entry, s32 arg2) {
    f32 phi_f0;
    obj->unk64 = func_800BE654(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position);
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x1E;
    phi_f0 = entry->unk9 & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->segment.unk3A = entry->unk8;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_log.s")

void obj_init_weather(Object *obj, LevelObjectEntry_Weather *entry) {
    f32 temp = entry->unk8;
    temp *= temp;
    obj->unk78f = temp;
}


#ifdef NON_EQUIVALENT
void func_800ABC5C(s32, s32, s32, s32, s32, s32); /* extern */

typedef struct Object_3C_Weather {
    u8 pad0[0x2];
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s8 unk8;
    u8 unk9;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 unk10;
    u8 unk11;
    s16 unk12;
} Object_3C_Weather;

// Has stack & regalloc issues.
void obj_loop_weather(Object *obj, s32 speed) {
  s32 sp54;
  s32 numberOfObjects;
  Object_64_Racer *curObj64;
  Object **objects;
  Object **lastObj;
  Object *curObj;
  Object_3C_Weather *obj3c;
  f32 temp_f0;
  f32 new_var;
  f32 temp_f2;
  s32 i;
  s32 temp[3];
  sp54 = func_80066220();
  objects = get_object_struct_array(&numberOfObjects);
  if (numberOfObjects != 0) {
    lastObj = &objects[numberOfObjects - 1];
    objects--;
    do {
      curObj = objects[1];
      curObj64 = (Object_64_Racer *) curObj->unk64;
    } while (((++objects) < lastObj) && (sp54 != curObj64->unk0));
    temp_f0 = obj->segment.trans.x_position - curObj->segment.trans.x_position;
    temp_f2 = obj->segment.trans.z_position - curObj->segment.trans.z_position;
    new_var = obj->unk78f;
    obj3c = obj->unk3C_a.unk3C;
    if (((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) <= (new_var * 1.0f)){
      func_800ABC5C(obj3c->unkA * 256, obj3c->unkC * 256, obj3c->unkE * 256, obj3c->unk10 * 257, obj3c->unk11 * 257, (s32) obj3c->unk12);
    }
  }
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_weather.s")
#endif

void obj_init_lensflare(Object *obj, LevelObjectEntry_LensFlare *entry) {
    func_800AC8A8(obj);
}

void obj_init_lensflareswitch(Object *obj, LevelObjectEntry_LensFlareSwitch *entry, s32 arg2) {
    func_800ACF60(obj);
    obj->segment.trans.scale = entry->unk8;
    obj->segment.trans.scale /= 40.0f;
}

void obj_init_wavegenerator(Object *obj, LevelObjectEntry_WaveGenerator *entry, s32 arg2) {
    func_800BF524(obj); //waves.c
}

#ifdef NON_EQUIVALENT

typedef struct Object_64_Butterfly {
/* 0x00  */ Triangle triangles[8];
/* 0x80  */ Vertex vertices[12];
/* 0xF8  */ TextureHeader *texture;
/* 0xFC  */ u8 unkFC;
/* 0xFD  */ u8 unkFD;
/* 0xFE  */ u8 unkFE;
/* 0xFF  */ u8 unkFF;
/* 0x100 */ s32 unk100;
/* 0x104 */ s16 unk104;
/* 0x106 */ s16 unk106;
/* 0x108 */ f32 unk108;
} Object_64_Butterfly;

void obj_init_butterfly(Object *obj, LevelObjectEntry_Butterfly *entry, s32 arg2) {
    Object_64_Butterfly *obj64;
    s32 i, j;
    s32 uMask, vMask;

    obj64 = (Object_64_Butterfly*)obj->unk64;
    if (arg2 == 0) {
        obj->y_velocity = 0.0f;
        obj64->unkFE = 0;
        obj64->unk100 = 0;
        obj64->unk104 = 0;
        obj64->unkFD = 0;
        obj64->unk106 = 384;
        obj64->unk108 = 0.0f;
        // This loop is okay
        for(i = 0; i < 8; i++) {
            obj64->triangles[i].drawBackface = D_800DCAA8[i].drawBackface;
            obj64->triangles[i].vi0 = D_800DCAA8[i].vi0;
            obj64->triangles[i].vi1 = D_800DCAA8[i].vi1;
            obj64->triangles[i].vi2 = D_800DCAA8[i].vi2;
        }
        // This loop is not.
        for(i = 0; i < 6; i++) {
            //u32 j = i + 6;
            obj64->vertices[i].x = D_800DCB28[i].x;
            obj64->vertices[i].y = D_800DCB28[i+1].y;
            obj64->vertices[i].z = D_800DCB28[i+1].z;
            obj64->vertices[i].r = 255;
            obj64->vertices[i].g = 255;
            obj64->vertices[i].b = 255;
            obj64->vertices[i].a = 255;
            obj64->vertices[(u32)(i+6)].x = D_800DCB28[i+1].x;
            obj64->vertices[i+6].y = D_800DCB28[i].y;
            obj64->vertices[i+6].z = D_800DCB28[i].z;
            obj64->vertices[i+6].r = 255;
            obj64->vertices[i+6].g = 255;
            obj64->vertices[i+6].b = 255;
            obj64->vertices[i+6].a = 255;
        }
        obj64->unkFC = 1;
    }
    obj->segment.trans.scale = entry->unkB * 0.01f;
    if (entry->unkA < obj->header->numberOfModelIds) {
        obj64->texture = (TextureHeader*)obj->unk68[entry->unkA];
    } else {
        obj64->texture = (TextureHeader*)obj->unk68[0];
    }
    
    if (obj64->texture) {
        uMask = (obj64->texture->width - 1) << 5;
        vMask = (obj64->texture->height - 1) << 5;
    } else {
        uMask = 0;
        vMask = 0;
    }
    for(i = 0; i < 8; i++) {
        obj64->triangles[i].uv0.u = D_800DCAA8[i].uv0.u & uMask;
        obj64->triangles[i].uv0.v = D_800DCAA8[i].uv0.v & vMask;
        obj64->triangles[i].uv1.u = D_800DCAA8[i].uv1.u & uMask;
        obj64->triangles[i].uv1.v = D_800DCAA8[i].uv1.v & vMask;
        obj64->triangles[i].uv2.u = D_800DCAA8[i].uv2.u & uMask;
        obj64->triangles[i].uv2.v = D_800DCAA8[i].uv2.v & vMask;
    }
}


#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_butterfly.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_butterfly.s")

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_midifade.s")

void obj_init_midifadepoint(Object *obj, LevelObjectEntry_MidiFadePoint *entry) {
  Object_64_MidiFadePoint *obj64;
  ObjectModel **models;
  ObjectModel *objModel;
  Vertex *vertex;
  s32 i;
  f32 x;
  f32 y;
  f32 z;
  f32 dist;

  obj64 = (LevelObjectEntry_MidiFadePoint *) obj->unk64;
  obj64->unk2 = entry->unkA;
  obj64->unk0 = entry->unk8;
  obj64->unk1C = entry->unk1C;
  if (obj64->unk2 < obj64->unk0) {
    obj64->unk2 = obj64->unk0 + 10;
  }
  obj->segment.trans.z_rotation = 0;
  obj->segment.trans.x_rotation = 0;
  obj->segment.trans.y_rotation = 0;

  for (i = 0; i < 15; i++) {
    obj64->unkC[i] = entry->unkC[i];
  }

  models = *((ObjectModel ***) obj->unk68);
  objModel = models[0];
  vertex = objModel->vertices + 1;
  x = vertex->x;
  y = vertex->y;
  z = vertex->z;
  dist = sqrtf(((x * x) + (y * y)) + (z * z));
  obj64->unk4 = entry->unk8 / dist;
  obj64->unk8 = entry->unkA / dist;
  obj->segment.trans.scale = obj64->unk8;
}

void obj_init_midichset(Object *obj, LevelObjectEntry_Midichset *entry) {
    unk80042014_arg0_64 *temp = obj->unk64;
    temp->unk0 = entry->unk8;
    temp->unk2 = entry->unkA;
    temp->unk3 = entry->unkB;
}

void obj_init_bubbler(Object *obj, LevelObjectEntry_Bubbler *entry) {
    func_800AF134(obj->unk6C, entry->unk9, entry->unk8, 0, 0, 0);
    obj->unk78 = entry->unkA;
}

void obj_loop_bubbler(Object *obj, s32 speed) {
    if (obj->unk78 >= get_random_number_from_range(0, 0x400)) {
        obj->unk74 = 1;
    } else {
        obj->unk74 = 0;
    }
    if (get_number_of_active_players() < 2) {
        func_800AFC3C(obj, speed);
    }
}

void obj_init_boost(Object *obj, LevelObjectEntry_Boost *entry) {
    obj->unk64 = (s32)get_misc_asset(0x14) + (entry->unk8[0] << 7);
    obj->segment.unk3C_a.unk3C = NULL;
}

void obj_init_unknown94(Object *obj, LevelObjectEntry_Unknown94 *entry, s32 arg2) {
}

void obj_loop_unknown94(Object *obj, s32 speed) {
}

void obj_init_rangetrigger(Object *obj, LevelObjectEntry_RangeTrigger *entry) {
}

void obj_loop_rangetrigger(Object *obj, s32 speed) {
    s32 temp;
    Object_3C_80042178 *obj3C;
    unk80042178 sp20;

    obj3C = obj->segment.unk3C_a.unk3C;
    if (func_80016DE8(obj->segment.trans.x_position, 0, obj->segment.trans.z_position, (f32)obj3C->unk8, 1, &sp20) > 0) {
        obj->unk74 = obj3C->unkA;
    } else {
        obj->unk74 = 0;
    }
    func_800AFC3C(obj, speed);
}

void obj_init_frog(Object *obj, LevelObjectEntry_Frog *entry) {
    Object_64_80042210 *obj64;

    obj64 = (Object_64_80042210 *)obj->unk64;
    obj64->unk15 = entry->unkA;
    obj64->unk0 = obj->segment.trans.x_position;
    obj64->unk4 = obj->segment.trans.y_position;
    obj64->unk8 = obj->segment.trans.z_position;
    obj64->unkC = entry->unk8;
    obj64->unk10 = obj64->unkC * obj64->unkC;
    obj64->unk14 = 0;
    obj64->unk20 = obj->segment.trans.x_position;
    obj64->unk24 = obj->segment.trans.z_position;
    obj64->unk19 = 0;
    obj64->unk30 = 1.0f;

    if (obj64->unk15) {
        obj->segment.unk3A = 1;
        /**
          * Don't spawn the chicken frog if drumstick is already unlocked, or 
          * if the player hasn't completed the trophy races yet.
          */
        if (is_drumstick_unlocked() || (get_settings()->trophies & 0xFF) != 0xFF) {
            gParticlePtrList_addObject(obj);
        }
    } else {
        obj->segment.unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_frog.s")

void obj_loop_pigrocketeer(Object *obj, s32 speed) {
    Object *someObj;
    Object_64_80042998 *obj64;

    func_8001F460(obj, speed, obj);
    someObj = func_8000BF44(-1);

    if (someObj != NULL) {
        obj64 = someObj->unk64;
        someObj->unk78 = 0;
        if (obj64 != 0) {
            obj64->unk72 += speed;
            obj64->unk70 = 2;
            obj64->unk74 = 1.0f;
            func_8000B750(obj, -1, 2, 1, 1);
        }
    }
}

void obj_init_levelname(Object *obj, LevelObjectEntry_LevelName *entry) {
    obj->unk78f = entry->unk9 * 8.0f;
    obj->unk78f *= obj->unk78f;
    obj->unk7C.half.upper = entry->unk8;
    obj->unk7C.half.lower = 0;
    if (is_in_tracks_mode()) {
        gParticlePtrList_addObject(obj);
    }
    func_800C56D0(4);
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_levelname.s")

void obj_loop_wizghosts(Object *obj, s32 speed) {
    func_8001F460(obj, speed, obj);
    obj->segment.unk18 = (obj->segment.unk18 + (speed * 8)) & 0xFF;
}

