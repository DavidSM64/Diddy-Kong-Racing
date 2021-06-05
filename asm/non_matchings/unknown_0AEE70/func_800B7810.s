.rdata
glabel D_800E8F18
.asciz " epc\t\t0x%08x\n"
.ascii "\0\0" # padding
glabel D_800E8F28
.asciz " cause\t\tmmAlloc(%d,0x%8x)\n"
.ascii "\0" # padding
glabel D_800E8F44
.asciz " object\t\t"
.ascii "\0\0" # padding
glabel D_800E8F50
.asciz "%s %d "
.ascii "\0" # padding
glabel D_800E8F58
.asciz "\n"
.ascii "\0\0" # padding
glabel D_800E8F5C
.asciz "\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
.ascii "\0" # padding
glabel D_800E8F6C
.asciz " Fault in thread %d\n"
.ascii "\0\0\0" # padding
glabel D_800E8F84
.asciz " epc\t\t0x%08x\n"
.ascii "\0\0" # padding
glabel D_800E8F94
.asciz " cause\t\t0x%08x\n"
glabel D_800E8FA4
.asciz " sr\t\t0x%08x\n"
.ascii "\0\0\0" # padding
glabel D_800E8FB4
.asciz " badvaddr\t0x%08x\n"
.ascii "\0\0" # padding
glabel D_800E8FC8
.asciz " object\t\t"
.ascii "\0\0" # padding
glabel D_800E8FD4
.asciz "%s %d "
.ascii "\0" # padding
glabel D_800E8FDC
.asciz "\n"
.ascii "\0\0" # padding
glabel D_800E8FE0
.asciz " at 0x%08x v0 0x%08x v1 0x%08x\n"
glabel D_800E9000
.asciz " a0 0x%08x a1 0x%08x a2 0x%08x\n"
glabel D_800E9020
.asciz " a3 0x%08x t0 0x%08x t1 0x%08x\n"
glabel D_800E9040
.asciz " t2 0x%08x t3 0x%08x t4 0x%08x\n"
glabel D_800E9060
.asciz " t5 0x%08x t6 0x%08x t7 0x%08x\n"
glabel D_800E9080
.asciz " s0 0x%08x s1 0x%08x s2 0x%08x\n"
glabel D_800E90A0
.asciz " s3 0x%08x s4 0x%08x s5 0x%08x\n"
glabel D_800E90C0
.asciz " s6 0x%08x s7 0x%08x t8 0x%08x\n"
glabel D_800E90E0
.asciz " t9 0x%08x gp 0x%08x sp 0x%08x\n"
glabel D_800E9100
.asciz " s8 0x%08x ra 0x%08x\n\n"
.ascii "\0" # padding
glabel D_800E9118
.asciz "   %08x %08x %08x\n"
.ascii "\0" # padding
glabel D_800E912C
.asciz "  "
.ascii "\0" # padding
glabel D_800E9130
.asciz "%04x "
.ascii "\0\0" # padding
glabel D_800E9138
.asciz "\n"
.ascii "\0\0" # padding

.late_rodata
glabel jpt_800E913C
.word L800B7898, L800B7C18, L800B7C18, L800B7C18, L800B7C70, L800B7CE4

