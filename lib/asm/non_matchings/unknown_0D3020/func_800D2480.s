glabel func_800D2480
/* 0D3080 800D2480 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0D3084 800D2484 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0D3088 800D2488 240E0001 */  li    $t6, 1
/* 0D308C 800D248C 3C01800E */  lui   $at, %hi(D_800E4800) # $at, 0x800e
/* 0D3090 800D2490 3C048013 */  lui   $a0, %hi(D_8012D1E8) # $a0, 0x8013
/* 0D3094 800D2494 3C058013 */  lui   $a1, %hi(D_8012D1E0) # $a1, 0x8013
/* 0D3098 800D2498 AC2E4800 */  sw    $t6, %lo(D_800E4800)($at)
/* 0D309C 800D249C 24A5D1E0 */  addiu $a1, %lo(D_8012D1E0) # addiu $a1, $a1, -0x2e20
/* 0D30A0 800D24A0 2484D1E8 */  addiu $a0, %lo(D_8012D1E8) # addiu $a0, $a0, -0x2e18
/* 0D30A4 800D24A4 0C032208 */  jal   osCreateMesgQueue
/* 0D30A8 800D24A8 24060001 */   li    $a2, 1
/* 0D30AC 800D24AC 3C048013 */  lui   $a0, %hi(D_8012D1E8) # $a0, 0x8013
/* 0D30B0 800D24B0 2484D1E8 */  addiu $a0, %lo(D_8012D1E8) # addiu $a0, $a0, -0x2e18
/* 0D30B4 800D24B4 00002825 */  move  $a1, $zero
/* 0D30B8 800D24B8 0C03238C */  jal   func_800C8E30
/* 0D30BC 800D24BC 00003025 */   move  $a2, $zero
/* 0D30C0 800D24C0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0D30C4 800D24C4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0D30C8 800D24C8 03E00008 */  jr    $ra
/* 0D30CC 800D24CC 00000000 */   nop   

/* 0D30D0 800D24D0 3C0E800E */  lui   $t6, %hi(D_800E4800) # $t6, 0x800e
/* 0D30D4 800D24D4 8DCE4800 */  lw    $t6, %lo(D_800E4800)($t6)
/* 0D30D8 800D24D8 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0D30DC 800D24DC AFBF0014 */  sw    $ra, 0x14($sp)
/* 0D30E0 800D24E0 15C00003 */  bnez  $t6, .L800D24F0
/* 0D30E4 800D24E4 00000000 */   nop   
/* 0D30E8 800D24E8 0C034920 */  jal   func_800D2480
/* 0D30EC 800D24EC 00000000 */   nop   
.L800D24F0:
/* 0D30F0 800D24F0 3C048013 */  lui   $a0, %hi(D_8012D1E8) # $a0, 0x8013
/* 0D30F4 800D24F4 2484D1E8 */  addiu $a0, %lo(D_8012D1E8) # addiu $a0, $a0, -0x2e18
/* 0D30F8 800D24F8 27A5001C */  addiu $a1, $sp, 0x1c
/* 0D30FC 800D24FC 0C0322EC */  jal   osRecvMesg
/* 0D3100 800D2500 24060001 */   li    $a2, 1
/* 0D3104 800D2504 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0D3108 800D2508 27BD0020 */  addiu $sp, $sp, 0x20
/* 0D310C 800D250C 03E00008 */  jr    $ra
/* 0D3110 800D2510 00000000 */   nop   

/* 0D3114 800D2514 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0D3118 800D2518 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0D311C 800D251C 3C048013 */  lui   $a0, %hi(D_8012D1E8) # $a0, 0x8013
/* 0D3120 800D2520 2484D1E8 */  addiu $a0, %lo(D_8012D1E8) # addiu $a0, $a0, -0x2e18
/* 0D3124 800D2524 00002825 */  move  $a1, $zero
/* 0D3128 800D2528 0C03238C */  jal   func_800C8E30
/* 0D312C 800D252C 00003025 */   move  $a2, $zero
/* 0D3130 800D2530 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0D3134 800D2534 27BD0018 */  addiu $sp, $sp, 0x18
/* 0D3138 800D2538 03E00008 */  jr    $ra
/* 0D313C 800D253C 00000000 */   nop   

