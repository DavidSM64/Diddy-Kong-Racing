glabel __osTimerServicesInit
/* 0D5AC0 800D4EC0 3C018013 */  lui   $at, %hi(__osCurrentTime) # $at, 0x8013
/* 0D5AC4 800D4EC4 240E0000 */  li    $t6, 0
/* 0D5AC8 800D4EC8 240F0000 */  li    $t7, 0
/* 0D5ACC 800D4ECC AC2FD224 */  sw    $t7, %lo(D_8012D224)($at)
/* 0D5AD0 800D4ED0 AC2ED220 */  sw    $t6, %lo(__osCurrentTime)($at)
/* 0D5AD4 800D4ED4 3C018013 */  lui   $at, %hi(__osBaseCounter) # $at, 0x8013
/* 0D5AD8 800D4ED8 3C18800E */  lui   $t8, %hi(D_800E4910) # $t8, 0x800e
/* 0D5ADC 800D4EDC 8F184910 */  lw    $t8, %lo(D_800E4910)($t8)
/* 0D5AE0 800D4EE0 AC20D228 */  sw    $zero, %lo(__osBaseCounter)($at)
/* 0D5AE4 800D4EE4 3C018013 */  lui   $at, %hi(D_8012D22C) # $at, 0x8013
/* 0D5AE8 800D4EE8 AC20D22C */  sw    $zero, %lo(D_8012D22C)($at)
/* 0D5AEC 800D4EEC 3C19800E */  lui   $t9, %hi(D_800E4910) # $t9, 0x800e
/* 0D5AF0 800D4EF0 AF180004 */  sw    $t8, 4($t8)
/* 0D5AF4 800D4EF4 8F394910 */  lw    $t9, %lo(D_800E4910)($t9)
/* 0D5AF8 800D4EF8 3C09800E */  lui   $t1, %hi(D_800E4910) # $t1, 0x800e
/* 0D5AFC 800D4EFC 240A0000 */  li    $t2, 0
/* 0D5B00 800D4F00 8F280004 */  lw    $t0, 4($t9)
/* 0D5B04 800D4F04 240B0000 */  li    $t3, 0
/* 0D5B08 800D4F08 3C0C800E */  lui   $t4, %hi(D_800E4910) # $t4, 0x800e
/* 0D5B0C 800D4F0C AF280000 */  sw    $t0, ($t9)
/* 0D5B10 800D4F10 8D294910 */  lw    $t1, %lo(D_800E4910)($t1)
/* 0D5B14 800D4F14 3C0D800E */  lui   $t5, %hi(D_800E4910) # $t5, 0x800e
/* 0D5B18 800D4F18 3C18800E */  lui   $t8, %hi(D_800E4910) # $t8, 0x800e
/* 0D5B1C 800D4F1C AD2A0010 */  sw    $t2, 0x10($t1)
/* 0D5B20 800D4F20 AD2B0014 */  sw    $t3, 0x14($t1)
/* 0D5B24 800D4F24 8D8C4910 */  lw    $t4, %lo(D_800E4910)($t4)
/* 0D5B28 800D4F28 8D8E0010 */  lw    $t6, 0x10($t4)
/* 0D5B2C 800D4F2C 8D8F0014 */  lw    $t7, 0x14($t4)
/* 0D5B30 800D4F30 AD8E0008 */  sw    $t6, 8($t4)
/* 0D5B34 800D4F34 AD8F000C */  sw    $t7, 0xc($t4)
/* 0D5B38 800D4F38 8DAD4910 */  lw    $t5, %lo(D_800E4910)($t5)
/* 0D5B3C 800D4F3C ADA00018 */  sw    $zero, 0x18($t5)
/* 0D5B40 800D4F40 8F184910 */  lw    $t8, %lo(D_800E4910)($t8)
/* 0D5B44 800D4F44 03E00008 */  jr    $ra
/* 0D5B48 800D4F48 AF00001C */   sw    $zero, 0x1c($t8)

