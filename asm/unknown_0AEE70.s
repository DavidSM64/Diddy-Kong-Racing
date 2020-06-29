.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

#glabel func_800AE270
#/* 0AEE70 800AE270 27BDFFE8 */  addiu $sp, $sp, -0x18
#/* 0AEE74 800AE274 AFBF0014 */  sw    $ra, 0x14($sp)
#/* 0AEE78 800AE278 0C02B8DD */  jal   func_800AE374
#/* 0AEE7C 800AE27C 00000000 */   nop   
#/* 0AEE80 800AE280 0C02B90E */  jal   func_800AE438
#/* 0AEE84 800AE284 00000000 */   nop   
#/* 0AEE88 800AE288 0C02B8B6 */  jal   func_800AE2D8
#/* 0AEE8C 800AE28C 00000000 */   nop   
#/* 0AEE90 800AE290 8FBF0014 */  lw    $ra, 0x14($sp)
#/* 0AEE94 800AE294 27BD0018 */  addiu $sp, $sp, 0x18
#/* 0AEE98 800AE298 03E00008 */  jr    $ra
#/* 0AEE9C 800AE29C 00000000 */   nop   

#/* 0AEEA0 800AE2A0 27BDFFE8 */  addiu $sp, $sp, -0x18
#/* 0AEEA4 800AE2A4 AFBF0014 */  sw    $ra, 0x14($sp)
#/* 0AEEA8 800AE2A8 0C02B8DD */  jal   func_800AE374
#/* 0AEEAC 800AE2AC 00000000 */   nop   
#/* 0AEEB0 800AE2B0 0C02B90E */  jal   func_800AE438
#/* 0AEEB4 800AE2B4 00000000 */   nop   
#/* 0AEEB8 800AE2B8 0C02B924 */  jal   func_800AE490
#/* 0AEEBC 800AE2BC 00000000 */   nop   
#/* 0AEEC0 800AE2C0 0C02B8B6 */  jal   func_800AE2D8
#/* 0AEEC4 800AE2C4 00000000 */   nop   
#/* 0AEEC8 800AE2C8 8FBF0014 */  lw    $ra, 0x14($sp)
#/* 0AEECC 800AE2CC 27BD0018 */  addiu $sp, $sp, 0x18
#/* 0AEED0 800AE2D0 03E00008 */  jr    $ra
#/* 0AEED4 800AE2D4 00000000 */   nop   

#glabel func_800AE2D8
#/* 0AEED8 800AE2D8 27BDFFD8 */  addiu $sp, $sp, -0x28
#/* 0AEEDC 800AE2DC AFB30020 */  sw    $s3, 0x20($sp)
#/* 0AEEE0 800AE2E0 3C13800E */  lui   $s3, %hi(D_800E2E60) # $s3, 0x800e
#/* 0AEEE4 800AE2E4 26732E60 */  addiu $s3, %lo(D_800E2E60) # addiu $s3, $s3, 0x2e60
#/* 0AEEE8 800AE2E8 8E640000 */  lw    $a0, ($s3)
#/* 0AEEEC 800AE2EC AFBF0024 */  sw    $ra, 0x24($sp)
#/* 0AEEF0 800AE2F0 AFB2001C */  sw    $s2, 0x1c($sp)
#/* 0AEEF4 800AE2F4 AFB10018 */  sw    $s1, 0x18($sp)
#/* 0AEEF8 800AE2F8 10800017 */  beqz  $a0, .L800AE358
#/* 0AEEFC 800AE2FC AFB00014 */   sw    $s0, 0x14($sp)
#/* 0AEF00 800AE300 3C12800E */  lui   $s2, %hi(D_800E2E64) # $s2, 0x800e
#/* 0AEF04 800AE304 26522E64 */  addiu $s2, %lo(D_800E2E64) # addiu $s2, $s2, 0x2e64
#/* 0AEF08 800AE308 8E4E0000 */  lw    $t6, ($s2)
#/* 0AEF0C 800AE30C 00008025 */  move  $s0, $zero
#/* 0AEF10 800AE310 19C0000E */  blez  $t6, .L800AE34C
#/* 0AEF14 800AE314 00008825 */   move  $s1, $zero
#.L800AE318:
#/* 0AEF18 800AE318 8E6F0000 */  lw    $t7, ($s3)
#/* 0AEF1C 800AE31C 00000000 */  nop   
#/* 0AEF20 800AE320 01F1C021 */  addu  $t8, $t7, $s1
#/* 0AEF24 800AE324 8F040000 */  lw    $a0, ($t8)
#/* 0AEF28 800AE328 0C01F32C */  jal   func_8007CCB0
#/* 0AEF2C 800AE32C 00000000 */   nop   
#/* 0AEF30 800AE330 8E590000 */  lw    $t9, ($s2)
#/* 0AEF34 800AE334 26100001 */  addiu $s0, $s0, 1
#/* 0AEF38 800AE338 0219082A */  slt   $at, $s0, $t9
#/* 0AEF3C 800AE33C 1420FFF6 */  bnez  $at, .L800AE318
#/* 0AEF40 800AE340 26310004 */   addiu $s1, $s1, 4
#/* 0AEF44 800AE344 8E640000 */  lw    $a0, ($s3)
#/* 0AEF48 800AE348 00000000 */  nop   
#.L800AE34C:
#/* 0AEF4C 800AE34C 0C01C450 */  jal   func_80071140
#/* 0AEF50 800AE350 00000000 */   nop   
#/* 0AEF54 800AE354 AE600000 */  sw    $zero, ($s3)
#.L800AE358:
#/* 0AEF58 800AE358 8FBF0024 */  lw    $ra, 0x24($sp)
#/* 0AEF5C 800AE35C 8FB00014 */  lw    $s0, 0x14($sp)
#/* 0AEF60 800AE360 8FB10018 */  lw    $s1, 0x18($sp)
#/* 0AEF64 800AE364 8FB2001C */  lw    $s2, 0x1c($sp)
#/* 0AEF68 800AE368 8FB30020 */  lw    $s3, 0x20($sp)
#/* 0AEF6C 800AE36C 03E00008 */  jr    $ra
#/* 0AEF70 800AE370 27BD0028 */   addiu $sp, $sp, 0x28

#glabel func_800AE374
#/* 0AEF74 800AE374 3C04800E */  lui   $a0, %hi(D_800E2CA8) # $a0, 0x800e
#/* 0AEF78 800AE378 8C842CA8 */  lw    $a0, %lo(D_800E2CA8)($a0)
#/* 0AEF7C 800AE37C 27BDFFE8 */  addiu $sp, $sp, -0x18
#/* 0AEF80 800AE380 10800005 */  beqz  $a0, .L800AE398
#/* 0AEF84 800AE384 AFBF0014 */   sw    $ra, 0x14($sp)
#/* 0AEF88 800AE388 0C01C450 */  jal   func_80071140
#/* 0AEF8C 800AE38C 00000000 */   nop   
#/* 0AEF90 800AE390 3C01800E */  lui   $at, %hi(D_800E2CA8) # $at, 0x800e
#/* 0AEF94 800AE394 AC202CA8 */  sw    $zero, %lo(D_800E2CA8)($at)
#.L800AE398:
#/* 0AEF98 800AE398 3C04800E */  lui   $a0, %hi(D_800E2CB4) # $a0, 0x800e
#/* 0AEF9C 800AE39C 8C842CB4 */  lw    $a0, %lo(D_800E2CB4)($a0)
#/* 0AEFA0 800AE3A0 00000000 */  nop   
#/* 0AEFA4 800AE3A4 10800005 */  beqz  $a0, .L800AE3BC
#/* 0AEFA8 800AE3A8 00000000 */   nop   
#/* 0AEFAC 800AE3AC 0C01C450 */  jal   func_80071140
#/* 0AEFB0 800AE3B0 00000000 */   nop   
#/* 0AEFB4 800AE3B4 3C01800E */  lui   $at, %hi(D_800E2CB4) # $at, 0x800e
#/* 0AEFB8 800AE3B8 AC202CB4 */  sw    $zero, %lo(D_800E2CB4)($at)
#.L800AE3BC:
#/* 0AEFBC 800AE3BC 3C04800E */  lui   $a0, %hi(D_800E2CC0) # $a0, 0x800e
#/* 0AEFC0 800AE3C0 8C842CC0 */  lw    $a0, %lo(D_800E2CC0)($a0)
#/* 0AEFC4 800AE3C4 00000000 */  nop   
#/* 0AEFC8 800AE3C8 10800005 */  beqz  $a0, .L800AE3E0
#/* 0AEFCC 800AE3CC 00000000 */   nop   
#/* 0AEFD0 800AE3D0 0C01C450 */  jal   func_80071140
#/* 0AEFD4 800AE3D4 00000000 */   nop   
#/* 0AEFD8 800AE3D8 3C01800E */  lui   $at, %hi(D_800E2CC0) # $at, 0x800e
#/* 0AEFDC 800AE3DC AC202CC0 */  sw    $zero, %lo(D_800E2CC0)($at)
#.L800AE3E0:
#/* 0AEFE0 800AE3E0 3C04800E */  lui   $a0, %hi(D_800E2CCC) # $a0, 0x800e
#/* 0AEFE4 800AE3E4 8C842CCC */  lw    $a0, %lo(D_800E2CCC)($a0)
#/* 0AEFE8 800AE3E8 00000000 */  nop   
#/* 0AEFEC 800AE3EC 10800005 */  beqz  $a0, .L800AE404
#/* 0AEFF0 800AE3F0 00000000 */   nop   
#/* 0AEFF4 800AE3F4 0C01C450 */  jal   func_80071140
#/* 0AEFF8 800AE3F8 00000000 */   nop   
#/* 0AEFFC 800AE3FC 3C01800E */  lui   $at, %hi(D_800E2CCC) # $at, 0x800e
#/* 0AF000 800AE400 AC202CCC */  sw    $zero, %lo(D_800E2CCC)($at)
#.L800AE404:
#/* 0AF004 800AE404 3C04800E */  lui   $a0, %hi(D_800E2CD8) # $a0, 0x800e
#/* 0AF008 800AE408 8C842CD8 */  lw    $a0, %lo(D_800E2CD8)($a0)
#/* 0AF00C 800AE40C 00000000 */  nop   
#/* 0AF010 800AE410 10800006 */  beqz  $a0, .L800AE42C
#/* 0AF014 800AE414 8FBF0014 */   lw    $ra, 0x14($sp)
#/* 0AF018 800AE418 0C01C450 */  jal   func_80071140
#/* 0AF01C 800AE41C 00000000 */   nop   
#/* 0AF020 800AE420 3C01800E */  lui   $at, %hi(D_800E2CD8) # $at, 0x800e
#/* 0AF024 800AE424 AC202CD8 */  sw    $zero, %lo(D_800E2CD8)($at)
#/* 0AF028 800AE428 8FBF0014 */  lw    $ra, 0x14($sp)
#.L800AE42C:
#/* 0AF02C 800AE42C 27BD0018 */  addiu $sp, $sp, 0x18
#/* 0AF030 800AE430 03E00008 */  jr    $ra
#/* 0AF034 800AE434 00000000 */   nop   

#glabel func_800AE438
#/* 0AF038 800AE438 3C04800E */  lui   $a0, %hi(D_800E2CE0) # $a0, 0x800e
#/* 0AF03C 800AE43C 8C842CE0 */  lw    $a0, %lo(D_800E2CE0)($a0)
#/* 0AF040 800AE440 27BDFFE8 */  addiu $sp, $sp, -0x18
#/* 0AF044 800AE444 10800005 */  beqz  $a0, .L800AE45C
#/* 0AF048 800AE448 AFBF0014 */   sw    $ra, 0x14($sp)
#/* 0AF04C 800AE44C 0C01C450 */  jal   func_80071140
#/* 0AF050 800AE450 00000000 */   nop   
#/* 0AF054 800AE454 3C01800E */  lui   $at, %hi(D_800E2CE0) # $at, 0x800e
#/* 0AF058 800AE458 AC202CE0 */  sw    $zero, %lo(D_800E2CE0)($at)
#.L800AE45C:
#/* 0AF05C 800AE45C 3C04800E */  lui   $a0, %hi(D_800E2CE4) # $a0, 0x800e
#/* 0AF060 800AE460 8C842CE4 */  lw    $a0, %lo(D_800E2CE4)($a0)
#/* 0AF064 800AE464 00000000 */  nop   
#/* 0AF068 800AE468 10800006 */  beqz  $a0, .L800AE484
#/* 0AF06C 800AE46C 8FBF0014 */   lw    $ra, 0x14($sp)
#/* 0AF070 800AE470 0C01C450 */  jal   func_80071140
#/* 0AF074 800AE474 00000000 */   nop   
#/* 0AF078 800AE478 3C01800E */  lui   $at, %hi(D_800E2CE4) # $at, 0x800e
#/* 0AF07C 800AE47C AC202CE4 */  sw    $zero, %lo(D_800E2CE4)($at)
#/* 0AF080 800AE480 8FBF0014 */  lw    $ra, 0x14($sp)
#.L800AE484:
#/* 0AF084 800AE484 27BD0018 */  addiu $sp, $sp, 0x18
#/* 0AF088 800AE488 03E00008 */  jr    $ra
#/* 0AF08C 800AE48C 00000000 */   nop   

#glabel func_800AE490
#/* 0AF090 800AE490 3C04800E */  lui   $a0, %hi(D_800E2CEC) # $a0, 0x800e
#/* 0AF094 800AE494 8C842CEC */  lw    $a0, %lo(D_800E2CEC)($a0)
#/* 0AF098 800AE498 27BDFFE8 */  addiu $sp, $sp, -0x18
#/* 0AF09C 800AE49C 10800005 */  beqz  $a0, .L800AE4B4
#/* 0AF0A0 800AE4A0 AFBF0014 */   sw    $ra, 0x14($sp)
#/* 0AF0A4 800AE4A4 0C01C450 */  jal   func_80071140
#/* 0AF0A8 800AE4A8 00000000 */   nop   
#/* 0AF0AC 800AE4AC 3C01800E */  lui   $at, %hi(D_800E2CEC) # $at, 0x800e
#/* 0AF0B0 800AE4B0 AC202CEC */  sw    $zero, %lo(D_800E2CEC)($at)
#.L800AE4B4:
#/* 0AF0B4 800AE4B4 3C04800E */  lui   $a0, %hi(D_800E2CF0) # $a0, 0x800e
#/* 0AF0B8 800AE4B8 8C842CF0 */  lw    $a0, %lo(D_800E2CF0)($a0)
#/* 0AF0BC 800AE4BC 00000000 */  nop   
#/* 0AF0C0 800AE4C0 10800005 */  beqz  $a0, .L800AE4D8
#/* 0AF0C4 800AE4C4 00000000 */   nop   
#/* 0AF0C8 800AE4C8 0C01C450 */  jal   func_80071140
#/* 0AF0CC 800AE4CC 00000000 */   nop   
#/* 0AF0D0 800AE4D0 3C01800E */  lui   $at, %hi(D_800E2CF0) # $at, 0x800e
#/* 0AF0D4 800AE4D4 AC202CF0 */  sw    $zero, %lo(D_800E2CF0)($at)
#.L800AE4D8:
#/* 0AF0D8 800AE4D8 3C04800E */  lui   $a0, %hi(D_800E2CF8) # $a0, 0x800e
#/* 0AF0DC 800AE4DC 8C842CF8 */  lw    $a0, %lo(D_800E2CF8)($a0)
#/* 0AF0E0 800AE4E0 00000000 */  nop   
#/* 0AF0E4 800AE4E4 10800005 */  beqz  $a0, .L800AE4FC
#/* 0AF0E8 800AE4E8 00000000 */   nop   
#/* 0AF0EC 800AE4EC 0C01C450 */  jal   func_80071140
#/* 0AF0F0 800AE4F0 00000000 */   nop   
#/* 0AF0F4 800AE4F4 3C01800E */  lui   $at, %hi(D_800E2CF8) # $at, 0x800e
#/* 0AF0F8 800AE4F8 AC202CF8 */  sw    $zero, %lo(D_800E2CF8)($at)
#.L800AE4FC:
#/* 0AF0FC 800AE4FC 3C04800E */  lui   $a0, %hi(D_800E2CFC) # $a0, 0x800e
#/* 0AF100 800AE500 8C842CFC */  lw    $a0, %lo(D_800E2CFC)($a0)
#/* 0AF104 800AE504 00000000 */  nop   
#/* 0AF108 800AE508 10800006 */  beqz  $a0, .L800AE524
#/* 0AF10C 800AE50C 8FBF0014 */   lw    $ra, 0x14($sp)
#/* 0AF110 800AE510 0C01C450 */  jal   func_80071140
#/* 0AF114 800AE514 00000000 */   nop   
#/* 0AF118 800AE518 3C01800E */  lui   $at, %hi(D_800E2CFC) # $at, 0x800e
#/* 0AF11C 800AE51C AC202CFC */  sw    $zero, %lo(D_800E2CFC)($at)
#/* 0AF120 800AE520 8FBF0014 */  lw    $ra, 0x14($sp)
#.L800AE524:
#/* 0AF124 800AE524 27BD0018 */  addiu $sp, $sp, 0x18
#/* 0AF128 800AE528 03E00008 */  jr    $ra
#/* 0AF12C 800AE52C 00000000 */   nop   

glabel func_800AE530
/* 0AF130 800AE530 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0AF134 800AE534 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0AF138 800AE538 AFB50028 */  sw    $s5, 0x28($sp)
/* 0AF13C 800AE53C AFB40024 */  sw    $s4, 0x24($sp)
/* 0AF140 800AE540 AFB30020 */  sw    $s3, 0x20($sp)
/* 0AF144 800AE544 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0AF148 800AE548 AFB10018 */  sw    $s1, 0x18($sp)
/* 0AF14C 800AE54C 0C02B924 */  jal   func_800AE490
/* 0AF150 800AE550 AFB00014 */   sw    $s0, 0x14($sp)
/* 0AF154 800AE554 0C01DB16 */  jal   func_80076C58
/* 0AF158 800AE558 24040028 */   li    $a0, 40
/* 0AF15C 800AE55C 3C05800E */  lui   $a1, %hi(D_800E2CE8) # $a1, 0x800e
/* 0AF160 800AE560 2406FFFF */  li    $a2, -1
/* 0AF164 800AE564 3C12800E */  lui   $s2, %hi(D_800E2CF0) # $s2, 0x800e
/* 0AF168 800AE568 26522CF0 */  addiu $s2, %lo(D_800E2CF0) # addiu $s2, $s2, 0x2cf0
/* 0AF16C 800AE56C 24A52CE8 */  addiu $a1, %lo(D_800E2CE8) # addiu $a1, $a1, 0x2ce8
/* 0AF170 800AE570 00067080 */  sll   $t6, $a2, 2
/* 0AF174 800AE574 AE420000 */  sw    $v0, ($s2)
/* 0AF178 800AE578 ACA60000 */  sw    $a2, ($a1)
/* 0AF17C 800AE57C 004E7821 */  addu  $t7, $v0, $t6
/* 0AF180 800AE580 8DF80004 */  lw    $t8, 4($t7)
/* 0AF184 800AE584 00C01825 */  move  $v1, $a2
/* 0AF188 800AE588 10D80009 */  beq   $a2, $t8, .L800AE5B0
/* 0AF18C 800AE58C 00402025 */   move  $a0, $v0
/* 0AF190 800AE590 24790001 */  addiu $t9, $v1, 1
.L800AE594:
/* 0AF194 800AE594 00194080 */  sll   $t0, $t9, 2
/* 0AF198 800AE598 00884821 */  addu  $t1, $a0, $t0
/* 0AF19C 800AE59C ACB90000 */  sw    $t9, ($a1)
/* 0AF1A0 800AE5A0 8D2A0004 */  lw    $t2, 4($t1)
/* 0AF1A4 800AE5A4 03201825 */  move  $v1, $t9
/* 0AF1A8 800AE5A8 14CAFFFA */  bne   $a2, $t2, .L800AE594
/* 0AF1AC 800AE5AC 24790001 */   addiu $t9, $v1, 1
.L800AE5B0:
/* 0AF1B0 800AE5B0 0C01DB16 */  jal   func_80076C58
/* 0AF1B4 800AE5B4 24040029 */   li    $a0, 41
/* 0AF1B8 800AE5B8 3C05800E */  lui   $a1, %hi(D_800E2CE8) # $a1, 0x800e
/* 0AF1BC 800AE5BC 24A52CE8 */  addiu $a1, %lo(D_800E2CE8) # addiu $a1, $a1, 0x2ce8
/* 0AF1C0 800AE5C0 8CAB0000 */  lw    $t3, ($a1)
/* 0AF1C4 800AE5C4 3C03800E */  lui   $v1, %hi(D_800E2CEC) # $v1, 0x800e
/* 0AF1C8 800AE5C8 24632CEC */  addiu $v1, %lo(D_800E2CEC) # addiu $v1, $v1, 0x2cec
/* 0AF1CC 800AE5CC AC620000 */  sw    $v0, ($v1)
/* 0AF1D0 800AE5D0 1960000F */  blez  $t3, .L800AE610
/* 0AF1D4 800AE5D4 00008825 */   move  $s1, $zero
/* 0AF1D8 800AE5D8 00008025 */  move  $s0, $zero
.L800AE5DC:
/* 0AF1DC 800AE5DC 8E4C0000 */  lw    $t4, ($s2)
/* 0AF1E0 800AE5E0 8C6E0000 */  lw    $t6, ($v1)
/* 0AF1E4 800AE5E4 01901021 */  addu  $v0, $t4, $s0
/* 0AF1E8 800AE5E8 8C4D0000 */  lw    $t5, ($v0)
/* 0AF1EC 800AE5EC 26310001 */  addiu $s1, $s1, 1
/* 0AF1F0 800AE5F0 01AE7821 */  addu  $t7, $t5, $t6
/* 0AF1F4 800AE5F4 AC4F0000 */  sw    $t7, ($v0)
/* 0AF1F8 800AE5F8 8CB80000 */  lw    $t8, ($a1)
/* 0AF1FC 800AE5FC 26100004 */  addiu $s0, $s0, 4
/* 0AF200 800AE600 0238082A */  slt   $at, $s1, $t8
/* 0AF204 800AE604 1420FFF5 */  bnez  $at, .L800AE5DC
/* 0AF208 800AE608 00000000 */   nop   
/* 0AF20C 800AE60C 00008825 */  move  $s1, $zero
.L800AE610:
/* 0AF210 800AE610 0C01DB16 */  jal   func_80076C58
/* 0AF214 800AE614 2404002A */   li    $a0, 42
/* 0AF218 800AE618 2406FFFF */  li    $a2, -1
/* 0AF21C 800AE61C 3C12800E */  lui   $s2, %hi(D_800E2CF4) # $s2, 0x800e
/* 0AF220 800AE620 3C13800E */  lui   $s3, %hi(D_800E2CFC) # $s3, 0x800e
/* 0AF224 800AE624 26732CFC */  addiu $s3, %lo(D_800E2CFC) # addiu $s3, $s3, 0x2cfc
/* 0AF228 800AE628 26522CF4 */  addiu $s2, %lo(D_800E2CF4) # addiu $s2, $s2, 0x2cf4
/* 0AF22C 800AE62C 0006C880 */  sll   $t9, $a2, 2
/* 0AF230 800AE630 AE620000 */  sw    $v0, ($s3)
/* 0AF234 800AE634 AE460000 */  sw    $a2, ($s2)
/* 0AF238 800AE638 00594021 */  addu  $t0, $v0, $t9
/* 0AF23C 800AE63C 8D090004 */  lw    $t1, 4($t0)
/* 0AF240 800AE640 00C01825 */  move  $v1, $a2
/* 0AF244 800AE644 10C90009 */  beq   $a2, $t1, .L800AE66C
/* 0AF248 800AE648 00402025 */   move  $a0, $v0
/* 0AF24C 800AE64C 246A0001 */  addiu $t2, $v1, 1
.L800AE650:
/* 0AF250 800AE650 000A5880 */  sll   $t3, $t2, 2
/* 0AF254 800AE654 008B6021 */  addu  $t4, $a0, $t3
/* 0AF258 800AE658 AE4A0000 */  sw    $t2, ($s2)
/* 0AF25C 800AE65C 8D8D0004 */  lw    $t5, 4($t4)
/* 0AF260 800AE660 01401825 */  move  $v1, $t2
/* 0AF264 800AE664 14CDFFFA */  bne   $a2, $t5, .L800AE650
/* 0AF268 800AE668 246A0001 */   addiu $t2, $v1, 1
.L800AE66C:
/* 0AF26C 800AE66C 0C01DB16 */  jal   func_80076C58
/* 0AF270 800AE670 2404002B */   li    $a0, 43
/* 0AF274 800AE674 8E4E0000 */  lw    $t6, ($s2)
/* 0AF278 800AE678 3C15800E */  lui   $s5, %hi(D_800E2CF8) # $s5, 0x800e
/* 0AF27C 800AE67C 26B52CF8 */  addiu $s5, %lo(D_800E2CF8) # addiu $s5, $s5, 0x2cf8
/* 0AF280 800AE680 19C00020 */  blez  $t6, .L800AE704
/* 0AF284 800AE684 AEA20000 */   sw    $v0, ($s5)
/* 0AF288 800AE688 00008025 */  move  $s0, $zero
/* 0AF28C 800AE68C 2414FFFF */  li    $s4, -1
.L800AE690:
/* 0AF290 800AE690 8E6F0000 */  lw    $t7, ($s3)
/* 0AF294 800AE694 8EB90000 */  lw    $t9, ($s5)
/* 0AF298 800AE698 01F01021 */  addu  $v0, $t7, $s0
/* 0AF29C 800AE69C 8C580000 */  lw    $t8, ($v0)
/* 0AF2A0 800AE6A0 00000000 */  nop   
/* 0AF2A4 800AE6A4 03194021 */  addu  $t0, $t8, $t9
/* 0AF2A8 800AE6A8 AC480000 */  sw    $t0, ($v0)
/* 0AF2AC 800AE6AC 8E690000 */  lw    $t1, ($s3)
/* 0AF2B0 800AE6B0 00000000 */  nop   
/* 0AF2B4 800AE6B4 01305021 */  addu  $t2, $t1, $s0
/* 0AF2B8 800AE6B8 8D4B0000 */  lw    $t3, ($t2)
/* 0AF2BC 800AE6BC 00000000 */  nop   
/* 0AF2C0 800AE6C0 8D63009C */  lw    $v1, 0x9c($t3)
/* 0AF2C4 800AE6C4 00000000 */  nop   
/* 0AF2C8 800AE6C8 12830009 */  beq   $s4, $v1, .L800AE6F0
/* 0AF2CC 800AE6CC 00000000 */   nop   
/* 0AF2D0 800AE6D0 0C0078A7 */  jal   func_8001E29C
/* 0AF2D4 800AE6D4 00602025 */   move  $a0, $v1
/* 0AF2D8 800AE6D8 8E6C0000 */  lw    $t4, ($s3)
/* 0AF2DC 800AE6DC 00000000 */  nop   
/* 0AF2E0 800AE6E0 01906821 */  addu  $t5, $t4, $s0
/* 0AF2E4 800AE6E4 8DAE0000 */  lw    $t6, ($t5)
/* 0AF2E8 800AE6E8 00000000 */  nop   
/* 0AF2EC 800AE6EC ADC2009C */  sw    $v0, 0x9c($t6)
.L800AE6F0:
/* 0AF2F0 800AE6F0 8E4F0000 */  lw    $t7, ($s2)
/* 0AF2F4 800AE6F4 26310001 */  addiu $s1, $s1, 1
/* 0AF2F8 800AE6F8 022F082A */  slt   $at, $s1, $t7
/* 0AF2FC 800AE6FC 1420FFE4 */  bnez  $at, .L800AE690
/* 0AF300 800AE700 26100004 */   addiu $s0, $s0, 4
.L800AE704:
/* 0AF304 800AE704 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0AF308 800AE708 8FB00014 */  lw    $s0, 0x14($sp)
/* 0AF30C 800AE70C 8FB10018 */  lw    $s1, 0x18($sp)
/* 0AF310 800AE710 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0AF314 800AE714 8FB30020 */  lw    $s3, 0x20($sp)
/* 0AF318 800AE718 8FB40024 */  lw    $s4, 0x24($sp)
/* 0AF31C 800AE71C 8FB50028 */  lw    $s5, 0x28($sp)
/* 0AF320 800AE720 03E00008 */  jr    $ra
/* 0AF324 800AE724 27BD0030 */   addiu $sp, $sp, 0x30

glabel func_800AE728
/* 0AF328 800AE728 27BDFF98 */  addiu $sp, $sp, -0x68
/* 0AF32C 800AE72C AFB70034 */  sw    $s7, 0x34($sp)
/* 0AF330 800AE730 AFB40028 */  sw    $s4, 0x28($sp)
/* 0AF334 800AE734 AFB30024 */  sw    $s3, 0x24($sp)
/* 0AF338 800AE738 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0AF33C 800AE73C 3C01800E */  lui   $at, %hi(D_800E2D00) # $at, 0x800e
/* 0AF340 800AE740 00808825 */  move  $s1, $a0
/* 0AF344 800AE744 00A09825 */  move  $s3, $a1
/* 0AF348 800AE748 00E0A025 */  move  $s4, $a3
/* 0AF34C 800AE74C 00C0B825 */  move  $s7, $a2
/* 0AF350 800AE750 AFBF003C */  sw    $ra, 0x3c($sp)
/* 0AF354 800AE754 AFBE0038 */  sw    $fp, 0x38($sp)
/* 0AF358 800AE758 AFB60030 */  sw    $s6, 0x30($sp)
/* 0AF35C 800AE75C AFB5002C */  sw    $s5, 0x2c($sp)
/* 0AF360 800AE760 AFB20020 */  sw    $s2, 0x20($sp)
/* 0AF364 800AE764 AFB00018 */  sw    $s0, 0x18($sp)
/* 0AF368 800AE768 04810002 */  bgez  $a0, .L800AE774
/* 0AF36C 800AE76C AC202D00 */   sw    $zero, %lo(D_800E2D00)($at)
/* 0AF370 800AE770 24110010 */  li    $s1, 16
.L800AE774:
/* 0AF374 800AE774 8FBE0078 */  lw    $fp, 0x78($sp)
/* 0AF378 800AE778 06610002 */  bgez  $s3, .L800AE784
/* 0AF37C 800AE77C 3C01800E */   lui   $at, %hi(D_800E2E4C) # $at, 0x800e
/* 0AF380 800AE780 24130010 */  li    $s3, 16
.L800AE784:
/* 0AF384 800AE784 06E10002 */  bgez  $s7, .L800AE790
/* 0AF388 800AE788 00000000 */   nop   
/* 0AF38C 800AE78C 241700D0 */  li    $s7, 208
.L800AE790:
/* 0AF390 800AE790 06810002 */  bgez  $s4, .L800AE79C
/* 0AF394 800AE794 00000000 */   nop   
/* 0AF398 800AE798 241400A0 */  li    $s4, 160
.L800AE79C:
/* 0AF39C 800AE79C 07C10002 */  bgez  $fp, .L800AE7A8
/* 0AF3A0 800AE7A0 00000000 */   nop   
/* 0AF3A4 800AE7A4 241E0040 */  li    $fp, 64
.L800AE7A8:
/* 0AF3A8 800AE7A8 AC312E4C */  sw    $s1, %lo(D_800E2E4C)($at)
/* 0AF3AC 800AE7AC 3C01800E */  lui   $at, %hi(D_800E2CA4) # $at, 0x800e
/* 0AF3B0 800AE7B0 AC202CA4 */  sw    $zero, %lo(D_800E2CA4)($at)
/* 0AF3B4 800AE7B4 3C01800E */  lui   $at, %hi(D_800E2E50) # $at, 0x800e
/* 0AF3B8 800AE7B8 AC332E50 */  sw    $s3, %lo(D_800E2E50)($at)
/* 0AF3BC 800AE7BC 3C01800E */  lui   $at, %hi(D_800E2CB0) # $at, 0x800e
/* 0AF3C0 800AE7C0 AC202CB0 */  sw    $zero, %lo(D_800E2CB0)($at)
/* 0AF3C4 800AE7C4 3C01800E */  lui   $at, %hi(D_800E2E54) # $at, 0x800e
/* 0AF3C8 800AE7C8 AC372E54 */  sw    $s7, %lo(D_800E2E54)($at)
/* 0AF3CC 800AE7CC 3C01800E */  lui   $at, %hi(D_800E2CBC) # $at, 0x800e
/* 0AF3D0 800AE7D0 AC202CBC */  sw    $zero, %lo(D_800E2CBC)($at)
/* 0AF3D4 800AE7D4 3C01800E */  lui   $at, %hi(D_800E2E58) # $at, 0x800e
/* 0AF3D8 800AE7D8 AC342E58 */  sw    $s4, %lo(D_800E2E58)($at)
/* 0AF3DC 800AE7DC 3C01800E */  lui   $at, %hi(D_800E2CC8) # $at, 0x800e
/* 0AF3E0 800AE7E0 AC202CC8 */  sw    $zero, %lo(D_800E2CC8)($at)
/* 0AF3E4 800AE7E4 3C01800E */  lui   $at, %hi(D_800E2E5C) # $at, 0x800e
/* 0AF3E8 800AE7E8 AC3E2E5C */  sw    $fp, %lo(D_800E2E5C)($at)
/* 0AF3EC 800AE7EC 3C01800E */  lui   $at, %hi(D_800E2CD4) # $at, 0x800e
/* 0AF3F0 800AE7F0 0C02B90E */  jal   func_800AE438
/* 0AF3F4 800AE7F4 AC202CD4 */   sw    $zero, %lo(D_800E2CD4)($at)
/* 0AF3F8 800AE7F8 00117080 */  sll   $t6, $s1, 2
/* 0AF3FC 800AE7FC 00144880 */  sll   $t1, $s4, 2
/* 0AF400 800AE800 01344823 */  subu  $t1, $t1, $s4
/* 0AF404 800AE804 01D17023 */  subu  $t6, $t6, $s1
/* 0AF408 800AE808 00137880 */  sll   $t7, $s3, 2
/* 0AF40C 800AE80C 01CFC021 */  addu  $t8, $t6, $t7
/* 0AF410 800AE810 00094840 */  sll   $t1, $t1, 1
/* 0AF414 800AE814 03095021 */  addu  $t2, $t8, $t1
/* 0AF418 800AE818 001E5900 */  sll   $t3, $fp, 4
/* 0AF41C 800AE81C 014B2021 */  addu  $a0, $t2, $t3
/* 0AF420 800AE820 3C128080 */  lui   $s2, (0x80808080 >> 16) # lui $s2, 0x8080
/* 0AF424 800AE824 00046080 */  sll   $t4, $a0, 2
/* 0AF428 800AE828 36528080 */  ori   $s2, (0x80808080 & 0xFFFF) # ori $s2, $s2, 0x8080
/* 0AF42C 800AE82C 01846021 */  addu  $t4, $t4, $a0
/* 0AF430 800AE830 000C2040 */  sll   $a0, $t4, 1
/* 0AF434 800AE834 02402825 */  move  $a1, $s2
/* 0AF438 800AE838 0C01C327 */  jal   func_80070C9C
/* 0AF43C 800AE83C 00008025 */   move  $s0, $zero
/* 0AF440 800AE840 00136840 */  sll   $t5, $s3, 1
/* 0AF444 800AE844 022D7021 */  addu  $t6, $s1, $t5
/* 0AF448 800AE848 01D02021 */  addu  $a0, $t6, $s0
/* 0AF44C 800AE84C 3C01800E */  lui   $at, %hi(D_800E2CE0) # $at, 0x800e
/* 0AF450 800AE850 00047900 */  sll   $t7, $a0, 4
/* 0AF454 800AE854 AC222CE0 */  sw    $v0, %lo(D_800E2CE0)($at)
/* 0AF458 800AE858 01E02025 */  move  $a0, $t7
/* 0AF45C 800AE85C 0C01C327 */  jal   func_80070C9C
/* 0AF460 800AE860 02402825 */   move  $a1, $s2
/* 0AF464 800AE864 3C10800E */  lui   $s0, %hi(D_800E2CE4) # $s0, 0x800e
/* 0AF468 800AE868 26102CE4 */  addiu $s0, %lo(D_800E2CE4) # addiu $s0, $s0, 0x2ce4
/* 0AF46C 800AE86C AE020000 */  sw    $v0, ($s0)
/* 0AF470 800AE870 3C01800E */  lui   $at, %hi(D_800E2CDC) # $at, 0x800e
/* 0AF474 800AE874 0C02B8DD */  jal   func_800AE374
/* 0AF478 800AE878 AC202CDC */   sw    $zero, %lo(D_800E2CDC)($at)
/* 0AF47C 800AE87C 3C18800E */  lui   $t8, %hi(D_800E2E4C) # $t8, 0x800e
/* 0AF480 800AE880 8F182E4C */  lw    $t8, %lo(D_800E2E4C)($t8)
/* 0AF484 800AE884 00000000 */  nop   
/* 0AF488 800AE888 1B000008 */  blez  $t8, .L800AE8AC
/* 0AF48C 800AE88C 3C01800E */   lui   $at, %hi(D_800E2CA0) # $at, 0x800e
/* 0AF490 800AE890 AC202CA0 */  sw    $zero, %lo(D_800E2CA0)($at)
/* 0AF494 800AE894 001121C0 */  sll   $a0, $s1, 7
/* 0AF498 800AE898 0C01C327 */  jal   func_80070C9C
/* 0AF49C 800AE89C 02402825 */   move  $a1, $s2
/* 0AF4A0 800AE8A0 3C15800E */  lui   $s5, %hi(D_800E2CA8) # $s5, 0x800e
/* 0AF4A4 800AE8A4 26B52CA8 */  addiu $s5, %lo(D_800E2CA8) # addiu $s5, $s5, 0x2ca8
/* 0AF4A8 800AE8A8 AEA20000 */  sw    $v0, ($s5)
.L800AE8AC:
/* 0AF4AC 800AE8AC 3C19800E */  lui   $t9, %hi(D_800E2E50) # $t9, 0x800e
/* 0AF4B0 800AE8B0 8F392E50 */  lw    $t9, %lo(D_800E2E50)($t9)
/* 0AF4B4 800AE8B4 3C15800E */  lui   $s5, %hi(D_800E2CA8) # $s5, 0x800e
/* 0AF4B8 800AE8B8 1B200009 */  blez  $t9, .L800AE8E0
/* 0AF4BC 800AE8BC 26B52CA8 */   addiu $s5, %lo(D_800E2CA8) # addiu $s5, $s5, 0x2ca8
/* 0AF4C0 800AE8C0 3C01800E */  lui   $at, %hi(D_800E2CAC) # $at, 0x800e
/* 0AF4C4 800AE8C4 AC202CAC */  sw    $zero, %lo(D_800E2CAC)($at)
/* 0AF4C8 800AE8C8 001321C0 */  sll   $a0, $s3, 7
/* 0AF4CC 800AE8CC 0C01C327 */  jal   func_80070C9C
/* 0AF4D0 800AE8D0 02402825 */   move  $a1, $s2
/* 0AF4D4 800AE8D4 3C16800E */  lui   $s6, %hi(D_800E2CB4) # $s6, 0x800e
/* 0AF4D8 800AE8D8 26D62CB4 */  addiu $s6, %lo(D_800E2CB4) # addiu $s6, $s6, 0x2cb4
/* 0AF4DC 800AE8DC AEC20000 */  sw    $v0, ($s6)
.L800AE8E0:
/* 0AF4E0 800AE8E0 3C09800E */  lui   $t1, %hi(D_800E2E54) # $t1, 0x800e
/* 0AF4E4 800AE8E4 8D292E54 */  lw    $t1, %lo(D_800E2E54)($t1)
/* 0AF4E8 800AE8E8 3C16800E */  lui   $s6, %hi(D_800E2CB4) # $s6, 0x800e
/* 0AF4EC 800AE8EC 1920000A */  blez  $t1, .L800AE918
/* 0AF4F0 800AE8F0 26D62CB4 */   addiu $s6, %lo(D_800E2CB4) # addiu $s6, $s6, 0x2cb4
/* 0AF4F4 800AE8F4 001720C0 */  sll   $a0, $s7, 3
/* 0AF4F8 800AE8F8 3C01800E */  lui   $at, %hi(D_800E2CB8) # $at, 0x800e
/* 0AF4FC 800AE8FC 00972023 */  subu  $a0, $a0, $s7
/* 0AF500 800AE900 AC202CB8 */  sw    $zero, %lo(D_800E2CB8)($at)
/* 0AF504 800AE904 00042100 */  sll   $a0, $a0, 4
/* 0AF508 800AE908 0C01C327 */  jal   func_80070C9C
/* 0AF50C 800AE90C 02402825 */   move  $a1, $s2
/* 0AF510 800AE910 3C01800E */  lui   $at, %hi(D_800E2CC0) # $at, 0x800e
/* 0AF514 800AE914 AC222CC0 */  sw    $v0, %lo(D_800E2CC0)($at)
.L800AE918:
/* 0AF518 800AE918 3C0A800E */  lui   $t2, %hi(D_800E2E58) # $t2, 0x800e
/* 0AF51C 800AE91C 8D4A2E58 */  lw    $t2, %lo(D_800E2E58)($t2)
/* 0AF520 800AE920 00000000 */  nop   
/* 0AF524 800AE924 19400008 */  blez  $t2, .L800AE948
/* 0AF528 800AE928 3C01800E */   lui   $at, %hi(D_800E2CC4) # $at, 0x800e
/* 0AF52C 800AE92C AC202CC4 */  sw    $zero, %lo(D_800E2CC4)($at)
/* 0AF530 800AE930 001421C0 */  sll   $a0, $s4, 7
/* 0AF534 800AE934 0C01C327 */  jal   func_80070C9C
/* 0AF538 800AE938 02402825 */   move  $a1, $s2
/* 0AF53C 800AE93C 3C17800E */  lui   $s7, %hi(D_800E2CCC) # $s7, 0x800e
/* 0AF540 800AE940 26F72CCC */  addiu $s7, %lo(D_800E2CCC) # addiu $s7, $s7, 0x2ccc
/* 0AF544 800AE944 AEE20000 */  sw    $v0, ($s7)
.L800AE948:
/* 0AF548 800AE948 3C0B800E */  lui   $t3, %hi(D_800E2E5C) # $t3, 0x800e
/* 0AF54C 800AE94C 8D6B2E5C */  lw    $t3, %lo(D_800E2E5C)($t3)
/* 0AF550 800AE950 3C17800E */  lui   $s7, %hi(D_800E2CCC) # $s7, 0x800e
/* 0AF554 800AE954 1960000B */  blez  $t3, .L800AE984
/* 0AF558 800AE958 26F72CCC */   addiu $s7, %lo(D_800E2CCC) # addiu $s7, $s7, 0x2ccc
/* 0AF55C 800AE95C 001E2100 */  sll   $a0, $fp, 4
/* 0AF560 800AE960 3C01800E */  lui   $at, %hi(D_800E2CD0) # $at, 0x800e
/* 0AF564 800AE964 009E2021 */  addu  $a0, $a0, $fp
/* 0AF568 800AE968 AC202CD0 */  sw    $zero, %lo(D_800E2CD0)($at)
/* 0AF56C 800AE96C 000420C0 */  sll   $a0, $a0, 3
/* 0AF570 800AE970 0C01C327 */  jal   func_80070C9C
/* 0AF574 800AE974 02402825 */   move  $a1, $s2
/* 0AF578 800AE978 3C1E800E */  lui   $fp, %hi(D_800E2CD8) # $fp, 0x800e
/* 0AF57C 800AE97C 27DE2CD8 */  addiu $fp, %lo(D_800E2CD8) # addiu $fp, $fp, 0x2cd8
/* 0AF580 800AE980 AFC20000 */  sw    $v0, ($fp)
.L800AE984:
/* 0AF584 800AE984 3C02800E */  lui   $v0, %hi(D_800E2E4C) # $v0, 0x800e
/* 0AF588 800AE988 8C422E4C */  lw    $v0, %lo(D_800E2E4C)($v0)
/* 0AF58C 800AE98C 3C0D800E */  lui   $t5, %hi(D_800E2CE0) # $t5, 0x800e
/* 0AF590 800AE990 8DAD2CE0 */  lw    $t5, %lo(D_800E2CE0)($t5)
/* 0AF594 800AE994 8E180000 */  lw    $t8, ($s0)
/* 0AF598 800AE998 000250C0 */  sll   $t2, $v0, 3
/* 0AF59C 800AE99C 8EA90000 */  lw    $t1, ($s5)
/* 0AF5A0 800AE9A0 000060C0 */  sll   $t4, $zero, 3
/* 0AF5A4 800AE9A4 00007900 */  sll   $t7, $zero, 4
/* 0AF5A8 800AE9A8 01425023 */  subu  $t2, $t2, $v0
/* 0AF5AC 800AE9AC 3C1E800E */  lui   $fp, %hi(D_800E2CD8) # $fp, 0x800e
/* 0AF5B0 800AE9B0 000A5100 */  sll   $t2, $t2, 4
/* 0AF5B4 800AE9B4 018D7021 */  addu  $t6, $t4, $t5
/* 0AF5B8 800AE9B8 01F8C821 */  addu  $t9, $t7, $t8
/* 0AF5BC 800AE9BC 27DE2CD8 */  addiu $fp, %lo(D_800E2CD8) # addiu $fp, $fp, 0x2cd8
/* 0AF5C0 800AE9C0 AFAE0054 */  sw    $t6, 0x54($sp)
/* 0AF5C4 800AE9C4 AFB90050 */  sw    $t9, 0x50($sp)
/* 0AF5C8 800AE9C8 00008825 */  move  $s1, $zero
/* 0AF5CC 800AE9CC 18400016 */  blez  $v0, .L800AEA28
/* 0AF5D0 800AE9D0 012A9021 */   addu  $s2, $t1, $t2
/* 0AF5D4 800AE9D4 00008025 */  move  $s0, $zero
/* 0AF5D8 800AE9D8 27B40050 */  addiu $s4, $sp, 0x50
/* 0AF5DC 800AE9DC 27B30054 */  addiu $s3, $sp, 0x54
.L800AE9E0:
/* 0AF5E0 800AE9E0 8EAD0000 */  lw    $t5, ($s5)
/* 0AF5E4 800AE9E4 00115900 */  sll   $t3, $s1, 4
/* 0AF5E8 800AE9E8 01726021 */  addu  $t4, $t3, $s2
/* 0AF5EC 800AE9EC 01B07021 */  addu  $t6, $t5, $s0
/* 0AF5F0 800AE9F0 ADCC0044 */  sw    $t4, 0x44($t6)
/* 0AF5F4 800AE9F4 8EAF0000 */  lw    $t7, ($s5)
/* 0AF5F8 800AE9F8 02602825 */  move  $a1, $s3
/* 0AF5FC 800AE9FC 01F0C021 */  addu  $t8, $t7, $s0
/* 0AF600 800AEA00 8F040044 */  lw    $a0, 0x44($t8)
/* 0AF604 800AEA04 0C02BB85 */  jal   func_800AEE14
/* 0AF608 800AEA08 02803025 */   move  $a2, $s4
/* 0AF60C 800AEA0C 3C19800E */  lui   $t9, %hi(D_800E2E4C) # $t9, 0x800e
/* 0AF610 800AEA10 8F392E4C */  lw    $t9, %lo(D_800E2E4C)($t9)
/* 0AF614 800AEA14 26310001 */  addiu $s1, $s1, 1
/* 0AF618 800AEA18 0239082A */  slt   $at, $s1, $t9
/* 0AF61C 800AEA1C 1420FFF0 */  bnez  $at, .L800AE9E0
/* 0AF620 800AEA20 26100070 */   addiu $s0, $s0, 0x70
/* 0AF624 800AEA24 00008825 */  move  $s1, $zero
.L800AEA28:
/* 0AF628 800AEA28 3C03800E */  lui   $v1, %hi(D_800E2E50) # $v1, 0x800e
/* 0AF62C 800AEA2C 24632E50 */  addiu $v1, %lo(D_800E2E50) # addiu $v1, $v1, 0x2e50
/* 0AF630 800AEA30 8C620000 */  lw    $v0, ($v1)
/* 0AF634 800AEA34 8EC90000 */  lw    $t1, ($s6)
/* 0AF638 800AEA38 000250C0 */  sll   $t2, $v0, 3
/* 0AF63C 800AEA3C 01425023 */  subu  $t2, $t2, $v0
/* 0AF640 800AEA40 000A5100 */  sll   $t2, $t2, 4
/* 0AF644 800AEA44 27B30054 */  addiu $s3, $sp, 0x54
/* 0AF648 800AEA48 27B40050 */  addiu $s4, $sp, 0x50
/* 0AF64C 800AEA4C 18400016 */  blez  $v0, .L800AEAA8
/* 0AF650 800AEA50 012A9021 */   addu  $s2, $t1, $t2
/* 0AF654 800AEA54 00008025 */  move  $s0, $zero
.L800AEA58:
/* 0AF658 800AEA58 8ECC0000 */  lw    $t4, ($s6)
/* 0AF65C 800AEA5C 00115900 */  sll   $t3, $s1, 4
/* 0AF660 800AEA60 01726821 */  addu  $t5, $t3, $s2
/* 0AF664 800AEA64 01907021 */  addu  $t6, $t4, $s0
/* 0AF668 800AEA68 ADCD0044 */  sw    $t5, 0x44($t6)
/* 0AF66C 800AEA6C 8ECF0000 */  lw    $t7, ($s6)
/* 0AF670 800AEA70 02602825 */  move  $a1, $s3
/* 0AF674 800AEA74 01F0C021 */  addu  $t8, $t7, $s0
/* 0AF678 800AEA78 8F040044 */  lw    $a0, 0x44($t8)
/* 0AF67C 800AEA7C 0C02BBAE */  jal   func_800AEEB8
/* 0AF680 800AEA80 02803025 */   move  $a2, $s4
/* 0AF684 800AEA84 3C19800E */  lui   $t9, %hi(D_800E2E50) # $t9, 0x800e
/* 0AF688 800AEA88 8F392E50 */  lw    $t9, %lo(D_800E2E50)($t9)
/* 0AF68C 800AEA8C 26310001 */  addiu $s1, $s1, 1
/* 0AF690 800AEA90 0239082A */  slt   $at, $s1, $t9
/* 0AF694 800AEA94 1420FFF0 */  bnez  $at, .L800AEA58
/* 0AF698 800AEA98 26100070 */   addiu $s0, $s0, 0x70
/* 0AF69C 800AEA9C 3C03800E */  lui   $v1, %hi(D_800E2E50) # $v1, 0x800e
/* 0AF6A0 800AEAA0 24632E50 */  addiu $v1, %lo(D_800E2E50) # addiu $v1, $v1, 0x2e50
/* 0AF6A4 800AEAA4 00008825 */  move  $s1, $zero
.L800AEAA8:
/* 0AF6A8 800AEAA8 3C07800E */  lui   $a3, %hi(D_800E2E58) # $a3, 0x800e
/* 0AF6AC 800AEAAC 24E72E58 */  addiu $a3, %lo(D_800E2E58) # addiu $a3, $a3, 0x2e58
/* 0AF6B0 800AEAB0 8CE20000 */  lw    $v0, ($a3)
/* 0AF6B4 800AEAB4 8EE90000 */  lw    $t1, ($s7)
/* 0AF6B8 800AEAB8 000250C0 */  sll   $t2, $v0, 3
/* 0AF6BC 800AEABC 01425023 */  subu  $t2, $t2, $v0
/* 0AF6C0 800AEAC0 000A5100 */  sll   $t2, $t2, 4
/* 0AF6C4 800AEAC4 1840001B */  blez  $v0, .L800AEB34
/* 0AF6C8 800AEAC8 012A9021 */   addu  $s2, $t1, $t2
/* 0AF6CC 800AEACC 00008025 */  move  $s0, $zero
.L800AEAD0:
/* 0AF6D0 800AEAD0 8EED0000 */  lw    $t5, ($s7)
/* 0AF6D4 800AEAD4 00115900 */  sll   $t3, $s1, 4
/* 0AF6D8 800AEAD8 01726021 */  addu  $t4, $t3, $s2
/* 0AF6DC 800AEADC 01B07021 */  addu  $t6, $t5, $s0
/* 0AF6E0 800AEAE0 ADCC0044 */  sw    $t4, 0x44($t6)
/* 0AF6E4 800AEAE4 8EF80000 */  lw    $t8, ($s7)
/* 0AF6E8 800AEAE8 3C0F800E */  lui   $t7, %hi(D_800E2D08) # $t7, 0x800e
/* 0AF6EC 800AEAEC 25EF2D08 */  addiu $t7, %lo(D_800E2D08) # addiu $t7, $t7, 0x2d08
/* 0AF6F0 800AEAF0 AFAF0050 */  sw    $t7, 0x50($sp)
/* 0AF6F4 800AEAF4 0310C821 */  addu  $t9, $t8, $s0
/* 0AF6F8 800AEAF8 8F240044 */  lw    $a0, 0x44($t9)
/* 0AF6FC 800AEAFC 02602825 */  move  $a1, $s3
/* 0AF700 800AEB00 0C02BBE2 */  jal   func_800AEF88
/* 0AF704 800AEB04 02803025 */   move  $a2, $s4
/* 0AF708 800AEB08 3C09800E */  lui   $t1, %hi(D_800E2E58) # $t1, 0x800e
/* 0AF70C 800AEB0C 8D292E58 */  lw    $t1, %lo(D_800E2E58)($t1)
/* 0AF710 800AEB10 26310001 */  addiu $s1, $s1, 1
/* 0AF714 800AEB14 0229082A */  slt   $at, $s1, $t1
/* 0AF718 800AEB18 1420FFED */  bnez  $at, .L800AEAD0
/* 0AF71C 800AEB1C 26100070 */   addiu $s0, $s0, 0x70
/* 0AF720 800AEB20 3C07800E */  lui   $a3, %hi(D_800E2E58) # $a3, 0x800e
/* 0AF724 800AEB24 3C03800E */  lui   $v1, %hi(D_800E2E50) # $v1, 0x800e
/* 0AF728 800AEB28 24632E50 */  addiu $v1, %lo(D_800E2E50) # addiu $v1, $v1, 0x2e50
/* 0AF72C 800AEB2C 24E72E58 */  addiu $a3, %lo(D_800E2E58) # addiu $a3, $a3, 0x2e58
/* 0AF730 800AEB30 00008825 */  move  $s1, $zero
.L800AEB34:
/* 0AF734 800AEB34 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF738 800AEB38 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF73C 800AEB3C 8D020000 */  lw    $v0, ($t0)
/* 0AF740 800AEB40 8FCA0000 */  lw    $t2, ($fp)
/* 0AF744 800AEB44 00025900 */  sll   $t3, $v0, 4
/* 0AF748 800AEB48 01625823 */  subu  $t3, $t3, $v0
/* 0AF74C 800AEB4C 000B58C0 */  sll   $t3, $t3, 3
/* 0AF750 800AEB50 1840001D */  blez  $v0, .L800AEBC8
/* 0AF754 800AEB54 014B9021 */   addu  $s2, $t2, $t3
/* 0AF758 800AEB58 00008025 */  move  $s0, $zero
.L800AEB5C:
/* 0AF75C 800AEB5C 8FCE0000 */  lw    $t6, ($fp)
/* 0AF760 800AEB60 00116900 */  sll   $t5, $s1, 4
/* 0AF764 800AEB64 01B26021 */  addu  $t4, $t5, $s2
/* 0AF768 800AEB68 01D07821 */  addu  $t7, $t6, $s0
/* 0AF76C 800AEB6C ADEC0044 */  sw    $t4, 0x44($t7)
/* 0AF770 800AEB70 8FD90000 */  lw    $t9, ($fp)
/* 0AF774 800AEB74 3C18800E */  lui   $t8, %hi(D_800E2D78) # $t8, 0x800e
/* 0AF778 800AEB78 27182D78 */  addiu $t8, %lo(D_800E2D78) # addiu $t8, $t8, 0x2d78
/* 0AF77C 800AEB7C AFB80050 */  sw    $t8, 0x50($sp)
/* 0AF780 800AEB80 03304821 */  addu  $t1, $t9, $s0
/* 0AF784 800AEB84 8D240044 */  lw    $a0, 0x44($t1)
/* 0AF788 800AEB88 02602825 */  move  $a1, $s3
/* 0AF78C 800AEB8C 0C02BC09 */  jal   func_800AF024
/* 0AF790 800AEB90 02803025 */   move  $a2, $s4
/* 0AF794 800AEB94 3C0A800E */  lui   $t2, %hi(D_800E2E5C) # $t2, 0x800e
/* 0AF798 800AEB98 8D4A2E5C */  lw    $t2, %lo(D_800E2E5C)($t2)
/* 0AF79C 800AEB9C 26310001 */  addiu $s1, $s1, 1
/* 0AF7A0 800AEBA0 022A082A */  slt   $at, $s1, $t2
/* 0AF7A4 800AEBA4 1420FFED */  bnez  $at, .L800AEB5C
/* 0AF7A8 800AEBA8 26100078 */   addiu $s0, $s0, 0x78
/* 0AF7AC 800AEBAC 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF7B0 800AEBB0 3C07800E */  lui   $a3, %hi(D_800E2E58) # $a3, 0x800e
/* 0AF7B4 800AEBB4 3C03800E */  lui   $v1, %hi(D_800E2E50) # $v1, 0x800e
/* 0AF7B8 800AEBB8 24632E50 */  addiu $v1, %lo(D_800E2E50) # addiu $v1, $v1, 0x2e50
/* 0AF7BC 800AEBBC 24E72E58 */  addiu $a3, %lo(D_800E2E58) # addiu $a3, $a3, 0x2e58
/* 0AF7C0 800AEBC0 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF7C4 800AEBC4 00008825 */  move  $s1, $zero
.L800AEBC8:
/* 0AF7C8 800AEBC8 3C0B800E */  lui   $t3, %hi(D_800E2E4C) # $t3, 0x800e
/* 0AF7CC 800AEBCC 8D6B2E4C */  lw    $t3, %lo(D_800E2E4C)($t3)
/* 0AF7D0 800AEBD0 3C13800E */  lui   $s3, %hi(D_800E2E60) # $s3, 0x800e
/* 0AF7D4 800AEBD4 1960000E */  blez  $t3, .L800AEC10
/* 0AF7D8 800AEBD8 26732E60 */   addiu $s3, %lo(D_800E2E60) # addiu $s3, $s3, 0x2e60
/* 0AF7DC 800AEBDC 00008025 */  move  $s0, $zero
.L800AEBE0:
/* 0AF7E0 800AEBE0 8EAD0000 */  lw    $t5, ($s5)
/* 0AF7E4 800AEBE4 3C0C800E */  lui   $t4, %hi(D_800E2E4C) # $t4, 0x800e
/* 0AF7E8 800AEBE8 01B07021 */  addu  $t6, $t5, $s0
/* 0AF7EC 800AEBEC A5C0002C */  sh    $zero, 0x2c($t6)
/* 0AF7F0 800AEBF0 8D8C2E4C */  lw    $t4, %lo(D_800E2E4C)($t4)
/* 0AF7F4 800AEBF4 26310001 */  addiu $s1, $s1, 1
/* 0AF7F8 800AEBF8 022C082A */  slt   $at, $s1, $t4
/* 0AF7FC 800AEBFC 1420FFF8 */  bnez  $at, .L800AEBE0
/* 0AF800 800AEC00 26100070 */   addiu $s0, $s0, 0x70
/* 0AF804 800AEC04 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF808 800AEC08 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF80C 800AEC0C 00008825 */  move  $s1, $zero
.L800AEC10:
/* 0AF810 800AEC10 8C6F0000 */  lw    $t7, ($v1)
/* 0AF814 800AEC14 00008025 */  move  $s0, $zero
/* 0AF818 800AEC18 19E0000D */  blez  $t7, .L800AEC50
/* 0AF81C 800AEC1C 3C02800E */   lui   $v0, %hi(D_800E2CC0) # $v0, 0x800e
.L800AEC20:
/* 0AF820 800AEC20 8ED80000 */  lw    $t8, ($s6)
/* 0AF824 800AEC24 26310001 */  addiu $s1, $s1, 1
/* 0AF828 800AEC28 0310C821 */  addu  $t9, $t8, $s0
/* 0AF82C 800AEC2C A720002C */  sh    $zero, 0x2c($t9)
/* 0AF830 800AEC30 8C690000 */  lw    $t1, ($v1)
/* 0AF834 800AEC34 26100070 */  addiu $s0, $s0, 0x70
/* 0AF838 800AEC38 0229082A */  slt   $at, $s1, $t1
/* 0AF83C 800AEC3C 1420FFF8 */  bnez  $at, .L800AEC20
/* 0AF840 800AEC40 00000000 */   nop   
/* 0AF844 800AEC44 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF848 800AEC48 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF84C 800AEC4C 00008825 */  move  $s1, $zero
.L800AEC50:
/* 0AF850 800AEC50 3C03800E */  lui   $v1, %hi(D_800E2E54) # $v1, 0x800e
/* 0AF854 800AEC54 24632E54 */  addiu $v1, %lo(D_800E2E54) # addiu $v1, $v1, 0x2e54
/* 0AF858 800AEC58 8C6A0000 */  lw    $t2, ($v1)
/* 0AF85C 800AEC5C 00008025 */  move  $s0, $zero
/* 0AF860 800AEC60 1940000D */  blez  $t2, .L800AEC98
/* 0AF864 800AEC64 24422CC0 */   addiu $v0, %lo(D_800E2CC0) # addiu $v0, $v0, 0x2cc0
.L800AEC68:
/* 0AF868 800AEC68 8C4B0000 */  lw    $t3, ($v0)
/* 0AF86C 800AEC6C 26310001 */  addiu $s1, $s1, 1
/* 0AF870 800AEC70 01706821 */  addu  $t5, $t3, $s0
/* 0AF874 800AEC74 A5A0002C */  sh    $zero, 0x2c($t5)
/* 0AF878 800AEC78 8C6E0000 */  lw    $t6, ($v1)
/* 0AF87C 800AEC7C 26100070 */  addiu $s0, $s0, 0x70
/* 0AF880 800AEC80 022E082A */  slt   $at, $s1, $t6
/* 0AF884 800AEC84 1420FFF8 */  bnez  $at, .L800AEC68
/* 0AF888 800AEC88 00000000 */   nop   
/* 0AF88C 800AEC8C 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF890 800AEC90 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF894 800AEC94 00008825 */  move  $s1, $zero
.L800AEC98:
/* 0AF898 800AEC98 8CEC0000 */  lw    $t4, ($a3)
/* 0AF89C 800AEC9C 00008025 */  move  $s0, $zero
/* 0AF8A0 800AECA0 1980000D */  blez  $t4, .L800AECD8
/* 0AF8A4 800AECA4 2404002F */   li    $a0, 47
.L800AECA8:
/* 0AF8A8 800AECA8 8EEF0000 */  lw    $t7, ($s7)
/* 0AF8AC 800AECAC 26310001 */  addiu $s1, $s1, 1
/* 0AF8B0 800AECB0 01F0C021 */  addu  $t8, $t7, $s0
/* 0AF8B4 800AECB4 A700002C */  sh    $zero, 0x2c($t8)
/* 0AF8B8 800AECB8 8CF90000 */  lw    $t9, ($a3)
/* 0AF8BC 800AECBC 26100070 */  addiu $s0, $s0, 0x70
/* 0AF8C0 800AECC0 0239082A */  slt   $at, $s1, $t9
/* 0AF8C4 800AECC4 1420FFF8 */  bnez  $at, .L800AECA8
/* 0AF8C8 800AECC8 00000000 */   nop   
/* 0AF8CC 800AECCC 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF8D0 800AECD0 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF8D4 800AECD4 00008825 */  move  $s1, $zero
.L800AECD8:
/* 0AF8D8 800AECD8 8D090000 */  lw    $t1, ($t0)
/* 0AF8DC 800AECDC 00008025 */  move  $s0, $zero
/* 0AF8E0 800AECE0 1920000A */  blez  $t1, .L800AED0C
/* 0AF8E4 800AECE4 00000000 */   nop   
.L800AECE8:
/* 0AF8E8 800AECE8 8FCA0000 */  lw    $t2, ($fp)
/* 0AF8EC 800AECEC 26310001 */  addiu $s1, $s1, 1
/* 0AF8F0 800AECF0 01505821 */  addu  $t3, $t2, $s0
/* 0AF8F4 800AECF4 A560002C */  sh    $zero, 0x2c($t3)
/* 0AF8F8 800AECF8 8D0D0000 */  lw    $t5, ($t0)
/* 0AF8FC 800AECFC 26100078 */  addiu $s0, $s0, 0x78
/* 0AF900 800AED00 022D082A */  slt   $at, $s1, $t5
/* 0AF904 800AED04 1420FFF8 */  bnez  $at, .L800AECE8
/* 0AF908 800AED08 00000000 */   nop   
.L800AED0C:
/* 0AF90C 800AED0C 8E6E0000 */  lw    $t6, ($s3)
/* 0AF910 800AED10 00000000 */  nop   
/* 0AF914 800AED14 15C00034 */  bnez  $t6, .L800AEDE8
/* 0AF918 800AED18 8FBF003C */   lw    $ra, 0x3c($sp)
/* 0AF91C 800AED1C 0C01DB16 */  jal   func_80076C58
/* 0AF920 800AED20 00008825 */   move  $s1, $zero
/* 0AF924 800AED24 3C06800E */  lui   $a2, %hi(D_800E2E64) # $a2, 0x800e
/* 0AF928 800AED28 24C62E64 */  addiu $a2, %lo(D_800E2E64) # addiu $a2, $a2, 0x2e64
/* 0AF92C 800AED2C 00006040 */  sll   $t4, $zero, 1
/* 0AF930 800AED30 ACC00000 */  sw    $zero, ($a2)
/* 0AF934 800AED34 004C7821 */  addu  $t7, $v0, $t4
/* 0AF938 800AED38 85F80000 */  lh    $t8, ($t7)
/* 0AF93C 800AED3C 2404FFFF */  li    $a0, -1
/* 0AF940 800AED40 00409025 */  move  $s2, $v0
/* 0AF944 800AED44 10980009 */  beq   $a0, $t8, .L800AED6C
/* 0AF948 800AED48 00001825 */   move  $v1, $zero
/* 0AF94C 800AED4C 24790001 */  addiu $t9, $v1, 1
.L800AED50:
/* 0AF950 800AED50 00194840 */  sll   $t1, $t9, 1
/* 0AF954 800AED54 02495021 */  addu  $t2, $s2, $t1
/* 0AF958 800AED58 ACD90000 */  sw    $t9, ($a2)
/* 0AF95C 800AED5C 854B0000 */  lh    $t3, ($t2)
/* 0AF960 800AED60 03201825 */  move  $v1, $t9
/* 0AF964 800AED64 148BFFFA */  bne   $a0, $t3, .L800AED50
/* 0AF968 800AED68 24790001 */   addiu $t9, $v1, 1
.L800AED6C:
/* 0AF96C 800AED6C 00032080 */  sll   $a0, $v1, 2
/* 0AF970 800AED70 0C01C327 */  jal   func_80070C9C
/* 0AF974 800AED74 3405FFFF */   li    $a1, 65535
/* 0AF978 800AED78 3C06800E */  lui   $a2, %hi(D_800E2E64) # $a2, 0x800e
/* 0AF97C 800AED7C 24C62E64 */  addiu $a2, %lo(D_800E2E64) # addiu $a2, $a2, 0x2e64
/* 0AF980 800AED80 8CCD0000 */  lw    $t5, ($a2)
/* 0AF984 800AED84 AE620000 */  sw    $v0, ($s3)
/* 0AF988 800AED88 19A00014 */  blez  $t5, .L800AEDDC
/* 0AF98C 800AED8C 02408025 */   move  $s0, $s2
/* 0AF990 800AED90 00001825 */  move  $v1, $zero
.L800AED94:
/* 0AF994 800AED94 86040000 */  lh    $a0, ($s0)
/* 0AF998 800AED98 AFA30044 */  sw    $v1, 0x44($sp)
/* 0AF99C 800AED9C 308E3FFF */  andi  $t6, $a0, 0x3fff
/* 0AF9A0 800AEDA0 01C02025 */  move  $a0, $t6
/* 0AF9A4 800AEDA4 0C01F04B */  jal   func_8007C12C
/* 0AF9A8 800AEDA8 24050001 */   li    $a1, 1
/* 0AF9AC 800AEDAC 8FA30044 */  lw    $v1, 0x44($sp)
/* 0AF9B0 800AEDB0 8E6C0000 */  lw    $t4, ($s3)
/* 0AF9B4 800AEDB4 3C06800E */  lui   $a2, %hi(D_800E2E64) # $a2, 0x800e
/* 0AF9B8 800AEDB8 01837821 */  addu  $t7, $t4, $v1
/* 0AF9BC 800AEDBC ADE20000 */  sw    $v0, ($t7)
/* 0AF9C0 800AEDC0 24C62E64 */  addiu $a2, %lo(D_800E2E64) # addiu $a2, $a2, 0x2e64
/* 0AF9C4 800AEDC4 8CD80000 */  lw    $t8, ($a2)
/* 0AF9C8 800AEDC8 26310001 */  addiu $s1, $s1, 1
/* 0AF9CC 800AEDCC 0238082A */  slt   $at, $s1, $t8
/* 0AF9D0 800AEDD0 26100002 */  addiu $s0, $s0, 2
/* 0AF9D4 800AEDD4 1420FFEF */  bnez  $at, .L800AED94
/* 0AF9D8 800AEDD8 24630004 */   addiu $v1, $v1, 4
.L800AEDDC:
/* 0AF9DC 800AEDDC 0C01C450 */  jal   func_80071140
/* 0AF9E0 800AEDE0 02402025 */   move  $a0, $s2
/* 0AF9E4 800AEDE4 8FBF003C */  lw    $ra, 0x3c($sp)
.L800AEDE8:
/* 0AF9E8 800AEDE8 8FB00018 */  lw    $s0, 0x18($sp)
/* 0AF9EC 800AEDEC 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0AF9F0 800AEDF0 8FB20020 */  lw    $s2, 0x20($sp)
/* 0AF9F4 800AEDF4 8FB30024 */  lw    $s3, 0x24($sp)
/* 0AF9F8 800AEDF8 8FB40028 */  lw    $s4, 0x28($sp)
/* 0AF9FC 800AEDFC 8FB5002C */  lw    $s5, 0x2c($sp)
/* 0AFA00 800AEE00 8FB60030 */  lw    $s6, 0x30($sp)
/* 0AFA04 800AEE04 8FB70034 */  lw    $s7, 0x34($sp)
/* 0AFA08 800AEE08 8FBE0038 */  lw    $fp, 0x38($sp)
/* 0AFA0C 800AEE0C 03E00008 */  jr    $ra
/* 0AFA10 800AEE10 27BD0068 */   addiu $sp, $sp, 0x68

glabel func_800AEE14
/* 0AFA14 800AEE14 240E0003 */  li    $t6, 3
/* 0AFA18 800AEE18 A48E0004 */  sh    $t6, 4($a0)
/* 0AFA1C 800AEE1C 8CAF0000 */  lw    $t7, ($a1)
/* 0AFA20 800AEE20 3C03800E */  lui   $v1, %hi(D_800E2E68) # $v1, 0x800e
/* 0AFA24 800AEE24 AC8F0008 */  sw    $t7, 8($a0)
/* 0AFA28 800AEE28 8CA20000 */  lw    $v0, ($a1)
/* 0AFA2C 800AEE2C 24632E68 */  addiu $v1, %lo(D_800E2E68) # addiu $v1, $v1, 0x2e68
/* 0AFA30 800AEE30 00003825 */  move  $a3, $zero
/* 0AFA34 800AEE34 240800FF */  li    $t0, 255
.L800AEE38:
/* 0AFA38 800AEE38 84780000 */  lh    $t8, ($v1)
/* 0AFA3C 800AEE3C 24E70001 */  addiu $a3, $a3, 1
/* 0AFA40 800AEE40 A4580000 */  sh    $t8, ($v0)
/* 0AFA44 800AEE44 84790002 */  lh    $t9, 2($v1)
/* 0AFA48 800AEE48 00074C00 */  sll   $t1, $a3, 0x10
/* 0AFA4C 800AEE4C 00093C03 */  sra   $a3, $t1, 0x10
/* 0AFA50 800AEE50 28E10003 */  slti  $at, $a3, 3
/* 0AFA54 800AEE54 24630004 */  addiu $v1, $v1, 4
/* 0AFA58 800AEE58 A4400004 */  sh    $zero, 4($v0)
/* 0AFA5C 800AEE5C A0480006 */  sb    $t0, 6($v0)
/* 0AFA60 800AEE60 A0480007 */  sb    $t0, 7($v0)
/* 0AFA64 800AEE64 A0480008 */  sb    $t0, 8($v0)
/* 0AFA68 800AEE68 A0480009 */  sb    $t0, 9($v0)
/* 0AFA6C 800AEE6C 2442000A */  addiu $v0, $v0, 0xa
/* 0AFA70 800AEE70 1420FFF1 */  bnez  $at, .L800AEE38
/* 0AFA74 800AEE74 A459FFF8 */   sh    $t9, -8($v0)
/* 0AFA78 800AEE78 ACA20000 */  sw    $v0, ($a1)
/* 0AFA7C 800AEE7C 240B0001 */  li    $t3, 1
/* 0AFA80 800AEE80 A48B0006 */  sh    $t3, 6($a0)
/* 0AFA84 800AEE84 8CCC0000 */  lw    $t4, ($a2)
/* 0AFA88 800AEE88 240D0040 */  li    $t5, 64
/* 0AFA8C 800AEE8C AC8C000C */  sw    $t4, 0xc($a0)
/* 0AFA90 800AEE90 8CC30000 */  lw    $v1, ($a2)
/* 0AFA94 800AEE94 240E0002 */  li    $t6, 2
/* 0AFA98 800AEE98 240F0001 */  li    $t7, 1
/* 0AFA9C 800AEE9C A06D0000 */  sb    $t5, ($v1)
/* 0AFAA0 800AEEA0 A06E0001 */  sb    $t6, 1($v1)
/* 0AFAA4 800AEEA4 A06F0002 */  sb    $t7, 2($v1)
/* 0AFAA8 800AEEA8 A0600003 */  sb    $zero, 3($v1)
/* 0AFAAC 800AEEAC 24630010 */  addiu $v1, $v1, 0x10
/* 0AFAB0 800AEEB0 03E00008 */  jr    $ra
/* 0AFAB4 800AEEB4 ACC30000 */   sw    $v1, ($a2)

glabel func_800AEEB8
/* 0AFAB8 800AEEB8 240E0004 */  li    $t6, 4
/* 0AFABC 800AEEBC A48E0004 */  sh    $t6, 4($a0)
/* 0AFAC0 800AEEC0 8CAF0000 */  lw    $t7, ($a1)
/* 0AFAC4 800AEEC4 3C03800E */  lui   $v1, %hi(D_800E2E74) # $v1, 0x800e
/* 0AFAC8 800AEEC8 AC8F0008 */  sw    $t7, 8($a0)
/* 0AFACC 800AEECC 8CA20000 */  lw    $v0, ($a1)
/* 0AFAD0 800AEED0 24632E74 */  addiu $v1, %lo(D_800E2E74) # addiu $v1, $v1, 0x2e74
/* 0AFAD4 800AEED4 00003825 */  move  $a3, $zero
/* 0AFAD8 800AEED8 240800FF */  li    $t0, 255
.L800AEEDC:
/* 0AFADC 800AEEDC 84780000 */  lh    $t8, ($v1)
/* 0AFAE0 800AEEE0 24E70001 */  addiu $a3, $a3, 1
/* 0AFAE4 800AEEE4 A4580000 */  sh    $t8, ($v0)
/* 0AFAE8 800AEEE8 84790002 */  lh    $t9, 2($v1)
/* 0AFAEC 800AEEEC 00075400 */  sll   $t2, $a3, 0x10
/* 0AFAF0 800AEEF0 000A3C03 */  sra   $a3, $t2, 0x10
/* 0AFAF4 800AEEF4 28E10004 */  slti  $at, $a3, 4
/* 0AFAF8 800AEEF8 24630004 */  addiu $v1, $v1, 4
/* 0AFAFC 800AEEFC A4400004 */  sh    $zero, 4($v0)
/* 0AFB00 800AEF00 A0480006 */  sb    $t0, 6($v0)
/* 0AFB04 800AEF04 A0480007 */  sb    $t0, 7($v0)
/* 0AFB08 800AEF08 A0480008 */  sb    $t0, 8($v0)
/* 0AFB0C 800AEF0C A0480009 */  sb    $t0, 9($v0)
/* 0AFB10 800AEF10 2442000A */  addiu $v0, $v0, 0xa
/* 0AFB14 800AEF14 1420FFF1 */  bnez  $at, .L800AEEDC
/* 0AFB18 800AEF18 A459FFF8 */   sh    $t9, -8($v0)
/* 0AFB1C 800AEF1C ACA20000 */  sw    $v0, ($a1)
/* 0AFB20 800AEF20 240C0002 */  li    $t4, 2
/* 0AFB24 800AEF24 A48C0006 */  sh    $t4, 6($a0)
/* 0AFB28 800AEF28 8CCD0000 */  lw    $t5, ($a2)
/* 0AFB2C 800AEF2C 24070040 */  li    $a3, 64
/* 0AFB30 800AEF30 AC8D000C */  sw    $t5, 0xc($a0)
/* 0AFB34 800AEF34 8CC30000 */  lw    $v1, ($a2)
/* 0AFB38 800AEF38 24080003 */  li    $t0, 3
/* 0AFB3C 800AEF3C 24090001 */  li    $t1, 1
/* 0AFB40 800AEF40 240E0002 */  li    $t6, 2
/* 0AFB44 800AEF44 A0670000 */  sb    $a3, ($v1)
/* 0AFB48 800AEF48 A0680001 */  sb    $t0, 1($v1)
/* 0AFB4C 800AEF4C A4600004 */  sh    $zero, 4($v1)
/* 0AFB50 800AEF50 A0690002 */  sb    $t1, 2($v1)
/* 0AFB54 800AEF54 A460000A */  sh    $zero, 0xa($v1)
/* 0AFB58 800AEF58 A0600003 */  sb    $zero, 3($v1)
/* 0AFB5C 800AEF5C A460000C */  sh    $zero, 0xc($v1)
/* 0AFB60 800AEF60 A460000E */  sh    $zero, 0xe($v1)
/* 0AFB64 800AEF64 A0670010 */  sb    $a3, 0x10($v1)
/* 0AFB68 800AEF68 A0680011 */  sb    $t0, 0x11($v1)
/* 0AFB6C 800AEF6C A4600014 */  sh    $zero, 0x14($v1)
/* 0AFB70 800AEF70 A06E0012 */  sb    $t6, 0x12($v1)
/* 0AFB74 800AEF74 A0690013 */  sb    $t1, 0x13($v1)
/* 0AFB78 800AEF78 A460001E */  sh    $zero, 0x1e($v1)
/* 0AFB7C 800AEF7C 24630020 */  addiu $v1, $v1, 0x20
/* 0AFB80 800AEF80 03E00008 */  jr    $ra
/* 0AFB84 800AEF84 ACC30000 */   sw    $v1, ($a2)

glabel func_800AEF88
/* 0AFB88 800AEF88 240E0006 */  li    $t6, 6
/* 0AFB8C 800AEF8C 240F0004 */  li    $t7, 4
/* 0AFB90 800AEF90 A48E0004 */  sh    $t6, 4($a0)
/* 0AFB94 800AEF94 A48F0006 */  sh    $t7, 6($a0)
/* 0AFB98 800AEF98 8CB80000 */  lw    $t8, ($a1)
/* 0AFB9C 800AEF9C 240300FF */  li    $v1, 255
/* 0AFBA0 800AEFA0 AC980008 */  sw    $t8, 8($a0)
/* 0AFBA4 800AEFA4 8CD90000 */  lw    $t9, ($a2)
/* 0AFBA8 800AEFA8 00000000 */  nop   
/* 0AFBAC 800AEFAC AC99000C */  sw    $t9, 0xc($a0)
/* 0AFBB0 800AEFB0 8CA20000 */  lw    $v0, ($a1)
/* 0AFBB4 800AEFB4 00000000 */  nop   
/* 0AFBB8 800AEFB8 A0430006 */  sb    $v1, 6($v0)
/* 0AFBBC 800AEFBC A0430007 */  sb    $v1, 7($v0)
/* 0AFBC0 800AEFC0 A0430008 */  sb    $v1, 8($v0)
/* 0AFBC4 800AEFC4 A0430009 */  sb    $v1, 9($v0)
/* 0AFBC8 800AEFC8 A0430010 */  sb    $v1, 0x10($v0)
/* 0AFBCC 800AEFCC A0430011 */  sb    $v1, 0x11($v0)
/* 0AFBD0 800AEFD0 A0430012 */  sb    $v1, 0x12($v0)
/* 0AFBD4 800AEFD4 A0430013 */  sb    $v1, 0x13($v0)
/* 0AFBD8 800AEFD8 A0430024 */  sb    $v1, 0x24($v0)
/* 0AFBDC 800AEFDC A0430025 */  sb    $v1, 0x25($v0)
/* 0AFBE0 800AEFE0 A0430026 */  sb    $v1, 0x26($v0)
/* 0AFBE4 800AEFE4 A0430027 */  sb    $v1, 0x27($v0)
/* 0AFBE8 800AEFE8 A043002E */  sb    $v1, 0x2e($v0)
/* 0AFBEC 800AEFEC A043002F */  sb    $v1, 0x2f($v0)
/* 0AFBF0 800AEFF0 A0430030 */  sb    $v1, 0x30($v0)
/* 0AFBF4 800AEFF4 A0430031 */  sb    $v1, 0x31($v0)
/* 0AFBF8 800AEFF8 A0430038 */  sb    $v1, 0x38($v0)
/* 0AFBFC 800AEFFC A0430039 */  sb    $v1, 0x39($v0)
/* 0AFC00 800AF000 A043003A */  sb    $v1, 0x3a($v0)
/* 0AFC04 800AF004 A043003B */  sb    $v1, 0x3b($v0)
/* 0AFC08 800AF008 2442003C */  addiu $v0, $v0, 0x3c
/* 0AFC0C 800AF00C A043FFDE */  sb    $v1, -0x22($v0)
/* 0AFC10 800AF010 A043FFDF */  sb    $v1, -0x21($v0)
/* 0AFC14 800AF014 A043FFE0 */  sb    $v1, -0x20($v0)
/* 0AFC18 800AF018 A043FFE1 */  sb    $v1, -0x1f($v0)
/* 0AFC1C 800AF01C 03E00008 */  jr    $ra
/* 0AFC20 800AF020 ACA20000 */   sw    $v0, ($a1)

glabel func_800AF024
/* 0AFC24 800AF024 24070008 */  li    $a3, 8
/* 0AFC28 800AF028 A4870004 */  sh    $a3, 4($a0)
/* 0AFC2C 800AF02C A4870006 */  sh    $a3, 6($a0)
/* 0AFC30 800AF030 8CAE0000 */  lw    $t6, ($a1)
/* 0AFC34 800AF034 00001825 */  move  $v1, $zero
/* 0AFC38 800AF038 AC8E0008 */  sw    $t6, 8($a0)
/* 0AFC3C 800AF03C 8CCF0000 */  lw    $t7, ($a2)
/* 0AFC40 800AF040 24060010 */  li    $a2, 16
/* 0AFC44 800AF044 AC8F000C */  sw    $t7, 0xc($a0)
/* 0AFC48 800AF048 8CA20000 */  lw    $v0, ($a1)
/* 0AFC4C 800AF04C 240400FF */  li    $a0, 255
.L800AF050:
/* 0AFC50 800AF050 24630004 */  addiu $v1, $v1, 4
/* 0AFC54 800AF054 A0440010 */  sb    $a0, 0x10($v0)
/* 0AFC58 800AF058 A0440011 */  sb    $a0, 0x11($v0)
/* 0AFC5C 800AF05C A0440012 */  sb    $a0, 0x12($v0)
/* 0AFC60 800AF060 A0440013 */  sb    $a0, 0x13($v0)
/* 0AFC64 800AF064 A044001A */  sb    $a0, 0x1a($v0)
/* 0AFC68 800AF068 A044001B */  sb    $a0, 0x1b($v0)
/* 0AFC6C 800AF06C A044001C */  sb    $a0, 0x1c($v0)
/* 0AFC70 800AF070 A044001D */  sb    $a0, 0x1d($v0)
/* 0AFC74 800AF074 A0440024 */  sb    $a0, 0x24($v0)
/* 0AFC78 800AF078 A0440025 */  sb    $a0, 0x25($v0)
/* 0AFC7C 800AF07C A0440026 */  sb    $a0, 0x26($v0)
/* 0AFC80 800AF080 A0440027 */  sb    $a0, 0x27($v0)
/* 0AFC84 800AF084 24420028 */  addiu $v0, $v0, 0x28
/* 0AFC88 800AF088 A044FFDE */  sb    $a0, -0x22($v0)
/* 0AFC8C 800AF08C A044FFDF */  sb    $a0, -0x21($v0)
/* 0AFC90 800AF090 A044FFE0 */  sb    $a0, -0x20($v0)
/* 0AFC94 800AF094 1466FFEE */  bne   $v1, $a2, .L800AF050
/* 0AFC98 800AF098 A044FFE1 */   sb    $a0, -0x1f($v0)
/* 0AFC9C 800AF09C 03E00008 */  jr    $ra
/* 0AFCA0 800AF0A0 ACA20000 */   sw    $v0, ($a1)

glabel func_800AF0A4
/* 0AFCA4 800AF0A4 8C820044 */  lw    $v0, 0x44($a0)
/* 0AFCA8 800AF0A8 00000000 */  nop   
/* 0AFCAC 800AF0AC 8C460000 */  lw    $a2, ($v0)
/* 0AFCB0 800AF0B0 8C43000C */  lw    $v1, 0xc($v0)
/* 0AFCB4 800AF0B4 90C50000 */  lbu   $a1, ($a2)
/* 0AFCB8 800AF0B8 90C70001 */  lbu   $a3, 1($a2)
/* 0AFCBC 800AF0BC 24AEFFFF */  addiu $t6, $a1, -1
/* 0AFCC0 800AF0C0 000E7D40 */  sll   $t7, $t6, 0x15
/* 0AFCC4 800AF0C4 000FC403 */  sra   $t8, $t7, 0x10
/* 0AFCC8 800AF0C8 24E7FFFF */  addiu $a3, $a3, -1
/* 0AFCCC 800AF0CC 00074940 */  sll   $t1, $a3, 5
/* 0AFCD0 800AF0D0 00185043 */  sra   $t2, $t8, 1
/* 0AFCD4 800AF0D4 A46A0004 */  sh    $t2, 4($v1)
/* 0AFCD8 800AF0D8 A4600006 */  sh    $zero, 6($v1)
/* 0AFCDC 800AF0DC A4600008 */  sh    $zero, 8($v1)
/* 0AFCE0 800AF0E0 A469000A */  sh    $t1, 0xa($v1)
/* 0AFCE4 800AF0E4 A478000C */  sh    $t8, 0xc($v1)
/* 0AFCE8 800AF0E8 03E00008 */  jr    $ra
/* 0AFCEC 800AF0EC A469000E */   sh    $t1, 0xe($v1)

glabel func_800AF0F0
/* 0AFCF0 800AF0F0 8C820044 */  lw    $v0, 0x44($a0)
/* 0AFCF4 800AF0F4 00000000 */  nop   
/* 0AFCF8 800AF0F8 8C460000 */  lw    $a2, ($v0)
/* 0AFCFC 800AF0FC 8C43000C */  lw    $v1, 0xc($v0)
/* 0AFD00 800AF100 90C50000 */  lbu   $a1, ($a2)
/* 0AFD04 800AF104 90C70001 */  lbu   $a3, 1($a2)
/* 0AFD08 800AF108 24A5FFFF */  addiu $a1, $a1, -1
/* 0AFD0C 800AF10C 0005C140 */  sll   $t8, $a1, 5
/* 0AFD10 800AF110 24E7FFFF */  addiu $a3, $a3, -1
/* 0AFD14 800AF114 00074940 */  sll   $t1, $a3, 5
/* 0AFD18 800AF118 A4690006 */  sh    $t1, 6($v1)
/* 0AFD1C 800AF11C A4780008 */  sh    $t8, 8($v1)
/* 0AFD20 800AF120 A4780016 */  sh    $t8, 0x16($v1)
/* 0AFD24 800AF124 A4780018 */  sh    $t8, 0x18($v1)
/* 0AFD28 800AF128 A469001A */  sh    $t1, 0x1a($v1)
/* 0AFD2C 800AF12C 03E00008 */  jr    $ra
/* 0AFD30 800AF130 A478001C */   sh    $t8, 0x1c($v1)

glabel func_800AF134
/* 0AFD34 800AF134 3C0E800E */  lui   $t6, %hi(D_800E2CE8) # $t6, 0x800e
/* 0AFD38 800AF138 8DCE2CE8 */  lw    $t6, %lo(D_800E2CE8)($t6)
/* 0AFD3C 800AF13C 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0AFD40 800AF140 00CE082A */  slt   $at, $a2, $t6
/* 0AFD44 800AF144 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0AFD48 800AF148 14200002 */  bnez  $at, .L800AF154
/* 0AFD4C 800AF14C AFA7002C */   sw    $a3, 0x2c($sp)
/* 0AFD50 800AF150 00003025 */  move  $a2, $zero
.L800AF154:
/* 0AFD54 800AF154 3C0F800E */  lui   $t7, %hi(D_800E2CF4) # $t7, 0x800e
/* 0AFD58 800AF158 8DEF2CF4 */  lw    $t7, %lo(D_800E2CF4)($t7)
/* 0AFD5C 800AF15C 3C18800E */  lui   $t8, %hi(D_800E2CFC) # $t8, 0x800e
/* 0AFD60 800AF160 00AF082A */  slt   $at, $a1, $t7
/* 0AFD64 800AF164 14200002 */  bnez  $at, .L800AF170
/* 0AFD68 800AF168 00000000 */   nop   
/* 0AFD6C 800AF16C 00002825 */  move  $a1, $zero
.L800AF170:
/* 0AFD70 800AF170 8F182CFC */  lw    $t8, %lo(D_800E2CFC)($t8)
/* 0AFD74 800AF174 0005C880 */  sll   $t9, $a1, 2
/* 0AFD78 800AF178 84890008 */  lh    $t1, 8($a0)
/* 0AFD7C 800AF17C 03194021 */  addu  $t0, $t8, $t9
/* 0AFD80 800AF180 8D020000 */  lw    $v0, ($t0)
/* 0AFD84 800AF184 14C90005 */  bne   $a2, $t1, .L800AF19C
/* 0AFD88 800AF188 00000000 */   nop   
/* 0AFD8C 800AF18C 8C8A0000 */  lw    $t2, ($a0)
/* 0AFD90 800AF190 00000000 */  nop   
/* 0AFD94 800AF194 104A000F */  beq   $v0, $t2, .L800AF1D4
/* 0AFD98 800AF198 8FBF001C */   lw    $ra, 0x1c($sp)
.L800AF19C:
/* 0AFD9C 800AF19C AFA40020 */  sw    $a0, 0x20($sp)
/* 0AFDA0 800AF1A0 AFA50024 */  sw    $a1, 0x24($sp)
/* 0AFDA4 800AF1A4 0C02C898 */  jal   func_800B2260
/* 0AFDA8 800AF1A8 AFA60028 */   sw    $a2, 0x28($sp)
/* 0AFDAC 800AF1AC 87AB0032 */  lh    $t3, 0x32($sp)
/* 0AFDB0 800AF1B0 87AC0036 */  lh    $t4, 0x36($sp)
/* 0AFDB4 800AF1B4 8FA40020 */  lw    $a0, 0x20($sp)
/* 0AFDB8 800AF1B8 8FA50024 */  lw    $a1, 0x24($sp)
/* 0AFDBC 800AF1BC 8FA60028 */  lw    $a2, 0x28($sp)
/* 0AFDC0 800AF1C0 87A7002E */  lh    $a3, 0x2e($sp)
/* 0AFDC4 800AF1C4 AFAB0010 */  sw    $t3, 0x10($sp)
/* 0AFDC8 800AF1C8 0C02BCA7 */  jal   func_800AF29C
/* 0AFDCC 800AF1CC AFAC0014 */   sw    $t4, 0x14($sp)
/* 0AFDD0 800AF1D0 8FBF001C */  lw    $ra, 0x1c($sp)
.L800AF1D4:
/* 0AFDD4 800AF1D4 27BD0020 */  addiu $sp, $sp, 0x20
/* 0AFDD8 800AF1D8 03E00008 */  jr    $ra
/* 0AFDDC 800AF1DC 00000000 */   nop   

glabel func_800AF1E0
/* 0AFDE0 800AF1E0 3C0E800E */  lui   $t6, %hi(D_800E2CF4) # $t6, 0x800e
/* 0AFDE4 800AF1E4 8DCE2CF4 */  lw    $t6, %lo(D_800E2CF4)($t6)
/* 0AFDE8 800AF1E8 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0AFDEC 800AF1EC 00AE082A */  slt   $at, $a1, $t6
/* 0AFDF0 800AF1F0 10200026 */  beqz  $at, .L800AF28C
/* 0AFDF4 800AF1F4 AFBF001C */   sw    $ra, 0x1c($sp)
/* 0AFDF8 800AF1F8 3C0F800E */  lui   $t7, %hi(D_800E2CFC) # $t7, 0x800e
/* 0AFDFC 800AF1FC 8DEF2CFC */  lw    $t7, %lo(D_800E2CFC)($t7)
/* 0AFE00 800AF200 4448F800 */  cfc1  $t0, $31
/* 0AFE04 800AF204 0005C080 */  sll   $t8, $a1, 2
/* 0AFE08 800AF208 01F8C821 */  addu  $t9, $t7, $t8
/* 0AFE0C 800AF20C 8F220000 */  lw    $v0, ($t9)
/* 0AFE10 800AF210 35010003 */  ori   $at, $t0, 3
/* 0AFE14 800AF214 38210002 */  xori  $at, $at, 2
/* 0AFE18 800AF218 44C1F800 */  ctc1  $at, $31
/* 0AFE1C 800AF21C C4440004 */  lwc1  $f4, 4($v0)
/* 0AFE20 800AF220 C4480008 */  lwc1  $f8, 8($v0)
/* 0AFE24 800AF224 460021A4 */  cvt.w.s $f6, $f4
/* 0AFE28 800AF228 44C8F800 */  ctc1  $t0, $31
/* 0AFE2C 800AF22C 44073000 */  mfc1  $a3, $f6
/* 0AFE30 800AF230 00000000 */  nop   
/* 0AFE34 800AF234 444BF800 */  cfc1  $t3, $31
/* 0AFE38 800AF238 00074C00 */  sll   $t1, $a3, 0x10
/* 0AFE3C 800AF23C 35610003 */  ori   $at, $t3, 3
/* 0AFE40 800AF240 38210002 */  xori  $at, $at, 2
/* 0AFE44 800AF244 44C1F800 */  ctc1  $at, $31
/* 0AFE48 800AF248 00093C03 */  sra   $a3, $t1, 0x10
/* 0AFE4C 800AF24C 460042A4 */  cvt.w.s $f10, $f8
/* 0AFE50 800AF250 44CBF800 */  ctc1  $t3, $31
/* 0AFE54 800AF254 440C5000 */  mfc1  $t4, $f10
/* 0AFE58 800AF258 00000000 */  nop   
/* 0AFE5C 800AF25C 444DF800 */  cfc1  $t5, $31
/* 0AFE60 800AF260 AFAC0010 */  sw    $t4, 0x10($sp)
/* 0AFE64 800AF264 35A10003 */  ori   $at, $t5, 3
/* 0AFE68 800AF268 38210002 */  xori  $at, $at, 2
/* 0AFE6C 800AF26C 44C1F800 */  ctc1  $at, $31
/* 0AFE70 800AF270 C450000C */  lwc1  $f16, 0xc($v0)
/* 0AFE74 800AF274 00000000 */  nop   
/* 0AFE78 800AF278 460084A4 */  cvt.w.s $f18, $f16
/* 0AFE7C 800AF27C 440E9000 */  mfc1  $t6, $f18
/* 0AFE80 800AF280 44CDF800 */  ctc1  $t5, $31
/* 0AFE84 800AF284 0C02BCA7 */  jal   func_800AF29C
/* 0AFE88 800AF288 AFAE0014 */   sw    $t6, 0x14($sp)
.L800AF28C:
/* 0AFE8C 800AF28C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0AFE90 800AF290 27BD0020 */  addiu $sp, $sp, 0x20
/* 0AFE94 800AF294 03E00008 */  jr    $ra
/* 0AFE98 800AF298 00000000 */   nop   

glabel func_800AF29C
/* 0AFE9C 800AF29C 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0AFEA0 800AF2A0 3C18800E */  lui   $t8, %hi(D_800E2CFC) # $t8, 0x800e
/* 0AFEA4 800AF2A4 8F182CFC */  lw    $t8, %lo(D_800E2CFC)($t8)
/* 0AFEA8 800AF2A8 0005C880 */  sll   $t9, $a1, 2
/* 0AFEAC 800AF2AC AFBF001C */  sw    $ra, 0x1c($sp)
/* 0AFEB0 800AF2B0 AFB00018 */  sw    $s0, 0x18($sp)
/* 0AFEB4 800AF2B4 AFA70034 */  sw    $a3, 0x34($sp)
/* 0AFEB8 800AF2B8 03194021 */  addu  $t0, $t8, $t9
/* 0AFEBC 800AF2BC 8D030000 */  lw    $v1, ($t0)
/* 0AFEC0 800AF2C0 A4860008 */  sh    $a2, 8($a0)
/* 0AFEC4 800AF2C4 A4870018 */  sh    $a3, 0x18($a0)
/* 0AFEC8 800AF2C8 AC830000 */  sw    $v1, ($a0)
/* 0AFECC 800AF2CC 87A9003A */  lh    $t1, 0x3a($sp)
/* 0AFED0 800AF2D0 00808025 */  move  $s0, $a0
/* 0AFED4 800AF2D4 A489001A */  sh    $t1, 0x1a($a0)
/* 0AFED8 800AF2D8 87AA003E */  lh    $t2, 0x3e($sp)
/* 0AFEDC 800AF2DC A480001E */  sh    $zero, 0x1e($a0)
/* 0AFEE0 800AF2E0 A48A001C */  sh    $t2, 0x1c($a0)
/* 0AFEE4 800AF2E4 8C620000 */  lw    $v0, ($v1)
/* 0AFEE8 800AF2E8 240C4000 */  li    $t4, 16384
/* 0AFEEC 800AF2EC 304B4000 */  andi  $t3, $v0, 0x4000
/* 0AFEF0 800AF2F0 11600008 */  beqz  $t3, .L800AF314
/* 0AFEF4 800AF2F4 304D0400 */   andi  $t5, $v0, 0x400
/* 0AFEF8 800AF2F8 44800000 */  mtc1  $zero, $f0
/* 0AFEFC 800AF2FC A48C0004 */  sh    $t4, 4($a0)
/* 0AFF00 800AF300 A0800006 */  sb    $zero, 6($a0)
/* 0AFF04 800AF304 E480000C */  swc1  $f0, 0xc($a0)
/* 0AFF08 800AF308 E4800010 */  swc1  $f0, 0x10($a0)
/* 0AFF0C 800AF30C 10000039 */  b     .L800AF3F4
/* 0AFF10 800AF310 E4800014 */   swc1  $f0, 0x14($a0)
.L800AF314:
/* 0AFF14 800AF314 11A00024 */  beqz  $t5, .L800AF3A8
/* 0AFF18 800AF318 240E0400 */   li    $t6, 1024
/* 0AFF1C 800AF31C A2000006 */  sb    $zero, 6($s0)
/* 0AFF20 800AF320 A60E0004 */  sh    $t6, 4($s0)
/* 0AFF24 800AF324 3C0F800E */  lui   $t7, %hi(D_800E2CF0) # $t7, 0x800e
/* 0AFF28 800AF328 8DEF2CF0 */  lw    $t7, %lo(D_800E2CF0)($t7)
/* 0AFF2C 800AF32C 0006C080 */  sll   $t8, $a2, 2
/* 0AFF30 800AF330 01F8C821 */  addu  $t9, $t7, $t8
/* 0AFF34 800AF334 8F280000 */  lw    $t0, ($t9)
/* 0AFF38 800AF338 3C058080 */  lui   $a1, (0x80808080 >> 16) # lui $a1, 0x8080
/* 0AFF3C 800AF33C 85020008 */  lh    $v0, 8($t0)
/* 0AFF40 800AF340 240900FF */  li    $t1, 255
/* 0AFF44 800AF344 28410100 */  slti  $at, $v0, 0x100
/* 0AFF48 800AF348 10200003 */  beqz  $at, .L800AF358
/* 0AFF4C 800AF34C 34A58080 */   ori   $a1, (0x80808080 & 0xFFFF) # ori $a1, $a1, 0x8080
/* 0AFF50 800AF350 10000002 */  b     .L800AF35C
/* 0AFF54 800AF354 A2020007 */   sb    $v0, 7($s0)
.L800AF358:
/* 0AFF58 800AF358 A2090007 */  sb    $t1, 7($s0)
.L800AF35C:
/* 0AFF5C 800AF35C 92040007 */  lbu   $a0, 7($s0)
/* 0AFF60 800AF360 AFA30024 */  sw    $v1, 0x24($sp)
/* 0AFF64 800AF364 00045080 */  sll   $t2, $a0, 2
/* 0AFF68 800AF368 0C01C327 */  jal   func_80070C9C
/* 0AFF6C 800AF36C 01402025 */   move  $a0, $t2
/* 0AFF70 800AF370 8FA30024 */  lw    $v1, 0x24($sp)
/* 0AFF74 800AF374 AE02000C */  sw    $v0, 0xc($s0)
/* 0AFF78 800AF378 846B0014 */  lh    $t3, 0x14($v1)
/* 0AFF7C 800AF37C 00000000 */  nop   
/* 0AFF80 800AF380 A60B0010 */  sh    $t3, 0x10($s0)
/* 0AFF84 800AF384 846C0016 */  lh    $t4, 0x16($v1)
/* 0AFF88 800AF388 00000000 */  nop   
/* 0AFF8C 800AF38C A60C0012 */  sh    $t4, 0x12($s0)
/* 0AFF90 800AF390 846D0022 */  lh    $t5, 0x22($v1)
/* 0AFF94 800AF394 00000000 */  nop   
/* 0AFF98 800AF398 A60D0014 */  sh    $t5, 0x14($s0)
/* 0AFF9C 800AF39C 846E0024 */  lh    $t6, 0x24($v1)
/* 0AFFA0 800AF3A0 10000014 */  b     .L800AF3F4
/* 0AFFA4 800AF3A4 A60E0016 */   sh    $t6, 0x16($s0)
.L800AF3A8:
/* 0AFFA8 800AF3A8 A6000004 */  sh    $zero, 4($s0)
/* 0AFFAC 800AF3AC 846F0014 */  lh    $t7, 0x14($v1)
/* 0AFFB0 800AF3B0 00000000 */  nop   
/* 0AFFB4 800AF3B4 A60F000C */  sh    $t7, 0xc($s0)
/* 0AFFB8 800AF3B8 84780016 */  lh    $t8, 0x16($v1)
/* 0AFFBC 800AF3BC 00000000 */  nop   
/* 0AFFC0 800AF3C0 A618000E */  sh    $t8, 0xe($s0)
/* 0AFFC4 800AF3C4 84790018 */  lh    $t9, 0x18($v1)
/* 0AFFC8 800AF3C8 00000000 */  nop   
/* 0AFFCC 800AF3CC A6190010 */  sh    $t9, 0x10($s0)
/* 0AFFD0 800AF3D0 84680022 */  lh    $t0, 0x22($v1)
/* 0AFFD4 800AF3D4 00000000 */  nop   
/* 0AFFD8 800AF3D8 A6080012 */  sh    $t0, 0x12($s0)
/* 0AFFDC 800AF3DC 84690024 */  lh    $t1, 0x24($v1)
/* 0AFFE0 800AF3E0 00000000 */  nop   
/* 0AFFE4 800AF3E4 A6090014 */  sh    $t1, 0x14($s0)
/* 0AFFE8 800AF3E8 846A0026 */  lh    $t2, 0x26($v1)
/* 0AFFEC 800AF3EC 00000000 */  nop   
/* 0AFFF0 800AF3F0 A60A0016 */  sh    $t2, 0x16($s0)
.L800AF3F4:
/* 0AFFF4 800AF3F4 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0AFFF8 800AF3F8 8FB00018 */  lw    $s0, 0x18($sp)
/* 0AFFFC 800AF3FC 03E00008 */  jr    $ra
/* 0B0000 800AF400 27BD0028 */   addiu $sp, $sp, 0x28

glabel func_800AF404
/* 0B0004 800AF404 3C08800E */  lui   $t0, %hi(D_800E2E28) # $t0, 0x800e
/* 0B0008 800AF408 25082E28 */  addiu $t0, %lo(D_800E2E28) # addiu $t0, $t0, 0x2e28
/* 0B000C 800AF40C 850E0000 */  lh    $t6, ($t0)
/* 0B0010 800AF410 00047980 */  sll   $t7, $a0, 6
/* 0B0014 800AF414 01CFC021 */  addu  $t8, $t6, $t7
/* 0B0018 800AF418 331901FF */  andi  $t9, $t8, 0x1ff
/* 0B001C 800AF41C A5190000 */  sh    $t9, ($t0)
/* 0B0020 800AF420 3C06800E */  lui   $a2, %hi(D_800E2D08) # $a2, 0x800e
/* 0B0024 800AF424 3C07800E */  lui   $a3, %hi(D_800E2D58) # $a3, 0x800e
/* 0B0028 800AF428 3C03800E */  lui   $v1, %hi(D_800E2D58) # $v1, 0x800e
/* 0B002C 800AF42C 85020000 */  lh    $v0, ($t0)
/* 0B0030 800AF430 24632D58 */  addiu $v1, %lo(D_800E2D58) # addiu $v1, $v1, 0x2d58
/* 0B0034 800AF434 24E72D58 */  addiu $a3, %lo(D_800E2D58) # addiu $a3, $a3, 0x2d58
/* 0B0038 800AF438 24C62D08 */  addiu $a2, %lo(D_800E2D08) # addiu $a2, $a2, 0x2d08
.L800AF43C:
/* 0B003C 800AF43C 84E90000 */  lh    $t1, ($a3)
/* 0B0040 800AF440 84EB0002 */  lh    $t3, 2($a3)
/* 0B0044 800AF444 84ED0004 */  lh    $t5, 4($a3)
/* 0B0048 800AF448 24C60010 */  addiu $a2, $a2, 0x10
/* 0B004C 800AF44C 00C3082B */  sltu  $at, $a2, $v1
/* 0B0050 800AF450 01225021 */  addu  $t2, $t1, $v0
/* 0B0054 800AF454 01626021 */  addu  $t4, $t3, $v0
/* 0B0058 800AF458 01A27021 */  addu  $t6, $t5, $v0
/* 0B005C 800AF45C A4CAFFF6 */  sh    $t2, -0xa($a2)
/* 0B0060 800AF460 A4CCFFFA */  sh    $t4, -6($a2)
/* 0B0064 800AF464 A4CEFFFE */  sh    $t6, -2($a2)
/* 0B0068 800AF468 1420FFF4 */  bnez  $at, .L800AF43C
/* 0B006C 800AF46C 24E70006 */   addiu $a3, $a3, 6
/* 0B0070 800AF470 3C04800E */  lui   $a0, %hi(D_800E2D78) # $a0, 0x800e
/* 0B0074 800AF474 3C06800E */  lui   $a2, %hi(D_800E2DF8) # $a2, 0x800e
/* 0B0078 800AF478 3C03800E */  lui   $v1, %hi(D_800E2DF8) # $v1, 0x800e
/* 0B007C 800AF47C 24632DF8 */  addiu $v1, %lo(D_800E2DF8) # addiu $v1, $v1, 0x2df8
/* 0B0080 800AF480 24C62DF8 */  addiu $a2, %lo(D_800E2DF8) # addiu $a2, $a2, 0x2df8
/* 0B0084 800AF484 24842D78 */  addiu $a0, %lo(D_800E2D78) # addiu $a0, $a0, 0x2d78
.L800AF488:
/* 0B0088 800AF488 84CF0000 */  lh    $t7, ($a2)
/* 0B008C 800AF48C 84D90002 */  lh    $t9, 2($a2)
/* 0B0090 800AF490 84CA0004 */  lh    $t2, 4($a2)
/* 0B0094 800AF494 01E2C021 */  addu  $t8, $t7, $v0
/* 0B0098 800AF498 03224821 */  addu  $t1, $t9, $v0
/* 0B009C 800AF49C A4980006 */  sh    $t8, 6($a0)
/* 0B00A0 800AF4A0 A489000A */  sh    $t1, 0xa($a0)
/* 0B00A4 800AF4A4 84C9000C */  lh    $t1, 0xc($a2)
/* 0B00A8 800AF4A8 84D8000A */  lh    $t8, 0xa($a2)
/* 0B00AC 800AF4AC 84CC0006 */  lh    $t4, 6($a2)
/* 0B00B0 800AF4B0 84CE0008 */  lh    $t6, 8($a2)
/* 0B00B4 800AF4B4 01425821 */  addu  $t3, $t2, $v0
/* 0B00B8 800AF4B8 A48B000E */  sh    $t3, 0xe($a0)
/* 0B00BC 800AF4BC 01225021 */  addu  $t2, $t1, $v0
/* 0B00C0 800AF4C0 0302C821 */  addu  $t9, $t8, $v0
/* 0B00C4 800AF4C4 01826821 */  addu  $t5, $t4, $v0
/* 0B00C8 800AF4C8 01C27821 */  addu  $t7, $t6, $v0
/* 0B00CC 800AF4CC 84CB000E */  lh    $t3, 0xe($a2)
/* 0B00D0 800AF4D0 A48F001A */  sh    $t7, 0x1a($a0)
/* 0B00D4 800AF4D4 A48D0016 */  sh    $t5, 0x16($a0)
/* 0B00D8 800AF4D8 A499001E */  sh    $t9, 0x1e($a0)
/* 0B00DC 800AF4DC A48A0026 */  sh    $t2, 0x26($a0)
/* 0B00E0 800AF4E0 84CA0016 */  lh    $t2, 0x16($a2)
/* 0B00E4 800AF4E4 84D90014 */  lh    $t9, 0x14($a2)
/* 0B00E8 800AF4E8 84CD0010 */  lh    $t5, 0x10($a2)
/* 0B00EC 800AF4EC 84CF0012 */  lh    $t7, 0x12($a2)
/* 0B00F0 800AF4F0 01626021 */  addu  $t4, $t3, $v0
/* 0B00F4 800AF4F4 24840040 */  addiu $a0, $a0, 0x40
/* 0B00F8 800AF4F8 01425821 */  addu  $t3, $t2, $v0
/* 0B00FC 800AF4FC 03224821 */  addu  $t1, $t9, $v0
/* 0B0100 800AF500 01A27021 */  addu  $t6, $t5, $v0
/* 0B0104 800AF504 01E2C021 */  addu  $t8, $t7, $v0
/* 0B0108 800AF508 A498FFF6 */  sh    $t8, -0xa($a0)
/* 0B010C 800AF50C A48EFFEE */  sh    $t6, -0x12($a0)
/* 0B0110 800AF510 A489FFFA */  sh    $t1, -6($a0)
/* 0B0114 800AF514 A48BFFFE */  sh    $t3, -2($a0)
/* 0B0118 800AF518 A48CFFEA */  sh    $t4, -0x16($a0)
/* 0B011C 800AF51C 1483FFDA */  bne   $a0, $v1, .L800AF488
/* 0B0120 800AF520 24C60018 */   addiu $a2, $a2, 0x18
/* 0B0124 800AF524 03E00008 */  jr    $ra
/* 0B0128 800AF528 00000000 */   nop   

glabel func_800AF52C
/* 0B012C 800AF52C 8C8E006C */  lw    $t6, 0x6c($a0)
/* 0B0130 800AF530 00057940 */  sll   $t7, $a1, 5
/* 0B0134 800AF534 01CF1021 */  addu  $v0, $t6, $t7
/* 0B0138 800AF538 84460004 */  lh    $a2, 4($v0)
/* 0B013C 800AF53C 8C430000 */  lw    $v1, ($v0)
/* 0B0140 800AF540 30D84000 */  andi  $t8, $a2, 0x4000
/* 0B0144 800AF544 1300000A */  beqz  $t8, .L800AF570
/* 0B0148 800AF548 A440000A */   sh    $zero, 0xa($v0)
/* 0B014C 800AF54C C484000C */  lwc1  $f4, 0xc($a0)
/* 0B0150 800AF550 00000000 */  nop   
/* 0B0154 800AF554 E444000C */  swc1  $f4, 0xc($v0)
/* 0B0158 800AF558 C4860010 */  lwc1  $f6, 0x10($a0)
/* 0B015C 800AF55C 00000000 */  nop   
/* 0B0160 800AF560 E4460010 */  swc1  $f6, 0x10($v0)
/* 0B0164 800AF564 C4880014 */  lwc1  $f8, 0x14($a0)
/* 0B0168 800AF568 10000051 */  b     .L800AF6B0
/* 0B016C 800AF56C E4480014 */   swc1  $f8, 0x14($v0)
.L800AF570:
/* 0B0170 800AF570 30D90400 */  andi  $t9, $a2, 0x400
/* 0B0174 800AF574 13200030 */  beqz  $t9, .L800AF638
/* 0B0178 800AF578 3C08800E */   lui   $t0, %hi(D_800E2CF0) # $t0, 0x800e
/* 0B017C 800AF57C 84490008 */  lh    $t1, 8($v0)
/* 0B0180 800AF580 8D082CF0 */  lw    $t0, %lo(D_800E2CF0)($t0)
/* 0B0184 800AF584 00095080 */  sll   $t2, $t1, 2
/* 0B0188 800AF588 010A5821 */  addu  $t3, $t0, $t2
/* 0B018C 800AF58C 8D6C0000 */  lw    $t4, ($t3)
/* 0B0190 800AF590 90450006 */  lbu   $a1, 6($v0)
/* 0B0194 800AF594 918D0017 */  lbu   $t5, 0x17($t4)
/* 0B0198 800AF598 00000000 */  nop   
/* 0B019C 800AF59C 000D7200 */  sll   $t6, $t5, 8
/* 0B01A0 800AF5A0 18A0000F */  blez  $a1, .L800AF5E0
/* 0B01A4 800AF5A4 A44E000A */   sh    $t6, 0xa($v0)
/* 0B01A8 800AF5A8 18A0000D */  blez  $a1, .L800AF5E0
/* 0B01AC 800AF5AC 00003025 */   move  $a2, $zero
/* 0B01B0 800AF5B0 00003825 */  move  $a3, $zero
.L800AF5B4:
/* 0B01B4 800AF5B4 8C4F000C */  lw    $t7, 0xc($v0)
/* 0B01B8 800AF5B8 24C60001 */  addiu $a2, $a2, 1
/* 0B01BC 800AF5BC 01E7C021 */  addu  $t8, $t7, $a3
/* 0B01C0 800AF5C0 8F050000 */  lw    $a1, ($t8)
/* 0B01C4 800AF5C4 24E70004 */  addiu $a3, $a3, 4
/* 0B01C8 800AF5C8 A4A0003A */  sh    $zero, 0x3a($a1)
/* 0B01CC 800AF5CC 90590006 */  lbu   $t9, 6($v0)
/* 0B01D0 800AF5D0 00000000 */  nop   
/* 0B01D4 800AF5D4 00D9082A */  slt   $at, $a2, $t9
/* 0B01D8 800AF5D8 1420FFF6 */  bnez  $at, .L800AF5B4
/* 0B01DC 800AF5DC 00000000 */   nop   
.L800AF5E0:
/* 0B01E0 800AF5E0 8C650000 */  lw    $a1, ($v1)
/* 0B01E4 800AF5E4 00000000 */  nop   
/* 0B01E8 800AF5E8 30A90001 */  andi  $t1, $a1, 1
/* 0B01EC 800AF5EC 1120000A */  beqz  $t1, .L800AF618
/* 0B01F0 800AF5F0 30AB0004 */   andi  $t3, $a1, 4
/* 0B01F4 800AF5F4 84680014 */  lh    $t0, 0x14($v1)
/* 0B01F8 800AF5F8 00000000 */  nop   
/* 0B01FC 800AF5FC A4480010 */  sh    $t0, 0x10($v0)
/* 0B0200 800AF600 846A0016 */  lh    $t2, 0x16($v1)
/* 0B0204 800AF604 00000000 */  nop   
/* 0B0208 800AF608 A44A0012 */  sh    $t2, 0x12($v0)
/* 0B020C 800AF60C 8C650000 */  lw    $a1, ($v1)
/* 0B0210 800AF610 00000000 */  nop   
/* 0B0214 800AF614 30AB0004 */  andi  $t3, $a1, 4
.L800AF618:
/* 0B0218 800AF618 11600025 */  beqz  $t3, .L800AF6B0
/* 0B021C 800AF61C 00000000 */   nop   
/* 0B0220 800AF620 846C0022 */  lh    $t4, 0x22($v1)
/* 0B0224 800AF624 00000000 */  nop   
/* 0B0228 800AF628 A44C0014 */  sh    $t4, 0x14($v0)
/* 0B022C 800AF62C 846D0024 */  lh    $t5, 0x24($v1)
/* 0B0230 800AF630 1000001F */  b     .L800AF6B0
/* 0B0234 800AF634 A44D0016 */   sh    $t5, 0x16($v0)
.L800AF638:
/* 0B0238 800AF638 8C650000 */  lw    $a1, ($v1)
/* 0B023C 800AF63C 00000000 */  nop   
/* 0B0240 800AF640 30AE0001 */  andi  $t6, $a1, 1
/* 0B0244 800AF644 11C0000E */  beqz  $t6, .L800AF680
/* 0B0248 800AF648 30A90004 */   andi  $t1, $a1, 4
/* 0B024C 800AF64C A0400006 */  sb    $zero, 6($v0)
/* 0B0250 800AF650 846F0014 */  lh    $t7, 0x14($v1)
/* 0B0254 800AF654 00000000 */  nop   
/* 0B0258 800AF658 A44F000C */  sh    $t7, 0xc($v0)
/* 0B025C 800AF65C 84780016 */  lh    $t8, 0x16($v1)
/* 0B0260 800AF660 00000000 */  nop   
/* 0B0264 800AF664 A458000E */  sh    $t8, 0xe($v0)
/* 0B0268 800AF668 84790018 */  lh    $t9, 0x18($v1)
/* 0B026C 800AF66C 00000000 */  nop   
/* 0B0270 800AF670 A4590010 */  sh    $t9, 0x10($v0)
/* 0B0274 800AF674 8C650000 */  lw    $a1, ($v1)
/* 0B0278 800AF678 00000000 */  nop   
/* 0B027C 800AF67C 30A90004 */  andi  $t1, $a1, 4
.L800AF680:
/* 0B0280 800AF680 1120000B */  beqz  $t1, .L800AF6B0
/* 0B0284 800AF684 00000000 */   nop   
/* 0B0288 800AF688 A0400007 */  sb    $zero, 7($v0)
/* 0B028C 800AF68C 84680022 */  lh    $t0, 0x22($v1)
/* 0B0290 800AF690 00000000 */  nop   
/* 0B0294 800AF694 A4480012 */  sh    $t0, 0x12($v0)
/* 0B0298 800AF698 846A0024 */  lh    $t2, 0x24($v1)
/* 0B029C 800AF69C 00000000 */  nop   
/* 0B02A0 800AF6A0 A44A0014 */  sh    $t2, 0x14($v0)
/* 0B02A4 800AF6A4 846B0026 */  lh    $t3, 0x26($v1)
/* 0B02A8 800AF6A8 00000000 */  nop   
/* 0B02AC 800AF6AC A44B0016 */  sh    $t3, 0x16($v0)
.L800AF6B0:
/* 0B02B0 800AF6B0 844C0004 */  lh    $t4, 4($v0)
/* 0B02B4 800AF6B4 00000000 */  nop   
/* 0B02B8 800AF6B8 318DFDFF */  andi  $t5, $t4, 0xfdff
/* 0B02BC 800AF6BC A44D0004 */  sh    $t5, 4($v0)
/* 0B02C0 800AF6C0 844E0004 */  lh    $t6, 4($v0)
/* 0B02C4 800AF6C4 00000000 */  nop   
/* 0B02C8 800AF6C8 35CFA000 */  ori   $t7, $t6, 0xa000
/* 0B02CC 800AF6CC A44F0004 */  sh    $t7, 4($v0)
/* 0B02D0 800AF6D0 8498001A */  lh    $t8, 0x1a($a0)
/* 0B02D4 800AF6D4 00000000 */  nop   
/* 0B02D8 800AF6D8 27190001 */  addiu $t9, $t8, 1
/* 0B02DC 800AF6DC 03E00008 */  jr    $ra
/* 0B02E0 800AF6E0 A499001A */   sh    $t9, 0x1a($a0)

glabel func_800AF6E4
/* 0B02E4 800AF6E4 8C8E006C */  lw    $t6, 0x6c($a0)
/* 0B02E8 800AF6E8 00057940 */  sll   $t7, $a1, 5
/* 0B02EC 800AF6EC 01CF1021 */  addu  $v0, $t6, $t7
/* 0B02F0 800AF6F0 84580004 */  lh    $t8, 4($v0)
/* 0B02F4 800AF6F4 00000000 */  nop   
/* 0B02F8 800AF6F8 33197FFF */  andi  $t9, $t8, 0x7fff
/* 0B02FC 800AF6FC A4590004 */  sh    $t9, 4($v0)
/* 0B0300 800AF700 8488001A */  lh    $t0, 0x1a($a0)
/* 0B0304 800AF704 00000000 */  nop   
/* 0B0308 800AF708 2509FFFF */  addiu $t1, $t0, -1
/* 0B030C 800AF70C 03E00008 */  jr    $ra
/* 0B0310 800AF710 A489001A */   sh    $t1, 0x1a($a0)

glabel func_800AF714
/* 0B0314 800AF714 27BDFF80 */  addiu $sp, $sp, -0x80
/* 0B0318 800AF718 AFBF003C */  sw    $ra, 0x3c($sp)
/* 0B031C 800AF71C AFBE0038 */  sw    $fp, 0x38($sp)
/* 0B0320 800AF720 AFB70034 */  sw    $s7, 0x34($sp)
/* 0B0324 800AF724 AFB60030 */  sw    $s6, 0x30($sp)
/* 0B0328 800AF728 AFB5002C */  sw    $s5, 0x2c($sp)
/* 0B032C 800AF72C AFB40028 */  sw    $s4, 0x28($sp)
/* 0B0330 800AF730 AFB30024 */  sw    $s3, 0x24($sp)
/* 0B0334 800AF734 AFB20020 */  sw    $s2, 0x20($sp)
/* 0B0338 800AF738 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0B033C 800AF73C AFB00018 */  sw    $s0, 0x18($sp)
/* 0B0340 800AF740 AFA50084 */  sw    $a1, 0x84($sp)
/* 0B0344 800AF744 8C930064 */  lw    $s3, 0x64($a0)
/* 0B0348 800AF748 8C970074 */  lw    $s7, 0x74($a0)
/* 0B034C 800AF74C 827E01D6 */  lb    $fp, 0x1d6($s3)
/* 0B0350 800AF750 00809025 */  move  $s2, $a0
/* 0B0354 800AF754 0C004B8A */  jal   func_80012E28
/* 0B0358 800AF758 00008025 */   move  $s0, $zero
/* 0B035C 800AF75C 8E4E0040 */  lw    $t6, 0x40($s2)
/* 0B0360 800AF760 24160002 */  li    $s6, 2
/* 0B0364 800AF764 81CF0057 */  lb    $t7, 0x57($t6)
/* 0B0368 800AF768 241500FF */  li    $s5, 255
/* 0B036C 800AF76C 19E00125 */  blez  $t7, .L800AFC04
/* 0B0370 800AF770 3C14800E */   lui   $s4, %hi(D_800E2E84) # $s4, 0x800e
/* 0B0374 800AF774 3C11800E */  lui   $s1, %hi(D_800E2D00) # $s1, 0x800e
/* 0B0378 800AF778 26312D00 */  addiu $s1, %lo(D_800E2D00) # addiu $s1, $s1, 0x2d00
/* 0B037C 800AF77C 26942E84 */  addiu $s4, %lo(D_800E2E84) # addiu $s4, $s4, 0x2e84
.L800AF780:
/* 0B0380 800AF780 32F80001 */  andi  $t8, $s7, 1
/* 0B0384 800AF784 130000E8 */  beqz  $t8, .L800AFB28
/* 0B0388 800AF788 00000000 */   nop   
/* 0B038C 800AF78C 13C00008 */  beqz  $fp, .L800AF7B0
/* 0B0390 800AF790 240B0001 */   li    $t3, 1
/* 0B0394 800AF794 24010001 */  li    $at, 1
/* 0B0398 800AF798 13C10099 */  beq   $fp, $at, .L800AFA00
/* 0B039C 800AF79C 00000000 */   nop   
/* 0B03A0 800AF7A0 13D60083 */  beq   $fp, $s6, .L800AF9B0
/* 0B03A4 800AF7A4 00000000 */   nop   
/* 0B03A8 800AF7A8 100000AA */  b     .L800AFA54
/* 0B03AC 800AF7AC 00000000 */   nop   
.L800AF7B0:
/* 0B03B0 800AF7B0 0600004C */  bltz  $s0, .L800AF8E4
/* 0B03B4 800AF7B4 2A01000A */   slti  $at, $s0, 0xa
/* 0B03B8 800AF7B8 1020004B */  beqz  $at, .L800AF8E8
/* 0B03BC 800AF7BC 2401000A */   li    $at, 10
/* 0B03C0 800AF7C0 8662016E */  lh    $v0, 0x16e($s3)
/* 0B03C4 800AF7C4 00106140 */  sll   $t4, $s0, 5
/* 0B03C8 800AF7C8 04410002 */  bgez  $v0, .L800AF7D4
/* 0B03CC 800AF7CC 3C18800E */   lui   $t8, %hi(D_800E2CF0) # $t8, 0x800e
/* 0B03D0 800AF7D0 00021023 */  negu  $v0, $v0
.L800AF7D4:
/* 0B03D4 800AF7D4 2442FFE8 */  addiu $v0, $v0, -0x18
/* 0B03D8 800AF7D8 1840009E */  blez  $v0, .L800AFA54
/* 0B03DC 800AF7DC 28410021 */   slti  $at, $v0, 0x21
/* 0B03E0 800AF7E0 8E59006C */  lw    $t9, 0x6c($s2)
/* 0B03E4 800AF7E4 8F182CF0 */  lw    $t8, %lo(D_800E2CF0)($t8)
/* 0B03E8 800AF7E8 032C6821 */  addu  $t5, $t9, $t4
/* 0B03EC 800AF7EC 85AE0008 */  lh    $t6, 8($t5)
/* 0B03F0 800AF7F0 3C0D800E */  lui   $t5, %hi(D_800E2EC4) # $t5, 0x800e
/* 0B03F4 800AF7F4 000E7880 */  sll   $t7, $t6, 2
/* 0B03F8 800AF7F8 25AD2EC4 */  addiu $t5, %lo(D_800E2EC4) # addiu $t5, $t5, 0x2ec4
/* 0B03FC 800AF7FC 00106080 */  sll   $t4, $s0, 2
/* 0B0400 800AF800 030FC821 */  addu  $t9, $t8, $t7
/* 0B0404 800AF804 8F270000 */  lw    $a3, ($t9)
/* 0B0408 800AF808 018D4021 */  addu  $t0, $t4, $t5
/* 0B040C 800AF80C 14200002 */  bnez  $at, .L800AF818
/* 0B0410 800AF810 250A0003 */   addiu $t2, $t0, 3
/* 0B0414 800AF814 24020020 */  li    $v0, 32
.L800AF818:
/* 0B0418 800AF818 00420019 */  multu $v0, $v0
/* 0B041C 800AF81C 90E40014 */  lbu   $a0, 0x14($a3)
/* 0B0420 800AF820 910F0000 */  lbu   $t7, ($t0)
/* 0B0424 800AF824 00024900 */  sll   $t1, $v0, 4
/* 0B0428 800AF828 01E4C823 */  subu  $t9, $t7, $a0
/* 0B042C 800AF82C 28410011 */  slti  $at, $v0, 0x11
/* 0B0430 800AF830 00007012 */  mflo  $t6
/* 0B0434 800AF834 000EC083 */  sra   $t8, $t6, 2
/* 0B0438 800AF838 01381823 */  subu  $v1, $t1, $t8
/* 0B043C 800AF83C 03230019 */  multu $t9, $v1
/* 0B0440 800AF840 91190001 */  lbu   $t9, 1($t0)
/* 0B0444 800AF844 00006012 */  mflo  $t4
/* 0B0448 800AF848 000C6A03 */  sra   $t5, $t4, 8
/* 0B044C 800AF84C 01A47021 */  addu  $t6, $t5, $a0
/* 0B0450 800AF850 000E7E00 */  sll   $t7, $t6, 0x18
/* 0B0454 800AF854 AE2F0000 */  sw    $t7, ($s1)
/* 0B0458 800AF858 90E50015 */  lbu   $a1, 0x15($a3)
/* 0B045C 800AF85C 00000000 */  nop   
/* 0B0460 800AF860 03256023 */  subu  $t4, $t9, $a1
/* 0B0464 800AF864 01830019 */  multu $t4, $v1
/* 0B0468 800AF868 00006812 */  mflo  $t5
/* 0B046C 800AF86C 000D7203 */  sra   $t6, $t5, 8
/* 0B0470 800AF870 00AEC021 */  addu  $t8, $a1, $t6
/* 0B0474 800AF874 0018CC00 */  sll   $t9, $t8, 0x10
/* 0B0478 800AF878 01F96825 */  or    $t5, $t7, $t9
/* 0B047C 800AF87C AE2D0000 */  sw    $t5, ($s1)
/* 0B0480 800AF880 90E60016 */  lbu   $a2, 0x16($a3)
/* 0B0484 800AF884 910E0002 */  lbu   $t6, 2($t0)
/* 0B0488 800AF888 00000000 */  nop   
/* 0B048C 800AF88C 01C6C023 */  subu  $t8, $t6, $a2
/* 0B0490 800AF890 03030019 */  multu $t8, $v1
/* 0B0494 800AF894 00007812 */  mflo  $t7
/* 0B0498 800AF898 000FCA03 */  sra   $t9, $t7, 8
/* 0B049C 800AF89C 00D96021 */  addu  $t4, $a2, $t9
/* 0B04A0 800AF8A0 000C7200 */  sll   $t6, $t4, 8
/* 0B04A4 800AF8A4 01AEC025 */  or    $t8, $t5, $t6
/* 0B04A8 800AF8A8 14200002 */  bnez  $at, .L800AF8B4
/* 0B04AC 800AF8AC AE380000 */   sw    $t8, ($s1)
/* 0B04B0 800AF8B0 24090100 */  li    $t1, 256
.L800AF8B4:
/* 0B04B4 800AF8B4 90E20017 */  lbu   $v0, 0x17($a3)
/* 0B04B8 800AF8B8 91590000 */  lbu   $t9, ($t2)
/* 0B04BC 800AF8BC 8E2F0000 */  lw    $t7, ($s1)
/* 0B04C0 800AF8C0 03226023 */  subu  $t4, $t9, $v0
/* 0B04C4 800AF8C4 01890019 */  multu $t4, $t1
/* 0B04C8 800AF8C8 3C01800E */  lui   $at, %hi(D_800E2D00) # $at, 0x800e
/* 0B04CC 800AF8CC 00006812 */  mflo  $t5
/* 0B04D0 800AF8D0 000D7203 */  sra   $t6, $t5, 8
/* 0B04D4 800AF8D4 004EC021 */  addu  $t8, $v0, $t6
/* 0B04D8 800AF8D8 01F8C825 */  or    $t9, $t7, $t8
/* 0B04DC 800AF8DC 1000005D */  b     .L800AFA54
/* 0B04E0 800AF8E0 AC392D00 */   sw    $t9, %lo(D_800E2D00)($at)
.L800AF8E4:
/* 0B04E4 800AF8E4 2401000A */  li    $at, 10
.L800AF8E8:
/* 0B04E8 800AF8E8 12010009 */  beq   $s0, $at, .L800AF910
/* 0B04EC 800AF8EC 2401000B */   li    $at, 11
/* 0B04F0 800AF8F0 12010011 */  beq   $s0, $at, .L800AF938
/* 0B04F4 800AF8F4 2401000C */   li    $at, 12
/* 0B04F8 800AF8F8 12010019 */  beq   $s0, $at, .L800AF960
/* 0B04FC 800AF8FC 2401000D */   li    $at, 13
/* 0B0500 800AF900 12010021 */  beq   $s0, $at, .L800AF988
/* 0B0504 800AF904 00000000 */   nop   
/* 0B0508 800AF908 10000052 */  b     .L800AFA54
/* 0B050C 800AF90C 00000000 */   nop   
.L800AF910:
/* 0B0510 800AF910 926201DE */  lbu   $v0, 0x1de($s3)
/* 0B0514 800AF914 00000000 */  nop   
/* 0B0518 800AF918 16A20002 */  bne   $s5, $v0, .L800AF924
/* 0B051C 800AF91C 304C000F */   andi  $t4, $v0, 0xf
/* 0B0520 800AF920 00005825 */  move  $t3, $zero
.L800AF924:
/* 0B0524 800AF924 000C6880 */  sll   $t5, $t4, 2
/* 0B0528 800AF928 028D7021 */  addu  $t6, $s4, $t5
/* 0B052C 800AF92C 8DCF0000 */  lw    $t7, ($t6)
/* 0B0530 800AF930 10000048 */  b     .L800AFA54
/* 0B0534 800AF934 AE2F0000 */   sw    $t7, ($s1)
.L800AF938:
/* 0B0538 800AF938 926201DF */  lbu   $v0, 0x1df($s3)
/* 0B053C 800AF93C 00000000 */  nop   
/* 0B0540 800AF940 16A20002 */  bne   $s5, $v0, .L800AF94C
/* 0B0544 800AF944 3058000F */   andi  $t8, $v0, 0xf
/* 0B0548 800AF948 00005825 */  move  $t3, $zero
.L800AF94C:
/* 0B054C 800AF94C 0018C880 */  sll   $t9, $t8, 2
/* 0B0550 800AF950 02996021 */  addu  $t4, $s4, $t9
/* 0B0554 800AF954 8D8D0000 */  lw    $t5, ($t4)
/* 0B0558 800AF958 1000003E */  b     .L800AFA54
/* 0B055C 800AF95C AE2D0000 */   sw    $t5, ($s1)
.L800AF960:
/* 0B0560 800AF960 926201DC */  lbu   $v0, 0x1dc($s3)
/* 0B0564 800AF964 00000000 */  nop   
/* 0B0568 800AF968 16A20002 */  bne   $s5, $v0, .L800AF974
/* 0B056C 800AF96C 304E000F */   andi  $t6, $v0, 0xf
/* 0B0570 800AF970 00005825 */  move  $t3, $zero
.L800AF974:
/* 0B0574 800AF974 000E7880 */  sll   $t7, $t6, 2
/* 0B0578 800AF978 028FC021 */  addu  $t8, $s4, $t7
/* 0B057C 800AF97C 8F190000 */  lw    $t9, ($t8)
/* 0B0580 800AF980 10000034 */  b     .L800AFA54
/* 0B0584 800AF984 AE390000 */   sw    $t9, ($s1)
.L800AF988:
/* 0B0588 800AF988 926201DD */  lbu   $v0, 0x1dd($s3)
/* 0B058C 800AF98C 00000000 */  nop   
/* 0B0590 800AF990 16A20002 */  bne   $s5, $v0, .L800AF99C
/* 0B0594 800AF994 304C000F */   andi  $t4, $v0, 0xf
/* 0B0598 800AF998 00005825 */  move  $t3, $zero
.L800AF99C:
/* 0B059C 800AF99C 000C6880 */  sll   $t5, $t4, 2
/* 0B05A0 800AF9A0 028D7021 */  addu  $t6, $s4, $t5
/* 0B05A4 800AF9A4 8DCF0000 */  lw    $t7, ($t6)
/* 0B05A8 800AF9A8 1000002A */  b     .L800AFA54
/* 0B05AC 800AF9AC AE2F0000 */   sw    $t7, ($s1)
.L800AF9B0:
/* 0B05B0 800AF9B0 16000009 */  bnez  $s0, .L800AF9D8
/* 0B05B4 800AF9B4 24010001 */   li    $at, 1
/* 0B05B8 800AF9B8 927801DC */  lbu   $t8, 0x1dc($s3)
/* 0B05BC 800AF9BC 00000000 */  nop   
/* 0B05C0 800AF9C0 3319000F */  andi  $t9, $t8, 0xf
/* 0B05C4 800AF9C4 00196080 */  sll   $t4, $t9, 2
/* 0B05C8 800AF9C8 028C6821 */  addu  $t5, $s4, $t4
/* 0B05CC 800AF9CC 8DAE0000 */  lw    $t6, ($t5)
/* 0B05D0 800AF9D0 10000020 */  b     .L800AFA54
/* 0B05D4 800AF9D4 AE2E0000 */   sw    $t6, ($s1)
.L800AF9D8:
/* 0B05D8 800AF9D8 1601001E */  bne   $s0, $at, .L800AFA54
/* 0B05DC 800AF9DC 00000000 */   nop   
/* 0B05E0 800AF9E0 926F01DD */  lbu   $t7, 0x1dd($s3)
/* 0B05E4 800AF9E4 00000000 */  nop   
/* 0B05E8 800AF9E8 31F8000F */  andi  $t8, $t7, 0xf
/* 0B05EC 800AF9EC 0018C880 */  sll   $t9, $t8, 2
/* 0B05F0 800AF9F0 02996021 */  addu  $t4, $s4, $t9
/* 0B05F4 800AF9F4 8D8D0000 */  lw    $t5, ($t4)
/* 0B05F8 800AF9F8 10000016 */  b     .L800AFA54
/* 0B05FC 800AF9FC AE2D0000 */   sw    $t5, ($s1)
.L800AFA00:
/* 0B0600 800AFA00 12160003 */  beq   $s0, $s6, .L800AFA10
/* 0B0604 800AFA04 24010003 */   li    $at, 3
/* 0B0608 800AFA08 16010012 */  bne   $s0, $at, .L800AFA54
/* 0B060C 800AFA0C 00000000 */   nop   
.L800AFA10:
/* 0B0610 800AFA10 826E0002 */  lb    $t6, 2($s3)
/* 0B0614 800AFA14 3C198012 */  lui   $t9, %hi(D_80127C88) # $t9, 0x8012
/* 0B0618 800AFA18 31CF0007 */  andi  $t7, $t6, 7
/* 0B061C 800AFA1C 000FC040 */  sll   $t8, $t7, 1
/* 0B0620 800AFA20 27397C88 */  addiu $t9, %lo(D_80127C88) # addiu $t9, $t9, 0x7c88
/* 0B0624 800AFA24 8FAC0084 */  lw    $t4, 0x84($sp)
/* 0B0628 800AFA28 03191821 */  addu  $v1, $t8, $t9
/* 0B062C 800AFA2C 84620000 */  lh    $v0, ($v1)
/* 0B0630 800AFA30 000C6880 */  sll   $t5, $t4, 2
/* 0B0634 800AFA34 004D1021 */  addu  $v0, $v0, $t5
/* 0B0638 800AFA38 28410101 */  slti  $at, $v0, 0x101
/* 0B063C 800AFA3C 14200002 */  bnez  $at, .L800AFA48
/* 0B0640 800AFA40 00000000 */   nop   
/* 0B0644 800AFA44 24020100 */  li    $v0, 256
.L800AFA48:
/* 0B0648 800AFA48 A4620000 */  sh    $v0, ($v1)
/* 0B064C 800AFA4C 3C01800E */  lui   $at, %hi(D_800E2EEC) # $at, 0x800e
/* 0B0650 800AFA50 AC222EEC */  sw    $v0, %lo(D_800E2EEC)($at)
.L800AFA54:
/* 0B0654 800AFA54 11600060 */  beqz  $t3, .L800AFBD8
/* 0B0658 800AFA58 00000000 */   nop   
/* 0B065C 800AFA5C 8E46006C */  lw    $a2, 0x6c($s2)
/* 0B0660 800AFA60 00103940 */  sll   $a3, $s0, 5
/* 0B0664 800AFA64 00C71021 */  addu  $v0, $a2, $a3
/* 0B0668 800AFA68 84430004 */  lh    $v1, 4($v0)
/* 0B066C 800AFA6C 02402025 */  move  $a0, $s2
/* 0B0670 800AFA70 306E8000 */  andi  $t6, $v1, 0x8000
/* 0B0674 800AFA74 15C00009 */  bnez  $t6, .L800AFA9C
/* 0B0678 800AFA78 02002825 */   move  $a1, $s0
/* 0B067C 800AFA7C 0C02BD4B */  jal   func_800AF52C
/* 0B0680 800AFA80 AFA70044 */   sw    $a3, 0x44($sp)
/* 0B0684 800AFA84 8FA70044 */  lw    $a3, 0x44($sp)
/* 0B0688 800AFA88 8E46006C */  lw    $a2, 0x6c($s2)
/* 0B068C 800AFA8C 00000000 */  nop   
/* 0B0690 800AFA90 00C71021 */  addu  $v0, $a2, $a3
/* 0B0694 800AFA94 84430004 */  lh    $v1, 4($v0)
/* 0B0698 800AFA98 00000000 */  nop   
.L800AFA9C:
/* 0B069C 800AFA9C 306F4000 */  andi  $t7, $v1, 0x4000
/* 0B06A0 800AFAA0 11E00007 */  beqz  $t7, .L800AFAC0
/* 0B06A4 800AFAA4 30790400 */   andi  $t9, $v1, 0x400
/* 0B06A8 800AFAA8 0010C140 */  sll   $t8, $s0, 5
/* 0B06AC 800AFAAC 00D82821 */  addu  $a1, $a2, $t8
/* 0B06B0 800AFAB0 0C02BF97 */  jal   func_800AFE5C
/* 0B06B4 800AFAB4 02402025 */   move  $a0, $s2
/* 0B06B8 800AFAB8 10000048 */  b     .L800AFBDC
/* 0B06BC 800AFABC AE200000 */   sw    $zero, ($s1)
.L800AFAC0:
/* 0B06C0 800AFAC0 13200006 */  beqz  $t9, .L800AFADC
/* 0B06C4 800AFAC4 02402025 */   move  $a0, $s2
/* 0B06C8 800AFAC8 00106140 */  sll   $t4, $s0, 5
/* 0B06CC 800AFACC 0C02BF97 */  jal   func_800AFE5C
/* 0B06D0 800AFAD0 00CC2821 */   addu  $a1, $a2, $t4
/* 0B06D4 800AFAD4 10000041 */  b     .L800AFBDC
/* 0B06D8 800AFAD8 AE200000 */   sw    $zero, ($s1)
.L800AFADC:
/* 0B06DC 800AFADC 844D000A */  lh    $t5, 0xa($v0)
/* 0B06E0 800AFAE0 8FAE0084 */  lw    $t6, 0x84($sp)
/* 0B06E4 800AFAE4 02402025 */  move  $a0, $s2
/* 0B06E8 800AFAE8 01AE7821 */  addu  $t7, $t5, $t6
/* 0B06EC 800AFAEC A44F000A */  sh    $t7, 0xa($v0)
/* 0B06F0 800AFAF0 8E46006C */  lw    $a2, 0x6c($s2)
/* 0B06F4 800AFAF4 00106940 */  sll   $t5, $s0, 5
/* 0B06F8 800AFAF8 00C71021 */  addu  $v0, $a2, $a3
/* 0B06FC 800AFAFC 8C590000 */  lw    $t9, ($v0)
/* 0B0700 800AFB00 8458000A */  lh    $t8, 0xa($v0)
/* 0B0704 800AFB04 872C0040 */  lh    $t4, 0x40($t9)
/* 0B0708 800AFB08 00000000 */  nop   
/* 0B070C 800AFB0C 030C082A */  slt   $at, $t8, $t4
/* 0B0710 800AFB10 14200031 */  bnez  $at, .L800AFBD8
/* 0B0714 800AFB14 00000000 */   nop   
/* 0B0718 800AFB18 0C02BF97 */  jal   func_800AFE5C
/* 0B071C 800AFB1C 00CD2821 */   addu  $a1, $a2, $t5
/* 0B0720 800AFB20 1000002E */  b     .L800AFBDC
/* 0B0724 800AFB24 AE200000 */   sw    $zero, ($s1)
.L800AFB28:
/* 0B0728 800AFB28 8E46006C */  lw    $a2, 0x6c($s2)
/* 0B072C 800AFB2C 00107140 */  sll   $t6, $s0, 5
/* 0B0730 800AFB30 00CE1021 */  addu  $v0, $a2, $t6
/* 0B0734 800AFB34 84430004 */  lh    $v1, 4($v0)
/* 0B0738 800AFB38 00000000 */  nop   
/* 0B073C 800AFB3C 306F8000 */  andi  $t7, $v1, 0x8000
/* 0B0740 800AFB40 11E00025 */  beqz  $t7, .L800AFBD8
/* 0B0744 800AFB44 30794000 */   andi  $t9, $v1, 0x4000
/* 0B0748 800AFB48 13200009 */  beqz  $t9, .L800AFB70
/* 0B074C 800AFB4C 306C0400 */   andi  $t4, $v1, 0x400
/* 0B0750 800AFB50 0010C140 */  sll   $t8, $s0, 5
/* 0B0754 800AFB54 00D81021 */  addu  $v0, $a2, $t8
/* 0B0758 800AFB58 A0400006 */  sb    $zero, 6($v0)
/* 0B075C 800AFB5C 02402025 */  move  $a0, $s2
/* 0B0760 800AFB60 0C02BDB9 */  jal   func_800AF6E4
/* 0B0764 800AFB64 02002825 */   move  $a1, $s0
/* 0B0768 800AFB68 10000011 */  b     .L800AFBB0
/* 0B076C 800AFB6C 00000000 */   nop   
.L800AFB70:
/* 0B0770 800AFB70 1180000D */  beqz  $t4, .L800AFBA8
/* 0B0774 800AFB74 02402025 */   move  $a0, $s2
/* 0B0778 800AFB78 00106940 */  sll   $t5, $s0, 5
/* 0B077C 800AFB7C 346E0200 */  ori   $t6, $v1, 0x200
/* 0B0780 800AFB80 00CD2021 */  addu  $a0, $a2, $t5
/* 0B0784 800AFB84 A44E0004 */  sh    $t6, 4($v0)
/* 0B0788 800AFB88 908F0006 */  lbu   $t7, 6($a0)
/* 0B078C 800AFB8C 02402025 */  move  $a0, $s2
/* 0B0790 800AFB90 15E00007 */  bnez  $t7, .L800AFBB0
/* 0B0794 800AFB94 00000000 */   nop   
/* 0B0798 800AFB98 0C02BDB9 */  jal   func_800AF6E4
/* 0B079C 800AFB9C 02002825 */   move  $a1, $s0
/* 0B07A0 800AFBA0 10000003 */  b     .L800AFBB0
/* 0B07A4 800AFBA4 00000000 */   nop   
.L800AFBA8:
/* 0B07A8 800AFBA8 0C02BDB9 */  jal   func_800AF6E4
/* 0B07AC 800AFBAC 02002825 */   move  $a1, $s0
.L800AFBB0:
/* 0B07B0 800AFBB0 12160003 */  beq   $s0, $s6, .L800AFBC0
/* 0B07B4 800AFBB4 24010003 */   li    $at, 3
/* 0B07B8 800AFBB8 16010007 */  bne   $s0, $at, .L800AFBD8
/* 0B07BC 800AFBBC 00000000 */   nop   
.L800AFBC0:
/* 0B07C0 800AFBC0 82790002 */  lb    $t9, 2($s3)
/* 0B07C4 800AFBC4 3C018012 */  lui   $at, 0x8012
/* 0B07C8 800AFBC8 33380007 */  andi  $t8, $t9, 7
/* 0B07CC 800AFBCC 00186040 */  sll   $t4, $t8, 1
/* 0B07D0 800AFBD0 002C0821 */  addu  $at, $at, $t4
/* 0B07D4 800AFBD4 A4207C88 */  sh    $zero, 0x7c88($at)
.L800AFBD8:
/* 0B07D8 800AFBD8 AE200000 */  sw    $zero, ($s1)
.L800AFBDC:
/* 0B07DC 800AFBDC 240E0100 */  li    $t6, 256
/* 0B07E0 800AFBE0 3C01800E */  lui   $at, %hi(D_800E2EEC) # $at, 0x800e
/* 0B07E4 800AFBE4 AC2E2EEC */  sw    $t6, %lo(D_800E2EEC)($at)
/* 0B07E8 800AFBE8 8E4F0040 */  lw    $t7, 0x40($s2)
/* 0B07EC 800AFBEC 26100001 */  addiu $s0, $s0, 1
/* 0B07F0 800AFBF0 81F90057 */  lb    $t9, 0x57($t7)
/* 0B07F4 800AFBF4 00176842 */  srl   $t5, $s7, 1
/* 0B07F8 800AFBF8 0219082A */  slt   $at, $s0, $t9
/* 0B07FC 800AFBFC 1420FEE0 */  bnez  $at, .L800AF780
/* 0B0800 800AFC00 01A0B825 */   move  $s7, $t5
.L800AFC04:
/* 0B0804 800AFC04 0C004BCC */  jal   func_80012F30
/* 0B0808 800AFC08 02402025 */   move  $a0, $s2
/* 0B080C 800AFC0C 8FBF003C */  lw    $ra, 0x3c($sp)
/* 0B0810 800AFC10 8FB00018 */  lw    $s0, 0x18($sp)
/* 0B0814 800AFC14 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0B0818 800AFC18 8FB20020 */  lw    $s2, 0x20($sp)
/* 0B081C 800AFC1C 8FB30024 */  lw    $s3, 0x24($sp)
/* 0B0820 800AFC20 8FB40028 */  lw    $s4, 0x28($sp)
/* 0B0824 800AFC24 8FB5002C */  lw    $s5, 0x2c($sp)
/* 0B0828 800AFC28 8FB60030 */  lw    $s6, 0x30($sp)
/* 0B082C 800AFC2C 8FB70034 */  lw    $s7, 0x34($sp)
/* 0B0830 800AFC30 8FBE0038 */  lw    $fp, 0x38($sp)
/* 0B0834 800AFC34 03E00008 */  jr    $ra
/* 0B0838 800AFC38 27BD0080 */   addiu $sp, $sp, 0x80

glabel func_800AFC3C
/* 0B083C 800AFC3C 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0B0840 800AFC40 AFBF0034 */  sw    $ra, 0x34($sp)
/* 0B0844 800AFC44 AFB60030 */  sw    $s6, 0x30($sp)
/* 0B0848 800AFC48 AFB5002C */  sw    $s5, 0x2c($sp)
/* 0B084C 800AFC4C AFB40028 */  sw    $s4, 0x28($sp)
/* 0B0850 800AFC50 AFB30024 */  sw    $s3, 0x24($sp)
/* 0B0854 800AFC54 AFB20020 */  sw    $s2, 0x20($sp)
/* 0B0858 800AFC58 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0B085C 800AFC5C AFB00018 */  sw    $s0, 0x18($sp)
/* 0B0860 800AFC60 8C8E0040 */  lw    $t6, 0x40($a0)
/* 0B0864 800AFC64 8C950074 */  lw    $s5, 0x74($a0)
/* 0B0868 800AFC68 81C70057 */  lb    $a3, 0x57($t6)
/* 0B086C 800AFC6C 00809025 */  move  $s2, $a0
/* 0B0870 800AFC70 00A0B025 */  move  $s6, $a1
/* 0B0874 800AFC74 18E0006F */  blez  $a3, .L800AFE34
/* 0B0878 800AFC78 00009825 */   move  $s3, $zero
/* 0B087C 800AFC7C 0000A025 */  move  $s4, $zero
.L800AFC80:
/* 0B0880 800AFC80 8E46006C */  lw    $a2, 0x6c($s2)
/* 0B0884 800AFC84 32AF0001 */  andi  $t7, $s5, 1
/* 0B0888 800AFC88 11E00032 */  beqz  $t7, .L800AFD54
/* 0B088C 800AFC8C 00D41821 */   addu  $v1, $a2, $s4
/* 0B0890 800AFC90 84620004 */  lh    $v0, 4($v1)
/* 0B0894 800AFC94 02402025 */  move  $a0, $s2
/* 0B0898 800AFC98 30588000 */  andi  $t8, $v0, 0x8000
/* 0B089C 800AFC9C 17000009 */  bnez  $t8, .L800AFCC4
/* 0B08A0 800AFCA0 30594000 */   andi  $t9, $v0, 0x4000
/* 0B08A4 800AFCA4 0C02BD4B */  jal   func_800AF52C
/* 0B08A8 800AFCA8 02602825 */   move  $a1, $s3
/* 0B08AC 800AFCAC 8E46006C */  lw    $a2, 0x6c($s2)
/* 0B08B0 800AFCB0 00000000 */  nop   
/* 0B08B4 800AFCB4 00D41821 */  addu  $v1, $a2, $s4
/* 0B08B8 800AFCB8 84620004 */  lh    $v0, 4($v1)
/* 0B08BC 800AFCBC 00000000 */  nop   
/* 0B08C0 800AFCC0 30594000 */  andi  $t9, $v0, 0x4000
.L800AFCC4:
/* 0B08C4 800AFCC4 13200007 */  beqz  $t9, .L800AFCE4
/* 0B08C8 800AFCC8 30490400 */   andi  $t1, $v0, 0x400
/* 0B08CC 800AFCCC 00134140 */  sll   $t0, $s3, 5
/* 0B08D0 800AFCD0 00C82821 */  addu  $a1, $a2, $t0
/* 0B08D4 800AFCD4 0C02BF97 */  jal   func_800AFE5C
/* 0B08D8 800AFCD8 02402025 */   move  $a0, $s2
/* 0B08DC 800AFCDC 10000019 */  b     .L800AFD44
/* 0B08E0 800AFCE0 8E590040 */   lw    $t9, 0x40($s2)
.L800AFCE4:
/* 0B08E4 800AFCE4 11200006 */  beqz  $t1, .L800AFD00
/* 0B08E8 800AFCE8 02402025 */   move  $a0, $s2
/* 0B08EC 800AFCEC 00135140 */  sll   $t2, $s3, 5
/* 0B08F0 800AFCF0 0C02BF97 */  jal   func_800AFE5C
/* 0B08F4 800AFCF4 00CA2821 */   addu  $a1, $a2, $t2
/* 0B08F8 800AFCF8 10000012 */  b     .L800AFD44
/* 0B08FC 800AFCFC 8E590040 */   lw    $t9, 0x40($s2)
.L800AFD00:
/* 0B0900 800AFD00 846B000A */  lh    $t3, 0xa($v1)
/* 0B0904 800AFD04 02402025 */  move  $a0, $s2
/* 0B0908 800AFD08 01766021 */  addu  $t4, $t3, $s6
/* 0B090C 800AFD0C A46C000A */  sh    $t4, 0xa($v1)
/* 0B0910 800AFD10 8E46006C */  lw    $a2, 0x6c($s2)
/* 0B0914 800AFD14 0013C140 */  sll   $t8, $s3, 5
/* 0B0918 800AFD18 00D41821 */  addu  $v1, $a2, $s4
/* 0B091C 800AFD1C 8C6E0000 */  lw    $t6, ($v1)
/* 0B0920 800AFD20 846D000A */  lh    $t5, 0xa($v1)
/* 0B0924 800AFD24 85CF0040 */  lh    $t7, 0x40($t6)
/* 0B0928 800AFD28 00000000 */  nop   
/* 0B092C 800AFD2C 01AF082A */  slt   $at, $t5, $t7
/* 0B0930 800AFD30 14200003 */  bnez  $at, .L800AFD40
/* 0B0934 800AFD34 00000000 */   nop   
/* 0B0938 800AFD38 0C02BF97 */  jal   func_800AFE5C
/* 0B093C 800AFD3C 00D82821 */   addu  $a1, $a2, $t8
.L800AFD40:
/* 0B0940 800AFD40 8E590040 */  lw    $t9, 0x40($s2)
.L800AFD44:
/* 0B0944 800AFD44 00000000 */  nop   
/* 0B0948 800AFD48 83270057 */  lb    $a3, 0x57($t9)
/* 0B094C 800AFD4C 10000034 */  b     .L800AFE20
/* 0B0950 800AFD50 26730001 */   addiu $s3, $s3, 1
.L800AFD54:
/* 0B0954 800AFD54 84620004 */  lh    $v0, 4($v1)
/* 0B0958 800AFD58 00000000 */  nop   
/* 0B095C 800AFD5C 30488000 */  andi  $t0, $v0, 0x8000
/* 0B0960 800AFD60 1100002E */  beqz  $t0, .L800AFE1C
/* 0B0964 800AFD64 30494000 */   andi  $t1, $v0, 0x4000
/* 0B0968 800AFD68 11200015 */  beqz  $t1, .L800AFDC0
/* 0B096C 800AFD6C 304C0400 */   andi  $t4, $v0, 0x400
/* 0B0970 800AFD70 00135140 */  sll   $t2, $s3, 5
/* 0B0974 800AFD74 00CA8821 */  addu  $s1, $a2, $t2
/* 0B0978 800AFD78 92300006 */  lbu   $s0, 6($s1)
/* 0B097C 800AFD7C 02202825 */  move  $a1, $s1
/* 0B0980 800AFD80 2610FFC0 */  addiu $s0, $s0, -0x40
/* 0B0984 800AFD84 06010002 */  bgez  $s0, .L800AFD90
/* 0B0988 800AFD88 02402025 */   move  $a0, $s2
/* 0B098C 800AFD8C 00008025 */  move  $s0, $zero
.L800AFD90:
/* 0B0990 800AFD90 0C02BF97 */  jal   func_800AFE5C
/* 0B0994 800AFD94 A2300006 */   sb    $s0, 6($s1)
/* 0B0998 800AFD98 16000004 */  bnez  $s0, .L800AFDAC
/* 0B099C 800AFD9C A2300006 */   sb    $s0, 6($s1)
/* 0B09A0 800AFDA0 02402025 */  move  $a0, $s2
/* 0B09A4 800AFDA4 0C02BDB9 */  jal   func_800AF6E4
/* 0B09A8 800AFDA8 02602825 */   move  $a1, $s3
.L800AFDAC:
/* 0B09AC 800AFDAC 8E4B0040 */  lw    $t3, 0x40($s2)
/* 0B09B0 800AFDB0 00000000 */  nop   
/* 0B09B4 800AFDB4 81670057 */  lb    $a3, 0x57($t3)
/* 0B09B8 800AFDB8 10000019 */  b     .L800AFE20
/* 0B09BC 800AFDBC 26730001 */   addiu $s3, $s3, 1
.L800AFDC0:
/* 0B09C0 800AFDC0 11800010 */  beqz  $t4, .L800AFE04
/* 0B09C4 800AFDC4 02402025 */   move  $a0, $s2
/* 0B09C8 800AFDC8 00137140 */  sll   $t6, $s3, 5
/* 0B09CC 800AFDCC 344D0200 */  ori   $t5, $v0, 0x200
/* 0B09D0 800AFDD0 00CE2021 */  addu  $a0, $a2, $t6
/* 0B09D4 800AFDD4 A46D0004 */  sh    $t5, 4($v1)
/* 0B09D8 800AFDD8 908F0006 */  lbu   $t7, 6($a0)
/* 0B09DC 800AFDDC 02402025 */  move  $a0, $s2
/* 0B09E0 800AFDE0 15E00003 */  bnez  $t7, .L800AFDF0
/* 0B09E4 800AFDE4 00000000 */   nop   
/* 0B09E8 800AFDE8 0C02BDB9 */  jal   func_800AF6E4
/* 0B09EC 800AFDEC 02602825 */   move  $a1, $s3
.L800AFDF0:
/* 0B09F0 800AFDF0 8E580040 */  lw    $t8, 0x40($s2)
/* 0B09F4 800AFDF4 00000000 */  nop   
/* 0B09F8 800AFDF8 83070057 */  lb    $a3, 0x57($t8)
/* 0B09FC 800AFDFC 10000008 */  b     .L800AFE20
/* 0B0A00 800AFE00 26730001 */   addiu $s3, $s3, 1
.L800AFE04:
/* 0B0A04 800AFE04 0C02BDB9 */  jal   func_800AF6E4
/* 0B0A08 800AFE08 02602825 */   move  $a1, $s3
/* 0B0A0C 800AFE0C 8E590040 */  lw    $t9, 0x40($s2)
/* 0B0A10 800AFE10 00000000 */  nop   
/* 0B0A14 800AFE14 83270057 */  lb    $a3, 0x57($t9)
/* 0B0A18 800AFE18 00000000 */  nop   
.L800AFE1C:
/* 0B0A1C 800AFE1C 26730001 */  addiu $s3, $s3, 1
.L800AFE20:
/* 0B0A20 800AFE20 0267082A */  slt   $at, $s3, $a3
/* 0B0A24 800AFE24 00154042 */  srl   $t0, $s5, 1
/* 0B0A28 800AFE28 26940020 */  addiu $s4, $s4, 0x20
/* 0B0A2C 800AFE2C 1420FF94 */  bnez  $at, .L800AFC80
/* 0B0A30 800AFE30 0100A825 */   move  $s5, $t0
.L800AFE34:
/* 0B0A34 800AFE34 8FBF0034 */  lw    $ra, 0x34($sp)
/* 0B0A38 800AFE38 8FB00018 */  lw    $s0, 0x18($sp)
/* 0B0A3C 800AFE3C 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0B0A40 800AFE40 8FB20020 */  lw    $s2, 0x20($sp)
/* 0B0A44 800AFE44 8FB30024 */  lw    $s3, 0x24($sp)
/* 0B0A48 800AFE48 8FB40028 */  lw    $s4, 0x28($sp)
/* 0B0A4C 800AFE4C 8FB5002C */  lw    $s5, 0x2c($sp)
/* 0B0A50 800AFE50 8FB60030 */  lw    $s6, 0x30($sp)
/* 0B0A54 800AFE54 03E00008 */  jr    $ra
/* 0B0A58 800AFE58 27BD0038 */   addiu $sp, $sp, 0x38

glabel func_800AFE5C
/* 0B0A5C 800AFE5C 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0B0A60 800AFE60 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0B0A64 800AFE64 AFB50028 */  sw    $s5, 0x28($sp)
/* 0B0A68 800AFE68 AFB40024 */  sw    $s4, 0x24($sp)
/* 0B0A6C 800AFE6C AFB30020 */  sw    $s3, 0x20($sp)
/* 0B0A70 800AFE70 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0B0A74 800AFE74 AFB10018 */  sw    $s1, 0x18($sp)
/* 0B0A78 800AFE78 AFB00014 */  sw    $s0, 0x14($sp)
/* 0B0A7C 800AFE7C 84A20004 */  lh    $v0, 4($a1)
/* 0B0A80 800AFE80 8CB40000 */  lw    $s4, ($a1)
/* 0B0A84 800AFE84 304E4000 */  andi  $t6, $v0, 0x4000
/* 0B0A88 800AFE88 00A09025 */  move  $s2, $a1
/* 0B0A8C 800AFE8C 11C00013 */  beqz  $t6, .L800AFEDC
/* 0B0A90 800AFE90 0080A825 */   move  $s5, $a0
/* 0B0A94 800AFE94 0C02C2EB */  jal   func_800B0BAC
/* 0B0A98 800AFE98 00000000 */   nop   
/* 0B0A9C 800AFE9C 10400003 */  beqz  $v0, .L800AFEAC
/* 0B0AA0 800AFEA0 00402025 */   move  $a0, $v0
/* 0B0AA4 800AFEA4 0C003A74 */  jal   func_8000E9D0
/* 0B0AA8 800AFEA8 00000000 */   nop   
.L800AFEAC:
/* 0B0AAC 800AFEAC 92420006 */  lbu   $v0, 6($s2)
/* 0B0AB0 800AFEB0 864F0004 */  lh    $t7, 4($s2)
/* 0B0AB4 800AFEB4 24420040 */  addiu $v0, $v0, 0x40
/* 0B0AB8 800AFEB8 28410100 */  slti  $at, $v0, 0x100
/* 0B0ABC 800AFEBC 31F8DFFF */  andi  $t8, $t7, 0xdfff
/* 0B0AC0 800AFEC0 14200004 */  bnez  $at, .L800AFED4
/* 0B0AC4 800AFEC4 A6580004 */   sh    $t8, 4($s2)
/* 0B0AC8 800AFEC8 241900FF */  li    $t9, 255
/* 0B0ACC 800AFECC 10000047 */  b     .L800AFFEC
/* 0B0AD0 800AFED0 A2590006 */   sb    $t9, 6($s2)
.L800AFED4:
/* 0B0AD4 800AFED4 10000045 */  b     .L800AFFEC
/* 0B0AD8 800AFED8 A2420006 */   sb    $v0, 6($s2)
.L800AFEDC:
/* 0B0ADC 800AFEDC 30480400 */  andi  $t0, $v0, 0x400
/* 0B0AE0 800AFEE0 1100001F */  beqz  $t0, .L800AFF60
/* 0B0AE4 800AFEE4 00000000 */   nop   
/* 0B0AE8 800AFEE8 92490006 */  lbu   $t1, 6($s2)
/* 0B0AEC 800AFEEC 924A0007 */  lbu   $t2, 7($s2)
/* 0B0AF0 800AFEF0 02A02025 */  move  $a0, $s5
/* 0B0AF4 800AFEF4 012A082A */  slt   $at, $t1, $t2
/* 0B0AF8 800AFEF8 1020003D */  beqz  $at, .L800AFFF0
/* 0B0AFC 800AFEFC 8FBF002C */   lw    $ra, 0x2c($sp)
/* 0B0B00 800AFF00 0C02C1A6 */  jal   func_800B0698
/* 0B0B04 800AFF04 02402825 */   move  $a1, $s2
/* 0B0B08 800AFF08 864B0004 */  lh    $t3, 4($s2)
/* 0B0B0C 800AFF0C 00408025 */  move  $s0, $v0
/* 0B0B10 800AFF10 316CDFFF */  andi  $t4, $t3, 0xdfff
/* 0B0B14 800AFF14 10400035 */  beqz  $v0, .L800AFFEC
/* 0B0B18 800AFF18 A64C0004 */   sh    $t4, 4($s2)
/* 0B0B1C 800AFF1C 0C003A74 */  jal   func_8000E9D0
/* 0B0B20 800AFF20 00402025 */   move  $a0, $v0
/* 0B0B24 800AFF24 8E0E0040 */  lw    $t6, 0x40($s0)
/* 0B0B28 800AFF28 924D0006 */  lbu   $t5, 6($s2)
/* 0B0B2C 800AFF2C 35CF2000 */  ori   $t7, $t6, 0x2000
/* 0B0B30 800AFF30 AE0F0040 */  sw    $t7, 0x40($s0)
/* 0B0B34 800AFF34 A20D0074 */  sb    $t5, 0x74($s0)
/* 0B0B38 800AFF38 92590006 */  lbu   $t9, 6($s2)
/* 0B0B3C 800AFF3C 8E58000C */  lw    $t8, 0xc($s2)
/* 0B0B40 800AFF40 00194080 */  sll   $t0, $t9, 2
/* 0B0B44 800AFF44 03084821 */  addu  $t1, $t8, $t0
/* 0B0B48 800AFF48 AD300000 */  sw    $s0, ($t1)
/* 0B0B4C 800AFF4C 924A0006 */  lbu   $t2, 6($s2)
/* 0B0B50 800AFF50 00000000 */  nop   
/* 0B0B54 800AFF54 254B0001 */  addiu $t3, $t2, 1
/* 0B0B58 800AFF58 10000024 */  b     .L800AFFEC
/* 0B0B5C 800AFF5C A24B0006 */   sb    $t3, 6($s2)
.L800AFF60:
/* 0B0B60 800AFF60 8642000A */  lh    $v0, 0xa($s2)
/* 0B0B64 800AFF64 86830040 */  lh    $v1, 0x40($s4)
/* 0B0B68 800AFF68 2413DFFF */  li    $s3, -8193
/* 0B0B6C 800AFF6C 0043082A */  slt   $at, $v0, $v1
/* 0B0B70 800AFF70 1420001E */  bnez  $at, .L800AFFEC
/* 0B0B74 800AFF74 00436023 */   subu  $t4, $v0, $v1
.L800AFF78:
/* 0B0B78 800AFF78 A64C000A */  sh    $t4, 0xa($s2)
/* 0B0B7C 800AFF7C 868D0042 */  lh    $t5, 0x42($s4)
/* 0B0B80 800AFF80 00008825 */  move  $s1, $zero
/* 0B0B84 800AFF84 19A00013 */  blez  $t5, .L800AFFD4
/* 0B0B88 800AFF88 02A02025 */   move  $a0, $s5
.L800AFF8C:
/* 0B0B8C 800AFF8C 0C02C44C */  jal   func_800B1130
/* 0B0B90 800AFF90 02402825 */   move  $a1, $s2
/* 0B0B94 800AFF94 10400006 */  beqz  $v0, .L800AFFB0
/* 0B0B98 800AFF98 00408025 */   move  $s0, $v0
/* 0B0B9C 800AFF9C 0C003A74 */  jal   func_8000E9D0
/* 0B0BA0 800AFFA0 00402025 */   move  $a0, $v0
/* 0B0BA4 800AFFA4 8645000A */  lh    $a1, 0xa($s2)
/* 0B0BA8 800AFFA8 0C02C8BF */  jal   func_800B22FC
/* 0B0BAC 800AFFAC 02002025 */   move  $a0, $s0
.L800AFFB0:
/* 0B0BB0 800AFFB0 864E0004 */  lh    $t6, 4($s2)
/* 0B0BB4 800AFFB4 26310001 */  addiu $s1, $s1, 1
/* 0B0BB8 800AFFB8 01D37824 */  and   $t7, $t6, $s3
/* 0B0BBC 800AFFBC A64F0004 */  sh    $t7, 4($s2)
/* 0B0BC0 800AFFC0 86990042 */  lh    $t9, 0x42($s4)
/* 0B0BC4 800AFFC4 00000000 */  nop   
/* 0B0BC8 800AFFC8 0239082A */  slt   $at, $s1, $t9
/* 0B0BCC 800AFFCC 1420FFEF */  bnez  $at, .L800AFF8C
/* 0B0BD0 800AFFD0 02A02025 */   move  $a0, $s5
.L800AFFD4:
/* 0B0BD4 800AFFD4 8642000A */  lh    $v0, 0xa($s2)
/* 0B0BD8 800AFFD8 86830040 */  lh    $v1, 0x40($s4)
/* 0B0BDC 800AFFDC 00000000 */  nop   
/* 0B0BE0 800AFFE0 0043082A */  slt   $at, $v0, $v1
/* 0B0BE4 800AFFE4 1020FFE4 */  beqz  $at, .L800AFF78
/* 0B0BE8 800AFFE8 00436023 */   subu  $t4, $v0, $v1
.L800AFFEC:
/* 0B0BEC 800AFFEC 8FBF002C */  lw    $ra, 0x2c($sp)
.L800AFFF0:
/* 0B0BF0 800AFFF0 8FB00014 */  lw    $s0, 0x14($sp)
/* 0B0BF4 800AFFF4 8FB10018 */  lw    $s1, 0x18($sp)
/* 0B0BF8 800AFFF8 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0B0BFC 800AFFFC 8FB30020 */  lw    $s3, 0x20($sp)
/* 0B0C00 800B0000 8FB40024 */  lw    $s4, 0x24($sp)
/* 0B0C04 800B0004 8FB50028 */  lw    $s5, 0x28($sp)
/* 0B0C08 800B0008 03E00008 */  jr    $ra
/* 0B0C0C 800B000C 27BD0030 */   addiu $sp, $sp, 0x30

glabel func_800B0010
/* 0B0C10 800B0010 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 0B0C14 800B0014 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B0C18 800B0018 AFB10018 */  sw    $s1, 0x18($sp)
/* 0B0C1C 800B001C AFB00014 */  sw    $s0, 0x14($sp)
/* 0B0C20 800B0020 AFA50044 */  sw    $a1, 0x44($sp)
/* 0B0C24 800B0024 AFA60048 */  sw    $a2, 0x48($sp)
/* 0B0C28 800B0028 8CEE0000 */  lw    $t6, ($a3)
/* 0B0C2C 800B002C 00808025 */  move  $s0, $a0
/* 0B0C30 800B0030 31CF0070 */  andi  $t7, $t6, 0x70
/* 0B0C34 800B0034 11E0000A */  beqz  $t7, .L800B0060
/* 0B0C38 800B0038 00E08825 */   move  $s1, $a3
/* 0B0C3C 800B003C C4E40030 */  lwc1  $f4, 0x30($a3)
/* 0B0C40 800B0040 00000000 */  nop   
/* 0B0C44 800B0044 E484001C */  swc1  $f4, 0x1c($a0)
/* 0B0C48 800B0048 C4E60034 */  lwc1  $f6, 0x34($a3)
/* 0B0C4C 800B004C 00000000 */  nop   
/* 0B0C50 800B0050 E4860020 */  swc1  $f6, 0x20($a0)
/* 0B0C54 800B0054 C4E80038 */  lwc1  $f8, 0x38($a3)
/* 0B0C58 800B0058 10000007 */  b     .L800B0078
/* 0B0C5C 800B005C E4880024 */   swc1  $f8, 0x24($a0)
.L800B0060:
/* 0B0C60 800B0060 44805000 */  mtc1  $zero, $f10
/* 0B0C64 800B0064 44808000 */  mtc1  $zero, $f16
/* 0B0C68 800B0068 44809000 */  mtc1  $zero, $f18
/* 0B0C6C 800B006C E60A001C */  swc1  $f10, 0x1c($s0)
/* 0B0C70 800B0070 E6100020 */  swc1  $f16, 0x20($s0)
/* 0B0C74 800B0074 E6120024 */  swc1  $f18, 0x24($s0)
.L800B0078:
/* 0B0C78 800B0078 8E23005C */  lw    $v1, 0x5c($s1)
/* 0B0C7C 800B007C 00000000 */  nop   
/* 0B0C80 800B0080 30780700 */  andi  $t8, $v1, 0x700
/* 0B0C84 800B0084 1300003C */  beqz  $t8, .L800B0178
/* 0B0C88 800B0088 03001825 */   move  $v1, $t8
/* 0B0C8C 800B008C 33190100 */  andi  $t9, $t8, 0x100
/* 0B0C90 800B0090 13200013 */  beqz  $t9, .L800B00E0
/* 0B0C94 800B0094 30680200 */   andi  $t0, $v1, 0x200
/* 0B0C98 800B0098 8E250074 */  lw    $a1, 0x74($s1)
/* 0B0C9C 800B009C AFB8003C */  sw    $t8, 0x3c($sp)
/* 0B0CA0 800B00A0 0C01BE53 */  jal   func_8006F94C
/* 0B0CA4 800B00A4 00052023 */   negu  $a0, $a1
/* 0B0CA8 800B00A8 44822000 */  mtc1  $v0, $f4
/* 0B0CAC 800B00AC 3C01800F */  lui   $at, %hi(D_800E8B9C) # $at, 0x800f
/* 0B0CB0 800B00B0 468021A0 */  cvt.s.w $f6, $f4
/* 0B0CB4 800B00B4 C42B8B98 */  lwc1  $f11, %lo(D_800E8B98)($at)
/* 0B0CB8 800B00B8 C42A8B9C */  lwc1  $f10, %lo(D_800E8B9C)($at)
/* 0B0CBC 800B00BC 46003221 */  cvt.d.s $f8, $f6
/* 0B0CC0 800B00C0 462A4402 */  mul.d $f16, $f8, $f10
/* 0B0CC4 800B00C4 C612001C */  lwc1  $f18, 0x1c($s0)
/* 0B0CC8 800B00C8 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B0CCC 800B00CC 46009121 */  cvt.d.s $f4, $f18
/* 0B0CD0 800B00D0 46302180 */  add.d $f6, $f4, $f16
/* 0B0CD4 800B00D4 46203220 */  cvt.s.d $f8, $f6
/* 0B0CD8 800B00D8 E608001C */  swc1  $f8, 0x1c($s0)
/* 0B0CDC 800B00DC 30680200 */  andi  $t0, $v1, 0x200
.L800B00E0:
/* 0B0CE0 800B00E0 11000013 */  beqz  $t0, .L800B0130
/* 0B0CE4 800B00E4 30690400 */   andi  $t1, $v1, 0x400
/* 0B0CE8 800B00E8 8E250078 */  lw    $a1, 0x78($s1)
/* 0B0CEC 800B00EC AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B0CF0 800B00F0 0C01BE53 */  jal   func_8006F94C
/* 0B0CF4 800B00F4 00052023 */   negu  $a0, $a1
/* 0B0CF8 800B00F8 44825000 */  mtc1  $v0, $f10
/* 0B0CFC 800B00FC 3C01800F */  lui   $at, %hi(D_800E8BA4) # $at, 0x800f
/* 0B0D00 800B0100 468054A0 */  cvt.s.w $f18, $f10
/* 0B0D04 800B0104 C4318BA0 */  lwc1  $f17, %lo(D_800E8BA0)($at)
/* 0B0D08 800B0108 C4308BA4 */  lwc1  $f16, %lo(D_800E8BA4)($at)
/* 0B0D0C 800B010C 46009121 */  cvt.d.s $f4, $f18
/* 0B0D10 800B0110 46302182 */  mul.d $f6, $f4, $f16
/* 0B0D14 800B0114 C6080020 */  lwc1  $f8, 0x20($s0)
/* 0B0D18 800B0118 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B0D1C 800B011C 460042A1 */  cvt.d.s $f10, $f8
/* 0B0D20 800B0120 46265480 */  add.d $f18, $f10, $f6
/* 0B0D24 800B0124 46209120 */  cvt.s.d $f4, $f18
/* 0B0D28 800B0128 E6040020 */  swc1  $f4, 0x20($s0)
/* 0B0D2C 800B012C 30690400 */  andi  $t1, $v1, 0x400
.L800B0130:
/* 0B0D30 800B0130 11200011 */  beqz  $t1, .L800B0178
/* 0B0D34 800B0134 00000000 */   nop   
/* 0B0D38 800B0138 8E25007C */  lw    $a1, 0x7c($s1)
/* 0B0D3C 800B013C 0C01BE53 */  jal   func_8006F94C
/* 0B0D40 800B0140 00052023 */   negu  $a0, $a1
/* 0B0D44 800B0144 44828000 */  mtc1  $v0, $f16
/* 0B0D48 800B0148 3C01800F */  lui   $at, %hi(D_800E8BAC) # $at, 0x800f
/* 0B0D4C 800B014C 46808220 */  cvt.s.w $f8, $f16
/* 0B0D50 800B0150 C4278BA8 */  lwc1  $f7, %lo(D_800E8BA8)($at)
/* 0B0D54 800B0154 C4268BAC */  lwc1  $f6, %lo(D_800E8BAC)($at)
/* 0B0D58 800B0158 460042A1 */  cvt.d.s $f10, $f8
/* 0B0D5C 800B015C 46265482 */  mul.d $f18, $f10, $f6
/* 0B0D60 800B0160 C6040024 */  lwc1  $f4, 0x24($s0)
/* 0B0D64 800B0164 00000000 */  nop   
/* 0B0D68 800B0168 46002421 */  cvt.d.s $f16, $f4
/* 0B0D6C 800B016C 46328200 */  add.d $f8, $f16, $f18
/* 0B0D70 800B0170 462042A0 */  cvt.s.d $f10, $f8
/* 0B0D74 800B0174 E60A0024 */  swc1  $f10, 0x24($s0)
.L800B0178:
/* 0B0D78 800B0178 8E220000 */  lw    $v0, ($s1)
/* 0B0D7C 800B017C 24010010 */  li    $at, 16
/* 0B0D80 800B0180 30430070 */  andi  $v1, $v0, 0x70
/* 0B0D84 800B0184 10610005 */  beq   $v1, $at, .L800B019C
/* 0B0D88 800B0188 24010040 */   li    $at, 64
/* 0B0D8C 800B018C 1061001A */  beq   $v1, $at, .L800B01F8
/* 0B0D90 800B0190 8FAD0044 */   lw    $t5, 0x44($sp)
/* 0B0D94 800B0194 1000002D */  b     .L800B024C
/* 0B0D98 800B0198 30580004 */   andi  $t8, $v0, 4
.L800B019C:
/* 0B0D9C 800B019C 8FAA0044 */  lw    $t2, 0x44($sp)
/* 0B0DA0 800B01A0 C606001C */  lwc1  $f6, 0x1c($s0)
/* 0B0DA4 800B01A4 C544001C */  lwc1  $f4, 0x1c($t2)
/* 0B0DA8 800B01A8 C6120020 */  lwc1  $f18, 0x20($s0)
/* 0B0DAC 800B01AC 46043400 */  add.s $f16, $f6, $f4
/* 0B0DB0 800B01B0 C6060024 */  lwc1  $f6, 0x24($s0)
/* 0B0DB4 800B01B4 E610001C */  swc1  $f16, 0x1c($s0)
/* 0B0DB8 800B01B8 8FAB0044 */  lw    $t3, 0x44($sp)
/* 0B0DBC 800B01BC 00000000 */  nop   
/* 0B0DC0 800B01C0 C5680020 */  lwc1  $f8, 0x20($t3)
/* 0B0DC4 800B01C4 00000000 */  nop   
/* 0B0DC8 800B01C8 46089280 */  add.s $f10, $f18, $f8
/* 0B0DCC 800B01CC E60A0020 */  swc1  $f10, 0x20($s0)
/* 0B0DD0 800B01D0 8FAC0044 */  lw    $t4, 0x44($sp)
/* 0B0DD4 800B01D4 00000000 */  nop   
/* 0B0DD8 800B01D8 C5840024 */  lwc1  $f4, 0x24($t4)
/* 0B0DDC 800B01DC 00000000 */  nop   
/* 0B0DE0 800B01E0 46043400 */  add.s $f16, $f6, $f4
/* 0B0DE4 800B01E4 E6100024 */  swc1  $f16, 0x24($s0)
/* 0B0DE8 800B01E8 8E220000 */  lw    $v0, ($s1)
/* 0B0DEC 800B01EC 10000017 */  b     .L800B024C
/* 0B0DF0 800B01F0 30580004 */   andi  $t8, $v0, 4
/* 0B0DF4 800B01F4 8FAD0044 */  lw    $t5, 0x44($sp)
.L800B01F8:
/* 0B0DF8 800B01F8 C612001C */  lwc1  $f18, 0x1c($s0)
/* 0B0DFC 800B01FC C5A8001C */  lwc1  $f8, 0x1c($t5)
/* 0B0E00 800B0200 C6060020 */  lwc1  $f6, 0x20($s0)
/* 0B0E04 800B0204 46089282 */  mul.s $f10, $f18, $f8
/* 0B0E08 800B0208 C6120024 */  lwc1  $f18, 0x24($s0)
/* 0B0E0C 800B020C E60A001C */  swc1  $f10, 0x1c($s0)
/* 0B0E10 800B0210 8FAE0044 */  lw    $t6, 0x44($sp)
/* 0B0E14 800B0214 00000000 */  nop   
/* 0B0E18 800B0218 C5C40020 */  lwc1  $f4, 0x20($t6)
/* 0B0E1C 800B021C 00000000 */  nop   
/* 0B0E20 800B0220 46043402 */  mul.s $f16, $f6, $f4
/* 0B0E24 800B0224 E6100020 */  swc1  $f16, 0x20($s0)
/* 0B0E28 800B0228 8FAF0044 */  lw    $t7, 0x44($sp)
/* 0B0E2C 800B022C 00000000 */  nop   
/* 0B0E30 800B0230 C5E80024 */  lwc1  $f8, 0x24($t7)
/* 0B0E34 800B0234 00000000 */  nop   
/* 0B0E38 800B0238 46089282 */  mul.s $f10, $f18, $f8
/* 0B0E3C 800B023C E60A0024 */  swc1  $f10, 0x24($s0)
/* 0B0E40 800B0240 8E220000 */  lw    $v0, ($s1)
/* 0B0E44 800B0244 00000000 */  nop   
/* 0B0E48 800B0248 30580004 */  andi  $t8, $v0, 4
.L800B024C:
/* 0B0E4C 800B024C 13000058 */  beqz  $t8, .L800B03B0
/* 0B0E50 800B0250 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0B0E54 800B0254 44800000 */  mtc1  $zero, $f0
/* 0B0E58 800B0258 00000000 */  nop   
/* 0B0E5C 800B025C E7A00030 */  swc1  $f0, 0x30($sp)
/* 0B0E60 800B0260 E7A00034 */  swc1  $f0, 0x34($sp)
/* 0B0E64 800B0264 C626003C */  lwc1  $f6, 0x3c($s1)
/* 0B0E68 800B0268 00000000 */  nop   
/* 0B0E6C 800B026C 46003107 */  neg.s $f4, $f6
/* 0B0E70 800B0270 E7A40038 */  swc1  $f4, 0x38($sp)
/* 0B0E74 800B0274 8E23005C */  lw    $v1, 0x5c($s1)
/* 0B0E78 800B0278 00000000 */  nop   
/* 0B0E7C 800B027C 30790010 */  andi  $t9, $v1, 0x10
/* 0B0E80 800B0280 13200013 */  beqz  $t9, .L800B02D0
/* 0B0E84 800B0284 30680060 */   andi  $t0, $v1, 0x60
/* 0B0E88 800B0288 8E250070 */  lw    $a1, 0x70($s1)
/* 0B0E8C 800B028C AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B0E90 800B0290 0C01BE53 */  jal   func_8006F94C
/* 0B0E94 800B0294 00052023 */   negu  $a0, $a1
/* 0B0E98 800B0298 44828000 */  mtc1  $v0, $f16
/* 0B0E9C 800B029C 3C01800F */  lui   $at, %hi(D_800E8BB4) # $at, 0x800f
/* 0B0EA0 800B02A0 468084A0 */  cvt.s.w $f18, $f16
/* 0B0EA4 800B02A4 C42B8BB0 */  lwc1  $f11, %lo(D_800E8BB0)($at)
/* 0B0EA8 800B02A8 C42A8BB4 */  lwc1  $f10, %lo(D_800E8BB4)($at)
/* 0B0EAC 800B02AC 46009221 */  cvt.d.s $f8, $f18
/* 0B0EB0 800B02B0 462A4182 */  mul.d $f6, $f8, $f10
/* 0B0EB4 800B02B4 C7A40038 */  lwc1  $f4, 0x38($sp)
/* 0B0EB8 800B02B8 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B0EBC 800B02BC 46002421 */  cvt.d.s $f16, $f4
/* 0B0EC0 800B02C0 46268480 */  add.d $f18, $f16, $f6
/* 0B0EC4 800B02C4 46209220 */  cvt.s.d $f8, $f18
/* 0B0EC8 800B02C8 E7A80038 */  swc1  $f8, 0x38($sp)
/* 0B0ECC 800B02CC 30680060 */  andi  $t0, $v1, 0x60
.L800B02D0:
/* 0B0ED0 800B02D0 11000021 */  beqz  $t0, .L800B0358
/* 0B0ED4 800B02D4 8FA40048 */   lw    $a0, 0x48($sp)
/* 0B0ED8 800B02D8 8FA90048 */  lw    $t1, 0x48($sp)
/* 0B0EDC 800B02DC 306B0020 */  andi  $t3, $v1, 0x20
/* 0B0EE0 800B02E0 852A0012 */  lh    $t2, 0x12($t1)
/* 0B0EE4 800B02E4 11600009 */  beqz  $t3, .L800B030C
/* 0B0EE8 800B02E8 A7AA0028 */   sh    $t2, 0x28($sp)
/* 0B0EEC 800B02EC 8625006A */  lh    $a1, 0x6a($s1)
/* 0B0EF0 800B02F0 AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B0EF4 800B02F4 0C01BE53 */  jal   func_8006F94C
/* 0B0EF8 800B02F8 00052023 */   negu  $a0, $a1
/* 0B0EFC 800B02FC 87AC0028 */  lh    $t4, 0x28($sp)
/* 0B0F00 800B0300 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B0F04 800B0304 01826821 */  addu  $t5, $t4, $v0
/* 0B0F08 800B0308 A7AD0028 */  sh    $t5, 0x28($sp)
.L800B030C:
/* 0B0F0C 800B030C 8FAE0048 */  lw    $t6, 0x48($sp)
/* 0B0F10 800B0310 30780040 */  andi  $t8, $v1, 0x40
/* 0B0F14 800B0314 85CF0014 */  lh    $t7, 0x14($t6)
/* 0B0F18 800B0318 13000008 */  beqz  $t8, .L800B033C
/* 0B0F1C 800B031C A7AF002A */   sh    $t7, 0x2a($sp)
/* 0B0F20 800B0320 8625006C */  lh    $a1, 0x6c($s1)
/* 0B0F24 800B0324 0C01BE53 */  jal   func_8006F94C
/* 0B0F28 800B0328 00052023 */   negu  $a0, $a1
/* 0B0F2C 800B032C 87B9002A */  lh    $t9, 0x2a($sp)
/* 0B0F30 800B0330 00000000 */  nop   
/* 0B0F34 800B0334 03224021 */  addu  $t0, $t9, $v0
/* 0B0F38 800B0338 A7A8002A */  sh    $t0, 0x2a($sp)
.L800B033C:
/* 0B0F3C 800B033C 27B10030 */  addiu $s1, $sp, 0x30
/* 0B0F40 800B0340 02202825 */  move  $a1, $s1
/* 0B0F44 800B0344 0C01C124 */  jal   func_80070490
/* 0B0F48 800B0348 27A40028 */   addiu $a0, $sp, 0x28
/* 0B0F4C 800B034C 10000007 */  b     .L800B036C
/* 0B0F50 800B0350 8E04003C */   lw    $a0, 0x3c($s0)
/* 0B0F54 800B0354 8FA40048 */  lw    $a0, 0x48($sp)
.L800B0358:
/* 0B0F58 800B0358 27B10030 */  addiu $s1, $sp, 0x30
/* 0B0F5C 800B035C 02202825 */  move  $a1, $s1
/* 0B0F60 800B0360 0C01C124 */  jal   func_80070490
/* 0B0F64 800B0364 24840012 */   addiu $a0, $a0, 0x12
/* 0B0F68 800B0368 8E04003C */  lw    $a0, 0x3c($s0)
.L800B036C:
/* 0B0F6C 800B036C 0C01C0C8 */  jal   func_80070320
/* 0B0F70 800B0370 02202825 */   move  $a1, $s1
/* 0B0F74 800B0374 C60A001C */  lwc1  $f10, 0x1c($s0)
/* 0B0F78 800B0378 C7A40030 */  lwc1  $f4, 0x30($sp)
/* 0B0F7C 800B037C C6060020 */  lwc1  $f6, 0x20($s0)
/* 0B0F80 800B0380 46045400 */  add.s $f16, $f10, $f4
/* 0B0F84 800B0384 C60A0024 */  lwc1  $f10, 0x24($s0)
/* 0B0F88 800B0388 E610001C */  swc1  $f16, 0x1c($s0)
/* 0B0F8C 800B038C C7B20034 */  lwc1  $f18, 0x34($sp)
/* 0B0F90 800B0390 00000000 */  nop   
/* 0B0F94 800B0394 46123200 */  add.s $f8, $f6, $f18
/* 0B0F98 800B0398 E6080020 */  swc1  $f8, 0x20($s0)
/* 0B0F9C 800B039C C7A40038 */  lwc1  $f4, 0x38($sp)
/* 0B0FA0 800B03A0 00000000 */  nop   
/* 0B0FA4 800B03A4 46045400 */  add.s $f16, $f10, $f4
/* 0B0FA8 800B03A8 E6100024 */  swc1  $f16, 0x24($s0)
/* 0B0FAC 800B03AC 8FBF001C */  lw    $ra, 0x1c($sp)
.L800B03B0:
/* 0B0FB0 800B03B0 8FB00014 */  lw    $s0, 0x14($sp)
/* 0B0FB4 800B03B4 8FB10018 */  lw    $s1, 0x18($sp)
/* 0B0FB8 800B03B8 03E00008 */  jr    $ra
/* 0B0FBC 800B03BC 27BD0040 */   addiu $sp, $sp, 0x40

glabel func_800B03C0
/* 0B0FC0 800B03C0 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 0B0FC4 800B03C4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B0FC8 800B03C8 AFB00018 */  sw    $s0, 0x18($sp)
/* 0B0FCC 800B03CC AFA50044 */  sw    $a1, 0x44($sp)
/* 0B0FD0 800B03D0 84CE0018 */  lh    $t6, 0x18($a2)
/* 0B0FD4 800B03D4 00808025 */  move  $s0, $a0
/* 0B0FD8 800B03D8 448E2000 */  mtc1  $t6, $f4
/* 0B0FDC 800B03DC 00000000 */  nop   
/* 0B0FE0 800B03E0 468021A0 */  cvt.s.w $f6, $f4
/* 0B0FE4 800B03E4 E486004C */  swc1  $f6, 0x4c($a0)
/* 0B0FE8 800B03E8 84CF001A */  lh    $t7, 0x1a($a2)
/* 0B0FEC 800B03EC 00000000 */  nop   
/* 0B0FF0 800B03F0 448F4000 */  mtc1  $t7, $f8
/* 0B0FF4 800B03F4 00000000 */  nop   
/* 0B0FF8 800B03F8 468042A0 */  cvt.s.w $f10, $f8
/* 0B0FFC 800B03FC E48A0050 */  swc1  $f10, 0x50($a0)
/* 0B1000 800B0400 84D8001C */  lh    $t8, 0x1c($a2)
/* 0B1004 800B0404 00000000 */  nop   
/* 0B1008 800B0408 44988000 */  mtc1  $t8, $f16
/* 0B100C 800B040C 00000000 */  nop   
/* 0B1010 800B0410 468084A0 */  cvt.s.w $f18, $f16
/* 0B1014 800B0414 E4920054 */  swc1  $f18, 0x54($a0)
/* 0B1018 800B0418 C4E40058 */  lwc1  $f4, 0x58($a3)
/* 0B101C 800B041C 00000000 */  nop   
/* 0B1020 800B0420 E4840058 */  swc1  $f4, 0x58($a0)
/* 0B1024 800B0424 8CF9005C */  lw    $t9, 0x5c($a3)
/* 0B1028 800B0428 00000000 */  nop   
/* 0B102C 800B042C 00194300 */  sll   $t0, $t9, 0xc
/* 0B1030 800B0430 05010014 */  bgez  $t0, .L800B0484
/* 0B1034 800B0434 00000000 */   nop   
/* 0B1038 800B0438 8CE50094 */  lw    $a1, 0x94($a3)
/* 0B103C 800B043C AFA7004C */  sw    $a3, 0x4c($sp)
/* 0B1040 800B0440 AFA60048 */  sw    $a2, 0x48($sp)
/* 0B1044 800B0444 0C01BE53 */  jal   func_8006F94C
/* 0B1048 800B0448 00052023 */   negu  $a0, $a1
/* 0B104C 800B044C 44823000 */  mtc1  $v0, $f6
/* 0B1050 800B0450 3C01800F */  lui   $at, %hi(D_800E8BBC) # $at, 0x800f
/* 0B1054 800B0454 46803220 */  cvt.s.w $f8, $f6
/* 0B1058 800B0458 C4318BB8 */  lwc1  $f17, %lo(D_800E8BB8)($at)
/* 0B105C 800B045C C4308BBC */  lwc1  $f16, %lo(D_800E8BBC)($at)
/* 0B1060 800B0460 460042A1 */  cvt.d.s $f10, $f8
/* 0B1064 800B0464 46305482 */  mul.d $f18, $f10, $f16
/* 0B1068 800B0468 C6040058 */  lwc1  $f4, 0x58($s0)
/* 0B106C 800B046C 8FA60048 */  lw    $a2, 0x48($sp)
/* 0B1070 800B0470 460021A1 */  cvt.d.s $f6, $f4
/* 0B1074 800B0474 8FA7004C */  lw    $a3, 0x4c($sp)
/* 0B1078 800B0478 46323200 */  add.d $f8, $f6, $f18
/* 0B107C 800B047C 462042A0 */  cvt.s.d $f10, $f8
/* 0B1080 800B0480 E60A0058 */  swc1  $f10, 0x58($s0)
.L800B0484:
/* 0B1084 800B0484 8CE90000 */  lw    $t1, ($a3)
/* 0B1088 800B0488 00000000 */  nop   
/* 0B108C 800B048C 312A0001 */  andi  $t2, $t1, 1
/* 0B1090 800B0490 11400056 */  beqz  $t2, .L800B05EC
/* 0B1094 800B0494 00000000 */   nop   
/* 0B1098 800B0498 44800000 */  mtc1  $zero, $f0
/* 0B109C 800B049C 00000000 */  nop   
/* 0B10A0 800B04A0 E7A00030 */  swc1  $f0, 0x30($sp)
/* 0B10A4 800B04A4 E7A00034 */  swc1  $f0, 0x34($sp)
/* 0B10A8 800B04A8 C4F00010 */  lwc1  $f16, 0x10($a3)
/* 0B10AC 800B04AC 00000000 */  nop   
/* 0B10B0 800B04B0 46008107 */  neg.s $f4, $f16
/* 0B10B4 800B04B4 E7A40038 */  swc1  $f4, 0x38($sp)
/* 0B10B8 800B04B8 8CE3005C */  lw    $v1, 0x5c($a3)
/* 0B10BC 800B04BC 00000000 */  nop   
/* 0B10C0 800B04C0 306B0001 */  andi  $t3, $v1, 1
/* 0B10C4 800B04C4 11600017 */  beqz  $t3, .L800B0524
/* 0B10C8 800B04C8 306C0006 */   andi  $t4, $v1, 6
/* 0B10CC 800B04CC 8CE50060 */  lw    $a1, 0x60($a3)
/* 0B10D0 800B04D0 AFA7004C */  sw    $a3, 0x4c($sp)
/* 0B10D4 800B04D4 AFA60048 */  sw    $a2, 0x48($sp)
/* 0B10D8 800B04D8 AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B10DC 800B04DC 0C01BE53 */  jal   func_8006F94C
/* 0B10E0 800B04E0 00052023 */   negu  $a0, $a1
/* 0B10E4 800B04E4 44823000 */  mtc1  $v0, $f6
/* 0B10E8 800B04E8 3C01800F */  lui   $at, %hi(D_800E8BC4) # $at, 0x800f
/* 0B10EC 800B04EC 468034A0 */  cvt.s.w $f18, $f6
/* 0B10F0 800B04F0 C42B8BC0 */  lwc1  $f11, %lo(D_800E8BC0)($at)
/* 0B10F4 800B04F4 C42A8BC4 */  lwc1  $f10, %lo(D_800E8BC4)($at)
/* 0B10F8 800B04F8 46009221 */  cvt.d.s $f8, $f18
/* 0B10FC 800B04FC 462A4402 */  mul.d $f16, $f8, $f10
/* 0B1100 800B0500 C7A40038 */  lwc1  $f4, 0x38($sp)
/* 0B1104 800B0504 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B1108 800B0508 460021A1 */  cvt.d.s $f6, $f4
/* 0B110C 800B050C 8FA60048 */  lw    $a2, 0x48($sp)
/* 0B1110 800B0510 46303480 */  add.d $f18, $f6, $f16
/* 0B1114 800B0514 8FA7004C */  lw    $a3, 0x4c($sp)
/* 0B1118 800B0518 46209220 */  cvt.s.d $f8, $f18
/* 0B111C 800B051C E7A80038 */  swc1  $f8, 0x38($sp)
/* 0B1120 800B0520 306C0006 */  andi  $t4, $v1, 6
.L800B0524:
/* 0B1124 800B0524 11800021 */  beqz  $t4, .L800B05AC
/* 0B1128 800B0528 24C4000C */   addiu $a0, $a2, 0xc
/* 0B112C 800B052C 84CD000C */  lh    $t5, 0xc($a2)
/* 0B1130 800B0530 306E0002 */  andi  $t6, $v1, 2
/* 0B1134 800B0534 11C0000D */  beqz  $t6, .L800B056C
/* 0B1138 800B0538 A7AD0028 */   sh    $t5, 0x28($sp)
/* 0B113C 800B053C 84E50064 */  lh    $a1, 0x64($a3)
/* 0B1140 800B0540 AFA7004C */  sw    $a3, 0x4c($sp)
/* 0B1144 800B0544 AFA60048 */  sw    $a2, 0x48($sp)
/* 0B1148 800B0548 AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B114C 800B054C 0C01BE53 */  jal   func_8006F94C
/* 0B1150 800B0550 00052023 */   negu  $a0, $a1
/* 0B1154 800B0554 87AF0028 */  lh    $t7, 0x28($sp)
/* 0B1158 800B0558 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B115C 800B055C 01E2C021 */  addu  $t8, $t7, $v0
/* 0B1160 800B0560 8FA60048 */  lw    $a2, 0x48($sp)
/* 0B1164 800B0564 8FA7004C */  lw    $a3, 0x4c($sp)
/* 0B1168 800B0568 A7B80028 */  sh    $t8, 0x28($sp)
.L800B056C:
/* 0B116C 800B056C 84D9000E */  lh    $t9, 0xe($a2)
/* 0B1170 800B0570 30680004 */  andi  $t0, $v1, 4
/* 0B1174 800B0574 11000008 */  beqz  $t0, .L800B0598
/* 0B1178 800B0578 A7B9002A */   sh    $t9, 0x2a($sp)
/* 0B117C 800B057C 84E50066 */  lh    $a1, 0x66($a3)
/* 0B1180 800B0580 0C01BE53 */  jal   func_8006F94C
/* 0B1184 800B0584 00052023 */   negu  $a0, $a1
/* 0B1188 800B0588 87A9002A */  lh    $t1, 0x2a($sp)
/* 0B118C 800B058C 00000000 */  nop   
/* 0B1190 800B0590 01225021 */  addu  $t2, $t1, $v0
/* 0B1194 800B0594 A7AA002A */  sh    $t2, 0x2a($sp)
.L800B0598:
/* 0B1198 800B0598 27A40028 */  addiu $a0, $sp, 0x28
/* 0B119C 800B059C 0C01C124 */  jal   func_80070490
/* 0B11A0 800B05A0 27A50030 */   addiu $a1, $sp, 0x30
/* 0B11A4 800B05A4 10000004 */  b     .L800B05B8
/* 0B11A8 800B05A8 C60A004C */   lwc1  $f10, 0x4c($s0)
.L800B05AC:
/* 0B11AC 800B05AC 0C01C0C8 */  jal   func_80070320
/* 0B11B0 800B05B0 27A50030 */   addiu $a1, $sp, 0x30
/* 0B11B4 800B05B4 C60A004C */  lwc1  $f10, 0x4c($s0)
.L800B05B8:
/* 0B11B8 800B05B8 C7A40030 */  lwc1  $f4, 0x30($sp)
/* 0B11BC 800B05BC C6100050 */  lwc1  $f16, 0x50($s0)
/* 0B11C0 800B05C0 46045180 */  add.s $f6, $f10, $f4
/* 0B11C4 800B05C4 C60A0054 */  lwc1  $f10, 0x54($s0)
/* 0B11C8 800B05C8 E606004C */  swc1  $f6, 0x4c($s0)
/* 0B11CC 800B05CC C7B20034 */  lwc1  $f18, 0x34($sp)
/* 0B11D0 800B05D0 00000000 */  nop   
/* 0B11D4 800B05D4 46128200 */  add.s $f8, $f16, $f18
/* 0B11D8 800B05D8 E6080050 */  swc1  $f8, 0x50($s0)
/* 0B11DC 800B05DC C7A40038 */  lwc1  $f4, 0x38($sp)
/* 0B11E0 800B05E0 00000000 */  nop   
/* 0B11E4 800B05E4 46045180 */  add.s $f6, $f10, $f4
/* 0B11E8 800B05E8 E6060054 */  swc1  $f6, 0x54($s0)
.L800B05EC:
/* 0B11EC 800B05EC 92020039 */  lbu   $v0, 0x39($s0)
/* 0B11F0 800B05F0 24010004 */  li    $at, 4
/* 0B11F4 800B05F4 10410006 */  beq   $v0, $at, .L800B0610
/* 0B11F8 800B05F8 00000000 */   nop   
/* 0B11FC 800B05FC 8FA40044 */  lw    $a0, 0x44($sp)
/* 0B1200 800B0600 0C01C0C8 */  jal   func_80070320
/* 0B1204 800B0604 2605004C */   addiu $a1, $s0, 0x4c
/* 0B1208 800B0608 92020039 */  lbu   $v0, 0x39($s0)
/* 0B120C 800B060C 00000000 */  nop   
.L800B0610:
/* 0B1210 800B0610 C610004C */  lwc1  $f16, 0x4c($s0)
/* 0B1214 800B0614 C6120050 */  lwc1  $f18, 0x50($s0)
/* 0B1218 800B0618 C6080054 */  lwc1  $f8, 0x54($s0)
/* 0B121C 800B061C 24010004 */  li    $at, 4
/* 0B1220 800B0620 E610000C */  swc1  $f16, 0xc($s0)
/* 0B1224 800B0624 E6120010 */  swc1  $f18, 0x10($s0)
/* 0B1228 800B0628 14410004 */  bne   $v0, $at, .L800B063C
/* 0B122C 800B062C E6080014 */   swc1  $f8, 0x14($s0)
/* 0B1230 800B0630 8FA40044 */  lw    $a0, 0x44($sp)
/* 0B1234 800B0634 0C01C0C8 */  jal   func_80070320
/* 0B1238 800B0638 2605000C */   addiu $a1, $s0, 0xc
.L800B063C:
/* 0B123C 800B063C 8FAB0044 */  lw    $t3, 0x44($sp)
/* 0B1240 800B0640 C60A000C */  lwc1  $f10, 0xc($s0)
/* 0B1244 800B0644 C564000C */  lwc1  $f4, 0xc($t3)
/* 0B1248 800B0648 C6100010 */  lwc1  $f16, 0x10($s0)
/* 0B124C 800B064C 46045180 */  add.s $f6, $f10, $f4
/* 0B1250 800B0650 C60A0014 */  lwc1  $f10, 0x14($s0)
/* 0B1254 800B0654 E606000C */  swc1  $f6, 0xc($s0)
/* 0B1258 800B0658 8FAC0044 */  lw    $t4, 0x44($sp)
/* 0B125C 800B065C 00000000 */  nop   
/* 0B1260 800B0660 C5920010 */  lwc1  $f18, 0x10($t4)
/* 0B1264 800B0664 00000000 */  nop   
/* 0B1268 800B0668 46128200 */  add.s $f8, $f16, $f18
/* 0B126C 800B066C E6080010 */  swc1  $f8, 0x10($s0)
/* 0B1270 800B0670 8FAD0044 */  lw    $t5, 0x44($sp)
/* 0B1274 800B0674 00000000 */  nop   
/* 0B1278 800B0678 C5A40014 */  lwc1  $f4, 0x14($t5)
/* 0B127C 800B067C 00000000 */  nop   
/* 0B1280 800B0680 46045180 */  add.s $f6, $f10, $f4
/* 0B1284 800B0684 E6060014 */  swc1  $f6, 0x14($s0)
/* 0B1288 800B0688 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B128C 800B068C 8FB00018 */  lw    $s0, 0x18($sp)
/* 0B1290 800B0690 03E00008 */  jr    $ra
/* 0B1294 800B0694 27BD0040 */   addiu $sp, $sp, 0x40

glabel func_800B0698
/* 0B1298 800B0698 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0B129C 800B069C AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B12A0 800B06A0 AFB00018 */  sw    $s0, 0x18($sp)
/* 0B12A4 800B06A4 AFA40030 */  sw    $a0, 0x30($sp)
/* 0B12A8 800B06A8 84AF0008 */  lh    $t7, 8($a1)
/* 0B12AC 800B06AC 3C0E800E */  lui   $t6, %hi(D_800E2CF0) # $t6, 0x800e
/* 0B12B0 800B06B0 8DCE2CF0 */  lw    $t6, %lo(D_800E2CF0)($t6)
/* 0B12B4 800B06B4 000FC080 */  sll   $t8, $t7, 2
/* 0B12B8 800B06B8 01D8C821 */  addu  $t9, $t6, $t8
/* 0B12BC 800B06BC 8F230000 */  lw    $v1, ($t9)
/* 0B12C0 800B06C0 24010004 */  li    $at, 4
/* 0B12C4 800B06C4 90680000 */  lbu   $t0, ($v1)
/* 0B12C8 800B06C8 00A03025 */  move  $a2, $a1
/* 0B12CC 800B06CC 11010003 */  beq   $t0, $at, .L800B06DC
/* 0B12D0 800B06D0 24040004 */   li    $a0, 4
/* 0B12D4 800B06D4 10000131 */  b     .L800B0B9C
/* 0B12D8 800B06D8 00001025 */   move  $v0, $zero
.L800B06DC:
/* 0B12DC 800B06DC 8CC70000 */  lw    $a3, ($a2)
/* 0B12E0 800B06E0 AFA60034 */  sw    $a2, 0x34($sp)
/* 0B12E4 800B06E4 AFA3002C */  sw    $v1, 0x2c($sp)
/* 0B12E8 800B06E8 0C02C72E */  jal   func_800B1CB8
/* 0B12EC 800B06EC AFA70020 */   sw    $a3, 0x20($sp)
/* 0B12F0 800B06F0 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0B12F4 800B06F4 8FA60034 */  lw    $a2, 0x34($sp)
/* 0B12F8 800B06F8 8FA70020 */  lw    $a3, 0x20($sp)
/* 0B12FC 800B06FC 14400003 */  bnez  $v0, .L800B070C
/* 0B1300 800B0700 00408025 */   move  $s0, $v0
/* 0B1304 800B0704 10000125 */  b     .L800B0B9C
/* 0B1308 800B0708 02001025 */   move  $v0, $s0
.L800B070C:
/* 0B130C 800B070C 8FA90030 */  lw    $t1, 0x30($sp)
/* 0B1310 800B0710 240B8000 */  li    $t3, -32768
/* 0B1314 800B0714 852A002E */  lh    $t2, 0x2e($t1)
/* 0B1318 800B0718 A44B0006 */  sh    $t3, 6($v0)
/* 0B131C 800B071C A44A002E */  sh    $t2, 0x2e($v0)
/* 0B1320 800B0720 906C0001 */  lbu   $t4, 1($v1)
/* 0B1324 800B0724 00000000 */  nop   
/* 0B1328 800B0728 A04C0039 */  sb    $t4, 0x39($v0)
/* 0B132C 800B072C 946D0002 */  lhu   $t5, 2($v1)
/* 0B1330 800B0730 00000000 */  nop   
/* 0B1334 800B0734 AC4D0040 */  sw    $t5, 0x40($v0)
/* 0B1338 800B0738 8FAF0030 */  lw    $t7, 0x30($sp)
/* 0B133C 800B073C AC460070 */  sw    $a2, 0x70($v0)
/* 0B1340 800B0740 AC4F003C */  sw    $t7, 0x3c($v0)
/* 0B1344 800B0744 C4640010 */  lwc1  $f4, 0x10($v1)
/* 0B1348 800B0748 C4E60050 */  lwc1  $f6, 0x50($a3)
/* 0B134C 800B074C 31AB0800 */  andi  $t3, $t5, 0x800
/* 0B1350 800B0750 46062202 */  mul.s $f8, $f4, $f6
/* 0B1354 800B0754 44802000 */  mtc1  $zero, $f4
/* 0B1358 800B0758 E4480008 */  swc1  $f8, 8($v0)
/* 0B135C 800B075C C4F00054 */  lwc1  $f16, 0x54($a3)
/* 0B1360 800B0760 C46A0010 */  lwc1  $f10, 0x10($v1)
/* 0B1364 800B0764 00000000 */  nop   
/* 0B1368 800B0768 46105482 */  mul.s $f18, $f10, $f16
/* 0B136C 800B076C E4520028 */  swc1  $f18, 0x28($v0)
/* 0B1370 800B0770 846E0008 */  lh    $t6, 8($v1)
/* 0B1374 800B0774 A0400038 */  sb    $zero, 0x38($v0)
/* 0B1378 800B0778 E4440034 */  swc1  $f4, 0x34($v0)
/* 0B137C 800B077C A44E003A */  sh    $t6, 0x3a($v0)
/* 0B1380 800B0780 90780014 */  lbu   $t8, 0x14($v1)
/* 0B1384 800B0784 00000000 */  nop   
/* 0B1388 800B0788 A058006C */  sb    $t8, 0x6c($v0)
/* 0B138C 800B078C 90790015 */  lbu   $t9, 0x15($v1)
/* 0B1390 800B0790 00000000 */  nop   
/* 0B1394 800B0794 A059006D */  sb    $t9, 0x6d($v0)
/* 0B1398 800B0798 90680016 */  lbu   $t0, 0x16($v1)
/* 0B139C 800B079C 00000000 */  nop   
/* 0B13A0 800B07A0 A048006E */  sb    $t0, 0x6e($v0)
/* 0B13A4 800B07A4 90690017 */  lbu   $t1, 0x17($v1)
/* 0B13A8 800B07A8 11600016 */  beqz  $t3, .L800B0804
/* 0B13AC 800B07AC A049006F */   sb    $t1, 0x6f($v0)
/* 0B13B0 800B07B0 8FAC0030 */  lw    $t4, 0x30($sp)
/* 0B13B4 800B07B4 3C01437F */  li    $at, 0x437F0000 # 255.000000
/* 0B13B8 800B07B8 8D840054 */  lw    $a0, 0x54($t4)
/* 0B13BC 800B07BC 00000000 */  nop   
/* 0B13C0 800B07C0 10800010 */  beqz  $a0, .L800B0804
/* 0B13C4 800B07C4 00000000 */   nop   
/* 0B13C8 800B07C8 C4860000 */  lwc1  $f6, ($a0)
/* 0B13CC 800B07CC 44814000 */  mtc1  $at, $f8
/* 0B13D0 800B07D0 00000000 */  nop   
/* 0B13D4 800B07D4 46083282 */  mul.s $f10, $f6, $f8
/* 0B13D8 800B07D8 444DF800 */  cfc1  $t5, $31
/* 0B13DC 800B07DC 00000000 */  nop   
/* 0B13E0 800B07E0 35A10003 */  ori   $at, $t5, 3
/* 0B13E4 800B07E4 38210002 */  xori  $at, $at, 2
/* 0B13E8 800B07E8 44C1F800 */  ctc1  $at, $31
/* 0B13EC 800B07EC 00000000 */  nop   
/* 0B13F0 800B07F0 46005424 */  cvt.w.s $f16, $f10
/* 0B13F4 800B07F4 440F8000 */  mfc1  $t7, $f16
/* 0B13F8 800B07F8 44CDF800 */  ctc1  $t5, $31
/* 0B13FC 800B07FC 10000003 */  b     .L800B080C
/* 0B1400 800B0800 A44F004A */   sh    $t7, 0x4a($v0)
.L800B0804:
/* 0B1404 800B0804 240E00FF */  li    $t6, 255
/* 0B1408 800B0808 A44E004A */  sh    $t6, 0x4a($v0)
.L800B080C:
/* 0B140C 800B080C 8478000E */  lh    $t8, 0xe($v1)
/* 0B1410 800B0810 00000000 */  nop   
/* 0B1414 800B0814 A4580060 */  sh    $t8, 0x60($v0)
/* 0B1418 800B0818 84D90004 */  lh    $t9, 4($a2)
/* 0B141C 800B081C 00000000 */  nop   
/* 0B1420 800B0820 33280100 */  andi  $t0, $t9, 0x100
/* 0B1424 800B0824 11000004 */  beqz  $t0, .L800B0838
/* 0B1428 800B0828 00000000 */   nop   
/* 0B142C 800B082C 84C9000A */  lh    $t1, 0xa($a2)
/* 0B1430 800B0830 10000005 */  b     .L800B0848
/* 0B1434 800B0834 A449005C */   sh    $t1, 0x5c($v0)
.L800B0838:
/* 0B1438 800B0838 906A000C */  lbu   $t2, 0xc($v1)
/* 0B143C 800B083C 00000000 */  nop   
/* 0B1440 800B0840 000A5A00 */  sll   $t3, $t2, 8
/* 0B1444 800B0844 A44B005C */  sh    $t3, 0x5c($v0)
.L800B0848:
/* 0B1448 800B0848 906C000C */  lbu   $t4, 0xc($v1)
/* 0B144C 800B084C 00000000 */  nop   
/* 0B1450 800B0850 298100FF */  slti  $at, $t4, 0xff
/* 0B1454 800B0854 1020000F */  beqz  $at, .L800B0894
/* 0B1458 800B0858 00000000 */   nop   
/* 0B145C 800B085C 8C4D0040 */  lw    $t5, 0x40($v0)
/* 0B1460 800B0860 00000000 */  nop   
/* 0B1464 800B0864 31AF1000 */  andi  $t7, $t5, 0x1000
/* 0B1468 800B0868 11E00006 */  beqz  $t7, .L800B0884
/* 0B146C 800B086C 00000000 */   nop   
/* 0B1470 800B0870 844E0006 */  lh    $t6, 6($v0)
/* 0B1474 800B0874 00000000 */  nop   
/* 0B1478 800B0878 35D80100 */  ori   $t8, $t6, 0x100
/* 0B147C 800B087C 10000005 */  b     .L800B0894
/* 0B1480 800B0880 A4580006 */   sh    $t8, 6($v0)
.L800B0884:
/* 0B1484 800B0884 84590006 */  lh    $t9, 6($v0)
/* 0B1488 800B0888 00000000 */  nop   
/* 0B148C 800B088C 37280080 */  ori   $t0, $t9, 0x80
/* 0B1490 800B0890 A4480006 */  sh    $t0, 6($v0)
.L800B0894:
/* 0B1494 800B0894 84450060 */  lh    $a1, 0x60($v0)
/* 0B1498 800B0898 8444003A */  lh    $a0, 0x3a($v0)
/* 0B149C 800B089C 00000000 */  nop   
/* 0B14A0 800B08A0 00A4082A */  slt   $at, $a1, $a0
/* 0B14A4 800B08A4 10200014 */  beqz  $at, .L800B08F8
/* 0B14A8 800B08A8 00857823 */   subu  $t7, $a0, $a1
/* 0B14AC 800B08AC 9069000D */  lbu   $t1, 0xd($v1)
/* 0B14B0 800B08B0 844B005C */  lh    $t3, 0x5c($v0)
/* 0B14B4 800B08B4 00095200 */  sll   $t2, $t1, 8
/* 0B14B8 800B08B8 316CFFFF */  andi  $t4, $t3, 0xffff
/* 0B14BC 800B08BC 014C6823 */  subu  $t5, $t2, $t4
/* 0B14C0 800B08C0 01AF001A */  div   $zero, $t5, $t7
/* 0B14C4 800B08C4 15E00002 */  bnez  $t7, .L800B08D0
/* 0B14C8 800B08C8 00000000 */   nop   
/* 0B14CC 800B08CC 0007000D */  break 7
.L800B08D0:
/* 0B14D0 800B08D0 2401FFFF */  li    $at, -1
/* 0B14D4 800B08D4 15E10004 */  bne   $t7, $at, .L800B08E8
/* 0B14D8 800B08D8 3C018000 */   lui   $at, 0x8000
/* 0B14DC 800B08DC 15A10002 */  bne   $t5, $at, .L800B08E8
/* 0B14E0 800B08E0 00000000 */   nop   
/* 0B14E4 800B08E4 0006000D */  break 6
.L800B08E8:
/* 0B14E8 800B08E8 00007012 */  mflo  $t6
/* 0B14EC 800B08EC A44E005E */  sh    $t6, 0x5e($v0)
/* 0B14F0 800B08F0 10000003 */  b     .L800B0900
/* 0B14F4 800B08F4 8FA50030 */   lw    $a1, 0x30($sp)
.L800B08F8:
/* 0B14F8 800B08F8 A440005E */  sh    $zero, 0x5e($v0)
/* 0B14FC 800B08FC 8FA50030 */  lw    $a1, 0x30($sp)
.L800B0900:
/* 0B1500 800B0900 02002025 */  move  $a0, $s0
/* 0B1504 800B0904 AFA3002C */  sw    $v1, 0x2c($sp)
/* 0B1508 800B0908 AFA60034 */  sw    $a2, 0x34($sp)
/* 0B150C 800B090C 0C02C0F0 */  jal   func_800B03C0
/* 0B1510 800B0910 AFA70020 */   sw    $a3, 0x20($sp)
/* 0B1514 800B0914 8FA70020 */  lw    $a3, 0x20($sp)
/* 0B1518 800B0918 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0B151C 800B091C 8CF80000 */  lw    $t8, ($a3)
/* 0B1520 800B0920 8FA50030 */  lw    $a1, 0x30($sp)
/* 0B1524 800B0924 8FA60034 */  lw    $a2, 0x34($sp)
/* 0B1528 800B0928 33190080 */  andi  $t9, $t8, 0x80
/* 0B152C 800B092C 1320000A */  beqz  $t9, .L800B0958
/* 0B1530 800B0930 00000000 */   nop   
/* 0B1534 800B0934 84E80044 */  lh    $t0, 0x44($a3)
/* 0B1538 800B0938 00000000 */  nop   
/* 0B153C 800B093C A6080000 */  sh    $t0, ($s0)
/* 0B1540 800B0940 84E90046 */  lh    $t1, 0x46($a3)
/* 0B1544 800B0944 00000000 */  nop   
/* 0B1548 800B0948 A6090002 */  sh    $t1, 2($s0)
/* 0B154C 800B094C 84EB0048 */  lh    $t3, 0x48($a3)
/* 0B1550 800B0950 10000010 */  b     .L800B0994
/* 0B1554 800B0954 A60B0004 */   sh    $t3, 4($s0)
.L800B0958:
/* 0B1558 800B0958 84AA0000 */  lh    $t2, ($a1)
/* 0B155C 800B095C 84EC0044 */  lh    $t4, 0x44($a3)
/* 0B1560 800B0960 00000000 */  nop   
/* 0B1564 800B0964 014C6821 */  addu  $t5, $t2, $t4
/* 0B1568 800B0968 A60D0000 */  sh    $t5, ($s0)
/* 0B156C 800B096C 84EE0046 */  lh    $t6, 0x46($a3)
/* 0B1570 800B0970 84AF0002 */  lh    $t7, 2($a1)
/* 0B1574 800B0974 00000000 */  nop   
/* 0B1578 800B0978 01EEC021 */  addu  $t8, $t7, $t6
/* 0B157C 800B097C A6180002 */  sh    $t8, 2($s0)
/* 0B1580 800B0980 84E80048 */  lh    $t0, 0x48($a3)
/* 0B1584 800B0984 84B90004 */  lh    $t9, 4($a1)
/* 0B1588 800B0988 00000000 */  nop   
/* 0B158C 800B098C 03284821 */  addu  $t1, $t9, $t0
/* 0B1590 800B0990 A6090004 */  sh    $t1, 4($s0)
.L800B0994:
/* 0B1594 800B0994 84EB004A */  lh    $t3, 0x4a($a3)
/* 0B1598 800B0998 02002025 */  move  $a0, $s0
/* 0B159C 800B099C A60B0062 */  sh    $t3, 0x62($s0)
/* 0B15A0 800B09A0 84EA004C */  lh    $t2, 0x4c($a3)
/* 0B15A4 800B09A4 00000000 */  nop   
/* 0B15A8 800B09A8 A60A0064 */  sh    $t2, 0x64($s0)
/* 0B15AC 800B09AC 84EC004E */  lh    $t4, 0x4e($a3)
/* 0B15B0 800B09B0 00000000 */  nop   
/* 0B15B4 800B09B4 A60C0066 */  sh    $t4, 0x66($s0)
/* 0B15B8 800B09B8 AFA70020 */  sw    $a3, 0x20($sp)
/* 0B15BC 800B09BC AFA60034 */  sw    $a2, 0x34($sp)
/* 0B15C0 800B09C0 0C02C004 */  jal   func_800B0010
/* 0B15C4 800B09C4 AFA3002C */   sw    $v1, 0x2c($sp)
/* 0B15C8 800B09C8 8E0D0040 */  lw    $t5, 0x40($s0)
/* 0B15CC 800B09CC 3C01800E */  lui   $at, 0x800e
/* 0B15D0 800B09D0 000D7903 */  sra   $t7, $t5, 4
/* 0B15D4 800B09D4 31EE0007 */  andi  $t6, $t7, 7
/* 0B15D8 800B09D8 000EC080 */  sll   $t8, $t6, 2
/* 0B15DC 800B09DC 00380821 */  addu  $at, $at, $t8
/* 0B15E0 800B09E0 C4322E2C */  lwc1  $f18, 0x2e2c($at)
/* 0B15E4 800B09E4 92190039 */  lbu   $t9, 0x39($s0)
/* 0B15E8 800B09E8 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0B15EC 800B09EC 8FA60034 */  lw    $a2, 0x34($sp)
/* 0B15F0 800B09F0 8FA70020 */  lw    $a3, 0x20($sp)
/* 0B15F4 800B09F4 24010005 */  li    $at, 5
/* 0B15F8 800B09F8 17210011 */  bne   $t9, $at, .L800B0A40
/* 0B15FC 800B09FC E6120068 */   swc1  $f18, 0x68($s0)
/* 0B1600 800B0A00 C600001C */  lwc1  $f0, 0x1c($s0)
/* 0B1604 800B0A04 C6020020 */  lwc1  $f2, 0x20($s0)
/* 0B1608 800B0A08 46000102 */  mul.s $f4, $f0, $f0
/* 0B160C 800B0A0C C60E0024 */  lwc1  $f14, 0x24($s0)
/* 0B1610 800B0A10 AFA70020 */  sw    $a3, 0x20($sp)
/* 0B1614 800B0A14 AFA60034 */  sw    $a2, 0x34($sp)
/* 0B1618 800B0A18 46021182 */  mul.s $f6, $f2, $f2
/* 0B161C 800B0A1C AFA3002C */  sw    $v1, 0x2c($sp)
/* 0B1620 800B0A20 460E7282 */  mul.s $f10, $f14, $f14
/* 0B1624 800B0A24 46062200 */  add.s $f8, $f4, $f6
/* 0B1628 800B0A28 0C0326B4 */  jal   sqrtf
/* 0B162C 800B0A2C 460A4300 */   add.s $f12, $f8, $f10
/* 0B1630 800B0A30 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0B1634 800B0A34 8FA60034 */  lw    $a2, 0x34($sp)
/* 0B1638 800B0A38 8FA70020 */  lw    $a3, 0x20($sp)
/* 0B163C 800B0A3C E6000058 */  swc1  $f0, 0x58($s0)
.L800B0A40:
/* 0B1640 800B0A40 8CE20000 */  lw    $v0, ($a3)
/* 0B1644 800B0A44 2401FFFF */  li    $at, -1
/* 0B1648 800B0A48 30480002 */  andi  $t0, $v0, 2
/* 0B164C 800B0A4C 1100000D */  beqz  $t0, .L800B0A84
/* 0B1650 800B0A50 304E0008 */   andi  $t6, $v0, 8
/* 0B1654 800B0A54 84C90010 */  lh    $t1, 0x10($a2)
/* 0B1658 800B0A58 84EB001C */  lh    $t3, 0x1c($a3)
/* 0B165C 800B0A5C 84CC0012 */  lh    $t4, 0x12($a2)
/* 0B1660 800B0A60 012B5021 */  addu  $t2, $t1, $t3
/* 0B1664 800B0A64 A4CA0010 */  sh    $t2, 0x10($a2)
/* 0B1668 800B0A68 84ED001E */  lh    $t5, 0x1e($a3)
/* 0B166C 800B0A6C 00000000 */  nop   
/* 0B1670 800B0A70 018D7821 */  addu  $t7, $t4, $t5
/* 0B1674 800B0A74 A4CF0012 */  sh    $t7, 0x12($a2)
/* 0B1678 800B0A78 8CE20000 */  lw    $v0, ($a3)
/* 0B167C 800B0A7C 00000000 */  nop   
/* 0B1680 800B0A80 304E0008 */  andi  $t6, $v0, 8
.L800B0A84:
/* 0B1684 800B0A84 11C0000A */  beqz  $t6, .L800B0AB0
/* 0B1688 800B0A88 00000000 */   nop   
/* 0B168C 800B0A8C 84D80014 */  lh    $t8, 0x14($a2)
/* 0B1690 800B0A90 84F9002A */  lh    $t9, 0x2a($a3)
/* 0B1694 800B0A94 84C90016 */  lh    $t1, 0x16($a2)
/* 0B1698 800B0A98 03194021 */  addu  $t0, $t8, $t9
/* 0B169C 800B0A9C A4C80014 */  sh    $t0, 0x14($a2)
/* 0B16A0 800B0AA0 84EB002C */  lh    $t3, 0x2c($a3)
/* 0B16A4 800B0AA4 00000000 */  nop   
/* 0B16A8 800B0AA8 012B5021 */  addu  $t2, $t1, $t3
/* 0B16AC 800B0AAC A4CA0016 */  sh    $t2, 0x16($a2)
.L800B0AB0:
/* 0B16B0 800B0AB0 846C0006 */  lh    $t4, 6($v1)
/* 0B16B4 800B0AB4 A6000018 */  sh    $zero, 0x18($s0)
/* 0B16B8 800B0AB8 A60C001A */  sh    $t4, 0x1a($s0)
/* 0B16BC 800B0ABC 84640004 */  lh    $a0, 4($v1)
/* 0B16C0 800B0AC0 8E050044 */  lw    $a1, 0x44($s0)
/* 0B16C4 800B0AC4 14810003 */  bne   $a0, $at, .L800B0AD4
/* 0B16C8 800B0AC8 00000000 */   nop   
/* 0B16CC 800B0ACC 10000026 */  b     .L800B0B68
/* 0B16D0 800B0AD0 ACA00000 */   sw    $zero, ($a1)
.L800B0AD4:
/* 0B16D4 800B0AD4 AFA3002C */  sw    $v1, 0x2c($sp)
/* 0B16D8 800B0AD8 0C01EB9D */  jal   func_8007AE74
/* 0B16DC 800B0ADC AFA50024 */   sw    $a1, 0x24($sp)
/* 0B16E0 800B0AE0 8FA50024 */  lw    $a1, 0x24($sp)
/* 0B16E4 800B0AE4 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0B16E8 800B0AE8 1040001F */  beqz  $v0, .L800B0B68
/* 0B16EC 800B0AEC ACA20000 */   sw    $v0, ($a1)
/* 0B16F0 800B0AF0 844F0006 */  lh    $t7, 6($v0)
/* 0B16F4 800B0AF4 00000000 */  nop   
/* 0B16F8 800B0AF8 31EE0004 */  andi  $t6, $t7, 4
/* 0B16FC 800B0AFC 11C0000F */  beqz  $t6, .L800B0B3C
/* 0B1700 800B0B00 00000000 */   nop   
/* 0B1704 800B0B04 8E180040 */  lw    $t8, 0x40($s0)
/* 0B1708 800B0B08 00000000 */  nop   
/* 0B170C 800B0B0C 33191000 */  andi  $t9, $t8, 0x1000
/* 0B1710 800B0B10 13200006 */  beqz  $t9, .L800B0B2C
/* 0B1714 800B0B14 00000000 */   nop   
/* 0B1718 800B0B18 86080006 */  lh    $t0, 6($s0)
/* 0B171C 800B0B1C 00000000 */  nop   
/* 0B1720 800B0B20 35090100 */  ori   $t1, $t0, 0x100
/* 0B1724 800B0B24 10000005 */  b     .L800B0B3C
/* 0B1728 800B0B28 A6090006 */   sh    $t1, 6($s0)
.L800B0B2C:
/* 0B172C 800B0B2C 860B0006 */  lh    $t3, 6($s0)
/* 0B1730 800B0B30 00000000 */  nop   
/* 0B1734 800B0B34 356A0080 */  ori   $t2, $t3, 0x80
/* 0B1738 800B0B38 A60A0006 */  sh    $t2, 6($s0)
.L800B0B3C:
/* 0B173C 800B0B3C 8E0C0040 */  lw    $t4, 0x40($s0)
/* 0B1740 800B0B40 24010002 */  li    $at, 2
/* 0B1744 800B0B44 318D0003 */  andi  $t5, $t4, 3
/* 0B1748 800B0B48 15A10007 */  bne   $t5, $at, .L800B0B68
/* 0B174C 800B0B4C 00000000 */   nop   
/* 0B1750 800B0B50 8CAF0000 */  lw    $t7, ($a1)
/* 0B1754 800B0B54 00000000 */  nop   
/* 0B1758 800B0B58 95EE0012 */  lhu   $t6, 0x12($t7)
/* 0B175C 800B0B5C 00000000 */  nop   
/* 0B1760 800B0B60 25D8FFFF */  addiu $t8, $t6, -1
/* 0B1764 800B0B64 A6180018 */  sh    $t8, 0x18($s0)
.L800B0B68:
/* 0B1768 800B0B68 A2000075 */  sb    $zero, 0x75($s0)
/* 0B176C 800B0B6C 9479000A */  lhu   $t9, 0xa($v1)
/* 0B1770 800B0B70 A2000077 */  sb    $zero, 0x77($s0)
/* 0B1774 800B0B74 00194282 */  srl   $t0, $t9, 0xa
/* 0B1778 800B0B78 A2080076 */  sb    $t0, 0x76($s0)
/* 0B177C 800B0B7C 8CA90000 */  lw    $t1, ($a1)
/* 0B1780 800B0B80 02001025 */  move  $v0, $s0
/* 0B1784 800B0B84 15200005 */  bnez  $t1, .L800B0B9C
/* 0B1788 800B0B88 00000000 */   nop   
/* 0B178C 800B0B8C 0C02C810 */  jal   func_800B2040
/* 0B1790 800B0B90 02002025 */   move  $a0, $s0
/* 0B1794 800B0B94 10000001 */  b     .L800B0B9C
/* 0B1798 800B0B98 00001025 */   move  $v0, $zero
.L800B0B9C:
/* 0B179C 800B0B9C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B17A0 800B0BA0 8FB00018 */  lw    $s0, 0x18($sp)
/* 0B17A4 800B0BA4 03E00008 */  jr    $ra
/* 0B17A8 800B0BA8 27BD0030 */   addiu $sp, $sp, 0x30

glabel func_800B0BAC
/* 0B17AC 800B0BAC 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0B17B0 800B0BB0 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B17B4 800B0BB4 AFB00018 */  sw    $s0, 0x18($sp)
/* 0B17B8 800B0BB8 84AF0008 */  lh    $t7, 8($a1)
/* 0B17BC 800B0BBC 3C0E800E */  lui   $t6, %hi(D_800E2CF0) # $t6, 0x800e
/* 0B17C0 800B0BC0 8DCE2CF0 */  lw    $t6, %lo(D_800E2CF0)($t6)
/* 0B17C4 800B0BC4 000FC080 */  sll   $t8, $t7, 2
/* 0B17C8 800B0BC8 01D8C821 */  addu  $t9, $t6, $t8
/* 0B17CC 800B0BCC 8F280000 */  lw    $t0, ($t9)
/* 0B17D0 800B0BD0 24010003 */  li    $at, 3
/* 0B17D4 800B0BD4 910A0000 */  lbu   $t2, ($t0)
/* 0B17D8 800B0BD8 00808025 */  move  $s0, $a0
/* 0B17DC 800B0BDC 11410003 */  beq   $t2, $at, .L800B0BEC
/* 0B17E0 800B0BE0 00A03025 */   move  $a2, $a1
/* 0B17E4 800B0BE4 1000014E */  b     .L800B1120
/* 0B17E8 800B0BE8 00001025 */   move  $v0, $zero
.L800B0BEC:
/* 0B17EC 800B0BEC 8CC30000 */  lw    $v1, ($a2)
/* 0B17F0 800B0BF0 24040003 */  li    $a0, 3
/* 0B17F4 800B0BF4 8C69009C */  lw    $t1, 0x9c($v1)
/* 0B17F8 800B0BF8 AFA80034 */  sw    $t0, 0x34($sp)
/* 0B17FC 800B0BFC AFA6003C */  sw    $a2, 0x3c($sp)
/* 0B1800 800B0C00 AFA30028 */  sw    $v1, 0x28($sp)
/* 0B1804 800B0C04 0C02C72E */  jal   func_800B1CB8
/* 0B1808 800B0C08 AFA90024 */   sw    $t1, 0x24($sp)
/* 0B180C 800B0C0C 8FA30028 */  lw    $v1, 0x28($sp)
/* 0B1810 800B0C10 8FA6003C */  lw    $a2, 0x3c($sp)
/* 0B1814 800B0C14 8FA80034 */  lw    $t0, 0x34($sp)
/* 0B1818 800B0C18 8FA90024 */  lw    $t1, 0x24($sp)
/* 0B181C 800B0C1C 14400003 */  bnez  $v0, .L800B0C2C
/* 0B1820 800B0C20 00403825 */   move  $a3, $v0
/* 0B1824 800B0C24 1000013E */  b     .L800B1120
/* 0B1828 800B0C28 00001025 */   move  $v0, $zero
.L800B0C2C:
/* 0B182C 800B0C2C 860B002E */  lh    $t3, 0x2e($s0)
/* 0B1830 800B0C30 240C8000 */  li    $t4, -32768
/* 0B1834 800B0C34 A44C0006 */  sh    $t4, 6($v0)
/* 0B1838 800B0C38 A44B002E */  sh    $t3, 0x2e($v0)
/* 0B183C 800B0C3C 910D0001 */  lbu   $t5, 1($t0)
/* 0B1840 800B0C40 00000000 */  nop   
/* 0B1844 800B0C44 A04D0039 */  sb    $t5, 0x39($v0)
/* 0B1848 800B0C48 950F0002 */  lhu   $t7, 2($t0)
/* 0B184C 800B0C4C AC50003C */  sw    $s0, 0x3c($v0)
/* 0B1850 800B0C50 AC460058 */  sw    $a2, 0x58($v0)
/* 0B1854 800B0C54 AC4F0040 */  sw    $t7, 0x40($v0)
/* 0B1858 800B0C58 C5040010 */  lwc1  $f4, 0x10($t0)
/* 0B185C 800B0C5C C4660050 */  lwc1  $f6, 0x50($v1)
/* 0B1860 800B0C60 00000000 */  nop   
/* 0B1864 800B0C64 46062202 */  mul.s $f8, $f4, $f6
/* 0B1868 800B0C68 44802000 */  mtc1  $zero, $f4
/* 0B186C 800B0C6C E4480008 */  swc1  $f8, 8($v0)
/* 0B1870 800B0C70 C4700054 */  lwc1  $f16, 0x54($v1)
/* 0B1874 800B0C74 C50A0010 */  lwc1  $f10, 0x10($t0)
/* 0B1878 800B0C78 3C03800E */  lui   $v1, %hi(D_800E2D00) # $v1, 0x800e
/* 0B187C 800B0C7C 46105482 */  mul.s $f18, $f10, $f16
/* 0B1880 800B0C80 E4520028 */  swc1  $f18, 0x28($v0)
/* 0B1884 800B0C84 850E0008 */  lh    $t6, 8($t0)
/* 0B1888 800B0C88 A0400038 */  sb    $zero, 0x38($v0)
/* 0B188C 800B0C8C E4440034 */  swc1  $f4, 0x34($v0)
/* 0B1890 800B0C90 A44E003A */  sh    $t6, 0x3a($v0)
/* 0B1894 800B0C94 8C632D00 */  lw    $v1, %lo(D_800E2D00)($v1)
/* 0B1898 800B0C98 00000000 */  nop   
/* 0B189C 800B0C9C 10600003 */  beqz  $v1, .L800B0CAC
/* 0B18A0 800B0CA0 00000000 */   nop   
/* 0B18A4 800B0CA4 1000000A */  b     .L800B0CD0
/* 0B18A8 800B0CA8 AC43006C */   sw    $v1, 0x6c($v0)
.L800B0CAC:
/* 0B18AC 800B0CAC 91180014 */  lbu   $t8, 0x14($t0)
/* 0B18B0 800B0CB0 00000000 */  nop   
/* 0B18B4 800B0CB4 A058006C */  sb    $t8, 0x6c($v0)
/* 0B18B8 800B0CB8 91190015 */  lbu   $t9, 0x15($t0)
/* 0B18BC 800B0CBC 00000000 */  nop   
/* 0B18C0 800B0CC0 A059006D */  sb    $t9, 0x6d($v0)
/* 0B18C4 800B0CC4 910A0016 */  lbu   $t2, 0x16($t0)
/* 0B18C8 800B0CC8 00000000 */  nop   
/* 0B18CC 800B0CCC A04A006E */  sb    $t2, 0x6e($v0)
.L800B0CD0:
/* 0B18D0 800B0CD0 8C4C0040 */  lw    $t4, 0x40($v0)
/* 0B18D4 800B0CD4 910B0017 */  lbu   $t3, 0x17($t0)
/* 0B18D8 800B0CD8 318D0800 */  andi  $t5, $t4, 0x800
/* 0B18DC 800B0CDC 11A00014 */  beqz  $t5, .L800B0D30
/* 0B18E0 800B0CE0 A04B006F */   sb    $t3, 0x6f($v0)
/* 0B18E4 800B0CE4 8E030054 */  lw    $v1, 0x54($s0)
/* 0B18E8 800B0CE8 3C01437F */  li    $at, 0x437F0000 # 255.000000
/* 0B18EC 800B0CEC 10600010 */  beqz  $v1, .L800B0D30
/* 0B18F0 800B0CF0 00000000 */   nop   
/* 0B18F4 800B0CF4 C4660000 */  lwc1  $f6, ($v1)
/* 0B18F8 800B0CF8 44814000 */  mtc1  $at, $f8
/* 0B18FC 800B0CFC 00000000 */  nop   
/* 0B1900 800B0D00 46083282 */  mul.s $f10, $f6, $f8
/* 0B1904 800B0D04 444FF800 */  cfc1  $t7, $31
/* 0B1908 800B0D08 00000000 */  nop   
/* 0B190C 800B0D0C 35E10003 */  ori   $at, $t7, 3
/* 0B1910 800B0D10 38210002 */  xori  $at, $at, 2
/* 0B1914 800B0D14 44C1F800 */  ctc1  $at, $31
/* 0B1918 800B0D18 00000000 */  nop   
/* 0B191C 800B0D1C 46005424 */  cvt.w.s $f16, $f10
/* 0B1920 800B0D20 440E8000 */  mfc1  $t6, $f16
/* 0B1924 800B0D24 44CFF800 */  ctc1  $t7, $31
/* 0B1928 800B0D28 10000003 */  b     .L800B0D38
/* 0B192C 800B0D2C A44E004A */   sh    $t6, 0x4a($v0)
.L800B0D30:
/* 0B1930 800B0D30 241800FF */  li    $t8, 255
/* 0B1934 800B0D34 A458004A */  sh    $t8, 0x4a($v0)
.L800B0D38:
/* 0B1938 800B0D38 8519000E */  lh    $t9, 0xe($t0)
/* 0B193C 800B0D3C 00000000 */  nop   
/* 0B1940 800B0D40 A4590060 */  sh    $t9, 0x60($v0)
/* 0B1944 800B0D44 910A000C */  lbu   $t2, 0xc($t0)
/* 0B1948 800B0D48 00000000 */  nop   
/* 0B194C 800B0D4C 000A5A00 */  sll   $t3, $t2, 8
/* 0B1950 800B0D50 A44B005C */  sh    $t3, 0x5c($v0)
/* 0B1954 800B0D54 910C000C */  lbu   $t4, 0xc($t0)
/* 0B1958 800B0D58 00000000 */  nop   
/* 0B195C 800B0D5C 298100FF */  slti  $at, $t4, 0xff
/* 0B1960 800B0D60 1020000F */  beqz  $at, .L800B0DA0
/* 0B1964 800B0D64 00000000 */   nop   
/* 0B1968 800B0D68 8C4D0040 */  lw    $t5, 0x40($v0)
/* 0B196C 800B0D6C 00000000 */  nop   
/* 0B1970 800B0D70 31AF1000 */  andi  $t7, $t5, 0x1000
/* 0B1974 800B0D74 11E00006 */  beqz  $t7, .L800B0D90
/* 0B1978 800B0D78 00000000 */   nop   
/* 0B197C 800B0D7C 844E0006 */  lh    $t6, 6($v0)
/* 0B1980 800B0D80 00000000 */  nop   
/* 0B1984 800B0D84 35D80100 */  ori   $t8, $t6, 0x100
/* 0B1988 800B0D88 10000005 */  b     .L800B0DA0
/* 0B198C 800B0D8C A4580006 */   sh    $t8, 6($v0)
.L800B0D90:
/* 0B1990 800B0D90 84590006 */  lh    $t9, 6($v0)
/* 0B1994 800B0D94 00000000 */  nop   
/* 0B1998 800B0D98 372A0080 */  ori   $t2, $t9, 0x80
/* 0B199C 800B0D9C A44A0006 */  sh    $t2, 6($v0)
.L800B0DA0:
/* 0B19A0 800B0DA0 84440060 */  lh    $a0, 0x60($v0)
/* 0B19A4 800B0DA4 8443003A */  lh    $v1, 0x3a($v0)
/* 0B19A8 800B0DA8 00000000 */  nop   
/* 0B19AC 800B0DAC 0083082A */  slt   $at, $a0, $v1
/* 0B19B0 800B0DB0 10200014 */  beqz  $at, .L800B0E04
/* 0B19B4 800B0DB4 00000000 */   nop   
/* 0B19B8 800B0DB8 910B000D */  lbu   $t3, 0xd($t0)
/* 0B19BC 800B0DBC 910C000C */  lbu   $t4, 0xc($t0)
/* 0B19C0 800B0DC0 00647023 */  subu  $t6, $v1, $a0
/* 0B19C4 800B0DC4 016C6823 */  subu  $t5, $t3, $t4
/* 0B19C8 800B0DC8 000D7A00 */  sll   $t7, $t5, 8
/* 0B19CC 800B0DCC 01EE001A */  div   $zero, $t7, $t6
/* 0B19D0 800B0DD0 15C00002 */  bnez  $t6, .L800B0DDC
/* 0B19D4 800B0DD4 00000000 */   nop   
/* 0B19D8 800B0DD8 0007000D */  break 7
.L800B0DDC:
/* 0B19DC 800B0DDC 2401FFFF */  li    $at, -1
/* 0B19E0 800B0DE0 15C10004 */  bne   $t6, $at, .L800B0DF4
/* 0B19E4 800B0DE4 3C018000 */   lui   $at, 0x8000
/* 0B19E8 800B0DE8 15E10002 */  bne   $t7, $at, .L800B0DF4
/* 0B19EC 800B0DEC 00000000 */   nop   
/* 0B19F0 800B0DF0 0006000D */  break 6
.L800B0DF4:
/* 0B19F4 800B0DF4 0000C012 */  mflo  $t8
/* 0B19F8 800B0DF8 A458005E */  sh    $t8, 0x5e($v0)
/* 0B19FC 800B0DFC 10000003 */  b     .L800B0E0C
/* 0B1A00 800B0E00 84D90018 */   lh    $t9, 0x18($a2)
.L800B0E04:
/* 0B1A04 800B0E04 A440005E */  sh    $zero, 0x5e($v0)
/* 0B1A08 800B0E08 84D90018 */  lh    $t9, 0x18($a2)
.L800B0E0C:
/* 0B1A0C 800B0E0C 84CA001A */  lh    $t2, 0x1a($a2)
/* 0B1A10 800B0E10 84CB001C */  lh    $t3, 0x1c($a2)
/* 0B1A14 800B0E14 44999000 */  mtc1  $t9, $f18
/* 0B1A18 800B0E18 448A3000 */  mtc1  $t2, $f6
/* 0B1A1C 800B0E1C 448B5000 */  mtc1  $t3, $f10
/* 0B1A20 800B0E20 46809120 */  cvt.s.w $f4, $f18
/* 0B1A24 800B0E24 02002025 */  move  $a0, $s0
/* 0B1A28 800B0E28 24C5000C */  addiu $a1, $a2, 0xc
/* 0B1A2C 800B0E2C 46803220 */  cvt.s.w $f8, $f6
/* 0B1A30 800B0E30 E4C4000C */  swc1  $f4, 0xc($a2)
/* 0B1A34 800B0E34 46805420 */  cvt.s.w $f16, $f10
/* 0B1A38 800B0E38 E4C80010 */  swc1  $f8, 0x10($a2)
/* 0B1A3C 800B0E3C E4D00014 */  swc1  $f16, 0x14($a2)
/* 0B1A40 800B0E40 AFA90024 */  sw    $t1, 0x24($sp)
/* 0B1A44 800B0E44 AFA80034 */  sw    $t0, 0x34($sp)
/* 0B1A48 800B0E48 AFA70030 */  sw    $a3, 0x30($sp)
/* 0B1A4C 800B0E4C 0C01C0C8 */  jal   func_80070320
/* 0B1A50 800B0E50 AFA6003C */   sw    $a2, 0x3c($sp)
/* 0B1A54 800B0E54 8FA6003C */  lw    $a2, 0x3c($sp)
/* 0B1A58 800B0E58 C604000C */  lwc1  $f4, 0xc($s0)
/* 0B1A5C 800B0E5C C4D2000C */  lwc1  $f18, 0xc($a2)
/* 0B1A60 800B0E60 8FA70030 */  lw    $a3, 0x30($sp)
/* 0B1A64 800B0E64 46049180 */  add.s $f6, $f18, $f4
/* 0B1A68 800B0E68 8FA80034 */  lw    $t0, 0x34($sp)
/* 0B1A6C 800B0E6C 8FA90024 */  lw    $t1, 0x24($sp)
/* 0B1A70 800B0E70 E4C6000C */  swc1  $f6, 0xc($a2)
/* 0B1A74 800B0E74 C60A0010 */  lwc1  $f10, 0x10($s0)
/* 0B1A78 800B0E78 C4C80010 */  lwc1  $f8, 0x10($a2)
/* 0B1A7C 800B0E7C C4D20014 */  lwc1  $f18, 0x14($a2)
/* 0B1A80 800B0E80 460A4400 */  add.s $f16, $f8, $f10
/* 0B1A84 800B0E84 2402FFFF */  li    $v0, -1
/* 0B1A88 800B0E88 E4D00010 */  swc1  $f16, 0x10($a2)
/* 0B1A8C 800B0E8C C6040014 */  lwc1  $f4, 0x14($s0)
/* 0B1A90 800B0E90 00000000 */  nop   
/* 0B1A94 800B0E94 46049180 */  add.s $f6, $f18, $f4
/* 0B1A98 800B0E98 E4C60014 */  swc1  $f6, 0x14($a2)
/* 0B1A9C 800B0E9C A0E00068 */  sb    $zero, 0x68($a3)
/* 0B1AA0 800B0EA0 A0E0006A */  sb    $zero, 0x6a($a3)
/* 0B1AA4 800B0EA4 A0E2006B */  sb    $v0, 0x6b($a3)
/* 0B1AA8 800B0EA8 850C0006 */  lh    $t4, 6($t0)
/* 0B1AAC 800B0EAC A4E00018 */  sh    $zero, 0x18($a3)
/* 0B1AB0 800B0EB0 A4EC001A */  sh    $t4, 0x1a($a3)
/* 0B1AB4 800B0EB4 85040004 */  lh    $a0, 4($t0)
/* 0B1AB8 800B0EB8 8CE30044 */  lw    $v1, 0x44($a3)
/* 0B1ABC 800B0EBC 14440003 */  bne   $v0, $a0, .L800B0ECC
/* 0B1AC0 800B0EC0 00000000 */   nop   
/* 0B1AC4 800B0EC4 1000002C */  b     .L800B0F78
/* 0B1AC8 800B0EC8 AC600000 */   sw    $zero, ($v1)
.L800B0ECC:
/* 0B1ACC 800B0ECC AFA3002C */  sw    $v1, 0x2c($sp)
/* 0B1AD0 800B0ED0 AFA6003C */  sw    $a2, 0x3c($sp)
/* 0B1AD4 800B0ED4 AFA70030 */  sw    $a3, 0x30($sp)
/* 0B1AD8 800B0ED8 AFA80034 */  sw    $t0, 0x34($sp)
/* 0B1ADC 800B0EDC 0C01EB9D */  jal   func_8007AE74
/* 0B1AE0 800B0EE0 AFA90024 */   sw    $t1, 0x24($sp)
/* 0B1AE4 800B0EE4 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0B1AE8 800B0EE8 8FA6003C */  lw    $a2, 0x3c($sp)
/* 0B1AEC 800B0EEC 8FA70030 */  lw    $a3, 0x30($sp)
/* 0B1AF0 800B0EF0 8FA80034 */  lw    $t0, 0x34($sp)
/* 0B1AF4 800B0EF4 8FA90024 */  lw    $t1, 0x24($sp)
/* 0B1AF8 800B0EF8 1040001F */  beqz  $v0, .L800B0F78
/* 0B1AFC 800B0EFC AC620000 */   sw    $v0, ($v1)
/* 0B1B00 800B0F00 844F0006 */  lh    $t7, 6($v0)
/* 0B1B04 800B0F04 00000000 */  nop   
/* 0B1B08 800B0F08 31EE0004 */  andi  $t6, $t7, 4
/* 0B1B0C 800B0F0C 11C0000F */  beqz  $t6, .L800B0F4C
/* 0B1B10 800B0F10 00000000 */   nop   
/* 0B1B14 800B0F14 8CF80040 */  lw    $t8, 0x40($a3)
/* 0B1B18 800B0F18 00000000 */  nop   
/* 0B1B1C 800B0F1C 33191000 */  andi  $t9, $t8, 0x1000
/* 0B1B20 800B0F20 13200006 */  beqz  $t9, .L800B0F3C
/* 0B1B24 800B0F24 00000000 */   nop   
/* 0B1B28 800B0F28 84EA0006 */  lh    $t2, 6($a3)
/* 0B1B2C 800B0F2C 00000000 */  nop   
/* 0B1B30 800B0F30 354B0100 */  ori   $t3, $t2, 0x100
/* 0B1B34 800B0F34 10000005 */  b     .L800B0F4C
/* 0B1B38 800B0F38 A4EB0006 */   sh    $t3, 6($a3)
.L800B0F3C:
/* 0B1B3C 800B0F3C 84EC0006 */  lh    $t4, 6($a3)
/* 0B1B40 800B0F40 00000000 */  nop   
/* 0B1B44 800B0F44 358D0080 */  ori   $t5, $t4, 0x80
/* 0B1B48 800B0F48 A4ED0006 */  sh    $t5, 6($a3)
.L800B0F4C:
/* 0B1B4C 800B0F4C 8CEF0040 */  lw    $t7, 0x40($a3)
/* 0B1B50 800B0F50 24010002 */  li    $at, 2
/* 0B1B54 800B0F54 31EE0003 */  andi  $t6, $t7, 3
/* 0B1B58 800B0F58 15C10007 */  bne   $t6, $at, .L800B0F78
/* 0B1B5C 800B0F5C 00000000 */   nop   
/* 0B1B60 800B0F60 8C780000 */  lw    $t8, ($v1)
/* 0B1B64 800B0F64 00000000 */  nop   
/* 0B1B68 800B0F68 97190012 */  lhu   $t9, 0x12($t8)
/* 0B1B6C 800B0F6C 00000000 */  nop   
/* 0B1B70 800B0F70 272AFFFF */  addiu $t2, $t9, -1
/* 0B1B74 800B0F74 A4EA0018 */  sh    $t2, 0x18($a3)
.L800B0F78:
/* 0B1B78 800B0F78 444BF800 */  cfc1  $t3, $31
/* 0B1B7C 800B0F7C C4C8000C */  lwc1  $f8, 0xc($a2)
/* 0B1B80 800B0F80 35610003 */  ori   $at, $t3, 3
/* 0B1B84 800B0F84 38210002 */  xori  $at, $at, 2
/* 0B1B88 800B0F88 44C1F800 */  ctc1  $at, $31
/* 0B1B8C 800B0F8C 8C6D0008 */  lw    $t5, 8($v1)
/* 0B1B90 800B0F90 460042A4 */  cvt.w.s $f10, $f8
/* 0B1B94 800B0F94 44CBF800 */  ctc1  $t3, $31
/* 0B1B98 800B0F98 440C5000 */  mfc1  $t4, $f10
/* 0B1B9C 800B0F9C 00000000 */  nop   
/* 0B1BA0 800B0FA0 444FF800 */  cfc1  $t7, $31
/* 0B1BA4 800B0FA4 A5AC0000 */  sh    $t4, ($t5)
/* 0B1BA8 800B0FA8 35E10003 */  ori   $at, $t7, 3
/* 0B1BAC 800B0FAC 38210002 */  xori  $at, $at, 2
/* 0B1BB0 800B0FB0 44C1F800 */  ctc1  $at, $31
/* 0B1BB4 800B0FB4 C4D00010 */  lwc1  $f16, 0x10($a2)
/* 0B1BB8 800B0FB8 8C780008 */  lw    $t8, 8($v1)
/* 0B1BBC 800B0FBC 460084A4 */  cvt.w.s $f18, $f16
/* 0B1BC0 800B0FC0 44CFF800 */  ctc1  $t7, $31
/* 0B1BC4 800B0FC4 440E9000 */  mfc1  $t6, $f18
/* 0B1BC8 800B0FC8 00000000 */  nop   
/* 0B1BCC 800B0FCC 4459F800 */  cfc1  $t9, $31
/* 0B1BD0 800B0FD0 A70E0002 */  sh    $t6, 2($t8)
/* 0B1BD4 800B0FD4 37210003 */  ori   $at, $t9, 3
/* 0B1BD8 800B0FD8 38210002 */  xori  $at, $at, 2
/* 0B1BDC 800B0FDC 44C1F800 */  ctc1  $at, $31
/* 0B1BE0 800B0FE0 C4C40014 */  lwc1  $f4, 0x14($a2)
/* 0B1BE4 800B0FE4 8C6B0008 */  lw    $t3, 8($v1)
/* 0B1BE8 800B0FE8 460021A4 */  cvt.w.s $f6, $f4
/* 0B1BEC 800B0FEC 2401FFFF */  li    $at, -1
/* 0B1BF0 800B0FF0 440A3000 */  mfc1  $t2, $f6
/* 0B1BF4 800B0FF4 44D9F800 */  ctc1  $t9, $31
/* 0B1BF8 800B0FF8 11210026 */  beq   $t1, $at, .L800B1094
/* 0B1BFC 800B0FFC A56A0004 */   sh    $t2, 4($t3)
/* 0B1C00 800B1000 84CC001E */  lh    $t4, 0x1e($a2)
/* 0B1C04 800B1004 00000000 */  nop   
/* 0B1C08 800B1008 258D0001 */  addiu $t5, $t4, 1
/* 0B1C0C 800B100C A4CD001E */  sh    $t5, 0x1e($a2)
/* 0B1C10 800B1010 8D2F0000 */  lw    $t7, ($t1)
/* 0B1C14 800B1014 84C2001E */  lh    $v0, 0x1e($a2)
/* 0B1C18 800B1018 00000000 */  nop   
/* 0B1C1C 800B101C 004F082A */  slt   $at, $v0, $t7
/* 0B1C20 800B1020 14200005 */  bnez  $at, .L800B1038
/* 0B1C24 800B1024 000270C0 */   sll   $t6, $v0, 3
/* 0B1C28 800B1028 A4C0001E */  sh    $zero, 0x1e($a2)
/* 0B1C2C 800B102C 84C2001E */  lh    $v0, 0x1e($a2)
/* 0B1C30 800B1030 00000000 */  nop   
/* 0B1C34 800B1034 000270C0 */  sll   $t6, $v0, 3
.L800B1038:
/* 0B1C38 800B1038 012EC021 */  addu  $t8, $t1, $t6
/* 0B1C3C 800B103C 93190014 */  lbu   $t9, 0x14($t8)
/* 0B1C40 800B1040 8C6A0008 */  lw    $t2, 8($v1)
/* 0B1C44 800B1044 00000000 */  nop   
/* 0B1C48 800B1048 A1590006 */  sb    $t9, 6($t2)
/* 0B1C4C 800B104C 84CB001E */  lh    $t3, 0x1e($a2)
/* 0B1C50 800B1050 8C6E0008 */  lw    $t6, 8($v1)
/* 0B1C54 800B1054 000B60C0 */  sll   $t4, $t3, 3
/* 0B1C58 800B1058 012C6821 */  addu  $t5, $t1, $t4
/* 0B1C5C 800B105C 91AF0015 */  lbu   $t7, 0x15($t5)
/* 0B1C60 800B1060 00000000 */  nop   
/* 0B1C64 800B1064 A1CF0007 */  sb    $t7, 7($t6)
/* 0B1C68 800B1068 84D8001E */  lh    $t8, 0x1e($a2)
/* 0B1C6C 800B106C 8C6C0008 */  lw    $t4, 8($v1)
/* 0B1C70 800B1070 0018C8C0 */  sll   $t9, $t8, 3
/* 0B1C74 800B1074 01395021 */  addu  $t2, $t1, $t9
/* 0B1C78 800B1078 914B0016 */  lbu   $t3, 0x16($t2)
/* 0B1C7C 800B107C 00000000 */  nop   
/* 0B1C80 800B1080 A18B0008 */  sb    $t3, 8($t4)
/* 0B1C84 800B1084 8C6F0008 */  lw    $t7, 8($v1)
/* 0B1C88 800B1088 90CD0006 */  lbu   $t5, 6($a2)
/* 0B1C8C 800B108C 10000011 */  b     .L800B10D4
/* 0B1C90 800B1090 A1ED0009 */   sb    $t5, 9($t7)
.L800B1094:
/* 0B1C94 800B1094 90EE006C */  lbu   $t6, 0x6c($a3)
/* 0B1C98 800B1098 8C780008 */  lw    $t8, 8($v1)
/* 0B1C9C 800B109C 00000000 */  nop   
/* 0B1CA0 800B10A0 A30E0006 */  sb    $t6, 6($t8)
/* 0B1CA4 800B10A4 8C6A0008 */  lw    $t2, 8($v1)
/* 0B1CA8 800B10A8 90F9006D */  lbu   $t9, 0x6d($a3)
/* 0B1CAC 800B10AC 00000000 */  nop   
/* 0B1CB0 800B10B0 A1590007 */  sb    $t9, 7($t2)
/* 0B1CB4 800B10B4 8C6C0008 */  lw    $t4, 8($v1)
/* 0B1CB8 800B10B8 90EB006E */  lbu   $t3, 0x6e($a3)
/* 0B1CBC 800B10BC 00000000 */  nop   
/* 0B1CC0 800B10C0 A18B0008 */  sb    $t3, 8($t4)
/* 0B1CC4 800B10C4 8C6F0008 */  lw    $t7, 8($v1)
/* 0B1CC8 800B10C8 90CD0006 */  lbu   $t5, 6($a2)
/* 0B1CCC 800B10CC 00000000 */  nop   
/* 0B1CD0 800B10D0 A1ED0009 */  sb    $t5, 9($t7)
.L800B10D4:
/* 0B1CD4 800B10D4 950E000A */  lhu   $t6, 0xa($t0)
/* 0B1CD8 800B10D8 00E01025 */  move  $v0, $a3
/* 0B1CDC 800B10DC 000EC282 */  srl   $t8, $t6, 0xa
/* 0B1CE0 800B10E0 A0F8006A */  sb    $t8, 0x6a($a3)
/* 0B1CE4 800B10E4 8D190008 */  lw    $t9, 8($t0)
/* 0B1CE8 800B10E8 00000000 */  nop   
/* 0B1CEC 800B10EC 00195580 */  sll   $t2, $t9, 0x16
/* 0B1CF0 800B10F0 000A5E82 */  srl   $t3, $t2, 0x1a
/* 0B1CF4 800B10F4 A0EB006B */  sb    $t3, 0x6b($a3)
/* 0B1CF8 800B10F8 C608000C */  lwc1  $f8, 0xc($s0)
/* 0B1CFC 800B10FC 00000000 */  nop   
/* 0B1D00 800B1100 E4E8000C */  swc1  $f8, 0xc($a3)
/* 0B1D04 800B1104 C60A0010 */  lwc1  $f10, 0x10($s0)
/* 0B1D08 800B1108 00000000 */  nop   
/* 0B1D0C 800B110C E4EA0010 */  swc1  $f10, 0x10($a3)
/* 0B1D10 800B1110 C6100014 */  lwc1  $f16, 0x14($s0)
/* 0B1D14 800B1114 00000000 */  nop   
/* 0B1D18 800B1118 E4F00014 */  swc1  $f16, 0x14($a3)
/* 0B1D1C 800B111C A4C0000A */  sh    $zero, 0xa($a2)
.L800B1120:
/* 0B1D20 800B1120 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B1D24 800B1124 8FB00018 */  lw    $s0, 0x18($sp)
/* 0B1D28 800B1128 03E00008 */  jr    $ra
/* 0B1D2C 800B112C 27BD0038 */   addiu $sp, $sp, 0x38

glabel func_800B1130
/* 0B1D30 800B1130 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 0B1D34 800B1134 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B1D38 800B1138 AFB10018 */  sw    $s1, 0x18($sp)
/* 0B1D3C 800B113C AFB00014 */  sw    $s0, 0x14($sp)
/* 0B1D40 800B1140 AFA40040 */  sw    $a0, 0x40($sp)
/* 0B1D44 800B1144 84AF0008 */  lh    $t7, 8($a1)
/* 0B1D48 800B1148 3C0E800E */  lui   $t6, %hi(D_800E2CF0) # $t6, 0x800e
/* 0B1D4C 800B114C 8DCE2CF0 */  lw    $t6, %lo(D_800E2CF0)($t6)
/* 0B1D50 800B1150 000FC080 */  sll   $t8, $t7, 2
/* 0B1D54 800B1154 01D8C821 */  addu  $t9, $t6, $t8
/* 0B1D58 800B1158 8F270000 */  lw    $a3, ($t9)
/* 0B1D5C 800B115C 24010003 */  li    $at, 3
/* 0B1D60 800B1160 90E60000 */  lbu   $a2, ($a3)
/* 0B1D64 800B1164 00000000 */  nop   
/* 0B1D68 800B1168 10C10003 */  beq   $a2, $at, .L800B1178
/* 0B1D6C 800B116C 24010004 */   li    $at, 4
/* 0B1D70 800B1170 14C10003 */  bne   $a2, $at, .L800B1180
/* 0B1D74 800B1174 00000000 */   nop   
.L800B1178:
/* 0B1D78 800B1178 100002CA */  b     .L800B1CA4
/* 0B1D7C 800B117C 00001025 */   move  $v0, $zero
.L800B1180:
/* 0B1D80 800B1180 8CB10000 */  lw    $s1, ($a1)
/* 0B1D84 800B1184 00C02025 */  move  $a0, $a2
/* 0B1D88 800B1188 8E28009C */  lw    $t0, 0x9c($s1)
/* 0B1D8C 800B118C AFA70038 */  sw    $a3, 0x38($sp)
/* 0B1D90 800B1190 AFA50044 */  sw    $a1, 0x44($sp)
/* 0B1D94 800B1194 0C02C72E */  jal   func_800B1CB8
/* 0B1D98 800B1198 AFA80028 */   sw    $t0, 0x28($sp)
/* 0B1D9C 800B119C 8FA70038 */  lw    $a3, 0x38($sp)
/* 0B1DA0 800B11A0 8FA80028 */  lw    $t0, 0x28($sp)
/* 0B1DA4 800B11A4 14400003 */  bnez  $v0, .L800B11B4
/* 0B1DA8 800B11A8 00408025 */   move  $s0, $v0
/* 0B1DAC 800B11AC 100002BD */  b     .L800B1CA4
/* 0B1DB0 800B11B0 02001025 */   move  $v0, $s0
.L800B11B4:
/* 0B1DB4 800B11B4 8FA90040 */  lw    $t1, 0x40($sp)
/* 0B1DB8 800B11B8 240B8000 */  li    $t3, -32768
/* 0B1DBC 800B11BC 852A002E */  lh    $t2, 0x2e($t1)
/* 0B1DC0 800B11C0 A44B0006 */  sh    $t3, 6($v0)
/* 0B1DC4 800B11C4 A44A002E */  sh    $t2, 0x2e($v0)
/* 0B1DC8 800B11C8 90EC0001 */  lbu   $t4, 1($a3)
/* 0B1DCC 800B11CC 240A00FF */  li    $t2, 255
/* 0B1DD0 800B11D0 A04C0039 */  sb    $t4, 0x39($v0)
/* 0B1DD4 800B11D4 94ED0002 */  lhu   $t5, 2($a3)
/* 0B1DD8 800B11D8 AC49003C */  sw    $t1, 0x3c($v0)
/* 0B1DDC 800B11DC 31AE0800 */  andi  $t6, $t5, 0x800
/* 0B1DE0 800B11E0 11C00014 */  beqz  $t6, .L800B1234
/* 0B1DE4 800B11E4 AC4D0040 */   sw    $t5, 0x40($v0)
/* 0B1DE8 800B11E8 8D230054 */  lw    $v1, 0x54($t1)
/* 0B1DEC 800B11EC 3C01437F */  li    $at, 0x437F0000 # 255.000000
/* 0B1DF0 800B11F0 10600010 */  beqz  $v1, .L800B1234
/* 0B1DF4 800B11F4 00000000 */   nop   
/* 0B1DF8 800B11F8 C4640000 */  lwc1  $f4, ($v1)
/* 0B1DFC 800B11FC 44813000 */  mtc1  $at, $f6
/* 0B1E00 800B1200 00000000 */  nop   
/* 0B1E04 800B1204 46062202 */  mul.s $f8, $f4, $f6
/* 0B1E08 800B1208 4458F800 */  cfc1  $t8, $31
/* 0B1E0C 800B120C 00000000 */  nop   
/* 0B1E10 800B1210 37010003 */  ori   $at, $t8, 3
/* 0B1E14 800B1214 38210002 */  xori  $at, $at, 2
/* 0B1E18 800B1218 44C1F800 */  ctc1  $at, $31
/* 0B1E1C 800B121C 00000000 */  nop   
/* 0B1E20 800B1220 460042A4 */  cvt.w.s $f10, $f8
/* 0B1E24 800B1224 44195000 */  mfc1  $t9, $f10
/* 0B1E28 800B1228 44D8F800 */  ctc1  $t8, $31
/* 0B1E2C 800B122C 10000002 */  b     .L800B1238
/* 0B1E30 800B1230 A459004A */   sh    $t9, 0x4a($v0)
.L800B1234:
/* 0B1E34 800B1234 A44A004A */  sh    $t2, 0x4a($v0)
.L800B1238:
/* 0B1E38 800B1238 8E2B005C */  lw    $t3, 0x5c($s1)
/* 0B1E3C 800B123C C6300050 */  lwc1  $f16, 0x50($s1)
/* 0B1E40 800B1240 000B6380 */  sll   $t4, $t3, 0xe
/* 0B1E44 800B1244 05810015 */  bgez  $t4, .L800B129C
/* 0B1E48 800B1248 00000000 */   nop   
/* 0B1E4C 800B124C 8E25008C */  lw    $a1, 0x8c($s1)
/* 0B1E50 800B1250 E7B00024 */  swc1  $f16, 0x24($sp)
/* 0B1E54 800B1254 AFA80028 */  sw    $t0, 0x28($sp)
/* 0B1E58 800B1258 AFA70038 */  sw    $a3, 0x38($sp)
/* 0B1E5C 800B125C 0C01BE53 */  jal   func_8006F94C
/* 0B1E60 800B1260 00052023 */   negu  $a0, $a1
/* 0B1E64 800B1264 44829000 */  mtc1  $v0, $f18
/* 0B1E68 800B1268 3C01800F */  lui   $at, %hi(D_800E8BCC) # $at, 0x800f
/* 0B1E6C 800B126C 46809120 */  cvt.s.w $f4, $f18
/* 0B1E70 800B1270 C4298BC8 */  lwc1  $f9, %lo(D_800E8BC8)($at)
/* 0B1E74 800B1274 C4288BCC */  lwc1  $f8, %lo(D_800E8BCC)($at)
/* 0B1E78 800B1278 460021A1 */  cvt.d.s $f6, $f4
/* 0B1E7C 800B127C 46283282 */  mul.d $f10, $f6, $f8
/* 0B1E80 800B1280 C7B00024 */  lwc1  $f16, 0x24($sp)
/* 0B1E84 800B1284 8FA70038 */  lw    $a3, 0x38($sp)
/* 0B1E88 800B1288 460084A1 */  cvt.d.s $f18, $f16
/* 0B1E8C 800B128C 8FA80028 */  lw    $t0, 0x28($sp)
/* 0B1E90 800B1290 462A9100 */  add.d $f4, $f18, $f10
/* 0B1E94 800B1294 8FA90040 */  lw    $t1, 0x40($sp)
/* 0B1E98 800B1298 46202420 */  cvt.s.d $f16, $f4
.L800B129C:
/* 0B1E9C 800B129C C4E60010 */  lwc1  $f6, 0x10($a3)
/* 0B1EA0 800B12A0 00000000 */  nop   
/* 0B1EA4 800B12A4 46103202 */  mul.s $f8, $f6, $f16
/* 0B1EA8 800B12A8 E6080008 */  swc1  $f8, 8($s0)
/* 0B1EAC 800B12AC 8E2D005C */  lw    $t5, 0x5c($s1)
/* 0B1EB0 800B12B0 C6300054 */  lwc1  $f16, 0x54($s1)
/* 0B1EB4 800B12B4 000D7B40 */  sll   $t7, $t5, 0xd
/* 0B1EB8 800B12B8 05E10015 */  bgez  $t7, .L800B1310
/* 0B1EBC 800B12BC 00000000 */   nop   
/* 0B1EC0 800B12C0 8E250090 */  lw    $a1, 0x90($s1)
/* 0B1EC4 800B12C4 E7B00024 */  swc1  $f16, 0x24($sp)
/* 0B1EC8 800B12C8 AFA80028 */  sw    $t0, 0x28($sp)
/* 0B1ECC 800B12CC AFA70038 */  sw    $a3, 0x38($sp)
/* 0B1ED0 800B12D0 0C01BE53 */  jal   func_8006F94C
/* 0B1ED4 800B12D4 00052023 */   negu  $a0, $a1
/* 0B1ED8 800B12D8 44829000 */  mtc1  $v0, $f18
/* 0B1EDC 800B12DC 3C01800F */  lui   $at, %hi(D_800E8BD4) # $at, 0x800f
/* 0B1EE0 800B12E0 468092A0 */  cvt.s.w $f10, $f18
/* 0B1EE4 800B12E4 C4278BD0 */  lwc1  $f7, %lo(D_800E8BD0)($at)
/* 0B1EE8 800B12E8 C4268BD4 */  lwc1  $f6, %lo(D_800E8BD4)($at)
/* 0B1EEC 800B12EC 46005121 */  cvt.d.s $f4, $f10
/* 0B1EF0 800B12F0 46262202 */  mul.d $f8, $f4, $f6
/* 0B1EF4 800B12F4 C7B00024 */  lwc1  $f16, 0x24($sp)
/* 0B1EF8 800B12F8 8FA70038 */  lw    $a3, 0x38($sp)
/* 0B1EFC 800B12FC 460084A1 */  cvt.d.s $f18, $f16
/* 0B1F00 800B1300 8FA80028 */  lw    $t0, 0x28($sp)
/* 0B1F04 800B1304 46289280 */  add.d $f10, $f18, $f8
/* 0B1F08 800B1308 8FA90040 */  lw    $t1, 0x40($sp)
/* 0B1F0C 800B130C 46205420 */  cvt.s.d $f16, $f10
.L800B1310:
/* 0B1F10 800B1310 8E2E0000 */  lw    $t6, ($s1)
/* 0B1F14 800B1314 00000000 */  nop   
/* 0B1F18 800B1318 31D81000 */  andi  $t8, $t6, 0x1000
/* 0B1F1C 800B131C 13000016 */  beqz  $t8, .L800B1378
/* 0B1F20 800B1320 00000000 */   nop   
/* 0B1F24 800B1324 C520001C */  lwc1  $f0, 0x1c($t1)
/* 0B1F28 800B1328 C5220020 */  lwc1  $f2, 0x20($t1)
/* 0B1F2C 800B132C 46000102 */  mul.s $f4, $f0, $f0
/* 0B1F30 800B1330 C52E0024 */  lwc1  $f14, 0x24($t1)
/* 0B1F34 800B1334 E7B00024 */  swc1  $f16, 0x24($sp)
/* 0B1F38 800B1338 AFA80028 */  sw    $t0, 0x28($sp)
/* 0B1F3C 800B133C 46021182 */  mul.s $f6, $f2, $f2
/* 0B1F40 800B1340 AFA70038 */  sw    $a3, 0x38($sp)
/* 0B1F44 800B1344 460E7202 */  mul.s $f8, $f14, $f14
/* 0B1F48 800B1348 46062480 */  add.s $f18, $f4, $f6
/* 0B1F4C 800B134C 0C0326B4 */  jal   sqrtf
/* 0B1F50 800B1350 46089300 */   add.s $f12, $f18, $f8
/* 0B1F54 800B1354 C7B00024 */  lwc1  $f16, 0x24($sp)
/* 0B1F58 800B1358 3C01800F */  lui   $at, %hi(D_800E8BD8) # $at, 0x800f
/* 0B1F5C 800B135C 46100282 */  mul.s $f10, $f0, $f16
/* 0B1F60 800B1360 C4248BD8 */  lwc1  $f4, %lo(D_800E8BD8)($at)
/* 0B1F64 800B1364 8FA70038 */  lw    $a3, 0x38($sp)
/* 0B1F68 800B1368 8FA80028 */  lw    $t0, 0x28($sp)
/* 0B1F6C 800B136C 46045182 */  mul.s $f6, $f10, $f4
/* 0B1F70 800B1370 10000005 */  b     .L800B1388
/* 0B1F74 800B1374 E6060028 */   swc1  $f6, 0x28($s0)
.L800B1378:
/* 0B1F78 800B1378 C4F20010 */  lwc1  $f18, 0x10($a3)
/* 0B1F7C 800B137C 00000000 */  nop   
/* 0B1F80 800B1380 46109202 */  mul.s $f8, $f18, $f16
/* 0B1F84 800B1384 E6080028 */  swc1  $f8, 0x28($s0)
.L800B1388:
/* 0B1F88 800B1388 84E5000A */  lh    $a1, 0xa($a3)
/* 0B1F8C 800B138C AFA80028 */  sw    $t0, 0x28($sp)
/* 0B1F90 800B1390 AFA70038 */  sw    $a3, 0x38($sp)
/* 0B1F94 800B1394 0C01BE53 */  jal   func_8006F94C
/* 0B1F98 800B1398 00052023 */   negu  $a0, $a1
/* 0B1F9C 800B139C 8FA70038 */  lw    $a3, 0x38($sp)
/* 0B1FA0 800B13A0 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B1FA4 800B13A4 84F90008 */  lh    $t9, 8($a3)
/* 0B1FA8 800B13A8 8FA80028 */  lw    $t0, 0x28($sp)
/* 0B1FAC 800B13AC 44805000 */  mtc1  $zero, $f10
/* 0B1FB0 800B13B0 00595021 */  addu  $t2, $v0, $t9
/* 0B1FB4 800B13B4 A60A003A */  sh    $t2, 0x3a($s0)
/* 0B1FB8 800B13B8 A2000038 */  sb    $zero, 0x38($s0)
/* 0B1FBC 800B13BC 3C03800E */  lui   $v1, %hi(D_800E2D00) # $v1, 0x800e
/* 0B1FC0 800B13C0 E60A0034 */  swc1  $f10, 0x34($s0)
/* 0B1FC4 800B13C4 8C632D00 */  lw    $v1, %lo(D_800E2D00)($v1)
/* 0B1FC8 800B13C8 2401FFFF */  li    $at, -1
/* 0B1FCC 800B13CC 10600003 */  beqz  $v1, .L800B13DC
/* 0B1FD0 800B13D0 00000000 */   nop   
/* 0B1FD4 800B13D4 10000036 */  b     .L800B14B0
/* 0B1FD8 800B13D8 AE03006C */   sw    $v1, 0x6c($s0)
.L800B13DC:
/* 0B1FDC 800B13DC 11010028 */  beq   $t0, $at, .L800B1480
/* 0B1FE0 800B13E0 00000000 */   nop   
/* 0B1FE4 800B13E4 84CB001E */  lh    $t3, 0x1e($a2)
/* 0B1FE8 800B13E8 00000000 */  nop   
/* 0B1FEC 800B13EC 256C0001 */  addiu $t4, $t3, 1
/* 0B1FF0 800B13F0 A4CC001E */  sh    $t4, 0x1e($a2)
/* 0B1FF4 800B13F4 8D0D0000 */  lw    $t5, ($t0)
/* 0B1FF8 800B13F8 84C2001E */  lh    $v0, 0x1e($a2)
/* 0B1FFC 800B13FC 00000000 */  nop   
/* 0B2000 800B1400 004D082A */  slt   $at, $v0, $t5
/* 0B2004 800B1404 14200005 */  bnez  $at, .L800B141C
/* 0B2008 800B1408 000278C0 */   sll   $t7, $v0, 3
/* 0B200C 800B140C A4C0001E */  sh    $zero, 0x1e($a2)
/* 0B2010 800B1410 84C2001E */  lh    $v0, 0x1e($a2)
/* 0B2014 800B1414 00000000 */  nop   
/* 0B2018 800B1418 000278C0 */  sll   $t7, $v0, 3
.L800B141C:
/* 0B201C 800B141C 010F7021 */  addu  $t6, $t0, $t7
/* 0B2020 800B1420 91D80014 */  lbu   $t8, 0x14($t6)
/* 0B2024 800B1424 00000000 */  nop   
/* 0B2028 800B1428 A218006C */  sb    $t8, 0x6c($s0)
/* 0B202C 800B142C 84D9001E */  lh    $t9, 0x1e($a2)
/* 0B2030 800B1430 00000000 */  nop   
/* 0B2034 800B1434 001950C0 */  sll   $t2, $t9, 3
/* 0B2038 800B1438 010A5821 */  addu  $t3, $t0, $t2
/* 0B203C 800B143C 916C0015 */  lbu   $t4, 0x15($t3)
/* 0B2040 800B1440 00000000 */  nop   
/* 0B2044 800B1444 A20C006D */  sb    $t4, 0x6d($s0)
/* 0B2048 800B1448 84CD001E */  lh    $t5, 0x1e($a2)
/* 0B204C 800B144C 00000000 */  nop   
/* 0B2050 800B1450 000D78C0 */  sll   $t7, $t5, 3
/* 0B2054 800B1454 010F7021 */  addu  $t6, $t0, $t7
/* 0B2058 800B1458 91D80016 */  lbu   $t8, 0x16($t6)
/* 0B205C 800B145C 00000000 */  nop   
/* 0B2060 800B1460 A218006E */  sb    $t8, 0x6e($s0)
/* 0B2064 800B1464 84D9001E */  lh    $t9, 0x1e($a2)
/* 0B2068 800B1468 00000000 */  nop   
/* 0B206C 800B146C 001950C0 */  sll   $t2, $t9, 3
/* 0B2070 800B1470 010A5821 */  addu  $t3, $t0, $t2
/* 0B2074 800B1474 916C0017 */  lbu   $t4, 0x17($t3)
/* 0B2078 800B1478 1000000D */  b     .L800B14B0
/* 0B207C 800B147C A20C006F */   sb    $t4, 0x6f($s0)
.L800B1480:
/* 0B2080 800B1480 90ED0014 */  lbu   $t5, 0x14($a3)
/* 0B2084 800B1484 00000000 */  nop   
/* 0B2088 800B1488 A20D006C */  sb    $t5, 0x6c($s0)
/* 0B208C 800B148C 90EF0015 */  lbu   $t7, 0x15($a3)
/* 0B2090 800B1490 00000000 */  nop   
/* 0B2094 800B1494 A20F006D */  sb    $t7, 0x6d($s0)
/* 0B2098 800B1498 90EE0016 */  lbu   $t6, 0x16($a3)
/* 0B209C 800B149C 00000000 */  nop   
/* 0B20A0 800B14A0 A20E006E */  sb    $t6, 0x6e($s0)
/* 0B20A4 800B14A4 90F80017 */  lbu   $t8, 0x17($a3)
/* 0B20A8 800B14A8 00000000 */  nop   
/* 0B20AC 800B14AC A218006F */  sb    $t8, 0x6f($s0)
.L800B14B0:
/* 0B20B0 800B14B0 8E23005C */  lw    $v1, 0x5c($s1)
/* 0B20B4 800B14B4 3C0100F0 */  lui   $at, 0xf0
/* 0B20B8 800B14B8 0061C824 */  and   $t9, $v1, $at
/* 0B20BC 800B14BC 13200037 */  beqz  $t9, .L800B159C
/* 0B20C0 800B14C0 03201825 */   move  $v1, $t9
/* 0B20C4 800B14C4 001952C0 */  sll   $t2, $t9, 0xb
/* 0B20C8 800B14C8 0541000D */  bgez  $t2, .L800B1500
/* 0B20CC 800B14CC 00036A80 */   sll   $t5, $v1, 0xa
/* 0B20D0 800B14D0 92250098 */  lbu   $a1, 0x98($s1)
/* 0B20D4 800B14D4 AFA70038 */  sw    $a3, 0x38($sp)
/* 0B20D8 800B14D8 AFB9003C */  sw    $t9, 0x3c($sp)
/* 0B20DC 800B14DC 0C01BE53 */  jal   func_8006F94C
/* 0B20E0 800B14E0 00052023 */   negu  $a0, $a1
/* 0B20E4 800B14E4 920B006C */  lbu   $t3, 0x6c($s0)
/* 0B20E8 800B14E8 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B20EC 800B14EC 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B20F0 800B14F0 8FA70038 */  lw    $a3, 0x38($sp)
/* 0B20F4 800B14F4 01626021 */  addu  $t4, $t3, $v0
/* 0B20F8 800B14F8 A20C006C */  sb    $t4, 0x6c($s0)
/* 0B20FC 800B14FC 00036A80 */  sll   $t5, $v1, 0xa
.L800B1500:
/* 0B2100 800B1500 05A1000D */  bgez  $t5, .L800B1538
/* 0B2104 800B1504 0003C240 */   sll   $t8, $v1, 9
/* 0B2108 800B1508 92250099 */  lbu   $a1, 0x99($s1)
/* 0B210C 800B150C AFA70038 */  sw    $a3, 0x38($sp)
/* 0B2110 800B1510 AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B2114 800B1514 0C01BE53 */  jal   func_8006F94C
/* 0B2118 800B1518 00052023 */   negu  $a0, $a1
/* 0B211C 800B151C 920F006D */  lbu   $t7, 0x6d($s0)
/* 0B2120 800B1520 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B2124 800B1524 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2128 800B1528 8FA70038 */  lw    $a3, 0x38($sp)
/* 0B212C 800B152C 01E27021 */  addu  $t6, $t7, $v0
/* 0B2130 800B1530 A20E006D */  sb    $t6, 0x6d($s0)
/* 0B2134 800B1534 0003C240 */  sll   $t8, $v1, 9
.L800B1538:
/* 0B2138 800B1538 0701000D */  bgez  $t8, .L800B1570
/* 0B213C 800B153C 00035A00 */   sll   $t3, $v1, 8
/* 0B2140 800B1540 9225009A */  lbu   $a1, 0x9a($s1)
/* 0B2144 800B1544 AFA70038 */  sw    $a3, 0x38($sp)
/* 0B2148 800B1548 AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B214C 800B154C 0C01BE53 */  jal   func_8006F94C
/* 0B2150 800B1550 00052023 */   negu  $a0, $a1
/* 0B2154 800B1554 9219006E */  lbu   $t9, 0x6e($s0)
/* 0B2158 800B1558 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B215C 800B155C 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2160 800B1560 8FA70038 */  lw    $a3, 0x38($sp)
/* 0B2164 800B1564 03225021 */  addu  $t2, $t9, $v0
/* 0B2168 800B1568 A20A006E */  sb    $t2, 0x6e($s0)
/* 0B216C 800B156C 00035A00 */  sll   $t3, $v1, 8
.L800B1570:
/* 0B2170 800B1570 0561000A */  bgez  $t3, .L800B159C
/* 0B2174 800B1574 00000000 */   nop   
/* 0B2178 800B1578 9225009B */  lbu   $a1, 0x9b($s1)
/* 0B217C 800B157C AFA70038 */  sw    $a3, 0x38($sp)
/* 0B2180 800B1580 0C01BE53 */  jal   func_8006F94C
/* 0B2184 800B1584 00052023 */   negu  $a0, $a1
/* 0B2188 800B1588 920C006F */  lbu   $t4, 0x6f($s0)
/* 0B218C 800B158C 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2190 800B1590 8FA70038 */  lw    $a3, 0x38($sp)
/* 0B2194 800B1594 01826821 */  addu  $t5, $t4, $v0
/* 0B2198 800B1598 A20D006F */  sb    $t5, 0x6f($s0)
.L800B159C:
/* 0B219C 800B159C 84EF000E */  lh    $t7, 0xe($a3)
/* 0B21A0 800B15A0 3C04800E */  lui   $a0, %hi(D_800E2EEC) # $a0, 0x800e
/* 0B21A4 800B15A4 A60F0060 */  sh    $t7, 0x60($s0)
/* 0B21A8 800B15A8 24842EEC */  addiu $a0, %lo(D_800E2EEC) # addiu $a0, $a0, 0x2eec
/* 0B21AC 800B15AC 8C980000 */  lw    $t8, ($a0)
/* 0B21B0 800B15B0 90EE000C */  lbu   $t6, 0xc($a3)
/* 0B21B4 800B15B4 00000000 */  nop   
/* 0B21B8 800B15B8 01D80019 */  multu $t6, $t8
/* 0B21BC 800B15BC 0000C812 */  mflo  $t9
/* 0B21C0 800B15C0 A619005C */  sh    $t9, 0x5c($s0)
/* 0B21C4 800B15C4 90EA000C */  lbu   $t2, 0xc($a3)
/* 0B21C8 800B15C8 00000000 */  nop   
/* 0B21CC 800B15CC 294100FF */  slti  $at, $t2, 0xff
/* 0B21D0 800B15D0 1020000F */  beqz  $at, .L800B1610
/* 0B21D4 800B15D4 00000000 */   nop   
/* 0B21D8 800B15D8 8E0B0040 */  lw    $t3, 0x40($s0)
/* 0B21DC 800B15DC 00000000 */  nop   
/* 0B21E0 800B15E0 316C1000 */  andi  $t4, $t3, 0x1000
/* 0B21E4 800B15E4 11800006 */  beqz  $t4, .L800B1600
/* 0B21E8 800B15E8 00000000 */   nop   
/* 0B21EC 800B15EC 860D0006 */  lh    $t5, 6($s0)
/* 0B21F0 800B15F0 00000000 */  nop   
/* 0B21F4 800B15F4 35AF0100 */  ori   $t7, $t5, 0x100
/* 0B21F8 800B15F8 10000005 */  b     .L800B1610
/* 0B21FC 800B15FC A60F0006 */   sh    $t7, 6($s0)
.L800B1600:
/* 0B2200 800B1600 860E0006 */  lh    $t6, 6($s0)
/* 0B2204 800B1604 00000000 */  nop   
/* 0B2208 800B1608 35D80080 */  ori   $t8, $t6, 0x80
/* 0B220C 800B160C A6180006 */  sh    $t8, 6($s0)
.L800B1610:
/* 0B2210 800B1610 86020060 */  lh    $v0, 0x60($s0)
/* 0B2214 800B1614 8603003A */  lh    $v1, 0x3a($s0)
/* 0B2218 800B1618 00000000 */  nop   
/* 0B221C 800B161C 0043082A */  slt   $at, $v0, $v1
/* 0B2220 800B1620 10200018 */  beqz  $at, .L800B1684
/* 0B2224 800B1624 00000000 */   nop   
/* 0B2228 800B1628 90F9000D */  lbu   $t9, 0xd($a3)
/* 0B222C 800B162C 90EA000C */  lbu   $t2, 0xc($a3)
/* 0B2230 800B1630 8C8C0000 */  lw    $t4, ($a0)
/* 0B2234 800B1634 032A5823 */  subu  $t3, $t9, $t2
/* 0B2238 800B1638 016C0019 */  multu $t3, $t4
/* 0B223C 800B163C 00627823 */  subu  $t7, $v1, $v0
/* 0B2240 800B1640 00006812 */  mflo  $t5
/* 0B2244 800B1644 00000000 */  nop   
/* 0B2248 800B1648 00000000 */  nop   
/* 0B224C 800B164C 01AF001A */  div   $zero, $t5, $t7
/* 0B2250 800B1650 15E00002 */  bnez  $t7, .L800B165C
/* 0B2254 800B1654 00000000 */   nop   
/* 0B2258 800B1658 0007000D */  break 7
.L800B165C:
/* 0B225C 800B165C 2401FFFF */  li    $at, -1
/* 0B2260 800B1660 15E10004 */  bne   $t7, $at, .L800B1674
/* 0B2264 800B1664 3C018000 */   lui   $at, 0x8000
/* 0B2268 800B1668 15A10002 */  bne   $t5, $at, .L800B1674
/* 0B226C 800B166C 00000000 */   nop   
/* 0B2270 800B1670 0006000D */  break 6
.L800B1674:
/* 0B2274 800B1674 00007012 */  mflo  $t6
/* 0B2278 800B1678 A60E005E */  sh    $t6, 0x5e($s0)
/* 0B227C 800B167C 10000003 */  b     .L800B168C
/* 0B2280 800B1680 A3A00023 */   sb    $zero, 0x23($sp)
.L800B1684:
/* 0B2284 800B1684 A600005E */  sh    $zero, 0x5e($s0)
/* 0B2288 800B1688 A3A00023 */  sb    $zero, 0x23($sp)
.L800B168C:
/* 0B228C 800B168C 84F80006 */  lh    $t8, 6($a3)
/* 0B2290 800B1690 8602002C */  lh    $v0, 0x2c($s0)
/* 0B2294 800B1694 24010080 */  li    $at, 128
/* 0B2298 800B1698 14410046 */  bne   $v0, $at, .L800B17B4
/* 0B229C 800B169C A618001A */   sh    $t8, 0x1a($s0)
/* 0B22A0 800B16A0 84E40004 */  lh    $a0, 4($a3)
/* 0B22A4 800B16A4 0C01F04B */  jal   func_8007C12C
/* 0B22A8 800B16A8 00002825 */   move  $a1, $zero
/* 0B22AC 800B16AC 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B22B0 800B16B0 1040003D */  beqz  $v0, .L800B17A8
/* 0B22B4 800B16B4 AE020044 */   sw    $v0, 0x44($s0)
/* 0B22B8 800B16B8 8C4A0008 */  lw    $t2, 8($v0)
/* 0B22BC 800B16BC 00000000 */  nop   
/* 0B22C0 800B16C0 8D4B0000 */  lw    $t3, ($t2)
/* 0B22C4 800B16C4 00000000 */  nop   
/* 0B22C8 800B16C8 856C0006 */  lh    $t4, 6($t3)
/* 0B22CC 800B16CC 00000000 */  nop   
/* 0B22D0 800B16D0 318D0004 */  andi  $t5, $t4, 4
/* 0B22D4 800B16D4 11A0000F */  beqz  $t5, .L800B1714
/* 0B22D8 800B16D8 00000000 */   nop   
/* 0B22DC 800B16DC 8E0F0040 */  lw    $t7, 0x40($s0)
/* 0B22E0 800B16E0 00000000 */  nop   
/* 0B22E4 800B16E4 31EE1000 */  andi  $t6, $t7, 0x1000
/* 0B22E8 800B16E8 11C00006 */  beqz  $t6, .L800B1704
/* 0B22EC 800B16EC 00000000 */   nop   
/* 0B22F0 800B16F0 86180006 */  lh    $t8, 6($s0)
/* 0B22F4 800B16F4 00000000 */  nop   
/* 0B22F8 800B16F8 37190100 */  ori   $t9, $t8, 0x100
/* 0B22FC 800B16FC 10000005 */  b     .L800B1714
/* 0B2300 800B1700 A6190006 */   sh    $t9, 6($s0)
.L800B1704:
/* 0B2304 800B1704 860A0006 */  lh    $t2, 6($s0)
/* 0B2308 800B1708 00000000 */  nop   
/* 0B230C 800B170C 354B0080 */  ori   $t3, $t2, 0x80
/* 0B2310 800B1710 A60B0006 */  sh    $t3, 6($s0)
.L800B1714:
/* 0B2314 800B1714 8E2C0000 */  lw    $t4, ($s1)
/* 0B2318 800B1718 00000000 */  nop   
/* 0B231C 800B171C 318D0800 */  andi  $t5, $t4, 0x800
/* 0B2320 800B1720 11A00012 */  beqz  $t5, .L800B176C
/* 0B2324 800B1724 00000000 */   nop   
/* 0B2328 800B1728 8E0F0044 */  lw    $t7, 0x44($s0)
/* 0B232C 800B172C 00002025 */  move  $a0, $zero
/* 0B2330 800B1730 85E50000 */  lh    $a1, ($t7)
/* 0B2334 800B1734 0C01BE53 */  jal   func_8006F94C
/* 0B2338 800B1738 24A5FFFF */   addiu $a1, $a1, -1
/* 0B233C 800B173C 8E180040 */  lw    $t8, 0x40($s0)
/* 0B2340 800B1740 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2344 800B1744 00027200 */  sll   $t6, $v0, 8
/* 0B2348 800B1748 24010002 */  li    $at, 2
/* 0B234C 800B174C 33190003 */  andi  $t9, $t8, 3
/* 0B2350 800B1750 17210063 */  bne   $t9, $at, .L800B18E0
/* 0B2354 800B1754 A60E0018 */   sh    $t6, 0x18($s0)
/* 0B2358 800B1758 860A0018 */  lh    $t2, 0x18($s0)
/* 0B235C 800B175C 00000000 */  nop   
/* 0B2360 800B1760 354B00FF */  ori   $t3, $t2, 0xff
/* 0B2364 800B1764 1000005E */  b     .L800B18E0
/* 0B2368 800B1768 A60B0018 */   sh    $t3, 0x18($s0)
.L800B176C:
/* 0B236C 800B176C 8E0C0040 */  lw    $t4, 0x40($s0)
/* 0B2370 800B1770 24010002 */  li    $at, 2
/* 0B2374 800B1774 318D0003 */  andi  $t5, $t4, 3
/* 0B2378 800B1778 15A10009 */  bne   $t5, $at, .L800B17A0
/* 0B237C 800B177C 00000000 */   nop   
/* 0B2380 800B1780 8E0F0044 */  lw    $t7, 0x44($s0)
/* 0B2384 800B1784 00000000 */  nop   
/* 0B2388 800B1788 85EE0000 */  lh    $t6, ($t7)
/* 0B238C 800B178C 00000000 */  nop   
/* 0B2390 800B1790 000EC200 */  sll   $t8, $t6, 8
/* 0B2394 800B1794 2719FFFF */  addiu $t9, $t8, -1
/* 0B2398 800B1798 10000051 */  b     .L800B18E0
/* 0B239C 800B179C A6190018 */   sh    $t9, 0x18($s0)
.L800B17A0:
/* 0B23A0 800B17A0 1000004F */  b     .L800B18E0
/* 0B23A4 800B17A4 A6000018 */   sh    $zero, 0x18($s0)
.L800B17A8:
/* 0B23A8 800B17A8 240A0001 */  li    $t2, 1
/* 0B23AC 800B17AC 1000004C */  b     .L800B18E0
/* 0B23B0 800B17B0 A3AA0023 */   sb    $t2, 0x23($sp)
.L800B17B4:
/* 0B23B4 800B17B4 24010002 */  li    $at, 2
/* 0B23B8 800B17B8 10410003 */  beq   $v0, $at, .L800B17C8
/* 0B23BC 800B17BC 24010001 */   li    $at, 1
/* 0B23C0 800B17C0 14410048 */  bne   $v0, $at, .L800B18E4
/* 0B23C4 800B17C4 83AB0023 */   lb    $t3, 0x23($sp)
.L800B17C8:
/* 0B23C8 800B17C8 8E030044 */  lw    $v1, 0x44($s0)
/* 0B23CC 800B17CC 00000000 */  nop   
/* 0B23D0 800B17D0 10600044 */  beqz  $v1, .L800B18E4
/* 0B23D4 800B17D4 83AB0023 */   lb    $t3, 0x23($sp)
/* 0B23D8 800B17D8 84E40004 */  lh    $a0, 4($a3)
/* 0B23DC 800B17DC 0C01EB9D */  jal   func_8007AE74
/* 0B23E0 800B17E0 AFA30030 */   sw    $v1, 0x30($sp)
/* 0B23E4 800B17E4 8FA30030 */  lw    $v1, 0x30($sp)
/* 0B23E8 800B17E8 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B23EC 800B17EC 1040003A */  beqz  $v0, .L800B18D8
/* 0B23F0 800B17F0 AC620000 */   sw    $v0, ($v1)
/* 0B23F4 800B17F4 844C0006 */  lh    $t4, 6($v0)
/* 0B23F8 800B17F8 00000000 */  nop   
/* 0B23FC 800B17FC 318D0004 */  andi  $t5, $t4, 4
/* 0B2400 800B1800 11A0000F */  beqz  $t5, .L800B1840
/* 0B2404 800B1804 00000000 */   nop   
/* 0B2408 800B1808 8E0F0040 */  lw    $t7, 0x40($s0)
/* 0B240C 800B180C 00000000 */  nop   
/* 0B2410 800B1810 31EE1000 */  andi  $t6, $t7, 0x1000
/* 0B2414 800B1814 11C00006 */  beqz  $t6, .L800B1830
/* 0B2418 800B1818 00000000 */   nop   
/* 0B241C 800B181C 86180006 */  lh    $t8, 6($s0)
/* 0B2420 800B1820 00000000 */  nop   
/* 0B2424 800B1824 37190100 */  ori   $t9, $t8, 0x100
/* 0B2428 800B1828 10000005 */  b     .L800B1840
/* 0B242C 800B182C A6190006 */   sh    $t9, 6($s0)
.L800B1830:
/* 0B2430 800B1830 860A0006 */  lh    $t2, 6($s0)
/* 0B2434 800B1834 00000000 */  nop   
/* 0B2438 800B1838 354B0080 */  ori   $t3, $t2, 0x80
/* 0B243C 800B183C A60B0006 */  sh    $t3, 6($s0)
.L800B1840:
/* 0B2440 800B1840 8E2C0000 */  lw    $t4, ($s1)
/* 0B2444 800B1844 00000000 */  nop   
/* 0B2448 800B1848 318D0800 */  andi  $t5, $t4, 0x800
/* 0B244C 800B184C 11A00014 */  beqz  $t5, .L800B18A0
/* 0B2450 800B1850 00000000 */   nop   
/* 0B2454 800B1854 8C6F0000 */  lw    $t7, ($v1)
/* 0B2458 800B1858 00002025 */  move  $a0, $zero
/* 0B245C 800B185C 95E50012 */  lhu   $a1, 0x12($t7)
/* 0B2460 800B1860 00000000 */  nop   
/* 0B2464 800B1864 00057203 */  sra   $t6, $a1, 8
/* 0B2468 800B1868 0C01BE53 */  jal   func_8006F94C
/* 0B246C 800B186C 25C5FFFF */   addiu $a1, $t6, -1
/* 0B2470 800B1870 8E190040 */  lw    $t9, 0x40($s0)
/* 0B2474 800B1874 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2478 800B1878 0002C200 */  sll   $t8, $v0, 8
/* 0B247C 800B187C 24010002 */  li    $at, 2
/* 0B2480 800B1880 332A0003 */  andi  $t2, $t9, 3
/* 0B2484 800B1884 15410016 */  bne   $t2, $at, .L800B18E0
/* 0B2488 800B1888 A6180018 */   sh    $t8, 0x18($s0)
/* 0B248C 800B188C 860B0018 */  lh    $t3, 0x18($s0)
/* 0B2490 800B1890 00000000 */  nop   
/* 0B2494 800B1894 356C00FF */  ori   $t4, $t3, 0xff
/* 0B2498 800B1898 10000011 */  b     .L800B18E0
/* 0B249C 800B189C A60C0018 */   sh    $t4, 0x18($s0)
.L800B18A0:
/* 0B24A0 800B18A0 8E0D0040 */  lw    $t5, 0x40($s0)
/* 0B24A4 800B18A4 24010002 */  li    $at, 2
/* 0B24A8 800B18A8 31AF0003 */  andi  $t7, $t5, 3
/* 0B24AC 800B18AC 15E10008 */  bne   $t7, $at, .L800B18D0
/* 0B24B0 800B18B0 00000000 */   nop   
/* 0B24B4 800B18B4 8C6E0000 */  lw    $t6, ($v1)
/* 0B24B8 800B18B8 00000000 */  nop   
/* 0B24BC 800B18BC 95D80012 */  lhu   $t8, 0x12($t6)
/* 0B24C0 800B18C0 00000000 */  nop   
/* 0B24C4 800B18C4 2719FFFF */  addiu $t9, $t8, -1
/* 0B24C8 800B18C8 10000005 */  b     .L800B18E0
/* 0B24CC 800B18CC A6190018 */   sh    $t9, 0x18($s0)
.L800B18D0:
/* 0B24D0 800B18D0 10000003 */  b     .L800B18E0
/* 0B24D4 800B18D4 A6000018 */   sh    $zero, 0x18($s0)
.L800B18D8:
/* 0B24D8 800B18D8 240A0001 */  li    $t2, 1
/* 0B24DC 800B18DC A3AA0023 */  sb    $t2, 0x23($sp)
.L800B18E0:
/* 0B24E0 800B18E0 83AB0023 */  lb    $t3, 0x23($sp)
.L800B18E4:
/* 0B24E4 800B18E4 00000000 */  nop   
/* 0B24E8 800B18E8 15600012 */  bnez  $t3, .L800B1934
/* 0B24EC 800B18EC 8FA50040 */   lw    $a1, 0x40($sp)
/* 0B24F0 800B18F0 8602002C */  lh    $v0, 0x2c($s0)
/* 0B24F4 800B18F4 24010001 */  li    $at, 1
/* 0B24F8 800B18F8 14410007 */  bne   $v0, $at, .L800B1918
/* 0B24FC 800B18FC 24010002 */   li    $at, 2
/* 0B2500 800B1900 0C02BC29 */  jal   func_800AF0A4
/* 0B2504 800B1904 02002025 */   move  $a0, $s0
/* 0B2508 800B1908 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B250C 800B190C 8602002C */  lh    $v0, 0x2c($s0)
/* 0B2510 800B1910 00000000 */  nop   
/* 0B2514 800B1914 24010002 */  li    $at, 2
.L800B1918:
/* 0B2518 800B1918 14410006 */  bne   $v0, $at, .L800B1934
/* 0B251C 800B191C 8FA50040 */   lw    $a1, 0x40($sp)
/* 0B2520 800B1920 0C02BC3C */  jal   func_800AF0F0
/* 0B2524 800B1924 02002025 */   move  $a0, $s0
/* 0B2528 800B1928 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B252C 800B192C 00000000 */  nop   
/* 0B2530 800B1930 8FA50040 */  lw    $a1, 0x40($sp)
.L800B1934:
/* 0B2534 800B1934 02002025 */  move  $a0, $s0
/* 0B2538 800B1938 0C02C0F0 */  jal   func_800B03C0
/* 0B253C 800B193C 02203825 */   move  $a3, $s1
/* 0B2540 800B1940 8E2C0000 */  lw    $t4, ($s1)
/* 0B2544 800B1944 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2548 800B1948 318D0080 */  andi  $t5, $t4, 0x80
/* 0B254C 800B194C 11A0000B */  beqz  $t5, .L800B197C
/* 0B2550 800B1950 8FB90040 */   lw    $t9, 0x40($sp)
/* 0B2554 800B1954 862F0044 */  lh    $t7, 0x44($s1)
/* 0B2558 800B1958 00000000 */  nop   
/* 0B255C 800B195C A60F0000 */  sh    $t7, ($s0)
/* 0B2560 800B1960 862E0046 */  lh    $t6, 0x46($s1)
/* 0B2564 800B1964 00000000 */  nop   
/* 0B2568 800B1968 A60E0002 */  sh    $t6, 2($s0)
/* 0B256C 800B196C 86380048 */  lh    $t8, 0x48($s1)
/* 0B2570 800B1970 10000013 */  b     .L800B19C0
/* 0B2574 800B1974 A6180004 */   sh    $t8, 4($s0)
/* 0B2578 800B1978 8FB90040 */  lw    $t9, 0x40($sp)
.L800B197C:
/* 0B257C 800B197C 862B0044 */  lh    $t3, 0x44($s1)
/* 0B2580 800B1980 872A0000 */  lh    $t2, ($t9)
/* 0B2584 800B1984 00000000 */  nop   
/* 0B2588 800B1988 014B6021 */  addu  $t4, $t2, $t3
/* 0B258C 800B198C A60C0000 */  sh    $t4, ($s0)
/* 0B2590 800B1990 8FAD0040 */  lw    $t5, 0x40($sp)
/* 0B2594 800B1994 862E0046 */  lh    $t6, 0x46($s1)
/* 0B2598 800B1998 85AF0002 */  lh    $t7, 2($t5)
/* 0B259C 800B199C 00000000 */  nop   
/* 0B25A0 800B19A0 01EEC021 */  addu  $t8, $t7, $t6
/* 0B25A4 800B19A4 A6180002 */  sh    $t8, 2($s0)
/* 0B25A8 800B19A8 8FB90040 */  lw    $t9, 0x40($sp)
/* 0B25AC 800B19AC 862B0048 */  lh    $t3, 0x48($s1)
/* 0B25B0 800B19B0 872A0004 */  lh    $t2, 4($t9)
/* 0B25B4 800B19B4 00000000 */  nop   
/* 0B25B8 800B19B8 014B6021 */  addu  $t4, $t2, $t3
/* 0B25BC 800B19BC A60C0004 */  sh    $t4, 4($s0)
.L800B19C0:
/* 0B25C0 800B19C0 8E23005C */  lw    $v1, 0x5c($s1)
/* 0B25C4 800B19C4 00000000 */  nop   
/* 0B25C8 800B19C8 306D3800 */  andi  $t5, $v1, 0x3800
/* 0B25CC 800B19CC 11A00023 */  beqz  $t5, .L800B1A5C
/* 0B25D0 800B19D0 01A01825 */   move  $v1, $t5
/* 0B25D4 800B19D4 31AF0800 */  andi  $t7, $t5, 0x800
/* 0B25D8 800B19D8 11E0000B */  beqz  $t7, .L800B1A08
/* 0B25DC 800B19DC 30791000 */   andi  $t9, $v1, 0x1000
/* 0B25E0 800B19E0 86250080 */  lh    $a1, 0x80($s1)
/* 0B25E4 800B19E4 AFAD003C */  sw    $t5, 0x3c($sp)
/* 0B25E8 800B19E8 0C01BE53 */  jal   func_8006F94C
/* 0B25EC 800B19EC 00052023 */   negu  $a0, $a1
/* 0B25F0 800B19F0 860E0000 */  lh    $t6, ($s0)
/* 0B25F4 800B19F4 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B25F8 800B19F8 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B25FC 800B19FC 01C2C021 */  addu  $t8, $t6, $v0
/* 0B2600 800B1A00 A6180000 */  sh    $t8, ($s0)
/* 0B2604 800B1A04 30791000 */  andi  $t9, $v1, 0x1000
.L800B1A08:
/* 0B2608 800B1A08 1320000B */  beqz  $t9, .L800B1A38
/* 0B260C 800B1A0C 306C2000 */   andi  $t4, $v1, 0x2000
/* 0B2610 800B1A10 86250082 */  lh    $a1, 0x82($s1)
/* 0B2614 800B1A14 AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B2618 800B1A18 0C01BE53 */  jal   func_8006F94C
/* 0B261C 800B1A1C 00052023 */   negu  $a0, $a1
/* 0B2620 800B1A20 860A0002 */  lh    $t2, 2($s0)
/* 0B2624 800B1A24 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B2628 800B1A28 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B262C 800B1A2C 01425821 */  addu  $t3, $t2, $v0
/* 0B2630 800B1A30 A60B0002 */  sh    $t3, 2($s0)
/* 0B2634 800B1A34 306C2000 */  andi  $t4, $v1, 0x2000
.L800B1A38:
/* 0B2638 800B1A38 11800008 */  beqz  $t4, .L800B1A5C
/* 0B263C 800B1A3C 00000000 */   nop   
/* 0B2640 800B1A40 86250084 */  lh    $a1, 0x84($s1)
/* 0B2644 800B1A44 0C01BE53 */  jal   func_8006F94C
/* 0B2648 800B1A48 00052023 */   negu  $a0, $a1
/* 0B264C 800B1A4C 860D0004 */  lh    $t5, 4($s0)
/* 0B2650 800B1A50 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2654 800B1A54 01A27821 */  addu  $t7, $t5, $v0
/* 0B2658 800B1A58 A60F0004 */  sh    $t7, 4($s0)
.L800B1A5C:
/* 0B265C 800B1A5C 862E004A */  lh    $t6, 0x4a($s1)
/* 0B2660 800B1A60 3C010001 */  lui   $at, (0x0001C000 >> 16) # lui $at, 1
/* 0B2664 800B1A64 A60E0062 */  sh    $t6, 0x62($s0)
/* 0B2668 800B1A68 8638004C */  lh    $t8, 0x4c($s1)
/* 0B266C 800B1A6C 3421C000 */  ori   $at, (0x0001C000 & 0xFFFF) # ori $at, $at, 0xc000
/* 0B2670 800B1A70 A6180064 */  sh    $t8, 0x64($s0)
/* 0B2674 800B1A74 8639004E */  lh    $t9, 0x4e($s1)
/* 0B2678 800B1A78 00000000 */  nop   
/* 0B267C 800B1A7C A6190066 */  sh    $t9, 0x66($s0)
/* 0B2680 800B1A80 8E23005C */  lw    $v1, 0x5c($s1)
/* 0B2684 800B1A84 00000000 */  nop   
/* 0B2688 800B1A88 00615024 */  and   $t2, $v1, $at
/* 0B268C 800B1A8C 11400023 */  beqz  $t2, .L800B1B1C
/* 0B2690 800B1A90 01401825 */   move  $v1, $t2
/* 0B2694 800B1A94 314B4000 */  andi  $t3, $t2, 0x4000
/* 0B2698 800B1A98 1160000B */  beqz  $t3, .L800B1AC8
/* 0B269C 800B1A9C 306F8000 */   andi  $t7, $v1, 0x8000
/* 0B26A0 800B1AA0 86250086 */  lh    $a1, 0x86($s1)
/* 0B26A4 800B1AA4 AFAA003C */  sw    $t2, 0x3c($sp)
/* 0B26A8 800B1AA8 0C01BE53 */  jal   func_8006F94C
/* 0B26AC 800B1AAC 00052023 */   negu  $a0, $a1
/* 0B26B0 800B1AB0 860C0062 */  lh    $t4, 0x62($s0)
/* 0B26B4 800B1AB4 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B26B8 800B1AB8 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B26BC 800B1ABC 01826821 */  addu  $t5, $t4, $v0
/* 0B26C0 800B1AC0 A60D0062 */  sh    $t5, 0x62($s0)
/* 0B26C4 800B1AC4 306F8000 */  andi  $t7, $v1, 0x8000
.L800B1AC8:
/* 0B26C8 800B1AC8 11E0000B */  beqz  $t7, .L800B1AF8
/* 0B26CC 800B1ACC 0003CBC0 */   sll   $t9, $v1, 0xf
/* 0B26D0 800B1AD0 86250088 */  lh    $a1, 0x88($s1)
/* 0B26D4 800B1AD4 AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B26D8 800B1AD8 0C01BE53 */  jal   func_8006F94C
/* 0B26DC 800B1ADC 00052023 */   negu  $a0, $a1
/* 0B26E0 800B1AE0 860E0064 */  lh    $t6, 0x64($s0)
/* 0B26E4 800B1AE4 8FA3003C */  lw    $v1, 0x3c($sp)
/* 0B26E8 800B1AE8 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B26EC 800B1AEC 01C2C021 */  addu  $t8, $t6, $v0
/* 0B26F0 800B1AF0 A6180064 */  sh    $t8, 0x64($s0)
/* 0B26F4 800B1AF4 0003CBC0 */  sll   $t9, $v1, 0xf
.L800B1AF8:
/* 0B26F8 800B1AF8 07210009 */  bgez  $t9, .L800B1B20
/* 0B26FC 800B1AFC 8FA50040 */   lw    $a1, 0x40($sp)
/* 0B2700 800B1B00 8625008A */  lh    $a1, 0x8a($s1)
/* 0B2704 800B1B04 0C01BE53 */  jal   func_8006F94C
/* 0B2708 800B1B08 00052023 */   negu  $a0, $a1
/* 0B270C 800B1B0C 860A0066 */  lh    $t2, 0x66($s0)
/* 0B2710 800B1B10 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2714 800B1B14 01425821 */  addu  $t3, $t2, $v0
/* 0B2718 800B1B18 A60B0066 */  sh    $t3, 0x66($s0)
.L800B1B1C:
/* 0B271C 800B1B1C 8FA50040 */  lw    $a1, 0x40($sp)
.L800B1B20:
/* 0B2720 800B1B20 02002025 */  move  $a0, $s0
/* 0B2724 800B1B24 0C02C004 */  jal   func_800B0010
/* 0B2728 800B1B28 02203825 */   move  $a3, $s1
/* 0B272C 800B1B2C 8E0C0040 */  lw    $t4, 0x40($s0)
/* 0B2730 800B1B30 3C01800E */  lui   $at, 0x800e
/* 0B2734 800B1B34 000C6903 */  sra   $t5, $t4, 4
/* 0B2738 800B1B38 31AF0007 */  andi  $t7, $t5, 7
/* 0B273C 800B1B3C 000F7080 */  sll   $t6, $t7, 2
/* 0B2740 800B1B40 002E0821 */  addu  $at, $at, $t6
/* 0B2744 800B1B44 C4242E2C */  lwc1  $f4, 0x2e2c($at)
/* 0B2748 800B1B48 92180039 */  lbu   $t8, 0x39($s0)
/* 0B274C 800B1B4C 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2750 800B1B50 24010005 */  li    $at, 5
/* 0B2754 800B1B54 1701000D */  bne   $t8, $at, .L800B1B8C
/* 0B2758 800B1B58 E6040068 */   swc1  $f4, 0x68($s0)
/* 0B275C 800B1B5C C600001C */  lwc1  $f0, 0x1c($s0)
/* 0B2760 800B1B60 C6020020 */  lwc1  $f2, 0x20($s0)
/* 0B2764 800B1B64 46000182 */  mul.s $f6, $f0, $f0
/* 0B2768 800B1B68 C60E0024 */  lwc1  $f14, 0x24($s0)
/* 0B276C 800B1B6C 46021482 */  mul.s $f18, $f2, $f2
/* 0B2770 800B1B70 00000000 */  nop   
/* 0B2774 800B1B74 460E7282 */  mul.s $f10, $f14, $f14
/* 0B2778 800B1B78 46123200 */  add.s $f8, $f6, $f18
/* 0B277C 800B1B7C 0C0326B4 */  jal   sqrtf
/* 0B2780 800B1B80 460A4300 */   add.s $f12, $f8, $f10
/* 0B2784 800B1B84 8FA60044 */  lw    $a2, 0x44($sp)
/* 0B2788 800B1B88 E6000058 */  swc1  $f0, 0x58($s0)
.L800B1B8C:
/* 0B278C 800B1B8C 8E390000 */  lw    $t9, ($s1)
/* 0B2790 800B1B90 00000000 */  nop   
/* 0B2794 800B1B94 332A0002 */  andi  $t2, $t9, 2
/* 0B2798 800B1B98 1140001B */  beqz  $t2, .L800B1C08
/* 0B279C 800B1B9C 00000000 */   nop   
/* 0B27A0 800B1BA0 90CB0006 */  lbu   $t3, 6($a2)
/* 0B27A4 800B1BA4 00000000 */  nop   
/* 0B27A8 800B1BA8 256C0001 */  addiu $t4, $t3, 1
/* 0B27AC 800B1BAC A0CC0006 */  sb    $t4, 6($a2)
/* 0B27B0 800B1BB0 862D001A */  lh    $t5, 0x1a($s1)
/* 0B27B4 800B1BB4 318200FF */  andi  $v0, $t4, 0xff
/* 0B27B8 800B1BB8 004D082A */  slt   $at, $v0, $t5
/* 0B27BC 800B1BBC 14200012 */  bnez  $at, .L800B1C08
/* 0B27C0 800B1BC0 00000000 */   nop   
/* 0B27C4 800B1BC4 84CF000C */  lh    $t7, 0xc($a2)
/* 0B27C8 800B1BC8 862E001C */  lh    $t6, 0x1c($s1)
/* 0B27CC 800B1BCC 84D9000E */  lh    $t9, 0xe($a2)
/* 0B27D0 800B1BD0 01EEC021 */  addu  $t8, $t7, $t6
/* 0B27D4 800B1BD4 A4D8000C */  sh    $t8, 0xc($a2)
/* 0B27D8 800B1BD8 862A001E */  lh    $t2, 0x1e($s1)
/* 0B27DC 800B1BDC 84CC0010 */  lh    $t4, 0x10($a2)
/* 0B27E0 800B1BE0 032A5821 */  addu  $t3, $t9, $t2
/* 0B27E4 800B1BE4 A4CB000E */  sh    $t3, 0xe($a2)
/* 0B27E8 800B1BE8 862D0018 */  lh    $t5, 0x18($s1)
/* 0B27EC 800B1BEC 00000000 */  nop   
/* 0B27F0 800B1BF0 018D7821 */  addu  $t7, $t4, $t5
/* 0B27F4 800B1BF4 A4CF0010 */  sh    $t7, 0x10($a2)
/* 0B27F8 800B1BF8 862E001A */  lh    $t6, 0x1a($s1)
/* 0B27FC 800B1BFC 00000000 */  nop   
/* 0B2800 800B1C00 004EC023 */  subu  $t8, $v0, $t6
/* 0B2804 800B1C04 A0D80006 */  sb    $t8, 6($a2)
.L800B1C08:
/* 0B2808 800B1C08 8E390000 */  lw    $t9, ($s1)
/* 0B280C 800B1C0C 00000000 */  nop   
/* 0B2810 800B1C10 332A0008 */  andi  $t2, $t9, 8
/* 0B2814 800B1C14 1140001B */  beqz  $t2, .L800B1C84
/* 0B2818 800B1C18 00000000 */   nop   
/* 0B281C 800B1C1C 90CB0007 */  lbu   $t3, 7($a2)
/* 0B2820 800B1C20 00000000 */  nop   
/* 0B2824 800B1C24 256C0001 */  addiu $t4, $t3, 1
/* 0B2828 800B1C28 A0CC0007 */  sb    $t4, 7($a2)
/* 0B282C 800B1C2C 862D0028 */  lh    $t5, 0x28($s1)
/* 0B2830 800B1C30 318200FF */  andi  $v0, $t4, 0xff
/* 0B2834 800B1C34 004D082A */  slt   $at, $v0, $t5
/* 0B2838 800B1C38 14200012 */  bnez  $at, .L800B1C84
/* 0B283C 800B1C3C 00000000 */   nop   
/* 0B2840 800B1C40 84CF0012 */  lh    $t7, 0x12($a2)
/* 0B2844 800B1C44 862E002A */  lh    $t6, 0x2a($s1)
/* 0B2848 800B1C48 84D90014 */  lh    $t9, 0x14($a2)
/* 0B284C 800B1C4C 01EEC021 */  addu  $t8, $t7, $t6
/* 0B2850 800B1C50 A4D80012 */  sh    $t8, 0x12($a2)
/* 0B2854 800B1C54 862A002C */  lh    $t2, 0x2c($s1)
/* 0B2858 800B1C58 84CC0016 */  lh    $t4, 0x16($a2)
/* 0B285C 800B1C5C 032A5821 */  addu  $t3, $t9, $t2
/* 0B2860 800B1C60 A4CB0014 */  sh    $t3, 0x14($a2)
/* 0B2864 800B1C64 862D002E */  lh    $t5, 0x2e($s1)
/* 0B2868 800B1C68 00000000 */  nop   
/* 0B286C 800B1C6C 018D7821 */  addu  $t7, $t4, $t5
/* 0B2870 800B1C70 A4CF0016 */  sh    $t7, 0x16($a2)
/* 0B2874 800B1C74 862E0028 */  lh    $t6, 0x28($s1)
/* 0B2878 800B1C78 00000000 */  nop   
/* 0B287C 800B1C7C 004EC023 */  subu  $t8, $v0, $t6
/* 0B2880 800B1C80 A0D80007 */  sb    $t8, 7($a2)
.L800B1C84:
/* 0B2884 800B1C84 8E190044 */  lw    $t9, 0x44($s0)
/* 0B2888 800B1C88 02001025 */  move  $v0, $s0
/* 0B288C 800B1C8C 17200005 */  bnez  $t9, .L800B1CA4
/* 0B2890 800B1C90 00000000 */   nop   
/* 0B2894 800B1C94 0C02C810 */  jal   func_800B2040
/* 0B2898 800B1C98 02002025 */   move  $a0, $s0
/* 0B289C 800B1C9C 10000001 */  b     .L800B1CA4
/* 0B28A0 800B1CA0 00001025 */   move  $v0, $zero
.L800B1CA4:
/* 0B28A4 800B1CA4 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B28A8 800B1CA8 8FB00014 */  lw    $s0, 0x14($sp)
/* 0B28AC 800B1CAC 8FB10018 */  lw    $s1, 0x18($sp)
/* 0B28B0 800B1CB0 03E00008 */  jr    $ra
/* 0B28B4 800B1CB4 27BD0040 */   addiu $sp, $sp, 0x40

glabel func_800B1CB8
/* 0B28B8 800B1CB8 24050001 */  li    $a1, 1
/* 0B28BC 800B1CBC 00001825 */  move  $v1, $zero
/* 0B28C0 800B1CC0 10850036 */  beq   $a0, $a1, .L800B1D9C
/* 0B28C4 800B1CC4 00001025 */   move  $v0, $zero
/* 0B28C8 800B1CC8 24070002 */  li    $a3, 2
/* 0B28CC 800B1CCC 1087005D */  beq   $a0, $a3, .L800B1E44
/* 0B28D0 800B1CD0 3C08800E */   lui   $t0, 0x800e
/* 0B28D4 800B1CD4 24070003 */  li    $a3, 3
/* 0B28D8 800B1CD8 10870083 */  beq   $a0, $a3, .L800B1EE8
/* 0B28DC 800B1CDC 3C08800E */   lui   $t0, 0x800e
/* 0B28E0 800B1CE0 24060004 */  li    $a2, 4
/* 0B28E4 800B1CE4 108600A9 */  beq   $a0, $a2, .L800B1F8C
/* 0B28E8 800B1CE8 3C07800E */   lui   $a3, 0x800e
/* 0B28EC 800B1CEC 24070080 */  li    $a3, 128
/* 0B28F0 800B1CF0 148700CE */  bne   $a0, $a3, .L800B202C
/* 0B28F4 800B1CF4 3C08800E */   lui   $t0, %hi(D_800E2CC0) # $t0, 0x800e
/* 0B28F8 800B1CF8 25082CC0 */  addiu $t0, %lo(D_800E2CC0) # addiu $t0, $t0, 0x2cc0
/* 0B28FC 800B1CFC 8D040000 */  lw    $a0, ($t0)
/* 0B2900 800B1D00 3C09800E */  lui   $t1, %hi(D_800E2CB8) # $t1, 0x800e
/* 0B2904 800B1D04 108000C9 */  beqz  $a0, .L800B202C
/* 0B2908 800B1D08 25292CB8 */   addiu $t1, %lo(D_800E2CB8) # addiu $t1, $t1, 0x2cb8
/* 0B290C 800B1D0C 3C0F800E */  lui   $t7, %hi(D_800E2E54) # $t7, 0x800e
/* 0B2910 800B1D10 8DEF2E54 */  lw    $t7, %lo(D_800E2E54)($t7)
/* 0B2914 800B1D14 8D2E0000 */  lw    $t6, ($t1)
/* 0B2918 800B1D18 25F8FFFF */  addiu $t8, $t7, -1
/* 0B291C 800B1D1C 01D8082A */  slt   $at, $t6, $t8
/* 0B2920 800B1D20 14200009 */  bnez  $at, .L800B1D48
/* 0B2924 800B1D24 00000000 */   nop   
/* 0B2928 800B1D28 3C02800E */  lui   $v0, %hi(D_800E2CBC) # $v0, 0x800e
/* 0B292C 800B1D2C 24422CBC */  addiu $v0, %lo(D_800E2CBC) # addiu $v0, $v0, 0x2cbc
/* 0B2930 800B1D30 8C590000 */  lw    $t9, ($v0)
/* 0B2934 800B1D34 00000000 */  nop   
/* 0B2938 800B1D38 172000BC */  bnez  $t9, .L800B202C
/* 0B293C 800B1D3C 00000000 */   nop   
/* 0B2940 800B1D40 100000BA */  b     .L800B202C
/* 0B2944 800B1D44 AC450000 */   sw    $a1, ($v0)
.L800B1D48:
/* 0B2948 800B1D48 848A002C */  lh    $t2, 0x2c($a0)
/* 0B294C 800B1D4C 000258C0 */  sll   $t3, $v0, 3
/* 0B2950 800B1D50 11400007 */  beqz  $t2, .L800B1D70
/* 0B2954 800B1D54 01625823 */   subu  $t3, $t3, $v0
/* 0B2958 800B1D58 000B5900 */  sll   $t3, $t3, 4
/* 0B295C 800B1D5C 008B1821 */  addu  $v1, $a0, $t3
.L800B1D60:
/* 0B2960 800B1D60 846C009C */  lh    $t4, 0x9c($v1)
/* 0B2964 800B1D64 24420001 */  addiu $v0, $v0, 1
/* 0B2968 800B1D68 1580FFFD */  bnez  $t4, .L800B1D60
/* 0B296C 800B1D6C 24630070 */   addiu $v1, $v1, 0x70
.L800B1D70:
/* 0B2970 800B1D70 000230C0 */  sll   $a2, $v0, 3
/* 0B2974 800B1D74 00C23023 */  subu  $a2, $a2, $v0
/* 0B2978 800B1D78 00063100 */  sll   $a2, $a2, 4
/* 0B297C 800B1D7C 00866821 */  addu  $t5, $a0, $a2
/* 0B2980 800B1D80 A5A7002C */  sh    $a3, 0x2c($t5)
/* 0B2984 800B1D84 8D2F0000 */  lw    $t7, ($t1)
/* 0B2988 800B1D88 8D180000 */  lw    $t8, ($t0)
/* 0B298C 800B1D8C 25EE0001 */  addiu $t6, $t7, 1
/* 0B2990 800B1D90 AD2E0000 */  sw    $t6, ($t1)
/* 0B2994 800B1D94 100000A5 */  b     .L800B202C
/* 0B2998 800B1D98 00D81821 */   addu  $v1, $a2, $t8
.L800B1D9C:
/* 0B299C 800B1D9C 3C07800E */  lui   $a3, %hi(D_800E2CA8) # $a3, 0x800e
/* 0B29A0 800B1DA0 24E72CA8 */  addiu $a3, %lo(D_800E2CA8) # addiu $a3, $a3, 0x2ca8
/* 0B29A4 800B1DA4 8CE40000 */  lw    $a0, ($a3)
/* 0B29A8 800B1DA8 3C08800E */  lui   $t0, %hi(D_800E2CA0) # $t0, 0x800e
/* 0B29AC 800B1DAC 1080009F */  beqz  $a0, .L800B202C
/* 0B29B0 800B1DB0 25082CA0 */   addiu $t0, %lo(D_800E2CA0) # addiu $t0, $t0, 0x2ca0
/* 0B29B4 800B1DB4 3C0A800E */  lui   $t2, %hi(D_800E2E4C) # $t2, 0x800e
/* 0B29B8 800B1DB8 8D4A2E4C */  lw    $t2, %lo(D_800E2E4C)($t2)
/* 0B29BC 800B1DBC 8D190000 */  lw    $t9, ($t0)
/* 0B29C0 800B1DC0 254BFFFF */  addiu $t3, $t2, -1
/* 0B29C4 800B1DC4 032B082A */  slt   $at, $t9, $t3
/* 0B29C8 800B1DC8 14200009 */  bnez  $at, .L800B1DF0
/* 0B29CC 800B1DCC 00000000 */   nop   
/* 0B29D0 800B1DD0 3C02800E */  lui   $v0, %hi(D_800E2CA4) # $v0, 0x800e
/* 0B29D4 800B1DD4 24422CA4 */  addiu $v0, %lo(D_800E2CA4) # addiu $v0, $v0, 0x2ca4
/* 0B29D8 800B1DD8 8C4C0000 */  lw    $t4, ($v0)
/* 0B29DC 800B1DDC 00000000 */  nop   
/* 0B29E0 800B1DE0 15800092 */  bnez  $t4, .L800B202C
/* 0B29E4 800B1DE4 00000000 */   nop   
/* 0B29E8 800B1DE8 10000090 */  b     .L800B202C
/* 0B29EC 800B1DEC AC450000 */   sw    $a1, ($v0)
.L800B1DF0:
/* 0B29F0 800B1DF0 848D002C */  lh    $t5, 0x2c($a0)
/* 0B29F4 800B1DF4 000278C0 */  sll   $t7, $v0, 3
/* 0B29F8 800B1DF8 11A00007 */  beqz  $t5, .L800B1E18
/* 0B29FC 800B1DFC 01E27823 */   subu  $t7, $t7, $v0
/* 0B2A00 800B1E00 000F7900 */  sll   $t7, $t7, 4
/* 0B2A04 800B1E04 008F1821 */  addu  $v1, $a0, $t7
.L800B1E08:
/* 0B2A08 800B1E08 846E009C */  lh    $t6, 0x9c($v1)
/* 0B2A0C 800B1E0C 24420001 */  addiu $v0, $v0, 1
/* 0B2A10 800B1E10 15C0FFFD */  bnez  $t6, .L800B1E08
/* 0B2A14 800B1E14 24630070 */   addiu $v1, $v1, 0x70
.L800B1E18:
/* 0B2A18 800B1E18 000230C0 */  sll   $a2, $v0, 3
/* 0B2A1C 800B1E1C 00C23023 */  subu  $a2, $a2, $v0
/* 0B2A20 800B1E20 00063100 */  sll   $a2, $a2, 4
/* 0B2A24 800B1E24 0086C021 */  addu  $t8, $a0, $a2
/* 0B2A28 800B1E28 A705002C */  sh    $a1, 0x2c($t8)
/* 0B2A2C 800B1E2C 8D0A0000 */  lw    $t2, ($t0)
/* 0B2A30 800B1E30 8CEB0000 */  lw    $t3, ($a3)
/* 0B2A34 800B1E34 25590001 */  addiu $t9, $t2, 1
/* 0B2A38 800B1E38 AD190000 */  sw    $t9, ($t0)
/* 0B2A3C 800B1E3C 1000007B */  b     .L800B202C
/* 0B2A40 800B1E40 00CB1821 */   addu  $v1, $a2, $t3
.L800B1E44:
/* 0B2A44 800B1E44 25082CB4 */  addiu $t0, $t0, 0x2cb4
/* 0B2A48 800B1E48 8D040000 */  lw    $a0, ($t0)
/* 0B2A4C 800B1E4C 3C09800E */  lui   $t1, %hi(D_800E2CAC) # $t1, 0x800e
/* 0B2A50 800B1E50 10800076 */  beqz  $a0, .L800B202C
/* 0B2A54 800B1E54 25292CAC */   addiu $t1, %lo(D_800E2CAC) # addiu $t1, $t1, 0x2cac
/* 0B2A58 800B1E58 3C0D800E */  lui   $t5, %hi(D_800E2E50) # $t5, 0x800e
/* 0B2A5C 800B1E5C 8DAD2E50 */  lw    $t5, %lo(D_800E2E50)($t5)
/* 0B2A60 800B1E60 8D2C0000 */  lw    $t4, ($t1)
/* 0B2A64 800B1E64 25AFFFFF */  addiu $t7, $t5, -1
/* 0B2A68 800B1E68 018F082A */  slt   $at, $t4, $t7
/* 0B2A6C 800B1E6C 14200009 */  bnez  $at, .L800B1E94
/* 0B2A70 800B1E70 00000000 */   nop   
/* 0B2A74 800B1E74 3C02800E */  lui   $v0, %hi(D_800E2CB0) # $v0, 0x800e
/* 0B2A78 800B1E78 24422CB0 */  addiu $v0, %lo(D_800E2CB0) # addiu $v0, $v0, 0x2cb0
/* 0B2A7C 800B1E7C 8C4E0000 */  lw    $t6, ($v0)
/* 0B2A80 800B1E80 00000000 */  nop   
/* 0B2A84 800B1E84 15C00069 */  bnez  $t6, .L800B202C
/* 0B2A88 800B1E88 00000000 */   nop   
/* 0B2A8C 800B1E8C 10000067 */  b     .L800B202C
/* 0B2A90 800B1E90 AC450000 */   sw    $a1, ($v0)
.L800B1E94:
/* 0B2A94 800B1E94 8498002C */  lh    $t8, 0x2c($a0)
/* 0B2A98 800B1E98 000250C0 */  sll   $t2, $v0, 3
/* 0B2A9C 800B1E9C 13000007 */  beqz  $t8, .L800B1EBC
/* 0B2AA0 800B1EA0 01425023 */   subu  $t2, $t2, $v0
/* 0B2AA4 800B1EA4 000A5100 */  sll   $t2, $t2, 4
/* 0B2AA8 800B1EA8 008A1821 */  addu  $v1, $a0, $t2
.L800B1EAC:
/* 0B2AAC 800B1EAC 8479009C */  lh    $t9, 0x9c($v1)
/* 0B2AB0 800B1EB0 24420001 */  addiu $v0, $v0, 1
/* 0B2AB4 800B1EB4 1720FFFD */  bnez  $t9, .L800B1EAC
/* 0B2AB8 800B1EB8 24630070 */   addiu $v1, $v1, 0x70
.L800B1EBC:
/* 0B2ABC 800B1EBC 000230C0 */  sll   $a2, $v0, 3
/* 0B2AC0 800B1EC0 00C23023 */  subu  $a2, $a2, $v0
/* 0B2AC4 800B1EC4 00063100 */  sll   $a2, $a2, 4
/* 0B2AC8 800B1EC8 00865821 */  addu  $t3, $a0, $a2
/* 0B2ACC 800B1ECC A567002C */  sh    $a3, 0x2c($t3)
/* 0B2AD0 800B1ED0 8D2D0000 */  lw    $t5, ($t1)
/* 0B2AD4 800B1ED4 8D0F0000 */  lw    $t7, ($t0)
/* 0B2AD8 800B1ED8 25AC0001 */  addiu $t4, $t5, 1
/* 0B2ADC 800B1EDC AD2C0000 */  sw    $t4, ($t1)
/* 0B2AE0 800B1EE0 10000052 */  b     .L800B202C
/* 0B2AE4 800B1EE4 00CF1821 */   addu  $v1, $a2, $t7
.L800B1EE8:
/* 0B2AE8 800B1EE8 25082CCC */  addiu $t0, $t0, 0x2ccc
/* 0B2AEC 800B1EEC 8D040000 */  lw    $a0, ($t0)
/* 0B2AF0 800B1EF0 3C09800E */  lui   $t1, %hi(D_800E2CC4) # $t1, 0x800e
/* 0B2AF4 800B1EF4 1080004D */  beqz  $a0, .L800B202C
/* 0B2AF8 800B1EF8 25292CC4 */   addiu $t1, %lo(D_800E2CC4) # addiu $t1, $t1, 0x2cc4
/* 0B2AFC 800B1EFC 3C18800E */  lui   $t8, %hi(D_800E2E58) # $t8, 0x800e
/* 0B2B00 800B1F00 8F182E58 */  lw    $t8, %lo(D_800E2E58)($t8)
/* 0B2B04 800B1F04 8D2E0000 */  lw    $t6, ($t1)
/* 0B2B08 800B1F08 270AFFFF */  addiu $t2, $t8, -1
/* 0B2B0C 800B1F0C 01CA082A */  slt   $at, $t6, $t2
/* 0B2B10 800B1F10 14200009 */  bnez  $at, .L800B1F38
/* 0B2B14 800B1F14 00000000 */   nop   
/* 0B2B18 800B1F18 3C02800E */  lui   $v0, %hi(D_800E2CC8) # $v0, 0x800e
/* 0B2B1C 800B1F1C 24422CC8 */  addiu $v0, %lo(D_800E2CC8) # addiu $v0, $v0, 0x2cc8
/* 0B2B20 800B1F20 8C590000 */  lw    $t9, ($v0)
/* 0B2B24 800B1F24 00000000 */  nop   
/* 0B2B28 800B1F28 17200040 */  bnez  $t9, .L800B202C
/* 0B2B2C 800B1F2C 00000000 */   nop   
/* 0B2B30 800B1F30 1000003E */  b     .L800B202C
/* 0B2B34 800B1F34 AC450000 */   sw    $a1, ($v0)
.L800B1F38:
/* 0B2B38 800B1F38 848B002C */  lh    $t3, 0x2c($a0)
/* 0B2B3C 800B1F3C 000268C0 */  sll   $t5, $v0, 3
/* 0B2B40 800B1F40 11600007 */  beqz  $t3, .L800B1F60
/* 0B2B44 800B1F44 01A26823 */   subu  $t5, $t5, $v0
/* 0B2B48 800B1F48 000D6900 */  sll   $t5, $t5, 4
/* 0B2B4C 800B1F4C 008D1821 */  addu  $v1, $a0, $t5
.L800B1F50:
/* 0B2B50 800B1F50 846C009C */  lh    $t4, 0x9c($v1)
/* 0B2B54 800B1F54 24420001 */  addiu $v0, $v0, 1
/* 0B2B58 800B1F58 1580FFFD */  bnez  $t4, .L800B1F50
/* 0B2B5C 800B1F5C 24630070 */   addiu $v1, $v1, 0x70
.L800B1F60:
/* 0B2B60 800B1F60 000230C0 */  sll   $a2, $v0, 3
/* 0B2B64 800B1F64 00C23023 */  subu  $a2, $a2, $v0
/* 0B2B68 800B1F68 00063100 */  sll   $a2, $a2, 4
/* 0B2B6C 800B1F6C 00867821 */  addu  $t7, $a0, $a2
/* 0B2B70 800B1F70 A5E7002C */  sh    $a3, 0x2c($t7)
/* 0B2B74 800B1F74 8D380000 */  lw    $t8, ($t1)
/* 0B2B78 800B1F78 8D0A0000 */  lw    $t2, ($t0)
/* 0B2B7C 800B1F7C 270E0001 */  addiu $t6, $t8, 1
/* 0B2B80 800B1F80 AD2E0000 */  sw    $t6, ($t1)
/* 0B2B84 800B1F84 10000029 */  b     .L800B202C
/* 0B2B88 800B1F88 00CA1821 */   addu  $v1, $a2, $t2
.L800B1F8C:
/* 0B2B8C 800B1F8C 24E72CD8 */  addiu $a3, $a3, 0x2cd8
/* 0B2B90 800B1F90 8CE40000 */  lw    $a0, ($a3)
/* 0B2B94 800B1F94 3C08800E */  lui   $t0, %hi(D_800E2CD0) # $t0, 0x800e
/* 0B2B98 800B1F98 10800024 */  beqz  $a0, .L800B202C
/* 0B2B9C 800B1F9C 25082CD0 */   addiu $t0, %lo(D_800E2CD0) # addiu $t0, $t0, 0x2cd0
/* 0B2BA0 800B1FA0 3C0B800E */  lui   $t3, %hi(D_800E2E5C) # $t3, 0x800e
/* 0B2BA4 800B1FA4 8D6B2E5C */  lw    $t3, %lo(D_800E2E5C)($t3)
/* 0B2BA8 800B1FA8 8D190000 */  lw    $t9, ($t0)
/* 0B2BAC 800B1FAC 256DFFFF */  addiu $t5, $t3, -1
/* 0B2BB0 800B1FB0 032D082A */  slt   $at, $t9, $t5
/* 0B2BB4 800B1FB4 14200009 */  bnez  $at, .L800B1FDC
/* 0B2BB8 800B1FB8 00000000 */   nop   
/* 0B2BBC 800B1FBC 3C02800E */  lui   $v0, %hi(D_800E2CD4) # $v0, 0x800e
/* 0B2BC0 800B1FC0 24422CD4 */  addiu $v0, %lo(D_800E2CD4) # addiu $v0, $v0, 0x2cd4
/* 0B2BC4 800B1FC4 8C4C0000 */  lw    $t4, ($v0)
/* 0B2BC8 800B1FC8 00000000 */  nop   
/* 0B2BCC 800B1FCC 15800017 */  bnez  $t4, .L800B202C
/* 0B2BD0 800B1FD0 00000000 */   nop   
/* 0B2BD4 800B1FD4 10000015 */  b     .L800B202C
/* 0B2BD8 800B1FD8 AC450000 */   sw    $a1, ($v0)
.L800B1FDC:
/* 0B2BDC 800B1FDC 848F002C */  lh    $t7, 0x2c($a0)
/* 0B2BE0 800B1FE0 0002C100 */  sll   $t8, $v0, 4
/* 0B2BE4 800B1FE4 11E00007 */  beqz  $t7, .L800B2004
/* 0B2BE8 800B1FE8 0302C023 */   subu  $t8, $t8, $v0
/* 0B2BEC 800B1FEC 0018C0C0 */  sll   $t8, $t8, 3
/* 0B2BF0 800B1FF0 00981821 */  addu  $v1, $a0, $t8
.L800B1FF4:
/* 0B2BF4 800B1FF4 846E00A4 */  lh    $t6, 0xa4($v1)
/* 0B2BF8 800B1FF8 24420001 */  addiu $v0, $v0, 1
/* 0B2BFC 800B1FFC 15C0FFFD */  bnez  $t6, .L800B1FF4
/* 0B2C00 800B2000 24630078 */   addiu $v1, $v1, 0x78
.L800B2004:
/* 0B2C04 800B2004 00022900 */  sll   $a1, $v0, 4
/* 0B2C08 800B2008 00A22823 */  subu  $a1, $a1, $v0
/* 0B2C0C 800B200C 000528C0 */  sll   $a1, $a1, 3
/* 0B2C10 800B2010 00855021 */  addu  $t2, $a0, $a1
/* 0B2C14 800B2014 A546002C */  sh    $a2, 0x2c($t2)
/* 0B2C18 800B2018 8D0B0000 */  lw    $t3, ($t0)
/* 0B2C1C 800B201C 8CED0000 */  lw    $t5, ($a3)
/* 0B2C20 800B2020 25790001 */  addiu $t9, $t3, 1
/* 0B2C24 800B2024 AD190000 */  sw    $t9, ($t0)
/* 0B2C28 800B2028 00AD1821 */  addu  $v1, $a1, $t5
.L800B202C:
/* 0B2C2C 800B202C 10600002 */  beqz  $v1, .L800B2038
/* 0B2C30 800B2030 240CFFFF */   li    $t4, -1
/* 0B2C34 800B2034 A46C0048 */  sh    $t4, 0x48($v1)
.L800B2038:
/* 0B2C38 800B2038 03E00008 */  jr    $ra
/* 0B2C3C 800B203C 00601025 */   move  $v0, $v1

glabel func_800B2040
/* 0B2C40 800B2040 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0B2C44 800B2044 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B2C48 800B2048 8482002C */  lh    $v0, 0x2c($a0)
/* 0B2C4C 800B204C 00802825 */  move  $a1, $a0
/* 0B2C50 800B2050 28410005 */  slti  $at, $v0, 5
/* 0B2C54 800B2054 14200005 */  bnez  $at, .L800B206C
/* 0B2C58 800B2058 24010080 */   li    $at, 128
/* 0B2C5C 800B205C 1041000C */  beq   $v0, $at, .L800B2090
/* 0B2C60 800B2060 00000000 */   nop   
/* 0B2C64 800B2064 1000007B */  b     .L800B2254
/* 0B2C68 800B2068 8FBF0014 */   lw    $ra, 0x14($sp)
.L800B206C:
/* 0B2C6C 800B206C 2C410005 */  sltiu $at, $v0, 5
/* 0B2C70 800B2070 10200077 */  beqz  $at, .L800B2250
/* 0B2C74 800B2074 00027080 */   sll   $t6, $v0, 2
/* 0B2C78 800B2078 3C01800F */  lui   $at, 0x800f
/* 0B2C7C 800B207C 002E0821 */  addu  $at, $at, $t6
/* 0B2C80 800B2080 8C2E8BDC */  lw    $t6, -0x7424($at)
/* 0B2C84 800B2084 00000000 */  nop   
/* 0B2C88 800B2088 01C00008 */  jr    $t6
/* 0B2C8C 800B208C 00000000 */   nop   
.L800B2090:
/* 0B2C90 800B2090 3C02800E */  lui   $v0, %hi(D_800E2CB8) # $v0, 0x800e
/* 0B2C94 800B2094 8C422CB8 */  lw    $v0, %lo(D_800E2CB8)($v0)
/* 0B2C98 800B2098 00000000 */  nop   
/* 0B2C9C 800B209C 1840006D */  blez  $v0, .L800B2254
/* 0B2CA0 800B20A0 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B2CA4 800B20A4 8CA40044 */  lw    $a0, 0x44($a1)
/* 0B2CA8 800B20A8 00000000 */  nop   
/* 0B2CAC 800B20AC 10800008 */  beqz  $a0, .L800B20D0
/* 0B2CB0 800B20B0 244FFFFF */   addiu $t7, $v0, -1
/* 0B2CB4 800B20B4 0C01F32C */  jal   func_8007CCB0
/* 0B2CB8 800B20B8 AFA50018 */   sw    $a1, 0x18($sp)
/* 0B2CBC 800B20BC 3C02800E */  lui   $v0, %hi(D_800E2CB8) # $v0, 0x800e
/* 0B2CC0 800B20C0 8C422CB8 */  lw    $v0, %lo(D_800E2CB8)($v0)
/* 0B2CC4 800B20C4 8FA50018 */  lw    $a1, 0x18($sp)
/* 0B2CC8 800B20C8 00000000 */  nop   
/* 0B2CCC 800B20CC 244FFFFF */  addiu $t7, $v0, -1
.L800B20D0:
/* 0B2CD0 800B20D0 3C01800E */  lui   $at, %hi(D_800E2CB8) # $at, 0x800e
/* 0B2CD4 800B20D4 AC2F2CB8 */  sw    $t7, %lo(D_800E2CB8)($at)
/* 0B2CD8 800B20D8 1000005D */  b     .L800B2250
/* 0B2CDC 800B20DC A4A0002C */   sh    $zero, 0x2c($a1)
/* 0B2CE0 800B20E0 3C02800E */  lui   $v0, %hi(D_800E2CA0) # $v0, 0x800e
/* 0B2CE4 800B20E4 8C422CA0 */  lw    $v0, %lo(D_800E2CA0)($v0)
/* 0B2CE8 800B20E8 00000000 */  nop   
/* 0B2CEC 800B20EC 18400059 */  blez  $v0, .L800B2254
/* 0B2CF0 800B20F0 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B2CF4 800B20F4 8CB80044 */  lw    $t8, 0x44($a1)
/* 0B2CF8 800B20F8 00000000 */  nop   
/* 0B2CFC 800B20FC 8F040000 */  lw    $a0, ($t8)
/* 0B2D00 800B2100 00000000 */  nop   
/* 0B2D04 800B2104 10800008 */  beqz  $a0, .L800B2128
/* 0B2D08 800B2108 2459FFFF */   addiu $t9, $v0, -1
/* 0B2D0C 800B210C 0C01ECAF */  jal   func_8007B2BC
/* 0B2D10 800B2110 AFA50018 */   sw    $a1, 0x18($sp)
/* 0B2D14 800B2114 3C02800E */  lui   $v0, %hi(D_800E2CA0) # $v0, 0x800e
/* 0B2D18 800B2118 8C422CA0 */  lw    $v0, %lo(D_800E2CA0)($v0)
/* 0B2D1C 800B211C 8FA50018 */  lw    $a1, 0x18($sp)
/* 0B2D20 800B2120 00000000 */  nop   
/* 0B2D24 800B2124 2459FFFF */  addiu $t9, $v0, -1
.L800B2128:
/* 0B2D28 800B2128 3C01800E */  lui   $at, %hi(D_800E2CA0) # $at, 0x800e
/* 0B2D2C 800B212C AC392CA0 */  sw    $t9, %lo(D_800E2CA0)($at)
/* 0B2D30 800B2130 10000047 */  b     .L800B2250
/* 0B2D34 800B2134 A4A0002C */   sh    $zero, 0x2c($a1)
/* 0B2D38 800B2138 3C02800E */  lui   $v0, %hi(D_800E2CAC) # $v0, 0x800e
/* 0B2D3C 800B213C 8C422CAC */  lw    $v0, %lo(D_800E2CAC)($v0)
/* 0B2D40 800B2140 00000000 */  nop   
/* 0B2D44 800B2144 18400043 */  blez  $v0, .L800B2254
/* 0B2D48 800B2148 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B2D4C 800B214C 8CA80044 */  lw    $t0, 0x44($a1)
/* 0B2D50 800B2150 00000000 */  nop   
/* 0B2D54 800B2154 8D040000 */  lw    $a0, ($t0)
/* 0B2D58 800B2158 00000000 */  nop   
/* 0B2D5C 800B215C 10800008 */  beqz  $a0, .L800B2180
/* 0B2D60 800B2160 2449FFFF */   addiu $t1, $v0, -1
/* 0B2D64 800B2164 0C01ECAF */  jal   func_8007B2BC
/* 0B2D68 800B2168 AFA50018 */   sw    $a1, 0x18($sp)
/* 0B2D6C 800B216C 3C02800E */  lui   $v0, %hi(D_800E2CAC) # $v0, 0x800e
/* 0B2D70 800B2170 8C422CAC */  lw    $v0, %lo(D_800E2CAC)($v0)
/* 0B2D74 800B2174 8FA50018 */  lw    $a1, 0x18($sp)
/* 0B2D78 800B2178 00000000 */  nop   
/* 0B2D7C 800B217C 2449FFFF */  addiu $t1, $v0, -1
.L800B2180:
/* 0B2D80 800B2180 3C01800E */  lui   $at, %hi(D_800E2CAC) # $at, 0x800e
/* 0B2D84 800B2184 AC292CAC */  sw    $t1, %lo(D_800E2CAC)($at)
/* 0B2D88 800B2188 10000031 */  b     .L800B2250
/* 0B2D8C 800B218C A4A0002C */   sh    $zero, 0x2c($a1)
/* 0B2D90 800B2190 3C02800E */  lui   $v0, %hi(D_800E2CC4) # $v0, 0x800e
/* 0B2D94 800B2194 8C422CC4 */  lw    $v0, %lo(D_800E2CC4)($v0)
/* 0B2D98 800B2198 00000000 */  nop   
/* 0B2D9C 800B219C 1840002D */  blez  $v0, .L800B2254
/* 0B2DA0 800B21A0 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B2DA4 800B21A4 8CAA0044 */  lw    $t2, 0x44($a1)
/* 0B2DA8 800B21A8 00000000 */  nop   
/* 0B2DAC 800B21AC 8D440000 */  lw    $a0, ($t2)
/* 0B2DB0 800B21B0 00000000 */  nop   
/* 0B2DB4 800B21B4 10800008 */  beqz  $a0, .L800B21D8
/* 0B2DB8 800B21B8 244BFFFF */   addiu $t3, $v0, -1
/* 0B2DBC 800B21BC 0C01ECAF */  jal   func_8007B2BC
/* 0B2DC0 800B21C0 AFA50018 */   sw    $a1, 0x18($sp)
/* 0B2DC4 800B21C4 3C02800E */  lui   $v0, %hi(D_800E2CC4) # $v0, 0x800e
/* 0B2DC8 800B21C8 8C422CC4 */  lw    $v0, %lo(D_800E2CC4)($v0)
/* 0B2DCC 800B21CC 8FA50018 */  lw    $a1, 0x18($sp)
/* 0B2DD0 800B21D0 00000000 */  nop   
/* 0B2DD4 800B21D4 244BFFFF */  addiu $t3, $v0, -1
.L800B21D8:
/* 0B2DD8 800B21D8 3C01800E */  lui   $at, %hi(D_800E2CC4) # $at, 0x800e
/* 0B2DDC 800B21DC AC2B2CC4 */  sw    $t3, %lo(D_800E2CC4)($at)
/* 0B2DE0 800B21E0 1000001B */  b     .L800B2250
/* 0B2DE4 800B21E4 A4A0002C */   sh    $zero, 0x2c($a1)
/* 0B2DE8 800B21E8 3C0C800E */  lui   $t4, %hi(D_800E2CD0) # $t4, 0x800e
/* 0B2DEC 800B21EC 8D8C2CD0 */  lw    $t4, %lo(D_800E2CD0)($t4)
/* 0B2DF0 800B21F0 00A02025 */  move  $a0, $a1
/* 0B2DF4 800B21F4 19800017 */  blez  $t4, .L800B2254
/* 0B2DF8 800B21F8 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B2DFC 800B21FC 0C02C98F */  jal   func_800B263C
/* 0B2E00 800B2200 AFA50018 */   sw    $a1, 0x18($sp)
/* 0B2E04 800B2204 8FA50018 */  lw    $a1, 0x18($sp)
/* 0B2E08 800B2208 00000000 */  nop   
/* 0B2E0C 800B220C 8CAD0044 */  lw    $t5, 0x44($a1)
/* 0B2E10 800B2210 00000000 */  nop   
/* 0B2E14 800B2214 8DA40000 */  lw    $a0, ($t5)
/* 0B2E18 800B2218 00000000 */  nop   
/* 0B2E1C 800B221C 10800005 */  beqz  $a0, .L800B2234
/* 0B2E20 800B2220 00000000 */   nop   
/* 0B2E24 800B2224 0C01ECAF */  jal   func_8007B2BC
/* 0B2E28 800B2228 AFA50018 */   sw    $a1, 0x18($sp)
/* 0B2E2C 800B222C 8FA50018 */  lw    $a1, 0x18($sp)
/* 0B2E30 800B2230 00000000 */  nop   
.L800B2234:
/* 0B2E34 800B2234 3C02800E */  lui   $v0, %hi(D_800E2CD0) # $v0, 0x800e
/* 0B2E38 800B2238 24422CD0 */  addiu $v0, %lo(D_800E2CD0) # addiu $v0, $v0, 0x2cd0
/* 0B2E3C 800B223C 8C4E0000 */  lw    $t6, ($v0)
/* 0B2E40 800B2240 00000000 */  nop   
/* 0B2E44 800B2244 25CFFFFF */  addiu $t7, $t6, -1
/* 0B2E48 800B2248 AC4F0000 */  sw    $t7, ($v0)
/* 0B2E4C 800B224C A4A0002C */  sh    $zero, 0x2c($a1)
.L800B2250:
/* 0B2E50 800B2250 8FBF0014 */  lw    $ra, 0x14($sp)
.L800B2254:
/* 0B2E54 800B2254 27BD0018 */  addiu $sp, $sp, 0x18
/* 0B2E58 800B2258 03E00008 */  jr    $ra
/* 0B2E5C 800B225C 00000000 */   nop   

glabel func_800B2260
/* 0B2E60 800B2260 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0B2E64 800B2264 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B2E68 800B2268 848E0004 */  lh    $t6, 4($a0)
/* 0B2E6C 800B226C 00802825 */  move  $a1, $a0
/* 0B2E70 800B2270 31CF0400 */  andi  $t7, $t6, 0x400
/* 0B2E74 800B2274 11E0001E */  beqz  $t7, .L800B22F0
/* 0B2E78 800B2278 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B2E7C 800B227C 8C84000C */  lw    $a0, 0xc($a0)
/* 0B2E80 800B2280 00000000 */  nop   
/* 0B2E84 800B2284 1080001A */  beqz  $a0, .L800B22F0
/* 0B2E88 800B2288 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B2E8C 800B228C 90B80006 */  lbu   $t8, 6($a1)
/* 0B2E90 800B2290 00001825 */  move  $v1, $zero
/* 0B2E94 800B2294 1B000010 */  blez  $t8, .L800B22D8
/* 0B2E98 800B2298 00000000 */   nop   
/* 0B2E9C 800B229C 00002025 */  move  $a0, $zero
.L800B22A0:
/* 0B2EA0 800B22A0 8CB9000C */  lw    $t9, 0xc($a1)
/* 0B2EA4 800B22A4 24630001 */  addiu $v1, $v1, 1
/* 0B2EA8 800B22A8 03244021 */  addu  $t0, $t9, $a0
/* 0B2EAC 800B22AC 8D020000 */  lw    $v0, ($t0)
/* 0B2EB0 800B22B0 24840004 */  addiu $a0, $a0, 4
/* 0B2EB4 800B22B4 A440003A */  sh    $zero, 0x3a($v0)
/* 0B2EB8 800B22B8 AC400070 */  sw    $zero, 0x70($v0)
/* 0B2EBC 800B22BC 90A90006 */  lbu   $t1, 6($a1)
/* 0B2EC0 800B22C0 00000000 */  nop   
/* 0B2EC4 800B22C4 0069082A */  slt   $at, $v1, $t1
/* 0B2EC8 800B22C8 1420FFF5 */  bnez  $at, .L800B22A0
/* 0B2ECC 800B22CC 00000000 */   nop   
/* 0B2ED0 800B22D0 8CA4000C */  lw    $a0, 0xc($a1)
/* 0B2ED4 800B22D4 00000000 */  nop   
.L800B22D8:
/* 0B2ED8 800B22D8 0C01C450 */  jal   func_80071140
/* 0B2EDC 800B22DC AFA50018 */   sw    $a1, 0x18($sp)
/* 0B2EE0 800B22E0 8FA50018 */  lw    $a1, 0x18($sp)
/* 0B2EE4 800B22E4 00000000 */  nop   
/* 0B2EE8 800B22E8 ACA0000C */  sw    $zero, 0xc($a1)
/* 0B2EEC 800B22EC 8FBF0014 */  lw    $ra, 0x14($sp)
.L800B22F0:
/* 0B2EF0 800B22F0 27BD0018 */  addiu $sp, $sp, 0x18
/* 0B2EF4 800B22F4 03E00008 */  jr    $ra
/* 0B2EF8 800B22F8 00000000 */   nop   

glabel func_800B22FC
/* 0B2EFC 800B22FC 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0B2F00 800B2300 3C018012 */  lui   $at, %hi(D_80127C80) # $at, 0x8012
/* 0B2F04 800B2304 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B2F08 800B2308 AFB00018 */  sw    $s0, 0x18($sp)
/* 0B2F0C 800B230C AC257C80 */  sw    $a1, %lo(D_80127C80)($at)
/* 0B2F10 800B2310 8482002C */  lh    $v0, 0x2c($a0)
/* 0B2F14 800B2314 24010003 */  li    $at, 3
/* 0B2F18 800B2318 00808025 */  move  $s0, $a0
/* 0B2F1C 800B231C 14410005 */  bne   $v0, $at, .L800B2334
/* 0B2F20 800B2320 00001825 */   move  $v1, $zero
/* 0B2F24 800B2324 0C02C9B8 */  jal   func_800B26E0
/* 0B2F28 800B2328 00000000 */   nop   
/* 0B2F2C 800B232C 100000C0 */  b     .L800B2630
/* 0B2F30 800B2330 8FBF001C */   lw    $ra, 0x1c($sp)
.L800B2334:
/* 0B2F34 800B2334 8E0E0040 */  lw    $t6, 0x40($s0)
/* 0B2F38 800B2338 3C188012 */  lui   $t8, %hi(D_80127C80) # $t8, 0x8012
/* 0B2F3C 800B233C 31CF0003 */  andi  $t7, $t6, 3
/* 0B2F40 800B2340 11E0000B */  beqz  $t7, .L800B2370
/* 0B2F44 800B2344 24040004 */   li    $a0, 4
/* 0B2F48 800B2348 8F187C80 */  lw    $t8, %lo(D_80127C80)($t8)
/* 0B2F4C 800B234C 02002025 */  move  $a0, $s0
/* 0B2F50 800B2350 1B000006 */  blez  $t8, .L800B236C
/* 0B2F54 800B2354 00000000 */   nop   
/* 0B2F58 800B2358 0C02CBEF */  jal   func_800B2FBC
/* 0B2F5C 800B235C AFA30020 */   sw    $v1, 0x20($sp)
/* 0B2F60 800B2360 8FA30020 */  lw    $v1, 0x20($sp)
/* 0B2F64 800B2364 8602002C */  lh    $v0, 0x2c($s0)
/* 0B2F68 800B2368 00000000 */  nop   
.L800B236C:
/* 0B2F6C 800B236C 24040004 */  li    $a0, 4
.L800B2370:
/* 0B2F70 800B2370 14820006 */  bne   $a0, $v0, .L800B238C
/* 0B2F74 800B2374 24080001 */   li    $t0, 1
/* 0B2F78 800B2378 92190075 */  lbu   $t9, 0x75($s0)
/* 0B2F7C 800B237C 02001825 */  move  $v1, $s0
/* 0B2F80 800B2380 01194823 */  subu  $t1, $t0, $t9
/* 0B2F84 800B2384 A2090075 */  sb    $t1, 0x75($s0)
/* 0B2F88 800B2388 A2000077 */  sb    $zero, 0x77($s0)
.L800B238C:
/* 0B2F8C 800B238C 10600007 */  beqz  $v1, .L800B23AC
/* 0B2F90 800B2390 00000000 */   nop   
/* 0B2F94 800B2394 10600022 */  beqz  $v1, .L800B2420
/* 0B2F98 800B2398 00000000 */   nop   
/* 0B2F9C 800B239C 8C6A0070 */  lw    $t2, 0x70($v1)
/* 0B2FA0 800B23A0 00000000 */  nop   
/* 0B2FA4 800B23A4 1140001E */  beqz  $t2, .L800B2420
/* 0B2FA8 800B23A8 00000000 */   nop   
.L800B23AC:
/* 0B2FAC 800B23AC 92020039 */  lbu   $v0, 0x39($s0)
/* 0B2FB0 800B23B0 24010002 */  li    $at, 2
/* 0B2FB4 800B23B4 14410006 */  bne   $v0, $at, .L800B23D0
/* 0B2FB8 800B23B8 24010003 */   li    $at, 3
/* 0B2FBC 800B23BC 0C02CCD6 */  jal   func_800B3358
/* 0B2FC0 800B23C0 02002025 */   move  $a0, $s0
/* 0B2FC4 800B23C4 10000017 */  b     .L800B2424
/* 0B2FC8 800B23C8 8604002E */   lh    $a0, 0x2e($s0)
/* 0B2FCC 800B23CC 24010003 */  li    $at, 3
.L800B23D0:
/* 0B2FD0 800B23D0 14410005 */  bne   $v0, $at, .L800B23E8
/* 0B2FD4 800B23D4 00000000 */   nop   
/* 0B2FD8 800B23D8 0C02CC90 */  jal   func_800B3240
/* 0B2FDC 800B23DC 02002025 */   move  $a0, $s0
/* 0B2FE0 800B23E0 10000010 */  b     .L800B2424
/* 0B2FE4 800B23E4 8604002E */   lh    $a0, 0x2e($s0)
.L800B23E8:
/* 0B2FE8 800B23E8 14820005 */  bne   $a0, $v0, .L800B2400
/* 0B2FEC 800B23EC 24010005 */   li    $at, 5
/* 0B2FF0 800B23F0 0C02CC50 */  jal   func_800B3140
/* 0B2FF4 800B23F4 02002025 */   move  $a0, $s0
/* 0B2FF8 800B23F8 1000000A */  b     .L800B2424
/* 0B2FFC 800B23FC 8604002E */   lh    $a0, 0x2e($s0)
.L800B2400:
/* 0B3000 800B2400 14410005 */  bne   $v0, $at, .L800B2418
/* 0B3004 800B2404 00000000 */   nop   
/* 0B3008 800B2408 0C02CD59 */  jal   func_800B3564
/* 0B300C 800B240C 02002025 */   move  $a0, $s0
/* 0B3010 800B2410 10000004 */  b     .L800B2424
/* 0B3014 800B2414 8604002E */   lh    $a0, 0x2e($s0)
.L800B2418:
/* 0B3018 800B2418 0C02CD2C */  jal   func_800B34B0
/* 0B301C 800B241C 02002025 */   move  $a0, $s0
.L800B2420:
/* 0B3020 800B2420 8604002E */  lh    $a0, 0x2e($s0)
.L800B2424:
/* 0B3024 800B2424 0C00A8B7 */  jal   func_8002A2DC
/* 0B3028 800B2428 00000000 */   nop   
/* 0B302C 800B242C 1040003D */  beqz  $v0, .L800B2524
/* 0B3030 800B2430 00000000 */   nop   
/* 0B3034 800B2434 844B0000 */  lh    $t3, ($v0)
/* 0B3038 800B2438 C60C000C */  lwc1  $f12, 0xc($s0)
/* 0B303C 800B243C 448B2000 */  mtc1  $t3, $f4
/* 0B3040 800B2440 00000000 */  nop   
/* 0B3044 800B2444 468021A0 */  cvt.s.w $f6, $f4
/* 0B3048 800B2448 4606603C */  c.lt.s $f12, $f6
/* 0B304C 800B244C 00000000 */  nop   
/* 0B3050 800B2450 4501002E */  bc1t  .L800B250C
/* 0B3054 800B2454 00000000 */   nop   
/* 0B3058 800B2458 844C0006 */  lh    $t4, 6($v0)
/* 0B305C 800B245C 00000000 */  nop   
/* 0B3060 800B2460 448C4000 */  mtc1  $t4, $f8
/* 0B3064 800B2464 00000000 */  nop   
/* 0B3068 800B2468 468042A0 */  cvt.s.w $f10, $f8
/* 0B306C 800B246C 460C503C */  c.lt.s $f10, $f12
/* 0B3070 800B2470 00000000 */  nop   
/* 0B3074 800B2474 45010025 */  bc1t  .L800B250C
/* 0B3078 800B2478 00000000 */   nop   
/* 0B307C 800B247C 844D0002 */  lh    $t5, 2($v0)
/* 0B3080 800B2480 C6000010 */  lwc1  $f0, 0x10($s0)
/* 0B3084 800B2484 448D8000 */  mtc1  $t5, $f16
/* 0B3088 800B2488 00000000 */  nop   
/* 0B308C 800B248C 468084A0 */  cvt.s.w $f18, $f16
/* 0B3090 800B2490 4612003C */  c.lt.s $f0, $f18
/* 0B3094 800B2494 00000000 */  nop   
/* 0B3098 800B2498 4501001C */  bc1t  .L800B250C
/* 0B309C 800B249C 00000000 */   nop   
/* 0B30A0 800B24A0 844E0008 */  lh    $t6, 8($v0)
/* 0B30A4 800B24A4 00000000 */  nop   
/* 0B30A8 800B24A8 448E2000 */  mtc1  $t6, $f4
/* 0B30AC 800B24AC 00000000 */  nop   
/* 0B30B0 800B24B0 468021A0 */  cvt.s.w $f6, $f4
/* 0B30B4 800B24B4 4600303C */  c.lt.s $f6, $f0
/* 0B30B8 800B24B8 00000000 */  nop   
/* 0B30BC 800B24BC 45010013 */  bc1t  .L800B250C
/* 0B30C0 800B24C0 00000000 */   nop   
/* 0B30C4 800B24C4 844F0004 */  lh    $t7, 4($v0)
/* 0B30C8 800B24C8 C6000014 */  lwc1  $f0, 0x14($s0)
/* 0B30CC 800B24CC 448F4000 */  mtc1  $t7, $f8
/* 0B30D0 800B24D0 00000000 */  nop   
/* 0B30D4 800B24D4 468042A0 */  cvt.s.w $f10, $f8
/* 0B30D8 800B24D8 460A003C */  c.lt.s $f0, $f10
/* 0B30DC 800B24DC 00000000 */  nop   
/* 0B30E0 800B24E0 4501000A */  bc1t  .L800B250C
/* 0B30E4 800B24E4 00000000 */   nop   
/* 0B30E8 800B24E8 8458000A */  lh    $t8, 0xa($v0)
/* 0B30EC 800B24EC 00000000 */  nop   
/* 0B30F0 800B24F0 44988000 */  mtc1  $t8, $f16
/* 0B30F4 800B24F4 00000000 */  nop   
/* 0B30F8 800B24F8 468084A0 */  cvt.s.w $f18, $f16
/* 0B30FC 800B24FC 4600903C */  c.lt.s $f18, $f0
/* 0B3100 800B2500 00000000 */  nop   
/* 0B3104 800B2504 4500000D */  bc1f  .L800B253C
/* 0B3108 800B2508 00000000 */   nop   
.L800B250C:
/* 0B310C 800B250C C60E0010 */  lwc1  $f14, 0x10($s0)
/* 0B3110 800B2510 8E060014 */  lw    $a2, 0x14($s0)
/* 0B3114 800B2514 0C00A7C6 */  jal   func_80029F18
/* 0B3118 800B2518 00000000 */   nop   
/* 0B311C 800B251C 10000007 */  b     .L800B253C
/* 0B3120 800B2520 A602002E */   sh    $v0, 0x2e($s0)
.L800B2524:
/* 0B3124 800B2524 C60C000C */  lwc1  $f12, 0xc($s0)
/* 0B3128 800B2528 C60E0010 */  lwc1  $f14, 0x10($s0)
/* 0B312C 800B252C 8E060014 */  lw    $a2, 0x14($s0)
/* 0B3130 800B2530 0C00A7C6 */  jal   func_80029F18
/* 0B3134 800B2534 00000000 */   nop   
/* 0B3138 800B2538 A602002E */  sh    $v0, 0x2e($s0)
.L800B253C:
/* 0B313C 800B253C 3C198012 */  lui   $t9, %hi(D_80127C80) # $t9, 0x8012
/* 0B3140 800B2540 8F397C80 */  lw    $t9, %lo(D_80127C80)($t9)
/* 0B3144 800B2544 8608003A */  lh    $t0, 0x3a($s0)
/* 0B3148 800B2548 00000000 */  nop   
/* 0B314C 800B254C 01194823 */  subu  $t1, $t0, $t9
/* 0B3150 800B2550 A609003A */  sh    $t1, 0x3a($s0)
/* 0B3154 800B2554 860A003A */  lh    $t2, 0x3a($s0)
/* 0B3158 800B2558 00000000 */  nop   
/* 0B315C 800B255C 1D400005 */  bgtz  $t2, .L800B2574
/* 0B3160 800B2560 00000000 */   nop   
/* 0B3164 800B2564 0C003FEE */  jal   func_8000FFB8
/* 0B3168 800B2568 02002025 */   move  $a0, $s0
/* 0B316C 800B256C 10000030 */  b     .L800B2630
/* 0B3170 800B2570 8FBF001C */   lw    $ra, 0x1c($sp)
.L800B2574:
/* 0B3174 800B2574 86020060 */  lh    $v0, 0x60($s0)
/* 0B3178 800B2578 3C0B8012 */  lui   $t3, %hi(D_80127C80) # $t3, 0x8012
/* 0B317C 800B257C 1440001C */  bnez  $v0, .L800B25F0
/* 0B3180 800B2580 3C0E8012 */   lui   $t6, %hi(D_80127C80) # $t6, 0x8012
/* 0B3184 800B2584 8D6B7C80 */  lw    $t3, %lo(D_80127C80)($t3)
/* 0B3188 800B2588 860C005E */  lh    $t4, 0x5e($s0)
/* 0B318C 800B258C 860E005C */  lh    $t6, 0x5c($s0)
/* 0B3190 800B2590 016C0019 */  multu $t3, $t4
/* 0B3194 800B2594 00006812 */  mflo  $t5
/* 0B3198 800B2598 01CD7821 */  addu  $t7, $t6, $t5
/* 0B319C 800B259C A60F005C */  sh    $t7, 0x5c($s0)
/* 0B31A0 800B25A0 8618005C */  lh    $t8, 0x5c($s0)
/* 0B31A4 800B25A4 00000000 */  nop   
/* 0B31A8 800B25A8 2B0100FF */  slti  $at, $t8, 0xff
/* 0B31AC 800B25AC 10200020 */  beqz  $at, .L800B2630
/* 0B31B0 800B25B0 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0B31B4 800B25B4 8E080040 */  lw    $t0, 0x40($s0)
/* 0B31B8 800B25B8 00000000 */  nop   
/* 0B31BC 800B25BC 31191000 */  andi  $t9, $t0, 0x1000
/* 0B31C0 800B25C0 13200006 */  beqz  $t9, .L800B25DC
/* 0B31C4 800B25C4 00000000 */   nop   
/* 0B31C8 800B25C8 86090006 */  lh    $t1, 6($s0)
/* 0B31CC 800B25CC 00000000 */  nop   
/* 0B31D0 800B25D0 352A0100 */  ori   $t2, $t1, 0x100
/* 0B31D4 800B25D4 10000015 */  b     .L800B262C
/* 0B31D8 800B25D8 A60A0006 */   sh    $t2, 6($s0)
.L800B25DC:
/* 0B31DC 800B25DC 860B0006 */  lh    $t3, 6($s0)
/* 0B31E0 800B25E0 00000000 */  nop   
/* 0B31E4 800B25E4 356C0080 */  ori   $t4, $t3, 0x80
/* 0B31E8 800B25E8 10000010 */  b     .L800B262C
/* 0B31EC 800B25EC A60C0006 */   sh    $t4, 6($s0)
.L800B25F0:
/* 0B31F0 800B25F0 8DCE7C80 */  lw    $t6, %lo(D_80127C80)($t6)
/* 0B31F4 800B25F4 00000000 */  nop   
/* 0B31F8 800B25F8 004E6823 */  subu  $t5, $v0, $t6
/* 0B31FC 800B25FC A60D0060 */  sh    $t5, 0x60($s0)
/* 0B3200 800B2600 86020060 */  lh    $v0, 0x60($s0)
/* 0B3204 800B2604 00000000 */  nop   
/* 0B3208 800B2608 04410009 */  bgez  $v0, .L800B2630
/* 0B320C 800B260C 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0B3210 800B2610 8618005E */  lh    $t8, 0x5e($s0)
/* 0B3214 800B2614 860F005C */  lh    $t7, 0x5c($s0)
/* 0B3218 800B2618 00580019 */  multu $v0, $t8
/* 0B321C 800B261C A6000060 */  sh    $zero, 0x60($s0)
/* 0B3220 800B2620 00004012 */  mflo  $t0
/* 0B3224 800B2624 01E8C823 */  subu  $t9, $t7, $t0
/* 0B3228 800B2628 A619005C */  sh    $t9, 0x5c($s0)
.L800B262C:
/* 0B322C 800B262C 8FBF001C */  lw    $ra, 0x1c($sp)
.L800B2630:
/* 0B3230 800B2630 8FB00018 */  lw    $s0, 0x18($sp)
/* 0B3234 800B2634 03E00008 */  jr    $ra
/* 0B3238 800B2638 27BD0028 */   addiu $sp, $sp, 0x28

glabel func_800B263C
/* 0B323C 800B263C 8C820070 */  lw    $v0, 0x70($a0)
/* 0B3240 800B2640 00000000 */  nop   
/* 0B3244 800B2644 10400024 */  beqz  $v0, .L800B26D8
/* 0B3248 800B2648 00000000 */   nop   
/* 0B324C 800B264C 90430006 */  lbu   $v1, 6($v0)
/* 0B3250 800B2650 00000000 */  nop   
/* 0B3254 800B2654 10600020 */  beqz  $v1, .L800B26D8
/* 0B3258 800B2658 00000000 */   nop   
/* 0B325C 800B265C 908F0074 */  lbu   $t7, 0x74($a0)
/* 0B3260 800B2660 8C4E000C */  lw    $t6, 0xc($v0)
/* 0B3264 800B2664 000FC080 */  sll   $t8, $t7, 2
/* 0B3268 800B2668 01D8C821 */  addu  $t9, $t6, $t8
/* 0B326C 800B266C 8F280000 */  lw    $t0, ($t9)
/* 0B3270 800B2670 2469FFFF */  addiu $t1, $v1, -1
/* 0B3274 800B2674 14880018 */  bne   $a0, $t0, .L800B26D8
/* 0B3278 800B2678 00000000 */   nop   
/* 0B327C 800B267C A0490006 */  sb    $t1, 6($v0)
/* 0B3280 800B2680 90850074 */  lbu   $a1, 0x74($a0)
/* 0B3284 800B2684 312A00FF */  andi  $t2, $t1, 0xff
/* 0B3288 800B2688 00AA082A */  slt   $at, $a1, $t2
/* 0B328C 800B268C 10200012 */  beqz  $at, .L800B26D8
/* 0B3290 800B2690 00051880 */   sll   $v1, $a1, 2
.L800B2694:
/* 0B3294 800B2694 8C4B000C */  lw    $t3, 0xc($v0)
/* 0B3298 800B2698 00000000 */  nop   
/* 0B329C 800B269C 01633021 */  addu  $a2, $t3, $v1
/* 0B32A0 800B26A0 8CCC0004 */  lw    $t4, 4($a2)
/* 0B32A4 800B26A4 00000000 */  nop   
/* 0B32A8 800B26A8 ACCC0000 */  sw    $t4, ($a2)
/* 0B32AC 800B26AC 8C4D000C */  lw    $t5, 0xc($v0)
/* 0B32B0 800B26B0 00000000 */  nop   
/* 0B32B4 800B26B4 01A37821 */  addu  $t7, $t5, $v1
/* 0B32B8 800B26B8 8DE40000 */  lw    $a0, ($t7)
/* 0B32BC 800B26BC 24630004 */  addiu $v1, $v1, 4
/* 0B32C0 800B26C0 A0850074 */  sb    $a1, 0x74($a0)
/* 0B32C4 800B26C4 904E0006 */  lbu   $t6, 6($v0)
/* 0B32C8 800B26C8 24A50001 */  addiu $a1, $a1, 1
/* 0B32CC 800B26CC 00AE082A */  slt   $at, $a1, $t6
/* 0B32D0 800B26D0 1420FFF0 */  bnez  $at, .L800B2694
/* 0B32D4 800B26D4 00000000 */   nop   
.L800B26D8:
/* 0B32D8 800B26D8 03E00008 */  jr    $ra
/* 0B32DC 800B26DC 00000000 */   nop   

glabel func_800B26E0
/* 0B32E0 800B26E0 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 0B32E4 800B26E4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B32E8 800B26E8 8C8E003C */  lw    $t6, 0x3c($a0)
/* 0B32EC 800B26EC 00803025 */  move  $a2, $a0
/* 0B32F0 800B26F0 00001825 */  move  $v1, $zero
/* 0B32F4 800B26F4 11C0000A */  beqz  $t6, .L800B2720
/* 0B32F8 800B26F8 AFAE0034 */   sw    $t6, 0x34($sp)
/* 0B32FC 800B26FC 8C870058 */  lw    $a3, 0x58($a0)
/* 0B3300 800B2700 00000000 */  nop   
/* 0B3304 800B2704 8CF80000 */  lw    $t8, ($a3)
/* 0B3308 800B2708 00000000 */  nop   
/* 0B330C 800B270C 8F19009C */  lw    $t9, 0x9c($t8)
/* 0B3310 800B2710 00000000 */  nop   
/* 0B3314 800B2714 AFB9002C */  sw    $t9, 0x2c($sp)
/* 0B3318 800B2718 8C830044 */  lw    $v1, 0x44($a0)
/* 0B331C 800B271C AFA70030 */  sw    $a3, 0x30($sp)
.L800B2720:
/* 0B3320 800B2720 90C80068 */  lbu   $t0, 0x68($a2)
/* 0B3324 800B2724 8FA70030 */  lw    $a3, 0x30($sp)
/* 0B3328 800B2728 29010002 */  slti  $at, $t0, 2
/* 0B332C 800B272C 102001CE */  beqz  $at, .L800B2E68
/* 0B3330 800B2730 3C058012 */   lui   $a1, 0x8012
/* 0B3334 800B2734 8FA90034 */  lw    $t1, 0x34($sp)
/* 0B3338 800B2738 00000000 */  nop   
/* 0B333C 800B273C 112001CA */  beqz  $t1, .L800B2E68
/* 0B3340 800B2740 00000000 */   nop   
/* 0B3344 800B2744 8CEA0000 */  lw    $t2, ($a3)
/* 0B3348 800B2748 00000000 */  nop   
/* 0B334C 800B274C 8D4B0000 */  lw    $t3, ($t2)
/* 0B3350 800B2750 00000000 */  nop   
/* 0B3354 800B2754 316C1000 */  andi  $t4, $t3, 0x1000
/* 0B3358 800B2758 11800017 */  beqz  $t4, .L800B27B8
/* 0B335C 800B275C 00000000 */   nop   
/* 0B3360 800B2760 C520001C */  lwc1  $f0, 0x1c($t1)
/* 0B3364 800B2764 C5220020 */  lwc1  $f2, 0x20($t1)
/* 0B3368 800B2768 46000102 */  mul.s $f4, $f0, $f0
/* 0B336C 800B276C C52E0024 */  lwc1  $f14, 0x24($t1)
/* 0B3370 800B2770 AFA70030 */  sw    $a3, 0x30($sp)
/* 0B3374 800B2774 AFA60050 */  sw    $a2, 0x50($sp)
/* 0B3378 800B2778 46021182 */  mul.s $f6, $f2, $f2
/* 0B337C 800B277C AFA30038 */  sw    $v1, 0x38($sp)
/* 0B3380 800B2780 460E7282 */  mul.s $f10, $f14, $f14
/* 0B3384 800B2784 46062200 */  add.s $f8, $f4, $f6
/* 0B3388 800B2788 0C0326B4 */  jal   sqrtf
/* 0B338C 800B278C 460A4300 */   add.s $f12, $f8, $f10
/* 0B3390 800B2790 8FA60050 */  lw    $a2, 0x50($sp)
/* 0B3394 800B2794 3C01800F */  lui   $at, %hi(D_800E8BF0) # $at, 0x800f
/* 0B3398 800B2798 C4D00008 */  lwc1  $f16, 8($a2)
/* 0B339C 800B279C C4248BF0 */  lwc1  $f4, %lo(D_800E8BF0)($at)
/* 0B33A0 800B27A0 46008482 */  mul.s $f18, $f16, $f0
/* 0B33A4 800B27A4 8FA30038 */  lw    $v1, 0x38($sp)
/* 0B33A8 800B27A8 8FA70030 */  lw    $a3, 0x30($sp)
/* 0B33AC 800B27AC 46049082 */  mul.s $f2, $f18, $f4
/* 0B33B0 800B27B0 10000004 */  b     .L800B27C4
/* 0B33B4 800B27B4 8CCD0040 */   lw    $t5, 0x40($a2)
.L800B27B8:
/* 0B33B8 800B27B8 C4C20008 */  lwc1  $f2, 8($a2)
/* 0B33BC 800B27BC 00000000 */  nop   
/* 0B33C0 800B27C0 8CCD0040 */  lw    $t5, 0x40($a2)
.L800B27C4:
/* 0B33C4 800B27C4 8FAF0034 */  lw    $t7, 0x34($sp)
/* 0B33C8 800B27C8 31AE4000 */  andi  $t6, $t5, 0x4000
/* 0B33CC 800B27CC 15C0001B */  bnez  $t6, .L800B283C
/* 0B33D0 800B27D0 27A50044 */   addiu $a1, $sp, 0x44
/* 0B33D4 800B27D4 44800000 */  mtc1  $zero, $f0
/* 0B33D8 800B27D8 24010001 */  li    $at, 1
/* 0B33DC 800B27DC E7A00044 */  swc1  $f0, 0x44($sp)
/* 0B33E0 800B27E0 E7A00048 */  swc1  $f0, 0x48($sp)
/* 0B33E4 800B27E4 E7A0004C */  swc1  $f0, 0x4c($sp)
/* 0B33E8 800B27E8 80C2006A */  lb    $v0, 0x6a($a2)
/* 0B33EC 800B27EC 00000000 */  nop   
/* 0B33F0 800B27F0 10410007 */  beq   $v0, $at, .L800B2810
/* 0B33F4 800B27F4 24010002 */   li    $at, 2
/* 0B33F8 800B27F8 10410003 */  beq   $v0, $at, .L800B2808
/* 0B33FC 800B27FC 00000000 */   nop   
/* 0B3400 800B2800 10000004 */  b     .L800B2814
/* 0B3404 800B2804 E7A20044 */   swc1  $f2, 0x44($sp)
.L800B2808:
/* 0B3408 800B2808 10000002 */  b     .L800B2814
/* 0B340C 800B280C E7A2004C */   swc1  $f2, 0x4c($sp)
.L800B2810:
/* 0B3410 800B2810 E7A20048 */  swc1  $f2, 0x48($sp)
.L800B2814:
/* 0B3414 800B2814 8FA40034 */  lw    $a0, 0x34($sp)
/* 0B3418 800B2818 AFA30038 */  sw    $v1, 0x38($sp)
/* 0B341C 800B281C AFA60050 */  sw    $a2, 0x50($sp)
/* 0B3420 800B2820 0C01C0C8 */  jal   func_80070320
/* 0B3424 800B2824 AFA70030 */   sw    $a3, 0x30($sp)
/* 0B3428 800B2828 8FA30038 */  lw    $v1, 0x38($sp)
/* 0B342C 800B282C 8FA60050 */  lw    $a2, 0x50($sp)
/* 0B3430 800B2830 8FA70030 */  lw    $a3, 0x30($sp)
/* 0B3434 800B2834 1000003D */  b     .L800B292C
/* 0B3438 800B2838 00000000 */   nop   
.L800B283C:
/* 0B343C 800B283C C5E6001C */  lwc1  $f6, 0x1c($t7)
/* 0B3440 800B2840 3C01800F */  lui   $at, %hi(D_800E8BF4) # $at, 0x800f
/* 0B3444 800B2844 E7A60044 */  swc1  $f6, 0x44($sp)
/* 0B3448 800B2848 46063402 */  mul.s $f16, $f6, $f6
/* 0B344C 800B284C C5E80020 */  lwc1  $f8, 0x20($t7)
/* 0B3450 800B2850 00000000 */  nop   
/* 0B3454 800B2854 E7A80048 */  swc1  $f8, 0x48($sp)
/* 0B3458 800B2858 46084482 */  mul.s $f18, $f8, $f8
/* 0B345C 800B285C C5EA0024 */  lwc1  $f10, 0x24($t7)
/* 0B3460 800B2860 C4288BF4 */  lwc1  $f8, %lo(D_800E8BF4)($at)
/* 0B3464 800B2864 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 0B3468 800B2868 460A5182 */  mul.s $f6, $f10, $f10
/* 0B346C 800B286C 46128100 */  add.s $f4, $f16, $f18
/* 0B3470 800B2870 E7AA004C */  swc1  $f10, 0x4c($sp)
/* 0B3474 800B2874 46043300 */  add.s $f12, $f6, $f4
/* 0B3478 800B2878 4608603C */  c.lt.s $f12, $f8
/* 0B347C 800B287C 00000000 */  nop   
/* 0B3480 800B2880 45000004 */  bc1f  .L800B2894
/* 0B3484 800B2884 00000000 */   nop   
/* 0B3488 800B2888 44816000 */  mtc1  $at, $f12
/* 0B348C 800B288C 1000000C */  b     .L800B28C0
/* 0B3490 800B2890 C7B00044 */   lwc1  $f16, 0x44($sp)
.L800B2894:
/* 0B3494 800B2894 AFA30038 */  sw    $v1, 0x38($sp)
/* 0B3498 800B2898 AFA60050 */  sw    $a2, 0x50($sp)
/* 0B349C 800B289C AFA70030 */  sw    $a3, 0x30($sp)
/* 0B34A0 800B28A0 0C0326B4 */  jal   sqrtf
/* 0B34A4 800B28A4 E7A2003C */   swc1  $f2, 0x3c($sp)
/* 0B34A8 800B28A8 C7A2003C */  lwc1  $f2, 0x3c($sp)
/* 0B34AC 800B28AC 8FA30038 */  lw    $v1, 0x38($sp)
/* 0B34B0 800B28B0 8FA60050 */  lw    $a2, 0x50($sp)
/* 0B34B4 800B28B4 8FA70030 */  lw    $a3, 0x30($sp)
/* 0B34B8 800B28B8 46001303 */  div.s $f12, $f2, $f0
/* 0B34BC 800B28BC C7B00044 */  lwc1  $f16, 0x44($sp)
.L800B28C0:
/* 0B34C0 800B28C0 C7AA0048 */  lwc1  $f10, 0x48($sp)
/* 0B34C4 800B28C4 460C8482 */  mul.s $f18, $f16, $f12
/* 0B34C8 800B28C8 C7A4004C */  lwc1  $f4, 0x4c($sp)
/* 0B34CC 800B28CC 24010001 */  li    $at, 1
/* 0B34D0 800B28D0 460C5182 */  mul.s $f6, $f10, $f12
/* 0B34D4 800B28D4 E7B20044 */  swc1  $f18, 0x44($sp)
/* 0B34D8 800B28D8 460C2202 */  mul.s $f8, $f4, $f12
/* 0B34DC 800B28DC E7A60048 */  swc1  $f6, 0x48($sp)
/* 0B34E0 800B28E0 C7AC0044 */  lwc1  $f12, 0x44($sp)
/* 0B34E4 800B28E4 E7A8004C */  swc1  $f8, 0x4c($sp)
/* 0B34E8 800B28E8 80C2006A */  lb    $v0, 0x6a($a2)
/* 0B34EC 800B28EC C7B0004C */  lwc1  $f16, 0x4c($sp)
/* 0B34F0 800B28F0 10400005 */  beqz  $v0, .L800B2908
/* 0B34F4 800B28F4 00000000 */   nop   
/* 0B34F8 800B28F8 10410007 */  beq   $v0, $at, .L800B2918
/* 0B34FC 800B28FC 00000000 */   nop   
/* 0B3500 800B2900 1000000A */  b     .L800B292C
/* 0B3504 800B2904 00000000 */   nop   
.L800B2908:
/* 0B3508 800B2908 46008487 */  neg.s $f18, $f16
/* 0B350C 800B290C E7B20044 */  swc1  $f18, 0x44($sp)
/* 0B3510 800B2910 10000006 */  b     .L800B292C
/* 0B3514 800B2914 E7AC004C */   swc1  $f12, 0x4c($sp)
.L800B2918:
/* 0B3518 800B2918 C7AA004C */  lwc1  $f10, 0x4c($sp)
/* 0B351C 800B291C C7AC0048 */  lwc1  $f12, 0x48($sp)
/* 0B3520 800B2920 46005187 */  neg.s $f6, $f10
/* 0B3524 800B2924 E7A60048 */  swc1  $f6, 0x48($sp)
/* 0B3528 800B2928 E7AC004C */  swc1  $f12, 0x4c($sp)
.L800B292C:
/* 0B352C 800B292C 106000CE */  beqz  $v1, .L800B2C68
/* 0B3530 800B2930 3C058012 */   lui   $a1, 0x8012
/* 0B3534 800B2934 90D80068 */  lbu   $t8, 0x68($a2)
/* 0B3538 800B2938 C7A40044 */  lwc1  $f4, 0x44($sp)
/* 0B353C 800B293C 170000CA */  bnez  $t8, .L800B2C68
/* 0B3540 800B2940 00000000 */   nop   
/* 0B3544 800B2944 C4E8000C */  lwc1  $f8, 0xc($a3)
/* 0B3548 800B2948 8C6A0008 */  lw    $t2, 8($v1)
/* 0B354C 800B294C 46082400 */  add.s $f16, $f4, $f8
/* 0B3550 800B2950 4459F800 */  cfc1  $t9, $31
/* 0B3554 800B2954 00000000 */  nop   
/* 0B3558 800B2958 37210003 */  ori   $at, $t9, 3
/* 0B355C 800B295C 38210002 */  xori  $at, $at, 2
/* 0B3560 800B2960 44C1F800 */  ctc1  $at, $31
/* 0B3564 800B2964 00000000 */  nop   
/* 0B3568 800B2968 460084A4 */  cvt.w.s $f18, $f16
/* 0B356C 800B296C 44089000 */  mfc1  $t0, $f18
/* 0B3570 800B2970 44D9F800 */  ctc1  $t9, $31
/* 0B3574 800B2974 A548000A */  sh    $t0, 0xa($t2)
/* 0B3578 800B2978 C4E60010 */  lwc1  $f6, 0x10($a3)
/* 0B357C 800B297C C7AA0048 */  lwc1  $f10, 0x48($sp)
/* 0B3580 800B2980 8C690008 */  lw    $t1, 8($v1)
/* 0B3584 800B2984 46065100 */  add.s $f4, $f10, $f6
/* 0B3588 800B2988 444BF800 */  cfc1  $t3, $31
/* 0B358C 800B298C 00000000 */  nop   
/* 0B3590 800B2990 35610003 */  ori   $at, $t3, 3
/* 0B3594 800B2994 38210002 */  xori  $at, $at, 2
/* 0B3598 800B2998 44C1F800 */  ctc1  $at, $31
/* 0B359C 800B299C 00000000 */  nop   
/* 0B35A0 800B29A0 46002224 */  cvt.w.s $f8, $f4
/* 0B35A4 800B29A4 440C4000 */  mfc1  $t4, $f8
/* 0B35A8 800B29A8 44CBF800 */  ctc1  $t3, $31
/* 0B35AC 800B29AC A52C000C */  sh    $t4, 0xc($t1)
/* 0B35B0 800B29B0 C4F20014 */  lwc1  $f18, 0x14($a3)
/* 0B35B4 800B29B4 C7B0004C */  lwc1  $f16, 0x4c($sp)
/* 0B35B8 800B29B8 8C6F0008 */  lw    $t7, 8($v1)
/* 0B35BC 800B29BC 46128280 */  add.s $f10, $f16, $f18
/* 0B35C0 800B29C0 444DF800 */  cfc1  $t5, $31
/* 0B35C4 800B29C4 00000000 */  nop   
/* 0B35C8 800B29C8 35A10003 */  ori   $at, $t5, 3
/* 0B35CC 800B29CC 38210002 */  xori  $at, $at, 2
/* 0B35D0 800B29D0 44C1F800 */  ctc1  $at, $31
/* 0B35D4 800B29D4 00000000 */  nop   
/* 0B35D8 800B29D8 460051A4 */  cvt.w.s $f6, $f10
/* 0B35DC 800B29DC 440E3000 */  mfc1  $t6, $f6
/* 0B35E0 800B29E0 44CDF800 */  ctc1  $t5, $31
/* 0B35E4 800B29E4 A5EE000E */  sh    $t6, 0xe($t7)
/* 0B35E8 800B29E8 8C620008 */  lw    $v0, 8($v1)
/* 0B35EC 800B29EC 444CF800 */  cfc1  $t4, $31
/* 0B35F0 800B29F0 90580006 */  lbu   $t8, 6($v0)
/* 0B35F4 800B29F4 35810003 */  ori   $at, $t4, 3
/* 0B35F8 800B29F8 A0580010 */  sb    $t8, 0x10($v0)
/* 0B35FC 800B29FC 8C620008 */  lw    $v0, 8($v1)
/* 0B3600 800B2A00 38210002 */  xori  $at, $at, 2
/* 0B3604 800B2A04 90590007 */  lbu   $t9, 7($v0)
/* 0B3608 800B2A08 44C1F800 */  ctc1  $at, $31
/* 0B360C 800B2A0C A0590011 */  sb    $t9, 0x11($v0)
/* 0B3610 800B2A10 8C620008 */  lw    $v0, 8($v1)
/* 0B3614 800B2A14 00000000 */  nop   
/* 0B3618 800B2A18 90480008 */  lbu   $t0, 8($v0)
/* 0B361C 800B2A1C 00000000 */  nop   
/* 0B3620 800B2A20 A0480012 */  sb    $t0, 0x12($v0)
/* 0B3624 800B2A24 8C6B0008 */  lw    $t3, 8($v1)
/* 0B3628 800B2A28 90EA0006 */  lbu   $t2, 6($a3)
/* 0B362C 800B2A2C 00000000 */  nop   
/* 0B3630 800B2A30 A16A0013 */  sb    $t2, 0x13($t3)
/* 0B3634 800B2A34 C4E4000C */  lwc1  $f4, 0xc($a3)
/* 0B3638 800B2A38 8C6D0008 */  lw    $t5, 8($v1)
/* 0B363C 800B2A3C 46002224 */  cvt.w.s $f8, $f4
/* 0B3640 800B2A40 44CCF800 */  ctc1  $t4, $31
/* 0B3644 800B2A44 44094000 */  mfc1  $t1, $f8
/* 0B3648 800B2A48 00000000 */  nop   
/* 0B364C 800B2A4C 444EF800 */  cfc1  $t6, $31
/* 0B3650 800B2A50 A5A90014 */  sh    $t1, 0x14($t5)
/* 0B3654 800B2A54 35C10003 */  ori   $at, $t6, 3
/* 0B3658 800B2A58 38210002 */  xori  $at, $at, 2
/* 0B365C 800B2A5C 44C1F800 */  ctc1  $at, $31
/* 0B3660 800B2A60 C4F00010 */  lwc1  $f16, 0x10($a3)
/* 0B3664 800B2A64 8C780008 */  lw    $t8, 8($v1)
/* 0B3668 800B2A68 460084A4 */  cvt.w.s $f18, $f16
/* 0B366C 800B2A6C 44CEF800 */  ctc1  $t6, $31
/* 0B3670 800B2A70 440F9000 */  mfc1  $t7, $f18
/* 0B3674 800B2A74 00000000 */  nop   
/* 0B3678 800B2A78 4459F800 */  cfc1  $t9, $31
/* 0B367C 800B2A7C A70F0016 */  sh    $t7, 0x16($t8)
/* 0B3680 800B2A80 37210003 */  ori   $at, $t9, 3
/* 0B3684 800B2A84 38210002 */  xori  $at, $at, 2
/* 0B3688 800B2A88 44C1F800 */  ctc1  $at, $31
/* 0B368C 800B2A8C C4EA0014 */  lwc1  $f10, 0x14($a3)
/* 0B3690 800B2A90 8C6A0008 */  lw    $t2, 8($v1)
/* 0B3694 800B2A94 460051A4 */  cvt.w.s $f6, $f10
/* 0B3698 800B2A98 2401FFFF */  li    $at, -1
/* 0B369C 800B2A9C 44083000 */  mfc1  $t0, $f6
/* 0B36A0 800B2AA0 44D9F800 */  ctc1  $t9, $31
/* 0B36A4 800B2AA4 A5480018 */  sh    $t0, 0x18($t2)
/* 0B36A8 800B2AA8 8FAB002C */  lw    $t3, 0x2c($sp)
/* 0B36AC 800B2AAC 00000000 */  nop   
/* 0B36B0 800B2AB0 1161001C */  beq   $t3, $at, .L800B2B24
/* 0B36B4 800B2AB4 00000000 */   nop   
/* 0B36B8 800B2AB8 84EC001E */  lh    $t4, 0x1e($a3)
/* 0B36BC 800B2ABC 8C6F0008 */  lw    $t7, 8($v1)
/* 0B36C0 800B2AC0 000C48C0 */  sll   $t1, $t4, 3
/* 0B36C4 800B2AC4 01696821 */  addu  $t5, $t3, $t1
/* 0B36C8 800B2AC8 91AE0014 */  lbu   $t6, 0x14($t5)
/* 0B36CC 800B2ACC 00000000 */  nop   
/* 0B36D0 800B2AD0 A1EE001A */  sb    $t6, 0x1a($t7)
/* 0B36D4 800B2AD4 84F9001E */  lh    $t9, 0x1e($a3)
/* 0B36D8 800B2AD8 8FB8002C */  lw    $t8, 0x2c($sp)
/* 0B36DC 800B2ADC 001940C0 */  sll   $t0, $t9, 3
/* 0B36E0 800B2AE0 03085021 */  addu  $t2, $t8, $t0
/* 0B36E4 800B2AE4 914C0015 */  lbu   $t4, 0x15($t2)
/* 0B36E8 800B2AE8 8C6B0008 */  lw    $t3, 8($v1)
/* 0B36EC 800B2AEC 00000000 */  nop   
/* 0B36F0 800B2AF0 A16C001B */  sb    $t4, 0x1b($t3)
/* 0B36F4 800B2AF4 84ED001E */  lh    $t5, 0x1e($a3)
/* 0B36F8 800B2AF8 8FA9002C */  lw    $t1, 0x2c($sp)
/* 0B36FC 800B2AFC 000D70C0 */  sll   $t6, $t5, 3
/* 0B3700 800B2B00 012E7821 */  addu  $t7, $t1, $t6
/* 0B3704 800B2B04 91F90016 */  lbu   $t9, 0x16($t7)
/* 0B3708 800B2B08 8C780008 */  lw    $t8, 8($v1)
/* 0B370C 800B2B0C 00000000 */  nop   
/* 0B3710 800B2B10 A319001C */  sb    $t9, 0x1c($t8)
/* 0B3714 800B2B14 8C6A0008 */  lw    $t2, 8($v1)
/* 0B3718 800B2B18 90E80006 */  lbu   $t0, 6($a3)
/* 0B371C 800B2B1C 10000011 */  b     .L800B2B64
/* 0B3720 800B2B20 A148001D */   sb    $t0, 0x1d($t2)
.L800B2B24:
/* 0B3724 800B2B24 90CC006C */  lbu   $t4, 0x6c($a2)
/* 0B3728 800B2B28 8C6B0008 */  lw    $t3, 8($v1)
/* 0B372C 800B2B2C 00000000 */  nop   
/* 0B3730 800B2B30 A16C001A */  sb    $t4, 0x1a($t3)
/* 0B3734 800B2B34 8C690008 */  lw    $t1, 8($v1)
/* 0B3738 800B2B38 90CD006D */  lbu   $t5, 0x6d($a2)
/* 0B373C 800B2B3C 00000000 */  nop   
/* 0B3740 800B2B40 A12D001B */  sb    $t5, 0x1b($t1)
/* 0B3744 800B2B44 8C6F0008 */  lw    $t7, 8($v1)
/* 0B3748 800B2B48 90CE006E */  lbu   $t6, 0x6e($a2)
/* 0B374C 800B2B4C 00000000 */  nop   
/* 0B3750 800B2B50 A1EE001C */  sb    $t6, 0x1c($t7)
/* 0B3754 800B2B54 8C780008 */  lw    $t8, 8($v1)
/* 0B3758 800B2B58 90F90006 */  lbu   $t9, 6($a3)
/* 0B375C 800B2B5C 00000000 */  nop   
/* 0B3760 800B2B60 A319001D */  sb    $t9, 0x1d($t8)
.L800B2B64:
/* 0B3764 800B2B64 C4E4000C */  lwc1  $f4, 0xc($a3)
/* 0B3768 800B2B68 C7A80044 */  lwc1  $f8, 0x44($sp)
/* 0B376C 800B2B6C 8C6C0008 */  lw    $t4, 8($v1)
/* 0B3770 800B2B70 46082401 */  sub.s $f16, $f4, $f8
/* 0B3774 800B2B74 3C058012 */  lui   $a1, %hi(D_80127C80) # $a1, 0x8012
/* 0B3778 800B2B78 4448F800 */  cfc1  $t0, $31
/* 0B377C 800B2B7C 24A57C80 */  addiu $a1, %lo(D_80127C80) # addiu $a1, $a1, 0x7c80
/* 0B3780 800B2B80 35010003 */  ori   $at, $t0, 3
/* 0B3784 800B2B84 38210002 */  xori  $at, $at, 2
/* 0B3788 800B2B88 44C1F800 */  ctc1  $at, $31
/* 0B378C 800B2B8C 00000000 */  nop   
/* 0B3790 800B2B90 460084A4 */  cvt.w.s $f18, $f16
/* 0B3794 800B2B94 440A9000 */  mfc1  $t2, $f18
/* 0B3798 800B2B98 44C8F800 */  ctc1  $t0, $31
/* 0B379C 800B2B9C A58A001E */  sh    $t2, 0x1e($t4)
/* 0B37A0 800B2BA0 C7A60048 */  lwc1  $f6, 0x48($sp)
/* 0B37A4 800B2BA4 C4EA0010 */  lwc1  $f10, 0x10($a3)
/* 0B37A8 800B2BA8 8C690008 */  lw    $t1, 8($v1)
/* 0B37AC 800B2BAC 46065101 */  sub.s $f4, $f10, $f6
/* 0B37B0 800B2BB0 444BF800 */  cfc1  $t3, $31
/* 0B37B4 800B2BB4 00000000 */  nop   
/* 0B37B8 800B2BB8 35610003 */  ori   $at, $t3, 3
/* 0B37BC 800B2BBC 38210002 */  xori  $at, $at, 2
/* 0B37C0 800B2BC0 44C1F800 */  ctc1  $at, $31
/* 0B37C4 800B2BC4 00000000 */  nop   
/* 0B37C8 800B2BC8 46002224 */  cvt.w.s $f8, $f4
/* 0B37CC 800B2BCC 440D4000 */  mfc1  $t5, $f8
/* 0B37D0 800B2BD0 44CBF800 */  ctc1  $t3, $31
/* 0B37D4 800B2BD4 A52D0020 */  sh    $t5, 0x20($t1)
/* 0B37D8 800B2BD8 C7B2004C */  lwc1  $f18, 0x4c($sp)
/* 0B37DC 800B2BDC C4F00014 */  lwc1  $f16, 0x14($a3)
/* 0B37E0 800B2BE0 8C790008 */  lw    $t9, 8($v1)
/* 0B37E4 800B2BE4 46128281 */  sub.s $f10, $f16, $f18
/* 0B37E8 800B2BE8 240D0001 */  li    $t5, 1
/* 0B37EC 800B2BEC 444EF800 */  cfc1  $t6, $31
/* 0B37F0 800B2BF0 00000000 */  nop   
/* 0B37F4 800B2BF4 35C10003 */  ori   $at, $t6, 3
/* 0B37F8 800B2BF8 38210002 */  xori  $at, $at, 2
/* 0B37FC 800B2BFC 44C1F800 */  ctc1  $at, $31
/* 0B3800 800B2C00 00000000 */  nop   
/* 0B3804 800B2C04 460051A4 */  cvt.w.s $f6, $f10
/* 0B3808 800B2C08 440F3000 */  mfc1  $t7, $f6
/* 0B380C 800B2C0C 44CEF800 */  ctc1  $t6, $31
/* 0B3810 800B2C10 A72F0022 */  sh    $t7, 0x22($t9)
/* 0B3814 800B2C14 8C620008 */  lw    $v0, 8($v1)
/* 0B3818 800B2C18 00000000 */  nop   
/* 0B381C 800B2C1C 90580006 */  lbu   $t8, 6($v0)
/* 0B3820 800B2C20 00000000 */  nop   
/* 0B3824 800B2C24 A0580024 */  sb    $t8, 0x24($v0)
/* 0B3828 800B2C28 8C620008 */  lw    $v0, 8($v1)
/* 0B382C 800B2C2C 00000000 */  nop   
/* 0B3830 800B2C30 90480007 */  lbu   $t0, 7($v0)
/* 0B3834 800B2C34 00000000 */  nop   
/* 0B3838 800B2C38 A0480025 */  sb    $t0, 0x25($v0)
/* 0B383C 800B2C3C 8C620008 */  lw    $v0, 8($v1)
/* 0B3840 800B2C40 00000000 */  nop   
/* 0B3844 800B2C44 904A0008 */  lbu   $t2, 8($v0)
/* 0B3848 800B2C48 00000000 */  nop   
/* 0B384C 800B2C4C A04A0026 */  sb    $t2, 0x26($v0)
/* 0B3850 800B2C50 8C6B0008 */  lw    $t3, 8($v1)
/* 0B3854 800B2C54 90EC0006 */  lbu   $t4, 6($a3)
/* 0B3858 800B2C58 00000000 */  nop   
/* 0B385C 800B2C5C A16C0027 */  sb    $t4, 0x27($t3)
/* 0B3860 800B2C60 100000C1 */  b     .L800B2F68
/* 0B3864 800B2C64 A0CD0068 */   sb    $t5, 0x68($a2)
.L800B2C68:
/* 0B3868 800B2C68 1060007D */  beqz  $v1, .L800B2E60
/* 0B386C 800B2C6C 00000000 */   nop   
/* 0B3870 800B2C70 C7A40044 */  lwc1  $f4, 0x44($sp)
/* 0B3874 800B2C74 C4E8000C */  lwc1  $f8, 0xc($a3)
/* 0B3878 800B2C78 8C6F0008 */  lw    $t7, 8($v1)
/* 0B387C 800B2C7C 46082400 */  add.s $f16, $f4, $f8
/* 0B3880 800B2C80 4449F800 */  cfc1  $t1, $31
/* 0B3884 800B2C84 00000000 */  nop   
/* 0B3888 800B2C88 35210003 */  ori   $at, $t1, 3
/* 0B388C 800B2C8C 38210002 */  xori  $at, $at, 2
/* 0B3890 800B2C90 44C1F800 */  ctc1  $at, $31
/* 0B3894 800B2C94 00000000 */  nop   
/* 0B3898 800B2C98 460084A4 */  cvt.w.s $f18, $f16
/* 0B389C 800B2C9C 440E9000 */  mfc1  $t6, $f18
/* 0B38A0 800B2CA0 44C9F800 */  ctc1  $t1, $31
/* 0B38A4 800B2CA4 A5EE0028 */  sh    $t6, 0x28($t7)
/* 0B38A8 800B2CA8 C7AA0048 */  lwc1  $f10, 0x48($sp)
/* 0B38AC 800B2CAC C4E60010 */  lwc1  $f6, 0x10($a3)
/* 0B38B0 800B2CB0 8C680008 */  lw    $t0, 8($v1)
/* 0B38B4 800B2CB4 46065100 */  add.s $f4, $f10, $f6
/* 0B38B8 800B2CB8 4459F800 */  cfc1  $t9, $31
/* 0B38BC 800B2CBC 00000000 */  nop   
/* 0B38C0 800B2CC0 37210003 */  ori   $at, $t9, 3
/* 0B38C4 800B2CC4 38210002 */  xori  $at, $at, 2
/* 0B38C8 800B2CC8 44C1F800 */  ctc1  $at, $31
/* 0B38CC 800B2CCC 00000000 */  nop   
/* 0B38D0 800B2CD0 46002224 */  cvt.w.s $f8, $f4
/* 0B38D4 800B2CD4 44184000 */  mfc1  $t8, $f8
/* 0B38D8 800B2CD8 44D9F800 */  ctc1  $t9, $31
/* 0B38DC 800B2CDC A518002A */  sh    $t8, 0x2a($t0)
/* 0B38E0 800B2CE0 C7B0004C */  lwc1  $f16, 0x4c($sp)
/* 0B38E4 800B2CE4 C4F20014 */  lwc1  $f18, 0x14($a3)
/* 0B38E8 800B2CE8 8C6B0008 */  lw    $t3, 8($v1)
/* 0B38EC 800B2CEC 46128280 */  add.s $f10, $f16, $f18
/* 0B38F0 800B2CF0 444AF800 */  cfc1  $t2, $31
/* 0B38F4 800B2CF4 00000000 */  nop   
/* 0B38F8 800B2CF8 35410003 */  ori   $at, $t2, 3
/* 0B38FC 800B2CFC 38210002 */  xori  $at, $at, 2
/* 0B3900 800B2D00 44C1F800 */  ctc1  $at, $31
/* 0B3904 800B2D04 00000000 */  nop   
/* 0B3908 800B2D08 460051A4 */  cvt.w.s $f6, $f10
/* 0B390C 800B2D0C 440C3000 */  mfc1  $t4, $f6
/* 0B3910 800B2D10 44CAF800 */  ctc1  $t2, $31
/* 0B3914 800B2D14 A56C002C */  sh    $t4, 0x2c($t3)
/* 0B3918 800B2D18 8C620008 */  lw    $v0, 8($v1)
/* 0B391C 800B2D1C 00000000 */  nop   
/* 0B3920 800B2D20 904D001A */  lbu   $t5, 0x1a($v0)
/* 0B3924 800B2D24 00000000 */  nop   
/* 0B3928 800B2D28 A04D002E */  sb    $t5, 0x2e($v0)
/* 0B392C 800B2D2C 8C620008 */  lw    $v0, 8($v1)
/* 0B3930 800B2D30 00000000 */  nop   
/* 0B3934 800B2D34 9049001B */  lbu   $t1, 0x1b($v0)
/* 0B3938 800B2D38 00000000 */  nop   
/* 0B393C 800B2D3C A049002F */  sb    $t1, 0x2f($v0)
/* 0B3940 800B2D40 8C620008 */  lw    $v0, 8($v1)
/* 0B3944 800B2D44 00000000 */  nop   
/* 0B3948 800B2D48 904E001C */  lbu   $t6, 0x1c($v0)
/* 0B394C 800B2D4C 00000000 */  nop   
/* 0B3950 800B2D50 A04E0030 */  sb    $t6, 0x30($v0)
/* 0B3954 800B2D54 8C790008 */  lw    $t9, 8($v1)
/* 0B3958 800B2D58 90EF0006 */  lbu   $t7, 6($a3)
/* 0B395C 800B2D5C 00000000 */  nop   
/* 0B3960 800B2D60 A32F0031 */  sb    $t7, 0x31($t9)
/* 0B3964 800B2D64 C7A80044 */  lwc1  $f8, 0x44($sp)
/* 0B3968 800B2D68 C4E4000C */  lwc1  $f4, 0xc($a3)
/* 0B396C 800B2D6C 8C6A0008 */  lw    $t2, 8($v1)
/* 0B3970 800B2D70 46082401 */  sub.s $f16, $f4, $f8
/* 0B3974 800B2D74 4458F800 */  cfc1  $t8, $31
/* 0B3978 800B2D78 00000000 */  nop   
/* 0B397C 800B2D7C 37010003 */  ori   $at, $t8, 3
/* 0B3980 800B2D80 38210002 */  xori  $at, $at, 2
/* 0B3984 800B2D84 44C1F800 */  ctc1  $at, $31
/* 0B3988 800B2D88 00000000 */  nop   
/* 0B398C 800B2D8C 460084A4 */  cvt.w.s $f18, $f16
/* 0B3990 800B2D90 44089000 */  mfc1  $t0, $f18
/* 0B3994 800B2D94 44D8F800 */  ctc1  $t8, $31
/* 0B3998 800B2D98 A5480032 */  sh    $t0, 0x32($t2)
/* 0B399C 800B2D9C C7A60048 */  lwc1  $f6, 0x48($sp)
/* 0B39A0 800B2DA0 C4EA0010 */  lwc1  $f10, 0x10($a3)
/* 0B39A4 800B2DA4 8C6D0008 */  lw    $t5, 8($v1)
/* 0B39A8 800B2DA8 46065101 */  sub.s $f4, $f10, $f6
/* 0B39AC 800B2DAC 444CF800 */  cfc1  $t4, $31
/* 0B39B0 800B2DB0 00000000 */  nop   
/* 0B39B4 800B2DB4 35810003 */  ori   $at, $t4, 3
/* 0B39B8 800B2DB8 38210002 */  xori  $at, $at, 2
/* 0B39BC 800B2DBC 44C1F800 */  ctc1  $at, $31
/* 0B39C0 800B2DC0 00000000 */  nop   
/* 0B39C4 800B2DC4 46002224 */  cvt.w.s $f8, $f4
/* 0B39C8 800B2DC8 440B4000 */  mfc1  $t3, $f8
/* 0B39CC 800B2DCC 44CCF800 */  ctc1  $t4, $31
/* 0B39D0 800B2DD0 A5AB0034 */  sh    $t3, 0x34($t5)
/* 0B39D4 800B2DD4 C7B2004C */  lwc1  $f18, 0x4c($sp)
/* 0B39D8 800B2DD8 C4F00014 */  lwc1  $f16, 0x14($a3)
/* 0B39DC 800B2DDC 8C6F0008 */  lw    $t7, 8($v1)
/* 0B39E0 800B2DE0 46128281 */  sub.s $f10, $f16, $f18
/* 0B39E4 800B2DE4 240B0002 */  li    $t3, 2
/* 0B39E8 800B2DE8 4449F800 */  cfc1  $t1, $31
/* 0B39EC 800B2DEC 00000000 */  nop   
/* 0B39F0 800B2DF0 35210003 */  ori   $at, $t1, 3
/* 0B39F4 800B2DF4 38210002 */  xori  $at, $at, 2
/* 0B39F8 800B2DF8 44C1F800 */  ctc1  $at, $31
/* 0B39FC 800B2DFC 00000000 */  nop   
/* 0B3A00 800B2E00 460051A4 */  cvt.w.s $f6, $f10
/* 0B3A04 800B2E04 440E3000 */  mfc1  $t6, $f6
/* 0B3A08 800B2E08 44C9F800 */  ctc1  $t1, $31
/* 0B3A0C 800B2E0C A5EE0036 */  sh    $t6, 0x36($t7)
/* 0B3A10 800B2E10 8C620008 */  lw    $v0, 8($v1)
/* 0B3A14 800B2E14 00000000 */  nop   
/* 0B3A18 800B2E18 9059001A */  lbu   $t9, 0x1a($v0)
/* 0B3A1C 800B2E1C 00000000 */  nop   
/* 0B3A20 800B2E20 A0590038 */  sb    $t9, 0x38($v0)
/* 0B3A24 800B2E24 8C620008 */  lw    $v0, 8($v1)
/* 0B3A28 800B2E28 00000000 */  nop   
/* 0B3A2C 800B2E2C 9058001B */  lbu   $t8, 0x1b($v0)
/* 0B3A30 800B2E30 00000000 */  nop   
/* 0B3A34 800B2E34 A0580039 */  sb    $t8, 0x39($v0)
/* 0B3A38 800B2E38 8C620008 */  lw    $v0, 8($v1)
/* 0B3A3C 800B2E3C 00000000 */  nop   
/* 0B3A40 800B2E40 9048001C */  lbu   $t0, 0x1c($v0)
/* 0B3A44 800B2E44 00000000 */  nop   
/* 0B3A48 800B2E48 A048003A */  sb    $t0, 0x3a($v0)
/* 0B3A4C 800B2E4C 8C6C0008 */  lw    $t4, 8($v1)
/* 0B3A50 800B2E50 90EA0006 */  lbu   $t2, 6($a3)
/* 0B3A54 800B2E54 00000000 */  nop   
/* 0B3A58 800B2E58 A18A003B */  sb    $t2, 0x3b($t4)
/* 0B3A5C 800B2E5C A0CB0068 */  sb    $t3, 0x68($a2)
.L800B2E60:
/* 0B3A60 800B2E60 10000041 */  b     .L800B2F68
/* 0B3A64 800B2E64 24A57C80 */   addiu $a1, $a1, 0x7c80
.L800B2E68:
/* 0B3A68 800B2E68 24A57C80 */  addiu $a1, $a1, 0x7c80
/* 0B3A6C 800B2E6C 8CA90000 */  lw    $t1, ($a1)
/* 0B3A70 800B2E70 84CD003A */  lh    $t5, 0x3a($a2)
/* 0B3A74 800B2E74 00C02025 */  move  $a0, $a2
/* 0B3A78 800B2E78 01A97023 */  subu  $t6, $t5, $t1
/* 0B3A7C 800B2E7C A4CE003A */  sh    $t6, 0x3a($a2)
/* 0B3A80 800B2E80 84CF003A */  lh    $t7, 0x3a($a2)
/* 0B3A84 800B2E84 00000000 */  nop   
/* 0B3A88 800B2E88 1DE00009 */  bgtz  $t7, .L800B2EB0
/* 0B3A8C 800B2E8C 00000000 */   nop   
/* 0B3A90 800B2E90 AFA30038 */  sw    $v1, 0x38($sp)
/* 0B3A94 800B2E94 0C003FEE */  jal   func_8000FFB8
/* 0B3A98 800B2E98 AFA60050 */   sw    $a2, 0x50($sp)
/* 0B3A9C 800B2E9C 8FA30038 */  lw    $v1, 0x38($sp)
/* 0B3AA0 800B2EA0 3C058012 */  lui   $a1, %hi(D_80127C80) # $a1, 0x8012
/* 0B3AA4 800B2EA4 8FA60050 */  lw    $a2, 0x50($sp)
/* 0B3AA8 800B2EA8 1000002F */  b     .L800B2F68
/* 0B3AAC 800B2EAC 24A57C80 */   addiu $a1, %lo(D_80127C80) # addiu $a1, $a1, 0x7c80
.L800B2EB0:
/* 0B3AB0 800B2EB0 84C20060 */  lh    $v0, 0x60($a2)
/* 0B3AB4 800B2EB4 00000000 */  nop   
/* 0B3AB8 800B2EB8 1440001C */  bnez  $v0, .L800B2F2C
/* 0B3ABC 800B2EBC 00000000 */   nop   
/* 0B3AC0 800B2EC0 8CB90000 */  lw    $t9, ($a1)
/* 0B3AC4 800B2EC4 84D8005E */  lh    $t8, 0x5e($a2)
/* 0B3AC8 800B2EC8 84CA005C */  lh    $t2, 0x5c($a2)
/* 0B3ACC 800B2ECC 03380019 */  multu $t9, $t8
/* 0B3AD0 800B2ED0 00004012 */  mflo  $t0
/* 0B3AD4 800B2ED4 01486021 */  addu  $t4, $t2, $t0
/* 0B3AD8 800B2ED8 A4CC005C */  sh    $t4, 0x5c($a2)
/* 0B3ADC 800B2EDC 84CB005C */  lh    $t3, 0x5c($a2)
/* 0B3AE0 800B2EE0 00000000 */  nop   
/* 0B3AE4 800B2EE4 296100FF */  slti  $at, $t3, 0xff
/* 0B3AE8 800B2EE8 1020001F */  beqz  $at, .L800B2F68
/* 0B3AEC 800B2EEC 00000000 */   nop   
/* 0B3AF0 800B2EF0 8CCD0040 */  lw    $t5, 0x40($a2)
/* 0B3AF4 800B2EF4 00000000 */  nop   
/* 0B3AF8 800B2EF8 31A91000 */  andi  $t1, $t5, 0x1000
/* 0B3AFC 800B2EFC 11200006 */  beqz  $t1, .L800B2F18
/* 0B3B00 800B2F00 00000000 */   nop   
/* 0B3B04 800B2F04 84CE0006 */  lh    $t6, 6($a2)
/* 0B3B08 800B2F08 00000000 */  nop   
/* 0B3B0C 800B2F0C 35CF0100 */  ori   $t7, $t6, 0x100
/* 0B3B10 800B2F10 10000015 */  b     .L800B2F68
/* 0B3B14 800B2F14 A4CF0006 */   sh    $t7, 6($a2)
.L800B2F18:
/* 0B3B18 800B2F18 84D90006 */  lh    $t9, 6($a2)
/* 0B3B1C 800B2F1C 00000000 */  nop   
/* 0B3B20 800B2F20 37380080 */  ori   $t8, $t9, 0x80
/* 0B3B24 800B2F24 10000010 */  b     .L800B2F68
/* 0B3B28 800B2F28 A4D80006 */   sh    $t8, 6($a2)
.L800B2F2C:
/* 0B3B2C 800B2F2C 8CAA0000 */  lw    $t2, ($a1)
/* 0B3B30 800B2F30 00000000 */  nop   
/* 0B3B34 800B2F34 004A4023 */  subu  $t0, $v0, $t2
/* 0B3B38 800B2F38 A4C80060 */  sh    $t0, 0x60($a2)
/* 0B3B3C 800B2F3C 84C20060 */  lh    $v0, 0x60($a2)
/* 0B3B40 800B2F40 00000000 */  nop   
/* 0B3B44 800B2F44 04410008 */  bgez  $v0, .L800B2F68
/* 0B3B48 800B2F48 00000000 */   nop   
/* 0B3B4C 800B2F4C 84CB005E */  lh    $t3, 0x5e($a2)
/* 0B3B50 800B2F50 84CC005C */  lh    $t4, 0x5c($a2)
/* 0B3B54 800B2F54 004B0019 */  multu $v0, $t3
/* 0B3B58 800B2F58 A4C00060 */  sh    $zero, 0x60($a2)
/* 0B3B5C 800B2F5C 00006812 */  mflo  $t5
/* 0B3B60 800B2F60 018D4823 */  subu  $t1, $t4, $t5
/* 0B3B64 800B2F64 A4C9005C */  sh    $t1, 0x5c($a2)
.L800B2F68:
/* 0B3B68 800B2F68 10600011 */  beqz  $v1, .L800B2FB0
/* 0B3B6C 800B2F6C 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B3B70 800B2F70 8C6E0000 */  lw    $t6, ($v1)
/* 0B3B74 800B2F74 00000000 */  nop   
/* 0B3B78 800B2F78 11C0000D */  beqz  $t6, .L800B2FB0
/* 0B3B7C 800B2F7C 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B3B80 800B2F80 8CCF0040 */  lw    $t7, 0x40($a2)
/* 0B3B84 800B2F84 00000000 */  nop   
/* 0B3B88 800B2F88 31F90003 */  andi  $t9, $t7, 3
/* 0B3B8C 800B2F8C 13200008 */  beqz  $t9, .L800B2FB0
/* 0B3B90 800B2F90 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B3B94 800B2F94 8CB80000 */  lw    $t8, ($a1)
/* 0B3B98 800B2F98 00000000 */  nop   
/* 0B3B9C 800B2F9C 1B000004 */  blez  $t8, .L800B2FB0
/* 0B3BA0 800B2FA0 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0B3BA4 800B2FA4 0C02CBEF */  jal   func_800B2FBC
/* 0B3BA8 800B2FA8 00C02025 */   move  $a0, $a2
/* 0B3BAC 800B2FAC 8FBF0014 */  lw    $ra, 0x14($sp)
.L800B2FB0:
/* 0B3BB0 800B2FB0 27BD0050 */  addiu $sp, $sp, 0x50
/* 0B3BB4 800B2FB4 03E00008 */  jr    $ra
/* 0B3BB8 800B2FB8 00000000 */   nop   

glabel func_800B2FBC
/* 0B3BBC 800B2FBC 27BDFFF8 */  addiu $sp, $sp, -8
/* 0B3BC0 800B2FC0 AFB00004 */  sw    $s0, 4($sp)
/* 0B3BC4 800B2FC4 848E002C */  lh    $t6, 0x2c($a0)
/* 0B3BC8 800B2FC8 24010080 */  li    $at, 128
/* 0B3BCC 800B2FCC 15C10008 */  bne   $t6, $at, .L800B2FF0
/* 0B3BD0 800B2FD0 2402FFFF */   li    $v0, -1
/* 0B3BD4 800B2FD4 8C8F0044 */  lw    $t7, 0x44($a0)
/* 0B3BD8 800B2FD8 00000000 */  nop   
/* 0B3BDC 800B2FDC 85E50000 */  lh    $a1, ($t7)
/* 0B3BE0 800B2FE0 00000000 */  nop   
/* 0B3BE4 800B2FE4 0005C200 */  sll   $t8, $a1, 8
/* 0B3BE8 800B2FE8 10000007 */  b     .L800B3008
/* 0B3BEC 800B2FEC 03002825 */   move  $a1, $t8
.L800B2FF0:
/* 0B3BF0 800B2FF0 8C990044 */  lw    $t9, 0x44($a0)
/* 0B3BF4 800B2FF4 00000000 */  nop   
/* 0B3BF8 800B2FF8 8F2E0000 */  lw    $t6, ($t9)
/* 0B3BFC 800B2FFC 00000000 */  nop   
/* 0B3C00 800B3000 95C50012 */  lhu   $a1, 0x12($t6)
/* 0B3C04 800B3004 00000000 */  nop   
.L800B3008:
/* 0B3C08 800B3008 8C870040 */  lw    $a3, 0x40($a0)
/* 0B3C0C 800B300C 3C0C8012 */  lui   $t4, %hi(D_80127C80) # $t4, 0x8012
/* 0B3C10 800B3010 258C7C80 */  addiu $t4, %lo(D_80127C80) # addiu $t4, $t4, 0x7c80
/* 0B3C14 800B3014 8D8B0000 */  lw    $t3, ($t4)
/* 0B3C18 800B3018 24030001 */  li    $v1, 1
/* 0B3C1C 800B301C 000B782A */  slt   $t7, $zero, $t3
/* 0B3C20 800B3020 30E60001 */  andi  $a2, $a3, 1
/* 0B3C24 800B3024 30E80002 */  andi  $t0, $a3, 2
/* 0B3C28 800B3028 30E90004 */  andi  $t1, $a3, 4
/* 0B3C2C 800B302C 11E00041 */  beqz  $t7, .L800B3134
/* 0B3C30 800B3030 30EA0008 */   andi  $t2, $a3, 8
/* 0B3C34 800B3034 2410FFF7 */  li    $s0, -9
/* 0B3C38 800B3038 240DFFFC */  li    $t5, -4
.L800B303C:
/* 0B3C3C 800B303C 84870018 */  lh    $a3, 0x18($a0)
/* 0B3C40 800B3040 848B001A */  lh    $t3, 0x1a($a0)
/* 0B3C44 800B3044 1540001D */  bnez  $t2, .L800B30BC
/* 0B3C48 800B3048 00EB7023 */   subu  $t6, $a3, $t3
/* 0B3C4C 800B304C 00EBC021 */  addu  $t8, $a3, $t3
/* 0B3C50 800B3050 A4980018 */  sh    $t8, 0x18($a0)
/* 0B3C54 800B3054 84870018 */  lh    $a3, 0x18($a0)
/* 0B3C58 800B3058 00000000 */  nop   
/* 0B3C5C 800B305C 00E5082A */  slt   $at, $a3, $a1
/* 0B3C60 800B3060 1420002D */  bnez  $at, .L800B3118
/* 0B3C64 800B3064 00000000 */   nop   
/* 0B3C68 800B3068 11000009 */  beqz  $t0, .L800B3090
/* 0B3C6C 800B306C 0005C840 */   sll   $t9, $a1, 1
/* 0B3C70 800B3070 8C980040 */  lw    $t8, 0x40($a0)
/* 0B3C74 800B3074 03277023 */  subu  $t6, $t9, $a3
/* 0B3C78 800B3078 25CFFFFF */  addiu $t7, $t6, -1
/* 0B3C7C 800B307C 37190008 */  ori   $t9, $t8, 8
/* 0B3C80 800B3080 A48F0018 */  sh    $t7, 0x18($a0)
/* 0B3C84 800B3084 240A0001 */  li    $t2, 1
/* 0B3C88 800B3088 10000023 */  b     .L800B3118
/* 0B3C8C 800B308C AC990040 */   sw    $t9, 0x40($a0)
.L800B3090:
/* 0B3C90 800B3090 11200004 */  beqz  $t1, .L800B30A4
/* 0B3C94 800B3094 24AFFFFF */   addiu $t7, $a1, -1
/* 0B3C98 800B3098 00E57023 */  subu  $t6, $a3, $a1
/* 0B3C9C 800B309C 1000001E */  b     .L800B3118
/* 0B3CA0 800B30A0 A48E0018 */   sh    $t6, 0x18($a0)
.L800B30A4:
/* 0B3CA4 800B30A4 8C980040 */  lw    $t8, 0x40($a0)
/* 0B3CA8 800B30A8 A48F0018 */  sh    $t7, 0x18($a0)
/* 0B3CAC 800B30AC 030DC824 */  and   $t9, $t8, $t5
/* 0B3CB0 800B30B0 00001025 */  move  $v0, $zero
/* 0B3CB4 800B30B4 10000018 */  b     .L800B3118
/* 0B3CB8 800B30B8 AC990040 */   sw    $t9, 0x40($a0)
.L800B30BC:
/* 0B3CBC 800B30BC A48E0018 */  sh    $t6, 0x18($a0)
/* 0B3CC0 800B30C0 84870018 */  lh    $a3, 0x18($a0)
/* 0B3CC4 800B30C4 00000000 */  nop   
/* 0B3CC8 800B30C8 04E10013 */  bgez  $a3, .L800B3118
/* 0B3CCC 800B30CC 00000000 */   nop   
/* 0B3CD0 800B30D0 1120000C */  beqz  $t1, .L800B3104
/* 0B3CD4 800B30D4 00000000 */   nop   
/* 0B3CD8 800B30D8 10C00008 */  beqz  $a2, .L800B30FC
/* 0B3CDC 800B30DC 00E57021 */   addu  $t6, $a3, $a1
/* 0B3CE0 800B30E0 8C980040 */  lw    $t8, 0x40($a0)
/* 0B3CE4 800B30E4 00077823 */  negu  $t7, $a3
/* 0B3CE8 800B30E8 0310C824 */  and   $t9, $t8, $s0
/* 0B3CEC 800B30EC A48F0018 */  sh    $t7, 0x18($a0)
/* 0B3CF0 800B30F0 00005025 */  move  $t2, $zero
/* 0B3CF4 800B30F4 10000008 */  b     .L800B3118
/* 0B3CF8 800B30F8 AC990040 */   sw    $t9, 0x40($a0)
.L800B30FC:
/* 0B3CFC 800B30FC 10000006 */  b     .L800B3118
/* 0B3D00 800B3100 A48E0018 */   sh    $t6, 0x18($a0)
.L800B3104:
/* 0B3D04 800B3104 8C8F0040 */  lw    $t7, 0x40($a0)
/* 0B3D08 800B3108 A4800018 */  sh    $zero, 0x18($a0)
/* 0B3D0C 800B310C 01EDC024 */  and   $t8, $t7, $t5
/* 0B3D10 800B3110 00001025 */  move  $v0, $zero
/* 0B3D14 800B3114 AC980040 */  sw    $t8, 0x40($a0)
.L800B3118:
/* 0B3D18 800B3118 8D990000 */  lw    $t9, ($t4)
/* 0B3D1C 800B311C 00000000 */  nop   
/* 0B3D20 800B3120 0079582A */  slt   $t3, $v1, $t9
/* 0B3D24 800B3124 11600003 */  beqz  $t3, .L800B3134
/* 0B3D28 800B3128 24630001 */   addiu $v1, $v1, 1
/* 0B3D2C 800B312C 1440FFC3 */  bnez  $v0, .L800B303C
/* 0B3D30 800B3130 00000000 */   nop   
.L800B3134:
/* 0B3D34 800B3134 8FB00004 */  lw    $s0, 4($sp)
/* 0B3D38 800B3138 03E00008 */  jr    $ra
/* 0B3D3C 800B313C 27BD0008 */   addiu $sp, $sp, 8

glabel func_800B3140
/* 0B3D40 800B3140 3C028012 */  lui   $v0, %hi(D_80127C80) # $v0, 0x8012
/* 0B3D44 800B3144 8C427C80 */  lw    $v0, %lo(D_80127C80)($v0)
/* 0B3D48 800B3148 00000000 */  nop   
/* 0B3D4C 800B314C 0002182A */  slt   $v1, $zero, $v0
/* 0B3D50 800B3150 10600023 */  beqz  $v1, .L800B31E0
/* 0B3D54 800B3154 2442FFFF */   addiu $v0, $v0, -1
.L800B3158:
/* 0B3D58 800B3158 C484004C */  lwc1  $f4, 0x4c($a0)
/* 0B3D5C 800B315C C486001C */  lwc1  $f6, 0x1c($a0)
/* 0B3D60 800B3160 C4800020 */  lwc1  $f0, 0x20($a0)
/* 0B3D64 800B3164 C48A0050 */  lwc1  $f10, 0x50($a0)
/* 0B3D68 800B3168 C4920068 */  lwc1  $f18, 0x68($a0)
/* 0B3D6C 800B316C 46062200 */  add.s $f8, $f4, $f6
/* 0B3D70 800B3170 C4860054 */  lwc1  $f6, 0x54($a0)
/* 0B3D74 800B3174 46005400 */  add.s $f16, $f10, $f0
/* 0B3D78 800B3178 E488004C */  swc1  $f8, 0x4c($a0)
/* 0B3D7C 800B317C 46120101 */  sub.s $f4, $f0, $f18
/* 0B3D80 800B3180 E4900050 */  swc1  $f16, 0x50($a0)
/* 0B3D84 800B3184 C4880024 */  lwc1  $f8, 0x24($a0)
/* 0B3D88 800B3188 848E0000 */  lh    $t6, ($a0)
/* 0B3D8C 800B318C 848F0062 */  lh    $t7, 0x62($a0)
/* 0B3D90 800B3190 84990002 */  lh    $t9, 2($a0)
/* 0B3D94 800B3194 84880064 */  lh    $t0, 0x64($a0)
/* 0B3D98 800B3198 848A0004 */  lh    $t2, 4($a0)
/* 0B3D9C 800B319C 848B0066 */  lh    $t3, 0x66($a0)
/* 0B3DA0 800B31A0 C4900008 */  lwc1  $f16, 8($a0)
/* 0B3DA4 800B31A4 C4920028 */  lwc1  $f18, 0x28($a0)
/* 0B3DA8 800B31A8 E4840020 */  swc1  $f4, 0x20($a0)
/* 0B3DAC 800B31AC 46083280 */  add.s $f10, $f6, $f8
/* 0B3DB0 800B31B0 0002182A */  slt   $v1, $zero, $v0
/* 0B3DB4 800B31B4 46128100 */  add.s $f4, $f16, $f18
/* 0B3DB8 800B31B8 01CFC021 */  addu  $t8, $t6, $t7
/* 0B3DBC 800B31BC 03284821 */  addu  $t1, $t9, $t0
/* 0B3DC0 800B31C0 014B6021 */  addu  $t4, $t2, $t3
/* 0B3DC4 800B31C4 E48A0054 */  swc1  $f10, 0x54($a0)
/* 0B3DC8 800B31C8 A4980000 */  sh    $t8, ($a0)
/* 0B3DCC 800B31CC A4890002 */  sh    $t1, 2($a0)
/* 0B3DD0 800B31D0 A48C0004 */  sh    $t4, 4($a0)
/* 0B3DD4 800B31D4 E4840008 */  swc1  $f4, 8($a0)
/* 0B3DD8 800B31D8 1460FFDF */  bnez  $v1, .L800B3158
/* 0B3DDC 800B31DC 2442FFFF */   addiu $v0, $v0, -1
.L800B31E0:
/* 0B3DE0 800B31E0 C486004C */  lwc1  $f6, 0x4c($a0)
/* 0B3DE4 800B31E4 C4880050 */  lwc1  $f8, 0x50($a0)
/* 0B3DE8 800B31E8 C48A0054 */  lwc1  $f10, 0x54($a0)
/* 0B3DEC 800B31EC 8C82003C */  lw    $v0, 0x3c($a0)
/* 0B3DF0 800B31F0 E486000C */  swc1  $f6, 0xc($a0)
/* 0B3DF4 800B31F4 E4880010 */  swc1  $f8, 0x10($a0)
/* 0B3DF8 800B31F8 1040000F */  beqz  $v0, .L800B3238
/* 0B3DFC 800B31FC E48A0014 */   swc1  $f10, 0x14($a0)
/* 0B3E00 800B3200 C490000C */  lwc1  $f16, 0xc($a0)
/* 0B3E04 800B3204 C452000C */  lwc1  $f18, 0xc($v0)
/* 0B3E08 800B3208 C4860010 */  lwc1  $f6, 0x10($a0)
/* 0B3E0C 800B320C 46128100 */  add.s $f4, $f16, $f18
/* 0B3E10 800B3210 C4900014 */  lwc1  $f16, 0x14($a0)
/* 0B3E14 800B3214 E484000C */  swc1  $f4, 0xc($a0)
/* 0B3E18 800B3218 C4480010 */  lwc1  $f8, 0x10($v0)
/* 0B3E1C 800B321C 00000000 */  nop   
/* 0B3E20 800B3220 46083280 */  add.s $f10, $f6, $f8
/* 0B3E24 800B3224 E48A0010 */  swc1  $f10, 0x10($a0)
/* 0B3E28 800B3228 C4520014 */  lwc1  $f18, 0x14($v0)
/* 0B3E2C 800B322C 00000000 */  nop   
/* 0B3E30 800B3230 46128100 */  add.s $f4, $f16, $f18
/* 0B3E34 800B3234 E4840014 */  swc1  $f4, 0x14($a0)
.L800B3238:
/* 0B3E38 800B3238 03E00008 */  jr    $ra
/* 0B3E3C 800B323C 00000000 */   nop   

glabel func_800B3240
/* 0B3E40 800B3240 3C028012 */  lui   $v0, %hi(D_80127C80) # $v0, 0x8012
/* 0B3E44 800B3244 8C427C80 */  lw    $v0, %lo(D_80127C80)($v0)
/* 0B3E48 800B3248 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0B3E4C 800B324C 0002182A */  slt   $v1, $zero, $v0
/* 0B3E50 800B3250 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B3E54 800B3254 10600015 */  beqz  $v1, .L800B32AC
/* 0B3E58 800B3258 2442FFFF */   addiu $v0, $v0, -1
/* 0B3E5C 800B325C 84850062 */  lh    $a1, 0x62($a0)
/* 0B3E60 800B3260 84860064 */  lh    $a2, 0x64($a0)
/* 0B3E64 800B3264 84870066 */  lh    $a3, 0x66($a0)
/* 0B3E68 800B3268 C4800028 */  lwc1  $f0, 0x28($a0)
/* 0B3E6C 800B326C 00000000 */  nop   
.L800B3270:
/* 0B3E70 800B3270 848E0000 */  lh    $t6, ($a0)
/* 0B3E74 800B3274 84980002 */  lh    $t8, 2($a0)
/* 0B3E78 800B3278 84880004 */  lh    $t0, 4($a0)
/* 0B3E7C 800B327C C4840008 */  lwc1  $f4, 8($a0)
/* 0B3E80 800B3280 0002182A */  slt   $v1, $zero, $v0
/* 0B3E84 800B3284 46002180 */  add.s $f6, $f4, $f0
/* 0B3E88 800B3288 01C57821 */  addu  $t7, $t6, $a1
/* 0B3E8C 800B328C 0306C821 */  addu  $t9, $t8, $a2
/* 0B3E90 800B3290 01074821 */  addu  $t1, $t0, $a3
/* 0B3E94 800B3294 A48F0000 */  sh    $t7, ($a0)
/* 0B3E98 800B3298 A4990002 */  sh    $t9, 2($a0)
/* 0B3E9C 800B329C A4890004 */  sh    $t1, 4($a0)
/* 0B3EA0 800B32A0 E4860008 */  swc1  $f6, 8($a0)
/* 0B3EA4 800B32A4 1460FFF2 */  bnez  $v1, .L800B3270
/* 0B3EA8 800B32A8 2442FFFF */   addiu $v0, $v0, -1
.L800B32AC:
/* 0B3EAC 800B32AC 44800000 */  mtc1  $zero, $f0
/* 0B3EB0 800B32B0 C4880058 */  lwc1  $f8, 0x58($a0)
/* 0B3EB4 800B32B4 E480000C */  swc1  $f0, 0xc($a0)
/* 0B3EB8 800B32B8 46004287 */  neg.s $f10, $f8
/* 0B3EBC 800B32BC E48A0010 */  swc1  $f10, 0x10($a0)
/* 0B3EC0 800B32C0 E4800014 */  swc1  $f0, 0x14($a0)
/* 0B3EC4 800B32C4 AFA40018 */  sw    $a0, 0x18($sp)
/* 0B3EC8 800B32C8 0C01C0C8 */  jal   func_80070320
/* 0B3ECC 800B32CC 2485000C */   addiu $a1, $a0, 0xc
/* 0B3ED0 800B32D0 8FA40018 */  lw    $a0, 0x18($sp)
/* 0B3ED4 800B32D4 00000000 */  nop   
/* 0B3ED8 800B32D8 C490000C */  lwc1  $f16, 0xc($a0)
/* 0B3EDC 800B32DC C492004C */  lwc1  $f18, 0x4c($a0)
/* 0B3EE0 800B32E0 C4860010 */  lwc1  $f6, 0x10($a0)
/* 0B3EE4 800B32E4 46128100 */  add.s $f4, $f16, $f18
/* 0B3EE8 800B32E8 C4880050 */  lwc1  $f8, 0x50($a0)
/* 0B3EEC 800B32EC C4920054 */  lwc1  $f18, 0x54($a0)
/* 0B3EF0 800B32F0 C4900014 */  lwc1  $f16, 0x14($a0)
/* 0B3EF4 800B32F4 8C82003C */  lw    $v0, 0x3c($a0)
/* 0B3EF8 800B32F8 E484000C */  swc1  $f4, 0xc($a0)
/* 0B3EFC 800B32FC 46083280 */  add.s $f10, $f6, $f8
/* 0B3F00 800B3300 46128100 */  add.s $f4, $f16, $f18
/* 0B3F04 800B3304 E48A0010 */  swc1  $f10, 0x10($a0)
/* 0B3F08 800B3308 1040000F */  beqz  $v0, .L800B3348
/* 0B3F0C 800B330C E4840014 */   swc1  $f4, 0x14($a0)
/* 0B3F10 800B3310 C486000C */  lwc1  $f6, 0xc($a0)
/* 0B3F14 800B3314 C448000C */  lwc1  $f8, 0xc($v0)
/* 0B3F18 800B3318 C4900010 */  lwc1  $f16, 0x10($a0)
/* 0B3F1C 800B331C 46083280 */  add.s $f10, $f6, $f8
/* 0B3F20 800B3320 C4860014 */  lwc1  $f6, 0x14($a0)
/* 0B3F24 800B3324 E48A000C */  swc1  $f10, 0xc($a0)
/* 0B3F28 800B3328 C4520010 */  lwc1  $f18, 0x10($v0)
/* 0B3F2C 800B332C 00000000 */  nop   
/* 0B3F30 800B3330 46128100 */  add.s $f4, $f16, $f18
/* 0B3F34 800B3334 E4840010 */  swc1  $f4, 0x10($a0)
/* 0B3F38 800B3338 C4480014 */  lwc1  $f8, 0x14($v0)
/* 0B3F3C 800B333C 00000000 */  nop   
/* 0B3F40 800B3340 46083280 */  add.s $f10, $f6, $f8
/* 0B3F44 800B3344 E48A0014 */  swc1  $f10, 0x14($a0)
.L800B3348:
/* 0B3F48 800B3348 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B3F4C 800B334C 27BD0018 */  addiu $sp, $sp, 0x18
/* 0B3F50 800B3350 03E00008 */  jr    $ra
/* 0B3F54 800B3354 00000000 */   nop   

glabel func_800B3358
/* 0B3F58 800B3358 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0B3F5C 800B335C AFB20024 */  sw    $s2, 0x24($sp)
/* 0B3F60 800B3360 3C128012 */  lui   $s2, %hi(D_80127C80) # $s2, 0x8012
/* 0B3F64 800B3364 26527C80 */  addiu $s2, %lo(D_80127C80) # addiu $s2, $s2, 0x7c80
/* 0B3F68 800B3368 8E420000 */  lw    $v0, ($s2)
/* 0B3F6C 800B336C AFB10020 */  sw    $s1, 0x20($sp)
/* 0B3F70 800B3370 AFB0001C */  sw    $s0, 0x1c($sp)
/* 0B3F74 800B3374 0002702A */  slt   $t6, $zero, $v0
/* 0B3F78 800B3378 00808025 */  move  $s0, $a0
/* 0B3F7C 800B337C AFBF002C */  sw    $ra, 0x2c($sp)
/* 0B3F80 800B3380 AFB30028 */  sw    $s3, 0x28($sp)
/* 0B3F84 800B3384 E7B50010 */  swc1  $f21, 0x10($sp)
/* 0B3F88 800B3388 E7B40014 */  swc1  $f20, 0x14($sp)
/* 0B3F8C 800B338C 11C0003F */  beqz  $t6, .L800B348C
/* 0B3F90 800B3390 24110001 */   li    $s1, 1
/* 0B3F94 800B3394 4480A000 */  mtc1  $zero, $f20
/* 0B3F98 800B3398 27B30038 */  addiu $s3, $sp, 0x38
.L800B339C:
/* 0B3F9C 800B339C C604000C */  lwc1  $f4, 0xc($s0)
/* 0B3FA0 800B33A0 C606001C */  lwc1  $f6, 0x1c($s0)
/* 0B3FA4 800B33A4 C60A0010 */  lwc1  $f10, 0x10($s0)
/* 0B3FA8 800B33A8 C6100020 */  lwc1  $f16, 0x20($s0)
/* 0B3FAC 800B33AC 46062200 */  add.s $f8, $f4, $f6
/* 0B3FB0 800B33B0 C6060024 */  lwc1  $f6, 0x24($s0)
/* 0B3FB4 800B33B4 46105480 */  add.s $f18, $f10, $f16
/* 0B3FB8 800B33B8 C6040014 */  lwc1  $f4, 0x14($s0)
/* 0B3FBC 800B33BC C6100028 */  lwc1  $f16, 0x28($s0)
/* 0B3FC0 800B33C0 C60A0008 */  lwc1  $f10, 8($s0)
/* 0B3FC4 800B33C4 860F0000 */  lh    $t7, ($s0)
/* 0B3FC8 800B33C8 86180062 */  lh    $t8, 0x62($s0)
/* 0B3FCC 800B33CC 86080002 */  lh    $t0, 2($s0)
/* 0B3FD0 800B33D0 86090064 */  lh    $t1, 0x64($s0)
/* 0B3FD4 800B33D4 860B0004 */  lh    $t3, 4($s0)
/* 0B3FD8 800B33D8 860C0066 */  lh    $t4, 0x66($s0)
/* 0B3FDC 800B33DC E608000C */  swc1  $f8, 0xc($s0)
/* 0B3FE0 800B33E0 E6120010 */  swc1  $f18, 0x10($s0)
/* 0B3FE4 800B33E4 46062200 */  add.s $f8, $f4, $f6
/* 0B3FE8 800B33E8 01F8C821 */  addu  $t9, $t7, $t8
/* 0B3FEC 800B33EC 46105480 */  add.s $f18, $f10, $f16
/* 0B3FF0 800B33F0 01095021 */  addu  $t2, $t0, $t1
/* 0B3FF4 800B33F4 016C6821 */  addu  $t5, $t3, $t4
/* 0B3FF8 800B33F8 E6080014 */  swc1  $f8, 0x14($s0)
/* 0B3FFC 800B33FC E6120008 */  swc1  $f18, 8($s0)
/* 0B4000 800B3400 A6190000 */  sh    $t9, ($s0)
/* 0B4004 800B3404 A60A0002 */  sh    $t2, 2($s0)
/* 0B4008 800B3408 A60D0004 */  sh    $t5, 4($s0)
/* 0B400C 800B340C E7B40038 */  swc1  $f20, 0x38($sp)
/* 0B4010 800B3410 C6040058 */  lwc1  $f4, 0x58($s0)
/* 0B4014 800B3414 E7B40040 */  swc1  $f20, 0x40($sp)
/* 0B4018 800B3418 46002187 */  neg.s $f6, $f4
/* 0B401C 800B341C E7A6003C */  swc1  $f6, 0x3c($sp)
/* 0B4020 800B3420 02002025 */  move  $a0, $s0
/* 0B4024 800B3424 0C01C0C8 */  jal   func_80070320
/* 0B4028 800B3428 02602825 */   move  $a1, $s3
/* 0B402C 800B342C C608001C */  lwc1  $f8, 0x1c($s0)
/* 0B4030 800B3430 C7AA0038 */  lwc1  $f10, 0x38($sp)
/* 0B4034 800B3434 C6120020 */  lwc1  $f18, 0x20($s0)
/* 0B4038 800B3438 460A4400 */  add.s $f16, $f8, $f10
/* 0B403C 800B343C C60A0068 */  lwc1  $f10, 0x68($s0)
/* 0B4040 800B3440 E610001C */  swc1  $f16, 0x1c($s0)
/* 0B4044 800B3444 C7A4003C */  lwc1  $f4, 0x3c($sp)
/* 0B4048 800B3448 00000000 */  nop   
/* 0B404C 800B344C 46049180 */  add.s $f6, $f18, $f4
/* 0B4050 800B3450 C6120024 */  lwc1  $f18, 0x24($s0)
/* 0B4054 800B3454 E6060020 */  swc1  $f6, 0x20($s0)
/* 0B4058 800B3458 C6080020 */  lwc1  $f8, 0x20($s0)
/* 0B405C 800B345C 00000000 */  nop   
/* 0B4060 800B3460 460A4401 */  sub.s $f16, $f8, $f10
/* 0B4064 800B3464 E6100020 */  swc1  $f16, 0x20($s0)
/* 0B4068 800B3468 C7A40040 */  lwc1  $f4, 0x40($sp)
/* 0B406C 800B346C 00000000 */  nop   
/* 0B4070 800B3470 46049180 */  add.s $f6, $f18, $f4
/* 0B4074 800B3474 E6060024 */  swc1  $f6, 0x24($s0)
/* 0B4078 800B3478 8E4E0000 */  lw    $t6, ($s2)
/* 0B407C 800B347C 00000000 */  nop   
/* 0B4080 800B3480 022E102A */  slt   $v0, $s1, $t6
/* 0B4084 800B3484 1440FFC5 */  bnez  $v0, .L800B339C
/* 0B4088 800B3488 26310001 */   addiu $s1, $s1, 1
.L800B348C:
/* 0B408C 800B348C 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0B4090 800B3490 C7B50010 */  lwc1  $f21, 0x10($sp)
/* 0B4094 800B3494 C7B40014 */  lwc1  $f20, 0x14($sp)
/* 0B4098 800B3498 8FB0001C */  lw    $s0, 0x1c($sp)
/* 0B409C 800B349C 8FB10020 */  lw    $s1, 0x20($sp)
/* 0B40A0 800B34A0 8FB20024 */  lw    $s2, 0x24($sp)
/* 0B40A4 800B34A4 8FB30028 */  lw    $s3, 0x28($sp)
/* 0B40A8 800B34A8 03E00008 */  jr    $ra
/* 0B40AC 800B34AC 27BD0048 */   addiu $sp, $sp, 0x48

glabel func_800B34B0
/* 0B40B0 800B34B0 3C058012 */  lui   $a1, %hi(D_80127C80) # $a1, 0x8012
/* 0B40B4 800B34B4 24A57C80 */  addiu $a1, %lo(D_80127C80) # addiu $a1, $a1, 0x7c80
/* 0B40B8 800B34B8 8CA20000 */  lw    $v0, ($a1)
/* 0B40BC 800B34BC 24030001 */  li    $v1, 1
/* 0B40C0 800B34C0 0002702A */  slt   $t6, $zero, $v0
/* 0B40C4 800B34C4 11C00025 */  beqz  $t6, .L800B355C
/* 0B40C8 800B34C8 00000000 */   nop   
.L800B34CC:
/* 0B40CC 800B34CC C484000C */  lwc1  $f4, 0xc($a0)
/* 0B40D0 800B34D0 C486001C */  lwc1  $f6, 0x1c($a0)
/* 0B40D4 800B34D4 C4800020 */  lwc1  $f0, 0x20($a0)
/* 0B40D8 800B34D8 C48A0010 */  lwc1  $f10, 0x10($a0)
/* 0B40DC 800B34DC C4920068 */  lwc1  $f18, 0x68($a0)
/* 0B40E0 800B34E0 46062200 */  add.s $f8, $f4, $f6
/* 0B40E4 800B34E4 C4860014 */  lwc1  $f6, 0x14($a0)
/* 0B40E8 800B34E8 46005400 */  add.s $f16, $f10, $f0
/* 0B40EC 800B34EC E488000C */  swc1  $f8, 0xc($a0)
/* 0B40F0 800B34F0 46120101 */  sub.s $f4, $f0, $f18
/* 0B40F4 800B34F4 E4900010 */  swc1  $f16, 0x10($a0)
/* 0B40F8 800B34F8 C4880024 */  lwc1  $f8, 0x24($a0)
/* 0B40FC 800B34FC C4900008 */  lwc1  $f16, 8($a0)
/* 0B4100 800B3500 C4920028 */  lwc1  $f18, 0x28($a0)
/* 0B4104 800B3504 848F0000 */  lh    $t7, ($a0)
/* 0B4108 800B3508 84980062 */  lh    $t8, 0x62($a0)
/* 0B410C 800B350C 84880002 */  lh    $t0, 2($a0)
/* 0B4110 800B3510 84890064 */  lh    $t1, 0x64($a0)
/* 0B4114 800B3514 848B0004 */  lh    $t3, 4($a0)
/* 0B4118 800B3518 848C0066 */  lh    $t4, 0x66($a0)
/* 0B411C 800B351C E4840020 */  swc1  $f4, 0x20($a0)
/* 0B4120 800B3520 46083280 */  add.s $f10, $f6, $f8
/* 0B4124 800B3524 01F8C821 */  addu  $t9, $t7, $t8
/* 0B4128 800B3528 46128100 */  add.s $f4, $f16, $f18
/* 0B412C 800B352C 01095021 */  addu  $t2, $t0, $t1
/* 0B4130 800B3530 016C6821 */  addu  $t5, $t3, $t4
/* 0B4134 800B3534 E48A0014 */  swc1  $f10, 0x14($a0)
/* 0B4138 800B3538 E4840008 */  swc1  $f4, 8($a0)
/* 0B413C 800B353C A4990000 */  sh    $t9, ($a0)
/* 0B4140 800B3540 A48A0002 */  sh    $t2, 2($a0)
/* 0B4144 800B3544 A48D0004 */  sh    $t5, 4($a0)
/* 0B4148 800B3548 8CAE0000 */  lw    $t6, ($a1)
/* 0B414C 800B354C 00000000 */  nop   
/* 0B4150 800B3550 006E102A */  slt   $v0, $v1, $t6
/* 0B4154 800B3554 1440FFDD */  bnez  $v0, .L800B34CC
/* 0B4158 800B3558 24630001 */   addiu $v1, $v1, 1
.L800B355C:
/* 0B415C 800B355C 03E00008 */  jr    $ra
/* 0B4160 800B3560 00000000 */   nop   

glabel func_800B3564
/* 0B4164 800B3564 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0B4168 800B3568 AFB30028 */  sw    $s3, 0x28($sp)
/* 0B416C 800B356C 3C138012 */  lui   $s3, %hi(D_80127C80) # $s3, 0x8012
/* 0B4170 800B3570 26737C80 */  addiu $s3, %lo(D_80127C80) # addiu $s3, $s3, 0x7c80
/* 0B4174 800B3574 8E620000 */  lw    $v0, ($s3)
/* 0B4178 800B3578 AFB10020 */  sw    $s1, 0x20($sp)
/* 0B417C 800B357C AFB0001C */  sw    $s0, 0x1c($sp)
/* 0B4180 800B3580 0002702A */  slt   $t6, $zero, $v0
/* 0B4184 800B3584 00808025 */  move  $s0, $a0
/* 0B4188 800B3588 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0B418C 800B358C AFB20024 */  sw    $s2, 0x24($sp)
/* 0B4190 800B3590 E7B50010 */  swc1  $f21, 0x10($sp)
/* 0B4194 800B3594 E7B40014 */  swc1  $f20, 0x14($sp)
/* 0B4198 800B3598 11C0002E */  beqz  $t6, .L800B3654
/* 0B419C 800B359C 24110001 */   li    $s1, 1
/* 0B41A0 800B35A0 4480A000 */  mtc1  $zero, $f20
/* 0B41A4 800B35A4 2492001C */  addiu $s2, $a0, 0x1c
.L800B35A8:
/* 0B41A8 800B35A8 C6040058 */  lwc1  $f4, 0x58($s0)
/* 0B41AC 800B35AC E614001C */  swc1  $f20, 0x1c($s0)
/* 0B41B0 800B35B0 46002187 */  neg.s $f6, $f4
/* 0B41B4 800B35B4 E6140020 */  swc1  $f20, 0x20($s0)
/* 0B41B8 800B35B8 E6060024 */  swc1  $f6, 0x24($s0)
/* 0B41BC 800B35BC 02002025 */  move  $a0, $s0
/* 0B41C0 800B35C0 0C01C124 */  jal   func_80070490
/* 0B41C4 800B35C4 02402825 */   move  $a1, $s2
/* 0B41C8 800B35C8 C608000C */  lwc1  $f8, 0xc($s0)
/* 0B41CC 800B35CC C60A001C */  lwc1  $f10, 0x1c($s0)
/* 0B41D0 800B35D0 C6120020 */  lwc1  $f18, 0x20($s0)
/* 0B41D4 800B35D4 C6040068 */  lwc1  $f4, 0x68($s0)
/* 0B41D8 800B35D8 460A4400 */  add.s $f16, $f8, $f10
/* 0B41DC 800B35DC C6080010 */  lwc1  $f8, 0x10($s0)
/* 0B41E0 800B35E0 46049181 */  sub.s $f6, $f18, $f4
/* 0B41E4 800B35E4 E610000C */  swc1  $f16, 0xc($s0)
/* 0B41E8 800B35E8 46064280 */  add.s $f10, $f8, $f6
/* 0B41EC 800B35EC C6100014 */  lwc1  $f16, 0x14($s0)
/* 0B41F0 800B35F0 C6120024 */  lwc1  $f18, 0x24($s0)
/* 0B41F4 800B35F4 C6060028 */  lwc1  $f6, 0x28($s0)
/* 0B41F8 800B35F8 C6080008 */  lwc1  $f8, 8($s0)
/* 0B41FC 800B35FC 860F0000 */  lh    $t7, ($s0)
/* 0B4200 800B3600 86180062 */  lh    $t8, 0x62($s0)
/* 0B4204 800B3604 86080002 */  lh    $t0, 2($s0)
/* 0B4208 800B3608 86090064 */  lh    $t1, 0x64($s0)
/* 0B420C 800B360C 860B0004 */  lh    $t3, 4($s0)
/* 0B4210 800B3610 860C0066 */  lh    $t4, 0x66($s0)
/* 0B4214 800B3614 E60A0010 */  swc1  $f10, 0x10($s0)
/* 0B4218 800B3618 46128100 */  add.s $f4, $f16, $f18
/* 0B421C 800B361C 01F8C821 */  addu  $t9, $t7, $t8
/* 0B4220 800B3620 46064280 */  add.s $f10, $f8, $f6
/* 0B4224 800B3624 01095021 */  addu  $t2, $t0, $t1
/* 0B4228 800B3628 016C6821 */  addu  $t5, $t3, $t4
/* 0B422C 800B362C E6040014 */  swc1  $f4, 0x14($s0)
/* 0B4230 800B3630 E60A0008 */  swc1  $f10, 8($s0)
/* 0B4234 800B3634 A6190000 */  sh    $t9, ($s0)
/* 0B4238 800B3638 A60A0002 */  sh    $t2, 2($s0)
/* 0B423C 800B363C A60D0004 */  sh    $t5, 4($s0)
/* 0B4240 800B3640 8E6E0000 */  lw    $t6, ($s3)
/* 0B4244 800B3644 00000000 */  nop   
/* 0B4248 800B3648 022E102A */  slt   $v0, $s1, $t6
/* 0B424C 800B364C 1440FFD6 */  bnez  $v0, .L800B35A8
/* 0B4250 800B3650 26310001 */   addiu $s1, $s1, 1
.L800B3654:
/* 0B4254 800B3654 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0B4258 800B3658 C7B50010 */  lwc1  $f21, 0x10($sp)
/* 0B425C 800B365C C7B40014 */  lwc1  $f20, 0x14($sp)
/* 0B4260 800B3660 8FB0001C */  lw    $s0, 0x1c($sp)
/* 0B4264 800B3664 8FB10020 */  lw    $s1, 0x20($sp)
/* 0B4268 800B3668 8FB20024 */  lw    $s2, 0x24($sp)
/* 0B426C 800B366C 8FB30028 */  lw    $s3, 0x28($sp)
/* 0B4270 800B3670 03E00008 */  jr    $ra
/* 0B4274 800B3674 27BD0030 */   addiu $sp, $sp, 0x30

/* 0B4278 800B3678 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0B427C 800B367C AFB20024 */  sw    $s2, 0x24($sp)
/* 0B4280 800B3680 AFB10020 */  sw    $s1, 0x20($sp)
/* 0B4284 800B3684 00808825 */  move  $s1, $a0
/* 0B4288 800B3688 00A09025 */  move  $s2, $a1
/* 0B428C 800B368C AFBF002C */  sw    $ra, 0x2c($sp)
/* 0B4290 800B3690 AFB30028 */  sw    $s3, 0x28($sp)
/* 0B4294 800B3694 00C09825 */  move  $s3, $a2
/* 0B4298 800B3698 AFB0001C */  sw    $s0, 0x1c($sp)
/* 0B429C 800B369C 27A50034 */  addiu $a1, $sp, 0x34
/* 0B42A0 800B36A0 0C003A62 */  jal   func_8000E988
/* 0B42A4 800B36A4 27A40038 */   addiu $a0, $sp, 0x38
/* 0B42A8 800B36A8 8FA30038 */  lw    $v1, 0x38($sp)
/* 0B42AC 800B36AC 8FAE0034 */  lw    $t6, 0x34($sp)
/* 0B42B0 800B36B0 00408025 */  move  $s0, $v0
/* 0B42B4 800B36B4 006E082A */  slt   $at, $v1, $t6
/* 0B42B8 800B36B8 1020001B */  beqz  $at, .L800B3728
/* 0B42BC 800B36BC 8FBF002C */   lw    $ra, 0x2c($sp)
.L800B36C0:
/* 0B42C0 800B36C0 8FAF0038 */  lw    $t7, 0x38($sp)
/* 0B42C4 800B36C4 00000000 */  nop   
/* 0B42C8 800B36C8 000FC080 */  sll   $t8, $t7, 2
/* 0B42CC 800B36CC 0218C821 */  addu  $t9, $s0, $t8
/* 0B42D0 800B36D0 8F240000 */  lw    $a0, ($t9)
/* 0B42D4 800B36D4 00000000 */  nop   
/* 0B42D8 800B36D8 84880006 */  lh    $t0, 6($a0)
/* 0B42DC 800B36DC 00000000 */  nop   
/* 0B42E0 800B36E0 31098000 */  andi  $t1, $t0, 0x8000
/* 0B42E4 800B36E4 1120000A */  beqz  $t1, .L800B3710
/* 0B42E8 800B36E8 8FA30038 */   lw    $v1, 0x38($sp)
/* 0B42EC 800B36EC 8C8A0040 */  lw    $t2, 0x40($a0)
/* 0B42F0 800B36F0 02202825 */  move  $a1, $s1
/* 0B42F4 800B36F4 314B8000 */  andi  $t3, $t2, 0x8000
/* 0B42F8 800B36F8 11600004 */  beqz  $t3, .L800B370C
/* 0B42FC 800B36FC 02403025 */   move  $a2, $s2
/* 0B4300 800B3700 02603825 */  move  $a3, $s3
/* 0B4304 800B3704 0C02CDD0 */  jal   func_800B3740
/* 0B4308 800B3708 AFA00010 */   sw    $zero, 0x10($sp)
.L800B370C:
/* 0B430C 800B370C 8FA30038 */  lw    $v1, 0x38($sp)
.L800B3710:
/* 0B4310 800B3710 8FAC0034 */  lw    $t4, 0x34($sp)
/* 0B4314 800B3714 24630001 */  addiu $v1, $v1, 1
/* 0B4318 800B3718 006C082A */  slt   $at, $v1, $t4
/* 0B431C 800B371C 1420FFE8 */  bnez  $at, .L800B36C0
/* 0B4320 800B3720 AFA30038 */   sw    $v1, 0x38($sp)
/* 0B4324 800B3724 8FBF002C */  lw    $ra, 0x2c($sp)
.L800B3728:
/* 0B4328 800B3728 8FB0001C */  lw    $s0, 0x1c($sp)
/* 0B432C 800B372C 8FB10020 */  lw    $s1, 0x20($sp)
/* 0B4330 800B3730 8FB20024 */  lw    $s2, 0x24($sp)
/* 0B4334 800B3734 8FB30028 */  lw    $s3, 0x28($sp)
/* 0B4338 800B3738 03E00008 */  jr    $ra
/* 0B433C 800B373C 27BD0048 */   addiu $sp, $sp, 0x48

glabel func_800B3740
/* 0B4340 800B3740 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 0B4344 800B3744 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0B4348 800B3748 AFB10020 */  sw    $s1, 0x20($sp)
/* 0B434C 800B374C AFB0001C */  sw    $s0, 0x1c($sp)
/* 0B4350 800B3750 AFA60048 */  sw    $a2, 0x48($sp)
/* 0B4354 800B3754 AFA7004C */  sw    $a3, 0x4c($sp)
/* 0B4358 800B3758 8C8E0040 */  lw    $t6, 0x40($a0)
/* 0B435C 800B375C 8FAF0050 */  lw    $t7, 0x50($sp)
/* 0B4360 800B3760 00A08025 */  move  $s0, $a1
/* 0B4364 800B3764 01CFC024 */  and   $t8, $t6, $t7
/* 0B4368 800B3768 00808825 */  move  $s1, $a0
/* 0B436C 800B376C 13000007 */  beqz  $t8, .L800B378C
/* 0B4370 800B3770 240B000A */   li    $t3, 10
/* 0B4374 800B3774 3C19800E */  lui   $t9, %hi(D_800E2CDC) # $t9, 0x800e
/* 0B4378 800B3778 8F392CDC */  lw    $t9, %lo(D_800E2CDC)($t9)
/* 0B437C 800B377C 00000000 */  nop   
/* 0B4380 800B3780 2B210200 */  slti  $at, $t9, 0x200
/* 0B4384 800B3784 142001B2 */  bnez  $at, .L800B3E50
/* 0B4388 800B3788 00000000 */   nop   
.L800B378C:
/* 0B438C 800B378C 862A005C */  lh    $t2, 0x5c($s1)
/* 0B4390 800B3790 00000000 */  nop   
/* 0B4394 800B3794 000A6203 */  sra   $t4, $t2, 8
/* 0B4398 800B3798 318A00FF */  andi  $t2, $t4, 0xff
/* 0B439C 800B379C 194001AC */  blez  $t2, .L800B3E50
/* 0B43A0 800B37A0 00000000 */   nop   
/* 0B43A4 800B37A4 8623002C */  lh    $v1, 0x2c($s1)
/* 0B43A8 800B37A8 24050004 */  li    $a1, 4
/* 0B43AC 800B37AC 10A300B3 */  beq   $a1, $v1, .L800B3A7C
/* 0B43B0 800B37B0 24010003 */   li    $at, 3
/* 0B43B4 800B37B4 106100B1 */  beq   $v1, $at, .L800B3A7C
/* 0B43B8 800B37B8 240900FF */   li    $t1, 255
/* 0B43BC 800B37BC 8E020000 */  lw    $v0, ($s0)
/* 0B43C0 800B37C0 3C0FFB00 */  lui   $t7, 0xfb00
/* 0B43C4 800B37C4 244E0008 */  addiu $t6, $v0, 8
/* 0B43C8 800B37C8 AE0E0000 */  sw    $t6, ($s0)
/* 0B43CC 800B37CC AC4F0000 */  sw    $t7, ($v0)
/* 0B43D0 800B37D0 922E006D */  lbu   $t6, 0x6d($s1)
/* 0B43D4 800B37D4 9239006C */  lbu   $t9, 0x6c($s1)
/* 0B43D8 800B37D8 922D006E */  lbu   $t5, 0x6e($s1)
/* 0B43DC 800B37DC 000E7C00 */  sll   $t7, $t6, 0x10
/* 0B43E0 800B37E0 00196600 */  sll   $t4, $t9, 0x18
/* 0B43E4 800B37E4 9239006F */  lbu   $t9, 0x6f($s1)
/* 0B43E8 800B37E8 018FC025 */  or    $t8, $t4, $t7
/* 0B43EC 800B37EC 000D7200 */  sll   $t6, $t5, 8
/* 0B43F0 800B37F0 030E6025 */  or    $t4, $t8, $t6
/* 0B43F4 800B37F4 01996825 */  or    $t5, $t4, $t9
/* 0B43F8 800B37F8 11490012 */  beq   $t2, $t1, .L800B3844
/* 0B43FC 800B37FC AC4D0004 */   sw    $t5, 4($v0)
/* 0B4400 800B3800 8E040000 */  lw    $a0, ($s0)
/* 0B4404 800B3804 3C0EFA00 */  lui   $t6, 0xfa00
/* 0B4408 800B3808 24980008 */  addiu $t8, $a0, 8
/* 0B440C 800B380C AE180000 */  sw    $t8, ($s0)
/* 0B4410 800B3810 AC8E0000 */  sw    $t6, ($a0)
/* 0B4414 800B3814 8623004A */  lh    $v1, 0x4a($s1)
/* 0B4418 800B3818 240B010E */  li    $t3, 270
/* 0B441C 800B381C 306F00FF */  andi  $t7, $v1, 0xff
/* 0B4420 800B3820 000F6600 */  sll   $t4, $t7, 0x18
/* 0B4424 800B3824 000FCC00 */  sll   $t9, $t7, 0x10
/* 0B4428 800B3828 000FC200 */  sll   $t8, $t7, 8
/* 0B442C 800B382C 01996825 */  or    $t5, $t4, $t9
/* 0B4430 800B3830 01B87025 */  or    $t6, $t5, $t8
/* 0B4434 800B3834 314F00FF */  andi  $t7, $t2, 0xff
/* 0B4438 800B3838 01CF6025 */  or    $t4, $t6, $t7
/* 0B443C 800B383C 10000008 */  b     .L800B3860
/* 0B4440 800B3840 AC8C0004 */   sw    $t4, 4($a0)
.L800B3844:
/* 0B4444 800B3844 8E020000 */  lw    $v0, ($s0)
/* 0B4448 800B3848 3C0DFA00 */  lui   $t5, 0xfa00
/* 0B444C 800B384C 24590008 */  addiu $t9, $v0, 8
/* 0B4450 800B3850 AE190000 */  sw    $t9, ($s0)
/* 0B4454 800B3854 2418FFFF */  li    $t8, -1
/* 0B4458 800B3858 AC580004 */  sw    $t8, 4($v0)
/* 0B445C 800B385C AC4D0000 */  sw    $t5, ($v0)
.L800B3860:
/* 0B4460 800B3860 862E002C */  lh    $t6, 0x2c($s1)
/* 0B4464 800B3864 24010080 */  li    $at, 128
/* 0B4468 800B3868 15C10026 */  bne   $t6, $at, .L800B3904
/* 0B446C 800B386C 00000000 */   nop   
/* 0B4470 800B3870 86230018 */  lh    $v1, 0x18($s1)
/* 0B4474 800B3874 8E280044 */  lw    $t0, 0x44($s1)
/* 0B4478 800B3878 00037A03 */  sra   $t7, $v1, 8
/* 0B447C 800B387C A62F0018 */  sh    $t7, 0x18($s1)
/* 0B4480 800B3880 862C0018 */  lh    $t4, 0x18($s1)
/* 0B4484 800B3884 850D0000 */  lh    $t5, ($t0)
/* 0B4488 800B3888 01890019 */  multu $t4, $t1
/* 0B448C 800B388C 00601025 */  move  $v0, $v1
/* 0B4490 800B3890 02002025 */  move  $a0, $s0
/* 0B4494 800B3894 02203825 */  move  $a3, $s1
/* 0B4498 800B3898 0000C812 */  mflo  $t9
/* 0B449C 800B389C 00000000 */  nop   
/* 0B44A0 800B38A0 00000000 */  nop   
/* 0B44A4 800B38A4 032D001A */  div   $zero, $t9, $t5
/* 0B44A8 800B38A8 15A00002 */  bnez  $t5, .L800B38B4
/* 0B44AC 800B38AC 00000000 */   nop   
/* 0B44B0 800B38B0 0007000D */  break 7
.L800B38B4:
/* 0B44B4 800B38B4 2401FFFF */  li    $at, -1
/* 0B44B8 800B38B8 15A10004 */  bne   $t5, $at, .L800B38CC
/* 0B44BC 800B38BC 3C018000 */   lui   $at, 0x8000
/* 0B44C0 800B38C0 17210002 */  bne   $t9, $at, .L800B38CC
/* 0B44C4 800B38C4 00000000 */   nop   
/* 0B44C8 800B38C8 0006000D */  break 6
.L800B38CC:
/* 0B44CC 800B38CC 0000C012 */  mflo  $t8
/* 0B44D0 800B38D0 A6380018 */  sh    $t8, 0x18($s1)
/* 0B44D4 800B38D4 8FA6004C */  lw    $a2, 0x4c($sp)
/* 0B44D8 800B38D8 8FA50048 */  lw    $a1, 0x48($sp)
/* 0B44DC 800B38DC AFAA0038 */  sw    $t2, 0x38($sp)
/* 0B44E0 800B38E0 AFA20034 */  sw    $v0, 0x34($sp)
/* 0B44E4 800B38E4 AFAB0014 */  sw    $t3, 0x14($sp)
/* 0B44E8 800B38E8 0C01A145 */  jal   func_80068514
/* 0B44EC 800B38EC AFA80010 */   sw    $t0, 0x10($sp)
/* 0B44F0 800B38F0 8FA20034 */  lw    $v0, 0x34($sp)
/* 0B44F4 800B38F4 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0B44F8 800B38F8 240900FF */  li    $t1, 255
/* 0B44FC 800B38FC 10000048 */  b     .L800B3A20
/* 0B4500 800B3900 A6220018 */   sh    $v0, 0x18($s1)
.L800B3904:
/* 0B4504 800B3904 8E230044 */  lw    $v1, 0x44($s1)
/* 0B4508 800B3908 8FA50048 */  lw    $a1, 0x48($sp)
/* 0B450C 800B390C 8C6E0000 */  lw    $t6, ($v1)
/* 0B4510 800B3910 02002025 */  move  $a0, $s0
/* 0B4514 800B3914 11C00042 */  beqz  $t6, .L800B3A20
/* 0B4518 800B3918 02203025 */   move  $a2, $s1
/* 0B451C 800B391C 44802000 */  mtc1  $zero, $f4
/* 0B4520 800B3920 3C073F80 */  lui   $a3, 0x3f80
/* 0B4524 800B3924 AFA30030 */  sw    $v1, 0x30($sp)
/* 0B4528 800B3928 AFAA0038 */  sw    $t2, 0x38($sp)
/* 0B452C 800B392C AFAB003C */  sw    $t3, 0x3c($sp)
/* 0B4530 800B3930 0C01A521 */  jal   func_80069484
/* 0B4534 800B3934 E7A40010 */   swc1  $f4, 0x10($sp)
/* 0B4538 800B3938 8FA30030 */  lw    $v1, 0x30($sp)
/* 0B453C 800B393C 86270018 */  lh    $a3, 0x18($s1)
/* 0B4540 800B3940 8FA6003C */  lw    $a2, 0x3c($sp)
/* 0B4544 800B3944 8C650000 */  lw    $a1, ($v1)
/* 0B4548 800B3948 00077A00 */  sll   $t7, $a3, 8
/* 0B454C 800B394C 01E03825 */  move  $a3, $t7
/* 0B4550 800B3950 0C01ED3A */  jal   func_8007B4E8
/* 0B4554 800B3954 02002025 */   move  $a0, $s0
/* 0B4558 800B3958 8E020000 */  lw    $v0, ($s0)
/* 0B455C 800B395C 8FA30030 */  lw    $v1, 0x30($sp)
/* 0B4560 800B3960 244C0008 */  addiu $t4, $v0, 8
/* 0B4564 800B3964 AE0C0000 */  sw    $t4, ($s0)
/* 0B4568 800B3968 8C780008 */  lw    $t8, 8($v1)
/* 0B456C 800B396C 84650004 */  lh    $a1, 4($v1)
/* 0B4570 800B3970 3C078000 */  lui   $a3, 0x8000
/* 0B4574 800B3974 03077021 */  addu  $t6, $t8, $a3
/* 0B4578 800B3978 24B9FFFF */  addiu $t9, $a1, -1
/* 0B457C 800B397C 001968C0 */  sll   $t5, $t9, 3
/* 0B4580 800B3980 31CF0006 */  andi  $t7, $t6, 6
/* 0B4584 800B3984 01AF6025 */  or    $t4, $t5, $t7
/* 0B4588 800B3988 319900FF */  andi  $t9, $t4, 0xff
/* 0B458C 800B398C 000568C0 */  sll   $t5, $a1, 3
/* 0B4590 800B3990 0019C400 */  sll   $t8, $t9, 0x10
/* 0B4594 800B3994 01A57821 */  addu  $t7, $t5, $a1
/* 0B4598 800B3998 000F6040 */  sll   $t4, $t7, 1
/* 0B459C 800B399C 3C010400 */  lui   $at, 0x400
/* 0B45A0 800B39A0 03017025 */  or    $t6, $t8, $at
/* 0B45A4 800B39A4 25990008 */  addiu $t9, $t4, 8
/* 0B45A8 800B39A8 3338FFFF */  andi  $t8, $t9, 0xffff
/* 0B45AC 800B39AC 01D86825 */  or    $t5, $t6, $t8
/* 0B45B0 800B39B0 AC4D0000 */  sw    $t5, ($v0)
/* 0B45B4 800B39B4 8C6F0008 */  lw    $t7, 8($v1)
/* 0B45B8 800B39B8 3C010500 */  lui   $at, 0x500
/* 0B45BC 800B39BC 01E76021 */  addu  $t4, $t7, $a3
/* 0B45C0 800B39C0 AC4C0004 */  sw    $t4, 4($v0)
/* 0B45C4 800B39C4 8E020000 */  lw    $v0, ($s0)
/* 0B45C8 800B39C8 02002025 */  move  $a0, $s0
/* 0B45CC 800B39CC 24590008 */  addiu $t9, $v0, 8
/* 0B45D0 800B39D0 AE190000 */  sw    $t9, ($s0)
/* 0B45D4 800B39D4 84660006 */  lh    $a2, 6($v1)
/* 0B45D8 800B39D8 00000000 */  nop   
/* 0B45DC 800B39DC 24CEFFFF */  addiu $t6, $a2, -1
/* 0B45E0 800B39E0 000EC100 */  sll   $t8, $t6, 4
/* 0B45E4 800B39E4 370D0001 */  ori   $t5, $t8, 1
/* 0B45E8 800B39E8 31AF00FF */  andi  $t7, $t5, 0xff
/* 0B45EC 800B39EC 000F6400 */  sll   $t4, $t7, 0x10
/* 0B45F0 800B39F0 00067100 */  sll   $t6, $a2, 4
/* 0B45F4 800B39F4 31D8FFFF */  andi  $t8, $t6, 0xffff
/* 0B45F8 800B39F8 0181C825 */  or    $t9, $t4, $at
/* 0B45FC 800B39FC 03386825 */  or    $t5, $t9, $t8
/* 0B4600 800B3A00 AC4D0000 */  sw    $t5, ($v0)
/* 0B4604 800B3A04 8C6F000C */  lw    $t7, 0xc($v1)
/* 0B4608 800B3A08 00000000 */  nop   
/* 0B460C 800B3A0C 01E76021 */  addu  $t4, $t7, $a3
/* 0B4610 800B3A10 0C01A690 */  jal   func_80069A40
/* 0B4614 800B3A14 AC4C0004 */   sw    $t4, 4($v0)
/* 0B4618 800B3A18 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0B461C 800B3A1C 240900FF */  li    $t1, 255
.L800B3A20:
/* 0B4620 800B3A20 15490005 */  bne   $t2, $t1, .L800B3A38
/* 0B4624 800B3A24 3C18FA00 */   lui   $t8, 0xfa00
/* 0B4628 800B3A28 862E004A */  lh    $t6, 0x4a($s1)
/* 0B462C 800B3A2C 00000000 */  nop   
/* 0B4630 800B3A30 112E0007 */  beq   $t1, $t6, .L800B3A50
/* 0B4634 800B3A34 00000000 */   nop   
.L800B3A38:
/* 0B4638 800B3A38 8E020000 */  lw    $v0, ($s0)
/* 0B463C 800B3A3C 240DFFFF */  li    $t5, -1
/* 0B4640 800B3A40 24590008 */  addiu $t9, $v0, 8
/* 0B4644 800B3A44 AE190000 */  sw    $t9, ($s0)
/* 0B4648 800B3A48 AC4D0004 */  sw    $t5, 4($v0)
/* 0B464C 800B3A4C AC580000 */  sw    $t8, ($v0)
.L800B3A50:
/* 0B4650 800B3A50 922F006F */  lbu   $t7, 0x6f($s1)
/* 0B4654 800B3A54 3C0EFB00 */  lui   $t6, 0xfb00
/* 0B4658 800B3A58 11E000FE */  beqz  $t7, .L800B3E54
/* 0B465C 800B3A5C 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0B4660 800B3A60 8E020000 */  lw    $v0, ($s0)
/* 0B4664 800B3A64 2419FF00 */  li    $t9, -256
/* 0B4668 800B3A68 244C0008 */  addiu $t4, $v0, 8
/* 0B466C 800B3A6C AE0C0000 */  sw    $t4, ($s0)
/* 0B4670 800B3A70 AC590004 */  sw    $t9, 4($v0)
/* 0B4674 800B3A74 100000F6 */  b     .L800B3E50
/* 0B4678 800B3A78 AC4E0000 */   sw    $t6, ($v0)
.L800B3A7C:
/* 0B467C 800B3A7C 8E020000 */  lw    $v0, ($s0)
/* 0B4680 800B3A80 3C0DFB00 */  lui   $t5, 0xfb00
/* 0B4684 800B3A84 24580008 */  addiu $t8, $v0, 8
/* 0B4688 800B3A88 AE180000 */  sw    $t8, ($s0)
/* 0B468C 800B3A8C 240FFF00 */  li    $t7, -256
/* 0B4690 800B3A90 AC4F0004 */  sw    $t7, 4($v0)
/* 0B4694 800B3A94 AC4D0000 */  sw    $t5, ($v0)
/* 0B4698 800B3A98 8623002C */  lh    $v1, 0x2c($s1)
/* 0B469C 800B3A9C 24010003 */  li    $at, 3
/* 0B46A0 800B3AA0 14A30063 */  bne   $a1, $v1, .L800B3C30
/* 0B46A4 800B3AA4 00000000 */   nop   
/* 0B46A8 800B3AA8 862C003A */  lh    $t4, 0x3a($s1)
/* 0B46AC 800B3AAC 00000000 */  nop   
/* 0B46B0 800B3AB0 198000E8 */  blez  $t4, .L800B3E54
/* 0B46B4 800B3AB4 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0B46B8 800B3AB8 8E020000 */  lw    $v0, ($s0)
/* 0B46BC 800B3ABC 3C19FA00 */  lui   $t9, 0xfa00
/* 0B46C0 800B3AC0 244E0008 */  addiu $t6, $v0, 8
/* 0B46C4 800B3AC4 AE0E0000 */  sw    $t6, ($s0)
/* 0B46C8 800B3AC8 AC590000 */  sw    $t9, ($v0)
/* 0B46CC 800B3ACC 8623004A */  lh    $v1, 0x4a($s1)
/* 0B46D0 800B3AD0 00000000 */  nop   
/* 0B46D4 800B3AD4 307800FF */  andi  $t8, $v1, 0xff
/* 0B46D8 800B3AD8 00186E00 */  sll   $t5, $t8, 0x18
/* 0B46DC 800B3ADC 00187C00 */  sll   $t7, $t8, 0x10
/* 0B46E0 800B3AE0 01AF6025 */  or    $t4, $t5, $t7
/* 0B46E4 800B3AE4 00187200 */  sll   $t6, $t8, 8
/* 0B46E8 800B3AE8 018EC825 */  or    $t9, $t4, $t6
/* 0B46EC 800B3AEC 373800FF */  ori   $t8, $t9, 0xff
/* 0B46F0 800B3AF0 AC580004 */  sw    $t8, 4($v0)
/* 0B46F4 800B3AF4 822D0077 */  lb    $t5, 0x77($s1)
/* 0B46F8 800B3AF8 00000000 */  nop   
/* 0B46FC 800B3AFC 15A00003 */  bnez  $t5, .L800B3B0C
/* 0B4700 800B3B00 00000000 */   nop   
/* 0B4704 800B3B04 0C02CF99 */  jal   func_800B3E64
/* 0B4708 800B3B08 02202025 */   move  $a0, $s1
.L800B3B0C:
/* 0B470C 800B3B0C 92220075 */  lbu   $v0, 0x75($s1)
/* 0B4710 800B3B10 8E230044 */  lw    $v1, 0x44($s1)
/* 0B4714 800B3B14 000278C0 */  sll   $t7, $v0, 3
/* 0B4718 800B3B18 000F7080 */  sll   $t6, $t7, 2
/* 0B471C 800B3B1C 8C6C0008 */  lw    $t4, 8($v1)
/* 0B4720 800B3B20 01CF7021 */  addu  $t6, $t6, $t7
/* 0B4724 800B3B24 000E7040 */  sll   $t6, $t6, 1
/* 0B4728 800B3B28 018EC821 */  addu  $t9, $t4, $t6
/* 0B472C 800B3B2C AFB9002C */  sw    $t9, 0x2c($sp)
/* 0B4730 800B3B30 86270018 */  lh    $a3, 0x18($s1)
/* 0B4734 800B3B34 3C060800 */  lui   $a2, (0x0800010B >> 16) # lui $a2, 0x800
/* 0B4738 800B3B38 8C650000 */  lw    $a1, ($v1)
/* 0B473C 800B3B3C 0007C200 */  sll   $t8, $a3, 8
/* 0B4740 800B3B40 03003825 */  move  $a3, $t8
/* 0B4744 800B3B44 34C6010B */  ori   $a2, (0x0800010B & 0xFFFF) # ori $a2, $a2, 0x10b
/* 0B4748 800B3B48 02002025 */  move  $a0, $s0
/* 0B474C 800B3B4C 0C01ED3A */  jal   func_8007B4E8
/* 0B4750 800B3B50 AFA30030 */   sw    $v1, 0x30($sp)
/* 0B4754 800B3B54 8E020000 */  lw    $v0, ($s0)
/* 0B4758 800B3B58 8FA30030 */  lw    $v1, 0x30($sp)
/* 0B475C 800B3B5C 244D0008 */  addiu $t5, $v0, 8
/* 0B4760 800B3B60 AE0D0000 */  sw    $t5, ($s0)
/* 0B4764 800B3B64 8FAF002C */  lw    $t7, 0x2c($sp)
/* 0B4768 800B3B68 84650004 */  lh    $a1, 4($v1)
/* 0B476C 800B3B6C 3C078000 */  lui   $a3, 0x8000
/* 0B4770 800B3B70 01E74021 */  addu  $t0, $t7, $a3
/* 0B4774 800B3B74 24ACFFFF */  addiu $t4, $a1, -1
/* 0B4778 800B3B78 000C70C0 */  sll   $t6, $t4, 3
/* 0B477C 800B3B7C 31190006 */  andi  $t9, $t0, 6
/* 0B4780 800B3B80 01D9C025 */  or    $t8, $t6, $t9
/* 0B4784 800B3B84 330D00FF */  andi  $t5, $t8, 0xff
/* 0B4788 800B3B88 000570C0 */  sll   $t6, $a1, 3
/* 0B478C 800B3B8C 000D7C00 */  sll   $t7, $t5, 0x10
/* 0B4790 800B3B90 01C5C821 */  addu  $t9, $t6, $a1
/* 0B4794 800B3B94 0019C040 */  sll   $t8, $t9, 1
/* 0B4798 800B3B98 3C010400 */  lui   $at, 0x400
/* 0B479C 800B3B9C 01E16025 */  or    $t4, $t7, $at
/* 0B47A0 800B3BA0 270D0008 */  addiu $t5, $t8, 8
/* 0B47A4 800B3BA4 31AFFFFF */  andi  $t7, $t5, 0xffff
/* 0B47A8 800B3BA8 018F7025 */  or    $t6, $t4, $t7
/* 0B47AC 800B3BAC AC4E0000 */  sw    $t6, ($v0)
/* 0B47B0 800B3BB0 AC480004 */  sw    $t0, 4($v0)
/* 0B47B4 800B3BB4 8E020000 */  lw    $v0, ($s0)
/* 0B47B8 800B3BB8 3C010500 */  lui   $at, 0x500
/* 0B47BC 800B3BBC 24590008 */  addiu $t9, $v0, 8
/* 0B47C0 800B3BC0 AE190000 */  sw    $t9, ($s0)
/* 0B47C4 800B3BC4 84660006 */  lh    $a2, 6($v1)
/* 0B47C8 800B3BC8 00000000 */  nop   
/* 0B47CC 800B3BCC 24D8FFFF */  addiu $t8, $a2, -1
/* 0B47D0 800B3BD0 00186900 */  sll   $t5, $t8, 4
/* 0B47D4 800B3BD4 35AC0001 */  ori   $t4, $t5, 1
/* 0B47D8 800B3BD8 318F00FF */  andi  $t7, $t4, 0xff
/* 0B47DC 800B3BDC 000F7400 */  sll   $t6, $t7, 0x10
/* 0B47E0 800B3BE0 0006C100 */  sll   $t8, $a2, 4
/* 0B47E4 800B3BE4 330DFFFF */  andi  $t5, $t8, 0xffff
/* 0B47E8 800B3BE8 01C1C825 */  or    $t9, $t6, $at
/* 0B47EC 800B3BEC 032D6025 */  or    $t4, $t9, $t5
/* 0B47F0 800B3BF0 AC4C0000 */  sw    $t4, ($v0)
/* 0B47F4 800B3BF4 8C6F000C */  lw    $t7, 0xc($v1)
/* 0B47F8 800B3BF8 240100FF */  li    $at, 255
/* 0B47FC 800B3BFC 01E77021 */  addu  $t6, $t7, $a3
/* 0B4800 800B3C00 AC4E0004 */  sw    $t6, 4($v0)
/* 0B4804 800B3C04 8638004A */  lh    $t8, 0x4a($s1)
/* 0B4808 800B3C08 3C0DFA00 */  lui   $t5, 0xfa00
/* 0B480C 800B3C0C 13010091 */  beq   $t8, $at, .L800B3E54
/* 0B4810 800B3C10 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0B4814 800B3C14 8E020000 */  lw    $v0, ($s0)
/* 0B4818 800B3C18 240CFFFF */  li    $t4, -1
/* 0B481C 800B3C1C 24590008 */  addiu $t9, $v0, 8
/* 0B4820 800B3C20 AE190000 */  sw    $t9, ($s0)
/* 0B4824 800B3C24 AC4C0004 */  sw    $t4, 4($v0)
/* 0B4828 800B3C28 10000089 */  b     .L800B3E50
/* 0B482C 800B3C2C AC4D0000 */   sw    $t5, ($v0)
.L800B3C30:
/* 0B4830 800B3C30 14610088 */  bne   $v1, $at, .L800B3E54
/* 0B4834 800B3C34 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0B4838 800B3C38 8E020000 */  lw    $v0, ($s0)
/* 0B483C 800B3C3C 3C0EFA00 */  lui   $t6, 0xfa00
/* 0B4840 800B3C40 244F0008 */  addiu $t7, $v0, 8
/* 0B4844 800B3C44 AE0F0000 */  sw    $t7, ($s0)
/* 0B4848 800B3C48 AC4E0000 */  sw    $t6, ($v0)
/* 0B484C 800B3C4C 8623004A */  lh    $v1, 0x4a($s1)
/* 0B4850 800B3C50 3C060800 */  lui   $a2, (0x0800010B >> 16) # lui $a2, 0x800
/* 0B4854 800B3C54 307800FF */  andi  $t8, $v1, 0xff
/* 0B4858 800B3C58 0018CE00 */  sll   $t9, $t8, 0x18
/* 0B485C 800B3C5C 00186C00 */  sll   $t5, $t8, 0x10
/* 0B4860 800B3C60 00187A00 */  sll   $t7, $t8, 8
/* 0B4864 800B3C64 032D6025 */  or    $t4, $t9, $t5
/* 0B4868 800B3C68 018F7025 */  or    $t6, $t4, $t7
/* 0B486C 800B3C6C 315800FF */  andi  $t8, $t2, 0xff
/* 0B4870 800B3C70 01D8C825 */  or    $t9, $t6, $t8
/* 0B4874 800B3C74 AC590004 */  sw    $t9, 4($v0)
/* 0B4878 800B3C78 92250068 */  lbu   $a1, 0x68($s1)
/* 0B487C 800B3C7C 34C6010B */  ori   $a2, (0x0800010B & 0xFFFF) # ori $a2, $a2, 0x10b
/* 0B4880 800B3C80 28A10002 */  slti  $at, $a1, 2
/* 0B4884 800B3C84 1420003A */  bnez  $at, .L800B3D70
/* 0B4888 800B3C88 02002025 */   move  $a0, $s0
/* 0B488C 800B3C8C 8E230044 */  lw    $v1, 0x44($s1)
/* 0B4890 800B3C90 86270018 */  lh    $a3, 0x18($s1)
/* 0B4894 800B3C94 8C650000 */  lw    $a1, ($v1)
/* 0B4898 800B3C98 00076A00 */  sll   $t5, $a3, 8
/* 0B489C 800B3C9C 01A03825 */  move  $a3, $t5
/* 0B48A0 800B3CA0 AFAA0038 */  sw    $t2, 0x38($sp)
/* 0B48A4 800B3CA4 0C01ED3A */  jal   func_8007B4E8
/* 0B48A8 800B3CA8 AFA30030 */   sw    $v1, 0x30($sp)
/* 0B48AC 800B3CAC 8E020000 */  lw    $v0, ($s0)
/* 0B48B0 800B3CB0 8FA30030 */  lw    $v1, 0x30($sp)
/* 0B48B4 800B3CB4 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0B48B8 800B3CB8 244C0008 */  addiu $t4, $v0, 8
/* 0B48BC 800B3CBC AE0C0000 */  sw    $t4, ($s0)
/* 0B48C0 800B3CC0 8C780008 */  lw    $t8, 8($v1)
/* 0B48C4 800B3CC4 84650004 */  lh    $a1, 4($v1)
/* 0B48C8 800B3CC8 3C078000 */  lui   $a3, 0x8000
/* 0B48CC 800B3CCC 0307C821 */  addu  $t9, $t8, $a3
/* 0B48D0 800B3CD0 24AFFFFF */  addiu $t7, $a1, -1
/* 0B48D4 800B3CD4 000F70C0 */  sll   $t6, $t7, 3
/* 0B48D8 800B3CD8 332D0006 */  andi  $t5, $t9, 6
/* 0B48DC 800B3CDC 01CD6025 */  or    $t4, $t6, $t5
/* 0B48E0 800B3CE0 318F00FF */  andi  $t7, $t4, 0xff
/* 0B48E4 800B3CE4 000570C0 */  sll   $t6, $a1, 3
/* 0B48E8 800B3CE8 000FC400 */  sll   $t8, $t7, 0x10
/* 0B48EC 800B3CEC 01C56821 */  addu  $t5, $t6, $a1
/* 0B48F0 800B3CF0 000D6040 */  sll   $t4, $t5, 1
/* 0B48F4 800B3CF4 3C010400 */  lui   $at, 0x400
/* 0B48F8 800B3CF8 0301C825 */  or    $t9, $t8, $at
/* 0B48FC 800B3CFC 258F0008 */  addiu $t7, $t4, 8
/* 0B4900 800B3D00 31F8FFFF */  andi  $t8, $t7, 0xffff
/* 0B4904 800B3D04 03387025 */  or    $t6, $t9, $t8
/* 0B4908 800B3D08 AC4E0000 */  sw    $t6, ($v0)
/* 0B490C 800B3D0C 8C6D0008 */  lw    $t5, 8($v1)
/* 0B4910 800B3D10 3C010500 */  lui   $at, 0x500
/* 0B4914 800B3D14 01A76021 */  addu  $t4, $t5, $a3
/* 0B4918 800B3D18 AC4C0004 */  sw    $t4, 4($v0)
/* 0B491C 800B3D1C 8E020000 */  lw    $v0, ($s0)
/* 0B4920 800B3D20 00000000 */  nop   
/* 0B4924 800B3D24 244F0008 */  addiu $t7, $v0, 8
/* 0B4928 800B3D28 AE0F0000 */  sw    $t7, ($s0)
/* 0B492C 800B3D2C 84660006 */  lh    $a2, 6($v1)
/* 0B4930 800B3D30 00000000 */  nop   
/* 0B4934 800B3D34 24D9FFFF */  addiu $t9, $a2, -1
/* 0B4938 800B3D38 0019C100 */  sll   $t8, $t9, 4
/* 0B493C 800B3D3C 370E0001 */  ori   $t6, $t8, 1
/* 0B4940 800B3D40 31CD00FF */  andi  $t5, $t6, 0xff
/* 0B4944 800B3D44 000D6400 */  sll   $t4, $t5, 0x10
/* 0B4948 800B3D48 0006C900 */  sll   $t9, $a2, 4
/* 0B494C 800B3D4C 3338FFFF */  andi  $t8, $t9, 0xffff
/* 0B4950 800B3D50 01817825 */  or    $t7, $t4, $at
/* 0B4954 800B3D54 01F87025 */  or    $t6, $t7, $t8
/* 0B4958 800B3D58 AC4E0000 */  sw    $t6, ($v0)
/* 0B495C 800B3D5C 8C6D000C */  lw    $t5, 0xc($v1)
/* 0B4960 800B3D60 00000000 */  nop   
/* 0B4964 800B3D64 01A76021 */  addu  $t4, $t5, $a3
/* 0B4968 800B3D68 1000002C */  b     .L800B3E1C
/* 0B496C 800B3D6C AC4C0004 */   sw    $t4, 4($v0)
.L800B3D70:
/* 0B4970 800B3D70 18A0002A */  blez  $a1, .L800B3E1C
/* 0B4974 800B3D74 02002025 */   move  $a0, $s0
/* 0B4978 800B3D78 8E230044 */  lw    $v1, 0x44($s1)
/* 0B497C 800B3D7C 86270018 */  lh    $a3, 0x18($s1)
/* 0B4980 800B3D80 8C650000 */  lw    $a1, ($v1)
/* 0B4984 800B3D84 3C060800 */  lui   $a2, (0x0800010B >> 16) # lui $a2, 0x800
/* 0B4988 800B3D88 0007CA00 */  sll   $t9, $a3, 8
/* 0B498C 800B3D8C 03203825 */  move  $a3, $t9
/* 0B4990 800B3D90 34C6010B */  ori   $a2, (0x0800010B & 0xFFFF) # ori $a2, $a2, 0x10b
/* 0B4994 800B3D94 AFAA0038 */  sw    $t2, 0x38($sp)
/* 0B4998 800B3D98 0C01ED3A */  jal   func_8007B4E8
/* 0B499C 800B3D9C AFA30030 */   sw    $v1, 0x30($sp)
/* 0B49A0 800B3DA0 8E020000 */  lw    $v0, ($s0)
/* 0B49A4 800B3DA4 8FA30030 */  lw    $v1, 0x30($sp)
/* 0B49A8 800B3DA8 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0B49AC 800B3DAC 244F0008 */  addiu $t7, $v0, 8
/* 0B49B0 800B3DB0 AE0F0000 */  sw    $t7, ($s0)
/* 0B49B4 800B3DB4 8C780008 */  lw    $t8, 8($v1)
/* 0B49B8 800B3DB8 3C078000 */  lui   $a3, 0x8000
/* 0B49BC 800B3DBC 03077021 */  addu  $t6, $t8, $a3
/* 0B49C0 800B3DC0 31CD0006 */  andi  $t5, $t6, 6
/* 0B49C4 800B3DC4 35AC0018 */  ori   $t4, $t5, 0x18
/* 0B49C8 800B3DC8 319900FF */  andi  $t9, $t4, 0xff
/* 0B49CC 800B3DCC 00197C00 */  sll   $t7, $t9, 0x10
/* 0B49D0 800B3DD0 3C010400 */  lui   $at, 0x400
/* 0B49D4 800B3DD4 01E1C025 */  or    $t8, $t7, $at
/* 0B49D8 800B3DD8 370E0050 */  ori   $t6, $t8, 0x50
/* 0B49DC 800B3DDC AC4E0000 */  sw    $t6, ($v0)
/* 0B49E0 800B3DE0 8C6D0008 */  lw    $t5, 8($v1)
/* 0B49E4 800B3DE4 3C0F0501 */  lui   $t7, (0x05010010 >> 16) # lui $t7, 0x501
/* 0B49E8 800B3DE8 01A76021 */  addu  $t4, $t5, $a3
/* 0B49EC 800B3DEC AC4C0004 */  sw    $t4, 4($v0)
/* 0B49F0 800B3DF0 8E020000 */  lw    $v0, ($s0)
/* 0B49F4 800B3DF4 35EF0010 */  ori   $t7, (0x05010010 & 0xFFFF) # ori $t7, $t7, 0x10
/* 0B49F8 800B3DF8 24590008 */  addiu $t9, $v0, 8
/* 0B49FC 800B3DFC AE190000 */  sw    $t9, ($s0)
/* 0B4A00 800B3E00 AC4F0000 */  sw    $t7, ($v0)
/* 0B4A04 800B3E04 846E0006 */  lh    $t6, 6($v1)
/* 0B4A08 800B3E08 8C78000C */  lw    $t8, 0xc($v1)
/* 0B4A0C 800B3E0C 000E6900 */  sll   $t5, $t6, 4
/* 0B4A10 800B3E10 030D6021 */  addu  $t4, $t8, $t5
/* 0B4A14 800B3E14 0187C821 */  addu  $t9, $t4, $a3
/* 0B4A18 800B3E18 AC590004 */  sw    $t9, 4($v0)
.L800B3E1C:
/* 0B4A1C 800B3E1C 240100FF */  li    $at, 255
/* 0B4A20 800B3E20 15410005 */  bne   $t2, $at, .L800B3E38
/* 0B4A24 800B3E24 3C18FA00 */   lui   $t8, 0xfa00
/* 0B4A28 800B3E28 862F004A */  lh    $t7, 0x4a($s1)
/* 0B4A2C 800B3E2C 240100FF */  li    $at, 255
/* 0B4A30 800B3E30 11E10008 */  beq   $t7, $at, .L800B3E54
/* 0B4A34 800B3E34 8FBF0024 */   lw    $ra, 0x24($sp)
.L800B3E38:
/* 0B4A38 800B3E38 8E020000 */  lw    $v0, ($s0)
/* 0B4A3C 800B3E3C 240DFFFF */  li    $t5, -1
/* 0B4A40 800B3E40 244E0008 */  addiu $t6, $v0, 8
/* 0B4A44 800B3E44 AE0E0000 */  sw    $t6, ($s0)
/* 0B4A48 800B3E48 AC4D0004 */  sw    $t5, 4($v0)
/* 0B4A4C 800B3E4C AC580000 */  sw    $t8, ($v0)
.L800B3E50:
/* 0B4A50 800B3E50 8FBF0024 */  lw    $ra, 0x24($sp)
.L800B3E54:
/* 0B4A54 800B3E54 8FB0001C */  lw    $s0, 0x1c($sp)
/* 0B4A58 800B3E58 8FB10020 */  lw    $s1, 0x20($sp)
/* 0B4A5C 800B3E5C 03E00008 */  jr    $ra
/* 0B4A60 800B3E60 27BD0040 */   addiu $sp, $sp, 0x40

glabel func_800B3E64
/* 0B4A64 800B3E64 27BDFF70 */  addiu $sp, $sp, -0x90
/* 0B4A68 800B3E68 AFBF0044 */  sw    $ra, 0x44($sp)
/* 0B4A6C 800B3E6C AFBE0040 */  sw    $fp, 0x40($sp)
/* 0B4A70 800B3E70 AFB7003C */  sw    $s7, 0x3c($sp)
/* 0B4A74 800B3E74 AFB60038 */  sw    $s6, 0x38($sp)
/* 0B4A78 800B3E78 AFB50034 */  sw    $s5, 0x34($sp)
/* 0B4A7C 800B3E7C AFB40030 */  sw    $s4, 0x30($sp)
/* 0B4A80 800B3E80 AFB3002C */  sw    $s3, 0x2c($sp)
/* 0B4A84 800B3E84 AFB20028 */  sw    $s2, 0x28($sp)
/* 0B4A88 800B3E88 AFB10024 */  sw    $s1, 0x24($sp)
/* 0B4A8C 800B3E8C AFB00020 */  sw    $s0, 0x20($sp)
/* 0B4A90 800B3E90 E7B50018 */  swc1  $f21, 0x18($sp)
/* 0B4A94 800B3E94 E7B4001C */  swc1  $f20, 0x1c($sp)
/* 0B4A98 800B3E98 8C960070 */  lw    $s6, 0x70($a0)
/* 0B4A9C 800B3E9C 0000A825 */  move  $s5, $zero
/* 0B4AA0 800B3EA0 12C0016B */  beqz  $s6, .L800B4450
/* 0B4AA4 800B3EA4 00009825 */   move  $s3, $zero
/* 0B4AA8 800B3EA8 8ECE000C */  lw    $t6, 0xc($s6)
/* 0B4AAC 800B3EAC 00000000 */  nop   
/* 0B4AB0 800B3EB0 11C00168 */  beqz  $t6, .L800B4454
/* 0B4AB4 800B3EB4 8FBF0044 */   lw    $ra, 0x44($sp)
/* 0B4AB8 800B3EB8 92C20006 */  lbu   $v0, 6($s6)
/* 0B4ABC 800B3EBC 27BE007C */  addiu $fp, $sp, 0x7c
/* 0B4AC0 800B3EC0 2442FFFF */  addiu $v0, $v0, -1
/* 0B4AC4 800B3EC4 04400162 */  bltz  $v0, .L800B4450
/* 0B4AC8 800B3EC8 00029080 */   sll   $s2, $v0, 2
/* 0B4ACC 800B3ECC 4480A000 */  mtc1  $zero, $f20
/* 0B4AD0 800B3ED0 27B70070 */  addiu $s7, $sp, 0x70
/* 0B4AD4 800B3ED4 2414000A */  li    $s4, 10
.L800B3ED8:
/* 0B4AD8 800B3ED8 8ECF000C */  lw    $t7, 0xc($s6)
/* 0B4ADC 800B3EDC 02E02825 */  move  $a1, $s7
/* 0B4AE0 800B3EE0 01F2C021 */  addu  $t8, $t7, $s2
/* 0B4AE4 800B3EE4 8F100000 */  lw    $s0, ($t8)
/* 0B4AE8 800B3EE8 00000000 */  nop   
/* 0B4AEC 800B3EEC 8619003A */  lh    $t9, 0x3a($s0)
/* 0B4AF0 800B3EF0 02002025 */  move  $a0, $s0
/* 0B4AF4 800B3EF4 13200157 */  beqz  $t9, .L800B4454
/* 0B4AF8 800B3EF8 8FBF0044 */   lw    $ra, 0x44($sp)
/* 0B4AFC 800B3EFC C6040008 */  lwc1  $f4, 8($s0)
/* 0B4B00 800B3F00 8E110044 */  lw    $s1, 0x44($s0)
/* 0B4B04 800B3F04 E7B40074 */  swc1  $f20, 0x74($sp)
/* 0B4B08 800B3F08 E7B40078 */  swc1  $f20, 0x78($sp)
/* 0B4B0C 800B3F0C 0C01C0C8 */  jal   func_80070320
/* 0B4B10 800B3F10 E7A40070 */   swc1  $f4, 0x70($sp)
/* 0B4B14 800B3F14 E7B4007C */  swc1  $f20, 0x7c($sp)
/* 0B4B18 800B3F18 C6060008 */  lwc1  $f6, 8($s0)
/* 0B4B1C 800B3F1C E7B40084 */  swc1  $f20, 0x84($sp)
/* 0B4B20 800B3F20 02002025 */  move  $a0, $s0
/* 0B4B24 800B3F24 03C02825 */  move  $a1, $fp
/* 0B4B28 800B3F28 0C01C0C8 */  jal   func_80070320
/* 0B4B2C 800B3F2C E7A60080 */   swc1  $f6, 0x80($sp)
/* 0B4B30 800B3F30 92090075 */  lbu   $t1, 0x75($s0)
/* 0B4B34 800B3F34 C7A80070 */  lwc1  $f8, 0x70($sp)
/* 0B4B38 800B3F38 000950C0 */  sll   $t2, $t1, 3
/* 0B4B3C 800B3F3C 01540019 */  multu $t2, $s4
/* 0B4B40 800B3F40 C60A000C */  lwc1  $f10, 0xc($s0)
/* 0B4B44 800B3F44 8E280008 */  lw    $t0, 8($s1)
/* 0B4B48 800B3F48 460A4400 */  add.s $f16, $f8, $f10
/* 0B4B4C 800B3F4C 444CF800 */  cfc1  $t4, $31
/* 0B4B50 800B3F50 00000000 */  nop   
/* 0B4B54 800B3F54 35810003 */  ori   $at, $t4, 3
/* 0B4B58 800B3F58 38210002 */  xori  $at, $at, 2
/* 0B4B5C 800B3F5C 44C1F800 */  ctc1  $at, $31
/* 0B4B60 800B3F60 00000000 */  nop   
/* 0B4B64 800B3F64 460084A4 */  cvt.w.s $f18, $f16
/* 0B4B68 800B3F68 00005812 */  mflo  $t3
/* 0B4B6C 800B3F6C 440D9000 */  mfc1  $t5, $f18
/* 0B4B70 800B3F70 010B1821 */  addu  $v1, $t0, $t3
/* 0B4B74 800B3F74 A46D0028 */  sh    $t5, 0x28($v1)
/* 0B4B78 800B3F78 44CCF800 */  ctc1  $t4, $31
/* 0B4B7C 800B3F7C C6060010 */  lwc1  $f6, 0x10($s0)
/* 0B4B80 800B3F80 C7A40074 */  lwc1  $f4, 0x74($sp)
/* 0B4B84 800B3F84 24630046 */  addiu $v1, $v1, 0x46
/* 0B4B88 800B3F88 46062200 */  add.s $f8, $f4, $f6
/* 0B4B8C 800B3F8C 444EF800 */  cfc1  $t6, $31
/* 0B4B90 800B3F90 00000000 */  nop   
/* 0B4B94 800B3F94 35C10003 */  ori   $at, $t6, 3
/* 0B4B98 800B3F98 38210002 */  xori  $at, $at, 2
/* 0B4B9C 800B3F9C 44C1F800 */  ctc1  $at, $31
/* 0B4BA0 800B3FA0 00000000 */  nop   
/* 0B4BA4 800B3FA4 460042A4 */  cvt.w.s $f10, $f8
/* 0B4BA8 800B3FA8 440F5000 */  mfc1  $t7, $f10
/* 0B4BAC 800B3FAC 44CEF800 */  ctc1  $t6, $31
/* 0B4BB0 800B3FB0 A46FFFE4 */  sh    $t7, -0x1c($v1)
/* 0B4BB4 800B3FB4 C6120014 */  lwc1  $f18, 0x14($s0)
/* 0B4BB8 800B3FB8 C7B00078 */  lwc1  $f16, 0x78($sp)
/* 0B4BBC 800B3FBC 00000000 */  nop   
/* 0B4BC0 800B3FC0 46128100 */  add.s $f4, $f16, $f18
/* 0B4BC4 800B3FC4 4458F800 */  cfc1  $t8, $31
/* 0B4BC8 800B3FC8 00000000 */  nop   
/* 0B4BCC 800B3FCC 37010003 */  ori   $at, $t8, 3
/* 0B4BD0 800B3FD0 38210002 */  xori  $at, $at, 2
/* 0B4BD4 800B3FD4 44C1F800 */  ctc1  $at, $31
/* 0B4BD8 800B3FD8 00000000 */  nop   
/* 0B4BDC 800B3FDC 460021A4 */  cvt.w.s $f6, $f4
/* 0B4BE0 800B3FE0 44193000 */  mfc1  $t9, $f6
/* 0B4BE4 800B3FE4 44D8F800 */  ctc1  $t8, $31
/* 0B4BE8 800B3FE8 A479FFE6 */  sh    $t9, -0x1a($v1)
/* 0B4BEC 800B3FEC 9209006C */  lbu   $t1, 0x6c($s0)
/* 0B4BF0 800B3FF0 00000000 */  nop   
/* 0B4BF4 800B3FF4 A069FFE8 */  sb    $t1, -0x18($v1)
/* 0B4BF8 800B3FF8 920A006D */  lbu   $t2, 0x6d($s0)
/* 0B4BFC 800B3FFC 00000000 */  nop   
/* 0B4C00 800B4000 A06AFFE9 */  sb    $t2, -0x17($v1)
/* 0B4C04 800B4004 9208006E */  lbu   $t0, 0x6e($s0)
/* 0B4C08 800B4008 00000000 */  nop   
/* 0B4C0C 800B400C A068FFEA */  sb    $t0, -0x16($v1)
/* 0B4C10 800B4010 860B005C */  lh    $t3, 0x5c($s0)
/* 0B4C14 800B4014 00000000 */  nop   
/* 0B4C18 800B4018 000B6203 */  sra   $t4, $t3, 8
/* 0B4C1C 800B401C A06CFFEB */  sb    $t4, -0x15($v1)
/* 0B4C20 800B4020 C7A8007C */  lwc1  $f8, 0x7c($sp)
/* 0B4C24 800B4024 C60A000C */  lwc1  $f10, 0xc($s0)
/* 0B4C28 800B4028 00000000 */  nop   
/* 0B4C2C 800B402C 460A4400 */  add.s $f16, $f8, $f10
/* 0B4C30 800B4030 444DF800 */  cfc1  $t5, $31
/* 0B4C34 800B4034 00000000 */  nop   
/* 0B4C38 800B4038 35A10003 */  ori   $at, $t5, 3
/* 0B4C3C 800B403C 38210002 */  xori  $at, $at, 2
/* 0B4C40 800B4040 44C1F800 */  ctc1  $at, $31
/* 0B4C44 800B4044 00000000 */  nop   
/* 0B4C48 800B4048 460084A4 */  cvt.w.s $f18, $f16
/* 0B4C4C 800B404C 440E9000 */  mfc1  $t6, $f18
/* 0B4C50 800B4050 44CDF800 */  ctc1  $t5, $31
/* 0B4C54 800B4054 A46EFFEC */  sh    $t6, -0x14($v1)
/* 0B4C58 800B4058 C7A40080 */  lwc1  $f4, 0x80($sp)
/* 0B4C5C 800B405C C6060010 */  lwc1  $f6, 0x10($s0)
/* 0B4C60 800B4060 00000000 */  nop   
/* 0B4C64 800B4064 46062200 */  add.s $f8, $f4, $f6
/* 0B4C68 800B4068 444FF800 */  cfc1  $t7, $31
/* 0B4C6C 800B406C 00000000 */  nop   
/* 0B4C70 800B4070 35E10003 */  ori   $at, $t7, 3
/* 0B4C74 800B4074 38210002 */  xori  $at, $at, 2
/* 0B4C78 800B4078 44C1F800 */  ctc1  $at, $31
/* 0B4C7C 800B407C 00000000 */  nop   
/* 0B4C80 800B4080 460042A4 */  cvt.w.s $f10, $f8
/* 0B4C84 800B4084 44185000 */  mfc1  $t8, $f10
/* 0B4C88 800B4088 44CFF800 */  ctc1  $t7, $31
/* 0B4C8C 800B408C A478FFEE */  sh    $t8, -0x12($v1)
/* 0B4C90 800B4090 C7B00084 */  lwc1  $f16, 0x84($sp)
/* 0B4C94 800B4094 C6120014 */  lwc1  $f18, 0x14($s0)
/* 0B4C98 800B4098 00000000 */  nop   
/* 0B4C9C 800B409C 46128100 */  add.s $f4, $f16, $f18
/* 0B4CA0 800B40A0 4459F800 */  cfc1  $t9, $31
/* 0B4CA4 800B40A4 00000000 */  nop   
/* 0B4CA8 800B40A8 37210003 */  ori   $at, $t9, 3
/* 0B4CAC 800B40AC 38210002 */  xori  $at, $at, 2
/* 0B4CB0 800B40B0 44C1F800 */  ctc1  $at, $31
/* 0B4CB4 800B40B4 00000000 */  nop   
/* 0B4CB8 800B40B8 460021A4 */  cvt.w.s $f6, $f4
/* 0B4CBC 800B40BC 44093000 */  mfc1  $t1, $f6
/* 0B4CC0 800B40C0 44D9F800 */  ctc1  $t9, $31
/* 0B4CC4 800B40C4 A469FFF0 */  sh    $t1, -0x10($v1)
/* 0B4CC8 800B40C8 920A006C */  lbu   $t2, 0x6c($s0)
/* 0B4CCC 800B40CC 00000000 */  nop   
/* 0B4CD0 800B40D0 A06AFFF2 */  sb    $t2, -0xe($v1)
/* 0B4CD4 800B40D4 9208006D */  lbu   $t0, 0x6d($s0)
/* 0B4CD8 800B40D8 00000000 */  nop   
/* 0B4CDC 800B40DC A068FFF3 */  sb    $t0, -0xd($v1)
/* 0B4CE0 800B40E0 920B006E */  lbu   $t3, 0x6e($s0)
/* 0B4CE4 800B40E4 00000000 */  nop   
/* 0B4CE8 800B40E8 A06BFFF4 */  sb    $t3, -0xc($v1)
/* 0B4CEC 800B40EC 860C005C */  lh    $t4, 0x5c($s0)
/* 0B4CF0 800B40F0 00000000 */  nop   
/* 0B4CF4 800B40F4 000C6A03 */  sra   $t5, $t4, 8
/* 0B4CF8 800B40F8 A06DFFF5 */  sb    $t5, -0xb($v1)
/* 0B4CFC 800B40FC C608000C */  lwc1  $f8, 0xc($s0)
/* 0B4D00 800B4100 C7AA0070 */  lwc1  $f10, 0x70($sp)
/* 0B4D04 800B4104 00000000 */  nop   
/* 0B4D08 800B4108 460A4401 */  sub.s $f16, $f8, $f10
/* 0B4D0C 800B410C 444EF800 */  cfc1  $t6, $31
/* 0B4D10 800B4110 00000000 */  nop   
/* 0B4D14 800B4114 35C10003 */  ori   $at, $t6, 3
/* 0B4D18 800B4118 38210002 */  xori  $at, $at, 2
/* 0B4D1C 800B411C 44C1F800 */  ctc1  $at, $31
/* 0B4D20 800B4120 00000000 */  nop   
/* 0B4D24 800B4124 460084A4 */  cvt.w.s $f18, $f16
/* 0B4D28 800B4128 440F9000 */  mfc1  $t7, $f18
/* 0B4D2C 800B412C 44CEF800 */  ctc1  $t6, $31
/* 0B4D30 800B4130 A46FFFF6 */  sh    $t7, -0xa($v1)
/* 0B4D34 800B4134 C6040010 */  lwc1  $f4, 0x10($s0)
/* 0B4D38 800B4138 C7A60074 */  lwc1  $f6, 0x74($sp)
/* 0B4D3C 800B413C 00000000 */  nop   
/* 0B4D40 800B4140 46062201 */  sub.s $f8, $f4, $f6
/* 0B4D44 800B4144 4458F800 */  cfc1  $t8, $31
/* 0B4D48 800B4148 00000000 */  nop   
/* 0B4D4C 800B414C 37010003 */  ori   $at, $t8, 3
/* 0B4D50 800B4150 38210002 */  xori  $at, $at, 2
/* 0B4D54 800B4154 44C1F800 */  ctc1  $at, $31
/* 0B4D58 800B4158 00000000 */  nop   
/* 0B4D5C 800B415C 460042A4 */  cvt.w.s $f10, $f8
/* 0B4D60 800B4160 44195000 */  mfc1  $t9, $f10
/* 0B4D64 800B4164 44D8F800 */  ctc1  $t8, $31
/* 0B4D68 800B4168 A479FFF8 */  sh    $t9, -8($v1)
/* 0B4D6C 800B416C C6100014 */  lwc1  $f16, 0x14($s0)
/* 0B4D70 800B4170 C7B20078 */  lwc1  $f18, 0x78($sp)
/* 0B4D74 800B4174 00000000 */  nop   
/* 0B4D78 800B4178 46128101 */  sub.s $f4, $f16, $f18
/* 0B4D7C 800B417C 4449F800 */  cfc1  $t1, $31
/* 0B4D80 800B4180 00000000 */  nop   
/* 0B4D84 800B4184 35210003 */  ori   $at, $t1, 3
/* 0B4D88 800B4188 38210002 */  xori  $at, $at, 2
/* 0B4D8C 800B418C 44C1F800 */  ctc1  $at, $31
/* 0B4D90 800B4190 00000000 */  nop   
/* 0B4D94 800B4194 460021A4 */  cvt.w.s $f6, $f4
/* 0B4D98 800B4198 440A3000 */  mfc1  $t2, $f6
/* 0B4D9C 800B419C 44C9F800 */  ctc1  $t1, $31
/* 0B4DA0 800B41A0 A46AFFFA */  sh    $t2, -6($v1)
/* 0B4DA4 800B41A4 9208006C */  lbu   $t0, 0x6c($s0)
/* 0B4DA8 800B41A8 00000000 */  nop   
/* 0B4DAC 800B41AC A068FFFC */  sb    $t0, -4($v1)
/* 0B4DB0 800B41B0 920B006D */  lbu   $t3, 0x6d($s0)
/* 0B4DB4 800B41B4 00000000 */  nop   
/* 0B4DB8 800B41B8 A06BFFFD */  sb    $t3, -3($v1)
/* 0B4DBC 800B41BC 920C006E */  lbu   $t4, 0x6e($s0)
/* 0B4DC0 800B41C0 00000000 */  nop   
/* 0B4DC4 800B41C4 A06CFFFE */  sb    $t4, -2($v1)
/* 0B4DC8 800B41C8 860D005C */  lh    $t5, 0x5c($s0)
/* 0B4DCC 800B41CC 00000000 */  nop   
/* 0B4DD0 800B41D0 000D7203 */  sra   $t6, $t5, 8
/* 0B4DD4 800B41D4 A06EFFFF */  sb    $t6, -1($v1)
/* 0B4DD8 800B41D8 C7AA007C */  lwc1  $f10, 0x7c($sp)
/* 0B4DDC 800B41DC C608000C */  lwc1  $f8, 0xc($s0)
/* 0B4DE0 800B41E0 00000000 */  nop   
/* 0B4DE4 800B41E4 460A4401 */  sub.s $f16, $f8, $f10
/* 0B4DE8 800B41E8 444FF800 */  cfc1  $t7, $31
/* 0B4DEC 800B41EC 00000000 */  nop   
/* 0B4DF0 800B41F0 35E10003 */  ori   $at, $t7, 3
/* 0B4DF4 800B41F4 38210002 */  xori  $at, $at, 2
/* 0B4DF8 800B41F8 44C1F800 */  ctc1  $at, $31
/* 0B4DFC 800B41FC 00000000 */  nop   
/* 0B4E00 800B4200 460084A4 */  cvt.w.s $f18, $f16
/* 0B4E04 800B4204 44189000 */  mfc1  $t8, $f18
/* 0B4E08 800B4208 44CFF800 */  ctc1  $t7, $31
/* 0B4E0C 800B420C A4780000 */  sh    $t8, ($v1)
/* 0B4E10 800B4210 C7A60080 */  lwc1  $f6, 0x80($sp)
/* 0B4E14 800B4214 C6040010 */  lwc1  $f4, 0x10($s0)
/* 0B4E18 800B4218 00000000 */  nop   
/* 0B4E1C 800B421C 46062201 */  sub.s $f8, $f4, $f6
/* 0B4E20 800B4220 4459F800 */  cfc1  $t9, $31
/* 0B4E24 800B4224 00000000 */  nop   
/* 0B4E28 800B4228 37210003 */  ori   $at, $t9, 3
/* 0B4E2C 800B422C 38210002 */  xori  $at, $at, 2
/* 0B4E30 800B4230 44C1F800 */  ctc1  $at, $31
/* 0B4E34 800B4234 00000000 */  nop   
/* 0B4E38 800B4238 460042A4 */  cvt.w.s $f10, $f8
/* 0B4E3C 800B423C 44095000 */  mfc1  $t1, $f10
/* 0B4E40 800B4240 44D9F800 */  ctc1  $t9, $31
/* 0B4E44 800B4244 A4690002 */  sh    $t1, 2($v1)
/* 0B4E48 800B4248 C7B20084 */  lwc1  $f18, 0x84($sp)
/* 0B4E4C 800B424C C6100014 */  lwc1  $f16, 0x14($s0)
/* 0B4E50 800B4250 00000000 */  nop   
/* 0B4E54 800B4254 46128101 */  sub.s $f4, $f16, $f18
/* 0B4E58 800B4258 444AF800 */  cfc1  $t2, $31
/* 0B4E5C 800B425C 00000000 */  nop   
/* 0B4E60 800B4260 35410003 */  ori   $at, $t2, 3
/* 0B4E64 800B4264 38210002 */  xori  $at, $at, 2
/* 0B4E68 800B4268 44C1F800 */  ctc1  $at, $31
/* 0B4E6C 800B426C 00000000 */  nop   
/* 0B4E70 800B4270 460021A4 */  cvt.w.s $f6, $f4
/* 0B4E74 800B4274 44083000 */  mfc1  $t0, $f6
/* 0B4E78 800B4278 44CAF800 */  ctc1  $t2, $31
/* 0B4E7C 800B427C A4680004 */  sh    $t0, 4($v1)
/* 0B4E80 800B4280 920B006C */  lbu   $t3, 0x6c($s0)
/* 0B4E84 800B4284 00000000 */  nop   
/* 0B4E88 800B4288 A06B0006 */  sb    $t3, 6($v1)
/* 0B4E8C 800B428C 920C006D */  lbu   $t4, 0x6d($s0)
/* 0B4E90 800B4290 00000000 */  nop   
/* 0B4E94 800B4294 A06C0007 */  sb    $t4, 7($v1)
/* 0B4E98 800B4298 920D006E */  lbu   $t5, 0x6e($s0)
/* 0B4E9C 800B429C 00000000 */  nop   
/* 0B4EA0 800B42A0 A06D0008 */  sb    $t5, 8($v1)
/* 0B4EA4 800B42A4 860E005C */  lh    $t6, 0x5c($s0)
/* 0B4EA8 800B42A8 00000000 */  nop   
/* 0B4EAC 800B42AC 000E7A03 */  sra   $t7, $t6, 8
/* 0B4EB0 800B42B0 A06F0009 */  sb    $t7, 9($v1)
/* 0B4EB4 800B42B4 92190075 */  lbu   $t9, 0x75($s0)
/* 0B4EB8 800B42B8 8E380008 */  lw    $t8, 8($s1)
/* 0B4EBC 800B42BC 001948C0 */  sll   $t1, $t9, 3
/* 0B4EC0 800B42C0 01340019 */  multu $t1, $s4
/* 0B4EC4 800B42C4 00005012 */  mflo  $t2
/* 0B4EC8 800B42C8 030A2021 */  addu  $a0, $t8, $t2
/* 0B4ECC 800B42CC 12600009 */  beqz  $s3, .L800B42F4
/* 0B4ED0 800B42D0 00801825 */   move  $v1, $a0
/* 0B4ED4 800B42D4 92AB0075 */  lbu   $t3, 0x75($s5)
/* 0B4ED8 800B42D8 8E680008 */  lw    $t0, 8($s3)
/* 0B4EDC 800B42DC 000B60C0 */  sll   $t4, $t3, 3
/* 0B4EE0 800B42E0 01940019 */  multu $t4, $s4
/* 0B4EE4 800B42E4 00006812 */  mflo  $t5
/* 0B4EE8 800B42E8 010D1021 */  addu  $v0, $t0, $t5
/* 0B4EEC 800B42EC 10000002 */  b     .L800B42F8
/* 0B4EF0 800B42F0 24420028 */   addiu $v0, $v0, 0x28
.L800B42F4:
/* 0B4EF4 800B42F4 24820028 */  addiu $v0, $a0, 0x28
.L800B42F8:
/* 0B4EF8 800B42F8 844E0000 */  lh    $t6, ($v0)
/* 0B4EFC 800B42FC 2652FFFC */  addiu $s2, $s2, -4
/* 0B4F00 800B4300 A46E0000 */  sh    $t6, ($v1)
/* 0B4F04 800B4304 844F0002 */  lh    $t7, 2($v0)
/* 0B4F08 800B4308 2463001E */  addiu $v1, $v1, 0x1e
/* 0B4F0C 800B430C A46FFFE4 */  sh    $t7, -0x1c($v1)
/* 0B4F10 800B4310 84590004 */  lh    $t9, 4($v0)
/* 0B4F14 800B4314 2442001E */  addiu $v0, $v0, 0x1e
/* 0B4F18 800B4318 A479FFE6 */  sh    $t9, -0x1a($v1)
/* 0B4F1C 800B431C 9049FFE8 */  lbu   $t1, -0x18($v0)
/* 0B4F20 800B4320 0200A825 */  move  $s5, $s0
/* 0B4F24 800B4324 A069FFE8 */  sb    $t1, -0x18($v1)
/* 0B4F28 800B4328 9058FFE9 */  lbu   $t8, -0x17($v0)
/* 0B4F2C 800B432C 02209825 */  move  $s3, $s1
/* 0B4F30 800B4330 A078FFE9 */  sb    $t8, -0x17($v1)
/* 0B4F34 800B4334 904AFFEA */  lbu   $t2, -0x16($v0)
/* 0B4F38 800B4338 00000000 */  nop   
/* 0B4F3C 800B433C A06AFFEA */  sb    $t2, -0x16($v1)
/* 0B4F40 800B4340 904BFFEB */  lbu   $t3, -0x15($v0)
/* 0B4F44 800B4344 00000000 */  nop   
/* 0B4F48 800B4348 A06BFFEB */  sb    $t3, -0x15($v1)
/* 0B4F4C 800B434C 844CFFEC */  lh    $t4, -0x14($v0)
/* 0B4F50 800B4350 00000000 */  nop   
/* 0B4F54 800B4354 A46CFFEC */  sh    $t4, -0x14($v1)
/* 0B4F58 800B4358 8448FFEE */  lh    $t0, -0x12($v0)
/* 0B4F5C 800B435C 00000000 */  nop   
/* 0B4F60 800B4360 A468FFEE */  sh    $t0, -0x12($v1)
/* 0B4F64 800B4364 844DFFF0 */  lh    $t5, -0x10($v0)
/* 0B4F68 800B4368 00000000 */  nop   
/* 0B4F6C 800B436C A46DFFF0 */  sh    $t5, -0x10($v1)
/* 0B4F70 800B4370 904EFFF2 */  lbu   $t6, -0xe($v0)
/* 0B4F74 800B4374 00000000 */  nop   
/* 0B4F78 800B4378 A06EFFF2 */  sb    $t6, -0xe($v1)
/* 0B4F7C 800B437C 904FFFF3 */  lbu   $t7, -0xd($v0)
/* 0B4F80 800B4380 00000000 */  nop   
/* 0B4F84 800B4384 A06FFFF3 */  sb    $t7, -0xd($v1)
/* 0B4F88 800B4388 9059FFF4 */  lbu   $t9, -0xc($v0)
/* 0B4F8C 800B438C 00000000 */  nop   
/* 0B4F90 800B4390 A079FFF4 */  sb    $t9, -0xc($v1)
/* 0B4F94 800B4394 9049FFF5 */  lbu   $t1, -0xb($v0)
/* 0B4F98 800B4398 00000000 */  nop   
/* 0B4F9C 800B439C A069FFF5 */  sb    $t1, -0xb($v1)
/* 0B4FA0 800B43A0 8458FFF6 */  lh    $t8, -0xa($v0)
/* 0B4FA4 800B43A4 00000000 */  nop   
/* 0B4FA8 800B43A8 A478FFF6 */  sh    $t8, -0xa($v1)
/* 0B4FAC 800B43AC 844AFFF8 */  lh    $t2, -8($v0)
/* 0B4FB0 800B43B0 00000000 */  nop   
/* 0B4FB4 800B43B4 A46AFFF8 */  sh    $t2, -8($v1)
/* 0B4FB8 800B43B8 844BFFFA */  lh    $t3, -6($v0)
/* 0B4FBC 800B43BC 00000000 */  nop   
/* 0B4FC0 800B43C0 A46BFFFA */  sh    $t3, -6($v1)
/* 0B4FC4 800B43C4 904CFFFC */  lbu   $t4, -4($v0)
/* 0B4FC8 800B43C8 00000000 */  nop   
/* 0B4FCC 800B43CC A06CFFFC */  sb    $t4, -4($v1)
/* 0B4FD0 800B43D0 9048FFFD */  lbu   $t0, -3($v0)
/* 0B4FD4 800B43D4 00000000 */  nop   
/* 0B4FD8 800B43D8 A068FFFD */  sb    $t0, -3($v1)
/* 0B4FDC 800B43DC 904DFFFE */  lbu   $t5, -2($v0)
/* 0B4FE0 800B43E0 2408FFFF */  li    $t0, -1
/* 0B4FE4 800B43E4 A06DFFFE */  sb    $t5, -2($v1)
/* 0B4FE8 800B43E8 904EFFFF */  lbu   $t6, -1($v0)
/* 0B4FEC 800B43EC 00000000 */  nop   
/* 0B4FF0 800B43F0 A06EFFFF */  sb    $t6, -1($v1)
/* 0B4FF4 800B43F4 844F0000 */  lh    $t7, ($v0)
/* 0B4FF8 800B43F8 00000000 */  nop   
/* 0B4FFC 800B43FC A46F0000 */  sh    $t7, ($v1)
/* 0B5000 800B4400 84590002 */  lh    $t9, 2($v0)
/* 0B5004 800B4404 00000000 */  nop   
/* 0B5008 800B4408 A4790002 */  sh    $t9, 2($v1)
/* 0B500C 800B440C 84490004 */  lh    $t1, 4($v0)
/* 0B5010 800B4410 00000000 */  nop   
/* 0B5014 800B4414 A4690004 */  sh    $t1, 4($v1)
/* 0B5018 800B4418 90580006 */  lbu   $t8, 6($v0)
/* 0B501C 800B441C 00000000 */  nop   
/* 0B5020 800B4420 A0780006 */  sb    $t8, 6($v1)
/* 0B5024 800B4424 904A0007 */  lbu   $t2, 7($v0)
/* 0B5028 800B4428 00000000 */  nop   
/* 0B502C 800B442C A06A0007 */  sb    $t2, 7($v1)
/* 0B5030 800B4430 904B0008 */  lbu   $t3, 8($v0)
/* 0B5034 800B4434 00000000 */  nop   
/* 0B5038 800B4438 A06B0008 */  sb    $t3, 8($v1)
/* 0B503C 800B443C 904C0009 */  lbu   $t4, 9($v0)
/* 0B5040 800B4440 00000000 */  nop   
/* 0B5044 800B4444 A06C0009 */  sb    $t4, 9($v1)
/* 0B5048 800B4448 0641FEA3 */  bgez  $s2, .L800B3ED8
/* 0B504C 800B444C A2080077 */   sb    $t0, 0x77($s0)
.L800B4450:
/* 0B5050 800B4450 8FBF0044 */  lw    $ra, 0x44($sp)
.L800B4454:
/* 0B5054 800B4454 C7B50018 */  lwc1  $f21, 0x18($sp)
/* 0B5058 800B4458 C7B4001C */  lwc1  $f20, 0x1c($sp)
/* 0B505C 800B445C 8FB00020 */  lw    $s0, 0x20($sp)
/* 0B5060 800B4460 8FB10024 */  lw    $s1, 0x24($sp)
/* 0B5064 800B4464 8FB20028 */  lw    $s2, 0x28($sp)
/* 0B5068 800B4468 8FB3002C */  lw    $s3, 0x2c($sp)
/* 0B506C 800B446C 8FB40030 */  lw    $s4, 0x30($sp)
/* 0B5070 800B4470 8FB50034 */  lw    $s5, 0x34($sp)
/* 0B5074 800B4474 8FB60038 */  lw    $s6, 0x38($sp)
/* 0B5078 800B4478 8FB7003C */  lw    $s7, 0x3c($sp)
/* 0B507C 800B447C 8FBE0040 */  lw    $fp, 0x40($sp)
/* 0B5080 800B4480 03E00008 */  jr    $ra
/* 0B5084 800B4484 27BD0090 */   addiu $sp, $sp, 0x90

/* 0B5088 800B4488 3C03800E */  lui   $v1, %hi(D_800E2CE8) # $v1, 0x800e
/* 0B508C 800B448C 8C632CE8 */  lw    $v1, %lo(D_800E2CE8)($v1)
/* 0B5090 800B4490 3C0E800E */  lui   $t6, %hi(D_800E2CF0) # $t6, 0x800e
/* 0B5094 800B4494 0083082A */  slt   $at, $a0, $v1
/* 0B5098 800B4498 10200007 */  beqz  $at, .L800B44B8
/* 0B509C 800B449C 3C19800E */   lui   $t9, 0x800e
/* 0B50A0 800B44A0 8DCE2CF0 */  lw    $t6, %lo(D_800E2CF0)($t6)
/* 0B50A4 800B44A4 00047880 */  sll   $t7, $a0, 2
/* 0B50A8 800B44A8 01CFC021 */  addu  $t8, $t6, $t7
/* 0B50AC 800B44AC 8F020000 */  lw    $v0, ($t8)
/* 0B50B0 800B44B0 03E00008 */  jr    $ra
/* 0B50B4 800B44B4 00000000 */   nop   

.L800B44B8:
/* 0B50B8 800B44B8 8F392CF0 */  lw    $t9, 0x2cf0($t9)
/* 0B50BC 800B44BC 00034080 */  sll   $t0, $v1, 2
/* 0B50C0 800B44C0 03284821 */  addu  $t1, $t9, $t0
/* 0B50C4 800B44C4 8D22FFFC */  lw    $v0, -4($t1)
/* 0B50C8 800B44C8 00000000 */  nop   
/* 0B50CC 800B44CC 03E00008 */  jr    $ra
/* 0B50D0 800B44D0 00000000 */   nop   

/* 0B50D4 800B44D4 8C8E0000 */  lw    $t6, ($a0)
/* 0B50D8 800B44D8 3C05800E */  lui   $a1, %hi(D_800E2CE8) # $a1, 0x800e
/* 0B50DC 800B44DC 25C30001 */  addiu $v1, $t6, 1
/* 0B50E0 800B44E0 24A52CE8 */  addiu $a1, %lo(D_800E2CE8) # addiu $a1, $a1, 0x2ce8
/* 0B50E4 800B44E4 AC830000 */  sw    $v1, ($a0)
/* 0B50E8 800B44E8 8CA20000 */  lw    $v0, ($a1)
/* 0B50EC 800B44EC 3C19800E */  lui   $t9, %hi(D_800E2CF0) # $t9, 0x800e
/* 0B50F0 800B44F0 0062082A */  slt   $at, $v1, $v0
/* 0B50F4 800B44F4 14200007 */  bnez  $at, .L800B4514
/* 0B50F8 800B44F8 0062C023 */   subu  $t8, $v1, $v0
.L800B44FC:
/* 0B50FC 800B44FC AC980000 */  sw    $t8, ($a0)
/* 0B5100 800B4500 8CA20000 */  lw    $v0, ($a1)
/* 0B5104 800B4504 03001825 */  move  $v1, $t8
/* 0B5108 800B4508 0302082A */  slt   $at, $t8, $v0
/* 0B510C 800B450C 1020FFFB */  beqz  $at, .L800B44FC
/* 0B5110 800B4510 0062C023 */   subu  $t8, $v1, $v0
.L800B4514:
/* 0B5114 800B4514 8F392CF0 */  lw    $t9, %lo(D_800E2CF0)($t9)
/* 0B5118 800B4518 00034080 */  sll   $t0, $v1, 2
/* 0B511C 800B451C 03284821 */  addu  $t1, $t9, $t0
/* 0B5120 800B4520 8D220000 */  lw    $v0, ($t1)
/* 0B5124 800B4524 03E00008 */  jr    $ra
/* 0B5128 800B4528 00000000 */   nop   

/* 0B512C 800B452C 8C8E0000 */  lw    $t6, ($a0)
/* 0B5130 800B4530 3C08800E */  lui   $t0, %hi(D_800E2CF0) # $t0, 0x800e
/* 0B5134 800B4534 25C3FFFF */  addiu $v1, $t6, -1
/* 0B5138 800B4538 04610009 */  bgez  $v1, .L800B4560
/* 0B513C 800B453C AC830000 */   sw    $v1, ($a0)
/* 0B5140 800B4540 3C02800E */  lui   $v0, %hi(D_800E2CE8) # $v0, 0x800e
/* 0B5144 800B4544 24422CE8 */  addiu $v0, %lo(D_800E2CE8) # addiu $v0, $v0, 0x2ce8
.L800B4548:
/* 0B5148 800B4548 8C580000 */  lw    $t8, ($v0)
/* 0B514C 800B454C 00000000 */  nop   
/* 0B5150 800B4550 0078C821 */  addu  $t9, $v1, $t8
/* 0B5154 800B4554 AC990000 */  sw    $t9, ($a0)
/* 0B5158 800B4558 0720FFFB */  bltz  $t9, .L800B4548
/* 0B515C 800B455C 03201825 */   move  $v1, $t9
.L800B4560:
/* 0B5160 800B4560 8D082CF0 */  lw    $t0, %lo(D_800E2CF0)($t0)
/* 0B5164 800B4564 00034880 */  sll   $t1, $v1, 2
/* 0B5168 800B4568 01095021 */  addu  $t2, $t0, $t1
/* 0B516C 800B456C 8D420000 */  lw    $v0, ($t2)
/* 0B5170 800B4570 03E00008 */  jr    $ra
/* 0B5174 800B4574 00000000 */   nop   

/* 0B5178 800B4578 3C03800E */  lui   $v1, %hi(D_800E2CF4) # $v1, 0x800e
/* 0B517C 800B457C 8C632CF4 */  lw    $v1, %lo(D_800E2CF4)($v1)
/* 0B5180 800B4580 3C0E800E */  lui   $t6, %hi(D_800E2CFC) # $t6, 0x800e
/* 0B5184 800B4584 0083082A */  slt   $at, $a0, $v1
/* 0B5188 800B4588 10200007 */  beqz  $at, .L800B45A8
/* 0B518C 800B458C 3C19800E */   lui   $t9, 0x800e
/* 0B5190 800B4590 8DCE2CFC */  lw    $t6, %lo(D_800E2CFC)($t6)
/* 0B5194 800B4594 00047880 */  sll   $t7, $a0, 2
/* 0B5198 800B4598 01CFC021 */  addu  $t8, $t6, $t7
/* 0B519C 800B459C 8F020000 */  lw    $v0, ($t8)
/* 0B51A0 800B45A0 03E00008 */  jr    $ra
/* 0B51A4 800B45A4 00000000 */   nop   

.L800B45A8:
/* 0B51A8 800B45A8 8F392CFC */  lw    $t9, 0x2cfc($t9)
/* 0B51AC 800B45AC 00034080 */  sll   $t0, $v1, 2
/* 0B51B0 800B45B0 03284821 */  addu  $t1, $t9, $t0
/* 0B51B4 800B45B4 8D22FFFC */  lw    $v0, -4($t1)
/* 0B51B8 800B45B8 00000000 */  nop   
/* 0B51BC 800B45BC 03E00008 */  jr    $ra
/* 0B51C0 800B45C0 00000000 */   nop   

/* 0B51C4 800B45C4 8C8E0000 */  lw    $t6, ($a0)
/* 0B51C8 800B45C8 3C05800E */  lui   $a1, %hi(D_800E2CF4) # $a1, 0x800e
/* 0B51CC 800B45CC 25C30001 */  addiu $v1, $t6, 1
/* 0B51D0 800B45D0 24A52CF4 */  addiu $a1, %lo(D_800E2CF4) # addiu $a1, $a1, 0x2cf4
/* 0B51D4 800B45D4 AC830000 */  sw    $v1, ($a0)
/* 0B51D8 800B45D8 8CA20000 */  lw    $v0, ($a1)
/* 0B51DC 800B45DC 3C19800E */  lui   $t9, %hi(D_800E2CFC) # $t9, 0x800e
/* 0B51E0 800B45E0 0062082A */  slt   $at, $v1, $v0
/* 0B51E4 800B45E4 14200007 */  bnez  $at, .L800B4604
/* 0B51E8 800B45E8 0062C023 */   subu  $t8, $v1, $v0
.L800B45EC:
/* 0B51EC 800B45EC AC980000 */  sw    $t8, ($a0)
/* 0B51F0 800B45F0 8CA20000 */  lw    $v0, ($a1)
/* 0B51F4 800B45F4 03001825 */  move  $v1, $t8
/* 0B51F8 800B45F8 0302082A */  slt   $at, $t8, $v0
/* 0B51FC 800B45FC 1020FFFB */  beqz  $at, .L800B45EC
/* 0B5200 800B4600 0062C023 */   subu  $t8, $v1, $v0
.L800B4604:
/* 0B5204 800B4604 8F392CFC */  lw    $t9, %lo(D_800E2CFC)($t9)
/* 0B5208 800B4608 00034080 */  sll   $t0, $v1, 2
/* 0B520C 800B460C 03284821 */  addu  $t1, $t9, $t0
/* 0B5210 800B4610 8D220000 */  lw    $v0, ($t1)
/* 0B5214 800B4614 03E00008 */  jr    $ra
/* 0B5218 800B4618 00000000 */   nop   

/* 0B521C 800B461C 8C8E0000 */  lw    $t6, ($a0)
/* 0B5220 800B4620 3C08800E */  lui   $t0, %hi(D_800E2CFC) # $t0, 0x800e
/* 0B5224 800B4624 25C3FFFF */  addiu $v1, $t6, -1
/* 0B5228 800B4628 04610009 */  bgez  $v1, .L800B4650
/* 0B522C 800B462C AC830000 */   sw    $v1, ($a0)
/* 0B5230 800B4630 3C02800E */  lui   $v0, %hi(D_800E2CF4) # $v0, 0x800e
/* 0B5234 800B4634 24422CF4 */  addiu $v0, %lo(D_800E2CF4) # addiu $v0, $v0, 0x2cf4
.L800B4638:
/* 0B5238 800B4638 8C580000 */  lw    $t8, ($v0)
/* 0B523C 800B463C 00000000 */  nop   
/* 0B5240 800B4640 0078C821 */  addu  $t9, $v1, $t8
/* 0B5244 800B4644 AC990000 */  sw    $t9, ($a0)
/* 0B5248 800B4648 0720FFFB */  bltz  $t9, .L800B4638
/* 0B524C 800B464C 03201825 */   move  $v1, $t9
.L800B4650:
/* 0B5250 800B4650 8D082CFC */  lw    $t0, %lo(D_800E2CFC)($t0)
/* 0B5254 800B4654 00034880 */  sll   $t1, $v1, 2
/* 0B5258 800B4658 01095021 */  addu  $t2, $t0, $t1
/* 0B525C 800B465C 8D420000 */  lw    $v0, ($t2)
/* 0B5260 800B4660 03E00008 */  jr    $ra
/* 0B5264 800B4664 00000000 */   nop   

glabel func_800B4668
/* 0B5268 800B4668 8C8F006C */  lw    $t7, 0x6c($a0)
/* 0B526C 800B466C 00051940 */  sll   $v1, $a1, 5
/* 0B5270 800B4670 01E34021 */  addu  $t0, $t7, $v1
/* 0B5274 800B4674 8518000A */  lh    $t8, 0xa($t0)
/* 0B5278 800B4678 00077200 */  sll   $t6, $a3, 8
/* 0B527C 800B467C 3319FFFF */  andi  $t9, $t8, 0xffff
/* 0B5280 800B4680 03261021 */  addu  $v0, $t9, $a2
/* 0B5284 800B4684 01C2082A */  slt   $at, $t6, $v0
/* 0B5288 800B4688 10200003 */  beqz  $at, .L800B4698
/* 0B528C 800B468C 00000000 */   nop   
/* 0B5290 800B4690 10000002 */  b     .L800B469C
/* 0B5294 800B4694 A50E000A */   sh    $t6, 0xa($t0)
.L800B4698:
/* 0B5298 800B4698 A502000A */  sh    $v0, 0xa($t0)
.L800B469C:
/* 0B529C 800B469C 8C89006C */  lw    $t1, 0x6c($a0)
/* 0B52A0 800B46A0 00000000 */  nop   
/* 0B52A4 800B46A4 01234021 */  addu  $t0, $t1, $v1
/* 0B52A8 800B46A8 850A0004 */  lh    $t2, 4($t0)
/* 0B52AC 800B46AC 00000000 */  nop   
/* 0B52B0 800B46B0 354B0100 */  ori   $t3, $t2, 0x100
/* 0B52B4 800B46B4 03E00008 */  jr    $ra
/* 0B52B8 800B46B8 A50B0004 */   sh    $t3, 4($t0)

glabel func_800B46BC
/* 0B52BC 800B46BC 8C8F006C */  lw    $t7, 0x6c($a0)
/* 0B52C0 800B46C0 00051940 */  sll   $v1, $a1, 5
/* 0B52C4 800B46C4 01E34021 */  addu  $t0, $t7, $v1
/* 0B52C8 800B46C8 8518000A */  lh    $t8, 0xa($t0)
/* 0B52CC 800B46CC 00077200 */  sll   $t6, $a3, 8
/* 0B52D0 800B46D0 3319FFFF */  andi  $t9, $t8, 0xffff
/* 0B52D4 800B46D4 03261023 */  subu  $v0, $t9, $a2
/* 0B52D8 800B46D8 004E082A */  slt   $at, $v0, $t6
/* 0B52DC 800B46DC 10200003 */  beqz  $at, .L800B46EC
/* 0B52E0 800B46E0 00000000 */   nop   
/* 0B52E4 800B46E4 10000002 */  b     .L800B46F0
/* 0B52E8 800B46E8 A50E000A */   sh    $t6, 0xa($t0)
.L800B46EC:
/* 0B52EC 800B46EC A502000A */  sh    $v0, 0xa($t0)
.L800B46F0:
/* 0B52F0 800B46F0 8C89006C */  lw    $t1, 0x6c($a0)
/* 0B52F4 800B46F4 00000000 */  nop   
/* 0B52F8 800B46F8 01234021 */  addu  $t0, $t1, $v1
/* 0B52FC 800B46FC 850A0004 */  lh    $t2, 4($t0)
/* 0B5300 800B4700 00000000 */  nop   
/* 0B5304 800B4704 354B0100 */  ori   $t3, $t2, 0x100
/* 0B5308 800B4708 03E00008 */  jr    $ra
/* 0B530C 800B470C A50B0004 */   sh    $t3, 4($t0)

/* 0B5310 800B4710 90A20000 */  lbu   $v0, ($a1)
/* 0B5314 800B4714 00801825 */  move  $v1, $a0
/* 0B5318 800B4718 24840001 */  addiu $a0, $a0, 1
/* 0B531C 800B471C 24A50001 */  addiu $a1, $a1, 1
/* 0B5320 800B4720 10400006 */  beqz  $v0, .L800B473C
/* 0B5324 800B4724 A082FFFF */   sb    $v0, -1($a0)
.L800B4728:
/* 0B5328 800B4728 90A20000 */  lbu   $v0, ($a1)
/* 0B532C 800B472C 24840001 */  addiu $a0, $a0, 1
/* 0B5330 800B4730 24A50001 */  addiu $a1, $a1, 1
/* 0B5334 800B4734 1440FFFC */  bnez  $v0, .L800B4728
/* 0B5338 800B4738 A082FFFF */   sb    $v0, -1($a0)
.L800B473C:
/* 0B533C 800B473C 03E00008 */  jr    $ra
/* 0B5340 800B4740 00601025 */   move  $v0, $v1

/* 0B5344 800B4744 908E0000 */  lbu   $t6, ($a0)
/* 0B5348 800B4748 00801825 */  move  $v1, $a0
/* 0B534C 800B474C 11C00005 */  beqz  $t6, .L800B4764
/* 0B5350 800B4750 00000000 */   nop   
.L800B4754:
/* 0B5354 800B4754 908F0001 */  lbu   $t7, 1($a0)
/* 0B5358 800B4758 24840001 */  addiu $a0, $a0, 1
/* 0B535C 800B475C 15E0FFFD */  bnez  $t7, .L800B4754
/* 0B5360 800B4760 00000000 */   nop   
.L800B4764:
/* 0B5364 800B4764 90A20000 */  lbu   $v0, ($a1)
/* 0B5368 800B4768 24840001 */  addiu $a0, $a0, 1
/* 0B536C 800B476C 24A50001 */  addiu $a1, $a1, 1
/* 0B5370 800B4770 10400006 */  beqz  $v0, .L800B478C
/* 0B5374 800B4774 A082FFFF */   sb    $v0, -1($a0)
.L800B4778:
/* 0B5378 800B4778 90A20000 */  lbu   $v0, ($a1)
/* 0B537C 800B477C 24840001 */  addiu $a0, $a0, 1
/* 0B5380 800B4780 24A50001 */  addiu $a1, $a1, 1
/* 0B5384 800B4784 1440FFFC */  bnez  $v0, .L800B4778
/* 0B5388 800B4788 A082FFFF */   sb    $v0, -1($a0)
.L800B478C:
/* 0B538C 800B478C 03E00008 */  jr    $ra
/* 0B5390 800B4790 00601025 */   move  $v0, $v1

/* 0B5394 800B4794 90820000 */  lbu   $v0, ($a0)
/* 0B5398 800B4798 00000000 */  nop   
/* 0B539C 800B479C 14400005 */  bnez  $v0, .L800B47B4
/* 0B53A0 800B47A0 304600FF */   andi  $a2, $v0, 0xff
/* 0B53A4 800B47A4 90AE0000 */  lbu   $t6, ($a1)
/* 0B53A8 800B47A8 00000000 */  nop   
/* 0B53AC 800B47AC 11C00023 */  beqz  $t6, .L800B483C
.L800B47B0:
/* 0B53B0 800B47B0 304600FF */   andi  $a2, $v0, 0xff
.L800B47B4:
/* 0B53B4 800B47B4 28C10061 */  slti  $at, $a2, 0x61
/* 0B53B8 800B47B8 90A30000 */  lbu   $v1, ($a1)
/* 0B53BC 800B47BC 14200005 */  bnez  $at, .L800B47D4
/* 0B53C0 800B47C0 00C03825 */   move  $a3, $a2
/* 0B53C4 800B47C4 28C1007B */  slti  $at, $a2, 0x7b
/* 0B53C8 800B47C8 10200002 */  beqz  $at, .L800B47D4
/* 0B53CC 800B47CC 24C6FFE0 */   addiu $a2, $a2, -0x20
/* 0B53D0 800B47D0 30C700FF */  andi  $a3, $a2, 0xff
.L800B47D4:
/* 0B53D4 800B47D4 306200FF */  andi  $v0, $v1, 0xff
/* 0B53D8 800B47D8 28410061 */  slti  $at, $v0, 0x61
/* 0B53DC 800B47DC 14200005 */  bnez  $at, .L800B47F4
/* 0B53E0 800B47E0 00403025 */   move  $a2, $v0
/* 0B53E4 800B47E4 2841007B */  slti  $at, $v0, 0x7b
/* 0B53E8 800B47E8 10200002 */  beqz  $at, .L800B47F4
/* 0B53EC 800B47EC 2442FFE0 */   addiu $v0, $v0, -0x20
/* 0B53F0 800B47F0 304600FF */  andi  $a2, $v0, 0xff
.L800B47F4:
/* 0B53F4 800B47F4 00E6082A */  slt   $at, $a3, $a2
/* 0B53F8 800B47F8 10200004 */  beqz  $at, .L800B480C
/* 0B53FC 800B47FC 00C7082A */   slt   $at, $a2, $a3
/* 0B5400 800B4800 03E00008 */  jr    $ra
/* 0B5404 800B4804 2402FFFF */   li    $v0, -1

/* 0B5408 800B4808 00C7082A */  slt   $at, $a2, $a3
.L800B480C:
/* 0B540C 800B480C 10200003 */  beqz  $at, .L800B481C
/* 0B5410 800B4810 00000000 */   nop   
/* 0B5414 800B4814 03E00008 */  jr    $ra
/* 0B5418 800B4818 24020001 */   li    $v0, 1

.L800B481C:
/* 0B541C 800B481C 90820001 */  lbu   $v0, 1($a0)
/* 0B5420 800B4820 24840001 */  addiu $a0, $a0, 1
/* 0B5424 800B4824 1440FFE2 */  bnez  $v0, .L800B47B0
/* 0B5428 800B4828 24A50001 */   addiu $a1, $a1, 1
/* 0B542C 800B482C 90B90000 */  lbu   $t9, ($a1)
/* 0B5430 800B4830 00000000 */  nop   
/* 0B5434 800B4834 1720FFDF */  bnez  $t9, .L800B47B4
/* 0B5438 800B4838 304600FF */   andi  $a2, $v0, 0xff
.L800B483C:
/* 0B543C 800B483C 00001025 */  move  $v0, $zero
/* 0B5440 800B4840 03E00008 */  jr    $ra
/* 0B5444 800B4844 00000000 */   nop   

/* 0B5448 800B4848 90820000 */  lbu   $v0, ($a0)
/* 0B544C 800B484C 00000000 */  nop   
/* 0B5450 800B4850 14400005 */  bnez  $v0, .L800B4868
/* 0B5454 800B4854 00000000 */   nop   
/* 0B5458 800B4858 90AE0000 */  lbu   $t6, ($a1)
/* 0B545C 800B485C 00000000 */  nop   
/* 0B5460 800B4860 11C00027 */  beqz  $t6, .L800B4900
/* 0B5464 800B4864 00000000 */   nop   
.L800B4868:
/* 0B5468 800B4868 10C00025 */  beqz  $a2, .L800B4900
/* 0B546C 800B486C 304700FF */   andi  $a3, $v0, 0xff
.L800B4870:
/* 0B5470 800B4870 28E10061 */  slti  $at, $a3, 0x61
/* 0B5474 800B4874 90A30000 */  lbu   $v1, ($a1)
/* 0B5478 800B4878 14200005 */  bnez  $at, .L800B4890
/* 0B547C 800B487C 00E04025 */   move  $t0, $a3
/* 0B5480 800B4880 28E1007B */  slti  $at, $a3, 0x7b
/* 0B5484 800B4884 10200002 */  beqz  $at, .L800B4890
/* 0B5488 800B4888 24E7FFE0 */   addiu $a3, $a3, -0x20
/* 0B548C 800B488C 30E800FF */  andi  $t0, $a3, 0xff
.L800B4890:
/* 0B5490 800B4890 306200FF */  andi  $v0, $v1, 0xff
/* 0B5494 800B4894 28410061 */  slti  $at, $v0, 0x61
/* 0B5498 800B4898 14200005 */  bnez  $at, .L800B48B0
/* 0B549C 800B489C 00403825 */   move  $a3, $v0
/* 0B54A0 800B48A0 2841007B */  slti  $at, $v0, 0x7b
/* 0B54A4 800B48A4 10200002 */  beqz  $at, .L800B48B0
/* 0B54A8 800B48A8 2442FFE0 */   addiu $v0, $v0, -0x20
/* 0B54AC 800B48AC 304700FF */  andi  $a3, $v0, 0xff
.L800B48B0:
/* 0B54B0 800B48B0 0107082A */  slt   $at, $t0, $a3
/* 0B54B4 800B48B4 10200003 */  beqz  $at, .L800B48C4
/* 0B54B8 800B48B8 24840001 */   addiu $a0, $a0, 1
/* 0B54BC 800B48BC 03E00008 */  jr    $ra
/* 0B54C0 800B48C0 2402FFFF */   li    $v0, -1

.L800B48C4:
/* 0B54C4 800B48C4 00E8082A */  slt   $at, $a3, $t0
/* 0B54C8 800B48C8 10200003 */  beqz  $at, .L800B48D8
/* 0B54CC 800B48CC 00000000 */   nop   
/* 0B54D0 800B48D0 03E00008 */  jr    $ra
/* 0B54D4 800B48D4 24020001 */   li    $v0, 1

.L800B48D8:
/* 0B54D8 800B48D8 90820000 */  lbu   $v0, ($a0)
/* 0B54DC 800B48DC 24A50001 */  addiu $a1, $a1, 1
/* 0B54E0 800B48E0 14400005 */  bnez  $v0, .L800B48F8
/* 0B54E4 800B48E4 24C6FFFF */   addiu $a2, $a2, -1
/* 0B54E8 800B48E8 90B90000 */  lbu   $t9, ($a1)
/* 0B54EC 800B48EC 00000000 */  nop   
/* 0B54F0 800B48F0 13200003 */  beqz  $t9, .L800B4900
/* 0B54F4 800B48F4 00000000 */   nop   
.L800B48F8:
/* 0B54F8 800B48F8 14C0FFDD */  bnez  $a2, .L800B4870
/* 0B54FC 800B48FC 304700FF */   andi  $a3, $v0, 0xff
.L800B4900:
/* 0B5500 800B4900 00001025 */  move  $v0, $zero
/* 0B5504 800B4904 03E00008 */  jr    $ra
/* 0B5508 800B4908 00000000 */   nop   

/* 0B550C 800B490C 2CC30001 */  sltiu $v1, $a2, 1
/* 0B5510 800B4910 38630001 */  xori  $v1, $v1, 1
/* 0B5514 800B4914 00801025 */  move  $v0, $a0
/* 0B5518 800B4918 10600007 */  beqz  $v1, .L800B4938
/* 0B551C 800B491C 24C6FFFF */   addiu $a2, $a2, -1
.L800B4920:
/* 0B5520 800B4920 2CC30001 */  sltiu $v1, $a2, 1
/* 0B5524 800B4924 38630001 */  xori  $v1, $v1, 1
/* 0B5528 800B4928 24C6FFFF */  addiu $a2, $a2, -1
/* 0B552C 800B492C A0450000 */  sb    $a1, ($v0)
/* 0B5530 800B4930 1460FFFB */  bnez  $v1, .L800B4920
/* 0B5534 800B4934 24420001 */   addiu $v0, $v0, 1
.L800B4938:
/* 0B5538 800B4938 03E00008 */  jr    $ra
/* 0B553C 800B493C 00801025 */   move  $v0, $a0

glabel func_800B4940
/* 0B5540 800B4940 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0B5544 800B4944 8FAE0048 */  lw    $t6, 0x48($sp)
/* 0B5548 800B4948 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B554C 800B494C AFB10018 */  sw    $s1, 0x18($sp)
/* 0B5550 800B4950 AFB00014 */  sw    $s0, 0x14($sp)
/* 0B5554 800B4954 AFA40038 */  sw    $a0, 0x38($sp)
/* 0B5558 800B4958 11C00004 */  beqz  $t6, .L800B496C
/* 0B555C 800B495C AFA5003C */   sw    $a1, 0x3c($sp)
/* 0B5560 800B4960 3C11800F */  lui   $s1, %hi(D_800E8C28) # $s1, 0x800f
/* 0B5564 800B4964 10000003 */  b     .L800B4974
/* 0B5568 800B4968 26318C28 */   addiu $s1, %lo(D_800E8C28) # addiu $s1, $s1, -0x73d8
.L800B496C:
/* 0B556C 800B496C 3C11800F */  lui   $s1, %hi(D_800E8C00) # $s1, 0x800f
/* 0B5570 800B4970 26318C00 */  addiu $s1, %lo(D_800E8C00) # addiu $s1, $s1, -0x7400
.L800B4974:
/* 0B5574 800B4974 8FB80038 */  lw    $t8, 0x38($sp)
/* 0B5578 800B4978 8FB9003C */  lw    $t9, 0x3c($sp)
/* 0B557C 800B497C 00C08025 */  move  $s0, $a2
/* 0B5580 800B4980 17000003 */  bnez  $t8, .L800B4990
/* 0B5584 800B4984 24080000 */   li    $t0, 0
/* 0B5588 800B4988 1320001A */  beqz  $t9, .L800B49F4
/* 0B558C 800B498C 8FBF001C */   lw    $ra, 0x1c($sp)
.L800B4990:
/* 0B5590 800B4990 AFA80020 */  sw    $t0, 0x20($sp)
/* 0B5594 800B4994 AFA70024 */  sw    $a3, 0x24($sp)
.L800B4998:
/* 0B5598 800B4998 8FA40038 */  lw    $a0, 0x38($sp)
.L800B499C:
/* 0B559C 800B499C 8FA5003C */  lw    $a1, 0x3c($sp)
/* 0B55A0 800B49A0 8FA60020 */  lw    $a2, 0x20($sp)
/* 0B55A4 800B49A4 8FA70024 */  lw    $a3, 0x24($sp)
/* 0B55A8 800B49A8 0C033AA3 */  jal   __ull_rem
/* 0B55AC 800B49AC 2610FFFF */   addiu $s0, $s0, -1
/* 0B55B0 800B49B0 00715021 */  addu  $t2, $v1, $s1
/* 0B55B4 800B49B4 914B0000 */  lbu   $t3, ($t2)
/* 0B55B8 800B49B8 00000000 */  nop   
/* 0B55BC 800B49BC A20B0000 */  sb    $t3, ($s0)
/* 0B55C0 800B49C0 8FA70024 */  lw    $a3, 0x24($sp)
/* 0B55C4 800B49C4 8FA60020 */  lw    $a2, 0x20($sp)
/* 0B55C8 800B49C8 8FA5003C */  lw    $a1, 0x3c($sp)
/* 0B55CC 800B49CC 8FA40038 */  lw    $a0, 0x38($sp)
/* 0B55D0 800B49D0 0C033AB2 */  jal   __ull_div
/* 0B55D4 800B49D4 00000000 */   nop   
/* 0B55D8 800B49D8 AFA20038 */  sw    $v0, 0x38($sp)
/* 0B55DC 800B49DC AFA3003C */  sw    $v1, 0x3c($sp)
/* 0B55E0 800B49E0 1440FFED */  bnez  $v0, .L800B4998
/* 0B55E4 800B49E4 00606825 */   move  $t5, $v1
/* 0B55E8 800B49E8 15A0FFEC */  bnez  $t5, .L800B499C
/* 0B55EC 800B49EC 8FA40038 */   lw    $a0, 0x38($sp)
/* 0B55F0 800B49F0 8FBF001C */  lw    $ra, 0x1c($sp)
.L800B49F4:
/* 0B55F4 800B49F4 02001025 */  move  $v0, $s0
/* 0B55F8 800B49F8 8FB00014 */  lw    $s0, 0x14($sp)
/* 0B55FC 800B49FC 8FB10018 */  lw    $s1, 0x18($sp)
/* 0B5600 800B4A00 03E00008 */  jr    $ra
/* 0B5604 800B4A04 27BD0038 */   addiu $sp, $sp, 0x38

glabel func_800B4A08
/* 0B5608 800B4A08 3C01800E */  lui   $at, 0x800e
/* 0B560C 800B4A0C 03E00008 */  jr    $ra
/* 0B5610 800B4A10 AC242EF0 */   sw    $a0, 0x2ef0($at)

/* 0B5614 800B4A14 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0B5618 800B4A18 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B561C 800B4A1C AFA60028 */  sw    $a2, 0x28($sp)
/* 0B5620 800B4A20 AFA50024 */  sw    $a1, 0x24($sp)
/* 0B5624 800B4A24 AFA7002C */  sw    $a3, 0x2c($sp)
/* 0B5628 800B4A28 0C02D290 */  jal   func_800B4A40
/* 0B562C 800B4A2C 27A60028 */   addiu $a2, $sp, 0x28
/* 0B5630 800B4A30 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B5634 800B4A34 27BD0020 */  addiu $sp, $sp, 0x20
/* 0B5638 800B4A38 03E00008 */  jr    $ra
/* 0B563C 800B4A3C 00000000 */   nop   

glabel func_800B4A40
/* 0B5640 800B4A40 27BDFE48 */  addiu $sp, $sp, -0x1b8
/* 0B5644 800B4A44 AFBF004C */  sw    $ra, 0x4c($sp)
/* 0B5648 800B4A48 AFBE0048 */  sw    $fp, 0x48($sp)
/* 0B564C 800B4A4C AFB70044 */  sw    $s7, 0x44($sp)
/* 0B5650 800B4A50 AFB60040 */  sw    $s6, 0x40($sp)
/* 0B5654 800B4A54 AFB5003C */  sw    $s5, 0x3c($sp)
/* 0B5658 800B4A58 AFB40038 */  sw    $s4, 0x38($sp)
/* 0B565C 800B4A5C AFB30034 */  sw    $s3, 0x34($sp)
/* 0B5660 800B4A60 AFB20030 */  sw    $s2, 0x30($sp)
/* 0B5664 800B4A64 AFB1002C */  sw    $s1, 0x2c($sp)
/* 0B5668 800B4A68 AFB00028 */  sw    $s0, 0x28($sp)
/* 0B566C 800B4A6C E7B50020 */  swc1  $f21, 0x20($sp)
/* 0B5670 800B4A70 E7B40024 */  swc1  $f20, 0x24($sp)
/* 0B5674 800B4A74 90AE0000 */  lbu   $t6, ($a1)
/* 0B5678 800B4A78 00808025 */  move  $s0, $a0
/* 0B567C 800B4A7C 00C08825 */  move  $s1, $a2
/* 0B5680 800B4A80 00004825 */  move  $t1, $zero
/* 0B5684 800B4A84 11C004F0 */  beqz  $t6, .L800B5E48
/* 0B5688 800B4A88 00A05825 */   move  $t3, $a1
/* 0B568C 800B4A8C 3C013FF0 */  li    $at, 0x3FF00000 # 1.875000
/* 0B5690 800B4A90 4481A800 */  mtc1  $at, $f21
/* 0B5694 800B4A94 90A30000 */  lbu   $v1, ($a1)
/* 0B5698 800B4A98 3C014024 */  li    $at, 0x40240000 # 2.562500
/* 0B569C 800B4A9C 44819800 */  mtc1  $at, $f19
/* 0B56A0 800B4AA0 4480A000 */  mtc1  $zero, $f20
/* 0B56A4 800B4AA4 44809000 */  mtc1  $zero, $f18
/* 0B56A8 800B4AA8 C7B100E0 */  lwc1  $f17, 0xe0($sp)
/* 0B56AC 800B4AAC C7B000E4 */  lwc1  $f16, 0xe4($sp)
/* 0B56B0 800B4AB0 8FB400C8 */  lw    $s4, 0xc8($sp)
/* 0B56B4 800B4AB4 240D0020 */  li    $t5, 32
/* 0B56B8 800B4AB8 24040025 */  li    $a0, 37
/* 0B56BC 800B4ABC 00601025 */  move  $v0, $v1
.L800B4AC0:
/* 0B56C0 800B4AC0 1082000F */  beq   $a0, $v0, .L800B4B00
/* 0B56C4 800B4AC4 00000000 */   nop   
/* 0B56C8 800B4AC8 108204D8 */  beq   $a0, $v0, .L800B5E2C
/* 0B56CC 800B4ACC 00000000 */   nop   
/* 0B56D0 800B4AD0 104004D6 */  beqz  $v0, .L800B5E2C
/* 0B56D4 800B4AD4 00000000 */   nop   
.L800B4AD8:
/* 0B56D8 800B4AD8 A2030000 */  sb    $v1, ($s0)
/* 0B56DC 800B4ADC 91630001 */  lbu   $v1, 1($t3)
/* 0B56E0 800B4AE0 25290001 */  addiu $t1, $t1, 1
/* 0B56E4 800B4AE4 26100001 */  addiu $s0, $s0, 1
/* 0B56E8 800B4AE8 108304D0 */  beq   $a0, $v1, .L800B5E2C
/* 0B56EC 800B4AEC 256B0001 */   addiu $t3, $t3, 1
/* 0B56F0 800B4AF0 1460FFF9 */  bnez  $v1, .L800B4AD8
/* 0B56F4 800B4AF4 00000000 */   nop   
/* 0B56F8 800B4AF8 100004CD */  b     .L800B5E30
/* 0B56FC 800B4AFC 91630000 */   lbu   $v1, ($t3)
.L800B4B00:
/* 0B5700 800B4B00 91630001 */  lbu   $v1, 1($t3)
/* 0B5704 800B4B04 256B0001 */  addiu $t3, $t3, 1
/* 0B5708 800B4B08 14830007 */  bne   $a0, $v1, .L800B4B28
/* 0B570C 800B4B0C 00601025 */   move  $v0, $v1
/* 0B5710 800B4B10 240F0025 */  li    $t7, 37
/* 0B5714 800B4B14 256B0001 */  addiu $t3, $t3, 1
/* 0B5718 800B4B18 A20F0000 */  sb    $t7, ($s0)
/* 0B571C 800B4B1C 25290001 */  addiu $t1, $t1, 1
/* 0B5720 800B4B20 100004C2 */  b     .L800B5E2C
/* 0B5724 800B4B24 26100001 */   addiu $s0, $s0, 1
.L800B4B28:
/* 0B5728 800B4B28 24010020 */  li    $at, 32
/* 0B572C 800B4B2C 0000F025 */  move  $fp, $zero
/* 0B5730 800B4B30 0000B825 */  move  $s7, $zero
/* 0B5734 800B4B34 0000A825 */  move  $s5, $zero
/* 0B5738 800B4B38 0000B025 */  move  $s6, $zero
/* 0B573C 800B4B3C 31AC00FF */  andi  $t4, $t5, 0xff
/* 0B5740 800B4B40 00004025 */  move  $t0, $zero
/* 0B5744 800B4B44 240AFFFF */  li    $t2, -1
/* 0B5748 800B4B48 00002025 */  move  $a0, $zero
/* 0B574C 800B4B4C 00002825 */  move  $a1, $zero
/* 0B5750 800B4B50 10410009 */  beq   $v0, $at, .L800B4B78
/* 0B5754 800B4B54 00003025 */   move  $a2, $zero
/* 0B5758 800B4B58 2401002B */  li    $at, 43
/* 0B575C 800B4B5C 10410006 */  beq   $v0, $at, .L800B4B78
/* 0B5760 800B4B60 2401002D */   li    $at, 45
/* 0B5764 800B4B64 10410004 */  beq   $v0, $at, .L800B4B78
/* 0B5768 800B4B68 24010023 */   li    $at, 35
/* 0B576C 800B4B6C 10410002 */  beq   $v0, $at, .L800B4B78
/* 0B5770 800B4B70 24010030 */   li    $at, 48
/* 0B5774 800B4B74 14410024 */  bne   $v0, $at, .L800B4C08
.L800B4B78:
/* 0B5778 800B4B78 2458FFE0 */   addiu $t8, $v0, -0x20
.L800B4B7C:
/* 0B577C 800B4B7C 2F010011 */  sltiu $at, $t8, 0x11
/* 0B5780 800B4B80 10200011 */  beqz  $at, .L800B4BC8
/* 0B5784 800B4B84 256B0001 */   addiu $t3, $t3, 1
/* 0B5788 800B4B88 0018C080 */  sll   $t8, $t8, 2
/* 0B578C 800B4B8C 3C01800F */  lui   $at, 0x800f
/* 0B5790 800B4B90 00380821 */  addu  $at, $at, $t8
/* 0B5794 800B4B94 8C388CAC */  lw    $t8, -0x7354($at)
/* 0B5798 800B4B98 00000000 */  nop   
/* 0B579C 800B4B9C 03000008 */  jr    $t8
/* 0B57A0 800B4BA0 00000000 */   nop   
/* 0B57A4 800B4BA4 10000008 */  b     .L800B4BC8
/* 0B57A8 800B4BA8 24160001 */   li    $s6, 1
/* 0B57AC 800B4BAC 10000006 */  b     .L800B4BC8
/* 0B57B0 800B4BB0 24150001 */   li    $s5, 1
/* 0B57B4 800B4BB4 10000004 */  b     .L800B4BC8
/* 0B57B8 800B4BB8 24170001 */   li    $s7, 1
/* 0B57BC 800B4BBC 10000002 */  b     .L800B4BC8
/* 0B57C0 800B4BC0 241E0001 */   li    $fp, 1
/* 0B57C4 800B4BC4 240C0030 */  li    $t4, 48
.L800B4BC8:
/* 0B57C8 800B4BC8 91630000 */  lbu   $v1, ($t3)
/* 0B57CC 800B4BCC 24010020 */  li    $at, 32
/* 0B57D0 800B4BD0 1061FFE9 */  beq   $v1, $at, .L800B4B78
/* 0B57D4 800B4BD4 00601025 */   move  $v0, $v1
/* 0B57D8 800B4BD8 2401002B */  li    $at, 43
/* 0B57DC 800B4BDC 1061FFE7 */  beq   $v1, $at, .L800B4B7C
/* 0B57E0 800B4BE0 2458FFE0 */   addiu $t8, $v0, -0x20
/* 0B57E4 800B4BE4 2401002D */  li    $at, 45
/* 0B57E8 800B4BE8 1061FFE4 */  beq   $v1, $at, .L800B4B7C
/* 0B57EC 800B4BEC 2458FFE0 */   addiu $t8, $v0, -0x20
/* 0B57F0 800B4BF0 24010023 */  li    $at, 35
/* 0B57F4 800B4BF4 1061FFE1 */  beq   $v1, $at, .L800B4B7C
/* 0B57F8 800B4BF8 2458FFE0 */   addiu $t8, $v0, -0x20
/* 0B57FC 800B4BFC 24010030 */  li    $at, 48
/* 0B5800 800B4C00 1061FFDE */  beq   $v1, $at, .L800B4B7C
/* 0B5804 800B4C04 2458FFE0 */   addiu $t8, $v0, -0x20
.L800B4C08:
/* 0B5808 800B4C08 12E00002 */  beqz  $s7, .L800B4C14
/* 0B580C 800B4C0C 2401002A */   li    $at, 42
/* 0B5810 800B4C10 31AC00FF */  andi  $t4, $t5, 0xff
.L800B4C14:
/* 0B5814 800B4C14 1441000F */  bne   $v0, $at, .L800B4C54
/* 0B5818 800B4C18 28410030 */   slti  $at, $v0, 0x30
/* 0B581C 800B4C1C 26310003 */  addiu $s1, $s1, 3
/* 0B5820 800B4C20 2401FFFC */  li    $at, -4
/* 0B5824 800B4C24 0221C824 */  and   $t9, $s1, $at
/* 0B5828 800B4C28 27310004 */  addiu $s1, $t9, 4
/* 0B582C 800B4C2C 8E28FFFC */  lw    $t0, -4($s1)
/* 0B5830 800B4C30 256B0001 */  addiu $t3, $t3, 1
/* 0B5834 800B4C34 05010003 */  bgez  $t0, .L800B4C44
/* 0B5838 800B4C38 00000000 */   nop   
/* 0B583C 800B4C3C 00084023 */  negu  $t0, $t0
/* 0B5840 800B4C40 24170001 */  li    $s7, 1
.L800B4C44:
/* 0B5844 800B4C44 91630000 */  lbu   $v1, ($t3)
/* 0B5848 800B4C48 10000012 */  b     .L800B4C94
/* 0B584C 800B4C4C 00601025 */   move  $v0, $v1
/* 0B5850 800B4C50 28410030 */  slti  $at, $v0, 0x30
.L800B4C54:
/* 0B5854 800B4C54 1420000F */  bnez  $at, .L800B4C94
/* 0B5858 800B4C58 2841003A */   slti  $at, $v0, 0x3a
/* 0B585C 800B4C5C 1020000D */  beqz  $at, .L800B4C94
/* 0B5860 800B4C60 00087080 */   sll   $t6, $t0, 2
.L800B4C64:
/* 0B5864 800B4C64 91630001 */  lbu   $v1, 1($t3)
/* 0B5868 800B4C68 01C87021 */  addu  $t6, $t6, $t0
/* 0B586C 800B4C6C 000E7040 */  sll   $t6, $t6, 1
/* 0B5870 800B4C70 01C24021 */  addu  $t0, $t6, $v0
/* 0B5874 800B4C74 28610030 */  slti  $at, $v1, 0x30
/* 0B5878 800B4C78 2508FFD0 */  addiu $t0, $t0, -0x30
/* 0B587C 800B4C7C 256B0001 */  addiu $t3, $t3, 1
/* 0B5880 800B4C80 14200004 */  bnez  $at, .L800B4C94
/* 0B5884 800B4C84 00601025 */   move  $v0, $v1
/* 0B5888 800B4C88 2841003A */  slti  $at, $v0, 0x3a
/* 0B588C 800B4C8C 1420FFF5 */  bnez  $at, .L800B4C64
/* 0B5890 800B4C90 00087080 */   sll   $t6, $t0, 2
.L800B4C94:
/* 0B5894 800B4C94 2401002E */  li    $at, 46
/* 0B5898 800B4C98 14410029 */  bne   $v0, $at, .L800B4D40
/* 0B589C 800B4C9C 24010068 */   li    $at, 104
/* 0B58A0 800B4CA0 91630001 */  lbu   $v1, 1($t3)
/* 0B58A4 800B4CA4 2401002A */  li    $at, 42
/* 0B58A8 800B4CA8 256B0001 */  addiu $t3, $t3, 1
/* 0B58AC 800B4CAC 1461000D */  bne   $v1, $at, .L800B4CE4
/* 0B58B0 800B4CB0 00601025 */   move  $v0, $v1
/* 0B58B4 800B4CB4 26310003 */  addiu $s1, $s1, 3
/* 0B58B8 800B4CB8 2401FFFC */  li    $at, -4
/* 0B58BC 800B4CBC 02217824 */  and   $t7, $s1, $at
/* 0B58C0 800B4CC0 25F10004 */  addiu $s1, $t7, 4
/* 0B58C4 800B4CC4 8E2AFFFC */  lw    $t2, -4($s1)
/* 0B58C8 800B4CC8 256B0001 */  addiu $t3, $t3, 1
/* 0B58CC 800B4CCC 05410002 */  bgez  $t2, .L800B4CD8
/* 0B58D0 800B4CD0 00000000 */   nop   
/* 0B58D4 800B4CD4 240AFFFF */  li    $t2, -1
.L800B4CD8:
/* 0B58D8 800B4CD8 91630000 */  lbu   $v1, ($t3)
/* 0B58DC 800B4CDC 10000017 */  b     .L800B4D3C
/* 0B58E0 800B4CE0 00601025 */   move  $v0, $v1
.L800B4CE4:
/* 0B58E4 800B4CE4 28410030 */  slti  $at, $v0, 0x30
/* 0B58E8 800B4CE8 14200014 */  bnez  $at, .L800B4D3C
/* 0B58EC 800B4CEC 2841003A */   slti  $at, $v0, 0x3a
/* 0B58F0 800B4CF0 10200012 */  beqz  $at, .L800B4D3C
/* 0B58F4 800B4CF4 28410030 */   slti  $at, $v0, 0x30
/* 0B58F8 800B4CF8 14200010 */  bnez  $at, .L800B4D3C
/* 0B58FC 800B4CFC 00005025 */   move  $t2, $zero
/* 0B5900 800B4D00 2841003A */  slti  $at, $v0, 0x3a
/* 0B5904 800B4D04 1020000D */  beqz  $at, .L800B4D3C
/* 0B5908 800B4D08 000AC080 */   sll   $t8, $t2, 2
.L800B4D0C:
/* 0B590C 800B4D0C 91630001 */  lbu   $v1, 1($t3)
/* 0B5910 800B4D10 030AC021 */  addu  $t8, $t8, $t2
/* 0B5914 800B4D14 0018C040 */  sll   $t8, $t8, 1
/* 0B5918 800B4D18 03025021 */  addu  $t2, $t8, $v0
/* 0B591C 800B4D1C 28610030 */  slti  $at, $v1, 0x30
/* 0B5920 800B4D20 254AFFD0 */  addiu $t2, $t2, -0x30
/* 0B5924 800B4D24 256B0001 */  addiu $t3, $t3, 1
/* 0B5928 800B4D28 14200004 */  bnez  $at, .L800B4D3C
/* 0B592C 800B4D2C 00601025 */   move  $v0, $v1
/* 0B5930 800B4D30 2841003A */  slti  $at, $v0, 0x3a
/* 0B5934 800B4D34 1420FFF5 */  bnez  $at, .L800B4D0C
/* 0B5938 800B4D38 000AC080 */   sll   $t8, $t2, 2
.L800B4D3C:
/* 0B593C 800B4D3C 24010068 */  li    $at, 104
.L800B4D40:
/* 0B5940 800B4D40 10410008 */  beq   $v0, $at, .L800B4D64
/* 0B5944 800B4D44 2401006C */   li    $at, 108
/* 0B5948 800B4D48 10410006 */  beq   $v0, $at, .L800B4D64
/* 0B594C 800B4D4C 2401004C */   li    $at, 76
/* 0B5950 800B4D50 10410004 */  beq   $v0, $at, .L800B4D64
/* 0B5954 800B4D54 2401005A */   li    $at, 90
/* 0B5958 800B4D58 10410002 */  beq   $v0, $at, .L800B4D64
/* 0B595C 800B4D5C 24010071 */   li    $at, 113
/* 0B5960 800B4D60 14410028 */  bne   $v0, $at, .L800B4E04
.L800B4D64:
/* 0B5964 800B4D64 2459FFB4 */   addiu $t9, $v0, -0x4c
.L800B4D68:
/* 0B5968 800B4D68 2F210026 */  sltiu $at, $t9, 0x26
/* 0B596C 800B4D6C 10200015 */  beqz  $at, .L800B4DC4
/* 0B5970 800B4D70 256B0001 */   addiu $t3, $t3, 1
/* 0B5974 800B4D74 0019C880 */  sll   $t9, $t9, 2
/* 0B5978 800B4D78 3C01800F */  lui   $at, 0x800f
/* 0B597C 800B4D7C 00390821 */  addu  $at, $at, $t9
/* 0B5980 800B4D80 8C398CF0 */  lw    $t9, -0x7310($at)
/* 0B5984 800B4D84 00000000 */  nop   
/* 0B5988 800B4D88 03200008 */  jr    $t9
/* 0B598C 800B4D8C 00000000 */   nop   
/* 0B5990 800B4D90 1000000C */  b     .L800B4DC4
/* 0B5994 800B4D94 24060001 */   li    $a2, 1
/* 0B5998 800B4D98 10A00003 */  beqz  $a1, .L800B4DA8
/* 0B599C 800B4D9C 00000000 */   nop   
/* 0B59A0 800B4DA0 10000008 */  b     .L800B4DC4
/* 0B59A4 800B4DA4 24040001 */   li    $a0, 1
.L800B4DA8:
/* 0B59A8 800B4DA8 10000006 */  b     .L800B4DC4
/* 0B59AC 800B4DAC 24050001 */   li    $a1, 1
/* 0B59B0 800B4DB0 10000004 */  b     .L800B4DC4
/* 0B59B4 800B4DB4 24040001 */   li    $a0, 1
/* 0B59B8 800B4DB8 10000002 */  b     .L800B4DC4
/* 0B59BC 800B4DBC 24050001 */   li    $a1, 1
/* 0B59C0 800B4DC0 24040001 */  li    $a0, 1
.L800B4DC4:
/* 0B59C4 800B4DC4 91630000 */  lbu   $v1, ($t3)
/* 0B59C8 800B4DC8 24010068 */  li    $at, 104
/* 0B59CC 800B4DCC 1061FFE5 */  beq   $v1, $at, .L800B4D64
/* 0B59D0 800B4DD0 00601025 */   move  $v0, $v1
/* 0B59D4 800B4DD4 2401006C */  li    $at, 108
/* 0B59D8 800B4DD8 1061FFE3 */  beq   $v1, $at, .L800B4D68
/* 0B59DC 800B4DDC 2459FFB4 */   addiu $t9, $v0, -0x4c
/* 0B59E0 800B4DE0 2401004C */  li    $at, 76
/* 0B59E4 800B4DE4 1061FFE0 */  beq   $v1, $at, .L800B4D68
/* 0B59E8 800B4DE8 2459FFB4 */   addiu $t9, $v0, -0x4c
/* 0B59EC 800B4DEC 2401005A */  li    $at, 90
/* 0B59F0 800B4DF0 1061FFDD */  beq   $v1, $at, .L800B4D68
/* 0B59F4 800B4DF4 2459FFB4 */   addiu $t9, $v0, -0x4c
/* 0B59F8 800B4DF8 24010071 */  li    $at, 113
/* 0B59FC 800B4DFC 1061FFDA */  beq   $v1, $at, .L800B4D68
/* 0B5A00 800B4E00 2459FFB4 */   addiu $t9, $v0, -0x4c
.L800B4E04:
/* 0B5A04 800B4E04 307300FF */  andi  $s3, $v1, 0xff
/* 0B5A08 800B4E08 266EFFBB */  addiu $t6, $s3, -0x45
/* 0B5A0C 800B4E0C 2DC10034 */  sltiu $at, $t6, 0x34
/* 0B5A10 800B4E10 256B0001 */  addiu $t3, $t3, 1
/* 0B5A14 800B4E14 102003FD */  beqz  $at, .L800B5E0C
/* 0B5A18 800B4E18 A3B3019A */   sb    $s3, 0x19a($sp)
/* 0B5A1C 800B4E1C 000E7080 */  sll   $t6, $t6, 2
/* 0B5A20 800B4E20 3C01800F */  lui   $at, 0x800f
/* 0B5A24 800B4E24 002E0821 */  addu  $at, $at, $t6
/* 0B5A28 800B4E28 8C2E8D88 */  lw    $t6, -0x7278($at)
/* 0B5A2C 800B4E2C 00000000 */  nop   
/* 0B5A30 800B4E30 01C00008 */  jr    $t6
/* 0B5A34 800B4E34 00000000 */   nop   
/* 0B5A38 800B4E38 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B5A3C 800B4E3C 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B5A40 800B4E40 2407000A */  li    $a3, 10
/* 0B5A44 800B4E44 1080000A */  beqz  $a0, .L800B4E70
/* 0B5A48 800B4E48 27BF017B */   addiu $ra, $sp, 0x17b
/* 0B5A4C 800B4E4C 26310007 */  addiu $s1, $s1, 7
/* 0B5A50 800B4E50 2401FFF8 */  li    $at, -8
/* 0B5A54 800B4E54 02217824 */  and   $t7, $s1, $at
/* 0B5A58 800B4E58 25F10008 */  addiu $s1, $t7, 8
/* 0B5A5C 800B4E5C 8E38FFF8 */  lw    $t8, -8($s1)
/* 0B5A60 800B4E60 8E39FFFC */  lw    $t9, -4($s1)
/* 0B5A64 800B4E64 AFB80180 */  sw    $t8, 0x180($sp)
/* 0B5A68 800B4E68 10000020 */  b     .L800B4EEC
/* 0B5A6C 800B4E6C AFB90184 */   sw    $t9, 0x184($sp)
.L800B4E70:
/* 0B5A70 800B4E70 10A0000A */  beqz  $a1, .L800B4E9C
/* 0B5A74 800B4E74 2401FFFC */   li    $at, -4
/* 0B5A78 800B4E78 26310003 */  addiu $s1, $s1, 3
/* 0B5A7C 800B4E7C 02217024 */  and   $t6, $s1, $at
/* 0B5A80 800B4E80 25D10004 */  addiu $s1, $t6, 4
/* 0B5A84 800B4E84 8E2FFFFC */  lw    $t7, -4($s1)
/* 0B5A88 800B4E88 00000000 */  nop   
/* 0B5A8C 800B4E8C 000FC7C3 */  sra   $t8, $t7, 0x1f
/* 0B5A90 800B4E90 AFB80180 */  sw    $t8, 0x180($sp)
/* 0B5A94 800B4E94 10000015 */  b     .L800B4EEC
/* 0B5A98 800B4E98 AFAF0184 */   sw    $t7, 0x184($sp)
.L800B4E9C:
/* 0B5A9C 800B4E9C 14C0000B */  bnez  $a2, .L800B4ECC
/* 0B5AA0 800B4EA0 2401FFFC */   li    $at, -4
/* 0B5AA4 800B4EA4 26310003 */  addiu $s1, $s1, 3
/* 0B5AA8 800B4EA8 2401FFFC */  li    $at, -4
/* 0B5AAC 800B4EAC 02217024 */  and   $t6, $s1, $at
/* 0B5AB0 800B4EB0 25D10004 */  addiu $s1, $t6, 4
/* 0B5AB4 800B4EB4 8E2FFFFC */  lw    $t7, -4($s1)
/* 0B5AB8 800B4EB8 00000000 */  nop   
/* 0B5ABC 800B4EBC 000FC7C3 */  sra   $t8, $t7, 0x1f
/* 0B5AC0 800B4EC0 AFB80180 */  sw    $t8, 0x180($sp)
/* 0B5AC4 800B4EC4 10000009 */  b     .L800B4EEC
/* 0B5AC8 800B4EC8 AFAF0184 */   sw    $t7, 0x184($sp)
.L800B4ECC:
/* 0B5ACC 800B4ECC 26310003 */  addiu $s1, $s1, 3
/* 0B5AD0 800B4ED0 02217024 */  and   $t6, $s1, $at
/* 0B5AD4 800B4ED4 25D10004 */  addiu $s1, $t6, 4
/* 0B5AD8 800B4ED8 862FFFFE */  lh    $t7, -2($s1)
/* 0B5ADC 800B4EDC 00000000 */  nop   
/* 0B5AE0 800B4EE0 000FC7C3 */  sra   $t8, $t7, 0x1f
/* 0B5AE4 800B4EE4 AFB80180 */  sw    $t8, 0x180($sp)
/* 0B5AE8 800B4EE8 AFAF0184 */  sw    $t7, 0x184($sp)
.L800B4EEC:
/* 0B5AEC 800B4EEC 8FAE0180 */  lw    $t6, 0x180($sp)
/* 0B5AF0 800B4EF0 8FAF0184 */  lw    $t7, 0x184($sp)
/* 0B5AF4 800B4EF4 29C20000 */  slti  $v0, $t6, 0
/* 0B5AF8 800B4EF8 1C400004 */  bgtz  $v0, .L800B4F0C
/* 0B5AFC 800B4EFC 2DE10001 */   sltiu $at, $t7, 1
/* 0B5B00 800B4F00 1DC00003 */  bgtz  $t6, .L800B4F10
/* 0B5B04 800B4F04 305800FF */   andi  $t8, $v0, 0xff
/* 0B5B08 800B4F08 2DE20000 */  sltiu $v0, $t7, 0
.L800B4F0C:
/* 0B5B0C 800B4F0C 305800FF */  andi  $t8, $v0, 0xff
.L800B4F10:
/* 0B5B10 800B4F10 13000007 */  beqz  $t8, .L800B4F30
/* 0B5B14 800B4F14 305200FF */   andi  $s2, $v0, 0xff
/* 0B5B18 800B4F18 01C0C027 */  not   $t8, $t6
/* 0B5B1C 800B4F1C 0301C021 */  addu  $t8, $t8, $at
/* 0B5B20 800B4F20 000FC823 */  negu  $t9, $t7
/* 0B5B24 800B4F24 AFB9018C */  sw    $t9, 0x18c($sp)
/* 0B5B28 800B4F28 1000004B */  b     .L800B5058
/* 0B5B2C 800B4F2C AFB80188 */   sw    $t8, 0x188($sp)
.L800B4F30:
/* 0B5B30 800B4F30 8FAE0180 */  lw    $t6, 0x180($sp)
/* 0B5B34 800B4F34 8FAF0184 */  lw    $t7, 0x184($sp)
/* 0B5B38 800B4F38 AFAE0188 */  sw    $t6, 0x188($sp)
/* 0B5B3C 800B4F3C 10000046 */  b     .L800B5058
/* 0B5B40 800B4F40 AFAF018C */   sw    $t7, 0x18c($sp)
/* 0B5B44 800B4F44 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B5B48 800B4F48 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B5B4C 800B4F4C 2407000A */  li    $a3, 10
/* 0B5B50 800B4F50 0000A825 */  move  $s5, $zero
/* 0B5B54 800B4F54 0000B025 */  move  $s6, $zero
/* 0B5B58 800B4F58 00009025 */  move  $s2, $zero
/* 0B5B5C 800B4F5C 10000018 */  b     .L800B4FC0
/* 0B5B60 800B4F60 27BF017B */   addiu $ra, $sp, 0x17b
/* 0B5B64 800B4F64 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B5B68 800B4F68 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B5B6C 800B4F6C 24070008 */  li    $a3, 8
/* 0B5B70 800B4F70 0000A825 */  move  $s5, $zero
/* 0B5B74 800B4F74 0000B025 */  move  $s6, $zero
/* 0B5B78 800B4F78 00009025 */  move  $s2, $zero
/* 0B5B7C 800B4F7C 10000010 */  b     .L800B4FC0
/* 0B5B80 800B4F80 27BF017B */   addiu $ra, $sp, 0x17b
/* 0B5B84 800B4F84 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B5B88 800B4F88 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B5B8C 800B4F8C 24070010 */  li    $a3, 16
/* 0B5B90 800B4F90 0000A825 */  move  $s5, $zero
/* 0B5B94 800B4F94 0000B025 */  move  $s6, $zero
/* 0B5B98 800B4F98 00009025 */  move  $s2, $zero
/* 0B5B9C 800B4F9C 10000008 */  b     .L800B4FC0
/* 0B5BA0 800B4FA0 27BF017B */   addiu $ra, $sp, 0x17b
/* 0B5BA4 800B4FA4 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B5BA8 800B4FA8 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B5BAC 800B4FAC 24070010 */  li    $a3, 16
/* 0B5BB0 800B4FB0 0000A825 */  move  $s5, $zero
/* 0B5BB4 800B4FB4 0000B025 */  move  $s6, $zero
/* 0B5BB8 800B4FB8 00009025 */  move  $s2, $zero
/* 0B5BBC 800B4FBC 27BF017B */  addiu $ra, $sp, 0x17b
.L800B4FC0:
/* 0B5BC0 800B4FC0 10800009 */  beqz  $a0, .L800B4FE8
/* 0B5BC4 800B4FC4 2401FFF8 */   li    $at, -8
/* 0B5BC8 800B4FC8 26310007 */  addiu $s1, $s1, 7
/* 0B5BCC 800B4FCC 0221C024 */  and   $t8, $s1, $at
/* 0B5BD0 800B4FD0 27110008 */  addiu $s1, $t8, 8
/* 0B5BD4 800B4FD4 8E2EFFF8 */  lw    $t6, -8($s1)
/* 0B5BD8 800B4FD8 8E2FFFFC */  lw    $t7, -4($s1)
/* 0B5BDC 800B4FDC AFAE0188 */  sw    $t6, 0x188($sp)
/* 0B5BE0 800B4FE0 1000001D */  b     .L800B5058
/* 0B5BE4 800B4FE4 AFAF018C */   sw    $t7, 0x18c($sp)
.L800B4FE8:
/* 0B5BE8 800B4FE8 10A00009 */  beqz  $a1, .L800B5010
/* 0B5BEC 800B4FEC 2401FFFC */   li    $at, -4
/* 0B5BF0 800B4FF0 26310003 */  addiu $s1, $s1, 3
/* 0B5BF4 800B4FF4 0221C824 */  and   $t9, $s1, $at
/* 0B5BF8 800B4FF8 27310004 */  addiu $s1, $t9, 4
/* 0B5BFC 800B4FFC 8E38FFFC */  lw    $t8, -4($s1)
/* 0B5C00 800B5000 240E0000 */  li    $t6, 0
/* 0B5C04 800B5004 AFAE0188 */  sw    $t6, 0x188($sp)
/* 0B5C08 800B5008 10000013 */  b     .L800B5058
/* 0B5C0C 800B500C AFB8018C */   sw    $t8, 0x18c($sp)
.L800B5010:
/* 0B5C10 800B5010 14C0000A */  bnez  $a2, .L800B503C
/* 0B5C14 800B5014 2401FFFC */   li    $at, -4
/* 0B5C18 800B5018 26310003 */  addiu $s1, $s1, 3
/* 0B5C1C 800B501C 2401FFFC */  li    $at, -4
/* 0B5C20 800B5020 0221C824 */  and   $t9, $s1, $at
/* 0B5C24 800B5024 27310004 */  addiu $s1, $t9, 4
/* 0B5C28 800B5028 8E38FFFC */  lw    $t8, -4($s1)
/* 0B5C2C 800B502C 240E0000 */  li    $t6, 0
/* 0B5C30 800B5030 AFAE0188 */  sw    $t6, 0x188($sp)
/* 0B5C34 800B5034 10000008 */  b     .L800B5058
/* 0B5C38 800B5038 AFB8018C */   sw    $t8, 0x18c($sp)
.L800B503C:
/* 0B5C3C 800B503C 26310003 */  addiu $s1, $s1, 3
/* 0B5C40 800B5040 0221C824 */  and   $t9, $s1, $at
/* 0B5C44 800B5044 27310004 */  addiu $s1, $t9, 4
/* 0B5C48 800B5048 9638FFFE */  lhu   $t8, -2($s1)
/* 0B5C4C 800B504C 240E0000 */  li    $t6, 0
/* 0B5C50 800B5050 AFAE0188 */  sw    $t6, 0x188($sp)
/* 0B5C54 800B5054 AFB8018C */  sw    $t8, 0x18c($sp)
.L800B5058:
/* 0B5C58 800B5058 10600005 */  beqz  $v1, .L800B5070
/* 0B5C5C 800B505C 2401FFFF */   li    $at, -1
/* 0B5C60 800B5060 24190084 */  li    $t9, 132
/* 0B5C64 800B5064 A2190000 */  sb    $t9, ($s0)
/* 0B5C68 800B5068 25290001 */  addiu $t1, $t1, 1
/* 0B5C6C 800B506C 26100001 */  addiu $s0, $s0, 1
.L800B5070:
/* 0B5C70 800B5070 05400002 */  bltz  $t2, .L800B507C
/* 0B5C74 800B5074 27A6017C */   addiu $a2, $sp, 0x17c
/* 0B5C78 800B5078 31AC00FF */  andi  $t4, $t5, 0xff
.L800B507C:
/* 0B5C7C 800B507C 15410002 */  bne   $t2, $at, .L800B5088
/* 0B5C80 800B5080 3A780058 */   xori  $t8, $s3, 0x58
/* 0B5C84 800B5084 240A0001 */  li    $t2, 1
.L800B5088:
/* 0B5C88 800B5088 8FA40188 */  lw    $a0, 0x188($sp)
/* 0B5C8C 800B508C 8FA5018C */  lw    $a1, 0x18c($sp)
/* 0B5C90 800B5090 2F180001 */  sltiu $t8, $t8, 1
/* 0B5C94 800B5094 AFBF00F8 */  sw    $ra, 0xf8($sp)
/* 0B5C98 800B5098 AFB80010 */  sw    $t8, 0x10($sp)
/* 0B5C9C 800B509C AFA70194 */  sw    $a3, 0x194($sp)
/* 0B5CA0 800B50A0 AFA801A0 */  sw    $t0, 0x1a0($sp)
/* 0B5CA4 800B50A4 AFA901AC */  sw    $t1, 0x1ac($sp)
/* 0B5CA8 800B50A8 AFAA019C */  sw    $t2, 0x19c($sp)
/* 0B5CAC 800B50AC AFAB01B4 */  sw    $t3, 0x1b4($sp)
/* 0B5CB0 800B50B0 A3AC01A4 */  sb    $t4, 0x1a4($sp)
/* 0B5CB4 800B50B4 E7B100E0 */  swc1  $f17, 0xe0($sp)
/* 0B5CB8 800B50B8 0C02D250 */  jal   func_800B4940
/* 0B5CBC 800B50BC E7B000E4 */   swc1  $f16, 0xe4($sp)
/* 0B5CC0 800B50C0 27AE017B */  addiu $t6, $sp, 0x17b
/* 0B5CC4 800B50C4 8FA801A0 */  lw    $t0, 0x1a0($sp)
/* 0B5CC8 800B50C8 8FAA019C */  lw    $t2, 0x19c($sp)
/* 0B5CCC 800B50CC 3C014024 */  li    $at, 0x40240000 # 2.562500
/* 0B5CD0 800B50D0 01C21823 */  subu  $v1, $t6, $v0
/* 0B5CD4 800B50D4 44819800 */  mtc1  $at, $f19
/* 0B5CD8 800B50D8 8FA70194 */  lw    $a3, 0x194($sp)
/* 0B5CDC 800B50DC 8FA901AC */  lw    $t1, 0x1ac($sp)
/* 0B5CE0 800B50E0 8FAB01B4 */  lw    $t3, 0x1b4($sp)
/* 0B5CE4 800B50E4 93AC01A4 */  lbu   $t4, 0x1a4($sp)
/* 0B5CE8 800B50E8 8FBF00F8 */  lw    $ra, 0xf8($sp)
/* 0B5CEC 800B50EC C7B100E0 */  lwc1  $f17, 0xe0($sp)
/* 0B5CF0 800B50F0 C7B000E4 */  lwc1  $f16, 0xe4($sp)
/* 0B5CF4 800B50F4 44809000 */  mtc1  $zero, $f18
/* 0B5CF8 800B50F8 2445FFFF */  addiu $a1, $v0, -1
/* 0B5CFC 800B50FC 24630001 */  addiu $v1, $v1, 1
/* 0B5D00 800B5100 001E302B */  sltu  $a2, $zero, $fp
/* 0B5D04 800B5104 00A02025 */  move  $a0, $a1
/* 0B5D08 800B5108 240D0020 */  li    $t5, 32
/* 0B5D0C 800B510C 01034023 */  subu  $t0, $t0, $v1
/* 0B5D10 800B5110 10C00009 */  beqz  $a2, .L800B5138
/* 0B5D14 800B5114 01435023 */   subu  $t2, $t2, $v1
/* 0B5D18 800B5118 24010008 */  li    $at, 8
/* 0B5D1C 800B511C 14E10007 */  bne   $a3, $at, .L800B513C
/* 0B5D20 800B5120 000A982A */   slt   $s3, $zero, $t2
/* 0B5D24 800B5124 1D400004 */  bgtz  $t2, .L800B5138
/* 0B5D28 800B5128 240F0030 */   li    $t7, 48
/* 0B5D2C 800B512C A0AF0000 */  sb    $t7, ($a1)
/* 0B5D30 800B5130 24A4FFFF */  addiu $a0, $a1, -1
/* 0B5D34 800B5134 2508FFFF */  addiu $t0, $t0, -1
.L800B5138:
/* 0B5D38 800B5138 000A982A */  slt   $s3, $zero, $t2
.L800B513C:
/* 0B5D3C 800B513C 1260000A */  beqz  $s3, .L800B5168
/* 0B5D40 800B5140 24010010 */   li    $at, 16
/* 0B5D44 800B5144 010A4023 */  subu  $t0, $t0, $t2
/* 0B5D48 800B5148 12600007 */  beqz  $s3, .L800B5168
/* 0B5D4C 800B514C 254AFFFF */   addiu $t2, $t2, -1
/* 0B5D50 800B5150 24020030 */  li    $v0, 48
.L800B5154:
/* 0B5D54 800B5154 000A182A */  slt   $v1, $zero, $t2
/* 0B5D58 800B5158 254AFFFF */  addiu $t2, $t2, -1
/* 0B5D5C 800B515C A0820000 */  sb    $v0, ($a0)
/* 0B5D60 800B5160 1460FFFC */  bnez  $v1, .L800B5154
/* 0B5D64 800B5164 2484FFFF */   addiu $a0, $a0, -1
.L800B5168:
/* 0B5D68 800B5168 10C00004 */  beqz  $a2, .L800B517C
/* 0B5D6C 800B516C 24840001 */   addiu $a0, $a0, 1
/* 0B5D70 800B5170 14E10002 */  bne   $a3, $at, .L800B517C
/* 0B5D74 800B5174 00000000 */   nop   
/* 0B5D78 800B5178 2508FFFE */  addiu $t0, $t0, -2
.L800B517C:
/* 0B5D7C 800B517C 16400005 */  bnez  $s2, .L800B5194
/* 0B5D80 800B5180 24010020 */   li    $at, 32
/* 0B5D84 800B5184 16A00003 */  bnez  $s5, .L800B5194
/* 0B5D88 800B5188 00000000 */   nop   
/* 0B5D8C 800B518C 12C00002 */  beqz  $s6, .L800B5198
/* 0B5D90 800B5190 00000000 */   nop   
.L800B5194:
/* 0B5D94 800B5194 2508FFFF */  addiu $t0, $t0, -1
.L800B5198:
/* 0B5D98 800B5198 16E0000B */  bnez  $s7, .L800B51C8
/* 0B5D9C 800B519C 2419002D */   li    $t9, 45
/* 0B5DA0 800B51A0 15810009 */  bne   $t4, $at, .L800B51C8
/* 0B5DA4 800B51A4 0008182A */   slt   $v1, $zero, $t0
/* 0B5DA8 800B51A8 10600007 */  beqz  $v1, .L800B51C8
/* 0B5DAC 800B51AC 2508FFFF */   addiu $t0, $t0, -1
.L800B51B0:
/* 0B5DB0 800B51B0 0008182A */  slt   $v1, $zero, $t0
/* 0B5DB4 800B51B4 2508FFFF */  addiu $t0, $t0, -1
/* 0B5DB8 800B51B8 25290001 */  addiu $t1, $t1, 1
/* 0B5DBC 800B51BC A20D0000 */  sb    $t5, ($s0)
/* 0B5DC0 800B51C0 1460FFFB */  bnez  $v1, .L800B51B0
/* 0B5DC4 800B51C4 26100001 */   addiu $s0, $s0, 1
.L800B51C8:
/* 0B5DC8 800B51C8 12400005 */  beqz  $s2, .L800B51E0
/* 0B5DCC 800B51CC 24010010 */   li    $at, 16
/* 0B5DD0 800B51D0 25290001 */  addiu $t1, $t1, 1
/* 0B5DD4 800B51D4 A2190000 */  sb    $t9, ($s0)
/* 0B5DD8 800B51D8 1000000C */  b     .L800B520C
/* 0B5DDC 800B51DC 26100001 */   addiu $s0, $s0, 1
.L800B51E0:
/* 0B5DE0 800B51E0 12A00005 */  beqz  $s5, .L800B51F8
/* 0B5DE4 800B51E4 2418002B */   li    $t8, 43
/* 0B5DE8 800B51E8 25290001 */  addiu $t1, $t1, 1
/* 0B5DEC 800B51EC A2180000 */  sb    $t8, ($s0)
/* 0B5DF0 800B51F0 10000006 */  b     .L800B520C
/* 0B5DF4 800B51F4 26100001 */   addiu $s0, $s0, 1
.L800B51F8:
/* 0B5DF8 800B51F8 12C00004 */  beqz  $s6, .L800B520C
/* 0B5DFC 800B51FC 00000000 */   nop   
/* 0B5E00 800B5200 25290001 */  addiu $t1, $t1, 1
/* 0B5E04 800B5204 A20D0000 */  sb    $t5, ($s0)
/* 0B5E08 800B5208 26100001 */  addiu $s0, $s0, 1
.L800B520C:
/* 0B5E0C 800B520C 10C00008 */  beqz  $a2, .L800B5230
/* 0B5E10 800B5210 27B8017B */   addiu $t8, $sp, 0x17b
/* 0B5E14 800B5214 14E10006 */  bne   $a3, $at, .L800B5230
/* 0B5E18 800B5218 240E0030 */   li    $t6, 48
/* 0B5E1C 800B521C A20E0000 */  sb    $t6, ($s0)
/* 0B5E20 800B5220 93AF019A */  lbu   $t7, 0x19a($sp)
/* 0B5E24 800B5224 25290002 */  addiu $t1, $t1, 2
/* 0B5E28 800B5228 26100002 */  addiu $s0, $s0, 2
/* 0B5E2C 800B522C A20FFFFF */  sb    $t7, -1($s0)
.L800B5230:
/* 0B5E30 800B5230 16E0000C */  bnez  $s7, .L800B5264
/* 0B5E34 800B5234 24010030 */   li    $at, 48
/* 0B5E38 800B5238 1581000A */  bne   $t4, $at, .L800B5264
/* 0B5E3C 800B523C 0008182A */   slt   $v1, $zero, $t0
/* 0B5E40 800B5240 10600008 */  beqz  $v1, .L800B5264
/* 0B5E44 800B5244 2508FFFF */   addiu $t0, $t0, -1
.L800B5248:
/* 0B5E48 800B5248 24190030 */  li    $t9, 48
/* 0B5E4C 800B524C 0008182A */  slt   $v1, $zero, $t0
/* 0B5E50 800B5250 2508FFFF */  addiu $t0, $t0, -1
/* 0B5E54 800B5254 A2190000 */  sb    $t9, ($s0)
/* 0B5E58 800B5258 25290001 */  addiu $t1, $t1, 1
/* 0B5E5C 800B525C 1460FFFA */  bnez  $v1, .L800B5248
/* 0B5E60 800B5260 26100001 */   addiu $s0, $s0, 1
.L800B5264:
/* 0B5E64 800B5264 0304082B */  sltu  $at, $t8, $a0
/* 0B5E68 800B5268 14200008 */  bnez  $at, .L800B528C
/* 0B5E6C 800B526C 0008182A */   slt   $v1, $zero, $t0
.L800B5270:
/* 0B5E70 800B5270 908E0000 */  lbu   $t6, ($a0)
/* 0B5E74 800B5274 24840001 */  addiu $a0, $a0, 1
/* 0B5E78 800B5278 03E4082B */  sltu  $at, $ra, $a0
/* 0B5E7C 800B527C 25290001 */  addiu $t1, $t1, 1
/* 0B5E80 800B5280 26100001 */  addiu $s0, $s0, 1
/* 0B5E84 800B5284 1020FFFA */  beqz  $at, .L800B5270
/* 0B5E88 800B5288 A20EFFFF */   sb    $t6, -1($s0)
.L800B528C:
/* 0B5E8C 800B528C 12E00009 */  beqz  $s7, .L800B52B4
/* 0B5E90 800B5290 00000000 */   nop   
/* 0B5E94 800B5294 10600007 */  beqz  $v1, .L800B52B4
/* 0B5E98 800B5298 2508FFFF */   addiu $t0, $t0, -1
.L800B529C:
/* 0B5E9C 800B529C 0008182A */  slt   $v1, $zero, $t0
/* 0B5EA0 800B52A0 2508FFFF */  addiu $t0, $t0, -1
/* 0B5EA4 800B52A4 25290001 */  addiu $t1, $t1, 1
/* 0B5EA8 800B52A8 A20D0000 */  sb    $t5, ($s0)
/* 0B5EAC 800B52AC 1460FFFB */  bnez  $v1, .L800B529C
/* 0B5EB0 800B52B0 26100001 */   addiu $s0, $s0, 1
.L800B52B4:
/* 0B5EB4 800B52B4 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B5EB8 800B52B8 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B5EBC 800B52BC 100002D6 */  b     .L800B5E18
/* 0B5EC0 800B52C0 00000000 */   nop   
/* 0B5EC4 800B52C4 3C0F800E */  lui   $t7, %hi(D_800E2EF0) # $t7, 0x800e
/* 0B5EC8 800B52C8 8DEF2EF0 */  lw    $t7, %lo(D_800E2EF0)($t7)
/* 0B5ECC 800B52CC 00002825 */  move  $a1, $zero
/* 0B5ED0 800B52D0 11E00004 */  beqz  $t7, .L800B52E4
/* 0B5ED4 800B52D4 24190084 */   li    $t9, 132
/* 0B5ED8 800B52D8 25290001 */  addiu $t1, $t1, 1
/* 0B5EDC 800B52DC A2190000 */  sb    $t9, ($s0)
/* 0B5EE0 800B52E0 26100001 */  addiu $s0, $s0, 1
.L800B52E4:
/* 0B5EE4 800B52E4 05410002 */  bgez  $t2, .L800B52F0
/* 0B5EE8 800B52E8 322E0001 */   andi  $t6, $s1, 1
/* 0B5EEC 800B52EC 240A0006 */  li    $t2, 6
.L800B52F0:
/* 0B5EF0 800B52F0 10C0000A */  beqz  $a2, .L800B531C
/* 0B5EF4 800B52F4 2401FFFC */   li    $at, -4
/* 0B5EF8 800B52F8 26310003 */  addiu $s1, $s1, 3
/* 0B5EFC 800B52FC 0221C024 */  and   $t8, $s1, $at
/* 0B5F00 800B5300 27110004 */  addiu $s1, $t8, 4
/* 0B5F04 800B5304 C624FFFC */  lwc1  $f4, -4($s1)
/* 0B5F08 800B5308 00000000 */  nop   
/* 0B5F0C 800B530C 460021A1 */  cvt.d.s $f6, $f4
/* 0B5F10 800B5310 E7A600D4 */  swc1  $f6, 0xd4($sp)
/* 0B5F14 800B5314 10000014 */  b     .L800B5368
/* 0B5F18 800B5318 E7A700D0 */   swc1  $f7, 0xd0($sp)
.L800B531C:
/* 0B5F1C 800B531C 11C00004 */  beqz  $t6, .L800B5330
/* 0B5F20 800B5320 322F0002 */   andi  $t7, $s1, 2
/* 0B5F24 800B5324 26310007 */  addiu $s1, $s1, 7
/* 0B5F28 800B5328 1000000B */  b     .L800B5358
/* 0B5F2C 800B532C 2623FFEA */   addiu $v1, $s1, -0x16
.L800B5330:
/* 0B5F30 800B5330 11E00004 */  beqz  $t7, .L800B5344
/* 0B5F34 800B5334 2401FFF8 */   li    $at, -8
/* 0B5F38 800B5338 2631000A */  addiu $s1, $s1, 0xa
/* 0B5F3C 800B533C 10000005 */  b     .L800B5354
/* 0B5F40 800B5340 2624FFD8 */   addiu $a0, $s1, -0x28
.L800B5344:
/* 0B5F44 800B5344 26310007 */  addiu $s1, $s1, 7
/* 0B5F48 800B5348 0221C824 */  and   $t9, $s1, $at
/* 0B5F4C 800B534C 27310008 */  addiu $s1, $t9, 8
/* 0B5F50 800B5350 02202025 */  move  $a0, $s1
.L800B5354:
/* 0B5F54 800B5354 00801825 */  move  $v1, $a0
.L800B5358:
/* 0B5F58 800B5358 C469FFF8 */  lwc1  $f9, -8($v1)
/* 0B5F5C 800B535C C468FFFC */  lwc1  $f8, -4($v1)
/* 0B5F60 800B5360 E7A900D0 */  swc1  $f9, 0xd0($sp)
/* 0B5F64 800B5364 E7A800D4 */  swc1  $f8, 0xd4($sp)
.L800B5368:
/* 0B5F68 800B5368 83B800D0 */  lb    $t8, 0xd0($sp)
/* 0B5F6C 800B536C 44804800 */  mtc1  $zero, $f9
/* 0B5F70 800B5370 07010007 */  bgez  $t8, .L800B5390
/* 0B5F74 800B5374 3C013FE0 */   li    $at, 0x3FE00000 # 1.750000
/* 0B5F78 800B5378 C7AB00D0 */  lwc1  $f11, 0xd0($sp)
/* 0B5F7C 800B537C C7AA00D4 */  lwc1  $f10, 0xd4($sp)
/* 0B5F80 800B5380 24050001 */  li    $a1, 1
/* 0B5F84 800B5384 46205107 */  neg.d $f4, $f10
/* 0B5F88 800B5388 E7A400D4 */  swc1  $f4, 0xd4($sp)
/* 0B5F8C 800B538C E7A500D0 */  swc1  $f5, 0xd0($sp)
.L800B5390:
/* 0B5F90 800B5390 C7A700D0 */  lwc1  $f7, 0xd0($sp)
/* 0B5F94 800B5394 C7A600D4 */  lwc1  $f6, 0xd4($sp)
/* 0B5F98 800B5398 44804000 */  mtc1  $zero, $f8
/* 0B5F9C 800B539C C7AB00D0 */  lwc1  $f11, 0xd0($sp)
/* 0B5FA0 800B53A0 46283032 */  c.eq.d $f6, $f8
/* 0B5FA4 800B53A4 C7A600D4 */  lwc1  $f6, 0xd4($sp)
/* 0B5FA8 800B53A8 C7A700D0 */  lwc1  $f7, 0xd0($sp)
/* 0B5FAC 800B53AC 45000004 */  bc1f  .L800B53C0
/* 0B5FB0 800B53B0 31440003 */   andi  $a0, $t2, 3
/* 0B5FB4 800B53B4 0000A025 */  move  $s4, $zero
/* 0B5FB8 800B53B8 10000014 */  b     .L800B540C
/* 0B5FBC 800B53BC 4620A406 */   mov.d $f16, $f20
.L800B53C0:
/* 0B5FC0 800B53C0 C7AA00D4 */  lwc1  $f10, 0xd4($sp)
/* 0B5FC4 800B53C4 00000000 */  nop   
/* 0B5FC8 800B53C8 4634503C */  c.lt.d $f10, $f20
/* 0B5FCC 800B53CC 00000000 */  nop   
/* 0B5FD0 800B53D0 4500000E */  bc1f  .L800B540C
/* 0B5FD4 800B53D4 00000000 */   nop   
/* 0B5FD8 800B53D8 4634503C */  c.lt.d $f10, $f20
/* 0B5FDC 800B53DC 0000A025 */  move  $s4, $zero
/* 0B5FE0 800B53E0 4500000A */  bc1f  .L800B540C
/* 0B5FE4 800B53E4 4620A406 */   mov.d $f16, $f20
/* 0B5FE8 800B53E8 00000000 */  nop   
.L800B53EC:
/* 0B5FEC 800B53EC 46328403 */  div.d $f16, $f16, $f18
/* 0B5FF0 800B53F0 C7A500D0 */  lwc1  $f5, 0xd0($sp)
/* 0B5FF4 800B53F4 C7A400D4 */  lwc1  $f4, 0xd4($sp)
/* 0B5FF8 800B53F8 2694FFFF */  addiu $s4, $s4, -1
/* 0B5FFC 800B53FC 4630203C */  c.lt.d $f4, $f16
/* 0B6000 800B5400 00000000 */  nop   
/* 0B6004 800B5404 4501FFF9 */  bc1t  .L800B53EC
/* 0B6008 800B5408 00000000 */   nop   
.L800B540C:
/* 0B600C 800B540C 4626A03E */  c.le.d $f20, $f6
/* 0B6010 800B5410 44815800 */  mtc1  $at, $f11
/* 0B6014 800B5414 4500000F */  bc1f  .L800B5454
/* 0B6018 800B5418 00042023 */   negu  $a0, $a0
/* 0B601C 800B541C 4626903E */  c.le.d $f18, $f6
/* 0B6020 800B5420 0000A025 */  move  $s4, $zero
/* 0B6024 800B5424 4620A406 */  mov.d $f16, $f20
/* 0B6028 800B5428 4500000A */  bc1f  .L800B5454
/* 0B602C 800B542C 46209006 */   mov.d $f0, $f18
.L800B5430:
/* 0B6030 800B5430 46200406 */  mov.d $f16, $f0
/* 0B6034 800B5434 46320002 */  mul.d $f0, $f0, $f18
/* 0B6038 800B5438 C7A900D0 */  lwc1  $f9, 0xd0($sp)
/* 0B603C 800B543C C7A800D4 */  lwc1  $f8, 0xd4($sp)
/* 0B6040 800B5440 26940001 */  addiu $s4, $s4, 1
/* 0B6044 800B5444 4628003E */  c.le.d $f0, $f8
/* 0B6048 800B5448 00000000 */  nop   
/* 0B604C 800B544C 4501FFF8 */  bc1t  .L800B5430
/* 0B6050 800B5450 00000000 */   nop   
.L800B5454:
/* 0B6054 800B5454 44805000 */  mtc1  $zero, $f10
/* 0B6058 800B5458 000A982A */  slt   $s3, $zero, $t2
/* 0B605C 800B545C 462A8002 */  mul.d $f0, $f16, $f10
/* 0B6060 800B5460 12600018 */  beqz  $s3, .L800B54C4
/* 0B6064 800B5464 01401025 */   move  $v0, $t2
/* 0B6068 800B5468 10800005 */  beqz  $a0, .L800B5480
/* 0B606C 800B546C 008A1821 */   addu  $v1, $a0, $t2
.L800B5470:
/* 0B6070 800B5470 2442FFFF */  addiu $v0, $v0, -1
/* 0B6074 800B5474 1462FFFE */  bne   $v1, $v0, .L800B5470
/* 0B6078 800B5478 46320003 */   div.d $f0, $f0, $f18
/* 0B607C 800B547C 10400011 */  beqz  $v0, .L800B54C4
.L800B5480:
/* 0B6080 800B5480 2442FFFC */   addiu $v0, $v0, -4
/* 0B6084 800B5484 10400009 */  beqz  $v0, .L800B54AC
/* 0B6088 800B5488 46320003 */   div.d $f0, $f0, $f18
.L800B548C:
/* 0B608C 800B548C 00000000 */  nop   
/* 0B6090 800B5490 46320003 */  div.d $f0, $f0, $f18
/* 0B6094 800B5494 2442FFFC */  addiu $v0, $v0, -4
/* 0B6098 800B5498 46320003 */  div.d $f0, $f0, $f18
/* 0B609C 800B549C 00000000 */  nop   
/* 0B60A0 800B54A0 46320003 */  div.d $f0, $f0, $f18
/* 0B60A4 800B54A4 1440FFF9 */  bnez  $v0, .L800B548C
/* 0B60A8 800B54A8 46320003 */   div.d $f0, $f0, $f18
.L800B54AC:
/* 0B60AC 800B54AC 00000000 */  nop   
/* 0B60B0 800B54B0 46320003 */  div.d $f0, $f0, $f18
/* 0B60B4 800B54B4 00000000 */  nop   
/* 0B60B8 800B54B8 46320003 */  div.d $f0, $f0, $f18
/* 0B60BC 800B54BC 00000000 */  nop   
/* 0B60C0 800B54C0 46320003 */  div.d $f0, $f0, $f18
.L800B54C4:
/* 0B60C4 800B54C4 46328082 */  mul.d $f2, $f16, $f18
/* 0B60C8 800B54C8 C7A500D0 */  lwc1  $f5, 0xd0($sp)
/* 0B60CC 800B54CC C7A400D4 */  lwc1  $f4, 0xd4($sp)
/* 0B60D0 800B54D0 0005102B */  sltu  $v0, $zero, $a1
/* 0B60D4 800B54D4 00402025 */  move  $a0, $v0
/* 0B60D8 800B54D8 46202180 */  add.d $f6, $f4, $f0
/* 0B60DC 800B54DC 24010020 */  li    $at, 32
/* 0B60E0 800B54E0 4626103E */  c.le.d $f2, $f6
/* 0B60E4 800B54E4 E7A600D4 */  swc1  $f6, 0xd4($sp)
/* 0B60E8 800B54E8 45000003 */  bc1f  .L800B54F8
/* 0B60EC 800B54EC E7A700D0 */   swc1  $f7, 0xd0($sp)
/* 0B60F0 800B54F0 46201406 */  mov.d $f16, $f2
/* 0B60F4 800B54F4 26940001 */  addiu $s4, $s4, 1
.L800B54F8:
/* 0B60F8 800B54F8 2A860064 */  slti  $a2, $s4, 0x64
/* 0B60FC 800B54FC 14400005 */  bnez  $v0, .L800B5514
/* 0B6100 800B5500 38C60001 */   xori  $a2, $a2, 1
/* 0B6104 800B5504 0015202B */  sltu  $a0, $zero, $s5
/* 0B6108 800B5508 14800002 */  bnez  $a0, .L800B5514
/* 0B610C 800B550C 00000000 */   nop   
/* 0B6110 800B5510 0016202B */  sltu  $a0, $zero, $s6
.L800B5514:
/* 0B6114 800B5514 16600002 */  bnez  $s3, .L800B5520
/* 0B6118 800B5518 02601825 */   move  $v1, $s3
/* 0B611C 800B551C 001E182B */  sltu  $v1, $zero, $fp
.L800B5520:
/* 0B6120 800B5520 00647021 */  addu  $t6, $v1, $a0
/* 0B6124 800B5524 01CA7821 */  addu  $t7, $t6, $t2
/* 0B6128 800B5528 01E62821 */  addu  $a1, $t7, $a2
/* 0B612C 800B552C 16E0000B */  bnez  $s7, .L800B555C
/* 0B6130 800B5530 24A50005 */   addiu $a1, $a1, 5
/* 0B6134 800B5534 15810009 */  bne   $t4, $at, .L800B555C
/* 0B6138 800B5538 00A8182A */   slt   $v1, $a1, $t0
/* 0B613C 800B553C 10600007 */  beqz  $v1, .L800B555C
/* 0B6140 800B5540 2508FFFF */   addiu $t0, $t0, -1
.L800B5544:
/* 0B6144 800B5544 00A8182A */  slt   $v1, $a1, $t0
/* 0B6148 800B5548 2508FFFF */  addiu $t0, $t0, -1
/* 0B614C 800B554C 25290001 */  addiu $t1, $t1, 1
/* 0B6150 800B5550 A20C0000 */  sb    $t4, ($s0)
/* 0B6154 800B5554 1460FFFB */  bnez  $v1, .L800B5544
/* 0B6158 800B5558 26100001 */   addiu $s0, $s0, 1
.L800B555C:
/* 0B615C 800B555C 10400005 */  beqz  $v0, .L800B5574
/* 0B6160 800B5560 2419002D */   li    $t9, 45
/* 0B6164 800B5564 25290001 */  addiu $t1, $t1, 1
/* 0B6168 800B5568 A2190000 */  sb    $t9, ($s0)
/* 0B616C 800B556C 1000000C */  b     .L800B55A0
/* 0B6170 800B5570 26100001 */   addiu $s0, $s0, 1
.L800B5574:
/* 0B6174 800B5574 12A00005 */  beqz  $s5, .L800B558C
/* 0B6178 800B5578 2418002B */   li    $t8, 43
/* 0B617C 800B557C 25290001 */  addiu $t1, $t1, 1
/* 0B6180 800B5580 A2180000 */  sb    $t8, ($s0)
/* 0B6184 800B5584 10000006 */  b     .L800B55A0
/* 0B6188 800B5588 26100001 */   addiu $s0, $s0, 1
.L800B558C:
/* 0B618C 800B558C 12C00004 */  beqz  $s6, .L800B55A0
/* 0B6190 800B5590 00000000 */   nop   
/* 0B6194 800B5594 25290001 */  addiu $t1, $t1, 1
/* 0B6198 800B5598 A20D0000 */  sb    $t5, ($s0)
/* 0B619C 800B559C 26100001 */  addiu $s0, $s0, 1
.L800B55A0:
/* 0B61A0 800B55A0 16E0000B */  bnez  $s7, .L800B55D0
/* 0B61A4 800B55A4 24010030 */   li    $at, 48
/* 0B61A8 800B55A8 15810009 */  bne   $t4, $at, .L800B55D0
/* 0B61AC 800B55AC 00A8182A */   slt   $v1, $a1, $t0
/* 0B61B0 800B55B0 10600007 */  beqz  $v1, .L800B55D0
/* 0B61B4 800B55B4 2508FFFF */   addiu $t0, $t0, -1
.L800B55B8:
/* 0B61B8 800B55B8 00A8182A */  slt   $v1, $a1, $t0
/* 0B61BC 800B55BC 2508FFFF */  addiu $t0, $t0, -1
/* 0B61C0 800B55C0 25290001 */  addiu $t1, $t1, 1
/* 0B61C4 800B55C4 A20C0000 */  sb    $t4, ($s0)
/* 0B61C8 800B55C8 1460FFFB */  bnez  $v1, .L800B55B8
/* 0B61CC 800B55CC 26100001 */   addiu $s0, $s0, 1
.L800B55D0:
/* 0B61D0 800B55D0 C7A900D0 */  lwc1  $f9, 0xd0($sp)
/* 0B61D4 800B55D4 C7A800D4 */  lwc1  $f8, 0xd4($sp)
/* 0B61D8 800B55D8 24020030 */  li    $v0, 48
/* 0B61DC 800B55DC 4628803E */  c.le.d $f16, $f8
/* 0B61E0 800B55E0 25290001 */  addiu $t1, $t1, 1
/* 0B61E4 800B55E4 45000009 */  bc1f  .L800B560C
/* 0B61E8 800B55E8 240E002E */   li    $t6, 46
.L800B55EC:
/* 0B61EC 800B55EC C7AB00D0 */  lwc1  $f11, 0xd0($sp)
/* 0B61F0 800B55F0 C7AA00D4 */  lwc1  $f10, 0xd4($sp)
/* 0B61F4 800B55F4 24420001 */  addiu $v0, $v0, 1
/* 0B61F8 800B55F8 46305101 */  sub.d $f4, $f10, $f16
/* 0B61FC 800B55FC 4624803E */  c.le.d $f16, $f4
/* 0B6200 800B5600 E7A400D4 */  swc1  $f4, 0xd4($sp)
/* 0B6204 800B5604 4501FFF9 */  bc1t  .L800B55EC
/* 0B6208 800B5608 E7A500D0 */   swc1  $f5, 0xd0($sp)
.L800B560C:
/* 0B620C 800B560C A2020000 */  sb    $v0, ($s0)
/* 0B6210 800B5610 26100001 */  addiu $s0, $s0, 1
/* 0B6214 800B5614 16600003 */  bnez  $s3, .L800B5624
/* 0B6218 800B5618 46328403 */   div.d $f16, $f16, $f18
/* 0B621C 800B561C 13C00004 */  beqz  $fp, .L800B5630
/* 0B6220 800B5620 00000000 */   nop   
.L800B5624:
/* 0B6224 800B5624 25290001 */  addiu $t1, $t1, 1
/* 0B6228 800B5628 A20E0000 */  sb    $t6, ($s0)
/* 0B622C 800B562C 26100001 */  addiu $s0, $s0, 1
.L800B5630:
/* 0B6230 800B5630 12600014 */  beqz  $s3, .L800B5684
/* 0B6234 800B5634 2401000A */   li    $at, 10
.L800B5638:
/* 0B6238 800B5638 C7A700D0 */  lwc1  $f7, 0xd0($sp)
/* 0B623C 800B563C C7A600D4 */  lwc1  $f6, 0xd4($sp)
/* 0B6240 800B5640 24020030 */  li    $v0, 48
/* 0B6244 800B5644 4626803E */  c.le.d $f16, $f6
/* 0B6248 800B5648 25290001 */  addiu $t1, $t1, 1
/* 0B624C 800B564C 45000009 */  bc1f  .L800B5674
/* 0B6250 800B5650 254AFFFF */   addiu $t2, $t2, -1
.L800B5654:
/* 0B6254 800B5654 C7A900D0 */  lwc1  $f9, 0xd0($sp)
/* 0B6258 800B5658 C7A800D4 */  lwc1  $f8, 0xd4($sp)
/* 0B625C 800B565C 24420001 */  addiu $v0, $v0, 1
/* 0B6260 800B5660 46304281 */  sub.d $f10, $f8, $f16
/* 0B6264 800B5664 462A803E */  c.le.d $f16, $f10
/* 0B6268 800B5668 E7AA00D4 */  swc1  $f10, 0xd4($sp)
/* 0B626C 800B566C 4501FFF9 */  bc1t  .L800B5654
/* 0B6270 800B5670 E7AB00D0 */   swc1  $f11, 0xd0($sp)
.L800B5674:
/* 0B6274 800B5674 A2020000 */  sb    $v0, ($s0)
/* 0B6278 800B5678 26100001 */  addiu $s0, $s0, 1
/* 0B627C 800B567C 1D40FFEE */  bgtz  $t2, .L800B5638
/* 0B6280 800B5680 46328403 */   div.d $f16, $f16, $f18
.L800B5684:
/* 0B6284 800B5684 93AF019A */  lbu   $t7, 0x19a($sp)
/* 0B6288 800B5688 25290001 */  addiu $t1, $t1, 1
/* 0B628C 800B568C 26100001 */  addiu $s0, $s0, 1
/* 0B6290 800B5690 06810016 */  bgez  $s4, .L800B56EC
/* 0B6294 800B5694 A20FFFFF */   sb    $t7, -1($s0)
/* 0B6298 800B5698 0014A023 */  negu  $s4, $s4
/* 0B629C 800B569C 2401000A */  li    $at, 10
/* 0B62A0 800B56A0 0281001A */  div   $zero, $s4, $at
/* 0B62A4 800B56A4 2A860064 */  slti  $a2, $s4, 0x64
/* 0B62A8 800B56A8 2419002D */  li    $t9, 45
/* 0B62AC 800B56AC A2190000 */  sb    $t9, ($s0)
/* 0B62B0 800B56B0 38C60001 */  xori  $a2, $a2, 1
/* 0B62B4 800B56B4 25290001 */  addiu $t1, $t1, 1
/* 0B62B8 800B56B8 26100001 */  addiu $s0, $s0, 1
/* 0B62BC 800B56BC 00001812 */  mflo  $v1
/* 0B62C0 800B56C0 00000000 */  nop   
/* 0B62C4 800B56C4 00000000 */  nop   
/* 0B62C8 800B56C8 0061001A */  div   $zero, $v1, $at
/* 0B62CC 800B56CC 0000C010 */  mfhi  $t8
/* 0B62D0 800B56D0 27030030 */  addiu $v1, $t8, 0x30
/* 0B62D4 800B56D4 00000000 */  nop   
/* 0B62D8 800B56D8 0281001A */  div   $zero, $s4, $at
/* 0B62DC 800B56DC 00002010 */  mfhi  $a0
/* 0B62E0 800B56E0 24840030 */  addiu $a0, $a0, 0x30
/* 0B62E4 800B56E4 10000011 */  b     .L800B572C
/* 0B62E8 800B56E8 00000000 */   nop   
.L800B56EC:
/* 0B62EC 800B56EC 0281001A */  div   $zero, $s4, $at
/* 0B62F0 800B56F0 240F002B */  li    $t7, 43
/* 0B62F4 800B56F4 A20F0000 */  sb    $t7, ($s0)
/* 0B62F8 800B56F8 25290001 */  addiu $t1, $t1, 1
/* 0B62FC 800B56FC 26100001 */  addiu $s0, $s0, 1
/* 0B6300 800B5700 00001812 */  mflo  $v1
/* 0B6304 800B5704 00000000 */  nop   
/* 0B6308 800B5708 00000000 */  nop   
/* 0B630C 800B570C 0061001A */  div   $zero, $v1, $at
/* 0B6310 800B5710 00007010 */  mfhi  $t6
/* 0B6314 800B5714 25C30030 */  addiu $v1, $t6, 0x30
/* 0B6318 800B5718 00000000 */  nop   
/* 0B631C 800B571C 0281001A */  div   $zero, $s4, $at
/* 0B6320 800B5720 00002010 */  mfhi  $a0
/* 0B6324 800B5724 24840030 */  addiu $a0, $a0, 0x30
/* 0B6328 800B5728 00000000 */  nop   
.L800B572C:
/* 0B632C 800B572C 10C00007 */  beqz  $a2, .L800B574C
/* 0B6330 800B5730 24010064 */   li    $at, 100
/* 0B6334 800B5734 0281001A */  div   $zero, $s4, $at
/* 0B6338 800B5738 25290001 */  addiu $t1, $t1, 1
/* 0B633C 800B573C 26100001 */  addiu $s0, $s0, 1
/* 0B6340 800B5740 00001012 */  mflo  $v0
/* 0B6344 800B5744 24420030 */  addiu $v0, $v0, 0x30
/* 0B6348 800B5748 A202FFFF */  sb    $v0, -1($s0)
.L800B574C:
/* 0B634C 800B574C A2030000 */  sb    $v1, ($s0)
/* 0B6350 800B5750 25290002 */  addiu $t1, $t1, 2
/* 0B6354 800B5754 A2040001 */  sb    $a0, 1($s0)
/* 0B6358 800B5758 12E0000A */  beqz  $s7, .L800B5784
/* 0B635C 800B575C 26100002 */   addiu $s0, $s0, 2
/* 0B6360 800B5760 00A8182A */  slt   $v1, $a1, $t0
/* 0B6364 800B5764 10600007 */  beqz  $v1, .L800B5784
/* 0B6368 800B5768 2508FFFF */   addiu $t0, $t0, -1
.L800B576C:
/* 0B636C 800B576C 00A8182A */  slt   $v1, $a1, $t0
/* 0B6370 800B5770 2508FFFF */  addiu $t0, $t0, -1
/* 0B6374 800B5774 25290001 */  addiu $t1, $t1, 1
/* 0B6378 800B5778 A20D0000 */  sb    $t5, ($s0)
/* 0B637C 800B577C 1460FFFB */  bnez  $v1, .L800B576C
/* 0B6380 800B5780 26100001 */   addiu $s0, $s0, 1
.L800B5784:
/* 0B6384 800B5784 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B6388 800B5788 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B638C 800B578C 100001A2 */  b     .L800B5E18
/* 0B6390 800B5790 00000000 */   nop   
/* 0B6394 800B5794 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B6398 800B5798 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B639C 800B579C 1000019E */  b     .L800B5E18
/* 0B63A0 800B57A0 00000000 */   nop   
/* 0B63A4 800B57A4 3C19800E */  lui   $t9, %hi(D_800E2EF0) # $t9, 0x800e
/* 0B63A8 800B57A8 8F392EF0 */  lw    $t9, %lo(D_800E2EF0)($t9)
/* 0B63AC 800B57AC 4620A306 */  mov.d $f12, $f20
/* 0B63B0 800B57B0 00002825 */  move  $a1, $zero
/* 0B63B4 800B57B4 13200005 */  beqz  $t9, .L800B57CC
/* 0B63B8 800B57B8 46209386 */   mov.d $f14, $f18
/* 0B63BC 800B57BC 24180084 */  li    $t8, 132
/* 0B63C0 800B57C0 A2180000 */  sb    $t8, ($s0)
/* 0B63C4 800B57C4 25290001 */  addiu $t1, $t1, 1
/* 0B63C8 800B57C8 26100001 */  addiu $s0, $s0, 1
.L800B57CC:
/* 0B63CC 800B57CC 05410003 */  bgez  $t2, .L800B57DC
/* 0B63D0 800B57D0 000A982A */   slt   $s3, $zero, $t2
/* 0B63D4 800B57D4 240A0006 */  li    $t2, 6
/* 0B63D8 800B57D8 000A982A */  slt   $s3, $zero, $t2
.L800B57DC:
/* 0B63DC 800B57DC 12600019 */  beqz  $s3, .L800B5844
/* 0B63E0 800B57E0 00001025 */   move  $v0, $zero
/* 0B63E4 800B57E4 31440003 */  andi  $a0, $t2, 3
/* 0B63E8 800B57E8 10800005 */  beqz  $a0, .L800B5800
/* 0B63EC 800B57EC 00801825 */   move  $v1, $a0
.L800B57F0:
/* 0B63F0 800B57F0 24420001 */  addiu $v0, $v0, 1
/* 0B63F4 800B57F4 1462FFFE */  bne   $v1, $v0, .L800B57F0
/* 0B63F8 800B57F8 46326303 */   div.d $f12, $f12, $f18
/* 0B63FC 800B57FC 104A0011 */  beq   $v0, $t2, .L800B5844
.L800B5800:
/* 0B6400 800B5800 24420004 */   addiu $v0, $v0, 4
/* 0B6404 800B5804 104A0009 */  beq   $v0, $t2, .L800B582C
/* 0B6408 800B5808 46326303 */   div.d $f12, $f12, $f18
.L800B580C:
/* 0B640C 800B580C 00000000 */  nop   
/* 0B6410 800B5810 46326303 */  div.d $f12, $f12, $f18
/* 0B6414 800B5814 24420004 */  addiu $v0, $v0, 4
/* 0B6418 800B5818 46326303 */  div.d $f12, $f12, $f18
/* 0B641C 800B581C 00000000 */  nop   
/* 0B6420 800B5820 46326303 */  div.d $f12, $f12, $f18
/* 0B6424 800B5824 144AFFF9 */  bne   $v0, $t2, .L800B580C
/* 0B6428 800B5828 46326303 */   div.d $f12, $f12, $f18
.L800B582C:
/* 0B642C 800B582C 00000000 */  nop   
/* 0B6430 800B5830 46326303 */  div.d $f12, $f12, $f18
/* 0B6434 800B5834 00000000 */  nop   
/* 0B6438 800B5838 46326303 */  div.d $f12, $f12, $f18
/* 0B643C 800B583C 00000000 */  nop   
/* 0B6440 800B5840 46326303 */  div.d $f12, $f12, $f18
.L800B5844:
/* 0B6444 800B5844 10C00008 */  beqz  $a2, .L800B5868
/* 0B6448 800B5848 322F0001 */   andi  $t7, $s1, 1
/* 0B644C 800B584C 26310003 */  addiu $s1, $s1, 3
/* 0B6450 800B5850 2401FFFC */  li    $at, -4
/* 0B6454 800B5854 02217024 */  and   $t6, $s1, $at
/* 0B6458 800B5858 25D10004 */  addiu $s1, $t6, 4
/* 0B645C 800B585C C624FFFC */  lwc1  $f4, -4($s1)
/* 0B6460 800B5860 10000013 */  b     .L800B58B0
/* 0B6464 800B5864 46002021 */   cvt.d.s $f0, $f4
.L800B5868:
/* 0B6468 800B5868 11E00004 */  beqz  $t7, .L800B587C
/* 0B646C 800B586C 32390002 */   andi  $t9, $s1, 2
/* 0B6470 800B5870 26310007 */  addiu $s1, $s1, 7
/* 0B6474 800B5874 1000000B */  b     .L800B58A4
/* 0B6478 800B5878 2623FFEA */   addiu $v1, $s1, -0x16
.L800B587C:
/* 0B647C 800B587C 13200004 */  beqz  $t9, .L800B5890
/* 0B6480 800B5880 2401FFF8 */   li    $at, -8
/* 0B6484 800B5884 2631000A */  addiu $s1, $s1, 0xa
/* 0B6488 800B5888 10000005 */  b     .L800B58A0
/* 0B648C 800B588C 2624FFD8 */   addiu $a0, $s1, -0x28
.L800B5890:
/* 0B6490 800B5890 26310007 */  addiu $s1, $s1, 7
/* 0B6494 800B5894 0221C024 */  and   $t8, $s1, $at
/* 0B6498 800B5898 27110008 */  addiu $s1, $t8, 8
/* 0B649C 800B589C 02202025 */  move  $a0, $s1
.L800B58A0:
/* 0B64A0 800B58A0 00801825 */  move  $v1, $a0
.L800B58A4:
/* 0B64A4 800B58A4 C461FFF8 */  lwc1  $f1, -8($v1)
/* 0B64A8 800B58A8 C460FFFC */  lwc1  $f0, -4($v1)
/* 0B64AC 800B58AC 00000000 */  nop   
.L800B58B0:
/* 0B64B0 800B58B0 44803800 */  mtc1  $zero, $f7
/* 0B64B4 800B58B4 44803000 */  mtc1  $zero, $f6
/* 0B64B8 800B58B8 3C013FE0 */  li    $at, 0x3FE00000 # 1.750000
/* 0B64BC 800B58BC 44814800 */  mtc1  $at, $f9
/* 0B64C0 800B58C0 44804000 */  mtc1  $zero, $f8
/* 0B64C4 800B58C4 4626003C */  c.lt.d $f0, $f6
/* 0B64C8 800B58C8 46286282 */  mul.d $f10, $f12, $f8
/* 0B64CC 800B58CC 45000003 */  bc1f  .L800B58DC
/* 0B64D0 800B58D0 24010020 */   li    $at, 32
/* 0B64D4 800B58D4 24050001 */  li    $a1, 1
/* 0B64D8 800B58D8 46200007 */  neg.d $f0, $f0
.L800B58DC:
/* 0B64DC 800B58DC 462A0000 */  add.d $f0, $f0, $f10
/* 0B64E0 800B58E0 24020001 */  li    $v0, 1
/* 0B64E4 800B58E4 4620903E */  c.le.d $f18, $f0
/* 0B64E8 800B58E8 4620A086 */  mov.d $f2, $f20
/* 0B64EC 800B58EC 45000008 */  bc1f  .L800B5910
/* 0B64F0 800B58F0 0005302B */   sltu  $a2, $zero, $a1
.L800B58F4:
/* 0B64F4 800B58F4 46207086 */  mov.d $f2, $f14
/* 0B64F8 800B58F8 46327382 */  mul.d $f14, $f14, $f18
/* 0B64FC 800B58FC 24420001 */  addiu $v0, $v0, 1
/* 0B6500 800B5900 4620703E */  c.le.d $f14, $f0
/* 0B6504 800B5904 00000000 */  nop   
/* 0B6508 800B5908 4501FFFA */  bc1t  .L800B58F4
/* 0B650C 800B590C 00000000 */   nop   
.L800B5910:
/* 0B6510 800B5910 14C00005 */  bnez  $a2, .L800B5928
/* 0B6514 800B5914 00C02025 */   move  $a0, $a2
/* 0B6518 800B5918 0015202B */  sltu  $a0, $zero, $s5
/* 0B651C 800B591C 14800002 */  bnez  $a0, .L800B5928
/* 0B6520 800B5920 00000000 */   nop   
/* 0B6524 800B5924 0016202B */  sltu  $a0, $zero, $s6
.L800B5928:
/* 0B6528 800B5928 16600002 */  bnez  $s3, .L800B5934
/* 0B652C 800B592C 02601825 */   move  $v1, $s3
/* 0B6530 800B5930 001E182B */  sltu  $v1, $zero, $fp
.L800B5934:
/* 0B6534 800B5934 00647021 */  addu  $t6, $v1, $a0
/* 0B6538 800B5938 01C27821 */  addu  $t7, $t6, $v0
/* 0B653C 800B593C 16E0000B */  bnez  $s7, .L800B596C
/* 0B6540 800B5940 01EA2821 */   addu  $a1, $t7, $t2
/* 0B6544 800B5944 15810009 */  bne   $t4, $at, .L800B596C
/* 0B6548 800B5948 00A8182A */   slt   $v1, $a1, $t0
/* 0B654C 800B594C 10600007 */  beqz  $v1, .L800B596C
/* 0B6550 800B5950 2508FFFF */   addiu $t0, $t0, -1
.L800B5954:
/* 0B6554 800B5954 00A8182A */  slt   $v1, $a1, $t0
/* 0B6558 800B5958 2508FFFF */  addiu $t0, $t0, -1
/* 0B655C 800B595C 25290001 */  addiu $t1, $t1, 1
/* 0B6560 800B5960 A20C0000 */  sb    $t4, ($s0)
/* 0B6564 800B5964 1460FFFB */  bnez  $v1, .L800B5954
/* 0B6568 800B5968 26100001 */   addiu $s0, $s0, 1
.L800B596C:
/* 0B656C 800B596C 10C00005 */  beqz  $a2, .L800B5984
/* 0B6570 800B5970 2419002D */   li    $t9, 45
/* 0B6574 800B5974 25290001 */  addiu $t1, $t1, 1
/* 0B6578 800B5978 A2190000 */  sb    $t9, ($s0)
/* 0B657C 800B597C 1000000C */  b     .L800B59B0
/* 0B6580 800B5980 26100001 */   addiu $s0, $s0, 1
.L800B5984:
/* 0B6584 800B5984 12A00005 */  beqz  $s5, .L800B599C
/* 0B6588 800B5988 2418002B */   li    $t8, 43
/* 0B658C 800B598C 25290001 */  addiu $t1, $t1, 1
/* 0B6590 800B5990 A2180000 */  sb    $t8, ($s0)
/* 0B6594 800B5994 10000006 */  b     .L800B59B0
/* 0B6598 800B5998 26100001 */   addiu $s0, $s0, 1
.L800B599C:
/* 0B659C 800B599C 12C00004 */  beqz  $s6, .L800B59B0
/* 0B65A0 800B59A0 00000000 */   nop   
/* 0B65A4 800B59A4 25290001 */  addiu $t1, $t1, 1
/* 0B65A8 800B59A8 A20D0000 */  sb    $t5, ($s0)
/* 0B65AC 800B59AC 26100001 */  addiu $s0, $s0, 1
.L800B59B0:
/* 0B65B0 800B59B0 16E0000B */  bnez  $s7, .L800B59E0
/* 0B65B4 800B59B4 24010030 */   li    $at, 48
/* 0B65B8 800B59B8 15810009 */  bne   $t4, $at, .L800B59E0
/* 0B65BC 800B59BC 00A8182A */   slt   $v1, $a1, $t0
/* 0B65C0 800B59C0 10600007 */  beqz  $v1, .L800B59E0
/* 0B65C4 800B59C4 2508FFFF */   addiu $t0, $t0, -1
.L800B59C8:
/* 0B65C8 800B59C8 00A8182A */  slt   $v1, $a1, $t0
/* 0B65CC 800B59CC 2508FFFF */  addiu $t0, $t0, -1
/* 0B65D0 800B59D0 25290001 */  addiu $t1, $t1, 1
/* 0B65D4 800B59D4 A20C0000 */  sb    $t4, ($s0)
/* 0B65D8 800B59D8 1460FFFB */  bnez  $v1, .L800B59C8
/* 0B65DC 800B59DC 26100001 */   addiu $s0, $s0, 1
.L800B59E0:
/* 0B65E0 800B59E0 4620103E */  c.le.d $f2, $f0
/* 0B65E4 800B59E4 24020030 */  li    $v0, 48
/* 0B65E8 800B59E8 45000008 */  bc1f  .L800B5A0C
/* 0B65EC 800B59EC 00000000 */   nop   
.L800B59F0:
/* 0B65F0 800B59F0 46220001 */  sub.d $f0, $f0, $f2
/* 0B65F4 800B59F4 24420001 */  addiu $v0, $v0, 1
/* 0B65F8 800B59F8 4620103E */  c.le.d $f2, $f0
/* 0B65FC 800B59FC 00000000 */  nop   
/* 0B6600 800B5A00 4501FFFB */  bc1t  .L800B59F0
/* 0B6604 800B5A04 00000000 */   nop   
/* 0B6608 800B5A08 00000000 */  nop   
.L800B5A0C:
/* 0B660C 800B5A0C 46321083 */  div.d $f2, $f2, $f18
/* 0B6610 800B5A10 25290001 */  addiu $t1, $t1, 1
/* 0B6614 800B5A14 A2020000 */  sb    $v0, ($s0)
/* 0B6618 800B5A18 26100001 */  addiu $s0, $s0, 1
/* 0B661C 800B5A1C 4622A03E */  c.le.d $f20, $f2
/* 0B6620 800B5A20 00000000 */  nop   
/* 0B6624 800B5A24 4501FFEE */  bc1t  .L800B59E0
/* 0B6628 800B5A28 00000000 */   nop   
/* 0B662C 800B5A2C 16600003 */  bnez  $s3, .L800B5A3C
/* 0B6630 800B5A30 240E002E */   li    $t6, 46
/* 0B6634 800B5A34 13C00004 */  beqz  $fp, .L800B5A48
/* 0B6638 800B5A38 00000000 */   nop   
.L800B5A3C:
/* 0B663C 800B5A3C 25290001 */  addiu $t1, $t1, 1
/* 0B6640 800B5A40 A20E0000 */  sb    $t6, ($s0)
/* 0B6644 800B5A44 26100001 */  addiu $s0, $s0, 1
.L800B5A48:
/* 0B6648 800B5A48 12600010 */  beqz  $s3, .L800B5A8C
/* 0B664C 800B5A4C 00A8182A */   slt   $v1, $a1, $t0
.L800B5A50:
/* 0B6650 800B5A50 4620103E */  c.le.d $f2, $f0
/* 0B6654 800B5A54 24020030 */  li    $v0, 48
/* 0B6658 800B5A58 45000007 */  bc1f  .L800B5A78
/* 0B665C 800B5A5C 25290001 */   addiu $t1, $t1, 1
.L800B5A60:
/* 0B6660 800B5A60 46220001 */  sub.d $f0, $f0, $f2
/* 0B6664 800B5A64 24420001 */  addiu $v0, $v0, 1
/* 0B6668 800B5A68 4620103E */  c.le.d $f2, $f0
/* 0B666C 800B5A6C 00000000 */  nop   
/* 0B6670 800B5A70 4501FFFB */  bc1t  .L800B5A60
/* 0B6674 800B5A74 00000000 */   nop   
.L800B5A78:
/* 0B6678 800B5A78 254AFFFF */  addiu $t2, $t2, -1
/* 0B667C 800B5A7C A2020000 */  sb    $v0, ($s0)
/* 0B6680 800B5A80 26100001 */  addiu $s0, $s0, 1
/* 0B6684 800B5A84 1D40FFF2 */  bgtz  $t2, .L800B5A50
/* 0B6688 800B5A88 46321083 */   div.d $f2, $f2, $f18
.L800B5A8C:
/* 0B668C 800B5A8C 12E00009 */  beqz  $s7, .L800B5AB4
/* 0B6690 800B5A90 00000000 */   nop   
/* 0B6694 800B5A94 10600007 */  beqz  $v1, .L800B5AB4
/* 0B6698 800B5A98 2508FFFF */   addiu $t0, $t0, -1
.L800B5A9C:
/* 0B669C 800B5A9C 00A8182A */  slt   $v1, $a1, $t0
/* 0B66A0 800B5AA0 2508FFFF */  addiu $t0, $t0, -1
/* 0B66A4 800B5AA4 25290001 */  addiu $t1, $t1, 1
/* 0B66A8 800B5AA8 A20D0000 */  sb    $t5, ($s0)
/* 0B66AC 800B5AAC 1460FFFB */  bnez  $v1, .L800B5A9C
/* 0B66B0 800B5AB0 26100001 */   addiu $s0, $s0, 1
.L800B5AB4:
/* 0B66B4 800B5AB4 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B66B8 800B5AB8 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B66BC 800B5ABC 100000D6 */  b     .L800B5E18
/* 0B66C0 800B5AC0 00000000 */   nop   
/* 0B66C4 800B5AC4 26310003 */  addiu $s1, $s1, 3
/* 0B66C8 800B5AC8 2401FFFC */  li    $at, -4
/* 0B66CC 800B5ACC 02217824 */  and   $t7, $s1, $at
/* 0B66D0 800B5AD0 25F10004 */  addiu $s1, $t7, 4
/* 0B66D4 800B5AD4 8E39FFFC */  lw    $t9, -4($s1)
/* 0B66D8 800B5AD8 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B66DC 800B5ADC 0019C7C3 */  sra   $t8, $t9, 0x1f
/* 0B66E0 800B5AE0 AFB80188 */  sw    $t8, 0x188($sp)
/* 0B66E4 800B5AE4 16E00009 */  bnez  $s7, .L800B5B0C
/* 0B66E8 800B5AE8 AFB9018C */   sw    $t9, 0x18c($sp)
/* 0B66EC 800B5AEC 2508FFFF */  addiu $t0, $t0, -1
/* 0B66F0 800B5AF0 19000007 */  blez  $t0, .L800B5B10
/* 0B66F4 800B5AF4 8FAF018C */   lw    $t7, 0x18c($sp)
.L800B5AF8:
/* 0B66F8 800B5AF8 2508FFFF */  addiu $t0, $t0, -1
/* 0B66FC 800B5AFC 25290001 */  addiu $t1, $t1, 1
/* 0B6700 800B5B00 A20C0000 */  sb    $t4, ($s0)
/* 0B6704 800B5B04 1D00FFFC */  bgtz  $t0, .L800B5AF8
/* 0B6708 800B5B08 26100001 */   addiu $s0, $s0, 1
.L800B5B0C:
/* 0B670C 800B5B0C 8FAF018C */  lw    $t7, 0x18c($sp)
.L800B5B10:
/* 0B6710 800B5B10 25290001 */  addiu $t1, $t1, 1
/* 0B6714 800B5B14 26100001 */  addiu $s0, $s0, 1
/* 0B6718 800B5B18 12E00008 */  beqz  $s7, .L800B5B3C
/* 0B671C 800B5B1C A20FFFFF */   sb    $t7, -1($s0)
/* 0B6720 800B5B20 2508FFFF */  addiu $t0, $t0, -1
/* 0B6724 800B5B24 19000005 */  blez  $t0, .L800B5B3C
.L800B5B28:
/* 0B6728 800B5B28 2508FFFF */   addiu $t0, $t0, -1
/* 0B672C 800B5B2C 25290001 */  addiu $t1, $t1, 1
/* 0B6730 800B5B30 A20D0000 */  sb    $t5, ($s0)
/* 0B6734 800B5B34 1D00FFFC */  bgtz  $t0, .L800B5B28
/* 0B6738 800B5B38 26100001 */   addiu $s0, $s0, 1
.L800B5B3C:
/* 0B673C 800B5B3C 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B6740 800B5B40 100000B5 */  b     .L800B5E18
/* 0B6744 800B5B44 00000000 */   nop   
/* 0B6748 800B5B48 26310003 */  addiu $s1, $s1, 3
/* 0B674C 800B5B4C 2401FFFC */  li    $at, -4
/* 0B6750 800B5B50 0221C824 */  and   $t9, $s1, $at
/* 0B6754 800B5B54 27310004 */  addiu $s1, $t9, 4
/* 0B6758 800B5B58 8E25FFFC */  lw    $a1, -4($s1)
/* 0B675C 800B5B5C 2401FFFF */  li    $at, -1
/* 0B6760 800B5B60 14A0000C */  bnez  $a1, .L800B5B94
/* 0B6764 800B5B64 00A02025 */   move  $a0, $a1
/* 0B6768 800B5B68 11410004 */  beq   $t2, $at, .L800B5B7C
/* 0B676C 800B5B6C 3C05800F */   lui   $a1, %hi(D_800E8C54) # $a1, 0x800f
/* 0B6770 800B5B70 29410006 */  slti  $at, $t2, 6
/* 0B6774 800B5B74 14200004 */  bnez  $at, .L800B5B88
/* 0B6778 800B5B78 00002025 */   move  $a0, $zero
.L800B5B7C:
/* 0B677C 800B5B7C 24A58C54 */  addiu $a1, %lo(D_800E8C54) # addiu $a1, $a1, -0x73ac
/* 0B6780 800B5B80 10000018 */  b     .L800B5BE4
/* 0B6784 800B5B84 24040006 */   li    $a0, 6
.L800B5B88:
/* 0B6788 800B5B88 3C05800F */  lui   $a1, %hi(D_800E8C50) # $a1, 0x800f
/* 0B678C 800B5B8C 10000015 */  b     .L800B5BE4
/* 0B6790 800B5B90 24A58C50 */   addiu $a1, %lo(D_800E8C50) # addiu $a1, $a1, -0x73b0
.L800B5B94:
/* 0B6794 800B5B94 AFA5017C */  sw    $a1, 0x17c($sp)
/* 0B6798 800B5B98 AFA801A0 */  sw    $t0, 0x1a0($sp)
/* 0B679C 800B5B9C AFA901AC */  sw    $t1, 0x1ac($sp)
/* 0B67A0 800B5BA0 AFAA019C */  sw    $t2, 0x19c($sp)
/* 0B67A4 800B5BA4 AFAB01B4 */  sw    $t3, 0x1b4($sp)
/* 0B67A8 800B5BA8 E7B100E0 */  swc1  $f17, 0xe0($sp)
/* 0B67AC 800B5BAC 0C033867 */  jal   strlen
/* 0B67B0 800B5BB0 E7B000E4 */   swc1  $f16, 0xe4($sp)
/* 0B67B4 800B5BB4 3C014024 */  li    $at, 0x40240000 # 2.562500
/* 0B67B8 800B5BB8 44819800 */  mtc1  $at, $f19
/* 0B67BC 800B5BBC 8FA5017C */  lw    $a1, 0x17c($sp)
/* 0B67C0 800B5BC0 8FA801A0 */  lw    $t0, 0x1a0($sp)
/* 0B67C4 800B5BC4 8FA901AC */  lw    $t1, 0x1ac($sp)
/* 0B67C8 800B5BC8 8FAA019C */  lw    $t2, 0x19c($sp)
/* 0B67CC 800B5BCC 8FAB01B4 */  lw    $t3, 0x1b4($sp)
/* 0B67D0 800B5BD0 C7B100E0 */  lwc1  $f17, 0xe0($sp)
/* 0B67D4 800B5BD4 C7B000E4 */  lwc1  $f16, 0xe4($sp)
/* 0B67D8 800B5BD8 44809000 */  mtc1  $zero, $f18
/* 0B67DC 800B5BDC 240D0020 */  li    $t5, 32
/* 0B67E0 800B5BE0 00402025 */  move  $a0, $v0
.L800B5BE4:
/* 0B67E4 800B5BE4 2401FFFF */  li    $at, -1
/* 0B67E8 800B5BE8 11410004 */  beq   $t2, $at, .L800B5BFC
/* 0B67EC 800B5BEC 0144082A */   slt   $at, $t2, $a0
/* 0B67F0 800B5BF0 10200002 */  beqz  $at, .L800B5BFC
/* 0B67F4 800B5BF4 00000000 */   nop   
/* 0B67F8 800B5BF8 01402025 */  move  $a0, $t2
.L800B5BFC:
/* 0B67FC 800B5BFC 16E0000A */  bnez  $s7, .L800B5C28
/* 0B6800 800B5C00 01044023 */   subu  $t0, $t0, $a0
/* 0B6804 800B5C04 0008182A */  slt   $v1, $zero, $t0
/* 0B6808 800B5C08 10600007 */  beqz  $v1, .L800B5C28
/* 0B680C 800B5C0C 2508FFFF */   addiu $t0, $t0, -1
.L800B5C10:
/* 0B6810 800B5C10 0008182A */  slt   $v1, $zero, $t0
/* 0B6814 800B5C14 2508FFFF */  addiu $t0, $t0, -1
/* 0B6818 800B5C18 25290001 */  addiu $t1, $t1, 1
/* 0B681C 800B5C1C A20D0000 */  sb    $t5, ($s0)
/* 0B6820 800B5C20 1460FFFB */  bnez  $v1, .L800B5C10
/* 0B6824 800B5C24 26100001 */   addiu $s0, $s0, 1
.L800B5C28:
/* 0B6828 800B5C28 0004182A */  slt   $v1, $zero, $a0
/* 0B682C 800B5C2C 10600009 */  beqz  $v1, .L800B5C54
/* 0B6830 800B5C30 2484FFFF */   addiu $a0, $a0, -1
.L800B5C34:
/* 0B6834 800B5C34 90AE0000 */  lbu   $t6, ($a1)
/* 0B6838 800B5C38 0004182A */  slt   $v1, $zero, $a0
/* 0B683C 800B5C3C 2484FFFF */  addiu $a0, $a0, -1
/* 0B6840 800B5C40 25290001 */  addiu $t1, $t1, 1
/* 0B6844 800B5C44 26100001 */  addiu $s0, $s0, 1
/* 0B6848 800B5C48 24A50001 */  addiu $a1, $a1, 1
/* 0B684C 800B5C4C 1460FFF9 */  bnez  $v1, .L800B5C34
/* 0B6850 800B5C50 A20EFFFF */   sb    $t6, -1($s0)
.L800B5C54:
/* 0B6854 800B5C54 12E00009 */  beqz  $s7, .L800B5C7C
/* 0B6858 800B5C58 0008182A */   slt   $v1, $zero, $t0
/* 0B685C 800B5C5C 10600007 */  beqz  $v1, .L800B5C7C
/* 0B6860 800B5C60 2508FFFF */   addiu $t0, $t0, -1
.L800B5C64:
/* 0B6864 800B5C64 0008182A */  slt   $v1, $zero, $t0
/* 0B6868 800B5C68 2508FFFF */  addiu $t0, $t0, -1
/* 0B686C 800B5C6C 25290001 */  addiu $t1, $t1, 1
/* 0B6870 800B5C70 A20D0000 */  sb    $t5, ($s0)
/* 0B6874 800B5C74 1460FFFB */  bnez  $v1, .L800B5C64
/* 0B6878 800B5C78 26100001 */   addiu $s0, $s0, 1
.L800B5C7C:
/* 0B687C 800B5C7C 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B6880 800B5C80 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B6884 800B5C84 10000064 */  b     .L800B5E18
/* 0B6888 800B5C88 00000000 */   nop   
/* 0B688C 800B5C8C 26310003 */  addiu $s1, $s1, 3
/* 0B6890 800B5C90 2401FFFC */  li    $at, -4
/* 0B6894 800B5C94 02217824 */  and   $t7, $s1, $at
/* 0B6898 800B5C98 25F10004 */  addiu $s1, $t7, 4
/* 0B689C 800B5C9C 8E22FFFC */  lw    $v0, -4($s1)
/* 0B68A0 800B5CA0 3C04800F */  lui   $a0, %hi(D_800E8C5C) # $a0, 0x800f
/* 0B68A4 800B5CA4 1040000E */  beqz  $v0, .L800B5CE0
/* 0B68A8 800B5CA8 24848C5C */   addiu $a0, %lo(D_800E8C5C) # addiu $a0, $a0, -0x73a4
/* 0B68AC 800B5CAC 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B68B0 800B5CB0 24180078 */  li    $t8, 120
/* 0B68B4 800B5CB4 240E0000 */  li    $t6, 0
/* 0B68B8 800B5CB8 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B68BC 800B5CBC 24070010 */  li    $a3, 16
/* 0B68C0 800B5CC0 A3B8019A */  sb    $t8, 0x19a($sp)
/* 0B68C4 800B5CC4 241E0001 */  li    $fp, 1
/* 0B68C8 800B5CC8 AFAE0188 */  sw    $t6, 0x188($sp)
/* 0B68CC 800B5CCC AFA2018C */  sw    $v0, 0x18c($sp)
/* 0B68D0 800B5CD0 00009025 */  move  $s2, $zero
/* 0B68D4 800B5CD4 24130078 */  li    $s3, 120
/* 0B68D8 800B5CD8 1000FCDF */  b     .L800B5058
/* 0B68DC 800B5CDC 27BF017B */   addiu $ra, $sp, 0x17b
.L800B5CE0:
/* 0B68E0 800B5CE0 16E0000A */  bnez  $s7, .L800B5D0C
/* 0B68E4 800B5CE4 2508FFFB */   addiu $t0, $t0, -5
/* 0B68E8 800B5CE8 0008182A */  slt   $v1, $zero, $t0
/* 0B68EC 800B5CEC 10600007 */  beqz  $v1, .L800B5D0C
/* 0B68F0 800B5CF0 2508FFFF */   addiu $t0, $t0, -1
.L800B5CF4:
/* 0B68F4 800B5CF4 0008182A */  slt   $v1, $zero, $t0
/* 0B68F8 800B5CF8 2508FFFF */  addiu $t0, $t0, -1
/* 0B68FC 800B5CFC 25290001 */  addiu $t1, $t1, 1
/* 0B6900 800B5D00 A20D0000 */  sb    $t5, ($s0)
/* 0B6904 800B5D04 1460FFFB */  bnez  $v1, .L800B5CF4
/* 0B6908 800B5D08 26100001 */   addiu $s0, $s0, 1
.L800B5D0C:
/* 0B690C 800B5D0C 3C19800F */  lui   $t9, %hi(D_800E8C5C) # $t9, 0x800f
/* 0B6910 800B5D10 93398C5C */  lbu   $t9, %lo(D_800E8C5C)($t9)
/* 0B6914 800B5D14 3C18800F */  lui   $t8, %hi(D_800E8C5C) # $t8, 0x800f
/* 0B6918 800B5D18 13200009 */  beqz  $t9, .L800B5D40
/* 0B691C 800B5D1C 27188C5C */   addiu $t8, %lo(D_800E8C5C) # addiu $t8, $t8, -0x73a4
/* 0B6920 800B5D20 93020000 */  lbu   $v0, ($t8)
/* 0B6924 800B5D24 00000000 */  nop   
.L800B5D28:
/* 0B6928 800B5D28 A2020000 */  sb    $v0, ($s0)
/* 0B692C 800B5D2C 90820001 */  lbu   $v0, 1($a0)
/* 0B6930 800B5D30 25290001 */  addiu $t1, $t1, 1
/* 0B6934 800B5D34 26100001 */  addiu $s0, $s0, 1
/* 0B6938 800B5D38 1440FFFB */  bnez  $v0, .L800B5D28
/* 0B693C 800B5D3C 24840001 */   addiu $a0, $a0, 1
.L800B5D40:
/* 0B6940 800B5D40 12E00009 */  beqz  $s7, .L800B5D68
/* 0B6944 800B5D44 0008182A */   slt   $v1, $zero, $t0
/* 0B6948 800B5D48 10600007 */  beqz  $v1, .L800B5D68
/* 0B694C 800B5D4C 2508FFFF */   addiu $t0, $t0, -1
.L800B5D50:
/* 0B6950 800B5D50 0008182A */  slt   $v1, $zero, $t0
/* 0B6954 800B5D54 2508FFFF */  addiu $t0, $t0, -1
/* 0B6958 800B5D58 25290001 */  addiu $t1, $t1, 1
/* 0B695C 800B5D5C A20D0000 */  sb    $t5, ($s0)
/* 0B6960 800B5D60 1460FFFB */  bnez  $v1, .L800B5D50
/* 0B6964 800B5D64 26100001 */   addiu $s0, $s0, 1
.L800B5D68:
/* 0B6968 800B5D68 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B696C 800B5D6C 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B6970 800B5D70 10000029 */  b     .L800B5E18
/* 0B6974 800B5D74 00000000 */   nop   
/* 0B6978 800B5D78 1080000A */  beqz  $a0, .L800B5DA4
/* 0B697C 800B5D7C 3C03800E */   lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B6980 800B5D80 26310003 */  addiu $s1, $s1, 3
/* 0B6984 800B5D84 2401FFFC */  li    $at, -4
/* 0B6988 800B5D88 02217024 */  and   $t6, $s1, $at
/* 0B698C 800B5D8C 25D10004 */  addiu $s1, $t6, 4
/* 0B6990 800B5D90 8E22FFFC */  lw    $v0, -4($s1)
/* 0B6994 800B5D94 0009C7C3 */  sra   $t8, $t1, 0x1f
/* 0B6998 800B5D98 AC580000 */  sw    $t8, ($v0)
/* 0B699C 800B5D9C 10000018 */  b     .L800B5E00
/* 0B69A0 800B5DA0 AC490004 */   sw    $t1, 4($v0)
.L800B5DA4:
/* 0B69A4 800B5DA4 10A00007 */  beqz  $a1, .L800B5DC4
/* 0B69A8 800B5DA8 2401FFFC */   li    $at, -4
/* 0B69AC 800B5DAC 26310003 */  addiu $s1, $s1, 3
/* 0B69B0 800B5DB0 02217824 */  and   $t7, $s1, $at
/* 0B69B4 800B5DB4 25F10004 */  addiu $s1, $t7, 4
/* 0B69B8 800B5DB8 8E22FFFC */  lw    $v0, -4($s1)
/* 0B69BC 800B5DBC 10000010 */  b     .L800B5E00
/* 0B69C0 800B5DC0 AC490000 */   sw    $t1, ($v0)
.L800B5DC4:
/* 0B69C4 800B5DC4 14C00008 */  bnez  $a2, .L800B5DE8
/* 0B69C8 800B5DC8 2401FFFC */   li    $at, -4
/* 0B69CC 800B5DCC 26310003 */  addiu $s1, $s1, 3
/* 0B69D0 800B5DD0 2401FFFC */  li    $at, -4
/* 0B69D4 800B5DD4 02217024 */  and   $t6, $s1, $at
/* 0B69D8 800B5DD8 25D10004 */  addiu $s1, $t6, 4
/* 0B69DC 800B5DDC 8E22FFFC */  lw    $v0, -4($s1)
/* 0B69E0 800B5DE0 10000007 */  b     .L800B5E00
/* 0B69E4 800B5DE4 AC490000 */   sw    $t1, ($v0)
.L800B5DE8:
/* 0B69E8 800B5DE8 26310003 */  addiu $s1, $s1, 3
/* 0B69EC 800B5DEC 0221C024 */  and   $t8, $s1, $at
/* 0B69F0 800B5DF0 27110004 */  addiu $s1, $t8, 4
/* 0B69F4 800B5DF4 8E22FFFC */  lw    $v0, -4($s1)
/* 0B69F8 800B5DF8 00000000 */  nop   
/* 0B69FC 800B5DFC A4490000 */  sh    $t1, ($v0)
.L800B5E00:
/* 0B6A00 800B5E00 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B6A04 800B5E04 10000004 */  b     .L800B5E18
/* 0B6A08 800B5E08 00000000 */   nop   
.L800B5E0C:
/* 0B6A0C 800B5E0C 3C03800E */  lui   $v1, %hi(D_800E2EF0) # $v1, 0x800e
/* 0B6A10 800B5E10 8C632EF0 */  lw    $v1, %lo(D_800E2EF0)($v1)
/* 0B6A14 800B5E14 00000000 */  nop   
.L800B5E18:
/* 0B6A18 800B5E18 10600004 */  beqz  $v1, .L800B5E2C
/* 0B6A1C 800B5E1C 24190083 */   li    $t9, 131
/* 0B6A20 800B5E20 25290001 */  addiu $t1, $t1, 1
/* 0B6A24 800B5E24 A2190000 */  sb    $t9, ($s0)
/* 0B6A28 800B5E28 26100001 */  addiu $s0, $s0, 1
.L800B5E2C:
/* 0B6A2C 800B5E2C 91630000 */  lbu   $v1, ($t3)
.L800B5E30:
/* 0B6A30 800B5E30 24040025 */  li    $a0, 37
/* 0B6A34 800B5E34 1460FB22 */  bnez  $v1, .L800B4AC0
/* 0B6A38 800B5E38 00601025 */   move  $v0, $v1
/* 0B6A3C 800B5E3C E7B100E0 */  swc1  $f17, 0xe0($sp)
/* 0B6A40 800B5E40 E7B000E4 */  swc1  $f16, 0xe4($sp)
/* 0B6A44 800B5E44 AFB400C8 */  sw    $s4, 0xc8($sp)
.L800B5E48:
/* 0B6A48 800B5E48 A2000000 */  sb    $zero, ($s0)
/* 0B6A4C 800B5E4C 8FBF004C */  lw    $ra, 0x4c($sp)
/* 0B6A50 800B5E50 8FBE0048 */  lw    $fp, 0x48($sp)
/* 0B6A54 800B5E54 8FB70044 */  lw    $s7, 0x44($sp)
/* 0B6A58 800B5E58 8FB60040 */  lw    $s6, 0x40($sp)
/* 0B6A5C 800B5E5C 8FB5003C */  lw    $s5, 0x3c($sp)
/* 0B6A60 800B5E60 8FB40038 */  lw    $s4, 0x38($sp)
/* 0B6A64 800B5E64 8FB30034 */  lw    $s3, 0x34($sp)
/* 0B6A68 800B5E68 8FB20030 */  lw    $s2, 0x30($sp)
/* 0B6A6C 800B5E6C 8FB1002C */  lw    $s1, 0x2c($sp)
/* 0B6A70 800B5E70 8FB00028 */  lw    $s0, 0x28($sp)
/* 0B6A74 800B5E74 C7B40024 */  lwc1  $f20, 0x24($sp)
/* 0B6A78 800B5E78 C7B50020 */  lwc1  $f21, 0x20($sp)
/* 0B6A7C 800B5E7C 27BD01B8 */  addiu $sp, $sp, 0x1b8
/* 0B6A80 800B5E80 03E00008 */  jr    $ra
/* 0B6A84 800B5E84 01201025 */   move  $v0, $t1

glabel func_800B5E88
/* 0B6A88 800B5E88 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0B6A8C 800B5E8C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B6A90 800B5E90 0C01EB9D */  jal   func_8007AE74
/* 0B6A94 800B5E94 00002025 */   move  $a0, $zero
/* 0B6A98 800B5E98 3C018012 */  lui   $at, %hi(D_80127CA0) # $at, 0x8012
/* 0B6A9C 800B5E9C AC227CA0 */  sw    $v0, %lo(D_80127CA0)($at)
/* 0B6AA0 800B5EA0 0C01EB9D */  jal   func_8007AE74
/* 0B6AA4 800B5EA4 24040001 */   li    $a0, 1
/* 0B6AA8 800B5EA8 3C018012 */  lui   $at, %hi(D_80127CA4) # $at, 0x8012
/* 0B6AAC 800B5EAC AC227CA4 */  sw    $v0, %lo(D_80127CA4)($at)
/* 0B6AB0 800B5EB0 0C01EB9D */  jal   func_8007AE74
/* 0B6AB4 800B5EB4 24040002 */   li    $a0, 2
/* 0B6AB8 800B5EB8 3C018012 */  lui   $at, %hi(D_80127CA8) # $at, 0x8012
/* 0B6ABC 800B5EBC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B6AC0 800B5EC0 AC227CA8 */  sw    $v0, %lo(D_80127CA8)($at)
/* 0B6AC4 800B5EC4 3C0E8012 */  lui   $t6, %hi(D_80127CD8) # $t6, 0x8012
/* 0B6AC8 800B5EC8 25CE7CD8 */  addiu $t6, %lo(D_80127CD8) # addiu $t6, $t6, 0x7cd8
/* 0B6ACC 800B5ECC 3C018013 */  lui   $at, %hi(D_801285D8) # $at, 0x8013
/* 0B6AD0 800B5ED0 AC2E85D8 */  sw    $t6, %lo(D_801285D8)($at)
/* 0B6AD4 800B5ED4 03E00008 */  jr    $ra
/* 0B6AD8 800B5ED8 27BD0018 */   addiu $sp, $sp, 0x18

glabel func_800B5EDC
/* 0B6ADC 800B5EDC 3C0E8013 */  lui   $t6, %hi(D_801285D8) # $t6, 0x8013
/* 0B6AE0 800B5EE0 8DCE85D8 */  lw    $t6, %lo(D_801285D8)($t6)
/* 0B6AE4 800B5EE4 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0B6AE8 800B5EE8 3C0F8012 */  lui   $t7, %hi(D_80127CD8) # $t7, 0x8012
/* 0B6AEC 800B5EEC 25EF7CD8 */  addiu $t7, %lo(D_80127CD8) # addiu $t7, $t7, 0x7cd8
/* 0B6AF0 800B5EF0 01CFC023 */  subu  $t8, $t6, $t7
/* 0B6AF4 800B5EF4 2B010801 */  slti  $at, $t8, 0x801
/* 0B6AF8 800B5EF8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B6AFC 800B5EFC AFA40020 */  sw    $a0, 0x20($sp)
/* 0B6B00 800B5F00 AFA50024 */  sw    $a1, 0x24($sp)
/* 0B6B04 800B5F04 AFA60028 */  sw    $a2, 0x28($sp)
/* 0B6B08 800B5F08 14200003 */  bnez  $at, .L800B5F18
/* 0B6B0C 800B5F0C AFA7002C */   sw    $a3, 0x2c($sp)
/* 0B6B10 800B5F10 10000015 */  b     .L800B5F68
/* 0B6B14 800B5F14 2402FFFF */   li    $v0, -1
.L800B5F18:
/* 0B6B18 800B5F18 0C02D282 */  jal   func_800B4A08
/* 0B6B1C 800B5F1C 24040001 */   li    $a0, 1
/* 0B6B20 800B5F20 3C048013 */  lui   $a0, %hi(D_801285D8) # $a0, 0x8013
/* 0B6B24 800B5F24 8C8485D8 */  lw    $a0, %lo(D_801285D8)($a0)
/* 0B6B28 800B5F28 8FA50020 */  lw    $a1, 0x20($sp)
/* 0B6B2C 800B5F2C 0C02D290 */  jal   func_800B4A40
/* 0B6B30 800B5F30 27A60024 */   addiu $a2, $sp, 0x24
/* 0B6B34 800B5F34 00002025 */  move  $a0, $zero
/* 0B6B38 800B5F38 0C02D282 */  jal   func_800B4A08
/* 0B6B3C 800B5F3C AFA20018 */   sw    $v0, 0x18($sp)
/* 0B6B40 800B5F40 8FA30018 */  lw    $v1, 0x18($sp)
/* 0B6B44 800B5F44 3C028013 */  lui   $v0, %hi(D_801285D8) # $v0, 0x8013
/* 0B6B48 800B5F48 18600006 */  blez  $v1, .L800B5F64
/* 0B6B4C 800B5F4C 244285D8 */   addiu $v0, %lo(D_801285D8) # addiu $v0, $v0, -0x7a28
/* 0B6B50 800B5F50 8C590000 */  lw    $t9, ($v0)
/* 0B6B54 800B5F54 00000000 */  nop   
/* 0B6B58 800B5F58 03234021 */  addu  $t0, $t9, $v1
/* 0B6B5C 800B5F5C 25090001 */  addiu $t1, $t0, 1
/* 0B6B60 800B5F60 AC490000 */  sw    $t1, ($v0)
.L800B5F64:
/* 0B6B64 800B5F64 00001025 */  move  $v0, $zero
.L800B5F68:
/* 0B6B68 800B5F68 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B6B6C 800B5F6C 27BD0020 */  addiu $sp, $sp, 0x20
/* 0B6B70 800B5F70 03E00008 */  jr    $ra
/* 0B6B74 800B5F74 00000000 */   nop   

glabel func_800B5F78
/* 0B6B78 800B5F78 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0B6B7C 800B5F7C AFBF0034 */  sw    $ra, 0x34($sp)
/* 0B6B80 800B5F80 AFB3002C */  sw    $s3, 0x2c($sp)
/* 0B6B84 800B5F84 00809825 */  move  $s3, $a0
/* 0B6B88 800B5F88 AFB40030 */  sw    $s4, 0x30($sp)
/* 0B6B8C 800B5F8C AFB20028 */  sw    $s2, 0x28($sp)
/* 0B6B90 800B5F90 AFB10024 */  sw    $s1, 0x24($sp)
/* 0B6B94 800B5F94 0C01E015 */  jal   func_80078054
/* 0B6B98 800B5F98 AFB00020 */   sw    $s0, 0x20($sp)
/* 0B6B9C 800B5F9C 0C01E948 */  jal   func_8007A520
/* 0B6BA0 800B5FA0 00000000 */   nop   
/* 0B6BA4 800B5FA4 3C048012 */  lui   $a0, %hi(D_80127CD2) # $a0, 0x8012
/* 0B6BA8 800B5FA8 3C058012 */  lui   $a1, %hi(D_80127CD0) # $a1, 0x8012
/* 0B6BAC 800B5FAC 24A57CD0 */  addiu $a1, %lo(D_80127CD0) # addiu $a1, $a1, 0x7cd0
/* 0B6BB0 800B5FB0 24847CD2 */  addiu $a0, %lo(D_80127CD2) # addiu $a0, $a0, 0x7cd2
/* 0B6BB4 800B5FB4 00027402 */  srl   $t6, $v0, 0x10
/* 0B6BB8 800B5FB8 A48E0000 */  sh    $t6, ($a0)
/* 0B6BBC 800B5FBC A4A20000 */  sh    $v0, ($a1)
/* 0B6BC0 800B5FC0 8E630000 */  lw    $v1, ($s3)
/* 0B6BC4 800B5FC4 3C19ED00 */  lui   $t9, 0xed00
/* 0B6BC8 800B5FC8 24780008 */  addiu $t8, $v1, 8
/* 0B6BCC 800B5FCC AE780000 */  sw    $t8, ($s3)
/* 0B6BD0 800B5FD0 AC790000 */  sw    $t9, ($v1)
/* 0B6BD4 800B5FD4 94A80000 */  lhu   $t0, ($a1)
/* 0B6BD8 800B5FD8 3C014080 */  li    $at, 0x40800000 # 4.000000
/* 0B6BDC 800B5FDC 44882000 */  mtc1  $t0, $f4
/* 0B6BE0 800B5FE0 44810000 */  mtc1  $at, $f0
/* 0B6BE4 800B5FE4 05010005 */  bgez  $t0, .L800B5FFC
/* 0B6BE8 800B5FE8 468021A0 */   cvt.s.w $f6, $f4
/* 0B6BEC 800B5FEC 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0B6BF0 800B5FF0 44814000 */  mtc1  $at, $f8
/* 0B6BF4 800B5FF4 00000000 */  nop   
/* 0B6BF8 800B5FF8 46083180 */  add.s $f6, $f6, $f8
.L800B5FFC:
/* 0B6BFC 800B5FFC 46003282 */  mul.s $f10, $f6, $f0
/* 0B6C00 800B6000 948D0000 */  lhu   $t5, ($a0)
/* 0B6C04 800B6004 00000000 */  nop   
/* 0B6C08 800B6008 448D9000 */  mtc1  $t5, $f18
/* 0B6C0C 800B600C 4449F800 */  cfc1  $t1, $31
/* 0B6C10 800B6010 00000000 */  nop   
/* 0B6C14 800B6014 35210003 */  ori   $at, $t1, 3
/* 0B6C18 800B6018 38210002 */  xori  $at, $at, 2
/* 0B6C1C 800B601C 44C1F800 */  ctc1  $at, $31
/* 0B6C20 800B6020 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0B6C24 800B6024 46005424 */  cvt.w.s $f16, $f10
/* 0B6C28 800B6028 440A8000 */  mfc1  $t2, $f16
/* 0B6C2C 800B602C 44C9F800 */  ctc1  $t1, $31
/* 0B6C30 800B6030 314B0FFF */  andi  $t3, $t2, 0xfff
/* 0B6C34 800B6034 000B6300 */  sll   $t4, $t3, 0xc
/* 0B6C38 800B6038 05A10004 */  bgez  $t5, .L800B604C
/* 0B6C3C 800B603C 46809120 */   cvt.s.w $f4, $f18
/* 0B6C40 800B6040 44814000 */  mtc1  $at, $f8
/* 0B6C44 800B6044 00000000 */  nop   
/* 0B6C48 800B6048 46082100 */  add.s $f4, $f4, $f8
.L800B604C:
/* 0B6C4C 800B604C 46002182 */  mul.s $f6, $f4, $f0
/* 0B6C50 800B6050 444EF800 */  cfc1  $t6, $31
/* 0B6C54 800B6054 00000000 */  nop   
/* 0B6C58 800B6058 35C10003 */  ori   $at, $t6, 3
/* 0B6C5C 800B605C 38210002 */  xori  $at, $at, 2
/* 0B6C60 800B6060 44C1F800 */  ctc1  $at, $31
/* 0B6C64 800B6064 00000000 */  nop   
/* 0B6C68 800B6068 460032A4 */  cvt.w.s $f10, $f6
/* 0B6C6C 800B606C 440F5000 */  mfc1  $t7, $f10
/* 0B6C70 800B6070 44CEF800 */  ctc1  $t6, $31
/* 0B6C74 800B6074 31F80FFF */  andi  $t8, $t7, 0xfff
/* 0B6C78 800B6078 0198C825 */  or    $t9, $t4, $t8
/* 0B6C7C 800B607C 0C02DB94 */  jal   func_800B6E50
/* 0B6C80 800B6080 AC790004 */   sw    $t9, 4($v1)
/* 0B6C84 800B6084 8E710000 */  lw    $s1, ($s3)
/* 0B6C88 800B6088 3C0A800E */  lui   $t2, %hi(D_800E2FB8) # $t2, 0x800e
/* 0B6C8C 800B608C 26280008 */  addiu $t0, $s1, 8
/* 0B6C90 800B6090 AE680000 */  sw    $t0, ($s3)
/* 0B6C94 800B6094 254A2FB8 */  addiu $t2, %lo(D_800E2FB8) # addiu $t2, $t2, 0x2fb8
/* 0B6C98 800B6098 3C090600 */  lui   $t1, 0x600
/* 0B6C9C 800B609C 3C108012 */  lui   $s0, %hi(D_80127CD8) # $s0, 0x8012
/* 0B6CA0 800B60A0 26107CD8 */  addiu $s0, %lo(D_80127CD8) # addiu $s0, $s0, 0x7cd8
/* 0B6CA4 800B60A4 AE290000 */  sw    $t1, ($s1)
/* 0B6CA8 800B60A8 0C02DBB8 */  jal   func_800B6EE0
/* 0B6CAC 800B60AC AE2A0004 */   sw    $t2, 4($s1)
/* 0B6CB0 800B60B0 3C148012 */  lui   $s4, %hi(D_80127CCC) # $s4, 0x8012
/* 0B6CB4 800B60B4 26947CCC */  addiu $s4, %lo(D_80127CCC) # addiu $s4, $s4, 0x7ccc
/* 0B6CB8 800B60B8 240BFFFF */  li    $t3, -1
/* 0B6CBC 800B60BC AE8B0000 */  sw    $t3, ($s4)
/* 0B6CC0 800B60C0 3C018012 */  lui   $at, %hi(D_80127CB4) # $at, 0x8012
/* 0B6CC4 800B60C4 3C078012 */  lui   $a3, %hi(D_80127CAC) # $a3, 0x8012
/* 0B6CC8 800B60C8 94E77CAC */  lhu   $a3, %lo(D_80127CAC)($a3)
/* 0B6CCC 800B60CC AC207CB4 */  sw    $zero, %lo(D_80127CB4)($at)
/* 0B6CD0 800B60D0 3C018012 */  lui   $at, %hi(D_80127CB0) # $at, 0x8012
/* 0B6CD4 800B60D4 3C028012 */  lui   $v0, %hi(D_80127CAE) # $v0, 0x8012
/* 0B6CD8 800B60D8 94427CAE */  lhu   $v0, %lo(D_80127CAE)($v0)
/* 0B6CDC 800B60DC A4277CB0 */  sh    $a3, %lo(D_80127CB0)($at)
/* 0B6CE0 800B60E0 3C128013 */  lui   $s2, %hi(D_801285D8) # $s2, 0x8013
/* 0B6CE4 800B60E4 3C018012 */  lui   $at, %hi(D_80127CB2) # $at, 0x8012
/* 0B6CE8 800B60E8 265285D8 */  addiu $s2, %lo(D_801285D8) # addiu $s2, $s2, -0x7a28
/* 0B6CEC 800B60EC A4227CB2 */  sh    $v0, %lo(D_80127CB2)($at)
/* 0B6CF0 800B60F0 8E4E0000 */  lw    $t6, ($s2)
/* 0B6CF4 800B60F4 3C0D8012 */  lui   $t5, %hi(D_80127CD8) # $t5, 0x8012
/* 0B6CF8 800B60F8 25AD7CD8 */  addiu $t5, %lo(D_80127CD8) # addiu $t5, $t5, 0x7cd8
/* 0B6CFC 800B60FC 11AE0010 */  beq   $t5, $t6, .L800B6140
/* 0B6D00 800B6100 3C118012 */   lui   $s1, %hi(D_80127CB8) # $s1, 0x8012
/* 0B6D04 800B6104 26317CB8 */  addiu $s1, %lo(D_80127CB8) # addiu $s1, $s1, 0x7cb8
.L800B6108:
/* 0B6D08 800B6108 AE200000 */  sw    $zero, ($s1)
/* 0B6D0C 800B610C 02602025 */  move  $a0, $s3
/* 0B6D10 800B6110 0C02D94F */  jal   func_800B653C
/* 0B6D14 800B6114 02002825 */   move  $a1, $s0
/* 0B6D18 800B6118 8E4F0000 */  lw    $t7, ($s2)
/* 0B6D1C 800B611C 02028021 */  addu  $s0, $s0, $v0
/* 0B6D20 800B6120 160FFFF9 */  bne   $s0, $t7, .L800B6108
/* 0B6D24 800B6124 00000000 */   nop   
/* 0B6D28 800B6128 3C078012 */  lui   $a3, %hi(D_80127CAC) # $a3, 0x8012
/* 0B6D2C 800B612C 3C028012 */  lui   $v0, %hi(D_80127CAE) # $v0, 0x8012
/* 0B6D30 800B6130 3C108012 */  lui   $s0, %hi(D_80127CD8) # $s0, 0x8012
/* 0B6D34 800B6134 94427CAE */  lhu   $v0, %lo(D_80127CAE)($v0)
/* 0B6D38 800B6138 94E77CAC */  lhu   $a3, %lo(D_80127CAC)($a3)
/* 0B6D3C 800B613C 26107CD8 */  addiu $s0, %lo(D_80127CD8) # addiu $s0, $s0, 0x7cd8
.L800B6140:
/* 0B6D40 800B6140 3C058012 */  lui   $a1, %hi(D_80127CB0) # $a1, 0x8012
/* 0B6D44 800B6144 3C068012 */  lui   $a2, %hi(D_80127CB2) # $a2, 0x8012
/* 0B6D48 800B6148 3C118012 */  lui   $s1, %hi(D_80127CB8) # $s1, 0x8012
/* 0B6D4C 800B614C 94C67CB2 */  lhu   $a2, %lo(D_80127CB2)($a2)
/* 0B6D50 800B6150 94A57CB0 */  lhu   $a1, %lo(D_80127CB0)($a1)
/* 0B6D54 800B6154 244C000A */  addiu $t4, $v0, 0xa
/* 0B6D58 800B6158 26317CB8 */  addiu $s1, %lo(D_80127CB8) # addiu $s1, $s1, 0x7cb8
/* 0B6D5C 800B615C AFAC0010 */  sw    $t4, 0x10($sp)
/* 0B6D60 800B6160 0C02DA57 */  jal   func_800B695C
/* 0B6D64 800B6164 02602025 */   move  $a0, $s3
/* 0B6D68 800B6168 0C02DBB8 */  jal   func_800B6EE0
/* 0B6D6C 800B616C 00000000 */   nop   
/* 0B6D70 800B6170 2418FFFF */  li    $t8, -1
/* 0B6D74 800B6174 AE980000 */  sw    $t8, ($s4)
/* 0B6D78 800B6178 3C018012 */  lui   $at, %hi(D_80127CB4) # $at, 0x8012
/* 0B6D7C 800B617C AC207CB4 */  sw    $zero, %lo(D_80127CB4)($at)
/* 0B6D80 800B6180 8E480000 */  lw    $t0, ($s2)
/* 0B6D84 800B6184 3C198012 */  lui   $t9, %hi(D_80127CD8) # $t9, 0x8012
/* 0B6D88 800B6188 27397CD8 */  addiu $t9, %lo(D_80127CD8) # addiu $t9, $t9, 0x7cd8
/* 0B6D8C 800B618C 13280009 */  beq   $t9, $t0, .L800B61B4
/* 0B6D90 800B6190 24140001 */   li    $s4, 1
.L800B6194:
/* 0B6D94 800B6194 AE340000 */  sw    $s4, ($s1)
/* 0B6D98 800B6198 02602025 */  move  $a0, $s3
/* 0B6D9C 800B619C 0C02D94F */  jal   func_800B653C
/* 0B6DA0 800B61A0 02002825 */   move  $a1, $s0
/* 0B6DA4 800B61A4 8E490000 */  lw    $t1, ($s2)
/* 0B6DA8 800B61A8 02028021 */  addu  $s0, $s0, $v0
/* 0B6DAC 800B61AC 1609FFF9 */  bne   $s0, $t1, .L800B6194
/* 0B6DB0 800B61B0 00000000 */   nop   
.L800B61B4:
/* 0B6DB4 800B61B4 3C0A8012 */  lui   $t2, %hi(D_80127CD8) # $t2, 0x8012
/* 0B6DB8 800B61B8 254A7CD8 */  addiu $t2, %lo(D_80127CD8) # addiu $t2, $t2, 0x7cd8
/* 0B6DBC 800B61BC 8FBF0034 */  lw    $ra, 0x34($sp)
/* 0B6DC0 800B61C0 AE4A0000 */  sw    $t2, ($s2)
/* 0B6DC4 800B61C4 8FB20028 */  lw    $s2, 0x28($sp)
/* 0B6DC8 800B61C8 8FB00020 */  lw    $s0, 0x20($sp)
/* 0B6DCC 800B61CC 8FB10024 */  lw    $s1, 0x24($sp)
/* 0B6DD0 800B61D0 8FB3002C */  lw    $s3, 0x2c($sp)
/* 0B6DD4 800B61D4 8FB40030 */  lw    $s4, 0x30($sp)
/* 0B6DD8 800B61D8 03E00008 */  jr    $ra
/* 0B6DDC 800B61DC 27BD0038 */   addiu $sp, $sp, 0x38

/* 0B6DE0 800B61E0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0B6DE4 800B61E4 3C0E8012 */  lui   $t6, %hi(D_80127CD8) # $t6, 0x8012
/* 0B6DE8 800B61E8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B6DEC 800B61EC 25CE7CD8 */  addiu $t6, %lo(D_80127CD8) # addiu $t6, $t6, 0x7cd8
/* 0B6DF0 800B61F0 3C018013 */  lui   $at, %hi(D_801285D8) # $at, 0x8013
/* 0B6DF4 800B61F4 0C02DBB8 */  jal   func_800B6EE0
/* 0B6DF8 800B61F8 AC2E85D8 */   sw    $t6, %lo(D_801285D8)($at)
/* 0B6DFC 800B61FC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B6E00 800B6200 27BD0018 */  addiu $sp, $sp, 0x18
/* 0B6E04 800B6204 03E00008 */  jr    $ra
/* 0B6E08 800B6208 00000000 */   nop   

/* 0B6E0C 800B620C 3C028013 */  lui   $v0, %hi(D_801285D8) # $v0, 0x8013
/* 0B6E10 800B6210 244285D8 */  addiu $v0, %lo(D_801285D8) # addiu $v0, $v0, -0x7a28
/* 0B6E14 800B6214 8C490000 */  lw    $t1, ($v0)
/* 0B6E18 800B6218 AFA40000 */  sw    $a0, ($sp)
/* 0B6E1C 800B621C AFA50004 */  sw    $a1, 4($sp)
/* 0B6E20 800B6220 AFA60008 */  sw    $a2, 8($sp)
/* 0B6E24 800B6224 AFA7000C */  sw    $a3, 0xc($sp)
/* 0B6E28 800B6228 24080081 */  li    $t0, 129
/* 0B6E2C 800B622C A1280000 */  sb    $t0, ($t1)
/* 0B6E30 800B6230 8C4A0000 */  lw    $t2, ($v0)
/* 0B6E34 800B6234 00A07825 */  move  $t7, $a1
/* 0B6E38 800B6238 254B0001 */  addiu $t3, $t2, 1
/* 0B6E3C 800B623C AC4B0000 */  sw    $t3, ($v0)
/* 0B6E40 800B6240 A1640000 */  sb    $a0, ($t3)
/* 0B6E44 800B6244 8C4D0000 */  lw    $t5, ($v0)
/* 0B6E48 800B6248 01E02825 */  move  $a1, $t7
/* 0B6E4C 800B624C 25AE0001 */  addiu $t6, $t5, 1
/* 0B6E50 800B6250 00C0C025 */  move  $t8, $a2
/* 0B6E54 800B6254 AC4E0000 */  sw    $t6, ($v0)
/* 0B6E58 800B6258 03003025 */  move  $a2, $t8
/* 0B6E5C 800B625C A1C50000 */  sb    $a1, ($t6)
/* 0B6E60 800B6260 8C580000 */  lw    $t8, ($v0)
/* 0B6E64 800B6264 00E0C825 */  move  $t9, $a3
/* 0B6E68 800B6268 03203825 */  move  $a3, $t9
/* 0B6E6C 800B626C 27190001 */  addiu $t9, $t8, 1
/* 0B6E70 800B6270 AC590000 */  sw    $t9, ($v0)
/* 0B6E74 800B6274 A3260000 */  sb    $a2, ($t9)
/* 0B6E78 800B6278 8C490000 */  lw    $t1, ($v0)
/* 0B6E7C 800B627C 00000000 */  nop   
/* 0B6E80 800B6280 252A0001 */  addiu $t2, $t1, 1
/* 0B6E84 800B6284 AC4A0000 */  sw    $t2, ($v0)
/* 0B6E88 800B6288 A1470000 */  sb    $a3, ($t2)
/* 0B6E8C 800B628C 8C4C0000 */  lw    $t4, ($v0)
/* 0B6E90 800B6290 00000000 */  nop   
/* 0B6E94 800B6294 258D0001 */  addiu $t5, $t4, 1
/* 0B6E98 800B6298 AC4D0000 */  sw    $t5, ($v0)
/* 0B6E9C 800B629C A1A00000 */  sb    $zero, ($t5)
/* 0B6EA0 800B62A0 8C4F0000 */  lw    $t7, ($v0)
/* 0B6EA4 800B62A4 00000000 */  nop   
/* 0B6EA8 800B62A8 25F80001 */  addiu $t8, $t7, 1
/* 0B6EAC 800B62AC 03E00008 */  jr    $ra
/* 0B6EB0 800B62B0 AC580000 */   sw    $t8, ($v0)

glabel func_800B62B4
/* 0B6EB4 800B62B4 3C028013 */  lui   $v0, %hi(D_801285D8) # $v0, 0x8013
/* 0B6EB8 800B62B8 244285D8 */  addiu $v0, %lo(D_801285D8) # addiu $v0, $v0, -0x7a28
/* 0B6EBC 800B62BC 8C490000 */  lw    $t1, ($v0)
/* 0B6EC0 800B62C0 AFA40000 */  sw    $a0, ($sp)
/* 0B6EC4 800B62C4 AFA50004 */  sw    $a1, 4($sp)
/* 0B6EC8 800B62C8 AFA60008 */  sw    $a2, 8($sp)
/* 0B6ECC 800B62CC AFA7000C */  sw    $a3, 0xc($sp)
/* 0B6ED0 800B62D0 24080085 */  li    $t0, 133
/* 0B6ED4 800B62D4 A1280000 */  sb    $t0, ($t1)
/* 0B6ED8 800B62D8 8C4A0000 */  lw    $t2, ($v0)
/* 0B6EDC 800B62DC 00A07825 */  move  $t7, $a1
/* 0B6EE0 800B62E0 254B0001 */  addiu $t3, $t2, 1
/* 0B6EE4 800B62E4 AC4B0000 */  sw    $t3, ($v0)
/* 0B6EE8 800B62E8 A1640000 */  sb    $a0, ($t3)
/* 0B6EEC 800B62EC 8C4D0000 */  lw    $t5, ($v0)
/* 0B6EF0 800B62F0 01E02825 */  move  $a1, $t7
/* 0B6EF4 800B62F4 25AE0001 */  addiu $t6, $t5, 1
/* 0B6EF8 800B62F8 00C0C025 */  move  $t8, $a2
/* 0B6EFC 800B62FC AC4E0000 */  sw    $t6, ($v0)
/* 0B6F00 800B6300 03003025 */  move  $a2, $t8
/* 0B6F04 800B6304 A1C50000 */  sb    $a1, ($t6)
/* 0B6F08 800B6308 8C580000 */  lw    $t8, ($v0)
/* 0B6F0C 800B630C 00E0C825 */  move  $t9, $a3
/* 0B6F10 800B6310 03203825 */  move  $a3, $t9
/* 0B6F14 800B6314 27190001 */  addiu $t9, $t8, 1
/* 0B6F18 800B6318 AC590000 */  sw    $t9, ($v0)
/* 0B6F1C 800B631C A3260000 */  sb    $a2, ($t9)
/* 0B6F20 800B6320 8C490000 */  lw    $t1, ($v0)
/* 0B6F24 800B6324 00000000 */  nop   
/* 0B6F28 800B6328 252A0001 */  addiu $t2, $t1, 1
/* 0B6F2C 800B632C AC4A0000 */  sw    $t2, ($v0)
/* 0B6F30 800B6330 A1470000 */  sb    $a3, ($t2)
/* 0B6F34 800B6334 8C4C0000 */  lw    $t4, ($v0)
/* 0B6F38 800B6338 00000000 */  nop   
/* 0B6F3C 800B633C 258D0001 */  addiu $t5, $t4, 1
/* 0B6F40 800B6340 AC4D0000 */  sw    $t5, ($v0)
/* 0B6F44 800B6344 A1A00000 */  sb    $zero, ($t5)
/* 0B6F48 800B6348 8C4F0000 */  lw    $t7, ($v0)
/* 0B6F4C 800B634C 00000000 */  nop   
/* 0B6F50 800B6350 25F80001 */  addiu $t8, $t7, 1
/* 0B6F54 800B6354 03E00008 */  jr    $ra
/* 0B6F58 800B6358 AC580000 */   sw    $t8, ($v0)

glabel func_800B635C
/* 0B6F5C 800B635C 3C068013 */  lui   $a2, %hi(D_801285D8) # $a2, 0x8013
/* 0B6F60 800B6360 24C685D8 */  addiu $a2, %lo(D_801285D8) # addiu $a2, $a2, -0x7a28
/* 0B6F64 800B6364 8CD90000 */  lw    $t9, ($a2)
/* 0B6F68 800B6368 AFA40000 */  sw    $a0, ($sp)
/* 0B6F6C 800B636C AFA50004 */  sw    $a1, 4($sp)
/* 0B6F70 800B6370 24180082 */  li    $t8, 130
/* 0B6F74 800B6374 A3380000 */  sb    $t8, ($t9)
/* 0B6F78 800B6378 8CC80000 */  lw    $t0, ($a2)
/* 0B6F7C 800B637C 00A07825 */  move  $t7, $a1
/* 0B6F80 800B6380 25090001 */  addiu $t1, $t0, 1
/* 0B6F84 800B6384 ACC90000 */  sw    $t1, ($a2)
/* 0B6F88 800B6388 A1240000 */  sb    $a0, ($t1)
/* 0B6F8C 800B638C 8CCC0000 */  lw    $t4, ($a2)
/* 0B6F90 800B6390 01E02825 */  move  $a1, $t7
/* 0B6F94 800B6394 258D0001 */  addiu $t5, $t4, 1
/* 0B6F98 800B6398 ACCD0000 */  sw    $t5, ($a2)
/* 0B6F9C 800B639C 00047A03 */  sra   $t7, $a0, 8
/* 0B6FA0 800B63A0 A1AF0000 */  sb    $t7, ($t5)
/* 0B6FA4 800B63A4 8CD90000 */  lw    $t9, ($a2)
/* 0B6FA8 800B63A8 00057203 */  sra   $t6, $a1, 8
/* 0B6FAC 800B63AC 27280001 */  addiu $t0, $t9, 1
/* 0B6FB0 800B63B0 ACC80000 */  sw    $t0, ($a2)
/* 0B6FB4 800B63B4 A1050000 */  sb    $a1, ($t0)
/* 0B6FB8 800B63B8 8CCB0000 */  lw    $t3, ($a2)
/* 0B6FBC 800B63BC 00000000 */  nop   
/* 0B6FC0 800B63C0 256C0001 */  addiu $t4, $t3, 1
/* 0B6FC4 800B63C4 ACCC0000 */  sw    $t4, ($a2)
/* 0B6FC8 800B63C8 A18E0000 */  sb    $t6, ($t4)
/* 0B6FCC 800B63CC 8CD80000 */  lw    $t8, ($a2)
/* 0B6FD0 800B63D0 00000000 */  nop   
/* 0B6FD4 800B63D4 27190001 */  addiu $t9, $t8, 1
/* 0B6FD8 800B63D8 ACD90000 */  sw    $t9, ($a2)
/* 0B6FDC 800B63DC A3200000 */  sb    $zero, ($t9)
/* 0B6FE0 800B63E0 8CC90000 */  lw    $t1, ($a2)
/* 0B6FE4 800B63E4 00000000 */  nop   
/* 0B6FE8 800B63E8 252A0001 */  addiu $t2, $t1, 1
/* 0B6FEC 800B63EC 03E00008 */  jr    $ra
/* 0B6FF0 800B63F0 ACCA0000 */   sw    $t2, ($a2)

/* 0B6FF4 800B63F4 27BDFEC8 */  addiu $sp, $sp, -0x138
/* 0B6FF8 800B63F8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B6FFC 800B63FC AFA40138 */  sw    $a0, 0x138($sp)
/* 0B7000 800B6400 AFA5013C */  sw    $a1, 0x13c($sp)
/* 0B7004 800B6404 AFA60140 */  sw    $a2, 0x140($sp)
/* 0B7008 800B6408 AFA70144 */  sw    $a3, 0x144($sp)
/* 0B700C 800B640C 24040001 */  li    $a0, 1
/* 0B7010 800B6410 0C02D282 */  jal   func_800B4A08
/* 0B7014 800B6414 AFA0012C */   sw    $zero, 0x12c($sp)
/* 0B7018 800B6418 8FA50138 */  lw    $a1, 0x138($sp)
/* 0B701C 800B641C 27A4002C */  addiu $a0, $sp, 0x2c
/* 0B7020 800B6420 0C02D290 */  jal   func_800B4A40
/* 0B7024 800B6424 27A6013C */   addiu $a2, $sp, 0x13c
/* 0B7028 800B6428 0C02D282 */  jal   func_800B4A08
/* 0B702C 800B642C 00002025 */   move  $a0, $zero
/* 0B7030 800B6430 93AF002C */  lbu   $t7, 0x2c($sp)
/* 0B7034 800B6434 8FA7012C */  lw    $a3, 0x12c($sp)
/* 0B7038 800B6438 27AE002C */  addiu $t6, $sp, 0x2c
/* 0B703C 800B643C 11E0003B */  beqz  $t7, .L800B652C
/* 0B7040 800B6440 01C01825 */   move  $v1, $t6
/* 0B7044 800B6444 91C50000 */  lbu   $a1, ($t6)
/* 0B7048 800B6448 3C0A800E */  lui   $t2, %hi(D_800E2EF4) # $t2, 0x800e
/* 0B704C 800B644C 3C068012 */  lui   $a2, %hi(D_80127CCC) # $a2, 0x8012
/* 0B7050 800B6450 24C67CCC */  addiu $a2, %lo(D_80127CCC) # addiu $a2, $a2, 0x7ccc
/* 0B7054 800B6454 254A2EF4 */  addiu $t2, %lo(D_800E2EF4) # addiu $t2, $t2, 0x2ef4
/* 0B7058 800B6458 240C0002 */  li    $t4, 2
/* 0B705C 800B645C 240B0001 */  li    $t3, 1
/* 0B7060 800B6460 24090020 */  li    $t1, 32
/* 0B7064 800B6464 2408000A */  li    $t0, 10
/* 0B7068 800B6468 00A01025 */  move  $v0, $a1
.L800B646C:
/* 0B706C 800B646C 1048002B */  beq   $v0, $t0, .L800B651C
/* 0B7070 800B6470 00000000 */   nop   
/* 0B7074 800B6474 14490003 */  bne   $v0, $t1, .L800B6484
/* 0B7078 800B6478 28410040 */   slti  $at, $v0, 0x40
/* 0B707C 800B647C 10000027 */  b     .L800B651C
/* 0B7080 800B6480 24E70006 */   addiu $a3, $a3, 6
.L800B6484:
/* 0B7084 800B6484 10200009 */  beqz  $at, .L800B64AC
/* 0B7088 800B6488 28410060 */   slti  $at, $v0, 0x60
/* 0B708C 800B648C ACC00000 */  sw    $zero, ($a2)
/* 0B7090 800B6490 90780000 */  lbu   $t8, ($v1)
/* 0B7094 800B6494 00000000 */  nop   
/* 0B7098 800B6498 2719FFDF */  addiu $t9, $t8, -0x21
/* 0B709C 800B649C A0790000 */  sb    $t9, ($v1)
/* 0B70A0 800B64A0 10000014 */  b     .L800B64F4
/* 0B70A4 800B64A4 332500FF */   andi  $a1, $t9, 0xff
/* 0B70A8 800B64A8 28410060 */  slti  $at, $v0, 0x60
.L800B64AC:
/* 0B70AC 800B64AC 10200009 */  beqz  $at, .L800B64D4
/* 0B70B0 800B64B0 28410080 */   slti  $at, $v0, 0x80
/* 0B70B4 800B64B4 ACCB0000 */  sw    $t3, ($a2)
/* 0B70B8 800B64B8 906D0000 */  lbu   $t5, ($v1)
/* 0B70BC 800B64BC 00000000 */  nop   
/* 0B70C0 800B64C0 25AFFFC0 */  addiu $t7, $t5, -0x40
/* 0B70C4 800B64C4 A06F0000 */  sb    $t7, ($v1)
/* 0B70C8 800B64C8 1000000A */  b     .L800B64F4
/* 0B70CC 800B64CC 31E500FF */   andi  $a1, $t7, 0xff
/* 0B70D0 800B64D0 28410080 */  slti  $at, $v0, 0x80
.L800B64D4:
/* 0B70D4 800B64D4 10200007 */  beqz  $at, .L800B64F4
/* 0B70D8 800B64D8 00000000 */   nop   
/* 0B70DC 800B64DC ACCC0000 */  sw    $t4, ($a2)
/* 0B70E0 800B64E0 906E0000 */  lbu   $t6, ($v1)
/* 0B70E4 800B64E4 00000000 */  nop   
/* 0B70E8 800B64E8 25D8FFA0 */  addiu $t8, $t6, -0x60
/* 0B70EC 800B64EC A0780000 */  sb    $t8, ($v1)
/* 0B70F0 800B64F0 330500FF */  andi  $a1, $t8, 0xff
.L800B64F4:
/* 0B70F4 800B64F4 8CD90000 */  lw    $t9, ($a2)
/* 0B70F8 800B64F8 00057040 */  sll   $t6, $a1, 1
/* 0B70FC 800B64FC 00196980 */  sll   $t5, $t9, 6
/* 0B7100 800B6500 014D7821 */  addu  $t7, $t2, $t5
/* 0B7104 800B6504 01EE1021 */  addu  $v0, $t7, $t6
/* 0B7108 800B6508 90580001 */  lbu   $t8, 1($v0)
/* 0B710C 800B650C 90440000 */  lbu   $a0, ($v0)
/* 0B7110 800B6510 00F8C821 */  addu  $t9, $a3, $t8
/* 0B7114 800B6514 03243823 */  subu  $a3, $t9, $a0
/* 0B7118 800B6518 24E70001 */  addiu $a3, $a3, 1
.L800B651C:
/* 0B711C 800B651C 90650001 */  lbu   $a1, 1($v1)
/* 0B7120 800B6520 24630001 */  addiu $v1, $v1, 1
/* 0B7124 800B6524 14A0FFD1 */  bnez  $a1, .L800B646C
/* 0B7128 800B6528 00A01025 */   move  $v0, $a1
.L800B652C:
/* 0B712C 800B652C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B7130 800B6530 27BD0138 */  addiu $sp, $sp, 0x138
/* 0B7134 800B6534 03E00008 */  jr    $ra
/* 0B7138 800B6538 00E01025 */   move  $v0, $a3

glabel func_800B653C
/* 0B713C 800B653C 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 0B7140 800B6540 AFBF0044 */  sw    $ra, 0x44($sp)
/* 0B7144 800B6544 AFBE0040 */  sw    $fp, 0x40($sp)
/* 0B7148 800B6548 AFB7003C */  sw    $s7, 0x3c($sp)
/* 0B714C 800B654C AFB60038 */  sw    $s6, 0x38($sp)
/* 0B7150 800B6550 AFB50034 */  sw    $s5, 0x34($sp)
/* 0B7154 800B6554 AFB40030 */  sw    $s4, 0x30($sp)
/* 0B7158 800B6558 AFB3002C */  sw    $s3, 0x2c($sp)
/* 0B715C 800B655C AFB20028 */  sw    $s2, 0x28($sp)
/* 0B7160 800B6560 AFB10024 */  sw    $s1, 0x24($sp)
/* 0B7164 800B6564 AFB00020 */  sw    $s0, 0x20($sp)
/* 0B7168 800B6568 AFA5004C */  sw    $a1, 0x4c($sp)
/* 0B716C 800B656C 90B10000 */  lbu   $s1, ($a1)
/* 0B7170 800B6570 0080A825 */  move  $s5, $a0
/* 0B7174 800B6574 122000EB */  beqz  $s1, .L800B6924
/* 0B7178 800B6578 24B00001 */   addiu $s0, $a1, 1
/* 0B717C 800B657C 3C1E8012 */  lui   $fp, %hi(D_80127CB8) # $fp, 0x8012
/* 0B7180 800B6580 3C178012 */  lui   $s7, %hi(D_80127CB2) # $s7, 0x8012
/* 0B7184 800B6584 3C168012 */  lui   $s6, %hi(D_80127CB0) # $s6, 0x8012
/* 0B7188 800B6588 3C148012 */  lui   $s4, %hi(D_80127CAE) # $s4, 0x8012
/* 0B718C 800B658C 3C128012 */  lui   $s2, %hi(D_80127CAC) # $s2, 0x8012
/* 0B7190 800B6590 26527CAC */  addiu $s2, %lo(D_80127CAC) # addiu $s2, $s2, 0x7cac
/* 0B7194 800B6594 26947CAE */  addiu $s4, %lo(D_80127CAE) # addiu $s4, $s4, 0x7cae
/* 0B7198 800B6598 26D67CB0 */  addiu $s6, %lo(D_80127CB0) # addiu $s6, $s6, 0x7cb0
/* 0B719C 800B659C 26F77CB2 */  addiu $s7, %lo(D_80127CB2) # addiu $s7, $s7, 0x7cb2
/* 0B71A0 800B65A0 27DE7CB8 */  addiu $fp, %lo(D_80127CB8) # addiu $fp, $fp, 0x7cb8
/* 0B71A4 800B65A4 2A21000B */  slti  $at, $s1, 0xb
.L800B65A8:
/* 0B71A8 800B65A8 14200012 */  bnez  $at, .L800B65F4
/* 0B71AC 800B65AC 00009825 */   move  $s3, $zero
/* 0B71B0 800B65B0 2A210021 */  slti  $at, $s1, 0x21
/* 0B71B4 800B65B4 1420000A */  bnez  $at, .L800B65E0
/* 0B71B8 800B65B8 262EFF7F */   addiu $t6, $s1, -0x81
/* 0B71BC 800B65BC 2DC10005 */  sltiu $at, $t6, 5
/* 0B71C0 800B65C0 102000AE */  beqz  $at, .L800B687C
/* 0B71C4 800B65C4 000E7080 */   sll   $t6, $t6, 2
/* 0B71C8 800B65C8 3C01800F */  lui   $at, 0x800f
/* 0B71CC 800B65CC 002E0821 */  addu  $at, $at, $t6
/* 0B71D0 800B65D0 8C2E8E58 */  lw    $t6, -0x71a8($at)
/* 0B71D4 800B65D4 00000000 */  nop   
/* 0B71D8 800B65D8 01C00008 */  jr    $t6
/* 0B71DC 800B65DC 00000000 */   nop   
.L800B65E0:
/* 0B71E0 800B65E0 24010020 */  li    $at, 32
/* 0B71E4 800B65E4 12210077 */  beq   $s1, $at, .L800B67C4
/* 0B71E8 800B65E8 24130006 */   li    $s3, 6
/* 0B71EC 800B65EC 100000A4 */  b     .L800B6880
/* 0B71F0 800B65F0 02A02025 */   move  $a0, $s5
.L800B65F4:
/* 0B71F4 800B65F4 24010009 */  li    $at, 9
/* 0B71F8 800B65F8 12210090 */  beq   $s1, $at, .L800B683C
/* 0B71FC 800B65FC 3C038012 */   lui   $v1, 0x8012
/* 0B7200 800B6600 2401000A */  li    $at, 10
/* 0B7204 800B6604 12210076 */  beq   $s1, $at, .L800B67E0
/* 0B7208 800B6608 00000000 */   nop   
/* 0B720C 800B660C 1000009C */  b     .L800B6880
/* 0B7210 800B6610 02A02025 */   move  $a0, $s5
/* 0B7214 800B6614 3C018012 */  lui   $at, %hi(D_80127CB4) # $at, 0x8012
/* 0B7218 800B6618 3C058012 */  lui   $a1, %hi(D_8011FFF0) # $a1, 0x8012
/* 0B721C 800B661C 94A57CD0 */  lhu   $a1, %lo(D_80127CD0)($a1)
/* 0B7220 800B6620 AC207CB4 */  sw    $zero, %lo(D_80127CB4)($at)
/* 0B7224 800B6624 96440000 */  lhu   $a0, ($s2)
/* 0B7228 800B6628 00001825 */  move  $v1, $zero
/* 0B722C 800B662C 1000009D */  b     .L800B68A4
/* 0B7230 800B6630 24A5FFF0 */   addiu $a1, %lo(D_8011FFF0) # addiu $a1, $a1, -0x10
/* 0B7234 800B6634 240F0001 */  li    $t7, 1
/* 0B7238 800B6638 3C018012 */  lui   $at, %hi(D_80127CB4) # $at, 0x8012
/* 0B723C 800B663C 3C058012 */  lui   $a1, %hi(D_8011FFF0) # $a1, 0x8012
/* 0B7240 800B6640 94A57CD0 */  lhu   $a1, %lo(D_80127CD0)($a1)
/* 0B7244 800B6644 AC2F7CB4 */  sw    $t7, %lo(D_80127CB4)($at)
/* 0B7248 800B6648 96440000 */  lhu   $a0, ($s2)
/* 0B724C 800B664C 24030001 */  li    $v1, 1
/* 0B7250 800B6650 10000094 */  b     .L800B68A4
/* 0B7254 800B6654 24A5FFF0 */   addiu $a1, %lo(D_8011FFF0) # addiu $a1, $a1, -0x10
/* 0B7258 800B6658 8FD80000 */  lw    $t8, ($fp)
/* 0B725C 800B665C 92040000 */  lbu   $a0, ($s0)
/* 0B7260 800B6660 92050001 */  lbu   $a1, 1($s0)
/* 0B7264 800B6664 92060002 */  lbu   $a2, 2($s0)
/* 0B7268 800B6668 92070003 */  lbu   $a3, 3($s0)
/* 0B726C 800B666C 13000010 */  beqz  $t8, .L800B66B0
/* 0B7270 800B6670 26100004 */   addiu $s0, $s0, 4
/* 0B7274 800B6674 8EA30000 */  lw    $v1, ($s5)
/* 0B7278 800B6678 30AB00FF */  andi  $t3, $a1, 0xff
/* 0B727C 800B667C 24790008 */  addiu $t9, $v1, 8
/* 0B7280 800B6680 AEB90000 */  sw    $t9, ($s5)
/* 0B7284 800B6684 000B6400 */  sll   $t4, $t3, 0x10
/* 0B7288 800B6688 00045600 */  sll   $t2, $a0, 0x18
/* 0B728C 800B668C 30CE00FF */  andi  $t6, $a2, 0xff
/* 0B7290 800B6690 000E7A00 */  sll   $t7, $t6, 8
/* 0B7294 800B6694 014C6825 */  or    $t5, $t2, $t4
/* 0B7298 800B6698 3C08FB00 */  lui   $t0, 0xfb00
/* 0B729C 800B669C 01AFC025 */  or    $t8, $t5, $t7
/* 0B72A0 800B66A0 30F900FF */  andi  $t9, $a3, 0xff
/* 0B72A4 800B66A4 AC680000 */  sw    $t0, ($v1)
/* 0B72A8 800B66A8 03194025 */  or    $t0, $t8, $t9
/* 0B72AC 800B66AC AC680004 */  sw    $t0, 4($v1)
.L800B66B0:
/* 0B72B0 800B66B0 3C058012 */  lui   $a1, %hi(D_8011FFF0) # $a1, 0x8012
/* 0B72B4 800B66B4 94A57CD0 */  lhu   $a1, %lo(D_80127CD0)($a1)
/* 0B72B8 800B66B8 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B72BC 800B66BC 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B72C0 800B66C0 96440000 */  lhu   $a0, ($s2)
/* 0B72C4 800B66C4 10000077 */  b     .L800B68A4
/* 0B72C8 800B66C8 24A5FFF0 */   addiu $a1, %lo(D_8011FFF0) # addiu $a1, $a1, -0x10
/* 0B72CC 800B66CC 8FC90000 */  lw    $t1, ($fp)
/* 0B72D0 800B66D0 92040000 */  lbu   $a0, ($s0)
/* 0B72D4 800B66D4 92050001 */  lbu   $a1, 1($s0)
/* 0B72D8 800B66D8 92060002 */  lbu   $a2, 2($s0)
/* 0B72DC 800B66DC 92070003 */  lbu   $a3, 3($s0)
/* 0B72E0 800B66E0 15200010 */  bnez  $t1, .L800B6724
/* 0B72E4 800B66E4 26100004 */   addiu $s0, $s0, 4
/* 0B72E8 800B66E8 8EA30000 */  lw    $v1, ($s5)
/* 0B72EC 800B66EC 30AD00FF */  andi  $t5, $a1, 0xff
/* 0B72F0 800B66F0 246B0008 */  addiu $t3, $v1, 8
/* 0B72F4 800B66F4 AEAB0000 */  sw    $t3, ($s5)
/* 0B72F8 800B66F8 000D7C00 */  sll   $t7, $t5, 0x10
/* 0B72FC 800B66FC 00047600 */  sll   $t6, $a0, 0x18
/* 0B7300 800B6700 30D900FF */  andi  $t9, $a2, 0xff
/* 0B7304 800B6704 00194200 */  sll   $t0, $t9, 8
/* 0B7308 800B6708 01CFC025 */  or    $t8, $t6, $t7
/* 0B730C 800B670C 3C0AFA00 */  lui   $t2, 0xfa00
/* 0B7310 800B6710 03084825 */  or    $t1, $t8, $t0
/* 0B7314 800B6714 30EB00FF */  andi  $t3, $a3, 0xff
/* 0B7318 800B6718 AC6A0000 */  sw    $t2, ($v1)
/* 0B731C 800B671C 012B5025 */  or    $t2, $t1, $t3
/* 0B7320 800B6720 AC6A0004 */  sw    $t2, 4($v1)
.L800B6724:
/* 0B7324 800B6724 3C058012 */  lui   $a1, %hi(D_8011FFF0) # $a1, 0x8012
/* 0B7328 800B6728 94A57CD0 */  lhu   $a1, %lo(D_80127CD0)($a1)
/* 0B732C 800B672C 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B7330 800B6730 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B7334 800B6734 96440000 */  lhu   $a0, ($s2)
/* 0B7338 800B6738 1000005A */  b     .L800B68A4
/* 0B733C 800B673C 24A5FFF0 */   addiu $a1, %lo(D_8011FFF0) # addiu $a1, $a1, -0x10
/* 0B7340 800B6740 8FCC0000 */  lw    $t4, ($fp)
/* 0B7344 800B6744 02A02025 */  move  $a0, $s5
/* 0B7348 800B6748 15800008 */  bnez  $t4, .L800B676C
/* 0B734C 800B674C 00000000 */   nop   
/* 0B7350 800B6750 968D0000 */  lhu   $t5, ($s4)
/* 0B7354 800B6754 96C50000 */  lhu   $a1, ($s6)
/* 0B7358 800B6758 96E60000 */  lhu   $a2, ($s7)
/* 0B735C 800B675C 96470000 */  lhu   $a3, ($s2)
/* 0B7360 800B6760 25AE000A */  addiu $t6, $t5, 0xa
/* 0B7364 800B6764 0C02DA57 */  jal   func_800B695C
/* 0B7368 800B6768 AFAE0010 */   sw    $t6, 0x10($sp)
.L800B676C:
/* 0B736C 800B676C 92190000 */  lbu   $t9, ($s0)
/* 0B7370 800B6770 3C058012 */  lui   $a1, %hi(D_8011FFF0) # $a1, 0x8012
/* 0B7374 800B6774 A6590000 */  sh    $t9, ($s2)
/* 0B7378 800B6778 92180001 */  lbu   $t8, 1($s0)
/* 0B737C 800B677C 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B7380 800B6780 00184200 */  sll   $t0, $t8, 8
/* 0B7384 800B6784 03284825 */  or    $t1, $t9, $t0
/* 0B7388 800B6788 A6490000 */  sh    $t1, ($s2)
/* 0B738C 800B678C 920A0002 */  lbu   $t2, 2($s0)
/* 0B7390 800B6790 3124FFFF */  andi  $a0, $t1, 0xffff
/* 0B7394 800B6794 A68A0000 */  sh    $t2, ($s4)
/* 0B7398 800B6798 920C0003 */  lbu   $t4, 3($s0)
/* 0B739C 800B679C A6C40000 */  sh    $a0, ($s6)
/* 0B73A0 800B67A0 000C6A00 */  sll   $t5, $t4, 8
/* 0B73A4 800B67A4 014D7825 */  or    $t7, $t2, $t5
/* 0B73A8 800B67A8 A68F0000 */  sh    $t7, ($s4)
/* 0B73AC 800B67AC A6EF0000 */  sh    $t7, ($s7)
/* 0B73B0 800B67B0 94A57CD0 */  lhu   $a1, %lo(D_80127CD0)($a1)
/* 0B73B4 800B67B4 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B73B8 800B67B8 26100004 */  addiu $s0, $s0, 4
/* 0B73BC 800B67BC 10000039 */  b     .L800B68A4
/* 0B73C0 800B67C0 24A5FFF0 */   addiu $a1, %lo(D_8011FFF0) # addiu $a1, $a1, -0x10
.L800B67C4:
/* 0B73C4 800B67C4 3C058012 */  lui   $a1, %hi(D_8011FFF0) # $a1, 0x8012
/* 0B73C8 800B67C8 94A57CD0 */  lhu   $a1, %lo(D_80127CD0)($a1)
/* 0B73CC 800B67CC 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B73D0 800B67D0 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B73D4 800B67D4 96440000 */  lhu   $a0, ($s2)
/* 0B73D8 800B67D8 10000032 */  b     .L800B68A4
/* 0B73DC 800B67DC 24A5FFF0 */   addiu $a1, %lo(D_8011FFF0) # addiu $a1, $a1, -0x10
.L800B67E0:
/* 0B73E0 800B67E0 8FD80000 */  lw    $t8, ($fp)
/* 0B73E4 800B67E4 02A02025 */  move  $a0, $s5
/* 0B73E8 800B67E8 17000008 */  bnez  $t8, .L800B680C
/* 0B73EC 800B67EC 00000000 */   nop   
/* 0B73F0 800B67F0 96990000 */  lhu   $t9, ($s4)
/* 0B73F4 800B67F4 96C50000 */  lhu   $a1, ($s6)
/* 0B73F8 800B67F8 96E60000 */  lhu   $a2, ($s7)
/* 0B73FC 800B67FC 96470000 */  lhu   $a3, ($s2)
/* 0B7400 800B6800 2728000A */  addiu $t0, $t9, 0xa
/* 0B7404 800B6804 0C02DA57 */  jal   func_800B695C
/* 0B7408 800B6808 AFA80010 */   sw    $t0, 0x10($sp)
.L800B680C:
/* 0B740C 800B680C 0C02DBC1 */  jal   func_800B6F04
/* 0B7410 800B6810 00000000 */   nop   
/* 0B7414 800B6814 96440000 */  lhu   $a0, ($s2)
/* 0B7418 800B6818 96890000 */  lhu   $t1, ($s4)
/* 0B741C 800B681C 3C058012 */  lui   $a1, %hi(D_8011FFF0) # $a1, 0x8012
/* 0B7420 800B6820 A6C40000 */  sh    $a0, ($s6)
/* 0B7424 800B6824 A6E90000 */  sh    $t1, ($s7)
/* 0B7428 800B6828 94A57CD0 */  lhu   $a1, %lo(D_80127CD0)($a1)
/* 0B742C 800B682C 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B7430 800B6830 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B7434 800B6834 1000001B */  b     .L800B68A4
/* 0B7438 800B6838 24A5FFF0 */   addiu $a1, %lo(D_8011FFF0) # addiu $a1, $a1, -0x10
.L800B683C:
/* 0B743C 800B683C 96440000 */  lhu   $a0, ($s2)
/* 0B7440 800B6840 3C058012 */  lui   $a1, %hi(D_8011FFF0) # $a1, 0x8012
/* 0B7444 800B6844 94A57CD0 */  lhu   $a1, %lo(D_80127CD0)($a1)
/* 0B7448 800B6848 8C637CB4 */  lw    $v1, 0x7cb4($v1)
/* 0B744C 800B684C 04810004 */  bgez  $a0, .L800B6860
/* 0B7450 800B6850 3082001F */   andi  $v0, $a0, 0x1f
/* 0B7454 800B6854 10400002 */  beqz  $v0, .L800B6860
/* 0B7458 800B6858 00000000 */   nop   
/* 0B745C 800B685C 2442FFE0 */  addiu $v0, $v0, -0x20
.L800B6860:
/* 0B7460 800B6860 14400003 */  bnez  $v0, .L800B6870
/* 0B7464 800B6864 24A5FFF0 */   addiu $a1, %lo(D_8011FFF0) # addiu $a1, $a1, -0x10
/* 0B7468 800B6868 1000000E */  b     .L800B68A4
/* 0B746C 800B686C 24130020 */   li    $s3, 32
.L800B6870:
/* 0B7470 800B6870 240B0020 */  li    $t3, 32
/* 0B7474 800B6874 1000000B */  b     .L800B68A4
/* 0B7478 800B6878 01629823 */   subu  $s3, $t3, $v0
.L800B687C:
/* 0B747C 800B687C 02A02025 */  move  $a0, $s5
.L800B6880:
/* 0B7480 800B6880 0C02DA7F */  jal   func_800B69FC
/* 0B7484 800B6884 02202825 */   move  $a1, $s1
/* 0B7488 800B6888 3C058012 */  lui   $a1, %hi(D_8011FFF0) # $a1, 0x8012
/* 0B748C 800B688C 94A57CD0 */  lhu   $a1, %lo(D_80127CD0)($a1)
/* 0B7490 800B6890 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B7494 800B6894 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B7498 800B6898 96440000 */  lhu   $a0, ($s2)
/* 0B749C 800B689C 00409825 */  move  $s3, $v0
/* 0B74A0 800B68A0 24A5FFF0 */  addiu $a1, %lo(D_8011FFF0) # addiu $a1, $a1, -0x10
.L800B68A4:
/* 0B74A4 800B68A4 10600006 */  beqz  $v1, .L800B68C0
/* 0B74A8 800B68A8 2A210020 */   slti  $at, $s1, 0x20
/* 0B74AC 800B68AC 14200004 */  bnez  $at, .L800B68C0
/* 0B74B0 800B68B0 2A210080 */   slti  $at, $s1, 0x80
/* 0B74B4 800B68B4 10200003 */  beqz  $at, .L800B68C4
/* 0B74B8 800B68B8 00936021 */   addu  $t4, $a0, $s3
/* 0B74BC 800B68BC 24130007 */  li    $s3, 7
.L800B68C0:
/* 0B74C0 800B68C0 00936021 */  addu  $t4, $a0, $s3
.L800B68C4:
/* 0B74C4 800B68C4 3187FFFF */  andi  $a3, $t4, 0xffff
/* 0B74C8 800B68C8 00A7082A */  slt   $at, $a1, $a3
/* 0B74CC 800B68CC 10200011 */  beqz  $at, .L800B6914
/* 0B74D0 800B68D0 A64C0000 */   sh    $t4, ($s2)
/* 0B74D4 800B68D4 8FCA0000 */  lw    $t2, ($fp)
/* 0B74D8 800B68D8 02A02025 */  move  $a0, $s5
/* 0B74DC 800B68DC 15400007 */  bnez  $t2, .L800B68FC
/* 0B74E0 800B68E0 00000000 */   nop   
/* 0B74E4 800B68E4 968D0000 */  lhu   $t5, ($s4)
/* 0B74E8 800B68E8 96C50000 */  lhu   $a1, ($s6)
/* 0B74EC 800B68EC 96E60000 */  lhu   $a2, ($s7)
/* 0B74F0 800B68F0 25AE000A */  addiu $t6, $t5, 0xa
/* 0B74F4 800B68F4 0C02DA57 */  jal   func_800B695C
/* 0B74F8 800B68F8 AFAE0010 */   sw    $t6, 0x10($sp)
.L800B68FC:
/* 0B74FC 800B68FC 0C02DBC1 */  jal   func_800B6F04
/* 0B7500 800B6900 00000000 */   nop   
/* 0B7504 800B6904 964F0000 */  lhu   $t7, ($s2)
/* 0B7508 800B6908 96980000 */  lhu   $t8, ($s4)
/* 0B750C 800B690C A6CF0000 */  sh    $t7, ($s6)
/* 0B7510 800B6910 A6F80000 */  sh    $t8, ($s7)
.L800B6914:
/* 0B7514 800B6914 92110000 */  lbu   $s1, ($s0)
/* 0B7518 800B6918 26100001 */  addiu $s0, $s0, 1
/* 0B751C 800B691C 1620FF22 */  bnez  $s1, .L800B65A8
/* 0B7520 800B6920 2A21000B */   slti  $at, $s1, 0xb
.L800B6924:
/* 0B7524 800B6924 8FB9004C */  lw    $t9, 0x4c($sp)
/* 0B7528 800B6928 8FBF0044 */  lw    $ra, 0x44($sp)
/* 0B752C 800B692C 02191023 */  subu  $v0, $s0, $t9
/* 0B7530 800B6930 8FB00020 */  lw    $s0, 0x20($sp)
/* 0B7534 800B6934 8FB10024 */  lw    $s1, 0x24($sp)
/* 0B7538 800B6938 8FB20028 */  lw    $s2, 0x28($sp)
/* 0B753C 800B693C 8FB3002C */  lw    $s3, 0x2c($sp)
/* 0B7540 800B6940 8FB40030 */  lw    $s4, 0x30($sp)
/* 0B7544 800B6944 8FB50034 */  lw    $s5, 0x34($sp)
/* 0B7548 800B6948 8FB60038 */  lw    $s6, 0x38($sp)
/* 0B754C 800B694C 8FB7003C */  lw    $s7, 0x3c($sp)
/* 0B7550 800B6950 8FBE0040 */  lw    $fp, 0x40($sp)
/* 0B7554 800B6954 03E00008 */  jr    $ra
/* 0B7558 800B6958 27BD0050 */   addiu $sp, $sp, 0x50

glabel func_800B695C
/* 0B755C 800B695C 8FAF0010 */  lw    $t7, 0x10($sp)
/* 0B7560 800B6960 00A77026 */  xor   $t6, $a1, $a3
/* 0B7564 800B6964 00CFC026 */  xor   $t8, $a2, $t7
/* 0B7568 800B6968 2F180001 */  sltiu $t8, $t8, 1
/* 0B756C 800B696C 2DCE0001 */  sltiu $t6, $t6, 1
/* 0B7570 800B6970 01D8C825 */  or    $t9, $t6, $t8
/* 0B7574 800B6974 1720001F */  bnez  $t9, .L800B69F4
/* 0B7578 800B6978 2CA10002 */   sltiu $at, $a1, 2
/* 0B757C 800B697C 14200002 */  bnez  $at, .L800B6988
/* 0B7580 800B6980 24E70002 */   addiu $a3, $a3, 2
/* 0B7584 800B6984 24A5FFFE */  addiu $a1, $a1, -2
.L800B6988:
/* 0B7588 800B6988 8C830000 */  lw    $v1, ($a0)
/* 0B758C 800B698C 3C0AFCFF */  lui   $t2, (0xFCFFFFFF >> 16) # lui $t2, 0xfcff
/* 0B7590 800B6990 24690008 */  addiu $t1, $v1, 8
/* 0B7594 800B6994 AC890000 */  sw    $t1, ($a0)
/* 0B7598 800B6998 3C0BFFFD */  lui   $t3, (0xFFFDF6FB >> 16) # lui $t3, 0xfffd
/* 0B759C 800B699C 356BF6FB */  ori   $t3, (0xFFFDF6FB & 0xFFFF) # ori $t3, $t3, 0xf6fb
/* 0B75A0 800B69A0 354AFFFF */  ori   $t2, (0xFCFFFFFF & 0xFFFF) # ori $t2, $t2, 0xffff
/* 0B75A4 800B69A4 AC6A0000 */  sw    $t2, ($v1)
/* 0B75A8 800B69A8 AC6B0004 */  sw    $t3, 4($v1)
/* 0B75AC 800B69AC 8C830000 */  lw    $v1, ($a0)
/* 0B75B0 800B69B0 30ED03FF */  andi  $t5, $a3, 0x3ff
/* 0B75B4 800B69B4 246C0008 */  addiu $t4, $v1, 8
/* 0B75B8 800B69B8 AC8C0000 */  sw    $t4, ($a0)
/* 0B75BC 800B69BC 8FB80010 */  lw    $t8, 0x10($sp)
/* 0B75C0 800B69C0 000D7B80 */  sll   $t7, $t5, 0xe
/* 0B75C4 800B69C4 3C01F600 */  lui   $at, 0xf600
/* 0B75C8 800B69C8 01E17025 */  or    $t6, $t7, $at
/* 0B75CC 800B69CC 30CD03FF */  andi  $t5, $a2, 0x3ff
/* 0B75D0 800B69D0 30AB03FF */  andi  $t3, $a1, 0x3ff
/* 0B75D4 800B69D4 331903FF */  andi  $t9, $t8, 0x3ff
/* 0B75D8 800B69D8 00194880 */  sll   $t1, $t9, 2
/* 0B75DC 800B69DC 000B6380 */  sll   $t4, $t3, 0xe
/* 0B75E0 800B69E0 000D7880 */  sll   $t7, $t5, 2
/* 0B75E4 800B69E4 018FC025 */  or    $t8, $t4, $t7
/* 0B75E8 800B69E8 01C95025 */  or    $t2, $t6, $t1
/* 0B75EC 800B69EC AC6A0000 */  sw    $t2, ($v1)
/* 0B75F0 800B69F0 AC780004 */  sw    $t8, 4($v1)
.L800B69F4:
/* 0B75F4 800B69F4 03E00008 */  jr    $ra
/* 0B75F8 800B69F8 00000000 */   nop   

glabel func_800B69FC
/* 0B75FC 800B69FC 28A10040 */  slti  $at, $a1, 0x40
/* 0B7600 800B6A00 10200043 */  beqz  $at, .L800B6B10
/* 0B7604 800B6A04 3C038012 */   lui   $v1, %hi(D_80127CCC) # $v1, 0x8012
/* 0B7608 800B6A08 24637CCC */  addiu $v1, %lo(D_80127CCC) # addiu $v1, $v1, 0x7ccc
/* 0B760C 800B6A0C 8C6E0000 */  lw    $t6, ($v1)
/* 0B7610 800B6A10 3C0F8012 */  lui   $t7, %hi(D_80127CB8) # $t7, 0x8012
/* 0B7614 800B6A14 11C0003C */  beqz  $t6, .L800B6B08
/* 0B7618 800B6A18 00000000 */   nop   
/* 0B761C 800B6A1C 8DEF7CB8 */  lw    $t7, %lo(D_80127CB8)($t7)
/* 0B7620 800B6A20 3C19FD70 */  lui   $t9, 0xfd70
/* 0B7624 800B6A24 11E00037 */  beqz  $t7, .L800B6B04
/* 0B7628 800B6A28 3C0C8012 */   lui   $t4, %hi(D_80127CA0) # $t4, 0x8012
/* 0B762C 800B6A2C 8C820000 */  lw    $v0, ($a0)
/* 0B7630 800B6A30 3C018000 */  lui   $at, (0x80000020 >> 16) # lui $at, 0x8000
/* 0B7634 800B6A34 24580008 */  addiu $t8, $v0, 8
/* 0B7638 800B6A38 AC980000 */  sw    $t8, ($a0)
/* 0B763C 800B6A3C AC590000 */  sw    $t9, ($v0)
/* 0B7640 800B6A40 8D8C7CA0 */  lw    $t4, %lo(D_80127CA0)($t4)
/* 0B7644 800B6A44 34210020 */  ori   $at, (0x80000020 & 0xFFFF) # ori $at, $at, 0x20
/* 0B7648 800B6A48 01816821 */  addu  $t5, $t4, $at
/* 0B764C 800B6A4C AC4D0004 */  sw    $t5, 4($v0)
/* 0B7650 800B6A50 8C820000 */  lw    $v0, ($a0)
/* 0B7654 800B6A54 3C180708 */  lui   $t8, (0x07080200 >> 16) # lui $t8, 0x708
/* 0B7658 800B6A58 244E0008 */  addiu $t6, $v0, 8
/* 0B765C 800B6A5C AC8E0000 */  sw    $t6, ($a0)
/* 0B7660 800B6A60 37180200 */  ori   $t8, (0x07080200 & 0xFFFF) # ori $t8, $t8, 0x200
/* 0B7664 800B6A64 3C0FF570 */  lui   $t7, 0xf570
/* 0B7668 800B6A68 AC4F0000 */  sw    $t7, ($v0)
/* 0B766C 800B6A6C AC580004 */  sw    $t8, 4($v0)
/* 0B7670 800B6A70 8C820000 */  lw    $v0, ($a0)
/* 0B7674 800B6A74 3C0CE600 */  lui   $t4, 0xe600
/* 0B7678 800B6A78 24590008 */  addiu $t9, $v0, 8
/* 0B767C 800B6A7C AC990000 */  sw    $t9, ($a0)
/* 0B7680 800B6A80 AC400004 */  sw    $zero, 4($v0)
/* 0B7684 800B6A84 AC4C0000 */  sw    $t4, ($v0)
/* 0B7688 800B6A88 8C820000 */  lw    $v0, ($a0)
/* 0B768C 800B6A8C 3C0F0741 */  lui   $t7, (0x0741F056 >> 16) # lui $t7, 0x741
/* 0B7690 800B6A90 244D0008 */  addiu $t5, $v0, 8
/* 0B7694 800B6A94 AC8D0000 */  sw    $t5, ($a0)
/* 0B7698 800B6A98 35EFF056 */  ori   $t7, (0x0741F056 & 0xFFFF) # ori $t7, $t7, 0xf056
/* 0B769C 800B6A9C 3C0EF300 */  lui   $t6, 0xf300
/* 0B76A0 800B6AA0 AC4E0000 */  sw    $t6, ($v0)
/* 0B76A4 800B6AA4 AC4F0004 */  sw    $t7, 4($v0)
/* 0B76A8 800B6AA8 8C820000 */  lw    $v0, ($a0)
/* 0B76AC 800B6AAC 3C19E700 */  lui   $t9, 0xe700
/* 0B76B0 800B6AB0 24580008 */  addiu $t8, $v0, 8
/* 0B76B4 800B6AB4 AC980000 */  sw    $t8, ($a0)
/* 0B76B8 800B6AB8 AC400004 */  sw    $zero, 4($v0)
/* 0B76BC 800B6ABC AC590000 */  sw    $t9, ($v0)
/* 0B76C0 800B6AC0 8C820000 */  lw    $v0, ($a0)
/* 0B76C4 800B6AC4 3C0E0008 */  lui   $t6, (0x00080200 >> 16) # lui $t6, 8
/* 0B76C8 800B6AC8 244C0008 */  addiu $t4, $v0, 8
/* 0B76CC 800B6ACC AC8C0000 */  sw    $t4, ($a0)
/* 0B76D0 800B6AD0 3C0DF568 */  lui   $t5, (0xF5683000 >> 16) # lui $t5, 0xf568
/* 0B76D4 800B6AD4 35AD3000 */  ori   $t5, (0xF5683000 & 0xFFFF) # ori $t5, $t5, 0x3000
/* 0B76D8 800B6AD8 35CE0200 */  ori   $t6, (0x00080200 & 0xFFFF) # ori $t6, $t6, 0x200
/* 0B76DC 800B6ADC AC4E0004 */  sw    $t6, 4($v0)
/* 0B76E0 800B6AE0 AC4D0000 */  sw    $t5, ($v0)
/* 0B76E4 800B6AE4 8C820000 */  lw    $v0, ($a0)
/* 0B76E8 800B6AE8 3C19002F */  lui   $t9, (0x002FC028 >> 16) # lui $t9, 0x2f
/* 0B76EC 800B6AEC 244F0008 */  addiu $t7, $v0, 8
/* 0B76F0 800B6AF0 AC8F0000 */  sw    $t7, ($a0)
/* 0B76F4 800B6AF4 3739C028 */  ori   $t9, (0x002FC028 & 0xFFFF) # ori $t9, $t9, 0xc028
/* 0B76F8 800B6AF8 3C18F200 */  lui   $t8, 0xf200
/* 0B76FC 800B6AFC AC580000 */  sw    $t8, ($v0)
/* 0B7700 800B6B00 AC590004 */  sw    $t9, 4($v0)
.L800B6B04:
/* 0B7704 800B6B04 AC600000 */  sw    $zero, ($v1)
.L800B6B08:
/* 0B7708 800B6B08 1000008A */  b     .L800B6D34
/* 0B770C 800B6B0C 24A5FFDF */   addiu $a1, $a1, -0x21
.L800B6B10:
/* 0B7710 800B6B10 28A10060 */  slti  $at, $a1, 0x60
/* 0B7714 800B6B14 10200043 */  beqz  $at, .L800B6C24
/* 0B7718 800B6B18 3C038012 */   lui   $v1, %hi(D_80127CCC) # $v1, 0x8012
/* 0B771C 800B6B1C 24637CCC */  addiu $v1, %lo(D_80127CCC) # addiu $v1, $v1, 0x7ccc
/* 0B7720 800B6B20 8C6C0000 */  lw    $t4, ($v1)
/* 0B7724 800B6B24 24060001 */  li    $a2, 1
/* 0B7728 800B6B28 10CC003C */  beq   $a2, $t4, .L800B6C1C
/* 0B772C 800B6B2C 3C0D8012 */   lui   $t5, %hi(D_80127CB8) # $t5, 0x8012
/* 0B7730 800B6B30 8DAD7CB8 */  lw    $t5, %lo(D_80127CB8)($t5)
/* 0B7734 800B6B34 3C0FFD70 */  lui   $t7, 0xfd70
/* 0B7738 800B6B38 11A00037 */  beqz  $t5, .L800B6C18
/* 0B773C 800B6B3C 3C188012 */   lui   $t8, %hi(D_80127CA4) # $t8, 0x8012
/* 0B7740 800B6B40 8C820000 */  lw    $v0, ($a0)
/* 0B7744 800B6B44 3C018000 */  lui   $at, (0x80000020 >> 16) # lui $at, 0x8000
/* 0B7748 800B6B48 244E0008 */  addiu $t6, $v0, 8
/* 0B774C 800B6B4C AC8E0000 */  sw    $t6, ($a0)
/* 0B7750 800B6B50 AC4F0000 */  sw    $t7, ($v0)
/* 0B7754 800B6B54 8F187CA4 */  lw    $t8, %lo(D_80127CA4)($t8)
/* 0B7758 800B6B58 34210020 */  ori   $at, (0x80000020 & 0xFFFF) # ori $at, $at, 0x20
/* 0B775C 800B6B5C 0301C821 */  addu  $t9, $t8, $at
/* 0B7760 800B6B60 AC590004 */  sw    $t9, 4($v0)
/* 0B7764 800B6B64 8C820000 */  lw    $v0, ($a0)
/* 0B7768 800B6B68 3C0E0708 */  lui   $t6, (0x07080200 >> 16) # lui $t6, 0x708
/* 0B776C 800B6B6C 244C0008 */  addiu $t4, $v0, 8
/* 0B7770 800B6B70 AC8C0000 */  sw    $t4, ($a0)
/* 0B7774 800B6B74 35CE0200 */  ori   $t6, (0x07080200 & 0xFFFF) # ori $t6, $t6, 0x200
/* 0B7778 800B6B78 3C0DF570 */  lui   $t5, 0xf570
/* 0B777C 800B6B7C AC4D0000 */  sw    $t5, ($v0)
/* 0B7780 800B6B80 AC4E0004 */  sw    $t6, 4($v0)
/* 0B7784 800B6B84 8C820000 */  lw    $v0, ($a0)
/* 0B7788 800B6B88 3C18E600 */  lui   $t8, 0xe600
/* 0B778C 800B6B8C 244F0008 */  addiu $t7, $v0, 8
/* 0B7790 800B6B90 AC8F0000 */  sw    $t7, ($a0)
/* 0B7794 800B6B94 AC400004 */  sw    $zero, 4($v0)
/* 0B7798 800B6B98 AC580000 */  sw    $t8, ($v0)
/* 0B779C 800B6B9C 8C820000 */  lw    $v0, ($a0)
/* 0B77A0 800B6BA0 3C0D0755 */  lui   $t5, (0x07553043 >> 16) # lui $t5, 0x755
/* 0B77A4 800B6BA4 24590008 */  addiu $t9, $v0, 8
/* 0B77A8 800B6BA8 AC990000 */  sw    $t9, ($a0)
/* 0B77AC 800B6BAC 35AD3043 */  ori   $t5, (0x07553043 & 0xFFFF) # ori $t5, $t5, 0x3043
/* 0B77B0 800B6BB0 3C0CF300 */  lui   $t4, 0xf300
/* 0B77B4 800B6BB4 AC4C0000 */  sw    $t4, ($v0)
/* 0B77B8 800B6BB8 AC4D0004 */  sw    $t5, 4($v0)
/* 0B77BC 800B6BBC 8C820000 */  lw    $v0, ($a0)
/* 0B77C0 800B6BC0 3C0FE700 */  lui   $t7, 0xe700
/* 0B77C4 800B6BC4 244E0008 */  addiu $t6, $v0, 8
/* 0B77C8 800B6BC8 AC8E0000 */  sw    $t6, ($a0)
/* 0B77CC 800B6BCC AC400004 */  sw    $zero, 4($v0)
/* 0B77D0 800B6BD0 AC4F0000 */  sw    $t7, ($v0)
/* 0B77D4 800B6BD4 8C820000 */  lw    $v0, ($a0)
/* 0B77D8 800B6BD8 3C0C0008 */  lui   $t4, (0x00080200 >> 16) # lui $t4, 8
/* 0B77DC 800B6BDC 24580008 */  addiu $t8, $v0, 8
/* 0B77E0 800B6BE0 AC980000 */  sw    $t8, ($a0)
/* 0B77E4 800B6BE4 3C19F568 */  lui   $t9, (0xF5683E00 >> 16) # lui $t9, 0xf568
/* 0B77E8 800B6BE8 37393E00 */  ori   $t9, (0xF5683E00 & 0xFFFF) # ori $t9, $t9, 0x3e00
/* 0B77EC 800B6BEC 358C0200 */  ori   $t4, (0x00080200 & 0xFFFF) # ori $t4, $t4, 0x200
/* 0B77F0 800B6BF0 AC4C0004 */  sw    $t4, 4($v0)
/* 0B77F4 800B6BF4 AC590000 */  sw    $t9, ($v0)
/* 0B77F8 800B6BF8 8C820000 */  lw    $v0, ($a0)
/* 0B77FC 800B6BFC 3C0F003D */  lui   $t7, (0x003DC028 >> 16) # lui $t7, 0x3d
/* 0B7800 800B6C00 244D0008 */  addiu $t5, $v0, 8
/* 0B7804 800B6C04 AC8D0000 */  sw    $t5, ($a0)
/* 0B7808 800B6C08 35EFC028 */  ori   $t7, (0x003DC028 & 0xFFFF) # ori $t7, $t7, 0xc028
/* 0B780C 800B6C0C 3C0EF200 */  lui   $t6, 0xf200
/* 0B7810 800B6C10 AC4E0000 */  sw    $t6, ($v0)
/* 0B7814 800B6C14 AC4F0004 */  sw    $t7, 4($v0)
.L800B6C18:
/* 0B7818 800B6C18 AC660000 */  sw    $a2, ($v1)
.L800B6C1C:
/* 0B781C 800B6C1C 10000045 */  b     .L800B6D34
/* 0B7820 800B6C20 24A5FFC0 */   addiu $a1, $a1, -0x40
.L800B6C24:
/* 0B7824 800B6C24 28A10080 */  slti  $at, $a1, 0x80
/* 0B7828 800B6C28 10200042 */  beqz  $at, .L800B6D34
/* 0B782C 800B6C2C 3C038012 */   lui   $v1, %hi(D_80127CCC) # $v1, 0x8012
/* 0B7830 800B6C30 24637CCC */  addiu $v1, %lo(D_80127CCC) # addiu $v1, $v1, 0x7ccc
/* 0B7834 800B6C34 8C780000 */  lw    $t8, ($v1)
/* 0B7838 800B6C38 24060002 */  li    $a2, 2
/* 0B783C 800B6C3C 10D8003D */  beq   $a2, $t8, .L800B6D34
/* 0B7840 800B6C40 24A5FFA0 */   addiu $a1, $a1, -0x60
/* 0B7844 800B6C44 3C198012 */  lui   $t9, %hi(D_80127CB8) # $t9, 0x8012
/* 0B7848 800B6C48 8F397CB8 */  lw    $t9, %lo(D_80127CB8)($t9)
/* 0B784C 800B6C4C 3C0DFD70 */  lui   $t5, 0xfd70
/* 0B7850 800B6C50 13200037 */  beqz  $t9, .L800B6D30
/* 0B7854 800B6C54 3C0E8012 */   lui   $t6, %hi(D_80127CA8) # $t6, 0x8012
/* 0B7858 800B6C58 8C820000 */  lw    $v0, ($a0)
/* 0B785C 800B6C5C 3C018000 */  lui   $at, (0x80000020 >> 16) # lui $at, 0x8000
/* 0B7860 800B6C60 244C0008 */  addiu $t4, $v0, 8
/* 0B7864 800B6C64 AC8C0000 */  sw    $t4, ($a0)
/* 0B7868 800B6C68 AC4D0000 */  sw    $t5, ($v0)
/* 0B786C 800B6C6C 8DCE7CA8 */  lw    $t6, %lo(D_80127CA8)($t6)
/* 0B7870 800B6C70 34210020 */  ori   $at, (0x80000020 & 0xFFFF) # ori $at, $at, 0x20
/* 0B7874 800B6C74 01C17821 */  addu  $t7, $t6, $at
/* 0B7878 800B6C78 AC4F0004 */  sw    $t7, 4($v0)
/* 0B787C 800B6C7C 8C820000 */  lw    $v0, ($a0)
/* 0B7880 800B6C80 3C0C0708 */  lui   $t4, (0x07080200 >> 16) # lui $t4, 0x708
/* 0B7884 800B6C84 24580008 */  addiu $t8, $v0, 8
/* 0B7888 800B6C88 AC980000 */  sw    $t8, ($a0)
/* 0B788C 800B6C8C 358C0200 */  ori   $t4, (0x07080200 & 0xFFFF) # ori $t4, $t4, 0x200
/* 0B7890 800B6C90 3C19F570 */  lui   $t9, 0xf570
/* 0B7894 800B6C94 AC590000 */  sw    $t9, ($v0)
/* 0B7898 800B6C98 AC4C0004 */  sw    $t4, 4($v0)
/* 0B789C 800B6C9C 8C820000 */  lw    $v0, ($a0)
/* 0B78A0 800B6CA0 3C0EE600 */  lui   $t6, 0xe600
/* 0B78A4 800B6CA4 244D0008 */  addiu $t5, $v0, 8
/* 0B78A8 800B6CA8 AC8D0000 */  sw    $t5, ($a0)
/* 0B78AC 800B6CAC AC400004 */  sw    $zero, 4($v0)
/* 0B78B0 800B6CB0 AC4E0000 */  sw    $t6, ($v0)
/* 0B78B4 800B6CB4 8C820000 */  lw    $v0, ($a0)
/* 0B78B8 800B6CB8 3C190741 */  lui   $t9, (0x0741F056 >> 16) # lui $t9, 0x741
/* 0B78BC 800B6CBC 244F0008 */  addiu $t7, $v0, 8
/* 0B78C0 800B6CC0 AC8F0000 */  sw    $t7, ($a0)
/* 0B78C4 800B6CC4 3739F056 */  ori   $t9, (0x0741F056 & 0xFFFF) # ori $t9, $t9, 0xf056
/* 0B78C8 800B6CC8 3C18F300 */  lui   $t8, 0xf300
/* 0B78CC 800B6CCC AC580000 */  sw    $t8, ($v0)
/* 0B78D0 800B6CD0 AC590004 */  sw    $t9, 4($v0)
/* 0B78D4 800B6CD4 8C820000 */  lw    $v0, ($a0)
/* 0B78D8 800B6CD8 3C0DE700 */  lui   $t5, 0xe700
/* 0B78DC 800B6CDC 244C0008 */  addiu $t4, $v0, 8
/* 0B78E0 800B6CE0 AC8C0000 */  sw    $t4, ($a0)
/* 0B78E4 800B6CE4 AC400004 */  sw    $zero, 4($v0)
/* 0B78E8 800B6CE8 AC4D0000 */  sw    $t5, ($v0)
/* 0B78EC 800B6CEC 8C820000 */  lw    $v0, ($a0)
/* 0B78F0 800B6CF0 3C180008 */  lui   $t8, (0x00080200 >> 16) # lui $t8, 8
/* 0B78F4 800B6CF4 244E0008 */  addiu $t6, $v0, 8
/* 0B78F8 800B6CF8 AC8E0000 */  sw    $t6, ($a0)
/* 0B78FC 800B6CFC 3C0FF568 */  lui   $t7, (0xF5683000 >> 16) # lui $t7, 0xf568
/* 0B7900 800B6D00 35EF3000 */  ori   $t7, (0xF5683000 & 0xFFFF) # ori $t7, $t7, 0x3000
/* 0B7904 800B6D04 37180200 */  ori   $t8, (0x00080200 & 0xFFFF) # ori $t8, $t8, 0x200
/* 0B7908 800B6D08 AC580004 */  sw    $t8, 4($v0)
/* 0B790C 800B6D0C AC4F0000 */  sw    $t7, ($v0)
/* 0B7910 800B6D10 8C820000 */  lw    $v0, ($a0)
/* 0B7914 800B6D14 3C0D002F */  lui   $t5, (0x002FC028 >> 16) # lui $t5, 0x2f
/* 0B7918 800B6D18 24590008 */  addiu $t9, $v0, 8
/* 0B791C 800B6D1C AC990000 */  sw    $t9, ($a0)
/* 0B7920 800B6D20 35ADC028 */  ori   $t5, (0x002FC028 & 0xFFFF) # ori $t5, $t5, 0xc028
/* 0B7924 800B6D24 3C0CF200 */  lui   $t4, 0xf200
/* 0B7928 800B6D28 AC4C0000 */  sw    $t4, ($v0)
/* 0B792C 800B6D2C AC4D0004 */  sw    $t5, 4($v0)
.L800B6D30:
/* 0B7930 800B6D30 AC660000 */  sw    $a2, ($v1)
.L800B6D34:
/* 0B7934 800B6D34 3C038012 */  lui   $v1, %hi(D_80127CCC) # $v1, 0x8012
/* 0B7938 800B6D38 24637CCC */  addiu $v1, %lo(D_80127CCC) # addiu $v1, $v1, 0x7ccc
/* 0B793C 800B6D3C 8C6E0000 */  lw    $t6, ($v1)
/* 0B7940 800B6D40 0005C040 */  sll   $t8, $a1, 1
/* 0B7944 800B6D44 3C0C800E */  lui   $t4, %hi(D_800E2EF4) # $t4, 0x800e
/* 0B7948 800B6D48 000E7980 */  sll   $t7, $t6, 6
/* 0B794C 800B6D4C 01F8C821 */  addu  $t9, $t7, $t8
/* 0B7950 800B6D50 258C2EF4 */  addiu $t4, %lo(D_800E2EF4) # addiu $t4, $t4, 0x2ef4
/* 0B7954 800B6D54 032C1021 */  addu  $v0, $t9, $t4
/* 0B7958 800B6D58 90460000 */  lbu   $a2, ($v0)
/* 0B795C 800B6D5C 904D0001 */  lbu   $t5, 1($v0)
/* 0B7960 800B6D60 3C0E8012 */  lui   $t6, %hi(D_80127CB8) # $t6, 0x8012
/* 0B7964 800B6D64 8DCE7CB8 */  lw    $t6, %lo(D_80127CB8)($t6)
/* 0B7968 800B6D68 01A63823 */  subu  $a3, $t5, $a2
/* 0B796C 800B6D6C 11C00036 */  beqz  $t6, .L800B6E48
/* 0B7970 800B6D70 24E70001 */   addiu $a3, $a3, 1
/* 0B7974 800B6D74 8C820000 */  lw    $v0, ($a0)
/* 0B7978 800B6D78 3C18FCFF */  lui   $t8, (0xFCFFFFFF >> 16) # lui $t8, 0xfcff
/* 0B797C 800B6D7C 244F0008 */  addiu $t7, $v0, 8
/* 0B7980 800B6D80 AC8F0000 */  sw    $t7, ($a0)
/* 0B7984 800B6D84 3C19FFFE */  lui   $t9, (0xFFFEF379 >> 16) # lui $t9, 0xfffe
/* 0B7988 800B6D88 3739F379 */  ori   $t9, (0xFFFEF379 & 0xFFFF) # ori $t9, $t9, 0xf379
/* 0B798C 800B6D8C 3718FFFF */  ori   $t8, (0xFCFFFFFF & 0xFFFF) # ori $t8, $t8, 0xffff
/* 0B7990 800B6D90 AC580000 */  sw    $t8, ($v0)
/* 0B7994 800B6D94 AC590004 */  sw    $t9, 4($v0)
/* 0B7998 800B6D98 8C820000 */  lw    $v0, ($a0)
/* 0B799C 800B6D9C 3C0A8012 */  lui   $t2, %hi(D_80127CAC) # $t2, 0x8012
/* 0B79A0 800B6DA0 244C0008 */  addiu $t4, $v0, 8
/* 0B79A4 800B6DA4 254A7CAC */  addiu $t2, %lo(D_80127CAC) # addiu $t2, $t2, 0x7cac
/* 0B79A8 800B6DA8 AC8C0000 */  sw    $t4, ($a0)
/* 0B79AC 800B6DAC 954D0000 */  lhu   $t5, ($t2)
/* 0B79B0 800B6DB0 3C0B8012 */  lui   $t3, %hi(D_80127CAE) # $t3, 0x8012
/* 0B79B4 800B6DB4 01A77021 */  addu  $t6, $t5, $a3
/* 0B79B8 800B6DB8 256B7CAE */  addiu $t3, %lo(D_80127CAE) # addiu $t3, $t3, 0x7cae
/* 0B79BC 800B6DBC 956D0000 */  lhu   $t5, ($t3)
/* 0B79C0 800B6DC0 000E7880 */  sll   $t7, $t6, 2
/* 0B79C4 800B6DC4 31F80FFF */  andi  $t8, $t7, 0xfff
/* 0B79C8 800B6DC8 0018CB00 */  sll   $t9, $t8, 0xc
/* 0B79CC 800B6DCC 25AE000A */  addiu $t6, $t5, 0xa
/* 0B79D0 800B6DD0 000E7880 */  sll   $t7, $t6, 2
/* 0B79D4 800B6DD4 3C01E400 */  lui   $at, 0xe400
/* 0B79D8 800B6DD8 03216025 */  or    $t4, $t9, $at
/* 0B79DC 800B6DDC 31F80FFF */  andi  $t8, $t7, 0xfff
/* 0B79E0 800B6DE0 0198C825 */  or    $t9, $t4, $t8
/* 0B79E4 800B6DE4 AC590000 */  sw    $t9, ($v0)
/* 0B79E8 800B6DE8 954D0000 */  lhu   $t5, ($t2)
/* 0B79EC 800B6DEC 95780000 */  lhu   $t8, ($t3)
/* 0B79F0 800B6DF0 000D7080 */  sll   $t6, $t5, 2
/* 0B79F4 800B6DF4 31CF0FFF */  andi  $t7, $t6, 0xfff
/* 0B79F8 800B6DF8 0018C880 */  sll   $t9, $t8, 2
/* 0B79FC 800B6DFC 332D0FFF */  andi  $t5, $t9, 0xfff
/* 0B7A00 800B6E00 000F6300 */  sll   $t4, $t7, 0xc
/* 0B7A04 800B6E04 018D7025 */  or    $t6, $t4, $t5
/* 0B7A08 800B6E08 AC4E0004 */  sw    $t6, 4($v0)
/* 0B7A0C 800B6E0C 8C820000 */  lw    $v0, ($a0)
/* 0B7A10 800B6E10 00066D40 */  sll   $t5, $a2, 0x15
/* 0B7A14 800B6E14 244F0008 */  addiu $t7, $v0, 8
/* 0B7A18 800B6E18 AC8F0000 */  sw    $t7, ($a0)
/* 0B7A1C 800B6E1C 3C18B300 */  lui   $t8, 0xb300
/* 0B7A20 800B6E20 AC580000 */  sw    $t8, ($v0)
/* 0B7A24 800B6E24 AC4D0004 */  sw    $t5, 4($v0)
/* 0B7A28 800B6E28 8C820000 */  lw    $v0, ($a0)
/* 0B7A2C 800B6E2C 3C180400 */  lui   $t8, (0x04000400 >> 16) # lui $t8, 0x400
/* 0B7A30 800B6E30 244E0008 */  addiu $t6, $v0, 8
/* 0B7A34 800B6E34 AC8E0000 */  sw    $t6, ($a0)
/* 0B7A38 800B6E38 37180400 */  ori   $t8, (0x04000400 & 0xFFFF) # ori $t8, $t8, 0x400
/* 0B7A3C 800B6E3C 3C0FB200 */  lui   $t7, 0xb200
/* 0B7A40 800B6E40 AC4F0000 */  sw    $t7, ($v0)
/* 0B7A44 800B6E44 AC580004 */  sw    $t8, 4($v0)
.L800B6E48:
/* 0B7A48 800B6E48 03E00008 */  jr    $ra
/* 0B7A4C 800B6E4C 00E01025 */   move  $v0, $a3

glabel func_800B6E50
/* 0B7A50 800B6E50 3C028012 */  lui   $v0, %hi(D_80127CD0) # $v0, 0x8012
/* 0B7A54 800B6E54 94427CD0 */  lhu   $v0, %lo(D_80127CD0)($v0)
/* 0B7A58 800B6E58 24180020 */  li    $t8, 32
/* 0B7A5C 800B6E5C 28410141 */  slti  $at, $v0, 0x141
/* 0B7A60 800B6E60 10200008 */  beqz  $at, .L800B6E84
/* 0B7A64 800B6E64 2459FFE0 */   addiu $t9, $v0, -0x20
/* 0B7A68 800B6E68 240E0010 */  li    $t6, 16
/* 0B7A6C 800B6E6C 3C018012 */  lui   $at, %hi(D_80127CBC) # $at, 0x8012
/* 0B7A70 800B6E70 AC2E7CBC */  sw    $t6, %lo(D_80127CBC)($at)
/* 0B7A74 800B6E74 3C018012 */  lui   $at, %hi(D_80127CC0) # $at, 0x8012
/* 0B7A78 800B6E78 244FFFF0 */  addiu $t7, $v0, -0x10
/* 0B7A7C 800B6E7C 10000005 */  b     .L800B6E94
/* 0B7A80 800B6E80 AC2F7CC0 */   sw    $t7, %lo(D_80127CC0)($at)
.L800B6E84:
/* 0B7A84 800B6E84 3C018012 */  lui   $at, %hi(D_80127CBC) # $at, 0x8012
/* 0B7A88 800B6E88 AC387CBC */  sw    $t8, %lo(D_80127CBC)($at)
/* 0B7A8C 800B6E8C 3C018012 */  lui   $at, %hi(D_80127CC0) # $at, 0x8012
/* 0B7A90 800B6E90 AC397CC0 */  sw    $t9, %lo(D_80127CC0)($at)
.L800B6E94:
/* 0B7A94 800B6E94 3C028012 */  lui   $v0, %hi(D_80127CD2) # $v0, 0x8012
/* 0B7A98 800B6E98 94427CD2 */  lhu   $v0, %lo(D_80127CD2)($v0)
/* 0B7A9C 800B6E9C 240A0020 */  li    $t2, 32
/* 0B7AA0 800B6EA0 284100F1 */  slti  $at, $v0, 0xf1
/* 0B7AA4 800B6EA4 10200008 */  beqz  $at, .L800B6EC8
/* 0B7AA8 800B6EA8 244BFFE0 */   addiu $t3, $v0, -0x20
/* 0B7AAC 800B6EAC 24080010 */  li    $t0, 16
/* 0B7AB0 800B6EB0 3C018012 */  lui   $at, %hi(D_80127CC4) # $at, 0x8012
/* 0B7AB4 800B6EB4 AC287CC4 */  sw    $t0, %lo(D_80127CC4)($at)
/* 0B7AB8 800B6EB8 3C018012 */  lui   $at, 0x8012
/* 0B7ABC 800B6EBC 2449FFF0 */  addiu $t1, $v0, -0x10
/* 0B7AC0 800B6EC0 03E00008 */  jr    $ra
/* 0B7AC4 800B6EC4 AC297CC8 */   sw    $t1, 0x7cc8($at)

.L800B6EC8:
/* 0B7AC8 800B6EC8 3C018012 */  lui   $at, %hi(D_80127CC4) # $at, 0x8012
/* 0B7ACC 800B6ECC AC2A7CC4 */  sw    $t2, %lo(D_80127CC4)($at)
/* 0B7AD0 800B6ED0 3C018012 */  lui   $at, %hi(D_80127CC8) # $at, 0x8012
/* 0B7AD4 800B6ED4 AC2B7CC8 */  sw    $t3, %lo(D_80127CC8)($at)
/* 0B7AD8 800B6ED8 03E00008 */  jr    $ra
/* 0B7ADC 800B6EDC 00000000 */   nop   

glabel func_800B6EE0
/* 0B7AE0 800B6EE0 3C0E8012 */  lui   $t6, %hi(D_80127CBC) # $t6, 0x8012
/* 0B7AE4 800B6EE4 8DCE7CBC */  lw    $t6, %lo(D_80127CBC)($t6)
/* 0B7AE8 800B6EE8 3C018012 */  lui   $at, %hi(D_80127CAC) # $at, 0x8012
/* 0B7AEC 800B6EEC 3C0F8012 */  lui   $t7, %hi(D_80127CC4) # $t7, 0x8012
/* 0B7AF0 800B6EF0 8DEF7CC4 */  lw    $t7, %lo(D_80127CC4)($t7)
/* 0B7AF4 800B6EF4 A42E7CAC */  sh    $t6, %lo(D_80127CAC)($at)
/* 0B7AF8 800B6EF8 3C018012 */  lui   $at, 0x8012
/* 0B7AFC 800B6EFC 03E00008 */  jr    $ra
/* 0B7B00 800B6F00 A42F7CAE */   sh    $t7, 0x7cae($at)

glabel func_800B6F04
/* 0B7B04 800B6F04 3C0E8012 */  lui   $t6, %hi(D_80127CBC) # $t6, 0x8012
/* 0B7B08 800B6F08 8DCE7CBC */  lw    $t6, %lo(D_80127CBC)($t6)
/* 0B7B0C 800B6F0C 3C028012 */  lui   $v0, %hi(D_80127CAE) # $v0, 0x8012
/* 0B7B10 800B6F10 3C018012 */  lui   $at, %hi(D_80127CAC) # $at, 0x8012
/* 0B7B14 800B6F14 24427CAE */  addiu $v0, %lo(D_80127CAE) # addiu $v0, $v0, 0x7cae
/* 0B7B18 800B6F18 A42E7CAC */  sh    $t6, %lo(D_80127CAC)($at)
/* 0B7B1C 800B6F1C 944F0000 */  lhu   $t7, ($v0)
/* 0B7B20 800B6F20 00000000 */  nop   
/* 0B7B24 800B6F24 25F8000B */  addiu $t8, $t7, 0xb
/* 0B7B28 800B6F28 03E00008 */  jr    $ra
/* 0B7B2C 800B6F2C A4580000 */   sh    $t8, ($v0)

/* 0B7B30 800B6F30 AFA40000 */  sw    $a0, ($sp)
/* 0B7B34 800B6F34 AFA50004 */  sw    $a1, 4($sp)
/* 0B7B38 800B6F38 03E00008 */  jr    $ra
/* 0B7B3C 800B6F3C AFA60008 */   sw    $a2, 8($sp)

glabel func_800B6F40
/* 0B7B40 800B6F40 AFA40000 */  sw    $a0, ($sp)
/* 0B7B44 800B6F44 AFA50004 */  sw    $a1, 4($sp)
/* 0B7B48 800B6F48 03E00008 */  jr    $ra
/* 0B7B4C 800B6F4C AFA60008 */   sw    $a2, 8($sp)

glabel func_800B6F50
/* 0B7B50 800B6F50 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0B7B54 800B6F54 3C0E8013 */  lui   $t6, %hi(D_801295E0) # $t6, 0x8013
/* 0B7B58 800B6F58 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B7B5C 800B6F5C 25CE95E0 */  addiu $t6, %lo(D_801295E0) # addiu $t6, $t6, -0x6a20
/* 0B7B60 800B6F60 3C048013 */  lui   $a0, %hi(D_801295E0) # $a0, 0x8013
/* 0B7B64 800B6F64 3C06800B */  lui   $a2, %hi(D_800B6FC4) # $a2, 0x800b
/* 0B7B68 800B6F68 240F00FF */  li    $t7, 255
/* 0B7B6C 800B6F6C AFAF0014 */  sw    $t7, 0x14($sp)
/* 0B7B70 800B6F70 24C66FC4 */  addiu $a2, %lo(D_800B6FC4) # addiu $a2, $a2, 0x6fc4
/* 0B7B74 800B6F74 248495E0 */  addiu $a0, %lo(D_801295E0) # addiu $a0, $a0, -0x6a20
/* 0B7B78 800B6F78 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0B7B7C 800B6F7C 00002825 */  move  $a1, $zero
/* 0B7B80 800B6F80 0C032214 */  jal   osCreateThread
/* 0B7B84 800B6F84 00003825 */   move  $a3, $zero
/* 0B7B88 800B6F88 3C048013 */  lui   $a0, %hi(D_801295E0) # $a0, 0x8013
/* 0B7B8C 800B6F8C 0C032268 */  jal   osStartThread
/* 0B7B90 800B6F90 248495E0 */   addiu $a0, %lo(D_801295E0) # addiu $a0, $a0, -0x6a20
/* 0B7B94 800B6F94 3C028013 */  lui   $v0, %hi(D_80129FB0) # $v0, 0x8013
/* 0B7B98 800B6F98 3C048013 */  lui   $a0, %hi(D_80129FBC) # $a0, 0x8013
/* 0B7B9C 800B6F9C 24849FBC */  addiu $a0, %lo(D_80129FBC) # addiu $a0, $a0, -0x6044
/* 0B7BA0 800B6FA0 24429FB0 */  addiu $v0, %lo(D_80129FB0) # addiu $v0, $v0, -0x6050
/* 0B7BA4 800B6FA4 2403FFFF */  li    $v1, -1
.L800B6FA8:
/* 0B7BA8 800B6FA8 24420004 */  addiu $v0, $v0, 4
/* 0B7BAC 800B6FAC 1444FFFE */  bne   $v0, $a0, .L800B6FA8
/* 0B7BB0 800B6FB0 AC43FFFC */   sw    $v1, -4($v0)
/* 0B7BB4 800B6FB4 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B7BB8 800B6FB8 27BD0020 */  addiu $sp, $sp, 0x20
/* 0B7BBC 800B6FBC 03E00008 */  jr    $ra
/* 0B7BC0 800B6FC0 00000000 */   nop   

glabel D_800B6FC4
/* 0B7BC4 800B6FC4 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0B7BC8 800B6FC8 AFB40028 */  sw    $s4, 0x28($sp)
/* 0B7BCC 800B6FCC 3C148013 */  lui   $s4, %hi(D_80129790) # $s4, 0x8013
/* 0B7BD0 800B6FD0 26949790 */  addiu $s4, %lo(D_80129790) # addiu $s4, $s4, -0x6870
/* 0B7BD4 800B6FD4 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0B7BD8 800B6FD8 AFB00018 */  sw    $s0, 0x18($sp)
/* 0B7BDC 800B6FDC AFA40038 */  sw    $a0, 0x38($sp)
/* 0B7BE0 800B6FE0 3C058013 */  lui   $a1, %hi(D_801297A8) # $a1, 0x8013
/* 0B7BE4 800B6FE4 AFB30024 */  sw    $s3, 0x24($sp)
/* 0B7BE8 800B6FE8 AFB20020 */  sw    $s2, 0x20($sp)
/* 0B7BEC 800B6FEC AFB1001C */  sw    $s1, 0x1c($sp)
/* 0B7BF0 800B6FF0 00008025 */  move  $s0, $zero
/* 0B7BF4 800B6FF4 24A597A8 */  addiu $a1, %lo(D_801297A8) # addiu $a1, $a1, -0x6858
/* 0B7BF8 800B6FF8 02802025 */  move  $a0, $s4
/* 0B7BFC 800B6FFC 0C032208 */  jal   osCreateMesgQueue
/* 0B7C00 800B7000 24060008 */   li    $a2, 8
/* 0B7C04 800B7004 2404000C */  li    $a0, 12
/* 0B7C08 800B7008 02802825 */  move  $a1, $s4
/* 0B7C0C 800B700C 0C0332EC */  jal   osSetEventMsg
/* 0B7C10 800B7010 24060008 */   li    $a2, 8
/* 0B7C14 800B7014 2404000A */  li    $a0, 10
/* 0B7C18 800B7018 02802825 */  move  $a1, $s4
/* 0B7C1C 800B701C 0C0332EC */  jal   osSetEventMsg
/* 0B7C20 800B7020 24060002 */   li    $a2, 2
/* 0B7C24 800B7024 3C058013 */  lui   $a1, %hi(D_801297E8) # $a1, 0x8013
/* 0B7C28 800B7028 3C068013 */  lui   $a2, %hi(D_801297C8) # $a2, 0x8013
/* 0B7C2C 800B702C 24C697C8 */  addiu $a2, %lo(D_801297C8) # addiu $a2, $a2, -0x6838
/* 0B7C30 800B7030 24A597E8 */  addiu $a1, %lo(D_801297E8) # addiu $a1, $a1, -0x6818
/* 0B7C34 800B7034 24040096 */  li    $a0, 150
/* 0B7C38 800B7038 0C031800 */  jal   func_800C6000
/* 0B7C3C 800B703C 24070008 */   li    $a3, 8
/* 0B7C40 800B7040 2413FFF7 */  li    $s3, -9
/* 0B7C44 800B7044 3C120800 */  lui   $s2, 0x800
/* 0B7C48 800B7048 27B10034 */  addiu $s1, $sp, 0x34
/* 0B7C4C 800B704C 02802025 */  move  $a0, $s4
.L800B7050:
/* 0B7C50 800B7050 02202825 */  move  $a1, $s1
/* 0B7C54 800B7054 0C0322EC */  jal   osRecvMesg
/* 0B7C58 800B7058 24060001 */   li    $a2, 1
/* 0B7C5C 800B705C 0C0270C3 */  jal   func_8009C30C
/* 0B7C60 800B7060 00000000 */   nop   
/* 0B7C64 800B7064 00527024 */  and   $t6, $v0, $s2
/* 0B7C68 800B7068 11C0FFF9 */  beqz  $t6, .L800B7050
/* 0B7C6C 800B706C 02802025 */   move  $a0, $s4
/* 0B7C70 800B7070 8FAF0034 */  lw    $t7, 0x34($sp)
/* 0B7C74 800B7074 00000000 */  nop   
/* 0B7C78 800B7078 020F8025 */  or    $s0, $s0, $t7
/* 0B7C7C 800B707C 32180008 */  andi  $t8, $s0, 8
/* 0B7C80 800B7080 17000003 */  bnez  $t8, .L800B7090
/* 0B7C84 800B7084 32190002 */   andi  $t9, $s0, 2
/* 0B7C88 800B7088 1320FFF1 */  beqz  $t9, .L800B7050
/* 0B7C8C 800B708C 02802025 */   move  $a0, $s4
.L800B7090:
/* 0B7C90 800B7090 0C02DC34 */  jal   func_800B70D0
/* 0B7C94 800B7094 02138024 */   and   $s0, $s0, $s3
/* 0B7C98 800B7098 0C02DC51 */  jal   func_800B7144
/* 0B7C9C 800B709C 00000000 */   nop   
/* 0B7CA0 800B70A0 0C02DC6C */  jal   func_800B71B0
/* 0B7CA4 800B70A4 00000000 */   nop   
/* 0B7CA8 800B70A8 1000FFE9 */  b     .L800B7050
/* 0B7CAC 800B70AC 02802025 */   move  $a0, $s4
/* 0B7CB0 800B70B0 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0B7CB4 800B70B4 8FB00018 */  lw    $s0, 0x18($sp)
/* 0B7CB8 800B70B8 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0B7CBC 800B70BC 8FB20020 */  lw    $s2, 0x20($sp)
/* 0B7CC0 800B70C0 8FB30024 */  lw    $s3, 0x24($sp)
/* 0B7CC4 800B70C4 8FB40028 */  lw    $s4, 0x28($sp)
/* 0B7CC8 800B70C8 03E00008 */  jr    $ra
/* 0B7CCC 800B70CC 27BD0038 */   addiu $sp, $sp, 0x38

glabel func_800B70D0
/* 0B7CD0 800B70D0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0B7CD4 800B70D4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B7CD8 800B70D8 0C03491C */  jal   func_800D2470
/* 0B7CDC 800B70DC 00000000 */   nop   
/* 0B7CE0 800B70E0 8C4E0004 */  lw    $t6, 4($v0)
/* 0B7CE4 800B70E4 2404FFFF */  li    $a0, -1
/* 0B7CE8 800B70E8 108E0012 */  beq   $a0, $t6, .L800B7134
/* 0B7CEC 800B70EC 00401825 */   move  $v1, $v0
/* 0B7CF0 800B70F0 8C420004 */  lw    $v0, 4($v0)
/* 0B7CF4 800B70F4 3C01FFFF */  lui   $at, (0xFFFF00FE >> 16) # lui $at, 0xffff
.L800B70F8:
/* 0B7CF8 800B70F8 14400008 */  bnez  $v0, .L800B711C
/* 0B7CFC 800B70FC 00000000 */   nop   
/* 0B7D00 800B7100 8C6F0118 */  lw    $t7, 0x118($v1)
/* 0B7D04 800B7104 342100FE */  ori   $at, (0xFFFF00FE & 0xFFFF) # ori $at, $at, 0xfe
/* 0B7D08 800B7108 01E1C024 */  and   $t8, $t7, $at
/* 0B7D0C 800B710C AC780118 */  sw    $t8, 0x118($v1)
/* 0B7D10 800B7110 37086C01 */  ori   $t0, $t8, 0x6c01
/* 0B7D14 800B7114 10000007 */  b     .L800B7134
/* 0B7D18 800B7118 AC680118 */   sw    $t0, 0x118($v1)
.L800B711C:
/* 0B7D1C 800B711C 8C63000C */  lw    $v1, 0xc($v1)
/* 0B7D20 800B7120 00000000 */  nop   
/* 0B7D24 800B7124 8C620004 */  lw    $v0, 4($v1)
/* 0B7D28 800B7128 00000000 */  nop   
/* 0B7D2C 800B712C 1482FFF2 */  bne   $a0, $v0, .L800B70F8
/* 0B7D30 800B7130 00000000 */   nop   
.L800B7134:
/* 0B7D34 800B7134 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B7D38 800B7138 27BD0018 */  addiu $sp, $sp, 0x18
/* 0B7D3C 800B713C 03E00008 */  jr    $ra
/* 0B7D40 800B7140 00000000 */   nop   

glabel func_800B7144
/* 0B7D44 800B7144 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0B7D48 800B7148 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B7D4C 800B714C AFB10018 */  sw    $s1, 0x18($sp)
/* 0B7D50 800B7150 0C03491C */  jal   func_800D2470
/* 0B7D54 800B7154 AFB00014 */   sw    $s0, 0x14($sp)
/* 0B7D58 800B7158 8C4E0004 */  lw    $t6, 4($v0)
/* 0B7D5C 800B715C 2411FFFF */  li    $s1, -1
/* 0B7D60 800B7160 122E000E */  beq   $s1, $t6, .L800B719C
/* 0B7D64 800B7164 00408025 */   move  $s0, $v0
/* 0B7D68 800B7168 01C01025 */  move  $v0, $t6
.L800B716C:
/* 0B7D6C 800B716C 18400005 */  blez  $v0, .L800B7184
/* 0B7D70 800B7170 28410080 */   slti  $at, $v0, 0x80
/* 0B7D74 800B7174 10200003 */  beqz  $at, .L800B7184
/* 0B7D78 800B7178 00000000 */   nop   
/* 0B7D7C 800B717C 0C0322BC */  jal   func_800C8AF0
/* 0B7D80 800B7180 02002025 */   move  $a0, $s0
.L800B7184:
/* 0B7D84 800B7184 8E10000C */  lw    $s0, 0xc($s0)
/* 0B7D88 800B7188 00000000 */  nop   
/* 0B7D8C 800B718C 8E020004 */  lw    $v0, 4($s0)
/* 0B7D90 800B7190 00000000 */  nop   
/* 0B7D94 800B7194 1622FFF5 */  bne   $s1, $v0, .L800B716C
/* 0B7D98 800B7198 00000000 */   nop   
.L800B719C:
/* 0B7D9C 800B719C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B7DA0 800B71A0 8FB00014 */  lw    $s0, 0x14($sp)
/* 0B7DA4 800B71A4 8FB10018 */  lw    $s1, 0x18($sp)
/* 0B7DA8 800B71A8 03E00008 */  jr    $ra
/* 0B7DAC 800B71AC 27BD0020 */   addiu $sp, $sp, 0x20

glabel func_800B71B0
/* 0B7DB0 800B71B0 27BDF7B8 */  addiu $sp, $sp, -0x848
/* 0B7DB4 800B71B4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B7DB8 800B71B8 0C03491C */  jal   func_800D2470
/* 0B7DBC 800B71BC 00000000 */   nop   
/* 0B7DC0 800B71C0 8C4E0004 */  lw    $t6, 4($v0)
/* 0B7DC4 800B71C4 2404FFFF */  li    $a0, -1
/* 0B7DC8 800B71C8 108E0014 */  beq   $a0, $t6, .L800B721C
/* 0B7DCC 800B71CC 00403825 */   move  $a3, $v0
/* 0B7DD0 800B71D0 8CE30004 */  lw    $v1, 4($a3)
/* 0B7DD4 800B71D4 00000000 */  nop   
.L800B71D8:
/* 0B7DD8 800B71D8 1860000A */  blez  $v1, .L800B7204
/* 0B7DDC 800B71DC 28610080 */   slti  $at, $v1, 0x80
/* 0B7DE0 800B71E0 10200008 */  beqz  $at, .L800B7204
/* 0B7DE4 800B71E4 00000000 */   nop   
/* 0B7DE8 800B71E8 94E30012 */  lhu   $v1, 0x12($a3)
/* 0B7DEC 800B71EC 00000000 */  nop   
/* 0B7DF0 800B71F0 306F0002 */  andi  $t7, $v1, 2
/* 0B7DF4 800B71F4 15E00009 */  bnez  $t7, .L800B721C
/* 0B7DF8 800B71F8 30780001 */   andi  $t8, $v1, 1
/* 0B7DFC 800B71FC 17000007 */  bnez  $t8, .L800B721C
/* 0B7E00 800B7200 00000000 */   nop   
.L800B7204:
/* 0B7E04 800B7204 8CE7000C */  lw    $a3, 0xc($a3)
/* 0B7E08 800B7208 00000000 */  nop   
/* 0B7E0C 800B720C 8CE30004 */  lw    $v1, 4($a3)
/* 0B7E10 800B7210 00000000 */  nop   
/* 0B7E14 800B7214 1483FFF0 */  bne   $a0, $v1, .L800B71D8
/* 0B7E18 800B7218 00000000 */   nop   
.L800B721C:
/* 0B7E1C 800B721C 8CF90004 */  lw    $t9, 4($a3)
/* 0B7E20 800B7220 00000000 */  nop   
/* 0B7E24 800B7224 10990081 */  beq   $a0, $t9, .L800B742C
/* 0B7E28 800B7228 00000000 */   nop   
/* 0B7E2C 800B722C 3C028013 */  lui   $v0, %hi(D_80129FB0) # $v0, 0x8013
/* 0B7E30 800B7230 24429FB0 */  addiu $v0, %lo(D_80129FB0) # addiu $v0, $v0, -0x6050
/* 0B7E34 800B7234 8C480000 */  lw    $t0, ($v0)
/* 0B7E38 800B7238 00E02025 */  move  $a0, $a3
/* 0B7E3C 800B723C 44882000 */  mtc1  $t0, $f4
/* 0B7E40 800B7240 27A50044 */  addiu $a1, $sp, 0x44
/* 0B7E44 800B7244 468021A0 */  cvt.s.w $f6, $f4
/* 0B7E48 800B7248 240601B0 */  li    $a2, 432
/* 0B7E4C 800B724C E4E60130 */  swc1  $f6, 0x130($a3)
/* 0B7E50 800B7250 8C490004 */  lw    $t1, 4($v0)
/* 0B7E54 800B7254 00000000 */  nop   
/* 0B7E58 800B7258 44894000 */  mtc1  $t1, $f8
/* 0B7E5C 800B725C 00000000 */  nop   
/* 0B7E60 800B7260 468042A0 */  cvt.s.w $f10, $f8
/* 0B7E64 800B7264 E4EA0134 */  swc1  $f10, 0x134($a3)
/* 0B7E68 800B7268 8C4A0008 */  lw    $t2, 8($v0)
/* 0B7E6C 800B726C 00000000 */  nop   
/* 0B7E70 800B7270 448A8000 */  mtc1  $t2, $f16
/* 0B7E74 800B7274 00000000 */  nop   
/* 0B7E78 800B7278 468084A0 */  cvt.s.w $f18, $f16
/* 0B7E7C 800B727C E4F20138 */  swc1  $f18, 0x138($a3)
/* 0B7E80 800B7280 0C032768 */  jal   bcopy
/* 0B7E84 800B7284 AFA70844 */   sw    $a3, 0x844($sp)
/* 0B7E88 800B7288 8FA70844 */  lw    $a3, 0x844($sp)
/* 0B7E8C 800B728C 27A50244 */  addiu $a1, $sp, 0x244
/* 0B7E90 800B7290 8CE400F4 */  lw    $a0, 0xf4($a3)
/* 0B7E94 800B7294 0C032768 */  jal   bcopy
/* 0B7E98 800B7298 24060200 */   li    $a2, 512
/* 0B7E9C 800B729C 27A40038 */  addiu $a0, $sp, 0x38
/* 0B7EA0 800B72A0 0C009165 */  jal   func_80024594
/* 0B7EA4 800B72A4 27A50034 */   addiu $a1, $sp, 0x34
/* 0B7EA8 800B72A8 8FAB0034 */  lw    $t3, 0x34($sp)
/* 0B7EAC 800B72AC 00002825 */  move  $a1, $zero
/* 0B7EB0 800B72B0 19600054 */  blez  $t3, .L800B7404
/* 0B7EB4 800B72B4 3C07800F */   lui   $a3, %hi(D_800E8EE4) # $a3, 0x800f
/* 0B7EB8 800B72B8 31660003 */  andi  $a2, $t3, 3
/* 0B7EBC 800B72BC 10C00018 */  beqz  $a2, .L800B7320
/* 0B7EC0 800B72C0 00C01825 */   move  $v1, $a2
/* 0B7EC4 800B72C4 00007040 */  sll   $t6, $zero, 1
/* 0B7EC8 800B72C8 27AF0444 */  addiu $t7, $sp, 0x444
/* 0B7ECC 800B72CC 01CF2021 */  addu  $a0, $t6, $t7
.L800B72D0:
/* 0B7ED0 800B72D0 8FB80038 */  lw    $t8, 0x38($sp)
/* 0B7ED4 800B72D4 24A50001 */  addiu $a1, $a1, 1
/* 0B7ED8 800B72D8 0018C840 */  sll   $t9, $t8, 1
/* 0B7EDC 800B72DC 00594021 */  addu  $t0, $v0, $t9
/* 0B7EE0 800B72E0 85090000 */  lh    $t1, ($t0)
/* 0B7EE4 800B72E4 00000000 */  nop   
/* 0B7EE8 800B72E8 A4890000 */  sh    $t1, ($a0)
/* 0B7EEC 800B72EC 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0B7EF0 800B72F0 8FAD0034 */  lw    $t5, 0x34($sp)
/* 0B7EF4 800B72F4 254CFFFF */  addiu $t4, $t2, -1
/* 0B7EF8 800B72F8 05810003 */  bgez  $t4, .L800B7308
/* 0B7EFC 800B72FC AFAC0038 */   sw    $t4, 0x38($sp)
/* 0B7F00 800B7300 018D3021 */  addu  $a2, $t4, $t5
/* 0B7F04 800B7304 AFA60038 */  sw    $a2, 0x38($sp)
.L800B7308:
/* 0B7F08 800B7308 8FA60038 */  lw    $a2, 0x38($sp)
/* 0B7F0C 800B730C 1465FFF0 */  bne   $v1, $a1, .L800B72D0
/* 0B7F10 800B7310 24840002 */   addiu $a0, $a0, 2
/* 0B7F14 800B7314 8FAB0034 */  lw    $t3, 0x34($sp)
/* 0B7F18 800B7318 AFA60038 */  sw    $a2, 0x38($sp)
/* 0B7F1C 800B731C 10AB0039 */  beq   $a1, $t3, .L800B7404
.L800B7320:
/* 0B7F20 800B7320 00057040 */   sll   $t6, $a1, 1
/* 0B7F24 800B7324 27AF0444 */  addiu $t7, $sp, 0x444
/* 0B7F28 800B7328 01CF2021 */  addu  $a0, $t6, $t7
.L800B732C:
/* 0B7F2C 800B732C 8FB80038 */  lw    $t8, 0x38($sp)
/* 0B7F30 800B7330 00000000 */  nop   
/* 0B7F34 800B7334 0018C840 */  sll   $t9, $t8, 1
/* 0B7F38 800B7338 00591821 */  addu  $v1, $v0, $t9
/* 0B7F3C 800B733C 84680000 */  lh    $t0, ($v1)
/* 0B7F40 800B7340 2463FFFE */  addiu $v1, $v1, -2
/* 0B7F44 800B7344 A4880000 */  sh    $t0, ($a0)
/* 0B7F48 800B7348 8FA90038 */  lw    $t1, 0x38($sp)
/* 0B7F4C 800B734C 8FAC0034 */  lw    $t4, 0x34($sp)
/* 0B7F50 800B7350 252AFFFF */  addiu $t2, $t1, -1
/* 0B7F54 800B7354 05410005 */  bgez  $t2, .L800B736C
/* 0B7F58 800B7358 AFAA0038 */   sw    $t2, 0x38($sp)
/* 0B7F5C 800B735C 014C3021 */  addu  $a2, $t2, $t4
/* 0B7F60 800B7360 00066840 */  sll   $t5, $a2, 1
/* 0B7F64 800B7364 004D1821 */  addu  $v1, $v0, $t5
/* 0B7F68 800B7368 AFA60038 */  sw    $a2, 0x38($sp)
.L800B736C:
/* 0B7F6C 800B736C 846B0000 */  lh    $t3, ($v1)
/* 0B7F70 800B7370 2463FFFE */  addiu $v1, $v1, -2
/* 0B7F74 800B7374 A48B0002 */  sh    $t3, 2($a0)
/* 0B7F78 800B7378 8FAE0038 */  lw    $t6, 0x38($sp)
/* 0B7F7C 800B737C 8FB80034 */  lw    $t8, 0x34($sp)
/* 0B7F80 800B7380 25CFFFFF */  addiu $t7, $t6, -1
/* 0B7F84 800B7384 05E10005 */  bgez  $t7, .L800B739C
/* 0B7F88 800B7388 AFAF0038 */   sw    $t7, 0x38($sp)
/* 0B7F8C 800B738C 01F83021 */  addu  $a2, $t7, $t8
/* 0B7F90 800B7390 0006C840 */  sll   $t9, $a2, 1
/* 0B7F94 800B7394 00591821 */  addu  $v1, $v0, $t9
/* 0B7F98 800B7398 AFA60038 */  sw    $a2, 0x38($sp)
.L800B739C:
/* 0B7F9C 800B739C 84680000 */  lh    $t0, ($v1)
/* 0B7FA0 800B73A0 2463FFFE */  addiu $v1, $v1, -2
/* 0B7FA4 800B73A4 A4880004 */  sh    $t0, 4($a0)
/* 0B7FA8 800B73A8 8FA90038 */  lw    $t1, 0x38($sp)
/* 0B7FAC 800B73AC 8FAC0034 */  lw    $t4, 0x34($sp)
/* 0B7FB0 800B73B0 252AFFFF */  addiu $t2, $t1, -1
/* 0B7FB4 800B73B4 05410005 */  bgez  $t2, .L800B73CC
/* 0B7FB8 800B73B8 AFAA0038 */   sw    $t2, 0x38($sp)
/* 0B7FBC 800B73BC 014C3021 */  addu  $a2, $t2, $t4
/* 0B7FC0 800B73C0 00066840 */  sll   $t5, $a2, 1
/* 0B7FC4 800B73C4 004D1821 */  addu  $v1, $v0, $t5
/* 0B7FC8 800B73C8 AFA60038 */  sw    $a2, 0x38($sp)
.L800B73CC:
/* 0B7FCC 800B73CC 846B0000 */  lh    $t3, ($v1)
/* 0B7FD0 800B73D0 00000000 */  nop   
/* 0B7FD4 800B73D4 A48B0006 */  sh    $t3, 6($a0)
/* 0B7FD8 800B73D8 8FAE0038 */  lw    $t6, 0x38($sp)
/* 0B7FDC 800B73DC 8FB80034 */  lw    $t8, 0x34($sp)
/* 0B7FE0 800B73E0 25CFFFFF */  addiu $t7, $t6, -1
/* 0B7FE4 800B73E4 05E10003 */  bgez  $t7, .L800B73F4
/* 0B7FE8 800B73E8 AFAF0038 */   sw    $t7, 0x38($sp)
/* 0B7FEC 800B73EC 01F83021 */  addu  $a2, $t7, $t8
/* 0B7FF0 800B73F0 AFA60038 */  sw    $a2, 0x38($sp)
.L800B73F4:
/* 0B7FF4 800B73F4 8FB90034 */  lw    $t9, 0x34($sp)
/* 0B7FF8 800B73F8 24A50004 */  addiu $a1, $a1, 4
/* 0B7FFC 800B73FC 14B9FFCB */  bne   $a1, $t9, .L800B732C
/* 0B8000 800B7400 24840008 */   addiu $a0, $a0, 8
.L800B7404:
/* 0B8004 800B7404 3C06800F */  lui   $a2, %hi(D_800E8EDC) # $a2, 0x800f
/* 0B8008 800B7408 27A80044 */  addiu $t0, $sp, 0x44
/* 0B800C 800B740C 24090800 */  li    $t1, 2048
/* 0B8010 800B7410 AFA90014 */  sw    $t1, 0x14($sp)
/* 0B8014 800B7414 AFA80010 */  sw    $t0, 0x10($sp)
/* 0B8018 800B7418 24C68EDC */  addiu $a2, %lo(D_800E8EDC) # addiu $a2, $a2, -0x7124
/* 0B801C 800B741C 00002025 */  move  $a0, $zero
/* 0B8020 800B7420 2405FFFF */  li    $a1, -1
/* 0B8024 800B7424 0C01D9B5 */  jal   func_800766D4
/* 0B8028 800B7428 24E78EE4 */   addiu $a3, %lo(D_800E8EE4) # addiu $a3, $a3, -0x711c
.L800B742C:
/* 0B802C 800B742C 1000FFFF */  b     .L800B742C
/* 0B8030 800B7430 00000000 */   nop   
/* 0B8034 800B7434 00000000 */  nop   
/* 0B8038 800B7438 00000000 */  nop   
/* 0B803C 800B743C 00000000 */  nop   
/* 0B8040 800B7440 00000000 */  nop   
/* 0B8044 800B7444 00000000 */  nop   
/* 0B8048 800B7448 00000000 */  nop   
/* 0B804C 800B744C 00000000 */  nop   
/* 0B8050 800B7450 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B8054 800B7454 27BD0848 */  addiu $sp, $sp, 0x848
/* 0B8058 800B7458 03E00008 */  jr    $ra
/* 0B805C 800B745C 00000000 */   nop   

glabel func_800B7460
/* 0B8060 800B7460 27BDF610 */  addiu $sp, $sp, -0x9f0
/* 0B8064 800B7464 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B8068 800B7468 AFA409F0 */  sw    $a0, 0x9f0($sp)
/* 0B806C 800B746C AFA509F4 */  sw    $a1, 0x9f4($sp)
/* 0B8070 800B7470 0C0270C3 */  jal   func_8009C30C
/* 0B8074 800B7474 AFA609F8 */   sw    $a2, 0x9f8($sp)
/* 0B8078 800B7478 00027100 */  sll   $t6, $v0, 4
/* 0B807C 800B747C 05C1008A */  bgez  $t6, .L800B76A8
/* 0B8080 800B7480 27A40840 */   addiu $a0, $sp, 0x840
/* 0B8084 800B7484 0C034138 */  jal   func_800D04E0
/* 0B8088 800B7488 240501B0 */   li    $a1, 432
/* 0B808C 800B748C 3C028013 */  lui   $v0, %hi(D_80129FB0) # $v0, 0x8013
/* 0B8090 800B7490 24429FB0 */  addiu $v0, %lo(D_80129FB0) # addiu $v0, $v0, -0x6050
/* 0B8094 800B7494 8C580000 */  lw    $t8, ($v0)
/* 0B8098 800B7498 8C590004 */  lw    $t9, 4($v0)
/* 0B809C 800B749C 8C480008 */  lw    $t0, 8($v0)
/* 0B80A0 800B74A0 44982000 */  mtc1  $t8, $f4
/* 0B80A4 800B74A4 44994000 */  mtc1  $t9, $f8
/* 0B80A8 800B74A8 44888000 */  mtc1  $t0, $f16
/* 0B80AC 800B74AC 8FA909F4 */  lw    $t1, 0x9f4($sp)
/* 0B80B0 800B74B0 468021A0 */  cvt.s.w $f6, $f4
/* 0B80B4 800B74B4 8FAF09F0 */  lw    $t7, 0x9f0($sp)
/* 0B80B8 800B74B8 8FAC09F8 */  lw    $t4, 0x9f8($sp)
/* 0B80BC 800B74BC 468042A0 */  cvt.s.w $f10, $f8
/* 0B80C0 800B74C0 240E0000 */  li    $t6, 0
/* 0B80C4 800B74C4 240DFFFF */  li    $t5, -1
/* 0B80C8 800B74C8 468084A0 */  cvt.s.w $f18, $f16
/* 0B80CC 800B74CC 000957C3 */  sra   $t2, $t1, 0x1f
/* 0B80D0 800B74D0 AFAA0878 */  sw    $t2, 0x878($sp)
/* 0B80D4 800B74D4 AFAE0880 */  sw    $t6, 0x880($sp)
/* 0B80D8 800B74D8 AFAD0960 */  sw    $t5, 0x960($sp)
/* 0B80DC 800B74DC E7A60970 */  swc1  $f6, 0x970($sp)
/* 0B80E0 800B74E0 E7AA0974 */  swc1  $f10, 0x974($sp)
/* 0B80E4 800B74E4 E7B20978 */  swc1  $f18, 0x978($sp)
/* 0B80E8 800B74E8 27A40840 */  addiu $a0, $sp, 0x840
/* 0B80EC 800B74EC 27A50040 */  addiu $a1, $sp, 0x40
/* 0B80F0 800B74F0 240601B0 */  li    $a2, 432
/* 0B80F4 800B74F4 AFA9087C */  sw    $t1, 0x87c($sp)
/* 0B80F8 800B74F8 AFAF095C */  sw    $t7, 0x95c($sp)
/* 0B80FC 800B74FC 0C032768 */  jal   bcopy
/* 0B8100 800B7500 AFAC0884 */   sw    $t4, 0x884($sp)
/* 0B8104 800B7504 27A40240 */  addiu $a0, $sp, 0x240
/* 0B8108 800B7508 0C034138 */  jal   func_800D04E0
/* 0B810C 800B750C 24050200 */   li    $a1, 512
/* 0B8110 800B7510 27A40038 */  addiu $a0, $sp, 0x38
/* 0B8114 800B7514 0C009165 */  jal   func_80024594
/* 0B8118 800B7518 27A509F4 */   addiu $a1, $sp, 0x9f4
/* 0B811C 800B751C 8FA909F4 */  lw    $t1, 0x9f4($sp)
/* 0B8120 800B7520 00002825 */  move  $a1, $zero
/* 0B8124 800B7524 19200054 */  blez  $t1, .L800B7678
/* 0B8128 800B7528 3C07800F */   lui   $a3, %hi(D_800E8EF0) # $a3, 0x800f
/* 0B812C 800B752C 31260003 */  andi  $a2, $t1, 3
/* 0B8130 800B7530 10C00018 */  beqz  $a2, .L800B7594
/* 0B8134 800B7534 00C01825 */   move  $v1, $a2
/* 0B8138 800B7538 00005040 */  sll   $t2, $zero, 1
/* 0B813C 800B753C 27AB0440 */  addiu $t3, $sp, 0x440
/* 0B8140 800B7540 014B2021 */  addu  $a0, $t2, $t3
.L800B7544:
/* 0B8144 800B7544 8FAC0038 */  lw    $t4, 0x38($sp)
/* 0B8148 800B7548 24A50001 */  addiu $a1, $a1, 1
/* 0B814C 800B754C 000C7040 */  sll   $t6, $t4, 1
/* 0B8150 800B7550 004E7821 */  addu  $t7, $v0, $t6
/* 0B8154 800B7554 85ED0000 */  lh    $t5, ($t7)
/* 0B8158 800B7558 00000000 */  nop   
/* 0B815C 800B755C A48D0000 */  sh    $t5, ($a0)
/* 0B8160 800B7560 8FB80038 */  lw    $t8, 0x38($sp)
/* 0B8164 800B7564 8FA809F4 */  lw    $t0, 0x9f4($sp)
/* 0B8168 800B7568 2719FFFF */  addiu $t9, $t8, -1
/* 0B816C 800B756C 07210003 */  bgez  $t9, .L800B757C
/* 0B8170 800B7570 AFB90038 */   sw    $t9, 0x38($sp)
/* 0B8174 800B7574 03283021 */  addu  $a2, $t9, $t0
/* 0B8178 800B7578 AFA60038 */  sw    $a2, 0x38($sp)
.L800B757C:
/* 0B817C 800B757C 8FA60038 */  lw    $a2, 0x38($sp)
/* 0B8180 800B7580 1465FFF0 */  bne   $v1, $a1, .L800B7544
/* 0B8184 800B7584 24840002 */   addiu $a0, $a0, 2
/* 0B8188 800B7588 8FA909F4 */  lw    $t1, 0x9f4($sp)
/* 0B818C 800B758C AFA60038 */  sw    $a2, 0x38($sp)
/* 0B8190 800B7590 10A90039 */  beq   $a1, $t1, .L800B7678
.L800B7594:
/* 0B8194 800B7594 00055040 */   sll   $t2, $a1, 1
/* 0B8198 800B7598 27AB0440 */  addiu $t3, $sp, 0x440
/* 0B819C 800B759C 014B2021 */  addu  $a0, $t2, $t3
.L800B75A0:
/* 0B81A0 800B75A0 8FAC0038 */  lw    $t4, 0x38($sp)
/* 0B81A4 800B75A4 00000000 */  nop   
/* 0B81A8 800B75A8 000C7040 */  sll   $t6, $t4, 1
/* 0B81AC 800B75AC 004E1821 */  addu  $v1, $v0, $t6
/* 0B81B0 800B75B0 846F0000 */  lh    $t7, ($v1)
/* 0B81B4 800B75B4 2463FFFE */  addiu $v1, $v1, -2
/* 0B81B8 800B75B8 A48F0000 */  sh    $t7, ($a0)
/* 0B81BC 800B75BC 8FAD0038 */  lw    $t5, 0x38($sp)
/* 0B81C0 800B75C0 8FB909F4 */  lw    $t9, 0x9f4($sp)
/* 0B81C4 800B75C4 25B8FFFF */  addiu $t8, $t5, -1
/* 0B81C8 800B75C8 07010005 */  bgez  $t8, .L800B75E0
/* 0B81CC 800B75CC AFB80038 */   sw    $t8, 0x38($sp)
/* 0B81D0 800B75D0 03193021 */  addu  $a2, $t8, $t9
/* 0B81D4 800B75D4 00064040 */  sll   $t0, $a2, 1
/* 0B81D8 800B75D8 00481821 */  addu  $v1, $v0, $t0
/* 0B81DC 800B75DC AFA60038 */  sw    $a2, 0x38($sp)
.L800B75E0:
/* 0B81E0 800B75E0 84690000 */  lh    $t1, ($v1)
/* 0B81E4 800B75E4 2463FFFE */  addiu $v1, $v1, -2
/* 0B81E8 800B75E8 A4890002 */  sh    $t1, 2($a0)
/* 0B81EC 800B75EC 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0B81F0 800B75F0 8FAC09F4 */  lw    $t4, 0x9f4($sp)
/* 0B81F4 800B75F4 254BFFFF */  addiu $t3, $t2, -1
/* 0B81F8 800B75F8 05610005 */  bgez  $t3, .L800B7610
/* 0B81FC 800B75FC AFAB0038 */   sw    $t3, 0x38($sp)
/* 0B8200 800B7600 016C3021 */  addu  $a2, $t3, $t4
/* 0B8204 800B7604 00067040 */  sll   $t6, $a2, 1
/* 0B8208 800B7608 004E1821 */  addu  $v1, $v0, $t6
/* 0B820C 800B760C AFA60038 */  sw    $a2, 0x38($sp)
.L800B7610:
/* 0B8210 800B7610 846F0000 */  lh    $t7, ($v1)
/* 0B8214 800B7614 2463FFFE */  addiu $v1, $v1, -2
/* 0B8218 800B7618 A48F0004 */  sh    $t7, 4($a0)
/* 0B821C 800B761C 8FAD0038 */  lw    $t5, 0x38($sp)
/* 0B8220 800B7620 8FB909F4 */  lw    $t9, 0x9f4($sp)
/* 0B8224 800B7624 25B8FFFF */  addiu $t8, $t5, -1
/* 0B8228 800B7628 07010005 */  bgez  $t8, .L800B7640
/* 0B822C 800B762C AFB80038 */   sw    $t8, 0x38($sp)
/* 0B8230 800B7630 03193021 */  addu  $a2, $t8, $t9
/* 0B8234 800B7634 00064040 */  sll   $t0, $a2, 1
/* 0B8238 800B7638 00481821 */  addu  $v1, $v0, $t0
/* 0B823C 800B763C AFA60038 */  sw    $a2, 0x38($sp)
.L800B7640:
/* 0B8240 800B7640 84690000 */  lh    $t1, ($v1)
/* 0B8244 800B7644 00000000 */  nop   
/* 0B8248 800B7648 A4890006 */  sh    $t1, 6($a0)
/* 0B824C 800B764C 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0B8250 800B7650 8FAC09F4 */  lw    $t4, 0x9f4($sp)
/* 0B8254 800B7654 254BFFFF */  addiu $t3, $t2, -1
/* 0B8258 800B7658 05610003 */  bgez  $t3, .L800B7668
/* 0B825C 800B765C AFAB0038 */   sw    $t3, 0x38($sp)
/* 0B8260 800B7660 016C3021 */  addu  $a2, $t3, $t4
/* 0B8264 800B7664 AFA60038 */  sw    $a2, 0x38($sp)
.L800B7668:
/* 0B8268 800B7668 8FAE09F4 */  lw    $t6, 0x9f4($sp)
/* 0B826C 800B766C 24A50004 */  addiu $a1, $a1, 4
/* 0B8270 800B7670 14AEFFCB */  bne   $a1, $t6, .L800B75A0
/* 0B8274 800B7674 24840008 */   addiu $a0, $a0, 8
.L800B7678:
/* 0B8278 800B7678 3C06800F */  lui   $a2, %hi(D_800E8EE8) # $a2, 0x800f
/* 0B827C 800B767C 27AF0040 */  addiu $t7, $sp, 0x40
/* 0B8280 800B7680 240D0800 */  li    $t5, 2048
/* 0B8284 800B7684 AFAD0014 */  sw    $t5, 0x14($sp)
/* 0B8288 800B7688 AFAF0010 */  sw    $t7, 0x10($sp)
/* 0B828C 800B768C 24C68EE8 */  addiu $a2, %lo(D_800E8EE8) # addiu $a2, $a2, -0x7118
/* 0B8290 800B7690 00002025 */  move  $a0, $zero
/* 0B8294 800B7694 2405FFFF */  li    $a1, -1
/* 0B8298 800B7698 0C01D9B5 */  jal   func_800766D4
/* 0B829C 800B769C 24E78EF0 */   addiu $a3, %lo(D_800E8EF0) # addiu $a3, $a3, -0x7110
.L800B76A0:
/* 0B82A0 800B76A0 1000FFFF */  b     .L800B76A0
/* 0B82A4 800B76A4 00000000 */   nop   
.L800B76A8:
/* 0B82A8 800B76A8 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B82AC 800B76AC 27BD09F0 */  addiu $sp, $sp, 0x9f0
/* 0B82B0 800B76B0 03E00008 */  jr    $ra
/* 0B82B4 800B76B4 00000000 */   nop   

glabel func_800B76B8
/* 0B82B8 800B76B8 04800006 */  bltz  $a0, .L800B76D4
/* 0B82BC 800B76BC 28810003 */   slti  $at, $a0, 3
/* 0B82C0 800B76C0 10200004 */  beqz  $at, .L800B76D4
/* 0B82C4 800B76C4 00047080 */   sll   $t6, $a0, 2
/* 0B82C8 800B76C8 3C018013 */  lui   $at, 0x8013
/* 0B82CC 800B76CC 002E0821 */  addu  $at, $at, $t6
/* 0B82D0 800B76D0 AC259FB0 */  sw    $a1, -0x6050($at)
.L800B76D4:
/* 0B82D4 800B76D4 03E00008 */  jr    $ra
/* 0B82D8 800B76D8 00000000 */   nop   

glabel func_800B76DC
/* 0B82DC 800B76DC 3C02800E */  lui   $v0, %hi(D_800E3020) # $v0, 0x800e
/* 0B82E0 800B76E0 24423020 */  addiu $v0, %lo(D_800E3020) # addiu $v0, $v0, 0x3020
/* 0B82E4 800B76E4 8C430000 */  lw    $v1, ($v0)
/* 0B82E8 800B76E8 27BDF7D8 */  addiu $sp, $sp, -0x828
/* 0B82EC 800B76EC 2401FFFF */  li    $at, -1
/* 0B82F0 800B76F0 10610003 */  beq   $v1, $at, .L800B7700
/* 0B82F4 800B76F4 AFBF0014 */   sw    $ra, 0x14($sp)
/* 0B82F8 800B76F8 10000032 */  b     .L800B77C4
/* 0B82FC 800B76FC 00601025 */   move  $v0, $v1
.L800B7700:
/* 0B8300 800B7700 AC400000 */  sw    $zero, ($v0)
/* 0B8304 800B7704 0C01D637 */  jal   func_800758DC
/* 0B8308 800B7708 00002025 */   move  $a0, $zero
/* 0B830C 800B770C 14400020 */  bnez  $v0, .L800B7790
/* 0B8310 800B7710 00002025 */   move  $a0, $zero
/* 0B8314 800B7714 3C05800F */  lui   $a1, %hi(D_800E8EF4) # $a1, 0x800f
/* 0B8318 800B7718 3C06800F */  lui   $a2, %hi(D_800E8EFC) # $a2, 0x800f
/* 0B831C 800B771C 24C68EFC */  addiu $a2, %lo(D_800E8EFC) # addiu $a2, $a2, -0x7104
/* 0B8320 800B7720 24A58EF4 */  addiu $a1, %lo(D_800E8EF4) # addiu $a1, $a1, -0x710c
/* 0B8324 800B7724 0C01D93A */  jal   func_800764E8
/* 0B8328 800B7728 27A70824 */   addiu $a3, $sp, 0x824
/* 0B832C 800B772C 14400018 */  bnez  $v0, .L800B7790
/* 0B8330 800B7730 00002025 */   move  $a0, $zero
/* 0B8334 800B7734 8FA50824 */  lw    $a1, 0x824($sp)
/* 0B8338 800B7738 27A60020 */  addiu $a2, $sp, 0x20
/* 0B833C 800B773C 0C01D984 */  jal   func_80076610
/* 0B8340 800B7740 24070800 */   li    $a3, 2048
/* 0B8344 800B7744 14400012 */  bnez  $v0, .L800B7790
/* 0B8348 800B7748 27A40020 */   addiu $a0, $sp, 0x20
/* 0B834C 800B774C 3C058013 */  lui   $a1, %hi(D_80129800) # $a1, 0x8013
/* 0B8350 800B7750 24A59800 */  addiu $a1, %lo(D_80129800) # addiu $a1, $a1, -0x6800
/* 0B8354 800B7754 0C032768 */  jal   bcopy
/* 0B8358 800B7758 240601B0 */   li    $a2, 432
/* 0B835C 800B775C 3C058013 */  lui   $a1, %hi(D_801299B0) # $a1, 0x8013
/* 0B8360 800B7760 24A599B0 */  addiu $a1, %lo(D_801299B0) # addiu $a1, $a1, -0x6650
/* 0B8364 800B7764 27A40220 */  addiu $a0, $sp, 0x220
/* 0B8368 800B7768 0C032768 */  jal   bcopy
/* 0B836C 800B776C 24060200 */   li    $a2, 512
/* 0B8370 800B7770 3C058013 */  lui   $a1, %hi(D_80129BB0) # $a1, 0x8013
/* 0B8374 800B7774 24A59BB0 */  addiu $a1, %lo(D_80129BB0) # addiu $a1, $a1, -0x6450
/* 0B8378 800B7778 27A40420 */  addiu $a0, $sp, 0x420
/* 0B837C 800B777C 0C032768 */  jal   bcopy
/* 0B8380 800B7780 24060400 */   li    $a2, 1024
/* 0B8384 800B7784 240E0001 */  li    $t6, 1
/* 0B8388 800B7788 3C01800E */  lui   $at, %hi(D_800E3020) # $at, 0x800e
/* 0B838C 800B778C AC2E3020 */  sw    $t6, %lo(D_800E3020)($at)
.L800B7790:
/* 0B8390 800B7790 0C01D6BB */  jal   func_80075AEC
/* 0B8394 800B7794 00002025 */   move  $a0, $zero
/* 0B8398 800B7798 3C03800E */  lui   $v1, %hi(D_800E3020) # $v1, 0x800e
/* 0B839C 800B779C 8C633020 */  lw    $v1, %lo(D_800E3020)($v1)
/* 0B83A0 800B77A0 8FA50824 */  lw    $a1, 0x824($sp)
/* 0B83A4 800B77A4 10600007 */  beqz  $v1, .L800B77C4
/* 0B83A8 800B77A8 00601025 */   move  $v0, $v1
/* 0B83AC 800B77AC 0C01D8B2 */  jal   func_800762C8
/* 0B83B0 800B77B0 00002025 */   move  $a0, $zero
/* 0B83B4 800B77B4 3C03800E */  lui   $v1, %hi(D_800E3020) # $v1, 0x800e
/* 0B83B8 800B77B8 8C633020 */  lw    $v1, %lo(D_800E3020)($v1)
/* 0B83BC 800B77BC 00000000 */  nop   
/* 0B83C0 800B77C0 00601025 */  move  $v0, $v1
.L800B77C4:
/* 0B83C4 800B77C4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B83C8 800B77C8 27BD0828 */  addiu $sp, $sp, 0x828
/* 0B83CC 800B77CC 03E00008 */  jr    $ra
/* 0B83D0 800B77D0 00000000 */   nop   

glabel func_800B77D4
/* 0B83D4 800B77D4 3C02800E */  lui   $v0, %hi(D_800E3028) # $v0, 0x800e
/* 0B83D8 800B77D8 24423028 */  addiu $v0, %lo(D_800E3028) # addiu $v0, $v0, 0x3028
/* 0B83DC 800B77DC 8C4E0000 */  lw    $t6, ($v0)
/* 0B83E0 800B77E0 3C03800E */  lui   $v1, %hi(D_800E3024) # $v1, 0x800e
/* 0B83E4 800B77E4 01C47821 */  addu  $t7, $t6, $a0
/* 0B83E8 800B77E8 29E1003D */  slti  $at, $t7, 0x3d
/* 0B83EC 800B77EC 14200006 */  bnez  $at, .L800B7808
/* 0B83F0 800B77F0 AC4F0000 */   sw    $t7, ($v0)
/* 0B83F4 800B77F4 24633024 */  addiu $v1, %lo(D_800E3024) # addiu $v1, $v1, 0x3024
/* 0B83F8 800B77F8 8C790000 */  lw    $t9, ($v1)
/* 0B83FC 800B77FC AC400000 */  sw    $zero, ($v0)
/* 0B8400 800B7800 27280001 */  addiu $t0, $t9, 1
/* 0B8404 800B7804 AC680000 */  sw    $t0, ($v1)
.L800B7808:
/* 0B8408 800B7808 03E00008 */  jr    $ra
/* 0B840C 800B780C 00000000 */   nop   

glabel func_800B7810
/* 0B8410 800B7810 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 0B8414 800B7814 3C0F800E */  lui   $t7, %hi(D_800E302C) # $t7, 0x800e
/* 0B8418 800B7818 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0B841C 800B781C AFB50028 */  sw    $s5, 0x28($sp)
/* 0B8420 800B7820 AFB40024 */  sw    $s4, 0x24($sp)
/* 0B8424 800B7824 AFB30020 */  sw    $s3, 0x20($sp)
/* 0B8428 800B7828 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0B842C 800B782C AFB10018 */  sw    $s1, 0x18($sp)
/* 0B8430 800B7830 AFB00014 */  sw    $s0, 0x14($sp)
/* 0B8434 800B7834 25EF302C */  addiu $t7, %lo(D_800E302C) # addiu $t7, $t7, 0x302c
/* 0B8438 800B7838 8DE10000 */  lw    $at, ($t7)
/* 0B843C 800B783C 27AE0050 */  addiu $t6, $sp, 0x50
/* 0B8440 800B7840 ADC10000 */  sw    $at, ($t6)
/* 0B8444 800B7844 8DE10008 */  lw    $at, 8($t7)
/* 0B8448 800B7848 8DE80004 */  lw    $t0, 4($t7)
/* 0B844C 800B784C 00009825 */  move  $s3, $zero
/* 0B8450 800B7850 24040010 */  li    $a0, 16
/* 0B8454 800B7854 24050020 */  li    $a1, 32
/* 0B8458 800B7858 ADC10008 */  sw    $at, 8($t6)
/* 0B845C 800B785C 0C02D8D7 */  jal   func_800B635C
/* 0B8460 800B7860 ADC80004 */   sw    $t0, 4($t6)
/* 0B8464 800B7864 3C03800E */  lui   $v1, %hi(D_800E3024) # $v1, 0x800e
/* 0B8468 800B7868 24633024 */  addiu $v1, %lo(D_800E3024) # addiu $v1, $v1, 0x3024
/* 0B846C 800B786C 8C620000 */  lw    $v0, ($v1)
/* 0B8470 800B7870 00000000 */  nop   
/* 0B8474 800B7874 2C410006 */  sltiu $at, $v0, 6
/* 0B8478 800B7878 1020011B */  beqz  $at, .L800B7CE8
/* 0B847C 800B787C 00024880 */   sll   $t1, $v0, 2
/* 0B8480 800B7880 3C01800F */  lui   $at, 0x800f
/* 0B8484 800B7884 00290821 */  addu  $at, $at, $t1
/* 0B8488 800B7888 8C29913C */  lw    $t1, -0x6ec4($at)
/* 0B848C 800B788C 00000000 */  nop   
/* 0B8490 800B7890 01200008 */  jr    $t1
/* 0B8494 800B7894 00000000 */   nop   
/* 0B8498 800B7898 444AF800 */  cfc1  $t2, $31
/* 0B849C 800B789C 3C038013 */  lui   $v1, %hi(D_80129800) # $v1, 0x8013
/* 0B84A0 800B78A0 35410003 */  ori   $at, $t2, 3
/* 0B84A4 800B78A4 24639800 */  addiu $v1, %lo(D_80129800) # addiu $v1, $v1, -0x6800
/* 0B84A8 800B78A8 38210002 */  xori  $at, $at, 2
/* 0B84AC 800B78AC 44C1F800 */  ctc1  $at, $31
/* 0B84B0 800B78B0 C4640130 */  lwc1  $f4, 0x130($v1)
/* 0B84B4 800B78B4 C4680134 */  lwc1  $f8, 0x134($v1)
/* 0B84B8 800B78B8 460021A4 */  cvt.w.s $f6, $f4
/* 0B84BC 800B78BC C4700138 */  lwc1  $f16, 0x138($v1)
/* 0B84C0 800B78C0 44CAF800 */  ctc1  $t2, $31
/* 0B84C4 800B78C4 3C028013 */  lui   $v0, %hi(D_80129FB0) # $v0, 0x8013
/* 0B84C8 800B78C8 440B3000 */  mfc1  $t3, $f6
/* 0B84CC 800B78CC 444CF800 */  cfc1  $t4, $31
/* 0B84D0 800B78D0 8C6E0120 */  lw    $t6, 0x120($v1)
/* 0B84D4 800B78D4 35810003 */  ori   $at, $t4, 3
/* 0B84D8 800B78D8 38210002 */  xori  $at, $at, 2
/* 0B84DC 800B78DC 44C1F800 */  ctc1  $at, $31
/* 0B84E0 800B78E0 24429FB0 */  addiu $v0, %lo(D_80129FB0) # addiu $v0, $v0, -0x6050
/* 0B84E4 800B78E4 460042A4 */  cvt.w.s $f10, $f8
/* 0B84E8 800B78E8 AC4B0000 */  sw    $t3, ($v0)
/* 0B84EC 800B78EC 44CCF800 */  ctc1  $t4, $31
/* 0B84F0 800B78F0 440D5000 */  mfc1  $t5, $f10
/* 0B84F4 800B78F4 00000000 */  nop   
/* 0B84F8 800B78F8 4459F800 */  cfc1  $t9, $31
/* 0B84FC 800B78FC AC4D0004 */  sw    $t5, 4($v0)
/* 0B8500 800B7900 37210003 */  ori   $at, $t9, 3
/* 0B8504 800B7904 38210002 */  xori  $at, $at, 2
/* 0B8508 800B7908 44C1F800 */  ctc1  $at, $31
/* 0B850C 800B790C 2401FFFF */  li    $at, -1
/* 0B8510 800B7910 460084A4 */  cvt.w.s $f18, $f16
/* 0B8514 800B7914 44189000 */  mfc1  $t8, $f18
/* 0B8518 800B7918 44D9F800 */  ctc1  $t9, $31
/* 0B851C 800B791C 15C1002F */  bne   $t6, $at, .L800B79DC
/* 0B8520 800B7920 AC580008 */   sw    $t8, 8($v0)
/* 0B8524 800B7924 3C058013 */  lui   $a1, %hi(D_8012991C) # $a1, 0x8013
/* 0B8528 800B7928 8CA5991C */  lw    $a1, %lo(D_8012991C)($a1)
/* 0B852C 800B792C 3C04800F */  lui   $a0, %hi(D_800E8F18) # $a0, 0x800f
/* 0B8530 800B7930 0C02D7B7 */  jal   func_800B5EDC
/* 0B8534 800B7934 24848F18 */   addiu $a0, %lo(D_800E8F18) # addiu $a0, $a0, -0x70e8
/* 0B8538 800B7938 3C098013 */  lui   $t1, %hi(D_8012983C) # $t1, 0x8013
/* 0B853C 800B793C 3C0B8013 */  lui   $t3, %hi(D_80129844) # $t3, 0x8013
/* 0B8540 800B7940 8D669844 */  lw    $a2, %lo(D_80129844)($t3)
/* 0B8544 800B7944 8D25983C */  lw    $a1, %lo(D_8012983C)($t1)
/* 0B8548 800B7948 3C04800F */  lui   $a0, %hi(D_800E8F28) # $a0, 0x800f
/* 0B854C 800B794C 0C02D7B7 */  jal   func_800B5EDC
/* 0B8550 800B7950 24848F28 */   addiu $a0, %lo(D_800E8F28) # addiu $a0, $a0, -0x70d8
/* 0B8554 800B7954 3C108013 */  lui   $s0, %hi(D_80129FB0) # $s0, 0x8013
/* 0B8558 800B7958 3C15800F */  lui   $s5, %hi(D_800E8F44) # $s5, 0x800f
/* 0B855C 800B795C 26B58F44 */  addiu $s5, %lo(D_800E8F44) # addiu $s5, $s5, -0x70bc
/* 0B8560 800B7960 26109FB0 */  addiu $s0, %lo(D_80129FB0) # addiu $s0, $s0, -0x6050
/* 0B8564 800B7964 00009025 */  move  $s2, $zero
/* 0B8568 800B7968 2414FFFF */  li    $s4, -1
.L800B796C:
/* 0B856C 800B796C 8E060000 */  lw    $a2, ($s0)
/* 0B8570 800B7970 27AF0050 */  addiu $t7, $sp, 0x50
/* 0B8574 800B7974 1286000C */  beq   $s4, $a2, .L800B79A8
/* 0B8578 800B7978 00000000 */   nop   
/* 0B857C 800B797C 16600006 */  bnez  $s3, .L800B7998
/* 0B8580 800B7980 024F8821 */   addu  $s1, $s2, $t7
/* 0B8584 800B7984 24130001 */  li    $s3, 1
/* 0B8588 800B7988 0C02D7B7 */  jal   func_800B5EDC
/* 0B858C 800B798C 02A02025 */   move  $a0, $s5
/* 0B8590 800B7990 8E060000 */  lw    $a2, ($s0)
/* 0B8594 800B7994 00000000 */  nop   
.L800B7998:
/* 0B8598 800B7998 3C04800F */  lui   $a0, %hi(D_800E8F50) # $a0, 0x800f
/* 0B859C 800B799C 8E250000 */  lw    $a1, ($s1)
/* 0B85A0 800B79A0 0C02D7B7 */  jal   func_800B5EDC
/* 0B85A4 800B79A4 24848F50 */   addiu $a0, %lo(D_800E8F50) # addiu $a0, $a0, -0x70b0
.L800B79A8:
/* 0B85A8 800B79A8 3C0C8013 */  lui   $t4, %hi(D_80129FBC) # $t4, 0x8013
/* 0B85AC 800B79AC 258C9FBC */  addiu $t4, %lo(D_80129FBC) # addiu $t4, $t4, -0x6044
/* 0B85B0 800B79B0 26100004 */  addiu $s0, $s0, 4
/* 0B85B4 800B79B4 160CFFED */  bne   $s0, $t4, .L800B796C
/* 0B85B8 800B79B8 26520004 */   addiu $s2, $s2, 4
/* 0B85BC 800B79BC 3C04800F */  lui   $a0, %hi(D_800E8F58) # $a0, 0x800f
/* 0B85C0 800B79C0 0C02D7B7 */  jal   func_800B5EDC
/* 0B85C4 800B79C4 24848F58 */   addiu $a0, %lo(D_800E8F58) # addiu $a0, $a0, -0x70a8
/* 0B85C8 800B79C8 3C04800F */  lui   $a0, %hi(D_800E8F5C) # $a0, 0x800f
/* 0B85CC 800B79CC 0C02D7B7 */  jal   func_800B5EDC
/* 0B85D0 800B79D0 24848F5C */   addiu $a0, %lo(D_800E8F5C) # addiu $a0, $a0, -0x70a4
/* 0B85D4 800B79D4 100000C5 */  b     .L800B7CEC
/* 0B85D8 800B79D8 8FBF002C */   lw    $ra, 0x2c($sp)
.L800B79DC:
/* 0B85DC 800B79DC 3C04800F */  lui   $a0, %hi(D_800E8F6C) # $a0, 0x800f
/* 0B85E0 800B79E0 8C650014 */  lw    $a1, 0x14($v1)
/* 0B85E4 800B79E4 0C02D7B7 */  jal   func_800B5EDC
/* 0B85E8 800B79E8 24848F6C */   addiu $a0, %lo(D_800E8F6C) # addiu $a0, $a0, -0x7094
/* 0B85EC 800B79EC 3C058013 */  lui   $a1, %hi(D_8012991C) # $a1, 0x8013
/* 0B85F0 800B79F0 8CA5991C */  lw    $a1, %lo(D_8012991C)($a1)
/* 0B85F4 800B79F4 3C04800F */  lui   $a0, %hi(D_800E8F84) # $a0, 0x800f
/* 0B85F8 800B79F8 0C02D7B7 */  jal   func_800B5EDC
/* 0B85FC 800B79FC 24848F84 */   addiu $a0, %lo(D_800E8F84) # addiu $a0, $a0, -0x707c
/* 0B8600 800B7A00 3C058013 */  lui   $a1, %hi(D_80129920) # $a1, 0x8013
/* 0B8604 800B7A04 8CA59920 */  lw    $a1, %lo(D_80129920)($a1)
/* 0B8608 800B7A08 3C04800F */  lui   $a0, %hi(D_800E8F94) # $a0, 0x800f
/* 0B860C 800B7A0C 0C02D7B7 */  jal   func_800B5EDC
/* 0B8610 800B7A10 24848F94 */   addiu $a0, %lo(D_800E8F94) # addiu $a0, $a0, -0x706c
/* 0B8614 800B7A14 3C058013 */  lui   $a1, %hi(D_80129918) # $a1, 0x8013
/* 0B8618 800B7A18 8CA59918 */  lw    $a1, %lo(D_80129918)($a1)
/* 0B861C 800B7A1C 3C04800F */  lui   $a0, %hi(D_800E8FA4) # $a0, 0x800f
/* 0B8620 800B7A20 0C02D7B7 */  jal   func_800B5EDC
/* 0B8624 800B7A24 24848FA4 */   addiu $a0, %lo(D_800E8FA4) # addiu $a0, $a0, -0x705c
/* 0B8628 800B7A28 3C058013 */  lui   $a1, %hi(D_80129924) # $a1, 0x8013
/* 0B862C 800B7A2C 8CA59924 */  lw    $a1, %lo(D_80129924)($a1)
/* 0B8630 800B7A30 3C04800F */  lui   $a0, %hi(D_800E8FB4) # $a0, 0x800f
/* 0B8634 800B7A34 0C02D7B7 */  jal   func_800B5EDC
/* 0B8638 800B7A38 24848FB4 */   addiu $a0, %lo(D_800E8FB4) # addiu $a0, $a0, -0x704c
/* 0B863C 800B7A3C 3C108013 */  lui   $s0, %hi(D_80129FB0) # $s0, 0x8013
/* 0B8640 800B7A40 3C15800F */  lui   $s5, %hi(D_800E8FC8) # $s5, 0x800f
/* 0B8644 800B7A44 26B58FC8 */  addiu $s5, %lo(D_800E8FC8) # addiu $s5, $s5, -0x7038
/* 0B8648 800B7A48 26109FB0 */  addiu $s0, %lo(D_80129FB0) # addiu $s0, $s0, -0x6050
/* 0B864C 800B7A4C 00009025 */  move  $s2, $zero
/* 0B8650 800B7A50 2414FFFF */  li    $s4, -1
.L800B7A54:
/* 0B8654 800B7A54 8E060000 */  lw    $a2, ($s0)
/* 0B8658 800B7A58 27AD0050 */  addiu $t5, $sp, 0x50
/* 0B865C 800B7A5C 1286000C */  beq   $s4, $a2, .L800B7A90
/* 0B8660 800B7A60 00000000 */   nop   
/* 0B8664 800B7A64 16600006 */  bnez  $s3, .L800B7A80
/* 0B8668 800B7A68 024D8821 */   addu  $s1, $s2, $t5
/* 0B866C 800B7A6C 24130001 */  li    $s3, 1
/* 0B8670 800B7A70 0C02D7B7 */  jal   func_800B5EDC
/* 0B8674 800B7A74 02A02025 */   move  $a0, $s5
/* 0B8678 800B7A78 8E060000 */  lw    $a2, ($s0)
/* 0B867C 800B7A7C 00000000 */  nop   
.L800B7A80:
/* 0B8680 800B7A80 3C04800F */  lui   $a0, %hi(D_800E8FD4) # $a0, 0x800f
/* 0B8684 800B7A84 8E250000 */  lw    $a1, ($s1)
/* 0B8688 800B7A88 0C02D7B7 */  jal   func_800B5EDC
/* 0B868C 800B7A8C 24848FD4 */   addiu $a0, %lo(D_800E8FD4) # addiu $a0, $a0, -0x702c
.L800B7A90:
/* 0B8690 800B7A90 3C198013 */  lui   $t9, %hi(D_80129FBC) # $t9, 0x8013
/* 0B8694 800B7A94 27399FBC */  addiu $t9, %lo(D_80129FBC) # addiu $t9, $t9, -0x6044
/* 0B8698 800B7A98 26100004 */  addiu $s0, $s0, 4
/* 0B869C 800B7A9C 1619FFED */  bne   $s0, $t9, .L800B7A54
/* 0B86A0 800B7AA0 26520004 */   addiu $s2, $s2, 4
/* 0B86A4 800B7AA4 3C04800F */  lui   $a0, %hi(D_800E8FDC) # $a0, 0x800f
/* 0B86A8 800B7AA8 0C02D7B7 */  jal   func_800B5EDC
/* 0B86AC 800B7AAC 24848FDC */   addiu $a0, %lo(D_800E8FDC) # addiu $a0, $a0, -0x7024
/* 0B86B0 800B7AB0 3C198013 */  lui   $t9, %hi(D_80129824) # $t9, 0x8013
/* 0B86B4 800B7AB4 3C0F8013 */  lui   $t7, %hi(D_8012982C) # $t7, 0x8013
/* 0B86B8 800B7AB8 3C098013 */  lui   $t1, %hi(D_80129834) # $t1, 0x8013
/* 0B86BC 800B7ABC 8D279834 */  lw    $a3, %lo(D_80129834)($t1)
/* 0B86C0 800B7AC0 8DE6982C */  lw    $a2, %lo(D_8012982C)($t7)
/* 0B86C4 800B7AC4 8F259824 */  lw    $a1, %lo(D_80129824)($t9)
/* 0B86C8 800B7AC8 3C04800F */  lui   $a0, %hi(D_800E8FE0) # $a0, 0x800f
/* 0B86CC 800B7ACC 0C02D7B7 */  jal   func_800B5EDC
/* 0B86D0 800B7AD0 24848FE0 */   addiu $a0, %lo(D_800E8FE0) # addiu $a0, $a0, -0x7020
/* 0B86D4 800B7AD4 3C0B8013 */  lui   $t3, %hi(D_8012983C) # $t3, 0x8013
/* 0B86D8 800B7AD8 3C0D8013 */  lui   $t5, %hi(D_80129844) # $t5, 0x8013
/* 0B86DC 800B7ADC 3C198013 */  lui   $t9, %hi(D_8012984C) # $t9, 0x8013
/* 0B86E0 800B7AE0 8F27984C */  lw    $a3, %lo(D_8012984C)($t9)
/* 0B86E4 800B7AE4 8DA69844 */  lw    $a2, %lo(D_80129844)($t5)
/* 0B86E8 800B7AE8 8D65983C */  lw    $a1, %lo(D_8012983C)($t3)
/* 0B86EC 800B7AEC 3C04800F */  lui   $a0, %hi(D_800E9000) # $a0, 0x800f
/* 0B86F0 800B7AF0 0C02D7B7 */  jal   func_800B5EDC
/* 0B86F4 800B7AF4 24849000 */   addiu $a0, %lo(D_800E9000) # addiu $a0, $a0, -0x7000
/* 0B86F8 800B7AF8 3C0F8013 */  lui   $t7, %hi(D_80129854) # $t7, 0x8013
/* 0B86FC 800B7AFC 3C098013 */  lui   $t1, %hi(D_8012985C) # $t1, 0x8013
/* 0B8700 800B7B00 3C0B8013 */  lui   $t3, %hi(D_80129864) # $t3, 0x8013
/* 0B8704 800B7B04 8D679864 */  lw    $a3, %lo(D_80129864)($t3)
/* 0B8708 800B7B08 8D26985C */  lw    $a2, %lo(D_8012985C)($t1)
/* 0B870C 800B7B0C 8DE59854 */  lw    $a1, %lo(D_80129854)($t7)
/* 0B8710 800B7B10 3C04800F */  lui   $a0, %hi(D_800E9020) # $a0, 0x800f
/* 0B8714 800B7B14 0C02D7B7 */  jal   func_800B5EDC
/* 0B8718 800B7B18 24849020 */   addiu $a0, %lo(D_800E9020) # addiu $a0, $a0, -0x6fe0
/* 0B871C 800B7B1C 3C0D8013 */  lui   $t5, %hi(D_8012986C) # $t5, 0x8013
/* 0B8720 800B7B20 3C198013 */  lui   $t9, %hi(D_80129874) # $t9, 0x8013
/* 0B8724 800B7B24 3C0F8013 */  lui   $t7, %hi(D_8012987C) # $t7, 0x8013
/* 0B8728 800B7B28 8DE7987C */  lw    $a3, %lo(D_8012987C)($t7)
/* 0B872C 800B7B2C 8F269874 */  lw    $a2, %lo(D_80129874)($t9)
/* 0B8730 800B7B30 8DA5986C */  lw    $a1, %lo(D_8012986C)($t5)
/* 0B8734 800B7B34 3C04800F */  lui   $a0, %hi(D_800E9040) # $a0, 0x800f
/* 0B8738 800B7B38 0C02D7B7 */  jal   func_800B5EDC
/* 0B873C 800B7B3C 24849040 */   addiu $a0, %lo(D_800E9040) # addiu $a0, $a0, -0x6fc0
/* 0B8740 800B7B40 3C098013 */  lui   $t1, %hi(D_80129884) # $t1, 0x8013
/* 0B8744 800B7B44 3C0B8013 */  lui   $t3, %hi(D_8012988C) # $t3, 0x8013
/* 0B8748 800B7B48 3C0D8013 */  lui   $t5, %hi(D_80129894) # $t5, 0x8013
/* 0B874C 800B7B4C 8DA79894 */  lw    $a3, %lo(D_80129894)($t5)
/* 0B8750 800B7B50 8D66988C */  lw    $a2, %lo(D_8012988C)($t3)
/* 0B8754 800B7B54 8D259884 */  lw    $a1, %lo(D_80129884)($t1)
/* 0B8758 800B7B58 3C04800F */  lui   $a0, %hi(D_800E9060) # $a0, 0x800f
/* 0B875C 800B7B5C 0C02D7B7 */  jal   func_800B5EDC
/* 0B8760 800B7B60 24849060 */   addiu $a0, %lo(D_800E9060) # addiu $a0, $a0, -0x6fa0
/* 0B8764 800B7B64 3C198013 */  lui   $t9, %hi(D_8012989C) # $t9, 0x8013
/* 0B8768 800B7B68 3C0F8013 */  lui   $t7, %hi(D_801298A4) # $t7, 0x8013
/* 0B876C 800B7B6C 3C098013 */  lui   $t1, %hi(D_801298AC) # $t1, 0x8013
/* 0B8770 800B7B70 8D2798AC */  lw    $a3, %lo(D_801298AC)($t1)
/* 0B8774 800B7B74 8DE698A4 */  lw    $a2, %lo(D_801298A4)($t7)
/* 0B8778 800B7B78 8F25989C */  lw    $a1, %lo(D_8012989C)($t9)
/* 0B877C 800B7B7C 3C04800F */  lui   $a0, %hi(D_800E9080) # $a0, 0x800f
/* 0B8780 800B7B80 0C02D7B7 */  jal   func_800B5EDC
/* 0B8784 800B7B84 24849080 */   addiu $a0, %lo(D_800E9080) # addiu $a0, $a0, -0x6f80
/* 0B8788 800B7B88 3C0B8013 */  lui   $t3, %hi(D_801298B4) # $t3, 0x8013
/* 0B878C 800B7B8C 3C0D8013 */  lui   $t5, %hi(D_801298BC) # $t5, 0x8013
/* 0B8790 800B7B90 3C198013 */  lui   $t9, %hi(D_801298C4) # $t9, 0x8013
/* 0B8794 800B7B94 8F2798C4 */  lw    $a3, %lo(D_801298C4)($t9)
/* 0B8798 800B7B98 8DA698BC */  lw    $a2, %lo(D_801298BC)($t5)
/* 0B879C 800B7B9C 8D6598B4 */  lw    $a1, %lo(D_801298B4)($t3)
/* 0B87A0 800B7BA0 3C04800F */  lui   $a0, %hi(D_800E90A0) # $a0, 0x800f
/* 0B87A4 800B7BA4 0C02D7B7 */  jal   func_800B5EDC
/* 0B87A8 800B7BA8 248490A0 */   addiu $a0, %lo(D_800E90A0) # addiu $a0, $a0, -0x6f60
/* 0B87AC 800B7BAC 3C0F8013 */  lui   $t7, %hi(D_801298CC) # $t7, 0x8013
/* 0B87B0 800B7BB0 3C098013 */  lui   $t1, %hi(D_801298D4) # $t1, 0x8013
/* 0B87B4 800B7BB4 3C0B8013 */  lui   $t3, %hi(D_801298DC) # $t3, 0x8013
/* 0B87B8 800B7BB8 8D6798DC */  lw    $a3, %lo(D_801298DC)($t3)
/* 0B87BC 800B7BBC 8D2698D4 */  lw    $a2, %lo(D_801298D4)($t1)
/* 0B87C0 800B7BC0 8DE598CC */  lw    $a1, %lo(D_801298CC)($t7)
/* 0B87C4 800B7BC4 3C04800F */  lui   $a0, %hi(D_800E90C0) # $a0, 0x800f
/* 0B87C8 800B7BC8 0C02D7B7 */  jal   func_800B5EDC
/* 0B87CC 800B7BCC 248490C0 */   addiu $a0, %lo(D_800E90C0) # addiu $a0, $a0, -0x6f40
/* 0B87D0 800B7BD0 3C0D8013 */  lui   $t5, %hi(D_801298E4) # $t5, 0x8013
/* 0B87D4 800B7BD4 3C198013 */  lui   $t9, %hi(D_801298EC) # $t9, 0x8013
/* 0B87D8 800B7BD8 3C0F8013 */  lui   $t7, %hi(D_801298F4) # $t7, 0x8013
/* 0B87DC 800B7BDC 8DE798F4 */  lw    $a3, %lo(D_801298F4)($t7)
/* 0B87E0 800B7BE0 8F2698EC */  lw    $a2, %lo(D_801298EC)($t9)
/* 0B87E4 800B7BE4 8DA598E4 */  lw    $a1, %lo(D_801298E4)($t5)
/* 0B87E8 800B7BE8 3C04800F */  lui   $a0, %hi(D_800E90E0) # $a0, 0x800f
/* 0B87EC 800B7BEC 0C02D7B7 */  jal   func_800B5EDC
/* 0B87F0 800B7BF0 248490E0 */   addiu $a0, %lo(D_800E90E0) # addiu $a0, $a0, -0x6f20
/* 0B87F4 800B7BF4 3C098013 */  lui   $t1, %hi(D_801298FC) # $t1, 0x8013
/* 0B87F8 800B7BF8 3C0B8013 */  lui   $t3, %hi(D_80129904) # $t3, 0x8013
/* 0B87FC 800B7BFC 8D669904 */  lw    $a2, %lo(D_80129904)($t3)
/* 0B8800 800B7C00 8D2598FC */  lw    $a1, %lo(D_801298FC)($t1)
/* 0B8804 800B7C04 3C04800F */  lui   $a0, %hi(D_800E9100) # $a0, 0x800f
/* 0B8808 800B7C08 0C02D7B7 */  jal   func_800B5EDC
/* 0B880C 800B7C0C 24849100 */   addiu $a0, %lo(D_800E9100) # addiu $a0, $a0, -0x6f00
/* 0B8810 800B7C10 10000036 */  b     .L800B7CEC
/* 0B8814 800B7C14 8FBF002C */   lw    $ra, 0x2c($sp)
/* 0B8818 800B7C18 00021880 */  sll   $v1, $v0, 2
/* 0B881C 800B7C1C 00621823 */  subu  $v1, $v1, $v0
/* 0B8820 800B7C20 00031900 */  sll   $v1, $v1, 4
/* 0B8824 800B7C24 2463FFD0 */  addiu $v1, $v1, -0x30
/* 0B8828 800B7C28 3C0D8013 */  lui   $t5, %hi(D_801299B0) # $t5, 0x8013
/* 0B882C 800B7C2C 25AD99B0 */  addiu $t5, %lo(D_801299B0) # addiu $t5, $t5, -0x6650
/* 0B8830 800B7C30 00036080 */  sll   $t4, $v1, 2
/* 0B8834 800B7C34 3C11800F */  lui   $s1, %hi(D_800E9118) # $s1, 0x800f
/* 0B8838 800B7C38 26319118 */  addiu $s1, %lo(D_800E9118) # addiu $s1, $s1, -0x6ee8
/* 0B883C 800B7C3C 018D8021 */  addu  $s0, $t4, $t5
/* 0B8840 800B7C40 0000A025 */  move  $s4, $zero
/* 0B8844 800B7C44 24150010 */  li    $s5, 16
.L800B7C48:
/* 0B8848 800B7C48 8E050000 */  lw    $a1, ($s0)
/* 0B884C 800B7C4C 8E060040 */  lw    $a2, 0x40($s0)
/* 0B8850 800B7C50 8E070080 */  lw    $a3, 0x80($s0)
/* 0B8854 800B7C54 0C02D7B7 */  jal   func_800B5EDC
/* 0B8858 800B7C58 02202025 */   move  $a0, $s1
/* 0B885C 800B7C5C 26940001 */  addiu $s4, $s4, 1
/* 0B8860 800B7C60 1695FFF9 */  bne   $s4, $s5, .L800B7C48
/* 0B8864 800B7C64 26100004 */   addiu $s0, $s0, 4
/* 0B8868 800B7C68 10000020 */  b     .L800B7CEC
/* 0B886C 800B7C6C 8FBF002C */   lw    $ra, 0x2c($sp)
/* 0B8870 800B7C70 000219C0 */  sll   $v1, $v0, 7
/* 0B8874 800B7C74 2463FE00 */  addiu $v1, $v1, -0x200
/* 0B8878 800B7C78 3C198013 */  lui   $t9, %hi(D_80129BB0) # $t9, 0x8013
/* 0B887C 800B7C7C 27399BB0 */  addiu $t9, %lo(D_80129BB0) # addiu $t9, $t9, -0x6450
/* 0B8880 800B7C80 0003C040 */  sll   $t8, $v1, 1
/* 0B8884 800B7C84 3C12800F */  lui   $s2, %hi(D_800E9130) # $s2, 0x800f
/* 0B8888 800B7C88 26529130 */  addiu $s2, %lo(D_800E9130) # addiu $s2, $s2, -0x6ed0
/* 0B888C 800B7C8C 03198821 */  addu  $s1, $t8, $t9
/* 0B8890 800B7C90 0000A025 */  move  $s4, $zero
/* 0B8894 800B7C94 24150010 */  li    $s5, 16
/* 0B8898 800B7C98 24130008 */  li    $s3, 8
.L800B7C9C:
/* 0B889C 800B7C9C 3C04800F */  lui   $a0, %hi(D_800E912C) # $a0, 0x800f
/* 0B88A0 800B7CA0 0C02D7B7 */  jal   func_800B5EDC
/* 0B88A4 800B7CA4 2484912C */   addiu $a0, %lo(D_800E912C) # addiu $a0, $a0, -0x6ed4
/* 0B88A8 800B7CA8 00008025 */  move  $s0, $zero
.L800B7CAC:
/* 0B88AC 800B7CAC 96250000 */  lhu   $a1, ($s1)
/* 0B88B0 800B7CB0 0C02D7B7 */  jal   func_800B5EDC
/* 0B88B4 800B7CB4 02402025 */   move  $a0, $s2
/* 0B88B8 800B7CB8 26100001 */  addiu $s0, $s0, 1
/* 0B88BC 800B7CBC 1613FFFB */  bne   $s0, $s3, .L800B7CAC
/* 0B88C0 800B7CC0 26310002 */   addiu $s1, $s1, 2
/* 0B88C4 800B7CC4 3C04800F */  lui   $a0, %hi(D_800E9138) # $a0, 0x800f
/* 0B88C8 800B7CC8 0C02D7B7 */  jal   func_800B5EDC
/* 0B88CC 800B7CCC 24849138 */   addiu $a0, %lo(D_800E9138) # addiu $a0, $a0, -0x6ec8
/* 0B88D0 800B7CD0 26940001 */  addiu $s4, $s4, 1
/* 0B88D4 800B7CD4 1695FFF1 */  bne   $s4, $s5, .L800B7C9C
/* 0B88D8 800B7CD8 00000000 */   nop   
/* 0B88DC 800B7CDC 10000003 */  b     .L800B7CEC
/* 0B88E0 800B7CE0 8FBF002C */   lw    $ra, 0x2c($sp)
/* 0B88E4 800B7CE4 AC600000 */  sw    $zero, ($v1)
.L800B7CE8:
/* 0B88E8 800B7CE8 8FBF002C */  lw    $ra, 0x2c($sp)
.L800B7CEC:
/* 0B88EC 800B7CEC 8FB00014 */  lw    $s0, 0x14($sp)
/* 0B88F0 800B7CF0 8FB10018 */  lw    $s1, 0x18($sp)
/* 0B88F4 800B7CF4 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0B88F8 800B7CF8 8FB30020 */  lw    $s3, 0x20($sp)
/* 0B88FC 800B7CFC 8FB40024 */  lw    $s4, 0x24($sp)
/* 0B8900 800B7D00 8FB50028 */  lw    $s5, 0x28($sp)
/* 0B8904 800B7D04 03E00008 */  jr    $ra
/* 0B8908 800B7D08 27BD0060 */   addiu $sp, $sp, 0x60

/* 0B890C 800B7D0C 00000000 */  nop   
glabel func_800B7D10
/* 0B8910 800B7D10 03E00008 */  jr    $ra
/* 0B8914 800B7D14 03A01025 */   move  $v0, $sp

/* 0B8918 800B7D18 00000000 */  nop   
/* 0B891C 800B7D1C 00000000 */  nop   
