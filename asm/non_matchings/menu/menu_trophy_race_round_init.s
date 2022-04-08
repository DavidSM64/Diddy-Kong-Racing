glabel menu_trophy_race_round_init
/* 098E6C 8009826C 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 098E70 80098270 AFBF0024 */  sw    $ra, 0x24($sp)
/* 098E74 80098274 AFB30020 */  sw    $s3, 0x20($sp)
/* 098E78 80098278 AFB2001C */  sw    $s2, 0x1c($sp)
/* 098E7C 8009827C AFB10018 */  sw    $s1, 0x18($sp)
/* 098E80 80098280 0C01BAA4 */  jal   get_settings
/* 098E84 80098284 AFB00014 */   sw    $s0, 0x14($sp)
/* 098E88 80098288 00408825 */  move  $s1, $v0
/* 098E8C 8009828C 0C0078A7 */  jal   get_misc_asset
/* 098E90 80098290 2404001A */   li    $a0, 26
/* 098E94 80098294 3C03800E */  lui   $v1, %hi(gTrophyRaceRound) # $v1, 0x800e
/* 098E98 80098298 8C630FEC */  lw    $v1, %lo(gTrophyRaceRound)($v1)
/* 098E9C 8009829C 3C0E800E */  lui   $t6, %hi(gTrophyRaceWorldId) # $t6, 0x800e
/* 098EA0 800982A0 1460000E */  bnez  $v1, .L800982DC
/* 098EA4 800982A4 3C13800E */   lui   $s3, %hi(gNumberOfActivePlayers) # $s3, 0x800e
/* 098EA8 800982A8 00008025 */  move  $s0, $zero
/* 098EAC 800982AC 02201825 */  move  $v1, $s1
/* 098EB0 800982B0 24040008 */  li    $a0, 8
.L800982B4:
/* 098EB4 800982B4 26100004 */  addiu $s0, $s0, 4
/* 098EB8 800982B8 AC60006C */  sw    $zero, 0x6c($v1)
/* 098EBC 800982BC AC600084 */  sw    $zero, 0x84($v1)
/* 098EC0 800982C0 AC60009C */  sw    $zero, 0x9c($v1)
/* 098EC4 800982C4 24630060 */  addiu $v1, $v1, 0x60
/* 098EC8 800982C8 1604FFFA */  bne   $s0, $a0, .L800982B4
/* 098ECC 800982CC AC60FFF4 */   sw    $zero, -0xc($v1)
/* 098ED0 800982D0 3C03800E */  lui   $v1, %hi(gTrophyRaceRound) # $v1, 0x800e
/* 098ED4 800982D4 8C630FEC */  lw    $v1, %lo(gTrophyRaceRound)($v1)
/* 098ED8 800982D8 00000000 */  nop   
.L800982DC:
/* 098EDC 800982DC 8DCE0FE8 */  lw    $t6, %lo(gTrophyRaceWorldId)($t6)
/* 098EE0 800982E0 2673F4BC */  addiu $s3, %lo(gNumberOfActivePlayers) # addiu $s3, $s3, -0xb44
/* 098EE4 800982E4 000E7880 */  sll   $t7, $t6, 2
/* 098EE8 800982E8 01EE7823 */  subu  $t7, $t7, $t6
/* 098EEC 800982EC 000F7840 */  sll   $t7, $t7, 1
/* 098EF0 800982F0 01E3C021 */  addu  $t8, $t7, $v1
/* 098EF4 800982F4 0302C821 */  addu  $t9, $t8, $v0
/* 098EF8 800982F8 8324FFFA */  lb    $a0, -6($t9)
/* 098EFC 800982FC 2403FFFF */  li    $v1, -1
.L80098300:
/* 098F00 80098300 14830004 */  bne   $a0, $v1, .L80098314
/* 098F04 80098304 00808025 */   move  $s0, $a0
/* 098F08 80098308 26100001 */  addiu $s0, $s0, 1
/* 098F0C 8009830C 32080003 */  andi  $t0, $s0, 3
/* 098F10 80098310 01008025 */  move  $s0, $t0
.L80098314:
/* 098F14 80098314 1203FFFA */  beq   $s0, $v1, .L80098300
/* 098F18 80098318 00000000 */   nop   
/* 098F1C 8009831C 8E690000 */  lw    $t1, ($s3)
/* 098F20 80098320 00008825 */  move  $s1, $zero
/* 098F24 80098324 1920000A */  blez  $t1, .L80098350
/* 098F28 80098328 3C128012 */   lui   $s2, %hi(gPlayerSelectVehicle) # $s2, 0x8012
/* 098F2C 8009832C 265269C0 */  addiu $s2, %lo(gPlayerSelectVehicle) # addiu $s2, $s2, 0x69c0
.L80098330:
/* 098F30 80098330 0C01AC2B */  jal   func_8006B0AC
/* 098F34 80098334 02002025 */   move  $a0, $s0
/* 098F38 80098338 8E6A0000 */  lw    $t2, ($s3)
/* 098F3C 8009833C 26310001 */  addiu $s1, $s1, 1
/* 098F40 80098340 022A082A */  slt   $at, $s1, $t2
/* 098F44 80098344 26520001 */  addiu $s2, $s2, 1
/* 098F48 80098348 1420FFF9 */  bnez  $at, .L80098330
/* 098F4C 8009834C A242FFFF */   sb    $v0, -1($s2)
.L80098350:
/* 098F50 80098350 0C01AC2B */  jal   func_8006B0AC
/* 098F54 80098354 02002025 */   move  $a0, $s0
/* 098F58 80098358 0C01B6C5 */  jal   func_8006DB14
/* 098F5C 8009835C 00402025 */   move  $a0, $v0
/* 098F60 80098360 02002025 */  move  $a0, $s0
/* 098F64 80098364 2405FFFF */  li    $a1, -1
/* 098F68 80098368 0C01B8BA */  jal   load_level_for_menu
/* 098F6C 8009836C 24060001 */   li    $a2, 1
/* 098F70 80098370 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 098F74 80098374 AC20F47C */  sw    $zero, %lo(gMenuDelay)($at)
/* 098F78 80098378 3C01800E */  lui   $at, %hi(D_800E0980) # $at, 0x800e
/* 098F7C 8009837C 240B000A */  li    $t3, 10
/* 098F80 80098380 AC2B0980 */  sw    $t3, %lo(D_800E0980)($at)
/* 098F84 80098384 0C03105C */  jal   load_font
/* 098F88 80098388 24040002 */   li    $a0, 2
/* 098F8C 8009838C 0C0002F8 */  jal   set_music_player_voice_limit
/* 098F90 80098390 24040018 */   li    $a0, 24
/* 098F94 80098394 0C0002CD */  jal   play_music
/* 098F98 80098398 24040018 */   li    $a0, 24
/* 098F9C 8009839C 0C000326 */  jal   set_music_fade_timer
/* 098FA0 800983A0 24040100 */   li    $a0, 256
/* 098FA4 800983A4 8FBF0024 */  lw    $ra, 0x24($sp)
/* 098FA8 800983A8 8FB00014 */  lw    $s0, 0x14($sp)
/* 098FAC 800983AC 8FB10018 */  lw    $s1, 0x18($sp)
/* 098FB0 800983B0 8FB2001C */  lw    $s2, 0x1c($sp)
/* 098FB4 800983B4 8FB30020 */  lw    $s3, 0x20($sp)
/* 098FB8 800983B8 03E00008 */  jr    $ra
/* 098FBC 800983BC 27BD0028 */   addiu $sp, $sp, 0x28

