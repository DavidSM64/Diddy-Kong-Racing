glabel set_render_printf_color
/* 0B6E0C 800B620C 3C028013 */  lui   $v0, %hi(D_801285D8) # $v0, 0x8013
/* 0B6E10 800B6210 244285D8 */  addiu $v0, %lo(D_801285D8) # addiu $v0, $v0, -0x7a28
/* 0B6E14 800B6214 8C490000 */  lw    $t1, ($v0)
/* 0B6E18 800B6218 AFA40000 */  sw    $a0, ($sp)
/* 0B6E1C 800B621C AFA50004 */  sw    $a1, 4($sp)
/* 0B6E20 800B6220 AFA60008 */  sw    $a2, 8($sp)
/* 0B6E24 800B6224 AFA7000C */  sw    $a3, 0xc($sp)
/* 0B6E28 800B6228 24080081 */  li    $t0, 129
/* 0B6E2C 800B622C A1280000 */  sb    $t0, ($t1)
/* 0B6E30 800B6230 8C4A0000 */  lw    $t2, ($v0)
/* 0B6E34 800B6234 00A07825 */  move  $t7, $a1
/* 0B6E38 800B6238 254B0001 */  addiu $t3, $t2, 1
/* 0B6E3C 800B623C AC4B0000 */  sw    $t3, ($v0)
/* 0B6E40 800B6240 A1640000 */  sb    $a0, ($t3)
/* 0B6E44 800B6244 8C4D0000 */  lw    $t5, ($v0)
/* 0B6E48 800B6248 01E02825 */  move  $a1, $t7
/* 0B6E4C 800B624C 25AE0001 */  addiu $t6, $t5, 1
/* 0B6E50 800B6250 00C0C025 */  move  $t8, $a2
/* 0B6E54 800B6254 AC4E0000 */  sw    $t6, ($v0)
/* 0B6E58 800B6258 03003025 */  move  $a2, $t8
/* 0B6E5C 800B625C A1C50000 */  sb    $a1, ($t6)
/* 0B6E60 800B6260 8C580000 */  lw    $t8, ($v0)
/* 0B6E64 800B6264 00E0C825 */  move  $t9, $a3
/* 0B6E68 800B6268 03203825 */  move  $a3, $t9
/* 0B6E6C 800B626C 27190001 */  addiu $t9, $t8, 1
/* 0B6E70 800B6270 AC590000 */  sw    $t9, ($v0)
/* 0B6E74 800B6274 A3260000 */  sb    $a2, ($t9)
/* 0B6E78 800B6278 8C490000 */  lw    $t1, ($v0)
/* 0B6E7C 800B627C 00000000 */  nop   
/* 0B6E80 800B6280 252A0001 */  addiu $t2, $t1, 1
/* 0B6E84 800B6284 AC4A0000 */  sw    $t2, ($v0)
/* 0B6E88 800B6288 A1470000 */  sb    $a3, ($t2)
/* 0B6E8C 800B628C 8C4C0000 */  lw    $t4, ($v0)
/* 0B6E90 800B6290 00000000 */  nop   
/* 0B6E94 800B6294 258D0001 */  addiu $t5, $t4, 1
/* 0B6E98 800B6298 AC4D0000 */  sw    $t5, ($v0)
/* 0B6E9C 800B629C A1A00000 */  sb    $zero, ($t5)
/* 0B6EA0 800B62A0 8C4F0000 */  lw    $t7, ($v0)
/* 0B6EA4 800B62A4 00000000 */  nop   
/* 0B6EA8 800B62A8 25F80001 */  addiu $t8, $t7, 1
/* 0B6EAC 800B62AC 03E00008 */  jr    $ra
/* 0B6EB0 800B62B0 AC580000 */   sw    $t8, ($v0)
