.late_rodata
glabel jpt_800E5154
.word L8000D974, L8000D974, L8000D974, L8000D974, L8000D974, L8000D98C, L8000D974, L8000D974, L8000D974
glabel D_800E5178
.float 0.0099999999
glabel D_800E517C
.float 0.0099999999
glabel D_800E5180
.float 1.4
glabel D_800E5184
.float 0.714

.text
glabel func_8000CC7C
/* 00D87C 8000CC7C 27BDFEB0 */  addiu $sp, $sp, -0x150
/* 00D880 8000CC80 3C018012 */  lui   $at, %hi(D_8011AD20) # $at, 0x8012
/* 00D884 8000CC84 A020AD20 */  sb    $zero, %lo(D_8011AD20)($at)
/* 00D888 8000CC88 3C018012 */  lui   $at, %hi(D_8011ADB0) # $at, 0x8012
/* 00D88C 8000CC8C AC20ADB0 */  sw    $zero, %lo(D_8011ADB0)($at)
/* 00D890 8000CC90 3C018012 */  lui   $at, %hi(D_8011ADC4) # $at, 0x8012
/* 00D894 8000CC94 AFB1001C */  sw    $s1, 0x1c($sp)
/* 00D898 8000CC98 A020ADC4 */  sb    $zero, %lo(D_8011ADC4)($at)
/* 00D89C 8000CC9C 3C118012 */  lui   $s1, %hi(D_8011AF00) # $s1, 0x8012
/* 00D8A0 8000CCA0 AFBE0038 */  sw    $fp, 0x38($sp)
/* 00D8A4 8000CCA4 3C018012 */  lui   $at, %hi(gNumRacers) # $at, 0x8012
/* 00D8A8 8000CCA8 0080F025 */  move  $fp, $a0
/* 00D8AC 8000CCAC 2631AF00 */  addiu $s1, %lo(D_8011AF00) # addiu $s1, $s1, -0x5100
/* 00D8B0 8000CCB0 AFBF003C */  sw    $ra, 0x3c($sp)
/* 00D8B4 8000CCB4 AFB30024 */  sw    $s3, 0x24($sp)
/* 00D8B8 8000CCB8 AFB00018 */  sw    $s0, 0x18($sp)
/* 00D8BC 8000CCBC AC20AEF0 */  sw    $zero, %lo(gNumRacers)($at)
/* 00D8C0 8000CCC0 00A08025 */  move  $s0, $a1
/* 00D8C4 8000CCC4 00C09825 */  move  $s3, $a2
/* 00D8C8 8000CCC8 AFB70034 */  sw    $s7, 0x34($sp)
/* 00D8CC 8000CCCC AFB60030 */  sw    $s6, 0x30($sp)
/* 00D8D0 8000CCD0 AFB5002C */  sw    $s5, 0x2c($sp)
/* 00D8D4 8000CCD4 AFB40028 */  sw    $s4, 0x28($sp)
/* 00D8D8 8000CCD8 AFB20020 */  sw    $s2, 0x20($sp)
/* 00D8DC 8000CCDC A2200000 */  sb    $zero, ($s1)
/* 00D8E0 8000CCE0 0C01486E */  jal   func_800521B8
/* 00D8E4 8000CCE4 00002025 */   move  $a0, $zero
/* 00D8E8 8000CCE8 0C01AF6C */  jal   get_current_level_header
/* 00D8EC 8000CCEC 00000000 */   nop   
/* 00D8F0 8000CCF0 AFA20078 */  sw    $v0, 0x78($sp)
/* 00D8F4 8000CCF4 9043004C */  lbu   $v1, 0x4c($v0)
/* 00D8F8 8000CCF8 24160006 */  li    $s6, 6
/* 00D8FC 8000CCFC 12C304E0 */  beq   $s6, $v1, .L8000E080
/* 00D900 8000CD00 00602025 */   move  $a0, $v1
/* 00D904 8000CD04 24010007 */  li    $at, 7
/* 00D908 8000CD08 106104DD */  beq   $v1, $at, .L8000E080
/* 00D90C 8000CD0C 240FFFFF */   li    $t7, -1
/* 00D910 8000CD10 24010008 */  li    $at, 8
/* 00D914 8000CD14 10610002 */  beq   $v1, $at, .L8000CD20
/* 00D918 8000CD18 306E0040 */   andi  $t6, $v1, 0x40
/* 00D91C 8000CD1C 11C00005 */  beqz  $t6, .L8000CD34
.L8000CD20:
/* 00D920 8000CD20 3C148012 */   lui   $s4, %hi(gTimeTrialEnabled) # $s4, 0x8012
/* 00D924 8000CD24 3C018012 */  lui   $at, %hi(gIsTimeTrial) # $at, 0x8012
/* 00D928 8000CD28 2694AEF4 */  addiu $s4, %lo(gTimeTrialEnabled) # addiu $s4, $s4, -0x510c
/* 00D92C 8000CD2C A020AEF5 */  sb    $zero, %lo(gIsTimeTrial)($at)
/* 00D930 8000CD30 A2800000 */  sb    $zero, ($s4)
.L8000CD34:
/* 00D934 8000CD34 3C148012 */  lui   $s4, %hi(gTimeTrialEnabled) # $s4, 0x8012
/* 00D938 8000CD38 2694AEF4 */  addiu $s4, %lo(gTimeTrialEnabled) # addiu $s4, $s4, -0x510c
/* 00D93C 8000CD3C AFAF0130 */  sw    $t7, 0x130($sp)
/* 00D940 8000CD40 0C003932 */  jal   is_time_trial_enabled
/* 00D944 8000CD44 AFA40068 */   sw    $a0, 0x68($sp)
/* 00D948 8000CD48 1040000C */  beqz  $v0, .L8000CD7C
/* 00D94C 8000CD4C 00000000 */   nop   
/* 00D950 8000CD50 8FB80068 */  lw    $t8, 0x68($sp)
/* 00D954 8000CD54 00000000 */  nop   
/* 00D958 8000CD58 17000008 */  bnez  $t8, .L8000CD7C
/* 00D95C 8000CD5C 00000000 */   nop   
/* 00D960 8000CD60 0C01A75F */  jal   get_cutscene_camera_segment
/* 00D964 8000CD64 00000000 */   nop   
/* 00D968 8000CD68 AFA20074 */  sw    $v0, 0x74($sp)
/* 00D96C 8000CD6C 9059003B */  lbu   $t9, 0x3b($v0)
/* 00D970 8000CD70 240D0001 */  li    $t5, 1
/* 00D974 8000CD74 AFB90130 */  sw    $t9, 0x130($sp)
/* 00D978 8000CD78 A04D003B */  sb    $t5, 0x3b($v0)
.L8000CD7C:
/* 00D97C 8000CD7C 0C01B683 */  jal   get_render_context
/* 00D980 8000CD80 00000000 */   nop   
/* 00D984 8000CD84 0C01BAA4 */  jal   get_settings
/* 00D988 8000CD88 AFA20138 */   sw    $v0, 0x138($sp)
/* 00D98C 8000CD8C 0040B825 */  move  $s7, $v0
/* 00D990 8000CD90 0C0078A7 */  jal   get_misc_asset
/* 00D994 8000CD94 24040003 */   li    $a0, 3
/* 00D998 8000CD98 3C0B8012 */  lui   $t3, %hi(D_8011ADC5) # $t3, 0x8012
/* 00D99C 8000CD9C 256BADC5 */  addiu $t3, %lo(D_8011ADC5) # addiu $t3, $t3, -0x523b
/* 00D9A0 8000CDA0 816E0000 */  lb    $t6, ($t3)
/* 00D9A4 8000CDA4 3C0C8012 */  lui   $t4, %hi(D_8011AE82) # $t4, 0x8012
/* 00D9A8 8000CDA8 258CAE82 */  addiu $t4, %lo(D_8011AE82) # addiu $t4, $t4, -0x517e
/* 00D9AC 8000CDAC AFA20128 */  sw    $v0, 0x128($sp)
/* 00D9B0 8000CDB0 A58E0000 */  sh    $t6, ($t4)
/* 00D9B4 8000CDB4 92F80049 */  lbu   $t8, 0x49($s7)
/* 00D9B8 8000CDB8 8EEF0004 */  lw    $t7, 4($s7)
/* 00D9BC 8000CDBC 0018C880 */  sll   $t9, $t8, 2
/* 00D9C0 8000CDC0 01F91821 */  addu  $v1, $t7, $t9
/* 00D9C4 8000CDC4 8C640000 */  lw    $a0, ($v1)
/* 00D9C8 8000CDC8 27A200B4 */  addiu $v0, $sp, 0xb4
/* 00D9CC 8000CDCC 308D0001 */  andi  $t5, $a0, 1
/* 00D9D0 8000CDD0 15A00005 */  bnez  $t5, .L8000CDE8
/* 00D9D4 8000CDD4 27A500D4 */   addiu $a1, $sp, 0xd4
/* 00D9D8 8000CDD8 348E0001 */  ori   $t6, $a0, 1
/* 00D9DC 8000CDDC AC6E0000 */  sw    $t6, ($v1)
/* 00D9E0 8000CDE0 24180002 */  li    $t8, 2
/* 00D9E4 8000CDE4 A2380000 */  sb    $t8, ($s1)
.L8000CDE8:
/* 00D9E8 8000CDE8 8FAF0068 */  lw    $t7, 0x68($sp)
/* 00D9EC 8000CDEC 27A300F4 */  addiu $v1, $sp, 0xf4
/* 00D9F0 8000CDF0 11E00003 */  beqz  $t7, .L8000CE00
/* 00D9F4 8000CDF4 27A400D4 */   addiu $a0, $sp, 0xd4
/* 00D9F8 8000CDF8 24190002 */  li    $t9, 2
/* 00D9FC 8000CDFC A2390000 */  sb    $t9, ($s1)
.L8000CE00:
/* 00DA00 8000CE00 24420004 */  addiu $v0, $v0, 4
/* 00DA04 8000CE04 0045082B */  sltu  $at, $v0, $a1
/* 00DA08 8000CE08 24630004 */  addiu $v1, $v1, 4
/* 00DA0C 8000CE0C 24840004 */  addiu $a0, $a0, 4
/* 00DA10 8000CE10 AC60FFFC */  sw    $zero, -4($v1)
/* 00DA14 8000CE14 AC80FFFC */  sw    $zero, -4($a0)
/* 00DA18 8000CE18 1420FFF9 */  bnez  $at, .L8000CE00
/* 00DA1C 8000CE1C AC40FFFC */   sw    $zero, -4($v0)
/* 00DA20 8000CE20 3C028012 */  lui   $v0, %hi(objCount) # $v0, 0x8012
/* 00DA24 8000CE24 8C42AE5C */  lw    $v0, %lo(objCount)($v0)
/* 00DA28 8000CE28 00009025 */  move  $s2, $zero
/* 00DA2C 8000CE2C 18400050 */  blez  $v0, .L8000CF70
/* 00DA30 8000CE30 0000A825 */   move  $s5, $zero
/* 00DA34 8000CE34 3C048012 */  lui   $a0, %hi(gObjPtrList) # $a0, 0x8012
/* 00DA38 8000CE38 8C84AE58 */  lw    $a0, %lo(gObjPtrList)($a0)
/* 00DA3C 8000CE3C 00022880 */  sll   $a1, $v0, 2
/* 00DA40 8000CE40 27AA0094 */  addiu $t2, $sp, 0x94
/* 00DA44 8000CE44 27A900B4 */  addiu $t1, $sp, 0xb4
/* 00DA48 8000CE48 27A800D4 */  addiu $t0, $sp, 0xd4
/* 00DA4C 8000CE4C 27A700F4 */  addiu $a3, $sp, 0xf4
/* 00DA50 8000CE50 2406000B */  li    $a2, 11
.L8000CE54:
/* 00DA54 8000CE54 8C910000 */  lw    $s1, ($a0)
/* 00DA58 8000CE58 26B50004 */  addiu $s5, $s5, 4
/* 00DA5C 8000CE5C 862D0006 */  lh    $t5, 6($s1)
/* 00DA60 8000CE60 00000000 */  nop   
/* 00DA64 8000CE64 31AE8000 */  andi  $t6, $t5, 0x8000
/* 00DA68 8000CE68 15C0003E */  bnez  $t6, .L8000CF64
/* 00DA6C 8000CE6C 02A5082A */   slt   $at, $s5, $a1
/* 00DA70 8000CE70 86380048 */  lh    $t8, 0x48($s1)
/* 00DA74 8000CE74 00000000 */  nop   
/* 00DA78 8000CE78 14D8003A */  bne   $a2, $t8, .L8000CF64
/* 00DA7C 8000CE7C 02A5082A */   slt   $at, $s5, $a1
/* 00DA80 8000CE80 8E2F007C */  lw    $t7, 0x7c($s1)
/* 00DA84 8000CE84 00000000 */  nop   
/* 00DA88 8000CE88 160F0036 */  bne   $s0, $t7, .L8000CF64
/* 00DA8C 8000CE8C 02A5082A */   slt   $at, $s5, $a1
/* 00DA90 8000CE90 8E220078 */  lw    $v0, 0x78($s1)
/* 00DA94 8000CE94 00000000 */  nop   
/* 00DA98 8000CE98 28410008 */  slti  $at, $v0, 8
/* 00DA9C 8000CE9C 10200029 */  beqz  $at, .L8000CF44
/* 00DAA0 8000CEA0 00000000 */   nop   
/* 00DAA4 8000CEA4 4459F800 */  cfc1  $t9, $31
/* 00DAA8 8000CEA8 C624000C */  lwc1  $f4, 0xc($s1)
/* 00DAAC 8000CEAC 37210003 */  ori   $at, $t9, 3
/* 00DAB0 8000CEB0 38210002 */  xori  $at, $at, 2
/* 00DAB4 8000CEB4 44C1F800 */  ctc1  $at, $31
/* 00DAB8 8000CEB8 00027080 */  sll   $t6, $v0, 2
/* 00DABC 8000CEBC 460021A4 */  cvt.w.s $f6, $f4
/* 00DAC0 8000CEC0 00EEC021 */  addu  $t8, $a3, $t6
/* 00DAC4 8000CEC4 44D9F800 */  ctc1  $t9, $31
/* 00DAC8 8000CEC8 440D3000 */  mfc1  $t5, $f6
/* 00DACC 8000CECC 00000000 */  nop   
/* 00DAD0 8000CED0 444FF800 */  cfc1  $t7, $31
/* 00DAD4 8000CED4 AF0D0000 */  sw    $t5, ($t8)
/* 00DAD8 8000CED8 35E10003 */  ori   $at, $t7, 3
/* 00DADC 8000CEDC 38210002 */  xori  $at, $at, 2
/* 00DAE0 8000CEE0 44C1F800 */  ctc1  $at, $31
/* 00DAE4 8000CEE4 C6280010 */  lwc1  $f8, 0x10($s1)
/* 00DAE8 8000CEE8 8E2E0078 */  lw    $t6, 0x78($s1)
/* 00DAEC 8000CEEC 460042A4 */  cvt.w.s $f10, $f8
/* 00DAF0 8000CEF0 000E6880 */  sll   $t5, $t6, 2
/* 00DAF4 8000CEF4 44195000 */  mfc1  $t9, $f10
/* 00DAF8 8000CEF8 010DC021 */  addu  $t8, $t0, $t5
/* 00DAFC 8000CEFC 35E10003 */  ori   $at, $t7, 3
/* 00DB00 8000CF00 38210002 */  xori  $at, $at, 2
/* 00DB04 8000CF04 44CFF800 */  ctc1  $t7, $31
/* 00DB08 8000CF08 AF190000 */  sw    $t9, ($t8)
/* 00DB0C 8000CF0C C6300014 */  lwc1  $f16, 0x14($s1)
/* 00DB10 8000CF10 44C1F800 */  ctc1  $at, $31
/* 00DB14 8000CF14 8E2D0078 */  lw    $t5, 0x78($s1)
/* 00DB18 8000CF18 460084A4 */  cvt.w.s $f18, $f16
/* 00DB1C 8000CF1C 000DC880 */  sll   $t9, $t5, 2
/* 00DB20 8000CF20 440E9000 */  mfc1  $t6, $f18
/* 00DB24 8000CF24 0139C021 */  addu  $t8, $t1, $t9
/* 00DB28 8000CF28 AF0E0000 */  sw    $t6, ($t8)
/* 00DB2C 8000CF2C 8E2D0078 */  lw    $t5, 0x78($s1)
/* 00DB30 8000CF30 44CFF800 */  ctc1  $t7, $31
/* 00DB34 8000CF34 862F0000 */  lh    $t7, ($s1)
/* 00DB38 8000CF38 000DC880 */  sll   $t9, $t5, 2
/* 00DB3C 8000CF3C 01597021 */  addu  $t6, $t2, $t9
/* 00DB40 8000CF40 ADCF0000 */  sw    $t7, ($t6)
.L8000CF44:
/* 00DB44 8000CF44 8E22003C */  lw    $v0, 0x3c($s1)
/* 00DB48 8000CF48 2401FFFF */  li    $at, -1
/* 00DB4C 8000CF4C 8043000B */  lb    $v1, 0xb($v0)
/* 00DB50 8000CF50 00000000 */  nop   
/* 00DB54 8000CF54 10610003 */  beq   $v1, $at, .L8000CF64
/* 00DB58 8000CF58 02A5082A */   slt   $at, $s5, $a1
/* 00DB5C 8000CF5C 0060F025 */  move  $fp, $v1
/* 00DB60 8000CF60 02A5082A */  slt   $at, $s5, $a1
.L8000CF64:
/* 00DB64 8000CF64 1420FFBB */  bnez  $at, .L8000CE54
/* 00DB68 8000CF68 24840004 */   addiu $a0, $a0, 4
/* 00DB6C 8000CF6C 00009025 */  move  $s2, $zero
.L8000CF70:
/* 00DB70 8000CF70 A17E0000 */  sb    $fp, ($t3)
/* 00DB74 8000CF74 81780000 */  lb    $t8, ($t3)
/* 00DB78 8000CF78 3C10800E */  lui   $s0, %hi(D_800DC740) # $s0, 0x800e
/* 00DB7C 8000CF7C 240D0008 */  li    $t5, 8
/* 00DB80 8000CF80 3C018012 */  lui   $at, %hi(gNumRacers) # $at, 0x8012
/* 00DB84 8000CF84 A5980000 */  sh    $t8, ($t4)
/* 00DB88 8000CF88 2610C740 */  addiu $s0, %lo(D_800DC740) # addiu $s0, $s0, -0x38c0
/* 00DB8C 8000CF8C 26620001 */  addiu $v0, $s3, 1
/* 00DB90 8000CF90 AC2DAEF0 */  sw    $t5, %lo(gNumRacers)($at)
/* 00DB94 8000CF94 AFA20144 */  sw    $v0, 0x144($sp)
/* 00DB98 8000CF98 A2000000 */  sb    $zero, ($s0)
/* 00DB9C 8000CF9C 0C01B067 */  jal   func_8006C19C
/* 00DBA0 8000CFA0 AFA20058 */   sw    $v0, 0x58($sp)
/* 00DBA4 8000CFA4 10400006 */  beqz  $v0, .L8000CFC0
/* 00DBA8 8000CFA8 24190002 */   li    $t9, 2
/* 00DBAC 8000CFAC 240F0001 */  li    $t7, 1
/* 00DBB0 8000CFB0 AFB90144 */  sw    $t9, 0x144($sp)
/* 00DBB4 8000CFB4 A20F0000 */  sb    $t7, ($s0)
/* 00DBB8 8000CFB8 0C009278 */  jal   set_scene_viewport_num
/* 00DBBC 8000CFBC 24040001 */   li    $a0, 1
.L8000CFC0:
/* 00DBC0 8000CFC0 8FAE0068 */  lw    $t6, 0x68($sp)
/* 00DBC4 8000CFC4 24010005 */  li    $at, 5
/* 00DBC8 8000CFC8 15C10002 */  bne   $t6, $at, .L8000CFD4
/* 00DBCC 8000CFCC 3C0D8012 */   lui   $t5, %hi(gIsTimeTrial) # $t5, 0x8012
/* 00DBD0 8000CFD0 A2800000 */  sb    $zero, ($s4)
.L8000CFD4:
/* 00DBD4 8000CFD4 92980000 */  lbu   $t8, ($s4)
/* 00DBD8 8000CFD8 3C018012 */  lui   $at, %hi(gIsTimeTrial) # $at, 0x8012
/* 00DBDC 8000CFDC A038AEF5 */  sb    $t8, %lo(gIsTimeTrial)($at)
/* 00DBE0 8000CFE0 91ADAEF5 */  lbu   $t5, %lo(gIsTimeTrial)($t5)
/* 00DBE4 8000CFE4 24190005 */  li    $t9, 5
/* 00DBE8 8000CFE8 11A00003 */  beqz  $t5, .L8000CFF8
/* 00DBEC 8000CFEC 8FAF0068 */   lw    $t7, 0x68($sp)
/* 00DBF0 8000CFF0 AFB90068 */  sw    $t9, 0x68($sp)
/* 00DBF4 8000CFF4 8FAF0068 */  lw    $t7, 0x68($sp)
.L8000CFF8:
/* 00DBF8 8000CFF8 24010005 */  li    $at, 5
/* 00DBFC 8000CFFC 31EE0040 */  andi  $t6, $t7, 0x40
/* 00DC00 8000D000 11E10006 */  beq   $t7, $at, .L8000D01C
/* 00DC04 8000D004 AFAE0064 */   sw    $t6, 0x64($sp)
/* 00DC08 8000D008 8FB80144 */  lw    $t8, 0x144($sp)
/* 00DC0C 8000D00C 8FAF0144 */  lw    $t7, 0x144($sp)
/* 00DC10 8000D010 2B010003 */  slti  $at, $t8, 3
/* 00DC14 8000D014 14200010 */  bnez  $at, .L8000D058
/* 00DC18 8000D018 24010002 */   li    $at, 2
.L8000D01C:
/* 00DC1C 8000D01C 8FAD0144 */  lw    $t5, 0x144($sp)
/* 00DC20 8000D020 3C018012 */  lui   $at, %hi(gNumRacers) # $at, 0x8012
/* 00DC24 8000D024 0C01B0BC */  jal   get_level_property_stack_pos
/* 00DC28 8000D028 AC2DAEF0 */   sw    $t5, %lo(gNumRacers)($at)
/* 00DC2C 8000D02C 14400010 */  bnez  $v0, .L8000D070
/* 00DC30 8000D030 3C03800E */   lui   $v1, %hi(D_800DC708) # $v1, 0x800e
/* 00DC34 8000D034 2463C708 */  addiu $v1, %lo(D_800DC708) # addiu $v1, $v1, -0x38f8
/* 00DC38 8000D038 84620000 */  lh    $v0, ($v1)
/* 00DC3C 8000D03C 8FB90094 */  lw    $t9, 0x94($sp)
/* 00DC40 8000D040 1040000B */  beqz  $v0, .L8000D070
/* 00DC44 8000D044 03227021 */   addu  $t6, $t9, $v0
/* 00DC48 8000D048 AFAE0094 */  sw    $t6, 0x94($sp)
/* 00DC4C 8000D04C 10000008 */  b     .L8000D070
/* 00DC50 8000D050 A4600000 */   sh    $zero, ($v1)
/* 00DC54 8000D054 24010002 */  li    $at, 2
.L8000D058:
/* 00DC58 8000D058 15E10006 */  bne   $t7, $at, .L8000D074
/* 00DC5C 8000D05C 8FB80064 */   lw    $t8, 0x64($sp)
/* 00DC60 8000D060 0C027110 */  jal   get_multiplayer_racer_count
/* 00DC64 8000D064 00000000 */   nop   
/* 00DC68 8000D068 3C018012 */  lui   $at, %hi(gNumRacers) # $at, 0x8012
/* 00DC6C 8000D06C AC22AEF0 */  sw    $v0, %lo(gNumRacers)($at)
.L8000D070:
/* 00DC70 8000D070 8FB80064 */  lw    $t8, 0x64($sp)
.L8000D074:
/* 00DC74 8000D074 3C058012 */  lui   $a1, %hi(D_8011AD3C) # $a1, 0x8012
/* 00DC78 8000D078 13000005 */  beqz  $t8, .L8000D090
/* 00DC7C 8000D07C 24A5AD3C */   addiu $a1, %lo(D_8011AD3C) # addiu $a1, $a1, -0x52c4
/* 00DC80 8000D080 3C068012 */  lui   $a2, %hi(gNumRacers) # $a2, 0x8012
/* 00DC84 8000D084 24C6AEF0 */  addiu $a2, %lo(gNumRacers) # addiu $a2, $a2, -0x5110
/* 00DC88 8000D088 240D0004 */  li    $t5, 4
/* 00DC8C 8000D08C ACCD0000 */  sw    $t5, ($a2)
.L8000D090:
/* 00DC90 8000D090 8FB90068 */  lw    $t9, 0x68($sp)
/* 00DC94 8000D094 3C068012 */  lui   $a2, %hi(gNumRacers) # $a2, 0x8012
/* 00DC98 8000D098 24010008 */  li    $at, 8
/* 00DC9C 8000D09C 24C6AEF0 */  addiu $a2, %lo(gNumRacers) # addiu $a2, $a2, -0x5110
/* 00DCA0 8000D0A0 17210006 */  bne   $t9, $at, .L8000D0BC
/* 00DCA4 8000D0A4 A0A00000 */   sb    $zero, ($a1)
/* 00DCA8 8000D0A8 24070001 */  li    $a3, 1
/* 00DCAC 8000D0AC 240E0002 */  li    $t6, 2
/* 00DCB0 8000D0B0 ACCE0000 */  sw    $t6, ($a2)
/* 00DCB4 8000D0B4 AFA70144 */  sw    $a3, 0x144($sp)
/* 00DCB8 8000D0B8 A0A70000 */  sb    $a3, ($a1)
.L8000D0BC:
/* 00DCBC 8000D0BC 8FAF0138 */  lw    $t7, 0x138($sp)
/* 00DCC0 8000D0C0 3C02800E */  lui   $v0, %hi(D_800DC71C) # $v0, 0x800e
/* 00DCC4 8000D0C4 2442C71C */  addiu $v0, %lo(D_800DC71C) # addiu $v0, $v0, -0x38e4
/* 00DCC8 8000D0C8 24070001 */  li    $a3, 1
/* 00DCCC 8000D0CC 15E70008 */  bne   $t7, $a3, .L8000D0F0
/* 00DCD0 8000D0D0 A0400000 */   sb    $zero, ($v0)
/* 00DCD4 8000D0D4 8FB80068 */  lw    $t8, 0x68($sp)
/* 00DCD8 8000D0D8 240D0002 */  li    $t5, 2
/* 00DCDC 8000D0DC 17000004 */  bnez  $t8, .L8000D0F0
/* 00DCE0 8000D0E0 00000000 */   nop   
/* 00DCE4 8000D0E4 ACD60000 */  sw    $s6, ($a2)
/* 00DCE8 8000D0E8 A0470000 */  sb    $a3, ($v0)
/* 00DCEC 8000D0EC A0AD0000 */  sb    $t5, ($a1)
.L8000D0F0:
/* 00DCF0 8000D0F0 8CC30000 */  lw    $v1, ($a2)
/* 00DCF4 8000D0F4 00008025 */  move  $s0, $zero
/* 00DCF8 8000D0F8 18600007 */  blez  $v1, .L8000D118
/* 00DCFC 8000D0FC 27A2011C */   addiu $v0, $sp, 0x11c
/* 00DD00 8000D100 00622021 */  addu  $a0, $v1, $v0
.L8000D104:
/* 00DD04 8000D104 24420001 */  addiu $v0, $v0, 1
/* 00DD08 8000D108 0044082B */  sltu  $at, $v0, $a0
/* 00DD0C 8000D10C 1420FFFD */  bnez  $at, .L8000D104
/* 00DD10 8000D110 A040FFFF */   sb    $zero, -1($v0)
/* 00DD14 8000D114 00008025 */  move  $s0, $zero
.L8000D118:
/* 00DD18 8000D118 8FAE0144 */  lw    $t6, 0x144($sp)
/* 00DD1C 8000D11C 00002825 */  move  $a1, $zero
/* 00DD20 8000D120 19C0006F */  blez  $t6, .L8000D2E0
/* 00DD24 8000D124 01C01025 */   move  $v0, $t6
/* 00DD28 8000D128 31C20003 */  andi  $v0, $t6, 3
/* 00DD2C 8000D12C 1040001D */  beqz  $v0, .L8000D1A4
/* 00DD30 8000D130 00404825 */   move  $t1, $v0
/* 00DD34 8000D134 00107880 */  sll   $t7, $s0, 2
/* 00DD38 8000D138 01F07823 */  subu  $t7, $t7, $s0
/* 00DD3C 8000D13C 000F78C0 */  sll   $t7, $t7, 3
/* 00DD40 8000D140 02EF3021 */  addu  $a2, $s7, $t7
/* 00DD44 8000D144 27A80114 */  addiu $t0, $sp, 0x114
/* 00DD48 8000D148 27A7011C */  addiu $a3, $sp, 0x11c
.L8000D14C:
/* 00DD4C 8000D14C 80C2005A */  lb    $v0, 0x5a($a2)
/* 00DD50 8000D150 00000000 */  nop   
/* 00DD54 8000D154 0043082A */  slt   $at, $v0, $v1
/* 00DD58 8000D158 10200007 */  beqz  $at, .L8000D178
/* 00DD5C 8000D15C 00E22021 */   addu  $a0, $a3, $v0
/* 00DD60 8000D160 80980000 */  lb    $t8, ($a0)
/* 00DD64 8000D164 240D0001 */  li    $t5, 1
/* 00DD68 8000D168 17000004 */  bnez  $t8, .L8000D17C
/* 00DD6C 8000D16C 0105C821 */   addu  $t9, $t0, $a1
/* 00DD70 8000D170 10000006 */  b     .L8000D18C
/* 00DD74 8000D174 A08D0000 */   sb    $t5, ($a0)
.L8000D178:
/* 00DD78 8000D178 0105C821 */  addu  $t9, $t0, $a1
.L8000D17C:
/* 00DD7C 8000D17C 24A50001 */  addiu $a1, $a1, 1
/* 00DD80 8000D180 30AE00FF */  andi  $t6, $a1, 0xff
/* 00DD84 8000D184 01C02825 */  move  $a1, $t6
/* 00DD88 8000D188 A3300000 */  sb    $s0, ($t9)
.L8000D18C:
/* 00DD8C 8000D18C 26100001 */  addiu $s0, $s0, 1
/* 00DD90 8000D190 1530FFEE */  bne   $t1, $s0, .L8000D14C
/* 00DD94 8000D194 24C60018 */   addiu $a2, $a2, 0x18
/* 00DD98 8000D198 8FAF0144 */  lw    $t7, 0x144($sp)
/* 00DD9C 8000D19C 00000000 */  nop   
/* 00DDA0 8000D1A0 120F004D */  beq   $s0, $t7, .L8000D2D8
.L8000D1A4:
/* 00DDA4 8000D1A4 0010C080 */   sll   $t8, $s0, 2
/* 00DDA8 8000D1A8 0310C023 */  subu  $t8, $t8, $s0
/* 00DDAC 8000D1AC 0018C0C0 */  sll   $t8, $t8, 3
/* 00DDB0 8000D1B0 02F83021 */  addu  $a2, $s7, $t8
/* 00DDB4 8000D1B4 27A7011C */  addiu $a3, $sp, 0x11c
/* 00DDB8 8000D1B8 27A80114 */  addiu $t0, $sp, 0x114
.L8000D1BC:
/* 00DDBC 8000D1BC 80C2005A */  lb    $v0, 0x5a($a2)
/* 00DDC0 8000D1C0 00000000 */  nop   
/* 00DDC4 8000D1C4 0043082A */  slt   $at, $v0, $v1
/* 00DDC8 8000D1C8 10200007 */  beqz  $at, .L8000D1E8
/* 00DDCC 8000D1CC 00E22021 */   addu  $a0, $a3, $v0
/* 00DDD0 8000D1D0 808D0000 */  lb    $t5, ($a0)
/* 00DDD4 8000D1D4 24190001 */  li    $t9, 1
/* 00DDD8 8000D1D8 15A00004 */  bnez  $t5, .L8000D1EC
/* 00DDDC 8000D1DC 01057021 */   addu  $t6, $t0, $a1
/* 00DDE0 8000D1E0 10000006 */  b     .L8000D1FC
/* 00DDE4 8000D1E4 A0990000 */   sb    $t9, ($a0)
.L8000D1E8:
/* 00DDE8 8000D1E8 01057021 */  addu  $t6, $t0, $a1
.L8000D1EC:
/* 00DDEC 8000D1EC 24A50001 */  addiu $a1, $a1, 1
/* 00DDF0 8000D1F0 30AF00FF */  andi  $t7, $a1, 0xff
/* 00DDF4 8000D1F4 01E02825 */  move  $a1, $t7
/* 00DDF8 8000D1F8 A1D00000 */  sb    $s0, ($t6)
.L8000D1FC:
/* 00DDFC 8000D1FC 80C20072 */  lb    $v0, 0x72($a2)
/* 00DE00 8000D200 00000000 */  nop   
/* 00DE04 8000D204 0043082A */  slt   $at, $v0, $v1
/* 00DE08 8000D208 10200007 */  beqz  $at, .L8000D228
/* 00DE0C 8000D20C 00E22021 */   addu  $a0, $a3, $v0
/* 00DE10 8000D210 80980000 */  lb    $t8, ($a0)
/* 00DE14 8000D214 240D0001 */  li    $t5, 1
/* 00DE18 8000D218 17000004 */  bnez  $t8, .L8000D22C
/* 00DE1C 8000D21C 01057021 */   addu  $t6, $t0, $a1
/* 00DE20 8000D220 10000007 */  b     .L8000D240
/* 00DE24 8000D224 A08D0000 */   sb    $t5, ($a0)
.L8000D228:
/* 00DE28 8000D228 01057021 */  addu  $t6, $t0, $a1
.L8000D22C:
/* 00DE2C 8000D22C 24A50001 */  addiu $a1, $a1, 1
/* 00DE30 8000D230 30AF00FF */  andi  $t7, $a1, 0xff
/* 00DE34 8000D234 26190001 */  addiu $t9, $s0, 1
/* 00DE38 8000D238 A1D90000 */  sb    $t9, ($t6)
/* 00DE3C 8000D23C 01E02825 */  move  $a1, $t7
.L8000D240:
/* 00DE40 8000D240 80C2008A */  lb    $v0, 0x8a($a2)
/* 00DE44 8000D244 00000000 */  nop   
/* 00DE48 8000D248 0043082A */  slt   $at, $v0, $v1
/* 00DE4C 8000D24C 10200007 */  beqz  $at, .L8000D26C
/* 00DE50 8000D250 00E22021 */   addu  $a0, $a3, $v0
/* 00DE54 8000D254 80980000 */  lb    $t8, ($a0)
/* 00DE58 8000D258 240D0001 */  li    $t5, 1
/* 00DE5C 8000D25C 17000004 */  bnez  $t8, .L8000D270
/* 00DE60 8000D260 01057021 */   addu  $t6, $t0, $a1
/* 00DE64 8000D264 10000007 */  b     .L8000D284
/* 00DE68 8000D268 A08D0000 */   sb    $t5, ($a0)
.L8000D26C:
/* 00DE6C 8000D26C 01057021 */  addu  $t6, $t0, $a1
.L8000D270:
/* 00DE70 8000D270 24A50001 */  addiu $a1, $a1, 1
/* 00DE74 8000D274 30AF00FF */  andi  $t7, $a1, 0xff
/* 00DE78 8000D278 26190002 */  addiu $t9, $s0, 2
/* 00DE7C 8000D27C A1D90000 */  sb    $t9, ($t6)
/* 00DE80 8000D280 01E02825 */  move  $a1, $t7
.L8000D284:
/* 00DE84 8000D284 80C200A2 */  lb    $v0, 0xa2($a2)
/* 00DE88 8000D288 00000000 */  nop   
/* 00DE8C 8000D28C 0043082A */  slt   $at, $v0, $v1
/* 00DE90 8000D290 10200007 */  beqz  $at, .L8000D2B0
/* 00DE94 8000D294 00E22021 */   addu  $a0, $a3, $v0
/* 00DE98 8000D298 80980000 */  lb    $t8, ($a0)
/* 00DE9C 8000D29C 240D0001 */  li    $t5, 1
/* 00DEA0 8000D2A0 17000004 */  bnez  $t8, .L8000D2B4
/* 00DEA4 8000D2A4 01057021 */   addu  $t6, $t0, $a1
/* 00DEA8 8000D2A8 10000007 */  b     .L8000D2C8
/* 00DEAC 8000D2AC A08D0000 */   sb    $t5, ($a0)
.L8000D2B0:
/* 00DEB0 8000D2B0 01057021 */  addu  $t6, $t0, $a1
.L8000D2B4:
/* 00DEB4 8000D2B4 24A50001 */  addiu $a1, $a1, 1
/* 00DEB8 8000D2B8 30AF00FF */  andi  $t7, $a1, 0xff
/* 00DEBC 8000D2BC 26190003 */  addiu $t9, $s0, 3
/* 00DEC0 8000D2C0 A1D90000 */  sb    $t9, ($t6)
/* 00DEC4 8000D2C4 01E02825 */  move  $a1, $t7
.L8000D2C8:
/* 00DEC8 8000D2C8 8FB80144 */  lw    $t8, 0x144($sp)
/* 00DECC 8000D2CC 26100004 */  addiu $s0, $s0, 4
/* 00DED0 8000D2D0 1618FFBA */  bne   $s0, $t8, .L8000D1BC
/* 00DED4 8000D2D4 24C60060 */   addiu $a2, $a2, 0x60
.L8000D2D8:
/* 00DED8 8000D2D8 8FA20144 */  lw    $v0, 0x144($sp)
/* 00DEDC 8000D2DC 00000000 */  nop   
.L8000D2E0:
/* 00DEE0 8000D2E0 0043082A */  slt   $at, $v0, $v1
/* 00DEE4 8000D2E4 27A7011C */  addiu $a3, $sp, 0x11c
/* 00DEE8 8000D2E8 27A80114 */  addiu $t0, $sp, 0x114
/* 00DEEC 8000D2EC 10200019 */  beqz  $at, .L8000D354
/* 00DEF0 8000D2F0 00408025 */   move  $s0, $v0
/* 00DEF4 8000D2F4 00026880 */  sll   $t5, $v0, 2
/* 00DEF8 8000D2F8 01A26823 */  subu  $t5, $t5, $v0
/* 00DEFC 8000D2FC 000D68C0 */  sll   $t5, $t5, 3
/* 00DF00 8000D300 02ED3021 */  addu  $a2, $s7, $t5
.L8000D304:
/* 00DF04 8000D304 80C2005A */  lb    $v0, 0x5a($a2)
/* 00DF08 8000D308 00000000 */  nop   
/* 00DF0C 8000D30C 0043082A */  slt   $at, $v0, $v1
/* 00DF10 8000D310 10200007 */  beqz  $at, .L8000D330
/* 00DF14 8000D314 00E22021 */   addu  $a0, $a3, $v0
/* 00DF18 8000D318 80990000 */  lb    $t9, ($a0)
/* 00DF1C 8000D31C 240E0001 */  li    $t6, 1
/* 00DF20 8000D320 17200004 */  bnez  $t9, .L8000D334
/* 00DF24 8000D324 01057821 */   addu  $t7, $t0, $a1
/* 00DF28 8000D328 10000006 */  b     .L8000D344
/* 00DF2C 8000D32C A08E0000 */   sb    $t6, ($a0)
.L8000D330:
/* 00DF30 8000D330 01057821 */  addu  $t7, $t0, $a1
.L8000D334:
/* 00DF34 8000D334 24A50001 */  addiu $a1, $a1, 1
/* 00DF38 8000D338 30B800FF */  andi  $t8, $a1, 0xff
/* 00DF3C 8000D33C 03002825 */  move  $a1, $t8
/* 00DF40 8000D340 A1F00000 */  sb    $s0, ($t7)
.L8000D344:
/* 00DF44 8000D344 26100001 */  addiu $s0, $s0, 1
/* 00DF48 8000D348 0203082A */  slt   $at, $s0, $v1
/* 00DF4C 8000D34C 1420FFED */  bnez  $at, .L8000D304
/* 00DF50 8000D350 24C60018 */   addiu $a2, $a2, 0x18
.L8000D354:
/* 00DF54 8000D354 00008025 */  move  $s0, $zero
/* 00DF58 8000D358 18A0001C */  blez  $a1, .L8000D3CC
/* 00DF5C 8000D35C 00A02025 */   move  $a0, $a1
/* 00DF60 8000D360 24150018 */  li    $s5, 24
.L8000D364:
/* 00DF64 8000D364 18600015 */  blez  $v1, .L8000D3BC
/* 00DF68 8000D368 00F21021 */   addu  $v0, $a3, $s2
.L8000D36C:
/* 00DF6C 8000D36C 804D0000 */  lb    $t5, ($v0)
/* 00DF70 8000D370 01107021 */  addu  $t6, $t0, $s0
/* 00DF74 8000D374 15A0000C */  bnez  $t5, .L8000D3A8
/* 00DF78 8000D378 00000000 */   nop   
/* 00DF7C 8000D37C 81CF0000 */  lb    $t7, ($t6)
/* 00DF80 8000D380 24190001 */  li    $t9, 1
/* 00DF84 8000D384 01F50019 */  multu $t7, $s5
/* 00DF88 8000D388 A0590000 */  sb    $t9, ($v0)
/* 00DF8C 8000D38C 3C038012 */  lui   $v1, %hi(gNumRacers) # $v1, 0x8012
/* 00DF90 8000D390 0000C012 */  mflo  $t8
/* 00DF94 8000D394 02F86821 */  addu  $t5, $s7, $t8
/* 00DF98 8000D398 A1B2005A */  sb    $s2, 0x5a($t5)
/* 00DF9C 8000D39C 8C63AEF0 */  lw    $v1, %lo(gNumRacers)($v1)
/* 00DFA0 8000D3A0 00000000 */  nop   
/* 00DFA4 8000D3A4 00609025 */  move  $s2, $v1
.L8000D3A8:
/* 00DFA8 8000D3A8 26520001 */  addiu $s2, $s2, 1
/* 00DFAC 8000D3AC 0243082A */  slt   $at, $s2, $v1
/* 00DFB0 8000D3B0 1420FFEE */  bnez  $at, .L8000D36C
/* 00DFB4 8000D3B4 00F21021 */   addu  $v0, $a3, $s2
/* 00DFB8 8000D3B8 00009025 */  move  $s2, $zero
.L8000D3BC:
/* 00DFBC 8000D3BC 26100001 */  addiu $s0, $s0, 1
/* 00DFC0 8000D3C0 1604FFE8 */  bne   $s0, $a0, .L8000D364
/* 00DFC4 8000D3C4 00000000 */   nop   
/* 00DFC8 8000D3C8 00008025 */  move  $s0, $zero
.L8000D3CC:
/* 00DFCC 8000D3CC 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 00DFD0 8000D3D0 24150018 */  li    $s5, 24
/* 00DFD4 8000D3D4 34A500FF */  ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 00DFD8 8000D3D8 0C01C327 */  jal   allocate_from_main_pool_safe
/* 00DFDC 8000D3DC 24040010 */   li    $a0, 16
/* 00DFE0 8000D3E0 A440000C */  sh    $zero, 0xc($v0)
/* 00DFE4 8000D3E4 A440000A */  sh    $zero, 0xa($v0)
/* 00DFE8 8000D3E8 A4400008 */  sh    $zero, 8($v0)
/* 00DFEC 8000D3EC 8FB90078 */  lw    $t9, 0x78($sp)
/* 00DFF0 8000D3F0 0040B025 */  move  $s6, $v0
/* 00DFF4 8000D3F4 832E004D */  lb    $t6, 0x4d($t9)
/* 00DFF8 8000D3F8 2419FFFF */  li    $t9, -1
/* 00DFFC 8000D3FC 15C00004 */  bnez  $t6, .L8000D410
/* 00E000 8000D400 3C038012 */   lui   $v1, %hi(gNumRacers) # $v1, 0x8012
/* 00E004 8000D404 3C018012 */  lui   $at, %hi(gIsNonCarRacers) # $at, 0x8012
/* 00E008 8000D408 10000004 */  b     .L8000D41C
/* 00E00C 8000D40C A020AE02 */   sb    $zero, %lo(gIsNonCarRacers)($at)
.L8000D410:
/* 00E010 8000D410 240F0001 */  li    $t7, 1
/* 00E014 8000D414 3C018012 */  lui   $at, %hi(gIsNonCarRacers) # $at, 0x8012
/* 00E018 8000D418 A02FAE02 */  sb    $t7, %lo(gIsNonCarRacers)($at)
.L8000D41C:
/* 00E01C 8000D41C 8FB80078 */  lw    $t8, 0x78($sp)
/* 00E020 8000D420 8C63AEF0 */  lw    $v1, %lo(gNumRacers)($v1)
/* 00E024 8000D424 830D00B8 */  lb    $t5, 0xb8($t8)
/* 00E028 8000D428 3C018012 */  lui   $at, %hi(D_8011AD24+1) # $at, 0x8012
/* 00E02C 8000D42C A3B90127 */  sb    $t9, 0x127($sp)
/* 00E030 8000D430 1860015E */  blez  $v1, .L8000D9AC
/* 00E034 8000D434 A02DAD25 */   sb    $t5, %lo(D_8011AD24+1)($at)
/* 00E038 8000D438 8FA40068 */  lw    $a0, 0x68($sp)
/* 00E03C 8000D43C 24020005 */  li    $v0, 5
.L8000D440:
/* 00E040 8000D440 10440019 */  beq   $v0, $a0, .L8000D4A8
/* 00E044 8000D444 0200A025 */   move  $s4, $s0
/* 00E048 8000D448 8FAE0064 */  lw    $t6, 0x64($sp)
/* 00E04C 8000D44C 3C0F8012 */  lui   $t7, %hi(D_8011AD3C) # $t7, 0x8012
/* 00E050 8000D450 15C00015 */  bnez  $t6, .L8000D4A8
/* 00E054 8000D454 00000000 */   nop   
/* 00E058 8000D458 81EFAD3C */  lb    $t7, %lo(D_8011AD3C)($t7)
/* 00E05C 8000D45C 00000000 */  nop   
/* 00E060 8000D460 15E00011 */  bnez  $t7, .L8000D4A8
/* 00E064 8000D464 00000000 */   nop   
/* 00E068 8000D468 0000A025 */  move  $s4, $zero
.L8000D46C:
/* 00E06C 8000D46C 02550019 */  multu $s2, $s5
/* 00E070 8000D470 0000C012 */  mflo  $t8
/* 00E074 8000D474 02F86821 */  addu  $t5, $s7, $t8
/* 00E078 8000D478 81B9005A */  lb    $t9, 0x5a($t5)
/* 00E07C 8000D47C 00000000 */  nop   
/* 00E080 8000D480 16190003 */  bne   $s0, $t9, .L8000D490
/* 00E084 8000D484 00000000 */   nop   
/* 00E088 8000D488 0240A025 */  move  $s4, $s2
/* 00E08C 8000D48C 00609025 */  move  $s2, $v1
.L8000D490:
/* 00E090 8000D490 26520001 */  addiu $s2, $s2, 1
/* 00E094 8000D494 0243082A */  slt   $at, $s2, $v1
/* 00E098 8000D498 1420FFF4 */  bnez  $at, .L8000D46C
/* 00E09C 8000D49C 00000000 */   nop   
/* 00E0A0 8000D4A0 10000001 */  b     .L8000D4A8
/* 00E0A4 8000D4A4 00009025 */   move  $s2, $zero
.L8000D4A8:
/* 00E0A8 8000D4A8 8FAE0144 */  lw    $t6, 0x144($sp)
/* 00E0AC 8000D4AC 240F0004 */  li    $t7, 4
/* 00E0B0 8000D4B0 028E082A */  slt   $at, $s4, $t6
/* 00E0B4 8000D4B4 10200003 */  beqz  $at, .L8000D4C4
/* 00E0B8 8000D4B8 00103080 */   sll   $a2, $s0, 2
/* 00E0BC 8000D4BC 10000002 */  b     .L8000D4C8
/* 00E0C0 8000D4C0 A6D4000E */   sh    $s4, 0xe($s6)
.L8000D4C4:
/* 00E0C4 8000D4C4 A6CF000E */  sh    $t7, 0xe($s6)
.L8000D4C8:
/* 00E0C8 8000D4C8 14440005 */  bne   $v0, $a0, .L8000D4E0
/* 00E0CC 8000D4CC 27AD00F4 */   addiu $t5, $sp, 0xf4
/* 00E0D0 8000D4D0 86D8000E */  lh    $t8, 0xe($s6)
/* 00E0D4 8000D4D4 24010004 */  li    $at, 4
/* 00E0D8 8000D4D8 1301012E */  beq   $t8, $at, .L8000D994
/* 00E0DC 8000D4DC 00000000 */   nop   
.L8000D4E0:
/* 00E0E0 8000D4E0 3C028012 */  lui   $v0, %hi(D_8011AD3C) # $v0, 0x8012
/* 00E0E4 8000D4E4 00CD9821 */  addu  $s3, $a2, $t5
/* 00E0E8 8000D4E8 27B900D4 */  addiu $t9, $sp, 0xd4
/* 00E0EC 8000D4EC 8042AD3C */  lb    $v0, %lo(D_8011AD3C)($v0)
/* 00E0F0 8000D4F0 00D97021 */  addu  $t6, $a2, $t9
/* 00E0F4 8000D4F4 27AD0094 */  addiu $t5, $sp, 0x94
/* 00E0F8 8000D4F8 27AF00B4 */  addiu $t7, $sp, 0xb4
/* 00E0FC 8000D4FC 00CFC021 */  addu  $t8, $a2, $t7
/* 00E100 8000D500 00CDC821 */  addu  $t9, $a2, $t5
/* 00E104 8000D504 24010001 */  li    $at, 1
/* 00E108 8000D508 AFB90044 */  sw    $t9, 0x44($sp)
/* 00E10C 8000D50C AFB80048 */  sw    $t8, 0x48($sp)
/* 00E110 8000D510 AFAE004C */  sw    $t6, 0x4c($sp)
/* 00E114 8000D514 14410012 */  bne   $v0, $at, .L8000D560
/* 00E118 8000D518 24110001 */   li    $s1, 1
/* 00E11C 8000D51C 16000009 */  bnez  $s0, .L8000D544
/* 00E120 8000D520 3C188012 */   lui   $t8, %hi(D_8011AD24+1) # $t8, 0x8012
/* 00E124 8000D524 3C0E8012 */  lui   $t6, %hi(D_8011AD24+1) # $t6, 0x8012
/* 00E128 8000D528 81CEAD25 */  lb    $t6, %lo(D_8011AD24+1)($t6)
# Indexing into gBossVehicles only reading the MSB?
/* 00E12C 8000D52C 3C1E800E */  lui   $fp, %hi(gBossVehicles) # $fp, 0x800e
/* 00E130 8000D530 000E7840 */  sll   $t7, $t6, 1
/* 00E134 8000D534 03CFF021 */  addu  $fp, $fp, $t7
/* 00E138 8000D538 83DEC820 */  lb    $fp, %lo(gBossVehicles)($fp)
/* 00E13C 8000D53C 10000028 */  b     .L8000D5E0
/* 00E140 8000D540 00000000 */   nop   
.L8000D544:
/* 00E144 8000D544 8318AD25 */  lb    $t8, %lo(D_8011AD24+1)($t8)
# Indexing into gBossVehicles only reading the LSB?
/* 00E148 8000D548 3C1E800E */  lui   $fp, %hi(gBossVehicles) # $fp, 0x800e
/* 00E14C 8000D54C 00186840 */  sll   $t5, $t8, 1
/* 00E150 8000D550 03CDF021 */  addu  $fp, $fp, $t5
/* 00E154 8000D554 83DEC821 */  lb    $fp, %lo(gBossVehicles+1)($fp)
/* 00E158 8000D558 10000021 */  b     .L8000D5E0
/* 00E15C 8000D55C 00000000 */   nop   
.L8000D560:
/* 00E160 8000D560 24010002 */  li    $at, 2
/* 00E164 8000D564 14410006 */  bne   $v0, $at, .L8000D580
/* 00E168 8000D568 00000000 */   nop   
/* 00E16C 8000D56C 8FB90078 */  lw    $t9, 0x78($sp)
/* 00E170 8000D570 00000000 */  nop   
/* 00E174 8000D574 833E004D */  lb    $fp, 0x4d($t9)
/* 00E178 8000D578 10000019 */  b     .L8000D5E0
/* 00E17C 8000D57C 00000000 */   nop   
.L8000D580:
/* 00E180 8000D580 86CE000E */  lh    $t6, 0xe($s6)
/* 00E184 8000D584 24010004 */  li    $at, 4
/* 00E188 8000D588 11C10006 */  beq   $t6, $at, .L8000D5A4
/* 00E18C 8000D58C 00002025 */   move  $a0, $zero
/* 00E190 8000D590 0C01B067 */  jal   func_8006C19C
/* 00E194 8000D594 AFA60054 */   sw    $a2, 0x54($sp)
/* 00E198 8000D598 8FA60054 */  lw    $a2, 0x54($sp)
/* 00E19C 8000D59C 10400006 */  beqz  $v0, .L8000D5B8
/* 00E1A0 8000D5A0 00002025 */   move  $a0, $zero
.L8000D5A4:
/* 00E1A4 8000D5A4 0C027094 */  jal   get_player_selected_vehicle
/* 00E1A8 8000D5A8 AFA60054 */   sw    $a2, 0x54($sp)
/* 00E1AC 8000D5AC 8FA60054 */  lw    $a2, 0x54($sp)
/* 00E1B0 8000D5B0 1000000B */  b     .L8000D5E0
/* 00E1B4 8000D5B4 0040F025 */   move  $fp, $v0
.L8000D5B8:
/* 00E1B8 8000D5B8 8FAF0144 */  lw    $t7, 0x144($sp)
/* 00E1BC 8000D5BC 00000000 */  nop   
/* 00E1C0 8000D5C0 29E10002 */  slti  $at, $t7, 2
/* 00E1C4 8000D5C4 14200006 */  bnez  $at, .L8000D5E0
/* 00E1C8 8000D5C8 00000000 */   nop   
/* 00E1CC 8000D5CC 86C4000E */  lh    $a0, 0xe($s6)
/* 00E1D0 8000D5D0 0C027094 */  jal   get_player_selected_vehicle
/* 00E1D4 8000D5D4 AFA60054 */   sw    $a2, 0x54($sp)
/* 00E1D8 8000D5D8 8FA60054 */  lw    $a2, 0x54($sp)
/* 00E1DC 8000D5DC 0040F025 */  move  $fp, $v0
.L8000D5E0:
/* 00E1E0 8000D5E0 3C188012 */  lui   $t8, %hi(D_8011AD3C) # $t8, 0x8012
/* 00E1E4 8000D5E4 8318AD3C */  lb    $t8, %lo(D_8011AD3C)($t8)
/* 00E1E8 8000D5E8 86C3000E */  lh    $v1, 0xe($s6)
/* 00E1EC 8000D5EC 24010002 */  li    $at, 2
/* 00E1F0 8000D5F0 17010010 */  bne   $t8, $at, .L8000D634
/* 00E1F4 8000D5F4 3C0D800E */   lui   $t5, %hi(D_800DC840) # $t5, 0x800e
/* 00E1F8 8000D5F8 01B06821 */  addu  $t5, $t5, $s0
/* 00E1FC 8000D5FC 81ADC840 */  lb    $t5, %lo(D_800DC840)($t5)
/* 00E200 8000D600 001E7080 */  sll   $t6, $fp, 2
/* 00E204 8000D604 01DE7021 */  addu  $t6, $t6, $fp
/* 00E208 8000D608 000DC840 */  sll   $t9, $t5, 1
/* 00E20C 8000D60C 000E7880 */  sll   $t7, $t6, 2
/* 00E210 8000D610 032FC021 */  addu  $t8, $t9, $t7
/* 00E214 8000D614 00146880 */  sll   $t5, $s4, 2
/* 00E218 8000D618 3C02800E */  lui   $v0, %hi(D_800DC7A8) # $v0, 0x800e
/* 00E21C 8000D61C 00581021 */  addu  $v0, $v0, $t8
/* 00E220 8000D620 01B46823 */  subu  $t5, $t5, $s4
/* 00E224 8000D624 000D68C0 */  sll   $t5, $t5, 3
/* 00E228 8000D628 8442C7A8 */  lh    $v0, %lo(D_800DC7A8)($v0)
/* 00E22C 8000D62C 1000001A */  b     .L8000D698
/* 00E230 8000D630 02ED3821 */   addu  $a3, $s7, $t5
.L8000D634:
/* 00E234 8000D634 2BC10005 */  slti  $at, $fp, 5
/* 00E238 8000D638 10200010 */  beqz  $at, .L8000D67C
/* 00E23C 8000D63C 001EC840 */   sll   $t9, $fp, 1
/* 00E240 8000D640 02950019 */  multu $s4, $s5
/* 00E244 8000D644 001EC080 */  sll   $t8, $fp, 2
/* 00E248 8000D648 031EC021 */  addu  $t8, $t8, $fp
/* 00E24C 8000D64C 00186880 */  sll   $t5, $t8, 2
/* 00E250 8000D650 3C02800E */  lui   $v0, %hi(D_800DC7A8) # $v0, 0x800e
/* 00E254 8000D654 00007012 */  mflo  $t6
/* 00E258 8000D658 02EE3821 */  addu  $a3, $s7, $t6
/* 00E25C 8000D65C 80F90059 */  lb    $t9, 0x59($a3)
/* 00E260 8000D660 00000000 */  nop   
/* 00E264 8000D664 00197840 */  sll   $t7, $t9, 1
/* 00E268 8000D668 01ED7021 */  addu  $t6, $t7, $t5
/* 00E26C 8000D66C 004E1021 */  addu  $v0, $v0, $t6
/* 00E270 8000D670 8442C7A8 */  lh    $v0, %lo(D_800DC7A8)($v0)
/* 00E274 8000D674 10000009 */  b     .L8000D69C
/* 00E278 8000D678 304F0100 */   andi  $t7, $v0, 0x100
.L8000D67C:
# Indexing into D_800DC7B8 starting at index 37?
/* 00E27C 8000D67C 3C02800E */  lui   $v0, %hi(D_800DC7B8) # $v0, 0x800e
/* 00E280 8000D680 0014C080 */  sll   $t8, $s4, 2
/* 00E284 8000D684 0314C023 */  subu  $t8, $t8, $s4
/* 00E288 8000D688 00591021 */  addu  $v0, $v0, $t9
/* 00E28C 8000D68C 0018C0C0 */  sll   $t8, $t8, 3
/* 00E290 8000D690 8442C802 */  lh    $v0, %lo(D_800DC7B8+0x4A)/*-0x37fe*/($v0)
/* 00E294 8000D694 02F83821 */  addu  $a3, $s7, $t8
.L8000D698:
/* 00E298 8000D698 304F0100 */  andi  $t7, $v0, 0x100
.L8000D69C:
/* 00E29C 8000D69C 000F6843 */  sra   $t5, $t7, 1
/* 00E2A0 8000D6A0 35AE0010 */  ori   $t6, $t5, 0x10
/* 00E2A4 8000D6A4 A2C20000 */  sb    $v0, ($s6)
/* 00E2A8 8000D6A8 A2CE0001 */  sb    $t6, 1($s6)
/* 00E2AC 8000D6AC 8E790000 */  lw    $t9, ($s3)
/* 00E2B0 8000D6B0 24010004 */  li    $at, 4
/* 00E2B4 8000D6B4 A6D90002 */  sh    $t9, 2($s6)
/* 00E2B8 8000D6B8 8FB8004C */  lw    $t8, 0x4c($sp)
/* 00E2BC 8000D6BC 24040001 */  li    $a0, 1
/* 00E2C0 8000D6C0 8F0F0000 */  lw    $t7, ($t8)
/* 00E2C4 8000D6C4 00000000 */  nop   
/* 00E2C8 8000D6C8 A6CF0004 */  sh    $t7, 4($s6)
/* 00E2CC 8000D6CC 8FAD0048 */  lw    $t5, 0x48($sp)
/* 00E2D0 8000D6D0 00000000 */  nop   
/* 00E2D4 8000D6D4 8DAE0000 */  lw    $t6, ($t5)
/* 00E2D8 8000D6D8 00000000 */  nop   
/* 00E2DC 8000D6DC A6CE0006 */  sh    $t6, 6($s6)
/* 00E2E0 8000D6E0 8FB90044 */  lw    $t9, 0x44($sp)
/* 00E2E4 8000D6E4 00000000 */  nop   
/* 00E2E8 8000D6E8 8F380000 */  lw    $t8, ($t9)
/* 00E2EC 8000D6EC 14610008 */  bne   $v1, $at, .L8000D710
/* 00E2F0 8000D6F0 A6D8000C */   sh    $t8, 0xc($s6)
/* 00E2F4 8000D6F4 AFA60054 */  sw    $a2, 0x54($sp)
/* 00E2F8 8000D6F8 0C01867D */  jal   func_800619F4
/* 00E2FC 8000D6FC AFA7005C */   sw    $a3, 0x5c($sp)
/* 00E300 8000D700 8FA60054 */  lw    $a2, 0x54($sp)
/* 00E304 8000D704 8FA7005C */  lw    $a3, 0x5c($sp)
/* 00E308 8000D708 86C3000E */  lh    $v1, 0xe($s6)
/* 00E30C 8000D70C 00000000 */  nop   
.L8000D710:
/* 00E310 8000D710 24010004 */  li    $at, 4
/* 00E314 8000D714 14610007 */  bne   $v1, $at, .L8000D734
/* 00E318 8000D718 00002025 */   move  $a0, $zero
/* 00E31C 8000D71C 8FAF0144 */  lw    $t7, 0x144($sp)
/* 00E320 8000D720 24110005 */  li    $s1, 5
/* 00E324 8000D724 29E10002 */  slti  $at, $t7, 2
/* 00E328 8000D728 14200002 */  bnez  $at, .L8000D734
/* 00E32C 8000D72C 362D0008 */   ori   $t5, $s1, 8
/* 00E330 8000D730 01A08825 */  move  $s1, $t5
.L8000D734:
/* 00E334 8000D734 24010004 */  li    $at, 4
/* 00E338 8000D738 10610007 */  beq   $v1, $at, .L8000D758
/* 00E33C 8000D73C 2BC10005 */   slti  $at, $fp, 5
/* 00E340 8000D740 8FAE0144 */  lw    $t6, 0x144($sp)
/* 00E344 8000D744 24010001 */  li    $at, 1
/* 00E348 8000D748 15C10002 */  bne   $t6, $at, .L8000D754
/* 00E34C 8000D74C 36390010 */   ori   $t9, $s1, 0x10
/* 00E350 8000D750 03208825 */  move  $s1, $t9
.L8000D754:
/* 00E354 8000D754 2BC10005 */  slti  $at, $fp, 5
.L8000D758:
/* 00E358 8000D758 14200008 */  bnez  $at, .L8000D77C
/* 00E35C 8000D75C 00000000 */   nop   
/* 00E360 8000D760 24110001 */  li    $s1, 1
/* 00E364 8000D764 AFA60054 */  sw    $a2, 0x54($sp)
/* 00E368 8000D768 0C01867D */  jal   func_800619F4
/* 00E36C 8000D76C AFA7005C */   sw    $a3, 0x5c($sp)
/* 00E370 8000D770 8FA60054 */  lw    $a2, 0x54($sp)
/* 00E374 8000D774 8FA7005C */  lw    $a3, 0x5c($sp)
/* 00E378 8000D778 00000000 */  nop   
.L8000D77C:
/* 00E37C 8000D77C 02C02025 */  move  $a0, $s6
/* 00E380 8000D780 02202825 */  move  $a1, $s1
/* 00E384 8000D784 AFA60054 */  sw    $a2, 0x54($sp)
/* 00E388 8000D788 0C003A95 */  jal   spawn_object
/* 00E38C 8000D78C AFA7005C */   sw    $a3, 0x5c($sp)
/* 00E390 8000D790 8FB80044 */  lw    $t8, 0x44($sp)
/* 00E394 8000D794 8FA60054 */  lw    $a2, 0x54($sp)
/* 00E398 8000D798 8F0F0000 */  lw    $t7, ($t8)
/* 00E39C 8000D79C 8FA7005C */  lw    $a3, 0x5c($sp)
/* 00E3A0 8000D7A0 3C0D8012 */  lui   $t5, %hi(gRacers) # $t5, 0x8012
/* 00E3A4 8000D7A4 A44F0000 */  sh    $t7, ($v0)
/* 00E3A8 8000D7A8 8DADAEE4 */  lw    $t5, %lo(gRacers)($t5)
/* 00E3AC 8000D7AC 3C198012 */  lui   $t9, %hi(gRacersByPosition) # $t9, 0x8012
/* 00E3B0 8000D7B0 01A67021 */  addu  $t6, $t5, $a2
/* 00E3B4 8000D7B4 ADC20000 */  sw    $v0, ($t6)
/* 00E3B8 8000D7B8 8F39AEE8 */  lw    $t9, %lo(gRacersByPosition)($t9)
/* 00E3BC 8000D7BC 3C0F8012 */  lui   $t7, %hi(gRacersByPort) # $t7, 0x8012
/* 00E3C0 8000D7C0 0326C021 */  addu  $t8, $t9, $a2
/* 00E3C4 8000D7C4 AF020000 */  sw    $v0, ($t8)
/* 00E3C8 8000D7C8 8DEFAEEC */  lw    $t7, %lo(gRacersByPort)($t7)
/* 00E3CC 8000D7CC 00146880 */  sll   $t5, $s4, 2
/* 00E3D0 8000D7D0 01ED7021 */  addu  $t6, $t7, $t5
/* 00E3D4 8000D7D4 ADC20000 */  sw    $v0, ($t6)
/* 00E3D8 8000D7D8 8C530064 */  lw    $s3, 0x64($v0)
/* 00E3DC 8000D7DC AC40003C */  sw    $zero, 0x3c($v0)
/* 00E3E0 8000D7E0 A27E01D6 */  sb    $fp, 0x1d6($s3)
/* 00E3E4 8000D7E4 A27E01D7 */  sb    $fp, 0x1d7($s3)
/* 00E3E8 8000D7E8 83B90127 */  lb    $t9, 0x127($sp)
/* 00E3EC 8000D7EC 2401FFFF */  li    $at, -1
/* 00E3F0 8000D7F0 13210005 */  beq   $t9, $at, .L8000D808
/* 00E3F4 8000D7F4 00408825 */   move  $s1, $v0
/* 00E3F8 8000D7F8 133E0003 */  beq   $t9, $fp, .L8000D808
/* 00E3FC 8000D7FC 24180001 */   li    $t8, 1
/* 00E400 8000D800 3C018012 */  lui   $at, %hi(D_8011AD20) # $at, 0x8012
/* 00E404 8000D804 A038AD20 */  sb    $t8, %lo(D_8011AD20)($at)
.L8000D808:
/* 00E408 8000D808 A3BE0127 */  sb    $fp, 0x127($sp)
/* 00E40C 8000D80C 826201D6 */  lb    $v0, 0x1d6($s3)
/* 00E410 8000D810 24010002 */  li    $at, 2
/* 00E414 8000D814 10410005 */  beq   $v0, $at, .L8000D82C
/* 00E418 8000D818 240F0001 */   li    $t7, 1
/* 00E41C 8000D81C 24010007 */  li    $at, 7
/* 00E420 8000D820 10410002 */  beq   $v0, $at, .L8000D82C
/* 00E424 8000D824 24010008 */   li    $at, 8
/* 00E428 8000D828 14410002 */  bne   $v0, $at, .L8000D834
.L8000D82C:
/* 00E42C 8000D82C 3C018012 */   lui   $at, %hi(gIsNonCarRacers) # $at, 0x8012
/* 00E430 8000D830 A02FAE02 */  sb    $t7, %lo(gIsNonCarRacers)($at)
.L8000D834:
/* 00E434 8000D834 A27E01CB */  sb    $fp, 0x1cb($s3)
/* 00E438 8000D838 826201CB */  lb    $v0, 0x1cb($s3)
/* 00E43C 8000D83C 3C19800E */  lui   $t9, %hi(D_800DC840) # $t9, 0x800e
/* 00E440 8000D840 04400003 */  bltz  $v0, .L8000D850
/* 00E444 8000D844 28410003 */   slti  $at, $v0, 3
/* 00E448 8000D848 14200002 */  bnez  $at, .L8000D854
/* 00E44C 8000D84C 00000000 */   nop   
.L8000D850:
/* 00E450 8000D850 A26001CB */  sb    $zero, 0x1cb($s3)
.L8000D854:
/* 00E454 8000D854 A2740002 */  sb    $s4, 2($s3)
/* 00E458 8000D858 80ED0059 */  lb    $t5, 0x59($a3)
/* 00E45C 8000D85C 3C0E8012 */  lui   $t6, %hi(D_8011AD3C) # $t6, 0x8012
/* 00E460 8000D860 A26D0003 */  sb    $t5, 3($s3)
/* 00E464 8000D864 81CEAD3C */  lb    $t6, %lo(D_8011AD3C)($t6)
/* 00E468 8000D868 24010002 */  li    $at, 2
/* 00E46C 8000D86C 15C10004 */  bne   $t6, $at, .L8000D880
/* 00E470 8000D870 0330C821 */   addu  $t9, $t9, $s0
/* 00E474 8000D874 8339C840 */  lb    $t9, %lo(D_800DC840)($t9)
/* 00E478 8000D878 10000004 */  b     .L8000D88C
/* 00E47C 8000D87C A2790003 */   sb    $t9, 3($s3)
.L8000D880:
/* 00E480 8000D880 80F80059 */  lb    $t8, 0x59($a3)
/* 00E484 8000D884 00000000 */  nop   
/* 00E488 8000D888 A2780003 */  sb    $t8, 3($s3)
.L8000D88C:
/* 00E48C 8000D88C 8FAF0068 */  lw    $t7, 0x68($sp)
/* 00E490 8000D890 24010040 */  li    $at, 64
/* 00E494 8000D894 15E10003 */  bne   $t7, $at, .L8000D8A4
/* 00E498 8000D898 240D0008 */   li    $t5, 8
/* 00E49C 8000D89C 10000002 */  b     .L8000D8A8
/* 00E4A0 8000D8A0 A26D0185 */   sb    $t5, 0x185($s3)
.L8000D8A4:
/* 00E4A4 8000D8A4 A2600185 */  sb    $zero, 0x185($s3)
.L8000D8A8:
/* 00E4A8 8000D8A8 0C0270C3 */  jal   get_filtered_cheats
/* 00E4AC 8000D8AC 00000000 */   nop   
/* 00E4B0 8000D8B0 304E0080 */  andi  $t6, $v0, 0x80
/* 00E4B4 8000D8B4 11C0000B */  beqz  $t6, .L8000D8E4
/* 00E4B8 8000D8B8 8FAD0138 */   lw    $t5, 0x138($sp)
/* 00E4BC 8000D8BC 8FB90064 */  lw    $t9, 0x64($sp)
/* 00E4C0 8000D8C0 00000000 */  nop   
/* 00E4C4 8000D8C4 17200007 */  bnez  $t9, .L8000D8E4
/* 00E4C8 8000D8C8 8FAD0138 */   lw    $t5, 0x138($sp)
/* 00E4CC 8000D8CC 86780000 */  lh    $t8, ($s3)
/* 00E4D0 8000D8D0 2401FFFF */  li    $at, -1
/* 00E4D4 8000D8D4 13010002 */  beq   $t8, $at, .L8000D8E0
/* 00E4D8 8000D8D8 240F000A */   li    $t7, 10
/* 00E4DC 8000D8DC A26F0185 */  sb    $t7, 0x185($s3)
.L8000D8E0:
/* 00E4E0 8000D8E0 8FAD0138 */  lw    $t5, 0x138($sp)
.L8000D8E4:
/* 00E4E4 8000D8E4 24010001 */  li    $at, 1
/* 00E4E8 8000D8E8 15A10004 */  bne   $t5, $at, .L8000D8FC
/* 00E4EC 8000D8EC 3C0E8012 */   lui   $t6, %hi(D_8011AD3C) # $t6, 0x8012
/* 00E4F0 8000D8F0 81CEAD3C */  lb    $t6, %lo(D_8011AD3C)($t6)
/* 00E4F4 8000D8F4 24010002 */  li    $at, 2
/* 00E4F8 8000D8F8 15C10009 */  bne   $t6, $at, .L8000D920
.L8000D8FC:
/* 00E4FC 8000D8FC 2BC10005 */   slti  $at, $fp, 5
/* 00E500 8000D900 10200007 */  beqz  $at, .L8000D920
/* 00E504 8000D904 00000000 */   nop   
/* 00E508 8000D908 82640003 */  lb    $a0, 3($s3)
/* 00E50C 8000D90C 826501D6 */  lb    $a1, 0x1d6($s3)
/* 00E510 8000D910 0C0012D0 */  jal   func_80004B40
/* 00E514 8000D914 00000000 */   nop   
/* 00E518 8000D918 10000002 */  b     .L8000D924
/* 00E51C 8000D91C AE620118 */   sw    $v0, 0x118($s3)
.L8000D920:
/* 00E520 8000D920 AE600118 */  sw    $zero, 0x118($s3)
.L8000D924:
/* 00E524 8000D924 82790003 */  lb    $t9, 3($s3)
/* 00E528 8000D928 8FB80128 */  lw    $t8, 0x128($sp)
/* 00E52C 8000D92C 00000000 */  nop   
/* 00E530 8000D930 03387821 */  addu  $t7, $t9, $t8
/* 00E534 8000D934 81ED0000 */  lb    $t5, ($t7)
/* 00E538 8000D938 8E39004C */  lw    $t9, 0x4c($s1)
/* 00E53C 8000D93C 25AE0001 */  addiu $t6, $t5, 1
/* 00E540 8000D940 A32E0012 */  sb    $t6, 0x12($t9)
/* 00E544 8000D944 827801D6 */  lb    $t8, 0x1d6($s3)
/* 00E548 8000D948 00000000 */  nop   
/* 00E54C 8000D94C 270FFFFB */  addiu $t7, $t8, -5
/* 00E550 8000D950 2DE10009 */  sltiu $at, $t7, 9
/* 00E554 8000D954 1020000D */  beqz  $at, .L8000D98C
/* 00E558 8000D958 000F7880 */   sll   $t7, $t7, 2
/* 00E55C 8000D95C 3C01800E */  lui   $at, %hi(jpt_800E5154) # $at, 0x800e
/* 00E560 8000D960 002F0821 */  addu  $at, $at, $t7
/* 00E564 8000D964 8C2F5154 */  lw    $t7, %lo(jpt_800E5154)($at)
/* 00E568 8000D968 00000000 */  nop   
/* 00E56C 8000D96C 01E00008 */  jr    $t7
/* 00E570 8000D970 00000000 */   nop   
glabel L8000D974
/* 00E574 8000D974 02202025 */  move  $a0, $s1
/* 00E578 8000D978 0C0170BC */  jal   func_8005C2F0
/* 00E57C 8000D97C 02602825 */   move  $a1, $s3
/* 00E580 8000D980 8FA40068 */  lw    $a0, 0x68($sp)
/* 00E584 8000D984 10000003 */  b     .L8000D994
/* 00E588 8000D988 24020005 */   li    $v0, 5
.L8000D98C:
glabel L8000D98C
/* 00E58C 8000D98C 8FA40068 */  lw    $a0, 0x68($sp)
/* 00E590 8000D990 24020005 */  li    $v0, 5
.L8000D994:
/* 00E594 8000D994 3C038012 */  lui   $v1, %hi(gNumRacers) # $v1, 0x8012
/* 00E598 8000D998 8C63AEF0 */  lw    $v1, %lo(gNumRacers)($v1)
/* 00E59C 8000D99C 26100001 */  addiu $s0, $s0, 1
/* 00E5A0 8000D9A0 0203082A */  slt   $at, $s0, $v1
/* 00E5A4 8000D9A4 1420FEA6 */  bnez  $at, .L8000D440
/* 00E5A8 8000D9A8 00000000 */   nop   
.L8000D9AC:
/* 00E5AC 8000D9AC 8FA40068 */  lw    $a0, 0x68($sp)
/* 00E5B0 8000D9B0 24010008 */  li    $at, 8
/* 00E5B4 8000D9B4 10810003 */  beq   $a0, $at, .L8000D9C4
/* 00E5B8 8000D9B8 0000A025 */   move  $s4, $zero
/* 00E5BC 8000D9BC 3C018012 */  lui   $at, %hi(D_8011AD3C) # $at, 0x8012
/* 00E5C0 8000D9C0 A020AD3C */  sb    $zero, %lo(D_8011AD3C)($at)
.L8000D9C4:
/* 00E5C4 8000D9C4 3C0D8012 */  lui   $t5, %hi(D_8011AD3C) # $t5, 0x8012
/* 00E5C8 8000D9C8 81ADAD3C */  lb    $t5, %lo(D_8011AD3C)($t5)
/* 00E5CC 8000D9CC 00000000 */  nop   
/* 00E5D0 8000D9D0 11A00002 */  beqz  $t5, .L8000D9DC
/* 00E5D4 8000D9D4 3C018012 */   lui   $at, %hi(D_8011AD20) # $at, 0x8012
/* 00E5D8 8000D9D8 A020AD20 */  sb    $zero, %lo(D_8011AD20)($at)
.L8000D9DC:
/* 00E5DC 8000D9DC 0C01B683 */  jal   get_render_context
/* 00E5E0 8000D9E0 00000000 */   nop   
/* 00E5E4 8000D9E4 1440002D */  bnez  $v0, .L8000DA9C
/* 00E5E8 8000D9E8 3C028012 */   lui   $v0, %hi(objCount) # $v0, 0x8012
/* 00E5EC 8000D9EC 8C42AE5C */  lw    $v0, %lo(objCount)($v0)
/* 00E5F0 8000D9F0 0000A825 */  move  $s5, $zero
/* 00E5F4 8000D9F4 18400029 */  blez  $v0, .L8000DA9C
/* 00E5F8 8000D9F8 3C138012 */   lui   $s3, %hi(gObjPtrList) # $s3, 0x8012
/* 00E5FC 8000D9FC 2673AE58 */  addiu $s3, %lo(gObjPtrList) # addiu $s3, $s3, -0x51a8
.L8000DA00:
/* 00E600 8000DA00 8E6E0000 */  lw    $t6, ($s3)
/* 00E604 8000DA04 3C0D8012 */  lui   $t5, %hi(gIsTimeTrial) # $t5, 0x8012
/* 00E608 8000DA08 01D5C821 */  addu  $t9, $t6, $s5
/* 00E60C 8000DA0C 8F310000 */  lw    $s1, ($t9)
/* 00E610 8000DA10 00000000 */  nop   
/* 00E614 8000DA14 8E380040 */  lw    $t8, 0x40($s1)
/* 00E618 8000DA18 00000000 */  nop   
/* 00E61C 8000DA1C 97100030 */  lhu   $s0, 0x30($t8)
/* 00E620 8000DA20 00000000 */  nop   
/* 00E624 8000DA24 320F0020 */  andi  $t7, $s0, 0x20
/* 00E628 8000DA28 11E0000B */  beqz  $t7, .L8000DA58
/* 00E62C 8000DA2C 320E0040 */   andi  $t6, $s0, 0x40
/* 00E630 8000DA30 91ADAEF5 */  lbu   $t5, %lo(gIsTimeTrial)($t5)
/* 00E634 8000DA34 00000000 */  nop   
/* 00E638 8000DA38 11A00007 */  beqz  $t5, .L8000DA58
/* 00E63C 8000DA3C 00000000 */   nop   
/* 00E640 8000DA40 0C003FEE */  jal   gParticlePtrList_addObject
/* 00E644 8000DA44 02202025 */   move  $a0, $s1
/* 00E648 8000DA48 3C028012 */  lui   $v0, %hi(objCount) # $v0, 0x8012
/* 00E64C 8000DA4C 8C42AE5C */  lw    $v0, %lo(objCount)($v0)
/* 00E650 8000DA50 1000000E */  b     .L8000DA8C
/* 00E654 8000DA54 26520001 */   addiu $s2, $s2, 1
.L8000DA58:
/* 00E658 8000DA58 11C0000B */  beqz  $t6, .L8000DA88
/* 00E65C 8000DA5C 00000000 */   nop   
/* 00E660 8000DA60 8FB90144 */  lw    $t9, 0x144($sp)
/* 00E664 8000DA64 00000000 */  nop   
/* 00E668 8000DA68 2B210002 */  slti  $at, $t9, 2
/* 00E66C 8000DA6C 14200006 */  bnez  $at, .L8000DA88
/* 00E670 8000DA70 00000000 */   nop   
/* 00E674 8000DA74 0C003FEE */  jal   gParticlePtrList_addObject
/* 00E678 8000DA78 02202025 */   move  $a0, $s1
/* 00E67C 8000DA7C 3C028012 */  lui   $v0, %hi(objCount) # $v0, 0x8012
/* 00E680 8000DA80 8C42AE5C */  lw    $v0, %lo(objCount)($v0)
/* 00E684 8000DA84 00000000 */  nop   
.L8000DA88:
/* 00E688 8000DA88 26520001 */  addiu $s2, $s2, 1
.L8000DA8C:
/* 00E68C 8000DA8C 0242082A */  slt   $at, $s2, $v0
/* 00E690 8000DA90 1420FFDB */  bnez  $at, .L8000DA00
/* 00E694 8000DA94 26B50004 */   addiu $s5, $s5, 4
/* 00E698 8000DA98 00009025 */  move  $s2, $zero
.L8000DA9C:
/* 00E69C 8000DA9C 3C15800E */  lui   $s5, %hi(D_800DC718) # $s5, 0x800e
/* 00E6A0 8000DAA0 26B5C718 */  addiu $s5, %lo(D_800DC718) # addiu $s5, $s5, -0x38e8
/* 00E6A4 8000DAA4 0C0166D3 */  jal   free_tt_ghost_data
/* 00E6A8 8000DAA8 AEA00000 */   sw    $zero, ($s5)
/* 00E6AC 8000DAAC 3C118012 */  lui   $s1, %hi(D_8011AD38) # $s1, 0x8012
/* 00E6B0 8000DAB0 2631AD38 */  addiu $s1, %lo(D_8011AD38) # addiu $s1, $s1, -0x52c8
/* 00E6B4 8000DAB4 2418FFFF */  li    $t8, -1
/* 00E6B8 8000DAB8 AE380000 */  sw    $t8, ($s1)
/* 00E6BC 8000DABC 3C0F8012 */  lui   $t7, %hi(gIsTimeTrial) # $t7, 0x8012
/* 00E6C0 8000DAC0 91EFAEF5 */  lbu   $t7, %lo(gIsTimeTrial)($t7)
/* 00E6C4 8000DAC4 00000000 */  nop   
/* 00E6C8 8000DAC8 11E00071 */  beqz  $t7, .L8000DC90
/* 00E6CC 8000DACC 00000000 */   nop   
/* 00E6D0 8000DAD0 8FAD0144 */  lw    $t5, 0x144($sp)
/* 00E6D4 8000DAD4 24010001 */  li    $at, 1
/* 00E6D8 8000DAD8 15A1006D */  bne   $t5, $at, .L8000DC90
/* 00E6DC 8000DADC 00000000 */   nop   
/* 00E6E0 8000DAE0 0C016651 */  jal   func_80059944
/* 00E6E4 8000DAE4 00000000 */   nop   
/* 00E6E8 8000DAE8 0C006D9A */  jal   func_8001B668
/* 00E6EC 8000DAEC 00002025 */   move  $a0, $zero
/* 00E6F0 8000DAF0 3C10800E */  lui   $s0, %hi(D_800DC728) # $s0, 0x800e
/* 00E6F4 8000DAF4 AE220000 */  sw    $v0, ($s1)
/* 00E6F8 8000DAF8 3C01800E */  lui   $at, %hi(gHasGhostToSave) # $at, 0x800e
/* 00E6FC 8000DAFC 2610C728 */  addiu $s0, %lo(D_800DC728) # addiu $s0, $s0, -0x38d8
/* 00E700 8000DB00 A020C730 */  sb    $zero, %lo(gHasGhostToSave)($at)
/* 00E704 8000DB04 860E0000 */  lh    $t6, ($s0)
/* 00E708 8000DB08 00000000 */  nop   
/* 00E70C 8000DB0C 29C10005 */  slti  $at, $t6, 5
/* 00E710 8000DB10 14200002 */  bnez  $at, .L8000DB1C
/* 00E714 8000DB14 00000000 */   nop   
/* 00E718 8000DB18 A6000000 */  sh    $zero, ($s0)
.L8000DB1C:
/* 00E71C 8000DB1C 0C006CA2 */  jal   func_8001B288
/* 00E720 8000DB20 00000000 */   nop   
/* 00E724 8000DB24 1040002C */  beqz  $v0, .L8000DBD8
/* 00E728 8000DB28 3C19800E */   lui   $t9, %hi(D_800DC72C) # $t9, 0x800e
/* 00E72C 8000DB2C 860F0000 */  lh    $t7, ($s0)
/* 00E730 8000DB30 8739C72C */  lh    $t9, %lo(D_800DC72C)($t9)
/* 00E734 8000DB34 000F6880 */  sll   $t5, $t7, 2
/* 00E738 8000DB38 01AF6821 */  addu  $t5, $t5, $t7
/* 00E73C 8000DB3C 000D7080 */  sll   $t6, $t5, 2
/* 00E740 8000DB40 0019C040 */  sll   $t8, $t9, 1
/* 00E744 8000DB44 030EC821 */  addu  $t9, $t8, $t6
/* 00E748 8000DB48 3C02800E */  lui   $v0, %hi(D_800DC7A8) # $v0, 0x800e
/* 00E74C 8000DB4C 00591021 */  addu  $v0, $v0, $t9
/* 00E750 8000DB50 8442C7A8 */  lh    $v0, %lo(D_800DC7A8)($v0)
/* 00E754 8000DB54 02C02025 */  move  $a0, $s6
/* 00E758 8000DB58 304F0100 */  andi  $t7, $v0, 0x100
/* 00E75C 8000DB5C 000F6843 */  sra   $t5, $t7, 1
/* 00E760 8000DB60 35B80010 */  ori   $t8, $t5, 0x10
/* 00E764 8000DB64 A2D80001 */  sb    $t8, 1($s6)
/* 00E768 8000DB68 A2C20000 */  sb    $v0, ($s6)
/* 00E76C 8000DB6C 8FAE00F4 */  lw    $t6, 0xf4($sp)
/* 00E770 8000DB70 24050001 */  li    $a1, 1
/* 00E774 8000DB74 A6CE0002 */  sh    $t6, 2($s6)
/* 00E778 8000DB78 8FB900D4 */  lw    $t9, 0xd4($sp)
/* 00E77C 8000DB7C 00000000 */  nop   
/* 00E780 8000DB80 A6D90004 */  sh    $t9, 4($s6)
/* 00E784 8000DB84 8FAF00B4 */  lw    $t7, 0xb4($sp)
/* 00E788 8000DB88 00000000 */  nop   
/* 00E78C 8000DB8C A6CF0006 */  sh    $t7, 6($s6)
/* 00E790 8000DB90 8FAD0094 */  lw    $t5, 0x94($sp)
/* 00E794 8000DB94 0C003A95 */  jal   spawn_object
/* 00E798 8000DB98 A6CD000C */   sh    $t5, 0xc($s6)
/* 00E79C 8000DB9C 2418003A */  li    $t8, 58
/* 00E7A0 8000DBA0 AC40003C */  sw    $zero, 0x3c($v0)
/* 00E7A4 8000DBA4 A4580048 */  sh    $t8, 0x48($v0)
/* 00E7A8 8000DBA8 3C01800E */  lui   $at, %hi(D_800E5178) # $at, 0x800e
/* 00E7AC 8000DBAC C4245178 */  lwc1  $f4, %lo(D_800E5178)($at)
/* 00E7B0 8000DBB0 8C4E0050 */  lw    $t6, 0x50($v0)
/* 00E7B4 8000DBB4 3C038012 */  lui   $v1, %hi(D_8011AD34) # $v1, 0x8012
/* 00E7B8 8000DBB8 E5C40000 */  swc1  $f4, ($t6)
/* 00E7BC 8000DBBC 8C59004C */  lw    $t9, 0x4c($v0)
/* 00E7C0 8000DBC0 2463AD34 */  addiu $v1, %lo(D_8011AD34) # addiu $v1, $v1, -0x52cc
/* 00E7C4 8000DBC4 A7200014 */  sh    $zero, 0x14($t9)
/* 00E7C8 8000DBC8 AC620000 */  sw    $v0, ($v1)
/* 00E7CC 8000DBCC 8C530064 */  lw    $s3, 0x64($v0)
/* 00E7D0 8000DBD0 240D0060 */  li    $t5, 96
/* 00E7D4 8000DBD4 A26D01F7 */  sb    $t5, 0x1f7($s3)
.L8000DBD8:
/* 00E7D8 8000DBD8 0C01AF62 */  jal   get_current_map_id
/* 00E7DC 8000DBDC 00000000 */   nop   
/* 00E7E0 8000DBE0 0C006D3F */  jal   func_8001B4FC
/* 00E7E4 8000DBE4 00402025 */   move  $a0, $v0
/* 00E7E8 8000DBE8 10400029 */  beqz  $v0, .L8000DC90
/* 00E7EC 8000DBEC 3C188012 */   lui   $t8, %hi(gMapDefaultVehicle) # $t8, 0x8012
/* 00E7F0 8000DBF0 8718AE84 */  lh    $t8, %lo(gMapDefaultVehicle)($t8)
/* 00E7F4 8000DBF4 3C02800E */  lui   $v0, %hi(D_800DC7B8) # $v0, 0x800e
/* 00E7F8 8000DBF8 00187080 */  sll   $t6, $t8, 2
/* 00E7FC 8000DBFC 01D87021 */  addu  $t6, $t6, $t8
/* 00E800 8000DC00 000EC880 */  sll   $t9, $t6, 2
/* 00E804 8000DC04 00591021 */  addu  $v0, $v0, $t9
/* 00E808 8000DC08 8442C7B8 */  lh    $v0, %lo(D_800DC7B8)($v0)
/* 00E80C 8000DC0C 02C02025 */  move  $a0, $s6
/* 00E810 8000DC10 304F0100 */  andi  $t7, $v0, 0x100
/* 00E814 8000DC14 000F6843 */  sra   $t5, $t7, 1
/* 00E818 8000DC18 35B80010 */  ori   $t8, $t5, 0x10
/* 00E81C 8000DC1C A2D80001 */  sb    $t8, 1($s6)
/* 00E820 8000DC20 A2C20000 */  sb    $v0, ($s6)
/* 00E824 8000DC24 8FAE00F4 */  lw    $t6, 0xf4($sp)
/* 00E828 8000DC28 24050001 */  li    $a1, 1
/* 00E82C 8000DC2C A6CE0002 */  sh    $t6, 2($s6)
/* 00E830 8000DC30 8FB900D4 */  lw    $t9, 0xd4($sp)
/* 00E834 8000DC34 00000000 */  nop   
/* 00E838 8000DC38 A6D90004 */  sh    $t9, 4($s6)
/* 00E83C 8000DC3C 8FAF00B4 */  lw    $t7, 0xb4($sp)
/* 00E840 8000DC40 00000000 */  nop   
/* 00E844 8000DC44 A6CF0006 */  sh    $t7, 6($s6)
/* 00E848 8000DC48 8FAD0094 */  lw    $t5, 0x94($sp)
/* 00E84C 8000DC4C 0C003A95 */  jal   spawn_object
/* 00E850 8000DC50 A6CD000C */   sh    $t5, 0xc($s6)
/* 00E854 8000DC54 2418003A */  li    $t8, 58
/* 00E858 8000DC58 AC40003C */  sw    $zero, 0x3c($v0)
/* 00E85C 8000DC5C A4580048 */  sh    $t8, 0x48($v0)
/* 00E860 8000DC60 3C01800E */  lui   $at, %hi(D_800E517C) # $at, 0x800e
/* 00E864 8000DC64 C426517C */  lwc1  $f6, %lo(D_800E517C)($at)
/* 00E868 8000DC68 8C4E0050 */  lw    $t6, 0x50($v0)
/* 00E86C 8000DC6C 240D0060 */  li    $t5, 96
/* 00E870 8000DC70 E5C60000 */  swc1  $f6, ($t6)
/* 00E874 8000DC74 8C59004C */  lw    $t9, 0x4c($v0)
/* 00E878 8000DC78 00000000 */  nop   
/* 00E87C 8000DC7C A7200014 */  sh    $zero, 0x14($t9)
/* 00E880 8000DC80 AEA20000 */  sw    $v0, ($s5)
/* 00E884 8000DC84 8C530064 */  lw    $s3, 0x64($v0)
/* 00E888 8000DC88 00000000 */  nop   
/* 00E88C 8000DC8C A26D01F7 */  sb    $t5, 0x1f7($s3)
.L8000DC90:
/* 00E890 8000DC90 3C0E8012 */  lui   $t6, %hi(gNumRacers) # $t6, 0x8012
/* 00E894 8000DC94 8DCEAEF0 */  lw    $t6, %lo(gNumRacers)($t6)
/* 00E898 8000DC98 24180064 */  li    $t8, 100
/* 00E89C 8000DC9C 3C018012 */  lui   $at, %hi(D_8011ADB0) # $at, 0x8012
/* 00E8A0 8000DCA0 19C00068 */  blez  $t6, .L8000DE44
/* 00E8A4 8000DCA4 AC38ADB0 */   sw    $t8, %lo(D_8011ADB0)($at)
/* 00E8A8 8000DCA8 0000A825 */  move  $s5, $zero
.L8000DCAC:
/* 00E8AC 8000DCAC 3C198012 */  lui   $t9, %hi(gRacers) # $t9, 0x8012
/* 00E8B0 8000DCB0 8F39AEE4 */  lw    $t9, %lo(gRacers)($t9)
/* 00E8B4 8000DCB4 00008025 */  move  $s0, $zero
/* 00E8B8 8000DCB8 03357821 */  addu  $t7, $t9, $s5
/* 00E8BC 8000DCBC 8DF10000 */  lw    $s1, ($t7)
/* 00E8C0 8000DCC0 00000000 */  nop   
/* 00E8C4 8000DCC4 8E330064 */  lw    $s3, 0x64($s1)
/* 00E8C8 8000DCC8 00000000 */  nop   
/* 00E8CC 8000DCCC 02202025 */  move  $a0, $s1
.L8000DCD0:
/* 00E8D0 8000DCD0 0C01378E */  jal   update_player_racer
/* 00E8D4 8000DCD4 24050002 */   li    $a1, 2
/* 00E8D8 8000DCD8 26100001 */  addiu $s0, $s0, 1
/* 00E8DC 8000DCDC 2A01000A */  slti  $at, $s0, 0xa
/* 00E8E0 8000DCE0 1420FFFB */  bnez  $at, .L8000DCD0
/* 00E8E4 8000DCE4 02202025 */   move  $a0, $s1
/* 00E8E8 8000DCE8 866D0000 */  lh    $t5, ($s3)
/* 00E8EC 8000DCEC 2401FFFF */  li    $at, -1
/* 00E8F0 8000DCF0 15A1001D */  bne   $t5, $at, .L8000DD68
/* 00E8F4 8000DCF4 00008025 */   move  $s0, $zero
/* 00E8F8 8000DCF8 8E2E0040 */  lw    $t6, 0x40($s1)
/* 00E8FC 8000DCFC 26940001 */  addiu $s4, $s4, 1
/* 00E900 8000DD00 81C40055 */  lb    $a0, 0x55($t6)
/* 00E904 8000DD04 32980001 */  andi  $t8, $s4, 1
/* 00E908 8000DD08 18800030 */  blez  $a0, .L8000DDCC
/* 00E90C 8000DD0C 0300A025 */   move  $s4, $t8
/* 00E910 8000DD10 00001825 */  move  $v1, $zero
.L8000DD14:
/* 00E914 8000DD14 8E390068 */  lw    $t9, 0x68($s1)
/* 00E918 8000DD18 26100001 */  addiu $s0, $s0, 1
/* 00E91C 8000DD1C 03237821 */  addu  $t7, $t9, $v1
/* 00E920 8000DD20 8DE20000 */  lw    $v0, ($t7)
/* 00E924 8000DD24 00000000 */  nop   
/* 00E928 8000DD28 1040000B */  beqz  $v0, .L8000DD58
/* 00E92C 8000DD2C 0204082A */   slt   $at, $s0, $a0
/* 00E930 8000DD30 804D0020 */  lb    $t5, 0x20($v0)
/* 00E934 8000DD34 0014C040 */  sll   $t8, $s4, 1
/* 00E938 8000DD38 11A00007 */  beqz  $t5, .L8000DD58
/* 00E93C 8000DD3C 0204082A */   slt   $at, $s0, $a0
/* 00E940 8000DD40 A0580020 */  sb    $t8, 0x20($v0)
/* 00E944 8000DD44 8E2E0040 */  lw    $t6, 0x40($s1)
/* 00E948 8000DD48 00000000 */  nop   
/* 00E94C 8000DD4C 81C40055 */  lb    $a0, 0x55($t6)
/* 00E950 8000DD50 00000000 */  nop   
/* 00E954 8000DD54 0204082A */  slt   $at, $s0, $a0
.L8000DD58:
/* 00E958 8000DD58 1420FFEE */  bnez  $at, .L8000DD14
/* 00E95C 8000DD5C 24630004 */   addiu $v1, $v1, 4
/* 00E960 8000DD60 1000001A */  b     .L8000DDCC
/* 00E964 8000DD64 00000000 */   nop   
.L8000DD68:
/* 00E968 8000DD68 8E390040 */  lw    $t9, 0x40($s1)
/* 00E96C 8000DD6C 00008025 */  move  $s0, $zero
/* 00E970 8000DD70 83240055 */  lb    $a0, 0x55($t9)
/* 00E974 8000DD74 00001825 */  move  $v1, $zero
/* 00E978 8000DD78 18800014 */  blez  $a0, .L8000DDCC
/* 00E97C 8000DD7C 00000000 */   nop   
.L8000DD80:
/* 00E980 8000DD80 8E2F0068 */  lw    $t7, 0x68($s1)
/* 00E984 8000DD84 26100001 */  addiu $s0, $s0, 1
/* 00E988 8000DD88 01E36821 */  addu  $t5, $t7, $v1
/* 00E98C 8000DD8C 8DA20000 */  lw    $v0, ($t5)
/* 00E990 8000DD90 00000000 */  nop   
/* 00E994 8000DD94 1040000B */  beqz  $v0, .L8000DDC4
/* 00E998 8000DD98 0204082A */   slt   $at, $s0, $a0
/* 00E99C 8000DD9C 80580020 */  lb    $t8, 0x20($v0)
/* 00E9A0 8000DDA0 00000000 */  nop   
/* 00E9A4 8000DDA4 13000007 */  beqz  $t8, .L8000DDC4
/* 00E9A8 8000DDA8 0204082A */   slt   $at, $s0, $a0
/* 00E9AC 8000DDAC A0400020 */  sb    $zero, 0x20($v0)
/* 00E9B0 8000DDB0 8E2E0040 */  lw    $t6, 0x40($s1)
/* 00E9B4 8000DDB4 00000000 */  nop   
/* 00E9B8 8000DDB8 81C40055 */  lb    $a0, 0x55($t6)
/* 00E9BC 8000DDBC 00000000 */  nop   
/* 00E9C0 8000DDC0 0204082A */  slt   $at, $s0, $a0
.L8000DDC4:
/* 00E9C4 8000DDC4 1420FFEE */  bnez  $at, .L8000DD80
/* 00E9C8 8000DDC8 24630004 */   addiu $v1, $v1, 4
.L8000DDCC:
/* 00E9CC 8000DDCC 0C0270C3 */  jal   get_filtered_cheats
/* 00E9D0 8000DDD0 00000000 */   nop   
/* 00E9D4 8000DDD4 30590010 */  andi  $t9, $v0, 0x10
/* 00E9D8 8000DDD8 13200006 */  beqz  $t9, .L8000DDF4
/* 00E9DC 8000DDDC 3C01800E */   lui   $at, %hi(D_800E5180) # $at, 0x800e
/* 00E9E0 8000DDE0 C6280008 */  lwc1  $f8, 8($s1)
/* 00E9E4 8000DDE4 C42A5180 */  lwc1  $f10, %lo(D_800E5180)($at)
/* 00E9E8 8000DDE8 00000000 */  nop   
/* 00E9EC 8000DDEC 460A4402 */  mul.s $f16, $f8, $f10
/* 00E9F0 8000DDF0 E6300008 */  swc1  $f16, 8($s1)
.L8000DDF4:
/* 00E9F4 8000DDF4 0C0270C3 */  jal   get_filtered_cheats
/* 00E9F8 8000DDF8 00000000 */   nop   
/* 00E9FC 8000DDFC 304F0020 */  andi  $t7, $v0, 0x20
/* 00EA00 8000DE00 11E00006 */  beqz  $t7, .L8000DE1C
/* 00EA04 8000DE04 3C01800E */   lui   $at, %hi(D_800E5184) # $at, 0x800e
/* 00EA08 8000DE08 C6320008 */  lwc1  $f18, 8($s1)
/* 00EA0C 8000DE0C C4245184 */  lwc1  $f4, %lo(D_800E5184)($at)
/* 00EA10 8000DE10 00000000 */  nop   
/* 00EA14 8000DE14 46049182 */  mul.s $f6, $f18, $f4
/* 00EA18 8000DE18 E6260008 */  swc1  $f6, 8($s1)
.L8000DE1C:
/* 00EA1C 8000DE1C 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 00EA20 8000DE20 44810000 */  mtc1  $at, $f0
/* 00EA24 8000DE24 3C0D8012 */  lui   $t5, %hi(gNumRacers) # $t5, 0x8012
/* 00EA28 8000DE28 E6600090 */  swc1  $f0, 0x90($s3)
/* 00EA2C 8000DE2C E660008C */  swc1  $f0, 0x8c($s3)
/* 00EA30 8000DE30 8DADAEF0 */  lw    $t5, %lo(gNumRacers)($t5)
/* 00EA34 8000DE34 26520001 */  addiu $s2, $s2, 1
/* 00EA38 8000DE38 024D082A */  slt   $at, $s2, $t5
/* 00EA3C 8000DE3C 1420FF9B */  bnez  $at, .L8000DCAC
/* 00EA40 8000DE40 26B50004 */   addiu $s5, $s5, 4
.L8000DE44:
/* 00EA44 8000DE44 8FB80068 */  lw    $t8, 0x68($sp)
/* 00EA48 8000DE48 8FAE0064 */  lw    $t6, 0x64($sp)
/* 00EA4C 8000DE4C 1300000B */  beqz  $t8, .L8000DE7C
/* 00EA50 8000DE50 240D0050 */   li    $t5, 80
/* 00EA54 8000DE54 15C00009 */  bnez  $t6, .L8000DE7C
/* 00EA58 8000DE58 3C198012 */   lui   $t9, %hi(gIsTimeTrial) # $t9, 0x8012
/* 00EA5C 8000DE5C 9339AEF5 */  lbu   $t9, %lo(gIsTimeTrial)($t9)
/* 00EA60 8000DE60 3C0F8012 */  lui   $t7, %hi(D_8011AD3C) # $t7, 0x8012
/* 00EA64 8000DE64 17200005 */  bnez  $t9, .L8000DE7C
/* 00EA68 8000DE68 00000000 */   nop   
/* 00EA6C 8000DE6C 81EFAD3C */  lb    $t7, %lo(D_8011AD3C)($t7)
/* 00EA70 8000DE70 3C018012 */  lui   $at, %hi(D_8011ADB0) # $at, 0x8012
/* 00EA74 8000DE74 11E00004 */  beqz  $t7, .L8000DE88
/* 00EA78 8000DE78 00000000 */   nop   
.L8000DE7C:
/* 00EA7C 8000DE7C 3C018012 */  lui   $at, %hi(D_8011ADB0) # $at, 0x8012
/* 00EA80 8000DE80 10000002 */  b     .L8000DE8C
/* 00EA84 8000DE84 AC2DADB0 */   sw    $t5, %lo(D_8011ADB0)($at)
.L8000DE88:
/* 00EA88 8000DE88 AC20ADB0 */  sw    $zero, %lo(D_8011ADB0)($at)
.L8000DE8C:
/* 00EA8C 8000DE8C 8FB80068 */  lw    $t8, 0x68($sp)
/* 00EA90 8000DE90 8FAE0058 */  lw    $t6, 0x58($sp)
/* 00EA94 8000DE94 1700001A */  bnez  $t8, .L8000DF00
/* 00EA98 8000DE98 24010001 */   li    $at, 1
/* 00EA9C 8000DE9C 15C10018 */  bne   $t6, $at, .L8000DF00
/* 00EAA0 8000DEA0 00000000 */   nop   
/* 00EAA4 8000DEA4 0C027B1C */  jal   is_in_adventure_two
/* 00EAA8 8000DEA8 00000000 */   nop   
/* 00EAAC 8000DEAC 14400014 */  bnez  $v0, .L8000DF00
/* 00EAB0 8000DEB0 00000000 */   nop   
/* 00EAB4 8000DEB4 0C01B067 */  jal   func_8006C19C
/* 00EAB8 8000DEB8 00000000 */   nop   
/* 00EABC 8000DEBC 14400010 */  bnez  $v0, .L8000DF00
/* 00EAC0 8000DEC0 00009025 */   move  $s2, $zero
/* 00EAC4 8000DEC4 24130003 */  li    $s3, 3
/* 00EAC8 8000DEC8 24110008 */  li    $s1, 8
/* 00EACC 8000DECC 24100032 */  li    $s0, 50
.L8000DED0:
/* 00EAD0 8000DED0 A2D00000 */  sb    $s0, ($s6)
/* 00EAD4 8000DED4 A2D10001 */  sb    $s1, 1($s6)
/* 00EAD8 8000DED8 A6C00002 */  sh    $zero, 2($s6)
/* 00EADC 8000DEDC A6C00004 */  sh    $zero, 4($s6)
/* 00EAE0 8000DEE0 A6C00006 */  sh    $zero, 6($s6)
/* 00EAE4 8000DEE4 02C02025 */  move  $a0, $s6
/* 00EAE8 8000DEE8 0C003A95 */  jal   spawn_object
/* 00EAEC 8000DEEC 24050001 */   li    $a1, 1
/* 00EAF0 8000DEF0 AC520078 */  sw    $s2, 0x78($v0)
/* 00EAF4 8000DEF4 26520001 */  addiu $s2, $s2, 1
/* 00EAF8 8000DEF8 1653FFF5 */  bne   $s2, $s3, .L8000DED0
/* 00EAFC 8000DEFC AC40003C */   sw    $zero, 0x3c($v0)
.L8000DF00:
/* 00EB00 8000DF00 3C018012 */  lui   $at, %hi(D_8011AD4E) # $at, 0x8012
/* 00EB04 8000DF04 A420AD4E */  sh    $zero, %lo(D_8011AD4E)($at)
/* 00EB08 8000DF08 3C018012 */  lui   $at, %hi(D_8011ADB4) # $at, 0x8012
/* 00EB0C 8000DF0C AC20ADB4 */  sw    $zero, %lo(D_8011ADB4)($at)
/* 00EB10 8000DF10 0C0274CC */  jal   set_next_taj_challenge_menu
/* 00EB14 8000DF14 00002025 */   move  $a0, $zero
/* 00EB18 8000DF18 92F90048 */  lbu   $t9, 0x48($s7)
/* 00EB1C 8000DF1C 00000000 */  nop   
/* 00EB20 8000DF20 1720003D */  bnez  $t9, .L8000E018
/* 00EB24 8000DF24 8FAE0130 */   lw    $t6, 0x130($sp)
/* 00EB28 8000DF28 0C0270B4 */  jal   is_in_tracks_mode
/* 00EB2C 8000DF2C 00000000 */   nop   
/* 00EB30 8000DF30 14400038 */  bnez  $v0, .L8000E014
/* 00EB34 8000DF34 24040010 */   li    $a0, 16
/* 00EB38 8000DF38 0C0078A7 */  jal   get_misc_asset
/* 00EB3C 8000DF3C 00009025 */   move  $s2, $zero
/* 00EB40 8000DF40 96E30014 */  lhu   $v1, 0x14($s7)
/* 00EB44 8000DF44 00000000 */  nop   
/* 00EB48 8000DF48 306F0001 */  andi  $t7, $v1, 1
/* 00EB4C 8000DF4C 15E0000A */  bnez  $t7, .L8000DF78
/* 00EB50 8000DF50 30790002 */   andi  $t9, $v1, 2
/* 00EB54 8000DF54 8EED0000 */  lw    $t5, ($s7)
/* 00EB58 8000DF58 804E0000 */  lb    $t6, ($v0)
/* 00EB5C 8000DF5C 85B80000 */  lh    $t8, ($t5)
/* 00EB60 8000DF60 00000000 */  nop   
/* 00EB64 8000DF64 030E082A */  slt   $at, $t8, $t6
/* 00EB68 8000DF68 14200003 */  bnez  $at, .L8000DF78
/* 00EB6C 8000DF6C 00000000 */   nop   
/* 00EB70 8000DF70 10000016 */  b     .L8000DFCC
/* 00EB74 8000DF74 24120001 */   li    $s2, 1
.L8000DF78:
/* 00EB78 8000DF78 1720000A */  bnez  $t9, .L8000DFA4
/* 00EB7C 8000DF7C 306E0004 */   andi  $t6, $v1, 4
/* 00EB80 8000DF80 8EEF0000 */  lw    $t7, ($s7)
/* 00EB84 8000DF84 80580001 */  lb    $t8, 1($v0)
/* 00EB88 8000DF88 85ED0000 */  lh    $t5, ($t7)
/* 00EB8C 8000DF8C 00000000 */  nop   
/* 00EB90 8000DF90 01B8082A */  slt   $at, $t5, $t8
/* 00EB94 8000DF94 14200003 */  bnez  $at, .L8000DFA4
/* 00EB98 8000DF98 00000000 */   nop   
/* 00EB9C 8000DF9C 1000000B */  b     .L8000DFCC
/* 00EBA0 8000DFA0 24120002 */   li    $s2, 2
.L8000DFA4:
/* 00EBA4 8000DFA4 15C00009 */  bnez  $t6, .L8000DFCC
/* 00EBA8 8000DFA8 00000000 */   nop   
/* 00EBAC 8000DFAC 8EF90000 */  lw    $t9, ($s7)
/* 00EBB0 8000DFB0 804D0002 */  lb    $t5, 2($v0)
/* 00EBB4 8000DFB4 872F0000 */  lh    $t7, ($t9)
/* 00EBB8 8000DFB8 00000000 */  nop   
/* 00EBBC 8000DFBC 01ED082A */  slt   $at, $t7, $t5
/* 00EBC0 8000DFC0 14200002 */  bnez  $at, .L8000DFCC
/* 00EBC4 8000DFC4 00000000 */   nop   
/* 00EBC8 8000DFC8 24120003 */  li    $s2, 3
.L8000DFCC:
/* 00EBCC 8000DFCC 12400012 */  beqz  $s2, .L8000E018
/* 00EBD0 8000DFD0 8FAE0130 */   lw    $t6, 0x130($sp)
/* 00EBD4 8000DFD4 0C00E4C8 */  jal   set_taj_voice_line
/* 00EBD8 8000DFD8 24040250 */   li    $a0, 592
/* 00EBDC 8000DFDC 96F80014 */  lhu   $t8, 0x14($s7)
/* 00EBE0 8000DFE0 264E001F */  addiu $t6, $s2, 0x1f
/* 00EBE4 8000DFE4 24190001 */  li    $t9, 1
/* 00EBE8 8000DFE8 01D97804 */  sllv  $t7, $t9, $t6
/* 00EBEC 8000DFEC 030F6825 */  or    $t5, $t8, $t7
/* 00EBF0 8000DFF0 A6ED0014 */  sh    $t5, 0x14($s7)
/* 00EBF4 8000DFF4 0C01486E */  jal   func_800521B8
/* 00EBF8 8000DFF8 24040002 */   li    $a0, 2
/* 00EBFC 8000DFFC 0C0274CC */  jal   set_next_taj_challenge_menu
/* 00EC00 8000E000 02402025 */   move  $a0, $s2
/* 00EC04 8000E004 0C027068 */  jal   get_save_file_index
/* 00EC08 8000E008 00000000 */   nop   
/* 00EC0C 8000E00C 0C01BB12 */  jal   safe_mark_write_save_file
/* 00EC10 8000E010 00402025 */   move  $a0, $v0
.L8000E014:
/* 00EC14 8000E014 8FAE0130 */  lw    $t6, 0x130($sp)
.L8000E018:
/* 00EC18 8000E018 24190001 */  li    $t9, 1
/* 00EC1C 8000E01C 3C018012 */  lui   $at, %hi(D_8011AD24) # $at, 0x8012
/* 00EC20 8000E020 05C00005 */  bltz  $t6, .L8000E038
/* 00EC24 8000E024 A039AD24 */   sb    $t9, %lo(D_8011AD24)($at)
/* 00EC28 8000E028 8FB80130 */  lw    $t8, 0x130($sp)
/* 00EC2C 8000E02C 8FAF0074 */  lw    $t7, 0x74($sp)
/* 00EC30 8000E030 00000000 */  nop   
/* 00EC34 8000E034 A1F8003B */  sb    $t8, 0x3b($t7)
.L8000E038:
/* 00EC38 8000E038 0C003852 */  jal   func_8000E148
/* 00EC3C 8000E03C 00000000 */   nop   
/* 00EC40 8000E040 10400009 */  beqz  $v0, .L8000E068
/* 00EC44 8000E044 00000000 */   nop   
/* 00EC48 8000E048 0C01C8A6 */  jal   func_80072298
/* 00EC4C 8000E04C 00002025 */   move  $a0, $zero
/* 00EC50 8000E050 3C018012 */  lui   $at, %hi(D_8011ADB0) # $at, 0x8012
/* 00EC54 8000E054 AC20ADB0 */  sw    $zero, %lo(D_8011ADB0)($at)
/* 00EC58 8000E058 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 00EC5C 8000E05C 44816000 */  mtc1  $at, $f12
/* 00EC60 8000E060 0C01AF44 */  jal   func_8006BD10
/* 00EC64 8000E064 00000000 */   nop   
.L8000E068:
/* 00EC68 8000E068 0C01C42C */  jal   set_free_queue_state
/* 00EC6C 8000E06C 00002025 */   move  $a0, $zero
/* 00EC70 8000E070 0C01C450 */  jal   free_from_memory_pool
/* 00EC74 8000E074 02C02025 */   move  $a0, $s6
/* 00EC78 8000E078 0C01C42C */  jal   set_free_queue_state
/* 00EC7C 8000E07C 24040002 */   li    $a0, 2
.L8000E080:
/* 00EC80 8000E080 8FBF003C */  lw    $ra, 0x3c($sp)
/* 00EC84 8000E084 8FB00018 */  lw    $s0, 0x18($sp)
/* 00EC88 8000E088 8FB1001C */  lw    $s1, 0x1c($sp)
/* 00EC8C 8000E08C 8FB20020 */  lw    $s2, 0x20($sp)
/* 00EC90 8000E090 8FB30024 */  lw    $s3, 0x24($sp)
/* 00EC94 8000E094 8FB40028 */  lw    $s4, 0x28($sp)
/* 00EC98 8000E098 8FB5002C */  lw    $s5, 0x2c($sp)
/* 00EC9C 8000E09C 8FB60030 */  lw    $s6, 0x30($sp)
/* 00ECA0 8000E0A0 8FB70034 */  lw    $s7, 0x34($sp)
/* 00ECA4 8000E0A4 8FBE0038 */  lw    $fp, 0x38($sp)
/* 00ECA8 8000E0A8 03E00008 */  jr    $ra
/* 00ECAC 8000E0AC 27BD0150 */   addiu $sp, $sp, 0x150

