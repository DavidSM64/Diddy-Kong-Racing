.rdata
glabel D_800E7078
.asciz "%x."
glabel D_800E707C
.asciz "%x  "
.ascii "\0\0\0" # padding
glabel D_800E7084
.asciz "\n"
.ascii "\0\0" # padding
glabel D_800E7088
.asciz "\n"
.ascii "\0\0" # padding
glabel D_800E708C
.asciz "%f  "
.ascii "\0\0\0" # padding
glabel D_800E7094
.asciz "\n"
.ascii "\0\0" # padding
glabel D_800E7098
.asciz "\n"
.ascii "\0\0" # padding

.text
glabel func_80069F28
/* 06AB28 80069F28 3C038012 */  lui   $v1, %hi(D_80120CE0) # $v1, 0x8012
/* 06AB2C 80069F2C 8C630CE0 */  lw    $v1, %lo(D_80120CE0)($v1)
/* 06AB30 80069F30 3C0E8012 */  lui   $t6, %hi(D_80120AC0) # $t6, 0x8012
/* 06AB34 80069F34 04600009 */  bltz  $v1, .L80069F5C
/* 06AB38 80069F38 25C20AC0 */   addiu $v0, $t6, %lo(D_80120AC0)
/* 06AB3C 80069F3C 00037900 */  sll   $t7, $v1, 4
/* 06AB40 80069F40 01E37821 */  addu  $t7, $t7, $v1
/* 06AB44 80069F44 000F7880 */  sll   $t7, $t7, 2
/* 06AB48 80069F48 01E22021 */  addu  $a0, $t7, $v0
.L80069F4C:
/* 06AB4C 80069F4C 24420044 */  addiu $v0, $v0, 0x44
/* 06AB50 80069F50 0082082B */  sltu  $at, $a0, $v0
/* 06AB54 80069F54 1020FFFD */  beqz  $at, .L80069F4C
/* 06AB58 80069F58 E44CFFEC */   swc1  $f12, -0x14($v0)
.L80069F5C:
/* 06AB5C 80069F5C 03E00008 */  jr    $ra
/* 06AB60 80069F60 00000000 */   nop   

