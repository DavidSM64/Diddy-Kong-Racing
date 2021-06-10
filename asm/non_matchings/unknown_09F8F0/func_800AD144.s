glabel func_800AD144
/* 0ADD44 800AD144 3C02800E */  lui   $v0, %hi(D_800E2C60) # $v0, 0x800e
/* 0ADD48 800AD148 24422C60 */  addiu $v0, %lo(D_800E2C60) # addiu $v0, $v0, 0x2c60
/* 0ADD4C 800AD14C AC440000 */  sw    $a0, ($v0)
/* 0ADD50 800AD150 3C01800E */  lui   $at, %hi(D_800E2C64) # $at, 0x800e
/* 0ADD54 800AD154 AC202C64 */  sw    $zero, %lo(D_800E2C64)($at)
/* 0ADD58 800AD158 8C4E0000 */  lw    $t6, ($v0)
/* 0ADD5C 800AD15C 3C01800E */  lui   $at, %hi(D_800E2C68) # $at, 0x800e
/* 0ADD60 800AD160 3C03800E */  lui   $v1, %hi(D_800E2C6C) # $v1, 0x800e
/* 0ADD64 800AD164 AC2E2C68 */  sw    $t6, %lo(D_800E2C68)($at)
/* 0ADD68 800AD168 24632C6C */  addiu $v1, %lo(D_800E2C6C) # addiu $v1, $v1, 0x2c6c
/* 0ADD6C 800AD16C AC650000 */  sw    $a1, ($v1)
/* 0ADD70 800AD170 3C01800E */  lui   $at, %hi(D_800E2C70) # $at, 0x800e
/* 0ADD74 800AD174 AC202C70 */  sw    $zero, %lo(D_800E2C70)($at)
/* 0ADD78 800AD178 8C6F0000 */  lw    $t7, ($v1)
/* 0ADD7C 800AD17C 3C01800E */  lui   $at, %hi(D_800E2C74) # $at, 0x800e
/* 0ADD80 800AD180 AC2F2C74 */  sw    $t7, %lo(D_800E2C74)($at)
/* 0ADD84 800AD184 3C01800E */  lui   $at, %hi(D_800E2C78) # $at, 0x800e
/* 0ADD88 800AD188 AC202C78 */  sw    $zero, %lo(D_800E2C78)($at)
/* 0ADD8C 800AD18C 3C01800E */  lui   $at, %hi(D_800E2C7C) # $at, 0x800e
/* 0ADD90 800AD190 AC202C7C */  sw    $zero, %lo(D_800E2C7C)($at)
/* 0ADD94 800AD194 3C01800E */  lui   $at, %hi(D_800E2C80) # $at, 0x800e
/* 0ADD98 800AD198 AC202C80 */  sw    $zero, %lo(D_800E2C80)($at)
/* 0ADD9C 800AD19C 3C01800E */  lui   $at, %hi(D_800E2C84) # $at, 0x800e
/* 0ADDA0 800AD1A0 AC202C84 */  sw    $zero, %lo(D_800E2C84)($at)
/* 0ADDA4 800AD1A4 3C18800E */  lui   $t8, %hi(D_800E291C) # $t8, 0x800e
/* 0ADDA8 800AD1A8 8F18291C */  lw    $t8, %lo(D_800E291C)($t8)
/* 0ADDAC 800AD1AC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0ADDB0 800AD1B0 3C01800E */  lui   $at, %hi(D_800E2C90) # $at, 0x800e
/* 0ADDB4 800AD1B4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0ADDB8 800AD1B8 AC202C90 */  sw    $zero, %lo(D_800E2C90)($at)
/* 0ADDBC 800AD1BC 8F040004 */  lw    $a0, 4($t8)
/* 0ADDC0 800AD1C0 0C01EB9D */  jal   func_8007AE74
/* 0ADDC4 800AD1C4 00000000 */   nop   
/* 0ADDC8 800AD1C8 3C19800E */  lui   $t9, %hi(D_800E291C) # $t9, 0x800e
/* 0ADDCC 800AD1CC 8F39291C */  lw    $t9, %lo(D_800E291C)($t9)
/* 0ADDD0 800AD1D0 3C01800E */  lui   $at, %hi(D_800E2C2C+12) # $at, 0x800e
/* 0ADDD4 800AD1D4 AC222C38 */  sw    $v0, %lo(D_800E2C2C+12)($at)
/* 0ADDD8 800AD1D8 8F240004 */  lw    $a0, 4($t9)
/* 0ADDDC 800AD1DC 0C01EB9D */  jal   func_8007AE74
/* 0ADDE0 800AD1E0 00000000 */   nop   
/* 0ADDE4 800AD1E4 3C08800E */  lui   $t0, %hi(D_800E291C) # $t0, 0x800e
/* 0ADDE8 800AD1E8 8D08291C */  lw    $t0, %lo(D_800E291C)($t0)
/* 0ADDEC 800AD1EC 3C01800E */  lui   $at, %hi(D_800E2C2C+36) # $at, 0x800e
/* 0ADDF0 800AD1F0 AC222C50 */  sw    $v0, %lo(D_800E2C2C+36)($at)
/* 0ADDF4 800AD1F4 8D04000C */  lw    $a0, 0xc($t0)
/* 0ADDF8 800AD1F8 0C01F04B */  jal   func_8007C12C
/* 0ADDFC 800AD1FC 00002825 */   move  $a1, $zero
/* 0ADE00 800AD200 3C01800E */  lui   $at, %hi(D_800E2C8C) # $at, 0x800e
/* 0ADE04 800AD204 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0ADE08 800AD208 AC222C8C */  sw    $v0, %lo(D_800E2C8C)($at)
/* 0ADE0C 800AD20C 3C01800E */  lui   $at, %hi(D_800E2C5C) # $at, 0x800e
/* 0ADE10 800AD210 24090001 */  li    $t1, 1
/* 0ADE14 800AD214 AC292C5C */  sw    $t1, %lo(D_800E2C5C)($at)
/* 0ADE18 800AD218 03E00008 */  jr    $ra
/* 0ADE1C 800AD21C 27BD0018 */   addiu $sp, $sp, 0x18

