glabel osStartThread
/* 0C95A0 800C89A0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C95A4 800C89A4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0C95A8 800C89A8 AFA40028 */  sw    $a0, 0x28($sp)
/* 0C95AC 800C89AC AFB10018 */  sw    $s1, 0x18($sp)
/* 0C95B0 800C89B0 0C034958 */  jal   __osDisableInt
/* 0C95B4 800C89B4 AFB00014 */   sw    $s0, 0x14($sp)
/* 0C95B8 800C89B8 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0C95BC 800C89BC 24010001 */  li    $at, 1
/* 0C95C0 800C89C0 00408025 */  move  $s0, $v0
/* 0C95C4 800C89C4 95D10010 */  lhu   $s1, 0x10($t6)
/* 0C95C8 800C89C8 1221000C */  beq   $s1, $at, .L800C89FC
/* 0C95CC 800C89CC 24010008 */   li    $at, 8
/* 0C95D0 800C89D0 1621002A */  bne   $s1, $at, .L800C8A7C
/* 0C95D4 800C89D4 00000000 */   nop   
/* 0C95D8 800C89D8 8FB80028 */  lw    $t8, 0x28($sp)
/* 0C95DC 800C89DC 240F0002 */  li    $t7, 2
/* 0C95E0 800C89E0 3C04800E */  lui   $a0, %hi(D_800E4888) # $a0, 0x800e
/* 0C95E4 800C89E4 A70F0010 */  sh    $t7, 0x10($t8)
/* 0C95E8 800C89E8 8FA50028 */  lw    $a1, 0x28($sp)
/* 0C95EC 800C89EC 0C034CF3 */  jal   __osEnqueueThread
/* 0C95F0 800C89F0 24844888 */   addiu $a0, %lo(D_800E4888) # addiu $a0, $a0, 0x4888
/* 0C95F4 800C89F4 10000021 */  b     .L800C8A7C
/* 0C95F8 800C89F8 00000000 */   nop   
.L800C89FC:
/* 0C95FC 800C89FC 8FB90028 */  lw    $t9, 0x28($sp)
/* 0C9600 800C8A00 8F280008 */  lw    $t0, 8($t9)
/* 0C9604 800C8A04 11000005 */  beqz  $t0, .L800C8A1C
/* 0C9608 800C8A08 00000000 */   nop   
/* 0C960C 800C8A0C 3C09800E */  lui   $t1, %hi(D_800E4888) # $t1, 0x800e
/* 0C9610 800C8A10 25294888 */  addiu $t1, %lo(D_800E4888) # addiu $t1, $t1, 0x4888
/* 0C9614 800C8A14 1509000A */  bne   $t0, $t1, .L800C8A40
/* 0C9618 800C8A18 00000000 */   nop   
.L800C8A1C:
/* 0C961C 800C8A1C 8FAB0028 */  lw    $t3, 0x28($sp)
/* 0C9620 800C8A20 240A0002 */  li    $t2, 2
/* 0C9624 800C8A24 3C04800E */  lui   $a0, %hi(D_800E4888) # $a0, 0x800e
/* 0C9628 800C8A28 A56A0010 */  sh    $t2, 0x10($t3)
/* 0C962C 800C8A2C 8FA50028 */  lw    $a1, 0x28($sp)
/* 0C9630 800C8A30 0C034CF3 */  jal   __osEnqueueThread
/* 0C9634 800C8A34 24844888 */   addiu $a0, %lo(D_800E4888) # addiu $a0, $a0, 0x4888
/* 0C9638 800C8A38 10000010 */  b     .L800C8A7C
/* 0C963C 800C8A3C 00000000 */   nop   
.L800C8A40:
/* 0C9640 800C8A40 8FAD0028 */  lw    $t5, 0x28($sp)
/* 0C9644 800C8A44 240C0008 */  li    $t4, 8
/* 0C9648 800C8A48 A5AC0010 */  sh    $t4, 0x10($t5)
/* 0C964C 800C8A4C 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0C9650 800C8A50 8DC40008 */  lw    $a0, 8($t6)
/* 0C9654 800C8A54 0C034CF3 */  jal   __osEnqueueThread
/* 0C9658 800C8A58 01C02825 */   move  $a1, $t6
/* 0C965C 800C8A5C 8FAF0028 */  lw    $t7, 0x28($sp)
/* 0C9660 800C8A60 0C034D05 */  jal   __osPopThread
/* 0C9664 800C8A64 8DE40008 */   lw    $a0, 8($t7)
/* 0C9668 800C8A68 00408825 */  move  $s1, $v0
/* 0C966C 800C8A6C 3C04800E */  lui   $a0, %hi(D_800E4888) # $a0, 0x800e
/* 0C9670 800C8A70 24844888 */  addiu $a0, %lo(D_800E4888) # addiu $a0, $a0, 0x4888
/* 0C9674 800C8A74 0C034CF3 */  jal   __osEnqueueThread
/* 0C9678 800C8A78 02202825 */   move  $a1, $s1
.L800C8A7C:
/* 0C967C 800C8A7C 3C18800E */  lui   $t8, %hi(__osRunningThread) # $t8, 0x800e
/* 0C9680 800C8A80 8F184890 */  lw    $t8, %lo(__osRunningThread)($t8)
/* 0C9684 800C8A84 17000005 */  bnez  $t8, .L800C8A9C
/* 0C9688 800C8A88 00000000 */   nop   
/* 0C968C 800C8A8C 0C034D09 */  jal   __osDispatchThread
/* 0C9690 800C8A90 00000000 */   nop   
/* 0C9694 800C8A94 1000000F */  b     .L800C8AD4
/* 0C9698 800C8A98 00000000 */   nop   
.L800C8A9C:
/* 0C969C 800C8A9C 3C19800E */  lui   $t9, %hi(__osRunningThread) # $t9, 0x800e
/* 0C96A0 800C8AA0 3C09800E */  lui   $t1, %hi(D_800E4888) # $t1, 0x800e
/* 0C96A4 800C8AA4 8D294888 */  lw    $t1, %lo(D_800E4888)($t1)
/* 0C96A8 800C8AA8 8F394890 */  lw    $t9, %lo(__osRunningThread)($t9)
/* 0C96AC 800C8AAC 8D2A0004 */  lw    $t2, 4($t1)
/* 0C96B0 800C8AB0 8F280004 */  lw    $t0, 4($t9)
/* 0C96B4 800C8AB4 010A082A */  slt   $at, $t0, $t2
/* 0C96B8 800C8AB8 10200006 */  beqz  $at, .L800C8AD4
/* 0C96BC 800C8ABC 00000000 */   nop   
/* 0C96C0 800C8AC0 240B0002 */  li    $t3, 2
/* 0C96C4 800C8AC4 3C04800E */  lui   $a0, %hi(D_800E4888) # $a0, 0x800e
/* 0C96C8 800C8AC8 A72B0010 */  sh    $t3, 0x10($t9)
/* 0C96CC 800C8ACC 0C034CB3 */  jal   __osEnqueueAndYield
/* 0C96D0 800C8AD0 24844888 */   addiu $a0, %lo(D_800E4888) # addiu $a0, $a0, 0x4888
.L800C8AD4:
/* 0C96D4 800C8AD4 0C034960 */  jal   __osRestoreInt
/* 0C96D8 800C8AD8 02002025 */   move  $a0, $s0
/* 0C96DC 800C8ADC 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0C96E0 800C8AE0 8FB00014 */  lw    $s0, 0x14($sp)
/* 0C96E4 800C8AE4 8FB10018 */  lw    $s1, 0x18($sp)
/* 0C96E8 800C8AE8 03E00008 */  jr    $ra
/* 0C96EC 800C8AEC 27BD0028 */   addiu $sp, $sp, 0x28

