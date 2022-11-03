glabel func_8001B3C4
/* 01BFC4 8001B3C4 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 01BFC8 8001B3C8 AFBF001C */  sw    $ra, 0x1c($sp)
/* 01BFCC 8001B3CC AFB00018 */  sw    $s0, 0x18($sp)
/* 01BFD0 8001B3D0 3C01800E */  lui   $at, %hi(D_800DC718) # $at, 0x800e
/* 01BFD4 8001B3D4 00808025 */  move  $s0, $a0
/* 01BFD8 8001B3D8 AFA50024 */  sw    $a1, 0x24($sp)
/* 01BFDC 8001B3DC 0C0166D3 */  jal   free_tt_ghost_data
/* 01BFE0 8001B3E0 AC20C718 */   sw    $zero, %lo(D_800DC718)($at)
/* 01BFE4 8001B3E4 3C01800E */  lui   $at, %hi(D_800DC734) # $at, 0x800e
/* 01BFE8 8001B3E8 A020C734 */  sb    $zero, %lo(D_800DC734)($at)
/* 01BFEC 8001B3EC 0C0078A7 */  jal   get_misc_asset
/* 01BFF0 8001B3F0 2404001C */   li    $a0, 28
/* 01BFF4 8001B3F4 804E0000 */  lb    $t6, ($v0)
/* 01BFF8 8001B3F8 2407FFFF */  li    $a3, -1
/* 01BFFC 8001B3FC 00402825 */  move  $a1, $v0
/* 01C000 8001B400 10EE000E */  beq   $a3, $t6, .L8001B43C
/* 01C004 8001B404 00003025 */   move  $a2, $zero
/* 01C008 8001B408 804F0000 */  lb    $t7, ($v0)
/* 01C00C 8001B40C 00402021 */  addu  $a0, $v0, $zero
/* 01C010 8001B410 120F000A */  beq   $s0, $t7, .L8001B43C
/* 01C014 8001B414 00000000 */   nop   
.L8001B418:
/* 01C018 8001B418 80980001 */  lb    $t8, 1($a0)
/* 01C01C 8001B41C 24C60001 */  addiu $a2, $a2, 1
/* 01C020 8001B420 10F80006 */  beq   $a3, $t8, .L8001B43C
/* 01C024 8001B424 24840001 */   addiu $a0, $a0, 1
/* 01C028 8001B428 00A6C821 */  addu  $t9, $a1, $a2
/* 01C02C 8001B42C 83280000 */  lb    $t0, ($t9)
/* 01C030 8001B430 00000000 */  nop   
/* 01C034 8001B434 1608FFF8 */  bne   $s0, $t0, .L8001B418
/* 01C038 8001B438 00000000 */   nop   
.L8001B43C:
/* 01C03C 8001B43C 3C10800E */  lui   $s0, %hi(D_800DC738) # $s0, 0x800e
/* 01C040 8001B440 2610C738 */  addiu $s0, %lo(D_800DC738) # addiu $s0, $s0, -0x38c8
/* 01C044 8001B444 92090000 */  lbu   $t1, ($s0)
/* 01C048 8001B448 240A0010 */  li    $t2, 16
/* 01C04C 8001B44C 11200024 */  beqz  $t1, .L8001B4E0
/* 01C050 8001B450 00CA2804 */   sllv  $a1, $t2, $a2
/* 01C054 8001B454 0C027A9E */  jal   set_eeprom_settings_value
/* 01C058 8001B458 000527C3 */   sra   $a0, $a1, 0x1f
/* 01C05C 8001B45C 0C027AC2 */  jal   get_eeprom_settings
/* 01C060 8001B460 00000000 */   nop   
/* 01C064 8001B464 3C0100FF */  lui   $at, (0x00FFFFF0 >> 16) # lui $at, 0xff
/* 01C068 8001B468 3421FFF0 */  ori   $at, (0x00FFFFF0 & 0xFFFF) # ori $at, $at, 0xfff0
/* 01C06C 8001B46C 00616824 */  and   $t5, $v1, $at
/* 01C070 8001B470 3C0100FF */  lui   $at, (0x00FFFFF0 >> 16) # lui $at, 0xff
/* 01C074 8001B474 3421FFF0 */  ori   $at, (0x00FFFFF0 & 0xFFFF) # ori $at, $at, 0xfff0
/* 01C078 8001B478 15A1000F */  bne   $t5, $at, .L8001B4B8
/* 01C07C 8001B47C 2404024C */   li    $a0, 588
/* 01C080 8001B480 0C0270B8 */  jal   set_magic_code_flags
/* 01C084 8001B484 24040001 */   li    $a0, 1
/* 01C088 8001B488 2404024E */  li    $a0, 590
/* 01C08C 8001B48C 0C000741 */  jal   play_sound_global
/* 01C090 8001B490 00002825 */   move  $a1, $zero
/* 01C094 8001B494 2404024F */  li    $a0, 591
/* 01C098 8001B498 00002825 */  move  $a1, $zero
/* 01C09C 8001B49C 0C0003F7 */  jal   func_80000FDC
/* 01C0A0 8001B4A0 3C063FC0 */   lui   $a2, 0x3fc0
/* 01C0A4 8001B4A4 0C030C7B */  jal   func_800C31EC
/* 01C0A8 8001B4A8 24040054 */   li    $a0, 84
/* 01C0AC 8001B4AC 1000000A */  b     .L8001B4D8
/* 01C0B0 8001B4B0 00000000 */   nop   
/* 01C0B4 8001B4B4 2404024C */  li    $a0, 588
.L8001B4B8:
/* 01C0B8 8001B4B8 0C000741 */  jal   play_sound_global
/* 01C0BC 8001B4BC 00002825 */   move  $a1, $zero
/* 01C0C0 8001B4C0 2404024D */  li    $a0, 589
/* 01C0C4 8001B4C4 00002825 */  move  $a1, $zero
/* 01C0C8 8001B4C8 0C0003F7 */  jal   func_80000FDC
/* 01C0CC 8001B4CC 3C063F80 */   lui   $a2, 0x3f80
/* 01C0D0 8001B4D0 0C030C7B */  jal   func_800C31EC
/* 01C0D4 8001B4D4 24040053 */   li    $a0, 83
.L8001B4D8:
/* 01C0D8 8001B4D8 10000004 */  b     .L8001B4EC
/* 01C0DC 8001B4DC A2000000 */   sb    $zero, ($s0)
.L8001B4E0:
/* 01C0E0 8001B4E0 8FA40024 */  lw    $a0, 0x24($sp)
/* 01C0E4 8001B4E4 0C029B6D */  jal   play_time_trial_end_message
/* 01C0E8 8001B4E8 00000000 */   nop   
.L8001B4EC:
/* 01C0EC 8001B4EC 8FBF001C */  lw    $ra, 0x1c($sp)
/* 01C0F0 8001B4F0 8FB00018 */  lw    $s0, 0x18($sp)
/* 01C0F4 8001B4F4 03E00008 */  jr    $ra
/* 01C0F8 8001B4F8 27BD0020 */   addiu $sp, $sp, 0x20

