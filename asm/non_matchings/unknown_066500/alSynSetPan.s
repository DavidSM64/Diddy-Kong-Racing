glabel alSynSetPan
/* 066720 80065B20 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 066724 80065B24 AFBF0014 */  sw    $ra, 0x14($sp)
/* 066728 80065B28 AFA40020 */  sw    $a0, 0x20($sp)
/* 06672C 80065B2C AFA50024 */  sw    $a1, 0x24($sp)
/* 066730 80065B30 AFA60028 */  sw    $a2, 0x28($sp)
/* 066734 80065B34 8CAF0008 */  lw    $t7, 8($a1)
/* 066738 80065B38 00000000 */  nop   
/* 06673C 80065B3C 11E0001F */  beqz  $t7, .L80065BBC
/* 066740 80065B40 8FBF0014 */   lw    $ra, 0x14($sp)
/* 066744 80065B44 0C01959A */  jal   __allocParam
/* 066748 80065B48 00000000 */   nop   
/* 06674C 80065B4C 1040001A */  beqz  $v0, .L80065BB8
/* 066750 80065B50 240C000C */   li    $t4, 12
/* 066754 80065B54 8FA80024 */  lw    $t0, 0x24($sp)
/* 066758 80065B58 8FB80020 */  lw    $t8, 0x20($sp)
/* 06675C 80065B5C 8D090008 */  lw    $t1, 8($t0)
/* 066760 80065B60 8F19001C */  lw    $t9, 0x1c($t8)
/* 066764 80065B64 8D2A00D8 */  lw    $t2, 0xd8($t1)
/* 066768 80065B68 A44C0008 */  sh    $t4, 8($v0)
/* 06676C 80065B6C 032A5821 */  addu  $t3, $t9, $t2
/* 066770 80065B70 AC4B0004 */  sw    $t3, 4($v0)
/* 066774 80065B74 93A4002B */  lbu   $a0, 0x2b($sp)
/* 066778 80065B78 0C0196FB */  jal   func_80065BEC
/* 06677C 80065B7C AFA2001C */   sw    $v0, 0x1c($sp)
/* 066780 80065B80 8FA6001C */  lw    $a2, 0x1c($sp)
/* 066784 80065B84 24050003 */  li    $a1, 3
/* 066788 80065B88 ACC2000C */  sw    $v0, 0xc($a2)
/* 06678C 80065B8C ACC00000 */  sw    $zero, ($a2)
/* 066790 80065B90 8FAD0024 */  lw    $t5, 0x24($sp)
/* 066794 80065B94 00000000 */  nop   
/* 066798 80065B98 8DAE0008 */  lw    $t6, 8($t5)
/* 06679C 80065B9C 00000000 */  nop   
/* 0667A0 80065BA0 8DC4000C */  lw    $a0, 0xc($t6)
/* 0667A4 80065BA4 00000000 */  nop   
/* 0667A8 80065BA8 8C990008 */  lw    $t9, 8($a0)
/* 0667AC 80065BAC 00000000 */  nop   
/* 0667B0 80065BB0 0320F809 */  jalr  $t9
/* 0667B4 80065BB4 00000000 */  nop   
.L80065BB8:
/* 0667B8 80065BB8 8FBF0014 */  lw    $ra, 0x14($sp)
.L80065BBC:
/* 0667BC 80065BBC 27BD0020 */  addiu $sp, $sp, 0x20
/* 0667C0 80065BC0 03E00008 */  jr    $ra
/* 0667C4 80065BC4 00000000 */   nop   

/* 0667C8 80065BC8 00000000 */  nop   
/* 0667CC 80065BCC 00000000 */  nop   

