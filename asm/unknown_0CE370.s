.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800CD770
/* 0CE370 800CD770 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CE374 800CD774 3084FFFF */  andi  $a0, $a0, 0xffff
/* 0CE378 800CD778 A3A0000F */  sb    $zero, 0xf($sp)
/* 0CE37C 800CD77C AFA00008 */  sw    $zero, 8($sp)
.L800CD780:
/* 0CE380 800CD780 93AE000F */  lbu   $t6, 0xf($sp)
/* 0CE384 800CD784 31CF0010 */  andi  $t7, $t6, 0x10
/* 0CE388 800CD788 11E00004 */  beqz  $t7, .L800CD79C
/* 0CE38C 800CD78C 00000000 */   nop   
/* 0CE390 800CD790 24180015 */  li    $t8, 21
/* 0CE394 800CD794 10000002 */  b     .L800CD7A0
/* 0CE398 800CD798 A3B8000E */   sb    $t8, 0xe($sp)
.L800CD79C:
/* 0CE39C 800CD79C A3A0000E */  sb    $zero, 0xe($sp)
.L800CD7A0:
/* 0CE3A0 800CD7A0 93B9000F */  lbu   $t9, 0xf($sp)
/* 0CE3A4 800CD7A4 30890400 */  andi  $t1, $a0, 0x400
/* 0CE3A8 800CD7A8 00194040 */  sll   $t0, $t9, 1
/* 0CE3AC 800CD7AC 11200003 */  beqz  $t1, .L800CD7BC
/* 0CE3B0 800CD7B0 A3A8000F */   sb    $t0, 0xf($sp)
/* 0CE3B4 800CD7B4 10000002 */  b     .L800CD7C0
/* 0CE3B8 800CD7B8 24050001 */   li    $a1, 1
.L800CD7BC:
/* 0CE3BC 800CD7BC 00002825 */  move  $a1, $zero
.L800CD7C0:
/* 0CE3C0 800CD7C0 93AA000F */  lbu   $t2, 0xf($sp)
/* 0CE3C4 800CD7C4 8FA80008 */  lw    $t0, 8($sp)
/* 0CE3C8 800CD7C8 93AF000E */  lbu   $t7, 0xe($sp)
/* 0CE3CC 800CD7CC 30AB00FF */  andi  $t3, $a1, 0xff
/* 0CE3D0 800CD7D0 00046840 */  sll   $t5, $a0, 1
/* 0CE3D4 800CD7D4 014B6025 */  or    $t4, $t2, $t3
/* 0CE3D8 800CD7D8 01A02025 */  move  $a0, $t5
/* 0CE3DC 800CD7DC 319800FF */  andi  $t8, $t4, 0xff
/* 0CE3E0 800CD7E0 25090001 */  addiu $t1, $t0, 1
/* 0CE3E4 800CD7E4 29210010 */  slti  $at, $t1, 0x10
/* 0CE3E8 800CD7E8 A3AC000F */  sb    $t4, 0xf($sp)
/* 0CE3EC 800CD7EC 308EFFFF */  andi  $t6, $a0, 0xffff
/* 0CE3F0 800CD7F0 030FC826 */  xor   $t9, $t8, $t7
/* 0CE3F4 800CD7F4 AFA90008 */  sw    $t1, 8($sp)
/* 0CE3F8 800CD7F8 01C02025 */  move  $a0, $t6
/* 0CE3FC 800CD7FC 1420FFE0 */  bnez  $at, .L800CD780
/* 0CE400 800CD800 A3B9000F */   sb    $t9, 0xf($sp)
/* 0CE404 800CD804 93A2000F */  lbu   $v0, 0xf($sp)
/* 0CE408 800CD808 27BD0010 */  addiu $sp, $sp, 0x10
/* 0CE40C 800CD80C 304A001F */  andi  $t2, $v0, 0x1f
/* 0CE410 800CD810 01401025 */  move  $v0, $t2
/* 0CE414 800CD814 304B00FF */  andi  $t3, $v0, 0xff
/* 0CE418 800CD818 03E00008 */  jr    $ra
/* 0CE41C 800CD81C 01601025 */   move  $v0, $t3

