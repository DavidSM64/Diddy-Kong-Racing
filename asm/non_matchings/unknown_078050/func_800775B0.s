glabel func_800775B0
/* 0781B0 800775B0 3C03800E */  lui   $v1, %hi(D_800DE4D8) # $v1, 0x800e
/* 0781B4 800775B4 2463E4D8 */  addiu $v1, %lo(D_800DE4D8) # addiu $v1, $v1, -0x1b28
/* 0781B8 800775B8 8C620000 */  lw    $v0, ($v1)
/* 0781BC 800775BC 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0781C0 800775C0 000270C0 */  sll   $t6, $v0, 3
/* 0781C4 800775C4 3C0F8012 */  lui   $t7, %hi(D_80126020) # $t7, 0x8012
/* 0781C8 800775C8 01C27023 */  subu  $t6, $t6, $v0
/* 0781CC 800775CC 000E7100 */  sll   $t6, $t6, 4
/* 0781D0 800775D0 25EF6020 */  addiu $t7, %lo(D_80126020) # addiu $t7, $t7, 0x6020
/* 0781D4 800775D4 24010002 */  li    $at, 2
/* 0781D8 800775D8 24580001 */  addiu $t8, $v0, 1
/* 0781DC 800775DC AFBF0014 */  sw    $ra, 0x14($sp)
/* 0781E0 800775E0 AFA60030 */  sw    $a2, 0x30($sp)
/* 0781E4 800775E4 AFA00020 */  sw    $zero, 0x20($sp)
/* 0781E8 800775E8 01CF3821 */  addu  $a3, $t6, $t7
/* 0781EC 800775EC 17010002 */  bne   $t8, $at, .L800775F8
/* 0781F0 800775F0 AC780000 */   sw    $t8, ($v1)
/* 0781F4 800775F4 AC600000 */  sw    $zero, ($v1)
.L800775F8:
/* 0781F8 800775F8 3C02800E */  lui   $v0, %hi(rspF3DDKRBootStart) # $v0, 0x800e
/* 0781FC 800775FC 3C0D800E */  lui   $t5, %hi(rspF3DDKRDramStart) # $t5, 0x800e
/* 078200 80077600 244284C0 */  addiu $v0, %lo(rspF3DDKRBootStart) # addiu $v0, $v0, -0x7b40
/* 078204 80077604 00A44023 */  subu  $t0, $a1, $a0
/* 078208 80077608 25AD8590 */  addiu $t5, %lo(rspF3DDKRDramStart) # addiu $t5, $t5, -0x7a70
/* 07820C 8007760C 000848C3 */  sra   $t1, $t0, 3
/* 078210 80077610 01A27023 */  subu  $t6, $t5, $v0
/* 078214 80077614 000950C0 */  sll   $t2, $t1, 3
/* 078218 80077618 ACEA0044 */  sw    $t2, 0x44($a3)
/* 07821C 8007761C 240B0001 */  li    $t3, 1
/* 078220 80077620 240C0002 */  li    $t4, 2
/* 078224 80077624 ACEE001C */  sw    $t6, 0x1c($a3)
/* 078228 80077628 3C0F800E */  lui   $t7, %hi(rspF3DDKRXbusStart) # $t7, 0x800e
/* 07822C 8007762C ACEB0010 */  sw    $t3, 0x10($a3)
/* 078230 80077630 ACEC0014 */  sw    $t4, 0x14($a3)
/* 078234 80077634 25EFA970 */  addiu $t7, %lo(rspF3DDKRXbusStart) # addiu $t7, $t7, -0x5690
/* 078238 80077638 3C18800F */  lui   $t8, %hi(rspF3DDKRDataXbusStart) # $t8, 0x800f
/* 07823C 8007763C 3C088012 */  lui   $t0, %hi(gDramStack) # $t0, 0x8012
/* 078240 80077640 3C0A8012 */  lui   $t2, %hi(D_801271B0) # $t2, 0x8012
/* 078244 80077644 3C0D8012 */  lui   $t5, %hi(D_80125ED8) # $t5, 0x8012
/* 078248 80077648 3C0E800E */  lui   $t6, %hi(D_800DE490) # $t6, 0x800e
/* 07824C 8007764C ACEF0020 */  sw    $t7, 0x20($a3)
/* 078250 80077650 2718ABA0 */  addiu $t8, %lo(rspF3DDKRDataXbusStart) # addiu $t8, $t8, -0x5460
/* 078254 80077654 24190800 */  li    $t9, 2048
/* 078258 80077658 250842A0 */  addiu $t0, %lo(gDramStack) # addiu $t0, $t0, 0x42a0
/* 07825C 8007765C 24090400 */  li    $t1, 1024
/* 078260 80077660 254A71B0 */  addiu $t2, %lo(D_801271B0) # addiu $t2, $t2, 0x71b0
/* 078264 80077664 240B0A00 */  li    $t3, 2560
/* 078268 80077668 240C0003 */  li    $t4, 3
/* 07826C 8007766C 25AD5ED8 */  addiu $t5, %lo(D_80125ED8) # addiu $t5, $t5, 0x5ed8
/* 078270 80077670 25CEE490 */  addiu $t6, %lo(D_800DE490) # addiu $t6, $t6, -0x1b70
/* 078274 80077674 ACE40040 */  sw    $a0, 0x40($a3)
/* 078278 80077678 ACE20018 */  sw    $v0, 0x18($a3)
/* 07827C 8007767C ACF80028 */  sw    $t8, 0x28($a3)
/* 078280 80077680 ACF9002C */  sw    $t9, 0x2c($a3)
/* 078284 80077684 ACE80030 */  sw    $t0, 0x30($a3)
/* 078288 80077688 ACE90034 */  sw    $t1, 0x34($a3)
/* 07828C 8007768C ACEA0048 */  sw    $t2, 0x48($a3)
/* 078290 80077690 ACEB004C */  sw    $t3, 0x4c($a3)
/* 078294 80077694 ACE00038 */  sw    $zero, 0x38($a3)
/* 078298 80077698 ACE0003C */  sw    $zero, 0x3c($a3)
/* 07829C 8007769C ACE00000 */  sw    $zero, ($a3)
/* 0782A0 800776A0 ACEC0008 */  sw    $t4, 8($a3)
/* 0782A4 800776A4 ACED0050 */  sw    $t5, 0x50($a3)
/* 0782A8 800776A8 ACEE0054 */  sw    $t6, 0x54($a3)
/* 0782AC 800776AC 3C0F8012 */  lui   $t7, %hi(gVideoCurrFramebuffer) # $t7, 0x8012
/* 0782B0 800776B0 8DEF62D4 */  lw    $t7, %lo(gVideoCurrFramebuffer)($t7)
/* 0782B4 800776B4 3C02FF00 */  lui   $v0, (0xFF0000FF >> 16) # lui $v0, 0xff00
/* 0782B8 800776B8 344200FF */  ori   $v0, (0xFF0000FF & 0xFFFF) # ori $v0, $v0, 0xff
/* 0782BC 800776BC 240300FF */  li    $v1, 255
/* 0782C0 800776C0 ACE20058 */  sw    $v0, 0x58($a3)
/* 0782C4 800776C4 ACE2005C */  sw    $v0, 0x5c($a3)
/* 0782C8 800776C8 ACE30060 */  sw    $v1, 0x60($a3)
/* 0782CC 800776CC ACE30064 */  sw    $v1, 0x64($a3)
/* 0782D0 800776D0 ACE00068 */  sw    $zero, 0x68($a3)
/* 0782D4 800776D4 ACEF000C */  sw    $t7, 0xc($a3)
/* 0782D8 800776D8 8FB80030 */  lw    $t8, 0x30($sp)
/* 0782DC 800776DC 3C198012 */  lui   $t9, %hi(D_80125EA0) # $t9, 0x8012
/* 0782E0 800776E0 13000002 */  beqz  $t8, .L800776EC
/* 0782E4 800776E4 27395EA0 */   addiu $t9, %lo(D_80125EA0) # addiu $t9, $t9, 0x5ea0
/* 0782E8 800776E8 ACF90050 */  sw    $t9, 0x50($a3)
.L800776EC:
/* 0782EC 800776EC 0C034628 */  jal   osWritebackDCacheAll
/* 0782F0 800776F0 AFA70024 */   sw    $a3, 0x24($sp)
/* 0782F4 800776F4 3C048012 */  lui   $a0, %hi(osScInterruptQ) # $a0, 0x8012
/* 0782F8 800776F8 8FA50024 */  lw    $a1, 0x24($sp)
/* 0782FC 800776FC 8C846100 */  lw    $a0, %lo(osScInterruptQ)($a0)
/* 078300 80077700 0C03238C */  jal   osSendMesg
/* 078304 80077704 24060001 */   li    $a2, 1
/* 078308 80077708 8FA80030 */  lw    $t0, 0x30($sp)
/* 07830C 8007770C 3C048012 */  lui   $a0, %hi(D_80125EA0) # $a0, 0x8012
/* 078310 80077710 11000004 */  beqz  $t0, .L80077724
/* 078314 80077714 24845EA0 */   addiu $a0, %lo(D_80125EA0) # addiu $a0, $a0, 0x5ea0
/* 078318 80077718 27A50020 */  addiu $a1, $sp, 0x20
/* 07831C 8007771C 0C0322EC */  jal   osRecvMesg
/* 078320 80077720 24060001 */   li    $a2, 1
.L80077724:
/* 078324 80077724 8FBF0014 */  lw    $ra, 0x14($sp)
/* 078328 80077728 27BD0028 */  addiu $sp, $sp, 0x28
/* 07832C 8007772C 03E00008 */  jr    $ra
/* 078330 80077730 00000000 */   nop   