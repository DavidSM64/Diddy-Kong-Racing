.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800CD600
/* 0CE200 800CD600 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CE204 800CD604 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CE208 800CD608 240E0001 */  li    $t6, 1
/* 0CE20C 800CD60C 3C01800E */  lui   $at, %hi(D_800E38D0) # $at, 0x800e
/* 0CE210 800CD610 3C048013 */  lui   $a0, %hi(D_8012CE28) # $a0, 0x8013
/* 0CE214 800CD614 3C058013 */  lui   $a1, %hi(D_8012CE20) # $a1, 0x8013
/* 0CE218 800CD618 AC2E38D0 */  sw    $t6, %lo(D_800E38D0)($at)
/* 0CE21C 800CD61C 24A5CE20 */  addiu $a1, %lo(D_8012CE20) # addiu $a1, $a1, -0x31e0
/* 0CE220 800CD620 2484CE28 */  addiu $a0, %lo(D_8012CE28) # addiu $a0, $a0, -0x31d8
/* 0CE224 800CD624 0C032208 */  jal   osCreateMesgQueue
/* 0CE228 800CD628 24060001 */   li    $a2, 1
/* 0CE22C 800CD62C 3C048013 */  lui   $a0, %hi(D_8012CE28) # $a0, 0x8013
/* 0CE230 800CD630 2484CE28 */  addiu $a0, %lo(D_8012CE28) # addiu $a0, $a0, -0x31d8
/* 0CE234 800CD634 00002825 */  move  $a1, $zero
/* 0CE238 800CD638 0C03238C */  jal   func_800C8E30
/* 0CE23C 800CD63C 00003025 */   move  $a2, $zero
/* 0CE240 800CD640 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CE244 800CD644 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CE248 800CD648 03E00008 */  jr    $ra
/* 0CE24C 800CD64C 00000000 */   nop   

glabel func_800CD650
/* 0CE250 800CD650 3C0E800E */  lui   $t6, %hi(D_800E38D0) # $t6, 0x800e
/* 0CE254 800CD654 8DCE38D0 */  lw    $t6, %lo(D_800E38D0)($t6)
/* 0CE258 800CD658 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0CE25C 800CD65C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CE260 800CD660 15C00003 */  bnez  $t6, .L800CD670
/* 0CE264 800CD664 00000000 */   nop   
/* 0CE268 800CD668 0C033580 */  jal   func_800CD600
/* 0CE26C 800CD66C 00000000 */   nop   
.L800CD670:
/* 0CE270 800CD670 3C048013 */  lui   $a0, %hi(D_8012CE28) # $a0, 0x8013
/* 0CE274 800CD674 2484CE28 */  addiu $a0, %lo(D_8012CE28) # addiu $a0, $a0, -0x31d8
/* 0CE278 800CD678 27A5001C */  addiu $a1, $sp, 0x1c
/* 0CE27C 800CD67C 0C0322EC */  jal   osRecvMesg
/* 0CE280 800CD680 24060001 */   li    $a2, 1
/* 0CE284 800CD684 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CE288 800CD688 27BD0020 */  addiu $sp, $sp, 0x20
/* 0CE28C 800CD68C 03E00008 */  jr    $ra
/* 0CE290 800CD690 00000000 */   nop   

glabel func_800CD694
/* 0CE294 800CD694 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CE298 800CD698 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CE29C 800CD69C 3C048013 */  lui   $a0, %hi(D_8012CE28) # $a0, 0x8013
/* 0CE2A0 800CD6A0 2484CE28 */  addiu $a0, %lo(D_8012CE28) # addiu $a0, $a0, -0x31d8
/* 0CE2A4 800CD6A4 00002825 */  move  $a1, $zero
/* 0CE2A8 800CD6A8 0C03238C */  jal   func_800C8E30
/* 0CE2AC 800CD6AC 00003025 */   move  $a2, $zero
/* 0CE2B0 800CD6B0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CE2B4 800CD6B4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CE2B8 800CD6B8 03E00008 */  jr    $ra
/* 0CE2BC 800CD6BC 00000000 */   nop   

