glabel func_8007A98C
/* 07B58C 8007A98C 3C038012 */  lui   $v1, %hi(D_801262D0) # $v1, 0x8012
/* 07B590 8007A990 246362D0 */  addiu $v1, %lo(D_801262D0) # addiu $v1, $v1, 0x62d0
/* 07B594 8007A994 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 07B598 8007A998 8C620000 */  lw    $v0, ($v1)
/* 07B59C 8007A99C AFB1001C */  sw    $s1, 0x1c($sp)
/* 07B5A0 8007A9A0 AFB00018 */  sw    $s0, 0x18($sp)
/* 07B5A4 8007A9A4 00808825 */  move  $s1, $a0
/* 07B5A8 8007A9A8 AFBF0024 */  sw    $ra, 0x24($sp)
/* 07B5AC 8007A9AC AFB20020 */  sw    $s2, 0x20($sp)
/* 07B5B0 8007A9B0 10400006 */  beqz  $v0, .L8007A9CC
/* 07B5B4 8007A9B4 24100001 */   li    $s0, 1
/* 07B5B8 8007A9B8 244EFFFF */  addiu $t6, $v0, -1
/* 07B5BC 8007A9BC 15C00003 */  bnez  $t6, .L8007A9CC
/* 07B5C0 8007A9C0 AC6E0000 */   sw    $t6, ($v1)
/* 07B5C4 8007A9C4 0C034744 */  jal   osViBlack
/* 07B5C8 8007A9C8 00002025 */   move  $a0, $zero
.L8007A9CC:
/* 07B5CC 8007A9CC 24010008 */  li    $at, 8
/* 07B5D0 8007A9D0 12210003 */  beq   $s1, $at, .L8007A9E0
/* 07B5D4 8007A9D4 00000000 */   nop   
/* 07B5D8 8007A9D8 0C01EAE7 */  jal   swap_framebuffers
/* 07B5DC 8007A9DC 00000000 */   nop   
.L8007A9E0:
/* 07B5E0 8007A9E0 3C128012 */  lui   $s2, %hi(gVideoMesgQueue) # $s2, 0x8012
/* 07B5E4 8007A9E4 265261A0 */  addiu $s2, %lo(gVideoMesgQueue) # addiu $s2, $s2, 0x61a0
/* 07B5E8 8007A9E8 02402025 */  move  $a0, $s2
/* 07B5EC 8007A9EC 00002825 */  move  $a1, $zero
/* 07B5F0 8007A9F0 0C0322EC */  jal   osRecvMesg
/* 07B5F4 8007A9F4 00003025 */   move  $a2, $zero
/* 07B5F8 8007A9F8 2411FFFF */  li    $s1, -1
/* 07B5FC 8007A9FC 1051000A */  beq   $v0, $s1, .L8007AA28
/* 07B600 8007AA00 00000000 */   nop   
.L8007AA04:
/* 07B604 8007AA04 26100001 */  addiu $s0, $s0, 1
/* 07B608 8007AA08 321800FF */  andi  $t8, $s0, 0xff
/* 07B60C 8007AA0C 03008025 */  move  $s0, $t8
/* 07B610 8007AA10 02402025 */  move  $a0, $s2
/* 07B614 8007AA14 00002825 */  move  $a1, $zero
/* 07B618 8007AA18 0C0322EC */  jal   osRecvMesg
/* 07B61C 8007AA1C 00003025 */   move  $a2, $zero
/* 07B620 8007AA20 1451FFF8 */  bne   $v0, $s1, .L8007AA04
/* 07B624 8007AA24 00000000 */   nop   
.L8007AA28:
/* 07B628 8007AA28 3C118012 */  lui   $s1, %hi(D_80126309) # $s1, 0x8012
/* 07B62C 8007AA2C 26316309 */  addiu $s1, %lo(D_80126309) # addiu $s1, $s1, 0x6309
/* 07B630 8007AA30 92240000 */  lbu   $a0, ($s1)
/* 07B634 8007AA34 02001825 */  move  $v1, $s0
/* 07B638 8007AA38 0204082A */  slt   $at, $s0, $a0
/* 07B63C 8007AA3C 10200012 */  beqz  $at, .L8007AA88
/* 07B640 8007AA40 3C068012 */   lui   $a2, %hi(D_80126308) # $a2, 0x8012
/* 07B644 8007AA44 3C068012 */  lui   $a2, %hi(D_80126308) # $a2, 0x8012
/* 07B648 8007AA48 24C66308 */  addiu $a2, %lo(D_80126308) # addiu $a2, $a2, 0x6308
/* 07B64C 8007AA4C 90C50000 */  lbu   $a1, ($a2)
/* 07B650 8007AA50 00000000 */  nop   
/* 07B654 8007AA54 28A10014 */  slti  $at, $a1, 0x14
/* 07B658 8007AA58 10200004 */  beqz  $at, .L8007AA6C
/* 07B65C 8007AA5C 00A01025 */   move  $v0, $a1
/* 07B660 8007AA60 24B90001 */  addiu $t9, $a1, 1
/* 07B664 8007AA64 A0D90000 */  sb    $t9, ($a2)
/* 07B668 8007AA68 332200FF */  andi  $v0, $t9, 0xff
.L8007AA6C:
/* 07B66C 8007AA6C 24010014 */  li    $at, 20
/* 07B670 8007AA70 14410012 */  bne   $v0, $at, .L8007AABC
/* 07B674 8007AA74 0064082A */   slt   $at, $v1, $a0
/* 07B678 8007AA78 A2300000 */  sb    $s0, ($s1)
/* 07B67C 8007AA7C A0C00000 */  sb    $zero, ($a2)
/* 07B680 8007AA80 1000000D */  b     .L8007AAB8
/* 07B684 8007AA84 320400FF */   andi  $a0, $s0, 0xff
.L8007AA88:
/* 07B688 8007AA88 24C66308 */  addiu $a2, %lo(D_80126308) # addiu $a2, $a2, 0x6308
/* 07B68C 8007AA8C 0083082A */  slt   $at, $a0, $v1
/* 07B690 8007AA90 10200009 */  beqz  $at, .L8007AAB8
/* 07B694 8007AA94 A0C00000 */   sb    $zero, ($a2)
/* 07B698 8007AA98 3C088012 */  lui   $t0, %hi(D_801262E4) # $t0, 0x8012
/* 07B69C 8007AA9C 910862E4 */  lbu   $t0, %lo(D_801262E4)($t0)
/* 07B6A0 8007AAA0 00000000 */  nop   
/* 07B6A4 8007AAA4 0103082A */  slt   $at, $t0, $v1
/* 07B6A8 8007AAA8 14200004 */  bnez  $at, .L8007AABC
/* 07B6AC 8007AAAC 0064082A */   slt   $at, $v1, $a0
/* 07B6B0 8007AAB0 A2300000 */  sb    $s0, ($s1)
/* 07B6B4 8007AAB4 320400FF */  andi  $a0, $s0, 0xff
.L8007AAB8:
/* 07B6B8 8007AAB8 0064082A */  slt   $at, $v1, $a0
.L8007AABC:
/* 07B6BC 8007AABC 1020000A */  beqz  $at, .L8007AAE8
.L8007AAC0:
/* 07B6C0 8007AAC0 02402025 */   move  $a0, $s2
/* 07B6C4 8007AAC4 00002825 */  move  $a1, $zero
/* 07B6C8 8007AAC8 0C0322EC */  jal   osRecvMesg
/* 07B6CC 8007AACC 24060001 */   li    $a2, 1
/* 07B6D0 8007AAD0 922A0000 */  lbu   $t2, ($s1)
/* 07B6D4 8007AAD4 26100001 */  addiu $s0, $s0, 1
/* 07B6D8 8007AAD8 320300FF */  andi  $v1, $s0, 0xff
/* 07B6DC 8007AADC 006A082A */  slt   $at, $v1, $t2
/* 07B6E0 8007AAE0 1420FFF7 */  bnez  $at, .L8007AAC0
/* 07B6E4 8007AAE4 00608025 */   move  $s0, $v1
.L8007AAE8:
/* 07B6E8 8007AAE8 3C048012 */  lui   $a0, %hi(gVideoLastFramebuffer) # $a0, 0x8012
/* 07B6EC 8007AAEC 8C8462D8 */  lw    $a0, %lo(gVideoLastFramebuffer)($a0)
/* 07B6F0 8007AAF0 0C034908 */  jal   osViSwapBuffer
/* 07B6F4 8007AAF4 AFA30028 */   sw    $v1, 0x28($sp)
/* 07B6F8 8007AAF8 02402025 */  move  $a0, $s2
/* 07B6FC 8007AAFC 00002825 */  move  $a1, $zero
/* 07B700 8007AB00 0C0322EC */  jal   osRecvMesg
/* 07B704 8007AB04 24060001 */   li    $a2, 1
/* 07B708 8007AB08 8FBF0024 */  lw    $ra, 0x24($sp)
/* 07B70C 8007AB0C 8FA20028 */  lw    $v0, 0x28($sp)
/* 07B710 8007AB10 8FB00018 */  lw    $s0, 0x18($sp)
/* 07B714 8007AB14 8FB1001C */  lw    $s1, 0x1c($sp)
/* 07B718 8007AB18 8FB20020 */  lw    $s2, 0x20($sp)
/* 07B71C 8007AB1C 03E00008 */  jr    $ra
/* 07B720 8007AB20 27BD0030 */   addiu $sp, $sp, 0x30

