.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800CCC20
/* 0CD820 800CCC20 27BDFF80 */  addiu $sp, $sp, -0x80
/* 0CD824 800CCC24 3C0E800E */  lui   $t6, %hi(D_800E38C0) # $t6, 0x800e
/* 0CD828 800CCC28 8DCE38C0 */  lw    $t6, %lo(D_800E38C0)($t6)
/* 0CD82C 800CCC2C AFBF0024 */  sw    $ra, 0x24($sp)
/* 0CD830 800CCC30 AFA40080 */  sw    $a0, 0x80($sp)
/* 0CD834 800CCC34 AFA50084 */  sw    $a1, 0x84($sp)
/* 0CD838 800CCC38 AFA60088 */  sw    $a2, 0x88($sp)
/* 0CD83C 800CCC3C 11C00003 */  beqz  $t6, .L800CCC4C
/* 0CD840 800CCC40 AFA00078 */   sw    $zero, 0x78($sp)
/* 0CD844 800CCC44 10000070 */  b     .L800CCE08
/* 0CD848 800CCC48 00001025 */   move  $v0, $zero
.L800CCC4C:
/* 0CD84C 800CCC4C 240F0001 */  li    $t7, 1
/* 0CD850 800CCC50 3C01800E */  lui   $at, %hi(D_800E38C0) # $at, 0x800e
/* 0CD854 800CCC54 0C03486C */  jal   func_800D21B0
/* 0CD858 800CCC58 AC2F38C0 */   sw    $t7, %lo(D_800E38C0)($at)
/* 0CD85C 800CCC5C 3C050007 */  lui   $a1, (0x0007A120 >> 16) # lui $a1, 7
/* 0CD860 800CCC60 3C06800E */  lui   $a2, %hi(D_800E38A0) # $a2, 0x800e
/* 0CD864 800CCC64 3C07800E */  lui   $a3, %hi(D_800E38A4) # $a3, 0x800e
/* 0CD868 800CCC68 AFA20070 */  sw    $v0, 0x70($sp)
/* 0CD86C 800CCC6C AFA30074 */  sw    $v1, 0x74($sp)
/* 0CD870 800CCC70 8CE738A4 */  lw    $a3, %lo(D_800E38A4)($a3)
/* 0CD874 800CCC74 8CC638A0 */  lw    $a2, %lo(D_800E38A0)($a2)
/* 0CD878 800CCC78 34A5A120 */  ori   $a1, (0x0007A120 & 0xFFFF) # ori $a1, $a1, 0xa120
/* 0CD87C 800CCC7C 0C033AF2 */  jal   __ll_mul
/* 0CD880 800CCC80 24040000 */   li    $a0, 0
/* 0CD884 800CCC84 AFA20030 */  sw    $v0, 0x30($sp)
/* 0CD888 800CCC88 AFA30034 */  sw    $v1, 0x34($sp)
/* 0CD88C 800CCC8C 3C07000F */  lui   $a3, (0x000F4240 >> 16) # lui $a3, 0xf
/* 0CD890 800CCC90 34E74240 */  ori   $a3, (0x000F4240 & 0xFFFF) # ori $a3, $a3, 0x4240
/* 0CD894 800CCC94 8FA50034 */  lw    $a1, 0x34($sp)
/* 0CD898 800CCC98 8FA40030 */  lw    $a0, 0x30($sp)
/* 0CD89C 800CCC9C 0C033AB2 */  jal   __ull_div
/* 0CD8A0 800CCCA0 24060000 */   li    $a2, 0
/* 0CD8A4 800CCCA4 8FB80070 */  lw    $t8, 0x70($sp)
/* 0CD8A8 800CCCA8 8FB90074 */  lw    $t9, 0x74($sp)
/* 0CD8AC 800CCCAC 0058082B */  sltu  $at, $v0, $t8
/* 0CD8B0 800CCCB0 14200031 */  bnez  $at, .L800CCD78
/* 0CD8B4 800CCCB4 0302082B */   sltu  $at, $t8, $v0
/* 0CD8B8 800CCCB8 14200003 */  bnez  $at, .L800CCCC8
/* 0CD8BC 800CCCBC 0323082B */   sltu  $at, $t9, $v1
/* 0CD8C0 800CCCC0 1020002D */  beqz  $at, .L800CCD78
/* 0CD8C4 800CCCC4 00000000 */   nop   
.L800CCCC8:
/* 0CD8C8 800CCCC8 27A40038 */  addiu $a0, $sp, 0x38
/* 0CD8CC 800CCCCC 27A5007C */  addiu $a1, $sp, 0x7c
/* 0CD8D0 800CCCD0 0C032208 */  jal   osCreateMesgQueue
/* 0CD8D4 800CCCD4 24060001 */   li    $a2, 1
/* 0CD8D8 800CCCD8 3C050007 */  lui   $a1, (0x0007A120 >> 16) # lui $a1, 7
/* 0CD8DC 800CCCDC 3C06800E */  lui   $a2, %hi(D_800E38A0) # $a2, 0x800e
/* 0CD8E0 800CCCE0 3C07800E */  lui   $a3, %hi(D_800E38A4) # $a3, 0x800e
/* 0CD8E4 800CCCE4 8CE738A4 */  lw    $a3, %lo(D_800E38A4)($a3)
/* 0CD8E8 800CCCE8 8CC638A0 */  lw    $a2, %lo(D_800E38A0)($a2)
/* 0CD8EC 800CCCEC 34A5A120 */  ori   $a1, (0x0007A120 & 0xFFFF) # ori $a1, $a1, 0xa120
/* 0CD8F0 800CCCF0 0C033AF2 */  jal   __ll_mul
/* 0CD8F4 800CCCF4 24040000 */   li    $a0, 0
/* 0CD8F8 800CCCF8 AFA20028 */  sw    $v0, 0x28($sp)
/* 0CD8FC 800CCCFC AFA3002C */  sw    $v1, 0x2c($sp)
/* 0CD900 800CCD00 3C07000F */  lui   $a3, (0x000F4240 >> 16) # lui $a3, 0xf
/* 0CD904 800CCD04 34E74240 */  ori   $a3, (0x000F4240 & 0xFFFF) # ori $a3, $a3, 0x4240
/* 0CD908 800CCD08 8FA5002C */  lw    $a1, 0x2c($sp)
/* 0CD90C 800CCD0C 8FA40028 */  lw    $a0, 0x28($sp)
/* 0CD910 800CCD10 0C033AB2 */  jal   __ull_div
/* 0CD914 800CCD14 24060000 */   li    $a2, 0
/* 0CD918 800CCD18 AFA20030 */  sw    $v0, 0x30($sp)
/* 0CD91C 800CCD1C AFA30034 */  sw    $v1, 0x34($sp)
/* 0CD920 800CCD20 8FA90034 */  lw    $t1, 0x34($sp)
/* 0CD924 800CCD24 8FA80030 */  lw    $t0, 0x30($sp)
/* 0CD928 800CCD28 8FAA0070 */  lw    $t2, 0x70($sp)
/* 0CD92C 800CCD2C 8FAB0074 */  lw    $t3, 0x74($sp)
/* 0CD930 800CCD30 240C0000 */  li    $t4, 0
/* 0CD934 800CCD34 240D0000 */  li    $t5, 0
/* 0CD938 800CCD38 27AE0038 */  addiu $t6, $sp, 0x38
/* 0CD93C 800CCD3C 27AF007C */  addiu $t7, $sp, 0x7c
/* 0CD940 800CCD40 010A3023 */  subu  $a2, $t0, $t2
/* 0CD944 800CCD44 012B082B */  sltu  $at, $t1, $t3
/* 0CD948 800CCD48 00C13023 */  subu  $a2, $a2, $at
/* 0CD94C 800CCD4C AFAF001C */  sw    $t7, 0x1c($sp)
/* 0CD950 800CCD50 AFAE0018 */  sw    $t6, 0x18($sp)
/* 0CD954 800CCD54 AFAD0014 */  sw    $t5, 0x14($sp)
/* 0CD958 800CCD58 AFAC0010 */  sw    $t4, 0x10($sp)
/* 0CD95C 800CCD5C 27A40050 */  addiu $a0, $sp, 0x50
/* 0CD960 800CCD60 0C035378 */  jal   func_800D4DE0
/* 0CD964 800CCD64 012B3823 */   subu  $a3, $t1, $t3
/* 0CD968 800CCD68 27A40038 */  addiu $a0, $sp, 0x38
/* 0CD96C 800CCD6C 27A5007C */  addiu $a1, $sp, 0x7c
/* 0CD970 800CCD70 0C0322EC */  jal   osRecvMesg
/* 0CD974 800CCD74 24060001 */   li    $a2, 1
.L800CCD78:
/* 0CD978 800CCD78 24180004 */  li    $t8, 4
/* 0CD97C 800CCD7C 3C018013 */  lui   $at, %hi(D_8012CD91) # $at, 0x8013
/* 0CD980 800CCD80 A038CD91 */  sb    $t8, %lo(D_8012CD91)($at)
/* 0CD984 800CCD84 0C0333BA */  jal   func_800CCEE8
/* 0CD988 800CCD88 00002025 */   move  $a0, $zero
/* 0CD98C 800CCD8C 3C058013 */  lui   $a1, %hi(D_8012CD50) # $a1, 0x8013
/* 0CD990 800CCD90 24A5CD50 */  addiu $a1, %lo(D_8012CD50) # addiu $a1, $a1, -0x32b0
/* 0CD994 800CCD94 0C0335B0 */  jal   func_800CD6C0
/* 0CD998 800CCD98 24040001 */   li    $a0, 1
/* 0CD99C 800CCD9C AFA20078 */  sw    $v0, 0x78($sp)
/* 0CD9A0 800CCDA0 8FA40080 */  lw    $a0, 0x80($sp)
/* 0CD9A4 800CCDA4 27A5007C */  addiu $a1, $sp, 0x7c
/* 0CD9A8 800CCDA8 0C0322EC */  jal   osRecvMesg
/* 0CD9AC 800CCDAC 24060001 */   li    $a2, 1
/* 0CD9B0 800CCDB0 3C058013 */  lui   $a1, %hi(D_8012CD50) # $a1, 0x8013
/* 0CD9B4 800CCDB4 24A5CD50 */  addiu $a1, %lo(D_8012CD50) # addiu $a1, $a1, -0x32b0
/* 0CD9B8 800CCDB8 0C0335B0 */  jal   func_800CD6C0
/* 0CD9BC 800CCDBC 00002025 */   move  $a0, $zero
/* 0CD9C0 800CCDC0 AFA20078 */  sw    $v0, 0x78($sp)
/* 0CD9C4 800CCDC4 8FA40080 */  lw    $a0, 0x80($sp)
/* 0CD9C8 800CCDC8 27A5007C */  addiu $a1, $sp, 0x7c
/* 0CD9CC 800CCDCC 0C0322EC */  jal   osRecvMesg
/* 0CD9D0 800CCDD0 24060001 */   li    $a2, 1
/* 0CD9D4 800CCDD4 8FA40084 */  lw    $a0, 0x84($sp)
/* 0CD9D8 800CCDD8 0C033386 */  jal   func_800CCE18
/* 0CD9DC 800CCDDC 8FA50088 */   lw    $a1, 0x88($sp)
/* 0CD9E0 800CCDE0 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CD9E4 800CCDE4 0C033580 */  jal   func_800CD600
/* 0CD9E8 800CCDE8 A020CD90 */   sb    $zero, %lo(D_8012CD90)($at)
/* 0CD9EC 800CCDEC 3C048013 */  lui   $a0, %hi(D_8012CDB8) # $a0, 0x8013
/* 0CD9F0 800CCDF0 3C058013 */  lui   $a1, %hi(D_8012CDD0) # $a1, 0x8013
/* 0CD9F4 800CCDF4 24A5CDD0 */  addiu $a1, %lo(D_8012CDD0) # addiu $a1, $a1, -0x3230
/* 0CD9F8 800CCDF8 2484CDB8 */  addiu $a0, %lo(D_8012CDB8) # addiu $a0, $a0, -0x3248
/* 0CD9FC 800CCDFC 0C032208 */  jal   osCreateMesgQueue
/* 0CDA00 800CCE00 24060001 */   li    $a2, 1
/* 0CDA04 800CCE04 8FA20078 */  lw    $v0, 0x78($sp)
.L800CCE08:
/* 0CDA08 800CCE08 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0CDA0C 800CCE0C 27BD0080 */  addiu $sp, $sp, 0x80
/* 0CDA10 800CCE10 03E00008 */  jr    $ra
/* 0CDA14 800CCE14 00000000 */   nop   

