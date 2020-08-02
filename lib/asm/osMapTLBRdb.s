/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4730 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel osMapTLBRdb
/* 0D5330 800D4730 40085000 */  mfc0  $t0, $10
/* 0D5334 800D4734 2409001F */  li    $t1, 31
/* 0D5338 800D4738 40890000 */  mtc0  $t1, $0
/* 0D533C 800D473C 40802800 */  mtc0  $zero, $5
/* 0D5340 800D4740 240A0017 */  li    $t2, 23
/* 0D5344 800D4744 3C09C000 */  lui   $t1, 0xc000
/* 0D5348 800D4748 40895000 */  mtc0  $t1, $10
/* 0D534C 800D474C 3C098000 */  lui   $t1, 0x8000
/* 0D5350 800D4750 00095982 */  srl   $t3, $t1, 6
/* 0D5354 800D4754 016A5825 */  or    $t3, $t3, $t2
/* 0D5358 800D4758 408B1000 */  mtc0  $t3, $2
/* 0D535C 800D475C 24090001 */  li    $t1, 1
/* 0D5360 800D4760 40891800 */  mtc0  $t1, $3
/* 0D5364 800D4764 00000000 */  nop   
/* 0D5368 800D4768 42000002 */  tlbwi 
/* 0D536C 800D476C 00000000 */  nop   
/* 0D5370 800D4770 00000000 */  nop   
/* 0D5374 800D4774 00000000 */  nop   
/* 0D5378 800D4778 00000000 */  nop   
/* 0D537C 800D477C 40885000 */  mtc0  $t0, $10
/* 0D5380 800D4780 03E00008 */  jr    $ra
/* 0D5384 800D4784 00000000 */   nop   

/* 0D5388 800D4788 00000000 */  nop   
/* 0D538C 800D478C 00000000 */  nop   
