glabel func_800AF404
/* 0B0004 800AF404 3C08800E */  lui   $t0, %hi(D_800E2E28) # $t0, 0x800e
/* 0B0008 800AF408 25082E28 */  addiu $t0, %lo(D_800E2E28) # addiu $t0, $t0, 0x2e28
/* 0B000C 800AF40C 850E0000 */  lh    $t6, ($t0)
/* 0B0010 800AF410 00047980 */  sll   $t7, $a0, 6
/* 0B0014 800AF414 01CFC021 */  addu  $t8, $t6, $t7
/* 0B0018 800AF418 331901FF */  andi  $t9, $t8, 0x1ff
/* 0B001C 800AF41C A5190000 */  sh    $t9, ($t0)
/* 0B0020 800AF420 3C06800E */  lui   $a2, %hi(D_800E2D08) # $a2, 0x800e
/* 0B0024 800AF424 3C07800E */  lui   $a3, %hi(D_800E2D58) # $a3, 0x800e
/* 0B0028 800AF428 3C03800E */  lui   $v1, %hi(D_800E2D58) # $v1, 0x800e
/* 0B002C 800AF42C 85020000 */  lh    $v0, ($t0)
/* 0B0030 800AF430 24632D58 */  addiu $v1, %lo(D_800E2D58) # addiu $v1, $v1, 0x2d58
/* 0B0034 800AF434 24E72D58 */  addiu $a3, %lo(D_800E2D58) # addiu $a3, $a3, 0x2d58
/* 0B0038 800AF438 24C62D08 */  addiu $a2, %lo(D_800E2D08) # addiu $a2, $a2, 0x2d08
.L800AF43C:
/* 0B003C 800AF43C 84E90000 */  lh    $t1, ($a3)
/* 0B0040 800AF440 84EB0002 */  lh    $t3, 2($a3)
/* 0B0044 800AF444 84ED0004 */  lh    $t5, 4($a3)
/* 0B0048 800AF448 24C60010 */  addiu $a2, $a2, 0x10
/* 0B004C 800AF44C 00C3082B */  sltu  $at, $a2, $v1
/* 0B0050 800AF450 01225021 */  addu  $t2, $t1, $v0
/* 0B0054 800AF454 01626021 */  addu  $t4, $t3, $v0
/* 0B0058 800AF458 01A27021 */  addu  $t6, $t5, $v0
/* 0B005C 800AF45C A4CAFFF6 */  sh    $t2, -0xa($a2)
/* 0B0060 800AF460 A4CCFFFA */  sh    $t4, -6($a2)
/* 0B0064 800AF464 A4CEFFFE */  sh    $t6, -2($a2)
/* 0B0068 800AF468 1420FFF4 */  bnez  $at, .L800AF43C
/* 0B006C 800AF46C 24E70006 */   addiu $a3, $a3, 6
/* 0B0070 800AF470 3C04800E */  lui   $a0, %hi(D_800E2D78) # $a0, 0x800e
/* 0B0074 800AF474 3C06800E */  lui   $a2, %hi(D_800E2DF8) # $a2, 0x800e
/* 0B0078 800AF478 3C03800E */  lui   $v1, %hi(D_800E2DF8) # $v1, 0x800e
/* 0B007C 800AF47C 24632DF8 */  addiu $v1, %lo(D_800E2DF8) # addiu $v1, $v1, 0x2df8
/* 0B0080 800AF480 24C62DF8 */  addiu $a2, %lo(D_800E2DF8) # addiu $a2, $a2, 0x2df8
/* 0B0084 800AF484 24842D78 */  addiu $a0, %lo(D_800E2D78) # addiu $a0, $a0, 0x2d78
.L800AF488:
/* 0B0088 800AF488 84CF0000 */  lh    $t7, ($a2)
/* 0B008C 800AF48C 84D90002 */  lh    $t9, 2($a2)
/* 0B0090 800AF490 84CA0004 */  lh    $t2, 4($a2)
/* 0B0094 800AF494 01E2C021 */  addu  $t8, $t7, $v0
/* 0B0098 800AF498 03224821 */  addu  $t1, $t9, $v0
/* 0B009C 800AF49C A4980006 */  sh    $t8, 6($a0)
/* 0B00A0 800AF4A0 A489000A */  sh    $t1, 0xa($a0)
/* 0B00A4 800AF4A4 84C9000C */  lh    $t1, 0xc($a2)
/* 0B00A8 800AF4A8 84D8000A */  lh    $t8, 0xa($a2)
/* 0B00AC 800AF4AC 84CC0006 */  lh    $t4, 6($a2)
/* 0B00B0 800AF4B0 84CE0008 */  lh    $t6, 8($a2)
/* 0B00B4 800AF4B4 01425821 */  addu  $t3, $t2, $v0
/* 0B00B8 800AF4B8 A48B000E */  sh    $t3, 0xe($a0)
/* 0B00BC 800AF4BC 01225021 */  addu  $t2, $t1, $v0
/* 0B00C0 800AF4C0 0302C821 */  addu  $t9, $t8, $v0
/* 0B00C4 800AF4C4 01826821 */  addu  $t5, $t4, $v0
/* 0B00C8 800AF4C8 01C27821 */  addu  $t7, $t6, $v0
/* 0B00CC 800AF4CC 84CB000E */  lh    $t3, 0xe($a2)
/* 0B00D0 800AF4D0 A48F001A */  sh    $t7, 0x1a($a0)
/* 0B00D4 800AF4D4 A48D0016 */  sh    $t5, 0x16($a0)
/* 0B00D8 800AF4D8 A499001E */  sh    $t9, 0x1e($a0)
/* 0B00DC 800AF4DC A48A0026 */  sh    $t2, 0x26($a0)
/* 0B00E0 800AF4E0 84CA0016 */  lh    $t2, 0x16($a2)
/* 0B00E4 800AF4E4 84D90014 */  lh    $t9, 0x14($a2)
/* 0B00E8 800AF4E8 84CD0010 */  lh    $t5, 0x10($a2)
/* 0B00EC 800AF4EC 84CF0012 */  lh    $t7, 0x12($a2)
/* 0B00F0 800AF4F0 01626021 */  addu  $t4, $t3, $v0
/* 0B00F4 800AF4F4 24840040 */  addiu $a0, $a0, 0x40
/* 0B00F8 800AF4F8 01425821 */  addu  $t3, $t2, $v0
/* 0B00FC 800AF4FC 03224821 */  addu  $t1, $t9, $v0
/* 0B0100 800AF500 01A27021 */  addu  $t6, $t5, $v0
/* 0B0104 800AF504 01E2C021 */  addu  $t8, $t7, $v0
/* 0B0108 800AF508 A498FFF6 */  sh    $t8, -0xa($a0)
/* 0B010C 800AF50C A48EFFEE */  sh    $t6, -0x12($a0)
/* 0B0110 800AF510 A489FFFA */  sh    $t1, -6($a0)
/* 0B0114 800AF514 A48BFFFE */  sh    $t3, -2($a0)
/* 0B0118 800AF518 A48CFFEA */  sh    $t4, -0x16($a0)
/* 0B011C 800AF51C 1483FFDA */  bne   $a0, $v1, .L800AF488
/* 0B0120 800AF520 24C60018 */   addiu $a2, $a2, 0x18
/* 0B0124 800AF524 03E00008 */  jr    $ra
/* 0B0128 800AF528 00000000 */   nop   

