glabel func_8009C6D4
/* 09D2D4 8009C6D4 3C08800E */  lui   $t0, %hi(gAssetsMenuElementIds) # $t0, 0x800e
/* 09D2D8 8009C6D8 2508F750 */  addiu $t0, %lo(gAssetsMenuElementIds) # addiu $t0, $t0, -0x8b0
/* 09D2DC 8009C6DC 8D060000 */  lw    $a2, ($t0)
/* 09D2E0 8009C6E0 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 09D2E4 8009C6E4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 09D2E8 8009C6E8 14C00026 */  bnez  $a2, .L8009C784
/* 09D2EC 8009C6EC 00803825 */   move  $a3, $a0
/* 09D2F0 8009C6F0 24040012 */  li    $a0, 18
/* 09D2F4 8009C6F4 0C01DB16 */  jal   load_asset_section_from_rom
/* 09D2F8 8009C6F8 AFA70038 */   sw    $a3, 0x38($sp)
/* 09D2FC 8009C6FC 3C05800E */  lui   $a1, %hi(D_800DF754) # $a1, 0x800e
/* 09D300 8009C700 24A5F754 */  addiu $a1, %lo(D_800DF754) # addiu $a1, $a1, -0x8ac
/* 09D304 8009C704 A4A00000 */  sh    $zero, ($a1)
/* 09D308 8009C708 84A30000 */  lh    $v1, ($a1)
/* 09D30C 8009C70C 3C08800E */  lui   $t0, %hi(gAssetsMenuElementIds) # $t0, 0x800e
/* 09D310 8009C710 2508F750 */  addiu $t0, %lo(gAssetsMenuElementIds) # addiu $t0, $t0, -0x8b0
/* 09D314 8009C714 00037040 */  sll   $t6, $v1, 1
/* 09D318 8009C718 AD020000 */  sw    $v0, ($t0)
/* 09D31C 8009C71C 004E7821 */  addu  $t7, $v0, $t6
/* 09D320 8009C720 85F80000 */  lh    $t8, ($t7)
/* 09D324 8009C724 2404FFFF */  li    $a0, -1
/* 09D328 8009C728 8FA70038 */  lw    $a3, 0x38($sp)
/* 09D32C 8009C72C 1098000B */  beq   $a0, $t8, .L8009C75C
/* 09D330 8009C730 00403025 */   move  $a2, $v0
/* 09D334 8009C734 24790001 */  addiu $t9, $v1, 1
.L8009C738:
/* 09D338 8009C738 A4B90000 */  sh    $t9, ($a1)
/* 09D33C 8009C73C 84A30000 */  lh    $v1, ($a1)
/* 09D340 8009C740 00000000 */  nop   
/* 09D344 8009C744 00034840 */  sll   $t1, $v1, 1
/* 09D348 8009C748 00C95021 */  addu  $t2, $a2, $t1
/* 09D34C 8009C74C 854B0000 */  lh    $t3, ($t2)
/* 09D350 8009C750 00000000 */  nop   
/* 09D354 8009C754 148BFFF8 */  bne   $a0, $t3, .L8009C738
/* 09D358 8009C758 24790001 */   addiu $t9, $v1, 1
.L8009C75C:
/* 09D35C 8009C75C 3C01800E */  lui   $at, %hi(D_800DF758) # $at, 0x800e
/* 09D360 8009C760 18600008 */  blez  $v1, .L8009C784
/* 09D364 8009C764 A420F758 */   sh    $zero, %lo(D_800DF758)($at)
/* 09D368 8009C768 3C0C8012 */  lui   $t4, %hi(D_80126750) # $t4, 0x8012
/* 09D36C 8009C76C 25826750 */  addiu $v0, $t4, %lo(D_80126750)
/* 09D370 8009C770 00622021 */  addu  $a0, $v1, $v0
.L8009C774:
/* 09D374 8009C774 24420001 */  addiu $v0, $v0, 1
/* 09D378 8009C778 0044082B */  sltu  $at, $v0, $a0
/* 09D37C 8009C77C 1420FFFD */  bnez  $at, .L8009C774
/* 09D380 8009C780 A040FFFF */   sb    $zero, -1($v0)
.L8009C784:
/* 09D384 8009C784 3C0D8012 */  lui   $t5, %hi(D_80126750) # $t5, 0x8012
/* 09D388 8009C788 25AD6750 */  addiu $t5, %lo(D_80126750) # addiu $t5, $t5, 0x6750
/* 09D38C 8009C78C 00ED7021 */  addu  $t6, $a3, $t5
/* 09D390 8009C790 AFAE0024 */  sw    $t6, 0x24($sp)
/* 09D394 8009C794 91D80000 */  lbu   $t8, ($t6)
/* 09D398 8009C798 0007C840 */  sll   $t9, $a3, 1
/* 09D39C 8009C79C 1700003D */  bnez  $t8, .L8009C894
/* 09D3A0 8009C7A0 00D94821 */   addu  $t1, $a2, $t9
/* 09D3A4 8009C7A4 85220000 */  lh    $v0, ($t1)
/* 09D3A8 8009C7A8 3401C000 */  li    $at, 49152
/* 09D3AC 8009C7AC 304AC000 */  andi  $t2, $v0, 0xc000
/* 09D3B0 8009C7B0 1541000A */  bne   $t2, $at, .L8009C7DC
/* 09D3B4 8009C7B4 304C8000 */   andi  $t4, $v0, 0x8000
/* 09D3B8 8009C7B8 30443FFF */  andi  $a0, $v0, 0x3fff
/* 09D3BC 8009C7BC 0C01EB9D */  jal   load_texture
/* 09D3C0 8009C7C0 AFA70038 */   sw    $a3, 0x38($sp)
/* 09D3C4 8009C7C4 8FA70038 */  lw    $a3, 0x38($sp)
/* 09D3C8 8009C7C8 3C018012 */  lui   $at, %hi(gMenuTextures) # $at, 0x8012
/* 09D3CC 8009C7CC 00075880 */  sll   $t3, $a3, 2
/* 09D3D0 8009C7D0 002B0821 */  addu  $at, $at, $t3
/* 09D3D4 8009C7D4 10000027 */  b     .L8009C874
/* 09D3D8 8009C7D8 AC226550 */   sw    $v0, %lo(gMenuTextures)($at)
.L8009C7DC:
/* 09D3DC 8009C7DC 1180000B */  beqz  $t4, .L8009C80C
/* 09D3E0 8009C7E0 304E4000 */   andi  $t6, $v0, 0x4000
/* 09D3E4 8009C7E4 30443FFF */  andi  $a0, $v0, 0x3fff
/* 09D3E8 8009C7E8 00002825 */  move  $a1, $zero
/* 09D3EC 8009C7EC 0C01F04B */  jal   func_8007C12C
/* 09D3F0 8009C7F0 AFA70038 */   sw    $a3, 0x38($sp)
/* 09D3F4 8009C7F4 8FA70038 */  lw    $a3, 0x38($sp)
/* 09D3F8 8009C7F8 3C018012 */  lui   $at, %hi(gMenuTextures) # $at, 0x8012
/* 09D3FC 8009C7FC 00076880 */  sll   $t5, $a3, 2
/* 09D400 8009C800 002D0821 */  addu  $at, $at, $t5
/* 09D404 8009C804 1000001B */  b     .L8009C874
/* 09D408 8009C808 AC226550 */   sw    $v0, %lo(gMenuTextures)($at)
.L8009C80C:
/* 09D40C 8009C80C 11C00011 */  beqz  $t6, .L8009C854
/* 09D410 8009C810 30443FFF */   andi  $a0, $v0, 0x3fff
/* 09D414 8009C814 24180008 */  li    $t8, 8
/* 09D418 8009C818 A3A2002C */  sb    $v0, 0x2c($sp)
/* 09D41C 8009C81C A3B8002D */  sb    $t8, 0x2d($sp)
/* 09D420 8009C820 A7A0002E */  sh    $zero, 0x2e($sp)
/* 09D424 8009C824 A7A00030 */  sh    $zero, 0x30($sp)
/* 09D428 8009C828 A7A00032 */  sh    $zero, 0x32($sp)
/* 09D42C 8009C82C 27A4002C */  addiu $a0, $sp, 0x2c
/* 09D430 8009C830 00002825 */  move  $a1, $zero
/* 09D434 8009C834 0C003A95 */  jal   spawn_object
/* 09D438 8009C838 AFA70038 */   sw    $a3, 0x38($sp)
/* 09D43C 8009C83C 8FA70038 */  lw    $a3, 0x38($sp)
/* 09D440 8009C840 3C018012 */  lui   $at, %hi(gMenuTextures) # $at, 0x8012
/* 09D444 8009C844 0007C880 */  sll   $t9, $a3, 2
/* 09D448 8009C848 00390821 */  addu  $at, $at, $t9
/* 09D44C 8009C84C 10000009 */  b     .L8009C874
/* 09D450 8009C850 AC226550 */   sw    $v0, %lo(gMenuTextures)($at)
.L8009C854:
/* 09D454 8009C854 00002825 */  move  $a1, $zero
/* 09D458 8009C858 0C017E67 */  jal   func_8005F99C
/* 09D45C 8009C85C AFA70038 */   sw    $a3, 0x38($sp)
/* 09D460 8009C860 8FA70038 */  lw    $a3, 0x38($sp)
/* 09D464 8009C864 3C018012 */  lui   $at, %hi(gMenuTextures) # $at, 0x8012
/* 09D468 8009C868 00074880 */  sll   $t1, $a3, 2
/* 09D46C 8009C86C 00290821 */  addu  $at, $at, $t1
/* 09D470 8009C870 AC226550 */  sw    $v0, %lo(gMenuTextures)($at)
.L8009C874:
/* 09D474 8009C874 8FAB0024 */  lw    $t3, 0x24($sp)
/* 09D478 8009C878 240A0001 */  li    $t2, 1
/* 09D47C 8009C87C 3C0C800E */  lui   $t4, %hi(D_800DF758) # $t4, 0x800e
/* 09D480 8009C880 A16A0000 */  sb    $t2, ($t3)
/* 09D484 8009C884 858CF758 */  lh    $t4, %lo(D_800DF758)($t4)
/* 09D488 8009C888 3C01800E */  lui   $at, %hi(D_800DF758) # $at, 0x800e
/* 09D48C 8009C88C 258D0001 */  addiu $t5, $t4, 1
/* 09D490 8009C890 A42DF758 */  sh    $t5, %lo(D_800DF758)($at)
.L8009C894:
/* 09D494 8009C894 8FBF0014 */  lw    $ra, 0x14($sp)
/* 09D498 8009C898 27BD0038 */  addiu $sp, $sp, 0x38
/* 09D49C 8009C89C 03E00008 */  jr    $ra
/* 09D4A0 8009C8A0 00000000 */   nop   

