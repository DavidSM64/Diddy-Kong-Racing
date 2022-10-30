glabel func_800A497C
/* 0A557C 800A497C 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0A5580 800A4980 3C028012 */  lui   $v0, %hi(D_80126CDC) # $v0, 0x8012
/* 0A5584 800A4984 8C426CDC */  lw    $v0, %lo(D_80126CDC)($v0)
/* 0A5588 800A4988 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0A558C 800A498C AFB00018 */  sw    $s0, 0x18($sp)
/* 0A5590 800A4990 AFA40030 */  sw    $a0, 0x30($sp)
/* 0A5594 800A4994 A3A00027 */  sb    $zero, 0x27($sp)
/* 0A5598 800A4998 24470700 */  addiu $a3, $v0, 0x700
/* 0A559C 800A499C 80E3001A */  lb    $v1, 0x1a($a3)
/* 0A55A0 800A49A0 24040018 */  li    $a0, 24
/* 0A55A4 800A49A4 1060000B */  beqz  $v1, .L800A49D4
/* 0A55A8 800A49A8 24500740 */   addiu $s0, $v0, 0x740
/* 0A55AC 800A49AC 24010001 */  li    $at, 1
/* 0A55B0 800A49B0 1061001F */  beq   $v1, $at, .L800A4A30
/* 0A55B4 800A49B4 24020002 */   li    $v0, 2
/* 0A55B8 800A49B8 1062005F */  beq   $v1, $v0, .L800A4B38
/* 0A55BC 800A49BC 00055880 */   sll   $t3, $a1, 2
/* 0A55C0 800A49C0 24020003 */  li    $v0, 3
/* 0A55C4 800A49C4 10620074 */  beq   $v1, $v0, .L800A4B98
/* 0A55C8 800A49C8 00000000 */   nop   
/* 0A55CC 800A49CC 10000074 */  b     .L800A4BA0
/* 0A55D0 800A49D0 83AD0027 */   lb    $t5, 0x27($sp)
.L800A49D4:
/* 0A55D4 800A49D4 0C0002F8 */  jal   set_music_player_voice_limit
/* 0A55D8 800A49D8 AFA7002C */   sw    $a3, 0x2c($sp)
/* 0A55DC 800A49DC 0C0002CD */  jal   play_music
/* 0A55E0 800A49E0 24040019 */   li    $a0, 25
/* 0A55E4 800A49E4 24040016 */  li    $a0, 22
/* 0A55E8 800A49E8 0C000741 */  jal   play_sound_global
/* 0A55EC 800A49EC 00002825 */   move  $a1, $zero
/* 0A55F0 800A49F0 3C058012 */  lui   $a1, %hi(gHUDVoiceSoundMask) # $a1, 0x8012
/* 0A55F4 800A49F4 24A56D40 */  addiu $a1, %lo(gHUDVoiceSoundMask) # addiu $a1, $a1, 0x6d40
/* 0A55F8 800A49F8 0C000741 */  jal   play_sound_global
/* 0A55FC 800A49FC 24040102 */   li    $a0, 258
/* 0A5600 800A4A00 3C02800E */  lui   $v0, %hi(D_800E2770) # $v0, 0x800e
/* 0A5604 800A4A04 24422770 */  addiu $v0, %lo(D_800E2770) # addiu $v0, $v0, 0x2770
/* 0A5608 800A4A08 8FAF0030 */  lw    $t7, 0x30($sp)
/* 0A560C 800A4A0C 240E007F */  li    $t6, 127
/* 0A5610 800A4A10 A04E0002 */  sb    $t6, 2($v0)
/* 0A5614 800A4A14 A0400003 */  sb    $zero, 3($v0)
/* 0A5618 800A4A18 85F80000 */  lh    $t8, ($t7)
/* 0A561C 800A4A1C 8FA7002C */  lw    $a3, 0x2c($sp)
/* 0A5620 800A4A20 24190001 */  li    $t9, 1
/* 0A5624 800A4A24 A058000C */  sb    $t8, 0xc($v0)
/* 0A5628 800A4A28 1000005C */  b     .L800A4B9C
/* 0A562C 800A4A2C A0F9001A */   sb    $t9, 0x1a($a3)
.L800A4A30:
/* 0A5630 800A4A30 00054080 */  sll   $t0, $a1, 2
/* 0A5634 800A4A34 01054023 */  subu  $t0, $t0, $a1
/* 0A5638 800A4A38 00084080 */  sll   $t0, $t0, 2
/* 0A563C 800A4A3C 01054021 */  addu  $t0, $t0, $a1
/* 0A5640 800A4A40 44882000 */  mtc1  $t0, $f4
/* 0A5644 800A4A44 C4E6000C */  lwc1  $f6, 0xc($a3)
/* 0A5648 800A4A48 46802020 */  cvt.s.w $f0, $f4
/* 0A564C 800A4A4C 3C01C1B8 */  li    $at, 0xC1B80000 # -23.000000
/* 0A5650 800A4A50 44811000 */  mtc1  $at, $f2
/* 0A5654 800A4A54 46003200 */  add.s $f8, $f6, $f0
/* 0A5658 800A4A58 E4E8000C */  swc1  $f8, 0xc($a3)
/* 0A565C 800A4A5C C4EA000C */  lwc1  $f10, 0xc($a3)
/* 0A5660 800A4A60 00000000 */  nop   
/* 0A5664 800A4A64 460A103C */  c.lt.s $f2, $f10
/* 0A5668 800A4A68 00000000 */  nop   
/* 0A566C 800A4A6C 45000002 */  bc1f  .L800A4A78
/* 0A5670 800A4A70 00000000 */   nop   
/* 0A5674 800A4A74 E4E2000C */  swc1  $f2, 0xc($a3)
.L800A4A78:
/* 0A5678 800A4A78 C610000C */  lwc1  $f16, 0xc($s0)
/* 0A567C 800A4A7C 3C0141B0 */  li    $at, 0x41B00000 # 22.000000
/* 0A5680 800A4A80 46008481 */  sub.s $f18, $f16, $f0
/* 0A5684 800A4A84 44816000 */  mtc1  $at, $f12
/* 0A5688 800A4A88 E612000C */  swc1  $f18, 0xc($s0)
/* 0A568C 800A4A8C C602000C */  lwc1  $f2, 0xc($s0)
/* 0A5690 800A4A90 00000000 */  nop   
/* 0A5694 800A4A94 460C103C */  c.lt.s $f2, $f12
/* 0A5698 800A4A98 00000000 */  nop   
/* 0A569C 800A4A9C 45000004 */  bc1f  .L800A4AB0
/* 0A56A0 800A4AA0 00000000 */   nop   
/* 0A56A4 800A4AA4 E60C000C */  swc1  $f12, 0xc($s0)
/* 0A56A8 800A4AA8 C602000C */  lwc1  $f2, 0xc($s0)
/* 0A56AC 800A4AAC 00000000 */  nop   
.L800A4AB0:
/* 0A56B0 800A4AB0 46026032 */  c.eq.s $f12, $f2
/* 0A56B4 800A4AB4 24090001 */  li    $t1, 1
/* 0A56B8 800A4AB8 45000038 */  bc1f  .L800A4B9C
/* 0A56BC 800A4ABC A3A90027 */   sb    $t1, 0x27($sp)
/* 0A56C0 800A4AC0 80EA001B */  lb    $t2, 0x1b($a3)
/* 0A56C4 800A4AC4 240DFF88 */  li    $t5, -120
/* 0A56C8 800A4AC8 01455821 */  addu  $t3, $t2, $a1
/* 0A56CC 800A4ACC A0EB001B */  sb    $t3, 0x1b($a3)
/* 0A56D0 800A4AD0 80EC001B */  lb    $t4, 0x1b($a3)
/* 0A56D4 800A4AD4 00002825 */  move  $a1, $zero
/* 0A56D8 800A4AD8 29810078 */  slti  $at, $t4, 0x78
/* 0A56DC 800A4ADC 14200005 */  bnez  $at, .L800A4AF4
/* 0A56E0 800A4AE0 24040016 */   li    $a0, 22
/* 0A56E4 800A4AE4 80EE001C */  lb    $t6, 0x1c($a3)
/* 0A56E8 800A4AE8 A0ED001B */  sb    $t5, 0x1b($a3)
/* 0A56EC 800A4AEC 25CF0001 */  addiu $t7, $t6, 1
/* 0A56F0 800A4AF0 A0EF001C */  sb    $t7, 0x1c($a3)
.L800A4AF4:
/* 0A56F4 800A4AF4 80F8001C */  lb    $t8, 0x1c($a3)
/* 0A56F8 800A4AF8 24020002 */  li    $v0, 2
/* 0A56FC 800A4AFC 14580028 */  bne   $v0, $t8, .L800A4BA0
/* 0A5700 800A4B00 83AD0027 */   lb    $t5, 0x27($sp)
/* 0A5704 800A4B04 A0E2001A */  sb    $v0, 0x1a($a3)
/* 0A5708 800A4B08 0C000741 */  jal   play_sound_global
/* 0A570C 800A4B0C AFA7002C */   sw    $a3, 0x2c($sp)
/* 0A5710 800A4B10 8FB90030 */  lw    $t9, 0x30($sp)
/* 0A5714 800A4B14 3C02800E */  lui   $v0, %hi(D_800E2770) # $v0, 0x800e
/* 0A5718 800A4B18 24422770 */  addiu $v0, %lo(D_800E2770) # addiu $v0, $v0, 0x2770
/* 0A571C 800A4B1C 8049000C */  lb    $t1, 0xc($v0)
/* 0A5720 800A4B20 87280000 */  lh    $t0, ($t9)
/* 0A5724 800A4B24 8FA7002C */  lw    $a3, 0x2c($sp)
/* 0A5728 800A4B28 1509001C */  bne   $t0, $t1, .L800A4B9C
/* 0A572C 800A4B2C 240AFFFF */   li    $t2, -1
/* 0A5730 800A4B30 1000001A */  b     .L800A4B9C
/* 0A5734 800A4B34 A04A0003 */   sb    $t2, 3($v0)
.L800A4B38:
/* 0A5738 800A4B38 01655823 */  subu  $t3, $t3, $a1
/* 0A573C 800A4B3C 000B5880 */  sll   $t3, $t3, 2
/* 0A5740 800A4B40 01655821 */  addu  $t3, $t3, $a1
/* 0A5744 800A4B44 448B2000 */  mtc1  $t3, $f4
/* 0A5748 800A4B48 C4E6000C */  lwc1  $f6, 0xc($a3)
/* 0A574C 800A4B4C 46802020 */  cvt.s.w $f0, $f4
/* 0A5750 800A4B50 240C0001 */  li    $t4, 1
/* 0A5754 800A4B54 3C014348 */  li    $at, 0x43480000 # 200.000000
/* 0A5758 800A4B58 46003200 */  add.s $f8, $f6, $f0
/* 0A575C 800A4B5C 44819000 */  mtc1  $at, $f18
/* 0A5760 800A4B60 E4E8000C */  swc1  $f8, 0xc($a3)
/* 0A5764 800A4B64 C60A000C */  lwc1  $f10, 0xc($s0)
/* 0A5768 800A4B68 24020003 */  li    $v0, 3
/* 0A576C 800A4B6C 46005400 */  add.s $f16, $f10, $f0
/* 0A5770 800A4B70 E610000C */  swc1  $f16, 0xc($s0)
/* 0A5774 800A4B74 A3AC0027 */  sb    $t4, 0x27($sp)
/* 0A5778 800A4B78 C4E4000C */  lwc1  $f4, 0xc($a3)
/* 0A577C 800A4B7C 00000000 */  nop   
/* 0A5780 800A4B80 4604903C */  c.lt.s $f18, $f4
/* 0A5784 800A4B84 00000000 */  nop   
/* 0A5788 800A4B88 45000005 */  bc1f  .L800A4BA0
/* 0A578C 800A4B8C 83AD0027 */   lb    $t5, 0x27($sp)
/* 0A5790 800A4B90 10000002 */  b     .L800A4B9C
/* 0A5794 800A4B94 A0E2001A */   sb    $v0, 0x1a($a3)
.L800A4B98:
/* 0A5798 800A4B98 A0E2001A */  sb    $v0, 0x1a($a3)
.L800A4B9C:
/* 0A579C 800A4B9C 83AD0027 */  lb    $t5, 0x27($sp)
.L800A4BA0:
/* 0A57A0 800A4BA0 00000000 */  nop   
/* 0A57A4 800A4BA4 11A0001F */  beqz  $t5, .L800A4C24
/* 0A57A8 800A4BA8 3C048012 */   lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A57AC 800A4BAC 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A57B0 800A4BB0 8C830000 */  lw    $v1, ($a0)
/* 0A57B4 800A4BB4 3C0FFA00 */  lui   $t7, 0xfa00
/* 0A57B8 800A4BB8 246E0008 */  addiu $t6, $v1, 8
/* 0A57BC 800A4BBC AC8E0000 */  sw    $t6, ($a0)
/* 0A57C0 800A4BC0 2418FFD2 */  li    $t8, -46
/* 0A57C4 800A4BC4 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A57C8 800A4BC8 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A57CC 800A4BCC 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A57D0 800A4BD0 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A57D4 800A4BD4 AC780004 */  sw    $t8, 4($v1)
/* 0A57D8 800A4BD8 0C02A980 */  jal   func_800AA600
/* 0A57DC 800A4BDC AC6F0000 */   sw    $t7, ($v1)
/* 0A57E0 800A4BE0 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A57E4 800A4BE4 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A57E8 800A4BE8 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A57EC 800A4BEC 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A57F0 800A4BF0 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A57F4 800A4BF4 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A57F8 800A4BF8 0C02A980 */  jal   func_800AA600
/* 0A57FC 800A4BFC 02003825 */   move  $a3, $s0
/* 0A5800 800A4C00 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A5804 800A4C04 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A5808 800A4C08 8C830000 */  lw    $v1, ($a0)
/* 0A580C 800A4C0C 3C08FA00 */  lui   $t0, 0xfa00
/* 0A5810 800A4C10 24790008 */  addiu $t9, $v1, 8
/* 0A5814 800A4C14 AC990000 */  sw    $t9, ($a0)
/* 0A5818 800A4C18 2409FFFF */  li    $t1, -1
/* 0A581C 800A4C1C AC690004 */  sw    $t1, 4($v1)
/* 0A5820 800A4C20 AC680000 */  sw    $t0, ($v1)
.L800A4C24:
/* 0A5824 800A4C24 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0A5828 800A4C28 8FB00018 */  lw    $s0, 0x18($sp)
/* 0A582C 800A4C2C 03E00008 */  jr    $ra
/* 0A5830 800A4C30 27BD0030 */   addiu $sp, $sp, 0x30

