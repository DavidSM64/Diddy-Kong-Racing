glabel func_8005C25C
/* 05CE5C 8005C25C 3C01800E */  lui   $at, %hi(D_800E6A00) # $at, 0x800e
/* 05CE60 8005C260 C4246A00 */  lwc1  $f4, %lo(D_800E6A00)($at)
/* 05CE64 8005C264 3C01800E */  lui   $at, 0x800e
/* 05CE68 8005C268 03E00008 */  jr    $ra
/* 05CE6C 8005C26C E424CB9C */   swc1  $f4, -0x3464($at)

