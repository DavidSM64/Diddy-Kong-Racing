glabel func_800C3048
/* 0C3C48 800C3048 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C3C4C 800C304C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C3C50 800C3050 240EFFFF */  li    $t6, -1
/* 0C3C54 800C3054 3C018013 */  lui   $at, %hi(D_8012A78C) # $at, 0x8013
/* 0C3C58 800C3058 3C0500FF */  lui   $a1, (0x00FF00FF >> 16) # lui $a1, 0xff
/* 0C3C5C 800C305C A42EA78C */  sh    $t6, %lo(D_8012A78C)($at)
/* 0C3C60 800C3060 34A500FF */  ori   $a1, (0x00FF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 0C3C64 800C3064 0C01C327 */  jal   func_80070C9C
/* 0C3C68 800C3068 24040800 */   li    $a0, 2048
/* 0C3C6C 800C306C 3C038013 */  lui   $v1, %hi(D_8012A798) # $v1, 0x8013
/* 0C3C70 800C3070 2463A798 */  addiu $v1, %lo(D_8012A798) # addiu $v1, $v1, -0x5868
/* 0C3C74 800C3074 3C048013 */  lui   $a0, %hi(D_8012A780) # $a0, 0x8013
/* 0C3C78 800C3078 24580080 */  addiu $t8, $v0, 0x80
/* 0C3C7C 800C307C 2484A780 */  addiu $a0, %lo(D_8012A780) # addiu $a0, $a0, -0x5880
/* 0C3C80 800C3080 270803C0 */  addiu $t0, $t8, 0x3c0
/* 0C3C84 800C3084 AC820000 */  sw    $v0, ($a0)
/* 0C3C88 800C3088 AC780000 */  sw    $t8, ($v1)
/* 0C3C8C 800C308C AC680004 */  sw    $t0, 4($v1)
/* 0C3C90 800C3090 3C018013 */  lui   $at, %hi(D_8012A7A4) # $at, 0x8013
/* 0C3C94 800C3094 0C030A7C */  jal   func_800C29F0
/* 0C3C98 800C3098 AC20A7A4 */   sw    $zero, %lo(D_8012A7A4)($at)
/* 0C3C9C 800C309C 0C01DBCC */  jal   func_80076F30
/* 0C3CA0 800C30A0 24040007 */   li    $a0, 7
/* 0C3CA4 800C30A4 00024883 */  sra   $t1, $v0, 2
/* 0C3CA8 800C30A8 252AFFFE */  addiu $t2, $t1, -2
/* 0C3CAC 800C30AC 3C018013 */  lui   $at, %hi(D_8012A790) # $at, 0x8013
/* 0C3CB0 800C30B0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C3CB4 800C30B4 A42AA790 */  sh    $t2, %lo(D_8012A790)($at)
/* 0C3CB8 800C30B8 3C01800E */  lui   $at, %hi(D_800E3670) # $at, 0x800e
/* 0C3CBC 800C30BC 240B0001 */  li    $t3, 1
/* 0C3CC0 800C30C0 A02B3670 */  sb    $t3, %lo(D_800E3670)($at)
/* 0C3CC4 800C30C4 03E00008 */  jr    $ra
/* 0C3CC8 800C30C8 27BD0018 */   addiu $sp, $sp, 0x18

