glabel func_8009B1E4
/* 09BDE4 8009B1E4 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 09BDE8 8009B1E8 8FAE0028 */  lw    $t6, 0x28($sp)
/* 09BDEC 8009B1EC AFBF0014 */  sw    $ra, 0x14($sp)
/* 09BDF0 8009B1F0 29C10100 */  slti  $at, $t6, 0x100
/* 09BDF4 8009B1F4 AFA40018 */  sw    $a0, 0x18($sp)
/* 09BDF8 8009B1F8 AFA5001C */  sw    $a1, 0x1c($sp)
/* 09BDFC 8009B1FC AFA60020 */  sw    $a2, 0x20($sp)
/* 09BE00 8009B200 14200003 */  bnez  $at, .L8009B210
/* 09BE04 8009B204 AFA70024 */   sw    $a3, 0x24($sp)
/* 09BE08 8009B208 240A00FF */  li    $t2, 255
/* 09BE0C 8009B20C AFAA0028 */  sw    $t2, 0x28($sp)
.L8009B210:
/* 09BE10 8009B210 8FAA0028 */  lw    $t2, 0x28($sp)
/* 09BE14 8009B214 3C048012 */  lui   $a0, %hi(D_801263A0) # $a0, 0x8012
/* 09BE18 8009B218 05410002 */  bgez  $t2, .L8009B224
/* 09BE1C 8009B21C 248463A0 */   addiu $a0, %lo(D_801263A0) # addiu $a0, $a0, 0x63a0
/* 09BE20 8009B220 00005025 */  move  $t2, $zero
.L8009B224:
/* 09BE24 8009B224 8C820000 */  lw    $v0, ($a0)
/* 09BE28 8009B228 3C19800E */  lui   $t9, %hi(D_800E1780) # $t9, 0x800e
/* 09BE2C 8009B22C 244F0008 */  addiu $t7, $v0, 8
/* 09BE30 8009B230 AC8F0000 */  sw    $t7, ($a0)
/* 09BE34 8009B234 27391780 */  addiu $t9, %lo(D_800E1780) # addiu $t9, $t9, 0x1780
/* 09BE38 8009B238 3C180600 */  lui   $t8, 0x600
/* 09BE3C 8009B23C AC580000 */  sw    $t8, ($v0)
/* 09BE40 8009B240 AC590004 */  sw    $t9, 4($v0)
/* 09BE44 8009B244 8C820000 */  lw    $v0, ($a0)
/* 09BE48 8009B248 3C0BFA00 */  lui   $t3, 0xfa00
/* 09BE4C 8009B24C 244C0008 */  addiu $t4, $v0, 8
/* 09BE50 8009B250 AC8C0000 */  sw    $t4, ($a0)
/* 09BE54 8009B254 314D00FF */  andi  $t5, $t2, 0xff
/* 09BE58 8009B258 AC4D0004 */  sw    $t5, 4($v0)
/* 09BE5C 8009B25C AC4B0000 */  sw    $t3, ($v0)
/* 09BE60 8009B260 8C820000 */  lw    $v0, ($a0)
/* 09BE64 8009B264 3C18FFFD */  lui   $t8, (0xFFFDF6FB >> 16) # lui $t8, 0xfffd
/* 09BE68 8009B268 244E0008 */  addiu $t6, $v0, 8
/* 09BE6C 8009B26C AC8E0000 */  sw    $t6, ($a0)
/* 09BE70 8009B270 3C0FFCFF */  lui   $t7, (0xFCFFFFFF >> 16) # lui $t7, 0xfcff
/* 09BE74 8009B274 35EFFFFF */  ori   $t7, (0xFCFFFFFF & 0xFFFF) # ori $t7, $t7, 0xffff
/* 09BE78 8009B278 3718F6FB */  ori   $t8, (0xFFFDF6FB & 0xFFFF) # ori $t8, $t8, 0xf6fb
/* 09BE7C 8009B27C AC580004 */  sw    $t8, 4($v0)
/* 09BE80 8009B280 AC4F0000 */  sw    $t7, ($v0)
/* 09BE84 8009B284 8FAC0018 */  lw    $t4, 0x18($sp)
/* 09BE88 8009B288 8FAD0020 */  lw    $t5, 0x20($sp)
/* 09BE8C 8009B28C 8C820000 */  lw    $v0, ($a0)
/* 09BE90 8009B290 018D7021 */  addu  $t6, $t4, $t5
/* 09BE94 8009B294 8FAD0024 */  lw    $t5, 0x24($sp)
/* 09BE98 8009B298 8FAC001C */  lw    $t4, 0x1c($sp)
/* 09BE9C 8009B29C 31CF03FF */  andi  $t7, $t6, 0x3ff
/* 09BEA0 8009B2A0 000FC380 */  sll   $t8, $t7, 0xe
/* 09BEA4 8009B2A4 24590008 */  addiu $t9, $v0, 8
/* 09BEA8 8009B2A8 AC990000 */  sw    $t9, ($a0)
/* 09BEAC 8009B2AC 3C01F600 */  lui   $at, 0xf600
/* 09BEB0 8009B2B0 018D7021 */  addu  $t6, $t4, $t5
/* 09BEB4 8009B2B4 31CF03FF */  andi  $t7, $t6, 0x3ff
/* 09BEB8 8009B2B8 0301C825 */  or    $t9, $t8, $at
/* 09BEBC 8009B2BC 000FC080 */  sll   $t8, $t7, 2
/* 09BEC0 8009B2C0 03386025 */  or    $t4, $t9, $t8
/* 09BEC4 8009B2C4 AC4C0000 */  sw    $t4, ($v0)
/* 09BEC8 8009B2C8 8FB9001C */  lw    $t9, 0x1c($sp)
/* 09BECC 8009B2CC 8FAD0018 */  lw    $t5, 0x18($sp)
/* 09BED0 8009B2D0 333803FF */  andi  $t8, $t9, 0x3ff
/* 09BED4 8009B2D4 31AE03FF */  andi  $t6, $t5, 0x3ff
/* 09BED8 8009B2D8 000E7B80 */  sll   $t7, $t6, 0xe
/* 09BEDC 8009B2DC 00186080 */  sll   $t4, $t8, 2
/* 09BEE0 8009B2E0 01EC6825 */  or    $t5, $t7, $t4
/* 09BEE4 8009B2E4 AC4D0004 */  sw    $t5, 4($v0)
/* 09BEE8 8009B2E8 8C820000 */  lw    $v0, ($a0)
/* 09BEEC 8009B2EC 3C19E700 */  lui   $t9, 0xe700
/* 09BEF0 8009B2F0 244E0008 */  addiu $t6, $v0, 8
/* 09BEF4 8009B2F4 AC8E0000 */  sw    $t6, ($a0)
/* 09BEF8 8009B2F8 AC400004 */  sw    $zero, 4($v0)
/* 09BEFC 8009B2FC AC590000 */  sw    $t9, ($v0)
/* 09BF00 8009B300 8C820000 */  lw    $v0, ($a0)
/* 09BF04 8009B304 240FFFFF */  li    $t7, -1
/* 09BF08 8009B308 24580008 */  addiu $t8, $v0, 8
/* 09BF0C 8009B30C AC980000 */  sw    $t8, ($a0)
/* 09BF10 8009B310 AC4F0004 */  sw    $t7, 4($v0)
/* 09BF14 8009B314 0C01ECF4 */  jal   func_8007B3D0
/* 09BF18 8009B318 AC4B0000 */   sw    $t3, ($v0)
/* 09BF1C 8009B31C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 09BF20 8009B320 27BD0018 */  addiu $sp, $sp, 0x18
/* 09BF24 8009B324 03E00008 */  jr    $ra
/* 09BF28 8009B328 00000000 */   nop   

