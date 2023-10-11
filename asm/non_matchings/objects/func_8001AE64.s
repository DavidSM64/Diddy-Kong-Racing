glabel func_8001AE64
/* 01BA64 8001AE64 27BDFFA8 */  addiu $sp, $sp, -0x58
/* 01BA68 8001AE68 AFBF001C */  sw    $ra, 0x1c($sp)
/* 01BA6C 8001AE6C 0C01AF6C */  jal   get_current_level_header
/* 01BA70 8001AE70 AFB00018 */   sw    $s0, 0x18($sp)
/* 01BA74 8001AE74 0C01BAA4 */  jal   get_settings
/* 01BA78 8001AE78 AFA2002C */   sw    $v0, 0x2c($sp)
/* 01BA7C 8001AE7C 8FAA002C */  lw    $t2, 0x2c($sp)
/* 01BA80 8001AE80 A0400114 */  sb    $zero, 0x114($v0)
/* 01BA84 8001AE84 A0400116 */  sb    $zero, 0x116($v0)
/* 01BA88 8001AE88 A0400115 */  sb    $zero, 0x115($v0)
/* 01BA8C 8001AE8C 3C0E8012 */  lui   $t6, %hi(gRacersByPosition) # $t6, 0x8012
/* 01BA90 8001AE90 8DCEAEE8 */  lw    $t6, %lo(gRacersByPosition)($t6)
/* 01BA94 8001AE94 3C198012 */  lui   $t9, %hi(gNumRacers) # $t9, 0x8012
/* 01BA98 8001AE98 8DCF0000 */  lw    $t7, ($t6)
/* 01BA9C 8001AE9C 8F39AEF0 */  lw    $t9, %lo(gNumRacers)($t9)
/* 01BAA0 8001AEA0 8DF80064 */  lw    $t8, 0x64($t7)
/* 01BAA4 8001AEA4 00404025 */  move  $t0, $v0
/* 01BAA8 8001AEA8 34108CA1 */  li    $s0, 36001
/* 01BAAC 8001AEAC 34098CA1 */  li    $t1, 36001
/* 01BAB0 8001AEB0 00006825 */  move  $t5, $zero
/* 01BAB4 8001AEB4 1B20005A */  blez  $t9, .L8001B020
/* 01BAB8 8001AEB8 AFB80034 */   sw    $t8, 0x34($sp)
/* 01BABC 8001AEBC 00006025 */  move  $t4, $zero
.L8001AEC0:
/* 01BAC0 8001AEC0 3C0E8012 */  lui   $t6, %hi(gRacersByPosition) # $t6, 0x8012
/* 01BAC4 8001AEC4 8DCEAEE8 */  lw    $t6, %lo(gRacersByPosition)($t6)
/* 01BAC8 8001AEC8 00000000 */  nop   
/* 01BACC 8001AECC 01CC7821 */  addu  $t7, $t6, $t4
/* 01BAD0 8001AED0 8DF80000 */  lw    $t8, ($t7)
/* 01BAD4 8001AED4 00000000 */  nop   
/* 01BAD8 8001AED8 8F070064 */  lw    $a3, 0x64($t8)
/* 01BADC 8001AEDC 00000000 */  nop   
/* 01BAE0 8001AEE0 80F90002 */  lb    $t9, 2($a3)
/* 01BAE4 8001AEE4 00000000 */  nop   
/* 01BAE8 8001AEE8 07200047 */  bltz  $t9, .L8001B008
/* 01BAEC 8001AEEC 00000000 */   nop   
/* 01BAF0 8001AEF0 AFA70038 */  sw    $a3, 0x38($sp)
/* 01BAF4 8001AEF4 AFA80030 */  sw    $t0, 0x30($sp)
/* 01BAF8 8001AEF8 AFA90050 */  sw    $t1, 0x50($sp)
/* 01BAFC 8001AEFC AFAA002C */  sw    $t2, 0x2c($sp)
/* 01BB00 8001AF00 AFAC0024 */  sw    $t4, 0x24($sp)
/* 01BB04 8001AF04 0C0270F2 */  jal   get_number_of_active_players
/* 01BB08 8001AF08 AFAD004C */   sw    $t5, 0x4c($sp)
/* 01BB0C 8001AF0C 8FA70038 */  lw    $a3, 0x38($sp)
/* 01BB10 8001AF10 8FA80030 */  lw    $t0, 0x30($sp)
/* 01BB14 8001AF14 80E30002 */  lb    $v1, 2($a3)
/* 01BB18 8001AF18 8FA90050 */  lw    $t1, 0x50($sp)
/* 01BB1C 8001AF1C 8FAA002C */  lw    $t2, 0x2c($sp)
/* 01BB20 8001AF20 8FAC0024 */  lw    $t4, 0x24($sp)
/* 01BB24 8001AF24 8FAD004C */  lw    $t5, 0x4c($sp)
/* 01BB28 8001AF28 0062082A */  slt   $at, $v1, $v0
/* 01BB2C 8001AF2C 240B0005 */  li    $t3, 5
/* 01BB30 8001AF30 10200035 */  beqz  $at, .L8001B008
/* 01BB34 8001AF34 241F0018 */   li    $ra, 24
/* 01BB38 8001AF38 007F0019 */  multu $v1, $ra
/* 01BB3C 8001AF3C 00007012 */  mflo  $t6
/* 01BB40 8001AF40 010E7821 */  addu  $t7, $t0, $t6
/* 01BB44 8001AF44 A1E00058 */  sb    $zero, 0x58($t7)
/* 01BB48 8001AF48 80E201D7 */  lb    $v0, 0x1d7($a3)
/* 01BB4C 8001AF4C 00000000 */  nop   
/* 01BB50 8001AF50 0440002D */  bltz  $v0, .L8001B008
/* 01BB54 8001AF54 28410003 */   slti  $at, $v0, 3
/* 01BB58 8001AF58 1020002B */  beqz  $at, .L8001B008
/* 01BB5C 8001AF5C 00000000 */   nop   
/* 01BB60 8001AF60 8158004B */  lb    $t8, 0x4b($t2)
/* 01BB64 8001AF64 00003025 */  move  $a2, $zero
/* 01BB68 8001AF68 1B00001C */  blez  $t8, .L8001AFDC
/* 01BB6C 8001AF6C 00002025 */   move  $a0, $zero
/* 01BB70 8001AF70 0004C880 */  sll   $t9, $a0, 2
/* 01BB74 8001AF74 00F91021 */  addu  $v0, $a3, $t9
/* 01BB78 8001AF78 00042840 */  sll   $a1, $a0, 1
.L8001AF7C:
/* 01BB7C 8001AF7C 80EF0002 */  lb    $t7, 2($a3)
/* 01BB80 8001AF80 8C4E0128 */  lw    $t6, 0x128($v0)
/* 01BB84 8001AF84 000FC080 */  sll   $t8, $t7, 2
/* 01BB88 8001AF88 030FC023 */  subu  $t8, $t8, $t7
/* 01BB8C 8001AF8C 0018C0C0 */  sll   $t8, $t8, 3
/* 01BB90 8001AF90 0118C821 */  addu  $t9, $t0, $t8
/* 01BB94 8001AF94 03257821 */  addu  $t7, $t9, $a1
/* 01BB98 8001AF98 A5EE0066 */  sh    $t6, 0x66($t7)
/* 01BB9C 8001AF9C 8C430128 */  lw    $v1, 0x128($v0)
/* 01BBA0 8001AFA0 24A50002 */  addiu $a1, $a1, 2
/* 01BBA4 8001AFA4 0069082A */  slt   $at, $v1, $t1
/* 01BBA8 8001AFA8 10200005 */  beqz  $at, .L8001AFC0
/* 01BBAC 8001AFAC 00C33021 */   addu  $a2, $a2, $v1
/* 01BBB0 8001AFB0 A1040116 */  sb    $a0, 0x116($t0)
/* 01BBB4 8001AFB4 80F80002 */  lb    $t8, 2($a3)
/* 01BBB8 8001AFB8 00604825 */  move  $t1, $v1
/* 01BBBC 8001AFBC A1180115 */  sb    $t8, 0x115($t0)
.L8001AFC0:
/* 01BBC0 8001AFC0 8159004B */  lb    $t9, 0x4b($t2)
/* 01BBC4 8001AFC4 24840001 */  addiu $a0, $a0, 1
/* 01BBC8 8001AFC8 0099082A */  slt   $at, $a0, $t9
/* 01BBCC 8001AFCC 10200003 */  beqz  $at, .L8001AFDC
/* 01BBD0 8001AFD0 24420004 */   addiu $v0, $v0, 4
/* 01BBD4 8001AFD4 148BFFE9 */  bne   $a0, $t3, .L8001AF7C
/* 01BBD8 8001AFD8 00000000 */   nop   
.L8001AFDC:
/* 01BBDC 8001AFDC 80EE0002 */  lb    $t6, 2($a3)
/* 01BBE0 8001AFE0 00D0082A */  slt   $at, $a2, $s0
/* 01BBE4 8001AFE4 01DF0019 */  multu $t6, $ra
/* 01BBE8 8001AFE8 00007812 */  mflo  $t7
/* 01BBEC 8001AFEC 010FC021 */  addu  $t8, $t0, $t7
/* 01BBF0 8001AFF0 10200005 */  beqz  $at, .L8001B008
/* 01BBF4 8001AFF4 A7060064 */   sh    $a2, 0x64($t8)
/* 01BBF8 8001AFF8 80F90002 */  lb    $t9, 2($a3)
/* 01BBFC 8001AFFC 00C08025 */  move  $s0, $a2
/* 01BC00 8001B000 A1190114 */  sb    $t9, 0x114($t0)
/* 01BC04 8001B004 AFA70034 */  sw    $a3, 0x34($sp)
.L8001B008:
/* 01BC08 8001B008 3C0E8012 */  lui   $t6, %hi(gNumRacers) # $t6, 0x8012
/* 01BC0C 8001B00C 8DCEAEF0 */  lw    $t6, %lo(gNumRacers)($t6)
/* 01BC10 8001B010 25AD0001 */  addiu $t5, $t5, 1
/* 01BC14 8001B014 01AE082A */  slt   $at, $t5, $t6
/* 01BC18 8001B018 1420FFA9 */  bnez  $at, .L8001AEC0
/* 01BC1C 8001B01C 258C0004 */   addiu $t4, $t4, 4
.L8001B020:
/* 01BC20 8001B020 A1000117 */  sb    $zero, 0x117($t0)
/* 01BC24 8001B024 3C0F8012 */  lui   $t7, %hi(gIsTimeTrial) # $t7, 0x8012
/* 01BC28 8001B028 91EFAEF5 */  lbu   $t7, %lo(gIsTimeTrial)($t7)
/* 01BC2C 8001B02C 240B0005 */  li    $t3, 5
/* 01BC30 8001B030 11E00091 */  beqz  $t7, .L8001B278
/* 01BC34 8001B034 241F0018 */   li    $ra, 24
/* 01BC38 8001B038 3C028012 */  lui   $v0, %hi(D_8011AE82) # $v0, 0x8012
/* 01BC3C 8001B03C 8442AE82 */  lh    $v0, %lo(D_8011AE82)($v0)
/* 01BC40 8001B040 00000000 */  nop   
/* 01BC44 8001B044 28410003 */  slti  $at, $v0, 3
/* 01BC48 8001B048 10200003 */  beqz  $at, .L8001B058
/* 01BC4C 8001B04C 00000000 */   nop   
/* 01BC50 8001B050 04410002 */  bgez  $v0, .L8001B05C
/* 01BC54 8001B054 00000000 */   nop   
.L8001B058:
/* 01BC58 8001B058 00001025 */  move  $v0, $zero
.L8001B05C:
/* 01BC5C 8001B05C 81190115 */  lb    $t9, 0x115($t0)
/* 01BC60 8001B060 24180001 */  li    $t8, 1
/* 01BC64 8001B064 17200018 */  bnez  $t9, .L8001B0C8
/* 01BC68 8001B068 A1180117 */   sb    $t8, 0x117($t0)
/* 01BC6C 8001B06C 00027080 */  sll   $t6, $v0, 2
/* 01BC70 8001B070 91190049 */  lbu   $t9, 0x49($t0)
/* 01BC74 8001B074 010E7821 */  addu  $t7, $t0, $t6
/* 01BC78 8001B078 8DF80024 */  lw    $t8, 0x24($t7)
/* 01BC7C 8001B07C 00197040 */  sll   $t6, $t9, 1
/* 01BC80 8001B080 030E2021 */  addu  $a0, $t8, $t6
/* 01BC84 8001B084 94830000 */  lhu   $v1, ($a0)
/* 01BC88 8001B088 00000000 */  nop   
/* 01BC8C 8001B08C 10600003 */  beqz  $v1, .L8001B09C
/* 01BC90 8001B090 0123082A */   slt   $at, $t1, $v1
/* 01BC94 8001B094 1020000C */  beqz  $at, .L8001B0C8
/* 01BC98 8001B098 00000000 */   nop   
.L8001B09C:
/* 01BC9C 8001B09C A4890000 */  sh    $t1, ($a0)
/* 01BCA0 8001B0A0 810F0115 */  lb    $t7, 0x115($t0)
/* 01BCA4 8001B0A4 810E0116 */  lb    $t6, 0x116($t0)
/* 01BCA8 8001B0A8 01FF0019 */  multu $t7, $ra
/* 01BCAC 8001B0AC 240F0001 */  li    $t7, 1
/* 01BCB0 8001B0B0 0000C812 */  mflo  $t9
/* 01BCB4 8001B0B4 01191821 */  addu  $v1, $t0, $t9
/* 01BCB8 8001B0B8 80780058 */  lb    $t8, 0x58($v1)
/* 01BCBC 8001B0BC 01CFC804 */  sllv  $t9, $t7, $t6
/* 01BCC0 8001B0C0 03197825 */  or    $t7, $t8, $t9
/* 01BCC4 8001B0C4 A06F0058 */  sb    $t7, 0x58($v1)
.L8001B0C8:
/* 01BCC8 8001B0C8 81050114 */  lb    $a1, 0x114($t0)
/* 01BCCC 8001B0CC 00027080 */  sll   $t6, $v0, 2
/* 01BCD0 8001B0D0 14A00018 */  bnez  $a1, .L8001B134
/* 01BCD4 8001B0D4 00000000 */   nop   
/* 01BCD8 8001B0D8 910F0049 */  lbu   $t7, 0x49($t0)
/* 01BCDC 8001B0DC 010EC021 */  addu  $t8, $t0, $t6
/* 01BCE0 8001B0E0 8F19003C */  lw    $t9, 0x3c($t8)
/* 01BCE4 8001B0E4 000F7040 */  sll   $t6, $t7, 1
/* 01BCE8 8001B0E8 032E2021 */  addu  $a0, $t9, $t6
/* 01BCEC 8001B0EC 94830000 */  lhu   $v1, ($a0)
/* 01BCF0 8001B0F0 00000000 */  nop   
/* 01BCF4 8001B0F4 10600003 */  beqz  $v1, .L8001B104
/* 01BCF8 8001B0F8 0203082A */   slt   $at, $s0, $v1
/* 01BCFC 8001B0FC 1020000D */  beqz  $at, .L8001B134
/* 01BD00 8001B100 00000000 */   nop   
.L8001B104:
/* 01BD04 8001B104 A4900000 */  sh    $s0, ($a0)
/* 01BD08 8001B108 81180114 */  lb    $t8, 0x114($t0)
/* 01BD0C 8001B10C 00000000 */  nop   
/* 01BD10 8001B110 031F0019 */  multu $t8, $ra
/* 01BD14 8001B114 00007812 */  mflo  $t7
/* 01BD18 8001B118 010F1821 */  addu  $v1, $t0, $t7
/* 01BD1C 8001B11C 80790058 */  lb    $t9, 0x58($v1)
/* 01BD20 8001B120 00000000 */  nop   
/* 01BD24 8001B124 372E0080 */  ori   $t6, $t9, 0x80
/* 01BD28 8001B128 A06E0058 */  sb    $t6, 0x58($v1)
/* 01BD2C 8001B12C 81050114 */  lb    $a1, 0x114($t0)
/* 01BD30 8001B130 00000000 */  nop   
.L8001B134:
/* 01BD34 8001B134 14A00050 */  bnez  $a1, .L8001B278
/* 01BD38 8001B138 2A012A30 */   slti  $at, $s0, 0x2a30
/* 01BD3C 8001B13C 10200024 */  beqz  $at, .L8001B1D0
/* 01BD40 8001B140 00000000 */   nop   
/* 01BD44 8001B144 3C18800E */  lui   $t8, %hi(D_800DC728) # $t8, 0x800e
/* 01BD48 8001B148 8718C728 */  lh    $t8, %lo(D_800DC728)($t8)
/* 01BD4C 8001B14C 00000000 */  nop   
/* 01BD50 8001B150 1458000F */  bne   $v0, $t8, .L8001B190
/* 01BD54 8001B154 00000000 */   nop   
/* 01BD58 8001B158 0C01666A */  jal   func_800599A8
/* 01BD5C 8001B15C AFA80030 */   sw    $t0, 0x30($sp)
/* 01BD60 8001B160 0C01AF62 */  jal   get_current_map_id
/* 01BD64 8001B164 AFA20028 */   sw    $v0, 0x28($sp)
/* 01BD68 8001B168 8FAF0028 */  lw    $t7, 0x28($sp)
/* 01BD6C 8001B16C 8FA80030 */  lw    $t0, 0x30($sp)
/* 01BD70 8001B170 144F0007 */  bne   $v0, $t7, .L8001B190
/* 01BD74 8001B174 240B0005 */   li    $t3, 5
/* 01BD78 8001B178 3C19800E */  lui   $t9, %hi(D_800DC724) # $t9, 0x800e
/* 01BD7C 8001B17C 8739C724 */  lh    $t9, %lo(D_800DC724)($t9)
/* 01BD80 8001B180 00000000 */  nop   
/* 01BD84 8001B184 0219082A */  slt   $at, $s0, $t9
/* 01BD88 8001B188 10200011 */  beqz  $at, .L8001B1D0
/* 01BD8C 8001B18C 00000000 */   nop   
.L8001B190:
/* 01BD90 8001B190 3C01800E */  lui   $at, %hi(D_800DC724) # $at, 0x800e
/* 01BD94 8001B194 3C0E8012 */  lui   $t6, %hi(D_8011AE82) # $t6, 0x8012
/* 01BD98 8001B198 85CEAE82 */  lh    $t6, %lo(D_8011AE82)($t6)
/* 01BD9C 8001B19C A430C724 */  sh    $s0, %lo(D_800DC724)($at)
/* 01BDA0 8001B1A0 3C01800E */  lui   $at, %hi(D_800DC728) # $at, 0x800e
/* 01BDA4 8001B1A4 A42EC728 */  sh    $t6, %lo(D_800DC728)($at)
/* 01BDA8 8001B1A8 81180059 */  lb    $t8, 0x59($t0)
/* 01BDAC 8001B1AC 3C01800E */  lui   $at, %hi(D_800DC72C) # $at, 0x800e
/* 01BDB0 8001B1B0 0C01AF62 */  jal   get_current_map_id
/* 01BDB4 8001B1B4 A438C72C */   sh    $t8, %lo(D_800DC72C)($at)
/* 01BDB8 8001B1B8 0C016661 */  jal   func_80059984
/* 01BDBC 8001B1BC 00402025 */   move  $a0, $v0
/* 01BDC0 8001B1C0 240F0001 */  li    $t7, 1
/* 01BDC4 8001B1C4 3C01800E */  lui   $at, %hi(gHasGhostToSave) # $at, 0x800e
/* 01BDC8 8001B1C8 240B0005 */  li    $t3, 5
/* 01BDCC 8001B1CC A02FC730 */  sb    $t7, %lo(gHasGhostToSave)($at)
.L8001B1D0:
/* 01BDD0 8001B1D0 3C198000 */  lui   $t9, %hi(osTvType) # $t9, 0x8000
/* 01BDD4 8001B1D4 8F390300 */  lw    $t9, %lo(osTvType)($t9)
/* 01BDD8 8001B1D8 00107080 */  sll   $t6, $s0, 2
/* 01BDDC 8001B1DC 17200010 */  bnez  $t9, .L8001B220
/* 01BDE0 8001B1E0 3C188012 */   lui   $t8, %hi(gTTGhostTimeToBeat) # $t8, 0x8012
/* 01BDE4 8001B1E4 01D07023 */  subu  $t6, $t6, $s0
/* 01BDE8 8001B1E8 000E7040 */  sll   $t6, $t6, 1
/* 01BDEC 8001B1EC 01CB001A */  div   $zero, $t6, $t3
/* 01BDF0 8001B1F0 15600002 */  bnez  $t3, .L8001B1FC
/* 01BDF4 8001B1F4 00000000 */   nop   
/* 01BDF8 8001B1F8 0007000D */  break 7
.L8001B1FC:
/* 01BDFC 8001B1FC 2401FFFF */  li    $at, -1
/* 01BE00 8001B200 15610004 */  bne   $t3, $at, .L8001B214
/* 01BE04 8001B204 3C018000 */   lui   $at, 0x8000
/* 01BE08 8001B208 15C10002 */  bne   $t6, $at, .L8001B214
/* 01BE0C 8001B20C 00000000 */   nop   
/* 01BE10 8001B210 0006000D */  break 6
.L8001B214:
/* 01BE14 8001B214 00008012 */  mflo  $s0
/* 01BE18 8001B218 00000000 */  nop   
/* 01BE1C 8001B21C 00000000 */  nop   
.L8001B220:
/* 01BE20 8001B220 8718AE80 */  lh    $t8, %lo(gTTGhostTimeToBeat)($t8)
/* 01BE24 8001B224 8FA40034 */  lw    $a0, 0x34($sp)
/* 01BE28 8001B228 0218082A */  slt   $at, $s0, $t8
/* 01BE2C 8001B22C 10200010 */  beqz  $at, .L8001B270
/* 01BE30 8001B230 3C0F800E */   lui   $t7, %hi(gTimeTrialStaffGhost) # $t7, 0x800e
/* 01BE34 8001B234 91EFC734 */  lbu   $t7, %lo(gTimeTrialStaffGhost)($t7)
/* 01BE38 8001B238 8FA40034 */  lw    $a0, 0x34($sp)
/* 01BE3C 8001B23C 11E00008 */  beqz  $t7, .L8001B260
/* 01BE40 8001B240 00000000 */   nop   
/* 01BE44 8001B244 0C01AF62 */  jal   get_current_map_id
/* 01BE48 8001B248 00000000 */   nop   
/* 01BE4C 8001B24C 8FA50034 */  lw    $a1, 0x34($sp)
/* 01BE50 8001B250 0C006CF1 */  jal   tt_ghost_beaten
/* 01BE54 8001B254 00402025 */   move  $a0, $v0
/* 01BE58 8001B258 10000008 */  b     .L8001B27C
/* 01BE5C 8001B25C 8FBF001C */   lw    $ra, 0x1c($sp)
.L8001B260:
/* 01BE60 8001B260 0C029B6D */  jal   play_time_trial_end_message
/* 01BE64 8001B264 00000000 */   nop   
/* 01BE68 8001B268 10000004 */  b     .L8001B27C
/* 01BE6C 8001B26C 8FBF001C */   lw    $ra, 0x1c($sp)
.L8001B270:
/* 01BE70 8001B270 0C029B6D */  jal   play_time_trial_end_message
/* 01BE74 8001B274 00000000 */   nop   
.L8001B278:
/* 01BE78 8001B278 8FBF001C */  lw    $ra, 0x1c($sp)
.L8001B27C:
/* 01BE7C 8001B27C 8FB00018 */  lw    $s0, 0x18($sp)
/* 01BE80 8001B280 03E00008 */  jr    $ra
/* 01BE84 8001B284 27BD0058 */   addiu $sp, $sp, 0x58

