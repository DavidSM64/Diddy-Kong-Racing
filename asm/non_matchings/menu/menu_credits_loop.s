.late_rodata
glabel jpt_800E8574
.word L8009BA98, L8009BAD8, L8009BB08, L8009BB48, L8009BB9C

.text
glabel menu_credits_loop
/* 09BF2C 8009B32C 27BDFF78 */  addiu $sp, $sp, -0x88
/* 09BF30 8009B330 AFBF0054 */  sw    $ra, 0x54($sp)
/* 09BF34 8009B334 AFA40088 */  sw    $a0, 0x88($sp)
/* 09BF38 8009B338 AFBE0050 */  sw    $fp, 0x50($sp)
/* 09BF3C 8009B33C AFB7004C */  sw    $s7, 0x4c($sp)
/* 09BF40 8009B340 AFB60048 */  sw    $s6, 0x48($sp)
/* 09BF44 8009B344 AFB50044 */  sw    $s5, 0x44($sp)
/* 09BF48 8009B348 AFB40040 */  sw    $s4, 0x40($sp)
/* 09BF4C 8009B34C AFB3003C */  sw    $s3, 0x3c($sp)
/* 09BF50 8009B350 AFB20038 */  sw    $s2, 0x38($sp)
/* 09BF54 8009B354 AFB10034 */  sw    $s1, 0x34($sp)
/* 09BF58 8009B358 AFB00030 */  sw    $s0, 0x30($sp)
/* 09BF5C 8009B35C E7B50028 */  swc1  $f21, 0x28($sp)
/* 09BF60 8009B360 E7B4002C */  swc1  $f20, 0x2c($sp)
/* 09BF64 8009B364 AFA00068 */  sw    $zero, 0x68($sp)
/* 09BF68 8009B368 0C0078A7 */  jal   get_misc_asset
/* 09BF6C 8009B36C 2404001C */   li    $a0, 28
/* 09BF70 8009B370 AFA2005C */  sw    $v0, 0x5c($sp)
/* 09BF74 8009B374 0C0078A7 */  jal   get_misc_asset
/* 09BF78 8009B378 24040045 */   li    $a0, 69
/* 09BF7C 8009B37C 0C031CFC */  jal   tick_thread30
/* 09BF80 8009B380 AFA20060 */   sw    $v0, 0x60($sp)
/* 09BF84 8009B384 3C0E800E */  lui   $t6, %hi(gMenuDelay) # $t6, 0x800e
/* 09BF88 8009B388 8DCEF47C */  lw    $t6, %lo(gMenuDelay)($t6)
/* 09BF8C 8009B38C 00000000 */  nop   
/* 09BF90 8009B390 15C00007 */  bnez  $t6, .L8009B3B0
/* 09BF94 8009B394 00000000 */   nop   
/* 09BF98 8009B398 0C030060 */  jal   disable_new_screen_transitions
/* 09BF9C 8009B39C 00000000 */   nop   
/* 09BFA0 8009B3A0 0C030076 */  jal   transition_begin
/* 09BFA4 8009B3A4 00002025 */   move  $a0, $zero
/* 09BFA8 8009B3A8 0C03005C */  jal   enable_new_screen_transitions
/* 09BFAC 8009B3AC 00000000 */   nop   
.L8009B3B0:
/* 09BFB0 8009B3B0 3C0F8000 */  lui   $t7, %hi(osTvType) # $t7, 0x8000
/* 09BFB4 8009B3B4 8DEF0300 */  lw    $t7, %lo(osTvType)($t7)
/* 09BFB8 8009B3B8 00002025 */  move  $a0, $zero
/* 09BFBC 8009B3BC 15E0000C */  bnez  $t7, .L8009B3F0
/* 09BFC0 8009B3C0 24050028 */   li    $a1, 40
/* 09BFC4 8009B3C4 3C188012 */  lui   $t8, %hi(gOpacityDecayTimer) # $t8, 0x8012
/* 09BFC8 8009B3C8 8F1863D8 */  lw    $t8, %lo(gOpacityDecayTimer)($t8)
/* 09BFCC 8009B3CC 00002025 */  move  $a0, $zero
/* 09BFD0 8009B3D0 0018C8C0 */  sll   $t9, $t8, 3
/* 09BFD4 8009B3D4 AFB90010 */  sw    $t9, 0x10($sp)
/* 09BFD8 8009B3D8 24050026 */  li    $a1, 38
/* 09BFDC 8009B3DC 24060140 */  li    $a2, 320
/* 09BFE0 8009B3E0 0C026C79 */  jal   render_credits_fade
/* 09BFE4 8009B3E4 240700BA */   li    $a3, 186
/* 09BFE8 8009B3E8 10000008 */  b     .L8009B40C
/* 09BFEC 8009B3EC 00000000 */   nop   
.L8009B3F0:
/* 09BFF0 8009B3F0 3C098012 */  lui   $t1, %hi(gOpacityDecayTimer) # $t1, 0x8012
/* 09BFF4 8009B3F4 8D2963D8 */  lw    $t1, %lo(gOpacityDecayTimer)($t1)
/* 09BFF8 8009B3F8 24060140 */  li    $a2, 320
/* 09BFFC 8009B3FC 000950C0 */  sll   $t2, $t1, 3
/* 09C000 8009B400 AFAA0010 */  sw    $t2, 0x10($sp)
/* 09C004 8009B404 0C026C79 */  jal   render_credits_fade
/* 09C008 8009B408 2407009C */   li    $a3, 156
.L8009B40C:
/* 09C00C 8009B40C 3C068012 */  lui   $a2, %hi(gOpacityDecayTimer) # $a2, 0x8012
/* 09C010 8009B410 24C663D8 */  addiu $a2, %lo(gOpacityDecayTimer) # addiu $a2, $a2, 0x63d8
/* 09C014 8009B414 8CC20000 */  lw    $v0, ($a2)
/* 09C018 8009B418 3C03800E */  lui   $v1, %hi(gMenuCurIndex) # $v1, 0x800e
/* 09C01C 8009B41C 18400041 */  blez  $v0, .L8009B524
/* 09C020 8009B420 2463F460 */   addiu $v1, %lo(gMenuCurIndex) # addiu $v1, $v1, -0xba0
/* 09C024 8009B424 8FAC0088 */  lw    $t4, 0x88($sp)
/* 09C028 8009B428 8C6B0000 */  lw    $t3, ($v1)
/* 09C02C 8009B42C 000C6A00 */  sll   $t5, $t4, 8
/* 09C030 8009B430 28410028 */  slti  $at, $v0, 0x28
/* 09C034 8009B434 016D7021 */  addu  $t6, $t3, $t5
/* 09C038 8009B438 14200003 */  bnez  $at, .L8009B448
/* 09C03C 8009B43C AC6E0000 */   sw    $t6, ($v1)
/* 09C040 8009B440 10000003 */  b     .L8009B450
/* 09C044 8009B444 0000A025 */   move  $s4, $zero
.L8009B448:
/* 09C048 8009B448 240F0028 */  li    $t7, 40
/* 09C04C 8009B44C 01E2A023 */  subu  $s4, $t7, $v0
.L8009B450:
/* 09C050 8009B450 0014C080 */  sll   $t8, $s4, 2
/* 09C054 8009B454 0314C021 */  addu  $t8, $t8, $s4
/* 09C058 8009B458 8C750000 */  lw    $s5, ($v1)
/* 09C05C 8009B45C 0C01E948 */  jal   get_video_width_and_height_as_s32
/* 09C060 8009B460 27140048 */   addiu $s4, $t8, 0x48
/* 09C064 8009B464 00029443 */  sra   $s2, $v0, 0x11
/* 09C068 8009B468 32597FFF */  andi  $t9, $s2, 0x7fff
/* 09C06C 8009B46C 3C10800E */  lui   $s0, %hi(gRacerPortraits) # $s0, 0x800e
/* 09C070 8009B470 3C178012 */  lui   $s7, %hi(sMenuCurrDisplayList) # $s7, 0x8012
/* 09C074 8009B474 3C16800E */  lui   $s6, %hi(unused_800E0B18) # $s6, 0x800e
/* 09C078 8009B478 03209025 */  move  $s2, $t9
/* 09C07C 8009B47C 26D60B18 */  addiu $s6, %lo(unused_800E0B18) # addiu $s6, $s6, 0xb18
/* 09C080 8009B480 26F763A0 */  addiu $s7, %lo(sMenuCurrDisplayList) # addiu $s7, $s7, 0x63a0
/* 09C084 8009B484 26100AF0 */  addiu $s0, %lo(gRacerPortraits) # addiu $s0, $s0, 0xaf0
.L8009B488:
/* 09C088 8009B488 00158C00 */  sll   $s1, $s5, 0x10
/* 09C08C 8009B48C 00114C03 */  sra   $t1, $s1, 0x10
/* 09C090 8009B490 00092400 */  sll   $a0, $t1, 0x10
/* 09C094 8009B494 00045403 */  sra   $t2, $a0, 0x10
/* 09C098 8009B498 01402025 */  move  $a0, $t2
/* 09C09C 8009B49C 0C01C20C */  jal   sins
/* 09C0A0 8009B4A0 01208825 */   move  $s1, $t1
/* 09C0A4 8009B4A4 00112400 */  sll   $a0, $s1, 0x10
/* 09C0A8 8009B4A8 00046403 */  sra   $t4, $a0, 0x10
/* 09C0AC 8009B4AC 01802025 */  move  $a0, $t4
/* 09C0B0 8009B4B0 0C01C20B */  jal   coss
/* 09C0B4 8009B4B4 00409825 */   move  $s3, $v0
/* 09C0B8 8009B4B8 02740019 */  multu $s3, $s4
/* 09C0BC 8009B4BC 8E050000 */  lw    $a1, ($s0)
/* 09C0C0 8009B4C0 240F00FF */  li    $t7, 255
/* 09C0C4 8009B4C4 241800FF */  li    $t8, 255
/* 09C0C8 8009B4C8 241900FF */  li    $t9, 255
/* 09C0CC 8009B4CC 240900FF */  li    $t1, 255
/* 09C0D0 8009B4D0 AFA9001C */  sw    $t1, 0x1c($sp)
/* 09C0D4 8009B4D4 AFB90018 */  sw    $t9, 0x18($sp)
/* 09C0D8 8009B4D8 AFB80014 */  sw    $t8, 0x14($sp)
/* 09C0DC 8009B4DC AFAF0010 */  sw    $t7, 0x10($sp)
/* 09C0E0 8009B4E0 02E02025 */  move  $a0, $s7
/* 09C0E4 8009B4E4 00003012 */  mflo  $a2
/* 09C0E8 8009B4E8 00065C03 */  sra   $t3, $a2, 0x10
/* 09C0EC 8009B4EC 2566008C */  addiu $a2, $t3, 0x8c
/* 09C0F0 8009B4F0 00540019 */  multu $v0, $s4
/* 09C0F4 8009B4F4 00006812 */  mflo  $t5
/* 09C0F8 8009B4F8 000D7403 */  sra   $t6, $t5, 0x10
/* 09C0FC 8009B4FC 01D23821 */  addu  $a3, $t6, $s2
/* 09C100 8009B500 0C01E2AE */  jal   render_textured_rectangle
/* 09C104 8009B504 24E7FFEC */   addiu $a3, $a3, -0x14
/* 09C108 8009B508 26100004 */  addiu $s0, $s0, 4
/* 09C10C 8009B50C 1616FFDE */  bne   $s0, $s6, .L8009B488
/* 09C110 8009B510 26B51999 */   addiu $s5, $s5, 0x1999
/* 09C114 8009B514 0C01ECF4 */  jal   reset_render_settings
/* 09C118 8009B518 02E02025 */   move  $a0, $s7
/* 09C11C 8009B51C 3C068012 */  lui   $a2, %hi(gOpacityDecayTimer) # $a2, 0x8012
/* 09C120 8009B520 24C663D8 */  addiu $a2, %lo(gOpacityDecayTimer) # addiu $a2, $a2, 0x63d8
.L8009B524:
/* 09C124 8009B524 3C0A8012 */  lui   $t2, %hi(D_80126BE0) # $t2, 0x8012
/* 09C128 8009B528 8D4A6BE0 */  lw    $t2, %lo(D_80126BE0)($t2)
/* 09C12C 8009B52C 8FA40088 */  lw    $a0, 0x88($sp)
/* 09C130 8009B530 11400008 */  beqz  $t2, .L8009B554
/* 09C134 8009B534 00000000 */   nop   
/* 09C138 8009B538 0C0207D3 */  jal   func_80081F4C
/* 09C13C 8009B53C 00000000 */   nop   
/* 09C140 8009B540 2C4C0001 */  sltiu $t4, $v0, 1
/* 09C144 8009B544 3C018012 */  lui   $at, %hi(D_80126BE0) # $at, 0x8012
/* 09C148 8009B548 3C068012 */  lui   $a2, %hi(gOpacityDecayTimer) # $a2, 0x8012
/* 09C14C 8009B54C 24C663D8 */  addiu $a2, %lo(gOpacityDecayTimer) # addiu $a2, $a2, 0x63d8
/* 09C150 8009B550 AC2C6BE0 */  sw    $t4, %lo(D_80126BE0)($at)
.L8009B554:
/* 09C154 8009B554 3C0B8012 */  lui   $t3, %hi(D_80126BD8) # $t3, 0x8012
/* 09C158 8009B558 8D6B6BD8 */  lw    $t3, %lo(D_80126BD8)($t3)
/* 09C15C 8009B55C 3C0D8012 */  lui   $t5, %hi(D_80126BE0) # $t5, 0x8012
/* 09C160 8009B560 15600130 */  bnez  $t3, .L8009BA24
/* 09C164 8009B564 00000000 */   nop   
/* 09C168 8009B568 8DAD6BE0 */  lw    $t5, %lo(D_80126BE0)($t5)
/* 09C16C 8009B56C 3C013F00 */  li    $at, 0x3F000000 # 0.500000
/* 09C170 8009B570 15A0012C */  bnez  $t5, .L8009BA24
/* 09C174 8009B574 3C168012 */   lui   $s6, %hi(D_80126BC4) # $s6, 0x8012
/* 09C178 8009B578 3C1E800E */  lui   $fp, %hi(gCreditsControlData) # $fp, 0x800e
/* 09C17C 8009B57C 3C08800E */  lui   $t0, %hi(gCreditsArray) # $t0, 0x800e
/* 09C180 8009B580 4481A000 */  mtc1  $at, $f20
/* 09C184 8009B584 AFA0006C */  sw    $zero, 0x6c($sp)
/* 09C188 8009B588 25081938 */  addiu $t0, %lo(gCreditsArray) # addiu $t0, $t0, 0x1938
/* 09C18C 8009B58C 27DE17F4 */  addiu $fp, %lo(gCreditsControlData) # addiu $fp, $fp, 0x17f4
/* 09C190 8009B590 26D66BC4 */  addiu $s6, %lo(D_80126BC4) # addiu $s6, $s6, 0x6bc4
/* 09C194 8009B594 24076000 */  li    $a3, 24576
.L8009B598:
/* 09C198 8009B598 8EC50000 */  lw    $a1, ($s6)
/* 09C19C 8009B59C 24011000 */  li    $at, 4096
/* 09C1A0 8009B5A0 00057040 */  sll   $t6, $a1, 1
/* 09C1A4 8009B5A4 03CE7821 */  addu  $t7, $fp, $t6
/* 09C1A8 8009B5A8 85E40000 */  lh    $a0, ($t7)
/* 09C1AC 8009B5AC 24090001 */  li    $t1, 1
/* 09C1B0 8009B5B0 3082F000 */  andi  $v0, $a0, 0xf000
/* 09C1B4 8009B5B4 00E23026 */  xor   $a2, $a3, $v0
/* 09C1B8 8009B5B8 2CC60001 */  sltiu $a2, $a2, 1
/* 09C1BC 8009B5BC 0006C600 */  sll   $t8, $a2, 0x18
/* 09C1C0 8009B5C0 10410011 */  beq   $v0, $at, .L8009B608
/* 09C1C4 8009B5C4 00183603 */   sra   $a2, $t8, 0x18
/* 09C1C8 8009B5C8 24012000 */  li    $at, 8192
/* 09C1CC 8009B5CC 10410013 */  beq   $v0, $at, .L8009B61C
/* 09C1D0 8009B5D0 24B00001 */   addiu $s0, $a1, 1
/* 09C1D4 8009B5D4 24013000 */  li    $at, 12288
/* 09C1D8 8009B5D8 104100AC */  beq   $v0, $at, .L8009B88C
/* 09C1DC 8009B5DC 24190001 */   li    $t9, 1
/* 09C1E0 8009B5E0 24014000 */  li    $at, 16384
/* 09C1E4 8009B5E4 10410101 */  beq   $v0, $at, .L8009B9EC
/* 09C1E8 8009B5E8 24AB0001 */   addiu $t3, $a1, 1
/* 09C1EC 8009B5EC 24015000 */  li    $at, 20480
/* 09C1F0 8009B5F0 10410105 */  beq   $v0, $at, .L8009BA08
/* 09C1F4 8009B5F4 24AF0001 */   addiu $t7, $a1, 1
/* 09C1F8 8009B5F8 10470009 */  beq   $v0, $a3, .L8009B620
/* 09C1FC 8009B5FC 3C01FFFF */   lui   $at, 0xffff
/* 09C200 8009B600 10000103 */  b     .L8009BA10
/* 09C204 8009B604 8FB8006C */   lw    $t8, 0x6c($sp)
.L8009B608:
/* 09C208 8009B608 AEC00000 */  sw    $zero, ($s6)
/* 09C20C 8009B60C 3C018012 */  lui   $at, %hi(gIgnorePlayerInputTime) # $at, 0x8012
/* 09C210 8009B610 AFA90068 */  sw    $t1, 0x68($sp)
/* 09C214 8009B614 100000FD */  b     .L8009BA0C
/* 09C218 8009B618 AC2063C4 */   sw    $zero, %lo(gIgnorePlayerInputTime)($at)
.L8009B61C:
/* 09C21C 8009B61C 3C01FFFF */  lui   $at, (0xFFFF0FFF >> 16) # lui $at, 0xffff
.L8009B620:
/* 09C220 8009B620 34210FFF */  ori   $at, (0xFFFF0FFF & 0xFFFF) # ori $at, $at, 0xfff
/* 09C224 8009B624 00815024 */  and   $t2, $a0, $at
/* 09C228 8009B628 3C018012 */  lui   $at, %hi(D_80126BE8) # $at, 0x8012
/* 09C22C 8009B62C 00105840 */  sll   $t3, $s0, 1
/* 09C230 8009B630 AC2A6BE8 */  sw    $t2, %lo(D_80126BE8)($at)
/* 09C234 8009B634 03CB6821 */  addu  $t5, $fp, $t3
/* 09C238 8009B638 85A20000 */  lh    $v0, ($t5)
/* 09C23C 8009B63C 240F0001 */  li    $t7, 1
/* 09C240 8009B640 304EF000 */  andi  $t6, $v0, 0xf000
/* 09C244 8009B644 AED00000 */  sw    $s0, ($s6)
/* 09C248 8009B648 02002825 */  move  $a1, $s0
/* 09C24C 8009B64C 01C01025 */  move  $v0, $t6
/* 09C250 8009B650 AFAF006C */  sw    $t7, 0x6c($sp)
/* 09C254 8009B654 0000A825 */  move  $s5, $zero
/* 09C258 8009B658 24170014 */  li    $s7, 20
/* 09C25C 8009B65C 15C0000A */  bnez  $t6, .L8009B688
/* 09C260 8009B660 00009825 */   move  $s3, $zero
.L8009B664:
/* 09C264 8009B664 24B80001 */  addiu $t8, $a1, 1
/* 09C268 8009B668 0018C840 */  sll   $t9, $t8, 1
/* 09C26C 8009B66C 03D94821 */  addu  $t1, $fp, $t9
/* 09C270 8009B670 85220000 */  lh    $v0, ($t1)
/* 09C274 8009B674 AED80000 */  sw    $t8, ($s6)
/* 09C278 8009B678 304AF000 */  andi  $t2, $v0, 0xf000
/* 09C27C 8009B67C 01401025 */  move  $v0, $t2
/* 09C280 8009B680 1140FFF8 */  beqz  $t2, .L8009B664
/* 09C284 8009B684 03002825 */   move  $a1, $t8
.L8009B688:
/* 09C288 8009B688 3C0C8000 */  lui   $t4, %hi(osTvType) # $t4, 0x8000
/* 09C28C 8009B68C 8D8C0300 */  lw    $t4, %lo(osTvType)($t4)
/* 09C290 8009B690 00B01823 */  subu  $v1, $a1, $s0
/* 09C294 8009B694 15800003 */  bnez  $t4, .L8009B6A4
/* 09C298 8009B698 24010001 */   li    $at, 1
/* 09C29C 8009B69C 10000002 */  b     .L8009B6A8
/* 09C2A0 8009B6A0 24120086 */   li    $s2, 134
.L8009B6A4:
/* 09C2A4 8009B6A4 24120078 */  li    $s2, 120
.L8009B6A8:
/* 09C2A8 8009B6A8 14610004 */  bne   $v1, $at, .L8009B6BC
/* 09C2AC 8009B6AC 240E01E0 */   li    $t6, 480
/* 09C2B0 8009B6B0 2652FFF2 */  addiu $s2, $s2, -0xe
/* 09C2B4 8009B6B4 1000000A */  b     .L8009B6E0
/* 09C2B8 8009B6B8 24150002 */   li    $s5, 2
.L8009B6BC:
/* 09C2BC 8009B6BC 10C00006 */  beqz  $a2, .L8009B6D8
/* 09C2C0 8009B6C0 00036900 */   sll   $t5, $v1, 4
/* 09C2C4 8009B6C4 00035900 */  sll   $t3, $v1, 4
/* 09C2C8 8009B6C8 024B9023 */  subu  $s2, $s2, $t3
/* 09C2CC 8009B6CC 26520003 */  addiu $s2, $s2, 3
/* 09C2D0 8009B6D0 10000003 */  b     .L8009B6E0
/* 09C2D4 8009B6D4 24170020 */   li    $s7, 32
.L8009B6D8:
/* 09C2D8 8009B6D8 024D9023 */  subu  $s2, $s2, $t5
/* 09C2DC 8009B6DC 26520008 */  addiu $s2, $s2, 8
.L8009B6E0:
/* 09C2E0 8009B6E0 3C01800E */  lui   $at, %hi(gCreditsMenuElements) # $at, 0x800e
/* 09C2E4 8009B6E4 A42E1B50 */  sh    $t6, %lo(gCreditsMenuElements)($at)
/* 09C2E8 8009B6E8 24013000 */  li    $at, 12288
/* 09C2EC 8009B6EC 14410005 */  bne   $v0, $at, .L8009B704
/* 09C2F0 8009B6F0 2418FF60 */   li    $t8, -160
/* 09C2F4 8009B6F4 240F00A0 */  li    $t7, 160
/* 09C2F8 8009B6F8 3C01800E */  lui   $at, %hi(gCreditsMenuElements+8) # $at, 0x800e
/* 09C2FC 8009B6FC 10000003 */  b     .L8009B70C
/* 09C300 8009B700 A42F1B58 */   sh    $t7, %lo(gCreditsMenuElements+8)($at)
.L8009B704:
/* 09C304 8009B704 3C01800E */  lui   $at, %hi(gCreditsMenuElements+8) # $at, 0x800e
/* 09C308 8009B708 A4381B58 */  sh    $t8, %lo(gCreditsMenuElements+8)($at)
.L8009B70C:
/* 09C30C 8009B70C 0205082A */  slt   $at, $s0, $a1
/* 09C310 8009B710 10200042 */  beqz  $at, .L8009B81C
/* 09C314 8009B714 0200A025 */   move  $s4, $s0
/* 09C318 8009B718 3C10800E */  lui   $s0, %hi(gCreditsMenuElements) # $s0, 0x800e
/* 09C31C 8009B71C 0014C840 */  sll   $t9, $s4, 1
/* 09C320 8009B720 03D98821 */  addu  $s1, $fp, $t9
/* 09C324 8009B724 26101B50 */  addiu $s0, %lo(gCreditsMenuElements) # addiu $s0, $s0, 0x1b50
.L8009B728:
/* 09C328 8009B728 A6120002 */  sh    $s2, 2($s0)
/* 09C32C 8009B72C A6120006 */  sh    $s2, 6($s0)
/* 09C330 8009B730 10C00023 */  beqz  $a2, .L8009B7C0
/* 09C334 8009B734 A612000A */   sh    $s2, 0xa($s0)
/* 09C338 8009B738 862A0000 */  lh    $t2, ($s1)
/* 09C33C 8009B73C 8FAC005C */  lw    $t4, 0x5c($sp)
/* 09C340 8009B740 24090030 */  li    $t1, 48
/* 09C344 8009B744 A2000011 */  sb    $zero, 0x11($s0)
/* 09C348 8009B748 A200000D */  sb    $zero, 0xd($s0)
/* 09C34C 8009B74C A209000F */  sb    $t1, 0xf($s0)
/* 09C350 8009B750 014C5821 */  addu  $t3, $t2, $t4
/* 09C354 8009B754 81640000 */  lb    $a0, ($t3)
/* 09C358 8009B758 A3A6005B */  sb    $a2, 0x5b($sp)
/* 09C35C 8009B75C 0C01AF77 */  jal   get_level_name
/* 09C360 8009B760 24150002 */   li    $s5, 2
/* 09C364 8009B764 862D0000 */  lh    $t5, ($s1)
/* 09C368 8009B768 2643000E */  addiu $v1, $s2, 0xe
/* 09C36C 8009B76C 3C0F800E */  lui   $t7, %hi(gCreditsBestTimesArray) # $t7, 0x800e
/* 09C370 8009B770 000D7080 */  sll   $t6, $t5, 2
/* 09C374 8009B774 8EC50000 */  lw    $a1, ($s6)
/* 09C378 8009B778 AE020014 */  sw    $v0, 0x14($s0)
/* 09C37C 8009B77C A6030022 */  sh    $v1, 0x22($s0)
/* 09C380 8009B780 A6030026 */  sh    $v1, 0x26($s0)
/* 09C384 8009B784 A603002A */  sh    $v1, 0x2a($s0)
/* 09C388 8009B788 A2000031 */  sb    $zero, 0x31($s0)
/* 09C38C 8009B78C 01EE7821 */  addu  $t7, $t7, $t6
/* 09C390 8009B790 8DEF1A94 */  lw    $t7, %lo(gCreditsBestTimesArray)($t7)
/* 09C394 8009B794 3C19800E */  lui   $t9, %hi(gCreditsControlData) # $t9, 0x800e
/* 09C398 8009B798 83A6005B */  lb    $a2, 0x5b($sp)
/* 09C39C 8009B79C 3C08800E */  lui   $t0, %hi(gCreditsArray) # $t0, 0x800e
/* 09C3A0 8009B7A0 273917F4 */  addiu $t9, %lo(gCreditsControlData) # addiu $t9, $t9, 0x17f4
/* 09C3A4 8009B7A4 0005C040 */  sll   $t8, $a1, 1
/* 09C3A8 8009B7A8 25081938 */  addiu $t0, %lo(gCreditsArray) # addiu $t0, $t0, 0x1938
/* 09C3AC 8009B7AC 03192021 */  addu  $a0, $t8, $t9
/* 09C3B0 8009B7B0 26730002 */  addiu $s3, $s3, 2
/* 09C3B4 8009B7B4 26100040 */  addiu $s0, $s0, 0x40
/* 09C3B8 8009B7B8 10000013 */  b     .L8009B808
/* 09C3BC 8009B7BC AE0FFFF4 */   sw    $t7, -0xc($s0)
.L8009B7C0:
/* 09C3C0 8009B7C0 3C0A800E */  lui   $t2, %hi(gCreditsControlData) # $t2, 0x800e
/* 09C3C4 8009B7C4 254A17F4 */  addiu $t2, %lo(gCreditsControlData) # addiu $t2, $t2, 0x17f4
/* 09C3C8 8009B7C8 00054840 */  sll   $t1, $a1, 1
/* 09C3CC 8009B7CC 326C0001 */  andi  $t4, $s3, 1
/* 09C3D0 8009B7D0 11800004 */  beqz  $t4, .L8009B7E4
/* 09C3D4 8009B7D4 012A2021 */   addu  $a0, $t1, $t2
/* 09C3D8 8009B7D8 240B00FF */  li    $t3, 255
/* 09C3DC 8009B7DC A20B000D */  sb    $t3, 0xd($s0)
/* 09C3E0 8009B7E0 A200000F */  sb    $zero, 0xf($s0)
.L8009B7E4:
/* 09C3E4 8009B7E4 862D0000 */  lh    $t5, ($s1)
/* 09C3E8 8009B7E8 A2150011 */  sb    $s5, 0x11($s0)
/* 09C3EC 8009B7EC 000D7080 */  sll   $t6, $t5, 2
/* 09C3F0 8009B7F0 010E7821 */  addu  $t7, $t0, $t6
/* 09C3F4 8009B7F4 8DF80000 */  lw    $t8, ($t7)
/* 09C3F8 8009B7F8 24150002 */  li    $s5, 2
/* 09C3FC 8009B7FC 26730001 */  addiu $s3, $s3, 1
/* 09C400 8009B800 26100020 */  addiu $s0, $s0, 0x20
/* 09C404 8009B804 AE18FFF4 */  sw    $t8, -0xc($s0)
.L8009B808:
/* 09C408 8009B808 26310002 */  addiu $s1, $s1, 2
/* 09C40C 8009B80C 0224082B */  sltu  $at, $s1, $a0
/* 09C410 8009B810 02579021 */  addu  $s2, $s2, $s7
/* 09C414 8009B814 1420FFC4 */  bnez  $at, .L8009B728
/* 09C418 8009B818 24170020 */   li    $s7, 32
.L8009B81C:
/* 09C41C 8009B81C 3C04800E */  lui   $a0, %hi(gCreditsMenuElements) # $a0, 0x800e
/* 09C420 8009B820 24841B50 */  addiu $a0, %lo(gCreditsMenuElements) # addiu $a0, $a0, 0x1b50
/* 09C424 8009B824 0013C940 */  sll   $t9, $s3, 5
/* 09C428 8009B828 00994821 */  addu  $t1, $a0, $t9
/* 09C42C 8009B82C AD200014 */  sw    $zero, 0x14($t1)
/* 09C430 8009B830 3C0A8012 */  lui   $t2, %hi(D_80126BE8) # $t2, 0x8012
/* 09C434 8009B834 8D4A6BE8 */  lw    $t2, %lo(D_80126BE8)($t2)
/* 09C438 8009B838 3C014270 */  li    $at, 0x42700000 # 60.000000
/* 09C43C 8009B83C 448A2000 */  mtc1  $t2, $f4
/* 09C440 8009B840 44814000 */  mtc1  $at, $f8
/* 09C444 8009B844 468021A0 */  cvt.s.w $f6, $f4
/* 09C448 8009B848 4405A000 */  mfc1  $a1, $f20
/* 09C44C 8009B84C 4407A000 */  mfc1  $a3, $f20
/* 09C450 8009B850 46083283 */  div.s $f10, $f6, $f8
/* 09C454 8009B854 AFA00014 */  sw    $zero, 0x14($sp)
/* 09C458 8009B858 AFA00010 */  sw    $zero, 0x10($sp)
/* 09C45C 8009B85C 44065000 */  mfc1  $a2, $f10
/* 09C460 8009B860 0C020795 */  jal   func_80081E54
/* 09C464 8009B864 00000000 */   nop   
/* 09C468 8009B868 0C0207D3 */  jal   func_80081F4C
/* 09C46C 8009B86C 00002025 */   move  $a0, $zero
/* 09C470 8009B870 3C08800E */  lui   $t0, %hi(gCreditsArray) # $t0, 0x800e
/* 09C474 8009B874 2C4C0001 */  sltiu $t4, $v0, 1
/* 09C478 8009B878 3C018012 */  lui   $at, %hi(D_80126BE0) # $at, 0x8012
/* 09C47C 8009B87C AC2C6BE0 */  sw    $t4, %lo(D_80126BE0)($at)
/* 09C480 8009B880 25081938 */  addiu $t0, %lo(gCreditsArray) # addiu $t0, $t0, 0x1938
/* 09C484 8009B884 10000061 */  b     .L8009BA0C
/* 09C488 8009B888 24076000 */   li    $a3, 24576
.L8009B88C:
/* 09C48C 8009B88C 3C01FFFF */  lui   $at, (0xFFFF0FFF >> 16) # lui $at, 0xffff
/* 09C490 8009B890 34210FFF */  ori   $at, (0xFFFF0FFF & 0xFFFF) # ori $at, $at, 0xfff
/* 09C494 8009B894 00815824 */  and   $t3, $a0, $at
/* 09C498 8009B898 24B00001 */  addiu $s0, $a1, 1
/* 09C49C 8009B89C 3C018012 */  lui   $at, %hi(D_80126BE8) # $at, 0x8012
/* 09C4A0 8009B8A0 00107040 */  sll   $t6, $s0, 1
/* 09C4A4 8009B8A4 AC2B6BE8 */  sw    $t3, %lo(D_80126BE8)($at)
/* 09C4A8 8009B8A8 03CE7821 */  addu  $t7, $fp, $t6
/* 09C4AC 8009B8AC 85E20000 */  lh    $v0, ($t7)
/* 09C4B0 8009B8B0 AED00000 */  sw    $s0, ($s6)
/* 09C4B4 8009B8B4 3058F000 */  andi  $t8, $v0, 0xf000
/* 09C4B8 8009B8B8 02002825 */  move  $a1, $s0
/* 09C4BC 8009B8BC 03001025 */  move  $v0, $t8
/* 09C4C0 8009B8C0 1700000A */  bnez  $t8, .L8009B8EC
/* 09C4C4 8009B8C4 AFB9006C */   sw    $t9, 0x6c($sp)
.L8009B8C8:
/* 09C4C8 8009B8C8 24A90001 */  addiu $t1, $a1, 1
/* 09C4CC 8009B8CC 00095040 */  sll   $t2, $t1, 1
/* 09C4D0 8009B8D0 03CA6021 */  addu  $t4, $fp, $t2
/* 09C4D4 8009B8D4 85820000 */  lh    $v0, ($t4)
/* 09C4D8 8009B8D8 AEC90000 */  sw    $t1, ($s6)
/* 09C4DC 8009B8DC 304BF000 */  andi  $t3, $v0, 0xf000
/* 09C4E0 8009B8E0 01601025 */  move  $v0, $t3
/* 09C4E4 8009B8E4 1160FFF8 */  beqz  $t3, .L8009B8C8
/* 09C4E8 8009B8E8 01202825 */   move  $a1, $t1
.L8009B8EC:
/* 09C4EC 8009B8EC 3C03800E */  lui   $v1, %hi(gCreditsMenuElements) # $v1, 0x800e
/* 09C4F0 8009B8F0 24631B50 */  addiu $v1, %lo(gCreditsMenuElements) # addiu $v1, $v1, 0x1b50
/* 09C4F4 8009B8F4 240400A0 */  li    $a0, 160
/* 09C4F8 8009B8F8 24013000 */  li    $at, 12288
/* 09C4FC 8009B8FC 14410003 */  bne   $v0, $at, .L8009B90C
/* 09C500 8009B900 A4640000 */   sh    $a0, ($v1)
/* 09C504 8009B904 10000003 */  b     .L8009B914
/* 09C508 8009B908 A4640008 */   sh    $a0, 8($v1)
.L8009B90C:
/* 09C50C 8009B90C 240DFF60 */  li    $t5, -160
/* 09C510 8009B910 A46D0008 */  sh    $t5, 8($v1)
.L8009B914:
/* 09C514 8009B914 0205082A */  slt   $at, $s0, $a1
/* 09C518 8009B918 10200014 */  beqz  $at, .L8009B96C
/* 09C51C 8009B91C 0200A025 */   move  $s4, $s0
/* 09C520 8009B920 0010C140 */  sll   $t8, $s0, 5
/* 09C524 8009B924 0018C823 */  negu  $t9, $t8
/* 09C528 8009B928 00147940 */  sll   $t7, $s4, 5
/* 09C52C 8009B92C 3C0A800E */  lui   $t2, %hi(gCreditsMenuElements) # $t2, 0x800e
/* 09C530 8009B930 254A1B50 */  addiu $t2, %lo(gCreditsMenuElements) # addiu $t2, $t2, 0x1b50
/* 09C534 8009B934 01F94821 */  addu  $t1, $t7, $t9
/* 09C538 8009B938 00147040 */  sll   $t6, $s4, 1
/* 09C53C 8009B93C 03CE8821 */  addu  $s1, $fp, $t6
/* 09C540 8009B940 012A1021 */  addu  $v0, $t1, $t2
.L8009B944:
/* 09C544 8009B944 862C0000 */  lh    $t4, ($s1)
/* 09C548 8009B948 26940001 */  addiu $s4, $s4, 1
/* 09C54C 8009B94C 000C5880 */  sll   $t3, $t4, 2
/* 09C550 8009B950 010B6821 */  addu  $t5, $t0, $t3
/* 09C554 8009B954 8DAE0000 */  lw    $t6, ($t5)
/* 09C558 8009B958 0285082A */  slt   $at, $s4, $a1
/* 09C55C 8009B95C 26310002 */  addiu $s1, $s1, 2
/* 09C560 8009B960 24420020 */  addiu $v0, $v0, 0x20
/* 09C564 8009B964 1420FFF7 */  bnez  $at, .L8009B944
/* 09C568 8009B968 AC4E0014 */   sw    $t6, 0x14($v0)
.L8009B96C:
/* 09C56C 8009B96C 00107940 */  sll   $t7, $s0, 5
/* 09C570 8009B970 3C0A8012 */  lui   $t2, %hi(D_80126BE8) # $t2, 0x8012
/* 09C574 8009B974 8D4A6BE8 */  lw    $t2, %lo(D_80126BE8)($t2)
/* 09C578 8009B978 000FC823 */  negu  $t9, $t7
/* 09C57C 8009B97C 0014C140 */  sll   $t8, $s4, 5
/* 09C580 8009B980 03194821 */  addu  $t1, $t8, $t9
# Setting gCreditsMenuElements[1].source? Not sure why adding $t1 then
/* 09C584 8009B984 3C01800E */  lui   $at, %hi(gCreditsMenuElements+0x34)
/* 09C588 8009B988 448A8000 */  mtc1  $t2, $f16
/* 09C58C 8009B98C 00290821 */  addu  $at, $at, $t1
/* 09C590 8009B990 AC201B84 */  sw    $zero, %lo(gCreditsMenuElements+0x34)($at)
/* 09C594 8009B994 468084A0 */  cvt.s.w $f18, $f16
/* 09C598 8009B998 3C014270 */  li    $at, 0x42700000 # 60.000000
/* 09C59C 8009B99C 44812000 */  mtc1  $at, $f4
/* 09C5A0 8009B9A0 3C04800E */  lui   $a0, %hi(gCreditsMenuElements) # $a0, 0x800e
/* 09C5A4 8009B9A4 46049183 */  div.s $f6, $f18, $f4
/* 09C5A8 8009B9A8 4405A000 */  mfc1  $a1, $f20
/* 09C5AC 8009B9AC 4407A000 */  mfc1  $a3, $f20
/* 09C5B0 8009B9B0 24841B50 */  addiu $a0, %lo(gCreditsMenuElements) # addiu $a0, $a0, 0x1b50
/* 09C5B4 8009B9B4 AFA00010 */  sw    $zero, 0x10($sp)
/* 09C5B8 8009B9B8 AFA00014 */  sw    $zero, 0x14($sp)
/* 09C5BC 8009B9BC 44063000 */  mfc1  $a2, $f6
/* 09C5C0 8009B9C0 0C020795 */  jal   func_80081E54
/* 09C5C4 8009B9C4 00000000 */   nop   
/* 09C5C8 8009B9C8 0C0207D3 */  jal   func_80081F4C
/* 09C5CC 8009B9CC 00002025 */   move  $a0, $zero
/* 09C5D0 8009B9D0 3C08800E */  lui   $t0, %hi(gCreditsArray) # $t0, 0x800e
/* 09C5D4 8009B9D4 2C4C0001 */  sltiu $t4, $v0, 1
/* 09C5D8 8009B9D8 3C018012 */  lui   $at, %hi(D_80126BE0) # $at, 0x8012
/* 09C5DC 8009B9DC AC2C6BE0 */  sw    $t4, %lo(D_80126BE0)($at)
/* 09C5E0 8009B9E0 25081938 */  addiu $t0, %lo(gCreditsArray) # addiu $t0, $t0, 0x1938
/* 09C5E4 8009B9E4 10000009 */  b     .L8009BA0C
/* 09C5E8 8009B9E8 24076000 */   li    $a3, 24576
.L8009B9EC:
/* 09C5EC 8009B9EC AECB0000 */  sw    $t3, ($s6)
/* 09C5F0 8009B9F0 240D0001 */  li    $t5, 1
/* 09C5F4 8009B9F4 3C018012 */  lui   $at, %hi(D_80126BD8) # $at, 0x8012
/* 09C5F8 8009B9F8 240E0001 */  li    $t6, 1
/* 09C5FC 8009B9FC AC2D6BD8 */  sw    $t5, %lo(D_80126BD8)($at)
/* 09C600 8009BA00 10000002 */  b     .L8009BA0C
/* 09C604 8009BA04 AFAE006C */   sw    $t6, 0x6c($sp)
.L8009BA08:
/* 09C608 8009BA08 AECF0000 */  sw    $t7, ($s6)
.L8009BA0C:
/* 09C60C 8009BA0C 8FB8006C */  lw    $t8, 0x6c($sp)
.L8009BA10:
/* 09C610 8009BA10 00000000 */  nop   
/* 09C614 8009BA14 1300FEE0 */  beqz  $t8, .L8009B598
/* 09C618 8009BA18 00000000 */   nop   
/* 09C61C 8009BA1C 3C068012 */  lui   $a2, %hi(gOpacityDecayTimer) # $a2, 0x8012
/* 09C620 8009BA20 24C663D8 */  addiu $a2, %lo(gOpacityDecayTimer) # addiu $a2, $a2, 0x63d8
.L8009BA24:
/* 09C624 8009BA24 3C198012 */  lui   $t9, %hi(gIgnorePlayerInputTime) # $t9, 0x8012
/* 09C628 8009BA28 8F3963C4 */  lw    $t9, %lo(gIgnorePlayerInputTime)($t9)
/* 09C62C 8009BA2C 00009025 */  move  $s2, $zero
/* 09C630 8009BA30 1720000C */  bnez  $t9, .L8009BA64
/* 09C634 8009BA34 3C09800E */   lui   $t1, %hi(gMenuDelay) # $t1, 0x800e
/* 09C638 8009BA38 8D29F47C */  lw    $t1, %lo(gMenuDelay)($t1)
/* 09C63C 8009BA3C 00008025 */  move  $s0, $zero
/* 09C640 8009BA40 15200008 */  bnez  $t1, .L8009BA64
/* 09C644 8009BA44 24110004 */   li    $s1, 4
.L8009BA48:
/* 09C648 8009BA48 0C01A955 */  jal   get_buttons_pressed_from_player
/* 09C64C 8009BA4C 02002025 */   move  $a0, $s0
/* 09C650 8009BA50 26100001 */  addiu $s0, $s0, 1
/* 09C654 8009BA54 1611FFFC */  bne   $s0, $s1, .L8009BA48
/* 09C658 8009BA58 02429025 */   or    $s2, $s2, $v0
/* 09C65C 8009BA5C 3C068012 */  lui   $a2, %hi(gOpacityDecayTimer) # $a2, 0x8012
/* 09C660 8009BA60 24C663D8 */  addiu $a2, %lo(gOpacityDecayTimer) # addiu $a2, $a2, 0x63d8
.L8009BA64:
/* 09C664 8009BA64 3C108012 */  lui   $s0, %hi(gMenuOptionCount) # $s0, 0x8012
/* 09C668 8009BA68 261063E0 */  addiu $s0, %lo(gMenuOptionCount) # addiu $s0, $s0, 0x63e0
/* 09C66C 8009BA6C 8E0A0000 */  lw    $t2, ($s0)
/* 09C670 8009BA70 24110004 */  li    $s1, 4
/* 09C674 8009BA74 2D410005 */  sltiu $at, $t2, 5
/* 09C678 8009BA78 10200062 */  beqz  $at, .L8009BC04
/* 09C67C 8009BA7C 000A5080 */   sll   $t2, $t2, 2
/* 09C680 8009BA80 3C01800F */  lui   $at, %hi(jpt_800E8574) # $at, 0x800f
/* 09C684 8009BA84 002A0821 */  addu  $at, $at, $t2
/* 09C688 8009BA88 8C2A8574 */  lw    $t2, %lo(jpt_800E8574)($at)
/* 09C68C 8009BA8C 00000000 */  nop   
/* 09C690 8009BA90 01400008 */  jr    $t2
/* 09C694 8009BA94 00000000 */   nop   
glabel L8009BA98
/* 09C698 8009BA98 3C038012 */  lui   $v1, %hi(D_80126BCC) # $v1, 0x8012
/* 09C69C 8009BA9C 24636BCC */  addiu $v1, %lo(D_80126BCC) # addiu $v1, $v1, 0x6bcc
/* 09C6A0 8009BAA0 8C6C0000 */  lw    $t4, ($v1)
/* 09C6A4 8009BAA4 8FAD0060 */  lw    $t5, 0x60($sp)
/* 09C6A8 8009BAA8 000C5880 */  sll   $t3, $t4, 2
/* 09C6AC 8009BAAC 016D1021 */  addu  $v0, $t3, $t5
/* 09C6B0 8009BAB0 80440000 */  lb    $a0, ($v0)
/* 09C6B4 8009BAB4 80450002 */  lb    $a1, 2($v0)
/* 09C6B8 8009BAB8 0C031D16 */  jal   set_level_to_load_in_background
/* 09C6BC 8009BABC 00000000 */   nop   
/* 09C6C0 8009BAC0 240E0001 */  li    $t6, 1
/* 09C6C4 8009BAC4 AE0E0000 */  sw    $t6, ($s0)
/* 09C6C8 8009BAC8 240F0028 */  li    $t7, 40
/* 09C6CC 8009BACC 3C018012 */  lui   $at, %hi(gOpacityDecayTimer) # $at, 0x8012
/* 09C6D0 8009BAD0 1000004C */  b     .L8009BC04
/* 09C6D4 8009BAD4 AC2F63D8 */   sw    $t7, %lo(gOpacityDecayTimer)($at)
glabel L8009BAD8
/* 09C6D8 8009BAD8 0C031CF8 */  jal   get_thread30_level_id_to_load
/* 09C6DC 8009BADC 00000000 */   nop   
/* 09C6E0 8009BAE0 14400048 */  bnez  $v0, .L8009BC04
/* 09C6E4 8009BAE4 3C038012 */   lui   $v1, %hi(gOptionBlinkTimer) # $v1, 0x8012
/* 09C6E8 8009BAE8 246363BC */  addiu $v1, %lo(gOptionBlinkTimer) # addiu $v1, $v1, 0x63bc
/* 09C6EC 8009BAEC 24180002 */  li    $t8, 2
/* 09C6F0 8009BAF0 24190028 */  li    $t9, 40
/* 09C6F4 8009BAF4 AE180000 */  sw    $t8, ($s0)
/* 09C6F8 8009BAF8 AC790000 */  sw    $t9, ($v1)
/* 09C6FC 8009BAFC 3C018012 */  lui   $at, %hi(D_80126BD8) # $at, 0x8012
/* 09C700 8009BB00 10000040 */  b     .L8009BC04
/* 09C704 8009BB04 AC206BD8 */   sw    $zero, %lo(D_80126BD8)($at)
glabel L8009BB08
/* 09C708 8009BB08 3C038012 */  lui   $v1, %hi(gOptionBlinkTimer) # $v1, 0x8012
/* 09C70C 8009BB0C 246363BC */  addiu $v1, %lo(gOptionBlinkTimer) # addiu $v1, $v1, 0x63bc
/* 09C710 8009BB10 8C690000 */  lw    $t1, ($v1)
/* 09C714 8009BB14 8FAA0088 */  lw    $t2, 0x88($sp)
/* 09C718 8009BB18 8CCB0000 */  lw    $t3, ($a2)
/* 09C71C 8009BB1C 8FAD0088 */  lw    $t5, 0x88($sp)
/* 09C720 8009BB20 012A6023 */  subu  $t4, $t1, $t2
/* 09C724 8009BB24 016D7023 */  subu  $t6, $t3, $t5
/* 09C728 8009BB28 AC6C0000 */  sw    $t4, ($v1)
/* 09C72C 8009BB2C 1D800035 */  bgtz  $t4, .L8009BC04
/* 09C730 8009BB30 ACCE0000 */   sw    $t6, ($a2)
/* 09C734 8009BB34 258F0258 */  addiu $t7, $t4, 0x258
/* 09C738 8009BB38 24180003 */  li    $t8, 3
/* 09C73C 8009BB3C AC6F0000 */  sw    $t7, ($v1)
/* 09C740 8009BB40 10000030 */  b     .L8009BC04
/* 09C744 8009BB44 AE180000 */   sw    $t8, ($s0)
glabel L8009BB48
/* 09C748 8009BB48 3C038012 */  lui   $v1, %hi(gOptionBlinkTimer) # $v1, 0x8012
/* 09C74C 8009BB4C 246363BC */  addiu $v1, %lo(gOptionBlinkTimer) # addiu $v1, $v1, 0x63bc
/* 09C750 8009BB50 8C790000 */  lw    $t9, ($v1)
/* 09C754 8009BB54 8FA90088 */  lw    $t1, 0x88($sp)
/* 09C758 8009BB58 8CC20000 */  lw    $v0, ($a2)
/* 09C75C 8009BB5C 03295023 */  subu  $t2, $t9, $t1
/* 09C760 8009BB60 18400006 */  blez  $v0, .L8009BB7C
/* 09C764 8009BB64 AC6A0000 */   sw    $t2, ($v1)
/* 09C768 8009BB68 8FAC0088 */  lw    $t4, 0x88($sp)
/* 09C76C 8009BB6C 00000000 */  nop   
/* 09C770 8009BB70 004C5823 */  subu  $t3, $v0, $t4
/* 09C774 8009BB74 10000002 */  b     .L8009BB80
/* 09C778 8009BB78 ACCB0000 */   sw    $t3, ($a2)
.L8009BB7C:
/* 09C77C 8009BB7C ACC00000 */  sw    $zero, ($a2)
.L8009BB80:
/* 09C780 8009BB80 8C6D0000 */  lw    $t5, ($v1)
/* 09C784 8009BB84 240E0028 */  li    $t6, 40
/* 09C788 8009BB88 1DA0001F */  bgtz  $t5, .L8009BC08
/* 09C78C 8009BB8C 324C9000 */   andi  $t4, $s2, 0x9000
/* 09C790 8009BB90 AC6E0000 */  sw    $t6, ($v1)
/* 09C794 8009BB94 1000001B */  b     .L8009BC04
/* 09C798 8009BB98 AE110000 */   sw    $s1, ($s0)
glabel L8009BB9C
/* 09C79C 8009BB9C 3C038012 */  lui   $v1, %hi(gOptionBlinkTimer) # $v1, 0x8012
/* 09C7A0 8009BBA0 246363BC */  addiu $v1, %lo(gOptionBlinkTimer) # addiu $v1, $v1, 0x63bc
/* 09C7A4 8009BBA4 8C6F0000 */  lw    $t7, ($v1)
/* 09C7A8 8009BBA8 8FB80088 */  lw    $t8, 0x88($sp)
/* 09C7AC 8009BBAC 8CC90000 */  lw    $t1, ($a2)
/* 09C7B0 8009BBB0 8FAA0088 */  lw    $t2, 0x88($sp)
/* 09C7B4 8009BBB4 01F8C823 */  subu  $t9, $t7, $t8
/* 09C7B8 8009BBB8 012A6021 */  addu  $t4, $t1, $t2
/* 09C7BC 8009BBBC AC790000 */  sw    $t9, ($v1)
/* 09C7C0 8009BBC0 1F200010 */  bgtz  $t9, .L8009BC04
/* 09C7C4 8009BBC4 ACCC0000 */   sw    $t4, ($a2)
/* 09C7C8 8009BBC8 3C038012 */  lui   $v1, %hi(D_80126BCC) # $v1, 0x8012
/* 09C7CC 8009BBCC 24636BCC */  addiu $v1, %lo(D_80126BCC) # addiu $v1, $v1, 0x6bcc
/* 09C7D0 8009BBD0 8C6D0000 */  lw    $t5, ($v1)
/* 09C7D4 8009BBD4 8FB90060 */  lw    $t9, 0x60($sp)
/* 09C7D8 8009BBD8 25AE0001 */  addiu $t6, $t5, 1
/* 09C7DC 8009BBDC 000EC080 */  sll   $t8, $t6, 2
/* 09C7E0 8009BBE0 AE000000 */  sw    $zero, ($s0)
/* 09C7E4 8009BBE4 AC6E0000 */  sw    $t6, ($v1)
/* 09C7E8 8009BBE8 03194821 */  addu  $t1, $t8, $t9
/* 09C7EC 8009BBEC 812A0000 */  lb    $t2, ($t1)
/* 09C7F0 8009BBF0 3C018012 */  lui   $at, %hi(gIgnorePlayerInputTime) # $at, 0x8012
/* 09C7F4 8009BBF4 05410004 */  bgez  $t2, .L8009BC08
/* 09C7F8 8009BBF8 324C9000 */   andi  $t4, $s2, 0x9000
/* 09C7FC 8009BBFC AC600000 */  sw    $zero, ($v1)
/* 09C800 8009BC00 AC2063C4 */  sw    $zero, %lo(gIgnorePlayerInputTime)($at)
.L8009BC04:
/* 09C804 8009BC04 324C9000 */  andi  $t4, $s2, 0x9000
.L8009BC08:
/* 09C808 8009BC08 15800006 */  bnez  $t4, .L8009BC24
/* 09C80C 8009BC0C 324B4000 */   andi  $t3, $s2, 0x4000
/* 09C810 8009BC10 15600005 */  bnez  $t3, .L8009BC28
/* 09C814 8009BC14 240E0001 */   li    $t6, 1
/* 09C818 8009BC18 8FAD0068 */  lw    $t5, 0x68($sp)
/* 09C81C 8009BC1C 00000000 */  nop   
/* 09C820 8009BC20 11A0000B */  beqz  $t5, .L8009BC50
.L8009BC24:
/* 09C824 8009BC24 240E0001 */   li    $t6, 1
.L8009BC28:
/* 09C828 8009BC28 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 09C82C 8009BC2C 0C030060 */  jal   disable_new_screen_transitions
/* 09C830 8009BC30 AC2EF47C */   sw    $t6, %lo(gMenuDelay)($at)
/* 09C834 8009BC34 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 09C838 8009BC38 0C030076 */  jal   transition_begin
/* 09C83C 8009BC3C 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 09C840 8009BC40 0C03005C */  jal   enable_new_screen_transitions
/* 09C844 8009BC44 00000000 */   nop   
/* 09C848 8009BC48 0C000326 */  jal   music_fade
/* 09C84C 8009BC4C 2404FF80 */   li    $a0, -128
.L8009BC50:
/* 09C850 8009BC50 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 09C854 8009BC54 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 09C858 8009BC58 8FAF0088 */  lw    $t7, 0x88($sp)
/* 09C85C 8009BC5C 18400015 */  blez  $v0, .L8009BCB4
/* 09C860 8009BC60 004FC021 */   addu  $t8, $v0, $t7
/* 09C864 8009BC64 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 09C868 8009BC68 0C031CF8 */  jal   get_thread30_level_id_to_load
/* 09C86C 8009BC6C AC38F47C */   sw    $t8, %lo(gMenuDelay)($at)
/* 09C870 8009BC70 14400010 */  bnez  $v0, .L8009BCB4
/* 09C874 8009BC74 3C19800E */   lui   $t9, %hi(gMenuDelay) # $t9, 0x800e
/* 09C878 8009BC78 8F39F47C */  lw    $t9, %lo(gMenuDelay)($t9)
/* 09C87C 8009BC7C 00000000 */  nop   
/* 09C880 8009BC80 2B21001F */  slti  $at, $t9, 0x1f
/* 09C884 8009BC84 1420000C */  bnez  $at, .L8009BCB8
/* 09C888 8009BC88 8FBF0054 */   lw    $ra, 0x54($sp)
/* 09C88C 8009BC8C 0C0002CA */  jal   music_change_on
/* 09C890 8009BC90 00000000 */   nop   
/* 09C894 8009BC94 0C026F3C */  jal   func_8009BCF0
/* 09C898 8009BC98 00000000 */   nop   
/* 09C89C 8009BC9C 24040015 */  li    $a0, 21
/* 09C8A0 8009BCA0 2405FFFF */  li    $a1, -1
/* 09C8A4 8009BCA4 0C01B8BA */  jal   load_level_for_menu
/* 09C8A8 8009BCA8 00003025 */   move  $a2, $zero
/* 09C8AC 8009BCAC 0C0204F4 */  jal   menu_init
/* 09C8B0 8009BCB0 24040001 */   li    $a0, 1
.L8009BCB4:
/* 09C8B4 8009BCB4 8FBF0054 */  lw    $ra, 0x54($sp)
.L8009BCB8:
/* 09C8B8 8009BCB8 C7B50028 */  lwc1  $f21, 0x28($sp)
/* 09C8BC 8009BCBC C7B4002C */  lwc1  $f20, 0x2c($sp)
/* 09C8C0 8009BCC0 8FB00030 */  lw    $s0, 0x30($sp)
/* 09C8C4 8009BCC4 8FB10034 */  lw    $s1, 0x34($sp)
/* 09C8C8 8009BCC8 8FB20038 */  lw    $s2, 0x38($sp)
/* 09C8CC 8009BCCC 8FB3003C */  lw    $s3, 0x3c($sp)
/* 09C8D0 8009BCD0 8FB40040 */  lw    $s4, 0x40($sp)
/* 09C8D4 8009BCD4 8FB50044 */  lw    $s5, 0x44($sp)
/* 09C8D8 8009BCD8 8FB60048 */  lw    $s6, 0x48($sp)
/* 09C8DC 8009BCDC 8FB7004C */  lw    $s7, 0x4c($sp)
/* 09C8E0 8009BCE0 8FBE0050 */  lw    $fp, 0x50($sp)
/* 09C8E4 8009BCE4 27BD0088 */  addiu $sp, $sp, 0x88
/* 09C8E8 8009BCE8 03E00008 */  jr    $ra
/* 09C8EC 8009BCEC 00001025 */   move  $v0, $zero

