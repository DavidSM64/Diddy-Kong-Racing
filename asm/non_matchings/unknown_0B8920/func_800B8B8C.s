glabel func_800B8B8C
/* 0B978C 800B8B8C 3C01800E */  lui   $at, %hi(D_800E30DC) # $at, 0x800e
/* 0B9790 800B8B90 3C048013 */  lui   $a0, %hi(D_8012A0D8) # $a0, 0x8013
/* 0B9794 800B8B94 3C058013 */  lui   $a1, %hi(D_8012A0DC) # $a1, 0x8013
/* 0B9798 800B8B98 AC2030DC */  sw    $zero, %lo(D_800E30DC)($at)
/* 0B979C 800B8B9C 24A5A0DC */  addiu $a1, %lo(D_8012A0DC) # addiu $a1, $a1, -0x5f24
/* 0B97A0 800B8BA0 2484A0D8 */  addiu $a0, %lo(D_8012A0D8) # addiu $a0, $a0, -0x5f28
/* 0B97A4 800B8BA4 8C8E0000 */  lw    $t6, ($a0)
/* 0B97A8 800B8BA8 8CAF0000 */  lw    $t7, ($a1)
/* 0B97AC 800B8BAC 3C06800E */  lui   $a2, %hi(D_800E30D4) # $a2, 0x800e
/* 0B97B0 800B8BB0 01CF0019 */  multu $t6, $t7
/* 0B97B4 800B8BB4 24C630D4 */  addiu $a2, %lo(D_800E30D4) # addiu $a2, $a2, 0x30d4
/* 0B97B8 800B8BB8 00001025 */  move  $v0, $zero
/* 0B97BC 800B8BBC 00001825 */  move  $v1, $zero
/* 0B97C0 800B8BC0 0000C012 */  mflo  $t8
/* 0B97C4 800B8BC4 1B00000D */  blez  $t8, .L800B8BFC
/* 0B97C8 800B8BC8 00000000 */   nop   
.L800B8BCC:
/* 0B97CC 800B8BCC 8CD90000 */  lw    $t9, ($a2)
/* 0B97D0 800B8BD0 24420001 */  addiu $v0, $v0, 1
/* 0B97D4 800B8BD4 03234021 */  addu  $t0, $t9, $v1
/* 0B97D8 800B8BD8 AD000000 */  sw    $zero, ($t0)
/* 0B97DC 800B8BDC 8CAA0000 */  lw    $t2, ($a1)
/* 0B97E0 800B8BE0 8C890000 */  lw    $t1, ($a0)
/* 0B97E4 800B8BE4 24630004 */  addiu $v1, $v1, 4
/* 0B97E8 800B8BE8 012A0019 */  multu $t1, $t2
/* 0B97EC 800B8BEC 00005812 */  mflo  $t3
/* 0B97F0 800B8BF0 004B082A */  slt   $at, $v0, $t3
/* 0B97F4 800B8BF4 1420FFF5 */  bnez  $at, .L800B8BCC
/* 0B97F8 800B8BF8 00000000 */   nop   
.L800B8BFC:
/* 0B97FC 800B8BFC 03E00008 */  jr    $ra
/* 0B9800 800B8C00 00000000 */   nop   

