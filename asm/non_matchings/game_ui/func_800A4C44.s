glabel func_800A4C44
/* 0A5844 800A4C44 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0A5848 800A4C48 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0A584C 800A4C4C AFA5003C */  sw    $a1, 0x3c($sp)
/* 0A5850 800A4C50 808E01D8 */  lb    $t6, 0x1d8($a0)
/* 0A5854 800A4C54 00000000 */  nop   
/* 0A5858 800A4C58 15C000BA */  bnez  $t6, .L800A4F44
/* 0A585C 800A4C5C 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0A5860 800A4C60 848301AE */  lh    $v1, 0x1ae($a0)
/* 0A5864 800A4C64 0C0044E7 */  jal   func_8001139C
/* 0A5868 800A4C68 AFA30034 */   sw    $v1, 0x34($sp)
/* 0A586C 800A4C6C 8FA30034 */  lw    $v1, 0x34($sp)
/* 0A5870 800A4C70 1040001B */  beqz  $v0, .L800A4CE0
/* 0A5874 800A4C74 00000000 */   nop   
/* 0A5878 800A4C78 0C01AF66 */  jal   get_current_level_race_type
/* 0A587C 800A4C7C 00000000 */   nop   
/* 0A5880 800A4C80 24010008 */  li    $at, 8
/* 0A5884 800A4C84 10410005 */  beq   $v0, $at, .L800A4C9C
/* 0A5888 800A4C88 00000000 */   nop   
/* 0A588C 800A4C8C 0C008D07 */  jal   is_taj_challenge
/* 0A5890 800A4C90 00000000 */   nop   
/* 0A5894 800A4C94 10400003 */  beqz  $v0, .L800A4CA4
/* 0A5898 800A4C98 00000000 */   nop   
.L800A4C9C:
/* 0A589C 800A4C9C 10000010 */  b     .L800A4CE0
/* 0A58A0 800A4CA0 24030002 */   li    $v1, 2
.L800A4CA4:
/* 0A58A4 800A4CA4 0C01BAA4 */  jal   get_settings
/* 0A58A8 800A4CA8 00000000 */   nop   
/* 0A58AC 800A4CAC 3C0F8012 */  lui   $t7, %hi(D_80126D10) # $t7, 0x8012
/* 0A58B0 800A4CB0 8DEF6D10 */  lw    $t7, %lo(D_80126D10)($t7)
/* 0A58B4 800A4CB4 3C088012 */  lui   $t0, %hi(gCurrentHud) # $t0, 0x8012
/* 0A58B8 800A4CB8 000FC080 */  sll   $t8, $t7, 2
/* 0A58BC 800A4CBC 030FC023 */  subu  $t8, $t8, $t7
/* 0A58C0 800A4CC0 0018C0C0 */  sll   $t8, $t8, 3
/* 0A58C4 800A4CC4 25086CDC */  addiu $t0, %lo(gCurrentHud) # addiu $t0, $t0, 0x6cdc
/* 0A58C8 800A4CC8 0058C821 */  addu  $t9, $v0, $t8
/* 0A58CC 800A4CCC 8323005A */  lb    $v1, 0x5a($t9)
/* 0A58D0 800A4CD0 8D090000 */  lw    $t1, ($t0)
/* 0A58D4 800A4CD4 00000000 */  nop   
/* 0A58D8 800A4CD8 A5230018 */  sh    $v1, 0x18($t1)
/* 0A58DC 800A4CDC 24630001 */  addiu $v1, $v1, 1
.L800A4CE0:
/* 0A58E0 800A4CE0 3C0A8012 */  lui   $t2, %hi(gHUDNumPlayers) # $t2, 0x8012
/* 0A58E4 800A4CE4 8D4A6D0C */  lw    $t2, %lo(gHUDNumPlayers)($t2)
/* 0A58E8 800A4CE8 3C088012 */  lui   $t0, %hi(gCurrentHud) # $t0, 0x8012
/* 0A58EC 800A4CEC 29410002 */  slti  $at, $t2, 2
/* 0A58F0 800A4CF0 10200017 */  beqz  $at, .L800A4D50
/* 0A58F4 800A4CF4 25086CDC */   addiu $t0, %lo(gCurrentHud) # addiu $t0, $t0, 0x6cdc
/* 0A58F8 800A4CF8 28610004 */  slti  $at, $v1, 4
/* 0A58FC 800A4CFC 10200005 */  beqz  $at, .L800A4D14
/* 0A5900 800A4D00 3C048012 */   lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5904 800A4D04 8D0C0000 */  lw    $t4, ($t0)
/* 0A5908 800A4D08 246BFFFF */  addiu $t3, $v1, -1
/* 0A590C 800A4D0C 10000004 */  b     .L800A4D20
/* 0A5910 800A4D10 A58B0038 */   sh    $t3, 0x38($t4)
.L800A4D14:
/* 0A5914 800A4D14 8D0E0000 */  lw    $t6, ($t0)
/* 0A5918 800A4D18 240D0003 */  li    $t5, 3
/* 0A591C 800A4D1C A5CD0038 */  sh    $t5, 0x38($t6)
.L800A4D20:
/* 0A5920 800A4D20 8D070000 */  lw    $a3, ($t0)
/* 0A5924 800A4D24 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A5928 800A4D28 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A592C 800A4D2C 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A5930 800A4D30 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A5934 800A4D34 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5938 800A4D38 AFA30034 */  sw    $v1, 0x34($sp)
/* 0A593C 800A4D3C 0C02A980 */  jal   func_800AA600
/* 0A5940 800A4D40 24E70020 */   addiu $a3, $a3, 0x20
/* 0A5944 800A4D44 3C088012 */  lui   $t0, %hi(gCurrentHud) # $t0, 0x8012
/* 0A5948 800A4D48 8FA30034 */  lw    $v1, 0x34($sp)
/* 0A594C 800A4D4C 25086CDC */  addiu $t0, %lo(gCurrentHud) # addiu $t0, $t0, 0x6cdc
.L800A4D50:
/* 0A5950 800A4D50 8D0F0000 */  lw    $t7, ($t0)
/* 0A5954 800A4D54 3C014300 */  li    $at, 0x43000000 # 128.000000
/* 0A5958 800A4D58 81F8001B */  lb    $t8, 0x1b($t7)
/* 0A595C 800A4D5C 44813000 */  mtc1  $at, $f6
/* 0A5960 800A4D60 27190081 */  addiu $t9, $t8, 0x81
/* 0A5964 800A4D64 44992000 */  mtc1  $t9, $f4
/* 0A5968 800A4D68 246CFFFF */  addiu $t4, $v1, -1
/* 0A596C 800A4D6C 46802020 */  cvt.s.w $f0, $f4
/* 0A5970 800A4D70 AFAC001C */  sw    $t4, 0x1c($sp)
/* 0A5974 800A4D74 46060002 */  mul.s $f0, $f0, $f6
/* 0A5978 800A4D78 4449F800 */  cfc1  $t1, $31
/* 0A597C 800A4D7C 00000000 */  nop   
/* 0A5980 800A4D80 35210003 */  ori   $at, $t1, 3
/* 0A5984 800A4D84 38210002 */  xori  $at, $at, 2
/* 0A5988 800A4D88 44C1F800 */  ctc1  $at, $31
/* 0A598C 800A4D8C 00000000 */  nop   
/* 0A5990 800A4D90 46000224 */  cvt.w.s $f8, $f0
/* 0A5994 800A4D94 44044000 */  mfc1  $a0, $f8
/* 0A5998 800A4D98 44C9F800 */  ctc1  $t1, $31
/* 0A599C 800A4D9C 00045400 */  sll   $t2, $a0, 0x10
/* 0A59A0 800A4DA0 0C01C1F1 */  jal   sins_f
/* 0A59A4 800A4DA4 000A2403 */   sra   $a0, $t2, 0x10
/* 0A59A8 800A4DA8 3C088012 */  lui   $t0, %hi(gCurrentHud) # $t0, 0x8012
/* 0A59AC 800A4DAC 25086CDC */  addiu $t0, %lo(gCurrentHud) # addiu $t0, $t0, 0x6cdc
/* 0A59B0 800A4DB0 8D020000 */  lw    $v0, ($t0)
/* 0A59B4 800A4DB4 3C0142FE */  li    $at, 0x42FE0000 # 127.000000
/* 0A59B8 800A4DB8 804D001C */  lb    $t5, 0x1c($v0)
/* 0A59BC 800A4DBC 44819000 */  mtc1  $at, $f18
/* 0A59C0 800A4DC0 448D5000 */  mtc1  $t5, $f10
/* 0A59C4 800A4DC4 3C013FE0 */  li    $at, 0x3FE00000 # 1.750000
/* 0A59C8 800A4DC8 46805420 */  cvt.s.w $f16, $f10
/* 0A59CC 800A4DCC 44814800 */  mtc1  $at, $f9
/* 0A59D0 800A4DD0 44804000 */  mtc1  $zero, $f8
/* 0A59D4 800A4DD4 46128103 */  div.s $f4, $f16, $f18
/* 0A59D8 800A4DD8 460002A1 */  cvt.d.s $f10, $f0
/* 0A59DC 800A4DDC 462A4402 */  mul.d $f16, $f8, $f10
/* 0A59E0 800A4DE0 3C013FF0 */  li    $at, 0x3FF00000 # 1.875000
/* 0A59E4 800A4DE4 44819800 */  mtc1  $at, $f19
/* 0A59E8 800A4DE8 44809000 */  mtc1  $zero, $f18
/* 0A59EC 800A4DEC 3C0141C0 */  li    $at, 0x41C00000 # 24.000000
/* 0A59F0 800A4DF0 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A59F4 800A4DF4 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A59F8 800A4DF8 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A59FC 800A4DFC 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A5A00 800A4E00 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A5A04 800A4E04 460021A1 */  cvt.d.s $f6, $f4
/* 0A5A08 800A4E08 46309100 */  add.d $f4, $f18, $f16
/* 0A5A0C 800A4E0C 44819000 */  mtc1  $at, $f18
/* 0A5A10 800A4E10 46243200 */  add.d $f8, $f6, $f4
/* 0A5A14 800A4E14 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5A18 800A4E18 462042A0 */  cvt.s.d $f10, $f8
/* 0A5A1C 800A4E1C E44A0008 */  swc1  $f10, 8($v0)
/* 0A5A20 800A4E20 8D020000 */  lw    $v0, ($t0)
/* 0A5A24 800A4E24 00000000 */  nop   
/* 0A5A28 800A4E28 C442000C */  lwc1  $f2, 0xc($v0)
/* 0A5A2C 800A4E2C 00000000 */  nop   
/* 0A5A30 800A4E30 E7A20030 */  swc1  $f2, 0x30($sp)
/* 0A5A34 800A4E34 C4500008 */  lwc1  $f16, 8($v0)
/* 0A5A38 800A4E38 00000000 */  nop   
/* 0A5A3C 800A4E3C 46109182 */  mul.s $f6, $f18, $f16
/* 0A5A40 800A4E40 46061101 */  sub.s $f4, $f2, $f6
/* 0A5A44 800A4E44 E444000C */  swc1  $f4, 0xc($v0)
/* 0A5A48 800A4E48 8D070000 */  lw    $a3, ($t0)
/* 0A5A4C 800A4E4C 0C02A980 */  jal   func_800AA600
/* 0A5A50 800A4E50 00000000 */   nop   
/* 0A5A54 800A4E54 3C088012 */  lui   $t0, %hi(gCurrentHud) # $t0, 0x8012
/* 0A5A58 800A4E58 25086CDC */  addiu $t0, %lo(gCurrentHud) # addiu $t0, $t0, 0x6cdc
/* 0A5A5C 800A4E5C 8D0E0000 */  lw    $t6, ($t0)
/* 0A5A60 800A4E60 C7A80030 */  lwc1  $f8, 0x30($sp)
/* 0A5A64 800A4E64 2405007F */  li    $a1, 127
/* 0A5A68 800A4E68 E5C8000C */  swc1  $f8, 0xc($t6)
/* 0A5A6C 800A4E6C 8D020000 */  lw    $v0, ($t0)
/* 0A5A70 800A4E70 8FA4003C */  lw    $a0, 0x3c($sp)
/* 0A5A74 800A4E74 804F001A */  lb    $t7, 0x1a($v0)
/* 0A5A78 800A4E78 0004C100 */  sll   $t8, $a0, 4
/* 0A5A7C 800A4E7C 11E0000D */  beqz  $t7, .L800A4EB4
/* 0A5A80 800A4E80 00000000 */   nop   
/* 0A5A84 800A4E84 8043001B */  lb    $v1, 0x1b($v0)
/* 0A5A88 800A4E88 00B8C823 */  subu  $t9, $a1, $t8
/* 0A5A8C 800A4E8C 0079082A */  slt   $at, $v1, $t9
/* 0A5A90 800A4E90 10200005 */  beqz  $at, .L800A4EA8
/* 0A5A94 800A4E94 00784821 */   addu  $t1, $v1, $t8
/* 0A5A98 800A4E98 A049001B */  sb    $t1, 0x1b($v0)
/* 0A5A9C 800A4E9C 8D020000 */  lw    $v0, ($t0)
/* 0A5AA0 800A4EA0 10000005 */  b     .L800A4EB8
/* 0A5AA4 800A4EA4 8FA4001C */   lw    $a0, 0x1c($sp)
.L800A4EA8:
/* 0A5AA8 800A4EA8 A045001B */  sb    $a1, 0x1b($v0)
/* 0A5AAC 800A4EAC 8D020000 */  lw    $v0, ($t0)
/* 0A5AB0 800A4EB0 00000000 */  nop   
.L800A4EB4:
/* 0A5AB4 800A4EB4 8FA4001C */  lw    $a0, 0x1c($sp)
.L800A4EB8:
/* 0A5AB8 800A4EB8 844A0018 */  lh    $t2, 0x18($v0)
/* 0A5ABC 800A4EBC 2405007F */  li    $a1, 127
/* 0A5AC0 800A4EC0 108A0013 */  beq   $a0, $t2, .L800A4F10
/* 0A5AC4 800A4EC4 00000000 */   nop   
/* 0A5AC8 800A4EC8 804B001A */  lb    $t3, 0x1a($v0)
/* 0A5ACC 800A4ECC 240DFF81 */  li    $t5, -127
/* 0A5AD0 800A4ED0 11600009 */  beqz  $t3, .L800A4EF8
/* 0A5AD4 800A4ED4 00000000 */   nop   
/* 0A5AD8 800A4ED8 8043001B */  lb    $v1, 0x1b($v0)
/* 0A5ADC 800A4EDC 00000000 */  nop   
/* 0A5AE0 800A4EE0 18600005 */  blez  $v1, .L800A4EF8
/* 0A5AE4 800A4EE4 00036023 */   negu  $t4, $v1
/* 0A5AE8 800A4EE8 A04C001B */  sb    $t4, 0x1b($v0)
/* 0A5AEC 800A4EEC 8D020000 */  lw    $v0, ($t0)
/* 0A5AF0 800A4EF0 10000008 */  b     .L800A4F14
/* 0A5AF4 800A4EF4 A4440018 */   sh    $a0, 0x18($v0)
.L800A4EF8:
/* 0A5AF8 800A4EF8 A04D001B */  sb    $t5, 0x1b($v0)
/* 0A5AFC 800A4EFC 8D0F0000 */  lw    $t7, ($t0)
/* 0A5B00 800A4F00 240E0001 */  li    $t6, 1
/* 0A5B04 800A4F04 A1EE001A */  sb    $t6, 0x1a($t7)
/* 0A5B08 800A4F08 8D020000 */  lw    $v0, ($t0)
/* 0A5B0C 800A4F0C 00000000 */  nop   
.L800A4F10:
/* 0A5B10 800A4F10 A4440018 */  sh    $a0, 0x18($v0)
.L800A4F14:
/* 0A5B14 800A4F14 8D020000 */  lw    $v0, ($t0)
/* 0A5B18 800A4F18 00000000 */  nop   
/* 0A5B1C 800A4F1C 8058001A */  lb    $t8, 0x1a($v0)
/* 0A5B20 800A4F20 00000000 */  nop   
/* 0A5B24 800A4F24 13000007 */  beqz  $t8, .L800A4F44
/* 0A5B28 800A4F28 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0A5B2C 800A4F2C 8059001B */  lb    $t9, 0x1b($v0)
/* 0A5B30 800A4F30 00000000 */  nop   
/* 0A5B34 800A4F34 14B90003 */  bne   $a1, $t9, .L800A4F44
/* 0A5B38 800A4F38 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0A5B3C 800A4F3C A040001A */  sb    $zero, 0x1a($v0)
/* 0A5B40 800A4F40 8FBF0014 */  lw    $ra, 0x14($sp)
.L800A4F44:
/* 0A5B44 800A4F44 27BD0038 */  addiu $sp, $sp, 0x38
/* 0A5B48 800A4F48 03E00008 */  jr    $ra
/* 0A5B4C 800A4F4C 00000000 */   nop   

