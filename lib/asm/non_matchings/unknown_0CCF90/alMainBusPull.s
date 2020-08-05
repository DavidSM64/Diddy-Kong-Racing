glabel alMainBusPull
/* 0CCFC0 800CC3C0 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0CCFC4 800CC3C4 8FA80058 */  lw    $t0, 0x58($sp)
/* 0CCFC8 800CC3C8 AFBF0044 */  sw    $ra, 0x44($sp)
/* 0CCFCC 800CC3CC AFBE0040 */  sw    $fp, 0x40($sp)
/* 0CCFD0 800CC3D0 AFB7003C */  sw    $s7, 0x3c($sp)
/* 0CCFD4 800CC3D4 AFB60038 */  sw    $s6, 0x38($sp)
/* 0CCFD8 800CC3D8 AFB50034 */  sw    $s5, 0x34($sp)
/* 0CCFDC 800CC3DC AFB40030 */  sw    $s4, 0x30($sp)
/* 0CCFE0 800CC3E0 AFB3002C */  sw    $s3, 0x2c($sp)
/* 0CCFE4 800CC3E4 AFB20028 */  sw    $s2, 0x28($sp)
/* 0CCFE8 800CC3E8 AFB10024 */  sw    $s1, 0x24($sp)
/* 0CCFEC 800CC3EC AFB00020 */  sw    $s0, 0x20($sp)
/* 0CCFF0 800CC3F0 8C83001C */  lw    $v1, 0x1c($a0)
/* 0CCFF4 800CC3F4 3C0E0200 */  lui   $t6, (0x02000440 >> 16) # lui $t6, 0x200
/* 0CCFF8 800CC3F8 00061040 */  sll   $v0, $a2, 1
/* 0CCFFC 800CC3FC 3C0F0200 */  lui   $t7, (0x02000580 >> 16) # lui $t7, 0x200
/* 0CD000 800CC400 35CE0440 */  ori   $t6, (0x02000440 & 0xFFFF) # ori $t6, $t6, 0x440
/* 0CD004 800CC404 35EF0580 */  ori   $t7, (0x02000580 & 0xFFFF) # ori $t7, $t7, 0x580
/* 0CD008 800CC408 AD0E0000 */  sw    $t6, ($t0)
/* 0CD00C 800CC40C AD020004 */  sw    $v0, 4($t0)
/* 0CD010 800CC410 AD0F0008 */  sw    $t7, 8($t0)
/* 0CD014 800CC414 AD02000C */  sw    $v0, 0xc($t0)
/* 0CD018 800CC418 8C980014 */  lw    $t8, 0x14($a0)
/* 0CD01C 800CC41C 00C0A825 */  move  $s5, $a2
/* 0CD020 800CC420 00A0B825 */  move  $s7, $a1
/* 0CD024 800CC424 00E0F025 */  move  $fp, $a3
/* 0CD028 800CC428 0080A025 */  move  $s4, $a0
/* 0CD02C 800CC42C 00008025 */  move  $s0, $zero
/* 0CD030 800CC430 1B00001E */  blez  $t8, .L800CC4AC
/* 0CD034 800CC434 25130010 */   addiu $s3, $t0, 0x10
/* 0CD038 800CC438 3C120C00 */  lui   $s2, (0x0C007FFF >> 16) # lui $s2, 0xc00
/* 0CD03C 800CC43C 36527FFF */  ori   $s2, (0x0C007FFF & 0xFFFF) # ori $s2, $s2, 0x7fff
/* 0CD040 800CC440 00608825 */  move  $s1, $v1
/* 0CD044 800CC444 3056FFFF */  andi  $s6, $v0, 0xffff
.L800CC448:
/* 0CD048 800CC448 8E240000 */  lw    $a0, ($s1)
/* 0CD04C 800CC44C AFB30010 */  sw    $s3, 0x10($sp)
/* 0CD050 800CC450 02E02825 */  move  $a1, $s7
/* 0CD054 800CC454 8C990004 */  lw    $t9, 4($a0)
/* 0CD058 800CC458 02A03025 */  move  $a2, $s5
/* 0CD05C 800CC45C 03C03825 */  move  $a3, $fp
/* 0CD060 800CC460 0320F809 */  jalr  $t9
/* 0CD064 800CC464 00000000 */  nop   
/* 0CD068 800CC468 3C0A06C0 */  lui   $t2, (0x06C00440 >> 16) # lui $t2, 0x6c0
/* 0CD06C 800CC46C 3C0B0800 */  lui   $t3, (0x08000580 >> 16) # lui $t3, 0x800
/* 0CD070 800CC470 3C090800 */  lui   $t1, 0x800
/* 0CD074 800CC474 354A0440 */  ori   $t2, (0x06C00440 & 0xFFFF) # ori $t2, $t2, 0x440
/* 0CD078 800CC478 356B0580 */  ori   $t3, (0x08000580 & 0xFFFF) # ori $t3, $t3, 0x580
/* 0CD07C 800CC47C AC490000 */  sw    $t1, ($v0)
/* 0CD080 800CC480 AC560004 */  sw    $s6, 4($v0)
/* 0CD084 800CC484 AC4A000C */  sw    $t2, 0xc($v0)
/* 0CD088 800CC488 AC520008 */  sw    $s2, 8($v0)
/* 0CD08C 800CC48C AC4B0014 */  sw    $t3, 0x14($v0)
/* 0CD090 800CC490 AC520010 */  sw    $s2, 0x10($v0)
/* 0CD094 800CC494 8E8C0014 */  lw    $t4, 0x14($s4)
/* 0CD098 800CC498 26100001 */  addiu $s0, $s0, 1
/* 0CD09C 800CC49C 26310004 */  addiu $s1, $s1, 4
/* 0CD0A0 800CC4A0 020C082A */  slt   $at, $s0, $t4
/* 0CD0A4 800CC4A4 1420FFE8 */  bnez  $at, .L800CC448
/* 0CD0A8 800CC4A8 24530018 */   addiu $s3, $v0, 0x18
.L800CC4AC:
/* 0CD0AC 800CC4AC 8FBF0044 */  lw    $ra, 0x44($sp)
/* 0CD0B0 800CC4B0 02601025 */  move  $v0, $s3
/* 0CD0B4 800CC4B4 8FB3002C */  lw    $s3, 0x2c($sp)
/* 0CD0B8 800CC4B8 8FB00020 */  lw    $s0, 0x20($sp)
/* 0CD0BC 800CC4BC 8FB10024 */  lw    $s1, 0x24($sp)
/* 0CD0C0 800CC4C0 8FB20028 */  lw    $s2, 0x28($sp)
/* 0CD0C4 800CC4C4 8FB40030 */  lw    $s4, 0x30($sp)
/* 0CD0C8 800CC4C8 8FB50034 */  lw    $s5, 0x34($sp)
/* 0CD0CC 800CC4CC 8FB60038 */  lw    $s6, 0x38($sp)
/* 0CD0D0 800CC4D0 8FB7003C */  lw    $s7, 0x3c($sp)
/* 0CD0D4 800CC4D4 8FBE0040 */  lw    $fp, 0x40($sp)
/* 0CD0D8 800CC4D8 03E00008 */  jr    $ra
/* 0CD0DC 800CC4DC 27BD0048 */   addiu $sp, $sp, 0x48

