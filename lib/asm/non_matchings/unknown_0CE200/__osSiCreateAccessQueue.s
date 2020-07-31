glabel __osSiCreateAccessQueue
/* 0CE200 800CD600 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CE204 800CD604 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CE208 800CD608 240E0001 */  li    $t6, 1
/* 0CE20C 800CD60C 3C01800E */  lui   $at, %hi(D_800E38D0) # $at, 0x800e
/* 0CE210 800CD610 3C048013 */  lui   $a0, %hi(D_8012CE28) # $a0, 0x8013
/* 0CE214 800CD614 3C058013 */  lui   $a1, %hi(D_8012CE20) # $a1, 0x8013
/* 0CE218 800CD618 AC2E38D0 */  sw    $t6, %lo(D_800E38D0)($at)
/* 0CE21C 800CD61C 24A5CE20 */  addiu $a1, %lo(D_8012CE20) # addiu $a1, $a1, -0x31e0
/* 0CE220 800CD620 2484CE28 */  addiu $a0, %lo(D_8012CE28) # addiu $a0, $a0, -0x31d8
/* 0CE224 800CD624 0C032208 */  jal   osCreateMesgQueue
/* 0CE228 800CD628 24060001 */   li    $a2, 1
/* 0CE22C 800CD62C 3C048013 */  lui   $a0, %hi(D_8012CE28) # $a0, 0x8013
/* 0CE230 800CD630 2484CE28 */  addiu $a0, %lo(D_8012CE28) # addiu $a0, $a0, -0x31d8
/* 0CE234 800CD634 00002825 */  move  $a1, $zero
/* 0CE238 800CD638 0C03238C */  jal   osSendMesg
/* 0CE23C 800CD63C 00003025 */   move  $a2, $zero
/* 0CE240 800CD640 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CE244 800CD644 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CE248 800CD648 03E00008 */  jr    $ra
/* 0CE24C 800CD64C 00000000 */   nop   