glabel func_800CCE18
/* 0CDA18 800CCE18 3C0F8013 */  lui   $t7, %hi(D_8012CD91) # $t7, 0x8013
/* 0CDA1C 800CCE1C 91EFCD91 */  lbu   $t7, %lo(D_8012CD91)($t7)
/* 0CDA20 800CCE20 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CDA24 800CCE24 3C0E8013 */  lui   $t6, %hi(D_8012CD50) # $t6, 0x8013
/* 0CDA28 800CCE28 25CECD50 */  addiu $t6, %lo(D_8012CD50) # addiu $t6, $t6, -0x32b0
/* 0CDA2C 800CCE2C A3A00007 */  sb    $zero, 7($sp)
/* 0CDA30 800CCE30 AFAE0014 */  sw    $t6, 0x14($sp)
/* 0CDA34 800CCE34 19E00028 */  blez  $t7, .L800CCED8
/* 0CDA38 800CCE38 AFA00008 */   sw    $zero, 8($sp)
.L800CCE3C:
/* 0CDA3C 800CCE3C 8FB90014 */  lw    $t9, 0x14($sp)
/* 0CDA40 800CCE40 27B8000C */  addiu $t8, $sp, 0xc
/* 0CDA44 800CCE44 8B210000 */  lwl   $at, ($t9)
/* 0CDA48 800CCE48 9B210003 */  lwr   $at, 3($t9)
/* 0CDA4C 800CCE4C AF010000 */  sw    $at, ($t8)
/* 0CDA50 800CCE50 8B290004 */  lwl   $t1, 4($t9)
/* 0CDA54 800CCE54 9B290007 */  lwr   $t1, 7($t9)
/* 0CDA58 800CCE58 AF090004 */  sw    $t1, 4($t8)
/* 0CDA5C 800CCE5C 93AA000E */  lbu   $t2, 0xe($sp)
/* 0CDA60 800CCE60 314B00C0 */  andi  $t3, $t2, 0xc0
/* 0CDA64 800CCE64 000B6103 */  sra   $t4, $t3, 4
/* 0CDA68 800CCE68 A0AC0003 */  sb    $t4, 3($a1)
/* 0CDA6C 800CCE6C 90AD0003 */  lbu   $t5, 3($a1)
/* 0CDA70 800CCE70 15A0000E */  bnez  $t5, .L800CCEAC
/* 0CDA74 800CCE74 00000000 */   nop   
/* 0CDA78 800CCE78 93AE0011 */  lbu   $t6, 0x11($sp)
/* 0CDA7C 800CCE7C 93A80010 */  lbu   $t0, 0x10($sp)
/* 0CDA80 800CCE80 240B0001 */  li    $t3, 1
/* 0CDA84 800CCE84 000E7A00 */  sll   $t7, $t6, 8
/* 0CDA88 800CCE88 01E8C025 */  or    $t8, $t7, $t0
/* 0CDA8C 800CCE8C A4B80000 */  sh    $t8, ($a1)
/* 0CDA90 800CCE90 93B90012 */  lbu   $t9, 0x12($sp)
/* 0CDA94 800CCE94 A0B90002 */  sb    $t9, 2($a1)
/* 0CDA98 800CCE98 8FAA0008 */  lw    $t2, 8($sp)
/* 0CDA9C 800CCE9C 93A90007 */  lbu   $t1, 7($sp)
/* 0CDAA0 800CCEA0 014B6004 */  sllv  $t4, $t3, $t2
/* 0CDAA4 800CCEA4 012C6825 */  or    $t5, $t1, $t4
/* 0CDAA8 800CCEA8 A3AD0007 */  sb    $t5, 7($sp)
.L800CCEAC:
/* 0CDAAC 800CCEAC 8FAE0008 */  lw    $t6, 8($sp)
/* 0CDAB0 800CCEB0 3C198013 */  lui   $t9, %hi(D_8012CD91) # $t9, 0x8013
/* 0CDAB4 800CCEB4 9339CD91 */  lbu   $t9, %lo(D_8012CD91)($t9)
/* 0CDAB8 800CCEB8 8FA80014 */  lw    $t0, 0x14($sp)
/* 0CDABC 800CCEBC 25CF0001 */  addiu $t7, $t6, 1
/* 0CDAC0 800CCEC0 01F9082A */  slt   $at, $t7, $t9
/* 0CDAC4 800CCEC4 25180008 */  addiu $t8, $t0, 8
/* 0CDAC8 800CCEC8 AFB80014 */  sw    $t8, 0x14($sp)
/* 0CDACC 800CCECC AFAF0008 */  sw    $t7, 8($sp)
/* 0CDAD0 800CCED0 1420FFDA */  bnez  $at, .L800CCE3C
/* 0CDAD4 800CCED4 24A50004 */   addiu $a1, $a1, 4
.L800CCED8:
/* 0CDAD8 800CCED8 93AB0007 */  lbu   $t3, 7($sp)
/* 0CDADC 800CCEDC 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CDAE0 800CCEE0 03E00008 */  jr    $ra
/* 0CDAE4 800CCEE4 A08B0000 */   sb    $t3, ($a0)

