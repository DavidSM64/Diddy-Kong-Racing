glabel func_800CE470
/* 0CF070 800CE470 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CF074 800CE474 3C0E8013 */  lui   $t6, %hi(D_8012CE40) # $t6, 0x8013
/* 0CF078 800CE478 25CECE40 */  addiu $t6, %lo(D_8012CE40) # addiu $t6, $t6, -0x31c0
/* 0CF07C 800CE47C 308400FF */  andi  $a0, $a0, 0xff
/* 0CF080 800CE480 AFAE0014 */  sw    $t6, 0x14($sp)
/* 0CF084 800CE484 AFA00004 */  sw    $zero, 4($sp)
.L800CE488:
/* 0CF088 800CE488 8FB80004 */  lw    $t8, 4($sp)
/* 0CF08C 800CE48C 8FA80004 */  lw    $t0, 4($sp)
/* 0CF090 800CE490 3C018013 */  lui   $at, 0x8013
/* 0CF094 800CE494 0018C880 */  sll   $t9, $t8, 2
/* 0CF098 800CE498 00390821 */  addu  $at, $at, $t9
/* 0CF09C 800CE49C 240F00FF */  li    $t7, 255
/* 0CF0A0 800CE4A0 AC2FCE40 */  sw    $t7, -0x31c0($at)
/* 0CF0A4 800CE4A4 25090001 */  addiu $t1, $t0, 1
/* 0CF0A8 800CE4A8 29210010 */  slti  $at, $t1, 0x10
/* 0CF0AC 800CE4AC 1420FFF6 */  bnez  $at, .L800CE488
/* 0CF0B0 800CE4B0 AFA90004 */   sw    $t1, 4($sp)
/* 0CF0B4 800CE4B4 240A0001 */  li    $t2, 1
/* 0CF0B8 800CE4B8 3C018013 */  lui   $at, %hi(D_8012CE7C) # $at, 0x8013
/* 0CF0BC 800CE4BC 240B0002 */  li    $t3, 2
/* 0CF0C0 800CE4C0 240C0008 */  li    $t4, 8
/* 0CF0C4 800CE4C4 240D0004 */  li    $t5, 4
/* 0CF0C8 800CE4C8 AC2ACE7C */  sw    $t2, %lo(D_8012CE7C)($at)
/* 0CF0CC 800CE4CC A3AB0008 */  sb    $t3, 8($sp)
/* 0CF0D0 800CE4D0 A3AC0009 */  sb    $t4, 9($sp)
/* 0CF0D4 800CE4D4 A3AD000A */  sb    $t5, 0xa($sp)
/* 0CF0D8 800CE4D8 A3A4000B */  sb    $a0, 0xb($sp)
/* 0CF0DC 800CE4DC AFA00004 */  sw    $zero, 4($sp)
.L800CE4E0:
/* 0CF0E0 800CE4E0 8FAE0004 */  lw    $t6, 4($sp)
/* 0CF0E4 800CE4E4 03AEC021 */  addu  $t8, $sp, $t6
/* 0CF0E8 800CE4E8 A300000C */  sb    $zero, 0xc($t8)
/* 0CF0EC 800CE4EC 8FAF0004 */  lw    $t7, 4($sp)
/* 0CF0F0 800CE4F0 25F90001 */  addiu $t9, $t7, 1
/* 0CF0F4 800CE4F4 2B210008 */  slti  $at, $t9, 8
/* 0CF0F8 800CE4F8 1420FFF9 */  bnez  $at, .L800CE4E0
/* 0CF0FC 800CE4FC AFB90004 */   sw    $t9, 4($sp)
/* 0CF100 800CE500 AFA00004 */  sw    $zero, 4($sp)
.L800CE504:
/* 0CF104 800CE504 8FA80014 */  lw    $t0, 0x14($sp)
/* 0CF108 800CE508 A1000000 */  sb    $zero, ($t0)
/* 0CF10C 800CE50C 8FAB0004 */  lw    $t3, 4($sp)
/* 0CF110 800CE510 8FA90014 */  lw    $t1, 0x14($sp)
/* 0CF114 800CE514 256C0001 */  addiu $t4, $t3, 1
/* 0CF118 800CE518 29810004 */  slti  $at, $t4, 4
/* 0CF11C 800CE51C 252A0001 */  addiu $t2, $t1, 1
/* 0CF120 800CE520 AFAC0004 */  sw    $t4, 4($sp)
/* 0CF124 800CE524 1420FFF7 */  bnez  $at, .L800CE504
/* 0CF128 800CE528 AFAA0014 */   sw    $t2, 0x14($sp)
/* 0CF12C 800CE52C 27AE0008 */  addiu $t6, $sp, 8
/* 0CF130 800CE530 8DC10000 */  lw    $at, ($t6)
/* 0CF134 800CE534 8FAD0014 */  lw    $t5, 0x14($sp)
/* 0CF138 800CE538 240900FE */  li    $t1, 254
/* 0CF13C 800CE53C A9A10000 */  swl   $at, ($t5)
/* 0CF140 800CE540 B9A10003 */  swr   $at, 3($t5)
/* 0CF144 800CE544 8DCF0004 */  lw    $t7, 4($t6)
/* 0CF148 800CE548 A9AF0004 */  swl   $t7, 4($t5)
/* 0CF14C 800CE54C B9AF0007 */  swr   $t7, 7($t5)
/* 0CF150 800CE550 8DC10008 */  lw    $at, 8($t6)
/* 0CF154 800CE554 A9A10008 */  swl   $at, 8($t5)
/* 0CF158 800CE558 B9A1000B */  swr   $at, 0xb($t5)
/* 0CF15C 800CE55C 8FB90014 */  lw    $t9, 0x14($sp)
/* 0CF160 800CE560 2728000C */  addiu $t0, $t9, 0xc
/* 0CF164 800CE564 AFA80014 */  sw    $t0, 0x14($sp)
/* 0CF168 800CE568 A1090000 */  sb    $t1, ($t0)
/* 0CF16C 800CE56C 03E00008 */  jr    $ra
/* 0CF170 800CE570 27BD0018 */   addiu $sp, $sp, 0x18

/* 0CF174 800CE574 00000000 */  nop   
/* 0CF178 800CE578 00000000 */  nop   
/* 0CF17C 800CE57C 00000000 */  nop   

