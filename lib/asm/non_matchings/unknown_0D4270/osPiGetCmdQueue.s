glabel osPiGetCmdQueue
/* 0D43F0 800D37F0 3C0E800E */  lui   $t6, %hi(__osPiDevMgr) # $t6, 0x800e
/* 0D43F4 800D37F4 8DCE3740 */  lw    $t6, %lo(__osPiDevMgr)($t6)
/* 0D43F8 800D37F8 15C00003 */  bnez  $t6, .L800D3808
/* 0D43FC 800D37FC 00000000 */   nop   
/* 0D4400 800D3800 03E00008 */  jr    $ra
/* 0D4404 800D3804 00001025 */   move  $v0, $zero

.L800D3808:
/* 0D4408 800D3808 3C02800E */  lui   $v0, %hi(D_800E3748) # $v0, 0x800e
/* 0D440C 800D380C 8C423748 */  lw    $v0, %lo(D_800E3748)($v0)
/* 0D4410 800D3810 03E00008 */  jr    $ra
/* 0D4414 800D3814 00000000 */   nop   

/* 0D4418 800D3818 00000000 */  nop   
/* 0D441C 800D381C 00000000 */  nop   
