.late_rodata
glabel jpt_800E92D0
.word L800C0310, L800C0320, L800C0370, L800C03C0, L800C03D0, L800C0420, L800C0470

.text
glabel func_800C01D8
/* 0C0DD8 800C01D8 3C0E800E */  lui   $t6, %hi(D_800E31A0) # $t6, 0x800e
/* 0C0DDC 800C01DC 8DCE31A0 */  lw    $t6, %lo(D_800E31A0)($t6)
/* 0C0DE0 800C01E0 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0C0DE4 800C01E4 11C00003 */  beqz  $t6, .L800C01F4
/* 0C0DE8 800C01E8 AFBF002C */   sw    $ra, 0x2c($sp)
/* 0C0DEC 800C01EC 100000A5 */  b     .L800C0484
/* 0C0DF0 800C01F0 00001025 */   move  $v0, $zero
.L800C01F4:
/* 0C0DF4 800C01F4 0C0301C9 */  jal   transition_end
/* 0C0DF8 800C01F8 AFA40030 */   sw    $a0, 0x30($sp)
/* 0C0DFC 800C01FC 8FA40030 */  lw    $a0, 0x30($sp)
/* 0C0E00 800C0200 3C03800E */  lui   $v1, %hi(D_800E31BC) # $v1, 0x800e
/* 0C0E04 800C0204 14800003 */  bnez  $a0, .L800C0214
/* 0C0E08 800C0208 246331BC */   addiu $v1, %lo(D_800E31BC) # addiu $v1, $v1, 0x31bc
/* 0C0E0C 800C020C 1000009D */  b     .L800C0484
/* 0C0E10 800C0210 00001025 */   move  $v0, $zero
.L800C0214:
/* 0C0E14 800C0214 948F0004 */  lhu   $t7, 4($a0)
/* 0C0E18 800C0218 3C06800E */  lui   $a2, %hi(sTransitionFadeTimer) # $a2, 0x800e
/* 0C0E1C 800C021C 24C631B0 */  addiu $a2, %lo(sTransitionFadeTimer) # addiu $a2, $a2, 0x31b0
/* 0C0E20 800C0220 A4CF0000 */  sh    $t7, ($a2)
/* 0C0E24 800C0224 94980004 */  lhu   $t8, 4($a0)
/* 0C0E28 800C0228 3C01800E */  lui   $at, %hi(D_800E31B8) # $at, 0x800e
/* 0C0E2C 800C022C A43831B8 */  sh    $t8, %lo(D_800E31B8)($at)
/* 0C0E30 800C0230 94990006 */  lhu   $t9, 6($a0)
/* 0C0E34 800C0234 3C01800E */  lui   $at, %hi(sTransitionFlags) # $at, 0x800e
/* 0C0E38 800C0238 A43931B4 */  sh    $t9, %lo(sTransitionFlags)($at)
/* 0C0E3C 800C023C 90820000 */  lbu   $v0, ($a0)
/* 0C0E40 800C0240 3C078013 */  lui   $a3, %hi(gCurFaceTransition) # $a3, 0x8013
/* 0C0E44 800C0244 30480080 */  andi  $t0, $v0, 0x80
/* 0C0E48 800C0248 2D090001 */  sltiu $t1, $t0, 1
/* 0C0E4C 800C024C A0690000 */  sb    $t1, ($v1)
/* 0C0E50 800C0250 908A0000 */  lbu   $t2, ($a0)
/* 0C0E54 800C0254 24E7A730 */  addiu $a3, %lo(gCurFaceTransition) # addiu $a3, $a3, -0x58d0
/* 0C0E58 800C0258 314B003F */  andi  $t3, $t2, 0x3f
/* 0C0E5C 800C025C ACEB0000 */  sw    $t3, ($a3)
/* 0C0E60 800C0260 908C0000 */  lbu   $t4, ($a0)
/* 0C0E64 800C0264 3C01800E */  lui   $at, %hi(D_800E31A8) # $at, 0x800e
/* 0C0E68 800C0268 318D0040 */  andi  $t5, $t4, 0x40
/* 0C0E6C 800C026C AC2D31A8 */  sw    $t5, %lo(D_800E31A8)($at)
/* 0C0E70 800C0270 806E0000 */  lb    $t6, ($v1)
/* 0C0E74 800C0274 3C05800E */  lui   $a1, %hi(sLevelTransitionDelayTimer) # $a1, 0x800e
/* 0C0E78 800C0278 24A531A4 */  addiu $a1, %lo(sLevelTransitionDelayTimer) # addiu $a1, $a1, 0x31a4
/* 0C0E7C 800C027C 15C00003 */  bnez  $t6, .L800C028C
/* 0C0E80 800C0280 ACA00000 */   sw    $zero, ($a1)
/* 0C0E84 800C0284 24180002 */  li    $t8, 2
/* 0C0E88 800C0288 ACB80000 */  sw    $t8, ($a1)
.L800C028C:
/* 0C0E8C 800C028C 94D90000 */  lhu   $t9, ($a2)
/* 0C0E90 800C0290 3C028013 */  lui   $v0, %hi(gCurFadeRed) # $v0, 0x8013
/* 0C0E94 800C0294 1B200078 */  blez  $t9, .L800C0478
/* 0C0E98 800C0298 2442A734 */   addiu $v0, %lo(gCurFadeRed) # addiu $v0, $v0, -0x58cc
/* 0C0E9C 800C029C 90480000 */  lbu   $t0, ($v0)
/* 0C0EA0 800C02A0 3C038013 */  lui   $v1, %hi(gCurFadeGreen) # $v1, 0x8013
/* 0C0EA4 800C02A4 3C018013 */  lui   $at, %hi(gLastFadeRed) # $at, 0x8013
/* 0C0EA8 800C02A8 2463A735 */  addiu $v1, %lo(gCurFadeGreen) # addiu $v1, $v1, -0x58cb
/* 0C0EAC 800C02AC AC28A738 */  sw    $t0, %lo(gLastFadeRed)($at)
/* 0C0EB0 800C02B0 90690000 */  lbu   $t1, ($v1)
/* 0C0EB4 800C02B4 3C058013 */  lui   $a1, %hi(gCurFadeBlue) # $a1, 0x8013
/* 0C0EB8 800C02B8 3C018013 */  lui   $at, %hi(gLastFadeGreen) # $at, 0x8013
/* 0C0EBC 800C02BC 24A5A736 */  addiu $a1, %lo(gCurFadeBlue) # addiu $a1, $a1, -0x58ca
/* 0C0EC0 800C02C0 AC29A73C */  sw    $t1, %lo(gLastFadeGreen)($at)
/* 0C0EC4 800C02C4 90AA0000 */  lbu   $t2, ($a1)
/* 0C0EC8 800C02C8 3C018013 */  lui   $at, %hi(gLastFadeBlue) # $at, 0x8013
/* 0C0ECC 800C02CC AC2AA740 */  sw    $t2, %lo(gLastFadeBlue)($at)
/* 0C0ED0 800C02D0 908B0001 */  lbu   $t3, 1($a0)
/* 0C0ED4 800C02D4 8CEE0000 */  lw    $t6, ($a3)
/* 0C0ED8 800C02D8 A04B0000 */  sb    $t3, ($v0)
/* 0C0EDC 800C02DC 908C0002 */  lbu   $t4, 2($a0)
/* 0C0EE0 800C02E0 2DC10007 */  sltiu $at, $t6, 7
/* 0C0EE4 800C02E4 A06C0000 */  sb    $t4, ($v1)
/* 0C0EE8 800C02E8 908D0003 */  lbu   $t5, 3($a0)
/* 0C0EEC 800C02EC 10200062 */  beqz  $at, .L800C0478
/* 0C0EF0 800C02F0 A0AD0000 */   sb    $t5, ($a1)
/* 0C0EF4 800C02F4 000E7080 */  sll   $t6, $t6, 2
/* 0C0EF8 800C02F8 3C01800F */  lui   $at, %hi(jpt_800E92D0) # $at, 0x800f
/* 0C0EFC 800C02FC 002E0821 */  addu  $at, $at, $t6
/* 0C0F00 800C0300 8C2E92D0 */  lw    $t6, %lo(jpt_800E92D0)($at)
/* 0C0F04 800C0304 00000000 */  nop   
/* 0C0F08 800C0308 01C00008 */  jr    $t6
/* 0C0F0C 800C030C 00000000 */   nop   
glabel L800C0310
/* 0C0F10 800C0310 0C0301E0 */  jal   func_800C0780
/* 0C0F14 800C0314 00000000 */   nop   
/* 0C0F18 800C0318 10000057 */  b     .L800C0478
/* 0C0F1C 800C031C 00000000 */   nop   
glabel L800C0320
/* 0C0F20 800C0320 3C02800E */  lui   $v0, %hi(D_800E32D0) # $v0, 0x800e
/* 0C0F24 800C0324 3C0F800E */  lui   $t7, %hi(D_800E32A0) # $t7, 0x800e
/* 0C0F28 800C0328 3C18800E */  lui   $t8, %hi(D_800E32AC) # $t8, 0x800e
/* 0C0F2C 800C032C 3C19800E */  lui   $t9, %hi(D_800E32B8) # $t9, 0x800e
/* 0C0F30 800C0330 244232D0 */  addiu $v0, %lo(D_800E32D0) # addiu $v0, $v0, 0x32d0
/* 0C0F34 800C0334 273932B8 */  addiu $t9, %lo(D_800E32B8) # addiu $t9, $t9, 0x32b8
/* 0C0F38 800C0338 271832AC */  addiu $t8, %lo(D_800E32AC) # addiu $t8, $t8, 0x32ac
/* 0C0F3C 800C033C 25EF32A0 */  addiu $t7, %lo(D_800E32A0) # addiu $t7, $t7, 0x32a0
/* 0C0F40 800C0340 3C07800E */  lui   $a3, %hi(D_800E3230) # $a3, 0x800e
/* 0C0F44 800C0344 24E73230 */  addiu $a3, %lo(D_800E3230) # addiu $a3, $a3, 0x3230
/* 0C0F48 800C0348 AFAF0010 */  sw    $t7, 0x10($sp)
/* 0C0F4C 800C034C AFB80014 */  sw    $t8, 0x14($sp)
/* 0C0F50 800C0350 AFB90020 */  sw    $t9, 0x20($sp)
/* 0C0F54 800C0354 AFA20018 */  sw    $v0, 0x18($sp)
/* 0C0F58 800C0358 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0C0F5C 800C035C 2405000C */  li    $a1, 12
/* 0C0F60 800C0360 0C0302C0 */  jal   func_800C0B00
/* 0C0F64 800C0364 24060008 */   li    $a2, 8
/* 0C0F68 800C0368 10000043 */  b     .L800C0478
/* 0C0F6C 800C036C 00000000 */   nop   
glabel L800C0370
/* 0C0F70 800C0370 3C02800E */  lui   $v0, %hi(D_800E32D0) # $v0, 0x800e
/* 0C0F74 800C0374 3C08800E */  lui   $t0, %hi(D_800E32A0) # $t0, 0x800e
/* 0C0F78 800C0378 3C09800E */  lui   $t1, %hi(D_800E32AC) # $t1, 0x800e
/* 0C0F7C 800C037C 3C0A800E */  lui   $t2, %hi(D_800E32B8) # $t2, 0x800e
/* 0C0F80 800C0380 244232D0 */  addiu $v0, %lo(D_800E32D0) # addiu $v0, $v0, 0x32d0
/* 0C0F84 800C0384 254A32B8 */  addiu $t2, %lo(D_800E32B8) # addiu $t2, $t2, 0x32b8
/* 0C0F88 800C0388 252932AC */  addiu $t1, %lo(D_800E32AC) # addiu $t1, $t1, 0x32ac
/* 0C0F8C 800C038C 250832A0 */  addiu $t0, %lo(D_800E32A0) # addiu $t0, $t0, 0x32a0
/* 0C0F90 800C0390 3C07800E */  lui   $a3, %hi(D_800E3268) # $a3, 0x800e
/* 0C0F94 800C0394 24E73268 */  addiu $a3, %lo(D_800E3268) # addiu $a3, $a3, 0x3268
/* 0C0F98 800C0398 AFA80010 */  sw    $t0, 0x10($sp)
/* 0C0F9C 800C039C AFA90014 */  sw    $t1, 0x14($sp)
/* 0C0FA0 800C03A0 AFAA0020 */  sw    $t2, 0x20($sp)
/* 0C0FA4 800C03A4 AFA20018 */  sw    $v0, 0x18($sp)
/* 0C0FA8 800C03A8 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0C0FAC 800C03AC 2405000C */  li    $a1, 12
/* 0C0FB0 800C03B0 0C0302C0 */  jal   func_800C0B00
/* 0C0FB4 800C03B4 24060008 */   li    $a2, 8
/* 0C0FB8 800C03B8 1000002F */  b     .L800C0478
/* 0C0FBC 800C03BC 00000000 */   nop   
glabel L800C03C0
/* 0C0FC0 800C03C0 0C030575 */  jal   func_800C15D4
/* 0C0FC4 800C03C4 00000000 */   nop   
/* 0C0FC8 800C03C8 1000002B */  b     .L800C0478
/* 0C0FCC 800C03CC 00000000 */   nop   
glabel L800C03D0
/* 0C0FD0 800C03D0 3C02800E */  lui   $v0, %hi(D_800E34F8) # $v0, 0x800e
/* 0C0FD4 800C03D4 3C0B800E */  lui   $t3, %hi(D_800E349C) # $t3, 0x800e
/* 0C0FD8 800C03D8 3C0C800E */  lui   $t4, %hi(D_800E3440) # $t4, 0x800e
/* 0C0FDC 800C03DC 3C0D800E */  lui   $t5, %hi(D_800E3554) # $t5, 0x800e
/* 0C0FE0 800C03E0 244234F8 */  addiu $v0, %lo(D_800E34F8) # addiu $v0, $v0, 0x34f8
/* 0C0FE4 800C03E4 25AD3554 */  addiu $t5, %lo(D_800E3554) # addiu $t5, $t5, 0x3554
/* 0C0FE8 800C03E8 258C3440 */  addiu $t4, %lo(D_800E3440) # addiu $t4, $t4, 0x3440
/* 0C0FEC 800C03EC 256B349C */  addiu $t3, %lo(D_800E349C) # addiu $t3, $t3, 0x349c
/* 0C0FF0 800C03F0 3C07800E */  lui   $a3, %hi(D_800E3344) # $a3, 0x800e
/* 0C0FF4 800C03F4 24E73344 */  addiu $a3, %lo(D_800E3344) # addiu $a3, $a3, 0x3344
/* 0C0FF8 800C03F8 AFAB0010 */  sw    $t3, 0x10($sp)
/* 0C0FFC 800C03FC AFAC0014 */  sw    $t4, 0x14($sp)
/* 0C1000 800C0400 AFAD0020 */  sw    $t5, 0x20($sp)
/* 0C1004 800C0404 AFA20018 */  sw    $v0, 0x18($sp)
/* 0C1008 800C0408 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0C100C 800C040C 2405005C */  li    $a1, 92
/* 0C1010 800C0410 0C0302C0 */  jal   func_800C0B00
/* 0C1014 800C0414 24060050 */   li    $a2, 80
/* 0C1018 800C0418 10000017 */  b     .L800C0478
/* 0C101C 800C041C 00000000 */   nop   
glabel L800C0420
/* 0C1020 800C0420 3C02800E */  lui   $v0, %hi(D_800E3338) # $v0, 0x800e
/* 0C1024 800C0424 3C0E800E */  lui   $t6, %hi(D_800E330C) # $t6, 0x800e
/* 0C1028 800C0428 3C0F800E */  lui   $t7, %hi(D_800E3318) # $t7, 0x800e
/* 0C102C 800C042C 3C18800E */  lui   $t8, %hi(D_800E3324) # $t8, 0x800e
/* 0C1030 800C0430 24423338 */  addiu $v0, %lo(D_800E3338) # addiu $v0, $v0, 0x3338
/* 0C1034 800C0434 27183324 */  addiu $t8, %lo(D_800E3324) # addiu $t8, $t8, 0x3324
/* 0C1038 800C0438 25EF3318 */  addiu $t7, %lo(D_800E3318) # addiu $t7, $t7, 0x3318
/* 0C103C 800C043C 25CE330C */  addiu $t6, %lo(D_800E330C) # addiu $t6, $t6, 0x330c
/* 0C1040 800C0440 3C07800E */  lui   $a3, %hi(D_800E32DC) # $a3, 0x800e
/* 0C1044 800C0444 24E732DC */  addiu $a3, %lo(D_800E32DC) # addiu $a3, $a3, 0x32dc
/* 0C1048 800C0448 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0C104C 800C044C AFAF0014 */  sw    $t7, 0x14($sp)
/* 0C1050 800C0450 AFB80020 */  sw    $t8, 0x20($sp)
/* 0C1054 800C0454 AFA20018 */  sw    $v0, 0x18($sp)
/* 0C1058 800C0458 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0C105C 800C045C 2405000A */  li    $a1, 10
/* 0C1060 800C0460 0C0302C0 */  jal   func_800C0B00
/* 0C1064 800C0464 24060006 */   li    $a2, 6
/* 0C1068 800C0468 10000003 */  b     .L800C0478
/* 0C106C 800C046C 00000000 */   nop   
glabel L800C0470
/* 0C1070 800C0470 0C030990 */  jal   func_800C2640
/* 0C1074 800C0474 00000000 */   nop   
.L800C0478:
/* 0C1078 800C0478 3C02800E */  lui   $v0, %hi(sTransitionStatus) # $v0, 0x800e
/* 0C107C 800C047C 8C4231AC */  lw    $v0, %lo(sTransitionStatus)($v0)
/* 0C1080 800C0480 00000000 */  nop   
.L800C0484:
/* 0C1084 800C0484 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0C1088 800C0488 27BD0030 */  addiu $sp, $sp, 0x30
/* 0C108C 800C048C 03E00008 */  jr    $ra
/* 0C1090 800C0490 00000000 */   nop   

