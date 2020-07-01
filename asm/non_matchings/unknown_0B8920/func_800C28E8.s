glabel func_800C28E8
/* 0C34E8 800C28E8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C34EC 800C28EC AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C34F0 800C28F0 AFA5001C */  sw    $a1, 0x1c($sp)
/* 0C34F4 800C28F4 AFA60020 */  sw    $a2, 0x20($sp)
/* 0C34F8 800C28F8 0C01E948 */  jal   func_8007A520
/* 0C34FC 800C28FC AFA40018 */   sw    $a0, 0x18($sp)
/* 0C3500 800C2900 8FA40018 */  lw    $a0, 0x18($sp)
/* 0C3504 800C2904 3C18800E */  lui   $t8, %hi(D_800E31D8) # $t8, 0x800e
/* 0C3508 800C2908 8C830000 */  lw    $v1, ($a0)
/* 0C350C 800C290C 271831D8 */  addiu $t8, %lo(D_800E31D8) # addiu $t8, $t8, 0x31d8
/* 0C3510 800C2910 246E0008 */  addiu $t6, $v1, 8
/* 0C3514 800C2914 AC8E0000 */  sw    $t6, ($a0)
/* 0C3518 800C2918 3C0F0600 */  lui   $t7, 0x600
/* 0C351C 800C291C AC6F0000 */  sw    $t7, ($v1)
/* 0C3520 800C2920 AC780004 */  sw    $t8, 4($v1)
/* 0C3524 800C2924 8C830000 */  lw    $v1, ($a0)
/* 0C3528 800C2928 3C09FA00 */  lui   $t1, 0xfa00
/* 0C352C 800C292C 24790008 */  addiu $t9, $v1, 8
/* 0C3530 800C2930 AC990000 */  sw    $t9, ($a0)
/* 0C3534 800C2934 3C0A8013 */  lui   $t2, %hi(D_8012A738) # $t2, 0x8013
/* 0C3538 800C2938 AC690000 */  sw    $t1, ($v1)
/* 0C353C 800C293C 8D4AA738 */  lw    $t2, %lo(D_8012A738)($t2)
/* 0C3540 800C2940 3C0E8013 */  lui   $t6, %hi(D_8012A73C) # $t6, 0x8013
/* 0C3544 800C2944 000A6403 */  sra   $t4, $t2, 0x10
/* 0C3548 800C2948 8DCEA73C */  lw    $t6, %lo(D_8012A73C)($t6)
/* 0C354C 800C294C 3C0A8013 */  lui   $t2, %hi(D_8012A740) # $t2, 0x8013
/* 0C3550 800C2950 8D4AA740 */  lw    $t2, %lo(D_8012A740)($t2)
/* 0C3554 800C2954 000E7C03 */  sra   $t7, $t6, 0x10
/* 0C3558 800C2958 31F800FF */  andi  $t8, $t7, 0xff
/* 0C355C 800C295C 000C6E00 */  sll   $t5, $t4, 0x18
/* 0C3560 800C2960 000A5C03 */  sra   $t3, $t2, 0x10
/* 0C3564 800C2964 316C00FF */  andi  $t4, $t3, 0xff
/* 0C3568 800C2968 0018CC00 */  sll   $t9, $t8, 0x10
/* 0C356C 800C296C 01B94825 */  or    $t1, $t5, $t9
/* 0C3570 800C2970 000C7200 */  sll   $t6, $t4, 8
/* 0C3574 800C2974 012E7825 */  or    $t7, $t1, $t6
/* 0C3578 800C2978 35F800FF */  ori   $t8, $t7, 0xff
/* 0C357C 800C297C AC780004 */  sw    $t8, 4($v1)
/* 0C3580 800C2980 8C830000 */  lw    $v1, ($a0)
/* 0C3584 800C2984 3C19FCFF */  lui   $t9, (0xFCFFFFFF >> 16) # lui $t9, 0xfcff
/* 0C3588 800C2988 246D0008 */  addiu $t5, $v1, 8
/* 0C358C 800C298C 3C0AFFFD */  lui   $t2, (0xFFFDF6FB >> 16) # lui $t2, 0xfffd
/* 0C3590 800C2990 AC8D0000 */  sw    $t5, ($a0)
/* 0C3594 800C2994 354AF6FB */  ori   $t2, (0xFFFDF6FB & 0xFFFF) # ori $t2, $t2, 0xf6fb
/* 0C3598 800C2998 3739FFFF */  ori   $t9, (0xFCFFFFFF & 0xFFFF) # ori $t9, $t9, 0xffff
/* 0C359C 800C299C AC790000 */  sw    $t9, ($v1)
/* 0C35A0 800C29A0 AC6A0004 */  sw    $t2, 4($v1)
/* 0C35A4 800C29A4 8C830000 */  lw    $v1, ($a0)
/* 0C35A8 800C29A8 00026C03 */  sra   $t5, $v0, 0x10
/* 0C35AC 800C29AC 304903FF */  andi  $t1, $v0, 0x3ff
/* 0C35B0 800C29B0 00097380 */  sll   $t6, $t1, 0xe
/* 0C35B4 800C29B4 31B903FF */  andi  $t9, $t5, 0x3ff
/* 0C35B8 800C29B8 3C01F600 */  lui   $at, 0xf600
/* 0C35BC 800C29BC 246B0008 */  addiu $t3, $v1, 8
/* 0C35C0 800C29C0 01C17825 */  or    $t7, $t6, $at
/* 0C35C4 800C29C4 00195080 */  sll   $t2, $t9, 2
/* 0C35C8 800C29C8 AC8B0000 */  sw    $t3, ($a0)
/* 0C35CC 800C29CC 01EA5825 */  or    $t3, $t7, $t2
/* 0C35D0 800C29D0 AC6B0000 */  sw    $t3, ($v1)
/* 0C35D4 800C29D4 0C01ECF4 */  jal   func_8007B3D0
/* 0C35D8 800C29D8 AC600004 */   sw    $zero, 4($v1)
/* 0C35DC 800C29DC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C35E0 800C29E0 27BD0018 */  addiu $sp, $sp, 0x18
/* 0C35E4 800C29E4 03E00008 */  jr    $ra
/* 0C35E8 800C29E8 00000000 */   nop   

/* 0C35EC 800C29EC 00000000 */  nop   
