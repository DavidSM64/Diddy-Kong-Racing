glabel __ll_mul
/* 0CF7C8 800CEBC8 AFA40000 */  sw    $a0, ($sp)
/* 0CF7CC 800CEBCC AFA50004 */  sw    $a1, 4($sp)
/* 0CF7D0 800CEBD0 AFA60008 */  sw    $a2, 8($sp)
/* 0CF7D4 800CEBD4 AFA7000C */  sw    $a3, 0xc($sp)
/* 0CF7D8 800CEBD8 DFAF0008 */  ld    $t7, 8($sp)
/* 0CF7DC 800CEBDC DFAE0000 */  ld    $t6, ($sp)
/* 0CF7E0 800CEBE0 01CF001D */  dmultu $t6, $t7
/* 0CF7E4 800CEBE4 00001012 */  mflo  $v0
/* 0CF7E8 800CEBE8 0002183C */  dsll32 $v1, $v0, 0
/* 0CF7EC 800CEBEC 0003183F */  dsra32 $v1, $v1, 0
/* 0CF7F0 800CEBF0 03E00008 */  jr    $ra
/* 0CF7F4 800CEBF4 0002103F */   dsra32 $v0, $v0, 0

