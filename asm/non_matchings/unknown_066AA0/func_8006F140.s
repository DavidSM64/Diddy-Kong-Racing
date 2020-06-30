glabel func_8006F140
/* 06FD40 8006F140 3C02800E */  lui   $v0, %hi(D_800DD394) # $v0, 0x800e
/* 06FD44 8006F144 2442D394 */  addiu $v0, %lo(D_800DD394) # addiu $v0, $v0, -0x2c6c
/* 06FD48 8006F148 844E0000 */  lh    $t6, ($v0)
/* 06FD4C 8006F14C 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 06FD50 8006F150 AFBF0014 */  sw    $ra, 0x14($sp)
/* 06FD54 8006F154 15C00029 */  bnez  $t6, .L8006F1FC
/* 06FD58 8006F158 00802825 */   move  $a1, $a0
/* 06FD5C 8006F15C 240F0028 */  li    $t7, 40
/* 06FD60 8006F160 A44F0000 */  sh    $t7, ($v0)
/* 06FD64 8006F164 3C018012 */  lui   $at, %hi(D_80123524) # $at, 0x8012
/* 06FD68 8006F168 A0203524 */  sb    $zero, %lo(D_80123524)($at)
/* 06FD6C 8006F16C 3C018012 */  lui   $at, %hi(D_80123526) # $at, 0x8012
/* 06FD70 8006F170 A0203526 */  sb    $zero, %lo(D_80123526)($at)
/* 06FD74 8006F174 24010001 */  li    $at, 1
/* 06FD78 8006F178 14810007 */  bne   $a0, $at, .L8006F198
/* 06FD7C 8006F17C 3C04800E */   lui   $a0, %hi(D_800DD41C) # $a0, 0x800e
/* 06FD80 8006F180 2484D41C */  addiu $a0, %lo(D_800DD41C) # addiu $a0, $a0, -0x2be4
/* 06FD84 8006F184 0C030076 */  jal   func_800C01D8
/* 06FD88 8006F188 AFA50018 */   sw    $a1, 0x18($sp)
/* 06FD8C 8006F18C 3C02800E */  lui   $v0, %hi(D_800DD394) # $v0, 0x800e
/* 06FD90 8006F190 8FA50018 */  lw    $a1, 0x18($sp)
/* 06FD94 8006F194 2442D394 */  addiu $v0, %lo(D_800DD394) # addiu $v0, $v0, -0x2c6c
.L8006F198:
/* 06FD98 8006F198 24010003 */  li    $at, 3
/* 06FD9C 8006F19C 14A10009 */  bne   $a1, $at, .L8006F1C4
/* 06FDA0 8006F1A0 2418011A */   li    $t8, 282
/* 06FDA4 8006F1A4 3C04800E */  lui   $a0, %hi(D_800DD424) # $a0, 0x800e
/* 06FDA8 8006F1A8 A4580000 */  sh    $t8, ($v0)
/* 06FDAC 8006F1AC 2484D424 */  addiu $a0, %lo(D_800DD424) # addiu $a0, $a0, -0x2bdc
/* 06FDB0 8006F1B0 0C030076 */  jal   func_800C01D8
/* 06FDB4 8006F1B4 AFA50018 */   sw    $a1, 0x18($sp)
/* 06FDB8 8006F1B8 3C02800E */  lui   $v0, %hi(D_800DD394) # $v0, 0x800e
/* 06FDBC 8006F1BC 8FA50018 */  lw    $a1, 0x18($sp)
/* 06FDC0 8006F1C0 2442D394 */  addiu $v0, %lo(D_800DD394) # addiu $v0, $v0, -0x2c6c
.L8006F1C4:
/* 06FDC4 8006F1C4 24010004 */  li    $at, 4
/* 06FDC8 8006F1C8 14A10009 */  bne   $a1, $at, .L8006F1F0
/* 06FDCC 8006F1CC 24190168 */   li    $t9, 360
/* 06FDD0 8006F1D0 3C04800E */  lui   $a0, %hi(D_800DD424) # $a0, 0x800e
/* 06FDD4 8006F1D4 A4590000 */  sh    $t9, ($v0)
/* 06FDD8 8006F1D8 2484D424 */  addiu $a0, %lo(D_800DD424) # addiu $a0, $a0, -0x2bdc
/* 06FDDC 8006F1DC 0C030076 */  jal   func_800C01D8
/* 06FDE0 8006F1E0 AFA50018 */   sw    $a1, 0x18($sp)
/* 06FDE4 8006F1E4 3C02800E */  lui   $v0, %hi(D_800DD394) # $v0, 0x800e
/* 06FDE8 8006F1E8 8FA50018 */  lw    $a1, 0x18($sp)
/* 06FDEC 8006F1EC 2442D394 */  addiu $v0, %lo(D_800DD394) # addiu $v0, $v0, -0x2c6c
.L8006F1F0:
/* 06FDF0 8006F1F0 14A00002 */  bnez  $a1, .L8006F1FC
/* 06FDF4 8006F1F4 24080002 */   li    $t0, 2
/* 06FDF8 8006F1F8 A4480000 */  sh    $t0, ($v0)
.L8006F1FC:
/* 06FDFC 8006F1FC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 06FE00 8006F200 27BD0018 */  addiu $sp, $sp, 0x18
/* 06FE04 8006F204 03E00008 */  jr    $ra
/* 06FE08 8006F208 00000000 */   nop   

/* 06FE0C 8006F20C 3C0E800E */  lui   $t6, %hi(D_800DD394) # $t6, 0x800e
/* 06FE10 8006F210 85CED394 */  lh    $t6, %lo(D_800DD394)($t6)
/* 06FE14 8006F214 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 06FE18 8006F218 15C0000A */  bnez  $t6, .L8006F244
/* 06FE1C 8006F21C AFBF0014 */   sw    $ra, 0x14($sp)
/* 06FE20 8006F220 3C04800E */  lui   $a0, %hi(D_800DD41C) # $a0, 0x800e
/* 06FE24 8006F224 0C030076 */  jal   func_800C01D8
/* 06FE28 8006F228 2484D41C */   addiu $a0, %lo(D_800DD41C) # addiu $a0, $a0, -0x2be4
/* 06FE2C 8006F22C 240F0028 */  li    $t7, 40
/* 06FE30 8006F230 3C01800E */  lui   $at, %hi(D_800DD394) # $at, 0x800e
/* 06FE34 8006F234 A42FD394 */  sh    $t7, %lo(D_800DD394)($at)
/* 06FE38 8006F238 3C018012 */  lui   $at, %hi(D_80123524) # $at, 0x8012
/* 06FE3C 8006F23C 24180001 */  li    $t8, 1
/* 06FE40 8006F240 A0383524 */  sb    $t8, %lo(D_80123524)($at)
.L8006F244:
/* 06FE44 8006F244 8FBF0014 */  lw    $ra, 0x14($sp)
/* 06FE48 8006F248 27BD0018 */  addiu $sp, $sp, 0x18
/* 06FE4C 8006F24C 03E00008 */  jr    $ra
/* 06FE50 8006F250 00000000 */   nop   