glabel func_800CD820
/* 0CE420 800CD820 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CE424 800CD824 A3A0000F */  sb    $zero, 0xf($sp)
/* 0CE428 800CD828 AFA00008 */  sw    $zero, 8($sp)
.L800CD82C:
/* 0CE42C 800CD82C 240E0007 */  li    $t6, 7
/* 0CE430 800CD830 AFAE0004 */  sw    $t6, 4($sp)
.L800CD834:
/* 0CE434 800CD834 93AF000F */  lbu   $t7, 0xf($sp)
/* 0CE438 800CD838 31F80080 */  andi  $t8, $t7, 0x80
/* 0CE43C 800CD83C 13000004 */  beqz  $t8, .L800CD850
/* 0CE440 800CD840 00000000 */   nop   
/* 0CE444 800CD844 24190085 */  li    $t9, 133
/* 0CE448 800CD848 10000002 */  b     .L800CD854
/* 0CE44C 800CD84C A3B9000E */   sb    $t9, 0xe($sp)
.L800CD850:
/* 0CE450 800CD850 A3A0000E */  sb    $zero, 0xe($sp)
.L800CD854:
/* 0CE454 800CD854 93A8000F */  lbu   $t0, 0xf($sp)
/* 0CE458 800CD858 8FAA0008 */  lw    $t2, 8($sp)
/* 0CE45C 800CD85C 24010020 */  li    $at, 32
/* 0CE460 800CD860 00084840 */  sll   $t1, $t0, 1
/* 0CE464 800CD864 15410004 */  bne   $t2, $at, .L800CD878
/* 0CE468 800CD868 A3A9000F */   sb    $t1, 0xf($sp)
/* 0CE46C 800CD86C 312B00FF */  andi  $t3, $t1, 0xff
/* 0CE470 800CD870 1000000E */  b     .L800CD8AC
/* 0CE474 800CD874 A3AB000F */   sb    $t3, 0xf($sp)
.L800CD878:
/* 0CE478 800CD878 8FAD0004 */  lw    $t5, 4($sp)
/* 0CE47C 800CD87C 908C0000 */  lbu   $t4, ($a0)
/* 0CE480 800CD880 240E0001 */  li    $t6, 1
/* 0CE484 800CD884 01AE7804 */  sllv  $t7, $t6, $t5
/* 0CE488 800CD888 018FC024 */  and   $t8, $t4, $t7
/* 0CE48C 800CD88C 13000003 */  beqz  $t8, .L800CD89C
/* 0CE490 800CD890 00000000 */   nop   
/* 0CE494 800CD894 10000002 */  b     .L800CD8A0
/* 0CE498 800CD898 24050001 */   li    $a1, 1
.L800CD89C:
/* 0CE49C 800CD89C 00002825 */  move  $a1, $zero
.L800CD8A0:
/* 0CE4A0 800CD8A0 93B9000F */  lbu   $t9, 0xf($sp)
/* 0CE4A4 800CD8A4 03254025 */  or    $t0, $t9, $a1
/* 0CE4A8 800CD8A8 A3A8000F */  sb    $t0, 0xf($sp)
.L800CD8AC:
/* 0CE4AC 800CD8AC 8FAE0004 */  lw    $t6, 4($sp)
/* 0CE4B0 800CD8B0 93AA000F */  lbu   $t2, 0xf($sp)
/* 0CE4B4 800CD8B4 93A9000E */  lbu   $t1, 0xe($sp)
/* 0CE4B8 800CD8B8 25CDFFFF */  addiu $t5, $t6, -1
/* 0CE4BC 800CD8BC AFAD0004 */  sw    $t5, 4($sp)
/* 0CE4C0 800CD8C0 01495826 */  xor   $t3, $t2, $t1
/* 0CE4C4 800CD8C4 05A1FFDB */  bgez  $t5, .L800CD834
/* 0CE4C8 800CD8C8 A3AB000F */   sb    $t3, 0xf($sp)
/* 0CE4CC 800CD8CC 8FAC0008 */  lw    $t4, 8($sp)
/* 0CE4D0 800CD8D0 24840001 */  addiu $a0, $a0, 1
/* 0CE4D4 800CD8D4 258F0001 */  addiu $t7, $t4, 1
/* 0CE4D8 800CD8D8 29E10021 */  slti  $at, $t7, 0x21
/* 0CE4DC 800CD8DC 1420FFD3 */  bnez  $at, .L800CD82C
/* 0CE4E0 800CD8E0 AFAF0008 */   sw    $t7, 8($sp)
/* 0CE4E4 800CD8E4 93A2000F */  lbu   $v0, 0xf($sp)
/* 0CE4E8 800CD8E8 03E00008 */  jr    $ra
/* 0CE4EC 800CD8EC 27BD0010 */   addiu $sp, $sp, 0x10

