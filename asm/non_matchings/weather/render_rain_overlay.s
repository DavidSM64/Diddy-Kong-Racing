glabel render_rain_overlay
/* 0AE8BC 800ADCBC 27BDFF60 */  addiu $sp, $sp, -0xa0
/* 0AE8C0 800ADCC0 AFBF0044 */  sw    $ra, 0x44($sp)
/* 0AE8C4 800ADCC4 AFB30040 */  sw    $s3, 0x40($sp)
/* 0AE8C8 800ADCC8 AFB2003C */  sw    $s2, 0x3c($sp)
/* 0AE8CC 800ADCCC AFB10038 */  sw    $s1, 0x38($sp)
/* 0AE8D0 800ADCD0 AFB00034 */  sw    $s0, 0x34($sp)
/* 0AE8D4 800ADCD4 E7BB0028 */  swc1  $f27, 0x28($sp)
/* 0AE8D8 800ADCD8 E7BA002C */  swc1  $f26, 0x2c($sp)
/* 0AE8DC 800ADCDC E7B90020 */  swc1  $f25, 0x20($sp)
/* 0AE8E0 800ADCE0 E7B80024 */  swc1  $f24, 0x24($sp)
/* 0AE8E4 800ADCE4 E7B70018 */  swc1  $f23, 0x18($sp)
/* 0AE8E8 800ADCE8 E7B6001C */  swc1  $f22, 0x1c($sp)
/* 0AE8EC 800ADCEC E7B50010 */  swc1  $f21, 0x10($sp)
/* 0AE8F0 800ADCF0 E7B40014 */  swc1  $f20, 0x14($sp)
/* 0AE8F4 800ADCF4 AFA500A4 */  sw    $a1, 0xa4($sp)
/* 0AE8F8 800ADCF8 8C82000C */  lw    $v0, 0xc($a0)
/* 0AE8FC 800ADCFC 00808025 */  move  $s0, $a0
/* 0AE900 800ADD00 1040014A */  beqz  $v0, .L800AE22C
/* 0AE904 800ADD04 8FBF0044 */   lw    $ra, 0x44($sp)
/* 0AE908 800ADD08 90510000 */  lbu   $s1, ($v0)
/* 0AE90C 800ADD0C 90520001 */  lbu   $s2, 1($v0)
/* 0AE910 800ADD10 00117140 */  sll   $t6, $s1, 5
/* 0AE914 800ADD14 00127940 */  sll   $t7, $s2, 5
/* 0AE918 800ADD18 000E1840 */  sll   $v1, $t6, 1
/* 0AE91C 800ADD1C 000FC040 */  sll   $t8, $t7, 1
/* 0AE920 800ADD20 2463FFFF */  addiu $v1, $v1, -1
/* 0AE924 800ADD24 2719FFFF */  addiu $t9, $t8, -1
/* 0AE928 800ADD28 AFA3008C */  sw    $v1, 0x8c($sp)
/* 0AE92C 800ADD2C AFB90088 */  sw    $t9, 0x88($sp)
/* 0AE930 800ADD30 848D0008 */  lh    $t5, 8($a0)
/* 0AE934 800ADD34 00409825 */  move  $s3, $v0
/* 0AE938 800ADD38 01A50019 */  multu $t5, $a1
/* 0AE93C 800ADD3C 01C08825 */  move  $s1, $t6
/* 0AE940 800ADD40 01E09025 */  move  $s2, $t7
/* 0AE944 800ADD44 AFA3004C */  sw    $v1, 0x4c($sp)
/* 0AE948 800ADD48 00002012 */  mflo  $a0
/* 0AE94C 800ADD4C 0C00322D */  jal   normalise_time
/* 0AE950 800ADD50 00000000 */   nop   
/* 0AE954 800ADD54 860F0000 */  lh    $t7, ($s0)
/* 0AE958 800ADD58 8FA3004C */  lw    $v1, 0x4c($sp)
/* 0AE95C 800ADD5C 004FC021 */  addu  $t8, $v0, $t7
/* 0AE960 800ADD60 0303C824 */  and   $t9, $t8, $v1
/* 0AE964 800ADD64 A6190000 */  sh    $t9, ($s0)
/* 0AE968 800ADD68 8FAE00A4 */  lw    $t6, 0xa4($sp)
/* 0AE96C 800ADD6C 860D000A */  lh    $t5, 0xa($s0)
/* 0AE970 800ADD70 00000000 */  nop   
/* 0AE974 800ADD74 01AE0019 */  multu $t5, $t6
/* 0AE978 800ADD78 00002012 */  mflo  $a0
/* 0AE97C 800ADD7C 0C00322D */  jal   normalise_time
/* 0AE980 800ADD80 00000000 */   nop   
/* 0AE984 800ADD84 860E0004 */  lh    $t6, 4($s0)
/* 0AE988 800ADD88 860F0002 */  lh    $t7, 2($s0)
/* 0AE98C 800ADD8C 01D10019 */  multu $t6, $s1
/* 0AE990 800ADD90 8FB90088 */  lw    $t9, 0x88($sp)
/* 0AE994 800ADD94 004FC021 */  addu  $t8, $v0, $t7
/* 0AE998 800ADD98 03196824 */  and   $t5, $t8, $t9
/* 0AE99C 800ADD9C 86180006 */  lh    $t8, 6($s0)
/* 0AE9A0 800ADDA0 A60D0002 */  sh    $t5, 2($s0)
/* 0AE9A4 800ADDA4 3C0D800E */  lui   $t5, %hi(D_800E2C6C) # $t5, 0x800e
/* 0AE9A8 800ADDA8 8DAD2C6C */  lw    $t5, %lo(D_800E2C6C)($t5)
/* 0AE9AC 800ADDAC 3C028012 */  lui   $v0, %hi(D_80127C1C) # $v0, 0x8012
/* 0AE9B0 800ADDB0 000D7083 */  sra   $t6, $t5, 2
/* 0AE9B4 800ADDB4 00008812 */  mflo  $s1
/* 0AE9B8 800ADDB8 00117A03 */  sra   $t7, $s1, 8
/* 0AE9BC 800ADDBC 01E08825 */  move  $s1, $t7
/* 0AE9C0 800ADDC0 03120019 */  multu $t8, $s2
/* 0AE9C4 800ADDC4 3C0F800E */  lui   $t7, %hi(gLightningFrequency) # $t7, 0x800e
/* 0AE9C8 800ADDC8 8DEF2C60 */  lw    $t7, %lo(gLightningFrequency)($t7)
/* 0AE9CC 800ADDCC 00009012 */  mflo  $s2
/* 0AE9D0 800ADDD0 0012CA03 */  sra   $t9, $s2, 8
/* 0AE9D4 800ADDD4 03209025 */  move  $s2, $t9
/* 0AE9D8 800ADDD8 01CF0019 */  multu $t6, $t7
/* 0AE9DC 800ADDDC 92190016 */  lbu   $t9, 0x16($s0)
/* 0AE9E0 800ADDE0 00117080 */  sll   $t6, $s1, 2
/* 0AE9E4 800ADDE4 00001812 */  mflo  $v1
/* 0AE9E8 800ADDE8 0003C383 */  sra   $t8, $v1, 0xe
/* 0AE9EC 800ADDEC 00000000 */  nop   
/* 0AE9F0 800ADDF0 03380019 */  multu $t9, $t8
/* 0AE9F4 800ADDF4 00001812 */  mflo  $v1
/* 0AE9F8 800ADDF8 00036C03 */  sra   $t5, $v1, 0x10
/* 0AE9FC 800ADDFC 19A0010A */  blez  $t5, .L800AE228
/* 0AEA00 800ADE00 01A01825 */   move  $v1, $t5
/* 0AEA04 800ADE04 8C427C1C */  lw    $v0, %lo(D_80127C1C)($v0)
/* 0AEA08 800ADE08 01D17023 */  subu  $t6, $t6, $s1
/* 0AEA0C 800ADE0C 844F0000 */  lh    $t7, ($v0)
/* 0AEA10 800ADE10 000E7040 */  sll   $t6, $t6, 1
/* 0AEA14 800ADE14 01CF0019 */  multu $t6, $t7
/* 0AEA18 800ADE18 860D0000 */  lh    $t5, ($s0)
/* 0AEA1C 800ADE1C 860A0002 */  lh    $t2, 2($s0)
/* 0AEA20 800ADE20 8FAF008C */  lw    $t7, 0x8c($sp)
/* 0AEA24 800ADE24 84440004 */  lh    $a0, 4($v0)
/* 0AEA28 800ADE28 AFA30084 */  sw    $v1, 0x84($sp)
/* 0AEA2C 800ADE2C 024A9021 */  addu  $s2, $s2, $t2
/* 0AEA30 800ADE30 AFAA0098 */  sw    $t2, 0x98($sp)
/* 0AEA34 800ADE34 0000C012 */  mflo  $t8
/* 0AEA38 800ADE38 0018CC03 */  sra   $t9, $t8, 0x10
/* 0AEA3C 800ADE3C 01B97021 */  addu  $t6, $t5, $t9
/* 0AEA40 800ADE40 01CF4024 */  and   $t0, $t6, $t7
/* 0AEA44 800ADE44 02288821 */  addu  $s1, $s1, $t0
/* 0AEA48 800ADE48 0C01C1F1 */  jal   sins_f
/* 0AEA4C 800ADE4C AFA8009C */   sw    $t0, 0x9c($sp)
/* 0AEA50 800ADE50 3C188012 */  lui   $t8, %hi(D_80127C1C) # $t8, 0x8012
/* 0AEA54 800ADE54 8F187C1C */  lw    $t8, %lo(D_80127C1C)($t8)
/* 0AEA58 800ADE58 00000000 */  nop   
/* 0AEA5C 800ADE5C 87040004 */  lh    $a0, 4($t8)
/* 0AEA60 800ADE60 0C01C1FE */  jal   coss_f
/* 0AEA64 800ADE64 E7A0007C */   swc1  $f0, 0x7c($sp)
/* 0AEA68 800ADE68 3C01800E */  lui   $at, %hi(D_800E2A8C) # $at, 0x800e
/* 0AEA6C 800ADE6C C42C2A8C */  lwc1  $f12, %lo(D_800E2A8C)($at)
/* 0AEA70 800ADE70 3C01800E */  lui   $at, %hi(D_800E2A9C) # $at, 0x800e
/* 0AEA74 800ADE74 46006102 */  mul.s $f4, $f12, $f0
/* 0AEA78 800ADE78 C7A2007C */  lwc1  $f2, 0x7c($sp)
/* 0AEA7C 800ADE7C C42E2A90 */  lwc1  $f14, %lo(D_800E2A90)($at)
/* 0AEA80 800ADE80 C4302A94 */  lwc1  $f16, %lo(D_800E2A94)($at)
/* 0AEA84 800ADE84 46027182 */  mul.s $f6, $f14, $f2
/* 0AEA88 800ADE88 C4322A98 */  lwc1  $f18, %lo(D_800E2A98)($at)
/* 0AEA8C 800ADE8C C4342A9C */  lwc1  $f20, %lo(D_800E2A9C)($at)
/* 0AEA90 800ADE90 3C01800E */  lui   $at, %hi(D_800E2AA8) # $at, 0x800e
/* 0AEA94 800ADE94 46062201 */  sub.s $f8, $f4, $f6
/* 0AEA98 800ADE98 C4362AA0 */  lwc1  $f22, %lo(D_800E2AA0)($at)
/* 0AEA9C 800ADE9C 444EF800 */  cfc1  $t6, $31
/* 0AEAA0 800ADEA0 C4382AA4 */  lwc1  $f24, %lo(D_800E2AA4)($at)
/* 0AEAA4 800ADEA4 C43A2AA8 */  lwc1  $f26, %lo(D_800E2AA8)($at)
/* 0AEAA8 800ADEA8 35C10003 */  ori   $at, $t6, 3
/* 0AEAAC 800ADEAC 38210002 */  xori  $at, $at, 2
/* 0AEAB0 800ADEB0 44C1F800 */  ctc1  $at, $31
/* 0AEAB4 800ADEB4 3C09800E */  lui   $t1, %hi(D_800E2C90) # $t1, 0x800e
/* 0AEAB8 800ADEB8 460042A4 */  cvt.w.s $f10, $f8
/* 0AEABC 800ADEBC 25292C90 */  addiu $t1, %lo(D_800E2C90) # addiu $t1, $t1, 0x2c90
/* 0AEAC0 800ADEC0 44CEF800 */  ctc1  $t6, $31
/* 0AEAC4 800ADEC4 440F5000 */  mfc1  $t7, $f10
/* 0AEAC8 800ADEC8 46026102 */  mul.s $f4, $f12, $f2
/* 0AEACC 800ADECC 8D2D0000 */  lw    $t5, ($t1)
/* 0AEAD0 800ADED0 3C0B800E */  lui   $t3, %hi(D_800E2AAC) # $t3, 0x800e
/* 0AEAD4 800ADED4 000DC880 */  sll   $t9, $t5, 2
/* 0AEAD8 800ADED8 46007182 */  mul.s $f6, $f14, $f0
/* 0AEADC 800ADEDC 032DC821 */  addu  $t9, $t9, $t5
/* 0AEAE0 800ADEE0 256B2AAC */  addiu $t3, %lo(D_800E2AAC) # addiu $t3, $t3, 0x2aac
/* 0AEAE4 800ADEE4 0019C840 */  sll   $t9, $t9, 1
/* 0AEAE8 800ADEE8 46062200 */  add.s $f8, $f4, $f6
/* 0AEAEC 800ADEEC 01791021 */  addu  $v0, $t3, $t9
/* 0AEAF0 800ADEF0 4458F800 */  cfc1  $t8, $31
/* 0AEAF4 800ADEF4 A44F0000 */  sh    $t7, ($v0)
/* 0AEAF8 800ADEF8 37010003 */  ori   $at, $t8, 3
/* 0AEAFC 800ADEFC 38210002 */  xori  $at, $at, 2
/* 0AEB00 800ADF00 44C1F800 */  ctc1  $at, $31
/* 0AEB04 800ADF04 3C0C8012 */  lui   $t4, %hi(gCurrWeatherTriList) # $t4, 0x8012
/* 0AEB08 800ADF08 460042A4 */  cvt.w.s $f10, $f8
/* 0AEB0C 800ADF0C 258C7C18 */  addiu $t4, %lo(gCurrWeatherTriList) # addiu $t4, $t4, 0x7c18
/* 0AEB10 800ADF10 44D8F800 */  ctc1  $t8, $31
/* 0AEB14 800ADF14 440D5000 */  mfc1  $t5, $f10
/* 0AEB18 800ADF18 46008102 */  mul.s $f4, $f16, $f0
/* 0AEB1C 800ADF1C A44D0002 */  sh    $t5, 2($v0)
/* 0AEB20 800ADF20 8FAA0098 */  lw    $t2, 0x98($sp)
/* 0AEB24 800ADF24 8FA30084 */  lw    $v1, 0x84($sp)
/* 0AEB28 800ADF28 46029182 */  mul.s $f6, $f18, $f2
/* 0AEB2C 800ADF2C 8FA8009C */  lw    $t0, 0x9c($sp)
/* 0AEB30 800ADF30 27A40068 */  addiu $a0, $sp, 0x68
/* 0AEB34 800ADF34 00002825 */  move  $a1, $zero
/* 0AEB38 800ADF38 46062201 */  sub.s $f8, $f4, $f6
/* 0AEB3C 800ADF3C 4459F800 */  cfc1  $t9, $31
/* 0AEB40 800ADF40 00000000 */  nop   
/* 0AEB44 800ADF44 37210003 */  ori   $at, $t9, 3
/* 0AEB48 800ADF48 38210002 */  xori  $at, $at, 2
/* 0AEB4C 800ADF4C 44C1F800 */  ctc1  $at, $31
/* 0AEB50 800ADF50 00000000 */  nop   
/* 0AEB54 800ADF54 460042A4 */  cvt.w.s $f10, $f8
/* 0AEB58 800ADF58 44D9F800 */  ctc1  $t9, $31
/* 0AEB5C 800ADF5C 440E5000 */  mfc1  $t6, $f10
/* 0AEB60 800ADF60 46028102 */  mul.s $f4, $f16, $f2
/* 0AEB64 800ADF64 A44E000A */  sh    $t6, 0xa($v0)
/* 0AEB68 800ADF68 46009182 */  mul.s $f6, $f18, $f0
/* 0AEB6C 800ADF6C 46062200 */  add.s $f8, $f4, $f6
/* 0AEB70 800ADF70 444FF800 */  cfc1  $t7, $31
/* 0AEB74 800ADF74 00000000 */  nop   
/* 0AEB78 800ADF78 35E10003 */  ori   $at, $t7, 3
/* 0AEB7C 800ADF7C 38210002 */  xori  $at, $at, 2
/* 0AEB80 800ADF80 44C1F800 */  ctc1  $at, $31
/* 0AEB84 800ADF84 00000000 */  nop   
/* 0AEB88 800ADF88 460042A4 */  cvt.w.s $f10, $f8
/* 0AEB8C 800ADF8C 44CFF800 */  ctc1  $t7, $31
/* 0AEB90 800ADF90 44185000 */  mfc1  $t8, $f10
/* 0AEB94 800ADF94 4600A102 */  mul.s $f4, $f20, $f0
/* 0AEB98 800ADF98 A458000C */  sh    $t8, 0xc($v0)
/* 0AEB9C 800ADF9C 4602B182 */  mul.s $f6, $f22, $f2
/* 0AEBA0 800ADFA0 46062201 */  sub.s $f8, $f4, $f6
/* 0AEBA4 800ADFA4 444DF800 */  cfc1  $t5, $31
/* 0AEBA8 800ADFA8 00000000 */  nop   
/* 0AEBAC 800ADFAC 35A10003 */  ori   $at, $t5, 3
/* 0AEBB0 800ADFB0 38210002 */  xori  $at, $at, 2
/* 0AEBB4 800ADFB4 44C1F800 */  ctc1  $at, $31
/* 0AEBB8 800ADFB8 00000000 */  nop   
/* 0AEBBC 800ADFBC 460042A4 */  cvt.w.s $f10, $f8
/* 0AEBC0 800ADFC0 44CDF800 */  ctc1  $t5, $31
/* 0AEBC4 800ADFC4 44195000 */  mfc1  $t9, $f10
/* 0AEBC8 800ADFC8 4602A102 */  mul.s $f4, $f20, $f2
/* 0AEBCC 800ADFCC A4590014 */  sh    $t9, 0x14($v0)
/* 0AEBD0 800ADFD0 4600B182 */  mul.s $f6, $f22, $f0
/* 0AEBD4 800ADFD4 46062200 */  add.s $f8, $f4, $f6
/* 0AEBD8 800ADFD8 444EF800 */  cfc1  $t6, $31
/* 0AEBDC 800ADFDC 00000000 */  nop   
/* 0AEBE0 800ADFE0 35C10003 */  ori   $at, $t6, 3
/* 0AEBE4 800ADFE4 38210002 */  xori  $at, $at, 2
/* 0AEBE8 800ADFE8 44C1F800 */  ctc1  $at, $31
/* 0AEBEC 800ADFEC 00000000 */  nop   
/* 0AEBF0 800ADFF0 460042A4 */  cvt.w.s $f10, $f8
/* 0AEBF4 800ADFF4 44CEF800 */  ctc1  $t6, $31
/* 0AEBF8 800ADFF8 440F5000 */  mfc1  $t7, $f10
/* 0AEBFC 800ADFFC 4600C102 */  mul.s $f4, $f24, $f0
/* 0AEC00 800AE000 A44F0016 */  sh    $t7, 0x16($v0)
/* 0AEC04 800AE004 3C0F8012 */  lui   $t7, %hi(gCurrWeatherDisplayList) # $t7, 0x8012
/* 0AEC08 800AE008 4602D182 */  mul.s $f6, $f26, $f2
/* 0AEC0C 800AE00C 46062201 */  sub.s $f8, $f4, $f6
/* 0AEC10 800AE010 4458F800 */  cfc1  $t8, $31
/* 0AEC14 800AE014 00000000 */  nop   
/* 0AEC18 800AE018 37010003 */  ori   $at, $t8, 3
/* 0AEC1C 800AE01C 38210002 */  xori  $at, $at, 2
/* 0AEC20 800AE020 44C1F800 */  ctc1  $at, $31
/* 0AEC24 800AE024 00000000 */  nop   
/* 0AEC28 800AE028 460042A4 */  cvt.w.s $f10, $f8
/* 0AEC2C 800AE02C 44D8F800 */  ctc1  $t8, $31
/* 0AEC30 800AE030 440D5000 */  mfc1  $t5, $f10
/* 0AEC34 800AE034 4602C102 */  mul.s $f4, $f24, $f2
/* 0AEC38 800AE038 A44D001E */  sh    $t5, 0x1e($v0)
/* 0AEC3C 800AE03C 3C184000 */  lui   $t8, (0x40000102 >> 16) # lui $t8, 0x4000
/* 0AEC40 800AE040 3C0D4002 */  lui   $t5, (0x40020300 >> 16) # lui $t5, 0x4002
/* 0AEC44 800AE044 4600D182 */  mul.s $f6, $f26, $f0
/* 0AEC48 800AE048 37180102 */  ori   $t8, (0x40000102 & 0xFFFF) # ori $t8, $t8, 0x102
/* 0AEC4C 800AE04C 35AD0300 */  ori   $t5, (0x40020300 & 0xFFFF) # ori $t5, $t5, 0x300
/* 0AEC50 800AE050 46062200 */  add.s $f8, $f4, $f6
/* 0AEC54 800AE054 4459F800 */  cfc1  $t9, $31
/* 0AEC58 800AE058 00000000 */  nop   
/* 0AEC5C 800AE05C 37210003 */  ori   $at, $t9, 3
/* 0AEC60 800AE060 38210002 */  xori  $at, $at, 2
/* 0AEC64 800AE064 44C1F800 */  ctc1  $at, $31
/* 0AEC68 800AE068 00000000 */  nop   
/* 0AEC6C 800AE06C 460042A4 */  cvt.w.s $f10, $f8
/* 0AEC70 800AE070 440E5000 */  mfc1  $t6, $f10
/* 0AEC74 800AE074 44D9F800 */  ctc1  $t9, $31
/* 0AEC78 800AE078 A44E0020 */  sh    $t6, 0x20($v0)
/* 0AEC7C 800AE07C 8DEF7C0C */  lw    $t7, %lo(gCurrWeatherDisplayList)($t7)
/* 0AEC80 800AE080 8D820000 */  lw    $v0, ($t4)
/* 0AEC84 800AE084 AFAF0068 */  sw    $t7, 0x68($sp)
/* 0AEC88 800AE088 AC580000 */  sw    $t8, ($v0)
/* 0AEC8C 800AE08C A4480004 */  sh    $t0, 4($v0)
/* 0AEC90 800AE090 A44A0006 */  sh    $t2, 6($v0)
/* 0AEC94 800AE094 A4510008 */  sh    $s1, 8($v0)
/* 0AEC98 800AE098 A44A000A */  sh    $t2, 0xa($v0)
/* 0AEC9C 800AE09C A451000C */  sh    $s1, 0xc($v0)
/* 0AECA0 800AE0A0 A452000E */  sh    $s2, 0xe($v0)
/* 0AECA4 800AE0A4 AC4D0010 */  sw    $t5, 0x10($v0)
/* 0AECA8 800AE0A8 A4510014 */  sh    $s1, 0x14($v0)
/* 0AECAC 800AE0AC A4520016 */  sh    $s2, 0x16($v0)
/* 0AECB0 800AE0B0 A4480018 */  sh    $t0, 0x18($v0)
/* 0AECB4 800AE0B4 A452001A */  sh    $s2, 0x1a($v0)
/* 0AECB8 800AE0B8 A448001C */  sh    $t0, 0x1c($v0)
/* 0AECBC 800AE0BC A44A001E */  sh    $t2, 0x1e($v0)
/* 0AECC0 800AE0C0 92190010 */  lbu   $t9, 0x10($s0)
/* 0AECC4 800AE0C4 920F0011 */  lbu   $t7, 0x11($s0)
/* 0AECC8 800AE0C8 00197600 */  sll   $t6, $t9, 0x18
/* 0AECCC 800AE0CC 92190012 */  lbu   $t9, 0x12($s0)
/* 0AECD0 800AE0D0 000FC400 */  sll   $t8, $t7, 0x10
/* 0AECD4 800AE0D4 01D86825 */  or    $t5, $t6, $t8
/* 0AECD8 800AE0D8 00197A00 */  sll   $t7, $t9, 8
/* 0AECDC 800AE0DC 92180013 */  lbu   $t8, 0x13($s0)
/* 0AECE0 800AE0E0 01AF7025 */  or    $t6, $t5, $t7
/* 0AECE4 800AE0E4 920D0014 */  lbu   $t5, 0x14($s0)
/* 0AECE8 800AE0E8 0018CE00 */  sll   $t9, $t8, 0x18
/* 0AECEC 800AE0EC 92180015 */  lbu   $t8, 0x15($s0)
/* 0AECF0 800AE0F0 000D7C00 */  sll   $t7, $t5, 0x10
/* 0AECF4 800AE0F4 01C33025 */  or    $a2, $t6, $v1
/* 0AECF8 800AE0F8 032F7025 */  or    $t6, $t9, $t7
/* 0AECFC 800AE0FC 24420020 */  addiu $v0, $v0, 0x20
/* 0AED00 800AE100 00186A00 */  sll   $t5, $t8, 8
/* 0AED04 800AE104 01CD3825 */  or    $a3, $t6, $t5
/* 0AED08 800AE108 0C01FD65 */  jal   func_8007F594
/* 0AED0C 800AE10C AFA20064 */   sw    $v0, 0x64($sp)
/* 0AED10 800AE110 8FA30068 */  lw    $v1, 0x68($sp)
/* 0AED14 800AE114 3C010700 */  lui   $at, 0x700
/* 0AED18 800AE118 246F0008 */  addiu $t7, $v1, 8
/* 0AED1C 800AE11C AFAF0068 */  sw    $t7, 0x68($sp)
/* 0AED20 800AE120 8664000A */  lh    $a0, 0xa($s3)
/* 0AED24 800AE124 8FA20064 */  lw    $v0, 0x64($sp)
/* 0AED28 800AE128 309800FF */  andi  $t8, $a0, 0xff
/* 0AED2C 800AE12C 00187400 */  sll   $t6, $t8, 0x10
/* 0AED30 800AE130 0004C8C0 */  sll   $t9, $a0, 3
/* 0AED34 800AE134 332FFFFF */  andi  $t7, $t9, 0xffff
/* 0AED38 800AE138 01C16825 */  or    $t5, $t6, $at
/* 0AED3C 800AE13C 01AFC025 */  or    $t8, $t5, $t7
/* 0AED40 800AE140 AC780000 */  sw    $t8, ($v1)
/* 0AED44 800AE144 8E6E000C */  lw    $t6, 0xc($s3)
/* 0AED48 800AE148 3C088000 */  lui   $t0, 0x8000
/* 0AED4C 800AE14C 3C09800E */  lui   $t1, %hi(D_800E2C90) # $t1, 0x800e
/* 0AED50 800AE150 01C8C821 */  addu  $t9, $t6, $t0
/* 0AED54 800AE154 25292C90 */  addiu $t1, %lo(D_800E2C90) # addiu $t1, $t1, 0x2c90
/* 0AED58 800AE158 AC790004 */  sw    $t9, 4($v1)
/* 0AED5C 800AE15C 8D380000 */  lw    $t8, ($t1)
/* 0AED60 800AE160 240A000A */  li    $t2, 10
/* 0AED64 800AE164 030A0019 */  multu $t8, $t2
/* 0AED68 800AE168 8FA50068 */  lw    $a1, 0x68($sp)
/* 0AED6C 800AE16C 3C0B800E */  lui   $t3, %hi(D_800E2AAC) # $t3, 0x800e
/* 0AED70 800AE170 256B2AAC */  addiu $t3, %lo(D_800E2AAC) # addiu $t3, $t3, 0x2aac
/* 0AED74 800AE174 24AF0008 */  addiu $t7, $a1, 8
/* 0AED78 800AE178 AFAF0068 */  sw    $t7, 0x68($sp)
/* 0AED7C 800AE17C 3C010400 */  lui   $at, 0x400
/* 0AED80 800AE180 3C0C8012 */  lui   $t4, %hi(gCurrWeatherTriList) # $t4, 0x8012
/* 0AED84 800AE184 258C7C18 */  addiu $t4, %lo(gCurrWeatherTriList) # addiu $t4, $t4, 0x7c18
/* 0AED88 800AE188 00007012 */  mflo  $t6
/* 0AED8C 800AE18C 016EC821 */  addu  $t9, $t3, $t6
/* 0AED90 800AE190 03286821 */  addu  $t5, $t9, $t0
/* 0AED94 800AE194 31AF0006 */  andi  $t7, $t5, 6
/* 0AED98 800AE198 35F80018 */  ori   $t8, $t7, 0x18
/* 0AED9C 800AE19C 330E00FF */  andi  $t6, $t8, 0xff
/* 0AEDA0 800AE1A0 000ECC00 */  sll   $t9, $t6, 0x10
/* 0AEDA4 800AE1A4 03216825 */  or    $t5, $t9, $at
/* 0AEDA8 800AE1A8 35AF0050 */  ori   $t7, $t5, 0x50
/* 0AEDAC 800AE1AC ACAF0000 */  sw    $t7, ($a1)
/* 0AEDB0 800AE1B0 8D380000 */  lw    $t8, ($t1)
/* 0AEDB4 800AE1B4 3C018012 */  lui   $at, %hi(gCurrWeatherDisplayList) # $at, 0x8012
/* 0AEDB8 800AE1B8 030A0019 */  multu $t8, $t2
/* 0AEDBC 800AE1BC 00007012 */  mflo  $t6
/* 0AEDC0 800AE1C0 016EC821 */  addu  $t9, $t3, $t6
/* 0AEDC4 800AE1C4 03286821 */  addu  $t5, $t9, $t0
/* 0AEDC8 800AE1C8 ACAD0004 */  sw    $t5, 4($a1)
/* 0AEDCC 800AE1CC 8FAF0068 */  lw    $t7, 0x68($sp)
/* 0AEDD0 800AE1D0 3C0E0511 */  lui   $t6, (0x05110020 >> 16) # lui $t6, 0x511
/* 0AEDD4 800AE1D4 25F80008 */  addiu $t8, $t7, 8
/* 0AEDD8 800AE1D8 AFB80068 */  sw    $t8, 0x68($sp)
/* 0AEDDC 800AE1DC 35CE0020 */  ori   $t6, (0x05110020 & 0xFFFF) # ori $t6, $t6, 0x20
/* 0AEDE0 800AE1E0 ADEE0000 */  sw    $t6, ($t7)
/* 0AEDE4 800AE1E4 8D990000 */  lw    $t9, ($t4)
/* 0AEDE8 800AE1E8 3C0EE700 */  lui   $t6, 0xe700
/* 0AEDEC 800AE1EC 03286821 */  addu  $t5, $t9, $t0
/* 0AEDF0 800AE1F0 ADED0004 */  sw    $t5, 4($t7)
/* 0AEDF4 800AE1F4 8FAF0068 */  lw    $t7, 0x68($sp)
/* 0AEDF8 800AE1F8 00000000 */  nop   
/* 0AEDFC 800AE1FC 25F80008 */  addiu $t8, $t7, 8
/* 0AEE00 800AE200 AFB80068 */  sw    $t8, 0x68($sp)
/* 0AEE04 800AE204 ADE00004 */  sw    $zero, 4($t7)
/* 0AEE08 800AE208 ADEE0000 */  sw    $t6, ($t7)
/* 0AEE0C 800AE20C 8D390000 */  lw    $t9, ($t1)
/* 0AEE10 800AE210 8FB80068 */  lw    $t8, 0x68($sp)
/* 0AEE14 800AE214 272D0004 */  addiu $t5, $t9, 4
/* 0AEE18 800AE218 31AF000F */  andi  $t7, $t5, 0xf
/* 0AEE1C 800AE21C AD2F0000 */  sw    $t7, ($t1)
/* 0AEE20 800AE220 AC387C0C */  sw    $t8, %lo(gCurrWeatherDisplayList)($at)
/* 0AEE24 800AE224 AD820000 */  sw    $v0, ($t4)
.L800AE228:
/* 0AEE28 800AE228 8FBF0044 */  lw    $ra, 0x44($sp)
.L800AE22C:
/* 0AEE2C 800AE22C C7B50010 */  lwc1  $f21, 0x10($sp)
/* 0AEE30 800AE230 C7B40014 */  lwc1  $f20, 0x14($sp)
/* 0AEE34 800AE234 C7B70018 */  lwc1  $f23, 0x18($sp)
/* 0AEE38 800AE238 C7B6001C */  lwc1  $f22, 0x1c($sp)
/* 0AEE3C 800AE23C C7B90020 */  lwc1  $f25, 0x20($sp)
/* 0AEE40 800AE240 C7B80024 */  lwc1  $f24, 0x24($sp)
/* 0AEE44 800AE244 C7BB0028 */  lwc1  $f27, 0x28($sp)
/* 0AEE48 800AE248 C7BA002C */  lwc1  $f26, 0x2c($sp)
/* 0AEE4C 800AE24C 8FB00034 */  lw    $s0, 0x34($sp)
/* 0AEE50 800AE250 8FB10038 */  lw    $s1, 0x38($sp)
/* 0AEE54 800AE254 8FB2003C */  lw    $s2, 0x3c($sp)
/* 0AEE58 800AE258 8FB30040 */  lw    $s3, 0x40($sp)
/* 0AEE5C 800AE25C 03E00008 */  jr    $ra
/* 0AEE60 800AE260 27BD00A0 */   addiu $sp, $sp, 0xa0

/* 0AEE64 800AE264 00000000 */  nop   
/* 0AEE68 800AE268 00000000 */  nop   
/* 0AEE6C 800AE26C 00000000 */  nop   

