glabel func_800AC880
/* 0AD480 800AC880 3C02800E */  lui   $v0, %hi(D_800E2A80) # $v0, 0x800e
/* 0AD484 800AC884 24422A80 */  addiu $v0, %lo(D_800E2A80) # addiu $v0, $v0, 0x2a80
/* 0AD488 800AC888 8C4E0000 */  lw    $t6, ($v0)
/* 0AD48C 800AC88C 240F0001 */  li    $t7, 1
/* 0AD490 800AC890 148E0003 */  bne   $a0, $t6, .L800AC8A0
/* 0AD494 800AC894 3C01800E */   lui   $at, %hi(D_800E2A84) # $at, 0x800e
/* 0AD498 800AC898 AC400000 */  sw    $zero, ($v0)
/* 0AD49C 800AC89C AC2F2A84 */  sw    $t7, %lo(D_800E2A84)($at)
.L800AC8A0:
/* 0AD4A0 800AC8A0 03E00008 */  jr    $ra
/* 0AD4A4 800AC8A4 00000000 */   nop   

