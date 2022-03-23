glabel render_magic_codes_list_menu_text
/* 08B16C 8008A56C 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 08B170 8008A570 AFBF004C */  sw    $ra, 0x4c($sp)
/* 08B174 8008A574 AFA40050 */  sw    $a0, 0x50($sp)
/* 08B178 8008A578 AFBE0048 */  sw    $fp, 0x48($sp)
/* 08B17C 8008A57C AFB70044 */  sw    $s7, 0x44($sp)
/* 08B180 8008A580 AFB60040 */  sw    $s6, 0x40($sp)
/* 08B184 8008A584 AFB5003C */  sw    $s5, 0x3c($sp)
/* 08B188 8008A588 AFB40038 */  sw    $s4, 0x38($sp)
/* 08B18C 8008A58C AFB30034 */  sw    $s3, 0x34($sp)
/* 08B190 8008A590 AFB20030 */  sw    $s2, 0x30($sp)
/* 08B194 8008A594 AFB1002C */  sw    $s1, 0x2c($sp)
/* 08B198 8008A598 AFB00028 */  sw    $s0, 0x28($sp)
/* 08B19C 8008A59C 00002025 */  move  $a0, $zero
/* 08B1A0 8008A5A0 00002825 */  move  $a1, $zero
/* 08B1A4 8008A5A4 00003025 */  move  $a2, $zero
/* 08B1A8 8008A5A8 0C0310F3 */  jal   set_text_background_colour
/* 08B1AC 8008A5AC 00003825 */   move  $a3, $zero
/* 08B1B0 8008A5B0 0C0310BB */  jal   set_text_font
/* 08B1B4 8008A5B4 24040002 */   li    $a0, 2
/* 08B1B8 8008A5B8 240E0080 */  li    $t6, 128
/* 08B1BC 8008A5BC AFAE0010 */  sw    $t6, 0x10($sp)
/* 08B1C0 8008A5C0 00002025 */  move  $a0, $zero
/* 08B1C4 8008A5C4 00002825 */  move  $a1, $zero
/* 08B1C8 8008A5C8 00003025 */  move  $a2, $zero
/* 08B1CC 8008A5CC 0C0310E1 */  jal   set_text_colour
/* 08B1D0 8008A5D0 240700FF */   li    $a3, 255
/* 08B1D4 8008A5D4 3C17800E */  lui   $s7, %hi(gMenuText) # $s7, 0x800e
/* 08B1D8 8008A5D8 26F7F4A0 */  addiu $s7, %lo(gMenuText) # addiu $s7, $s7, -0xb60
/* 08B1DC 8008A5DC 8EEF0000 */  lw    $t7, ($s7)
/* 08B1E0 8008A5E0 3C158012 */  lui   $s5, %hi(sMenuCurrDisplayList) # $s5, 0x8012
/* 08B1E4 8008A5E4 26B563A0 */  addiu $s5, %lo(sMenuCurrDisplayList) # addiu $s5, $s5, 0x63a0
/* 08B1E8 8008A5E8 2418000C */  li    $t8, 12
/* 08B1EC 8008A5EC 8DE70050 */  lw    $a3, 0x50($t7)
/* 08B1F0 8008A5F0 AFB80010 */  sw    $t8, 0x10($sp)
/* 08B1F4 8008A5F4 02A02025 */  move  $a0, $s5
/* 08B1F8 8008A5F8 240500A1 */  li    $a1, 161
/* 08B1FC 8008A5FC 0C031110 */  jal   draw_text
/* 08B200 8008A600 24060023 */   li    $a2, 35
/* 08B204 8008A604 241900FF */  li    $t9, 255
/* 08B208 8008A608 AFB90010 */  sw    $t9, 0x10($sp)
/* 08B20C 8008A60C 240400FF */  li    $a0, 255
/* 08B210 8008A610 240500FF */  li    $a1, 255
/* 08B214 8008A614 240600FF */  li    $a2, 255
/* 08B218 8008A618 0C0310E1 */  jal   set_text_colour
/* 08B21C 8008A61C 00003825 */   move  $a3, $zero
/* 08B220 8008A620 8EE80000 */  lw    $t0, ($s7)
/* 08B224 8008A624 2409000C */  li    $t1, 12
/* 08B228 8008A628 8D070050 */  lw    $a3, 0x50($t0)
/* 08B22C 8008A62C AFA90010 */  sw    $t1, 0x10($sp)
/* 08B230 8008A630 02A02025 */  move  $a0, $s5
/* 08B234 8008A634 240500A0 */  li    $a1, 160
/* 08B238 8008A638 0C031110 */  jal   draw_text
/* 08B23C 8008A63C 24060020 */   li    $a2, 32
/* 08B240 8008A640 3C03800E */  lui   $v1, %hi(gUnlockedMagicCodes) # $v1, 0x800e
/* 08B244 8008A644 3C048012 */  lui   $a0, %hi(D_80126C80) # $a0, 0x8012
/* 08B248 8008A648 8C63FD9C */  lw    $v1, %lo(gUnlockedMagicCodes)($v1)
/* 08B24C 8008A64C 24846C80 */  addiu $a0, %lo(D_80126C80) # addiu $a0, $a0, 0x6c80
/* 08B250 8008A650 00008025 */  move  $s0, $zero
/* 08B254 8008A654 24020001 */  li    $v0, 1
/* 08B258 8008A658 00009825 */  move  $s3, $zero
.L8008A65C:
/* 08B25C 8008A65C 00435024 */  and   $t2, $v0, $v1
/* 08B260 8008A660 11400005 */  beqz  $t2, .L8008A678
/* 08B264 8008A664 00026840 */   sll   $t5, $v0, 1
/* 08B268 8008A668 00135840 */  sll   $t3, $s3, 1
/* 08B26C 8008A66C 008B6021 */  addu  $t4, $a0, $t3
/* 08B270 8008A670 A5900000 */  sh    $s0, ($t4)
/* 08B274 8008A674 26730001 */  addiu $s3, $s3, 1
.L8008A678:
/* 08B278 8008A678 26100001 */  addiu $s0, $s0, 1
/* 08B27C 8008A67C 2A010020 */  slti  $at, $s0, 0x20
/* 08B280 8008A680 1420FFF6 */  bnez  $at, .L8008A65C
/* 08B284 8008A684 01A01025 */   move  $v0, $t5
/* 08B288 8008A688 3C1E8012 */  lui   $fp, %hi(D_801263BC) # $fp, 0x8012
/* 08B28C 8008A68C 8FDE63BC */  lw    $fp, %lo(D_801263BC)($fp)
/* 08B290 8008A690 24120036 */  li    $s2, 54
/* 08B294 8008A694 001E70C0 */  sll   $t6, $fp, 3
/* 08B298 8008A698 29C10100 */  slti  $at, $t6, 0x100
/* 08B29C 8008A69C 14200003 */  bnez  $at, .L8008A6AC
/* 08B2A0 8008A6A0 01C0F025 */   move  $fp, $t6
/* 08B2A4 8008A6A4 240F01FF */  li    $t7, 511
/* 08B2A8 8008A6A8 01EEF023 */  subu  $fp, $t7, $t6
.L8008A6AC:
/* 08B2AC 8008A6AC 0C0310BB */  jal   set_text_font
/* 08B2B0 8008A6B0 00002025 */   move  $a0, $zero
/* 08B2B4 8008A6B4 241800FF */  li    $t8, 255
/* 08B2B8 8008A6B8 AFB80010 */  sw    $t8, 0x10($sp)
/* 08B2BC 8008A6BC 240400FF */  li    $a0, 255
/* 08B2C0 8008A6C0 240500FF */  li    $a1, 255
/* 08B2C4 8008A6C4 240600FF */  li    $a2, 255
/* 08B2C8 8008A6C8 0C0310E1 */  jal   set_text_colour
/* 08B2CC 8008A6CC 00003825 */   move  $a3, $zero
/* 08B2D0 8008A6D0 3C038012 */  lui   $v1, %hi(D_801263E0) # $v1, 0x8012
/* 08B2D4 8008A6D4 3C198012 */  lui   $t9, %hi(D_80126C70) # $t9, 0x8012
/* 08B2D8 8008A6D8 8F396C70 */  lw    $t9, %lo(D_80126C70)($t9)
/* 08B2DC 8008A6DC 8C6363E0 */  lw    $v1, %lo(D_801263E0)($v1)
/* 08B2E0 8008A6E0 3C168012 */  lui   $s6, %hi(gCheatsAssetData) # $s6, 0x8012
/* 08B2E4 8008A6E4 8ED66C30 */  lw    $s6, %lo(gCheatsAssetData)($s6)
/* 08B2E8 8008A6E8 00791021 */  addu  $v0, $v1, $t9
/* 08B2EC 8008A6EC 0062082A */  slt   $at, $v1, $v0
/* 08B2F0 8008A6F0 00608025 */  move  $s0, $v1
/* 08B2F4 8008A6F4 1020004B */  beqz  $at, .L8008A824
/* 08B2F8 8008A6F8 26D60002 */   addiu $s6, $s6, 2
/* 08B2FC 8008A6FC 0073082A */  slt   $at, $v1, $s3
/* 08B300 8008A700 10200048 */  beqz  $at, .L8008A824
/* 08B304 8008A704 00034040 */   sll   $t0, $v1, 1
/* 08B308 8008A708 3C098012 */  lui   $t1, %hi(D_80126C80) # $t1, 0x8012
/* 08B30C 8008A70C 25296C80 */  addiu $t1, %lo(D_80126C80) # addiu $t1, $t1, 0x6c80
/* 08B310 8008A710 3C148012 */  lui   $s4, %hi(gOptionsMenuItemIndex) # $s4, 0x8012
/* 08B314 8008A714 26946C46 */  addiu $s4, %lo(gOptionsMenuItemIndex) # addiu $s4, $s4, 0x6c46
/* 08B318 8008A718 01098821 */  addu  $s1, $t0, $t1
.L8008A71C:
/* 08B31C 8008A71C 868A0000 */  lh    $t2, ($s4)
/* 08B320 8008A720 240400FF */  li    $a0, 255
/* 08B324 8008A724 160A0006 */  bne   $s0, $t2, .L8008A740
/* 08B328 8008A728 240500FF */   li    $a1, 255
/* 08B32C 8008A72C 240B00FF */  li    $t3, 255
/* 08B330 8008A730 AFAB0010 */  sw    $t3, 0x10($sp)
/* 08B334 8008A734 240600FF */  li    $a2, 255
/* 08B338 8008A738 0C0310E1 */  jal   set_text_colour
/* 08B33C 8008A73C 03C03825 */   move  $a3, $fp
.L8008A740:
/* 08B340 8008A740 862D0000 */  lh    $t5, ($s1)
/* 08B344 8008A744 3C198012 */  lui   $t9, %hi(gCheatsAssetData) # $t9, 0x8012
/* 08B348 8008A748 000D7080 */  sll   $t6, $t5, 2
/* 08B34C 8008A74C 02CE7821 */  addu  $t7, $s6, $t6
/* 08B350 8008A750 95F80002 */  lhu   $t8, 2($t7)
/* 08B354 8008A754 8F396C30 */  lw    $t9, %lo(gCheatsAssetData)($t9)
/* 08B358 8008A758 AFA00010 */  sw    $zero, 0x10($sp)
/* 08B35C 8008A75C 02A02025 */  move  $a0, $s5
/* 08B360 8008A760 24050030 */  li    $a1, 48
/* 08B364 8008A764 02403025 */  move  $a2, $s2
/* 08B368 8008A768 0C031110 */  jal   draw_text
/* 08B36C 8008A76C 03193821 */   addu  $a3, $t8, $t9
/* 08B370 8008A770 86280000 */  lh    $t0, ($s1)
/* 08B374 8008A774 3C0B800E */  lui   $t3, %hi(gActiveMagicCodes) # $t3, 0x800e
/* 08B378 8008A778 8D6BFD98 */  lw    $t3, %lo(gActiveMagicCodes)($t3)
/* 08B37C 8008A77C 24090001 */  li    $t1, 1
/* 08B380 8008A780 01095004 */  sllv  $t2, $t1, $t0
/* 08B384 8008A784 014B6024 */  and   $t4, $t2, $t3
/* 08B388 8008A788 1180000A */  beqz  $t4, .L8008A7B4
/* 08B38C 8008A78C 02A02025 */   move  $a0, $s5
/* 08B390 8008A790 8EED0000 */  lw    $t5, ($s7)
/* 08B394 8008A794 02A02025 */  move  $a0, $s5
/* 08B398 8008A798 8DA70054 */  lw    $a3, 0x54($t5)
/* 08B39C 8008A79C AFA00010 */  sw    $zero, 0x10($sp)
/* 08B3A0 8008A7A0 24050100 */  li    $a1, 256
/* 08B3A4 8008A7A4 0C031110 */  jal   draw_text
/* 08B3A8 8008A7A8 02403025 */   move  $a2, $s2
/* 08B3AC 8008A7AC 10000008 */  b     .L8008A7D0
/* 08B3B0 8008A7B0 868F0000 */   lh    $t7, ($s4)
.L8008A7B4:
/* 08B3B4 8008A7B4 8EEE0000 */  lw    $t6, ($s7)
/* 08B3B8 8008A7B8 24050100 */  li    $a1, 256
/* 08B3BC 8008A7BC 8DC70058 */  lw    $a3, 0x58($t6)
/* 08B3C0 8008A7C0 AFA00010 */  sw    $zero, 0x10($sp)
/* 08B3C4 8008A7C4 0C031110 */  jal   draw_text
/* 08B3C8 8008A7C8 02403025 */   move  $a2, $s2
/* 08B3CC 8008A7CC 868F0000 */  lh    $t7, ($s4)
.L8008A7D0:
/* 08B3D0 8008A7D0 240400FF */  li    $a0, 255
/* 08B3D4 8008A7D4 160F0006 */  bne   $s0, $t7, .L8008A7F0
/* 08B3D8 8008A7D8 240500FF */   li    $a1, 255
/* 08B3DC 8008A7DC 241800FF */  li    $t8, 255
/* 08B3E0 8008A7E0 AFB80010 */  sw    $t8, 0x10($sp)
/* 08B3E4 8008A7E4 240600FF */  li    $a2, 255
/* 08B3E8 8008A7E8 0C0310E1 */  jal   set_text_colour
/* 08B3EC 8008A7EC 00003825 */   move  $a3, $zero
.L8008A7F0:
/* 08B3F0 8008A7F0 3C198012 */  lui   $t9, %hi(D_801263E0) # $t9, 0x8012
/* 08B3F4 8008A7F4 3C098012 */  lui   $t1, %hi(D_80126C70) # $t1, 0x8012
/* 08B3F8 8008A7F8 8D296C70 */  lw    $t1, %lo(D_80126C70)($t1)
/* 08B3FC 8008A7FC 8F3963E0 */  lw    $t9, %lo(D_801263E0)($t9)
/* 08B400 8008A800 26100001 */  addiu $s0, $s0, 1
/* 08B404 8008A804 03291021 */  addu  $v0, $t9, $t1
/* 08B408 8008A808 0202082A */  slt   $at, $s0, $v0
/* 08B40C 8008A80C 26310002 */  addiu $s1, $s1, 2
/* 08B410 8008A810 10200004 */  beqz  $at, .L8008A824
/* 08B414 8008A814 26520010 */   addiu $s2, $s2, 0x10
/* 08B418 8008A818 0213082A */  slt   $at, $s0, $s3
/* 08B41C 8008A81C 1420FFBF */  bnez  $at, .L8008A71C
/* 08B420 8008A820 00000000 */   nop   
.L8008A824:
/* 08B424 8008A824 3C148012 */  lui   $s4, %hi(gOptionsMenuItemIndex) # $s4, 0x8012
/* 08B428 8008A828 0202082A */  slt   $at, $s0, $v0
/* 08B42C 8008A82C 10200014 */  beqz  $at, .L8008A880
/* 08B430 8008A830 26946C46 */   addiu $s4, %lo(gOptionsMenuItemIndex) # addiu $s4, $s4, 0x6c46
/* 08B434 8008A834 86880000 */  lh    $t0, ($s4)
/* 08B438 8008A838 240400FF */  li    $a0, 255
/* 08B43C 8008A83C 16680006 */  bne   $s3, $t0, .L8008A858
/* 08B440 8008A840 240500FF */   li    $a1, 255
/* 08B444 8008A844 240A00FF */  li    $t2, 255
/* 08B448 8008A848 AFAA0010 */  sw    $t2, 0x10($sp)
/* 08B44C 8008A84C 240600FF */  li    $a2, 255
/* 08B450 8008A850 0C0310E1 */  jal   set_text_colour
/* 08B454 8008A854 03C03825 */   move  $a3, $fp
.L8008A858:
/* 08B458 8008A858 8EEB0000 */  lw    $t3, ($s7)
/* 08B45C 8008A85C 240C0004 */  li    $t4, 4
/* 08B460 8008A860 8D670014 */  lw    $a3, 0x14($t3)
/* 08B464 8008A864 AFAC0010 */  sw    $t4, 0x10($sp)
/* 08B468 8008A868 02A02025 */  move  $a0, $s5
/* 08B46C 8008A86C 24058000 */  li    $a1, -32768
/* 08B470 8008A870 0C031110 */  jal   draw_text
/* 08B474 8008A874 02403025 */   move  $a2, $s2
/* 08B478 8008A878 10000014 */  b     .L8008A8CC
/* 08B47C 8008A87C 8FBF004C */   lw    $ra, 0x4c($sp)
.L8008A880:
/* 08B480 8008A880 3C0D8012 */  lui   $t5, %hi(D_801263BC) # $t5, 0x8012
/* 08B484 8008A884 8DAD63BC */  lw    $t5, %lo(D_801263BC)($t5)
/* 08B488 8008A888 02A02025 */  move  $a0, $s5
/* 08B48C 8008A88C 31AE0008 */  andi  $t6, $t5, 8
/* 08B490 8008A890 11C0000D */  beqz  $t6, .L8008A8C8
/* 08B494 8008A894 3C05800E */   lui   $a1, %hi(D_800E043C) # $a1, 0x800e
/* 08B498 8008A898 240F00FF */  li    $t7, 255
/* 08B49C 8008A89C 241800FF */  li    $t8, 255
/* 08B4A0 8008A8A0 241900FF */  li    $t9, 255
/* 08B4A4 8008A8A4 240900FF */  li    $t1, 255
/* 08B4A8 8008A8A8 AFA9001C */  sw    $t1, 0x1c($sp)
/* 08B4AC 8008A8AC AFB90018 */  sw    $t9, 0x18($sp)
/* 08B4B0 8008A8B0 AFB80014 */  sw    $t8, 0x14($sp)
/* 08B4B4 8008A8B4 AFAF0010 */  sw    $t7, 0x10($sp)
/* 08B4B8 8008A8B8 24A5043C */  addiu $a1, %lo(D_800E043C) # addiu $a1, $a1, 0x43c
/* 08B4BC 8008A8BC 240600A0 */  li    $a2, 160
/* 08B4C0 8008A8C0 0C01E2AE */  jal   render_textured_rectangle
/* 08B4C4 8008A8C4 26470008 */   addiu $a3, $s2, 8
.L8008A8C8:
/* 08B4C8 8008A8C8 8FBF004C */  lw    $ra, 0x4c($sp)
.L8008A8CC:
/* 08B4CC 8008A8CC 8FB00028 */  lw    $s0, 0x28($sp)
/* 08B4D0 8008A8D0 8FB1002C */  lw    $s1, 0x2c($sp)
/* 08B4D4 8008A8D4 8FB20030 */  lw    $s2, 0x30($sp)
/* 08B4D8 8008A8D8 8FB30034 */  lw    $s3, 0x34($sp)
/* 08B4DC 8008A8DC 8FB40038 */  lw    $s4, 0x38($sp)
/* 08B4E0 8008A8E0 8FB5003C */  lw    $s5, 0x3c($sp)
/* 08B4E4 8008A8E4 8FB60040 */  lw    $s6, 0x40($sp)
/* 08B4E8 8008A8E8 8FB70044 */  lw    $s7, 0x44($sp)
/* 08B4EC 8008A8EC 8FBE0048 */  lw    $fp, 0x48($sp)
/* 08B4F0 8008A8F0 03E00008 */  jr    $ra
/* 08B4F4 8008A8F4 27BD0050 */   addiu $sp, $sp, 0x50

