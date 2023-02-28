glabel render_printf /* official name: diPrintf */
/* 0B6ADC 800B5EDC 3C0E8013 */  lui   $t6, %hi(gDebugPrintBufferEnd) # $t6, 0x8013
/* 0B6AE0 800B5EE0 8DCE85D8 */  lw    $t6, %lo(gDebugPrintBufferEnd)($t6)
/* 0B6AE4 800B5EE4 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0B6AE8 800B5EE8 3C0F8012 */  lui   $t7, %hi(gDebugPrintBufferStart) # $t7, 0x8012
/* 0B6AEC 800B5EEC 25EF7CD8 */  addiu $t7, %lo(gDebugPrintBufferStart) # addiu $t7, $t7, 0x7cd8
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
/* 0B6B20 800B5F20 3C048013 */  lui   $a0, %hi(gDebugPrintBufferEnd) # $a0, 0x8013
/* 0B6B24 800B5F24 8C8485D8 */  lw    $a0, %lo(gDebugPrintBufferEnd)($a0)
/* 0B6B28 800B5F28 8FA50020 */  lw    $a1, 0x20($sp)
/* 0B6B2C 800B5F2C 0C02D290 */  jal   sprintf
/* 0B6B30 800B5F30 27A60024 */   addiu $a2, $sp, 0x24
/* 0B6B34 800B5F34 00002025 */  move  $a0, $zero
/* 0B6B38 800B5F38 0C02D282 */  jal   func_800B4A08
/* 0B6B3C 800B5F3C AFA20018 */   sw    $v0, 0x18($sp)
/* 0B6B40 800B5F40 8FA30018 */  lw    $v1, 0x18($sp)
/* 0B6B44 800B5F44 3C028013 */  lui   $v0, %hi(gDebugPrintBufferEnd) # $v0, 0x8013
/* 0B6B48 800B5F48 18600006 */  blez  $v1, .L800B5F64
/* 0B6B4C 800B5F4C 244285D8 */   addiu $v0, %lo(gDebugPrintBufferEnd) # addiu $v0, $v0, -0x7a28
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

