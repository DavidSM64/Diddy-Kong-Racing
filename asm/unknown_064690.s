.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_80063A90
/* 064690 80063A90 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 064694 80063A94 AFBF0014 */  sw    $ra, 0x14($sp)
/* 064698 80063A98 AFA40028 */  sw    $a0, 0x28($sp)
/* 06469C 80063A9C AFA5002C */  sw    $a1, 0x2c($sp)
/* 0646A0 80063AA0 00A03825 */  move  $a3, $a1
/* 0646A4 80063AA4 240E0002 */  li    $t6, 2
/* 0646A8 80063AA8 240F00B0 */  li    $t7, 176
/* 0646AC 80063AAC 2418005F */  li    $t8, 95
/* 0646B0 80063AB0 A7AE0018 */  sh    $t6, 0x18($sp)
/* 0646B4 80063AB4 AFA0001C */  sw    $zero, 0x1c($sp)
/* 0646B8 80063AB8 A3AF0020 */  sb    $t7, 0x20($sp)
/* 0646BC 80063ABC A3B80021 */  sb    $t8, 0x21($sp)
/* 0646C0 80063AC0 A3A70022 */  sb    $a3, 0x22($sp)
/* 0646C4 80063AC4 27A50018 */  addiu $a1, $sp, 0x18
/* 0646C8 80063AC8 24840048 */  addiu $a0, $a0, 0x48
/* 0646CC 80063ACC 0C03246B */  jal   func_800C91AC
/* 0646D0 80063AD0 00003025 */   move  $a2, $zero
/* 0646D4 80063AD4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0646D8 80063AD8 27BD0028 */  addiu $sp, $sp, 0x28
/* 0646DC 80063ADC 03E00008 */  jr    $ra
/* 0646E0 80063AE0 00000000 */   nop   

/* 0646E4 80063AE4 00000000 */  nop   
/* 0646E8 80063AE8 00000000 */  nop   
/* 0646EC 80063AEC 00000000 */  nop   
