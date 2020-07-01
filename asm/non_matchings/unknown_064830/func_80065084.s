glabel func_80065084
/* 065C84 80065084 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 065C88 80065088 AFA5001C */  sw    $a1, 0x1c($sp)
/* 065C8C 8006508C AFA60020 */  sw    $a2, 0x20($sp)
/* 065C90 80065090 AFBF0014 */  sw    $ra, 0x14($sp)
/* 065C94 80065094 3C06800D */  lui   $a2, %hi(D_800CC390) # $a2, 0x800d
/* 065C98 80065098 3C05800D */  lui   $a1, %hi(D_800CC3C0) # $a1, 0x800d
/* 065C9C 8006509C 24A5C3C0 */  addiu $a1, %lo(D_800CC3C0) # addiu $a1, $a1, -0x3c40
/* 065CA0 800650A0 24C6C390 */  addiu $a2, %lo(D_800CC390) # addiu $a2, $a2, -0x3c70
/* 065CA4 800650A4 AFA40018 */  sw    $a0, 0x18($sp)
/* 065CA8 800650A8 0C03282C */  jal   func_800CA0B0
/* 065CAC 800650AC 24070007 */   li    $a3, 7
/* 065CB0 800650B0 8FA40018 */  lw    $a0, 0x18($sp)
/* 065CB4 800650B4 00000000 */  nop   
/* 065CB8 800650B8 AC800014 */  sw    $zero, 0x14($a0)
/* 065CBC 800650BC 8FAE0020 */  lw    $t6, 0x20($sp)
/* 065CC0 800650C0 00000000 */  nop   
/* 065CC4 800650C4 AC8E0018 */  sw    $t6, 0x18($a0)
/* 065CC8 800650C8 8FAF001C */  lw    $t7, 0x1c($sp)
/* 065CCC 800650CC 00000000 */  nop   
/* 065CD0 800650D0 AC8F001C */  sw    $t7, 0x1c($a0)
/* 065CD4 800650D4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 065CD8 800650D8 27BD0018 */  addiu $sp, $sp, 0x18
/* 065CDC 800650DC 03E00008 */  jr    $ra
/* 065CE0 800650E0 00000000 */   nop   

