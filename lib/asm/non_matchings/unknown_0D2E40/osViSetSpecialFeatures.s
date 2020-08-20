glabel osViSetSpecialFeatures
/* 0D2E60 800D2260 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D2E64 800D2264 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D2E68 800D2268 AFA40028 */  sw    $a0, 0x28($sp)
/* 0D2E6C 800D226C 0C034958 */  jal   __osDisableInt
/* 0D2E70 800D2270 AFB00018 */   sw    $s0, 0x18($sp)
/* 0D2E74 800D2274 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0D2E78 800D2278 00408025 */  move  $s0, $v0
/* 0D2E7C 800D227C 31CF0001 */  andi  $t7, $t6, 1
/* 0D2E80 800D2280 11E00006 */  beqz  $t7, .L800D229C
/* 0D2E84 800D2284 00000000 */   nop   
/* 0D2E88 800D2288 3C18800E */  lui   $t8, %hi(__osViNext) # $t8, 0x800e
/* 0D2E8C 800D228C 8F184874 */  lw    $t8, %lo(__osViNext)($t8)
/* 0D2E90 800D2290 8F19000C */  lw    $t9, 0xc($t8)
/* 0D2E94 800D2294 37280008 */  ori   $t0, $t9, 8
/* 0D2E98 800D2298 AF08000C */  sw    $t0, 0xc($t8)
.L800D229C:
/* 0D2E9C 800D229C 8FA90028 */  lw    $t1, 0x28($sp)
/* 0D2EA0 800D22A0 312A0002 */  andi  $t2, $t1, 2
/* 0D2EA4 800D22A4 11400007 */  beqz  $t2, .L800D22C4
/* 0D2EA8 800D22A8 00000000 */   nop   
/* 0D2EAC 800D22AC 3C0B800E */  lui   $t3, %hi(__osViNext) # $t3, 0x800e
/* 0D2EB0 800D22B0 8D6B4874 */  lw    $t3, %lo(__osViNext)($t3)
/* 0D2EB4 800D22B4 2401FFF7 */  li    $at, -9
/* 0D2EB8 800D22B8 8D6C000C */  lw    $t4, 0xc($t3)
/* 0D2EBC 800D22BC 01816824 */  and   $t5, $t4, $at
/* 0D2EC0 800D22C0 AD6D000C */  sw    $t5, 0xc($t3)
.L800D22C4:
/* 0D2EC4 800D22C4 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0D2EC8 800D22C8 31CF0004 */  andi  $t7, $t6, 4
/* 0D2ECC 800D22CC 11E00006 */  beqz  $t7, .L800D22E8
/* 0D2ED0 800D22D0 00000000 */   nop   
/* 0D2ED4 800D22D4 3C19800E */  lui   $t9, %hi(__osViNext) # $t9, 0x800e
/* 0D2ED8 800D22D8 8F394874 */  lw    $t9, %lo(__osViNext)($t9)
/* 0D2EDC 800D22DC 8F28000C */  lw    $t0, 0xc($t9)
/* 0D2EE0 800D22E0 35180004 */  ori   $t8, $t0, 4
/* 0D2EE4 800D22E4 AF38000C */  sw    $t8, 0xc($t9)
.L800D22E8:
/* 0D2EE8 800D22E8 8FA90028 */  lw    $t1, 0x28($sp)
/* 0D2EEC 800D22EC 312A0008 */  andi  $t2, $t1, 8
/* 0D2EF0 800D22F0 11400007 */  beqz  $t2, .L800D2310
/* 0D2EF4 800D22F4 00000000 */   nop   
/* 0D2EF8 800D22F8 3C0C800E */  lui   $t4, %hi(__osViNext) # $t4, 0x800e
/* 0D2EFC 800D22FC 8D8C4874 */  lw    $t4, %lo(__osViNext)($t4)
/* 0D2F00 800D2300 2401FFFB */  li    $at, -5
/* 0D2F04 800D2304 8D8D000C */  lw    $t5, 0xc($t4)
/* 0D2F08 800D2308 01A15824 */  and   $t3, $t5, $at
/* 0D2F0C 800D230C AD8B000C */  sw    $t3, 0xc($t4)
.L800D2310:
/* 0D2F10 800D2310 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0D2F14 800D2314 31CF0010 */  andi  $t7, $t6, 0x10
/* 0D2F18 800D2318 11E00006 */  beqz  $t7, .L800D2334
/* 0D2F1C 800D231C 00000000 */   nop   
/* 0D2F20 800D2320 3C08800E */  lui   $t0, %hi(__osViNext) # $t0, 0x800e
/* 0D2F24 800D2324 8D084874 */  lw    $t0, %lo(__osViNext)($t0)
/* 0D2F28 800D2328 8D18000C */  lw    $t8, 0xc($t0)
/* 0D2F2C 800D232C 37190010 */  ori   $t9, $t8, 0x10
/* 0D2F30 800D2330 AD19000C */  sw    $t9, 0xc($t0)
.L800D2334:
/* 0D2F34 800D2334 8FA90028 */  lw    $t1, 0x28($sp)
/* 0D2F38 800D2338 312A0020 */  andi  $t2, $t1, 0x20
/* 0D2F3C 800D233C 11400007 */  beqz  $t2, .L800D235C
/* 0D2F40 800D2340 00000000 */   nop   
/* 0D2F44 800D2344 3C0D800E */  lui   $t5, %hi(__osViNext) # $t5, 0x800e
/* 0D2F48 800D2348 8DAD4874 */  lw    $t5, %lo(__osViNext)($t5)
/* 0D2F4C 800D234C 2401FFEF */  li    $at, -17
/* 0D2F50 800D2350 8DAB000C */  lw    $t3, 0xc($t5)
/* 0D2F54 800D2354 01616024 */  and   $t4, $t3, $at
/* 0D2F58 800D2358 ADAC000C */  sw    $t4, 0xc($t5)
.L800D235C:
/* 0D2F5C 800D235C 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0D2F60 800D2360 31CF0040 */  andi  $t7, $t6, 0x40
/* 0D2F64 800D2364 11E0000D */  beqz  $t7, .L800D239C
/* 0D2F68 800D2368 00000000 */   nop   
/* 0D2F6C 800D236C 3C18800E */  lui   $t8, %hi(__osViNext) # $t8, 0x800e
/* 0D2F70 800D2370 8F184874 */  lw    $t8, %lo(__osViNext)($t8)
/* 0D2F74 800D2374 3C010001 */  lui   $at, 1
/* 0D2F78 800D2378 3C09800E */  lui   $t1, %hi(__osViNext) # $t1, 0x800e
/* 0D2F7C 800D237C 8F19000C */  lw    $t9, 0xc($t8)
/* 0D2F80 800D2380 03214025 */  or    $t0, $t9, $at
/* 0D2F84 800D2384 AF08000C */  sw    $t0, 0xc($t8)
/* 0D2F88 800D2388 8D294874 */  lw    $t1, %lo(__osViNext)($t1)
/* 0D2F8C 800D238C 2401FCFF */  li    $at, -769
/* 0D2F90 800D2390 8D2A000C */  lw    $t2, 0xc($t1)
/* 0D2F94 800D2394 01415824 */  and   $t3, $t2, $at
/* 0D2F98 800D2398 AD2B000C */  sw    $t3, 0xc($t1)
.L800D239C:
/* 0D2F9C 800D239C 8FAC0028 */  lw    $t4, 0x28($sp)
/* 0D2FA0 800D23A0 318D0080 */  andi  $t5, $t4, 0x80
/* 0D2FA4 800D23A4 11A00010 */  beqz  $t5, .L800D23E8
/* 0D2FA8 800D23A8 00000000 */   nop   
/* 0D2FAC 800D23AC 3C0E800E */  lui   $t6, %hi(__osViNext) # $t6, 0x800e
/* 0D2FB0 800D23B0 8DCE4874 */  lw    $t6, %lo(__osViNext)($t6)
/* 0D2FB4 800D23B4 3C01FFFE */  lui   $at, (0xFFFEFFFF >> 16) # lui $at, 0xfffe
/* 0D2FB8 800D23B8 3421FFFF */  ori   $at, (0xFFFEFFFF & 0xFFFF) # ori $at, $at, 0xffff
/* 0D2FBC 800D23BC 8DCF000C */  lw    $t7, 0xc($t6)
/* 0D2FC0 800D23C0 3C08800E */  lui   $t0, %hi(__osViNext) # $t0, 0x800e
/* 0D2FC4 800D23C4 01E1C824 */  and   $t9, $t7, $at
/* 0D2FC8 800D23C8 ADD9000C */  sw    $t9, 0xc($t6)
/* 0D2FCC 800D23CC 8D084874 */  lw    $t0, %lo(__osViNext)($t0)
/* 0D2FD0 800D23D0 8D0A0008 */  lw    $t2, 8($t0)
/* 0D2FD4 800D23D4 8D18000C */  lw    $t8, 0xc($t0)
/* 0D2FD8 800D23D8 8D4B0004 */  lw    $t3, 4($t2)
/* 0D2FDC 800D23DC 31690300 */  andi  $t1, $t3, 0x300
/* 0D2FE0 800D23E0 03096025 */  or    $t4, $t8, $t1
/* 0D2FE4 800D23E4 AD0C000C */  sw    $t4, 0xc($t0)
.L800D23E8:
/* 0D2FE8 800D23E8 3C0D800E */  lui   $t5, %hi(__osViNext) # $t5, 0x800e
/* 0D2FEC 800D23EC 8DAD4874 */  lw    $t5, %lo(__osViNext)($t5)
/* 0D2FF0 800D23F0 02002025 */  move  $a0, $s0
/* 0D2FF4 800D23F4 95AF0000 */  lhu   $t7, ($t5)
/* 0D2FF8 800D23F8 35F90008 */  ori   $t9, $t7, 8
/* 0D2FFC 800D23FC 0C034960 */  jal   __osRestoreInt
/* 0D3000 800D2400 A5B90000 */   sh    $t9, ($t5)
/* 0D3004 800D2404 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D3008 800D2408 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D300C 800D240C 27BD0028 */  addiu $sp, $sp, 0x28
/* 0D3010 800D2410 03E00008 */  jr    $ra
/* 0D3014 800D2414 00000000 */   nop   

/* 0D3018 800D2418 00000000 */  nop   
/* 0D301C 800D241C 00000000 */  nop   

