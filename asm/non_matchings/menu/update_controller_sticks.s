glabel update_controller_sticks
/* 09CB20 8009BF20 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 09CB24 8009BF24 AFB70034 */  sw    $s7, 0x34($sp)
/* 09CB28 8009BF28 AFB60030 */  sw    $s6, 0x30($sp)
/* 09CB2C 8009BF2C AFB30024 */  sw    $s3, 0x24($sp)
/* 09CB30 8009BF30 AFB20020 */  sw    $s2, 0x20($sp)
/* 09CB34 8009BF34 AFB1001C */  sw    $s1, 0x1c($sp)
/* 09CB38 8009BF38 AFB00018 */  sw    $s0, 0x18($sp)
/* 09CB3C 8009BF3C AFBE0038 */  sw    $fp, 0x38($sp)
/* 09CB40 8009BF40 AFB5002C */  sw    $s5, 0x2c($sp)
/* 09CB44 8009BF44 3C108012 */  lui   $s0, %hi(gControllersXAxisDelay) # $s0, 0x8012
/* 09CB48 8009BF48 3C118012 */  lui   $s1, %hi(gControllersYAxisDelay) # $s1, 0x8012
/* 09CB4C 8009BF4C 3C128012 */  lui   $s2, %hi(gControllersXAxis) # $s2, 0x8012
/* 09CB50 8009BF50 3C138012 */  lui   $s3, %hi(gControllersYAxis) # $s3, 0x8012
/* 09CB54 8009BF54 3C168012 */  lui   $s6, %hi(gControllersXAxisDirection) # $s6, 0x8012
/* 09CB58 8009BF58 3C178012 */  lui   $s7, %hi(gControllersYAxisDirection) # $s7, 0x8012
/* 09CB5C 8009BF5C AFBF003C */  sw    $ra, 0x3c($sp)
/* 09CB60 8009BF60 AFB40028 */  sw    $s4, 0x28($sp)
/* 09CB64 8009BF64 26F76464 */  addiu $s7, %lo(gControllersYAxisDirection) # addiu $s7, $s7, 0x6464
/* 09CB68 8009BF68 26D6645C */  addiu $s6, %lo(gControllersXAxisDirection) # addiu $s6, $s6, 0x645c
/* 09CB6C 8009BF6C 2673646C */  addiu $s3, %lo(gControllersYAxis) # addiu $s3, $s3, 0x646c
/* 09CB70 8009BF70 26526468 */  addiu $s2, %lo(gControllersXAxis) # addiu $s2, $s2, 0x6468
/* 09CB74 8009BF74 26316458 */  addiu $s1, %lo(gControllersYAxisDelay) # addiu $s1, $s1, 0x6458
/* 09CB78 8009BF78 26106454 */  addiu $s0, %lo(gControllersXAxisDelay) # addiu $s0, $s0, 0x6454
/* 09CB7C 8009BF7C 0000A825 */  move  $s5, $zero
/* 09CB80 8009BF80 241EFFFF */  li    $fp, -1
.L8009BF84:
/* 09CB84 8009BF84 0C01A967 */  jal   clamp_joystick_x_axis
/* 09CB88 8009BF88 02A02025 */   move  $a0, $s5
/* 09CB8C 8009BF8C 0040A025 */  move  $s4, $v0
/* 09CB90 8009BF90 0C01A978 */  jal   clamp_joystick_y_axis
/* 09CB94 8009BF94 02A02025 */   move  $a0, $s5
/* 09CB98 8009BF98 2A81FFDD */  slti  $at, $s4, -0x23
/* 09CB9C 8009BF9C A2C00000 */  sb    $zero, ($s6)
/* 09CBA0 8009BFA0 10200008 */  beqz  $at, .L8009BFC4
/* 09CBA4 8009BFA4 A2E00000 */   sb    $zero, ($s7)
/* 09CBA8 8009BFA8 824E0000 */  lb    $t6, ($s2)
/* 09CBAC 8009BFAC 00000000 */  nop   
/* 09CBB0 8009BFB0 29C1FFDD */  slti  $at, $t6, -0x23
/* 09CBB4 8009BFB4 14200004 */  bnez  $at, .L8009BFC8
/* 09CBB8 8009BFB8 2A810024 */   slti  $at, $s4, 0x24
/* 09CBBC 8009BFBC A2DE0000 */  sb    $fp, ($s6)
/* 09CBC0 8009BFC0 A2000000 */  sb    $zero, ($s0)
.L8009BFC4:
/* 09CBC4 8009BFC4 2A810024 */  slti  $at, $s4, 0x24
.L8009BFC8:
/* 09CBC8 8009BFC8 14200008 */  bnez  $at, .L8009BFEC
/* 09CBCC 8009BFCC 26B50001 */   addiu $s5, $s5, 1
/* 09CBD0 8009BFD0 824F0000 */  lb    $t7, ($s2)
/* 09CBD4 8009BFD4 24180001 */  li    $t8, 1
/* 09CBD8 8009BFD8 29E10024 */  slti  $at, $t7, 0x24
/* 09CBDC 8009BFDC 10200004 */  beqz  $at, .L8009BFF0
/* 09CBE0 8009BFE0 2841FFDD */   slti  $at, $v0, -0x23
/* 09CBE4 8009BFE4 A2D80000 */  sb    $t8, ($s6)
/* 09CBE8 8009BFE8 A2000000 */  sb    $zero, ($s0)
.L8009BFEC:
/* 09CBEC 8009BFEC 2841FFDD */  slti  $at, $v0, -0x23
.L8009BFF0:
/* 09CBF0 8009BFF0 10200008 */  beqz  $at, .L8009C014
/* 09CBF4 8009BFF4 26D60001 */   addiu $s6, $s6, 1
/* 09CBF8 8009BFF8 82790000 */  lb    $t9, ($s3)
/* 09CBFC 8009BFFC 00000000 */  nop   
/* 09CC00 8009C000 2B21FFDD */  slti  $at, $t9, -0x23
/* 09CC04 8009C004 14200004 */  bnez  $at, .L8009C018
/* 09CC08 8009C008 28410024 */   slti  $at, $v0, 0x24
/* 09CC0C 8009C00C A2FE0000 */  sb    $fp, ($s7)
/* 09CC10 8009C010 A2200000 */  sb    $zero, ($s1)
.L8009C014:
/* 09CC14 8009C014 28410024 */  slti  $at, $v0, 0x24
.L8009C018:
/* 09CC18 8009C018 14200008 */  bnez  $at, .L8009C03C
/* 09CC1C 8009C01C 00000000 */   nop   
/* 09CC20 8009C020 82680000 */  lb    $t0, ($s3)
/* 09CC24 8009C024 24090001 */  li    $t1, 1
/* 09CC28 8009C028 29010024 */  slti  $at, $t0, 0x24
/* 09CC2C 8009C02C 10200003 */  beqz  $at, .L8009C03C
/* 09CC30 8009C030 00000000 */   nop   
/* 09CC34 8009C034 A2E90000 */  sb    $t1, ($s7)
/* 09CC38 8009C038 A2200000 */  sb    $zero, ($s1)
.L8009C03C:
/* 09CC3C 8009C03C A2620000 */  sb    $v0, ($s3)
/* 09CC40 8009C040 82630000 */  lb    $v1, ($s3)
/* 09CC44 8009C044 26F70001 */  addiu $s7, $s7, 1
/* 09CC48 8009C048 2861FFDD */  slti  $at, $v1, -0x23
/* 09CC4C 8009C04C 10200007 */  beqz  $at, .L8009C06C
/* 09CC50 8009C050 28610024 */   slti  $at, $v1, 0x24
/* 09CC54 8009C054 822A0000 */  lb    $t2, ($s1)
/* 09CC58 8009C058 00000000 */  nop   
/* 09CC5C 8009C05C 254B0001 */  addiu $t3, $t2, 1
/* 09CC60 8009C060 1000000A */  b     .L8009C08C
/* 09CC64 8009C064 A22B0000 */   sb    $t3, ($s1)
/* 09CC68 8009C068 28610024 */  slti  $at, $v1, 0x24
.L8009C06C:
/* 09CC6C 8009C06C 14200006 */  bnez  $at, .L8009C088
/* 09CC70 8009C070 00000000 */   nop   
/* 09CC74 8009C074 822C0000 */  lb    $t4, ($s1)
/* 09CC78 8009C078 00000000 */  nop   
/* 09CC7C 8009C07C 258D0001 */  addiu $t5, $t4, 1
/* 09CC80 8009C080 10000002 */  b     .L8009C08C
/* 09CC84 8009C084 A22D0000 */   sb    $t5, ($s1)
.L8009C088:
/* 09CC88 8009C088 A2200000 */  sb    $zero, ($s1)
.L8009C08C:
/* 09CC8C 8009C08C 822E0000 */  lb    $t6, ($s1)
/* 09CC90 8009C090 00000000 */  nop   
/* 09CC94 8009C094 29C10010 */  slti  $at, $t6, 0x10
/* 09CC98 8009C098 14200003 */  bnez  $at, .L8009C0A8
/* 09CC9C 8009C09C 00000000 */   nop   
/* 09CCA0 8009C0A0 A2600000 */  sb    $zero, ($s3)
/* 09CCA4 8009C0A4 A2200000 */  sb    $zero, ($s1)
.L8009C0A8:
/* 09CCA8 8009C0A8 A2540000 */  sb    $s4, ($s2)
/* 09CCAC 8009C0AC 82420000 */  lb    $v0, ($s2)
/* 09CCB0 8009C0B0 26730001 */  addiu $s3, $s3, 1
/* 09CCB4 8009C0B4 2841FFDD */  slti  $at, $v0, -0x23
/* 09CCB8 8009C0B8 10200006 */  beqz  $at, .L8009C0D4
/* 09CCBC 8009C0BC 26310001 */   addiu $s1, $s1, 1
/* 09CCC0 8009C0C0 820F0000 */  lb    $t7, ($s0)
/* 09CCC4 8009C0C4 00000000 */  nop   
/* 09CCC8 8009C0C8 25F80001 */  addiu $t8, $t7, 1
/* 09CCCC 8009C0CC 1000000A */  b     .L8009C0F8
/* 09CCD0 8009C0D0 A2180000 */   sb    $t8, ($s0)
.L8009C0D4:
/* 09CCD4 8009C0D4 28410024 */  slti  $at, $v0, 0x24
/* 09CCD8 8009C0D8 14200006 */  bnez  $at, .L8009C0F4
/* 09CCDC 8009C0DC 00000000 */   nop   
/* 09CCE0 8009C0E0 82190000 */  lb    $t9, ($s0)
/* 09CCE4 8009C0E4 00000000 */  nop   
/* 09CCE8 8009C0E8 27280001 */  addiu $t0, $t9, 1
/* 09CCEC 8009C0EC 10000002 */  b     .L8009C0F8
/* 09CCF0 8009C0F0 A2080000 */   sb    $t0, ($s0)
.L8009C0F4:
/* 09CCF4 8009C0F4 A2000000 */  sb    $zero, ($s0)
.L8009C0F8:
/* 09CCF8 8009C0F8 82090000 */  lb    $t1, ($s0)
/* 09CCFC 8009C0FC 00000000 */  nop   
/* 09CD00 8009C100 29210010 */  slti  $at, $t1, 0x10
/* 09CD04 8009C104 14200004 */  bnez  $at, .L8009C118
/* 09CD08 8009C108 24010004 */   li    $at, 4
/* 09CD0C 8009C10C A2400000 */  sb    $zero, ($s2)
/* 09CD10 8009C110 A2000000 */  sb    $zero, ($s0)
/* 09CD14 8009C114 24010004 */  li    $at, 4
.L8009C118:
/* 09CD18 8009C118 26520001 */  addiu $s2, $s2, 1
/* 09CD1C 8009C11C 16A1FF99 */  bne   $s5, $at, .L8009BF84
/* 09CD20 8009C120 26100001 */   addiu $s0, $s0, 1
/* 09CD24 8009C124 8FBF003C */  lw    $ra, 0x3c($sp)
/* 09CD28 8009C128 8FB00018 */  lw    $s0, 0x18($sp)
/* 09CD2C 8009C12C 8FB1001C */  lw    $s1, 0x1c($sp)
/* 09CD30 8009C130 8FB20020 */  lw    $s2, 0x20($sp)
/* 09CD34 8009C134 8FB30024 */  lw    $s3, 0x24($sp)
/* 09CD38 8009C138 8FB40028 */  lw    $s4, 0x28($sp)
/* 09CD3C 8009C13C 8FB5002C */  lw    $s5, 0x2c($sp)
/* 09CD40 8009C140 8FB60030 */  lw    $s6, 0x30($sp)
/* 09CD44 8009C144 8FB70034 */  lw    $s7, 0x34($sp)
/* 09CD48 8009C148 8FBE0038 */  lw    $fp, 0x38($sp)
/* 09CD4C 8009C14C 03E00008 */  jr    $ra
/* 09CD50 8009C150 27BD0040 */   addiu $sp, $sp, 0x40

