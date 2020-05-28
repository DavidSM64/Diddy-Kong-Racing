.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C7940
/* 0C8540 800C7940 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C8544 800C7944 00A03825 */  move  $a3, $a1
/* 0C8548 800C7948 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C854C 800C794C AFA5002C */  sw    $a1, 0x2c($sp)
/* 0C8550 800C7950 AFA60030 */  sw    $a2, 0x30($sp)
/* 0C8554 800C7954 00C04025 */  move  $t0, $a2
/* 0C8558 800C7958 240E0002 */  li    $t6, 2
/* 0C855C 800C795C 34EF00B0 */  ori   $t7, $a3, 0xb0
/* 0C8560 800C7960 24180007 */  li    $t8, 7
/* 0C8564 800C7964 A7AE0018 */  sh    $t6, 0x18($sp)
/* 0C8568 800C7968 AFA0001C */  sw    $zero, 0x1c($sp)
/* 0C856C 800C796C A3AF0020 */  sb    $t7, 0x20($sp)
/* 0C8570 800C7970 A3B80021 */  sb    $t8, 0x21($sp)
/* 0C8574 800C7974 A3A80022 */  sb    $t0, 0x22($sp)
/* 0C8578 800C7978 00003025 */  move  $a2, $zero
/* 0C857C 800C797C 27A50018 */  addiu $a1, $sp, 0x18
/* 0C8580 800C7980 0C03246B */  jal   func_800C91AC
/* 0C8584 800C7984 24840048 */   addiu $a0, $a0, 0x48
/* 0C8588 800C7988 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C858C 800C798C 27BD0028 */  addiu $sp, $sp, 0x28
/* 0C8590 800C7990 03E00008 */  jr    $ra
/* 0C8594 800C7994 00000000 */   nop   

/* 0C8598 800C7998 00000000 */  nop   
/* 0C859C 800C799C 00000000 */  nop   
