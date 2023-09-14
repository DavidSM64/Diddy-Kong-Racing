.late_rodata
glabel D_800E87D8
.float 1.1
.word 0 # Padding
glabel D_800E87E0
.double 1.1

.text
glabel func_800AA600
/* 0AB200 800AA600 27BDFF48 */  addiu $sp, $sp, -0xb8
/* 0AB204 800AA604 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0AB208 800AA608 AFB00028 */  sw    $s0, 0x28($sp)
/* 0AB20C 800AA60C AFA400B8 */  sw    $a0, 0xb8($sp)
/* 0AB210 800AA610 AFA500BC */  sw    $a1, 0xbc($sp)
/* 0AB214 800AA614 AFA600C0 */  sw    $a2, 0xc0($sp)
/* 0AB218 800AA618 84E80006 */  lh    $t0, 6($a3)
/* 0AB21C 800AA61C 3C038012 */  lui   $v1, %hi(gAssetHudElementIds) # $v1, 0x8012
/* 0AB220 800AA620 8C636CF0 */  lw    $v1, %lo(gAssetHudElementIds)($v1)
/* 0AB224 800AA624 00087040 */  sll   $t6, $t0, 1
/* 0AB228 800AA628 006E7821 */  addu  $t7, $v1, $t6
/* 0AB22C 800AA62C 85F80000 */  lh    $t8, ($t7)
/* 0AB230 800AA630 340AC000 */  li    $t2, 49152
/* 0AB234 800AA634 3302C000 */  andi  $v0, $t8, 0xc000
/* 0AB238 800AA638 00E08025 */  move  $s0, $a3
/* 0AB23C 800AA63C 15420007 */  bne   $t2, $v0, .L800AA65C
/* 0AB240 800AA640 AFB80038 */   sw    $t8, 0x38($sp)
/* 0AB244 800AA644 3C0B8012 */  lui   $t3, %hi(D_80126CD0) # $t3, 0x8012
/* 0AB248 800AA648 816B6CD0 */  lb    $t3, %lo(D_80126CD0)($t3)
/* 0AB24C 800AA64C 00000000 */  nop   
/* 0AB250 800AA650 000B6023 */  negu  $t4, $t3
/* 0AB254 800AA654 10000005 */  b     .L800AA66C
/* 0AB258 800AA658 AFAC00A4 */   sw    $t4, 0xa4($sp)
.L800AA65C:
/* 0AB25C 800AA65C 3C0D8012 */  lui   $t5, %hi(D_80126CD0) # $t5, 0x8012
/* 0AB260 800AA660 81AD6CD0 */  lb    $t5, %lo(D_80126CD0)($t5)
/* 0AB264 800AA664 00000000 */  nop   
/* 0AB268 800AA668 AFAD00A4 */  sw    $t5, 0xa4($sp)
.L800AA66C:
/* 0AB26C 800AA66C 3C098012 */  lui   $t1, %hi(gAssetHudElements) # $t1, 0x8012
/* 0AB270 800AA670 25296CF4 */  addiu $t1, %lo(gAssetHudElements) # addiu $t1, $t1, 0x6cf4
/* 0AB274 800AA674 8D2E0000 */  lw    $t6, ($t1)
/* 0AB278 800AA678 00087880 */  sll   $t7, $t0, 2
/* 0AB27C 800AA67C 01CFC021 */  addu  $t8, $t6, $t7
/* 0AB280 800AA680 8F190000 */  lw    $t9, ($t8)
/* 0AB284 800AA684 00000000 */  nop   
/* 0AB288 800AA688 1720004A */  bnez  $t9, .L800AA7B4
/* 0AB28C 800AA68C 00000000 */   nop   
/* 0AB290 800AA690 1542000F */  bne   $t2, $v0, .L800AA6D0
/* 0AB294 800AA694 8FB80038 */   lw    $t8, 0x38($sp)
/* 0AB298 800AA698 8FA40038 */  lw    $a0, 0x38($sp)
/* 0AB29C 800AA69C 00000000 */  nop   
/* 0AB2A0 800AA6A0 308B3FFF */  andi  $t3, $a0, 0x3fff
/* 0AB2A4 800AA6A4 0C01EB9D */  jal   load_texture
/* 0AB2A8 800AA6A8 01602025 */   move  $a0, $t3
/* 0AB2AC 800AA6AC 3C098012 */  lui   $t1, %hi(gAssetHudElements) # $t1, 0x8012
/* 0AB2B0 800AA6B0 860D0006 */  lh    $t5, 6($s0)
/* 0AB2B4 800AA6B4 25296CF4 */  addiu $t1, %lo(gAssetHudElements) # addiu $t1, $t1, 0x6cf4
/* 0AB2B8 800AA6B8 8D2C0000 */  lw    $t4, ($t1)
/* 0AB2BC 800AA6BC 000D7080 */  sll   $t6, $t5, 2
/* 0AB2C0 800AA6C0 018E7821 */  addu  $t7, $t4, $t6
/* 0AB2C4 800AA6C4 10000034 */  b     .L800AA798
/* 0AB2C8 800AA6C8 ADE20000 */   sw    $v0, ($t7)
/* 0AB2CC 800AA6CC 8FB80038 */  lw    $t8, 0x38($sp)
.L800AA6D0:
/* 0AB2D0 800AA6D0 8FAF0038 */  lw    $t7, 0x38($sp)
/* 0AB2D4 800AA6D4 33198000 */  andi  $t9, $t8, 0x8000
/* 0AB2D8 800AA6D8 1320000B */  beqz  $t9, .L800AA708
/* 0AB2DC 800AA6DC 33043FFF */   andi  $a0, $t8, 0x3fff
/* 0AB2E0 800AA6E0 0C01F04B */  jal   func_8007C12C
/* 0AB2E4 800AA6E4 24050001 */   li    $a1, 1
/* 0AB2E8 800AA6E8 3C098012 */  lui   $t1, %hi(gAssetHudElements) # $t1, 0x8012
/* 0AB2EC 800AA6EC 860D0006 */  lh    $t5, 6($s0)
/* 0AB2F0 800AA6F0 25296CF4 */  addiu $t1, %lo(gAssetHudElements) # addiu $t1, $t1, 0x6cf4
/* 0AB2F4 800AA6F4 8D2B0000 */  lw    $t3, ($t1)
/* 0AB2F8 800AA6F8 000D6080 */  sll   $t4, $t5, 2
/* 0AB2FC 800AA6FC 016C7021 */  addu  $t6, $t3, $t4
/* 0AB300 800AA700 10000025 */  b     .L800AA798
/* 0AB304 800AA704 ADC20000 */   sw    $v0, ($t6)
.L800AA708:
/* 0AB308 800AA708 31F94000 */  andi  $t9, $t7, 0x4000
/* 0AB30C 800AA70C 13200018 */  beqz  $t9, .L800AA770
/* 0AB310 800AA710 01E0C025 */   move  $t8, $t7
/* 0AB314 800AA714 A3B8009C */  sb    $t8, 0x9c($sp)
/* 0AB318 800AA718 860D0006 */  lh    $t5, 6($s0)
/* 0AB31C 800AA71C 27A4009C */  addiu $a0, $sp, 0x9c
/* 0AB320 800AA720 000D5840 */  sll   $t3, $t5, 1
/* 0AB324 800AA724 006B6021 */  addu  $t4, $v1, $t3
/* 0AB328 800AA728 858E0000 */  lh    $t6, ($t4)
/* 0AB32C 800AA72C A7A0009E */  sh    $zero, 0x9e($sp)
/* 0AB330 800AA730 31D90100 */  andi  $t9, $t6, 0x100
/* 0AB334 800AA734 00197843 */  sra   $t7, $t9, 1
/* 0AB338 800AA738 35F80008 */  ori   $t8, $t7, 8
/* 0AB33C 800AA73C A3B8009D */  sb    $t8, 0x9d($sp)
/* 0AB340 800AA740 A7A000A0 */  sh    $zero, 0xa0($sp)
/* 0AB344 800AA744 A7A000A2 */  sh    $zero, 0xa2($sp)
/* 0AB348 800AA748 0C003A95 */  jal   spawn_object
/* 0AB34C 800AA74C 00002825 */   move  $a1, $zero
/* 0AB350 800AA750 3C098012 */  lui   $t1, %hi(gAssetHudElements) # $t1, 0x8012
/* 0AB354 800AA754 860B0006 */  lh    $t3, 6($s0)
/* 0AB358 800AA758 25296CF4 */  addiu $t1, %lo(gAssetHudElements) # addiu $t1, $t1, 0x6cf4
/* 0AB35C 800AA75C 8D2D0000 */  lw    $t5, ($t1)
/* 0AB360 800AA760 000B6080 */  sll   $t4, $t3, 2
/* 0AB364 800AA764 01AC7021 */  addu  $t6, $t5, $t4
/* 0AB368 800AA768 1000000B */  b     .L800AA798
/* 0AB36C 800AA76C ADC20000 */   sw    $v0, ($t6)
.L800AA770:
/* 0AB370 800AA770 8FA40038 */  lw    $a0, 0x38($sp)
/* 0AB374 800AA774 0C017E67 */  jal   func_8005F99C
/* 0AB378 800AA778 00002825 */   move  $a1, $zero
/* 0AB37C 800AA77C 3C098012 */  lui   $t1, %hi(gAssetHudElements) # $t1, 0x8012
/* 0AB380 800AA780 860F0006 */  lh    $t7, 6($s0)
/* 0AB384 800AA784 25296CF4 */  addiu $t1, %lo(gAssetHudElements) # addiu $t1, $t1, 0x6cf4
/* 0AB388 800AA788 8D390000 */  lw    $t9, ($t1)
/* 0AB38C 800AA78C 000FC080 */  sll   $t8, $t7, 2
/* 0AB390 800AA790 03385821 */  addu  $t3, $t9, $t8
/* 0AB394 800AA794 AD620000 */  sw    $v0, ($t3)
.L800AA798:
/* 0AB398 800AA798 86080006 */  lh    $t0, 6($s0)
/* 0AB39C 800AA79C 8D2D0000 */  lw    $t5, ($t1)
/* 0AB3A0 800AA7A0 00086080 */  sll   $t4, $t0, 2
/* 0AB3A4 800AA7A4 01AC7021 */  addu  $t6, $t5, $t4
/* 0AB3A8 800AA7A8 8DCF0000 */  lw    $t7, ($t6)
/* 0AB3AC 800AA7AC 00000000 */  nop   
/* 0AB3B0 800AA7B0 11E00203 */  beqz  $t7, .L800AAFC0
.L800AA7B4:
/* 0AB3B4 800AA7B4 3C198012 */   lui   $t9, %hi(D_80126CD8) # $t9, 0x8012
/* 0AB3B8 800AA7B8 8F396CD8 */  lw    $t9, %lo(D_80126CD8)($t9)
/* 0AB3BC 800AA7BC 3C018012 */  lui   $at, %hi(gHUDCurrDisplayList) # $at, 0x8012
/* 0AB3C0 800AA7C0 0328C021 */  addu  $t8, $t9, $t0
/* 0AB3C4 800AA7C4 A3000000 */  sb    $zero, ($t8)
/* 0AB3C8 800AA7C8 8FAB00B8 */  lw    $t3, 0xb8($sp)
/* 0AB3CC 800AA7CC 8FAC00BC */  lw    $t4, 0xbc($sp)
/* 0AB3D0 800AA7D0 8D6D0000 */  lw    $t5, ($t3)
/* 0AB3D4 800AA7D4 8FAF00C0 */  lw    $t7, 0xc0($sp)
/* 0AB3D8 800AA7D8 AC2D6CFC */  sw    $t5, %lo(gHUDCurrDisplayList)($at)
/* 0AB3DC 800AA7DC 8D8E0000 */  lw    $t6, ($t4)
/* 0AB3E0 800AA7E0 3C018012 */  lui   $at, %hi(gHUDCurrMatrix) # $at, 0x8012
/* 0AB3E4 800AA7E4 AC2E6D00 */  sw    $t6, %lo(gHUDCurrMatrix)($at)
/* 0AB3E8 800AA7E8 8DF90000 */  lw    $t9, ($t7)
/* 0AB3EC 800AA7EC 3C018012 */  lui   $at, %hi(gHUDCurrVertex) # $at, 0x8012
/* 0AB3F0 800AA7F0 AC396D04 */  sw    $t9, %lo(gHUDCurrVertex)($at)
/* 0AB3F4 800AA7F4 86080006 */  lh    $t0, 6($s0)
/* 0AB3F8 800AA7F8 24010028 */  li    $at, 40
/* 0AB3FC 800AA7FC 11010021 */  beq   $t0, $at, .L800AA884
/* 0AB400 800AA800 340AC000 */   li    $t2, 49152
/* 0AB404 800AA804 2401000E */  li    $at, 14
/* 0AB408 800AA808 11010014 */  beq   $t0, $at, .L800AA85C
/* 0AB40C 800AA80C 3C0C8012 */   lui   $t4, %hi(D_80126D24) # $t4, 0x8012
/* 0AB410 800AA810 2401001B */  li    $at, 27
/* 0AB414 800AA814 11010011 */  beq   $t0, $at, .L800AA85C
/* 0AB418 800AA818 2901002F */   slti  $at, $t0, 0x2f
/* 0AB41C 800AA81C 14200002 */  bnez  $at, .L800AA828
/* 0AB420 800AA820 29010036 */   slti  $at, $t0, 0x36
/* 0AB424 800AA824 1420000D */  bnez  $at, .L800AA85C
.L800AA828:
/* 0AB428 800AA828 2401002E */   li    $at, 46
/* 0AB42C 800AA82C 1101000B */  beq   $t0, $at, .L800AA85C
/* 0AB430 800AA830 3C188012 */   lui   $t8, %hi(D_80126CD3) # $t8, 0x8012
/* 0AB434 800AA834 83186CD3 */  lb    $t8, %lo(D_80126CD3)($t8)
/* 0AB438 800AA838 8FAD00A4 */  lw    $t5, 0xa4($sp)
/* 0AB43C 800AA83C 330B0001 */  andi  $t3, $t8, 1
/* 0AB440 800AA840 11600006 */  beqz  $t3, .L800AA85C
/* 0AB444 800AA844 00000000 */   nop   
/* 0AB448 800AA848 448D3000 */  mtc1  $t5, $f6
/* 0AB44C 800AA84C C6040010 */  lwc1  $f4, 0x10($s0)
/* 0AB450 800AA850 46803220 */  cvt.s.w $f8, $f6
/* 0AB454 800AA854 46082280 */  add.s $f10, $f4, $f8
/* 0AB458 800AA858 E60A0010 */  swc1  $f10, 0x10($s0)
.L800AA85C:
/* 0AB45C 800AA85C 3C0E8012 */  lui   $t6, %hi(D_80126D28) # $t6, 0x8012
/* 0AB460 800AA860 8DCE6D28 */  lw    $t6, %lo(D_80126D28)($t6)
/* 0AB464 800AA864 8D8C6D24 */  lw    $t4, %lo(D_80126D24)($t4)
/* 0AB468 800AA868 C606000C */  lwc1  $f6, 0xc($s0)
/* 0AB46C 800AA86C 018E7821 */  addu  $t7, $t4, $t6
/* 0AB470 800AA870 448F8000 */  mtc1  $t7, $f16
/* 0AB474 800AA874 86080006 */  lh    $t0, 6($s0)
/* 0AB478 800AA878 468084A0 */  cvt.s.w $f18, $f16
/* 0AB47C 800AA87C 46123100 */  add.s $f4, $f6, $f18
/* 0AB480 800AA880 E604000C */  swc1  $f4, 0xc($s0)
.L800AA884:
/* 0AB484 800AA884 3C198012 */  lui   $t9, %hi(gAssetHudElementIds) # $t9, 0x8012
/* 0AB488 800AA888 8F396CF0 */  lw    $t9, %lo(gAssetHudElementIds)($t9)
/* 0AB48C 800AA88C 0008C040 */  sll   $t8, $t0, 1
/* 0AB490 800AA890 03385821 */  addu  $t3, $t9, $t8
/* 0AB494 800AA894 85620000 */  lh    $v0, ($t3)
/* 0AB498 800AA898 2901002F */  slti  $at, $t0, 0x2f
/* 0AB49C 800AA89C 304DC000 */  andi  $t5, $v0, 0xc000
/* 0AB4A0 800AA8A0 154D0140 */  bne   $t2, $t5, .L800AADA4
/* 0AB4A4 800AA8A4 30598000 */   andi  $t9, $v0, 0x8000
/* 0AB4A8 800AA8A8 14200095 */  bnez  $at, .L800AAB00
/* 0AB4AC 800AA8AC 3C198012 */   lui   $t9, %hi(D_80126CD5) # $t9, 0x8012
/* 0AB4B0 800AA8B0 29010036 */  slti  $at, $t0, 0x36
/* 0AB4B4 800AA8B4 10200092 */  beqz  $at, .L800AAB00
/* 0AB4B8 800AA8B8 3C048000 */   lui   $a0, %hi(osTvType) # $a0, 0x8000
/* 0AB4BC 800AA8BC 8C840300 */  lw    $a0, %lo(osTvType)($a0)
/* 0AB4C0 800AA8C0 3C014100 */  li    $at, 0x41000000 # 8.000000
/* 0AB4C4 800AA8C4 14800009 */  bnez  $a0, .L800AA8EC
/* 0AB4C8 800AA8C8 3C0C8012 */   lui   $t4, %hi(D_80126CD3) # $t4, 0x8012
/* 0AB4CC 800AA8CC C6080010 */  lwc1  $f8, 0x10($s0)
/* 0AB4D0 800AA8D0 44815000 */  mtc1  $at, $f10
/* 0AB4D4 800AA8D4 3C048000 */  lui   $a0, %hi(osTvType) # $a0, 0x8000
/* 0AB4D8 800AA8D8 460A4401 */  sub.s $f16, $f8, $f10
/* 0AB4DC 800AA8DC 86080006 */  lh    $t0, 6($s0)
/* 0AB4E0 800AA8E0 E6100010 */  swc1  $f16, 0x10($s0)
/* 0AB4E4 800AA8E4 8C840300 */  lw    $a0, %lo(osTvType)($a0)
/* 0AB4E8 800AA8E8 00000000 */  nop   
.L800AA8EC:
/* 0AB4EC 800AA8EC 818C6CD3 */  lb    $t4, %lo(D_80126CD3)($t4)
/* 0AB4F0 800AA8F0 3C01437F */  li    $at, 0x437F0000 # 255.000000
/* 0AB4F4 800AA8F4 318E0002 */  andi  $t6, $t4, 2
/* 0AB4F8 800AA8F8 11C0001E */  beqz  $t6, .L800AA974
/* 0AB4FC 800AA8FC 240300FF */   li    $v1, 255
/* 0AB500 800AA900 3C0F8012 */  lui   $t7, %hi(D_80126CD0) # $t7, 0x8012
/* 0AB504 800AA904 81EF6CD0 */  lb    $t7, %lo(D_80126CD0)($t7)
/* 0AB508 800AA908 3C198012 */  lui   $t9, %hi(D_80126CD5) # $t9, 0x8012
/* 0AB50C 800AA90C 448F3000 */  mtc1  $t7, $f6
/* 0AB510 800AA910 9339718B */  lbu   $t9, %lo(D_8012718B)($t9)
/* 0AB514 800AA914 468034A0 */  cvt.s.w $f18, $f6
/* 0AB518 800AA918 44810000 */  mtc1  $at, $f0
/* 0AB51C 800AA91C 44994000 */  mtc1  $t9, $f8
/* 0AB520 800AA920 46009102 */  mul.s $f4, $f18, $f0
/* 0AB524 800AA924 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0AB528 800AA928 07210004 */  bgez  $t9, .L800AA93C
/* 0AB52C 800AA92C 468042A0 */   cvt.s.w $f10, $f8
/* 0AB530 800AA930 44818000 */  mtc1  $at, $f16
/* 0AB534 800AA934 00000000 */  nop   
/* 0AB538 800AA938 46105280 */  add.s $f10, $f10, $f16
.L800AA93C:
/* 0AB53C 800AA93C 00000000 */  nop   
/* 0AB540 800AA940 460A2183 */  div.s $f6, $f4, $f10
/* 0AB544 800AA944 46060481 */  sub.s $f18, $f0, $f6
/* 0AB548 800AA948 4458F800 */  cfc1  $t8, $31
/* 0AB54C 800AA94C 00000000 */  nop   
/* 0AB550 800AA950 37010003 */  ori   $at, $t8, 3
/* 0AB554 800AA954 38210002 */  xori  $at, $at, 2
/* 0AB558 800AA958 44C1F800 */  ctc1  $at, $31
/* 0AB55C 800AA95C 00000000 */  nop   
/* 0AB560 800AA960 46009224 */  cvt.w.s $f8, $f18
/* 0AB564 800AA964 44034000 */  mfc1  $v1, $f8
/* 0AB568 800AA968 44D8F800 */  ctc1  $t8, $31
/* 0AB56C 800AA96C 10000002 */  b     .L800AA978
/* 0AB570 800AA970 8D2B0000 */   lw    $t3, ($t1)
.L800AA974:
/* 0AB574 800AA974 8D2B0000 */  lw    $t3, ($t1)
.L800AA978:
/* 0AB578 800AA978 00086880 */  sll   $t5, $t0, 2
/* 0AB57C 800AA97C 016D6021 */  addu  $t4, $t3, $t5
/* 0AB580 800AA980 8D820000 */  lw    $v0, ($t4)
/* 0AB584 800AA984 860E0018 */  lh    $t6, 0x18($s0)
/* 0AB588 800AA988 844F0016 */  lh    $t7, 0x16($v0)
/* 0AB58C 800AA98C 4458F800 */  cfc1  $t8, $31
/* 0AB590 800AA990 01CF0019 */  multu $t6, $t7
/* 0AB594 800AA994 37010003 */  ori   $at, $t8, 3
/* 0AB598 800AA998 38210002 */  xori  $at, $at, 2
/* 0AB59C 800AA99C 44C1F800 */  ctc1  $at, $31
/* 0AB5A0 800AA9A0 240E00FF */  li    $t6, 255
/* 0AB5A4 800AA9A4 27A50088 */  addiu $a1, $sp, 0x88
/* 0AB5A8 800AA9A8 00003025 */  move  $a2, $zero
/* 0AB5AC 800AA9AC 00003825 */  move  $a3, $zero
/* 0AB5B0 800AA9B0 0000C812 */  mflo  $t9
/* 0AB5B4 800AA9B4 00591021 */  addu  $v0, $v0, $t9
/* 0AB5B8 800AA9B8 AFA20088 */  sw    $v0, 0x88($sp)
/* 0AB5BC 800AA9BC C610000C */  lwc1  $f16, 0xc($s0)
/* 0AB5C0 800AA9C0 00000000 */  nop   
/* 0AB5C4 800AA9C4 46008124 */  cvt.w.s $f4, $f16
/* 0AB5C8 800AA9C8 44D8F800 */  ctc1  $t8, $31
/* 0AB5CC 800AA9CC 440B2000 */  mfc1  $t3, $f4
/* 0AB5D0 800AA9D0 00000000 */  nop   
/* 0AB5D4 800AA9D4 444DF800 */  cfc1  $t5, $31
/* 0AB5D8 800AA9D8 A7AB008C */  sh    $t3, 0x8c($sp)
/* 0AB5DC 800AA9DC 35A10003 */  ori   $at, $t5, 3
/* 0AB5E0 800AA9E0 38210002 */  xori  $at, $at, 2
/* 0AB5E4 800AA9E4 44C1F800 */  ctc1  $at, $31
/* 0AB5E8 800AA9E8 C60A0010 */  lwc1  $f10, 0x10($s0)
/* 0AB5EC 800AA9EC AFA00090 */  sw    $zero, 0x90($sp)
/* 0AB5F0 800AA9F0 460051A4 */  cvt.w.s $f6, $f10
/* 0AB5F4 800AA9F4 440C3000 */  mfc1  $t4, $f6
/* 0AB5F8 800AA9F8 44CDF800 */  ctc1  $t5, $31
/* 0AB5FC 800AA9FC 1480002C */  bnez  $a0, .L800AAAB0
/* 0AB600 800AAA00 A7AC008E */   sh    $t4, 0x8e($sp)
/* 0AB604 800AAA04 860E0006 */  lh    $t6, 6($s0)
/* 0AB608 800AAA08 24010035 */  li    $at, 53
/* 0AB60C 800AAA0C 15C1001A */  bne   $t6, $at, .L800AAA78
/* 0AB610 800AAA10 3C048012 */   lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0AB614 800AAA14 240100FF */  li    $at, 255
/* 0AB618 800AAA18 14610003 */  bne   $v1, $at, .L800AAA28
/* 0AB61C 800AAA1C 3C048012 */   lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0AB620 800AAA20 10000003 */  b     .L800AAA30
/* 0AB624 800AAA24 2402FFFE */   li    $v0, -2
.L800AAA28:
/* 0AB628 800AAA28 2401FF00 */  li    $at, -256
/* 0AB62C 800AAA2C 00611025 */  or    $v0, $v1, $at
.L800AAA30:
/* 0AB630 800AAA30 A7A0008C */  sh    $zero, 0x8c($sp)
/* 0AB634 800AAA34 A7A0008E */  sh    $zero, 0x8e($sp)
/* 0AB638 800AAA38 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 0AB63C 800AAA3C 44819000 */  mtc1  $at, $f18
/* 0AB640 800AAA40 8E070010 */  lw    $a3, 0x10($s0)
/* 0AB644 800AAA44 8E06000C */  lw    $a2, 0xc($s0)
/* 0AB648 800AAA48 3C01800F */  lui   $at, %hi(D_800E87D8) # $at, 0x800f
/* 0AB64C 800AAA4C C42887D8 */  lwc1  $f8, %lo(D_800E87D8)($at)
/* 0AB650 800AAA50 240F0001 */  li    $t7, 1
/* 0AB654 800AAA54 AFAF001C */  sw    $t7, 0x1c($sp)
/* 0AB658 800AAA58 AFA20018 */  sw    $v0, 0x18($sp)
/* 0AB65C 800AAA5C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0AB660 800AAA60 27A50088 */  addiu $a1, $sp, 0x88
/* 0AB664 800AAA64 E7B20010 */  swc1  $f18, 0x10($sp)
/* 0AB668 800AAA68 0C01E340 */  jal   render_texture_rectangle_scaled
/* 0AB66C 800AAA6C E7A80014 */   swc1  $f8, 0x14($sp)
/* 0AB670 800AAA70 10000018 */  b     .L800AAAD4
/* 0AB674 800AAA74 00000000 */   nop   
.L800AAA78:
/* 0AB678 800AAA78 241900FF */  li    $t9, 255
/* 0AB67C 800AAA7C 241800FF */  li    $t8, 255
/* 0AB680 800AAA80 240B00FF */  li    $t3, 255
/* 0AB684 800AAA84 AFAB0018 */  sw    $t3, 0x18($sp)
/* 0AB688 800AAA88 AFB80014 */  sw    $t8, 0x14($sp)
/* 0AB68C 800AAA8C AFB90010 */  sw    $t9, 0x10($sp)
/* 0AB690 800AAA90 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0AB694 800AAA94 27A50088 */  addiu $a1, $sp, 0x88
/* 0AB698 800AAA98 00003025 */  move  $a2, $zero
/* 0AB69C 800AAA9C 00003825 */  move  $a3, $zero
/* 0AB6A0 800AAAA0 0C01E2AE */  jal   render_textured_rectangle
/* 0AB6A4 800AAAA4 AFA3001C */   sw    $v1, 0x1c($sp)
/* 0AB6A8 800AAAA8 1000000A */  b     .L800AAAD4
/* 0AB6AC 800AAAAC 00000000 */   nop   
.L800AAAB0:
/* 0AB6B0 800AAAB0 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0AB6B4 800AAAB4 240D00FF */  li    $t5, 255
/* 0AB6B8 800AAAB8 240C00FF */  li    $t4, 255
/* 0AB6BC 800AAABC AFAC0014 */  sw    $t4, 0x14($sp)
/* 0AB6C0 800AAAC0 AFAD0010 */  sw    $t5, 0x10($sp)
/* 0AB6C4 800AAAC4 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0AB6C8 800AAAC8 AFAE0018 */  sw    $t6, 0x18($sp)
/* 0AB6CC 800AAACC 0C01E2AE */  jal   render_textured_rectangle
/* 0AB6D0 800AAAD0 AFA3001C */   sw    $v1, 0x1c($sp)
.L800AAAD4:
/* 0AB6D4 800AAAD4 3C0F8000 */  lui   $t7, %hi(osTvType) # $t7, 0x8000
/* 0AB6D8 800AAAD8 8DEF0300 */  lw    $t7, %lo(osTvType)($t7)
/* 0AB6DC 800AAADC 3C014100 */  li    $at, 0x41000000 # 8.000000
/* 0AB6E0 800AAAE0 15E00107 */  bnez  $t7, .L800AAF00
/* 0AB6E4 800AAAE4 00000000 */   nop   
/* 0AB6E8 800AAAE8 C6100010 */  lwc1  $f16, 0x10($s0)
/* 0AB6EC 800AAAEC 44812000 */  mtc1  $at, $f4
/* 0AB6F0 800AAAF0 00000000 */  nop   
/* 0AB6F4 800AAAF4 46048280 */  add.s $f10, $f16, $f4
/* 0AB6F8 800AAAF8 10000101 */  b     .L800AAF00
/* 0AB6FC 800AAAFC E60A0010 */   swc1  $f10, 0x10($s0)
.L800AAB00:
/* 0AB700 800AAB00 83396CD5 */  lb    $t9, %lo(D_80126CD5)($t9)
/* 0AB704 800AAB04 3C188000 */  lui   $t8, %hi(osTvType) # $t8, 0x8000
/* 0AB708 800AAB08 13200028 */  beqz  $t9, .L800AABAC
/* 0AB70C 800AAB0C 3C013FF0 */   lui   $at, 0x3ff0
/* 0AB710 800AAB10 8F180300 */  lw    $t8, %lo(osTvType)($t8)
/* 0AB714 800AAB14 00000000 */  nop   
/* 0AB718 800AAB18 17000024 */  bnez  $t8, .L800AABAC
/* 0AB71C 800AAB1C 00000000 */   nop   
/* 0AB720 800AAB20 8D2B0000 */  lw    $t3, ($t1)
/* 0AB724 800AAB24 00086880 */  sll   $t5, $t0, 2
/* 0AB728 800AAB28 016D6021 */  addu  $t4, $t3, $t5
/* 0AB72C 800AAB2C 8D820000 */  lw    $v0, ($t4)
/* 0AB730 800AAB30 860E0018 */  lh    $t6, 0x18($s0)
/* 0AB734 800AAB34 844F0016 */  lh    $t7, 0x16($v0)
/* 0AB738 800AAB38 A7A00074 */  sh    $zero, 0x74($sp)
/* 0AB73C 800AAB3C 01CF0019 */  multu $t6, $t7
/* 0AB740 800AAB40 A7A00076 */  sh    $zero, 0x76($sp)
/* 0AB744 800AAB44 AFA00078 */  sw    $zero, 0x78($sp)
# Used to access D_800E87E0 and D_800E87E0 + 4.
/* 0AB748 800AAB48 3C01800F */  lui   $at, %hi(D_800E87E0) # $at, 0x800f
/* 0AB74C 800AAB4C C43387E0 */  lwc1  $f19, %lo(D_800E87E0)($at)
/* 0AB750 800AAB50 C43287E4 */  lwc1  $f18, %lo(D_800E87E0 + 4)($at)
/* 0AB754 800AAB54 3C18800E */  lui   $t8, %hi(D_800E2834) # $t8, 0x800e
/* 0AB758 800AAB58 8F182834 */  lw    $t8, %lo(D_800E2834)($t8)
/* 0AB75C 800AAB5C 240B0001 */  li    $t3, 1
/* 0AB760 800AAB60 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0AB764 800AAB64 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0AB768 800AAB68 27A50070 */  addiu $a1, $sp, 0x70
/* 0AB76C 800AAB6C 0000C812 */  mflo  $t9
/* 0AB770 800AAB70 00591021 */  addu  $v0, $v0, $t9
/* 0AB774 800AAB74 AFA20070 */  sw    $v0, 0x70($sp)
/* 0AB778 800AAB78 C6000008 */  lwc1  $f0, 8($s0)
/* 0AB77C 800AAB7C 8E070010 */  lw    $a3, 0x10($s0)
/* 0AB780 800AAB80 460001A1 */  cvt.d.s $f6, $f0
/* 0AB784 800AAB84 46323202 */  mul.d $f8, $f6, $f18
/* 0AB788 800AAB88 8E06000C */  lw    $a2, 0xc($s0)
/* 0AB78C 800AAB8C AFAB001C */  sw    $t3, 0x1c($sp)
/* 0AB790 800AAB90 AFB80018 */  sw    $t8, 0x18($sp)
/* 0AB794 800AAB94 E7A00010 */  swc1  $f0, 0x10($sp)
/* 0AB798 800AAB98 46204420 */  cvt.s.d $f16, $f8
/* 0AB79C 800AAB9C 0C01E340 */  jal   render_texture_rectangle_scaled
/* 0AB7A0 800AABA0 E7B00014 */   swc1  $f16, 0x14($sp)
/* 0AB7A4 800AABA4 100000D7 */  b     .L800AAF04
/* 0AB7A8 800AABA8 86080006 */   lh    $t0, 6($s0)
.L800AABAC:
/* 0AB7AC 800AABAC C60A0008 */  lwc1  $f10, 8($s0)
/* 0AB7B0 800AABB0 44812800 */  mtc1  $at, $f5
/* 0AB7B4 800AABB4 44802000 */  mtc1  $zero, $f4
/* 0AB7B8 800AABB8 460051A1 */  cvt.d.s $f6, $f10
/* 0AB7BC 800AABBC 46262032 */  c.eq.d $f4, $f6
/* 0AB7C0 800AABC0 00000000 */  nop   
/* 0AB7C4 800AABC4 45000057 */  bc1f  .L800AAD24
/* 0AB7C8 800AABC8 00000000 */   nop   
/* 0AB7CC 800AABCC 8D2D0000 */  lw    $t5, ($t1)
/* 0AB7D0 800AABD0 00086080 */  sll   $t4, $t0, 2
/* 0AB7D4 800AABD4 01AC7021 */  addu  $t6, $t5, $t4
/* 0AB7D8 800AABD8 8DC30000 */  lw    $v1, ($t6)
/* 0AB7DC 800AABDC 860F0018 */  lh    $t7, 0x18($s0)
/* 0AB7E0 800AABE0 84790016 */  lh    $t9, 0x16($v1)
/* 0AB7E4 800AABE4 3C02800E */  lui   $v0, %hi(D_800E2834) # $v0, 0x800e
/* 0AB7E8 800AABE8 01F90019 */  multu $t7, $t9
/* 0AB7EC 800AABEC 8C422834 */  lw    $v0, %lo(D_800E2834)($v0)
/* 0AB7F0 800AABF0 2401FFFE */  li    $at, -2
/* 0AB7F4 800AABF4 3C058012 */  lui   $a1, %hi(D_80127180) # $a1, 0x8012
/* 0AB7F8 800AABF8 3C0D8012 */  lui   $t5, %hi(gHudSprites) # $t5, 0x8012
/* 0AB7FC 800AABFC 24A57180 */  addiu $a1, %lo(D_80127180) # addiu $a1, $a1, 0x7180
/* 0AB800 800AAC00 25AD6D80 */  addiu $t5, %lo(gHudSprites) # addiu $t5, $t5, 0x6d80
/* 0AB804 800AAC04 0000C012 */  mflo  $t8
/* 0AB808 800AAC08 00781821 */  addu  $v1, $v1, $t8
/* 0AB80C 800AAC0C 1441001B */  bne   $v0, $at, .L800AAC7C
/* 0AB810 800AAC10 00000000 */   nop   
/* 0AB814 800AAC14 8CA40000 */  lw    $a0, ($a1)
/* 0AB818 800AAC18 444CF800 */  cfc1  $t4, $31
/* 0AB81C 800AAC1C 000458C0 */  sll   $t3, $a0, 3
/* 0AB820 800AAC20 016D1021 */  addu  $v0, $t3, $t5
/* 0AB824 800AAC24 35810003 */  ori   $at, $t4, 3
/* 0AB828 800AAC28 AC430000 */  sw    $v1, ($v0)
/* 0AB82C 800AAC2C 38210002 */  xori  $at, $at, 2
/* 0AB830 800AAC30 44C1F800 */  ctc1  $at, $31
/* 0AB834 800AAC34 C612000C */  lwc1  $f18, 0xc($s0)
/* 0AB838 800AAC38 24980001 */  addiu $t8, $a0, 1
/* 0AB83C 800AAC3C 46009224 */  cvt.w.s $f8, $f18
/* 0AB840 800AAC40 44CCF800 */  ctc1  $t4, $31
/* 0AB844 800AAC44 440E4000 */  mfc1  $t6, $f8
/* 0AB848 800AAC48 00000000 */  nop   
/* 0AB84C 800AAC4C 444FF800 */  cfc1  $t7, $31
/* 0AB850 800AAC50 A44E0004 */  sh    $t6, 4($v0)
/* 0AB854 800AAC54 35E10003 */  ori   $at, $t7, 3
/* 0AB858 800AAC58 38210002 */  xori  $at, $at, 2
/* 0AB85C 800AAC5C 44C1F800 */  ctc1  $at, $31
/* 0AB860 800AAC60 C6100010 */  lwc1  $f16, 0x10($s0)
/* 0AB864 800AAC64 ACB80000 */  sw    $t8, ($a1)
/* 0AB868 800AAC68 460082A4 */  cvt.w.s $f10, $f16
/* 0AB86C 800AAC6C 44195000 */  mfc1  $t9, $f10
/* 0AB870 800AAC70 44CFF800 */  ctc1  $t7, $31
/* 0AB874 800AAC74 100000A2 */  b     .L800AAF00
/* 0AB878 800AAC78 A4590006 */   sh    $t9, 6($v0)
.L800AAC7C:
/* 0AB87C 800AAC7C 444BF800 */  cfc1  $t3, $31
/* 0AB880 800AAC80 AFA30058 */  sw    $v1, 0x58($sp)
/* 0AB884 800AAC84 35610003 */  ori   $at, $t3, 3
/* 0AB888 800AAC88 38210002 */  xori  $at, $at, 2
/* 0AB88C 800AAC8C 44C1F800 */  ctc1  $at, $31
/* 0AB890 800AAC90 C604000C */  lwc1  $f4, 0xc($s0)
/* 0AB894 800AAC94 00027E02 */  srl   $t7, $v0, 0x18
/* 0AB898 800AAC98 460021A4 */  cvt.w.s $f6, $f4
/* 0AB89C 800AAC9C 0002C402 */  srl   $t8, $v0, 0x10
/* 0AB8A0 800AACA0 44CBF800 */  ctc1  $t3, $31
/* 0AB8A4 800AACA4 440D3000 */  mfc1  $t5, $f6
/* 0AB8A8 800AACA8 330B00FF */  andi  $t3, $t8, 0xff
/* 0AB8AC 800AACAC 444CF800 */  cfc1  $t4, $31
/* 0AB8B0 800AACB0 A7AD005C */  sh    $t5, 0x5c($sp)
/* 0AB8B4 800AACB4 35810003 */  ori   $at, $t4, 3
/* 0AB8B8 800AACB8 38210002 */  xori  $at, $at, 2
/* 0AB8BC 800AACBC 44C1F800 */  ctc1  $at, $31
/* 0AB8C0 800AACC0 C6120010 */  lwc1  $f18, 0x10($s0)
/* 0AB8C4 800AACC4 00026A02 */  srl   $t5, $v0, 8
/* 0AB8C8 800AACC8 46009224 */  cvt.w.s $f8, $f18
/* 0AB8CC 800AACCC 31F900FF */  andi  $t9, $t7, 0xff
/* 0AB8D0 800AACD0 440E4000 */  mfc1  $t6, $f8
/* 0AB8D4 800AACD4 44CCF800 */  ctc1  $t4, $31
/* 0AB8D8 800AACD8 A7AE005E */  sh    $t6, 0x5e($sp)
/* 0AB8DC 800AACDC 304E00FF */  andi  $t6, $v0, 0xff
/* 0AB8E0 800AACE0 31AC00FF */  andi  $t4, $t5, 0xff
/* 0AB8E4 800AACE4 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0AB8E8 800AACE8 AFA00060 */  sw    $zero, 0x60($sp)
/* 0AB8EC 800AACEC 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0AB8F0 800AACF0 AFAC0018 */  sw    $t4, 0x18($sp)
/* 0AB8F4 800AACF4 AFAE001C */  sw    $t6, 0x1c($sp)
/* 0AB8F8 800AACF8 AFB90010 */  sw    $t9, 0x10($sp)
/* 0AB8FC 800AACFC AFAB0014 */  sw    $t3, 0x14($sp)
/* 0AB900 800AAD00 27A50058 */  addiu $a1, $sp, 0x58
/* 0AB904 800AAD04 00003025 */  move  $a2, $zero
/* 0AB908 800AAD08 0C01E2AE */  jal   render_textured_rectangle
/* 0AB90C 800AAD0C 00003825 */   move  $a3, $zero
/* 0AB910 800AAD10 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0AB914 800AAD14 0C01ECF4 */  jal   reset_render_settings
/* 0AB918 800AAD18 24846CFC */   addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0AB91C 800AAD1C 10000079 */  b     .L800AAF04
/* 0AB920 800AAD20 86080006 */   lh    $t0, 6($s0)
.L800AAD24:
/* 0AB924 800AAD24 8D2F0000 */  lw    $t7, ($t1)
/* 0AB928 800AAD28 0008C880 */  sll   $t9, $t0, 2
/* 0AB92C 800AAD2C 01F9C021 */  addu  $t8, $t7, $t9
/* 0AB930 800AAD30 8F020000 */  lw    $v0, ($t8)
/* 0AB934 800AAD34 860B0018 */  lh    $t3, 0x18($s0)
/* 0AB938 800AAD38 844D0016 */  lh    $t5, 0x16($v0)
/* 0AB93C 800AAD3C A7A0004C */  sh    $zero, 0x4c($sp)
/* 0AB940 800AAD40 016D0019 */  multu $t3, $t5
/* 0AB944 800AAD44 A7A0004E */  sh    $zero, 0x4e($sp)
/* 0AB948 800AAD48 AFA00050 */  sw    $zero, 0x50($sp)
/* 0AB94C 800AAD4C 3C0E800E */  lui   $t6, %hi(D_800E2834) # $t6, 0x800e
/* 0AB950 800AAD50 8DCE2834 */  lw    $t6, %lo(D_800E2834)($t6)
/* 0AB954 800AAD54 240F0001 */  li    $t7, 1
/* 0AB958 800AAD58 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0AB95C 800AAD5C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0AB960 800AAD60 27A50048 */  addiu $a1, $sp, 0x48
/* 0AB964 800AAD64 00006012 */  mflo  $t4
/* 0AB968 800AAD68 004C1021 */  addu  $v0, $v0, $t4
/* 0AB96C 800AAD6C AFA20048 */  sw    $v0, 0x48($sp)
/* 0AB970 800AAD70 C6000008 */  lwc1  $f0, 8($s0)
/* 0AB974 800AAD74 8E070010 */  lw    $a3, 0x10($s0)
/* 0AB978 800AAD78 8E06000C */  lw    $a2, 0xc($s0)
/* 0AB97C 800AAD7C AFAF001C */  sw    $t7, 0x1c($sp)
/* 0AB980 800AAD80 AFAE0018 */  sw    $t6, 0x18($sp)
/* 0AB984 800AAD84 E7A00014 */  swc1  $f0, 0x14($sp)
/* 0AB988 800AAD88 0C01E340 */  jal   render_texture_rectangle_scaled
/* 0AB98C 800AAD8C E7A00010 */   swc1  $f0, 0x10($sp)
/* 0AB990 800AAD90 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0AB994 800AAD94 0C01ECF4 */  jal   reset_render_settings
/* 0AB998 800AAD98 24846CFC */   addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0AB99C 800AAD9C 10000059 */  b     .L800AAF04
/* 0AB9A0 800AADA0 86080006 */   lh    $t0, 6($s0)
.L800AADA4:
/* 0AB9A4 800AADA4 13200020 */  beqz  $t9, .L800AAE28
/* 0AB9A8 800AADA8 304E4000 */   andi  $t6, $v0, 0x4000
/* 0AB9AC 800AADAC 0C01A748 */  jal   get_active_camera_segment
/* 0AB9B0 800AADB0 00000000 */   nop   
/* 0AB9B4 800AADB4 3C098012 */  lui   $t1, %hi(gAssetHudElements) # $t1, 0x8012
/* 0AB9B8 800AADB8 AFA200A8 */  sw    $v0, 0xa8($sp)
/* 0AB9BC 800AADBC 860B0006 */  lh    $t3, 6($s0)
/* 0AB9C0 800AADC0 25296CF4 */  addiu $t1, %lo(gAssetHudElements) # addiu $t1, $t1, 0x6cf4
/* 0AB9C4 800AADC4 8D380000 */  lw    $t8, ($t1)
/* 0AB9C8 800AADC8 000B6880 */  sll   $t5, $t3, 2
/* 0AB9CC 800AADCC 860E0004 */  lh    $t6, 4($s0)
/* 0AB9D0 800AADD0 844F0004 */  lh    $t7, 4($v0)
/* 0AB9D4 800AADD4 030D6021 */  addu  $t4, $t8, $t5
/* 0AB9D8 800AADD8 8D830000 */  lw    $v1, ($t4)
/* 0AB9DC 800AADDC 01CFC823 */  subu  $t9, $t6, $t7
/* 0AB9E0 800AADE0 A6190004 */  sh    $t9, 4($s0)
/* 0AB9E4 800AADE4 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0AB9E8 800AADE8 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0AB9EC 800AADEC 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0AB9F0 800AADF0 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0AB9F4 800AADF4 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0AB9F8 800AADF8 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0AB9FC 800AADFC AFA00014 */  sw    $zero, 0x14($sp)
/* 0ABA00 800AAE00 02003825 */  move  $a3, $s0
/* 0ABA04 800AAE04 0C01A2FD */  jal   render_ortho_triangle_image
/* 0ABA08 800AAE08 AFA30010 */   sw    $v1, 0x10($sp)
/* 0ABA0C 800AAE0C 8FB800A8 */  lw    $t8, 0xa8($sp)
/* 0ABA10 800AAE10 860B0004 */  lh    $t3, 4($s0)
/* 0ABA14 800AAE14 870D0004 */  lh    $t5, 4($t8)
/* 0ABA18 800AAE18 00000000 */  nop   
/* 0ABA1C 800AAE1C 016D6021 */  addu  $t4, $t3, $t5
/* 0ABA20 800AAE20 10000037 */  b     .L800AAF00
/* 0ABA24 800AAE24 A60C0004 */   sh    $t4, 4($s0)
.L800AAE28:
/* 0ABA28 800AAE28 11C0001F */  beqz  $t6, .L800AAEA8
/* 0ABA2C 800AAE2C 3C048012 */   lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0ABA30 800AAE30 8D2F0000 */  lw    $t7, ($t1)
/* 0ABA34 800AAE34 0008C880 */  sll   $t9, $t0, 2
/* 0ABA38 800AAE38 01F9C021 */  addu  $t8, $t7, $t9
/* 0ABA3C 800AAE3C 8F070000 */  lw    $a3, ($t8)
/* 0ABA40 800AAE40 860B0000 */  lh    $t3, ($s0)
/* 0ABA44 800AAE44 240E00FF */  li    $t6, 255
/* 0ABA48 800AAE48 A4EB0000 */  sh    $t3, ($a3)
/* 0ABA4C 800AAE4C 860D0002 */  lh    $t5, 2($s0)
/* 0ABA50 800AAE50 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0ABA54 800AAE54 A4ED0002 */  sh    $t5, 2($a3)
/* 0ABA58 800AAE58 860C0004 */  lh    $t4, 4($s0)
/* 0ABA5C 800AAE5C 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0ABA60 800AAE60 A4EC0004 */  sh    $t4, 4($a3)
/* 0ABA64 800AAE64 C610000C */  lwc1  $f16, 0xc($s0)
/* 0ABA68 800AAE68 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0ABA6C 800AAE6C E4F0000C */  swc1  $f16, 0xc($a3)
/* 0ABA70 800AAE70 C60A0010 */  lwc1  $f10, 0x10($s0)
/* 0ABA74 800AAE74 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0ABA78 800AAE78 E4EA0010 */  swc1  $f10, 0x10($a3)
/* 0ABA7C 800AAE7C C6040014 */  lwc1  $f4, 0x14($s0)
/* 0ABA80 800AAE80 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0ABA84 800AAE84 E4E40014 */  swc1  $f4, 0x14($a3)
/* 0ABA88 800AAE88 C6060008 */  lwc1  $f6, 8($s0)
/* 0ABA8C 800AAE8C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0ABA90 800AAE90 A0E0003A */  sb    $zero, 0x3a($a3)
/* 0ABA94 800AAE94 A0EE0039 */  sb    $t6, 0x39($a3)
/* 0ABA98 800AAE98 0C004B57 */  jal   render_object
/* 0ABA9C 800AAE9C E4E60008 */   swc1  $f6, 8($a3)
/* 0ABAA0 800AAEA0 10000018 */  b     .L800AAF04
/* 0ABAA4 800AAEA4 86080006 */   lh    $t0, 6($s0)
.L800AAEA8:
/* 0ABAA8 800AAEA8 44809000 */  mtc1  $zero, $f18
/* 0ABAAC 800AAEAC 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0ABAB0 800AAEB0 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0ABAB4 800AAEB4 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0ABAB8 800AAEB8 02003025 */  move  $a2, $s0
/* 0ABABC 800AAEBC 3C073F80 */  lui   $a3, 0x3f80
/* 0ABAC0 800AAEC0 0C01A521 */  jal   camera_push_model_mtx
/* 0ABAC4 800AAEC4 E7B20010 */   swc1  $f18, 0x10($sp)
/* 0ABAC8 800AAEC8 3C098012 */  lui   $t1, %hi(gAssetHudElements) # $t1, 0x8012
/* 0ABACC 800AAECC 86190006 */  lh    $t9, 6($s0)
/* 0ABAD0 800AAED0 25296CF4 */  addiu $t1, %lo(gAssetHudElements) # addiu $t1, $t1, 0x6cf4
/* 0ABAD4 800AAED4 8D2F0000 */  lw    $t7, ($t1)
/* 0ABAD8 800AAED8 0019C080 */  sll   $t8, $t9, 2
/* 0ABADC 800AAEDC 01F85821 */  addu  $t3, $t7, $t8
/* 0ABAE0 800AAEE0 8D620000 */  lw    $v0, ($t3)
/* 0ABAE4 800AAEE4 00000000 */  nop   
/* 0ABAE8 800AAEE8 8C440000 */  lw    $a0, ($v0)
/* 0ABAEC 800AAEEC 0C02ABF4 */  jal   func_800AAFD0
/* 0ABAF0 800AAEF0 00000000 */   nop   
/* 0ABAF4 800AAEF4 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0ABAF8 800AAEF8 0C01A690 */  jal   func_80069A40
/* 0ABAFC 800AAEFC 24846CFC */   addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
.L800AAF00:
/* 0ABB00 800AAF00 86080006 */  lh    $t0, 6($s0)
.L800AAF04:
/* 0ABB04 800AAF04 24010028 */  li    $at, 40
/* 0ABB08 800AAF08 11010021 */  beq   $t0, $at, .L800AAF90
/* 0ABB0C 800AAF0C 3C0B8012 */   lui   $t3, %hi(gHUDCurrDisplayList) # $t3, 0x8012
/* 0ABB10 800AAF10 2401000E */  li    $at, 14
/* 0ABB14 800AAF14 11010014 */  beq   $t0, $at, .L800AAF68
/* 0ABB18 800AAF18 3C198012 */   lui   $t9, %hi(D_80126D24) # $t9, 0x8012
/* 0ABB1C 800AAF1C 2401001B */  li    $at, 27
/* 0ABB20 800AAF20 11010011 */  beq   $t0, $at, .L800AAF68
/* 0ABB24 800AAF24 2901002F */   slti  $at, $t0, 0x2f
/* 0ABB28 800AAF28 14200002 */  bnez  $at, .L800AAF34
/* 0ABB2C 800AAF2C 29010036 */   slti  $at, $t0, 0x36
/* 0ABB30 800AAF30 1420000D */  bnez  $at, .L800AAF68
.L800AAF34:
/* 0ABB34 800AAF34 2401002E */   li    $at, 46
/* 0ABB38 800AAF38 1101000B */  beq   $t0, $at, .L800AAF68
/* 0ABB3C 800AAF3C 3C0D8012 */   lui   $t5, %hi(D_80126CD3) # $t5, 0x8012
/* 0ABB40 800AAF40 81AD6CD3 */  lb    $t5, %lo(D_80126CD3)($t5)
/* 0ABB44 800AAF44 8FAE00A4 */  lw    $t6, 0xa4($sp)
/* 0ABB48 800AAF48 31AC0001 */  andi  $t4, $t5, 1
/* 0ABB4C 800AAF4C 11800006 */  beqz  $t4, .L800AAF68
/* 0ABB50 800AAF50 00000000 */   nop   
/* 0ABB54 800AAF54 448E8000 */  mtc1  $t6, $f16
/* 0ABB58 800AAF58 C6080010 */  lwc1  $f8, 0x10($s0)
/* 0ABB5C 800AAF5C 468082A0 */  cvt.s.w $f10, $f16
/* 0ABB60 800AAF60 460A4101 */  sub.s $f4, $f8, $f10
/* 0ABB64 800AAF64 E6040010 */  swc1  $f4, 0x10($s0)
.L800AAF68:
/* 0ABB68 800AAF68 3C0F8012 */  lui   $t7, %hi(D_80126D28) # $t7, 0x8012
/* 0ABB6C 800AAF6C 8DEF6D28 */  lw    $t7, %lo(D_80126D28)($t7)
/* 0ABB70 800AAF70 8F396D24 */  lw    $t9, %lo(D_80126D24)($t9)
/* 0ABB74 800AAF74 C610000C */  lwc1  $f16, 0xc($s0)
/* 0ABB78 800AAF78 032FC021 */  addu  $t8, $t9, $t7
/* 0ABB7C 800AAF7C 44983000 */  mtc1  $t8, $f6
/* 0ABB80 800AAF80 00000000 */  nop   
/* 0ABB84 800AAF84 468034A0 */  cvt.s.w $f18, $f6
/* 0ABB88 800AAF88 46128201 */  sub.s $f8, $f16, $f18
/* 0ABB8C 800AAF8C E608000C */  swc1  $f8, 0xc($s0)
.L800AAF90:
/* 0ABB90 800AAF90 8D6B6CFC */  lw    $t3, %lo(gHUDCurrDisplayList)($t3)
/* 0ABB94 800AAF94 8FAD00B8 */  lw    $t5, 0xb8($sp)
/* 0ABB98 800AAF98 3C0C8012 */  lui   $t4, %hi(gHUDCurrMatrix) # $t4, 0x8012
/* 0ABB9C 800AAF9C ADAB0000 */  sw    $t3, ($t5)
/* 0ABBA0 800AAFA0 8FAE00BC */  lw    $t6, 0xbc($sp)
/* 0ABBA4 800AAFA4 8D8C6D00 */  lw    $t4, %lo(gHUDCurrMatrix)($t4)
/* 0ABBA8 800AAFA8 3C198012 */  lui   $t9, %hi(gHUDCurrVertex) # $t9, 0x8012
/* 0ABBAC 800AAFAC ADCC0000 */  sw    $t4, ($t6)
/* 0ABBB0 800AAFB0 8FAF00C0 */  lw    $t7, 0xc0($sp)
/* 0ABBB4 800AAFB4 8F396D04 */  lw    $t9, %lo(gHUDCurrVertex)($t9)
/* 0ABBB8 800AAFB8 00000000 */  nop   
/* 0ABBBC 800AAFBC ADF90000 */  sw    $t9, ($t7)
.L800AAFC0:
/* 0ABBC0 800AAFC0 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0ABBC4 800AAFC4 8FB00028 */  lw    $s0, 0x28($sp)
/* 0ABBC8 800AAFC8 03E00008 */  jr    $ra
/* 0ABBCC 800AAFCC 27BD00B8 */   addiu $sp, $sp, 0xb8

