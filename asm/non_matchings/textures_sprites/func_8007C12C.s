glabel func_8007C12C
/* 07CD2C 8007C12C 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 07CD30 8007C130 AFB10018 */  sw    $s1, 0x18($sp)
/* 07CD34 8007C134 3C018012 */  lui   $at, %hi(D_8012635C) # $at, 0x8012
/* 07CD38 8007C138 00808825 */  move  $s1, $a0
/* 07CD3C 8007C13C AFBF002C */  sw    $ra, 0x2c($sp)
/* 07CD40 8007C140 AFB50028 */  sw    $s5, 0x28($sp)
/* 07CD44 8007C144 AFB40024 */  sw    $s4, 0x24($sp)
/* 07CD48 8007C148 AFB30020 */  sw    $s3, 0x20($sp)
/* 07CD4C 8007C14C AFB2001C */  sw    $s2, 0x1c($sp)
/* 07CD50 8007C150 AFB00014 */  sw    $s0, 0x14($sp)
/* 07CD54 8007C154 04800007 */  bltz  $a0, .L8007C174
/* 07CD58 8007C158 AC25635C */   sw    $a1, %lo(D_8012635C)($at)
/* 07CD5C 8007C15C 3C0E8012 */  lui   $t6, %hi(gSpriteTableNum) # $t6, 0x8012
/* 07CD60 8007C160 8DCE6354 */  lw    $t6, %lo(gSpriteTableNum)($t6)
/* 07CD64 8007C164 3C0A8012 */  lui   $t2, %hi(D_80126358) # $t2, 0x8012
/* 07CD68 8007C168 008E082A */  slt   $at, $a0, $t6
/* 07CD6C 8007C16C 14200003 */  bnez  $at, .L8007C17C
/* 07CD70 8007C170 254A6358 */   addiu $t2, %lo(D_80126358) # addiu $t2, $t2, 0x6358
.L8007C174:
/* 07CD74 8007C174 100000E4 */  b     .L8007C508
/* 07CD78 8007C178 00001025 */   move  $v0, $zero
.L8007C17C:
/* 07CD7C 8007C17C 8D440000 */  lw    $a0, ($t2)
/* 07CD80 8007C180 00008025 */  move  $s0, $zero
/* 07CD84 8007C184 18800014 */  blez  $a0, .L8007C1D8
/* 07CD88 8007C188 00004825 */   move  $t1, $zero
/* 07CD8C 8007C18C 3C028012 */  lui   $v0, %hi(gSpriteCache) # $v0, 0x8012
/* 07CD90 8007C190 8C42634C */  lw    $v0, %lo(gSpriteCache)($v0)
/* 07CD94 8007C194 00000000 */  nop   
/* 07CD98 8007C198 0010C0C0 */  sll   $t8, $s0, 3
.L8007C19C:
/* 07CD9C 8007C19C 00581821 */  addu  $v1, $v0, $t8
/* 07CDA0 8007C1A0 8C790000 */  lw    $t9, ($v1)
/* 07CDA4 8007C1A4 26100001 */  addiu $s0, $s0, 1
/* 07CDA8 8007C1A8 16390008 */  bne   $s1, $t9, .L8007C1CC
/* 07CDAC 8007C1AC 0204082A */   slt   $at, $s0, $a0
/* 07CDB0 8007C1B0 8C620004 */  lw    $v0, 4($v1)
/* 07CDB4 8007C1B4 00000000 */  nop   
/* 07CDB8 8007C1B8 844B0004 */  lh    $t3, 4($v0)
/* 07CDBC 8007C1BC 00000000 */  nop   
/* 07CDC0 8007C1C0 256C0001 */  addiu $t4, $t3, 1
/* 07CDC4 8007C1C4 100000D0 */  b     .L8007C508
/* 07CDC8 8007C1C8 A44C0004 */   sh    $t4, 4($v0)
.L8007C1CC:
/* 07CDCC 8007C1CC 1420FFF3 */  bnez  $at, .L8007C19C
/* 07CDD0 8007C1D0 0010C0C0 */   sll   $t8, $s0, 3
/* 07CDD4 8007C1D4 00008025 */  move  $s0, $zero
.L8007C1D8:
/* 07CDD8 8007C1D8 1880000F */  blez  $a0, .L8007C218
/* 07CDDC 8007C1DC 2408FFFF */   li    $t0, -1
/* 07CDE0 8007C1E0 3C028012 */  lui   $v0, %hi(gSpriteCache) # $v0, 0x8012
/* 07CDE4 8007C1E4 8C42634C */  lw    $v0, %lo(gSpriteCache)($v0)
/* 07CDE8 8007C1E8 2403FFFF */  li    $v1, -1
/* 07CDEC 8007C1EC 001070C0 */  sll   $t6, $s0, 3
.L8007C1F0:
/* 07CDF0 8007C1F0 004E7821 */  addu  $t7, $v0, $t6
/* 07CDF4 8007C1F4 8DF80000 */  lw    $t8, ($t7)
/* 07CDF8 8007C1F8 00000000 */  nop   
/* 07CDFC 8007C1FC 14780002 */  bne   $v1, $t8, .L8007C208
/* 07CE00 8007C200 00000000 */   nop   
/* 07CE04 8007C204 02004025 */  move  $t0, $s0
.L8007C208:
/* 07CE08 8007C208 26100001 */  addiu $s0, $s0, 1
/* 07CE0C 8007C20C 0204082A */  slt   $at, $s0, $a0
/* 07CE10 8007C210 1420FFF7 */  bnez  $at, .L8007C1F0
/* 07CE14 8007C214 001070C0 */   sll   $t6, $s0, 3
.L8007C218:
/* 07CE18 8007C218 2403FFFF */  li    $v1, -1
/* 07CE1C 8007C21C 15030005 */  bne   $t0, $v1, .L8007C234
/* 07CE20 8007C220 3C0B8012 */   lui   $t3, %hi(gSpriteOffsetTable) # $t3, 0x8012
/* 07CE24 8007C224 24990001 */  addiu $t9, $a0, 1
/* 07CE28 8007C228 24090001 */  li    $t1, 1
/* 07CE2C 8007C22C 00804025 */  move  $t0, $a0
/* 07CE30 8007C230 AD590000 */  sw    $t9, ($t2)
.L8007C234:
/* 07CE34 8007C234 8D6B6348 */  lw    $t3, %lo(gSpriteOffsetTable)($t3)
/* 07CE38 8007C238 00116080 */  sll   $t4, $s1, 2
/* 07CE3C 8007C23C 016C1021 */  addu  $v0, $t3, $t4
/* 07CE40 8007C240 8C460000 */  lw    $a2, ($v0)
/* 07CE44 8007C244 8C4D0004 */  lw    $t5, 4($v0)
/* 07CE48 8007C248 3C148012 */  lui   $s4, %hi(gCurrentSprite) # $s4, 0x8012
/* 07CE4C 8007C24C 8E946350 */  lw    $s4, %lo(gCurrentSprite)($s4)
/* 07CE50 8007C250 AFB10050 */  sw    $s1, 0x50($sp)
/* 07CE54 8007C254 A3A90032 */  sb    $t1, 0x32($sp)
/* 07CE58 8007C258 AFA80044 */  sw    $t0, 0x44($sp)
/* 07CE5C 8007C25C 2404000C */  li    $a0, 12
/* 07CE60 8007C260 01A63823 */  subu  $a3, $t5, $a2
/* 07CE64 8007C264 0C01DB9A */  jal   load_asset_to_address
/* 07CE68 8007C268 02802825 */   move  $a1, $s4
/* 07CE6C 8007C26C 86850002 */  lh    $a1, 2($s4)
/* 07CE70 8007C270 24040010 */  li    $a0, 16
/* 07CE74 8007C274 02857021 */  addu  $t6, $s4, $a1
/* 07CE78 8007C278 91D5000C */  lbu   $s5, 0xc($t6)
/* 07CE7C 8007C27C 000558C0 */  sll   $t3, $a1, 3
/* 07CE80 8007C280 00151880 */  sll   $v1, $s5, 2
/* 07CE84 8007C284 00037880 */  sll   $t7, $v1, 2
/* 07CE88 8007C288 01E37821 */  addu  $t7, $t7, $v1
/* 07CE8C 8007C28C 000F7840 */  sll   $t7, $t7, 1
/* 07CE90 8007C290 0003C0C0 */  sll   $t8, $v1, 3
/* 07CE94 8007C294 01F8C821 */  addu  $t9, $t7, $t8
/* 07CE98 8007C298 032B8021 */  addu  $s0, $t9, $t3
/* 07CE9C 8007C29C 00156940 */  sll   $t5, $s5, 5
/* 07CEA0 8007C2A0 020D8021 */  addu  $s0, $s0, $t5
/* 07CEA4 8007C2A4 0C01C614 */  jal   align16
/* 07CEA8 8007C2A8 02038021 */   addu  $s0, $s0, $v1
/* 07CEAC 8007C2AC 86840002 */  lh    $a0, 2($s4)
/* 07CEB0 8007C2B0 02028021 */  addu  $s0, $s0, $v0
/* 07CEB4 8007C2B4 00047080 */  sll   $t6, $a0, 2
/* 07CEB8 8007C2B8 0C01C614 */  jal   align16
/* 07CEBC 8007C2BC 01C02025 */   move  $a0, $t6
/* 07CEC0 8007C2C0 3C05FF00 */  lui   $a1, (0xFF00FFFF >> 16) # lui $a1, 0xff00
/* 07CEC4 8007C2C4 02022021 */  addu  $a0, $s0, $v0
/* 07CEC8 8007C2C8 0C01C344 */  jal   mempool_alloc
/* 07CECC 8007C2CC 34A5FFFF */   ori   $a1, (0xFF00FFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 07CED0 8007C2D0 1440000B */  bnez  $v0, .L8007C300
/* 07CED4 8007C2D4 00409825 */   move  $s3, $v0
/* 07CED8 8007C2D8 83AF0032 */  lb    $t7, 0x32($sp)
/* 07CEDC 8007C2DC 3C028012 */  lui   $v0, %hi(D_80126358) # $v0, 0x8012
/* 07CEE0 8007C2E0 11E00005 */  beqz  $t7, .L8007C2F8
/* 07CEE4 8007C2E4 24426358 */   addiu $v0, %lo(D_80126358) # addiu $v0, $v0, 0x6358
/* 07CEE8 8007C2E8 8C580000 */  lw    $t8, ($v0)
/* 07CEEC 8007C2EC 00000000 */  nop   
/* 07CEF0 8007C2F0 2719FFFF */  addiu $t9, $t8, -1
/* 07CEF4 8007C2F4 AC590000 */  sw    $t9, ($v0)
.L8007C2F8:
/* 07CEF8 8007C2F8 10000083 */  b     .L8007C508
/* 07CEFC 8007C2FC 00001025 */   move  $v0, $zero
.L8007C300:
/* 07CF00 8007C300 24040010 */  li    $a0, 16
/* 07CF04 8007C304 0C01C614 */  jal   align16
/* 07CF08 8007C308 00008025 */   move  $s0, $zero
/* 07CF0C 8007C30C 86840002 */  lh    $a0, 2($s4)
/* 07CF10 8007C310 00408825 */  move  $s1, $v0
/* 07CF14 8007C314 00045880 */  sll   $t3, $a0, 2
/* 07CF18 8007C318 0C01C614 */  jal   align16
/* 07CF1C 8007C31C 01602025 */   move  $a0, $t3
/* 07CF20 8007C320 00536021 */  addu  $t4, $v0, $s3
/* 07CF24 8007C324 01916821 */  addu  $t5, $t4, $s1
/* 07CF28 8007C328 3C058012 */  lui   $a1, %hi(D_80126368) # $a1, 0x8012
/* 07CF2C 8007C32C 3C078012 */  lui   $a3, %hi(D_80126364) # $a3, 0x8012
/* 07CF30 8007C330 00152140 */  sll   $a0, $s5, 5
/* 07CF34 8007C334 24E76364 */  addiu $a3, %lo(D_80126364) # addiu $a3, $a3, 0x6364
/* 07CF38 8007C338 24A56368 */  addiu $a1, %lo(D_80126368) # addiu $a1, $a1, 0x6368
/* 07CF3C 8007C33C 01A47821 */  addu  $t7, $t5, $a0
/* 07CF40 8007C340 ACAD0000 */  sw    $t5, ($a1)
/* 07CF44 8007C344 ACEF0000 */  sw    $t7, ($a3)
/* 07CF48 8007C348 868B0002 */  lh    $t3, 2($s4)
/* 07CF4C 8007C34C 01E4C821 */  addu  $t9, $t7, $a0
/* 07CF50 8007C350 00157880 */  sll   $t7, $s5, 2
/* 07CF54 8007C354 000B60C0 */  sll   $t4, $t3, 3
/* 07CF58 8007C358 3C068012 */  lui   $a2, %hi(D_80126360) # $a2, 0x8012
/* 07CF5C 8007C35C 032C6821 */  addu  $t5, $t9, $t4
/* 07CF60 8007C360 01F57821 */  addu  $t7, $t7, $s5
/* 07CF64 8007C364 24C66360 */  addiu $a2, %lo(D_80126360) # addiu $a2, $a2, 0x6360
/* 07CF68 8007C368 000F78C0 */  sll   $t7, $t7, 3
/* 07CF6C 8007C36C ACCD0000 */  sw    $t5, ($a2)
/* 07CF70 8007C370 01AFC021 */  addu  $t8, $t5, $t7
/* 07CF74 8007C374 AE780008 */  sw    $t8, 8($s3)
/* 07CF78 8007C378 1AA0001E */  blez  $s5, .L8007C3F4
/* 07CF7C 8007C37C 00001825 */   move  $v1, $zero
/* 07CF80 8007C380 3C12800E */  lui   $s2, %hi(gTexColourTag) # $s2, 0x800e
/* 07CF84 8007C384 2652E7C0 */  addiu $s2, %lo(gTexColourTag) # addiu $s2, $s2, -0x1840
/* 07CF88 8007C388 00008825 */  move  $s1, $zero
.L8007C38C:
/* 07CF8C 8007C38C 3C0B00FF */  lui   $t3, (0x00FF0163 >> 16) # lui $t3, 0xff
/* 07CF90 8007C390 356B0163 */  ori   $t3, (0x00FF0163 & 0xFFFF) # ori $t3, $t3, 0x163
/* 07CF94 8007C394 AE4B0000 */  sw    $t3, ($s2)
/* 07CF98 8007C398 86990000 */  lh    $t9, ($s4)
/* 07CF9C 8007C39C A3A30033 */  sb    $v1, 0x33($sp)
/* 07CFA0 8007C3A0 0C01EB9D */  jal   load_texture
/* 07CFA4 8007C3A4 03302021 */   addu  $a0, $t9, $s0
/* 07CFA8 8007C3A8 8E6C0008 */  lw    $t4, 8($s3)
/* 07CFAC 8007C3AC 83A30033 */  lb    $v1, 0x33($sp)
/* 07CFB0 8007C3B0 01916821 */  addu  $t5, $t4, $s1
/* 07CFB4 8007C3B4 ADA20000 */  sw    $v0, ($t5)
/* 07CFB8 8007C3B8 8E6E0008 */  lw    $t6, 8($s3)
/* 07CFBC 8007C3BC 3C0BFF00 */  lui   $t3, (0xFF00FFFF >> 16) # lui $t3, 0xff00
/* 07CFC0 8007C3C0 01D17821 */  addu  $t7, $t6, $s1
/* 07CFC4 8007C3C4 8DF80000 */  lw    $t8, ($t7)
/* 07CFC8 8007C3C8 356BFFFF */  ori   $t3, (0xFF00FFFF & 0xFFFF) # ori $t3, $t3, 0xffff
/* 07CFCC 8007C3CC 17000002 */  bnez  $t8, .L8007C3D8
/* 07CFD0 8007C3D0 24190001 */   li    $t9, 1
/* 07CFD4 8007C3D4 24030001 */  li    $v1, 1
.L8007C3D8:
/* 07CFD8 8007C3D8 26100001 */  addiu $s0, $s0, 1
/* 07CFDC 8007C3DC AE4B0000 */  sw    $t3, ($s2)
/* 07CFE0 8007C3E0 3C018012 */  lui   $at, %hi(D_80126344) # $at, 0x8012
/* 07CFE4 8007C3E4 26310004 */  addiu $s1, $s1, 4
/* 07CFE8 8007C3E8 1615FFE8 */  bne   $s0, $s5, .L8007C38C
/* 07CFEC 8007C3EC AC396344 */   sw    $t9, %lo(D_80126344)($at)
/* 07CFF0 8007C3F0 00008025 */  move  $s0, $zero
.L8007C3F4:
/* 07CFF4 8007C3F4 3C018012 */  lui   $at, %hi(D_80126344) # $at, 0x8012
/* 07CFF8 8007C3F8 1060001B */  beqz  $v1, .L8007C468
/* 07CFFC 8007C3FC AC206344 */   sw    $zero, %lo(D_80126344)($at)
/* 07D000 8007C400 1AA0000D */  blez  $s5, .L8007C438
/* 07D004 8007C404 00008825 */   move  $s1, $zero
.L8007C408:
/* 07D008 8007C408 8E6C0008 */  lw    $t4, 8($s3)
/* 07D00C 8007C40C 00000000 */  nop   
/* 07D010 8007C410 01916821 */  addu  $t5, $t4, $s1
/* 07D014 8007C414 8DA40000 */  lw    $a0, ($t5)
/* 07D018 8007C418 00000000 */  nop   
/* 07D01C 8007C41C 10800003 */  beqz  $a0, .L8007C42C
/* 07D020 8007C420 00000000 */   nop   
/* 07D024 8007C424 0C01ECAF */  jal   free_texture
/* 07D028 8007C428 00000000 */   nop   
.L8007C42C:
/* 07D02C 8007C42C 26100001 */  addiu $s0, $s0, 1
/* 07D030 8007C430 1615FFF5 */  bne   $s0, $s5, .L8007C408
/* 07D034 8007C434 26310004 */   addiu $s1, $s1, 4
.L8007C438:
/* 07D038 8007C438 83AE0032 */  lb    $t6, 0x32($sp)
/* 07D03C 8007C43C 3C028012 */  lui   $v0, %hi(D_80126358) # $v0, 0x8012
/* 07D040 8007C440 11C00005 */  beqz  $t6, .L8007C458
/* 07D044 8007C444 24426358 */   addiu $v0, %lo(D_80126358) # addiu $v0, $v0, 0x6358
/* 07D048 8007C448 8C4F0000 */  lw    $t7, ($v0)
/* 07D04C 8007C44C 00000000 */  nop   
/* 07D050 8007C450 25F8FFFF */  addiu $t8, $t7, -1
/* 07D054 8007C454 AC580000 */  sw    $t8, ($v0)
.L8007C458:
/* 07D058 8007C458 0C01C450 */  jal   mempool_free
/* 07D05C 8007C45C 02602025 */   move  $a0, $s3
/* 07D060 8007C460 10000029 */  b     .L8007C508
/* 07D064 8007C464 00001025 */   move  $v0, $zero
.L8007C468:
/* 07D068 8007C468 A6750002 */  sh    $s5, 2($s3)
/* 07D06C 8007C46C 868B0002 */  lh    $t3, 2($s4)
/* 07D070 8007C470 02608825 */  move  $s1, $s3
/* 07D074 8007C474 A66B0000 */  sh    $t3, ($s3)
/* 07D078 8007C478 86990002 */  lh    $t9, 2($s4)
/* 07D07C 8007C47C 00000000 */  nop   
/* 07D080 8007C480 1B20000D */  blez  $t9, .L8007C4B8
.L8007C484:
/* 07D084 8007C484 3C078012 */   lui   $a3, %hi(D_80126364) # $a3, 0x8012
/* 07D088 8007C488 24E76364 */  addiu $a3, %lo(D_80126364) # addiu $a3, $a3, 0x6364
/* 07D08C 8007C48C 8CEC0000 */  lw    $t4, ($a3)
/* 07D090 8007C490 02802025 */  move  $a0, $s4
/* 07D094 8007C494 02602825 */  move  $a1, $s3
/* 07D098 8007C498 02003025 */  move  $a2, $s0
/* 07D09C 8007C49C 0C01F370 */  jal   func_8007CDC0
/* 07D0A0 8007C4A0 AE2C000C */   sw    $t4, 0xc($s1)
/* 07D0A4 8007C4A4 868D0002 */  lh    $t5, 2($s4)
/* 07D0A8 8007C4A8 26100001 */  addiu $s0, $s0, 1
/* 07D0AC 8007C4AC 020D082A */  slt   $at, $s0, $t5
/* 07D0B0 8007C4B0 1420FFF4 */  bnez  $at, .L8007C484
/* 07D0B4 8007C4B4 26310004 */   addiu $s1, $s1, 4
.L8007C4B8:
/* 07D0B8 8007C4B8 3C0E8012 */  lui   $t6, %hi(D_80126358) # $t6, 0x8012
/* 07D0BC 8007C4BC 8DCE6358 */  lw    $t6, %lo(D_80126358)($t6)
/* 07D0C0 8007C4C0 3C048012 */  lui   $a0, %hi(gSpriteCache) # $a0, 0x8012
/* 07D0C4 8007C4C4 29C10064 */  slti  $at, $t6, 0x64
/* 07D0C8 8007C4C8 14200003 */  bnez  $at, .L8007C4D8
/* 07D0CC 8007C4CC 2484634C */   addiu $a0, %lo(gSpriteCache) # addiu $a0, $a0, 0x634c
/* 07D0D0 8007C4D0 1000000D */  b     .L8007C508
/* 07D0D4 8007C4D4 00001025 */   move  $v0, $zero
.L8007C4D8:
/* 07D0D8 8007C4D8 8FAF0044 */  lw    $t7, 0x44($sp)
/* 07D0DC 8007C4DC 8C990000 */  lw    $t9, ($a0)
/* 07D0E0 8007C4E0 8FAB0050 */  lw    $t3, 0x50($sp)
/* 07D0E4 8007C4E4 000FC0C0 */  sll   $t8, $t7, 3
/* 07D0E8 8007C4E8 03386021 */  addu  $t4, $t9, $t8
/* 07D0EC 8007C4EC AD8B0000 */  sw    $t3, ($t4)
/* 07D0F0 8007C4F0 8C8D0000 */  lw    $t5, ($a0)
/* 07D0F4 8007C4F4 240F0001 */  li    $t7, 1
/* 07D0F8 8007C4F8 01B87021 */  addu  $t6, $t5, $t8
/* 07D0FC 8007C4FC ADD30004 */  sw    $s3, 4($t6)
/* 07D100 8007C500 A66F0004 */  sh    $t7, 4($s3)
/* 07D104 8007C504 02601025 */  move  $v0, $s3
.L8007C508:
/* 07D108 8007C508 8FBF002C */  lw    $ra, 0x2c($sp)
/* 07D10C 8007C50C 8FB00014 */  lw    $s0, 0x14($sp)
/* 07D110 8007C510 8FB10018 */  lw    $s1, 0x18($sp)
/* 07D114 8007C514 8FB2001C */  lw    $s2, 0x1c($sp)
/* 07D118 8007C518 8FB30020 */  lw    $s3, 0x20($sp)
/* 07D11C 8007C51C 8FB40024 */  lw    $s4, 0x24($sp)
/* 07D120 8007C520 8FB50028 */  lw    $s5, 0x28($sp)
/* 07D124 8007C524 03E00008 */  jr    $ra
/* 07D128 8007C528 27BD0050 */   addiu $sp, $sp, 0x50