/* 06AB64 80069F64 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 06AB68 80069F68 AFBE0038 */  sw    $fp, 0x38($sp)
/* 06AB6C 80069F6C AFB40028 */  sw    $s4, 0x28($sp)
/* 06AB70 80069F70 AFB30024 */  sw    $s3, 0x24($sp)
/* 06AB74 80069F74 AFB70034 */  sw    $s7, 0x34($sp)
/* 06AB78 80069F78 AFB60030 */  sw    $s6, 0x30($sp)
/* 06AB7C 80069F7C AFB5002C */  sw    $s5, 0x2c($sp)
/* 06AB80 80069F80 3C13800E */  lui   $s3, %hi(D_800E7078) # $s3, 0x800e
/* 06AB84 80069F84 3C14800E */  lui   $s4, %hi(D_800E707C) # $s4, 0x800e
/* 06AB88 80069F88 3C1E800E */  lui   $fp, %hi(D_800E7084) # $fp, 0x800e
/* 06AB8C 80069F8C AFBF003C */  sw    $ra, 0x3c($sp)
/* 06AB90 80069F90 AFB20020 */  sw    $s2, 0x20($sp)
/* 06AB94 80069F94 AFB1001C */  sw    $s1, 0x1c($sp)
/* 06AB98 80069F98 AFB00018 */  sw    $s0, 0x18($sp)
/* 06AB9C 80069F9C 27DE7084 */  addiu $fp, %lo(D_800E7084) # addiu $fp, $fp, 0x7084
/* 06ABA0 80069FA0 2694707C */  addiu $s4, %lo(D_800E707C) # addiu $s4, $s4, 0x707c
/* 06ABA4 80069FA4 26737078 */  addiu $s3, %lo(D_800E7078) # addiu $s3, $s3, 0x7078
/* 06ABA8 80069FA8 24150008 */  li    $s5, 8
/* 06ABAC 80069FAC 0000B025 */  move  $s6, $zero
/* 06ABB0 80069FB0 0080B825 */  move  $s7, $a0
.L80069FB4:
/* 06ABB4 80069FB4 00008825 */  move  $s1, $zero
/* 06ABB8 80069FB8 02E08025 */  move  $s0, $s7
.L80069FBC:
/* 06ABBC 80069FBC 86050000 */  lh    $a1, ($s0)
/* 06ABC0 80069FC0 0C032755 */  jal   func_800C9D54
/* 06ABC4 80069FC4 02602025 */   move  $a0, $s3
/* 06ABC8 80069FC8 86050020 */  lh    $a1, 0x20($s0)
/* 06ABCC 80069FCC 02802025 */  move  $a0, $s4
/* 06ABD0 80069FD0 30AEFFFF */  andi  $t6, $a1, 0xffff
/* 06ABD4 80069FD4 0C032755 */  jal   func_800C9D54
/* 06ABD8 80069FD8 01C02825 */   move  $a1, $t6
/* 06ABDC 80069FDC 26310002 */  addiu $s1, $s1, 2
/* 06ABE0 80069FE0 1635FFF6 */  bne   $s1, $s5, .L80069FBC
/* 06ABE4 80069FE4 26100002 */   addiu $s0, $s0, 2
/* 06ABE8 80069FE8 0C032755 */  jal   func_800C9D54
/* 06ABEC 80069FEC 03C02025 */   move  $a0, $fp
/* 06ABF0 80069FF0 26D60004 */  addiu $s6, $s6, 4
/* 06ABF4 80069FF4 24010010 */  li    $at, 16
/* 06ABF8 80069FF8 16C1FFEE */  bne   $s6, $at, .L80069FB4
/* 06ABFC 80069FFC 26F70008 */   addiu $s7, $s7, 8
/* 06AC00 8006A000 3C04800E */  lui   $a0, %hi(D_800E7088) # $a0, 0x800e
/* 06AC04 8006A004 0C032755 */  jal   func_800C9D54
/* 06AC08 8006A008 24847088 */   addiu $a0, %lo(D_800E7088) # addiu $a0, $a0, 0x7088
/* 06AC0C 8006A00C 8FBF003C */  lw    $ra, 0x3c($sp)
/* 06AC10 8006A010 8FB00018 */  lw    $s0, 0x18($sp)
/* 06AC14 8006A014 8FB1001C */  lw    $s1, 0x1c($sp)
/* 06AC18 8006A018 8FB20020 */  lw    $s2, 0x20($sp)
/* 06AC1C 8006A01C 8FB30024 */  lw    $s3, 0x24($sp)
/* 06AC20 8006A020 8FB40028 */  lw    $s4, 0x28($sp)
/* 06AC24 8006A024 8FB5002C */  lw    $s5, 0x2c($sp)
/* 06AC28 8006A028 8FB60030 */  lw    $s6, 0x30($sp)
/* 06AC2C 8006A02C 8FB70034 */  lw    $s7, 0x34($sp)
/* 06AC30 8006A030 8FBE0038 */  lw    $fp, 0x38($sp)
/* 06AC34 8006A034 03E00008 */  jr    $ra
/* 06AC38 8006A038 27BD0040 */   addiu $sp, $sp, 0x40

