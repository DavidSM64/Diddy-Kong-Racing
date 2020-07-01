glabel D_800CC514
/* 0CD114 800CC514 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0CD118 800CC518 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0CD11C 800CC51C AFA40020 */  sw    $a0, 0x20($sp)
/* 0CD120 800CC520 8C840000 */  lw    $a0, ($a0)
/* 0CD124 800CC524 8FAF0030 */  lw    $t7, 0x30($sp)
/* 0CD128 800CC528 AFA60028 */  sw    $a2, 0x28($sp)
/* 0CD12C 800CC52C AFAF0010 */  sw    $t7, 0x10($sp)
/* 0CD130 800CC530 8C990004 */  lw    $t9, 4($a0)
/* 0CD134 800CC534 0320F809 */  jalr  $t9
/* 0CD138 800CC538 00000000 */  nop   
/* 0CD13C 800CC53C 8FA60028 */  lw    $a2, 0x28($sp)
/* 0CD140 800CC540 3C030800 */  lui   $v1, 0x800
/* 0CD144 800CC544 3C0A0440 */  lui   $t2, (0x04400580 >> 16) # lui $t2, 0x440
/* 0CD148 800CC548 0006C040 */  sll   $t8, $a2, 1
/* 0CD14C 800CC54C 00065880 */  sll   $t3, $a2, 2
/* 0CD150 800CC550 3308FFFF */  andi  $t0, $t8, 0xffff
/* 0CD154 800CC554 354A0580 */  ori   $t2, (0x04400580 & 0xFFFF) # ori $t2, $t2, 0x580
/* 0CD158 800CC558 3C090D00 */  lui   $t1, 0xd00
/* 0CD15C 800CC55C 316CFFFF */  andi  $t4, $t3, 0xffff
/* 0CD160 800CC560 3C0D0600 */  lui   $t5, 0x600
/* 0CD164 800CC564 AC480004 */  sw    $t0, 4($v0)
/* 0CD168 800CC568 AC430000 */  sw    $v1, ($v0)
/* 0CD16C 800CC56C AC490008 */  sw    $t1, 8($v0)
/* 0CD170 800CC570 AC4A000C */  sw    $t2, 0xc($v0)
/* 0CD174 800CC574 AC4C0014 */  sw    $t4, 0x14($v0)
/* 0CD178 800CC578 AC430010 */  sw    $v1, 0x10($v0)
/* 0CD17C 800CC57C AC4D0018 */  sw    $t5, 0x18($v0)
/* 0CD180 800CC580 8FAE0020 */  lw    $t6, 0x20($sp)
/* 0CD184 800CC584 24420020 */  addiu $v0, $v0, 0x20
/* 0CD188 800CC588 8DCF0014 */  lw    $t7, 0x14($t6)
/* 0CD18C 800CC58C AC4FFFFC */  sw    $t7, -4($v0)
/* 0CD190 800CC590 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0CD194 800CC594 27BD0020 */  addiu $sp, $sp, 0x20
/* 0CD198 800CC598 03E00008 */  jr    $ra
/* 0CD19C 800CC59C 00000000 */   nop   

