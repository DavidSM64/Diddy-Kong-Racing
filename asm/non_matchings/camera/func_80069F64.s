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

.text

# Unused
glabel func_80069F64
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
/* 06ABC0 80069FC0 0C032755 */  jal   simple_sprintf
/* 06ABC4 80069FC4 02602025 */   move  $a0, $s3
/* 06ABC8 80069FC8 86050020 */  lh    $a1, 0x20($s0)
/* 06ABCC 80069FCC 02802025 */  move  $a0, $s4
/* 06ABD0 80069FD0 30AEFFFF */  andi  $t6, $a1, 0xffff
/* 06ABD4 80069FD4 0C032755 */  jal   simple_sprintf
/* 06ABD8 80069FD8 01C02825 */   move  $a1, $t6
/* 06ABDC 80069FDC 26310002 */  addiu $s1, $s1, 2
/* 06ABE0 80069FE0 1635FFF6 */  bne   $s1, $s5, .L80069FBC
/* 06ABE4 80069FE4 26100002 */   addiu $s0, $s0, 2
/* 06ABE8 80069FE8 0C032755 */  jal   simple_sprintf
/* 06ABEC 80069FEC 03C02025 */   move  $a0, $fp
/* 06ABF0 80069FF0 26D60004 */  addiu $s6, $s6, 4
/* 06ABF4 80069FF4 24010010 */  li    $at, 16
/* 06ABF8 80069FF8 16C1FFEE */  bne   $s6, $at, .L80069FB4
/* 06ABFC 80069FFC 26F70008 */   addiu $s7, $s7, 8
/* 06AC00 8006A000 3C04800E */  lui   $a0, %hi(D_800E7088) # $a0, 0x800e
/* 06AC04 8006A004 0C032755 */  jal   simple_sprintf
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
