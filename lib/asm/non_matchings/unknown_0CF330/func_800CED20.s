glabel func_800CED20
/* 0CF920 800CED20 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0CF924 800CED24 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CF928 800CED28 AFA40020 */  sw    $a0, 0x20($sp)
/* 0CF92C 800CED2C AFA50024 */  sw    $a1, 0x24($sp)
/* 0CF930 800CED30 AFA60028 */  sw    $a2, 0x28($sp)
/* 0CF934 800CED34 0C033594 */  jal   __osSiGetAccess
/* 0CF938 800CED38 AFA0001C */   sw    $zero, 0x1c($sp)
/* 0CF93C 800CED3C 8FA40020 */  lw    $a0, 0x20($sp)
/* 0CF940 800CED40 0C033B75 */  jal   __osPfsGetStatus
/* 0CF944 800CED44 8FA50028 */   lw    $a1, 0x28($sp)
/* 0CF948 800CED48 0C0335A5 */  jal   __osSiRelAccess
/* 0CF94C 800CED4C AFA2001C */   sw    $v0, 0x1c($sp)
/* 0CF950 800CED50 8FAE001C */  lw    $t6, 0x1c($sp)
/* 0CF954 800CED54 11C00003 */  beqz  $t6, .L800CED64
/* 0CF958 800CED58 00000000 */   nop   
/* 0CF95C 800CED5C 10000019 */  b     .L800CEDC4
/* 0CF960 800CED60 01C01025 */   move  $v0, $t6
.L800CED64:
/* 0CF964 800CED64 8FAF0020 */  lw    $t7, 0x20($sp)
/* 0CF968 800CED68 8FB80024 */  lw    $t8, 0x24($sp)
/* 0CF96C 800CED6C AF0F0004 */  sw    $t7, 4($t8)
/* 0CF970 800CED70 8FA80024 */  lw    $t0, 0x24($sp)
/* 0CF974 800CED74 8FB90028 */  lw    $t9, 0x28($sp)
/* 0CF978 800CED78 AD190008 */  sw    $t9, 8($t0)
/* 0CF97C 800CED7C 8FA90024 */  lw    $t1, 0x24($sp)
/* 0CF980 800CED80 AD200000 */  sw    $zero, ($t1)
/* 0CF984 800CED84 0C035659 */  jal   __osGetId
/* 0CF988 800CED88 8FA40024 */   lw    $a0, 0x24($sp)
/* 0CF98C 800CED8C AFA2001C */  sw    $v0, 0x1c($sp)
/* 0CF990 800CED90 8FAA001C */  lw    $t2, 0x1c($sp)
/* 0CF994 800CED94 11400003 */  beqz  $t2, .L800CEDA4
/* 0CF998 800CED98 00000000 */   nop   
/* 0CF99C 800CED9C 10000009 */  b     .L800CEDC4
/* 0CF9A0 800CEDA0 01401025 */   move  $v0, $t2
.L800CEDA4:
/* 0CF9A4 800CEDA4 0C033D4C */  jal   osPfsChecker
/* 0CF9A8 800CEDA8 8FA40024 */   lw    $a0, 0x24($sp)
/* 0CF9AC 800CEDAC 8FAB0024 */  lw    $t3, 0x24($sp)
/* 0CF9B0 800CEDB0 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0CF9B4 800CEDB4 8D6C0000 */  lw    $t4, ($t3)
/* 0CF9B8 800CEDB8 358D0001 */  ori   $t5, $t4, 1
/* 0CF9BC 800CEDBC AD6D0000 */  sw    $t5, ($t3)
/* 0CF9C0 800CEDC0 8FA2001C */  lw    $v0, 0x1c($sp)
.L800CEDC4:
/* 0CF9C4 800CEDC4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CF9C8 800CEDC8 27BD0020 */  addiu $sp, $sp, 0x20
/* 0CF9CC 800CEDCC 03E00008 */  jr    $ra
/* 0CF9D0 800CEDD0 00000000 */   nop   

