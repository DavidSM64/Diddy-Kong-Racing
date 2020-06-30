glabel func_8006ECAC
/* 06F8AC 8006ECAC 308E0003 */  andi  $t6, $a0, 3
/* 06F8B0 8006ECB0 000E7A80 */  sll   $t7, $t6, 0xa
/* 06F8B4 8006ECB4 35F80080 */  ori   $t8, $t7, 0x80
/* 06F8B8 8006ECB8 3C01800E */  lui   $at, 0x800e
/* 06F8BC 8006ECBC 03E00008 */  jr    $ra
/* 06F8C0 8006ECC0 AC38D37C */   sw    $t8, -0x2c84($at)

/* 06F8C4 8006ECC4 3C02800E */  lui   $v0, %hi(D_800DD37C) # $v0, 0x800e
/* 06F8C8 8006ECC8 2442D37C */  addiu $v0, %lo(D_800DD37C) # addiu $v0, $v0, -0x2c84
/* 06F8CC 8006ECCC 8C4E0000 */  lw    $t6, ($v0)
/* 06F8D0 8006ECD0 00000000 */  nop   
/* 06F8D4 8006ECD4 35CF0100 */  ori   $t7, $t6, 0x100
/* 06F8D8 8006ECD8 03E00008 */  jr    $ra
/* 06F8DC 8006ECDC AC4F0000 */   sw    $t7, ($v0)

