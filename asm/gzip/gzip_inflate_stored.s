glabel gzip_inflate_stored
/* 0C7B34 800C6F34 3C0D8013 */  lui   $t5, %hi(gzip_num_bits) # $t5, 0x8013
/* 0C7B38 800C6F38 8DADAAD4 */  lw    $t5, %lo(gzip_num_bits)($t5)
/* 0C7B3C 800C6F3C 3C0C8013 */  lui   $t4, %hi(gzip_bit_buffer) # $t4, 0x8013
/* 0C7B40 800C6F40 8D8CAAD0 */  lw    $t4, %lo(gzip_bit_buffer)($t4)
/* 0C7B44 800C6F44 31A80007 */  andi  $t0, $t5, 7
/* 0C7B48 800C6F48 01A86822 */  sub   $t5, $t5, $t0
/* 0C7B4C 800C6F4C 010C6006 */  srlv  $t4, $t4, $t0
/* 0C7B50 800C6F50 24080010 */  li    $t0, 16
/* 0C7B54 800C6F54 3C0F800E */  lui   $t7, %hi(gzip_inflate_input) # $t7, 0x800e
/* 0C7B58 800C6F58 3C0E800E */  lui   $t6, %hi(gzip_inflate_output) # $t6, 0x800e
/* 0C7B5C 800C6F5C 01A8082B */  sltu  $at, $t5, $t0
/* 0C7B60 800C6F60 8DEF3768 */  lw    $t7, %lo(gzip_inflate_input)($t7)
/* 0C7B64 800C6F64 10200008 */  beqz  $at, .L800C6F88
/* 0C7B68 800C6F68 8DCE376C */   lw    $t6, %lo(gzip_inflate_output)($t6)
.L800C6F6C:
/* 0C7B6C 800C6F6C 91E20000 */  lbu   $v0, ($t7)
/* 0C7B70 800C6F70 25EF0001 */  addiu $t7, $t7, 1
/* 0C7B74 800C6F74 01A21004 */  sllv  $v0, $v0, $t5
/* 0C7B78 800C6F78 25AD0008 */  addiu $t5, $t5, 8
/* 0C7B7C 800C6F7C 01A8082A */  slt   $at, $t5, $t0
/* 0C7B80 800C6F80 1420FFFA */  bnez  $at, .L800C6F6C
/* 0C7B84 800C6F84 01826025 */   or    $t4, $t4, $v0
.L800C6F88:
/* 0C7B88 800C6F88 01A86822 */  sub   $t5, $t5, $t0
/* 0C7B8C 800C6F8C 3189FFFF */  andi  $t1, $t4, 0xffff
/* 0C7B90 800C6F90 01A8082B */  sltu  $at, $t5, $t0
/* 0C7B94 800C6F94 10200008 */  beqz  $at, .L800C6FB8
/* 0C7B98 800C6F98 010C6006 */   srlv  $t4, $t4, $t0
.L800C6F9C:
/* 0C7B9C 800C6F9C 91E20000 */  lbu   $v0, ($t7)
/* 0C7BA0 800C6FA0 25EF0001 */  addiu $t7, $t7, 1
/* 0C7BA4 800C6FA4 01A21004 */  sllv  $v0, $v0, $t5
/* 0C7BA8 800C6FA8 25AD0008 */  addiu $t5, $t5, 8
/* 0C7BAC 800C6FAC 01A8082A */  slt   $at, $t5, $t0
/* 0C7BB0 800C6FB0 1420FFFA */  bnez  $at, .L800C6F9C
/* 0C7BB4 800C6FB4 01826025 */   or    $t4, $t4, $v0
.L800C6FB8:
/* 0C7BB8 800C6FB8 31220003 */  andi  $v0, $t1, 3
/* 0C7BBC 800C6FBC 010C6006 */  srlv  $t4, $t4, $t0
/* 0C7BC0 800C6FC0 1040000A */  beqz  $v0, .L800C6FEC
/* 0C7BC4 800C6FC4 01A86822 */   sub   $t5, $t5, $t0
/* 0C7BC8 800C6FC8 01224822 */  sub   $t1, $t1, $v0
.L800C6FCC:
/* 0C7BCC 800C6FCC 91EA0000 */  lbu   $t2, ($t7)
/* 0C7BD0 800C6FD0 2042FFFF */  addi  $v0, $v0, -1
/* 0C7BD4 800C6FD4 21EF0001 */  addi  $t7, $t7, 1
/* 0C7BD8 800C6FD8 21CE0001 */  addi  $t6, $t6, 1
/* 0C7BDC 800C6FDC 1440FFFB */  bnez  $v0, .L800C6FCC
/* 0C7BE0 800C6FE0 A1CAFFFF */   sb    $t2, -1($t6)
/* 0C7BE4 800C6FE4 1120000D */  beqz  $t1, .L800C701C
/* 0C7BE8 800C6FE8 00000000 */   nop   
.L800C6FEC:
/* 0C7BEC 800C6FEC 91E20000 */  lbu   $v0, ($t7)
/* 0C7BF0 800C6FF0 2529FFFC */  addiu $t1, $t1, -4
/* 0C7BF4 800C6FF4 25EF0004 */  addiu $t7, $t7, 4
/* 0C7BF8 800C6FF8 A1C20000 */  sb    $v0, ($t6)
/* 0C7BFC 800C6FFC 91E3FFFD */  lbu   $v1, -3($t7)
/* 0C7C00 800C7000 25CE0004 */  addiu $t6, $t6, 4
/* 0C7C04 800C7004 A1C3FFFD */  sb    $v1, -3($t6)
/* 0C7C08 800C7008 91EAFFFE */  lbu   $t2, -2($t7)
/* 0C7C0C 800C700C A1CAFFFE */  sb    $t2, -2($t6)
/* 0C7C10 800C7010 91EBFFFF */  lbu   $t3, -1($t7)
/* 0C7C14 800C7014 1520FFF5 */  bnez  $t1, .L800C6FEC
/* 0C7C18 800C7018 A1CBFFFF */   sb    $t3, -1($t6)
.L800C701C:
/* 0C7C1C 800C701C 3C01800E */  lui   $at, %hi(gzip_inflate_input) # $at, 0x800e
/* 0C7C20 800C7020 AC2F3768 */  sw    $t7, %lo(gzip_inflate_input)($at)
/* 0C7C24 800C7024 3C01800E */  lui   $at, %hi(gzip_inflate_output) # $at, 0x800e
/* 0C7C28 800C7028 AC2E376C */  sw    $t6, %lo(gzip_inflate_output)($at)
/* 0C7C2C 800C702C 3C018013 */  lui   $at, %hi(gzip_bit_buffer) # $at, 0x8013
/* 0C7C30 800C7030 AC2CAAD0 */  sw    $t4, %lo(gzip_bit_buffer)($at)
/* 0C7C34 800C7034 3C018013 */  lui   $at, 0x8013
/* 0C7C38 800C7038 03E00008 */  jr    $ra
/* 0C7C3C 800C703C AC2DAAD4 */   sw    $t5, -0x552c($at)

