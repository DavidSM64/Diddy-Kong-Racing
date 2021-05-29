glabel func_800AC5A4
/* 0AD1A4 800AC5A4 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0AD1A8 800AC5A8 AFB10018 */  sw    $s1, 0x18($sp)
/* 0AD1AC 800AC5AC 3C11800E */  lui   $s1, %hi(D_800E28D8) # $s1, 0x800e
/* 0AD1B0 800AC5B0 263128D8 */  addiu $s1, %lo(D_800E28D8) # addiu $s1, $s1, 0x28d8
/* 0AD1B4 800AC5B4 8E2E0008 */  lw    $t6, 8($s1)
/* 0AD1B8 800AC5B8 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0AD1BC 800AC5BC AFB50028 */  sw    $s5, 0x28($sp)
/* 0AD1C0 800AC5C0 AFB40024 */  sw    $s4, 0x24($sp)
/* 0AD1C4 800AC5C4 AFB30020 */  sw    $s3, 0x20($sp)
/* 0AD1C8 800AC5C8 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0AD1CC 800AC5CC 11C00097 */  beqz  $t6, .L800AC82C
/* 0AD1D0 800AC5D0 AFB00014 */   sw    $s0, 0x14($sp)
/* 0AD1D4 800AC5D4 3C13800E */  lui   $s3, %hi(D_800E2908) # $s3, 0x800e
/* 0AD1D8 800AC5D8 26732908 */  addiu $s3, %lo(D_800E2908) # addiu $s3, $s3, 0x2908
/* 0AD1DC 800AC5DC 8E790000 */  lw    $t9, ($s3)
/* 0AD1E0 800AC5E0 3C148012 */  lui   $s4, %hi(D_80127C00) # $s4, 0x8012
/* 0AD1E4 800AC5E4 3C158012 */  lui   $s5, %hi(D_80127C04) # $s5, 0x8012
/* 0AD1E8 800AC5E8 26B57C04 */  addiu $s5, %lo(D_80127C04) # addiu $s5, $s5, 0x7c04
/* 0AD1EC 800AC5EC 26947C00 */  addiu $s4, %lo(D_80127C00) # addiu $s4, $s4, 0x7c00
/* 0AD1F0 800AC5F0 240F0004 */  li    $t7, 4
/* 0AD1F4 800AC5F4 24180002 */  li    $t8, 2
/* 0AD1F8 800AC5F8 2B210004 */  slti  $at, $t9, 4
/* 0AD1FC 800AC5FC AE8F0000 */  sw    $t7, ($s4)
/* 0AD200 800AC600 1420008A */  bnez  $at, .L800AC82C
/* 0AD204 800AC604 AEB80000 */   sw    $t8, ($s5)
/* 0AD208 800AC608 0C01A76C */  jal   func_80069DB0
/* 0AD20C 800AC60C AFA00034 */   sw    $zero, 0x34($sp)
/* 0AD210 800AC610 3C108012 */  lui   $s0, %hi(D_80127C0C) # $s0, 0x8012
/* 0AD214 800AC614 26107C0C */  addiu $s0, %lo(D_80127C0C) # addiu $s0, $s0, 0x7c0c
/* 0AD218 800AC618 8E030000 */  lw    $v1, ($s0)
/* 0AD21C 800AC61C 3C0B8000 */  lui   $t3, 0x8000
/* 0AD220 800AC620 246E0008 */  addiu $t6, $v1, 8
/* 0AD224 800AC624 AE0E0000 */  sw    $t6, ($s0)
/* 0AD228 800AC628 3C0F0100 */  lui   $t7, (0x01000040 >> 16) # lui $t7, 0x100
/* 0AD22C 800AC62C 35EF0040 */  ori   $t7, (0x01000040 & 0xFFFF) # ori $t7, $t7, 0x40
/* 0AD230 800AC630 004BC021 */  addu  $t8, $v0, $t3
/* 0AD234 800AC634 AC780004 */  sw    $t8, 4($v1)
/* 0AD238 800AC638 AC6F0000 */  sw    $t7, ($v1)
/* 0AD23C 800AC63C 8E030000 */  lw    $v1, ($s0)
/* 0AD240 800AC640 3C0EBC00 */  lui   $t6, (0xBC00000A >> 16) # lui $t6, 0xbc00
/* 0AD244 800AC644 24790008 */  addiu $t9, $v1, 8
/* 0AD248 800AC648 AE190000 */  sw    $t9, ($s0)
/* 0AD24C 800AC64C 35CE000A */  ori   $t6, (0xBC00000A & 0xFFFF) # ori $t6, $t6, 0xa
/* 0AD250 800AC650 AC6E0000 */  sw    $t6, ($v1)
/* 0AD254 800AC654 AC600004 */  sw    $zero, 4($v1)
/* 0AD258 800AC658 8E250008 */  lw    $a1, 8($s1)
/* 0AD25C 800AC65C 02002025 */  move  $a0, $s0
/* 0AD260 800AC660 0C01ED32 */  jal   func_8007B4C8
/* 0AD264 800AC664 24060002 */   li    $a2, 2
/* 0AD268 800AC668 8E820000 */  lw    $v0, ($s4)
/* 0AD26C 800AC66C 8E690000 */  lw    $t1, ($s3)
/* 0AD270 800AC670 8FA80034 */  lw    $t0, 0x34($sp)
/* 0AD274 800AC674 0049082A */  slt   $at, $v0, $t1
/* 0AD278 800AC678 10200038 */  beqz  $at, .L800AC75C
/* 0AD27C 800AC67C 3C0B8000 */   lui   $t3, 0x8000
/* 0AD280 800AC680 3C12800E */  lui   $s2, %hi(D_800E290C) # $s2, 0x800e
/* 0AD284 800AC684 3C0D800E */  lui   $t5, %hi(D_800E2904) # $t5, 0x800e
/* 0AD288 800AC688 25AD2904 */  addiu $t5, %lo(D_800E2904) # addiu $t5, $t5, 0x2904
/* 0AD28C 800AC68C 2652290C */  addiu $s2, %lo(D_800E290C) # addiu $s2, $s2, 0x290c
/* 0AD290 800AC690 3C110500 */  lui   $s1, 0x500
/* 0AD294 800AC694 3C1F0400 */  lui   $ra, 0x400
/* 0AD298 800AC698 240C000A */  li    $t4, 10
.L800AC69C:
/* 0AD29C 800AC69C 010C0019 */  multu $t0, $t4
/* 0AD2A0 800AC6A0 8DB80000 */  lw    $t8, ($t5)
/* 0AD2A4 800AC6A4 8E030000 */  lw    $v1, ($s0)
/* 0AD2A8 800AC6A8 244EFFFF */  addiu $t6, $v0, -1
/* 0AD2AC 800AC6AC 24790008 */  addiu $t9, $v1, 8
/* 0AD2B0 800AC6B0 AE190000 */  sw    $t9, ($s0)
/* 0AD2B4 800AC6B4 00007812 */  mflo  $t7
/* 0AD2B8 800AC6B8 01F85021 */  addu  $t2, $t7, $t8
/* 0AD2BC 800AC6BC 014B3821 */  addu  $a3, $t2, $t3
/* 0AD2C0 800AC6C0 30F80006 */  andi  $t8, $a3, 6
/* 0AD2C4 800AC6C4 000E78C0 */  sll   $t7, $t6, 3
/* 0AD2C8 800AC6C8 01F8C825 */  or    $t9, $t7, $t8
/* 0AD2CC 800AC6CC 332E00FF */  andi  $t6, $t9, 0xff
/* 0AD2D0 800AC6D0 000E7C00 */  sll   $t7, $t6, 0x10
/* 0AD2D4 800AC6D4 0002C8C0 */  sll   $t9, $v0, 3
/* 0AD2D8 800AC6D8 03227021 */  addu  $t6, $t9, $v0
/* 0AD2DC 800AC6DC 01FFC025 */  or    $t8, $t7, $ra
/* 0AD2E0 800AC6E0 000E7840 */  sll   $t7, $t6, 1
/* 0AD2E4 800AC6E4 25F90008 */  addiu $t9, $t7, 8
/* 0AD2E8 800AC6E8 332EFFFF */  andi  $t6, $t9, 0xffff
/* 0AD2EC 800AC6EC 030E7825 */  or    $t7, $t8, $t6
/* 0AD2F0 800AC6F0 AC6F0000 */  sw    $t7, ($v1)
/* 0AD2F4 800AC6F4 AC670004 */  sw    $a3, 4($v1)
/* 0AD2F8 800AC6F8 8EA60000 */  lw    $a2, ($s5)
/* 0AD2FC 800AC6FC 8E030000 */  lw    $v1, ($s0)
/* 0AD300 800AC700 24D8FFFF */  addiu $t8, $a2, -1
/* 0AD304 800AC704 00187100 */  sll   $t6, $t8, 4
/* 0AD308 800AC708 24790008 */  addiu $t9, $v1, 8
/* 0AD30C 800AC70C AE190000 */  sw    $t9, ($s0)
/* 0AD310 800AC710 35CF0001 */  ori   $t7, $t6, 1
/* 0AD314 800AC714 31F900FF */  andi  $t9, $t7, 0xff
/* 0AD318 800AC718 0019C400 */  sll   $t8, $t9, 0x10
/* 0AD31C 800AC71C 00067900 */  sll   $t7, $a2, 4
/* 0AD320 800AC720 31F9FFFF */  andi  $t9, $t7, 0xffff
/* 0AD324 800AC724 03117025 */  or    $t6, $t8, $s1
/* 0AD328 800AC728 01D9C025 */  or    $t8, $t6, $t9
/* 0AD32C 800AC72C AC780000 */  sw    $t8, ($v1)
/* 0AD330 800AC730 8E4F0000 */  lw    $t7, ($s2)
/* 0AD334 800AC734 00000000 */  nop   
/* 0AD338 800AC738 01EB7021 */  addu  $t6, $t7, $t3
/* 0AD33C 800AC73C AC6E0004 */  sw    $t6, 4($v1)
/* 0AD340 800AC740 8E820000 */  lw    $v0, ($s4)
/* 0AD344 800AC744 8E690000 */  lw    $t1, ($s3)
/* 0AD348 800AC748 01024021 */  addu  $t0, $t0, $v0
/* 0AD34C 800AC74C 0102C821 */  addu  $t9, $t0, $v0
/* 0AD350 800AC750 0329082A */  slt   $at, $t9, $t1
/* 0AD354 800AC754 1420FFD1 */  bnez  $at, .L800AC69C
/* 0AD358 800AC758 00000000 */   nop   
.L800AC75C:
/* 0AD35C 800AC75C 240C000A */  li    $t4, 10
/* 0AD360 800AC760 010C0019 */  multu $t0, $t4
/* 0AD364 800AC764 3C0D800E */  lui   $t5, %hi(D_800E2904) # $t5, 0x800e
/* 0AD368 800AC768 25AD2904 */  addiu $t5, %lo(D_800E2904) # addiu $t5, $t5, 0x2904
/* 0AD36C 800AC76C 8DAF0000 */  lw    $t7, ($t5)
/* 0AD370 800AC770 8E030000 */  lw    $v1, ($s0)
/* 0AD374 800AC774 01281023 */  subu  $v0, $t1, $t0
/* 0AD378 800AC778 2459FFFF */  addiu $t9, $v0, -1
/* 0AD37C 800AC77C 246E0008 */  addiu $t6, $v1, 8
/* 0AD380 800AC780 AE0E0000 */  sw    $t6, ($s0)
/* 0AD384 800AC784 3C1F0400 */  lui   $ra, 0x400
/* 0AD388 800AC788 3C110500 */  lui   $s1, 0x500
/* 0AD38C 800AC78C 3C12800E */  lui   $s2, %hi(D_800E290C) # $s2, 0x800e
/* 0AD390 800AC790 0000C012 */  mflo  $t8
/* 0AD394 800AC794 030F5021 */  addu  $t2, $t8, $t7
/* 0AD398 800AC798 014B3821 */  addu  $a3, $t2, $t3
/* 0AD39C 800AC79C 30EF0006 */  andi  $t7, $a3, 6
/* 0AD3A0 800AC7A0 0019C0C0 */  sll   $t8, $t9, 3
/* 0AD3A4 800AC7A4 030F7025 */  or    $t6, $t8, $t7
/* 0AD3A8 800AC7A8 31D900FF */  andi  $t9, $t6, 0xff
/* 0AD3AC 800AC7AC 0019C400 */  sll   $t8, $t9, 0x10
/* 0AD3B0 800AC7B0 000270C0 */  sll   $t6, $v0, 3
/* 0AD3B4 800AC7B4 01C2C821 */  addu  $t9, $t6, $v0
/* 0AD3B8 800AC7B8 031F7825 */  or    $t7, $t8, $ra
/* 0AD3BC 800AC7BC 0019C040 */  sll   $t8, $t9, 1
/* 0AD3C0 800AC7C0 270E0008 */  addiu $t6, $t8, 8
/* 0AD3C4 800AC7C4 31D9FFFF */  andi  $t9, $t6, 0xffff
/* 0AD3C8 800AC7C8 01F9C025 */  or    $t8, $t7, $t9
/* 0AD3CC 800AC7CC AC780000 */  sw    $t8, ($v1)
/* 0AD3D0 800AC7D0 AC670004 */  sw    $a3, 4($v1)
/* 0AD3D4 800AC7D4 8E6F0000 */  lw    $t7, ($s3)
/* 0AD3D8 800AC7D8 8E030000 */  lw    $v1, ($s0)
/* 0AD3DC 800AC7DC 01E83023 */  subu  $a2, $t7, $t0
/* 0AD3E0 800AC7E0 0006C843 */  sra   $t9, $a2, 1
/* 0AD3E4 800AC7E4 246E0008 */  addiu $t6, $v1, 8
/* 0AD3E8 800AC7E8 AE0E0000 */  sw    $t6, ($s0)
/* 0AD3EC 800AC7EC 2738FFFF */  addiu $t8, $t9, -1
/* 0AD3F0 800AC7F0 00187100 */  sll   $t6, $t8, 4
/* 0AD3F4 800AC7F4 35CF0001 */  ori   $t7, $t6, 1
/* 0AD3F8 800AC7F8 03203025 */  move  $a2, $t9
/* 0AD3FC 800AC7FC 31F900FF */  andi  $t9, $t7, 0xff
/* 0AD400 800AC800 0019C400 */  sll   $t8, $t9, 0x10
/* 0AD404 800AC804 00067900 */  sll   $t7, $a2, 4
/* 0AD408 800AC808 31F9FFFF */  andi  $t9, $t7, 0xffff
/* 0AD40C 800AC80C 03117025 */  or    $t6, $t8, $s1
/* 0AD410 800AC810 01D9C025 */  or    $t8, $t6, $t9
/* 0AD414 800AC814 2652290C */  addiu $s2, %lo(D_800E290C) # addiu $s2, $s2, 0x290c
/* 0AD418 800AC818 AC780000 */  sw    $t8, ($v1)
/* 0AD41C 800AC81C 8E4F0000 */  lw    $t7, ($s2)
/* 0AD420 800AC820 00000000 */  nop   
/* 0AD424 800AC824 01EB7021 */  addu  $t6, $t7, $t3
/* 0AD428 800AC828 AC6E0004 */  sw    $t6, 4($v1)
.L800AC82C:
/* 0AD42C 800AC82C 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0AD430 800AC830 8FB00014 */  lw    $s0, 0x14($sp)
/* 0AD434 800AC834 8FB10018 */  lw    $s1, 0x18($sp)
/* 0AD438 800AC838 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0AD43C 800AC83C 8FB30020 */  lw    $s3, 0x20($sp)
/* 0AD440 800AC840 8FB40024 */  lw    $s4, 0x24($sp)
/* 0AD444 800AC844 8FB50028 */  lw    $s5, 0x28($sp)
/* 0AD448 800AC848 03E00008 */  jr    $ra
/* 0AD44C 800AC84C 27BD0038 */   addiu $sp, $sp, 0x38

/* 0AD450 800AC850 240E0001 */  li    $t6, 1
/* 0AD454 800AC854 3C01800E */  lui   $at, %hi(D_800E2A84) # $at, 0x800e
/* 0AD458 800AC858 03E00008 */  jr    $ra
/* 0AD45C 800AC85C AC2E2A84 */   sw    $t6, %lo(D_800E2A84)($at)

/* 0AD460 800AC860 3C0E800E */  lui   $t6, %hi(D_800E2A80) # $t6, 0x800e
/* 0AD464 800AC864 8DCE2A80 */  lw    $t6, %lo(D_800E2A80)($t6)
/* 0AD468 800AC868 3C01800E */  lui   $at, %hi(D_800E2A84) # $at, 0x800e
/* 0AD46C 800AC86C 11C00002 */  beqz  $t6, .L800AC878
/* 0AD470 800AC870 00000000 */   nop   
/* 0AD474 800AC874 AC202A84 */  sw    $zero, %lo(D_800E2A84)($at)
.L800AC878:
/* 0AD478 800AC878 03E00008 */  jr    $ra
/* 0AD47C 800AC87C 00000000 */   nop   