/* 06AC3C 8006A03C 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 06AC40 8006A040 AFB6002C */  sw    $s6, 0x2c($sp)
/* 06AC44 8006A044 AFB2001C */  sw    $s2, 0x1c($sp)
/* 06AC48 8006A048 AFB70030 */  sw    $s7, 0x30($sp)
/* 06AC4C 8006A04C AFB50028 */  sw    $s5, 0x28($sp)
/* 06AC50 8006A050 AFB40024 */  sw    $s4, 0x24($sp)
/* 06AC54 8006A054 AFB30020 */  sw    $s3, 0x20($sp)
/* 06AC58 8006A058 3C12800E */  lui   $s2, %hi(D_800E708C) # $s2, 0x800e
/* 06AC5C 8006A05C 3C16800E */  lui   $s6, %hi(D_800E7094) # $s6, 0x800e
/* 06AC60 8006A060 AFBF0034 */  sw    $ra, 0x34($sp)
/* 06AC64 8006A064 AFB10018 */  sw    $s1, 0x18($sp)
/* 06AC68 8006A068 AFB00014 */  sw    $s0, 0x14($sp)
/* 06AC6C 8006A06C 26D67094 */  addiu $s6, %lo(D_800E7094) # addiu $s6, $s6, 0x7094
/* 06AC70 8006A070 2652708C */  addiu $s2, %lo(D_800E708C) # addiu $s2, $s2, 0x708c
/* 06AC74 8006A074 24130010 */  li    $s3, 16
/* 06AC78 8006A078 0000A025 */  move  $s4, $zero
/* 06AC7C 8006A07C 0080A825 */  move  $s5, $a0
/* 06AC80 8006A080 24170010 */  li    $s7, 16
.L8006A084:
/* 06AC84 8006A084 00008025 */  move  $s0, $zero
/* 06AC88 8006A088 02A08825 */  move  $s1, $s5
.L8006A08C:
/* 06AC8C 8006A08C C6240000 */  lwc1  $f4, ($s1)
/* 06AC90 8006A090 02402025 */  move  $a0, $s2
/* 06AC94 8006A094 460021A1 */  cvt.d.s $f6, $f4
/* 06AC98 8006A098 44073000 */  mfc1  $a3, $f6
/* 06AC9C 8006A09C 44063800 */  mfc1  $a2, $f7
/* 06ACA0 8006A0A0 0C032755 */  jal   func_800C9D54
/* 06ACA4 8006A0A4 00000000 */   nop   
/* 06ACA8 8006A0A8 26100004 */  addiu $s0, $s0, 4
/* 06ACAC 8006A0AC 1613FFF7 */  bne   $s0, $s3, .L8006A08C
/* 06ACB0 8006A0B0 26310004 */   addiu $s1, $s1, 4
/* 06ACB4 8006A0B4 0C032755 */  jal   func_800C9D54
/* 06ACB8 8006A0B8 02C02025 */   move  $a0, $s6
/* 06ACBC 8006A0BC 26940004 */  addiu $s4, $s4, 4
/* 06ACC0 8006A0C0 1697FFF0 */  bne   $s4, $s7, .L8006A084
/* 06ACC4 8006A0C4 26B50010 */   addiu $s5, $s5, 0x10
/* 06ACC8 8006A0C8 3C04800E */  lui   $a0, %hi(D_800E7098) # $a0, 0x800e
/* 06ACCC 8006A0CC 0C032755 */  jal   func_800C9D54
/* 06ACD0 8006A0D0 24847098 */   addiu $a0, %lo(D_800E7098) # addiu $a0, $a0, 0x7098
/* 06ACD4 8006A0D4 8FBF0034 */  lw    $ra, 0x34($sp)
/* 06ACD8 8006A0D8 8FB00014 */  lw    $s0, 0x14($sp)
/* 06ACDC 8006A0DC 8FB10018 */  lw    $s1, 0x18($sp)
/* 06ACE0 8006A0E0 8FB2001C */  lw    $s2, 0x1c($sp)
/* 06ACE4 8006A0E4 8FB30020 */  lw    $s3, 0x20($sp)
/* 06ACE8 8006A0E8 8FB40024 */  lw    $s4, 0x24($sp)
/* 06ACEC 8006A0EC 8FB50028 */  lw    $s5, 0x28($sp)
/* 06ACF0 8006A0F0 8FB6002C */  lw    $s6, 0x2c($sp)
/* 06ACF4 8006A0F4 8FB70030 */  lw    $s7, 0x30($sp)
/* 06ACF8 8006A0F8 03E00008 */  jr    $ra
/* 06ACFC 8006A0FC 27BD0038 */   addiu $sp, $sp, 0x38

