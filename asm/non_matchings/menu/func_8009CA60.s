glabel func_8009CA60
/* 09D660 8009CA60 3C0B800E */  lui   $t3, %hi(gMenuImageStack) # $t3, 0x800e
/* 09D664 8009CA64 256BF75C */  addiu $t3, %lo(gMenuImageStack) # addiu $t3, $t3, -0x8a4
/* 09D668 8009CA68 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 09D66C 8009CA6C 8D630000 */  lw    $v1, ($t3)
/* 09D670 8009CA70 00044140 */  sll   $t0, $a0, 5
/* 09D674 8009CA74 AFBF0024 */  sw    $ra, 0x24($sp)
/* 09D678 8009CA78 AFB00020 */  sw    $s0, 0x20($sp)
/* 09D67C 8009CA7C AFA40060 */  sw    $a0, 0x60($sp)
/* 09D680 8009CA80 00687821 */  addu  $t7, $v1, $t0
/* 09D684 8009CA84 85E50006 */  lh    $a1, 6($t7)
/* 09D688 8009CA88 3C0A8012 */  lui   $t2, %hi(D_80126550) # $t2, 0x8012
/* 09D68C 8009CA8C 0005C080 */  sll   $t8, $a1, 2
/* 09D690 8009CA90 01585021 */  addu  $t2, $t2, $t8
/* 09D694 8009CA94 8D4A6550 */  lw    $t2, %lo(D_80126550)($t2)
/* 09D698 8009CA98 3C19800E */  lui   $t9, %hi(D_800DF750) # $t9, 0x800e
/* 09D69C 8009CA9C 114000B4 */  beqz  $t2, .L8009CD70
/* 09D6A0 8009CAA0 8FBF0024 */   lw    $ra, 0x24($sp)
/* 09D6A4 8009CAA4 8F39F750 */  lw    $t9, %lo(D_800DF750)($t9)
/* 09D6A8 8009CAA8 00056040 */  sll   $t4, $a1, 1
/* 09D6AC 8009CAAC 032C6821 */  addu  $t5, $t9, $t4
/* 09D6B0 8009CAB0 85A20000 */  lh    $v0, ($t5)
/* 09D6B4 8009CAB4 3401C000 */  li    $at, 49152
/* 09D6B8 8009CAB8 304EC000 */  andi  $t6, $v0, 0xc000
/* 09D6BC 8009CABC 11C100AB */  beq   $t6, $at, .L8009CD6C
/* 09D6C0 8009CAC0 304F4000 */   andi  $t7, $v0, 0x4000
/* 09D6C4 8009CAC4 11E00027 */  beqz  $t7, .L8009CB64
/* 09D6C8 8009CAC8 304D8000 */   andi  $t5, $v0, 0x8000
/* 09D6CC 8009CACC 0004C940 */  sll   $t9, $a0, 5
/* 09D6D0 8009CAD0 03231021 */  addu  $v0, $t9, $v1
/* 09D6D4 8009CAD4 844C0000 */  lh    $t4, ($v0)
/* 09D6D8 8009CAD8 3C0F800E */  lui   $t7, %hi(D_800DF468) # $t7, 0x800e
/* 09D6DC 8009CADC A54C0000 */  sh    $t4, ($t2)
/* 09D6E0 8009CAE0 844D0002 */  lh    $t5, 2($v0)
/* 09D6E4 8009CAE4 3C108012 */  lui   $s0, %hi(D_801263A0) # $s0, 0x8012
/* 09D6E8 8009CAE8 A54D0002 */  sh    $t5, 2($t2)
/* 09D6EC 8009CAEC 844E0004 */  lh    $t6, 4($v0)
/* 09D6F0 8009CAF0 3C058012 */  lui   $a1, %hi(D_801263A8) # $a1, 0x8012
/* 09D6F4 8009CAF4 A54E0004 */  sh    $t6, 4($t2)
/* 09D6F8 8009CAF8 C444000C */  lwc1  $f4, 0xc($v0)
/* 09D6FC 8009CAFC 3C068012 */  lui   $a2, %hi(D_801263AC) # $a2, 0x8012
/* 09D700 8009CB00 E544000C */  swc1  $f4, 0xc($t2)
/* 09D704 8009CB04 C4460010 */  lwc1  $f6, 0x10($v0)
/* 09D708 8009CB08 01403825 */  move  $a3, $t2
/* 09D70C 8009CB0C E5460010 */  swc1  $f6, 0x10($t2)
/* 09D710 8009CB10 C4480014 */  lwc1  $f8, 0x14($v0)
/* 09D714 8009CB14 260463A0 */  addiu $a0, $s0, %lo(D_801263A0)
/* 09D718 8009CB18 E5480014 */  swc1  $f8, 0x14($t2)
/* 09D71C 8009CB1C C44A0008 */  lwc1  $f10, 8($v0)
/* 09D720 8009CB20 3C0C800E */  lui   $t4, %hi(sMenuGuiOpacity) # $t4, 0x800e
/* 09D724 8009CB24 E54A0008 */  swc1  $f10, 8($t2)
/* 09D728 8009CB28 8DEFF468 */  lw    $t7, %lo(D_800DF468)($t7)
/* 09D72C 8009CB2C 24C663AC */  addiu $a2, %lo(D_801263AC) # addiu $a2, $a2, 0x63ac
/* 09D730 8009CB30 15E00007 */  bnez  $t7, .L8009CB50
/* 09D734 8009CB34 24A563A8 */   addiu $a1, %lo(D_801263A8) # addiu $a1, $a1, 0x63a8
/* 09D738 8009CB38 8058001D */  lb    $t8, 0x1d($v0)
/* 09D73C 8009CB3C 00000000 */  nop   
/* 09D740 8009CB40 A5580018 */  sh    $t8, 0x18($t2)
/* 09D744 8009CB44 84590018 */  lh    $t9, 0x18($v0)
/* 09D748 8009CB48 00000000 */  nop   
/* 09D74C 8009CB4C A159003A */  sb    $t9, 0x3a($t2)
.L8009CB50:
/* 09D750 8009CB50 8D8CF764 */  lw    $t4, %lo(sMenuGuiOpacity)($t4)
/* 09D754 8009CB54 0C004B57 */  jal   func_80012D5C
/* 09D758 8009CB58 A0EC0039 */   sb    $t4, 0x39($a3)
/* 09D75C 8009CB5C 10000084 */  b     .L8009CD70
/* 09D760 8009CB60 8FBF0024 */   lw    $ra, 0x24($sp)
.L8009CB64:
/* 09D764 8009CB64 11A00034 */  beqz  $t5, .L8009CC38
/* 09D768 8009CB68 3C108012 */   lui   $s0, %hi(D_801263A0) # $s0, 0x8012
/* 09D76C 8009CB6C 261063A0 */  addiu $s0, %lo(D_801263A0) # addiu $s0, $s0, 0x63a0
/* 09D770 8009CB70 8E020000 */  lw    $v0, ($s0)
/* 09D774 8009CB74 3C0FFA00 */  lui   $t7, 0xfa00
/* 09D778 8009CB78 244E0008 */  addiu $t6, $v0, 8
/* 09D77C 8009CB7C AE0E0000 */  sw    $t6, ($s0)
/* 09D780 8009CB80 3C18800E */  lui   $t8, %hi(sMenuGuiColourR) # $t8, 0x800e
/* 09D784 8009CB84 AC4F0000 */  sw    $t7, ($v0)
/* 09D788 8009CB88 9319F4A4 */  lbu   $t9, %lo(sMenuGuiColourR)($t8)
/* 09D78C 8009CB8C 3C0D800E */  lui   $t5, %hi(sMenuGuiColourG) # $t5, 0x800e
/* 09D790 8009CB90 91AEF4A8 */  lbu   $t6, %lo(sMenuGuiColourG)($t5)
/* 09D794 8009CB94 00196600 */  sll   $t4, $t9, 0x18
/* 09D798 8009CB98 000E7C00 */  sll   $t7, $t6, 0x10
/* 09D79C 8009CB9C 018FC025 */  or    $t8, $t4, $t7
/* 09D7A0 8009CBA0 3C19800E */  lui   $t9, %hi(sMenuGuiColourB) # $t9, 0x800e
/* 09D7A4 8009CBA4 932DF4AC */  lbu   $t5, %lo(sMenuGuiColourB)($t9)
/* 09D7A8 8009CBA8 3C0F800E */  lui   $t7, %hi(sMenuGuiOpacity) # $t7, 0x800e
/* 09D7AC 8009CBAC 8DEFF764 */  lw    $t7, %lo(sMenuGuiOpacity)($t7)
/* 09D7B0 8009CBB0 000D7200 */  sll   $t6, $t5, 8
/* 09D7B4 8009CBB4 030E6025 */  or    $t4, $t8, $t6
/* 09D7B8 8009CBB8 31F900FF */  andi  $t9, $t7, 0xff
/* 09D7BC 8009CBBC 01996825 */  or    $t5, $t4, $t9
/* 09D7C0 8009CBC0 AC4D0004 */  sw    $t5, 4($v0)
/* 09D7C4 8009CBC4 8E020000 */  lw    $v0, ($s0)
/* 09D7C8 8009CBC8 240FFF00 */  li    $t7, -256
/* 09D7CC 8009CBCC 24580008 */  addiu $t8, $v0, 8
/* 09D7D0 8009CBD0 AE180000 */  sw    $t8, ($s0)
/* 09D7D4 8009CBD4 3C0EFB00 */  lui   $t6, 0xfb00
/* 09D7D8 8009CBD8 AC4E0000 */  sw    $t6, ($v0)
/* 09D7DC 8009CBDC AC4F0004 */  sw    $t7, 4($v0)
/* 09D7E0 8009CBE0 8FAC0060 */  lw    $t4, 0x60($sp)
/* 09D7E4 8009CBE4 3C18800E */  lui   $t8, %hi(D_800DF4B4) # $t8, 0x800e
/* 09D7E8 8009CBE8 8F18F4B4 */  lw    $t8, %lo(D_800DF4B4)($t8)
/* 09D7EC 8009CBEC 8D6D0000 */  lw    $t5, ($t3)
/* 09D7F0 8009CBF0 3C058012 */  lui   $a1, %hi(D_801263A8) # $a1, 0x8012
/* 09D7F4 8009CBF4 3C068012 */  lui   $a2, %hi(D_801263AC) # $a2, 0x8012
/* 09D7F8 8009CBF8 000CC940 */  sll   $t9, $t4, 5
/* 09D7FC 8009CBFC 24C663AC */  addiu $a2, %lo(D_801263AC) # addiu $a2, $a2, 0x63ac
/* 09D800 8009CC00 24A563A8 */  addiu $a1, %lo(D_801263A8) # addiu $a1, $a1, 0x63a8
/* 09D804 8009CC04 AFAA0010 */  sw    $t2, 0x10($sp)
/* 09D808 8009CC08 02002025 */  move  $a0, $s0
/* 09D80C 8009CC0C AFB80014 */  sw    $t8, 0x14($sp)
/* 09D810 8009CC10 0C01A2FD */  jal   func_80068BF4
/* 09D814 8009CC14 032D3821 */   addu  $a3, $t9, $t5
/* 09D818 8009CC18 8E020000 */  lw    $v0, ($s0)
/* 09D81C 8009CC1C 3C0FFA00 */  lui   $t7, 0xfa00
/* 09D820 8009CC20 244E0008 */  addiu $t6, $v0, 8
/* 09D824 8009CC24 AE0E0000 */  sw    $t6, ($s0)
/* 09D828 8009CC28 240CFFFF */  li    $t4, -1
/* 09D82C 8009CC2C AC4C0004 */  sw    $t4, 4($v0)
/* 09D830 8009CC30 1000004E */  b     .L8009CD6C
/* 09D834 8009CC34 AC4F0000 */   sw    $t7, ($v0)
.L8009CC38:
/* 09D838 8009CC38 3C09800E */  lui   $t1, %hi(sMenuGuiOpacity) # $t1, 0x800e
/* 09D83C 8009CC3C 2529F764 */  addiu $t1, %lo(sMenuGuiOpacity) # addiu $t1, $t1, -0x89c
/* 09D840 8009CC40 8D390000 */  lw    $t9, ($t1)
/* 09D844 8009CC44 3C058012 */  lui   $a1, %hi(D_801263A8) # $a1, 0x8012
/* 09D848 8009CC48 2B2100FF */  slti  $at, $t9, 0xff
/* 09D84C 8009CC4C 1020000E */  beqz  $at, .L8009CC88
/* 09D850 8009CC50 24A563A8 */   addiu $a1, %lo(D_801263A8) # addiu $a1, $a1, 0x63a8
/* 09D854 8009CC54 3C108012 */  lui   $s0, %hi(D_801263A0) # $s0, 0x8012
/* 09D858 8009CC58 261063A0 */  addiu $s0, %lo(D_801263A0) # addiu $s0, $s0, 0x63a0
/* 09D85C 8009CC5C 8E020000 */  lw    $v0, ($s0)
/* 09D860 8009CC60 3C18FA00 */  lui   $t8, 0xfa00
/* 09D864 8009CC64 244D0008 */  addiu $t5, $v0, 8
/* 09D868 8009CC68 AE0D0000 */  sw    $t5, ($s0)
/* 09D86C 8009CC6C AC580000 */  sw    $t8, ($v0)
/* 09D870 8009CC70 8D2E0000 */  lw    $t6, ($t1)
/* 09D874 8009CC74 2401FF00 */  li    $at, -256
/* 09D878 8009CC78 31CF00FF */  andi  $t7, $t6, 0xff
/* 09D87C 8009CC7C 01E16025 */  or    $t4, $t7, $at
/* 09D880 8009CC80 1000000A */  b     .L8009CCAC
/* 09D884 8009CC84 AC4C0004 */   sw    $t4, 4($v0)
.L8009CC88:
/* 09D888 8009CC88 3C108012 */  lui   $s0, %hi(D_801263A0) # $s0, 0x8012
/* 09D88C 8009CC8C 261063A0 */  addiu $s0, %lo(D_801263A0) # addiu $s0, $s0, 0x63a0
/* 09D890 8009CC90 8E020000 */  lw    $v0, ($s0)
/* 09D894 8009CC94 3C0DFA00 */  lui   $t5, 0xfa00
/* 09D898 8009CC98 24590008 */  addiu $t9, $v0, 8
/* 09D89C 8009CC9C AE190000 */  sw    $t9, ($s0)
/* 09D8A0 8009CCA0 2418FFFF */  li    $t8, -1
/* 09D8A4 8009CCA4 AC580004 */  sw    $t8, 4($v0)
/* 09D8A8 8009CCA8 AC4D0000 */  sw    $t5, ($v0)
.L8009CCAC:
/* 09D8AC 8009CCAC 8E020000 */  lw    $v0, ($s0)
/* 09D8B0 8009CCB0 3C0FFB00 */  lui   $t7, 0xfb00
/* 09D8B4 8009CCB4 244E0008 */  addiu $t6, $v0, 8
/* 09D8B8 8009CCB8 AE0E0000 */  sw    $t6, ($s0)
/* 09D8BC 8009CCBC 240CFF00 */  li    $t4, -256
/* 09D8C0 8009CCC0 AC4C0004 */  sw    $t4, 4($v0)
/* 09D8C4 8009CCC4 AC4F0000 */  sw    $t7, ($v0)
/* 09D8C8 8009CCC8 8FB90060 */  lw    $t9, 0x60($sp)
/* 09D8CC 8009CCCC 8D780000 */  lw    $t8, ($t3)
/* 09D8D0 8009CCD0 44808000 */  mtc1  $zero, $f16
/* 09D8D4 8009CCD4 3C07800E */  lui   $a3, %hi(D_800DF454) # $a3, 0x800e
/* 09D8D8 8009CCD8 8CE7F454 */  lw    $a3, %lo(D_800DF454)($a3)
/* 09D8DC 8009CCDC 00196940 */  sll   $t5, $t9, 5
/* 09D8E0 8009CCE0 AFA8002C */  sw    $t0, 0x2c($sp)
/* 09D8E4 8009CCE4 02002025 */  move  $a0, $s0
/* 09D8E8 8009CCE8 01B83021 */  addu  $a2, $t5, $t8
/* 09D8EC 8009CCEC 0C01A521 */  jal   func_80069484
/* 09D8F0 8009CCF0 E7B00010 */   swc1  $f16, 0x10($sp)
/* 09D8F4 8009CCF4 3C0B800E */  lui   $t3, %hi(gMenuImageStack) # $t3, 0x800e
/* 09D8F8 8009CCF8 256BF75C */  addiu $t3, %lo(gMenuImageStack) # addiu $t3, $t3, -0x8a4
/* 09D8FC 8009CCFC 8FA8002C */  lw    $t0, 0x2c($sp)
/* 09D900 8009CD00 8D6E0000 */  lw    $t6, ($t3)
/* 09D904 8009CD04 3C028012 */  lui   $v0, %hi(D_80126550) # $v0, 0x8012
/* 09D908 8009CD08 01C87821 */  addu  $t7, $t6, $t0
/* 09D90C 8009CD0C 85EC0006 */  lh    $t4, 6($t7)
/* 09D910 8009CD10 00000000 */  nop   
/* 09D914 8009CD14 000CC880 */  sll   $t9, $t4, 2
/* 09D918 8009CD18 00591021 */  addu  $v0, $v0, $t9
/* 09D91C 8009CD1C 8C426550 */  lw    $v0, %lo(D_80126550)($v0)
/* 09D920 8009CD20 00000000 */  nop   
/* 09D924 8009CD24 8C440000 */  lw    $a0, ($v0)
/* 09D928 8009CD28 0C02735F */  jal   func_8009CD7C
/* 09D92C 8009CD2C 00000000 */   nop   
/* 09D930 8009CD30 0C01A690 */  jal   func_80069A40
/* 09D934 8009CD34 02002025 */   move  $a0, $s0
/* 09D938 8009CD38 3C0D800E */  lui   $t5, %hi(sMenuGuiOpacity) # $t5, 0x800e
/* 09D93C 8009CD3C 8DADF764 */  lw    $t5, %lo(sMenuGuiOpacity)($t5)
/* 09D940 8009CD40 00000000 */  nop   
/* 09D944 8009CD44 29A100FF */  slti  $at, $t5, 0xff
/* 09D948 8009CD48 10200009 */  beqz  $at, .L8009CD70
/* 09D94C 8009CD4C 8FBF0024 */   lw    $ra, 0x24($sp)
/* 09D950 8009CD50 8E020000 */  lw    $v0, ($s0)
/* 09D954 8009CD54 3C0EFA00 */  lui   $t6, 0xfa00
/* 09D958 8009CD58 24580008 */  addiu $t8, $v0, 8
/* 09D95C 8009CD5C AE180000 */  sw    $t8, ($s0)
/* 09D960 8009CD60 240FFFFF */  li    $t7, -1
/* 09D964 8009CD64 AC4F0004 */  sw    $t7, 4($v0)
/* 09D968 8009CD68 AC4E0000 */  sw    $t6, ($v0)
.L8009CD6C:
/* 09D96C 8009CD6C 8FBF0024 */  lw    $ra, 0x24($sp)
.L8009CD70:
/* 09D970 8009CD70 8FB00020 */  lw    $s0, 0x20($sp)
/* 09D974 8009CD74 03E00008 */  jr    $ra
/* 09D978 8009CD78 27BD0060 */   addiu $sp, $sp, 0x60

