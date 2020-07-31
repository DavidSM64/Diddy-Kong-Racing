glabel __osPfsGetInitData
/* 0CE12C 800CD52C 3C0F8013 */  lui   $t7, %hi(D_8012CD91) # $t7, 0x8013
/* 0CE130 800CD530 91EFCD91 */  lbu   $t7, %lo(D_8012CD91)($t7)
/* 0CE134 800CD534 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CE138 800CD538 3C0E8013 */  lui   $t6, %hi(D_8012CDE0) # $t6, 0x8013
/* 0CE13C 800CD53C 25CECDE0 */  addiu $t6, %lo(D_8012CDE0) # addiu $t6, $t6, -0x3220
/* 0CE140 800CD540 A3A00007 */  sb    $zero, 7($sp)
/* 0CE144 800CD544 AFAE0014 */  sw    $t6, 0x14($sp)
/* 0CE148 800CD548 19E00028 */  blez  $t7, .L800CD5EC
/* 0CE14C 800CD54C AFA00008 */   sw    $zero, 8($sp)
.L800CD550:
/* 0CE150 800CD550 8FB90014 */  lw    $t9, 0x14($sp)
/* 0CE154 800CD554 27B8000C */  addiu $t8, $sp, 0xc
/* 0CE158 800CD558 8B210000 */  lwl   $at, ($t9)
/* 0CE15C 800CD55C 9B210003 */  lwr   $at, 3($t9)
/* 0CE160 800CD560 AF010000 */  sw    $at, ($t8)
/* 0CE164 800CD564 8B290004 */  lwl   $t1, 4($t9)
/* 0CE168 800CD568 9B290007 */  lwr   $t1, 7($t9)
/* 0CE16C 800CD56C AF090004 */  sw    $t1, 4($t8)
/* 0CE170 800CD570 93AA000E */  lbu   $t2, 0xe($sp)
/* 0CE174 800CD574 314B00C0 */  andi  $t3, $t2, 0xc0
/* 0CE178 800CD578 000B6103 */  sra   $t4, $t3, 4
/* 0CE17C 800CD57C A0AC0003 */  sb    $t4, 3($a1)
/* 0CE180 800CD580 90AD0003 */  lbu   $t5, 3($a1)
/* 0CE184 800CD584 15A0000E */  bnez  $t5, .L800CD5C0
/* 0CE188 800CD588 00000000 */   nop   
/* 0CE18C 800CD58C 93AE0011 */  lbu   $t6, 0x11($sp)
/* 0CE190 800CD590 93A80010 */  lbu   $t0, 0x10($sp)
/* 0CE194 800CD594 240B0001 */  li    $t3, 1
/* 0CE198 800CD598 000E7A00 */  sll   $t7, $t6, 8
/* 0CE19C 800CD59C 01E8C025 */  or    $t8, $t7, $t0
/* 0CE1A0 800CD5A0 A4B80000 */  sh    $t8, ($a1)
/* 0CE1A4 800CD5A4 93B90012 */  lbu   $t9, 0x12($sp)
/* 0CE1A8 800CD5A8 A0B90002 */  sb    $t9, 2($a1)
/* 0CE1AC 800CD5AC 8FAA0008 */  lw    $t2, 8($sp)
/* 0CE1B0 800CD5B0 93A90007 */  lbu   $t1, 7($sp)
/* 0CE1B4 800CD5B4 014B6004 */  sllv  $t4, $t3, $t2
/* 0CE1B8 800CD5B8 012C6825 */  or    $t5, $t1, $t4
/* 0CE1BC 800CD5BC A3AD0007 */  sb    $t5, 7($sp)
.L800CD5C0:
/* 0CE1C0 800CD5C0 8FAE0008 */  lw    $t6, 8($sp)
/* 0CE1C4 800CD5C4 3C198013 */  lui   $t9, %hi(D_8012CD91) # $t9, 0x8013
/* 0CE1C8 800CD5C8 9339CD91 */  lbu   $t9, %lo(D_8012CD91)($t9)
/* 0CE1CC 800CD5CC 8FA80014 */  lw    $t0, 0x14($sp)
/* 0CE1D0 800CD5D0 25CF0001 */  addiu $t7, $t6, 1
/* 0CE1D4 800CD5D4 01F9082A */  slt   $at, $t7, $t9
/* 0CE1D8 800CD5D8 25180008 */  addiu $t8, $t0, 8
/* 0CE1DC 800CD5DC AFB80014 */  sw    $t8, 0x14($sp)
/* 0CE1E0 800CD5E0 AFAF0008 */  sw    $t7, 8($sp)
/* 0CE1E4 800CD5E4 1420FFDA */  bnez  $at, .L800CD550
/* 0CE1E8 800CD5E8 24A50004 */   addiu $a1, $a1, 4
.L800CD5EC:
/* 0CE1EC 800CD5EC 93AB0007 */  lbu   $t3, 7($sp)
/* 0CE1F0 800CD5F0 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CE1F4 800CD5F4 03E00008 */  jr    $ra
/* 0CE1F8 800CD5F8 A08B0000 */   sb    $t3, ($a0)

/* 0CE1FC 800CD5FC 00000000 */  nop   

