glabel func_800B695C
/* 0B755C 800B695C 8FAF0010 */  lw    $t7, 0x10($sp)
/* 0B7560 800B6960 00A77026 */  xor   $t6, $a1, $a3
/* 0B7564 800B6964 00CFC026 */  xor   $t8, $a2, $t7
/* 0B7568 800B6968 2F180001 */  sltiu $t8, $t8, 1
/* 0B756C 800B696C 2DCE0001 */  sltiu $t6, $t6, 1
/* 0B7570 800B6970 01D8C825 */  or    $t9, $t6, $t8
/* 0B7574 800B6974 1720001F */  bnez  $t9, .L800B69F4
/* 0B7578 800B6978 2CA10002 */   sltiu $at, $a1, 2
/* 0B757C 800B697C 14200002 */  bnez  $at, .L800B6988
/* 0B7580 800B6980 24E70002 */   addiu $a3, $a3, 2
/* 0B7584 800B6984 24A5FFFE */  addiu $a1, $a1, -2
.L800B6988:
/* 0B7588 800B6988 8C830000 */  lw    $v1, ($a0)
/* 0B758C 800B698C 3C0AFCFF */  lui   $t2, (0xFCFFFFFF >> 16) # lui $t2, 0xfcff
/* 0B7590 800B6990 24690008 */  addiu $t1, $v1, 8
/* 0B7594 800B6994 AC890000 */  sw    $t1, ($a0)
/* 0B7598 800B6998 3C0BFFFD */  lui   $t3, (0xFFFDF6FB >> 16) # lui $t3, 0xfffd
/* 0B759C 800B699C 356BF6FB */  ori   $t3, (0xFFFDF6FB & 0xFFFF) # ori $t3, $t3, 0xf6fb
/* 0B75A0 800B69A0 354AFFFF */  ori   $t2, (0xFCFFFFFF & 0xFFFF) # ori $t2, $t2, 0xffff
/* 0B75A4 800B69A4 AC6A0000 */  sw    $t2, ($v1)
/* 0B75A8 800B69A8 AC6B0004 */  sw    $t3, 4($v1)
/* 0B75AC 800B69AC 8C830000 */  lw    $v1, ($a0)
/* 0B75B0 800B69B0 30ED03FF */  andi  $t5, $a3, 0x3ff
/* 0B75B4 800B69B4 246C0008 */  addiu $t4, $v1, 8
/* 0B75B8 800B69B8 AC8C0000 */  sw    $t4, ($a0)
/* 0B75BC 800B69BC 8FB80010 */  lw    $t8, 0x10($sp)
/* 0B75C0 800B69C0 000D7B80 */  sll   $t7, $t5, 0xe
/* 0B75C4 800B69C4 3C01F600 */  lui   $at, 0xf600
/* 0B75C8 800B69C8 01E17025 */  or    $t6, $t7, $at
/* 0B75CC 800B69CC 30CD03FF */  andi  $t5, $a2, 0x3ff
/* 0B75D0 800B69D0 30AB03FF */  andi  $t3, $a1, 0x3ff
/* 0B75D4 800B69D4 331903FF */  andi  $t9, $t8, 0x3ff
/* 0B75D8 800B69D8 00194880 */  sll   $t1, $t9, 2
/* 0B75DC 800B69DC 000B6380 */  sll   $t4, $t3, 0xe
/* 0B75E0 800B69E0 000D7880 */  sll   $t7, $t5, 2
/* 0B75E4 800B69E4 018FC025 */  or    $t8, $t4, $t7
/* 0B75E8 800B69E8 01C95025 */  or    $t2, $t6, $t1
/* 0B75EC 800B69EC AC6A0000 */  sw    $t2, ($v1)
/* 0B75F0 800B69F0 AC780004 */  sw    $t8, 4($v1)
.L800B69F4:
/* 0B75F4 800B69F4 03E00008 */  jr    $ra
/* 0B75F8 800B69F8 00000000 */   nop   

