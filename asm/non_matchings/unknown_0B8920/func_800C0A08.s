glabel func_800C0A08
/* 0C1608 800C0A08 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C160C 800C0A0C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C1610 800C0A10 AFA5001C */  sw    $a1, 0x1c($sp)
/* 0C1614 800C0A14 AFA60020 */  sw    $a2, 0x20($sp)
/* 0C1618 800C0A18 0C01E948 */  jal   func_8007A520
/* 0C161C 800C0A1C AFA40018 */   sw    $a0, 0x18($sp)
/* 0C1620 800C0A20 8FA40018 */  lw    $a0, 0x18($sp)
/* 0C1624 800C0A24 3C18800E */  lui   $t8, %hi(D_800E31D8) # $t8, 0x800e
/* 0C1628 800C0A28 8C830000 */  lw    $v1, ($a0)
/* 0C162C 800C0A2C 271831D8 */  addiu $t8, %lo(D_800E31D8) # addiu $t8, $t8, 0x31d8
/* 0C1630 800C0A30 246E0008 */  addiu $t6, $v1, 8
/* 0C1634 800C0A34 AC8E0000 */  sw    $t6, ($a0)
/* 0C1638 800C0A38 3C0F0600 */  lui   $t7, 0x600
/* 0C163C 800C0A3C AC6F0000 */  sw    $t7, ($v1)
/* 0C1640 800C0A40 AC780004 */  sw    $t8, 4($v1)
/* 0C1644 800C0A44 8C830000 */  lw    $v1, ($a0)
/* 0C1648 800C0A48 3C09FA00 */  lui   $t1, 0xfa00
/* 0C164C 800C0A4C 24790008 */  addiu $t9, $v1, 8
/* 0C1650 800C0A50 AC990000 */  sw    $t9, ($a0)
/* 0C1654 800C0A54 3C0D8013 */  lui   $t5, %hi(D_8012A735) # $t5, 0x8013
/* 0C1658 800C0A58 AC690000 */  sw    $t1, ($v1)
/* 0C165C 800C0A5C 91AEA735 */  lbu   $t6, %lo(D_8012A735)($t5)
/* 0C1660 800C0A60 3C0A8013 */  lui   $t2, %hi(D_8012A734) # $t2, 0x8013
/* 0C1664 800C0A64 914BA734 */  lbu   $t3, %lo(D_8012A734)($t2)
/* 0C1668 800C0A68 3C198013 */  lui   $t9, %hi(D_8012A736) # $t9, 0x8013
/* 0C166C 800C0A6C 9329A736 */  lbu   $t1, %lo(D_8012A736)($t9)
/* 0C1670 800C0A70 000E7C00 */  sll   $t7, $t6, 0x10
/* 0C1674 800C0A74 3C0D8013 */  lui   $t5, %hi(D_8012A737) # $t5, 0x8013
/* 0C1678 800C0A78 000B6600 */  sll   $t4, $t3, 0x18
/* 0C167C 800C0A7C 91AEA737 */  lbu   $t6, %lo(D_8012A737)($t5)
/* 0C1680 800C0A80 018FC025 */  or    $t8, $t4, $t7
/* 0C1684 800C0A84 00095200 */  sll   $t2, $t1, 8
/* 0C1688 800C0A88 030A5825 */  or    $t3, $t8, $t2
/* 0C168C 800C0A8C 016E6025 */  or    $t4, $t3, $t6
/* 0C1690 800C0A90 AC6C0004 */  sw    $t4, 4($v1)
/* 0C1694 800C0A94 8C830000 */  lw    $v1, ($a0)
/* 0C1698 800C0A98 3C09FFFD */  lui   $t1, (0xFFFDF6FB >> 16) # lui $t1, 0xfffd
/* 0C169C 800C0A9C 246F0008 */  addiu $t7, $v1, 8
/* 0C16A0 800C0AA0 3C19FCFF */  lui   $t9, (0xFCFFFFFF >> 16) # lui $t9, 0xfcff
/* 0C16A4 800C0AA4 AC8F0000 */  sw    $t7, ($a0)
/* 0C16A8 800C0AA8 3739FFFF */  ori   $t9, (0xFCFFFFFF & 0xFFFF) # ori $t9, $t9, 0xffff
/* 0C16AC 800C0AAC 3529F6FB */  ori   $t1, (0xFFFDF6FB & 0xFFFF) # ori $t1, $t1, 0xf6fb
/* 0C16B0 800C0AB0 AC690004 */  sw    $t1, 4($v1)
/* 0C16B4 800C0AB4 AC790000 */  sw    $t9, ($v1)
/* 0C16B8 800C0AB8 8C830000 */  lw    $v1, ($a0)
/* 0C16BC 800C0ABC 00027C03 */  sra   $t7, $v0, 0x10
/* 0C16C0 800C0AC0 304D03FF */  andi  $t5, $v0, 0x3ff
/* 0C16C4 800C0AC4 000D5B80 */  sll   $t3, $t5, 0xe
/* 0C16C8 800C0AC8 31F903FF */  andi  $t9, $t7, 0x3ff
/* 0C16CC 800C0ACC 3C01F600 */  lui   $at, 0xf600
/* 0C16D0 800C0AD0 24780008 */  addiu $t8, $v1, 8
/* 0C16D4 800C0AD4 01617025 */  or    $t6, $t3, $at
/* 0C16D8 800C0AD8 00194880 */  sll   $t1, $t9, 2
/* 0C16DC 800C0ADC AC980000 */  sw    $t8, ($a0)
/* 0C16E0 800C0AE0 01C9C025 */  or    $t8, $t6, $t1
/* 0C16E4 800C0AE4 AC780000 */  sw    $t8, ($v1)
/* 0C16E8 800C0AE8 0C01ECF4 */  jal   func_8007B3D0
/* 0C16EC 800C0AEC AC600004 */   sw    $zero, 4($v1)
/* 0C16F0 800C0AF0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C16F4 800C0AF4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0C16F8 800C0AF8 03E00008 */  jr    $ra
/* 0C16FC 800C0AFC 00000000 */   nop   

