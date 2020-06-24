.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800CDCA0
/* 0CE8A0 800CDCA0 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 0CE8A4 800CDCA4 3C0E8013 */  lui   $t6, %hi(D_8012CDE0) # $t6, 0x8013
/* 0CE8A8 800CDCA8 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0CE8AC 800CDCAC 25CECDE0 */  addiu $t6, %lo(D_8012CDE0) # addiu $t6, $t6, -0x3220
/* 0CE8B0 800CDCB0 240F0002 */  li    $t7, 2
/* 0CE8B4 800CDCB4 AFA40060 */  sw    $a0, 0x60($sp)
/* 0CE8B8 800CDCB8 AFA50064 */  sw    $a1, 0x64($sp)
/* 0CE8BC 800CDCBC AFA60068 */  sw    $a2, 0x68($sp)
/* 0CE8C0 800CDCC0 AFA7006C */  sw    $a3, 0x6c($sp)
/* 0CE8C4 800CDCC4 AFB00018 */  sw    $s0, 0x18($sp)
/* 0CE8C8 800CDCC8 AFA0005C */  sw    $zero, 0x5c($sp)
/* 0CE8CC 800CDCCC AFAE0054 */  sw    $t6, 0x54($sp)
/* 0CE8D0 800CDCD0 0C033594 */  jal   func_800CD650
/* 0CE8D4 800CDCD4 AFAF0028 */   sw    $t7, 0x28($sp)
/* 0CE8D8 800CDCD8 24180002 */  li    $t8, 2
/* 0CE8DC 800CDCDC 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CE8E0 800CDCE0 A038CD90 */  sb    $t8, %lo(D_8012CD90)($at)
/* 0CE8E4 800CDCE4 8FA40064 */  lw    $a0, 0x64($sp)
/* 0CE8E8 800CDCE8 0C0337B9 */  jal   func_800CDEE4
/* 0CE8EC 800CDCEC 97A5006A */   lhu   $a1, 0x6a($sp)
/* 0CE8F0 800CDCF0 3C058013 */  lui   $a1, %hi(D_8012CDE0) # $a1, 0x8013
/* 0CE8F4 800CDCF4 24A5CDE0 */  addiu $a1, %lo(D_8012CDE0) # addiu $a1, $a1, -0x3220
/* 0CE8F8 800CDCF8 0C0335B0 */  jal   func_800CD6C0
/* 0CE8FC 800CDCFC 24040001 */   li    $a0, 1
/* 0CE900 800CDD00 AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CE904 800CDD04 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CE908 800CDD08 00002825 */  move  $a1, $zero
/* 0CE90C 800CDD0C 0C0322EC */  jal   osRecvMesg
/* 0CE910 800CDD10 24060001 */   li    $a2, 1
.L800CDD14:
/* 0CE914 800CDD14 AFA00058 */  sw    $zero, 0x58($sp)
.L800CDD18:
/* 0CE918 800CDD18 8FA80058 */  lw    $t0, 0x58($sp)
/* 0CE91C 800CDD1C 8FAA0058 */  lw    $t2, 0x58($sp)
/* 0CE920 800CDD20 3C018013 */  lui   $at, 0x8013
/* 0CE924 800CDD24 00084880 */  sll   $t1, $t0, 2
/* 0CE928 800CDD28 00290821 */  addu  $at, $at, $t1
/* 0CE92C 800CDD2C 241900FF */  li    $t9, 255
/* 0CE930 800CDD30 AC39CDE0 */  sw    $t9, -0x3220($at)
/* 0CE934 800CDD34 254B0001 */  addiu $t3, $t2, 1
/* 0CE938 800CDD38 29610010 */  slti  $at, $t3, 0x10
/* 0CE93C 800CDD3C 1420FFF6 */  bnez  $at, .L800CDD18
/* 0CE940 800CDD40 AFAB0058 */   sw    $t3, 0x58($sp)
/* 0CE944 800CDD44 3C018013 */  lui   $at, %hi(D_8012CE1C) # $at, 0x8013
/* 0CE948 800CDD48 3C058013 */  lui   $a1, %hi(D_8012CDE0) # $a1, 0x8013
/* 0CE94C 800CDD4C AC20CE1C */  sw    $zero, %lo(D_8012CE1C)($at)
/* 0CE950 800CDD50 24A5CDE0 */  addiu $a1, %lo(D_8012CDE0) # addiu $a1, $a1, -0x3220
/* 0CE954 800CDD54 0C0335B0 */  jal   func_800CD6C0
/* 0CE958 800CDD58 00002025 */   move  $a0, $zero
/* 0CE95C 800CDD5C AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CE960 800CDD60 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CE964 800CDD64 00002825 */  move  $a1, $zero
/* 0CE968 800CDD68 0C0322EC */  jal   osRecvMesg
/* 0CE96C 800CDD6C 24060001 */   li    $a2, 1
/* 0CE970 800CDD70 8FAD0064 */  lw    $t5, 0x64($sp)
/* 0CE974 800CDD74 3C0C8013 */  lui   $t4, %hi(D_8012CDE0) # $t4, 0x8013
/* 0CE978 800CDD78 258CCDE0 */  addiu $t4, %lo(D_8012CDE0) # addiu $t4, $t4, -0x3220
/* 0CE97C 800CDD7C 11A0000C */  beqz  $t5, .L800CDDB0
/* 0CE980 800CDD80 AFAC0054 */   sw    $t4, 0x54($sp)
/* 0CE984 800CDD84 19A0000A */  blez  $t5, .L800CDDB0
/* 0CE988 800CDD88 AFA00058 */   sw    $zero, 0x58($sp)
.L800CDD8C:
/* 0CE98C 800CDD8C 8FB80058 */  lw    $t8, 0x58($sp)
/* 0CE990 800CDD90 8FB90064 */  lw    $t9, 0x64($sp)
/* 0CE994 800CDD94 8FAE0054 */  lw    $t6, 0x54($sp)
/* 0CE998 800CDD98 27080001 */  addiu $t0, $t8, 1
/* 0CE99C 800CDD9C 0119082A */  slt   $at, $t0, $t9
/* 0CE9A0 800CDDA0 25CF0001 */  addiu $t7, $t6, 1
/* 0CE9A4 800CDDA4 AFA80058 */  sw    $t0, 0x58($sp)
/* 0CE9A8 800CDDA8 1420FFF8 */  bnez  $at, .L800CDD8C
/* 0CE9AC 800CDDAC AFAF0054 */   sw    $t7, 0x54($sp)
.L800CDDB0:
/* 0CE9B0 800CDDB0 8FAA0054 */  lw    $t2, 0x54($sp)
/* 0CE9B4 800CDDB4 27A9002C */  addiu $t1, $sp, 0x2c
/* 0CE9B8 800CDDB8 254C0024 */  addiu $t4, $t2, 0x24
.L800CDDBC:
/* 0CE9BC 800CDDBC 89410000 */  lwl   $at, ($t2)
/* 0CE9C0 800CDDC0 99410003 */  lwr   $at, 3($t2)
/* 0CE9C4 800CDDC4 254A000C */  addiu $t2, $t2, 0xc
/* 0CE9C8 800CDDC8 2529000C */  addiu $t1, $t1, 0xc
/* 0CE9CC 800CDDCC AD21FFF4 */  sw    $at, -0xc($t1)
/* 0CE9D0 800CDDD0 8941FFF8 */  lwl   $at, -8($t2)
/* 0CE9D4 800CDDD4 9941FFFB */  lwr   $at, -5($t2)
/* 0CE9D8 800CDDD8 AD21FFF8 */  sw    $at, -8($t1)
/* 0CE9DC 800CDDDC 8941FFFC */  lwl   $at, -4($t2)
/* 0CE9E0 800CDDE0 9941FFFF */  lwr   $at, -1($t2)
/* 0CE9E4 800CDDE4 154CFFF5 */  bne   $t2, $t4, .L800CDDBC
/* 0CE9E8 800CDDE8 AD21FFFC */   sw    $at, -4($t1)
/* 0CE9EC 800CDDEC 89410000 */  lwl   $at, ($t2)
/* 0CE9F0 800CDDF0 99410003 */  lwr   $at, 3($t2)
/* 0CE9F4 800CDDF4 AD210000 */  sw    $at, ($t1)
/* 0CE9F8 800CDDF8 93AD002E */  lbu   $t5, 0x2e($sp)
/* 0CE9FC 800CDDFC 31AE00C0 */  andi  $t6, $t5, 0xc0
/* 0CEA00 800CDE00 000E7903 */  sra   $t7, $t6, 4
/* 0CEA04 800CDE04 15E00025 */  bnez  $t7, .L800CDE9C
/* 0CEA08 800CDE08 AFAF005C */   sw    $t7, 0x5c($sp)
/* 0CEA0C 800CDE0C 27A4002C */  addiu $a0, $sp, 0x2c
/* 0CEA10 800CDE10 0C033608 */  jal   func_800CD820
/* 0CEA14 800CDE14 24840006 */   addiu $a0, $a0, 6
/* 0CEA18 800CDE18 A3A20027 */  sb    $v0, 0x27($sp)
/* 0CEA1C 800CDE1C 93B80027 */  lbu   $t8, 0x27($sp)
/* 0CEA20 800CDE20 93A80052 */  lbu   $t0, 0x52($sp)
/* 0CEA24 800CDE24 1308000F */  beq   $t8, $t0, .L800CDE64
/* 0CEA28 800CDE28 00000000 */   nop   
/* 0CEA2C 800CDE2C 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CEA30 800CDE30 0C033B75 */  jal   func_800CEDD4
/* 0CEA34 800CDE34 8FA50064 */   lw    $a1, 0x64($sp)
/* 0CEA38 800CDE38 AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CEA3C 800CDE3C 8FB9005C */  lw    $t9, 0x5c($sp)
/* 0CEA40 800CDE40 13200005 */  beqz  $t9, .L800CDE58
/* 0CEA44 800CDE44 00000000 */   nop   
/* 0CEA48 800CDE48 0C0335A5 */  jal   func_800CD694
/* 0CEA4C 800CDE4C 00000000 */   nop   
/* 0CEA50 800CDE50 1000001F */  b     .L800CDED0
/* 0CEA54 800CDE54 8FA2005C */   lw    $v0, 0x5c($sp)
.L800CDE58:
/* 0CEA58 800CDE58 240B0004 */  li    $t3, 4
/* 0CEA5C 800CDE5C 1000000F */  b     .L800CDE9C
/* 0CEA60 800CDE60 AFAB005C */   sw    $t3, 0x5c($sp)
.L800CDE64:
/* 0CEA64 800CDE64 AFA00058 */  sw    $zero, 0x58($sp)
.L800CDE68:
/* 0CEA68 800CDE68 8FAC0058 */  lw    $t4, 0x58($sp)
/* 0CEA6C 800CDE6C 8FA9006C */  lw    $t1, 0x6c($sp)
/* 0CEA70 800CDE70 03AC5021 */  addu  $t2, $sp, $t4
/* 0CEA74 800CDE74 914A0032 */  lbu   $t2, 0x32($t2)
/* 0CEA78 800CDE78 A12A0000 */  sb    $t2, ($t1)
/* 0CEA7C 800CDE7C 8FAF0058 */  lw    $t7, 0x58($sp)
/* 0CEA80 800CDE80 8FAD006C */  lw    $t5, 0x6c($sp)
/* 0CEA84 800CDE84 25F80001 */  addiu $t8, $t7, 1
/* 0CEA88 800CDE88 2B010020 */  slti  $at, $t8, 0x20
/* 0CEA8C 800CDE8C 25AE0001 */  addiu $t6, $t5, 1
/* 0CEA90 800CDE90 AFB80058 */  sw    $t8, 0x58($sp)
/* 0CEA94 800CDE94 1420FFF4 */  bnez  $at, .L800CDE68
/* 0CEA98 800CDE98 AFAE006C */   sw    $t6, 0x6c($sp)
.L800CDE9C:
/* 0CEA9C 800CDE9C 8FA8005C */  lw    $t0, 0x5c($sp)
/* 0CEAA0 800CDEA0 24010004 */  li    $at, 4
/* 0CEAA4 800CDEA4 15010007 */  bne   $t0, $at, .L800CDEC4
/* 0CEAA8 800CDEA8 00000000 */   nop   
/* 0CEAAC 800CDEAC 8FB90028 */  lw    $t9, 0x28($sp)
/* 0CEAB0 800CDEB0 2B300000 */  slti  $s0, $t9, 0
/* 0CEAB4 800CDEB4 3A100001 */  xori  $s0, $s0, 1
/* 0CEAB8 800CDEB8 272BFFFF */  addiu $t3, $t9, -1
/* 0CEABC 800CDEBC 1600FF95 */  bnez  $s0, .L800CDD14
/* 0CEAC0 800CDEC0 AFAB0028 */   sw    $t3, 0x28($sp)
.L800CDEC4:
/* 0CEAC4 800CDEC4 0C0335A5 */  jal   func_800CD694
/* 0CEAC8 800CDEC8 00000000 */   nop   
/* 0CEACC 800CDECC 8FA2005C */  lw    $v0, 0x5c($sp)
.L800CDED0:
/* 0CEAD0 800CDED0 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0CEAD4 800CDED4 8FB00018 */  lw    $s0, 0x18($sp)
/* 0CEAD8 800CDED8 27BD0060 */  addiu $sp, $sp, 0x60
/* 0CEADC 800CDEDC 03E00008 */  jr    $ra
/* 0CEAE0 800CDEE0 00000000 */   nop   

