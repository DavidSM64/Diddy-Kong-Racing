glabel func_8008B758
/* 08C358 8008B758 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 08C35C 8008B75C AFBE0040 */  sw    $fp, 0x40($sp)
/* 08C360 8008B760 AFB7003C */  sw    $s7, 0x3c($sp)
/* 08C364 8008B764 AFB60038 */  sw    $s6, 0x38($sp)
/* 08C368 8008B768 AFB00020 */  sw    $s0, 0x20($sp)
/* 08C36C 8008B76C AFB50034 */  sw    $s5, 0x34($sp)
/* 08C370 8008B770 AFB40030 */  sw    $s4, 0x30($sp)
/* 08C374 8008B774 AFB3002C */  sw    $s3, 0x2c($sp)
/* 08C378 8008B778 3C108012 */  lui   $s0, %hi(D_801263C0) # $s0, 0x8012
/* 08C37C 8008B77C 3C168012 */  lui   $s6, %hi(gPlayersCharacterArray) # $s6, 0x8012
/* 08C380 8008B780 3C17800E */  lui   $s7, %hi(gNumberOfReadyPlayers) # $s7, 0x800e
/* 08C384 8008B784 3C1E8012 */  lui   $fp, %hi(D_801263CC) # $fp, 0x8012
/* 08C388 8008B788 AFBF0044 */  sw    $ra, 0x44($sp)
/* 08C38C 8008B78C AFB20028 */  sw    $s2, 0x28($sp)
/* 08C390 8008B790 AFB10024 */  sw    $s1, 0x24($sp)
/* 08C394 8008B794 27DE63CC */  addiu $fp, %lo(D_801263CC) # addiu $fp, $fp, 0x63cc
/* 08C398 8008B798 26F7F480 */  addiu $s7, %lo(gNumberOfReadyPlayers) # addiu $s7, $s7, -0xb80
/* 08C39C 8008B79C 26D663E8 */  addiu $s6, %lo(gPlayersCharacterArray) # addiu $s6, $s6, 0x63e8
/* 08C3A0 8008B7A0 261063C0 */  addiu $s0, %lo(D_801263C0) # addiu $s0, $s0, 0x63c0
/* 08C3A4 8008B7A4 2413000E */  li    $s3, 14
/* 08C3A8 8008B7A8 0000A025 */  move  $s4, $zero
/* 08C3AC 8008B7AC 24150014 */  li    $s5, 20
/* 08C3B0 8008B7B0 00801025 */  move  $v0, $a0
.L8008B7B4:
/* 08C3B4 8008B7B4 AFA2004C */  sw    $v0, 0x4c($sp)
/* 08C3B8 8008B7B8 804E0000 */  lb    $t6, ($v0)
/* 08C3BC 8008B7BC 3C0F8012 */  lui   $t7, %hi(D_801263DC) # $t7, 0x8012
/* 08C3C0 8008B7C0 11C000CD */  beqz  $t6, .L8008BAF8
/* 08C3C4 8008B7C4 25EF63DC */   addiu $t7, %lo(D_801263DC) # addiu $t7, $t7, 0x63dc
/* 08C3C8 8008B7C8 028F2821 */  addu  $a1, $s4, $t7
/* 08C3CC 8008B7CC 80B90000 */  lb    $t9, ($a1)
/* 08C3D0 8008B7D0 3C188012 */  lui   $t8, %hi(D_801267D8) # $t8, 0x8012
/* 08C3D4 8008B7D4 271867D8 */  addiu $t8, %lo(D_801267D8) # addiu $t8, $t8, 0x67d8
/* 08C3D8 8008B7D8 00143080 */  sll   $a2, $s4, 2
/* 08C3DC 8008B7DC 1320001E */  beqz  $t9, .L8008B858
/* 08C3E0 8008B7E0 00D81021 */   addu  $v0, $a2, $t8
/* 08C3E4 8008B7E4 8C480000 */  lw    $t0, ($v0)
/* 08C3E8 8008B7E8 3C0C8012 */  lui   $t4, %hi(D_80126808) # $t4, 0x8012
/* 08C3EC 8008B7EC 31094000 */  andi  $t1, $t0, 0x4000
/* 08C3F0 8008B7F0 112000C1 */  beqz  $t1, .L8008BAF8
/* 08C3F4 8008B7F4 258C6808 */   addiu $t4, %lo(D_80126808) # addiu $t4, $t4, 0x6808
/* 08C3F8 8008B7F8 8EEA0000 */  lw    $t2, ($s7)
/* 08C3FC 8008B7FC 00CC8821 */  addu  $s1, $a2, $t4
/* 08C400 8008B800 8E240000 */  lw    $a0, ($s1)
/* 08C404 8008B804 254BFFFF */  addiu $t3, $t2, -1
/* 08C408 8008B808 A0A00000 */  sb    $zero, ($a1)
/* 08C40C 8008B80C AEEB0000 */  sw    $t3, ($s7)
/* 08C410 8008B810 10800003 */  beqz  $a0, .L8008B820
/* 08C414 8008B814 02D49021 */   addu  $s2, $s6, $s4
/* 08C418 8008B818 0C001223 */  jal   func_8000488C
/* 08C41C 8008B81C 00000000 */   nop   
.L8008B820:
/* 08C420 8008B820 824E0000 */  lb    $t6, ($s2)
/* 08C424 8008B824 8FCD0000 */  lw    $t5, ($fp)
/* 08C428 8008B828 01D30019 */  multu $t6, $s3
/* 08C42C 8008B82C 02202825 */  move  $a1, $s1
/* 08C430 8008B830 00007812 */  mflo  $t7
/* 08C434 8008B834 01AFC021 */  addu  $t8, $t5, $t7
/* 08C438 8008B838 8704000C */  lh    $a0, 0xc($t8)
/* 08C43C 8008B83C 00000000 */  nop   
/* 08C440 8008B840 24840093 */  addiu $a0, $a0, 0x93
/* 08C444 8008B844 3099FFFF */  andi  $t9, $a0, 0xffff
/* 08C448 8008B848 0C000741 */  jal   func_80001D04
/* 08C44C 8008B84C 03202025 */   move  $a0, $t9
/* 08C450 8008B850 100000AA */  b     .L8008BAFC
/* 08C454 8008B854 8FA2004C */   lw    $v0, 0x4c($sp)
.L8008B858:
/* 08C458 8008B858 8C430000 */  lw    $v1, ($v0)
/* 08C45C 8008B85C 02D49021 */  addu  $s2, $s6, $s4
/* 08C460 8008B860 30684000 */  andi  $t0, $v1, 0x4000
/* 08C464 8008B864 1100003C */  beqz  $t0, .L8008B958
/* 08C468 8008B868 30789000 */   andi  $t8, $v1, 0x9000
/* 08C46C 8008B86C 3C09800E */  lui   $t1, %hi(gNumberOfActivePlayers) # $t1, 0x800e
/* 08C470 8008B870 8D29F4BC */  lw    $t1, %lo(gNumberOfActivePlayers)($t1)
/* 08C474 8008B874 3C01800E */  lui   $at, %hi(gNumberOfActivePlayers) # $at, 0x800e
/* 08C478 8008B878 252AFFFF */  addiu $t2, $t1, -1
/* 08C47C 8008B87C AC2AF4BC */  sw    $t2, %lo(gNumberOfActivePlayers)($at)
/* 08C480 8008B880 3C06800E */  lui   $a2, %hi(gNumberOfActivePlayers) # $a2, 0x800e
/* 08C484 8008B884 8CC6F4BC */  lw    $a2, %lo(gNumberOfActivePlayers)($a2)
/* 08C488 8008B888 3C018012 */  lui   $at, %hi(gActivePlayersArray) # $at, 0x8012
/* 08C48C 8008B88C 00340821 */  addu  $at, $at, $s4
/* 08C490 8008B890 18C00026 */  blez  $a2, .L8008B92C
/* 08C494 8008B894 A02063D4 */   sb    $zero, %lo(gActivePlayersArray)($at)
/* 08C498 8008B898 824C0000 */  lb    $t4, ($s2)
/* 08C49C 8008B89C 8FC50000 */  lw    $a1, ($fp)
/* 08C4A0 8008B8A0 01930019 */  multu $t4, $s3
/* 08C4A4 8008B8A4 3C0B8012 */  lui   $t3, %hi(D_801263B4) # $t3, 0x8012
/* 08C4A8 8008B8A8 816B63B4 */  lb    $t3, %lo(D_801263B4)($t3)
/* 08C4AC 8008B8AC 00007012 */  mflo  $t6
/* 08C4B0 8008B8B0 00AE6821 */  addu  $t5, $a1, $t6
/* 08C4B4 8008B8B4 85AF000C */  lh    $t7, 0xc($t5)
/* 08C4B8 8008B8B8 00000000 */  nop   
/* 08C4BC 8008B8BC 156F001C */  bne   $t3, $t7, .L8008B930
/* 08C4C0 8008B8C0 240BFFFF */   li    $t3, -1
/* 08C4C4 8008B8C4 82180001 */  lb    $t8, 1($s0)
/* 08C4C8 8008B8C8 00002025 */  move  $a0, $zero
/* 08C4CC 8008B8CC 1F000017 */  bgtz  $t8, .L8008B92C
/* 08C4D0 8008B8D0 00001825 */   move  $v1, $zero
/* 08C4D4 8008B8D4 3C198012 */  lui   $t9, %hi(gActivePlayersArray) # $t9, 0x8012
/* 08C4D8 8008B8D8 273963D4 */  addiu $t9, %lo(gActivePlayersArray) # addiu $t9, $t9, 0x63d4
/* 08C4DC 8008B8DC 00191021 */  addu  $v0, $zero, $t9
.L8008B8E0:
/* 08C4E0 8008B8E0 80480000 */  lb    $t0, ($v0)
/* 08C4E4 8008B8E4 02C34821 */  addu  $t1, $s6, $v1
/* 08C4E8 8008B8E8 1100000A */  beqz  $t0, .L8008B914
/* 08C4EC 8008B8EC 00000000 */   nop   
/* 08C4F0 8008B8F0 812A0000 */  lb    $t2, ($t1)
/* 08C4F4 8008B8F4 24040001 */  li    $a0, 1
/* 08C4F8 8008B8F8 01530019 */  multu $t2, $s3
/* 08C4FC 8008B8FC 00006012 */  mflo  $t4
/* 08C500 8008B900 00AC7021 */  addu  $t6, $a1, $t4
/* 08C504 8008B904 85CD000C */  lh    $t5, 0xc($t6)
/* 08C508 8008B908 A6000002 */  sh    $zero, 2($s0)
/* 08C50C 8008B90C A2150001 */  sb    $s5, 1($s0)
/* 08C510 8008B910 A20D0000 */  sb    $t5, ($s0)
.L8008B914:
/* 08C514 8008B914 24630001 */  addiu $v1, $v1, 1
/* 08C518 8008B918 28610004 */  slti  $at, $v1, 4
/* 08C51C 8008B91C 10200003 */  beqz  $at, .L8008B92C
/* 08C520 8008B920 24420001 */   addiu $v0, $v0, 1
/* 08C524 8008B924 1080FFEE */  beqz  $a0, .L8008B8E0
/* 08C528 8008B928 00000000 */   nop   
.L8008B92C:
/* 08C52C 8008B92C 240BFFFF */  li    $t3, -1
.L8008B930:
/* 08C530 8008B930 1CC00071 */  bgtz  $a2, .L8008BAF8
/* 08C534 8008B934 A24B0000 */   sb    $t3, ($s2)
/* 08C538 8008B938 240FFFFF */  li    $t7, -1
/* 08C53C 8008B93C 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08C540 8008B940 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 08C544 8008B944 AC2FF47C */  sw    $t7, %lo(gMenuDelay)($at)
/* 08C548 8008B948 0C030076 */  jal   func_800C01D8
/* 08C54C 8008B94C 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 08C550 8008B950 1000006A */  b     .L8008BAFC
/* 08C554 8008B954 8FA2004C */   lw    $v0, 0x4c($sp)
.L8008B958:
/* 08C558 8008B958 1300001A */  beqz  $t8, .L8008B9C4
/* 08C55C 8008B95C 24190001 */   li    $t9, 1
/* 08C560 8008B960 3C0A8012 */  lui   $t2, %hi(D_80126808) # $t2, 0x8012
/* 08C564 8008B964 254A6808 */  addiu $t2, %lo(D_80126808) # addiu $t2, $t2, 0x6808
/* 08C568 8008B968 8EE80000 */  lw    $t0, ($s7)
/* 08C56C 8008B96C 00CA8821 */  addu  $s1, $a2, $t2
/* 08C570 8008B970 8E240000 */  lw    $a0, ($s1)
/* 08C574 8008B974 25090001 */  addiu $t1, $t0, 1
/* 08C578 8008B978 A0B90000 */  sb    $t9, ($a1)
/* 08C57C 8008B97C 10800003 */  beqz  $a0, .L8008B98C
/* 08C580 8008B980 AEE90000 */   sw    $t1, ($s7)
/* 08C584 8008B984 0C001223 */  jal   func_8000488C
/* 08C588 8008B988 00000000 */   nop   
.L8008B98C:
/* 08C58C 8008B98C 824E0000 */  lb    $t6, ($s2)
/* 08C590 8008B990 8FCC0000 */  lw    $t4, ($fp)
/* 08C594 8008B994 01D30019 */  multu $t6, $s3
/* 08C598 8008B998 02202825 */  move  $a1, $s1
/* 08C59C 8008B99C 00006812 */  mflo  $t5
/* 08C5A0 8008B9A0 018D5821 */  addu  $t3, $t4, $t5
/* 08C5A4 8008B9A4 8564000C */  lh    $a0, 0xc($t3)
/* 08C5A8 8008B9A8 00000000 */  nop   
/* 08C5AC 8008B9AC 24840087 */  addiu $a0, $a0, 0x87
/* 08C5B0 8008B9B0 308FFFFF */  andi  $t7, $a0, 0xffff
/* 08C5B4 8008B9B4 0C000741 */  jal   func_80001D04
/* 08C5B8 8008B9B8 01E02025 */   move  $a0, $t7
/* 08C5BC 8008B9BC 1000004F */  b     .L8008BAFC
/* 08C5C0 8008B9C0 8FA2004C */   lw    $v0, 0x4c($sp)
.L8008B9C4:
/* 08C5C4 8008B9C4 82580000 */  lb    $t8, ($s2)
/* 08C5C8 8008B9C8 00141840 */  sll   $v1, $s4, 1
/* 08C5CC 8008B9CC 03130019 */  multu $t8, $s3
/* 08C5D0 8008B9D0 3C048012 */  lui   $a0, %hi(D_80126830) # $a0, 0x8012
/* 08C5D4 8008B9D4 00832021 */  addu  $a0, $a0, $v1
/* 08C5D8 8008B9D8 8FC50000 */  lw    $a1, ($fp)
/* 08C5DC 8008B9DC 84846830 */  lh    $a0, %lo(D_80126830)($a0)
/* 08C5E0 8008B9E0 24060002 */  li    $a2, 2
/* 08C5E4 8008B9E4 240700EC */  li    $a3, 236
/* 08C5E8 8008B9E8 2419015C */  li    $t9, 348
/* 08C5EC 8008B9EC 00001012 */  mflo  $v0
/* 08C5F0 8008B9F0 00458821 */  addu  $s1, $v0, $a1
/* 08C5F4 8008B9F4 1880000B */  blez  $a0, .L8008BA24
/* 08C5F8 8008B9F8 00000000 */   nop   
/* 08C5FC 8008B9FC 02802025 */  move  $a0, $s4
/* 08C600 8008BA00 02202825 */  move  $a1, $s1
/* 08C604 8008BA04 0C022FFA */  jal   func_8008BFE8
/* 08C608 8008BA08 AFB90010 */   sw    $t9, 0x10($sp)
/* 08C60C 8008BA0C 82420000 */  lb    $v0, ($s2)
/* 08C610 8008BA10 8FC50000 */  lw    $a1, ($fp)
/* 08C614 8008BA14 000240C0 */  sll   $t0, $v0, 3
/* 08C618 8008BA18 01024023 */  subu  $t0, $t0, $v0
/* 08C61C 8008BA1C 1000002D */  b     .L8008BAD4
/* 08C620 8008BA20 00081040 */   sll   $v0, $t0, 1
.L8008BA24:
/* 08C624 8008BA24 0481000D */  bgez  $a0, .L8008BA5C
/* 08C628 8008BA28 24060002 */   li    $a2, 2
/* 08C62C 8008BA2C 2409015C */  li    $t1, 348
/* 08C630 8008BA30 AFA90010 */  sw    $t1, 0x10($sp)
/* 08C634 8008BA34 02802025 */  move  $a0, $s4
/* 08C638 8008BA38 26250002 */  addiu $a1, $s1, 2
/* 08C63C 8008BA3C 0C022FFA */  jal   func_8008BFE8
/* 08C640 8008BA40 240700EC */   li    $a3, 236
/* 08C644 8008BA44 82420000 */  lb    $v0, ($s2)
/* 08C648 8008BA48 8FC50000 */  lw    $a1, ($fp)
/* 08C64C 8008BA4C 000250C0 */  sll   $t2, $v0, 3
/* 08C650 8008BA50 01425023 */  subu  $t2, $t2, $v0
/* 08C654 8008BA54 1000001F */  b     .L8008BAD4
/* 08C658 8008BA58 000A1040 */   sll   $v0, $t2, 1
.L8008BA5C:
/* 08C65C 8008BA5C 3C048012 */  lui   $a0, %hi(D_80126818) # $a0, 0x8012
/* 08C660 8008BA60 00832021 */  addu  $a0, $a0, $v1
/* 08C664 8008BA64 84846818 */  lh    $a0, %lo(D_80126818)($a0)
/* 08C668 8008BA68 24060004 */  li    $a2, 4
/* 08C66C 8008BA6C 0481000C */  bgez  $a0, .L8008BAA0
/* 08C670 8008BA70 240700EC */   li    $a3, 236
/* 08C674 8008BA74 240E015C */  li    $t6, 348
/* 08C678 8008BA78 AFAE0010 */  sw    $t6, 0x10($sp)
/* 08C67C 8008BA7C 02802025 */  move  $a0, $s4
/* 08C680 8008BA80 0C022FFA */  jal   func_8008BFE8
/* 08C684 8008BA84 26250004 */   addiu $a1, $s1, 4
/* 08C688 8008BA88 82420000 */  lb    $v0, ($s2)
/* 08C68C 8008BA8C 8FC50000 */  lw    $a1, ($fp)
/* 08C690 8008BA90 000260C0 */  sll   $t4, $v0, 3
/* 08C694 8008BA94 01826023 */  subu  $t4, $t4, $v0
/* 08C698 8008BA98 1000000E */  b     .L8008BAD4
/* 08C69C 8008BA9C 000C1040 */   sll   $v0, $t4, 1
.L8008BAA0:
/* 08C6A0 8008BAA0 1880000C */  blez  $a0, .L8008BAD4
/* 08C6A4 8008BAA4 24060004 */   li    $a2, 4
/* 08C6A8 8008BAA8 240D015C */  li    $t5, 348
/* 08C6AC 8008BAAC AFAD0010 */  sw    $t5, 0x10($sp)
/* 08C6B0 8008BAB0 02802025 */  move  $a0, $s4
/* 08C6B4 8008BAB4 26250008 */  addiu $a1, $s1, 8
/* 08C6B8 8008BAB8 0C022FFA */  jal   func_8008BFE8
/* 08C6BC 8008BABC 240700EC */   li    $a3, 236
/* 08C6C0 8008BAC0 82420000 */  lb    $v0, ($s2)
/* 08C6C4 8008BAC4 8FC50000 */  lw    $a1, ($fp)
/* 08C6C8 8008BAC8 000258C0 */  sll   $t3, $v0, 3
/* 08C6CC 8008BACC 01625823 */  subu  $t3, $t3, $v0
/* 08C6D0 8008BAD0 000B1040 */  sll   $v0, $t3, 1
.L8008BAD4:
/* 08C6D4 8008BAD4 00A27821 */  addu  $t7, $a1, $v0
/* 08C6D8 8008BAD8 85E3000C */  lh    $v1, 0xc($t7)
/* 08C6DC 8008BADC 8638000C */  lh    $t8, 0xc($s1)
/* 08C6E0 8008BAE0 00000000 */  nop   
/* 08C6E4 8008BAE4 13030005 */  beq   $t8, $v1, .L8008BAFC
/* 08C6E8 8008BAE8 8FA2004C */   lw    $v0, 0x4c($sp)
/* 08C6EC 8008BAEC A2030000 */  sb    $v1, ($s0)
/* 08C6F0 8008BAF0 A6000002 */  sh    $zero, 2($s0)
/* 08C6F4 8008BAF4 A2150001 */  sb    $s5, 1($s0)
.L8008BAF8:
/* 08C6F8 8008BAF8 8FA2004C */  lw    $v0, 0x4c($sp)
.L8008BAFC:
/* 08C6FC 8008BAFC 26940001 */  addiu $s4, $s4, 1
/* 08C700 8008BB00 24010004 */  li    $at, 4
/* 08C704 8008BB04 1681FF2B */  bne   $s4, $at, .L8008B7B4
/* 08C708 8008BB08 24420001 */   addiu $v0, $v0, 1
/* 08C70C 8008BB0C 8FBF0044 */  lw    $ra, 0x44($sp)
/* 08C710 8008BB10 8FB00020 */  lw    $s0, 0x20($sp)
/* 08C714 8008BB14 8FB10024 */  lw    $s1, 0x24($sp)
/* 08C718 8008BB18 8FB20028 */  lw    $s2, 0x28($sp)
/* 08C71C 8008BB1C 8FB3002C */  lw    $s3, 0x2c($sp)
/* 08C720 8008BB20 8FB40030 */  lw    $s4, 0x30($sp)
/* 08C724 8008BB24 8FB50034 */  lw    $s5, 0x34($sp)
/* 08C728 8008BB28 8FB60038 */  lw    $s6, 0x38($sp)
/* 08C72C 8008BB2C 8FB7003C */  lw    $s7, 0x3c($sp)
/* 08C730 8008BB30 8FBE0040 */  lw    $fp, 0x40($sp)
/* 08C734 8008BB34 03E00008 */  jr    $ra
/* 08C738 8008BB38 27BD0060 */   addiu $sp, $sp, 0x60

