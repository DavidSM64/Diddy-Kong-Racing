glabel func_800CD14C
/* 0CDD4C 800CD14C 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CDD50 800CD150 3C0E8013 */  lui   $t6, %hi(D_8012CD50) # $t6, 0x8013
/* 0CDD54 800CD154 25CECD50 */  addiu $t6, %lo(D_8012CD50) # addiu $t6, $t6, -0x32b0
/* 0CDD58 800CD158 AFAE000C */  sw    $t6, 0xc($sp)
/* 0CDD5C 800CD15C AFA00000 */  sw    $zero, ($sp)
.L800CD160:
/* 0CDD60 800CD160 8FAF0000 */  lw    $t7, ($sp)
/* 0CDD64 800CD164 8FB90000 */  lw    $t9, ($sp)
/* 0CDD68 800CD168 3C018013 */  lui   $at, %hi(D_8012CD50) #$at, 0x8013
/* 0CDD6C 800CD16C 000FC080 */  sll   $t8, $t7, 2
/* 0CDD70 800CD170 00380821 */  addu  $at, $at, $t8
/* 0CDD74 800CD174 AC20CD50 */  sw    $zero, %lo(D_8012CD50)($at)
/* 0CDD78 800CD178 27280001 */  addiu $t0, $t9, 1
/* 0CDD7C 800CD17C 29010010 */  slti  $at, $t0, 0x10
/* 0CDD80 800CD180 1420FFF7 */  bnez  $at, .L800CD160
/* 0CDD84 800CD184 AFA80000 */   sw    $t0, ($sp)
/* 0CDD88 800CD188 3C198013 */  lui   $t9, %hi(__osMaxControllers) # $t9, 0x8013
/* 0CDD8C 800CD18C 9339CD91 */  lbu   $t9, %lo(__osMaxControllers)($t9)
/* 0CDD90 800CD190 24090001 */  li    $t1, 1
/* 0CDD94 800CD194 3C018013 */  lui   $at, %hi(D_8012CD8C) # $at, 0x8013
/* 0CDD98 800CD198 240A00FF */  li    $t2, 255
/* 0CDD9C 800CD19C 240B0001 */  li    $t3, 1
/* 0CDDA0 800CD1A0 240C0004 */  li    $t4, 4
/* 0CDDA4 800CD1A4 240D0001 */  li    $t5, 1
/* 0CDDA8 800CD1A8 340EFFFF */  li    $t6, 65535
/* 0CDDAC 800CD1AC 240FFFFF */  li    $t7, -1
/* 0CDDB0 800CD1B0 2418FFFF */  li    $t8, -1
/* 0CDDB4 800CD1B4 AC29CD8C */  sw    $t1, %lo(D_8012CD8C)($at)
/* 0CDDB8 800CD1B8 A3AA0004 */  sb    $t2, 4($sp)
/* 0CDDBC 800CD1BC A3AB0005 */  sb    $t3, 5($sp)
/* 0CDDC0 800CD1C0 A3AC0006 */  sb    $t4, 6($sp)
/* 0CDDC4 800CD1C4 A3AD0007 */  sb    $t5, 7($sp)
/* 0CDDC8 800CD1C8 A7AE0008 */  sh    $t6, 8($sp)
/* 0CDDCC 800CD1CC A3AF000A */  sb    $t7, 0xa($sp)
/* 0CDDD0 800CD1D0 A3B8000B */  sb    $t8, 0xb($sp)
/* 0CDDD4 800CD1D4 1B200013 */  blez  $t9, .L800CD224
/* 0CDDD8 800CD1D8 AFA00000 */   sw    $zero, ($sp)
.L800CD1DC:
/* 0CDDDC 800CD1DC 27A90004 */  addiu $t1, $sp, 4
/* 0CDDE0 800CD1E0 8D210000 */  lw    $at, ($t1)
/* 0CDDE4 800CD1E4 8FA8000C */  lw    $t0, 0xc($sp)
/* 0CDDE8 800CD1E8 3C188013 */  lui   $t8, %hi(__osMaxControllers) # $t8, 0x8013
/* 0CDDEC 800CD1EC A9010000 */  swl   $at, ($t0)
/* 0CDDF0 800CD1F0 B9010003 */  swr   $at, 3($t0)
/* 0CDDF4 800CD1F4 8D2B0004 */  lw    $t3, 4($t1)
/* 0CDDF8 800CD1F8 A90B0004 */  swl   $t3, 4($t0)
/* 0CDDFC 800CD1FC B90B0007 */  swr   $t3, 7($t0)
/* 0CDE00 800CD200 8FAE0000 */  lw    $t6, ($sp)
/* 0CDE04 800CD204 9318CD91 */  lbu   $t8, %lo(__osMaxControllers)($t8)
/* 0CDE08 800CD208 8FAC000C */  lw    $t4, 0xc($sp)
/* 0CDE0C 800CD20C 25CF0001 */  addiu $t7, $t6, 1
/* 0CDE10 800CD210 01F8082A */  slt   $at, $t7, $t8
/* 0CDE14 800CD214 258D0008 */  addiu $t5, $t4, 8
/* 0CDE18 800CD218 AFAF0000 */  sw    $t7, ($sp)
/* 0CDE1C 800CD21C 1420FFEF */  bnez  $at, .L800CD1DC
/* 0CDE20 800CD220 AFAD000C */   sw    $t5, 0xc($sp)
.L800CD224:
/* 0CDE24 800CD224 8FAA000C */  lw    $t2, 0xc($sp)
/* 0CDE28 800CD228 241900FE */  li    $t9, 254
/* 0CDE2C 800CD22C 27BD0010 */  addiu $sp, $sp, 0x10
/* 0CDE30 800CD230 03E00008 */  jr    $ra
/* 0CDE34 800CD234 A1590000 */   sb    $t9, ($t2)

/* 0CDE38 800CD238 00000000 */  nop   
/* 0CDE3C 800CD23C 00000000 */  nop   

