glabel menu_track_select_loop
/* 08FE34 8008F234 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 08FE38 8008F238 AFBF0014 */  sw    $ra, 0x14($sp)
/* 08FE3C 8008F23C 0C01BAA4 */  jal   get_settings
/* 08FE40 8008F240 AFA40020 */   sw    $a0, 0x20($sp)
/* 08FE44 8008F244 3C038012 */  lui   $v1, %hi(D_801263BC) # $v1, 0x8012
/* 08FE48 8008F248 246363BC */  addiu $v1, %lo(D_801263BC) # addiu $v1, $v1, 0x63bc
/* 08FE4C 8008F24C 8C6E0000 */  lw    $t6, ($v1)
/* 08FE50 8008F250 8FAF0020 */  lw    $t7, 0x20($sp)
/* 08FE54 8008F254 AFA20018 */  sw    $v0, 0x18($sp)
/* 08FE58 8008F258 01CFC021 */  addu  $t8, $t6, $t7
/* 08FE5C 8008F25C 3319003F */  andi  $t9, $t8, 0x3f
/* 08FE60 8008F260 0C031CF8 */  jal   get_thread30_level_id_to_load
/* 08FE64 8008F264 AC790000 */   sw    $t9, ($v1)
/* 08FE68 8008F268 14400011 */  bnez  $v0, .L8008F2B0
/* 08FE6C 8008F26C 3C03800E */   lui   $v1, %hi(gMenuDelay) # $v1, 0x800e
/* 08FE70 8008F270 2463F47C */  addiu $v1, %lo(gMenuDelay) # addiu $v1, $v1, -0xb84
/* 08FE74 8008F274 8C620000 */  lw    $v0, ($v1)
/* 08FE78 8008F278 00000000 */  nop   
/* 08FE7C 8008F27C 1040000C */  beqz  $v0, .L8008F2B0
/* 08FE80 8008F280 00000000 */   nop   
/* 08FE84 8008F284 04410007 */  bgez  $v0, .L8008F2A4
/* 08FE88 8008F288 8FAA0020 */   lw    $t2, 0x20($sp)
/* 08FE8C 8008F28C 8FA80020 */  lw    $t0, 0x20($sp)
/* 08FE90 8008F290 00000000 */  nop   
/* 08FE94 8008F294 00484823 */  subu  $t1, $v0, $t0
/* 08FE98 8008F298 10000005 */  b     .L8008F2B0
/* 08FE9C 8008F29C AC690000 */   sw    $t1, ($v1)
/* 08FEA0 8008F2A0 8FAA0020 */  lw    $t2, 0x20($sp)
.L8008F2A4:
/* 08FEA4 8008F2A4 00000000 */  nop   
/* 08FEA8 8008F2A8 004A5821 */  addu  $t3, $v0, $t2
/* 08FEAC 8008F2AC AC6B0000 */  sw    $t3, ($v1)
.L8008F2B0:
/* 08FEB0 8008F2B0 0C02393B */  jal   func_8008E4EC
/* 08FEB4 8008F2B4 00000000 */   nop   
/* 08FEB8 8008F2B8 3C058012 */  lui   $a1, %hi(D_801263A0) # $a1, 0x8012
/* 08FEBC 8008F2BC 24A563A0 */  addiu $a1, %lo(D_801263A0) # addiu $a1, $a1, 0x63a0
/* 08FEC0 8008F2C0 8CA30000 */  lw    $v1, ($a1)
/* 08FEC4 8008F2C4 3C0DB600 */  lui   $t5, 0xb600
/* 08FEC8 8008F2C8 246C0008 */  addiu $t4, $v1, 8
/* 08FECC 8008F2CC ACAC0000 */  sw    $t4, ($a1)
/* 08FED0 8008F2D0 240E1000 */  li    $t6, 4096
/* 08FED4 8008F2D4 3C048012 */  lui   $a0, %hi(D_801267D0) # $a0, 0x8012
/* 08FED8 8008F2D8 AC6E0004 */  sw    $t6, 4($v1)
/* 08FEDC 8008F2DC AC6D0000 */  sw    $t5, ($v1)
/* 08FEE0 8008F2E0 8C8467D0 */  lw    $a0, %lo(D_801267D0)($a0)
/* 08FEE4 8008F2E4 24010001 */  li    $at, 1
/* 08FEE8 8008F2E8 10800005 */  beqz  $a0, .L8008F300
/* 08FEEC 8008F2EC 00000000 */   nop   
/* 08FEF0 8008F2F0 1081000F */  beq   $a0, $at, .L8008F330
/* 08FEF4 8008F2F4 8FA40020 */   lw    $a0, 0x20($sp)
/* 08FEF8 8008F2F8 10000015 */  b     .L8008F350
/* 08FEFC 8008F2FC 00000000 */   nop   
.L8008F300:
/* 08FF00 8008F300 8FA40020 */  lw    $a0, 0x20($sp)
/* 08FF04 8008F304 0C023FC7 */  jal   func_8008FF1C
/* 08FF08 8008F308 00000000 */   nop   
/* 08FF0C 8008F30C 8FA40020 */  lw    $a0, 0x20($sp)
/* 08FF10 8008F310 0C02413A */  jal   func_800904E8
/* 08FF14 8008F314 00000000 */   nop   
/* 08FF18 8008F318 8FA40020 */  lw    $a0, 0x20($sp)
/* 08FF1C 8008F31C 0C024246 */  jal   func_80090918
/* 08FF20 8008F320 00000000 */   nop   
/* 08FF24 8008F324 1000000A */  b     .L8008F350
/* 08FF28 8008F328 00000000 */   nop   
/* 08FF2C 8008F32C 8FA40020 */  lw    $a0, 0x20($sp)
.L8008F330:
/* 08FF30 8008F330 0C0243B6 */  jal   func_80090ED8
/* 08FF34 8008F334 00000000 */   nop   
/* 08FF38 8008F338 8FA40020 */  lw    $a0, 0x20($sp)
/* 08FF3C 8008F33C 0C0243CC */  jal   render_track_select_setup_ui
/* 08FF40 8008F340 00000000 */   nop   
/* 08FF44 8008F344 8FA40020 */  lw    $a0, 0x20($sp)
/* 08FF48 8008F348 0C024862 */  jal   func_80092188
/* 08FF4C 8008F34C 00000000 */   nop   
.L8008F350:
/* 08FF50 8008F350 3C03800E */  lui   $v1, %hi(D_800DF760) # $v1, 0x800e
/* 08FF54 8008F354 2463F760 */  addiu $v1, %lo(D_800DF760) # addiu $v1, $v1, -0x8a0
/* 08FF58 8008F358 8C620000 */  lw    $v0, ($v1)
/* 08FF5C 8008F35C 8FAF0020 */  lw    $t7, 0x20($sp)
/* 08FF60 8008F360 04410005 */  bgez  $v0, .L8008F378
/* 08FF64 8008F364 000FC040 */   sll   $t8, $t7, 1
/* 08FF68 8008F368 0C000664 */  jal   set_relative_volume_for_music
/* 08FF6C 8008F36C 00002025 */   move  $a0, $zero
/* 08FF70 8008F370 1000000A */  b     .L8008F39C
/* 08FF74 8008F374 00000000 */   nop   
.L8008F378:
/* 08FF78 8008F378 0058C821 */  addu  $t9, $v0, $t8
/* 08FF7C 8008F37C 2B210051 */  slti  $at, $t9, 0x51
/* 08FF80 8008F380 AC790000 */  sw    $t9, ($v1)
/* 08FF84 8008F384 14200003 */  bnez  $at, .L8008F394
/* 08FF88 8008F388 03201025 */   move  $v0, $t9
/* 08FF8C 8008F38C 24020050 */  li    $v0, 80
/* 08FF90 8008F390 AC620000 */  sw    $v0, ($v1)
.L8008F394:
/* 08FF94 8008F394 0C000664 */  jal   set_relative_volume_for_music
/* 08FF98 8008F398 304400FF */   andi  $a0, $v0, 0xff
.L8008F39C:
/* 08FF9C 8008F39C 3C028012 */  lui   $v0, %hi(D_801267D0) # $v0, 0x8012
/* 08FFA0 8008F3A0 8C4267D0 */  lw    $v0, %lo(D_801267D0)($v0)
/* 08FFA4 8008F3A4 00000000 */  nop   
/* 08FFA8 8008F3A8 0441002F */  bgez  $v0, .L8008F468
/* 08FFAC 8008F3AC 28410002 */   slti  $at, $v0, 2
/* 08FFB0 8008F3B0 0C023D4D */  jal   func_8008F534
/* 08FFB4 8008F3B4 00000000 */   nop   
/* 08FFB8 8008F3B8 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 08FFBC 8008F3BC 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 08FFC0 8008F3C0 3C01800E */  lui   $at, %hi(D_800DF478) # $at, 0x800e
/* 08FFC4 8008F3C4 AC20F478 */  sw    $zero, %lo(D_800DF478)($at)
/* 08FFC8 8008F3C8 28410003 */  slti  $at, $v0, 3
/* 08FFCC 8008F3CC 10200008 */  beqz  $at, .L8008F3F0
/* 08FFD0 8008F3D0 24010002 */   li    $at, 2
/* 08FFD4 8008F3D4 1441001C */  bne   $v0, $at, .L8008F448
/* 08FFD8 8008F3D8 3C09800E */   lui   $t1, %hi(gActiveMagicCodes) # $t1, 0x800e
/* 08FFDC 8008F3DC 8D29FD98 */  lw    $t1, %lo(gActiveMagicCodes)($t1)
/* 08FFE0 8008F3E0 00000000 */  nop   
/* 08FFE4 8008F3E4 000951C0 */  sll   $t2, $t1, 7
/* 08FFE8 8008F3E8 05400018 */  bltz  $t2, .L8008F44C
/* 08FFEC 8008F3EC 24040027 */   li    $a0, 39
.L8008F3F0:
/* 08FFF0 8008F3F0 0C027B34 */  jal   is_drumstick_unlocked
/* 08FFF4 8008F3F4 AFA0001C */   sw    $zero, 0x1c($sp)
/* 08FFF8 8008F3F8 8FA6001C */  lw    $a2, 0x1c($sp)
/* 08FFFC 8008F3FC 10400002 */  beqz  $v0, .L8008F408
/* 090000 8008F400 00000000 */   nop   
/* 090004 8008F404 24060001 */  li    $a2, 1
.L8008F408:
/* 090008 8008F408 0C027B2E */  jal   is_tt_unlocked
/* 09000C 8008F40C AFA6001C */   sw    $a2, 0x1c($sp)
/* 090010 8008F410 8FA6001C */  lw    $a2, 0x1c($sp)
/* 090014 8008F414 10400003 */  beqz  $v0, .L8008F424
/* 090018 8008F418 24040016 */   li    $a0, 22
/* 09001C 8008F41C 38CB0003 */  xori  $t3, $a2, 3
/* 090020 8008F420 01603025 */  move  $a2, $t3
.L8008F424:
/* 090024 8008F424 0C01B8BA */  jal   load_level_for_menu
/* 090028 8008F428 2405FFFF */   li    $a1, -1
/* 09002C 8008F42C 00002025 */  move  $a0, $zero
/* 090030 8008F430 0C022BAD */  jal   func_8008AEB4
/* 090034 8008F434 00002825 */   move  $a1, $zero
/* 090038 8008F438 0C0204F4 */  jal   menu_init
/* 09003C 8008F43C 24040003 */   li    $a0, 3
/* 090040 8008F440 10000038 */  b     .L8008F524
/* 090044 8008F444 00001025 */   move  $v0, $zero
.L8008F448:
/* 090048 8008F448 24040027 */  li    $a0, 39
.L8008F44C:
/* 09004C 8008F44C 2405FFFF */  li    $a1, -1
/* 090050 8008F450 0C01B8BA */  jal   load_level_for_menu
/* 090054 8008F454 00003025 */   move  $a2, $zero
/* 090058 8008F458 0C0204F4 */  jal   menu_init
/* 09005C 8008F45C 24040013 */   li    $a0, 19
/* 090060 8008F460 10000030 */  b     .L8008F524
/* 090064 8008F464 00001025 */   move  $v0, $zero
.L8008F468:
/* 090068 8008F468 1420002C */  bnez  $at, .L8008F51C
/* 09006C 8008F46C 00001025 */   move  $v0, $zero
/* 090070 8008F470 0C023D4D */  jal   func_8008F534
/* 090074 8008F474 00000000 */   nop   
/* 090078 8008F478 3C0C800E */  lui   $t4, %hi(gMultiplayerSelectedNumberOfRacers) # $t4, 0x800e
/* 09007C 8008F47C 3C0D8012 */  lui   $t5, %hi(gMultiplayerSelectedNumberOfRacersCopy) # $t5, 0x8012
/* 090080 8008F480 8DAD6548 */  lw    $t5, %lo(gMultiplayerSelectedNumberOfRacersCopy)($t5)
/* 090084 8008F484 8D8C0410 */  lw    $t4, %lo(gMultiplayerSelectedNumberOfRacers)($t4)
/* 090088 8008F488 00003025 */  move  $a2, $zero
/* 09008C 8008F48C 118D000D */  beq   $t4, $t5, .L8008F4C4
/* 090090 8008F490 3C198012 */   lui   $t9, %hi(D_801269C8) # $t9, 0x8012
/* 090094 8008F494 8FA20018 */  lw    $v0, 0x18($sp)
/* 090098 8008F498 24030008 */  li    $v1, 8
.L8008F49C:
/* 09009C 8008F49C 24CE0001 */  addiu $t6, $a2, 1
/* 0900A0 8008F4A0 24CF0002 */  addiu $t7, $a2, 2
/* 0900A4 8008F4A4 24D80003 */  addiu $t8, $a2, 3
/* 0900A8 8008F4A8 A046005A */  sb    $a2, 0x5a($v0)
/* 0900AC 8008F4AC 24C60004 */  addiu $a2, $a2, 4
/* 0900B0 8008F4B0 A05800A2 */  sb    $t8, 0xa2($v0)
/* 0900B4 8008F4B4 A04F008A */  sb    $t7, 0x8a($v0)
/* 0900B8 8008F4B8 A04E0072 */  sb    $t6, 0x72($v0)
/* 0900BC 8008F4BC 14C3FFF7 */  bne   $a2, $v1, .L8008F49C
/* 0900C0 8008F4C0 24420060 */   addiu $v0, $v0, 0x60
.L8008F4C4:
/* 0900C4 8008F4C4 8F3969C8 */  lw    $t9, %lo(D_801269C8)($t9)
/* 0900C8 8008F4C8 24010004 */  li    $at, 4
/* 0900CC 8008F4CC 13210007 */  beq   $t9, $at, .L8008F4EC
/* 0900D0 8008F4D0 3C098012 */   lui   $t1, %hi(D_801269CC) # $t1, 0x8012
/* 0900D4 8008F4D4 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 0900D8 8008F4D8 24080001 */  li    $t0, 1
/* 0900DC 8008F4DC 3C01800E */  lui   $at, %hi(D_800DF478) # $at, 0x800e
/* 0900E0 8008F4E0 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 0900E4 8008F4E4 1000000F */  b     .L8008F524
/* 0900E8 8008F4E8 AC28F478 */   sw    $t0, %lo(D_800DF478)($at)
.L8008F4EC:
/* 0900EC 8008F4EC 8D2969CC */  lw    $t1, %lo(D_801269CC)($t1)
/* 0900F0 8008F4F0 3C01800E */  lui   $at, %hi(gTrophyRaceWorldId) # $at, 0x800e
/* 0900F4 8008F4F4 252A0001 */  addiu $t2, $t1, 1
/* 0900F8 8008F4F8 AC2A0FE8 */  sw    $t2, %lo(gTrophyRaceWorldId)($at)
/* 0900FC 8008F4FC 3C01800E */  lui   $at, %hi(D_800DF450) # $at, 0x800e
/* 090100 8008F500 A020F450 */  sb    $zero, %lo(D_800DF450)($at)
/* 090104 8008F504 3C01800E */  lui   $at, %hi(D_800E0FEC) # $at, 0x800e
/* 090108 8008F508 AC200FEC */  sw    $zero, %lo(D_800E0FEC)($at)
/* 09010C 8008F50C 0C0204F4 */  jal   menu_init
/* 090110 8008F510 24040014 */   li    $a0, 20
/* 090114 8008F514 10000003 */  b     .L8008F524
/* 090118 8008F518 00001025 */   move  $v0, $zero
.L8008F51C:
/* 09011C 8008F51C 3C018012 */  lui   $at, %hi(gIgnorePlayerInput) # $at, 0x8012
/* 090120 8008F520 AC2063C4 */  sw    $zero, %lo(gIgnorePlayerInput)($at)
.L8008F524:
/* 090124 8008F524 8FBF0014 */  lw    $ra, 0x14($sp)
/* 090128 8008F528 27BD0020 */  addiu $sp, $sp, 0x20
/* 09012C 8008F52C 03E00008 */  jr    $ra
/* 090130 8008F530 00000000 */   nop   

