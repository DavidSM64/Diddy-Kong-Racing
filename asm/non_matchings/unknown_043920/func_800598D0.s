glabel func_800598D0
/* 05A4D0 800598D0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 05A4D4 800598D4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 05A4D8 800598D8 3C05FF00 */  lui   $a1, (0xFF0000FF >> 16) # lui $a1, 0xff00
/* 05A4DC 800598DC 34A500FF */  ori   $a1, (0xFF0000FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 05A4E0 800598E0 0C01C327 */  jal   func_80070C9C
/* 05A4E4 800598E4 240421C0 */   li    $a0, 8640
/* 05A4E8 800598E8 3C038012 */  lui   $v1, %hi(D_8011D590) # $v1, 0x8012
/* 05A4EC 800598EC 3C048012 */  lui   $a0, %hi(D_8011D5A0) # $a0, 0x8012
/* 05A4F0 800598F0 2484D5A0 */  addiu $a0, %lo(D_8011D5A0) # addiu $a0, $a0, -0x2a60
/* 05A4F4 800598F4 2463D590 */  addiu $v1, %lo(D_8011D590) # addiu $v1, $v1, -0x2a70
/* 05A4F8 800598F8 3C058012 */  lui   $a1, %hi(D_8011D5A8) # $a1, 0x8012
/* 05A4FC 800598FC 24A5D5A8 */  addiu $a1, %lo(D_8011D5A8) # addiu $a1, $a1, -0x2a58
/* 05A500 80059900 244F10E0 */  addiu $t7, $v0, 0x10e0
/* 05A504 80059904 AC620000 */  sw    $v0, ($v1)
/* 05A508 80059908 AC6F0004 */  sw    $t7, 4($v1)
/* 05A50C 8005990C AC600008 */  sw    $zero, 8($v1)
/* 05A510 80059910 A4800000 */  sh    $zero, ($a0)
/* 05A514 80059914 A4800002 */  sh    $zero, 2($a0)
/* 05A518 80059918 A4800004 */  sh    $zero, 4($a0)
/* 05A51C 8005991C A4A00000 */  sh    $zero, ($a1)
/* 05A520 80059920 A4A00002 */  sh    $zero, 2($a1)
/* 05A524 80059924 3C018012 */  lui   $at, %hi(D_8011D59D) # $at, 0x8012
/* 05A528 80059928 8FBF0014 */  lw    $ra, 0x14($sp)
/* 05A52C 8005992C A020D59D */  sb    $zero, %lo(D_8011D59D)($at)
/* 05A530 80059930 3C018012 */  lui   $at, %hi(D_8011D5AC) # $at, 0x8012
/* 05A534 80059934 2418FFFF */  li    $t8, -1
/* 05A538 80059938 A438D5AC */  sh    $t8, %lo(D_8011D5AC)($at)
/* 05A53C 8005993C 03E00008 */  jr    $ra
/* 05A540 80059940 27BD0018 */   addiu $sp, $sp, 0x18

