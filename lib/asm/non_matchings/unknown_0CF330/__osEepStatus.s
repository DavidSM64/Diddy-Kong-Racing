glabel __osEepStatus
/* 0CF43C 800CE83C 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0CF440 800CE840 3C0E8013 */  lui   $t6, %hi(D_8012CE40) # $t6, 0x8013
/* 0CF444 800CE844 25CECE40 */  addiu $t6, %lo(D_8012CE40) # addiu $t6, $t6, -0x31c0
/* 0CF448 800CE848 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CF44C 800CE84C AFA40030 */  sw    $a0, 0x30($sp)
/* 0CF450 800CE850 AFA50034 */  sw    $a1, 0x34($sp)
/* 0CF454 800CE854 AFA0002C */  sw    $zero, 0x2c($sp)
/* 0CF458 800CE858 AFAE0024 */  sw    $t6, 0x24($sp)
/* 0CF45C 800CE85C AFA00028 */  sw    $zero, 0x28($sp)
.L800CE860:
/* 0CF460 800CE860 8FAF0028 */  lw    $t7, 0x28($sp)
/* 0CF464 800CE864 8FB90028 */  lw    $t9, 0x28($sp)
/* 0CF468 800CE868 3C018013 */  lui   $at, %hi(D_8012CE40) #$at, 0x8013
/* 0CF46C 800CE86C 000FC080 */  sll   $t8, $t7, 2
/* 0CF470 800CE870 00380821 */  addu  $at, $at, $t8
/* 0CF474 800CE874 AC20CE40 */  sw    $zero, %lo(D_8012CE40)($at)
/* 0CF478 800CE878 27280001 */  addiu $t0, $t9, 1
/* 0CF47C 800CE87C 29010010 */  slti  $at, $t0, 0x10
/* 0CF480 800CE880 1420FFF7 */  bnez  $at, .L800CE860
/* 0CF484 800CE884 AFA80028 */   sw    $t0, 0x28($sp)
/* 0CF488 800CE888 3C0A8013 */  lui   $t2, %hi(D_8012CE40) # $t2, 0x8013
/* 0CF48C 800CE88C 24090001 */  li    $t1, 1
/* 0CF490 800CE890 3C018013 */  lui   $at, %hi(D_8012CE7C) # $at, 0x8013
/* 0CF494 800CE894 254ACE40 */  addiu $t2, %lo(D_8012CE40) # addiu $t2, $t2, -0x31c0
/* 0CF498 800CE898 AC29CE7C */  sw    $t1, %lo(D_8012CE7C)($at)
/* 0CF49C 800CE89C AFAA0024 */  sw    $t2, 0x24($sp)
/* 0CF4A0 800CE8A0 AFA00028 */  sw    $zero, 0x28($sp)
.L800CE8A4:
/* 0CF4A4 800CE8A4 8FAB0024 */  lw    $t3, 0x24($sp)
/* 0CF4A8 800CE8A8 A1600000 */  sb    $zero, ($t3)
/* 0CF4AC 800CE8AC 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0CF4B0 800CE8B0 8FAC0024 */  lw    $t4, 0x24($sp)
/* 0CF4B4 800CE8B4 25CF0001 */  addiu $t7, $t6, 1
/* 0CF4B8 800CE8B8 29E10004 */  slti  $at, $t7, 4
/* 0CF4BC 800CE8BC 258D0001 */  addiu $t5, $t4, 1
/* 0CF4C0 800CE8C0 AFAF0028 */  sw    $t7, 0x28($sp)
/* 0CF4C4 800CE8C4 1420FFF7 */  bnez  $at, .L800CE8A4
/* 0CF4C8 800CE8C8 AFAD0024 */   sw    $t5, 0x24($sp)
/* 0CF4CC 800CE8CC 241800FF */  li    $t8, 255
/* 0CF4D0 800CE8D0 24190001 */  li    $t9, 1
/* 0CF4D4 800CE8D4 24080003 */  li    $t0, 3
/* 0CF4D8 800CE8D8 240900FF */  li    $t1, 255
/* 0CF4DC 800CE8DC 240A00FF */  li    $t2, 255
/* 0CF4E0 800CE8E0 240B00FF */  li    $t3, 255
/* 0CF4E4 800CE8E4 240C00FF */  li    $t4, 255
/* 0CF4E8 800CE8E8 A3B8001C */  sb    $t8, 0x1c($sp)
/* 0CF4EC 800CE8EC A3B9001D */  sb    $t9, 0x1d($sp)
/* 0CF4F0 800CE8F0 A3A8001E */  sb    $t0, 0x1e($sp)
/* 0CF4F4 800CE8F4 A3A0001F */  sb    $zero, 0x1f($sp)
/* 0CF4F8 800CE8F8 A3A90020 */  sb    $t1, 0x20($sp)
/* 0CF4FC 800CE8FC A3AA0021 */  sb    $t2, 0x21($sp)
/* 0CF500 800CE900 A3AB0022 */  sb    $t3, 0x22($sp)
/* 0CF504 800CE904 A3AC0023 */  sb    $t4, 0x23($sp)
/* 0CF508 800CE908 27AE001C */  addiu $t6, $sp, 0x1c
/* 0CF50C 800CE90C 8DC10000 */  lw    $at, ($t6)
/* 0CF510 800CE910 8FAD0024 */  lw    $t5, 0x24($sp)
/* 0CF514 800CE914 240A00FE */  li    $t2, 254
/* 0CF518 800CE918 3C058013 */  lui   $a1, %hi(D_8012CE40) # $a1, 0x8013
/* 0CF51C 800CE91C A9A10000 */  swl   $at, ($t5)
/* 0CF520 800CE920 B9A10003 */  swr   $at, 3($t5)
/* 0CF524 800CE924 8DD90004 */  lw    $t9, 4($t6)
/* 0CF528 800CE928 24A5CE40 */  addiu $a1, %lo(D_8012CE40) # addiu $a1, $a1, -0x31c0
/* 0CF52C 800CE92C 24040001 */  li    $a0, 1
/* 0CF530 800CE930 A9B90004 */  swl   $t9, 4($t5)
/* 0CF534 800CE934 B9B90007 */  swr   $t9, 7($t5)
/* 0CF538 800CE938 8FA80024 */  lw    $t0, 0x24($sp)
/* 0CF53C 800CE93C 25090008 */  addiu $t1, $t0, 8
/* 0CF540 800CE940 AFA90024 */  sw    $t1, 0x24($sp)
/* 0CF544 800CE944 0C0335B0 */  jal   __osSiRawStartDma
/* 0CF548 800CE948 A12A0000 */   sb    $t2, ($t1)
/* 0CF54C 800CE94C AFA2002C */  sw    $v0, 0x2c($sp)
/* 0CF550 800CE950 8FA40030 */  lw    $a0, 0x30($sp)
/* 0CF554 800CE954 00002825 */  move  $a1, $zero
/* 0CF558 800CE958 0C0322EC */  jal   osRecvMesg
/* 0CF55C 800CE95C 24060001 */   li    $a2, 1
/* 0CF560 800CE960 240B0005 */  li    $t3, 5
/* 0CF564 800CE964 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CF568 800CE968 3C058013 */  lui   $a1, %hi(D_8012CE40) # $a1, 0x8013
/* 0CF56C 800CE96C A02BCD90 */  sb    $t3, %lo(D_8012CD90)($at)
/* 0CF570 800CE970 24A5CE40 */  addiu $a1, %lo(D_8012CE40) # addiu $a1, $a1, -0x31c0
/* 0CF574 800CE974 0C0335B0 */  jal   __osSiRawStartDma
/* 0CF578 800CE978 00002025 */   move  $a0, $zero
/* 0CF57C 800CE97C AFA2002C */  sw    $v0, 0x2c($sp)
/* 0CF580 800CE980 8FA40030 */  lw    $a0, 0x30($sp)
/* 0CF584 800CE984 00002825 */  move  $a1, $zero
/* 0CF588 800CE988 0C0322EC */  jal   osRecvMesg
/* 0CF58C 800CE98C 24060001 */   li    $a2, 1
/* 0CF590 800CE990 8FAC002C */  lw    $t4, 0x2c($sp)
/* 0CF594 800CE994 11800003 */  beqz  $t4, .L800CE9A4
/* 0CF598 800CE998 00000000 */   nop   
/* 0CF59C 800CE99C 1000002C */  b     .L800CEA50
/* 0CF5A0 800CE9A0 01801025 */   move  $v0, $t4
.L800CE9A4:
/* 0CF5A4 800CE9A4 3C188013 */  lui   $t8, %hi(D_8012CE40) # $t8, 0x8013
/* 0CF5A8 800CE9A8 2718CE40 */  addiu $t8, %lo(D_8012CE40) # addiu $t8, $t8, -0x31c0
/* 0CF5AC 800CE9AC AFB80024 */  sw    $t8, 0x24($sp)
/* 0CF5B0 800CE9B0 AFA00028 */  sw    $zero, 0x28($sp)
.L800CE9B4:
/* 0CF5B4 800CE9B4 8FAF0024 */  lw    $t7, 0x24($sp)
/* 0CF5B8 800CE9B8 A1E00000 */  sb    $zero, ($t7)
/* 0CF5BC 800CE9BC 8FB90028 */  lw    $t9, 0x28($sp)
/* 0CF5C0 800CE9C0 8FAD0024 */  lw    $t5, 0x24($sp)
/* 0CF5C4 800CE9C4 27280001 */  addiu $t0, $t9, 1
/* 0CF5C8 800CE9C8 29010004 */  slti  $at, $t0, 4
/* 0CF5CC 800CE9CC 25AE0001 */  addiu $t6, $t5, 1
/* 0CF5D0 800CE9D0 AFA80028 */  sw    $t0, 0x28($sp)
/* 0CF5D4 800CE9D4 1420FFF7 */  bnez  $at, .L800CE9B4
/* 0CF5D8 800CE9D8 AFAE0024 */   sw    $t6, 0x24($sp)
/* 0CF5DC 800CE9DC 8FA90024 */  lw    $t1, 0x24($sp)
/* 0CF5E0 800CE9E0 27AA001C */  addiu $t2, $sp, 0x1c
/* 0CF5E4 800CE9E4 89210000 */  lwl   $at, ($t1)
/* 0CF5E8 800CE9E8 99210003 */  lwr   $at, 3($t1)
/* 0CF5EC 800CE9EC AD410000 */  sw    $at, ($t2)
/* 0CF5F0 800CE9F0 892C0004 */  lwl   $t4, 4($t1)
/* 0CF5F4 800CE9F4 992C0007 */  lwr   $t4, 7($t1)
/* 0CF5F8 800CE9F8 AD4C0004 */  sw    $t4, 4($t2)
/* 0CF5FC 800CE9FC 93B8001E */  lbu   $t8, 0x1e($sp)
/* 0CF600 800CEA00 8FAE0034 */  lw    $t6, 0x34($sp)
/* 0CF604 800CEA04 330F00C0 */  andi  $t7, $t8, 0xc0
/* 0CF608 800CEA08 000F6903 */  sra   $t5, $t7, 4
/* 0CF60C 800CEA0C A1CD0003 */  sb    $t5, 3($t6)
/* 0CF610 800CEA10 93B90021 */  lbu   $t9, 0x21($sp)
/* 0CF614 800CEA14 93AB0020 */  lbu   $t3, 0x20($sp)
/* 0CF618 800CEA18 8FA90034 */  lw    $t1, 0x34($sp)
/* 0CF61C 800CEA1C 00194200 */  sll   $t0, $t9, 8
/* 0CF620 800CEA20 010B5025 */  or    $t2, $t0, $t3
/* 0CF624 800CEA24 A52A0000 */  sh    $t2, ($t1)
/* 0CF628 800CEA28 8FB80034 */  lw    $t8, 0x34($sp)
/* 0CF62C 800CEA2C 93AC0022 */  lbu   $t4, 0x22($sp)
/* 0CF630 800CEA30 A30C0002 */  sb    $t4, 2($t8)
/* 0CF634 800CEA34 8FAF0034 */  lw    $t7, 0x34($sp)
/* 0CF638 800CEA38 91ED0003 */  lbu   $t5, 3($t7)
/* 0CF63C 800CEA3C 11A00003 */  beqz  $t5, .L800CEA4C
/* 0CF640 800CEA40 00000000 */   nop   
/* 0CF644 800CEA44 10000002 */  b     .L800CEA50
/* 0CF648 800CEA48 01A01025 */   move  $v0, $t5
.L800CEA4C:
/* 0CF64C 800CEA4C 00001025 */  move  $v0, $zero
.L800CEA50:
/* 0CF650 800CEA50 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CF654 800CEA54 27BD0030 */  addiu $sp, $sp, 0x30
/* 0CF658 800CEA58 03E00008 */  jr    $ra
/* 0CF65C 800CEA5C 00000000 */   nop   

