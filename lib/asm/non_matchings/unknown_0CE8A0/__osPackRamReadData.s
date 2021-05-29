glabel __osPackRamReadData
/* 0CEAE4 800CDEE4 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0CEAE8 800CDEE8 3C0E8013 */  lui   $t6, %hi(__osPfsPifRam) # $t6, 0x8013
/* 0CEAEC 800CDEEC 25CECDE0 */  addiu $t6, %lo(__osPfsPifRam) # addiu $t6, $t6, -0x3220
/* 0CEAF0 800CDEF0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CEAF4 800CDEF4 AFA40048 */  sw    $a0, 0x48($sp)
/* 0CEAF8 800CDEF8 AFA5004C */  sw    $a1, 0x4c($sp)
/* 0CEAFC 800CDEFC AFAE0044 */  sw    $t6, 0x44($sp)
/* 0CEB00 800CDF00 AFA00018 */  sw    $zero, 0x18($sp)
.L800CDF04:
/* 0CEB04 800CDF04 8FAF0018 */  lw    $t7, 0x18($sp)
/* 0CEB08 800CDF08 8FB90018 */  lw    $t9, 0x18($sp)
/* 0CEB0C 800CDF0C 3C018013 */  lui   $at, %hi(__osPfsPifRam) # $at, 0x8013
/* 0CEB10 800CDF10 000FC080 */  sll   $t8, $t7, 2
/* 0CEB14 800CDF14 00380821 */  addu  $at, $at, $t8
/* 0CEB18 800CDF18 AC20CDE0 */  sw    $zero, %lo(__osPfsPifRam)($at)
/* 0CEB1C 800CDF1C 27280001 */  addiu $t0, $t9, 1
/* 0CEB20 800CDF20 29010010 */  slti  $at, $t0, 0x10
/* 0CEB24 800CDF24 1420FFF7 */  bnez  $at, .L800CDF04
/* 0CEB28 800CDF28 AFA80018 */   sw    $t0, 0x18($sp)
/* 0CEB2C 800CDF2C 24090001 */  li    $t1, 1
/* 0CEB30 800CDF30 3C018013 */  lui   $at, %hi(D_8012CE1C) # $at, 0x8013
/* 0CEB34 800CDF34 240A00FF */  li    $t2, 255
/* 0CEB38 800CDF38 240B0003 */  li    $t3, 3
/* 0CEB3C 800CDF3C 240C0021 */  li    $t4, 33
/* 0CEB40 800CDF40 240D0002 */  li    $t5, 2
/* 0CEB44 800CDF44 AC29CE1C */  sw    $t1, %lo(D_8012CE1C)($at)
/* 0CEB48 800CDF48 A3AA001C */  sb    $t2, 0x1c($sp)
/* 0CEB4C 800CDF4C A3AB001D */  sb    $t3, 0x1d($sp)
/* 0CEB50 800CDF50 A3AC001E */  sb    $t4, 0x1e($sp)
/* 0CEB54 800CDF54 A3AD001F */  sb    $t5, 0x1f($sp)
/* 0CEB58 800CDF58 0C0335DC */  jal   __osContAddressCrc
/* 0CEB5C 800CDF5C 97A4004E */   lhu   $a0, 0x4e($sp)
/* 0CEB60 800CDF60 97AE004E */  lhu   $t6, 0x4e($sp)
/* 0CEB64 800CDF64 241900FF */  li    $t9, 255
/* 0CEB68 800CDF68 A3B90042 */  sb    $t9, 0x42($sp)
/* 0CEB6C 800CDF6C 000E7940 */  sll   $t7, $t6, 5
/* 0CEB70 800CDF70 004FC025 */  or    $t8, $v0, $t7
/* 0CEB74 800CDF74 A7B80020 */  sh    $t8, 0x20($sp)
/* 0CEB78 800CDF78 AFA00018 */  sw    $zero, 0x18($sp)
.L800CDF7C:
/* 0CEB7C 800CDF7C 8FA90018 */  lw    $t1, 0x18($sp)
/* 0CEB80 800CDF80 240800FF */  li    $t0, 255
/* 0CEB84 800CDF84 03A95021 */  addu  $t2, $sp, $t1
/* 0CEB88 800CDF88 A1480022 */  sb    $t0, 0x22($t2)
/* 0CEB8C 800CDF8C 8FAB0018 */  lw    $t3, 0x18($sp)
/* 0CEB90 800CDF90 256C0001 */  addiu $t4, $t3, 1
/* 0CEB94 800CDF94 29810020 */  slti  $at, $t4, 0x20
/* 0CEB98 800CDF98 1420FFF8 */  bnez  $at, .L800CDF7C
/* 0CEB9C 800CDF9C AFAC0018 */   sw    $t4, 0x18($sp)
/* 0CEBA0 800CDFA0 8FAD0048 */  lw    $t5, 0x48($sp)
/* 0CEBA4 800CDFA4 11A0000E */  beqz  $t5, .L800CDFE0
/* 0CEBA8 800CDFA8 00000000 */   nop   
/* 0CEBAC 800CDFAC 19A0000C */  blez  $t5, .L800CDFE0
/* 0CEBB0 800CDFB0 AFA00018 */   sw    $zero, 0x18($sp)
.L800CDFB4:
/* 0CEBB4 800CDFB4 8FAE0044 */  lw    $t6, 0x44($sp)
/* 0CEBB8 800CDFB8 A1C00000 */  sb    $zero, ($t6)
/* 0CEBBC 800CDFBC 8FB90018 */  lw    $t9, 0x18($sp)
/* 0CEBC0 800CDFC0 8FA90048 */  lw    $t1, 0x48($sp)
/* 0CEBC4 800CDFC4 8FAF0044 */  lw    $t7, 0x44($sp)
/* 0CEBC8 800CDFC8 27280001 */  addiu $t0, $t9, 1
/* 0CEBCC 800CDFCC 0109082A */  slt   $at, $t0, $t1
/* 0CEBD0 800CDFD0 25F80001 */  addiu $t8, $t7, 1
/* 0CEBD4 800CDFD4 AFA80018 */  sw    $t0, 0x18($sp)
/* 0CEBD8 800CDFD8 1420FFF6 */  bnez  $at, .L800CDFB4
/* 0CEBDC 800CDFDC AFB80044 */   sw    $t8, 0x44($sp)
.L800CDFE0:
/* 0CEBE0 800CDFE0 27AB001C */  addiu $t3, $sp, 0x1c
/* 0CEBE4 800CDFE4 256D0024 */  addiu $t5, $t3, 0x24
/* 0CEBE8 800CDFE8 8FAA0044 */  lw    $t2, 0x44($sp)
.L800CDFEC:
/* 0CEBEC 800CDFEC 8D610000 */  lw    $at, ($t3)
/* 0CEBF0 800CDFF0 256B000C */  addiu $t3, $t3, 0xc
/* 0CEBF4 800CDFF4 254A000C */  addiu $t2, $t2, 0xc
/* 0CEBF8 800CDFF8 A941FFF4 */  swl   $at, -0xc($t2)
/* 0CEBFC 800CDFFC B941FFF7 */  swr   $at, -9($t2)
/* 0CEC00 800CE000 8D61FFF8 */  lw    $at, -8($t3)
/* 0CEC04 800CE004 A941FFF8 */  swl   $at, -8($t2)
/* 0CEC08 800CE008 B941FFFB */  swr   $at, -5($t2)
/* 0CEC0C 800CE00C 8D61FFFC */  lw    $at, -4($t3)
/* 0CEC10 800CE010 A941FFFC */  swl   $at, -4($t2)
/* 0CEC14 800CE014 156DFFF5 */  bne   $t3, $t5, .L800CDFEC
/* 0CEC18 800CE018 B941FFFF */   swr   $at, -1($t2)
/* 0CEC1C 800CE01C 8D610000 */  lw    $at, ($t3)
/* 0CEC20 800CE020 241800FE */  li    $t8, 254
/* 0CEC24 800CE024 A9410000 */  swl   $at, ($t2)
/* 0CEC28 800CE028 B9410003 */  swr   $at, 3($t2)
/* 0CEC2C 800CE02C 8FAE0044 */  lw    $t6, 0x44($sp)
/* 0CEC30 800CE030 25CF0028 */  addiu $t7, $t6, 0x28
/* 0CEC34 800CE034 AFAF0044 */  sw    $t7, 0x44($sp)
/* 0CEC38 800CE038 A1F80000 */  sb    $t8, ($t7)
/* 0CEC3C 800CE03C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CEC40 800CE040 27BD0048 */  addiu $sp, $sp, 0x48
/* 0CEC44 800CE044 03E00008 */  jr    $ra
/* 0CEC48 800CE048 00000000 */   nop   

/* 0CEC4C 800CE04C 00000000 */  nop   

