glabel osSetIntMask
/* 0CA630 800C9A30 400C6000 */  mfc0  $t4, $12
/* 0CA634 800C9A34 3182FF01 */  andi  $v0, $t4, 0xff01
/* 0CA638 800C9A38 3C08800E */  lui   $t0, %hi(__OSGlobalIntMask) # $t0, 0x800e
/* 0CA63C 800C9A3C 250838AC */  addiu $t0, %lo(__OSGlobalIntMask) # addiu $t0, $t0, 0x38ac
/* 0CA640 800C9A40 8D0B0000 */  lw    $t3, ($t0)
/* 0CA644 800C9A44 2401FFFF */  li    $at, -1
/* 0CA648 800C9A48 01614026 */  xor   $t0, $t3, $at
/* 0CA64C 800C9A4C 3108FF00 */  andi  $t0, $t0, 0xff00
/* 0CA650 800C9A50 00481025 */  or    $v0, $v0, $t0
/* 0CA654 800C9A54 3C0AA430 */  lui   $t2, %hi(MI_INTR_MASK_REG) # $t2, 0xa430
/* 0CA658 800C9A58 8D4A000C */  lw    $t2, %lo(MI_INTR_MASK_REG)($t2)
/* 0CA65C 800C9A5C 11400005 */  beqz  $t2, .L800C9A74
/* 0CA660 800C9A60 000B4C02 */   srl   $t1, $t3, 0x10
/* 0CA664 800C9A64 2401FFFF */  li    $at, -1
/* 0CA668 800C9A68 01214826 */  xor   $t1, $t1, $at
/* 0CA66C 800C9A6C 3129003F */  andi  $t1, $t1, 0x3f
/* 0CA670 800C9A70 01495025 */  or    $t2, $t2, $t1
.L800C9A74:
/* 0CA674 800C9A74 000A5400 */  sll   $t2, $t2, 0x10
/* 0CA678 800C9A78 004A1025 */  or    $v0, $v0, $t2
/* 0CA67C 800C9A7C 3C01003F */  lui   $at, 0x3f
/* 0CA680 800C9A80 00814024 */  and   $t0, $a0, $at
/* 0CA684 800C9A84 010B4024 */  and   $t0, $t0, $t3
/* 0CA688 800C9A88 000843C2 */  srl   $t0, $t0, 0xf
/* 0CA68C 800C9A8C 3C0A800F */  lui   $t2, %hi(D_800E94D0) # $t2, 0x800f
/* 0CA690 800C9A90 01485021 */  addu  $t2, $t2, $t0
/* 0CA694 800C9A94 954A94D0 */  lhu   $t2, %lo(D_800E94D0)($t2)
/* 0CA698 800C9A98 3C01A430 */  lui   $at, %hi(MI_INTR_MASK_REG) # $at, 0xa430
/* 0CA69C 800C9A9C AC2A000C */  sw    $t2, %lo(MI_INTR_MASK_REG)($at)
/* 0CA6A0 800C9AA0 3088FF01 */  andi  $t0, $a0, 0xff01
/* 0CA6A4 800C9AA4 3169FF00 */  andi  $t1, $t3, 0xff00
/* 0CA6A8 800C9AA8 01094024 */  and   $t0, $t0, $t1
/* 0CA6AC 800C9AAC 3C01FFFF */  lui   $at, (0xFFFF00FF >> 16) # lui $at, 0xffff
/* 0CA6B0 800C9AB0 342100FF */  ori   $at, (0xFFFF00FF & 0xFFFF) # ori $at, $at, 0xff
/* 0CA6B4 800C9AB4 01816024 */  and   $t4, $t4, $at
/* 0CA6B8 800C9AB8 01886025 */  or    $t4, $t4, $t0
/* 0CA6BC 800C9ABC 408C6000 */  mtc0  $t4, $12
/* 0CA6C0 800C9AC0 00000000 */  nop   
/* 0CA6C4 800C9AC4 00000000 */  nop   
/* 0CA6C8 800C9AC8 03E00008 */  jr    $ra
/* 0CA6CC 800C9ACC 00000000 */   nop   