glabel func_800CCEE8
/* 0CDAE8 800CCEE8 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CDAEC 800CCEEC 308400FF */  andi  $a0, $a0, 0xff
/* 0CDAF0 800CCEF0 AFA00000 */  sw    $zero, ($sp)
.L800CCEF4:
/* 0CDAF4 800CCEF4 8FAE0000 */  lw    $t6, ($sp)
/* 0CDAF8 800CCEF8 8FB80000 */  lw    $t8, ($sp)
/* 0CDAFC 800CCEFC 3C018013 */  lui   $at, 0x8013
/* 0CDB00 800CCF00 000E7880 */  sll   $t7, $t6, 2
/* 0CDB04 800CCF04 002F0821 */  addu  $at, $at, $t7
/* 0CDB08 800CCF08 AC20CD50 */  sw    $zero, -0x32b0($at)
/* 0CDB0C 800CCF0C 27190001 */  addiu $t9, $t8, 1
/* 0CDB10 800CCF10 2B210010 */  slti  $at, $t9, 0x10
/* 0CDB14 800CCF14 1420FFF7 */  bnez  $at, .L800CCEF4
/* 0CDB18 800CCF18 AFB90000 */   sw    $t9, ($sp)
/* 0CDB1C 800CCF1C 3C198013 */  lui   $t9, %hi(D_8012CD91) # $t9, 0x8013
/* 0CDB20 800CCF20 9339CD91 */  lbu   $t9, %lo(D_8012CD91)($t9)
/* 0CDB24 800CCF24 3C098013 */  lui   $t1, %hi(D_8012CD50) # $t1, 0x8013
/* 0CDB28 800CCF28 24080001 */  li    $t0, 1
/* 0CDB2C 800CCF2C 3C018013 */  lui   $at, %hi(D_8012CD8C) # $at, 0x8013
/* 0CDB30 800CCF30 2529CD50 */  addiu $t1, %lo(D_8012CD50) # addiu $t1, $t1, -0x32b0
/* 0CDB34 800CCF34 240A00FF */  li    $t2, 255
/* 0CDB38 800CCF38 240B0001 */  li    $t3, 1
/* 0CDB3C 800CCF3C 240C0003 */  li    $t4, 3
/* 0CDB40 800CCF40 240D00FF */  li    $t5, 255
/* 0CDB44 800CCF44 240E00FF */  li    $t6, 255
/* 0CDB48 800CCF48 240F00FF */  li    $t7, 255
/* 0CDB4C 800CCF4C 241800FF */  li    $t8, 255
/* 0CDB50 800CCF50 AC28CD8C */  sw    $t0, %lo(D_8012CD8C)($at)
/* 0CDB54 800CCF54 AFA9000C */  sw    $t1, 0xc($sp)
/* 0CDB58 800CCF58 A3AA0004 */  sb    $t2, 4($sp)
/* 0CDB5C 800CCF5C A3AB0005 */  sb    $t3, 5($sp)
/* 0CDB60 800CCF60 A3AC0006 */  sb    $t4, 6($sp)
/* 0CDB64 800CCF64 A3A40007 */  sb    $a0, 7($sp)
/* 0CDB68 800CCF68 A3AD0008 */  sb    $t5, 8($sp)
/* 0CDB6C 800CCF6C A3AE0009 */  sb    $t6, 9($sp)
/* 0CDB70 800CCF70 A3AF000A */  sb    $t7, 0xa($sp)
/* 0CDB74 800CCF74 A3B8000B */  sb    $t8, 0xb($sp)
/* 0CDB78 800CCF78 1B200013 */  blez  $t9, .L800CCFC8
/* 0CDB7C 800CCF7C AFA00000 */   sw    $zero, ($sp)
.L800CCF80:
/* 0CDB80 800CCF80 27A90004 */  addiu $t1, $sp, 4
/* 0CDB84 800CCF84 8D210000 */  lw    $at, ($t1)
/* 0CDB88 800CCF88 8FA8000C */  lw    $t0, 0xc($sp)
/* 0CDB8C 800CCF8C 3C188013 */  lui   $t8, %hi(D_8012CD91) # $t8, 0x8013
/* 0CDB90 800CCF90 A9010000 */  swl   $at, ($t0)
/* 0CDB94 800CCF94 B9010003 */  swr   $at, 3($t0)
/* 0CDB98 800CCF98 8D2B0004 */  lw    $t3, 4($t1)
/* 0CDB9C 800CCF9C A90B0004 */  swl   $t3, 4($t0)
/* 0CDBA0 800CCFA0 B90B0007 */  swr   $t3, 7($t0)
/* 0CDBA4 800CCFA4 8FAE0000 */  lw    $t6, ($sp)
/* 0CDBA8 800CCFA8 9318CD91 */  lbu   $t8, %lo(D_8012CD91)($t8)
/* 0CDBAC 800CCFAC 8FAC000C */  lw    $t4, 0xc($sp)
/* 0CDBB0 800CCFB0 25CF0001 */  addiu $t7, $t6, 1
/* 0CDBB4 800CCFB4 01F8082A */  slt   $at, $t7, $t8
/* 0CDBB8 800CCFB8 258D0008 */  addiu $t5, $t4, 8
/* 0CDBBC 800CCFBC AFAF0000 */  sw    $t7, ($sp)
/* 0CDBC0 800CCFC0 1420FFEF */  bnez  $at, .L800CCF80
/* 0CDBC4 800CCFC4 AFAD000C */   sw    $t5, 0xc($sp)
.L800CCFC8:
/* 0CDBC8 800CCFC8 8FAA000C */  lw    $t2, 0xc($sp)
/* 0CDBCC 800CCFCC 241900FE */  li    $t9, 254
/* 0CDBD0 800CCFD0 27BD0010 */  addiu $sp, $sp, 0x10
/* 0CDBD4 800CCFD4 03E00008 */  jr    $ra
/* 0CDBD8 800CCFD8 A1590000 */   sb    $t9, ($t2)

