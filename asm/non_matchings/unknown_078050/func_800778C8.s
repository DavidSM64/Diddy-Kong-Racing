glabel func_800778C8
/* 0784C8 800778C8 3C03800E */  lui   $v1, %hi(D_800DE4D4) # $v1, 0x800e
/* 0784CC 800778CC 2463E4D4 */  addiu $v1, %lo(D_800DE4D4) # addiu $v1, $v1, -0x1b2c
/* 0784D0 800778D0 8C620000 */  lw    $v0, ($v1)
/* 0784D4 800778D4 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0784D8 800778D8 000270C0 */  sll   $t6, $v0, 3
/* 0784DC 800778DC 3C0F8012 */  lui   $t7, %hi(D_80125F40) # $t7, 0x8012
/* 0784E0 800778E0 01C27023 */  subu  $t6, $t6, $v0
/* 0784E4 800778E4 000E7100 */  sll   $t6, $t6, 4
/* 0784E8 800778E8 25EF5F40 */  addiu $t7, %lo(D_80125F40) # addiu $t7, $t7, 0x5f40
/* 0784EC 800778EC 24010003 */  li    $at, 3
/* 0784F0 800778F0 24580001 */  addiu $t8, $v0, 1
/* 0784F4 800778F4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0784F8 800778F8 AFA60030 */  sw    $a2, 0x30($sp)
/* 0784FC 800778FC AFA00020 */  sw    $zero, 0x20($sp)
/* 078500 80077900 01CF3821 */  addu  $a3, $t6, $t7
/* 078504 80077904 17010002 */  bne   $t8, $at, .L80077910
/* 078508 80077908 AC780000 */   sw    $t8, ($v1)
/* 07850C 8007790C AC600000 */  sw    $zero, ($v1)
.L80077910:
/* 078510 80077910 3C02800E */  lui   $v0, %hi(rspF3DDKRBootStart) # $v0, 0x800e
/* 078514 80077914 00A44023 */  subu  $t0, $a1, $a0
/* 078518 80077918 3C0D800E */  lui   $t5, %hi(rspF3DDKRDramStart) # $t5, 0x800e
/* 07851C 8007791C 244284C0 */  addiu $v0, %lo(rspF3DDKRBootStart) # addiu $v0, $v0, -0x7b40
/* 078520 80077920 000848C3 */  sra   $t1, $t0, 3
/* 078524 80077924 25AD8590 */  addiu $t5, %lo(rspF3DDKRDramStart) # addiu $t5, $t5, -0x7a70
/* 078528 80077928 3C0F800E */  lui   $t7, %hi(rspF3DDKRFifoStart) # $t7, 0x800e
/* 07852C 8007792C 3C18800F */  lui   $t8, %hi(rspF3DDKRDataFifoStart) # $t8, 0x800f
/* 078530 80077930 000950C0 */  sll   $t2, $t1, 3
/* 078534 80077934 240B0001 */  li    $t3, 1
/* 078538 80077938 240C0002 */  li    $t4, 2
/* 07853C 8007793C 01A27023 */  subu  $t6, $t5, $v0
/* 078540 80077940 25EF9790 */  addiu $t7, %lo(rspF3DDKRFifoStart) # addiu $t7, $t7, -0x6870
/* 078544 80077944 2718A3A0 */  addiu $t8, %lo(rspF3DDKRDataFifoStart) # addiu $t8, $t8, -0x5c60
/* 078548 80077948 ACEA0044 */  sw    $t2, 0x44($a3)
/* 07854C 8007794C ACEB0010 */  sw    $t3, 0x10($a3)
/* 078550 80077950 ACEC0014 */  sw    $t4, 0x14($a3)
/* 078554 80077954 ACEF0020 */  sw    $t7, 0x20($a3)
/* 078558 80077958 ACF80028 */  sw    $t8, 0x28($a3)
/* 07855C 8007795C ACEE001C */  sw    $t6, 0x1c($a3)
/* 078560 80077960 24190800 */  li    $t9, 2048
/* 078564 80077964 3C088012 */  lui   $t0, %hi(gDramStack) # $t0, 0x8012
/* 078568 80077968 3C0A8012 */  lui   $t2, %hi(gGfxSPTaskYieldBuffer) # $t2, 0x8012
/* 07856C 8007796C 3C0B8012 */  lui   $t3, %hi(D_80125EA0) # $t3, 0x8012
/* 078570 80077970 3C0C8012 */  lui   $t4, %hi(D_801271B0) # $t4, 0x8012
/* 078574 80077974 3C0F8012 */  lui   $t7, %hi(D_80125ED8) # $t7, 0x8012
/* 078578 80077978 3C18800E */  lui   $t8, %hi(D_800DE490) # $t8, 0x800e
/* 07857C 8007797C ACE20018 */  sw    $v0, 0x18($a3)
/* 078580 80077980 ACF9002C */  sw    $t9, 0x2c($a3)
/* 078584 80077984 250842A0 */  addiu $t0, %lo(gDramStack) # addiu $t0, $t0, 0x42a0
/* 078588 80077988 24090400 */  li    $t1, 1024
/* 07858C 8007798C 254A46A0 */  addiu $t2, %lo(gGfxSPTaskYieldBuffer) # addiu $t2, $t2, 0x46a0
/* 078590 80077990 256B5EA0 */  addiu $t3, %lo(D_80125EA0) # addiu $t3, $t3, 0x5ea0
/* 078594 80077994 258C71B0 */  addiu $t4, %lo(D_801271B0) # addiu $t4, $t4, 0x71b0
/* 078598 80077998 240D0A00 */  li    $t5, 2560
/* 07859C 8007799C 240E0007 */  li    $t6, 7
/* 0785A0 800779A0 25EF5ED8 */  addiu $t7, %lo(D_80125ED8) # addiu $t7, $t7, 0x5ed8
/* 0785A4 800779A4 2718E490 */  addiu $t8, %lo(D_800DE490) # addiu $t8, $t8, -0x1b70
/* 0785A8 800779A8 ACE40040 */  sw    $a0, 0x40($a3)
/* 0785AC 800779AC ACE80030 */  sw    $t0, 0x30($a3)
/* 0785B0 800779B0 ACE90034 */  sw    $t1, 0x34($a3)
/* 0785B4 800779B4 ACEA0038 */  sw    $t2, 0x38($a3)
/* 0785B8 800779B8 ACEB003C */  sw    $t3, 0x3c($a3)
/* 0785BC 800779BC ACEC0048 */  sw    $t4, 0x48($a3)
/* 0785C0 800779C0 ACED004C */  sw    $t5, 0x4c($a3)
/* 0785C4 800779C4 ACE00000 */  sw    $zero, ($a3)
/* 0785C8 800779C8 ACEE0008 */  sw    $t6, 8($a3)
/* 0785CC 800779CC ACEF0050 */  sw    $t7, 0x50($a3)
/* 0785D0 800779D0 ACF80054 */  sw    $t8, 0x54($a3)
/* 0785D4 800779D4 3C198012 */  lui   $t9, %hi(gVideoCurrFramebuffer) # $t9, 0x8012
/* 0785D8 800779D8 8F3962D4 */  lw    $t9, %lo(gVideoCurrFramebuffer)($t9)
/* 0785DC 800779DC 3C02FF00 */  lui   $v0, (0xFF0000FF >> 16) # lui $v0, 0xff00
/* 0785E0 800779E0 344200FF */  ori   $v0, (0xFF0000FF & 0xFFFF) # ori $v0, $v0, 0xff
/* 0785E4 800779E4 ACE20058 */  sw    $v0, 0x58($a3)
/* 0785E8 800779E8 ACE2005C */  sw    $v0, 0x5c($a3)
/* 0785EC 800779EC ACF9000C */  sw    $t9, 0xc($a3)
/* 0785F0 800779F0 8FA80030 */  lw    $t0, 0x30($sp)
/* 0785F4 800779F4 240200FF */  li    $v0, 255
/* 0785F8 800779F8 11000003 */  beqz  $t0, .L80077A08
/* 0785FC 800779FC 00000000 */   nop   
/* 078600 80077A00 ACE20060 */  sw    $v0, 0x60($a3)
/* 078604 80077A04 ACE20064 */  sw    $v0, 0x64($a3)
.L80077A08:
/* 078608 80077A08 ACE00068 */  sw    $zero, 0x68($a3)
/* 07860C 80077A0C 0C034628 */  jal   osWritebackDCacheAll
/* 078610 80077A10 AFA70024 */   sw    $a3, 0x24($sp)
/* 078614 80077A14 3C048012 */  lui   $a0, %hi(osScInterruptQ) # $a0, 0x8012
/* 078618 80077A18 8FA50024 */  lw    $a1, 0x24($sp)
/* 07861C 80077A1C 8C846100 */  lw    $a0, %lo(osScInterruptQ)($a0)
/* 078620 80077A20 0C03238C */  jal   osSendMesg
/* 078624 80077A24 24060001 */   li    $a2, 1
/* 078628 80077A28 8FA90030 */  lw    $t1, 0x30($sp)
/* 07862C 80077A2C 3C048012 */  lui   $a0, %hi(D_80125ED8) # $a0, 0x8012
/* 078630 80077A30 11200004 */  beqz  $t1, .L80077A44
/* 078634 80077A34 24845ED8 */   addiu $a0, %lo(D_80125ED8) # addiu $a0, $a0, 0x5ed8
/* 078638 80077A38 27A50020 */  addiu $a1, $sp, 0x20
/* 07863C 80077A3C 0C0322EC */  jal   osRecvMesg
/* 078640 80077A40 24060001 */   li    $a2, 1
.L80077A44:
/* 078644 80077A44 8FBF0014 */  lw    $ra, 0x14($sp)
/* 078648 80077A48 27BD0028 */  addiu $sp, $sp, 0x28
/* 07864C 80077A4C 03E00008 */  jr    $ra
/* 078650 80077A50 00000000 */   nop   

