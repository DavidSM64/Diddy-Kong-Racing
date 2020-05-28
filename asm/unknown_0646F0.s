.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_80063AF0
/* 0646F0 80063AF0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0646F4 80063AF4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0646F8 80063AF8 AFA40028 */  sw    $a0, 0x28($sp)
/* 0646FC 80063AFC AFA5002C */  sw    $a1, 0x2c($sp)
/* 064700 80063B00 00A03825 */  move  $a3, $a1
/* 064704 80063B04 240E0002 */  li    $t6, 2
/* 064708 80063B08 240F00B0 */  li    $t7, 176
/* 06470C 80063B0C 2418006A */  li    $t8, 106
/* 064710 80063B10 A7AE0018 */  sh    $t6, 0x18($sp)
/* 064714 80063B14 AFA0001C */  sw    $zero, 0x1c($sp)
/* 064718 80063B18 A3AF0020 */  sb    $t7, 0x20($sp)
/* 06471C 80063B1C A3B80021 */  sb    $t8, 0x21($sp)
/* 064720 80063B20 A3A70022 */  sb    $a3, 0x22($sp)
/* 064724 80063B24 27A50018 */  addiu $a1, $sp, 0x18
/* 064728 80063B28 24840048 */  addiu $a0, $a0, 0x48
/* 06472C 80063B2C 0C03246B */  jal   func_800C91AC
/* 064730 80063B30 00003025 */   move  $a2, $zero
/* 064734 80063B34 8FBF0014 */  lw    $ra, 0x14($sp)
/* 064738 80063B38 27BD0028 */  addiu $sp, $sp, 0x28
/* 06473C 80063B3C 03E00008 */  jr    $ra
/* 064740 80063B40 00000000 */   nop   

glabel func_80063B44
/* 064744 80063B44 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 064748 80063B48 AFBF0014 */  sw    $ra, 0x14($sp)
/* 06474C 80063B4C AFA40028 */  sw    $a0, 0x28($sp)
/* 064750 80063B50 AFA5002C */  sw    $a1, 0x2c($sp)
/* 064754 80063B54 00A03825 */  move  $a3, $a1
/* 064758 80063B58 240E0002 */  li    $t6, 2
/* 06475C 80063B5C 240F00B0 */  li    $t7, 176
/* 064760 80063B60 2418006C */  li    $t8, 108
/* 064764 80063B64 A7AE0018 */  sh    $t6, 0x18($sp)
/* 064768 80063B68 AFA0001C */  sw    $zero, 0x1c($sp)
/* 06476C 80063B6C A3AF0020 */  sb    $t7, 0x20($sp)
/* 064770 80063B70 A3B80021 */  sb    $t8, 0x21($sp)
/* 064774 80063B74 A3A70022 */  sb    $a3, 0x22($sp)
/* 064778 80063B78 27A50018 */  addiu $a1, $sp, 0x18
/* 06477C 80063B7C 24840048 */  addiu $a0, $a0, 0x48
/* 064780 80063B80 0C03246B */  jal   func_800C91AC
/* 064784 80063B84 00003025 */   move  $a2, $zero
/* 064788 80063B88 8FBF0014 */  lw    $ra, 0x14($sp)
/* 06478C 80063B8C 27BD0028 */  addiu $sp, $sp, 0x28
/* 064790 80063B90 03E00008 */  jr    $ra
/* 064794 80063B94 00000000 */   nop   

/* 064798 80063B98 00000000 */  nop   
/* 06479C 80063B9C 00000000 */  nop   
