glabel func_8007BF34
/* 07CB34 8007BF34 3C078012 */  lui   $a3, %hi(gCurrentRenderFlags) # $a3, 0x8012
/* 07CB38 8007BF38 24E76374 */  addiu $a3, %lo(gCurrentRenderFlags) # addiu $a3, $a3, 0x6374
/* 07CB3C 8007BF3C 8CEE0000 */  lw    $t6, ($a3)
/* 07CB40 8007BF40 3C088012 */  lui   $t0, %hi(gForceFlags) # $t0, 0x8012
/* 07CB44 8007BF44 14AE0005 */  bne   $a1, $t6, .L8007BF5C
/* 07CB48 8007BF48 25086382 */   addiu $t0, %lo(gForceFlags) # addiu $t0, $t0, 0x6382
/* 07CB4C 8007BF4C 850F0000 */  lh    $t7, ($t0)
/* 07CB50 8007BF50 00000000 */  nop   
/* 07CB54 8007BF54 11E00073 */  beqz  $t7, .L8007C124
/* 07CB58 8007BF58 00000000 */   nop   
.L8007BF5C:
/* 07CB5C 8007BF5C 8C820000 */  lw    $v0, ($a0)
/* 07CB60 8007BF60 3C19E700 */  lui   $t9, 0xe700
/* 07CB64 8007BF64 24580008 */  addiu $t8, $v0, 8
/* 07CB68 8007BF68 AC980000 */  sw    $t8, ($a0)
/* 07CB6C 8007BF6C AC400004 */  sw    $zero, 4($v0)
/* 07CB70 8007BF70 AC590000 */  sw    $t9, ($v0)
/* 07CB74 8007BF74 8CE30000 */  lw    $v1, ($a3)
/* 07CB78 8007BF78 3C088012 */  lui   $t0, %hi(gForceFlags) # $t0, 0x8012
/* 07CB7C 8007BF7C 00034900 */  sll   $t1, $v1, 4
/* 07CB80 8007BF80 05200005 */  bltz  $t1, .L8007BF98
/* 07CB84 8007BF84 25086382 */   addiu $t0, %lo(gForceFlags) # addiu $t0, $t0, 0x6382
/* 07CB88 8007BF88 850A0000 */  lh    $t2, ($t0)
/* 07CB8C 8007BF8C 00000000 */  nop   
/* 07CB90 8007BF90 1140000A */  beqz  $t2, .L8007BFBC
/* 07CB94 8007BF94 00000000 */   nop   
.L8007BF98:
/* 07CB98 8007BF98 8C820000 */  lw    $v0, ($a0)
/* 07CB9C 8007BF9C 3C0CB700 */  lui   $t4, 0xb700
/* 07CBA0 8007BFA0 244B0008 */  addiu $t3, $v0, 8
/* 07CBA4 8007BFA4 AC8B0000 */  sw    $t3, ($a0)
/* 07CBA8 8007BFA8 3C0D0001 */  lui   $t5, 1
/* 07CBAC 8007BFAC AC4D0004 */  sw    $t5, 4($v0)
/* 07CBB0 8007BFB0 AC4C0000 */  sw    $t4, ($v0)
/* 07CBB4 8007BFB4 8CE30000 */  lw    $v1, ($a3)
/* 07CBB8 8007BFB8 00000000 */  nop   
.L8007BFBC:
/* 07CBBC 8007BFBC 3C0F8012 */  lui   $t7, %hi(gBlockedRenderFlags) # $t7, 0x8012
/* 07CBC0 8007BFC0 8DEF6378 */  lw    $t7, %lo(gBlockedRenderFlags)($t7)
/* 07CBC4 8007BFC4 3C01F7FF */  lui   $at, (0xF7FFFFFF >> 16) # lui $at, 0xf7ff
/* 07CBC8 8007BFC8 3421FFFF */  ori   $at, (0xF7FFFFFF & 0xFFFF) # ori $at, $at, 0xffff
/* 07CBCC 8007BFCC 00A17024 */  and   $t6, $a1, $at
/* 07CBD0 8007BFD0 01E0C027 */  not   $t8, $t7
/* 07CBD4 8007BFD4 01D82824 */  and   $a1, $t6, $t8
/* 07CBD8 8007BFD8 30A20002 */  andi  $v0, $a1, 2
/* 07CBDC 8007BFDC 30790002 */  andi  $t9, $v1, 2
/* 07CBE0 8007BFE0 17220005 */  bne   $t9, $v0, .L8007BFF8
/* 07CBE4 8007BFE4 2401F7FF */   li    $at, -2049
/* 07CBE8 8007BFE8 85090000 */  lh    $t1, ($t0)
/* 07CBEC 8007BFEC 00000000 */  nop   
/* 07CBF0 8007BFF0 11200011 */  beqz  $t1, .L8007C038
/* 07CBF4 8007BFF4 00000000 */   nop   
.L8007BFF8:
/* 07CBF8 8007BFF8 10400009 */  beqz  $v0, .L8007C020
/* 07CBFC 8007BFFC 3C0EB600 */   lui   $t6, 0xb600
/* 07CC00 8007C000 8C820000 */  lw    $v0, ($a0)
/* 07CC04 8007C004 3C0BB700 */  lui   $t3, 0xb700
/* 07CC08 8007C008 244A0008 */  addiu $t2, $v0, 8
/* 07CC0C 8007C00C AC8A0000 */  sw    $t2, ($a0)
/* 07CC10 8007C010 240C0001 */  li    $t4, 1
/* 07CC14 8007C014 AC4C0004 */  sw    $t4, 4($v0)
/* 07CC18 8007C018 10000007 */  b     .L8007C038
/* 07CC1C 8007C01C AC4B0000 */   sw    $t3, ($v0)
.L8007C020:
/* 07CC20 8007C020 8C820000 */  lw    $v0, ($a0)
/* 07CC24 8007C024 240F0001 */  li    $t7, 1
/* 07CC28 8007C028 244D0008 */  addiu $t5, $v0, 8
/* 07CC2C 8007C02C AC8D0000 */  sw    $t5, ($a0)
/* 07CC30 8007C030 AC4F0004 */  sw    $t7, 4($v0)
/* 07CC34 8007C034 AC4E0000 */  sw    $t6, ($v0)
.L8007C038:
/* 07CC38 8007C038 A5000000 */  sh    $zero, ($t0)
/* 07CC3C 8007C03C ACE50000 */  sw    $a1, ($a3)
/* 07CC40 8007C040 3C19800E */  lui   $t9, %hi(D_800DE7C4) # $t9, 0x800e
/* 07CC44 8007C044 8F39E7C4 */  lw    $t9, %lo(D_800DE7C4)($t9)
/* 07CC48 8007C048 00A1C024 */  and   $t8, $a1, $at
/* 07CC4C 8007C04C 17200023 */  bnez  $t9, .L8007C0DC
/* 07CC50 8007C050 03002825 */   move  $a1, $t8
/* 07CC54 8007C054 8CE90000 */  lw    $t1, ($a3)
/* 07CC58 8007C058 3C0B0702 */  lui   $t3, (0x07020010 >> 16) # lui $t3, 0x702
/* 07CC5C 8007C05C 312A0200 */  andi  $t2, $t1, 0x200
/* 07CC60 8007C060 11400011 */  beqz  $t2, .L8007C0A8
/* 07CC64 8007C064 356B0010 */   ori   $t3, (0x07020010 & 0xFFFF) # ori $t3, $t3, 0x10
/* 07CC68 8007C068 8C820000 */  lw    $v0, ($a0)
/* 07CC6C 8007C06C 00186843 */  sra   $t5, $t8, 1
/* 07CC70 8007C070 31AE0001 */  andi  $t6, $t5, 1
/* 07CC74 8007C074 000E7900 */  sll   $t7, $t6, 4
/* 07CC78 8007C078 3C018000 */  lui   $at, 0x8000
/* 07CC7C 8007C07C 3C19800E */  lui   $t9, %hi(dRenderSettingsSpriteCld) # $t9, 0x800e
/* 07CC80 8007C080 2739E848 */  addiu $t9, %lo(dRenderSettingsSpriteCld) # addiu $t9, $t9, -0x17b8
/* 07CC84 8007C084 01E1C021 */  addu  $t8, $t7, $at
/* 07CC88 8007C088 3C0C0702 */  lui   $t4, (0x07020010 >> 16) # lui $t4, 0x702
/* 07CC8C 8007C08C 244B0008 */  addiu $t3, $v0, 8
/* 07CC90 8007C090 AC8B0000 */  sw    $t3, ($a0)
/* 07CC94 8007C094 358C0010 */  ori   $t4, (0x07020010 & 0xFFFF) # ori $t4, $t4, 0x10
/* 07CC98 8007C098 03194821 */  addu  $t1, $t8, $t9
/* 07CC9C 8007C09C AC490004 */  sw    $t1, 4($v0)
/* 07CCA0 8007C0A0 1000001B */  b     .L8007C110
/* 07CCA4 8007C0A4 AC4C0000 */   sw    $t4, ($v0)
.L8007C0A8:
/* 07CCA8 8007C0A8 8C820000 */  lw    $v0, ($a0)
/* 07CCAC 8007C0AC 24ACFFF0 */  addiu $t4, $a1, -0x10
/* 07CCB0 8007C0B0 000C6900 */  sll   $t5, $t4, 4
/* 07CCB4 8007C0B4 3C018000 */  lui   $at, 0x8000
/* 07CCB8 8007C0B8 3C0F800E */  lui   $t7, %hi(dRenderSettingsSpriteXlu) # $t7, 0x800e
/* 07CCBC 8007C0BC 25EFE868 */  addiu $t7, %lo(dRenderSettingsSpriteXlu) # addiu $t7, $t7, -0x1798
/* 07CCC0 8007C0C0 01A17021 */  addu  $t6, $t5, $at
/* 07CCC4 8007C0C4 244A0008 */  addiu $t2, $v0, 8
/* 07CCC8 8007C0C8 AC8A0000 */  sw    $t2, ($a0)
/* 07CCCC 8007C0CC 01CFC021 */  addu  $t8, $t6, $t7
/* 07CCD0 8007C0D0 AC580004 */  sw    $t8, 4($v0)
/* 07CCD4 8007C0D4 1000000E */  b     .L8007C110
/* 07CCD8 8007C0D8 AC4B0000 */   sw    $t3, ($v0)
.L8007C0DC:
/* 07CCDC 8007C0DC 8C820000 */  lw    $v0, ($a0)
/* 07CCE0 8007C0E0 00055100 */  sll   $t2, $a1, 4
/* 07CCE4 8007C0E4 3C018000 */  lui   $at, 0x8000
/* 07CCE8 8007C0E8 3C0C800E */  lui   $t4, %hi(dRenderSettingsCommon) # $t4, 0x800e
/* 07CCEC 8007C0EC 24590008 */  addiu $t9, $v0, 8
/* 07CCF0 8007C0F0 AC990000 */  sw    $t9, ($a0)
/* 07CCF4 8007C0F4 258CE8E8 */  addiu $t4, %lo(dRenderSettingsCommon) # addiu $t4, $t4, -0x1718
/* 07CCF8 8007C0F8 01415821 */  addu  $t3, $t2, $at
/* 07CCFC 8007C0FC 3C090702 */  lui   $t1, (0x07020010 >> 16) # lui $t1, 0x702
/* 07CD00 8007C100 35290010 */  ori   $t1, (0x07020010 & 0xFFFF) # ori $t1, $t1, 0x10
/* 07CD04 8007C104 016C6821 */  addu  $t5, $t3, $t4
/* 07CD08 8007C108 AC4D0004 */  sw    $t5, 4($v0)
/* 07CD0C 8007C10C AC490000 */  sw    $t1, ($v0)
.L8007C110:
/* 07CD10 8007C110 3C018012 */  lui   $at, %hi(gCurrentTextureHeader) # $at, 0x8012
/* 07CD14 8007C114 AC20637C */  sw    $zero, %lo(gCurrentTextureHeader)($at)
/* 07CD18 8007C118 3C018012 */  lui   $at, %hi(gUsingTexture) # $at, 0x8012
/* 07CD1C 8007C11C 240E0001 */  li    $t6, 1
/* 07CD20 8007C120 A42E6380 */  sh    $t6, %lo(gUsingTexture)($at)
.L8007C124:
/* 07CD24 8007C124 03E00008 */  jr    $ra
/* 07CD28 8007C128 00000000 */   nop   

