glabel func_8002C71C
/* 02D31C 8002C71C 848E0020 */  lh    $t6, 0x20($a0)
/* 02D320 8002C720 2408D8F0 */  li    $t0, -10000
/* 02D324 8002C724 A4880038 */  sh    $t0, 0x38($a0)
/* 02D328 8002C728 00001025 */  move  $v0, $zero
/* 02D32C 8002C72C 19C00023 */  blez  $t6, .L8002C7BC
/* 02D330 8002C730 00001825 */   move  $v1, $zero
/* 02D334 8002C734 00002825 */  move  $a1, $zero
/* 02D338 8002C738 2409000A */  li    $t1, 10
.L8002C73C:
/* 02D33C 8002C73C 8C8F000C */  lw    $t7, 0xc($a0)
/* 02D340 8002C740 00000000 */  nop   
/* 02D344 8002C744 01E5C021 */  addu  $t8, $t7, $a1
/* 02D348 8002C748 8F190008 */  lw    $t9, 8($t8)
/* 02D34C 8002C74C 00000000 */  nop   
/* 02D350 8002C750 332A2000 */  andi  $t2, $t9, 0x2000
/* 02D354 8002C754 11400014 */  beqz  $t2, .L8002C7A8
/* 02D358 8002C758 00000000 */   nop   
/* 02D35C 8002C75C 8C8B0034 */  lw    $t3, 0x34($a0)
/* 02D360 8002C760 00026040 */  sll   $t4, $v0, 1
/* 02D364 8002C764 016C6821 */  addu  $t5, $t3, $t4
/* 02D368 8002C768 A5A30000 */  sh    $v1, ($t5)
/* 02D36C 8002C76C 8C8F000C */  lw    $t7, 0xc($a0)
/* 02D370 8002C770 8C8E0000 */  lw    $t6, ($a0)
/* 02D374 8002C774 01E5C021 */  addu  $t8, $t7, $a1
/* 02D378 8002C778 87190002 */  lh    $t9, 2($t8)
/* 02D37C 8002C77C 84870038 */  lh    $a3, 0x38($a0)
/* 02D380 8002C780 03290019 */  multu $t9, $t1
/* 02D384 8002C784 24420001 */  addiu $v0, $v0, 1
/* 02D388 8002C788 00005012 */  mflo  $t2
/* 02D38C 8002C78C 01CA5821 */  addu  $t3, $t6, $t2
/* 02D390 8002C790 85660002 */  lh    $a2, 2($t3)
/* 02D394 8002C794 11070003 */  beq   $t0, $a3, .L8002C7A4
/* 02D398 8002C798 00E6082A */   slt   $at, $a3, $a2
/* 02D39C 8002C79C 10200002 */  beqz  $at, .L8002C7A8
/* 02D3A0 8002C7A0 00000000 */   nop   
.L8002C7A4:
/* 02D3A4 8002C7A4 A4860038 */  sh    $a2, 0x38($a0)
.L8002C7A8:
/* 02D3A8 8002C7A8 848C0020 */  lh    $t4, 0x20($a0)
/* 02D3AC 8002C7AC 24630001 */  addiu $v1, $v1, 1
/* 02D3B0 8002C7B0 006C082A */  slt   $at, $v1, $t4
/* 02D3B4 8002C7B4 1420FFE1 */  bnez  $at, .L8002C73C
/* 02D3B8 8002C7B8 24A5000C */   addiu $a1, $a1, 0xc
.L8002C7BC:
/* 02D3BC 8002C7BC 03E00008 */  jr    $ra
/* 02D3C0 8002C7C0 A4820032 */   sh    $v0, 0x32($a0)

