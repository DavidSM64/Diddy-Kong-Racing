.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800D18E0
/* 0D24E0 800D18E0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D24E4 800D18E4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D24E8 800D18E8 AFA40028 */  sw    $a0, 0x28($sp)
/* 0D24EC 800D18EC AFA60030 */  sw    $a2, 0x30($sp)
/* 0D24F0 800D18F0 AFA70034 */  sw    $a3, 0x34($sp)
/* 0D24F4 800D18F4 0C035814 */  jal   func_800D6050
/* 0D24F8 800D18F8 AFB00018 */   sw    $s0, 0x18($sp)
/* 0D24FC 800D18FC 10400003 */  beqz  $v0, .L800D190C
/* 0D2500 800D1900 00000000 */   nop   
/* 0D2504 800D1904 1000001B */  b     .L800D1974
/* 0D2508 800D1908 2402FFFF */   li    $v0, -1
.L800D190C:
/* 0D250C 800D190C 240E0001 */  li    $t6, 1
/* 0D2510 800D1910 3C0FA410 */  lui   $t7, %hi(D_A410000C) # $t7, 0xa410
/* 0D2514 800D1914 ADEE000C */  sw    $t6, %lo(D_A410000C)($t7)
.L800D1918:
/* 0D2518 800D1918 3C18A410 */  lui   $t8, %hi(D_A410000C) # $t8, 0xa410
/* 0D251C 800D191C 8F10000C */  lw    $s0, %lo(D_A410000C)($t8)
/* 0D2520 800D1920 32190001 */  andi  $t9, $s0, 1
/* 0D2524 800D1924 1720FFFC */  bnez  $t9, .L800D1918
/* 0D2528 800D1928 00000000 */   nop   
/* 0D252C 800D192C 0C03233C */  jal   func_800C8CF0
/* 0D2530 800D1930 8FA40028 */   lw    $a0, 0x28($sp)
/* 0D2534 800D1934 3C08A410 */  lui   $t0, 0xa410
/* 0D2538 800D1938 AD020000 */  sw    $v0, ($t0)
/* 0D253C 800D193C 0C03233C */  jal   func_800C8CF0
/* 0D2540 800D1940 8FA40028 */   lw    $a0, 0x28($sp)
/* 0D2544 800D1944 8FAD0034 */  lw    $t5, 0x34($sp)
/* 0D2548 800D1948 00405825 */  move  $t3, $v0
/* 0D254C 800D194C 8FAC0030 */  lw    $t4, 0x30($sp)
/* 0D2550 800D1950 016D7821 */  addu  $t7, $t3, $t5
/* 0D2554 800D1954 240A0000 */  li    $t2, 0
/* 0D2558 800D1958 01ED082B */  sltu  $at, $t7, $t5
/* 0D255C 800D195C 002A7021 */  addu  $t6, $at, $t2
/* 0D2560 800D1960 01E04825 */  move  $t1, $t7
/* 0D2564 800D1964 3C18A410 */  lui   $t8, %hi(D_A4100004) # $t8, 0xa410
/* 0D2568 800D1968 AF090004 */  sw    $t1, %lo(D_A4100004)($t8)
/* 0D256C 800D196C 00001025 */  move  $v0, $zero
/* 0D2570 800D1970 01CC7021 */  addu  $t6, $t6, $t4
.L800D1974:
/* 0D2574 800D1974 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D2578 800D1978 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D257C 800D197C 27BD0028 */  addiu $sp, $sp, 0x28
/* 0D2580 800D1980 03E00008 */  jr    $ra
/* 0D2584 800D1984 00000000 */   nop   

/* 0D2588 800D1988 00000000 */  nop   
/* 0D258C 800D198C 00000000 */  nop   
