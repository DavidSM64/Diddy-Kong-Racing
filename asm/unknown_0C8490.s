.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C7890
/* 0C8490 800C7890 8C830018 */  lw    $v1, 0x18($a0)
/* 0C8494 800C7894 54600004 */  bnezl $v1, .L800C78A8
/* 0C8498 800C7898 8C8E0024 */   lw    $t6, 0x24($a0)
/* 0C849C 800C789C 03E00008 */  jr    $ra
/* 0C84A0 800C78A0 00001025 */   move  $v0, $zero

/* 0C84A4 800C78A4 8C8E0024 */  lw    $t6, 0x24($a0)
.L800C78A8:
/* 0C84A8 800C78A8 C4680008 */  lwc1  $f8, 8($v1)
/* 0C84AC 800C78AC 448E2000 */  mtc1  $t6, $f4
/* 0C84B0 800C78B0 00000000 */  nop   
/* 0C84B4 800C78B4 468021A0 */  cvt.s.w $f6, $f4
/* 0C84B8 800C78B8 46083283 */  div.s $f10, $f6, $f8
/* 0C84BC 800C78BC 4600540D */  trunc.w.s $f16, $f10
/* 0C84C0 800C78C0 44028000 */  mfc1  $v0, $f16
/* 0C84C4 800C78C4 00000000 */  nop   
/* 0C84C8 800C78C8 03E00008 */  jr    $ra
/* 0C84CC 800C78CC 00000000 */   nop   

glabel func_800C78D0
/* 0C84D0 800C78D0 40024800 */  mfc0  $v0, $9
/* 0C84D4 800C78D4 03E00008 */  jr    $ra
/* 0C84D8 800C78D8 00000000 */   nop   

/* 0C84DC 800C78DC 00000000 */  nop   
