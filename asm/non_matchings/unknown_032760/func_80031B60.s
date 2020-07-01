glabel func_80031B60
/* 032760 80031B60 3C04800E */  lui   $a0, %hi(D_800DC950) # $a0, 0x800e
/* 032764 80031B64 8C84C950 */  lw    $a0, %lo(D_800DC950)($a0)
/* 032768 80031B68 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 03276C 80031B6C 1080000B */  beqz  $a0, .L80031B9C
/* 032770 80031B70 AFBF0014 */   sw    $ra, 0x14($sp)
/* 032774 80031B74 0C01C450 */  jal   func_80071140
/* 032778 80031B78 00000000 */   nop   
/* 03277C 80031B7C 3C01800E */  lui   $at, %hi(D_800DC950) # $at, 0x800e
/* 032780 80031B80 AC20C950 */  sw    $zero, %lo(D_800DC950)($at)
/* 032784 80031B84 3C01800E */  lui   $at, %hi(D_800DC954) # $at, 0x800e
/* 032788 80031B88 AC20C954 */  sw    $zero, %lo(D_800DC954)($at)
/* 03278C 80031B8C 3C01800E */  lui   $at, %hi(D_800DC960) # $at, 0x800e
/* 032790 80031B90 AC20C960 */  sw    $zero, %lo(D_800DC960)($at)
/* 032794 80031B94 3C01800E */  lui   $at, %hi(D_800DC964) # $at, 0x800e
/* 032798 80031B98 AC20C964 */  sw    $zero, %lo(D_800DC964)($at)
.L80031B9C:
/* 03279C 80031B9C 3C01800E */  lui   $at, %hi(D_800DC95C) # $at, 0x800e
/* 0327A0 80031BA0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0327A4 80031BA4 AC20C95C */  sw    $zero, %lo(D_800DC95C)($at)
/* 0327A8 80031BA8 3C01800E */  lui   $at, %hi(D_800DC958) # $at, 0x800e
/* 0327AC 80031BAC AC20C958 */  sw    $zero, %lo(D_800DC958)($at)
/* 0327B0 80031BB0 03E00008 */  jr    $ra
/* 0327B4 80031BB4 27BD0018 */   addiu $sp, $sp, 0x18