/* 0CDBDC 800CCFDC 00000000 */  nop   
glabel func_800CCFE0
/* 0CDBE0 800CCFE0 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0CDBE4 800CCFE4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CDBE8 800CCFE8 AFA40020 */  sw    $a0, 0x20($sp)
/* 0CDBEC 800CCFEC 0C033594 */  jal   func_800CD650
/* 0CDBF0 800CCFF0 AFA0001C */   sw    $zero, 0x1c($sp)
/* 0CDBF4 800CCFF4 3C0E8013 */  lui   $t6, %hi(D_8012CD90) # $t6, 0x8013
/* 0CDBF8 800CCFF8 91CECD90 */  lbu   $t6, %lo(D_8012CD90)($t6)
/* 0CDBFC 800CCFFC 24010001 */  li    $at, 1
/* 0CDC00 800CD000 11C1000C */  beq   $t6, $at, .L800CD034
/* 0CDC04 800CD004 00000000 */   nop   
/* 0CDC08 800CD008 0C033453 */  jal   func_800CD14C
/* 0CDC0C 800CD00C 00000000 */   nop   
/* 0CDC10 800CD010 3C058013 */  lui   $a1, %hi(D_8012CD50) # $a1, 0x8013
/* 0CDC14 800CD014 24A5CD50 */  addiu $a1, %lo(D_8012CD50) # addiu $a1, $a1, -0x32b0
/* 0CDC18 800CD018 0C0335B0 */  jal   func_800CD6C0
/* 0CDC1C 800CD01C 24040001 */   li    $a0, 1
/* 0CDC20 800CD020 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0CDC24 800CD024 8FA40020 */  lw    $a0, 0x20($sp)
/* 0CDC28 800CD028 00002825 */  move  $a1, $zero
/* 0CDC2C 800CD02C 0C0322EC */  jal   osRecvMesg
/* 0CDC30 800CD030 24060001 */   li    $a2, 1
.L800CD034:
/* 0CDC34 800CD034 AFA00018 */  sw    $zero, 0x18($sp)
.L800CD038:
/* 0CDC38 800CD038 8FB80018 */  lw    $t8, 0x18($sp)
/* 0CDC3C 800CD03C 8FA80018 */  lw    $t0, 0x18($sp)
/* 0CDC40 800CD040 3C018013 */  lui   $at, 0x8013
/* 0CDC44 800CD044 0018C880 */  sll   $t9, $t8, 2
/* 0CDC48 800CD048 00390821 */  addu  $at, $at, $t9
/* 0CDC4C 800CD04C 240F00FF */  li    $t7, 255
/* 0CDC50 800CD050 AC2FCD50 */  sw    $t7, -0x32b0($at)
/* 0CDC54 800CD054 25090001 */  addiu $t1, $t0, 1
/* 0CDC58 800CD058 29210010 */  slti  $at, $t1, 0x10
/* 0CDC5C 800CD05C 1420FFF6 */  bnez  $at, .L800CD038
/* 0CDC60 800CD060 AFA90018 */   sw    $t1, 0x18($sp)
/* 0CDC64 800CD064 3C018013 */  lui   $at, %hi(D_8012CD8C) # $at, 0x8013
/* 0CDC68 800CD068 3C058013 */  lui   $a1, %hi(D_8012CD50) # $a1, 0x8013
/* 0CDC6C 800CD06C AC20CD8C */  sw    $zero, %lo(D_8012CD8C)($at)
/* 0CDC70 800CD070 24A5CD50 */  addiu $a1, %lo(D_8012CD50) # addiu $a1, $a1, -0x32b0
/* 0CDC74 800CD074 0C0335B0 */  jal   func_800CD6C0
/* 0CDC78 800CD078 00002025 */   move  $a0, $zero
/* 0CDC7C 800CD07C 240A0001 */  li    $t2, 1
/* 0CDC80 800CD080 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CDC84 800CD084 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0CDC88 800CD088 0C0335A5 */  jal   func_800CD694
/* 0CDC8C 800CD08C A02ACD90 */   sb    $t2, %lo(D_8012CD90)($at)
/* 0CDC90 800CD090 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CDC94 800CD094 8FA2001C */  lw    $v0, 0x1c($sp)
/* 0CDC98 800CD098 27BD0020 */  addiu $sp, $sp, 0x20
/* 0CDC9C 800CD09C 03E00008 */  jr    $ra
/* 0CDCA0 800CD0A0 00000000 */   nop   

