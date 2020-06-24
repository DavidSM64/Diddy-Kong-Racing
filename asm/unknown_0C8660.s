.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C7A60
/* 0C8660 800C7A60 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C8664 800C7A64 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C8668 800C7A68 240E000E */  li    $t6, 14
/* 0C866C 800C7A6C AFA5001C */  sw    $a1, 0x1c($sp)
/* 0C8670 800C7A70 A7AE0018 */  sh    $t6, 0x18($sp)
/* 0C8674 800C7A74 27A50018 */  addiu $a1, $sp, 0x18
/* 0C8678 800C7A78 24840048 */  addiu $a0, $a0, 0x48
/* 0C867C 800C7A7C 0C03246B */  jal   func_800C91AC
/* 0C8680 800C7A80 00003025 */   move  $a2, $zero
/* 0C8684 800C7A84 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C8688 800C7A88 27BD0028 */  addiu $sp, $sp, 0x28
/* 0C868C 800C7A8C 03E00008 */  jr    $ra
/* 0C8690 800C7A90 00000000 */   nop   

/* 0C8694 800C7A94 00000000 */  nop   
/* 0C8698 800C7A98 00000000 */  nop   
/* 0C869C 800C7A9C 00000000 */  nop   
