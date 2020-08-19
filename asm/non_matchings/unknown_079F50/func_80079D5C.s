glabel func_80079D5C
/* 07A95C 80079D5C 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 07A960 80079D60 AFBF0014 */  sw    $ra, 0x14($sp)
/* 07A964 80079D64 AFA00020 */  sw    $zero, 0x20($sp)
/* 07A968 80079D68 AFA0001C */  sw    $zero, 0x1c($sp)
/* 07A96C 80079D6C 8C850278 */  lw    $a1, 0x278($a0)
/* 07A970 80079D70 AC800278 */  sw    $zero, 0x278($a0)
/* 07A974 80079D74 8CAE0004 */  lw    $t6, 4($a1)
/* 07A978 80079D78 2401FFFE */  li    $at, -2
/* 07A97C 80079D7C 01C17824 */  and   $t7, $t6, $at
/* 07A980 80079D80 ACAF0004 */  sw    $t7, 4($a1)
/* 07A984 80079D84 0C01E790 */  jal   func_80079E40
/* 07A988 80079D88 AFA40028 */   sw    $a0, 0x28($sp)
/* 07A98C 80079D8C 8FA40028 */  lw    $a0, 0x28($sp)
/* 07A990 80079D90 27A50020 */  addiu $a1, $sp, 0x20
/* 07A994 80079D94 8C980274 */  lw    $t8, 0x274($a0)
/* 07A998 80079D98 8C890278 */  lw    $t1, 0x278($a0)
/* 07A99C 80079D9C 2F190001 */  sltiu $t9, $t8, 1
/* 07A9A0 80079DA0 00194040 */  sll   $t0, $t9, 1
/* 07A9A4 80079DA4 2D2A0001 */  sltiu $t2, $t1, 1
/* 07A9A8 80079DA8 010A3825 */  or    $a3, $t0, $t2
/* 07A9AC 80079DAC AFA70018 */  sw    $a3, 0x18($sp)
/* 07A9B0 80079DB0 0C01E835 */  jal   func_8007A0D4
/* 07A9B4 80079DB4 27A6001C */   addiu $a2, $sp, 0x1c
/* 07A9B8 80079DB8 8FA70018 */  lw    $a3, 0x18($sp)
/* 07A9BC 80079DBC 8FA40028 */  lw    $a0, 0x28($sp)
/* 07A9C0 80079DC0 10470006 */  beq   $v0, $a3, .L80079DDC
/* 07A9C4 80079DC4 8FBF0014 */   lw    $ra, 0x14($sp)
/* 07A9C8 80079DC8 8FA50020 */  lw    $a1, 0x20($sp)
/* 07A9CC 80079DCC 8FA6001C */  lw    $a2, 0x1c($sp)
/* 07A9D0 80079DD0 0C01E7EA */  jal   __scExec
/* 07A9D4 80079DD4 00000000 */   nop   
/* 07A9D8 80079DD8 8FBF0014 */  lw    $ra, 0x14($sp)
.L80079DDC:
/* 07A9DC 80079DDC 27BD0028 */  addiu $sp, $sp, 0x28
/* 07A9E0 80079DE0 03E00008 */  jr    $ra
/* 07A9E4 80079DE4 00000000 */   nop   

