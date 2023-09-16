glabel func_800AC0C8
/* 0ACCC8 800AC0C8 3C098012 */  lui   $t1, %hi(D_80127BB0) # $t1, 0x8012
/* 0ACCCC 800AC0CC 25297BB0 */  addiu $t1, %lo(D_80127BB0) # addiu $t1, $t1, 0x7bb0
/* 0ACCD0 800AC0D0 8D2E0000 */  lw    $t6, ($t1)
/* 0ACCD4 800AC0D4 00803025 */  move  $a2, $a0
/* 0ACCD8 800AC0D8 19C0004E */  blez  $t6, .L800AC214
/* 0ACCDC 800AC0DC 00001025 */   move  $v0, $zero
/* 0ACCE0 800AC0E0 3C0D8012 */  lui   $t5, %hi(D_80127BB8) # $t5, 0x8012
/* 0ACCE4 800AC0E4 3C0C800E */  lui   $t4, %hi(D_800E28D8) # $t4, 0x800e
/* 0ACCE8 800AC0E8 3C0A800E */  lui   $t2, %hi(D_800E28D4) # $t2, 0x800e
/* 0ACCEC 800AC0EC 254A28D4 */  addiu $t2, %lo(D_800E28D4) # addiu $t2, $t2, 0x28d4
/* 0ACCF0 800AC0F0 258C28D8 */  addiu $t4, %lo(D_800E28D8) # addiu $t4, $t4, 0x28d8
/* 0ACCF4 800AC0F4 25AD7BB8 */  addiu $t5, %lo(D_80127BB8) # addiu $t5, $t5, 0x7bb8
/* 0ACCF8 800AC0F8 00002025 */  move  $a0, $zero
/* 0ACCFC 800AC0FC 240B000C */  li    $t3, 12
.L800AC100:
/* 0ACD00 800AC100 8D4F0000 */  lw    $t7, ($t2)
/* 0ACD04 800AC104 8D8E0000 */  lw    $t6, ($t4)
/* 0ACD08 800AC108 01E42821 */  addu  $a1, $t7, $a0
/* 0ACD0C 800AC10C 90B8000F */  lbu   $t8, 0xf($a1)
/* 0ACD10 800AC110 00000000 */  nop   
/* 0ACD14 800AC114 030B0019 */  multu $t8, $t3
/* 0ACD18 800AC118 8DB8000C */  lw    $t8, 0xc($t5)
/* 0ACD1C 800AC11C 0000C812 */  mflo  $t9
/* 0ACD20 800AC120 032E1821 */  addu  $v1, $t9, $t6
/* 0ACD24 800AC124 8C6F0000 */  lw    $t7, ($v1)
/* 0ACD28 800AC128 0018C840 */  sll   $t9, $t8, 1
/* 0ACD2C 800AC12C 01F97021 */  addu  $t6, $t7, $t9
/* 0ACD30 800AC130 01C60019 */  multu $t6, $a2
/* 0ACD34 800AC134 8CB90000 */  lw    $t9, ($a1)
/* 0ACD38 800AC138 0000C012 */  mflo  $t8
/* 0ACD3C 800AC13C 00187843 */  sra   $t7, $t8, 1
/* 0ACD40 800AC140 8D980018 */  lw    $t8, 0x18($t4)
/* 0ACD44 800AC144 032F7021 */  addu  $t6, $t9, $t7
/* 0ACD48 800AC148 01D8C824 */  and   $t9, $t6, $t8
/* 0ACD4C 800AC14C ACB90000 */  sw    $t9, ($a1)
/* 0ACD50 800AC150 8D4F0000 */  lw    $t7, ($t2)
/* 0ACD54 800AC154 8DB80018 */  lw    $t8, 0x18($t5)
/* 0ACD58 800AC158 8C6E0004 */  lw    $t6, 4($v1)
/* 0ACD5C 800AC15C 01E42821 */  addu  $a1, $t7, $a0
/* 0ACD60 800AC160 0018C840 */  sll   $t9, $t8, 1
/* 0ACD64 800AC164 01D97821 */  addu  $t7, $t6, $t9
/* 0ACD68 800AC168 01E60019 */  multu $t7, $a2
/* 0ACD6C 800AC16C 8CB90004 */  lw    $t9, 4($a1)
/* 0ACD70 800AC170 0000C012 */  mflo  $t8
/* 0ACD74 800AC174 00187043 */  sra   $t6, $t8, 1
/* 0ACD78 800AC178 8D98001C */  lw    $t8, 0x1c($t4)
/* 0ACD7C 800AC17C 032E7821 */  addu  $t7, $t9, $t6
/* 0ACD80 800AC180 01F8C824 */  and   $t9, $t7, $t8
/* 0ACD84 800AC184 ACB90004 */  sw    $t9, 4($a1)
/* 0ACD88 800AC188 8D4E0000 */  lw    $t6, ($t2)
/* 0ACD8C 800AC18C 8DB80024 */  lw    $t8, 0x24($t5)
/* 0ACD90 800AC190 8C6F0008 */  lw    $t7, 8($v1)
/* 0ACD94 800AC194 01C42821 */  addu  $a1, $t6, $a0
/* 0ACD98 800AC198 0018C840 */  sll   $t9, $t8, 1
/* 0ACD9C 800AC19C 01F97021 */  addu  $t6, $t7, $t9
/* 0ACDA0 800AC1A0 01C60019 */  multu $t6, $a2
/* 0ACDA4 800AC1A4 8CB90008 */  lw    $t9, 8($a1)
/* 0ACDA8 800AC1A8 0000C012 */  mflo  $t8
/* 0ACDAC 800AC1AC 00187843 */  sra   $t7, $t8, 1
/* 0ACDB0 800AC1B0 8D980020 */  lw    $t8, 0x20($t4)
/* 0ACDB4 800AC1B4 032F7021 */  addu  $t6, $t9, $t7
/* 0ACDB8 800AC1B8 01D8C824 */  and   $t9, $t6, $t8
/* 0ACDBC 800AC1BC ACB90008 */  sw    $t9, 8($a1)
/* 0ACDC0 800AC1C0 8D4F0000 */  lw    $t7, ($t2)
/* 0ACDC4 800AC1C4 00000000 */  nop   
/* 0ACDC8 800AC1C8 01E42821 */  addu  $a1, $t7, $a0
/* 0ACDCC 800AC1CC 90AE000F */  lbu   $t6, 0xf($a1)
/* 0ACDD0 800AC1D0 00000000 */  nop   
/* 0ACDD4 800AC1D4 25D80001 */  addiu $t8, $t6, 1
/* 0ACDD8 800AC1D8 A0B8000F */  sb    $t8, 0xf($a1)
/* 0ACDDC 800AC1DC 8D590000 */  lw    $t9, ($t2)
/* 0ACDE0 800AC1E0 8D880004 */  lw    $t0, 4($t4)
/* 0ACDE4 800AC1E4 03242821 */  addu  $a1, $t9, $a0
/* 0ACDE8 800AC1E8 90A7000F */  lbu   $a3, 0xf($a1)
/* 0ACDEC 800AC1EC 00000000 */  nop   
/* 0ACDF0 800AC1F0 00E8082A */  slt   $at, $a3, $t0
/* 0ACDF4 800AC1F4 14200002 */  bnez  $at, .L800AC200
/* 0ACDF8 800AC1F8 00E87823 */   subu  $t7, $a3, $t0
/* 0ACDFC 800AC1FC A0AF000F */  sb    $t7, 0xf($a1)
.L800AC200:
/* 0ACE00 800AC200 8D2E0000 */  lw    $t6, ($t1)
/* 0ACE04 800AC204 24420001 */  addiu $v0, $v0, 1
/* 0ACE08 800AC208 004E082A */  slt   $at, $v0, $t6
/* 0ACE0C 800AC20C 1420FFBC */  bnez  $at, .L800AC100
/* 0ACE10 800AC210 24840010 */   addiu $a0, $a0, 0x10
.L800AC214:
/* 0ACE14 800AC214 03E00008 */  jr    $ra
/* 0ACE18 800AC218 00000000 */   nop   

