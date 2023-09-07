glabel gzip_inflate_block /* Official name: inflate_block */
/* 0C74C0 800C68C0 3C0B8013 */  lui   $t3, %hi(gzip_num_bits) # $t3, 0x8013
/* 0C74C4 800C68C4 8D6BAAD4 */  lw    $t3, %lo(gzip_num_bits)($t3)
/* 0C74C8 800C68C8 3C018013 */  lui   $at, %hi(gHuftTablePos) # $at, 0x8013
/* 0C74CC 800C68CC AC20AAD8 */  sw    $zero, %lo(gHuftTablePos)($at)
/* 0C74D0 800C68D0 24080001 */  li    $t0, 1
/* 0C74D4 800C68D4 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0C74D8 800C68D8 3C0C800E */  lui   $t4, %hi(gzip_inflate_input) # $t4, 0x800e
/* 0C74DC 800C68DC 3C0A8013 */  lui   $t2, %hi(gzip_bit_buffer) # $t2, 0x8013
/* 0C74E0 800C68E0 0168082B */  sltu  $at, $t3, $t0
/* 0C74E4 800C68E4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0C74E8 800C68E8 AFB00018 */  sw    $s0, 0x18($sp)
/* 0C74EC 800C68EC 8D8C3768 */  lw    $t4, %lo(gzip_inflate_input)($t4)
/* 0C74F0 800C68F0 10200008 */  beqz  $at, .L800C6914
/* 0C74F4 800C68F4 8D4AAAD0 */   lw    $t2, %lo(gzip_bit_buffer)($t2)
.L800C68F8:
/* 0C74F8 800C68F8 91820000 */  lbu   $v0, ($t4)
/* 0C74FC 800C68FC 258C0001 */  addiu $t4, $t4, 1
/* 0C7500 800C6900 01621004 */  sllv  $v0, $v0, $t3
/* 0C7504 800C6904 256B0008 */  addiu $t3, $t3, 8
/* 0C7508 800C6908 0168082A */  slt   $at, $t3, $t0
/* 0C750C 800C690C 1420FFFA */  bnez  $at, .L800C68F8
/* 0C7510 800C6910 01425025 */   or    $t2, $t2, $v0
.L800C6914:
/* 0C7514 800C6914 31500001 */  andi  $s0, $t2, 1
/* 0C7518 800C6918 010A5006 */  srlv  $t2, $t2, $t0
/* 0C751C 800C691C 01685822 */  sub   $t3, $t3, $t0
/* 0C7520 800C6920 24080002 */  li    $t0, 2
/* 0C7524 800C6924 0168082B */  sltu  $at, $t3, $t0
/* 0C7528 800C6928 10200008 */  beqz  $at, .L800C694C
/* 0C752C 800C692C 00000000 */   nop   
.L800C6930:
/* 0C7530 800C6930 91820000 */  lbu   $v0, ($t4)
/* 0C7534 800C6934 258C0001 */  addiu $t4, $t4, 1
/* 0C7538 800C6938 01621004 */  sllv  $v0, $v0, $t3
/* 0C753C 800C693C 256B0008 */  addiu $t3, $t3, 8
/* 0C7540 800C6940 0168082A */  slt   $at, $t3, $t0
/* 0C7544 800C6944 1420FFFA */  bnez  $at, .L800C6930
/* 0C7548 800C6948 01425025 */   or    $t2, $t2, $v0
.L800C694C:
/* 0C754C 800C694C 3C01800E */  lui   $at, %hi(gzip_inflate_input) # $at, 0x800e
/* 0C7550 800C6950 31490003 */  andi  $t1, $t2, 3
/* 0C7554 800C6954 AC2C3768 */  sw    $t4, %lo(gzip_inflate_input)($at)
/* 0C7558 800C6958 010A5006 */  srlv  $t2, $t2, $t0
/* 0C755C 800C695C 3C018013 */  lui   $at, %hi(gzip_bit_buffer) # $at, 0x8013
/* 0C7560 800C6960 AC2AAAD0 */  sw    $t2, %lo(gzip_bit_buffer)($at)
/* 0C7564 800C6964 01685822 */  sub   $t3, $t3, $t0
/* 0C7568 800C6968 3C018013 */  lui   $at, %hi(gzip_num_bits) # $at, 0x8013
/* 0C756C 800C696C AC2BAAD4 */  sw    $t3, %lo(gzip_num_bits)($at)
/* 0C7570 800C6970 24010002 */  li    $at, 2
/* 0C7574 800C6974 1121000B */  beq   $t1, $at, .L800C69A4
/* 0C7578 800C6978 24010001 */   li    $at, 1
/* 0C757C 800C697C 11210005 */  beq   $t1, $at, .L800C6994
/* 0C7580 800C6980 00000000 */   nop   
/* 0C7584 800C6984 0C031BCD */  jal   gzip_inflate_stored
/* 0C7588 800C6988 00000000 */   nop   
/* 0C758C 800C698C 08031A6B */  j     .L800C69AC
/* 0C7590 800C6990 00000000 */   nop   
.L800C6994:
/* 0C7594 800C6994 0C031B77 */  jal   gzip_inflate_fixed
/* 0C7598 800C6998 00000000 */   nop   
/* 0C759C 800C699C 08031A6B */  j     .L800C69AC
/* 0C75A0 800C69A0 00000000 */   nop   
.L800C69A4:
/* 0C75A4 800C69A4 0C031A71 */  jal   gzip_inflate_dynamic
/* 0C75A8 800C69A8 00000000 */   nop   
.L800C69AC:
/* 0C75AC 800C69AC 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0C75B0 800C69B0 24020001 */  li    $v0, 1
/* 0C75B4 800C69B4 00501022 */  sub   $v0, $v0, $s0
/* 0C75B8 800C69B8 8FB00018 */  lw    $s0, 0x18($sp)
/* 0C75BC 800C69BC 03E00008 */  jr    $ra
/* 0C75C0 800C69C0 27BD0020 */   addiu $sp, $sp, 0x20

