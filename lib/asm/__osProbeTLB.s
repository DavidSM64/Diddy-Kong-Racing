/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D35B0 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel __osProbeTLB
/* 0D41B0 800D35B0 40085000 */  mfc0  $t0, $10
/* 0D41B4 800D35B4 310900FF */  andi  $t1, $t0, 0xff
/* 0D41B8 800D35B8 2401E000 */  li    $at, -8192
/* 0D41BC 800D35BC 00815024 */  and   $t2, $a0, $at
/* 0D41C0 800D35C0 012A4825 */  or    $t1, $t1, $t2
/* 0D41C4 800D35C4 40895000 */  mtc0  $t1, $10
/* 0D41C8 800D35C8 00000000 */  nop   
/* 0D41CC 800D35CC 00000000 */  nop   
/* 0D41D0 800D35D0 00000000 */  nop   
/* 0D41D4 800D35D4 42000008 */  tlbp  
/* 0D41D8 800D35D8 00000000 */  nop   
/* 0D41DC 800D35DC 00000000 */  nop   
/* 0D41E0 800D35E0 400B0000 */  mfc0  $t3, $0
/* 0D41E4 800D35E4 3C018000 */  lui   $at, 0x8000
/* 0D41E8 800D35E8 01615824 */  and   $t3, $t3, $at
/* 0D41EC 800D35EC 1560001A */  bnez  $t3, .L800D3658
/* 0D41F0 800D35F0 00000000 */   nop   
/* 0D41F4 800D35F4 42000001 */  tlbr  
/* 0D41F8 800D35F8 00000000 */  nop   
/* 0D41FC 800D35FC 00000000 */  nop   
/* 0D4200 800D3600 00000000 */  nop   
/* 0D4204 800D3604 400B2800 */  mfc0  $t3, $5
/* 0D4208 800D3608 216B2000 */  addi  $t3, $t3, 0x2000
/* 0D420C 800D360C 000B5842 */  srl   $t3, $t3, 1
/* 0D4210 800D3610 01646024 */  and   $t4, $t3, $a0
/* 0D4214 800D3614 15800004 */  bnez  $t4, .L800D3628
/* 0D4218 800D3618 216BFFFF */   addi  $t3, $t3, -1
/* 0D421C 800D361C 40021000 */  mfc0  $v0, $2
/* 0D4220 800D3620 10000002 */  b     .L800D362C
/* 0D4224 800D3624 00000000 */   nop   
.L800D3628:
/* 0D4228 800D3628 40021800 */  mfc0  $v0, $3
.L800D362C:
/* 0D422C 800D362C 304D0002 */  andi  $t5, $v0, 2
/* 0D4230 800D3630 11A00009 */  beqz  $t5, .L800D3658
/* 0D4234 800D3634 00000000 */   nop   
/* 0D4238 800D3638 3C013FFF */  lui   $at, (0x3FFFFFC0 >> 16) # lui $at, 0x3fff
/* 0D423C 800D363C 3421FFC0 */  ori   $at, (0x3FFFFFC0 & 0xFFFF) # ori $at, $at, 0xffc0
/* 0D4240 800D3640 00411024 */  and   $v0, $v0, $at
/* 0D4244 800D3644 00021180 */  sll   $v0, $v0, 6
/* 0D4248 800D3648 008B6824 */  and   $t5, $a0, $t3
/* 0D424C 800D364C 004D1020 */  add   $v0, $v0, $t5
/* 0D4250 800D3650 10000002 */  b     .L800D365C
/* 0D4254 800D3654 00000000 */   nop   
.L800D3658:
/* 0D4258 800D3658 2402FFFF */  li    $v0, -1
.L800D365C:
/* 0D425C 800D365C 40885000 */  mtc0  $t0, $10
/* 0D4260 800D3660 03E00008 */  jr    $ra
/* 0D4264 800D3664 00000000 */   nop   

/* 0D4268 800D3668 00000000 */  nop   
/* 0D426C 800D366C 00000000 */  nop   
