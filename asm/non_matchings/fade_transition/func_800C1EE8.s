.late_rodata
glabel D_800E932C
.float 1.2

.text
glabel func_800C1EE8
/* 0C2AE8 800C1EE8 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 0C2AEC 800C1EEC 3C03800E */  lui   $v1, %hi(sTransitionFadeTimer) # $v1, 0x800e
/* 0C2AF0 800C1EF0 246331B0 */  addiu $v1, %lo(sTransitionFadeTimer) # addiu $v1, $v1, 0x31b0
/* 0C2AF4 800C1EF4 44842000 */  mtc1  $a0, $f4
/* 0C2AF8 800C1EF8 94620000 */  lhu   $v0, ($v1)
/* 0C2AFC 800C1EFC AFBF004C */  sw    $ra, 0x4c($sp)
/* 0C2B00 800C1F00 AFBE0048 */  sw    $fp, 0x48($sp)
/* 0C2B04 800C1F04 AFB70044 */  sw    $s7, 0x44($sp)
/* 0C2B08 800C1F08 AFB60040 */  sw    $s6, 0x40($sp)
/* 0C2B0C 800C1F0C AFB5003C */  sw    $s5, 0x3c($sp)
/* 0C2B10 800C1F10 AFB40038 */  sw    $s4, 0x38($sp)
/* 0C2B14 800C1F14 AFB30034 */  sw    $s3, 0x34($sp)
/* 0C2B18 800C1F18 AFB20030 */  sw    $s2, 0x30($sp)
/* 0C2B1C 800C1F1C AFB1002C */  sw    $s1, 0x2c($sp)
/* 0C2B20 800C1F20 AFB00028 */  sw    $s0, 0x28($sp)
/* 0C2B24 800C1F24 E7B70020 */  swc1  $f23, 0x20($sp)
/* 0C2B28 800C1F28 E7B60024 */  swc1  $f22, 0x24($sp)
/* 0C2B2C 800C1F2C E7B50018 */  swc1  $f21, 0x18($sp)
/* 0C2B30 800C1F30 E7B4001C */  swc1  $f20, 0x1c($sp)
/* 0C2B34 800C1F34 184000B4 */  blez  $v0, .L800C2208
/* 0C2B38 800C1F38 46802020 */   cvt.s.w $f0, $f4
/* 0C2B3C 800C1F3C 0082082A */  slt   $at, $a0, $v0
/* 0C2B40 800C1F40 10200014 */  beqz  $at, .L800C1F94
/* 0C2B44 800C1F44 00009825 */   move  $s3, $zero
/* 0C2B48 800C1F48 3C018013 */  lui   $at, %hi(D_8012A760) # $at, 0x8013
/* 0C2B4C 800C1F4C C428A760 */  lwc1  $f8, %lo(D_8012A760)($at)
/* 0C2B50 800C1F50 3C178013 */  lui   $s7, %hi(D_8012A758) # $s7, 0x8013
/* 0C2B54 800C1F54 46080282 */  mul.s $f10, $f0, $f8
/* 0C2B58 800C1F58 26F7A758 */  addiu $s7, %lo(D_8012A758) # addiu $s7, $s7, -0x58a8
/* 0C2B5C 800C1F5C C6E60000 */  lwc1  $f6, ($s7)
/* 0C2B60 800C1F60 3C018013 */  lui   $at, %hi(D_8012A764) # $at, 0x8013
/* 0C2B64 800C1F64 460A3400 */  add.s $f16, $f6, $f10
/* 0C2B68 800C1F68 3C1E8013 */  lui   $fp, %hi(D_8012A75C) # $fp, 0x8013
/* 0C2B6C 800C1F6C E6F00000 */  swc1  $f16, ($s7)
/* 0C2B70 800C1F70 C424A764 */  lwc1  $f4, %lo(D_8012A764)($at)
/* 0C2B74 800C1F74 27DEA75C */  addiu $fp, %lo(D_8012A75C) # addiu $fp, $fp, -0x58a4
/* 0C2B78 800C1F78 46040202 */  mul.s $f8, $f0, $f4
/* 0C2B7C 800C1F7C C7D20000 */  lwc1  $f18, ($fp)
/* 0C2B80 800C1F80 00447023 */  subu  $t6, $v0, $a0
/* 0C2B84 800C1F84 A46E0000 */  sh    $t6, ($v1)
/* 0C2B88 800C1F88 46089180 */  add.s $f6, $f18, $f8
/* 0C2B8C 800C1F8C 1000000C */  b     .L800C1FC0
/* 0C2B90 800C1F90 E7C60000 */   swc1  $f6, ($fp)
.L800C1F94:
/* 0C2B94 800C1F94 3C018013 */  lui   $at, %hi(D_8012A768) # $at, 0x8013
/* 0C2B98 800C1F98 C42AA768 */  lwc1  $f10, %lo(D_8012A768)($at)
/* 0C2B9C 800C1F9C 3C178013 */  lui   $s7, %hi(D_8012A758) # $s7, 0x8013
/* 0C2BA0 800C1FA0 26F7A758 */  addiu $s7, %lo(D_8012A758) # addiu $s7, $s7, -0x58a8
/* 0C2BA4 800C1FA4 3C018013 */  lui   $at, %hi(D_8012A76C) # $at, 0x8013
/* 0C2BA8 800C1FA8 E6EA0000 */  swc1  $f10, ($s7)
/* 0C2BAC 800C1FAC C430A76C */  lwc1  $f16, %lo(D_8012A76C)($at)
/* 0C2BB0 800C1FB0 3C1E8013 */  lui   $fp, %hi(D_8012A75C) # $fp, 0x8013
/* 0C2BB4 800C1FB4 27DEA75C */  addiu $fp, %lo(D_8012A75C) # addiu $fp, $fp, -0x58a4
/* 0C2BB8 800C1FB8 A4600000 */  sh    $zero, ($v1)
/* 0C2BBC 800C1FBC E7D00000 */  swc1  $f16, ($fp)
.L800C1FC0:
/* 0C2BC0 800C1FC0 3C01800F */  lui   $at, %hi(D_800E932C) # $at, 0x800f
/* 0C2BC4 800C1FC4 3C11800E */  lui   $s1, %hi(sTransitionTaskNum) # $s1, 0x800e
/* 0C2BC8 800C1FC8 3C10800E */  lui   $s0, %hi(sTransitionVtx) # $s0, 0x800e
/* 0C2BCC 800C1FCC C436932C */  lwc1  $f22, %lo(D_800E932C)($at)
/* 0C2BD0 800C1FD0 261031C0 */  addiu $s0, %lo(sTransitionVtx) # addiu $s0, $s0, 0x31c0
/* 0C2BD4 800C1FD4 263131D0 */  addiu $s1, %lo(sTransitionTaskNum) # addiu $s1, $s1, 0x31d0
/* 0C2BD8 800C1FD8 00009025 */  move  $s2, $zero
/* 0C2BDC 800C1FDC 24160009 */  li    $s6, 9
/* 0C2BE0 800C1FE0 2415000A */  li    $s5, 10
.L800C1FE4:
/* 0C2BE4 800C1FE4 0013A400 */  sll   $s4, $s3, 0x10
/* 0C2BE8 800C1FE8 00147C03 */  sra   $t7, $s4, 0x10
/* 0C2BEC 800C1FEC 000F2400 */  sll   $a0, $t7, 0x10
/* 0C2BF0 800C1FF0 0004C403 */  sra   $t8, $a0, 0x10
/* 0C2BF4 800C1FF4 03002025 */  move  $a0, $t8
/* 0C2BF8 800C1FF8 0C01C1F1 */  jal   func_800707C4
/* 0C2BFC 800C1FFC 01E0A025 */   move  $s4, $t7
/* 0C2C00 800C2000 C6E40000 */  lwc1  $f4, ($s7)
/* 0C2C04 800C2004 00142400 */  sll   $a0, $s4, 0x10
/* 0C2C08 800C2008 0004CC03 */  sra   $t9, $a0, 0x10
/* 0C2C0C 800C200C 46040502 */  mul.s $f20, $f0, $f4
/* 0C2C10 800C2010 0C01C1FE */  jal   func_800707F8
/* 0C2C14 800C2014 03202025 */   move  $a0, $t9
/* 0C2C18 800C2018 C7D20000 */  lwc1  $f18, ($fp)
/* 0C2C1C 800C201C 00124040 */  sll   $t0, $s2, 1
/* 0C2C20 800C2020 46120082 */  mul.s $f2, $f0, $f18
/* 0C2C24 800C2024 8E2A0000 */  lw    $t2, ($s1)
/* 0C2C28 800C2028 01150019 */  multu $t0, $s5
/* 0C2C2C 800C202C 000A5880 */  sll   $t3, $t2, 2
/* 0C2C30 800C2030 4616A202 */  mul.s $f8, $f20, $f22
/* 0C2C34 800C2034 020B6021 */  addu  $t4, $s0, $t3
/* 0C2C38 800C2038 8D8D0000 */  lw    $t5, ($t4)
/* 0C2C3C 800C203C 26520001 */  addiu $s2, $s2, 1
/* 0C2C40 800C2040 4449F800 */  cfc1  $t1, $31
/* 0C2C44 800C2044 26731000 */  addiu $s3, $s3, 0x1000
/* 0C2C48 800C2048 35210003 */  ori   $at, $t1, 3
/* 0C2C4C 800C204C 38210002 */  xori  $at, $at, 2
/* 0C2C50 800C2050 44C1F800 */  ctc1  $at, $31
/* 0C2C54 800C2054 00000000 */  nop   
/* 0C2C58 800C2058 460041A4 */  cvt.w.s $f6, $f8
/* 0C2C5C 800C205C 00001012 */  mflo  $v0
/* 0C2C60 800C2060 44C9F800 */  ctc1  $t1, $31
/* 0C2C64 800C2064 44043000 */  mfc1  $a0, $f6
/* 0C2C68 800C2068 46161282 */  mul.s $f10, $f2, $f22
/* 0C2C6C 800C206C 01A27021 */  addu  $t6, $t5, $v0
/* 0C2C70 800C2070 A5C4000A */  sh    $a0, 0xa($t6)
/* 0C2C74 800C2074 8E380000 */  lw    $t8, ($s1)
/* 0C2C78 800C2078 444FF800 */  cfc1  $t7, $31
/* 0C2C7C 800C207C 0018C880 */  sll   $t9, $t8, 2
/* 0C2C80 800C2080 35E10003 */  ori   $at, $t7, 3
/* 0C2C84 800C2084 38210002 */  xori  $at, $at, 2
/* 0C2C88 800C2088 44C1F800 */  ctc1  $at, $31
/* 0C2C8C 800C208C 02194021 */  addu  $t0, $s0, $t9
/* 0C2C90 800C2090 46005424 */  cvt.w.s $f16, $f10
/* 0C2C94 800C2094 8D090000 */  lw    $t1, ($t0)
/* 0C2C98 800C2098 44038000 */  mfc1  $v1, $f16
/* 0C2C9C 800C209C 01225021 */  addu  $t2, $t1, $v0
/* 0C2CA0 800C20A0 A543000C */  sh    $v1, 0xc($t2)
/* 0C2CA4 800C20A4 8E2C0000 */  lw    $t4, ($s1)
/* 0C2CA8 800C20A8 44CFF800 */  ctc1  $t7, $31
/* 0C2CAC 800C20AC 000C6880 */  sll   $t5, $t4, 2
/* 0C2CB0 800C20B0 020D7021 */  addu  $t6, $s0, $t5
/* 0C2CB4 800C20B4 8DCF0000 */  lw    $t7, ($t6)
/* 0C2CB8 800C20B8 00043823 */  negu  $a3, $a0
/* 0C2CBC 800C20BC 01E2C021 */  addu  $t8, $t7, $v0
/* 0C2CC0 800C20C0 A7070172 */  sh    $a3, 0x172($t8)
/* 0C2CC4 800C20C4 8E390000 */  lw    $t9, ($s1)
/* 0C2CC8 800C20C8 00000000 */  nop   
/* 0C2CCC 800C20CC 00194080 */  sll   $t0, $t9, 2
/* 0C2CD0 800C20D0 02084821 */  addu  $t1, $s0, $t0
/* 0C2CD4 800C20D4 8D2A0000 */  lw    $t2, ($t1)
/* 0C2CD8 800C20D8 00000000 */  nop   
/* 0C2CDC 800C20DC 01425821 */  addu  $t3, $t2, $v0
/* 0C2CE0 800C20E0 A5630174 */  sh    $v1, 0x174($t3)
/* 0C2CE4 800C20E4 8E2C0000 */  lw    $t4, ($s1)
/* 0C2CE8 800C20E8 00000000 */  nop   
/* 0C2CEC 800C20EC 000C6880 */  sll   $t5, $t4, 2
/* 0C2CF0 800C20F0 020D7021 */  addu  $t6, $s0, $t5
/* 0C2CF4 800C20F4 8DCF0000 */  lw    $t7, ($t6)
/* 0C2CF8 800C20F8 00000000 */  nop   
/* 0C2CFC 800C20FC 01E2C021 */  addu  $t8, $t7, $v0
/* 0C2D00 800C2100 A70400B4 */  sh    $a0, 0xb4($t8)
/* 0C2D04 800C2104 8E390000 */  lw    $t9, ($s1)
/* 0C2D08 800C2108 00000000 */  nop   
/* 0C2D0C 800C210C 00194080 */  sll   $t0, $t9, 2
/* 0C2D10 800C2110 02084821 */  addu  $t1, $s0, $t0
/* 0C2D14 800C2114 8D2A0000 */  lw    $t2, ($t1)
/* 0C2D18 800C2118 00000000 */  nop   
/* 0C2D1C 800C211C 01425821 */  addu  $t3, $t2, $v0
/* 0C2D20 800C2120 A56300B6 */  sh    $v1, 0xb6($t3)
/* 0C2D24 800C2124 8E2C0000 */  lw    $t4, ($s1)
/* 0C2D28 800C2128 00000000 */  nop   
/* 0C2D2C 800C212C 000C6880 */  sll   $t5, $t4, 2
/* 0C2D30 800C2130 020D7021 */  addu  $t6, $s0, $t5
/* 0C2D34 800C2134 8DCF0000 */  lw    $t7, ($t6)
/* 0C2D38 800C2138 444CF800 */  cfc1  $t4, $31
/* 0C2D3C 800C213C 01E2C021 */  addu  $t8, $t7, $v0
/* 0C2D40 800C2140 A707021C */  sh    $a3, 0x21c($t8)
/* 0C2D44 800C2144 8E390000 */  lw    $t9, ($s1)
/* 0C2D48 800C2148 35810003 */  ori   $at, $t4, 3
/* 0C2D4C 800C214C 00194080 */  sll   $t0, $t9, 2
/* 0C2D50 800C2150 02084821 */  addu  $t1, $s0, $t0
/* 0C2D54 800C2154 8D2A0000 */  lw    $t2, ($t1)
/* 0C2D58 800C2158 38210002 */  xori  $at, $at, 2
/* 0C2D5C 800C215C 44C1F800 */  ctc1  $at, $31
/* 0C2D60 800C2160 01425821 */  addu  $t3, $t2, $v0
/* 0C2D64 800C2164 A563021E */  sh    $v1, 0x21e($t3)
/* 0C2D68 800C2168 8E2D0000 */  lw    $t5, ($s1)
/* 0C2D6C 800C216C 4600A124 */  cvt.w.s $f4, $f20
/* 0C2D70 800C2170 000D7080 */  sll   $t6, $t5, 2
/* 0C2D74 800C2174 44CCF800 */  ctc1  $t4, $31
/* 0C2D78 800C2178 020E7821 */  addu  $t7, $s0, $t6
/* 0C2D7C 800C217C 8DF80000 */  lw    $t8, ($t7)
/* 0C2D80 800C2180 44052000 */  mfc1  $a1, $f4
/* 0C2D84 800C2184 4448F800 */  cfc1  $t0, $31
/* 0C2D88 800C2188 0302C821 */  addu  $t9, $t8, $v0
/* 0C2D8C 800C218C A72500BE */  sh    $a1, 0xbe($t9)
/* 0C2D90 800C2190 35010003 */  ori   $at, $t0, 3
/* 0C2D94 800C2194 8E290000 */  lw    $t1, ($s1)
/* 0C2D98 800C2198 38210002 */  xori  $at, $at, 2
/* 0C2D9C 800C219C 44C1F800 */  ctc1  $at, $31
/* 0C2DA0 800C21A0 00095080 */  sll   $t2, $t1, 2
/* 0C2DA4 800C21A4 460014A4 */  cvt.w.s $f18, $f2
/* 0C2DA8 800C21A8 020A5821 */  addu  $t3, $s0, $t2
/* 0C2DAC 800C21AC 8D6C0000 */  lw    $t4, ($t3)
/* 0C2DB0 800C21B0 44069000 */  mfc1  $a2, $f18
/* 0C2DB4 800C21B4 01826821 */  addu  $t5, $t4, $v0
/* 0C2DB8 800C21B8 A5A600C0 */  sh    $a2, 0xc0($t5)
/* 0C2DBC 800C21BC 8E390000 */  lw    $t9, ($s1)
/* 0C2DC0 800C21C0 44C8F800 */  ctc1  $t0, $31
/* 0C2DC4 800C21C4 00194080 */  sll   $t0, $t9, 2
/* 0C2DC8 800C21C8 02084821 */  addu  $t1, $s0, $t0
/* 0C2DCC 800C21CC 8D2A0000 */  lw    $t2, ($t1)
/* 0C2DD0 800C21D0 0005C023 */  negu  $t8, $a1
/* 0C2DD4 800C21D4 01425821 */  addu  $t3, $t2, $v0
/* 0C2DD8 800C21D8 A5780226 */  sh    $t8, 0x226($t3)
/* 0C2DDC 800C21DC 8E2C0000 */  lw    $t4, ($s1)
/* 0C2DE0 800C21E0 00000000 */  nop   
/* 0C2DE4 800C21E4 000C6880 */  sll   $t5, $t4, 2
/* 0C2DE8 800C21E8 020D7021 */  addu  $t6, $s0, $t5
/* 0C2DEC 800C21EC 8DCF0000 */  lw    $t7, ($t6)
/* 0C2DF0 800C21F0 00000000 */  nop   
/* 0C2DF4 800C21F4 01E2C821 */  addu  $t9, $t7, $v0
/* 0C2DF8 800C21F8 1656FF7A */  bne   $s2, $s6, .L800C1FE4
/* 0C2DFC 800C21FC A7260228 */   sh    $a2, 0x228($t9)
/* 0C2E00 800C2200 1000000D */  b     .L800C2238
/* 0C2E04 800C2204 8FBF004C */   lw    $ra, 0x4c($sp)
.L800C2208:
/* 0C2E08 800C2208 3C03800E */  lui   $v1, %hi(sTransitionFlags) # $v1, 0x800e
/* 0C2E0C 800C220C 246331B4 */  addiu $v1, %lo(sTransitionFlags) # addiu $v1, $v1, 0x31b4
/* 0C2E10 800C2210 94620000 */  lhu   $v0, ($v1)
/* 0C2E14 800C2214 3401FFFF */  li    $at, 65535
/* 0C2E18 800C2218 10410006 */  beq   $v0, $at, .L800C2234
/* 0C2E1C 800C221C 0082082A */   slt   $at, $a0, $v0
/* 0C2E20 800C2220 10200003 */  beqz  $at, .L800C2230
/* 0C2E24 800C2224 00444023 */   subu  $t0, $v0, $a0
/* 0C2E28 800C2228 10000002 */  b     .L800C2234
/* 0C2E2C 800C222C A4680000 */   sh    $t0, ($v1)
.L800C2230:
/* 0C2E30 800C2230 A4600000 */  sh    $zero, ($v1)
.L800C2234:
/* 0C2E34 800C2234 8FBF004C */  lw    $ra, 0x4c($sp)
.L800C2238:
/* 0C2E38 800C2238 C7B50018 */  lwc1  $f21, 0x18($sp)
/* 0C2E3C 800C223C C7B4001C */  lwc1  $f20, 0x1c($sp)
/* 0C2E40 800C2240 C7B70020 */  lwc1  $f23, 0x20($sp)
/* 0C2E44 800C2244 C7B60024 */  lwc1  $f22, 0x24($sp)
/* 0C2E48 800C2248 8FB00028 */  lw    $s0, 0x28($sp)
/* 0C2E4C 800C224C 8FB1002C */  lw    $s1, 0x2c($sp)
/* 0C2E50 800C2250 8FB20030 */  lw    $s2, 0x30($sp)
/* 0C2E54 800C2254 8FB30034 */  lw    $s3, 0x34($sp)
/* 0C2E58 800C2258 8FB40038 */  lw    $s4, 0x38($sp)
/* 0C2E5C 800C225C 8FB5003C */  lw    $s5, 0x3c($sp)
/* 0C2E60 800C2260 8FB60040 */  lw    $s6, 0x40($sp)
/* 0C2E64 800C2264 8FB70044 */  lw    $s7, 0x44($sp)
/* 0C2E68 800C2268 8FBE0048 */  lw    $fp, 0x48($sp)
/* 0C2E6C 800C226C 03E00008 */  jr    $ra
/* 0C2E70 800C2270 27BD0050 */   addiu $sp, $sp, 0x50

