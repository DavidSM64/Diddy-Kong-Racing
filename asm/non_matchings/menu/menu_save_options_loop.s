.late_rodata
glabel jpt_800E84B0
.word L80087D18, L80087D28, L80087D54, L80087D94, L80087DAC, L80087DEC, L80087E04, L80087E1C

.text
glabel menu_save_options_loop
/* 088760 80087B60 3C038012 */  lui   $v1, %hi(gOptionBlinkTimer) # $v1, 0x8012
/* 088764 80087B64 246363BC */  addiu $v1, %lo(gOptionBlinkTimer) # addiu $v1, $v1, 0x63bc
/* 088768 80087B68 8C6E0000 */  lw    $t6, ($v1)
/* 08876C 80087B6C 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 088770 80087B70 01C47821 */  addu  $t7, $t6, $a0
/* 088774 80087B74 31F8003F */  andi  $t8, $t7, 0x3f
/* 088778 80087B78 AC780000 */  sw    $t8, ($v1)
/* 08877C 80087B7C 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 088780 80087B80 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 088784 80087B84 AFB00018 */  sw    $s0, 0x18($sp)
/* 088788 80087B88 00808025 */  move  $s0, $a0
/* 08878C 80087B8C AFBF002C */  sw    $ra, 0x2c($sp)
/* 088790 80087B90 AFB40028 */  sw    $s4, 0x28($sp)
/* 088794 80087B94 AFB30024 */  sw    $s3, 0x24($sp)
/* 088798 80087B98 AFB20020 */  sw    $s2, 0x20($sp)
/* 08879C 80087B9C 10400009 */  beqz  $v0, .L80087BC4
/* 0887A0 80087BA0 AFB1001C */   sw    $s1, 0x1c($sp)
/* 0887A4 80087BA4 18400005 */  blez  $v0, .L80087BBC
/* 0887A8 80087BA8 00504023 */   subu  $t0, $v0, $s0
/* 0887AC 80087BAC 0044C821 */  addu  $t9, $v0, $a0
/* 0887B0 80087BB0 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 0887B4 80087BB4 10000003 */  b     .L80087BC4
/* 0887B8 80087BB8 AC39F47C */   sw    $t9, %lo(gMenuDelay)($at)
.L80087BBC:
/* 0887BC 80087BBC 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 0887C0 80087BC0 AC28F47C */  sw    $t0, %lo(gMenuDelay)($at)
.L80087BC4:
/* 0887C4 80087BC4 3C098012 */  lui   $t1, %hi(D_801263E0) # $t1, 0x8012
/* 0887C8 80087BC8 8D2963E0 */  lw    $t1, %lo(D_801263E0)($t1)
/* 0887CC 80087BCC 00000000 */  nop   
/* 0887D0 80087BD0 312A0007 */  andi  $t2, $t1, 7
/* 0887D4 80087BD4 29410002 */  slti  $at, $t2, 2
/* 0887D8 80087BD8 14200003 */  bnez  $at, .L80087BE8
/* 0887DC 80087BDC 00000000 */   nop   
/* 0887E0 80087BE0 0C021A92 */  jal   func_80086A48
/* 0887E4 80087BE4 02002025 */   move  $a0, $s0
.L80087BE8:
/* 0887E8 80087BE8 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 0887EC 80087BEC 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 0887F0 80087BF0 00000000 */  nop   
/* 0887F4 80087BF4 2841FFED */  slti  $at, $v0, -0x13
/* 0887F8 80087BF8 14200008 */  bnez  $at, .L80087C1C
/* 0887FC 80087BFC 28410014 */   slti  $at, $v0, 0x14
/* 088800 80087C00 10200006 */  beqz  $at, .L80087C1C
/* 088804 80087C04 00000000 */   nop   
/* 088808 80087C08 0C0216E7 */  jal   func_80085B9C
/* 08880C 80087C0C 02002025 */   move  $a0, $s0
/* 088810 80087C10 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 088814 80087C14 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 088818 80087C18 00000000 */  nop   
.L80087C1C:
/* 08881C 80087C1C 10400013 */  beqz  $v0, .L80087C6C
/* 088820 80087C20 00003025 */   move  $a2, $zero
/* 088824 80087C24 2841001F */  slti  $at, $v0, 0x1f
/* 088828 80087C28 14200008 */  bnez  $at, .L80087C4C
/* 08882C 80087C2C 2841FFE2 */   slti  $at, $v0, -0x1e
/* 088830 80087C30 0C021FAE */  jal   func_80087EB8
/* 088834 80087C34 00000000 */   nop   
/* 088838 80087C38 0C0204F4 */  jal   menu_init
/* 08883C 80087C3C 24040018 */   li    $a0, 24
/* 088840 80087C40 10000095 */  b     .L80087E98
/* 088844 80087C44 00001025 */   move  $v0, $zero
/* 088848 80087C48 2841FFE2 */  slti  $at, $v0, -0x1e
.L80087C4C:
/* 08884C 80087C4C 10200005 */  beqz  $at, .L80087C64
/* 088850 80087C50 00000000 */   nop   
/* 088854 80087C54 0C021FAE */  jal   func_80087EB8
/* 088858 80087C58 00000000 */   nop   
/* 08885C 80087C5C 0C0204F4 */  jal   menu_init
/* 088860 80087C60 2404000C */   li    $a0, 12
.L80087C64:
/* 088864 80087C64 1000008C */  b     .L80087E98
/* 088868 80087C68 00001025 */   move  $v0, $zero
.L80087C6C:
/* 08886C 80087C6C 3C0B8012 */  lui   $t3, %hi(gIgnorePlayerInput) # $t3, 0x8012
/* 088870 80087C70 8D6B63C4 */  lw    $t3, %lo(gIgnorePlayerInput)($t3)
/* 088874 80087C74 0000A025 */  move  $s4, $zero
/* 088878 80087C78 15600014 */  bnez  $t3, .L80087CCC
/* 08887C 80087C7C 00009825 */   move  $s3, $zero
/* 088880 80087C80 3C118012 */  lui   $s1, %hi(gControllersXAxisDirection) # $s1, 0x8012
/* 088884 80087C84 3C128012 */  lui   $s2, %hi(gControllersYAxisDirection) # $s2, 0x8012
/* 088888 80087C88 26526464 */  addiu $s2, %lo(gControllersYAxisDirection) # addiu $s2, $s2, 0x6464
/* 08888C 80087C8C 2631645C */  addiu $s1, %lo(gControllersXAxisDirection) # addiu $s1, $s1, 0x645c
/* 088890 80087C90 00008025 */  move  $s0, $zero
.L80087C94:
/* 088894 80087C94 822C0000 */  lb    $t4, ($s1)
/* 088898 80087C98 824D0000 */  lb    $t5, ($s2)
/* 08889C 80087C9C 02002025 */  move  $a0, $s0
/* 0888A0 80087CA0 AFA60030 */  sw    $a2, 0x30($sp)
/* 0888A4 80087CA4 028CA021 */  addu  $s4, $s4, $t4
/* 0888A8 80087CA8 0C01A955 */  jal   get_buttons_pressed_from_player
/* 0888AC 80087CAC 026D9821 */   addu  $s3, $s3, $t5
/* 0888B0 80087CB0 8FA60030 */  lw    $a2, 0x30($sp)
/* 0888B4 80087CB4 26100001 */  addiu $s0, $s0, 1
/* 0888B8 80087CB8 24010004 */  li    $at, 4
/* 0888BC 80087CBC 26310001 */  addiu $s1, $s1, 1
/* 0888C0 80087CC0 26520001 */  addiu $s2, $s2, 1
/* 0888C4 80087CC4 1601FFF3 */  bne   $s0, $at, .L80087C94
/* 0888C8 80087CC8 00C23025 */   or    $a2, $a2, $v0
.L80087CCC:
/* 0888CC 80087CCC 3C028012 */  lui   $v0, %hi(D_801263E0) # $v0, 0x8012
/* 0888D0 80087CD0 8C4263E0 */  lw    $v0, %lo(D_801263E0)($v0)
/* 0888D4 80087CD4 00C02025 */  move  $a0, $a2
/* 0888D8 80087CD8 304E0008 */  andi  $t6, $v0, 8
/* 0888DC 80087CDC 11C00006 */  beqz  $t6, .L80087CF8
/* 0888E0 80087CE0 2C410008 */   sltiu $at, $v0, 8
/* 0888E4 80087CE4 0C021DCD */  jal   func_80087734
/* 0888E8 80087CE8 02602825 */   move  $a1, $s3
/* 0888EC 80087CEC 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 0888F0 80087CF0 10000066 */  b     .L80087E8C
/* 0888F4 80087CF4 AC22F47C */   sw    $v0, %lo(gMenuDelay)($at)
.L80087CF8:
/* 0888F8 80087CF8 1020005D */  beqz  $at, .L80087E70
/* 0888FC 80087CFC 00027880 */   sll   $t7, $v0, 2
/* 088900 80087D00 3C01800F */  lui   $at, %hi(jpt_800E84B0) # $at, 0x800f
/* 088904 80087D04 002F0821 */  addu  $at, $at, $t7
/* 088908 80087D08 8C2F84B0 */  lw    $t7, %lo(jpt_800E84B0)($at)
/* 08890C 80087D0C 00000000 */  nop   
/* 088910 80087D10 01E00008 */  jr    $t7
/* 088914 80087D14 00000000 */   nop   
glabel L80087D18
/* 088918 80087D18 2418FFFF */  li    $t8, -1
/* 08891C 80087D1C 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 088920 80087D20 10000053 */  b     .L80087E70
/* 088924 80087D24 AC38F47C */   sw    $t8, %lo(gMenuDelay)($at)
glabel L80087D28
/* 088928 80087D28 3C108012 */  lui   $s0, %hi(D_801263D8) # $s0, 0x8012
/* 08892C 80087D2C 261063D8 */  addiu $s0, %lo(D_801263D8) # addiu $s0, $s0, 0x63d8
/* 088930 80087D30 8E190000 */  lw    $t9, ($s0)
/* 088934 80087D34 240A0002 */  li    $t2, 2
/* 088938 80087D38 27280001 */  addiu $t0, $t9, 1
/* 08893C 80087D3C 2901000B */  slti  $at, $t0, 0xb
/* 088940 80087D40 1420004B */  bnez  $at, .L80087E70
/* 088944 80087D44 AE080000 */   sw    $t0, ($s0)
/* 088948 80087D48 3C018012 */  lui   $at, %hi(D_801263E0) # $at, 0x8012
/* 08894C 80087D4C 10000048 */  b     .L80087E70
/* 088950 80087D50 AC2A63E0 */   sw    $t2, %lo(D_801263E0)($at)
glabel L80087D54
/* 088954 80087D54 3C018012 */  lui   $at, %hi(D_80126BD4) # $at, 0x8012
/* 088958 80087D58 44802000 */  mtc1  $zero, $f4
/* 08895C 80087D5C AC206BD4 */  sw    $zero, %lo(D_80126BD4)($at)
/* 088960 80087D60 3C018012 */  lui   $at, %hi(D_80126BDC) # $at, 0x8012
/* 088964 80087D64 0C0218B1 */  jal   func_800862C4
/* 088968 80087D68 E4246BDC */   swc1  $f4, %lo(D_80126BDC)($at)
/* 08896C 80087D6C 10400005 */  beqz  $v0, .L80087D84
/* 088970 80087D70 00402025 */   move  $a0, $v0
/* 088974 80087D74 0C021C76 */  jal   func_800871D8
/* 088978 80087D78 00000000 */   nop   
/* 08897C 80087D7C 1000003C */  b     .L80087E70
/* 088980 80087D80 00000000 */   nop   
.L80087D84:
/* 088984 80087D84 240B0003 */  li    $t3, 3
/* 088988 80087D88 3C018012 */  lui   $at, %hi(D_801263E0) # $at, 0x8012
/* 08898C 80087D8C 10000038 */  b     .L80087E70
/* 088990 80087D90 AC2B63E0 */   sw    $t3, %lo(D_801263E0)($at)
glabel L80087D94
/* 088994 80087D94 00C02025 */  move  $a0, $a2
/* 088998 80087D98 0C021D34 */  jal   func_800874D0
/* 08899C 80087D9C 02802825 */   move  $a1, $s4
/* 0889A0 80087DA0 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 0889A4 80087DA4 10000032 */  b     .L80087E70
/* 0889A8 80087DA8 AC22F47C */   sw    $v0, %lo(gMenuDelay)($at)
glabel L80087DAC
/* 0889AC 80087DAC 3C018012 */  lui   $at, %hi(D_80126BE4) # $at, 0x8012
/* 0889B0 80087DB0 44803000 */  mtc1  $zero, $f6
/* 0889B4 80087DB4 AC206BE4 */  sw    $zero, %lo(D_80126BE4)($at)
/* 0889B8 80087DB8 3C018012 */  lui   $at, %hi(D_80126BEC) # $at, 0x8012
/* 0889BC 80087DBC 0C0219F5 */  jal   func_800867D4
/* 0889C0 80087DC0 E4266BEC */   swc1  $f6, %lo(D_80126BEC)($at)
/* 0889C4 80087DC4 10400005 */  beqz  $v0, .L80087DDC
/* 0889C8 80087DC8 00402025 */   move  $a0, $v0
/* 0889CC 80087DCC 0C021C76 */  jal   func_800871D8
/* 0889D0 80087DD0 00000000 */   nop   
/* 0889D4 80087DD4 10000026 */  b     .L80087E70
/* 0889D8 80087DD8 00000000 */   nop   
.L80087DDC:
/* 0889DC 80087DDC 240C0005 */  li    $t4, 5
/* 0889E0 80087DE0 3C018012 */  lui   $at, %hi(D_801263E0) # $at, 0x8012
/* 0889E4 80087DE4 10000022 */  b     .L80087E70
/* 0889E8 80087DE8 AC2C63E0 */   sw    $t4, %lo(D_801263E0)($at)
glabel L80087DEC
/* 0889EC 80087DEC 00C02025 */  move  $a0, $a2
/* 0889F0 80087DF0 0C021D79 */  jal   func_800875E4
/* 0889F4 80087DF4 02802825 */   move  $a1, $s4
/* 0889F8 80087DF8 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 0889FC 80087DFC 1000001C */  b     .L80087E70
/* 088A00 80087E00 AC22F47C */   sw    $v0, %lo(gMenuDelay)($at)
glabel L80087E04
/* 088A04 80087E04 00C02025 */  move  $a0, $a2
/* 088A08 80087E08 0C021DB3 */  jal   func_800876CC
/* 088A0C 80087E0C 02802825 */   move  $a1, $s4
/* 088A10 80087E10 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 088A14 80087E14 10000016 */  b     .L80087E70
/* 088A18 80087E18 AC22F47C */   sw    $v0, %lo(gMenuDelay)($at)
glabel L80087E1C
/* 088A1C 80087E1C 3C108012 */  lui   $s0, %hi(D_801263D8) # $s0, 0x8012
/* 088A20 80087E20 261063D8 */  addiu $s0, %lo(D_801263D8) # addiu $s0, $s0, 0x63d8
/* 088A24 80087E24 8E0D0000 */  lw    $t5, ($s0)
/* 088A28 80087E28 00000000 */  nop   
/* 088A2C 80087E2C 25AE0001 */  addiu $t6, $t5, 1
/* 088A30 80087E30 29C10004 */  slti  $at, $t6, 4
/* 088A34 80087E34 1420000E */  bnez  $at, .L80087E70
/* 088A38 80087E38 AE0E0000 */   sw    $t6, ($s0)
/* 088A3C 80087E3C 0C021ABF */  jal   func_80086AFC
/* 088A40 80087E40 00000000 */   nop   
/* 088A44 80087E44 10400005 */  beqz  $v0, .L80087E5C
/* 088A48 80087E48 00402025 */   move  $a0, $v0
/* 088A4C 80087E4C 0C021C76 */  jal   func_800871D8
/* 088A50 80087E50 00000000 */   nop   
/* 088A54 80087E54 10000006 */  b     .L80087E70
/* 088A58 80087E58 00000000 */   nop   
.L80087E5C:
/* 088A5C 80087E5C 24180006 */  li    $t8, 6
/* 088A60 80087E60 AE180000 */  sw    $t8, ($s0)
/* 088A64 80087E64 24190001 */  li    $t9, 1
/* 088A68 80087E68 3C018012 */  lui   $at, %hi(D_801263E0) # $at, 0x8012
/* 088A6C 80087E6C AC3963E0 */  sw    $t9, %lo(D_801263E0)($at)
.L80087E70:
/* 088A70 80087E70 3C08800E */  lui   $t0, %hi(gMenuDelay) # $t0, 0x800e
/* 088A74 80087E74 8D08F47C */  lw    $t0, %lo(gMenuDelay)($t0)
/* 088A78 80087E78 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 088A7C 80087E7C 11000003 */  beqz  $t0, .L80087E8C
/* 088A80 80087E80 00000000 */   nop   
/* 088A84 80087E84 0C030076 */  jal   func_800C01D8
/* 088A88 80087E88 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
.L80087E8C:
/* 088A8C 80087E8C 3C018012 */  lui   $at, %hi(gIgnorePlayerInput) # $at, 0x8012
/* 088A90 80087E90 AC2063C4 */  sw    $zero, %lo(gIgnorePlayerInput)($at)
/* 088A94 80087E94 00001025 */  move  $v0, $zero
.L80087E98:
/* 088A98 80087E98 8FBF002C */  lw    $ra, 0x2c($sp)
/* 088A9C 80087E9C 8FB00018 */  lw    $s0, 0x18($sp)
/* 088AA0 80087EA0 8FB1001C */  lw    $s1, 0x1c($sp)
/* 088AA4 80087EA4 8FB20020 */  lw    $s2, 0x20($sp)
/* 088AA8 80087EA8 8FB30024 */  lw    $s3, 0x24($sp)
/* 088AAC 80087EAC 8FB40028 */  lw    $s4, 0x28($sp)
/* 088AB0 80087EB0 03E00008 */  jr    $ra
/* 088AB4 80087EB4 27BD0038 */   addiu $sp, $sp, 0x38

