glabel func_800AE728
/* 0AF328 800AE728 27BDFF98 */  addiu $sp, $sp, -0x68
/* 0AF32C 800AE72C AFB70034 */  sw    $s7, 0x34($sp)
/* 0AF330 800AE730 AFB40028 */  sw    $s4, 0x28($sp)
/* 0AF334 800AE734 AFB30024 */  sw    $s3, 0x24($sp)
/* 0AF338 800AE738 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0AF33C 800AE73C 3C01800E */  lui   $at, %hi(D_800E2D00) # $at, 0x800e
/* 0AF340 800AE740 00808825 */  move  $s1, $a0
/* 0AF344 800AE744 00A09825 */  move  $s3, $a1
/* 0AF348 800AE748 00E0A025 */  move  $s4, $a3
/* 0AF34C 800AE74C 00C0B825 */  move  $s7, $a2
/* 0AF350 800AE750 AFBF003C */  sw    $ra, 0x3c($sp)
/* 0AF354 800AE754 AFBE0038 */  sw    $fp, 0x38($sp)
/* 0AF358 800AE758 AFB60030 */  sw    $s6, 0x30($sp)
/* 0AF35C 800AE75C AFB5002C */  sw    $s5, 0x2c($sp)
/* 0AF360 800AE760 AFB20020 */  sw    $s2, 0x20($sp)
/* 0AF364 800AE764 AFB00018 */  sw    $s0, 0x18($sp)
/* 0AF368 800AE768 04810002 */  bgez  $a0, .L800AE774
/* 0AF36C 800AE76C AC202D00 */   sw    $zero, %lo(D_800E2D00)($at)
/* 0AF370 800AE770 24110010 */  li    $s1, 16
.L800AE774:
/* 0AF374 800AE774 8FBE0078 */  lw    $fp, 0x78($sp)
/* 0AF378 800AE778 06610002 */  bgez  $s3, .L800AE784
/* 0AF37C 800AE77C 3C01800E */   lui   $at, %hi(D_800E2E4C) # $at, 0x800e
/* 0AF380 800AE780 24130010 */  li    $s3, 16
.L800AE784:
/* 0AF384 800AE784 06E10002 */  bgez  $s7, .L800AE790
/* 0AF388 800AE788 00000000 */   nop   
/* 0AF38C 800AE78C 241700D0 */  li    $s7, 208
.L800AE790:
/* 0AF390 800AE790 06810002 */  bgez  $s4, .L800AE79C
/* 0AF394 800AE794 00000000 */   nop   
/* 0AF398 800AE798 241400A0 */  li    $s4, 160
.L800AE79C:
/* 0AF39C 800AE79C 07C10002 */  bgez  $fp, .L800AE7A8
/* 0AF3A0 800AE7A0 00000000 */   nop   
/* 0AF3A4 800AE7A4 241E0040 */  li    $fp, 64
.L800AE7A8:
/* 0AF3A8 800AE7A8 AC312E4C */  sw    $s1, %lo(D_800E2E4C)($at)
/* 0AF3AC 800AE7AC 3C01800E */  lui   $at, %hi(D_800E2CA4) # $at, 0x800e
/* 0AF3B0 800AE7B0 AC202CA4 */  sw    $zero, %lo(D_800E2CA4)($at)
/* 0AF3B4 800AE7B4 3C01800E */  lui   $at, %hi(D_800E2E50) # $at, 0x800e
/* 0AF3B8 800AE7B8 AC332E50 */  sw    $s3, %lo(D_800E2E50)($at)
/* 0AF3BC 800AE7BC 3C01800E */  lui   $at, %hi(D_800E2CB0) # $at, 0x800e
/* 0AF3C0 800AE7C0 AC202CB0 */  sw    $zero, %lo(D_800E2CB0)($at)
/* 0AF3C4 800AE7C4 3C01800E */  lui   $at, %hi(D_800E2E54) # $at, 0x800e
/* 0AF3C8 800AE7C8 AC372E54 */  sw    $s7, %lo(D_800E2E54)($at)
/* 0AF3CC 800AE7CC 3C01800E */  lui   $at, %hi(D_800E2CBC) # $at, 0x800e
/* 0AF3D0 800AE7D0 AC202CBC */  sw    $zero, %lo(D_800E2CBC)($at)
/* 0AF3D4 800AE7D4 3C01800E */  lui   $at, %hi(D_800E2E58) # $at, 0x800e
/* 0AF3D8 800AE7D8 AC342E58 */  sw    $s4, %lo(D_800E2E58)($at)
/* 0AF3DC 800AE7DC 3C01800E */  lui   $at, %hi(D_800E2CC8) # $at, 0x800e
/* 0AF3E0 800AE7E0 AC202CC8 */  sw    $zero, %lo(D_800E2CC8)($at)
/* 0AF3E4 800AE7E4 3C01800E */  lui   $at, %hi(D_800E2E5C) # $at, 0x800e
/* 0AF3E8 800AE7E8 AC3E2E5C */  sw    $fp, %lo(D_800E2E5C)($at)
/* 0AF3EC 800AE7EC 3C01800E */  lui   $at, %hi(D_800E2CD4) # $at, 0x800e
/* 0AF3F0 800AE7F0 0C02B90E */  jal   func_800AE438
/* 0AF3F4 800AE7F4 AC202CD4 */   sw    $zero, %lo(D_800E2CD4)($at)
/* 0AF3F8 800AE7F8 00117080 */  sll   $t6, $s1, 2
/* 0AF3FC 800AE7FC 00144880 */  sll   $t1, $s4, 2
/* 0AF400 800AE800 01344823 */  subu  $t1, $t1, $s4
/* 0AF404 800AE804 01D17023 */  subu  $t6, $t6, $s1
/* 0AF408 800AE808 00137880 */  sll   $t7, $s3, 2
/* 0AF40C 800AE80C 01CFC021 */  addu  $t8, $t6, $t7
/* 0AF410 800AE810 00094840 */  sll   $t1, $t1, 1
/* 0AF414 800AE814 03095021 */  addu  $t2, $t8, $t1
/* 0AF418 800AE818 001E5900 */  sll   $t3, $fp, 4
/* 0AF41C 800AE81C 014B2021 */  addu  $a0, $t2, $t3
/* 0AF420 800AE820 3C128080 */  lui   $s2, (0x80808080 >> 16) # lui $s2, 0x8080
/* 0AF424 800AE824 00046080 */  sll   $t4, $a0, 2
/* 0AF428 800AE828 36528080 */  ori   $s2, (0x80808080 & 0xFFFF) # ori $s2, $s2, 0x8080
/* 0AF42C 800AE82C 01846021 */  addu  $t4, $t4, $a0
/* 0AF430 800AE830 000C2040 */  sll   $a0, $t4, 1
/* 0AF434 800AE834 02402825 */  move  $a1, $s2
/* 0AF438 800AE838 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AF43C 800AE83C 00008025 */   move  $s0, $zero
/* 0AF440 800AE840 00136840 */  sll   $t5, $s3, 1
/* 0AF444 800AE844 022D7021 */  addu  $t6, $s1, $t5
/* 0AF448 800AE848 01D02021 */  addu  $a0, $t6, $s0
/* 0AF44C 800AE84C 3C01800E */  lui   $at, %hi(D_800E2CE0) # $at, 0x800e
/* 0AF450 800AE850 00047900 */  sll   $t7, $a0, 4
/* 0AF454 800AE854 AC222CE0 */  sw    $v0, %lo(D_800E2CE0)($at)
/* 0AF458 800AE858 01E02025 */  move  $a0, $t7
/* 0AF45C 800AE85C 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AF460 800AE860 02402825 */   move  $a1, $s2
/* 0AF464 800AE864 3C10800E */  lui   $s0, %hi(D_800E2CE4) # $s0, 0x800e
/* 0AF468 800AE868 26102CE4 */  addiu $s0, %lo(D_800E2CE4) # addiu $s0, $s0, 0x2ce4
/* 0AF46C 800AE86C AE020000 */  sw    $v0, ($s0)
/* 0AF470 800AE870 3C01800E */  lui   $at, %hi(D_800E2CDC) # $at, 0x800e
/* 0AF474 800AE874 0C02B8DD */  jal   func_800AE374
/* 0AF478 800AE878 AC202CDC */   sw    $zero, %lo(D_800E2CDC)($at)
/* 0AF47C 800AE87C 3C18800E */  lui   $t8, %hi(D_800E2E4C) # $t8, 0x800e
/* 0AF480 800AE880 8F182E4C */  lw    $t8, %lo(D_800E2E4C)($t8)
/* 0AF484 800AE884 00000000 */  nop   
/* 0AF488 800AE888 1B000008 */  blez  $t8, .L800AE8AC
/* 0AF48C 800AE88C 3C01800E */   lui   $at, %hi(D_800E2CA0) # $at, 0x800e
/* 0AF490 800AE890 AC202CA0 */  sw    $zero, %lo(D_800E2CA0)($at)
/* 0AF494 800AE894 001121C0 */  sll   $a0, $s1, 7
/* 0AF498 800AE898 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AF49C 800AE89C 02402825 */   move  $a1, $s2
/* 0AF4A0 800AE8A0 3C15800E */  lui   $s5, %hi(D_800E2CA8) # $s5, 0x800e
/* 0AF4A4 800AE8A4 26B52CA8 */  addiu $s5, %lo(D_800E2CA8) # addiu $s5, $s5, 0x2ca8
/* 0AF4A8 800AE8A8 AEA20000 */  sw    $v0, ($s5)
.L800AE8AC:
/* 0AF4AC 800AE8AC 3C19800E */  lui   $t9, %hi(D_800E2E50) # $t9, 0x800e
/* 0AF4B0 800AE8B0 8F392E50 */  lw    $t9, %lo(D_800E2E50)($t9)
/* 0AF4B4 800AE8B4 3C15800E */  lui   $s5, %hi(D_800E2CA8) # $s5, 0x800e
/* 0AF4B8 800AE8B8 1B200009 */  blez  $t9, .L800AE8E0
/* 0AF4BC 800AE8BC 26B52CA8 */   addiu $s5, %lo(D_800E2CA8) # addiu $s5, $s5, 0x2ca8
/* 0AF4C0 800AE8C0 3C01800E */  lui   $at, %hi(D_800E2CAC) # $at, 0x800e
/* 0AF4C4 800AE8C4 AC202CAC */  sw    $zero, %lo(D_800E2CAC)($at)
/* 0AF4C8 800AE8C8 001321C0 */  sll   $a0, $s3, 7
/* 0AF4CC 800AE8CC 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AF4D0 800AE8D0 02402825 */   move  $a1, $s2
/* 0AF4D4 800AE8D4 3C16800E */  lui   $s6, %hi(D_800E2CB4) # $s6, 0x800e
/* 0AF4D8 800AE8D8 26D62CB4 */  addiu $s6, %lo(D_800E2CB4) # addiu $s6, $s6, 0x2cb4
/* 0AF4DC 800AE8DC AEC20000 */  sw    $v0, ($s6)
.L800AE8E0:
/* 0AF4E0 800AE8E0 3C09800E */  lui   $t1, %hi(D_800E2E54) # $t1, 0x800e
/* 0AF4E4 800AE8E4 8D292E54 */  lw    $t1, %lo(D_800E2E54)($t1)
/* 0AF4E8 800AE8E8 3C16800E */  lui   $s6, %hi(D_800E2CB4) # $s6, 0x800e
/* 0AF4EC 800AE8EC 1920000A */  blez  $t1, .L800AE918
/* 0AF4F0 800AE8F0 26D62CB4 */   addiu $s6, %lo(D_800E2CB4) # addiu $s6, $s6, 0x2cb4
/* 0AF4F4 800AE8F4 001720C0 */  sll   $a0, $s7, 3
/* 0AF4F8 800AE8F8 3C01800E */  lui   $at, %hi(D_800E2CB8) # $at, 0x800e
/* 0AF4FC 800AE8FC 00972023 */  subu  $a0, $a0, $s7
/* 0AF500 800AE900 AC202CB8 */  sw    $zero, %lo(D_800E2CB8)($at)
/* 0AF504 800AE904 00042100 */  sll   $a0, $a0, 4
/* 0AF508 800AE908 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AF50C 800AE90C 02402825 */   move  $a1, $s2
/* 0AF510 800AE910 3C01800E */  lui   $at, %hi(D_800E2CC0) # $at, 0x800e
/* 0AF514 800AE914 AC222CC0 */  sw    $v0, %lo(D_800E2CC0)($at)
.L800AE918:
/* 0AF518 800AE918 3C0A800E */  lui   $t2, %hi(D_800E2E58) # $t2, 0x800e
/* 0AF51C 800AE91C 8D4A2E58 */  lw    $t2, %lo(D_800E2E58)($t2)
/* 0AF520 800AE920 00000000 */  nop   
/* 0AF524 800AE924 19400008 */  blez  $t2, .L800AE948
/* 0AF528 800AE928 3C01800E */   lui   $at, %hi(D_800E2CC4) # $at, 0x800e
/* 0AF52C 800AE92C AC202CC4 */  sw    $zero, %lo(D_800E2CC4)($at)
/* 0AF530 800AE930 001421C0 */  sll   $a0, $s4, 7
/* 0AF534 800AE934 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AF538 800AE938 02402825 */   move  $a1, $s2
/* 0AF53C 800AE93C 3C17800E */  lui   $s7, %hi(D_800E2CCC) # $s7, 0x800e
/* 0AF540 800AE940 26F72CCC */  addiu $s7, %lo(D_800E2CCC) # addiu $s7, $s7, 0x2ccc
/* 0AF544 800AE944 AEE20000 */  sw    $v0, ($s7)
.L800AE948:
/* 0AF548 800AE948 3C0B800E */  lui   $t3, %hi(D_800E2E5C) # $t3, 0x800e
/* 0AF54C 800AE94C 8D6B2E5C */  lw    $t3, %lo(D_800E2E5C)($t3)
/* 0AF550 800AE950 3C17800E */  lui   $s7, %hi(D_800E2CCC) # $s7, 0x800e
/* 0AF554 800AE954 1960000B */  blez  $t3, .L800AE984
/* 0AF558 800AE958 26F72CCC */   addiu $s7, %lo(D_800E2CCC) # addiu $s7, $s7, 0x2ccc
/* 0AF55C 800AE95C 001E2100 */  sll   $a0, $fp, 4
/* 0AF560 800AE960 3C01800E */  lui   $at, %hi(D_800E2CD0) # $at, 0x800e
/* 0AF564 800AE964 009E2021 */  addu  $a0, $a0, $fp
/* 0AF568 800AE968 AC202CD0 */  sw    $zero, %lo(D_800E2CD0)($at)
/* 0AF56C 800AE96C 000420C0 */  sll   $a0, $a0, 3
/* 0AF570 800AE970 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AF574 800AE974 02402825 */   move  $a1, $s2
/* 0AF578 800AE978 3C1E800E */  lui   $fp, %hi(D_800E2CD8) # $fp, 0x800e
/* 0AF57C 800AE97C 27DE2CD8 */  addiu $fp, %lo(D_800E2CD8) # addiu $fp, $fp, 0x2cd8
/* 0AF580 800AE980 AFC20000 */  sw    $v0, ($fp)
.L800AE984:
/* 0AF584 800AE984 3C02800E */  lui   $v0, %hi(D_800E2E4C) # $v0, 0x800e
/* 0AF588 800AE988 8C422E4C */  lw    $v0, %lo(D_800E2E4C)($v0)
/* 0AF58C 800AE98C 3C0D800E */  lui   $t5, %hi(D_800E2CE0) # $t5, 0x800e
/* 0AF590 800AE990 8DAD2CE0 */  lw    $t5, %lo(D_800E2CE0)($t5)
/* 0AF594 800AE994 8E180000 */  lw    $t8, ($s0)
/* 0AF598 800AE998 000250C0 */  sll   $t2, $v0, 3
/* 0AF59C 800AE99C 8EA90000 */  lw    $t1, ($s5)
/* 0AF5A0 800AE9A0 000060C0 */  sll   $t4, $zero, 3
/* 0AF5A4 800AE9A4 00007900 */  sll   $t7, $zero, 4
/* 0AF5A8 800AE9A8 01425023 */  subu  $t2, $t2, $v0
/* 0AF5AC 800AE9AC 3C1E800E */  lui   $fp, %hi(D_800E2CD8) # $fp, 0x800e
/* 0AF5B0 800AE9B0 000A5100 */  sll   $t2, $t2, 4
/* 0AF5B4 800AE9B4 018D7021 */  addu  $t6, $t4, $t5
/* 0AF5B8 800AE9B8 01F8C821 */  addu  $t9, $t7, $t8
/* 0AF5BC 800AE9BC 27DE2CD8 */  addiu $fp, %lo(D_800E2CD8) # addiu $fp, $fp, 0x2cd8
/* 0AF5C0 800AE9C0 AFAE0054 */  sw    $t6, 0x54($sp)
/* 0AF5C4 800AE9C4 AFB90050 */  sw    $t9, 0x50($sp)
/* 0AF5C8 800AE9C8 00008825 */  move  $s1, $zero
/* 0AF5CC 800AE9CC 18400016 */  blez  $v0, .L800AEA28
/* 0AF5D0 800AE9D0 012A9021 */   addu  $s2, $t1, $t2
/* 0AF5D4 800AE9D4 00008025 */  move  $s0, $zero
/* 0AF5D8 800AE9D8 27B40050 */  addiu $s4, $sp, 0x50
/* 0AF5DC 800AE9DC 27B30054 */  addiu $s3, $sp, 0x54
.L800AE9E0:
/* 0AF5E0 800AE9E0 8EAD0000 */  lw    $t5, ($s5)
/* 0AF5E4 800AE9E4 00115900 */  sll   $t3, $s1, 4
/* 0AF5E8 800AE9E8 01726021 */  addu  $t4, $t3, $s2
/* 0AF5EC 800AE9EC 01B07021 */  addu  $t6, $t5, $s0
/* 0AF5F0 800AE9F0 ADCC0044 */  sw    $t4, 0x44($t6)
/* 0AF5F4 800AE9F4 8EAF0000 */  lw    $t7, ($s5)
/* 0AF5F8 800AE9F8 02602825 */  move  $a1, $s3
/* 0AF5FC 800AE9FC 01F0C021 */  addu  $t8, $t7, $s0
/* 0AF600 800AEA00 8F040044 */  lw    $a0, 0x44($t8)
/* 0AF604 800AEA04 0C02BB85 */  jal   generate_particle_shape_triangle
/* 0AF608 800AEA08 02803025 */   move  $a2, $s4
/* 0AF60C 800AEA0C 3C19800E */  lui   $t9, %hi(D_800E2E4C) # $t9, 0x800e
/* 0AF610 800AEA10 8F392E4C */  lw    $t9, %lo(D_800E2E4C)($t9)
/* 0AF614 800AEA14 26310001 */  addiu $s1, $s1, 1
/* 0AF618 800AEA18 0239082A */  slt   $at, $s1, $t9
/* 0AF61C 800AEA1C 1420FFF0 */  bnez  $at, .L800AE9E0
/* 0AF620 800AEA20 26100070 */   addiu $s0, $s0, 0x70
/* 0AF624 800AEA24 00008825 */  move  $s1, $zero
.L800AEA28:
/* 0AF628 800AEA28 3C03800E */  lui   $v1, %hi(D_800E2E50) # $v1, 0x800e
/* 0AF62C 800AEA2C 24632E50 */  addiu $v1, %lo(D_800E2E50) # addiu $v1, $v1, 0x2e50
/* 0AF630 800AEA30 8C620000 */  lw    $v0, ($v1)
/* 0AF634 800AEA34 8EC90000 */  lw    $t1, ($s6)
/* 0AF638 800AEA38 000250C0 */  sll   $t2, $v0, 3
/* 0AF63C 800AEA3C 01425023 */  subu  $t2, $t2, $v0
/* 0AF640 800AEA40 000A5100 */  sll   $t2, $t2, 4
/* 0AF644 800AEA44 27B30054 */  addiu $s3, $sp, 0x54
/* 0AF648 800AEA48 27B40050 */  addiu $s4, $sp, 0x50
/* 0AF64C 800AEA4C 18400016 */  blez  $v0, .L800AEAA8
/* 0AF650 800AEA50 012A9021 */   addu  $s2, $t1, $t2
/* 0AF654 800AEA54 00008025 */  move  $s0, $zero
.L800AEA58:
/* 0AF658 800AEA58 8ECC0000 */  lw    $t4, ($s6)
/* 0AF65C 800AEA5C 00115900 */  sll   $t3, $s1, 4
/* 0AF660 800AEA60 01726821 */  addu  $t5, $t3, $s2
/* 0AF664 800AEA64 01907021 */  addu  $t6, $t4, $s0
/* 0AF668 800AEA68 ADCD0044 */  sw    $t5, 0x44($t6)
/* 0AF66C 800AEA6C 8ECF0000 */  lw    $t7, ($s6)
/* 0AF670 800AEA70 02602825 */  move  $a1, $s3
/* 0AF674 800AEA74 01F0C021 */  addu  $t8, $t7, $s0
/* 0AF678 800AEA78 8F040044 */  lw    $a0, 0x44($t8)
/* 0AF67C 800AEA7C 0C02BBAE */  jal   generate_particle_shape_quad
/* 0AF680 800AEA80 02803025 */   move  $a2, $s4
/* 0AF684 800AEA84 3C19800E */  lui   $t9, %hi(D_800E2E50) # $t9, 0x800e
/* 0AF688 800AEA88 8F392E50 */  lw    $t9, %lo(D_800E2E50)($t9)
/* 0AF68C 800AEA8C 26310001 */  addiu $s1, $s1, 1
/* 0AF690 800AEA90 0239082A */  slt   $at, $s1, $t9
/* 0AF694 800AEA94 1420FFF0 */  bnez  $at, .L800AEA58
/* 0AF698 800AEA98 26100070 */   addiu $s0, $s0, 0x70
/* 0AF69C 800AEA9C 3C03800E */  lui   $v1, %hi(D_800E2E50) # $v1, 0x800e
/* 0AF6A0 800AEAA0 24632E50 */  addiu $v1, %lo(D_800E2E50) # addiu $v1, $v1, 0x2e50
/* 0AF6A4 800AEAA4 00008825 */  move  $s1, $zero
.L800AEAA8:
/* 0AF6A8 800AEAA8 3C07800E */  lui   $a3, %hi(D_800E2E58) # $a3, 0x800e
/* 0AF6AC 800AEAAC 24E72E58 */  addiu $a3, %lo(D_800E2E58) # addiu $a3, $a3, 0x2e58
/* 0AF6B0 800AEAB0 8CE20000 */  lw    $v0, ($a3)
/* 0AF6B4 800AEAB4 8EE90000 */  lw    $t1, ($s7)
/* 0AF6B8 800AEAB8 000250C0 */  sll   $t2, $v0, 3
/* 0AF6BC 800AEABC 01425023 */  subu  $t2, $t2, $v0
/* 0AF6C0 800AEAC0 000A5100 */  sll   $t2, $t2, 4
/* 0AF6C4 800AEAC4 1840001B */  blez  $v0, .L800AEB34
/* 0AF6C8 800AEAC8 012A9021 */   addu  $s2, $t1, $t2
/* 0AF6CC 800AEACC 00008025 */  move  $s0, $zero
.L800AEAD0:
/* 0AF6D0 800AEAD0 8EED0000 */  lw    $t5, ($s7)
/* 0AF6D4 800AEAD4 00115900 */  sll   $t3, $s1, 4
/* 0AF6D8 800AEAD8 01726021 */  addu  $t4, $t3, $s2
/* 0AF6DC 800AEADC 01B07021 */  addu  $t6, $t5, $s0
/* 0AF6E0 800AEAE0 ADCC0044 */  sw    $t4, 0x44($t6)
/* 0AF6E4 800AEAE4 8EF80000 */  lw    $t8, ($s7)
/* 0AF6E8 800AEAE8 3C0F800E */  lui   $t7, %hi(D_800E2D08) # $t7, 0x800e
/* 0AF6EC 800AEAEC 25EF2D08 */  addiu $t7, %lo(D_800E2D08) # addiu $t7, $t7, 0x2d08
/* 0AF6F0 800AEAF0 AFAF0050 */  sw    $t7, 0x50($sp)
/* 0AF6F4 800AEAF4 0310C821 */  addu  $t9, $t8, $s0
/* 0AF6F8 800AEAF8 8F240044 */  lw    $a0, 0x44($t9)
/* 0AF6FC 800AEAFC 02602825 */  move  $a1, $s3
/* 0AF700 800AEB00 0C02BBE2 */  jal   func_800AEF88
/* 0AF704 800AEB04 02803025 */   move  $a2, $s4
/* 0AF708 800AEB08 3C09800E */  lui   $t1, %hi(D_800E2E58) # $t1, 0x800e
/* 0AF70C 800AEB0C 8D292E58 */  lw    $t1, %lo(D_800E2E58)($t1)
/* 0AF710 800AEB10 26310001 */  addiu $s1, $s1, 1
/* 0AF714 800AEB14 0229082A */  slt   $at, $s1, $t1
/* 0AF718 800AEB18 1420FFED */  bnez  $at, .L800AEAD0
/* 0AF71C 800AEB1C 26100070 */   addiu $s0, $s0, 0x70
/* 0AF720 800AEB20 3C07800E */  lui   $a3, %hi(D_800E2E58) # $a3, 0x800e
/* 0AF724 800AEB24 3C03800E */  lui   $v1, %hi(D_800E2E50) # $v1, 0x800e
/* 0AF728 800AEB28 24632E50 */  addiu $v1, %lo(D_800E2E50) # addiu $v1, $v1, 0x2e50
/* 0AF72C 800AEB2C 24E72E58 */  addiu $a3, %lo(D_800E2E58) # addiu $a3, $a3, 0x2e58
/* 0AF730 800AEB30 00008825 */  move  $s1, $zero
.L800AEB34:
/* 0AF734 800AEB34 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF738 800AEB38 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF73C 800AEB3C 8D020000 */  lw    $v0, ($t0)
/* 0AF740 800AEB40 8FCA0000 */  lw    $t2, ($fp)
/* 0AF744 800AEB44 00025900 */  sll   $t3, $v0, 4
/* 0AF748 800AEB48 01625823 */  subu  $t3, $t3, $v0
/* 0AF74C 800AEB4C 000B58C0 */  sll   $t3, $t3, 3
/* 0AF750 800AEB50 1840001D */  blez  $v0, .L800AEBC8
/* 0AF754 800AEB54 014B9021 */   addu  $s2, $t2, $t3
/* 0AF758 800AEB58 00008025 */  move  $s0, $zero
.L800AEB5C:
/* 0AF75C 800AEB5C 8FCE0000 */  lw    $t6, ($fp)
/* 0AF760 800AEB60 00116900 */  sll   $t5, $s1, 4
/* 0AF764 800AEB64 01B26021 */  addu  $t4, $t5, $s2
/* 0AF768 800AEB68 01D07821 */  addu  $t7, $t6, $s0
/* 0AF76C 800AEB6C ADEC0044 */  sw    $t4, 0x44($t7)
/* 0AF770 800AEB70 8FD90000 */  lw    $t9, ($fp)
/* 0AF774 800AEB74 3C18800E */  lui   $t8, %hi(D_800E2D78) # $t8, 0x800e
/* 0AF778 800AEB78 27182D78 */  addiu $t8, %lo(D_800E2D78) # addiu $t8, $t8, 0x2d78
/* 0AF77C 800AEB7C AFB80050 */  sw    $t8, 0x50($sp)
/* 0AF780 800AEB80 03304821 */  addu  $t1, $t9, $s0
/* 0AF784 800AEB84 8D240044 */  lw    $a0, 0x44($t1)
/* 0AF788 800AEB88 02602825 */  move  $a1, $s3
/* 0AF78C 800AEB8C 0C02BC09 */  jal   func_800AF024
/* 0AF790 800AEB90 02803025 */   move  $a2, $s4
/* 0AF794 800AEB94 3C0A800E */  lui   $t2, %hi(D_800E2E5C) # $t2, 0x800e
/* 0AF798 800AEB98 8D4A2E5C */  lw    $t2, %lo(D_800E2E5C)($t2)
/* 0AF79C 800AEB9C 26310001 */  addiu $s1, $s1, 1
/* 0AF7A0 800AEBA0 022A082A */  slt   $at, $s1, $t2
/* 0AF7A4 800AEBA4 1420FFED */  bnez  $at, .L800AEB5C
/* 0AF7A8 800AEBA8 26100078 */   addiu $s0, $s0, 0x78
/* 0AF7AC 800AEBAC 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF7B0 800AEBB0 3C07800E */  lui   $a3, %hi(D_800E2E58) # $a3, 0x800e
/* 0AF7B4 800AEBB4 3C03800E */  lui   $v1, %hi(D_800E2E50) # $v1, 0x800e
/* 0AF7B8 800AEBB8 24632E50 */  addiu $v1, %lo(D_800E2E50) # addiu $v1, $v1, 0x2e50
/* 0AF7BC 800AEBBC 24E72E58 */  addiu $a3, %lo(D_800E2E58) # addiu $a3, $a3, 0x2e58
/* 0AF7C0 800AEBC0 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF7C4 800AEBC4 00008825 */  move  $s1, $zero
.L800AEBC8:
/* 0AF7C8 800AEBC8 3C0B800E */  lui   $t3, %hi(D_800E2E4C) # $t3, 0x800e
/* 0AF7CC 800AEBCC 8D6B2E4C */  lw    $t3, %lo(D_800E2E4C)($t3)
/* 0AF7D0 800AEBD0 3C13800E */  lui   $s3, %hi(D_800E2E60) # $s3, 0x800e
/* 0AF7D4 800AEBD4 1960000E */  blez  $t3, .L800AEC10
/* 0AF7D8 800AEBD8 26732E60 */   addiu $s3, %lo(D_800E2E60) # addiu $s3, $s3, 0x2e60
/* 0AF7DC 800AEBDC 00008025 */  move  $s0, $zero
.L800AEBE0:
/* 0AF7E0 800AEBE0 8EAD0000 */  lw    $t5, ($s5)
/* 0AF7E4 800AEBE4 3C0C800E */  lui   $t4, %hi(D_800E2E4C) # $t4, 0x800e
/* 0AF7E8 800AEBE8 01B07021 */  addu  $t6, $t5, $s0
/* 0AF7EC 800AEBEC A5C0002C */  sh    $zero, 0x2c($t6)
/* 0AF7F0 800AEBF0 8D8C2E4C */  lw    $t4, %lo(D_800E2E4C)($t4)
/* 0AF7F4 800AEBF4 26310001 */  addiu $s1, $s1, 1
/* 0AF7F8 800AEBF8 022C082A */  slt   $at, $s1, $t4
/* 0AF7FC 800AEBFC 1420FFF8 */  bnez  $at, .L800AEBE0
/* 0AF800 800AEC00 26100070 */   addiu $s0, $s0, 0x70
/* 0AF804 800AEC04 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF808 800AEC08 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF80C 800AEC0C 00008825 */  move  $s1, $zero
.L800AEC10:
/* 0AF810 800AEC10 8C6F0000 */  lw    $t7, ($v1)
/* 0AF814 800AEC14 00008025 */  move  $s0, $zero
/* 0AF818 800AEC18 19E0000D */  blez  $t7, .L800AEC50
/* 0AF81C 800AEC1C 3C02800E */   lui   $v0, %hi(D_800E2CC0) # $v0, 0x800e
.L800AEC20:
/* 0AF820 800AEC20 8ED80000 */  lw    $t8, ($s6)
/* 0AF824 800AEC24 26310001 */  addiu $s1, $s1, 1
/* 0AF828 800AEC28 0310C821 */  addu  $t9, $t8, $s0
/* 0AF82C 800AEC2C A720002C */  sh    $zero, 0x2c($t9)
/* 0AF830 800AEC30 8C690000 */  lw    $t1, ($v1)
/* 0AF834 800AEC34 26100070 */  addiu $s0, $s0, 0x70
/* 0AF838 800AEC38 0229082A */  slt   $at, $s1, $t1
/* 0AF83C 800AEC3C 1420FFF8 */  bnez  $at, .L800AEC20
/* 0AF840 800AEC40 00000000 */   nop   
/* 0AF844 800AEC44 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF848 800AEC48 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF84C 800AEC4C 00008825 */  move  $s1, $zero
.L800AEC50:
/* 0AF850 800AEC50 3C03800E */  lui   $v1, %hi(D_800E2E54) # $v1, 0x800e
/* 0AF854 800AEC54 24632E54 */  addiu $v1, %lo(D_800E2E54) # addiu $v1, $v1, 0x2e54
/* 0AF858 800AEC58 8C6A0000 */  lw    $t2, ($v1)
/* 0AF85C 800AEC5C 00008025 */  move  $s0, $zero
/* 0AF860 800AEC60 1940000D */  blez  $t2, .L800AEC98
/* 0AF864 800AEC64 24422CC0 */   addiu $v0, %lo(D_800E2CC0) # addiu $v0, $v0, 0x2cc0
.L800AEC68:
/* 0AF868 800AEC68 8C4B0000 */  lw    $t3, ($v0)
/* 0AF86C 800AEC6C 26310001 */  addiu $s1, $s1, 1
/* 0AF870 800AEC70 01706821 */  addu  $t5, $t3, $s0
/* 0AF874 800AEC74 A5A0002C */  sh    $zero, 0x2c($t5)
/* 0AF878 800AEC78 8C6E0000 */  lw    $t6, ($v1)
/* 0AF87C 800AEC7C 26100070 */  addiu $s0, $s0, 0x70
/* 0AF880 800AEC80 022E082A */  slt   $at, $s1, $t6
/* 0AF884 800AEC84 1420FFF8 */  bnez  $at, .L800AEC68
/* 0AF888 800AEC88 00000000 */   nop   
/* 0AF88C 800AEC8C 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF890 800AEC90 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF894 800AEC94 00008825 */  move  $s1, $zero
.L800AEC98:
/* 0AF898 800AEC98 8CEC0000 */  lw    $t4, ($a3)
/* 0AF89C 800AEC9C 00008025 */  move  $s0, $zero
/* 0AF8A0 800AECA0 1980000D */  blez  $t4, .L800AECD8
/* 0AF8A4 800AECA4 2404002F */   li    $a0, 47
.L800AECA8:
/* 0AF8A8 800AECA8 8EEF0000 */  lw    $t7, ($s7)
/* 0AF8AC 800AECAC 26310001 */  addiu $s1, $s1, 1
/* 0AF8B0 800AECB0 01F0C021 */  addu  $t8, $t7, $s0
/* 0AF8B4 800AECB4 A700002C */  sh    $zero, 0x2c($t8)
/* 0AF8B8 800AECB8 8CF90000 */  lw    $t9, ($a3)
/* 0AF8BC 800AECBC 26100070 */  addiu $s0, $s0, 0x70
/* 0AF8C0 800AECC0 0239082A */  slt   $at, $s1, $t9
/* 0AF8C4 800AECC4 1420FFF8 */  bnez  $at, .L800AECA8
/* 0AF8C8 800AECC8 00000000 */   nop   
/* 0AF8CC 800AECCC 3C08800E */  lui   $t0, %hi(D_800E2E5C) # $t0, 0x800e
/* 0AF8D0 800AECD0 25082E5C */  addiu $t0, %lo(D_800E2E5C) # addiu $t0, $t0, 0x2e5c
/* 0AF8D4 800AECD4 00008825 */  move  $s1, $zero
.L800AECD8:
/* 0AF8D8 800AECD8 8D090000 */  lw    $t1, ($t0)
/* 0AF8DC 800AECDC 00008025 */  move  $s0, $zero
/* 0AF8E0 800AECE0 1920000A */  blez  $t1, .L800AED0C
/* 0AF8E4 800AECE4 00000000 */   nop   
.L800AECE8:
/* 0AF8E8 800AECE8 8FCA0000 */  lw    $t2, ($fp)
/* 0AF8EC 800AECEC 26310001 */  addiu $s1, $s1, 1
/* 0AF8F0 800AECF0 01505821 */  addu  $t3, $t2, $s0
/* 0AF8F4 800AECF4 A560002C */  sh    $zero, 0x2c($t3)
/* 0AF8F8 800AECF8 8D0D0000 */  lw    $t5, ($t0)
/* 0AF8FC 800AECFC 26100078 */  addiu $s0, $s0, 0x78
/* 0AF900 800AED00 022D082A */  slt   $at, $s1, $t5
/* 0AF904 800AED04 1420FFF8 */  bnez  $at, .L800AECE8
/* 0AF908 800AED08 00000000 */   nop   
.L800AED0C:
/* 0AF90C 800AED0C 8E6E0000 */  lw    $t6, ($s3)
/* 0AF910 800AED10 00000000 */  nop   
/* 0AF914 800AED14 15C00034 */  bnez  $t6, .L800AEDE8
/* 0AF918 800AED18 8FBF003C */   lw    $ra, 0x3c($sp)
/* 0AF91C 800AED1C 0C01DB16 */  jal   load_asset_section_from_rom
/* 0AF920 800AED20 00008825 */   move  $s1, $zero
/* 0AF924 800AED24 3C06800E */  lui   $a2, %hi(D_800E2E64) # $a2, 0x800e
/* 0AF928 800AED28 24C62E64 */  addiu $a2, %lo(D_800E2E64) # addiu $a2, $a2, 0x2e64
/* 0AF92C 800AED2C 00006040 */  sll   $t4, $zero, 1
/* 0AF930 800AED30 ACC00000 */  sw    $zero, ($a2)
/* 0AF934 800AED34 004C7821 */  addu  $t7, $v0, $t4
/* 0AF938 800AED38 85F80000 */  lh    $t8, ($t7)
/* 0AF93C 800AED3C 2404FFFF */  li    $a0, -1
/* 0AF940 800AED40 00409025 */  move  $s2, $v0
/* 0AF944 800AED44 10980009 */  beq   $a0, $t8, .L800AED6C
/* 0AF948 800AED48 00001825 */   move  $v1, $zero
/* 0AF94C 800AED4C 24790001 */  addiu $t9, $v1, 1
.L800AED50:
/* 0AF950 800AED50 00194840 */  sll   $t1, $t9, 1
/* 0AF954 800AED54 02495021 */  addu  $t2, $s2, $t1
/* 0AF958 800AED58 ACD90000 */  sw    $t9, ($a2)
/* 0AF95C 800AED5C 854B0000 */  lh    $t3, ($t2)
/* 0AF960 800AED60 03201825 */  move  $v1, $t9
/* 0AF964 800AED64 148BFFFA */  bne   $a0, $t3, .L800AED50
/* 0AF968 800AED68 24790001 */   addiu $t9, $v1, 1
.L800AED6C:
/* 0AF96C 800AED6C 00032080 */  sll   $a0, $v1, 2
/* 0AF970 800AED70 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AF974 800AED74 3405FFFF */   li    $a1, 65535
/* 0AF978 800AED78 3C06800E */  lui   $a2, %hi(D_800E2E64) # $a2, 0x800e
/* 0AF97C 800AED7C 24C62E64 */  addiu $a2, %lo(D_800E2E64) # addiu $a2, $a2, 0x2e64
/* 0AF980 800AED80 8CCD0000 */  lw    $t5, ($a2)
/* 0AF984 800AED84 AE620000 */  sw    $v0, ($s3)
/* 0AF988 800AED88 19A00014 */  blez  $t5, .L800AEDDC
/* 0AF98C 800AED8C 02408025 */   move  $s0, $s2
/* 0AF990 800AED90 00001825 */  move  $v1, $zero
.L800AED94:
/* 0AF994 800AED94 86040000 */  lh    $a0, ($s0)
/* 0AF998 800AED98 AFA30044 */  sw    $v1, 0x44($sp)
/* 0AF99C 800AED9C 308E3FFF */  andi  $t6, $a0, 0x3fff
/* 0AF9A0 800AEDA0 01C02025 */  move  $a0, $t6
/* 0AF9A4 800AEDA4 0C01F04B */  jal   func_8007C12C
/* 0AF9A8 800AEDA8 24050001 */   li    $a1, 1
/* 0AF9AC 800AEDAC 8FA30044 */  lw    $v1, 0x44($sp)
/* 0AF9B0 800AEDB0 8E6C0000 */  lw    $t4, ($s3)
/* 0AF9B4 800AEDB4 3C06800E */  lui   $a2, %hi(D_800E2E64) # $a2, 0x800e
/* 0AF9B8 800AEDB8 01837821 */  addu  $t7, $t4, $v1
/* 0AF9BC 800AEDBC ADE20000 */  sw    $v0, ($t7)
/* 0AF9C0 800AEDC0 24C62E64 */  addiu $a2, %lo(D_800E2E64) # addiu $a2, $a2, 0x2e64
/* 0AF9C4 800AEDC4 8CD80000 */  lw    $t8, ($a2)
/* 0AF9C8 800AEDC8 26310001 */  addiu $s1, $s1, 1
/* 0AF9CC 800AEDCC 0238082A */  slt   $at, $s1, $t8
/* 0AF9D0 800AEDD0 26100002 */  addiu $s0, $s0, 2
/* 0AF9D4 800AEDD4 1420FFEF */  bnez  $at, .L800AED94
/* 0AF9D8 800AEDD8 24630004 */   addiu $v1, $v1, 4
.L800AEDDC:
/* 0AF9DC 800AEDDC 0C01C450 */  jal   free_from_memory_pool
/* 0AF9E0 800AEDE0 02402025 */   move  $a0, $s2
/* 0AF9E4 800AEDE4 8FBF003C */  lw    $ra, 0x3c($sp)
.L800AEDE8:
/* 0AF9E8 800AEDE8 8FB00018 */  lw    $s0, 0x18($sp)
/* 0AF9EC 800AEDEC 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0AF9F0 800AEDF0 8FB20020 */  lw    $s2, 0x20($sp)
/* 0AF9F4 800AEDF4 8FB30024 */  lw    $s3, 0x24($sp)
/* 0AF9F8 800AEDF8 8FB40028 */  lw    $s4, 0x28($sp)
/* 0AF9FC 800AEDFC 8FB5002C */  lw    $s5, 0x2c($sp)
/* 0AFA00 800AEE00 8FB60030 */  lw    $s6, 0x30($sp)
/* 0AFA04 800AEE04 8FB70034 */  lw    $s7, 0x34($sp)
/* 0AFA08 800AEE08 8FBE0038 */  lw    $fp, 0x38($sp)
/* 0AFA0C 800AEE0C 03E00008 */  jr    $ra
/* 0AFA10 800AEE10 27BD0068 */   addiu $sp, $sp, 0x68

