glabel load_texture
/* 07BA74 8007AE74 27BDFF90 */  addiu $sp, $sp, -0x70
/* 07BA78 8007AE78 308EFFFF */  andi  $t6, $a0, 0xffff
/* 07BA7C 8007AE7C AFB30024 */  sw    $s3, 0x24($sp)
/* 07BA80 8007AE80 AFB00018 */  sw    $s0, 0x18($sp)
/* 07BA84 8007AE84 31CF8000 */  andi  $t7, $t6, 0x8000
/* 07BA88 8007AE88 AFBF002C */  sw    $ra, 0x2c($sp)
/* 07BA8C 8007AE8C AFB40028 */  sw    $s4, 0x28($sp)
/* 07BA90 8007AE90 AFB20020 */  sw    $s2, 0x20($sp)
/* 07BA94 8007AE94 AFB1001C */  sw    $s1, 0x1c($sp)
/* 07BA98 8007AE98 01C08025 */  move  $s0, $t6
/* 07BA9C 8007AE9C 01C04025 */  move  $t0, $t6
/* 07BAA0 8007AEA0 24130004 */  li    $s3, 4
/* 07BAA4 8007AEA4 11E00004 */  beqz  $t7, .L8007AEB8
/* 07BAA8 8007AEA8 00001025 */   move  $v0, $zero
/* 07BAAC 8007AEAC 24020001 */  li    $v0, 1
/* 07BAB0 8007AEB0 31C87FFF */  andi  $t0, $t6, 0x7fff
/* 07BAB4 8007AEB4 24130002 */  li    $s3, 2
.L8007AEB8:
/* 07BAB8 8007AEB8 00024880 */  sll   $t1, $v0, 2
/* 07BABC 8007AEBC 3C188012 */  lui   $t8, %hi(gTextureAssetID) # $t8, 0x8012
/* 07BAC0 8007AEC0 0309C021 */  addu  $t8, $t8, $t1
/* 07BAC4 8007AEC4 8F186338 */  lw    $t8, %lo(gTextureAssetID)($t8)
/* 07BAC8 8007AEC8 3C028012 */  lui   $v0, %hi(gNumberOfLoadedTextures) # $v0, 0x8012
/* 07BACC 8007AECC 0118082A */  slt   $at, $t0, $t8
/* 07BAD0 8007AED0 10200003 */  beqz  $at, .L8007AEE0
/* 07BAD4 8007AED4 3C048012 */   lui   $a0, %hi(gTextureCache) # $a0, 0x8012
/* 07BAD8 8007AED8 05010002 */  bgez  $t0, .L8007AEE4
/* 07BADC 8007AEDC 00000000 */   nop   
.L8007AEE0:
/* 07BAE0 8007AEE0 00008025 */  move  $s0, $zero
.L8007AEE4:
/* 07BAE4 8007AEE4 8C426330 */  lw    $v0, %lo(gNumberOfLoadedTextures)($v0)
/* 07BAE8 8007AEE8 00008825 */  move  $s1, $zero
/* 07BAEC 8007AEEC 18400012 */  blez  $v0, .L8007AF38
/* 07BAF0 8007AEF0 3C148012 */   lui   $s4, %hi(gTempTextureHeader) # $s4, 0x8012
/* 07BAF4 8007AEF4 8C846328 */  lw    $a0, %lo(gTextureCache)($a0)
/* 07BAF8 8007AEF8 00000000 */  nop   
/* 07BAFC 8007AEFC 001150C0 */  sll   $t2, $s1, 3
.L8007AF00:
/* 07BB00 8007AF00 008A1821 */  addu  $v1, $a0, $t2
/* 07BB04 8007AF04 8C6B0000 */  lw    $t3, ($v1)
/* 07BB08 8007AF08 26310001 */  addiu $s1, $s1, 1
/* 07BB0C 8007AF0C 160B0008 */  bne   $s0, $t3, .L8007AF30
/* 07BB10 8007AF10 0222082A */   slt   $at, $s1, $v0
/* 07BB14 8007AF14 8C620004 */  lw    $v0, 4($v1)
/* 07BB18 8007AF18 00000000 */  nop   
/* 07BB1C 8007AF1C 904C0005 */  lbu   $t4, 5($v0)
/* 07BB20 8007AF20 00000000 */  nop   
/* 07BB24 8007AF24 258D0001 */  addiu $t5, $t4, 1
/* 07BB28 8007AF28 100000DC */  b     .L8007B29C
/* 07BB2C 8007AF2C A04D0005 */   sb    $t5, 5($v0)
.L8007AF30:
/* 07BB30 8007AF30 1420FFF3 */  bnez  $at, .L8007AF00
/* 07BB34 8007AF34 001150C0 */   sll   $t2, $s1, 3
.L8007AF38:
/* 07BB38 8007AF38 3C0E8012 */  lui   $t6, %hi(gTextureAssetTable) # $t6, 0x8012
/* 07BB3C 8007AF3C 01C97021 */  addu  $t6, $t6, $t1
/* 07BB40 8007AF40 8DCE6320 */  lw    $t6, %lo(gTextureAssetTable)($t6)
/* 07BB44 8007AF44 00087880 */  sll   $t7, $t0, 2
/* 07BB48 8007AF48 01CF1021 */  addu  $v0, $t6, $t7
/* 07BB4C 8007AF4C 8C520000 */  lw    $s2, ($v0)
/* 07BB50 8007AF50 8C580004 */  lw    $t8, 4($v0)
/* 07BB54 8007AF54 2694636C */  addiu $s4, %lo(gTempTextureHeader) # addiu $s4, $s4, 0x636c
/* 07BB58 8007AF58 8E850000 */  lw    $a1, ($s4)
/* 07BB5C 8007AF5C 0312C823 */  subu  $t9, $t8, $s2
/* 07BB60 8007AF60 AFB90058 */  sw    $t9, 0x58($sp)
/* 07BB64 8007AF64 AFB30050 */  sw    $s3, 0x50($sp)
/* 07BB68 8007AF68 02602025 */  move  $a0, $s3
/* 07BB6C 8007AF6C 24070028 */  li    $a3, 40
/* 07BB70 8007AF70 0C01DB9A */  jal   load_asset_to_address
/* 07BB74 8007AF74 02403025 */   move  $a2, $s2
/* 07BB78 8007AF78 8E830000 */  lw    $v1, ($s4)
/* 07BB7C 8007AF7C 8FAE0058 */  lw    $t6, 0x58($sp)
/* 07BB80 8007AF80 94710012 */  lhu   $s1, 0x12($v1)
/* 07BB84 8007AF84 906C001D */  lbu   $t4, 0x1d($v1)
/* 07BB88 8007AF88 00115203 */  sra   $t2, $s1, 8
/* 07BB8C 8007AF8C 314BFFFF */  andi  $t3, $t2, 0xffff
/* 07BB90 8007AF90 15800015 */  bnez  $t4, .L8007AFE8
/* 07BB94 8007AF94 01608825 */   move  $s1, $t3
/* 07BB98 8007AF98 000B6880 */  sll   $t5, $t3, 2
/* 07BB9C 8007AF9C 01AB6823 */  subu  $t5, $t5, $t3
/* 07BBA0 8007AFA0 3C05800E */  lui   $a1, %hi(gTexColourTag) # $a1, 0x800e
/* 07BBA4 8007AFA4 8CA5E7C0 */  lw    $a1, %lo(gTexColourTag)($a1)
/* 07BBA8 8007AFA8 000D6940 */  sll   $t5, $t5, 5
/* 07BBAC 8007AFAC 01AE2021 */  addu  $a0, $t5, $t6
/* 07BBB0 8007AFB0 0C01C344 */  jal   mempool_alloc
/* 07BBB4 8007AFB4 0160A025 */   move  $s4, $t3
/* 07BBB8 8007AFB8 14400003 */  bnez  $v0, .L8007AFC8
/* 07BBBC 8007AFBC 00409825 */   move  $s3, $v0
/* 07BBC0 8007AFC0 100000B6 */  b     .L8007B29C
/* 07BBC4 8007AFC4 00001025 */   move  $v0, $zero
.L8007AFC8:
/* 07BBC8 8007AFC8 8FA40050 */  lw    $a0, 0x50($sp)
/* 07BBCC 8007AFCC 8FA70058 */  lw    $a3, 0x58($sp)
/* 07BBD0 8007AFD0 02602825 */  move  $a1, $s3
/* 07BBD4 8007AFD4 02403025 */  move  $a2, $s2
/* 07BBD8 8007AFD8 0C01DB9A */  jal   load_asset_to_address
/* 07BBDC 8007AFDC 00008825 */   move  $s1, $zero
/* 07BBE0 8007AFE0 1000002A */  b     .L8007B08C
/* 07BBE4 8007AFE4 00000000 */   nop   
.L8007AFE8:
/* 07BBE8 8007AFE8 0C03186B */  jal   byteswap32
/* 07BBEC 8007AFEC 24640020 */   addiu $a0, $v1, 0x20
/* 07BBF0 8007AFF0 0011C080 */  sll   $t8, $s1, 2
/* 07BBF4 8007AFF4 0311C023 */  subu  $t8, $t8, $s1
/* 07BBF8 8007AFF8 0018C140 */  sll   $t8, $t8, 5
/* 07BBFC 8007AFFC 3C05800E */  lui   $a1, %hi(gTexColourTag) # $a1, 0x800e
/* 07BC00 8007B000 244F0020 */  addiu $t7, $v0, 0x20
/* 07BC04 8007B004 8CA5E7C0 */  lw    $a1, %lo(gTexColourTag)($a1)
/* 07BC08 8007B008 03022021 */  addu  $a0, $t8, $v0
/* 07BC0C 8007B00C AFAF003C */  sw    $t7, 0x3c($sp)
/* 07BC10 8007B010 24840020 */  addiu $a0, $a0, 0x20
/* 07BC14 8007B014 0C01C344 */  jal   mempool_alloc
/* 07BC18 8007B018 0220A025 */   move  $s4, $s1
/* 07BC1C 8007B01C 14400003 */  bnez  $v0, .L8007B02C
/* 07BC20 8007B020 00409825 */   move  $s3, $v0
/* 07BC24 8007B024 1000009D */  b     .L8007B29C
/* 07BC28 8007B028 00001025 */   move  $v0, $zero
.L8007B02C:
/* 07BC2C 8007B02C 8FB9003C */  lw    $t9, 0x3c($sp)
/* 07BC30 8007B030 8FAB0058 */  lw    $t3, 0x58($sp)
/* 07BC34 8007B034 02795021 */  addu  $t2, $s3, $t9
/* 07BC38 8007B038 014B1023 */  subu  $v0, $t2, $t3
/* 07BC3C 8007B03C 8FA40050 */  lw    $a0, 0x50($sp)
/* 07BC40 8007B040 04410004 */  bgez  $v0, .L8007B054
/* 07BC44 8007B044 304C000F */   andi  $t4, $v0, 0xf
/* 07BC48 8007B048 11800002 */  beqz  $t4, .L8007B054
/* 07BC4C 8007B04C 00000000 */   nop   
/* 07BC50 8007B050 258CFFF0 */  addiu $t4, $t4, -0x10
.L8007B054:
/* 07BC54 8007B054 004C2823 */  subu  $a1, $v0, $t4
/* 07BC58 8007B058 AFA50034 */  sw    $a1, 0x34($sp)
/* 07BC5C 8007B05C 02403025 */  move  $a2, $s2
/* 07BC60 8007B060 00008825 */  move  $s1, $zero
/* 07BC64 8007B064 0C01DB9A */  jal   load_asset_to_address
/* 07BC68 8007B068 01603825 */   move  $a3, $t3
/* 07BC6C 8007B06C 8FA40034 */  lw    $a0, 0x34($sp)
/* 07BC70 8007B070 02602825 */  move  $a1, $s3
/* 07BC74 8007B074 0C031886 */  jal   gzip_inflate
/* 07BC78 8007B078 24840020 */   addiu $a0, $a0, 0x20
/* 07BC7C 8007B07C 8FAD003C */  lw    $t5, 0x3c($sp)
/* 07BC80 8007B080 00000000 */  nop   
/* 07BC84 8007B084 25AEFFE0 */  addiu $t6, $t5, -0x20
/* 07BC88 8007B088 AFAE0058 */  sw    $t6, 0x58($sp)
.L8007B08C:
/* 07BC8C 8007B08C 3C028012 */  lui   $v0, %hi(gNumberOfLoadedTextures) # $v0, 0x8012
/* 07BC90 8007B090 8C426330 */  lw    $v0, %lo(gNumberOfLoadedTextures)($v0)
/* 07BC94 8007B094 2405FFFF */  li    $a1, -1
/* 07BC98 8007B098 18400010 */  blez  $v0, .L8007B0DC
/* 07BC9C 8007B09C 3C0E8012 */   lui   $t6, %hi(gTextureCache) # $t6, 0x8012
/* 07BCA0 8007B0A0 3C048012 */  lui   $a0, %hi(gTextureCache) # $a0, 0x8012
/* 07BCA4 8007B0A4 8C846328 */  lw    $a0, %lo(gTextureCache)($a0)
/* 07BCA8 8007B0A8 2403FFFF */  li    $v1, -1
/* 07BCAC 8007B0AC 0011C0C0 */  sll   $t8, $s1, 3
.L8007B0B0:
/* 07BCB0 8007B0B0 0098C821 */  addu  $t9, $a0, $t8
/* 07BCB4 8007B0B4 8F2A0000 */  lw    $t2, ($t9)
/* 07BCB8 8007B0B8 00000000 */  nop   
/* 07BCBC 8007B0BC 146A0002 */  bne   $v1, $t2, .L8007B0C8
/* 07BCC0 8007B0C0 00000000 */   nop   
/* 07BCC4 8007B0C4 02202825 */  move  $a1, $s1
.L8007B0C8:
/* 07BCC8 8007B0C8 26310001 */  addiu $s1, $s1, 1
/* 07BCCC 8007B0CC 0222082A */  slt   $at, $s1, $v0
/* 07BCD0 8007B0D0 1420FFF7 */  bnez  $at, .L8007B0B0
/* 07BCD4 8007B0D4 0011C0C0 */   sll   $t8, $s1, 3
/* 07BCD8 8007B0D8 00008825 */  move  $s1, $zero
.L8007B0DC:
/* 07BCDC 8007B0DC 3C048012 */  lui   $a0, %hi(gTextureCache) # $a0, 0x8012
/* 07BCE0 8007B0E0 2403FFFF */  li    $v1, -1
/* 07BCE4 8007B0E4 8C846328 */  lw    $a0, %lo(gTextureCache)($a0)
/* 07BCE8 8007B0E8 14A30004 */  bne   $a1, $v1, .L8007B0FC
/* 07BCEC 8007B0EC 244C0001 */   addiu $t4, $v0, 1
/* 07BCF0 8007B0F0 3C018012 */  lui   $at, %hi(gNumberOfLoadedTextures) # $at, 0x8012
/* 07BCF4 8007B0F4 00402825 */  move  $a1, $v0
/* 07BCF8 8007B0F8 AC2C6330 */  sw    $t4, %lo(gNumberOfLoadedTextures)($at)
.L8007B0FC:
/* 07BCFC 8007B0FC 000558C0 */  sll   $t3, $a1, 3
/* 07BD00 8007B100 008B6821 */  addu  $t5, $a0, $t3
/* 07BD04 8007B104 ADB00000 */  sw    $s0, ($t5)
/* 07BD08 8007B108 8DCE6328 */  lw    $t6, %lo(gTextureCache)($t6)
/* 07BD0C 8007B10C 24010007 */  li    $at, 7
/* 07BD10 8007B110 01CB7821 */  addu  $t7, $t6, $t3
/* 07BD14 8007B114 ADF30004 */  sw    $s3, 4($t7)
/* 07BD18 8007B118 92660002 */  lbu   $a2, 2($s3)
/* 07BD1C 8007B11C 2403FFFF */  li    $v1, -1
/* 07BD20 8007B120 30D8000F */  andi  $t8, $a2, 0xf
/* 07BD24 8007B124 1701001E */  bne   $t8, $at, .L8007B1A0
/* 07BD28 8007B128 03003025 */   move  $a2, $t8
/* 07BD2C 8007B12C 3C128012 */  lui   $s2, %hi(D_80126344) # $s2, 0x8012
/* 07BD30 8007B130 26526344 */  addiu $s2, %lo(D_80126344) # addiu $s2, $s2, 0x6344
/* 07BD34 8007B134 8E590000 */  lw    $t9, ($s2)
/* 07BD38 8007B138 2404000E */  li    $a0, 14
/* 07BD3C 8007B13C 17200014 */  bnez  $t9, .L8007B190
/* 07BD40 8007B140 3C0A8012 */   lui   $t2, %hi(gCiPalettes) # $t2, 0x8012
/* 07BD44 8007B144 3C0C8012 */  lui   $t4, %hi(gCiPalettesSize) # $t4, 0x8012
/* 07BD48 8007B148 8D8C6340 */  lw    $t4, %lo(gCiPalettesSize)($t4)
/* 07BD4C 8007B14C 8D4A632C */  lw    $t2, %lo(gCiPalettes)($t2)
/* 07BD50 8007B150 86660008 */  lh    $a2, 8($s3)
/* 07BD54 8007B154 24070020 */  li    $a3, 32
/* 07BD58 8007B158 0C01DB9A */  jal   load_asset_to_address
/* 07BD5C 8007B15C 014C2821 */   addu  $a1, $t2, $t4
/* 07BD60 8007B160 3C0B8012 */  lui   $t3, %hi(gCiPalettesSize) # $t3, 0x8012
/* 07BD64 8007B164 8D6B6340 */  lw    $t3, %lo(gCiPalettesSize)($t3)
/* 07BD68 8007B168 3C0D8012 */  lui   $t5, %hi(gCiPalettesSize) # $t5, 0x8012
/* 07BD6C 8007B16C A66B0008 */  sh    $t3, 8($s3)
/* 07BD70 8007B170 8DAD6340 */  lw    $t5, %lo(gCiPalettesSize)($t5)
/* 07BD74 8007B174 3C018012 */  lui   $at, %hi(gCiPalettesSize) # $at, 0x8012
/* 07BD78 8007B178 25AE0020 */  addiu $t6, $t5, 0x20
/* 07BD7C 8007B17C AC2E6340 */  sw    $t6, %lo(gCiPalettesSize)($at)
/* 07BD80 8007B180 92660002 */  lbu   $a2, 2($s3)
/* 07BD84 8007B184 00000000 */  nop   
/* 07BD88 8007B188 30CF000F */  andi  $t7, $a2, 0xf
/* 07BD8C 8007B18C 01E03025 */  move  $a2, $t7
.L8007B190:
/* 07BD90 8007B190 3C038012 */  lui   $v1, %hi(gCiPalettesSize) # $v1, 0x8012
/* 07BD94 8007B194 8C636340 */  lw    $v1, %lo(gCiPalettesSize)($v1)
/* 07BD98 8007B198 00000000 */  nop   
/* 07BD9C 8007B19C 2463FFE0 */  addiu $v1, $v1, -0x20
.L8007B1A0:
/* 07BDA0 8007B1A0 3C128012 */  lui   $s2, %hi(D_80126344) # $s2, 0x8012
/* 07BDA4 8007B1A4 24010008 */  li    $at, 8
/* 07BDA8 8007B1A8 14C10016 */  bne   $a2, $at, .L8007B204
/* 07BDAC 8007B1AC 26526344 */   addiu $s2, %lo(D_80126344) # addiu $s2, $s2, 0x6344
/* 07BDB0 8007B1B0 8E580000 */  lw    $t8, ($s2)
/* 07BDB4 8007B1B4 3C108012 */  lui   $s0, %hi(gCiPalettesSize) # $s0, 0x8012
/* 07BDB8 8007B1B8 8E106340 */  lw    $s0, %lo(gCiPalettesSize)($s0)
/* 07BDBC 8007B1BC 17000010 */  bnez  $t8, .L8007B200
/* 07BDC0 8007B1C0 2404000E */   li    $a0, 14
/* 07BDC4 8007B1C4 3C198012 */  lui   $t9, %hi(gCiPalettes) # $t9, 0x8012
/* 07BDC8 8007B1C8 8F39632C */  lw    $t9, %lo(gCiPalettes)($t9)
/* 07BDCC 8007B1CC 86660008 */  lh    $a2, 8($s3)
/* 07BDD0 8007B1D0 24070080 */  li    $a3, 128
/* 07BDD4 8007B1D4 0C01DB9A */  jal   load_asset_to_address
/* 07BDD8 8007B1D8 03302821 */   addu  $a1, $t9, $s0
/* 07BDDC 8007B1DC 3C038012 */  lui   $v1, %hi(gCiPalettesSize) # $v1, 0x8012
/* 07BDE0 8007B1E0 24636340 */  addiu $v1, %lo(gCiPalettesSize) # addiu $v1, $v1, 0x6340
/* 07BDE4 8007B1E4 8C6A0000 */  lw    $t2, ($v1)
/* 07BDE8 8007B1E8 00000000 */  nop   
/* 07BDEC 8007B1EC A66A0008 */  sh    $t2, 8($s3)
/* 07BDF0 8007B1F0 8C6C0000 */  lw    $t4, ($v1)
/* 07BDF4 8007B1F4 00000000 */  nop   
/* 07BDF8 8007B1F8 25900080 */  addiu $s0, $t4, 0x80
/* 07BDFC 8007B1FC AC700000 */  sw    $s0, ($v1)
.L8007B200:
/* 07BE00 8007B200 2603FF80 */  addiu $v1, $s0, -0x80
.L8007B204:
/* 07BE04 8007B204 8FAD0058 */  lw    $t5, 0x58($sp)
/* 07BE08 8007B208 AE400000 */  sw    $zero, ($s2)
/* 07BE0C 8007B20C AFA30054 */  sw    $v1, 0x54($sp)
/* 07BE10 8007B210 0C01C614 */  jal   align16
/* 07BE14 8007B214 026D2021 */   addu  $a0, $s3, $t5
/* 07BE18 8007B218 8FA30054 */  lw    $v1, 0x54($sp)
/* 07BE1C 8007B21C 00409025 */  move  $s2, $v0
/* 07BE20 8007B220 1A80000F */  blez  $s4, .L8007B260
/* 07BE24 8007B224 02608025 */   move  $s0, $s3
.L8007B228:
/* 07BE28 8007B228 02002025 */  move  $a0, $s0
/* 07BE2C 8007B22C 02402825 */  move  $a1, $s2
/* 07BE30 8007B230 0C01F43D */  jal   build_tex_display_list
/* 07BE34 8007B234 AFA30054 */   sw    $v1, 0x54($sp)
/* 07BE38 8007B238 8FA30054 */  lw    $v1, 0x54($sp)
/* 07BE3C 8007B23C 26310001 */  addiu $s1, $s1, 1
/* 07BE40 8007B240 04600003 */  bltz  $v1, .L8007B250
/* 07BE44 8007B244 00000000 */   nop   
/* 07BE48 8007B248 A6030008 */  sh    $v1, 8($s0)
/* 07BE4C 8007B24C 26520030 */  addiu $s2, $s2, 0x30
.L8007B250:
/* 07BE50 8007B250 860E0016 */  lh    $t6, 0x16($s0)
/* 07BE54 8007B254 26520060 */  addiu $s2, $s2, 0x60
/* 07BE58 8007B258 1634FFF3 */  bne   $s1, $s4, .L8007B228
/* 07BE5C 8007B25C 020E8021 */   addu  $s0, $s0, $t6
.L8007B260:
/* 07BE60 8007B260 3C0F8012 */  lui   $t7, %hi(gCiPalettesSize) # $t7, 0x8012
/* 07BE64 8007B264 8DEF6340 */  lw    $t7, %lo(gCiPalettesSize)($t7)
/* 07BE68 8007B268 3C188012 */  lui   $t8, %hi(gNumberOfLoadedTextures) # $t8, 0x8012
/* 07BE6C 8007B26C 29E10280 */  slti  $at, $t7, 0x280
/* 07BE70 8007B270 14200003 */  bnez  $at, .L8007B280
/* 07BE74 8007B274 00000000 */   nop   
/* 07BE78 8007B278 10000008 */  b     .L8007B29C
/* 07BE7C 8007B27C 00001025 */   move  $v0, $zero
.L8007B280:
/* 07BE80 8007B280 8F186330 */  lw    $t8, %lo(gNumberOfLoadedTextures)($t8)
/* 07BE84 8007B284 02601025 */  move  $v0, $s3
/* 07BE88 8007B288 2B0102BD */  slti  $at, $t8, 0x2bd
/* 07BE8C 8007B28C 14200003 */  bnez  $at, .L8007B29C
/* 07BE90 8007B290 00000000 */   nop   
/* 07BE94 8007B294 10000001 */  b     .L8007B29C
/* 07BE98 8007B298 00001025 */   move  $v0, $zero
.L8007B29C:
/* 07BE9C 8007B29C 8FBF002C */  lw    $ra, 0x2c($sp)
/* 07BEA0 8007B2A0 8FB00018 */  lw    $s0, 0x18($sp)
/* 07BEA4 8007B2A4 8FB1001C */  lw    $s1, 0x1c($sp)
/* 07BEA8 8007B2A8 8FB20020 */  lw    $s2, 0x20($sp)
/* 07BEAC 8007B2AC 8FB30024 */  lw    $s3, 0x24($sp)
/* 07BEB0 8007B2B0 8FB40028 */  lw    $s4, 0x28($sp)
/* 07BEB4 8007B2B4 03E00008 */  jr    $ra
/* 07BEB8 8007B2B8 27BD0070 */   addiu $sp, $sp, 0x70