glabel func_800CDEE4
/* 0CEAE4 800CDEE4 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0CEAE8 800CDEE8 3C0E8013 */  lui   $t6, %hi(D_8012CDE0) # $t6, 0x8013
/* 0CEAEC 800CDEEC 25CECDE0 */  addiu $t6, %lo(D_8012CDE0) # addiu $t6, $t6, -0x3220
/* 0CEAF0 800CDEF0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CEAF4 800CDEF4 AFA40048 */  sw    $a0, 0x48($sp)
/* 0CEAF8 800CDEF8 AFA5004C */  sw    $a1, 0x4c($sp)
/* 0CEAFC 800CDEFC AFAE0044 */  sw    $t6, 0x44($sp)
/* 0CEB00 800CDF00 AFA00018 */  sw    $zero, 0x18($sp)
.L800CDF04:
/* 0CEB04 800CDF04 8FAF0018 */  lw    $t7, 0x18($sp)
/* 0CEB08 800CDF08 8FB90018 */  lw    $t9, 0x18($sp)
/* 0CEB0C 800CDF0C 3C018013 */  lui   $at, 0x8013
/* 0CEB10 800CDF10 000FC080 */  sll   $t8, $t7, 2
/* 0CEB14 800CDF14 00380821 */  addu  $at, $at, $t8
/* 0CEB18 800CDF18 AC20CDE0 */  sw    $zero, -0x3220($at)
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
/* 0CEB58 800CDF58 0C0335DC */  jal   func_800CD770
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
