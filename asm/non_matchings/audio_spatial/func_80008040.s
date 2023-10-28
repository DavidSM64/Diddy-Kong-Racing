glabel func_80008040
/* 008C40 80008040 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 008C44 80008044 AFBF0014 */  sw    $ra, 0x14($sp)
/* 008C48 80008048 3C048012 */  lui   $a0, %hi(D_80119C40) # $a0, 0x8012
/* 008C4C 8000804C 24849C40 */  addiu $a0, %lo(D_80119C40) # addiu $a0, $a0, -0x63c0
/* 008C50 80008050 00002825 */  move  $a1, $zero
/* 008C54 80008054 0C00084A */  jal   func_80002128
/* 008C58 80008058 00003025 */   move  $a2, $zero
/* 008C5C 8000805C 3C0500FF */  lui   $a1, (0x00FFFFFF >> 16) # lui $a1, 0xff
/* 008C60 80008060 34A5FFFF */  ori   $a1, (0x00FFFFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 008C64 80008064 0C01C327 */  jal   allocate_from_main_pool_safe
/* 008C68 80008068 240405A0 */   li    $a0, 1440
/* 008C6C 8000806C 3C068012 */  lui   $a2, %hi(D_80119C48) # $a2, 0x8012
/* 008C70 80008070 24C69C48 */  addiu $a2, %lo(D_80119C48) # addiu $a2, $a2, -0x63b8
/* 008C74 80008074 3C0500FF */  lui   $a1, (0x00FFFFFF >> 16) # lui $a1, 0xff
/* 008C78 80008078 ACC20000 */  sw    $v0, ($a2)
/* 008C7C 8000807C 34A5FFFF */  ori   $a1, (0x00FFFFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 008C80 80008080 0C01C327 */  jal   allocate_from_main_pool_safe
/* 008C84 80008084 240400A0 */   li    $a0, 160
/* 008C88 80008088 3C018012 */  lui   $at, %hi(D_80119C50) # $at, 0x8012
/* 008C8C 8000808C 3C0500FF */  lui   $a1, (0x00FFFFFF >> 16) # lui $a1, 0xff
/* 008C90 80008090 AC229C50 */  sw    $v0, %lo(D_80119C50)($at)
/* 008C94 80008094 34A5FFFF */  ori   $a1, (0x00FFFFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 008C98 80008098 0C01C327 */  jal   allocate_from_main_pool_safe
/* 008C9C 8000809C 240400A0 */   li    $a0, 160
/* 008CA0 800080A0 3C018012 */  lui   $at, %hi(D_80119C44) # $at, 0x8012
/* 008CA4 800080A4 AC229C44 */  sw    $v0, %lo(D_80119C44)($at)
/* 008CA8 800080A8 3C068012 */  lui   $a2, %hi(D_80119C48) # $a2, 0x8012
/* 008CAC 800080AC 3C01800E */  lui   $at, %hi(D_800DC6E0) # $at, 0x800e
/* 008CB0 800080B0 3C028012 */  lui   $v0, %hi(D_8011A6D8) # $v0, 0x8012
/* 008CB4 800080B4 3C038012 */  lui   $v1, %hi(D_80119C58) # $v1, 0x8012
/* 008CB8 800080B8 24C69C48 */  addiu $a2, %lo(D_80119C48) # addiu $a2, $a2, -0x63b8
/* 008CBC 800080BC A420C6E0 */  sh    $zero, %lo(D_800DC6E0)($at)
/* 008CC0 800080C0 24639C58 */  addiu $v1, %lo(D_80119C58) # addiu $v1, $v1, -0x63a8
/* 008CC4 800080C4 2442A6D8 */  addiu $v0, %lo(D_8011A6D8) # addiu $v0, $v0, -0x5928
.L800080C8:
/* 008CC8 800080C8 24630180 */  addiu $v1, $v1, 0x180
/* 008CCC 800080CC 0062082B */  sltu  $at, $v1, $v0
/* 008CD0 800080D0 1420FFFD */  bnez  $at, .L800080C8
/* 008CD4 800080D4 AC60FFF8 */   sw    $zero, -8($v1)
/* 008CD8 800080D8 00001025 */  move  $v0, $zero
/* 008CDC 800080DC 240305A0 */  li    $v1, 1440
.L800080E0:
/* 008CE0 800080E0 8CCE0000 */  lw    $t6, ($a2)
/* 008CE4 800080E4 00000000 */  nop   
/* 008CE8 800080E8 01C27821 */  addu  $t7, $t6, $v0
/* 008CEC 800080EC ADE00018 */  sw    $zero, 0x18($t7)
/* 008CF0 800080F0 8CD80000 */  lw    $t8, ($a2)
/* 008CF4 800080F4 00000000 */  nop   
/* 008CF8 800080F8 0302C821 */  addu  $t9, $t8, $v0
/* 008CFC 800080FC AF20003C */  sw    $zero, 0x3c($t9)
/* 008D00 80008100 8CC80000 */  lw    $t0, ($a2)
/* 008D04 80008104 00000000 */  nop   
/* 008D08 80008108 01024821 */  addu  $t1, $t0, $v0
/* 008D0C 8000810C AD200060 */  sw    $zero, 0x60($t1)
/* 008D10 80008110 8CCA0000 */  lw    $t2, ($a2)
/* 008D14 80008114 00000000 */  nop   
/* 008D18 80008118 01425821 */  addu  $t3, $t2, $v0
/* 008D1C 8000811C 24420090 */  addiu $v0, $v0, 0x90
/* 008D20 80008120 1443FFEF */  bne   $v0, $v1, .L800080E0
/* 008D24 80008124 AD600084 */   sw    $zero, 0x84($t3)
/* 008D28 80008128 0C00205D */  jal   func_80008174
/* 008D2C 8000812C 00000000 */   nop   
/* 008D30 80008130 8FBF0014 */  lw    $ra, 0x14($sp)
/* 008D34 80008134 27BD0018 */  addiu $sp, $sp, 0x18
/* 008D38 80008138 03E00008 */  jr    $ra
/* 008D3C 8000813C 00000000 */   nop   

