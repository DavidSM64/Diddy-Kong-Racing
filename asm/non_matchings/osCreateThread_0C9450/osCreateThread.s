glabel osCreateThread
/* 0C9450 800C8850 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C9454 800C8854 AFA40028 */  sw    $a0, 0x28($sp)
/* 0C9458 800C8858 AFA5002C */  sw    $a1, 0x2c($sp)
/* 0C945C 800C885C 8FAE002C */  lw    $t6, 0x2c($sp)
/* 0C9460 800C8860 8FAF0028 */  lw    $t7, 0x28($sp)
/* 0C9464 800C8864 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0C9468 800C8868 AFA60030 */  sw    $a2, 0x30($sp)
/* 0C946C 800C886C AFA70034 */  sw    $a3, 0x34($sp)
/* 0C9470 800C8870 AFB00018 */  sw    $s0, 0x18($sp)
/* 0C9474 800C8874 ADEE0014 */  sw    $t6, 0x14($t7)
/* 0C9478 800C8878 8FB90028 */  lw    $t9, 0x28($sp)
/* 0C947C 800C887C 8FB8003C */  lw    $t8, 0x3c($sp)
/* 0C9480 800C8880 AF380004 */  sw    $t8, 4($t9)
/* 0C9484 800C8884 8FA80028 */  lw    $t0, 0x28($sp)
/* 0C9488 800C8888 AD000000 */  sw    $zero, ($t0)
/* 0C948C 800C888C 8FA90028 */  lw    $t1, 0x28($sp)
/* 0C9490 800C8890 AD200008 */  sw    $zero, 8($t1)
/* 0C9494 800C8894 8FAB0028 */  lw    $t3, 0x28($sp)
/* 0C9498 800C8898 8FAA0030 */  lw    $t2, 0x30($sp)
/* 0C949C 800C889C AD6A011C */  sw    $t2, 0x11c($t3)
/* 0C94A0 800C88A0 8FAC0034 */  lw    $t4, 0x34($sp)
/* 0C94A4 800C88A4 8FAD0028 */  lw    $t5, 0x28($sp)
/* 0C94A8 800C88A8 01807825 */  move  $t7, $t4
/* 0C94AC 800C88AC 000C77C3 */  sra   $t6, $t4, 0x1f
/* 0C94B0 800C88B0 ADAE0038 */  sw    $t6, 0x38($t5)
/* 0C94B4 800C88B4 ADAF003C */  sw    $t7, 0x3c($t5)
/* 0C94B8 800C88B8 8FB80038 */  lw    $t8, 0x38($sp)
/* 0C94BC 800C88BC 8FB90028 */  lw    $t9, 0x28($sp)
/* 0C94C0 800C88C0 3C0C800D */  lui   $t4, %hi(D_800D35A0) # $t4, 0x800d
/* 0C94C4 800C88C4 03004825 */  move  $t1, $t8
/* 0C94C8 800C88C8 2D210010 */  sltiu $at, $t1, 0x10
/* 0C94CC 800C88CC 001847C3 */  sra   $t0, $t8, 0x1f
/* 0C94D0 800C88D0 01015023 */  subu  $t2, $t0, $at
/* 0C94D4 800C88D4 252BFFF0 */  addiu $t3, $t1, -0x10
/* 0C94D8 800C88D8 AF2B00F4 */  sw    $t3, 0xf4($t9)
/* 0C94DC 800C88DC AF2A00F0 */  sw    $t2, 0xf0($t9)
/* 0C94E0 800C88E0 8FAD0028 */  lw    $t5, 0x28($sp)
/* 0C94E4 800C88E4 258C35A0 */  addiu $t4, %lo(D_800D35A0) # addiu $t4, $t4, 0x35a0
/* 0C94E8 800C88E8 01807825 */  move  $t7, $t4
/* 0C94EC 800C88EC 000C77C3 */  sra   $t6, $t4, 0x1f
/* 0C94F0 800C88F0 ADAE0100 */  sw    $t6, 0x100($t5)
/* 0C94F4 800C88F4 ADAF0104 */  sw    $t7, 0x104($t5)
/* 0C94F8 800C88F8 8FA90028 */  lw    $t1, 0x28($sp)
/* 0C94FC 800C88FC 3C18003F */  lui   $t8, (0x003FFF01 >> 16) # lui $t8, 0x3f
/* 0C9500 800C8900 3718FF01 */  ori   $t8, (0x003FFF01 & 0xFFFF) # ori $t8, $t8, 0xff01
/* 0C9504 800C8904 AFB80020 */  sw    $t8, 0x20($sp)
/* 0C9508 800C8908 3408FF03 */  li    $t0, 65283
/* 0C950C 800C890C AD280118 */  sw    $t0, 0x118($t1)
/* 0C9510 800C8910 8FAA0020 */  lw    $t2, 0x20($sp)
/* 0C9514 800C8914 8FAC0028 */  lw    $t4, 0x28($sp)
/* 0C9518 800C8918 3C01003F */  lui   $at, 0x3f
/* 0C951C 800C891C 01415824 */  and   $t3, $t2, $at
/* 0C9520 800C8920 000BCC02 */  srl   $t9, $t3, 0x10
/* 0C9524 800C8924 AD990128 */  sw    $t9, 0x128($t4)
/* 0C9528 800C8928 8FAF0028 */  lw    $t7, 0x28($sp)
/* 0C952C 800C892C 3C0E0100 */  lui   $t6, (0x01000800 >> 16) # lui $t6, 0x100
/* 0C9530 800C8930 35CE0800 */  ori   $t6, (0x01000800 & 0xFFFF) # ori $t6, $t6, 0x800
/* 0C9534 800C8934 ADEE012C */  sw    $t6, 0x12c($t7)
/* 0C9538 800C8938 8FAD0028 */  lw    $t5, 0x28($sp)
/* 0C953C 800C893C 24180001 */  li    $t8, 1
/* 0C9540 800C8940 ADA00018 */  sw    $zero, 0x18($t5)
/* 0C9544 800C8944 8FA80028 */  lw    $t0, 0x28($sp)
/* 0C9548 800C8948 A5180010 */  sh    $t8, 0x10($t0)
/* 0C954C 800C894C 8FA90028 */  lw    $t1, 0x28($sp)
/* 0C9550 800C8950 0C034958 */  jal   __osDisableInt
/* 0C9554 800C8954 A5200012 */   sh    $zero, 0x12($t1)
/* 0C9558 800C8958 3C0A800E */  lui   $t2, %hi(D_800E488C) # $t2, 0x800e
/* 0C955C 800C895C 8D4A488C */  lw    $t2, %lo(D_800E488C)($t2)
/* 0C9560 800C8960 8FAB0028 */  lw    $t3, 0x28($sp)
/* 0C9564 800C8964 00408025 */  move  $s0, $v0
/* 0C9568 800C8968 3C01800E */  lui   $at, %hi(D_800E488C) # $at, 0x800e
/* 0C956C 800C896C AD6A000C */  sw    $t2, 0xc($t3)
/* 0C9570 800C8970 8FB90028 */  lw    $t9, 0x28($sp)
/* 0C9574 800C8974 02002025 */  move  $a0, $s0
/* 0C9578 800C8978 0C034960 */  jal   __osRestoreInt
/* 0C957C 800C897C AC39488C */   sw    $t9, %lo(D_800E488C)($at)
/* 0C9580 800C8980 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0C9584 800C8984 8FB00018 */  lw    $s0, 0x18($sp)
/* 0C9588 800C8988 27BD0028 */  addiu $sp, $sp, 0x28
/* 0C958C 800C898C 03E00008 */  jr    $ra
/* 0C9590 800C8990 00000000 */   nop   

/* 0C9594 800C8994 00000000 */  nop   
/* 0C9598 800C8998 00000000 */  nop   
/* 0C959C 800C899C 00000000 */  nop   

