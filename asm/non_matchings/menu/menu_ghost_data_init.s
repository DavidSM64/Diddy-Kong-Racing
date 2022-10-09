glabel menu_ghost_data_init
/* 09A65C 80099A5C 27BDFF88 */  addiu $sp, $sp, -0x78
/* 09A660 80099A60 3C048012 */  lui   $a0, %hi(D_801264D0) # $a0, 0x8012
/* 09A664 80099A64 3C0E8012 */  lui   $t6, %hi(D_801264F8) # $t6, 0x8012
/* 09A668 80099A68 AFBF0044 */  sw    $ra, 0x44($sp)
/* 09A66C 80099A6C 25CE64F8 */  addiu $t6, %lo(D_801264F8) # addiu $t6, $t6, 0x64f8
/* 09A670 80099A70 8C8464D0 */  lw    $a0, %lo(D_801264D0)($a0)
/* 09A674 80099A74 3C058012 */  lui   $a1, %hi(D_801264DC) # $a1, 0x8012
/* 09A678 80099A78 3C068012 */  lui   $a2, %hi(D_801264EC) # $a2, 0x8012
/* 09A67C 80099A7C 3C078012 */  lui   $a3, %hi(D_801264E4) # $a3, 0x8012
/* 09A680 80099A80 AFBE0040 */  sw    $fp, 0x40($sp)
/* 09A684 80099A84 AFB7003C */  sw    $s7, 0x3c($sp)
/* 09A688 80099A88 AFB60038 */  sw    $s6, 0x38($sp)
/* 09A68C 80099A8C AFB50034 */  sw    $s5, 0x34($sp)
/* 09A690 80099A90 AFB40030 */  sw    $s4, 0x30($sp)
/* 09A694 80099A94 AFB3002C */  sw    $s3, 0x2c($sp)
/* 09A698 80099A98 AFB20028 */  sw    $s2, 0x28($sp)
/* 09A69C 80099A9C AFB10024 */  sw    $s1, 0x24($sp)
/* 09A6A0 80099AA0 AFB00020 */  sw    $s0, 0x20($sp)
/* 09A6A4 80099AA4 24E764E4 */  addiu $a3, %lo(D_801264E4) # addiu $a3, $a3, 0x64e4
/* 09A6A8 80099AA8 24C664EC */  addiu $a2, %lo(D_801264EC) # addiu $a2, $a2, 0x64ec
/* 09A6AC 80099AAC 24A564DC */  addiu $a1, %lo(D_801264DC) # addiu $a1, $a1, 0x64dc
/* 09A6B0 80099AB0 0C01D5B5 */  jal   func_800756D4
/* 09A6B4 80099AB4 AFAE0010 */   sw    $t6, 0x10($sp)
/* 09A6B8 80099AB8 14400003 */  bnez  $v0, .L80099AC8
/* 09A6BC 80099ABC AFA20070 */   sw    $v0, 0x70($sp)
/* 09A6C0 80099AC0 0C02658F */  jal   func_8009963C
/* 09A6C4 80099AC4 00000000 */   nop   
.L80099AC8:
/* 09A6C8 80099AC8 3C04800E */  lui   $a0, %hi(D_800E1708) # $a0, 0x800e
/* 09A6CC 80099ACC 0C02719D */  jal   func_8009C674
/* 09A6D0 80099AD0 24841708 */   addiu $a0, %lo(D_800E1708) # addiu $a0, $a0, 0x1708
/* 09A6D4 80099AD4 3C04800E */  lui   $a0, %hi(D_800E174C) # $a0, 0x800e
/* 09A6D8 80099AD8 0C027229 */  jal   allocate_menu_images
/* 09A6DC 80099ADC 2484174C */   addiu $a0, %lo(D_800E174C) # addiu $a0, $a0, 0x174c
/* 09A6E0 80099AE0 0C03105C */  jal   load_font
/* 09A6E4 80099AE4 24040002 */   li    $a0, 2
/* 09A6E8 80099AE8 3C028012 */  lui   $v0, %hi(D_80126550) # $v0, 0x8012
/* 09A6EC 80099AEC 24426550 */  addiu $v0, %lo(D_80126550) # addiu $v0, $v0, 0x6550
/* 09A6F0 80099AF0 8C570038 */  lw    $s7, 0x38($v0)
/* 09A6F4 80099AF4 3C01800E */  lui   $at, %hi(D_800E153C) # $at, 0x800e
/* 09A6F8 80099AF8 AC37153C */  sw    $s7, %lo(D_800E153C)($at)
/* 09A6FC 80099AFC 8C5E003C */  lw    $fp, 0x3c($v0)
/* 09A700 80099B00 3C01800E */  lui   $at, %hi(D_800E153C+0x28) # $at, 0x800e
/* 09A704 80099B04 AC3E1564 */  sw    $fp, %lo(D_800E153C+0x28)($at)
/* 09A708 80099B08 8C430040 */  lw    $v1, 0x40($v0)
/* 09A70C 80099B0C 3C01800E */  lui   $at, %hi(D_800E1594) # $at, 0x800e
/* 09A710 80099B10 AC231594 */  sw    $v1, %lo(D_800E1594)($at)
/* 09A714 80099B14 8C440044 */  lw    $a0, 0x44($v0)
/* 09A718 80099B18 3C01800E */  lui   $at, %hi(D_800E1594+0x28) # $at, 0x800e
/* 09A71C 80099B1C AC2415BC */  sw    $a0, %lo(D_800E1594+0x28)($at)
/* 09A720 80099B20 8C450048 */  lw    $a1, 0x48($v0)
/* 09A724 80099B24 3C01800E */  lui   $at, %hi(D_800E15EC) # $at, 0x800e
/* 09A728 80099B28 AC2515EC */  sw    $a1, %lo(D_800E15EC)($at)
/* 09A72C 80099B2C 8C46004C */  lw    $a2, 0x4c($v0)
/* 09A730 80099B30 3C01800E */  lui   $at, %hi(D_800E15EC+0x28) # $at, 0x800e
/* 09A734 80099B34 AC261614 */  sw    $a2, %lo(D_800E15EC+0x28)($at)
/* 09A738 80099B38 8C470050 */  lw    $a3, 0x50($v0)
/* 09A73C 80099B3C 3C01800E */  lui   $at, %hi(D_800E1644) # $at, 0x800e
/* 09A740 80099B40 AC271644 */  sw    $a3, %lo(D_800E1644)($at)
/* 09A744 80099B44 8C490054 */  lw    $t1, 0x54($v0)
/* 09A748 80099B48 3C01800E */  lui   $at, %hi(D_800E1644+0x28) # $at, 0x800e
/* 09A74C 80099B4C AC29166C */  sw    $t1, %lo(D_800E1644+0x28)($at)
/* 09A750 80099B50 8C4A0058 */  lw    $t2, 0x58($v0)
/* 09A754 80099B54 3C01800E */  lui   $at, %hi(D_800E169C) # $at, 0x800e
/* 09A758 80099B58 24080001 */  li    $t0, 1
/* 09A75C 80099B5C AFA60058 */  sw    $a2, 0x58($sp)
/* 09A760 80099B60 AC2A169C */  sw    $t2, %lo(D_800E169C)($at)
/* 09A764 80099B64 AFAA004C */  sw    $t2, 0x4c($sp)
/* 09A768 80099B68 24060005 */  li    $a2, 5
/* 09A76C 80099B6C 310A0001 */  andi  $t2, $t0, 1
/* 09A770 80099B70 01460019 */  multu $t2, $a2
/* 09A774 80099B74 8C4B005C */  lw    $t3, 0x5c($v0)
/* 09A778 80099B78 3C01800E */  lui   $at, %hi(D_800E169C+0x28) # $at, 0x800e
/* 09A77C 80099B7C AC2B16C4 */  sw    $t3, %lo(D_800E169C+0x28)($at)
/* 09A780 80099B80 AFAB0048 */  sw    $t3, 0x48($sp)
/* 09A784 80099B84 3C0F800E */  lui   $t7, %hi(D_800E153C) # $t7, 0x800e
/* 09A788 80099B88 AFA5005C */  sw    $a1, 0x5c($sp)
/* 09A78C 80099B8C AFA90050 */  sw    $t1, 0x50($sp)
/* 09A790 80099B90 3C05800E */  lui   $a1, %hi(D_800E1594) # $a1, 0x800e
/* 09A794 80099B94 000848C0 */  sll   $t1, $t0, 3
/* 09A798 80099B98 25EF153C */  addiu $t7, %lo(D_800E153C) # addiu $t7, $t7, 0x153c
/* 09A79C 80099B9C 24A51594 */  addiu $a1, %lo(D_800E1594) # addiu $a1, $a1, 0x1594
/* 09A7A0 80099BA0 0000C012 */  mflo  $t8
/* 09A7A4 80099BA4 01185821 */  addu  $t3, $t0, $t8
/* 09A7A8 80099BA8 39580001 */  xori  $t8, $t2, 1
/* 09A7AC 80099BAC 03060019 */  multu $t8, $a2
/* 09A7B0 80099BB0 000BC8C0 */  sll   $t9, $t3, 3
/* 09A7B4 80099BB4 012F1021 */  addu  $v0, $t1, $t7
/* 09A7B8 80099BB8 00B97821 */  addu  $t7, $a1, $t9
/* 09A7BC 80099BBC 03205825 */  move  $t3, $t9
/* 09A7C0 80099BC0 ADE30000 */  sw    $v1, ($t7)
/* 09A7C4 80099BC4 AFA30064 */  sw    $v1, 0x64($sp)
/* 09A7C8 80099BC8 AFA70054 */  sw    $a3, 0x54($sp)
/* 09A7CC 80099BCC 3C07800E */  lui   $a3, %hi(D_800E169C) # $a3, 0x800e
/* 09A7D0 80099BD0 AFA40060 */  sw    $a0, 0x60($sp)
/* 09A7D4 80099BD4 24E7169C */  addiu $a3, %lo(D_800E169C) # addiu $a3, $a3, 0x169c
/* 09A7D8 80099BD8 250D0001 */  addiu $t5, $t0, 1
/* 09A7DC 80099BDC 0000C812 */  mflo  $t9
/* 09A7E0 80099BE0 01196021 */  addu  $t4, $t0, $t9
/* 09A7E4 80099BE4 000C70C0 */  sll   $t6, $t4, 3
/* 09A7E8 80099BE8 00AEC021 */  addu  $t8, $a1, $t6
/* 09A7EC 80099BEC AF040000 */  sw    $a0, ($t8)
/* 09A7F0 80099BF0 3C19800E */  lui   $t9, %hi(D_800E15EC) # $t9, 0x800e
/* 09A7F4 80099BF4 8FAF0058 */  lw    $t7, 0x58($sp)
/* 09A7F8 80099BF8 273915EC */  addiu $t9, %lo(D_800E15EC) # addiu $t9, $t9, 0x15ec
/* 09A7FC 80099BFC 01391821 */  addu  $v1, $t1, $t9
/* 09A800 80099C00 3C18800E */  lui   $t8, %hi(D_800E1644) # $t8, 0x800e
/* 09A804 80099C04 27181644 */  addiu $t8, %lo(D_800E1644) # addiu $t8, $t8, 0x1644
/* 09A808 80099C08 AC6F0028 */  sw    $t7, 0x28($v1)
/* 09A80C 80099C0C 8FAF004C */  lw    $t7, 0x4c($sp)
/* 09A810 80099C10 01382021 */  addu  $a0, $t1, $t8
/* 09A814 80099C14 00EBC021 */  addu  $t8, $a3, $t3
/* 09A818 80099C18 AF0F0000 */  sw    $t7, ($t8)
/* 09A81C 80099C1C 31AF0001 */  andi  $t7, $t5, 1
/* 09A820 80099C20 01E60019 */  multu $t7, $a2
/* 09A824 80099C24 01E06825 */  move  $t5, $t7
/* 09A828 80099C28 01C06025 */  move  $t4, $t6
/* 09A82C 80099C2C 8FAE005C */  lw    $t6, 0x5c($sp)
/* 09A830 80099C30 8FB90054 */  lw    $t9, 0x54($sp)
/* 09A834 80099C34 AC6E0000 */  sw    $t6, ($v1)
/* 09A838 80099C38 8FAE0050 */  lw    $t6, 0x50($sp)
/* 09A83C 80099C3C AC990000 */  sw    $t9, ($a0)
/* 09A840 80099C40 8FB90048 */  lw    $t9, 0x48($sp)
/* 09A844 80099C44 AC8E0028 */  sw    $t6, 0x28($a0)
/* 09A848 80099C48 00EC7021 */  addu  $t6, $a3, $t4
/* 09A84C 80099C4C ADD90000 */  sw    $t9, ($t6)
/* 09A850 80099C50 0000C012 */  mflo  $t8
/* 09A854 80099C54 0118F821 */  addu  $ra, $t0, $t8
/* 09A858 80099C58 39B80001 */  xori  $t8, $t5, 1
/* 09A85C 80099C5C 03060019 */  multu $t8, $a2
/* 09A860 80099C60 001FC8C0 */  sll   $t9, $ra, 3
/* 09A864 80099C64 8FAE0064 */  lw    $t6, 0x64($sp)
/* 09A868 80099C68 00B97821 */  addu  $t7, $a1, $t9
/* 09A86C 80099C6C 0320F825 */  move  $ra, $t9
/* 09A870 80099C70 AC570000 */  sw    $s7, ($v0)
/* 09A874 80099C74 AC5E0028 */  sw    $fp, 0x28($v0)
/* 09A878 80099C78 ADEE0008 */  sw    $t6, 8($t7)
/* 09A87C 80099C7C 8FAF0060 */  lw    $t7, 0x60($sp)
/* 09A880 80099C80 25110002 */  addiu $s1, $t0, 2
/* 09A884 80099C84 AC570008 */  sw    $s7, 8($v0)
/* 09A888 80099C88 AC5E0030 */  sw    $fp, 0x30($v0)
/* 09A88C 80099C8C 0000C812 */  mflo  $t9
/* 09A890 80099C90 01198021 */  addu  $s0, $t0, $t9
/* 09A894 80099C94 001070C0 */  sll   $t6, $s0, 3
/* 09A898 80099C98 00AEC021 */  addu  $t8, $a1, $t6
/* 09A89C 80099C9C AF0F0008 */  sw    $t7, 8($t8)
/* 09A8A0 80099CA0 8FB9005C */  lw    $t9, 0x5c($sp)
/* 09A8A4 80099CA4 01C08025 */  move  $s0, $t6
/* 09A8A8 80099CA8 8FAE0058 */  lw    $t6, 0x58($sp)
/* 09A8AC 80099CAC AC790008 */  sw    $t9, 8($v1)
/* 09A8B0 80099CB0 8FB9004C */  lw    $t9, 0x4c($sp)
/* 09A8B4 80099CB4 AC6E0030 */  sw    $t6, 0x30($v1)
/* 09A8B8 80099CB8 00FF7021 */  addu  $t6, $a3, $ra
/* 09A8BC 80099CBC ADD90008 */  sw    $t9, 8($t6)
/* 09A8C0 80099CC0 32390001 */  andi  $t9, $s1, 1
/* 09A8C4 80099CC4 03260019 */  multu $t9, $a2
/* 09A8C8 80099CC8 03208825 */  move  $s1, $t9
/* 09A8CC 80099CCC 8FAF0054 */  lw    $t7, 0x54($sp)
/* 09A8D0 80099CD0 8FB80050 */  lw    $t8, 0x50($sp)
/* 09A8D4 80099CD4 AC8F0008 */  sw    $t7, 8($a0)
/* 09A8D8 80099CD8 8FAF0048 */  lw    $t7, 0x48($sp)
/* 09A8DC 80099CDC AC980030 */  sw    $t8, 0x30($a0)
/* 09A8E0 80099CE0 00F0C021 */  addu  $t8, $a3, $s0
/* 09A8E4 80099CE4 AF0F0008 */  sw    $t7, 8($t8)
/* 09A8E8 80099CE8 8FB80064 */  lw    $t8, 0x64($sp)
/* 09A8EC 80099CEC 25140003 */  addiu $s4, $t0, 3
/* 09A8F0 80099CF0 AC570010 */  sw    $s7, 0x10($v0)
/* 09A8F4 80099CF4 00007012 */  mflo  $t6
/* 09A8F8 80099CF8 010E9021 */  addu  $s2, $t0, $t6
/* 09A8FC 80099CFC 3A2E0001 */  xori  $t6, $s1, 1
/* 09A900 80099D00 01C60019 */  multu $t6, $a2
/* 09A904 80099D04 001278C0 */  sll   $t7, $s2, 3
/* 09A908 80099D08 00AFC821 */  addu  $t9, $a1, $t7
/* 09A90C 80099D0C 01E09025 */  move  $s2, $t7
/* 09A910 80099D10 AF380010 */  sw    $t8, 0x10($t9)
/* 09A914 80099D14 8FB90060 */  lw    $t9, 0x60($sp)
/* 09A918 80099D18 AC5E0038 */  sw    $fp, 0x38($v0)
/* 09A91C 80099D1C 00007812 */  mflo  $t7
/* 09A920 80099D20 010F9821 */  addu  $s3, $t0, $t7
/* 09A924 80099D24 0013C0C0 */  sll   $t8, $s3, 3
/* 09A928 80099D28 00B87021 */  addu  $t6, $a1, $t8
/* 09A92C 80099D2C ADD90010 */  sw    $t9, 0x10($t6)
/* 09A930 80099D30 8FAF005C */  lw    $t7, 0x5c($sp)
/* 09A934 80099D34 03009825 */  move  $s3, $t8
/* 09A938 80099D38 8FB80058 */  lw    $t8, 0x58($sp)
/* 09A93C 80099D3C AC6F0010 */  sw    $t7, 0x10($v1)
/* 09A940 80099D40 8FAF004C */  lw    $t7, 0x4c($sp)
/* 09A944 80099D44 AC780038 */  sw    $t8, 0x38($v1)
/* 09A948 80099D48 00F2C021 */  addu  $t8, $a3, $s2
/* 09A94C 80099D4C AF0F0010 */  sw    $t7, 0x10($t8)
/* 09A950 80099D50 328F0001 */  andi  $t7, $s4, 1
/* 09A954 80099D54 01E60019 */  multu $t7, $a2
/* 09A958 80099D58 01E0A025 */  move  $s4, $t7
/* 09A95C 80099D5C 8FB90054 */  lw    $t9, 0x54($sp)
/* 09A960 80099D60 8FAE0050 */  lw    $t6, 0x50($sp)
/* 09A964 80099D64 AC990010 */  sw    $t9, 0x10($a0)
/* 09A968 80099D68 8FB90048 */  lw    $t9, 0x48($sp)
/* 09A96C 80099D6C AC8E0038 */  sw    $t6, 0x38($a0)
/* 09A970 80099D70 00F37021 */  addu  $t6, $a3, $s3
/* 09A974 80099D74 ADD90010 */  sw    $t9, 0x10($t6)
/* 09A978 80099D78 8FAE0064 */  lw    $t6, 0x64($sp)
/* 09A97C 80099D7C AC570018 */  sw    $s7, 0x18($v0)
/* 09A980 80099D80 AC5E0040 */  sw    $fp, 0x40($v0)
/* 09A984 80099D84 0000C012 */  mflo  $t8
/* 09A988 80099D88 0118A821 */  addu  $s5, $t0, $t8
/* 09A98C 80099D8C 3A980001 */  xori  $t8, $s4, 1
/* 09A990 80099D90 03060019 */  multu $t8, $a2
/* 09A994 80099D94 0015C8C0 */  sll   $t9, $s5, 3
/* 09A998 80099D98 00B97821 */  addu  $t7, $a1, $t9
/* 09A99C 80099D9C 0320A825 */  move  $s5, $t9
/* 09A9A0 80099DA0 ADEE0018 */  sw    $t6, 0x18($t7)
/* 09A9A4 80099DA4 8FAF0060 */  lw    $t7, 0x60($sp)
/* 09A9A8 80099DA8 0000C812 */  mflo  $t9
/* 09A9AC 80099DAC 0119B021 */  addu  $s6, $t0, $t9
/* 09A9B0 80099DB0 001670C0 */  sll   $t6, $s6, 3
/* 09A9B4 80099DB4 00AEC021 */  addu  $t8, $a1, $t6
/* 09A9B8 80099DB8 AF0F0018 */  sw    $t7, 0x18($t8)
/* 09A9BC 80099DBC 8FB9005C */  lw    $t9, 0x5c($sp)
/* 09A9C0 80099DC0 01C0B025 */  move  $s6, $t6
/* 09A9C4 80099DC4 8FAE0058 */  lw    $t6, 0x58($sp)
/* 09A9C8 80099DC8 AC790018 */  sw    $t9, 0x18($v1)
/* 09A9CC 80099DCC 8FB9004C */  lw    $t9, 0x4c($sp)
/* 09A9D0 80099DD0 8FAF0054 */  lw    $t7, 0x54($sp)
/* 09A9D4 80099DD4 AC6E0040 */  sw    $t6, 0x40($v1)
/* 09A9D8 80099DD8 8FB80050 */  lw    $t8, 0x50($sp)
/* 09A9DC 80099DDC 00F57021 */  addu  $t6, $a3, $s5
/* 09A9E0 80099DE0 ADD90018 */  sw    $t9, 0x18($t6)
/* 09A9E4 80099DE4 AC8F0018 */  sw    $t7, 0x18($a0)
/* 09A9E8 80099DE8 8FAF0048 */  lw    $t7, 0x48($sp)
/* 09A9EC 80099DEC AC980040 */  sw    $t8, 0x40($a0)
/* 09A9F0 80099DF0 00F6C021 */  addu  $t8, $a3, $s6
/* 09A9F4 80099DF4 0C023917 */  jal   assign_vehicle_icon_textures
/* 09A9F8 80099DF8 AF0F0018 */   sw    $t7, 0x18($t8)
/* 09A9FC 80099DFC 0C025181 */  jal   assign_racer_portrait_textures
/* 09AA00 80099E00 00000000 */   nop   
/* 09AA04 80099E04 0C02392C */  jal   func_8008E4B0
/* 09AA08 80099E08 00000000 */   nop   
/* 09AA0C 80099E0C 3C018012 */  lui   $at, %hi(gOptionBlinkTimer) # $at, 0x8012
/* 09AA10 80099E10 AC2063BC */  sw    $zero, %lo(gOptionBlinkTimer)($at)
/* 09AA14 80099E14 3C018012 */  lui   $at, %hi(D_801263E0) # $at, 0x8012
/* 09AA18 80099E18 AC2063E0 */  sw    $zero, %lo(D_801263E0)($at)
/* 09AA1C 80099E1C 3C018012 */  lui   $at, %hi(D_801263D8) # $at, 0x8012
/* 09AA20 80099E20 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 09AA24 80099E24 AC2063D8 */  sw    $zero, %lo(D_801263D8)($at)
/* 09AA28 80099E28 8FB90070 */  lw    $t9, 0x70($sp)
/* 09AA2C 80099E2C 2442F47C */  addiu $v0, %lo(gMenuDelay) # addiu $v0, $v0, -0xb84
/* 09AA30 80099E30 AC400000 */  sw    $zero, ($v0)
/* 09AA34 80099E34 3C018012 */  lui   $at, %hi(D_80126498) # $at, 0x8012
/* 09AA38 80099E38 17200006 */  bnez  $t9, .L80099E54
/* 09AA3C 80099E3C AC206498 */   sw    $zero, %lo(D_80126498)($at)
/* 09AA40 80099E40 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeOut) # $a0, 0x800e
/* 09AA44 80099E44 0C030076 */  jal   func_800C01D8
/* 09AA48 80099E48 2484F77C */   addiu $a0, %lo(sMenuTransitionFadeOut) # addiu $a0, $a0, -0x884
/* 09AA4C 80099E4C 10000004 */  b     .L80099E60
/* 09AA50 80099E50 8FBF0044 */   lw    $ra, 0x44($sp)
.L80099E54:
/* 09AA54 80099E54 240E001E */  li    $t6, 30
/* 09AA58 80099E58 AC4E0000 */  sw    $t6, ($v0)
/* 09AA5C 80099E5C 8FBF0044 */  lw    $ra, 0x44($sp)
.L80099E60:
/* 09AA60 80099E60 8FB00020 */  lw    $s0, 0x20($sp)
/* 09AA64 80099E64 8FB10024 */  lw    $s1, 0x24($sp)
/* 09AA68 80099E68 8FB20028 */  lw    $s2, 0x28($sp)
/* 09AA6C 80099E6C 8FB3002C */  lw    $s3, 0x2c($sp)
/* 09AA70 80099E70 8FB40030 */  lw    $s4, 0x30($sp)
/* 09AA74 80099E74 8FB50034 */  lw    $s5, 0x34($sp)
/* 09AA78 80099E78 8FB60038 */  lw    $s6, 0x38($sp)
/* 09AA7C 80099E7C 8FB7003C */  lw    $s7, 0x3c($sp)
/* 09AA80 80099E80 8FBE0040 */  lw    $fp, 0x40($sp)
/* 09AA84 80099E84 03E00008 */  jr    $ra
/* 09AA88 80099E88 27BD0078 */   addiu $sp, $sp, 0x78

