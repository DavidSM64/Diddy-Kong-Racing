glabel func_8000A184
/* 00AD84 8000A184 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 00AD88 8000A188 AFBE0048 */  sw    $fp, 0x48($sp)
/* 00AD8C 8000A18C AFB70044 */  sw    $s7, 0x44($sp)
/* 00AD90 8000A190 AFB60040 */  sw    $s6, 0x40($sp)
/* 00AD94 8000A194 AFB5003C */  sw    $s5, 0x3c($sp)
/* 00AD98 8000A198 AFB40038 */  sw    $s4, 0x38($sp)
/* 00AD9C 8000A19C AFB30034 */  sw    $s3, 0x34($sp)
/* 00ADA0 8000A1A0 3C168012 */  lui   $s6, %hi(D_80119C58) # $s6, 0x8012
/* 00ADA4 8000A1A4 3C178012 */  lui   $s7, %hi(D_80119C5C) # $s7, 0x8012
/* 00ADA8 8000A1A8 3C1E8012 */  lui   $fp, %hi(D_8011A6DC) # $fp, 0x8012
/* 00ADAC 8000A1AC 00809825 */  move  $s3, $a0
/* 00ADB0 8000A1B0 00A0A025 */  move  $s4, $a1
/* 00ADB4 8000A1B4 00C0A825 */  move  $s5, $a2
/* 00ADB8 8000A1B8 AFBF004C */  sw    $ra, 0x4c($sp)
/* 00ADBC 8000A1BC AFB20030 */  sw    $s2, 0x30($sp)
/* 00ADC0 8000A1C0 AFB1002C */  sw    $s1, 0x2c($sp)
/* 00ADC4 8000A1C4 AFB00028 */  sw    $s0, 0x28($sp)
/* 00ADC8 8000A1C8 27DEA6DC */  addiu $fp, %lo(D_8011A6DC) # addiu $fp, $fp, -0x5924
/* 00ADCC 8000A1CC 26F79C5C */  addiu $s7, %lo(D_80119C5C) # addiu $s7, $s7, -0x63a4
/* 00ADD0 8000A1D0 26D69C58 */  addiu $s6, %lo(D_80119C58) # addiu $s6, $s6, -0x63a8
.L8000A1D4:
/* 00ADD4 8000A1D4 8ECE016C */  lw    $t6, 0x16c($s6)
/* 00ADD8 8000A1D8 02C09025 */  move  $s2, $s6
/* 00ADDC 8000A1DC 11C00013 */  beqz  $t6, .L8000A22C
/* 00ADE0 8000A1E0 02E08825 */   move  $s1, $s7
/* 00ADE4 8000A1E4 82CF017C */  lb    $t7, 0x17c($s6)
/* 00ADE8 8000A1E8 00008025 */  move  $s0, $zero
/* 00ADEC 8000A1EC 19E0000F */  blez  $t7, .L8000A22C
.L8000A1F0:
/* 00ADF0 8000A1F0 241800FF */   li    $t8, 255
/* 00ADF4 8000A1F4 241900FF */  li    $t9, 255
/* 00ADF8 8000A1F8 AFB90014 */  sw    $t9, 0x14($sp)
/* 00ADFC 8000A1FC AFB80010 */  sw    $t8, 0x10($sp)
/* 00AE00 8000A200 02602025 */  move  $a0, $s3
/* 00AE04 8000A204 02802825 */  move  $a1, $s4
/* 00AE08 8000A208 02A03025 */  move  $a2, $s5
/* 00AE0C 8000A20C 02203825 */  move  $a3, $s1
/* 00AE10 8000A210 0C002905 */  jal   debug_render_spline
/* 00AE14 8000A214 AFA00018 */   sw    $zero, 0x18($sp)
/* 00AE18 8000A218 8248017C */  lb    $t0, 0x17c($s2)
/* 00AE1C 8000A21C 26100001 */  addiu $s0, $s0, 1
/* 00AE20 8000A220 0208082A */  slt   $at, $s0, $t0
/* 00AE24 8000A224 1420FFF2 */  bnez  $at, .L8000A1F0
/* 00AE28 8000A228 2631000C */   addiu $s1, $s1, 0xc
.L8000A22C:
/* 00AE2C 8000A22C 26F70180 */  addiu $s7, $s7, 0x180
/* 00AE30 8000A230 02FE082B */  sltu  $at, $s7, $fp
/* 00AE34 8000A234 1420FFE7 */  bnez  $at, .L8000A1D4
/* 00AE38 8000A238 26D60180 */   addiu $s6, $s6, 0x180
/* 00AE3C 8000A23C 3C168012 */  lui   $s6, %hi(D_8011A6D8) # $s6, 0x8012
/* 00AE40 8000A240 3C178012 */  lui   $s7, %hi(D_8011A6DC) # $s7, 0x8012
/* 00AE44 8000A244 3C1E8012 */  lui   $fp, %hi(D_8011AC1C) # $fp, 0x8012
/* 00AE48 8000A248 27DEAC1C */  addiu $fp, %lo(D_8011AC1C) # addiu $fp, $fp, -0x53e4
/* 00AE4C 8000A24C 26F7A6DC */  addiu $s7, %lo(D_8011A6DC) # addiu $s7, $s7, -0x5924
/* 00AE50 8000A250 26D6A6D8 */  addiu $s6, %lo(D_8011A6D8) # addiu $s6, $s6, -0x5928
.L8000A254:
/* 00AE54 8000A254 92C90000 */  lbu   $t1, ($s6)
/* 00AE58 8000A258 02C09025 */  move  $s2, $s6
/* 00AE5C 8000A25C 11200013 */  beqz  $t1, .L8000A2AC
/* 00AE60 8000A260 02E08825 */   move  $s1, $s7
/* 00AE64 8000A264 82CA00B8 */  lb    $t2, 0xb8($s6)
/* 00AE68 8000A268 00008025 */  move  $s0, $zero
/* 00AE6C 8000A26C 1940000F */  blez  $t2, .L8000A2AC
.L8000A270:
/* 00AE70 8000A270 240B00FF */   li    $t3, 255
/* 00AE74 8000A274 240C00FF */  li    $t4, 255
/* 00AE78 8000A278 AFAC0018 */  sw    $t4, 0x18($sp)
/* 00AE7C 8000A27C AFAB0010 */  sw    $t3, 0x10($sp)
/* 00AE80 8000A280 02602025 */  move  $a0, $s3
/* 00AE84 8000A284 02802825 */  move  $a1, $s4
/* 00AE88 8000A288 02A03025 */  move  $a2, $s5
/* 00AE8C 8000A28C 02203825 */  move  $a3, $s1
/* 00AE90 8000A290 0C002905 */  jal   debug_render_spline
/* 00AE94 8000A294 AFA00014 */   sw    $zero, 0x14($sp)
/* 00AE98 8000A298 824D00B8 */  lb    $t5, 0xb8($s2)
/* 00AE9C 8000A29C 26100001 */  addiu $s0, $s0, 1
/* 00AEA0 8000A2A0 020D082A */  slt   $at, $s0, $t5
/* 00AEA4 8000A2A4 1420FFF2 */  bnez  $at, .L8000A270
/* 00AEA8 8000A2A8 2631000C */   addiu $s1, $s1, 0xc
.L8000A2AC:
/* 00AEAC 8000A2AC 26F700C0 */  addiu $s7, $s7, 0xc0
/* 00AEB0 8000A2B0 16FEFFE8 */  bne   $s7, $fp, .L8000A254
/* 00AEB4 8000A2B4 26D600C0 */   addiu $s6, $s6, 0xc0
/* 00AEB8 8000A2B8 8FBF004C */  lw    $ra, 0x4c($sp)
/* 00AEBC 8000A2BC 8FB00028 */  lw    $s0, 0x28($sp)
/* 00AEC0 8000A2C0 8FB1002C */  lw    $s1, 0x2c($sp)
/* 00AEC4 8000A2C4 8FB20030 */  lw    $s2, 0x30($sp)
/* 00AEC8 8000A2C8 8FB30034 */  lw    $s3, 0x34($sp)
/* 00AECC 8000A2CC 8FB40038 */  lw    $s4, 0x38($sp)
/* 00AED0 8000A2D0 8FB5003C */  lw    $s5, 0x3c($sp)
/* 00AED4 8000A2D4 8FB60040 */  lw    $s6, 0x40($sp)
/* 00AED8 8000A2D8 8FB70044 */  lw    $s7, 0x44($sp)
/* 00AEDC 8000A2DC 8FBE0048 */  lw    $fp, 0x48($sp)
/* 00AEE0 8000A2E0 03E00008 */  jr    $ra
/* 00AEE4 8000A2E4 27BD0050 */   addiu $sp, $sp, 0x50

