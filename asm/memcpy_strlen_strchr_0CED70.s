.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel memcpy
/* 0CED70 800CE170 00801025 */  move  $v0, $a0
/* 0CED74 800CE174 10C00007 */  beqz  $a2, .L800CE194
/* 0CED78 800CE178 00A01825 */   move  $v1, $a1
.L800CE17C:
/* 0CED7C 800CE17C 906E0000 */  lbu   $t6, ($v1)
/* 0CED80 800CE180 24C6FFFF */  addiu $a2, $a2, -1
/* 0CED84 800CE184 24420001 */  addiu $v0, $v0, 1
/* 0CED88 800CE188 24630001 */  addiu $v1, $v1, 1
/* 0CED8C 800CE18C 14C0FFFB */  bnez  $a2, .L800CE17C
/* 0CED90 800CE190 A04EFFFF */   sb    $t6, -1($v0)
.L800CE194:
/* 0CED94 800CE194 03E00008 */  jr    $ra
/* 0CED98 800CE198 00801025 */   move  $v0, $a0

glabel strlen
/* 0CED9C 800CE19C 908E0000 */  lbu   $t6, ($a0)
/* 0CEDA0 800CE1A0 00801825 */  move  $v1, $a0
/* 0CEDA4 800CE1A4 11C00005 */  beqz  $t6, .L800CE1BC
/* 0CEDA8 800CE1A8 00000000 */   nop   
/* 0CEDAC 800CE1AC 906F0001 */  lbu   $t7, 1($v1)
.L800CE1B0:
/* 0CEDB0 800CE1B0 24630001 */  addiu $v1, $v1, 1
/* 0CEDB4 800CE1B4 55E0FFFE */  bnezl $t7, .L800CE1B0
/* 0CEDB8 800CE1B8 906F0001 */   lbu   $t7, 1($v1)
.L800CE1BC:
/* 0CEDBC 800CE1BC 03E00008 */  jr    $ra
/* 0CEDC0 800CE1C0 00641023 */   subu  $v0, $v1, $a0

glabel strchr
/* 0CEDC4 800CE1C4 90830000 */  lbu   $v1, ($a0)
/* 0CEDC8 800CE1C8 30AE00FF */  andi  $t6, $a1, 0xff
/* 0CEDCC 800CE1CC 30A200FF */  andi  $v0, $a1, 0xff
/* 0CEDD0 800CE1D0 51C3000A */  beql  $t6, $v1, .L800CE1FC
/* 0CEDD4 800CE1D4 00801025 */   move  $v0, $a0
.L800CE1D8:
/* 0CEDD8 800CE1D8 54600004 */  bnezl $v1, .L800CE1EC
/* 0CEDDC 800CE1DC 90830001 */   lbu   $v1, 1($a0)
/* 0CEDE0 800CE1E0 03E00008 */  jr    $ra
/* 0CEDE4 800CE1E4 00001025 */   move  $v0, $zero

/* 0CEDE8 800CE1E8 90830001 */  lbu   $v1, 1($a0)
.L800CE1EC:
/* 0CEDEC 800CE1EC 24840001 */  addiu $a0, $a0, 1
/* 0CEDF0 800CE1F0 1443FFF9 */  bne   $v0, $v1, .L800CE1D8
/* 0CEDF4 800CE1F4 00000000 */   nop   
/* 0CEDF8 800CE1F8 00801025 */  move  $v0, $a0
.L800CE1FC:
/* 0CEDFC 800CE1FC 03E00008 */  jr    $ra
/* 0CEE00 800CE200 00000000 */   nop   

/* 0CEE04 800CE204 00000000 */  nop   
/* 0CEE08 800CE208 00000000 */  nop   
/* 0CEE0C 800CE20C 00000000 */  nop   
