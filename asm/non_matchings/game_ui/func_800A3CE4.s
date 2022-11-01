glabel func_800A3CE4
/* 0A48E4 800A3CE4 27BDFFA8 */  addiu $sp, $sp, -0x58
/* 0A48E8 800A3CE8 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0A48EC 800A3CEC AFA40058 */  sw    $a0, 0x58($sp)
/* 0A48F0 800A3CF0 0C01BAA8 */  jal   is_game_paused
/* 0A48F4 800A3CF4 AFA5005C */   sw    $a1, 0x5c($sp)
/* 0A48F8 800A3CF8 8FA90058 */  lw    $t1, 0x58($sp)
/* 0A48FC 800A3CFC 14400111 */  bnez  $v0, .L800A4144
/* 0A4900 800A3D00 3C0F8012 */   lui   $t7, %hi(gHUDNumPlayers) # $t7, 0x8012
/* 0A4904 800A3D04 15200008 */  bnez  $t1, .L800A3D28
/* 0A4908 800A3D08 3C03800E */   lui   $v1, %hi(D_800E2770) # $v1, 0x800e
/* 0A490C 800A3D0C 24632770 */  addiu $v1, %lo(D_800E2770) # addiu $v1, $v1, 0x2770
/* 0A4910 800A3D10 806E000C */  lb    $t6, 0xc($v1)
/* 0A4914 800A3D14 2402FFFF */  li    $v0, -1
/* 0A4918 800A3D18 144E0003 */  bne   $v0, $t6, .L800A3D28
/* 0A491C 800A3D1C 00000000 */   nop   
/* 0A4920 800A3D20 A0620003 */  sb    $v0, 3($v1)
/* 0A4924 800A3D24 A0620013 */  sb    $v0, 0x13($v1)
.L800A3D28:
/* 0A4928 800A3D28 8DEF6D0C */  lw    $t7, %lo(gHUDNumPlayers)($t7)
/* 0A492C 800A3D2C 24010001 */  li    $at, 1
/* 0A4930 800A3D30 15E10005 */  bne   $t7, $at, .L800A3D48
/* 0A4934 800A3D34 00000000 */   nop   
/* 0A4938 800A3D38 0C01EFC7 */  jal   func_8007BF1C
/* 0A493C 800A3D3C 24040001 */   li    $a0, 1
/* 0A4940 800A3D40 8FA90058 */  lw    $t1, 0x58($sp)
/* 0A4944 800A3D44 00000000 */  nop   
.L800A3D48:
/* 0A4948 800A3D48 19200083 */  blez  $t1, .L800A3F58
/* 0A494C 800A3D4C 3C088012 */   lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A4950 800A3D50 3C188012 */  lui   $t8, %hi(D_80126D34) # $t8, 0x8012
/* 0A4954 800A3D54 93186D34 */  lbu   $t8, %lo(D_80126D34)($t8)
/* 0A4958 800A3D58 00095A00 */  sll   $t3, $t1, 8
/* 0A495C 800A3D5C 1300002F */  beqz  $t8, .L800A3E1C
/* 0A4960 800A3D60 01695823 */   subu  $t3, $t3, $t1
/* 0A4964 800A3D64 24010028 */  li    $at, 40
/* 0A4968 800A3D68 0161001A */  div   $zero, $t3, $at
/* 0A496C 800A3D6C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4970 800A3D70 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A4974 800A3D74 8C820000 */  lw    $v0, ($a0)
/* 0A4978 800A3D78 2401FF00 */  li    $at, -256
/* 0A497C 800A3D7C 24590008 */  addiu $t9, $v0, 8
/* 0A4980 800A3D80 AC990000 */  sw    $t9, ($a0)
/* 0A4984 800A3D84 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A4988 800A3D88 3C0AFA00 */  lui   $t2, 0xfa00
/* 0A498C 800A3D8C 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A4990 800A3D90 AC4A0000 */  sw    $t2, ($v0)
/* 0A4994 800A3D94 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A4998 800A3D98 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A499C 800A3D9C 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A49A0 800A3DA0 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A49A4 800A3DA4 00006012 */  mflo  $t4
/* 0A49A8 800A3DA8 318D00FF */  andi  $t5, $t4, 0xff
/* 0A49AC 800A3DAC 01A17025 */  or    $t6, $t5, $at
/* 0A49B0 800A3DB0 AC4E0004 */  sw    $t6, 4($v0)
/* 0A49B4 800A3DB4 8D070000 */  lw    $a3, ($t0)
/* 0A49B8 800A3DB8 0C02A980 */  jal   func_800AA600
/* 0A49BC 800A3DBC 24E701A0 */   addiu $a3, $a3, 0x1a0
/* 0A49C0 800A3DC0 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A49C4 800A3DC4 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A49C8 800A3DC8 8C820000 */  lw    $v0, ($a0)
/* 0A49CC 800A3DCC 3C18FA00 */  lui   $t8, 0xfa00
/* 0A49D0 800A3DD0 244F0008 */  addiu $t7, $v0, 8
/* 0A49D4 800A3DD4 AC8F0000 */  sw    $t7, ($a0)
/* 0A49D8 800A3DD8 2419FFFF */  li    $t9, -1
/* 0A49DC 800A3DDC 3C0A8012 */  lui   $t2, %hi(gRaceStartShowHudStep) # $t2, 0x8012
/* 0A49E0 800A3DE0 AC590004 */  sw    $t9, 4($v0)
/* 0A49E4 800A3DE4 AC580000 */  sw    $t8, ($v0)
/* 0A49E8 800A3DE8 814A6CD4 */  lb    $t2, %lo(gRaceStartShowHudStep)($t2)
/* 0A49EC 800A3DEC 24010002 */  li    $at, 2
/* 0A49F0 800A3DF0 1541000A */  bne   $t2, $at, .L800A3E1C
/* 0A49F4 800A3DF4 24040018 */   li    $a0, 24
/* 0A49F8 800A3DF8 3C058012 */  lui   $a1, %hi(gHUDVoiceSoundMask) # $a1, 0x8012
/* 0A49FC 800A3DFC 0C000741 */  jal   play_sound_global
/* 0A4A00 800A3E00 24A56D40 */   addiu $a1, %lo(gHUDVoiceSoundMask) # addiu $a1, $a1, 0x6d40
/* 0A4A04 800A3E04 3C028012 */  lui   $v0, %hi(gRaceStartShowHudStep) # $v0, 0x8012
/* 0A4A08 800A3E08 24426CD4 */  addiu $v0, %lo(gRaceStartShowHudStep) # addiu $v0, $v0, 0x6cd4
/* 0A4A0C 800A3E0C 804B0000 */  lb    $t3, ($v0)
/* 0A4A10 800A3E10 00000000 */  nop   
/* 0A4A14 800A3E14 256C0001 */  addiu $t4, $t3, 1
/* 0A4A18 800A3E18 A04C0000 */  sb    $t4, ($v0)
.L800A3E1C:
/* 0A4A1C 800A3E1C 3C0D8012 */  lui   $t5, %hi(D_80126D3C) # $t5, 0x8012
/* 0A4A20 800A3E20 8DAD6D3C */  lw    $t5, %lo(D_80126D3C)($t5)
/* 0A4A24 800A3E24 00000000 */  nop   
/* 0A4A28 800A3E28 15A000C4 */  bnez  $t5, .L800A413C
/* 0A4A2C 800A3E2C 00000000 */   nop   
/* 0A4A30 800A3E30 0C008D5A */  jal   func_80023568
/* 0A4A34 800A3E34 00000000 */   nop   
/* 0A4A38 800A3E38 144000C0 */  bnez  $v0, .L800A413C
/* 0A4A3C 800A3E3C 00000000 */   nop   
/* 0A4A40 800A3E40 0C006E9D */  jal   get_object_struct_array
/* 0A4A44 800A3E44 27A40038 */   addiu $a0, $sp, 0x38
/* 0A4A48 800A3E48 8FA50038 */  lw    $a1, 0x38($sp)
/* 0A4A4C 800A3E4C AFA20044 */  sw    $v0, 0x44($sp)
/* 0A4A50 800A3E50 0C01BE53 */  jal   get_random_number_from_range
/* 0A4A54 800A3E54 24040001 */   li    $a0, 1
/* 0A4A58 800A3E58 8FAE0044 */  lw    $t6, 0x44($sp)
/* 0A4A5C 800A3E5C 00027880 */  sll   $t7, $v0, 2
/* 0A4A60 800A3E60 01CFC021 */  addu  $t8, $t6, $t7
/* 0A4A64 800A3E64 8F08FFFC */  lw    $t0, -4($t8)
/* 0A4A68 800A3E68 00002025 */  move  $a0, $zero
/* 0A4A6C 800A3E6C 8D030064 */  lw    $v1, 0x64($t0)
/* 0A4A70 800A3E70 24050064 */  li    $a1, 100
/* 0A4A74 800A3E74 807901D6 */  lb    $t9, 0x1d6($v1)
/* 0A4A78 800A3E78 00000000 */  nop   
/* 0A4A7C 800A3E7C 172000AF */  bnez  $t9, .L800A413C
/* 0A4A80 800A3E80 00000000 */   nop   
/* 0A4A84 800A3E84 0C01BE53 */  jal   get_random_number_from_range
/* 0A4A88 800A3E88 AFA80040 */   sw    $t0, 0x40($sp)
/* 0A4A8C 800A3E8C 8FA80040 */  lw    $t0, 0x40($sp)
/* 0A4A90 800A3E90 28410060 */  slti  $at, $v0, 0x60
/* 0A4A94 800A3E94 142000A9 */  bnez  $at, .L800A413C
/* 0A4A98 800A3E98 00002025 */   move  $a0, $zero
/* 0A4A9C 800A3E9C 24050007 */  li    $a1, 7
/* 0A4AA0 800A3EA0 0C01BE53 */  jal   get_random_number_from_range
/* 0A4AA4 800A3EA4 AFA80040 */   sw    $t0, 0x40($sp)
/* 0A4AA8 800A3EA8 44822000 */  mtc1  $v0, $f4
/* 0A4AAC 800A3EAC 3C013FE0 */  li    $at, 0x3FE00000 # 1.750000
/* 0A4AB0 800A3EB0 468021A1 */  cvt.d.w $f6, $f4
/* 0A4AB4 800A3EB4 44814800 */  mtc1  $at, $f9
/* 0A4AB8 800A3EB8 44804000 */  mtc1  $zero, $f8
/* 0A4ABC 800A3EBC 3C01401C */  li    $at, 0x401C0000 # 2.437500
/* 0A4AC0 800A3EC0 46283282 */  mul.d $f10, $f6, $f8
/* 0A4AC4 800A3EC4 44818800 */  mtc1  $at, $f17
/* 0A4AC8 800A3EC8 44808000 */  mtc1  $zero, $f16
/* 0A4ACC 800A3ECC 3C013FF4 */  li    $at, 0x3FF40000 # 1.906250
/* 0A4AD0 800A3ED0 44812800 */  mtc1  $at, $f5
/* 0A4AD4 800A3ED4 46305483 */  div.d $f18, $f10, $f16
/* 0A4AD8 800A3ED8 44802000 */  mtc1  $zero, $f4
/* 0A4ADC 800A3EDC 00002025 */  move  $a0, $zero
/* 0A4AE0 800A3EE0 24050007 */  li    $a1, 7
/* 0A4AE4 800A3EE4 46322181 */  sub.d $f6, $f4, $f18
/* 0A4AE8 800A3EE8 46203220 */  cvt.s.d $f8, $f6
/* 0A4AEC 800A3EEC 0C01BE53 */  jal   get_random_number_from_range
/* 0A4AF0 800A3EF0 E7A8004C */   swc1  $f8, 0x4c($sp)
/* 0A4AF4 800A3EF4 00025980 */  sll   $t3, $v0, 6
/* 0A4AF8 800A3EF8 01625823 */  subu  $t3, $t3, $v0
/* 0A4AFC 800A3EFC 24010007 */  li    $at, 7
/* 0A4B00 800A3F00 0161001A */  div   $zero, $t3, $at
/* 0A4B04 800A3F04 8FA80040 */  lw    $t0, 0x40($sp)
/* 0A4B08 800A3F08 3C0142C8 */  li    $at, 0x42C80000 # 100.000000
/* 0A4B0C 800A3F0C 44818000 */  mtc1  $at, $f16
/* 0A4B10 800A3F10 C7AA004C */  lwc1  $f10, 0x4c($sp)
/* 0A4B14 800A3F14 8D05000C */  lw    $a1, 0xc($t0)
/* 0A4B18 800A3F18 8D060010 */  lw    $a2, 0x10($t0)
/* 0A4B1C 800A3F1C 8D070014 */  lw    $a3, 0x14($t0)
/* 0A4B20 800A3F20 46105102 */  mul.s $f4, $f10, $f16
/* 0A4B24 800A3F24 3C0E8012 */  lui   $t6, %hi(D_80126D3C) # $t6, 0x8012
/* 0A4B28 800A3F28 25CE6D3C */  addiu $t6, %lo(D_80126D3C) # addiu $t6, $t6, 0x6d3c
/* 0A4B2C 800A3F2C 240A0004 */  li    $t2, 4
/* 0A4B30 800A3F30 AFAA0010 */  sw    $t2, 0x10($sp)
/* 0A4B34 800A3F34 AFAE001C */  sw    $t6, 0x1c($sp)
/* 0A4B38 800A3F38 E7A40018 */  swc1  $f4, 0x18($sp)
/* 0A4B3C 800A3F3C 2404004C */  li    $a0, 76
/* 0A4B40 800A3F40 00006012 */  mflo  $t4
/* 0A4B44 800A3F44 258D0018 */  addiu $t5, $t4, 0x18
/* 0A4B48 800A3F48 0C00257A */  jal   func_800095E8
/* 0A4B4C 800A3F4C AFAD0014 */   sw    $t5, 0x14($sp)
/* 0A4B50 800A3F50 1000007A */  b     .L800A413C
/* 0A4B54 800A3F54 00000000 */   nop   
.L800A3F58:
/* 0A4B58 800A3F58 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A4B5C 800A3F5C 8D0F0000 */  lw    $t7, ($t0)
/* 0A4B60 800A3F60 3C01C348 */  li    $at, 0xC3480000 # -200.000000
/* 0A4B64 800A3F64 44819000 */  mtc1  $at, $f18
/* 0A4B68 800A3F68 C5E6018C */  lwc1  $f6, 0x18c($t7)
/* 0A4B6C 800A3F6C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4B70 800A3F70 4606903C */  c.lt.s $f18, $f6
/* 0A4B74 800A3F74 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A4B78 800A3F78 45000070 */  bc1f  .L800A413C
/* 0A4B7C 800A3F7C 3C19FA00 */   lui   $t9, 0xfa00
/* 0A4B80 800A3F80 8C820000 */  lw    $v0, ($a0)
/* 0A4B84 800A3F84 240AFFA0 */  li    $t2, -96
/* 0A4B88 800A3F88 24580008 */  addiu $t8, $v0, 8
/* 0A4B8C 800A3F8C AC980000 */  sw    $t8, ($a0)
/* 0A4B90 800A3F90 AC4A0004 */  sw    $t2, 4($v0)
/* 0A4B94 800A3F94 AC590000 */  sw    $t9, ($v0)
/* 0A4B98 800A3F98 8D070000 */  lw    $a3, ($t0)
/* 0A4B9C 800A3F9C 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A4BA0 800A3FA0 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A4BA4 800A3FA4 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A4BA8 800A3FA8 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A4BAC 800A3FAC 0C02A980 */  jal   func_800AA600
/* 0A4BB0 800A3FB0 24E70180 */   addiu $a3, $a3, 0x180
/* 0A4BB4 800A3FB4 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4BB8 800A3FB8 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A4BBC 800A3FBC 8C820000 */  lw    $v0, ($a0)
/* 0A4BC0 800A3FC0 3C0CFA00 */  lui   $t4, 0xfa00
/* 0A4BC4 800A3FC4 244B0008 */  addiu $t3, $v0, 8
/* 0A4BC8 800A3FC8 AC8B0000 */  sw    $t3, ($a0)
/* 0A4BCC 800A3FCC 240DFFFF */  li    $t5, -1
/* 0A4BD0 800A3FD0 3C078012 */  lui   $a3, %hi(D_80126D08) # $a3, 0x8012
/* 0A4BD4 800A3FD4 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A4BD8 800A3FD8 AC4D0004 */  sw    $t5, 4($v0)
/* 0A4BDC 800A3FDC AC4C0000 */  sw    $t4, ($v0)
/* 0A4BE0 800A3FE0 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A4BE4 800A3FE4 24E76D08 */  addiu $a3, %lo(D_80126D08) # addiu $a3, $a3, 0x6d08
/* 0A4BE8 800A3FE8 8CEF0000 */  lw    $t7, ($a3)
/* 0A4BEC 800A3FEC 8D0E0000 */  lw    $t6, ($t0)
/* 0A4BF0 800A3FF0 8FB9005C */  lw    $t9, 0x5c($sp)
/* 0A4BF4 800A3FF4 01CF2821 */  addu  $a1, $t6, $t7
/* 0A4BF8 800A3FF8 80B8019A */  lb    $t8, 0x19a($a1)
/* 0A4BFC 800A3FFC 3C0E8012 */  lui   $t6, %hi(gRaceStartShowHudStep) # $t6, 0x8012
/* 0A4C00 800A4000 03195021 */  addu  $t2, $t8, $t9
/* 0A4C04 800A4004 A0AA019A */  sb    $t2, 0x19a($a1)
/* 0A4C08 800A4008 8CEB0000 */  lw    $t3, ($a3)
/* 0A4C0C 800A400C 8D060000 */  lw    $a2, ($t0)
/* 0A4C10 800A4010 00000000 */  nop   
/* 0A4C14 800A4014 00CB6021 */  addu  $t4, $a2, $t3
/* 0A4C18 800A4018 818D019A */  lb    $t5, 0x19a($t4)
/* 0A4C1C 800A401C 00000000 */  nop   
/* 0A4C20 800A4020 29A1003C */  slti  $at, $t5, 0x3c
/* 0A4C24 800A4024 14200025 */  bnez  $at, .L800A40BC
/* 0A4C28 800A4028 00000000 */   nop   
/* 0A4C2C 800A402C 81CE6CD4 */  lb    $t6, %lo(gRaceStartShowHudStep)($t6)
/* 0A4C30 800A4030 24010004 */  li    $at, 4
/* 0A4C34 800A4034 15C1001A */  bne   $t6, $at, .L800A40A0
/* 0A4C38 800A4038 8FB9005C */   lw    $t9, 0x5c($sp)
/* 0A4C3C 800A403C 0C019884 */  jal   get_viewport_count
/* 0A4C40 800A4040 00000000 */   nop   
/* 0A4C44 800A4044 28410002 */  slti  $at, $v0, 2
/* 0A4C48 800A4048 14200006 */  bnez  $at, .L800A4064
/* 0A4C4C 800A404C 3C013F80 */   lui   $at, 0x3f80
/* 0A4C50 800A4050 0C0002CD */  jal   play_music
/* 0A4C54 800A4054 00002025 */   move  $a0, $zero
/* 0A4C58 800A4058 10000006 */  b     .L800A4074
/* 0A4C5C 800A405C 24040016 */   li    $a0, 22
/* 0A4C60 800A4060 3C013F80 */  li    $at, 0x3F800000 # 1.000000
.L800A4064:
/* 0A4C64 800A4064 44816000 */  mtc1  $at, $f12
/* 0A4C68 800A4068 0C01AF44 */  jal   func_8006BD10
/* 0A4C6C 800A406C 00000000 */   nop   
/* 0A4C70 800A4070 24040016 */  li    $a0, 22
.L800A4074:
/* 0A4C74 800A4074 0C000741 */  jal   play_sound_global
/* 0A4C78 800A4078 00002825 */   move  $a1, $zero
/* 0A4C7C 800A407C 3C028012 */  lui   $v0, %hi(gRaceStartShowHudStep) # $v0, 0x8012
/* 0A4C80 800A4080 24426CD4 */  addiu $v0, %lo(gRaceStartShowHudStep) # addiu $v0, $v0, 0x6cd4
/* 0A4C84 800A4084 804F0000 */  lb    $t7, ($v0)
/* 0A4C88 800A4088 3C068012 */  lui   $a2, %hi(D_80126CDC) # $a2, 0x8012
/* 0A4C8C 800A408C 25F80001 */  addiu $t8, $t7, 1
/* 0A4C90 800A4090 A0580000 */  sb    $t8, ($v0)
/* 0A4C94 800A4094 8CC66CDC */  lw    $a2, %lo(D_80126CDC)($a2)
/* 0A4C98 800A4098 00000000 */  nop   
/* 0A4C9C 800A409C 8FB9005C */  lw    $t9, 0x5c($sp)
.L800A40A0:
/* 0A4CA0 800A40A0 C4C8018C */  lwc1  $f8, 0x18c($a2)
/* 0A4CA4 800A40A4 001950C0 */  sll   $t2, $t9, 3
/* 0A4CA8 800A40A8 448A5000 */  mtc1  $t2, $f10
/* 0A4CAC 800A40AC 00000000 */  nop   
/* 0A4CB0 800A40B0 46805420 */  cvt.s.w $f16, $f10
/* 0A4CB4 800A40B4 46104101 */  sub.s $f4, $f8, $f16
/* 0A4CB8 800A40B8 E4C4018C */  swc1  $f4, 0x18c($a2)
.L800A40BC:
/* 0A4CBC 800A40BC 3C0B8012 */  lui   $t3, %hi(gRaceStartShowHudStep) # $t3, 0x8012
/* 0A4CC0 800A40C0 816B6CD4 */  lb    $t3, %lo(gRaceStartShowHudStep)($t3)
/* 0A4CC4 800A40C4 24010003 */  li    $at, 3
/* 0A4CC8 800A40C8 1561001C */  bne   $t3, $at, .L800A413C
/* 0A4CCC 800A40CC 24040019 */   li    $a0, 25
/* 0A4CD0 800A40D0 3C058012 */  lui   $a1, %hi(gHUDVoiceSoundMask) # $a1, 0x8012
/* 0A4CD4 800A40D4 0C000741 */  jal   play_sound_global
/* 0A4CD8 800A40D8 24A56D40 */   addiu $a1, %lo(gHUDVoiceSoundMask) # addiu $a1, $a1, 0x6d40
/* 0A4CDC 800A40DC 0C006D90 */  jal   func_8001B640
/* 0A4CE0 800A40E0 00000000 */   nop   
/* 0A4CE4 800A40E4 1040000D */  beqz  $v0, .L800A411C
/* 0A4CE8 800A40E8 00000000 */   nop   
/* 0A4CEC 800A40EC 0C006D94 */  jal   func_8001B650
/* 0A4CF0 800A40F0 00000000 */   nop   
/* 0A4CF4 800A40F4 14400009 */  bnez  $v0, .L800A411C
/* 0A4CF8 800A40F8 2404024B */   li    $a0, 587
/* 0A4CFC 800A40FC 3C053FD9 */  lui   $a1, (0x3FD9999A >> 16) # lui $a1, 0x3fd9
/* 0A4D00 800A4100 34A5999A */  ori   $a1, (0x3FD9999A & 0xFFFF) # ori $a1, $a1, 0x999a
/* 0A4D04 800A4104 0C029D21 */  jal   func_800A7484
/* 0A4D08 800A4108 00003025 */   move  $a2, $zero
/* 0A4D0C 800A410C 3C053FD9 */  lui   $a1, (0x3FD9999A >> 16) # lui $a1, 0x3fd9
/* 0A4D10 800A4110 34A5999A */  ori   $a1, (0x3FD9999A & 0xFFFF) # ori $a1, $a1, 0x999a
/* 0A4D14 800A4114 0C030C56 */  jal   func_800C3158
/* 0A4D18 800A4118 24040052 */   li    $a0, 82
.L800A411C:
/* 0A4D1C 800A411C 3C0D8012 */  lui   $t5, %hi(gRaceStartShowHudStep) # $t5, 0x8012
/* 0A4D20 800A4120 81AD6CD4 */  lb    $t5, %lo(gRaceStartShowHudStep)($t5)
/* 0A4D24 800A4124 240C0001 */  li    $t4, 1
/* 0A4D28 800A4128 3C018012 */  lui   $at, %hi(D_80126D70) # $at, 0x8012
/* 0A4D2C 800A412C A02C6D70 */  sb    $t4, %lo(D_80126D70)($at)
/* 0A4D30 800A4130 3C018012 */  lui   $at, %hi(gRaceStartShowHudStep) # $at, 0x8012
/* 0A4D34 800A4134 25AE0001 */  addiu $t6, $t5, 1
/* 0A4D38 800A4138 A02E6CD4 */  sb    $t6, %lo(gRaceStartShowHudStep)($at)
.L800A413C:
/* 0A4D3C 800A413C 0C01EFC7 */  jal   func_8007BF1C
/* 0A4D40 800A4140 00002025 */   move  $a0, $zero
.L800A4144:
/* 0A4D44 800A4144 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0A4D48 800A4148 27BD0058 */  addiu $sp, $sp, 0x58
/* 0A4D4C 800A414C 03E00008 */  jr    $ra
/* 0A4D50 800A4150 00000000 */   nop   

