glabel func_800C1130
/* 0C1D30 800C1130 3C07800E */  lui   $a3, %hi(sTransitionFadeTimer) # $a3, 0x800e
/* 0C1D34 800C1134 24E731B0 */  addiu $a3, %lo(sTransitionFadeTimer) # addiu $a3, $a3, 0x31b0
/* 0C1D38 800C1138 44842000 */  mtc1  $a0, $f4
/* 0C1D3C 800C113C 94E20000 */  lhu   $v0, ($a3)
/* 0C1D40 800C1140 3C03800E */  lui   $v1, 0x800e
/* 0C1D44 800C1144 1840009B */  blez  $v0, .L800C13B4
/* 0C1D48 800C1148 46802020 */   cvt.s.w $f0, $f4
/* 0C1D4C 800C114C 0082082A */  slt   $at, $a0, $v0
/* 0C1D50 800C1150 10200034 */  beqz  $at, .L800C1224
/* 0C1D54 800C1154 3C088013 */   lui   $t0, %hi(D_8012A77C) # $t0, 0x8013
/* 0C1D58 800C1158 2508A77C */  addiu $t0, %lo(D_8012A77C) # addiu $t0, $t0, -0x5884
/* 0C1D5C 800C115C 8D050000 */  lw    $a1, ($t0)
/* 0C1D60 800C1160 00001825 */  move  $v1, $zero
/* 0C1D64 800C1164 18A0002A */  blez  $a1, .L800C1210
/* 0C1D68 800C1168 3C0A8013 */   lui   $t2, %hi(D_8012A774) # $t2, 0x8013
/* 0C1D6C 800C116C 3C098013 */  lui   $t1, %hi(D_8012A770) # $t1, 0x8013
/* 0C1D70 800C1170 2529A770 */  addiu $t1, %lo(D_8012A770) # addiu $t1, $t1, -0x5890
/* 0C1D74 800C1174 00001025 */  move  $v0, $zero
/* 0C1D78 800C1178 254AA774 */  addiu $t2, %lo(D_8012A774) # addiu $t2, $t2, -0x588c
.L800C117C:
/* 0C1D7C 800C117C 8D4F0000 */  lw    $t7, ($t2)
/* 0C1D80 800C1180 8D2E0000 */  lw    $t6, ($t1)
/* 0C1D84 800C1184 01E2C021 */  addu  $t8, $t7, $v0
/* 0C1D88 800C1188 C7080000 */  lwc1  $f8, ($t8)
/* 0C1D8C 800C118C 01C23021 */  addu  $a2, $t6, $v0
/* 0C1D90 800C1190 46080282 */  mul.s $f10, $f0, $f8
/* 0C1D94 800C1194 C4C60000 */  lwc1  $f6, ($a2)
/* 0C1D98 800C1198 24630001 */  addiu $v1, $v1, 1
/* 0C1D9C 800C119C 460A3400 */  add.s $f16, $f6, $f10
/* 0C1DA0 800C11A0 E4D00000 */  swc1  $f16, ($a2)
/* 0C1DA4 800C11A4 8D4B0000 */  lw    $t3, ($t2)
/* 0C1DA8 800C11A8 8D390000 */  lw    $t9, ($t1)
/* 0C1DAC 800C11AC 01626021 */  addu  $t4, $t3, $v0
/* 0C1DB0 800C11B0 C5840004 */  lwc1  $f4, 4($t4)
/* 0C1DB4 800C11B4 03223021 */  addu  $a2, $t9, $v0
/* 0C1DB8 800C11B8 46040202 */  mul.s $f8, $f0, $f4
/* 0C1DBC 800C11BC C4D20004 */  lwc1  $f18, 4($a2)
/* 0C1DC0 800C11C0 00000000 */  nop   
/* 0C1DC4 800C11C4 46089180 */  add.s $f6, $f18, $f8
/* 0C1DC8 800C11C8 E4C60004 */  swc1  $f6, 4($a2)
/* 0C1DCC 800C11CC 8D4E0000 */  lw    $t6, ($t2)
/* 0C1DD0 800C11D0 8D2D0000 */  lw    $t5, ($t1)
/* 0C1DD4 800C11D4 01C27821 */  addu  $t7, $t6, $v0
/* 0C1DD8 800C11D8 C5F00008 */  lwc1  $f16, 8($t7)
/* 0C1DDC 800C11DC 01A23021 */  addu  $a2, $t5, $v0
/* 0C1DE0 800C11E0 46100102 */  mul.s $f4, $f0, $f16
/* 0C1DE4 800C11E4 C4CA0008 */  lwc1  $f10, 8($a2)
/* 0C1DE8 800C11E8 2442000C */  addiu $v0, $v0, 0xc
/* 0C1DEC 800C11EC 46045480 */  add.s $f18, $f10, $f4
/* 0C1DF0 800C11F0 E4D20008 */  swc1  $f18, 8($a2)
/* 0C1DF4 800C11F4 8D050000 */  lw    $a1, ($t0)
/* 0C1DF8 800C11F8 00000000 */  nop   
/* 0C1DFC 800C11FC 0065082A */  slt   $at, $v1, $a1
/* 0C1E00 800C1200 1420FFDE */  bnez  $at, .L800C117C
/* 0C1E04 800C1204 00000000 */   nop   
/* 0C1E08 800C1208 94E20000 */  lhu   $v0, ($a3)
/* 0C1E0C 800C120C 00001825 */  move  $v1, $zero
.L800C1210:
/* 0C1E10 800C1210 3C098013 */  lui   $t1, %hi(D_8012A770) # $t1, 0x8013
/* 0C1E14 800C1214 0044C023 */  subu  $t8, $v0, $a0
/* 0C1E18 800C1218 2529A770 */  addiu $t1, %lo(D_8012A770) # addiu $t1, $t1, -0x5890
/* 0C1E1C 800C121C 10000026 */  b     .L800C12B8
/* 0C1E20 800C1220 A4F80000 */   sh    $t8, ($a3)
.L800C1224:
/* 0C1E24 800C1224 3C088013 */  lui   $t0, %hi(D_8012A77C) # $t0, 0x8013
/* 0C1E28 800C1228 2508A77C */  addiu $t0, %lo(D_8012A77C) # addiu $t0, $t0, -0x5884
/* 0C1E2C 800C122C 8D050000 */  lw    $a1, ($t0)
/* 0C1E30 800C1230 00001825 */  move  $v1, $zero
/* 0C1E34 800C1234 18A0001D */  blez  $a1, .L800C12AC
/* 0C1E38 800C1238 3C098013 */   lui   $t1, %hi(D_8012A770) # $t1, 0x8013
/* 0C1E3C 800C123C 3C048013 */  lui   $a0, %hi(D_8012A778) # $a0, 0x8013
/* 0C1E40 800C1240 2484A778 */  addiu $a0, %lo(D_8012A778) # addiu $a0, $a0, -0x5888
/* 0C1E44 800C1244 2529A770 */  addiu $t1, %lo(D_8012A770) # addiu $t1, $t1, -0x5890
/* 0C1E48 800C1248 00001025 */  move  $v0, $zero
.L800C124C:
/* 0C1E4C 800C124C 8C990000 */  lw    $t9, ($a0)
/* 0C1E50 800C1250 8D2C0000 */  lw    $t4, ($t1)
/* 0C1E54 800C1254 03225821 */  addu  $t3, $t9, $v0
/* 0C1E58 800C1258 C5680000 */  lwc1  $f8, ($t3)
/* 0C1E5C 800C125C 01826821 */  addu  $t5, $t4, $v0
/* 0C1E60 800C1260 E5A80000 */  swc1  $f8, ($t5)
/* 0C1E64 800C1264 8C8E0000 */  lw    $t6, ($a0)
/* 0C1E68 800C1268 8D380000 */  lw    $t8, ($t1)
/* 0C1E6C 800C126C 01C27821 */  addu  $t7, $t6, $v0
/* 0C1E70 800C1270 C5E60004 */  lwc1  $f6, 4($t7)
/* 0C1E74 800C1274 0302C821 */  addu  $t9, $t8, $v0
/* 0C1E78 800C1278 E7260004 */  swc1  $f6, 4($t9)
/* 0C1E7C 800C127C 8C8B0000 */  lw    $t3, ($a0)
/* 0C1E80 800C1280 8D2D0000 */  lw    $t5, ($t1)
/* 0C1E84 800C1284 01626021 */  addu  $t4, $t3, $v0
/* 0C1E88 800C1288 C5900008 */  lwc1  $f16, 8($t4)
/* 0C1E8C 800C128C 01A27021 */  addu  $t6, $t5, $v0
/* 0C1E90 800C1290 E5D00008 */  swc1  $f16, 8($t6)
/* 0C1E94 800C1294 8D050000 */  lw    $a1, ($t0)
/* 0C1E98 800C1298 24630001 */  addiu $v1, $v1, 1
/* 0C1E9C 800C129C 0065082A */  slt   $at, $v1, $a1
/* 0C1EA0 800C12A0 1420FFEA */  bnez  $at, .L800C124C
/* 0C1EA4 800C12A4 2442000C */   addiu $v0, $v0, 0xc
/* 0C1EA8 800C12A8 00001825 */  move  $v1, $zero
.L800C12AC:
/* 0C1EAC 800C12AC 3C098013 */  lui   $t1, %hi(D_8012A770) # $t1, 0x8013
/* 0C1EB0 800C12B0 2529A770 */  addiu $t1, %lo(D_8012A770) # addiu $t1, $t1, -0x5890
/* 0C1EB4 800C12B4 A4E00000 */  sh    $zero, ($a3)
.L800C12B8:
/* 0C1EB8 800C12B8 18A00048 */  blez  $a1, .L800C13DC
/* 0C1EBC 800C12BC 00001025 */   move  $v0, $zero
/* 0C1EC0 800C12C0 3C06800E */  lui   $a2, %hi(sTransitionTaskNum) # $a2, 0x800e
/* 0C1EC4 800C12C4 3C05800E */  lui   $a1, %hi(sTransitionVtx) # $a1, 0x800e
/* 0C1EC8 800C12C8 24A531C0 */  addiu $a1, %lo(sTransitionVtx) # addiu $a1, $a1, 0x31c0
/* 0C1ECC 800C12CC 24C631D0 */  addiu $a2, %lo(sTransitionTaskNum) # addiu $a2, $a2, 0x31d0
/* 0C1ED0 800C12D0 00002025 */  move  $a0, $zero
.L800C12D4:
/* 0C1ED4 800C12D4 4459F800 */  cfc1  $t9, $31
/* 0C1ED8 800C12D8 8D2F0000 */  lw    $t7, ($t1)
/* 0C1EDC 800C12DC 37210003 */  ori   $at, $t9, 3
/* 0C1EE0 800C12E0 38210002 */  xori  $at, $at, 2
/* 0C1EE4 800C12E4 01E2C021 */  addu  $t8, $t7, $v0
/* 0C1EE8 800C12E8 C70A0000 */  lwc1  $f10, ($t8)
/* 0C1EEC 800C12EC 44C1F800 */  ctc1  $at, $31
/* 0C1EF0 800C12F0 8CCC0000 */  lw    $t4, ($a2)
/* 0C1EF4 800C12F4 46005124 */  cvt.w.s $f4, $f10
/* 0C1EF8 800C12F8 000C6880 */  sll   $t5, $t4, 2
/* 0C1EFC 800C12FC 00AD7021 */  addu  $t6, $a1, $t5
/* 0C1F00 800C1300 44D9F800 */  ctc1  $t9, $31
/* 0C1F04 800C1304 8DCF0000 */  lw    $t7, ($t6)
/* 0C1F08 800C1308 440B2000 */  mfc1  $t3, $f4
/* 0C1F0C 800C130C 01E4C021 */  addu  $t8, $t7, $a0
/* 0C1F10 800C1310 444DF800 */  cfc1  $t5, $31
/* 0C1F14 800C1314 A70B0000 */  sh    $t3, ($t8)
/* 0C1F18 800C1318 8D390000 */  lw    $t9, ($t1)
/* 0C1F1C 800C131C 35A10003 */  ori   $at, $t5, 3
/* 0C1F20 800C1320 38210002 */  xori  $at, $at, 2
/* 0C1F24 800C1324 03226021 */  addu  $t4, $t9, $v0
/* 0C1F28 800C1328 C5920004 */  lwc1  $f18, 4($t4)
/* 0C1F2C 800C132C 44C1F800 */  ctc1  $at, $31
/* 0C1F30 800C1330 8CCF0000 */  lw    $t7, ($a2)
/* 0C1F34 800C1334 46009224 */  cvt.w.s $f8, $f18
/* 0C1F38 800C1338 000F5880 */  sll   $t3, $t7, 2
/* 0C1F3C 800C133C 00ABC021 */  addu  $t8, $a1, $t3
/* 0C1F40 800C1340 44CDF800 */  ctc1  $t5, $31
/* 0C1F44 800C1344 8F190000 */  lw    $t9, ($t8)
/* 0C1F48 800C1348 440E4000 */  mfc1  $t6, $f8
/* 0C1F4C 800C134C 03246021 */  addu  $t4, $t9, $a0
/* 0C1F50 800C1350 444BF800 */  cfc1  $t3, $31
/* 0C1F54 800C1354 A58E0002 */  sh    $t6, 2($t4)
/* 0C1F58 800C1358 8D2D0000 */  lw    $t5, ($t1)
/* 0C1F5C 800C135C 35610003 */  ori   $at, $t3, 3
/* 0C1F60 800C1360 8CD90000 */  lw    $t9, ($a2)
/* 0C1F64 800C1364 38210002 */  xori  $at, $at, 2
/* 0C1F68 800C1368 01A27821 */  addu  $t7, $t5, $v0
/* 0C1F6C 800C136C C5E60008 */  lwc1  $f6, 8($t7)
/* 0C1F70 800C1370 44C1F800 */  ctc1  $at, $31
/* 0C1F74 800C1374 00197080 */  sll   $t6, $t9, 2
/* 0C1F78 800C1378 46003424 */  cvt.w.s $f16, $f6
/* 0C1F7C 800C137C 00AE6021 */  addu  $t4, $a1, $t6
/* 0C1F80 800C1380 8D8D0000 */  lw    $t5, ($t4)
/* 0C1F84 800C1384 44188000 */  mfc1  $t8, $f16
/* 0C1F88 800C1388 01A47821 */  addu  $t7, $t5, $a0
/* 0C1F8C 800C138C 44CBF800 */  ctc1  $t3, $31
/* 0C1F90 800C1390 A1F80009 */  sb    $t8, 9($t7)
/* 0C1F94 800C1394 8D0B0000 */  lw    $t3, ($t0)
/* 0C1F98 800C1398 24630001 */  addiu $v1, $v1, 1
/* 0C1F9C 800C139C 006B082A */  slt   $at, $v1, $t3
/* 0C1FA0 800C13A0 2484000A */  addiu $a0, $a0, 0xa
/* 0C1FA4 800C13A4 1420FFCB */  bnez  $at, .L800C12D4
/* 0C1FA8 800C13A8 2442000C */   addiu $v0, $v0, 0xc
/* 0C1FAC 800C13AC 03E00008 */  jr    $ra
/* 0C1FB0 800C13B0 00000000 */   nop   

.L800C13B4:
/* 0C1FB4 800C13B4 246331B4 */  addiu $v1, $v1, %lo(sTransitionFlags)# 0x31b4
/* 0C1FB8 800C13B8 94620000 */  lhu   $v0, ($v1)
/* 0C1FBC 800C13BC 3401FFFF */  li    $at, 65535
/* 0C1FC0 800C13C0 10410006 */  beq   $v0, $at, .L800C13DC
/* 0C1FC4 800C13C4 0082082A */   slt   $at, $a0, $v0
/* 0C1FC8 800C13C8 10200003 */  beqz  $at, .L800C13D8
/* 0C1FCC 800C13CC 0044C823 */   subu  $t9, $v0, $a0
/* 0C1FD0 800C13D0 03E00008 */  jr    $ra
/* 0C1FD4 800C13D4 A4790000 */   sh    $t9, ($v1)

.L800C13D8:
/* 0C1FD8 800C13D8 A4600000 */  sh    $zero, ($v1)
.L800C13DC:
/* 0C1FDC 800C13DC 03E00008 */  jr    $ra
/* 0C1FE0 800C13E0 00000000 */   nop   

