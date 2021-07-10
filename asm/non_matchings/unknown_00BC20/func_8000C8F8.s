glabel func_8000C8F8
/* 00D4F8 8000C8F8 27BDFFA8 */  addiu $sp, $sp, -0x58
/* 00D4FC 8000C8FC AFBF0024 */  sw    $ra, 0x24($sp)
/* 00D500 8000C900 AFB20020 */  sw    $s2, 0x20($sp)
/* 00D504 8000C904 AFB1001C */  sw    $s1, 0x1c($sp)
/* 00D508 8000C908 AFB00018 */  sw    $s0, 0x18($sp)
/* 00D50C 8000C90C AFA40058 */  sw    $a0, 0x58($sp)
/* 00D510 8000C910 0C01BAA4 */  jal   get_settings
/* 00D514 8000C914 AFA5005C */   sw    $a1, 0x5c($sp)
/* 00D518 8000C918 90580049 */  lbu   $t8, 0x49($v0)
/* 00D51C 8000C91C 8C4F0004 */  lw    $t7, 4($v0)
/* 00D520 8000C920 0018C880 */  sll   $t9, $t8, 2
/* 00D524 8000C924 01F94021 */  addu  $t0, $t7, $t9
/* 00D528 8000C928 8D030000 */  lw    $v1, ($t0)
/* 00D52C 8000C92C 9450000C */  lhu   $s0, 0xc($v0)
/* 00D530 8000C930 30690004 */  andi  $t1, $v1, 4
/* 00D534 8000C934 2D230001 */  sltiu $v1, $t1, 1
/* 00D538 8000C938 10600007 */  beqz  $v1, .L8000C958
/* 00D53C 8000C93C 360E0820 */   ori   $t6, $s0, 0x820
/* 00D540 8000C940 904B0048 */  lbu   $t3, 0x48($v0)
/* 00D544 8000C944 240C0001 */  li    $t4, 1
/* 00D548 8000C948 016C6804 */  sllv  $t5, $t4, $t3
/* 00D54C 8000C94C 01AE1824 */  and   $v1, $t5, $t6
/* 00D550 8000C950 0003702B */  sltu  $t6, $zero, $v1
/* 00D554 8000C954 01C01825 */  move  $v1, $t6
.L8000C958:
/* 00D558 8000C958 3C108012 */  lui   $s0, %hi(D_8011AE03) # $s0, 0x8012
/* 00D55C 8000C95C 2610AE03 */  addiu $s0, %lo(D_8011AE03) # addiu $s0, $s0, -0x51fd
/* 00D560 8000C960 A2030000 */  sb    $v1, ($s0)
/* 00D564 8000C964 904F0049 */  lbu   $t7, 0x49($v0)
/* 00D568 8000C968 8C580004 */  lw    $t8, 4($v0)
/* 00D56C 8000C96C 000FC880 */  sll   $t9, $t7, 2
/* 00D570 8000C970 03194021 */  addu  $t0, $t8, $t9
/* 00D574 8000C974 8D090000 */  lw    $t1, ($t0)
/* 00D578 8000C978 00000000 */  nop   
/* 00D57C 8000C97C 312A0002 */  andi  $t2, $t1, 2
/* 00D580 8000C980 15400002 */  bnez  $t2, .L8000C98C
/* 00D584 8000C984 00000000 */   nop   
/* 00D588 8000C988 A2000000 */  sb    $zero, ($s0)
.L8000C98C:
/* 00D58C 8000C98C 0C0270B4 */  jal   is_in_tracks_mode
/* 00D590 8000C990 00000000 */   nop   
/* 00D594 8000C994 10400002 */  beqz  $v0, .L8000C9A0
/* 00D598 8000C998 00000000 */   nop   
/* 00D59C 8000C99C A2000000 */  sb    $zero, ($s0)
.L8000C9A0:
/* 00D5A0 8000C9A0 0C01AF66 */  jal   get_current_level_race_type
/* 00D5A4 8000C9A4 00000000 */   nop   
/* 00D5A8 8000C9A8 10400002 */  beqz  $v0, .L8000C9B4
/* 00D5AC 8000C9AC 3C018012 */   lui   $at, %hi(D_8011AD3E) # $at, 0x8012
/* 00D5B0 8000C9B0 A2000000 */  sb    $zero, ($s0)
.L8000C9B4:
/* 00D5B4 8000C9B4 A020AD3E */  sb    $zero, %lo(D_8011AD3E)($at)
/* 00D5B8 8000C9B8 24043000 */  li    $a0, 12288
/* 00D5BC 8000C9BC 0C01C327 */  jal   allocate_from_main_pool_safe
/* 00D5C0 8000C9C0 3405FFFF */   li    $a1, 65535
/* 00D5C4 8000C9C4 8FA3005C */  lw    $v1, 0x5c($sp)
/* 00D5C8 8000C9C8 3C0B8012 */  lui   $t3, %hi(D_8011AEB0) # $t3, 0x8012
/* 00D5CC 8000C9CC 00036080 */  sll   $t4, $v1, 2
/* 00D5D0 8000C9D0 3C0D8012 */  lui   $t5, %hi(D_8011AE98) # $t5, 0x8012
/* 00D5D4 8000C9D4 3C0F8012 */  lui   $t7, %hi(D_8011AEA0) # $t7, 0x8012
/* 00D5D8 8000C9D8 256BAEB0 */  addiu $t3, %lo(D_8011AEB0) # addiu $t3, $t3, -0x5150
/* 00D5DC 8000C9DC 25ADAE98 */  addiu $t5, %lo(D_8011AE98) # addiu $t5, $t5, -0x5168
/* 00D5E0 8000C9E0 25EFAEA0 */  addiu $t7, %lo(D_8011AEA0) # addiu $t7, $t7, -0x5160
/* 00D5E4 8000C9E4 8FB80058 */  lw    $t8, 0x58($sp)
/* 00D5E8 8000C9E8 018B2821 */  addu  $a1, $t4, $t3
/* 00D5EC 8000C9EC 018D8821 */  addu  $s1, $t4, $t5
/* 00D5F0 8000C9F0 244E0010 */  addiu $t6, $v0, 0x10
/* 00D5F4 8000C9F4 018F9021 */  addu  $s2, $t4, $t7
/* 00D5F8 8000C9F8 3C018012 */  lui   $at, %hi(D_8011AEA8) # $at, 0x8012
/* 00D5FC 8000C9FC ACA20000 */  sw    $v0, ($a1)
/* 00D600 8000CA00 AE2E0000 */  sw    $t6, ($s1)
/* 00D604 8000CA04 AE400000 */  sw    $zero, ($s2)
/* 00D608 8000CA08 002C0821 */  addu  $at, $at, $t4
/* 00D60C 8000CA0C AFA20048 */  sw    $v0, 0x48($sp)
/* 00D610 8000CA10 AFA50028 */  sw    $a1, 0x28($sp)
/* 00D614 8000CA14 24040014 */  li    $a0, 20
/* 00D618 8000CA18 0C01DB16 */  jal   load_asset_section_from_rom
/* 00D61C 8000CA1C AC38AEA8 */   sw    $t8, %lo(D_8011AEA8)($at)
/* 00D620 8000CA20 8C590000 */  lw    $t9, ($v0)
/* 00D624 8000CA24 2405FFFF */  li    $a1, -1
/* 00D628 8000CA28 00403025 */  move  $a2, $v0
/* 00D62C 8000CA2C 10B90006 */  beq   $a1, $t9, .L8000CA48
/* 00D630 8000CA30 00002025 */   move  $a0, $zero
/* 00D634 8000CA34 00C01825 */  move  $v1, $a2
.L8000CA38:
/* 00D638 8000CA38 8C680004 */  lw    $t0, 4($v1)
/* 00D63C 8000CA3C 24840001 */  addiu $a0, $a0, 1
/* 00D640 8000CA40 14A8FFFD */  bne   $a1, $t0, .L8000CA38
/* 00D644 8000CA44 24630004 */   addiu $v1, $v1, 4
.L8000CA48:
/* 00D648 8000CA48 8FA90058 */  lw    $t1, 0x58($sp)
/* 00D64C 8000CA4C 2484FFFF */  addiu $a0, $a0, -1
/* 00D650 8000CA50 0124082A */  slt   $at, $t1, $a0
/* 00D654 8000CA54 14200002 */  bnez  $at, .L8000CA60
/* 00D658 8000CA58 24040015 */   li    $a0, 21
/* 00D65C 8000CA5C AFA00058 */  sw    $zero, 0x58($sp)
.L8000CA60:
/* 00D660 8000CA60 8FAA0058 */  lw    $t2, 0x58($sp)
/* 00D664 8000CA64 00000000 */  nop   
/* 00D668 8000CA68 000A6080 */  sll   $t4, $t2, 2
/* 00D66C 8000CA6C 004C1821 */  addu  $v1, $v0, $t4
/* 00D670 8000CA70 8C700000 */  lw    $s0, ($v1)
/* 00D674 8000CA74 8C6B0004 */  lw    $t3, 4($v1)
/* 00D678 8000CA78 02002825 */  move  $a1, $s0
/* 00D67C 8000CA7C 01703823 */  subu  $a3, $t3, $s0
/* 00D680 8000CA80 10E0004A */  beqz  $a3, .L8000CBAC
/* 00D684 8000CA84 8FBF0024 */   lw    $ra, 0x24($sp)
/* 00D688 8000CA88 AFA6003C */  sw    $a2, 0x3c($sp)
/* 00D68C 8000CA8C 0C031877 */  jal   get_asset_uncompressed_size
/* 00D690 8000CA90 AFA70054 */   sw    $a3, 0x54($sp)
/* 00D694 8000CA94 8FAD0048 */  lw    $t5, 0x48($sp)
/* 00D698 8000CA98 8FA70054 */  lw    $a3, 0x54($sp)
/* 00D69C 8000CA9C 01A27021 */  addu  $t6, $t5, $v0
/* 00D6A0 8000CAA0 01C72823 */  subu  $a1, $t6, $a3
/* 00D6A4 8000CAA4 24A50020 */  addiu $a1, $a1, 0x20
/* 00D6A8 8000CAA8 AFA50034 */  sw    $a1, 0x34($sp)
/* 00D6AC 8000CAAC 24040015 */  li    $a0, 21
/* 00D6B0 8000CAB0 0C01DB9A */  jal   load_asset_to_address
/* 00D6B4 8000CAB4 02003025 */   move  $a2, $s0
/* 00D6B8 8000CAB8 8FA40034 */  lw    $a0, 0x34($sp)
/* 00D6BC 8000CABC 8FA50048 */  lw    $a1, 0x48($sp)
/* 00D6C0 8000CAC0 0C031886 */  jal   gzip_inflate
/* 00D6C4 8000CAC4 00000000 */   nop   
/* 00D6C8 8000CAC8 8FA4003C */  lw    $a0, 0x3c($sp)
/* 00D6CC 8000CACC 0C01C450 */  jal   free_from_memory_pool
/* 00D6D0 8000CAD0 00000000 */   nop   
/* 00D6D4 8000CAD4 8FAF0028 */  lw    $t7, 0x28($sp)
/* 00D6D8 8000CAD8 8FA80048 */  lw    $t0, 0x48($sp)
/* 00D6DC 8000CADC 8DF80000 */  lw    $t8, ($t7)
/* 00D6E0 8000CAE0 8FAA005C */  lw    $t2, 0x5c($sp)
/* 00D6E4 8000CAE4 27190010 */  addiu $t9, $t8, 0x10
/* 00D6E8 8000CAE8 AE390000 */  sw    $t9, ($s1)
/* 00D6EC 8000CAEC 8D090000 */  lw    $t1, ($t0)
/* 00D6F0 8000CAF0 3C018012 */  lui   $at, %hi(D_8011AEC0) # $at, 0x8012
/* 00D6F4 8000CAF4 AE490000 */  sw    $t1, ($s2)
/* 00D6F8 8000CAF8 AC2AAEC0 */  sw    $t2, %lo(D_8011AEC0)($at)
/* 00D6FC 8000CAFC 8E4C0000 */  lw    $t4, ($s2)
/* 00D700 8000CB00 00008025 */  move  $s0, $zero
/* 00D704 8000CB04 19800014 */  blez  $t4, .L8000CB58
/* 00D708 8000CB08 00000000 */   nop   
.L8000CB0C:
/* 00D70C 8000CB0C 8E240000 */  lw    $a0, ($s1)
/* 00D710 8000CB10 0C003A95 */  jal   func_8000EA54
/* 00D714 8000CB14 24050001 */   li    $a1, 1
/* 00D718 8000CB18 8E230000 */  lw    $v1, ($s1)
/* 00D71C 8000CB1C 8E4E0000 */  lw    $t6, ($s2)
/* 00D720 8000CB20 90640001 */  lbu   $a0, 1($v1)
/* 00D724 8000CB24 00000000 */  nop   
/* 00D728 8000CB28 308B003F */  andi  $t3, $a0, 0x3f
/* 00D72C 8000CB2C 020B8021 */  addu  $s0, $s0, $t3
/* 00D730 8000CB30 01636821 */  addu  $t5, $t3, $v1
/* 00D734 8000CB34 020E082A */  slt   $at, $s0, $t6
/* 00D738 8000CB38 1420FFF4 */  bnez  $at, .L8000CB0C
/* 00D73C 8000CB3C AE2D0000 */   sw    $t5, ($s1)
/* 00D740 8000CB40 8FAF0028 */  lw    $t7, 0x28($sp)
/* 00D744 8000CB44 00000000 */  nop   
/* 00D748 8000CB48 8DF80000 */  lw    $t8, ($t7)
/* 00D74C 8000CB4C 00000000 */  nop   
/* 00D750 8000CB50 27190010 */  addiu $t9, $t8, 0x10
/* 00D754 8000CB54 AE390000 */  sw    $t9, ($s1)
.L8000CB58:
/* 00D758 8000CB58 3C018012 */  lui   $at, %hi(D_8011AE70) # $at, 0x8012
/* 00D75C 8000CB5C AC20AE70 */  sw    $zero, %lo(D_8011AE70)($at)
/* 00D760 8000CB60 24100001 */  li    $s0, 1
/* 00D764 8000CB64 3C118012 */  lui   $s1, %hi(D_8011ADAC) # $s1, 0x8012
/* 00D768 8000CB68 3C018012 */  lui   $at, %hi(D_8011ADC0) # $at, 0x8012
/* 00D76C 8000CB6C 2631ADAC */  addiu $s1, %lo(D_8011ADAC) # addiu $s1, $s1, -0x5254
/* 00D770 8000CB70 AC30ADC0 */  sw    $s0, %lo(D_8011ADC0)($at)
/* 00D774 8000CB74 8E280000 */  lw    $t0, ($s1)
/* 00D778 8000CB78 00000000 */  nop   
/* 00D77C 8000CB7C 15000009 */  bnez  $t0, .L8000CBA4
/* 00D780 8000CB80 00000000 */   nop   
/* 00D784 8000CB84 0C004013 */  jal   gParticlePtrList_flush
/* 00D788 8000CB88 00000000 */   nop   
/* 00D78C 8000CB8C 0C005FA6 */  jal   func_80017E98
/* 00D790 8000CB90 00000000 */   nop   
/* 00D794 8000CB94 0C006F15 */  jal   func_8001BC54
/* 00D798 8000CB98 00000000 */   nop   
/* 00D79C 8000CB9C 0C007A4F */  jal   func_8001E93C
/* 00D7A0 8000CBA0 00000000 */   nop   
.L8000CBA4:
/* 00D7A4 8000CBA4 AE300000 */  sw    $s0, ($s1)
/* 00D7A8 8000CBA8 8FBF0024 */  lw    $ra, 0x24($sp)
.L8000CBAC:
/* 00D7AC 8000CBAC 8FB00018 */  lw    $s0, 0x18($sp)
/* 00D7B0 8000CBB0 8FB1001C */  lw    $s1, 0x1c($sp)
/* 00D7B4 8000CBB4 8FB20020 */  lw    $s2, 0x20($sp)
/* 00D7B8 8000CBB8 03E00008 */  jr    $ra
/* 00D7BC 8000CBBC 27BD0058 */   addiu $sp, $sp, 0x58

