glabel load_sprite_info
/* 07D4E0 8007C8E0 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 07D4E4 8007C8E4 AFB00018 */  sw    $s0, 0x18($sp)
/* 07D4E8 8007C8E8 00808025 */  move  $s0, $a0
/* 07D4EC 8007C8EC AFBF002C */  sw    $ra, 0x2c($sp)
/* 07D4F0 8007C8F0 AFB40028 */  sw    $s4, 0x28($sp)
/* 07D4F4 8007C8F4 AFB30024 */  sw    $s3, 0x24($sp)
/* 07D4F8 8007C8F8 AFB20020 */  sw    $s2, 0x20($sp)
/* 07D4FC 8007C8FC AFB1001C */  sw    $s1, 0x1c($sp)
/* 07D500 8007C900 AFA50034 */  sw    $a1, 0x34($sp)
/* 07D504 8007C904 AFA60038 */  sw    $a2, 0x38($sp)
/* 07D508 8007C908 04800007 */  bltz  $a0, .L8007C928
/* 07D50C 8007C90C AFA7003C */   sw    $a3, 0x3c($sp)
/* 07D510 8007C910 3C0E8012 */  lui   $t6, %hi(D_80126354) # $t6, 0x8012
/* 07D514 8007C914 8DCE6354 */  lw    $t6, %lo(D_80126354)($t6)
/* 07D518 8007C918 3C088012 */  lui   $t0, %hi(gSpriteOffsetTable) # $t0, 0x8012
/* 07D51C 8007C91C 008E082A */  slt   $at, $a0, $t6
/* 07D520 8007C920 1420000A */  bnez  $at, .L8007C94C
/* 07D524 8007C924 00104880 */   sll   $t1, $s0, 2
.L8007C928:
/* 07D528 8007C928 8FAF0034 */  lw    $t7, 0x34($sp)
/* 07D52C 8007C92C 00001025 */  move  $v0, $zero
/* 07D530 8007C930 ADE00000 */  sw    $zero, ($t7)
/* 07D534 8007C934 8FB80038 */  lw    $t8, 0x38($sp)
/* 07D538 8007C938 00000000 */  nop   
/* 07D53C 8007C93C AF000000 */  sw    $zero, ($t8)
/* 07D540 8007C940 8FB9003C */  lw    $t9, 0x3c($sp)
/* 07D544 8007C944 10000040 */  b     .L8007CA48
/* 07D548 8007C948 AF200000 */   sw    $zero, ($t9)
.L8007C94C:
/* 07D54C 8007C94C 8D086348 */  lw    $t0, %lo(gSpriteOffsetTable)($t0)
/* 07D550 8007C950 3C138012 */  lui   $s3, %hi(gCurrentSprite) # $s3, 0x8012
/* 07D554 8007C954 01091021 */  addu  $v0, $t0, $t1
/* 07D558 8007C958 8C460000 */  lw    $a2, ($v0)
/* 07D55C 8007C95C 8C4A0004 */  lw    $t2, 4($v0)
/* 07D560 8007C960 8E736350 */  lw    $s3, %lo(gCurrentSprite)($s3)
/* 07D564 8007C964 2404000C */  li    $a0, 12
/* 07D568 8007C968 01463823 */  subu  $a3, $t2, $a2
/* 07D56C 8007C96C 0C01DB9A */  jal   load_asset_to_address
/* 07D570 8007C970 02602825 */   move  $a1, $s3
/* 07D574 8007C974 926B000C */  lbu   $t3, 0xc($s3)
/* 07D578 8007C978 866C0000 */  lh    $t4, ($s3)
/* 07D57C 8007C97C 0C01EB9D */  jal   load_texture
/* 07D580 8007C980 016C2021 */   addu  $a0, $t3, $t4
/* 07D584 8007C984 1040FFE8 */  beqz  $v0, .L8007C928
/* 07D588 8007C988 00402025 */   move  $a0, $v0
/* 07D58C 8007C98C 904D0002 */  lbu   $t5, 2($v0)
/* 07D590 8007C990 8FAF0040 */  lw    $t7, 0x40($sp)
/* 07D594 8007C994 31AE000F */  andi  $t6, $t5, 0xf
/* 07D598 8007C998 0C01ECAF */  jal   free_texture
/* 07D59C 8007C99C ADEE0000 */   sw    $t6, ($t7)
/* 07D5A0 8007C9A0 8FB10044 */  lw    $s1, 0x44($sp)
/* 07D5A4 8007C9A4 0000A025 */  move  $s4, $zero
/* 07D5A8 8007C9A8 AE200000 */  sw    $zero, ($s1)
/* 07D5AC 8007C9AC 86630002 */  lh    $v1, 2($s3)
/* 07D5B0 8007C9B0 02609025 */  move  $s2, $s3
/* 07D5B4 8007C9B4 1860001A */  blez  $v1, .L8007CA20
/* 07D5B8 8007C9B8 8FAB003C */   lw    $t3, 0x3c($sp)
.L8007C9BC:
/* 07D5BC 8007C9BC 9250000C */  lbu   $s0, 0xc($s2)
/* 07D5C0 8007C9C0 9258000D */  lbu   $t8, 0xd($s2)
/* 07D5C4 8007C9C4 00000000 */  nop   
/* 07D5C8 8007C9C8 0218082A */  slt   $at, $s0, $t8
/* 07D5CC 8007C9CC 1020000F */  beqz  $at, .L8007CA0C
/* 07D5D0 8007C9D0 00000000 */   nop   
.L8007C9D4:
/* 07D5D4 8007C9D4 86790000 */  lh    $t9, ($s3)
/* 07D5D8 8007C9D8 0C01F15F */  jal   get_texture_size_from_id
/* 07D5DC 8007C9DC 03302021 */   addu  $a0, $t9, $s0
/* 07D5E0 8007C9E0 8E280000 */  lw    $t0, ($s1)
/* 07D5E4 8007C9E4 26100001 */  addiu $s0, $s0, 1
/* 07D5E8 8007C9E8 01024821 */  addu  $t1, $t0, $v0
/* 07D5EC 8007C9EC AE290000 */  sw    $t1, ($s1)
/* 07D5F0 8007C9F0 924A000D */  lbu   $t2, 0xd($s2)
/* 07D5F4 8007C9F4 00000000 */  nop   
/* 07D5F8 8007C9F8 020A082A */  slt   $at, $s0, $t2
/* 07D5FC 8007C9FC 1420FFF5 */  bnez  $at, .L8007C9D4
/* 07D600 8007CA00 00000000 */   nop   
/* 07D604 8007CA04 86630002 */  lh    $v1, 2($s3)
/* 07D608 8007CA08 00000000 */  nop   
.L8007CA0C:
/* 07D60C 8007CA0C 26940001 */  addiu $s4, $s4, 1
/* 07D610 8007CA10 0283082A */  slt   $at, $s4, $v1
/* 07D614 8007CA14 1420FFE9 */  bnez  $at, .L8007C9BC
/* 07D618 8007CA18 26520001 */   addiu $s2, $s2, 1
/* 07D61C 8007CA1C 8FAB003C */  lw    $t3, 0x3c($sp)
.L8007CA20:
/* 07D620 8007CA20 24020001 */  li    $v0, 1
/* 07D624 8007CA24 AD630000 */  sw    $v1, ($t3)
/* 07D628 8007CA28 8FAD0034 */  lw    $t5, 0x34($sp)
/* 07D62C 8007CA2C 866C0004 */  lh    $t4, 4($s3)
/* 07D630 8007CA30 00000000 */  nop   
/* 07D634 8007CA34 ADAC0000 */  sw    $t4, ($t5)
/* 07D638 8007CA38 8FAF0038 */  lw    $t7, 0x38($sp)
/* 07D63C 8007CA3C 866E0006 */  lh    $t6, 6($s3)
/* 07D640 8007CA40 00000000 */  nop   
/* 07D644 8007CA44 ADEE0000 */  sw    $t6, ($t7)
.L8007CA48:
/* 07D648 8007CA48 8FBF002C */  lw    $ra, 0x2c($sp)
/* 07D64C 8007CA4C 8FB00018 */  lw    $s0, 0x18($sp)
/* 07D650 8007CA50 8FB1001C */  lw    $s1, 0x1c($sp)
/* 07D654 8007CA54 8FB20020 */  lw    $s2, 0x20($sp)
/* 07D658 8007CA58 8FB30024 */  lw    $s3, 0x24($sp)
/* 07D65C 8007CA5C 8FB40028 */  lw    $s4, 0x28($sp)
/* 07D660 8007CA60 03E00008 */  jr    $ra
/* 07D664 8007CA64 27BD0030 */   addiu $sp, $sp, 0x30

