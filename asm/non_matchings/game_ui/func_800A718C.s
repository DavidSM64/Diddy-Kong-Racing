glabel func_800A718C
/* 0A7D8C 800A718C 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0A7D90 800A7190 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0A7D94 800A7194 0C01BAA4 */  jal   get_settings
/* 0A7D98 800A7198 AFA40030 */   sw    $a0, 0x30($sp)
/* 0A7D9C 800A719C 3C0E8000 */  lui   $t6, %hi(osTvType) # $t6, 0x8000
/* 0A7DA0 800A71A0 8DCE0300 */  lw    $t6, %lo(osTvType)($t6)
/* 0A7DA4 800A71A4 00402025 */  move  $a0, $v0
/* 0A7DA8 800A71A8 15C00003 */  bnez  $t6, .L800A71B8
/* 0A7DAC 800A71AC 240F0286 */   li    $t7, 646
/* 0A7DB0 800A71B0 10000003 */  b     .L800A71C0
/* 0A7DB4 800A71B4 AFAF0020 */   sw    $t7, 0x20($sp)
.L800A71B8:
/* 0A7DB8 800A71B8 24180348 */  li    $t8, 840
/* 0A7DBC 800A71BC AFB80020 */  sw    $t8, 0x20($sp)
.L800A71C0:
/* 0A7DC0 800A71C0 8C590010 */  lw    $t9, 0x10($v0)
/* 0A7DC4 800A71C4 00000000 */  nop   
/* 0A7DC8 800A71C8 332A0004 */  andi  $t2, $t9, 4
/* 0A7DCC 800A71CC 11400004 */  beqz  $t2, .L800A71E0
/* 0A7DD0 800A71D0 3C0C8012 */   lui   $t4, %hi(gCurrentHud) # $t4, 0x8012
/* 0A7DD4 800A71D4 8D8C6CDC */  lw    $t4, %lo(gCurrentHud)($t4)
/* 0A7DD8 800A71D8 240B0045 */  li    $t3, 69
/* 0A7DDC 800A71DC A58B0266 */  sh    $t3, 0x266($t4)
.L800A71E0:
/* 0A7DE0 800A71E0 0C007910 */  jal   func_8001E440
/* 0A7DE4 800A71E4 AFA4001C */   sw    $a0, 0x1c($sp)
/* 0A7DE8 800A71E8 8FA4001C */  lw    $a0, 0x1c($sp)
/* 0A7DEC 800A71EC 2401000A */  li    $at, 10
/* 0A7DF0 800A71F0 1441000D */  bne   $v0, $at, .L800A7228
/* 0A7DF4 800A71F4 00000000 */   nop   
/* 0A7DF8 800A71F8 0C006B95 */  jal   func_8001AE54
/* 0A7DFC 800A71FC AFA4001C */   sw    $a0, 0x1c($sp)
/* 0A7E00 800A7200 8FAD0020 */  lw    $t5, 0x20($sp)
/* 0A7E04 800A7204 8FA4001C */  lw    $a0, 0x1c($sp)
/* 0A7E08 800A7208 004D082B */  sltu  $at, $v0, $t5
/* 0A7E0C 800A720C 10200006 */  beqz  $at, .L800A7228
/* 0A7E10 800A7210 00000000 */   nop   
/* 0A7E14 800A7214 8C8E0000 */  lw    $t6, ($a0)
/* 0A7E18 800A7218 00000000 */  nop   
/* 0A7E1C 800A721C 85C30000 */  lh    $v1, ($t6)
/* 0A7E20 800A7220 1000001D */  b     .L800A7298
/* 0A7E24 800A7224 2463FFFF */   addiu $v1, $v1, -1
.L800A7228:
/* 0A7E28 800A7228 8C8F0000 */  lw    $t7, ($a0)
/* 0A7E2C 800A722C 00000000 */  nop   
/* 0A7E30 800A7230 85E30000 */  lh    $v1, ($t7)
/* 0A7E34 800A7234 0C007910 */  jal   func_8001E440
/* 0A7E38 800A7238 AFA3002C */   sw    $v1, 0x2c($sp)
/* 0A7E3C 800A723C 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0A7E40 800A7240 2401000A */  li    $at, 10
/* 0A7E44 800A7244 14410014 */  bne   $v0, $at, .L800A7298
/* 0A7E48 800A7248 00000000 */   nop   
/* 0A7E4C 800A724C 0C006B95 */  jal   func_8001AE54
/* 0A7E50 800A7250 AFA3002C */   sw    $v1, 0x2c($sp)
/* 0A7E54 800A7254 8FB80020 */  lw    $t8, 0x20($sp)
/* 0A7E58 800A7258 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0A7E5C 800A725C 27190008 */  addiu $t9, $t8, 8
/* 0A7E60 800A7260 0059082B */  sltu  $at, $v0, $t9
/* 0A7E64 800A7264 1020000C */  beqz  $at, .L800A7298
/* 0A7E68 800A7268 00000000 */   nop   
/* 0A7E6C 800A726C 3C058012 */  lui   $a1, %hi(D_80126D44) # $a1, 0x8012
/* 0A7E70 800A7270 24A56D44 */  addiu $a1, %lo(D_80126D44) # addiu $a1, $a1, 0x6d44
/* 0A7E74 800A7274 8CAA0000 */  lw    $t2, ($a1)
/* 0A7E78 800A7278 00000000 */  nop   
/* 0A7E7C 800A727C 15400006 */  bnez  $t2, .L800A7298
/* 0A7E80 800A7280 00000000 */   nop   
/* 0A7E84 800A7284 240400FE */  li    $a0, 254
/* 0A7E88 800A7288 0C000741 */  jal   play_sound_global
/* 0A7E8C 800A728C AFA3002C */   sw    $v1, 0x2c($sp)
/* 0A7E90 800A7290 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0A7E94 800A7294 00000000 */  nop   
.L800A7298:
/* 0A7E98 800A7298 04610002 */  bgez  $v1, .L800A72A4
/* 0A7E9C 800A729C 2409000A */   li    $t1, 10
/* 0A7EA0 800A72A0 00001825 */  move  $v1, $zero
.L800A72A4:
/* 0A7EA4 800A72A4 0069001A */  div   $zero, $v1, $t1
/* 0A7EA8 800A72A8 15200002 */  bnez  $t1, .L800A72B4
/* 0A7EAC 800A72AC 00000000 */   nop   
/* 0A7EB0 800A72B0 0007000D */  break 7
.L800A72B4:
/* 0A7EB4 800A72B4 2401FFFF */  li    $at, -1
/* 0A7EB8 800A72B8 15210004 */  bne   $t1, $at, .L800A72CC
/* 0A7EBC 800A72BC 3C018000 */   lui   $at, 0x8000
/* 0A7EC0 800A72C0 14610002 */  bne   $v1, $at, .L800A72CC
/* 0A7EC4 800A72C4 00000000 */   nop   
/* 0A7EC8 800A72C8 0006000D */  break 6
.L800A72CC:
/* 0A7ECC 800A72CC 00001012 */  mflo  $v0
/* 0A7ED0 800A72D0 1040001D */  beqz  $v0, .L800A7348
/* 0A7ED4 800A72D4 00000000 */   nop   
/* 0A7ED8 800A72D8 0069001A */  div   $zero, $v1, $t1
/* 0A7EDC 800A72DC 3C088012 */  lui   $t0, %hi(gCurrentHud) # $t0, 0x8012
/* 0A7EE0 800A72E0 25086CDC */  addiu $t0, %lo(gCurrentHud) # addiu $t0, $t0, 0x6cdc
/* 0A7EE4 800A72E4 8D0B0000 */  lw    $t3, ($t0)
/* 0A7EE8 800A72E8 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A7EEC 800A72EC A56202B8 */  sh    $v0, 0x2b8($t3)
/* 0A7EF0 800A72F0 8D0D0000 */  lw    $t5, ($t0)
/* 0A7EF4 800A72F4 15200002 */  bnez  $t1, .L800A7300
/* 0A7EF8 800A72F8 00000000 */   nop   
/* 0A7EFC 800A72FC 0007000D */  break 7
.L800A7300:
/* 0A7F00 800A7300 2401FFFF */  li    $at, -1
/* 0A7F04 800A7304 15210004 */  bne   $t1, $at, .L800A7318
/* 0A7F08 800A7308 3C018000 */   lui   $at, 0x8000
/* 0A7F0C 800A730C 14610002 */  bne   $v1, $at, .L800A7318
/* 0A7F10 800A7310 00000000 */   nop   
/* 0A7F14 800A7314 0006000D */  break 6
.L800A7318:
/* 0A7F18 800A7318 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A7F1C 800A731C 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A7F20 800A7320 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A7F24 800A7324 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A7F28 800A7328 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A7F2C 800A732C 00006010 */  mfhi  $t4
/* 0A7F30 800A7330 A5AC02D8 */  sh    $t4, 0x2d8($t5)
/* 0A7F34 800A7334 8D070000 */  lw    $a3, ($t0)
/* 0A7F38 800A7338 0C02A980 */  jal   func_800AA600
/* 0A7F3C 800A733C 24E702C0 */   addiu $a3, $a3, 0x2c0
/* 0A7F40 800A7340 10000010 */  b     .L800A7384
/* 0A7F44 800A7344 00000000 */   nop   
.L800A7348:
/* 0A7F48 800A7348 0069001A */  div   $zero, $v1, $t1
/* 0A7F4C 800A734C 3C0F8012 */  lui   $t7, %hi(gCurrentHud) # $t7, 0x8012
/* 0A7F50 800A7350 8DEF6CDC */  lw    $t7, %lo(gCurrentHud)($t7)
/* 0A7F54 800A7354 15200002 */  bnez  $t1, .L800A7360
/* 0A7F58 800A7358 00000000 */   nop   
/* 0A7F5C 800A735C 0007000D */  break 7
.L800A7360:
/* 0A7F60 800A7360 2401FFFF */  li    $at, -1
/* 0A7F64 800A7364 15210004 */  bne   $t1, $at, .L800A7378
/* 0A7F68 800A7368 3C018000 */   lui   $at, 0x8000
/* 0A7F6C 800A736C 14610002 */  bne   $v1, $at, .L800A7378
/* 0A7F70 800A7370 00000000 */   nop   
/* 0A7F74 800A7374 0006000D */  break 6
.L800A7378:
/* 0A7F78 800A7378 00007010 */  mfhi  $t6
/* 0A7F7C 800A737C A5EE02B8 */  sh    $t6, 0x2b8($t7)
/* 0A7F80 800A7380 00000000 */  nop   
.L800A7384:
/* 0A7F84 800A7384 3C078012 */  lui   $a3, %hi(gCurrentHud) # $a3, 0x8012
/* 0A7F88 800A7388 8CE76CDC */  lw    $a3, %lo(gCurrentHud)($a3)
/* 0A7F8C 800A738C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A7F90 800A7390 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A7F94 800A7394 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A7F98 800A7398 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A7F9C 800A739C 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A7FA0 800A73A0 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A7FA4 800A73A4 0C02A980 */  jal   func_800AA600
/* 0A7FA8 800A73A8 24E702A0 */   addiu $a3, $a3, 0x2a0
/* 0A7FAC 800A73AC 0C019826 */  jal   set_viewport_tv_type
/* 0A7FB0 800A73B0 24040001 */   li    $a0, 1
/* 0A7FB4 800A73B4 3C188000 */  lui   $t8, %hi(osTvType) # $t8, 0x8000
/* 0A7FB8 800A73B8 8F180300 */  lw    $t8, %lo(osTvType)($t8)
/* 0A7FBC 800A73BC 00000000 */  nop   
/* 0A7FC0 800A73C0 17000003 */  bnez  $t8, .L800A73D0
/* 0A7FC4 800A73C4 00000000 */   nop   
/* 0A7FC8 800A73C8 0C01EFC7 */  jal   func_8007BF1C
/* 0A7FCC 800A73CC 24040001 */   li    $a0, 1
.L800A73D0:
/* 0A7FD0 800A73D0 3C078012 */  lui   $a3, %hi(gCurrentHud) # $a3, 0x8012
/* 0A7FD4 800A73D4 8CE76CDC */  lw    $a3, %lo(gCurrentHud)($a3)
/* 0A7FD8 800A73D8 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A7FDC 800A73DC 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A7FE0 800A73E0 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A7FE4 800A73E4 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A7FE8 800A73E8 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A7FEC 800A73EC 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A7FF0 800A73F0 0C02A980 */  jal   func_800AA600
/* 0A7FF4 800A73F4 24E70260 */   addiu $a3, $a3, 0x260
/* 0A7FF8 800A73F8 0C01EFC7 */  jal   func_8007BF1C
/* 0A7FFC 800A73FC 00002025 */   move  $a0, $zero
/* 0A8000 800A7400 0C019826 */  jal   set_viewport_tv_type
/* 0A8004 800A7404 00002025 */   move  $a0, $zero
/* 0A8008 800A7408 3C078012 */  lui   $a3, %hi(gCurrentHud) # $a3, 0x8012
/* 0A800C 800A740C 8CE76CDC */  lw    $a3, %lo(gCurrentHud)($a3)
/* 0A8010 800A7410 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A8014 800A7414 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A8018 800A7418 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A801C 800A741C 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A8020 800A7420 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A8024 800A7424 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A8028 800A7428 0C02A980 */  jal   func_800AA600
/* 0A802C 800A742C 24E70280 */   addiu $a3, $a3, 0x280
/* 0A8030 800A7430 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0A8034 800A7434 27BD0030 */  addiu $sp, $sp, 0x30
/* 0A8038 800A7438 03E00008 */  jr    $ra
/* 0A803C 800A743C 00000000 */   nop   

