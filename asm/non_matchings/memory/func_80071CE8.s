# Unused?

glabel func_80071CE8
/* 0728E8 80071CE8 3C028012 */  lui   $v0, %hi(gNumberOfMemoryPools) # $v0, 0x8012
/* 0728EC 80071CEC 8C4235C0 */  lw    $v0, %lo(gNumberOfMemoryPools)($v0)
/* 0728F0 80071CF0 2405FFFF */  li    $a1, -1
/* 0728F4 80071CF4 1045000C */  beq   $v0, $a1, .L80071D28
/* 0728F8 80071CF8 24440001 */   addiu $a0, $v0, 1
/* 0728FC 80071CFC 308E0003 */  andi  $t6, $a0, 3
/* 072900 80071D00 000E2023 */  negu  $a0, $t6
/* 072904 80071D04 10800005 */  beqz  $a0, .L80071D1C
/* 072908 80071D08 00821821 */   addu  $v1, $a0, $v0
.L80071D0C:
/* 07290C 80071D0C 2442FFFF */  addiu $v0, $v0, -1
/* 072910 80071D10 1462FFFE */  bne   $v1, $v0, .L80071D0C
/* 072914 80071D14 00000000 */   nop   
/* 072918 80071D18 10450003 */  beq   $v0, $a1, .L80071D28
.L80071D1C:
/* 07291C 80071D1C 2442FFFC */   addiu $v0, $v0, -4
.L80071D20:
/* 072920 80071D20 1445FFFF */  bne   $v0, $a1, .L80071D20
/* 072924 80071D24 2442FFFC */   addiu $v0, $v0, -4
.L80071D28:
/* 072928 80071D28 03E00008 */  jr    $ra
/* 07292C 80071D2C 00000000 */   nop   