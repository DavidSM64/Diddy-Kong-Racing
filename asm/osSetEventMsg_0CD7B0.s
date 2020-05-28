.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel osSetEventMsg
/* 0CD7B0 800CCBB0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0CD7B4 800CCBB4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0CD7B8 800CCBB8 AFA40028 */  sw    $a0, 0x28($sp)
/* 0CD7BC 800CCBBC AFA5002C */  sw    $a1, 0x2c($sp)
/* 0CD7C0 800CCBC0 AFA60030 */  sw    $a2, 0x30($sp)
/* 0CD7C4 800CCBC4 0C034958 */  jal   __osDisableInt
/* 0CD7C8 800CCBC8 AFB00018 */   sw    $s0, 0x18($sp)
/* 0CD7CC 800CCBCC 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0CD7D0 800CCBD0 3C188013 */  lui   $t8, %hi(D_8012CCD0) # $t8, 0x8013
/* 0CD7D4 800CCBD4 8FA8002C */  lw    $t0, 0x2c($sp)
/* 0CD7D8 800CCBD8 2718CCD0 */  addiu $t8, %lo(D_8012CCD0) # addiu $t8, $t8, -0x3330
/* 0CD7DC 800CCBDC 000E78C0 */  sll   $t7, $t6, 3
/* 0CD7E0 800CCBE0 01F8C821 */  addu  $t9, $t7, $t8
/* 0CD7E4 800CCBE4 AFB90020 */  sw    $t9, 0x20($sp)
/* 0CD7E8 800CCBE8 AF280000 */  sw    $t0, ($t9)
/* 0CD7EC 800CCBEC 8FAA0020 */  lw    $t2, 0x20($sp)
/* 0CD7F0 800CCBF0 8FA90030 */  lw    $t1, 0x30($sp)
/* 0CD7F4 800CCBF4 00408025 */  move  $s0, $v0
/* 0CD7F8 800CCBF8 02002025 */  move  $a0, $s0
/* 0CD7FC 800CCBFC 0C034960 */  jal   __osRestoreInt
/* 0CD800 800CCC00 AD490004 */   sw    $t1, 4($t2)
/* 0CD804 800CCC04 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0CD808 800CCC08 8FB00018 */  lw    $s0, 0x18($sp)
/* 0CD80C 800CCC0C 27BD0028 */  addiu $sp, $sp, 0x28
/* 0CD810 800CCC10 03E00008 */  jr    $ra
/* 0CD814 800CCC14 00000000 */   nop   

/* 0CD818 800CCC18 00000000 */  nop   
/* 0CD81C 800CCC1C 00000000 */  nop   
