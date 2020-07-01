glabel func_80001BC0
/* 0027C0 80001BC0 3C028011 */  lui   $v0, %hi(D_80115D05) # $v0, 0x8011
/* 0027C4 80001BC4 240E0001 */  li    $t6, 1
/* 0027C8 80001BC8 3C01800E */  lui   $at, %hi(D_800DC644) # $at, 0x800e
/* 0027CC 80001BCC 24425D05 */  addiu $v0, %lo(D_80115D05) # addiu $v0, $v0, 0x5d05
/* 0027D0 80001BD0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0027D4 80001BD4 00803025 */  move  $a2, $a0
/* 0027D8 80001BD8 A02EC644 */  sb    $t6, %lo(D_800DC644)($at)
/* 0027DC 80001BDC A0460000 */  sb    $a2, ($v0)
/* 0027E0 80001BE0 3C05800E */  lui   $a1, %hi(D_800DC634) # $a1, 0x800e
/* 0027E4 80001BE4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0027E8 80001BE8 AFA40018 */  sw    $a0, 0x18($sp)
/* 0027EC 80001BEC 8CA5C634 */  lw    $a1, %lo(D_800DC634)($a1)
/* 0027F0 80001BF0 0C0008AF */  jal   func_800022BC
/* 0027F4 80001BF4 30C400FF */   andi  $a0, $a2, 0xff
/* 0027F8 80001BF8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0027FC 80001BFC 27BD0018 */  addiu $sp, $sp, 0x18
/* 002800 80001C00 03E00008 */  jr    $ra
/* 002804 80001C04 00000000 */   nop   

