glabel func_8005CB68
/* 05D768 8005CB68 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 05D76C 8005CB6C AFBF001C */  sw    $ra, 0x1c($sp)
/* 05D770 8005CB70 AFB00018 */  sw    $s0, 0x18($sp)
/* 05D774 8005CB74 AFA40048 */  sw    $a0, 0x48($sp)
/* 05D778 8005CB78 AFA5004C */  sw    $a1, 0x4c($sp)
/* 05D77C 8005CB7C 80AF0000 */  lb    $t7, ($a1)
/* 05D780 8005CB80 0C01BAA4 */  jal   get_settings
/* 05D784 8005CB84 A3AF0043 */   sb    $t7, 0x43($sp)
/* 05D788 8005CB88 90580048 */  lbu   $t8, 0x48($v0)
/* 05D78C 8005CB8C 24190001 */  li    $t9, 1
/* 05D790 8005CB90 03194804 */  sllv  $t1, $t9, $t8
/* 05D794 8005CB94 AFA90038 */  sw    $t1, 0x38($sp)
/* 05D798 8005CB98 AFA20044 */  sw    $v0, 0x44($sp)
/* 05D79C 8005CB9C 0C0078A7 */  jal   get_misc_asset
/* 05D7A0 8005CBA0 24040044 */   li    $a0, 68
/* 05D7A4 8005CBA4 804C0005 */  lb    $t4, 5($v0)
/* 05D7A8 8005CBA8 24040043 */  li    $a0, 67
/* 05D7AC 8005CBAC AFAC002C */  sw    $t4, 0x2c($sp)
/* 05D7B0 8005CBB0 804D0006 */  lb    $t5, 6($v0)
/* 05D7B4 8005CBB4 00000000 */  nop   
/* 05D7B8 8005CBB8 AFAD0028 */  sw    $t5, 0x28($sp)
/* 05D7BC 8005CBBC 804E0007 */  lb    $t6, 7($v0)
/* 05D7C0 8005CBC0 0C0078A7 */  jal   get_misc_asset
/* 05D7C4 8005CBC4 AFAE0024 */   sw    $t6, 0x24($sp)
/* 05D7C8 8005CBC8 8FAA0044 */  lw    $t2, 0x44($sp)
/* 05D7CC 8005CBCC 804F0000 */  lb    $t7, ($v0)
/* 05D7D0 8005CBD0 91440049 */  lbu   $a0, 0x49($t2)
/* 05D7D4 8005CBD4 8FA90038 */  lw    $t1, 0x38($sp)
/* 05D7D8 8005CBD8 00402825 */  move  $a1, $v0
/* 05D7DC 8005CBDC 108F0006 */  beq   $a0, $t7, .L8005CBF8
/* 05D7E0 8005CBE0 00008025 */   move  $s0, $zero
/* 05D7E4 8005CBE4 00A01825 */  move  $v1, $a1
.L8005CBE8:
/* 05D7E8 8005CBE8 80790002 */  lb    $t9, 2($v1)
/* 05D7EC 8005CBEC 26100002 */  addiu $s0, $s0, 2
/* 05D7F0 8005CBF0 1499FFFD */  bne   $a0, $t9, .L8005CBE8
/* 05D7F4 8005CBF4 24630002 */   addiu $v1, $v1, 2
.L8005CBF8:
/* 05D7F8 8005CBF8 8FAC0048 */  lw    $t4, 0x48($sp)
/* 05D7FC 8005CBFC 83AE0043 */  lb    $t6, 0x43($sp)
/* 05D800 8005CC00 858D01AC */  lh    $t5, 0x1ac($t4)
/* 05D804 8005CC04 0202C021 */  addu  $t8, $s0, $v0
/* 05D808 8005CC08 24030001 */  li    $v1, 1
/* 05D80C 8005CC0C 83100001 */  lb    $s0, 1($t8)
/* 05D810 8005CC10 15C30105 */  bne   $t6, $v1, .L8005D028
/* 05D814 8005CC14 AFAD0034 */   sw    $t5, 0x34($sp)
/* 05D818 8005CC18 15A30009 */  bne   $t5, $v1, .L8005CC40
/* 05D81C 8005CC1C 2404003E */   li    $a0, 62
/* 05D820 8005CC20 2404003D */  li    $a0, 61
/* 05D824 8005CC24 AFA90038 */  sw    $t1, 0x38($sp)
/* 05D828 8005CC28 0C0002CD */  jal   play_music
/* 05D82C 8005CC2C AFAA0044 */   sw    $t2, 0x44($sp)
/* 05D830 8005CC30 8FA90038 */  lw    $t1, 0x38($sp)
/* 05D834 8005CC34 8FAA0044 */  lw    $t2, 0x44($sp)
/* 05D838 8005CC38 10000008 */  b     .L8005CC5C
/* 05D83C 8005CC3C 91430048 */   lbu   $v1, 0x48($t2)
.L8005CC40:
/* 05D840 8005CC40 AFA90038 */  sw    $t1, 0x38($sp)
/* 05D844 8005CC44 0C0002CD */  jal   play_music
/* 05D848 8005CC48 AFAA0044 */   sw    $t2, 0x44($sp)
/* 05D84C 8005CC4C 8FA90038 */  lw    $t1, 0x38($sp)
/* 05D850 8005CC50 8FAA0044 */  lw    $t2, 0x44($sp)
/* 05D854 8005CC54 00000000 */  nop   
/* 05D858 8005CC58 91430048 */  lbu   $v1, 0x48($t2)
.L8005CC5C:
/* 05D85C 8005CC5C 8FA80034 */  lw    $t0, 0x34($sp)
/* 05D860 8005CC60 10600002 */  beqz  $v1, .L8005CC6C
/* 05D864 8005CC64 24010005 */   li    $at, 5
/* 05D868 8005CC68 14610063 */  bne   $v1, $at, .L8005CDF8
.L8005CC6C:
/* 05D86C 8005CC6C 240B0001 */   li    $t3, 1
/* 05D870 8005CC70 150B000E */  bne   $t0, $t3, .L8005CCAC
/* 05D874 8005CC74 00000000 */   nop   
/* 05D878 8005CC78 954F000C */  lhu   $t7, 0xc($t2)
/* 05D87C 8005CC7C 914C0049 */  lbu   $t4, 0x49($t2)
/* 05D880 8005CC80 8D580004 */  lw    $t8, 4($t2)
/* 05D884 8005CC84 01E9C825 */  or    $t9, $t7, $t1
/* 05D888 8005CC88 000C7080 */  sll   $t6, $t4, 2
/* 05D88C 8005CC8C A559000C */  sh    $t9, 0xc($t2)
/* 05D890 8005CC90 030E1021 */  addu  $v0, $t8, $t6
/* 05D894 8005CC94 8C4D0000 */  lw    $t5, ($v0)
/* 05D898 8005CC98 00000000 */  nop   
/* 05D89C 8005CC9C 35AF0002 */  ori   $t7, $t5, 2
/* 05D8A0 8005CCA0 AC4F0000 */  sw    $t7, ($v0)
/* 05D8A4 8005CCA4 91430048 */  lbu   $v1, 0x48($t2)
/* 05D8A8 8005CCA8 00000000 */  nop   
.L8005CCAC:
/* 05D8AC 8005CCAC 1460001F */  bnez  $v1, .L8005CD2C
/* 05D8B0 8005CCB0 00000000 */   nop   
/* 05D8B4 8005CCB4 150B0012 */  bne   $t0, $t3, .L8005CD00
/* 05D8B8 8005CCB8 2404FFF6 */   li    $a0, -10
/* 05D8BC 8005CCBC 2404FFFE */  li    $a0, -2
/* 05D8C0 8005CCC0 00002825 */  move  $a1, $zero
/* 05D8C4 8005CCC4 00003025 */  move  $a2, $zero
/* 05D8C8 8005CCC8 0C01B06B */  jal   push_level_property_stack
/* 05D8CC 8005CCCC 00003825 */   move  $a3, $zero
/* 05D8D0 8005CCD0 8FA4002C */  lw    $a0, 0x2c($sp)
/* 05D8D4 8005CCD4 00002825 */  move  $a1, $zero
/* 05D8D8 8005CCD8 2406FFFF */  li    $a2, -1
/* 05D8DC 8005CCDC 0C01B06B */  jal   push_level_property_stack
/* 05D8E0 8005CCE0 00003825 */   move  $a3, $zero
/* 05D8E4 8005CCE4 02002025 */  move  $a0, $s0
/* 05D8E8 8005CCE8 00002825 */  move  $a1, $zero
/* 05D8EC 8005CCEC 2406FFFF */  li    $a2, -1
/* 05D8F0 8005CCF0 0C01B06B */  jal   push_level_property_stack
/* 05D8F4 8005CCF4 24070001 */   li    $a3, 1
/* 05D8F8 8005CCF8 10000031 */  b     .L8005CDC0
/* 05D8FC 8005CCFC 8FB90034 */   lw    $t9, 0x34($sp)
.L8005CD00:
/* 05D900 8005CD00 00002825 */  move  $a1, $zero
/* 05D904 8005CD04 00003025 */  move  $a2, $zero
/* 05D908 8005CD08 0C01B06B */  jal   push_level_property_stack
/* 05D90C 8005CD0C 00003825 */   move  $a3, $zero
/* 05D910 8005CD10 02002025 */  move  $a0, $s0
/* 05D914 8005CD14 00002825 */  move  $a1, $zero
/* 05D918 8005CD18 2406FFFF */  li    $a2, -1
/* 05D91C 8005CD1C 0C01B06B */  jal   push_level_property_stack
/* 05D920 8005CD20 24070002 */   li    $a3, 2
/* 05D924 8005CD24 10000026 */  b     .L8005CDC0
/* 05D928 8005CD28 8FB90034 */   lw    $t9, 0x34($sp)
.L8005CD2C:
/* 05D92C 8005CD2C 150B001A */  bne   $t0, $t3, .L8005CD98
/* 05D930 8005CD30 2404FFF6 */   li    $a0, -10
/* 05D934 8005CD34 24040000 */  li    $a0, 0
/* 05D938 8005CD38 0C027A9E */  jal   set_eeprom_settings_value
/* 05D93C 8005CD3C 24050001 */   li    $a1, 1
/* 05D940 8005CD40 2404FFFE */  li    $a0, -2
/* 05D944 8005CD44 00002825 */  move  $a1, $zero
/* 05D948 8005CD48 00003025 */  move  $a2, $zero
/* 05D94C 8005CD4C 0C01B06B */  jal   push_level_property_stack
/* 05D950 8005CD50 00003825 */   move  $a3, $zero
/* 05D954 8005CD54 8FA40024 */  lw    $a0, 0x24($sp)
/* 05D958 8005CD58 00002825 */  move  $a1, $zero
/* 05D95C 8005CD5C 2406FFFF */  li    $a2, -1
/* 05D960 8005CD60 0C01B06B */  jal   push_level_property_stack
/* 05D964 8005CD64 00003825 */   move  $a3, $zero
/* 05D968 8005CD68 8FA40028 */  lw    $a0, 0x28($sp)
/* 05D96C 8005CD6C 00002825 */  move  $a1, $zero
/* 05D970 8005CD70 2406FFFF */  li    $a2, -1
/* 05D974 8005CD74 0C01B06B */  jal   push_level_property_stack
/* 05D978 8005CD78 00003825 */   move  $a3, $zero
/* 05D97C 8005CD7C 02002025 */  move  $a0, $s0
/* 05D980 8005CD80 00002825 */  move  $a1, $zero
/* 05D984 8005CD84 2406FFFF */  li    $a2, -1
/* 05D988 8005CD88 0C01B06B */  jal   push_level_property_stack
/* 05D98C 8005CD8C 24070001 */   li    $a3, 1
/* 05D990 8005CD90 1000000B */  b     .L8005CDC0
/* 05D994 8005CD94 8FB90034 */   lw    $t9, 0x34($sp)
.L8005CD98:
/* 05D998 8005CD98 00002825 */  move  $a1, $zero
/* 05D99C 8005CD9C 00003025 */  move  $a2, $zero
/* 05D9A0 8005CDA0 0C01B06B */  jal   push_level_property_stack
/* 05D9A4 8005CDA4 00003825 */   move  $a3, $zero
/* 05D9A8 8005CDA8 02002025 */  move  $a0, $s0
/* 05D9AC 8005CDAC 00002825 */  move  $a1, $zero
/* 05D9B0 8005CDB0 2406FFFF */  li    $a2, -1
/* 05D9B4 8005CDB4 0C01B06B */  jal   push_level_property_stack
/* 05D9B8 8005CDB8 24070002 */   li    $a3, 2
/* 05D9BC 8005CDBC 8FB90034 */  lw    $t9, 0x34($sp)
.L8005CDC0:
/* 05D9C0 8005CDC0 24010001 */  li    $at, 1
/* 05D9C4 8005CDC4 17210005 */  bne   $t9, $at, .L8005CDDC
/* 05D9C8 8005CDC8 00000000 */   nop   
/* 05D9CC 8005CDCC 0C01BC50 */  jal   func_8006F140
/* 05D9D0 8005CDD0 24040004 */   li    $a0, 4
/* 05D9D4 8005CDD4 10000004 */  b     .L8005CDE8
/* 05D9D8 8005CDD8 83A20043 */   lb    $v0, 0x43($sp)
.L8005CDDC:
/* 05D9DC 8005CDDC 0C01BC50 */  jal   func_8006F140
/* 05D9E0 8005CDE0 24040003 */   li    $a0, 3
/* 05D9E4 8005CDE4 83A20043 */  lb    $v0, 0x43($sp)
.L8005CDE8:
/* 05D9E8 8005CDE8 8FAE004C */  lw    $t6, 0x4c($sp)
/* 05D9EC 8005CDEC 24580001 */  addiu $t8, $v0, 1
/* 05D9F0 8005CDF0 10000091 */  b     .L8005D038
/* 05D9F4 8005CDF4 A1D80000 */   sb    $t8, ($t6)
.L8005CDF8:
/* 05D9F8 8005CDF8 914F0049 */  lbu   $t7, 0x49($t2)
/* 05D9FC 8005CDFC 8D4D0004 */  lw    $t5, 4($t2)
/* 05DA00 8005CE00 000FC880 */  sll   $t9, $t7, 2
/* 05DA04 8005CE04 01B91021 */  addu  $v0, $t5, $t9
/* 05DA08 8005CE08 8C430000 */  lw    $v1, ($v0)
/* 05DA0C 8005CE0C 8FB80034 */  lw    $t8, 0x34($sp)
/* 05DA10 8005CE10 306C0002 */  andi  $t4, $v1, 2
/* 05DA14 8005CE14 11800019 */  beqz  $t4, .L8005CE7C
/* 05DA18 8005CE18 24010001 */   li    $at, 1
/* 05DA1C 8005CE1C 8FB80034 */  lw    $t8, 0x34($sp)
/* 05DA20 8005CE20 24010001 */  li    $at, 1
/* 05DA24 8005CE24 17010007 */  bne   $t8, $at, .L8005CE44
/* 05DA28 8005CE28 00000000 */   nop   
/* 05DA2C 8005CE2C 0C01BC50 */  jal   func_8006F140
/* 05DA30 8005CE30 24040004 */   li    $a0, 4
/* 05DA34 8005CE34 0C00384A */  jal   instShowBearBar
/* 05DA38 8005CE38 00000000 */   nop   
/* 05DA3C 8005CE3C 1000000A */  b     .L8005CE68
/* 05DA40 8005CE40 83AE0043 */   lb    $t6, 0x43($sp)
.L8005CE44:
/* 05DA44 8005CE44 0C01BC50 */  jal   func_8006F140
/* 05DA48 8005CE48 24040003 */   li    $a0, 3
/* 05DA4C 8005CE4C 0C027B20 */  jal   is_in_two_player_adventure
/* 05DA50 8005CE50 00000000 */   nop   
/* 05DA54 8005CE54 10400004 */  beqz  $v0, .L8005CE68
/* 05DA58 8005CE58 83AE0043 */   lb    $t6, 0x43($sp)
/* 05DA5C 8005CE5C 0C01BCE6 */  jal   swap_lead_player
/* 05DA60 8005CE60 00000000 */   nop   
/* 05DA64 8005CE64 83AE0043 */  lb    $t6, 0x43($sp)
.L8005CE68:
/* 05DA68 8005CE68 8FAC004C */  lw    $t4, 0x4c($sp)
/* 05DA6C 8005CE6C 25D90001 */  addiu $t9, $t6, 1
/* 05DA70 8005CE70 A3B90043 */  sb    $t9, 0x43($sp)
/* 05DA74 8005CE74 10000070 */  b     .L8005D038
/* 05DA78 8005CE78 A1990000 */   sb    $t9, ($t4)
.L8005CE7C:
/* 05DA7C 8005CE7C 17010058 */  bne   $t8, $at, .L8005CFE0
/* 05DA80 8005CE80 2404FFF6 */   li    $a0, -10
/* 05DA84 8005CE84 346E0002 */  ori   $t6, $v1, 2
/* 05DA88 8005CE88 AC4E0000 */  sw    $t6, ($v0)
/* 05DA8C 8005CE8C 9548000C */  lhu   $t0, 0xc($t2)
/* 05DA90 8005CE90 0009C980 */  sll   $t9, $t1, 6
/* 05DA94 8005CE94 01097824 */  and   $t7, $t0, $t1
/* 05DA98 8005CE98 15E0000F */  bnez  $t7, .L8005CED8
/* 05DA9C 8005CE9C 01196024 */   and   $t4, $t0, $t9
/* 05DAA0 8005CEA0 01096825 */  or    $t5, $t0, $t1
/* 05DAA4 8005CEA4 A54D000C */  sh    $t5, 0xc($t2)
/* 05DAA8 8005CEA8 2404FFFF */  li    $a0, -1
/* 05DAAC 8005CEAC 00002825 */  move  $a1, $zero
/* 05DAB0 8005CEB0 00003025 */  move  $a2, $zero
/* 05DAB4 8005CEB4 0C01B06B */  jal   push_level_property_stack
/* 05DAB8 8005CEB8 00003825 */   move  $a3, $zero
/* 05DABC 8005CEBC 02002025 */  move  $a0, $s0
/* 05DAC0 8005CEC0 24050004 */  li    $a1, 4
/* 05DAC4 8005CEC4 2406FFFF */  li    $a2, -1
/* 05DAC8 8005CEC8 0C01B06B */  jal   push_level_property_stack
/* 05DACC 8005CECC 24070004 */   li    $a3, 4
/* 05DAD0 8005CED0 1000003D */  b     .L8005CFC8
/* 05DAD4 8005CED4 00000000 */   nop   
.L8005CED8:
/* 05DAD8 8005CED8 15800032 */  bnez  $t4, .L8005CFA4
/* 05DADC 8005CEDC 2404FFFF */   li    $a0, -1
/* 05DAE0 8005CEE0 91430048 */  lbu   $v1, 0x48($t2)
/* 05DAE4 8005CEE4 0119C025 */  or    $t8, $t0, $t9
/* 05DAE8 8005CEE8 A558000C */  sh    $t8, 0xc($t2)
/* 05DAEC 8005CEEC 1860000C */  blez  $v1, .L8005CF20
/* 05DAF0 8005CEF0 00004825 */   move  $t1, $zero
/* 05DAF4 8005CEF4 28610005 */  slti  $at, $v1, 5
/* 05DAF8 8005CEF8 10200009 */  beqz  $at, .L8005CF20
/* 05DAFC 8005CEFC 00000000 */   nop   
/* 05DB00 8005CF00 91490017 */  lbu   $t1, 0x17($t2)
/* 05DB04 8005CF04 00000000 */  nop   
/* 05DB08 8005CF08 25290001 */  addiu $t1, $t1, 1
/* 05DB0C 8005CF0C 29210005 */  slti  $at, $t1, 5
/* 05DB10 8005CF10 14200002 */  bnez  $at, .L8005CF1C
/* 05DB14 8005CF14 00000000 */   nop   
/* 05DB18 8005CF18 24090004 */  li    $t1, 4
.L8005CF1C:
/* 05DB1C 8005CF1C A1490017 */  sb    $t1, 0x17($t2)
.L8005CF20:
/* 05DB20 8005CF20 11200015 */  beqz  $t1, .L8005CF78
/* 05DB24 8005CF24 2404FFFF */   li    $a0, -1
/* 05DB28 8005CF28 2404FFFF */  li    $a0, -1
/* 05DB2C 8005CF2C 00002825 */  move  $a1, $zero
/* 05DB30 8005CF30 00003025 */  move  $a2, $zero
/* 05DB34 8005CF34 00003825 */  move  $a3, $zero
/* 05DB38 8005CF38 0C01B06B */  jal   push_level_property_stack
/* 05DB3C 8005CF3C AFAA0044 */   sw    $t2, 0x44($sp)
/* 05DB40 8005CF40 8FAA0044 */  lw    $t2, 0x44($sp)
/* 05DB44 8005CF44 2404002B */  li    $a0, 43
/* 05DB48 8005CF48 91470017 */  lbu   $a3, 0x17($t2)
/* 05DB4C 8005CF4C 00002825 */  move  $a1, $zero
/* 05DB50 8005CF50 2406FFFF */  li    $a2, -1
/* 05DB54 8005CF54 0C01B06B */  jal   push_level_property_stack
/* 05DB58 8005CF58 24E7FFFF */   addiu $a3, $a3, -1
/* 05DB5C 8005CF5C 02002025 */  move  $a0, $s0
/* 05DB60 8005CF60 24050006 */  li    $a1, 6
/* 05DB64 8005CF64 2406FFFF */  li    $a2, -1
/* 05DB68 8005CF68 0C01B06B */  jal   push_level_property_stack
/* 05DB6C 8005CF6C 24070006 */   li    $a3, 6
/* 05DB70 8005CF70 10000015 */  b     .L8005CFC8
/* 05DB74 8005CF74 00000000 */   nop   
.L8005CF78:
/* 05DB78 8005CF78 00002825 */  move  $a1, $zero
/* 05DB7C 8005CF7C 00003025 */  move  $a2, $zero
/* 05DB80 8005CF80 0C01B06B */  jal   push_level_property_stack
/* 05DB84 8005CF84 00003825 */   move  $a3, $zero
/* 05DB88 8005CF88 02002025 */  move  $a0, $s0
/* 05DB8C 8005CF8C 24050004 */  li    $a1, 4
/* 05DB90 8005CF90 2406FFFF */  li    $a2, -1
/* 05DB94 8005CF94 0C01B06B */  jal   push_level_property_stack
/* 05DB98 8005CF98 24070004 */   li    $a3, 4
/* 05DB9C 8005CF9C 1000000A */  b     .L8005CFC8
/* 05DBA0 8005CFA0 00000000 */   nop   
.L8005CFA4:
/* 05DBA4 8005CFA4 00002825 */  move  $a1, $zero
/* 05DBA8 8005CFA8 00003025 */  move  $a2, $zero
/* 05DBAC 8005CFAC 0C01B06B */  jal   push_level_property_stack
/* 05DBB0 8005CFB0 00003825 */   move  $a3, $zero
/* 05DBB4 8005CFB4 02002025 */  move  $a0, $s0
/* 05DBB8 8005CFB8 24050004 */  li    $a1, 4
/* 05DBBC 8005CFBC 2406FFFF */  li    $a2, -1
/* 05DBC0 8005CFC0 0C01B06B */  jal   push_level_property_stack
/* 05DBC4 8005CFC4 24070004 */   li    $a3, 4
.L8005CFC8:
/* 05DBC8 8005CFC8 0C01BC50 */  jal   func_8006F140
/* 05DBCC 8005CFCC 24040004 */   li    $a0, 4
/* 05DBD0 8005CFD0 0C00384A */  jal   instShowBearBar
/* 05DBD4 8005CFD4 00000000 */   nop   
/* 05DBD8 8005CFD8 1000000D */  b     .L8005D010
/* 05DBDC 8005CFDC 83AE0043 */   lb    $t6, 0x43($sp)
.L8005CFE0:
/* 05DBE0 8005CFE0 00002825 */  move  $a1, $zero
/* 05DBE4 8005CFE4 00003025 */  move  $a2, $zero
/* 05DBE8 8005CFE8 0C01B06B */  jal   push_level_property_stack
/* 05DBEC 8005CFEC 00003825 */   move  $a3, $zero
/* 05DBF0 8005CFF0 02002025 */  move  $a0, $s0
/* 05DBF4 8005CFF4 24050005 */  li    $a1, 5
/* 05DBF8 8005CFF8 2406FFFF */  li    $a2, -1
/* 05DBFC 8005CFFC 0C01B06B */  jal   push_level_property_stack
/* 05DC00 8005D000 24070005 */   li    $a3, 5
/* 05DC04 8005D004 0C01BC50 */  jal   func_8006F140
/* 05DC08 8005D008 24040003 */   li    $a0, 3
/* 05DC0C 8005D00C 83AE0043 */  lb    $t6, 0x43($sp)
.L8005D010:
/* 05DC10 8005D010 00000000 */  nop   
/* 05DC14 8005D014 25CF0001 */  addiu $t7, $t6, 1
/* 05DC18 8005D018 0C027068 */  jal   get_save_file_index
/* 05DC1C 8005D01C A3AF0043 */   sb    $t7, 0x43($sp)
/* 05DC20 8005D020 0C01BB12 */  jal   safe_mark_write_save_file
/* 05DC24 8005D024 00402025 */   move  $a0, $v0
.L8005D028:
/* 05DC28 8005D028 83AD0043 */  lb    $t5, 0x43($sp)
/* 05DC2C 8005D02C 8FB9004C */  lw    $t9, 0x4c($sp)
/* 05DC30 8005D030 00000000 */  nop   
/* 05DC34 8005D034 A32D0000 */  sb    $t5, ($t9)
.L8005D038:
/* 05DC38 8005D038 8FBF001C */  lw    $ra, 0x1c($sp)
/* 05DC3C 8005D03C 8FB00018 */  lw    $s0, 0x18($sp)
/* 05DC40 8005D040 03E00008 */  jr    $ra
/* 05DC44 8005D044 27BD0048 */   addiu $sp, $sp, 0x48

