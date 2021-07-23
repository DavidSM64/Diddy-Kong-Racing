glabel func_80065D98
/* 066998 80065D98 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 06699C 80065D9C AFBF001C */  sw    $ra, 0x1c($sp)
/* 0669A0 80065DA0 0C02DBD4 */  jal   func_800B6F50
/* 0669A4 80065DA4 AFA40020 */   sw    $a0, 0x20($sp)
/* 0669A8 80065DA8 3C0E8012 */  lui   $t6, %hi(D_8011F758) # $t6, 0x8012
/* 0669AC 80065DAC 25CEF758 */  addiu $t6, %lo(D_8011F758) # addiu $t6, $t6, -0x8a8
/* 0669B0 80065DB0 3C048012 */  lui   $a0, %hi(D_8011F910) # $a0, 0x8012
/* 0669B4 80065DB4 3C068007 */  lui   $a2, %hi(thread3_main) # $a2, 0x8007
/* 0669B8 80065DB8 240F000A */  li    $t7, 10
/* 0669BC 80065DBC AFAF0014 */  sw    $t7, 0x14($sp)
/* 0669C0 80065DC0 24C6C330 */  addiu $a2, %lo(thread3_main) # addiu $a2, $a2, -0x3cd0
/* 0669C4 80065DC4 2484F910 */  addiu $a0, %lo(D_8011F910) # addiu $a0, $a0, -0x6f0
/* 0669C8 80065DC8 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0669CC 80065DCC 24050003 */  li    $a1, 3
/* 0669D0 80065DD0 0C032214 */  jal   osCreateThread
/* 0669D4 80065DD4 00003825 */   move  $a3, $zero
/* 0669D8 80065DD8 3C028012 */  lui   $v0, %hi(D_8011D758) # $v0, 0x8012
/* 0669DC 80065DDC 2442D758 */  addiu $v0, %lo(D_8011D758) # addiu $v0, $v0, -0x28a8
/* 0669E0 80065DE0 24180000 */  li    $t8, 0
/* 0669E4 80065DE4 24190000 */  li    $t9, 0
/* 0669E8 80065DE8 24080000 */  li    $t0, 0
/* 0669EC 80065DEC 24090000 */  li    $t1, 0
/* 0669F0 80065DF0 3C048012 */  lui   $a0, %hi(D_8011F910) # $a0, 0x8012
/* 0669F4 80065DF4 AC592004 */  sw    $t9, 0x2004($v0)
/* 0669F8 80065DF8 AC582000 */  sw    $t8, 0x2000($v0)
/* 0669FC 80065DFC AC490004 */  sw    $t1, 4($v0)
/* 066A00 80065E00 AC480000 */  sw    $t0, ($v0)
/* 066A04 80065E04 0C032268 */  jal   osStartThread
/* 066A08 80065E08 2484F910 */   addiu $a0, %lo(D_8011F910) # addiu $a0, $a0, -0x6f0
/* 066A0C 80065E0C 00002025 */  move  $a0, $zero
/* 066A10 80065E10 0C033210 */  jal   osSetThreadPri
/* 066A14 80065E14 00002825 */   move  $a1, $zero
.L80065E18:
/* 066A18 80065E18 1000FFFF */  b     .L80065E18
/* 066A1C 80065E1C 00000000 */   nop   
/* 066A20 80065E20 8FBF001C */  lw    $ra, 0x1c($sp)
/* 066A24 80065E24 27BD0020 */  addiu $sp, $sp, 0x20
/* 066A28 80065E28 03E00008 */  jr    $ra
/* 066A2C 80065E2C 00000000 */   nop  