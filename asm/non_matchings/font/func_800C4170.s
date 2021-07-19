glabel func_800C4170
/* 0C4D70 800C4170 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C4D74 800C4174 3C0E8013 */  lui   $t6, %hi(gNumberOfFonts) # $t6, 0x8013
/* 0C4D78 800C4178 8DCEA7E0 */  lw    $t6, %lo(gNumberOfFonts)($t6)
/* 0C4D7C 800C417C AFBF0024 */  sw    $ra, 0x24($sp)
/* 0C4D80 800C4180 008E082A */  slt   $at, $a0, $t6
/* 0C4D84 800C4184 AFB30020 */  sw    $s3, 0x20($sp)
/* 0C4D88 800C4188 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0C4D8C 800C418C AFB10018 */  sw    $s1, 0x18($sp)
/* 0C4D90 800C4190 1020001F */  beqz  $at, .L800C4210
/* 0C4D94 800C4194 AFB00014 */   sw    $s0, 0x14($sp)
/* 0C4D98 800C4198 3C188013 */  lui   $t8, %hi(gFonts) # $t8, 0x8013
/* 0C4D9C 800C419C 8F18A7E4 */  lw    $t8, %lo(gFonts)($t8)
/* 0C4DA0 800C41A0 00047A80 */  sll   $t7, $a0, 0xa
/* 0C4DA4 800C41A4 01F81021 */  addu  $v0, $t7, $t8
/* 0C4DA8 800C41A8 90590028 */  lbu   $t9, 0x28($v0)
/* 0C4DAC 800C41AC 24010001 */  li    $at, 1
/* 0C4DB0 800C41B0 27280001 */  addiu $t0, $t9, 1
/* 0C4DB4 800C41B4 310900FF */  andi  $t1, $t0, 0xff
/* 0C4DB8 800C41B8 15210015 */  bne   $t1, $at, .L800C4210
/* 0C4DBC 800C41BC A0480028 */   sb    $t0, 0x28($v0)
/* 0C4DC0 800C41C0 844A0040 */  lh    $t2, 0x40($v0)
/* 0C4DC4 800C41C4 2413FFFF */  li    $s3, -1
/* 0C4DC8 800C41C8 126A0011 */  beq   $s3, $t2, .L800C4210
/* 0C4DCC 800C41CC 00008040 */   sll   $s0, $zero, 1
/* 0C4DD0 800C41D0 00508821 */  addu  $s1, $v0, $s0
/* 0C4DD4 800C41D4 00005880 */  sll   $t3, $zero, 2
/* 0C4DD8 800C41D8 86240040 */  lh    $a0, 0x40($s1)
/* 0C4DDC 800C41DC 004B9021 */  addu  $s2, $v0, $t3
.L800C41E0:
/* 0C4DE0 800C41E0 0C01EB9D */  jal   load_texture
/* 0C4DE4 800C41E4 00000000 */   nop   
/* 0C4DE8 800C41E8 26100002 */  addiu $s0, $s0, 2
/* 0C4DEC 800C41EC 2A010040 */  slti  $at, $s0, 0x40
/* 0C4DF0 800C41F0 AE420080 */  sw    $v0, 0x80($s2)
/* 0C4DF4 800C41F4 26310002 */  addiu $s1, $s1, 2
/* 0C4DF8 800C41F8 10200005 */  beqz  $at, .L800C4210
/* 0C4DFC 800C41FC 26520004 */   addiu $s2, $s2, 4
/* 0C4E00 800C4200 86240040 */  lh    $a0, 0x40($s1)
/* 0C4E04 800C4204 00000000 */  nop   
/* 0C4E08 800C4208 1664FFF5 */  bne   $s3, $a0, .L800C41E0
/* 0C4E0C 800C420C 00000000 */   nop   
.L800C4210:
/* 0C4E10 800C4210 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0C4E14 800C4214 8FB00014 */  lw    $s0, 0x14($sp)
/* 0C4E18 800C4218 8FB10018 */  lw    $s1, 0x18($sp)
/* 0C4E1C 800C421C 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0C4E20 800C4220 8FB30020 */  lw    $s3, 0x20($sp)
/* 0C4E24 800C4224 03E00008 */  jr    $ra
/* 0C4E28 800C4228 27BD0028 */   addiu $sp, $sp, 0x28

