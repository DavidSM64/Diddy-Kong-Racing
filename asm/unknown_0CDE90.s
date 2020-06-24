.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800CD290
/* 0CDE90 800CD290 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 0CDE94 800CD294 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CDE98 800CD298 240E0003 */  li    $t6, 3
/* 0CDE9C 800CD29C AFA40040 */  sw    $a0, 0x40($sp)
/* 0CDEA0 800CD2A0 AFA50044 */  sw    $a1, 0x44($sp)
/* 0CDEA4 800CD2A4 AFA0003C */  sw    $zero, 0x3c($sp)
/* 0CDEA8 800CD2A8 A3A0001F */  sb    $zero, 0x1f($sp)
/* 0CDEAC 800CD2AC 0C033594 */  jal   func_800CD650
/* 0CDEB0 800CD2B0 AFAE0018 */   sw    $t6, 0x18($sp)
.L800CD2B4:
/* 0CDEB4 800CD2B4 0C03350C */  jal   func_800CD430
/* 0CDEB8 800CD2B8 00002025 */   move  $a0, $zero
/* 0CDEBC 800CD2BC 3C058013 */  lui   $a1, %hi(D_8012CDE0) # $a1, 0x8013
/* 0CDEC0 800CD2C0 24A5CDE0 */  addiu $a1, %lo(D_8012CDE0) # addiu $a1, $a1, -0x3220
/* 0CDEC4 800CD2C4 0C0335B0 */  jal   func_800CD6C0
/* 0CDEC8 800CD2C8 24040001 */   li    $a0, 1
/* 0CDECC 800CD2CC AFA2003C */  sw    $v0, 0x3c($sp)
/* 0CDED0 800CD2D0 8FA40040 */  lw    $a0, 0x40($sp)
/* 0CDED4 800CD2D4 27A50038 */  addiu $a1, $sp, 0x38
/* 0CDED8 800CD2D8 0C0322EC */  jal   osRecvMesg
/* 0CDEDC 800CD2DC 24060001 */   li    $a2, 1
/* 0CDEE0 800CD2E0 3C058013 */  lui   $a1, %hi(D_8012CDE0) # $a1, 0x8013
/* 0CDEE4 800CD2E4 24A5CDE0 */  addiu $a1, %lo(D_8012CDE0) # addiu $a1, $a1, -0x3220
/* 0CDEE8 800CD2E8 0C0335B0 */  jal   func_800CD6C0
/* 0CDEEC 800CD2EC 00002025 */   move  $a0, $zero
/* 0CDEF0 800CD2F0 AFA2003C */  sw    $v0, 0x3c($sp)
/* 0CDEF4 800CD2F4 8FA40040 */  lw    $a0, 0x40($sp)
/* 0CDEF8 800CD2F8 27A50038 */  addiu $a1, $sp, 0x38
/* 0CDEFC 800CD2FC 0C0322EC */  jal   osRecvMesg
/* 0CDF00 800CD300 24060001 */   li    $a2, 1
/* 0CDF04 800CD304 27A40037 */  addiu $a0, $sp, 0x37
/* 0CDF08 800CD308 0C03354B */  jal   func_800CD52C
/* 0CDF0C 800CD30C 27A50024 */   addiu $a1, $sp, 0x24
/* 0CDF10 800CD310 3C0F8013 */  lui   $t7, %hi(D_8012CD91) # $t7, 0x8013
/* 0CDF14 800CD314 91EFCD91 */  lbu   $t7, %lo(D_8012CD91)($t7)
/* 0CDF18 800CD318 AFA00020 */  sw    $zero, 0x20($sp)
/* 0CDF1C 800CD31C 19E00014 */  blez  $t7, .L800CD370
/* 0CDF20 800CD320 00000000 */   nop   
.L800CD324:
/* 0CDF24 800CD324 8FB80020 */  lw    $t8, 0x20($sp)
/* 0CDF28 800CD328 0018C880 */  sll   $t9, $t8, 2
/* 0CDF2C 800CD32C 03B94021 */  addu  $t0, $sp, $t9
/* 0CDF30 800CD330 91080026 */  lbu   $t0, 0x26($t0)
/* 0CDF34 800CD334 31090004 */  andi  $t1, $t0, 4
/* 0CDF38 800CD338 15200005 */  bnez  $t1, .L800CD350
/* 0CDF3C 800CD33C 00000000 */   nop   
/* 0CDF40 800CD340 8FAA0018 */  lw    $t2, 0x18($sp)
/* 0CDF44 800CD344 254BFFFF */  addiu $t3, $t2, -1
/* 0CDF48 800CD348 10000009 */  b     .L800CD370
/* 0CDF4C 800CD34C AFAB0018 */   sw    $t3, 0x18($sp)
.L800CD350:
/* 0CDF50 800CD350 8FAC0020 */  lw    $t4, 0x20($sp)
/* 0CDF54 800CD354 3C0E8013 */  lui   $t6, %hi(D_8012CD91) # $t6, 0x8013
/* 0CDF58 800CD358 91CECD91 */  lbu   $t6, %lo(D_8012CD91)($t6)
/* 0CDF5C 800CD35C 258D0001 */  addiu $t5, $t4, 1
/* 0CDF60 800CD360 AFAD0020 */  sw    $t5, 0x20($sp)
/* 0CDF64 800CD364 01AE082A */  slt   $at, $t5, $t6
/* 0CDF68 800CD368 1420FFEE */  bnez  $at, .L800CD324
/* 0CDF6C 800CD36C 00000000 */   nop   
.L800CD370:
/* 0CDF70 800CD370 3C0F8013 */  lui   $t7, %hi(D_8012CD91) # $t7, 0x8013
/* 0CDF74 800CD374 91EFCD91 */  lbu   $t7, %lo(D_8012CD91)($t7)
/* 0CDF78 800CD378 8FB80020 */  lw    $t8, 0x20($sp)
/* 0CDF7C 800CD37C 15F80002 */  bne   $t7, $t8, .L800CD388
/* 0CDF80 800CD380 00000000 */   nop   
/* 0CDF84 800CD384 AFA00018 */  sw    $zero, 0x18($sp)
.L800CD388:
/* 0CDF88 800CD388 8FB90018 */  lw    $t9, 0x18($sp)
/* 0CDF8C 800CD38C 1F20FFC9 */  bgtz  $t9, .L800CD2B4
/* 0CDF90 800CD390 00000000 */   nop   
/* 0CDF94 800CD394 3C088013 */  lui   $t0, %hi(D_8012CD91) # $t0, 0x8013
/* 0CDF98 800CD398 9108CD91 */  lbu   $t0, %lo(D_8012CD91)($t0)
/* 0CDF9C 800CD39C AFA00020 */  sw    $zero, 0x20($sp)
/* 0CDFA0 800CD3A0 19000019 */  blez  $t0, .L800CD408
/* 0CDFA4 800CD3A4 00000000 */   nop   
.L800CD3A8:
/* 0CDFA8 800CD3A8 8FA90020 */  lw    $t1, 0x20($sp)
/* 0CDFAC 800CD3AC 27AB0024 */  addiu $t3, $sp, 0x24
/* 0CDFB0 800CD3B0 00095080 */  sll   $t2, $t1, 2
/* 0CDFB4 800CD3B4 014B6021 */  addu  $t4, $t2, $t3
/* 0CDFB8 800CD3B8 918D0003 */  lbu   $t5, 3($t4)
/* 0CDFBC 800CD3BC 15A0000A */  bnez  $t5, .L800CD3E8
/* 0CDFC0 800CD3C0 00000000 */   nop   
/* 0CDFC4 800CD3C4 918E0002 */  lbu   $t6, 2($t4)
/* 0CDFC8 800CD3C8 31CF0001 */  andi  $t7, $t6, 1
/* 0CDFCC 800CD3CC 11E00006 */  beqz  $t7, .L800CD3E8
/* 0CDFD0 800CD3D0 00000000 */   nop   
/* 0CDFD4 800CD3D4 93B8001F */  lbu   $t8, 0x1f($sp)
/* 0CDFD8 800CD3D8 24190001 */  li    $t9, 1
/* 0CDFDC 800CD3DC 01394004 */  sllv  $t0, $t9, $t1
/* 0CDFE0 800CD3E0 03085025 */  or    $t2, $t8, $t0
/* 0CDFE4 800CD3E4 A3AA001F */  sb    $t2, 0x1f($sp)
.L800CD3E8:
/* 0CDFE8 800CD3E8 8FAB0020 */  lw    $t3, 0x20($sp)
/* 0CDFEC 800CD3EC 3C0C8013 */  lui   $t4, %hi(D_8012CD91) # $t4, 0x8013
/* 0CDFF0 800CD3F0 918CCD91 */  lbu   $t4, %lo(D_8012CD91)($t4)
/* 0CDFF4 800CD3F4 256D0001 */  addiu $t5, $t3, 1
/* 0CDFF8 800CD3F8 AFAD0020 */  sw    $t5, 0x20($sp)
/* 0CDFFC 800CD3FC 01AC082A */  slt   $at, $t5, $t4
/* 0CE000 800CD400 1420FFE9 */  bnez  $at, .L800CD3A8
/* 0CE004 800CD404 00000000 */   nop   
.L800CD408:
/* 0CE008 800CD408 0C0335A5 */  jal   func_800CD694
/* 0CE00C 800CD40C 00000000 */   nop   
/* 0CE010 800CD410 93AE001F */  lbu   $t6, 0x1f($sp)
/* 0CE014 800CD414 8FAF0044 */  lw    $t7, 0x44($sp)
/* 0CE018 800CD418 A1EE0000 */  sb    $t6, ($t7)
/* 0CE01C 800CD41C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CE020 800CD420 8FA2003C */  lw    $v0, 0x3c($sp)
/* 0CE024 800CD424 27BD0040 */  addiu $sp, $sp, 0x40
/* 0CE028 800CD428 03E00008 */  jr    $ra
/* 0CE02C 800CD42C 00000000 */   nop   

