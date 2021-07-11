glabel __osSetHWIntrRoutine
/* 0D53F0 800D47F0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D53F4 800D47F4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D53F8 800D47F8 AFA40028 */  sw    $a0, 0x28($sp)
/* 0D53FC 800D47FC AFA5002C */  sw    $a1, 0x2c($sp)
/* 0D5400 800D4800 0C034958 */  jal   __osDisableInt
/* 0D5404 800D4804 AFB00018 */   sw    $s0, 0x18($sp)
/* 0D5408 800D4808 8FAF0028 */  lw    $t7, 0x28($sp)
/* 0D540C 800D480C 8FAE002C */  lw    $t6, 0x2c($sp)
/* 0D5410 800D4810 3C01800E */  lui   $at, %hi(D_800E48A0) # $at, 0x800e
/* 0D5414 800D4814 000FC080 */  sll   $t8, $t7, 2
/* 0D5418 800D4818 00408025 */  move  $s0, $v0
/* 0D541C 800D481C 00380821 */  addu  $at, $at, $t8
/* 0D5420 800D4820 02002025 */  move  $a0, $s0
/* 0D5424 800D4824 0C034960 */  jal   __osRestoreInt
/* 0D5428 800D4828 AC2E48A0 */   sw    $t6, %lo(D_800E48A0)($at)
/* 0D542C 800D482C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D5430 800D4830 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D5434 800D4834 27BD0028 */  addiu $sp, $sp, 0x28
/* 0D5438 800D4838 03E00008 */  jr    $ra
/* 0D543C 800D483C 00000000 */   nop   

