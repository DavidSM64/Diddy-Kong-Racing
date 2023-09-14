glabel func_800A003C
/* 0A0C3C 800A003C 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0A0C40 800A0040 3C028012 */  lui   $v0, %hi(gAssetHudElementIdsCount) # $v0, 0x8012
/* 0A0C44 800A0044 8C426CF8 */  lw    $v0, %lo(gAssetHudElementIdsCount)($v0)
/* 0A0C48 800A0048 AFB00018 */  sw    $s0, 0x18($sp)
/* 0A0C4C 800A004C AFBF002C */  sw    $ra, 0x2c($sp)
/* 0A0C50 800A0050 AFB40028 */  sw    $s4, 0x28($sp)
/* 0A0C54 800A0054 AFB30024 */  sw    $s3, 0x24($sp)
/* 0A0C58 800A0058 AFB20020 */  sw    $s2, 0x20($sp)
/* 0A0C5C 800A005C AFB1001C */  sw    $s1, 0x1c($sp)
/* 0A0C60 800A0060 18400032 */  blez  $v0, .L800A012C
/* 0A0C64 800A0064 00008025 */   move  $s0, $zero
/* 0A0C68 800A0068 3C148012 */  lui   $s4, %hi(gAssetHudElementIds) # $s4, 0x8012
/* 0A0C6C 800A006C 3C128012 */  lui   $s2, %hi(gAssetHudElements) # $s2, 0x8012
/* 0A0C70 800A0070 26526CF4 */  addiu $s2, %lo(gAssetHudElements) # addiu $s2, $s2, 0x6cf4
/* 0A0C74 800A0074 26946CF0 */  addiu $s4, %lo(gAssetHudElementIds) # addiu $s4, $s4, 0x6cf0
/* 0A0C78 800A0078 00008825 */  move  $s1, $zero
/* 0A0C7C 800A007C 3413C000 */  li    $s3, 49152
.L800A0080:
/* 0A0C80 800A0080 8E4E0000 */  lw    $t6, ($s2)
/* 0A0C84 800A0084 00000000 */  nop   
/* 0A0C88 800A0088 01D17821 */  addu  $t7, $t6, $s1
/* 0A0C8C 800A008C 8DE40000 */  lw    $a0, ($t7)
/* 0A0C90 800A0090 00000000 */  nop   
/* 0A0C94 800A0094 10800021 */  beqz  $a0, .L800A011C
/* 0A0C98 800A0098 00000000 */   nop   
/* 0A0C9C 800A009C 8E980000 */  lw    $t8, ($s4)
/* 0A0CA0 800A00A0 0010C840 */  sll   $t9, $s0, 1
/* 0A0CA4 800A00A4 03194021 */  addu  $t0, $t8, $t9
/* 0A0CA8 800A00A8 85020000 */  lh    $v0, ($t0)
/* 0A0CAC 800A00AC 00000000 */  nop   
/* 0A0CB0 800A00B0 3049C000 */  andi  $t1, $v0, 0xc000
/* 0A0CB4 800A00B4 16690005 */  bne   $s3, $t1, .L800A00CC
/* 0A0CB8 800A00B8 304A8000 */   andi  $t2, $v0, 0x8000
/* 0A0CBC 800A00BC 0C01ECAF */  jal   free_texture
/* 0A0CC0 800A00C0 00000000 */   nop   
/* 0A0CC4 800A00C4 10000010 */  b     .L800A0108
/* 0A0CC8 800A00C8 8E4C0000 */   lw    $t4, ($s2)
.L800A00CC:
/* 0A0CCC 800A00CC 11400005 */  beqz  $t2, .L800A00E4
/* 0A0CD0 800A00D0 304B4000 */   andi  $t3, $v0, 0x4000
/* 0A0CD4 800A00D4 0C01F32C */  jal   free_sprite
/* 0A0CD8 800A00D8 00000000 */   nop   
/* 0A0CDC 800A00DC 1000000A */  b     .L800A0108
/* 0A0CE0 800A00E0 8E4C0000 */   lw    $t4, ($s2)
.L800A00E4:
/* 0A0CE4 800A00E4 11600005 */  beqz  $t3, .L800A00FC
/* 0A0CE8 800A00E8 00000000 */   nop   
/* 0A0CEC 800A00EC 0C003FEE */  jal   gParticlePtrList_addObject
/* 0A0CF0 800A00F0 00000000 */   nop   
/* 0A0CF4 800A00F4 10000004 */  b     .L800A0108
/* 0A0CF8 800A00F8 8E4C0000 */   lw    $t4, ($s2)
.L800A00FC:
/* 0A0CFC 800A00FC 0C017FD0 */  jal   func_8005FF40
/* 0A0D00 800A0100 00000000 */   nop   
/* 0A0D04 800A0104 8E4C0000 */  lw    $t4, ($s2)
.L800A0108:
/* 0A0D08 800A0108 3C028012 */  lui   $v0, %hi(gAssetHudElementIdsCount) # $v0, 0x8012
/* 0A0D0C 800A010C 01916821 */  addu  $t5, $t4, $s1
/* 0A0D10 800A0110 ADA00000 */  sw    $zero, ($t5)
/* 0A0D14 800A0114 8C426CF8 */  lw    $v0, %lo(gAssetHudElementIdsCount)($v0)
/* 0A0D18 800A0118 00000000 */  nop   
.L800A011C:
/* 0A0D1C 800A011C 26100001 */  addiu $s0, $s0, 1
/* 0A0D20 800A0120 0202082A */  slt   $at, $s0, $v0
/* 0A0D24 800A0124 1420FFD6 */  bnez  $at, .L800A0080
/* 0A0D28 800A0128 26310004 */   addiu $s1, $s1, 4
.L800A012C:
/* 0A0D2C 800A012C 3C048012 */  lui   $a0, %hi(D_80126CE0) # $a0, 0x8012
/* 0A0D30 800A0130 3C128012 */  lui   $s2, %hi(gAssetHudElements) # $s2, 0x8012
/* 0A0D34 800A0134 3C148012 */  lui   $s4, %hi(gAssetHudElementIds) # $s4, 0x8012
/* 0A0D38 800A0138 8C846CE0 */  lw    $a0, %lo(D_80126CE0)($a0)
/* 0A0D3C 800A013C 26946CF0 */  addiu $s4, %lo(gAssetHudElementIds) # addiu $s4, $s4, 0x6cf0
/* 0A0D40 800A0140 0C01C450 */  jal   free_from_memory_pool
/* 0A0D44 800A0144 26526CF4 */   addiu $s2, %lo(gAssetHudElements) # addiu $s2, $s2, 0x6cf4
/* 0A0D48 800A0148 8E840000 */  lw    $a0, ($s4)
/* 0A0D4C 800A014C 0C01C450 */  jal   free_from_memory_pool
/* 0A0D50 800A0150 00000000 */   nop   
/* 0A0D54 800A0154 3C018012 */  lui   $at, %hi(gAssetHudElementIdsCount) # $at, 0x8012
/* 0A0D58 800A0158 AC206CF8 */  sw    $zero, %lo(gAssetHudElementIdsCount)($at)
/* 0A0D5C 800A015C 8E440000 */  lw    $a0, ($s2)
/* 0A0D60 800A0160 0C01C450 */  jal   free_from_memory_pool
/* 0A0D64 800A0164 00000000 */   nop   
/* 0A0D68 800A0168 0C004013 */  jal   gParticlePtrList_flush
/* 0A0D6C 800A016C 00000000 */   nop   
/* 0A0D70 800A0170 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0A0D74 800A0174 8FB00018 */  lw    $s0, 0x18($sp)
/* 0A0D78 800A0178 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0A0D7C 800A017C 8FB20020 */  lw    $s2, 0x20($sp)
/* 0A0D80 800A0180 8FB30024 */  lw    $s3, 0x24($sp)
/* 0A0D84 800A0184 8FB40028 */  lw    $s4, 0x28($sp)
/* 0A0D88 800A0188 03E00008 */  jr    $ra
/* 0A0D8C 800A018C 27BD0030 */   addiu $sp, $sp, 0x30