.text
glabel func_800B7810
/* 0B8410 800B7810 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 0B8414 800B7814 3C0F800E */  lui   $t7, %hi(D_800E302C) # $t7, 0x800e
/* 0B8418 800B7818 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0B841C 800B781C AFB50028 */  sw    $s5, 0x28($sp)
/* 0B8420 800B7820 AFB40024 */  sw    $s4, 0x24($sp)
/* 0B8424 800B7824 AFB30020 */  sw    $s3, 0x20($sp)
/* 0B8428 800B7828 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0B842C 800B782C AFB10018 */  sw    $s1, 0x18($sp)
/* 0B8430 800B7830 AFB00014 */  sw    $s0, 0x14($sp)
/* 0B8434 800B7834 25EF302C */  addiu $t7, %lo(D_800E302C) # addiu $t7, $t7, 0x302c
/* 0B8438 800B7838 8DE10000 */  lw    $at, ($t7)
/* 0B843C 800B783C 27AE0050 */  addiu $t6, $sp, 0x50
/* 0B8440 800B7840 ADC10000 */  sw    $at, ($t6)
/* 0B8444 800B7844 8DE10008 */  lw    $at, 8($t7)
/* 0B8448 800B7848 8DE80004 */  lw    $t0, 4($t7)
/* 0B844C 800B784C 00009825 */  move  $s3, $zero
/* 0B8450 800B7850 24040010 */  li    $a0, 16
/* 0B8454 800B7854 24050020 */  li    $a1, 32
/* 0B8458 800B7858 ADC10008 */  sw    $at, 8($t6)
/* 0B845C 800B785C 0C02D8D7 */  jal   func_800B635C
/* 0B8460 800B7860 ADC80004 */   sw    $t0, 4($t6)
/* 0B8464 800B7864 3C03800E */  lui   $v1, %hi(D_800E3024) # $v1, 0x800e
/* 0B8468 800B7868 24633024 */  addiu $v1, %lo(D_800E3024) # addiu $v1, $v1, 0x3024
/* 0B846C 800B786C 8C620000 */  lw    $v0, ($v1)
/* 0B8470 800B7870 00000000 */  nop   
/* 0B8474 800B7874 2C410006 */  sltiu $at, $v0, 6
/* 0B8478 800B7878 1020011B */  beqz  $at, .L800B7CE8
/* 0B847C 800B787C 00024880 */   sll   $t1, $v0, 2
/* 0B8480 800B7880 3C01800F */  lui   $at, %hi(jpt_800E913C) # $at, 0x800f
/* 0B8484 800B7884 00290821 */  addu  $at, $at, $t1
/* 0B8488 800B7888 8C29913C */  lw    $t1, %lo(jpt_800E913C)($at)
/* 0B848C 800B788C 00000000 */  nop   
/* 0B8490 800B7890 01200008 */  jr    $t1
/* 0B8494 800B7894 00000000 */   nop   
glabel L800B7898
/* 0B8498 800B7898 444AF800 */  cfc1  $t2, $31
/* 0B849C 800B789C 3C038013 */  lui   $v1, %hi(D_80129800) # $v1, 0x8013
/* 0B84A0 800B78A0 35410003 */  ori   $at, $t2, 3
/* 0B84A4 800B78A4 24639800 */  addiu $v1, %lo(D_80129800) # addiu $v1, $v1, -0x6800
/* 0B84A8 800B78A8 38210002 */  xori  $at, $at, 2
/* 0B84AC 800B78AC 44C1F800 */  ctc1  $at, $31
/* 0B84B0 800B78B0 C4640130 */  lwc1  $f4, 0x130($v1)
/* 0B84B4 800B78B4 C4680134 */  lwc1  $f8, 0x134($v1)
/* 0B84B8 800B78B8 460021A4 */  cvt.w.s $f6, $f4
/* 0B84BC 800B78BC C4700138 */  lwc1  $f16, 0x138($v1)
/* 0B84C0 800B78C0 44CAF800 */  ctc1  $t2, $31
/* 0B84C4 800B78C4 3C028013 */  lui   $v0, %hi(D_80129FB0) # $v0, 0x8013
/* 0B84C8 800B78C8 440B3000 */  mfc1  $t3, $f6
/* 0B84CC 800B78CC 444CF800 */  cfc1  $t4, $31
/* 0B84D0 800B78D0 8C6E0120 */  lw    $t6, 0x120($v1)
/* 0B84D4 800B78D4 35810003 */  ori   $at, $t4, 3
/* 0B84D8 800B78D8 38210002 */  xori  $at, $at, 2
/* 0B84DC 800B78DC 44C1F800 */  ctc1  $at, $31
/* 0B84E0 800B78E0 24429FB0 */  addiu $v0, %lo(D_80129FB0) # addiu $v0, $v0, -0x6050
/* 0B84E4 800B78E4 460042A4 */  cvt.w.s $f10, $f8
/* 0B84E8 800B78E8 AC4B0000 */  sw    $t3, ($v0)
/* 0B84EC 800B78EC 44CCF800 */  ctc1  $t4, $31
/* 0B84F0 800B78F0 440D5000 */  mfc1  $t5, $f10
/* 0B84F4 800B78F4 00000000 */  nop   
/* 0B84F8 800B78F8 4459F800 */  cfc1  $t9, $31
/* 0B84FC 800B78FC AC4D0004 */  sw    $t5, 4($v0)
/* 0B8500 800B7900 37210003 */  ori   $at, $t9, 3
/* 0B8504 800B7904 38210002 */  xori  $at, $at, 2
/* 0B8508 800B7908 44C1F800 */  ctc1  $at, $31
/* 0B850C 800B790C 2401FFFF */  li    $at, -1
/* 0B8510 800B7910 460084A4 */  cvt.w.s $f18, $f16
/* 0B8514 800B7914 44189000 */  mfc1  $t8, $f18
/* 0B8518 800B7918 44D9F800 */  ctc1  $t9, $31
/* 0B851C 800B791C 15C1002F */  bne   $t6, $at, .L800B79DC
/* 0B8520 800B7920 AC580008 */   sw    $t8, 8($v0)
/* 0B8524 800B7924 3C058013 */  lui   $a1, %hi(D_8012991C) # $a1, 0x8013
/* 0B8528 800B7928 8CA5991C */  lw    $a1, %lo(D_8012991C)($a1)
/* 0B852C 800B792C 3C04800F */  lui   $a0, %hi(D_800E8F18) # $a0, 0x800f
/* 0B8530 800B7930 0C02D7B7 */  jal   func_800B5EDC
/* 0B8534 800B7934 24848F18 */   addiu $a0, %lo(D_800E8F18) # addiu $a0, $a0, -0x70e8
/* 0B8538 800B7938 3C098013 */  lui   $t1, %hi(D_8012983C) # $t1, 0x8013
/* 0B853C 800B793C 3C0B8013 */  lui   $t3, %hi(D_80129844) # $t3, 0x8013
/* 0B8540 800B7940 8D669844 */  lw    $a2, %lo(D_80129844)($t3)
/* 0B8544 800B7944 8D25983C */  lw    $a1, %lo(D_8012983C)($t1)
/* 0B8548 800B7948 3C04800F */  lui   $a0, %hi(D_800E8F28) # $a0, 0x800f
/* 0B854C 800B794C 0C02D7B7 */  jal   func_800B5EDC
/* 0B8550 800B7950 24848F28 */   addiu $a0, %lo(D_800E8F28) # addiu $a0, $a0, -0x70d8
/* 0B8554 800B7954 3C108013 */  lui   $s0, %hi(D_80129FB0) # $s0, 0x8013
/* 0B8558 800B7958 3C15800F */  lui   $s5, %hi(D_800E8F44) # $s5, 0x800f
/* 0B855C 800B795C 26B58F44 */  addiu $s5, %lo(D_800E8F44) # addiu $s5, $s5, -0x70bc
/* 0B8560 800B7960 26109FB0 */  addiu $s0, %lo(D_80129FB0) # addiu $s0, $s0, -0x6050
/* 0B8564 800B7964 00009025 */  move  $s2, $zero
/* 0B8568 800B7968 2414FFFF */  li    $s4, -1
.L800B796C:
/* 0B856C 800B796C 8E060000 */  lw    $a2, ($s0)
/* 0B8570 800B7970 27AF0050 */  addiu $t7, $sp, 0x50
/* 0B8574 800B7974 1286000C */  beq   $s4, $a2, .L800B79A8
/* 0B8578 800B7978 00000000 */   nop   
/* 0B857C 800B797C 16600006 */  bnez  $s3, .L800B7998
/* 0B8580 800B7980 024F8821 */   addu  $s1, $s2, $t7
/* 0B8584 800B7984 24130001 */  li    $s3, 1
/* 0B8588 800B7988 0C02D7B7 */  jal   func_800B5EDC
/* 0B858C 800B798C 02A02025 */   move  $a0, $s5
/* 0B8590 800B7990 8E060000 */  lw    $a2, ($s0)
/* 0B8594 800B7994 00000000 */  nop   
.L800B7998:
/* 0B8598 800B7998 3C04800F */  lui   $a0, %hi(D_800E8F50) # $a0, 0x800f
/* 0B859C 800B799C 8E250000 */  lw    $a1, ($s1)
/* 0B85A0 800B79A0 0C02D7B7 */  jal   func_800B5EDC
/* 0B85A4 800B79A4 24848F50 */   addiu $a0, %lo(D_800E8F50) # addiu $a0, $a0, -0x70b0
.L800B79A8:
/* 0B85A8 800B79A8 3C0C8013 */  lui   $t4, %hi(D_80129FBC) # $t4, 0x8013
/* 0B85AC 800B79AC 258C9FBC */  addiu $t4, %lo(D_80129FBC) # addiu $t4, $t4, -0x6044
/* 0B85B0 800B79B0 26100004 */  addiu $s0, $s0, 4
/* 0B85B4 800B79B4 160CFFED */  bne   $s0, $t4, .L800B796C
/* 0B85B8 800B79B8 26520004 */   addiu $s2, $s2, 4
/* 0B85BC 800B79BC 3C04800F */  lui   $a0, %hi(D_800E8F58) # $a0, 0x800f
/* 0B85C0 800B79C0 0C02D7B7 */  jal   func_800B5EDC
/* 0B85C4 800B79C4 24848F58 */   addiu $a0, %lo(D_800E8F58) # addiu $a0, $a0, -0x70a8
/* 0B85C8 800B79C8 3C04800F */  lui   $a0, %hi(D_800E8F5C) # $a0, 0x800f
/* 0B85CC 800B79CC 0C02D7B7 */  jal   func_800B5EDC
/* 0B85D0 800B79D0 24848F5C */   addiu $a0, %lo(D_800E8F5C) # addiu $a0, $a0, -0x70a4
/* 0B85D4 800B79D4 100000C5 */  b     .L800B7CEC
/* 0B85D8 800B79D8 8FBF002C */   lw    $ra, 0x2c($sp)
.L800B79DC:
/* 0B85DC 800B79DC 3C04800F */  lui   $a0, %hi(D_800E8F6C) # $a0, 0x800f
/* 0B85E0 800B79E0 8C650014 */  lw    $a1, 0x14($v1)
/* 0B85E4 800B79E4 0C02D7B7 */  jal   func_800B5EDC
/* 0B85E8 800B79E8 24848F6C */   addiu $a0, %lo(D_800E8F6C) # addiu $a0, $a0, -0x7094
/* 0B85EC 800B79EC 3C058013 */  lui   $a1, %hi(D_8012991C) # $a1, 0x8013
/* 0B85F0 800B79F0 8CA5991C */  lw    $a1, %lo(D_8012991C)($a1)
/* 0B85F4 800B79F4 3C04800F */  lui   $a0, %hi(D_800E8F84) # $a0, 0x800f
/* 0B85F8 800B79F8 0C02D7B7 */  jal   func_800B5EDC
/* 0B85FC 800B79FC 24848F84 */   addiu $a0, %lo(D_800E8F84) # addiu $a0, $a0, -0x707c
/* 0B8600 800B7A00 3C058013 */  lui   $a1, %hi(D_80129920) # $a1, 0x8013
/* 0B8604 800B7A04 8CA59920 */  lw    $a1, %lo(D_80129920)($a1)
/* 0B8608 800B7A08 3C04800F */  lui   $a0, %hi(D_800E8F94) # $a0, 0x800f
/* 0B860C 800B7A0C 0C02D7B7 */  jal   func_800B5EDC
/* 0B8610 800B7A10 24848F94 */   addiu $a0, %lo(D_800E8F94) # addiu $a0, $a0, -0x706c
/* 0B8614 800B7A14 3C058013 */  lui   $a1, %hi(D_80129918) # $a1, 0x8013
/* 0B8618 800B7A18 8CA59918 */  lw    $a1, %lo(D_80129918)($a1)
/* 0B861C 800B7A1C 3C04800F */  lui   $a0, %hi(D_800E8FA4) # $a0, 0x800f
/* 0B8620 800B7A20 0C02D7B7 */  jal   func_800B5EDC
/* 0B8624 800B7A24 24848FA4 */   addiu $a0, %lo(D_800E8FA4) # addiu $a0, $a0, -0x705c
/* 0B8628 800B7A28 3C058013 */  lui   $a1, %hi(D_80129924) # $a1, 0x8013
/* 0B862C 800B7A2C 8CA59924 */  lw    $a1, %lo(D_80129924)($a1)
/* 0B8630 800B7A30 3C04800F */  lui   $a0, %hi(D_800E8FB4) # $a0, 0x800f
/* 0B8634 800B7A34 0C02D7B7 */  jal   func_800B5EDC
/* 0B8638 800B7A38 24848FB4 */   addiu $a0, %lo(D_800E8FB4) # addiu $a0, $a0, -0x704c
/* 0B863C 800B7A3C 3C108013 */  lui   $s0, %hi(D_80129FB0) # $s0, 0x8013
/* 0B8640 800B7A40 3C15800F */  lui   $s5, %hi(D_800E8FC8) # $s5, 0x800f
/* 0B8644 800B7A44 26B58FC8 */  addiu $s5, %lo(D_800E8FC8) # addiu $s5, $s5, -0x7038
/* 0B8648 800B7A48 26109FB0 */  addiu $s0, %lo(D_80129FB0) # addiu $s0, $s0, -0x6050
/* 0B864C 800B7A4C 00009025 */  move  $s2, $zero
/* 0B8650 800B7A50 2414FFFF */  li    $s4, -1
.L800B7A54:
/* 0B8654 800B7A54 8E060000 */  lw    $a2, ($s0)
/* 0B8658 800B7A58 27AD0050 */  addiu $t5, $sp, 0x50
/* 0B865C 800B7A5C 1286000C */  beq   $s4, $a2, .L800B7A90
/* 0B8660 800B7A60 00000000 */   nop   
/* 0B8664 800B7A64 16600006 */  bnez  $s3, .L800B7A80
/* 0B8668 800B7A68 024D8821 */   addu  $s1, $s2, $t5
/* 0B866C 800B7A6C 24130001 */  li    $s3, 1
/* 0B8670 800B7A70 0C02D7B7 */  jal   func_800B5EDC
/* 0B8674 800B7A74 02A02025 */   move  $a0, $s5
/* 0B8678 800B7A78 8E060000 */  lw    $a2, ($s0)
/* 0B867C 800B7A7C 00000000 */  nop   
.L800B7A80:
/* 0B8680 800B7A80 3C04800F */  lui   $a0, %hi(D_800E8FD4) # $a0, 0x800f
/* 0B8684 800B7A84 8E250000 */  lw    $a1, ($s1)
/* 0B8688 800B7A88 0C02D7B7 */  jal   func_800B5EDC
/* 0B868C 800B7A8C 24848FD4 */   addiu $a0, %lo(D_800E8FD4) # addiu $a0, $a0, -0x702c
.L800B7A90:
/* 0B8690 800B7A90 3C198013 */  lui   $t9, %hi(D_80129FBC) # $t9, 0x8013
/* 0B8694 800B7A94 27399FBC */  addiu $t9, %lo(D_80129FBC) # addiu $t9, $t9, -0x6044
/* 0B8698 800B7A98 26100004 */  addiu $s0, $s0, 4
/* 0B869C 800B7A9C 1619FFED */  bne   $s0, $t9, .L800B7A54
/* 0B86A0 800B7AA0 26520004 */   addiu $s2, $s2, 4
/* 0B86A4 800B7AA4 3C04800F */  lui   $a0, %hi(D_800E8FDC) # $a0, 0x800f
/* 0B86A8 800B7AA8 0C02D7B7 */  jal   func_800B5EDC
/* 0B86AC 800B7AAC 24848FDC */   addiu $a0, %lo(D_800E8FDC) # addiu $a0, $a0, -0x7024
/* 0B86B0 800B7AB0 3C198013 */  lui   $t9, %hi(D_80129824) # $t9, 0x8013
/* 0B86B4 800B7AB4 3C0F8013 */  lui   $t7, %hi(D_8012982C) # $t7, 0x8013
/* 0B86B8 800B7AB8 3C098013 */  lui   $t1, %hi(D_80129834) # $t1, 0x8013
/* 0B86BC 800B7ABC 8D279834 */  lw    $a3, %lo(D_80129834)($t1)
/* 0B86C0 800B7AC0 8DE6982C */  lw    $a2, %lo(D_8012982C)($t7)
/* 0B86C4 800B7AC4 8F259824 */  lw    $a1, %lo(D_80129824)($t9)
/* 0B86C8 800B7AC8 3C04800F */  lui   $a0, %hi(D_800E8FE0) # $a0, 0x800f
/* 0B86CC 800B7ACC 0C02D7B7 */  jal   func_800B5EDC
/* 0B86D0 800B7AD0 24848FE0 */   addiu $a0, %lo(D_800E8FE0) # addiu $a0, $a0, -0x7020
/* 0B86D4 800B7AD4 3C0B8013 */  lui   $t3, %hi(D_8012983C) # $t3, 0x8013
/* 0B86D8 800B7AD8 3C0D8013 */  lui   $t5, %hi(D_80129844) # $t5, 0x8013
/* 0B86DC 800B7ADC 3C198013 */  lui   $t9, %hi(D_8012984C) # $t9, 0x8013
/* 0B86E0 800B7AE0 8F27984C */  lw    $a3, %lo(D_8012984C)($t9)
/* 0B86E4 800B7AE4 8DA69844 */  lw    $a2, %lo(D_80129844)($t5)
/* 0B86E8 800B7AE8 8D65983C */  lw    $a1, %lo(D_8012983C)($t3)
/* 0B86EC 800B7AEC 3C04800F */  lui   $a0, %hi(D_800E9000) # $a0, 0x800f
/* 0B86F0 800B7AF0 0C02D7B7 */  jal   func_800B5EDC
/* 0B86F4 800B7AF4 24849000 */   addiu $a0, %lo(D_800E9000) # addiu $a0, $a0, -0x7000
/* 0B86F8 800B7AF8 3C0F8013 */  lui   $t7, %hi(D_80129854) # $t7, 0x8013
/* 0B86FC 800B7AFC 3C098013 */  lui   $t1, %hi(D_8012985C) # $t1, 0x8013
/* 0B8700 800B7B00 3C0B8013 */  lui   $t3, %hi(D_80129864) # $t3, 0x8013
/* 0B8704 800B7B04 8D679864 */  lw    $a3, %lo(D_80129864)($t3)
/* 0B8708 800B7B08 8D26985C */  lw    $a2, %lo(D_8012985C)($t1)
/* 0B870C 800B7B0C 8DE59854 */  lw    $a1, %lo(D_80129854)($t7)
/* 0B8710 800B7B10 3C04800F */  lui   $a0, %hi(D_800E9020) # $a0, 0x800f
/* 0B8714 800B7B14 0C02D7B7 */  jal   func_800B5EDC
/* 0B8718 800B7B18 24849020 */   addiu $a0, %lo(D_800E9020) # addiu $a0, $a0, -0x6fe0
/* 0B871C 800B7B1C 3C0D8013 */  lui   $t5, %hi(D_8012986C) # $t5, 0x8013
/* 0B8720 800B7B20 3C198013 */  lui   $t9, %hi(D_80129874) # $t9, 0x8013
/* 0B8724 800B7B24 3C0F8013 */  lui   $t7, %hi(D_8012987C) # $t7, 0x8013
/* 0B8728 800B7B28 8DE7987C */  lw    $a3, %lo(D_8012987C)($t7)
/* 0B872C 800B7B2C 8F269874 */  lw    $a2, %lo(D_80129874)($t9)
/* 0B8730 800B7B30 8DA5986C */  lw    $a1, %lo(D_8012986C)($t5)
/* 0B8734 800B7B34 3C04800F */  lui   $a0, %hi(D_800E9040) # $a0, 0x800f
/* 0B8738 800B7B38 0C02D7B7 */  jal   func_800B5EDC
/* 0B873C 800B7B3C 24849040 */   addiu $a0, %lo(D_800E9040) # addiu $a0, $a0, -0x6fc0
/* 0B8740 800B7B40 3C098013 */  lui   $t1, %hi(D_80129884) # $t1, 0x8013
/* 0B8744 800B7B44 3C0B8013 */  lui   $t3, %hi(D_8012988C) # $t3, 0x8013
/* 0B8748 800B7B48 3C0D8013 */  lui   $t5, %hi(D_80129894) # $t5, 0x8013
/* 0B874C 800B7B4C 8DA79894 */  lw    $a3, %lo(D_80129894)($t5)
/* 0B8750 800B7B50 8D66988C */  lw    $a2, %lo(D_8012988C)($t3)
/* 0B8754 800B7B54 8D259884 */  lw    $a1, %lo(D_80129884)($t1)
/* 0B8758 800B7B58 3C04800F */  lui   $a0, %hi(D_800E9060) # $a0, 0x800f
/* 0B875C 800B7B5C 0C02D7B7 */  jal   func_800B5EDC
/* 0B8760 800B7B60 24849060 */   addiu $a0, %lo(D_800E9060) # addiu $a0, $a0, -0x6fa0
/* 0B8764 800B7B64 3C198013 */  lui   $t9, %hi(D_8012989C) # $t9, 0x8013
/* 0B8768 800B7B68 3C0F8013 */  lui   $t7, %hi(D_801298A4) # $t7, 0x8013
/* 0B876C 800B7B6C 3C098013 */  lui   $t1, %hi(D_801298AC) # $t1, 0x8013
/* 0B8770 800B7B70 8D2798AC */  lw    $a3, %lo(D_801298AC)($t1)
/* 0B8774 800B7B74 8DE698A4 */  lw    $a2, %lo(D_801298A4)($t7)
/* 0B8778 800B7B78 8F25989C */  lw    $a1, %lo(D_8012989C)($t9)
/* 0B877C 800B7B7C 3C04800F */  lui   $a0, %hi(D_800E9080) # $a0, 0x800f
/* 0B8780 800B7B80 0C02D7B7 */  jal   func_800B5EDC
/* 0B8784 800B7B84 24849080 */   addiu $a0, %lo(D_800E9080) # addiu $a0, $a0, -0x6f80
/* 0B8788 800B7B88 3C0B8013 */  lui   $t3, %hi(D_801298B4) # $t3, 0x8013
/* 0B878C 800B7B8C 3C0D8013 */  lui   $t5, %hi(D_801298BC) # $t5, 0x8013
/* 0B8790 800B7B90 3C198013 */  lui   $t9, %hi(D_801298C4) # $t9, 0x8013
/* 0B8794 800B7B94 8F2798C4 */  lw    $a3, %lo(D_801298C4)($t9)
/* 0B8798 800B7B98 8DA698BC */  lw    $a2, %lo(D_801298BC)($t5)
/* 0B879C 800B7B9C 8D6598B4 */  lw    $a1, %lo(D_801298B4)($t3)
/* 0B87A0 800B7BA0 3C04800F */  lui   $a0, %hi(D_800E90A0) # $a0, 0x800f
/* 0B87A4 800B7BA4 0C02D7B7 */  jal   func_800B5EDC
/* 0B87A8 800B7BA8 248490A0 */   addiu $a0, %lo(D_800E90A0) # addiu $a0, $a0, -0x6f60
/* 0B87AC 800B7BAC 3C0F8013 */  lui   $t7, %hi(D_801298CC) # $t7, 0x8013
/* 0B87B0 800B7BB0 3C098013 */  lui   $t1, %hi(D_801298D4) # $t1, 0x8013
/* 0B87B4 800B7BB4 3C0B8013 */  lui   $t3, %hi(D_801298DC) # $t3, 0x8013
/* 0B87B8 800B7BB8 8D6798DC */  lw    $a3, %lo(D_801298DC)($t3)
/* 0B87BC 800B7BBC 8D2698D4 */  lw    $a2, %lo(D_801298D4)($t1)
/* 0B87C0 800B7BC0 8DE598CC */  lw    $a1, %lo(D_801298CC)($t7)
/* 0B87C4 800B7BC4 3C04800F */  lui   $a0, %hi(D_800E90C0) # $a0, 0x800f
/* 0B87C8 800B7BC8 0C02D7B7 */  jal   func_800B5EDC
/* 0B87CC 800B7BCC 248490C0 */   addiu $a0, %lo(D_800E90C0) # addiu $a0, $a0, -0x6f40
/* 0B87D0 800B7BD0 3C0D8013 */  lui   $t5, %hi(D_801298E4) # $t5, 0x8013
/* 0B87D4 800B7BD4 3C198013 */  lui   $t9, %hi(D_801298EC) # $t9, 0x8013
/* 0B87D8 800B7BD8 3C0F8013 */  lui   $t7, %hi(D_801298F4) # $t7, 0x8013
/* 0B87DC 800B7BDC 8DE798F4 */  lw    $a3, %lo(D_801298F4)($t7)
/* 0B87E0 800B7BE0 8F2698EC */  lw    $a2, %lo(D_801298EC)($t9)
/* 0B87E4 800B7BE4 8DA598E4 */  lw    $a1, %lo(D_801298E4)($t5)
/* 0B87E8 800B7BE8 3C04800F */  lui   $a0, %hi(D_800E90E0) # $a0, 0x800f
/* 0B87EC 800B7BEC 0C02D7B7 */  jal   func_800B5EDC
/* 0B87F0 800B7BF0 248490E0 */   addiu $a0, %lo(D_800E90E0) # addiu $a0, $a0, -0x6f20
/* 0B87F4 800B7BF4 3C098013 */  lui   $t1, %hi(D_801298FC) # $t1, 0x8013
/* 0B87F8 800B7BF8 3C0B8013 */  lui   $t3, %hi(D_80129904) # $t3, 0x8013
/* 0B87FC 800B7BFC 8D669904 */  lw    $a2, %lo(D_80129904)($t3)
/* 0B8800 800B7C00 8D2598FC */  lw    $a1, %lo(D_801298FC)($t1)
/* 0B8804 800B7C04 3C04800F */  lui   $a0, %hi(D_800E9100) # $a0, 0x800f
/* 0B8808 800B7C08 0C02D7B7 */  jal   func_800B5EDC
/* 0B880C 800B7C0C 24849100 */   addiu $a0, %lo(D_800E9100) # addiu $a0, $a0, -0x6f00
/* 0B8810 800B7C10 10000036 */  b     .L800B7CEC
/* 0B8814 800B7C14 8FBF002C */   lw    $ra, 0x2c($sp)
glabel L800B7C18
/* 0B8818 800B7C18 00021880 */  sll   $v1, $v0, 2
/* 0B881C 800B7C1C 00621823 */  subu  $v1, $v1, $v0
/* 0B8820 800B7C20 00031900 */  sll   $v1, $v1, 4
/* 0B8824 800B7C24 2463FFD0 */  addiu $v1, $v1, -0x30
/* 0B8828 800B7C28 3C0D8013 */  lui   $t5, %hi(D_801299B0) # $t5, 0x8013
/* 0B882C 800B7C2C 25AD99B0 */  addiu $t5, %lo(D_801299B0) # addiu $t5, $t5, -0x6650
/* 0B8830 800B7C30 00036080 */  sll   $t4, $v1, 2
/* 0B8834 800B7C34 3C11800F */  lui   $s1, %hi(D_800E9118) # $s1, 0x800f
/* 0B8838 800B7C38 26319118 */  addiu $s1, %lo(D_800E9118) # addiu $s1, $s1, -0x6ee8
/* 0B883C 800B7C3C 018D8021 */  addu  $s0, $t4, $t5
/* 0B8840 800B7C40 0000A025 */  move  $s4, $zero
/* 0B8844 800B7C44 24150010 */  li    $s5, 16
.L800B7C48:
/* 0B8848 800B7C48 8E050000 */  lw    $a1, ($s0)
/* 0B884C 800B7C4C 8E060040 */  lw    $a2, 0x40($s0)
/* 0B8850 800B7C50 8E070080 */  lw    $a3, 0x80($s0)
/* 0B8854 800B7C54 0C02D7B7 */  jal   func_800B5EDC
/* 0B8858 800B7C58 02202025 */   move  $a0, $s1
/* 0B885C 800B7C5C 26940001 */  addiu $s4, $s4, 1
/* 0B8860 800B7C60 1695FFF9 */  bne   $s4, $s5, .L800B7C48
/* 0B8864 800B7C64 26100004 */   addiu $s0, $s0, 4
/* 0B8868 800B7C68 10000020 */  b     .L800B7CEC
/* 0B886C 800B7C6C 8FBF002C */   lw    $ra, 0x2c($sp)
glabel L800B7C70
/* 0B8870 800B7C70 000219C0 */  sll   $v1, $v0, 7
/* 0B8874 800B7C74 2463FE00 */  addiu $v1, $v1, -0x200
/* 0B8878 800B7C78 3C198013 */  lui   $t9, %hi(D_80129BB0) # $t9, 0x8013
/* 0B887C 800B7C7C 27399BB0 */  addiu $t9, %lo(D_80129BB0) # addiu $t9, $t9, -0x6450
/* 0B8880 800B7C80 0003C040 */  sll   $t8, $v1, 1
/* 0B8884 800B7C84 3C12800F */  lui   $s2, %hi(D_800E9130) # $s2, 0x800f
/* 0B8888 800B7C88 26529130 */  addiu $s2, %lo(D_800E9130) # addiu $s2, $s2, -0x6ed0
/* 0B888C 800B7C8C 03198821 */  addu  $s1, $t8, $t9
/* 0B8890 800B7C90 0000A025 */  move  $s4, $zero
/* 0B8894 800B7C94 24150010 */  li    $s5, 16
/* 0B8898 800B7C98 24130008 */  li    $s3, 8
.L800B7C9C:
/* 0B889C 800B7C9C 3C04800F */  lui   $a0, %hi(D_800E912C) # $a0, 0x800f
/* 0B88A0 800B7CA0 0C02D7B7 */  jal   func_800B5EDC
/* 0B88A4 800B7CA4 2484912C */   addiu $a0, %lo(D_800E912C) # addiu $a0, $a0, -0x6ed4
/* 0B88A8 800B7CA8 00008025 */  move  $s0, $zero
.L800B7CAC:
/* 0B88AC 800B7CAC 96250000 */  lhu   $a1, ($s1)
/* 0B88B0 800B7CB0 0C02D7B7 */  jal   func_800B5EDC
/* 0B88B4 800B7CB4 02402025 */   move  $a0, $s2
/* 0B88B8 800B7CB8 26100001 */  addiu $s0, $s0, 1
/* 0B88BC 800B7CBC 1613FFFB */  bne   $s0, $s3, .L800B7CAC
/* 0B88C0 800B7CC0 26310002 */   addiu $s1, $s1, 2
/* 0B88C4 800B7CC4 3C04800F */  lui   $a0, %hi(D_800E9138) # $a0, 0x800f
/* 0B88C8 800B7CC8 0C02D7B7 */  jal   func_800B5EDC
/* 0B88CC 800B7CCC 24849138 */   addiu $a0, %lo(D_800E9138) # addiu $a0, $a0, -0x6ec8
/* 0B88D0 800B7CD0 26940001 */  addiu $s4, $s4, 1
/* 0B88D4 800B7CD4 1695FFF1 */  bne   $s4, $s5, .L800B7C9C
/* 0B88D8 800B7CD8 00000000 */   nop   
/* 0B88DC 800B7CDC 10000003 */  b     .L800B7CEC
/* 0B88E0 800B7CE0 8FBF002C */   lw    $ra, 0x2c($sp)
glabel L800B7CE4
/* 0B88E4 800B7CE4 AC600000 */  sw    $zero, ($v1)
.L800B7CE8:
/* 0B88E8 800B7CE8 8FBF002C */  lw    $ra, 0x2c($sp)
.L800B7CEC:
/* 0B88EC 800B7CEC 8FB00014 */  lw    $s0, 0x14($sp)
/* 0B88F0 800B7CF0 8FB10018 */  lw    $s1, 0x18($sp)
/* 0B88F4 800B7CF4 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0B88F8 800B7CF8 8FB30020 */  lw    $s3, 0x20($sp)
/* 0B88FC 800B7CFC 8FB40024 */  lw    $s4, 0x24($sp)
/* 0B8900 800B7D00 8FB50028 */  lw    $s5, 0x28($sp)
/* 0B8904 800B7D04 03E00008 */  jr    $ra
/* 0B8908 800B7D08 27BD0060 */   addiu $sp, $sp, 0x60

/* 0B890C 800B7D0C 00000000 */  nop   
