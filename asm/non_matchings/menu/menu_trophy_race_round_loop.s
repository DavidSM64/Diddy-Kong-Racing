glabel menu_trophy_race_round_loop
/* 09919C 8009859C 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0991A0 800985A0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0991A4 800985A4 AFA40020 */  sw    $a0, 0x20($sp)
/* 0991A8 800985A8 0C0078A7 */  jal   get_misc_asset
/* 0991AC 800985AC 2404001A */   li    $a0, 26
/* 0991B0 800985B0 3C07800E */  lui   $a3, %hi(D_800E0980) # $a3, 0x800e
/* 0991B4 800985B4 24E70980 */  addiu $a3, %lo(D_800E0980) # addiu $a3, $a3, 0x980
/* 0991B8 800985B8 8CE30000 */  lw    $v1, ($a3)
/* 0991BC 800985BC 8FAE0020 */  lw    $t6, 0x20($sp)
/* 0991C0 800985C0 1060001A */  beqz  $v1, .L8009862C
/* 0991C4 800985C4 AFA2001C */   sw    $v0, 0x1c($sp)
/* 0991C8 800985C8 006E7823 */  subu  $t7, $v1, $t6
/* 0991CC 800985CC 1DE00017 */  bgtz  $t7, .L8009862C
/* 0991D0 800985D0 ACEF0000 */   sw    $t7, ($a3)
/* 0991D4 800985D4 3C19800E */  lui   $t9, %hi(gTrophyRaceWorldId) # $t9, 0x800e
/* 0991D8 800985D8 8F390FE8 */  lw    $t9, %lo(gTrophyRaceWorldId)($t9)
/* 0991DC 800985DC 3C09800E */  lui   $t1, %hi(D_800E0FEC) # $t1, 0x800e
/* 0991E0 800985E0 00194080 */  sll   $t0, $t9, 2
/* 0991E4 800985E4 8D290FEC */  lw    $t1, %lo(D_800E0FEC)($t1)
/* 0991E8 800985E8 01194023 */  subu  $t0, $t0, $t9
/* 0991EC 800985EC 00084040 */  sll   $t0, $t0, 1
/* 0991F0 800985F0 01095021 */  addu  $t2, $t0, $t1
/* 0991F4 800985F4 01425821 */  addu  $t3, $t2, $v0
/* 0991F8 800985F8 8163FFFA */  lb    $v1, -6($t3)
/* 0991FC 800985FC 3C06800E */  lui   $a2, %hi(D_800E0758) # $a2, 0x800e
/* 099200 80098600 00036040 */  sll   $t4, $v1, 1
/* 099204 80098604 00CC3021 */  addu  $a2, $a2, $t4
/* 099208 80098608 84C60758 */  lh    $a2, %lo(D_800E0758)($a2)
/* 09920C 8009860C 2401FFFF */  li    $at, -1
/* 099210 80098610 10C10005 */  beq   $a2, $at, .L80098628
/* 099214 80098614 30C4FFFF */   andi  $a0, $a2, 0xffff
/* 099218 80098618 0C000741 */  jal   func_80001D04
/* 09921C 8009861C 00002825 */   move  $a1, $zero
/* 099220 80098620 3C07800E */  lui   $a3, %hi(D_800E0980) # $a3, 0x800e
/* 099224 80098624 24E70980 */  addiu $a3, %lo(D_800E0980) # addiu $a3, $a3, 0x980
.L80098628:
/* 099228 80098628 ACE00000 */  sw    $zero, ($a3)
.L8009862C:
/* 09922C 8009862C 3C03800E */  lui   $v1, %hi(gMenuDelay) # $v1, 0x800e
/* 099230 80098630 2463F47C */  addiu $v1, %lo(gMenuDelay) # addiu $v1, $v1, -0xb84
/* 099234 80098634 8C620000 */  lw    $v0, ($v1)
/* 099238 80098638 8FAD0020 */  lw    $t5, 0x20($sp)
/* 09923C 8009863C 10400003 */  beqz  $v0, .L8009864C
/* 099240 80098640 004D7021 */   addu  $t6, $v0, $t5
/* 099244 80098644 AC6E0000 */  sw    $t6, ($v1)
/* 099248 80098648 01C01025 */  move  $v0, $t6
.L8009864C:
/* 09924C 8009864C 28410016 */  slti  $at, $v0, 0x16
/* 099250 80098650 10200006 */  beqz  $at, .L8009866C
/* 099254 80098654 00000000 */   nop   
/* 099258 80098658 8FA40020 */  lw    $a0, 0x20($sp)
/* 09925C 8009865C 0C0260F0 */  jal   func_800983C0
/* 099260 80098660 00000000 */   nop   
/* 099264 80098664 3C03800E */  lui   $v1, %hi(gMenuDelay) # $v1, 0x800e
/* 099268 80098668 2463F47C */  addiu $v1, %lo(gMenuDelay) # addiu $v1, $v1, -0xb84
.L8009866C:
/* 09926C 8009866C 3C0F8012 */  lui   $t7, %hi(gIgnorePlayerInput) # $t7, 0x8012
/* 099270 80098670 8DEF63C4 */  lw    $t7, %lo(gIgnorePlayerInput)($t7)
/* 099274 80098674 00000000 */  nop   
/* 099278 80098678 15E00014 */  bnez  $t7, .L800986CC
/* 09927C 8009867C 00000000 */   nop   
/* 099280 80098680 8C780000 */  lw    $t8, ($v1)
/* 099284 80098684 00000000 */  nop   
/* 099288 80098688 17000010 */  bnez  $t8, .L800986CC
/* 09928C 8009868C 00000000 */   nop   
/* 099290 80098690 0C02393B */  jal   func_8008E4EC
/* 099294 80098694 00000000 */   nop   
/* 099298 80098698 3C198012 */  lui   $t9, %hi(D_801267E8) # $t9, 0x8012
/* 09929C 8009869C 8F3967E8 */  lw    $t9, %lo(D_801267E8)($t9)
/* 0992A0 800986A0 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 0992A4 800986A4 33289000 */  andi  $t0, $t9, 0x9000
/* 0992A8 800986A8 11000008 */  beqz  $t0, .L800986CC
/* 0992AC 800986AC 00000000 */   nop   
/* 0992B0 800986B0 0C030076 */  jal   func_800C01D8
/* 0992B4 800986B4 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 0992B8 800986B8 24090001 */  li    $t1, 1
/* 0992BC 800986BC 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 0992C0 800986C0 AC29F47C */  sw    $t1, %lo(gMenuDelay)($at)
/* 0992C4 800986C4 0C000326 */  jal   set_music_fade_timer
/* 0992C8 800986C8 2404FF80 */   li    $a0, -128
.L800986CC:
/* 0992CC 800986CC 3C03800E */  lui   $v1, %hi(gMenuDelay) # $v1, 0x800e
/* 0992D0 800986D0 2463F47C */  addiu $v1, %lo(gMenuDelay) # addiu $v1, $v1, -0xb84
/* 0992D4 800986D4 8C6A0000 */  lw    $t2, ($v1)
/* 0992D8 800986D8 00001025 */  move  $v0, $zero
/* 0992DC 800986DC 2941001F */  slti  $at, $t2, 0x1f
/* 0992E0 800986E0 14200016 */  bnez  $at, .L8009873C
/* 0992E4 800986E4 00000000 */   nop   
/* 0992E8 800986E8 0C0261D5 */  jal   func_80098754
/* 0992EC 800986EC 00000000 */   nop   
/* 0992F0 800986F0 3C0B800E */  lui   $t3, %hi(gTrophyRaceWorldId) # $t3, 0x800e
/* 0992F4 800986F4 8D6B0FE8 */  lw    $t3, %lo(gTrophyRaceWorldId)($t3)
/* 0992F8 800986F8 3C0D800E */  lui   $t5, %hi(D_800E0FEC) # $t5, 0x800e
/* 0992FC 800986FC 000B6080 */  sll   $t4, $t3, 2
/* 099300 80098700 8DAD0FEC */  lw    $t5, %lo(D_800E0FEC)($t5)
/* 099304 80098704 018B6023 */  subu  $t4, $t4, $t3
/* 099308 80098708 8FAF001C */  lw    $t7, 0x1c($sp)
/* 09930C 8009870C 000C6040 */  sll   $t4, $t4, 1
/* 099310 80098710 018D7021 */  addu  $t6, $t4, $t5
/* 099314 80098714 01CFC021 */  addu  $t8, $t6, $t7
/* 099318 80098718 8319FFFA */  lb    $t9, -6($t8)
/* 09931C 8009871C 3C01800E */  lui   $at, %hi(gTrackIdToLoad) # $at, 0x800e
/* 099320 80098720 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 099324 80098724 AC39F4D4 */  sw    $t9, %lo(gTrackIdToLoad)($at)
/* 099328 80098728 3C01800E */  lui   $at, %hi(D_800DF478) # $at, 0x800e
/* 09932C 8009872C 24080001 */  li    $t0, 1
/* 099330 80098730 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 099334 80098734 10000003 */  b     .L80098744
/* 099338 80098738 AC28F478 */   sw    $t0, %lo(D_800DF478)($at)
.L8009873C:
/* 09933C 8009873C 3C018012 */  lui   $at, %hi(gIgnorePlayerInput) # $at, 0x8012
/* 099340 80098740 AC2063C4 */  sw    $zero, %lo(gIgnorePlayerInput)($at)
.L80098744:
/* 099344 80098744 8FBF0014 */  lw    $ra, 0x14($sp)
/* 099348 80098748 27BD0020 */  addiu $sp, $sp, 0x20
/* 09934C 8009874C 03E00008 */  jr    $ra
/* 099350 80098750 00000000 */   nop   