glabel func_800CD8F0
/* 0CE4F0 800CD8F0 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 0CE4F4 800CD8F4 8FB80070 */  lw    $t8, 0x70($sp)
/* 0CE4F8 800CD8F8 3C0E8013 */  lui   $t6, %hi(D_8012CDE0) # $t6, 0x8013
/* 0CE4FC 800CD8FC 25CECDE0 */  addiu $t6, %lo(D_8012CDE0) # addiu $t6, $t6, -0x3220
/* 0CE500 800CD900 240F0002 */  li    $t7, 2
/* 0CE504 800CD904 24010001 */  li    $at, 1
/* 0CE508 800CD908 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0CE50C 800CD90C AFA40060 */  sw    $a0, 0x60($sp)
/* 0CE510 800CD910 AFA50064 */  sw    $a1, 0x64($sp)
/* 0CE514 800CD914 AFA60068 */  sw    $a2, 0x68($sp)
/* 0CE518 800CD918 AFA7006C */  sw    $a3, 0x6c($sp)
/* 0CE51C 800CD91C AFB00018 */  sw    $s0, 0x18($sp)
/* 0CE520 800CD920 AFA0005C */  sw    $zero, 0x5c($sp)
/* 0CE524 800CD924 AFAE0054 */  sw    $t6, 0x54($sp)
/* 0CE528 800CD928 13010009 */  beq   $t8, $at, .L800CD950
/* 0CE52C 800CD92C AFAF0028 */   sw    $t7, 0x28($sp)
/* 0CE530 800CD930 97B9006A */  lhu   $t9, 0x6a($sp)
/* 0CE534 800CD934 2B210007 */  slti  $at, $t9, 7
/* 0CE538 800CD938 10200005 */  beqz  $at, .L800CD950
/* 0CE53C 800CD93C 00000000 */   nop   
/* 0CE540 800CD940 13200003 */  beqz  $t9, .L800CD950
/* 0CE544 800CD944 00000000 */   nop   
/* 0CE548 800CD948 10000070 */  b     .L800CDB0C
/* 0CE54C 800CD94C 00001025 */   move  $v0, $zero
.L800CD950:
/* 0CE550 800CD950 0C033594 */  jal   func_800CD650
/* 0CE554 800CD954 00000000 */   nop   
/* 0CE558 800CD958 24080003 */  li    $t0, 3
/* 0CE55C 800CD95C 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CE560 800CD960 A028CD90 */  sb    $t0, %lo(D_8012CD90)($at)
/* 0CE564 800CD964 8FA40064 */  lw    $a0, 0x64($sp)
/* 0CE568 800CD968 97A5006A */  lhu   $a1, 0x6a($sp)
/* 0CE56C 800CD96C 0C0336C8 */  jal   func_800CDB20
/* 0CE570 800CD970 8FA6006C */   lw    $a2, 0x6c($sp)
/* 0CE574 800CD974 3C058013 */  lui   $a1, %hi(D_8012CDE0) # $a1, 0x8013
/* 0CE578 800CD978 24A5CDE0 */  addiu $a1, %lo(D_8012CDE0) # addiu $a1, $a1, -0x3220
/* 0CE57C 800CD97C 0C0335B0 */  jal   func_800CD6C0
/* 0CE580 800CD980 24040001 */   li    $a0, 1
/* 0CE584 800CD984 AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CE588 800CD988 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CE58C 800CD98C 00002825 */  move  $a1, $zero
/* 0CE590 800CD990 0C0322EC */  jal   osRecvMesg
/* 0CE594 800CD994 24060001 */   li    $a2, 1
.L800CD998:
/* 0CE598 800CD998 AFA00058 */  sw    $zero, 0x58($sp)
.L800CD99C:
/* 0CE59C 800CD99C 8FAA0058 */  lw    $t2, 0x58($sp)
/* 0CE5A0 800CD9A0 8FAC0058 */  lw    $t4, 0x58($sp)
/* 0CE5A4 800CD9A4 3C018013 */  lui   $at, 0x8013
/* 0CE5A8 800CD9A8 000A5880 */  sll   $t3, $t2, 2
/* 0CE5AC 800CD9AC 002B0821 */  addu  $at, $at, $t3
/* 0CE5B0 800CD9B0 240900FF */  li    $t1, 255
/* 0CE5B4 800CD9B4 AC29CDE0 */  sw    $t1, -0x3220($at)
/* 0CE5B8 800CD9B8 258D0001 */  addiu $t5, $t4, 1
/* 0CE5BC 800CD9BC 29A10010 */  slti  $at, $t5, 0x10
/* 0CE5C0 800CD9C0 1420FFF6 */  bnez  $at, .L800CD99C
/* 0CE5C4 800CD9C4 AFAD0058 */   sw    $t5, 0x58($sp)
/* 0CE5C8 800CD9C8 3C018013 */  lui   $at, %hi(D_8012CE1C) # $at, 0x8013
/* 0CE5CC 800CD9CC 3C058013 */  lui   $a1, %hi(D_8012CDE0) # $a1, 0x8013
/* 0CE5D0 800CD9D0 AC20CE1C */  sw    $zero, %lo(D_8012CE1C)($at)
/* 0CE5D4 800CD9D4 24A5CDE0 */  addiu $a1, %lo(D_8012CDE0) # addiu $a1, $a1, -0x3220
/* 0CE5D8 800CD9D8 0C0335B0 */  jal   func_800CD6C0
/* 0CE5DC 800CD9DC 00002025 */   move  $a0, $zero
/* 0CE5E0 800CD9E0 AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CE5E4 800CD9E4 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CE5E8 800CD9E8 00002825 */  move  $a1, $zero
/* 0CE5EC 800CD9EC 0C0322EC */  jal   osRecvMesg
/* 0CE5F0 800CD9F0 24060001 */   li    $a2, 1
/* 0CE5F4 800CD9F4 8FAF0064 */  lw    $t7, 0x64($sp)
/* 0CE5F8 800CD9F8 3C0E8013 */  lui   $t6, %hi(D_8012CDE0) # $t6, 0x8013
/* 0CE5FC 800CD9FC 25CECDE0 */  addiu $t6, %lo(D_8012CDE0) # addiu $t6, $t6, -0x3220
/* 0CE600 800CDA00 11E0000C */  beqz  $t7, .L800CDA34
/* 0CE604 800CDA04 AFAE0054 */   sw    $t6, 0x54($sp)
/* 0CE608 800CDA08 19E0000A */  blez  $t7, .L800CDA34
/* 0CE60C 800CDA0C AFA00058 */   sw    $zero, 0x58($sp)
.L800CDA10:
/* 0CE610 800CDA10 8FA80058 */  lw    $t0, 0x58($sp)
/* 0CE614 800CDA14 8FA90064 */  lw    $t1, 0x64($sp)
/* 0CE618 800CDA18 8FB80054 */  lw    $t8, 0x54($sp)
/* 0CE61C 800CDA1C 250A0001 */  addiu $t2, $t0, 1
/* 0CE620 800CDA20 0149082A */  slt   $at, $t2, $t1
/* 0CE624 800CDA24 27190001 */  addiu $t9, $t8, 1
/* 0CE628 800CDA28 AFAA0058 */  sw    $t2, 0x58($sp)
/* 0CE62C 800CDA2C 1420FFF8 */  bnez  $at, .L800CDA10
/* 0CE630 800CDA30 AFB90054 */   sw    $t9, 0x54($sp)
.L800CDA34:
/* 0CE634 800CDA34 8FAC0054 */  lw    $t4, 0x54($sp)
/* 0CE638 800CDA38 27AB002C */  addiu $t3, $sp, 0x2c
/* 0CE63C 800CDA3C 258E0024 */  addiu $t6, $t4, 0x24
.L800CDA40:
/* 0CE640 800CDA40 89810000 */  lwl   $at, ($t4)
/* 0CE644 800CDA44 99810003 */  lwr   $at, 3($t4)
/* 0CE648 800CDA48 258C000C */  addiu $t4, $t4, 0xc
/* 0CE64C 800CDA4C 256B000C */  addiu $t3, $t3, 0xc
/* 0CE650 800CDA50 AD61FFF4 */  sw    $at, -0xc($t3)
/* 0CE654 800CDA54 8981FFF8 */  lwl   $at, -8($t4)
/* 0CE658 800CDA58 9981FFFB */  lwr   $at, -5($t4)
/* 0CE65C 800CDA5C AD61FFF8 */  sw    $at, -8($t3)
/* 0CE660 800CDA60 8981FFFC */  lwl   $at, -4($t4)
/* 0CE664 800CDA64 9981FFFF */  lwr   $at, -1($t4)
/* 0CE668 800CDA68 158EFFF5 */  bne   $t4, $t6, .L800CDA40
/* 0CE66C 800CDA6C AD61FFFC */   sw    $at, -4($t3)
/* 0CE670 800CDA70 89810000 */  lwl   $at, ($t4)
/* 0CE674 800CDA74 99810003 */  lwr   $at, 3($t4)
/* 0CE678 800CDA78 AD610000 */  sw    $at, ($t3)
/* 0CE67C 800CDA7C 93AF002E */  lbu   $t7, 0x2e($sp)
/* 0CE680 800CDA80 31F800C0 */  andi  $t8, $t7, 0xc0
/* 0CE684 800CDA84 0018C903 */  sra   $t9, $t8, 4
/* 0CE688 800CDA88 17200013 */  bnez  $t9, .L800CDAD8
/* 0CE68C 800CDA8C AFB9005C */   sw    $t9, 0x5c($sp)
/* 0CE690 800CDA90 0C033608 */  jal   func_800CD820
/* 0CE694 800CDA94 8FA4006C */   lw    $a0, 0x6c($sp)
/* 0CE698 800CDA98 93A80052 */  lbu   $t0, 0x52($sp)
/* 0CE69C 800CDA9C 1048000E */  beq   $v0, $t0, .L800CDAD8
/* 0CE6A0 800CDAA0 00000000 */   nop   
/* 0CE6A4 800CDAA4 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CE6A8 800CDAA8 0C033B75 */  jal   func_800CEDD4
/* 0CE6AC 800CDAAC 8FA50064 */   lw    $a1, 0x64($sp)
/* 0CE6B0 800CDAB0 AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CE6B4 800CDAB4 8FAA005C */  lw    $t2, 0x5c($sp)
/* 0CE6B8 800CDAB8 11400005 */  beqz  $t2, .L800CDAD0
/* 0CE6BC 800CDABC 00000000 */   nop   
/* 0CE6C0 800CDAC0 0C0335A5 */  jal   func_800CD694
/* 0CE6C4 800CDAC4 00000000 */   nop   
/* 0CE6C8 800CDAC8 10000010 */  b     .L800CDB0C
/* 0CE6CC 800CDACC 8FA2005C */   lw    $v0, 0x5c($sp)
.L800CDAD0:
/* 0CE6D0 800CDAD0 24090004 */  li    $t1, 4
/* 0CE6D4 800CDAD4 AFA9005C */  sw    $t1, 0x5c($sp)
.L800CDAD8:
/* 0CE6D8 800CDAD8 8FAD005C */  lw    $t5, 0x5c($sp)
/* 0CE6DC 800CDADC 24010004 */  li    $at, 4
/* 0CE6E0 800CDAE0 15A10007 */  bne   $t5, $at, .L800CDB00
/* 0CE6E4 800CDAE4 00000000 */   nop   
/* 0CE6E8 800CDAE8 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0CE6EC 800CDAEC 29D00000 */  slti  $s0, $t6, 0
/* 0CE6F0 800CDAF0 3A100001 */  xori  $s0, $s0, 1
/* 0CE6F4 800CDAF4 25CCFFFF */  addiu $t4, $t6, -1
/* 0CE6F8 800CDAF8 1600FFA7 */  bnez  $s0, .L800CD998
/* 0CE6FC 800CDAFC AFAC0028 */   sw    $t4, 0x28($sp)
.L800CDB00:
/* 0CE700 800CDB00 0C0335A5 */  jal   func_800CD694
/* 0CE704 800CDB04 00000000 */   nop   
/* 0CE708 800CDB08 8FA2005C */  lw    $v0, 0x5c($sp)
.L800CDB0C:
/* 0CE70C 800CDB0C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0CE710 800CDB10 8FB00018 */  lw    $s0, 0x18($sp)
/* 0CE714 800CDB14 27BD0060 */  addiu $sp, $sp, 0x60
/* 0CE718 800CDB18 03E00008 */  jr    $ra
/* 0CE71C 800CDB1C 00000000 */   nop   

