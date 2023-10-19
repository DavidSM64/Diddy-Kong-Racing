glabel func_800B7460
/* 0B8060 800B7460 27BDF610 */  addiu $sp, $sp, -0x9f0
/* 0B8064 800B7464 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B8068 800B7468 AFA409F0 */  sw    $a0, 0x9f0($sp)
/* 0B806C 800B746C AFA509F4 */  sw    $a1, 0x9f4($sp)
/* 0B8070 800B7470 0C0270C3 */  jal   get_filtered_cheats
/* 0B8074 800B7474 AFA609F8 */   sw    $a2, 0x9f8($sp)
/* 0B8078 800B7478 00027100 */  sll   $t6, $v0, 4
/* 0B807C 800B747C 05C1008A */  bgez  $t6, .L800B76A8
/* 0B8080 800B7480 27A40840 */   addiu $a0, $sp, 0x840
/* 0B8084 800B7484 0C034138 */  jal   bzero
/* 0B8088 800B7488 240501B0 */   li    $a1, 432
/* 0B808C 800B748C 3C028013 */  lui   $v0, %hi(gObjectStackTrace) # $v0, 0x8013
/* 0B8090 800B7490 24429FB0 */  addiu $v0, %lo(gObjectStackTrace) # addiu $v0, $v0, -0x6050
/* 0B8094 800B7494 8C580000 */  lw    $t8, ($v0)
/* 0B8098 800B7498 8C590004 */  lw    $t9, 4($v0)
/* 0B809C 800B749C 8C480008 */  lw    $t0, 8($v0)
/* 0B80A0 800B74A0 44982000 */  mtc1  $t8, $f4
/* 0B80A4 800B74A4 44994000 */  mtc1  $t9, $f8
/* 0B80A8 800B74A8 44888000 */  mtc1  $t0, $f16
/* 0B80AC 800B74AC 8FA909F4 */  lw    $t1, 0x9f4($sp)
/* 0B80B0 800B74B0 468021A0 */  cvt.s.w $f6, $f4
/* 0B80B4 800B74B4 8FAF09F0 */  lw    $t7, 0x9f0($sp)
/* 0B80B8 800B74B8 8FAC09F8 */  lw    $t4, 0x9f8($sp)
/* 0B80BC 800B74BC 468042A0 */  cvt.s.w $f10, $f8
/* 0B80C0 800B74C0 240E0000 */  li    $t6, 0
/* 0B80C4 800B74C4 240DFFFF */  li    $t5, -1
/* 0B80C8 800B74C8 468084A0 */  cvt.s.w $f18, $f16
/* 0B80CC 800B74CC 000957C3 */  sra   $t2, $t1, 0x1f
/* 0B80D0 800B74D0 AFAA0878 */  sw    $t2, 0x878($sp)
/* 0B80D4 800B74D4 AFAE0880 */  sw    $t6, 0x880($sp)
/* 0B80D8 800B74D8 AFAD0960 */  sw    $t5, 0x960($sp)
/* 0B80DC 800B74DC E7A60970 */  swc1  $f6, 0x970($sp)
/* 0B80E0 800B74E0 E7AA0974 */  swc1  $f10, 0x974($sp)
/* 0B80E4 800B74E4 E7B20978 */  swc1  $f18, 0x978($sp)
/* 0B80E8 800B74E8 27A40840 */  addiu $a0, $sp, 0x840
/* 0B80EC 800B74EC 27A50040 */  addiu $a1, $sp, 0x40
/* 0B80F0 800B74F0 240601B0 */  li    $a2, 432
/* 0B80F4 800B74F4 AFA9087C */  sw    $t1, 0x87c($sp)
/* 0B80F8 800B74F8 AFAF095C */  sw    $t7, 0x95c($sp)
/* 0B80FC 800B74FC 0C032768 */  jal   bcopy
/* 0B8100 800B7500 AFAC0884 */   sw    $t4, 0x884($sp)
/* 0B8104 800B7504 27A40240 */  addiu $a0, $sp, 0x240
/* 0B8108 800B7508 0C034138 */  jal   bzero
/* 0B810C 800B750C 24050200 */   li    $a1, 512
/* 0B8110 800B7510 27A40038 */  addiu $a0, $sp, 0x38
/* 0B8114 800B7514 0C009165 */  jal   func_80024594
/* 0B8118 800B7518 27A509F4 */   addiu $a1, $sp, 0x9f4
/* 0B811C 800B751C 8FA909F4 */  lw    $t1, 0x9f4($sp)
/* 0B8120 800B7520 00002825 */  move  $a1, $zero
/* 0B8124 800B7524 19200054 */  blez  $t1, .L800B7678
/* 0B8128 800B7528 3C07800F */   lui   $a3, %hi(sCoreFileExt) # $a3, 0x800f
/* 0B812C 800B752C 31260003 */  andi  $a2, $t1, 3
/* 0B8130 800B7530 10C00018 */  beqz  $a2, .L800B7594
/* 0B8134 800B7534 00C01825 */   move  $v1, $a2
/* 0B8138 800B7538 00005040 */  sll   $t2, $zero, 1
/* 0B813C 800B753C 27AB0440 */  addiu $t3, $sp, 0x440
/* 0B8140 800B7540 014B2021 */  addu  $a0, $t2, $t3
.L800B7544:
/* 0B8144 800B7544 8FAC0038 */  lw    $t4, 0x38($sp)
/* 0B8148 800B7548 24A50001 */  addiu $a1, $a1, 1
/* 0B814C 800B754C 000C7040 */  sll   $t6, $t4, 1
/* 0B8150 800B7550 004E7821 */  addu  $t7, $v0, $t6
/* 0B8154 800B7554 85ED0000 */  lh    $t5, ($t7)
/* 0B8158 800B7558 00000000 */  nop   
/* 0B815C 800B755C A48D0000 */  sh    $t5, ($a0)
/* 0B8160 800B7560 8FB80038 */  lw    $t8, 0x38($sp)
/* 0B8164 800B7564 8FA809F4 */  lw    $t0, 0x9f4($sp)
/* 0B8168 800B7568 2719FFFF */  addiu $t9, $t8, -1
/* 0B816C 800B756C 07210003 */  bgez  $t9, .L800B757C
/* 0B8170 800B7570 AFB90038 */   sw    $t9, 0x38($sp)
/* 0B8174 800B7574 03283021 */  addu  $a2, $t9, $t0
/* 0B8178 800B7578 AFA60038 */  sw    $a2, 0x38($sp)
.L800B757C:
/* 0B817C 800B757C 8FA60038 */  lw    $a2, 0x38($sp)
/* 0B8180 800B7580 1465FFF0 */  bne   $v1, $a1, .L800B7544
/* 0B8184 800B7584 24840002 */   addiu $a0, $a0, 2
/* 0B8188 800B7588 8FA909F4 */  lw    $t1, 0x9f4($sp)
/* 0B818C 800B758C AFA60038 */  sw    $a2, 0x38($sp)
/* 0B8190 800B7590 10A90039 */  beq   $a1, $t1, .L800B7678
.L800B7594:
/* 0B8194 800B7594 00055040 */   sll   $t2, $a1, 1
/* 0B8198 800B7598 27AB0440 */  addiu $t3, $sp, 0x440
/* 0B819C 800B759C 014B2021 */  addu  $a0, $t2, $t3
.L800B75A0:
/* 0B81A0 800B75A0 8FAC0038 */  lw    $t4, 0x38($sp)
/* 0B81A4 800B75A4 00000000 */  nop   
/* 0B81A8 800B75A8 000C7040 */  sll   $t6, $t4, 1
/* 0B81AC 800B75AC 004E1821 */  addu  $v1, $v0, $t6
/* 0B81B0 800B75B0 846F0000 */  lh    $t7, ($v1)
/* 0B81B4 800B75B4 2463FFFE */  addiu $v1, $v1, -2
/* 0B81B8 800B75B8 A48F0000 */  sh    $t7, ($a0)
/* 0B81BC 800B75BC 8FAD0038 */  lw    $t5, 0x38($sp)
/* 0B81C0 800B75C0 8FB909F4 */  lw    $t9, 0x9f4($sp)
/* 0B81C4 800B75C4 25B8FFFF */  addiu $t8, $t5, -1
/* 0B81C8 800B75C8 07010005 */  bgez  $t8, .L800B75E0
/* 0B81CC 800B75CC AFB80038 */   sw    $t8, 0x38($sp)
/* 0B81D0 800B75D0 03193021 */  addu  $a2, $t8, $t9
/* 0B81D4 800B75D4 00064040 */  sll   $t0, $a2, 1
/* 0B81D8 800B75D8 00481821 */  addu  $v1, $v0, $t0
/* 0B81DC 800B75DC AFA60038 */  sw    $a2, 0x38($sp)
.L800B75E0:
/* 0B81E0 800B75E0 84690000 */  lh    $t1, ($v1)
/* 0B81E4 800B75E4 2463FFFE */  addiu $v1, $v1, -2
/* 0B81E8 800B75E8 A4890002 */  sh    $t1, 2($a0)
/* 0B81EC 800B75EC 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0B81F0 800B75F0 8FAC09F4 */  lw    $t4, 0x9f4($sp)
/* 0B81F4 800B75F4 254BFFFF */  addiu $t3, $t2, -1
/* 0B81F8 800B75F8 05610005 */  bgez  $t3, .L800B7610
/* 0B81FC 800B75FC AFAB0038 */   sw    $t3, 0x38($sp)
/* 0B8200 800B7600 016C3021 */  addu  $a2, $t3, $t4
/* 0B8204 800B7604 00067040 */  sll   $t6, $a2, 1
/* 0B8208 800B7608 004E1821 */  addu  $v1, $v0, $t6
/* 0B820C 800B760C AFA60038 */  sw    $a2, 0x38($sp)
.L800B7610:
/* 0B8210 800B7610 846F0000 */  lh    $t7, ($v1)
/* 0B8214 800B7614 2463FFFE */  addiu $v1, $v1, -2
/* 0B8218 800B7618 A48F0004 */  sh    $t7, 4($a0)
/* 0B821C 800B761C 8FAD0038 */  lw    $t5, 0x38($sp)
/* 0B8220 800B7620 8FB909F4 */  lw    $t9, 0x9f4($sp)
/* 0B8224 800B7624 25B8FFFF */  addiu $t8, $t5, -1
/* 0B8228 800B7628 07010005 */  bgez  $t8, .L800B7640
/* 0B822C 800B762C AFB80038 */   sw    $t8, 0x38($sp)
/* 0B8230 800B7630 03193021 */  addu  $a2, $t8, $t9
/* 0B8234 800B7634 00064040 */  sll   $t0, $a2, 1
/* 0B8238 800B7638 00481821 */  addu  $v1, $v0, $t0
/* 0B823C 800B763C AFA60038 */  sw    $a2, 0x38($sp)
.L800B7640:
/* 0B8240 800B7640 84690000 */  lh    $t1, ($v1)
/* 0B8244 800B7644 00000000 */  nop   
/* 0B8248 800B7648 A4890006 */  sh    $t1, 6($a0)
/* 0B824C 800B764C 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0B8250 800B7650 8FAC09F4 */  lw    $t4, 0x9f4($sp)
/* 0B8254 800B7654 254BFFFF */  addiu $t3, $t2, -1
/* 0B8258 800B7658 05610003 */  bgez  $t3, .L800B7668
/* 0B825C 800B765C AFAB0038 */   sw    $t3, 0x38($sp)
/* 0B8260 800B7660 016C3021 */  addu  $a2, $t3, $t4
/* 0B8264 800B7664 AFA60038 */  sw    $a2, 0x38($sp)
.L800B7668:
/* 0B8268 800B7668 8FAE09F4 */  lw    $t6, 0x9f4($sp)
/* 0B826C 800B766C 24A50004 */  addiu $a1, $a1, 4
/* 0B8270 800B7670 14AEFFCB */  bne   $a1, $t6, .L800B75A0
/* 0B8274 800B7674 24840008 */   addiu $a0, $a0, 8
.L800B7678:
/* 0B8278 800B7678 3C06800F */  lui   $a2, %hi(sCoreFileName) # $a2, 0x800f
/* 0B827C 800B767C 27AF0040 */  addiu $t7, $sp, 0x40
/* 0B8280 800B7680 240D0800 */  li    $t5, 2048
/* 0B8284 800B7684 AFAD0014 */  sw    $t5, 0x14($sp)
/* 0B8288 800B7688 AFAF0010 */  sw    $t7, 0x10($sp)
/* 0B828C 800B768C 24C68EE8 */  addiu $a2, %lo(sCoreFileName) # addiu $a2, $a2, -0x7118
/* 0B8290 800B7690 00002025 */  move  $a0, $zero
/* 0B8294 800B7694 2405FFFF */  li    $a1, -1
/* 0B8298 800B7698 0C01D9B5 */  jal   write_controller_pak_file
/* 0B829C 800B769C 24E78EF0 */   addiu $a3, %lo(sCoreFileExt) # addiu $a3, $a3, -0x7110
.L800B76A0:
/* 0B82A0 800B76A0 1000FFFF */  b     .L800B76A0
/* 0B82A4 800B76A4 00000000 */   nop   
.L800B76A8:
/* 0B82A8 800B76A8 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B82AC 800B76AC 27BD09F0 */  addiu $sp, $sp, 0x9f0
/* 0B82B0 800B76B0 03E00008 */  jr    $ra
/* 0B82B4 800B76B4 00000000 */   nop   

