glabel func_800AB1F0
/* 0ABDF0 800AB1F0 3C03800E */  lui   $v1, %hi(D_800E28D8) # $v1, 0x800e
/* 0ABDF4 800AB1F4 246328D8 */  addiu $v1, %lo(D_800E28D8) # addiu $v1, $v1, 0x28d8
/* 0ABDF8 800AB1F8 AC600000 */  sw    $zero, ($v1)
/* 0ABDFC 800AB1FC AC600004 */  sw    $zero, 4($v1)
/* 0ABE00 800AB200 3C01800E */  lui   $at, %hi(D_800E28D4) # $at, 0x800e
/* 0ABE04 800AB204 AC2028D4 */  sw    $zero, %lo(D_800E28D4)($at)
/* 0ABE08 800AB208 3C028012 */  lui   $v0, %hi(D_80127C00) # $v0, 0x8012
/* 0ABE0C 800AB20C 3C018012 */  lui   $at, %hi(D_80127BB0) # $at, 0x8012
/* 0ABE10 800AB210 240E0006 */  li    $t6, 6
/* 0ABE14 800AB214 24427C00 */  addiu $v0, %lo(D_80127C00) # addiu $v0, $v0, 0x7c00
/* 0ABE18 800AB218 AC207BB0 */  sw    $zero, %lo(D_80127BB0)($at)
/* 0ABE1C 800AB21C 000EC080 */  sll   $t8, $t6, 2
/* 0ABE20 800AB220 AC4E0000 */  sw    $t6, ($v0)
/* 0ABE24 800AB224 AC580000 */  sw    $t8, ($v0)
/* 0ABE28 800AB228 00184043 */  sra   $t0, $t8, 1
/* 0ABE2C 800AB22C 3C018012 */  lui   $at, %hi(D_80127C04) # $at, 0x8012
/* 0ABE30 800AB230 3C04800E */  lui   $a0, %hi(D_800E2914) # $a0, 0x800e
/* 0ABE34 800AB234 AC287C04 */  sw    $t0, %lo(D_80127C04)($at)
/* 0ABE38 800AB238 24842914 */  addiu $a0, %lo(D_800E2914) # addiu $a0, $a0, 0x2914
/* 0ABE3C 800AB23C AC800000 */  sw    $zero, ($a0)
/* 0ABE40 800AB240 AC800004 */  sw    $zero, 4($a0)
/* 0ABE44 800AB244 3C01800E */  lui   $at, %hi(D_800E290C) # $at, 0x800e
/* 0ABE48 800AB248 3C058012 */  lui   $a1, %hi(D_80127BF8) # $a1, 0x8012
/* 0ABE4C 800AB24C AC20290C */  sw    $zero, %lo(D_800E290C)($at)
/* 0ABE50 800AB250 24A57BF8 */  addiu $a1, %lo(D_80127BF8) # addiu $a1, $a1, 0x7bf8
/* 0ABE54 800AB254 2406FFFF */  li    $a2, -1
/* 0ABE58 800AB258 2409FE00 */  li    $t1, -512
/* 0ABE5C 800AB25C A4A60000 */  sh    $a2, ($a1)
/* 0ABE60 800AB260 A4A90002 */  sh    $t1, 2($a1)
/* 0ABE64 800AB264 3C01800E */  lui   $at, %hi(D_800E2A80) # $at, 0x800e
/* 0ABE68 800AB268 AC202A80 */  sw    $zero, %lo(D_800E2A80)($at)
/* 0ABE6C 800AB26C 3C01800E */  lui   $at, %hi(D_800E2A84) # $at, 0x800e
/* 0ABE70 800AB270 240A0001 */  li    $t2, 1
/* 0ABE74 800AB274 AC2A2A84 */  sw    $t2, %lo(D_800E2A84)($at)
/* 0ABE78 800AB278 3C07800E */  lui   $a3, %hi(D_800E291C) # $a3, 0x800e
/* 0ABE7C 800AB27C 3C01800E */  lui   $at, %hi(D_800E2A88) # $at, 0x800e
/* 0ABE80 800AB280 24E7291C */  addiu $a3, %lo(D_800E291C) # addiu $a3, $a3, 0x291c
/* 0ABE84 800AB284 AC202A88 */  sw    $zero, %lo(D_800E2A88)($at)
/* 0ABE88 800AB288 8CEB0000 */  lw    $t3, ($a3)
/* 0ABE8C 800AB28C 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0ABE90 800AB290 15600018 */  bnez  $t3, .L800AB2F4
/* 0ABE94 800AB294 AFBF0014 */   sw    $ra, 0x14($sp)
/* 0ABE98 800AB298 0C01DB16 */  jal   func_80076C58
/* 0ABE9C 800AB29C 24040013 */   li    $a0, 19
/* 0ABEA0 800AB2A0 3C04800E */  lui   $a0, %hi(D_800E2920) # $a0, 0x800e
/* 0ABEA4 800AB2A4 3C07800E */  lui   $a3, %hi(D_800E291C) # $a3, 0x800e
/* 0ABEA8 800AB2A8 24E7291C */  addiu $a3, %lo(D_800E291C) # addiu $a3, $a3, 0x291c
/* 0ABEAC 800AB2AC 24842920 */  addiu $a0, %lo(D_800E2920) # addiu $a0, $a0, 0x2920
/* 0ABEB0 800AB2B0 00006080 */  sll   $t4, $zero, 2
/* 0ABEB4 800AB2B4 ACE20000 */  sw    $v0, ($a3)
/* 0ABEB8 800AB2B8 AC800000 */  sw    $zero, ($a0)
/* 0ABEBC 800AB2BC 004C6821 */  addu  $t5, $v0, $t4
/* 0ABEC0 800AB2C0 8DAE0000 */  lw    $t6, ($t5)
/* 0ABEC4 800AB2C4 2406FFFF */  li    $a2, -1
/* 0ABEC8 800AB2C8 00402825 */  move  $a1, $v0
/* 0ABECC 800AB2CC 10CE0009 */  beq   $a2, $t6, .L800AB2F4
/* 0ABED0 800AB2D0 00001825 */   move  $v1, $zero
/* 0ABED4 800AB2D4 246F0001 */  addiu $t7, $v1, 1
.L800AB2D8:
/* 0ABED8 800AB2D8 000FC080 */  sll   $t8, $t7, 2
/* 0ABEDC 800AB2DC 00B8C821 */  addu  $t9, $a1, $t8
/* 0ABEE0 800AB2E0 AC8F0000 */  sw    $t7, ($a0)
/* 0ABEE4 800AB2E4 8F280000 */  lw    $t0, ($t9)
/* 0ABEE8 800AB2E8 01E01825 */  move  $v1, $t7
/* 0ABEEC 800AB2EC 14C8FFFA */  bne   $a2, $t0, .L800AB2D8
/* 0ABEF0 800AB2F0 246F0001 */   addiu $t7, $v1, 1
.L800AB2F4:
/* 0ABEF4 800AB2F4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0ABEF8 800AB2F8 3C018012 */  lui   $at, %hi(D_80127C08) # $at, 0x8012
/* 0ABEFC 800AB2FC AC207C08 */  sw    $zero, %lo(D_80127C08)($at)
/* 0ABF00 800AB300 03E00008 */  jr    $ra
/* 0ABF04 800AB304 27BD0018 */   addiu $sp, $sp, 0x18

