glabel func_8006E994
/* 06F594 8006E994 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 06F598 8006E998 AFBF0014 */  sw    $ra, 0x14($sp)
/* 06F59C 8006E99C 00803025 */  move  $a2, $a0
/* 06F5A0 8006E9A0 AFA60028 */  sw    $a2, 0x28($sp)
/* 06F5A4 8006E9A4 27A4001C */  addiu $a0, $sp, 0x1c
/* 06F5A8 8006E9A8 0C01AC89 */  jal   func_8006B224
/* 06F5AC 8006E9AC 27A50020 */   addiu $a1, $sp, 0x20
/* 06F5B0 8006E9B0 8FA60028 */  lw    $a2, 0x28($sp)
/* 06F5B4 8006E9B4 240E0001 */  li    $t6, 1
/* 06F5B8 8006E9B8 A0CE004B */  sb    $t6, 0x4b($a2)
/* 06F5BC 8006E9BC 8FAF0020 */  lw    $t7, 0x20($sp)
/* 06F5C0 8006E9C0 00001025 */  move  $v0, $zero
/* 06F5C4 8006E9C4 19E0000B */  blez  $t7, .L8006E9F4
/* 06F5C8 8006E9C8 00001825 */   move  $v1, $zero
.L8006E9CC:
/* 06F5CC 8006E9CC 8CD80000 */  lw    $t8, ($a2)
/* 06F5D0 8006E9D0 24420001 */  addiu $v0, $v0, 1
/* 06F5D4 8006E9D4 0303C821 */  addu  $t9, $t8, $v1
/* 06F5D8 8006E9D8 A7200000 */  sh    $zero, ($t9)
/* 06F5DC 8006E9DC 8FA80020 */  lw    $t0, 0x20($sp)
/* 06F5E0 8006E9E0 24630002 */  addiu $v1, $v1, 2
/* 06F5E4 8006E9E4 0048082A */  slt   $at, $v0, $t0
/* 06F5E8 8006E9E8 1420FFF8 */  bnez  $at, .L8006E9CC
/* 06F5EC 8006E9EC 00000000 */   nop   
/* 06F5F0 8006E9F0 00001025 */  move  $v0, $zero
.L8006E9F4:
/* 06F5F4 8006E9F4 8FA9001C */  lw    $t1, 0x1c($sp)
/* 06F5F8 8006E9F8 00001825 */  move  $v1, $zero
/* 06F5FC 8006E9FC 1920000A */  blez  $t1, .L8006EA28
/* 06F600 8006EA00 00000000 */   nop   
.L8006EA04:
/* 06F604 8006EA04 8CCA0004 */  lw    $t2, 4($a2)
/* 06F608 8006EA08 24420001 */  addiu $v0, $v0, 1
/* 06F60C 8006EA0C 01435821 */  addu  $t3, $t2, $v1
/* 06F610 8006EA10 AD600000 */  sw    $zero, ($t3)
/* 06F614 8006EA14 8FAC001C */  lw    $t4, 0x1c($sp)
/* 06F618 8006EA18 24630004 */  addiu $v1, $v1, 4
/* 06F61C 8006EA1C 004C082A */  slt   $at, $v0, $t4
/* 06F620 8006EA20 1420FFF8 */  bnez  $at, .L8006EA04
/* 06F624 8006EA24 00000000 */   nop   
.L8006EA28:
/* 06F628 8006EA28 A4C00008 */  sh    $zero, 8($a2)
/* 06F62C 8006EA2C A4C0000A */  sh    $zero, 0xa($a2)
/* 06F630 8006EA30 A4C0000C */  sh    $zero, 0xc($a2)
/* 06F634 8006EA34 A4C0000E */  sh    $zero, 0xe($a2)
/* 06F638 8006EA38 ACC00010 */  sw    $zero, 0x10($a2)
/* 06F63C 8006EA3C A4C00014 */  sh    $zero, 0x14($a2)
/* 06F640 8006EA40 A0C00016 */  sb    $zero, 0x16($a2)
/* 06F644 8006EA44 A0C00017 */  sb    $zero, 0x17($a2)
/* 06F648 8006EA48 8FBF0014 */  lw    $ra, 0x14($sp)
/* 06F64C 8006EA4C 27BD0028 */  addiu $sp, $sp, 0x28
/* 06F650 8006EA50 03E00008 */  jr    $ra
/* 06F654 8006EA54 00000000 */   nop   

/* 06F658 8006EA58 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 06F65C 8006EA5C 3C048012 */  lui   $a0, %hi(gSettingsPtr) # $a0, 0x8012
/* 06F660 8006EA60 AFBF0014 */  sw    $ra, 0x14($sp)
/* 06F664 8006EA64 8C843510 */  lw    $a0, %lo(gSettingsPtr)($a0)
/* 06F668 8006EA68 0C01B9DC */  jal   func_8006E770
/* 06F66C 8006EA6C 24050003 */   li    $a1, 3
/* 06F670 8006EA70 3C048012 */  lui   $a0, %hi(gSettingsPtr) # $a0, 0x8012
/* 06F674 8006EA74 8C843510 */  lw    $a0, %lo(gSettingsPtr)($a0)
/* 06F678 8006EA78 0C01BA65 */  jal   func_8006E994
/* 06F67C 8006EA7C 00000000 */   nop   
/* 06F680 8006EA80 8FBF0014 */  lw    $ra, 0x14($sp)
/* 06F684 8006EA84 27BD0018 */  addiu $sp, $sp, 0x18
/* 06F688 8006EA88 03E00008 */  jr    $ra
/* 06F68C 8006EA8C 00000000 */   nop   

