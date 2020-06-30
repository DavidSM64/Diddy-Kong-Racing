glabel func_800B77D4
/* 0B83D4 800B77D4 3C02800E */  lui   $v0, %hi(D_800E3028) # $v0, 0x800e
/* 0B83D8 800B77D8 24423028 */  addiu $v0, %lo(D_800E3028) # addiu $v0, $v0, 0x3028
/* 0B83DC 800B77DC 8C4E0000 */  lw    $t6, ($v0)
/* 0B83E0 800B77E0 3C03800E */  lui   $v1, %hi(D_800E3024) # $v1, 0x800e
/* 0B83E4 800B77E4 01C47821 */  addu  $t7, $t6, $a0
/* 0B83E8 800B77E8 29E1003D */  slti  $at, $t7, 0x3d
/* 0B83EC 800B77EC 14200006 */  bnez  $at, .L800B7808
/* 0B83F0 800B77F0 AC4F0000 */   sw    $t7, ($v0)
/* 0B83F4 800B77F4 24633024 */  addiu $v1, %lo(D_800E3024) # addiu $v1, $v1, 0x3024
/* 0B83F8 800B77F8 8C790000 */  lw    $t9, ($v1)
/* 0B83FC 800B77FC AC400000 */  sw    $zero, ($v0)
/* 0B8400 800B7800 27280001 */  addiu $t0, $t9, 1
/* 0B8404 800B7804 AC680000 */  sw    $t0, ($v1)
.L800B7808:
/* 0B8408 800B7808 03E00008 */  jr    $ra
/* 0B840C 800B780C 00000000 */   nop   

