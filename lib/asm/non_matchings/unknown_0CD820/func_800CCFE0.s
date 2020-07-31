glabel func_800CCFE0
/* 0CDBE0 800CCFE0 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0CDBE4 800CCFE4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CDBE8 800CCFE8 AFA40020 */  sw    $a0, 0x20($sp)
/* 0CDBEC 800CCFEC 0C033594 */  jal   __osSiGetAccess
/* 0CDBF0 800CCFF0 AFA0001C */   sw    $zero, 0x1c($sp)
/* 0CDBF4 800CCFF4 3C0E8013 */  lui   $t6, %hi(D_8012CD90) # $t6, 0x8013
/* 0CDBF8 800CCFF8 91CECD90 */  lbu   $t6, %lo(D_8012CD90)($t6)
/* 0CDBFC 800CCFFC 24010001 */  li    $at, 1
/* 0CDC00 800CD000 11C1000C */  beq   $t6, $at, .L800CD034
/* 0CDC04 800CD004 00000000 */   nop   
/* 0CDC08 800CD008 0C033453 */  jal   func_800CD14C
/* 0CDC0C 800CD00C 00000000 */   nop   
/* 0CDC10 800CD010 3C058013 */  lui   $a1, %hi(D_8012CD50) # $a1, 0x8013
/* 0CDC14 800CD014 24A5CD50 */  addiu $a1, %lo(D_8012CD50) # addiu $a1, $a1, -0x32b0
/* 0CDC18 800CD018 0C0335B0 */  jal   __osSiRawStartDma
/* 0CDC1C 800CD01C 24040001 */   li    $a0, 1
/* 0CDC20 800CD020 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0CDC24 800CD024 8FA40020 */  lw    $a0, 0x20($sp)
/* 0CDC28 800CD028 00002825 */  move  $a1, $zero
/* 0CDC2C 800CD02C 0C0322EC */  jal   osRecvMesg
/* 0CDC30 800CD030 24060001 */   li    $a2, 1
.L800CD034:
/* 0CDC34 800CD034 AFA00018 */  sw    $zero, 0x18($sp)
.L800CD038:
/* 0CDC38 800CD038 8FB80018 */  lw    $t8, 0x18($sp)
/* 0CDC3C 800CD03C 8FA80018 */  lw    $t0, 0x18($sp)
/* 0CDC40 800CD040 3C018013 */  lui   $at, 0x8013
/* 0CDC44 800CD044 0018C880 */  sll   $t9, $t8, 2
/* 0CDC48 800CD048 00390821 */  addu  $at, $at, $t9
/* 0CDC4C 800CD04C 240F00FF */  li    $t7, 255
/* 0CDC50 800CD050 AC2FCD50 */  sw    $t7, -0x32b0($at)
/* 0CDC54 800CD054 25090001 */  addiu $t1, $t0, 1
/* 0CDC58 800CD058 29210010 */  slti  $at, $t1, 0x10
/* 0CDC5C 800CD05C 1420FFF6 */  bnez  $at, .L800CD038
/* 0CDC60 800CD060 AFA90018 */   sw    $t1, 0x18($sp)
/* 0CDC64 800CD064 3C018013 */  lui   $at, %hi(D_8012CD8C) # $at, 0x8013
/* 0CDC68 800CD068 3C058013 */  lui   $a1, %hi(D_8012CD50) # $a1, 0x8013
/* 0CDC6C 800CD06C AC20CD8C */  sw    $zero, %lo(D_8012CD8C)($at)
/* 0CDC70 800CD070 24A5CD50 */  addiu $a1, %lo(D_8012CD50) # addiu $a1, $a1, -0x32b0
/* 0CDC74 800CD074 0C0335B0 */  jal   __osSiRawStartDma
/* 0CDC78 800CD078 00002025 */   move  $a0, $zero
/* 0CDC7C 800CD07C 240A0001 */  li    $t2, 1
/* 0CDC80 800CD080 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CDC84 800CD084 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0CDC88 800CD088 0C0335A5 */  jal   __osSiRelAccess
/* 0CDC8C 800CD08C A02ACD90 */   sb    $t2, %lo(D_8012CD90)($at)
/* 0CDC90 800CD090 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CDC94 800CD094 8FA2001C */  lw    $v0, 0x1c($sp)
/* 0CDC98 800CD098 27BD0020 */  addiu $sp, $sp, 0x20
/* 0CDC9C 800CD09C 03E00008 */  jr    $ra
/* 0CDCA0 800CD0A0 00000000 */   nop   

