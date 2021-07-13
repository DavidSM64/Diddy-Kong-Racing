glabel menu_game_select_loop
/* 08D3BC 8008C7BC 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 08D3C0 8008C7C0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 08D3C4 8008C7C4 0C02305A */  jal   func_8008C168
/* 08D3C8 8008C7C8 AFA40028 */   sw    $a0, 0x28($sp)
/* 08D3CC 8008C7CC 3C038012 */  lui   $v1, %hi(D_801263BC) # $v1, 0x8012
/* 08D3D0 8008C7D0 246363BC */  addiu $v1, %lo(D_801263BC) # addiu $v1, $v1, 0x63bc
/* 08D3D4 8008C7D4 8FA40028 */  lw    $a0, 0x28($sp)
/* 08D3D8 8008C7D8 8C6E0000 */  lw    $t6, ($v1)
/* 08D3DC 8008C7DC 3C058012 */  lui   $a1, %hi(D_801263D8) # $a1, 0x8012
/* 08D3E0 8008C7E0 24A563D8 */  addiu $a1, %lo(D_801263D8) # addiu $a1, $a1, 0x63d8
/* 08D3E4 8008C7E4 8CA20000 */  lw    $v0, ($a1)
/* 08D3E8 8008C7E8 01C47821 */  addu  $t7, $t6, $a0
/* 08D3EC 8008C7EC 31F8003F */  andi  $t8, $t7, 0x3f
/* 08D3F0 8008C7F0 1040000B */  beqz  $v0, .L8008C820
/* 08D3F4 8008C7F4 AC780000 */   sw    $t8, ($v1)
/* 08D3F8 8008C7F8 24590001 */  addiu $t9, $v0, 1
/* 08D3FC 8008C7FC 2B210003 */  slti  $at, $t9, 3
/* 08D400 8008C800 14200007 */  bnez  $at, .L8008C820
/* 08D404 8008C804 ACB90000 */   sw    $t9, ($a1)
/* 08D408 8008C808 0C020A2E */  jal   func_800828B8
/* 08D40C 8008C80C AFA40028 */   sw    $a0, 0x28($sp)
/* 08D410 8008C810 3C058012 */  lui   $a1, %hi(D_801263D8) # $a1, 0x8012
/* 08D414 8008C814 24A563D8 */  addiu $a1, %lo(D_801263D8) # addiu $a1, $a1, 0x63d8
/* 08D418 8008C818 8FA40028 */  lw    $a0, 0x28($sp)
/* 08D41C 8008C81C ACA00000 */  sw    $zero, ($a1)
.L8008C820:
/* 08D420 8008C820 3C03800E */  lui   $v1, %hi(gMenuDelay) # $v1, 0x800e
/* 08D424 8008C824 2463F47C */  addiu $v1, %lo(gMenuDelay) # addiu $v1, $v1, -0xb84
/* 08D428 8008C828 8C620000 */  lw    $v0, ($v1)
/* 08D42C 8008C82C 00000000 */  nop   
/* 08D430 8008C830 1040000A */  beqz  $v0, .L8008C85C
/* 08D434 8008C834 2841001F */   slti  $at, $v0, 0x1f
/* 08D438 8008C838 04410005 */  bgez  $v0, .L8008C850
/* 08D43C 8008C83C 00445021 */   addu  $t2, $v0, $a0
/* 08D440 8008C840 00444823 */  subu  $t1, $v0, $a0
/* 08D444 8008C844 AC690000 */  sw    $t1, ($v1)
/* 08D448 8008C848 10000003 */  b     .L8008C858
/* 08D44C 8008C84C 01201025 */   move  $v0, $t1
.L8008C850:
/* 08D450 8008C850 AC6A0000 */  sw    $t2, ($v1)
/* 08D454 8008C854 01401025 */  move  $v0, $t2
.L8008C858:
/* 08D458 8008C858 2841001F */  slti  $at, $v0, 0x1f
.L8008C85C:
/* 08D45C 8008C85C 14200023 */  bnez  $at, .L8008C8EC
/* 08D460 8008C860 2841FFE2 */   slti  $at, $v0, -0x1e
/* 08D464 8008C864 0C0232B3 */  jal   func_8008CACC
/* 08D468 8008C868 00000000 */   nop   
/* 08D46C 8008C86C 3C02800E */  lui   $v0, %hi(D_800DF460) # $v0, 0x800e
/* 08D470 8008C870 3C0B8012 */  lui   $t3, %hi(D_801263E0) # $t3, 0x8012
/* 08D474 8008C874 8D6B63E0 */  lw    $t3, %lo(D_801263E0)($t3)
/* 08D478 8008C878 8C42F460 */  lw    $v0, %lo(D_800DF460)($v0)
/* 08D47C 8008C87C 3C01800E */  lui   $at, %hi(gIsInAdventureTwo) # $at, 0x800e
/* 08D480 8008C880 1562000F */  bne   $t3, $v0, .L8008C8C0
/* 08D484 8008C884 00002025 */   move  $a0, $zero
/* 08D488 8008C888 0C0002CA */  jal   func_80000B28
/* 08D48C 8008C88C 00000000 */   nop   
/* 08D490 8008C890 240C0001 */  li    $t4, 1
/* 08D494 8008C894 3C01800E */  lui   $at, %hi(gIsInAdventureTwo) # $at, 0x800e
/* 08D498 8008C898 0C01B96F */  jal   func_8006E5BC
/* 08D49C 8008C89C AC2CF4B8 */   sw    $t4, %lo(gIsInTracksMode)($at)
/* 08D4A0 8008C8A0 2404FFFF */  li    $a0, -1
/* 08D4A4 8008C8A4 2405FFFF */  li    $a1, -1
/* 08D4A8 8008C8A8 0C01B8BA */  jal   load_level_for_menu
/* 08D4AC 8008C8AC 00003025 */   move  $a2, $zero
/* 08D4B0 8008C8B0 0C0204F4 */  jal   menu_init
/* 08D4B4 8008C8B4 2404000F */   li    $a0, 15
/* 08D4B8 8008C8B8 10000080 */  b     .L8008CABC
/* 08D4BC 8008C8BC 00001025 */   move  $v0, $zero
.L8008C8C0:
/* 08D4C0 8008C8C0 AC22F494 */  sw    $v0, %lo(gIsInAdventureTwo)($at)
/* 08D4C4 8008C8C4 3C01800E */  lui   $at, %hi(gIsInTracksMode) # $at, 0x800e
/* 08D4C8 8008C8C8 AC20F4B8 */  sw    $zero, %lo(gIsInTracksMode)($at)
/* 08D4CC 8008C8CC 3C018012 */  lui   $at, %hi(gPlayerSelectVehicle) # $at, 0x8012
/* 08D4D0 8008C8D0 0C01B6C5 */  jal   func_8006DB14
/* 08D4D4 8008C8D4 A02069C0 */   sb    $zero, %lo(gPlayerSelectVehicle)($at)
/* 08D4D8 8008C8D8 0C0204F4 */  jal   menu_init
/* 08D4DC 8008C8DC 24040006 */   li    $a0, 6
/* 08D4E0 8008C8E0 10000076 */  b     .L8008CABC
/* 08D4E4 8008C8E4 00001025 */   move  $v0, $zero
/* 08D4E8 8008C8E8 2841FFE2 */  slti  $at, $v0, -0x1e
.L8008C8EC:
/* 08D4EC 8008C8EC 10200019 */  beqz  $at, .L8008C954
/* 08D4F0 8008C8F0 00000000 */   nop   
/* 08D4F4 8008C8F4 0C0232B3 */  jal   func_8008CACC
/* 08D4F8 8008C8F8 00000000 */   nop   
/* 08D4FC 8008C8FC 0C027B34 */  jal   is_drumstick_unlocked
/* 08D500 8008C900 AFA0001C */   sw    $zero, 0x1c($sp)
/* 08D504 8008C904 8FA6001C */  lw    $a2, 0x1c($sp)
/* 08D508 8008C908 10400002 */  beqz  $v0, .L8008C914
/* 08D50C 8008C90C 00000000 */   nop   
/* 08D510 8008C910 24060001 */  li    $a2, 1
.L8008C914:
/* 08D514 8008C914 0C027B2E */  jal   is_tt_unlocked
/* 08D518 8008C918 AFA6001C */   sw    $a2, 0x1c($sp)
/* 08D51C 8008C91C 8FA6001C */  lw    $a2, 0x1c($sp)
/* 08D520 8008C920 10400003 */  beqz  $v0, .L8008C930
/* 08D524 8008C924 24040016 */   li    $a0, 22
/* 08D528 8008C928 38CD0003 */  xori  $t5, $a2, 3
/* 08D52C 8008C92C 01A03025 */  move  $a2, $t5
.L8008C930:
/* 08D530 8008C930 0C01B8BA */  jal   load_level_for_menu
/* 08D534 8008C934 2405FFFF */   li    $a1, -1
/* 08D538 8008C938 00002025 */  move  $a0, $zero
/* 08D53C 8008C93C 0C022BAD */  jal   func_8008AEB4
/* 08D540 8008C940 00002825 */   move  $a1, $zero
/* 08D544 8008C944 0C0204F4 */  jal   menu_init
/* 08D548 8008C948 24040003 */   li    $a0, 3
/* 08D54C 8008C94C 1000005B */  b     .L8008CABC
/* 08D550 8008C950 00001025 */   move  $v0, $zero
.L8008C954:
/* 08D554 8008C954 0C0231A6 */  jal   func_8008C698
/* 08D558 8008C958 00000000 */   nop   
/* 08D55C 8008C95C 3C0E800E */  lui   $t6, %hi(gMenuDelay) # $t6, 0x800e
/* 08D560 8008C960 8DCEF47C */  lw    $t6, %lo(gMenuDelay)($t6)
/* 08D564 8008C964 3C058012 */  lui   $a1, %hi(D_801263D8) # $a1, 0x8012
/* 08D568 8008C968 15C00051 */  bnez  $t6, .L8008CAB0
/* 08D56C 8008C96C 24A563D8 */   addiu $a1, %lo(D_801263D8) # addiu $a1, $a1, 0x63d8
/* 08D570 8008C970 8CAF0000 */  lw    $t7, ($a1)
/* 08D574 8008C974 00000000 */  nop   
/* 08D578 8008C978 15E0004D */  bnez  $t7, .L8008CAB0
/* 08D57C 8008C97C 00000000 */   nop   
/* 08D580 8008C980 0C01A955 */  jal   get_button_inputs_from_player
/* 08D584 8008C984 00002025 */   move  $a0, $zero
/* 08D588 8008C988 3C18800E */  lui   $t8, %hi(gNumberOfActivePlayers) # $t8, 0x800e
/* 08D58C 8008C98C 8F18F4BC */  lw    $t8, %lo(gNumberOfActivePlayers)($t8)
/* 08D590 8008C990 3C068012 */  lui   $a2, %hi(gControllersYAxisDirection) # $a2, 0x8012
/* 08D594 8008C994 80C66464 */  lb    $a2, %lo(gControllersYAxisDirection)($a2)
/* 08D598 8008C998 24010002 */  li    $at, 2
/* 08D59C 8008C99C 1701000B */  bne   $t8, $at, .L8008C9CC
/* 08D5A0 8008C9A0 00401825 */   move  $v1, $v0
/* 08D5A4 8008C9A4 24040001 */  li    $a0, 1
/* 08D5A8 8008C9A8 AFA20024 */  sw    $v0, 0x24($sp)
/* 08D5AC 8008C9AC 0C01A955 */  jal   get_button_inputs_from_player
/* 08D5B0 8008C9B0 AFA60020 */   sw    $a2, 0x20($sp)
/* 08D5B4 8008C9B4 3C198012 */  lui   $t9, %hi(gControllersYAxisDirection+1) # $t9, 0x8012
/* 08D5B8 8008C9B8 8FA30024 */  lw    $v1, 0x24($sp)
/* 08D5BC 8008C9BC 8FA60020 */  lw    $a2, 0x20($sp)
/* 08D5C0 8008C9C0 83396465 */  lb    $t9, %lo(gControllersYAxisDirection+1)($t9)
/* 08D5C4 8008C9C4 00621825 */  or    $v1, $v1, $v0
/* 08D5C8 8008C9C8 00D93021 */  addu  $a2, $a2, $t9
.L8008C9CC:
/* 08D5CC 8008C9CC 30689000 */  andi  $t0, $v1, 0x9000
/* 08D5D0 8008C9D0 11000015 */  beqz  $t0, .L8008CA28
/* 08D5D4 8008C9D4 306C4000 */   andi  $t4, $v1, 0x4000
/* 08D5D8 8008C9D8 3C098012 */  lui   $t1, %hi(D_801263E0) # $t1, 0x8012
/* 08D5DC 8008C9DC 3C0A800E */  lui   $t2, %hi(D_800DF460) # $t2, 0x800e
/* 08D5E0 8008C9E0 8D4AF460 */  lw    $t2, %lo(D_800DF460)($t2)
/* 08D5E4 8008C9E4 8D2963E0 */  lw    $t1, %lo(D_801263E0)($t1)
/* 08D5E8 8008C9E8 00000000 */  nop   
/* 08D5EC 8008C9EC 152A0003 */  bne   $t1, $t2, .L8008C9FC
/* 08D5F0 8008C9F0 00000000 */   nop   
/* 08D5F4 8008C9F4 0C000326 */  jal   func_80000C98
/* 08D5F8 8008C9F8 2404FF80 */   li    $a0, -128
.L8008C9FC:
/* 08D5FC 8008C9FC 3C04800E */  lui   $a0, %hi(D_800DF774) # $a0, 0x800e
/* 08D600 8008CA00 0C030076 */  jal   func_800C01D8
/* 08D604 8008CA04 2484F774 */   addiu $a0, %lo(D_800DF774) # addiu $a0, $a0, -0x88c
/* 08D608 8008CA08 240B0001 */  li    $t3, 1
/* 08D60C 8008CA0C 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08D610 8008CA10 AC2BF47C */  sw    $t3, %lo(gMenuDelay)($at)
/* 08D614 8008CA14 240400EF */  li    $a0, 239
/* 08D618 8008CA18 0C000741 */  jal   func_80001D04
/* 08D61C 8008CA1C 00002825 */   move  $a1, $zero
/* 08D620 8008CA20 10000023 */  b     .L8008CAB0
/* 08D624 8008CA24 00000000 */   nop   
.L8008CA28:
/* 08D628 8008CA28 11800007 */  beqz  $t4, .L8008CA48
/* 08D62C 8008CA2C 3C04800E */   lui   $a0, %hi(D_800DF774) # $a0, 0x800e
/* 08D630 8008CA30 0C030076 */  jal   func_800C01D8
/* 08D634 8008CA34 2484F774 */   addiu $a0, %lo(D_800DF774) # addiu $a0, $a0, -0x88c
/* 08D638 8008CA38 240DFFFF */  li    $t5, -1
/* 08D63C 8008CA3C 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08D640 8008CA40 1000001B */  b     .L8008CAB0
/* 08D644 8008CA44 AC2DF47C */   sw    $t5, %lo(gMenuDelay)($at)
.L8008CA48:
/* 08D648 8008CA48 04C1000F */  bgez  $a2, .L8008CA88
/* 08D64C 8008CA4C 3C03800E */   lui   $v1, %hi(D_800DF460) # $v1, 0x800e
/* 08D650 8008CA50 2463F460 */  addiu $v1, %lo(D_800DF460) # addiu $v1, $v1, -0xba0
/* 08D654 8008CA54 3C0E8012 */  lui   $t6, %hi(D_801263E0) # $t6, 0x8012
/* 08D658 8008CA58 8DCE63E0 */  lw    $t6, %lo(D_801263E0)($t6)
/* 08D65C 8008CA5C 8C620000 */  lw    $v0, ($v1)
/* 08D660 8008CA60 240400EB */  li    $a0, 235
/* 08D664 8008CA64 004E082A */  slt   $at, $v0, $t6
/* 08D668 8008CA68 10200007 */  beqz  $at, .L8008CA88
/* 08D66C 8008CA6C 244F0001 */   addiu $t7, $v0, 1
/* 08D670 8008CA70 AC6F0000 */  sw    $t7, ($v1)
/* 08D674 8008CA74 00002825 */  move  $a1, $zero
/* 08D678 8008CA78 0C000741 */  jal   func_80001D04
/* 08D67C 8008CA7C AFA60020 */   sw    $a2, 0x20($sp)
/* 08D680 8008CA80 8FA60020 */  lw    $a2, 0x20($sp)
/* 08D684 8008CA84 00000000 */  nop   
.L8008CA88:
/* 08D688 8008CA88 3C03800E */  lui   $v1, %hi(D_800DF460) # $v1, 0x800e
/* 08D68C 8008CA8C 18C00008 */  blez  $a2, .L8008CAB0
/* 08D690 8008CA90 2463F460 */   addiu $v1, %lo(D_800DF460) # addiu $v1, $v1, -0xba0
/* 08D694 8008CA94 8C620000 */  lw    $v0, ($v1)
/* 08D698 8008CA98 240400EB */  li    $a0, 235
/* 08D69C 8008CA9C 18400004 */  blez  $v0, .L8008CAB0
/* 08D6A0 8008CAA0 2458FFFF */   addiu $t8, $v0, -1
/* 08D6A4 8008CAA4 AC780000 */  sw    $t8, ($v1)
/* 08D6A8 8008CAA8 0C000741 */  jal   func_80001D04
/* 08D6AC 8008CAAC 00002825 */   move  $a1, $zero
.L8008CAB0:
/* 08D6B0 8008CAB0 3C018012 */  lui   $at, %hi(gIgnorePlayerInput) # $at, 0x8012
/* 08D6B4 8008CAB4 AC2063C4 */  sw    $zero, %lo(gIgnorePlayerInput)($at)
/* 08D6B8 8008CAB8 00001025 */  move  $v0, $zero
.L8008CABC:
/* 08D6BC 8008CABC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 08D6C0 8008CAC0 27BD0028 */  addiu $sp, $sp, 0x28
/* 08D6C4 8008CAC4 03E00008 */  jr    $ra
/* 08D6C8 8008CAC8 00000000 */   nop   

