glabel func_800AB4A8
/* 0AC0A8 800AB4A8 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0AC0AC 800AB4AC AFBF0034 */  sw    $ra, 0x34($sp)
/* 0AC0B0 800AB4B0 AFB40028 */  sw    $s4, 0x28($sp)
/* 0AC0B4 800AB4B4 AFB20020 */  sw    $s2, 0x20($sp)
/* 0AC0B8 800AB4B8 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0AC0BC 800AB4BC AFB00018 */  sw    $s0, 0x18($sp)
/* 0AC0C0 800AB4C0 00C08025 */  move  $s0, $a2
/* 0AC0C4 800AB4C4 00808825 */  move  $s1, $a0
/* 0AC0C8 800AB4C8 00E09025 */  move  $s2, $a3
/* 0AC0CC 800AB4CC 00A0A025 */  move  $s4, $a1
/* 0AC0D0 800AB4D0 AFB60030 */  sw    $s6, 0x30($sp)
/* 0AC0D4 800AB4D4 AFB5002C */  sw    $s5, 0x2c($sp)
/* 0AC0D8 800AB4D8 0C02ACD7 */  jal   free_weather_memory
/* 0AC0DC 800AB4DC AFB30024 */   sw    $s3, 0x24($sp)
/* 0AC0E0 800AB4E0 3C028012 */  lui   $v0, %hi(D_80127BB8) # $v0, 0x8012
/* 0AC0E4 800AB4E4 24427BB8 */  addiu $v0, %lo(D_80127BB8) # addiu $v0, $v0, 0x7bb8
/* 0AC0E8 800AB4E8 8FA30048 */  lw    $v1, 0x48($sp)
/* 0AC0EC 800AB4EC 8FA6004C */  lw    $a2, 0x4c($sp)
/* 0AC0F0 800AB4F0 8FA70050 */  lw    $a3, 0x50($sp)
/* 0AC0F4 800AB4F4 2A210002 */  slti  $at, $s1, 2
/* 0AC0F8 800AB4F8 AC50000C */  sw    $s0, 0xc($v0)
/* 0AC0FC 800AB4FC AC400010 */  sw    $zero, 0x10($v0)
/* 0AC100 800AB500 AC500014 */  sw    $s0, 0x14($v0)
/* 0AC104 800AB504 AC520018 */  sw    $s2, 0x18($v0)
/* 0AC108 800AB508 AC40001C */  sw    $zero, 0x1c($v0)
/* 0AC10C 800AB50C AC520020 */  sw    $s2, 0x20($v0)
/* 0AC110 800AB510 AC400028 */  sw    $zero, 0x28($v0)
/* 0AC114 800AB514 AC400004 */  sw    $zero, 4($v0)
/* 0AC118 800AB518 AC400034 */  sw    $zero, 0x34($v0)
/* 0AC11C 800AB51C AC40003C */  sw    $zero, 0x3c($v0)
/* 0AC120 800AB520 AC430024 */  sw    $v1, 0x24($v0)
/* 0AC124 800AB524 AC43002C */  sw    $v1, 0x2c($v0)
/* 0AC128 800AB528 AC460000 */  sw    $a2, ($v0)
/* 0AC12C 800AB52C AC460008 */  sw    $a2, 8($v0)
/* 0AC130 800AB530 AC470030 */  sw    $a3, 0x30($v0)
/* 0AC134 800AB534 14200002 */  bnez  $at, .L800AB540
/* 0AC138 800AB538 AC470038 */   sw    $a3, 0x38($v0)
/* 0AC13C 800AB53C 24110001 */  li    $s1, 1
.L800AB540:
/* 0AC140 800AB540 00117080 */  sll   $t6, $s1, 2
/* 0AC144 800AB544 01D17023 */  subu  $t6, $t6, $s1
/* 0AC148 800AB548 000E7080 */  sll   $t6, $t6, 2
/* 0AC14C 800AB54C 01D17023 */  subu  $t6, $t6, $s1
/* 0AC150 800AB550 3C0F800E */  lui   $t7, %hi(D_800E2850) # $t7, 0x800e
/* 0AC154 800AB554 25EF2850 */  addiu $t7, %lo(D_800E2850) # addiu $t7, $t7, 0x2850
/* 0AC158 800AB558 000E7080 */  sll   $t6, $t6, 2
/* 0AC15C 800AB55C 01CF8021 */  addu  $s0, $t6, $t7
/* 0AC160 800AB560 8E180008 */  lw    $t8, 8($s0)
/* 0AC164 800AB564 24010001 */  li    $at, 1
/* 0AC168 800AB568 17010006 */  bne   $t8, $at, .L800AB584
/* 0AC16C 800AB56C 3C16FFAA */   lui   $s6, (0xFFAA55FF >> 16) # lui $s6, 0xffaa
/* 0AC170 800AB570 24C40001 */  addiu $a0, $a2, 1
/* 0AC174 800AB574 0C02B451 */  jal   func_800AD144
/* 0AC178 800AB578 24E50001 */   addiu $a1, $a3, 1
/* 0AC17C 800AB57C 10000164 */  b     .L800ABB10
/* 0AC180 800AB580 8FBF0034 */   lw    $ra, 0x34($sp)
.L800AB584:
/* 0AC184 800AB584 8E040004 */  lw    $a0, 4($s0)
/* 0AC188 800AB588 36D655FF */  ori   $s6, (0xFFAA55FF & 0xFFFF) # ori $s6, $s6, 0x55ff
/* 0AC18C 800AB58C 0004C880 */  sll   $t9, $a0, 2
/* 0AC190 800AB590 0324C823 */  subu  $t9, $t9, $a0
/* 0AC194 800AB594 00192080 */  sll   $a0, $t9, 2
/* 0AC198 800AB598 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AC19C 800AB59C 02C02825 */   move  $a1, $s6
/* 0AC1A0 800AB5A0 3C15800E */  lui   $s5, %hi(D_800E28D8) # $s5, 0x800e
/* 0AC1A4 800AB5A4 26B528D8 */  addiu $s5, %lo(D_800E28D8) # addiu $s5, $s5, 0x28d8
/* 0AC1A8 800AB5A8 8E090004 */  lw    $t1, 4($s0)
/* 0AC1AC 800AB5AC 8E0B0010 */  lw    $t3, 0x10($s0)
/* 0AC1B0 800AB5B0 86180024 */  lh    $t8, 0x24($s0)
/* 0AC1B4 800AB5B4 86190026 */  lh    $t9, 0x26($s0)
/* 0AC1B8 800AB5B8 8E0D0018 */  lw    $t5, 0x18($s0)
/* 0AC1BC 800AB5BC 8E0A000C */  lw    $t2, 0xc($s0)
/* 0AC1C0 800AB5C0 8E0C0014 */  lw    $t4, 0x14($s0)
/* 0AC1C4 800AB5C4 AEA90004 */  sw    $t1, 4($s5)
/* 0AC1C8 800AB5C8 AEAB0010 */  sw    $t3, 0x10($s5)
/* 0AC1CC 800AB5CC A6B80024 */  sh    $t8, 0x24($s5)
/* 0AC1D0 800AB5D0 A6B90026 */  sh    $t9, 0x26($s5)
/* 0AC1D4 800AB5D4 86A90024 */  lh    $t1, 0x24($s5)
/* 0AC1D8 800AB5D8 86AB0026 */  lh    $t3, 0x26($s5)
/* 0AC1DC 800AB5DC AEAD0018 */  sw    $t5, 0x18($s5)
/* 0AC1E0 800AB5E0 8E0E001C */  lw    $t6, 0x1c($s0)
/* 0AC1E4 800AB5E4 8E0F0020 */  lw    $t7, 0x20($s0)
/* 0AC1E8 800AB5E8 8E0D0008 */  lw    $t5, 8($s0)
/* 0AC1EC 800AB5EC AEAA000C */  sw    $t2, 0xc($s5)
/* 0AC1F0 800AB5F0 AEAC0014 */  sw    $t4, 0x14($s5)
/* 0AC1F4 800AB5F4 00095040 */  sll   $t2, $t1, 1
/* 0AC1F8 800AB5F8 000B6040 */  sll   $t4, $t3, 1
/* 0AC1FC 800AB5FC AEA20000 */  sw    $v0, ($s5)
/* 0AC200 800AB600 A6AA0028 */  sh    $t2, 0x28($s5)
/* 0AC204 800AB604 A6AC002A */  sh    $t4, 0x2a($s5)
/* 0AC208 800AB608 AEAE001C */  sw    $t6, 0x1c($s5)
/* 0AC20C 800AB60C 15A00003 */  bnez  $t5, .L800AB61C
/* 0AC210 800AB610 AEAF0020 */   sw    $t7, 0x20($s5)
/* 0AC214 800AB614 0C02AECD */  jal   func_800ABB34
/* 0AC218 800AB618 00000000 */   nop   
.L800AB61C:
/* 0AC21C 800AB61C 3C138012 */  lui   $s3, %hi(D_80127BB0) # $s3, 0x8012
/* 0AC220 800AB620 26737BB0 */  addiu $s3, %lo(D_80127BB0) # addiu $s3, $s3, 0x7bb0
/* 0AC224 800AB624 AE740000 */  sw    $s4, ($s3)
/* 0AC228 800AB628 00142040 */  sll   $a0, $s4, 1
/* 0AC22C 800AB62C 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AC230 800AB630 02C02825 */   move  $a1, $s6
/* 0AC234 800AB634 3C01800E */  lui   $at, %hi(D_800E2910) # $at, 0x800e
/* 0AC238 800AB638 AC222910 */  sw    $v0, %lo(D_800E2910)($at)
/* 0AC23C 800AB63C 00142100 */  sll   $a0, $s4, 4
/* 0AC240 800AB640 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AC244 800AB644 02C02825 */   move  $a1, $s6
/* 0AC248 800AB648 8E6E0000 */  lw    $t6, ($s3)
/* 0AC24C 800AB64C 3C12800E */  lui   $s2, %hi(D_800E28D4) # $s2, 0x800e
/* 0AC250 800AB650 265228D4 */  addiu $s2, %lo(D_800E28D4) # addiu $s2, $s2, 0x28d4
/* 0AC254 800AB654 AE420000 */  sw    $v0, ($s2)
/* 0AC258 800AB658 19C0003F */  blez  $t6, .L800AB758
/* 0AC25C 800AB65C 00008825 */   move  $s1, $zero
/* 0AC260 800AB660 00008025 */  move  $s0, $zero
.L800AB664:
/* 0AC264 800AB664 8EA50018 */  lw    $a1, 0x18($s5)
/* 0AC268 800AB668 0C01BE53 */  jal   get_random_number_from_range
/* 0AC26C 800AB66C 00002025 */   move  $a0, $zero
/* 0AC270 800AB670 8E4F0000 */  lw    $t7, ($s2)
/* 0AC274 800AB674 00002025 */  move  $a0, $zero
/* 0AC278 800AB678 01F0C021 */  addu  $t8, $t7, $s0
/* 0AC27C 800AB67C AF020000 */  sw    $v0, ($t8)
/* 0AC280 800AB680 8EA5001C */  lw    $a1, 0x1c($s5)
/* 0AC284 800AB684 0C01BE53 */  jal   get_random_number_from_range
/* 0AC288 800AB688 00000000 */   nop   
/* 0AC28C 800AB68C 8E590000 */  lw    $t9, ($s2)
/* 0AC290 800AB690 00002025 */  move  $a0, $zero
/* 0AC294 800AB694 03304821 */  addu  $t1, $t9, $s0
/* 0AC298 800AB698 AD220004 */  sw    $v0, 4($t1)
/* 0AC29C 800AB69C 8EA50020 */  lw    $a1, 0x20($s5)
/* 0AC2A0 800AB6A0 0C01BE53 */  jal   get_random_number_from_range
/* 0AC2A4 800AB6A4 00000000 */   nop   
/* 0AC2A8 800AB6A8 8E4A0000 */  lw    $t2, ($s2)
/* 0AC2AC 800AB6AC 00002025 */  move  $a0, $zero
/* 0AC2B0 800AB6B0 01505821 */  addu  $t3, $t2, $s0
/* 0AC2B4 800AB6B4 AD620008 */  sw    $v0, 8($t3)
/* 0AC2B8 800AB6B8 0C01BE53 */  jal   get_random_number_from_range
/* 0AC2BC 800AB6BC 24050020 */   li    $a1, 32
/* 0AC2C0 800AB6C0 8E4F0000 */  lw    $t7, ($s2)
/* 0AC2C4 800AB6C4 244C0005 */  addiu $t4, $v0, 5
/* 0AC2C8 800AB6C8 240D0001 */  li    $t5, 1
/* 0AC2CC 800AB6CC 018D7004 */  sllv  $t6, $t5, $t4
/* 0AC2D0 800AB6D0 01F0C021 */  addu  $t8, $t7, $s0
/* 0AC2D4 800AB6D4 A30E000C */  sb    $t6, 0xc($t8)
/* 0AC2D8 800AB6D8 00002025 */  move  $a0, $zero
/* 0AC2DC 800AB6DC 0C01BE53 */  jal   get_random_number_from_range
/* 0AC2E0 800AB6E0 24050020 */   li    $a1, 32
/* 0AC2E4 800AB6E4 8E4B0000 */  lw    $t3, ($s2)
/* 0AC2E8 800AB6E8 24590005 */  addiu $t9, $v0, 5
/* 0AC2EC 800AB6EC 24090001 */  li    $t1, 1
/* 0AC2F0 800AB6F0 03295004 */  sllv  $t2, $t1, $t9
/* 0AC2F4 800AB6F4 01706821 */  addu  $t5, $t3, $s0
/* 0AC2F8 800AB6F8 A1AA000D */  sb    $t2, 0xd($t5)
/* 0AC2FC 800AB6FC 00002025 */  move  $a0, $zero
/* 0AC300 800AB700 0C01BE53 */  jal   get_random_number_from_range
/* 0AC304 800AB704 24050020 */   li    $a1, 32
/* 0AC308 800AB708 8E580000 */  lw    $t8, ($s2)
/* 0AC30C 800AB70C 244C0005 */  addiu $t4, $v0, 5
/* 0AC310 800AB710 240F0001 */  li    $t7, 1
/* 0AC314 800AB714 018F7004 */  sllv  $t6, $t7, $t4
/* 0AC318 800AB718 03104821 */  addu  $t1, $t8, $s0
/* 0AC31C 800AB71C A12E000E */  sb    $t6, 0xe($t1)
/* 0AC320 800AB720 8EA50004 */  lw    $a1, 4($s5)
/* 0AC324 800AB724 00002025 */  move  $a0, $zero
/* 0AC328 800AB728 0C01BE53 */  jal   get_random_number_from_range
/* 0AC32C 800AB72C 24A5FFFF */   addiu $a1, $a1, -1
/* 0AC330 800AB730 8E590000 */  lw    $t9, ($s2)
/* 0AC334 800AB734 26310001 */  addiu $s1, $s1, 1
/* 0AC338 800AB738 03305821 */  addu  $t3, $t9, $s0
/* 0AC33C 800AB73C A162000F */  sb    $v0, 0xf($t3)
/* 0AC340 800AB740 8E6A0000 */  lw    $t2, ($s3)
/* 0AC344 800AB744 26100010 */  addiu $s0, $s0, 0x10
/* 0AC348 800AB748 022A082A */  slt   $at, $s1, $t2
/* 0AC34C 800AB74C 1420FFC5 */  bnez  $at, .L800AB664
/* 0AC350 800AB750 00000000 */   nop   
/* 0AC354 800AB754 00008825 */  move  $s1, $zero
.L800AB758:
/* 0AC358 800AB758 00148080 */  sll   $s0, $s4, 2
/* 0AC35C 800AB75C 00109080 */  sll   $s2, $s0, 2
/* 0AC360 800AB760 02509021 */  addu  $s2, $s2, $s0
/* 0AC364 800AB764 00129040 */  sll   $s2, $s2, 1
/* 0AC368 800AB768 02402025 */  move  $a0, $s2
/* 0AC36C 800AB76C 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AC370 800AB770 02C02825 */   move  $a1, $s6
/* 0AC374 800AB774 3C13800E */  lui   $s3, %hi(D_800E2914) # $s3, 0x800e
/* 0AC378 800AB778 26732914 */  addiu $s3, %lo(D_800E2914) # addiu $s3, $s3, 0x2914
/* 0AC37C 800AB77C AE620000 */  sw    $v0, ($s3)
/* 0AC380 800AB780 02402025 */  move  $a0, $s2
/* 0AC384 800AB784 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AC388 800AB788 02C02825 */   move  $a1, $s6
/* 0AC38C 800AB78C 3C07800E */  lui   $a3, %hi(D_800E2914) # $a3, 0x800e
/* 0AC390 800AB790 3C08800E */  lui   $t0, %hi(gWeatherAssetTable) # $t0, 0x800e
/* 0AC394 800AB794 3C03800E */  lui   $v1, %hi(D_800E2904) # $v1, 0x800e
/* 0AC398 800AB798 AE620004 */  sw    $v0, 4($s3)
/* 0AC39C 800AB79C 24632904 */  addiu $v1, %lo(D_800E2904) # addiu $v1, $v1, 0x2904
/* 0AC3A0 800AB7A0 2508291C */  addiu $t0, %lo(gWeatherAssetTable) # addiu $t0, $t0, 0x291c
/* 0AC3A4 800AB7A4 24E72914 */  addiu $a3, %lo(D_800E2914) # addiu $a3, $a3, 0x2914
/* 0AC3A8 800AB7A8 240400FF */  li    $a0, 255
.L800AB7AC:
/* 0AC3AC 800AB7AC 8CED0000 */  lw    $t5, ($a3)
/* 0AC3B0 800AB7B0 1A000063 */  blez  $s0, .L800AB940
/* 0AC3B4 800AB7B4 AC6D0000 */   sw    $t5, ($v1)
/* 0AC3B8 800AB7B8 32060003 */  andi  $a2, $s0, 3
/* 0AC3BC 800AB7BC 10C00017 */  beqz  $a2, .L800AB81C
/* 0AC3C0 800AB7C0 00C02825 */   move  $a1, $a2
/* 0AC3C4 800AB7C4 00111080 */  sll   $v0, $s1, 2
/* 0AC3C8 800AB7C8 00511021 */  addu  $v0, $v0, $s1
/* 0AC3CC 800AB7CC 00021040 */  sll   $v0, $v0, 1
.L800AB7D0:
/* 0AC3D0 800AB7D0 8C6F0000 */  lw    $t7, ($v1)
/* 0AC3D4 800AB7D4 26310001 */  addiu $s1, $s1, 1
/* 0AC3D8 800AB7D8 01E26021 */  addu  $t4, $t7, $v0
/* 0AC3DC 800AB7DC A1840006 */  sb    $a0, 6($t4)
/* 0AC3E0 800AB7E0 8C780000 */  lw    $t8, ($v1)
/* 0AC3E4 800AB7E4 00000000 */  nop   
/* 0AC3E8 800AB7E8 03027021 */  addu  $t6, $t8, $v0
/* 0AC3EC 800AB7EC A1C40007 */  sb    $a0, 7($t6)
/* 0AC3F0 800AB7F0 8C690000 */  lw    $t1, ($v1)
/* 0AC3F4 800AB7F4 00000000 */  nop   
/* 0AC3F8 800AB7F8 0122C821 */  addu  $t9, $t1, $v0
/* 0AC3FC 800AB7FC A3240008 */  sb    $a0, 8($t9)
/* 0AC400 800AB800 8C6B0000 */  lw    $t3, ($v1)
/* 0AC404 800AB804 00000000 */  nop   
/* 0AC408 800AB808 01625021 */  addu  $t2, $t3, $v0
/* 0AC40C 800AB80C A1440009 */  sb    $a0, 9($t2)
/* 0AC410 800AB810 14B1FFEF */  bne   $a1, $s1, .L800AB7D0
/* 0AC414 800AB814 2442000A */   addiu $v0, $v0, 0xa
/* 0AC418 800AB818 12300048 */  beq   $s1, $s0, .L800AB93C
.L800AB81C:
/* 0AC41C 800AB81C 00111080 */   sll   $v0, $s1, 2
/* 0AC420 800AB820 00102880 */  sll   $a1, $s0, 2
/* 0AC424 800AB824 00B02821 */  addu  $a1, $a1, $s0
/* 0AC428 800AB828 00511021 */  addu  $v0, $v0, $s1
/* 0AC42C 800AB82C 00021040 */  sll   $v0, $v0, 1
/* 0AC430 800AB830 00052840 */  sll   $a1, $a1, 1
.L800AB834:
/* 0AC434 800AB834 8C6D0000 */  lw    $t5, ($v1)
/* 0AC438 800AB838 00000000 */  nop   
/* 0AC43C 800AB83C 01A27821 */  addu  $t7, $t5, $v0
/* 0AC440 800AB840 A1E40006 */  sb    $a0, 6($t7)
/* 0AC444 800AB844 8C6C0000 */  lw    $t4, ($v1)
/* 0AC448 800AB848 00000000 */  nop   
/* 0AC44C 800AB84C 0182C021 */  addu  $t8, $t4, $v0
/* 0AC450 800AB850 A3040007 */  sb    $a0, 7($t8)
/* 0AC454 800AB854 8C6E0000 */  lw    $t6, ($v1)
/* 0AC458 800AB858 00000000 */  nop   
/* 0AC45C 800AB85C 01C24821 */  addu  $t1, $t6, $v0
/* 0AC460 800AB860 A1240008 */  sb    $a0, 8($t1)
/* 0AC464 800AB864 8C790000 */  lw    $t9, ($v1)
/* 0AC468 800AB868 00000000 */  nop   
/* 0AC46C 800AB86C 03225821 */  addu  $t3, $t9, $v0
/* 0AC470 800AB870 A1640009 */  sb    $a0, 9($t3)
/* 0AC474 800AB874 8C6A0000 */  lw    $t2, ($v1)
/* 0AC478 800AB878 00000000 */  nop   
/* 0AC47C 800AB87C 01426821 */  addu  $t5, $t2, $v0
/* 0AC480 800AB880 A1A40010 */  sb    $a0, 0x10($t5)
/* 0AC484 800AB884 8C6F0000 */  lw    $t7, ($v1)
/* 0AC488 800AB888 00000000 */  nop   
/* 0AC48C 800AB88C 01E26021 */  addu  $t4, $t7, $v0
/* 0AC490 800AB890 A1840011 */  sb    $a0, 0x11($t4)
/* 0AC494 800AB894 8C780000 */  lw    $t8, ($v1)
/* 0AC498 800AB898 00000000 */  nop   
/* 0AC49C 800AB89C 03027021 */  addu  $t6, $t8, $v0
/* 0AC4A0 800AB8A0 A1C40012 */  sb    $a0, 0x12($t6)
/* 0AC4A4 800AB8A4 8C690000 */  lw    $t1, ($v1)
/* 0AC4A8 800AB8A8 00000000 */  nop   
/* 0AC4AC 800AB8AC 0122C821 */  addu  $t9, $t1, $v0
/* 0AC4B0 800AB8B0 A3240013 */  sb    $a0, 0x13($t9)
/* 0AC4B4 800AB8B4 8C6B0000 */  lw    $t3, ($v1)
/* 0AC4B8 800AB8B8 00000000 */  nop   
/* 0AC4BC 800AB8BC 01625021 */  addu  $t2, $t3, $v0
/* 0AC4C0 800AB8C0 A144001A */  sb    $a0, 0x1a($t2)
/* 0AC4C4 800AB8C4 8C6D0000 */  lw    $t5, ($v1)
/* 0AC4C8 800AB8C8 00000000 */  nop   
/* 0AC4CC 800AB8CC 01A27821 */  addu  $t7, $t5, $v0
/* 0AC4D0 800AB8D0 A1E4001B */  sb    $a0, 0x1b($t7)
/* 0AC4D4 800AB8D4 8C6C0000 */  lw    $t4, ($v1)
/* 0AC4D8 800AB8D8 00000000 */  nop   
/* 0AC4DC 800AB8DC 0182C021 */  addu  $t8, $t4, $v0
/* 0AC4E0 800AB8E0 A304001C */  sb    $a0, 0x1c($t8)
/* 0AC4E4 800AB8E4 8C6E0000 */  lw    $t6, ($v1)
/* 0AC4E8 800AB8E8 00000000 */  nop   
/* 0AC4EC 800AB8EC 01C24821 */  addu  $t1, $t6, $v0
/* 0AC4F0 800AB8F0 A124001D */  sb    $a0, 0x1d($t1)
/* 0AC4F4 800AB8F4 8C790000 */  lw    $t9, ($v1)
/* 0AC4F8 800AB8F8 00000000 */  nop   
/* 0AC4FC 800AB8FC 03225821 */  addu  $t3, $t9, $v0
/* 0AC500 800AB900 A1640024 */  sb    $a0, 0x24($t3)
/* 0AC504 800AB904 8C6A0000 */  lw    $t2, ($v1)
/* 0AC508 800AB908 00000000 */  nop   
/* 0AC50C 800AB90C 01426821 */  addu  $t5, $t2, $v0
/* 0AC510 800AB910 A1A40025 */  sb    $a0, 0x25($t5)
/* 0AC514 800AB914 8C6F0000 */  lw    $t7, ($v1)
/* 0AC518 800AB918 00000000 */  nop   
/* 0AC51C 800AB91C 01E26021 */  addu  $t4, $t7, $v0
/* 0AC520 800AB920 A1840026 */  sb    $a0, 0x26($t4)
/* 0AC524 800AB924 8C780000 */  lw    $t8, ($v1)
/* 0AC528 800AB928 00000000 */  nop   
/* 0AC52C 800AB92C 03027021 */  addu  $t6, $t8, $v0
/* 0AC530 800AB930 24420028 */  addiu $v0, $v0, 0x28
/* 0AC534 800AB934 1445FFBF */  bne   $v0, $a1, .L800AB834
/* 0AC538 800AB938 A1C40027 */   sb    $a0, 0x27($t6)
.L800AB93C:
/* 0AC53C 800AB93C 00008825 */  move  $s1, $zero
.L800AB940:
/* 0AC540 800AB940 24E70004 */  addiu $a3, $a3, 4
/* 0AC544 800AB944 00E8082B */  sltu  $at, $a3, $t0
/* 0AC548 800AB948 1420FF98 */  bnez  $at, .L800AB7AC
/* 0AC54C 800AB94C 00000000 */   nop   
/* 0AC550 800AB950 8EA20008 */  lw    $v0, 8($s5)
/* 0AC554 800AB954 3C148012 */  lui   $s4, %hi(D_80127C04) # $s4, 0x8012
/* 0AC558 800AB958 90520000 */  lbu   $s2, ($v0)
/* 0AC55C 800AB95C 90530001 */  lbu   $s3, 1($v0)
/* 0AC560 800AB960 26947C04 */  addiu $s4, %lo(D_80127C04) # addiu $s4, $s4, 0x7c04
/* 0AC564 800AB964 8E840000 */  lw    $a0, ($s4)
/* 0AC568 800AB968 00124940 */  sll   $t1, $s2, 5
/* 0AC56C 800AB96C 00135140 */  sll   $t2, $s3, 5
/* 0AC570 800AB970 2532FFFF */  addiu $s2, $t1, -1
/* 0AC574 800AB974 2553FFFF */  addiu $s3, $t2, -1
/* 0AC578 800AB978 0012CC00 */  sll   $t9, $s2, 0x10
/* 0AC57C 800AB97C 00136C00 */  sll   $t5, $s3, 0x10
/* 0AC580 800AB980 00046100 */  sll   $t4, $a0, 4
/* 0AC584 800AB984 00199403 */  sra   $s2, $t9, 0x10
/* 0AC588 800AB988 000D9C03 */  sra   $s3, $t5, 0x10
/* 0AC58C 800AB98C 01802025 */  move  $a0, $t4
/* 0AC590 800AB990 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0AC594 800AB994 02C02825 */   move  $a1, $s6
/* 0AC598 800AB998 8E980000 */  lw    $t8, ($s4)
/* 0AC59C 800AB99C 3C03800E */  lui   $v1, %hi(D_800E290C) # $v1, 0x800e
/* 0AC5A0 800AB9A0 2463290C */  addiu $v1, %lo(D_800E290C) # addiu $v1, $v1, 0x290c
/* 0AC5A4 800AB9A4 1B000057 */  blez  $t8, .L800ABB04
/* 0AC5A8 800AB9A8 AC620000 */   sw    $v0, ($v1)
/* 0AC5AC 800AB9AC 00008025 */  move  $s0, $zero
.L800AB9B0:
/* 0AC5B0 800AB9B0 8C6E0000 */  lw    $t6, ($v1)
/* 0AC5B4 800AB9B4 00112040 */  sll   $a0, $s1, 1
/* 0AC5B8 800AB9B8 01D04821 */  addu  $t1, $t6, $s0
/* 0AC5BC 800AB9BC A1200000 */  sb    $zero, ($t1)
/* 0AC5C0 800AB9C0 8C790000 */  lw    $t9, ($v1)
/* 0AC5C4 800AB9C4 24820003 */  addiu $v0, $a0, 3
/* 0AC5C8 800AB9C8 03305821 */  addu  $t3, $t9, $s0
/* 0AC5CC 800AB9CC A1620001 */  sb    $v0, 1($t3)
/* 0AC5D0 800AB9D0 8C6A0000 */  lw    $t2, ($v1)
/* 0AC5D4 800AB9D4 24850001 */  addiu $a1, $a0, 1
/* 0AC5D8 800AB9D8 01506821 */  addu  $t5, $t2, $s0
/* 0AC5DC 800AB9DC A5A00004 */  sh    $zero, 4($t5)
/* 0AC5E0 800AB9E0 8C6F0000 */  lw    $t7, ($v1)
/* 0AC5E4 800AB9E4 26310002 */  addiu $s1, $s1, 2
/* 0AC5E8 800AB9E8 01F06021 */  addu  $t4, $t7, $s0
/* 0AC5EC 800AB9EC A5930006 */  sh    $s3, 6($t4)
/* 0AC5F0 800AB9F0 8C780000 */  lw    $t8, ($v1)
/* 0AC5F4 800AB9F4 00000000 */  nop   
/* 0AC5F8 800AB9F8 03107021 */  addu  $t6, $t8, $s0
/* 0AC5FC 800AB9FC A1C50002 */  sb    $a1, 2($t6)
/* 0AC600 800ABA00 8C690000 */  lw    $t1, ($v1)
/* 0AC604 800ABA04 00000000 */  nop   
/* 0AC608 800ABA08 0130C821 */  addu  $t9, $t1, $s0
/* 0AC60C 800ABA0C A7320008 */  sh    $s2, 8($t9)
/* 0AC610 800ABA10 8C6B0000 */  lw    $t3, ($v1)
/* 0AC614 800ABA14 00000000 */  nop   
/* 0AC618 800ABA18 01705021 */  addu  $t2, $t3, $s0
/* 0AC61C 800ABA1C A540000A */  sh    $zero, 0xa($t2)
/* 0AC620 800ABA20 8C6D0000 */  lw    $t5, ($v1)
/* 0AC624 800ABA24 00000000 */  nop   
/* 0AC628 800ABA28 01B07821 */  addu  $t7, $t5, $s0
/* 0AC62C 800ABA2C A1E40003 */  sb    $a0, 3($t7)
/* 0AC630 800ABA30 8C6C0000 */  lw    $t4, ($v1)
/* 0AC634 800ABA34 00000000 */  nop   
/* 0AC638 800ABA38 0190C021 */  addu  $t8, $t4, $s0
/* 0AC63C 800ABA3C A700000C */  sh    $zero, 0xc($t8)
/* 0AC640 800ABA40 8C6E0000 */  lw    $t6, ($v1)
/* 0AC644 800ABA44 00000000 */  nop   
/* 0AC648 800ABA48 01D04821 */  addu  $t1, $t6, $s0
/* 0AC64C 800ABA4C A520000E */  sh    $zero, 0xe($t1)
/* 0AC650 800ABA50 8C790000 */  lw    $t9, ($v1)
/* 0AC654 800ABA54 24890002 */  addiu $t1, $a0, 2
/* 0AC658 800ABA58 03305821 */  addu  $t3, $t9, $s0
/* 0AC65C 800ABA5C A1600010 */  sb    $zero, 0x10($t3)
/* 0AC660 800ABA60 8C6A0000 */  lw    $t2, ($v1)
/* 0AC664 800ABA64 00000000 */  nop   
/* 0AC668 800ABA68 01506821 */  addu  $t5, $t2, $s0
/* 0AC66C 800ABA6C A1A20011 */  sb    $v0, 0x11($t5)
/* 0AC670 800ABA70 8C6F0000 */  lw    $t7, ($v1)
/* 0AC674 800ABA74 00000000 */  nop   
/* 0AC678 800ABA78 01F06021 */  addu  $t4, $t7, $s0
/* 0AC67C 800ABA7C A5800014 */  sh    $zero, 0x14($t4)
/* 0AC680 800ABA80 8C780000 */  lw    $t8, ($v1)
/* 0AC684 800ABA84 00000000 */  nop   
/* 0AC688 800ABA88 03107021 */  addu  $t6, $t8, $s0
/* 0AC68C 800ABA8C A5D30016 */  sh    $s3, 0x16($t6)
/* 0AC690 800ABA90 8C790000 */  lw    $t9, ($v1)
/* 0AC694 800ABA94 00000000 */  nop   
/* 0AC698 800ABA98 03305821 */  addu  $t3, $t9, $s0
/* 0AC69C 800ABA9C A1690012 */  sb    $t1, 0x12($t3)
/* 0AC6A0 800ABAA0 8C6A0000 */  lw    $t2, ($v1)
/* 0AC6A4 800ABAA4 00000000 */  nop   
/* 0AC6A8 800ABAA8 01506821 */  addu  $t5, $t2, $s0
/* 0AC6AC 800ABAAC A5B20018 */  sh    $s2, 0x18($t5)
/* 0AC6B0 800ABAB0 8C6F0000 */  lw    $t7, ($v1)
/* 0AC6B4 800ABAB4 00000000 */  nop   
/* 0AC6B8 800ABAB8 01F06021 */  addu  $t4, $t7, $s0
/* 0AC6BC 800ABABC A593001A */  sh    $s3, 0x1a($t4)
/* 0AC6C0 800ABAC0 8C780000 */  lw    $t8, ($v1)
/* 0AC6C4 800ABAC4 00000000 */  nop   
/* 0AC6C8 800ABAC8 03107021 */  addu  $t6, $t8, $s0
/* 0AC6CC 800ABACC A1C50013 */  sb    $a1, 0x13($t6)
/* 0AC6D0 800ABAD0 8C790000 */  lw    $t9, ($v1)
/* 0AC6D4 800ABAD4 00000000 */  nop   
/* 0AC6D8 800ABAD8 03304821 */  addu  $t1, $t9, $s0
/* 0AC6DC 800ABADC A532001C */  sh    $s2, 0x1c($t1)
/* 0AC6E0 800ABAE0 8C6B0000 */  lw    $t3, ($v1)
/* 0AC6E4 800ABAE4 00000000 */  nop   
/* 0AC6E8 800ABAE8 01705021 */  addu  $t2, $t3, $s0
/* 0AC6EC 800ABAEC A540001E */  sh    $zero, 0x1e($t2)
/* 0AC6F0 800ABAF0 8E8D0000 */  lw    $t5, ($s4)
/* 0AC6F4 800ABAF4 26100020 */  addiu $s0, $s0, 0x20
/* 0AC6F8 800ABAF8 022D082A */  slt   $at, $s1, $t5
/* 0AC6FC 800ABAFC 1420FFAC */  bnez  $at, .L800AB9B0
/* 0AC700 800ABB00 00000000 */   nop   
.L800ABB04:
/* 0AC704 800ABB04 3C018012 */  lui   $at, %hi(D_80127C08) # $at, 0x8012
/* 0AC708 800ABB08 AC207C08 */  sw    $zero, %lo(D_80127C08)($at)
/* 0AC70C 800ABB0C 8FBF0034 */  lw    $ra, 0x34($sp)
.L800ABB10:
/* 0AC710 800ABB10 8FB00018 */  lw    $s0, 0x18($sp)
/* 0AC714 800ABB14 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0AC718 800ABB18 8FB20020 */  lw    $s2, 0x20($sp)
/* 0AC71C 800ABB1C 8FB30024 */  lw    $s3, 0x24($sp)
/* 0AC720 800ABB20 8FB40028 */  lw    $s4, 0x28($sp)
/* 0AC724 800ABB24 8FB5002C */  lw    $s5, 0x2c($sp)
/* 0AC728 800ABB28 8FB60030 */  lw    $s6, 0x30($sp)
/* 0AC72C 800ABB2C 03E00008 */  jr    $ra
/* 0AC730 800ABB30 27BD0038 */   addiu $sp, $sp, 0x38

