glabel calc_env_mapping_for_object
/* 01E954 8001DD54 27BDFEE8 */  addiu $sp, $sp, -0x118
/* 01E958 8001DD58 AFBF003C */  sw    $ra, 0x3c($sp)
/* 01E95C 8001DD5C AFBE0038 */  sw    $fp, 0x38($sp)
/* 01E960 8001DD60 AFB70034 */  sw    $s7, 0x34($sp)
/* 01E964 8001DD64 AFB60030 */  sw    $s6, 0x30($sp)
/* 01E968 8001DD68 AFB5002C */  sw    $s5, 0x2c($sp)
/* 01E96C 8001DD6C AFB40028 */  sw    $s4, 0x28($sp)
/* 01E970 8001DD70 AFB30024 */  sw    $s3, 0x24($sp)
/* 01E974 8001DD74 AFB20020 */  sw    $s2, 0x20($sp)
/* 01E978 8001DD78 AFB1001C */  sw    $s1, 0x1c($sp)
/* 01E97C 8001DD7C AFB00018 */  sw    $s0, 0x18($sp)
/* 01E980 8001DD80 AFA5011C */  sw    $a1, 0x11c($sp)
/* 01E984 8001DD84 AFA60120 */  sw    $a2, 0x120($sp)
/* 01E988 8001DD88 AFA70124 */  sw    $a3, 0x124($sp)
/* 01E98C 8001DD8C 8C890008 */  lw    $t1, 8($a0)
/* 01E990 8001DD90 44800000 */  mtc1  $zero, $f0
/* 01E994 8001DD94 AFA90078 */  sw    $t1, 0x78($sp)
/* 01E998 8001DD98 8C8A0040 */  lw    $t2, 0x40($a0)
/* 01E99C 8001DD9C 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 01E9A0 8001DDA0 44812000 */  mtc1  $at, $f4
/* 01E9A4 8001DDA4 27B10098 */  addiu $s1, $sp, 0x98
/* 01E9A8 8001DDA8 0080F025 */  move  $fp, $a0
/* 01E9AC 8001DDAC 00A07025 */  move  $t6, $a1
/* 01E9B0 8001DDB0 0000A025 */  move  $s4, $zero
/* 01E9B4 8001DDB4 A7AE0084 */  sh    $t6, 0x84($sp)
/* 01E9B8 8001DDB8 A7A60082 */  sh    $a2, 0x82($sp)
/* 01E9BC 8001DDBC A7A70080 */  sh    $a3, 0x80($sp)
/* 01E9C0 8001DDC0 27A50080 */  addiu $a1, $sp, 0x80
/* 01E9C4 8001DDC4 02202025 */  move  $a0, $s1
/* 01E9C8 8001DDC8 E7A0008C */  swc1  $f0, 0x8c($sp)
/* 01E9CC 8001DDCC E7A00090 */  swc1  $f0, 0x90($sp)
/* 01E9D0 8001DDD0 E7A00094 */  swc1  $f0, 0x94($sp)
/* 01E9D4 8001DDD4 AFAA0074 */  sw    $t2, 0x74($sp)
/* 01E9D8 8001DDD8 0C01BF0C */  jal   object_transform_to_matrix
/* 01E9DC 8001DDDC E7A40088 */   swc1  $f4, 0x88($sp)
/* 01E9E0 8001DDE0 02202025 */  move  $a0, $s1
/* 01E9E4 8001DDE4 0C01BD78 */  jal   f32_matrix_to_s32_matrix
/* 01E9E8 8001DDE8 27A500D8 */   addiu $a1, $sp, 0xd8
/* 01E9EC 8001DDEC A7A00062 */  sh    $zero, 0x62($sp)
/* 01E9F0 8001DDF0 87C20028 */  lh    $v0, 0x28($fp)
/* 01E9F4 8001DDF4 3C138012 */  lui   $s3, %hi(D_8011AF68) # $s3, 0x8012
/* 01E9F8 8001DDF8 184000C4 */  blez  $v0, .L8001E10C
/* 01E9FC 8001DDFC 2673AF68 */   addiu $s3, %lo(D_8011AF68) # addiu $s3, $s3, -0x5098
/* 01EA00 8001DE00 3C118012 */  lui   $s1, %hi(gEnvmapPos) # $s1, 0x8012
/* 01EA04 8001DE04 8FC60038 */  lw    $a2, 0x38($fp)
/* 01EA08 8001DE08 2631AFE8 */  addiu $s1, %lo(gEnvmapPos) # addiu $s1, $s1, -0x5018
.L8001DE0C:
/* 01EA0C 8001DE0C 87B70062 */  lh    $s7, 0x62($sp)
/* 01EA10 8001DE10 3C010002 */  lui   $at, 2
/* 01EA14 8001DE14 00175880 */  sll   $t3, $s7, 2
/* 01EA18 8001DE18 01775823 */  subu  $t3, $t3, $s7
/* 01EA1C 8001DE1C 000BB880 */  sll   $s7, $t3, 2
/* 01EA20 8001DE20 00D72821 */  addu  $a1, $a2, $s7
/* 01EA24 8001DE24 8CA30008 */  lw    $v1, 8($a1)
/* 01EA28 8001DE28 00000000 */  nop   
/* 01EA2C 8001DE2C 306C8000 */  andi  $t4, $v1, 0x8000
/* 01EA30 8001DE30 118000A3 */  beqz  $t4, .L8001E0C0
/* 01EA34 8001DE34 00616824 */   and   $t5, $v1, $at
/* 01EA38 8001DE38 35AE8000 */  ori   $t6, $t5, 0x8000
/* 01EA3C 8001DE3C 39CF8000 */  xori  $t7, $t6, 0x8000
/* 01EA40 8001DE40 AFAF0070 */  sw    $t7, 0x70($sp)
/* 01EA44 8001DE44 90B90000 */  lbu   $t9, ($a1)
/* 01EA48 8001DE48 8FD80000 */  lw    $t8, ($fp)
/* 01EA4C 8001DE4C 001940C0 */  sll   $t0, $t9, 3
/* 01EA50 8001DE50 03084821 */  addu  $t1, $t8, $t0
/* 01EA54 8001DE54 8D240000 */  lw    $a0, ($t1)
/* 01EA58 8001DE58 24070020 */  li    $a3, 32
/* 01EA5C 8001DE5C 90820000 */  lbu   $v0, ($a0)
/* 01EA60 8001DE60 00009025 */  move  $s2, $zero
/* 01EA64 8001DE64 10470014 */  beq   $v0, $a3, .L8001DEB8
/* 01EA68 8001DE68 24190006 */   li    $t9, 6
/* 01EA6C 8001DE6C 24010040 */  li    $at, 64
/* 01EA70 8001DE70 1041000D */  beq   $v0, $at, .L8001DEA8
/* 01EA74 8001DE74 240E0005 */   li    $t6, 5
/* 01EA78 8001DE78 24010080 */  li    $at, 128
/* 01EA7C 8001DE7C 10410006 */  beq   $v0, $at, .L8001DE98
/* 01EA80 8001DE80 240C0004 */   li    $t4, 4
/* 01EA84 8001DE84 240A0007 */  li    $t2, 7
/* 01EA88 8001DE88 240B01FF */  li    $t3, 511
/* 01EA8C 8001DE8C A7AB0068 */  sh    $t3, 0x68($sp)
/* 01EA90 8001DE90 1000000C */  b     .L8001DEC4
/* 01EA94 8001DE94 A7AA006A */   sh    $t2, 0x6a($sp)
.L8001DE98:
/* 01EA98 8001DE98 240D0FFF */  li    $t5, 4095
/* 01EA9C 8001DE9C A7AD0068 */  sh    $t5, 0x68($sp)
/* 01EAA0 8001DEA0 10000008 */  b     .L8001DEC4
/* 01EAA4 8001DEA4 A7AC006A */   sh    $t4, 0x6a($sp)
.L8001DEA8:
/* 01EAA8 8001DEA8 240F07FF */  li    $t7, 2047
/* 01EAAC 8001DEAC A7AF0068 */  sh    $t7, 0x68($sp)
/* 01EAB0 8001DEB0 10000004 */  b     .L8001DEC4
/* 01EAB4 8001DEB4 A7AE006A */   sh    $t6, 0x6a($sp)
.L8001DEB8:
/* 01EAB8 8001DEB8 241803FF */  li    $t8, 1023
/* 01EABC 8001DEBC A7B80068 */  sh    $t8, 0x68($sp)
/* 01EAC0 8001DEC0 A7B9006A */  sh    $t9, 0x6a($sp)
.L8001DEC4:
/* 01EAC4 8001DEC4 90820001 */  lbu   $v0, 1($a0)
/* 01EAC8 8001DEC8 24150006 */  li    $s5, 6
/* 01EACC 8001DECC 1047000E */  beq   $v0, $a3, .L8001DF08
/* 01EAD0 8001DED0 241603FF */   li    $s6, 1023
/* 01EAD4 8001DED4 24010040 */  li    $at, 64
/* 01EAD8 8001DED8 10410009 */  beq   $v0, $at, .L8001DF00
/* 01EADC 8001DEDC 24150005 */   li    $s5, 5
/* 01EAE0 8001DEE0 24010080 */  li    $at, 128
/* 01EAE4 8001DEE4 10410004 */  beq   $v0, $at, .L8001DEF8
/* 01EAE8 8001DEE8 24150004 */   li    $s5, 4
/* 01EAEC 8001DEEC 24150007 */  li    $s5, 7
/* 01EAF0 8001DEF0 10000005 */  b     .L8001DF08
/* 01EAF4 8001DEF4 241601FF */   li    $s6, 511
.L8001DEF8:
/* 01EAF8 8001DEF8 10000003 */  b     .L8001DF08
/* 01EAFC 8001DEFC 24160FFF */   li    $s6, 4095
.L8001DF00:
/* 01EB00 8001DF00 10000001 */  b     .L8001DF08
/* 01EB04 8001DF04 241607FF */   li    $s6, 2047
.L8001DF08:
/* 01EB08 8001DF08 84B00002 */  lh    $s0, 2($a1)
/* 01EB0C 8001DF0C 84A8000E */  lh    $t0, 0xe($a1)
/* 01EB10 8001DF10 00000000 */  nop   
/* 01EB14 8001DF14 0208082A */  slt   $at, $s0, $t0
/* 01EB18 8001DF18 10200040 */  beqz  $at, .L8001E01C
.L8001DF1C:
/* 01EB1C 8001DF1C 00145080 */   sll   $t2, $s4, 2
/* 01EB20 8001DF20 8FA90074 */  lw    $t1, 0x74($sp)
/* 01EB24 8001DF24 01545023 */  subu  $t2, $t2, $s4
/* 01EB28 8001DF28 000A5040 */  sll   $t2, $t2, 1
/* 01EB2C 8001DF2C 012A1021 */  addu  $v0, $t1, $t2
/* 01EB30 8001DF30 844B0000 */  lh    $t3, ($v0)
/* 01EB34 8001DF34 26940001 */  addiu $s4, $s4, 1
/* 01EB38 8001DF38 A62B0006 */  sh    $t3, 6($s1)
/* 01EB3C 8001DF3C 844C0002 */  lh    $t4, 2($v0)
/* 01EB40 8001DF40 00147400 */  sll   $t6, $s4, 0x10
/* 01EB44 8001DF44 A62C0008 */  sh    $t4, 8($s1)
/* 01EB48 8001DF48 844D0004 */  lh    $t5, 4($v0)
/* 01EB4C 8001DF4C 3C058012 */  lui   $a1, %hi(D_8011AFEE) # $a1, 0x8012
/* 01EB50 8001DF50 000EA403 */  sra   $s4, $t6, 0x10
/* 01EB54 8001DF54 24A5AFEE */  addiu $a1, %lo(D_8011AFEE) # addiu $a1, $a1, -0x5012
/* 01EB58 8001DF58 27A400D8 */  addiu $a0, $sp, 0xd8
/* 01EB5C 8001DF5C 0C01BED8 */  jal   s16_vec3_mult_by_s32_matrix
/* 01EB60 8001DF60 A62D000A */   sh    $t5, 0xa($s1)
/* 01EB64 8001DF64 8FB90070 */  lw    $t9, 0x70($sp)
/* 01EB68 8001DF68 02202025 */  move  $a0, $s1
/* 01EB6C 8001DF6C 17200003 */  bnez  $t9, .L8001DF7C
/* 01EB70 8001DF70 3C058012 */   lui   $a1, %hi(D_8011AFEE) # $a1, 0x8012
/* 01EB74 8001DF74 0C01BE6E */  jal   s16_matrix_rotate
/* 01EB78 8001DF78 24A5AFEE */   addiu $a1, %lo(D_8011AFEE) # addiu $a1, $a1, -0x5012
.L8001DF7C:
/* 01EB7C 8001DF7C 86220006 */  lh    $v0, 6($s1)
/* 01EB80 8001DF80 86230008 */  lh    $v1, 8($s1)
/* 01EB84 8001DF84 18400004 */  blez  $v0, .L8001DF98
/* 01EB88 8001DF88 34078000 */   li    $a3, 32768
/* 01EB8C 8001DF8C 2442FFFF */  addiu $v0, $v0, -1
/* 01EB90 8001DF90 0002C400 */  sll   $t8, $v0, 0x10
/* 01EB94 8001DF94 00181403 */  sra   $v0, $t8, 0x10
.L8001DF98:
/* 01EB98 8001DF98 18600004 */  blez  $v1, .L8001DFAC
/* 01EB9C 8001DF9C 00025880 */   sll   $t3, $v0, 2
/* 01EBA0 8001DFA0 2463FFFF */  addiu $v1, $v1, -1
/* 01EBA4 8001DFA4 00034C00 */  sll   $t1, $v1, 0x10
/* 01EBA8 8001DFA8 00091C03 */  sra   $v1, $t1, 0x10
.L8001DFAC:
/* 01EBAC 8001DFAC 01671021 */  addu  $v0, $t3, $a3
/* 01EBB0 8001DFB0 00037080 */  sll   $t6, $v1, 2
/* 01EBB4 8001DFB4 87A8006A */  lh    $t0, 0x6a($sp)
/* 01EBB8 8001DFB8 00026400 */  sll   $t4, $v0, 0x10
/* 01EBBC 8001DFBC 01C71821 */  addu  $v1, $t6, $a3
/* 01EBC0 8001DFC0 000C6C03 */  sra   $t5, $t4, 0x10
/* 01EBC4 8001DFC4 00037C00 */  sll   $t7, $v1, 0x10
/* 01EBC8 8001DFC8 87AA0068 */  lh    $t2, 0x68($sp)
/* 01EBCC 8001DFCC 000FCC03 */  sra   $t9, $t7, 0x10
/* 01EBD0 8001DFD0 0012C080 */  sll   $t8, $s2, 2
/* 01EBD4 8001DFD4 010D4807 */  srav  $t1, $t5, $t0
/* 01EBD8 8001DFD8 02782021 */  addu  $a0, $s3, $t8
/* 01EBDC 8001DFDC 02B96007 */  srav  $t4, $t9, $s5
/* 01EBE0 8001DFE0 01966824 */  and   $t5, $t4, $s6
/* 01EBE4 8001DFE4 012A5824 */  and   $t3, $t1, $t2
/* 01EBE8 8001DFE8 A48B0000 */  sh    $t3, ($a0)
/* 01EBEC 8001DFEC A48D0002 */  sh    $t5, 2($a0)
/* 01EBF0 8001DFF0 8FC60038 */  lw    $a2, 0x38($fp)
/* 01EBF4 8001DFF4 26100001 */  addiu $s0, $s0, 1
/* 01EBF8 8001DFF8 00D72821 */  addu  $a1, $a2, $s7
/* 01EBFC 8001DFFC 84A8000E */  lh    $t0, 0xe($a1)
/* 01EC00 8001E000 00107400 */  sll   $t6, $s0, 0x10
/* 01EC04 8001E004 000E8403 */  sra   $s0, $t6, 0x10
/* 01EC08 8001E008 26520001 */  addiu $s2, $s2, 1
/* 01EC0C 8001E00C 0012CC00 */  sll   $t9, $s2, 0x10
/* 01EC10 8001E010 0208082A */  slt   $at, $s0, $t0
/* 01EC14 8001E014 1420FFC1 */  bnez  $at, .L8001DF1C
/* 01EC18 8001E018 00199403 */   sra   $s2, $t9, 0x10
.L8001E01C:
/* 01EC1C 8001E01C 84B00004 */  lh    $s0, 4($a1)
/* 01EC20 8001E020 84A90010 */  lh    $t1, 0x10($a1)
/* 01EC24 8001E024 8FA70078 */  lw    $a3, 0x78($sp)
/* 01EC28 8001E028 0209082A */  slt   $at, $s0, $t1
/* 01EC2C 8001E02C 10200021 */  beqz  $at, .L8001E0B4
/* 01EC30 8001E030 00105100 */   sll   $t2, $s0, 4
.L8001E034:
/* 01EC34 8001E034 00EA1021 */  addu  $v0, $a3, $t2
/* 01EC38 8001E038 904B0001 */  lbu   $t3, 1($v0)
/* 01EC3C 8001E03C 904F0002 */  lbu   $t7, 2($v0)
/* 01EC40 8001E040 000B6080 */  sll   $t4, $t3, 2
/* 01EC44 8001E044 026C1821 */  addu  $v1, $s3, $t4
/* 01EC48 8001E048 846D0000 */  lh    $t5, ($v1)
/* 01EC4C 8001E04C 000FC880 */  sll   $t9, $t7, 2
/* 01EC50 8001E050 A44D0004 */  sh    $t5, 4($v0)
/* 01EC54 8001E054 846E0002 */  lh    $t6, 2($v1)
/* 01EC58 8001E058 02792021 */  addu  $a0, $s3, $t9
/* 01EC5C 8001E05C A44E0006 */  sh    $t6, 6($v0)
/* 01EC60 8001E060 84980000 */  lh    $t8, ($a0)
/* 01EC64 8001E064 90490003 */  lbu   $t1, 3($v0)
/* 01EC68 8001E068 A4580008 */  sh    $t8, 8($v0)
/* 01EC6C 8001E06C 84880002 */  lh    $t0, 2($a0)
/* 01EC70 8001E070 00095080 */  sll   $t2, $t1, 2
/* 01EC74 8001E074 026A2821 */  addu  $a1, $s3, $t2
/* 01EC78 8001E078 A448000A */  sh    $t0, 0xa($v0)
/* 01EC7C 8001E07C 84AB0000 */  lh    $t3, ($a1)
/* 01EC80 8001E080 26100001 */  addiu $s0, $s0, 1
/* 01EC84 8001E084 A44B000C */  sh    $t3, 0xc($v0)
/* 01EC88 8001E088 84AC0002 */  lh    $t4, 2($a1)
/* 01EC8C 8001E08C 00106C00 */  sll   $t5, $s0, 0x10
/* 01EC90 8001E090 A44C000E */  sh    $t4, 0xe($v0)
/* 01EC94 8001E094 8FC60038 */  lw    $a2, 0x38($fp)
/* 01EC98 8001E098 000D8403 */  sra   $s0, $t5, 0x10
/* 01EC9C 8001E09C 00D77821 */  addu  $t7, $a2, $s7
/* 01ECA0 8001E0A0 85F90010 */  lh    $t9, 0x10($t7)
/* 01ECA4 8001E0A4 00000000 */  nop   
/* 01ECA8 8001E0A8 0219082A */  slt   $at, $s0, $t9
/* 01ECAC 8001E0AC 1420FFE1 */  bnez  $at, .L8001E034
/* 01ECB0 8001E0B0 00105100 */   sll   $t2, $s0, 4
.L8001E0B4:
/* 01ECB4 8001E0B4 87C20028 */  lh    $v0, 0x28($fp)
/* 01ECB8 8001E0B8 1000000D */  b     .L8001E0F0
/* 01ECBC 8001E0BC 87AD0062 */   lh    $t5, 0x62($sp)
.L8001E0C0:
/* 01ECC0 8001E0C0 90B80006 */  lbu   $t8, 6($a1)
/* 01ECC4 8001E0C4 00000000 */  nop   
/* 01ECC8 8001E0C8 2B0100FF */  slti  $at, $t8, 0xff
/* 01ECCC 8001E0CC 10200008 */  beqz  $at, .L8001E0F0
/* 01ECD0 8001E0D0 87AD0062 */   lh    $t5, 0x62($sp)
/* 01ECD4 8001E0D4 84A8000E */  lh    $t0, 0xe($a1)
/* 01ECD8 8001E0D8 84AA0002 */  lh    $t2, 2($a1)
/* 01ECDC 8001E0DC 02884821 */  addu  $t1, $s4, $t0
/* 01ECE0 8001E0E0 012AA023 */  subu  $s4, $t1, $t2
/* 01ECE4 8001E0E4 00145C00 */  sll   $t3, $s4, 0x10
/* 01ECE8 8001E0E8 000BA403 */  sra   $s4, $t3, 0x10
/* 01ECEC 8001E0EC 87AD0062 */  lh    $t5, 0x62($sp)
.L8001E0F0:
/* 01ECF0 8001E0F0 00000000 */  nop   
/* 01ECF4 8001E0F4 25AE0001 */  addiu $t6, $t5, 1
/* 01ECF8 8001E0F8 000E7C00 */  sll   $t7, $t6, 0x10
/* 01ECFC 8001E0FC 000FCC03 */  sra   $t9, $t7, 0x10
/* 01ED00 8001E100 0322082A */  slt   $at, $t9, $v0
/* 01ED04 8001E104 1420FF41 */  bnez  $at, .L8001DE0C
/* 01ED08 8001E108 A7AE0062 */   sh    $t6, 0x62($sp)
.L8001E10C:
/* 01ED0C 8001E10C 8FBF003C */  lw    $ra, 0x3c($sp)
/* 01ED10 8001E110 8FB00018 */  lw    $s0, 0x18($sp)
/* 01ED14 8001E114 8FB1001C */  lw    $s1, 0x1c($sp)
/* 01ED18 8001E118 8FB20020 */  lw    $s2, 0x20($sp)
/* 01ED1C 8001E11C 8FB30024 */  lw    $s3, 0x24($sp)
/* 01ED20 8001E120 8FB40028 */  lw    $s4, 0x28($sp)
/* 01ED24 8001E124 8FB5002C */  lw    $s5, 0x2c($sp)
/* 01ED28 8001E128 8FB60030 */  lw    $s6, 0x30($sp)
/* 01ED2C 8001E12C 8FB70034 */  lw    $s7, 0x34($sp)
/* 01ED30 8001E130 8FBE0038 */  lw    $fp, 0x38($sp)
/* 01ED34 8001E134 03E00008 */  jr    $ra
/* 01ED38 8001E138 27BD0118 */   addiu $sp, $sp, 0x118