glabel func_800CD0A4
/* 0CDCA4 800CD0A4 3C0F8013 */  lui   $t7, %hi(D_8012CD91) # $t7, 0x8013
/* 0CDCA8 800CD0A8 91EFCD91 */  lbu   $t7, %lo(D_8012CD91)($t7)
/* 0CDCAC 800CD0AC 3C0E8013 */  lui   $t6, %hi(D_8012CD50) # $t6, 0x8013
/* 0CDCB0 800CD0B0 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CDCB4 800CD0B4 25CECD50 */  addiu $t6, %lo(D_8012CD50) # addiu $t6, $t6, -0x32b0
/* 0CDCB8 800CD0B8 AFAE000C */  sw    $t6, 0xc($sp)
/* 0CDCBC 800CD0BC 19E00021 */  blez  $t7, .L800CD144
/* 0CDCC0 800CD0C0 AFA00000 */   sw    $zero, ($sp)
.L800CD0C4:
/* 0CDCC4 800CD0C4 8FB9000C */  lw    $t9, 0xc($sp)
/* 0CDCC8 800CD0C8 27B80004 */  addiu $t8, $sp, 4
/* 0CDCCC 800CD0CC 8B210000 */  lwl   $at, ($t9)
/* 0CDCD0 800CD0D0 9B210003 */  lwr   $at, 3($t9)
/* 0CDCD4 800CD0D4 AF010000 */  sw    $at, ($t8)
/* 0CDCD8 800CD0D8 8B290004 */  lwl   $t1, 4($t9)
/* 0CDCDC 800CD0DC 9B290007 */  lwr   $t1, 7($t9)
/* 0CDCE0 800CD0E0 AF090004 */  sw    $t1, 4($t8)
/* 0CDCE4 800CD0E4 93AA0006 */  lbu   $t2, 6($sp)
/* 0CDCE8 800CD0E8 314B00C0 */  andi  $t3, $t2, 0xc0
/* 0CDCEC 800CD0EC 000B6103 */  sra   $t4, $t3, 4
/* 0CDCF0 800CD0F0 A08C0004 */  sb    $t4, 4($a0)
/* 0CDCF4 800CD0F4 908D0004 */  lbu   $t5, 4($a0)
/* 0CDCF8 800CD0F8 15A00007 */  bnez  $t5, .L800CD118
/* 0CDCFC 800CD0FC 00000000 */   nop   
/* 0CDD00 800CD100 97AE0008 */  lhu   $t6, 8($sp)
/* 0CDD04 800CD104 A48E0000 */  sh    $t6, ($a0)
/* 0CDD08 800CD108 83AF000A */  lb    $t7, 0xa($sp)
/* 0CDD0C 800CD10C A08F0002 */  sb    $t7, 2($a0)
/* 0CDD10 800CD110 83A8000B */  lb    $t0, 0xb($sp)
/* 0CDD14 800CD114 A0880003 */  sb    $t0, 3($a0)
.L800CD118:
/* 0CDD18 800CD118 8FB80000 */  lw    $t8, ($sp)
/* 0CDD1C 800CD11C 3C0B8013 */  lui   $t3, %hi(D_8012CD91) # $t3, 0x8013
/* 0CDD20 800CD120 916BCD91 */  lbu   $t3, %lo(D_8012CD91)($t3)
/* 0CDD24 800CD124 8FA9000C */  lw    $t1, 0xc($sp)
/* 0CDD28 800CD128 27190001 */  addiu $t9, $t8, 1
/* 0CDD2C 800CD12C 032B082A */  slt   $at, $t9, $t3
/* 0CDD30 800CD130 252A0008 */  addiu $t2, $t1, 8
/* 0CDD34 800CD134 AFAA000C */  sw    $t2, 0xc($sp)
/* 0CDD38 800CD138 AFB90000 */  sw    $t9, ($sp)
/* 0CDD3C 800CD13C 1420FFE1 */  bnez  $at, .L800CD0C4
/* 0CDD40 800CD140 24840006 */   addiu $a0, $a0, 6
.L800CD144:
/* 0CDD44 800CD144 03E00008 */  jr    $ra
/* 0CDD48 800CD148 27BD0010 */   addiu $sp, $sp, 0x10

