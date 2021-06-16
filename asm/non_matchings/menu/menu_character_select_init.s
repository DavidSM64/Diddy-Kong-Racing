glabel menu_character_select_init
/* 08BBCC 8008AFCC 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 08BBD0 8008AFD0 AFBF002C */  sw    $ra, 0x2c($sp)
/* 08BBD4 8008AFD4 AFB1001C */  sw    $s1, 0x1c($sp)
/* 08BBD8 8008AFD8 AFB40028 */  sw    $s4, 0x28($sp)
/* 08BBDC 8008AFDC AFB30024 */  sw    $s3, 0x24($sp)
/* 08BBE0 8008AFE0 AFB20020 */  sw    $s2, 0x20($sp)
/* 08BBE4 8008AFE4 AFB00018 */  sw    $s0, 0x18($sp)
/* 08BBE8 8008AFE8 0C01A90D */  jal   func_8006A434
/* 08BBEC 8008AFEC 00008825 */   move  $s1, $zero
/* 08BBF0 8008AFF0 0C027B34 */  jal   is_drumstick_unlocked
/* 08BBF4 8008AFF4 00000000 */   nop   
/* 08BBF8 8008AFF8 10400010 */  beqz  $v0, .L8008B03C
/* 08BBFC 8008AFFC 00000000 */   nop   
/* 08BC00 8008B000 0C027B2E */  jal   is_tt_unlocked
/* 08BC04 8008B004 00000000 */   nop   
/* 08BC08 8008B008 10400007 */  beqz  $v0, .L8008B028
/* 08BC0C 8008B00C 3C078012 */   lui   $a3, %hi(D_801263CC) # $a3, 0x8012
/* 08BC10 8008B010 3C078012 */  lui   $a3, %hi(D_801263CC) # $a3, 0x8012
/* 08BC14 8008B014 3C0E800E */  lui   $t6, %hi(D_800DFF40) # $t6, 0x800e
/* 08BC18 8008B018 24E763CC */  addiu $a3, %lo(D_801263CC) # addiu $a3, $a3, 0x63cc
/* 08BC1C 8008B01C 25CEFF40 */  addiu $t6, %lo(D_800DFF40) # addiu $t6, $t6, -0xc0
/* 08BC20 8008B020 10000014 */  b     .L8008B074
/* 08BC24 8008B024 ACEE0000 */   sw    $t6, ($a3)
.L8008B028:
/* 08BC28 8008B028 3C0F800E */  lui   $t7, %hi(D_800DFE40) # $t7, 0x800e
/* 08BC2C 8008B02C 24E763CC */  addiu $a3, %lo(D_801263CC) # addiu $a3, $a3, 0x63cc
/* 08BC30 8008B030 25EFFE40 */  addiu $t7, %lo(D_800DFE40) # addiu $t7, $t7, -0x1c0
/* 08BC34 8008B034 1000000F */  b     .L8008B074
/* 08BC38 8008B038 ACEF0000 */   sw    $t7, ($a3)
.L8008B03C:
/* 08BC3C 8008B03C 0C027B2E */  jal   is_tt_unlocked
/* 08BC40 8008B040 00000000 */   nop   
/* 08BC44 8008B044 10400006 */  beqz  $v0, .L8008B060
/* 08BC48 8008B048 3C078012 */   lui   $a3, %hi(D_801263CC) # $a3, 0x8012
/* 08BC4C 8008B04C 3C18800E */  lui   $t8, %hi(D_800DFEC0) # $t8, 0x800e
/* 08BC50 8008B050 24E763CC */  addiu $a3, %lo(D_801263CC) # addiu $a3, $a3, 0x63cc
/* 08BC54 8008B054 2718FEC0 */  addiu $t8, %lo(D_800DFEC0) # addiu $t8, $t8, -0x140
/* 08BC58 8008B058 10000006 */  b     .L8008B074
/* 08BC5C 8008B05C ACF80000 */   sw    $t8, ($a3)
.L8008B060:
/* 08BC60 8008B060 3C078012 */  lui   $a3, %hi(D_801263CC) # $a3, 0x8012
/* 08BC64 8008B064 3C19800E */  lui   $t9, %hi(D_800DFDD0) # $t9, 0x800e
/* 08BC68 8008B068 24E763CC */  addiu $a3, %lo(D_801263CC) # addiu $a3, $a3, 0x63cc
/* 08BC6C 8008B06C 2739FDD0 */  addiu $t9, %lo(D_800DFDD0) # addiu $t9, $t9, -0x230
/* 08BC70 8008B070 ACF90000 */  sw    $t9, ($a3)
.L8008B074:
/* 08BC74 8008B074 3C028012 */  lui   $v0, %hi(D_801263DC) # $v0, 0x8012
/* 08BC78 8008B078 3C038012 */  lui   $v1, %hi(D_801263E0) # $v1, 0x8012
/* 08BC7C 8008B07C 246363E0 */  addiu $v1, %lo(D_801263E0) # addiu $v1, $v1, 0x63e0
/* 08BC80 8008B080 244263DC */  addiu $v0, %lo(D_801263DC) # addiu $v0, $v0, 0x63dc
.L8008B084:
/* 08BC84 8008B084 24420001 */  addiu $v0, $v0, 1
/* 08BC88 8008B088 0043082B */  sltu  $at, $v0, $v1
/* 08BC8C 8008B08C 1420FFFD */  bnez  $at, .L8008B084
/* 08BC90 8008B090 A040FFFF */   sb    $zero, -1($v0)
/* 08BC94 8008B094 3C01800E */  lui   $at, %hi(gNumberOfReadyPlayers) # $at, 0x800e
/* 08BC98 8008B098 AC20F480 */  sw    $zero, %lo(gNumberOfReadyPlayers)($at)
/* 08BC9C 8008B09C 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08BCA0 8008B0A0 AC20F47C */  sw    $zero, %lo(gMenuDelay)($at)
/* 08BCA4 8008B0A4 3C018012 */  lui   $at, %hi(D_801263BC) # $at, 0x8012
/* 08BCA8 8008B0A8 AC2063BC */  sw    $zero, %lo(D_801263BC)($at)
/* 08BCAC 8008B0AC 3C088012 */  lui   $t0, %hi(gActivePlayersArray) # $t0, 0x8012
/* 08BCB0 8008B0B0 3C01800E */  lui   $at, %hi(D_800DF484) # $at, 0x800e
/* 08BCB4 8008B0B4 250863D4 */  addiu $t0, %lo(gActivePlayersArray) # addiu $t0, $t0, 0x63d4
/* 08BCB8 8008B0B8 3C128012 */  lui   $s2, %hi(D_801263C0) # $s2, 0x8012
/* 08BCBC 8008B0BC 3C038012 */  lui   $v1, %hi(gPlayersCharacterArray) # $v1, 0x8012
/* 08BCC0 8008B0C0 AC20F484 */  sw    $zero, %lo(D_800DF484)($at)
/* 08BCC4 8008B0C4 246363E8 */  addiu $v1, %lo(gPlayersCharacterArray) # addiu $v1, $v1, 0x63e8
/* 08BCC8 8008B0C8 265263C0 */  addiu $s2, %lo(D_801263C0) # addiu $s2, $s2, 0x63c0
/* 08BCCC 8008B0CC 00081021 */  addu  $v0, $zero, $t0
/* 08BCD0 8008B0D0 00008025 */  move  $s0, $zero
/* 08BCD4 8008B0D4 24060001 */  li    $a2, 1
/* 08BCD8 8008B0D8 2405007F */  li    $a1, 127
/* 08BCDC 8008B0DC 2404000E */  li    $a0, 14
.L8008B0E0:
/* 08BCE0 8008B0E0 80490000 */  lb    $t1, ($v0)
/* 08BCE4 8008B0E4 00705821 */  addu  $t3, $v1, $s0
/* 08BCE8 8008B0E8 1120000B */  beqz  $t1, .L8008B118
/* 08BCEC 8008B0EC 00000000 */   nop   
/* 08BCF0 8008B0F0 816C0000 */  lb    $t4, ($t3)
/* 08BCF4 8008B0F4 8CEA0000 */  lw    $t2, ($a3)
/* 08BCF8 8008B0F8 01840019 */  multu $t4, $a0
/* 08BCFC 8008B0FC 00C08825 */  move  $s1, $a2
/* 08BD00 8008B100 00006812 */  mflo  $t5
/* 08BD04 8008B104 014D7021 */  addu  $t6, $t2, $t5
/* 08BD08 8008B108 85CF000C */  lh    $t7, 0xc($t6)
/* 08BD0C 8008B10C A6450002 */  sh    $a1, 2($s2)
/* 08BD10 8008B110 A2460001 */  sb    $a2, 1($s2)
/* 08BD14 8008B114 A24F0000 */  sb    $t7, ($s2)
.L8008B118:
/* 08BD18 8008B118 26100001 */  addiu $s0, $s0, 1
/* 08BD1C 8008B11C 2A010004 */  slti  $at, $s0, 4
/* 08BD20 8008B120 10200003 */  beqz  $at, .L8008B130
/* 08BD24 8008B124 24420001 */   addiu $v0, $v0, 1
/* 08BD28 8008B128 1220FFED */  beqz  $s1, .L8008B0E0
/* 08BD2C 8008B12C 00000000 */   nop   
.L8008B130:
/* 08BD30 8008B130 3C028012 */  lui   $v0, %hi(D_801263B4) # $v0, 0x8012
/* 08BD34 8008B134 3C038012 */  lui   $v1, %hi(D_801263B8) # $v1, 0x8012
/* 08BD38 8008B138 246363B8 */  addiu $v1, %lo(D_801263B8) # addiu $v1, $v1, 0x63b8
/* 08BD3C 8008B13C 244263B4 */  addiu $v0, %lo(D_801263B4) # addiu $v0, $v0, 0x63b4
/* 08BD40 8008B140 2405FFFF */  li    $a1, -1
/* 08BD44 8008B144 3C128012 */  lui   $s2, %hi(D_801263C0) # $s2, 0x8012
/* 08BD48 8008B148 265263C0 */  addiu $s2, %lo(D_801263C0) # addiu $s2, $s2, 0x63c0
/* 08BD4C 8008B14C A0450000 */  sb    $a1, ($v0)
/* 08BD50 8008B150 A4400002 */  sh    $zero, 2($v0)
/* 08BD54 8008B154 A0400001 */  sb    $zero, 1($v0)
/* 08BD58 8008B158 A0650000 */  sb    $a1, ($v1)
/* 08BD5C 8008B15C A4600002 */  sh    $zero, 2($v1)
/* 08BD60 8008B160 A0600001 */  sb    $zero, 1($v1)
/* 08BD64 8008B164 2404001A */  li    $a0, 26
/* 08BD68 8008B168 0C0002CD */  jal   play_music
/* 08BD6C 8008B16C 00008025 */   move  $s0, $zero
/* 08BD70 8008B170 3C13800E */  lui   $s3, %hi(D_800DFDB4) # $s3, 0x800e
/* 08BD74 8008B174 2673FDB4 */  addiu $s3, %lo(D_800DFDB4) # addiu $s3, $s3, -0x24c
/* 08BD78 8008B178 2414000A */  li    $s4, 10
.L8008B17C:
/* 08BD7C 8008B17C 82580000 */  lb    $t8, ($s2)
/* 08BD80 8008B180 0010C840 */  sll   $t9, $s0, 1
/* 08BD84 8008B184 12180007 */  beq   $s0, $t8, .L8008B1A4
/* 08BD88 8008B188 02798821 */   addu  $s1, $s3, $t9
/* 08BD8C 8008B18C 92240000 */  lbu   $a0, ($s1)
/* 08BD90 8008B190 0C000445 */  jal   func_80001114
/* 08BD94 8008B194 00000000 */   nop   
/* 08BD98 8008B198 92240001 */  lbu   $a0, 1($s1)
/* 08BD9C 8008B19C 0C000445 */  jal   func_80001114
/* 08BDA0 8008B1A0 00000000 */   nop   
.L8008B1A4:
/* 08BDA4 8008B1A4 26100001 */  addiu $s0, $s0, 1
/* 08BDA8 8008B1A8 1614FFF4 */  bne   $s0, $s4, .L8008B17C
/* 08BDAC 8008B1AC 00000000 */   nop   
/* 08BDB0 8008B1B0 0C000445 */  jal   func_80001114
/* 08BDB4 8008B1B4 24040006 */   li    $a0, 6
/* 08BDB8 8008B1B8 0C0002C6 */  jal   func_80000B18
/* 08BDBC 8008B1BC 00000000 */   nop   
/* 08BDC0 8008B1C0 3C04800E */  lui   $a0, %hi(D_800DFDC8) # $a0, 0x800e
/* 08BDC4 8008B1C4 0C02719D */  jal   func_8009C674
/* 08BDC8 8008B1C8 2484FDC8 */   addiu $a0, %lo(D_800DFDC8) # addiu $a0, $a0, -0x238
/* 08BDCC 8008B1CC 3C04800E */  lui   $a0, %hi(D_800DFDCC) # $a0, 0x800e
/* 08BDD0 8008B1D0 0C027229 */  jal   func_8009C8A4
/* 08BDD4 8008B1D4 2484FDCC */   addiu $a0, %lo(D_800DFDCC) # addiu $a0, $a0, -0x234
/* 08BDD8 8008B1D8 3C04800E */  lui   $a0, %hi(D_800DF77C) # $a0, 0x800e
/* 08BDDC 8008B1DC 0C030076 */  jal   func_800C01D8
/* 08BDE0 8008B1E0 2484F77C */   addiu $a0, %lo(D_800DF77C) # addiu $a0, $a0, -0x884
/* 08BDE4 8008B1E4 0C03105C */  jal   func_800C4170
/* 08BDE8 8008B1E8 24040002 */   li    $a0, 2
/* 08BDEC 8008B1EC 8FBF002C */  lw    $ra, 0x2c($sp)
/* 08BDF0 8008B1F0 8FB00018 */  lw    $s0, 0x18($sp)
/* 08BDF4 8008B1F4 8FB1001C */  lw    $s1, 0x1c($sp)
/* 08BDF8 8008B1F8 8FB20020 */  lw    $s2, 0x20($sp)
/* 08BDFC 8008B1FC 8FB30024 */  lw    $s3, 0x24($sp)
/* 08BE00 8008B200 8FB40028 */  lw    $s4, 0x28($sp)
/* 08BE04 8008B204 03E00008 */  jr    $ra
/* 08BE08 8008B208 27BD0030 */   addiu $sp, $sp, 0x30

