.late_rodata
glabel D_800E709C
.float 15000.0

.text
glabel func_80065EA0
/* 066AA0 80065EA0 3C048012 */  lui   $a0, %hi(D_80120DA0) # $a0, 0x8012
/* 066AA4 80065EA4 24030001 */  li    $v1, 1
/* 066AA8 80065EA8 3C0F8012 */  lui   $t7, %hi(gModelMatrixF) # $t7, 0x8012
/* 066AAC 80065EAC 25EF0D70 */  addiu $t7, %lo(gModelMatrixF) # addiu $t7, $t7, 0xd70
/* 066AB0 80065EB0 00037080 */  sll   $t6, $v1, 2
/* 066AB4 80065EB4 24840DA0 */  addiu $a0, %lo(D_80120DA0) # addiu $a0, $a0, 0xda0
/* 066AB8 80065EB8 01CF1021 */  addu  $v0, $t6, $t7
/* 066ABC 80065EBC 0003C980 */  sll   $t9, $v1, 6
/* 066AC0 80065EC0 3C018012 */  lui   $at, %hi(gModelMatrixF) # $at, 0x8012
/* 066AC4 80065EC4 AC240D70 */  sw    $a0, %lo(gModelMatrixF)($at)
/* 066AC8 80065EC8 00994021 */  addu  $t0, $a0, $t9
/* 066ACC 80065ECC 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 066AD0 80065ED0 AC480000 */  sw    $t0, ($v0)
/* 066AD4 80065ED4 246A0001 */  addiu $t2, $v1, 1
/* 066AD8 80065ED8 000A5980 */  sll   $t3, $t2, 6
/* 066ADC 80065EDC 24680003 */  addiu $t0, $v1, 3
/* 066AE0 80065EE0 246E0002 */  addiu $t6, $v1, 2
/* 066AE4 80065EE4 AFB1002C */  sw    $s1, 0x2c($sp)
/* 066AE8 80065EE8 000E7980 */  sll   $t7, $t6, 6
/* 066AEC 80065EEC 00084980 */  sll   $t1, $t0, 6
/* 066AF0 80065EF0 AFB20030 */  sw    $s2, 0x30($sp)
/* 066AF4 80065EF4 AFB00028 */  sw    $s0, 0x28($sp)
/* 066AF8 80065EF8 00895021 */  addu  $t2, $a0, $t1
/* 066AFC 80065EFC 008FC021 */  addu  $t8, $a0, $t7
/* 066B00 80065F00 008B6021 */  addu  $t4, $a0, $t3
/* 066B04 80065F04 3C118012 */  lui   $s1, %hi(gActiveCameraID) # $s1, 0x8012
/* 066B08 80065F08 AFBF0034 */  sw    $ra, 0x34($sp)
/* 066B0C 80065F0C AC4C0004 */  sw    $t4, 4($v0)
/* 066B10 80065F10 AC580008 */  sw    $t8, 8($v0)
/* 066B14 80065F14 AC4A000C */  sw    $t2, 0xc($v0)
/* 066B18 80065F18 26310CE4 */  addiu $s1, %lo(gActiveCameraID) # addiu $s1, $s1, 0xce4
/* 066B1C 80065F1C 00008025 */  move  $s0, $zero
/* 066B20 80065F20 24120008 */  li    $s2, 8
/* 066B24 80065F24 240B00B4 */  li    $t3, 180
.L80065F28:
/* 066B28 80065F28 AE300000 */  sw    $s0, ($s1)
/* 066B2C 80065F2C AFAB0014 */  sw    $t3, 0x14($sp)
/* 066B30 80065F30 240400C8 */  li    $a0, 200
/* 066B34 80065F34 240500C8 */  li    $a1, 200
/* 066B38 80065F38 240600C8 */  li    $a2, 200
/* 066B3C 80065F3C 00003825 */  move  $a3, $zero
/* 066B40 80065F40 0C0198F7 */  jal   func_800663DC
/* 066B44 80065F44 AFA00010 */   sw    $zero, 0x10($sp)
/* 066B48 80065F48 26100001 */  addiu $s0, $s0, 1
/* 066B4C 80065F4C 1612FFF6 */  bne   $s0, $s2, .L80065F28
/* 066B50 80065F50 240B00B4 */   li    $t3, 180
/* 066B54 80065F54 3C018012 */  lui   $at, %hi(gCutsceneCameraActive) # $at, 0x8012
/* 066B58 80065F58 A0200D14 */  sb    $zero, %lo(gCutsceneCameraActive)($at)
/* 066B5C 80065F5C AE200000 */  sw    $zero, ($s1)
/* 066B60 80065F60 3C018012 */  lui   $at, %hi(gModelMatrixStackPos) # $at, 0x8012
/* 066B64 80065F64 AC200D1C */  sw    $zero, %lo(gModelMatrixStackPos)($at)
/* 066B68 80065F68 3C018012 */  lui   $at, %hi(gCameraMatrixPos) # $at, 0x8012
/* 066B6C 80065F6C AC200D20 */  sw    $zero, %lo(gCameraMatrixPos)($at)
/* 066B70 80065F70 3C018012 */  lui   $at, %hi(gNumberOfViewports) # $at, 0x8012
/* 066B74 80065F74 AC200CE0 */  sw    $zero, %lo(gNumberOfViewports)($at)
/* 066B78 80065F78 3C018012 */  lui   $at, %hi(D_80120D0C) # $at, 0x8012
/* 066B7C 80065F7C AC200D0C */  sw    $zero, %lo(D_80120D0C)($at)
/* 066B80 80065F80 3C018012 */  lui   $at, %hi(D_80120D18) # $at, 0x8012
/* 066B84 80065F84 AC200D18 */  sw    $zero, %lo(D_80120D18)($at)
/* 066B88 80065F88 3C04800E */  lui   $a0, %hi(gAntiPiracyViewport) # $a0, 0x800e
/* 066B8C 80065F8C 3C018012 */  lui   $at, %hi(gAdjustViewportHeight) # $at, 0x8012
/* 066B90 80065F90 2484D060 */  addiu $a0, %lo(gAntiPiracyViewport) # addiu $a0, $a0, -0x2fa0
/* 066B94 80065F94 3C03A460 */  lui   $v1, (0xA4600010 >> 16) # lui $v1, 0xa460
/* 066B98 80065F98 A0200D15 */  sb    $zero, %lo(gAdjustViewportHeight)($at)
/* 066B9C 80065F9C 34630010 */  ori   $v1, (0xA4600010 & 0xFFFF) # ori $v1, $v1, 0x10
/* 066BA0 80065FA0 A0800000 */  sb    $zero, ($a0)
/* 066BA4 80065FA4 8C620000 */  lw    $v0, ($v1)
/* 066BA8 80065FA8 3C0EB000 */  lui   $t6, %hi(D_B0000578) # $t6, 0xb000
/* 066BAC 80065FAC 304C0003 */  andi  $t4, $v0, 3
/* 066BB0 80065FB0 11800006 */  beqz  $t4, .L80065FCC
/* 066BB4 80065FB4 3C108012 */   lui   $s0, %hi(gPerspectiveMatrixF) # $s0, 0x8012
.L80065FB8:
/* 066BB8 80065FB8 8C620000 */  lw    $v0, ($v1)
/* 066BBC 80065FBC 00000000 */  nop   
/* 066BC0 80065FC0 304D0003 */  andi  $t5, $v0, 3
/* 066BC4 80065FC4 15A0FFFC */  bnez  $t5, .L80065FB8
/* 066BC8 80065FC8 00000000 */   nop   
.L80065FCC:
/* 066BCC 80065FCC 8DCF0578 */  lw    $t7, %lo(D_B0000578)($t6)
/* 066BD0 80065FD0 34018965 */  li    $at, 0x8965
/* 066BD4 80065FD4 31F8FFFF */  andi  $t8, $t7, 0xffff
/* 066BD8 80065FD8 13010003 */  beq   $t8, $at, .L80065FE8
/* 066BDC 80065FDC 26100EE0 */   addiu $s0, %lo(gPerspectiveMatrixF) # addiu $s0, $s0, 0xee0
/* 066BE0 80065FE0 24190001 */  li    $t9, 1
/* 066BE4 80065FE4 A0990000 */  sb    $t9, ($a0)
.L80065FE8:
/* 066BE8 80065FE8 3C014120 */  li    $at, 0x41200000 # 10.000000
/* 066BEC 80065FEC 44812000 */  mtc1  $at, $f4
/* 066BF0 80065FF0 3C01800E */  lui   $at, %hi(D_800E709C) # $at, 0x800e
/* 066BF4 80065FF4 C426709C */  lwc1  $f6, %lo(D_800E709C)($at)
/* 066BF8 80065FF8 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 066BFC 80065FFC 44814000 */  mtc1  $at, $f8
/* 066C00 80066000 3C058012 */  lui   $a1, %hi(perspNorm) # $a1, 0x8012
/* 066C04 80066004 3C073FAA */  lui   $a3, (0x3FAAAAAB >> 16) # lui $a3, 0x3faa
/* 066C08 80066008 34E7AAAB */  ori   $a3, (0x3FAAAAAB & 0xFFFF) # ori $a3, $a3, 0xaaab
/* 066C0C 8006600C 24A50D6C */  addiu $a1, %lo(perspNorm) # addiu $a1, $a1, 0xd6c
/* 066C10 80066010 02002025 */  move  $a0, $s0
/* 066C14 80066014 3C064270 */  lui   $a2, 0x4270
/* 066C18 80066018 E7A40010 */  swc1  $f4, 0x10($sp)
/* 066C1C 8006601C E7A60014 */  swc1  $f6, 0x14($sp)
/* 066C20 80066020 0C033248 */  jal   guPerspectiveF
/* 066C24 80066024 E7A80018 */   swc1  $f8, 0x18($sp)
/* 066C28 80066028 3C058012 */  lui   $a1, %hi(gProjectionMatrixS) # $a1, 0x8012
/* 066C2C 8006602C 24A50FE0 */  addiu $a1, %lo(gProjectionMatrixS) # addiu $a1, $a1, 0xfe0
/* 066C30 80066030 0C01BE1C */  jal   f32_matrix_to_s16_matrix
/* 066C34 80066034 02002025 */   move  $a0, $s0
/* 066C38 80066038 3C014270 */  li    $at, 0x42700000 # 60.000000
/* 066C3C 8006603C 44815000 */  mtc1  $at, $f10
/* 066C40 80066040 8FBF0034 */  lw    $ra, 0x34($sp)
/* 066C44 80066044 3C018012 */  lui   $at, %hi(gCurCamFOV) # $at, 0x8012
/* 066C48 80066048 8FB00028 */  lw    $s0, 0x28($sp)
/* 066C4C 8006604C 8FB1002C */  lw    $s1, 0x2c($sp)
/* 066C50 80066050 8FB20030 */  lw    $s2, 0x30($sp)
/* 066C54 80066054 27BD0038 */  addiu $sp, $sp, 0x38
/* 066C58 80066058 03E00008 */  jr    $ra
/* 066C5C 8006605C E42A0D10 */   swc1  $f10, %lo(gCurCamFOV)($at)
