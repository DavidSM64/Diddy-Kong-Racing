glabel func_8006EAC0
/* 06F6C0 8006EAC0 3C038012 */  lui   $v1, %hi(D_80123560) # $v1, 0x8012
/* 06F6C4 8006EAC4 8C633560 */  lw    $v1, %lo(D_80123560)($v1)
/* 06F6C8 8006EAC8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 06F6CC 8006EACC 1460000D */  bnez  $v1, .L8006EB04
/* 06F6D0 8006EAD0 AFBF0014 */   sw    $ra, 0x14($sp)
/* 06F6D4 8006EAD4 3C048012 */  lui   $a0, %hi(D_80123548) # $a0, 0x8012
/* 06F6D8 8006EAD8 24843548 */  addiu $a0, %lo(D_80123548) # addiu $a0, $a0, 0x3548
/* 06F6DC 8006EADC 00002825 */  move  $a1, $zero
/* 06F6E0 8006EAE0 0C0322EC */  jal   osRecvMesg
/* 06F6E4 8006EAE4 00003025 */   move  $a2, $zero
/* 06F6E8 8006EAE8 244E0001 */  addiu $t6, $v0, 1
/* 06F6EC 8006EAEC 000E702B */  sltu  $t6, $zero, $t6
/* 06F6F0 8006EAF0 3C018012 */  lui   $at, %hi(D_80123560) # $at, 0x8012
/* 06F6F4 8006EAF4 AC2E3560 */  sw    $t6, %lo(D_80123560)($at)
/* 06F6F8 8006EAF8 3C038012 */  lui   $v1, %hi(D_80123560) # $v1, 0x8012
/* 06F6FC 8006EAFC 8C633560 */  lw    $v1, %lo(D_80123560)($v1)
/* 06F700 8006EB00 00000000 */  nop   
.L8006EB04:
/* 06F704 8006EB04 8FBF0014 */  lw    $ra, 0x14($sp)
/* 06F708 8006EB08 27BD0018 */  addiu $sp, $sp, 0x18
/* 06F70C 8006EB0C 03E00008 */  jr    $ra
/* 06F710 8006EB10 00601025 */   move  $v0, $v1

