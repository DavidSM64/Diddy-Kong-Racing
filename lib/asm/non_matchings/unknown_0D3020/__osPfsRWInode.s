glabel __osPfsRWInode
/* 0D68BC 800D5CBC 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0D68C0 800D5CC0 AFA40038 */  sw    $a0, 0x38($sp)
/* 0D68C4 800D5CC4 8FAE0038 */  lw    $t6, 0x38($sp)
/* 0D68C8 800D5CC8 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D68CC 800D5CCC AFA5003C */  sw    $a1, 0x3c($sp)
/* 0D68D0 800D5CD0 AFA60040 */  sw    $a2, 0x40($sp)
/* 0D68D4 800D5CD4 AFA70044 */  sw    $a3, 0x44($sp)
/* 0D68D8 800D5CD8 91CF0065 */  lbu   $t7, 0x65($t6)
/* 0D68DC 800D5CDC 11E0000A */  beqz  $t7, .L800D5D08
/* 0D68E0 800D5CE0 00000000 */   nop   
/* 0D68E4 800D5CE4 A1C00065 */  sb    $zero, 0x65($t6)
/* 0D68E8 800D5CE8 0C0357F7 */  jal   __osPfsSelectBank
/* 0D68EC 800D5CEC 8FA40038 */   lw    $a0, 0x38($sp)
/* 0D68F0 800D5CF0 AFA2002C */  sw    $v0, 0x2c($sp)
/* 0D68F4 800D5CF4 8FB8002C */  lw    $t8, 0x2c($sp)
/* 0D68F8 800D5CF8 13000003 */  beqz  $t8, .L800D5D08
/* 0D68FC 800D5CFC 00000000 */   nop   
/* 0D6900 800D5D00 100000B2 */  b     .L800D5FCC
/* 0D6904 800D5D04 03001025 */   move  $v0, $t8
.L800D5D08:
/* 0D6908 800D5D08 93B90047 */  lbu   $t9, 0x47($sp)
/* 0D690C 800D5D0C 1B200004 */  blez  $t9, .L800D5D20
/* 0D6910 800D5D10 00000000 */   nop   
/* 0D6914 800D5D14 24080001 */  li    $t0, 1
/* 0D6918 800D5D18 10000004 */  b     .L800D5D2C
/* 0D691C 800D5D1C AFA80028 */   sw    $t0, 0x28($sp)
.L800D5D20:
/* 0D6920 800D5D20 8FA90038 */  lw    $t1, 0x38($sp)
/* 0D6924 800D5D24 8D2A0060 */  lw    $t2, 0x60($t1)
/* 0D6928 800D5D28 AFAA0028 */  sw    $t2, 0x28($sp)
.L800D5D2C:
/* 0D692C 800D5D2C 93AB0043 */  lbu   $t3, 0x43($sp)
/* 0D6930 800D5D30 24010001 */  li    $at, 1
/* 0D6934 800D5D34 1561000C */  bne   $t3, $at, .L800D5D68
/* 0D6938 800D5D38 00000000 */   nop   
/* 0D693C 800D5D3C 8FAD0028 */  lw    $t5, 0x28($sp)
/* 0D6940 800D5D40 8FAC003C */  lw    $t4, 0x3c($sp)
/* 0D6944 800D5D44 000D2823 */  negu  $a1, $t5
/* 0D6948 800D5D48 00057040 */  sll   $t6, $a1, 1
/* 0D694C 800D5D4C 01C02825 */  move  $a1, $t6
/* 0D6950 800D5D50 000D7840 */  sll   $t7, $t5, 1
/* 0D6954 800D5D54 24A50100 */  addiu $a1, $a1, 0x100
/* 0D6958 800D5D58 0C0354BC */  jal   __osSumcalc
/* 0D695C 800D5D5C 018F2021 */   addu  $a0, $t4, $t7
/* 0D6960 800D5D60 8FB8003C */  lw    $t8, 0x3c($sp)
/* 0D6964 800D5D64 A3020001 */  sb    $v0, 1($t8)
.L800D5D68:
/* 0D6968 800D5D68 AFA00030 */  sw    $zero, 0x30($sp)
.L800D5D6C:
/* 0D696C 800D5D6C 8FA80030 */  lw    $t0, 0x30($sp)
/* 0D6970 800D5D70 8FB9003C */  lw    $t9, 0x3c($sp)
/* 0D6974 800D5D74 93AB0043 */  lbu   $t3, 0x43($sp)
/* 0D6978 800D5D78 00084940 */  sll   $t1, $t0, 5
/* 0D697C 800D5D7C 24010001 */  li    $at, 1
/* 0D6980 800D5D80 03295021 */  addu  $t2, $t9, $t1
/* 0D6984 800D5D84 1561001B */  bne   $t3, $at, .L800D5DF4
/* 0D6988 800D5D88 AFAA0024 */   sw    $t2, 0x24($sp)
/* 0D698C 800D5D8C 8FAC0038 */  lw    $t4, 0x38($sp)
/* 0D6990 800D5D90 93AD0047 */  lbu   $t5, 0x47($sp)
/* 0D6994 800D5D94 01403825 */  move  $a3, $t2
/* 0D6998 800D5D98 8D8F0054 */  lw    $t7, 0x54($t4)
/* 0D699C 800D5D9C 000D70C0 */  sll   $t6, $t5, 3
/* 0D69A0 800D5DA0 8D840004 */  lw    $a0, 4($t4)
/* 0D69A4 800D5DA4 8D850008 */  lw    $a1, 8($t4)
/* 0D69A8 800D5DA8 01EEC021 */  addu  $t8, $t7, $t6
/* 0D69AC 800D5DAC 03083021 */  addu  $a2, $t8, $t0
/* 0D69B0 800D5DB0 0C03363C */  jal   __osContRamWrite
/* 0D69B4 800D5DB4 AFA00010 */   sw    $zero, 0x10($sp)
/* 0D69B8 800D5DB8 8FB90038 */  lw    $t9, 0x38($sp)
/* 0D69BC 800D5DBC 93AB0047 */  lbu   $t3, 0x47($sp)
/* 0D69C0 800D5DC0 AFA2002C */  sw    $v0, 0x2c($sp)
/* 0D69C4 800D5DC4 8F290058 */  lw    $t1, 0x58($t9)
/* 0D69C8 800D5DC8 8FAF0030 */  lw    $t7, 0x30($sp)
/* 0D69CC 800D5DCC 000B60C0 */  sll   $t4, $t3, 3
/* 0D69D0 800D5DD0 8F250008 */  lw    $a1, 8($t9)
/* 0D69D4 800D5DD4 8F240004 */  lw    $a0, 4($t9)
/* 0D69D8 800D5DD8 012C6821 */  addu  $t5, $t1, $t4
/* 0D69DC 800D5DDC AFA00010 */  sw    $zero, 0x10($sp)
/* 0D69E0 800D5DE0 8FA70024 */  lw    $a3, 0x24($sp)
/* 0D69E4 800D5DE4 0C03363C */  jal   __osContRamWrite
/* 0D69E8 800D5DE8 01AF3021 */   addu  $a2, $t5, $t7
/* 0D69EC 800D5DEC 1000000D */  b     .L800D5E24
/* 0D69F0 800D5DF0 AFA2002C */   sw    $v0, 0x2c($sp)
.L800D5DF4:
/* 0D69F4 800D5DF4 8FAE0038 */  lw    $t6, 0x38($sp)
/* 0D69F8 800D5DF8 93A80047 */  lbu   $t0, 0x47($sp)
/* 0D69FC 800D5DFC 8FAB0030 */  lw    $t3, 0x30($sp)
/* 0D6A00 800D5E00 8DD80054 */  lw    $t8, 0x54($t6)
/* 0D6A04 800D5E04 000850C0 */  sll   $t2, $t0, 3
/* 0D6A08 800D5E08 8FA70024 */  lw    $a3, 0x24($sp)
/* 0D6A0C 800D5E0C 030AC821 */  addu  $t9, $t8, $t2
/* 0D6A10 800D5E10 8DC40004 */  lw    $a0, 4($t6)
/* 0D6A14 800D5E14 8DC50008 */  lw    $a1, 8($t6)
/* 0D6A18 800D5E18 0C033728 */  jal   __osContRamRead
/* 0D6A1C 800D5E1C 032B3021 */   addu  $a2, $t9, $t3
/* 0D6A20 800D5E20 AFA2002C */  sw    $v0, 0x2c($sp)
.L800D5E24:
/* 0D6A24 800D5E24 8FA9002C */  lw    $t1, 0x2c($sp)
/* 0D6A28 800D5E28 11200003 */  beqz  $t1, .L800D5E38
/* 0D6A2C 800D5E2C 00000000 */   nop   
/* 0D6A30 800D5E30 10000066 */  b     .L800D5FCC
/* 0D6A34 800D5E34 01201025 */   move  $v0, $t1
.L800D5E38:
/* 0D6A38 800D5E38 8FAC0030 */  lw    $t4, 0x30($sp)
/* 0D6A3C 800D5E3C 258D0001 */  addiu $t5, $t4, 1
/* 0D6A40 800D5E40 29A10008 */  slti  $at, $t5, 8
/* 0D6A44 800D5E44 1420FFC9 */  bnez  $at, .L800D5D6C
/* 0D6A48 800D5E48 AFAD0030 */   sw    $t5, 0x30($sp)
/* 0D6A4C 800D5E4C 93AF0043 */  lbu   $t7, 0x43($sp)
/* 0D6A50 800D5E50 15E0005D */  bnez  $t7, .L800D5FC8
/* 0D6A54 800D5E54 00000000 */   nop   
/* 0D6A58 800D5E58 8FA80028 */  lw    $t0, 0x28($sp)
/* 0D6A5C 800D5E5C 8FAE003C */  lw    $t6, 0x3c($sp)
/* 0D6A60 800D5E60 00082823 */  negu  $a1, $t0
/* 0D6A64 800D5E64 00055040 */  sll   $t2, $a1, 1
/* 0D6A68 800D5E68 01402825 */  move  $a1, $t2
/* 0D6A6C 800D5E6C 0008C040 */  sll   $t8, $t0, 1
/* 0D6A70 800D5E70 24A50100 */  addiu $a1, $a1, 0x100
/* 0D6A74 800D5E74 0C0354BC */  jal   __osSumcalc
/* 0D6A78 800D5E78 01D82021 */   addu  $a0, $t6, $t8
/* 0D6A7C 800D5E7C 8FB9003C */  lw    $t9, 0x3c($sp)
/* 0D6A80 800D5E80 A3A20037 */  sb    $v0, 0x37($sp)
/* 0D6A84 800D5E84 93A90037 */  lbu   $t1, 0x37($sp)
/* 0D6A88 800D5E88 932B0001 */  lbu   $t3, 1($t9)
/* 0D6A8C 800D5E8C 11690037 */  beq   $t3, $t1, .L800D5F6C
/* 0D6A90 800D5E90 00000000 */   nop   
/* 0D6A94 800D5E94 AFA00030 */  sw    $zero, 0x30($sp)
.L800D5E98:
/* 0D6A98 800D5E98 8FAD0030 */  lw    $t5, 0x30($sp)
/* 0D6A9C 800D5E9C 8FAC003C */  lw    $t4, 0x3c($sp)
/* 0D6AA0 800D5EA0 8FB80038 */  lw    $t8, 0x38($sp)
/* 0D6AA4 800D5EA4 000D7940 */  sll   $t7, $t5, 5
/* 0D6AA8 800D5EA8 018F7021 */  addu  $t6, $t4, $t7
/* 0D6AAC 800D5EAC 93AA0047 */  lbu   $t2, 0x47($sp)
/* 0D6AB0 800D5EB0 AFAE0024 */  sw    $t6, 0x24($sp)
/* 0D6AB4 800D5EB4 8F080058 */  lw    $t0, 0x58($t8)
/* 0D6AB8 800D5EB8 000AC8C0 */  sll   $t9, $t2, 3
/* 0D6ABC 800D5EBC 01C03825 */  move  $a3, $t6
/* 0D6AC0 800D5EC0 01195821 */  addu  $t3, $t0, $t9
/* 0D6AC4 800D5EC4 016D3021 */  addu  $a2, $t3, $t5
/* 0D6AC8 800D5EC8 8F050008 */  lw    $a1, 8($t8)
/* 0D6ACC 800D5ECC 0C033728 */  jal   __osContRamRead
/* 0D6AD0 800D5ED0 8F040004 */   lw    $a0, 4($t8)
/* 0D6AD4 800D5ED4 8FA90030 */  lw    $t1, 0x30($sp)
/* 0D6AD8 800D5ED8 AFA2002C */  sw    $v0, 0x2c($sp)
/* 0D6ADC 800D5EDC 252C0001 */  addiu $t4, $t1, 1
/* 0D6AE0 800D5EE0 29810008 */  slti  $at, $t4, 8
/* 0D6AE4 800D5EE4 1420FFEC */  bnez  $at, .L800D5E98
/* 0D6AE8 800D5EE8 AFAC0030 */   sw    $t4, 0x30($sp)
/* 0D6AEC 800D5EEC 8FAF003C */  lw    $t7, 0x3c($sp)
/* 0D6AF0 800D5EF0 93AA0037 */  lbu   $t2, 0x37($sp)
/* 0D6AF4 800D5EF4 91F80001 */  lbu   $t8, 1($t7)
/* 0D6AF8 800D5EF8 130A0003 */  beq   $t8, $t2, .L800D5F08
/* 0D6AFC 800D5EFC 00000000 */   nop   
/* 0D6B00 800D5F00 10000032 */  b     .L800D5FCC
/* 0D6B04 800D5F04 24020003 */   li    $v0, 3
.L800D5F08:
/* 0D6B08 800D5F08 AFA00030 */  sw    $zero, 0x30($sp)
.L800D5F0C:
/* 0D6B0C 800D5F0C 8FB90030 */  lw    $t9, 0x30($sp)
/* 0D6B10 800D5F10 8FA8003C */  lw    $t0, 0x3c($sp)
/* 0D6B14 800D5F14 8FAE0038 */  lw    $t6, 0x38($sp)
/* 0D6B18 800D5F18 00195940 */  sll   $t3, $t9, 5
/* 0D6B1C 800D5F1C 010B6821 */  addu  $t5, $t0, $t3
/* 0D6B20 800D5F20 93AC0047 */  lbu   $t4, 0x47($sp)
/* 0D6B24 800D5F24 AFAD0024 */  sw    $t5, 0x24($sp)
/* 0D6B28 800D5F28 8DC90054 */  lw    $t1, 0x54($t6)
/* 0D6B2C 800D5F2C 000C78C0 */  sll   $t7, $t4, 3
/* 0D6B30 800D5F30 8DC50008 */  lw    $a1, 8($t6)
/* 0D6B34 800D5F34 8DC40004 */  lw    $a0, 4($t6)
/* 0D6B38 800D5F38 012FC021 */  addu  $t8, $t1, $t7
/* 0D6B3C 800D5F3C AFA00010 */  sw    $zero, 0x10($sp)
/* 0D6B40 800D5F40 01A03825 */  move  $a3, $t5
/* 0D6B44 800D5F44 0C03363C */  jal   __osContRamWrite
/* 0D6B48 800D5F48 03193021 */   addu  $a2, $t8, $t9
/* 0D6B4C 800D5F4C 8FAA0030 */  lw    $t2, 0x30($sp)
/* 0D6B50 800D5F50 AFA2002C */  sw    $v0, 0x2c($sp)
/* 0D6B54 800D5F54 25480001 */  addiu $t0, $t2, 1
/* 0D6B58 800D5F58 29010008 */  slti  $at, $t0, 8
/* 0D6B5C 800D5F5C 1420FFEB */  bnez  $at, .L800D5F0C
/* 0D6B60 800D5F60 AFA80030 */   sw    $t0, 0x30($sp)
/* 0D6B64 800D5F64 10000018 */  b     .L800D5FC8
/* 0D6B68 800D5F68 00000000 */   nop   
.L800D5F6C:
/* 0D6B6C 800D5F6C AFA00030 */  sw    $zero, 0x30($sp)
.L800D5F70:
/* 0D6B70 800D5F70 8FAE0030 */  lw    $t6, 0x30($sp)
/* 0D6B74 800D5F74 8FAB003C */  lw    $t3, 0x3c($sp)
/* 0D6B78 800D5F78 8FAF0038 */  lw    $t7, 0x38($sp)
/* 0D6B7C 800D5F7C 000E6140 */  sll   $t4, $t6, 5
/* 0D6B80 800D5F80 016C4821 */  addu  $t1, $t3, $t4
/* 0D6B84 800D5F84 93B90047 */  lbu   $t9, 0x47($sp)
/* 0D6B88 800D5F88 AFA90024 */  sw    $t1, 0x24($sp)
/* 0D6B8C 800D5F8C 8DF80058 */  lw    $t8, 0x58($t7)
/* 0D6B90 800D5F90 001968C0 */  sll   $t5, $t9, 3
/* 0D6B94 800D5F94 8DE50008 */  lw    $a1, 8($t7)
/* 0D6B98 800D5F98 8DE40004 */  lw    $a0, 4($t7)
/* 0D6B9C 800D5F9C 030D5021 */  addu  $t2, $t8, $t5
/* 0D6BA0 800D5FA0 AFA00010 */  sw    $zero, 0x10($sp)
/* 0D6BA4 800D5FA4 01203825 */  move  $a3, $t1
/* 0D6BA8 800D5FA8 0C03363C */  jal   __osContRamWrite
/* 0D6BAC 800D5FAC 014E3021 */   addu  $a2, $t2, $t6
/* 0D6BB0 800D5FB0 8FA80030 */  lw    $t0, 0x30($sp)
/* 0D6BB4 800D5FB4 AFA2002C */  sw    $v0, 0x2c($sp)
/* 0D6BB8 800D5FB8 250B0001 */  addiu $t3, $t0, 1
/* 0D6BBC 800D5FBC 29610008 */  slti  $at, $t3, 8
/* 0D6BC0 800D5FC0 1420FFEB */  bnez  $at, .L800D5F70
/* 0D6BC4 800D5FC4 AFAB0030 */   sw    $t3, 0x30($sp)
.L800D5FC8:
/* 0D6BC8 800D5FC8 00001025 */  move  $v0, $zero
.L800D5FCC:
/* 0D6BCC 800D5FCC 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D6BD0 800D5FD0 27BD0038 */  addiu $sp, $sp, 0x38
/* 0D6BD4 800D5FD4 03E00008 */  jr    $ra
/* 0D6BD8 800D5FD8 00000000 */   nop   

