glabel func_800C0724
/* 0C1324 800C0724 3C02800E */  lui   $v0, %hi(D_800E31C0) # $v0, 0x800e
/* 0C1328 800C0728 244231C0 */  addiu $v0, %lo(D_800E31C0) # addiu $v0, $v0, 0x31c0
/* 0C132C 800C072C 8C440000 */  lw    $a0, ($v0)
/* 0C1330 800C0730 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C1334 800C0734 1080000B */  beqz  $a0, .L800C0764
/* 0C1338 800C0738 AFBF0014 */   sw    $ra, 0x14($sp)
/* 0C133C 800C073C 0C01C450 */  jal   func_80071140
/* 0C1340 800C0740 00000000 */   nop   
/* 0C1344 800C0744 3C02800E */  lui   $v0, %hi(D_800E31C0) # $v0, 0x800e
/* 0C1348 800C0748 3C03800E */  lui   $v1, %hi(D_800E31C8) # $v1, 0x800e
/* 0C134C 800C074C 246331C8 */  addiu $v1, %lo(D_800E31C8) # addiu $v1, $v1, 0x31c8
/* 0C1350 800C0750 244231C0 */  addiu $v0, %lo(D_800E31C0) # addiu $v0, $v0, 0x31c0
/* 0C1354 800C0754 AC400000 */  sw    $zero, ($v0)
/* 0C1358 800C0758 AC400004 */  sw    $zero, 4($v0)
/* 0C135C 800C075C AC600000 */  sw    $zero, ($v1)
/* 0C1360 800C0760 AC600004 */  sw    $zero, 4($v1)
.L800C0764:
/* 0C1364 800C0764 3C01800E */  lui   $at, %hi(D_800E31AC) # $at, 0x800e
/* 0C1368 800C0768 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C136C 800C076C AC2031AC */  sw    $zero, %lo(D_800E31AC)($at)
/* 0C1370 800C0770 3C01800E */  lui   $at, %hi(D_800E31D0) # $at, 0x800e
/* 0C1374 800C0774 AC2031D0 */  sw    $zero, %lo(D_800E31D0)($at)
/* 0C1378 800C0778 03E00008 */  jr    $ra
/* 0C137C 800C077C 27BD0018 */   addiu $sp, $sp, 0x18

