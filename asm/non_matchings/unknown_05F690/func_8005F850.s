glabel func_8005F850
/* 060450 8005F850 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 060454 8005F854 AFBF0014 */  sw    $ra, 0x14($sp)
/* 060458 8005F858 3C0500FF */  lui   $a1, (0x00FF00FF >> 16) # lui $a1, 0xff
/* 06045C 8005F85C 34A500FF */  ori   $a1, (0x00FF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 060460 8005F860 0C01C327 */  jal   allocate_from_main_pool_safe
/* 060464 8005F864 24040230 */   li    $a0, 560
/* 060468 8005F868 3C018012 */  lui   $at, %hi(D_8011D624) # $at, 0x8012
/* 06046C 8005F86C 3C0500FF */  lui   $a1, (0x00FF00FF >> 16) # lui $a1, 0xff
/* 060470 8005F870 AC22D624 */  sw    $v0, %lo(D_8011D624)($at)
/* 060474 8005F874 34A500FF */  ori   $a1, (0x00FF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 060478 8005F878 0C01C327 */  jal   allocate_from_main_pool_safe
/* 06047C 8005F87C 24040190 */   li    $a0, 400
/* 060480 8005F880 3C018012 */  lui   $at, %hi(D_8011D628) # $at, 0x8012
/* 060484 8005F884 AC22D628 */  sw    $v0, %lo(D_8011D628)($at)
/* 060488 8005F888 3C018012 */  lui   $at, %hi(D_8011D62C) # $at, 0x8012
/* 06048C 8005F88C AC20D62C */  sw    $zero, %lo(D_8011D62C)($at)
/* 060490 8005F890 3C018012 */  lui   $at, %hi(D_8011D634) # $at, 0x8012
/* 060494 8005F894 AC20D634 */  sw    $zero, %lo(D_8011D634)($at)
/* 060498 8005F898 0C01DB16 */  jal   load_asset_section_from_rom
/* 06049C 8005F89C 2404001C */   li    $a0, 28
/* 0604A0 8005F8A0 3C058012 */  lui   $a1, %hi(D_8011D630) # $a1, 0x8012
/* 0604A4 8005F8A4 3C078012 */  lui   $a3, %hi(D_8011D620) # $a3, 0x8012
/* 0604A8 8005F8A8 24E7D620 */  addiu $a3, %lo(D_8011D620) # addiu $a3, $a3, -0x29e0
/* 0604AC 8005F8AC 24A5D630 */  addiu $a1, %lo(D_8011D630) # addiu $a1, $a1, -0x29d0
/* 0604B0 8005F8B0 00007080 */  sll   $t6, $zero, 2
/* 0604B4 8005F8B4 ACE20000 */  sw    $v0, ($a3)
/* 0604B8 8005F8B8 ACA00000 */  sw    $zero, ($a1)
/* 0604BC 8005F8BC 004E7821 */  addu  $t7, $v0, $t6
/* 0604C0 8005F8C0 8DF80000 */  lw    $t8, ($t7)
/* 0604C4 8005F8C4 2406FFFF */  li    $a2, -1
/* 0604C8 8005F8C8 00402025 */  move  $a0, $v0
/* 0604CC 8005F8CC 10D80009 */  beq   $a2, $t8, .L8005F8F4
/* 0604D0 8005F8D0 00001825 */   move  $v1, $zero
/* 0604D4 8005F8D4 24790001 */  addiu $t9, $v1, 1
.L8005F8D8:
/* 0604D8 8005F8D8 00194080 */  sll   $t0, $t9, 2
/* 0604DC 8005F8DC 00884821 */  addu  $t1, $a0, $t0
/* 0604E0 8005F8E0 ACB90000 */  sw    $t9, ($a1)
/* 0604E4 8005F8E4 8D2A0000 */  lw    $t2, ($t1)
/* 0604E8 8005F8E8 03201825 */  move  $v1, $t9
/* 0604EC 8005F8EC 14CAFFFA */  bne   $a2, $t2, .L8005F8D8
/* 0604F0 8005F8F0 24790001 */   addiu $t9, $v1, 1
.L8005F8F4:
/* 0604F4 8005F8F4 246BFFFF */  addiu $t3, $v1, -1
/* 0604F8 8005F8F8 ACAB0000 */  sw    $t3, ($a1)
/* 0604FC 8005F8FC 0C01DB16 */  jal   load_asset_section_from_rom
/* 060500 8005F900 2404001E */   li    $a0, 30
/* 060504 8005F904 3C018012 */  lui   $at, %hi(D_8011D638) # $at, 0x8012
/* 060508 8005F908 AC22D638 */  sw    $v0, %lo(D_8011D638)($at)
/* 06050C 8005F90C 0C01DB16 */  jal   load_asset_section_from_rom
/* 060510 8005F910 2404001F */   li    $a0, 31
/* 060514 8005F914 3C018012 */  lui   $at, %hi(D_8011D63C) # $at, 0x8012
/* 060518 8005F918 3C0500FF */  lui   $a1, (0x00FF00FF >> 16) # lui $a1, 0xff
/* 06051C 8005F91C AC22D63C */  sw    $v0, %lo(D_8011D63C)($at)
/* 060520 8005F920 34A500FF */  ori   $a1, (0x00FF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 060524 8005F924 0C01C327 */  jal   allocate_from_main_pool_safe
/* 060528 8005F928 24040C00 */   li    $a0, 3072
/* 06052C 8005F92C 3C018012 */  lui   $at, %hi(D_8011D644) # $at, 0x8012
/* 060530 8005F930 3C05800E */  lui   $a1, %hi(D_800DCEA4) # $a1, 0x800e
/* 060534 8005F934 8CA5CEA4 */  lw    $a1, %lo(D_800DCEA4)($a1)
/* 060538 8005F938 AC22D644 */  sw    $v0, %lo(D_8011D644)($at)
/* 06053C 8005F93C 3C018012 */  lui   $at, %hi(D_8011D640) # $at, 0x8012
/* 060540 8005F940 AC20D640 */  sw    $zero, %lo(D_8011D640)($at)
/* 060544 8005F944 00002025 */  move  $a0, $zero
/* 060548 8005F948 18A00009 */  blez  $a1, .L8005F970
/* 06054C 8005F94C 00001825 */   move  $v1, $zero
/* 060550 8005F950 3C028002 */  lui   $v0, %hi(func_80024D54) # $v0, 0x8002
/* 060554 8005F954 24424D54 */  addiu $v0, %lo(func_80024D54) # addiu $v0, $v0, 0x4d54
.L8005F958:
/* 060558 8005F958 00436021 */  addu  $t4, $v0, $v1
/* 06055C 8005F95C 918D0000 */  lbu   $t5, ($t4)
/* 060560 8005F960 24630001 */  addiu $v1, $v1, 1
/* 060564 8005F964 0065082A */  slt   $at, $v1, $a1
/* 060568 8005F968 1420FFFB */  bnez  $at, .L8005F958
/* 06056C 8005F96C 008D2021 */   addu  $a0, $a0, $t5
.L8005F970:
/* 060570 8005F970 3C0E800E */  lui   $t6, %hi(D_800DCEA0) # $t6, 0x800e
/* 060574 8005F974 8DCECEA0 */  lw    $t6, %lo(D_800DCEA0)($t6)
/* 060578 8005F978 00000000 */  nop   
/* 06057C 8005F97C 108E0004 */  beq   $a0, $t6, .L8005F990
/* 060580 8005F980 8FBF0014 */   lw    $ra, 0x14($sp)
/* 060584 8005F984 0C017097 */  jal   func_8005C25C
/* 060588 8005F988 00000000 */   nop   
/* 06058C 8005F98C 8FBF0014 */  lw    $ra, 0x14($sp)
.L8005F990:
/* 060590 8005F990 27BD0018 */  addiu $sp, $sp, 0x18
/* 060594 8005F994 03E00008 */  jr    $ra
/* 060598 8005F998 00000000 */   nop   

