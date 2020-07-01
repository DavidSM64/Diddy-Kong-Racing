glabel func_8007FF88
/* 080B88 8007FF88 3C02800E */  lui   $v0, %hi(D_800E1DAC) # $v0, 0x800e
/* 080B8C 8007FF8C 24421DAC */  addiu $v0, %lo(D_800E1DAC) # addiu $v0, $v0, 0x1dac
/* 080B90 8007FF90 8C440000 */  lw    $a0, ($v0)
/* 080B94 8007FF94 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 080B98 8007FF98 10800006 */  beqz  $a0, .L8007FFB4
/* 080B9C 8007FF9C AFBF0014 */   sw    $ra, 0x14($sp)
/* 080BA0 8007FFA0 0C01C450 */  jal   func_80071140
/* 080BA4 8007FFA4 00000000 */   nop   
/* 080BA8 8007FFA8 3C02800E */  lui   $v0, %hi(D_800E1DAC) # $v0, 0x800e
/* 080BAC 8007FFAC 24421DAC */  addiu $v0, %lo(D_800E1DAC) # addiu $v0, $v0, 0x1dac
/* 080BB0 8007FFB0 AC400000 */  sw    $zero, ($v0)
.L8007FFB4:
/* 080BB4 8007FFB4 AC400004 */  sw    $zero, 4($v0)
/* 080BB8 8007FFB8 3C018012 */  lui   $at, %hi(D_80126C2C) # $at, 0x8012
/* 080BBC 8007FFBC 3C03800E */  lui   $v1, %hi(D_800E1DA4) # $v1, 0x800e
/* 080BC0 8007FFC0 AC206C2C */  sw    $zero, %lo(D_80126C2C)($at)
/* 080BC4 8007FFC4 24631DA4 */  addiu $v1, %lo(D_800E1DA4) # addiu $v1, $v1, 0x1da4
/* 080BC8 8007FFC8 AC600000 */  sw    $zero, ($v1)
/* 080BCC 8007FFCC AC600004 */  sw    $zero, 4($v1)
/* 080BD0 8007FFD0 3C01800E */  lui   $at, %hi(D_800E1DB8) # $at, 0x800e
/* 080BD4 8007FFD4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 080BD8 8007FFD8 AC201DB8 */  sw    $zero, %lo(D_800E1DB8)($at)
/* 080BDC 8007FFDC 3C01800E */  lui   $at, %hi(D_800E1DBC) # $at, 0x800e
/* 080BE0 8007FFE0 AC201DBC */  sw    $zero, %lo(D_800E1DBC)($at)
/* 080BE4 8007FFE4 03E00008 */  jr    $ra
/* 080BE8 8007FFE8 27BD0018 */   addiu $sp, $sp, 0x18

