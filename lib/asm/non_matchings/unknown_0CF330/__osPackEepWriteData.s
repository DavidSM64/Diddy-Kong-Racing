glabel __osPackEepWriteData
/* 0CF330 800CE730 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CF334 800CE734 3C0E8013 */  lui   $t6, %hi(D_8012CE40) # $t6, 0x8013
/* 0CF338 800CE738 25CECE40 */  addiu $t6, %lo(D_8012CE40) # addiu $t6, $t6, -0x31c0
/* 0CF33C 800CE73C 308400FF */  andi  $a0, $a0, 0xff
/* 0CF340 800CE740 AFAE0014 */  sw    $t6, 0x14($sp)
/* 0CF344 800CE744 AFA00004 */  sw    $zero, 4($sp)
.L800CE748:
/* 0CF348 800CE748 8FB80004 */  lw    $t8, 4($sp)
/* 0CF34C 800CE74C 8FA80004 */  lw    $t0, 4($sp)
/* 0CF350 800CE750 3C018013 */  lui   $at, 0x8013
/* 0CF354 800CE754 0018C880 */  sll   $t9, $t8, 2
/* 0CF358 800CE758 00390821 */  addu  $at, $at, $t9
/* 0CF35C 800CE75C 240F00FF */  li    $t7, 255
/* 0CF360 800CE760 AC2FCE40 */  sw    $t7, -0x31c0($at)
/* 0CF364 800CE764 25090001 */  addiu $t1, $t0, 1
/* 0CF368 800CE768 29210010 */  slti  $at, $t1, 0x10
/* 0CF36C 800CE76C 1420FFF6 */  bnez  $at, .L800CE748
/* 0CF370 800CE770 AFA90004 */   sw    $t1, 4($sp)
/* 0CF374 800CE774 240A0001 */  li    $t2, 1
/* 0CF378 800CE778 3C018013 */  lui   $at, %hi(D_8012CE7C) # $at, 0x8013
/* 0CF37C 800CE77C 240B000A */  li    $t3, 10
/* 0CF380 800CE780 240C0001 */  li    $t4, 1
/* 0CF384 800CE784 240D0005 */  li    $t5, 5
/* 0CF388 800CE788 AC2ACE7C */  sw    $t2, %lo(D_8012CE7C)($at)
/* 0CF38C 800CE78C A3AB0008 */  sb    $t3, 8($sp)
/* 0CF390 800CE790 A3AC0009 */  sb    $t4, 9($sp)
/* 0CF394 800CE794 A3AD000A */  sb    $t5, 0xa($sp)
/* 0CF398 800CE798 A3A4000B */  sb    $a0, 0xb($sp)
/* 0CF39C 800CE79C AFA00004 */  sw    $zero, 4($sp)
.L800CE7A0:
/* 0CF3A0 800CE7A0 8FB80004 */  lw    $t8, 4($sp)
/* 0CF3A4 800CE7A4 90AE0000 */  lbu   $t6, ($a1)
/* 0CF3A8 800CE7A8 24A50001 */  addiu $a1, $a1, 1
/* 0CF3AC 800CE7AC 03B87821 */  addu  $t7, $sp, $t8
/* 0CF3B0 800CE7B0 A1EE000C */  sb    $t6, 0xc($t7)
/* 0CF3B4 800CE7B4 8FB90004 */  lw    $t9, 4($sp)
/* 0CF3B8 800CE7B8 27280001 */  addiu $t0, $t9, 1
/* 0CF3BC 800CE7BC 29010008 */  slti  $at, $t0, 8
/* 0CF3C0 800CE7C0 1420FFF7 */  bnez  $at, .L800CE7A0
/* 0CF3C4 800CE7C4 AFA80004 */   sw    $t0, 4($sp)
/* 0CF3C8 800CE7C8 AFA00004 */  sw    $zero, 4($sp)
.L800CE7CC:
/* 0CF3CC 800CE7CC 8FA90014 */  lw    $t1, 0x14($sp)
/* 0CF3D0 800CE7D0 A1200000 */  sb    $zero, ($t1)
/* 0CF3D4 800CE7D4 8FAC0004 */  lw    $t4, 4($sp)
/* 0CF3D8 800CE7D8 8FAA0014 */  lw    $t2, 0x14($sp)
/* 0CF3DC 800CE7DC 258D0001 */  addiu $t5, $t4, 1
/* 0CF3E0 800CE7E0 29A10004 */  slti  $at, $t5, 4
/* 0CF3E4 800CE7E4 254B0001 */  addiu $t3, $t2, 1
/* 0CF3E8 800CE7E8 AFAD0004 */  sw    $t5, 4($sp)
/* 0CF3EC 800CE7EC 1420FFF7 */  bnez  $at, .L800CE7CC
/* 0CF3F0 800CE7F0 AFAB0014 */   sw    $t3, 0x14($sp)
/* 0CF3F4 800CE7F4 27B80008 */  addiu $t8, $sp, 8
/* 0CF3F8 800CE7F8 8F010000 */  lw    $at, ($t8)
/* 0CF3FC 800CE7FC 8FAE0014 */  lw    $t6, 0x14($sp)
/* 0CF400 800CE800 240A00FE */  li    $t2, 254
/* 0CF404 800CE804 A9C10000 */  swl   $at, ($t6)
/* 0CF408 800CE808 B9C10003 */  swr   $at, 3($t6)
/* 0CF40C 800CE80C 8F190004 */  lw    $t9, 4($t8)
/* 0CF410 800CE810 A9D90004 */  swl   $t9, 4($t6)
/* 0CF414 800CE814 B9D90007 */  swr   $t9, 7($t6)
/* 0CF418 800CE818 8F010008 */  lw    $at, 8($t8)
/* 0CF41C 800CE81C A9C10008 */  swl   $at, 8($t6)
/* 0CF420 800CE820 B9C1000B */  swr   $at, 0xb($t6)
/* 0CF424 800CE824 8FA80014 */  lw    $t0, 0x14($sp)
/* 0CF428 800CE828 2509000C */  addiu $t1, $t0, 0xc
/* 0CF42C 800CE82C AFA90014 */  sw    $t1, 0x14($sp)
/* 0CF430 800CE830 A12A0000 */  sb    $t2, ($t1)
/* 0CF434 800CE834 03E00008 */  jr    $ra
/* 0CF438 800CE838 27BD0018 */   addiu $sp, $sp, 0x18

