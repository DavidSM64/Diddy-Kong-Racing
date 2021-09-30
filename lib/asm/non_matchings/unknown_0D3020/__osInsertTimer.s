glabel __osInsertTimer
/* 0D5D38 800D5138 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0D5D3C 800D513C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0D5D40 800D5140 0C034958 */  jal   __osDisableInt
/* 0D5D44 800D5144 AFA40038 */   sw    $a0, 0x38($sp)
/* 0D5D48 800D5148 3C0E800E */  lui   $t6, %hi(__osTimerList) # $t6, 0x800e
/* 0D5D4C 800D514C 8DCE4910 */  lw    $t6, %lo(__osTimerList)($t6)
/* 0D5D50 800D5150 AFA20024 */  sw    $v0, 0x24($sp)
/* 0D5D54 800D5154 8FB80038 */  lw    $t8, 0x38($sp)
/* 0D5D58 800D5158 8DCF0000 */  lw    $t7, ($t6)
/* 0D5D5C 800D515C AFAF0034 */  sw    $t7, 0x34($sp)
/* 0D5D60 800D5160 8F090014 */  lw    $t1, 0x14($t8)
/* 0D5D64 800D5164 8F080010 */  lw    $t0, 0x10($t8)
/* 0D5D68 800D5168 AFA9002C */  sw    $t1, 0x2c($sp)
/* 0D5D6C 800D516C 11EE0029 */  beq   $t7, $t6, .L800D5214
/* 0D5D70 800D5170 AFA80028 */   sw    $t0, 0x28($sp)
/* 0D5D74 800D5174 8DEA0010 */  lw    $t2, 0x10($t7)
/* 0D5D78 800D5178 8DEB0014 */  lw    $t3, 0x14($t7)
/* 0D5D7C 800D517C 010A082B */  sltu  $at, $t0, $t2
/* 0D5D80 800D5180 14200024 */  bnez  $at, .L800D5214
/* 0D5D84 800D5184 0148082B */   sltu  $at, $t2, $t0
/* 0D5D88 800D5188 14200003 */  bnez  $at, .L800D5198
/* 0D5D8C 800D518C 0169082B */   sltu  $at, $t3, $t1
/* 0D5D90 800D5190 10200020 */  beqz  $at, .L800D5214
/* 0D5D94 800D5194 00000000 */   nop   
.L800D5198:
/* 0D5D98 800D5198 27B90028 */  addiu $t9, $sp, 0x28
/* 0D5D9C 800D519C 8FB80034 */  lw    $t8, 0x34($sp)
/* 0D5DA0 800D51A0 AFB90020 */  sw    $t9, 0x20($sp)
/* 0D5DA4 800D51A4 8F2D0004 */  lw    $t5, 4($t9)
/* 0D5DA8 800D51A8 8F2C0000 */  lw    $t4, ($t9)
/* 0D5DAC 800D51AC 8F0F0014 */  lw    $t7, 0x14($t8)
/* 0D5DB0 800D51B0 8F0E0010 */  lw    $t6, 0x10($t8)
/* 0D5DB4 800D51B4 3C18800E */  lui   $t8, %hi(__osTimerList) # $t8, 0x800e
/* 0D5DB8 800D51B8 01AF082B */  sltu  $at, $t5, $t7
/* 0D5DBC 800D51BC 018E4023 */  subu  $t0, $t4, $t6
/* 0D5DC0 800D51C0 01014023 */  subu  $t0, $t0, $at
/* 0D5DC4 800D51C4 01AF4823 */  subu  $t1, $t5, $t7
/* 0D5DC8 800D51C8 AF290004 */  sw    $t1, 4($t9)
/* 0D5DCC 800D51CC AF280000 */  sw    $t0, ($t9)
/* 0D5DD0 800D51D0 8FAA0034 */  lw    $t2, 0x34($sp)
/* 0D5DD4 800D51D4 8F184910 */  lw    $t8, %lo(__osTimerList)($t8)
/* 0D5DD8 800D51D8 8D4B0000 */  lw    $t3, ($t2)
/* 0D5DDC 800D51DC 1178000D */  beq   $t3, $t8, .L800D5214
/* 0D5DE0 800D51E0 AFAB0034 */   sw    $t3, 0x34($sp)
/* 0D5DE4 800D51E4 8FAC0028 */  lw    $t4, 0x28($sp)
/* 0D5DE8 800D51E8 8D6E0010 */  lw    $t6, 0x10($t3)
/* 0D5DEC 800D51EC 8FAD002C */  lw    $t5, 0x2c($sp)
/* 0D5DF0 800D51F0 8D6F0014 */  lw    $t7, 0x14($t3)
/* 0D5DF4 800D51F4 01CC082B */  sltu  $at, $t6, $t4
/* 0D5DF8 800D51F8 1420FFE7 */  bnez  $at, .L800D5198
/* 0D5DFC 800D51FC 00000000 */   nop   
/* 0D5E00 800D5200 018E082B */  sltu  $at, $t4, $t6
/* 0D5E04 800D5204 14200003 */  bnez  $at, .L800D5214
/* 0D5E08 800D5208 01ED082B */   sltu  $at, $t7, $t5
/* 0D5E0C 800D520C 1420FFE2 */  bnez  $at, .L800D5198
/* 0D5E10 800D5210 00000000 */   nop   
.L800D5214:
/* 0D5E14 800D5214 8FB90038 */  lw    $t9, 0x38($sp)
/* 0D5E18 800D5218 8FA80028 */  lw    $t0, 0x28($sp)
/* 0D5E1C 800D521C 8FA9002C */  lw    $t1, 0x2c($sp)
/* 0D5E20 800D5220 3C18800E */  lui   $t8, %hi(__osTimerList) # $t8, 0x800e
/* 0D5E24 800D5224 AF280010 */  sw    $t0, 0x10($t9)
/* 0D5E28 800D5228 AF290014 */  sw    $t1, 0x14($t9)
/* 0D5E2C 800D522C 8F184910 */  lw    $t8, %lo(__osTimerList)($t8)
/* 0D5E30 800D5230 8FAA0034 */  lw    $t2, 0x34($sp)
/* 0D5E34 800D5234 1158000D */  beq   $t2, $t8, .L800D526C
/* 0D5E38 800D5238 00000000 */   nop   
/* 0D5E3C 800D523C 254B0010 */  addiu $t3, $t2, 0x10
/* 0D5E40 800D5240 AFAB001C */  sw    $t3, 0x1c($sp)
/* 0D5E44 800D5244 8D4D0014 */  lw    $t5, 0x14($t2)
/* 0D5E48 800D5248 8D4C0010 */  lw    $t4, 0x10($t2)
/* 0D5E4C 800D524C 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0D5E50 800D5250 8FAF002C */  lw    $t7, 0x2c($sp)
/* 0D5E54 800D5254 018E4023 */  subu  $t0, $t4, $t6
/* 0D5E58 800D5258 01AF082B */  sltu  $at, $t5, $t7
/* 0D5E5C 800D525C 01014023 */  subu  $t0, $t0, $at
/* 0D5E60 800D5260 01AF4823 */  subu  $t1, $t5, $t7
/* 0D5E64 800D5264 AD490014 */  sw    $t1, 0x14($t2)
/* 0D5E68 800D5268 AD480010 */  sw    $t0, 0x10($t2)
.L800D526C:
/* 0D5E6C 800D526C 8FB90034 */  lw    $t9, 0x34($sp)
/* 0D5E70 800D5270 8FB80038 */  lw    $t8, 0x38($sp)
/* 0D5E74 800D5274 AF190000 */  sw    $t9, ($t8)
/* 0D5E78 800D5278 8FAB0034 */  lw    $t3, 0x34($sp)
/* 0D5E7C 800D527C 8FAD0038 */  lw    $t5, 0x38($sp)
/* 0D5E80 800D5280 8D6C0004 */  lw    $t4, 4($t3)
/* 0D5E84 800D5284 ADAC0004 */  sw    $t4, 4($t5)
/* 0D5E88 800D5288 8FAF0034 */  lw    $t7, 0x34($sp)
/* 0D5E8C 800D528C 8FAE0038 */  lw    $t6, 0x38($sp)
/* 0D5E90 800D5290 8DE80004 */  lw    $t0, 4($t7)
/* 0D5E94 800D5294 AD0E0000 */  sw    $t6, ($t0)
/* 0D5E98 800D5298 8FAA0034 */  lw    $t2, 0x34($sp)
/* 0D5E9C 800D529C 8FA90038 */  lw    $t1, 0x38($sp)
/* 0D5EA0 800D52A0 AD490004 */  sw    $t1, 4($t2)
/* 0D5EA4 800D52A4 0C034960 */  jal   __osRestoreInt
/* 0D5EA8 800D52A8 8FA40024 */   lw    $a0, 0x24($sp)
/* 0D5EAC 800D52AC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0D5EB0 800D52B0 8FA20028 */  lw    $v0, 0x28($sp)
/* 0D5EB4 800D52B4 8FA3002C */  lw    $v1, 0x2c($sp)
/* 0D5EB8 800D52B8 03E00008 */  jr    $ra
/* 0D5EBC 800D52BC 27BD0038 */   addiu $sp, $sp, 0x38

