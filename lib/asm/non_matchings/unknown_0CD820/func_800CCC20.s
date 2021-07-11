glabel func_800CCC20
/* 0CD820 800CCC20 27BDFF80 */  addiu $sp, $sp, -0x80
/* 0CD824 800CCC24 3C0E800E */  lui   $t6, %hi(D_800E38C0) # $t6, 0x800e
/* 0CD828 800CCC28 8DCE38C0 */  lw    $t6, %lo(D_800E38C0)($t6)
/* 0CD82C 800CCC2C AFBF0024 */  sw    $ra, 0x24($sp)
/* 0CD830 800CCC30 AFA40080 */  sw    $a0, 0x80($sp)
/* 0CD834 800CCC34 AFA50084 */  sw    $a1, 0x84($sp)
/* 0CD838 800CCC38 AFA60088 */  sw    $a2, 0x88($sp)
/* 0CD83C 800CCC3C 11C00003 */  beqz  $t6, .L800CCC4C
/* 0CD840 800CCC40 AFA00078 */   sw    $zero, 0x78($sp)
/* 0CD844 800CCC44 10000070 */  b     .L800CCE08
/* 0CD848 800CCC48 00001025 */   move  $v0, $zero
.L800CCC4C:
/* 0CD84C 800CCC4C 240F0001 */  li    $t7, 1
/* 0CD850 800CCC50 3C01800E */  lui   $at, %hi(D_800E38C0) # $at, 0x800e
/* 0CD854 800CCC54 0C03486C */  jal   osGetTime
/* 0CD858 800CCC58 AC2F38C0 */   sw    $t7, %lo(D_800E38C0)($at)
/* 0CD85C 800CCC5C 3C050007 */  lui   $a1, (0x0007A120 >> 16) # lui $a1, 7
/* 0CD860 800CCC60 3C06800E */  lui   $a2, %hi(D_800E38A0) # $a2, 0x800e
/* 0CD864 800CCC64 3C07800E */  lui   $a3, %hi(D_800E38A4) # $a3, 0x800e
/* 0CD868 800CCC68 AFA20070 */  sw    $v0, 0x70($sp)
/* 0CD86C 800CCC6C AFA30074 */  sw    $v1, 0x74($sp)
/* 0CD870 800CCC70 8CE738A4 */  lw    $a3, %lo(D_800E38A4)($a3)
/* 0CD874 800CCC74 8CC638A0 */  lw    $a2, %lo(D_800E38A0)($a2)
/* 0CD878 800CCC78 34A5A120 */  ori   $a1, (0x0007A120 & 0xFFFF) # ori $a1, $a1, 0xa120
/* 0CD87C 800CCC7C 0C033AF2 */  jal   __ll_mul
/* 0CD880 800CCC80 24040000 */   li    $a0, 0
/* 0CD884 800CCC84 AFA20030 */  sw    $v0, 0x30($sp)
/* 0CD888 800CCC88 AFA30034 */  sw    $v1, 0x34($sp)
/* 0CD88C 800CCC8C 3C07000F */  lui   $a3, (0x000F4240 >> 16) # lui $a3, 0xf
/* 0CD890 800CCC90 34E74240 */  ori   $a3, (0x000F4240 & 0xFFFF) # ori $a3, $a3, 0x4240
/* 0CD894 800CCC94 8FA50034 */  lw    $a1, 0x34($sp)
/* 0CD898 800CCC98 8FA40030 */  lw    $a0, 0x30($sp)
/* 0CD89C 800CCC9C 0C033AB2 */  jal   __ull_div
/* 0CD8A0 800CCCA0 24060000 */   li    $a2, 0
/* 0CD8A4 800CCCA4 8FB80070 */  lw    $t8, 0x70($sp)
/* 0CD8A8 800CCCA8 8FB90074 */  lw    $t9, 0x74($sp)
/* 0CD8AC 800CCCAC 0058082B */  sltu  $at, $v0, $t8
/* 0CD8B0 800CCCB0 14200031 */  bnez  $at, .L800CCD78
/* 0CD8B4 800CCCB4 0302082B */   sltu  $at, $t8, $v0
/* 0CD8B8 800CCCB8 14200003 */  bnez  $at, .L800CCCC8
/* 0CD8BC 800CCCBC 0323082B */   sltu  $at, $t9, $v1
/* 0CD8C0 800CCCC0 1020002D */  beqz  $at, .L800CCD78
/* 0CD8C4 800CCCC4 00000000 */   nop   
.L800CCCC8:
/* 0CD8C8 800CCCC8 27A40038 */  addiu $a0, $sp, 0x38
/* 0CD8CC 800CCCCC 27A5007C */  addiu $a1, $sp, 0x7c
/* 0CD8D0 800CCCD0 0C032208 */  jal   osCreateMesgQueue
/* 0CD8D4 800CCCD4 24060001 */   li    $a2, 1
/* 0CD8D8 800CCCD8 3C050007 */  lui   $a1, (0x0007A120 >> 16) # lui $a1, 7
/* 0CD8DC 800CCCDC 3C06800E */  lui   $a2, %hi(D_800E38A0) # $a2, 0x800e
/* 0CD8E0 800CCCE0 3C07800E */  lui   $a3, %hi(D_800E38A4) # $a3, 0x800e
/* 0CD8E4 800CCCE4 8CE738A4 */  lw    $a3, %lo(D_800E38A4)($a3)
/* 0CD8E8 800CCCE8 8CC638A0 */  lw    $a2, %lo(D_800E38A0)($a2)
/* 0CD8EC 800CCCEC 34A5A120 */  ori   $a1, (0x0007A120 & 0xFFFF) # ori $a1, $a1, 0xa120
/* 0CD8F0 800CCCF0 0C033AF2 */  jal   __ll_mul
/* 0CD8F4 800CCCF4 24040000 */   li    $a0, 0
/* 0CD8F8 800CCCF8 AFA20028 */  sw    $v0, 0x28($sp)
/* 0CD8FC 800CCCFC AFA3002C */  sw    $v1, 0x2c($sp)
/* 0CD900 800CCD00 3C07000F */  lui   $a3, (0x000F4240 >> 16) # lui $a3, 0xf
/* 0CD904 800CCD04 34E74240 */  ori   $a3, (0x000F4240 & 0xFFFF) # ori $a3, $a3, 0x4240
/* 0CD908 800CCD08 8FA5002C */  lw    $a1, 0x2c($sp)
/* 0CD90C 800CCD0C 8FA40028 */  lw    $a0, 0x28($sp)
/* 0CD910 800CCD10 0C033AB2 */  jal   __ull_div
/* 0CD914 800CCD14 24060000 */   li    $a2, 0
/* 0CD918 800CCD18 AFA20030 */  sw    $v0, 0x30($sp)
/* 0CD91C 800CCD1C AFA30034 */  sw    $v1, 0x34($sp)
/* 0CD920 800CCD20 8FA90034 */  lw    $t1, 0x34($sp)
/* 0CD924 800CCD24 8FA80030 */  lw    $t0, 0x30($sp)
/* 0CD928 800CCD28 8FAA0070 */  lw    $t2, 0x70($sp)
/* 0CD92C 800CCD2C 8FAB0074 */  lw    $t3, 0x74($sp)
/* 0CD930 800CCD30 240C0000 */  li    $t4, 0
/* 0CD934 800CCD34 240D0000 */  li    $t5, 0
/* 0CD938 800CCD38 27AE0038 */  addiu $t6, $sp, 0x38
/* 0CD93C 800CCD3C 27AF007C */  addiu $t7, $sp, 0x7c
/* 0CD940 800CCD40 010A3023 */  subu  $a2, $t0, $t2
/* 0CD944 800CCD44 012B082B */  sltu  $at, $t1, $t3
/* 0CD948 800CCD48 00C13023 */  subu  $a2, $a2, $at
/* 0CD94C 800CCD4C AFAF001C */  sw    $t7, 0x1c($sp)
/* 0CD950 800CCD50 AFAE0018 */  sw    $t6, 0x18($sp)
/* 0CD954 800CCD54 AFAD0014 */  sw    $t5, 0x14($sp)
/* 0CD958 800CCD58 AFAC0010 */  sw    $t4, 0x10($sp)
/* 0CD95C 800CCD5C 27A40050 */  addiu $a0, $sp, 0x50
/* 0CD960 800CCD60 0C035378 */  jal   osSetTimer
/* 0CD964 800CCD64 012B3823 */   subu  $a3, $t1, $t3
/* 0CD968 800CCD68 27A40038 */  addiu $a0, $sp, 0x38
/* 0CD96C 800CCD6C 27A5007C */  addiu $a1, $sp, 0x7c
/* 0CD970 800CCD70 0C0322EC */  jal   osRecvMesg
/* 0CD974 800CCD74 24060001 */   li    $a2, 1
.L800CCD78:
/* 0CD978 800CCD78 24180004 */  li    $t8, 4
/* 0CD97C 800CCD7C 3C018013 */  lui   $at, %hi(__osMaxControllers) # $at, 0x8013
/* 0CD980 800CCD80 A038CD91 */  sb    $t8, %lo(__osMaxControllers)($at)
/* 0CD984 800CCD84 0C0333BA */  jal   func_800CCEE8
/* 0CD988 800CCD88 00002025 */   move  $a0, $zero
/* 0CD98C 800CCD8C 3C058013 */  lui   $a1, %hi(D_8012CD50) # $a1, 0x8013
/* 0CD990 800CCD90 24A5CD50 */  addiu $a1, %lo(D_8012CD50) # addiu $a1, $a1, -0x32b0
/* 0CD994 800CCD94 0C0335B0 */  jal   __osSiRawStartDma
/* 0CD998 800CCD98 24040001 */   li    $a0, 1
/* 0CD99C 800CCD9C AFA20078 */  sw    $v0, 0x78($sp)
/* 0CD9A0 800CCDA0 8FA40080 */  lw    $a0, 0x80($sp)
/* 0CD9A4 800CCDA4 27A5007C */  addiu $a1, $sp, 0x7c
/* 0CD9A8 800CCDA8 0C0322EC */  jal   osRecvMesg
/* 0CD9AC 800CCDAC 24060001 */   li    $a2, 1
/* 0CD9B0 800CCDB0 3C058013 */  lui   $a1, %hi(D_8012CD50) # $a1, 0x8013
/* 0CD9B4 800CCDB4 24A5CD50 */  addiu $a1, %lo(D_8012CD50) # addiu $a1, $a1, -0x32b0
/* 0CD9B8 800CCDB8 0C0335B0 */  jal   __osSiRawStartDma
/* 0CD9BC 800CCDBC 00002025 */   move  $a0, $zero
/* 0CD9C0 800CCDC0 AFA20078 */  sw    $v0, 0x78($sp)
/* 0CD9C4 800CCDC4 8FA40080 */  lw    $a0, 0x80($sp)
/* 0CD9C8 800CCDC8 27A5007C */  addiu $a1, $sp, 0x7c
/* 0CD9CC 800CCDCC 0C0322EC */  jal   osRecvMesg
/* 0CD9D0 800CCDD0 24060001 */   li    $a2, 1
/* 0CD9D4 800CCDD4 8FA40084 */  lw    $a0, 0x84($sp)
/* 0CD9D8 800CCDD8 0C033386 */  jal   func_800CCE18
/* 0CD9DC 800CCDDC 8FA50088 */   lw    $a1, 0x88($sp)
/* 0CD9E0 800CCDE0 3C018013 */  lui   $at, %hi(__osContLastCmd) # $at, 0x8013
/* 0CD9E4 800CCDE4 0C033580 */  jal   __osSiCreateAccessQueue
/* 0CD9E8 800CCDE8 A020CD90 */   sb    $zero, %lo(__osContLastCmd)($at)
/* 0CD9EC 800CCDEC 3C048013 */  lui   $a0, %hi(D_8012CDB8) # $a0, 0x8013
/* 0CD9F0 800CCDF0 3C058013 */  lui   $a1, %hi(D_8012CDD0) # $a1, 0x8013
/* 0CD9F4 800CCDF4 24A5CDD0 */  addiu $a1, %lo(D_8012CDD0) # addiu $a1, $a1, -0x3230
/* 0CD9F8 800CCDF8 2484CDB8 */  addiu $a0, %lo(D_8012CDB8) # addiu $a0, $a0, -0x3248
/* 0CD9FC 800CCDFC 0C032208 */  jal   osCreateMesgQueue
/* 0CDA00 800CCE00 24060001 */   li    $a2, 1
/* 0CDA04 800CCE04 8FA20078 */  lw    $v0, 0x78($sp)
.L800CCE08:
/* 0CDA08 800CCE08 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0CDA0C 800CCE0C 27BD0080 */  addiu $sp, $sp, 0x80
/* 0CDA10 800CCE10 03E00008 */  jr    $ra
/* 0CDA14 800CCE14 00000000 */   nop   