glabel func_800CDB20
/* 0CE720 800CDB20 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0CE724 800CDB24 3C0E8013 */  lui   $t6, %hi(D_8012CDE0) # $t6, 0x8013
/* 0CE728 800CDB28 25CECDE0 */  addiu $t6, %lo(D_8012CDE0) # addiu $t6, $t6, -0x3220
/* 0CE72C 800CDB2C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CE730 800CDB30 AFA40048 */  sw    $a0, 0x48($sp)
/* 0CE734 800CDB34 AFA5004C */  sw    $a1, 0x4c($sp)
/* 0CE738 800CDB38 AFA60050 */  sw    $a2, 0x50($sp)
/* 0CE73C 800CDB3C AFAE0044 */  sw    $t6, 0x44($sp)
/* 0CE740 800CDB40 AFA00018 */  sw    $zero, 0x18($sp)
.L800CDB44:
/* 0CE744 800CDB44 8FAF0018 */  lw    $t7, 0x18($sp)
/* 0CE748 800CDB48 8FB90018 */  lw    $t9, 0x18($sp)
/* 0CE74C 800CDB4C 3C018013 */  lui   $at, 0x8013
/* 0CE750 800CDB50 000FC080 */  sll   $t8, $t7, 2
/* 0CE754 800CDB54 00380821 */  addu  $at, $at, $t8
/* 0CE758 800CDB58 AC20CDE0 */  sw    $zero, -0x3220($at)
/* 0CE75C 800CDB5C 27280001 */  addiu $t0, $t9, 1
/* 0CE760 800CDB60 29010010 */  slti  $at, $t0, 0x10
/* 0CE764 800CDB64 1420FFF7 */  bnez  $at, .L800CDB44
/* 0CE768 800CDB68 AFA80018 */   sw    $t0, 0x18($sp)
/* 0CE76C 800CDB6C 24090001 */  li    $t1, 1
/* 0CE770 800CDB70 3C018013 */  lui   $at, %hi(D_8012CE1C) # $at, 0x8013
/* 0CE774 800CDB74 240A00FF */  li    $t2, 255
/* 0CE778 800CDB78 240B0023 */  li    $t3, 35
/* 0CE77C 800CDB7C 240C0001 */  li    $t4, 1
/* 0CE780 800CDB80 240D0003 */  li    $t5, 3
/* 0CE784 800CDB84 AC29CE1C */  sw    $t1, %lo(D_8012CE1C)($at)
/* 0CE788 800CDB88 A3AA001C */  sb    $t2, 0x1c($sp)
/* 0CE78C 800CDB8C A3AB001D */  sb    $t3, 0x1d($sp)
/* 0CE790 800CDB90 A3AC001E */  sb    $t4, 0x1e($sp)
/* 0CE794 800CDB94 A3AD001F */  sb    $t5, 0x1f($sp)
/* 0CE798 800CDB98 0C0335DC */  jal   func_800CD770
/* 0CE79C 800CDB9C 97A4004E */   lhu   $a0, 0x4e($sp)
/* 0CE7A0 800CDBA0 97AE004E */  lhu   $t6, 0x4e($sp)
/* 0CE7A4 800CDBA4 241900FF */  li    $t9, 255
/* 0CE7A8 800CDBA8 A3B90042 */  sb    $t9, 0x42($sp)
/* 0CE7AC 800CDBAC 000E7940 */  sll   $t7, $t6, 5
/* 0CE7B0 800CDBB0 004FC025 */  or    $t8, $v0, $t7
/* 0CE7B4 800CDBB4 A7B80020 */  sh    $t8, 0x20($sp)
/* 0CE7B8 800CDBB8 AFA00018 */  sw    $zero, 0x18($sp)
.L800CDBBC:
/* 0CE7BC 800CDBBC 8FA80050 */  lw    $t0, 0x50($sp)
/* 0CE7C0 800CDBC0 8FAA0018 */  lw    $t2, 0x18($sp)
/* 0CE7C4 800CDBC4 91090000 */  lbu   $t1, ($t0)
/* 0CE7C8 800CDBC8 03AA5821 */  addu  $t3, $sp, $t2
/* 0CE7CC 800CDBCC A1690022 */  sb    $t1, 0x22($t3)
/* 0CE7D0 800CDBD0 8FAE0018 */  lw    $t6, 0x18($sp)
/* 0CE7D4 800CDBD4 8FAC0050 */  lw    $t4, 0x50($sp)
/* 0CE7D8 800CDBD8 25CF0001 */  addiu $t7, $t6, 1
/* 0CE7DC 800CDBDC 29E10020 */  slti  $at, $t7, 0x20
/* 0CE7E0 800CDBE0 258D0001 */  addiu $t5, $t4, 1
/* 0CE7E4 800CDBE4 AFAF0018 */  sw    $t7, 0x18($sp)
/* 0CE7E8 800CDBE8 1420FFF4 */  bnez  $at, .L800CDBBC
/* 0CE7EC 800CDBEC AFAD0050 */   sw    $t5, 0x50($sp)
/* 0CE7F0 800CDBF0 8FB80048 */  lw    $t8, 0x48($sp)
/* 0CE7F4 800CDBF4 1300000E */  beqz  $t8, .L800CDC30
/* 0CE7F8 800CDBF8 00000000 */   nop   
/* 0CE7FC 800CDBFC 1B00000C */  blez  $t8, .L800CDC30
/* 0CE800 800CDC00 AFA00018 */   sw    $zero, 0x18($sp)
.L800CDC04:
/* 0CE804 800CDC04 8FB90044 */  lw    $t9, 0x44($sp)
/* 0CE808 800CDC08 A3200000 */  sb    $zero, ($t9)
/* 0CE80C 800CDC0C 8FAA0018 */  lw    $t2, 0x18($sp)
/* 0CE810 800CDC10 8FAC0048 */  lw    $t4, 0x48($sp)
/* 0CE814 800CDC14 8FA80044 */  lw    $t0, 0x44($sp)
/* 0CE818 800CDC18 254B0001 */  addiu $t3, $t2, 1
/* 0CE81C 800CDC1C 016C082A */  slt   $at, $t3, $t4
/* 0CE820 800CDC20 25090001 */  addiu $t1, $t0, 1
/* 0CE824 800CDC24 AFAB0018 */  sw    $t3, 0x18($sp)
/* 0CE828 800CDC28 1420FFF6 */  bnez  $at, .L800CDC04
/* 0CE82C 800CDC2C AFA90044 */   sw    $t1, 0x44($sp)
.L800CDC30:
/* 0CE830 800CDC30 27AE001C */  addiu $t6, $sp, 0x1c
/* 0CE834 800CDC34 25D80024 */  addiu $t8, $t6, 0x24
/* 0CE838 800CDC38 8FAD0044 */  lw    $t5, 0x44($sp)
.L800CDC3C:
/* 0CE83C 800CDC3C 8DC10000 */  lw    $at, ($t6)
/* 0CE840 800CDC40 25CE000C */  addiu $t6, $t6, 0xc
/* 0CE844 800CDC44 25AD000C */  addiu $t5, $t5, 0xc
/* 0CE848 800CDC48 A9A1FFF4 */  swl   $at, -0xc($t5)
/* 0CE84C 800CDC4C B9A1FFF7 */  swr   $at, -9($t5)
/* 0CE850 800CDC50 8DC1FFF8 */  lw    $at, -8($t6)
/* 0CE854 800CDC54 A9A1FFF8 */  swl   $at, -8($t5)
/* 0CE858 800CDC58 B9A1FFFB */  swr   $at, -5($t5)
/* 0CE85C 800CDC5C 8DC1FFFC */  lw    $at, -4($t6)
/* 0CE860 800CDC60 A9A1FFFC */  swl   $at, -4($t5)
/* 0CE864 800CDC64 15D8FFF5 */  bne   $t6, $t8, .L800CDC3C
/* 0CE868 800CDC68 B9A1FFFF */   swr   $at, -1($t5)
/* 0CE86C 800CDC6C 8DC10000 */  lw    $at, ($t6)
/* 0CE870 800CDC70 240900FE */  li    $t1, 254
/* 0CE874 800CDC74 A9A10000 */  swl   $at, ($t5)
/* 0CE878 800CDC78 B9A10003 */  swr   $at, 3($t5)
/* 0CE87C 800CDC7C 8FB90044 */  lw    $t9, 0x44($sp)
/* 0CE880 800CDC80 27280028 */  addiu $t0, $t9, 0x28
/* 0CE884 800CDC84 AFA80044 */  sw    $t0, 0x44($sp)
/* 0CE888 800CDC88 A1090000 */  sb    $t1, ($t0)
/* 0CE88C 800CDC8C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CE890 800CDC90 27BD0048 */  addiu $sp, $sp, 0x48
/* 0CE894 800CDC94 03E00008 */  jr    $ra
/* 0CE898 800CDC98 00000000 */   nop   

/* 0CE89C 800CDC9C 00000000 */  nop   
