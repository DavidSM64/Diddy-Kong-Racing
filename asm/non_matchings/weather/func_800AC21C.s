glabel func_800AC21C
/* 0ACE1C 800AC21C 27BDFF88 */  addiu $sp, $sp, -0x78
/* 0ACE20 800AC220 3C028012 */  lui   $v0, %hi(gWeatherCamera) # $v0, 0x8012
/* 0ACE24 800AC224 8C427C1C */  lw    $v0, %lo(gWeatherCamera)($v0)
/* 0ACE28 800AC228 AFBF0044 */  sw    $ra, 0x44($sp)
/* 0ACE2C 800AC22C AFBE0040 */  sw    $fp, 0x40($sp)
/* 0ACE30 800AC230 AFB7003C */  sw    $s7, 0x3c($sp)
/* 0ACE34 800AC234 AFB60038 */  sw    $s6, 0x38($sp)
/* 0ACE38 800AC238 AFB50034 */  sw    $s5, 0x34($sp)
/* 0ACE3C 800AC23C AFB40030 */  sw    $s4, 0x30($sp)
/* 0ACE40 800AC240 AFB3002C */  sw    $s3, 0x2c($sp)
/* 0ACE44 800AC244 AFB20028 */  sw    $s2, 0x28($sp)
/* 0ACE48 800AC248 AFB10024 */  sw    $s1, 0x24($sp)
/* 0ACE4C 800AC24C AFB00020 */  sw    $s0, 0x20($sp)
/* 0ACE50 800AC250 E7B50018 */  swc1  $f21, 0x18($sp)
/* 0ACE54 800AC254 E7B4001C */  swc1  $f20, 0x1c($sp)
/* 0ACE58 800AC258 3C014780 */  li    $at, 0x47800000 # 65536.000000
/* 0ACE5C 800AC25C 44810000 */  mtc1  $at, $f0
/* 0ACE60 800AC260 C444000C */  lwc1  $f4, 0xc($v0)
/* 0ACE64 800AC264 C44A0010 */  lwc1  $f10, 0x10($v0)
/* 0ACE68 800AC268 46002182 */  mul.s $f6, $f4, $f0
/* 0ACE6C 800AC26C C4440014 */  lwc1  $f4, 0x14($v0)
/* 0ACE70 800AC270 3C14800E */  lui   $s4, %hi(D_800E2908) # $s4, 0x800e
/* 0ACE74 800AC274 26942908 */  addiu $s4, %lo(D_800E2908) # addiu $s4, $s4, 0x2908
/* 0ACE78 800AC278 444EF800 */  cfc1  $t6, $31
/* 0ACE7C 800AC27C AE800000 */  sw    $zero, ($s4)
/* 0ACE80 800AC280 35C10003 */  ori   $at, $t6, 3
/* 0ACE84 800AC284 38210002 */  xori  $at, $at, 2
/* 0ACE88 800AC288 44C1F800 */  ctc1  $at, $31
/* 0ACE8C 800AC28C 3C198012 */  lui   $t9, %hi(D_80127BB4) # $t9, 0x8012
/* 0ACE90 800AC290 46003224 */  cvt.w.s $f8, $f6
/* 0ACE94 800AC294 8F397BB4 */  lw    $t9, %lo(D_80127BB4)($t9)
/* 0ACE98 800AC298 44CEF800 */  ctc1  $t6, $31
/* 0ACE9C 800AC29C 44034000 */  mfc1  $v1, $f8
/* 0ACEA0 800AC2A0 46005402 */  mul.s $f16, $f10, $f0
/* 0ACEA4 800AC2A4 3C11800E */  lui   $s1, %hi(D_800E2904) # $s1, 0x800e
/* 0ACEA8 800AC2A8 8E312904 */  lw    $s1, %lo(D_800E2904)($s1)
/* 0ACEAC 800AC2AC 3C168012 */  lui   $s6, %hi(D_80127BF8) # $s6, 0x8012
/* 0ACEB0 800AC2B0 444FF800 */  cfc1  $t7, $31
/* 0ACEB4 800AC2B4 3C17800E */  lui   $s7, %hi(D_800E28D4) # $s7, 0x800e
/* 0ACEB8 800AC2B8 35E10003 */  ori   $at, $t7, 3
/* 0ACEBC 800AC2BC 38210002 */  xori  $at, $at, 2
/* 0ACEC0 800AC2C0 44C1F800 */  ctc1  $at, $31
/* 0ACEC4 800AC2C4 3C1E8012 */  lui   $fp, %hi(gWeatherCameraMatrix) # $fp, 0x8012
/* 0ACEC8 800AC2C8 460084A4 */  cvt.w.s $f18, $f16
/* 0ACECC 800AC2CC 27DE7C20 */  addiu $fp, %lo(gWeatherCameraMatrix) # addiu $fp, $fp, 0x7c20
/* 0ACED0 800AC2D0 44CFF800 */  ctc1  $t7, $31
/* 0ACED4 800AC2D4 44079000 */  mfc1  $a3, $f18
/* 0ACED8 800AC2D8 46002182 */  mul.s $f6, $f4, $f0
/* 0ACEDC 800AC2DC 26F728D4 */  addiu $s7, %lo(D_800E28D4) # addiu $s7, $s7, 0x28d4
/* 0ACEE0 800AC2E0 26D67BF8 */  addiu $s6, %lo(D_80127BF8) # addiu $s6, $s6, 0x7bf8
/* 0ACEE4 800AC2E4 3C10800E */  lui   $s0, %hi(D_800E28D8) # $s0, 0x800e
/* 0ACEE8 800AC2E8 4458F800 */  cfc1  $t8, $31
/* 0ACEEC 800AC2EC 00009025 */  move  $s2, $zero
/* 0ACEF0 800AC2F0 37010003 */  ori   $at, $t8, 3
/* 0ACEF4 800AC2F4 38210002 */  xori  $at, $at, 2
/* 0ACEF8 800AC2F8 44C1F800 */  ctc1  $at, $31
/* 0ACEFC 800AC2FC 3C013780 */  li    $at, 0x37800000 # 0.000015
/* 0ACF00 800AC300 46003224 */  cvt.w.s $f8, $f6
/* 0ACF04 800AC304 00009825 */  move  $s3, $zero
/* 0ACF08 800AC308 44084000 */  mfc1  $t0, $f8
/* 0ACF0C 800AC30C 44D8F800 */  ctc1  $t8, $31
/* 0ACF10 800AC310 1B200096 */  blez  $t9, .L800AC56C
/* 0ACF14 800AC314 27B50064 */   addiu $s5, $sp, 0x64
/* 0ACF18 800AC318 4481A000 */  mtc1  $at, $f20
/* 0ACF1C 800AC31C AFA30058 */  sw    $v1, 0x58($sp)
/* 0ACF20 800AC320 AFA70054 */  sw    $a3, 0x54($sp)
/* 0ACF24 800AC324 AFA80050 */  sw    $t0, 0x50($sp)
/* 0ACF28 800AC328 261028D8 */  addiu $s0, %lo(D_800E28D8) # addiu $s0, $s0, 0x28d8
.L800AC32C:
/* 0ACF2C 800AC32C 8EE90000 */  lw    $t1, ($s7)
/* 0ACF30 800AC330 8FA30058 */  lw    $v1, 0x58($sp)
/* 0ACF34 800AC334 01331021 */  addu  $v0, $t1, $s3
/* 0ACF38 800AC338 8C4A0000 */  lw    $t2, ($v0)
/* 0ACF3C 800AC33C 8E0C0018 */  lw    $t4, 0x18($s0)
/* 0ACF40 800AC340 8E0E000C */  lw    $t6, 0xc($s0)
/* 0ACF44 800AC344 01435823 */  subu  $t3, $t2, $v1
/* 0ACF48 800AC348 016C6824 */  and   $t5, $t3, $t4
/* 0ACF4C 800AC34C 01AE7821 */  addu  $t7, $t5, $t6
/* 0ACF50 800AC350 448F5000 */  mtc1  $t7, $f10
/* 0ACF54 800AC354 8FA70054 */  lw    $a3, 0x54($sp)
/* 0ACF58 800AC358 46805420 */  cvt.s.w $f16, $f10
/* 0ACF5C 800AC35C 8E09001C */  lw    $t1, 0x1c($s0)
/* 0ACF60 800AC360 8E0B0010 */  lw    $t3, 0x10($s0)
/* 0ACF64 800AC364 46148482 */  mul.s $f18, $f16, $f20
/* 0ACF68 800AC368 8FA80050 */  lw    $t0, 0x50($sp)
/* 0ACF6C 800AC36C 8E0F0020 */  lw    $t7, 0x20($s0)
/* 0ACF70 800AC370 8FC40000 */  lw    $a0, ($fp)
/* 0ACF74 800AC374 E7B20064 */  swc1  $f18, 0x64($sp)
/* 0ACF78 800AC378 8C580004 */  lw    $t8, 4($v0)
/* 0ACF7C 800AC37C 02A02825 */  move  $a1, $s5
/* 0ACF80 800AC380 0307C823 */  subu  $t9, $t8, $a3
/* 0ACF84 800AC384 03295024 */  and   $t2, $t9, $t1
/* 0ACF88 800AC388 014B6021 */  addu  $t4, $t2, $t3
/* 0ACF8C 800AC38C 448C2000 */  mtc1  $t4, $f4
/* 0ACF90 800AC390 8E190014 */  lw    $t9, 0x14($s0)
/* 0ACF94 800AC394 468021A0 */  cvt.s.w $f6, $f4
/* 0ACF98 800AC398 02A03025 */  move  $a2, $s5
/* 0ACF9C 800AC39C 46143202 */  mul.s $f8, $f6, $f20
/* 0ACFA0 800AC3A0 E7A80068 */  swc1  $f8, 0x68($sp)
/* 0ACFA4 800AC3A4 8C4D0008 */  lw    $t5, 8($v0)
/* 0ACFA8 800AC3A8 00000000 */  nop   
/* 0ACFAC 800AC3AC 01A87023 */  subu  $t6, $t5, $t0
/* 0ACFB0 800AC3B0 01CFC024 */  and   $t8, $t6, $t7
/* 0ACFB4 800AC3B4 03194821 */  addu  $t1, $t8, $t9
/* 0ACFB8 800AC3B8 44895000 */  mtc1  $t1, $f10
/* 0ACFBC 800AC3BC 00000000 */  nop   
/* 0ACFC0 800AC3C0 46805420 */  cvt.s.w $f16, $f10
/* 0ACFC4 800AC3C4 46148482 */  mul.s $f18, $f16, $f20
/* 0ACFC8 800AC3C8 0C01BDBB */  jal   f32_matrix_dot
/* 0ACFCC 800AC3CC E7B2006C */   swc1  $f18, 0x6c($sp)
/* 0ACFD0 800AC3D0 444AF800 */  cfc1  $t2, $31
/* 0ACFD4 800AC3D4 C7A4006C */  lwc1  $f4, 0x6c($sp)
/* 0ACFD8 800AC3D8 35410003 */  ori   $at, $t2, 3
/* 0ACFDC 800AC3DC 38210002 */  xori  $at, $at, 2
/* 0ACFE0 800AC3E0 44C1F800 */  ctc1  $at, $31
/* 0ACFE4 800AC3E4 86CD0000 */  lh    $t5, ($s6)
/* 0ACFE8 800AC3E8 460021A4 */  cvt.w.s $f6, $f4
/* 0ACFEC 800AC3EC 44023000 */  mfc1  $v0, $f6
/* 0ACFF0 800AC3F0 44CAF800 */  ctc1  $t2, $31
/* 0ACFF4 800AC3F4 00025C00 */  sll   $t3, $v0, 0x10
/* 0ACFF8 800AC3F8 000B6403 */  sra   $t4, $t3, 0x10
/* 0ACFFC 800AC3FC 018D082A */  slt   $at, $t4, $t5
/* 0AD000 800AC400 10200054 */  beqz  $at, .L800AC554
/* 0AD004 800AC404 A7AC0074 */   sh    $t4, 0x74($sp)
/* 0AD008 800AC408 8ECE0004 */  lw    $t6, 4($s6)
/* 0AD00C 800AC40C A7AC0074 */  sh    $t4, 0x74($sp)
/* 0AD010 800AC410 01CC082A */  slt   $at, $t6, $t4
/* 0AD014 800AC414 1020004F */  beqz  $at, .L800AC554
/* 0AD018 800AC418 00000000 */   nop   
/* 0AD01C 800AC41C 444FF800 */  cfc1  $t7, $31
/* 0AD020 800AC420 C7A80064 */  lwc1  $f8, 0x64($sp)
/* 0AD024 800AC424 35E10003 */  ori   $at, $t7, 3
/* 0AD028 800AC428 38210002 */  xori  $at, $at, 2
/* 0AD02C 800AC42C 44C1F800 */  ctc1  $at, $31
/* 0AD030 800AC430 C7B00068 */  lwc1  $f16, 0x68($sp)
/* 0AD034 800AC434 460042A4 */  cvt.w.s $f10, $f8
/* 0AD038 800AC438 860A0024 */  lh    $t2, 0x24($s0)
/* 0AD03C 800AC43C 44CFF800 */  ctc1  $t7, $31
/* 0AD040 800AC440 440C5000 */  mfc1  $t4, $f10
/* 0AD044 800AC444 26310028 */  addiu $s1, $s1, 0x28
/* 0AD048 800AC448 4459F800 */  cfc1  $t9, $31
/* 0AD04C 800AC44C A7AC0070 */  sh    $t4, 0x70($sp)
/* 0AD050 800AC450 37210003 */  ori   $at, $t9, 3
/* 0AD054 800AC454 38210002 */  xori  $at, $at, 2
/* 0AD058 800AC458 44C1F800 */  ctc1  $at, $31
/* 0AD05C 800AC45C 018A6823 */  subu  $t5, $t4, $t2
/* 0AD060 800AC460 460084A4 */  cvt.w.s $f18, $f16
/* 0AD064 800AC464 44099000 */  mfc1  $t1, $f18
/* 0AD068 800AC468 44D9F800 */  ctc1  $t9, $31
/* 0AD06C 800AC46C A7A90072 */  sh    $t1, 0x72($sp)
/* 0AD070 800AC470 A62DFFD8 */  sh    $t5, -0x28($s1)
/* 0AD074 800AC474 860F0026 */  lh    $t7, 0x26($s0)
/* 0AD078 800AC478 87AE0072 */  lh    $t6, 0x72($sp)
/* 0AD07C 800AC47C 00000000 */  nop   
/* 0AD080 800AC480 01CFC821 */  addu  $t9, $t6, $t7
/* 0AD084 800AC484 A639FFDA */  sh    $t9, -0x26($s1)
/* 0AD088 800AC488 87A90074 */  lh    $t1, 0x74($sp)
/* 0AD08C 800AC48C 00000000 */  nop   
/* 0AD090 800AC490 A629FFDC */  sh    $t1, -0x24($s1)
/* 0AD094 800AC494 860B0024 */  lh    $t3, 0x24($s0)
/* 0AD098 800AC498 87B80070 */  lh    $t8, 0x70($sp)
/* 0AD09C 800AC49C 00000000 */  nop   
/* 0AD0A0 800AC4A0 030B6021 */  addu  $t4, $t8, $t3
/* 0AD0A4 800AC4A4 A62CFFE2 */  sh    $t4, -0x1e($s1)
/* 0AD0A8 800AC4A8 860D0026 */  lh    $t5, 0x26($s0)
/* 0AD0AC 800AC4AC 87AA0072 */  lh    $t2, 0x72($sp)
/* 0AD0B0 800AC4B0 00000000 */  nop   
/* 0AD0B4 800AC4B4 014D7021 */  addu  $t6, $t2, $t5
/* 0AD0B8 800AC4B8 A62EFFE4 */  sh    $t6, -0x1c($s1)
/* 0AD0BC 800AC4BC 87AF0074 */  lh    $t7, 0x74($sp)
/* 0AD0C0 800AC4C0 00000000 */  nop   
/* 0AD0C4 800AC4C4 A62FFFE6 */  sh    $t7, -0x1a($s1)
/* 0AD0C8 800AC4C8 86090024 */  lh    $t1, 0x24($s0)
/* 0AD0CC 800AC4CC 87B90070 */  lh    $t9, 0x70($sp)
/* 0AD0D0 800AC4D0 00000000 */  nop   
/* 0AD0D4 800AC4D4 0329C021 */  addu  $t8, $t9, $t1
/* 0AD0D8 800AC4D8 A638FFEC */  sh    $t8, -0x14($s1)
/* 0AD0DC 800AC4DC 860C0026 */  lh    $t4, 0x26($s0)
/* 0AD0E0 800AC4E0 87AB0072 */  lh    $t3, 0x72($sp)
/* 0AD0E4 800AC4E4 00000000 */  nop   
/* 0AD0E8 800AC4E8 016C5023 */  subu  $t2, $t3, $t4
/* 0AD0EC 800AC4EC A62AFFEE */  sh    $t2, -0x12($s1)
/* 0AD0F0 800AC4F0 87AD0074 */  lh    $t5, 0x74($sp)
/* 0AD0F4 800AC4F4 00000000 */  nop   
/* 0AD0F8 800AC4F8 A62DFFF0 */  sh    $t5, -0x10($s1)
/* 0AD0FC 800AC4FC 860F0024 */  lh    $t7, 0x24($s0)
/* 0AD100 800AC500 87AE0070 */  lh    $t6, 0x70($sp)
/* 0AD104 800AC504 00000000 */  nop   
/* 0AD108 800AC508 01CFC823 */  subu  $t9, $t6, $t7
/* 0AD10C 800AC50C A639FFF6 */  sh    $t9, -0xa($s1)
/* 0AD110 800AC510 86180026 */  lh    $t8, 0x26($s0)
/* 0AD114 800AC514 87A90072 */  lh    $t1, 0x72($sp)
/* 0AD118 800AC518 3C0E800E */  lui   $t6, %hi(D_800E2910) # $t6, 0x800e
/* 0AD11C 800AC51C 01385823 */  subu  $t3, $t1, $t8
/* 0AD120 800AC520 A62BFFF8 */  sh    $t3, -8($s1)
/* 0AD124 800AC524 87AC0074 */  lh    $t4, 0x74($sp)
/* 0AD128 800AC528 00000000 */  nop   
/* 0AD12C 800AC52C A62CFFFA */  sh    $t4, -6($s1)
/* 0AD130 800AC530 8E8A0000 */  lw    $t2, ($s4)
/* 0AD134 800AC534 00000000 */  nop   
/* 0AD138 800AC538 254D0004 */  addiu $t5, $t2, 4
/* 0AD13C 800AC53C AE8D0000 */  sw    $t5, ($s4)
/* 0AD140 800AC540 8DCE2910 */  lw    $t6, %lo(D_800E2910)($t6)
/* 0AD144 800AC544 000DC883 */  sra   $t9, $t5, 2
/* 0AD148 800AC548 00194840 */  sll   $t1, $t9, 1
/* 0AD14C 800AC54C 01C9C021 */  addu  $t8, $t6, $t1
/* 0AD150 800AC550 A7120000 */  sh    $s2, ($t8)
.L800AC554:
/* 0AD154 800AC554 3C0B8012 */  lui   $t3, %hi(D_80127BB4) # $t3, 0x8012
/* 0AD158 800AC558 8D6B7BB4 */  lw    $t3, %lo(D_80127BB4)($t3)
/* 0AD15C 800AC55C 26520001 */  addiu $s2, $s2, 1
/* 0AD160 800AC560 024B082A */  slt   $at, $s2, $t3
/* 0AD164 800AC564 1420FF71 */  bnez  $at, .L800AC32C
/* 0AD168 800AC568 26730010 */   addiu $s3, $s3, 0x10
.L800AC56C:
/* 0AD16C 800AC56C 8FBF0044 */  lw    $ra, 0x44($sp)
/* 0AD170 800AC570 C7B50018 */  lwc1  $f21, 0x18($sp)
/* 0AD174 800AC574 C7B4001C */  lwc1  $f20, 0x1c($sp)
/* 0AD178 800AC578 8FB00020 */  lw    $s0, 0x20($sp)
/* 0AD17C 800AC57C 8FB10024 */  lw    $s1, 0x24($sp)
/* 0AD180 800AC580 8FB20028 */  lw    $s2, 0x28($sp)
/* 0AD184 800AC584 8FB3002C */  lw    $s3, 0x2c($sp)
/* 0AD188 800AC588 8FB40030 */  lw    $s4, 0x30($sp)
/* 0AD18C 800AC58C 8FB50034 */  lw    $s5, 0x34($sp)
/* 0AD190 800AC590 8FB60038 */  lw    $s6, 0x38($sp)
/* 0AD194 800AC594 8FB7003C */  lw    $s7, 0x3c($sp)
/* 0AD198 800AC598 8FBE0040 */  lw    $fp, 0x40($sp)
/* 0AD19C 800AC59C 03E00008 */  jr    $ra
/* 0AD1A0 800AC5A0 27BD0078 */   addiu $sp, $sp, 0x78