glabel func_800CD430
/* 0CE030 800CD430 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CE034 800CD434 308400FF */  andi  $a0, $a0, 0xff
/* 0CE038 800CD438 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CE03C 800CD43C A024CD90 */  sb    $a0, %lo(D_8012CD90)($at)
/* 0CE040 800CD440 AFA00000 */  sw    $zero, ($sp)
.L800CD444:
/* 0CE044 800CD444 8FAE0000 */  lw    $t6, ($sp)
/* 0CE048 800CD448 8FB80000 */  lw    $t8, ($sp)
/* 0CE04C 800CD44C 3C018013 */  lui   $at, 0x8013
/* 0CE050 800CD450 000E7880 */  sll   $t7, $t6, 2
/* 0CE054 800CD454 002F0821 */  addu  $at, $at, $t7
/* 0CE058 800CD458 AC20CDE0 */  sw    $zero, -0x3220($at)
/* 0CE05C 800CD45C 27190001 */  addiu $t9, $t8, 1
/* 0CE060 800CD460 2B210010 */  slti  $at, $t9, 0x10
/* 0CE064 800CD464 1420FFF7 */  bnez  $at, .L800CD444
/* 0CE068 800CD468 AFB90000 */   sw    $t9, ($sp)
/* 0CE06C 800CD46C 3C198013 */  lui   $t9, %hi(D_8012CD91) # $t9, 0x8013
/* 0CE070 800CD470 9339CD91 */  lbu   $t9, %lo(D_8012CD91)($t9)
/* 0CE074 800CD474 3C098013 */  lui   $t1, %hi(D_8012CDE0) # $t1, 0x8013
/* 0CE078 800CD478 24080001 */  li    $t0, 1
/* 0CE07C 800CD47C 3C018013 */  lui   $at, %hi(D_8012CE1C) # $at, 0x8013
/* 0CE080 800CD480 2529CDE0 */  addiu $t1, %lo(D_8012CDE0) # addiu $t1, $t1, -0x3220
/* 0CE084 800CD484 240A00FF */  li    $t2, 255
/* 0CE088 800CD488 240B0001 */  li    $t3, 1
/* 0CE08C 800CD48C 240C0003 */  li    $t4, 3
/* 0CE090 800CD490 240D00FF */  li    $t5, 255
/* 0CE094 800CD494 240E00FF */  li    $t6, 255
/* 0CE098 800CD498 240F00FF */  li    $t7, 255
/* 0CE09C 800CD49C 241800FF */  li    $t8, 255
/* 0CE0A0 800CD4A0 AC28CE1C */  sw    $t0, %lo(D_8012CE1C)($at)
/* 0CE0A4 800CD4A4 AFA9000C */  sw    $t1, 0xc($sp)
/* 0CE0A8 800CD4A8 A3AA0004 */  sb    $t2, 4($sp)
/* 0CE0AC 800CD4AC A3AB0005 */  sb    $t3, 5($sp)
/* 0CE0B0 800CD4B0 A3AC0006 */  sb    $t4, 6($sp)
/* 0CE0B4 800CD4B4 A3A40007 */  sb    $a0, 7($sp)
/* 0CE0B8 800CD4B8 A3AD0008 */  sb    $t5, 8($sp)
/* 0CE0BC 800CD4BC A3AE0009 */  sb    $t6, 9($sp)
/* 0CE0C0 800CD4C0 A3AF000A */  sb    $t7, 0xa($sp)
/* 0CE0C4 800CD4C4 A3B8000B */  sb    $t8, 0xb($sp)
/* 0CE0C8 800CD4C8 1B200013 */  blez  $t9, .L800CD518
/* 0CE0CC 800CD4CC AFA00000 */   sw    $zero, ($sp)
.L800CD4D0:
/* 0CE0D0 800CD4D0 27A90004 */  addiu $t1, $sp, 4
/* 0CE0D4 800CD4D4 8D210000 */  lw    $at, ($t1)
/* 0CE0D8 800CD4D8 8FA8000C */  lw    $t0, 0xc($sp)
/* 0CE0DC 800CD4DC 3C188013 */  lui   $t8, %hi(D_8012CD91) # $t8, 0x8013
/* 0CE0E0 800CD4E0 A9010000 */  swl   $at, ($t0)
/* 0CE0E4 800CD4E4 B9010003 */  swr   $at, 3($t0)
/* 0CE0E8 800CD4E8 8D2B0004 */  lw    $t3, 4($t1)
/* 0CE0EC 800CD4EC A90B0004 */  swl   $t3, 4($t0)
/* 0CE0F0 800CD4F0 B90B0007 */  swr   $t3, 7($t0)
/* 0CE0F4 800CD4F4 8FAE0000 */  lw    $t6, ($sp)
/* 0CE0F8 800CD4F8 9318CD91 */  lbu   $t8, %lo(D_8012CD91)($t8)
/* 0CE0FC 800CD4FC 8FAC000C */  lw    $t4, 0xc($sp)
/* 0CE100 800CD500 25CF0001 */  addiu $t7, $t6, 1
/* 0CE104 800CD504 01F8082A */  slt   $at, $t7, $t8
/* 0CE108 800CD508 258D0008 */  addiu $t5, $t4, 8
/* 0CE10C 800CD50C AFAF0000 */  sw    $t7, ($sp)
/* 0CE110 800CD510 1420FFEF */  bnez  $at, .L800CD4D0
/* 0CE114 800CD514 AFAD000C */   sw    $t5, 0xc($sp)
.L800CD518:
/* 0CE118 800CD518 8FAA000C */  lw    $t2, 0xc($sp)
/* 0CE11C 800CD51C 241900FE */  li    $t9, 254
/* 0CE120 800CD520 27BD0010 */  addiu $sp, $sp, 0x10
/* 0CE124 800CD524 03E00008 */  jr    $ra
/* 0CE128 800CD528 A1590000 */   sb    $t9, ($t2)

glabel func_800CD52C
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
