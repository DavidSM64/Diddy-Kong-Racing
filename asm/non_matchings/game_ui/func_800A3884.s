.late_rodata
glabel D_800E8740
.float 25744.0

.text
glabel func_800A3884
/* 0A4484 800A3884 3C0E8012 */  lui   $t6, %hi(D_80126D37) # $t6, 0x8012
/* 0A4488 800A3888 91CE6D37 */  lbu   $t6, %lo(D_80126D37)($t6)
/* 0A448C 800A388C 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0A4490 800A3890 24010001 */  li    $at, 1
/* 0A4494 800A3894 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0A4498 800A3898 15C1010E */  bne   $t6, $at, .L800A3CD4
/* 0A449C 800A389C AFA5002C */   sw    $a1, 0x2c($sp)
/* 0A44A0 800A38A0 0C019944 */  jal   check_if_showing_cutscene_camera
/* 0A44A4 800A38A4 AFA40028 */   sw    $a0, 0x28($sp)
/* 0A44A8 800A38A8 8FA40028 */  lw    $a0, 0x28($sp)
/* 0A44AC 800A38AC 1440010A */  bnez  $v0, .L800A3CD8
/* 0A44B0 800A38B0 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0A44B4 800A38B4 8C820064 */  lw    $v0, 0x64($a0)
/* 0A44B8 800A38B8 00000000 */  nop   
/* 0A44BC 800A38BC 804F01D8 */  lb    $t7, 0x1d8($v0)
/* 0A44C0 800A38C0 00000000 */  nop   
/* 0A44C4 800A38C4 15E00104 */  bnez  $t7, .L800A3CD8
/* 0A44C8 800A38C8 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0A44CC 800A38CC 805801D6 */  lb    $t8, 0x1d6($v0)
/* 0A44D0 800A38D0 24010002 */  li    $at, 2
/* 0A44D4 800A38D4 1701000F */  bne   $t8, $at, .L800A3914
/* 0A44D8 800A38D8 00000000 */   nop   
/* 0A44DC 800A38DC C480001C */  lwc1  $f0, 0x1c($a0)
/* 0A44E0 800A38E0 C4820020 */  lwc1  $f2, 0x20($a0)
/* 0A44E4 800A38E4 46000102 */  mul.s $f4, $f0, $f0
/* 0A44E8 800A38E8 C48E0024 */  lwc1  $f14, 0x24($a0)
/* 0A44EC 800A38EC AFA20020 */  sw    $v0, 0x20($sp)
/* 0A44F0 800A38F0 46021182 */  mul.s $f6, $f2, $f2
/* 0A44F4 800A38F4 00000000 */  nop   
/* 0A44F8 800A38F8 460E7282 */  mul.s $f10, $f14, $f14
/* 0A44FC 800A38FC 46062200 */  add.s $f8, $f4, $f6
/* 0A4500 800A3900 0C0326B4 */  jal   sqrtf
/* 0A4504 800A3904 460A4300 */   add.s $f12, $f8, $f10
/* 0A4508 800A3908 8FA20020 */  lw    $v0, 0x20($sp)
/* 0A450C 800A390C 1000000A */  b     .L800A3938
/* 0A4510 800A3910 00000000 */   nop   
.L800A3914:
/* 0A4514 800A3914 C480001C */  lwc1  $f0, 0x1c($a0)
/* 0A4518 800A3918 C48E0024 */  lwc1  $f14, 0x24($a0)
/* 0A451C 800A391C 46000402 */  mul.s $f16, $f0, $f0
/* 0A4520 800A3920 AFA20020 */  sw    $v0, 0x20($sp)
/* 0A4524 800A3924 460E7482 */  mul.s $f18, $f14, $f14
/* 0A4528 800A3928 0C0326B4 */  jal   sqrtf
/* 0A452C 800A392C 46128300 */   add.s $f12, $f16, $f18
/* 0A4530 800A3930 8FA20020 */  lw    $v0, 0x20($sp)
/* 0A4534 800A3934 00000000 */  nop   
.L800A3938:
/* 0A4538 800A3938 3C01800E */  lui   $at, %hi(D_800E2838) # $at, 0x800e
/* 0A453C 800A393C C4242838 */  lwc1  $f4, %lo(D_800E2838)($at)
/* 0A4540 800A3940 44806000 */  mtc1  $zero, $f12
/* 0A4544 800A3944 4600203C */  c.lt.s $f4, $f0
/* 0A4548 800A3948 3C01800E */  lui   $at, %hi(D_800E2838) # $at, 0x800e
/* 0A454C 800A394C 45000002 */  bc1f  .L800A3958
/* 0A4550 800A3950 00000000 */   nop   
/* 0A4554 800A3954 E4202838 */  swc1  $f0, %lo(D_800E2838)($at)
.L800A3958:
/* 0A4558 800A3958 3C014080 */  li    $at, 0x40800000 # 4.000000
/* 0A455C 800A395C 44813000 */  mtc1  $at, $f6
/* 0A4560 800A3960 805901E6 */  lb    $t9, 0x1e6($v0)
/* 0A4564 800A3964 46060082 */  mul.s $f2, $f0, $f6
/* 0A4568 800A3968 13200004 */  beqz  $t9, .L800A397C
/* 0A456C 800A396C 3C0140E0 */   li    $at, 0x40E00000 # 7.000000
/* 0A4570 800A3970 44814000 */  mtc1  $at, $f8
/* 0A4574 800A3974 00000000 */  nop   
/* 0A4578 800A3978 46081080 */  add.s $f2, $f2, $f8
.L800A397C:
/* 0A457C 800A397C 3C0142C8 */  li    $at, 0x42C80000 # 100.000000
/* 0A4580 800A3980 44810000 */  mtc1  $at, $f0
/* 0A4584 800A3984 3C01800F */  lui   $at, %hi(D_800E8740) # $at, 0x800f
/* 0A4588 800A3988 4602003C */  c.lt.s $f0, $f2
/* 0A458C 800A398C 00000000 */  nop   
/* 0A4590 800A3990 45000002 */  bc1f  .L800A399C
/* 0A4594 800A3994 00000000 */   nop   
/* 0A4598 800A3998 46000086 */  mov.s $f2, $f0
.L800A399C:
/* 0A459C 800A399C C44A002C */  lwc1  $f10, 0x2c($v0)
/* 0A45A0 800A39A0 00000000 */  nop   
/* 0A45A4 800A39A4 460A603C */  c.lt.s $f12, $f10
/* 0A45A8 800A39A8 00000000 */  nop   
/* 0A45AC 800A39AC 45000002 */  bc1f  .L800A39B8
/* 0A45B0 800A39B0 00000000 */   nop   
/* 0A45B4 800A39B4 46006086 */  mov.s $f2, $f12
.L800A39B8:
/* 0A45B8 800A39B8 C42C8740 */  lwc1  $f12, %lo(D_800E8740)($at)
/* 0A45BC 800A39BC 3C014396 */  li    $at, 0x43960000 # 300.000000
/* 0A45C0 800A39C0 46020081 */  sub.s $f2, $f0, $f2
/* 0A45C4 800A39C4 44818000 */  mtc1  $at, $f16
/* 0A45C8 800A39C8 00000000 */  nop   
/* 0A45CC 800A39CC 46101082 */  mul.s $f2, $f2, $f16
/* 0A45D0 800A39D0 4602603C */  c.lt.s $f12, $f2
/* 0A45D4 800A39D4 00000000 */  nop   
/* 0A45D8 800A39D8 45000002 */  bc1f  .L800A39E4
/* 0A45DC 800A39DC 00000000 */   nop   
/* 0A45E0 800A39E0 46006086 */  mov.s $f2, $f12
.L800A39E4:
/* 0A45E4 800A39E4 0C01BAA8 */  jal   is_game_paused
/* 0A45E8 800A39E8 E7A20024 */   swc1  $f2, 0x24($sp)
/* 0A45EC 800A39EC C7A20024 */  lwc1  $f2, 0x24($sp)
/* 0A45F0 800A39F0 1440002E */  bnez  $v0, .L800A3AAC
/* 0A45F4 800A39F4 3C0D8012 */   lui   $t5, %hi(gHUDNumPlayers) # $t5, 0x8012
/* 0A45F8 800A39F8 3C028012 */  lui   $v0, %hi(D_80126CDC) # $v0, 0x8012
/* 0A45FC 800A39FC 8C426CDC */  lw    $v0, %lo(D_80126CDC)($v0)
/* 0A4600 800A3A00 3C014100 */  li    $at, 0x41000000 # 8.000000
/* 0A4604 800A3A04 844804C4 */  lh    $t0, 0x4c4($v0)
/* 0A4608 800A3A08 00000000 */  nop   
/* 0A460C 800A3A0C 44889000 */  mtc1  $t0, $f18
/* 0A4610 800A3A10 00000000 */  nop   
/* 0A4614 800A3A14 46809020 */  cvt.s.w $f0, $f18
/* 0A4618 800A3A18 4600103C */  c.lt.s $f2, $f0
/* 0A461C 800A3A1C 00000000 */  nop   
/* 0A4620 800A3A20 45000012 */  bc1f  .L800A3A6C
/* 0A4624 800A3A24 00000000 */   nop   
/* 0A4628 800A3A28 3C014000 */  li    $at, 0x40000000 # 2.000000
/* 0A462C 800A3A2C 44813000 */  mtc1  $at, $f6
/* 0A4630 800A3A30 46001101 */  sub.s $f4, $f2, $f0
/* 0A4634 800A3A34 00000000 */  nop   
/* 0A4638 800A3A38 46062203 */  div.s $f8, $f4, $f6
/* 0A463C 800A3A3C 46080280 */  add.s $f10, $f0, $f8
/* 0A4640 800A3A40 4449F800 */  cfc1  $t1, $31
/* 0A4644 800A3A44 00000000 */  nop   
/* 0A4648 800A3A48 35210003 */  ori   $at, $t1, 3
/* 0A464C 800A3A4C 38210002 */  xori  $at, $at, 2
/* 0A4650 800A3A50 44C1F800 */  ctc1  $at, $31
/* 0A4654 800A3A54 00000000 */  nop   
/* 0A4658 800A3A58 46005424 */  cvt.w.s $f16, $f10
/* 0A465C 800A3A5C 440A8000 */  mfc1  $t2, $f16
/* 0A4660 800A3A60 44C9F800 */  ctc1  $t1, $31
/* 0A4664 800A3A64 10000011 */  b     .L800A3AAC
/* 0A4668 800A3A68 A44A04C4 */   sh    $t2, 0x4c4($v0)
.L800A3A6C:
/* 0A466C 800A3A6C 46001481 */  sub.s $f18, $f2, $f0
/* 0A4670 800A3A70 44812000 */  mtc1  $at, $f4
/* 0A4674 800A3A74 00000000 */  nop   
/* 0A4678 800A3A78 46049183 */  div.s $f6, $f18, $f4
/* 0A467C 800A3A7C 46060200 */  add.s $f8, $f0, $f6
/* 0A4680 800A3A80 444BF800 */  cfc1  $t3, $31
/* 0A4684 800A3A84 00000000 */  nop   
/* 0A4688 800A3A88 35610003 */  ori   $at, $t3, 3
/* 0A468C 800A3A8C 38210002 */  xori  $at, $at, 2
/* 0A4690 800A3A90 44C1F800 */  ctc1  $at, $31
/* 0A4694 800A3A94 00000000 */  nop   
/* 0A4698 800A3A98 460042A4 */  cvt.w.s $f10, $f8
/* 0A469C 800A3A9C 440C5000 */  mfc1  $t4, $f10
/* 0A46A0 800A3AA0 44CBF800 */  ctc1  $t3, $31
/* 0A46A4 800A3AA4 A44C04C4 */  sh    $t4, 0x4c4($v0)
/* 0A46A8 800A3AA8 00000000 */  nop   
.L800A3AAC:
/* 0A46AC 800A3AAC 8DAD6D0C */  lw    $t5, %lo(gHUDNumPlayers)($t5)
/* 0A46B0 800A3AB0 3C0E800E */  lui   $t6, %hi(D_800E27A4) # $t6, 0x800e
/* 0A46B4 800A3AB4 01CD7021 */  addu  $t6, $t6, $t5
/* 0A46B8 800A3AB8 81CE27A4 */  lb    $t6, %lo(D_800E27A4)($t6)
/* 0A46BC 800A3ABC 3C0F8012 */  lui   $t7, %hi(D_80126CD3) # $t7, 0x8012
/* 0A46C0 800A3AC0 15C00084 */  bnez  $t6, .L800A3CD4
/* 0A46C4 800A3AC4 3C048012 */   lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A46C8 800A3AC8 81EF6CD3 */  lb    $t7, %lo(D_80126CD3)($t7)
/* 0A46CC 800A3ACC 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A46D0 800A3AD0 31F80002 */  andi  $t8, $t7, 2
/* 0A46D4 800A3AD4 1300001F */  beqz  $t8, .L800A3B54
/* 0A46D8 800A3AD8 3C058012 */   lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A46DC 800A3ADC 3C198012 */  lui   $t9, %hi(D_80126CD0) # $t9, 0x8012
/* 0A46E0 800A3AE0 83396CD0 */  lb    $t9, %lo(D_80126CD0)($t9)
/* 0A46E4 800A3AE4 3C088012 */  lui   $t0, %hi(D_8012718B) # $t0, 0x8012
/* 0A46E8 800A3AE8 44998000 */  mtc1  $t9, $f16
/* 0A46EC 800A3AEC 9108718B */  lbu   $t0, %lo(D_8012718B)($t0)
/* 0A46F0 800A3AF0 468084A0 */  cvt.s.w $f18, $f16
/* 0A46F4 800A3AF4 3C01437F */  li    $at, 0x437F0000 # 255.000000
/* 0A46F8 800A3AF8 44810000 */  mtc1  $at, $f0
/* 0A46FC 800A3AFC 44883000 */  mtc1  $t0, $f6
/* 0A4700 800A3B00 46009102 */  mul.s $f4, $f18, $f0
/* 0A4704 800A3B04 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0A4708 800A3B08 05010004 */  bgez  $t0, .L800A3B1C
/* 0A470C 800A3B0C 46803220 */   cvt.s.w $f8, $f6
/* 0A4710 800A3B10 44815000 */  mtc1  $at, $f10
/* 0A4714 800A3B14 00000000 */  nop   
/* 0A4718 800A3B18 460A4200 */  add.s $f8, $f8, $f10
.L800A3B1C:
/* 0A471C 800A3B1C 00000000 */  nop   
/* 0A4720 800A3B20 46082403 */  div.s $f16, $f4, $f8
/* 0A4724 800A3B24 46100481 */  sub.s $f18, $f0, $f16
/* 0A4728 800A3B28 4449F800 */  cfc1  $t1, $31
/* 0A472C 800A3B2C 00000000 */  nop   
/* 0A4730 800A3B30 35210003 */  ori   $at, $t1, 3
/* 0A4734 800A3B34 38210002 */  xori  $at, $at, 2
/* 0A4738 800A3B38 44C1F800 */  ctc1  $at, $31
/* 0A473C 800A3B3C 00000000 */  nop   
/* 0A4740 800A3B40 460091A4 */  cvt.w.s $f6, $f18
/* 0A4744 800A3B44 440A3000 */  mfc1  $t2, $f6
/* 0A4748 800A3B48 44C9F800 */  ctc1  $t1, $31
/* 0A474C 800A3B4C 10000003 */  b     .L800A3B5C
/* 0A4750 800A3B50 AFAA001C */   sw    $t2, 0x1c($sp)
.L800A3B54:
/* 0A4754 800A3B54 240B00FF */  li    $t3, 255
/* 0A4758 800A3B58 AFAB001C */  sw    $t3, 0x1c($sp)
.L800A3B5C:
/* 0A475C 800A3B5C 3C078012 */  lui   $a3, %hi(D_80126CDC) # $a3, 0x8012
/* 0A4760 800A3B60 8CE76CDC */  lw    $a3, %lo(D_80126CDC)($a3)
/* 0A4764 800A3B64 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A4768 800A3B68 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A476C 800A3B6C 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A4770 800A3B70 0C02A980 */  jal   func_800AA600
/* 0A4774 800A3B74 24E705A0 */   addiu $a3, $a3, 0x5a0
/* 0A4778 800A3B78 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A477C 800A3B7C 0C01ECF4 */  jal   func_8007B3D0
/* 0A4780 800A3B80 24846CFC */   addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A4784 800A3B84 0C01EFC7 */  jal   func_8007BF1C
/* 0A4788 800A3B88 24040001 */   li    $a0, 1
/* 0A478C 800A3B8C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4790 800A3B90 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A4794 800A3B94 8C830000 */  lw    $v1, ($a0)
/* 0A4798 800A3B98 3C0DFA00 */  lui   $t5, 0xfa00
/* 0A479C 800A3B9C 246C0008 */  addiu $t4, $v1, 8
/* 0A47A0 800A3BA0 AC8C0000 */  sw    $t4, ($a0)
/* 0A47A4 800A3BA4 AC6D0000 */  sw    $t5, ($v1)
/* 0A47A8 800A3BA8 8FAE001C */  lw    $t6, 0x1c($sp)
/* 0A47AC 800A3BAC 2401FF00 */  li    $at, -256
/* 0A47B0 800A3BB0 31CF00FF */  andi  $t7, $t6, 0xff
/* 0A47B4 800A3BB4 01E1C025 */  or    $t8, $t7, $at
/* 0A47B8 800A3BB8 3C078012 */  lui   $a3, %hi(D_80126CDC) # $a3, 0x8012
/* 0A47BC 800A3BBC AC780004 */  sw    $t8, 4($v1)
/* 0A47C0 800A3BC0 8CE76CDC */  lw    $a3, %lo(D_80126CDC)($a3)
/* 0A47C4 800A3BC4 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A47C8 800A3BC8 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A47CC 800A3BCC 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A47D0 800A3BD0 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A47D4 800A3BD4 0C02A980 */  jal   func_800AA600
/* 0A47D8 800A3BD8 24E704C0 */   addiu $a3, $a3, 0x4c0
/* 0A47DC 800A3BDC 0C01EFC7 */  jal   func_8007BF1C
/* 0A47E0 800A3BE0 00002025 */   move  $a0, $zero
/* 0A47E4 800A3BE4 3C078012 */  lui   $a3, %hi(D_80126CDC) # $a3, 0x8012
/* 0A47E8 800A3BE8 8CE76CDC */  lw    $a3, %lo(D_80126CDC)($a3)
/* 0A47EC 800A3BEC 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A47F0 800A3BF0 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A47F4 800A3BF4 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A47F8 800A3BF8 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A47FC 800A3BFC 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A4800 800A3C00 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A4804 800A3C04 0C02A980 */  jal   func_800AA600
/* 0A4808 800A3C08 24E704E0 */   addiu $a3, $a3, 0x4e0
/* 0A480C 800A3C0C 3C078012 */  lui   $a3, %hi(D_80126CDC) # $a3, 0x8012
/* 0A4810 800A3C10 8CE76CDC */  lw    $a3, %lo(D_80126CDC)($a3)
/* 0A4814 800A3C14 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4818 800A3C18 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A481C 800A3C1C 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A4820 800A3C20 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A4824 800A3C24 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A4828 800A3C28 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A482C 800A3C2C 0C02A980 */  jal   func_800AA600
/* 0A4830 800A3C30 24E70500 */   addiu $a3, $a3, 0x500
/* 0A4834 800A3C34 3C078012 */  lui   $a3, %hi(D_80126CDC) # $a3, 0x8012
/* 0A4838 800A3C38 8CE76CDC */  lw    $a3, %lo(D_80126CDC)($a3)
/* 0A483C 800A3C3C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4840 800A3C40 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A4844 800A3C44 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A4848 800A3C48 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A484C 800A3C4C 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A4850 800A3C50 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A4854 800A3C54 0C02A980 */  jal   func_800AA600
/* 0A4858 800A3C58 24E70520 */   addiu $a3, $a3, 0x520
/* 0A485C 800A3C5C 3C078012 */  lui   $a3, %hi(D_80126CDC) # $a3, 0x8012
/* 0A4860 800A3C60 8CE76CDC */  lw    $a3, %lo(D_80126CDC)($a3)
/* 0A4864 800A3C64 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4868 800A3C68 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A486C 800A3C6C 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A4870 800A3C70 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A4874 800A3C74 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A4878 800A3C78 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A487C 800A3C7C 0C02A980 */  jal   func_800AA600
/* 0A4880 800A3C80 24E70540 */   addiu $a3, $a3, 0x540
/* 0A4884 800A3C84 3C078012 */  lui   $a3, %hi(D_80126CDC) # $a3, 0x8012
/* 0A4888 800A3C88 8CE76CDC */  lw    $a3, %lo(D_80126CDC)($a3)
/* 0A488C 800A3C8C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A4890 800A3C90 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A4894 800A3C94 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A4898 800A3C98 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A489C 800A3C9C 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A48A0 800A3CA0 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A48A4 800A3CA4 0C02A980 */  jal   func_800AA600
/* 0A48A8 800A3CA8 24E70560 */   addiu $a3, $a3, 0x560
/* 0A48AC 800A3CAC 3C078012 */  lui   $a3, %hi(D_80126CDC) # $a3, 0x8012
/* 0A48B0 800A3CB0 8CE76CDC */  lw    $a3, %lo(D_80126CDC)($a3)
/* 0A48B4 800A3CB4 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A48B8 800A3CB8 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A48BC 800A3CBC 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A48C0 800A3CC0 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A48C4 800A3CC4 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A48C8 800A3CC8 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A48CC 800A3CCC 0C02A980 */  jal   func_800AA600
/* 0A48D0 800A3CD0 24E70580 */   addiu $a3, $a3, 0x580
.L800A3CD4:
/* 0A48D4 800A3CD4 8FBF0014 */  lw    $ra, 0x14($sp)
.L800A3CD8:
/* 0A48D8 800A3CD8 27BD0028 */  addiu $sp, $sp, 0x28
/* 0A48DC 800A3CDC 03E00008 */  jr    $ra
/* 0A48E0 800A3CE0 00000000 */   nop   

