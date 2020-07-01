glabel func_8003E5C8
/* 03F1C8 8003E5C8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 03F1CC 8003E5CC AFBF0014 */  sw    $ra, 0x14($sp)
/* 03F1D0 8003E5D0 AFA40018 */  sw    $a0, 0x18($sp)
/* 03F1D4 8003E5D4 AFA5001C */  sw    $a1, 0x1c($sp)
/* 03F1D8 8003E5D8 8C8F004C */  lw    $t7, 0x4c($a0)
/* 03F1DC 8003E5DC 240E0002 */  li    $t6, 2
/* 03F1E0 8003E5E0 A5EE0014 */  sh    $t6, 0x14($t7)
/* 03F1E4 8003E5E4 8C98004C */  lw    $t8, 0x4c($a0)
/* 03F1E8 8003E5E8 24190018 */  li    $t9, 24
/* 03F1EC 8003E5EC A3000011 */  sb    $zero, 0x11($t8)
/* 03F1F0 8003E5F0 8C88004C */  lw    $t0, 0x4c($a0)
/* 03F1F4 8003E5F4 00802825 */  move  $a1, $a0
/* 03F1F8 8003E5F8 A1190010 */  sb    $t9, 0x10($t0)
/* 03F1FC 8003E5FC 8C89004C */  lw    $t1, 0x4c($a0)
/* 03F200 8003E600 240401E0 */  li    $a0, 480
/* 03F204 8003E604 A1200012 */  sb    $zero, 0x12($t1)
/* 03F208 8003E608 0C00322D */  jal   func_8000C8B4
/* 03F20C 8003E60C AFA50018 */   sw    $a1, 0x18($sp)
/* 03F210 8003E610 8FA50018 */  lw    $a1, 0x18($sp)
/* 03F214 8003E614 00000000 */  nop   
/* 03F218 8003E618 ACA20078 */  sw    $v0, 0x78($a1)
/* 03F21C 8003E61C ACA0007C */  sw    $zero, 0x7c($a1)
/* 03F220 8003E620 8FBF0014 */  lw    $ra, 0x14($sp)
/* 03F224 8003E624 27BD0018 */  addiu $sp, $sp, 0x18
/* 03F228 8003E628 03E00008 */  jr    $ra
/* 03F22C 8003E62C 00000000 */   nop   

