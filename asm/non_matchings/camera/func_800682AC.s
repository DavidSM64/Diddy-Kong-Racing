glabel func_800682AC
/* 068EAC 800682AC 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 068EB0 800682B0 AFBF001C */  sw    $ra, 0x1c($sp)
/* 068EB4 800682B4 240E0004 */  li    $t6, 4
/* 068EB8 800682B8 3C018012 */  lui   $at, %hi(D_80120CE4) # $at, 0x8012
/* 068EBC 800682BC AC2E0CE4 */  sw    $t6, %lo(D_80120CE4)($at)
/* 068EC0 800682C0 0C01E948 */  jal   get_video_width_and_height_as_s32
/* 068EC4 800682C4 AFA40020 */   sw    $a0, 0x20($sp)
/* 068EC8 800682C8 3C0F8012 */  lui   $t7, %hi(D_80120CE4) # $t7, 0x8012
/* 068ECC 800682CC 8DEF0CE4 */  lw    $t7, %lo(D_80120CE4)($t7)
/* 068ED0 800682D0 3C19800E */  lui   $t9, %hi(gScreenViewports + 0x30) # $t9, 0x800e
/* 068ED4 800682D4 000FC080 */  sll   $t8, $t7, 2
/* 068ED8 800682D8 030FC023 */  subu  $t8, $t8, $t7
/* 068EDC 800682DC 0018C080 */  sll   $t8, $t8, 2
/* 068EE0 800682E0 030FC021 */  addu  $t8, $t8, $t7
/* 068EE4 800682E4 0018C080 */  sll   $t8, $t8, 2
/* 068EE8 800682E8 0338C821 */  addu  $t9, $t9, $t8
/* 068EEC 800682EC 8F39D094 */  lw    $t9, %lo(gScreenViewports + 0x30)($t9)
/* 068EF0 800682F0 8FA40020 */  lw    $a0, 0x20($sp)
/* 068EF4 800682F4 332A0001 */  andi  $t2, $t9, 1
/* 068EF8 800682F8 00024402 */  srl   $t0, $v0, 0x10
/* 068EFC 800682FC 15400035 */  bnez  $t2, .L800683D4
/* 068F00 80068300 3049FFFF */   andi  $t1, $v0, 0xffff
/* 068F04 80068304 8C820000 */  lw    $v0, ($a0)
/* 068F08 80068308 252DFFFF */  addiu $t5, $t1, -1
/* 068F0C 8006830C 448D2000 */  mtc1  $t5, $f4
/* 068F10 80068310 3C014080 */  li    $at, 0x40800000 # 4.000000
/* 068F14 80068314 244B0008 */  addiu $t3, $v0, 8
/* 068F18 80068318 44810000 */  mtc1  $at, $f0
/* 068F1C 8006831C AC8B0000 */  sw    $t3, ($a0)
/* 068F20 80068320 3C0CED00 */  lui   $t4, 0xed00
/* 068F24 80068324 AC4C0000 */  sw    $t4, ($v0)
/* 068F28 80068328 05A10005 */  bgez  $t5, .L80068340
/* 068F2C 8006832C 468021A0 */   cvt.s.w $f6, $f4
/* 068F30 80068330 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 068F34 80068334 44814000 */  mtc1  $at, $f8
/* 068F38 80068338 00000000 */  nop   
/* 068F3C 8006833C 46083180 */  add.s $f6, $f6, $f8
.L80068340:
/* 068F40 80068340 46003282 */  mul.s $f10, $f6, $f0
/* 068F44 80068344 250AFFFF */  addiu $t2, $t0, -1
/* 068F48 80068348 448A9000 */  mtc1  $t2, $f18
/* 068F4C 8006834C 444EF800 */  cfc1  $t6, $31
/* 068F50 80068350 00000000 */  nop   
/* 068F54 80068354 35C10003 */  ori   $at, $t6, 3
/* 068F58 80068358 38210002 */  xori  $at, $at, 2
/* 068F5C 8006835C 44C1F800 */  ctc1  $at, $31
/* 068F60 80068360 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 068F64 80068364 46005424 */  cvt.w.s $f16, $f10
/* 068F68 80068368 440F8000 */  mfc1  $t7, $f16
/* 068F6C 8006836C 44CEF800 */  ctc1  $t6, $31
/* 068F70 80068370 31F80FFF */  andi  $t8, $t7, 0xfff
/* 068F74 80068374 0018CB00 */  sll   $t9, $t8, 0xc
/* 068F78 80068378 05410004 */  bgez  $t2, .L8006838C
/* 068F7C 8006837C 46809120 */   cvt.s.w $f4, $f18
/* 068F80 80068380 44814000 */  mtc1  $at, $f8
/* 068F84 80068384 00000000 */  nop   
/* 068F88 80068388 46082100 */  add.s $f4, $f4, $f8
.L8006838C:
/* 068F8C 8006838C 46002182 */  mul.s $f6, $f4, $f0
/* 068F90 80068390 444BF800 */  cfc1  $t3, $31
/* 068F94 80068394 00092842 */  srl   $a1, $t1, 1
/* 068F98 80068398 35610003 */  ori   $at, $t3, 3
/* 068F9C 8006839C 38210002 */  xori  $at, $at, 2
/* 068FA0 800683A0 44C1F800 */  ctc1  $at, $31
/* 068FA4 800683A4 00083042 */  srl   $a2, $t0, 1
/* 068FA8 800683A8 460032A4 */  cvt.w.s $f10, $f6
/* 068FAC 800683AC 00A03825 */  move  $a3, $a1
/* 068FB0 800683B0 440C5000 */  mfc1  $t4, $f10
/* 068FB4 800683B4 44CBF800 */  ctc1  $t3, $31
/* 068FB8 800683B8 318D0FFF */  andi  $t5, $t4, 0xfff
/* 068FBC 800683BC 032D7025 */  or    $t6, $t9, $t5
/* 068FC0 800683C0 AC4E0004 */  sw    $t6, 4($v0)
/* 068FC4 800683C4 0C01A056 */  jal   func_80068158
/* 068FC8 800683C8 AFA60010 */   sw    $a2, 0x10($sp)
/* 068FCC 800683CC 1000000A */  b     .L800683F8
/* 068FD0 800683D0 8FBF001C */   lw    $ra, 0x1c($sp)
.L800683D4:
/* 068FD4 800683D4 0C019E8F */  jal   func_80067A3C
/* 068FD8 800683D8 AFA40020 */   sw    $a0, 0x20($sp)
/* 068FDC 800683DC 8FA40020 */  lw    $a0, 0x20($sp)
/* 068FE0 800683E0 00002825 */  move  $a1, $zero
/* 068FE4 800683E4 00003025 */  move  $a2, $zero
/* 068FE8 800683E8 00003825 */  move  $a3, $zero
/* 068FEC 800683EC 0C01A056 */  jal   func_80068158
/* 068FF0 800683F0 AFA00010 */   sw    $zero, 0x10($sp)
/* 068FF4 800683F4 8FBF001C */  lw    $ra, 0x1c($sp)
.L800683F8:
/* 068FF8 800683F8 3C018012 */  lui   $at, %hi(D_80120CE4) # $at, 0x8012
/* 068FFC 800683FC AC200CE4 */  sw    $zero, %lo(D_80120CE4)($at)
/* 069000 80068400 03E00008 */  jr    $ra
/* 069004 80068404 27BD0020 */   addiu $sp, $sp, 0x20

