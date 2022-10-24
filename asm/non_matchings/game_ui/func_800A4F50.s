glabel func_800A4F50
/* 0A5B50 800A4F50 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0A5B54 800A4F54 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0A5B58 800A4F58 AFA40018 */  sw    $a0, 0x18($sp)
/* 0A5B5C 800A4F5C AFA5001C */  sw    $a1, 0x1c($sp)
/* 0A5B60 800A4F60 808F01D8 */  lb    $t7, 0x1d8($a0)
/* 0A5B64 800A4F64 3C028012 */  lui   $v0, %hi(gHUDNumPlayers) # $v0, 0x8012
/* 0A5B68 800A4F68 15E00089 */  bnez  $t7, .L800A5190
/* 0A5B6C 800A4F6C 00000000 */   nop   
/* 0A5B70 800A4F70 8C426D0C */  lw    $v0, %lo(gHUDNumPlayers)($v0)
/* 0A5B74 800A4F74 00000000 */  nop   
/* 0A5B78 800A4F78 1840000B */  blez  $v0, .L800A4FA8
/* 0A5B7C 800A4F7C 00000000 */   nop   
/* 0A5B80 800A4F80 80830193 */  lb    $v1, 0x193($a0)
/* 0A5B84 800A4F84 00000000 */  nop   
/* 0A5B88 800A4F88 18600007 */  blez  $v1, .L800A4FA8
/* 0A5B8C 800A4F8C 0003C080 */   sll   $t8, $v1, 2
/* 0A5B90 800A4F90 0098C821 */  addu  $t9, $a0, $t8
/* 0A5B94 800A4F94 8F2B0128 */  lw    $t3, 0x128($t9)
/* 0A5B98 800A4F98 00000000 */  nop   
/* 0A5B9C 800A4F9C 296100B4 */  slti  $at, $t3, 0xb4
/* 0A5BA0 800A4FA0 1420007B */  bnez  $at, .L800A5190
/* 0A5BA4 800A4FA4 00000000 */   nop   
.L800A4FA8:
/* 0A5BA8 800A4FA8 1840000B */  blez  $v0, .L800A4FD8
/* 0A5BAC 800A4FAC 3C198012 */   lui   $t9, %hi(D_80126D60) # $t9, 0x8012
/* 0A5BB0 800A4FB0 8FAD0018 */  lw    $t5, 0x18($sp)
/* 0A5BB4 800A4FB4 00026080 */  sll   $t4, $v0, 2
/* 0A5BB8 800A4FB8 85AF0000 */  lh    $t7, ($t5)
/* 0A5BBC 800A4FBC 3C18800E */  lui   $t8, %hi(D_800E2794) # $t8, 0x800e
/* 0A5BC0 800A4FC0 018F7021 */  addu  $t6, $t4, $t7
/* 0A5BC4 800A4FC4 030EC021 */  addu  $t8, $t8, $t6
/* 0A5BC8 800A4FC8 93182794 */  lbu   $t8, %lo(D_800E2794)($t8)
/* 0A5BCC 800A4FCC 24010003 */  li    $at, 3
/* 0A5BD0 800A4FD0 1701006F */  bne   $t8, $at, .L800A5190
/* 0A5BD4 800A4FD4 00000000 */   nop   
.L800A4FD8:
/* 0A5BD8 800A4FD8 8FAD0018 */  lw    $t5, 0x18($sp)
/* 0A5BDC 800A4FDC 8F396D60 */  lw    $t9, %lo(D_80126D60)($t9)
/* 0A5BE0 800A4FE0 81AC0194 */  lb    $t4, 0x194($t5)
/* 0A5BE4 800A4FE4 832B004B */  lb    $t3, 0x4b($t9)
/* 0A5BE8 800A4FE8 258F0001 */  addiu $t7, $t4, 1
/* 0A5BEC 800A4FEC 156F0029 */  bne   $t3, $t7, .L800A5094
/* 0A5BF0 800A4FF0 28410002 */   slti  $at, $v0, 2
/* 0A5BF4 800A4FF4 10200027 */  beqz  $at, .L800A5094
/* 0A5BF8 800A4FF8 3C088012 */   lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A5BFC 800A4FFC 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A5C00 800A5000 8D020000 */  lw    $v0, ($t0)
/* 0A5C04 800A5004 8FB8001C */  lw    $t8, 0x1c($sp)
/* 0A5C08 800A5008 804E021A */  lb    $t6, 0x21a($v0)
/* 0A5C0C 800A500C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5C10 800A5010 01D8C821 */  addu  $t9, $t6, $t8
/* 0A5C14 800A5014 A059021A */  sb    $t9, 0x21a($v0)
/* 0A5C18 800A5018 8D020000 */  lw    $v0, ($t0)
/* 0A5C1C 800A501C 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A5C20 800A5020 804D021A */  lb    $t5, 0x21a($v0)
/* 0A5C24 800A5024 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A5C28 800A5028 29A10007 */  slti  $at, $t5, 7
/* 0A5C2C 800A502C 14200015 */  bnez  $at, .L800A5084
/* 0A5C30 800A5030 24846CFC */   addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5C34 800A5034 844C0218 */  lh    $t4, 0x218($v0)
/* 0A5C38 800A5038 00000000 */  nop   
/* 0A5C3C 800A503C 258B0001 */  addiu $t3, $t4, 1
/* 0A5C40 800A5040 A44B0218 */  sh    $t3, 0x218($v0)
/* 0A5C44 800A5044 8D020000 */  lw    $v0, ($t0)
/* 0A5C48 800A5048 00000000 */  nop   
/* 0A5C4C 800A504C 804F021A */  lb    $t7, 0x21a($v0)
/* 0A5C50 800A5050 00000000 */  nop   
/* 0A5C54 800A5054 25EEFFFA */  addiu $t6, $t7, -6
/* 0A5C58 800A5058 A04E021A */  sb    $t6, 0x21a($v0)
/* 0A5C5C 800A505C 8D020000 */  lw    $v0, ($t0)
/* 0A5C60 800A5060 00000000 */  nop   
/* 0A5C64 800A5064 84580218 */  lh    $t8, 0x218($v0)
/* 0A5C68 800A5068 00000000 */  nop   
/* 0A5C6C 800A506C 2B010005 */  slti  $at, $t8, 5
/* 0A5C70 800A5070 14200004 */  bnez  $at, .L800A5084
/* 0A5C74 800A5074 00000000 */   nop   
/* 0A5C78 800A5078 A4400218 */  sh    $zero, 0x218($v0)
/* 0A5C7C 800A507C 8D020000 */  lw    $v0, ($t0)
/* 0A5C80 800A5080 00000000 */  nop   
.L800A5084:
/* 0A5C84 800A5084 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A5C88 800A5088 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A5C8C 800A508C 0C02A980 */  jal   func_800AA600
/* 0A5C90 800A5090 24470200 */   addiu $a3, $v0, 0x200
.L800A5094:
/* 0A5C94 800A5094 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A5C98 800A5098 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A5C9C 800A509C 8D070000 */  lw    $a3, ($t0)
/* 0A5CA0 800A50A0 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5CA4 800A50A4 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A5CA8 800A50A8 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A5CAC 800A50AC 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A5CB0 800A50B0 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A5CB4 800A50B4 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5CB8 800A50B8 0C02A980 */  jal   func_800AA600
/* 0A5CBC 800A50BC 24E70060 */   addiu $a3, $a3, 0x60
/* 0A5CC0 800A50C0 3C0A8012 */  lui   $t2, %hi(D_80126D60) # $t2, 0x8012
/* 0A5CC4 800A50C4 254A6D60 */  addiu $t2, %lo(D_80126D60) # addiu $t2, $t2, 0x6d60
/* 0A5CC8 800A50C8 8D590000 */  lw    $t9, ($t2)
/* 0A5CCC 800A50CC 8FA90018 */  lw    $t1, 0x18($sp)
/* 0A5CD0 800A50D0 8322004B */  lb    $v0, 0x4b($t9)
/* 0A5CD4 800A50D4 81230194 */  lb    $v1, 0x194($t1)
/* 0A5CD8 800A50D8 244DFFFF */  addiu $t5, $v0, -1
/* 0A5CDC 800A50DC 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A5CE0 800A50E0 006D082A */  slt   $at, $v1, $t5
/* 0A5CE4 800A50E4 14200004 */  bnez  $at, .L800A50F8
/* 0A5CE8 800A50E8 25086CDC */   addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A5CEC 800A50EC 8D0C0000 */  lw    $t4, ($t0)
/* 0A5CF0 800A50F0 10000004 */  b     .L800A5104
/* 0A5CF4 800A50F4 A5820098 */   sh    $v0, 0x98($t4)
.L800A50F8:
/* 0A5CF8 800A50F8 8D0F0000 */  lw    $t7, ($t0)
/* 0A5CFC 800A50FC 246B0001 */  addiu $t3, $v1, 1
/* 0A5D00 800A5100 A5EB0098 */  sh    $t3, 0x98($t7)
.L800A5104:
/* 0A5D04 800A5104 8D4E0000 */  lw    $t6, ($t2)
/* 0A5D08 800A5108 8D190000 */  lw    $t9, ($t0)
/* 0A5D0C 800A510C 81D8004B */  lb    $t8, 0x4b($t6)
/* 0A5D10 800A5110 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5D14 800A5114 A73800D8 */  sh    $t8, 0xd8($t9)
/* 0A5D18 800A5118 8D070000 */  lw    $a3, ($t0)
/* 0A5D1C 800A511C 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A5D20 800A5120 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A5D24 800A5124 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A5D28 800A5128 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A5D2C 800A512C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5D30 800A5130 0C02A980 */  jal   func_800AA600
/* 0A5D34 800A5134 24E70080 */   addiu $a3, $a3, 0x80
/* 0A5D38 800A5138 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A5D3C 800A513C 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A5D40 800A5140 8D070000 */  lw    $a3, ($t0)
/* 0A5D44 800A5144 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5D48 800A5148 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A5D4C 800A514C 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A5D50 800A5150 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A5D54 800A5154 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A5D58 800A5158 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5D5C 800A515C 0C02A980 */  jal   func_800AA600
/* 0A5D60 800A5160 24E700A0 */   addiu $a3, $a3, 0xa0
/* 0A5D64 800A5164 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A5D68 800A5168 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A5D6C 800A516C 8D070000 */  lw    $a3, ($t0)
/* 0A5D70 800A5170 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5D74 800A5174 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A5D78 800A5178 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A5D7C 800A517C 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A5D80 800A5180 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A5D84 800A5184 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5D88 800A5188 0C02A980 */  jal   func_800AA600
/* 0A5D8C 800A518C 24E700C0 */   addiu $a3, $a3, 0xc0
.L800A5190:
/* 0A5D90 800A5190 3C0D8012 */  lui   $t5, %hi(gHUDNumPlayers) # $t5, 0x8012
/* 0A5D94 800A5194 8DAD6D0C */  lw    $t5, %lo(gHUDNumPlayers)($t5)
/* 0A5D98 800A5198 24010001 */  li    $at, 1
/* 0A5D9C 800A519C 15A10003 */  bne   $t5, $at, .L800A51AC
/* 0A5DA0 800A51A0 00000000 */   nop   
/* 0A5DA4 800A51A4 0C01EFC7 */  jal   func_8007BF1C
/* 0A5DA8 800A51A8 24040001 */   li    $a0, 1
.L800A51AC:
/* 0A5DAC 800A51AC 0C01BAA8 */  jal   is_game_paused
/* 0A5DB0 800A51B0 00000000 */   nop   
/* 0A5DB4 800A51B4 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A5DB8 800A51B8 8FA90018 */  lw    $t1, 0x18($sp)
/* 0A5DBC 800A51BC 14400223 */  bnez  $v0, .L800A5A4C
/* 0A5DC0 800A51C0 25086CDC */   addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A5DC4 800A51C4 81230193 */  lb    $v1, 0x193($t1)
/* 0A5DC8 800A51C8 00000000 */  nop   
/* 0A5DCC 800A51CC 00036080 */  sll   $t4, $v1, 2
/* 0A5DD0 800A51D0 012C5821 */  addu  $t3, $t1, $t4
/* 0A5DD4 800A51D4 8D6F0128 */  lw    $t7, 0x128($t3)
/* 0A5DD8 800A51D8 00000000 */  nop   
/* 0A5DDC 800A51DC 29E1001E */  slti  $at, $t7, 0x1e
/* 0A5DE0 800A51E0 102000BF */  beqz  $at, .L800A54E0
/* 0A5DE4 800A51E4 00000000 */   nop   
/* 0A5DE8 800A51E8 8D020000 */  lw    $v0, ($t0)
/* 0A5DEC 800A51EC 00000000 */  nop   
/* 0A5DF0 800A51F0 804E03DA */  lb    $t6, 0x3da($v0)
/* 0A5DF4 800A51F4 00000000 */  nop   
/* 0A5DF8 800A51F8 15C000B9 */  bnez  $t6, .L800A54E0
/* 0A5DFC 800A51FC 00000000 */   nop   
/* 0A5E00 800A5200 813801D8 */  lb    $t8, 0x1d8($t1)
/* 0A5E04 800A5204 24060001 */  li    $a2, 1
/* 0A5E08 800A5208 170000B5 */  bnez  $t8, .L800A54E0
/* 0A5E0C 800A520C 00000000 */   nop   
/* 0A5E10 800A5210 14C30058 */  bne   $a2, $v1, .L800A5374
/* 0A5E14 800A5214 3C198012 */   lui   $t9, %hi(D_80126D60) # $t9, 0x8012
/* 0A5E18 800A5218 8F396D60 */  lw    $t9, %lo(D_80126D60)($t9)
/* 0A5E1C 800A521C 240C0002 */  li    $t4, 2
/* 0A5E20 800A5220 832D004B */  lb    $t5, 0x4b($t9)
/* 0A5E24 800A5224 24040016 */  li    $a0, 22
/* 0A5E28 800A5228 29A10003 */  slti  $at, $t5, 3
/* 0A5E2C 800A522C 14200051 */  bnez  $at, .L800A5374
/* 0A5E30 800A5230 00000000 */   nop   
/* 0A5E34 800A5234 A04C03DA */  sb    $t4, 0x3da($v0)
/* 0A5E38 800A5238 8D0B0000 */  lw    $t3, ($t0)
/* 0A5E3C 800A523C 00002825 */  move  $a1, $zero
/* 0A5E40 800A5240 A16603DB */  sb    $a2, 0x3db($t3)
/* 0A5E44 800A5244 8D0F0000 */  lw    $t7, ($t0)
/* 0A5E48 800A5248 0C000741 */  jal   play_sound_global
/* 0A5E4C 800A524C A1E003DD */   sb    $zero, 0x3dd($t7)
/* 0A5E50 800A5250 3C028012 */  lui   $v0, %hi(gHUDNumPlayers) # $v0, 0x8012
/* 0A5E54 800A5254 8C426D0C */  lw    $v0, %lo(gHUDNumPlayers)($v0)
/* 0A5E58 800A5258 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A5E5C 800A525C 8FA90018 */  lw    $t1, 0x18($sp)
/* 0A5E60 800A5260 10400006 */  beqz  $v0, .L800A527C
/* 0A5E64 800A5264 25086CDC */   addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A5E68 800A5268 24010001 */  li    $at, 1
/* 0A5E6C 800A526C 10410012 */  beq   $v0, $at, .L800A52B8
/* 0A5E70 800A5270 240FFFF0 */   li    $t7, -16
/* 0A5E74 800A5274 1000001E */  b     .L800A52F0
/* 0A5E78 800A5278 24010002 */   li    $at, 2
.L800A527C:
/* 0A5E7C 800A527C 8D180000 */  lw    $t8, ($t0)
/* 0A5E80 800A5280 240EFFEB */  li    $t6, -21
/* 0A5E84 800A5284 A30E03DC */  sb    $t6, 0x3dc($t8)
/* 0A5E88 800A5288 8D0D0000 */  lw    $t5, ($t0)
/* 0A5E8C 800A528C 24190020 */  li    $t9, 32
/* 0A5E90 800A5290 3C01C348 */  li    $at, 0xC3480000 # -200.000000
/* 0A5E94 800A5294 A1B903FC */  sb    $t9, 0x3fc($t5)
/* 0A5E98 800A5298 8D0C0000 */  lw    $t4, ($t0)
/* 0A5E9C 800A529C 44812000 */  mtc1  $at, $f4
/* 0A5EA0 800A52A0 3C014353 */  li    $at, 0x43530000 # 211.000000
/* 0A5EA4 800A52A4 E58403CC */  swc1  $f4, 0x3cc($t4)
/* 0A5EA8 800A52A8 8D0B0000 */  lw    $t3, ($t0)
/* 0A5EAC 800A52AC 44813000 */  mtc1  $at, $f6
/* 0A5EB0 800A52B0 1000008B */  b     .L800A54E0
/* 0A5EB4 800A52B4 E56603EC */   swc1  $f6, 0x3ec($t3)
.L800A52B8:
/* 0A5EB8 800A52B8 8D0E0000 */  lw    $t6, ($t0)
/* 0A5EBC 800A52BC 2418001B */  li    $t8, 27
/* 0A5EC0 800A52C0 A1CF03DC */  sb    $t7, 0x3dc($t6)
/* 0A5EC4 800A52C4 8D190000 */  lw    $t9, ($t0)
/* 0A5EC8 800A52C8 3C01C348 */  li    $at, 0xC3480000 # -200.000000
/* 0A5ECC 800A52CC A33803FC */  sb    $t8, 0x3fc($t9)
/* 0A5ED0 800A52D0 8D0D0000 */  lw    $t5, ($t0)
/* 0A5ED4 800A52D4 44814000 */  mtc1  $at, $f8
/* 0A5ED8 800A52D8 3C014353 */  li    $at, 0x43530000 # 211.000000
/* 0A5EDC 800A52DC E5A803CC */  swc1  $f8, 0x3cc($t5)
/* 0A5EE0 800A52E0 8D0C0000 */  lw    $t4, ($t0)
/* 0A5EE4 800A52E4 44815000 */  mtc1  $at, $f10
/* 0A5EE8 800A52E8 1000007D */  b     .L800A54E0
/* 0A5EEC 800A52EC E58A03EC */   swc1  $f10, 0x3ec($t4)
.L800A52F0:
/* 0A5EF0 800A52F0 85220000 */  lh    $v0, ($t1)
/* 0A5EF4 800A52F4 240CFFA6 */  li    $t4, -90
/* 0A5EF8 800A52F8 10400011 */  beqz  $v0, .L800A5340
/* 0A5EFC 800A52FC 240FFFC5 */   li    $t7, -59
/* 0A5F00 800A5300 1041000F */  beq   $v0, $at, .L800A5340
/* 0A5F04 800A5304 240B003C */   li    $t3, 60
/* 0A5F08 800A5308 8D0F0000 */  lw    $t7, ($t0)
/* 0A5F0C 800A530C 240E005B */  li    $t6, 91
/* 0A5F10 800A5310 A1EB03DC */  sb    $t3, 0x3dc($t7)
/* 0A5F14 800A5314 8D180000 */  lw    $t8, ($t0)
/* 0A5F18 800A5318 3C01C28C */  li    $at, 0xC28C0000 # -70.000000
/* 0A5F1C 800A531C A30E03FC */  sb    $t6, 0x3fc($t8)
/* 0A5F20 800A5320 8D190000 */  lw    $t9, ($t0)
/* 0A5F24 800A5324 44818000 */  mtc1  $at, $f16
/* 0A5F28 800A5328 3C01435D */  li    $at, 0x435D0000 # 221.000000
/* 0A5F2C 800A532C E73003CC */  swc1  $f16, 0x3cc($t9)
/* 0A5F30 800A5330 8D0D0000 */  lw    $t5, ($t0)
/* 0A5F34 800A5334 44819000 */  mtc1  $at, $f18
/* 0A5F38 800A5338 10000069 */  b     .L800A54E0
/* 0A5F3C 800A533C E5B203EC */   swc1  $f18, 0x3ec($t5)
.L800A5340:
/* 0A5F40 800A5340 8D0B0000 */  lw    $t3, ($t0)
/* 0A5F44 800A5344 3C01C35C */  li    $at, 0xC35C0000 # -220.000000
/* 0A5F48 800A5348 A16C03DC */  sb    $t4, 0x3dc($t3)
/* 0A5F4C 800A534C 8D0E0000 */  lw    $t6, ($t0)
/* 0A5F50 800A5350 44812000 */  mtc1  $at, $f4
/* 0A5F54 800A5354 A1CF03FC */  sb    $t7, 0x3fc($t6)
/* 0A5F58 800A5358 8D180000 */  lw    $t8, ($t0)
/* 0A5F5C 800A535C 3C01428E */  li    $at, 0x428E0000 # 71.000000
/* 0A5F60 800A5360 E70403CC */  swc1  $f4, 0x3cc($t8)
/* 0A5F64 800A5364 8D190000 */  lw    $t9, ($t0)
/* 0A5F68 800A5368 44813000 */  mtc1  $at, $f6
/* 0A5F6C 800A536C 1000005C */  b     .L800A54E0
/* 0A5F70 800A5370 E72603EC */   swc1  $f6, 0x3ec($t9)
.L800A5374:
/* 0A5F74 800A5374 3C0D8012 */  lui   $t5, %hi(D_80126D60) # $t5, 0x8012
/* 0A5F78 800A5378 8DAD6D60 */  lw    $t5, %lo(D_80126D60)($t5)
/* 0A5F7C 800A537C 246B0001 */  addiu $t3, $v1, 1
/* 0A5F80 800A5380 81AC004B */  lb    $t4, 0x4b($t5)
/* 0A5F84 800A5384 00000000 */  nop   
/* 0A5F88 800A5388 158B0055 */  bne   $t4, $t3, .L800A54E0
/* 0A5F8C 800A538C 00000000 */   nop   
/* 0A5F90 800A5390 10600053 */  beqz  $v1, .L800A54E0
/* 0A5F94 800A5394 240F0003 */   li    $t7, 3
/* 0A5F98 800A5398 A04F03DA */  sb    $t7, 0x3da($v0)
/* 0A5F9C 800A539C 8D180000 */  lw    $t8, ($t0)
/* 0A5FA0 800A53A0 240EFFFF */  li    $t6, -1
/* 0A5FA4 800A53A4 A30E03DB */  sb    $t6, 0x3db($t8)
/* 0A5FA8 800A53A8 8D190000 */  lw    $t9, ($t0)
/* 0A5FAC 800A53AC 24040016 */  li    $a0, 22
/* 0A5FB0 800A53B0 00002825 */  move  $a1, $zero
/* 0A5FB4 800A53B4 0C000741 */  jal   play_sound_global
/* 0A5FB8 800A53B8 A32003DD */   sb    $zero, 0x3dd($t9)
/* 0A5FBC 800A53BC 3C028012 */  lui   $v0, %hi(gHUDNumPlayers) # $v0, 0x8012
/* 0A5FC0 800A53C0 8C426D0C */  lw    $v0, %lo(gHUDNumPlayers)($v0)
/* 0A5FC4 800A53C4 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A5FC8 800A53C8 8FA90018 */  lw    $t1, 0x18($sp)
/* 0A5FCC 800A53CC 10400006 */  beqz  $v0, .L800A53E8
/* 0A5FD0 800A53D0 25086CDC */   addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A5FD4 800A53D4 24010001 */  li    $at, 1
/* 0A5FD8 800A53D8 10410012 */  beq   $v0, $at, .L800A5424
/* 0A5FDC 800A53DC 24190029 */   li    $t9, 41
/* 0A5FE0 800A53E0 1000001E */  b     .L800A545C
/* 0A5FE4 800A53E4 24010002 */   li    $at, 2
.L800A53E8:
/* 0A5FE8 800A53E8 8D0C0000 */  lw    $t4, ($t0)
/* 0A5FEC 800A53EC 240D0033 */  li    $t5, 51
/* 0A5FF0 800A53F0 A18D03DC */  sb    $t5, 0x3dc($t4)
/* 0A5FF4 800A53F4 8D0F0000 */  lw    $t7, ($t0)
/* 0A5FF8 800A53F8 240BFFD7 */  li    $t3, -41
/* 0A5FFC 800A53FC 3C014352 */  li    $at, 0x43520000 # 210.000000
/* 0A6000 800A5400 A1EB03BC */  sb    $t3, 0x3bc($t7)
/* 0A6004 800A5404 8D0E0000 */  lw    $t6, ($t0)
/* 0A6008 800A5408 44814000 */  mtc1  $at, $f8
/* 0A600C 800A540C 3C01C348 */  li    $at, 0xC3480000 # -200.000000
/* 0A6010 800A5410 E5C803CC */  swc1  $f8, 0x3cc($t6)
/* 0A6014 800A5414 8D180000 */  lw    $t8, ($t0)
/* 0A6018 800A5418 44815000 */  mtc1  $at, $f10
/* 0A601C 800A541C 10000030 */  b     .L800A54E0
/* 0A6020 800A5420 E70A03AC */   swc1  $f10, 0x3ac($t8)
.L800A5424:
/* 0A6024 800A5424 8D0D0000 */  lw    $t5, ($t0)
/* 0A6028 800A5428 240CFFE1 */  li    $t4, -31
/* 0A602C 800A542C A1B903DC */  sb    $t9, 0x3dc($t5)
/* 0A6030 800A5430 8D0B0000 */  lw    $t3, ($t0)
/* 0A6034 800A5434 3C014352 */  li    $at, 0x43520000 # 210.000000
/* 0A6038 800A5438 A16C03BC */  sb    $t4, 0x3bc($t3)
/* 0A603C 800A543C 8D0F0000 */  lw    $t7, ($t0)
/* 0A6040 800A5440 44818000 */  mtc1  $at, $f16
/* 0A6044 800A5444 3C01C348 */  li    $at, 0xC3480000 # -200.000000
/* 0A6048 800A5448 E5F003CC */  swc1  $f16, 0x3cc($t7)
/* 0A604C 800A544C 8D0E0000 */  lw    $t6, ($t0)
/* 0A6050 800A5450 44819000 */  mtc1  $at, $f18
/* 0A6054 800A5454 10000022 */  b     .L800A54E0
/* 0A6058 800A5458 E5D203AC */   swc1  $f18, 0x3ac($t6)
.L800A545C:
/* 0A605C 800A545C 85220000 */  lh    $v0, ($t1)
/* 0A6060 800A5460 240EFFCE */  li    $t6, -50
/* 0A6064 800A5464 10400011 */  beqz  $v0, .L800A54AC
/* 0A6068 800A5468 2419FF9C */   li    $t9, -100
/* 0A606C 800A546C 1041000F */  beq   $v0, $at, .L800A54AC
/* 0A6070 800A5470 24180064 */   li    $t8, 100
/* 0A6074 800A5474 8D190000 */  lw    $t9, ($t0)
/* 0A6078 800A5478 240D0032 */  li    $t5, 50
/* 0A607C 800A547C A33803DC */  sb    $t8, 0x3dc($t9)
/* 0A6080 800A5480 8D0C0000 */  lw    $t4, ($t0)
/* 0A6084 800A5484 3C0142C8 */  li    $at, 0x42C80000 # 100.000000
/* 0A6088 800A5488 A18D03BC */  sb    $t5, 0x3bc($t4)
/* 0A608C 800A548C 8D0B0000 */  lw    $t3, ($t0)
/* 0A6090 800A5490 44812000 */  mtc1  $at, $f4
/* 0A6094 800A5494 3C01C248 */  li    $at, 0xC2480000 # -50.000000
/* 0A6098 800A5498 E56403CC */  swc1  $f4, 0x3cc($t3)
/* 0A609C 800A549C 8D0F0000 */  lw    $t7, ($t0)
/* 0A60A0 800A54A0 44813000 */  mtc1  $at, $f6
/* 0A60A4 800A54A4 1000000E */  b     .L800A54E0
/* 0A60A8 800A54A8 E5E603AC */   swc1  $f6, 0x3ac($t7)
.L800A54AC:
/* 0A60AC 800A54AC 8D180000 */  lw    $t8, ($t0)
/* 0A60B0 800A54B0 3C014248 */  li    $at, 0x42480000 # 50.000000
/* 0A60B4 800A54B4 A30E03DC */  sb    $t6, 0x3dc($t8)
/* 0A60B8 800A54B8 8D0D0000 */  lw    $t5, ($t0)
/* 0A60BC 800A54BC 44814000 */  mtc1  $at, $f8
/* 0A60C0 800A54C0 A1B903BC */  sb    $t9, 0x3bc($t5)
/* 0A60C4 800A54C4 8D0C0000 */  lw    $t4, ($t0)
/* 0A60C8 800A54C8 3C01C348 */  li    $at, 0xC3480000 # -200.000000
/* 0A60CC 800A54CC E58803CC */  swc1  $f8, 0x3cc($t4)
/* 0A60D0 800A54D0 8D0B0000 */  lw    $t3, ($t0)
/* 0A60D4 800A54D4 44815000 */  mtc1  $at, $f10
/* 0A60D8 800A54D8 00000000 */  nop   
/* 0A60DC 800A54DC E56A03AC */  swc1  $f10, 0x3ac($t3)
.L800A54E0:
/* 0A60E0 800A54E0 8D020000 */  lw    $v0, ($t0)
/* 0A60E4 800A54E4 24060001 */  li    $a2, 1
/* 0A60E8 800A54E8 804303DA */  lb    $v1, 0x3da($v0)
/* 0A60EC 800A54EC 24010002 */  li    $at, 2
/* 0A60F0 800A54F0 10600156 */  beqz  $v1, .L800A5A4C
/* 0A60F4 800A54F4 00000000 */   nop   
/* 0A60F8 800A54F8 146100AA */  bne   $v1, $at, .L800A57A4
/* 0A60FC 800A54FC 24010003 */   li    $at, 3
/* 0A6100 800A5500 804303DB */  lb    $v1, 0x3db($v0)
/* 0A6104 800A5504 8FA4001C */  lw    $a0, 0x1c($sp)
/* 0A6108 800A5508 14C30063 */  bne   $a2, $v1, .L800A5698
/* 0A610C 800A550C 2401FFFF */   li    $at, -1
/* 0A6110 800A5510 00047880 */  sll   $t7, $a0, 2
/* 0A6114 800A5514 01E47823 */  subu  $t7, $t7, $a0
/* 0A6118 800A5518 804303DC */  lb    $v1, 0x3dc($v0)
/* 0A611C 800A551C 000F7880 */  sll   $t7, $t7, 2
/* 0A6120 800A5520 01E47821 */  addu  $t7, $t7, $a0
/* 0A6124 800A5524 006F7023 */  subu  $t6, $v1, $t7
/* 0A6128 800A5528 448E8000 */  mtc1  $t6, $f16
/* 0A612C 800A552C C44003CC */  lwc1  $f0, 0x3cc($v0)
/* 0A6130 800A5530 468084A0 */  cvt.s.w $f18, $f16
/* 0A6134 800A5534 01E02025 */  move  $a0, $t7
/* 0A6138 800A5538 240FFFFF */  li    $t7, -1
/* 0A613C 800A553C 4612003C */  c.lt.s $f0, $f18
/* 0A6140 800A5540 00002825 */  move  $a1, $zero
/* 0A6144 800A5544 45000007 */  bc1f  .L800A5564
/* 0A6148 800A5548 00000000 */   nop   
/* 0A614C 800A554C 44842000 */  mtc1  $a0, $f4
/* 0A6150 800A5550 00000000 */  nop   
/* 0A6154 800A5554 468021A0 */  cvt.s.w $f6, $f4
/* 0A6158 800A5558 46060200 */  add.s $f8, $f0, $f6
/* 0A615C 800A555C 10000005 */  b     .L800A5574
/* 0A6160 800A5560 E44803CC */   swc1  $f8, 0x3cc($v0)
.L800A5564:
/* 0A6164 800A5564 44835000 */  mtc1  $v1, $f10
/* 0A6168 800A5568 00000000 */  nop   
/* 0A616C 800A556C 46805420 */  cvt.s.w $f16, $f10
/* 0A6170 800A5570 E45003CC */  swc1  $f16, 0x3cc($v0)
.L800A5574:
/* 0A6174 800A5574 8D020000 */  lw    $v0, ($t0)
/* 0A6178 800A5578 00000000 */  nop   
/* 0A617C 800A557C 804303FC */  lb    $v1, 0x3fc($v0)
/* 0A6180 800A5580 C44003EC */  lwc1  $f0, 0x3ec($v0)
/* 0A6184 800A5584 0064C021 */  addu  $t8, $v1, $a0
/* 0A6188 800A5588 44989000 */  mtc1  $t8, $f18
/* 0A618C 800A558C 00000000 */  nop   
/* 0A6190 800A5590 46809120 */  cvt.s.w $f4, $f18
/* 0A6194 800A5594 4600203C */  c.lt.s $f4, $f0
/* 0A6198 800A5598 00000000 */  nop   
/* 0A619C 800A559C 45000007 */  bc1f  .L800A55BC
/* 0A61A0 800A55A0 00000000 */   nop   
/* 0A61A4 800A55A4 44843000 */  mtc1  $a0, $f6
/* 0A61A8 800A55A8 00000000 */  nop   
/* 0A61AC 800A55AC 46803220 */  cvt.s.w $f8, $f6
/* 0A61B0 800A55B0 46080281 */  sub.s $f10, $f0, $f8
/* 0A61B4 800A55B4 10000005 */  b     .L800A55CC
/* 0A61B8 800A55B8 E44A03EC */   swc1  $f10, 0x3ec($v0)
.L800A55BC:
/* 0A61BC 800A55BC 44838000 */  mtc1  $v1, $f16
/* 0A61C0 800A55C0 00000000 */  nop   
/* 0A61C4 800A55C4 468084A0 */  cvt.s.w $f18, $f16
/* 0A61C8 800A55C8 E45203EC */  swc1  $f18, 0x3ec($v0)
.L800A55CC:
/* 0A61CC 800A55CC 81390193 */  lb    $t9, 0x193($t1)
/* 0A61D0 800A55D0 24040016 */  li    $a0, 22
/* 0A61D4 800A55D4 00196880 */  sll   $t5, $t9, 2
/* 0A61D8 800A55D8 012D6021 */  addu  $t4, $t1, $t5
/* 0A61DC 800A55DC 8D8B0128 */  lw    $t3, 0x128($t4)
/* 0A61E0 800A55E0 00000000 */  nop   
/* 0A61E4 800A55E4 2961003C */  slti  $at, $t3, 0x3c
/* 0A61E8 800A55E8 14200007 */  bnez  $at, .L800A5608
/* 0A61EC 800A55EC 00000000 */   nop   
/* 0A61F0 800A55F0 8D0E0000 */  lw    $t6, ($t0)
/* 0A61F4 800A55F4 0C000741 */  jal   play_sound_global
/* 0A61F8 800A55F8 A1CF03DB */   sb    $t7, 0x3db($t6)
/* 0A61FC 800A55FC 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A6200 800A5600 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A6204 800A5604 24060001 */  li    $a2, 1
.L800A5608:
/* 0A6208 800A5608 8D020000 */  lw    $v0, ($t0)
/* 0A620C 800A560C 00000000 */  nop   
/* 0A6210 800A5610 805803DC */  lb    $t8, 0x3dc($v0)
/* 0A6214 800A5614 C44403CC */  lwc1  $f4, 0x3cc($v0)
/* 0A6218 800A5618 44983000 */  mtc1  $t8, $f6
/* 0A621C 800A561C 00000000 */  nop   
/* 0A6220 800A5620 46803220 */  cvt.s.w $f8, $f6
/* 0A6224 800A5624 46082032 */  c.eq.s $f4, $f8
/* 0A6228 800A5628 00000000 */  nop   
/* 0A622C 800A562C 45000037 */  bc1f  .L800A570C
/* 0A6230 800A5630 00000000 */   nop   
/* 0A6234 800A5634 805903FC */  lb    $t9, 0x3fc($v0)
/* 0A6238 800A5638 C44A03EC */  lwc1  $f10, 0x3ec($v0)
/* 0A623C 800A563C 44998000 */  mtc1  $t9, $f16
/* 0A6240 800A5640 00000000 */  nop   
/* 0A6244 800A5644 468084A0 */  cvt.s.w $f18, $f16
/* 0A6248 800A5648 46125032 */  c.eq.s $f10, $f18
/* 0A624C 800A564C 00000000 */  nop   
/* 0A6250 800A5650 4500002E */  bc1f  .L800A570C
/* 0A6254 800A5654 00000000 */   nop   
/* 0A6258 800A5658 804D03DD */  lb    $t5, 0x3dd($v0)
/* 0A625C 800A565C 3C058012 */  lui   $a1, %hi(gHUDVoiceSoundMask) # $a1, 0x8012
/* 0A6260 800A5660 15A0002A */  bnez  $t5, .L800A570C
/* 0A6264 800A5664 24A56D40 */   addiu $a1, %lo(gHUDVoiceSoundMask) # addiu $a1, $a1, 0x6d40
/* 0A6268 800A5668 8CAC0000 */  lw    $t4, ($a1)
/* 0A626C 800A566C 00000000 */  nop   
/* 0A6270 800A5670 15800007 */  bnez  $t4, .L800A5690
/* 0A6274 800A5674 00000000 */   nop   
/* 0A6278 800A5678 0C000741 */  jal   play_sound_global
/* 0A627C 800A567C 24040100 */   li    $a0, 256
/* 0A6280 800A5680 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A6284 800A5684 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A6288 800A5688 8D020000 */  lw    $v0, ($t0)
/* 0A628C 800A568C 24060001 */  li    $a2, 1
.L800A5690:
/* 0A6290 800A5690 1000001E */  b     .L800A570C
/* 0A6294 800A5694 A04603DD */   sb    $a2, 0x3dd($v0)
.L800A5698:
/* 0A6298 800A5698 1461001C */  bne   $v1, $at, .L800A570C
/* 0A629C 800A569C 00000000 */   nop   
/* 0A62A0 800A56A0 8FAB001C */  lw    $t3, 0x1c($sp)
/* 0A62A4 800A56A4 C44403CC */  lwc1  $f4, 0x3cc($v0)
/* 0A62A8 800A56A8 000B7880 */  sll   $t7, $t3, 2
/* 0A62AC 800A56AC 01EB7823 */  subu  $t7, $t7, $t3
/* 0A62B0 800A56B0 000F7880 */  sll   $t7, $t7, 2
/* 0A62B4 800A56B4 01EB7821 */  addu  $t7, $t7, $t3
/* 0A62B8 800A56B8 448F3000 */  mtc1  $t7, $f6
/* 0A62BC 800A56BC 3C01C348 */  li    $at, 0xC3480000 # -200.000000
/* 0A62C0 800A56C0 46803020 */  cvt.s.w $f0, $f6
/* 0A62C4 800A56C4 44813000 */  mtc1  $at, $f6
/* 0A62C8 800A56C8 46002201 */  sub.s $f8, $f4, $f0
/* 0A62CC 800A56CC E44803CC */  swc1  $f8, 0x3cc($v0)
/* 0A62D0 800A56D0 8D020000 */  lw    $v0, ($t0)
/* 0A62D4 800A56D4 00000000 */  nop   
/* 0A62D8 800A56D8 C45003EC */  lwc1  $f16, 0x3ec($v0)
/* 0A62DC 800A56DC 00000000 */  nop   
/* 0A62E0 800A56E0 46008280 */  add.s $f10, $f16, $f0
/* 0A62E4 800A56E4 E44A03EC */  swc1  $f10, 0x3ec($v0)
/* 0A62E8 800A56E8 8D020000 */  lw    $v0, ($t0)
/* 0A62EC 800A56EC 00000000 */  nop   
/* 0A62F0 800A56F0 C45203CC */  lwc1  $f18, 0x3cc($v0)
/* 0A62F4 800A56F4 00000000 */  nop   
/* 0A62F8 800A56F8 4606903C */  c.lt.s $f18, $f6
/* 0A62FC 800A56FC 00000000 */  nop   
/* 0A6300 800A5700 45000002 */  bc1f  .L800A570C
/* 0A6304 800A5704 00000000 */   nop   
/* 0A6308 800A5708 A04003DA */  sb    $zero, 0x3da($v0)
.L800A570C:
/* 0A630C 800A570C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A6310 800A5710 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A6314 800A5714 8C820000 */  lw    $v0, ($a0)
/* 0A6318 800A5718 3C18FA00 */  lui   $t8, 0xfa00
/* 0A631C 800A571C 244E0008 */  addiu $t6, $v0, 8
/* 0A6320 800A5720 AC8E0000 */  sw    $t6, ($a0)
/* 0A6324 800A5724 2419FFA0 */  li    $t9, -96
/* 0A6328 800A5728 AC590004 */  sw    $t9, 4($v0)
/* 0A632C 800A572C AC580000 */  sw    $t8, ($v0)
/* 0A6330 800A5730 8D070000 */  lw    $a3, ($t0)
/* 0A6334 800A5734 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A6338 800A5738 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A633C 800A573C 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A6340 800A5740 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A6344 800A5744 0C02A980 */  jal   func_800AA600
/* 0A6348 800A5748 24E703E0 */   addiu $a3, $a3, 0x3e0
/* 0A634C 800A574C 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A6350 800A5750 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A6354 800A5754 8D070000 */  lw    $a3, ($t0)
/* 0A6358 800A5758 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A635C 800A575C 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A6360 800A5760 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A6364 800A5764 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A6368 800A5768 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A636C 800A576C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A6370 800A5770 0C02A980 */  jal   func_800AA600
/* 0A6374 800A5774 24E703C0 */   addiu $a3, $a3, 0x3c0
/* 0A6378 800A5778 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A637C 800A577C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A6380 800A5780 8C820000 */  lw    $v0, ($a0)
/* 0A6384 800A5784 3C0CFA00 */  lui   $t4, 0xfa00
/* 0A6388 800A5788 244D0008 */  addiu $t5, $v0, 8
/* 0A638C 800A578C AC8D0000 */  sw    $t5, ($a0)
/* 0A6390 800A5790 240BFFFF */  li    $t3, -1
/* 0A6394 800A5794 AC4B0004 */  sw    $t3, 4($v0)
/* 0A6398 800A5798 100000AC */  b     .L800A5A4C
/* 0A639C 800A579C AC4C0000 */   sw    $t4, ($v0)
/* 0A63A0 800A57A0 24010003 */  li    $at, 3
.L800A57A4:
/* 0A63A4 800A57A4 146100A9 */  bne   $v1, $at, .L800A5A4C
/* 0A63A8 800A57A8 00000000 */   nop   
/* 0A63AC 800A57AC 804303DB */  lb    $v1, 0x3db($v0)
/* 0A63B0 800A57B0 2401FFFF */  li    $at, -1
/* 0A63B4 800A57B4 14610064 */  bne   $v1, $at, .L800A5948
/* 0A63B8 800A57B8 00000000 */   nop   
/* 0A63BC 800A57BC 8FA4001C */  lw    $a0, 0x1c($sp)
/* 0A63C0 800A57C0 804303DC */  lb    $v1, 0x3dc($v0)
/* 0A63C4 800A57C4 00047880 */  sll   $t7, $a0, 2
/* 0A63C8 800A57C8 01E47823 */  subu  $t7, $t7, $a0
/* 0A63CC 800A57CC 000F7880 */  sll   $t7, $t7, 2
/* 0A63D0 800A57D0 01E47821 */  addu  $t7, $t7, $a0
/* 0A63D4 800A57D4 006F7021 */  addu  $t6, $v1, $t7
/* 0A63D8 800A57D8 448E2000 */  mtc1  $t6, $f4
/* 0A63DC 800A57DC C44003CC */  lwc1  $f0, 0x3cc($v0)
/* 0A63E0 800A57E0 46802220 */  cvt.s.w $f8, $f4
/* 0A63E4 800A57E4 01E02025 */  move  $a0, $t7
/* 0A63E8 800A57E8 00002825 */  move  $a1, $zero
/* 0A63EC 800A57EC 4600403C */  c.lt.s $f8, $f0
/* 0A63F0 800A57F0 00000000 */  nop   
/* 0A63F4 800A57F4 45000007 */  bc1f  .L800A5814
/* 0A63F8 800A57F8 00000000 */   nop   
/* 0A63FC 800A57FC 44848000 */  mtc1  $a0, $f16
/* 0A6400 800A5800 00000000 */  nop   
/* 0A6404 800A5804 468082A0 */  cvt.s.w $f10, $f16
/* 0A6408 800A5808 460A0481 */  sub.s $f18, $f0, $f10
/* 0A640C 800A580C 10000005 */  b     .L800A5824
/* 0A6410 800A5810 E45203CC */   swc1  $f18, 0x3cc($v0)
.L800A5814:
/* 0A6414 800A5814 44833000 */  mtc1  $v1, $f6
/* 0A6418 800A5818 00000000 */  nop   
/* 0A641C 800A581C 46803120 */  cvt.s.w $f4, $f6
/* 0A6420 800A5820 E44403CC */  swc1  $f4, 0x3cc($v0)
.L800A5824:
/* 0A6424 800A5824 8D020000 */  lw    $v0, ($t0)
/* 0A6428 800A5828 00000000 */  nop   
/* 0A642C 800A582C 804303BC */  lb    $v1, 0x3bc($v0)
/* 0A6430 800A5830 C44003AC */  lwc1  $f0, 0x3ac($v0)
/* 0A6434 800A5834 0064C023 */  subu  $t8, $v1, $a0
/* 0A6438 800A5838 44984000 */  mtc1  $t8, $f8
/* 0A643C 800A583C 00000000 */  nop   
/* 0A6440 800A5840 46804420 */  cvt.s.w $f16, $f8
/* 0A6444 800A5844 4610003C */  c.lt.s $f0, $f16
/* 0A6448 800A5848 00000000 */  nop   
/* 0A644C 800A584C 45000007 */  bc1f  .L800A586C
/* 0A6450 800A5850 00000000 */   nop   
/* 0A6454 800A5854 44845000 */  mtc1  $a0, $f10
/* 0A6458 800A5858 00000000 */  nop   
/* 0A645C 800A585C 468054A0 */  cvt.s.w $f18, $f10
/* 0A6460 800A5860 46120180 */  add.s $f6, $f0, $f18
/* 0A6464 800A5864 10000005 */  b     .L800A587C
/* 0A6468 800A5868 E44603AC */   swc1  $f6, 0x3ac($v0)
.L800A586C:
/* 0A646C 800A586C 44832000 */  mtc1  $v1, $f4
/* 0A6470 800A5870 00000000 */  nop   
/* 0A6474 800A5874 46802220 */  cvt.s.w $f8, $f4
/* 0A6478 800A5878 E44803AC */  swc1  $f8, 0x3ac($v0)
.L800A587C:
/* 0A647C 800A587C 81390193 */  lb    $t9, 0x193($t1)
/* 0A6480 800A5880 24040016 */  li    $a0, 22
/* 0A6484 800A5884 00196880 */  sll   $t5, $t9, 2
/* 0A6488 800A5888 012D6021 */  addu  $t4, $t1, $t5
/* 0A648C 800A588C 8D8B0128 */  lw    $t3, 0x128($t4)
/* 0A6490 800A5890 00000000 */  nop   
/* 0A6494 800A5894 2961003C */  slti  $at, $t3, 0x3c
/* 0A6498 800A5898 14200007 */  bnez  $at, .L800A58B8
/* 0A649C 800A589C 00000000 */   nop   
/* 0A64A0 800A58A0 8D0F0000 */  lw    $t7, ($t0)
/* 0A64A4 800A58A4 0C000741 */  jal   play_sound_global
/* 0A64A8 800A58A8 A1E603DB */   sb    $a2, 0x3db($t7)
/* 0A64AC 800A58AC 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A64B0 800A58B0 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A64B4 800A58B4 24060001 */  li    $a2, 1
.L800A58B8:
/* 0A64B8 800A58B8 8D020000 */  lw    $v0, ($t0)
/* 0A64BC 800A58BC 00000000 */  nop   
/* 0A64C0 800A58C0 804E03DC */  lb    $t6, 0x3dc($v0)
/* 0A64C4 800A58C4 C45003CC */  lwc1  $f16, 0x3cc($v0)
/* 0A64C8 800A58C8 448E5000 */  mtc1  $t6, $f10
/* 0A64CC 800A58CC 00000000 */  nop   
/* 0A64D0 800A58D0 468054A0 */  cvt.s.w $f18, $f10
/* 0A64D4 800A58D4 46128032 */  c.eq.s $f16, $f18
/* 0A64D8 800A58D8 00000000 */  nop   
/* 0A64DC 800A58DC 45000037 */  bc1f  .L800A59BC
/* 0A64E0 800A58E0 00000000 */   nop   
/* 0A64E4 800A58E4 805803BC */  lb    $t8, 0x3bc($v0)
/* 0A64E8 800A58E8 C44603AC */  lwc1  $f6, 0x3ac($v0)
/* 0A64EC 800A58EC 44982000 */  mtc1  $t8, $f4
/* 0A64F0 800A58F0 00000000 */  nop   
/* 0A64F4 800A58F4 46802220 */  cvt.s.w $f8, $f4
/* 0A64F8 800A58F8 46083032 */  c.eq.s $f6, $f8
/* 0A64FC 800A58FC 00000000 */  nop   
/* 0A6500 800A5900 4500002E */  bc1f  .L800A59BC
/* 0A6504 800A5904 00000000 */   nop   
/* 0A6508 800A5908 805903DD */  lb    $t9, 0x3dd($v0)
/* 0A650C 800A590C 3C058012 */  lui   $a1, %hi(gHUDVoiceSoundMask) # $a1, 0x8012
/* 0A6510 800A5910 1720002A */  bnez  $t9, .L800A59BC
/* 0A6514 800A5914 24A56D40 */   addiu $a1, %lo(gHUDVoiceSoundMask) # addiu $a1, $a1, 0x6d40
/* 0A6518 800A5918 8CAD0000 */  lw    $t5, ($a1)
/* 0A651C 800A591C 00000000 */  nop   
/* 0A6520 800A5920 15A00007 */  bnez  $t5, .L800A5940
/* 0A6524 800A5924 00000000 */   nop   
/* 0A6528 800A5928 0C000741 */  jal   play_sound_global
/* 0A652C 800A592C 24040101 */   li    $a0, 257
/* 0A6530 800A5930 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A6534 800A5934 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A6538 800A5938 8D020000 */  lw    $v0, ($t0)
/* 0A653C 800A593C 24060001 */  li    $a2, 1
.L800A5940:
/* 0A6540 800A5940 1000001E */  b     .L800A59BC
/* 0A6544 800A5944 A04603DD */   sb    $a2, 0x3dd($v0)
.L800A5948:
/* 0A6548 800A5948 14C3001C */  bne   $a2, $v1, .L800A59BC
/* 0A654C 800A594C 00000000 */   nop   
/* 0A6550 800A5950 8FAC001C */  lw    $t4, 0x1c($sp)
/* 0A6554 800A5954 C45003CC */  lwc1  $f16, 0x3cc($v0)
/* 0A6558 800A5958 000C5880 */  sll   $t3, $t4, 2
/* 0A655C 800A595C 016C5823 */  subu  $t3, $t3, $t4
/* 0A6560 800A5960 000B5880 */  sll   $t3, $t3, 2
/* 0A6564 800A5964 016C5821 */  addu  $t3, $t3, $t4
/* 0A6568 800A5968 448B5000 */  mtc1  $t3, $f10
/* 0A656C 800A596C 3C014348 */  li    $at, 0x43480000 # 200.000000
/* 0A6570 800A5970 46805020 */  cvt.s.w $f0, $f10
/* 0A6574 800A5974 44814000 */  mtc1  $at, $f8
/* 0A6578 800A5978 46008480 */  add.s $f18, $f16, $f0
/* 0A657C 800A597C E45203CC */  swc1  $f18, 0x3cc($v0)
/* 0A6580 800A5980 8D020000 */  lw    $v0, ($t0)
/* 0A6584 800A5984 00000000 */  nop   
/* 0A6588 800A5988 C44403AC */  lwc1  $f4, 0x3ac($v0)
/* 0A658C 800A598C 00000000 */  nop   
/* 0A6590 800A5990 46002181 */  sub.s $f6, $f4, $f0
/* 0A6594 800A5994 E44603AC */  swc1  $f6, 0x3ac($v0)
/* 0A6598 800A5998 8D020000 */  lw    $v0, ($t0)
/* 0A659C 800A599C 00000000 */  nop   
/* 0A65A0 800A59A0 C44A03CC */  lwc1  $f10, 0x3cc($v0)
/* 0A65A4 800A59A4 00000000 */  nop   
/* 0A65A8 800A59A8 460A403C */  c.lt.s $f8, $f10
/* 0A65AC 800A59AC 00000000 */  nop   
/* 0A65B0 800A59B0 45000002 */  bc1f  .L800A59BC
/* 0A65B4 800A59B4 00000000 */   nop   
/* 0A65B8 800A59B8 A04003DA */  sb    $zero, 0x3da($v0)
.L800A59BC:
/* 0A65BC 800A59BC 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A65C0 800A59C0 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A65C4 800A59C4 8C820000 */  lw    $v0, ($a0)
/* 0A65C8 800A59C8 3C0EFA00 */  lui   $t6, 0xfa00
/* 0A65CC 800A59CC 244F0008 */  addiu $t7, $v0, 8
/* 0A65D0 800A59D0 AC8F0000 */  sw    $t7, ($a0)
/* 0A65D4 800A59D4 2418FFA0 */  li    $t8, -96
/* 0A65D8 800A59D8 AC580004 */  sw    $t8, 4($v0)
/* 0A65DC 800A59DC AC4E0000 */  sw    $t6, ($v0)
/* 0A65E0 800A59E0 8D070000 */  lw    $a3, ($t0)
/* 0A65E4 800A59E4 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A65E8 800A59E8 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A65EC 800A59EC 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A65F0 800A59F0 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A65F4 800A59F4 0C02A980 */  jal   func_800AA600
/* 0A65F8 800A59F8 24E703A0 */   addiu $a3, $a3, 0x3a0
/* 0A65FC 800A59FC 3C088012 */  lui   $t0, %hi(D_80126CDC) # $t0, 0x8012
/* 0A6600 800A5A00 25086CDC */  addiu $t0, %lo(D_80126CDC) # addiu $t0, $t0, 0x6cdc
/* 0A6604 800A5A04 8D070000 */  lw    $a3, ($t0)
/* 0A6608 800A5A08 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A660C 800A5A0C 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A6610 800A5A10 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A6614 800A5A14 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A6618 800A5A18 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A661C 800A5A1C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A6620 800A5A20 0C02A980 */  jal   func_800AA600
/* 0A6624 800A5A24 24E703C0 */   addiu $a3, $a3, 0x3c0
/* 0A6628 800A5A28 3C028012 */  lui   $v0, %hi(gHUDCurrDisplayList) # $v0, 0x8012
/* 0A662C 800A5A2C 8C426CFC */  lw    $v0, %lo(gHUDCurrDisplayList)($v0)
/* 0A6630 800A5A30 3C018012 */  lui   $at, %hi(gHUDCurrDisplayList) # $at, 0x8012
/* 0A6634 800A5A34 24590008 */  addiu $t9, $v0, 8
/* 0A6638 800A5A38 AC396CFC */  sw    $t9, %lo(gHUDCurrDisplayList)($at)
/* 0A663C 800A5A3C 3C0DFA00 */  lui   $t5, 0xfa00
/* 0A6640 800A5A40 240CFFFF */  li    $t4, -1
/* 0A6644 800A5A44 AC4C0004 */  sw    $t4, 4($v0)
/* 0A6648 800A5A48 AC4D0000 */  sw    $t5, ($v0)
.L800A5A4C:
/* 0A664C 800A5A4C 0C01EFC7 */  jal   func_8007BF1C
/* 0A6650 800A5A50 00002025 */   move  $a0, $zero
/* 0A6654 800A5A54 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0A6658 800A5A58 27BD0018 */  addiu $sp, $sp, 0x18
/* 0A665C 800A5A5C 03E00008 */  jr    $ra
/* 0A6660 800A5A60 00000000 */   nop   

