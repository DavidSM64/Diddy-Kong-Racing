glabel __osDispatchThread
/* 0D4024 800D3424 3C04800E */  lui   $a0, %hi(__osRunQueue) # $a0, 0x800e
/* 0D4028 800D3428 0C034D05 */  jal   __osPopThread
/* 0D402C 800D342C 24844888 */   addiu $a0, %lo(__osRunQueue) # addiu $a0, $a0, 0x4888
/* 0D4030 800D3430 3C01800E */  lui   $at, %hi(__osRunningThread) # $at, 0x800e
/* 0D4034 800D3434 AC224890 */  sw    $v0, %lo(__osRunningThread)($at)
/* 0D4038 800D3438 24080004 */  li    $t0, 4
/* 0D403C 800D343C A4480010 */  sh    $t0, 0x10($v0)
/* 0D4040 800D3440 0040D025 */  move  $k0, $v0
/* 0D4044 800D3444 3C08800E */  lui   $t0, %hi(__OSGlobalIntMask) # $t0, 0x800e
/* 0D4048 800D3448 8F5B0118 */  lw    $k1, 0x118($k0)
/* 0D404C 800D344C 250838AC */  addiu $t0, %lo(__OSGlobalIntMask) # addiu $t0, $t0, 0x38ac
/* 0D4050 800D3450 8D080000 */  lw    $t0, ($t0)
/* 0D4054 800D3454 3C01FFFF */  lui   $at, (0xFFFF00FF >> 16) # lui $at, 0xffff
/* 0D4058 800D3458 3369FF00 */  andi  $t1, $k1, 0xff00
/* 0D405C 800D345C 342100FF */  ori   $at, (0xFFFF00FF & 0xFFFF) # ori $at, $at, 0xff
/* 0D4060 800D3460 3108FF00 */  andi  $t0, $t0, 0xff00
/* 0D4064 800D3464 01284824 */  and   $t1, $t1, $t0
/* 0D4068 800D3468 0361D824 */  and   $k1, $k1, $at
/* 0D406C 800D346C 0369D825 */  or    $k1, $k1, $t1
/* 0D4070 800D3470 409B6000 */  mtc0  $k1, $12
/* 0D4074 800D3474 DF5B0108 */  ld    $k1, 0x108($k0)
/* 0D4078 800D3478 DF410020 */  ld    $at, 0x20($k0)
/* 0D407C 800D347C DF420028 */  ld    $v0, 0x28($k0)
/* 0D4080 800D3480 03600013 */  mtlo  $k1
/* 0D4084 800D3484 DF5B0110 */  ld    $k1, 0x110($k0)
/* 0D4088 800D3488 DF430030 */  ld    $v1, 0x30($k0)
/* 0D408C 800D348C DF440038 */  ld    $a0, 0x38($k0)
/* 0D4090 800D3490 DF450040 */  ld    $a1, 0x40($k0)
/* 0D4094 800D3494 DF460048 */  ld    $a2, 0x48($k0)
/* 0D4098 800D3498 DF470050 */  ld    $a3, 0x50($k0)
/* 0D409C 800D349C DF480058 */  ld    $t0, 0x58($k0)
/* 0D40A0 800D34A0 DF490060 */  ld    $t1, 0x60($k0)
/* 0D40A4 800D34A4 DF4A0068 */  ld    $t2, 0x68($k0)
/* 0D40A8 800D34A8 DF4B0070 */  ld    $t3, 0x70($k0)
/* 0D40AC 800D34AC DF4C0078 */  ld    $t4, 0x78($k0)
/* 0D40B0 800D34B0 DF4D0080 */  ld    $t5, 0x80($k0)
/* 0D40B4 800D34B4 DF4E0088 */  ld    $t6, 0x88($k0)
/* 0D40B8 800D34B8 DF4F0090 */  ld    $t7, 0x90($k0)
/* 0D40BC 800D34BC DF500098 */  ld    $s0, 0x98($k0)
/* 0D40C0 800D34C0 DF5100A0 */  ld    $s1, 0xa0($k0)
/* 0D40C4 800D34C4 DF5200A8 */  ld    $s2, 0xa8($k0)
/* 0D40C8 800D34C8 DF5300B0 */  ld    $s3, 0xb0($k0)
/* 0D40CC 800D34CC DF5400B8 */  ld    $s4, 0xb8($k0)
/* 0D40D0 800D34D0 DF5500C0 */  ld    $s5, 0xc0($k0)
/* 0D40D4 800D34D4 DF5600C8 */  ld    $s6, 0xc8($k0)
/* 0D40D8 800D34D8 DF5700D0 */  ld    $s7, 0xd0($k0)
/* 0D40DC 800D34DC DF5800D8 */  ld    $t8, 0xd8($k0)
/* 0D40E0 800D34E0 DF5900E0 */  ld    $t9, 0xe0($k0)
/* 0D40E4 800D34E4 DF5C00E8 */  ld    $gp, 0xe8($k0)
/* 0D40E8 800D34E8 03600011 */  mthi  $k1
/* 0D40EC 800D34EC DF5D00F0 */  ld    $sp, 0xf0($k0)
/* 0D40F0 800D34F0 DF5E00F8 */  ld    $fp, 0xf8($k0)
/* 0D40F4 800D34F4 DF5F0100 */  ld    $ra, 0x100($k0)
/* 0D40F8 800D34F8 8F5B011C */  lw    $k1, 0x11c($k0)
/* 0D40FC 800D34FC 409B7000 */  mtc0  $k1, $14
/* 0D4100 800D3500 8F5B0018 */  lw    $k1, 0x18($k0)
/* 0D4104 800D3504 13600013 */  beqz  $k1, .L800D3554
/* 0D4108 800D3508 00000000 */   nop   
/* 0D410C 800D350C 8F5B012C */  lw    $k1, 0x12c($k0)
/* 0D4110 800D3510 44DBF800 */  ctc1  $k1, $31
/* 0D4114 800D3514 D7400130 */  ldc1  $f0, 0x130($k0)
/* 0D4118 800D3518 D7420138 */  ldc1  $f2, 0x138($k0)
/* 0D411C 800D351C D7440140 */  ldc1  $f4, 0x140($k0)
/* 0D4120 800D3520 D7460148 */  ldc1  $f6, 0x148($k0)
/* 0D4124 800D3524 D7480150 */  ldc1  $f8, 0x150($k0)
/* 0D4128 800D3528 D74A0158 */  ldc1  $f10, 0x158($k0)
/* 0D412C 800D352C D74C0160 */  ldc1  $f12, 0x160($k0)
/* 0D4130 800D3530 D74E0168 */  ldc1  $f14, 0x168($k0)
/* 0D4134 800D3534 D7500170 */  ldc1  $f16, 0x170($k0)
/* 0D4138 800D3538 D7520178 */  ldc1  $f18, 0x178($k0)
/* 0D413C 800D353C D7540180 */  ldc1  $f20, 0x180($k0)
/* 0D4140 800D3540 D7560188 */  ldc1  $f22, 0x188($k0)
/* 0D4144 800D3544 D7580190 */  ldc1  $f24, 0x190($k0)
/* 0D4148 800D3548 D75A0198 */  ldc1  $f26, 0x198($k0)
/* 0D414C 800D354C D75C01A0 */  ldc1  $f28, 0x1a0($k0)
/* 0D4150 800D3550 D75E01A8 */  ldc1  $f30, 0x1a8($k0)
.L800D3554:
/* 0D4154 800D3554 8F5B0128 */  lw    $k1, 0x128($k0)
/* 0D4158 800D3558 3C1A800E */  lui   $k0, %hi(__OSGlobalIntMask) # $k0, 0x800e
/* 0D415C 800D355C 275A38AC */  addiu $k0, %lo(__OSGlobalIntMask) # addiu $k0, $k0, 0x38ac
/* 0D4160 800D3560 8F5A0000 */  lw    $k0, ($k0)
/* 0D4164 800D3564 001AD402 */  srl   $k0, $k0, 0x10
/* 0D4168 800D3568 037AD824 */  and   $k1, $k1, $k0
/* 0D416C 800D356C 001BD840 */  sll   $k1, $k1, 1
/* 0D4170 800D3570 3C1A800F */  lui   $k0, %hi(__osRcpImTable) # $k0, 0x800f
/* 0D4174 800D3574 275A94D0 */  addiu $k0, %lo(__osRcpImTable) # addiu $k0, $k0, -0x6b30
/* 0D4178 800D3578 037AD821 */  addu  $k1, $k1, $k0
/* 0D417C 800D357C 977B0000 */  lhu   $k1, ($k1)
/* 0D4180 800D3580 3C1AA430 */  lui   $k0, %hi(MI_INTR_MASK_REG) # $k0, 0xa430
/* 0D4184 800D3584 275A000C */  addiu $k0, %lo(MI_INTR_MASK_REG) # addiu $k0, $k0, 0xc
/* 0D4188 800D3588 AF5B0000 */  sw    $k1, ($k0)
/* 0D418C 800D358C 00000000 */  nop   
/* 0D4190 800D3590 00000000 */  nop   
/* 0D4194 800D3594 00000000 */  nop   
/* 0D4198 800D3598 00000000 */  nop   
/* 0D419C 800D359C 42000018 */  eret  
