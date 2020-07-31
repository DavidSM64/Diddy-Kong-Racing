glabel func_800CD770
/* 0CE370 800CD770 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CE374 800CD774 3084FFFF */  andi  $a0, $a0, 0xffff
/* 0CE378 800CD778 A3A0000F */  sb    $zero, 0xf($sp)
/* 0CE37C 800CD77C AFA00008 */  sw    $zero, 8($sp)
.L800CD780:
/* 0CE380 800CD780 93AE000F */  lbu   $t6, 0xf($sp)
/* 0CE384 800CD784 31CF0010 */  andi  $t7, $t6, 0x10
/* 0CE388 800CD788 11E00004 */  beqz  $t7, .L800CD79C
/* 0CE38C 800CD78C 00000000 */   nop   
/* 0CE390 800CD790 24180015 */  li    $t8, 21
/* 0CE394 800CD794 10000002 */  b     .L800CD7A0
/* 0CE398 800CD798 A3B8000E */   sb    $t8, 0xe($sp)
.L800CD79C:
/* 0CE39C 800CD79C A3A0000E */  sb    $zero, 0xe($sp)
.L800CD7A0:
/* 0CE3A0 800CD7A0 93B9000F */  lbu   $t9, 0xf($sp)
/* 0CE3A4 800CD7A4 30890400 */  andi  $t1, $a0, 0x400
/* 0CE3A8 800CD7A8 00194040 */  sll   $t0, $t9, 1
/* 0CE3AC 800CD7AC 11200003 */  beqz  $t1, .L800CD7BC
/* 0CE3B0 800CD7B0 A3A8000F */   sb    $t0, 0xf($sp)
/* 0CE3B4 800CD7B4 10000002 */  b     .L800CD7C0
/* 0CE3B8 800CD7B8 24050001 */   li    $a1, 1
.L800CD7BC:
/* 0CE3BC 800CD7BC 00002825 */  move  $a1, $zero
.L800CD7C0:
/* 0CE3C0 800CD7C0 93AA000F */  lbu   $t2, 0xf($sp)
/* 0CE3C4 800CD7C4 8FA80008 */  lw    $t0, 8($sp)
/* 0CE3C8 800CD7C8 93AF000E */  lbu   $t7, 0xe($sp)
/* 0CE3CC 800CD7CC 30AB00FF */  andi  $t3, $a1, 0xff
/* 0CE3D0 800CD7D0 00046840 */  sll   $t5, $a0, 1
/* 0CE3D4 800CD7D4 014B6025 */  or    $t4, $t2, $t3
/* 0CE3D8 800CD7D8 01A02025 */  move  $a0, $t5
/* 0CE3DC 800CD7DC 319800FF */  andi  $t8, $t4, 0xff
/* 0CE3E0 800CD7E0 25090001 */  addiu $t1, $t0, 1
/* 0CE3E4 800CD7E4 29210010 */  slti  $at, $t1, 0x10
/* 0CE3E8 800CD7E8 A3AC000F */  sb    $t4, 0xf($sp)
/* 0CE3EC 800CD7EC 308EFFFF */  andi  $t6, $a0, 0xffff
/* 0CE3F0 800CD7F0 030FC826 */  xor   $t9, $t8, $t7
/* 0CE3F4 800CD7F4 AFA90008 */  sw    $t1, 8($sp)
/* 0CE3F8 800CD7F8 01C02025 */  move  $a0, $t6
/* 0CE3FC 800CD7FC 1420FFE0 */  bnez  $at, .L800CD780
/* 0CE400 800CD800 A3B9000F */   sb    $t9, 0xf($sp)
/* 0CE404 800CD804 93A2000F */  lbu   $v0, 0xf($sp)
/* 0CE408 800CD808 27BD0010 */  addiu $sp, $sp, 0x10
/* 0CE40C 800CD80C 304A001F */  andi  $t2, $v0, 0x1f
/* 0CE410 800CD810 01401025 */  move  $v0, $t2
/* 0CE414 800CD814 304B00FF */  andi  $t3, $v0, 0xff
/* 0CE418 800CD818 03E00008 */  jr    $ra
/* 0CE41C 800CD81C 01601025 */   move  $v0, $t3

