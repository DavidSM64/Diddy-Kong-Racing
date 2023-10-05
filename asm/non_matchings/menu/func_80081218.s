glabel func_80081218
/* 081E18 80081218 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 081E1C 8008121C AFBF0014 */  sw    $ra, 0x14($sp)
/* 081E20 80081220 27A40034 */  addiu $a0, $sp, 0x34
/* 081E24 80081224 0C01AC89 */  jal   get_number_of_levels_and_worlds
/* 081E28 80081228 27A50030 */   addiu $a1, $sp, 0x30
/* 081E2C 8008122C 8FA20034 */  lw    $v0, 0x34($sp)
/* 081E30 80081230 8FAF0030 */  lw    $t7, 0x30($sp)
/* 081E34 80081234 00027080 */  sll   $t6, $v0, 2
/* 081E38 80081238 000FC040 */  sll   $t8, $t7, 1
/* 081E3C 8008123C 01D81821 */  addu  $v1, $t6, $t8
/* 081E40 80081240 2463011B */  addiu $v1, $v1, 0x11b
/* 081E44 80081244 2401FFFC */  li    $at, -4
/* 081E48 80081248 0061C824 */  and   $t9, $v1, $at
/* 081E4C 8008124C 00192080 */  sll   $a0, $t9, 2
/* 081E50 80081250 AFB90020 */  sw    $t9, 0x20($sp)
/* 081E54 80081254 AFAE0028 */  sw    $t6, 0x28($sp)
/* 081E58 80081258 0C01C327 */  jal   allocate_from_main_pool_safe
/* 081E5C 8008125C 2405FFFF */   li    $a1, -1
/* 081E60 80081260 3C048012 */  lui   $a0, %hi(gSavefileData) # $a0, 0x8012
/* 081E64 80081264 24846530 */  addiu $a0, %lo(gSavefileData) # addiu $a0, $a0, 0x6530
/* 081E68 80081268 AC820000 */  sw    $v0, ($a0)
/* 081E6C 8008126C 3C018012 */  lui   $at, %hi(gSavefileData+4) # $at, 0x8012
/* 081E70 80081270 AC226530 */  sw    $v0, %lo(gSavefileData)($at)
/* 081E74 80081274 3C098012 */  lui   $t1, %hi(gSavefileData) # $t1, 0x8012
/* 081E78 80081278 8D296530 */  lw    $t1, %lo(gSavefileData)($t1)
/* 081E7C 8008127C 8FA60028 */  lw    $a2, 0x28($sp)
/* 081E80 80081280 8FA70020 */  lw    $a3, 0x20($sp)
/* 081E84 80081284 252A0118 */  addiu $t2, $t1, 0x118
/* 081E88 80081288 3C0B8012 */  lui   $t3, %hi(gSavefileData) # $t3, 0x8012
/* 081E8C 8008128C AD2A0004 */  sw    $t2, 4($t1)
/* 081E90 80081290 8D6B6530 */  lw    $t3, %lo(gSavefileData)($t3)
/* 081E94 80081294 3C188012 */  lui   $t8, %hi(gSavefileData+4) # $t8, 0x8012
/* 081E98 80081298 8D6C0004 */  lw    $t4, 4($t3)
/* 081E9C 8008129C 3C088012 */  lui   $t0, %hi(gSavefileData+4) # $t0, 0x8012
/* 081EA0 800812A0 01866821 */  addu  $t5, $t4, $a2
/* 081EA4 800812A4 AD6D0000 */  sw    $t5, ($t3)
/* 081EA8 800812A8 8C8E0000 */  lw    $t6, ($a0)
/* 081EAC 800812AC 00E71821 */  addu  $v1, $a3, $a3
/* 081EB0 800812B0 01C77821 */  addu  $t7, $t6, $a3
/* 081EB4 800812B4 AC2F6534 */  sw    $t7, %lo(gSavefileData+4)($at)
/* 081EB8 800812B8 8F186534 */  lw    $t8, %lo(gSavefileData+4)($t8)
/* 081EBC 800812BC 3C018012 */  lui   $at, %hi(gSavefileData+12) # $at, 0x8012
/* 081EC0 800812C0 27190118 */  addiu $t9, $t8, 0x118
/* 081EC4 800812C4 AF190004 */  sw    $t9, 4($t8)
/* 081EC8 800812C8 8D086534 */  lw    $t0, %lo(gSavefileData+4)($t0)
/* 081ECC 800812CC 3C0B8012 */  lui   $t3, %hi(gSavefileData+8) # $t3, 0x8012
/* 081ED0 800812D0 8D0A0004 */  lw    $t2, 4($t0)
/* 081ED4 800812D4 3C0F8012 */  lui   $t7, %hi(gSavefileData+8) # $t7, 0x8012
/* 081ED8 800812D8 01464821 */  addu  $t1, $t2, $a2
/* 081EDC 800812DC AD090000 */  sw    $t1, ($t0)
/* 081EE0 800812E0 8C8C0000 */  lw    $t4, ($a0)
/* 081EE4 800812E4 3C088012 */  lui   $t0, %hi(gSavefileData+12) # $t0, 0x8012
/* 081EE8 800812E8 01836821 */  addu  $t5, $t4, $v1
/* 081EEC 800812EC AC2D6538 */  sw    $t5, %lo(gSavefileData+8)($at)
/* 081EF0 800812F0 8D6B6538 */  lw    $t3, %lo(gSavefileData+8)($t3)
/* 081EF4 800812F4 00671821 */  addu  $v1, $v1, $a3
/* 081EF8 800812F8 256E0118 */  addiu $t6, $t3, 0x118
/* 081EFC 800812FC AD6E0004 */  sw    $t6, 4($t3)
/* 081F00 80081300 8DEF6538 */  lw    $t7, %lo(gSavefileData+8)($t7)
/* 081F04 80081304 3C0D8012 */  lui   $t5, %hi(gSavefileData+12) # $t5, 0x8012
/* 081F08 80081308 8DF90004 */  lw    $t9, 4($t7)
/* 081F0C 8008130C 00000000 */  nop   
/* 081F10 80081310 0326C021 */  addu  $t8, $t9, $a2
/* 081F14 80081314 ADF80000 */  sw    $t8, ($t7)
/* 081F18 80081318 8C8A0000 */  lw    $t2, ($a0)
/* 081F1C 8008131C 24040041 */  li    $a0, 65
/* 081F20 80081320 01434821 */  addu  $t1, $t2, $v1
/* 081F24 80081324 AC29653C */  sw    $t1, %lo(gSavefileData+12)($at)
/* 081F28 80081328 8D08653C */  lw    $t0, %lo(gSavefileData+12)($t0)
/* 081F2C 8008132C 00000000 */  nop   
/* 081F30 80081330 250C0118 */  addiu $t4, $t0, 0x118
/* 081F34 80081334 AD0C0004 */  sw    $t4, 4($t0)
/* 081F38 80081338 8DAD653C */  lw    $t5, %lo(gSavefileData+12)($t5)
/* 081F3C 8008133C 00000000 */  nop   
/* 081F40 80081340 8DAE0004 */  lw    $t6, 4($t5)
/* 081F44 80081344 00000000 */  nop   
/* 081F48 80081348 01C65821 */  addu  $t3, $t6, $a2
/* 081F4C 8008134C 0C0078A7 */  jal   get_misc_asset
/* 081F50 80081350 ADAB0000 */   sw    $t3, ($t5)
/* 081F54 80081354 3C038012 */  lui   $v1, %hi(gCheatsAssetData) # $v1, 0x8012
/* 081F58 80081358 24636C30 */  addiu $v1, %lo(gCheatsAssetData) # addiu $v1, $v1, 0x6c30
/* 081F5C 8008135C AC620000 */  sw    $v0, ($v1)
/* 081F60 80081360 94580000 */  lhu   $t8, ($v0)
/* 081F64 80081364 3C018012 */  lui   $at, %hi(gNumberOfCheats) # $at, 0x8012
/* 081F68 80081368 24041000 */  li    $a0, 4096
/* 081F6C 8008136C 2405FFFF */  li    $a1, -1
/* 081F70 80081370 0C01C327 */  jal   allocate_from_main_pool_safe
/* 081F74 80081374 AC386C38 */   sw    $t8, %lo(gNumberOfCheats)($at)
/* 081F78 80081378 3C01800E */  lui   $at, %hi(gMenuText) # $at, 0x800e
/* 081F7C 8008137C AC22F4A0 */  sw    $v0, %lo(gMenuText)($at)
/* 081F80 80081380 0C01FE40 */  jal   load_menu_text
/* 081F84 80081384 00002025 */   move  $a0, $zero
/* 081F88 80081388 3C028012 */  lui   $v0, %hi(gMenuTextures) # $v0, 0x8012
/* 081F8C 8008138C 3C038012 */  lui   $v1, %hi(D_80126750) # $v1, 0x8012
/* 081F90 80081390 24636750 */  addiu $v1, %lo(D_80126750) # addiu $v1, $v1, 0x6750
/* 081F94 80081394 24426550 */  addiu $v0, %lo(gMenuTextures) # addiu $v0, $v0, 0x6550
.L80081398:
/* 081F98 80081398 24420010 */  addiu $v0, $v0, 0x10
/* 081F9C 8008139C AC40FFF0 */  sw    $zero, -0x10($v0)
/* 081FA0 800813A0 AC40FFF4 */  sw    $zero, -0xc($v0)
/* 081FA4 800813A4 AC40FFF8 */  sw    $zero, -8($v0)
/* 081FA8 800813A8 1443FFFB */  bne   $v0, $v1, .L80081398
/* 081FAC 800813AC AC40FFFC */   sw    $zero, -4($v0)
/* 081FB0 800813B0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 081FB4 800813B4 27BD0038 */  addiu $sp, $sp, 0x38
/* 081FB8 800813B8 03E00008 */  jr    $ra
/* 081FBC 800813BC 00000000 */   nop   

