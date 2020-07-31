glabel osVirtualToPhysical
/* 0C98F0 800C8CF0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C98F4 800C8CF4 AFA40018 */  sw    $a0, 0x18($sp)
/* 0C98F8 800C8CF8 8FAE0018 */  lw    $t6, 0x18($sp)
/* 0C98FC 800C8CFC 3C018000 */  lui   $at, 0x8000
/* 0C9900 800C8D00 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C9904 800C8D04 01C1082B */  sltu  $at, $t6, $at
/* 0C9908 800C8D08 14200007 */  bnez  $at, .L800C8D28
/* 0C990C 800C8D0C 3C01A000 */   lui   $at, 0xa000
/* 0C9910 800C8D10 01C1082B */  sltu  $at, $t6, $at
/* 0C9914 800C8D14 10200004 */  beqz  $at, .L800C8D28
/* 0C9918 800C8D18 3C011FFF */   lui   $at, (0x1FFFFFFF >> 16) # lui $at, 0x1fff
/* 0C991C 800C8D1C 3421FFFF */  ori   $at, (0x1FFFFFFF & 0xFFFF) # ori $at, $at, 0xffff
/* 0C9920 800C8D20 1000000E */  b     .L800C8D5C
/* 0C9924 800C8D24 01C11024 */   and   $v0, $t6, $at
.L800C8D28:
/* 0C9928 800C8D28 8FAF0018 */  lw    $t7, 0x18($sp)
/* 0C992C 800C8D2C 3C01A000 */  lui   $at, 0xa000
/* 0C9930 800C8D30 01E1082B */  sltu  $at, $t7, $at
/* 0C9934 800C8D34 14200007 */  bnez  $at, .L800C8D54
/* 0C9938 800C8D38 3C01C000 */   lui   $at, 0xc000
/* 0C993C 800C8D3C 01E1082B */  sltu  $at, $t7, $at
/* 0C9940 800C8D40 10200004 */  beqz  $at, .L800C8D54
/* 0C9944 800C8D44 3C011FFF */   lui   $at, (0x1FFFFFFF >> 16) # lui $at, 0x1fff
/* 0C9948 800C8D48 3421FFFF */  ori   $at, (0x1FFFFFFF & 0xFFFF) # ori $at, $at, 0xffff
/* 0C994C 800C8D4C 10000003 */  b     .L800C8D5C
/* 0C9950 800C8D50 01E11024 */   and   $v0, $t7, $at
.L800C8D54:
/* 0C9954 800C8D54 0C034D6C */  jal   __osProbeTLB
/* 0C9958 800C8D58 8FA40018 */   lw    $a0, 0x18($sp)
.L800C8D5C:
/* 0C995C 800C8D5C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C9960 800C8D60 27BD0018 */  addiu $sp, $sp, 0x18
/* 0C9964 800C8D64 03E00008 */  jr    $ra
/* 0C9968 800C8D68 00000000 */   nop   

/* 0C996C 800C8D6C 00000000 */  nop   

