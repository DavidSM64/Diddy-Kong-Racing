glabel func_800C422C
/* 0C4E2C 800C422C 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C4E30 800C4230 3C0E8013 */  lui   $t6, %hi(gNumberOfFonts) # $t6, 0x8013
/* 0C4E34 800C4234 8DCEA7E0 */  lw    $t6, %lo(gNumberOfFonts)($t6)
/* 0C4E38 800C4238 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0C4E3C 800C423C 008E082A */  slt   $at, $a0, $t6
/* 0C4E40 800C4240 AFB30020 */  sw    $s3, 0x20($sp)
/* 0C4E44 800C4244 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0C4E48 800C4248 AFB10018 */  sw    $s1, 0x18($sp)
/* 0C4E4C 800C424C 10200020 */  beqz  $at, .L800C42D0
/* 0C4E50 800C4250 AFB00014 */   sw    $s0, 0x14($sp)
/* 0C4E54 800C4254 3C188013 */  lui   $t8, %hi(gFonts) # $t8, 0x8013
/* 0C4E58 800C4258 8F18A7E4 */  lw    $t8, %lo(gFonts)($t8)
/* 0C4E5C 800C425C 00047A80 */  sll   $t7, $a0, 0xa
/* 0C4E60 800C4260 01F89021 */  addu  $s2, $t7, $t8
/* 0C4E64 800C4264 92420028 */  lbu   $v0, 0x28($s2)
/* 0C4E68 800C4268 00000000 */  nop   
/* 0C4E6C 800C426C 18400018 */  blez  $v0, .L800C42D0
/* 0C4E70 800C4270 2459FFFF */   addiu $t9, $v0, -1
/* 0C4E74 800C4274 332800FF */  andi  $t0, $t9, 0xff
/* 0C4E78 800C4278 15000015 */  bnez  $t0, .L800C42D0
/* 0C4E7C 800C427C A2590028 */   sb    $t9, 0x28($s2)
/* 0C4E80 800C4280 86490040 */  lh    $t1, 0x40($s2)
/* 0C4E84 800C4284 2413FFFF */  li    $s3, -1
/* 0C4E88 800C4288 12690011 */  beq   $s3, $t1, .L800C42D0
/* 0C4E8C 800C428C 00008825 */   move  $s1, $zero
/* 0C4E90 800C4290 00005080 */  sll   $t2, $zero, 2
/* 0C4E94 800C4294 024A8021 */  addu  $s0, $s2, $t2
.L800C4298:
/* 0C4E98 800C4298 8E040080 */  lw    $a0, 0x80($s0)
/* 0C4E9C 800C429C 0C01ECAF */  jal   free_texture
/* 0C4EA0 800C42A0 00000000 */   nop   
/* 0C4EA4 800C42A4 26310001 */  addiu $s1, $s1, 1
/* 0C4EA8 800C42A8 2A210020 */  slti  $at, $s1, 0x20
/* 0C4EAC 800C42AC AE000080 */  sw    $zero, 0x80($s0)
/* 0C4EB0 800C42B0 10200007 */  beqz  $at, .L800C42D0
/* 0C4EB4 800C42B4 26100004 */   addiu $s0, $s0, 4
/* 0C4EB8 800C42B8 00115840 */  sll   $t3, $s1, 1
/* 0C4EBC 800C42BC 024B6021 */  addu  $t4, $s2, $t3
/* 0C4EC0 800C42C0 858D0040 */  lh    $t5, 0x40($t4)
/* 0C4EC4 800C42C4 00000000 */  nop   
/* 0C4EC8 800C42C8 166DFFF3 */  bne   $s3, $t5, .L800C4298
/* 0C4ECC 800C42CC 00000000 */   nop   
.L800C42D0:
/* 0C4ED0 800C42D0 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0C4ED4 800C42D4 8FB00014 */  lw    $s0, 0x14($sp)
/* 0C4ED8 800C42D8 8FB10018 */  lw    $s1, 0x18($sp)
/* 0C4EDC 800C42DC 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0C4EE0 800C42E0 8FB30020 */  lw    $s3, 0x20($sp)
/* 0C4EE4 800C42E4 03E00008 */  jr    $ra
/* 0C4EE8 800C42E8 27BD0028 */   addiu $sp, $sp, 0x28

