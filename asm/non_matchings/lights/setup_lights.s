glabel setup_lights
/* 0327B8 80031BB8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0327BC 80031BBC AFBF0014 */  sw    $ra, 0x14($sp)
/* 0327C0 80031BC0 0C00C6D8 */  jal   free_lights
/* 0327C4 80031BC4 AFA40018 */   sw    $a0, 0x18($sp)
/* 0327C8 80031BC8 8FAE0018 */  lw    $t6, 0x18($sp)
/* 0327CC 80031BCC 3C06800E */  lui   $a2, %hi(gMaxLights) # $a2, 0x800e
/* 0327D0 80031BD0 000E7880 */  sll   $t7, $t6, 2
/* 0327D4 80031BD4 01EE7823 */  subu  $t7, $t7, $t6
/* 0327D8 80031BD8 000F7880 */  sll   $t7, $t7, 2
/* 0327DC 80031BDC 01EE7823 */  subu  $t7, $t7, $t6
/* 0327E0 80031BE0 000F7880 */  sll   $t7, $t7, 2
/* 0327E4 80031BE4 24C6C958 */  addiu $a2, %lo(gMaxLights) # addiu $a2, $a2, -0x36a8
/* 0327E8 80031BE8 3C05FF00 */  lui   $a1, (0xFF00FFFF >> 16) # lui $a1, 0xff00
/* 0327EC 80031BEC 01EE7823 */  subu  $t7, $t7, $t6
/* 0327F0 80031BF0 000F2080 */  sll   $a0, $t7, 2
/* 0327F4 80031BF4 34A5FFFF */  ori   $a1, (0xFF00FFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 0327F8 80031BF8 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0327FC 80031BFC ACCE0000 */   sw    $t6, ($a2)
/* 032800 80031C00 3C06800E */  lui   $a2, %hi(gMaxLights) # $a2, 0x800e
/* 032804 80031C04 24C6C958 */  addiu $a2, %lo(gMaxLights) # addiu $a2, $a2, -0x36a8
/* 032808 80031C08 8CC80000 */  lw    $t0, ($a2)
/* 03280C 80031C0C 3C05800E */  lui   $a1, %hi(D_800DC954) # $a1, 0x800e
/* 032810 80031C10 00085900 */  sll   $t3, $t0, 4
/* 032814 80031C14 0008C080 */  sll   $t8, $t0, 2
/* 032818 80031C18 01685821 */  addu  $t3, $t3, $t0
/* 03281C 80031C1C 0058C821 */  addu  $t9, $v0, $t8
/* 032820 80031C20 000B58C0 */  sll   $t3, $t3, 3
/* 032824 80031C24 00087080 */  sll   $t6, $t0, 2
/* 032828 80031C28 3C07800E */  lui   $a3, %hi(gActiveLights) # $a3, 0x800e
/* 03282C 80031C2C 3C09800E */  lui   $t1, %hi(D_800DC960) # $t1, 0x800e
/* 032830 80031C30 032B6021 */  addu  $t4, $t9, $t3
/* 032834 80031C34 01C87021 */  addu  $t6, $t6, $t0
/* 032838 80031C38 2529C960 */  addiu $t1, %lo(D_800DC960) # addiu $t1, $t1, -0x36a0
/* 03283C 80031C3C 24E7C950 */  addiu $a3, %lo(gActiveLights) # addiu $a3, $a3, -0x36b0
/* 032840 80031C40 24A5C954 */  addiu $a1, %lo(D_800DC954) # addiu $a1, $a1, -0x36ac
/* 032844 80031C44 000E7080 */  sll   $t6, $t6, 2
/* 032848 80031C48 ACE20000 */  sw    $v0, ($a3)
/* 03284C 80031C4C ACB90000 */  sw    $t9, ($a1)
/* 032850 80031C50 AD2C0000 */  sw    $t4, ($t1)
/* 032854 80031C54 018E7821 */  addu  $t7, $t4, $t6
/* 032858 80031C58 3C01800E */  lui   $at, %hi(D_800DC964) # $at, 0x800e
/* 03285C 80031C5C AC2FC964 */  sw    $t7, %lo(D_800DC964)($at)
/* 032860 80031C60 1900000E */  blez  $t0, .L80031C9C
/* 032864 80031C64 00001825 */   move  $v1, $zero
/* 032868 80031C68 00001025 */  move  $v0, $zero
/* 03286C 80031C6C 00002025 */  move  $a0, $zero
.L80031C70:
/* 032870 80031C70 8CB80000 */  lw    $t8, ($a1)
/* 032874 80031C74 8CEA0000 */  lw    $t2, ($a3)
/* 032878 80031C78 0098C821 */  addu  $t9, $a0, $t8
/* 03287C 80031C7C 01425821 */  addu  $t3, $t2, $v0
/* 032880 80031C80 AD790000 */  sw    $t9, ($t3)
/* 032884 80031C84 8CCC0000 */  lw    $t4, ($a2)
/* 032888 80031C88 24630001 */  addiu $v1, $v1, 1
/* 03288C 80031C8C 006C082A */  slt   $at, $v1, $t4
/* 032890 80031C90 24420004 */  addiu $v0, $v0, 4
/* 032894 80031C94 1420FFF6 */  bnez  $at, .L80031C70
/* 032898 80031C98 24840088 */   addiu $a0, $a0, 0x88
.L80031C9C:
/* 03289C 80031C9C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0328A0 80031CA0 27BD0018 */  addiu $sp, $sp, 0x18
/* 0328A4 80031CA4 03E00008 */  jr    $ra
/* 0328A8 80031CA8 00000000 */   nop   

