glabel func_8007F460
/* 080060 8007F460 948E0000 */  lhu   $t6, ($a0)
/* 080064 8007F464 00000000 */  nop   
/* 080068 8007F468 29C10002 */  slti  $at, $t6, 2
/* 08006C 8007F46C 14200047 */  bnez  $at, .L8007F58C
/* 080070 8007F470 00000000 */   nop   
/* 080074 8007F474 948F0004 */  lhu   $t7, 4($a0)
/* 080078 8007F478 94830006 */  lhu   $v1, 6($a0)
/* 08007C 8007F47C 01E5C021 */  addu  $t8, $t7, $a1
/* 080080 8007F480 3302FFFF */  andi  $v0, $t8, 0xffff
/* 080084 8007F484 0043082A */  slt   $at, $v0, $v1
/* 080088 8007F488 14200006 */  bnez  $at, .L8007F4A4
/* 08008C 8007F48C A4980004 */   sh    $t8, 4($a0)
.L8007F490:
/* 080090 8007F490 0043C823 */  subu  $t9, $v0, $v1
/* 080094 8007F494 3322FFFF */  andi  $v0, $t9, 0xffff
/* 080098 8007F498 0043082A */  slt   $at, $v0, $v1
/* 08009C 8007F49C 1020FFFC */  beqz  $at, .L8007F490
/* 0800A0 8007F4A0 A4990004 */   sh    $t9, 4($a0)
.L8007F4A4:
/* 0800A4 8007F4A4 94830002 */  lhu   $v1, 2($a0)
/* 0800A8 8007F4A8 00000000 */  nop   
/* 0800AC 8007F4AC 00034080 */  sll   $t0, $v1, 2
/* 0800B0 8007F4B0 00884821 */  addu  $t1, $a0, $t0
/* 0800B4 8007F4B4 9525000E */  lhu   $a1, 0xe($t1)
/* 0800B8 8007F4B8 00000000 */  nop   
/* 0800BC 8007F4BC 0045082A */  slt   $at, $v0, $a1
/* 0800C0 8007F4C0 14200013 */  bnez  $at, .L8007F510
/* 0800C4 8007F4C4 00000000 */   nop   
.L8007F4C8:
/* 0800C8 8007F4C8 948C0000 */  lhu   $t4, ($a0)
/* 0800CC 8007F4CC 246B0001 */  addiu $t3, $v1, 1
/* 0800D0 8007F4D0 3163FFFF */  andi  $v1, $t3, 0xffff
/* 0800D4 8007F4D4 00455023 */  subu  $t2, $v0, $a1
/* 0800D8 8007F4D8 006C082A */  slt   $at, $v1, $t4
/* 0800DC 8007F4DC A48A0004 */  sh    $t2, 4($a0)
/* 0800E0 8007F4E0 14200003 */  bnez  $at, .L8007F4F0
/* 0800E4 8007F4E4 A48B0002 */   sh    $t3, 2($a0)
/* 0800E8 8007F4E8 A4800002 */  sh    $zero, 2($a0)
/* 0800EC 8007F4EC 3003FFFF */  andi  $v1, $zero, 0xffff
.L8007F4F0:
/* 0800F0 8007F4F0 00036880 */  sll   $t5, $v1, 2
/* 0800F4 8007F4F4 008D7021 */  addu  $t6, $a0, $t5
/* 0800F8 8007F4F8 95C5000E */  lhu   $a1, 0xe($t6)
/* 0800FC 8007F4FC 94820004 */  lhu   $v0, 4($a0)
/* 080100 8007F500 00000000 */  nop   
/* 080104 8007F504 0045082A */  slt   $at, $v0, $a1
/* 080108 8007F508 1020FFEF */  beqz  $at, .L8007F4C8
/* 08010C 8007F50C 00000000 */   nop   
.L8007F510:
/* 080110 8007F510 948F0000 */  lhu   $t7, ($a0)
/* 080114 8007F514 24670001 */  addiu $a3, $v1, 1
/* 080118 8007F518 00EF082A */  slt   $at, $a3, $t7
/* 08011C 8007F51C 00602825 */  move  $a1, $v1
/* 080120 8007F520 14200002 */  bnez  $at, .L8007F52C
/* 080124 8007F524 00E03025 */   move  $a2, $a3
/* 080128 8007F528 00003025 */  move  $a2, $zero
.L8007F52C:
/* 08012C 8007F52C 0006C880 */  sll   $t9, $a2, 2
/* 080130 8007F530 00994021 */  addu  $t0, $a0, $t9
/* 080134 8007F534 9509000C */  lhu   $t1, 0xc($t0)
/* 080138 8007F538 0005C080 */  sll   $t8, $a1, 2
/* 08013C 8007F53C 01220019 */  multu $t1, $v0
/* 080140 8007F540 00981821 */  addu  $v1, $a0, $t8
/* 080144 8007F544 946B000E */  lhu   $t3, 0xe($v1)
/* 080148 8007F548 946D000C */  lhu   $t5, 0xc($v1)
/* 08014C 8007F54C 00005012 */  mflo  $t2
/* 080150 8007F550 00000000 */  nop   
/* 080154 8007F554 00000000 */  nop   
/* 080158 8007F558 014B001A */  div   $zero, $t2, $t3
/* 08015C 8007F55C 15600002 */  bnez  $t3, .L8007F568
/* 080160 8007F560 00000000 */   nop   
/* 080164 8007F564 0007000D */  break 7
.L8007F568:
/* 080168 8007F568 2401FFFF */  li    $at, -1
/* 08016C 8007F56C 15610004 */  bne   $t3, $at, .L8007F580
/* 080170 8007F570 3C018000 */   lui   $at, 0x8000
/* 080174 8007F574 15410002 */  bne   $t2, $at, .L8007F580
/* 080178 8007F578 00000000 */   nop   
/* 08017C 8007F57C 0006000D */  break 6
.L8007F580:
/* 080180 8007F580 00006012 */  mflo  $t4
/* 080184 8007F584 018D7021 */  addu  $t6, $t4, $t5
/* 080188 8007F588 AC8E0008 */  sw    $t6, 8($a0)
.L8007F58C:
/* 08018C 8007F58C 03E00008 */  jr    $ra
/* 080190 8007F590 00000000 */   nop   

