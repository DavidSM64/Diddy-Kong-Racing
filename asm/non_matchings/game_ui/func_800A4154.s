glabel func_800A4154
/* 0A4D54 800A4154 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 0A4D58 800A4158 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0A4D5C 800A415C AFB00018 */  sw    $s0, 0x18($sp)
/* 0A4D60 800A4160 AFA40040 */  sw    $a0, 0x40($sp)
/* 0A4D64 800A4164 AFA50044 */  sw    $a1, 0x44($sp)
/* 0A4D68 800A4168 84820000 */  lh    $v0, ($a0)
/* 0A4D6C 800A416C 2401FFFF */  li    $at, -1
/* 0A4D70 800A4170 1041002B */  beq   $v0, $at, .L800A4220
/* 0A4D74 800A4174 3C038012 */   lui   $v1, %hi(gHUDNumPlayers) # $v1, 0x8012
/* 0A4D78 800A4178 8C636D0C */  lw    $v1, %lo(gHUDNumPlayers)($v1)
/* 0A4D7C 800A417C 3C19800E */  lui   $t9, %hi(D_800E2794) # $t9, 0x800e
/* 0A4D80 800A4180 1860000F */  blez  $v1, .L800A41C0
/* 0A4D84 800A4184 00037880 */   sll   $t7, $v1, 2
/* 0A4D88 800A4188 01E2C021 */  addu  $t8, $t7, $v0
/* 0A4D8C 800A418C 0338C821 */  addu  $t9, $t9, $t8
/* 0A4D90 800A4190 93392794 */  lbu   $t9, %lo(D_800E2794)($t9)
/* 0A4D94 800A4194 24010002 */  li    $at, 2
/* 0A4D98 800A4198 13210009 */  beq   $t9, $at, .L800A41C0
/* 0A4D9C 800A419C 3C0A8012 */   lui   $t2, %hi(D_80126D60) # $t2, 0x8012
/* 0A4DA0 800A41A0 8D4A6D60 */  lw    $t2, %lo(D_80126D60)($t2)
/* 0A4DA4 800A41A4 24010041 */  li    $at, 65
/* 0A4DA8 800A41A8 8142004C */  lb    $v0, 0x4c($t2)
/* 0A4DAC 800A41AC 00000000 */  nop   
/* 0A4DB0 800A41B0 10410003 */  beq   $v0, $at, .L800A41C0
/* 0A4DB4 800A41B4 24010040 */   li    $at, 64
/* 0A4DB8 800A41B8 1441010A */  bne   $v0, $at, .L800A45E4
/* 0A4DBC 800A41BC 8FBF001C */   lw    $ra, 0x1c($sp)
.L800A41C0:
/* 0A4DC0 800A41C0 8FAB0040 */  lw    $t3, 0x40($sp)
/* 0A4DC4 800A41C4 00000000 */  nop   
/* 0A4DC8 800A41C8 816C01D8 */  lb    $t4, 0x1d8($t3)
/* 0A4DCC 800A41CC 00000000 */  nop   
/* 0A4DD0 800A41D0 15800104 */  bnez  $t4, .L800A45E4
/* 0A4DD4 800A41D4 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0A4DD8 800A41D8 18600011 */  blez  $v1, .L800A4220
/* 0A4DDC 800A41DC 00000000 */   nop   
/* 0A4DE0 800A41E0 81620193 */  lb    $v0, 0x193($t3)
/* 0A4DE4 800A41E4 00000000 */  nop   
/* 0A4DE8 800A41E8 1840000D */  blez  $v0, .L800A4220
/* 0A4DEC 800A41EC 00026880 */   sll   $t5, $v0, 2
/* 0A4DF0 800A41F0 016D7021 */  addu  $t6, $t3, $t5
/* 0A4DF4 800A41F4 8DCF0128 */  lw    $t7, 0x128($t6)
/* 0A4DF8 800A41F8 3C188012 */  lui   $t8, %hi(D_80126D60) # $t8, 0x8012
/* 0A4DFC 800A41FC 29E100B4 */  slti  $at, $t7, 0xb4
/* 0A4E00 800A4200 10200007 */  beqz  $at, .L800A4220
/* 0A4E04 800A4204 00000000 */   nop   
/* 0A4E08 800A4208 8F186D60 */  lw    $t8, %lo(D_80126D60)($t8)
/* 0A4E0C 800A420C 00000000 */  nop   
/* 0A4E10 800A4210 8319004C */  lb    $t9, 0x4c($t8)
/* 0A4E14 800A4214 00000000 */  nop   
/* 0A4E18 800A4218 332A0040 */  andi  $t2, $t9, 0x40
/* 0A4E1C 800A421C 114000F0 */  beqz  $t2, .L800A45E0
.L800A4220:
/* 0A4E20 800A4220 3C108012 */   lui   $s0, %hi(D_80126CDC) # $s0, 0x8012
/* 0A4E24 800A4224 26106CDC */  addiu $s0, %lo(D_80126CDC) # addiu $s0, $s0, 0x6cdc
/* 0A4E28 800A4228 8E070000 */  lw    $a3, ($s0)
/* 0A4E2C 800A422C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4E30 800A4230 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A4E34 800A4234 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A4E38 800A4238 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A4E3C 800A423C 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A4E40 800A4240 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A4E44 800A4244 0C02A980 */  jal   func_800AA600
/* 0A4E48 800A4248 24E70240 */   addiu $a3, $a3, 0x240
/* 0A4E4C 800A424C 8FA60040 */  lw    $a2, 0x40($sp)
/* 0A4E50 800A4250 8E020000 */  lw    $v0, ($s0)
/* 0A4E54 800A4254 80C40185 */  lb    $a0, 0x185($a2)
/* 0A4E58 800A4258 00000000 */  nop   
/* 0A4E5C 800A425C AFA4003C */  sw    $a0, 0x3c($sp)
/* 0A4E60 800A4260 804500FA */  lb    $a1, 0xfa($v0)
/* 0A4E64 800A4264 904300F9 */  lbu   $v1, 0xf9($v0)
/* 0A4E68 800A4268 14A0000A */  bnez  $a1, .L800A4294
/* 0A4E6C 800A426C 00000000 */   nop   
/* 0A4E70 800A4270 804C00FB */  lb    $t4, 0xfb($v0)
/* 0A4E74 800A4274 240B0002 */  li    $t3, 2
/* 0A4E78 800A4278 108C0006 */  beq   $a0, $t4, .L800A4294
/* 0A4E7C 800A427C 00000000 */   nop   
/* 0A4E80 800A4280 A04B00FA */  sb    $t3, 0xfa($v0)
/* 0A4E84 800A4284 8E0E0000 */  lw    $t6, ($s0)
/* 0A4E88 800A4288 80CD0185 */  lb    $t5, 0x185($a2)
/* 0A4E8C 800A428C 10000024 */  b     .L800A4320
/* 0A4E90 800A4290 A1CD00FB */   sb    $t5, 0xfb($t6)
.L800A4294:
/* 0A4E94 800A4294 10A00022 */  beqz  $a1, .L800A4320
/* 0A4E98 800A4298 3C014000 */   li    $at, 0x40000000 # 2.000000
/* 0A4E9C 800A429C 44812000 */  mtc1  $at, $f4
/* 0A4EA0 800A42A0 00000000 */  nop   
/* 0A4EA4 800A42A4 E4440388 */  swc1  $f4, 0x388($v0)
/* 0A4EA8 800A42A8 8FAF0044 */  lw    $t7, 0x44($sp)
/* 0A4EAC 800A42AC 8E020000 */  lw    $v0, ($s0)
/* 0A4EB0 800A42B0 000FC080 */  sll   $t8, $t7, 2
/* 0A4EB4 800A42B4 030FC023 */  subu  $t8, $t8, $t7
/* 0A4EB8 800A42B8 0018C080 */  sll   $t8, $t8, 2
/* 0A4EBC 800A42BC 844A00F8 */  lh    $t2, 0xf8($v0)
/* 0A4EC0 800A42C0 030FC021 */  addu  $t8, $t8, $t7
/* 0A4EC4 800A42C4 00781821 */  addu  $v1, $v1, $t8
/* 0A4EC8 800A42C8 307900FF */  andi  $t9, $v1, 0xff
/* 0A4ECC 800A42CC 314C00FF */  andi  $t4, $t2, 0xff
/* 0A4ED0 800A42D0 032C082A */  slt   $at, $t9, $t4
/* 0A4ED4 800A42D4 10200012 */  beqz  $at, .L800A4320
/* 0A4ED8 800A42D8 03201825 */   move  $v1, $t9
/* 0A4EDC 800A42DC 804B00FA */  lb    $t3, 0xfa($v0)
/* 0A4EE0 800A42E0 24040001 */  li    $a0, 1
/* 0A4EE4 800A42E4 256DFFFF */  addiu $t5, $t3, -1
/* 0A4EE8 800A42E8 A04D00FA */  sb    $t5, 0xfa($v0)
/* 0A4EEC 800A42EC 8E020000 */  lw    $v0, ($s0)
/* 0A4EF0 800A42F0 00000000 */  nop   
/* 0A4EF4 800A42F4 804E00FA */  lb    $t6, 0xfa($v0)
/* 0A4EF8 800A42F8 00000000 */  nop   
/* 0A4EFC 800A42FC 15C00008 */  bnez  $t6, .L800A4320
/* 0A4F00 800A4300 00000000 */   nop   
/* 0A4F04 800A4304 A044039B */  sb    $a0, 0x39b($v0)
/* 0A4F08 800A4308 8E180000 */  lw    $t8, ($s0)
/* 0A4F0C 800A430C 240F0006 */  li    $t7, 6
/* 0A4F10 800A4310 A30F039A */  sb    $t7, 0x39a($t8)
/* 0A4F14 800A4314 8E190000 */  lw    $t9, ($s0)
/* 0A4F18 800A4318 00001825 */  move  $v1, $zero
/* 0A4F1C 800A431C A7240398 */  sh    $a0, 0x398($t9)
.L800A4320:
/* 0A4F20 800A4320 14600048 */  bnez  $v1, .L800A4444
/* 0A4F24 800A4324 00601025 */   move  $v0, $v1
/* 0A4F28 800A4328 24040001 */  li    $a0, 1
/* 0A4F2C 800A432C 0C01EFC7 */  jal   func_8007BF1C
/* 0A4F30 800A4330 AFA30024 */   sw    $v1, 0x24($sp)
/* 0A4F34 800A4334 0C019826 */  jal   set_viewport_tv_type
/* 0A4F38 800A4338 24040001 */   li    $a0, 1
/* 0A4F3C 800A433C 8E070000 */  lw    $a3, ($s0)
/* 0A4F40 800A4340 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4F44 800A4344 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A4F48 800A4348 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A4F4C 800A434C 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A4F50 800A4350 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A4F54 800A4354 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A4F58 800A4358 0C02A980 */  jal   func_800AA600
/* 0A4F5C 800A435C 24E70360 */   addiu $a3, $a3, 0x360
/* 0A4F60 800A4360 0C019826 */  jal   set_viewport_tv_type
/* 0A4F64 800A4364 00002025 */   move  $a0, $zero
/* 0A4F68 800A4368 0C01EFC7 */  jal   func_8007BF1C
/* 0A4F6C 800A436C 00002025 */   move  $a0, $zero
/* 0A4F70 800A4370 8FAA0024 */  lw    $t2, 0x24($sp)
/* 0A4F74 800A4374 8E0C0000 */  lw    $t4, ($s0)
/* 0A4F78 800A4378 00000000 */  nop   
/* 0A4F7C 800A437C A58A00F8 */  sh    $t2, 0xf8($t4)
/* 0A4F80 800A4380 8E020000 */  lw    $v0, ($s0)
/* 0A4F84 800A4384 00000000 */  nop   
/* 0A4F88 800A4388 804B039B */  lb    $t3, 0x39b($v0)
/* 0A4F8C 800A438C 00000000 */  nop   
/* 0A4F90 800A4390 1160004D */  beqz  $t3, .L800A44C8
/* 0A4F94 800A4394 8FA9003C */   lw    $t1, 0x3c($sp)
/* 0A4F98 800A4398 804D039A */  lb    $t5, 0x39a($v0)
/* 0A4F9C 800A439C 8FAE0044 */  lw    $t6, 0x44($sp)
/* 0A4FA0 800A43A0 24040006 */  li    $a0, 6
/* 0A4FA4 800A43A4 01AE7823 */  subu  $t7, $t5, $t6
/* 0A4FA8 800A43A8 A04F039A */  sb    $t7, 0x39a($v0)
/* 0A4FAC 800A43AC 8E020000 */  lw    $v0, ($s0)
/* 0A4FB0 800A43B0 00000000 */  nop   
/* 0A4FB4 800A43B4 8058039A */  lb    $t8, 0x39a($v0)
/* 0A4FB8 800A43B8 00000000 */  nop   
/* 0A4FBC 800A43BC 07010011 */  bgez  $t8, .L800A4404
/* 0A4FC0 800A43C0 00000000 */   nop   
/* 0A4FC4 800A43C4 A044039A */  sb    $a0, 0x39a($v0)
/* 0A4FC8 800A43C8 8E020000 */  lw    $v0, ($s0)
/* 0A4FCC 800A43CC 00000000 */  nop   
/* 0A4FD0 800A43D0 84430398 */  lh    $v1, 0x398($v0)
/* 0A4FD4 800A43D4 00000000 */  nop   
/* 0A4FD8 800A43D8 14830009 */  bne   $a0, $v1, .L800A4400
/* 0A4FDC 800A43DC 246C0001 */   addiu $t4, $v1, 1
/* 0A4FE0 800A43E0 A4400398 */  sh    $zero, 0x398($v0)
/* 0A4FE4 800A43E4 8E020000 */  lw    $v0, ($s0)
/* 0A4FE8 800A43E8 00000000 */  nop   
/* 0A4FEC 800A43EC 8059039B */  lb    $t9, 0x39b($v0)
/* 0A4FF0 800A43F0 00000000 */  nop   
/* 0A4FF4 800A43F4 272AFFFF */  addiu $t2, $t9, -1
/* 0A4FF8 800A43F8 10000002 */  b     .L800A4404
/* 0A4FFC 800A43FC A04A039B */   sb    $t2, 0x39b($v0)
.L800A4400:
/* 0A5000 800A4400 A44C0398 */  sh    $t4, 0x398($v0)
.L800A4404:
/* 0A5004 800A4404 0C019826 */  jal   set_viewport_tv_type
/* 0A5008 800A4408 24040001 */   li    $a0, 1
/* 0A500C 800A440C 8E070000 */  lw    $a3, ($s0)
/* 0A5010 800A4410 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5014 800A4414 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A5018 800A4418 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A501C 800A441C 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A5020 800A4420 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A5024 800A4424 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5028 800A4428 0C02A980 */  jal   func_800AA600
/* 0A502C 800A442C 24E70380 */   addiu $a3, $a3, 0x380
/* 0A5030 800A4430 0C019826 */  jal   set_viewport_tv_type
/* 0A5034 800A4434 00002025 */   move  $a0, $zero
/* 0A5038 800A4438 8E020000 */  lw    $v0, ($s0)
/* 0A503C 800A443C 10000022 */  b     .L800A44C8
/* 0A5040 800A4440 8FA9003C */   lw    $t1, 0x3c($sp)
.L800A4444:
/* 0A5044 800A4444 8E0D0000 */  lw    $t5, ($s0)
/* 0A5048 800A4448 244B0080 */  addiu $t3, $v0, 0x80
/* 0A504C 800A444C 00002025 */  move  $a0, $zero
/* 0A5050 800A4450 0C01A142 */  jal   func_80068508
/* 0A5054 800A4454 A5AB00F8 */   sh    $t3, 0xf8($t5)
/* 0A5058 800A4458 0C01EFC7 */  jal   func_8007BF1C
/* 0A505C 800A445C 24040001 */   li    $a0, 1
/* 0A5060 800A4460 0C019826 */  jal   set_viewport_tv_type
/* 0A5064 800A4464 24040001 */   li    $a0, 1
/* 0A5068 800A4468 8E070000 */  lw    $a3, ($s0)
/* 0A506C 800A446C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5070 800A4470 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A5074 800A4474 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A5078 800A4478 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A507C 800A447C 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A5080 800A4480 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5084 800A4484 0C02A980 */  jal   func_800AA600
/* 0A5088 800A4488 24E700E0 */   addiu $a3, $a3, 0xe0
/* 0A508C 800A448C 0C01EFC7 */  jal   func_8007BF1C
/* 0A5090 800A4490 00002025 */   move  $a0, $zero
/* 0A5094 800A4494 0C019826 */  jal   set_viewport_tv_type
/* 0A5098 800A4498 00002025 */   move  $a0, $zero
/* 0A509C 800A449C 0C01A142 */  jal   func_80068508
/* 0A50A0 800A44A0 24040001 */   li    $a0, 1
/* 0A50A4 800A44A4 8E020000 */  lw    $v0, ($s0)
/* 0A50A8 800A44A8 00000000 */  nop   
/* 0A50AC 800A44AC 844E00F8 */  lh    $t6, 0xf8($v0)
/* 0A50B0 800A44B0 00000000 */  nop   
/* 0A50B4 800A44B4 25CFFF80 */  addiu $t7, $t6, -0x80
/* 0A50B8 800A44B8 A44F00F8 */  sh    $t7, 0xf8($v0)
/* 0A50BC 800A44BC 8E020000 */  lw    $v0, ($s0)
/* 0A50C0 800A44C0 00000000 */  nop   
/* 0A50C4 800A44C4 8FA9003C */  lw    $t1, 0x3c($sp)
.L800A44C8:
/* 0A50C8 800A44C8 2408000A */  li    $t0, 10
/* 0A50CC 800A44CC 0128001A */  div   $zero, $t1, $t0
/* 0A50D0 800A44D0 15000002 */  bnez  $t0, .L800A44DC
/* 0A50D4 800A44D4 00000000 */   nop   
/* 0A50D8 800A44D8 0007000D */  break 7
.L800A44DC:
/* 0A50DC 800A44DC 2401FFFF */  li    $at, -1
/* 0A50E0 800A44E0 15010004 */  bne   $t0, $at, .L800A44F4
/* 0A50E4 800A44E4 3C018000 */   lui   $at, 0x8000
/* 0A50E8 800A44E8 15210002 */  bne   $t1, $at, .L800A44F4
/* 0A50EC 800A44EC 00000000 */   nop   
/* 0A50F0 800A44F0 0006000D */  break 6
.L800A44F4:
/* 0A50F4 800A44F4 00001812 */  mflo  $v1
/* 0A50F8 800A44F8 1060001A */  beqz  $v1, .L800A4564
/* 0A50FC 800A44FC 00000000 */   nop   
/* 0A5100 800A4500 0128001A */  div   $zero, $t1, $t0
/* 0A5104 800A4504 A4430118 */  sh    $v1, 0x118($v0)
/* 0A5108 800A4508 8E190000 */  lw    $t9, ($s0)
/* 0A510C 800A450C 15000002 */  bnez  $t0, .L800A4518
/* 0A5110 800A4510 00000000 */   nop   
/* 0A5114 800A4514 0007000D */  break 7
.L800A4518:
/* 0A5118 800A4518 2401FFFF */  li    $at, -1
/* 0A511C 800A451C 15010004 */  bne   $t0, $at, .L800A4530
/* 0A5120 800A4520 3C018000 */   lui   $at, 0x8000
/* 0A5124 800A4524 15210002 */  bne   $t1, $at, .L800A4530
/* 0A5128 800A4528 00000000 */   nop   
/* 0A512C 800A452C 0006000D */  break 6
.L800A4530:
/* 0A5130 800A4530 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5134 800A4534 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A5138 800A4538 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A513C 800A453C 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A5140 800A4540 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A5144 800A4544 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5148 800A4548 0000C010 */  mfhi  $t8
/* 0A514C 800A454C A7380138 */  sh    $t8, 0x138($t9)
/* 0A5150 800A4550 8E070000 */  lw    $a3, ($s0)
/* 0A5154 800A4554 0C02A980 */  jal   func_800AA600
/* 0A5158 800A4558 24E70120 */   addiu $a3, $a3, 0x120
/* 0A515C 800A455C 1000000F */  b     .L800A459C
/* 0A5160 800A4560 8E070000 */   lw    $a3, ($s0)
.L800A4564:
/* 0A5164 800A4564 0128001A */  div   $zero, $t1, $t0
/* 0A5168 800A4568 15000002 */  bnez  $t0, .L800A4574
/* 0A516C 800A456C 00000000 */   nop   
/* 0A5170 800A4570 0007000D */  break 7
.L800A4574:
/* 0A5174 800A4574 2401FFFF */  li    $at, -1
/* 0A5178 800A4578 15010004 */  bne   $t0, $at, .L800A458C
/* 0A517C 800A457C 3C018000 */   lui   $at, 0x8000
/* 0A5180 800A4580 15210002 */  bne   $t1, $at, .L800A458C
/* 0A5184 800A4584 00000000 */   nop   
/* 0A5188 800A4588 0006000D */  break 6
.L800A458C:
/* 0A518C 800A458C 00005010 */  mfhi  $t2
/* 0A5190 800A4590 A44A0118 */  sh    $t2, 0x118($v0)
/* 0A5194 800A4594 00000000 */  nop   
/* 0A5198 800A4598 8E070000 */  lw    $a3, ($s0)
.L800A459C:
/* 0A519C 800A459C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A51A0 800A45A0 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A51A4 800A45A4 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A51A8 800A45A8 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A51AC 800A45AC 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A51B0 800A45B0 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A51B4 800A45B4 0C02A980 */  jal   func_800AA600
/* 0A51B8 800A45B8 24E70100 */   addiu $a3, $a3, 0x100
/* 0A51BC 800A45BC 3C038012 */  lui   $v1, %hi(gHUDCurrDisplayList) # $v1, 0x8012
/* 0A51C0 800A45C0 8C636CFC */  lw    $v1, %lo(gHUDCurrDisplayList)($v1)
/* 0A51C4 800A45C4 3C018012 */  lui   $at, %hi(gHUDCurrDisplayList) # $at, 0x8012
/* 0A51C8 800A45C8 246C0008 */  addiu $t4, $v1, 8
/* 0A51CC 800A45CC AC2C6CFC */  sw    $t4, %lo(gHUDCurrDisplayList)($at)
/* 0A51D0 800A45D0 3C0BFA00 */  lui   $t3, 0xfa00
/* 0A51D4 800A45D4 240DFFFF */  li    $t5, -1
/* 0A51D8 800A45D8 AC6D0004 */  sw    $t5, 4($v1)
/* 0A51DC 800A45DC AC6B0000 */  sw    $t3, ($v1)
.L800A45E0:
/* 0A51E0 800A45E0 8FBF001C */  lw    $ra, 0x1c($sp)
.L800A45E4:
/* 0A51E4 800A45E4 8FB00018 */  lw    $s0, 0x18($sp)
/* 0A51E8 800A45E8 03E00008 */  jr    $ra
/* 0A51EC 800A45EC 27BD0040 */   addiu $sp, $sp, 0x40

