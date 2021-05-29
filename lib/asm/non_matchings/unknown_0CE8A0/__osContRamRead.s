glabel __osContRamRead
/* 0CE8A0 800CDCA0 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 0CE8A4 800CDCA4 3C0E8013 */  lui   $t6, %hi(__osPfsPifRam) # $t6, 0x8013
/* 0CE8A8 800CDCA8 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0CE8AC 800CDCAC 25CECDE0 */  addiu $t6, %lo(__osPfsPifRam) # addiu $t6, $t6, -0x3220
/* 0CE8B0 800CDCB0 240F0002 */  li    $t7, 2
/* 0CE8B4 800CDCB4 AFA40060 */  sw    $a0, 0x60($sp)
/* 0CE8B8 800CDCB8 AFA50064 */  sw    $a1, 0x64($sp)
/* 0CE8BC 800CDCBC AFA60068 */  sw    $a2, 0x68($sp)
/* 0CE8C0 800CDCC0 AFA7006C */  sw    $a3, 0x6c($sp)
/* 0CE8C4 800CDCC4 AFB00018 */  sw    $s0, 0x18($sp)
/* 0CE8C8 800CDCC8 AFA0005C */  sw    $zero, 0x5c($sp)
/* 0CE8CC 800CDCCC AFAE0054 */  sw    $t6, 0x54($sp)
/* 0CE8D0 800CDCD0 0C033594 */  jal   __osSiGetAccess
/* 0CE8D4 800CDCD4 AFAF0028 */   sw    $t7, 0x28($sp)
/* 0CE8D8 800CDCD8 24180002 */  li    $t8, 2
/* 0CE8DC 800CDCDC 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CE8E0 800CDCE0 A038CD90 */  sb    $t8, %lo(D_8012CD90)($at)
/* 0CE8E4 800CDCE4 8FA40064 */  lw    $a0, 0x64($sp)
/* 0CE8E8 800CDCE8 0C0337B9 */  jal   __osPackRamReadData
/* 0CE8EC 800CDCEC 97A5006A */   lhu   $a1, 0x6a($sp)
/* 0CE8F0 800CDCF0 3C058013 */  lui   $a1, %hi(__osPfsPifRam) # $a1, 0x8013
/* 0CE8F4 800CDCF4 24A5CDE0 */  addiu $a1, %lo(__osPfsPifRam) # addiu $a1, $a1, -0x3220
/* 0CE8F8 800CDCF8 0C0335B0 */  jal   __osSiRawStartDma
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
/* 0CE920 800CDD20 3C018013 */  lui   $at, %hi(__osPfsPifRam) # $at, 0x8013
/* 0CE924 800CDD24 00084880 */  sll   $t1, $t0, 2
/* 0CE928 800CDD28 00290821 */  addu  $at, $at, $t1
/* 0CE92C 800CDD2C 241900FF */  li    $t9, 255
/* 0CE930 800CDD30 AC39CDE0 */  sw    $t9, %lo(__osPfsPifRam)($at)
/* 0CE934 800CDD34 254B0001 */  addiu $t3, $t2, 1
/* 0CE938 800CDD38 29610010 */  slti  $at, $t3, 0x10
/* 0CE93C 800CDD3C 1420FFF6 */  bnez  $at, .L800CDD18
/* 0CE940 800CDD40 AFAB0058 */   sw    $t3, 0x58($sp)
/* 0CE944 800CDD44 3C018013 */  lui   $at, %hi(D_8012CE1C) # $at, 0x8013
/* 0CE948 800CDD48 3C058013 */  lui   $a1, %hi(__osPfsPifRam) # $a1, 0x8013
/* 0CE94C 800CDD4C AC20CE1C */  sw    $zero, %lo(D_8012CE1C)($at)
/* 0CE950 800CDD50 24A5CDE0 */  addiu $a1, %lo(__osPfsPifRam) # addiu $a1, $a1, -0x3220
/* 0CE954 800CDD54 0C0335B0 */  jal   __osSiRawStartDma
/* 0CE958 800CDD58 00002025 */   move  $a0, $zero
/* 0CE95C 800CDD5C AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CE960 800CDD60 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CE964 800CDD64 00002825 */  move  $a1, $zero
/* 0CE968 800CDD68 0C0322EC */  jal   osRecvMesg
/* 0CE96C 800CDD6C 24060001 */   li    $a2, 1
/* 0CE970 800CDD70 8FAD0064 */  lw    $t5, 0x64($sp)
/* 0CE974 800CDD74 3C0C8013 */  lui   $t4, %hi(__osPfsPifRam) # $t4, 0x8013
/* 0CE978 800CDD78 258CCDE0 */  addiu $t4, %lo(__osPfsPifRam) # addiu $t4, $t4, -0x3220
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
/* 0CEA10 800CDE10 0C033608 */  jal   __osContDataCrc
/* 0CEA14 800CDE14 24840006 */   addiu $a0, $a0, 6
/* 0CEA18 800CDE18 A3A20027 */  sb    $v0, 0x27($sp)
/* 0CEA1C 800CDE1C 93B80027 */  lbu   $t8, 0x27($sp)
/* 0CEA20 800CDE20 93A80052 */  lbu   $t0, 0x52($sp)
/* 0CEA24 800CDE24 1308000F */  beq   $t8, $t0, .L800CDE64
/* 0CEA28 800CDE28 00000000 */   nop   
/* 0CEA2C 800CDE2C 8FA40060 */  lw    $a0, 0x60($sp)
/* 0CEA30 800CDE30 0C033B75 */  jal   __osPfsGetStatus
/* 0CEA34 800CDE34 8FA50064 */   lw    $a1, 0x64($sp)
/* 0CEA38 800CDE38 AFA2005C */  sw    $v0, 0x5c($sp)
/* 0CEA3C 800CDE3C 8FB9005C */  lw    $t9, 0x5c($sp)
/* 0CEA40 800CDE40 13200005 */  beqz  $t9, .L800CDE58
/* 0CEA44 800CDE44 00000000 */   nop   
/* 0CEA48 800CDE48 0C0335A5 */  jal   __osSiRelAccess
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
/* 0CEAC4 800CDEC4 0C0335A5 */  jal   __osSiRelAccess
/* 0CEAC8 800CDEC8 00000000 */   nop   
/* 0CEACC 800CDECC 8FA2005C */  lw    $v0, 0x5c($sp)
.L800CDED0:
/* 0CEAD0 800CDED0 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0CEAD4 800CDED4 8FB00018 */  lw    $s0, 0x18($sp)
/* 0CEAD8 800CDED8 27BD0060 */  addiu $sp, $sp, 0x60
/* 0CEADC 800CDEDC 03E00008 */  jr    $ra
/* 0CEAE0 800CDEE0 00000000 */   nop   

