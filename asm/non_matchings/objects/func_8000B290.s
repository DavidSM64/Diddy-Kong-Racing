glabel func_8000B290
/* 00BE90 8000B290 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 00BE94 8000B294 AFB00018 */  sw    $s0, 0x18($sp)
/* 00BE98 8000B298 3C10800E */  lui   $s0, %hi(D_800DC754) # $s0, 0x800e
/* 00BE9C 8000B29C 2610C754 */  addiu $s0, %lo(D_800DC754) # addiu $s0, $s0, -0x38ac
/* 00BEA0 8000B2A0 8E040000 */  lw    $a0, ($s0)
/* 00BEA4 8000B2A4 AFBF0024 */  sw    $ra, 0x24($sp)
/* 00BEA8 8000B2A8 AFB20020 */  sw    $s2, 0x20($sp)
/* 00BEAC 8000B2AC 10800009 */  beqz  $a0, .L8000B2D4
/* 00BEB0 8000B2B0 AFB1001C */   sw    $s1, 0x1c($sp)
/* 00BEB4 8000B2B4 0C01C450 */  jal   free_from_memory_pool
/* 00BEB8 8000B2B8 00000000 */   nop   
/* 00BEBC 8000B2BC 3C02800E */  lui   $v0, %hi(D_800DC74C) # $v0, 0x800e
/* 00BEC0 8000B2C0 2442C74C */  addiu $v0, %lo(D_800DC74C) # addiu $v0, $v0, -0x38b4
/* 00BEC4 8000B2C4 AE000000 */  sw    $zero, ($s0)
/* 00BEC8 8000B2C8 AE000004 */  sw    $zero, 4($s0)
/* 00BECC 8000B2CC AC400000 */  sw    $zero, ($v0)
/* 00BED0 8000B2D0 AC400004 */  sw    $zero, 4($v0)
.L8000B2D4:
/* 00BED4 8000B2D4 0C0078A7 */  jal   get_misc_asset
/* 00BED8 8000B2D8 24040014 */   li    $a0, 20
/* 00BEDC 8000B2DC 00008825 */  move  $s1, $zero
/* 00BEE0 8000B2E0 00408025 */  move  $s0, $v0
/* 00BEE4 8000B2E4 24120500 */  li    $s2, 1280
.L8000B2E8:
/* 00BEE8 8000B2E8 8E040078 */  lw    $a0, 0x78($s0)
/* 00BEEC 8000B2EC 00000000 */  nop   
/* 00BEF0 8000B2F0 10800004 */  beqz  $a0, .L8000B304
/* 00BEF4 8000B2F4 00000000 */   nop   
/* 00BEF8 8000B2F8 0C01F32C */  jal   free_sprite
/* 00BEFC 8000B2FC 00000000 */   nop   
/* 00BF00 8000B300 AE000078 */  sw    $zero, 0x78($s0)
.L8000B304:
/* 00BF04 8000B304 8E04007C */  lw    $a0, 0x7c($s0)
/* 00BF08 8000B308 00000000 */  nop   
/* 00BF0C 8000B30C 10800004 */  beqz  $a0, .L8000B320
/* 00BF10 8000B310 00000000 */   nop   
/* 00BF14 8000B314 0C01ECAF */  jal   free_texture
/* 00BF18 8000B318 00000000 */   nop   
/* 00BF1C 8000B31C AE00007C */  sw    $zero, 0x7c($s0)
.L8000B320:
/* 00BF20 8000B320 26310080 */  addiu $s1, $s1, 0x80
/* 00BF24 8000B324 1632FFF0 */  bne   $s1, $s2, .L8000B2E8
/* 00BF28 8000B328 26100080 */   addiu $s0, $s0, 0x80
/* 00BF2C 8000B32C 3C10800E */  lui   $s0, %hi(D_800DC75C) # $s0, 0x800e
/* 00BF30 8000B330 2610C75C */  addiu $s0, %lo(D_800DC75C) # addiu $s0, $s0, -0x38a4
/* 00BF34 8000B334 8E040000 */  lw    $a0, ($s0)
/* 00BF38 8000B338 00000000 */  nop   
/* 00BF3C 8000B33C 10800003 */  beqz  $a0, .L8000B34C
/* 00BF40 8000B340 00000000 */   nop   
/* 00BF44 8000B344 0C003FEE */  jal   gParticlePtrList_addObject
/* 00BF48 8000B348 00000000 */   nop   
.L8000B34C:
/* 00BF4C 8000B34C 3C11800E */  lui   $s1, %hi(D_800DC764) # $s1, 0x800e
/* 00BF50 8000B350 2631C764 */  addiu $s1, %lo(D_800DC764) # addiu $s1, $s1, -0x389c
/* 00BF54 8000B354 8E240000 */  lw    $a0, ($s1)
/* 00BF58 8000B358 AE000000 */  sw    $zero, ($s0)
/* 00BF5C 8000B35C 10800003 */  beqz  $a0, .L8000B36C
/* 00BF60 8000B360 00000000 */   nop   
/* 00BF64 8000B364 0C003FEE */  jal   gParticlePtrList_addObject
/* 00BF68 8000B368 00000000 */   nop   
.L8000B36C:
/* 00BF6C 8000B36C 0C004013 */  jal   gParticlePtrList_flush
/* 00BF70 8000B370 AE200000 */   sw    $zero, ($s1)
/* 00BF74 8000B374 8FBF0024 */  lw    $ra, 0x24($sp)
/* 00BF78 8000B378 8FB00018 */  lw    $s0, 0x18($sp)
/* 00BF7C 8000B37C 8FB1001C */  lw    $s1, 0x1c($sp)
/* 00BF80 8000B380 8FB20020 */  lw    $s2, 0x20($sp)
/* 00BF84 8000B384 03E00008 */  jr    $ra
/* 00BF88 8000B388 27BD0028 */   addiu $sp, $sp, 0x28

