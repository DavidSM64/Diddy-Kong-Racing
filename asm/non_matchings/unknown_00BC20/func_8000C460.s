glabel func_8000C460
/* 00D060 8000C460 24020001 */  li    $v0, 1
/* 00D064 8000C464 3C018012 */  lui   $at, %hi(D_8011AD26) # $at, 0x8012
/* 00D068 8000C468 A022AD26 */  sb    $v0, %lo(D_8011AD26)($at)
/* 00D06C 8000C46C 3C018012 */  lui   $at, %hi(D_8011AD5C) # $at, 0x8012
/* 00D070 8000C470 AC20AD5C */  sw    $zero, %lo(D_8011AD5C)($at)
/* 00D074 8000C474 3C018012 */  lui   $at, %hi(D_8011AD60) # $at, 0x8012
/* 00D078 8000C478 AC20AD60 */  sw    $zero, %lo(D_8011AD60)($at)
/* 00D07C 8000C47C 3C018012 */  lui   $at, %hi(D_8011AEC8) # $at, 0x8012
/* 00D080 8000C480 AC20AEC8 */  sw    $zero, %lo(D_8011AEC8)($at)
/* 00D084 8000C484 3C018012 */  lui   $at, %hi(D_8011AE70) # $at, 0x8012
/* 00D088 8000C488 AC20AE70 */  sw    $zero, %lo(D_8011AE70)($at)
/* 00D08C 8000C48C 3C018012 */  lui   $at, %hi(D_8011AED0) # $at, 0x8012
/* 00D090 8000C490 AC20AED0 */  sw    $zero, %lo(D_8011AED0)($at)
/* 00D094 8000C494 3C018012 */  lui   $at, %hi(D_8011AED4) # $at, 0x8012
/* 00D098 8000C498 AC20AED4 */  sw    $zero, %lo(D_8011AED4)($at)
/* 00D09C 8000C49C 3C018012 */  lui   $at, %hi(D_8011AEF0) # $at, 0x8012
/* 00D0A0 8000C4A0 AC20AEF0 */  sw    $zero, %lo(D_8011AEF0)($at)
/* 00D0A4 8000C4A4 3C018012 */  lui   $at, %hi(D_8011AE78) # $at, 0x8012
/* 00D0A8 8000C4A8 A420AE78 */  sh    $zero, %lo(D_8011AE78)($at)
/* 00D0AC 8000C4AC 3C058012 */  lui   $a1, %hi(D_8011AD22) # $a1, 0x8012
/* 00D0B0 8000C4B0 3C018012 */  lui   $at, %hi(D_8011AD21) # $at, 0x8012
/* 00D0B4 8000C4B4 24A5AD22 */  addiu $a1, %lo(D_8011AD22) # addiu $a1, $a1, -0x52de
/* 00D0B8 8000C4B8 A020AD21 */  sb    $zero, %lo(D_8011AD21)($at)
/* 00D0BC 8000C4BC 3C038012 */  lui   $v1, %hi(D_8011AF04) # $v1, 0x8012
/* 00D0C0 8000C4C0 A0A00000 */  sb    $zero, ($a1)
/* 00D0C4 8000C4C4 A0A00001 */  sb    $zero, 1($a1)
/* 00D0C8 8000C4C8 2463AF04 */  addiu $v1, %lo(D_8011AF04) # addiu $v1, $v1, -0x50fc
/* 00D0CC 8000C4CC 00002025 */  move  $a0, $zero
.L8000C4D0:
/* 00D0D0 8000C4D0 8C6E0000 */  lw    $t6, ($v1)
/* 00D0D4 8000C4D4 00000000 */  nop   
/* 00D0D8 8000C4D8 01C47821 */  addu  $t7, $t6, $a0
/* 00D0DC 8000C4DC 24840004 */  addiu $a0, $a0, 4
/* 00D0E0 8000C4E0 28810200 */  slti  $at, $a0, 0x200
/* 00D0E4 8000C4E4 1420FFFA */  bnez  $at, .L8000C4D0
/* 00D0E8 8000C4E8 ADE00000 */   sw    $zero, ($t7)
/* 00D0EC 8000C4EC 3C048012 */  lui   $a0, %hi(D_8011ADCC) # $a0, 0x8012
/* 00D0F0 8000C4F0 2484ADCC */  addiu $a0, %lo(D_8011ADCC) # addiu $a0, $a0, -0x5234
/* 00D0F4 8000C4F4 00001825 */  move  $v1, $zero
.L8000C4F8:
/* 00D0F8 8000C4F8 8C980000 */  lw    $t8, ($a0)
/* 00D0FC 8000C4FC 00000000 */  nop   
/* 00D100 8000C500 0303C821 */  addu  $t9, $t8, $v1
/* 00D104 8000C504 24630001 */  addiu $v1, $v1, 1
/* 00D108 8000C508 28610008 */  slti  $at, $v1, 8
/* 00D10C 8000C50C 1420FFFA */  bnez  $at, .L8000C4F8
/* 00D110 8000C510 A3200000 */   sb    $zero, ($t9)
/* 00D114 8000C514 3C038012 */  lui   $v1, %hi(D_8011AFF4) # $v1, 0x8012
/* 00D118 8000C518 2463AFF4 */  addiu $v1, %lo(D_8011AFF4) # addiu $v1, $v1, -0x500c
/* 00D11C 8000C51C 00002025 */  move  $a0, $zero
/* 00D120 8000C520 24050400 */  li    $a1, 1024
.L8000C524:
/* 00D124 8000C524 8C680000 */  lw    $t0, ($v1)
/* 00D128 8000C528 00000000 */  nop   
/* 00D12C 8000C52C 01044821 */  addu  $t1, $t0, $a0
/* 00D130 8000C530 AD200000 */  sw    $zero, ($t1)
/* 00D134 8000C534 8C6A0000 */  lw    $t2, ($v1)
/* 00D138 8000C538 00000000 */  nop   
/* 00D13C 8000C53C 01445821 */  addu  $t3, $t2, $a0
/* 00D140 8000C540 AD600040 */  sw    $zero, 0x40($t3)
/* 00D144 8000C544 8C6C0000 */  lw    $t4, ($v1)
/* 00D148 8000C548 00000000 */  nop   
/* 00D14C 8000C54C 01846821 */  addu  $t5, $t4, $a0
/* 00D150 8000C550 ADA00080 */  sw    $zero, 0x80($t5)
/* 00D154 8000C554 8C6E0000 */  lw    $t6, ($v1)
/* 00D158 8000C558 00000000 */  nop   
/* 00D15C 8000C55C 01C47821 */  addu  $t7, $t6, $a0
/* 00D160 8000C560 24840100 */  addiu $a0, $a0, 0x100
/* 00D164 8000C564 1485FFEF */  bne   $a0, $a1, .L8000C524
/* 00D168 8000C568 ADE000C0 */   sw    $zero, 0xc0($t7)
/* 00D16C 8000C56C 3C038012 */  lui   $v1, %hi(D_8011AF08) # $v1, 0x8012
/* 00D170 8000C570 2463AF08 */  addiu $v1, %lo(D_8011AF08) # addiu $v1, $v1, -0x50f8
/* 00D174 8000C574 240400FF */  li    $a0, 255
/* 00D178 8000C578 AC640000 */  sw    $a0, ($v1)
/* 00D17C 8000C57C AC640004 */  sw    $a0, 4($v1)
/* 00D180 8000C580 3C018012 */  lui   $at, %hi(D_8011AE5C) # $at, 0x8012
/* 00D184 8000C584 AC20AE5C */  sw    $zero, %lo(D_8011AE5C)($at)
/* 00D188 8000C588 3C018012 */  lui   $at, %hi(D_8011AE60) # $at, 0x8012
/* 00D18C 8000C58C AC20AE60 */  sw    $zero, %lo(D_8011AE60)($at)
/* 00D190 8000C590 3C018012 */  lui   $at, %hi(D_8011AE64) # $at, 0x8012
/* 00D194 8000C594 AC20AE64 */  sw    $zero, %lo(D_8011AE64)($at)
/* 00D198 8000C598 3C018012 */  lui   $at, %hi(D_8011AE88) # $at, 0x8012
/* 00D19C 8000C59C AC20AE88 */  sw    $zero, %lo(D_8011AE88)($at)
/* 00D1A0 8000C5A0 3C018012 */  lui   $at, %hi(D_8011ADD4) # $at, 0x8012
/* 00D1A4 8000C5A4 A020ADD4 */  sb    $zero, %lo(D_8011ADD4)($at)
/* 00D1A8 8000C5A8 3C018012 */  lui   $at, %hi(D_8011AE7A) # $at, 0x8012
/* 00D1AC 8000C5AC A420AE7A */  sh    $zero, %lo(D_8011AE7A)($at)
/* 00D1B0 8000C5B0 3C018012 */  lui   $at, %hi(D_8011AE7E) # $at, 0x8012
/* 00D1B4 8000C5B4 A022AE7E */  sb    $v0, %lo(D_8011AE7E)($at)
/* 00D1B8 8000C5B8 3C018012 */  lui   $at, %hi(D_8011AE7C) # $at, 0x8012
/* 00D1BC 8000C5BC A420AE7C */  sh    $zero, %lo(D_8011AE7C)($at)
/* 00D1C0 8000C5C0 3C018012 */  lui   $at, %hi(D_8011AD44) # $at, 0x8012
/* 00D1C4 8000C5C4 A020AD44 */  sb    $zero, %lo(D_8011AD44)($at)
/* 00D1C8 8000C5C8 3C018012 */  lui   $at, %hi(D_8011AEF6) # $at, 0x8012
/* 00D1CC 8000C5CC A020AEF6 */  sb    $zero, %lo(D_8011AEF6)($at)
/* 00D1D0 8000C5D0 3C018012 */  lui   $at, %hi(D_8011AEF7) # $at, 0x8012
/* 00D1D4 8000C5D4 A020AEF7 */  sb    $zero, %lo(D_8011AEF7)($at)
/* 00D1D8 8000C5D8 3C018012 */  lui   $at, %hi(D_8011AF60) # $at, 0x8012
/* 00D1DC 8000C5DC AC20AF60 */  sw    $zero, %lo(D_8011AF60)($at)
/* 00D1E0 8000C5E0 3C018012 */  lui   $at, %hi(D_8011AE00) # $at, 0x8012
/* 00D1E4 8000C5E4 A020AE00 */  sb    $zero, %lo(D_8011AE00)($at)
/* 00D1E8 8000C5E8 3C018012 */  lui   $at, %hi(D_8011AE01) # $at, 0x8012
/* 00D1EC 8000C5EC A022AE01 */  sb    $v0, %lo(D_8011AE01)($at)
/* 00D1F0 8000C5F0 3C018012 */  lui   $at, %hi(D_8011AD53) # $at, 0x8012
/* 00D1F4 8000C5F4 A020AD53 */  sb    $zero, %lo(D_8011AD53)($at)
/* 00D1F8 8000C5F8 3C018012 */  lui   $at, 0x8012
/* 00D1FC 8000C5FC 03E00008 */  jr    $ra
/* 00D200 8000C600 A020ADD5 */   sb    $zero, -0x522b($at)

