glabel func_8001A8F4
/* 01B4F4 8001A8F4 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 01B4F8 8001A8F8 AFBF001C */  sw    $ra, 0x1c($sp)
/* 01B4FC 8001A8FC AFA40040 */  sw    $a0, 0x40($sp)
/* 01B500 8001A900 AFB10018 */  sw    $s1, 0x18($sp)
/* 01B504 8001A904 AFB00014 */  sw    $s0, 0x14($sp)
/* 01B508 8001A908 0C01BCE2 */  jal   func_8006F388
/* 01B50C 8001A90C 24040001 */   li    $a0, 1
/* 01B510 8001A910 3C108012 */  lui   $s0, %hi(D_8011AD4E) # $s0, 0x8012
/* 01B514 8001A914 2610AD4E */  addiu $s0, %lo(D_8011AD4E) # addiu $s0, $s0, -0x52b2
/* 01B518 8001A918 86030000 */  lh    $v1, ($s0)
/* 01B51C 8001A91C 8FAE0040 */  lw    $t6, 0x40($sp)
/* 01B520 8001A920 2419FFFF */  li    $t9, -1
/* 01B524 8001A924 006E7823 */  subu  $t7, $v1, $t6
/* 01B528 8001A928 A60F0000 */  sh    $t7, ($s0)
/* 01B52C 8001A92C 86180000 */  lh    $t8, ($s0)
/* 01B530 8001A930 28610033 */  slti  $at, $v1, 0x33
/* 01B534 8001A934 1F000002 */  bgtz  $t8, .L8001A940
/* 01B538 8001A938 00000000 */   nop   
/* 01B53C 8001A93C A6190000 */  sh    $t9, ($s0)
.L8001A940:
/* 01B540 8001A940 14200008 */  bnez  $at, .L8001A964
/* 01B544 8001A944 00000000 */   nop   
/* 01B548 8001A948 86090000 */  lh    $t1, ($s0)
/* 01B54C 8001A94C 3C04800E */  lui   $a0, %hi(D_800DC858) # $a0, 0x800e
/* 01B550 8001A950 29210033 */  slti  $at, $t1, 0x33
/* 01B554 8001A954 10200003 */  beqz  $at, .L8001A964
/* 01B558 8001A958 00000000 */   nop   
/* 01B55C 8001A95C 0C030076 */  jal   transition_begin
/* 01B560 8001A960 2484C858 */   addiu $a0, %lo(D_800DC858) # addiu $a0, $a0, -0x37a8
.L8001A964:
/* 01B564 8001A964 3C028012 */  lui   $v0, %hi(D_8011AD50) # $v0, 0x8012
/* 01B568 8001A968 8042AD50 */  lb    $v0, %lo(D_8011AD50)($v0)
/* 01B56C 8001A96C AFA00030 */  sw    $zero, 0x30($sp)
/* 01B570 8001A970 14400071 */  bnez  $v0, .L8001AB38
/* 01B574 8001A974 00000000 */   nop   
/* 01B578 8001A978 860A0000 */  lh    $t2, ($s0)
/* 01B57C 8001A97C 2401FFFF */  li    $at, -1
/* 01B580 8001A980 1541006D */  bne   $t2, $at, .L8001AB38
/* 01B584 8001A984 3C118012 */   lui   $s1, %hi(gNumRacers) # $s1, 0x8012
/* 01B588 8001A988 2631AEF0 */  addiu $s1, %lo(gNumRacers) # addiu $s1, $s1, -0x5110
/* 01B58C 8001A98C 8E2B0000 */  lw    $t3, ($s1)
/* 01B590 8001A990 00008025 */  move  $s0, $zero
/* 01B594 8001A994 19600029 */  blez  $t3, .L8001AA3C
/* 01B598 8001A998 00001825 */   move  $v1, $zero
.L8001A99C:
/* 01B59C 8001A99C 3C0C8012 */  lui   $t4, %hi(gRacers) # $t4, 0x8012
/* 01B5A0 8001A9A0 8D8CAEE4 */  lw    $t4, %lo(gRacers)($t4)
/* 01B5A4 8001A9A4 2401FFFF */  li    $at, -1
/* 01B5A8 8001A9A8 01836821 */  addu  $t5, $t4, $v1
/* 01B5AC 8001A9AC 8DAE0000 */  lw    $t6, ($t5)
/* 01B5B0 8001A9B0 00000000 */  nop   
/* 01B5B4 8001A9B4 8DC50064 */  lw    $a1, 0x64($t6)
/* 01B5B8 8001A9B8 00000000 */  nop   
/* 01B5BC 8001A9BC 84AF0000 */  lh    $t7, ($a1)
/* 01B5C0 8001A9C0 ACA00140 */  sw    $zero, 0x140($a1)
/* 01B5C4 8001A9C4 11E10006 */  beq   $t7, $at, .L8001A9E0
/* 01B5C8 8001A9C8 00000000 */   nop   
/* 01B5CC 8001A9CC 84B801AC */  lh    $t8, 0x1ac($a1)
/* 01B5D0 8001A9D0 24010001 */  li    $at, 1
/* 01B5D4 8001A9D4 17010002 */  bne   $t8, $at, .L8001A9E0
/* 01B5D8 8001A9D8 00000000 */   nop   
/* 01B5DC 8001A9DC AFB00030 */  sw    $s0, 0x30($sp)
.L8001A9E0:
/* 01B5E0 8001A9E0 8CA40178 */  lw    $a0, 0x178($a1)
/* 01B5E4 8001A9E4 00000000 */  nop   
/* 01B5E8 8001A9E8 10800007 */  beqz  $a0, .L8001AA08
/* 01B5EC 8001A9EC 00000000 */   nop   
/* 01B5F0 8001A9F0 AFA30020 */  sw    $v1, 0x20($sp)
/* 01B5F4 8001A9F4 0C001223 */  jal   func_8000488C
/* 01B5F8 8001A9F8 AFA50038 */   sw    $a1, 0x38($sp)
/* 01B5FC 8001A9FC 8FA30020 */  lw    $v1, 0x20($sp)
/* 01B600 8001AA00 8FA50038 */  lw    $a1, 0x38($sp)
/* 01B604 8001AA04 00000000 */  nop   
.L8001AA08:
/* 01B608 8001AA08 8CA4017C */  lw    $a0, 0x17c($a1)
/* 01B60C 8001AA0C 00000000 */  nop   
/* 01B610 8001AA10 10800005 */  beqz  $a0, .L8001AA28
/* 01B614 8001AA14 00000000 */   nop   
/* 01B618 8001AA18 0C0025BE */  jal   func_800096F8
/* 01B61C 8001AA1C AFA30020 */   sw    $v1, 0x20($sp)
/* 01B620 8001AA20 8FA30020 */  lw    $v1, 0x20($sp)
/* 01B624 8001AA24 00000000 */  nop   
.L8001AA28:
/* 01B628 8001AA28 8E390000 */  lw    $t9, ($s1)
/* 01B62C 8001AA2C 26100001 */  addiu $s0, $s0, 1
/* 01B630 8001AA30 0219082A */  slt   $at, $s0, $t9
/* 01B634 8001AA34 1420FFD9 */  bnez  $at, .L8001A99C
/* 01B638 8001AA38 24630004 */   addiu $v1, $v1, 4
.L8001AA3C:
/* 01B63C 8001AA3C 8FA30030 */  lw    $v1, 0x30($sp)
/* 01B640 8001AA40 3C028012 */  lui   $v0, %hi(gRacers) # $v0, 0x8012
/* 01B644 8001AA44 8C42AEE4 */  lw    $v0, %lo(gRacers)($v0)
/* 01B648 8001AA48 00034880 */  sll   $t1, $v1, 2
/* 01B64C 8001AA4C 00495021 */  addu  $t2, $v0, $t1
/* 01B650 8001AA50 8D4B0000 */  lw    $t3, ($t2)
/* 01B654 8001AA54 8C460000 */  lw    $a2, ($v0)
/* 01B658 8001AA58 3C0C8012 */  lui   $t4, %hi(gRacers) # $t4, 0x8012
/* 01B65C 8001AA5C AC4B0000 */  sw    $t3, ($v0)
/* 01B660 8001AA60 8D8CAEE4 */  lw    $t4, %lo(gRacers)($t4)
/* 01B664 8001AA64 3C0E8012 */  lui   $t6, %hi(gRacers) # $t6, 0x8012
/* 01B668 8001AA68 01896821 */  addu  $t5, $t4, $t1
/* 01B66C 8001AA6C ADA60000 */  sw    $a2, ($t5)
/* 01B670 8001AA70 8DCEAEE4 */  lw    $t6, %lo(gRacers)($t6)
/* 01B674 8001AA74 00000000 */  nop   
/* 01B678 8001AA78 8DC40000 */  lw    $a0, ($t6)
/* 01B67C 8001AA7C 0C001AB2 */  jal   func_80006AC8
/* 01B680 8001AA80 00000000 */   nop   
/* 01B684 8001AA84 0C0282DD */  jal   func_800A0B74
/* 01B688 8001AA88 00000000 */   nop   
/* 01B68C 8001AA8C 0C00FC34 */  jal   func_8003F0D0
/* 01B690 8001AA90 00000000 */   nop   
/* 01B694 8001AA94 0C001276 */  jal   func_800049D8
/* 01B698 8001AA98 00000000 */   nop   
/* 01B69C 8001AA9C 0C027B20 */  jal   is_in_two_player_adventure
/* 01B6A0 8001AAA0 00000000 */   nop   
/* 01B6A4 8001AAA4 1040001C */  beqz  $v0, .L8001AB18
/* 01B6A8 8001AAA8 00000000 */   nop   
/* 01B6AC 8001AAAC 0C009278 */  jal   set_scene_viewport_num
/* 01B6B0 8001AAB0 00002025 */   move  $a0, $zero
/* 01B6B4 8001AAB4 0C01994B */  jal   set_active_viewports_and_max
/* 01B6B8 8001AAB8 00002025 */   move  $a0, $zero
/* 01B6BC 8001AABC 3C0F8012 */  lui   $t7, %hi(gRacers) # $t7, 0x8012
/* 01B6C0 8001AAC0 8DEFAEE4 */  lw    $t7, %lo(gRacers)($t7)
/* 01B6C4 8001AAC4 3C078012 */  lui   $a3, %hi(gRacersByPort) # $a3, 0x8012
/* 01B6C8 8001AAC8 24E7AEEC */  addiu $a3, %lo(gRacersByPort) # addiu $a3, $a3, -0x5114
/* 01B6CC 8001AACC 8CE40000 */  lw    $a0, ($a3)
/* 01B6D0 8001AAD0 8DE30000 */  lw    $v1, ($t7)
/* 01B6D4 8001AAD4 8C860000 */  lw    $a2, ($a0)
/* 01B6D8 8001AAD8 8C650064 */  lw    $a1, 0x64($v1)
/* 01B6DC 8001AADC AC830000 */  sw    $v1, ($a0)
/* 01B6E0 8001AAE0 8CF80000 */  lw    $t8, ($a3)
/* 01B6E4 8001AAE4 3C08800E */  lui   $t0, %hi(D_800DC744) # $t0, 0x800e
/* 01B6E8 8001AAE8 2508C744 */  addiu $t0, %lo(D_800DC744) # addiu $t0, $t0, -0x38bc
/* 01B6EC 8001AAEC AF060004 */  sw    $a2, 4($t8)
/* 01B6F0 8001AAF0 81190000 */  lb    $t9, ($t0)
/* 01B6F4 8001AAF4 00000000 */  nop   
/* 01B6F8 8001AAF8 13200007 */  beqz  $t9, .L8001AB18
/* 01B6FC 8001AAFC 00000000 */   nop   
/* 01B700 8001AB00 A1000000 */  sb    $zero, ($t0)
/* 01B704 8001AB04 0C01BCE6 */  jal   func_8006F398
/* 01B708 8001AB08 AFA50038 */   sw    $a1, 0x38($sp)
/* 01B70C 8001AB0C 8FA50038 */  lw    $a1, 0x38($sp)
/* 01B710 8001AB10 00000000 */  nop   
/* 01B714 8001AB14 A4A00000 */  sh    $zero, ($a1)
.L8001AB18:
/* 01B718 8001AB18 8E290000 */  lw    $t1, ($s1)
/* 01B71C 8001AB1C 3C078012 */  lui   $a3, %hi(D_8011AD51) # $a3, 0x8012
/* 01B720 8001AB20 24E7AD51 */  addiu $a3, %lo(D_8011AD51) # addiu $a3, $a3, -0x52af
/* 01B724 8001AB24 240A0001 */  li    $t2, 1
/* 01B728 8001AB28 3C018012 */  lui   $at, %hi(D_8011AD50) # $at, 0x8012
/* 01B72C 8001AB2C A0E90000 */  sb    $t1, ($a3)
/* 01B730 8001AB30 A02AAD50 */  sb    $t2, %lo(D_8011AD50)($at)
/* 01B734 8001AB34 24020001 */  li    $v0, 1
.L8001AB38:
/* 01B738 8001AB38 3C118012 */  lui   $s1, %hi(gNumRacers) # $s1, 0x8012
/* 01B73C 8001AB3C 24010001 */  li    $at, 1
/* 01B740 8001AB40 14410055 */  bne   $v0, $at, .L8001AC98
/* 01B744 8001AB44 2631AEF0 */   addiu $s1, %lo(gNumRacers) # addiu $s1, $s1, -0x5110
/* 01B748 8001AB48 0C02AC75 */  jal   set_hud_visibility
/* 01B74C 8001AB4C 00002025 */   move  $a0, $zero
/* 01B750 8001AB50 3C078012 */  lui   $a3, %hi(D_8011AD51) # $a3, 0x8012
/* 01B754 8001AB54 24E7AD51 */  addiu $a3, %lo(D_8011AD51) # addiu $a3, $a3, -0x52af
/* 01B758 8001AB58 80EB0000 */  lb    $t3, ($a3)
/* 01B75C 8001AB5C 00000000 */  nop   
/* 01B760 8001AB60 256CFFFF */  addiu $t4, $t3, -1
/* 01B764 8001AB64 A0EC0000 */  sb    $t4, ($a3)
/* 01B768 8001AB68 80E60000 */  lb    $a2, ($a3)
/* 01B76C 8001AB6C 00000000 */  nop   
/* 01B770 8001AB70 18C00046 */  blez  $a2, .L8001AC8C
/* 01B774 8001AB74 24180002 */   li    $t8, 2
/* 01B778 8001AB78 8E240000 */  lw    $a0, ($s1)
/* 01B77C 8001AB7C 00008025 */  move  $s0, $zero
/* 01B780 8001AB80 18800015 */  blez  $a0, .L8001ABD8
/* 01B784 8001AB84 3C058012 */   lui   $a1, %hi(gRacersByPosition) # $a1, 0x8012
/* 01B788 8001AB88 3C0D8012 */  lui   $t5, %hi(gRacers) # $t5, 0x8012
/* 01B78C 8001AB8C 8DADAEE4 */  lw    $t5, %lo(gRacers)($t5)
/* 01B790 8001AB90 24A5AEE8 */  addiu $a1, %lo(gRacersByPosition) # addiu $a1, $a1, -0x5118
/* 01B794 8001AB94 8CA20000 */  lw    $v0, ($a1)
/* 01B798 8001AB98 00067080 */  sll   $t6, $a2, 2
/* 01B79C 8001AB9C 01AE7821 */  addu  $t7, $t5, $t6
/* 01B7A0 8001ABA0 8DE30000 */  lw    $v1, ($t7)
/* 01B7A4 8001ABA4 8C580000 */  lw    $t8, ($v0)
/* 01B7A8 8001ABA8 00000000 */  nop   
/* 01B7AC 8001ABAC 1303000A */  beq   $t8, $v1, .L8001ABD8
/* 01B7B0 8001ABB0 00000000 */   nop   
.L8001ABB4:
/* 01B7B4 8001ABB4 26100001 */  addiu $s0, $s0, 1
/* 01B7B8 8001ABB8 0204082A */  slt   $at, $s0, $a0
/* 01B7BC 8001ABBC 10200006 */  beqz  $at, .L8001ABD8
/* 01B7C0 8001ABC0 0010C880 */   sll   $t9, $s0, 2
/* 01B7C4 8001ABC4 00594821 */  addu  $t1, $v0, $t9
/* 01B7C8 8001ABC8 8D2A0000 */  lw    $t2, ($t1)
/* 01B7CC 8001ABCC 00000000 */  nop   
/* 01B7D0 8001ABD0 1543FFF8 */  bne   $t2, $v1, .L8001ABB4
/* 01B7D4 8001ABD4 00000000 */   nop   
.L8001ABD8:
/* 01B7D8 8001ABD8 3C058012 */  lui   $a1, %hi(gRacersByPosition) # $a1, 0x8012
/* 01B7DC 8001ABDC 0204082A */  slt   $at, $s0, $a0
/* 01B7E0 8001ABE0 10200013 */  beqz  $at, .L8001AC30
/* 01B7E4 8001ABE4 24A5AEE8 */   addiu $a1, %lo(gRacersByPosition) # addiu $a1, $a1, -0x5118
/* 01B7E8 8001ABE8 248BFFFF */  addiu $t3, $a0, -1
/* 01B7EC 8001ABEC 020B082A */  slt   $at, $s0, $t3
/* 01B7F0 8001ABF0 1020000F */  beqz  $at, .L8001AC30
/* 01B7F4 8001ABF4 00101880 */   sll   $v1, $s0, 2
.L8001ABF8:
/* 01B7F8 8001ABF8 8CAC0000 */  lw    $t4, ($a1)
/* 01B7FC 8001ABFC 26100001 */  addiu $s0, $s0, 1
/* 01B800 8001AC00 01831021 */  addu  $v0, $t4, $v1
/* 01B804 8001AC04 8C4D0004 */  lw    $t5, 4($v0)
/* 01B808 8001AC08 24630004 */  addiu $v1, $v1, 4
/* 01B80C 8001AC0C AC4D0000 */  sw    $t5, ($v0)
/* 01B810 8001AC10 8E2E0000 */  lw    $t6, ($s1)
/* 01B814 8001AC14 00000000 */  nop   
/* 01B818 8001AC18 25CFFFFF */  addiu $t7, $t6, -1
/* 01B81C 8001AC1C 020F082A */  slt   $at, $s0, $t7
/* 01B820 8001AC20 1420FFF5 */  bnez  $at, .L8001ABF8
/* 01B824 8001AC24 00000000 */   nop   
/* 01B828 8001AC28 80E60000 */  lb    $a2, ($a3)
/* 01B82C 8001AC2C 00000000 */  nop   
.L8001AC30:
/* 01B830 8001AC30 3C188012 */  lui   $t8, %hi(gRacers) # $t8, 0x8012
/* 01B834 8001AC34 8F18AEE4 */  lw    $t8, %lo(gRacers)($t8)
/* 01B838 8001AC38 0006C880 */  sll   $t9, $a2, 2
/* 01B83C 8001AC3C 03194821 */  addu  $t1, $t8, $t9
/* 01B840 8001AC40 8D240000 */  lw    $a0, ($t1)
/* 01B844 8001AC44 0C003FEE */  jal   gParticlePtrList_addObject
/* 01B848 8001AC48 00000000 */   nop   
/* 01B84C 8001AC4C 3C078012 */  lui   $a3, %hi(D_8011AD51) # $a3, 0x8012
/* 01B850 8001AC50 24E7AD51 */  addiu $a3, %lo(D_8011AD51) # addiu $a3, $a3, -0x52af
/* 01B854 8001AC54 80EB0000 */  lb    $t3, ($a3)
/* 01B858 8001AC58 3C0A8012 */  lui   $t2, %hi(gRacers) # $t2, 0x8012
/* 01B85C 8001AC5C 8D4AAEE4 */  lw    $t2, %lo(gRacers)($t2)
/* 01B860 8001AC60 000B6080 */  sll   $t4, $t3, 2
/* 01B864 8001AC64 014C6821 */  addu  $t5, $t2, $t4
/* 01B868 8001AC68 ADA00000 */  sw    $zero, ($t5)
/* 01B86C 8001AC6C 8E2E0000 */  lw    $t6, ($s1)
/* 01B870 8001AC70 3C028012 */  lui   $v0, %hi(D_8011AD50) # $v0, 0x8012
/* 01B874 8001AC74 25CFFFFF */  addiu $t7, $t6, -1
/* 01B878 8001AC78 AE2F0000 */  sw    $t7, ($s1)
/* 01B87C 8001AC7C 8042AD50 */  lb    $v0, %lo(D_8011AD50)($v0)
/* 01B880 8001AC80 10000006 */  b     .L8001AC9C
/* 01B884 8001AC84 24010002 */   li    $at, 2
/* 01B888 8001AC88 24180002 */  li    $t8, 2
.L8001AC8C:
/* 01B88C 8001AC8C 3C018012 */  lui   $at, %hi(D_8011AD50) # $at, 0x8012
/* 01B890 8001AC90 A038AD50 */  sb    $t8, %lo(D_8011AD50)($at)
/* 01B894 8001AC94 24020002 */  li    $v0, 2
.L8001AC98:
/* 01B898 8001AC98 24010002 */  li    $at, 2
.L8001AC9C:
/* 01B89C 8001AC9C 14410016 */  bne   $v0, $at, .L8001ACF8
/* 01B8A0 8001ACA0 3C198012 */   lui   $t9, %hi(gRacers) # $t9, 0x8012
/* 01B8A4 8001ACA4 8F39AEE4 */  lw    $t9, %lo(gRacers)($t9)
/* 01B8A8 8001ACA8 00000000 */  nop   
/* 01B8AC 8001ACAC 8F240000 */  lw    $a0, ($t9)
/* 01B8B0 8001ACB0 00000000 */  nop   
/* 01B8B4 8001ACB4 8C850064 */  lw    $a1, 0x64($a0)
/* 01B8B8 8001ACB8 0C008C34 */  jal   func_800230D0
/* 01B8BC 8001ACBC AFA50038 */   sw    $a1, 0x38($sp)
/* 01B8C0 8001ACC0 8FA50038 */  lw    $a1, 0x38($sp)
/* 01B8C4 8001ACC4 24090003 */  li    $t1, 3
/* 01B8C8 8001ACC8 3C018012 */  lui   $at, %hi(D_8011AD50) # $at, 0x8012
/* 01B8CC 8001ACCC A0A001D8 */  sb    $zero, 0x1d8($a1)
/* 01B8D0 8001ACD0 A029AD50 */  sb    $t1, %lo(D_8011AD50)($at)
/* 01B8D4 8001ACD4 0C007917 */  jal   func_8001E45C
/* 01B8D8 8001ACD8 2404000A */   li    $a0, 10
/* 01B8DC 8001ACDC 3C108012 */  lui   $s0, %hi(D_8011ADC8) # $s0, 0x8012
/* 01B8E0 8001ACE0 2610ADC8 */  addiu $s0, %lo(D_8011ADC8) # addiu $s0, $s0, -0x5238
/* 01B8E4 8001ACE4 0C007A4F */  jal   func_8001E93C
/* 01B8E8 8001ACE8 AE000000 */   sw    $zero, ($s0)
/* 01B8EC 8001ACEC 3C028012 */  lui   $v0, %hi(D_8011AD50) # $v0, 0x8012
/* 01B8F0 8001ACF0 8042AD50 */  lb    $v0, %lo(D_8011AD50)($v0)
/* 01B8F4 8001ACF4 00000000 */  nop   
.L8001ACF8:
/* 01B8F8 8001ACF8 3C108012 */  lui   $s0, %hi(D_8011ADC8) # $s0, 0x8012
/* 01B8FC 8001ACFC 24010003 */  li    $at, 3
/* 01B900 8001AD00 1441000C */  bne   $v0, $at, .L8001AD34
/* 01B904 8001AD04 2610ADC8 */   addiu $s0, %lo(D_8011ADC8) # addiu $s0, $s0, -0x5238
/* 01B908 8001AD08 3C04800E */  lui   $a0, %hi(D_800DC860) # $a0, 0x800e
/* 01B90C 8001AD0C 0C030076 */  jal   transition_begin
/* 01B910 8001AD10 2484C860 */   addiu $a0, %lo(D_800DC860) # addiu $a0, $a0, -0x37a0
/* 01B914 8001AD14 240B0004 */  li    $t3, 4
/* 01B918 8001AD18 3C018012 */  lui   $at, %hi(D_8011AD50) # $at, 0x8012
/* 01B91C 8001AD1C A02BAD50 */  sb    $t3, %lo(D_8011AD50)($at)
/* 01B920 8001AD20 0C00A3E8 */  jal   set_anti_aliasing
/* 01B924 8001AD24 24040001 */   li    $a0, 1
/* 01B928 8001AD28 3C028012 */  lui   $v0, %hi(D_8011AD50) # $v0, 0x8012
/* 01B92C 8001AD2C 8042AD50 */  lb    $v0, %lo(D_8011AD50)($v0)
/* 01B930 8001AD30 00000000 */  nop   
.L8001AD34:
/* 01B934 8001AD34 24010004 */  li    $at, 4
/* 01B938 8001AD38 1441003E */  bne   $v0, $at, .L8001AE34
/* 01B93C 8001AD3C 8FBF001C */   lw    $ra, 0x1c($sp)
/* 01B940 8001AD40 0C00A3E8 */  jal   set_anti_aliasing
/* 01B944 8001AD44 24040001 */   li    $a0, 1
/* 01B948 8001AD48 0C0168EC */  jal   disable_racer_input
/* 01B94C 8001AD4C 00000000 */   nop   
/* 01B950 8001AD50 0C01AF66 */  jal   get_current_level_race_type
/* 01B954 8001AD54 00000000 */   nop   
/* 01B958 8001AD58 304A0040 */  andi  $t2, $v0, 0x40
/* 01B95C 8001AD5C 15400013 */  bnez  $t2, .L8001ADAC
/* 01B960 8001AD60 3C0C8000 */   lui   $t4, %hi(osTvType) # $t4, 0x8000
/* 01B964 8001AD64 8D8C0300 */  lw    $t4, %lo(osTvType)($t4)
/* 01B968 8001AD68 8FAE0040 */  lw    $t6, 0x40($sp)
/* 01B96C 8001AD6C 15800003 */  bnez  $t4, .L8001AD7C
/* 01B970 8001AD70 2402021C */   li    $v0, 540
/* 01B974 8001AD74 10000001 */  b     .L8001AD7C
/* 01B978 8001AD78 2402019F */   li    $v0, 415
.L8001AD7C:
/* 01B97C 8001AD7C 8E0D0000 */  lw    $t5, ($s0)
/* 01B980 8001AD80 00000000 */  nop   
/* 01B984 8001AD84 01AE7821 */  addu  $t7, $t5, $t6
/* 01B988 8001AD88 01E2082B */  sltu  $at, $t7, $v0
/* 01B98C 8001AD8C 10200005 */  beqz  $at, .L8001ADA4
/* 01B990 8001AD90 AE0F0000 */   sw    $t7, ($s0)
/* 01B994 8001AD94 0C02AC65 */  jal   func_800AB194
/* 01B998 8001AD98 24040001 */   li    $a0, 1
/* 01B99C 8001AD9C 10000003 */  b     .L8001ADAC
/* 01B9A0 8001ADA0 00000000 */   nop   
.L8001ADA4:
/* 01B9A4 8001ADA4 0C02AC75 */  jal   set_hud_visibility
/* 01B9A8 8001ADA8 24040001 */   li    $a0, 1
.L8001ADAC:
/* 01B9AC 8001ADAC 0C01A955 */  jal   get_buttons_pressed_from_player
/* 01B9B0 8001ADB0 00002025 */   move  $a0, $zero
/* 01B9B4 8001ADB4 0C01BAA4 */  jal   get_settings
/* 01B9B8 8001ADB8 30508000 */   andi  $s0, $v0, 0x8000
/* 01B9BC 8001ADBC 8C590010 */  lw    $t9, 0x10($v0)
/* 01B9C0 8001ADC0 00408825 */  move  $s1, $v0
/* 01B9C4 8001ADC4 00194B40 */  sll   $t1, $t9, 0xd
/* 01B9C8 8001ADC8 05200002 */  bltz  $t1, .L8001ADD4
/* 01B9CC 8001ADCC 00000000 */   nop   
/* 01B9D0 8001ADD0 00008025 */  move  $s0, $zero
.L8001ADD4:
/* 01B9D4 8001ADD4 0C008531 */  jal   func_800214C4
/* 01B9D8 8001ADD8 00000000 */   nop   
/* 01B9DC 8001ADDC 14400007 */  bnez  $v0, .L8001ADFC
/* 01B9E0 8001ADE0 00000000 */   nop   
/* 01B9E4 8001ADE4 12000013 */  beqz  $s0, .L8001AE34
/* 01B9E8 8001ADE8 8FBF001C */   lw    $ra, 0x1c($sp)
/* 01B9EC 8001ADEC 0C030063 */  jal   fxFadeOn
/* 01B9F0 8001ADF0 00000000 */   nop   
/* 01B9F4 8001ADF4 1440000F */  bnez  $v0, .L8001AE34
/* 01B9F8 8001ADF8 8FBF001C */   lw    $ra, 0x1c($sp)
.L8001ADFC:
/* 01B9FC 8001ADFC 12000003 */  beqz  $s0, .L8001AE0C
/* 01BA00 8001AE00 3C04800E */   lui   $a0, %hi(D_800DC6F8) # $a0, 0x800e
/* 01BA04 8001AE04 0C030076 */  jal   transition_begin
/* 01BA08 8001AE08 2484C6F8 */   addiu $a0, %lo(D_800DC6F8) # addiu $a0, $a0, -0x3908
.L8001AE0C:
/* 01BA0C 8001AE0C 0C01BC50 */  jal   func_8006F140
/* 01BA10 8001AE10 24040002 */   li    $a0, 2
/* 01BA14 8001AE14 240B0005 */  li    $t3, 5
/* 01BA18 8001AE18 3C018012 */  lui   $at, %hi(D_8011AD50) # $at, 0x8012
/* 01BA1C 8001AE1C A02BAD50 */  sb    $t3, %lo(D_8011AD50)($at)
/* 01BA20 8001AE20 8E2A0010 */  lw    $t2, 0x10($s1)
/* 01BA24 8001AE24 3C010004 */  lui   $at, 4
/* 01BA28 8001AE28 01416025 */  or    $t4, $t2, $at
/* 01BA2C 8001AE2C AE2C0010 */  sw    $t4, 0x10($s1)
/* 01BA30 8001AE30 8FBF001C */  lw    $ra, 0x1c($sp)
.L8001AE34:
/* 01BA34 8001AE34 8FB00014 */  lw    $s0, 0x14($sp)
/* 01BA38 8001AE38 8FB10018 */  lw    $s1, 0x18($sp)
/* 01BA3C 8001AE3C 03E00008 */  jr    $ra
/* 01BA40 8001AE40 27BD0040 */   addiu $sp, $sp, 0x40

