glabel __ull_div
/* 0CF6C8 800CEAC8 AFA40000 */  sw    $a0, ($sp)
/* 0CF6CC 800CEACC AFA50004 */  sw    $a1, 4($sp)
/* 0CF6D0 800CEAD0 AFA60008 */  sw    $a2, 8($sp)
/* 0CF6D4 800CEAD4 AFA7000C */  sw    $a3, 0xc($sp)
/* 0CF6D8 800CEAD8 DFAF0008 */  ld    $t7, 8($sp)
/* 0CF6DC 800CEADC DFAE0000 */  ld    $t6, ($sp)
/* 0CF6E0 800CEAE0 01CF001F */  ddivu $zero, $t6, $t7
/* 0CF6E4 800CEAE4 15E00002 */  bnez  $t7, .L800CEAF0
/* 0CF6E8 800CEAE8 00000000 */   nop   
/* 0CF6EC 800CEAEC 0007000D */  break 7
.L800CEAF0:
/* 0CF6F0 800CEAF0 00001012 */  mflo  $v0
/* 0CF6F4 800CEAF4 0002183C */  dsll32 $v1, $v0, 0
/* 0CF6F8 800CEAF8 0003183F */  dsra32 $v1, $v1, 0
/* 0CF6FC 800CEAFC 03E00008 */  jr    $ra
/* 0CF700 800CEB00 0002103F */   dsra32 $v0, $v0, 0

