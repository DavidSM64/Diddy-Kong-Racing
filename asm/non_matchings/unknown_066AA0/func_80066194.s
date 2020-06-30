glabel func_80066194
/* 066D94 80066194 3C014120 */  li    $at, 0x41200000 # 10.000000
/* 066D98 80066198 44812000 */  mtc1  $at, $f4
/* 066D9C 8006619C 3C01800E */  lui   $at, %hi(D_800E70A4) # $at, 0x800e
/* 066DA0 800661A0 C42670A4 */  lwc1  $f6, %lo(D_800E70A4)($at)
/* 066DA4 800661A4 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 066DA8 800661A8 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 066DAC 800661AC 44814000 */  mtc1  $at, $f8
/* 066DB0 800661B0 AFBF0024 */  sw    $ra, 0x24($sp)
/* 066DB4 800661B4 3C048012 */  lui   $a0, %hi(D_80120EE0) # $a0, 0x8012
/* 066DB8 800661B8 3C058012 */  lui   $a1, %hi(D_80120D6C) # $a1, 0x8012
/* 066DBC 800661BC 3C073FAA */  lui   $a3, (0x3FAAAAAB >> 16) # lui $a3, 0x3faa
/* 066DC0 800661C0 34E7AAAB */  ori   $a3, (0x3FAAAAAB & 0xFFFF) # ori $a3, $a3, 0xaaab
/* 066DC4 800661C4 24A50D6C */  addiu $a1, %lo(D_80120D6C) # addiu $a1, $a1, 0xd6c
/* 066DC8 800661C8 24840EE0 */  addiu $a0, %lo(D_80120EE0) # addiu $a0, $a0, 0xee0
/* 066DCC 800661CC 3C064270 */  lui   $a2, 0x4270
/* 066DD0 800661D0 E7A40010 */  swc1  $f4, 0x10($sp)
/* 066DD4 800661D4 E7A60014 */  swc1  $f6, 0x14($sp)
/* 066DD8 800661D8 0C033248 */  jal   func_800CC920
/* 066DDC 800661DC E7A80018 */   swc1  $f8, 0x18($sp)
/* 066DE0 800661E0 3C048012 */  lui   $a0, %hi(D_80120EE0) # $a0, 0x8012
/* 066DE4 800661E4 3C058012 */  lui   $a1, %hi(D_80120FE0) # $a1, 0x8012
/* 066DE8 800661E8 24A50FE0 */  addiu $a1, %lo(D_80120FE0) # addiu $a1, $a1, 0xfe0
/* 066DEC 800661EC 0C01BE1C */  jal   func_8006F870
/* 066DF0 800661F0 24840EE0 */   addiu $a0, %lo(D_80120EE0) # addiu $a0, $a0, 0xee0
/* 066DF4 800661F4 8FBF0024 */  lw    $ra, 0x24($sp)
/* 066DF8 800661F8 27BD0028 */  addiu $sp, $sp, 0x28
/* 066DFC 800661FC 03E00008 */  jr    $ra
/* 066E00 80066200 00000000 */   nop   
