glabel gzip_inflate_fixed /* Official name: inflate_fixed */
/* 0C79DC 800C6DDC 27BDFAD0 */  addiu $sp, $sp, -0x530
/* 0C79E0 800C6DE0 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0C79E4 800C6DE4 23AB0044 */  addi  $t3, $sp, 0x44
/* 0C79E8 800C6DE8 24080024 */  li    $t0, 36
/* 0C79EC 800C6DEC 24090008 */  li    $t1, 8
.L800C6DF0:
/* 0C79F0 800C6DF0 2508FFFF */  addiu $t0, $t0, -1
/* 0C79F4 800C6DF4 AD690000 */  sw    $t1, ($t3)
/* 0C79F8 800C6DF8 AD690004 */  sw    $t1, 4($t3)
/* 0C79FC 800C6DFC AD690008 */  sw    $t1, 8($t3)
/* 0C7A00 800C6E00 AD69000C */  sw    $t1, 0xc($t3)
/* 0C7A04 800C6E04 1500FFFA */  bnez  $t0, .L800C6DF0
/* 0C7A08 800C6E08 256B0010 */   addiu $t3, $t3, 0x10
/* 0C7A0C 800C6E0C 2408001C */  li    $t0, 28
/* 0C7A10 800C6E10 24090009 */  li    $t1, 9
.L800C6E14:
/* 0C7A14 800C6E14 2508FFFF */  addiu $t0, $t0, -1
/* 0C7A18 800C6E18 AD690000 */  sw    $t1, ($t3)
/* 0C7A1C 800C6E1C AD690004 */  sw    $t1, 4($t3)
/* 0C7A20 800C6E20 AD690008 */  sw    $t1, 8($t3)
/* 0C7A24 800C6E24 AD69000C */  sw    $t1, 0xc($t3)
/* 0C7A28 800C6E28 1500FFFA */  bnez  $t0, .L800C6E14
/* 0C7A2C 800C6E2C 256B0010 */   addiu $t3, $t3, 0x10
/* 0C7A30 800C6E30 24080006 */  li    $t0, 6
/* 0C7A34 800C6E34 24090007 */  li    $t1, 7
.L800C6E38:
/* 0C7A38 800C6E38 2508FFFF */  addiu $t0, $t0, -1
/* 0C7A3C 800C6E3C AD690000 */  sw    $t1, ($t3)
/* 0C7A40 800C6E40 AD690004 */  sw    $t1, 4($t3)
/* 0C7A44 800C6E44 AD690008 */  sw    $t1, 8($t3)
/* 0C7A48 800C6E48 AD69000C */  sw    $t1, 0xc($t3)
/* 0C7A4C 800C6E4C 1500FFFA */  bnez  $t0, .L800C6E38
/* 0C7A50 800C6E50 256B0010 */   addiu $t3, $t3, 0x10
/* 0C7A54 800C6E54 24090008 */  li    $t1, 8
/* 0C7A58 800C6E58 AD690000 */  sw    $t1, ($t3)
/* 0C7A5C 800C6E5C AD690004 */  sw    $t1, 4($t3)
/* 0C7A60 800C6E60 AD690008 */  sw    $t1, 8($t3)
/* 0C7A64 800C6E64 AD69000C */  sw    $t1, 0xc($t3)
/* 0C7A68 800C6E68 AD690010 */  sw    $t1, 0x10($t3)
/* 0C7A6C 800C6E6C AD690014 */  sw    $t1, 0x14($t3)
/* 0C7A70 800C6E70 AD690018 */  sw    $t1, 0x18($t3)
/* 0C7A74 800C6E74 AD69001C */  sw    $t1, 0x1c($t3)
/* 0C7A78 800C6E78 24080007 */  li    $t0, 7
/* 0C7A7C 800C6E7C AFA80038 */  sw    $t0, 0x38($sp)
/* 0C7A80 800C6E80 3C02800F */  lui   $v0, %hi(gzip_cplext) # $v0, 0x800f
/* 0C7A84 800C6E84 3C07800F */  lui   $a3, %hi(gzip_cplens) # $a3, 0x800f
/* 0C7A88 800C6E88 24429412 */  addiu $v0, %lo(gzip_cplext) # addiu $v0, $v0, -0x6bee
/* 0C7A8C 800C6E8C 23A30020 */  addi  $v1, $sp, 0x20
/* 0C7A90 800C6E90 23A80024 */  addi  $t0, $sp, 0x24
/* 0C7A94 800C6E94 23A40044 */  addi  $a0, $sp, 0x44
/* 0C7A98 800C6E98 24050120 */  li    $a1, 288
/* 0C7A9C 800C6E9C 24060101 */  li    $a2, 257
/* 0C7AA0 800C6EA0 24E793D4 */  addiu $a3, %lo(gzip_cplens) # addiu $a3, $a3, -0x6c2c
/* 0C7AA4 800C6EA4 AFA20010 */  sw    $v0, 0x10($sp)
/* 0C7AA8 800C6EA8 AFA30014 */  sw    $v1, 0x14($sp)
/* 0C7AAC 800C6EAC 0C03189D */  jal   gzip_huft_build
/* 0C7AB0 800C6EB0 AFA80018 */   sw    $t0, 0x18($sp)
/* 0C7AB4 800C6EB4 23AB0044 */  addi  $t3, $sp, 0x44
/* 0C7AB8 800C6EB8 2408000A */  li    $t0, 10
/* 0C7ABC 800C6EBC 24090005 */  li    $t1, 5
.L800C6EC0:
/* 0C7AC0 800C6EC0 2508FFFF */  addiu $t0, $t0, -1
/* 0C7AC4 800C6EC4 AD690000 */  sw    $t1, ($t3)
/* 0C7AC8 800C6EC8 AD690004 */  sw    $t1, 4($t3)
/* 0C7ACC 800C6ECC AD690008 */  sw    $t1, 8($t3)
/* 0C7AD0 800C6ED0 1500FFFB */  bnez  $t0, .L800C6EC0
/* 0C7AD4 800C6ED4 256B000C */   addiu $t3, $t3, 0xc
/* 0C7AD8 800C6ED8 3C02800F */  lui   $v0, %hi(gzip_cpdext) # $v0, 0x800f
/* 0C7ADC 800C6EDC 3C07800F */  lui   $a3, %hi(gzip_cpdist) # $a3, 0x800f
/* 0C7AE0 800C6EE0 2442946E */  addiu $v0, %lo(gzip_cpdext) # addiu $v0, $v0, -0x6b92
/* 0C7AE4 800C6EE4 23A30028 */  addi  $v1, $sp, 0x28
/* 0C7AE8 800C6EE8 23A8002C */  addi  $t0, $sp, 0x2c
/* 0C7AEC 800C6EEC AFA90040 */  sw    $t1, 0x40($sp)
/* 0C7AF0 800C6EF0 23A40044 */  addi  $a0, $sp, 0x44
/* 0C7AF4 800C6EF4 2405001E */  li    $a1, 30
/* 0C7AF8 800C6EF8 24060000 */  li    $a2, 0
/* 0C7AFC 800C6EFC 24E79432 */  addiu $a3, %lo(gzip_cpdist) # addiu $a3, $a3, -0x6bce
/* 0C7B00 800C6F00 AFA20010 */  sw    $v0, 0x10($sp)
/* 0C7B04 800C6F04 AFA30014 */  sw    $v1, 0x14($sp)
/* 0C7B08 800C6F08 0C03189D */  jal   gzip_huft_build
/* 0C7B0C 800C6F0C AFA80018 */   sw    $t0, 0x18($sp)
/* 0C7B10 800C6F10 8FA40020 */  lw    $a0, 0x20($sp)
/* 0C7B14 800C6F14 8FA50028 */  lw    $a1, 0x28($sp)
/* 0C7B18 800C6F18 8FA60024 */  lw    $a2, 0x24($sp)
/* 0C7B1C 800C6F1C 0C031C10 */  jal   gzip_inflate_codes
/* 0C7B20 800C6F20 8FA7002C */   lw    $a3, 0x2c($sp)
/* 0C7B24 800C6F24 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0C7B28 800C6F28 27BD0530 */  addiu $sp, $sp, 0x530
/* 0C7B2C 800C6F2C 03E00008 */  jr    $ra
/* 0C7B30 800C6F30 00000000 */   nop   

