glabel menu_game_select_init
/* 08D108 8008C508 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08D10C 8008C50C 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 08D110 8008C510 AC20F47C */  sw    $zero, %lo(gMenuDelay)($at)
/* 08D114 8008C514 3C018012 */  lui   $at, %hi(D_801263BC) # $at, 0x8012
/* 08D118 8008C518 AFB40028 */  sw    $s4, 0x28($sp)
/* 08D11C 8008C51C AC2063BC */  sw    $zero, %lo(D_801263BC)($at)
/* 08D120 8008C520 3C148012 */  lui   $s4, %hi(D_801263E0) # $s4, 0x8012
/* 08D124 8008C524 3C01800E */  lui   $at, %hi(D_800DF460) # $at, 0x800e
/* 08D128 8008C528 269463E0 */  addiu $s4, %lo(D_801263E0) # addiu $s4, $s4, 0x63e0
/* 08D12C 8008C52C AFBF002C */  sw    $ra, 0x2c($sp)
/* 08D130 8008C530 AC20F460 */  sw    $zero, %lo(D_800DF460)($at)
/* 08D134 8008C534 240E0002 */  li    $t6, 2
/* 08D138 8008C538 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeOut) # $a0, 0x800e
/* 08D13C 8008C53C AFB30024 */  sw    $s3, 0x24($sp)
/* 08D140 8008C540 AFB20020 */  sw    $s2, 0x20($sp)
/* 08D144 8008C544 AFB1001C */  sw    $s1, 0x1c($sp)
/* 08D148 8008C548 AFB00018 */  sw    $s0, 0x18($sp)
/* 08D14C 8008C54C AE8E0000 */  sw    $t6, ($s4)
/* 08D150 8008C550 0C030076 */  jal   func_800C01D8
/* 08D154 8008C554 2484F77C */   addiu $a0, %lo(sMenuTransitionFadeOut) # addiu $a0, $a0, -0x884
/* 08D158 8008C558 0C01BAEA */  jal   func_8006EBA8
/* 08D15C 8008C55C 00000000 */   nop   
/* 08D160 8008C560 0C006DE4 */  jal   func_8001B790
/* 08D164 8008C564 00000000 */   nop   
/* 08D168 8008C568 240F0001 */  li    $t7, 1
/* 08D16C 8008C56C 3C018012 */  lui   $at, %hi(D_801263D8) # $at, 0x8012
/* 08D170 8008C570 AC2F63D8 */  sw    $t7, %lo(D_801263D8)($at)
/* 08D174 8008C574 0C0271B5 */  jal   func_8009C6D4
/* 08D178 8008C578 24040043 */   li    $a0, 67
/* 08D17C 8008C57C 0C01FFFB */  jal   func_8007FFEC
/* 08D180 8008C580 24040003 */   li    $a0, 3
/* 08D184 8008C584 0C03105C */  jal   load_font
/* 08D188 8008C588 24040002 */   li    $a0, 2
/* 08D18C 8008C58C 0C0002CD */  jal   play_music
/* 08D190 8008C590 2404001A */   li    $a0, 26
/* 08D194 8008C594 3C13800E */  lui   $s3, %hi(D_800DFDB4) # $s3, 0x800e
/* 08D198 8008C598 3C128012 */  lui   $s2, %hi(D_801263B4) # $s2, 0x8012
/* 08D19C 8008C59C 265263B4 */  addiu $s2, %lo(D_801263B4) # addiu $s2, $s2, 0x63b4
/* 08D1A0 8008C5A0 2673FDB4 */  addiu $s3, %lo(D_800DFDB4) # addiu $s3, $s3, -0x24c
/* 08D1A4 8008C5A4 00008025 */  move  $s0, $zero
.L8008C5A8:
/* 08D1A8 8008C5A8 82580000 */  lb    $t8, ($s2)
/* 08D1AC 8008C5AC 0010C840 */  sll   $t9, $s0, 1
/* 08D1B0 8008C5B0 12180007 */  beq   $s0, $t8, .L8008C5D0
/* 08D1B4 8008C5B4 02798821 */   addu  $s1, $s3, $t9
/* 08D1B8 8008C5B8 92240000 */  lbu   $a0, ($s1)
/* 08D1BC 8008C5BC 0C000445 */  jal   func_80001114
/* 08D1C0 8008C5C0 00000000 */   nop   
/* 08D1C4 8008C5C4 92240001 */  lbu   $a0, 1($s1)
/* 08D1C8 8008C5C8 0C000445 */  jal   func_80001114
/* 08D1CC 8008C5CC 00000000 */   nop   
.L8008C5D0:
/* 08D1D0 8008C5D0 26100001 */  addiu $s0, $s0, 1
/* 08D1D4 8008C5D4 2A01000A */  slti  $at, $s0, 0xa
/* 08D1D8 8008C5D8 1420FFF3 */  bnez  $at, .L8008C5A8
/* 08D1DC 8008C5DC 00000000 */   nop   
/* 08D1E0 8008C5E0 0C000445 */  jal   func_80001114
/* 08D1E4 8008C5E4 24040006 */   li    $a0, 6
/* 08D1E8 8008C5E8 0C0002C6 */  jal   func_80000B18
/* 08D1EC 8008C5EC 00000000 */   nop   
/* 08D1F0 8008C5F0 0C027B18 */  jal   is_adventure_two_unlocked
/* 08D1F4 8008C5F4 00000000 */   nop   
/* 08D1F8 8008C5F8 10400009 */  beqz  $v0, .L8008C620
/* 08D1FC 8008C5FC 3C038012 */   lui   $v1, %hi(D_80126460) # $v1, 0x8012
/* 08D200 8008C600 3C038012 */  lui   $v1, %hi(D_80126460) # $v1, 0x8012
/* 08D204 8008C604 3C08800E */  lui   $t0, %hi(gGameSelectTextElemsWithAdv2) # $t0, 0x800e
/* 08D208 8008C608 24636460 */  addiu $v1, %lo(D_80126460) # addiu $v1, $v1, 0x6460
/* 08D20C 8008C60C 25080278 */  addiu $t0, %lo(gGameSelectTextElemsWithAdv2) # addiu $t0, $t0, 0x278
/* 08D210 8008C610 24090002 */  li    $t1, 2
/* 08D214 8008C614 AC680000 */  sw    $t0, ($v1)
/* 08D218 8008C618 10000007 */  b     .L8008C638
/* 08D21C 8008C61C AE890000 */   sw    $t1, ($s4)
.L8008C620:
/* 08D220 8008C620 3C0A800E */  lui   $t2, %hi(gGameSelectTextElemsNoAdv2) # $t2, 0x800e
/* 08D224 8008C624 24636460 */  addiu $v1, %lo(D_80126460) # addiu $v1, $v1, 0x6460
/* 08D228 8008C628 254A0198 */  addiu $t2, %lo(gGameSelectTextElemsNoAdv2) # addiu $t2, $t2, 0x198
/* 08D22C 8008C62C 240B0001 */  li    $t3, 1
/* 08D230 8008C630 AC6A0000 */  sw    $t2, ($v1)
/* 08D234 8008C634 AE8B0000 */  sw    $t3, ($s4)
.L8008C638:
/* 08D238 8008C638 8E8C0000 */  lw    $t4, ($s4)
/* 08D23C 8008C63C 00008025 */  move  $s0, $zero
/* 08D240 8008C640 0580000D */  bltz  $t4, .L8008C678
/* 08D244 8008C644 3C028012 */   lui   $v0, %hi(D_80126550) # $v0, 0x8012
/* 08D248 8008C648 24426550 */  addiu $v0, %lo(D_80126550) # addiu $v0, $v0, 0x6550
.L8008C64C:
/* 08D24C 8008C64C 8C6E0000 */  lw    $t6, ($v1)
/* 08D250 8008C650 02007825 */  move  $t7, $s0
/* 08D254 8008C654 8C4D010C */  lw    $t5, 0x10c($v0)
/* 08D258 8008C658 000FC180 */  sll   $t8, $t7, 6
/* 08D25C 8008C65C 01D8C821 */  addu  $t9, $t6, $t8
/* 08D260 8008C660 AF2D0054 */  sw    $t5, 0x54($t9)
/* 08D264 8008C664 8E880000 */  lw    $t0, ($s4)
/* 08D268 8008C668 26100001 */  addiu $s0, $s0, 1
/* 08D26C 8008C66C 0110082A */  slt   $at, $t0, $s0
/* 08D270 8008C670 1020FFF6 */  beqz  $at, .L8008C64C
/* 08D274 8008C674 00000000 */   nop   
.L8008C678:
/* 08D278 8008C678 8FBF002C */  lw    $ra, 0x2c($sp)
/* 08D27C 8008C67C 8FB00018 */  lw    $s0, 0x18($sp)
/* 08D280 8008C680 8FB1001C */  lw    $s1, 0x1c($sp)
/* 08D284 8008C684 8FB20020 */  lw    $s2, 0x20($sp)
/* 08D288 8008C688 8FB30024 */  lw    $s3, 0x24($sp)
/* 08D28C 8008C68C 8FB40028 */  lw    $s4, 0x28($sp)
/* 08D290 8008C690 03E00008 */  jr    $ra
/* 08D294 8008C694 27BD0030 */   addiu $sp, $sp, 0x30

