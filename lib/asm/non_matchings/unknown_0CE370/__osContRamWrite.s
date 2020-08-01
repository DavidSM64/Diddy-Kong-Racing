glabel __osContRamWrite
/* 0CE4F0 800CD8F0 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 0CE4F4 800CD8F4 8FB80070 */  lw    $t8, 0x70($sp)
/* 0CE4F8 800CD8F8 3C0E8013 */  lui   $t6, %hi(__osPfsPifRam) # $t6, 0x8013
/* 0CE4FC 800CD8FC 25CECDE0 */  addiu $t6, %lo(__osPfsPifRam) # addiu $t6, $t6, -0x3220
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
/* 0CE550 800CD950 0C033594 */  jal   __osSiGetAccess
/* 0CE554 800CD954 00000000 */   nop   
/* 0CE558 800CD958 24080003 */  li    $t0, 3
/* 0CE55C 800CD95C 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CE560 800CD960 A028CD90 */  sb    $t0, %lo(D_8012CD90)($at)
/* 0CE564 800CD964 8FA40064 */  lw    $a0, 0x64($sp)
/* 0CE568 800CD968 97A5006A */  lhu   $a1, 0x6a($sp)
/* 0CE56C 800CD96C 0C0336C8 */  jal   __osPackRamWriteData
/* 0CE570 800CD970 8FA6006C */   lw    $a2, 0x6c($sp)
/* 0CE574 800CD974 3C058013 */  lui   $a1, %hi(__osPfsPifRam) # $a1, 0x8013
/* 0CE578 800CD978 24A5CDE0 */  addiu $a1, %lo(__osPfsPifRam) # addiu $a1, $a1, -0x3220
/* 0CE57C 800CD97C 0C0335B0 */  jal   __osSiRawStartDma
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
/* 0CE5CC 800CD9CC 3C058013 */  lui   $a1, %hi(__osPfsPifRam) # $a1, 0x8013
/* 0CE5D0 800CD9D0 AC20CE1C */  sw    $zero, %lo(D_8012CE1C)($at)
/* 0CE5D4 800CD9D4 24A5CDE0 */  addiu $a1, %lo(__osPfsPifRam) # addiu $a1, $a1, -0x3220
/* 0CE5D8 800CD9D8 0C0335B0 */  jal   __osSiRawStartDma
/* 0CE5DC 800CD9DC 00002025 */   move  $a0, $zero
/* 0CE5E0 800CD9E0 AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CE5E4 800CD9E4 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CE5E8 800CD9E8 00002825 */  move  $a1, $zero
/* 0CE5EC 800CD9EC 0C0322EC */  jal   osRecvMesg
/* 0CE5F0 800CD9F0 24060001 */   li    $a2, 1
/* 0CE5F4 800CD9F4 8FAF0064 */  lw    $t7, 0x64($sp)
/* 0CE5F8 800CD9F8 3C0E8013 */  lui   $t6, %hi(__osPfsPifRam) # $t6, 0x8013
/* 0CE5FC 800CD9FC 25CECDE0 */  addiu $t6, %lo(__osPfsPifRam) # addiu $t6, $t6, -0x3220
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
/* 0CE690 800CDA90 0C033608 */  jal   __osContDataCrc
/* 0CE694 800CDA94 8FA4006C */   lw    $a0, 0x6c($sp)
/* 0CE698 800CDA98 93A80052 */  lbu   $t0, 0x52($sp)
/* 0CE69C 800CDA9C 1048000E */  beq   $v0, $t0, .L800CDAD8
/* 0CE6A0 800CDAA0 00000000 */   nop   
/* 0CE6A4 800CDAA4 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CE6A8 800CDAA8 0C033B75 */  jal   __osPfsGetStatus
/* 0CE6AC 800CDAAC 8FA50064 */   lw    $a1, 0x64($sp)
/* 0CE6B0 800CDAB0 AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CE6B4 800CDAB4 8FAA005C */  lw    $t2, 0x5c($sp)
/* 0CE6B8 800CDAB8 11400005 */  beqz  $t2, .L800CDAD0
/* 0CE6BC 800CDABC 00000000 */   nop   
/* 0CE6C0 800CDAC0 0C0335A5 */  jal   __osSiRelAccess
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
/* 0CE700 800CDB00 0C0335A5 */  jal   __osSiRelAccess
/* 0CE704 800CDB04 00000000 */   nop   
/* 0CE708 800CDB08 8FA2005C */  lw    $v0, 0x5c($sp)
.L800CDB0C:
/* 0CE70C 800CDB0C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0CE710 800CDB10 8FB00018 */  lw    $s0, 0x18($sp)
/* 0CE714 800CDB14 27BD0060 */  addiu $sp, $sp, 0x60
/* 0CE718 800CDB18 03E00008 */  jr    $ra
/* 0CE71C 800CDB1C 00000000 */   nop   

