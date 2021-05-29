glabel func_8006EFDC
/* 06FBDC 8006EFDC 3C0F800E */  lui   $t7, %hi(D_800DD3EC) # $t7, 0x800e
/* 06FBE0 8006EFE0 3C19800E */  lui   $t9, %hi(D_800DD3BC) # $t9, 0x800e
/* 06FBE4 8006EFE4 3C0D800E */  lui   $t5, %hi(D_800DD3CC) # $t5, 0x800e
/* 06FBE8 8006EFE8 8DADD3CC */  lw    $t5, %lo(D_800DD3CC)($t5)
/* 06FBEC 8006EFEC 8F39D3BC */  lw    $t9, %lo(D_800DD3BC)($t9)
/* 06FBF0 8006EFF0 8DEFD3EC */  lw    $t7, %lo(D_800DD3EC)($t7)
/* 06FBF4 8006EFF4 240E0003 */  li    $t6, 3
/* 06FBF8 8006EFF8 3C018012 */  lui   $at, %hi(D_8012350C) # $at, 0x8012
/* 06FBFC 8006EFFC 3C0A800E */  lui   $t2, %hi(D_800DD3DC) # $t2, 0x800e
/* 06FC00 8006F000 8D4AD3DC */  lw    $t2, %lo(D_800DD3DC)($t2)
/* 06FC04 8006F004 AC2E350C */  sw    $t6, %lo(D_8012350C)($at)
/* 06FC08 8006F008 000D7080 */  sll   $t6, $t5, 2
/* 06FC0C 8006F00C 001940C0 */  sll   $t0, $t9, 3
/* 06FC10 8006F010 000FC100 */  sll   $t8, $t7, 4
/* 06FC14 8006F014 03084821 */  addu  $t1, $t8, $t0
/* 06FC18 8006F018 01CD7021 */  addu  $t6, $t6, $t5
/* 06FC1C 8006F01C 000A5980 */  sll   $t3, $t2, 6
/* 06FC20 8006F020 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 06FC24 8006F024 012B6021 */  addu  $t4, $t1, $t3
/* 06FC28 8006F028 000E7040 */  sll   $t6, $t6, 1
/* 06FC2C 8006F02C AFBF0014 */  sw    $ra, 0x14($sp)
/* 06FC30 8006F030 018E2021 */  addu  $a0, $t4, $t6
/* 06FC34 8006F034 3C05FF00 */  lui   $a1, (0xFF0000FF >> 16) # lui $a1, 0xff00
/* 06FC38 8006F038 34A500FF */  ori   $a1, (0xFF0000FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 06FC3C 8006F03C 0C01C327 */  jal   func_80070C9C
/* 06FC40 8006F040 AFA40018 */   sw    $a0, 0x18($sp)
/* 06FC44 8006F044 3C038012 */  lui   $v1, %hi(D_801211F0) # $v1, 0x8012
/* 06FC48 8006F048 246311F0 */  addiu $v1, %lo(D_801211F0) # addiu $v1, $v1, 0x11f0
/* 06FC4C 8006F04C AC620000 */  sw    $v0, ($v1)
/* 06FC50 8006F050 3C0F800E */  lui   $t7, %hi(D_800DD3BC) # $t7, 0x800e
/* 06FC54 8006F054 8DEFD3BC */  lw    $t7, %lo(D_800DD3BC)($t7)
/* 06FC58 8006F058 3C0A800E */  lui   $t2, %hi(D_800DD3DC) # $t2, 0x800e
/* 06FC5C 8006F05C 3C0D800E */  lui   $t5, %hi(D_800DD3CC) # $t5, 0x800e
/* 06FC60 8006F060 8D4AD3DC */  lw    $t2, %lo(D_800DD3DC)($t2)
/* 06FC64 8006F064 8DADD3CC */  lw    $t5, %lo(D_800DD3CC)($t5)
/* 06FC68 8006F068 000FC8C0 */  sll   $t9, $t7, 3
/* 06FC6C 8006F06C 03224021 */  addu  $t0, $t9, $v0
/* 06FC70 8006F070 3C018012 */  lui   $at, %hi(D_80121200) # $at, 0x8012
/* 06FC74 8006F074 AC281200 */  sw    $t0, %lo(D_80121200)($at)
/* 06FC78 8006F078 000A4980 */  sll   $t1, $t2, 6
/* 06FC7C 8006F07C 000D6080 */  sll   $t4, $t5, 2
/* 06FC80 8006F080 01285821 */  addu  $t3, $t1, $t0
/* 06FC84 8006F084 3C018012 */  lui   $at, %hi(D_80121210) # $at, 0x8012
/* 06FC88 8006F088 018D6021 */  addu  $t4, $t4, $t5
/* 06FC8C 8006F08C AC2B1210 */  sw    $t3, %lo(D_80121210)($at)
/* 06FC90 8006F090 000C6040 */  sll   $t4, $t4, 1
/* 06FC94 8006F094 8FA40018 */  lw    $a0, 0x18($sp)
/* 06FC98 8006F098 018B7021 */  addu  $t6, $t4, $t3
/* 06FC9C 8006F09C 3C018012 */  lui   $at, %hi(D_80121220) # $at, 0x8012
/* 06FCA0 8006F0A0 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 06FCA4 8006F0A4 AC2E1220 */  sw    $t6, %lo(D_80121220)($at)
/* 06FCA8 8006F0A8 0C01C327 */  jal   func_80070C9C
/* 06FCAC 8006F0AC 34A500FF */   ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 06FCB0 8006F0B0 3C04800E */  lui   $a0, %hi(D_800DD3BC) # $a0, 0x800e
/* 06FCB4 8006F0B4 8C84D3BC */  lw    $a0, %lo(D_800DD3BC)($a0)
/* 06FCB8 8006F0B8 3C05800E */  lui   $a1, %hi(D_800DD3DC) # $a1, 0x800e
/* 06FCBC 8006F0BC 3C06800E */  lui   $a2, %hi(D_800DD3CC) # $a2, 0x800e
/* 06FCC0 8006F0C0 8CC6D3CC */  lw    $a2, %lo(D_800DD3CC)($a2)
/* 06FCC4 8006F0C4 8CA5D3DC */  lw    $a1, %lo(D_800DD3DC)($a1)
/* 06FCC8 8006F0C8 3C038012 */  lui   $v1, %hi(D_801211F0) # $v1, 0x8012
/* 06FCCC 8006F0CC 246311F0 */  addiu $v1, %lo(D_801211F0) # addiu $v1, $v1, 0x11f0
/* 06FCD0 8006F0D0 000478C0 */  sll   $t7, $a0, 3
/* 06FCD4 8006F0D4 AC620004 */  sw    $v0, 4($v1)
/* 06FCD8 8006F0D8 01E2C021 */  addu  $t8, $t7, $v0
/* 06FCDC 8006F0DC 3C018012 */  lui   $at, %hi(D_80121204) # $at, 0x8012
/* 06FCE0 8006F0E0 AC381204 */  sw    $t8, %lo(D_80121204)($at)
/* 06FCE4 8006F0E4 00064080 */  sll   $t0, $a2, 2
/* 06FCE8 8006F0E8 00055180 */  sll   $t2, $a1, 6
/* 06FCEC 8006F0EC 01584821 */  addu  $t1, $t2, $t8
/* 06FCF0 8006F0F0 3C018012 */  lui   $at, %hi(D_80121214) # $at, 0x8012
/* 06FCF4 8006F0F4 01064021 */  addu  $t0, $t0, $a2
/* 06FCF8 8006F0F8 AC291214 */  sw    $t1, %lo(D_80121214)($at)
/* 06FCFC 8006F0FC 00084040 */  sll   $t0, $t0, 1
/* 06FD00 8006F100 01096821 */  addu  $t5, $t0, $t1
/* 06FD04 8006F104 3C018012 */  lui   $at, %hi(D_80121224) # $at, 0x8012
/* 06FD08 8006F108 AC2D1224 */  sw    $t5, %lo(D_80121224)($at)
/* 06FD0C 8006F10C 3C018012 */  lui   $at, %hi(D_80123528) # $at, 0x8012
/* 06FD10 8006F110 AC243528 */  sw    $a0, %lo(D_80123528)($at)
/* 06FD14 8006F114 3C018012 */  lui   $at, %hi(D_8012352C) # $at, 0x8012
/* 06FD18 8006F118 3C0C800E */  lui   $t4, %hi(D_800DD3EC) # $t4, 0x800e
/* 06FD1C 8006F11C 8D8CD3EC */  lw    $t4, %lo(D_800DD3EC)($t4)
/* 06FD20 8006F120 AC25352C */  sw    $a1, %lo(D_8012352C)($at)
/* 06FD24 8006F124 3C018012 */  lui   $at, %hi(D_80123530) # $at, 0x8012
/* 06FD28 8006F128 8FBF0014 */  lw    $ra, 0x14($sp)
/* 06FD2C 8006F12C AC2C3530 */  sw    $t4, %lo(D_80123530)($at)
/* 06FD30 8006F130 3C018012 */  lui   $at, %hi(D_80123534) # $at, 0x8012
/* 06FD34 8006F134 27BD0020 */  addiu $sp, $sp, 0x20
/* 06FD38 8006F138 03E00008 */  jr    $ra
/* 06FD3C 8006F13C AC263534 */   sw    $a2, %lo(D_80123534)($at)

