glabel menu_magic_codes_list_loop
/* 08B528 8008A928 27BDFFA8 */  addiu $sp, $sp, -0x58
/* 08B52C 8008A92C 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 08B530 8008A930 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 08B534 8008A934 AFBF0024 */  sw    $ra, 0x24($sp)
/* 08B538 8008A938 AFB30020 */  sw    $s3, 0x20($sp)
/* 08B53C 8008A93C AFB2001C */  sw    $s2, 0x1c($sp)
/* 08B540 8008A940 AFB10018 */  sw    $s1, 0x18($sp)
/* 08B544 8008A944 AFB00014 */  sw    $s0, 0x14($sp)
/* 08B548 8008A948 1040000F */  beqz  $v0, .L8008A988
/* 08B54C 8008A94C AFA00048 */   sw    $zero, 0x48($sp)
/* 08B550 8008A950 18400008 */  blez  $v0, .L8008A974
/* 08B554 8008A954 00447823 */   subu  $t7, $v0, $a0
/* 08B558 8008A958 00447021 */  addu  $t6, $v0, $a0
/* 08B55C 8008A95C 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08B560 8008A960 AC2EF47C */  sw    $t6, %lo(gMenuDelay)($at)
/* 08B564 8008A964 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 08B568 8008A968 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 08B56C 8008A96C 10000006 */  b     .L8008A988
/* 08B570 8008A970 00000000 */   nop   
.L8008A974:
/* 08B574 8008A974 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08B578 8008A978 AC2FF47C */  sw    $t7, %lo(gMenuDelay)($at)
/* 08B57C 8008A97C 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 08B580 8008A980 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 08B584 8008A984 00000000 */  nop   
.L8008A988:
/* 08B588 8008A988 3C038012 */  lui   $v1, %hi(D_801263BC) # $v1, 0x8012
/* 08B58C 8008A98C 246363BC */  addiu $v1, %lo(D_801263BC) # addiu $v1, $v1, 0x63bc
/* 08B590 8008A990 8C780000 */  lw    $t8, ($v1)
/* 08B594 8008A994 2841FFED */  slti  $at, $v0, -0x13
/* 08B598 8008A998 0304C821 */  addu  $t9, $t8, $a0
/* 08B59C 8008A99C 3329003F */  andi  $t1, $t9, 0x3f
/* 08B5A0 8008A9A0 14200006 */  bnez  $at, .L8008A9BC
/* 08B5A4 8008A9A4 AC690000 */   sw    $t1, ($v1)
/* 08B5A8 8008A9A8 28410014 */  slti  $at, $v0, 0x14
/* 08B5AC 8008A9AC 10200003 */  beqz  $at, .L8008A9BC
/* 08B5B0 8008A9B0 00000000 */   nop   
/* 08B5B4 8008A9B4 0C02295B */  jal   render_magic_codes_list_menu_text
/* 08B5B8 8008A9B8 00000000 */   nop   
.L8008A9BC:
/* 08B5BC 8008A9BC 3C0A8012 */  lui   $t2, %hi(gIgnorePlayerInput) # $t2, 0x8012
/* 08B5C0 8008A9C0 8D4A63C4 */  lw    $t2, %lo(gIgnorePlayerInput)($t2)
/* 08B5C4 8008A9C4 00009825 */  move  $s3, $zero
/* 08B5C8 8008A9C8 00003025 */  move  $a2, $zero
/* 08B5CC 8008A9CC 1540001B */  bnez  $t2, .L8008AA3C
/* 08B5D0 8008A9D0 00009025 */   move  $s2, $zero
/* 08B5D4 8008A9D4 3C0B800E */  lui   $t3, %hi(gMenuDelay) # $t3, 0x800e
/* 08B5D8 8008A9D8 8D6BF47C */  lw    $t3, %lo(gMenuDelay)($t3)
/* 08B5DC 8008A9DC 00008025 */  move  $s0, $zero
/* 08B5E0 8008A9E0 15600016 */  bnez  $t3, .L8008AA3C
/* 08B5E4 8008A9E4 3C038012 */   lui   $v1, %hi(gControllersXAxisDirection) # $v1, 0x8012
/* 08B5E8 8008A9E8 3C058012 */  lui   $a1, %hi(gControllersYAxisDirection) # $a1, 0x8012
/* 08B5EC 8008A9EC 24A56464 */  addiu $a1, %lo(gControllersYAxisDirection) # addiu $a1, $a1, 0x6464
/* 08B5F0 8008A9F0 2463645C */  addiu $v1, %lo(gControllersXAxisDirection) # addiu $v1, $v1, 0x645c
/* 08B5F4 8008A9F4 24110004 */  li    $s1, 4
.L8008A9F8:
/* 08B5F8 8008A9F8 02002025 */  move  $a0, $s0
/* 08B5FC 8008A9FC AFA30030 */  sw    $v1, 0x30($sp)
/* 08B600 8008AA00 AFA5002C */  sw    $a1, 0x2c($sp)
/* 08B604 8008AA04 0C01A955 */  jal   get_buttons_pressed_from_player
/* 08B608 8008AA08 AFA60050 */   sw    $a2, 0x50($sp)
/* 08B60C 8008AA0C 8FA30030 */  lw    $v1, 0x30($sp)
/* 08B610 8008AA10 8FA5002C */  lw    $a1, 0x2c($sp)
/* 08B614 8008AA14 8FA60050 */  lw    $a2, 0x50($sp)
/* 08B618 8008AA18 806C0000 */  lb    $t4, ($v1)
/* 08B61C 8008AA1C 80AD0000 */  lb    $t5, ($a1)
/* 08B620 8008AA20 26100001 */  addiu $s0, $s0, 1
/* 08B624 8008AA24 02629825 */  or    $s3, $s3, $v0
/* 08B628 8008AA28 24630001 */  addiu $v1, $v1, 1
/* 08B62C 8008AA2C 24A50001 */  addiu $a1, $a1, 1
/* 08B630 8008AA30 00CC3021 */  addu  $a2, $a2, $t4
/* 08B634 8008AA34 1611FFF0 */  bne   $s0, $s1, .L8008A9F8
/* 08B638 8008AA38 024D9021 */   addu  $s2, $s2, $t5
.L8008AA3C:
/* 08B63C 8008AA3C 3C02800E */  lui   $v0, %hi(gUnlockedMagicCodes) # $v0, 0x800e
/* 08B640 8008AA40 3C088012 */  lui   $t0, %hi(D_80126C80) # $t0, 0x8012
/* 08B644 8008AA44 8C42FD9C */  lw    $v0, %lo(gUnlockedMagicCodes)($v0)
/* 08B648 8008AA48 25086C80 */  addiu $t0, %lo(D_80126C80) # addiu $t0, $t0, 0x6c80
/* 08B64C 8008AA4C 00008025 */  move  $s0, $zero
/* 08B650 8008AA50 24110001 */  li    $s1, 1
/* 08B654 8008AA54 00003825 */  move  $a3, $zero
/* 08B658 8008AA58 24030020 */  li    $v1, 32
.L8008AA5C:
/* 08B65C 8008AA5C 02227024 */  and   $t6, $s1, $v0
/* 08B660 8008AA60 11C00005 */  beqz  $t6, .L8008AA78
/* 08B664 8008AA64 0011C840 */   sll   $t9, $s1, 1
/* 08B668 8008AA68 00077840 */  sll   $t7, $a3, 1
/* 08B66C 8008AA6C 010FC021 */  addu  $t8, $t0, $t7
/* 08B670 8008AA70 A7100000 */  sh    $s0, ($t8)
/* 08B674 8008AA74 24E70001 */  addiu $a3, $a3, 1
.L8008AA78:
/* 08B678 8008AA78 26100001 */  addiu $s0, $s0, 1
/* 08B67C 8008AA7C 1603FFF7 */  bne   $s0, $v1, .L8008AA5C
/* 08B680 8008AA80 03208825 */   move  $s1, $t9
/* 08B684 8008AA84 04C00002 */  bltz  $a2, .L8008AA90
/* 08B688 8008AA88 3C108012 */   lui   $s0, %hi(gOptionsMenuItemIndex) # $s0, 0x8012
/* 08B68C 8008AA8C 18C00048 */  blez  $a2, .L8008ABB0
.L8008AA90:
/* 08B690 8008AA90 26106C46 */   addiu $s0, %lo(gOptionsMenuItemIndex) # addiu $s0, $s0, 0x6c46
/* 08B694 8008AA94 86090000 */  lh    $t1, ($s0)
/* 08B698 8008AA98 240400EF */  li    $a0, 239
/* 08B69C 8008AA9C 10E90044 */  beq   $a3, $t1, .L8008ABB0
/* 08B6A0 8008AAA0 00002825 */   move  $a1, $zero
/* 08B6A4 8008AAA4 0C000741 */  jal   func_80001D04
/* 08B6A8 8008AAA8 AFA7003C */   sw    $a3, 0x3c($sp)
/* 08B6AC 8008AAAC 860A0000 */  lh    $t2, ($s0)
/* 08B6B0 8008AAB0 3C088012 */  lui   $t0, %hi(D_80126C80) # $t0, 0x8012
/* 08B6B4 8008AAB4 25086C80 */  addiu $t0, %lo(D_80126C80) # addiu $t0, $t0, 0x6c80
/* 08B6B8 8008AAB8 000A5840 */  sll   $t3, $t2, 1
/* 08B6BC 8008AABC 3C02800E */  lui   $v0, %hi(gActiveMagicCodes) # $v0, 0x800e
/* 08B6C0 8008AAC0 010B6021 */  addu  $t4, $t0, $t3
/* 08B6C4 8008AAC4 858D0000 */  lh    $t5, ($t4)
/* 08B6C8 8008AAC8 2442FD98 */  addiu $v0, %lo(gActiveMagicCodes) # addiu $v0, $v0, -0x268
/* 08B6CC 8008AACC 8C4F0000 */  lw    $t7, ($v0)
/* 08B6D0 8008AAD0 240E0001 */  li    $t6, 1
/* 08B6D4 8008AAD4 01AE8804 */  sllv  $s1, $t6, $t5
/* 08B6D8 8008AAD8 01F1C026 */  xor   $t8, $t7, $s1
/* 08B6DC 8008AADC AC580000 */  sw    $t8, ($v0)
/* 08B6E0 8008AAE0 02202025 */  move  $a0, $s1
/* 08B6E4 8008AAE4 24050010 */  li    $a1, 16
/* 08B6E8 8008AAE8 0C022A3E */  jal   func_8008A8F8
/* 08B6EC 8008AAEC 24060020 */   li    $a2, 32
/* 08B6F0 8008AAF0 02202025 */  move  $a0, $s1
/* 08B6F4 8008AAF4 24050020 */  li    $a1, 32
/* 08B6F8 8008AAF8 0C022A3E */  jal   func_8008A8F8
/* 08B6FC 8008AAFC 24060010 */   li    $a2, 16
/* 08B700 8008AB00 02202025 */  move  $a0, $s1
/* 08B704 8008AB04 24051000 */  li    $a1, 4096
/* 08B708 8008AB08 0C022A3E */  jal   func_8008A8F8
/* 08B70C 8008AB0C 24066080 */   li    $a2, 24704
/* 08B710 8008AB10 02202025 */  move  $a0, $s1
/* 08B714 8008AB14 24056080 */  li    $a1, 24704
/* 08B718 8008AB18 0C022A3E */  jal   func_8008A8F8
/* 08B71C 8008AB1C 24061000 */   li    $a2, 4096
/* 08B720 8008AB20 3C06001F */  lui   $a2, (0x001F8000 >> 16) # lui $a2, 0x1f
/* 08B724 8008AB24 34C68000 */  ori   $a2, (0x001F8000 & 0xFFFF) # ori $a2, $a2, 0x8000
/* 08B728 8008AB28 02202025 */  move  $a0, $s1
/* 08B72C 8008AB2C 0C022A3E */  jal   func_8008A8F8
/* 08B730 8008AB30 24050800 */   li    $a1, 2048
/* 08B734 8008AB34 3C05001F */  lui   $a1, (0x001F8000 >> 16) # lui $a1, 0x1f
/* 08B738 8008AB38 34A58000 */  ori   $a1, (0x001F8000 & 0xFFFF) # ori $a1, $a1, 0x8000
/* 08B73C 8008AB3C 02202025 */  move  $a0, $s1
/* 08B740 8008AB40 0C022A3E */  jal   func_8008A8F8
/* 08B744 8008AB44 24060800 */   li    $a2, 2048
/* 08B748 8008AB48 02202025 */  move  $a0, $s1
/* 08B74C 8008AB4C 34058000 */  li    $a1, 32768
/* 08B750 8008AB50 0C022A3E */  jal   func_8008A8F8
/* 08B754 8008AB54 3C06000F */   lui   $a2, 0xf
/* 08B758 8008AB58 3C06000E */  lui   $a2, (0x000E8000 >> 16) # lui $a2, 0xe
/* 08B75C 8008AB5C 34C68000 */  ori   $a2, (0x000E8000 & 0xFFFF) # ori $a2, $a2, 0x8000
/* 08B760 8008AB60 02202025 */  move  $a0, $s1
/* 08B764 8008AB64 0C022A3E */  jal   func_8008A8F8
/* 08B768 8008AB68 3C050001 */   lui   $a1, 1
/* 08B76C 8008AB6C 3C06000D */  lui   $a2, (0x000D8000 >> 16) # lui $a2, 0xd
/* 08B770 8008AB70 34C68000 */  ori   $a2, (0x000D8000 & 0xFFFF) # ori $a2, $a2, 0x8000
/* 08B774 8008AB74 02202025 */  move  $a0, $s1
/* 08B778 8008AB78 0C022A3E */  jal   func_8008A8F8
/* 08B77C 8008AB7C 3C050002 */   lui   $a1, 2
/* 08B780 8008AB80 3C06000B */  lui   $a2, (0x000B8000 >> 16) # lui $a2, 0xb
/* 08B784 8008AB84 34C68000 */  ori   $a2, (0x000B8000 & 0xFFFF) # ori $a2, $a2, 0x8000
/* 08B788 8008AB88 02202025 */  move  $a0, $s1
/* 08B78C 8008AB8C 0C022A3E */  jal   func_8008A8F8
/* 08B790 8008AB90 3C050004 */   lui   $a1, 4
/* 08B794 8008AB94 3C060007 */  lui   $a2, (0x00078000 >> 16) # lui $a2, 7
/* 08B798 8008AB98 34C68000 */  ori   $a2, (0x00078000 & 0xFFFF) # ori $a2, $a2, 0x8000
/* 08B79C 8008AB9C 02202025 */  move  $a0, $s1
/* 08B7A0 8008ABA0 0C022A3E */  jal   func_8008A8F8
/* 08B7A4 8008ABA4 3C050008 */   lui   $a1, 8
/* 08B7A8 8008ABA8 8FA7003C */  lw    $a3, 0x3c($sp)
/* 08B7AC 8008ABAC 00000000 */  nop   
.L8008ABB0:
/* 08B7B0 8008ABB0 3C108012 */  lui   $s0, %hi(gOptionsMenuItemIndex) # $s0, 0x8012
/* 08B7B4 8008ABB4 26106C46 */  addiu $s0, %lo(gOptionsMenuItemIndex) # addiu $s0, $s0, 0x6c46
/* 08B7B8 8008ABB8 86020000 */  lh    $v0, ($s0)
/* 08B7BC 8008ABBC 0641000B */  bgez  $s2, .L8008ABEC
/* 08B7C0 8008ABC0 00403025 */   move  $a2, $v0
/* 08B7C4 8008ABC4 24590001 */  addiu $t9, $v0, 1
/* 08B7C8 8008ABC8 A6190000 */  sh    $t9, ($s0)
/* 08B7CC 8008ABCC 86020000 */  lh    $v0, ($s0)
/* 08B7D0 8008ABD0 00000000 */  nop   
/* 08B7D4 8008ABD4 00E2082A */  slt   $at, $a3, $v0
/* 08B7D8 8008ABD8 10200004 */  beqz  $at, .L8008ABEC
/* 08B7DC 8008ABDC 00000000 */   nop   
/* 08B7E0 8008ABE0 A6070000 */  sh    $a3, ($s0)
/* 08B7E4 8008ABE4 86020000 */  lh    $v0, ($s0)
/* 08B7E8 8008ABE8 00000000 */  nop   
.L8008ABEC:
/* 08B7EC 8008ABEC 1A40000A */  blez  $s2, .L8008AC18
/* 08B7F0 8008ABF0 3C058012 */   lui   $a1, %hi(D_801263E0) # $a1, 0x8012
/* 08B7F4 8008ABF4 2449FFFF */  addiu $t1, $v0, -1
/* 08B7F8 8008ABF8 A6090000 */  sh    $t1, ($s0)
/* 08B7FC 8008ABFC 86020000 */  lh    $v0, ($s0)
/* 08B800 8008AC00 00000000 */  nop   
/* 08B804 8008AC04 04410004 */  bgez  $v0, .L8008AC18
/* 08B808 8008AC08 00000000 */   nop   
/* 08B80C 8008AC0C A6000000 */  sh    $zero, ($s0)
/* 08B810 8008AC10 86020000 */  lh    $v0, ($s0)
/* 08B814 8008AC14 00000000 */  nop   
.L8008AC18:
/* 08B818 8008AC18 24A563E0 */  addiu $a1, %lo(D_801263E0) # addiu $a1, $a1, 0x63e0
/* 08B81C 8008AC1C 8CA30000 */  lw    $v1, ($a1)
/* 08B820 8008AC20 3C048012 */  lui   $a0, %hi(D_80126C70) # $a0, 0x8012
/* 08B824 8008AC24 0043082A */  slt   $at, $v0, $v1
/* 08B828 8008AC28 10200003 */  beqz  $at, .L8008AC38
/* 08B82C 8008AC2C 00000000 */   nop   
/* 08B830 8008AC30 10000009 */  b     .L8008AC58
/* 08B834 8008AC34 ACA20000 */   sw    $v0, ($a1)
.L8008AC38:
/* 08B838 8008AC38 8C846C70 */  lw    $a0, %lo(D_80126C70)($a0)
/* 08B83C 8008AC3C 00000000 */  nop   
/* 08B840 8008AC40 00645021 */  addu  $t2, $v1, $a0
/* 08B844 8008AC44 004A082A */  slt   $at, $v0, $t2
/* 08B848 8008AC48 14200003 */  bnez  $at, .L8008AC58
/* 08B84C 8008AC4C 00445823 */   subu  $t3, $v0, $a0
/* 08B850 8008AC50 256C0001 */  addiu $t4, $t3, 1
/* 08B854 8008AC54 ACAC0000 */  sw    $t4, ($a1)
.L8008AC58:
/* 08B858 8008AC58 10C20006 */  beq   $a2, $v0, .L8008AC74
/* 08B85C 8008AC5C 240400EB */   li    $a0, 235
/* 08B860 8008AC60 00002825 */  move  $a1, $zero
/* 08B864 8008AC64 0C000741 */  jal   func_80001D04
/* 08B868 8008AC68 AFA7003C */   sw    $a3, 0x3c($sp)
/* 08B86C 8008AC6C 8FA7003C */  lw    $a3, 0x3c($sp)
/* 08B870 8008AC70 00000000 */  nop   
.L8008AC74:
/* 08B874 8008AC74 326E9000 */  andi  $t6, $s3, 0x9000
/* 08B878 8008AC78 11C00006 */  beqz  $t6, .L8008AC94
/* 08B87C 8008AC7C 32784000 */   andi  $t8, $s3, 0x4000
/* 08B880 8008AC80 860D0000 */  lh    $t5, ($s0)
/* 08B884 8008AC84 240FFFFF */  li    $t7, -1
/* 08B888 8008AC88 14ED0002 */  bne   $a3, $t5, .L8008AC94
/* 08B88C 8008AC8C 00000000 */   nop   
/* 08B890 8008AC90 AFAF0048 */  sw    $t7, 0x48($sp)
.L8008AC94:
/* 08B894 8008AC94 13000002 */  beqz  $t8, .L8008ACA0
/* 08B898 8008AC98 2419FFFF */   li    $t9, -1
/* 08B89C 8008AC9C AFB90048 */  sw    $t9, 0x48($sp)
.L8008ACA0:
/* 08B8A0 8008ACA0 8FA90048 */  lw    $t1, 0x48($sp)
/* 08B8A4 8008ACA4 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08B8A8 8008ACA8 11200007 */  beqz  $t1, .L8008ACC8
/* 08B8AC 8008ACAC 3C04800E */   lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 08B8B0 8008ACB0 AC29F47C */  sw    $t1, %lo(gMenuDelay)($at)
/* 08B8B4 8008ACB4 0C030076 */  jal   func_800C01D8
/* 08B8B8 8008ACB8 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 08B8BC 8008ACBC 24040241 */  li    $a0, 577
/* 08B8C0 8008ACC0 0C000741 */  jal   func_80001D04
/* 08B8C4 8008ACC4 00002825 */   move  $a1, $zero
.L8008ACC8:
/* 08B8C8 8008ACC8 3C0A800E */  lui   $t2, %hi(gMenuDelay) # $t2, 0x800e
/* 08B8CC 8008ACCC 8D4AF47C */  lw    $t2, %lo(gMenuDelay)($t2)
/* 08B8D0 8008ACD0 00001025 */  move  $v0, $zero
/* 08B8D4 8008ACD4 2941FFE2 */  slti  $at, $t2, -0x1e
/* 08B8D8 8008ACD8 10200007 */  beqz  $at, .L8008ACF8
/* 08B8DC 8008ACDC 00000000 */   nop   
/* 08B8E0 8008ACE0 0C022B47 */  jal   func_8008AD1C
/* 08B8E4 8008ACE4 00000000 */   nop   
/* 08B8E8 8008ACE8 0C0204F4 */  jal   menu_init
/* 08B8EC 8008ACEC 2404000A */   li    $a0, 10
/* 08B8F0 8008ACF0 10000003 */  b     .L8008AD00
/* 08B8F4 8008ACF4 00001025 */   move  $v0, $zero
.L8008ACF8:
/* 08B8F8 8008ACF8 3C018012 */  lui   $at, %hi(gIgnorePlayerInput) # $at, 0x8012
/* 08B8FC 8008ACFC AC2063C4 */  sw    $zero, %lo(gIgnorePlayerInput)($at)
.L8008AD00:
/* 08B900 8008AD00 8FBF0024 */  lw    $ra, 0x24($sp)
/* 08B904 8008AD04 8FB00014 */  lw    $s0, 0x14($sp)
/* 08B908 8008AD08 8FB10018 */  lw    $s1, 0x18($sp)
/* 08B90C 8008AD0C 8FB2001C */  lw    $s2, 0x1c($sp)
/* 08B910 8008AD10 8FB30020 */  lw    $s3, 0x20($sp)
/* 08B914 8008AD14 03E00008 */  jr    $ra
/* 08B918 8008AD18 27BD0058 */   addiu $sp, $sp, 0x58

