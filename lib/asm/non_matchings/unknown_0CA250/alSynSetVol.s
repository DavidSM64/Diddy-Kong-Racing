glabel alSynSetVol
/* 0CA250 800C9650 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0CA254 800C9654 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CA258 800C9658 AFA50024 */  sw    $a1, 0x24($sp)
/* 0CA25C 800C965C AFA60028 */  sw    $a2, 0x28($sp)
/* 0CA260 800C9660 AFA7002C */  sw    $a3, 0x2c($sp)
/* 0CA264 800C9664 8CAF0008 */  lw    $t7, 8($a1)
/* 0CA268 800C9668 51E0001D */  beql  $t7, $zero, .L800C96E0
/* 0CA26C 800C966C 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0CA270 800C9670 0C01959A */  jal   __allocParam
/* 0CA274 800C9674 AFA40020 */   sw    $a0, 0x20($sp)
/* 0CA278 800C9678 10400018 */  beqz  $v0, .L800C96DC
/* 0CA27C 800C967C 8FA40020 */   lw    $a0, 0x20($sp)
/* 0CA280 800C9680 8FB90024 */  lw    $t9, 0x24($sp)
/* 0CA284 800C9684 8C98001C */  lw    $t8, 0x1c($a0)
/* 0CA288 800C9688 240B000B */  li    $t3, 11
/* 0CA28C 800C968C 8F280008 */  lw    $t0, 8($t9)
/* 0CA290 800C9690 8D0900D8 */  lw    $t1, 0xd8($t0)
/* 0CA294 800C9694 A44B0008 */  sh    $t3, 8($v0)
/* 0CA298 800C9698 03095021 */  addu  $t2, $t8, $t1
/* 0CA29C 800C969C AC4A0004 */  sw    $t2, 4($v0)
/* 0CA2A0 800C96A0 87AC002A */  lh    $t4, 0x2a($sp)
/* 0CA2A4 800C96A4 AC4C000C */  sw    $t4, 0xc($v0)
/* 0CA2A8 800C96A8 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0CA2AC 800C96AC 0C0195F1 */  jal   __timeToSamples
/* 0CA2B0 800C96B0 8FA5002C */   lw    $a1, 0x2c($sp)
/* 0CA2B4 800C96B4 8FA6001C */  lw    $a2, 0x1c($sp)
/* 0CA2B8 800C96B8 24050003 */  li    $a1, 3
/* 0CA2BC 800C96BC ACC20010 */  sw    $v0, 0x10($a2)
/* 0CA2C0 800C96C0 ACC00000 */  sw    $zero, ($a2)
/* 0CA2C4 800C96C4 8FAD0024 */  lw    $t5, 0x24($sp)
/* 0CA2C8 800C96C8 8DAE0008 */  lw    $t6, 8($t5)
/* 0CA2CC 800C96CC 8DC4000C */  lw    $a0, 0xc($t6)
/* 0CA2D0 800C96D0 8C990008 */  lw    $t9, 8($a0)
/* 0CA2D4 800C96D4 0320F809 */  jalr  $t9
/* 0CA2D8 800C96D8 00000000 */  nop   
.L800C96DC:
/* 0CA2DC 800C96DC 8FBF0014 */  lw    $ra, 0x14($sp)
.L800C96E0:
/* 0CA2E0 800C96E0 27BD0020 */  addiu $sp, $sp, 0x20
/* 0CA2E4 800C96E4 03E00008 */  jr    $ra
/* 0CA2E8 800C96E8 00000000 */   nop   

/* 0CA2EC 800C96EC 00000000 */  nop   

