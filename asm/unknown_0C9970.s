.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C8D70
/* 0C9970 800C8D70 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0C9974 800C8D74 3C0F800E */  lui   $t7, %hi(D_800E3790) # $t7, 0x800e
/* 0C9978 800C8D78 91EF3790 */  lbu   $t7, %lo(D_800E3790)($t7)
/* 0C997C 800C8D7C AFA40020 */  sw    $a0, 0x20($sp)
/* 0C9980 800C8D80 8FAE0020 */  lw    $t6, 0x20($sp)
/* 0C9984 800C8D84 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C9988 800C8D88 AFA50024 */  sw    $a1, 0x24($sp)
/* 0C998C 800C8D8C 11E00003 */  beqz  $t7, .L800C8D9C
/* 0C9990 800C8D90 AFAE001C */   sw    $t6, 0x1c($sp)
/* 0C9994 800C8D94 25D8E000 */  addiu $t8, $t6, -0x2000
/* 0C9998 800C8D98 AFB8001C */  sw    $t8, 0x1c($sp)
.L800C8D9C:
/* 0C999C 800C8D9C 8FB90020 */  lw    $t9, 0x20($sp)
/* 0C99A0 800C8DA0 8FA80024 */  lw    $t0, 0x24($sp)
/* 0C99A4 800C8DA4 24012000 */  li    $at, 8192
/* 0C99A8 800C8DA8 03284821 */  addu  $t1, $t9, $t0
/* 0C99AC 800C8DAC 312A3FFF */  andi  $t2, $t1, 0x3fff
/* 0C99B0 800C8DB0 15410005 */  bne   $t2, $at, .L800C8DC8
/* 0C99B4 800C8DB4 00000000 */   nop   
/* 0C99B8 800C8DB8 240B0001 */  li    $t3, 1
/* 0C99BC 800C8DBC 3C01800E */  lui   $at, %hi(D_800E3790) # $at, 0x800e
/* 0C99C0 800C8DC0 10000003 */  b     .L800C8DD0
/* 0C99C4 800C8DC4 A02B3790 */   sb    $t3, %lo(D_800E3790)($at)
.L800C8DC8:
/* 0C99C8 800C8DC8 3C01800E */  lui   $at, %hi(D_800E3790) # $at, 0x800e
/* 0C99CC 800C8DCC A0203790 */  sb    $zero, %lo(D_800E3790)($at)
.L800C8DD0:
/* 0C99D0 800C8DD0 0C034D9C */  jal   func_800D3670
/* 0C99D4 800C8DD4 00000000 */   nop   
/* 0C99D8 800C8DD8 10400003 */  beqz  $v0, .L800C8DE8
/* 0C99DC 800C8DDC 00000000 */   nop   
/* 0C99E0 800C8DE0 10000009 */  b     .L800C8E08
/* 0C99E4 800C8DE4 2402FFFF */   li    $v0, -1
.L800C8DE8:
/* 0C99E8 800C8DE8 0C03233C */  jal   func_800C8CF0
/* 0C99EC 800C8DEC 8FA4001C */   lw    $a0, 0x1c($sp)
/* 0C99F0 800C8DF0 3C0CA450 */  lui   $t4, 0xa450
/* 0C99F4 800C8DF4 AD820000 */  sw    $v0, ($t4)
/* 0C99F8 800C8DF8 8FAD0024 */  lw    $t5, 0x24($sp)
/* 0C99FC 800C8DFC 3C0FA450 */  lui   $t7, %hi(D_A4500004) # $t7, 0xa450
/* 0C9A00 800C8E00 00001025 */  move  $v0, $zero
/* 0C9A04 800C8E04 ADED0004 */  sw    $t5, %lo(D_A4500004)($t7)
.L800C8E08:
/* 0C9A08 800C8E08 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C9A0C 800C8E0C 27BD0020 */  addiu $sp, $sp, 0x20
/* 0C9A10 800C8E10 03E00008 */  jr    $ra
/* 0C9A14 800C8E14 00000000 */   nop   

/* 0C9A18 800C8E18 00000000 */  nop   
/* 0C9A1C 800C8E1C 00000000 */  nop   
