.late_rodata
glabel jpt_800E8768
.word L800A6E70, L800A6F3C, L800A7014, L800A70D4, L800A7158

.text
glabel func_800A6E30
/* 0A7A30 800A6E30 3C088012 */  lui   $t0, %hi(gCurrentHud) # $t0, 0x8012
/* 0A7A34 800A6E34 25086CDC */  addiu $t0, %lo(gCurrentHud) # addiu $t0, $t0, 0x6cdc
/* 0A7A38 800A6E38 8D020000 */  lw    $v0, ($t0)
/* 0A7A3C 800A6E3C 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0A7A40 800A6E40 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0A7A44 800A6E44 904E01DA */  lbu   $t6, 0x1da($v0)
/* 0A7A48 800A6E48 00803025 */  move  $a2, $a0
/* 0A7A4C 800A6E4C 2DC10005 */  sltiu $at, $t6, 5
/* 0A7A50 800A6E50 102000CA */  beqz  $at, .L800A717C
/* 0A7A54 800A6E54 000E7080 */   sll   $t6, $t6, 2
/* 0A7A58 800A6E58 3C01800F */  lui   $at, %hi(jpt_800E8768) # $at, 0x800f
/* 0A7A5C 800A6E5C 002E0821 */  addu  $at, $at, $t6
/* 0A7A60 800A6E60 8C2E8768 */  lw    $t6, %lo(jpt_800E8768)($at)
/* 0A7A64 800A6E64 00000000 */  nop   
/* 0A7A68 800A6E68 01C00008 */  jr    $t6
/* 0A7A6C 800A6E6C 00000000 */   nop   
glabel L800A6E70
/* 0A7A70 800A6E70 3C03800E */  lui   $v1, %hi(D_800E2770) # $v1, 0x800e
/* 0A7A74 800A6E74 24632770 */  addiu $v1, %lo(D_800E2770) # addiu $v1, $v1, 0x2770
/* 0A7A78 800A6E78 240F007F */  li    $t7, 127
/* 0A7A7C 800A6E7C A06F0002 */  sb    $t7, 2($v1)
/* 0A7A80 800A6E80 A0600003 */  sb    $zero, 3($v1)
/* 0A7A84 800A6E84 84D80000 */  lh    $t8, ($a2)
/* 0A7A88 800A6E88 AFA60018 */  sw    $a2, 0x18($sp)
/* 0A7A8C 800A6E8C 24040016 */  li    $a0, 22
/* 0A7A90 800A6E90 00002825 */  move  $a1, $zero
/* 0A7A94 800A6E94 0C000741 */  jal   play_sound_global
/* 0A7A98 800A6E98 A078000C */   sb    $t8, 0xc($v1)
/* 0A7A9C 800A6E9C 3C038012 */  lui   $v1, %hi(gHUDNumPlayers) # $v1, 0x8012
/* 0A7AA0 800A6EA0 8C636D0C */  lw    $v1, %lo(gHUDNumPlayers)($v1)
/* 0A7AA4 800A6EA4 8FA60018 */  lw    $a2, 0x18($sp)
/* 0A7AA8 800A6EA8 3C088012 */  lui   $t0, %hi(gCurrentHud) # $t0, 0x8012
/* 0A7AAC 800A6EAC 10600003 */  beqz  $v1, .L800A6EBC
/* 0A7AB0 800A6EB0 25086CDC */   addiu $t0, %lo(gCurrentHud) # addiu $t0, $t0, 0x6cdc
/* 0A7AB4 800A6EB4 24010001 */  li    $at, 1
/* 0A7AB8 800A6EB8 14610008 */  bne   $v1, $at, .L800A6EDC
.L800A6EBC:
/* 0A7ABC 800A6EBC 3C01C348 */   li    $at, 0xC3480000 # -200.000000
/* 0A7AC0 800A6EC0 44812000 */  mtc1  $at, $f4
/* 0A7AC4 800A6EC4 8D190000 */  lw    $t9, ($t0)
/* 0A7AC8 800A6EC8 00000000 */  nop   
/* 0A7ACC 800A6ECC E72401CC */  swc1  $f4, 0x1cc($t9)
/* 0A7AD0 800A6ED0 8D090000 */  lw    $t1, ($t0)
/* 0A7AD4 800A6ED4 10000015 */  b     .L800A6F2C
/* 0A7AD8 800A6ED8 A12001DD */   sb    $zero, 0x1dd($t1)
.L800A6EDC:
/* 0A7ADC 800A6EDC 84C20000 */  lh    $v0, ($a2)
/* 0A7AE0 800A6EE0 24010002 */  li    $at, 2
/* 0A7AE4 800A6EE4 10400003 */  beqz  $v0, .L800A6EF4
/* 0A7AE8 800A6EE8 240AFFB0 */   li    $t2, -80
/* 0A7AEC 800A6EEC 14410008 */  bne   $v0, $at, .L800A6F10
/* 0A7AF0 800A6EF0 240D0050 */   li    $t5, 80
.L800A6EF4:
/* 0A7AF4 800A6EF4 8D0B0000 */  lw    $t3, ($t0)
/* 0A7AF8 800A6EF8 3C01C348 */  li    $at, 0xC3480000 # -200.000000
/* 0A7AFC 800A6EFC A16A01DD */  sb    $t2, 0x1dd($t3)
/* 0A7B00 800A6F00 8D0C0000 */  lw    $t4, ($t0)
/* 0A7B04 800A6F04 44813000 */  mtc1  $at, $f6
/* 0A7B08 800A6F08 10000008 */  b     .L800A6F2C
/* 0A7B0C 800A6F0C E58601CC */   swc1  $f6, 0x1cc($t4)
.L800A6F10:
/* 0A7B10 800A6F10 8D0E0000 */  lw    $t6, ($t0)
/* 0A7B14 800A6F14 3C01C220 */  li    $at, 0xC2200000 # -40.000000
/* 0A7B18 800A6F18 A1CD01DD */  sb    $t5, 0x1dd($t6)
/* 0A7B1C 800A6F1C 8D0F0000 */  lw    $t7, ($t0)
/* 0A7B20 800A6F20 44814000 */  mtc1  $at, $f8
/* 0A7B24 800A6F24 00000000 */  nop   
/* 0A7B28 800A6F28 E5E801CC */  swc1  $f8, 0x1cc($t7)
.L800A6F2C:
/* 0A7B2C 800A6F2C 8D190000 */  lw    $t9, ($t0)
/* 0A7B30 800A6F30 24180001 */  li    $t8, 1
/* 0A7B34 800A6F34 10000091 */  b     .L800A717C
/* 0A7B38 800A6F38 A33801DA */   sb    $t8, 0x1da($t9)
glabel L800A6F3C
/* 0A7B3C 800A6F3C 00051880 */  sll   $v1, $a1, 2
/* 0A7B40 800A6F40 00651823 */  subu  $v1, $v1, $a1
/* 0A7B44 800A6F44 804401DD */  lb    $a0, 0x1dd($v0)
/* 0A7B48 800A6F48 00031880 */  sll   $v1, $v1, 2
/* 0A7B4C 800A6F4C 00651821 */  addu  $v1, $v1, $a1
/* 0A7B50 800A6F50 00834823 */  subu  $t1, $a0, $v1
/* 0A7B54 800A6F54 44895000 */  mtc1  $t1, $f10
/* 0A7B58 800A6F58 C44001CC */  lwc1  $f0, 0x1cc($v0)
/* 0A7B5C 800A6F5C 46805420 */  cvt.s.w $f16, $f10
/* 0A7B60 800A6F60 4610003C */  c.lt.s $f0, $f16
/* 0A7B64 800A6F64 00000000 */  nop   
/* 0A7B68 800A6F68 45000007 */  bc1f  .L800A6F88
/* 0A7B6C 800A6F6C 00000000 */   nop   
/* 0A7B70 800A6F70 44839000 */  mtc1  $v1, $f18
/* 0A7B74 800A6F74 00000000 */  nop   
/* 0A7B78 800A6F78 46809120 */  cvt.s.w $f4, $f18
/* 0A7B7C 800A6F7C 46040180 */  add.s $f6, $f0, $f4
/* 0A7B80 800A6F80 10000019 */  b     .L800A6FE8
/* 0A7B84 800A6F84 E44601CC */   swc1  $f6, 0x1cc($v0)
.L800A6F88:
/* 0A7B88 800A6F88 44844000 */  mtc1  $a0, $f8
/* 0A7B8C 800A6F8C 240A0002 */  li    $t2, 2
/* 0A7B90 800A6F90 468042A0 */  cvt.s.w $f10, $f8
/* 0A7B94 800A6F94 240CFF88 */  li    $t4, -120
/* 0A7B98 800A6F98 3C0E8012 */  lui   $t6, %hi(gHUDVoiceSoundMask) # $t6, 0x8012
/* 0A7B9C 800A6F9C E44A01CC */  swc1  $f10, 0x1cc($v0)
/* 0A7BA0 800A6FA0 8D0B0000 */  lw    $t3, ($t0)
/* 0A7BA4 800A6FA4 3C0F8012 */  lui   $t7, %hi(D_80126D71) # $t7, 0x8012
/* 0A7BA8 800A6FA8 A16A01DA */  sb    $t2, 0x1da($t3)
/* 0A7BAC 800A6FAC 8D0D0000 */  lw    $t5, ($t0)
/* 0A7BB0 800A6FB0 00000000 */  nop   
/* 0A7BB4 800A6FB4 A1AC01DB */  sb    $t4, 0x1db($t5)
/* 0A7BB8 800A6FB8 8DCE6D40 */  lw    $t6, %lo(gHUDVoiceSoundMask)($t6)
/* 0A7BBC 800A6FBC 00000000 */  nop   
/* 0A7BC0 800A6FC0 15C00009 */  bnez  $t6, .L800A6FE8
/* 0A7BC4 800A6FC4 00000000 */   nop   
/* 0A7BC8 800A6FC8 91EF6D71 */  lbu   $t7, %lo(D_80126D71)($t7)
/* 0A7BCC 800A6FCC 00000000 */  nop   
/* 0A7BD0 800A6FD0 15E00005 */  bnez  $t7, .L800A6FE8
/* 0A7BD4 800A6FD4 00000000 */   nop   
/* 0A7BD8 800A6FD8 0C029B6D */  jal   play_time_trial_end_message
/* 0A7BDC 800A6FDC 00C02025 */   move  $a0, $a2
/* 0A7BE0 800A6FE0 3C088012 */  lui   $t0, %hi(gCurrentHud) # $t0, 0x8012
/* 0A7BE4 800A6FE4 25086CDC */  addiu $t0, %lo(gCurrentHud) # addiu $t0, $t0, 0x6cdc
.L800A6FE8:
/* 0A7BE8 800A6FE8 8D070000 */  lw    $a3, ($t0)
/* 0A7BEC 800A6FEC 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A7BF0 800A6FF0 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A7BF4 800A6FF4 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A7BF8 800A6FF8 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A7BFC 800A6FFC 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A7C00 800A7000 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A7C04 800A7004 0C02A980 */  jal   func_800AA600
/* 0A7C08 800A7008 24E701C0 */   addiu $a3, $a3, 0x1c0
/* 0A7C0C 800A700C 1000005C */  b     .L800A7180
/* 0A7C10 800A7010 8FBF0014 */   lw    $ra, 0x14($sp)
glabel L800A7014
/* 0A7C14 800A7014 805801DB */  lb    $t8, 0x1db($v0)
/* 0A7C18 800A7018 240A0003 */  li    $t2, 3
/* 0A7C1C 800A701C 0305C821 */  addu  $t9, $t8, $a1
/* 0A7C20 800A7020 A05901DB */  sb    $t9, 0x1db($v0)
/* 0A7C24 800A7024 8D020000 */  lw    $v0, ($t0)
/* 0A7C28 800A7028 3C038012 */  lui   $v1, %hi(gHUDNumPlayers) # $v1, 0x8012
/* 0A7C2C 800A702C 804901DB */  lb    $t1, 0x1db($v0)
/* 0A7C30 800A7030 24040016 */  li    $a0, 22
/* 0A7C34 800A7034 29210078 */  slti  $at, $t1, 0x78
/* 0A7C38 800A7038 1420001C */  bnez  $at, .L800A70AC
/* 0A7C3C 800A703C 00000000 */   nop   
/* 0A7C40 800A7040 A04A01DA */  sb    $t2, 0x1da($v0)
/* 0A7C44 800A7044 8C636D0C */  lw    $v1, %lo(gHUDNumPlayers)($v1)
/* 0A7C48 800A7048 24010001 */  li    $at, 1
/* 0A7C4C 800A704C 10600003 */  beqz  $v1, .L800A705C
/* 0A7C50 800A7050 240B0038 */   li    $t3, 56
/* 0A7C54 800A7054 14610004 */  bne   $v1, $at, .L800A7068
/* 0A7C58 800A7058 00000000 */   nop   
.L800A705C:
/* 0A7C5C 800A705C 8D0C0000 */  lw    $t4, ($t0)
/* 0A7C60 800A7060 1000000D */  b     .L800A7098
/* 0A7C64 800A7064 A18B01DD */   sb    $t3, 0x1dd($t4)
.L800A7068:
/* 0A7C68 800A7068 84C20000 */  lh    $v0, ($a2)
/* 0A7C6C 800A706C 24010002 */  li    $at, 2
/* 0A7C70 800A7070 10400003 */  beqz  $v0, .L800A7080
/* 0A7C74 800A7074 240D0038 */   li    $t5, 56
/* 0A7C78 800A7078 14410004 */  bne   $v0, $at, .L800A708C
/* 0A7C7C 800A707C 00000000 */   nop   
.L800A7080:
/* 0A7C80 800A7080 8D0E0000 */  lw    $t6, ($t0)
/* 0A7C84 800A7084 10000004 */  b     .L800A7098
/* 0A7C88 800A7088 A1CD01DD */   sb    $t5, 0x1dd($t6)
.L800A708C:
/* 0A7C8C 800A708C 8D180000 */  lw    $t8, ($t0)
/* 0A7C90 800A7090 240FFFD8 */  li    $t7, -40
/* 0A7C94 800A7094 A30F01DD */  sb    $t7, 0x1dd($t8)
.L800A7098:
/* 0A7C98 800A7098 0C000741 */  jal   play_sound_global
/* 0A7C9C 800A709C 00002825 */   move  $a1, $zero
/* 0A7CA0 800A70A0 3C028012 */  lui   $v0, %hi(gCurrentHud) # $v0, 0x8012
/* 0A7CA4 800A70A4 8C426CDC */  lw    $v0, %lo(gCurrentHud)($v0)
/* 0A7CA8 800A70A8 00000000 */  nop   
.L800A70AC:
/* 0A7CAC 800A70AC 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A7CB0 800A70B0 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A7CB4 800A70B4 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A7CB8 800A70B8 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A7CBC 800A70BC 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A7CC0 800A70C0 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A7CC4 800A70C4 0C02A980 */  jal   func_800AA600
/* 0A7CC8 800A70C8 244701C0 */   addiu $a3, $v0, 0x1c0
/* 0A7CCC 800A70CC 1000002C */  b     .L800A7180
/* 0A7CD0 800A70D0 8FBF0014 */   lw    $ra, 0x14($sp)
glabel L800A70D4
/* 0A7CD4 800A70D4 0005C880 */  sll   $t9, $a1, 2
/* 0A7CD8 800A70D8 0325C823 */  subu  $t9, $t9, $a1
/* 0A7CDC 800A70DC 0019C880 */  sll   $t9, $t9, 2
/* 0A7CE0 800A70E0 0325C821 */  addu  $t9, $t9, $a1
/* 0A7CE4 800A70E4 44999000 */  mtc1  $t9, $f18
/* 0A7CE8 800A70E8 C45001CC */  lwc1  $f16, 0x1cc($v0)
/* 0A7CEC 800A70EC 46809120 */  cvt.s.w $f4, $f18
/* 0A7CF0 800A70F0 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A7CF4 800A70F4 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A7CF8 800A70F8 46048181 */  sub.s $f6, $f16, $f4
/* 0A7CFC 800A70FC 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A7D00 800A7100 E44601CC */  swc1  $f6, 0x1cc($v0)
/* 0A7D04 800A7104 8D020000 */  lw    $v0, ($t0)
/* 0A7D08 800A7108 240A0004 */  li    $t2, 4
/* 0A7D0C 800A710C 804901DD */  lb    $t1, 0x1dd($v0)
/* 0A7D10 800A7110 C44801CC */  lwc1  $f8, 0x1cc($v0)
/* 0A7D14 800A7114 44895000 */  mtc1  $t1, $f10
/* 0A7D18 800A7118 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A7D1C 800A711C 468054A0 */  cvt.s.w $f18, $f10
/* 0A7D20 800A7120 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A7D24 800A7124 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A7D28 800A7128 4612403C */  c.lt.s $f8, $f18
/* 0A7D2C 800A712C 00000000 */  nop   
/* 0A7D30 800A7130 45000005 */  bc1f  .L800A7148
/* 0A7D34 800A7134 00000000 */   nop   
/* 0A7D38 800A7138 A04A01DA */  sb    $t2, 0x1da($v0)
/* 0A7D3C 800A713C 3C028012 */  lui   $v0, %hi(gCurrentHud) # $v0, 0x8012
/* 0A7D40 800A7140 8C426CDC */  lw    $v0, %lo(gCurrentHud)($v0)
/* 0A7D44 800A7144 00000000 */  nop   
.L800A7148:
/* 0A7D48 800A7148 0C02A980 */  jal   func_800AA600
/* 0A7D4C 800A714C 244701C0 */   addiu $a3, $v0, 0x1c0
/* 0A7D50 800A7150 1000000B */  b     .L800A7180
/* 0A7D54 800A7154 8FBF0014 */   lw    $ra, 0x14($sp)
glabel L800A7158
/* 0A7D58 800A7158 3C03800E */  lui   $v1, %hi(D_800E2770) # $v1, 0x800e
/* 0A7D5C 800A715C 24632770 */  addiu $v1, %lo(D_800E2770) # addiu $v1, $v1, 0x2770
/* 0A7D60 800A7160 240BFFFF */  li    $t3, -1
/* 0A7D64 800A7164 A06B0003 */  sb    $t3, 3($v1)
/* 0A7D68 800A7168 240C0005 */  li    $t4, 5
/* 0A7D6C 800A716C A04C01DA */  sb    $t4, 0x1da($v0)
/* 0A7D70 800A7170 8D0D0000 */  lw    $t5, ($t0)
/* 0A7D74 800A7174 00000000 */  nop   
/* 0A7D78 800A7178 A1A001DB */  sb    $zero, 0x1db($t5)
.L800A717C:
/* 0A7D7C 800A717C 8FBF0014 */  lw    $ra, 0x14($sp)
.L800A7180:
/* 0A7D80 800A7180 27BD0018 */  addiu $sp, $sp, 0x18
/* 0A7D84 800A7184 03E00008 */  jr    $ra
/* 0A7D88 800A7188 00000000 */   nop   

