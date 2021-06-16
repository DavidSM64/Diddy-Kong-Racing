glabel func_8008F00C
/* 08FC0C 8008F00C 3C058012 */  lui   $a1, %hi(D_801267D0) # $a1, 0x8012
/* 08FC10 8008F010 24A567D0 */  addiu $a1, %lo(D_801267D0) # addiu $a1, $a1, 0x67d0
/* 08FC14 8008F014 8CA20000 */  lw    $v0, ($a1)
/* 08FC18 8008F018 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 08FC1C 8008F01C 2401FFFF */  li    $at, -1
/* 08FC20 8008F020 AFBF0014 */  sw    $ra, 0x14($sp)
/* 08FC24 8008F024 10410009 */  beq   $v0, $at, .L8008F04C
/* 08FC28 8008F028 AFA40018 */   sw    $a0, 0x18($sp)
/* 08FC2C 8008F02C 10400007 */  beqz  $v0, .L8008F04C
/* 08FC30 8008F030 24010001 */   li    $at, 1
/* 08FC34 8008F034 14410005 */  bne   $v0, $at, .L8008F04C
/* 08FC38 8008F038 3C04800E */   lui   $a0, %hi(D_800E07E8) # $a0, 0x800e
/* 08FC3C 8008F03C 0C02712A */  jal   func_8009C4A8
/* 08FC40 8008F040 248407E8 */   addiu $a0, %lo(D_800E07E8) # addiu $a0, $a0, 0x7e8
/* 08FC44 8008F044 3C058012 */  lui   $a1, %hi(D_801267D0) # $a1, 0x8012
/* 08FC48 8008F048 24A567D0 */  addiu $a1, %lo(D_801267D0) # addiu $a1, $a1, 0x67d0
.L8008F04C:
/* 08FC4C 8008F04C 8FAE0018 */  lw    $t6, 0x18($sp)
/* 08FC50 8008F050 00000000 */  nop   
/* 08FC54 8008F054 05C00072 */  bltz  $t6, .L8008F220
/* 08FC58 8008F058 ACAE0000 */   sw    $t6, ($a1)
/* 08FC5C 8008F05C 29C10002 */  slti  $at, $t6, 2
/* 08FC60 8008F060 10200070 */  beqz  $at, .L8008F224
/* 08FC64 8008F064 8FBF0014 */   lw    $ra, 0x14($sp)
/* 08FC68 8008F068 11C00006 */  beqz  $t6, .L8008F084
/* 08FC6C 8008F06C 3C018012 */   lui   $at, %hi(D_801269DC) # $at, 0x8012
/* 08FC70 8008F070 24010001 */  li    $at, 1
/* 08FC74 8008F074 11C1000B */  beq   $t6, $at, .L8008F0A4
/* 08FC78 8008F078 3C04800E */   lui   $a0, %hi(gTrackIdForPreview) # $a0, 0x800e
/* 08FC7C 8008F07C 10000069 */  b     .L8008F224
/* 08FC80 8008F080 8FBF0014 */   lw    $ra, 0x14($sp)
.L8008F084:
/* 08FC84 8008F084 C42469DC */  lwc1  $f4, %lo(D_801269DC)($at)
/* 08FC88 8008F088 3C018012 */  lui   $at, %hi(D_801269E8) # $at, 0x8012
/* 08FC8C 8008F08C E42469E8 */  swc1  $f4, %lo(D_801269E8)($at)
/* 08FC90 8008F090 3C018012 */  lui   $at, %hi(D_801269E4) # $at, 0x8012
/* 08FC94 8008F094 C42669E4 */  lwc1  $f6, %lo(D_801269E4)($at)
/* 08FC98 8008F098 3C018012 */  lui   $at, %hi(D_801269EC) # $at, 0x8012
/* 08FC9C 8008F09C 10000060 */  b     .L8008F220
/* 08FCA0 8008F0A0 E42669EC */   swc1  $f6, %lo(D_801269EC)($at)
.L8008F0A4:
/* 08FCA4 8008F0A4 8C84F4C4 */  lw    $a0, %lo(gTrackIdForPreview)($a0)
/* 08FCA8 8008F0A8 0C01AC2B */  jal   func_8006B0AC
/* 08FCAC 8008F0AC 00000000 */   nop   
/* 08FCB0 8008F0B0 3C06800E */  lui   $a2, %hi(gNumberOfActivePlayers) # $a2, 0x800e
/* 08FCB4 8008F0B4 8CC6F4BC */  lw    $a2, %lo(gNumberOfActivePlayers)($a2)
/* 08FCB8 8008F0B8 3C048012 */  lui   $a0, %hi(D_801269C4) # $a0, 0x8012
/* 08FCBC 8008F0BC 18C0000B */  blez  $a2, .L8008F0EC
/* 08FCC0 8008F0C0 24180001 */   li    $t8, 1
/* 08FCC4 8008F0C4 3C0F8012 */  lui   $t7, %hi(gPlayerSelectVehicle) # $t7, 0x8012
/* 08FCC8 8008F0C8 25E369C0 */  addiu $v1, $t7, %lo(gPlayerSelectVehicle)
/* 08FCCC 8008F0CC 00C32821 */  addu  $a1, $a2, $v1
/* 08FCD0 8008F0D0 248469C4 */  addiu $a0, %lo(D_801269C4) # addiu $a0, $a0, 0x69c4
.L8008F0D4:
/* 08FCD4 8008F0D4 24630001 */  addiu $v1, $v1, 1
/* 08FCD8 8008F0D8 0065082B */  sltu  $at, $v1, $a1
/* 08FCDC 8008F0DC 24840001 */  addiu $a0, $a0, 1
/* 08FCE0 8008F0E0 A080FFFF */  sb    $zero, -1($a0)
/* 08FCE4 8008F0E4 1420FFFB */  bnez  $at, .L8008F0D4
/* 08FCE8 8008F0E8 A062FFFF */   sb    $v0, -1($v1)
.L8008F0EC:
/* 08FCEC 8008F0EC 3C01800E */  lui   $at, %hi(gNumberOfReadyPlayers) # $at, 0x800e
/* 08FCF0 8008F0F0 AC20F480 */  sw    $zero, %lo(gNumberOfReadyPlayers)($at)
/* 08FCF4 8008F0F4 3C01800E */  lui   $at, %hi(D_800E0980) # $at, 0x800e
/* 08FCF8 8008F0F8 3C04800E */  lui   $a0, %hi(D_800E07E8) # $a0, 0x800e
/* 08FCFC 8008F0FC AC380980 */  sw    $t8, %lo(D_800E0980)($at)
/* 08FD00 8008F100 0C02719D */  jal   func_8009C674
/* 08FD04 8008F104 248407E8 */   addiu $a0, %lo(D_800E07E8) # addiu $a0, $a0, 0x7e8
/* 08FD08 8008F108 3C04800E */  lui   $a0, %hi(D_800E0830) # $a0, 0x800e
/* 08FD0C 8008F10C 0C027229 */  jal   func_8009C8A4
/* 08FD10 8008F110 24840830 */   addiu $a0, %lo(D_800E0830) # addiu $a0, $a0, 0x830
/* 08FD14 8008F114 0C023917 */  jal   func_8008E45C
/* 08FD18 8008F118 00000000 */   nop   
/* 08FD1C 8008F11C 3C028012 */  lui   $v0, %hi(D_80126550) # $v0, 0x8012
/* 08FD20 8008F120 24426550 */  addiu $v0, %lo(D_80126550) # addiu $v0, $v0, 0x6550
/* 08FD24 8008F124 3C03800E */  lui   $v1, %hi(D_800E04A4) # $v1, 0x800e
/* 08FD28 8008F128 3C04800E */  lui   $a0, %hi(D_800E04BC) # $a0, 0x800e
/* 08FD2C 8008F12C 8C590090 */  lw    $t9, 0x90($v0)
/* 08FD30 8008F130 8C480094 */  lw    $t0, 0x94($v0)
/* 08FD34 8008F134 8C490098 */  lw    $t1, 0x98($v0)
/* 08FD38 8008F138 8C4A009C */  lw    $t2, 0x9c($v0)
/* 08FD3C 8008F13C 248404BC */  addiu $a0, %lo(D_800E04BC) # addiu $a0, $a0, 0x4bc
/* 08FD40 8008F140 246304A4 */  addiu $v1, %lo(D_800E04A4) # addiu $v1, $v1, 0x4a4
/* 08FD44 8008F144 8C4B007C */  lw    $t3, 0x7c($v0)
/* 08FD48 8008F148 3C01800E */  lui   $at, %hi(D_800E04D4) # $at, 0x800e
/* 08FD4C 8008F14C AC790000 */  sw    $t9, ($v1)
/* 08FD50 8008F150 AC680008 */  sw    $t0, 8($v1)
/* 08FD54 8008F154 AC890000 */  sw    $t1, ($a0)
/* 08FD58 8008F158 AC8A0008 */  sw    $t2, 8($a0)
/* 08FD5C 8008F15C AC2B04D4 */  sw    $t3, %lo(D_800E04D4)($at)
/* 08FD60 8008F160 8C4C0078 */  lw    $t4, 0x78($v0)
/* 08FD64 8008F164 3C01800E */  lui   $at, %hi(D_800E04E4) # $at, 0x800e
/* 08FD68 8008F168 AC2C04E4 */  sw    $t4, %lo(D_800E04E4)($at)
/* 08FD6C 8008F16C 8C4D0084 */  lw    $t5, 0x84($v0)
/* 08FD70 8008F170 3C01800E */  lui   $at, %hi(D_800E04F4) # $at, 0x800e
/* 08FD74 8008F174 AC2D04F4 */  sw    $t5, %lo(D_800E04F4)($at)
/* 08FD78 8008F178 8C4E0080 */  lw    $t6, 0x80($v0)
/* 08FD7C 8008F17C 3C01800E */  lui   $at, %hi(D_800E0504) # $at, 0x800e
/* 08FD80 8008F180 AC2E0504 */  sw    $t6, %lo(D_800E0504)($at)
/* 08FD84 8008F184 8C4F008C */  lw    $t7, 0x8c($v0)
/* 08FD88 8008F188 3C01800E */  lui   $at, %hi(D_800E0514) # $at, 0x800e
/* 08FD8C 8008F18C AC2F0514 */  sw    $t7, %lo(D_800E0514)($at)
/* 08FD90 8008F190 8C580088 */  lw    $t8, 0x88($v0)
/* 08FD94 8008F194 3C01800E */  lui   $at, %hi(D_800E0524) # $at, 0x800e
/* 08FD98 8008F198 AC380524 */  sw    $t8, %lo(D_800E0524)($at)
/* 08FD9C 8008F19C 8C5900A0 */  lw    $t9, 0xa0($v0)
/* 08FDA0 8008F1A0 3C01800E */  lui   $at, %hi(D_800E0534) # $at, 0x800e
/* 08FDA4 8008F1A4 AC390534 */  sw    $t9, %lo(D_800E0534)($at)
/* 08FDA8 8008F1A8 8C4800A8 */  lw    $t0, 0xa8($v0)
/* 08FDAC 8008F1AC 3C01800E */  lui   $at, %hi(D_800E0544) # $at, 0x800e
/* 08FDB0 8008F1B0 AC280544 */  sw    $t0, %lo(D_800E0544)($at)
/* 08FDB4 8008F1B4 8C4900A4 */  lw    $t1, 0xa4($v0)
/* 08FDB8 8008F1B8 3C01800E */  lui   $at, %hi(D_800E0554) # $at, 0x800e
/* 08FDBC 8008F1BC AC290554 */  sw    $t1, %lo(D_800E0554)($at)
/* 08FDC0 8008F1C0 8C4A00AC */  lw    $t2, 0xac($v0)
/* 08FDC4 8008F1C4 3C01800E */  lui   $at, %hi(D_800E0564) # $at, 0x800e
/* 08FDC8 8008F1C8 AC2A0564 */  sw    $t2, %lo(D_800E0564)($at)
/* 08FDCC 8008F1CC 8C4B00B0 */  lw    $t3, 0xb0($v0)
/* 08FDD0 8008F1D0 3C01800E */  lui   $at, %hi(D_800E0574) # $at, 0x800e
/* 08FDD4 8008F1D4 AC2B0574 */  sw    $t3, %lo(D_800E0574)($at)
/* 08FDD8 8008F1D8 8C4C00B4 */  lw    $t4, 0xb4($v0)
/* 08FDDC 8008F1DC 3C01800E */  lui   $at, %hi(D_800E0584) # $at, 0x800e
/* 08FDE0 8008F1E0 AC2C0584 */  sw    $t4, %lo(D_800E0584)($at)
/* 08FDE4 8008F1E4 8C4D00B8 */  lw    $t5, 0xb8($v0)
/* 08FDE8 8008F1E8 3C01800E */  lui   $at, %hi(D_800E0594) # $at, 0x800e
/* 08FDEC 8008F1EC AC2D0594 */  sw    $t5, %lo(D_800E0594)($at)
/* 08FDF0 8008F1F0 8C4E00BC */  lw    $t6, 0xbc($v0)
/* 08FDF4 8008F1F4 3C01800E */  lui   $at, %hi(D_800E05A4) # $at, 0x800e
/* 08FDF8 8008F1F8 AC2E05A4 */  sw    $t6, %lo(D_800E05A4)($at)
/* 08FDFC 8008F1FC 8C4F00C0 */  lw    $t7, 0xc0($v0)
/* 08FE00 8008F200 3C01800E */  lui   $at, %hi(D_800E05B4) # $at, 0x800e
/* 08FE04 8008F204 AC2F05B4 */  sw    $t7, %lo(D_800E05B4)($at)
/* 08FE08 8008F208 8C5800C4 */  lw    $t8, 0xc4($v0)
/* 08FE0C 8008F20C 3C01800E */  lui   $at, %hi(D_800E05C4) # $at, 0x800e
/* 08FE10 8008F210 AC3805C4 */  sw    $t8, %lo(D_800E05C4)($at)
/* 08FE14 8008F214 8C590178 */  lw    $t9, 0x178($v0)
/* 08FE18 8008F218 3C01800E */  lui   $at, %hi(D_800E0614) # $at, 0x800e
/* 08FE1C 8008F21C AC390614 */  sw    $t9, %lo(D_800E0614)($at)
.L8008F220:
/* 08FE20 8008F220 8FBF0014 */  lw    $ra, 0x14($sp)
.L8008F224:
/* 08FE24 8008F224 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08FE28 8008F228 AC20F47C */  sw    $zero, %lo(gMenuDelay)($at)
/* 08FE2C 8008F22C 03E00008 */  jr    $ra
/* 08FE30 8008F230 27BD0018 */   addiu $sp, $sp, 0x18

