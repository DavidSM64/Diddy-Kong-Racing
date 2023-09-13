.late_rodata
glabel D_800E8718
.float 275.0

.text
glabel func_800A1248
/* 0A1E48 800A1248 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0A1E4C 800A124C AFBF002C */  sw    $ra, 0x2c($sp)
/* 0A1E50 800A1250 AFB30028 */  sw    $s3, 0x28($sp)
/* 0A1E54 800A1254 AFB20024 */  sw    $s2, 0x24($sp)
/* 0A1E58 800A1258 AFB10020 */  sw    $s1, 0x20($sp)
/* 0A1E5C 800A125C AFB0001C */  sw    $s0, 0x1c($sp)
/* 0A1E60 800A1260 E7B50010 */  swc1  $f21, 0x10($sp)
/* 0A1E64 800A1264 E7B40014 */  swc1  $f20, 0x14($sp)
/* 0A1E68 800A1268 AFA5004C */  sw    $a1, 0x4c($sp)
/* 0A1E6C 800A126C AFA60050 */  sw    $a2, 0x50($sp)
/* 0A1E70 800A1270 8CA70064 */  lw    $a3, 0x64($a1)
/* 0A1E74 800A1274 00808025 */  move  $s0, $a0
/* 0A1E78 800A1278 27A4003C */  addiu $a0, $sp, 0x3c
/* 0A1E7C 800A127C 0C006E9D */  jal   get_racer_objects
/* 0A1E80 800A1280 AFA70044 */   sw    $a3, 0x44($sp)
/* 0A1E84 800A1284 00409025 */  move  $s2, $v0
/* 0A1E88 800A1288 0C01A142 */  jal   func_80068508
/* 0A1E8C 800A128C 24040001 */   li    $a0, 1
/* 0A1E90 800A1290 8FA50050 */  lw    $a1, 0x50($sp)
/* 0A1E94 800A1294 0C028F39 */  jal   render_race_start
/* 0A1E98 800A1298 02002025 */   move  $a0, $s0
/* 0A1E9C 800A129C 3C028012 */  lui   $v0, %hi(gNumActivePlayers) # $v0, 0x8012
/* 0A1EA0 800A12A0 90426D37 */  lbu   $v0, %lo(gNumActivePlayers)($v0)
/* 0A1EA4 800A12A4 8FA70044 */  lw    $a3, 0x44($sp)
/* 0A1EA8 800A12A8 24130001 */  li    $s3, 1
/* 0A1EAC 800A12AC 10530007 */  beq   $v0, $s3, .L800A12CC
/* 0A1EB0 800A12B0 24010003 */   li    $at, 3
/* 0A1EB4 800A12B4 10410041 */  beq   $v0, $at, .L800A13BC
/* 0A1EB8 800A12B8 24010004 */   li    $at, 4
/* 0A1EBC 800A12BC 1041003F */  beq   $v0, $at, .L800A13BC
/* 0A1EC0 800A12C0 00000000 */   nop   
/* 0A1EC4 800A12C4 10000040 */  b     .L800A13C8
/* 0A1EC8 800A12C8 8FA8004C */   lw    $t0, 0x4c($sp)
.L800A12CC:
/* 0A1ECC 800A12CC 8FAF003C */  lw    $t7, 0x3c($sp)
/* 0A1ED0 800A12D0 00008825 */  move  $s1, $zero
/* 0A1ED4 800A12D4 19E00029 */  blez  $t7, .L800A137C
/* 0A1ED8 800A12D8 02408025 */   move  $s0, $s2
/* 0A1EDC 800A12DC 3C01425C */  li    $at, 0x425C0000 # 55.000000
/* 0A1EE0 800A12E0 3C128012 */  lui   $s2, %hi(gCurrentHud) # $s2, 0x8012
/* 0A1EE4 800A12E4 4481A000 */  mtc1  $at, $f20
/* 0A1EE8 800A12E8 26526CDC */  addiu $s2, %lo(gCurrentHud) # addiu $s2, $s2, 0x6cdc
.L800A12EC:
/* 0A1EEC 800A12EC 8E180000 */  lw    $t8, ($s0)
/* 0A1EF0 800A12F0 00000000 */  nop   
/* 0A1EF4 800A12F4 8F040064 */  lw    $a0, 0x64($t8)
/* 0A1EF8 800A12F8 0C02917C */  jal   render_treasure_hud
/* 0A1EFC 800A12FC 00000000 */   nop   
/* 0A1F00 800A1300 1633000D */  bne   $s1, $s3, .L800A1338
/* 0A1F04 800A1304 00000000 */   nop   
/* 0A1F08 800A1308 8E420000 */  lw    $v0, ($s2)
/* 0A1F0C 800A130C 00000000 */  nop   
/* 0A1F10 800A1310 C444064C */  lwc1  $f4, 0x64c($v0)
/* 0A1F14 800A1314 00000000 */  nop   
/* 0A1F18 800A1318 46142180 */  add.s $f6, $f4, $f20
/* 0A1F1C 800A131C E446064C */  swc1  $f6, 0x64c($v0)
/* 0A1F20 800A1320 8E420000 */  lw    $v0, ($s2)
/* 0A1F24 800A1324 00000000 */  nop   
/* 0A1F28 800A1328 C448040C */  lwc1  $f8, 0x40c($v0)
/* 0A1F2C 800A132C 00000000 */  nop   
/* 0A1F30 800A1330 46144280 */  add.s $f10, $f8, $f20
/* 0A1F34 800A1334 E44A040C */  swc1  $f10, 0x40c($v0)
.L800A1338:
/* 0A1F38 800A1338 8E420000 */  lw    $v0, ($s2)
/* 0A1F3C 800A133C 26310001 */  addiu $s1, $s1, 1
/* 0A1F40 800A1340 C450064C */  lwc1  $f16, 0x64c($v0)
/* 0A1F44 800A1344 26100004 */  addiu $s0, $s0, 4
/* 0A1F48 800A1348 46148480 */  add.s $f18, $f16, $f20
/* 0A1F4C 800A134C E452064C */  swc1  $f18, 0x64c($v0)
/* 0A1F50 800A1350 8E420000 */  lw    $v0, ($s2)
/* 0A1F54 800A1354 00000000 */  nop   
/* 0A1F58 800A1358 C444040C */  lwc1  $f4, 0x40c($v0)
/* 0A1F5C 800A135C 00000000 */  nop   
/* 0A1F60 800A1360 46142180 */  add.s $f6, $f4, $f20
/* 0A1F64 800A1364 E446040C */  swc1  $f6, 0x40c($v0)
/* 0A1F68 800A1368 8FB9003C */  lw    $t9, 0x3c($sp)
/* 0A1F6C 800A136C 00000000 */  nop   
/* 0A1F70 800A1370 0239082A */  slt   $at, $s1, $t9
/* 0A1F74 800A1374 1420FFDD */  bnez  $at, .L800A12EC
/* 0A1F78 800A1378 00000000 */   nop   
.L800A137C:
/* 0A1F7C 800A137C 3C128012 */  lui   $s2, %hi(gCurrentHud) # $s2, 0x8012
/* 0A1F80 800A1380 26526CDC */  addiu $s2, %lo(gCurrentHud) # addiu $s2, $s2, 0x6cdc
/* 0A1F84 800A1384 8E420000 */  lw    $v0, ($s2)
/* 0A1F88 800A1388 3C01800F */  lui   $at, %hi(D_800E8718) # $at, 0x800f
/* 0A1F8C 800A138C C4208718 */  lwc1  $f0, %lo(D_800E8718)($at)
/* 0A1F90 800A1390 C448064C */  lwc1  $f8, 0x64c($v0)
/* 0A1F94 800A1394 00000000 */  nop   
/* 0A1F98 800A1398 46004281 */  sub.s $f10, $f8, $f0
/* 0A1F9C 800A139C E44A064C */  swc1  $f10, 0x64c($v0)
/* 0A1FA0 800A13A0 8E420000 */  lw    $v0, ($s2)
/* 0A1FA4 800A13A4 00000000 */  nop   
/* 0A1FA8 800A13A8 C450040C */  lwc1  $f16, 0x40c($v0)
/* 0A1FAC 800A13AC 00000000 */  nop   
/* 0A1FB0 800A13B0 46008481 */  sub.s $f18, $f16, $f0
/* 0A1FB4 800A13B4 10000003 */  b     .L800A13C4
/* 0A1FB8 800A13B8 E452040C */   swc1  $f18, 0x40c($v0)
.L800A13BC:
/* 0A1FBC 800A13BC 0C02917C */  jal   render_treasure_hud
/* 0A1FC0 800A13C0 00E02025 */   move  $a0, $a3
.L800A13C4:
/* 0A1FC4 800A13C4 8FA8004C */  lw    $t0, 0x4c($sp)
.L800A13C8:
/* 0A1FC8 800A13C8 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A1FCC 800A13CC 8D070064 */  lw    $a3, 0x64($t0)
/* 0A1FD0 800A13D0 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A1FD4 800A13D4 0C01ECF4 */  jal   reset_render_settings
/* 0A1FD8 800A13D8 AFA70044 */   sw    $a3, 0x44($sp)
/* 0A1FDC 800A13DC 8FA40044 */  lw    $a0, 0x44($sp)
/* 0A1FE0 800A13E0 8FA50050 */  lw    $a1, 0x50($sp)
/* 0A1FE4 800A13E4 0C029055 */  jal   render_racer_bananas
/* 0A1FE8 800A13E8 00000000 */   nop   
/* 0A1FEC 800A13EC 8FA4004C */  lw    $a0, 0x4c($sp)
/* 0A1FF0 800A13F0 8FA50050 */  lw    $a1, 0x50($sp)
/* 0A1FF4 800A13F4 0C029D48 */  jal   render_weapon_hud
/* 0A1FF8 800A13F8 00000000 */   nop   
/* 0A1FFC 800A13FC 0C01A142 */  jal   func_80068508
/* 0A2000 800A1400 00002025 */   move  $a0, $zero
/* 0A2004 800A1404 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0A2008 800A1408 C7B50010 */  lwc1  $f21, 0x10($sp)
/* 0A200C 800A140C C7B40014 */  lwc1  $f20, 0x14($sp)
/* 0A2010 800A1410 8FB0001C */  lw    $s0, 0x1c($sp)
/* 0A2014 800A1414 8FB10020 */  lw    $s1, 0x20($sp)
/* 0A2018 800A1418 8FB20024 */  lw    $s2, 0x24($sp)
/* 0A201C 800A141C 8FB30028 */  lw    $s3, 0x28($sp)
/* 0A2020 800A1420 03E00008 */  jr    $ra
/* 0A2024 800A1424 27BD0048 */   addiu $sp, $sp, 0x48

