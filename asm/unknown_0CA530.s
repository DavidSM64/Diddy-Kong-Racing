.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C9930
/* 0CA530 800C9930 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CA534 800C9934 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CA538 800C9938 8CA60008 */  lw    $a2, 8($a1)
/* 0CA53C 800C993C 00804025 */  move  $t0, $a0
/* 0CA540 800C9940 00A03825 */  move  $a3, $a1
/* 0CA544 800C9944 50C00023 */  beql  $a2, $zero, .L800C99D4
/* 0CA548 800C9948 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0CA54C 800C994C 8CCE00D8 */  lw    $t6, 0xd8($a2)
/* 0CA550 800C9950 51C0001A */  beql  $t6, $zero, .L800C99BC
/* 0CA554 800C9954 01002025 */   move  $a0, $t0
/* 0CA558 800C9958 AFA5001C */  sw    $a1, 0x1c($sp)
/* 0CA55C 800C995C 0C01959A */  jal   func_80065668
/* 0CA560 800C9960 AFA40018 */   sw    $a0, 0x18($sp)
/* 0CA564 800C9964 8FA7001C */  lw    $a3, 0x1c($sp)
/* 0CA568 800C9968 8FA80018 */  lw    $t0, 0x18($sp)
/* 0CA56C 800C996C 10400018 */  beqz  $v0, .L800C99D0
/* 0CA570 800C9970 00403025 */   move  $a2, $v0
/* 0CA574 800C9974 8CF80008 */  lw    $t8, 8($a3)
/* 0CA578 800C9978 8D0F001C */  lw    $t7, 0x1c($t0)
/* 0CA57C 800C997C 24050003 */  li    $a1, 3
/* 0CA580 800C9980 8F1900D8 */  lw    $t9, 0xd8($t8)
/* 0CA584 800C9984 A4400008 */  sh    $zero, 8($v0)
/* 0CA588 800C9988 01F94821 */  addu  $t1, $t7, $t9
/* 0CA58C 800C998C AC490004 */  sw    $t1, 4($v0)
/* 0CA590 800C9990 8CEA0008 */  lw    $t2, 8($a3)
/* 0CA594 800C9994 AC4A000C */  sw    $t2, 0xc($v0)
/* 0CA598 800C9998 8CEB0008 */  lw    $t3, 8($a3)
/* 0CA59C 800C999C 8D64000C */  lw    $a0, 0xc($t3)
/* 0CA5A0 800C99A0 AFA7001C */  sw    $a3, 0x1c($sp)
/* 0CA5A4 800C99A4 8C990008 */  lw    $t9, 8($a0)
/* 0CA5A8 800C99A8 0320F809 */  jalr  $t9
/* 0CA5AC 800C99AC 00000000 */  nop   
/* 0CA5B0 800C99B0 10000006 */  b     .L800C99CC
/* 0CA5B4 800C99B4 8FA7001C */   lw    $a3, 0x1c($sp)
/* 0CA5B8 800C99B8 01002025 */  move  $a0, $t0
.L800C99BC:
/* 0CA5BC 800C99BC 00C02825 */  move  $a1, $a2
/* 0CA5C0 800C99C0 0C0195C7 */  jal   func_8006571C
/* 0CA5C4 800C99C4 AFA7001C */   sw    $a3, 0x1c($sp)
/* 0CA5C8 800C99C8 8FA7001C */  lw    $a3, 0x1c($sp)
.L800C99CC:
/* 0CA5CC 800C99CC ACE00008 */  sw    $zero, 8($a3)
.L800C99D0:
/* 0CA5D0 800C99D0 8FBF0014 */  lw    $ra, 0x14($sp)
.L800C99D4:
/* 0CA5D4 800C99D4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CA5D8 800C99D8 03E00008 */  jr    $ra
/* 0CA5DC 800C99DC 00000000 */   nop   

glabel func_800C99E0
/* 0CA5E0 800C99E0 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 0CA5E4 800C99E4 44811000 */  mtc1  $at, $f2
/* 0CA5E8 800C99E8 04800004 */  bltz  $a0, .L800C99FC
/* 0CA5EC 800C99EC 3C01800F */   lui   $at, 0x800f
/* 0CA5F0 800C99F0 3C01800F */  lui   $at, %hi(D_800E94C4) # $at, 0x800f
/* 0CA5F4 800C99F4 10000003 */  b     .L800C9A04
/* 0CA5F8 800C99F8 C42094C0 */   lwc1  $f0, %lo(D_800E94C0)($at)
.L800C99FC:
/* 0CA5FC 800C99FC C42094C4 */  lwc1  $f0, %lo(D_800E94C4)($at)
/* 0CA600 800C9A00 00042023 */  negu  $a0, $a0
.L800C9A04:
/* 0CA604 800C9A04 10800008 */  beqz  $a0, .L800C9A28
.L800C9A08:
/* 0CA608 800C9A08 308E0001 */   andi  $t6, $a0, 1
/* 0CA60C 800C9A0C 11C00003 */  beqz  $t6, .L800C9A1C
/* 0CA610 800C9A10 00047843 */   sra   $t7, $a0, 1
/* 0CA614 800C9A14 46001082 */  mul.s $f2, $f2, $f0
/* 0CA618 800C9A18 00000000 */  nop   
.L800C9A1C:
/* 0CA61C 800C9A1C 46000002 */  mul.s $f0, $f0, $f0
/* 0CA620 800C9A20 15E0FFF9 */  bnez  $t7, .L800C9A08
/* 0CA624 800C9A24 01E02025 */   move  $a0, $t7
.L800C9A28:
/* 0CA628 800C9A28 03E00008 */  jr    $ra
/* 0CA62C 800C9A2C 46001006 */   mov.s $f0, $f2

