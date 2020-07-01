glabel osCreateMesgQueue
/* 0C9420 800C8820 3C0E800E */  lui   $t6, %hi(D_800E4880) # $t6, 0x800e
/* 0C9424 800C8824 3C0F800E */  lui   $t7, %hi(D_800E4880) # $t7, 0x800e
/* 0C9428 800C8828 25CE4880 */  addiu $t6, %lo(D_800E4880) # addiu $t6, $t6, 0x4880
/* 0C942C 800C882C 25EF4880 */  addiu $t7, %lo(D_800E4880) # addiu $t7, $t7, 0x4880
/* 0C9430 800C8830 AC8E0000 */  sw    $t6, ($a0)
/* 0C9434 800C8834 AC8F0004 */  sw    $t7, 4($a0)
/* 0C9438 800C8838 AC800008 */  sw    $zero, 8($a0)
/* 0C943C 800C883C AC80000C */  sw    $zero, 0xc($a0)
/* 0C9440 800C8840 AC860010 */  sw    $a2, 0x10($a0)
/* 0C9444 800C8844 03E00008 */  jr    $ra
/* 0C9448 800C8848 AC850014 */   sw    $a1, 0x14($a0)

/* 0C944C 800C884C 00000000 */  nop   

