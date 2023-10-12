glabel func_8007CA68
/* 07D668 8007CA68 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 07D66C 8007CA6C AFB1001C */  sw    $s1, 0x1c($sp)
/* 07D670 8007CA70 AFB00018 */  sw    $s0, 0x18($sp)
/* 07D674 8007CA74 00808025 */  move  $s0, $a0
/* 07D678 8007CA78 00A08825 */  move  $s1, $a1
/* 07D67C 8007CA7C AFBF003C */  sw    $ra, 0x3c($sp)
/* 07D680 8007CA80 AFBE0038 */  sw    $fp, 0x38($sp)
/* 07D684 8007CA84 AFB70034 */  sw    $s7, 0x34($sp)
/* 07D688 8007CA88 AFB60030 */  sw    $s6, 0x30($sp)
/* 07D68C 8007CA8C AFB5002C */  sw    $s5, 0x2c($sp)
/* 07D690 8007CA90 AFB40028 */  sw    $s4, 0x28($sp)
/* 07D694 8007CA94 AFB30024 */  sw    $s3, 0x24($sp)
/* 07D698 8007CA98 AFB20020 */  sw    $s2, 0x20($sp)
/* 07D69C 8007CA9C AFA60048 */  sw    $a2, 0x48($sp)
/* 07D6A0 8007CAA0 04800007 */  bltz  $a0, .L8007CAC0
/* 07D6A4 8007CAA4 AFA7004C */   sw    $a3, 0x4c($sp)
/* 07D6A8 8007CAA8 3C0E8012 */  lui   $t6, %hi(gSpriteTableNum) # $t6, 0x8012
/* 07D6AC 8007CAAC 8DCE6354 */  lw    $t6, %lo(gSpriteTableNum)($t6)
/* 07D6B0 8007CAB0 3C198012 */  lui   $t9, %hi(gSpriteOffsetTable) # $t9, 0x8012
/* 07D6B4 8007CAB4 008E082A */  slt   $at, $a0, $t6
/* 07D6B8 8007CAB8 14200007 */  bnez  $at, .L8007CAD8
/* 07D6BC 8007CABC 00104080 */   sll   $t0, $s0, 2
.L8007CAC0:
/* 07D6C0 8007CAC0 8FAF0048 */  lw    $t7, 0x48($sp)
/* 07D6C4 8007CAC4 00000000 */  nop   
/* 07D6C8 8007CAC8 ADE00000 */  sw    $zero, ($t7)
/* 07D6CC 8007CACC 8FB8004C */  lw    $t8, 0x4c($sp)
/* 07D6D0 8007CAD0 1000006B */  b     .L8007CC80
/* 07D6D4 8007CAD4 AF000000 */   sw    $zero, ($t8)
.L8007CAD8:
/* 07D6D8 8007CAD8 8F396348 */  lw    $t9, %lo(gSpriteOffsetTable)($t9)
/* 07D6DC 8007CADC 3C128012 */  lui   $s2, %hi(gCurrentSprite) # $s2, 0x8012
/* 07D6E0 8007CAE0 03281021 */  addu  $v0, $t9, $t0
/* 07D6E4 8007CAE4 8C460000 */  lw    $a2, ($v0)
/* 07D6E8 8007CAE8 8C490004 */  lw    $t1, 4($v0)
/* 07D6EC 8007CAEC 8E526350 */  lw    $s2, %lo(gCurrentSprite)($s2)
/* 07D6F0 8007CAF0 2404000C */  li    $a0, 12
/* 07D6F4 8007CAF4 01263823 */  subu  $a3, $t1, $a2
/* 07D6F8 8007CAF8 0C01DB9A */  jal   load_asset_to_address
/* 07D6FC 8007CAFC 02402825 */   move  $a1, $s2
/* 07D700 8007CB00 864A0002 */  lh    $t2, 2($s2)
/* 07D704 8007CB04 8FB70050 */  lw    $s7, 0x50($sp)
/* 07D708 8007CB08 0151082A */  slt   $at, $t2, $s1
/* 07D70C 8007CB0C 10200009 */  beqz  $at, .L8007CB34
/* 07D710 8007CB10 0251F021 */   addu  $fp, $s2, $s1
.L8007CB14:
/* 07D714 8007CB14 8FAB0048 */  lw    $t3, 0x48($sp)
.L8007CB18:
/* 07D718 8007CB18 00000000 */  nop   
/* 07D71C 8007CB1C AD600000 */  sw    $zero, ($t3)
/* 07D720 8007CB20 8FAC004C */  lw    $t4, 0x4c($sp)
/* 07D724 8007CB24 00000000 */  nop   
/* 07D728 8007CB28 AD800000 */  sw    $zero, ($t4)
/* 07D72C 8007CB2C 10000054 */  b     .L8007CC80
/* 07D730 8007CB30 AEE00000 */   sw    $zero, ($s7)
.L8007CB34:
/* 07D734 8007CB34 93CD000C */  lbu   $t5, 0xc($fp)
/* 07D738 8007CB38 864E0000 */  lh    $t6, ($s2)
/* 07D73C 8007CB3C 0C01EB9D */  jal   load_texture
/* 07D740 8007CB40 01AE2021 */   addu  $a0, $t5, $t6
/* 07D744 8007CB44 14400004 */  bnez  $v0, .L8007CB58
/* 07D748 8007CB48 00408025 */   move  $s0, $v0
/* 07D74C 8007CB4C 8FB70050 */  lw    $s7, 0x50($sp)
/* 07D750 8007CB50 1000FFF1 */  b     .L8007CB18
/* 07D754 8007CB54 8FAB0048 */   lw    $t3, 0x48($sp)
.L8007CB58:
/* 07D758 8007CB58 93CF000C */  lbu   $t7, 0xc($fp)
/* 07D75C 8007CB5C 86580000 */  lh    $t8, ($s2)
/* 07D760 8007CB60 0C01F15F */  jal   get_texture_size_from_id
/* 07D764 8007CB64 01F82021 */   addu  $a0, $t7, $t8
/* 07D768 8007CB68 8FB70050 */  lw    $s7, 0x50($sp)
/* 07D76C 8007CB6C 02002025 */  move  $a0, $s0
/* 07D770 8007CB70 AEE20000 */  sw    $v0, ($s7)
/* 07D774 8007CB74 86480004 */  lh    $t0, 4($s2)
/* 07D778 8007CB78 82190003 */  lb    $t9, 3($s0)
/* 07D77C 8007CB7C 820A0004 */  lb    $t2, 4($s0)
/* 07D780 8007CB80 86490006 */  lh    $t1, 6($s2)
/* 07D784 8007CB84 92050000 */  lbu   $a1, ($s0)
/* 07D788 8007CB88 92060001 */  lbu   $a2, 1($s0)
/* 07D78C 8007CB8C 03289823 */  subu  $s3, $t9, $t0
/* 07D790 8007CB90 012AA023 */  subu  $s4, $t1, $t2
/* 07D794 8007CB94 0265A821 */  addu  $s5, $s3, $a1
/* 07D798 8007CB98 0C01ECAF */  jal   free_texture
/* 07D79C 8007CB9C 0286B023 */   subu  $s6, $s4, $a2
/* 07D7A0 8007CBA0 93D1000C */  lbu   $s1, 0xc($fp)
/* 07D7A4 8007CBA4 93CB000D */  lbu   $t3, 0xd($fp)
/* 07D7A8 8007CBA8 26310001 */  addiu $s1, $s1, 1
/* 07D7AC 8007CBAC 022B082A */  slt   $at, $s1, $t3
/* 07D7B0 8007CBB0 1020002E */  beqz  $at, .L8007CC6C
/* 07D7B4 8007CBB4 8FAC0048 */   lw    $t4, 0x48($sp)
.L8007CBB8:
/* 07D7B8 8007CBB8 864C0000 */  lh    $t4, ($s2)
/* 07D7BC 8007CBBC 0C01EB9D */  jal   load_texture
/* 07D7C0 8007CBC0 01912021 */   addu  $a0, $t4, $s1
/* 07D7C4 8007CBC4 1040FFD3 */  beqz  $v0, .L8007CB14
/* 07D7C8 8007CBC8 00408025 */   move  $s0, $v0
/* 07D7CC 8007CBCC 864D0000 */  lh    $t5, ($s2)
/* 07D7D0 8007CBD0 0C01F15F */  jal   get_texture_size_from_id
/* 07D7D4 8007CBD4 01B12021 */   addu  $a0, $t5, $s1
/* 07D7D8 8007CBD8 8EEE0000 */  lw    $t6, ($s7)
/* 07D7DC 8007CBDC 00000000 */  nop   
/* 07D7E0 8007CBE0 01C27821 */  addu  $t7, $t6, $v0
/* 07D7E4 8007CBE4 AEEF0000 */  sw    $t7, ($s7)
/* 07D7E8 8007CBE8 86590004 */  lh    $t9, 4($s2)
/* 07D7EC 8007CBEC 82180003 */  lb    $t8, 3($s0)
/* 07D7F0 8007CBF0 82090004 */  lb    $t1, 4($s0)
/* 07D7F4 8007CBF4 86480006 */  lh    $t0, 6($s2)
/* 07D7F8 8007CBF8 03191823 */  subu  $v1, $t8, $t9
/* 07D7FC 8007CBFC 92050000 */  lbu   $a1, ($s0)
/* 07D800 8007CC00 92060001 */  lbu   $a2, 1($s0)
/* 07D804 8007CC04 0073082A */  slt   $at, $v1, $s3
/* 07D808 8007CC08 10200002 */  beqz  $at, .L8007CC14
/* 07D80C 8007CC0C 01092023 */   subu  $a0, $t0, $t1
/* 07D810 8007CC10 00609825 */  move  $s3, $v1
.L8007CC14:
/* 07D814 8007CC14 00651021 */  addu  $v0, $v1, $a1
/* 07D818 8007CC18 02A2082A */  slt   $at, $s5, $v0
/* 07D81C 8007CC1C 10200002 */  beqz  $at, .L8007CC28
/* 07D820 8007CC20 00000000 */   nop   
/* 07D824 8007CC24 0040A825 */  move  $s5, $v0
.L8007CC28:
/* 07D828 8007CC28 00861023 */  subu  $v0, $a0, $a2
/* 07D82C 8007CC2C 0056082A */  slt   $at, $v0, $s6
/* 07D830 8007CC30 10200003 */  beqz  $at, .L8007CC40
/* 07D834 8007CC34 0284082A */   slt   $at, $s4, $a0
/* 07D838 8007CC38 0040B025 */  move  $s6, $v0
/* 07D83C 8007CC3C 0284082A */  slt   $at, $s4, $a0
.L8007CC40:
/* 07D840 8007CC40 10200002 */  beqz  $at, .L8007CC4C
/* 07D844 8007CC44 00000000 */   nop   
/* 07D848 8007CC48 0080A025 */  move  $s4, $a0
.L8007CC4C:
/* 07D84C 8007CC4C 0C01ECAF */  jal   free_texture
/* 07D850 8007CC50 02002025 */   move  $a0, $s0
/* 07D854 8007CC54 93CA000D */  lbu   $t2, 0xd($fp)
/* 07D858 8007CC58 26310001 */  addiu $s1, $s1, 1
/* 07D85C 8007CC5C 022A082A */  slt   $at, $s1, $t2
/* 07D860 8007CC60 1420FFD5 */  bnez  $at, .L8007CBB8
/* 07D864 8007CC64 00000000 */   nop   
/* 07D868 8007CC68 8FAC0048 */  lw    $t4, 0x48($sp)
.L8007CC6C:
/* 07D86C 8007CC6C 02B35823 */  subu  $t3, $s5, $s3
/* 07D870 8007CC70 AD8B0000 */  sw    $t3, ($t4)
/* 07D874 8007CC74 8FAE004C */  lw    $t6, 0x4c($sp)
/* 07D878 8007CC78 02966823 */  subu  $t5, $s4, $s6
/* 07D87C 8007CC7C ADCD0000 */  sw    $t5, ($t6)
.L8007CC80:
/* 07D880 8007CC80 8FBF003C */  lw    $ra, 0x3c($sp)
/* 07D884 8007CC84 8FB00018 */  lw    $s0, 0x18($sp)
/* 07D888 8007CC88 8FB1001C */  lw    $s1, 0x1c($sp)
/* 07D88C 8007CC8C 8FB20020 */  lw    $s2, 0x20($sp)
/* 07D890 8007CC90 8FB30024 */  lw    $s3, 0x24($sp)
/* 07D894 8007CC94 8FB40028 */  lw    $s4, 0x28($sp)
/* 07D898 8007CC98 8FB5002C */  lw    $s5, 0x2c($sp)
/* 07D89C 8007CC9C 8FB60030 */  lw    $s6, 0x30($sp)
/* 07D8A0 8007CCA0 8FB70034 */  lw    $s7, 0x34($sp)
/* 07D8A4 8007CCA4 8FBE0038 */  lw    $fp, 0x38($sp)
/* 07D8A8 8007CCA8 03E00008 */  jr    $ra
/* 07D8AC 8007CCAC 27BD0040 */   addiu $sp, $sp, 0x40

