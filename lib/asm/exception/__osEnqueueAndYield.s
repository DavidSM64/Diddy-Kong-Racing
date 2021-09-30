glabel __osEnqueueAndYield
/* 0D3ECC 800D32CC 3C05800E */  lui   $a1, %hi(__osRunningThread) # $a1, 0x800e
/* 0D3ED0 800D32D0 8CA54890 */  lw    $a1, %lo(__osRunningThread)($a1)
/* 0D3ED4 800D32D4 40086000 */  mfc0  $t0, $12
/* 0D3ED8 800D32D8 8CBB0018 */  lw    $k1, 0x18($a1)
/* 0D3EDC 800D32DC 35080002 */  ori   $t0, $t0, 2
/* 0D3EE0 800D32E0 ACA80118 */  sw    $t0, 0x118($a1)
/* 0D3EE4 800D32E4 FCB00098 */  sd    $s0, 0x98($a1)
/* 0D3EE8 800D32E8 FCB100A0 */  sd    $s1, 0xa0($a1)
/* 0D3EEC 800D32EC FCB200A8 */  sd    $s2, 0xa8($a1)
/* 0D3EF0 800D32F0 FCB300B0 */  sd    $s3, 0xb0($a1)
/* 0D3EF4 800D32F4 FCB400B8 */  sd    $s4, 0xb8($a1)
/* 0D3EF8 800D32F8 FCB500C0 */  sd    $s5, 0xc0($a1)
/* 0D3EFC 800D32FC FCB600C8 */  sd    $s6, 0xc8($a1)
/* 0D3F00 800D3300 FCB700D0 */  sd    $s7, 0xd0($a1)
/* 0D3F04 800D3304 FCBC00E8 */  sd    $gp, 0xe8($a1)
/* 0D3F08 800D3308 FCBD00F0 */  sd    $sp, 0xf0($a1)
/* 0D3F0C 800D330C FCBE00F8 */  sd    $fp, 0xf8($a1)
/* 0D3F10 800D3310 FCBF0100 */  sd    $ra, 0x100($a1)
/* 0D3F14 800D3314 13600009 */  beqz  $k1, .L800D333C
/* 0D3F18 800D3318 ACBF011C */   sw    $ra, 0x11c($a1)
/* 0D3F1C 800D331C 445BF800 */  cfc1  $k1, $31
/* 0D3F20 800D3320 F4B40180 */  sdc1  $f20, 0x180($a1)
/* 0D3F24 800D3324 F4B60188 */  sdc1  $f22, 0x188($a1)
/* 0D3F28 800D3328 F4B80190 */  sdc1  $f24, 0x190($a1)
/* 0D3F2C 800D332C F4BA0198 */  sdc1  $f26, 0x198($a1)
/* 0D3F30 800D3330 F4BC01A0 */  sdc1  $f28, 0x1a0($a1)
/* 0D3F34 800D3334 F4BE01A8 */  sdc1  $f30, 0x1a8($a1)
/* 0D3F38 800D3338 ACBB012C */  sw    $k1, 0x12c($a1)
.L800D333C:
/* 0D3F3C 800D333C 8CBB0118 */  lw    $k1, 0x118($a1)
/* 0D3F40 800D3340 3369FF00 */  andi  $t1, $k1, 0xff00
/* 0D3F44 800D3344 1120000D */  beqz  $t1, .L800D337C
/* 0D3F48 800D3348 00000000 */   nop   
/* 0D3F4C 800D334C 3C08800E */  lui   $t0, %hi(__OSGlobalIntMask) # $t0, 0x800e
/* 0D3F50 800D3350 250838AC */  addiu $t0, %lo(__OSGlobalIntMask) # addiu $t0, $t0, 0x38ac
/* 0D3F54 800D3354 8D080000 */  lw    $t0, ($t0)
/* 0D3F58 800D3358 2401FFFF */  li    $at, -1
/* 0D3F5C 800D335C 01014026 */  xor   $t0, $t0, $at
/* 0D3F60 800D3360 3C01FFFF */  lui   $at, (0xFFFF00FF >> 16) # lui $at, 0xffff
/* 0D3F64 800D3364 3108FF00 */  andi  $t0, $t0, 0xff00
/* 0D3F68 800D3368 342100FF */  ori   $at, (0xFFFF00FF & 0xFFFF) # ori $at, $at, 0xff
/* 0D3F6C 800D336C 01284825 */  or    $t1, $t1, $t0
/* 0D3F70 800D3370 0361D824 */  and   $k1, $k1, $at
/* 0D3F74 800D3374 0369D825 */  or    $k1, $k1, $t1
/* 0D3F78 800D3378 ACBB0118 */  sw    $k1, 0x118($a1)
.L800D337C:
/* 0D3F7C 800D337C 3C1BA430 */  lui   $k1, %hi(MI_INTR_MASK_REG) # $k1, 0xa430
/* 0D3F80 800D3380 8F7B000C */  lw    $k1, %lo(MI_INTR_MASK_REG)($k1)
/* 0D3F84 800D3384 1360000B */  beqz  $k1, .L800D33B4
/* 0D3F88 800D3388 00000000 */   nop   
/* 0D3F8C 800D338C 3C1A800E */  lui   $k0, %hi(__OSGlobalIntMask) # $k0, 0x800e
/* 0D3F90 800D3390 275A38AC */  addiu $k0, %lo(__OSGlobalIntMask) # addiu $k0, $k0, 0x38ac
/* 0D3F94 800D3394 8F5A0000 */  lw    $k0, ($k0)
/* 0D3F98 800D3398 8CA80128 */  lw    $t0, 0x128($a1)
/* 0D3F9C 800D339C 2401FFFF */  li    $at, -1
/* 0D3FA0 800D33A0 001AD402 */  srl   $k0, $k0, 0x10
/* 0D3FA4 800D33A4 0341D026 */  xor   $k0, $k0, $at
/* 0D3FA8 800D33A8 335A003F */  andi  $k0, $k0, 0x3f
/* 0D3FAC 800D33AC 0348D024 */  and   $k0, $k0, $t0
/* 0D3FB0 800D33B0 037AD825 */  or    $k1, $k1, $k0
.L800D33B4:
/* 0D3FB4 800D33B4 10800003 */  beqz  $a0, .L800D33C4
/* 0D3FB8 800D33B8 ACBB0128 */   sw    $k1, 0x128($a1)
/* 0D3FBC 800D33BC 0C034CF3 */  jal   __osEnqueueThread
/* 0D3FC0 800D33C0 00000000 */   nop   
.L800D33C4:
/* 0D3FC4 800D33C4 08034D09 */  j     __osDispatchThread
/* 0D3FC8 800D33C8 00000000 */   nop   

