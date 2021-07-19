glabel free_texture
/* 07BEBC 8007B2BC 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 07BEC0 8007B2C0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 07BEC4 8007B2C4 10800027 */  beqz  $a0, .L8007B364
/* 07BEC8 8007B2C8 00803025 */   move  $a2, $a0
/* 07BECC 8007B2CC 908E0005 */  lbu   $t6, 5($a0)
/* 07BED0 8007B2D0 00000000 */  nop   
/* 07BED4 8007B2D4 25CFFFFF */  addiu $t7, $t6, -1
/* 07BED8 8007B2D8 31F800FF */  andi  $t8, $t7, 0xff
/* 07BEDC 8007B2DC 1F000021 */  bgtz  $t8, .L8007B364
/* 07BEE0 8007B2E0 A08F0005 */   sb    $t7, 5($a0)
/* 07BEE4 8007B2E4 3C048012 */  lui   $a0, %hi(gNumberOfLoadedTextures) # $a0, 0x8012
/* 07BEE8 8007B2E8 8C846330 */  lw    $a0, %lo(gNumberOfLoadedTextures)($a0)
/* 07BEEC 8007B2EC 00001025 */  move  $v0, $zero
/* 07BEF0 8007B2F0 1880001C */  blez  $a0, .L8007B364
/* 07BEF4 8007B2F4 3C058012 */   lui   $a1, %hi(gTextureCache) # $a1, 0x8012
/* 07BEF8 8007B2F8 8CA56328 */  lw    $a1, %lo(gTextureCache)($a1)
/* 07BEFC 8007B2FC 00000000 */  nop   
/* 07BF00 8007B300 0002C8C0 */  sll   $t9, $v0, 3
.L8007B304:
/* 07BF04 8007B304 00B94021 */  addu  $t0, $a1, $t9
/* 07BF08 8007B308 8D090004 */  lw    $t1, 4($t0)
/* 07BF0C 8007B30C 00000000 */  nop   
/* 07BF10 8007B310 14C90011 */  bne   $a2, $t1, .L8007B358
/* 07BF14 8007B314 24420001 */   addiu $v0, $v0, 1
/* 07BF18 8007B318 00C02025 */  move  $a0, $a2
/* 07BF1C 8007B31C 0C01C450 */  jal   free_from_memory_pool
/* 07BF20 8007B320 AFB90018 */   sw    $t9, 0x18($sp)
/* 07BF24 8007B324 3C028012 */  lui   $v0, %hi(gTextureCache) # $v0, 0x8012
/* 07BF28 8007B328 24426328 */  addiu $v0, %lo(gTextureCache) # addiu $v0, $v0, 0x6328
/* 07BF2C 8007B32C 8FA30018 */  lw    $v1, 0x18($sp)
/* 07BF30 8007B330 8C4A0000 */  lw    $t2, ($v0)
/* 07BF34 8007B334 2404FFFF */  li    $a0, -1
/* 07BF38 8007B338 01435821 */  addu  $t3, $t2, $v1
/* 07BF3C 8007B33C AD640000 */  sw    $a0, ($t3)
/* 07BF40 8007B340 8C4C0000 */  lw    $t4, ($v0)
/* 07BF44 8007B344 00000000 */  nop   
/* 07BF48 8007B348 01836821 */  addu  $t5, $t4, $v1
/* 07BF4C 8007B34C 10000005 */  b     .L8007B364
/* 07BF50 8007B350 ADA40004 */   sw    $a0, 4($t5)
/* 07BF54 8007B354 24420001 */  addiu $v0, $v0, 1
.L8007B358:
/* 07BF58 8007B358 0044082A */  slt   $at, $v0, $a0
/* 07BF5C 8007B35C 1420FFE9 */  bnez  $at, .L8007B304
/* 07BF60 8007B360 0002C8C0 */   sll   $t9, $v0, 3
.L8007B364:
/* 07BF64 8007B364 8FBF0014 */  lw    $ra, 0x14($sp)
/* 07BF68 8007B368 27BD0028 */  addiu $sp, $sp, 0x28
/* 07BF6C 8007B36C 03E00008 */  jr    $ra
/* 07BF70 8007B370 00000000 */   nop   

