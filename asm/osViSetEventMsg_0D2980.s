.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel osViSetEventMsg
/* 0D2980 800D1D80 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D2984 800D1D84 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D2988 800D1D88 AFA40028 */  sw    $a0, 0x28($sp)
/* 0D298C 800D1D8C AFA5002C */  sw    $a1, 0x2c($sp)
/* 0D2990 800D1D90 AFA60030 */  sw    $a2, 0x30($sp)
/* 0D2994 800D1D94 0C034958 */  jal   __osDisableInt
/* 0D2998 800D1D98 AFB00018 */   sw    $s0, 0x18($sp)
/* 0D299C 800D1D9C 3C0F800E */  lui   $t7, %hi(D_800E4874) # $t7, 0x800e
/* 0D29A0 800D1DA0 8DEF4874 */  lw    $t7, %lo(D_800E4874)($t7)
/* 0D29A4 800D1DA4 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0D29A8 800D1DA8 3C19800E */  lui   $t9, %hi(D_800E4874) # $t9, 0x800e
/* 0D29AC 800D1DAC 3C09800E */  lui   $t1, %hi(D_800E4874) # $t1, 0x800e
/* 0D29B0 800D1DB0 ADEE0010 */  sw    $t6, 0x10($t7)
/* 0D29B4 800D1DB4 8F394874 */  lw    $t9, %lo(D_800E4874)($t9)
/* 0D29B8 800D1DB8 8FB8002C */  lw    $t8, 0x2c($sp)
/* 0D29BC 800D1DBC 00408025 */  move  $s0, $v0
/* 0D29C0 800D1DC0 02002025 */  move  $a0, $s0
/* 0D29C4 800D1DC4 AF380014 */  sw    $t8, 0x14($t9)
/* 0D29C8 800D1DC8 8D294874 */  lw    $t1, %lo(D_800E4874)($t1)
/* 0D29CC 800D1DCC 8FA80030 */  lw    $t0, 0x30($sp)
/* 0D29D0 800D1DD0 0C034960 */  jal   __osRestoreInt
/* 0D29D4 800D1DD4 A5280002 */   sh    $t0, 2($t1)
/* 0D29D8 800D1DD8 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D29DC 800D1DDC 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D29E0 800D1DE0 27BD0028 */  addiu $sp, $sp, 0x28
/* 0D29E4 800D1DE4 03E00008 */  jr    $ra
/* 0D29E8 800D1DE8 00000000 */   nop   

/* 0D29EC 800D1DEC 00000000 */  nop   