glabel func_800C9A30
/* 0CA630 800C9A30 400C6000 */  mfc0  $t4, $12
/* 0CA634 800C9A34 3182FF01 */  andi  $v0, $t4, 0xff01
/* 0CA638 800C9A38 3C08800E */  lui   $t0, %hi(D_800E38AC) # $t0, 0x800e
/* 0CA63C 800C9A3C 250838AC */  addiu $t0, %lo(D_800E38AC) # addiu $t0, $t0, 0x38ac
/* 0CA640 800C9A40 8D0B0000 */  lw    $t3, ($t0)
/* 0CA644 800C9A44 2401FFFF */  li    $at, -1
/* 0CA648 800C9A48 01614026 */  xor   $t0, $t3, $at
/* 0CA64C 800C9A4C 3108FF00 */  andi  $t0, $t0, 0xff00
/* 0CA650 800C9A50 00481025 */  or    $v0, $v0, $t0
/* 0CA654 800C9A54 3C0AA430 */  lui   $t2, %hi(D_A430000C) # $t2, 0xa430
/* 0CA658 800C9A58 8D4A000C */  lw    $t2, %lo(D_A430000C)($t2)
/* 0CA65C 800C9A5C 11400005 */  beqz  $t2, .L800C9A74
/* 0CA660 800C9A60 000B4C02 */   srl   $t1, $t3, 0x10
/* 0CA664 800C9A64 2401FFFF */  li    $at, -1
/* 0CA668 800C9A68 01214826 */  xor   $t1, $t1, $at
/* 0CA66C 800C9A6C 3129003F */  andi  $t1, $t1, 0x3f
/* 0CA670 800C9A70 01495025 */  or    $t2, $t2, $t1
.L800C9A74:
/* 0CA674 800C9A74 000A5400 */  sll   $t2, $t2, 0x10
/* 0CA678 800C9A78 004A1025 */  or    $v0, $v0, $t2
/* 0CA67C 800C9A7C 3C01003F */  lui   $at, 0x3f
/* 0CA680 800C9A80 00814024 */  and   $t0, $a0, $at
/* 0CA684 800C9A84 010B4024 */  and   $t0, $t0, $t3
/* 0CA688 800C9A88 000843C2 */  srl   $t0, $t0, 0xf
/* 0CA68C 800C9A8C 3C0A800F */  lui   $t2, 0x800f
/* 0CA690 800C9A90 01485021 */  addu  $t2, $t2, $t0
/* 0CA694 800C9A94 954A94D0 */  lhu   $t2, -0x6b30($t2)
/* 0CA698 800C9A98 3C01A430 */  lui   $at, %hi(D_A430000C) # $at, 0xa430
/* 0CA69C 800C9A9C AC2A000C */  sw    $t2, %lo(D_A430000C)($at)
/* 0CA6A0 800C9AA0 3088FF01 */  andi  $t0, $a0, 0xff01
/* 0CA6A4 800C9AA4 3169FF00 */  andi  $t1, $t3, 0xff00
/* 0CA6A8 800C9AA8 01094024 */  and   $t0, $t0, $t1
/* 0CA6AC 800C9AAC 3C01FFFF */  lui   $at, (0xFFFF00FF >> 16) # lui $at, 0xffff
/* 0CA6B0 800C9AB0 342100FF */  ori   $at, (0xFFFF00FF & 0xFFFF) # ori $at, $at, 0xff
/* 0CA6B4 800C9AB4 01816024 */  and   $t4, $t4, $at
/* 0CA6B8 800C9AB8 01886025 */  or    $t4, $t4, $t0
/* 0CA6BC 800C9ABC 408C6000 */  mtc0  $t4, $12
/* 0CA6C0 800C9AC0 00000000 */  nop   
/* 0CA6C4 800C9AC4 00000000 */  nop   
/* 0CA6C8 800C9AC8 03E00008 */  jr    $ra
/* 0CA6CC 800C9ACC 00000000 */   nop   

glabel sqrtf
/* 0CA6D0 800C9AD0 03E00008 */  jr    $ra
/* 0CA6D4 800C9AD4 46006004 */   sqrt.s $f0, $f12

/* 0CA6D8 800C9AD8 00000000 */  nop   
/* 0CA6DC 800C9ADC 00000000 */  nop   
