.rdata
glabel D_800E5E38
.asciz "ERROR!! TrackMem overflow .. %d\n"
.ascii "\0\0\0" # padding

.text
glabel func_8002C0C4
/* 02CCC4 8002C0C4 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 02CCC8 8002C0C8 AFB2001C */  sw    $s2, 0x1c($sp)
/* 02CCCC 8002C0CC 00809025 */  move  $s2, $a0
/* 02CCD0 8002C0D0 AFBF002C */  sw    $ra, 0x2c($sp)
/* 02CCD4 8002C0D4 3C0400FF */  lui   $a0, (0x00FF00FF >> 16) # lui $a0, 0xff
/* 02CCD8 8002C0D8 AFB50028 */  sw    $s5, 0x28($sp)
/* 02CCDC 8002C0DC AFB40024 */  sw    $s4, 0x24($sp)
/* 02CCE0 8002C0E0 AFB30020 */  sw    $s3, 0x20($sp)
/* 02CCE4 8002C0E4 AFB10018 */  sw    $s1, 0x18($sp)
/* 02CCE8 8002C0E8 AFB00014 */  sw    $s0, 0x14($sp)
/* 02CCEC 8002C0EC 0C01ECDD */  jal   set_texture_colour_tag
/* 02CCF0 8002C0F0 348400FF */   ori   $a0, (0x00FF00FF & 0xFFFF) # ori $a0, $a0, 0xff
/* 02CCF4 8002C0F4 3C150008 */  lui   $s5, (0x00082A00 >> 16) # lui $s5, 8
/* 02CCF8 8002C0F8 36B52A00 */  ori   $s5, (0x00082A00 & 0xFFFF) # ori $s5, $s5, 0x2a00
/* 02CCFC 8002C0FC 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 02CD00 8002C100 34A500FF */  ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 02CD04 8002C104 0C01C327 */  jal   allocate_from_main_pool_safe
/* 02CD08 8002C108 02A02025 */   move  $a0, $s5
/* 02CD0C 8002C10C 3C038012 */  lui   $v1, %hi(D_8011D30C) # $v1, 0x8012
/* 02CD10 8002C110 3C11800E */  lui   $s1, %hi(gCurrentLevelModel) # $s1, 0x800e
/* 02CD14 8002C114 2631C918 */  addiu $s1, %lo(gCurrentLevelModel) # addiu $s1, $s1, -0x36e8
/* 02CD18 8002C118 2463D30C */  addiu $v1, %lo(D_8011D30C) # addiu $v1, $v1, -0x2cf4
/* 02CD1C 8002C11C 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 02CD20 8002C120 AC620000 */  sw    $v0, ($v1)
/* 02CD24 8002C124 AE220000 */  sw    $v0, ($s1)
/* 02CD28 8002C128 34A500FF */  ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 02CD2C 8002C12C 0C01C327 */  jal   allocate_from_main_pool_safe
/* 02CD30 8002C130 240407D0 */   li    $a0, 2000
/* 02CD34 8002C134 3C018012 */  lui   $at, %hi(D_8011D370) # $at, 0x8012
/* 02CD38 8002C138 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 02CD3C 8002C13C AC22D370 */  sw    $v0, %lo(D_8011D370)($at)
/* 02CD40 8002C140 34A500FF */  ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 02CD44 8002C144 0C01C327 */  jal   allocate_from_main_pool_safe
/* 02CD48 8002C148 240401F4 */   li    $a0, 500
/* 02CD4C 8002C14C 3C018012 */  lui   $at, %hi(D_8011D374) # $at, 0x8012
/* 02CD50 8002C150 AC22D374 */  sw    $v0, %lo(D_8011D374)($at)
/* 02CD54 8002C154 3C018012 */  lui   $at, %hi(D_8011D378) # $at, 0x8012
/* 02CD58 8002C158 AC20D378 */  sw    $zero, %lo(D_8011D378)($at)
/* 02CD5C 8002C15C 0C01DB16 */  jal   load_asset_section_from_rom
/* 02CD60 8002C160 2404001A */   li    $a0, 26
/* 02CD64 8002C164 3C148012 */  lui   $s4, %hi(D_8011D310) # $s4, 0x8012
/* 02CD68 8002C168 2694D310 */  addiu $s4, %lo(D_8011D310) # addiu $s4, $s4, -0x2cf0
/* 02CD6C 8002C16C AE820000 */  sw    $v0, ($s4)
/* 02CD70 8002C170 8C4F0000 */  lw    $t7, ($v0)
/* 02CD74 8002C174 2403FFFF */  li    $v1, -1
/* 02CD78 8002C178 00006025 */  move  $t4, $zero
/* 02CD7C 8002C17C 106F0005 */  beq   $v1, $t7, .L8002C194
/* 02CD80 8002C180 00404025 */   move  $t0, $v0
.L8002C184:
/* 02CD84 8002C184 8C580004 */  lw    $t8, 4($v0)
/* 02CD88 8002C188 258C0001 */  addiu $t4, $t4, 1
/* 02CD8C 8002C18C 1478FFFD */  bne   $v1, $t8, .L8002C184
/* 02CD90 8002C190 24420004 */   addiu $v0, $v0, 4
.L8002C194:
/* 02CD94 8002C194 258CFFFF */  addiu $t4, $t4, -1
/* 02CD98 8002C198 024C082A */  slt   $at, $s2, $t4
/* 02CD9C 8002C19C 14200002 */  bnez  $at, .L8002C1A8
/* 02CDA0 8002C1A0 2404001B */   li    $a0, 27
/* 02CDA4 8002C1A4 00009025 */  move  $s2, $zero
.L8002C1A8:
/* 02CDA8 8002C1A8 0012C880 */  sll   $t9, $s2, 2
/* 02CDAC 8002C1AC 01191021 */  addu  $v0, $t0, $t9
/* 02CDB0 8002C1B0 8C460000 */  lw    $a2, ($v0)
/* 02CDB4 8002C1B4 8C4D0004 */  lw    $t5, 4($v0)
/* 02CDB8 8002C1B8 8E300000 */  lw    $s0, ($s1)
/* 02CDBC 8002C1BC 01A69823 */  subu  $s3, $t5, $a2
/* 02CDC0 8002C1C0 02157021 */  addu  $t6, $s0, $s5
/* 02CDC4 8002C1C4 01D38023 */  subu  $s0, $t6, $s3
/* 02CDC8 8002C1C8 06010004 */  bgez  $s0, .L8002C1DC
/* 02CDCC 8002C1CC 320F000F */   andi  $t7, $s0, 0xf
/* 02CDD0 8002C1D0 11E00002 */  beqz  $t7, .L8002C1DC
/* 02CDD4 8002C1D4 00000000 */   nop   
/* 02CDD8 8002C1D8 25EFFFF0 */  addiu $t7, $t7, -0x10
.L8002C1DC:
/* 02CDDC 8002C1DC 020F8023 */  subu  $s0, $s0, $t7
/* 02CDE0 8002C1E0 02002825 */  move  $a1, $s0
/* 02CDE4 8002C1E4 0C01DB9A */  jal   load_asset_to_address
/* 02CDE8 8002C1E8 02603825 */   move  $a3, $s3
/* 02CDEC 8002C1EC 8E250000 */  lw    $a1, ($s1)
/* 02CDF0 8002C1F0 0C031886 */  jal   gzip_inflate
/* 02CDF4 8002C1F4 02002025 */   move  $a0, $s0
/* 02CDF8 8002C1F8 8E840000 */  lw    $a0, ($s4)
/* 02CDFC 8002C1FC 0C01C450 */  jal   free_from_memory_pool
/* 02CE00 8002C200 00000000 */   nop   
/* 02CE04 8002C204 8E320000 */  lw    $s2, ($s1)
/* 02CE08 8002C208 00008025 */  move  $s0, $zero
/* 02CE0C 8002C20C 8E580000 */  lw    $t8, ($s2)
/* 02CE10 8002C210 02403025 */  move  $a2, $s2
/* 02CE14 8002C214 0312C821 */  addu  $t9, $t8, $s2
/* 02CE18 8002C218 AE590000 */  sw    $t9, ($s2)
/* 02CE1C 8002C21C 8E320000 */  lw    $s2, ($s1)
/* 02CE20 8002C220 00000000 */  nop   
/* 02CE24 8002C224 8E4D0004 */  lw    $t5, 4($s2)
/* 02CE28 8002C228 00000000 */  nop   
/* 02CE2C 8002C22C 01A67021 */  addu  $t6, $t5, $a2
/* 02CE30 8002C230 AE4E0004 */  sw    $t6, 4($s2)
/* 02CE34 8002C234 8E320000 */  lw    $s2, ($s1)
/* 02CE38 8002C238 00000000 */  nop   
/* 02CE3C 8002C23C 8E4F0008 */  lw    $t7, 8($s2)
/* 02CE40 8002C240 00000000 */  nop   
/* 02CE44 8002C244 01E6C021 */  addu  $t8, $t7, $a2
/* 02CE48 8002C248 AE580008 */  sw    $t8, 8($s2)
/* 02CE4C 8002C24C 8E320000 */  lw    $s2, ($s1)
/* 02CE50 8002C250 00000000 */  nop   
/* 02CE54 8002C254 8E59000C */  lw    $t9, 0xc($s2)
/* 02CE58 8002C258 00000000 */  nop   
/* 02CE5C 8002C25C 03266821 */  addu  $t5, $t9, $a2
/* 02CE60 8002C260 AE4D000C */  sw    $t5, 0xc($s2)
/* 02CE64 8002C264 8E320000 */  lw    $s2, ($s1)
/* 02CE68 8002C268 00000000 */  nop   
/* 02CE6C 8002C26C 8E4E0010 */  lw    $t6, 0x10($s2)
/* 02CE70 8002C270 00000000 */  nop   
/* 02CE74 8002C274 01C67821 */  addu  $t7, $t6, $a2
/* 02CE78 8002C278 AE4F0010 */  sw    $t7, 0x10($s2)
/* 02CE7C 8002C27C 8E320000 */  lw    $s2, ($s1)
/* 02CE80 8002C280 00000000 */  nop   
/* 02CE84 8002C284 8E580014 */  lw    $t8, 0x14($s2)
/* 02CE88 8002C288 00000000 */  nop   
/* 02CE8C 8002C28C 0306C821 */  addu  $t9, $t8, $a2
/* 02CE90 8002C290 AE590014 */  sw    $t9, 0x14($s2)
/* 02CE94 8002C294 8E320000 */  lw    $s2, ($s1)
/* 02CE98 8002C298 00000000 */  nop   
/* 02CE9C 8002C29C 8643001A */  lh    $v1, 0x1a($s2)
/* 02CEA0 8002C2A0 00000000 */  nop   
/* 02CEA4 8002C2A4 1860002B */  blez  $v1, .L8002C354
/* 02CEA8 8002C2A8 00009825 */   move  $s3, $zero
.L8002C2AC:
/* 02CEAC 8002C2AC 8E4D0004 */  lw    $t5, 4($s2)
/* 02CEB0 8002C2B0 26100001 */  addiu $s0, $s0, 1
/* 02CEB4 8002C2B4 01B31021 */  addu  $v0, $t5, $s3
/* 02CEB8 8002C2B8 8C4E0000 */  lw    $t6, ($v0)
/* 02CEBC 8002C2BC 00000000 */  nop   
/* 02CEC0 8002C2C0 01C67821 */  addu  $t7, $t6, $a2
/* 02CEC4 8002C2C4 AC4F0000 */  sw    $t7, ($v0)
/* 02CEC8 8002C2C8 8E380000 */  lw    $t8, ($s1)
/* 02CECC 8002C2CC 00000000 */  nop   
/* 02CED0 8002C2D0 8F190004 */  lw    $t9, 4($t8)
/* 02CED4 8002C2D4 00000000 */  nop   
/* 02CED8 8002C2D8 03331021 */  addu  $v0, $t9, $s3
/* 02CEDC 8002C2DC 8C4D0004 */  lw    $t5, 4($v0)
/* 02CEE0 8002C2E0 00000000 */  nop   
/* 02CEE4 8002C2E4 01A67021 */  addu  $t6, $t5, $a2
/* 02CEE8 8002C2E8 AC4E0004 */  sw    $t6, 4($v0)
/* 02CEEC 8002C2EC 8E2F0000 */  lw    $t7, ($s1)
/* 02CEF0 8002C2F0 00000000 */  nop   
/* 02CEF4 8002C2F4 8DF80004 */  lw    $t8, 4($t7)
/* 02CEF8 8002C2F8 00000000 */  nop   
/* 02CEFC 8002C2FC 03131021 */  addu  $v0, $t8, $s3
/* 02CF00 8002C300 8C59000C */  lw    $t9, 0xc($v0)
/* 02CF04 8002C304 00000000 */  nop   
/* 02CF08 8002C308 03266821 */  addu  $t5, $t9, $a2
/* 02CF0C 8002C30C AC4D000C */  sw    $t5, 0xc($v0)
/* 02CF10 8002C310 8E2E0000 */  lw    $t6, ($s1)
/* 02CF14 8002C314 00000000 */  nop   
/* 02CF18 8002C318 8DCF0004 */  lw    $t7, 4($t6)
/* 02CF1C 8002C31C 00000000 */  nop   
/* 02CF20 8002C320 01F31021 */  addu  $v0, $t7, $s3
/* 02CF24 8002C324 8C580014 */  lw    $t8, 0x14($v0)
/* 02CF28 8002C328 26730044 */  addiu $s3, $s3, 0x44
/* 02CF2C 8002C32C 0306C821 */  addu  $t9, $t8, $a2
/* 02CF30 8002C330 AC590014 */  sw    $t9, 0x14($v0)
/* 02CF34 8002C334 8E320000 */  lw    $s2, ($s1)
/* 02CF38 8002C338 00000000 */  nop   
/* 02CF3C 8002C33C 8643001A */  lh    $v1, 0x1a($s2)
/* 02CF40 8002C340 00000000 */  nop   
/* 02CF44 8002C344 0203082A */  slt   $at, $s0, $v1
/* 02CF48 8002C348 1420FFD8 */  bnez  $at, .L8002C2AC
/* 02CF4C 8002C34C 00000000 */   nop   
/* 02CF50 8002C350 00008025 */  move  $s0, $zero
.L8002C354:
/* 02CF54 8002C354 864D0018 */  lh    $t5, 0x18($s2)
/* 02CF58 8002C358 00009825 */  move  $s3, $zero
/* 02CF5C 8002C35C 19A00018 */  blez  $t5, .L8002C3C0
/* 02CF60 8002C360 00000000 */   nop   
.L8002C364:
/* 02CF64 8002C364 8E4E0000 */  lw    $t6, ($s2)
/* 02CF68 8002C368 00000000 */  nop   
/* 02CF6C 8002C36C 01D37821 */  addu  $t7, $t6, $s3
/* 02CF70 8002C370 8DE40000 */  lw    $a0, ($t7)
/* 02CF74 8002C374 00000000 */  nop   
/* 02CF78 8002C378 34988000 */  ori   $t8, $a0, 0x8000
/* 02CF7C 8002C37C 0C01EB9D */  jal   load_texture
/* 02CF80 8002C380 03002025 */   move  $a0, $t8
/* 02CF84 8002C384 8E390000 */  lw    $t9, ($s1)
/* 02CF88 8002C388 26100001 */  addiu $s0, $s0, 1
/* 02CF8C 8002C38C 8F2D0000 */  lw    $t5, ($t9)
/* 02CF90 8002C390 00000000 */  nop   
/* 02CF94 8002C394 01B37021 */  addu  $t6, $t5, $s3
/* 02CF98 8002C398 ADC20000 */  sw    $v0, ($t6)
/* 02CF9C 8002C39C 8E320000 */  lw    $s2, ($s1)
/* 02CFA0 8002C3A0 26730008 */  addiu $s3, $s3, 8
/* 02CFA4 8002C3A4 864F0018 */  lh    $t7, 0x18($s2)
/* 02CFA8 8002C3A8 00000000 */  nop   
/* 02CFAC 8002C3AC 020F082A */  slt   $at, $s0, $t7
/* 02CFB0 8002C3B0 1420FFEC */  bnez  $at, .L8002C364
/* 02CFB4 8002C3B4 00000000 */   nop   
/* 02CFB8 8002C3B8 8643001A */  lh    $v1, 0x1a($s2)
/* 02CFBC 8002C3BC 00008025 */  move  $s0, $zero
.L8002C3C0:
/* 02CFC0 8002C3C0 8E580048 */  lw    $t8, 0x48($s2)
/* 02CFC4 8002C3C4 02401025 */  move  $v0, $s2
/* 02CFC8 8002C3C8 18600048 */  blez  $v1, .L8002C4EC
/* 02CFCC 8002C3CC 0258A021 */   addu  $s4, $s2, $t8
/* 02CFD0 8002C3D0 00009825 */  move  $s3, $zero
/* 02CFD4 8002C3D4 0000A825 */  move  $s5, $zero
.L8002C3D8:
/* 02CFD8 8002C3D8 8E590004 */  lw    $t9, 4($s2)
/* 02CFDC 8002C3DC 00000000 */  nop   
/* 02CFE0 8002C3E0 03336821 */  addu  $t5, $t9, $s3
/* 02CFE4 8002C3E4 ADB40010 */  sw    $s4, 0x10($t5)
/* 02CFE8 8002C3E8 8E2E0000 */  lw    $t6, ($s1)
/* 02CFEC 8002C3EC 00000000 */  nop   
/* 02CFF0 8002C3F0 8DCF0004 */  lw    $t7, 4($t6)
/* 02CFF4 8002C3F4 00000000 */  nop   
/* 02CFF8 8002C3F8 01F3C021 */  addu  $t8, $t7, $s3
/* 02CFFC 8002C3FC 8719001E */  lh    $t9, 0x1e($t8)
/* 02D000 8002C400 00000000 */  nop   
/* 02D004 8002C404 00196840 */  sll   $t5, $t9, 1
/* 02D008 8002C408 0C01C614 */  jal   align16
/* 02D00C 8002C40C 01B42021 */   addu  $a0, $t5, $s4
/* 02D010 8002C410 8E2E0000 */  lw    $t6, ($s1)
/* 02D014 8002C414 0040A025 */  move  $s4, $v0
/* 02D018 8002C418 8DCF0004 */  lw    $t7, 4($t6)
/* 02D01C 8002C41C 00000000 */  nop   
/* 02D020 8002C420 01F3C021 */  addu  $t8, $t7, $s3
/* 02D024 8002C424 AF020018 */  sw    $v0, 0x18($t8)
/* 02D028 8002C428 8E390000 */  lw    $t9, ($s1)
/* 02D02C 8002C42C 00000000 */  nop   
/* 02D030 8002C430 8F2D0004 */  lw    $t5, 4($t9)
/* 02D034 8002C434 0C00B30C */  jal   func_8002CC30
/* 02D038 8002C438 01B32021 */   addu  $a0, $t5, $s3
/* 02D03C 8002C43C 8E320000 */  lw    $s2, ($s1)
/* 02D040 8002C440 0054A021 */  addu  $s4, $v0, $s4
/* 02D044 8002C444 8E4E0004 */  lw    $t6, 4($s2)
/* 02D048 8002C448 8E4F0008 */  lw    $t7, 8($s2)
/* 02D04C 8002C44C 02003025 */  move  $a2, $s0
/* 02D050 8002C450 01D32021 */  addu  $a0, $t6, $s3
/* 02D054 8002C454 0C00B255 */  jal   func_8002C954
/* 02D058 8002C458 01F52821 */   addu  $a1, $t7, $s5
/* 02D05C 8002C45C 8E380000 */  lw    $t8, ($s1)
/* 02D060 8002C460 00000000 */  nop   
/* 02D064 8002C464 8F190004 */  lw    $t9, 4($t8)
/* 02D068 8002C468 00000000 */  nop   
/* 02D06C 8002C46C 03336821 */  addu  $t5, $t9, $s3
/* 02D070 8002C470 A5A00030 */  sh    $zero, 0x30($t5)
/* 02D074 8002C474 8E2E0000 */  lw    $t6, ($s1)
/* 02D078 8002C478 00000000 */  nop   
/* 02D07C 8002C47C 8DCF0004 */  lw    $t7, 4($t6)
/* 02D080 8002C480 00000000 */  nop   
/* 02D084 8002C484 01F3C021 */  addu  $t8, $t7, $s3
/* 02D088 8002C488 AF140034 */  sw    $s4, 0x34($t8)
/* 02D08C 8002C48C 8E390000 */  lw    $t9, ($s1)
/* 02D090 8002C490 00000000 */  nop   
/* 02D094 8002C494 8F2D0004 */  lw    $t5, 4($t9)
/* 02D098 8002C498 0C00B1C7 */  jal   func_8002C71C
/* 02D09C 8002C49C 01B32021 */   addu  $a0, $t5, $s3
/* 02D0A0 8002C4A0 8E2E0000 */  lw    $t6, ($s1)
/* 02D0A4 8002C4A4 00000000 */  nop   
/* 02D0A8 8002C4A8 8DCF0004 */  lw    $t7, 4($t6)
/* 02D0AC 8002C4AC 00000000 */  nop   
/* 02D0B0 8002C4B0 01F3C021 */  addu  $t8, $t7, $s3
/* 02D0B4 8002C4B4 87190032 */  lh    $t9, 0x32($t8)
/* 02D0B8 8002C4B8 00000000 */  nop   
/* 02D0BC 8002C4BC 00196840 */  sll   $t5, $t9, 1
/* 02D0C0 8002C4C0 0C01C614 */  jal   align16
/* 02D0C4 8002C4C4 01B42021 */   addu  $a0, $t5, $s4
/* 02D0C8 8002C4C8 8E320000 */  lw    $s2, ($s1)
/* 02D0CC 8002C4CC 26100001 */  addiu $s0, $s0, 1
/* 02D0D0 8002C4D0 864E001A */  lh    $t6, 0x1a($s2)
/* 02D0D4 8002C4D4 26730044 */  addiu $s3, $s3, 0x44
/* 02D0D8 8002C4D8 020E082A */  slt   $at, $s0, $t6
/* 02D0DC 8002C4DC 26B5000C */  addiu $s5, $s5, 0xc
/* 02D0E0 8002C4E0 1420FFBD */  bnez  $at, .L8002C3D8
/* 02D0E4 8002C4E4 0040A025 */   move  $s4, $v0
/* 02D0E8 8002C4E8 02401025 */  move  $v0, $s2
.L8002C4EC:
/* 02D0EC 8002C4EC 3C010008 */  lui   $at, (0x00082A01 >> 16) # lui $at, 8
/* 02D0F0 8002C4F0 02829823 */  subu  $s3, $s4, $v0
/* 02D0F4 8002C4F4 34212A01 */  ori   $at, (0x00082A01 & 0xFFFF) # ori $at, $at, 0x2a01
/* 02D0F8 8002C4F8 0261082A */  slt   $at, $s3, $at
/* 02D0FC 8002C4FC 14200004 */  bnez  $at, .L8002C510
/* 02D100 8002C500 3C04800E */   lui   $a0, %hi(D_800E5E38) # $a0, 0x800e
/* 02D104 8002C504 24845E38 */  addiu $a0, %lo(D_800E5E38) # addiu $a0, $a0, 0x5e38
/* 02D108 8002C508 0C032755 */  jal   rmonPrintf
/* 02D10C 8002C50C 02602825 */   move  $a1, $s3
.L8002C510:
/* 02D110 8002C510 0C01C42C */  jal   set_free_queue_state
/* 02D114 8002C514 00002025 */   move  $a0, $zero
/* 02D118 8002C518 3C048012 */  lui   $a0, %hi(D_8011D30C) # $a0, 0x8012
/* 02D11C 8002C51C 8C84D30C */  lw    $a0, %lo(D_8011D30C)($a0)
/* 02D120 8002C520 0C01C450 */  jal   free_from_memory_pool
/* 02D124 8002C524 00000000 */   nop   
/* 02D128 8002C528 3C058012 */  lui   $a1, %hi(D_8011D30C) # $a1, 0x8012
/* 02D12C 8002C52C 8CA5D30C */  lw    $a1, %lo(D_8011D30C)($a1)
/* 02D130 8002C530 3C06FFFF */  lui   $a2, (0xFFFF00FF >> 16) # lui $a2, 0xffff
/* 02D134 8002C534 34C600FF */  ori   $a2, (0xFFFF00FF & 0xFFFF) # ori $a2, $a2, 0xff
/* 02D138 8002C538 0C01C3BE */  jal   allocate_at_address_in_main_pool
/* 02D13C 8002C53C 02602025 */   move  $a0, $s3
/* 02D140 8002C540 0C01C42C */  jal   set_free_queue_state
/* 02D144 8002C544 24040002 */   li    $a0, 2
/* 02D148 8002C548 8E240000 */  lw    $a0, ($s1)
/* 02D14C 8002C54C 0C02A0ED */  jal   minimap_init
/* 02D150 8002C550 00000000 */   nop   
/* 02D154 8002C554 8E320000 */  lw    $s2, ($s1)
/* 02D158 8002C558 00006025 */  move  $t4, $zero
/* 02D15C 8002C55C 8643001A */  lh    $v1, 0x1a($s2)
/* 02D160 8002C560 00002825 */  move  $a1, $zero
/* 02D164 8002C564 18600061 */  blez  $v1, .L8002C6EC
/* 02D168 8002C568 3C0B0800 */   lui   $t3, 0x800
/* 02D16C 8002C56C 8E460004 */  lw    $a2, 4($s2)
/* 02D170 8002C570 240A0001 */  li    $t2, 1
/* 02D174 8002C574 24070080 */  li    $a3, 128
.L8002C578:
/* 02D178 8002C578 84C20020 */  lh    $v0, 0x20($a2)
/* 02D17C 8002C57C 258C0001 */  addiu $t4, $t4, 1
/* 02D180 8002C580 18400056 */  blez  $v0, .L8002C6DC
/* 02D184 8002C584 00009825 */   move  $s3, $zero
/* 02D188 8002C588 8CC4000C */  lw    $a0, 0xc($a2)
/* 02D18C 8002C58C 00004025 */  move  $t0, $zero
.L8002C590:
/* 02D190 8002C590 84900002 */  lh    $s0, 2($a0)
/* 02D194 8002C594 8489000E */  lh    $t1, 0xe($a0)
/* 02D198 8002C598 26730001 */  addiu $s3, $s3, 1
/* 02D19C 8002C59C 0209082A */  slt   $at, $s0, $t1
/* 02D1A0 8002C5A0 10200049 */  beqz  $at, .L8002C6C8
/* 02D1A4 8002C5A4 0262082A */   slt   $at, $s3, $v0
/* 02D1A8 8002C5A8 00101080 */  sll   $v0, $s0, 2
/* 02D1AC 8002C5AC 00501021 */  addu  $v0, $v0, $s0
/* 02D1B0 8002C5B0 00021040 */  sll   $v0, $v0, 1
.L8002C5B4:
/* 02D1B4 8002C5B4 8CCF0000 */  lw    $t7, ($a2)
/* 02D1B8 8002C5B8 26100001 */  addiu $s0, $s0, 1
/* 02D1BC 8002C5BC 01E21821 */  addu  $v1, $t7, $v0
/* 02D1C0 8002C5C0 90780006 */  lbu   $t8, 6($v1)
/* 02D1C4 8002C5C4 00000000 */  nop   
/* 02D1C8 8002C5C8 1558003A */  bne   $t2, $t8, .L8002C6B4
/* 02D1CC 8002C5CC 0209082A */   slt   $at, $s0, $t1
/* 02D1D0 8002C5D0 90790007 */  lbu   $t9, 7($v1)
/* 02D1D4 8002C5D4 00000000 */  nop   
/* 02D1D8 8002C5D8 15590036 */  bne   $t2, $t9, .L8002C6B4
/* 02D1DC 8002C5DC 0209082A */   slt   $at, $s0, $t1
/* 02D1E0 8002C5E0 906D0008 */  lbu   $t5, 8($v1)
/* 02D1E4 8002C5E4 00000000 */  nop   
/* 02D1E8 8002C5E8 A06D0009 */  sb    $t5, 9($v1)
/* 02D1EC 8002C5EC 8E2E0000 */  lw    $t6, ($s1)
/* 02D1F0 8002C5F0 00000000 */  nop   
/* 02D1F4 8002C5F4 8DCF0004 */  lw    $t7, 4($t6)
/* 02D1F8 8002C5F8 00000000 */  nop   
/* 02D1FC 8002C5FC 01E5C021 */  addu  $t8, $t7, $a1
/* 02D200 8002C600 8F190000 */  lw    $t9, ($t8)
/* 02D204 8002C604 00000000 */  nop   
/* 02D208 8002C608 03226821 */  addu  $t5, $t9, $v0
/* 02D20C 8002C60C A1A70006 */  sb    $a3, 6($t5)
/* 02D210 8002C610 8E2E0000 */  lw    $t6, ($s1)
/* 02D214 8002C614 00000000 */  nop   
/* 02D218 8002C618 8DCF0004 */  lw    $t7, 4($t6)
/* 02D21C 8002C61C 00000000 */  nop   
/* 02D220 8002C620 01E5C021 */  addu  $t8, $t7, $a1
/* 02D224 8002C624 8F190000 */  lw    $t9, ($t8)
/* 02D228 8002C628 00000000 */  nop   
/* 02D22C 8002C62C 03226821 */  addu  $t5, $t9, $v0
/* 02D230 8002C630 A1A70007 */  sb    $a3, 7($t5)
/* 02D234 8002C634 8E2E0000 */  lw    $t6, ($s1)
/* 02D238 8002C638 00000000 */  nop   
/* 02D23C 8002C63C 8DCF0004 */  lw    $t7, 4($t6)
/* 02D240 8002C640 00000000 */  nop   
/* 02D244 8002C644 01E5C021 */  addu  $t8, $t7, $a1
/* 02D248 8002C648 8F190000 */  lw    $t9, ($t8)
/* 02D24C 8002C64C 00000000 */  nop   
/* 02D250 8002C650 03226821 */  addu  $t5, $t9, $v0
/* 02D254 8002C654 A1A70008 */  sb    $a3, 8($t5)
/* 02D258 8002C658 8E2E0000 */  lw    $t6, ($s1)
/* 02D25C 8002C65C 00000000 */  nop   
/* 02D260 8002C660 8DCF0004 */  lw    $t7, 4($t6)
/* 02D264 8002C664 00000000 */  nop   
/* 02D268 8002C668 01E5C021 */  addu  $t8, $t7, $a1
/* 02D26C 8002C66C 8F19000C */  lw    $t9, 0xc($t8)
/* 02D270 8002C670 00000000 */  nop   
/* 02D274 8002C674 03282021 */  addu  $a0, $t9, $t0
/* 02D278 8002C678 8C8D0008 */  lw    $t5, 8($a0)
/* 02D27C 8002C67C 00000000 */  nop   
/* 02D280 8002C680 01AB7025 */  or    $t6, $t5, $t3
/* 02D284 8002C684 AC8E0008 */  sw    $t6, 8($a0)
/* 02D288 8002C688 8E320000 */  lw    $s2, ($s1)
/* 02D28C 8002C68C 00000000 */  nop   
/* 02D290 8002C690 8E4F0004 */  lw    $t7, 4($s2)
/* 02D294 8002C694 00000000 */  nop   
/* 02D298 8002C698 01E53021 */  addu  $a2, $t7, $a1
/* 02D29C 8002C69C 8CD8000C */  lw    $t8, 0xc($a2)
/* 02D2A0 8002C6A0 00000000 */  nop   
/* 02D2A4 8002C6A4 03082021 */  addu  $a0, $t8, $t0
/* 02D2A8 8002C6A8 8489000E */  lh    $t1, 0xe($a0)
/* 02D2AC 8002C6AC 00000000 */  nop   
/* 02D2B0 8002C6B0 0209082A */  slt   $at, $s0, $t1
.L8002C6B4:
/* 02D2B4 8002C6B4 1420FFBF */  bnez  $at, .L8002C5B4
/* 02D2B8 8002C6B8 2442000A */   addiu $v0, $v0, 0xa
/* 02D2BC 8002C6BC 84C20020 */  lh    $v0, 0x20($a2)
/* 02D2C0 8002C6C0 00000000 */  nop   
/* 02D2C4 8002C6C4 0262082A */  slt   $at, $s3, $v0
.L8002C6C8:
/* 02D2C8 8002C6C8 2508000C */  addiu $t0, $t0, 0xc
/* 02D2CC 8002C6CC 1420FFB0 */  bnez  $at, .L8002C590
/* 02D2D0 8002C6D0 2484000C */   addiu $a0, $a0, 0xc
/* 02D2D4 8002C6D4 8643001A */  lh    $v1, 0x1a($s2)
/* 02D2D8 8002C6D8 00000000 */  nop   
.L8002C6DC:
/* 02D2DC 8002C6DC 0183082A */  slt   $at, $t4, $v1
/* 02D2E0 8002C6E0 24A50044 */  addiu $a1, $a1, 0x44
/* 02D2E4 8002C6E4 1420FFA4 */  bnez  $at, .L8002C578
/* 02D2E8 8002C6E8 24C60044 */   addiu $a2, $a2, 0x44
.L8002C6EC:
/* 02D2EC 8002C6EC 3C04FF00 */  lui   $a0, (0xFF00FFFF >> 16) # lui $a0, 0xff00
/* 02D2F0 8002C6F0 0C01ECDD */  jal   set_texture_colour_tag
/* 02D2F4 8002C6F4 3484FFFF */   ori   $a0, (0xFF00FFFF & 0xFFFF) # ori $a0, $a0, 0xffff
/* 02D2F8 8002C6F8 8FBF002C */  lw    $ra, 0x2c($sp)
/* 02D2FC 8002C6FC 8FB00014 */  lw    $s0, 0x14($sp)
/* 02D300 8002C700 8FB10018 */  lw    $s1, 0x18($sp)
/* 02D304 8002C704 8FB2001C */  lw    $s2, 0x1c($sp)
/* 02D308 8002C708 8FB30020 */  lw    $s3, 0x20($sp)
/* 02D30C 8002C70C 8FB40024 */  lw    $s4, 0x24($sp)
/* 02D310 8002C710 8FB50028 */  lw    $s5, 0x28($sp)
/* 02D314 8002C714 03E00008 */  jr    $ra
/* 02D318 8002C718 27BD0030 */   addiu $sp, $sp, 0x30

