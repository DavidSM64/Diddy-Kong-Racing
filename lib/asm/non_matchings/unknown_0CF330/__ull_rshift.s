glabel __ull_rshift
/* 0CF660 800CEA60 AFA40000 */  sw    $a0, ($sp)
/* 0CF664 800CEA64 AFA50004 */  sw    $a1, 4($sp)
/* 0CF668 800CEA68 AFA60008 */  sw    $a2, 8($sp)
/* 0CF66C 800CEA6C AFA7000C */  sw    $a3, 0xc($sp)
/* 0CF670 800CEA70 DFAF0008 */  ld    $t7, 8($sp)
/* 0CF674 800CEA74 DFAE0000 */  ld    $t6, ($sp)
/* 0CF678 800CEA78 01EE1016 */  dsrlv $v0, $t6, $t7
/* 0CF67C 800CEA7C 0002183C */  dsll32 $v1, $v0, 0
/* 0CF680 800CEA80 0003183F */  dsra32 $v1, $v1, 0
/* 0CF684 800CEA84 03E00008 */  jr    $ra
/* 0CF688 800CEA88 0002103F */   dsra32 $v0, $v0, 0

