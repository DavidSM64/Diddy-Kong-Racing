glabel setupOSTasks
/* 078050 80077450 3C03800E */  lui   $v1, %hi(D_800DE4D4) # $v1, 0x800e
/* 078054 80077454 240E0001 */  li    $t6, 1
/* 078058 80077458 3C01800E */  lui   $at, %hi(D_800DE4DC) # $at, 0x800e
/* 07805C 8007745C 2463E4D4 */  addiu $v1, %lo(D_800DE4D4) # addiu $v1, $v1, -0x1b2c
/* 078060 80077460 AC2EE4DC */  sw    $t6, %lo(D_800DE4DC)($at)
/* 078064 80077464 8C620000 */  lw    $v0, ($v1)
/* 078068 80077468 3C188012 */  lui   $t8, %hi(D_80125F40) # $t8, 0x8012
/* 07806C 8007746C 000278C0 */  sll   $t7, $v0, 3
/* 078070 80077470 01E27823 */  subu  $t7, $t7, $v0
/* 078074 80077474 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 078078 80077478 000F7900 */  sll   $t7, $t7, 4
/* 07807C 8007747C 27185F40 */  addiu $t8, %lo(D_80125F40) # addiu $t8, $t8, 0x5f40
/* 078080 80077480 24010002 */  li    $at, 2
/* 078084 80077484 24590001 */  addiu $t9, $v0, 1
/* 078088 80077488 AFBF0014 */  sw    $ra, 0x14($sp)
/* 07808C 8007748C AFA60028 */  sw    $a2, 0x28($sp)
/* 078090 80077490 01F83821 */  addu  $a3, $t7, $t8
/* 078094 80077494 17210002 */  bne   $t9, $at, .L800774A0
/* 078098 80077498 AC790000 */   sw    $t9, ($v1)
/* 07809C 8007749C AC600000 */  sw    $zero, ($v1)
.L800774A0:
/* 0780A0 800774A0 00A45823 */  subu  $t3, $a1, $a0
/* 0780A4 800774A4 3C03800E */  lui   $v1, %hi(rspF3DDKRBootStart) # $v1, 0x800e
/* 0780A8 800774A8 3C0A8012 */  lui   $t2, %hi(D_80125ED8) # $t2, 0x8012
/* 0780AC 800774AC 000B60C3 */  sra   $t4, $t3, 3
/* 0780B0 800774B0 240D0001 */  li    $t5, 1
/* 0780B4 800774B4 3C0F800E */  lui   $t7, %hi(rspF3DDKRDramStart) # $t7, 0x800e
/* 0780B8 800774B8 246384C0 */  addiu $v1, %lo(rspF3DDKRBootStart) # addiu $v1, $v1, -0x7b40
/* 0780BC 800774BC 254A5ED8 */  addiu $t2, %lo(D_80125ED8) # addiu $t2, $t2, 0x5ed8
/* 0780C0 800774C0 ACEC0044 */  sw    $t4, 0x44($a3)
/* 0780C4 800774C4 ACED0010 */  sw    $t5, 0x10($a3)
/* 0780C8 800774C8 240E0002 */  li    $t6, 2
/* 0780CC 800774CC 25EF8590 */  addiu $t7, %lo(rspF3DDKRDramStart) # addiu $t7, $t7, -0x7a70
/* 0780D0 800774D0 3C02FF00 */  lui   $v0, (0xFF0000FF >> 16) # lui $v0, 0xff00
/* 0780D4 800774D4 24090023 */  li    $t1, 35
/* 0780D8 800774D8 ACEA0050 */  sw    $t2, 0x50($a3)
/* 0780DC 800774DC ACEE0014 */  sw    $t6, 0x14($a3)
/* 0780E0 800774E0 01E3C023 */  subu  $t8, $t7, $v1
/* 0780E4 800774E4 3C0C8012 */  lui   $t4, %hi(gGfxSPTaskYieldBuffer) # $t4, 0x8012
/* 0780E8 800774E8 3C0D8012 */  lui   $t5, %hi(D_80125EA0) # $t5, 0x8012
/* 0780EC 800774EC 344200FF */  ori   $v0, (0xFF0000FF & 0xFFFF) # ori $v0, $v0, 0xff
/* 0780F0 800774F0 ACE90008 */  sw    $t1, 8($a3)
/* 0780F4 800774F4 3C19800E */  lui   $t9, %hi(rspF3DDKRXbusStart) # $t9, 0x800e
/* 0780F8 800774F8 3C08800F */  lui   $t0, %hi(rspF3DDKRDataXbusStart) # $t0, 0x800f
/* 0780FC 800774FC 3C0A8012 */  lui   $t2, %hi(gDramStack) # $t2, 0x8012
/* 078100 80077500 258C46A0 */  addiu $t4, %lo(gGfxSPTaskYieldBuffer) # addiu $t4, $t4, 0x46a0
/* 078104 80077504 25AD5EA0 */  addiu $t5, %lo(D_80125EA0) # addiu $t5, $t5, 0x5ea0
/* 078108 80077508 3C0E8012 */  lui   $t6, %hi(D_801271B0) # $t6, 0x8012
/* 07810C 8007750C ACF8001C */  sw    $t8, 0x1c($a3)
/* 078110 80077510 2739A970 */  addiu $t9, %lo(rspF3DDKRXbusStart) # addiu $t9, $t9, -0x5690
/* 078114 80077514 2508ABA0 */  addiu $t0, %lo(rspF3DDKRDataXbusStart) # addiu $t0, $t0, -0x5460
/* 078118 80077518 24090800 */  li    $t1, 2048
/* 07811C 8007751C 254A42A0 */  addiu $t2, %lo(gDramStack) # addiu $t2, $t2, 0x42a0
/* 078120 80077520 240B0400 */  li    $t3, 1024
/* 078124 80077524 ACEC0038 */  sw    $t4, 0x38($a3)
/* 078128 80077528 ACED003C */  sw    $t5, 0x3c($a3)
/* 07812C 8007752C 25CE71B0 */  addiu $t6, %lo(D_801271B0) # addiu $t6, $t6, 0x71b0
/* 078130 80077530 240F0A00 */  li    $t7, 2560
/* 078134 80077534 ACE20058 */  sw    $v0, 0x58($a3)
/* 078138 80077538 ACE2005C */  sw    $v0, 0x5c($a3)
/* 07813C 8007753C ACE40040 */  sw    $a0, 0x40($a3)
/* 078140 80077540 ACE30018 */  sw    $v1, 0x18($a3)
/* 078144 80077544 ACF90020 */  sw    $t9, 0x20($a3)
/* 078148 80077548 ACE80028 */  sw    $t0, 0x28($a3)
/* 07814C 8007754C ACE9002C */  sw    $t1, 0x2c($a3)
/* 078150 80077550 ACEA0030 */  sw    $t2, 0x30($a3)
/* 078154 80077554 ACEB0034 */  sw    $t3, 0x34($a3)
/* 078158 80077558 ACEE0048 */  sw    $t6, 0x48($a3)
/* 07815C 8007755C ACEF004C */  sw    $t7, 0x4c($a3)
/* 078160 80077560 ACE00038 */  sw    $zero, 0x38($a3)
/* 078164 80077564 ACE0003C */  sw    $zero, 0x3c($a3)
/* 078168 80077568 ACE00000 */  sw    $zero, ($a3)
/* 07816C 8007756C 3C188012 */  lui   $t8, %hi(gVideoCurrFramebuffer) # $t8, 0x8012
/* 078170 80077570 8F1862D4 */  lw    $t8, %lo(gVideoCurrFramebuffer)($t8)
/* 078174 80077574 240200FF */  li    $v0, 255
/* 078178 80077578 ACE20060 */  sw    $v0, 0x60($a3)
/* 07817C 8007757C ACE20064 */  sw    $v0, 0x64($a3)
/* 078180 80077580 ACF8000C */  sw    $t8, 0xc($a3)
/* 078184 80077584 0C034628 */  jal   osWritebackDCacheAll
/* 078188 80077588 AFA7001C */   sw    $a3, 0x1c($sp)
/* 07818C 8007758C 3C048012 */  lui   $a0, %hi(osScInterruptQ) # $a0, 0x8012
/* 078190 80077590 8FA5001C */  lw    $a1, 0x1c($sp)
/* 078194 80077594 8C846100 */  lw    $a0, %lo(osScInterruptQ)($a0)
/* 078198 80077598 0C03238C */  jal   osSendMesg
/* 07819C 8007759C 24060001 */   li    $a2, 1
/* 0781A0 800775A0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0781A4 800775A4 27BD0020 */  addiu $sp, $sp, 0x20
/* 0781A8 800775A8 03E00008 */  jr    $ra
/* 0781AC 800775AC 00001025 */   move  $v0, $zero

