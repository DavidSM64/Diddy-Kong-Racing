glabel func_8008B4C8
/* 08C0C8 8008B4C8 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 08C0CC 8008B4CC AFB40028 */  sw    $s4, 0x28($sp)
/* 08C0D0 8008B4D0 AFB1001C */  sw    $s1, 0x1c($sp)
/* 08C0D4 8008B4D4 AFB00018 */  sw    $s0, 0x18($sp)
/* 08C0D8 8008B4D8 3C118012 */  lui   $s1, %hi(gActivePlayersArray) # $s1, 0x8012
/* 08C0DC 8008B4DC 3C148012 */  lui   $s4, %hi(D_801267D8) # $s4, 0x8012
/* 08C0E0 8008B4E0 AFBF003C */  sw    $ra, 0x3c($sp)
/* 08C0E4 8008B4E4 AFBE0038 */  sw    $fp, 0x38($sp)
/* 08C0E8 8008B4E8 AFB70034 */  sw    $s7, 0x34($sp)
/* 08C0EC 8008B4EC AFB60030 */  sw    $s6, 0x30($sp)
/* 08C0F0 8008B4F0 AFB5002C */  sw    $s5, 0x2c($sp)
/* 08C0F4 8008B4F4 AFB30024 */  sw    $s3, 0x24($sp)
/* 08C0F8 8008B4F8 AFB20020 */  sw    $s2, 0x20($sp)
/* 08C0FC 8008B4FC 00001025 */  move  $v0, $zero
/* 08C100 8008B500 269467D8 */  addiu $s4, %lo(D_801267D8) # addiu $s4, $s4, 0x67d8
/* 08C104 8008B504 263163D4 */  addiu $s1, %lo(gActivePlayersArray) # addiu $s1, $s1, 0x63d4
/* 08C108 8008B508 00008025 */  move  $s0, $zero
.L8008B50C:
/* 08C10C 8008B50C 822E0000 */  lb    $t6, ($s1)
/* 08C110 8008B510 00107880 */  sll   $t7, $s0, 2
/* 08C114 8008B514 11C00004 */  beqz  $t6, .L8008B528
/* 08C118 8008B518 028FC021 */   addu  $t8, $s4, $t7
/* 08C11C 8008B51C 8F190000 */  lw    $t9, ($t8)
/* 08C120 8008B520 00000000 */  nop   
/* 08C124 8008B524 00591025 */  or    $v0, $v0, $t9
.L8008B528:
/* 08C128 8008B528 26100001 */  addiu $s0, $s0, 1
/* 08C12C 8008B52C 2A010004 */  slti  $at, $s0, 4
/* 08C130 8008B530 1420FFF6 */  bnez  $at, .L8008B50C
/* 08C134 8008B534 26310001 */   addiu $s1, $s1, 1
/* 08C138 8008B538 30489000 */  andi  $t0, $v0, 0x9000
/* 08C13C 8008B53C 11000047 */  beqz  $t0, .L8008B65C
/* 08C140 8008B540 00008025 */   move  $s0, $zero
/* 08C144 8008B544 24120001 */  li    $s2, 1
/* 08C148 8008B548 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08C14C 8008B54C 0C01BAEA */  jal   func_8006EBA8
/* 08C150 8008B550 AC32F47C */   sw    $s2, %lo(gMenuDelay)($at)
/* 08C154 8008B554 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 08C158 8008B558 0C030076 */  jal   func_800C01D8
/* 08C15C 8008B55C 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 08C160 8008B560 3C028012 */  lui   $v0, %hi(D_801267D8) # $v0, 0x8012
/* 08C164 8008B564 2411FFFF */  li    $s1, -1
/* 08C168 8008B568 244267D8 */  addiu $v0, %lo(D_801267D8) # addiu $v0, $v0, 0x67d8
/* 08C16C 8008B56C 00008025 */  move  $s0, $zero
.L8008B570:
/* 08C170 8008B570 8C490000 */  lw    $t1, ($v0)
/* 08C174 8008B574 00000000 */  nop   
/* 08C178 8008B578 312A9000 */  andi  $t2, $t1, 0x9000
/* 08C17C 8008B57C 11400002 */  beqz  $t2, .L8008B588
/* 08C180 8008B580 00000000 */   nop   
/* 08C184 8008B584 02008825 */  move  $s1, $s0
.L8008B588:
/* 08C188 8008B588 26100001 */  addiu $s0, $s0, 1
/* 08C18C 8008B58C 2A0B0004 */  slti  $t3, $s0, 4
/* 08C190 8008B590 2A2C0000 */  slti  $t4, $s1, 0
/* 08C194 8008B594 016C6824 */  and   $t5, $t3, $t4
/* 08C198 8008B598 15A0FFF5 */  bnez  $t5, .L8008B570
/* 08C19C 8008B59C 24420004 */   addiu $v0, $v0, 4
/* 08C1A0 8008B5A0 3C178012 */  lui   $s7, %hi(D_80126808) # $s7, 0x8012
/* 08C1A4 8008B5A4 26F76808 */  addiu $s7, %lo(D_80126808) # addiu $s7, $s7, 0x6808
/* 08C1A8 8008B5A8 00117080 */  sll   $t6, $s1, 2
/* 08C1AC 8008B5AC 02EE8021 */  addu  $s0, $s7, $t6
/* 08C1B0 8008B5B0 8E040000 */  lw    $a0, ($s0)
/* 08C1B4 8008B5B4 00000000 */  nop   
/* 08C1B8 8008B5B8 10800003 */  beqz  $a0, .L8008B5C8
/* 08C1BC 8008B5BC 00000000 */   nop   
/* 08C1C0 8008B5C0 0C001223 */  jal   func_8000488C
/* 08C1C4 8008B5C4 00000000 */   nop   
.L8008B5C8:
/* 08C1C8 8008B5C8 3C188012 */  lui   $t8, %hi(gPlayersCharacterArray) # $t8, 0x8012
/* 08C1CC 8008B5CC 0311C021 */  addu  $t8, $t8, $s1
/* 08C1D0 8008B5D0 831863E8 */  lb    $t8, %lo(gPlayersCharacterArray)($t8)
/* 08C1D4 8008B5D4 3C1E8012 */  lui   $fp, %hi(D_801263CC) # $fp, 0x8012
/* 08C1D8 8008B5D8 27DE63CC */  addiu $fp, %lo(D_801263CC) # addiu $fp, $fp, 0x63cc
/* 08C1DC 8008B5DC 0018C8C0 */  sll   $t9, $t8, 3
/* 08C1E0 8008B5E0 8FCF0000 */  lw    $t7, ($fp)
/* 08C1E4 8008B5E4 0338C823 */  subu  $t9, $t9, $t8
/* 08C1E8 8008B5E8 0019C840 */  sll   $t9, $t9, 1
/* 08C1EC 8008B5EC 01F94021 */  addu  $t0, $t7, $t9
/* 08C1F0 8008B5F0 8504000C */  lh    $a0, 0xc($t0)
/* 08C1F4 8008B5F4 02002825 */  move  $a1, $s0
/* 08C1F8 8008B5F8 2484019E */  addiu $a0, $a0, 0x19e
/* 08C1FC 8008B5FC 3089FFFF */  andi  $t1, $a0, 0xffff
/* 08C200 8008B600 0C000741 */  jal   play_sound_global
/* 08C204 8008B604 01202025 */   move  $a0, $t1
/* 08C208 8008B608 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 08C20C 8008B60C 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 08C210 8008B610 00000000 */  nop   
/* 08C214 8008B614 28410003 */  slti  $at, $v0, 3
/* 08C218 8008B618 1020000C */  beqz  $at, .L8008B64C
/* 08C21C 8008B61C 28410002 */   slti  $at, $v0, 2
/* 08C220 8008B620 14200005 */  bnez  $at, .L8008B638
/* 08C224 8008B624 3C0A800E */   lui   $t2, %hi(gActiveMagicCodes) # $t2, 0x800e
/* 08C228 8008B628 8D4AFD98 */  lw    $t2, %lo(gActiveMagicCodes)($t2)
/* 08C22C 8008B62C 00000000 */  nop   
/* 08C230 8008B630 000A59C0 */  sll   $t3, $t2, 7
/* 08C234 8008B634 05610005 */  bgez  $t3, .L8008B64C
.L8008B638:
/* 08C238 8008B638 3C0C800E */   lui   $t4, %hi(D_800DFFD0) # $t4, 0x800e
/* 08C23C 8008B63C 8D8CFFD0 */  lw    $t4, %lo(D_800DFFD0)($t4)
/* 08C240 8008B640 00000000 */  nop   
/* 08C244 8008B644 164C0039 */  bne   $s2, $t4, .L8008B72C
/* 08C248 8008B648 8FBF003C */   lw    $ra, 0x3c($sp)
.L8008B64C:
/* 08C24C 8008B64C 0C000326 */  jal   set_music_fade_timer
/* 08C250 8008B650 2404FF80 */   li    $a0, -128
/* 08C254 8008B654 10000035 */  b     .L8008B72C
/* 08C258 8008B658 8FBF003C */   lw    $ra, 0x3c($sp)
.L8008B65C:
/* 08C25C 8008B65C 3C118012 */  lui   $s1, %hi(gActivePlayersArray) # $s1, 0x8012
/* 08C260 8008B660 3C1E8012 */  lui   $fp, %hi(D_801263CC) # $fp, 0x8012
/* 08C264 8008B664 3C178012 */  lui   $s7, %hi(D_80126808) # $s7, 0x8012
/* 08C268 8008B668 3C158012 */  lui   $s5, %hi(D_801263DC) # $s5, 0x8012
/* 08C26C 8008B66C 3C13800E */  lui   $s3, %hi(gNumberOfReadyPlayers) # $s3, 0x800e
/* 08C270 8008B670 2673F480 */  addiu $s3, %lo(gNumberOfReadyPlayers) # addiu $s3, $s3, -0xb80
/* 08C274 8008B674 26B563DC */  addiu $s5, %lo(D_801263DC) # addiu $s5, $s5, 0x63dc
/* 08C278 8008B678 26F76808 */  addiu $s7, %lo(D_80126808) # addiu $s7, $s7, 0x6808
/* 08C27C 8008B67C 27DE63CC */  addiu $fp, %lo(D_801263CC) # addiu $fp, $fp, 0x63cc
/* 08C280 8008B680 263163D4 */  addiu $s1, %lo(gActivePlayersArray) # addiu $s1, $s1, 0x63d4
/* 08C284 8008B684 24160004 */  li    $s6, 4
.L8008B688:
/* 08C288 8008B688 822D0000 */  lb    $t5, ($s1)
/* 08C28C 8008B68C 02B01821 */  addu  $v1, $s5, $s0
/* 08C290 8008B690 11A00022 */  beqz  $t5, .L8008B71C
/* 08C294 8008B694 00000000 */   nop   
/* 08C298 8008B698 806E0000 */  lb    $t6, ($v1)
/* 08C29C 8008B69C 00101080 */  sll   $v0, $s0, 2
/* 08C2A0 8008B6A0 11C0001E */  beqz  $t6, .L8008B71C
/* 08C2A4 8008B6A4 0282C021 */   addu  $t8, $s4, $v0
/* 08C2A8 8008B6A8 8F0F0000 */  lw    $t7, ($t8)
/* 08C2AC 8008B6AC 02E22821 */  addu  $a1, $s7, $v0
/* 08C2B0 8008B6B0 31F94000 */  andi  $t9, $t7, 0x4000
/* 08C2B4 8008B6B4 13200019 */  beqz  $t9, .L8008B71C
/* 08C2B8 8008B6B8 3C0A8012 */   lui   $t2, %hi(gPlayersCharacterArray) # $t2, 0x8012
/* 08C2BC 8008B6BC 8E680000 */  lw    $t0, ($s3)
/* 08C2C0 8008B6C0 8CA40000 */  lw    $a0, ($a1)
/* 08C2C4 8008B6C4 254A63E8 */  addiu $t2, %lo(gPlayersCharacterArray) # addiu $t2, $t2, 0x63e8
/* 08C2C8 8008B6C8 2509FFFF */  addiu $t1, $t0, -1
/* 08C2CC 8008B6CC A0600000 */  sb    $zero, ($v1)
/* 08C2D0 8008B6D0 AE690000 */  sw    $t1, ($s3)
/* 08C2D4 8008B6D4 10800005 */  beqz  $a0, .L8008B6EC
/* 08C2D8 8008B6D8 020A9021 */   addu  $s2, $s0, $t2
/* 08C2DC 8008B6DC 0C001223 */  jal   func_8000488C
/* 08C2E0 8008B6E0 AFA50044 */   sw    $a1, 0x44($sp)
/* 08C2E4 8008B6E4 8FA50044 */  lw    $a1, 0x44($sp)
/* 08C2E8 8008B6E8 00000000 */  nop   
.L8008B6EC:
/* 08C2EC 8008B6EC 824C0000 */  lb    $t4, ($s2)
/* 08C2F0 8008B6F0 8FCB0000 */  lw    $t3, ($fp)
/* 08C2F4 8008B6F4 000C68C0 */  sll   $t5, $t4, 3
/* 08C2F8 8008B6F8 01AC6823 */  subu  $t5, $t5, $t4
/* 08C2FC 8008B6FC 000D6840 */  sll   $t5, $t5, 1
/* 08C300 8008B700 016D7021 */  addu  $t6, $t3, $t5
/* 08C304 8008B704 85C4000C */  lh    $a0, 0xc($t6)
/* 08C308 8008B708 00000000 */  nop   
/* 08C30C 8008B70C 24840093 */  addiu $a0, $a0, 0x93
/* 08C310 8008B710 3098FFFF */  andi  $t8, $a0, 0xffff
/* 08C314 8008B714 0C000741 */  jal   play_sound_global
/* 08C318 8008B718 03002025 */   move  $a0, $t8
.L8008B71C:
/* 08C31C 8008B71C 26100001 */  addiu $s0, $s0, 1
/* 08C320 8008B720 1616FFD9 */  bne   $s0, $s6, .L8008B688
/* 08C324 8008B724 26310001 */   addiu $s1, $s1, 1
/* 08C328 8008B728 8FBF003C */  lw    $ra, 0x3c($sp)
.L8008B72C:
/* 08C32C 8008B72C 8FB00018 */  lw    $s0, 0x18($sp)
/* 08C330 8008B730 8FB1001C */  lw    $s1, 0x1c($sp)
/* 08C334 8008B734 8FB20020 */  lw    $s2, 0x20($sp)
/* 08C338 8008B738 8FB30024 */  lw    $s3, 0x24($sp)
/* 08C33C 8008B73C 8FB40028 */  lw    $s4, 0x28($sp)
/* 08C340 8008B740 8FB5002C */  lw    $s5, 0x2c($sp)
/* 08C344 8008B744 8FB60030 */  lw    $s6, 0x30($sp)
/* 08C348 8008B748 8FB70034 */  lw    $s7, 0x34($sp)
/* 08C34C 8008B74C 8FBE0038 */  lw    $fp, 0x38($sp)
/* 08C350 8008B750 03E00008 */  jr    $ra
/* 08C354 8008B754 27BD0060 */   addiu $sp, $sp, 0x60

