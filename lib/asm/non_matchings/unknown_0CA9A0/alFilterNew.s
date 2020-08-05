glabel alFilterNew
/* 0CACB0 800CA0B0 AC800000 */  sw    $zero, ($a0)
/* 0CACB4 800CA0B4 AC850004 */  sw    $a1, 4($a0)
/* 0CACB8 800CA0B8 AC860008 */  sw    $a2, 8($a0)
/* 0CACBC 800CA0BC A480000C */  sh    $zero, 0xc($a0)
/* 0CACC0 800CA0C0 A480000E */  sh    $zero, 0xe($a0)
/* 0CACC4 800CA0C4 03E00008 */  jr    $ra
/* 0CACC8 800CA0C8 AC870010 */   sw    $a3, 0x10($a0)

/* 0CACCC 800CA0CC 00000000 */  nop   
