glabel func_800B7EB4
/* 0B8AB4 800B7EB4 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0B8AB8 800B7EB8 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0B8ABC 800B7EBC AFB20020 */  sw    $s2, 0x20($sp)
/* 0B8AC0 800B7EC0 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0B8AC4 800B7EC4 0C02DF48 */  jal   free_waves
/* 0B8AC8 800B7EC8 AFB00018 */   sw    $s0, 0x18($sp)
/* 0B8ACC 800B7ECC 3C128013 */  lui   $s2, %hi(D_80129FC8) # $s2, 0x8013
/* 0B8AD0 800B7ED0 26529FC8 */  addiu $s2, %lo(D_80129FC8) # addiu $s2, $s2, -0x6038
/* 0B8AD4 800B7ED4 8E440020 */  lw    $a0, 0x20($s2)
/* 0B8AD8 800B7ED8 3C1100FF */  lui   $s1, (0x00FFFFFF >> 16) # lui $s1, 0xff
/* 0B8ADC 800B7EDC 3631FFFF */  ori   $s1, (0x00FFFFFF & 0xFFFF) # ori $s1, $s1, 0xffff
/* 0B8AE0 800B7EE0 00047080 */  sll   $t6, $a0, 2
/* 0B8AE4 800B7EE4 01C02025 */  move  $a0, $t6
/* 0B8AE8 800B7EE8 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0B8AEC 800B7EEC 02202825 */   move  $a1, $s1
/* 0B8AF0 800B7EF0 3C01800E */  lui   $at, %hi(D_800E3040) # $at, 0x800e
/* 0B8AF4 800B7EF4 AC223040 */  sw    $v0, %lo(D_800E3040)($at)
/* 0B8AF8 800B7EF8 8E430004 */  lw    $v1, 4($s2)
/* 0B8AFC 800B7EFC 02202825 */  move  $a1, $s1
/* 0B8B00 800B7F00 00037880 */  sll   $t7, $v1, 2
/* 0B8B04 800B7F04 01E30019 */  multu $t7, $v1
/* 0B8B08 800B7F08 00002012 */  mflo  $a0
/* 0B8B0C 800B7F0C 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0B8B10 800B7F10 00000000 */   nop   
/* 0B8B14 800B7F14 3C01800E */  lui   $at, %hi(D_800E3044) # $at, 0x800e
/* 0B8B18 800B7F18 AC223044 */  sw    $v0, %lo(D_800E3044)($at)
/* 0B8B1C 800B7F1C 8E430000 */  lw    $v1, ($s2)
/* 0B8B20 800B7F20 02202825 */  move  $a1, $s1
/* 0B8B24 800B7F24 24630001 */  addiu $v1, $v1, 1
/* 0B8B28 800B7F28 0003C080 */  sll   $t8, $v1, 2
/* 0B8B2C 800B7F2C 03030019 */  multu $t8, $v1
/* 0B8B30 800B7F30 00002012 */  mflo  $a0
/* 0B8B34 800B7F34 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0B8B38 800B7F38 00000000 */   nop   
/* 0B8B3C 800B7F3C 3C01800E */  lui   $at, %hi(D_800E3048) # $at, 0x800e
/* 0B8B40 800B7F40 AC223048 */  sw    $v0, %lo(D_800E3048)($at)
/* 0B8B44 800B7F44 8E430000 */  lw    $v1, ($s2)
/* 0B8B48 800B7F48 241F0009 */  li    $ra, 9
/* 0B8B4C 800B7F4C 24630001 */  addiu $v1, $v1, 1
/* 0B8B50 800B7F50 0003C880 */  sll   $t9, $v1, 2
/* 0B8B54 800B7F54 03230019 */  multu $t9, $v1
/* 0B8B58 800B7F58 02202825 */  move  $a1, $s1
/* 0B8B5C 800B7F5C 00008012 */  mflo  $s0
/* 0B8B60 800B7F60 00000000 */  nop   
/* 0B8B64 800B7F64 00000000 */  nop   
/* 0B8B68 800B7F68 021F0019 */  multu $s0, $ra
/* 0B8B6C 800B7F6C 00002012 */  mflo  $a0
/* 0B8B70 800B7F70 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0B8B74 800B7F74 00000000 */   nop   
/* 0B8B78 800B7F78 3C04800E */  lui   $a0, %hi(D_800E304C) # $a0, 0x800e
/* 0B8B7C 800B7F7C 2484304C */  addiu $a0, %lo(D_800E304C) # addiu $a0, $a0, 0x304c
/* 0B8B80 800B7F80 3C03800E */  lui   $v1, %hi(D_800E304C) # $v1, 0x800e
/* 0B8B84 800B7F84 00104080 */  sll   $t0, $s0, 2
/* 0B8B88 800B7F88 AC820000 */  sw    $v0, ($a0)
/* 0B8B8C 800B7F8C 241F0009 */  li    $ra, 9
/* 0B8B90 800B7F90 01104023 */  subu  $t0, $t0, $s0
/* 0B8B94 800B7F94 24633050 */  addiu $v1, %lo(D_800E304C + 4) # addiu $v1, $v1, 0x3050
/* 0B8B98 800B7F98 24050001 */  li    $a1, 1
/* 0B8B9C 800B7F9C 02003025 */  move  $a2, $s0
/* 0B8BA0 800B7FA0 00105080 */  sll   $t2, $s0, 2
/* 0B8BA4 800B7FA4 00103840 */  sll   $a3, $s0, 1
/* 0B8BA8 800B7FA8 00105880 */  sll   $t3, $s0, 2
/* 0B8BAC 800B7FAC 00106080 */  sll   $t4, $s0, 2
/* 0B8BB0 800B7FB0 00104880 */  sll   $t1, $s0, 2
/* 0B8BB4 800B7FB4 00106880 */  sll   $t5, $s0, 2
.L800B7FB8:
/* 0B8BB8 800B7FB8 8C8E0000 */  lw    $t6, ($a0)
/* 0B8BBC 800B7FBC 24A50004 */  addiu $a1, $a1, 4
/* 0B8BC0 800B7FC0 01C67821 */  addu  $t7, $t6, $a2
/* 0B8BC4 800B7FC4 AC6F0000 */  sw    $t7, ($v1)
/* 0B8BC8 800B7FC8 8C980000 */  lw    $t8, ($a0)
/* 0B8BCC 800B7FCC 00CA3021 */  addu  $a2, $a2, $t2
/* 0B8BD0 800B7FD0 0307C821 */  addu  $t9, $t8, $a3
/* 0B8BD4 800B7FD4 AC790004 */  sw    $t9, 4($v1)
/* 0B8BD8 800B7FD8 8C8E0000 */  lw    $t6, ($a0)
/* 0B8BDC 800B7FDC 00EB3821 */  addu  $a3, $a3, $t3
/* 0B8BE0 800B7FE0 01C87821 */  addu  $t7, $t6, $t0
/* 0B8BE4 800B7FE4 AC6F0008 */  sw    $t7, 8($v1)
/* 0B8BE8 800B7FE8 8C980000 */  lw    $t8, ($a0)
/* 0B8BEC 800B7FEC 010C4021 */  addu  $t0, $t0, $t4
/* 0B8BF0 800B7FF0 0309C821 */  addu  $t9, $t8, $t1
/* 0B8BF4 800B7FF4 AC79000C */  sw    $t9, 0xc($v1)
/* 0B8BF8 800B7FF8 012D4821 */  addu  $t1, $t1, $t5
/* 0B8BFC 800B7FFC 14BFFFEE */  bne   $a1, $ra, .L800B7FB8
/* 0B8C00 800B8000 24630010 */   addiu $v1, $v1, 0x10
/* 0B8C04 800B8004 8E430000 */  lw    $v1, ($s2)
/* 0B8C08 800B8008 3C0F8013 */  lui   $t7, %hi(D_8012A078) # $t7, 0x8013
/* 0B8C0C 800B800C 24630001 */  addiu $v1, $v1, 1
/* 0B8C10 800B8010 00037140 */  sll   $t6, $v1, 5
/* 0B8C14 800B8014 01C37023 */  subu  $t6, $t6, $v1
/* 0B8C18 800B8018 000E7080 */  sll   $t6, $t6, 2
/* 0B8C1C 800B801C 01C37021 */  addu  $t6, $t6, $v1
/* 0B8C20 800B8020 000E7040 */  sll   $t6, $t6, 1
/* 0B8C24 800B8024 01C30019 */  multu $t6, $v1
/* 0B8C28 800B8028 8DEFA078 */  lw    $t7, %lo(D_8012A078)($t7)
/* 0B8C2C 800B802C 24010002 */  li    $at, 2
/* 0B8C30 800B8030 00008012 */  mflo  $s0
/* 0B8C34 800B8034 00102040 */  sll   $a0, $s0, 1
/* 0B8C38 800B8038 11E10009 */  beq   $t7, $at, .L800B8060
/* 0B8C3C 800B803C 00000000 */   nop   
/* 0B8C40 800B8040 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0B8C44 800B8044 02202825 */   move  $a1, $s1
/* 0B8C48 800B8048 3C03800E */  lui   $v1, %hi(D_800E3070) # $v1, 0x800e
/* 0B8C4C 800B804C 24633070 */  addiu $v1, %lo(D_800E3070) # addiu $v1, $v1, 0x3070
/* 0B8C50 800B8050 0050C821 */  addu  $t9, $v0, $s0
/* 0B8C54 800B8054 AC620000 */  sw    $v0, ($v1)
/* 0B8C58 800B8058 1000000D */  b     .L800B8090
/* 0B8C5C 800B805C AC790004 */   sw    $t9, 4($v1)
.L800B8060:
/* 0B8C60 800B8060 00102080 */  sll   $a0, $s0, 2
/* 0B8C64 800B8064 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0B8C68 800B8068 02202825 */   move  $a1, $s1
/* 0B8C6C 800B806C 3C03800E */  lui   $v1, %hi(D_800E3070) # $v1, 0x800e
/* 0B8C70 800B8070 24633070 */  addiu $v1, %lo(D_800E3070) # addiu $v1, $v1, 0x3070
/* 0B8C74 800B8074 00507821 */  addu  $t7, $v0, $s0
/* 0B8C78 800B8078 AC6F0004 */  sw    $t7, 4($v1)
/* 0B8C7C 800B807C 01F0C821 */  addu  $t9, $t7, $s0
/* 0B8C80 800B8080 03307821 */  addu  $t7, $t9, $s0
/* 0B8C84 800B8084 AC620000 */  sw    $v0, ($v1)
/* 0B8C88 800B8088 AC790008 */  sw    $t9, 8($v1)
/* 0B8C8C 800B808C AC6F000C */  sw    $t7, 0xc($v1)
.L800B8090:
/* 0B8C90 800B8090 8E420000 */  lw    $v0, ($s2)
/* 0B8C94 800B8094 3C198013 */  lui   $t9, %hi(D_8012A078) # $t9, 0x8013
/* 0B8C98 800B8098 0002C140 */  sll   $t8, $v0, 5
/* 0B8C9C 800B809C 03020019 */  multu $t8, $v0
/* 0B8CA0 800B80A0 8F39A078 */  lw    $t9, %lo(D_8012A078)($t9)
/* 0B8CA4 800B80A4 24010002 */  li    $at, 2
/* 0B8CA8 800B80A8 00008012 */  mflo  $s0
/* 0B8CAC 800B80AC 00102040 */  sll   $a0, $s0, 1
/* 0B8CB0 800B80B0 13210009 */  beq   $t9, $at, .L800B80D8
/* 0B8CB4 800B80B4 00000000 */   nop   
/* 0B8CB8 800B80B8 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0B8CBC 800B80BC 02202825 */   move  $a1, $s1
/* 0B8CC0 800B80C0 3C03800E */  lui   $v1, %hi(D_800E3080) # $v1, 0x800e
/* 0B8CC4 800B80C4 24633080 */  addiu $v1, %lo(D_800E3080) # addiu $v1, $v1, 0x3080
/* 0B8CC8 800B80C8 00507821 */  addu  $t7, $v0, $s0
/* 0B8CCC 800B80CC AC620000 */  sw    $v0, ($v1)
/* 0B8CD0 800B80D0 1000000D */  b     .L800B8108
/* 0B8CD4 800B80D4 AC6F0004 */   sw    $t7, 4($v1)
.L800B80D8:
/* 0B8CD8 800B80D8 00102080 */  sll   $a0, $s0, 2
/* 0B8CDC 800B80DC 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0B8CE0 800B80E0 02202825 */   move  $a1, $s1
/* 0B8CE4 800B80E4 3C03800E */  lui   $v1, %hi(D_800E3080) # $v1, 0x800e
/* 0B8CE8 800B80E8 24633080 */  addiu $v1, %lo(D_800E3080) # addiu $v1, $v1, 0x3080
/* 0B8CEC 800B80EC 0050C821 */  addu  $t9, $v0, $s0
/* 0B8CF0 800B80F0 AC790004 */  sw    $t9, 4($v1)
/* 0B8CF4 800B80F4 03307821 */  addu  $t7, $t9, $s0
/* 0B8CF8 800B80F8 01F0C821 */  addu  $t9, $t7, $s0
/* 0B8CFC 800B80FC AC620000 */  sw    $v0, ($v1)
/* 0B8D00 800B8100 AC6F0008 */  sw    $t7, 8($v1)
/* 0B8D04 800B8104 AC79000C */  sw    $t9, 0xc($v1)
.L800B8108:
/* 0B8D08 800B8108 8E44002C */  lw    $a0, 0x2c($s2)
/* 0B8D0C 800B810C 0C01EB9D */  jal   load_texture
/* 0B8D10 800B8110 00000000 */   nop   
/* 0B8D14 800B8114 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0B8D18 800B8118 3C01800E */  lui   $at, %hi(D_800E30D0) # $at, 0x800e
/* 0B8D1C 800B811C 8FB00018 */  lw    $s0, 0x18($sp)
/* 0B8D20 800B8120 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0B8D24 800B8124 8FB20020 */  lw    $s2, 0x20($sp)
/* 0B8D28 800B8128 AC2230D0 */  sw    $v0, %lo(D_800E30D0)($at)
/* 0B8D2C 800B812C 03E00008 */  jr    $ra
/* 0B8D30 800B8130 27BD0028 */   addiu $sp, $sp, 0x28

