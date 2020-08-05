glabel alSynFreeVoice
/* 0CA530 800C9930 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CA534 800C9934 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CA538 800C9938 8CA60008 */  lw    $a2, 8($a1)
/* 0CA53C 800C993C 00804025 */  move  $t0, $a0
/* 0CA540 800C9940 00A03825 */  move  $a3, $a1
/* 0CA544 800C9944 50C00023 */  beql  $a2, $zero, .L800C99D4
/* 0CA548 800C9948 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0CA54C 800C994C 8CCE00D8 */  lw    $t6, 0xd8($a2)
/* 0CA550 800C9950 51C0001A */  beql  $t6, $zero, .L800C99BC
/* 0CA554 800C9954 01002025 */   move  $a0, $t0
/* 0CA558 800C9958 AFA5001C */  sw    $a1, 0x1c($sp)
/* 0CA55C 800C995C 0C01959A */  jal   __allocParam
/* 0CA560 800C9960 AFA40018 */   sw    $a0, 0x18($sp)
/* 0CA564 800C9964 8FA7001C */  lw    $a3, 0x1c($sp)
/* 0CA568 800C9968 8FA80018 */  lw    $t0, 0x18($sp)
/* 0CA56C 800C996C 10400018 */  beqz  $v0, .L800C99D0
/* 0CA570 800C9970 00403025 */   move  $a2, $v0
/* 0CA574 800C9974 8CF80008 */  lw    $t8, 8($a3)
/* 0CA578 800C9978 8D0F001C */  lw    $t7, 0x1c($t0)
/* 0CA57C 800C997C 24050003 */  li    $a1, 3
/* 0CA580 800C9980 8F1900D8 */  lw    $t9, 0xd8($t8)
/* 0CA584 800C9984 A4400008 */  sh    $zero, 8($v0)
/* 0CA588 800C9988 01F94821 */  addu  $t1, $t7, $t9
/* 0CA58C 800C998C AC490004 */  sw    $t1, 4($v0)
/* 0CA590 800C9990 8CEA0008 */  lw    $t2, 8($a3)
/* 0CA594 800C9994 AC4A000C */  sw    $t2, 0xc($v0)
/* 0CA598 800C9998 8CEB0008 */  lw    $t3, 8($a3)
/* 0CA59C 800C999C 8D64000C */  lw    $a0, 0xc($t3)
/* 0CA5A0 800C99A0 AFA7001C */  sw    $a3, 0x1c($sp)
/* 0CA5A4 800C99A4 8C990008 */  lw    $t9, 8($a0)
/* 0CA5A8 800C99A8 0320F809 */  jalr  $t9
/* 0CA5AC 800C99AC 00000000 */  nop   
/* 0CA5B0 800C99B0 10000006 */  b     .L800C99CC
/* 0CA5B4 800C99B4 8FA7001C */   lw    $a3, 0x1c($sp)
/* 0CA5B8 800C99B8 01002025 */  move  $a0, $t0
.L800C99BC:
/* 0CA5BC 800C99BC 00C02825 */  move  $a1, $a2
/* 0CA5C0 800C99C0 0C0195C7 */  jal   __freePVoices
/* 0CA5C4 800C99C4 AFA7001C */   sw    $a3, 0x1c($sp)
/* 0CA5C8 800C99C8 8FA7001C */  lw    $a3, 0x1c($sp)
.L800C99CC:
/* 0CA5CC 800C99CC ACE00008 */  sw    $zero, 8($a3)
.L800C99D0:
/* 0CA5D0 800C99D0 8FBF0014 */  lw    $ra, 0x14($sp)
.L800C99D4:
/* 0CA5D4 800C99D4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CA5D8 800C99D8 03E00008 */  jr    $ra
/* 0CA5DC 800C99DC 00000000 */   nop   