glabel func_800CD6C0
/* 0CE2C0 800CD6C0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CE2C4 800CD6C4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CE2C8 800CD6C8 AFA40018 */  sw    $a0, 0x18($sp)
/* 0CE2CC 800CD6CC 0C0354B0 */  jal   func_800D52C0
/* 0CE2D0 800CD6D0 AFA5001C */   sw    $a1, 0x1c($sp)
/* 0CE2D4 800CD6D4 10400003 */  beqz  $v0, .L800CD6E4
/* 0CE2D8 800CD6D8 00000000 */   nop   
/* 0CE2DC 800CD6DC 1000001F */  b     .L800CD75C
/* 0CE2E0 800CD6E0 2402FFFF */   li    $v0, -1
.L800CD6E4:
/* 0CE2E4 800CD6E4 8FAE0018 */  lw    $t6, 0x18($sp)
/* 0CE2E8 800CD6E8 24010001 */  li    $at, 1
/* 0CE2EC 800CD6EC 15C10004 */  bne   $t6, $at, .L800CD700
/* 0CE2F0 800CD6F0 00000000 */   nop   
/* 0CE2F4 800CD6F4 8FA4001C */  lw    $a0, 0x1c($sp)
/* 0CE2F8 800CD6F8 0C03518C */  jal   func_800D4630
/* 0CE2FC 800CD6FC 24050040 */   li    $a1, 64
.L800CD700:
/* 0CE300 800CD700 0C03233C */  jal   func_800C8CF0
/* 0CE304 800CD704 8FA4001C */   lw    $a0, 0x1c($sp)
/* 0CE308 800CD708 3C0FA480 */  lui   $t7, 0xa480
/* 0CE30C 800CD70C ADE20000 */  sw    $v0, ($t7)
/* 0CE310 800CD710 8FB80018 */  lw    $t8, 0x18($sp)
/* 0CE314 800CD714 17000006 */  bnez  $t8, .L800CD730
/* 0CE318 800CD718 00000000 */   nop   
/* 0CE31C 800CD71C 3C191FC0 */  lui   $t9, (0x1FC007C0 >> 16) # lui $t9, 0x1fc0
/* 0CE320 800CD720 373907C0 */  ori   $t9, (0x1FC007C0 & 0xFFFF) # ori $t9, $t9, 0x7c0
/* 0CE324 800CD724 3C08A480 */  lui   $t0, %hi(D_A4800004) # $t0, 0xa480
/* 0CE328 800CD728 10000005 */  b     .L800CD740
/* 0CE32C 800CD72C AD190004 */   sw    $t9, %lo(D_A4800004)($t0)
.L800CD730:
/* 0CE330 800CD730 3C091FC0 */  lui   $t1, (0x1FC007C0 >> 16) # lui $t1, 0x1fc0
/* 0CE334 800CD734 352907C0 */  ori   $t1, (0x1FC007C0 & 0xFFFF) # ori $t1, $t1, 0x7c0
/* 0CE338 800CD738 3C0AA480 */  lui   $t2, %hi(D_A4800010) # $t2, 0xa480
/* 0CE33C 800CD73C AD490010 */  sw    $t1, %lo(D_A4800010)($t2)
.L800CD740:
/* 0CE340 800CD740 8FAB0018 */  lw    $t3, 0x18($sp)
/* 0CE344 800CD744 15600004 */  bnez  $t3, .L800CD758
/* 0CE348 800CD748 00000000 */   nop   
/* 0CE34C 800CD74C 8FA4001C */  lw    $a0, 0x1c($sp)
/* 0CE350 800CD750 0C0345FC */  jal   func_800D17F0
/* 0CE354 800CD754 24050040 */   li    $a1, 64
.L800CD758:
/* 0CE358 800CD758 00001025 */  move  $v0, $zero
.L800CD75C:
/* 0CE35C 800CD75C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CE360 800CD760 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CE364 800CD764 03E00008 */  jr    $ra
/* 0CE368 800CD768 00000000 */   nop   

/* 0CE36C 800CD76C 00000000 */  nop   
