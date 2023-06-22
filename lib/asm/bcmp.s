/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CE050 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel bcmp /* Official name: _bcmp */
/* 0CEC50 800CE050 28C10010 */  slti  $at, $a2, 0x10
/* 0CEC54 800CE054 14200037 */  bnez  $at, .L800CE134
/* 0CEC58 800CE058 00851026 */   xor   $v0, $a0, $a1
/* 0CEC5C 800CE05C 30420003 */  andi  $v0, $v0, 3
/* 0CEC60 800CE060 14400019 */  bnez  $v0, .L800CE0C8
/* 0CEC64 800CE064 0004C023 */   negu  $t8, $a0
/* 0CEC68 800CE068 33180003 */  andi  $t8, $t8, 3
/* 0CEC6C 800CE06C 13000007 */  beqz  $t8, .L800CE08C
/* 0CEC70 800CE070 00D83023 */   subu  $a2, $a2, $t8
/* 0CEC74 800CE074 00601025 */  move  $v0, $v1
/* 0CEC78 800CE078 88820000 */  lwl   $v0, ($a0)
/* 0CEC7C 800CE07C 88A30000 */  lwl   $v1, ($a1)
/* 0CEC80 800CE080 00982021 */  addu  $a0, $a0, $t8
/* 0CEC84 800CE084 00B82821 */  addu  $a1, $a1, $t8
/* 0CEC88 800CE088 14430036 */  bne   $v0, $v1, .L800CE164
.L800CE08C:
/* 0CEC8C 800CE08C 2401FFFC */   li    $at, -4
/* 0CEC90 800CE090 00C13824 */  and   $a3, $a2, $at
/* 0CEC94 800CE094 10E00027 */  beqz  $a3, .L800CE134
/* 0CEC98 800CE098 00C73023 */   subu  $a2, $a2, $a3
/* 0CEC9C 800CE09C 00E43821 */  addu  $a3, $a3, $a0
/* 0CECA0 800CE0A0 8C820000 */  lw    $v0, ($a0)
.L800CE0A4:
/* 0CECA4 800CE0A4 8CA30000 */  lw    $v1, ($a1)
/* 0CECA8 800CE0A8 24840004 */  addiu $a0, $a0, 4
/* 0CECAC 800CE0AC 24A50004 */  addiu $a1, $a1, 4
/* 0CECB0 800CE0B0 1443002C */  bne   $v0, $v1, .L800CE164
/* 0CECB4 800CE0B4 00000000 */   nop
/* 0CECB8 800CE0B8 5487FFFA */  bnel  $a0, $a3, .L800CE0A4
/* 0CECBC 800CE0BC 8C820000 */   lw    $v0, ($a0)
/* 0CECC0 800CE0C0 1000001C */  b     .L800CE134
/* 0CECC4 800CE0C4 00000000 */   nop
.L800CE0C8:
/* 0CECC8 800CE0C8 00053823 */  negu  $a3, $a1
/* 0CECCC 800CE0CC 30E70003 */  andi  $a3, $a3, 3
/* 0CECD0 800CE0D0 10E0000A */  beqz  $a3, .L800CE0FC
/* 0CECD4 800CE0D4 00C73023 */   subu  $a2, $a2, $a3
/* 0CECD8 800CE0D8 00E43821 */  addu  $a3, $a3, $a0
/* 0CECDC 800CE0DC 90820000 */  lbu   $v0, ($a0)
.L800CE0E0:
/* 0CECE0 800CE0E0 90A30000 */  lbu   $v1, ($a1)
/* 0CECE4 800CE0E4 24840001 */  addiu $a0, $a0, 1
/* 0CECE8 800CE0E8 24A50001 */  addiu $a1, $a1, 1
/* 0CECEC 800CE0EC 1443001D */  bne   $v0, $v1, .L800CE164
/* 0CECF0 800CE0F0 00000000 */   nop
/* 0CECF4 800CE0F4 5487FFFA */  bnel  $a0, $a3, .L800CE0E0
/* 0CECF8 800CE0F8 90820000 */   lbu   $v0, ($a0)
.L800CE0FC:
/* 0CECFC 800CE0FC 2401FFFC */  li    $at, -4
/* 0CED00 800CE100 00C13824 */  and   $a3, $a2, $at
/* 0CED04 800CE104 10E0000B */  beqz  $a3, .L800CE134
/* 0CED08 800CE108 00C73023 */   subu  $a2, $a2, $a3
/* 0CED0C 800CE10C 00E43821 */  addu  $a3, $a3, $a0
/* 0CED10 800CE110 88820000 */  lwl   $v0, ($a0)
.L800CE114:
/* 0CED14 800CE114 8CA30000 */  lw    $v1, ($a1)
/* 0CED18 800CE118 98820003 */  lwr   $v0, 3($a0)
/* 0CED1C 800CE11C 24840004 */  addiu $a0, $a0, 4
/* 0CED20 800CE120 24A50004 */  addiu $a1, $a1, 4
/* 0CED24 800CE124 1443000F */  bne   $v0, $v1, .L800CE164
/* 0CED28 800CE128 00000000 */   nop
/* 0CED2C 800CE12C 5487FFF9 */  bnel  $a0, $a3, .L800CE114
/* 0CED30 800CE130 88820000 */   lwl   $v0, ($a0)
.L800CE134:
/* 0CED34 800CE134 18C00009 */  blez  $a2, .L800CE15C
/* 0CED38 800CE138 00C43821 */   addu  $a3, $a2, $a0
/* 0CED3C 800CE13C 90820000 */  lbu   $v0, ($a0)
.L800CE140:
/* 0CED40 800CE140 90A30000 */  lbu   $v1, ($a1)
/* 0CED44 800CE144 24840001 */  addiu $a0, $a0, 1
/* 0CED48 800CE148 24A50001 */  addiu $a1, $a1, 1
/* 0CED4C 800CE14C 14430005 */  bne   $v0, $v1, .L800CE164
/* 0CED50 800CE150 00000000 */   nop
/* 0CED54 800CE154 5487FFFA */  bnel  $a0, $a3, .L800CE140
/* 0CED58 800CE158 90820000 */   lbu   $v0, ($a0)
.L800CE15C:
/* 0CED5C 800CE15C 03E00008 */  jr    $ra
/* 0CED60 800CE160 00001025 */   move  $v0, $zero

.L800CE164:
/* 0CED64 800CE164 03E00008 */  jr    $ra
/* 0CED68 800CE168 24020001 */   li    $v0, 1

/* 0CED6C 800CE16C 00000000 */  nop

