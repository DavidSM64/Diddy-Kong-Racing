glabel func_8006A1C4
/* 06ADC4 8006A1C4 27BDFFA8 */  addiu $sp, $sp, -0x58
/* 06ADC8 8006A1C8 AFB20020 */  sw    $s2, 0x20($sp)
/* 06ADCC 8006A1CC 00809025 */  move  $s2, $a0
/* 06ADD0 8006A1D0 AFBF0024 */  sw    $ra, 0x24($sp)
/* 06ADD4 8006A1D4 AFA5005C */  sw    $a1, 0x5c($sp)
/* 06ADD8 8006A1D8 3C048012 */  lui   $a0, %hi(sSIMesgQueue) # $a0, 0x8012
/* 06ADDC 8006A1DC AFB1001C */  sw    $s1, 0x1c($sp)
/* 06ADE0 8006A1E0 AFB00018 */  sw    $s0, 0x18($sp)
/* 06ADE4 8006A1E4 248410E0 */  addiu $a0, %lo(sSIMesgQueue) # addiu $a0, $a0, 0x10e0
/* 06ADE8 8006A1E8 27A50050 */  addiu $a1, $sp, 0x50
/* 06ADEC 8006A1EC 0C0322EC */  jal   osRecvMesg
/* 06ADF0 8006A1F0 00003025 */   move  $a2, $zero
/* 06ADF4 8006A1F4 1440005D */  bnez  $v0, .L8006A36C
/* 06ADF8 8006A1F8 3C068012 */   lui   $a2, %hi(sControllerData+24) # $a2, 0x8012
/* 06ADFC 8006A1FC 3C028012 */  lui   $v0, %hi(sControllerData) # $v0, 0x8012
/* 06AE00 8006A200 3C038012 */  lui   $v1, %hi(sControllerData+24) # $v1, 0x8012
/* 06AE04 8006A204 24631128 */  addiu $v1, %lo(sControllerData+24) # addiu $v1, $v1, 0x1128
/* 06AE08 8006A208 24421110 */  addiu $v0, %lo(sControllerData) # addiu $v0, $v0, 0x1110
/* 06AE0C 8006A20C 24C61128 */  addiu $a2, %lo(sControllerData+24) # addiu $a2, $a2, 0x1128
.L8006A210:
/* 06AE10 8006A210 88410000 */  lwl   $at, ($v0)
/* 06AE14 8006A214 98410003 */  lwr   $at, 3($v0)
/* 06AE18 8006A218 24420006 */  addiu $v0, $v0, 6
/* 06AE1C 8006A21C A8C10000 */  swl   $at, ($a2)
/* 06AE20 8006A220 B8C10003 */  swr   $at, 3($a2)
/* 06AE24 8006A224 9441FFFE */  lhu   $at, -2($v0)
/* 06AE28 8006A228 24C60006 */  addiu $a2, $a2, 6
/* 06AE2C 8006A22C A4C1FFFE */  sh    $at, -2($a2)
/* 06AE30 8006A230 0043082B */  sltu  $at, $v0, $v1
/* 06AE34 8006A234 1420FFF6 */  bnez  $at, .L8006A210
/* 06AE38 8006A238 00000000 */   nop   
/* 06AE3C 8006A23C 3C048012 */  lui   $a0, %hi(sControllerData) # $a0, 0x8012
/* 06AE40 8006A240 0C033429 */  jal   osContGetReadData
/* 06AE44 8006A244 24841110 */   addiu $a0, %lo(sControllerData) # addiu $a0, $a0, 0x1110
/* 06AE48 8006A248 12400043 */  beqz  $s2, .L8006A358
/* 06AE4C 8006A24C 8FA4005C */   lw    $a0, 0x5c($sp)
/* 06AE50 8006A250 0C01BAA4 */  jal   get_settings
/* 06AE54 8006A254 00000000 */   nop   
/* 06AE58 8006A258 32430003 */  andi  $v1, $s2, 3
/* 06AE5C 8006A25C 10600004 */  beqz  $v1, .L8006A270
/* 06AE60 8006A260 AFA2004C */   sw    $v0, 0x4c($sp)
/* 06AE64 8006A264 00402025 */  move  $a0, $v0
/* 06AE68 8006A268 0C01D174 */  jal   func_800745D0
/* 06AE6C 8006A26C 306500FF */   andi  $a1, $v1, 0xff
.L8006A270:
/* 06AE70 8006A270 32580008 */  andi  $t8, $s2, 8
/* 06AE74 8006A274 1300000D */  beqz  $t8, .L8006A2AC
/* 06AE78 8006A278 32590004 */   andi  $t9, $s2, 4
/* 06AE7C 8006A27C 0C027124 */  jal   func_8009C490
/* 06AE80 8006A280 00000000 */   nop   
/* 06AE84 8006A284 00008025 */  move  $s0, $zero
/* 06AE88 8006A288 00408825 */  move  $s1, $v0
.L8006A28C:
/* 06AE8C 8006A28C 8E250000 */  lw    $a1, ($s1)
/* 06AE90 8006A290 0C01D081 */  jal   func_80074204
/* 06AE94 8006A294 02002025 */   move  $a0, $s0
/* 06AE98 8006A298 26100001 */  addiu $s0, $s0, 1
/* 06AE9C 8006A29C 24010003 */  li    $at, 3
/* 06AEA0 8006A2A0 1601FFFA */  bne   $s0, $at, .L8006A28C
/* 06AEA4 8006A2A4 26310004 */   addiu $s1, $s1, 4
/* 06AEA8 8006A2A8 32590004 */  andi  $t9, $s2, 4
.L8006A2AC:
/* 06AEAC 8006A2AC 13200005 */  beqz  $t9, .L8006A2C4
/* 06AEB0 8006A2B0 00122203 */   sra   $a0, $s2, 8
/* 06AEB4 8006A2B4 308C0003 */  andi  $t4, $a0, 3
/* 06AEB8 8006A2B8 8FA5004C */  lw    $a1, 0x4c($sp)
/* 06AEBC 8006A2BC 0C01D081 */  jal   func_80074204
/* 06AEC0 8006A2C0 01802025 */   move  $a0, $t4
.L8006A2C4:
/* 06AEC4 8006A2C4 32420030 */  andi  $v0, $s2, 0x30
/* 06AEC8 8006A2C8 00026903 */  sra   $t5, $v0, 4
/* 06AECC 8006A2CC 11A00005 */  beqz  $t5, .L8006A2E4
/* 06AED0 8006A2D0 324E0040 */   andi  $t6, $s2, 0x40
/* 06AED4 8006A2D4 8FA4004C */  lw    $a0, 0x4c($sp)
/* 06AED8 8006A2D8 0C01D1BC */  jal   func_800746F0
/* 06AEDC 8006A2DC 31A500FF */   andi  $a1, $t5, 0xff
/* 06AEE0 8006A2E0 324E0040 */  andi  $t6, $s2, 0x40
.L8006A2E4:
/* 06AEE4 8006A2E4 11C00005 */  beqz  $t6, .L8006A2FC
/* 06AEE8 8006A2E8 00122283 */   sra   $a0, $s2, 0xa
/* 06AEEC 8006A2EC 308F0003 */  andi  $t7, $a0, 3
/* 06AEF0 8006A2F0 8FA5004C */  lw    $a1, 0x4c($sp)
/* 06AEF4 8006A2F4 0C01D137 */  jal   func_800744DC
/* 06AEF8 8006A2F8 01E02025 */   move  $a0, $t7
.L8006A2FC:
/* 06AEFC 8006A2FC 32580080 */  andi  $t8, $s2, 0x80
/* 06AF00 8006A300 13000005 */  beqz  $t8, .L8006A318
/* 06AF04 8006A304 00122283 */   sra   $a0, $s2, 0xa
/* 06AF08 8006A308 30990003 */  andi  $t9, $a0, 3
/* 06AF0C 8006A30C 8FA5004C */  lw    $a1, 0x4c($sp)
/* 06AF10 8006A310 0C01D0C7 */  jal   func_8007431C
/* 06AF14 8006A314 03202025 */   move  $a0, $t9
.L8006A318:
/* 06AF18 8006A318 324C0100 */  andi  $t4, $s2, 0x100
/* 06AF1C 8006A31C 11800006 */  beqz  $t4, .L8006A338
/* 06AF20 8006A320 324D0200 */   andi  $t5, $s2, 0x200
/* 06AF24 8006A324 0C027A9B */  jal   func_8009EA6C
/* 06AF28 8006A328 00000000 */   nop   
/* 06AF2C 8006A32C 0C01D21D */  jal   func_80074874
/* 06AF30 8006A330 00402025 */   move  $a0, $v0
/* 06AF34 8006A334 324D0200 */  andi  $t5, $s2, 0x200
.L8006A338:
/* 06AF38 8006A338 11A00006 */  beqz  $t5, .L8006A354
/* 06AF3C 8006A33C 00009025 */   move  $s2, $zero
/* 06AF40 8006A340 0C027A9B */  jal   func_8009EA6C
/* 06AF44 8006A344 00000000 */   nop   
/* 06AF48 8006A348 0C01D25F */  jal   func_8007497C
/* 06AF4C 8006A34C 00402025 */   move  $a0, $v0
/* 06AF50 8006A350 00009025 */  move  $s2, $zero
.L8006A354:
/* 06AF54 8006A354 8FA4005C */  lw    $a0, 0x5c($sp)
.L8006A358:
/* 06AF58 8006A358 0C01C9C6 */  jal   func_80072718
/* 06AF5C 8006A35C 00000000 */   nop   
/* 06AF60 8006A360 3C048012 */  lui   $a0, %hi(sSIMesgQueue) # $a0, 0x8012
/* 06AF64 8006A364 0C0333F8 */  jal   osContStartReadData
/* 06AF68 8006A368 248410E0 */   addiu $a0, %lo(sSIMesgQueue) # addiu $a0, $a0, 0x10e0
.L8006A36C:
/* 06AF6C 8006A36C 3C0A800E */  lui   $t2, %hi(D_800DD300) # $t2, 0x800e
/* 06AF70 8006A370 3C09800E */  lui   $t1, %hi(gButtonMask) # $t1, 0x800e
/* 06AF74 8006A374 3C068012 */  lui   $a2, %hi(sControllerData+24) # $a2, 0x8012
/* 06AF78 8006A378 3C028012 */  lui   $v0, %hi(sControllerData) # $v0, 0x8012
/* 06AF7C 8006A37C 3C088012 */  lui   $t0, %hi(sControllerButtonsPressed) # $t0, 0x8012
/* 06AF80 8006A380 3C078012 */  lui   $a3, %hi(D_80121148) # $a3, 0x8012
/* 06AF84 8006A384 3C0B8012 */  lui   $t3, %hi(sPlayerID) # $t3, 0x8012
/* 06AF88 8006A388 9529D304 */  lhu   $t1, %lo(gButtonMask)($t1)
/* 06AF8C 8006A38C 8D4AD300 */  lw    $t2, %lo(D_800DD300)($t2)
/* 06AF90 8006A390 256B1150 */  addiu $t3, %lo(sPlayerID) # addiu $t3, $t3, 0x1150
/* 06AF94 8006A394 24E71148 */  addiu $a3, %lo(D_80121148) # addiu $a3, $a3, 0x1148
/* 06AF98 8006A398 25081140 */  addiu $t0, %lo(sControllerButtonsPressed) # addiu $t0, $t0, 0x1140
/* 06AF9C 8006A39C 24421110 */  addiu $v0, %lo(sControllerData) # addiu $v0, $v0, 0x1110
/* 06AFA0 8006A3A0 24C61128 */  addiu $a2, %lo(sControllerData+24) # addiu $a2, $a2, 0x1128
.L8006A3A4:
/* 06AFA4 8006A3A4 11400002 */  beqz  $t2, .L8006A3B0
/* 06AFA8 8006A3A8 00000000 */   nop   
/* 06AFAC 8006A3AC A4400000 */  sh    $zero, ($v0)
.L8006A3B0:
/* 06AFB0 8006A3B0 94430000 */  lhu   $v1, ($v0)
/* 06AFB4 8006A3B4 94C40000 */  lhu   $a0, ($a2)
/* 06AFB8 8006A3B8 00000000 */  nop   
/* 06AFBC 8006A3BC 00642826 */  xor   $a1, $v1, $a0
/* 06AFC0 8006A3C0 00657024 */  and   $t6, $v1, $a1
/* 06AFC4 8006A3C4 0085C024 */  and   $t8, $a0, $a1
/* 06AFC8 8006A3C8 01C97824 */  and   $t7, $t6, $t1
/* 06AFCC 8006A3CC 0309C824 */  and   $t9, $t8, $t1
/* 06AFD0 8006A3D0 A50F0000 */  sh    $t7, ($t0)
/* 06AFD4 8006A3D4 11400002 */  beqz  $t2, .L8006A3E0
/* 06AFD8 8006A3D8 A4F90000 */   sh    $t9, ($a3)
/* 06AFDC 8006A3DC A4400006 */  sh    $zero, 6($v0)
.L8006A3E0:
/* 06AFE0 8006A3E0 94430006 */  lhu   $v1, 6($v0)
/* 06AFE4 8006A3E4 94C40006 */  lhu   $a0, 6($a2)
/* 06AFE8 8006A3E8 24E70004 */  addiu $a3, $a3, 4
/* 06AFEC 8006A3EC 00642826 */  xor   $a1, $v1, $a0
/* 06AFF0 8006A3F0 00656024 */  and   $t4, $v1, $a1
/* 06AFF4 8006A3F4 00857024 */  and   $t6, $a0, $a1
/* 06AFF8 8006A3F8 01C97824 */  and   $t7, $t6, $t1
/* 06AFFC 8006A3FC 01896824 */  and   $t5, $t4, $t1
/* 06B000 8006A400 A50D0002 */  sh    $t5, 2($t0)
/* 06B004 8006A404 A4EFFFFE */  sh    $t7, -2($a3)
/* 06B008 8006A408 24C6000C */  addiu $a2, $a2, 0xc
/* 06B00C 8006A40C 2442000C */  addiu $v0, $v0, 0xc
/* 06B010 8006A410 14EBFFE4 */  bne   $a3, $t3, .L8006A3A4
/* 06B014 8006A414 25080004 */   addiu $t0, $t0, 4
/* 06B018 8006A418 8FBF0024 */  lw    $ra, 0x24($sp)
/* 06B01C 8006A41C 02401025 */  move  $v0, $s2
/* 06B020 8006A420 8FB20020 */  lw    $s2, 0x20($sp)
/* 06B024 8006A424 8FB00018 */  lw    $s0, 0x18($sp)
/* 06B028 8006A428 8FB1001C */  lw    $s1, 0x1c($sp)
/* 06B02C 8006A42C 03E00008 */  jr    $ra
/* 06B030 8006A430 27BD0058 */   addiu $sp, $sp, 0x58

