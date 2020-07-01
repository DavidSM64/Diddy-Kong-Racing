glabel func_8009CF68
/* 09DB68 8009CF68 3C0E800E */  lui   $t6, %hi(D_800DF4E4) # $t6, 0x800e
/* 09DB6C 8009CF6C 25CEF4E4 */  addiu $t6, %lo(D_800DF4E4) # addiu $t6, $t6, -0xb1c
/* 09DB70 8009CF70 008E1021 */  addu  $v0, $a0, $t6
/* 09DB74 8009CF74 804F0000 */  lb    $t7, ($v0)
/* 09DB78 8009CF78 3C18800E */  lui   $t8, %hi(D_800DF4E7) # $t8, 0x800e
/* 09DB7C 8009CF7C 15E0000A */  bnez  $t7, .L8009CFA8
/* 09DB80 8009CF80 2718F4E7 */   addiu $t8, %lo(D_800DF4E7) # addiu $t8, $t8, -0xb19
/* 09DB84 8009CF84 10580005 */  beq   $v0, $t8, .L8009CF9C
/* 09DB88 8009CF88 24030001 */   li    $v1, 1
/* 09DB8C 8009CF8C 3C018012 */  lui   $at, %hi(D_801264E2) # $at, 0x8012
/* 09DB90 8009CF90 A02064E2 */  sb    $zero, %lo(D_801264E2)($at)
/* 09DB94 8009CF94 3C018012 */  lui   $at, %hi(D_801264D8) # $at, 0x8012
/* 09DB98 8009CF98 A02064D8 */  sb    $zero, %lo(D_801264D8)($at)
.L8009CF9C:
/* 09DB9C 8009CF9C 3C01800E */  lui   $at, %hi(D_800DF4E0) # $at, 0x800e
/* 09DBA0 8009CFA0 A023F4E0 */  sb    $v1, %lo(D_800DF4E0)($at)
/* 09DBA4 8009CFA4 A0430000 */  sb    $v1, ($v0)
.L8009CFA8:
/* 09DBA8 8009CFA8 03E00008 */  jr    $ra
/* 09DBAC 8009CFAC 00000000 */   nop   

