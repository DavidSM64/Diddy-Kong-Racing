.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C78E0
/* 0C84E0 800C78E0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C84E4 800C78E4 00A03825 */  move  $a3, $a1
/* 0C84E8 800C78E8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C84EC 800C78EC AFA5002C */  sw    $a1, 0x2c($sp)
/* 0C84F0 800C78F0 AFA60030 */  sw    $a2, 0x30($sp)
/* 0C84F4 800C78F4 00C04025 */  move  $t0, $a2
/* 0C84F8 800C78F8 240E0002 */  li    $t6, 2
/* 0C84FC 800C78FC 34EF00B0 */  ori   $t7, $a3, 0xb0
/* 0C8500 800C7900 2418000A */  li    $t8, 10
/* 0C8504 800C7904 A7AE0018 */  sh    $t6, 0x18($sp)
/* 0C8508 800C7908 AFA0001C */  sw    $zero, 0x1c($sp)
/* 0C850C 800C790C A3AF0020 */  sb    $t7, 0x20($sp)
/* 0C8510 800C7910 A3B80021 */  sb    $t8, 0x21($sp)
/* 0C8514 800C7914 A3A80022 */  sb    $t0, 0x22($sp)
/* 0C8518 800C7918 00003025 */  move  $a2, $zero
/* 0C851C 800C791C 27A50018 */  addiu $a1, $sp, 0x18
/* 0C8520 800C7920 0C03246B */  jal   func_800C91AC
/* 0C8524 800C7924 24840048 */   addiu $a0, $a0, 0x48
/* 0C8528 800C7928 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C852C 800C792C 27BD0028 */  addiu $sp, $sp, 0x28
/* 0C8530 800C7930 03E00008 */  jr    $ra
/* 0C8534 800C7934 00000000 */   nop   

/* 0C8538 800C7938 00000000 */  nop   
/* 0C853C 800C793C 00000000 */  nop   
