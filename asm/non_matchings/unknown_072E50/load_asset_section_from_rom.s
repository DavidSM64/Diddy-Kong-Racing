glabel func_80076CF0
/* 0778F0 80076CF0 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0778F4 80076CF4 3C028012 */  lui   $v0, %hi(gAssetsLookupTable) # $v0, 0x8012
/* 0778F8 80076CF8 8C424290 */  lw    $v0, %lo(gAssetsLookupTable)($v0)
/* 0778FC 80076CFC AFBF0014 */  sw    $ra, 0x14($sp)
/* 077900 80076D00 AFA5003C */  sw    $a1, 0x3c($sp)
/* 077904 80076D04 8C4E0000 */  lw    $t6, ($v0)
/* 077908 80076D08 00803025 */  move  $a2, $a0
/* 07790C 80076D0C 01C4082B */  sltu  $at, $t6, $a0
/* 077910 80076D10 10200003 */  beqz  $at, .L80076D20
/* 077914 80076D14 24C60001 */   addiu $a2, $a2, 1
/* 077918 80076D18 10000034 */  b     .L80076DEC
/* 07791C 80076D1C 00001025 */   move  $v0, $zero
.L80076D20:
/* 077920 80076D20 00067880 */  sll   $t7, $a2, 2
/* 077924 80076D24 01E23821 */  addu  $a3, $t7, $v0
/* 077928 80076D28 8CE30000 */  lw    $v1, ($a3)
/* 07792C 80076D2C 8CF80004 */  lw    $t8, 4($a3)
/* 077930 80076D30 24040008 */  li    $a0, 8
/* 077934 80076D34 0303C823 */  subu  $t9, $t8, $v1
/* 077938 80076D38 AFB90034 */  sw    $t9, 0x34($sp)
/* 07793C 80076D3C 2405FFFF */  li    $a1, -1
/* 077940 80076D40 0C01C327 */  jal   allocate_from_main_pool_safe
/* 077944 80076D44 AFA30030 */   sw    $v1, 0x30($sp)
/* 077948 80076D48 8FA30030 */  lw    $v1, 0x30($sp)
/* 07794C 80076D4C 3C08000F */  lui   $t0, %hi(__ASSETS_LUT_END) # $t0, 0xf
/* 077950 80076D50 2508CC30 */  addiu $t0, %lo(__ASSETS_LUT_END) # addiu $t0, $t0, -0x33d0
/* 077954 80076D54 00682021 */  addu  $a0, $v1, $t0
/* 077958 80076D58 AFA20028 */  sw    $v0, 0x28($sp)
/* 07795C 80076D5C AFA40020 */  sw    $a0, 0x20($sp)
/* 077960 80076D60 00402825 */  move  $a1, $v0
/* 077964 80076D64 0C01DBDE */  jal   dmacopy
/* 077968 80076D68 24060008 */   li    $a2, 8
/* 07796C 80076D6C 8FA40028 */  lw    $a0, 0x28($sp)
/* 077970 80076D70 0C03186B */  jal   byteswap32
/* 077974 80076D74 00000000 */   nop   
/* 077978 80076D78 8FA9003C */  lw    $t1, 0x3c($sp)
/* 07797C 80076D7C 8FA40028 */  lw    $a0, 0x28($sp)
/* 077980 80076D80 00495021 */  addu  $t2, $v0, $t1
/* 077984 80076D84 0C01C450 */  jal   func_80071140
/* 077988 80076D88 AFAA002C */   sw    $t2, 0x2c($sp)
/* 07798C 80076D8C 8FAB002C */  lw    $t3, 0x2c($sp)
/* 077990 80076D90 8FAC003C */  lw    $t4, 0x3c($sp)
/* 077994 80076D94 3C057F7F */  lui   $a1, (0x7F7F7FFF >> 16) # lui $a1, 0x7f7f
/* 077998 80076D98 34A57FFF */  ori   $a1, (0x7F7F7FFF & 0xFFFF) # ori $a1, $a1, 0x7fff
/* 07799C 80076D9C 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0779A0 80076DA0 016C2021 */   addu  $a0, $t3, $t4
/* 0779A4 80076DA4 14400003 */  bnez  $v0, .L80076DB4
/* 0779A8 80076DA8 00403825 */   move  $a3, $v0
/* 0779AC 80076DAC 1000000F */  b     .L80076DEC
/* 0779B0 80076DB0 00001025 */   move  $v0, $zero
.L80076DB4:
/* 0779B4 80076DB4 8FAD002C */  lw    $t5, 0x2c($sp)
/* 0779B8 80076DB8 8FA60034 */  lw    $a2, 0x34($sp)
/* 0779BC 80076DBC 00ED7021 */  addu  $t6, $a3, $t5
/* 0779C0 80076DC0 8FA40020 */  lw    $a0, 0x20($sp)
/* 0779C4 80076DC4 01C62823 */  subu  $a1, $t6, $a2
/* 0779C8 80076DC8 AFA5001C */  sw    $a1, 0x1c($sp)
/* 0779CC 80076DCC 0C01DBDE */  jal   dmacopy
/* 0779D0 80076DD0 AFA70024 */   sw    $a3, 0x24($sp)
/* 0779D4 80076DD4 8FA50024 */  lw    $a1, 0x24($sp)
/* 0779D8 80076DD8 8FA4001C */  lw    $a0, 0x1c($sp)
/* 0779DC 80076DDC 0C031886 */  jal   func_800C6218
/* 0779E0 80076DE0 00000000 */   nop   
/* 0779E4 80076DE4 8FA20024 */  lw    $v0, 0x24($sp)
/* 0779E8 80076DE8 00000000 */  nop   
.L80076DEC:
/* 0779EC 80076DEC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0779F0 80076DF0 27BD0038 */  addiu $sp, $sp, 0x38
/* 0779F4 80076DF4 03E00008 */  jr    $ra
/* 0779F8 80076DF8 00000000 */   nop   
