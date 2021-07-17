glabel set_render_printf_position
/* 0B6F5C 800B635C 3C068013 */  lui   $a2, %hi(D_801285D8) # $a2, 0x8013
/* 0B6F60 800B6360 24C685D8 */  addiu $a2, %lo(D_801285D8) # addiu $a2, $a2, -0x7a28
/* 0B6F64 800B6364 8CD90000 */  lw    $t9, ($a2)
/* 0B6F68 800B6368 AFA40000 */  sw    $a0, ($sp)
/* 0B6F6C 800B636C AFA50004 */  sw    $a1, 4($sp)
/* 0B6F70 800B6370 24180082 */  li    $t8, 130
/* 0B6F74 800B6374 A3380000 */  sb    $t8, ($t9)
/* 0B6F78 800B6378 8CC80000 */  lw    $t0, ($a2)
/* 0B6F7C 800B637C 00A07825 */  move  $t7, $a1
/* 0B6F80 800B6380 25090001 */  addiu $t1, $t0, 1
/* 0B6F84 800B6384 ACC90000 */  sw    $t1, ($a2)
/* 0B6F88 800B6388 A1240000 */  sb    $a0, ($t1)
/* 0B6F8C 800B638C 8CCC0000 */  lw    $t4, ($a2)
/* 0B6F90 800B6390 01E02825 */  move  $a1, $t7
/* 0B6F94 800B6394 258D0001 */  addiu $t5, $t4, 1
/* 0B6F98 800B6398 ACCD0000 */  sw    $t5, ($a2)
/* 0B6F9C 800B639C 00047A03 */  sra   $t7, $a0, 8
/* 0B6FA0 800B63A0 A1AF0000 */  sb    $t7, ($t5)
/* 0B6FA4 800B63A4 8CD90000 */  lw    $t9, ($a2)
/* 0B6FA8 800B63A8 00057203 */  sra   $t6, $a1, 8
/* 0B6FAC 800B63AC 27280001 */  addiu $t0, $t9, 1
/* 0B6FB0 800B63B0 ACC80000 */  sw    $t0, ($a2)
/* 0B6FB4 800B63B4 A1050000 */  sb    $a1, ($t0)
/* 0B6FB8 800B63B8 8CCB0000 */  lw    $t3, ($a2)
/* 0B6FBC 800B63BC 00000000 */  nop   
/* 0B6FC0 800B63C0 256C0001 */  addiu $t4, $t3, 1
/* 0B6FC4 800B63C4 ACCC0000 */  sw    $t4, ($a2)
/* 0B6FC8 800B63C8 A18E0000 */  sb    $t6, ($t4)
/* 0B6FCC 800B63CC 8CD80000 */  lw    $t8, ($a2)
/* 0B6FD0 800B63D0 00000000 */  nop   
/* 0B6FD4 800B63D4 27190001 */  addiu $t9, $t8, 1
/* 0B6FD8 800B63D8 ACD90000 */  sw    $t9, ($a2)
/* 0B6FDC 800B63DC A3200000 */  sb    $zero, ($t9)
/* 0B6FE0 800B63E0 8CC90000 */  lw    $t1, ($a2)
/* 0B6FE4 800B63E4 00000000 */  nop   
/* 0B6FE8 800B63E8 252A0001 */  addiu $t2, $t1, 1
/* 0B6FEC 800B63EC 03E00008 */  jr    $ra
/* 0B6FF0 800B63F0 ACCA0000 */   sw    $t2, ($a2)



