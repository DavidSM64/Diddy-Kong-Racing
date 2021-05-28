glabel func_8007AB9C
/* 07B79C 8007AB9C 3C058012 */  lui   $a1, %hi(D_801262C8) # $a1, 0x8012
/* 07B7A0 8007ABA0 24A562C8 */  addiu $a1, %lo(D_801262C8) # addiu $a1, $a1, 0x62c8
/* 07B7A4 8007ABA4 8CA20000 */  lw    $v0, ($a1)
/* 07B7A8 8007ABA8 3C048012 */  lui   $a0, %hi(D_801262C0) # $a0, 0x8012
/* 07B7AC 8007ABAC 248462C0 */  addiu $a0, %lo(D_801262C0) # addiu $a0, $a0, 0x62c0
/* 07B7B0 8007ABB0 00027080 */  sll   $t6, $v0, 2
/* 07B7B4 8007ABB4 008E7821 */  addu  $t7, $a0, $t6
/* 07B7B8 8007ABB8 8DF80000 */  lw    $t8, ($t7)
/* 07B7BC 8007ABBC 3C018012 */  lui   $at, %hi(D_801262D8) # $at, 0x8012
/* 07B7C0 8007ABC0 3C03800E */  lui   $v1, %hi(D_800DE770) # $v1, 0x800e
/* 07B7C4 8007ABC4 8C63E770 */  lw    $v1, %lo(D_800DE770)($v1)
/* 07B7C8 8007ABC8 AC3862D8 */  sw    $t8, %lo(D_801262D8)($at)
/* 07B7CC 8007ABCC 3C018012 */  lui   $at, %hi(D_801262E0) # $at, 0x8012
/* 07B7D0 8007ABD0 38590001 */  xori  $t9, $v0, 1
/* 07B7D4 8007ABD4 00194880 */  sll   $t1, $t9, 2
/* 07B7D8 8007ABD8 AC2362E0 */  sw    $v1, %lo(D_801262E0)($at)
/* 07B7DC 8007ABDC 00895021 */  addu  $t2, $a0, $t1
/* 07B7E0 8007ABE0 8D4B0000 */  lw    $t3, ($t2)
/* 07B7E4 8007ABE4 ACB90000 */  sw    $t9, ($a1)
/* 07B7E8 8007ABE8 3C018012 */  lui   $at, %hi(D_801262D4) # $at, 0x8012
/* 07B7EC 8007ABEC AC2B62D4 */  sw    $t3, %lo(D_801262D4)($at)
/* 07B7F0 8007ABF0 3C018012 */  lui   $at, %hi(D_801262DC) # $at, 0x8012
/* 07B7F4 8007ABF4 03E00008 */  jr    $ra
/* 07B7F8 8007ABF8 AC2362DC */   sw    $v1, %lo(D_801262DC)($at)

