glabel func_800C9D54
/* 0CA954 800C9D54 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0CA958 800C9D58 AFA40020 */  sw    $a0, 0x20($sp)
/* 0CA95C 800C9D5C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CA960 800C9D60 AFA50024 */  sw    $a1, 0x24($sp)
/* 0CA964 800C9D64 AFA60028 */  sw    $a2, 0x28($sp)
/* 0CA968 800C9D68 AFA7002C */  sw    $a3, 0x2c($sp)
/* 0CA96C 800C9D6C 3C04800D */  lui   $a0, %hi(D_800C9D40) # $a0, 0x800d
/* 0CA970 800C9D70 24849D40 */  addiu $a0, %lo(D_800C9D40) # addiu $a0, $a0, -0x62c0
/* 0CA974 800C9D74 27A70024 */  addiu $a3, $sp, 0x24
/* 0CA978 800C9D78 8FA60020 */  lw    $a2, 0x20($sp)
/* 0CA97C 800C9D7C 0C034FC4 */  jal   _Printf
/* 0CA980 800C9D80 00002825 */   move  $a1, $zero
/* 0CA984 800C9D84 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CA988 800C9D88 27BD0020 */  addiu $sp, $sp, 0x20
/* 0CA98C 800C9D8C 03E00008 */  jr    $ra
/* 0CA990 800C9D90 00000000 */   nop   

/* 0CA994 800C9D94 00000000 */  nop   
/* 0CA998 800C9D98 00000000 */  nop   
/* 0CA99C 800C9D9C 00000000 */  nop   