glabel func_800CD14C
/* 0CDD4C 800CD14C 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CDD50 800CD150 3C0E8013 */  lui   $t6, %hi(D_8012CD50) # $t6, 0x8013
/* 0CDD54 800CD154 25CECD50 */  addiu $t6, %lo(D_8012CD50) # addiu $t6, $t6, -0x32b0
/* 0CDD58 800CD158 AFAE000C */  sw    $t6, 0xc($sp)
/* 0CDD5C 800CD15C AFA00000 */  sw    $zero, ($sp)
.L800CD160:
/* 0CDD60 800CD160 8FAF0000 */  lw    $t7, ($sp)
/* 0CDD64 800CD164 8FB90000 */  lw    $t9, ($sp)
/* 0CDD68 800CD168 3C018013 */  lui   $at, 0x8013
/* 0CDD6C 800CD16C 000FC080 */  sll   $t8, $t7, 2
/* 0CDD70 800CD170 00380821 */  addu  $at, $at, $t8
/* 0CDD74 800CD174 AC20CD50 */  sw    $zero, -0x32b0($at)
/* 0CDD78 800CD178 27280001 */  addiu $t0, $t9, 1
/* 0CDD7C 800CD17C 29010010 */  slti  $at, $t0, 0x10
/* 0CDD80 800CD180 1420FFF7 */  bnez  $at, .L800CD160
/* 0CDD84 800CD184 AFA80000 */   sw    $t0, ($sp)
/* 0CDD88 800CD188 3C198013 */  lui   $t9, %hi(D_8012CD91) # $t9, 0x8013
/* 0CDD8C 800CD18C 9339CD91 */  lbu   $t9, %lo(D_8012CD91)($t9)
/* 0CDD90 800CD190 24090001 */  li    $t1, 1
/* 0CDD94 800CD194 3C018013 */  lui   $at, %hi(D_8012CD8C) # $at, 0x8013
/* 0CDD98 800CD198 240A00FF */  li    $t2, 255
/* 0CDD9C 800CD19C 240B0001 */  li    $t3, 1
/* 0CDDA0 800CD1A0 240C0004 */  li    $t4, 4
/* 0CDDA4 800CD1A4 240D0001 */  li    $t5, 1
/* 0CDDA8 800CD1A8 340EFFFF */  li    $t6, 65535
/* 0CDDAC 800CD1AC 240FFFFF */  li    $t7, -1
/* 0CDDB0 800CD1B0 2418FFFF */  li    $t8, -1
/* 0CDDB4 800CD1B4 AC29CD8C */  sw    $t1, %lo(D_8012CD8C)($at)
/* 0CDDB8 800CD1B8 A3AA0004 */  sb    $t2, 4($sp)
/* 0CDDBC 800CD1BC A3AB0005 */  sb    $t3, 5($sp)
/* 0CDDC0 800CD1C0 A3AC0006 */  sb    $t4, 6($sp)
/* 0CDDC4 800CD1C4 A3AD0007 */  sb    $t5, 7($sp)
/* 0CDDC8 800CD1C8 A7AE0008 */  sh    $t6, 8($sp)
/* 0CDDCC 800CD1CC A3AF000A */  sb    $t7, 0xa($sp)
/* 0CDDD0 800CD1D0 A3B8000B */  sb    $t8, 0xb($sp)
/* 0CDDD4 800CD1D4 1B200013 */  blez  $t9, .L800CD224
/* 0CDDD8 800CD1D8 AFA00000 */   sw    $zero, ($sp)
.L800CD1DC:
/* 0CDDDC 800CD1DC 27A90004 */  addiu $t1, $sp, 4
/* 0CDDE0 800CD1E0 8D210000 */  lw    $at, ($t1)
/* 0CDDE4 800CD1E4 8FA8000C */  lw    $t0, 0xc($sp)
/* 0CDDE8 800CD1E8 3C188013 */  lui   $t8, %hi(D_8012CD91) # $t8, 0x8013
/* 0CDDEC 800CD1EC A9010000 */  swl   $at, ($t0)
/* 0CDDF0 800CD1F0 B9010003 */  swr   $at, 3($t0)
/* 0CDDF4 800CD1F4 8D2B0004 */  lw    $t3, 4($t1)
/* 0CDDF8 800CD1F8 A90B0004 */  swl   $t3, 4($t0)
/* 0CDDFC 800CD1FC B90B0007 */  swr   $t3, 7($t0)
/* 0CDE00 800CD200 8FAE0000 */  lw    $t6, ($sp)
/* 0CDE04 800CD204 9318CD91 */  lbu   $t8, %lo(D_8012CD91)($t8)
/* 0CDE08 800CD208 8FAC000C */  lw    $t4, 0xc($sp)
/* 0CDE0C 800CD20C 25CF0001 */  addiu $t7, $t6, 1
/* 0CDE10 800CD210 01F8082A */  slt   $at, $t7, $t8
/* 0CDE14 800CD214 258D0008 */  addiu $t5, $t4, 8
/* 0CDE18 800CD218 AFAF0000 */  sw    $t7, ($sp)
/* 0CDE1C 800CD21C 1420FFEF */  bnez  $at, .L800CD1DC
/* 0CDE20 800CD220 AFAD000C */   sw    $t5, 0xc($sp)
.L800CD224:
/* 0CDE24 800CD224 8FAA000C */  lw    $t2, 0xc($sp)
/* 0CDE28 800CD228 241900FE */  li    $t9, 254
/* 0CDE2C 800CD22C 27BD0010 */  addiu $sp, $sp, 0x10
/* 0CDE30 800CD230 03E00008 */  jr    $ra
/* 0CDE34 800CD234 A1590000 */   sb    $t9, ($t2)

/* 0CDE38 800CD238 00000000 */  nop   
/* 0CDE3C 800CD23C 00000000 */  nop   
