glabel menu_ghost_data_loop
/* 09B3D4 8009A7D4 3C038012 */  lui   $v1, %hi(D_801263BC) # $v1, 0x8012
/* 09B3D8 8009A7D8 246363BC */  addiu $v1, %lo(D_801263BC) # addiu $v1, $v1, 0x63bc
/* 09B3DC 8009A7DC 3C09800E */  lui   $t1, %hi(gMenuDelay) # $t1, 0x800e
/* 09B3E0 8009A7E0 8C6E0000 */  lw    $t6, ($v1)
/* 09B3E4 8009A7E4 2529F47C */  addiu $t1, %lo(gMenuDelay) # addiu $t1, $t1, -0xb84
/* 09B3E8 8009A7E8 8D220000 */  lw    $v0, ($t1)
/* 09B3EC 8009A7EC 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 09B3F0 8009A7F0 01C47821 */  addu  $t7, $t6, $a0
/* 09B3F4 8009A7F4 AFB00018 */  sw    $s0, 0x18($sp)
/* 09B3F8 8009A7F8 31F8003F */  andi  $t8, $t7, 0x3f
/* 09B3FC 8009A7FC 2841FFED */  slti  $at, $v0, -0x13
/* 09B400 8009A800 00808025 */  move  $s0, $a0
/* 09B404 8009A804 AFBF001C */  sw    $ra, 0x1c($sp)
/* 09B408 8009A808 1420000A */  bnez  $at, .L8009A834
/* 09B40C 8009A80C AC780000 */   sw    $t8, ($v1)
/* 09B410 8009A810 28410014 */  slti  $at, $v0, 0x14
/* 09B414 8009A814 10200007 */  beqz  $at, .L8009A834
/* 09B418 8009A818 00000000 */   nop   
/* 09B41C 8009A81C 0C0267A3 */  jal   func_80099E8C
/* 09B420 8009A820 00000000 */   nop   
/* 09B424 8009A824 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 09B428 8009A828 3C09800E */  lui   $t1, %hi(gMenuDelay) # $t1, 0x800e
/* 09B42C 8009A82C 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 09B430 8009A830 2529F47C */  addiu $t1, %lo(gMenuDelay) # addiu $t1, $t1, -0xb84
.L8009A834:
/* 09B434 8009A834 10400007 */  beqz  $v0, .L8009A854
/* 09B438 8009A838 00003825 */   move  $a3, $zero
/* 09B43C 8009A83C 04410004 */  bgez  $v0, .L8009A850
/* 09B440 8009A840 00505021 */   addu  $t2, $v0, $s0
/* 09B444 8009A844 0050C823 */  subu  $t9, $v0, $s0
/* 09B448 8009A848 10000002 */  b     .L8009A854
/* 09B44C 8009A84C AD390000 */   sw    $t9, ($t1)
.L8009A850:
/* 09B450 8009A850 AD2A0000 */  sw    $t2, ($t1)
.L8009A854:
/* 09B454 8009A854 3C0B8012 */  lui   $t3, %hi(gIgnorePlayerInput) # $t3, 0x8012
/* 09B458 8009A858 8D6B63C4 */  lw    $t3, %lo(gIgnorePlayerInput)($t3)
/* 09B45C 8009A85C 00003025 */  move  $a2, $zero
/* 09B460 8009A860 15600020 */  bnez  $t3, .L8009A8E4
/* 09B464 8009A864 00004025 */   move  $t0, $zero
/* 09B468 8009A868 8D2C0000 */  lw    $t4, ($t1)
/* 09B46C 8009A86C 00008025 */  move  $s0, $zero
/* 09B470 8009A870 1580001C */  bnez  $t4, .L8009A8E4
/* 09B474 8009A874 3C038012 */   lui   $v1, %hi(gControllersXAxisDirection) # $v1, 0x8012
/* 09B478 8009A878 3C058012 */  lui   $a1, %hi(gControllersYAxisDirection) # $a1, 0x8012
/* 09B47C 8009A87C 24A56464 */  addiu $a1, %lo(gControllersYAxisDirection) # addiu $a1, $a1, 0x6464
/* 09B480 8009A880 2463645C */  addiu $v1, %lo(gControllersXAxisDirection) # addiu $v1, $v1, 0x645c
.L8009A884:
/* 09B484 8009A884 02002025 */  move  $a0, $s0
/* 09B488 8009A888 AFA30028 */  sw    $v1, 0x28($sp)
/* 09B48C 8009A88C AFA50024 */  sw    $a1, 0x24($sp)
/* 09B490 8009A890 AFA6003C */  sw    $a2, 0x3c($sp)
/* 09B494 8009A894 AFA70040 */  sw    $a3, 0x40($sp)
/* 09B498 8009A898 0C01A955 */  jal   get_buttons_pressed_from_player
/* 09B49C 8009A89C AFA80038 */   sw    $t0, 0x38($sp)
/* 09B4A0 8009A8A0 8FA30028 */  lw    $v1, 0x28($sp)
/* 09B4A4 8009A8A4 8FA50024 */  lw    $a1, 0x24($sp)
/* 09B4A8 8009A8A8 8FA6003C */  lw    $a2, 0x3c($sp)
/* 09B4AC 8009A8AC 8FA70040 */  lw    $a3, 0x40($sp)
/* 09B4B0 8009A8B0 8FA80038 */  lw    $t0, 0x38($sp)
/* 09B4B4 8009A8B4 806D0000 */  lb    $t5, ($v1)
/* 09B4B8 8009A8B8 80AE0000 */  lb    $t6, ($a1)
/* 09B4BC 8009A8BC 26100001 */  addiu $s0, $s0, 1
/* 09B4C0 8009A8C0 24010004 */  li    $at, 4
/* 09B4C4 8009A8C4 24630001 */  addiu $v1, $v1, 1
/* 09B4C8 8009A8C8 24A50001 */  addiu $a1, $a1, 1
/* 09B4CC 8009A8CC 00E23825 */  or    $a3, $a3, $v0
/* 09B4D0 8009A8D0 00CD3021 */  addu  $a2, $a2, $t5
/* 09B4D4 8009A8D4 1601FFEB */  bne   $s0, $at, .L8009A884
/* 09B4D8 8009A8D8 010E4021 */   addu  $t0, $t0, $t6
/* 09B4DC 8009A8DC 3C09800E */  lui   $t1, %hi(gMenuDelay) # $t1, 0x800e
/* 09B4E0 8009A8E0 2529F47C */  addiu $t1, %lo(gMenuDelay) # addiu $t1, $t1, -0xb84
.L8009A8E4:
/* 09B4E4 8009A8E4 3C068012 */  lui   $a2, %hi(D_801263E0) # $a2, 0x8012
/* 09B4E8 8009A8E8 24C663E0 */  addiu $a2, %lo(D_801263E0) # addiu $a2, $a2, 0x63e0
/* 09B4EC 8009A8EC 8CC20000 */  lw    $v0, ($a2)
/* 09B4F0 8009A8F0 24030001 */  li    $v1, 1
/* 09B4F4 8009A8F4 1040000A */  beqz  $v0, .L8009A920
/* 09B4F8 8009A8F8 00000000 */   nop   
/* 09B4FC 8009A8FC 1043004E */  beq   $v0, $v1, .L8009AA38
/* 09B500 8009A900 30EB4000 */   andi  $t3, $a3, 0x4000
/* 09B504 8009A904 24010002 */  li    $at, 2
/* 09B508 8009A908 1041008B */  beq   $v0, $at, .L8009AB38
/* 09B50C 8009A90C 30F8D000 */   andi  $t8, $a3, 0xd000
/* 09B510 8009A910 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 09B514 8009A914 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 09B518 8009A918 10000096 */  b     .L8009AB74
/* 09B51C 8009A91C 00000000 */   nop   
.L8009A920:
/* 09B520 8009A920 30E29000 */  andi  $v0, $a3, 0x9000
/* 09B524 8009A924 1040000B */  beqz  $v0, .L8009A954
/* 09B528 8009A928 3C058012 */   lui   $a1, %hi(D_801264D4) # $a1, 0x8012
/* 09B52C 8009A92C 24A564D4 */  addiu $a1, %lo(D_801264D4) # addiu $a1, $a1, 0x64d4
/* 09B530 8009A930 8CAF0000 */  lw    $t7, ($a1)
/* 09B534 8009A934 24180002 */  li    $t8, 2
/* 09B538 8009A938 19E00006 */  blez  $t7, .L8009A954
/* 09B53C 8009A93C 240400EF */   li    $a0, 239
/* 09B540 8009A940 ACD80000 */  sw    $t8, ($a2)
/* 09B544 8009A944 0C000741 */  jal   func_80001D04
/* 09B548 8009A948 00002825 */   move  $a1, $zero
/* 09B54C 8009A94C 10000036 */  b     .L8009AA28
/* 09B550 8009A950 00000000 */   nop   
.L8009A954:
/* 09B554 8009A954 3C058012 */  lui   $a1, %hi(D_801264D4) # $a1, 0x8012
/* 09B558 8009A958 30F94000 */  andi  $t9, $a3, 0x4000
/* 09B55C 8009A95C 17200006 */  bnez  $t9, .L8009A978
/* 09B560 8009A960 24A564D4 */   addiu $a1, %lo(D_801264D4) # addiu $a1, $a1, 0x64d4
/* 09B564 8009A964 1040000E */  beqz  $v0, .L8009A9A0
/* 09B568 8009A968 3C108012 */   lui   $s0, %hi(D_80126498) # $s0, 0x8012
/* 09B56C 8009A96C 8CAA0000 */  lw    $t2, ($a1)
/* 09B570 8009A970 00000000 */  nop   
/* 09B574 8009A974 1540000A */  bnez  $t2, .L8009A9A0
.L8009A978:
/* 09B578 8009A978 24030001 */   li    $v1, 1
/* 09B57C 8009A97C 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 09B580 8009A980 AD230000 */  sw    $v1, ($t1)
/* 09B584 8009A984 0C030076 */  jal   func_800C01D8
/* 09B588 8009A988 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 09B58C 8009A98C 24040241 */  li    $a0, 577
/* 09B590 8009A990 0C000741 */  jal   func_80001D04
/* 09B594 8009A994 00002825 */   move  $a1, $zero
/* 09B598 8009A998 10000023 */  b     .L8009AA28
/* 09B59C 8009A99C 00000000 */   nop   
.L8009A9A0:
/* 09B5A0 8009A9A0 26106498 */  addiu $s0, %lo(D_80126498) # addiu $s0, $s0, 0x6498
/* 09B5A4 8009A9A4 8E020000 */  lw    $v0, ($s0)
/* 09B5A8 8009A9A8 05010010 */  bgez  $t0, .L8009A9EC
/* 09B5AC 8009A9AC 00402025 */   move  $a0, $v0
/* 09B5B0 8009A9B0 8CAB0000 */  lw    $t3, ($a1)
/* 09B5B4 8009A9B4 3C038012 */  lui   $v1, %hi(D_801263D8) # $v1, 0x8012
/* 09B5B8 8009A9B8 256CFFFF */  addiu $t4, $t3, -1
/* 09B5BC 8009A9BC 004C082A */  slt   $at, $v0, $t4
/* 09B5C0 8009A9C0 1020000A */  beqz  $at, .L8009A9EC
/* 09B5C4 8009A9C4 246363D8 */   addiu $v1, %lo(D_801263D8) # addiu $v1, $v1, 0x63d8
/* 09B5C8 8009A9C8 8C6E0000 */  lw    $t6, ($v1)
/* 09B5CC 8009A9CC 244D0001 */  addiu $t5, $v0, 1
/* 09B5D0 8009A9D0 25CF0003 */  addiu $t7, $t6, 3
/* 09B5D4 8009A9D4 01AF082A */  slt   $at, $t5, $t7
/* 09B5D8 8009A9D8 AE0D0000 */  sw    $t5, ($s0)
/* 09B5DC 8009A9DC 14200003 */  bnez  $at, .L8009A9EC
/* 09B5E0 8009A9E0 01A01025 */   move  $v0, $t5
/* 09B5E4 8009A9E4 25B8FFFE */  addiu $t8, $t5, -2
/* 09B5E8 8009A9E8 AC780000 */  sw    $t8, ($v1)
.L8009A9EC:
/* 09B5EC 8009A9EC 3C038012 */  lui   $v1, %hi(D_801263D8) # $v1, 0x8012
/* 09B5F0 8009A9F0 19000009 */  blez  $t0, .L8009AA18
/* 09B5F4 8009A9F4 246363D8 */   addiu $v1, %lo(D_801263D8) # addiu $v1, $v1, 0x63d8
/* 09B5F8 8009A9F8 18400007 */  blez  $v0, .L8009AA18
/* 09B5FC 8009A9FC 2459FFFF */   addiu $t9, $v0, -1
/* 09B600 8009AA00 8C6A0000 */  lw    $t2, ($v1)
/* 09B604 8009AA04 AE190000 */  sw    $t9, ($s0)
/* 09B608 8009AA08 032A082A */  slt   $at, $t9, $t2
/* 09B60C 8009AA0C 10200002 */  beqz  $at, .L8009AA18
/* 09B610 8009AA10 03201025 */   move  $v0, $t9
/* 09B614 8009AA14 AC790000 */  sw    $t9, ($v1)
.L8009AA18:
/* 09B618 8009AA18 10820003 */  beq   $a0, $v0, .L8009AA28
/* 09B61C 8009AA1C 00002825 */   move  $a1, $zero
/* 09B620 8009AA20 0C000741 */  jal   func_80001D04
/* 09B624 8009AA24 240400EB */   li    $a0, 235
.L8009AA28:
/* 09B628 8009AA28 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 09B62C 8009AA2C 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 09B630 8009AA30 10000050 */  b     .L8009AB74
/* 09B634 8009AA34 00000000 */   nop   
.L8009AA38:
/* 09B638 8009AA38 11600007 */  beqz  $t3, .L8009AA58
/* 09B63C 8009AA3C 30EC9000 */   andi  $t4, $a3, 0x9000
/* 09B640 8009AA40 ACC00000 */  sw    $zero, ($a2)
/* 09B644 8009AA44 24040241 */  li    $a0, 577
/* 09B648 8009AA48 0C000741 */  jal   func_80001D04
/* 09B64C 8009AA4C 00002825 */   move  $a1, $zero
/* 09B650 8009AA50 10000035 */  b     .L8009AB28
/* 09B654 8009AA54 00000000 */   nop   
.L8009AA58:
/* 09B658 8009AA58 1180002D */  beqz  $t4, .L8009AB10
/* 09B65C 8009AA5C 3C108012 */   lui   $s0, %hi(D_80126498) # $s0, 0x8012
/* 09B660 8009AA60 26106498 */  addiu $s0, %lo(D_80126498) # addiu $s0, $s0, 0x6498
/* 09B664 8009AA64 8E040000 */  lw    $a0, ($s0)
/* 09B668 8009AA68 0C026638 */  jal   func_800998E0
/* 09B66C 8009AA6C 00000000 */   nop   
/* 09B670 8009AA70 1440001B */  bnez  $v0, .L8009AAE0
/* 09B674 8009AA74 24030001 */   li    $v1, 1
/* 09B678 8009AA78 3C058012 */  lui   $a1, %hi(D_801264D4) # $a1, 0x8012
/* 09B67C 8009AA7C 24A564D4 */  addiu $a1, %lo(D_801264D4) # addiu $a1, $a1, 0x64d4
/* 09B680 8009AA80 8CA30000 */  lw    $v1, ($a1)
/* 09B684 8009AA84 8E020000 */  lw    $v0, ($s0)
/* 09B688 8009AA88 240400EF */  li    $a0, 239
/* 09B68C 8009AA8C 0043082A */  slt   $at, $v0, $v1
/* 09B690 8009AA90 14200003 */  bnez  $at, .L8009AAA0
/* 09B694 8009AA94 00000000 */   nop   
/* 09B698 8009AA98 2462FFFF */  addiu $v0, $v1, -1
/* 09B69C 8009AA9C AE020000 */  sw    $v0, ($s0)
.L8009AAA0:
/* 09B6A0 8009AAA0 04410003 */  bgez  $v0, .L8009AAB0
/* 09B6A4 8009AAA4 3C038012 */   lui   $v1, %hi(D_801263D8) # $v1, 0x8012
/* 09B6A8 8009AAA8 AE000000 */  sw    $zero, ($s0)
/* 09B6AC 8009AAAC 00001025 */  move  $v0, $zero
.L8009AAB0:
/* 09B6B0 8009AAB0 246363D8 */  addiu $v1, %lo(D_801263D8) # addiu $v1, $v1, 0x63d8
/* 09B6B4 8009AAB4 8C6E0000 */  lw    $t6, ($v1)
/* 09B6B8 8009AAB8 00000000 */  nop   
/* 09B6BC 8009AABC 004E082A */  slt   $at, $v0, $t6
/* 09B6C0 8009AAC0 10200002 */  beqz  $at, .L8009AACC
/* 09B6C4 8009AAC4 00000000 */   nop   
/* 09B6C8 8009AAC8 AC620000 */  sw    $v0, ($v1)
.L8009AACC:
/* 09B6CC 8009AACC 0C000741 */  jal   func_80001D04
/* 09B6D0 8009AAD0 00002825 */   move  $a1, $zero
/* 09B6D4 8009AAD4 3C068012 */  lui   $a2, %hi(D_801263E0) # $a2, 0x8012
/* 09B6D8 8009AAD8 1000000B */  b     .L8009AB08
/* 09B6DC 8009AADC 24C663E0 */   addiu $a2, %lo(D_801263E0) # addiu $a2, $a2, 0x63e0
.L8009AAE0:
/* 09B6E0 8009AAE0 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 09B6E4 8009AAE4 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 09B6E8 8009AAE8 AC23F47C */  sw    $v1, %lo(gMenuDelay)($at)
/* 09B6EC 8009AAEC 0C030076 */  jal   func_800C01D8
/* 09B6F0 8009AAF0 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 09B6F4 8009AAF4 24040241 */  li    $a0, 577
/* 09B6F8 8009AAF8 0C000741 */  jal   func_80001D04
/* 09B6FC 8009AAFC 00002825 */   move  $a1, $zero
/* 09B700 8009AB00 3C068012 */  lui   $a2, %hi(D_801263E0) # $a2, 0x8012
/* 09B704 8009AB04 24C663E0 */  addiu $a2, %lo(D_801263E0) # addiu $a2, $a2, 0x63e0
.L8009AB08:
/* 09B708 8009AB08 10000007 */  b     .L8009AB28
/* 09B70C 8009AB0C ACC00000 */   sw    $zero, ($a2)
.L8009AB10:
/* 09B710 8009AB10 05010005 */  bgez  $t0, .L8009AB28
/* 09B714 8009AB14 240F0002 */   li    $t7, 2
/* 09B718 8009AB18 ACCF0000 */  sw    $t7, ($a2)
/* 09B71C 8009AB1C 240400EB */  li    $a0, 235
/* 09B720 8009AB20 0C000741 */  jal   func_80001D04
/* 09B724 8009AB24 00002825 */   move  $a1, $zero
.L8009AB28:
/* 09B728 8009AB28 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 09B72C 8009AB2C 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 09B730 8009AB30 10000010 */  b     .L8009AB74
/* 09B734 8009AB34 00000000 */   nop   
.L8009AB38:
/* 09B738 8009AB38 13000006 */  beqz  $t8, .L8009AB54
/* 09B73C 8009AB3C 24040241 */   li    $a0, 577
/* 09B740 8009AB40 ACC00000 */  sw    $zero, ($a2)
/* 09B744 8009AB44 0C000741 */  jal   func_80001D04
/* 09B748 8009AB48 00002825 */   move  $a1, $zero
/* 09B74C 8009AB4C 10000006 */  b     .L8009AB68
/* 09B750 8009AB50 00000000 */   nop   
.L8009AB54:
/* 09B754 8009AB54 19000004 */  blez  $t0, .L8009AB68
/* 09B758 8009AB58 240400EB */   li    $a0, 235
/* 09B75C 8009AB5C ACC30000 */  sw    $v1, ($a2)
/* 09B760 8009AB60 0C000741 */  jal   func_80001D04
/* 09B764 8009AB64 00002825 */   move  $a1, $zero
.L8009AB68:
/* 09B768 8009AB68 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 09B76C 8009AB6C 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 09B770 8009AB70 00000000 */  nop   
.L8009AB74:
/* 09B774 8009AB74 3C018012 */  lui   $at, %hi(gIgnorePlayerInput) # $at, 0x8012
/* 09B778 8009AB78 AC2063C4 */  sw    $zero, %lo(gIgnorePlayerInput)($at)
/* 09B77C 8009AB7C 2841001F */  slti  $at, $v0, 0x1f
/* 09B780 8009AB80 14200006 */  bnez  $at, .L8009AB9C
/* 09B784 8009AB84 8FBF001C */   lw    $ra, 0x1c($sp)
/* 09B788 8009AB88 0C026AEB */  jal   func_8009ABAC
/* 09B78C 8009AB8C 00000000 */   nop   
/* 09B790 8009AB90 0C0204F4 */  jal   menu_init
/* 09B794 8009AB94 2404000E */   li    $a0, 14
/* 09B798 8009AB98 8FBF001C */  lw    $ra, 0x1c($sp)
.L8009AB9C:
/* 09B79C 8009AB9C 8FB00018 */  lw    $s0, 0x18($sp)
/* 09B7A0 8009ABA0 27BD0048 */  addiu $sp, $sp, 0x48
/* 09B7A4 8009ABA4 03E00008 */  jr    $ra
/* 09B7A8 8009ABA8 00001025 */   move  $v0, $zero

