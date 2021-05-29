glabel __osPfsRequestData
/* 0CE030 800CD430 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CE034 800CD434 308400FF */  andi  $a0, $a0, 0xff
/* 0CE038 800CD438 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CE03C 800CD43C A024CD90 */  sb    $a0, %lo(D_8012CD90)($at)
/* 0CE040 800CD440 AFA00000 */  sw    $zero, ($sp)
.L800CD444:
/* 0CE044 800CD444 8FAE0000 */  lw    $t6, ($sp)
/* 0CE048 800CD448 8FB80000 */  lw    $t8, ($sp)
/* 0CE04C 800CD44C 3C018013 */  lui   $at, %hi(__osPfsPifRam) #$at, 0x8013
/* 0CE050 800CD450 000E7880 */  sll   $t7, $t6, 2
/* 0CE054 800CD454 002F0821 */  addu  $at, $at, $t7
/* 0CE058 800CD458 AC20CDE0 */  sw    $zero, %lo(__osPfsPifRam)($at)
/* 0CE05C 800CD45C 27190001 */  addiu $t9, $t8, 1
/* 0CE060 800CD460 2B210010 */  slti  $at, $t9, 0x10
/* 0CE064 800CD464 1420FFF7 */  bnez  $at, .L800CD444
/* 0CE068 800CD468 AFB90000 */   sw    $t9, ($sp)
/* 0CE06C 800CD46C 3C198013 */  lui   $t9, %hi(__osMaxControllers) # $t9, 0x8013
/* 0CE070 800CD470 9339CD91 */  lbu   $t9, %lo(__osMaxControllers)($t9)
/* 0CE074 800CD474 3C098013 */  lui   $t1, %hi(__osPfsPifRam) # $t1, 0x8013
/* 0CE078 800CD478 24080001 */  li    $t0, 1
/* 0CE07C 800CD47C 3C018013 */  lui   $at, %hi(D_8012CE1C) # $at, 0x8013
/* 0CE080 800CD480 2529CDE0 */  addiu $t1, %lo(__osPfsPifRam) # addiu $t1, $t1, -0x3220
/* 0CE084 800CD484 240A00FF */  li    $t2, 255
/* 0CE088 800CD488 240B0001 */  li    $t3, 1
/* 0CE08C 800CD48C 240C0003 */  li    $t4, 3
/* 0CE090 800CD490 240D00FF */  li    $t5, 255
/* 0CE094 800CD494 240E00FF */  li    $t6, 255
/* 0CE098 800CD498 240F00FF */  li    $t7, 255
/* 0CE09C 800CD49C 241800FF */  li    $t8, 255
/* 0CE0A0 800CD4A0 AC28CE1C */  sw    $t0, %lo(D_8012CE1C)($at)
/* 0CE0A4 800CD4A4 AFA9000C */  sw    $t1, 0xc($sp)
/* 0CE0A8 800CD4A8 A3AA0004 */  sb    $t2, 4($sp)
/* 0CE0AC 800CD4AC A3AB0005 */  sb    $t3, 5($sp)
/* 0CE0B0 800CD4B0 A3AC0006 */  sb    $t4, 6($sp)
/* 0CE0B4 800CD4B4 A3A40007 */  sb    $a0, 7($sp)
/* 0CE0B8 800CD4B8 A3AD0008 */  sb    $t5, 8($sp)
/* 0CE0BC 800CD4BC A3AE0009 */  sb    $t6, 9($sp)
/* 0CE0C0 800CD4C0 A3AF000A */  sb    $t7, 0xa($sp)
/* 0CE0C4 800CD4C4 A3B8000B */  sb    $t8, 0xb($sp)
/* 0CE0C8 800CD4C8 1B200013 */  blez  $t9, .L800CD518
/* 0CE0CC 800CD4CC AFA00000 */   sw    $zero, ($sp)
.L800CD4D0:
/* 0CE0D0 800CD4D0 27A90004 */  addiu $t1, $sp, 4
/* 0CE0D4 800CD4D4 8D210000 */  lw    $at, ($t1)
/* 0CE0D8 800CD4D8 8FA8000C */  lw    $t0, 0xc($sp)
/* 0CE0DC 800CD4DC 3C188013 */  lui   $t8, %hi(__osMaxControllers) # $t8, 0x8013
/* 0CE0E0 800CD4E0 A9010000 */  swl   $at, ($t0)
/* 0CE0E4 800CD4E4 B9010003 */  swr   $at, 3($t0)
/* 0CE0E8 800CD4E8 8D2B0004 */  lw    $t3, 4($t1)
/* 0CE0EC 800CD4EC A90B0004 */  swl   $t3, 4($t0)
/* 0CE0F0 800CD4F0 B90B0007 */  swr   $t3, 7($t0)
/* 0CE0F4 800CD4F4 8FAE0000 */  lw    $t6, ($sp)
/* 0CE0F8 800CD4F8 9318CD91 */  lbu   $t8, %lo(__osMaxControllers)($t8)
/* 0CE0FC 800CD4FC 8FAC000C */  lw    $t4, 0xc($sp)
/* 0CE100 800CD500 25CF0001 */  addiu $t7, $t6, 1
/* 0CE104 800CD504 01F8082A */  slt   $at, $t7, $t8
/* 0CE108 800CD508 258D0008 */  addiu $t5, $t4, 8
/* 0CE10C 800CD50C AFAF0000 */  sw    $t7, ($sp)
/* 0CE110 800CD510 1420FFEF */  bnez  $at, .L800CD4D0
/* 0CE114 800CD514 AFAD000C */   sw    $t5, 0xc($sp)
.L800CD518:
/* 0CE118 800CD518 8FAA000C */  lw    $t2, 0xc($sp)
/* 0CE11C 800CD51C 241900FE */  li    $t9, 254
/* 0CE120 800CD520 27BD0010 */  addiu $sp, $sp, 0x10
/* 0CE124 800CD524 03E00008 */  jr    $ra
/* 0CE128 800CD528 A1590000 */   sb    $t9, ($t2)

