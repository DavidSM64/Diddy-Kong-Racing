.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C9780
/* 0CA380 800C9780 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CA384 800C9784 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CA388 800C9788 AFA40018 */  sw    $a0, 0x18($sp)
/* 0CA38C 800C978C AFA60020 */  sw    $a2, 0x20($sp)
/* 0CA390 800C9790 8CAE0008 */  lw    $t6, 8($a1)
/* 0CA394 800C9794 51C00018 */  beql  $t6, $zero, .L800C97F8
/* 0CA398 800C9798 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0CA39C 800C979C 0C01959A */  jal   func_80065668
/* 0CA3A0 800C97A0 AFA5001C */   sw    $a1, 0x1c($sp)
/* 0CA3A4 800C97A4 8FA7001C */  lw    $a3, 0x1c($sp)
/* 0CA3A8 800C97A8 10400012 */  beqz  $v0, .L800C97F4
/* 0CA3AC 800C97AC 00403025 */   move  $a2, $v0
/* 0CA3B0 800C97B0 8FAF0018 */  lw    $t7, 0x18($sp)
/* 0CA3B4 800C97B4 8CF90008 */  lw    $t9, 8($a3)
/* 0CA3B8 800C97B8 240A0007 */  li    $t2, 7
/* 0CA3BC 800C97BC 8DF8001C */  lw    $t8, 0x1c($t7)
/* 0CA3C0 800C97C0 8F2800D8 */  lw    $t0, 0xd8($t9)
/* 0CA3C4 800C97C4 A44A0008 */  sh    $t2, 8($v0)
/* 0CA3C8 800C97C8 24050003 */  li    $a1, 3
/* 0CA3CC 800C97CC 03084821 */  addu  $t1, $t8, $t0
/* 0CA3D0 800C97D0 AC490004 */  sw    $t1, 4($v0)
/* 0CA3D4 800C97D4 C7A40020 */  lwc1  $f4, 0x20($sp)
/* 0CA3D8 800C97D8 AC400000 */  sw    $zero, ($v0)
/* 0CA3DC 800C97DC E444000C */  swc1  $f4, 0xc($v0)
/* 0CA3E0 800C97E0 8CEB0008 */  lw    $t3, 8($a3)
/* 0CA3E4 800C97E4 8D64000C */  lw    $a0, 0xc($t3)
/* 0CA3E8 800C97E8 8C990008 */  lw    $t9, 8($a0)
/* 0CA3EC 800C97EC 0320F809 */  jalr  $t9
/* 0CA3F0 800C97F0 00000000 */  nop   
.L800C97F4:
/* 0CA3F4 800C97F4 8FBF0014 */  lw    $ra, 0x14($sp)
.L800C97F8:
/* 0CA3F8 800C97F8 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CA3FC 800C97FC 03E00008 */  jr    $ra
/* 0CA400 800C9800 00000000 */   nop   

/* 0CA404 800C9804 00000000 */  nop   
/* 0CA408 800C9808 00000000 */  nop   
/* 0CA40C 800C980C 00000000 */  nop   
