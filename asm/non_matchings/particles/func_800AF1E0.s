glabel func_800AF1E0
/* 0AFDE0 800AF1E0 3C0E800E */  lui   $t6, %hi(gParticleBehavioursAssetTableCount) # $t6, 0x800e
/* 0AFDE4 800AF1E4 8DCE2CF4 */  lw    $t6, %lo(gParticleBehavioursAssetTableCount)($t6)
/* 0AFDE8 800AF1E8 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0AFDEC 800AF1EC 00AE082A */  slt   $at, $a1, $t6
/* 0AFDF0 800AF1F0 10200026 */  beqz  $at, .L800AF28C
/* 0AFDF4 800AF1F4 AFBF001C */   sw    $ra, 0x1c($sp)
/* 0AFDF8 800AF1F8 3C0F800E */  lui   $t7, %hi(gParticleBehavioursAssetTable) # $t7, 0x800e
/* 0AFDFC 800AF1FC 8DEF2CFC */  lw    $t7, %lo(gParticleBehavioursAssetTable)($t7)
/* 0AFE00 800AF200 4448F800 */  cfc1  $t0, $31
/* 0AFE04 800AF204 0005C080 */  sll   $t8, $a1, 2
/* 0AFE08 800AF208 01F8C821 */  addu  $t9, $t7, $t8
/* 0AFE0C 800AF20C 8F220000 */  lw    $v0, ($t9)
/* 0AFE10 800AF210 35010003 */  ori   $at, $t0, 3
/* 0AFE14 800AF214 38210002 */  xori  $at, $at, 2
/* 0AFE18 800AF218 44C1F800 */  ctc1  $at, $31
/* 0AFE1C 800AF21C C4440004 */  lwc1  $f4, 4($v0)
/* 0AFE20 800AF220 C4480008 */  lwc1  $f8, 8($v0)
/* 0AFE24 800AF224 460021A4 */  cvt.w.s $f6, $f4
/* 0AFE28 800AF228 44C8F800 */  ctc1  $t0, $31
/* 0AFE2C 800AF22C 44073000 */  mfc1  $a3, $f6
/* 0AFE30 800AF230 00000000 */  nop   
/* 0AFE34 800AF234 444BF800 */  cfc1  $t3, $31
/* 0AFE38 800AF238 00074C00 */  sll   $t1, $a3, 0x10
/* 0AFE3C 800AF23C 35610003 */  ori   $at, $t3, 3
/* 0AFE40 800AF240 38210002 */  xori  $at, $at, 2
/* 0AFE44 800AF244 44C1F800 */  ctc1  $at, $31
/* 0AFE48 800AF248 00093C03 */  sra   $a3, $t1, 0x10
/* 0AFE4C 800AF24C 460042A4 */  cvt.w.s $f10, $f8
/* 0AFE50 800AF250 44CBF800 */  ctc1  $t3, $31
/* 0AFE54 800AF254 440C5000 */  mfc1  $t4, $f10
/* 0AFE58 800AF258 00000000 */  nop   
/* 0AFE5C 800AF25C 444DF800 */  cfc1  $t5, $31
/* 0AFE60 800AF260 AFAC0010 */  sw    $t4, 0x10($sp)
/* 0AFE64 800AF264 35A10003 */  ori   $at, $t5, 3
/* 0AFE68 800AF268 38210002 */  xori  $at, $at, 2
/* 0AFE6C 800AF26C 44C1F800 */  ctc1  $at, $31
/* 0AFE70 800AF270 C450000C */  lwc1  $f16, 0xc($v0)
/* 0AFE74 800AF274 00000000 */  nop   
/* 0AFE78 800AF278 460084A4 */  cvt.w.s $f18, $f16
/* 0AFE7C 800AF27C 440E9000 */  mfc1  $t6, $f18
/* 0AFE80 800AF280 44CDF800 */  ctc1  $t5, $31
/* 0AFE84 800AF284 0C02BCA7 */  jal   func_800AF29C
/* 0AFE88 800AF288 AFAE0014 */   sw    $t6, 0x14($sp)
.L800AF28C:
/* 0AFE8C 800AF28C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0AFE90 800AF290 27BD0020 */  addiu $sp, $sp, 0x20
/* 0AFE94 800AF294 03E00008 */  jr    $ra
/* 0AFE98 800AF298 00000000 */   nop   

