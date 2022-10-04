glabel randomise_ai_racer_slots
/* 08C73C 8008BB3C 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 08C740 8008BB40 AFBF0034 */  sw    $ra, 0x34($sp)
/* 08C744 8008BB44 AFB60030 */  sw    $s6, 0x30($sp)
/* 08C748 8008BB48 AFB00018 */  sw    $s0, 0x18($sp)
/* 08C74C 8008BB4C 00808025 */  move  $s0, $a0
/* 08C750 8008BB50 AFB5002C */  sw    $s5, 0x2c($sp)
/* 08C754 8008BB54 AFB40028 */  sw    $s4, 0x28($sp)
/* 08C758 8008BB58 AFB30024 */  sw    $s3, 0x24($sp)
/* 08C75C 8008BB5C AFB20020 */  sw    $s2, 0x20($sp)
/* 08C760 8008BB60 AFB1001C */  sw    $s1, 0x1c($sp)
/* 08C764 8008BB64 0C027B34 */  jal   is_drumstick_unlocked
/* 08C768 8008BB68 24160007 */   li    $s6, 7
/* 08C76C 8008BB6C 10400002 */  beqz  $v0, .L8008BB78
/* 08C770 8008BB70 00000000 */   nop   
/* 08C774 8008BB74 24160008 */  li    $s6, 8
.L8008BB78:
/* 08C778 8008BB78 0C027B2E */  jal   is_tt_unlocked
/* 08C77C 8008BB7C 00000000 */   nop   
/* 08C780 8008BB80 10400002 */  beqz  $v0, .L8008BB8C
/* 08C784 8008BB84 2A010008 */   slti  $at, $s0, 8
/* 08C788 8008BB88 26D60001 */  addiu $s6, $s6, 1
.L8008BB8C:
/* 08C78C 8008BB8C 10200017 */  beqz  $at, .L8008BBEC
/* 08C790 8008BB90 3C188012 */   lui   $t8, %hi(gCharacterIdSlots) # $t8, 0x8012
/* 08C794 8008BB94 1A00000F */  blez  $s0, .L8008BBD4
/* 08C798 8008BB98 00008825 */   move  $s1, $zero
/* 08C79C 8008BB9C 3C0E8012 */  lui   $t6, %hi(gCharacterIdSlots) # $t6, 0x8012
/* 08C7A0 8008BBA0 25CE63F0 */  addiu $t6, %lo(gCharacterIdSlots) # addiu $t6, $t6, 0x63f0
/* 08C7A4 8008BBA4 000E9821 */  addu  $s3, $zero, $t6
/* 08C7A8 8008BBA8 020E1021 */  addu  $v0, $s0, $t6
/* 08C7AC 8008BBAC 24030009 */  li    $v1, 9
.L8008BBB0:
/* 08C7B0 8008BBB0 826F0000 */  lb    $t7, ($s3)
/* 08C7B4 8008BBB4 26730001 */  addiu $s3, $s3, 1
/* 08C7B8 8008BBB8 146F0002 */  bne   $v1, $t7, .L8008BBC4
/* 08C7BC 8008BBBC 0262082B */   sltu  $at, $s3, $v0
/* 08C7C0 8008BBC0 24110001 */  li    $s1, 1
.L8008BBC4:
/* 08C7C4 8008BBC4 10200003 */  beqz  $at, .L8008BBD4
/* 08C7C8 8008BBC8 00000000 */   nop   
/* 08C7CC 8008BBCC 1220FFF8 */  beqz  $s1, .L8008BBB0
/* 08C7D0 8008BBD0 00000000 */   nop   
.L8008BBD4:
/* 08C7D4 8008BBD4 16200005 */  bnez  $s1, .L8008BBEC
/* 08C7D8 8008BBD8 24030009 */   li    $v1, 9
/* 08C7DC 8008BBDC 3C018012 */  lui   $at, %hi(gCharacterIdSlots) # $at, 0x8012
/* 08C7E0 8008BBE0 00300821 */  addu  $at, $at, $s0
/* 08C7E4 8008BBE4 A02363F0 */  sb    $v1, %lo(gCharacterIdSlots)($at)
/* 08C7E8 8008BBE8 26100001 */  addiu $s0, $s0, 1
.L8008BBEC:
/* 08C7EC 8008BBEC 2A010008 */  slti  $at, $s0, 8
/* 08C7F0 8008BBF0 10200042 */  beqz  $at, .L8008BCFC
/* 08C7F4 8008BBF4 02009025 */   move  $s2, $s0
/* 08C7F8 8008BBF8 271863F0 */  addiu $t8, %lo(gCharacterIdSlots) # addiu $t8, $t8, 0x63f0
/* 08C7FC 8008BBFC 3C148012 */  lui   $s4, %hi(gCurrCharacterSelectData) # $s4, 0x8012
/* 08C800 8008BC00 269463CC */  addiu $s4, %lo(gCurrCharacterSelectData) # addiu $s4, $s4, 0x63cc
/* 08C804 8008BC04 02189821 */  addu  $s3, $s0, $t8
/* 08C808 8008BC08 2415000E */  li    $s5, 14
.L8008BC0C:
/* 08C80C 8008BC0C 00002025 */  move  $a0, $zero
.L8008BC10:
/* 08C810 8008BC10 02C02825 */  move  $a1, $s6
/* 08C814 8008BC14 00008825 */  move  $s1, $zero
/* 08C818 8008BC18 0C01BE53 */  jal   get_random_number_from_range
/* 08C81C 8008BC1C 00008025 */   move  $s0, $zero
/* 08C820 8008BC20 00550019 */  multu $v0, $s5
/* 08C824 8008BC24 8E990000 */  lw    $t9, ($s4)
/* 08C828 8008BC28 32450003 */  andi  $a1, $s2, 3
/* 08C82C 8008BC2C 00004012 */  mflo  $t0
/* 08C830 8008BC30 03284821 */  addu  $t1, $t9, $t0
/* 08C834 8008BC34 852A000C */  lh    $t2, 0xc($t1)
/* 08C838 8008BC38 1A40002A */  blez  $s2, .L8008BCE4
/* 08C83C 8008BC3C A26A0000 */   sb    $t2, ($s3)
/* 08C840 8008BC40 10A0000D */  beqz  $a1, .L8008BC78
/* 08C844 8008BC44 00A02025 */   move  $a0, $a1
/* 08C848 8008BC48 3C0B8012 */  lui   $t3, %hi(gCharacterIdSlots) # $t3, 0x8012
/* 08C84C 8008BC4C 256B63F0 */  addiu $t3, %lo(gCharacterIdSlots) # addiu $t3, $t3, 0x63f0
/* 08C850 8008BC50 82630000 */  lb    $v1, ($s3)
/* 08C854 8008BC54 020B1021 */  addu  $v0, $s0, $t3
.L8008BC58:
/* 08C858 8008BC58 804C0000 */  lb    $t4, ($v0)
/* 08C85C 8008BC5C 26100001 */  addiu $s0, $s0, 1
/* 08C860 8008BC60 15830002 */  bne   $t4, $v1, .L8008BC6C
/* 08C864 8008BC64 00000000 */   nop   
/* 08C868 8008BC68 24110001 */  li    $s1, 1
.L8008BC6C:
/* 08C86C 8008BC6C 1490FFFA */  bne   $a0, $s0, .L8008BC58
/* 08C870 8008BC70 24420001 */   addiu $v0, $v0, 1
/* 08C874 8008BC74 1212001B */  beq   $s0, $s2, .L8008BCE4
.L8008BC78:
/* 08C878 8008BC78 3C0D8012 */   lui   $t5, %hi(gCharacterIdSlots) # $t5, 0x8012
/* 08C87C 8008BC7C 25AD63F0 */  addiu $t5, %lo(gCharacterIdSlots) # addiu $t5, $t5, 0x63f0
/* 08C880 8008BC80 82630000 */  lb    $v1, ($s3)
/* 08C884 8008BC84 020D1021 */  addu  $v0, $s0, $t5
/* 08C888 8008BC88 024D2021 */  addu  $a0, $s2, $t5
.L8008BC8C:
/* 08C88C 8008BC8C 804E0000 */  lb    $t6, ($v0)
/* 08C890 8008BC90 00000000 */  nop   
/* 08C894 8008BC94 15C30002 */  bne   $t6, $v1, .L8008BCA0
/* 08C898 8008BC98 00000000 */   nop   
/* 08C89C 8008BC9C 24110001 */  li    $s1, 1
.L8008BCA0:
/* 08C8A0 8008BCA0 804F0001 */  lb    $t7, 1($v0)
/* 08C8A4 8008BCA4 00000000 */  nop   
/* 08C8A8 8008BCA8 15E30002 */  bne   $t7, $v1, .L8008BCB4
/* 08C8AC 8008BCAC 00000000 */   nop   
/* 08C8B0 8008BCB0 24110001 */  li    $s1, 1
.L8008BCB4:
/* 08C8B4 8008BCB4 80580002 */  lb    $t8, 2($v0)
/* 08C8B8 8008BCB8 00000000 */  nop   
/* 08C8BC 8008BCBC 17030002 */  bne   $t8, $v1, .L8008BCC8
/* 08C8C0 8008BCC0 00000000 */   nop   
/* 08C8C4 8008BCC4 24110001 */  li    $s1, 1
.L8008BCC8:
/* 08C8C8 8008BCC8 80590003 */  lb    $t9, 3($v0)
/* 08C8CC 8008BCCC 24420004 */  addiu $v0, $v0, 4
/* 08C8D0 8008BCD0 17230002 */  bne   $t9, $v1, .L8008BCDC
/* 08C8D4 8008BCD4 00000000 */   nop   
/* 08C8D8 8008BCD8 24110001 */  li    $s1, 1
.L8008BCDC:
/* 08C8DC 8008BCDC 1444FFEB */  bne   $v0, $a0, .L8008BC8C
/* 08C8E0 8008BCE0 00000000 */   nop   
.L8008BCE4:
/* 08C8E4 8008BCE4 1620FFCA */  bnez  $s1, .L8008BC10
/* 08C8E8 8008BCE8 00002025 */   move  $a0, $zero
/* 08C8EC 8008BCEC 26520001 */  addiu $s2, $s2, 1
/* 08C8F0 8008BCF0 24010008 */  li    $at, 8
/* 08C8F4 8008BCF4 1641FFC5 */  bne   $s2, $at, .L8008BC0C
/* 08C8F8 8008BCF8 26730001 */   addiu $s3, $s3, 1
.L8008BCFC:
/* 08C8FC 8008BCFC 8FBF0034 */  lw    $ra, 0x34($sp)
/* 08C900 8008BD00 8FB00018 */  lw    $s0, 0x18($sp)
/* 08C904 8008BD04 8FB1001C */  lw    $s1, 0x1c($sp)
/* 08C908 8008BD08 8FB20020 */  lw    $s2, 0x20($sp)
/* 08C90C 8008BD0C 8FB30024 */  lw    $s3, 0x24($sp)
/* 08C910 8008BD10 8FB40028 */  lw    $s4, 0x28($sp)
/* 08C914 8008BD14 8FB5002C */  lw    $s5, 0x2c($sp)
/* 08C918 8008BD18 8FB60030 */  lw    $s6, 0x30($sp)
/* 08C91C 8008BD1C 03E00008 */  jr    $ra
/* 08C920 8008BD20 27BD0038 */   addiu $sp, $sp, 0x38

