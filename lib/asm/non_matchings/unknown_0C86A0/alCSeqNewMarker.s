glabel alCSeqNewMarker
/* 0C8D10 800C8110 27BDFEB0 */  addiu $sp, $sp, -0x150
/* 0C8D14 800C8114 AFB30020 */  sw    $s3, 0x20($sp)
/* 0C8D18 800C8118 AFB10018 */  sw    $s1, 0x18($sp)
/* 0C8D1C 800C811C 00A08825 */  move  $s1, $a1
/* 0C8D20 800C8120 27B30048 */  addiu $s3, $sp, 0x48
/* 0C8D24 800C8124 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0C8D28 800C8128 AFB50028 */  sw    $s5, 0x28($sp)
/* 0C8D2C 800C812C AFB40024 */  sw    $s4, 0x24($sp)
/* 0C8D30 800C8130 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0C8D34 800C8134 AFB00014 */  sw    $s0, 0x14($sp)
/* 0C8D38 800C8138 00803825 */  move  $a3, $a0
/* 0C8D3C 800C813C 00C09025 */  move  $s2, $a2
/* 0C8D40 800C8140 8CE50000 */  lw    $a1, ($a3)
/* 0C8D44 800C8144 0C031FFF */  jal   alCSeqNew
/* 0C8D48 800C8148 02602025 */   move  $a0, $s3
/* 0C8D4C 800C814C 24150004 */  li    $s5, 4
/* 0C8D50 800C8150 27B40140 */  addiu $s4, $sp, 0x140
/* 0C8D54 800C8154 27B00058 */  addiu $s0, $sp, 0x58
/* 0C8D58 800C8158 8FAE004C */  lw    $t6, 0x4c($sp)
.L800C815C:
/* 0C8D5C 800C815C 27A40048 */  addiu $a0, $sp, 0x48
/* 0C8D60 800C8160 00801825 */  move  $v1, $a0
/* 0C8D64 800C8164 AE2E0000 */  sw    $t6, ($s1)
/* 0C8D68 800C8168 8FAF0054 */  lw    $t7, 0x54($sp)
/* 0C8D6C 800C816C 02201025 */  move  $v0, $s1
/* 0C8D70 800C8170 02202825 */  move  $a1, $s1
/* 0C8D74 800C8174 AE2F0004 */  sw    $t7, 4($s1)
/* 0C8D78 800C8178 8FB80058 */  lw    $t8, 0x58($sp)
/* 0C8D7C 800C817C AE380008 */  sw    $t8, 8($s1)
.L800C8180:
/* 0C8D80 800C8180 8C680018 */  lw    $t0, 0x18($v1)
/* 0C8D84 800C8184 24840004 */  addiu $a0, $a0, 4
/* 0C8D88 800C8188 24420010 */  addiu $v0, $v0, 0x10
/* 0C8D8C 800C818C AC48FFFC */  sw    $t0, -4($v0)
/* 0C8D90 800C8190 8C690058 */  lw    $t1, 0x58($v1)
/* 0C8D94 800C8194 24630010 */  addiu $v1, $v1, 0x10
/* 0C8D98 800C8198 24A50004 */  addiu $a1, $a1, 4
/* 0C8D9C 800C819C AC49003C */  sw    $t1, 0x3c($v0)
/* 0C8DA0 800C81A0 908A0094 */  lbu   $t2, 0x94($a0)
/* 0C8DA4 800C81A4 A0AA0088 */  sb    $t2, 0x88($a1)
/* 0C8DA8 800C81A8 908B00A4 */  lbu   $t3, 0xa4($a0)
/* 0C8DAC 800C81AC A0AB0098 */  sb    $t3, 0x98($a1)
/* 0C8DB0 800C81B0 8C6C00A8 */  lw    $t4, 0xa8($v1)
/* 0C8DB4 800C81B4 AC4C009C */  sw    $t4, 0x9c($v0)
/* 0C8DB8 800C81B8 8C6D000C */  lw    $t5, 0xc($v1)
/* 0C8DBC 800C81BC AC4D0000 */  sw    $t5, ($v0)
/* 0C8DC0 800C81C0 8C6E004C */  lw    $t6, 0x4c($v1)
/* 0C8DC4 800C81C4 AC4E0040 */  sw    $t6, 0x40($v0)
/* 0C8DC8 800C81C8 908F0095 */  lbu   $t7, 0x95($a0)
/* 0C8DCC 800C81CC A0AF0089 */  sb    $t7, 0x89($a1)
/* 0C8DD0 800C81D0 909800A5 */  lbu   $t8, 0xa5($a0)
/* 0C8DD4 800C81D4 A0B80099 */  sb    $t8, 0x99($a1)
/* 0C8DD8 800C81D8 8C7900AC */  lw    $t9, 0xac($v1)
/* 0C8DDC 800C81DC AC5900A0 */  sw    $t9, 0xa0($v0)
/* 0C8DE0 800C81E0 8C680010 */  lw    $t0, 0x10($v1)
/* 0C8DE4 800C81E4 AC480004 */  sw    $t0, 4($v0)
/* 0C8DE8 800C81E8 8C690050 */  lw    $t1, 0x50($v1)
/* 0C8DEC 800C81EC AC490044 */  sw    $t1, 0x44($v0)
/* 0C8DF0 800C81F0 908A0096 */  lbu   $t2, 0x96($a0)
/* 0C8DF4 800C81F4 A0AA008A */  sb    $t2, 0x8a($a1)
/* 0C8DF8 800C81F8 908B00A6 */  lbu   $t3, 0xa6($a0)
/* 0C8DFC 800C81FC A0AB009A */  sb    $t3, 0x9a($a1)
/* 0C8E00 800C8200 8C6C00B0 */  lw    $t4, 0xb0($v1)
/* 0C8E04 800C8204 AC4C00A4 */  sw    $t4, 0xa4($v0)
/* 0C8E08 800C8208 8C6D0014 */  lw    $t5, 0x14($v1)
/* 0C8E0C 800C820C AC4D0008 */  sw    $t5, 8($v0)
/* 0C8E10 800C8210 8C6E0054 */  lw    $t6, 0x54($v1)
/* 0C8E14 800C8214 AC4E0048 */  sw    $t6, 0x48($v0)
/* 0C8E18 800C8218 908F0097 */  lbu   $t7, 0x97($a0)
/* 0C8E1C 800C821C A0AF008B */  sb    $t7, 0x8b($a1)
/* 0C8E20 800C8220 909800A7 */  lbu   $t8, 0xa7($a0)
/* 0C8E24 800C8224 A0B8009B */  sb    $t8, 0x9b($a1)
/* 0C8E28 800C8228 8C7900B4 */  lw    $t9, 0xb4($v1)
/* 0C8E2C 800C822C 1490FFD4 */  bne   $a0, $s0, .L800C8180
/* 0C8E30 800C8230 AC5900A8 */   sw    $t9, 0xa8($v0)
/* 0C8E34 800C8234 02602025 */  move  $a0, $s3
/* 0C8E38 800C8238 0C031F41 */  jal   __alCSeqGetTrackEvent
/* 0C8E3C 800C823C 02802825 */   move  $a1, $s4
/* 0C8E40 800C8240 87A80140 */  lh    $t0, 0x140($sp)
/* 0C8E44 800C8244 8FA90054 */  lw    $t1, 0x54($sp)
/* 0C8E48 800C8248 11150003 */  beq   $t0, $s5, .L800C8258
/* 0C8E4C 800C824C 0132082B */   sltu  $at, $t1, $s2
/* 0C8E50 800C8250 5420FFC2 */  bnezl $at, .L800C815C
/* 0C8E54 800C8254 8FAE004C */   lw    $t6, 0x4c($sp)
.L800C8258:
/* 0C8E58 800C8258 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0C8E5C 800C825C 8FB00014 */  lw    $s0, 0x14($sp)
/* 0C8E60 800C8260 8FB10018 */  lw    $s1, 0x18($sp)
/* 0C8E64 800C8264 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0C8E68 800C8268 8FB30020 */  lw    $s3, 0x20($sp)
/* 0C8E6C 800C826C 8FB40024 */  lw    $s4, 0x24($sp)
/* 0C8E70 800C8270 8FB50028 */  lw    $s5, 0x28($sp)
/* 0C8E74 800C8274 03E00008 */  jr    $ra
/* 0C8E78 800C8278 27BD0150 */   addiu $sp, $sp, 0x150
