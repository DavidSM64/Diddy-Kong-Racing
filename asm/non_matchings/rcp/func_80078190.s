glabel func_80078190
/* 078D90 80078190 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 078D94 80078194 AFBF003C */  sw    $ra, 0x3c($sp)
/* 078D98 80078198 AFBE0038 */  sw    $fp, 0x38($sp)
/* 078D9C 8007819C AFB70034 */  sw    $s7, 0x34($sp)
/* 078DA0 800781A0 AFB60030 */  sw    $s6, 0x30($sp)
/* 078DA4 800781A4 AFB5002C */  sw    $s5, 0x2c($sp)
/* 078DA8 800781A8 AFB40028 */  sw    $s4, 0x28($sp)
/* 078DAC 800781AC AFB30024 */  sw    $s3, 0x24($sp)
/* 078DB0 800781B0 AFB20020 */  sw    $s2, 0x20($sp)
/* 078DB4 800781B4 AFB1001C */  sw    $s1, 0x1c($sp)
/* 078DB8 800781B8 AFB00018 */  sw    $s0, 0x18($sp)
/* 078DBC 800781BC 0C01E948 */  jal   fb_size
/* 078DC0 800781C0 AFA40040 */   sw    $a0, 0x40($sp)
/* 078DC4 800781C4 8FA40040 */  lw    $a0, 0x40($sp)
/* 078DC8 800781C8 00024403 */  sra   $t0, $v0, 0x10
/* 078DCC 800781CC 8C830000 */  lw    $v1, ($a0)
/* 078DD0 800781D0 3C19800E */  lui   $t9, %hi(dRaceFinishBackgroundSettings) # $t9, 0x800e
/* 078DD4 800781D4 246F0008 */  addiu $t7, $v1, 8
/* 078DD8 800781D8 AC8F0000 */  sw    $t7, ($a0)
/* 078DDC 800781DC 3C0A800E */  lui   $t2, %hi(gTexBGTex2) # $t2, 0x800e
/* 078DE0 800781E0 310EFFFF */  andi  $t6, $t0, 0xffff
/* 078DE4 800781E4 2739E598 */  addiu $t9, %lo(dRaceFinishBackgroundSettings) # addiu $t9, $t9, -0x1a68
/* 078DE8 800781E8 3C180600 */  lui   $t8, 0x600
/* 078DEC 800781EC 254AE4C8 */  addiu $t2, %lo(gTexBGTex2) # addiu $t2, $t2, -0x1b38
/* 078DF0 800781F0 01C04025 */  move  $t0, $t6
/* 078DF4 800781F4 AC780000 */  sw    $t8, ($v1)
/* 078DF8 800781F8 AC790004 */  sw    $t9, 4($v1)
/* 078DFC 800781FC 8D4E0000 */  lw    $t6, ($t2)
/* 078E00 80078200 3C09800E */  lui   $t1, %hi(gTexBGTex1) # $t1, 0x800e
/* 078E04 80078204 15C00070 */  bnez  $t6, .L800783C8
/* 078E08 80078208 2529E4C4 */   addiu $t1, %lo(gTexBGTex1) # addiu $t1, $t1, -0x1b3c
/* 078E0C 8007820C 8C830000 */  lw    $v1, ($a0)
/* 078E10 80078210 3C09800E */  lui   $t1, %hi(gTexBGTex1) # $t1, 0x800e
/* 078E14 80078214 246F0008 */  addiu $t7, $v1, 8
/* 078E18 80078218 2529E4C4 */  addiu $t1, %lo(gTexBGTex1) # addiu $t1, $t1, -0x1b3c
/* 078E1C 8007821C AC8F0000 */  sw    $t7, ($a0)
/* 078E20 80078220 8D380000 */  lw    $t8, ($t1)
/* 078E24 80078224 3C010700 */  lui   $at, 0x700
/* 078E28 80078228 8707000A */  lh    $a3, 0xa($t8)
/* 078E2C 8007822C 3051FFFF */  andi  $s1, $v0, 0xffff
/* 078E30 80078230 30F900FF */  andi  $t9, $a3, 0xff
/* 078E34 80078234 00197400 */  sll   $t6, $t9, 0x10
/* 078E38 80078238 0007C0C0 */  sll   $t8, $a3, 3
/* 078E3C 8007823C 3319FFFF */  andi  $t9, $t8, 0xffff
/* 078E40 80078240 01C17825 */  or    $t7, $t6, $at
/* 078E44 80078244 01F97025 */  or    $t6, $t7, $t9
/* 078E48 80078248 AC6E0000 */  sw    $t6, ($v1)
/* 078E4C 8007824C 8D380000 */  lw    $t8, ($t1)
/* 078E50 80078250 3C018000 */  lui   $at, 0x8000
/* 078E54 80078254 8F0F000C */  lw    $t7, 0xc($t8)
/* 078E58 80078258 00117080 */  sll   $t6, $s1, 2
/* 078E5C 8007825C 01E1C821 */  addu  $t9, $t7, $at
/* 078E60 80078260 AC790004 */  sw    $t9, 4($v1)
/* 078E64 80078264 8D260000 */  lw    $a2, ($t1)
/* 078E68 80078268 0008B080 */  sll   $s6, $t0, 2
/* 078E6C 8007826C 90D00000 */  lbu   $s0, ($a2)
/* 078E70 80078270 90D40001 */  lbu   $s4, 1($a2)
/* 078E74 80078274 0010C080 */  sll   $t8, $s0, 2
/* 078E78 80078278 00147880 */  sll   $t7, $s4, 2
/* 078E7C 8007827C 01C08825 */  move  $s1, $t6
/* 078E80 80078280 03008025 */  move  $s0, $t8
/* 078E84 80078284 01E0A025 */  move  $s4, $t7
/* 078E88 80078288 00009825 */  move  $s3, $zero
/* 078E8C 8007828C 1AC00128 */  blez  $s6, .L80078730
/* 078E90 80078290 00009025 */   move  $s2, $zero
/* 078E94 80078294 3C17800E */  lui   $s7, %hi(gTexBGShiftX) # $s7, 0x800e
/* 078E98 80078298 3C1F0400 */  lui   $ra, (0x04000400 >> 16) # lui $ra, 0x400
/* 078E9C 8007829C 37FF0400 */  ori   $ra, (0x04000400 & 0xFFFF) # ori $ra, $ra, 0x400
/* 078EA0 800782A0 26F7E4C0 */  addiu $s7, %lo(gTexBGShiftX) # addiu $s7, $s7, -0x1b40
/* 078EA4 800782A4 2715FFFF */  addiu $s5, $t8, -1
/* 078EA8 800782A8 3C0DB200 */  lui   $t5, 0xb200
/* 078EAC 800782AC 3C0CB300 */  lui   $t4, 0xb300
/* 078EB0 800782B0 3C0BE400 */  lui   $t3, 0xe400
.L800782B4:
/* 078EB4 800782B4 00131023 */  negu  $v0, $s3
/* 078EB8 800782B8 0051082A */  slt   $at, $v0, $s1
/* 078EBC 800782BC 1020003A */  beqz  $at, .L800783A8
/* 078EC0 800782C0 02544821 */   addu  $t1, $s2, $s4
/* 078EC4 800782C4 31390FFF */  andi  $t9, $t1, 0xfff
/* 078EC8 800782C8 03204825 */  move  $t1, $t9
/* 078ECC 800782CC 324A0FFF */  andi  $t2, $s2, 0xfff
.L800782D0:
/* 078ED0 800782D0 0441001A */  bgez  $v0, .L8007833C
/* 078ED4 800782D4 00503021 */   addu  $a2, $v0, $s0
/* 078ED8 800782D8 8C830000 */  lw    $v1, ($a0)
/* 078EDC 800782DC 00503021 */  addu  $a2, $v0, $s0
/* 078EE0 800782E0 30D80FFF */  andi  $t8, $a2, 0xfff
/* 078EE4 800782E4 246E0008 */  addiu $t6, $v1, 8
/* 078EE8 800782E8 AC8E0000 */  sw    $t6, ($a0)
/* 078EEC 800782EC 00187B00 */  sll   $t7, $t8, 0xc
/* 078EF0 800782F0 01EBC825 */  or    $t9, $t7, $t3
/* 078EF4 800782F4 03297025 */  or    $t6, $t9, $t1
/* 078EF8 800782F8 AC6E0000 */  sw    $t6, ($v1)
/* 078EFC 800782FC AC6A0004 */  sw    $t2, 4($v1)
/* 078F00 80078300 8C830000 */  lw    $v1, ($a0)
/* 078F04 80078304 000278C0 */  sll   $t7, $v0, 3
/* 078F08 80078308 24780008 */  addiu $t8, $v1, 8
/* 078F0C 8007830C AC980000 */  sw    $t8, ($a0)
/* 078F10 80078310 000F7023 */  negu  $t6, $t7
/* 078F14 80078314 000EC400 */  sll   $t8, $t6, 0x10
/* 078F18 80078318 AC780004 */  sw    $t8, 4($v1)
/* 078F1C 8007831C AC6C0000 */  sw    $t4, ($v1)
/* 078F20 80078320 8C830000 */  lw    $v1, ($a0)
/* 078F24 80078324 00000000 */  nop   
/* 078F28 80078328 246F0008 */  addiu $t7, $v1, 8
/* 078F2C 8007832C AC8F0000 */  sw    $t7, ($a0)
/* 078F30 80078330 AC7F0004 */  sw    $ra, 4($v1)
/* 078F34 80078334 10000019 */  b     .L8007839C
/* 078F38 80078338 AC6D0000 */   sw    $t5, ($v1)
.L8007833C:
/* 078F3C 8007833C 8C830000 */  lw    $v1, ($a0)
/* 078F40 80078340 30CE0FFF */  andi  $t6, $a2, 0xfff
/* 078F44 80078344 000EC300 */  sll   $t8, $t6, 0xc
/* 078F48 80078348 030B7825 */  or    $t7, $t8, $t3
/* 078F4C 8007834C 24790008 */  addiu $t9, $v1, 8
/* 078F50 80078350 AC990000 */  sw    $t9, ($a0)
/* 078F54 80078354 304E0FFF */  andi  $t6, $v0, 0xfff
/* 078F58 80078358 000EC300 */  sll   $t8, $t6, 0xc
/* 078F5C 8007835C 01E9C825 */  or    $t9, $t7, $t1
/* 078F60 80078360 030A7825 */  or    $t7, $t8, $t2
/* 078F64 80078364 AC6F0004 */  sw    $t7, 4($v1)
/* 078F68 80078368 AC790000 */  sw    $t9, ($v1)
/* 078F6C 8007836C 8C830000 */  lw    $v1, ($a0)
/* 078F70 80078370 00000000 */  nop   
/* 078F74 80078374 24790008 */  addiu $t9, $v1, 8
/* 078F78 80078378 AC990000 */  sw    $t9, ($a0)
/* 078F7C 8007837C AC600004 */  sw    $zero, 4($v1)
/* 078F80 80078380 AC6C0000 */  sw    $t4, ($v1)
/* 078F84 80078384 8C830000 */  lw    $v1, ($a0)
/* 078F88 80078388 00000000 */  nop   
/* 078F8C 8007838C 246E0008 */  addiu $t6, $v1, 8
/* 078F90 80078390 AC8E0000 */  sw    $t6, ($a0)
/* 078F94 80078394 AC7F0004 */  sw    $ra, 4($v1)
/* 078F98 80078398 AC6D0000 */  sw    $t5, ($v1)
.L8007839C:
/* 078F9C 8007839C 00D1082A */  slt   $at, $a2, $s1
/* 078FA0 800783A0 1420FFCB */  bnez  $at, .L800782D0
/* 078FA4 800783A4 00C01025 */   move  $v0, $a2
.L800783A8:
/* 078FA8 800783A8 8EF80000 */  lw    $t8, ($s7)
/* 078FAC 800783AC 02549021 */  addu  $s2, $s2, $s4
/* 078FB0 800783B0 0256082A */  slt   $at, $s2, $s6
/* 078FB4 800783B4 02787821 */  addu  $t7, $s3, $t8
/* 078FB8 800783B8 1420FFBE */  bnez  $at, .L800782B4
/* 078FBC 800783BC 01F59824 */   and   $s3, $t7, $s5
/* 078FC0 800783C0 100000DC */  b     .L80078734
/* 078FC4 800783C4 8C830000 */   lw    $v1, ($a0)
.L800783C8:
/* 078FC8 800783C8 8C830000 */  lw    $v1, ($a0)
/* 078FCC 800783CC 3C010700 */  lui   $at, 0x700
/* 078FD0 800783D0 24790008 */  addiu $t9, $v1, 8
/* 078FD4 800783D4 AC990000 */  sw    $t9, ($a0)
/* 078FD8 800783D8 8D2E0000 */  lw    $t6, ($t1)
/* 078FDC 800783DC 3051FFFF */  andi  $s1, $v0, 0xffff
/* 078FE0 800783E0 85C7000A */  lh    $a3, 0xa($t6)
/* 078FE4 800783E4 0008B080 */  sll   $s6, $t0, 2
/* 078FE8 800783E8 30F800FF */  andi  $t8, $a3, 0xff
/* 078FEC 800783EC 00187C00 */  sll   $t7, $t8, 0x10
/* 078FF0 800783F0 000770C0 */  sll   $t6, $a3, 3
/* 078FF4 800783F4 31D8FFFF */  andi  $t8, $t6, 0xffff
/* 078FF8 800783F8 01E1C825 */  or    $t9, $t7, $at
/* 078FFC 800783FC 03387825 */  or    $t7, $t9, $t8
/* 079000 80078400 AC6F0000 */  sw    $t7, ($v1)
/* 079004 80078404 8D2E0000 */  lw    $t6, ($t1)
/* 079008 80078408 3C018000 */  lui   $at, 0x8000
/* 07900C 8007840C 8DD9000C */  lw    $t9, 0xc($t6)
/* 079010 80078410 00117880 */  sll   $t7, $s1, 2
/* 079014 80078414 0321C021 */  addu  $t8, $t9, $at
/* 079018 80078418 AC780004 */  sw    $t8, 4($v1)
/* 07901C 8007841C 8D260000 */  lw    $a2, ($t1)
/* 079020 80078420 8D580000 */  lw    $t8, ($t2)
/* 079024 80078424 90D00000 */  lbu   $s0, ($a2)
/* 079028 80078428 01E08825 */  move  $s1, $t7
/* 07902C 8007842C 90D40001 */  lbu   $s4, 1($a2)
/* 079030 80078430 930F0001 */  lbu   $t7, 1($t8)
/* 079034 80078434 00107080 */  sll   $t6, $s0, 2
/* 079038 80078438 01C08025 */  move  $s0, $t6
/* 07903C 8007843C 0014C880 */  sll   $t9, $s4, 2
/* 079040 80078440 000F7080 */  sll   $t6, $t7, 2
/* 079044 80078444 00009025 */  move  $s2, $zero
/* 079048 80078448 0320A025 */  move  $s4, $t9
/* 07904C 8007844C 01D9F021 */  addu  $fp, $t6, $t9
/* 079050 80078450 1AC0004D */  blez  $s6, .L80078588
/* 079054 80078454 00009825 */   move  $s3, $zero
/* 079058 80078458 3C17800E */  lui   $s7, %hi(gTexBGShiftX) # $s7, 0x800e
/* 07905C 8007845C 3C1F0400 */  lui   $ra, (0x04000400 >> 16) # lui $ra, 0x400
/* 079060 80078460 37FF0400 */  ori   $ra, (0x04000400 & 0xFFFF) # ori $ra, $ra, 0x400
/* 079064 80078464 26F7E4C0 */  addiu $s7, %lo(gTexBGShiftX) # addiu $s7, $s7, -0x1b40
/* 079068 80078468 2615FFFF */  addiu $s5, $s0, -1
/* 07906C 8007846C 3C0DB200 */  lui   $t5, 0xb200
/* 079070 80078470 3C0CB300 */  lui   $t4, 0xb300
/* 079074 80078474 3C0BE400 */  lui   $t3, 0xe400
.L80078478:
/* 079078 80078478 00131023 */  negu  $v0, $s3
/* 07907C 8007847C 0051082A */  slt   $at, $v0, $s1
/* 079080 80078480 1020003A */  beqz  $at, .L8007856C
/* 079084 80078484 02544821 */   addu  $t1, $s2, $s4
/* 079088 80078488 31390FFF */  andi  $t9, $t1, 0xfff
/* 07908C 8007848C 03204825 */  move  $t1, $t9
/* 079090 80078490 324A0FFF */  andi  $t2, $s2, 0xfff
.L80078494:
/* 079094 80078494 0441001A */  bgez  $v0, .L80078500
/* 079098 80078498 00503021 */   addu  $a2, $v0, $s0
/* 07909C 8007849C 8C830000 */  lw    $v1, ($a0)
/* 0790A0 800784A0 00503021 */  addu  $a2, $v0, $s0
/* 0790A4 800784A4 30CF0FFF */  andi  $t7, $a2, 0xfff
/* 0790A8 800784A8 24780008 */  addiu $t8, $v1, 8
/* 0790AC 800784AC AC980000 */  sw    $t8, ($a0)
/* 0790B0 800784B0 000F7300 */  sll   $t6, $t7, 0xc
/* 0790B4 800784B4 01CBC825 */  or    $t9, $t6, $t3
/* 0790B8 800784B8 0329C025 */  or    $t8, $t9, $t1
/* 0790BC 800784BC AC780000 */  sw    $t8, ($v1)
/* 0790C0 800784C0 AC6A0004 */  sw    $t2, 4($v1)
/* 0790C4 800784C4 8C830000 */  lw    $v1, ($a0)
/* 0790C8 800784C8 000270C0 */  sll   $t6, $v0, 3
/* 0790CC 800784CC 246F0008 */  addiu $t7, $v1, 8
/* 0790D0 800784D0 AC8F0000 */  sw    $t7, ($a0)
/* 0790D4 800784D4 000EC023 */  negu  $t8, $t6
/* 0790D8 800784D8 00187C00 */  sll   $t7, $t8, 0x10
/* 0790DC 800784DC AC6F0004 */  sw    $t7, 4($v1)
/* 0790E0 800784E0 AC6C0000 */  sw    $t4, ($v1)
/* 0790E4 800784E4 8C830000 */  lw    $v1, ($a0)
/* 0790E8 800784E8 00000000 */  nop   
/* 0790EC 800784EC 246E0008 */  addiu $t6, $v1, 8
/* 0790F0 800784F0 AC8E0000 */  sw    $t6, ($a0)
/* 0790F4 800784F4 AC7F0004 */  sw    $ra, 4($v1)
/* 0790F8 800784F8 10000019 */  b     .L80078560
/* 0790FC 800784FC AC6D0000 */   sw    $t5, ($v1)
.L80078500:
/* 079100 80078500 8C830000 */  lw    $v1, ($a0)
/* 079104 80078504 30D80FFF */  andi  $t8, $a2, 0xfff
/* 079108 80078508 00187B00 */  sll   $t7, $t8, 0xc
/* 07910C 8007850C 01EB7025 */  or    $t6, $t7, $t3
/* 079110 80078510 24790008 */  addiu $t9, $v1, 8
/* 079114 80078514 AC990000 */  sw    $t9, ($a0)
/* 079118 80078518 30580FFF */  andi  $t8, $v0, 0xfff
/* 07911C 8007851C 00187B00 */  sll   $t7, $t8, 0xc
/* 079120 80078520 01C9C825 */  or    $t9, $t6, $t1
/* 079124 80078524 01EA7025 */  or    $t6, $t7, $t2
/* 079128 80078528 AC6E0004 */  sw    $t6, 4($v1)
/* 07912C 8007852C AC790000 */  sw    $t9, ($v1)
/* 079130 80078530 8C830000 */  lw    $v1, ($a0)
/* 079134 80078534 00000000 */  nop   
/* 079138 80078538 24790008 */  addiu $t9, $v1, 8
/* 07913C 8007853C AC990000 */  sw    $t9, ($a0)
/* 079140 80078540 AC600004 */  sw    $zero, 4($v1)
/* 079144 80078544 AC6C0000 */  sw    $t4, ($v1)
/* 079148 80078548 8C830000 */  lw    $v1, ($a0)
/* 07914C 8007854C 00000000 */  nop   
/* 079150 80078550 24780008 */  addiu $t8, $v1, 8
/* 079154 80078554 AC980000 */  sw    $t8, ($a0)
/* 079158 80078558 AC7F0004 */  sw    $ra, 4($v1)
/* 07915C 8007855C AC6D0000 */  sw    $t5, ($v1)
.L80078560:
/* 079160 80078560 00D1082A */  slt   $at, $a2, $s1
/* 079164 80078564 1420FFCB */  bnez  $at, .L80078494
/* 079168 80078568 00C01025 */   move  $v0, $a2
.L8007856C:
/* 07916C 8007856C 8EEF0000 */  lw    $t7, ($s7)
/* 079170 80078570 025E9021 */  addu  $s2, $s2, $fp
/* 079174 80078574 0256082A */  slt   $at, $s2, $s6
/* 079178 80078578 026F7021 */  addu  $t6, $s3, $t7
/* 07917C 8007857C 1420FFBE */  bnez  $at, .L80078478
/* 079180 80078580 01D59824 */   and   $s3, $t6, $s5
/* 079184 80078584 00009825 */  move  $s3, $zero
.L80078588:
/* 079188 80078588 8C830000 */  lw    $v1, ($a0)
/* 07918C 8007858C 3C06800E */  lui   $a2, %hi(gTexBGTex2) # $a2, 0x800e
/* 079190 80078590 24790008 */  addiu $t9, $v1, 8
/* 079194 80078594 24C6E4C8 */  addiu $a2, %lo(gTexBGTex2) # addiu $a2, $a2, -0x1b38
/* 079198 80078598 AC990000 */  sw    $t9, ($a0)
/* 07919C 8007859C 8CD80000 */  lw    $t8, ($a2)
/* 0791A0 800785A0 3C010700 */  lui   $at, 0x700
/* 0791A4 800785A4 8705000A */  lh    $a1, 0xa($t8)
/* 0791A8 800785A8 02809025 */  move  $s2, $s4
/* 0791AC 800785AC 30AF00FF */  andi  $t7, $a1, 0xff
/* 0791B0 800785B0 000F7400 */  sll   $t6, $t7, 0x10
/* 0791B4 800785B4 0005C0C0 */  sll   $t8, $a1, 3
/* 0791B8 800785B8 330FFFFF */  andi  $t7, $t8, 0xffff
/* 0791BC 800785BC 01C1C825 */  or    $t9, $t6, $at
/* 0791C0 800785C0 032F7025 */  or    $t6, $t9, $t7
/* 0791C4 800785C4 AC6E0000 */  sw    $t6, ($v1)
/* 0791C8 800785C8 8CD80000 */  lw    $t8, ($a2)
/* 0791CC 800785CC 3C018000 */  lui   $at, 0x8000
/* 0791D0 800785D0 8F19000C */  lw    $t9, 0xc($t8)
/* 0791D4 800785D4 0016C080 */  sll   $t8, $s6, 2
/* 0791D8 800785D8 03217821 */  addu  $t7, $t9, $at
/* 0791DC 800785DC AC6F0004 */  sw    $t7, 4($v1)
/* 0791E0 800785E0 8CD90000 */  lw    $t9, ($a2)
/* 0791E4 800785E4 3C1F0400 */  lui   $ra, (0x04000400 >> 16) # lui $ra, 0x400
/* 0791E8 800785E8 93340001 */  lbu   $s4, 1($t9)
/* 0791EC 800785EC 3C17800E */  lui   $s7, %hi(gTexBGShiftX) # $s7, 0x800e
/* 0791F0 800785F0 00117080 */  sll   $t6, $s1, 2
/* 0791F4 800785F4 0258082A */  slt   $at, $s2, $t8
/* 0791F8 800785F8 00147880 */  sll   $t7, $s4, 2
/* 0791FC 800785FC 26F7E4C0 */  addiu $s7, %lo(gTexBGShiftX) # addiu $s7, $s7, -0x1b40
/* 079200 80078600 37FF0400 */  ori   $ra, (0x04000400 & 0xFFFF) # ori $ra, $ra, 0x400
/* 079204 80078604 3C0BE400 */  lui   $t3, 0xe400
/* 079208 80078608 3C0CB300 */  lui   $t4, 0xb300
/* 07920C 8007860C 3C0DB200 */  lui   $t5, 0xb200
/* 079210 80078610 01C08825 */  move  $s1, $t6
/* 079214 80078614 0300B025 */  move  $s6, $t8
/* 079218 80078618 10200045 */  beqz  $at, .L80078730
/* 07921C 8007861C 01E0A025 */   move  $s4, $t7
/* 079220 80078620 2615FFFF */  addiu $s5, $s0, -1
.L80078624:
/* 079224 80078624 00131023 */  negu  $v0, $s3
/* 079228 80078628 0051082A */  slt   $at, $v0, $s1
/* 07922C 8007862C 1020003A */  beqz  $at, .L80078718
/* 079230 80078630 02544821 */   addu  $t1, $s2, $s4
/* 079234 80078634 312E0FFF */  andi  $t6, $t1, 0xfff
/* 079238 80078638 01C04825 */  move  $t1, $t6
/* 07923C 8007863C 324A0FFF */  andi  $t2, $s2, 0xfff
.L80078640:
/* 079240 80078640 0441001A */  bgez  $v0, .L800786AC
/* 079244 80078644 00503021 */   addu  $a2, $v0, $s0
/* 079248 80078648 8C830000 */  lw    $v1, ($a0)
/* 07924C 8007864C 00503021 */  addu  $a2, $v0, $s0
/* 079250 80078650 30D90FFF */  andi  $t9, $a2, 0xfff
/* 079254 80078654 24780008 */  addiu $t8, $v1, 8
/* 079258 80078658 AC980000 */  sw    $t8, ($a0)
/* 07925C 8007865C 00197B00 */  sll   $t7, $t9, 0xc
/* 079260 80078660 01EB7025 */  or    $t6, $t7, $t3
/* 079264 80078664 01C9C025 */  or    $t8, $t6, $t1
/* 079268 80078668 AC780000 */  sw    $t8, ($v1)
/* 07926C 8007866C AC6A0004 */  sw    $t2, 4($v1)
/* 079270 80078670 8C830000 */  lw    $v1, ($a0)
/* 079274 80078674 000278C0 */  sll   $t7, $v0, 3
/* 079278 80078678 24790008 */  addiu $t9, $v1, 8
/* 07927C 8007867C AC990000 */  sw    $t9, ($a0)
/* 079280 80078680 000FC023 */  negu  $t8, $t7
/* 079284 80078684 0018CC00 */  sll   $t9, $t8, 0x10
/* 079288 80078688 AC790004 */  sw    $t9, 4($v1)
/* 07928C 8007868C AC6C0000 */  sw    $t4, ($v1)
/* 079290 80078690 8C830000 */  lw    $v1, ($a0)
/* 079294 80078694 00000000 */  nop   
/* 079298 80078698 246F0008 */  addiu $t7, $v1, 8
/* 07929C 8007869C AC8F0000 */  sw    $t7, ($a0)
/* 0792A0 800786A0 AC7F0004 */  sw    $ra, 4($v1)
/* 0792A4 800786A4 10000019 */  b     .L8007870C
/* 0792A8 800786A8 AC6D0000 */   sw    $t5, ($v1)
.L800786AC:
/* 0792AC 800786AC 8C830000 */  lw    $v1, ($a0)
/* 0792B0 800786B0 30D80FFF */  andi  $t8, $a2, 0xfff
/* 0792B4 800786B4 0018CB00 */  sll   $t9, $t8, 0xc
/* 0792B8 800786B8 032B7825 */  or    $t7, $t9, $t3
/* 0792BC 800786BC 246E0008 */  addiu $t6, $v1, 8
/* 0792C0 800786C0 AC8E0000 */  sw    $t6, ($a0)
/* 0792C4 800786C4 30580FFF */  andi  $t8, $v0, 0xfff
/* 0792C8 800786C8 0018CB00 */  sll   $t9, $t8, 0xc
/* 0792CC 800786CC 01E97025 */  or    $t6, $t7, $t1
/* 0792D0 800786D0 032A7825 */  or    $t7, $t9, $t2
/* 0792D4 800786D4 AC6F0004 */  sw    $t7, 4($v1)
/* 0792D8 800786D8 AC6E0000 */  sw    $t6, ($v1)
/* 0792DC 800786DC 8C830000 */  lw    $v1, ($a0)
/* 0792E0 800786E0 00000000 */  nop   
/* 0792E4 800786E4 246E0008 */  addiu $t6, $v1, 8
/* 0792E8 800786E8 AC8E0000 */  sw    $t6, ($a0)
/* 0792EC 800786EC AC600004 */  sw    $zero, 4($v1)
/* 0792F0 800786F0 AC6C0000 */  sw    $t4, ($v1)
/* 0792F4 800786F4 8C830000 */  lw    $v1, ($a0)
/* 0792F8 800786F8 00000000 */  nop   
/* 0792FC 800786FC 24780008 */  addiu $t8, $v1, 8
/* 079300 80078700 AC980000 */  sw    $t8, ($a0)
/* 079304 80078704 AC7F0004 */  sw    $ra, 4($v1)
/* 079308 80078708 AC6D0000 */  sw    $t5, ($v1)
.L8007870C:
/* 07930C 8007870C 00D1082A */  slt   $at, $a2, $s1
/* 079310 80078710 1420FFCB */  bnez  $at, .L80078640
/* 079314 80078714 00C01025 */   move  $v0, $a2
.L80078718:
/* 079318 80078718 8EF90000 */  lw    $t9, ($s7)
/* 07931C 8007871C 025E9021 */  addu  $s2, $s2, $fp
/* 079320 80078720 0256082A */  slt   $at, $s2, $s6
/* 079324 80078724 02797821 */  addu  $t7, $s3, $t9
/* 079328 80078728 1420FFBE */  bnez  $at, .L80078624
/* 07932C 8007872C 01F59824 */   and   $s3, $t7, $s5
.L80078730:
/* 079330 80078730 8C830000 */  lw    $v1, ($a0)
.L80078734:
/* 079334 80078734 3C18E700 */  lui   $t8, 0xe700
/* 079338 80078738 246E0008 */  addiu $t6, $v1, 8
/* 07933C 8007873C AC8E0000 */  sw    $t6, ($a0)
/* 079340 80078740 AC600004 */  sw    $zero, 4($v1)
/* 079344 80078744 AC780000 */  sw    $t8, ($v1)
/* 079348 80078748 8FBF003C */  lw    $ra, 0x3c($sp)
/* 07934C 8007874C 8FBE0038 */  lw    $fp, 0x38($sp)
/* 079350 80078750 8FB70034 */  lw    $s7, 0x34($sp)
/* 079354 80078754 8FB60030 */  lw    $s6, 0x30($sp)
/* 079358 80078758 8FB5002C */  lw    $s5, 0x2c($sp)
/* 07935C 8007875C 8FB40028 */  lw    $s4, 0x28($sp)
/* 079360 80078760 8FB30024 */  lw    $s3, 0x24($sp)
/* 079364 80078764 8FB20020 */  lw    $s2, 0x20($sp)
/* 079368 80078768 8FB1001C */  lw    $s1, 0x1c($sp)
/* 07936C 8007876C 8FB00018 */  lw    $s0, 0x18($sp)
/* 079370 80078770 03E00008 */  jr    $ra
/* 079374 80078774 27BD0040 */   addiu $sp, $sp, 0x40
