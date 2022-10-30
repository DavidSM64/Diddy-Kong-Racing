glabel func_800A45F0
/* 0A51F0 800A45F0 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 0A51F4 800A45F4 AFB7003C */  sw    $s7, 0x3c($sp)
/* 0A51F8 800A45F8 444EF800 */  cfc1  $t6, $31
/* 0A51FC 800A45FC 3C178012 */  lui   $s7, %hi(D_80126CDC) # $s7, 0x8012
/* 0A5200 800A4600 26F76CDC */  addiu $s7, %lo(D_80126CDC) # addiu $s7, $s7, 0x6cdc
/* 0A5204 800A4604 AFB10024 */  sw    $s1, 0x24($sp)
/* 0A5208 800A4608 8EF10000 */  lw    $s1, ($s7)
/* 0A520C 800A460C 35C10003 */  ori   $at, $t6, 3
/* 0A5210 800A4610 AFBF0044 */  sw    $ra, 0x44($sp)
/* 0A5214 800A4614 AFBE0040 */  sw    $fp, 0x40($sp)
/* 0A5218 800A4618 AFB60038 */  sw    $s6, 0x38($sp)
/* 0A521C 800A461C AFB50034 */  sw    $s5, 0x34($sp)
/* 0A5220 800A4620 AFB40030 */  sw    $s4, 0x30($sp)
/* 0A5224 800A4624 AFB3002C */  sw    $s3, 0x2c($sp)
/* 0A5228 800A4628 AFB20028 */  sw    $s2, 0x28($sp)
/* 0A522C 800A462C AFB00020 */  sw    $s0, 0x20($sp)
/* 0A5230 800A4630 E7B50018 */  swc1  $f21, 0x18($sp)
/* 0A5234 800A4634 E7B4001C */  swc1  $f20, 0x1c($sp)
/* 0A5238 800A4638 38210002 */  xori  $at, $at, 2
/* 0A523C 800A463C 44C1F800 */  ctc1  $at, $31
/* 0A5240 800A4640 C6240410 */  lwc1  $f4, 0x410($s1)
/* 0A5244 800A4644 3C028012 */  lui   $v0, %hi(D_80126D37) # $v0, 0x8012
/* 0A5248 800A4648 460021A4 */  cvt.w.s $f6, $f4
/* 0A524C 800A464C 90426D37 */  lbu   $v0, %lo(D_80126D37)($v0)
/* 0A5250 800A4650 440F3000 */  mfc1  $t7, $f6
/* 0A5254 800A4654 44CEF800 */  ctc1  $t6, $31
/* 0A5258 800A4658 28410003 */  slti  $at, $v0, 3
/* 0A525C 800A465C 0080B025 */  move  $s6, $a0
/* 0A5260 800A4660 14200008 */  bnez  $at, .L800A4684
/* 0A5264 800A4664 AFAF0048 */   sw    $t7, 0x48($sp)
/* 0A5268 800A4668 24010003 */  li    $at, 3
/* 0A526C 800A466C 14410017 */  bne   $v0, $at, .L800A46CC
/* 0A5270 800A4670 3C014040 */   lui   $at, 0x4040
/* 0A5274 800A4674 84980000 */  lh    $t8, ($a0)
/* 0A5278 800A4678 2401FFFF */  li    $at, -1
/* 0A527C 800A467C 17010013 */  bne   $t8, $at, .L800A46CC
/* 0A5280 800A4680 3C014040 */   lui   $at, 0x4040
.L800A4684:
/* 0A5284 800A4684 82D90003 */  lb    $t9, 3($s6)
/* 0A5288 800A4688 3C128012 */  lui   $s2, %hi(D_80126CD5) # $s2, 0x8012
/* 0A528C 800A468C 27280038 */  addiu $t0, $t9, 0x38
/* 0A5290 800A4690 A6280646 */  sh    $t0, 0x646($s1)
/* 0A5294 800A4694 8EE70000 */  lw    $a3, ($s7)
/* 0A5298 800A4698 26526CD5 */  addiu $s2, %lo(D_80126CD5) # addiu $s2, $s2, 0x6cd5
/* 0A529C 800A469C 241E0001 */  li    $fp, 1
/* 0A52A0 800A46A0 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A52A4 800A46A4 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A52A8 800A46A8 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A52AC 800A46AC A25E0000 */  sb    $fp, ($s2)
/* 0A52B0 800A46B0 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A52B4 800A46B4 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A52B8 800A46B8 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A52BC 800A46BC 0C02A980 */  jal   func_800AA600
/* 0A52C0 800A46C0 24E70640 */   addiu $a3, $a3, 0x640
/* 0A52C4 800A46C4 A2400000 */  sb    $zero, ($s2)
/* 0A52C8 800A46C8 3C014040 */  li    $at, 0x40400000 # 3.000000
.L800A46CC:
/* 0A52CC 800A46CC 3C128012 */  lui   $s2, %hi(D_80126CD5) # $s2, 0x8012
/* 0A52D0 800A46D0 3C15800E */  lui   $s5, %hi(D_800E2834) # $s5, 0x800e
/* 0A52D4 800A46D4 3C138080 */  lui   $s3, (0x80808080 >> 16) # lui $s3, 0x8080
/* 0A52D8 800A46D8 4481A000 */  mtc1  $at, $f20
/* 0A52DC 800A46DC 26526CD5 */  addiu $s2, %lo(D_80126CD5) # addiu $s2, $s2, 0x6cd5
/* 0A52E0 800A46E0 241E0001 */  li    $fp, 1
/* 0A52E4 800A46E4 36738080 */  ori   $s3, (0x80808080 & 0xFFFF) # ori $s3, $s3, 0x8080
/* 0A52E8 800A46E8 26B52834 */  addiu $s5, %lo(D_800E2834) # addiu $s5, $s5, 0x2834
/* 0A52EC 800A46EC 00008025 */  move  $s0, $zero
/* 0A52F0 800A46F0 2414000A */  li    $s4, 10
.L800A46F4:
/* 0A52F4 800A46F4 82C90193 */  lb    $t1, 0x193($s6)
/* 0A52F8 800A46F8 8EF10000 */  lw    $s1, ($s7)
/* 0A52FC 800A46FC 0209082A */  slt   $at, $s0, $t1
/* 0A5300 800A4700 14200002 */  bnez  $at, .L800A470C
/* 0A5304 800A4704 3C048012 */   lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5308 800A4708 AEB30000 */  sw    $s3, ($s5)
.L800A470C:
/* 0A530C 800A470C 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A5310 800A4710 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A5314 800A4714 A25E0000 */  sb    $fp, ($s2)
/* 0A5318 800A4718 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A531C 800A471C 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A5320 800A4720 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5324 800A4724 0C02A980 */  jal   func_800AA600
/* 0A5328 800A4728 26270400 */   addiu $a3, $s1, 0x400
/* 0A532C 800A472C 8EF10000 */  lw    $s1, ($s7)
/* 0A5330 800A4730 A2400000 */  sb    $zero, ($s2)
/* 0A5334 800A4734 C6280410 */  lwc1  $f8, 0x410($s1)
/* 0A5338 800A4738 26100001 */  addiu $s0, $s0, 1
/* 0A533C 800A473C 46144281 */  sub.s $f10, $f8, $f20
/* 0A5340 800A4740 1614FFEC */  bne   $s0, $s4, .L800A46F4
/* 0A5344 800A4744 E62A0410 */   swc1  $f10, 0x410($s1)
/* 0A5348 800A4748 8FAA0048 */  lw    $t2, 0x48($sp)
/* 0A534C 800A474C 8EEB0000 */  lw    $t3, ($s7)
/* 0A5350 800A4750 448A8000 */  mtc1  $t2, $f16
/* 0A5354 800A4754 240CFFFE */  li    $t4, -2
/* 0A5358 800A4758 468084A0 */  cvt.s.w $f18, $f16
/* 0A535C 800A475C E5720410 */  swc1  $f18, 0x410($t3)
/* 0A5360 800A4760 8FBF0044 */  lw    $ra, 0x44($sp)
/* 0A5364 800A4764 AEAC0000 */  sw    $t4, ($s5)
/* 0A5368 800A4768 A2400000 */  sb    $zero, ($s2)
/* 0A536C 800A476C 8FB20028 */  lw    $s2, 0x28($sp)
/* 0A5370 800A4770 8FB50034 */  lw    $s5, 0x34($sp)
/* 0A5374 800A4774 8FBE0040 */  lw    $fp, 0x40($sp)
/* 0A5378 800A4778 8FB7003C */  lw    $s7, 0x3c($sp)
/* 0A537C 800A477C 8FB60038 */  lw    $s6, 0x38($sp)
/* 0A5380 800A4780 8FB40030 */  lw    $s4, 0x30($sp)
/* 0A5384 800A4784 8FB3002C */  lw    $s3, 0x2c($sp)
/* 0A5388 800A4788 8FB10024 */  lw    $s1, 0x24($sp)
/* 0A538C 800A478C 8FB00020 */  lw    $s0, 0x20($sp)
/* 0A5390 800A4790 C7B4001C */  lwc1  $f20, 0x1c($sp)
/* 0A5394 800A4794 C7B50018 */  lwc1  $f21, 0x18($sp)
/* 0A5398 800A4798 03E00008 */  jr    $ra
/* 0A539C 800A479C 27BD0050 */   addiu $sp, $sp, 0x50

