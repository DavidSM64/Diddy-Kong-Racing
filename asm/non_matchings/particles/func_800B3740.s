glabel func_800B3740
/* B4340 800B3740 27BDFFC0 */  addiu      $sp, $sp, -0x40
/* B4344 800B3744 AFBF0024 */  sw         $ra, 0x24($sp)
/* B4348 800B3748 AFB10020 */  sw         $s1, 0x20($sp)
/* B434C 800B374C AFB0001C */  sw         $s0, 0x1C($sp)
/* B4350 800B3750 AFA60048 */  sw         $a2, 0x48($sp)
/* B4354 800B3754 AFA7004C */  sw         $a3, 0x4C($sp)
/* B4358 800B3758 8C8E0040 */  lw         $t6, 0x40($a0)
/* B435C 800B375C 8FAF0050 */  lw         $t7, 0x50($sp)
/* B4360 800B3760 00A08025 */  or         $s0, $a1, $zero
/* B4364 800B3764 01CFC024 */  and        $t8, $t6, $t7
/* B4368 800B3768 00808825 */  or         $s1, $a0, $zero
/* B436C 800B376C 13000007 */  beqz       $t8, .L800B378C_B438C
/* B4370 800B3770 240B000A */   addiu     $t3, $zero, 0xA
/* B4374 800B3774 3C19800E */  lui        $t9, %hi(D_800E2CDC)
/* B4378 800B3778 8F392CDC */  lw         $t9, %lo(D_800E2CDC)($t9)
/* B437C 800B377C 00000000 */  nop
/* B4380 800B3780 2B210200 */  slti       $at, $t9, 0x200
/* B4384 800B3784 142001B2 */  bnez       $at, .L800B3E50_B4A50
/* B4388 800B3788 00000000 */   nop
.L800B378C_B438C:
/* B438C 800B378C 862A005C */  lh         $t2, 0x5C($s1)
/* B4390 800B3790 00000000 */  nop
/* B4394 800B3794 000A6203 */  sra        $t4, $t2, 8
/* B4398 800B3798 318A00FF */  andi       $t2, $t4, 0xFF
/* B439C 800B379C 194001AC */  blez       $t2, .L800B3E50_B4A50
/* B43A0 800B37A0 00000000 */   nop
/* B43A4 800B37A4 8623002C */  lh         $v1, 0x2C($s1)
/* B43A8 800B37A8 24050004 */  addiu      $a1, $zero, 0x4
/* B43AC 800B37AC 10A300B3 */  beq        $a1, $v1, .L800B3A7C_B467C
/* B43B0 800B37B0 24010003 */   addiu     $at, $zero, 0x3
/* B43B4 800B37B4 106100B1 */  beq        $v1, $at, .L800B3A7C_B467C
/* B43B8 800B37B8 240900FF */   addiu     $t1, $zero, 0xFF
/* B43BC 800B37BC 8E020000 */  lw         $v0, 0x0($s0)
/* B43C0 800B37C0 3C0FFB00 */  lui        $t7, (0xFB000000 >> 16)
/* B43C4 800B37C4 244E0008 */  addiu      $t6, $v0, 0x8
/* B43C8 800B37C8 AE0E0000 */  sw         $t6, 0x0($s0)
/* B43CC 800B37CC AC4F0000 */  sw         $t7, 0x0($v0)
/* B43D0 800B37D0 922E006D */  lbu        $t6, 0x6D($s1)
/* B43D4 800B37D4 9239006C */  lbu        $t9, 0x6C($s1)
/* B43D8 800B37D8 922D006E */  lbu        $t5, 0x6E($s1)
/* B43DC 800B37DC 000E7C00 */  sll        $t7, $t6, 16
/* B43E0 800B37E0 00196600 */  sll        $t4, $t9, 24
/* B43E4 800B37E4 9239006F */  lbu        $t9, 0x6F($s1)
/* B43E8 800B37E8 018FC025 */  or         $t8, $t4, $t7
/* B43EC 800B37EC 000D7200 */  sll        $t6, $t5, 8
/* B43F0 800B37F0 030E6025 */  or         $t4, $t8, $t6
/* B43F4 800B37F4 01996825 */  or         $t5, $t4, $t9
/* B43F8 800B37F8 11490012 */  beq        $t2, $t1, .L800B3844_B4444
/* B43FC 800B37FC AC4D0004 */   sw        $t5, 0x4($v0)
/* B4400 800B3800 8E040000 */  lw         $a0, 0x0($s0)
/* B4404 800B3804 3C0EFA00 */  lui        $t6, (0xFA000000 >> 16)
/* B4408 800B3808 24980008 */  addiu      $t8, $a0, 0x8
/* B440C 800B380C AE180000 */  sw         $t8, 0x0($s0)
/* B4410 800B3810 AC8E0000 */  sw         $t6, 0x0($a0)
/* B4414 800B3814 8623004A */  lh         $v1, 0x4A($s1)
/* B4418 800B3818 240B010E */  addiu      $t3, $zero, 0x10E
/* B441C 800B381C 306F00FF */  andi       $t7, $v1, 0xFF
/* B4420 800B3820 000F6600 */  sll        $t4, $t7, 24
/* B4424 800B3824 000FCC00 */  sll        $t9, $t7, 16
/* B4428 800B3828 000FC200 */  sll        $t8, $t7, 8
/* B442C 800B382C 01996825 */  or         $t5, $t4, $t9
/* B4430 800B3830 01B87025 */  or         $t6, $t5, $t8
/* B4434 800B3834 314F00FF */  andi       $t7, $t2, 0xFF
/* B4438 800B3838 01CF6025 */  or         $t4, $t6, $t7
/* B443C 800B383C 10000008 */  b          .L800B3860_B4460
/* B4440 800B3840 AC8C0004 */   sw        $t4, 0x4($a0)
.L800B3844_B4444:
/* B4444 800B3844 8E020000 */  lw         $v0, 0x0($s0)
/* B4448 800B3848 3C0DFA00 */  lui        $t5, (0xFA000000 >> 16)
/* B444C 800B384C 24590008 */  addiu      $t9, $v0, 0x8
/* B4450 800B3850 AE190000 */  sw         $t9, 0x0($s0)
/* B4454 800B3854 2418FFFF */  addiu      $t8, $zero, -0x1
/* B4458 800B3858 AC580004 */  sw         $t8, 0x4($v0)
/* B445C 800B385C AC4D0000 */  sw         $t5, 0x0($v0)
.L800B3860_B4460:
/* B4460 800B3860 862E002C */  lh         $t6, 0x2C($s1)
/* B4464 800B3864 24010080 */  addiu      $at, $zero, 0x80
/* B4468 800B3868 15C10026 */  bne        $t6, $at, .L800B3904_B4504
/* B446C 800B386C 00000000 */   nop
/* B4470 800B3870 86230018 */  lh         $v1, 0x18($s1)
/* B4474 800B3874 8E280044 */  lw         $t0, 0x44($s1)
/* B4478 800B3878 00037A03 */  sra        $t7, $v1, 8
/* B447C 800B387C A62F0018 */  sh         $t7, 0x18($s1)
/* B4480 800B3880 862C0018 */  lh         $t4, 0x18($s1)
/* B4484 800B3884 850D0000 */  lh         $t5, 0x0($t0)
/* B4488 800B3888 01890019 */  multu      $t4, $t1
/* B448C 800B388C 00601025 */  or         $v0, $v1, $zero
/* B4490 800B3890 02002025 */  or         $a0, $s0, $zero
/* B4494 800B3894 02203825 */  or         $a3, $s1, $zero
/* B4498 800B3898 0000C812 */  mflo       $t9
/* B449C 800B389C 00000000 */  nop
/* B44A0 800B38A0 00000000 */  nop
/* B44A4 800B38A4 032D001A */  div        $zero, $t9, $t5
/* B44A8 800B38A8 15A00002 */  bnez       $t5, .L800B38B4_B44B4
/* B44AC 800B38AC 00000000 */   nop
/* B44B0 800B38B0 0007000D */  break      7
.L800B38B4_B44B4:
/* B44B4 800B38B4 2401FFFF */  addiu      $at, $zero, -0x1
/* B44B8 800B38B8 15A10004 */  bne        $t5, $at, .L800B38CC_B44CC
/* B44BC 800B38BC 3C018000 */   lui       $at, (0x80000000 >> 16)
/* B44C0 800B38C0 17210002 */  bne        $t9, $at, .L800B38CC_B44CC
/* B44C4 800B38C4 00000000 */   nop
/* B44C8 800B38C8 0006000D */  break      6
.L800B38CC_B44CC:
/* B44CC 800B38CC 0000C012 */  mflo       $t8
/* B44D0 800B38D0 A6380018 */  sh         $t8, 0x18($s1)
/* B44D4 800B38D4 8FA6004C */  lw         $a2, 0x4C($sp)
/* B44D8 800B38D8 8FA50048 */  lw         $a1, 0x48($sp)
/* B44DC 800B38DC AFAA0038 */  sw         $t2, 0x38($sp)
/* B44E0 800B38E0 AFA20034 */  sw         $v0, 0x34($sp)
/* B44E4 800B38E4 AFAB0014 */  sw         $t3, 0x14($sp)
/* B44E8 800B38E8 0C01A145 */  jal        render_sprite_billboard
/* B44EC 800B38EC AFA80010 */   sw        $t0, 0x10($sp)
/* B44F0 800B38F0 8FA20034 */  lw         $v0, 0x34($sp)
/* B44F4 800B38F4 8FAA0038 */  lw         $t2, 0x38($sp)
/* B44F8 800B38F8 240900FF */  addiu      $t1, $zero, 0xFF
/* B44FC 800B38FC 10000048 */  b          .L800B3A20_B4620
/* B4500 800B3900 A6220018 */   sh        $v0, 0x18($s1)
.L800B3904_B4504:
/* B4504 800B3904 8E230044 */  lw         $v1, 0x44($s1)
/* B4508 800B3908 8FA50048 */  lw         $a1, 0x48($sp)
/* B450C 800B390C 8C6E0000 */  lw         $t6, 0x0($v1)
/* B4510 800B3910 02002025 */  or         $a0, $s0, $zero
/* B4514 800B3914 11C00042 */  beqz       $t6, .L800B3A20_B4620
/* B4518 800B3918 02203025 */   or        $a2, $s1, $zero
/* B451C 800B391C 44802000 */  mtc1       $zero, $f4
/* B4520 800B3920 3C073F80 */  lui        $a3, (0x3F800000 >> 16)
/* B4524 800B3924 AFA30030 */  sw         $v1, 0x30($sp)
/* B4528 800B3928 AFAA0038 */  sw         $t2, 0x38($sp)
/* B452C 800B392C AFAB003C */  sw         $t3, 0x3C($sp)
/* B4530 800B3930 0C01A521 */  jal        camera_push_model_mtx
/* B4534 800B3934 E7A40010 */   swc1      $f4, 0x10($sp)
/* B4538 800B3938 8FA30030 */  lw         $v1, 0x30($sp)
/* B453C 800B393C 86270018 */  lh         $a3, 0x18($s1)
/* B4540 800B3940 8FA6003C */  lw         $a2, 0x3C($sp)
/* B4544 800B3944 8C650000 */  lw         $a1, 0x0($v1)
/* B4548 800B3948 00077A00 */  sll        $t7, $a3, 8
/* B454C 800B394C 01E03825 */  or         $a3, $t7, $zero
/* B4550 800B3950 0C01ED3A */  jal        load_and_set_texture
/* B4554 800B3954 02002025 */   or        $a0, $s0, $zero
/* B4558 800B3958 8E020000 */  lw         $v0, 0x0($s0)
/* B455C 800B395C 8FA30030 */  lw         $v1, 0x30($sp)
/* B4560 800B3960 244C0008 */  addiu      $t4, $v0, 0x8
/* B4564 800B3964 AE0C0000 */  sw         $t4, 0x0($s0)
/* B4568 800B3968 8C780008 */  lw         $t8, 0x8($v1)
/* B456C 800B396C 84650004 */  lh         $a1, 0x4($v1)
/* B4570 800B3970 3C078000 */  lui        $a3, (0x80000000 >> 16)
/* B4574 800B3974 03077021 */  addu       $t6, $t8, $a3
/* B4578 800B3978 24B9FFFF */  addiu      $t9, $a1, -0x1
/* B457C 800B397C 001968C0 */  sll        $t5, $t9, 3
/* B4580 800B3980 31CF0006 */  andi       $t7, $t6, 0x6
/* B4584 800B3984 01AF6025 */  or         $t4, $t5, $t7
/* B4588 800B3988 319900FF */  andi       $t9, $t4, 0xFF
/* B458C 800B398C 000568C0 */  sll        $t5, $a1, 3
/* B4590 800B3990 0019C400 */  sll        $t8, $t9, 16
/* B4594 800B3994 01A57821 */  addu       $t7, $t5, $a1
/* B4598 800B3998 000F6040 */  sll        $t4, $t7, 1
/* B459C 800B399C 3C010400 */  lui        $at, (0x4000000 >> 16)
/* B45A0 800B39A0 03017025 */  or         $t6, $t8, $at
/* B45A4 800B39A4 25990008 */  addiu      $t9, $t4, 0x8
/* B45A8 800B39A8 3338FFFF */  andi       $t8, $t9, 0xFFFF
/* B45AC 800B39AC 01D86825 */  or         $t5, $t6, $t8
/* B45B0 800B39B0 AC4D0000 */  sw         $t5, 0x0($v0)
/* B45B4 800B39B4 8C6F0008 */  lw         $t7, 0x8($v1)
/* B45B8 800B39B8 3C010500 */  lui        $at, (0x5000000 >> 16)
/* B45BC 800B39BC 01E76021 */  addu       $t4, $t7, $a3
/* B45C0 800B39C0 AC4C0004 */  sw         $t4, 0x4($v0)
/* B45C4 800B39C4 8E020000 */  lw         $v0, 0x0($s0)
/* B45C8 800B39C8 02002025 */  or         $a0, $s0, $zero
/* B45CC 800B39CC 24590008 */  addiu      $t9, $v0, 0x8
/* B45D0 800B39D0 AE190000 */  sw         $t9, 0x0($s0)
/* B45D4 800B39D4 84660006 */  lh         $a2, 0x6($v1)
/* B45D8 800B39D8 00000000 */  nop
/* B45DC 800B39DC 24CEFFFF */  addiu      $t6, $a2, -0x1
/* B45E0 800B39E0 000EC100 */  sll        $t8, $t6, 4
/* B45E4 800B39E4 370D0001 */  ori        $t5, $t8, 0x1
/* B45E8 800B39E8 31AF00FF */  andi       $t7, $t5, 0xFF
/* B45EC 800B39EC 000F6400 */  sll        $t4, $t7, 16
/* B45F0 800B39F0 00067100 */  sll        $t6, $a2, 4
/* B45F4 800B39F4 31D8FFFF */  andi       $t8, $t6, 0xFFFF
/* B45F8 800B39F8 0181C825 */  or         $t9, $t4, $at
/* B45FC 800B39FC 03386825 */  or         $t5, $t9, $t8
/* B4600 800B3A00 AC4D0000 */  sw         $t5, 0x0($v0)
/* B4604 800B3A04 8C6F000C */  lw         $t7, 0xC($v1)
/* B4608 800B3A08 00000000 */  nop
/* B460C 800B3A0C 01E76021 */  addu       $t4, $t7, $a3
/* B4610 800B3A10 0C01A690 */  jal        func_80069A40
/* B4614 800B3A14 AC4C0004 */   sw        $t4, 0x4($v0)
/* B4618 800B3A18 8FAA0038 */  lw         $t2, 0x38($sp)
/* B461C 800B3A1C 240900FF */  addiu      $t1, $zero, 0xFF
.L800B3A20_B4620:
/* B4620 800B3A20 15490005 */  bne        $t2, $t1, .L800B3A38_B4638
/* B4624 800B3A24 3C18FA00 */   lui       $t8, (0xFA000000 >> 16)
/* B4628 800B3A28 862E004A */  lh         $t6, 0x4A($s1)
/* B462C 800B3A2C 00000000 */  nop
/* B4630 800B3A30 112E0007 */  beq        $t1, $t6, .L800B3A50_B4650
/* B4634 800B3A34 00000000 */   nop
.L800B3A38_B4638:
/* B4638 800B3A38 8E020000 */  lw         $v0, 0x0($s0)
/* B463C 800B3A3C 240DFFFF */  addiu      $t5, $zero, -0x1
/* B4640 800B3A40 24590008 */  addiu      $t9, $v0, 0x8
/* B4644 800B3A44 AE190000 */  sw         $t9, 0x0($s0)
/* B4648 800B3A48 AC4D0004 */  sw         $t5, 0x4($v0)
/* B464C 800B3A4C AC580000 */  sw         $t8, 0x0($v0)
.L800B3A50_B4650:
/* B4650 800B3A50 922F006F */  lbu        $t7, 0x6F($s1)
/* B4654 800B3A54 3C0EFB00 */  lui        $t6, (0xFB000000 >> 16)
/* B4658 800B3A58 11E000FE */  beqz       $t7, .L800B3E54_B4A54
/* B465C 800B3A5C 8FBF0024 */   lw        $ra, 0x24($sp)
/* B4660 800B3A60 8E020000 */  lw         $v0, 0x0($s0)
/* B4664 800B3A64 2419FF00 */  addiu      $t9, $zero, -0x100
/* B4668 800B3A68 244C0008 */  addiu      $t4, $v0, 0x8
/* B466C 800B3A6C AE0C0000 */  sw         $t4, 0x0($s0)
/* B4670 800B3A70 AC590004 */  sw         $t9, 0x4($v0)
/* B4674 800B3A74 100000F6 */  b          .L800B3E50_B4A50
/* B4678 800B3A78 AC4E0000 */   sw        $t6, 0x0($v0)
.L800B3A7C_B467C:
/* B467C 800B3A7C 8E020000 */  lw         $v0, 0x0($s0)
/* B4680 800B3A80 3C0DFB00 */  lui        $t5, (0xFB000000 >> 16)
/* B4684 800B3A84 24580008 */  addiu      $t8, $v0, 0x8
/* B4688 800B3A88 AE180000 */  sw         $t8, 0x0($s0)
/* B468C 800B3A8C 240FFF00 */  addiu      $t7, $zero, -0x100
/* B4690 800B3A90 AC4F0004 */  sw         $t7, 0x4($v0)
/* B4694 800B3A94 AC4D0000 */  sw         $t5, 0x0($v0)
/* B4698 800B3A98 8623002C */  lh         $v1, 0x2C($s1)
/* B469C 800B3A9C 24010003 */  addiu      $at, $zero, 0x3
/* B46A0 800B3AA0 14A30063 */  bne        $a1, $v1, .L800B3C30_B4830
/* B46A4 800B3AA4 00000000 */   nop
/* B46A8 800B3AA8 862C003A */  lh         $t4, 0x3A($s1)
/* B46AC 800B3AAC 00000000 */  nop
/* B46B0 800B3AB0 198000E8 */  blez       $t4, .L800B3E54_B4A54
/* B46B4 800B3AB4 8FBF0024 */   lw        $ra, 0x24($sp)
/* B46B8 800B3AB8 8E020000 */  lw         $v0, 0x0($s0)
/* B46BC 800B3ABC 3C19FA00 */  lui        $t9, (0xFA000000 >> 16)
/* B46C0 800B3AC0 244E0008 */  addiu      $t6, $v0, 0x8
/* B46C4 800B3AC4 AE0E0000 */  sw         $t6, 0x0($s0)
/* B46C8 800B3AC8 AC590000 */  sw         $t9, 0x0($v0)
/* B46CC 800B3ACC 8623004A */  lh         $v1, 0x4A($s1)
/* B46D0 800B3AD0 00000000 */  nop
/* B46D4 800B3AD4 307800FF */  andi       $t8, $v1, 0xFF
/* B46D8 800B3AD8 00186E00 */  sll        $t5, $t8, 24
/* B46DC 800B3ADC 00187C00 */  sll        $t7, $t8, 16
/* B46E0 800B3AE0 01AF6025 */  or         $t4, $t5, $t7
/* B46E4 800B3AE4 00187200 */  sll        $t6, $t8, 8
/* B46E8 800B3AE8 018EC825 */  or         $t9, $t4, $t6
/* B46EC 800B3AEC 373800FF */  ori        $t8, $t9, 0xFF
/* B46F0 800B3AF0 AC580004 */  sw         $t8, 0x4($v0)
/* B46F4 800B3AF4 822D0077 */  lb         $t5, 0x77($s1)
/* B46F8 800B3AF8 00000000 */  nop
/* B46FC 800B3AFC 15A00003 */  bnez       $t5, .L800B3B0C_B470C
/* B4700 800B3B00 00000000 */   nop
/* B4704 800B3B04 0C02CF99 */  jal        func_800B3E64
/* B4708 800B3B08 02202025 */   or        $a0, $s1, $zero
.L800B3B0C_B470C:
/* B470C 800B3B0C 92220075 */  lbu        $v0, 0x75($s1)
/* B4710 800B3B10 8E230044 */  lw         $v1, 0x44($s1)
/* B4714 800B3B14 000278C0 */  sll        $t7, $v0, 3
/* B4718 800B3B18 000F7080 */  sll        $t6, $t7, 2
/* B471C 800B3B1C 8C6C0008 */  lw         $t4, 0x8($v1)
/* B4720 800B3B20 01CF7021 */  addu       $t6, $t6, $t7
/* B4724 800B3B24 000E7040 */  sll        $t6, $t6, 1
/* B4728 800B3B28 018EC821 */  addu       $t9, $t4, $t6
/* B472C 800B3B2C AFB9002C */  sw         $t9, 0x2C($sp)
/* B4730 800B3B30 86270018 */  lh         $a3, 0x18($s1)
/* B4734 800B3B34 3C060800 */  lui        $a2, (0x800010B >> 16)
/* B4738 800B3B38 8C650000 */  lw         $a1, 0x0($v1)
/* B473C 800B3B3C 0007C200 */  sll        $t8, $a3, 8
/* B4740 800B3B40 03003825 */  or         $a3, $t8, $zero
/* B4744 800B3B44 34C6010B */  ori        $a2, $a2, (0x800010B & 0xFFFF)
/* B4748 800B3B48 02002025 */  or         $a0, $s0, $zero
/* B474C 800B3B4C 0C01ED3A */  jal        load_and_set_texture
/* B4750 800B3B50 AFA30030 */   sw        $v1, 0x30($sp)
/* B4754 800B3B54 8E020000 */  lw         $v0, 0x0($s0)
/* B4758 800B3B58 8FA30030 */  lw         $v1, 0x30($sp)
/* B475C 800B3B5C 244D0008 */  addiu      $t5, $v0, 0x8
/* B4760 800B3B60 AE0D0000 */  sw         $t5, 0x0($s0)
/* B4764 800B3B64 8FAF002C */  lw         $t7, 0x2C($sp)
/* B4768 800B3B68 84650004 */  lh         $a1, 0x4($v1)
/* B476C 800B3B6C 3C078000 */  lui        $a3, (0x80000000 >> 16)
/* B4770 800B3B70 01E74021 */  addu       $t0, $t7, $a3
/* B4774 800B3B74 24ACFFFF */  addiu      $t4, $a1, -0x1
/* B4778 800B3B78 000C70C0 */  sll        $t6, $t4, 3
/* B477C 800B3B7C 31190006 */  andi       $t9, $t0, 0x6
/* B4780 800B3B80 01D9C025 */  or         $t8, $t6, $t9
/* B4784 800B3B84 330D00FF */  andi       $t5, $t8, 0xFF
/* B4788 800B3B88 000570C0 */  sll        $t6, $a1, 3
/* B478C 800B3B8C 000D7C00 */  sll        $t7, $t5, 16
/* B4790 800B3B90 01C5C821 */  addu       $t9, $t6, $a1
/* B4794 800B3B94 0019C040 */  sll        $t8, $t9, 1
/* B4798 800B3B98 3C010400 */  lui        $at, (0x4000000 >> 16)
/* B479C 800B3B9C 01E16025 */  or         $t4, $t7, $at
/* B47A0 800B3BA0 270D0008 */  addiu      $t5, $t8, 0x8
/* B47A4 800B3BA4 31AFFFFF */  andi       $t7, $t5, 0xFFFF
/* B47A8 800B3BA8 018F7025 */  or         $t6, $t4, $t7
/* B47AC 800B3BAC AC4E0000 */  sw         $t6, 0x0($v0)
/* B47B0 800B3BB0 AC480004 */  sw         $t0, 0x4($v0)
/* B47B4 800B3BB4 8E020000 */  lw         $v0, 0x0($s0)
/* B47B8 800B3BB8 3C010500 */  lui        $at, (0x5000000 >> 16)
/* B47BC 800B3BBC 24590008 */  addiu      $t9, $v0, 0x8
/* B47C0 800B3BC0 AE190000 */  sw         $t9, 0x0($s0)
/* B47C4 800B3BC4 84660006 */  lh         $a2, 0x6($v1)
/* B47C8 800B3BC8 00000000 */  nop
/* B47CC 800B3BCC 24D8FFFF */  addiu      $t8, $a2, -0x1
/* B47D0 800B3BD0 00186900 */  sll        $t5, $t8, 4
/* B47D4 800B3BD4 35AC0001 */  ori        $t4, $t5, 0x1
/* B47D8 800B3BD8 318F00FF */  andi       $t7, $t4, 0xFF
/* B47DC 800B3BDC 000F7400 */  sll        $t6, $t7, 16
/* B47E0 800B3BE0 0006C100 */  sll        $t8, $a2, 4
/* B47E4 800B3BE4 330DFFFF */  andi       $t5, $t8, 0xFFFF
/* B47E8 800B3BE8 01C1C825 */  or         $t9, $t6, $at
/* B47EC 800B3BEC 032D6025 */  or         $t4, $t9, $t5
/* B47F0 800B3BF0 AC4C0000 */  sw         $t4, 0x0($v0)
/* B47F4 800B3BF4 8C6F000C */  lw         $t7, 0xC($v1)
/* B47F8 800B3BF8 240100FF */  addiu      $at, $zero, 0xFF
/* B47FC 800B3BFC 01E77021 */  addu       $t6, $t7, $a3
/* B4800 800B3C00 AC4E0004 */  sw         $t6, 0x4($v0)
/* B4804 800B3C04 8638004A */  lh         $t8, 0x4A($s1)
/* B4808 800B3C08 3C0DFA00 */  lui        $t5, (0xFA000000 >> 16)
/* B480C 800B3C0C 13010091 */  beq        $t8, $at, .L800B3E54_B4A54
/* B4810 800B3C10 8FBF0024 */   lw        $ra, 0x24($sp)
/* B4814 800B3C14 8E020000 */  lw         $v0, 0x0($s0)
/* B4818 800B3C18 240CFFFF */  addiu      $t4, $zero, -0x1
/* B481C 800B3C1C 24590008 */  addiu      $t9, $v0, 0x8
/* B4820 800B3C20 AE190000 */  sw         $t9, 0x0($s0)
/* B4824 800B3C24 AC4C0004 */  sw         $t4, 0x4($v0)
/* B4828 800B3C28 10000089 */  b          .L800B3E50_B4A50
/* B482C 800B3C2C AC4D0000 */   sw        $t5, 0x0($v0)
.L800B3C30_B4830:
/* B4830 800B3C30 14610088 */  bne        $v1, $at, .L800B3E54_B4A54
/* B4834 800B3C34 8FBF0024 */   lw        $ra, 0x24($sp)
/* B4838 800B3C38 8E020000 */  lw         $v0, 0x0($s0)
/* B483C 800B3C3C 3C0EFA00 */  lui        $t6, (0xFA000000 >> 16)
/* B4840 800B3C40 244F0008 */  addiu      $t7, $v0, 0x8
/* B4844 800B3C44 AE0F0000 */  sw         $t7, 0x0($s0)
/* B4848 800B3C48 AC4E0000 */  sw         $t6, 0x0($v0)
/* B484C 800B3C4C 8623004A */  lh         $v1, 0x4A($s1)
/* B4850 800B3C50 3C060800 */  lui        $a2, (0x800010B >> 16)
/* B4854 800B3C54 307800FF */  andi       $t8, $v1, 0xFF
/* B4858 800B3C58 0018CE00 */  sll        $t9, $t8, 24
/* B485C 800B3C5C 00186C00 */  sll        $t5, $t8, 16
/* B4860 800B3C60 00187A00 */  sll        $t7, $t8, 8
/* B4864 800B3C64 032D6025 */  or         $t4, $t9, $t5
/* B4868 800B3C68 018F7025 */  or         $t6, $t4, $t7
/* B486C 800B3C6C 315800FF */  andi       $t8, $t2, 0xFF
/* B4870 800B3C70 01D8C825 */  or         $t9, $t6, $t8
/* B4874 800B3C74 AC590004 */  sw         $t9, 0x4($v0)
/* B4878 800B3C78 92250068 */  lbu        $a1, 0x68($s1)
/* B487C 800B3C7C 34C6010B */  ori        $a2, $a2, (0x800010B & 0xFFFF)
/* B4880 800B3C80 28A10002 */  slti       $at, $a1, 0x2
/* B4884 800B3C84 1420003A */  bnez       $at, .L800B3D70_B4970
/* B4888 800B3C88 02002025 */   or        $a0, $s0, $zero
/* B488C 800B3C8C 8E230044 */  lw         $v1, 0x44($s1)
/* B4890 800B3C90 86270018 */  lh         $a3, 0x18($s1)
/* B4894 800B3C94 8C650000 */  lw         $a1, 0x0($v1)
/* B4898 800B3C98 00076A00 */  sll        $t5, $a3, 8
/* B489C 800B3C9C 01A03825 */  or         $a3, $t5, $zero
/* B48A0 800B3CA0 AFAA0038 */  sw         $t2, 0x38($sp)
/* B48A4 800B3CA4 0C01ED3A */  jal        load_and_set_texture
/* B48A8 800B3CA8 AFA30030 */   sw        $v1, 0x30($sp)
/* B48AC 800B3CAC 8E020000 */  lw         $v0, 0x0($s0)
/* B48B0 800B3CB0 8FA30030 */  lw         $v1, 0x30($sp)
/* B48B4 800B3CB4 8FAA0038 */  lw         $t2, 0x38($sp)
/* B48B8 800B3CB8 244C0008 */  addiu      $t4, $v0, 0x8
/* B48BC 800B3CBC AE0C0000 */  sw         $t4, 0x0($s0)
/* B48C0 800B3CC0 8C780008 */  lw         $t8, 0x8($v1)
/* B48C4 800B3CC4 84650004 */  lh         $a1, 0x4($v1)
/* B48C8 800B3CC8 3C078000 */  lui        $a3, (0x80000000 >> 16)
/* B48CC 800B3CCC 0307C821 */  addu       $t9, $t8, $a3
/* B48D0 800B3CD0 24AFFFFF */  addiu      $t7, $a1, -0x1
/* B48D4 800B3CD4 000F70C0 */  sll        $t6, $t7, 3
/* B48D8 800B3CD8 332D0006 */  andi       $t5, $t9, 0x6
/* B48DC 800B3CDC 01CD6025 */  or         $t4, $t6, $t5
/* B48E0 800B3CE0 318F00FF */  andi       $t7, $t4, 0xFF
/* B48E4 800B3CE4 000570C0 */  sll        $t6, $a1, 3
/* B48E8 800B3CE8 000FC400 */  sll        $t8, $t7, 16
/* B48EC 800B3CEC 01C56821 */  addu       $t5, $t6, $a1
/* B48F0 800B3CF0 000D6040 */  sll        $t4, $t5, 1
/* B48F4 800B3CF4 3C010400 */  lui        $at, (0x4000000 >> 16)
/* B48F8 800B3CF8 0301C825 */  or         $t9, $t8, $at
/* B48FC 800B3CFC 258F0008 */  addiu      $t7, $t4, 0x8
/* B4900 800B3D00 31F8FFFF */  andi       $t8, $t7, 0xFFFF
/* B4904 800B3D04 03387025 */  or         $t6, $t9, $t8
/* B4908 800B3D08 AC4E0000 */  sw         $t6, 0x0($v0)
/* B490C 800B3D0C 8C6D0008 */  lw         $t5, 0x8($v1)
/* B4910 800B3D10 3C010500 */  lui        $at, (0x5000000 >> 16)
/* B4914 800B3D14 01A76021 */  addu       $t4, $t5, $a3
/* B4918 800B3D18 AC4C0004 */  sw         $t4, 0x4($v0)
/* B491C 800B3D1C 8E020000 */  lw         $v0, 0x0($s0)
/* B4920 800B3D20 00000000 */  nop
/* B4924 800B3D24 244F0008 */  addiu      $t7, $v0, 0x8
/* B4928 800B3D28 AE0F0000 */  sw         $t7, 0x0($s0)
/* B492C 800B3D2C 84660006 */  lh         $a2, 0x6($v1)
/* B4930 800B3D30 00000000 */  nop
/* B4934 800B3D34 24D9FFFF */  addiu      $t9, $a2, -0x1
/* B4938 800B3D38 0019C100 */  sll        $t8, $t9, 4
/* B493C 800B3D3C 370E0001 */  ori        $t6, $t8, 0x1
/* B4940 800B3D40 31CD00FF */  andi       $t5, $t6, 0xFF
/* B4944 800B3D44 000D6400 */  sll        $t4, $t5, 16
/* B4948 800B3D48 0006C900 */  sll        $t9, $a2, 4
/* B494C 800B3D4C 3338FFFF */  andi       $t8, $t9, 0xFFFF
/* B4950 800B3D50 01817825 */  or         $t7, $t4, $at
/* B4954 800B3D54 01F87025 */  or         $t6, $t7, $t8
/* B4958 800B3D58 AC4E0000 */  sw         $t6, 0x0($v0)
/* B495C 800B3D5C 8C6D000C */  lw         $t5, 0xC($v1)
/* B4960 800B3D60 00000000 */  nop
/* B4964 800B3D64 01A76021 */  addu       $t4, $t5, $a3
/* B4968 800B3D68 1000002C */  b          .L800B3E1C_B4A1C
/* B496C 800B3D6C AC4C0004 */   sw        $t4, 0x4($v0)
.L800B3D70_B4970:
/* B4970 800B3D70 18A0002A */  blez       $a1, .L800B3E1C_B4A1C
/* B4974 800B3D74 02002025 */   or        $a0, $s0, $zero
/* B4978 800B3D78 8E230044 */  lw         $v1, 0x44($s1)
/* B497C 800B3D7C 86270018 */  lh         $a3, 0x18($s1)
/* B4980 800B3D80 8C650000 */  lw         $a1, 0x0($v1)
/* B4984 800B3D84 3C060800 */  lui        $a2, (0x800010B >> 16)
/* B4988 800B3D88 0007CA00 */  sll        $t9, $a3, 8
/* B498C 800B3D8C 03203825 */  or         $a3, $t9, $zero
/* B4990 800B3D90 34C6010B */  ori        $a2, $a2, (0x800010B & 0xFFFF)
/* B4994 800B3D94 AFAA0038 */  sw         $t2, 0x38($sp)
/* B4998 800B3D98 0C01ED3A */  jal        load_and_set_texture
/* B499C 800B3D9C AFA30030 */   sw        $v1, 0x30($sp)
/* B49A0 800B3DA0 8E020000 */  lw         $v0, 0x0($s0)
/* B49A4 800B3DA4 8FA30030 */  lw         $v1, 0x30($sp)
/* B49A8 800B3DA8 8FAA0038 */  lw         $t2, 0x38($sp)
/* B49AC 800B3DAC 244F0008 */  addiu      $t7, $v0, 0x8
/* B49B0 800B3DB0 AE0F0000 */  sw         $t7, 0x0($s0)
/* B49B4 800B3DB4 8C780008 */  lw         $t8, 0x8($v1)
/* B49B8 800B3DB8 3C078000 */  lui        $a3, (0x80000000 >> 16)
/* B49BC 800B3DBC 03077021 */  addu       $t6, $t8, $a3
/* B49C0 800B3DC0 31CD0006 */  andi       $t5, $t6, 0x6
/* B49C4 800B3DC4 35AC0018 */  ori        $t4, $t5, 0x18
/* B49C8 800B3DC8 319900FF */  andi       $t9, $t4, 0xFF
/* B49CC 800B3DCC 00197C00 */  sll        $t7, $t9, 16
/* B49D0 800B3DD0 3C010400 */  lui        $at, (0x4000050 >> 16)
/* B49D4 800B3DD4 01E1C025 */  or         $t8, $t7, $at
/* B49D8 800B3DD8 370E0050 */  ori        $t6, $t8, (0x4000050 & 0xFFFF)
/* B49DC 800B3DDC AC4E0000 */  sw         $t6, 0x0($v0)
/* B49E0 800B3DE0 8C6D0008 */  lw         $t5, 0x8($v1)
/* B49E4 800B3DE4 3C0F0501 */  lui        $t7, (0x5010010 >> 16)
/* B49E8 800B3DE8 01A76021 */  addu       $t4, $t5, $a3
/* B49EC 800B3DEC AC4C0004 */  sw         $t4, 0x4($v0)
/* B49F0 800B3DF0 8E020000 */  lw         $v0, 0x0($s0)
/* B49F4 800B3DF4 35EF0010 */  ori        $t7, $t7, (0x5010010 & 0xFFFF)
/* B49F8 800B3DF8 24590008 */  addiu      $t9, $v0, 0x8
/* B49FC 800B3DFC AE190000 */  sw         $t9, 0x0($s0)
/* B4A00 800B3E00 AC4F0000 */  sw         $t7, 0x0($v0)
/* B4A04 800B3E04 846E0006 */  lh         $t6, 0x6($v1)
/* B4A08 800B3E08 8C78000C */  lw         $t8, 0xC($v1)
/* B4A0C 800B3E0C 000E6900 */  sll        $t5, $t6, 4
/* B4A10 800B3E10 030D6021 */  addu       $t4, $t8, $t5
/* B4A14 800B3E14 0187C821 */  addu       $t9, $t4, $a3
/* B4A18 800B3E18 AC590004 */  sw         $t9, 0x4($v0)
.L800B3E1C_B4A1C:
/* B4A1C 800B3E1C 240100FF */  addiu      $at, $zero, 0xFF
/* B4A20 800B3E20 15410005 */  bne        $t2, $at, .L800B3E38_B4A38
/* B4A24 800B3E24 3C18FA00 */   lui       $t8, (0xFA000000 >> 16)
/* B4A28 800B3E28 862F004A */  lh         $t7, 0x4A($s1)
/* B4A2C 800B3E2C 240100FF */  addiu      $at, $zero, 0xFF
/* B4A30 800B3E30 11E10008 */  beq        $t7, $at, .L800B3E54_B4A54
/* B4A34 800B3E34 8FBF0024 */   lw        $ra, 0x24($sp)
.L800B3E38_B4A38:
/* B4A38 800B3E38 8E020000 */  lw         $v0, 0x0($s0)
/* B4A3C 800B3E3C 240DFFFF */  addiu      $t5, $zero, -0x1
/* B4A40 800B3E40 244E0008 */  addiu      $t6, $v0, 0x8
/* B4A44 800B3E44 AE0E0000 */  sw         $t6, 0x0($s0)
/* B4A48 800B3E48 AC4D0004 */  sw         $t5, 0x4($v0)
/* B4A4C 800B3E4C AC580000 */  sw         $t8, 0x0($v0)
.L800B3E50_B4A50:
/* B4A50 800B3E50 8FBF0024 */  lw         $ra, 0x24($sp)
.L800B3E54_B4A54:
/* B4A54 800B3E54 8FB0001C */  lw         $s0, 0x1C($sp)
/* B4A58 800B3E58 8FB10020 */  lw         $s1, 0x20($sp)
/* B4A5C 800B3E5C 03E00008 */  jr         $ra
/* B4A60 800B3E60 27BD0040 */   addiu     $sp, $sp, 0x40
