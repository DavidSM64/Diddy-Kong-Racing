glabel __ll_lshift
/* 0CF704 800CEB04 AFA40000 */  sw    $a0, ($sp)
/* 0CF708 800CEB08 AFA50004 */  sw    $a1, 4($sp)
/* 0CF70C 800CEB0C AFA60008 */  sw    $a2, 8($sp)
/* 0CF710 800CEB10 AFA7000C */  sw    $a3, 0xc($sp)
/* 0CF714 800CEB14 DFAF0008 */  ld    $t7, 8($sp)
/* 0CF718 800CEB18 DFAE0000 */  ld    $t6, ($sp)
/* 0CF71C 800CEB1C 01EE1014 */  dsllv $v0, $t6, $t7
/* 0CF720 800CEB20 0002183C */  dsll32 $v1, $v0, 0
/* 0CF724 800CEB24 0003183F */  dsra32 $v1, $v1, 0
/* 0CF728 800CEB28 03E00008 */  jr    $ra
/* 0CF72C 800CEB2C 0002103F */   dsra32 $v0, $v0, 0

/* 0CF730 800CEB30 AFA40000 */  sw    $a0, ($sp)
/* 0CF734 800CEB34 AFA50004 */  sw    $a1, 4($sp)
/* 0CF738 800CEB38 AFA60008 */  sw    $a2, 8($sp)
/* 0CF73C 800CEB3C AFA7000C */  sw    $a3, 0xc($sp)
/* 0CF740 800CEB40 DFAF0008 */  ld    $t7, 8($sp)
/* 0CF744 800CEB44 DFAE0000 */  ld    $t6, ($sp)
/* 0CF748 800CEB48 01CF001F */  ddivu $zero, $t6, $t7
/* 0CF74C 800CEB4C 15E00002 */  bnez  $t7, .L800CEB58
/* 0CF750 800CEB50 00000000 */   nop   
/* 0CF754 800CEB54 0007000D */  break 7
.L800CEB58:
/* 0CF758 800CEB58 00001010 */  mfhi  $v0
/* 0CF75C 800CEB5C 0002183C */  dsll32 $v1, $v0, 0
/* 0CF760 800CEB60 0003183F */  dsra32 $v1, $v1, 0
/* 0CF764 800CEB64 03E00008 */  jr    $ra
/* 0CF768 800CEB68 0002103F */   dsra32 $v0, $v0, 0

