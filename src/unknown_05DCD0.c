/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005D820 */

#include "unknown_05DCD0.h"

#include "types.h"
#include "macros.h"
#include "math_util.h"
#include "objects.h"
#include "object_functions.h"
#include "unknown_008C40.h"
#include "racer.h"
#include "unknown_05CEF0.h"
#include "particles.h"

/************ .bss ************/

s8 D_8011D5E0;
s8 D_8011D5E1;

/******************************/
GLOBAL_ASM("asm/non_matchings/unknown_05DCD0/func_8005D820.s")

void func_8005E204(Object *obj, Object_Racer *racer, f32 arg2, s32 objectID, s32 arg4) {
    Object** var_s6;
    s32 sp80;
    s32 sp7C;
    LevelObjectEntry* temp_s2;
    Object* temp_s1;
    Object* newObj;
    s32 i;
    LevelObjectEntryCommon spawnObj;
    f32 xDiff;
    f32 zDiff;
    f32 yDiff;

    var_s6 = func_8000E988(&sp80, &sp7C);
    spawnObj.objectID = objectID;
    spawnObj.size = (((objectID & 0x100) & 0xFFFF) >> 1) | 8;
    spawnObj.x = obj->segment.trans.x_position - (racer->ox1 * arg2);
    spawnObj.y = obj->segment.trans.y_position - (racer->oy1 * arg2);
    spawnObj.z = obj->segment.trans.z_position - (racer->oz1 * arg2);
    
    for (i = 0; i < sp7C; i++) {
        temp_s1 = var_s6[i];
        if (temp_s1->behaviorId == BHV_UNK_6B) {
            temp_s2 = temp_s1->segment.unk3C_a.level_entry; 
            if ((s8) temp_s2->animation.z_rotation == racer->lap + 1 || (s8) temp_s2->animation.z_rotation == 0) {
                xDiff = temp_s1->segment.trans.x_position - obj->segment.trans.x_position;
                yDiff = temp_s1->segment.trans.y_position - obj->segment.trans.y_position;
                zDiff = temp_s1->segment.trans.z_position - obj->segment.trans.z_position;
                if (sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < (f32) ((s8) temp_s2->animation.x_rotation & 0xFF) * 4.0) {
                    if (temp_s1->unk78 == 0) {
                        temp_s1->unk78 = 1;
                        newObj = spawn_object(&spawnObj, 1);
                        if (newObj != NULL) {
                            newObj->segment.unk3C_a.level_entry = NULL;
                            newObj->segment.x_velocity = obj->segment.x_velocity;
                            newObj->segment.y_velocity = obj->segment.y_velocity;
                            newObj->segment.z_velocity = obj->segment.z_velocity;
                            newObj->unk78_obj = temp_s1;
                            newObj->unk7C.word = (s8) temp_s2->animation.y_rotation * 60;
                            newObj->segment.animFrame = get_random_number_from_range(0, 255);
                            func_80009558(arg4, newObj->segment.trans.x_position, newObj->segment.trans.y_position, newObj->segment.trans.z_position, 4, NULL);
                        }
                    }
                } else {
                    temp_s1->unk78 = 0;
                }
            }
        }
    }
}
