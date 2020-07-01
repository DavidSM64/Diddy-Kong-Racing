glabel func_800C2274
/* 0C2E74 800C2274 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C2E78 800C2278 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C2E7C 800C227C AFA40018 */  sw    $a0, 0x18($sp)
/* 0C2E80 800C2280 AFA5001C */  sw    $a1, 0x1c($sp)
/* 0C2E84 800C2284 0C01ECF4 */  jal   func_8007B3D0
/* 0C2E88 800C2288 AFA60020 */   sw    $a2, 0x20($sp)
/* 0C2E8C 800C228C 3C03800E */  lui   $v1, %hi(D_800E31D0) # $v1, 0x800e
/* 0C2E90 800C2290 8C6331D0 */  lw    $v1, %lo(D_800E31D0)($v1)
/* 0C2E94 800C2294 8FAE0018 */  lw    $t6, 0x18($sp)
/* 0C2E98 800C2298 3C07800E */  lui   $a3, 0x800e
/* 0C2E9C 800C229C 00037880 */  sll   $t7, $v1, 2
/* 0C2EA0 800C22A0 8DC20000 */  lw    $v0, ($t6)
/* 0C2EA4 800C22A4 00EF3821 */  addu  $a3, $a3, $t7
/* 0C2EA8 800C22A8 3C08800E */  lui   $t0, 0x800e
/* 0C2EAC 800C22AC 8CE731C0 */  lw    $a3, 0x31c0($a3)
/* 0C2EB0 800C22B0 010F4021 */  addu  $t0, $t0, $t7
/* 0C2EB4 800C22B4 8D0831C8 */  lw    $t0, 0x31c8($t0)
/* 0C2EB8 800C22B8 3C19800E */  lui   $t9, %hi(D_800E3648) # $t9, 0x800e
/* 0C2EBC 800C22BC 00402025 */  move  $a0, $v0
/* 0C2EC0 800C22C0 27393648 */  addiu $t9, %lo(D_800E3648) # addiu $t9, $t9, 0x3648
/* 0C2EC4 800C22C4 3C180600 */  lui   $t8, 0x600
/* 0C2EC8 800C22C8 AC980000 */  sw    $t8, ($a0)
/* 0C2ECC 800C22CC AC990004 */  sw    $t9, 4($a0)
/* 0C2ED0 800C22D0 3C068000 */  lui   $a2, 0x8000
/* 0C2ED4 800C22D4 00E62021 */  addu  $a0, $a3, $a2
/* 0C2ED8 800C22D8 308B0006 */  andi  $t3, $a0, 6
/* 0C2EDC 800C22DC 356C0088 */  ori   $t4, $t3, 0x88
/* 0C2EE0 800C22E0 318D00FF */  andi  $t5, $t4, 0xff
/* 0C2EE4 800C22E4 24430008 */  addiu $v1, $v0, 8
/* 0C2EE8 800C22E8 3C090400 */  lui   $t1, 0x400
/* 0C2EEC 800C22EC AC640004 */  sw    $a0, 4($v1)
/* 0C2EF0 800C22F0 000D7400 */  sll   $t6, $t5, 0x10
/* 0C2EF4 800C22F4 24E700B4 */  addiu $a3, $a3, 0xb4
/* 0C2EF8 800C22F8 00E62021 */  addu  $a0, $a3, $a2
/* 0C2EFC 800C22FC 01C97825 */  or    $t7, $t6, $t1
/* 0C2F00 800C2300 308B0006 */  andi  $t3, $a0, 6
/* 0C2F04 800C2304 35F8014C */  ori   $t8, $t7, 0x14c
/* 0C2F08 800C2308 24650008 */  addiu $a1, $v1, 8
/* 0C2F0C 800C230C 356C0088 */  ori   $t4, $t3, 0x88
/* 0C2F10 800C2310 3C0A05F0 */  lui   $t2, (0x05F00100 >> 16) # lui $t2, 0x5f0
/* 0C2F14 800C2314 AC780000 */  sw    $t8, ($v1)
/* 0C2F18 800C2318 354A0100 */  ori   $t2, (0x05F00100 & 0xFFFF) # ori $t2, $t2, 0x100
/* 0C2F1C 800C231C 318D00FF */  andi  $t5, $t4, 0xff
/* 0C2F20 800C2320 0106C821 */  addu  $t9, $t0, $a2
/* 0C2F24 800C2324 000D7400 */  sll   $t6, $t5, 0x10
/* 0C2F28 800C2328 ACB90004 */  sw    $t9, 4($a1)
/* 0C2F2C 800C232C ACAA0000 */  sw    $t2, ($a1)
/* 0C2F30 800C2330 24A20008 */  addiu $v0, $a1, 8
/* 0C2F34 800C2334 AC440004 */  sw    $a0, 4($v0)
/* 0C2F38 800C2338 01C97825 */  or    $t7, $t6, $t1
/* 0C2F3C 800C233C 24E700B4 */  addiu $a3, $a3, 0xb4
/* 0C2F40 800C2340 00E62021 */  addu  $a0, $a3, $a2
/* 0C2F44 800C2344 35F8014C */  ori   $t8, $t7, 0x14c
/* 0C2F48 800C2348 24450008 */  addiu $a1, $v0, 8
/* 0C2F4C 800C234C AC580000 */  sw    $t8, ($v0)
/* 0C2F50 800C2350 308B0006 */  andi  $t3, $a0, 6
/* 0C2F54 800C2354 25080100 */  addiu $t0, $t0, 0x100
/* 0C2F58 800C2358 0106C821 */  addu  $t9, $t0, $a2
/* 0C2F5C 800C235C 356C0088 */  ori   $t4, $t3, 0x88
/* 0C2F60 800C2360 318D00FF */  andi  $t5, $t4, 0xff
/* 0C2F64 800C2364 ACB90004 */  sw    $t9, 4($a1)
/* 0C2F68 800C2368 ACAA0000 */  sw    $t2, ($a1)
/* 0C2F6C 800C236C 24A30008 */  addiu $v1, $a1, 8
/* 0C2F70 800C2370 AC640004 */  sw    $a0, 4($v1)
/* 0C2F74 800C2374 000D7400 */  sll   $t6, $t5, 0x10
/* 0C2F78 800C2378 24E700B4 */  addiu $a3, $a3, 0xb4
/* 0C2F7C 800C237C 00E62021 */  addu  $a0, $a3, $a2
/* 0C2F80 800C2380 01C97825 */  or    $t7, $t6, $t1
/* 0C2F84 800C2384 35F8014C */  ori   $t8, $t7, 0x14c
/* 0C2F88 800C2388 308B0006 */  andi  $t3, $a0, 6
/* 0C2F8C 800C238C 356C0088 */  ori   $t4, $t3, 0x88
/* 0C2F90 800C2390 AC780000 */  sw    $t8, ($v1)
/* 0C2F94 800C2394 24620008 */  addiu $v0, $v1, 8
/* 0C2F98 800C2398 25080100 */  addiu $t0, $t0, 0x100
/* 0C2F9C 800C239C 0106C821 */  addu  $t9, $t0, $a2
/* 0C2FA0 800C23A0 318D00FF */  andi  $t5, $t4, 0xff
/* 0C2FA4 800C23A4 000D7400 */  sll   $t6, $t5, 0x10
/* 0C2FA8 800C23A8 AC590004 */  sw    $t9, 4($v0)
/* 0C2FAC 800C23AC 24430008 */  addiu $v1, $v0, 8
/* 0C2FB0 800C23B0 01C97825 */  or    $t7, $t6, $t1
/* 0C2FB4 800C23B4 AC4A0000 */  sw    $t2, ($v0)
/* 0C2FB8 800C23B8 35F8014C */  ori   $t8, $t7, 0x14c
/* 0C2FBC 800C23BC AC780000 */  sw    $t8, ($v1)
/* 0C2FC0 800C23C0 AC640004 */  sw    $a0, 4($v1)
/* 0C2FC4 800C23C4 24650008 */  addiu $a1, $v1, 8
/* 0C2FC8 800C23C8 25080100 */  addiu $t0, $t0, 0x100
/* 0C2FCC 800C23CC 0106C821 */  addu  $t9, $t0, $a2
/* 0C2FD0 800C23D0 ACB90004 */  sw    $t9, 4($a1)
/* 0C2FD4 800C23D4 ACAA0000 */  sw    $t2, ($a1)
/* 0C2FD8 800C23D8 8FA40018 */  lw    $a0, 0x18($sp)
/* 0C2FDC 800C23DC 24A20008 */  addiu $v0, $a1, 8
/* 0C2FE0 800C23E0 0C01ECF4 */  jal   func_8007B3D0
/* 0C2FE4 800C23E4 AC820000 */   sw    $v0, ($a0)
/* 0C2FE8 800C23E8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C2FEC 800C23EC 27BD0018 */  addiu $sp, $sp, 0x18
/* 0C2FF0 800C23F0 03E00008 */  jr    $ra
/* 0C2FF4 800C23F4 00000000 */   nop   

