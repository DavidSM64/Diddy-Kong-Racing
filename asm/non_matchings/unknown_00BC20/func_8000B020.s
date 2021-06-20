glabel func_8000B020
/* 00BC20 8000B020 27BDFF98 */  addiu $sp, $sp, -0x68
/* 00BC24 8000B024 AFB10020 */  sw    $s1, 0x20($sp)
/* 00BC28 8000B028 00048880 */  sll   $s1, $a0, 2
/* 00BC2C 8000B02C AFB30028 */  sw    $s3, 0x28($sp)
/* 00BC30 8000B030 AFB0001C */  sw    $s0, 0x1c($sp)
/* 00BC34 8000B034 02248821 */  addu  $s1, $s1, $a0
/* 00BC38 8000B038 00809825 */  move  $s3, $a0
/* 00BC3C 8000B03C 00118840 */  sll   $s1, $s1, 1
/* 00BC40 8000B040 00058100 */  sll   $s0, $a1, 4
/* 00BC44 8000B044 AFB20024 */  sw    $s2, 0x24($sp)
/* 00BC48 8000B048 02112021 */  addu  $a0, $s0, $s1
/* 00BC4C 8000B04C 00A09025 */  move  $s2, $a1
/* 00BC50 8000B050 AFBF003C */  sw    $ra, 0x3c($sp)
/* 00BC54 8000B054 00047040 */  sll   $t6, $a0, 1
/* 00BC58 8000B058 AFB70038 */  sw    $s7, 0x38($sp)
/* 00BC5C 8000B05C AFB60034 */  sw    $s6, 0x34($sp)
/* 00BC60 8000B060 AFB50030 */  sw    $s5, 0x30($sp)
/* 00BC64 8000B064 AFB4002C */  sw    $s4, 0x2c($sp)
/* 00BC68 8000B068 E7B50010 */  swc1  $f21, 0x10($sp)
/* 00BC6C 8000B06C E7B40014 */  swc1  $f20, 0x14($sp)
/* 00BC70 8000B070 01C02025 */  move  $a0, $t6
/* 00BC74 8000B074 0C01C327 */  jal   allocate_from_main_pool_safe
/* 00BC78 8000B078 3405FFFF */   li    $a1, 65535
/* 00BC7C 8000B07C 3C03800E */  lui   $v1, %hi(D_800DC754) # $v1, 0x800e
/* 00BC80 8000B080 3C05800E */  lui   $a1, %hi(D_800DC74C) # $a1, 0x800e
/* 00BC84 8000B084 0050C021 */  addu  $t8, $v0, $s0
/* 00BC88 8000B088 24A5C74C */  addiu $a1, %lo(D_800DC74C) # addiu $a1, $a1, -0x38b4
/* 00BC8C 8000B08C 2463C754 */  addiu $v1, %lo(D_800DC754) # addiu $v1, $v1, -0x38ac
/* 00BC90 8000B090 03104021 */  addu  $t0, $t8, $s0
/* 00BC94 8000B094 01115021 */  addu  $t2, $t0, $s1
/* 00BC98 8000B098 AC620000 */  sw    $v0, ($v1)
/* 00BC9C 8000B09C AC780004 */  sw    $t8, 4($v1)
/* 00BCA0 8000B0A0 ACA80000 */  sw    $t0, ($a1)
/* 00BCA4 8000B0A4 ACAA0004 */  sw    $t2, 4($a1)
/* 00BCA8 8000B0A8 3C018012 */  lui   $at, %hi(D_8011AFF8) # $at, 0x8012
/* 00BCAC 8000B0AC AC33AFF8 */  sw    $s3, %lo(D_8011AFF8)($at)
/* 00BCB0 8000B0B0 3C018012 */  lui   $at, %hi(D_8011AFFC) # $at, 0x8012
/* 00BCB4 8000B0B4 AC20AFFC */  sw    $zero, %lo(D_8011AFFC)($at)
/* 00BCB8 8000B0B8 3C018012 */  lui   $at, %hi(D_8011B000) # $at, 0x8012
/* 00BCBC 8000B0BC AC32B000 */  sw    $s2, %lo(D_8011B000)($at)
/* 00BCC0 8000B0C0 3C018012 */  lui   $at, %hi(D_8011B004) # $at, 0x8012
/* 00BCC4 8000B0C4 AC20B004 */  sw    $zero, %lo(D_8011B004)($at)
/* 00BCC8 8000B0C8 3C018012 */  lui   $at, %hi(D_8011B008) # $at, 0x8012
/* 00BCCC 8000B0CC AC20B008 */  sw    $zero, %lo(D_8011B008)($at)
/* 00BCD0 8000B0D0 0C0078A7 */  jal   func_8001E29C
/* 00BCD4 8000B0D4 24040014 */   li    $a0, 20
/* 00BCD8 8000B0D8 3C118012 */  lui   $s1, %hi(D_8011B020) # $s1, 0x8012
/* 00BCDC 8000B0DC 3C138012 */  lui   $s3, %hi(D_8011B068) # $s3, 0x8012
/* 00BCE0 8000B0E0 4480A000 */  mtc1  $zero, $f20
/* 00BCE4 8000B0E4 0040A825 */  move  $s5, $v0
/* 00BCE8 8000B0E8 2673B068 */  addiu $s3, %lo(D_8011B068) # addiu $s3, $s3, -0x4f98
/* 00BCEC 8000B0EC 2631B020 */  addiu $s1, %lo(D_8011B020) # addiu $s1, $s1, -0x4fe0
/* 00BCF0 8000B0F0 00009025 */  move  $s2, $zero
/* 00BCF4 8000B0F4 27B70058 */  addiu $s7, $sp, 0x58
/* 00BCF8 8000B0F8 24160001 */  li    $s6, 1
.L8000B0FC:
/* 00BCFC 8000B0FC 240B007E */  li    $t3, 126
/* 00BD00 8000B100 240C000A */  li    $t4, 10
/* 00BD04 8000B104 A3AB0058 */  sb    $t3, 0x58($sp)
/* 00BD08 8000B108 A3AC0059 */  sb    $t4, 0x59($sp)
/* 00BD0C 8000B10C A7A0005A */  sh    $zero, 0x5a($sp)
/* 00BD10 8000B110 A7A0005C */  sh    $zero, 0x5c($sp)
/* 00BD14 8000B114 A7A0005E */  sh    $zero, 0x5e($sp)
/* 00BD18 8000B118 A3B20060 */  sb    $s2, 0x60($sp)
/* 00BD1C 8000B11C 02E02025 */  move  $a0, $s7
/* 00BD20 8000B120 0C003A95 */  jal   func_8000EA54
/* 00BD24 8000B124 24050001 */   li    $a1, 1
/* 00BD28 8000B128 1040001B */  beqz  $v0, .L8000B198
/* 00BD2C 8000B12C AE220000 */   sw    $v0, ($s1)
/* 00BD30 8000B130 AC400078 */  sw    $zero, 0x78($v0)
/* 00BD34 8000B134 8E2E0000 */  lw    $t6, ($s1)
/* 00BD38 8000B138 001279C0 */  sll   $t7, $s2, 7
/* 00BD3C 8000B13C 02AF8021 */  addu  $s0, $s5, $t7
/* 00BD40 8000B140 3C188012 */  lui   $t8, %hi(D_8011B010) # $t8, 0x8012
/* 00BD44 8000B144 ADC0007C */  sw    $zero, 0x7c($t6)
/* 00BD48 8000B148 8604006C */  lh    $a0, 0x6c($s0)
/* 00BD4C 8000B14C 2718B010 */  addiu $t8, %lo(D_8011B010) # addiu $t8, $t8, -0x4ff0
/* 00BD50 8000B150 A2000070 */  sb    $zero, 0x70($s0)
/* 00BD54 8000B154 E6140074 */  swc1  $f20, 0x74($s0)
/* 00BD58 8000B158 0258A021 */  addu  $s4, $s2, $t8
/* 00BD5C 8000B15C 0C01F04B */  jal   func_8007C12C
/* 00BD60 8000B160 00002825 */   move  $a1, $zero
/* 00BD64 8000B164 8604006E */  lh    $a0, 0x6e($s0)
/* 00BD68 8000B168 0C01EB9D */  jal   func_8007AE74
/* 00BD6C 8000B16C AE020078 */   sw    $v0, 0x78($s0)
/* 00BD70 8000B170 AE02007C */  sw    $v0, 0x7c($s0)
/* 00BD74 8000B174 00002025 */  move  $a0, $zero
/* 00BD78 8000B178 0C01BE53 */  jal   get_random_number_from_range
/* 00BD7C 8000B17C 240500FF */   li    $a1, 255
/* 00BD80 8000B180 A2020072 */  sb    $v0, 0x72($s0)
/* 00BD84 8000B184 A2000073 */  sb    $zero, 0x73($s0)
/* 00BD88 8000B188 00002025 */  move  $a0, $zero
/* 00BD8C 8000B18C 0C01BE53 */  jal   get_random_number_from_range
/* 00BD90 8000B190 240500FF */   li    $a1, 255
/* 00BD94 8000B194 A2820000 */  sb    $v0, ($s4)
.L8000B198:
/* 00BD98 8000B198 26520001 */  addiu $s2, $s2, 1
/* 00BD9C 8000B19C 2A41000A */  slti  $at, $s2, 0xa
/* 00BDA0 8000B1A0 26310004 */  addiu $s1, $s1, 4
/* 00BDA4 8000B1A4 26730001 */  addiu $s3, $s3, 1
/* 00BDA8 8000B1A8 1420FFD4 */  bnez  $at, .L8000B0FC
/* 00BDAC 8000B1AC A276FFFF */   sb    $s6, -1($s3)
/* 00BDB0 8000B1B0 24190009 */  li    $t9, 9
/* 00BDB4 8000B1B4 3C01800E */  lui   $at, %hi(D_800DC760) # $at, 0x800e
/* 00BDB8 8000B1B8 2408008D */  li    $t0, 141
/* 00BDBC 8000B1BC 2409000A */  li    $t1, 10
/* 00BDC0 8000B1C0 AC39C760 */  sw    $t9, %lo(D_800DC760)($at)
/* 00BDC4 8000B1C4 A3A80058 */  sb    $t0, 0x58($sp)
/* 00BDC8 8000B1C8 A3A90059 */  sb    $t1, 0x59($sp)
/* 00BDCC 8000B1CC A7A0005A */  sh    $zero, 0x5a($sp)
/* 00BDD0 8000B1D0 A7A0005C */  sh    $zero, 0x5c($sp)
/* 00BDD4 8000B1D4 A7A0005E */  sh    $zero, 0x5e($sp)
/* 00BDD8 8000B1D8 02E02025 */  move  $a0, $s7
/* 00BDDC 8000B1DC 0C003A95 */  jal   func_8000EA54
/* 00BDE0 8000B1E0 00002825 */   move  $a1, $zero
/* 00BDE4 8000B1E4 3C01800E */  lui   $at, %hi(D_800DC75C) # $at, 0x800e
/* 00BDE8 8000B1E8 3C108012 */  lui   $s0, %hi(D_8011B078) # $s0, 0x8012
/* 00BDEC 8000B1EC 3C118012 */  lui   $s1, %hi(D_8011B0A0) # $s1, 0x8012
/* 00BDF0 8000B1F0 AC22C75C */  sw    $v0, %lo(D_800DC75C)($at)
/* 00BDF4 8000B1F4 2631B0A0 */  addiu $s1, %lo(D_8011B0A0) # addiu $s1, $s1, -0x4f60
/* 00BDF8 8000B1F8 2610B078 */  addiu $s0, %lo(D_8011B078) # addiu $s0, $s0, -0x4f88
.L8000B1FC:
/* 00BDFC 8000B1FC A2000000 */  sb    $zero, ($s0)
/* 00BE00 8000B200 00002025 */  move  $a0, $zero
/* 00BE04 8000B204 0C01BE53 */  jal   get_random_number_from_range
/* 00BE08 8000B208 240500FF */   li    $a1, 255
/* 00BE0C 8000B20C A2020001 */  sb    $v0, 1($s0)
/* 00BE10 8000B210 00002025 */  move  $a0, $zero
/* 00BE14 8000B214 0C01BE53 */  jal   get_random_number_from_range
/* 00BE18 8000B218 240500FF */   li    $a1, 255
/* 00BE1C 8000B21C 26100004 */  addiu $s0, $s0, 4
/* 00BE20 8000B220 A202FFFE */  sb    $v0, -2($s0)
/* 00BE24 8000B224 1611FFF5 */  bne   $s0, $s1, .L8000B1FC
/* 00BE28 8000B228 A200FFFF */   sb    $zero, -1($s0)
/* 00BE2C 8000B22C 240A001B */  li    $t2, 27
/* 00BE30 8000B230 240B008A */  li    $t3, 138
/* 00BE34 8000B234 A3AA0058 */  sb    $t2, 0x58($sp)
/* 00BE38 8000B238 A3AB0059 */  sb    $t3, 0x59($sp)
/* 00BE3C 8000B23C A7A0005A */  sh    $zero, 0x5a($sp)
/* 00BE40 8000B240 A7A0005C */  sh    $zero, 0x5c($sp)
/* 00BE44 8000B244 A7A0005E */  sh    $zero, 0x5e($sp)
/* 00BE48 8000B248 02E02025 */  move  $a0, $s7
/* 00BE4C 8000B24C 0C003A95 */  jal   func_8000EA54
/* 00BE50 8000B250 00002825 */   move  $a1, $zero
/* 00BE54 8000B254 8FBF003C */  lw    $ra, 0x3c($sp)
/* 00BE58 8000B258 3C01800E */  lui   $at, %hi(D_800DC764) # $at, 0x800e
/* 00BE5C 8000B25C C7B50010 */  lwc1  $f21, 0x10($sp)
/* 00BE60 8000B260 C7B40014 */  lwc1  $f20, 0x14($sp)
/* 00BE64 8000B264 8FB0001C */  lw    $s0, 0x1c($sp)
/* 00BE68 8000B268 8FB10020 */  lw    $s1, 0x20($sp)
/* 00BE6C 8000B26C 8FB20024 */  lw    $s2, 0x24($sp)
/* 00BE70 8000B270 8FB30028 */  lw    $s3, 0x28($sp)
/* 00BE74 8000B274 8FB4002C */  lw    $s4, 0x2c($sp)
/* 00BE78 8000B278 8FB50030 */  lw    $s5, 0x30($sp)
/* 00BE7C 8000B27C 8FB60034 */  lw    $s6, 0x34($sp)
/* 00BE80 8000B280 8FB70038 */  lw    $s7, 0x38($sp)
/* 00BE84 8000B284 AC22C764 */  sw    $v0, %lo(D_800DC764)($at)
/* 00BE88 8000B288 03E00008 */  jr    $ra
/* 00BE8C 8000B28C 27BD0068 */   addiu $sp, $sp, 0x68

